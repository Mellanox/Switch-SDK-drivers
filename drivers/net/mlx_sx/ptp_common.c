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

#include <linux/if_vlan.h>
#include <uapi/linux/ip.h>
#include <linux/ipv6.h>
#include <linux/udp.h>
#include <linux/ptp_classify.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/kernel_user.h>
#include "sx.h"
#include "sx_clock.h"
#include "ptp.h"

#define PTP_RX_MAX_PPS_PER_PORT (394)
#define PTP_TX_MAX_PPS_PER_PORT (404)

enum ptp_common_counters {
    PTP_COUNTER_COMMON_TOTAL,
    PTP_COUNTER_COMMON_NEED_TIMESTAMP,
    PTP_COUNTER_COMMON_RATE_LIMIT,
    PTP_COUNTER_COMMON_LAST
};
static struct delayed_work __per_sec_dwork;
static atomic64_t          __ptp_rx_budget[PTP_MAX_PORTS];
static atomic64_t          __ptp_tx_budget[PTP_MAX_PORTS];
static atomic64_t          __ptp_common_counters[2][PTP_COUNTER_COMMON_LAST];
static ptp_mode_t          __ptp_working_mode = KU_PTP_MODE_DISABLED;
static void __ptp_reset_budget(void)
{
    int i;

    for (i = 0; i < PTP_MAX_PORTS; i++) {
        atomic64_set(&__ptp_rx_budget[i], PTP_RX_MAX_PPS_PER_PORT);
    }

    for (i = 0; i < PTP_MAX_PORTS; i++) {
        atomic64_set(&__ptp_tx_budget[i], PTP_TX_MAX_PPS_PER_PORT);
    }
}


/* This function runs once per second */
static void __per_sec(struct work_struct *work)
{
    __ptp_reset_budget();
    sx_clock_queue_delayed_work(&__per_sec_dwork, HZ);
}


static u8 __is_ptp_packet(struct sk_buff *skb, struct sx_ptp_packet_metadata *pkt_meta)
{
    const struct vlan_hdr *vhdr;
    const struct udphdr   *udp;
    const struct iphdr    *ip_hdr;
    const struct ipv6hdr  *ip6_hdr;
    const u8              *data = skb->data;
    u16                    ether_type = be16_to_cpu(((struct ethhdr*)data)->h_proto);
    u32                    offset = 0;
    u8                     is_ptp = 0;

    offset += ETH_HLEN;

    /*PTP_V2_VLAN*/
    if (ether_type == ETH_P_8021Q) {
        vhdr = (struct vlan_hdr *)(data + offset);
        offset += VLAN_HLEN;
        ether_type = be16_to_cpu(vhdr->h_vlan_encapsulated_proto);
    }

    switch (ether_type) {
    case ETH_P_1588: /* PTP_V2_L2 */
        is_ptp = 1;
        break;

    case ETH_P_IP:    /* PTP_V2_IPV4 */
        ip_hdr = (struct iphdr *)(data + offset);
        if (ip_hdr->protocol == IPPROTO_UDP) {
            udp = (struct udphdr *)(data + offset + (ip_hdr->ihl << 2));
            if (be16_to_cpu(udp->dest) == 319) {
                offset += (ip_hdr->ihl << 2) + UDP_HLEN;
                is_ptp = 1;
            }
        }
        break;

    case ETH_P_IPV6:    /*PTP_V2_IPV6*/
        ip6_hdr = (struct ipv6hdr *)(data + offset);
        if (ip6_hdr->nexthdr == IPPROTO_UDP) {
            udp = (struct udphdr *)(data + offset + IP6_HLEN);
            if (be16_to_cpu(udp->dest) == 319) {
                offset += IP6_HLEN + UDP_HLEN;
                is_ptp = 1;
            }
        }
        break;

    default:
        break;
    }

#define OFFSET_PTP_DOMAIN_NUMBER (4)

    if (is_ptp) {
        pkt_meta->seqid = ntohs(*((u16*)(data + offset + OFF_PTP_SEQUENCE_ID)));
        pkt_meta->domain = *(data + offset + OFFSET_PTP_DOMAIN_NUMBER);
        pkt_meta->msg_type = *(data + offset) & 0xf;
    }

    return is_ptp;
}


int sx_core_ptp_rx_handler(struct sx_priv *priv, struct completion_info *ci, int cqn)
{
    struct sx_ptp_packet_metadata pkt_meta;

    switch (ci->hw_synd) {
    case SXD_TRAP_ID_PTP_ING_EVENT:
    case SXD_TRAP_ID_PTP_EGR_EVENT:
        goto ptp_fifo_event;
        break;

    case SXD_TRAP_ID_PTP_PTP0:
    case SXD_TRAP_ID_PTP_PTP1:
    case SXD_TRAP_ID_ETH_L2_LLDP: /* PTP L2 Peer to Peer packets received with LLDP trap */
        if (__is_ptp_packet(ci->skb, &pkt_meta)) {
            goto ptp_packet;
        }

    /* fall through */

    default:
        return -1; /* if we get here, it is not a PTP packet */
    }

ptp_packet:
    atomic64_inc(&__ptp_common_counters[PTP_PACKET_INGRESS][PTP_COUNTER_COMMON_TOTAL]);

    if (ci->is_lag) {
        pkt_meta.sysport_lag_id = priv->lag_member_to_local_db[ci->sysport][ci->lag_subport];
    } else {
        pkt_meta.sysport_lag_id = ci->sysport;
    }

    /*  with LLDP trap ptp general messages should be dispatch without timestamp */
    if (((u16)(1 << pkt_meta.msg_type) & PTP_MSG_GENERAL_ALL) && (ci->hw_synd == SXD_TRAP_ID_ETH_L2_LLDP)) {
        pkt_meta.timestamp_required = 0;
    } else if (ci->hw_synd == SXD_TRAP_ID_PTP_PTP1) {
        pkt_meta.timestamp_required = 0;
    } else {
        pkt_meta.timestamp_required = 1;

        if (atomic64_dec_return(&__ptp_rx_budget[pkt_meta.sysport_lag_id]) < 0) {
            /* no more budget for this RX PTP packet! */
            atomic64_inc(&__ptp_common_counters[PTP_PACKET_INGRESS][PTP_COUNTER_COMMON_RATE_LIMIT]);
        }

        atomic64_inc(&__ptp_common_counters[PTP_PACKET_INGRESS][PTP_COUNTER_COMMON_NEED_TIMESTAMP]);
    }

    priv->ptp_cqn = cqn;

ptp_fifo_event:

    /* handler should take care of deleting 'ci->skb' and 'ci' */
    return SX_CLOCK_DEV_SPECIFIC_CB(&priv->dev, sx_ptp_rx_handler, priv, ci, __ptp_working_mode, &pkt_meta);
}


int sx_core_ptp_tx_handler(struct sx_dev *dev, struct sk_buff *skb, u16 sysport_lag_id, u8 is_lag)
{
    struct sx_priv               *priv = sx_priv(dev);
    struct sx_ptp_packet_metadata pkt_meta;
    u16                           phy_port_max = 0;
    u8                            is_ptp_pkt;
    int                           err;

    if (!sx_priv(dev)->tstamp.is_ptp_enable) {
        return 0;
    }

    pkt_meta.sysport_lag_id = sysport_lag_id;

    if (is_lag) {
        if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
            printk(KERN_ERR PFX "Failed to get max number of phy ports.\n");
            return -EINVAL;
        }

        pkt_meta.sysport_lag_id += phy_port_max;
    }

    is_ptp_pkt = __is_ptp_packet(skb, &pkt_meta);
    if (!is_ptp_pkt) {
        return 0;
    }

    atomic64_inc(&__ptp_common_counters[PTP_PACKET_EGRESS][PTP_COUNTER_COMMON_TOTAL]);

    /*  with ptp general messages should be dispatch without timestamp */
    if (((u16)(1 << pkt_meta.msg_type) & PTP_MSG_GENERAL_ALL)) {
        skb_tstamp_tx(skb, NULL);
        return 0;
    }

    pkt_meta.timestamp_required = 1;

    if (atomic64_dec_return(&__ptp_tx_budget[pkt_meta.sysport_lag_id]) < 0) {
        atomic64_inc(&__ptp_common_counters[PTP_PACKET_EGRESS][PTP_COUNTER_COMMON_RATE_LIMIT]);
    }

    atomic64_inc(&__ptp_common_counters[PTP_PACKET_EGRESS][PTP_COUNTER_COMMON_NEED_TIMESTAMP]);

    skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
    sock_hold(skb->sk);

    err = SX_CLOCK_DEV_SPECIFIC_CB(dev, sx_ptp_tx_handler, priv, skb, &pkt_meta);
    if (err) {
        sock_put(skb->sk);
        kfree_skb(skb);
    }

    return err;
}
EXPORT_SYMBOL(sx_core_ptp_tx_handler);


ptp_mode_t sx_ptp_get_mode(void)
{
    return __ptp_working_mode;
}


int sx_core_get_ptp_state(struct sx_dev *dev, uint8_t *is_ptp_enable)
{
    *is_ptp_enable = sx_priv(dev)->tstamp.is_ptp_enable;
    return 0;
}
EXPORT_SYMBOL(sx_core_get_ptp_state);

int sx_core_get_ptp_clock_index(struct sx_dev *dev, uint8_t *ptp_clock_index_p)
{
    if (sx_priv(dev)->tstamp.is_ptp_enable) {
        *ptp_clock_index_p = ptp_clock_index(sx_priv(dev)->tstamp.ptp);
    }

    return 0;
}
EXPORT_SYMBOL(sx_core_get_ptp_clock_index);


int sx_core_ptp_tx_ts_handler(struct sx_priv *priv, struct sk_buff *skb, const struct timespec *tx_ts)
{
    return SX_CLOCK_DEV_SPECIFIC_CB(&priv->dev, sx_ptp_tx_ts_handler, priv, skb, tx_ts);
}


int sx_core_ptp_init(struct sx_priv *priv, ptp_mode_t ptp_mode)
{
    int                         i = 0, err = 0;
    struct ku_access_mtptpt_reg mtptpt_reg_data;
    struct sx_dev              *dev = &priv->dev;

    if (priv->tstamp.is_ptp_enable) {
        sx_err(dev, "PTP is already initialized!\n");
        err = -EBUSY;
        goto out;
    }

    for (i = 0; i < PTP_COUNTER_COMMON_LAST; i++) {
        atomic64_set(&__ptp_common_counters[PTP_PACKET_INGRESS][i], 0);
        atomic64_set(&__ptp_common_counters[PTP_PACKET_EGRESS][i], 0);
    }

    for (i = 0; i < PTP_MAX_PORTS; i++) {
        atomic64_set(&__ptp_rx_budget[i], 0);
    }

    for (i = 0; i < PTP_MAX_PORTS; i++) {
        atomic64_set(&__ptp_tx_budget[i], 0);
    }

    /* Configure trap PTP0 for event ptp message types */
    memset(&mtptpt_reg_data, 0, sizeof(mtptpt_reg_data));
    mtptpt_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mtptpt_reg_data.op_tlv, MTPTPT_REG_ID, 2);
    mtptpt_reg_data.mtptpt_reg.trap_id = 0;
    mtptpt_reg_data.mtptpt_reg.message_type = PTP_MSG_SYNC |
                                              PTP_MSG_DELAY_REQ | PTP_MSG_PDELAY_REQ | PTP_MSG_PDELAY_RESP;
    err = sx_ACCESS_REG_MTPTPT(dev, &mtptpt_reg_data);
    if (err) {
        sx_err(dev, "Failed to configure register mtptpt.\n");
        goto out;
    }

    /* Configure trap PTP1 for general ptp message types */
    memset(&mtptpt_reg_data, 0, sizeof(mtptpt_reg_data));
    mtptpt_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mtptpt_reg_data.op_tlv, MTPTPT_REG_ID, 2);
    mtptpt_reg_data.mtptpt_reg.trap_id = 1;
    mtptpt_reg_data.mtptpt_reg.message_type = PTP_MSG_FOLLOW_UP |
                                              PTP_MSG_DELAY_RESP | PTP_MSG_PDELAY_RESP_FOLLOW_UP | PTP_MSG_ANNOUNCE |
                                              PTP_MSG_SIGNALING | PTP_MSG_MANAGEMENT;

    err = sx_ACCESS_REG_MTPTPT(dev, &mtptpt_reg_data);
    if (err) {
        sx_err(dev, "Failed to configure register mtptpt.\n");
        goto out;
    }

    err = SX_CLOCK_DEV_SPECIFIC_CB(dev, sx_ptp_init, priv, ptp_mode);
    if (err) {
        sx_err(dev, "Failed in chip-specific PTP init function.\n");
        goto out;
    }

    INIT_DELAYED_WORK(&__per_sec_dwork, __per_sec);
    sx_clock_queue_delayed_work(&__per_sec_dwork, 0);

    priv->ptp_cqn = -1;
    __ptp_working_mode = ptp_mode;
    priv->tstamp.is_ptp_enable = 1;

out:
    return err;
}


int sx_core_ptp_cleanup(struct sx_priv *priv)
{
    struct sx_dev *dev = &priv->dev;
    int            err = 0;

    if (!priv->tstamp.is_ptp_enable) {
        goto out;
    }

    err = SX_CLOCK_DEV_SPECIFIC_CB(dev, sx_ptp_cleanup, priv);
    if (err) {
        sx_err(dev, "Failed in chip-specific PTP cleanup function.\n");
    }

    cancel_delayed_work_sync(&__per_sec_dwork);

    priv->ptp_cqn = -1;
    __ptp_working_mode = KU_PTP_MODE_DISABLED;
    priv->tstamp.is_ptp_enable = 0;

out:
    return err;
}


int sx_dbg_ptp_dump_proc_show(struct seq_file *m, void *v)
{
    struct sx_dev  *dev;
    struct sx_priv *priv;

    dev = sx_clock_get_dev();
    if (!dev) {
        return 0;
    }

    priv = sx_priv(dev);

    seq_printf(m, "PTP DUMP\n");
    seq_printf(m, "--------\n");

    switch (sx_ptp_get_mode()) {
    case KU_PTP_MODE_DISABLED:
        seq_printf(m, "PTP mode: Disabled\n");
        return 0;

    case KU_PTP_MODE_EVENTS:
        seq_printf(m, "PTP mode: Events\n");
        break;

    case KU_PTP_MODE_POLLING:
        seq_printf(m, "PTP mode: Polling\n");
        break;

    default:
        seq_printf(m, "PTP mode: N/A\n");
        return 0;
    }

    seq_printf(m, "PTP CQn: %d\n\n", priv->ptp_cqn);

    seq_printf(m, "%-40s   %-15s   %-15s\n", "Counter", "RX", "TX");
    seq_printf(m, "-----------------------------------------------------------------------------\n");

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Total packets",
               (u64)atomic64_read(&__ptp_common_counters[PTP_PACKET_INGRESS][PTP_COUNTER_COMMON_TOTAL]),
               (u64)atomic64_read(&__ptp_common_counters[PTP_PACKET_EGRESS][PTP_COUNTER_COMMON_TOTAL]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Timestamp required",
               (u64)atomic64_read(&__ptp_common_counters[PTP_PACKET_INGRESS][PTP_COUNTER_COMMON_NEED_TIMESTAMP]),
               (u64)atomic64_read(&__ptp_common_counters[PTP_PACKET_EGRESS][PTP_COUNTER_COMMON_NEED_TIMESTAMP]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Rate limiter violation",
               (u64)atomic64_read(&__ptp_common_counters[PTP_PACKET_INGRESS][PTP_COUNTER_COMMON_RATE_LIMIT]),
               (u64)atomic64_read(&__ptp_common_counters[PTP_PACKET_EGRESS][PTP_COUNTER_COMMON_RATE_LIMIT]));

    SX_CLOCK_DEV_SPECIFIC_CB(dev, sx_ptp_dump, m, v);

    seq_printf(m, "\n\n");
    return 0;
}
