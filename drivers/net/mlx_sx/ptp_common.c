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
#include "dev_db.h"
#include "sx_dbg_dump_proc.h"

#define PTP_RX_MAX_PPS_PER_PORT (394)
#define PTP_TX_MAX_PPS_PER_PORT (404)

static void __ptp_reset_budget(struct sx_priv *priv)
{
    int i;

    for (i = 0; i < PTP_MAX_PORTS; i++) {
        atomic64_set(&priv->ptp.rx_budget[i], PTP_RX_MAX_PPS_PER_PORT);
    }

    for (i = 0; i < PTP_MAX_PORTS; i++) {
        atomic64_set(&priv->ptp.tx_budget[i], PTP_TX_MAX_PPS_PER_PORT);
    }
}


/* This function runs once per second */
static void __per_sec(struct work_struct *work)
{
    struct delayed_work *dwork = to_delayed_work(work);
    struct sx_priv      *priv = container_of(dwork, struct sx_priv, ptp.per_sec_dwork);

    __ptp_reset_budget(priv);
    sx_clock_queue_delayed_work(&priv->ptp.per_sec_dwork, HZ);
}

#define IS_PTP_UDP_PORT(udp_hdr) (be16_to_cpu((udp_hdr)->dest) == 319 || be16_to_cpu((udp_hdr)->dest) == 320)

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
            is_ptp = IS_PTP_UDP_PORT(udp);
            offset += (ip_hdr->ihl << 2) + UDP_HLEN;
        }
        break;

    case ETH_P_IPV6:    /*PTP_V2_IPV6*/
        ip6_hdr = (struct ipv6hdr *)(data + offset);
        if (ip6_hdr->nexthdr == IPPROTO_UDP) {
            udp = (struct udphdr *)(data + offset + IP6_HLEN);
            is_ptp = IS_PTP_UDP_PORT(udp);
            offset += IP6_HLEN + UDP_HLEN;
        }
        break;

    default:
        break;
    }

#define OFFSET_PTP_DOMAIN_NUMBER (4)

    if (pkt_meta && is_ptp) {
        pkt_meta->pkt_fields.seqid = ntohs(*((u16*)(data + offset + OFF_PTP_SEQUENCE_ID)));
        pkt_meta->pkt_fields.domain = *(data + offset + OFFSET_PTP_DOMAIN_NUMBER);
        pkt_meta->pkt_fields.msg_type = *(data + offset) & 0xf;
        pkt_meta->timestamp_required = !!(((u16)(1 << pkt_meta->pkt_fields.msg_type)) & PTP_MSG_EVENT_ALL);
    }

    return is_ptp;
}


int sx_core_ptp_rx_handler(struct sx_priv *priv, struct completion_info *ci, int cqn)
{
    struct sx_ptp_packet_metadata pkt_meta;
    int                           trap_counter_index, trap_counter_error_index = PTP_COUNTER_TRAP_LAST;

    switch (ci->hw_synd) {
    case SXD_TRAP_ID_PTP_ING_EVENT:
    case SXD_TRAP_ID_PTP_EGR_EVENT:
        goto ptp_fifo_event;
        break;

    case SXD_TRAP_ID_PTP_PTP0:
        trap_counter_index = PTP_COUNTER_TRAP_PTP0;
        trap_counter_error_index = PTP_COUNTER_TRAP_PTP0_ERROR; /* counter index if it is not PTP packet */
        break;

    case SXD_TRAP_ID_PTP_PTP1:
        trap_counter_index = PTP_COUNTER_TRAP_PTP1;
        trap_counter_error_index = PTP_COUNTER_TRAP_PTP1_ERROR; /* counter index if it is not PTP packet */
        break;

    case SXD_TRAP_ID_ETH_L2_LLDP: /* PTP L2 Peer to Peer packets received with LLDP trap */
        trap_counter_index = PTP_COUNTER_TRAP_OTHER;
        break;

    default:
        return -1; /* if we get here, it is not a PTP packet */
    }

    if (!__is_ptp_packet(ci->skb, &pkt_meta)) {
        /* if we get here from PTP0/PTP1 traps, it is an error. either it is not a PTP
         *  packet or it is not a valid one */
        if (trap_counter_error_index != PTP_COUNTER_TRAP_LAST) {
            atomic64_inc(&priv->ptp.common_counters[PTP_PACKET_INGRESS][PTP_COUNTER_COMMON_TOTAL]);
            atomic64_inc(&priv->ptp.traps_counters[trap_counter_error_index]);
        }

        return -1; /* if we get here, it is not a PTP packet or not a valid one */
    }

    priv->ptp.ptp_cqn = cqn;

    atomic64_inc(&priv->ptp.common_counters[PTP_PACKET_INGRESS][PTP_COUNTER_COMMON_TOTAL]);
    atomic64_inc(&priv->ptp.traps_counters[trap_counter_index]);


    if (ci->is_lag) {
        pkt_meta.sysport_lag_id = priv->lag_member_to_local_db[ci->sysport][ci->lag_subport];
    } else {
        pkt_meta.sysport_lag_id = ci->sysport;
    }

    if (pkt_meta.timestamp_required) {
        if (atomic64_dec_return(&priv->ptp.rx_budget[pkt_meta.sysport_lag_id]) < 0) {
            /* no more budget for this RX PTP packet! */
            atomic64_inc(&priv->ptp.common_counters[PTP_PACKET_INGRESS][PTP_COUNTER_COMMON_RATE_LIMIT]);
        }

        atomic64_inc(&priv->ptp.common_counters[PTP_PACKET_INGRESS][PTP_COUNTER_COMMON_NEED_TIMESTAMP]);
    }

ptp_fifo_event:

    /* handler should take care of deleting 'ci->skb' and 'ci' */
    return SX_CLOCK_DEV_SPECIFIC_CB(&priv->dev, sx_ptp_rx_handler, priv, ci, sx_ptp_get_mode(priv), &pkt_meta);
}


int sx_core_ptp_tx_handler(struct sx_dev *dev, struct sk_buff *skb, u16 sysport_lag_id, u8 is_lag, bool *is_ptp_pkt)
{
    struct sx_priv               *priv = sx_priv(dev);
    struct sx_ptp_packet_metadata pkt_meta;
    u16                           phy_port_max = 0;
    int                           err;

    if (!sx_ptp_is_enabled(priv) || !__is_ptp_packet(skb, &pkt_meta)) {
        *is_ptp_pkt = false;
        return 0;
    }

    *is_ptp_pkt = true;
    pkt_meta.sysport_lag_id = sysport_lag_id;

    if (is_lag) {
        if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
            printk(KERN_ERR PFX "Failed to get max number of phy ports.\n");
            return -EINVAL;
        }

        pkt_meta.sysport_lag_id += phy_port_max;
    }

    atomic64_inc(&priv->ptp.common_counters[PTP_PACKET_EGRESS][PTP_COUNTER_COMMON_TOTAL]);

    /*  with ptp general messages should be dispatch without timestamp */
    if (!pkt_meta.timestamp_required) {
        return 0;
    }

    if (atomic64_dec_return(&priv->ptp.tx_budget[pkt_meta.sysport_lag_id]) < 0) {
        atomic64_inc(&priv->ptp.common_counters[PTP_PACKET_EGRESS][PTP_COUNTER_COMMON_RATE_LIMIT]);
    }

    atomic64_inc(&priv->ptp.common_counters[PTP_PACKET_EGRESS][PTP_COUNTER_COMMON_NEED_TIMESTAMP]);

    skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;

    err = SX_CLOCK_DEV_SPECIFIC_CB(dev, sx_ptp_tx_handler, priv, skb, &pkt_meta);
    if (err) {
        kfree_skb(skb); /* drop packet flow, use kfree_skb */
    }

    return err;
}
EXPORT_SYMBOL(sx_core_ptp_tx_handler);

ptp_mode_t sx_ptp_get_mode(struct sx_priv *priv)
{
    return priv->ptp.ptp_mode;
}

bool sx_ptp_is_enabled(struct sx_priv *priv)
{
    return (sx_ptp_get_mode(priv) != KU_PTP_MODE_DISABLED);
}

int sx_core_get_ptp_state(struct sx_dev *dev, uint8_t *is_ptp_enable)
{
    *is_ptp_enable = sx_ptp_is_enabled(sx_priv(dev));
    return 0;
}
EXPORT_SYMBOL(sx_core_get_ptp_state);


int sx_core_is_ptp_packet(struct sk_buff *skb, u8 *is_ptp_pkt)
{
    *is_ptp_pkt = __is_ptp_packet(skb, NULL);
    return 0;
}

const char * sx_core_ptp_msg_type_to_str(u8 msg_type)
{
    static const char *msg_type_str[] = {
        [0] = "Sync",
        [1] = "DelayReq",
        [2] = "PDelayReq",
        [3] = "PDelayResp",
        [8] = "FollowUp",
        [9] = "DelayResp",
        [10] = "PDelayRespFollowUp",
        [11] = "Announce",
        [12] = "Signaling",
        [13] = "Management"
    };

    if (msg_type < sizeof(msg_type_str) / sizeof(msg_type_str[0])) {
        return msg_type_str[msg_type];
    }

    return "N/A";
}

int sx_core_get_ptp_clock_index(struct sx_dev *dev, uint8_t *ptp_clock_index_p)
{
    struct sx_priv *priv = sx_priv(dev);

    if (sx_ptp_is_enabled(priv)) {
        *ptp_clock_index_p = ptp_clock_index(priv->hw_clock.clock);
    }

    return 0;
}
EXPORT_SYMBOL(sx_core_get_ptp_clock_index);


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
int sx_core_ptp_tx_ts_handler(struct sx_priv *priv, struct sk_buff *skb, const struct timespec64 *tx_ts)
#else
int sx_core_ptp_tx_ts_handler(struct sx_priv *priv, struct sk_buff *skb, const struct timespec *tx_ts)
#endif
{
    return SX_CLOCK_DEV_SPECIFIC_CB(&priv->dev, sx_ptp_tx_ts_handler, priv, skb, tx_ts);
}

int sx_core_ptp_get_supported_tx_types(struct sx_dev *dev, u32 *tx_types)
{
    return SX_CLOCK_DEV_SPECIFIC_CB(dev,
                                    sx_ptp_get_supported_tx_types,
                                    sx_priv(dev),
                                    tx_types);
}
EXPORT_SYMBOL(sx_core_ptp_get_supported_tx_types);

int sx_core_ptp_set_tx_type(struct sx_dev *dev, int tx_type)
{
    return SX_CLOCK_DEV_SPECIFIC_CB(dev,
                                    sx_ptp_set_tx_type,
                                    sx_priv(dev),
                                    tx_type);
}
EXPORT_SYMBOL(sx_core_ptp_set_tx_type);

int sx_core_ptp_tx_control_to_data(struct sx_dev   *dev,
                                   struct sk_buff **orig_skb,
                                   struct isx_meta *meta,
                                   u16              port,
                                   u8               is_lag,
                                   u8              *is_tagged)
{
    return SX_CLOCK_DEV_SPECIFIC_CB(dev,
                                    sx_ptp_tx_control_to_data,
                                    sx_priv(dev),
                                    orig_skb,
                                    meta,
                                    port,
                                    is_lag,
                                    is_tagged);
}
EXPORT_SYMBOL(sx_core_ptp_tx_control_to_data);

int sx_core_ptp_dev_init(struct sx_priv *priv, ptp_mode_t ptp_mode)
{
    int                         i = 0, err = 0;
    struct ku_access_mtptpt_reg mtptpt_reg_data;
    struct sx_dev              *dev = &priv->dev;
    bool                        log_created = false;

    if (sx_ptp_is_enabled(priv)) {
        sx_err(dev, "PTP is already initialized!\n");
        err = -EBUSY;
        goto out;
    }

    for (i = 0; i < PTP_COUNTER_COMMON_LAST; i++) {
        atomic64_set(&priv->ptp.common_counters[PTP_PACKET_INGRESS][i], 0);
        atomic64_set(&priv->ptp.common_counters[PTP_PACKET_EGRESS][i], 0);
    }

    for (i = 0; i < PTP_COUNTER_TRAP_LAST; i++) {
        atomic64_set(&priv->ptp.traps_counters[i], 0);
    }

    for (i = 0; i < PTP_MAX_PORTS; i++) {
        atomic64_set(&priv->ptp.rx_budget[i], 0);
    }

    for (i = 0; i < PTP_MAX_PORTS; i++) {
        atomic64_set(&priv->ptp.tx_budget[i], 0);
    }

    err = sx_internal_log_init(&priv->ptp.log,
                               1000,
                               SX_INTERNAL_LOG_SEVERITY_INFO_E,
                               "ptp_errors_and_major_events");
    if (err) {
        sx_err(dev, "Failed to create PTP error log (err=%d)\n", err);
        goto out;
    }

    log_created = true;

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

    err = SX_CLOCK_DEV_SPECIFIC_CB(dev, sx_ptp_dev_init, priv, ptp_mode);
    if (err) {
        sx_err(dev, "Failed in chip-specific PTP init function.\n");
        goto out;
    }

    INIT_DELAYED_WORK(&priv->ptp.per_sec_dwork, __per_sec);
    sx_clock_queue_delayed_work(&priv->ptp.per_sec_dwork, 0);

    priv->ptp.ptp_cqn = -1;
    priv->ptp.ptp_mode = ptp_mode;
    printk(KERN_INFO "Enabling PTP on device %u\n", dev->device_id);

    SX_CLOCK_ACTIVITY_LOG(priv, SX_INTERNAL_LOG_SEVERITY_INFO_E, "PTP initialized");
    goto out;

out:
    if (err && log_created) {
        sx_internal_log_deinit(&priv->ptp.log);
    }

    return err;
}


int sx_core_ptp_dev_cleanup(struct sx_priv *priv)
{
    struct sx_dev *dev = &priv->dev;
    int            err = 0;

    if (!sx_ptp_is_enabled(priv)) {
        goto out;
    }

    err = SX_CLOCK_DEV_SPECIFIC_CB(dev, sx_ptp_dev_cleanup, priv);
    if (err) {
        sx_err(dev, "Failed in chip-specific PTP cleanup function.\n");
    }

    cancel_delayed_work_sync(&priv->ptp.per_sec_dwork);

    priv->ptp.ptp_cqn = -1;
    priv->ptp.ptp_mode = KU_PTP_MODE_DISABLED;

    printk(KERN_INFO "Disabling PTP on device %u\n", dev->device_id);
    SX_CLOCK_ACTIVITY_LOG(priv, SX_INTERNAL_LOG_SEVERITY_INFO_E, "PTP cleanup");

    sx_internal_log_deinit(&priv->ptp.log);

out:
    return err;
}


int sx_dbg_ptp_dump_proc_show(struct seq_file *m, void *v, void *context)
{
    struct sx_priv *priv = NULL;
    struct sx_dev * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    priv = sx_priv(dev);
    seq_printf(m, "PTP DUMP (device #%u)\n", priv->dev.device_id);
    seq_printf(m, "-----------------------\n");

    switch (sx_ptp_get_mode(priv)) {
    case KU_PTP_MODE_DISABLED:
        seq_printf(m, "PTP mode: Disabled\n");
        goto out;

    case KU_PTP_MODE_EVENTS:
        seq_printf(m, "PTP mode: Events\n");
        break;

    case KU_PTP_MODE_POLLING:
        seq_printf(m, "PTP mode: Polling\n");
        break;

    default:
        seq_printf(m, "PTP mode: N/A\n");
        goto out;
    }

    seq_printf(m, "PTP CQn: %d\n\n", priv->ptp.ptp_cqn);

    seq_printf(m, "%-40s   %-15s   %-15s\n", "Counter", "RX", "TX");
    seq_printf(m, "-----------------------------------------------------------------------------\n");

    seq_printf(m,
               "%-40s   %-15llu   %-15llu\n",
               "Total packets",
               (u64)atomic64_read(
                   &priv->ptp.common_counters[PTP_PACKET_INGRESS][PTP_COUNTER_COMMON_TOTAL]),
               (u64)atomic64_read(&priv->ptp.common_counters[PTP_PACKET_EGRESS][PTP_COUNTER_COMMON_TOTAL]));

    seq_printf(m, "    %-36s   %-15llu\n",
               "PTP0 (Ok)",
               (u64)atomic64_read(&priv->ptp.traps_counters[PTP_COUNTER_TRAP_PTP0]));

    seq_printf(m, "    %-36s   %-15llu\n",
               "PTP0 (Error)",
               (u64)atomic64_read(&priv->ptp.traps_counters[PTP_COUNTER_TRAP_PTP0_ERROR]));

    seq_printf(m, "    %-36s   %-15llu\n",
               "PTP1 (Ok)",
               (u64)atomic64_read(&priv->ptp.traps_counters[PTP_COUNTER_TRAP_PTP1]));

    seq_printf(m, "    %-36s   %-15llu\n",
               "PTP1 (Error)",
               (u64)atomic64_read(&priv->ptp.traps_counters[PTP_COUNTER_TRAP_PTP1_ERROR]));

    seq_printf(m, "    %-36s   %-15llu\n",
               "Other",
               (u64)atomic64_read(&priv->ptp.traps_counters[PTP_COUNTER_TRAP_OTHER]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Timestamp required",
               (u64)atomic64_read(&priv->ptp.common_counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_COMMON_NEED_TIMESTAMP]),
               (u64)atomic64_read(&priv->ptp.common_counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_COMMON_NEED_TIMESTAMP]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Rate limiter violation",
               (u64)atomic64_read(&priv->ptp.common_counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_COMMON_RATE_LIMIT]),
               (u64)atomic64_read(&priv->ptp.common_counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_COMMON_RATE_LIMIT]));

    SX_CLOCK_DEV_SPECIFIC_CB(dev, sx_ptp_dump, priv, m, v, context);

    seq_printf(m, "\n\n");

out:
    return 0;
}
