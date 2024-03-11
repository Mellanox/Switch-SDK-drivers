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

/************************************************
 * Includes
 ***********************************************/

#include <linux/sched.h>
#include <linux/skbuff.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/hardirq.h>
#include <linux/interrupt.h>
#include <linux/kthread.h>
#include <linux/if_vlan.h>
#include <linux/filter.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/workqueue.h>
#include <linux/vmalloc.h>
#include <linux/mlx_sx/skb_hook.h>
#include <linux/ktime.h>
#include "sx.h"
#include "cq.h"
#include "dq.h"
#include "ib.h"
#include "alloc.h"
#include "sx_proc.h"
#include "sx_clock.h"
#include "ptp.h"
#include "sgmii.h"
#include "bulk_cntr_event.h"
#include "ber_monitor.h"
#include "drop_monitor.h"
#include "sx_af_counters.h"
#include "health_check.h"
#include "trace_func.h"

#include <linux/module.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/version.h>
#include <linux/ktime.h>
#include <linux/hrtimer.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
/************************************************
 *  Definitions
 ***********************************************/
#define IB_CRC_LENGTH  (6) /* CRC length of all IB packets except IB_Raw */
#define IB_VCRC_LENGTH (2) /* CRC length of IB_Raw packets */

#define HETT_TRAP_ID                 269
#define MAX_MATCHING_LISTENERS       100
#define SX_LATE_COMPLETION_THRESHOLD (2 * HZ) /* completion later than 2 seconds means 'late completion' */

static inline int PORT_VLAN_BIT_IS_SET(u64* arr, u64 num)
{
    u64 tmp;

    tmp = (arr)[(num) / 64];
    return tmp & (1ULL << ((num) % 64)) ? 1 : 0;
}


#ifdef CONFIG_SX_DEBUG
int sx_debug_cqn;
#define sx_dbg_cq(cqn, mdev, format, arg ...)                          \
    do {                                                               \
        if (sx_debug_level && cqn == sx_debug_cqn) {                   \
            if (net_ratelimit()) {                                     \
                dev_printk(KERN_DEBUG,                                 \
                           &(mdev)->pdev->dev, "%s.%d: CQ:%d "         \
                           format, __func__, __LINE__, cqn, ## arg); } \
        }                                                              \
    } while (0)
#else
#define sx_dbg_cq(cqn, mdev, format, arg ...) do { (void)mdev; } while (0)
#endif

/************************************************
 * Globals
 ***********************************************/

extern int   rx_debug;
extern int   rx_debug_pkt_type;
extern int   rx_debug_emad_type;
extern int   rx_cqev2_dbg;
extern int   rx_dump;
extern int   rx_dump_cnt;
extern int   cpu_traffic_priority_disrupt_low_prio_upon_stress;
extern int   cpu_traffic_priority_disrupt_low_prio_upon_stress_delay;
extern uint  mon_cq_thread_cpu_util_percent;
extern int   enable_monitor_rdq_trace_points;
extern int   enable_cpu_port_loopback;
extern int   enable_keep_packet_crc;
unsigned int credit_thread_vals[1001] = {0};
unsigned int arr_count = 0;
atomic_t     cq_backup_polling_enabled = ATOMIC_INIT(1);
int          debug_cq_backup_poll_cqn = CQN_INVALID;
struct handler_entry {
    cq_handler handler;
    void      *context;
};
struct cpu_loopback_data {
    struct completion_info *ci;
    struct delayed_work     dwork;
};

/************************************************
 *  Functions
 ***********************************************/

static void __sx_cq_dec_refcnt(struct sx_cq *cq)
{
    /*
     * decrement the reference count and if we reach 0, signal the 'free' completion
     * that tells the CQ is no longer in use and can be deleted
     */
    if (atomic_dec_and_test(&cq->refcount)) {
        complete(&cq->free);
    }
}

void sx_printk_cqe_v0(union sx_cqe *u_cqe)
{
    __be32 *cqebuf = (void*)u_cqe->v0;

    if (printk_ratelimit()) {
        pr_debug("CQEv0 %p contents:\n%08x\n%08x\n%08x\n%08x\n",
                 u_cqe->v0,
                 be32_to_cpu(cqebuf[0]),
                 be32_to_cpu(cqebuf[1]),
                 be32_to_cpu(cqebuf[2]),
                 be32_to_cpu(cqebuf[3]));
    }
}

void sx_printk_cqe_v1(union sx_cqe *u_cqe)
{
    __be32 *cqebuf = (void*)u_cqe->v1;

    if (printk_ratelimit()) {
        pr_debug("CQEv1 %p contents:\n%08x\n%08x\n%08x\n%08x\n",
                 u_cqe->v1,
                 be32_to_cpu(cqebuf[0]),
                 be32_to_cpu(cqebuf[1]),
                 be32_to_cpu(cqebuf[2]),
                 be32_to_cpu(cqebuf[3]));
    }
}

void sx_printk_cqe_v2(union sx_cqe *u_cqe)
{
    __be32 *cqebuf = (void*)u_cqe->v2;

    pr_debug("CQEv2 %p contents:\n%08x\n%08x\n%08x\n%08x\n%08x\n%08x\n%08x\n%08x\n",
             u_cqe->v2,
             be32_to_cpu(cqebuf[0]),
             be32_to_cpu(cqebuf[1]),
             be32_to_cpu(cqebuf[2]),
             be32_to_cpu(cqebuf[3]),
             be32_to_cpu(cqebuf[4]),
             be32_to_cpu(cqebuf[5]),
             be32_to_cpu(cqebuf[6]),
             be32_to_cpu(cqebuf[7]));
}

void sx_fill_ci_from_cqe_v0(struct completion_info *ci, union sx_cqe *u_cqe)
{
    ci->swid = (u_cqe->v0->type_swid >> 1) & 0x7;
    ci->is_lag = u_cqe->v0->lag & 0x80 ? 1 : 0;
    ci->sysport = be16_to_cpu(u_cqe->v0->system_port_lag_id);
    if (ci->is_lag) {
        ci->sysport = (ci->sysport >> 4) & 0xFFF;
    }
    ci->lag_subport = (ci->is_lag) ? u_cqe->v0->vlan2_lag_subport & 0x1F : 0;
    ci->pkt_type = (u_cqe->v0->type_swid >> 5) & 0x7;
    ci->is_send = (u_cqe->v0->e_sr_dqn_owner >> 6) & 0x1;
    ci->user_def_val = 0;
    ci->dest_sysport = 0xFFFF;
    ci->dest_is_lag = 0;
    ci->dest_lag_subport = 0;
    ci->mirror_reason = 0;
    ci->mirror_cong = 0xFFFF;
    ci->mirror_lantency = 0xFFFFFF;
    ci->mirror_tclass = 0x1F;
    ci->mirror_elephant = 0;
}

void sx_fill_ci_from_cqe_v2(struct completion_info *ci, union sx_cqe *u_cqe)
{
    ci->swid = (u_cqe->v2->type_swid_crc >> 2) & 0x7;
    ci->pkt_type = (u_cqe->v2->type_swid_crc >> 5) & 0x7;
    ci->is_send = (u_cqe->v2->version_e_sr_packet_ok_rp_lag >> 2) & 0x1;
    ci->is_lag = u_cqe->v2->version_e_sr_packet_ok_rp_lag & 0x1;
    ci->sysport = be16_to_cpu(u_cqe->v2->rp_system_port_lag_id);
    ci->lag_subport = (ci->is_lag) ? u_cqe->v2->rp_lag_subport : 0;
    ci->user_def_val = be32_to_cpu(u_cqe->v2->mirror_cong1_user_def_val_orig_pkt_len) & 0xFFFFF;
    ci->dest_sysport = be16_to_cpu(u_cqe->v2->ep_system_port_lag_id);
    ci->dest_is_lag = u_cqe->v2->mirror_tclass_mirror_elph_ep_lag & 0x1;
    ci->dest_lag_subport = (ci->dest_is_lag) ? u_cqe->v2->ep_lag_subport : 0;
    ci->mirror_reason = (be32_to_cpu(u_cqe->v2->mirror_reason_time_stamp_type_time_stamp2) >> 24) & 0xFF;
    ci->mirror_cong = (be16_to_cpu(u_cqe->v2->vlan_mirror_cong2) & 0xF) << 12;
    ci->mirror_cong |= (be32_to_cpu(u_cqe->v2->mirror_cong1_user_def_val_orig_pkt_len) >> 20) & 0xFFF;
    ci->mirror_lantency = (be16_to_cpu(u_cqe->v2->mirror_latency2) << 8) | u_cqe->v2->mirror_latency1;
    ci->mirror_tclass = (u_cqe->v2->mirror_tclass_mirror_elph_ep_lag >> 3) & 0x1F;
    ci->mirror_elephant = (u_cqe->v2->mirror_tclass_mirror_elph_ep_lag >> 1) & 0x3;
}

void sx_fill_params_from_cqe_v0(union sx_cqe *u_cqe,
                                u16          *hw_synd_p,
                                u8           *is_isx_p,
                                u16          *byte_count_p,
                                u8           *dqn_p,
                                u8           *crc_present_p)
{
    *hw_synd_p = be16_to_cpu(u_cqe->v0->trap_id) & 0x01FF;
    *is_isx_p = be16_to_cpu(u_cqe->v0->dqn5_byte_count) >> 15;
    *byte_count_p = be16_to_cpu(u_cqe->v0->dqn5_byte_count) & 0x3FFF;
    *dqn_p = (u_cqe->v0->e_sr_dqn_owner >> 1) & SX_CQE_DQN_MASK;
    if (be16_to_cpu(u_cqe->v0->dqn5_byte_count) & SX_CQE_DQN_MSB_MASK) {
        *dqn_p |= (1 << SX_CQE_DQN_MSB_SHIFT);
    }
    *crc_present_p = u_cqe->v0->type_swid & 0x1;
}

void sx_fill_params_from_cqe_v2(union sx_cqe *u_cqe,
                                u16          *hw_synd_p,
                                u8           *is_isx_p,
                                u16          *byte_count_p,
                                u8           *dqn_p,
                                u8           *crc_present_p)
{
    *hw_synd_p = be16_to_cpu(u_cqe->v2->sma_check_id_trap_id) & 0x3FF;
    *is_isx_p = be16_to_cpu(u_cqe->v2->isx_ulp_crc_byte_count) >> 15;
    *byte_count_p = be16_to_cpu(u_cqe->v2->isx_ulp_crc_byte_count) & 0x3FFF;
    *dqn_p = (u_cqe->v2->dqn >> 1) & 0x3F;
    *crc_present_p = (u_cqe->v2->type_swid_crc >> 1) & 0x1;
}

static u16 get_truncate_size_from_db(struct sx_dev *dev, int dqn)
{
    u16           ret = 0;
    unsigned long flags;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    ret = sx_priv(dev)->truncate_size_db[dqn];
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    return ret;
}

/* Returns 1 if the port/lag id is found in the trap filter DB and the packet should be dropped */
static u8 check_trap_port_in_filter_db(struct sx_dev *dev, u16 hw_synd, u8 is_lag, u16 sysport_lag_id)
{
    struct sx_priv *priv = sx_priv(dev);
    int             i;
    u8              ret = 0;
    unsigned long   flags;

    if (is_lag) {
        spin_lock_irqsave(&priv->db_lock, flags);
        for (i = 0; i < MAX_LAG_PORTS_IN_FILTER; i++) {
            if (priv->lag_filter_db[hw_synd][i] == sysport_lag_id) {
                inc_filtered_lag_packets_counter(priv);
                ret = 1;
                break;
            }
        }

        spin_unlock_irqrestore(&priv->db_lock, flags);
        return ret;
    }

    /* EMADs can be received with sysport==0 */
    if (sysport_lag_id == 0) {
        return 0;
    }

    spin_lock_irqsave(&priv->db_lock, flags);
    for (i = 0; i < MAX_SYSTEM_PORTS_IN_FILTER; i++) {
        if (priv->sysport_filter_db[hw_synd][i] == sysport_lag_id) {
            inc_filtered_port_packets_counter(priv);
            ret = 1;
            break;
        }
    }

    spin_unlock_irqrestore(&priv->db_lock, flags);
    return ret;
}

static void sx_cpu_port_loopback(struct completion_info *ci)
{
    struct isx_meta meta;
    struct sk_buff *skb = ci->skb;
    struct sk_buff *tmp_skb = NULL;
    struct sx_priv *priv = sx_priv(ci->dev);
    int             len = 0;
    int             err = 0;

    /*
     * check if called from tasklet context drop the packet
     */
    if (in_softirq()) {
        err = -EINVAL;
        goto out;
    }

    memset(&meta, 0, sizeof(meta));
    meta.dev_id = 1;
    meta.type = SX_PKT_TYPE_ETH_CTL_UC;

    /* No LAG support */
    meta.system_port_mid = ci->sysport;

    len = skb->len;
    tmp_skb = alloc_skb(ISX_HDR_SIZE + len, GFP_KERNEL);
    if (!tmp_skb) {
        printk(KERN_INFO PFX "%s: fail to alloc_skb\n", __func__);
        err = -ENOMEM;
        goto out;
    }

    skb_reserve(tmp_skb, ISX_HDR_SIZE);
    memcpy(skb_put(tmp_skb, len), skb->data, len);

    err = sx_core_post_send(ci->dev, tmp_skb, &meta);
    if (err) {
        printk(KERN_INFO PFX "%s: sx_core_post_send FAILED\n", __func__);
        goto out;
    }

    priv->stats.tx_loopback_ok_by_synd[ci->hw_synd]++;

out:

    if (err) {
        priv->stats.tx_loopback_dropped_by_synd[ci->hw_synd]++;
    }

    /* Free memory */
    sx_skb_free(skb);
    kfree(ci);
}

static void sx_handle_ppbme_event(struct completion_info *ci)
{
    struct sxd_emad_ppbme_reg* ppbme = (struct sxd_emad_ppbme_reg *)ci->skb->data;
    struct sx_emad            *emad_header = &ppbme->emad_header;
    int                        reg_id = be16_to_cpu(emad_header->emad_op.register_id);
    unsigned short             type_len, ethertype;

    type_len = ntohs(ppbme->tlv_header.type_len);
    ethertype = ntohs(ppbme->emad_header.eth_hdr.ethertype);

    /* Sanity checks */
    if ((ethertype != ETHTYPE_EMAD) || (reg_id != PPMBE_REG_ID) ||
        ((type_len >> EMAD_TLV_TYPE_SHIFT) != TLV_TYPE_REG_E) ||
        ((type_len & 0x7FF) != 4)) {
        printk(KERN_ERR PFX "%s: Called wrongly with ethertype = %04X and reg-id = %04X, type = %d, len = %d\n",
               __func__, ci->info.eth.ethtype, reg_id,
               type_len >> EMAD_TLV_TYPE_SHIFT, type_len & 0x7FF);
        return;
    }

    sx_core_ber_monitor_handle_ppbme_event(ci);
}

static void sx_handle_sbctr_event(struct completion_info *ci)
{
    struct sxd_emad_sbctr_reg* sbctr = (struct sxd_emad_sbctr_reg *)ci->skb->data;
    struct sx_emad            *emad_header = &sbctr->emad_header;
    int                        reg_id = be16_to_cpu(emad_header->emad_op.register_id);
    unsigned short             type_len, ethertype;
    u64                        old_tc_vec = 0, tc_vec = 0, new_tc_vec = 0;
    u8                         entity = 0, fp = 0, maybe_flag = 0, port_state = 0;
    u8                         dir_ing = 0;
    u16                        local_port = 0;
    struct sx_priv            *priv = sx_priv((struct sx_dev *)ci->dev);
    unsigned long              flags;

    type_len = ntohs(sbctr->tlv_header.type_len);
    ethertype = ntohs(sbctr->emad_header.eth_hdr.ethertype);

    /* Sanity checks */
    if ((ethertype != ETHTYPE_EMAD) || (reg_id != SBCTR_REG_ID) ||
        ((type_len >> EMAD_TLV_TYPE_SHIFT) != TLV_TYPE_REG_E) ||
        ((type_len & 0x7FF) != 4)) {
        printk(KERN_ERR PFX "%s: Called wrongly with ethertype = %04X and reg-id = %04X, type = %d, len = %d\n",
               __func__, ci->info.eth.ethtype, reg_id,
               type_len >> EMAD_TLV_TYPE_SHIFT, type_len & 0x7FF);
        return;
    }

    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port,
                                      sbctr->local_port,
                                      ((sbctr->lp_msb_and_dir_ing >> 4) & 0x3));

    if (local_port > MAX_PHYPORT_NUM) {
        printk(KERN_ERR PFX "Received local_port %d is invalid (max. %d) \n",
               sbctr->local_port, MAX_PHYPORT_NUM);
        return;
    }
    dir_ing = sbctr->lp_msb_and_dir_ing & 0x1;
    entity = sbctr->fp_entity & 0x3;
    fp = (sbctr->fp_entity >> 4) & 0x1;
    tc_vec = be64_to_cpu(sbctr->tc_vec);

    spin_lock_irqsave(&priv->db_lock, flags);
    if (entity == 0) { /* entity is port tc */
        /* Update DB only upon port_tc event */
        old_tc_vec = priv->tele_thrs_tc_vec[local_port][dir_ing];
        priv->tele_thrs_tc_vec[local_port][dir_ing] = tc_vec;
        port_state = priv->tele_thrs_state[local_port][dir_ing];

        if (tc_vec == old_tc_vec) {
            /* No change in tc_vec state */
            if (tc_vec != 0) {
                /* If port is congested: drop event */
                ci->info.dont_care.drop_enable = 1;
            } else {
                /* No congestion - keep event in those cases:
                 * 1. This is the first event on port
                 * 2. Previous event was "port maybe congested" event */
                if ((SX_TELE_THRS_MAYBE_GET(port_state) == 1) || (SX_TELE_THRS_FIRST_EVENT_GET(port_state) == 0)) {
                    ci->info.dont_care.drop_enable = 0;
                } else {
                    ci->info.dont_care.drop_enable = 1;
                }
            }
        } else {
            /* Set new tc_vec:
             * High 32 bits marks the changed TCs
             * Low 32 bits keeps TCs value
             * Valid bits [0..15] */
            new_tc_vec = ((old_tc_vec ^ tc_vec) << 32) | (tc_vec & 0xFFFF);

            /* re-write the event */
            sbctr->tc_vec = cpu_to_be64(new_tc_vec);
        }
    } else if ((entity == 1) && (fp == 1)) {
        /* Port maybe congested event */
        maybe_flag = 1;
    }

    /* Update port state field */
    if (maybe_flag) {
        SX_TELE_THRS_MAYBE_SET(priv->tele_thrs_state[local_port][dir_ing]);
    } else {
        SX_TELE_THRS_MAYBE_CLR(priv->tele_thrs_state[local_port][dir_ing]);
    }
    SX_TELE_THRS_FIRST_EVENT_SET(priv->tele_thrs_state[local_port][dir_ing]);
    spin_unlock_irqrestore(&priv->db_lock, flags);
}
static void sx_handle_fshe_event(struct completion_info *ci)
{
    struct ku_fshe_reg fshe_reg;
    int                err;
    u8               * fshe_outbox = (u8*)ci->skb->data + sizeof(struct sx_emad) +
                                     sizeof(struct sxd_emad_tlv_reg);

    err = __FSHE_decode(fshe_outbox, &fshe_reg, NULL);
    if (err) {
        printk(KERN_ERR "__FSHE_decode returned with error %d\n", err);
        return;
    }
    sx_health_check_fshe_error_update(ci->dev);
}

static void sx_handle_meccc_event(struct completion_info *ci)
{
    struct ku_meccc_reg meccc_reg;
    int                 err;
    u8                * meccc_outbox = (u8*)ci->skb->data + sizeof(struct sx_emad) +
                                       sizeof(struct sxd_emad_tlv_reg);

    err = __MECCC_decode(meccc_outbox, &meccc_reg, NULL);
    if (err) {
        printk(KERN_ERR "__MECCC_decode returned with error %d\n", err);
        return;
    }
    sx_health_check_meccc_error_update(&meccc_reg, ci->dev);
}

static void sx_handle_mfde_event(struct completion_info *ci)
{
    struct ku_mfde_reg mfde_reg;
    int                err;
    u8               * mfde_outbox = (u8*)ci->skb->data + sizeof(struct sx_emad) +
                                     sizeof(struct sxd_emad_tlv_reg);

    err = __MFDE_decode(mfde_outbox, &mfde_reg, NULL);
    if (err) {
        printk(KERN_ERR "__MFDE_decode returned with error %d\n", err);
        return;
    }
    sx_health_check_mfde_error_update(&mfde_reg, ci->dev);
}

static void sx_parse_event(struct completion_info *ci)
{
    ci->info.dont_care.drop_enable = 0;

    switch (ci->hw_synd) {
    case SXD_TRAP_ID_PPCNT:
        sx_bulk_cntr_handle_ppcnt(ci);
        break;

    case SXD_TRAP_ID_MGPCB:
        sx_bulk_cntr_handle_mgpcb(ci);
        break;

    case SXD_TRAP_ID_MOFRB:
        sx_bulk_cntr_handle_mofrb(ci);
        break;

    case SXD_TRAP_ID_PBSR:
        sx_bulk_cntr_handle_pbsr(ci);
        break;

    case SXD_TRAP_ID_SBSRD:
        sx_bulk_cntr_handle_sbsrd(ci);
        break;

    case SXD_TRAP_ID_CEER:
        sx_bulk_cntr_handle_ceer(ci);
        break;

    case SXD_TRAP_ID_MOCS_DONE:
        sx_bulk_cntr_handle_mocs_done(ci);
        break;

    case SXD_TRAP_ID_PPBME:
        sx_handle_ppbme_event(ci);
        break;

    case SXD_TRAP_ID_SB_CONG_TX_PORT:
        sx_handle_sbctr_event(ci);
        break;

    case SXD_TRAP_ID_MAFBI:
    /* fall-through */
    case SXD_TRAP_ID_MAFRI:
    /* fall-through */
    case SXD_TRAP_ID_ACCU_FLOW_INC:
        sx_af_counters_event_job_schedule(ci);
        break;

    case SXD_TRAP_ID_MTPPST:
        sx_core_ptp_handle_mtppst_event(ci);
        break;

    case SXD_TRAP_ID_FSED:
        sx_bulk_cntr_handle_fsed(ci);
        break;

    case SXD_TRAP_ID_MFDE:
        sx_handle_mfde_event(ci);
        break;

    case SXD_TRAP_ID_FSHE:
        sx_handle_fshe_event(ci);
        break;

    case SXD_TRAP_ID_MECCC:
        sx_handle_meccc_event(ci);
        break;

    case SXD_TRAP_ID_UTCC:
        sx_bulk_cntr_handle_utcc(ci);
        break;

    case SXD_TRAP_ID_UPCNT:
        sx_bulk_cntr_handle_upcnt(ci);
        break;

    case SXD_TRAP_ID_USACN:
        sx_bulk_cntr_handle_usacn(ci);
        break;

    default:
        break;
    }
}

static u16 get_vid_from_db(struct sx_dev *dev, u8 is_lag, u16 sysport_lag_id)
{
    u16           ret = 1;
    unsigned long flags;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (is_lag) {
        ret = sx_priv(dev)->pvid_lag_db[sysport_lag_id];
    } else {
        ret = sx_priv(dev)->pvid_sysport_db[sysport_lag_id];
    }

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    return ret;
}

static u32 get_qpn(u16 hw_synd, struct sk_buff *skb)
{
    u8  lnh = 0;
    u32 qpn;

    lnh = ((struct ib_header_lrh *)skb->data)->sl_lnh & 0x3;
    if (lnh == 3) {
        qpn = be32_to_cpu(((struct ib_header_multicast *)
                           skb->data)->bth.dest_qp) & 0xffffff;
    } else if (lnh == 2) {
        qpn = be32_to_cpu(((struct ib_header_unicast *)
                           skb->data)->bth.dest_qp) & 0xffffff;
    } else {
        qpn = 0xffffffff;
    }

    return qpn;
}


static int listener_register_filter_entry_match_dispatch(struct completion_info                *ci,
                                                         struct listener_register_filter_entry *listener_register_filter)
{
    if ((listener_register_filter->is_global_filter) ||
        PORT_VLAN_BIT_IS_SET(listener_register_filter->ports_filters, ci->sysport) ||
        ((ci->is_lag) && PORT_VLAN_BIT_IS_SET(listener_register_filter->lags_filters, ci->sysport)) ||
        (PORT_VLAN_BIT_IS_SET(listener_register_filter->vlans_filters, ci->vid))) {
        return 0;
    }
    if ((listener_register_filter->is_global_register) ||
        (PORT_VLAN_BIT_IS_SET(listener_register_filter->ports_registers, ci->sysport) ||
         ((ci->is_lag) && PORT_VLAN_BIT_IS_SET(listener_register_filter->lags_registers, ci->sysport)) ||
         (PORT_VLAN_BIT_IS_SET(listener_register_filter->vlans_registers, ci->vid)))) {
        return 1;
    }
    return 0;
}

static int is_matching(struct completion_info *ci, struct listener_entry *listener)
{
    if ((listener->swid != ci->swid) &&
        (listener->swid != SWID_NUM_DONT_CARE)) {
        return 0;
    }
    /* If the packet came from a user (loopback), don't return it to the same user */
    if ((ci->context != NULL) && (listener->context == ci->context)) {
        return 0;
    }

    /* in case we want to send the trap to a certain process, other processes won't get it */
    if ((ci->target_pid != TARGET_PID_DONT_CARE) && (listener->pid != ci->target_pid)) {
        return 0;
    }

    switch (listener->listener_type) {
    case L2_TYPE_DONT_CARE:
        if (listener->critireas.dont_care.drop_enable && ci->info.dont_care.drop_enable) {
            break;
        }
        return 1;

    case L2_TYPE_ETH:
        if ((ci->pkt_type != PKT_TYPE_ETH) &&
            (ci->pkt_type != PKT_TYPE_FCoETH)) {
            break;
        }

        if ((ci->info.eth.ethtype != listener->critireas.eth.ethtype) &&
            (listener->critireas.eth.ethtype !=
             ETHTYPE_DONT_CARE_VALUE)) {
            break;
        }

        if ((ci->info.eth.dmac != listener->critireas.eth.dmac)
            && (listener->critireas.eth.dmac !=
                DMAC_DONT_CARE_VALUE)) {
            break;
        }

        if ((listener->critireas.eth.emad_tid != TID_DONT_CARE_VALUE) &&
            (ci->info.eth.emad_tid !=
             listener->critireas.eth.emad_tid)) {
            break;
        }

        if ((listener->critireas.eth.from_rp != IS_RP_DONT_CARE_E) &&
            (ci->info.eth.from_rp != listener->critireas.eth.from_rp)) {
            break;
        }

        if ((listener->critireas.eth.from_bridge != IS_BRIDGE_DONT_CARE_E) &&
            (ci->info.eth.from_bridge != listener->critireas.eth.from_bridge)) {
            break;
        }
        return 1;

    case L2_TYPE_IB:
        if ((ci->pkt_type == PKT_TYPE_IB_Raw) ||
            (ci->pkt_type == PKT_TYPE_IB_non_Raw) ||
            (ci->pkt_type == PKT_TYPE_FCoIB) ||
            (ci->pkt_type == PKT_TYPE_ETHoIB)) {
            if ((ci->info.ib.is_oob_originated_mad != listener->critireas.ib.is_oob_originated_mad) &&
                (listener->critireas.ib.is_oob_originated_mad != 255) /* don't care */) {
                break;
            }
            if ((ci->info.ib.qpn == listener->critireas.ib.qpn) ||
                (listener->critireas.ib.qpn == QPN_DONT_CARE_VALUE)) {
                return 1;
            }
        }
        break;

    default:
        break;
    }

    return 0;
}

/*
 * filter the listeners table, and call all relevant handlers
 */
int dispatch_pkt(struct sx_dev *dev, struct completion_info *ci, u16 entry, int dispatch_default)
{
    struct sx_priv               *priv = sx_priv(dev);
    struct listeners_and_rf_info *info = NULL;
    struct listener_entry        *listener;
    cq_handler                    listener_handler;    /*The completion handler*/
    void                         *listener_context;    /*to pass to the handler*/
    int                           num_found = 0;
    u8                            is_default;

    /* validate the syndrome range */
    if (entry > NUM_HW_SYNDROMES) {
        printk(KERN_ERR PFX "Error: arrived synd %d is out of range (1..%d) \n",
               entry, NUM_HW_SYNDROMES);
        return -1;
    }

    info = priv->listeners_and_rf_db.info;

    if (!info) {
        goto out;
    }

    rcu_read_lock();

    /* Checking syndrome registration and NUM_HW_SYNDROMES callback iff dispatch_default set */
    /* I don't like the syndrome dispatchers at all, but it's too late to change */
    while (1) {
        list_for_each_entry_rcu(listener, &info->per_synd_list[entry], list) {
            if (listener->is_default && (num_found == 0)) {
                is_default = 1;
            } else {
                is_default = 0;
            }
            if (listener_register_filter_entry_match_dispatch(ci, &(listener->listener_register_filter))) {
                if (is_default || is_matching(ci, listener)) {
                    listener_handler = listener->handler;
                    listener_context = listener->context;
                    listener_handler(ci, listener_context);
                    listener->rx_pkts++;
                    ++num_found;
                }
            }
        }

        if (!dispatch_default || (entry == NUM_HW_SYNDROMES)) {
            break;
        }
        entry = NUM_HW_SYNDROMES;
    }

    rcu_read_unlock();

    if (num_found == 0) {
        inc_unconsumed_packets_counter(priv, ci->hw_synd, ci->pkt_type);
    }

out:
    return num_found;
}


static int chk_completion_info(struct completion_info *ci)
{
    int err = 0;

    if ((ci->swid >= NUMBER_OF_SWIDS) && (ci->swid != SWID_NUM_DONT_CARE)) {
        err = -EINVAL;
#ifdef SX_DEBUG
        if (printk_ratelimit()) {
            pr_debug(PFX "The given cqe is not valid: " \
                     " swid=[%d]\n", ci->swid);
        }
#endif
    }

    if (ci->hw_synd > NUM_HW_SYNDROMES) {
        err = -EINVAL;
#ifdef SX_DEBUG
        if (printk_ratelimit()) {
            pr_debug(PFX "The given cqe is not valid: " \
                     "hw_synd=[%d]\n", ci->hw_synd);
        }
#endif
    }

    return err;
}


#ifdef SW_PUDE_EMULATION
/* PUDE WA for NOS (PUDE events are handled by SDK). Needed for BU. */
static int __verify_hw_synd(struct sx_priv *priv, struct completion_info *ci)
{
    int                       err = 0;
    struct sxd_emad_pude_reg* pude = NULL;

    if (!priv || !ci) {
        err = -EINVAL;
        goto out;
    }

    if (ci->hw_synd == SXD_TRAP_ID_PUDE) {
        pude = (struct sxd_emad_pude_reg *)ci->skb->data;

        if ((pude->oper_status == PORT_OPER_STATUS_UP) &&
            (priv->admin_status_sysport_db[pude->local_port] == 0x2)) { /* SXD_PORT_ADMIN_STATUS_DOWN_BY_CONF = 0x2 */
            pr_debug(PFX "Skipping PUDE [%d] event for port [%d] - admin status: %d \n",
                     pude->oper_status,
                     pude->local_port,
                     priv->admin_status_sysport_db[pude->local_port]);
            err = -EBADMSG;
            goto out;
        }
    }

out:
    return err;
}
#endif /* SW_PUDE_EMULATION */

/*
 * extracts the needed data from the cqe and from the packet, calls
 * the filter listeners with that info
 */
int rx_skb(void                         *context,
           struct sk_buff               *skb,
           union sx_cqe                 *u_cqe,
           const struct sx_rx_timestamp *rx_timestamp,
           int                           is_from_monitor_rdq,
           struct listener_entry       * force_listener,
           u8                            dev_id)
{
    struct completion_info *ci = NULL;
    struct sx_priv         *priv = sx_priv((struct sx_dev *)context);
    u16                     hw_synd = 0;
    int                     err = 0;
    u8                      dqn = 0, cqn = 0;
    u16                     truncate_size = 0;
    u8                      crc_present = 0;
    u8                      remove_crc = 0;
    struct sx_dev         * sx_device = (struct sx_dev *)context;
    u8                      swid = 0;
    u8                      is_from_rp = IS_RP_DONT_CARE_E;
    u16                     fid = 0;
    u8                      is_isx = 0;
    u16                     byte_count = 0;
    u16                     mad_attr_id;

#ifdef SX_DEBUG
    pr_debug(PFX "rx_skb: Entered function\n");

    priv->dev_specific_cb.sx_printk_cqe_cb(u_cqe);
#endif

    ci = kzalloc(sizeof(*ci), GFP_ATOMIC);
    if (!ci) {
        err = -ENOMEM;
        goto out_free_skb;
    }

    err = __sx_core_dev_specific_cb_get_reference(sx_device);
    if (err) {
        err = -ENOMEM;
        goto out;
    }

    /* Get trap_id, is_isx, byte_count, dqn, vlan, crc_present */
    priv->dev_specific_cb.sx_fill_params_from_cqe_cb(u_cqe,
                                                     &hw_synd,
                                                     &is_isx,
                                                     &byte_count,
                                                     &dqn,
                                                     &crc_present);

    __sx_core_dev_specific_cb_release_reference(sx_device);

    if (hw_synd == HETT_TRAP_ID) {
        goto out; /*if is HETT trap we do not want to count it*/
    }

    remove_crc = (crc_present && !enable_keep_packet_crc);
    cqn = dqn + NUMBER_OF_SDQS;

    /* update skb->len to the real len,
     * instead of the max len we allocated */
    skb->len = byte_count;

    if (is_isx) {
        skb->data += ISX_HDR_SIZE;
        skb->len -= ISX_HDR_SIZE;
#ifdef SX_DEBUG
        pr_debug(PFX "Got a packet with ISX header\n");
#endif
    }

    ci->skb = skb;
    ci->context = NULL;
    ci->dev = sx_device;
    ci->hw_synd = hw_synd;
    ci->device_id = dev_id;

#ifdef SW_PUDE_EMULATION
    /* PUDE WA for NOS (PUDE events are handled by SDK). Needed for BU. */
    if (__verify_hw_synd(priv, ci) != 0) {
        goto out;
    }
#endif /* SW_PUDE_EMULATION */

    err = __sx_core_dev_specific_cb_get_reference(sx_device);
    if (err) {
        err = -EINVAL;
        goto out;
    }

    priv->dev_specific_cb.sx_fill_ci_from_cqe_cb(ci, u_cqe);

    __sx_core_dev_specific_cb_release_reference(sx_device);

    /* If packet arrived from external port then ci->sysport != 0 or is_lag != 0 */
    if ((ci->sysport != 0) || (ci->is_lag != 0)) {
        err = sx_core_get_swid(sx_device, ci, &swid);
        if (err) {
            err = -EINVAL;
            goto out;
        }

        if (swid == 255) { /* port is in migration between 2 swids */
            if (rx_debug) {
                printk(KERN_ERR "port (sysport=%u, is_lag=%u) is temporarily disabled! dropping packet!\n",
                       ci->sysport, ci->is_lag);
            }

            err = -EINVAL;
            goto out;
        }

#ifdef SX_DEBUG
        pr_debug(PFX "rx_skb() pkt_type:%d, hw_synd:%d is_lag:%d, sysport:0x%x, "
                 "old_swid:%d, new_swid: %d\n", ci->pkt_type, ci->hw_synd, ci->is_lag,
                 ci->sysport, ci->swid, swid);
#endif

        ci->swid = swid;
    } else if ((ci->swid < NUMBER_OF_SWIDS) &&
               (priv->profile.pci_profile.swid_type[ci->swid] == SX_KU_L2_TYPE_ROUTER_PORT)) {
        /* if event arrived from Router Port Swid forward it to swid 0 (Default ETH swid) */
        ci->swid = 0;
    }

    SX_RX_TIMESTAMP_COPY(&ci->rx_timestamp, rx_timestamp);

    sx_core_skb_hook_rx_call(sx_device, skb);

    if (rx_debug &&
        ((rx_debug_pkt_type == SX_DBG_PACKET_TYPE_ANY) ||
         (rx_debug_pkt_type == ci->hw_synd)) &&
        ((rx_debug_emad_type == SX_DBG_EMAD_TYPE_ANY) ||
         (rx_debug_emad_type ==
          be16_to_cpu(((struct sx_emad *)skb->data)->emad_op.register_id)))) {
        if (rx_cqev2_dbg) {
            if (__sx_core_dev_specific_cb_get_reference(sx_device) == 0) {
                priv->dev_specific_cb.sx_printk_cqe_cb(u_cqe);
                __sx_core_dev_specific_cb_release_reference(sx_device);
            }
        }

        pr_debug(PFX "rx_skb: swid = %d, "
                 "sysport = %d, hw_synd = %d (reg_id: 0x%x),"
                 "pkt_type = %d, byte_count = %d, is_lag: %d, src lag_subport: %d\n",
                 ci->swid, ci->sysport, ci->hw_synd,
                 be16_to_cpu(((struct sx_emad *)skb->data)->emad_op.register_id),
                 ci->pkt_type, skb->len, ci->is_lag, ci->lag_subport);
        pr_debug(PFX "rx_skb: dest sysport:%#x, dest is_lag:%d, dest lag_subport:%d user_def_val:%#08x\n",
                 ci->dest_sysport, ci->dest_is_lag, ci->dest_lag_subport, ci->user_def_val);
        pr_debug(PFX "rx_skb: mirror_tclass:%d, mirror_cong:%d, mirror_latency:%d \n",
                 ci->mirror_tclass, ci->mirror_cong, ci->mirror_lantency);

        if (rx_dump) {
            int i;
            u8 *buf = (void*)skb->data;
            int cnt = skb->len;

            for (i = 0; i < cnt; i++) {
                if ((i == 0) || (i % 4 == 0)) {
                    printk(KERN_INFO "\n0x%04x : ", i);
                }

                printk(KERN_INFO " 0x%02x", buf[i]);
            }

            printk(KERN_INFO "\n");
        }

        if ((rx_dump_cnt != SX_DBG_COUNT_UNLIMITED) && (rx_dump_cnt > 0)) {
            rx_dump_cnt--;
        }

        if (rx_dump_cnt == 0) {
            rx_dump = 0;
            rx_debug = 0;
            rx_debug_pkt_type = 0xFF;
        }
    }

    if (ci->swid < NUMBER_OF_SWIDS) {
        priv->stats.rx_by_pkt_type[ci->swid][ci->pkt_type]++;
        priv->stats.rx_by_synd[ci->swid][ci->hw_synd]++;
        priv->stats.rx_by_synd_bytes[ci->swid][ci->hw_synd] += skb->len;
        priv->stats.rx_by_rdq[ci->swid][dqn]++;
        priv->stats.rx_by_rdq_bytes[ci->swid][dqn] += skb->len;
    } else {
        priv->stats.rx_by_pkt_type[NUMBER_OF_SWIDS][ci->pkt_type]++;
        priv->stats.rx_by_synd[NUMBER_OF_SWIDS][ci->hw_synd]++;
        priv->stats.rx_by_synd_bytes[NUMBER_OF_SWIDS][ci->hw_synd] += skb->len;
        priv->stats.rx_by_rdq[NUMBER_OF_SWIDS][dqn]++;
        priv->stats.rx_by_rdq_bytes[NUMBER_OF_SWIDS][dqn] += skb->len;
    }

    if (enable_cpu_port_loopback) { /* it's a DEBUG feature */
        if (((ci->sysport != 0) || (ci->is_lag != 0)) && !is_from_monitor_rdq) {
            /*put the original packet size before truncation in the completion info*/
            ci->original_packet_size = skb->len;

            truncate_size = get_truncate_size_from_db((struct sx_dev *)context, dqn);
            if ((truncate_size > 0) && (truncate_size < skb->len)) {
                skb->len = truncate_size;
            }

            if (remove_crc) {
                ci->original_packet_size -= ETH_CRC_LENGTH;

                if (!truncate_size) {
                    skb->len -= ETH_CRC_LENGTH;
                }
            }

            sx_cpu_port_loopback(ci);
            return err;
        }
    }

    /* Check if the port/lag is in the traps filter DB. If so we silently drop the packet */
    if (check_trap_port_in_filter_db((struct sx_dev *)context, ci->hw_synd,
                                     ci->is_lag, ci->sysport) && !is_from_monitor_rdq) {
        goto out;
    }

    /*put the original packet size before truncation in the completion info*/
    ci->original_packet_size = skb->len;

    truncate_size = get_truncate_size_from_db((struct sx_dev *)context, dqn);
    if ((truncate_size > 0) && (truncate_size < skb->len)) {
        skb->len = truncate_size;
    }

    /* Some events need to be silently drop in driver */
    sx_parse_event(ci);

    switch (ci->pkt_type) {
    case PKT_TYPE_ETH:
    case PKT_TYPE_FCoETH:
        ci->info.eth.ethtype = be16_to_cpu(((struct sx_eth_hdr *)
                                            skb->data)->ethertype);
        ci->info.eth.dmac = be64_to_cpu(((struct sx_eth_hdr *)
                                         skb->data)->dmac_smac1) >> 16;
        if (ci->info.eth.ethtype == ETHTYPE_EMAD) {
            ci->info.eth.emad_tid = be64_to_cpu(((struct sx_emad *)
                                                 skb->data)->emad_op.tid) >> 32;
            /* Tid that configure via HEALTH CHECK SDQ monitor process */
            if (ci->info.eth.emad_tid == 0xffffffff) {
                pr_debug(PFX "emad_tid =  0x%x HEALTH CHECK packet via "
                         "SDQ monitor received\n", ci->info.eth.emad_tid);
                goto out;
            }
        } else if (ci->info.eth.ethtype == ETHTYPE_VLAN) {
            ci->is_tagged = VLAN_TAGGED_E;
            ci->vid = be16_to_cpu(((struct vlan_ethhdr*)skb->data)->h_vlan_TCI) & 0xfff;
            if (ci->vid == 0) { /* VLAN header with tag 0 ==> we should use pvid instead */
                ci->is_tagged = VLAN_PRIO_TAGGED_E;
                ci->vid = get_vid_from_db((struct sx_dev*)context, ci->is_lag, ci->sysport);
            }
        } else {
            ci->is_tagged = VLAN_UNTAGGED_E;
            ci->vid = get_vid_from_db((struct sx_dev *)context,
                                      ci->is_lag, ci->sysport);
        }
        if (remove_crc) {
            ci->original_packet_size -= ETH_CRC_LENGTH;
        }
        if (remove_crc && !truncate_size) {
            skb->len -= ETH_CRC_LENGTH;
        }

        /*
         *  - if sysport is 0 and is_lag is 0 that the packet is FW event,
         *     and we don't need to check if from RP / bridge
         *  - For monitor RDQ don't check if arrived from RP or Bridge
         *    The packet should only arrive to Monitor FD
         */
        if (((ci->sysport != 0) || (ci->is_lag != 0)) && !is_from_monitor_rdq) {
            err = sx_core_get_rp_mode((struct sx_dev *)context,
                                      ci->is_lag, ci->sysport, ci->vid,
                                      &is_from_rp);
            if (err) {
                printk(KERN_ERR PFX "Failed sx_core_get_rp_mode(). err: %d \n", err);
            }
            ci->info.eth.from_rp = (is_from_rp) ? IS_RP_FROM_RP_E : IS_RP_NOT_FROM_RP_E;

            err = sx_core_get_fid_by_port_vid((struct sx_dev *)context, ci, &fid);
            if (err) {
                printk(KERN_ERR PFX "Failed sx_core_get_bridge(). err: %d \n", err);
            }
            ci->bridge_id = fid;
            ci->info.eth.from_bridge = (fid) ?
                                       IS_BRIDGE_FROM_BRIDGE_E : IS_BRIDGE_NOT_FROM_BRIDGE_E;
        }
        break;

    case PKT_TYPE_IB_non_Raw:
    case PKT_TYPE_FCoIB:
    case PKT_TYPE_ETHoIB:
        ci->info.ib.qpn = get_qpn(hw_synd, skb);
        if (ci->info.ib.qpn == 0xffffffff) {
            if (printk_ratelimit()) {
                printk(KERN_WARNING PFX "Received IB packet "
                       "is not valid. Dropping the packet\n");
            }
            err = -EINVAL;
            goto out;
        }
        FALL_THROUGH;

    /* fall-through */
    case PKT_TYPE_IB_Raw:
        if (is_sgmii_supported()) {
            err = sgmii_get_mad_header_info(skb->data,
                                            skb->len,
                                            NULL,
                                            &ci->info.ib.mad_tid,
                                            &mad_attr_id);
            if (!err) {
                ci->info.ib.is_oob_originated_mad = ((ci->info.ib.mad_tid >> 32) == SGMII_TR_ID_PREFIX);
            }
        }

        /* Extract the IB port from the sysport */
        ci->sysport = (ci->sysport >> 4) & 0xfff;
        if (remove_crc && !truncate_size) {
            skb->len -= (ci->pkt_type == PKT_TYPE_IB_Raw) ? IB_VCRC_LENGTH : IB_CRC_LENGTH;
        }
        break;

    default:
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "Received packet type is FC, "
                   "and therefore unsupported right now\n");
        }
        err = -EINVAL;
        goto out;
    }

    err = chk_completion_info(ci);
    if (err) {
        err = -EINVAL;
        goto out;
    }

    if (rx_debug) {
        if (printk_ratelimit()) {
            pr_debug(PFX " rx_skb() received packet data: "
                     "skb->len=[%d] sysport=[%d] hw_synd(trap_id)=[%d] "
                     "swid=[%d] pkt_type=[%d]\n",
                     ci->skb->len, ci->sysport, ci->hw_synd,
                     ci->swid, ci->pkt_type);
        }
    }


    if (sx_ptp_is_enabled(priv) && !is_from_monitor_rdq) {
        err = sx_core_ptp_rx_handler(priv, ci, cqn);

        /* if (err != 0) it is not a real error, it just means that either it is not a PTP packet/event or
         *               it is a PTP packet that got its timestamp and should continue the packet flow as
         *               usual [dispatch_pkt(), free skb, free ci].
         * if (err == 0) it means that packet is being handled by PTP and processing is done here (only on SPC1) */
        if (!err) {
            return 0;
        }
    }

    if (force_listener == NULL) {
        dispatch_pkt((struct sx_dev *)context, ci, hw_synd, 1);
    } else {
        force_listener->handler(ci, force_listener->context);
    }

out:
    kfree(ci);
out_free_skb:
    /* don't free skb for monitor RD */
    if (!is_from_monitor_rdq) {
        sx_skb_free(skb);       /* drop packet flow, use kfree_skb */
    }

    return err;
}
EXPORT_SYMBOL(rx_skb);
static void * sx_get_cqe_from_buf(struct sx_buf *buf, int n, size_t cqe_size)
{
    int offset = n * cqe_size;

    if (buf->nbufs == 1) {
        return buf->u.direct.buf + offset;
    } else {
        return buf->u.page_list[offset >> PAGE_SHIFT].buf +
               (offset & (PAGE_SIZE - 1));
    }
}

static void * sx_get_cqe(struct sx_cq *cq, int n)
{
    return sx_get_cqe_from_buf(&cq->buf, n, cq->cqe_sizeof);
}

u8 sx_get_cqe_owner_v0(struct sx_cq *cq, int n)
{
    struct sx_cqe_v0 *cqe = sx_get_cqe(cq, n & (cq->nent - 1));

    return cqe->e_sr_dqn_owner;
}

u8 sx_get_cqe_owner_v1(struct sx_cq *cq, int n)
{
    struct sx_cqe_v1 *cqe = sx_get_cqe(cq, n & (cq->nent - 1));

    return cqe->dqn_owner;
}

u8 sx_get_cqe_owner_v2(struct sx_cq *cq, int n)
{
    struct sx_cqe_v2 *cqe = sx_get_cqe(cq, n & (cq->nent - 1));

    return cqe->pe2cqe_token_owner;
}

void sx_cqe_owner_init_v0(struct sx_cq *cq)
{
    int               i = 0;
    struct sx_cqe_v0 *cqe = NULL;

    for (i = 0; i < cq->nent; i++) {
        cqe = sx_get_cqe(cq, i);
        cqe->e_sr_dqn_owner = 1;
    }
}

void sx_cqe_owner_init_v1(struct sx_cq *cq)
{
    int               i = 0;
    struct sx_cqe_v1 *cqe = NULL;

    for (i = 0; i < cq->nent; i++) {
        cqe = sx_get_cqe(cq, i);
        cqe->dqn_owner = 1;
    }
}

void sx_cqe_owner_init_v2(struct sx_cq *cq)
{
    int               i = 0;
    struct sx_cqe_v2 *cqe = NULL;

    for (i = 0; i < cq->nent; i++) {
        cqe = sx_get_cqe(cq, i);
        cqe->pe2cqe_token_owner = 1;
    }
}

static void * sx_get_sw_cqe_v0(struct sx_cq *cq, int n)
{
    struct sx_cqe_v0 *cqe = sx_get_cqe(cq, n & (cq->nent - 1));

    return (cqe->e_sr_dqn_owner & 0x1) ^ !!(n & cq->nent) ? NULL : cqe;
}

static void * sx_get_sw_cqe_v2(struct sx_cq *cq, int n)
{
    struct sx_cqe_v2 *cqe = sx_get_cqe(cq, n & (cq->nent - 1));

    return (cqe->pe2cqe_token_owner & 0x1) ^ !!(n & cq->nent) ? NULL : cqe;
}

static void * sx_get_sw_cqe_v1(struct sx_cq *cq, int n)
{
    struct sx_cqe_v1 *cqe = sx_get_cqe(cq, n & (cq->nent - 1));

    return (cqe->dqn_owner & 0x1) ^ !!(n & cq->nent) ? NULL : cqe;
}

void sx_next_cqe_v0(struct sx_cq *cq, union sx_cqe *cqe_p)
{
    cqe_p->v0 = sx_get_sw_cqe_v0(cq, cq->cons_index);
}

void sx_next_cqe_v1(struct sx_cq *cq, union sx_cqe *cqe_p)
{
    cqe_p->v1 = sx_get_sw_cqe_v1(cq, cq->cons_index);
}

void sx_next_cqe_v2(struct sx_cq *cq, union sx_cqe *cqe_p)
{
    cqe_p->v2 = sx_get_sw_cqe_v2(cq, cq->cons_index);
}

void wqe_sync_for_cpu(struct sx_dq *dq, int idx)
{
    int dir = dq->is_send ? DMA_TO_DEVICE : DMA_FROM_DEVICE;

    dma_sync_single_for_cpu(&dq->dev->pdev->dev,
                            dq->sge[idx].hdr_pld_sg.dma_addr,
                            dq->sge[idx].hdr_pld_sg.len, dir);
    dma_unmap_single(&dq->dev->pdev->dev,
                     dq->sge[idx].hdr_pld_sg.dma_addr,
                     dq->sge[idx].hdr_pld_sg.len, dir);
    /*
     * if rdq isn't monitor than clean the field below
     * else if rdq is monitor we reuse the same buffer so shouldn't be cleaned
     */
    if (!dq->is_monitor) {
        dq->sge[idx].hdr_pld_sg.vaddr = NULL;
        dq->sge[idx].hdr_pld_sg.len = 0;
    }
    if (dq->is_send) {
        if (dq->sge[idx].pld_sg_1.len) {
            dma_sync_single_for_cpu(&dq->dev->pdev->dev,
                                    dq->sge[idx].pld_sg_1.dma_addr,
                                    dq->sge[idx].pld_sg_1.len, dir);
            dma_unmap_single(&dq->dev->pdev->dev,
                             dq->sge[idx].pld_sg_1.dma_addr,
                             dq->sge[idx].pld_sg_1.len, dir);
            dq->sge[idx].pld_sg_1.vaddr = NULL;
            dq->sge[idx].pld_sg_1.len = 0;
        }

        if (dq->sge[idx].pld_sg_2.len) {
            dma_sync_single_for_cpu(&dq->dev->pdev->dev,
                                    dq->sge[idx].pld_sg_2.dma_addr,
                                    dq->sge[idx].pld_sg_2.len, dir);
            dma_unmap_single(&dq->dev->pdev->dev,
                             dq->sge[idx].pld_sg_2.dma_addr,
                             dq->sge[idx].pld_sg_2.len, dir);
            dq->sge[idx].pld_sg_2.vaddr = NULL;
            dq->sge[idx].pld_sg_2.len = 0;
        }
    }
}

static int post_skb(struct sx_dq *dq)
{
    u16             size = sx_priv(dq->dev)->profile.pci_profile.rdq_properties[dq->dqn].entry_size;
    int             err = 0;
    struct sk_buff *new_skb;

    new_skb = alloc_skb(size, GFP_ATOMIC);
    if (!new_skb) {
        printk(KERN_ERR "failed to allocate a new buffer with size of %u for RDQ %d\n", size, dq->dqn);
        sx_health_external_report_all(SXD_HEALTH_SEVERITY_FATAL, SXD_HEALTH_CAUSE_GENERIC_E, "RDQ entry allocation");
        err = -ENOMEM;
        goto out;
    }

    if (skb_put(new_skb, size) == NULL) {
        printk(KERN_ERR "failed to set buffer size %u to a new buffer for RDQ %d\n", size, dq->dqn);
        sx_health_external_report_all(SXD_HEALTH_SEVERITY_FATAL,
                                      SXD_HEALTH_CAUSE_GENERIC_E,
                                      "RDQ entry set buffer size");
        err = -ENOMEM;
        goto out;
    }

    sx_core_post_recv(dq, new_skb);

out:
    return err;
}

void sx_fill_poll_one_params_from_cqe_v0(union sx_cqe *u_cqe, struct sx_cqe_params *cqe_params)
{
    cqe_params->dqn = (u_cqe->v0->e_sr_dqn_owner >> 1) & SX_CQE_DQN_MASK;
    if (be16_to_cpu(u_cqe->v0->dqn5_byte_count) & SX_CQE_DQN_MSB_MASK) {
        cqe_params->dqn |= (1 << SX_CQE_DQN_MSB_SHIFT);
    }
    cqe_params->is_err = !!(u_cqe->v0->e_sr_dqn_owner & SX_CQE_IS_ERR_MASK);
    cqe_params->is_send = !!(u_cqe->v0->e_sr_dqn_owner & SX_CQE_IS_SEND_MASK);
    cqe_params->wqe_counter = be16_to_cpu(u_cqe->v0->wqe_counter);
    cqe_params->trap_id = u_cqe->v0->trap_id & 0xFF;
    cqe_params->byte_count = be16_to_cpu(u_cqe->v0->dqn5_byte_count) & 0x3FFF;
    cqe_params->user_def_val_orig_pkt_len = 0;
    cqe_params->is_lag = (u_cqe->v0->lag >> 7) & 0x1;
    cqe_params->lag_subport = u_cqe->v0->vlan2_lag_subport & 0x1F;
    cqe_params->sysport_lag_id = be16_to_cpu(u_cqe->v0->system_port_lag_id);
    cqe_params->mirror_reason = 0;
    SX_RX_TIMESTAMP_INIT(&cqe_params->cqe_ts, 0, 0, SXD_TS_TYPE_NONE);
}

void sx_fill_poll_one_params_from_cqe_v1(union sx_cqe *u_cqe, struct sx_cqe_params *cqe_params)
{
    cqe_params->dqn = (u_cqe->v1->dqn_owner >> 1) & 0x3F;
    cqe_params->is_err = !!(u_cqe->v1->version_e_sr_packet_ok_rp_lag & 0x8);
    cqe_params->is_send = !!(u_cqe->v1->version_e_sr_packet_ok_rp_lag & 0x4);
    cqe_params->wqe_counter = be16_to_cpu(u_cqe->v1->wqe_counter);
    cqe_params->trap_id = be16_to_cpu(u_cqe->v1->sma_check_id_trap_id) & 0x3FF;
    cqe_params->byte_count = be16_to_cpu(u_cqe->v1->isx_ulp_crc_byte_count) & 0x3FFF;
    cqe_params->user_def_val_orig_pkt_len = 0;
    cqe_params->is_lag = u_cqe->v1->version_e_sr_packet_ok_rp_lag & 0x1;
    cqe_params->lag_subport = u_cqe->v1->rp_lag_subport & 0xFF;
    cqe_params->sysport_lag_id = be16_to_cpu(u_cqe->v1->rp_system_port_lag_id);
    cqe_params->mirror_reason = 0;
    SX_RX_TIMESTAMP_INIT(&cqe_params->cqe_ts, 0, 0, SXD_TS_TYPE_NONE);
}

void sx_fill_poll_one_params_from_cqe_v2(union sx_cqe *u_cqe, struct sx_cqe_params *cqe_params)
{
    cqe_params->dqn = (u_cqe->v2->dqn >> 1) & 0x3F;
    cqe_params->is_err = !!(u_cqe->v2->version_e_sr_packet_ok_rp_lag & 0x8);
    cqe_params->is_send = !!(u_cqe->v2->version_e_sr_packet_ok_rp_lag & 0x4);
    cqe_params->wqe_counter = be16_to_cpu(u_cqe->v2->wqe_counter);
    cqe_params->trap_id = be16_to_cpu(u_cqe->v2->sma_check_id_trap_id) & 0x3FF;
    cqe_params->byte_count = be16_to_cpu(u_cqe->v2->isx_ulp_crc_byte_count) & 0x3FFF;
    cqe_params->user_def_val_orig_pkt_len = be32_to_cpu(
        u_cqe->v2->mirror_cong1_user_def_val_orig_pkt_len) & 0xFFFFF;
    cqe_params->is_lag = u_cqe->v2->version_e_sr_packet_ok_rp_lag & 0x1;
    cqe_params->lag_subport = u_cqe->v2->rp_lag_subport & 0xFF;
    cqe_params->sysport_lag_id = be16_to_cpu(u_cqe->v2->rp_system_port_lag_id);
    cqe_params->mirror_reason = (be32_to_cpu(u_cqe->v2->mirror_reason_time_stamp_type_time_stamp2) >> 24) & 0xFF;
    cqe_params->mirror_tclass = (u_cqe->v2->mirror_tclass_mirror_elph_ep_lag >> 3) & 0x1F;
    cqe_params->mirror_cong = ((be16_to_cpu(u_cqe->v2->vlan_mirror_cong2) & 0xF) << 12) |
                              ((be32_to_cpu(u_cqe->v2->mirror_cong1_user_def_val_orig_pkt_len) & 0xFFF00000) >> 20);
    cqe_params->mirror_lantency = (be16_to_cpu(u_cqe->v2->mirror_latency2) << 8) | u_cqe->v2->mirror_latency1;
    cqe_params->dest_is_lag = u_cqe->v2->mirror_tclass_mirror_elph_ep_lag & 0x1;
    cqe_params->dest_lag_subport = u_cqe->v2->ep_lag_subport;
    cqe_params->dest_sysport_lag_id = be16_to_cpu(u_cqe->v2->ep_system_port_lag_id);
    cqe_params->cqe_ts.timestamp.tv_sec =
        (be32_to_cpu(u_cqe->v2->mirror_reason_time_stamp_type_time_stamp2) >> 14) & 0xFF;
    cqe_params->cqe_ts.timestamp.tv_nsec =
        ((be32_to_cpu(u_cqe->v2->mirror_reason_time_stamp_type_time_stamp2) & 0x3FFF) << 16) |
        be16_to_cpu(u_cqe->v2->time_stamp1);
    cqe_params->cqe_ts.ts_type = (be32_to_cpu(u_cqe->v2->mirror_reason_time_stamp_type_time_stamp2) >> 22) & 0x3;
    cqe_params->mirror_elephant = (u_cqe->v2->mirror_tclass_mirror_elph_ep_lag >> 1) & 0x3;
}


/* the purpose of this function is to fill the desired timestamp:
 * 1) if CQ is configured to work with HW timestamp and the timestamp-type is not 'None' (CQE holds
 *    a valid timestamp), get the timestamp from CQE and adjust it to real UTC (CQEv2 holds only 8bit
 *    of the seconds).
 * 2) if CQ is configured to work with Linux timestamp, use it if valid.
 * 3) On all other cases, put zero timestamp and mark timestamp-type to 'None'.
 */
void set_timestamp_of_rx_packet(struct sx_cq *cq,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                                const struct timespec64      *linux_ts,
#else
                                const struct timespec        *linux_ts,
#endif
                                const struct sx_rx_timestamp *cqe_ts, struct sx_rx_timestamp       *rx_ts)
{
    if (IS_CQ_WORKING_WITH_TIMESTAMP(cq->sx_dev, cq->cqn)) { /* CQ is configured to get RX timestamp */
        if ((cqe_ts->ts_type != SXD_TS_TYPE_NONE) && IS_CQ_WORKING_WITH_HW_TIMESTAMP(cq->sx_dev, cq->cqn)) {
            sx_core_clock_cqe_ts_to_utc(sx_priv(cq->sx_dev), &cqe_ts->timestamp, &rx_ts->timestamp);
            rx_ts->ts_type = cqe_ts->ts_type;
        } else if (linux_ts) {
            SX_RX_TIMESTAMP_INIT(rx_ts, linux_ts->tv_sec, linux_ts->tv_nsec, SXD_TS_TYPE_LINUX);
        } else { /* we should not get here but to be on the safe side ... */
            SX_RX_TIMESTAMP_INIT(rx_ts, 0, 0, SXD_TS_TYPE_NONE);
        }
    } else { /* CQ is not configured to get timestamp */
        SX_RX_TIMESTAMP_INIT(rx_ts, 0, 0, SXD_TS_TYPE_NONE);
    }
}


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
static int sx_poll_one(struct sx_cq *cq, const struct timespec64 *ts_linux)
#else
static int sx_poll_one(struct sx_cq *cq, const struct timespec *ts_linux)
#endif
{
    union sx_cqe           u_cqe = {.v0 = NULL, .v1 = NULL, .v2 = NULL};
    struct sx_dq          *dq;
    struct sk_buff        *skb;
    int                    err = 0;
    struct sx_priv        *priv = sx_priv(cq->sx_dev);
    u16                    wqe_ctr = 0;
    u16                    idx = 0;
    struct sx_cqe_params   cqe_params = {0};
    unsigned long          flags;
    uint8_t                rdq_num = 0;
    struct sx_rx_timestamp rx_timestamp;
    struct sx_pkt         *curr_pkt;
    struct list_head      *pos;
    bool                   found = false;
    u16                    rdq_max_buff_size = 0;
    u64                    now, comp_time;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
    int should_drop = 0;
#endif

    spin_lock_irqsave(&cq->lock, flags);
    cq->sx_next_cqe_cb(cq, &u_cqe);
    if (!u_cqe.v0 && !u_cqe.v1 && !u_cqe.v2) {
        spin_unlock_irqrestore(&cq->lock, flags);
        return -EAGAIN;
    }

    ++cq->cons_index;
    ++cq->cons_index_dbg;
    spin_unlock_irqrestore(&cq->lock, flags);

    /*
     * Make sure we read CQ entry contents after we've checked the
     * ownership bit.
     */
    rmb();

    cq->sx_fill_poll_one_params_from_cqe_cb(&u_cqe, &cqe_params);

    if (cqe_params.is_send) {
        if (cqe_params.dqn >= NUMBER_OF_SDQS) {
            sx_warn(cq->sx_dev, "dqn %d is larger than max SDQ %d.\n",
                    cqe_params.dqn, NUMBER_OF_SDQS);
            return 0;
        }
    } else {
        err = sx_core_get_rdq_param_max(&(priv->dev), &rdq_num, &rdq_max_buff_size);
        if (err) {
            printk(KERN_ERR PFX "Error: failed to get max RDQ params (err=%d)\n", err);
            return err;
        }

        if (cqe_params.dqn >= rdq_num) {
            sx_warn(cq->sx_dev, "dqn %d is larger than max RDQ %d.\n",
                    cqe_params.dqn, rdq_num);
            return 0;
        }
    }
    dq = cqe_params.is_send ? priv->sdq_table.dq[cqe_params.dqn] : priv->rdq_table.dq[cqe_params.dqn];

#ifdef SX_DEBUG
    pr_debug(PFX "sx_poll_one: dqn = %d, is_err = %d, "
             "is_send = %d\n", dqn, is_err, is_send);
#endif

    if (!dq) {
        if (printk_ratelimit()) {
            sx_warn(cq->sx_dev, "could not find dq context for %s "
                    "dqn = %d\n",
                    cqe_params.is_send ? "send" : "recv", cqe_params.dqn);
        }

        return 0;
    }

    wqe_ctr = cqe_params.wqe_counter & (dq->wqe_cnt - 1);
    if (cqe_params.is_err && !dq->is_flushing) {
        sx_warn(cq->sx_dev, "got %s completion with error, "
                "syndrom=0x%x\n",
                cqe_params.is_send ? "send" : "recv", cqe_params.trap_id);

        if (!cqe_params.is_send) {
            idx = dq->tail++ & (dq->wqe_cnt - 1);
            dq->last_completion = jiffies;
            wqe_sync_for_cpu(dq, idx);
            sx_skb_free(dq->sge[idx].skb);  /* drop packet flow, use kfree_skb */
            dq->sge[idx].skb = NULL;
        }

        SX_RX_TIMESTAMP_INIT(&rx_timestamp, 0, 0, SXD_TS_TYPE_NONE);
        goto skip;
    }

    if (cqe_params.is_send) {
        /*update the active SDQ's bitmap for the fatal failure detection feature */
        sx_health_check_report_dq_ok(dq->dev, true, dq->dqn);

        spin_lock_bh(&dq->lock);

        /* find the wqe and unmap the DMA buffer.
         * sx_skb_free to call  the destructor which will signal
         * the write-semaphore for ETH packets, or call gen_completion
         * for IB packets. */
        do {
            idx = dq->tail++ & (dq->wqe_cnt - 1);
            dq->last_completion = jiffies;
            wqe_sync_for_cpu(dq, idx);

            /* if it is a TX PTP packet, put the timestamp skb */
            if ((cqe_params.cqe_ts.ts_type != SXD_TS_TYPE_NONE) && /* can be true only on SPC2 and above */
                (dq->sge[idx].skb != NULL) &&
                (skb_shinfo(dq->sge[idx].skb)->tx_flags & SKBTX_IN_PROGRESS)) {
                sx_core_clock_cqe_ts_to_utc(priv, &cqe_params.cqe_ts.timestamp, &cqe_params.cqe_ts.timestamp);
                sx_core_ptp_tx_ts_handler(priv, dq->sge[idx].skb, &cqe_params.cqe_ts.timestamp);
            }

            found = false;
            list_for_each(pos, &dq->pkts_comp_list.list_wait_for_completion) {
                curr_pkt = list_entry(pos, struct sx_pkt, list_wait_for_completion);
                if (curr_pkt->idx == idx) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                printk(KERN_ERR "SDQ [%u]: completion for an unknown index (idx=%u)\n",
                       cqe_params.dqn, idx);
            } else {
                list_del(pos);
                sx_skb_consume(dq->sge[idx].skb);   /* free unused skb, use consume_skb */
                dq->sge[idx].skb = NULL;
                if (time_after(jiffies, curr_pkt->since + SX_LATE_COMPLETION_THRESHOLD)) {
                    dq->pkts_late_completion++;
                    if (printk_ratelimit()) {
                        sx_warn(cq->sx_dev, "Receive late completion for dqn (%d) idx (%d)\n",
                                cqe_params.dqn, idx);
                    }
                } else {
                    dq->pkts_recv_completion++;
                }

                now = jiffies;
                comp_time = now - curr_pkt->since;
                if (comp_time > dq->max_comp_time) {
                    dq->max_comp_time = comp_time;
                    dq->max_comp_ts = now;
                }

                kfree(curr_pkt);
            }
        } while (idx != wqe_ctr);

        if ((!priv->global_flushing) && (0 == dq->is_flushing)) {
            sx_add_pkts_to_sdq(dq);
        }

        spin_unlock_bh(&dq->lock);
    } else {
        /*update the active RDQ's bitmap for the fatal failure detection feature */
        sx_health_check_report_dq_ok(dq->dev, false, dq->dqn);
        /* get the skb from the right rdq entry, unmap the buffers
         * and call rx_skb with the cqe and skb */
        /* this while is temporary, we need it because FW doesn't
         * send us error CQes for wqe too short. */

        idx = dq->tail & (dq->wqe_cnt - 1);
        while (idx != wqe_ctr) {
            if (printk_ratelimit()) {
                pr_debug(PFX "sx_poll_one: Err wqe_ctr [%u] != idx [%u] (dq->tail [%u])\n",
                         wqe_ctr, idx, dq->tail);
            }

            dq->tail++; /* increment before sx_core_post_recv()/post_skb() */
            wqe_sync_for_cpu(dq, idx);

            if (dq->is_monitor) {
                sx_core_post_recv(dq, NULL);
            } else {
                sx_skb_free(dq->sge[idx].skb);  /* drop packet flow, use kfree_skb */
                dq->sge[idx].skb = NULL;
                post_skb(dq);
            }

            idx = dq->tail & (dq->wqe_cnt - 1);
        }

        ++dq->tail;
        wqe_sync_for_cpu(dq, idx);
#ifdef SX_DEBUG
        pr_debug(PFX "sx_poll_one: This is a RDQ, idx = %d, "
                 "wqe_ctr = %d, dq->tail = %d. "
                 "Calling rx_skb\n",
                 idx, wqe_ctr, dq->tail - 1);
#endif

        skb = dq->sge[idx].skb;

        /* Put timestamp on RX packet */
        set_timestamp_of_rx_packet(cq, ts_linux, &cqe_params.cqe_ts, &rx_timestamp);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
        if (enable_monitor_rdq_trace_points) {
            should_drop = 0;
            spin_lock_irqsave(&priv->rdq_table.lock, flags);
            if (priv->filter_ebpf_progs[cqe_params.dqn]) {
                should_drop = sx_core_call_rdq_filter_trace_point_func(cq->sx_dev,
                                                                       priv->filter_ebpf_progs[cqe_params.dqn],
                                                                       skb,
                                                                       &cqe_params,
                                                                       rdq_max_buff_size);
            }
            spin_unlock_irqrestore(&priv->rdq_table.lock, flags);
            if (should_drop != 0) {
                sx_skb_free(skb);
                dq->sge[idx].skb = NULL;
                goto skip;
            }
        }
#endif

        /*
         *   For monitor rdq we don't need to send the packet to upper layer and
         *   also not to free the packet in case of error , because the same packet
         *   will be repost_recv
         */
        if (dq->is_monitor) {
            if (enable_monitor_rdq_trace_points) {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
                spin_lock_irqsave(&priv->rdq_table.lock, flags);
                sx_core_call_rdq_agg_trace_point_func(priv,
                                                      cqe_params.dqn,
                                                      rdq_max_buff_size,
                                                      skb,
                                                      &cqe_params,
                                                      &rx_timestamp.timestamp);
                spin_unlock_irqrestore(&priv->rdq_table.lock, flags);
#endif
            }
            goto skip;
        }

        if (!cqe_params.is_err) {
            /* if packet length is less than 2K, let's reallocate it and reassign lower skb->truesize.
             * current skb->truesize is 10K and IP stack accounts for truesize and not for actual buffer size.
             */
            if (cqe_params.byte_count <= 2048) {
                struct sk_buff *new_skb;

                new_skb = skb_clone(skb, GFP_ATOMIC);
                if (new_skb) {
                    new_skb->len = cqe_params.byte_count;
                    new_skb->truesize = roundup_pow_of_two(cqe_params.byte_count);

                    sx_skb_consume(skb); /* free original 10K buffer */
                    skb = new_skb; /* use the new buffer that is much lower in size */
                }
            }

            rx_skb(cq->sx_dev, skb, &u_cqe, &rx_timestamp, 0, NULL, cq->sx_dev->device_id);
        } else {
            sx_skb_free(skb);   /* drop packet flow, use kfree_skb */
        }

        dq->sge[idx].skb = NULL;
    }
skip:
    sx_cq_set_ci(cq);

    /* when RDQ flushed all its buffers, return -ENOBUFS to tell the caller that CQ is no longer in use */
    if (dq->is_flushing && !cqe_params.is_send && (dq->head == dq->tail)) {
        err = -ENOBUFS;
        goto out;
    }

    if (!cqe_params.is_send && !dq->is_flushing) {
        if (!dq->is_monitor) {
            err = post_skb(dq);
        } else {
            if (rx_timestamp.ts_type != SXD_TS_TYPE_NONE) {
                SX_RX_TIMESTAMP_COPY(&cq->cqe_ts_arr[idx], &rx_timestamp);
            }

            /* sx_core_post_recv will re-post the same buffer for monitor rdq */
            sx_core_post_recv(dq, NULL);
        }
    }

    if (cqe_params.is_send) {
        wake_up_interruptible(&dq->tx_full_wait);
    }

out:
    return err;
}

/* return errno on error, otherwise num of handled cqes */
int sx_cq_completion(struct sx_dev *dev, u32 cqn, u16 weight,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                     const struct timespec64 *timestamp,
#else
                     const struct timespec *timestamp,
#endif
                     struct sx_bitmap      *prio_bitmap)
{
    struct sx_priv *priv = sx_priv(dev);
    struct sx_cq   *cq;
    unsigned long   flags;
    int             num_of_cqes = 0;
    int             err = 0;

    spin_lock_irqsave(&priv->cq_table.lock, flags);
    cq = (priv->cq_table.cq[cqn]);
    spin_unlock_irqrestore(&priv->cq_table.lock, flags);
    if (!cq) {
        if (!priv->global_flushing && printk_ratelimit()) {
            sx_warn(dev, "Completion event for bogus CQ %08x\n", cqn);
        }

        return -EAGAIN;
    }

    if (cq->dbg_cq_on_hold) {
        return 0;
    }

    if (!IS_CQ_WORKING_WITH_TIMESTAMP(dev, cqn)) {
        timestamp = NULL;
    }

    do {
        err = sx_poll_one(cq, timestamp);
    } while (!err && ++num_of_cqes < weight);

    /* for more details of this 'if', read the big comment in ctrl_cmd_set_monitor_rdq() */
    if ((priv->pause_cqn == cqn) || (num_of_cqes < weight)) {
        sx_bitmap_free(prio_bitmap, cqn);
        sx_cq_arm(cq);

        if (priv->pause_cqn == cqn) {
            /* make sure that the next time tasklet runs, the CQ bit in 'active_bitmap' will be off.
             * this will ensure to signal [complete()] the ioctl() command that waits for us.
             * for more details of the flow, read the big comment in ctrl_cmd_set_monitor_rdq().
             */
            tasklet_schedule(&priv->intr_tasklet);
        }
    }

    if (err == -EAGAIN) { /* -EAGAIN is the only error where the consumer index is not increased */
        atomic_inc(&cq->bkp_poll_data.curr_num_cq_polls);
        err = 0;
    } else if (err == -ENOBUFS) { /* CQ is no longer in use (its RDQ is in ERR state and flushed all its buffers) */
        __sx_cq_dec_refcnt(cq); /* this will signal sx_core_destroy_cq() that CQ can be deleted */
        err = 0;
    }

    return err ? err : num_of_cqes;
}


static int sx_SW2HW_CQ(struct sx_dev *dev, struct sx_cmd_mailbox *mailbox, int cq_num)
{
    return sx_cmd(dev, dev->device_id, mailbox, cq_num, 0, SX_CMD_SW2HW_CQ,
                  SX_CMD_TIME_CLASS_A, sx_priv(dev)->fw.local_in_mb_size);
}

static int sx_HW2SW_CQ(struct sx_dev *dev, int cq_num)
{
    return sx_cmd_box(dev, dev->device_id, 0, 0, cq_num, 0,
                      SX_CMD_HW2SW_CQ, SX_CMD_TIME_CLASS_A,
                      sx_priv(dev)->fw.local_in_mb_size);
}

void sx_init_cq_db_v0(struct sx_cq *tcq, u8 cqn, u8 *cqe_ver)
{
    tcq->cqe_version = 0;
    tcq->cqe_sizeof = sizeof(struct sx_cqe_v0);
    tcq->sx_next_cqe_cb = sx_next_cqe_v0;
    tcq->sx_fill_poll_one_params_from_cqe_cb = sx_fill_poll_one_params_from_cqe_v0;
    tcq->sx_get_cqe_owner_cb = sx_get_cqe_owner_v0;
    tcq->sx_cqe_owner_init_cb = sx_cqe_owner_init_v0;
    *cqe_ver = 0;
}

void sx_init_cq_db_spc(struct sx_cq *tcq, u8 cqn, u8 *cqe_ver)
{
    if (cqn < NUMBER_OF_SDQS) {
        tcq->cqe_version = 1;
        tcq->cqe_sizeof = sizeof(struct sx_cqe_v1);
        tcq->sx_next_cqe_cb = sx_next_cqe_v1;
        tcq->sx_fill_poll_one_params_from_cqe_cb = sx_fill_poll_one_params_from_cqe_v1;
        tcq->sx_get_cqe_owner_cb = sx_get_cqe_owner_v1;
        tcq->sx_cqe_owner_init_cb = sx_cqe_owner_init_v1;
        *cqe_ver = 0;
    } else {
        tcq->cqe_sizeof = sizeof(struct sx_cqe_v2);
        tcq->cqe_version = 2;
        tcq->sx_next_cqe_cb = sx_next_cqe_v2;
        tcq->sx_fill_poll_one_params_from_cqe_cb = sx_fill_poll_one_params_from_cqe_v2;
        tcq->sx_get_cqe_owner_cb = sx_get_cqe_owner_v2;
        tcq->sx_cqe_owner_init_cb = sx_cqe_owner_init_v2;
        *cqe_ver = 1;
    }
}

void sx_init_cq_db_v2(struct sx_cq *tcq, u8 cqn, u8 *cqe_ver)
{
    tcq->cqe_version = 2;
    tcq->cqe_sizeof = sizeof(struct sx_cqe_v2);
    tcq->sx_next_cqe_cb = sx_next_cqe_v2;
    tcq->sx_fill_poll_one_params_from_cqe_cb = sx_fill_poll_one_params_from_cqe_v2;
    tcq->sx_get_cqe_owner_cb = sx_get_cqe_owner_v2;
    tcq->sx_cqe_owner_init_cb = sx_cqe_owner_init_v2;
    *cqe_ver = 1;
}

int sx_core_create_cq(struct sx_dev *dev, int nent, struct sx_cq **cq, u8 cqn)
{
    struct sx_priv        *priv = sx_priv(dev);
    struct sx_cq_table    *cq_table = &priv->cq_table;
    struct sx_cmd_mailbox *mailbox;
    struct sx_cq_context  *cq_context;
    int                    err;
    unsigned long          flags;
    struct sx_cq          *tcq;
    u8                     cqe_ver = 0;

    if ((nent <= 0) || (dev == NULL)) {
        return -EINVAL;
    }

    tcq = kzalloc(sizeof *tcq, GFP_KERNEL);
    if (!tcq) {
        return -ENOMEM;
    }

    tcq->cqn = sx_bitmap_set(&cq_table->bitmap, cqn);
    if (tcq->cqn == -1) {
        err = -EBUSY;
        goto out_free_cq;
    }

    /* CQ is for send completions - CPU high priority */
    if (cqn < NUMBER_OF_SDQS) {
        sx_bitmap_set(&cq_table->cpu_traffic_prio.high_prio_cq_bitmap, cqn);
    }

    err = __sx_core_dev_specific_cb_get_reference(dev);
    if (err) {
        err = -EINVAL;
        goto free_from_cq_table;
    }

    priv->dev_specific_cb.sx_init_cq_db_cb(tcq, cqn, &cqe_ver);

    __sx_core_dev_specific_cb_release_reference(dev);

    spin_lock_irqsave(&cq_table->lock, flags);
    cq_table->cq[tcq->cqn] = tcq;
    spin_unlock_irqrestore(&cq_table->lock, flags);
    mailbox = sx_alloc_cmd_mailbox(dev, dev->device_id);
    if (IS_ERR(mailbox)) {
        err = PTR_ERR(mailbox);
        goto free_from_cq_table;
    }

    cq_context = mailbox->buf;
    memset(cq_context, 0, sizeof *cq_context);
    err = sx_buf_alloc(dev, nent * tcq->cqe_sizeof, PAGE_SIZE,
                       &tcq->buf, 0);
    if (err) {
        goto err_mbox;
    }

    tcq->nent = nent;
    cq_context->eq_num = priv->eq_table.eq[SX_EQ_COMP].eqn
                         | (cqe_ver << SX_CQE_VER_OFFSET);

    tcq->cqe_ts_arr = vmalloc(nent * sizeof(tcq->cqe_ts_arr[0]));
    if (tcq->cqe_ts_arr == NULL) {
        goto err_buf;
    }

    cq_context->log_cq_size = (u8)ilog2(nent);
    if (dev->pdev) {
        sx_fill_page_list(cq_context->dma_addr, &tcq->buf);
    }

    tcq->sx_cqe_owner_init_cb(tcq);
    err = sx_SW2HW_CQ(dev, mailbox, tcq->cqn);
    if (err) {
        goto err_ts_alloc;
    }

    sx_free_cmd_mailbox(dev, mailbox);
    tcq->set_ci_db = priv->db_base + SX_DBELL_CQ_CI_OFFSET + 4 * tcq->cqn;
    tcq->arm_db = priv->db_base + SX_DBELL_CQ_ARM_OFFSET + 4 * tcq->cqn;
    tcq->sx_dev = dev;
    tcq->cons_index = 0;
    tcq->cons_index_dbg = 0;
    tcq->cons_index_dbg_snapshot = 0;
    atomic_set(&tcq->refcount, 1);
    atomic_set(&tcq->bkp_poll_data.curr_num_cq_polls, 0);
    atomic_set(&tcq->bkp_poll_data.cq_bkp_poll_mode, 0);
    init_completion(&tcq->free);
    spin_lock_init(&tcq->lock);
    spin_lock_init(&tcq->rearm_lock);
    sx_cq_set_ci(tcq);
    sx_cq_arm(tcq);
    *cq = tcq;

    return 0;

err_ts_alloc:
    if (tcq->cqe_ts_arr) {
        vfree(tcq->cqe_ts_arr);
    }

err_buf:
    sx_buf_free(dev, tcq->nent * tcq->cqe_sizeof, &tcq->buf);

err_mbox:
    sx_free_cmd_mailbox(dev, mailbox);

free_from_cq_table:
    spin_lock_irqsave(&cq_table->lock, flags);
    cq_table->cq[tcq->cqn] = NULL;
    spin_unlock_irqrestore(&cq_table->lock, flags);
    sx_bitmap_free(&cq_table->bitmap, tcq->cqn);

out_free_cq:
    kfree(tcq);

    return err;
}


void sx_core_destroy_cq(struct sx_dev *dev, struct sx_cq *cq, struct sx_dq *dq)
{
    struct sx_priv     *priv = sx_priv(dev);
    struct sx_cq_table *cq_table = &priv->cq_table;
    unsigned long       flags;
    int                 err;

    if (!cq) {
        sx_err(dev, "sx_core_destroy_cq  : cq(%p) == NULL\n", cq);
        return;
    }

    spin_lock_irqsave(&cq_table->lock, flags);
    cq_table->cq[cq->cqn] = NULL;
    spin_unlock_irqrestore(&cq_table->lock, flags);

    if (!priv->dev_stuck) {
        err = sx_HW2SW_CQ(dev, cq->cqn);
        if (err) {
            sx_warn(dev, "HW2SW_CQ failed (%d) "
                    "for CQN %06x\n", err, cq->cqn);
        }
    }

    synchronize_irq(priv->eq_table.eq[SX_EQ_COMP].irq);

    __sx_cq_dec_refcnt(cq);
    if (wait_for_completion_timeout(&cq->free, msecs_to_jiffies(10000)) == 0) {
        printk(KERN_ERR "sx_core: Error - trying to delete CQ but it is still in use! "
               "[cqn=%d, is_monitor=%s, DQ_head=%u, DQ_tail=%u, idle=%s]\n",
               cq->cqn,
               (dq->is_monitor ? "true" : "false"),
               dq->head,
               dq->tail,
               (sx_is_cq_idle(dev, cq->cqn) ? "true" : "false"));
    }

    if (cq->cqe_ts_arr) {
        vfree(cq->cqe_ts_arr);
    }

    sx_bitmap_free(&cq_table->bitmap, cq->cqn);
    sx_buf_free(dev, cq->nent * cq->cqe_sizeof, &cq->buf);
    kfree(cq);
}


int iterate_active_cqs(struct sx_dev *dev, struct sx_bitmap *active_cq_bitmap)
{
    struct sx_priv *priv = sx_priv(dev);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    struct timespec64 *ts;
#else
    struct timespec *ts;
#endif
    int num_of_cqe_handled;
    int should_continue_polling = 0;
    int cqn;
    u16 weight;

    weight = 1 << priv->dev_cap.log_max_sdq_sz;
    for (cqn = 0; cqn < priv->dev_cap.max_num_cqs; cqn++) {
        if (!test_bit(cqn, active_cq_bitmap->table)) {
            continue;
        }

        if (cqn >= NUMBER_OF_SDQS) {
            weight = priv->profile.pci_profile.rdq_properties[cqn - NUMBER_OF_SDQS].rdq_weight;
            ts = &priv->cq_table.timestamps[cqn];
        } else {
            ts = NULL;
        }

        num_of_cqe_handled = sx_cq_completion(dev, cqn, weight, ts, active_cq_bitmap);
        if (num_of_cqe_handled < 0) {
            if (!priv->global_flushing) {
                printk(KERN_WARNING PFX "CQ completion failed (err=%d)\n", num_of_cqe_handled);
            }
        } else if (num_of_cqe_handled == weight) {
            should_continue_polling = 1;
        }
    }

    return should_continue_polling;
}

int __handle_monitor_rdq_completion(struct sx_dev *dev, int dqn)
{
    int                    err;
    struct ku_query_cq     cq_context;
    u16                    rx_cnt = 0;
    unsigned long          flags;
    struct sx_cq          *cq;
    struct sx_dq          *rdq;
    int                    cqn;
    struct sx_priv        *priv = sx_priv(dev);
    int                    i;
    u32                    cq_ts_enabled = 0;
    union sx_cqe           u_cqe;
    struct sx_cqe_params   cqe_params = {0};
    int                    idx;
    struct sk_buff        *skb;
    u16                    rdq_max_buff_size = 0;
    bool                   rx_ts_set = false;
    struct sx_rx_timestamp rx_ts;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
    int should_drop = 0;
#endif

    spin_lock_irqsave(&priv->rdq_table.lock, flags);
    rdq = priv->rdq_table.dq[dqn];
    spin_unlock_irqrestore(&priv->rdq_table.lock, flags);
    if (rdq == NULL) {
        sx_warn(dev, "Completion event for bogus DQ %08x\n", dqn);
        return -EINVAL;
    }
    /*update the active RDQ's bitmap for the fatal failure detection feature */
    sx_health_check_report_dq_ok(dev, false, dqn);

    /* no need to check cq existence because dq destroyed first */
    cq = rdq->cq;
    cqn = cq->cqn;

    if (!test_bit(cqn, priv->active_monitor_cq_bitmap.table)) {
        goto out;
    }

    err = sx_core_get_rdq_param_max(dev, NULL, &rdq_max_buff_size);
    if (err) {
        sx_err(dev, "failed to get monitor RDQ attributes (err=%d)\n", err);
        return err;
    }

    /* read cq producer counter, which indicate the total number of
     * received packets */
    err = sx_QUERY_CQ(dev, cqn, &cq_context);
    if (err) {
        sx_err(dev, "sx_QUERY_CQ failed for cqn %08x\n", cqn);
        return -EINVAL;
    }

    /* valid cqes is cqes between cons_index and producer_index */
    /* for more details about 'priv->pause_cqn' role, read the big comment in ctrl_cmd_set_monitor_rdq() */
    if (cq_context.producer_counter == (cq->cons_index & 0xffff)) {
        /* No packets was received so
         * arm cq so next time we will be waked up from interrupt */
        sx_bitmap_free(&priv->active_monitor_cq_bitmap, cqn);
        sx_cq_arm(cq);

        if (rdq->is_flushing) {
            /* CQ is no longer in use (its RDQ is in ERR state and flushed all its buffers).
             *  this will signal sx_core_destroy_cq() that CQ can be deleted */
            __sx_cq_dec_refcnt(cq);
        }

        goto out;
    }

    cq_ts_enabled = IS_CQ_WORKING_WITH_TIMESTAMP(dev, cq->cqn);

    /* if CQ configured with TS enable add them to each cqe.
     * the timestamp source may change later in this function (if enable_monitor_rdq_trace_points enabled)
     * or in sx_monitor_simulate_rx_skb(). now we have Linux timestamp but the CQ may be configured to get
     * the timestamp from HW (thus, from CQE).
     */
    if (cq_ts_enabled) {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
        ktime_get_real_ts64(&priv->cq_table.timestamps[cq->cqn]);
#else
        getnstimeofday(&priv->cq_table.timestamps[cq->cqn]);
#endif
    }

    for (i = cq->cons_index & 0xffff; i != cq_context.producer_counter; i = (i + 1) & 0xffff) {
        sx_get_cqe_all_versions(cq, i, &u_cqe);
        if (u_cqe.v2 == NULL) {
            break;
        }

        rx_cnt++;
        cq->sx_fill_poll_one_params_from_cqe_cb(&u_cqe, &cqe_params);

        if (cqe_params.is_send) {
            continue;
        }

        if (cq_ts_enabled) {
            cq->cqe_ts_arr[i % cq->nent].timestamp = priv->cq_table.timestamps[cq->cqn];
            cq->cqe_ts_arr[i % cq->nent].ts_type = SXD_TS_TYPE_LINUX;
        }

        idx = i % rdq->wqe_cnt;
        skb = rdq->sge[idx].skb;
        rx_ts_set = false;

        sx_drop_monitor_handle_monitor_rdq(cq_ts_enabled, cq, i, &cqe_params, &u_cqe, &rx_ts, &rx_ts_set, skb);

        if (enable_monitor_rdq_trace_points) {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
            should_drop = 0;
            spin_lock_irqsave(&priv->rdq_table.lock, flags);
            if (priv->filter_ebpf_progs[dqn]) {
                should_drop = sx_core_call_rdq_filter_trace_point_func(dev,
                                                                       priv->filter_ebpf_progs[dqn],
                                                                       skb,
                                                                       &cqe_params,
                                                                       rdq_max_buff_size);
            } else {
                skb->mark = 0;
            }

            if (should_drop != 0) {
                spin_unlock_irqrestore(&priv->rdq_table.lock, flags);
                continue;
            }
            if (cq_ts_enabled) {
                if (!rx_ts_set) {
                    set_timestamp_of_rx_packet(cq, &cq->cqe_ts_arr[i % cq->nent].timestamp, &cqe_params.cqe_ts,
                                               &rx_ts);
                }
                sx_core_call_rdq_agg_trace_point_func(priv,
                                                      dqn,
                                                      rdq_max_buff_size,
                                                      skb,
                                                      &cqe_params,
                                                      &rx_ts.timestamp);
            } else {
                sx_core_call_rdq_agg_trace_point_func(priv, dqn, rdq_max_buff_size, skb, &cqe_params, NULL);
            }
            spin_unlock_irqrestore(&priv->rdq_table.lock, flags);
#endif
        } else {
            skb->mark = 0;
        }
    }

    /* simulate we polled all cqes */
    cq->cons_index = cq_context.producer_counter;
    cq->cons_index_dbg += rx_cnt;
    sx_cq_set_ci(cq);

    /* update rdq head and tail */
    rdq->head += rx_cnt;
    rdq->tail += rx_cnt;

    /* Write rdq doorbell */
    wmb();
    __raw_writel((__force u32)cpu_to_be32(rdq->head & 0xffff), rdq->db);
    MMIOWB();

    rdq->mon_rx_count += rx_cnt;

    /*
     *  the window [mon_rx_start, mon_rx_start+mon_rx_cnt] should
     *  contains maximum wqe_cnt packets
     */
    if (rdq->mon_rx_count - rdq->mon_rx_start > rdq->wqe_cnt) {
        rdq->mon_rx_start = rdq->mon_rx_count - rdq->wqe_cnt;
    }

    /* valid cqes is cqes between cons_index and producer_index */
    /* for more details about 'priv->pause_cqn' role, read the big comment in ctrl_cmd_set_monitor_rdq() */
    if ((priv->pause_cqn == cqn) || (i != cq_context.producer_counter)) {
        /* No packets was received so
         * arm cq so next time we will be waked up from interrupt */
        sx_bitmap_free(&priv->active_monitor_cq_bitmap, cqn);
        sx_cq_arm(cq);

        if (rdq->is_flushing) {
            /* CQ is no longer in use (its RDQ is in ERR state and flushed all its buffers).
             *  this will signal sx_core_destroy_cq() that CQ can be deleted */
            __sx_cq_dec_refcnt(cq);
        }

        /* make sure that the next time tasklet runs, the CQ bit in 'active_bitmap' will be off.
         * this will ensure to signal [complete()] the ioctl() command that waits for us.
         * for more details of the flow, read the big comment in ctrl_cmd_set_monitor_rdq().
         */
        tasklet_schedule(&priv->intr_tasklet);
        goto out;
    }

out:
    return rx_cnt;
}

static inline u64 __calculate_sleep_time(u64 ktime)
{
    int percent;
    u64 sleep_time;

    if (mon_cq_thread_cpu_util_percent == 0) {
        percent = MON_CQ_HANDLER_THREAD_CPU_UTIL_PERCENT_DEFAULT;
    } else if (mon_cq_thread_cpu_util_percent > 100) {
        percent = 100;
    } else {
        percent = mon_cq_thread_cpu_util_percent;
    }

    /* Calculate the time to sleep, in nanoseconds */
    if (((ktime * (100 - percent)) % percent) == 0) {
        sleep_time = ktime * (100 - percent) / percent;
    } else {
        sleep_time = ktime * (100 - percent) / percent + 1;
    }

    /* Transform the time to sleep to microseconds */
    if ((sleep_time % 1000) == 0) {
        sleep_time = sleep_time / 1000;
    } else {
        sleep_time = sleep_time / 1000 + 1;
    }

    /* According to https://www.kernel.org/doc/Documentation/timers/timers-howto.txt,
     * if the sleep time is less than 10us, we should use udelay instead of usleep.
     * As udelay is doing busy-wait which is a waste of CPU cycles, we limit the minimum
     * sleep time to 10us here.
     */
    if (sleep_time < 10) {
        return 10;
    } else {
        return sleep_time;
    }
}

static int __monitor_cq_handler_thread(void *arg)
{
    struct sx_dev               *dev = (struct sx_dev*)arg;
    struct cpu_traffic_priority *cpu_traffic_prio = &sx_priv(dev)->cq_table.cpu_traffic_prio;
    int                          should_continue_polling;
    int                          ret;
    int                          i;
    u64                          ktime_before;
    u64                          ktime_after;
    u64                          sleep_time;
    unsigned long                flags;
    int                          dqn;

    pr_debug("starting new device's monitor CQ handler thread\n");

    cpu_traffic_prio->monitor_cq_thread_alive = 1;

    /* signal that __monitor_cq_handler_thread has started */
    up(&cpu_traffic_prio->monitor_cq_thread_started_sem);

    while (cpu_traffic_prio->monitor_cq_thread_alive) {
        if (down_interruptible(&cpu_traffic_prio->monitor_cq_thread_sem)) {
            continue;
        }

        if (!cpu_traffic_prio->monitor_cq_thread_alive) {
            break;
        }

        should_continue_polling = 0;
        for (i = 0; i < MAX_MONITOR_RDQ_NUM; i++) {
            spin_lock_irqsave(&sx_priv(dev)->rdq_table.lock, flags);
            dqn = sx_priv(dev)->monitor_rdqs_arr[i];
            spin_unlock_irqrestore(&sx_priv(dev)->rdq_table.lock, flags);
            if (dqn == RDQ_INVALID_ID) {
                continue;
            }

            ktime_before = ktime_to_ns(ktime_get());
            ret = __handle_monitor_rdq_completion(dev, dqn);
            if (ret > 0) {
                should_continue_polling++;
                ktime_after = ktime_to_ns(ktime_get());
                sleep_time = __calculate_sleep_time(ktime_after - ktime_before);
                usleep_range(sleep_time, sleep_time + 5);
            }
        }

        if (should_continue_polling) {
            up(&cpu_traffic_prio->monitor_cq_thread_sem); /* re-arm thread loop */
        }
    }

    pr_debug("terminating new device's monitor CQ handler thread\n");

    return 0;
}

static int __low_priority_cq_handler_thread(void *arg)
{
    struct sx_dev               *dev = (struct sx_dev*)arg;
    struct cpu_traffic_priority *cpu_traffic_prio = &sx_priv(dev)->cq_table.cpu_traffic_prio;
    int                          should_continue_polling;

    pr_debug("starting new device's low-priority CQ handler thread\n");

    cpu_traffic_prio->low_prio_cq_thread_alive = 1;

    /* signal __low_priority_cq_handler_thread has started */
    up(&cpu_traffic_prio->low_prio_cq_thread_started_sem);

    while (cpu_traffic_prio->low_prio_cq_thread_alive) {
        if (down_interruptible(&cpu_traffic_prio->low_prio_cq_thread_sem)) {
            continue;
        }

        if (!cpu_traffic_prio->low_prio_cq_thread_alive) {
            break;
        }

        /* if high priority traffic has not completed handling, we'll wait ... */
        while (cpu_traffic_priority_disrupt_low_prio_upon_stress &&
               atomic_read(&cpu_traffic_prio->high_prio_cq_in_load) == 1) {
            msleep(cpu_traffic_priority_disrupt_low_prio_upon_stress_delay);
        }

        should_continue_polling = iterate_active_cqs(dev, &cpu_traffic_prio->active_low_prio_cq_bitmap);
        if (should_continue_polling) {
            cond_resched(); /* if kernel is compiled without CONFIG_PREEMPT flag, heavy traffic to CPU can
                             *  cause lots of troubles if we're not explicitly give up CPU */
            up(&cpu_traffic_prio->low_prio_cq_thread_sem); /* re-arm thread loop */
        }
    }

    pr_debug("terminating new device's low-priority CQ handler thread\n");

    return 0;
}


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0))
static void __sampling_timer_fn(struct timer_list *t)
#else
static void __sampling_timer_fn(unsigned long data)
#endif
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0))
    struct cpu_traffic_priority *cpu_traffic_prio = from_timer(cpu_traffic_prio, t, sampling_timer);
#else
    struct sx_dev               *dev = (struct sx_dev*)data;
    struct sx_priv              *priv = sx_priv(dev);
    struct cpu_traffic_priority *cpu_traffic_prio = &priv->cq_table.cpu_traffic_prio;
#endif

    atomic_set(&cpu_traffic_prio->high_prio_cq_in_load, 0);
    mod_timer(&cpu_traffic_prio->sampling_timer, jiffies + HZ);
}


int __cpu_traffic_priority_init(struct sx_dev *dev, struct cpu_traffic_priority *cpu_traffic_prio)
{
    struct sx_priv *priv = sx_priv(dev);
    char            thread_name[32];
    static atomic_t sn = ATOMIC_INIT(0);
    int             err;

    err = sx_bitmap_init(&cpu_traffic_prio->high_prio_cq_bitmap, priv->dev_cap.max_num_cqs);
    if (err) {
        goto out;
    }

    err = sx_bitmap_init(&cpu_traffic_prio->active_high_prio_cq_bitmap, priv->dev_cap.max_num_cqs);
    if (err) {
        goto out;
    }

    err = sx_bitmap_init(&cpu_traffic_prio->active_low_prio_cq_bitmap, priv->dev_cap.max_num_cqs);
    if (err) {
        goto out;
    }

    sema_init(&cpu_traffic_prio->low_prio_cq_thread_started_sem, 0);
    sema_init(&cpu_traffic_prio->monitor_cq_thread_started_sem, 0);
    atomic_set(&cpu_traffic_prio->high_prio_cq_in_load, 0);
    sema_init(&cpu_traffic_prio->low_prio_cq_thread_sem, 0);
    sema_init(&cpu_traffic_prio->monitor_cq_thread_sem, 0);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0))
    timer_setup(&cpu_traffic_prio->sampling_timer, __sampling_timer_fn, 0);
#else
    init_timer(&cpu_traffic_prio->sampling_timer);

    cpu_traffic_prio->sampling_timer.data = (unsigned long)dev;
    cpu_traffic_prio->sampling_timer.function = __sampling_timer_fn;
#endif
    mod_timer(&cpu_traffic_prio->sampling_timer, jiffies + HZ);

    atomic_inc(&sn);
    snprintf(thread_name, sizeof(thread_name), "cq_cpu_prio_%u", atomic_read(&sn));
    cpu_traffic_prio->low_prio_cq_thread = kthread_run(__low_priority_cq_handler_thread, dev, thread_name);
    if (IS_ERR(cpu_traffic_prio->low_prio_cq_thread)) {
        err = PTR_ERR(cpu_traffic_prio->low_prio_cq_thread);
        printk(KERN_ERR "failed to create low-priority thread (err=%d)\n", err);
        goto del_timer;
    }

    /* wait for __low_priority_cq_handler_thread to be started */
    down(&cpu_traffic_prio->low_prio_cq_thread_started_sem);

    err = sx_bitmap_init(&sx_priv(dev)->monitor_cq_bitmap, priv->dev_cap.max_num_cqs);
    if (err) {
        printk(KERN_ERR PFX "Monitor RDQ bitmap init failed. Aborting...\n");
        goto stop_low_prio_cq_thread;
    }

    err = sx_bitmap_init(&sx_priv(dev)->active_monitor_cq_bitmap, priv->dev_cap.max_num_cqs);
    if (err) {
        printk(KERN_ERR PFX "Active monitor RDQ bitmap init failed. Aborting...\n");
        goto stop_low_prio_cq_thread;
    }

    snprintf(thread_name, sizeof(thread_name), "mon_cq_handler");
    cpu_traffic_prio->monitor_cq_thread = kthread_run(__monitor_cq_handler_thread, dev, thread_name);
    if (IS_ERR(cpu_traffic_prio->monitor_cq_thread)) {
        err = PTR_ERR(cpu_traffic_prio->monitor_cq_thread);
        printk(KERN_ERR "failed to create monitor cq thread (err=%d)\n", err);
        goto stop_low_prio_cq_thread;
    }

    /* wait for __monitor_cq_handler_thread to be started */
    down(&cpu_traffic_prio->monitor_cq_thread_started_sem);
    goto out;

stop_low_prio_cq_thread:
    cpu_traffic_prio->low_prio_cq_thread_alive = 0;
    up(&cpu_traffic_prio->low_prio_cq_thread_sem);
    kthread_stop(cpu_traffic_prio->low_prio_cq_thread);
    cpu_traffic_prio->low_prio_cq_thread = NULL;

del_timer:
    del_timer_sync(&cpu_traffic_prio->sampling_timer);

out:
    return err;
}


void __cpu_traffic_priority_deinit(struct sx_dev *dev, struct cpu_traffic_priority *cpu_traffic_prio)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err;

    /* clean all monitor cqs so on unload it will be handled in regular way and
     * not by __monitor_cq_handler_thread */
    err = sx_bitmap_init(&priv->monitor_cq_bitmap, priv->dev_cap.max_num_cqs);
    if (err) {
        printk(KERN_ERR PFX "Monitor RDQ bitmap init failed.\n");
    }

    if (cpu_traffic_prio->monitor_cq_thread && !IS_ERR(cpu_traffic_prio->monitor_cq_thread)) {
        cpu_traffic_prio->monitor_cq_thread_alive = 0;
        up(&cpu_traffic_prio->monitor_cq_thread_sem);
        kthread_stop(cpu_traffic_prio->monitor_cq_thread);
        cpu_traffic_prio->monitor_cq_thread = NULL;
    }

    if (cpu_traffic_prio->low_prio_cq_thread && !IS_ERR(cpu_traffic_prio->low_prio_cq_thread)) {
        del_timer_sync(&cpu_traffic_prio->sampling_timer);
        cpu_traffic_prio->low_prio_cq_thread_alive = 0;
        up(&cpu_traffic_prio->low_prio_cq_thread_sem);
        kthread_stop(cpu_traffic_prio->low_prio_cq_thread);
        cpu_traffic_prio->low_prio_cq_thread = NULL;
    }
}


int sx_core_init_cq_table(struct sx_dev *dev)
{
    struct sx_priv     *priv = sx_priv(dev);
    struct sx_cq_table *cq_table = &priv->cq_table;
    struct sx_cq      **cq_array = NULL;
    int                 err = 0;
    int                 i = 0;
    unsigned long       flags;

    spin_lock_init(&cq_table->lock);

    cq_array = kmalloc(priv->dev_cap.max_num_cqs * sizeof(*cq_array),
                       GFP_KERNEL);
    if (!cq_array) {
        return -ENOMEM;
    }

    for (i = 0; i < priv->dev_cap.max_num_cqs; i++) {
        cq_array[i] = NULL;
    }

    spin_lock_irqsave(&cq_table->lock, flags);
    cq_table->cq = cq_array;
    spin_unlock_irqrestore(&cq_table->lock, flags);
    err = sx_bitmap_init(&cq_table->bitmap, priv->dev_cap.max_num_cqs);
    if (err) {
        return err;
    }

    err = sx_bitmap_init(&cq_table->ts_bitmap, priv->dev_cap.max_num_cqs);
    if (err) {
        return err;
    }

    err = sx_bitmap_init(&cq_table->ts_hw_utc_bitmap, priv->dev_cap.max_num_cqs);
    if (err) {
        return err;
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    cq_table->timestamps = kmalloc(sizeof(struct timespec64) * priv->dev_cap.max_num_cqs, GFP_KERNEL);
#else
    cq_table->timestamps = kmalloc(sizeof(struct timespec) * priv->dev_cap.max_num_cqs, GFP_KERNEL);
#endif

    if (!cq_table->timestamps) {
        err = -ENOMEM;
        goto out;
    }

    err = __cpu_traffic_priority_init(dev, &cq_table->cpu_traffic_prio);

out:
    if (err) {
        kfree(cq_table->timestamps);
        cq_table->timestamps = NULL;
        kfree(cq_table->cq);
        cq_table->cq = NULL;
    }

    return err;
}

void sx_core_destroy_cq_table(struct sx_dev *dev)
{
    struct sx_cq_table *cq_table = &sx_priv(dev)->cq_table;
    unsigned long       flags;

    __cpu_traffic_priority_deinit(dev, &cq_table->cpu_traffic_prio);

    spin_lock_irqsave(&cq_table->lock, flags);
    kfree(cq_table->timestamps);
    cq_table->timestamps = NULL;
    kfree(cq_table->cq);
    cq_table->cq = NULL;
    spin_unlock_irqrestore(&cq_table->lock, flags);

    sx_drop_monitor_destroy();
}

void sx_core_dump_synd_tbl(struct sx_dev *dev)
{
    struct sx_priv               *priv = sx_priv(dev);
    struct listeners_and_rf_info *info = NULL;
    struct listener_entry        *listener;
    struct list_head             *pos;
    u16                           entry = 0;

    mutex_lock(&priv->listeners_and_rf_db.lock);
    info = priv->listeners_and_rf_db.info;

    if (!info) {
        goto out;
    }

    for (entry = 0; entry < NUM_HW_SYNDROMES + 1; entry++) {
        if (entry % 100 == 0) {
            udelay(1);
        }
        if (!list_empty(&info->per_synd_list[entry])) {
            list_for_each(pos, &info->per_synd_list[entry]) {
                listener = list_entry(pos,
                                      struct listener_entry, list);
                printk(KERN_INFO
                       "=============================\n");
                printk(KERN_INFO
                       "synd=%d, swid=%d,is_def:%d, "
                       "handler:%p, rx_pkt:%llu \n",
                       entry,
                       listener->swid,
                       listener->is_default,
                       listener->handler,
                       listener->rx_pkts);

                switch (listener->listener_type) {
                case L2_TYPE_DONT_CARE:
                    printk(KERN_INFO "list_type: "
                           "DONT_CARE, crit [port:0x%x] \n",
                           listener->critireas.dont_care.sysport);
                    break;

                case L2_TYPE_IB:
                    printk(KERN_INFO "list_type: IB, crit"
                           " [qpn:0x%x (%d)] \n",
                           listener->critireas.ib.qpn,
                           listener->critireas.ib.qpn);
                    break;

                case L2_TYPE_ETH:
                    printk(KERN_INFO "list_type: ETH, crit "
                           "[ethtype:0x%x, dmac:%llx, "
                           "emad_tid:0x%x, from_rp:%u, from_bridge:%u ] \n",
                           listener->critireas.eth.ethtype,
                           listener->critireas.eth.dmac,
                           listener->critireas.eth.emad_tid,
                           listener->critireas.eth.from_rp,
                           listener->critireas.eth.from_bridge);
                    break;

                case L2_TYPE_FC:
                    printk(KERN_INFO "list_type: FC \n");
                    break;

                default:
                    printk(KERN_INFO "list_type: UNKNOWN \n");
                    break;
                }
            }
        }
    }

out:
    mutex_unlock(&priv->listeners_and_rf_db.lock);
}


void sx_cq_show_cq(struct sx_dev *dev, int cqn)
{
    struct sx_priv                     *priv = sx_priv(dev);
    struct sx_cq_table * __maybe_unused cq_table = &priv->cq_table;
    struct sx_cq                       *cq = priv->cq_table.cq[cqn];
    int                                 iii, jjj;
    u8                                  cqe_owner[16];

    if (!cq) {
        printk(KERN_ERR "cq %d doesn't exist \n", cqn);
        return;
    }

    printk(KERN_INFO "[cq %d]: cqn:%d, cons_index:%d, nent:%d cons_index&(nent-1):%d"
           " ref_cnt:%d, cqe_version:%d, on_hold:%d \n",
           cqn,
           cq->cqn,
           cq->cons_index,
           cq->nent,
           (cq->cons_index & (cq->nent - 1)),
           atomic_read(&cq->refcount),
           cq->cqe_version,
           cq_table->cq[cqn]->dbg_cq_on_hold
           );

    printk(KERN_INFO "CQ %d owner:\n", cqn);
    for (iii = 0; iii < cq->nent / 16; iii++) {
        for (jjj = 0; (jjj < 16) && ((iii * 16 + jjj) < cq->nent); jjj++) {
            cqe_owner[jjj] = cq->sx_get_cqe_owner_cb(cq, (iii * 16 + jjj));
        }
        printk(KERN_INFO "[%5.5d]: %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x "
               "%2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x\n",
               iii * 16,
               cqe_owner[0], cqe_owner[1], cqe_owner[2], cqe_owner[3],
               cqe_owner[4], cqe_owner[5], cqe_owner[6], cqe_owner[7],
               cqe_owner[8], cqe_owner[9], cqe_owner[10], cqe_owner[11],
               cqe_owner[12], cqe_owner[13], cqe_owner[14], cqe_owner[15]);
    }
    printk(KERN_INFO "\n");
}

/* Get CQE despite the cqe version */
void sx_get_cqe_all_versions(struct sx_cq *cq, uint32_t n, union sx_cqe *cqe_p)
{
    switch (cq->cqe_version) {
    case 0:
        cqe_p->v0 = sx_get_cqe(cq, n & (cq->nent - 1));
        break;

    case 1:
        cqe_p->v1 = sx_get_cqe(cq, n & (cq->nent - 1));
        break;

    case 2:
        cqe_p->v2 = sx_get_cqe(cq, n & (cq->nent - 1));
        break;
    }

    /* In case the CQ version isn't 0-2 return NULL */
}

void sx_cq_flush_rdq(struct sx_dev *dev, int dqn)
{
    struct sx_priv     *priv = sx_priv(dev);
    struct sx_dq_table *rdq_table = &priv->rdq_table;
    struct sx_dq       *dq = rdq_table->dq[dqn];
    struct sx_cq       *cq = dq->cq;
    int                 num_of_packets = 0;
    int                 err = 0;

    /* these lines will force sx_is_cq_idle() to return 1 [in EQ code] so sx_cq_pause() will get
     * the completion eventually */
    sx_bitmap_free(&priv->cq_table.cpu_traffic_prio.active_high_prio_cq_bitmap, cq->cqn);
    sx_bitmap_free(&priv->cq_table.cpu_traffic_prio.active_low_prio_cq_bitmap, cq->cqn);
    sx_bitmap_free(&priv->active_monitor_cq_bitmap, cq->cqn);

    /* pause the CQ so no other tasklet/thread handles it concurrently */
    err = sx_cq_pause(cq, priv);
    if (err) {
        printk(KERN_ERR "failed to pause RDQ %d\n", dqn);
        return;
    }

    do {
        err = sx_poll_one(cq, NULL);
        num_of_packets += (err == 0);
    } while (err == 0);

    printk(KERN_NOTICE "RDQ flushed %d packets\n", num_of_packets);

    /* resume the CQ so other tasklet/threads can continue handling it */
    sx_cq_resume(cq, priv);
}

enum {
    SX_CQ_BITMAP_HIGH_PRIO,
    SX_CQ_BITMAP_LOW_PRIO,
    SX_CQ_BITMAP_MONITOR
};

static u32 __sx_cq_active_bitmaps(struct sx_dev *dev, int cqn)
{
    struct sx_priv              *priv = sx_priv(dev);
    struct cpu_traffic_priority *cpu_tp = &priv->cq_table.cpu_traffic_prio;
    u32                          ret = 0;

    if (sx_bitmap_test(&cpu_tp->active_high_prio_cq_bitmap, cqn)) {
        ret |= (1 << SX_CQ_BITMAP_HIGH_PRIO);
    }

    if (sx_bitmap_test(&cpu_tp->active_low_prio_cq_bitmap, cqn)) {
        ret |= (1 << SX_CQ_BITMAP_LOW_PRIO);
    }

    if (sx_bitmap_test(&priv->active_monitor_cq_bitmap, cqn)) {
        ret |= (1 << SX_CQ_BITMAP_MONITOR);
    }

    return ret;
}

/* use this function to make sure that a CQ and its associated DQ is idle,
 * which means that no tasklet, not low-priority thread or monitoring thread
 * runs the CQ/DQ. Currently we use this function is two cases:
 * 1. when changing a RDQ role from regular to monitoring or vice versa. in
 *    this case we must make sure that before changing role the CQ is idle so
 *    there will not be a point in time when two threads handling the same RDQ.
 * 2. when destroying a SDQ/RDQ. When doing so, we must wait until no thread is
 *    working on the DQ while it is being destroyed.
 */
u8 sx_is_cq_idle(struct sx_dev *dev, int cqn)
{
    return __sx_cq_active_bitmaps(dev, cqn) == 0;
}

int sx_cq_pause(struct sx_cq *cq, struct sx_priv* priv)
{
    int err = 0;

    init_completion(&priv->pause_cqn_completion);
    priv->pause_cqn_completed = 0;
    priv->pause_cqn = cq->cqn;
    tasklet_schedule(&priv->intr_tasklet);

    if (wait_for_completion_timeout(&priv->pause_cqn_completion, msecs_to_jiffies(5000)) == 0) {
        printk(KERN_ERR "CQ is still active (CQ=%d, active_bitmaps=0x%x)\n",
               priv->pause_cqn,
               __sx_cq_active_bitmaps(&priv->dev, cq->cqn));
        priv->pause_cqn = -1;
        err = -ETIMEDOUT;
        goto out;
    }

out:
    return err;
}

void sx_cq_resume(struct sx_cq *cq, struct sx_priv* priv)
{
    priv->pause_cqn = -1;
    sx_cq_arm(cq);
    tasklet_schedule(&priv->intr_tasklet);
}

/************************************************
 *                  EOF                         *
 ***********************************************/
