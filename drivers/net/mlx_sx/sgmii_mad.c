/*
 * Copyright (c) 2010-2019,  Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/driver.h>

#include "sgmii_internal.h"
#include "map.h"

#define INFINIBAND_QP0_TRAP_ID       (0xf0)
#define INFINIBAND_QP1_TRAP_ID       (0xf1)
#define INFINIBAND_OTHER_QPS_TRAP_ID (0xf2)

#define MAD_HDR_LEN (0x18)                  /* length of MAD header */

#define UNRELIABLE_DATAGRAM_MAD_HDR_OFFSET (0x1c) /* LRH + BTH + DETH */
#define LRH_SLID_OFFSET                    (0x6)
#define MAD_HDR_TR_ID_OFFSET               (0x8)
#define MAD_HDR_STATUS_OFFSET              (0x4)
#define MAD_HDR_ATTR_ID_OFFSET             (0x10)

#define MAD_IFC_TR_ID_BITS (28)                 /* 28bit [the rest 4bits (MSB) reserved for op-modifier] */

static struct sgmii_transaction_db __mad_tr_db;
static atomic_t                    __sgmii_mad_transactions_in_progress = ATOMIC_INIT(0);
static struct mutex                __mad_ifc_mutex;
extern uint64_t                    sx_system_mkey;

int sgmii_get_mad_header_info(const uint8_t *buff,
                              uint32_t       buff_len,
                              uint32_t      *mad_hdr_offset,
                              uint64_t      *tr_id,
                              uint16_t      *attr_id)
{
    const uint8_t* lrh = buff; /* local route header */
    const uint8_t* bth = NULL; /* base transport header */
    const uint8_t* grh = NULL; /* global route header */
    uint32_t       offset = 0;

    switch (lrh[1] & 3) { /* 2bit of next-header */
    case 3: /* GRH header */
        grh = lrh + 8; /* length of LRH header */
        break;

    case 2: /* BTH header */
        bth = lrh + 8; /* length of LRH header */
        break;

    default:
        return -ENOENT;
    }

    offset += 8; /* length of LRH header */

    if (grh) {
        if (grh[6] != 0x1b) { /* GRH next-header field is @ index 6. it must be 0x1b for an IB transport */
            return -ENOENT;
        }

        bth = grh + 40; /* length of GRH header */
        offset += 40; /* length of GRH header */
    }

    offset += 12; /* length of BTH header */

    switch (bth[0] >> 5) { /* 3 MSBs of the first byte keep the code of the packet */
    case 2: /* reliable datagram (RD) */
        offset += 4 + 8; /* RDETH + DETH headers length */
        break;

    case 3: /* unreliable datagram (UD) */
        offset += 8; /* DETH header length */
        break;

    default:
        return -ENOENT;
    }

    if (offset >= buff_len) {
        return -ENOENT;
    }

    if (mad_hdr_offset) {
        *mad_hdr_offset = offset;
    }

    if (tr_id) {
        memcpy(tr_id, buff + offset + MAD_HDR_TR_ID_OFFSET, sizeof(*tr_id));
        *tr_id = be64_to_cpu(*tr_id);
    }

    if (attr_id) {
        memcpy(attr_id, buff + offset + MAD_HDR_ATTR_ID_OFFSET, sizeof(*attr_id));
        *attr_id = be16_to_cpu(*attr_id);
    }

    return 0;
}


static void __mad_work_entry_status_cb(int err, struct sgmii_transaction_info *tr_info, void *context)
{
    if (err) {
        SGMII_DEV_INC_COUNTER(tr_info->orig_tx_dev, mad_send_failed);
    }

    if (tr_info->send_attempts_so_far > 1) {
        SGMII_DEV_INC_COUNTER(tr_info->orig_tx_dev, mad_retransmission);
    }
}


static void __sgmii_rx_mad(struct completion_info* ci, void *context)
{
    struct sgmii_dev *rx_dev;

    /* first check if this function handles a SGMII RX originated SKB */
    if (sgmii_rx_skb_cb_dev_id_get(ci->skb, &rx_dev) != 0) {
        /* probably skb comes from PCI handler */
        return;
    }

    SGMII_DEV_INC_COUNTER(rx_dev, mad_rx);
    sgmii_transaction_check_completion(&__mad_tr_db, ci->skb, ci->info.ib.mad_tid, rx_dev);
}


struct send_mad_info {
    struct sgmii_dev                      *sgmii_dev;
    struct sk_buff                        *skb;
    struct isx_meta                        meta;
    uint8_t                                is_transaction;
    sgmii_transaction_id_t                 tr_id;
    struct sgmii_sync_transaction_context *sync_context;
};
static void __sgmii_send_mad_deferred(void *task_param)
{
    struct send_mad_info         *info;
    int                           ret = 0, should_free_skb = 1;
    struct sgmii_transaction_meta tr_meta;

    info = (struct send_mad_info*)task_param;

    SGMII_DEV_INC_COUNTER(info->sgmii_dev, mad_tx);

    /* If MAD is send not as transaction, we want it as simple send */
    if (!info->is_transaction) {
        ret = sgmii_send(info->sgmii_dev,
                         info->skb,
                         &info->meta,
                         SGMII_PCP_FROM_METADATA,
                         sgmii_fill_common_control_segment,
                         sgmii_fill_common_tx_base_header);

        if (ret) {
            SGMII_DEV_INC_COUNTER(info->sgmii_dev, mad_send_failed);
        }

        goto dec_ref;
    }

    /* If we're here, starting a transaction.
     * transaction will free the SKB when it completes (or upon failure), so we should not worry about it */
    should_free_skb = 0;

    tr_meta.skb = info->skb;
    tr_meta.tr_db = &__mad_tr_db;
    tr_meta.tr_id = info->tr_id;
    tr_meta.transport_type = SXD_COMMAND_TYPE_MAD;

    ret = sgmii_send_transaction(&tr_meta,
                                 info->sgmii_dev,
                                 &info->meta,
                                 info->sync_context);
    if (ret == 0) {
        atomic_inc(&__sgmii_mad_transactions_in_progress);
        goto dec_ref;
    }

    /* -EINPROGRESS ==> joined to an existing transaction. just have to release the dev refcnt */
    if (ret != -EINPROGRESS) {
        SGMII_DEV_INC_COUNTER(info->sgmii_dev, mad_transaction_init_failed);
    }

dec_ref:

    /* call kfree_skb() [and not sx_free_skb()] because we're only playing with the reference
     * count of the skb and not actually need to clean the frags list. the only place that should
     * clean the frag list is the completion handler, after the skb has been sent.
     *
     * just release the reference taken in sgmii_send_mad().
     * for sure it will not actually delete the skb and not call its destructor
     * the other reference is from sgmii_send() or sgmii_send_transaction() */
    kfree_skb(info->skb);

    if (should_free_skb) {
        /* we free original skb so it will activate its destructor (just like with PCI) */
        sx_skb_free(info->skb);
    }

    sgmii_dev_dec_ref(info->sgmii_dev);
}


static int __sgmii_send_mad(struct sgmii_dev                      *sgmii_dev,
                            struct sk_buff                        *skb,
                            const struct isx_meta                 *meta,
                            struct sgmii_sync_transaction_context *sync_context,
                            sgmii_transaction_id_t                 mad_tr_id,
                            uint8_t                                is_transaction)
{
    /*
     * we may get here from IB flow where in its layers it sends a packet within a scope of
     * spin_lock_irqsave/spin_lock_irqrestore so we cannot use the _bh style at all. we use dev_queue_xmit()
     * to send the packet to the SGMII network and this function uses _bh locks which is forbidden in IRQ context.
     * so, unfortunately, we have no choice but to defer the send to a workqueue where we are free to use any lock
     * method we want.
     */

    struct send_mad_info info;
    int                  ret;

    memset(&info, 0, sizeof(info));

    info.sgmii_dev = sgmii_dev;
    info.skb = skb_get(skb); /* __sgmii_send_mad_deferred will release the reference */
    info.sync_context = sync_context;
    info.is_transaction = is_transaction;
    info.tr_id = be64_to_cpu(mad_tr_id);
    memcpy(&info.meta, meta, sizeof(info.meta));

    if (sync_context) {
        sync_context->tr_db = &__mad_tr_db;
        sync_context->tr_id = info.tr_id;
    }

    ret = sgmii_queue_task(__sgmii_send_mad_deferred, &info, sizeof(info), 0);
    if (ret) {
        COUNTER_INC(&__sgmii_global_counters.tx_mad_deferred_send_failed);

        /* call kfree_skb() [and not sx_free_skb()] because we're only playing with the reference
         * count of the skb and not actually need to clean the frags list. the only place that should
         * clean the frag list is the completion handler, after the skb has been sent.
         * just release the reference taken here by skb_get(), for sure will not delete skb */
        kfree_skb(skb);

        sx_skb_free(skb); /* free original skb so it will activate its destructor (just like with PCI) */

        sgmii_dev_dec_ref(sgmii_dev);
    }

    return ret;
}


int sgmii_send_mad(int dev_id, struct sk_buff *skb, const struct isx_meta *meta)
{
    struct sgmii_dev      *sgmii_dev;
    sgmii_transaction_id_t mad_tr_id = 0;
    uint16_t               mad_attr_id = 0;
    uint8_t                is_transaction = 0;
    int                    ret;

    ret = sgmii_dev_get_by_id(dev_id, &sgmii_dev);
    if (ret) {
        return ret;
    }

    ret = sgmii_get_mad_header_info(skb->data, skb->len, NULL, &mad_tr_id, &mad_attr_id);
    if (ret) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, mad_unrecognized_packet);
        return -EFAULT;
    }

    /* If MAD is ACCESS_REG, we want to start a transaction, not a simple transmit */
    if (mad_attr_id == MAD_ATTR_ACCESS_REG) {
        is_transaction = 1;
    }

    return __sgmii_send_mad(sgmii_dev, skb, meta, NULL, mad_tr_id, is_transaction);
}


static int __sgmii_send_mad_ifc_cb(int                                    dev_id,
                                   struct sk_buff                        *skb,
                                   const struct isx_meta                 *meta,
                                   struct sgmii_sync_transaction_context *sync_context)
{
    struct sgmii_dev      *sgmii_dev;
    sgmii_transaction_id_t mad_tr_id;
    int                    ret;

    ret = sgmii_dev_get_by_id(dev_id, &sgmii_dev);
    if (ret) {
        return ret;
    }

    memcpy(&mad_tr_id, skb->data + UNRELIABLE_DATAGRAM_MAD_HDR_OFFSET + MAD_HDR_TR_ID_OFFSET, sizeof(mad_tr_id));
    return __sgmii_send_mad(sgmii_dev, skb, meta, sync_context, mad_tr_id, 1);
}


int sgmii_simulate_sync_mad_ifc(struct sx_dev* dev,
                                int            dev_id,
                                u32            in_modifier,
                                u8             op_modifier,
                                void          *in_mad,
                                int            in_size,
                                void          *out_mad,
                                int            out_size)
{
    static const uint8_t  ib_headers[] = { /* arr_size = UNRELIABLE_DATAGRAM_MAD_HDR_OFFSET = LRH + BTH + DETH */
        0xf0, 0x02, 0xff, 0xff, 0x00, 0x48, 0xff, 0xff, /* LRH */
        0x64, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* BTH */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 /* DETH */
    };
    static const uint32_t tid_high = cpu_to_be32(SGMII_TR_ID_PREFIX);
    static uint32_t       packet_seq_number = 0;
    uint64_t              orig_tr_id;
    uint32_t              tid_low;
    u8                    port = in_modifier & 0xff;
    u8                    swid = (in_modifier >> 8) & 0xff;
    u16                   slid = (in_modifier >> 16) & 0xffff;
    struct isx_meta       meta;
    struct sk_buff       *skb;
    struct sk_buff       *rx_skb;
    uint32_t              psn, mad_hdr_offset;
    int                   err;

    memset(&meta, 0, sizeof(meta));
    meta.swid = swid;
    meta.dev_id = dev_id;
    meta.type = SX_PKT_TYPE_IB_TRANSPORT_CTL;
    meta.lp = 1;
    err = sx_core_get_ib_system_port_mid(dev, port, &meta.system_port_mid);
    if (err) {
        return err;
    }

    skb = alloc_skb(1024, GFP_KERNEL);
    if (!skb) {
        return -ENOMEM;
    }

    skb_reserve(skb, 128);
    skb_put(skb, UNRELIABLE_DATAGRAM_MAD_HDR_OFFSET + in_size);

    /* encode IB headers */
    memcpy(skb->data, ib_headers, sizeof(ib_headers));
    if (slid) {
        slid = cpu_to_be16(slid);
        memcpy(skb->data + LRH_SLID_OFFSET, &slid, sizeof(slid));
    }

    err = mutex_lock_interruptible(&__mad_ifc_mutex);
    if (err) {
        kfree_skb(skb);
        return err;
    }

    /*
     * MAD_IFC transaction ID (64bit):
     *
     *    6         5         4         3         2         1
     * 3210987654321098765432109876543210987654321098765432109876543210
     * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                  0xC001D00D (SGMII MAD_IFC prefix)
     *                                 ^^^^                              Opcode modifier (4bits)
     *                                     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^  Running transaction ID (28bits)
     *
     */
    tid_low = (((u32)op_modifier) & 0xf) << MAD_IFC_TR_ID_BITS;
    tid_low |= (++packet_seq_number) & ((1U << MAD_IFC_TR_ID_BITS) - 1);

    tid_low = cpu_to_be32(tid_low);
    psn = tid_low;
    memcpy(skb->data + 17 /* psn offset */, &((char*)&psn)[1], 3);
    memcpy(&orig_tr_id, (char*)in_mad + MAD_HDR_TR_ID_OFFSET, 8);
    memcpy((char*)in_mad + MAD_HDR_TR_ID_OFFSET, &tid_high, 4);
    memcpy((char*)in_mad + MAD_HDR_TR_ID_OFFSET + 4, &tid_low, 4);

    /* encode MAD header */
    memcpy(skb->data + UNRELIABLE_DATAGRAM_MAD_HDR_OFFSET, in_mad, in_size);

    err = sgmii_send_transaction_sync(dev_id, skb, &meta, __sgmii_send_mad_ifc_cb, &rx_skb);
    if (err) {
        goto unlock;
    }

    err = sgmii_get_mad_header_info(rx_skb->data, rx_skb->len, &mad_hdr_offset, NULL, NULL);
    if (err) {
        goto out;
    }

    skb_pull(rx_skb, mad_hdr_offset);

    if (out_size > rx_skb->len) {
        out_size = rx_skb->len;
    }

    memcpy(out_mad, rx_skb->data, out_size);
    memcpy((char*)out_mad + MAD_HDR_TR_ID_OFFSET, &orig_tr_id, 8);

out:
    kfree_skb(rx_skb);

unlock:
    mutex_unlock(&__mad_ifc_mutex);
    return err;
}


static void __sgmii_mad_transaction_completion(struct sk_buff                          *rx_skb,
                                               enum sgmii_transaction_completion_status status,
                                               struct sgmii_transaction_info           *tr_info,
                                               void                                    *context)
{
    switch (status) {
    case SGMII_TR_COMP_ST_COMPLETED:
        SGMII_DEV_INC_COUNTER(tr_info->orig_tx_dev, mad_transaction_completed);
        break;

    case SGMII_TR_COMP_ST_RX_DEV_MISMATCH:
        SGMII_DEV_INC_COUNTER(tr_info->rx_dev, mad_dev_mismatch);
        break;

    case SGMII_TR_COMP_ST_TIMEDOUT:
        SGMII_DEV_INC_COUNTER(tr_info->orig_tx_dev, mad_timeout);
        break;

    default:
        break;
    }

    if (context) { /* only in sync transaction */
        struct sgmii_sync_transaction_context *tr_ctx = (struct sgmii_sync_transaction_context*)context;
        sgmii_sync_transaction_complete(tr_ctx, rx_skb, status);
    }

    atomic_dec(&__sgmii_mad_transactions_in_progress);
}


int sgmii_mad_get_transactions_in_progress(void)
{
    return atomic_read(&__sgmii_mad_transactions_in_progress);
}


int sgmii_mad_init(void)
{
    union ku_filter_critireas crit;
    int                       ret;

    memset(&crit, 0, sizeof(crit));
    crit.ib.is_oob_originated_mad = 255; /* don't care */

    mutex_init(&__mad_ifc_mutex);

    ret = sgmii_transaction_db_init(&__mad_tr_db,
                                    sgmii_fill_common_control_segment,
                                    sgmii_fill_common_tx_base_header,
                                    __mad_work_entry_status_cb,
                                    __sgmii_mad_transaction_completion);
    if (ret) {
        printk(KERN_ERR "failed to create mad transaction db (ret=%d)\n", ret);
        return ret;
    }

    crit.ib.qpn = 0;
    ret = sx_core_add_synd(0, INFINIBAND_QP0_TRAP_ID, L2_TYPE_IB, 0, 0, crit, __sgmii_rx_mad,
                           NULL, CHECK_DUP_DISABLED_E, NULL, NULL, 1);
    if (ret) {
        printk(KERN_ERR "failed to register MAD QP0 handler (ret=%d)\n", ret);
        goto mad_qp0_failed;
    }

    crit.ib.qpn = 1;
    ret = sx_core_add_synd(0, INFINIBAND_QP1_TRAP_ID, L2_TYPE_IB, 0, 0, crit, __sgmii_rx_mad,
                           NULL, CHECK_DUP_DISABLED_E, NULL, NULL, 1);
    if (ret) {
        printk(KERN_ERR "failed to register MAD QP1 handler (ret=%d)\n", ret);
        goto mad_qp1_failed;
    }

    crit.ib.qpn = QPN_MULTICAST_VALUE;
    ret = sx_core_add_synd(0, INFINIBAND_OTHER_QPS_TRAP_ID, L2_TYPE_IB, 0, 0, crit, __sgmii_rx_mad,
                           NULL, CHECK_DUP_DISABLED_E, NULL, NULL, 1);
    if (ret) {
        printk(KERN_ERR "failed to register MAD other-QPs handler (ret=%d)\n", ret);
        goto mad_other_qps_failed;
    }

    return 0;

mad_other_qps_failed:
    crit.ib.qpn = 1;
    sx_core_remove_synd(0, INFINIBAND_QP1_TRAP_ID, L2_TYPE_IB, 0, crit, NULL, NULL, __sgmii_rx_mad, NULL, 1);

mad_qp1_failed:
    crit.ib.qpn = 0;
    sx_core_remove_synd(0, INFINIBAND_QP0_TRAP_ID, L2_TYPE_IB, 0, crit, NULL, NULL, __sgmii_rx_mad, NULL, 1);

mad_qp0_failed:
    return ret;
}


void sgmii_mad_deinit(void)
{
    union ku_filter_critireas crit;

    memset(&crit, 0, sizeof(crit));
    crit.ib.is_oob_originated_mad = 255; /* don't care */

    crit.ib.qpn = 0;
    sx_core_remove_synd(0, INFINIBAND_QP0_TRAP_ID, L2_TYPE_IB, 0, crit, NULL, NULL, __sgmii_rx_mad, NULL, 1);

    crit.ib.qpn = 1;
    sx_core_remove_synd(0, INFINIBAND_QP1_TRAP_ID, L2_TYPE_IB, 0, crit, NULL, NULL, __sgmii_rx_mad, NULL, 1);

    crit.ib.qpn = QPN_MULTICAST_VALUE;
    sx_core_remove_synd(0, INFINIBAND_OTHER_QPS_TRAP_ID, L2_TYPE_IB, 0, crit, NULL, NULL, __sgmii_rx_mad, NULL, 1);
}
