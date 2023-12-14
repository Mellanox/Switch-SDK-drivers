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

#include <linux/types.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <net/sock.h>

#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include <linux/mlx_sx/auto_registers/reg.h>

#include "cq.h"
#include "sx_clock.h"
#include "ptp.h"
#include "dev_db.h"

struct ts_required_entry {
#define PTP_TX_ONE_STEP_MAGIC (0x1a2b3c4d5e6f7890)
    u64 magic; /* validate that the entry actually exists in skb->cb */
    u8  msg_type;
};

static const char * __tx_type_to_str(int tx_type)
{
    static const char *tx_types[] = {
        [HWTSTAMP_TX_OFF] = "Off",
        [HWTSTAMP_TX_ON] = "2-Step",
        [HWTSTAMP_TX_ONESTEP_SYNC] = "1-Step (E2E)",

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
        [HWTSTAMP_TX_ONESTEP_P2P] = "1-Step (P2P)",
#endif
    };

    if ((tx_type >= 0) && (tx_type < (sizeof(tx_types) / sizeof(tx_types[0]))) && (tx_types[tx_type] != NULL)) {
        return tx_types[tx_type];
    }

    return "N/A";
}

int sx_ptp_dev_init_spc2(struct sx_priv *priv, ptp_mode_t ptp_mode)
{
    struct ku_access_mtpcpc_reg mtpcpc;
    struct ku_query_rsrc        cap_fid;
    int                         err, i;

    sx_internal_log_init(&priv->ptp.hwd.spc2.log_rx,
                         10,
                         SX_INTERNAL_LOG_SEVERITY_INFO_E,
                         "ptp_rx");
    sx_internal_log_init(&priv->ptp.hwd.spc2.log_tx,
                         10,
                         SX_INTERNAL_LOG_SEVERITY_INFO_E,
                         "ptp_tx");
    sx_internal_log_init(&priv->ptp.hwd.spc2.log_pps_events,
                         10,
                         SX_INTERNAL_LOG_SEVERITY_INFO_E,
                         "pps_events");

    if (ptp_mode != KU_PTP_MODE_EVENTS) {
        printk(KERN_ERR "invalid PTP mode: %u\n", ptp_mode);
        return -EINVAL;
    }

    priv->ptp.hwd.spc2.global_tx_type = HWTSTAMP_TX_OFF;
    priv->ptp.hwd.spc2.global_tx_msg_type_one_step_bitmap = 0; /* message type bitmap of which time stamp should
                                                                *  not be delivered in socket error queue */

    for (i = 0; i < PTP_COUNTER_SPC2_LAST; i++) {
        atomic64_set(&priv->ptp.hwd.spc2.counters[PTP_PACKET_INGRESS][i], 0);
        atomic64_set(&priv->ptp.hwd.spc2.counters[PTP_PACKET_EGRESS][i], 0);
    }

    /* we need to get CAP_FID in favor of the PTP WA */
    cap_fid.dev_id = priv->dev.device_id;
    cap_fid.rsrc_id = 0x2512; /* CAP_FID */
    err = sx_QUERY_RSRC(&priv->dev, &cap_fid);
    if (err) {
        printk(KERN_ERR "PTP: failed to get max FID\n");
        goto out;
    }

    priv->ptp.hwd.spc2.cap_fid = (u16)cap_fid.rsrc_val;

    memset(&mtpcpc, 0, sizeof(mtpcpc));
    mtpcpc.dev_id = priv->dev.device_id;
    sx_cmd_set_op_tlv(&mtpcpc.op_tlv, MLXSW_MTPCPC_ID, 2);
    mtpcpc.mtpcpc_reg.pport = 0; /* global */
    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(mtpcpc.mtpcpc_reg.local_port,
                                        mtpcpc.mtpcpc_reg.lp_msb,
                                        0); /* reserved when global configuration */
    mtpcpc.mtpcpc_reg.ptp_trap_en = 1;
    mtpcpc.mtpcpc_reg.ing_correction_message_type = 0x3; /* chip-design recommendation: SYNC | DELAY_REQ */
    mtpcpc.mtpcpc_reg.egr_correction_message_type = 0x3; /* chip-design recommendation: SYNC | DELAY_REQ */
    err = sx_ACCESS_REG_MTPCPC(&priv->dev, &mtpcpc);
    if (err) {
        printk(KERN_ERR "failed to configure MTPCPC, err=%d\n", err);
        goto out;
    }

out:
    return err;
}


int sx_ptp_dev_cleanup_spc2(struct sx_priv *priv)
{
    sx_internal_log_deinit(&priv->ptp.hwd.spc2.log_rx);
    sx_internal_log_deinit(&priv->ptp.hwd.spc2.log_tx);
    sx_internal_log_deinit(&priv->ptp.hwd.spc2.log_pps_events);
    return 0;
}


static void __fill_hwtstamp_from_cqe_ts(struct sx_priv *priv,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                                        const struct timespec64     *cqe_ts,
#else
                                        const struct timespec       *cqe_ts,
#endif
                                        struct skb_shared_hwtstamps *hwts)
{
    u64 nsec;

    /* CQE timestamp is already fixed (holds entire UTC, not only 8bit seconds) */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    nsec = timespec64_to_ns(cqe_ts);
#else
    nsec = timespec_to_ns(cqe_ts);
#endif
    sx_clock_fill_hwtstamp_nsec(nsec, hwts);
}


int sx_ptp_rx_handler_spc2(struct sx_priv                      *priv,
                           struct completion_info              *ci,
                           ptp_mode_t                           ptp_mode,
                           const struct sx_ptp_packet_metadata *pkt_meta)
{
    u64 utc_ts;

    if (pkt_meta->timestamp_required) {
        atomic64_inc(&priv->ptp.hwd.spc2.counters[PTP_PACKET_INGRESS][
                         PTP_COUNTER_SPC2_TIMESTAMP_ARRIVED]);

        utc_ts = ((u64)ci->rx_timestamp.timestamp.tv_sec) * NSEC_PER_SEC + ci->rx_timestamp.timestamp.tv_nsec;

        sx_int_log_info(&priv->ptp.hwd.spc2.log_rx, "msg=%-15s   %llu",
                        sx_core_ptp_msg_type_to_str(pkt_meta->pkt_fields.msg_type),
                        utc_ts);

        if (utc_ts != 0) {
            __fill_hwtstamp_from_cqe_ts(priv,
                                        &ci->rx_timestamp.timestamp,
                                        skb_hwtstamps(ci->skb));
        } else {
            atomic64_inc(&priv->ptp.hwd.spc2.counters[PTP_PACKET_INGRESS][
                             PTP_COUNTER_SPC2_EMPTY_TIMESTAMP]);
        }
    }

    return 1; /* this will return to rx_skb() and continue handling packet: dispatch_pkt() and free skb */
}


int sx_ptp_tx_handler_spc2(struct sx_priv *priv, struct sk_buff *skb, const struct sx_ptp_packet_metadata *pkt_meta)
{
    struct ts_required_entry *ts_entry = (struct ts_required_entry*)skb->cb;

    BUILD_BUG_ON(sizeof(struct ts_required_entry) > sizeof(skb->cb));

    if ((1 << pkt_meta->pkt_fields.msg_type) & priv->ptp.hwd.spc2.global_tx_msg_type_one_step_bitmap) {
        /* we use 1-step mode and the message type is in the TX bitmap */
        ts_entry->magic = PTP_TX_ONE_STEP_MAGIC;
    } else {
        ts_entry->magic = 0;
    }

    ts_entry->msg_type = pkt_meta->pkt_fields.msg_type;
    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
int sx_ptp_tx_ts_handler_spc2(struct sx_priv *priv, struct sk_buff *skb, const struct timespec64 *tx_ts)
#else
int sx_ptp_tx_ts_handler_spc2(struct sx_priv *priv, struct sk_buff *skb, const struct timespec *tx_ts)
#endif
{
    struct ts_required_entry   *entry = (struct ts_required_entry*)skb->cb;
    u64                         utc_ts = ((u64)(tx_ts->tv_sec * NSEC_PER_SEC)) + tx_ts->tv_nsec;
    struct skb_shared_hwtstamps hwts;

    if (entry->magic == PTP_TX_ONE_STEP_MAGIC) {
        /* timestamp is delivered by one-step, no need to deliver in socket error queue */
        atomic64_inc(&priv->ptp.hwd.spc2.counters[PTP_PACKET_EGRESS][PTP_COUNTER_SPC2_ONE_STEP_TIMESTAMP_ARRIVED]);
        sx_int_log_info(&priv->ptp.hwd.spc2.log_tx, "msg=%-15s   %llu (one-step)",
                        sx_core_ptp_msg_type_to_str(entry->msg_type),
                        utc_ts);
    } else {
        /* time stamp of TX packet should be delivered in socket error buffer */
        atomic64_inc(&priv->ptp.hwd.spc2.counters[PTP_PACKET_EGRESS][PTP_COUNTER_SPC2_TIMESTAMP_ARRIVED]);
        sx_int_log_info(&priv->ptp.hwd.spc2.log_tx, "msg=%-15s   %llu",
                        sx_core_ptp_msg_type_to_str(entry->msg_type),
                        utc_ts);

        if (utc_ts != 0) {
            __fill_hwtstamp_from_cqe_ts(priv, tx_ts, &hwts);
            skb_tstamp_tx(skb, &hwts);
        } else {
            atomic64_inc(&priv->ptp.hwd.spc2.counters[PTP_PACKET_EGRESS][PTP_COUNTER_SPC2_EMPTY_TIMESTAMP]);
        }
    }

    return 0;
}

int sx_ptp_dump_spc2(struct sx_priv *priv, struct seq_file *m, void *v, void *context)
{
    char tx_1step_bitmap_str[128] = "";
    u8   msg_type;

    seq_printf(m, "%-40s   %-15s   %-15llu\n",
               "TX Control-to-Data WA",
               "N/A",
               (u64)atomic64_read(&priv->ptp.hwd.spc2.counters[PTP_PACKET_EGRESS][PTP_COUNTER_SPC2_TX_WA]));
    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Timestamp arrived",
               (u64)atomic64_read(&priv->ptp.hwd.spc2.counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_SPC2_TIMESTAMP_ARRIVED]),
               (u64)atomic64_read(&priv->ptp.hwd.spc2.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC2_TIMESTAMP_ARRIVED]));
    seq_printf(m, "%-40s   %-15s   %-15llu\n",
               "Timestamp arrived (1-Step)",
               "N/A",
               (u64)atomic64_read(&priv->ptp.hwd.spc2.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC2_ONE_STEP_TIMESTAMP_ARRIVED]));
    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Empty timestamp",
               (u64)atomic64_read(&priv->ptp.hwd.spc2.counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_SPC2_EMPTY_TIMESTAMP]),
               (u64)atomic64_read(&priv->ptp.hwd.spc2.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC2_EMPTY_TIMESTAMP]));

    seq_printf(m, "\n\n");

    for (msg_type = 0; msg_type < 16; msg_type++) {
        if ((1 << msg_type) & priv->ptp.hwd.spc2.global_tx_msg_type_one_step_bitmap) {
            if (tx_1step_bitmap_str[0] != '\0') {
                strcat(tx_1step_bitmap_str, " | ");
            }

            strcat(tx_1step_bitmap_str, sx_core_ptp_msg_type_to_str(msg_type));
        }
    }

    seq_printf(m, "TX stepping mode: %s\n", __tx_type_to_str(priv->ptp.hwd.spc2.global_tx_type));
    seq_printf(m, "TX 1-step message type bitmap = %s\n", tx_1step_bitmap_str);

    seq_printf(m, "\n\n");

    sx_internal_log_dump(&priv->ptp.hwd.spc2.log_tx, m);
    sx_internal_log_dump(&priv->ptp.hwd.spc2.log_rx, m);
    sx_internal_log_dump(&priv->ptp.hwd.spc2.log_pps_events, m);
    sx_internal_log_dump(&priv->ptp.log, m);
    return 0;
}

int sx_ptp_get_supported_tx_types_spc2(struct sx_priv *priv, u32 *tx_types)
{
    *tx_types = (BIT(1) << HWTSTAMP_TX_ON) |
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                (BIT(1) << HWTSTAMP_TX_ONESTEP_P2P) |
#endif
                (BIT(1) << HWTSTAMP_TX_ONESTEP_SYNC);

    return 0;
}

static int __configure_MTPSPU(struct sx_dev *dev, u16 msg_type_bitmap)
{
    struct ku_access_mtpspu_reg mtpspu_reg_data;
    int                         err = 0;

    memset(&mtpspu_reg_data, 0, sizeof(mtpspu_reg_data));
    mtpspu_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mtpspu_reg_data.op_tlv, MTPSPU_REG_ID, 2);
    mtpspu_reg_data.mtpspu_reg.message_type = msg_type_bitmap;
    err = sx_ACCESS_REG_MTPSPU(dev, &mtpspu_reg_data);
    if (err) {
        printk(KERN_ERR "Failed to configure register MTPSPU (msg_type_bitmap = 0x%x)\n", msg_type_bitmap);
    }

    return err;
}

int sx_ptp_set_tx_type_spc2(struct sx_priv *priv, int tx_type)
{
    u16 tx_msg_type_one_step_bitmap = 0;
    int err = 0;

    switch (tx_type) {
    case HWTSTAMP_TX_OFF:
    case HWTSTAMP_TX_ON:           /* 2-Step PTP boundary clock       */
        break;

    case HWTSTAMP_TX_ONESTEP_SYNC: /* 1-Step PTP boundary clock (E2E) */
        tx_msg_type_one_step_bitmap = PTP_MSG_SYNC;
        break;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    case HWTSTAMP_TX_ONESTEP_P2P:  /* 1-Step PTP boundary clock (P2P) */
        tx_msg_type_one_step_bitmap = PTP_MSG_SYNC | PTP_MSG_PDELAY_RESP;
        break;
#endif

    default:
        err = -ERANGE;
        goto out;
    }

    /* nothing to do if configured type is the same as the global one */
    if (tx_type == priv->ptp.hwd.spc2.global_tx_type) {
        goto out;
    }

    printk(KERN_NOTICE "PTP stepping mode is changing from %s to %s\n",
           __tx_type_to_str(priv->ptp.hwd.spc2.global_tx_type), __tx_type_to_str(tx_type));
    sx_int_log_notice(&priv->ptp.log,
                      "PTP stepping mode is changing from %s to %s",
                      __tx_type_to_str(priv->ptp.hwd.spc2.global_tx_type), __tx_type_to_str(tx_type));

    err = __configure_MTPSPU(&priv->dev, tx_msg_type_one_step_bitmap);
    if (err) {
        printk(KERN_ERR "failed to set MTPSPU(0x%x)\n", tx_msg_type_one_step_bitmap);
        sx_int_log_error(&priv->ptp.log,
                         "failed to set MTPSPU(0x%x)", tx_msg_type_one_step_bitmap);
        goto out;
    }

    priv->ptp.hwd.spc2.global_tx_type = tx_type;
    priv->ptp.hwd.spc2.global_tx_msg_type_one_step_bitmap = tx_msg_type_one_step_bitmap;

out:
    return err;
}

int sx_ptp_tx_control_to_data_spc2(struct sx_priv  *priv,
                                   struct sk_buff **orig_skb,
                                   struct isx_meta *meta,
                                   u16              port,
                                   u8               is_lag,
                                   u8              *is_tagged)
{
    struct sx_dev  *dev = &priv->dev;
    struct sk_buff *skb = *orig_skb;
    u16             pvid;
    int             err;

    /* ************************************************************************
     * PTP WA
     *
     * On SPC2/3/4 when PTP is sent as control, HW does not override the 'correction'
     * field on the PTP packet so it remains negative (and invalid). therefore, the
     * WA is to switch the 'Control' packet to 'Data' packet:
     *
     * if packet is 'Control':
     *     Switch to 'Data'
     *     fid = CAP_FID + port - 1
     *     fid_valid = 1
     *     rx_is_router = 1
     *     if packet is untagged:
     *         add VLAN tag with PVID and PCP=6
     * ***********************************************************************/

    /* if PTP is disabled, skip WA */
    if (!sx_ptp_is_enabled(priv)) {
        return 0;
    }

    /* if packet is not 'Control', skip WA */
    if (meta->type != SX_PKT_TYPE_ETH_CTL_UC) {
        return 0;
    }

    /* from this point, WA will be surely applied to the packet */

    /* if packet is untagged, add a VLAN tag with PVID and PCP=6 */
    if (!(*is_tagged)) {
        err = sx_core_get_pvid(dev, port, is_lag, &pvid);
        if (err) {
            return err;
        }

        err = sx_core_skb_add_vlan(&skb, pvid, 6);
        if (err) {
            return err;
        }

        *orig_skb = skb; /* skb may have changed pointer in call to sx_netdev_skb_add_vlan() */
        *is_tagged = 1;
    }

    meta->type = SX_PKT_TYPE_ETH_DATA;
    meta->fid = priv->ptp.hwd.spc2.cap_fid + meta->system_port_mid - 1;  /* see PRM, TX-base-header description */
    meta->fid_valid = 1;
    meta->rx_is_router = 1;

    /* following fields must be reserved when sending as 'DATA': */
    meta->system_port_mid = 0;
    meta->etclass = 0;

    atomic64_inc(&priv->ptp.hwd.spc2.counters[PTP_PACKET_EGRESS][PTP_COUNTER_SPC2_TX_WA]);
    return 0;
}
