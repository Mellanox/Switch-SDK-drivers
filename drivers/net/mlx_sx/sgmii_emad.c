/*
 * Copyright (C) 2010-2023 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of NVIDIA CORPORATION & AFFILIATES, Ltd.
 * (the "Company") and all right, title, and interest in and to the software product,
 * including all associated intellectual property rights, are and shall
 * remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 *
 */

#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include <linux/mlx_sx/map.h>

#include "sgmii_internal.h"
#include "emad.h"

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

    memcpy(&tr_id, ci->skb->data + EMAD_FRAME_TRANSACTION_ID_OFFSET,
           sizeof(tr_id));
    tr_id = be64_to_cpu(tr_id);

    if (!sgmii_transaction_check_completion(&__emad_tr_db, ci->skb, tr_id,
                                            rx_dev)) {
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
        sx_skb_free(skb);   /* drop packet flow, use kfree_skb */
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

static int __sgmii_send_emad_sync(int                    dev_id,
                                  struct sk_buff        *skb,
                                  const struct isx_meta *meta,
                                  struct sk_buff       **reply_skb)
{
    return sgmii_send_transaction_sync(dev_id, skb, meta, __sgmii_send_emad,
                                       reply_skb);
}

static void __sgmii_emad_transaction_completion(struct sk_buff                          *rx_skb,
                                                enum sgmii_transaction_completion_status status,
                                                struct sgmii_transaction_info           *tr_info,
                                                void                                    *context)
{
    switch (status) {
    case SGMII_TR_COMP_ST_COMPLETED:
        SGMII_DEV_INC_COUNTER(tr_info->orig_tx_dev,
                              emad_transaction_completed);
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
        struct sgmii_sync_transaction_context *tr_ctx =
            (struct sgmii_sync_transaction_context*)context;
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
    static const uint32_t tid_high = cpu_to_be32(SGMII_TR_ID_PREFIX);
    static atomic_t       tid_low_atomic = ATOMIC_INIT(0);
    uint32_t              tid_low = cpu_to_be32(atomic_inc_return(&tid_low_atomic));

    return sx_emad_build((sxd_dev_id_t)dev_id, reg_buff, reg_buff_len, skb, meta,
                         tid_high, tid_low,
                         GFP_KERNEL, reg_id, method);
}

static int __sgmii_emad_build_and_send_sync(int              dev_id,
                                            const uint8_t  * reg_buff,
                                            uint32_t         reg_buff_len,
                                            uint16_t         reg_id,
                                            uint8_t          method,
                                            struct sk_buff **reply_skb)
{
    struct isx_meta meta;
    struct sk_buff *skb;
    int             err;


    if (dev_id == DEFAULT_DEVICE_ID) {
        err = sgmii_default_dev_id_get(&dev_id);
        if (err) {
            COUNTER_INC(
                &__sgmii_global_counters.tx_default_device_not_configured);
            return err;
        }
    }

    err = __sgmii_emad_build(dev_id, reg_buff, reg_buff_len, &skb, &meta,
                             GFP_KERNEL, reg_id, method);

    if (!err) {
        err = __sgmii_send_emad_sync(dev_id, skb, &meta, reply_skb);
    }

    return err;
}

int sgmii_emad_access_ppad(int dev_id, const struct ku_ppad_reg *reg_ppad)
{
    uint8_t ppad[16] =
    { 0 };

    ppad[0] = 0x1c; /* single_base_mac = single_mac, pnat=OOB */
    ppad[0] |= reg_ppad->lp_msb & 0x3;
    ppad[1] = reg_ppad->local_port;
    memcpy(&ppad[2], reg_ppad->mac, 6);

    return __sgmii_emad_build_and_send_sync(dev_id, ppad, sizeof(ppad),
                                            PPAD_REG_ID, EMAD_METHOD_WRITE,
                                            NULL);
}

int sgmii_emad_access_hopf(int dev_id, const struct ku_hopf_reg *reg_hopf)
{
    uint8_t hopf[32] =
    { 0 };
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

    return __sgmii_emad_build_and_send_sync(dev_id, hopf, sizeof(hopf),
                                            HOPF_REG_ID, EMAD_METHOD_WRITE,
                                            NULL);
}

int sgmii_emad_access_spzr(int dev_id, const struct ku_spzr_reg *reg_spzr)
{
    char inbox[256] = { 0 };

    __SPZR_encode(inbox, (struct ku_spzr_reg*)reg_spzr, NULL);
    return __sgmii_emad_build_and_send_sync(dev_id,
                                            inbox,
                                            sizeof(inbox),
                                            SPZR_REG_ID,
                                            EMAD_METHOD_WRITE,
                                            NULL);
}

int sgmii_emad_access_ppbmc(int dev_id, u8 method, /* EMAD_METHOD_QUERY / EMAD_METHOD_WRITE */
                            u32 reg_size_dwords, struct ku_ppbmc_reg *reg_ppbmc)
{
    struct sk_buff *reply_skb = NULL;
    u8             *ppbmc_in;
    int             ret = 0;

    ppbmc_in = kzalloc(reg_size_dwords * 4, GFP_KERNEL);
    if (!ppbmc_in) {
        ret = -ENOMEM;
        goto out;
    }

    __PPBMC_encode(ppbmc_in, reg_ppbmc, NULL);

    ret = __sgmii_emad_build_and_send_sync(
        dev_id, ppbmc_in, reg_size_dwords * 4, PPBMC_REG_ID,
        method,
        (method == EMAD_METHOD_QUERY) ? &reply_skb : NULL);

    if ((method == EMAD_METHOD_QUERY) && (ret == 0)) {
        __PPBMC_decode(reply_skb->data, reg_ppbmc, NULL);
    }

    if (reply_skb) {
        consume_skb(reply_skb); /* free unused skb, use consume_skb */
    }

    kfree(ppbmc_in);

out:
    return ret;
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
    ret = sx_core_add_synd(0, SXD_TRAP_ID_GENERAL_ETH_EMAD, L2_TYPE_DONT_CARE,
                           0, "sgmii_driver", 0, &dummy, __sgmii_rx_emad, NULL,
                           CHECK_DUP_DISABLED_E, NULL, NULL, 1);
    if (ret) {
        printk(KERN_ERR "failed to register EMAD handler (ret=%d)\n", ret);
    }

    return ret;
}

void sgmii_emad_deinit(void)
{
    union ku_filter_critireas dummy;

    dummy.dont_care.sysport = SYSPORT_DONT_CARE_VALUE;
    sx_core_remove_synd(0, SXD_TRAP_ID_GENERAL_ETH_EMAD, L2_TYPE_DONT_CARE, 0,
                        &dummy,
                        NULL,
                        NULL, __sgmii_rx_emad, NULL, 1, NULL);
}
