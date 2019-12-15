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
#include <linux/ptp_classify.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/workqueue.h>
#include <linux/vmalloc.h>
#include <linux/mlx_sx/skb_hook.h>
#include "sx.h"
#include "cq.h"
#include "dq.h"
#include "ib.h"
#include "alloc.h"
#include "sx_proc.h"
#include "sx_clock.h"
#include "sgmii.h"

#define CREATE_TRACE_POINTS
#include "trace.h"

#include <linux/module.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/version.h>
#include <linux/ktime.h>
#include <linux/hrtimer.h>

/************************************************
 *  Definitions
 ***********************************************/

#define MAX_MATCHING_LISTENERS 100

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

extern struct sx_globals sx_glb;
extern int               rx_debug;
extern int               rx_debug_pkt_type;
extern int               rx_debug_emad_type;
extern int               rx_cqev2_dbg;
extern int               rx_dump;
extern int               rx_dump_cnt;
extern int               cpu_traffic_priority_disrupt_low_prio_upon_stress;
extern int               cpu_traffic_priority_disrupt_low_prio_upon_stress_delay;
extern int               mon_cq_thread_delay_time_usec;
extern int               enable_monitor_rdq_trace_points;
extern int               enable_cpu_port_loopback;
unsigned int             credit_thread_vals[1001] = {0};
unsigned int             arr_count = 0;
atomic_t                 cq_backup_polling_enabled = ATOMIC_INIT(1);
int                      debug_cq_backup_poll_cqn = CQN_INVALID;
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

void sx_printk_cqe_v0(union sx_cqe *u_cqe)
{
    __be32 *cqebuf = (void*)u_cqe->v0;

    if (printk_ratelimit()) {
        printk(KERN_DEBUG "CQEv0 %p contents:\n%08x\n%08x\n%08x\n%08x\n",
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
        printk(KERN_DEBUG "CQEv1 %p contents:\n%08x\n%08x\n%08x\n%08x\n",
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

    printk(KERN_DEBUG "CQEv2 %p contents:\n%08x\n%08x\n%08x\n%08x\n%08x\n%08x\n%08x\n%08x\n",
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
}

void sx_fill_ci_from_cqe_v2(struct completion_info *ci, union sx_cqe *u_cqe)
{
    ci->swid = (u_cqe->v2->type_swid_crc >> 2) & 0x7;
    ci->pkt_type = (u_cqe->v2->type_swid_crc >> 5) & 0x7;
    ci->is_send = (u_cqe->v2->version_e_sr_packet_ok_rp_lag >> 2) & 0x1;
    ci->is_lag = u_cqe->v2->version_e_sr_packet_ok_rp_lag & 0x1;
    ci->sysport = be16_to_cpu(u_cqe->v2->rp_system_port_lag_id);
    ci->lag_subport = (ci->is_lag) ? u_cqe->v2->rp_lag_subport & 0x1F : 0;
    ci->user_def_val = be32_to_cpu(u_cqe->v2->mirror_cong1_user_def_val_orig_pkt_len) & 0xFFFFF;
    ci->dest_sysport = be16_to_cpu(u_cqe->v2->ep_system_port_lag_id);
    ci->dest_is_lag = u_cqe->v2->mirror_tclass_mirror_elph_ep_lag & 0x1;
    ci->dest_lag_subport = (ci->dest_is_lag) ? u_cqe->v2->ep_lag_subport & 0x1F : 0;
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
    int           i;
    u8            ret = 0;
    unsigned long flags;

    if (is_lag) {
        spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
        for (i = 0; i < MAX_LAG_PORTS_IN_FILTER; i++) {
            if (sx_priv(dev)->lag_filter_db[hw_synd][i] == sysport_lag_id) {
                inc_filtered_lag_packets_counter(dev);
                ret = 1;
                break;
            }
        }

        spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
        return ret;
    }

    /* EMADs can be received with sysport==0 */
    if (sysport_lag_id == 0) {
        return 0;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    for (i = 0; i < MAX_SYSTEM_PORTS_IN_FILTER; i++) {
        if (sx_priv(dev)->sysport_filter_db[hw_synd][i] == sysport_lag_id) {
            inc_filtered_port_packets_counter(dev);
            ret = 1;
            break;
        }
    }

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
    return ret;
}

static void cpu_loopback_work_handler(struct work_struct *work)
{
    struct cpu_loopback_data *cpu_lp_wdata = container_of(work, struct cpu_loopback_data, dwork.work);
    struct isx_meta           meta;
    struct sk_buff           *skb = cpu_lp_wdata->ci->skb;
    struct sk_buff           *tmp_skb = NULL;
    int                       len = 0;
    int                       err = 0;

    memset(&meta, 0, sizeof(meta));
    meta.dev_id = 1;
    meta.type = SX_PKT_TYPE_ETH_CTL_UC;

    /* No LAG support */
    meta.system_port_mid = cpu_lp_wdata->ci->sysport;

    len = skb->len;
    tmp_skb = alloc_skb(ISX_HDR_SIZE + len, GFP_KERNEL);
    if (!tmp_skb) {
        sx_skb_free(skb);
        printk(KERN_INFO PFX "%s: fail to alloc_skb\n", __func__);
        goto out;
    }

    skb_reserve(tmp_skb, ISX_HDR_SIZE);
    memcpy(skb_put(tmp_skb, len), skb->data, len);
    sx_skb_free(skb);

    err = sx_core_post_send(cpu_lp_wdata->ci->dev, tmp_skb, &meta);
    if (err) {
        printk(KERN_INFO PFX "%s: sx_core_post_send FAILED\n", __func__);
    }

out:
    /* Free memory */
    kfree(cpu_lp_wdata->ci);
    kfree(cpu_lp_wdata);
}

static void sx_cpu_port_loopback(struct completion_info *ci)
{
    struct cpu_loopback_data *cpu_lp_wdata = NULL;

    cpu_lp_wdata = kzalloc(sizeof(*cpu_lp_wdata), GFP_ATOMIC);
    if (!cpu_lp_wdata) {
        printk(KERN_ERR PFX "%s: Fail to alloc memory to loopback trap\n", __func__);
        return;
    }

    cpu_lp_wdata->ci = ci;
    INIT_DELAYED_WORK(&cpu_lp_wdata->dwork, cpu_loopback_work_handler);

    queue_delayed_work(ci->dev->generic_wq, &cpu_lp_wdata->dwork, 0);
}

static void ber_monitor_work_handler(struct work_struct *work)
{
    struct ber_work_data      *ber_wdata = container_of(work, struct ber_work_data, dwork.work);
    struct ku_access_ppbmc_reg ppbmc_reg_data;
    int                        err = 0;

    memset(&ppbmc_reg_data, 0, sizeof(ppbmc_reg_data));

    ppbmc_reg_data.dev_id = ber_wdata->dev->device_id;
    sx_cmd_set_op_tlv(&ppbmc_reg_data.op_tlv, PPBMC_REG_ID, 1);
    ppbmc_reg_data.ppbmc_reg.local_port = ber_wdata->local_port;

    /* Read PPBMC */
    err = sx_ACCESS_REG_PPBMC(ber_wdata->dev, &ppbmc_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Query PPBMC failed for local_port %d (err %d) \n",
               ber_wdata->local_port, err);
    }

    /* If armed - no need to re-arm */
    if (ppbmc_reg_data.ppbmc_reg.e != 0) {
        goto out;
    }

    ppbmc_reg_data.ppbmc_reg.e = 2; /* Generate single event */
    ppbmc_reg_data.ppbmc_reg.monitor_type = 0; /* monitor type is RO field */
    sx_cmd_set_op_tlv(&ppbmc_reg_data.op_tlv, PPBMC_REG_ID, 2);

    /* Set PPBMC */
    err = sx_ACCESS_REG_PPBMC(ber_wdata->dev, &ppbmc_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Set PPBMC failed for local_port %d (err %d) \n",
               ber_wdata->local_port, err);
    }

out:
    /* Free memory */
    kfree(ber_wdata);
}

static void sx_handle_ppbme_event(struct completion_info *ci)
{
    struct sxd_emad_ppbme_reg* ppbme = (struct sxd_emad_ppbme_reg *)ci->skb->data;
    struct sx_emad            *emad_header = &ppbme->emad_header;
    int                        reg_id = be16_to_cpu(emad_header->emad_op.register_id);
    unsigned short             type_len, ethertype;
    struct ber_work_data      *ber_wdata = NULL;
    u8                         monitor_state = 0, old_monitor_state = 0, ber_monitor_bitmask = 0;
    struct sx_priv            *priv = sx_priv((struct sx_dev *)ci->dev);
    unsigned long              flags;

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

    if (ppbme->local_port > MAX_PHYPORT_NUM) {
        printk(KERN_ERR PFX "Received local_port %d is invalid (max. %d) \n",
               ppbme->local_port, MAX_PHYPORT_NUM);
        return;
    }

    spin_lock_irqsave(&priv->db_lock, flags);
    old_monitor_state = priv->port_ber_monitor_state[ppbme->local_port];
    priv->port_ber_monitor_state[ppbme->local_port] = ppbme->monitor_state;
    ber_monitor_bitmask = priv->port_ber_monitor_bitmask[ppbme->local_port];
    spin_unlock_irqrestore(&priv->db_lock, flags);

    /* If monitor state didn't changed: silently drop the event */
    monitor_state = ppbme->monitor_state;
    if (old_monitor_state == monitor_state) {
        ci->info.dont_care.drop_enable = 1;
        goto rearm;
    }

    /* If user didn't request to be notified for the received monitor state:
     * Silently drop the event  */
    if (monitor_state == 0) {
        ci->info.dont_care.drop_enable = 1;
    } else if ((1 << (monitor_state - 1)) & ber_monitor_bitmask) {
        ci->info.dont_care.drop_enable = 0;
    } else {
        ci->info.dont_care.drop_enable = 1;
    }

rearm:
    /* Re-arm */
    ber_wdata = kzalloc(sizeof(*ber_wdata), GFP_ATOMIC);
    if (!ber_wdata) {
        printk(KERN_ERR PFX "Fail to alloc memory to re-arm event for local_port %d\n",
               ppbme->local_port);
        return;
    }

    ber_wdata->dev = ci->dev;
    ber_wdata->local_port = ppbme->local_port;
    INIT_DELAYED_WORK(&ber_wdata->dwork, ber_monitor_work_handler);

    queue_delayed_work(ci->dev->generic_wq, &ber_wdata->dwork, 0);
}

static void sx_handle_sbctr_event(struct completion_info *ci)
{
    struct sxd_emad_sbctr_reg* sbctr = (struct sxd_emad_sbctr_reg *)ci->skb->data;
    struct sx_emad            *emad_header = &sbctr->emad_header;
    int                        reg_id = be16_to_cpu(emad_header->emad_op.register_id);
    unsigned short             type_len, ethertype;
    u64                        old_tc_vec = 0, tc_vec = 0, new_tc_vec = 0;
    u8                         entity = 0, fp = 0, maybe_flag = 0, port_state = 0;
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

    if (sbctr->local_port > MAX_PHYPORT_NUM) {
        printk(KERN_ERR PFX "Received local_port %d is invalid (max. %d) \n",
               sbctr->local_port, MAX_PHYPORT_NUM);
        return;
    }

    entity = sbctr->fp_entity & 0x3;
    fp = (sbctr->fp_entity >> 4) & 0x1;
    tc_vec = be64_to_cpu(sbctr->tc_vec);

    if (entity == 0) { /* entity is port tc */
        /* Update DB only upon port_tc event */
        spin_lock_irqsave(&priv->db_lock, flags);
        old_tc_vec = priv->tele_thrs_tc_vec[sbctr->local_port];
        priv->tele_thrs_tc_vec[sbctr->local_port] = tc_vec;
        port_state = priv->tele_thrs_state[sbctr->local_port];
        spin_unlock_irqrestore(&priv->db_lock, flags);

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
             * Low 32 bits keeps TCs value */
            new_tc_vec = ((old_tc_vec ^ tc_vec) << 32) | (tc_vec & 0xFFFF);

            /* re-write the event */
            sbctr->tc_vec = cpu_to_be64(new_tc_vec);
        }
    } else if ((entity == 1) && (fp == 1)) {
        /* Port maybe congested event */
        maybe_flag = 1;
    }

    /* Update port state field */
    spin_lock_irqsave(&priv->db_lock, flags);
    if (maybe_flag) {
        SX_TELE_THRS_MAYBE_SET(priv->tele_thrs_state[sbctr->local_port]);
    } else {
        SX_TELE_THRS_MAYBE_CLR(priv->tele_thrs_state[sbctr->local_port]);
    }
    SX_TELE_THRS_FIRST_EVENT_SET(priv->tele_thrs_state[sbctr->local_port]);
    spin_unlock_irqrestore(&priv->db_lock, flags);
}

static void sx_parse_event(struct completion_info *ci)
{
    ci->info.dont_care.drop_enable = 0;

    switch (ci->hw_synd) {
    case SXD_TRAP_ID_PPBME:
        sx_handle_ppbme_event(ci);
        break;

    case SXD_TRAP_ID_SB_CONG_TX_PORT:
        sx_handle_sbctr_event(ci);
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
static int is_port_Vlan_matching(struct completion_info *ci, struct listener_port_vlan_entry *listener)
{
    switch (listener->match_crit) {
    case PORT_VLAN_MATCH_GLOBAL:
        COUNTER_INC(&listener->counters.listener_port_vlan.accepted.global);
        break;

    case PORT_VLAN_MATCH_PORT_VALID:
        if (ci->sysport != listener->sysport) {
            COUNTER_INC(&listener->counters.listener_port_vlan.mismtach.sysport);
            return 0;
        }

        COUNTER_INC(&listener->counters.listener_port_vlan.accepted.sysport);
        break;

    case PORT_VLAN_MATCH_LAG_VALID:
        if (!(ci->is_lag) || (ci->sysport != listener->lag_id)) {
            COUNTER_INC(&listener->counters.listener_port_vlan.mismtach.lag);
            return 0;
        }

        COUNTER_INC(&listener->counters.listener_port_vlan.accepted.lag);
        break;

    case PORT_VLAN_MATCH_VLAN_VALID:
        if (ci->vid != listener->vlan) {
            COUNTER_INC(&listener->counters.listener_port_vlan.mismtach.vlan);
            return 0;
        }

        COUNTER_INC(&listener->counters.listener_port_vlan.accepted.vlan);
        break;
    }

    return 1;
}

static int is_matching(struct completion_info          *ci,
                       struct listener_port_vlan_entry *listener_port_vlan,
                       struct listener_entry           *listener)
{
    if ((listener->swid != ci->swid) &&
        (listener->swid != SWID_NUM_DONT_CARE)) {
        COUNTER_INC(&listener_port_vlan->counters.listener.mismatch.common.swid);
        return 0;
    }

    /* If the packet came from a user (loopback), don't return it to the same user */
    if ((ci->context != NULL) && (listener->context == ci->context)) {
        COUNTER_INC(&listener_port_vlan->counters.listener.mismatch.common.context);
        return 0;
    }

    switch (listener->listener_type) {
    case L2_TYPE_DONT_CARE:
        if (listener->critireas.dont_care.drop_enable && ci->info.dont_care.drop_enable) {
            break;
        }

        if (listener->critireas.dont_care.sysport ==
            SYSPORT_DONT_CARE_VALUE) {
            COUNTER_INC(&listener_port_vlan->counters.listener.accepted.l2_dont_care);
            return 1;
        }

        /* LAGs will also work in the same way */
        if (ci->sysport != listener->critireas.dont_care.sysport) {
            COUNTER_INC(&listener_port_vlan->counters.listener.mismatch.l2_dont_care.sysport);
            break;
        }

        COUNTER_INC(&listener_port_vlan->counters.listener.accepted.l2_dont_care);
        return 1;

    case L2_TYPE_ETH:
        if ((ci->pkt_type != PKT_TYPE_ETH) &&
            (ci->pkt_type != PKT_TYPE_FCoETH)) {
            COUNTER_INC(&listener_port_vlan->counters.listener.mismatch.l2_eth.no_eth);
            break;
        }

        if ((ci->info.eth.ethtype != listener->critireas.eth.ethtype) &&
            (listener->critireas.eth.ethtype !=
             ETHTYPE_DONT_CARE_VALUE)) {
            COUNTER_INC(&listener_port_vlan->counters.listener.mismatch.l2_eth.ethtype);
            break;
        }

        if ((ci->info.eth.dmac != listener->critireas.eth.dmac)
            && (listener->critireas.eth.dmac !=
                DMAC_DONT_CARE_VALUE)) {
            COUNTER_INC(&listener_port_vlan->counters.listener.mismatch.l2_eth.dmac);
            break;
        }

        if ((listener->critireas.eth.emad_tid != TID_DONT_CARE_VALUE) &&
            (ci->info.eth.emad_tid !=
             listener->critireas.eth.emad_tid)) {
            COUNTER_INC(&listener_port_vlan->counters.listener.mismatch.l2_eth.emad_tid);
            break;
        }

        if ((listener->critireas.eth.from_rp != IS_RP_DONT_CARE_E) &&
            (ci->info.eth.from_rp != listener->critireas.eth.from_rp)) {
            COUNTER_INC(&listener_port_vlan->counters.listener.mismatch.l2_eth.from_rp);
            break;
        }

        if ((listener->critireas.eth.from_bridge != IS_BRIDGE_DONT_CARE_E) &&
            (ci->info.eth.from_bridge != listener->critireas.eth.from_bridge)) {
            COUNTER_INC(&listener_port_vlan->counters.listener.mismatch.l2_eth.from_bridge);
            break;
        }

        COUNTER_INC(&listener_port_vlan->counters.listener.accepted.l2_eth);
        return 1;

    case L2_TYPE_IB:
        /* TODO: IB Raw packets have no IB header at all so they
         * need a special handling */
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
                COUNTER_INC(&listener_port_vlan->counters.listener.accepted.l2_ib);
                return 1;
            }

            COUNTER_INC(&listener_port_vlan->counters.listener.mismatch.l2_ib.qpn);
        } else {
            COUNTER_INC(&listener_port_vlan->counters.listener.mismatch.l2_ib.no_ib);
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
    struct listener_entry           *listener;
    struct listener_port_vlan_entry *port_vlan_listener;
    struct list_head                *pos;
    struct list_head                *port_vlan_pos;
    unsigned long                    flags;
    cq_handler                       listener_handler; /*The completion handler*/
    void                            *listener_context; /*to pass to the handler*/
    int                              num_found = 0;
    u8                               is_default;

    /* validate the syndrome range */
    if (entry > NUM_HW_SYNDROMES) {
        printk(KERN_ERR PFX "Error: arrived synd %d is out of range (1..%d) \n",
               entry, NUM_HW_SYNDROMES);
        return -1;
    }

    spin_lock_irqsave(&sx_glb.listeners_lock, flags);
    /* Checking syndrome registration and NUM_HW_SYNDROMES callback iff dispatch_default set */
    /* I don't like the syndrome dispatchers at all, but it's too late to change */
    while (1) {
        if (!list_empty(&sx_glb.listeners_db[entry].list)) {
            list_for_each(port_vlan_pos, &sx_glb.listeners_db[entry].list) {
                port_vlan_listener = list_entry(port_vlan_pos, struct listener_port_vlan_entry, list);
                if (is_port_Vlan_matching(ci, port_vlan_listener)) {
                    list_for_each(pos, &(port_vlan_listener->listener.list)) {
                        listener = list_entry(pos, struct listener_entry, list);

                        if (listener->is_default && (num_found == 0)) {
                            COUNTER_INC(&port_vlan_listener->counters.listener.accepted.def);
                            is_default = 1;
                        } else {
                            is_default = 0;
                        }

                        if (is_default || is_matching(ci, port_vlan_listener, listener)) {
                            listener_handler = listener->handler;
                            listener_context = listener->context;
                            listener_handler(ci, listener_context);
                            listener->rx_pkts++;
                            ++num_found;
                        }
                    }
                }
            }
        }
        if (!dispatch_default || (entry == NUM_HW_SYNDROMES)) {
            break;
        }
        entry = NUM_HW_SYNDROMES;
    }
    spin_unlock_irqrestore(&sx_glb.listeners_lock, flags);

    if (num_found == 0) {
        inc_unconsumed_packets_counter(dev, ci->hw_synd, ci->pkt_type);
    }

    return num_found;
}


static int chk_completion_info(struct completion_info *ci)
{
    int err = 0;

    if ((ci->swid >= NUMBER_OF_SWIDS) && (ci->swid != SWID_NUM_DONT_CARE)) {
        err = -EINVAL;
#ifdef SX_DEBUG
        if (printk_ratelimit()) {
            printk(KERN_DEBUG PFX "The given cqe is not valid: " \
                   " swid=[%d]\n", ci->swid);
        }
#endif
    }

    if (ci->hw_synd > NUM_HW_SYNDROMES) {
        err = -EINVAL;
#ifdef SX_DEBUG
        if (printk_ratelimit()) {
            printk(KERN_DEBUG PFX "The given cqe is not valid: " \
                   "hw_synd=[%d]\n", ci->hw_synd);
        }
#endif
    }

    return err;
}

int rx_ptp_trap_handler(struct sx_priv *priv, struct completion_info *ci, int cqn)
{
    int                       err = 0;
    struct ptp_rx_event_data *rx_ptp_event;
    u8                        need_timestamp;
    u16                       ptp_evt_seqid = 0;
    u8                        ptp_domain_num = 0, ptp_msg_type = 0;
    u16                       lag_id = 0, sysport = 0;

    /* PTP L2 Peer to Peer packets received with LLDP trap */
    if ((ci->hw_synd == PTP_EVENT_PTP0_TRAP_ID) || (ci->hw_synd == PTP_GENERAL_PTP1_TRAP_ID) ||
        (ci->hw_synd == ETH_L2_LLDP_TRAP_ID)) {
        atomic64_inc(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_TOTAL]);

        err = sx_ptp_pkt_parse(ci->skb, NULL, &ptp_evt_seqid, &ptp_domain_num, &ptp_msg_type);
        if (err) {
            if (ci->hw_synd == PTP_EVENT_PTP0_TRAP_ID) {
                err = -EINVAL;
                printk(KERN_ERR PFX "Failed to parse ptp packet(). err: %d \n", err);
            }

            goto dispatch;
        }

        if (ci->is_lag) {
            lag_id = ci->sysport;
            sysport = priv->lag_member_to_local_db[lag_id][ci->lag_subport];
        } else {
            sysport = ci->sysport;
        }

        /*  with LLDP trap ptp general messages should be dispatch without timestamp */
        if (((u16)(1 << ptp_msg_type) & PTP_MSG_GENERAL_ALL) && (ci->hw_synd == ETH_L2_LLDP_TRAP_ID)) {
            need_timestamp = 0;
        } else if (ci->hw_synd == PTP_GENERAL_PTP1_TRAP_ID) {
            need_timestamp = 0;
        } else {
            need_timestamp = 1;

            if (atomic64_dec_return(&ptp_rx_budget[sysport]) < 0) {
                /* no more budget for this RX PTP packet! */
                atomic64_inc(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_RATE_LIMIT]);
            }

            atomic64_inc(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_NEED_TIMESTAMP]);
        }

        priv->ptp_cqn = cqn;

        rx_ptp_event = ptp_allocate_rx_event_data(GFP_ATOMIC);
        if (!rx_ptp_event) {
            atomic64_inc(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_OUT_OF_MEMORY]);
            goto out;
        }

        INIT_LIST_HEAD(&rx_ptp_event->common.list);
        rx_ptp_event->common.sequence_id = ptp_evt_seqid;
        rx_ptp_event->common.domain_num = ptp_domain_num;
        rx_ptp_event->common.msg_type = ptp_msg_type;
        rx_ptp_event->common.need_timestamp = need_timestamp;
        rx_ptp_event->common.since = jiffies;
        rx_ptp_event->ci = ci;

        spin_lock_bh(&ptp_rx_db.sysport_lock[sysport]);
        list_add_tail(&rx_ptp_event->common.list, &ptp_rx_db.sysport_events_list[sysport]);
        atomic64_inc(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_PENDING_EVENTS]);

        if (!need_timestamp) {
            ptp_dequeue_general_messages(sysport, &ptp_rx_db);
        } else if (IS_PTP_MODE_POLLING) {
            up(&ptp_polling_sem);
        }

        spin_unlock_bh(&ptp_rx_db.sysport_lock[sysport]);

        return 0;
    }

#define MTPPTR_OFFSET (0x24)

    if (ci->hw_synd == PTP_ING_PTP_TRAP_ID) {
        atomic64_inc(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_FIFO_TRAP]);
        if (IS_PTP_MODE_EVENTS) {
            ptp_lookup_event(ci->skb->data + MTPPTR_OFFSET, &ptp_rx_db);
        }

        goto out;
    }

    if (ci->hw_synd == PTP_EGR_PTP_TRAP_ID) {
        atomic64_inc(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_FIFO_TRAP]);
        ptp_lookup_event(ci->skb->data + MTPPTR_OFFSET, &ptp_tx_db);

        goto out;
    }

dispatch:
    dispatch_pkt(&priv->dev, ci, ci->hw_synd, 1);

out:
    sx_skb_free(ci->skb);
    kfree(ci);

    return err;
}

#if defined(PD_BU)
/* Part of the PUDE WA for MLNX OS (PUDE events are handled manually):
 * - should be removed before Phoenix bring up;
 * - skip UP PUDE event on the port if port admin status is DOWN;
 */
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
            printk(KERN_DEBUG PFX "Skipping PUDE [%d] event for port [%d] - admin status: %d \n",
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
#endif

/*
 * extracts the needed data from the cqe and from the packet, calls
 * the filter listeners with that info
 */
int rx_skb(void                  *context,
           struct sk_buff        *skb,
           union sx_cqe          *u_cqe,
           const struct timespec *timestamp,
           int                    is_from_monitor_rdq,
           struct listener_entry* force_listener)
{
    struct completion_info *ci = NULL;
    struct sx_priv         *priv = sx_priv((struct sx_dev *)context);
    u16                     hw_synd = 0;
    int                     err = 0;
    u8                      dqn = 0, cqn = 0;
    u16                     truncate_size = 0;
    u8                      crc_present = 0;
    struct sx_dev         * sx_device = (struct sx_dev *)context;
    u8                      swid = 0;
    u8                      is_from_rp = IS_RP_DONT_CARE_E;
    u16                     fid = 0;
    u8                      is_isx = 0;
    u16                     byte_count = 0;
    u16                     mad_attr_id;

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX "rx_skb: Entered function\n");

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
        goto out_free_skb;
    }

    /* Get trap_id, is_isx, byte_count, dqn, vlan, crc_present */
    priv->dev_specific_cb.sx_fill_params_from_cqe_cb(u_cqe,
                                                     &hw_synd,
                                                     &is_isx,
                                                     &byte_count,
                                                     &dqn,
                                                     &crc_present);

    __sx_core_dev_specific_cb_release_reference(sx_device);

    /* TODO: WA because LP packets return with hw_synd = 0 */
    if (!hw_synd) {
        hw_synd = 1;
#ifdef SX_DEBUG
        printk(KERN_DEBUG PFX "Got a packet with trap_id==0, "
               "probably a LP response\n");
#endif
    }

    /* update skb->len to the real len,
     * instead of the max len we allocated */
    skb->len = byte_count;
    /* TODO: remove this check in the future. ISX bit means ISX header is present */
    if (is_isx) {
        skb->data += ISX_HDR_SIZE;
        skb->len -= ISX_HDR_SIZE;
#ifdef SX_DEBUG
        printk(KERN_DEBUG PFX "Got a packet with ISX header\n");
#endif
    }

    ci->skb = skb;
    ci->context = NULL;
    ci->dev = sx_device;
    ci->hw_synd = hw_synd;

#if defined(PD_BU)
    /* Part of the PUDE WA for MLNX OS (PUDE events are handled manually):
     * - should be removed before Phoenix bring up */
    if (__verify_hw_synd(priv, ci) != 0) {
        goto out;
    }
#endif

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
        printk(KERN_DEBUG PFX "rx_skb() pkt_type:%d, hw_synd:%d is_lag:%d, sysport:0x%x, "
               "old_swid:%d, new_swid: %d\n", ci->pkt_type, ci->hw_synd, ci->is_lag,
               ci->sysport, ci->swid, swid);
#endif

        ci->swid = swid;
    } else if ((ci->swid < NUMBER_OF_SWIDS) &&
               (sx_device->profile.swid_type[ci->swid] == SX_KU_L2_TYPE_ROUTER_PORT)) {
        /* if event arrived from Router Port Swid forward it to swid 0 (Default ETH swid) */
        ci->swid = 0;
    }

    ci->has_timestamp = (timestamp != NULL);
    if (ci->has_timestamp) {
        memcpy(&ci->timestamp, timestamp, sizeof(ci->timestamp));
    }

    sx_core_skb_hook_rx_call(sx_device, skb);

    if (rx_debug &&
        ((rx_debug_pkt_type == SX_DBG_PACKET_TYPE_ANY) ||
         (rx_debug_pkt_type == ci->hw_synd)) &&
        ((rx_debug_emad_type == SX_DBG_EMAD_TYPE_ANY) ||
         (rx_debug_emad_type ==
          be16_to_cpu(((struct sx_emad *)skb->data)->emad_op.register_id)))) {
        if (rx_cqev2_dbg) {
            __sx_core_dev_specific_cb_get_reference(sx_device);
            priv->dev_specific_cb.sx_printk_cqe_cb(u_cqe);
            __sx_core_dev_specific_cb_release_reference(sx_device);
        }

        printk(KERN_DEBUG PFX "rx_skb: swid = %d, "
               "sysport = %d, hw_synd = %d (reg_id: 0x%x),"
               "pkt_type = %d, byte_count = %d, is_lag: %d\n",
               ci->swid, ci->sysport, ci->hw_synd,
               be16_to_cpu(((struct sx_emad *)skb->data)->emad_op.register_id),
               ci->pkt_type, skb->len, ci->is_lag);
        printk(KERN_DEBUG PFX "rx_skb: dest sysport:%#x, dest is_lag:%d, dest lag_subport:%d user_def_val:%#08x\n",
               ci->dest_sysport, ci->dest_is_lag, ci->dest_lag_subport, ci->user_def_val);

        if (rx_dump) {
            int i;
            u8 *buf = (void*)skb->data;
            int cnt = skb->len;

            for (i = 0; i < cnt; i++) {
                if ((i == 0) || (i % 4 == 0)) {
                    printk("\n0x%04x : ", i);
                }

                printk(" 0x%02x", buf[i]);
            }

            printk("\n");
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

    sx_glb.stats.rx_by_pkt_type[ci->swid][ci->pkt_type]++;
    sx_glb.stats.rx_by_synd[ci->swid][ci->hw_synd]++;
    sx_glb.stats.rx_by_synd_bytes[ci->swid][ci->hw_synd] += skb->len;

    if (ci->swid < NUMBER_OF_SWIDS) {
        sx_device->stats.rx_by_pkt_type[ci->swid][ci->pkt_type]++;
        sx_device->stats.rx_by_synd[ci->swid][ci->hw_synd]++;
        sx_device->stats.rx_by_synd_bytes[ci->swid][ci->hw_synd] += skb->len;
    } else {
        sx_device->stats.rx_by_pkt_type[NUMBER_OF_SWIDS][ci->pkt_type]++;
        sx_device->stats.rx_by_synd[NUMBER_OF_SWIDS][ci->hw_synd]++;
        sx_device->stats.rx_by_synd_bytes[NUMBER_OF_SWIDS][ci->hw_synd] += skb->len;
    }

    if (enable_cpu_port_loopback) { /* it's a DEBUG feature */
        if (((ci->sysport != 0) || (ci->is_lag != 0)) && !is_from_monitor_rdq) {
            /*put the original packet size before truncation in the completion info*/
            ci->original_packet_size = skb->len;

            truncate_size = get_truncate_size_from_db((struct sx_dev *)context, dqn);
            if ((truncate_size > 0) && (truncate_size < skb->len)) {
                skb->len = truncate_size;
            }

            if (crc_present) {
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
    if ((ci->sysport == 0) && (ci->is_lag == 0)) {
        sx_parse_event(ci);
    }

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
        if (crc_present) {
            ci->original_packet_size -= ETH_CRC_LENGTH;
        }
        if (crc_present && !truncate_size) {
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

    case PKT_TYPE_IB_Raw: /* TODO: Extract qpn from IB Raw pkts */
    case PKT_TYPE_IB_non_Raw:
    case PKT_TYPE_FCoIB:
    case PKT_TYPE_ETHoIB:
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

        ci->info.ib.qpn = get_qpn(hw_synd, skb);
        if (ci->info.ib.qpn == 0xffffffff) {
            if (printk_ratelimit()) {
                printk(KERN_WARNING PFX "Received IB packet "
                       "is not valid. Dropping the packet\n");
            }
            err = -EINVAL;
            goto out;
        }

        /* Extract the IB port from the sysport */
        ci->sysport = (ci->sysport >> 4) & 0x7f;
        if (crc_present && !truncate_size) {
            skb->len -= IB_CRC_LENGTH;
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

#ifdef SX_DEBUG
    if (printk_ratelimit()) {
        printk(KERN_DEBUG PFX " rx_skb() received packet data: "
               "skb->len=[%d] sysport=[%d] hw_synd(trap_id)=[%d] "
               "swid=[%d] pkt_type=[%d]\n",
               ci->skb->len, ci->sysport, ci->hw_synd,
               ci->swid, ci->pkt_type);
    }
#endif

    if (priv->tstamp.is_ptp_enable && !is_from_monitor_rdq) {
        cqn = dqn + NUMBER_OF_SDQS;
        err = rx_ptp_trap_handler(priv, ci, cqn);
        return err;
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
        sx_skb_free(skb);
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

    pci_dma_sync_single_for_cpu(dq->dev->pdev,
                                dq->sge[idx].hdr_pld_sg.dma_addr,
                                dq->sge[idx].hdr_pld_sg.len, dir);
    pci_unmap_single(dq->dev->pdev,
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
            pci_dma_sync_single_for_cpu(dq->dev->pdev,
                                        dq->sge[idx].pld_sg_1.dma_addr,
                                        dq->sge[idx].pld_sg_1.len, dir);
            pci_unmap_single(dq->dev->pdev,
                             dq->sge[idx].pld_sg_1.dma_addr,
                             dq->sge[idx].pld_sg_1.len, dir);
            dq->sge[idx].pld_sg_1.vaddr = NULL;
            dq->sge[idx].pld_sg_1.len = 0;
        }

        if (dq->sge[idx].pld_sg_2.len) {
            pci_dma_sync_single_for_cpu(dq->dev->pdev,
                                        dq->sge[idx].pld_sg_2.dma_addr,
                                        dq->sge[idx].pld_sg_2.len, dir);
            pci_unmap_single(dq->dev->pdev,
                             dq->sge[idx].pld_sg_2.dma_addr,
                             dq->sge[idx].pld_sg_2.len, dir);
            dq->sge[idx].pld_sg_2.vaddr = NULL;
            dq->sge[idx].pld_sg_2.len = 0;
        }
    }
}

static int post_skb(struct sx_dq *dq)
{
    u16             size = dq->dev->profile.rdq_properties[dq->dqn].entry_size;
    int             err = 0;
    struct sk_buff *new_skb;

    new_skb = alloc_skb(size, GFP_ATOMIC);
    if (!new_skb) {
        err = -ENOMEM;
        goto out;
    }

    if (skb_put(new_skb, size) == NULL) {
        err = -ENOMEM;
        goto out;
    }

    sx_core_post_recv(dq, new_skb);

out:
    return err;
}

void sx_fill_poll_one_params_from_cqe_v0(union sx_cqe *u_cqe,
                                         u16          *trap_id,
                                         u8           *is_err,
                                         u8           *is_send,
                                         u8           *dqn,
                                         u16          *wqe_counter,
                                         u16          *byte_count)
{
    *dqn = (u_cqe->v0->e_sr_dqn_owner >> 1) & SX_CQE_DQN_MASK;
    if (be16_to_cpu(u_cqe->v0->dqn5_byte_count) & SX_CQE_DQN_MSB_MASK) {
        *dqn |= (1 << SX_CQE_DQN_MSB_SHIFT);
    }
    *is_err = !!(u_cqe->v0->e_sr_dqn_owner & SX_CQE_IS_ERR_MASK);
    *is_send = !!(u_cqe->v0->e_sr_dqn_owner & SX_CQE_IS_SEND_MASK);
    *wqe_counter = be16_to_cpu(u_cqe->v0->wqe_counter);
    *trap_id = u_cqe->v0->trap_id & 0xFF;
    *byte_count = be16_to_cpu(u_cqe->v0->dqn5_byte_count) & 0x3FFF;
}

void sx_fill_poll_one_params_from_cqe_v1(union sx_cqe *u_cqe,
                                         u16          *trap_id,
                                         u8           *is_err,
                                         u8           *is_send,
                                         u8           *dqn,
                                         u16          *wqe_counter,
                                         u16          *byte_count)
{
    *dqn = (u_cqe->v1->dqn_owner >> 1) & 0x3F;
    *is_err = !!(u_cqe->v1->version_e_sr_packet_ok_rp_lag & 0x8);
    *is_send = !!(u_cqe->v1->version_e_sr_packet_ok_rp_lag & 0x4);
    *wqe_counter = be16_to_cpu(u_cqe->v1->wqe_counter);
    *trap_id = be16_to_cpu(u_cqe->v1->sma_check_id_trap_id) & 0x3FF;
    *byte_count = be16_to_cpu(u_cqe->v1->isx_ulp_crc_byte_count) & 0x3FFF;
}

void sx_fill_poll_one_params_from_cqe_v2(union sx_cqe *u_cqe,
                                         u16          *trap_id,
                                         u8           *is_err,
                                         u8           *is_send,
                                         u8           *dqn,
                                         u16          *wqe_counter,
                                         u16          *byte_count)
{
    *dqn = (u_cqe->v2->dqn >> 1) & 0x3F;
    *is_err = !!(u_cqe->v2->version_e_sr_packet_ok_rp_lag & 0x8);
    *is_send = !!(u_cqe->v2->version_e_sr_packet_ok_rp_lag & 0x4);
    *wqe_counter = be16_to_cpu(u_cqe->v2->wqe_counter);
    *trap_id = be16_to_cpu(u_cqe->v2->sma_check_id_trap_id) & 0x3FF;
    *byte_count = be16_to_cpu(u_cqe->v2->isx_ulp_crc_byte_count) & 0x3FFF;
}

static int sx_poll_one(struct sx_cq *cq, const struct timespec *timestamp)
{
    union sx_cqe    u_cqe = {.v0 = NULL, .v1 = NULL, .v2 = NULL};
    u8              dqn = 0;
    u8              is_send = 0;
    u8              is_err = 0;
    struct sx_dq   *dq;
    struct sk_buff *skb;
    int             err = 0;
    struct sx_priv *priv = sx_priv(cq->sx_dev);
    u16             wqe_ctr = 0;
    u16             idx = 0;
    u16             wqe_counter = 0;
    u16             trap_id = 0;
    u16             byte_count = 0;
    unsigned long   flags;
    uint8_t         rdq_num = 0;

    spin_lock_irqsave(&cq->lock, flags);
    cq->sx_next_cqe_cb(cq, &u_cqe);
    if (!u_cqe.v0 && !u_cqe.v1 && !u_cqe.v2) {
        spin_unlock_irqrestore(&cq->lock, flags);
        return -EAGAIN;
    }

    ++cq->cons_index;
    spin_unlock_irqrestore(&cq->lock, flags);

    /*
     * Make sure we read CQ entry contents after we've checked the
     * ownership bit.
     */
    rmb();


    cq->sx_fill_poll_one_params_from_cqe_cb(&u_cqe, &trap_id, &is_err, &is_send, &dqn, &wqe_counter, &byte_count);

    if (is_send) {
        if (dqn >= NUMBER_OF_SDQS) {
            sx_warn(cq->sx_dev, "dqn %d is larger than max SDQ %d.\n",
                    dqn, NUMBER_OF_SDQS);
            return 0;
        }
    } else {
        err = sx_core_get_rdq_num_max(&(priv->dev), &rdq_num);
        if (err) {
            printk(KERN_ERR PFX "Error: failed to get max RDQ num\n");
            return err;
        }

        if (dqn >= rdq_num) {
            sx_warn(cq->sx_dev, "dqn %d is larger than max RDQ %d.\n",
                    dqn, rdq_num);
            return 0;
        }
    }
    dq = is_send ? priv->sdq_table.dq[dqn] : priv->rdq_table.dq[dqn];

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX "sx_poll_one: dqn = %d, is_err = %d, "
           "is_send = %d\n", dqn, is_err, is_send);
#endif

    if (!dq) {
        if (printk_ratelimit()) {
            sx_warn(cq->sx_dev, "could not find dq context for %s "
                    "dqn = %d\n",
                    is_send ? "send" : "recv", dqn);
        }

        return 0;
    }

    wqe_ctr = wqe_counter & (dq->wqe_cnt - 1);
    if (is_err && !dq->is_flushing) {
        sx_warn(cq->sx_dev, "got %s completion with error, "
                "syndrom=0x%x\n",
                is_send ? "send" : "recv", trap_id);

        if (!is_send) {
            idx = dq->tail++ & (dq->wqe_cnt - 1);
            dq->last_completion = jiffies;
            wqe_sync_for_cpu(dq, idx);
            sx_skb_free(dq->sge[idx].skb);
            dq->sge[idx].skb = NULL;
        }

        goto skip;
    }

    if (is_send) {
        spin_lock_bh(&dq->lock);

        /* find the wqe and unmap the DMA buffer.
         * sx_skb_free to call  the destructor which will signal
         * the write-semaphore for ETH packets, or call gen_completion
         * for IB packets. */
        do {
            idx = dq->tail++ & (dq->wqe_cnt - 1);
            dq->last_completion = jiffies;
            wqe_sync_for_cpu(dq, idx);
            sx_skb_free(dq->sge[idx].skb);
            dq->sge[idx].skb = NULL;
        } while (idx != wqe_ctr);


        if ((0 == cq->sx_dev->global_flushing) && (0 == dq->is_flushing)) {
            sx_add_pkts_to_sdq(dq);
        }

        spin_unlock_bh(&dq->lock);
    } else {
        /* get the skb from the right rdq entry, unmap the buffers
         * and call rx_skb with the cqe and skb */
        /* this while is temporary, we need it because FW doesn't
         * send us error CQes for wqe too short. */
        idx = dq->tail & (dq->wqe_cnt - 1);
        while (idx != wqe_ctr) {
            if (printk_ratelimit()) {
                printk(KERN_DEBUG PFX "sx_poll_one: Err wqe_ctr [%u] != idx [%u] (dq->tail [%u])\n",
                       wqe_ctr, idx, dq->tail);
            }

            dq->tail++; /* increment before sx_core_post_recv()/post_skb() */
            wqe_sync_for_cpu(dq, idx);

            if (dq->is_monitor) {
                sx_core_post_recv(dq, NULL);
            } else {
                sx_skb_free(dq->sge[idx].skb);
                dq->sge[idx].skb = NULL;
                post_skb(dq);
            }

            idx = dq->tail & (dq->wqe_cnt - 1);
        }

        ++dq->tail;
        wqe_sync_for_cpu(dq, idx);
#ifdef SX_DEBUG
        printk(KERN_DEBUG PFX "sx_poll_one: This is a RDQ, idx = %d, "
               "wqe_ctr = %d, dq->tail = %d. "
               "Calling rx_skb\n",
               idx, wqe_ctr, dq->tail - 1);
#endif

        skb = dq->sge[idx].skb;

        /*
         *   For monitor rdq we don't need to send the packet to upper layer and
         *   also not to free the packet in case of error , because the same packet
         *   will be repost_recv
         */
        if (dq->is_monitor) {
            if (enable_monitor_rdq_trace_points) {
                trace_monitor_rdq_rx(skb, trap_id, timestamp);
            }
            goto skip;
        }

        if (!is_err) {
            /* if packet length is less than 2K, let's reallocate it and reassign lower skb->truesize.
             * current skb->truesize is 10K and IP stack accounts for truesize and not for actual buffer size.
             */
            if (byte_count <= 2048) {
                struct sk_buff *new_skb;

                new_skb = skb_clone(skb, GFP_ATOMIC);
                if (new_skb) {
                    new_skb->len = byte_count;
                    new_skb->truesize = roundup_pow_of_two(byte_count);

                    sx_skb_free(skb); /* free original 10K buffer */
                    skb = new_skb; /* use the new buffer that is much lower in size */
                }
            }

            rx_skb(cq->sx_dev, skb, &u_cqe, timestamp, 0, NULL);
        } else {
            sx_skb_free(skb);
        }

        dq->sge[idx].skb = NULL;
    }
skip:
    sx_cq_set_ci(cq);
    if (!is_send && !dq->is_flushing) {
        if (!dq->is_monitor) {
            err = post_skb(dq);
        } else {
            if (timestamp) {
                cq->cqe_ts_arr[idx] = *timestamp;
            }
            /* sx_core_post_recv will repost the same buffer for monitor rdq */
            sx_core_post_recv(dq, NULL);
        }
    }

    if (is_send) {
        wake_up_interruptible(&dq->tx_full_wait);
    }

    return err;
}

/* return errno on error, otherwise num of handled cqes */
int sx_cq_completion(struct sx_dev         *dev,
                     u32                    cqn,
                     u16                    weight,
                     const struct timespec *timestamp,
                     struct sx_bitmap      *prio_bitmap)
{
    struct sx_cq *cq;
    unsigned long flags;
    int           num_of_cqes = 0;
    int           err = 0;

    spin_lock_irqsave(&sx_priv(dev)->cq_table.lock, flags);
    cq = (sx_priv(dev)->cq_table.cq[cqn]);
    spin_unlock_irqrestore(&sx_priv(dev)->cq_table.lock, flags);
    if (!cq) {
        if (printk_ratelimit()) {
            sx_warn(dev, "Completion event for bogus CQ %08x\n", cqn);
        }

        return -EAGAIN;
    }

    if (!sx_bitmap_test(&sx_priv(dev)->cq_table.ts_bitmap, cqn)) {
        timestamp = NULL;
    }

    do {
        err = sx_poll_one(cq, timestamp);
        /* -EAGAIN is the only error where the consumer index is not increased */
        if (err == -EAGAIN) {
            atomic_inc(&cq->bkp_poll_data.curr_num_cq_polls);
        }
    } while (!err && ++num_of_cqes < weight);

    if (num_of_cqes < weight) {
        sx_bitmap_free(prio_bitmap, cqn);
        sx_cq_arm(cq);
    }

    if (!err || (err == -EAGAIN)) {
        return num_of_cqes;
    }

    return err;
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
    tcq->set_ci_db = dev->db_base + SX_DBELL_CQ_CI_OFFSET + 4 * tcq->cqn;
    tcq->arm_db = dev->db_base + SX_DBELL_CQ_ARM_OFFSET + 4 * tcq->cqn;
    tcq->sx_dev = dev;
    tcq->cons_index = 0;
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


void sx_core_destroy_cq(struct sx_dev *dev, struct sx_cq *cq)
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
    err = sx_HW2SW_CQ(dev, cq->cqn);
    if (err) {
        sx_warn(dev, "HW2SW_CQ failed (%d) "
                "for CQN %06x\n", err, cq->cqn);
    }

    synchronize_irq(priv->eq_table.eq[SX_EQ_COMP].irq);
    if (atomic_dec_and_test(&cq->refcount)) {
        complete(&cq->free);
    }
    wait_for_completion(&cq->free);

    if (cq->cqe_ts_arr) {
        vfree(cq->cqe_ts_arr);
    }

    sx_bitmap_free(&cq_table->bitmap, cq->cqn);
    sx_buf_free(dev, cq->nent * cq->cqe_sizeof, &cq->buf);
    kfree(cq);
}


int iterate_active_cqs(struct sx_dev *dev, struct sx_bitmap *active_cq_bitmap)
{
    struct sx_priv  *priv = sx_priv(dev);
    struct timespec *ts;
    int              num_of_cqe_handled;
    int              should_continue_polling = 0;
    int              cqn;
    u16              weight;

    weight = 1 << dev->dev_cap.log_max_sdq_sz;
    for (cqn = 0; cqn < dev->dev_cap.max_num_cqs; cqn++) {
        if (!test_bit(cqn, active_cq_bitmap->table)) {
            continue;
        }

        if (cqn >= NUMBER_OF_SDQS) {
            weight = dev->profile.rdq_properties[cqn - NUMBER_OF_SDQS].rdq_weight;
            ts = &priv->cq_table.timestamps[cqn];
        } else {
            ts = NULL;
        }

        num_of_cqe_handled = sx_cq_completion(dev, cqn, weight, ts, active_cq_bitmap);
        if (num_of_cqe_handled < 0) {
            printk(KERN_WARNING PFX "sx_eq_int: cq_completion failed\n");
        } else if (num_of_cqe_handled == weight) {
            should_continue_polling = 1;
        }
    }

    return should_continue_polling;
}

int __handle_monitor_rdq_completion(struct sx_dev *dev, int dqn)
{
    int                err;
    struct ku_query_cq cq_context;
    static __be16      rx_cnt = 0;
    unsigned long      flags;
    struct sx_cq      *cq;
    struct sx_dq      *rdq;
    int                cqn;
    struct sx_priv    *priv = sx_priv(dev);
    int                i;
    u32                cq_ts_enabled = 0;
    union sx_cqe       u_cqe;
    u8                 dqn1 = 0;
    u8                 is_send = 0;
    u8                 is_err = 0;
    u16                trap_id = 0;
    u16                byte_count = 0;
    u16                wqe_counter = 0;
    int                idx;
    struct sk_buff    *skb;

    spin_lock_irqsave(&priv->rdq_table.lock, flags);
    rdq = priv->rdq_table.dq[dqn];
    spin_unlock_irqrestore(&priv->rdq_table.lock, flags);
    if (rdq == NULL) {
        sx_warn(dev, "Completion event for bogus DQ %08x\n", dqn);
        return -EINVAL;
    }

    /* no need to check cq existence because dq destroyed first */
    cq = rdq->cq;
    cqn = cq->cqn;

    /* read cq producer counter, which indicate the total number of
     * received packets */
    err = sx_QUERY_CQ(dev, cqn, &cq_context);
    if (err) {
        sx_err(dev, "sx_QUERY_CQ failed for cqn %08x\n", cqn);
        return -EINVAL;
    }

    /* valid cqes is cqes between cons_index and producer_index */
    if (cq_context.producer_counter == cq->cons_index) {
        /* No packets was received so
         * arm cq so next time we will be waked up from interrupt */
        rx_cnt = 0;
        sx_cq_arm(cq);
        goto out;
    }

    /* Calculate number of received packets */
    rx_cnt = cq_context.producer_counter - cq->cons_index;

    /* if CQ configured with TS enable add them to each cqe */
    if (sx_bitmap_test(&priv->cq_table.ts_bitmap, cq->cqn)) {
        for (i = cq->cons_index; i < cq_context.producer_counter; i++) {
            cq->cqe_ts_arr[i % cq->nent] = priv->cq_table.timestamps[cq->cqn];
        }
    }

    if (enable_monitor_rdq_trace_points) {
        cq_ts_enabled = sx_bitmap_test(&priv->cq_table.ts_bitmap, cq->cqn);
        for (i = cq->cons_index; i < cq_context.producer_counter; i++) {
            sx_get_cqe_all_versions(cq, i, &u_cqe);
            if (u_cqe.v2 == NULL) {
                continue;
            }
            cq->sx_fill_poll_one_params_from_cqe_cb(&u_cqe, &trap_id, &is_err,
                                                    &is_send, &dqn1, &wqe_counter, &byte_count);

            if (is_send) {
                continue;
            }
            idx = i % rdq->wqe_cnt;
            skb = rdq->sge[idx].skb;
            if (cq_ts_enabled) {
                trace_monitor_rdq_rx(skb, trap_id, &cq->cqe_ts_arr[i % cq->nent]);
            } else {
                trace_monitor_rdq_rx(skb, trap_id, NULL);
            }
        }
    }

    /* simulate we polled all cqes */
    cq->cons_index = cq_context.producer_counter;
    sx_cq_set_ci(cq);

    /* update rdq head and tail */
    rdq->head += rx_cnt;
    rdq->tail += rx_cnt;

    /* Write rdq doorbell */
    wmb();
    __raw_writel((__force u32)cpu_to_be32(rdq->head & 0xffff), rdq->db);
    mmiowb();

    rdq->mon_rx_count += rx_cnt;

    /*
     *  the window [mon_rx_start, mon_rx_start+mon_rx_cnt] should
     *  contains maximum wqe_cnt packets
     */
    if (rdq->mon_rx_count - rdq->mon_rx_start > rdq->wqe_cnt) {
        rdq->mon_rx_start = rdq->mon_rx_count - rdq->wqe_cnt;
    }

out:
    return rx_cnt;
}


static int __monitor_cq_handler_thread(void *arg)
{
    struct sx_dev               *dev = (struct sx_dev*)arg;
    struct cpu_traffic_priority *cpu_traffic_prio = &sx_priv(dev)->cq_table.cpu_traffic_prio;
    int                          should_continue_polling;
    int                          ret;
    int                          i;

    printk(KERN_INFO "starting new device's monitor CQ handler thread\n");

    while (!kthread_should_stop()) {
        ret = down_timeout(&cpu_traffic_prio->monitor_cq_thread_sem, HZ);
        if (ret == -ETIME) {
            continue;
        }

        should_continue_polling = 0;
        for (i = 0; i < sx_priv(dev)->monitor_rdqs_count; i++) {
            ret = __handle_monitor_rdq_completion(dev,
                                                  sx_priv(dev)->monitor_rdqs_arr[i]);
            if (ret > 0) {
                should_continue_polling++;
            }
        }

        if (should_continue_polling) {
            usleep_range(mon_cq_thread_delay_time_usec,
                         mon_cq_thread_delay_time_usec + 5);
            up(&cpu_traffic_prio->monitor_cq_thread_sem); /* re-arm thread loop */
        }
    }

    printk(KERN_INFO "terminating new device's monitor CQ handler thread\n");

    return 0;
}

static int __low_priority_cq_handler_thread(void *arg)
{
    struct sx_dev               *dev = (struct sx_dev*)arg;
    struct cpu_traffic_priority *cpu_traffic_prio = &sx_priv(dev)->cq_table.cpu_traffic_prio;
    int                          should_continue_polling;
    int                          ret;

    printk(KERN_INFO "starting new device's low-priority CQ handler thread\n");

    while (!kthread_should_stop()) {
        ret = down_timeout(&cpu_traffic_prio->low_prio_cq_thread_sem, HZ);
        if (ret == -ETIME) {
            continue;
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

    printk(KERN_INFO "terminating new device's low-priority CQ handler thread\n");

    return 0;
}


static void __sampling_timer_fn(unsigned long data)
{
    struct sx_dev               *dev = (struct sx_dev*)data;
    struct sx_priv              *priv = sx_priv(dev);
    struct cpu_traffic_priority *cpu_traffic_prio = &priv->cq_table.cpu_traffic_prio;

    atomic_set(&cpu_traffic_prio->high_prio_cq_in_load, 0);
    mod_timer(&cpu_traffic_prio->sampling_timer, jiffies + HZ);
}


int __cpu_traffic_priority_init(struct sx_dev *dev, struct cpu_traffic_priority *cpu_traffic_prio)
{
    char            thread_name[32];
    static atomic_t sn = ATOMIC_INIT(0);
    int             err;

    err = sx_bitmap_init(&cpu_traffic_prio->high_prio_cq_bitmap, dev->dev_cap.max_num_cqs);
    if (err) {
        goto out;
    }

    err = sx_bitmap_init(&cpu_traffic_prio->active_high_prio_cq_bitmap, dev->dev_cap.max_num_cqs);
    if (err) {
        goto out;
    }

    err = sx_bitmap_init(&cpu_traffic_prio->active_low_prio_cq_bitmap, dev->dev_cap.max_num_cqs);
    if (err) {
        goto out;
    }

    atomic_set(&cpu_traffic_prio->high_prio_cq_in_load, 0);
    sema_init(&cpu_traffic_prio->low_prio_cq_thread_sem, 0);
    sema_init(&cpu_traffic_prio->monitor_cq_thread_sem, 0);
    init_timer(&cpu_traffic_prio->sampling_timer);

    cpu_traffic_prio->sampling_timer.data = (unsigned long)dev;
    cpu_traffic_prio->sampling_timer.function = __sampling_timer_fn;
    mod_timer(&cpu_traffic_prio->sampling_timer, jiffies + HZ);

    atomic_inc(&sn);
    snprintf(thread_name, sizeof(thread_name), "cq_cpu_prio_%u", atomic_read(&sn));
    cpu_traffic_prio->low_prio_cq_thread = kthread_run(__low_priority_cq_handler_thread, dev, thread_name);
    if (!cpu_traffic_prio->low_prio_cq_thread) {
        printk(KERN_ERR "failed to create low-priority thread\n");
        err = -ENOMEM;
        goto out;
    }

    err = sx_bitmap_init(&sx_priv(dev)->active_monitor_cq_bitmap, dev->dev_cap.max_num_cqs);
    if (err) {
        printk(KERN_ERR PFX "Monitor RDQ bitmap init failed. Aborting...\n");
        goto out;
    }

    snprintf(thread_name, sizeof(thread_name), "mon_cq_handler");
    cpu_traffic_prio->monitor_cq_thread = kthread_run(__monitor_cq_handler_thread, dev, thread_name);
    if (!cpu_traffic_prio->monitor_cq_thread) {
        printk(KERN_ERR "failed to create monitor cq thread\n");
        err = -ENOMEM;
        goto out;
    }

out:

    return err;
}


void __cpu_traffic_priority_deinit(struct sx_dev *dev, struct cpu_traffic_priority *cpu_traffic_prio)
{
    /* clean all monitor cqs so on unload it will be handled in regular way and
     * not by __monitor_cq_handler_thread */
    sx_bitmap_init(&sx_priv(dev)->active_monitor_cq_bitmap, dev->dev_cap.max_num_cqs);

    if (cpu_traffic_prio->monitor_cq_thread) {
        kthread_stop(cpu_traffic_prio->monitor_cq_thread);
        cpu_traffic_prio->monitor_cq_thread = NULL;
    }

    if (cpu_traffic_prio->low_prio_cq_thread) {
        del_timer_sync(&cpu_traffic_prio->sampling_timer);
        kthread_stop(cpu_traffic_prio->low_prio_cq_thread);
        cpu_traffic_prio->low_prio_cq_thread = NULL;
    }
}


int sx_core_init_cq_table(struct sx_dev *dev)
{
    struct sx_cq_table *cq_table = &sx_priv(dev)->cq_table;
    struct sx_cq      **cq_array = NULL;
    int                 err = 0;
    int                 i = 0;
    unsigned long       flags;

    spin_lock_init(&cq_table->lock);

    cq_array = kmalloc(dev->dev_cap.max_num_cqs * sizeof(*cq_array),
                       GFP_KERNEL);
    if (!cq_array) {
        return -ENOMEM;
    }

    for (i = 0; i < dev->dev_cap.max_num_cqs; i++) {
        cq_array[i] = NULL;
    }

    spin_lock_irqsave(&cq_table->lock, flags);
    cq_table->cq = cq_array;
    spin_unlock_irqrestore(&cq_table->lock, flags);
    err = sx_bitmap_init(&cq_table->bitmap, dev->dev_cap.max_num_cqs);
    if (err) {
        return err;
    }

    err = sx_bitmap_init(&cq_table->ts_bitmap, dev->dev_cap.max_num_cqs);
    if (err) {
        return err;
    }

    cq_table->timestamps = kmalloc(sizeof(struct timespec) * dev->dev_cap.max_num_cqs, GFP_KERNEL);
    if (!cq_table->timestamps) {
        err = -ENOMEM;
        goto out;
    }

    err = __cpu_traffic_priority_init(dev, &cq_table->cpu_traffic_prio);

out:
    if (err) {
        kfree(cq_table->timestamps);
        cq_table->timestamps = NULL;
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
}

void sx_core_dump_synd_tbl(struct sx_dev *dev)
{
    struct listener_entry           *listener;
    struct listener_port_vlan_entry *port_vlan_listener;
    struct list_head                *pos;
    struct list_head                *port_vlan_pos;
    unsigned long                    flags;
    u16                              entry = 0;

    spin_lock_irqsave(&sx_glb.listeners_lock, flags);
    for (entry = 0; entry < NUM_HW_SYNDROMES + 1; entry++) {
        if (entry % 100 == 0) {
            udelay(1);
        }
        if (!list_empty(&sx_glb.listeners_db[entry].list)) {
            list_for_each(port_vlan_pos, &sx_glb.listeners_db[entry].list) {
                port_vlan_listener = list_entry(port_vlan_pos, struct listener_port_vlan_entry, list);
                list_for_each(pos, &(port_vlan_listener->listener.list)) {
                    listener = list_entry(pos,
                                          struct listener_entry, list);
                    printk(KERN_DEBUG
                           "=============================\n");
                    printk(KERN_DEBUG
                           "synd=%d, swid=%d, match_crit=%s, port=%d, lag=%d, vlan=%d, is_def:%d, "
                           "handler:%p, rx_pkt:%llu \n",
                           entry,
                           listener->swid,
                           port_vlan_match_str[port_vlan_listener->match_crit],
                           port_vlan_listener->sysport,
                           port_vlan_listener->lag_id,
                           port_vlan_listener->vlan,
                           listener->is_default,
                           listener->handler,
                           listener->rx_pkts);

                    switch (listener->listener_type) {
                    case L2_TYPE_DONT_CARE:
                        printk(KERN_DEBUG "list_type: "
                               "DONT_CARE, crit [port:0x%x] \n",
                               listener->critireas.dont_care.sysport);
                        break;

                    case L2_TYPE_IB:
                        printk(KERN_DEBUG "list_type: IB, crit"
                               " [qpn:0x%x (%d)] \n",
                               listener->critireas.ib.qpn,
                               listener->critireas.ib.qpn);
                        break;

                    case L2_TYPE_ETH:
                        printk(KERN_DEBUG "list_type: ETH, crit "
                               "[ethtype:0x%x, dmac:%llx, "
                               "emad_tid:0x%x, from_rp:%u, from_bridge:%u ] \n",
                               listener->critireas.eth.ethtype,
                               listener->critireas.eth.dmac,
                               listener->critireas.eth.emad_tid,
                               listener->critireas.eth.from_rp,
                               listener->critireas.eth.from_bridge);
                        break;

                    case L2_TYPE_FC:
                        printk(KERN_DEBUG "list_type: FC \n");
                        break;

                    default:
                        printk(KERN_DEBUG "list_type: UNKNOWN \n");
                        break;
                    }
                }
            }
        }
    }

    spin_unlock_irqrestore(&sx_glb.listeners_lock, flags);
}


void sx_cq_show_cq(struct sx_dev *dev, int cqn)
{
    struct sx_priv                     *priv = sx_priv(dev);
    struct sx_cq_table * __maybe_unused cq_table = &priv->cq_table;
    struct sx_cq                       *cq = priv->cq_table.cq[cqn];
    int                                 iii, jjj;
    u8                                  cqe_owner[16];

    if (!cq) {
        printk("cq %d doesn't exist \n", cqn);
        return;
    }

    printk("[cq %d]: cqn:%d, cons_index:%d, nent:%d cons_index&(nent-1):%d"
           " ref_cnt:%d, cqe_version:%d \n",
           cqn,
           cq->cqn,
           cq->cons_index,
           cq->nent,
           (cq->cons_index & (cq->nent - 1)),
           atomic_read(&cq->refcount),
           cq->cqe_version
           );

    printk("CQ %d owner:\n", cqn);
    for (iii = 0; iii < cq->nent / 16; iii++) {
        for (jjj = 0; (jjj < 16) && ((iii * 16 + jjj) < cq->nent); jjj++) {
            cqe_owner[jjj] = cq->sx_get_cqe_owner_cb(cq, (iii * 16 + jjj));
        }
        printk("[%5.5d]: %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x "
               "%2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x\n",
               iii * 16,
               cqe_owner[0], cqe_owner[1], cqe_owner[2], cqe_owner[3],
               cqe_owner[4], cqe_owner[5], cqe_owner[6], cqe_owner[7],
               cqe_owner[8], cqe_owner[9], cqe_owner[10], cqe_owner[11],
               cqe_owner[12], cqe_owner[13], cqe_owner[14], cqe_owner[15]);
    }
    printk("\n");
}

/* Get CQE despite the cqe version */
void sx_get_cqe_all_versions(struct sx_cq *cq, uint32_t n, union sx_cqe *cqe_p)
{
    switch (cq->cqe_version) {
    case 0:
        cqe_p->v0 = sx_get_cqe(cq, n & (cq->nent - 1));

    case 1:
        cqe_p->v1 = sx_get_cqe(cq, n & (cq->nent - 1));

    case 2:
        cqe_p->v2 = sx_get_cqe(cq, n & (cq->nent - 1));
    }

    /* In case the CQ version isn't 0-2 return NULL */
}

void sx_cq_flush_rdq(struct sx_dev *dev, int dqn)
{
    int                 iii;
    int                 idx;
    struct sx_priv     *priv = sx_priv(dev);
    struct sx_dq_table *rdq_table = &priv->rdq_table;
    struct sx_dq       *dq = rdq_table->dq[dqn];

    idx = dq->tail & (dq->wqe_cnt - 1);
    for (iii = 0; iii < dq->wqe_cnt; iii++) {
        printk("%s:%d flushing rdq %d sge %d \n", __func__, __LINE__, dqn, idx);
        wqe_sync_for_cpu(dq, idx);
        sx_skb_free(dq->sge[idx].skb);
        dq->sge[idx].skb = NULL;
        dq->tail++;
        idx = dq->tail & (dq->wqe_cnt - 1);
        post_skb(dq);
    }
}

/************************************************
 *                  EOF                         *
 ***********************************************/
