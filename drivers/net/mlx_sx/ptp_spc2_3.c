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

#include <linux/types.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <net/sock.h>

#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/cmd.h>

#include "cq.h"
#include "sx_clock.h"
#include "ptp.h"

#define CAP_FID_SPC2_3 ((16 * 1024) - 256) /* 16K - 256 ==> 256 FIDs reserved for SPC2/3 PTP WA */

enum ptp_spc2_counters {
    PTP_COUNTER_SPC2_TIMESTAMP_ARRIVED,
    PTP_COUNTER_SPC2_EMPTY_TIMESTAMP,
    PTP_COUNTER_SPC2_LAST
};
static atomic64_t             __ptp_spc2_counters[2][PTP_COUNTER_SPC2_LAST];
static struct sx_clock_log_db __log_tx;
static struct sx_clock_log_db __log_rx;

int sx_ptp_init_spc2(struct sx_priv *priv, ptp_mode_t ptp_mode)
{
    struct ku_access_mtpcpc_reg mtpcpc;
    int                         err, i;

    sx_clock_log_init(&__log_tx, 10);
    sx_clock_log_init(&__log_rx, 10);

    if (ptp_mode != KU_PTP_MODE_EVENTS) {
        printk(KERN_ERR "invalid PTP mode for SPC2/3: %u\n", ptp_mode);
        return -EINVAL;
    }

    for (i = 0; i < PTP_COUNTER_SPC2_LAST; i++) {
        atomic64_set(&__ptp_spc2_counters[PTP_PACKET_INGRESS][i], 0);
        atomic64_set(&__ptp_spc2_counters[PTP_PACKET_EGRESS][i], 0);
    }

    memset(&mtpcpc, 0, sizeof(mtpcpc));
    mtpcpc.dev_id = priv->dev.device_id;
    sx_cmd_set_op_tlv(&mtpcpc.op_tlv, MTPCPC_REG_ID, 2);
    mtpcpc.mtpcpc_reg.pport = 0; /* global */
    mtpcpc.mtpcpc_reg.local_port = 0; /* reserved when global configuration */
    mtpcpc.mtpcpc_reg.ptp_trap_en = 1;
    mtpcpc.mtpcpc_reg.ing_correction_msg_type = 0x3; /* chip-design recommendation: SYNC | DELAY_REQ */
    mtpcpc.mtpcpc_reg.egr_correction_msg_type = 0x3; /* chip-design recommendation: SYNC | DELAY_REQ */
    err = sx_ACCESS_REG_MTPCPC(&priv->dev, &mtpcpc);
    if (err) {
        printk(KERN_ERR "failed to configure MTPCPC, err=%d\n", err);
    }

    return err;
}


int sx_ptp_cleanup_spc2(struct sx_priv *priv)
{
    sx_clock_log_deinit(&__log_tx);
    sx_clock_log_deinit(&__log_rx);
    return 0;
}


static void __fill_hwtstamp_from_cqe_ts(struct sx_priv              *priv,
                                        const struct timespec       *cqe_ts,
                                        struct skb_shared_hwtstamps *hwts)
{
    u64 nsec;

    /* CQE timestamp is already fixed (holds entire UTC, not only 8bit seconds) */
    nsec = timespec_to_ns(cqe_ts);
    sx_clock_fill_hwtstamp_nsec(nsec, hwts);
}


int sx_ptp_rx_handler_spc2(struct sx_priv                      *priv,
                           struct completion_info              *ci,
                           ptp_mode_t                           ptp_mode,
                           const struct sx_ptp_packet_metadata *pkt_meta)
{
    u64 utc_ts;

    if (pkt_meta->timestamp_required) {
        atomic64_inc(&__ptp_spc2_counters[PTP_PACKET_INGRESS][PTP_COUNTER_SPC2_TIMESTAMP_ARRIVED]);

        utc_ts = ((u64)ci->rx_timestamp.timestamp.tv_sec) * NSEC_PER_SEC + ci->rx_timestamp.timestamp.tv_nsec;

        sx_clock_log_add_s64(&__log_rx, utc_ts);

        if (utc_ts != 0) {
            __fill_hwtstamp_from_cqe_ts(priv,
                                        &ci->rx_timestamp.timestamp,
                                        skb_hwtstamps(ci->skb));
        } else {
            atomic64_inc(&__ptp_spc2_counters[PTP_PACKET_INGRESS][PTP_COUNTER_SPC2_EMPTY_TIMESTAMP]);
        }
    }

    return 1; /* this will return to rx_skb() and continue handling packet: dispatch_pkt() and free skb */
}


int sx_ptp_tx_handler_spc2(struct sx_priv *priv, struct sk_buff *skb, const struct sx_ptp_packet_metadata *pkt_meta)
{
    return 0;
}


int sx_ptp_tx_ts_handler_spc2(struct sx_priv *priv, struct sk_buff *skb, const struct timespec *tx_ts)
{
    struct skb_shared_hwtstamps hwts;
    u64                         utc_ts = ((u64)(tx_ts->tv_sec * NSEC_PER_SEC)) + tx_ts->tv_nsec;

    atomic64_inc(&__ptp_spc2_counters[PTP_PACKET_EGRESS][PTP_COUNTER_SPC2_TIMESTAMP_ARRIVED]);

    sx_clock_log_add_s64(&__log_tx, utc_ts);

    if (utc_ts != 0) {
        __fill_hwtstamp_from_cqe_ts(priv, tx_ts, &hwts);
        skb_tstamp_tx(skb, &hwts);
    } else {
        atomic64_inc(&__ptp_spc2_counters[PTP_PACKET_EGRESS][PTP_COUNTER_SPC2_EMPTY_TIMESTAMP]);
    }

    sock_put(skb->sk);
    return 0;
}


int sx_ptp_dump_spc2(struct seq_file *m, void *v)
{
    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Timestamp arrived",
               (u64)atomic64_read(&__ptp_spc2_counters[PTP_PACKET_INGRESS][PTP_COUNTER_SPC2_TIMESTAMP_ARRIVED]),
               (u64)atomic64_read(&__ptp_spc2_counters[PTP_PACKET_EGRESS][PTP_COUNTER_SPC2_TIMESTAMP_ARRIVED]));
    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Empty timestamp",
               (u64)atomic64_read(&__ptp_spc2_counters[PTP_PACKET_INGRESS][PTP_COUNTER_SPC2_EMPTY_TIMESTAMP]),
               (u64)atomic64_read(&__ptp_spc2_counters[PTP_PACKET_EGRESS][PTP_COUNTER_SPC2_EMPTY_TIMESTAMP]));

    seq_printf(m, "\n\n");

    sx_clock_log_dump(&__log_tx, m, "TX log");
    sx_clock_log_dump(&__log_rx, m, "RX log");

    return 0;
}


int sx_ptp_tx_control_to_data_spc2(struct sx_priv  *priv,
                                   struct sk_buff **orig_skb,
                                   struct isx_meta *meta,
                                   u16              port,
                                   u8               is_lag,
                                   u8              *is_tagged,
                                   u8               hw_ts_required)
{
    struct sx_dev  *dev = &priv->dev;
    struct sk_buff *skb = *orig_skb;
    u8              is_ptp_pkt = hw_ts_required;
    u16             pvid;
    int             err;

    /* ************************************************************************
     * PTP SPC2/3 WA
     *
     * On SPC2/3 when PTP is sent as control, HW does not override the 'correction'
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
    if (!priv->tstamp.is_ptp_enable) {
        return 0;
    }

    /* if packet is not 'Control', skip WA */
    if (meta->type != SX_PKT_TYPE_ETH_CTL_UC) {
        return 0;
    }

    /* if packet does not require timestamp (i.e. not sure if it a PTP packet), check if packet is PTP. */
    if (!hw_ts_required) {
        sx_core_is_ptp_packet(skb, &is_ptp_pkt);

        /* if packet is not PTP, skip WA */
        if (!is_ptp_pkt) {
            return 0;
        }
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
    meta->fid = CAP_FID_SPC2_3 + meta->system_port_mid - 1;  /* see PRM, TX-base-header description */
    meta->fid_valid = 1;
    meta->rx_is_router = 1;

    /* following fields must be reserved when sending as 'DATA': */
    meta->system_port_mid = 0;
    meta->etclass = 0;
    return 0;
}
