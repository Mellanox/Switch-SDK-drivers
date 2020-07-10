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

    sx_clock_log_init(&__log_tx);
    sx_clock_log_init(&__log_rx);

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

        sx_clock_log_add(&__log_rx, (s64)utc_ts);

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

    sx_clock_log_add(&__log_tx, (s64)utc_ts);

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
