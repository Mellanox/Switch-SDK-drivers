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
#include <linux/mlx_sx/kernel_user.h>

#include "sgmii_internal.h"
#include "map.h"

#define EMAD_TRAP_ID                     (0x5)
#define EMAD_FRAME_TRANSACTION_ID_OFFSET (0x18)

static struct sgmii_transaction_db __emad_tr_db;
static atomic_t                    __sgmii_emad_transactions_in_progress = ATOMIC_INIT(0);
static void __emad_work_entry_status_cb(int err, struct sgmii_transaction_info *tr_info, void *context)
{
    if (err) {
        SGMII_DEV_INC_COUNTER(tr_info->orig_tx_dev, emad_send_failed);
    }

    if (tr_info->send_attempts_so_far > 1) {
        SGMII_DEV_INC_COUNTER(tr_info->orig_tx_dev, emad_retransmission);
    }
}


static void __sgmii_rx_emad(struct completion_info* ci, void *context)
{
    struct sgmii_dev      *rx_dev;
    sgmii_transaction_id_t tr_id;

    /* first check if this function handles a SGMII RX originated SKB */
    if (sgmii_rx_skb_cb_dev_id_get(ci->skb, &rx_dev) != 0) {
        /* probably skb comes from PCI handler */
        return;
    }

    SGMII_DEV_INC_COUNTER(rx_dev, emad_rx);

    memcpy(&tr_id, ci->skb->data + EMAD_FRAME_TRANSACTION_ID_OFFSET, sizeof(tr_id));
    tr_id = be64_to_cpu(tr_id);

    if (!sgmii_transaction_check_completion(&__emad_tr_db, ci->skb, tr_id, rx_dev)) {
        SGMII_DEV_INC_COUNTER(rx_dev, emad_unsolicited);
    }
}


static int __sgmii_send_emad(int                                    dev_id,
                             struct sk_buff                        *skb,
                             const struct isx_meta                 *meta,
                             struct sgmii_sync_transaction_context *sync_context)
{
    struct sgmii_dev             *sgmii_dev;
    sgmii_transaction_id_t        tr_id;
    int                           ret;
    struct sgmii_transaction_meta tr_meta;

    ret = sgmii_dev_get_by_id(dev_id, &sgmii_dev);
    if (ret) {
        /* no matter what, we free original skb so it will activate its destructor (just like with PCI) */
        sx_skb_free(skb);
        return ret;
    }

    SGMII_DEV_INC_COUNTER(sgmii_dev, emad_tx);

    memcpy(&tr_id, skb->data + EMAD_FRAME_TRANSACTION_ID_OFFSET, sizeof(tr_id));
    tr_id = be64_to_cpu(tr_id);

    if (sync_context) {
        sync_context->tr_db = &__emad_tr_db;
        sync_context->tr_id = tr_id;
    }

    tr_meta.skb = skb;
    tr_meta.tr_db = &__emad_tr_db;
    tr_meta.tr_id = tr_id;
    tr_meta.transport_type = SXD_COMMAND_TYPE_EMAD;

    ret = sgmii_send_transaction(&tr_meta, sgmii_dev, meta, sync_context);
    if (ret == 0) {
        atomic_inc(&__sgmii_emad_transactions_in_progress);
        goto dec_ref;
    }

    if (ret == -EINPROGRESS) {
        /* joined to an existing transaction. just have to release the dev refcnt */
        ret = 0;
    } else {
        SGMII_DEV_INC_COUNTER(sgmii_dev, emad_transaction_init_failed);
    }

dec_ref:

    sgmii_dev_dec_ref(sgmii_dev);
    return ret;
}


int sgmii_send_emad(int dev_id, struct sk_buff *skb, const struct isx_meta *meta)
{
    return __sgmii_send_emad(dev_id, skb, meta, NULL);
}


static int __sgmii_send_emad_sync(int dev_id, struct sk_buff *skb, const struct isx_meta *meta)
{
    return sgmii_send_transaction_sync(dev_id, skb, meta, __sgmii_send_emad, NULL);
}


static void __sgmii_emad_transaction_completion(struct sk_buff                          *rx_skb,
                                                enum sgmii_transaction_completion_status status,
                                                struct sgmii_transaction_info           *tr_info,
                                                void                                    *context)
{
    switch (status) {
    case SGMII_TR_COMP_ST_COMPLETED:
        SGMII_DEV_INC_COUNTER(tr_info->orig_tx_dev, emad_transaction_completed);
        break;

    case SGMII_TR_COMP_ST_RX_DEV_MISMATCH:
        SGMII_DEV_INC_COUNTER(tr_info->rx_dev, emad_dev_mismatch);
        break;

    case SGMII_TR_COMP_ST_TIMEDOUT:
        SGMII_DEV_INC_COUNTER(tr_info->orig_tx_dev, emad_timeout);
        break;

    default:
        break;
    }

    if (context) { /* only in sync transaction */
        struct sgmii_sync_transaction_context *tr_ctx = (struct sgmii_sync_transaction_context*)context;
        sgmii_sync_transaction_complete(tr_ctx, rx_skb, status);
    }

    atomic_dec(&__sgmii_emad_transactions_in_progress);
}


int sgmii_emad_get_transactions_in_progress(void)
{
    return atomic_read(&__sgmii_emad_transactions_in_progress);
}


static int __sgmii_emad_build(int              dev_id,
                              const uint8_t   *reg_buff,
                              uint32_t         reg_buff_len,
                              struct sk_buff **skb,
                              struct isx_meta *meta,
                              gfp_t            gfp,
                              uint16_t         reg_id,
                              uint8_t          method)
{
    uint8_t               emad_header[] = {
        0x01, 0x02, 0xc9, 0x00, 0x00, 0x01, /* dst mac */
        0x00, 0x02, 0xc9, 0x01, 0x02, 0x03, /* src mac */
        0x89, 0x32,                         /* ethtype */
        0x00,                               /* MLX proto */
        0x00                                /* version */
    };
    uint8_t               emad_op_tlv[] = {
        0x08, 0x04, 0x00, 0x00,             /* type, len, dr, status, gas, stat_details */
        0xff, 0xff, 0xff, 0x01,             /* reg_id, r, method, trap_index, emad_class */
        0xff, 0xff, 0xff, 0xff,             /* tid (high)*/
        0xff, 0xff, 0xff, 0xff,             /* tid (low) */
    };
    uint8_t              *p_reg_id = &emad_op_tlv[4];
    uint8_t              *p_method = &emad_op_tlv[6];
    uint8_t              *p_tid = &emad_op_tlv[8];
    uint8_t               emad_reg_tlv[] = {
        0xff, 0xff, 0x00, 0x00              /* type, len */
    };
    uint8_t              *p_type_len = &emad_reg_tlv[0];
    uint8_t               emad_end_tlv[] = {
        0x00, 0x01, 0x00, 0x00
    };
    static atomic_t       tid_low_atomic = ATOMIC_INIT(0);
    static const uint32_t tid_high = cpu_to_be32(SGMII_TR_ID_PREFIX);
    uint32_t              tid_low = cpu_to_be32(atomic_inc_return(&tid_low_atomic));
    uint16_t              reg_type_len = cpu_to_be16((3 << 11) | (1 + (reg_buff_len >> 2)));
    uint8_t              *p;
    struct sk_buff       *new_skb;

#define EMAD_BUFF_SIZE(reg_size_in_bytes) \
    (sizeof(emad_header) +                \
     sizeof(emad_op_tlv) +                \
     sizeof(emad_reg_tlv) +               \
     reg_size_in_bytes +                  \
     sizeof(emad_end_tlv))

    new_skb = alloc_skb(EMAD_BUFF_SIZE(reg_buff_len) * 2, gfp);
    if (!new_skb) {
        return -ENOMEM;
    }

    reg_id = cpu_to_be16(reg_id);
    memcpy(p_reg_id, &reg_id, 2);
    *p_method = method;
    memcpy(p_tid, &tid_high, 4);
    memcpy(p_tid + 4, &tid_low, 4);
    memcpy(p_type_len, &reg_type_len, 2);

    memset(meta, 0, sizeof(*meta));
    meta->etclass = 6;
    meta->swid = 0;
    meta->rdq = 0x1f;
    meta->lp = 1;
    meta->type = SX_PKT_TYPE_EMAD_CTL;
    meta->dev_id = (uint8_t)dev_id;

    skb_put(new_skb, EMAD_BUFF_SIZE(reg_buff_len));
    p = new_skb->data;

    memcpy(p, emad_header, sizeof(emad_header));
    p += sizeof(emad_header);

    memcpy(p, emad_op_tlv, sizeof(emad_op_tlv));
    p += sizeof(emad_op_tlv);

    memcpy(p, emad_reg_tlv, sizeof(emad_reg_tlv));
    p += sizeof(emad_reg_tlv);

    memcpy(p, reg_buff, reg_buff_len);
    p += reg_buff_len;

    memcpy(p, emad_end_tlv, sizeof(emad_end_tlv));

    *skb = new_skb;
    return 0;
}


int __sgmii_emad_build_and_send_sync(int            dev_id,
                                     const uint8_t* reg_buff,
                                     uint32_t       reg_buff_len,
                                     uint16_t       reg_id,
                                     uint8_t        method)
{
    struct isx_meta meta;
    struct sk_buff *skb;
    int             err;

    if (dev_id == DEFAULT_DEVICE_ID) {
        err = sgmii_default_dev_id_get(&dev_id);
        if (err) {
            COUNTER_INC(&__sgmii_global_counters.tx_default_device_not_configured);
            return err;
        }
    }

    err = __sgmii_emad_build(dev_id,
                             reg_buff,
                             reg_buff_len,
                             &skb,
                             &meta,
                             GFP_KERNEL,
                             reg_id,
                             method);

    if (!err) {
        err = __sgmii_send_emad_sync(dev_id, skb, &meta);
    }

    return err;
}


int sgmii_emad_access_ppad(int dev_id, const struct ku_ppad_reg *reg_ppad)
{
    uint8_t ppad[16] = { 0 };

    ppad[0] = 0x1c; /* single_base_mac = single_mac, pnat=OOB */
    ppad[1] = reg_ppad->local_port;
    memcpy(&ppad[2], reg_ppad->mac, 6);

    return __sgmii_emad_build_and_send_sync(dev_id, ppad, sizeof(ppad), PPAD_REG_ID, EMAD_METHOD_WRITE);
}


int sgmii_emad_access_hopf(int dev_id, const struct ku_hopf_reg *reg_hopf)
{
    uint8_t  hopf[32] = { 0 };
    uint32_t flow_number;
    uint16_t vid;

    hopf[0] = (reg_hopf->sr << 7) | reg_hopf->cqe_ver;
    flow_number = cpu_to_be32(reg_hopf->flow_number & 0xffffff);
    memcpy(&hopf[1], ((uint8_t*)&flow_number) + 1, 3);
    hopf[4] = reg_hopf->rcv_cpu_tclass;
    hopf[7] = reg_hopf->i_f;
    memcpy(&hopf[10], reg_hopf->mac, 6);
    hopf[17] = 1;

    vid = cpu_to_be16((reg_hopf->pcp << 12) | reg_hopf->vid);
    memcpy(&hopf[18], &vid, 2);

    return __sgmii_emad_build_and_send_sync(dev_id, hopf, sizeof(hopf), HOPF_REG_ID, EMAD_METHOD_WRITE);
}


int sgmii_emad_access_spzr(int dev_id, const struct ku_spzr_reg *reg_spzr)
{
    uint32_t spzr_dwords[64] = { 0 };

    __sgmii_bit_field_set(&spzr_dwords[0], 1, 1, reg_spzr->EnhSwP0);
    __sgmii_bit_field_set(&spzr_dwords[0], 8, 8, reg_spzr->g0);
    __sgmii_bit_field_set(&spzr_dwords[0], 9, 9, reg_spzr->ng);
    __sgmii_bit_field_set(&spzr_dwords[0], 10, 10, reg_spzr->sig);
    __sgmii_bit_field_set(&spzr_dwords[0], 11, 11, reg_spzr->mp);
    __sgmii_bit_field_set(&spzr_dwords[0], 12, 12, reg_spzr->vk);
    __sgmii_bit_field_set(&spzr_dwords[0], 13, 13, reg_spzr->cm);
    __sgmii_bit_field_set(&spzr_dwords[0], 14, 14, reg_spzr->EnhSwP0_mask);
    __sgmii_bit_field_set(&spzr_dwords[0], 15, 15, reg_spzr->ndm);
    __sgmii_bit_field_set(&spzr_dwords[0], 24, 31, reg_spzr->swid);
    CONVERT_TO_NETWORK_ORDER(spzr_dwords[0]);

    __sgmii_bit_field_set(&spzr_dwords[1], 0, 31, reg_spzr->capability_mask);
    CONVERT_TO_NETWORK_ORDER(spzr_dwords[1]);

    __sgmii_64bit_field_set(&spzr_dwords[2], &spzr_dwords[3], reg_spzr->system_image_guid_h_l);
    CONVERT_TO_NETWORK_ORDER(spzr_dwords[2]);
    CONVERT_TO_NETWORK_ORDER(spzr_dwords[3]);

    __sgmii_64bit_field_set(&spzr_dwords[4], &spzr_dwords[5], reg_spzr->guid0_h_l);
    CONVERT_TO_NETWORK_ORDER(spzr_dwords[4]);
    CONVERT_TO_NETWORK_ORDER(spzr_dwords[5]);

    __sgmii_64bit_field_set(&spzr_dwords[6], &spzr_dwords[7], reg_spzr->node_guid_h_l);
    CONVERT_TO_NETWORK_ORDER(spzr_dwords[6]);
    CONVERT_TO_NETWORK_ORDER(spzr_dwords[7]);

    __sgmii_bit_field_set(&spzr_dwords[8], 0, 31, reg_spzr->v_key_h);
    CONVERT_TO_NETWORK_ORDER(spzr_dwords[8]);

    __sgmii_bit_field_set(&spzr_dwords[9], 0, 31, reg_spzr->v_key_l);
    CONVERT_TO_NETWORK_ORDER(spzr_dwords[9]);

    /* spzr_dwords[10] is all 0's */

    __sgmii_bit_field_set(&spzr_dwords[11], 16, 31, reg_spzr->max_pkey);
    CONVERT_TO_NETWORK_ORDER(spzr_dwords[11]);

    memcpy(&spzr_dwords[12], reg_spzr->NodeDescription, sizeof(reg_spzr->NodeDescription));

    return __sgmii_emad_build_and_send_sync(dev_id,
                                            (uint8_t*)spzr_dwords,
                                            sizeof(spzr_dwords),
                                            SPZR_REG_ID,
                                            EMAD_METHOD_WRITE);
}


int sgmii_emad_init(void)
{
    union ku_filter_critireas dummy;
    int                       ret;

    ret = sgmii_transaction_db_init(&__emad_tr_db,
                                    sgmii_fill_common_control_segment,
                                    sgmii_fill_common_tx_base_header,
                                    __emad_work_entry_status_cb,
                                    __sgmii_emad_transaction_completion);
    if (ret) {
        printk(KERN_ERR "failed to create emad transaction db (ret=%d)\n", ret);
        return ret;
    }

    dummy.dont_care.sysport = SYSPORT_DONT_CARE_VALUE;
    ret = sx_core_add_synd(0, EMAD_TRAP_ID, L2_TYPE_DONT_CARE, 0, 0, dummy, __sgmii_rx_emad,
                           NULL, CHECK_DUP_DISABLED_E, NULL, NULL, 1);
    if (ret) {
        printk(KERN_ERR "failed to register EMAD handler (ret=%d)\n", ret);
    }

    return ret;
}


void sgmii_emad_deinit(void)
{
    union ku_filter_critireas dummy;

    dummy.dont_care.sysport = SYSPORT_DONT_CARE_VALUE;
    sx_core_remove_synd(0, EMAD_TRAP_ID, L2_TYPE_DONT_CARE, 0, dummy, NULL, NULL, __sgmii_rx_emad, NULL, 1);
}
