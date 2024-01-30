/*
 * Copyright © 2021-2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include <linux/module.h>
#include <net/flow_offload.h>
#include "drop_monitor.h"

static sx_net_dm_hw_report_func g_sx_net_dm_hw_report = NULL;
static int                      enable_drop_monitor_report = 0;
module_param_named(enable_drop_monitor_report, enable_drop_monitor_report, int, 0644);
MODULE_PARM_DESC(enable_drop_monitor_report, "enabled/disable packet reports to drop_monitor");

#ifndef SX_DROP_MONITOR_DISABLED

static u16                    g_buffer_drop_trap_id = NUM_HW_SYNDROMES + 1;
static struct listener_entry *g_drop_monitor_listener = NULL;

#define DROP_MONITOR_L2_DROP_GROUP_STR     "l2"
#define DROP_MONITOR_L3_DROP_GROUP_STR     "router"
#define DROP_MONITOR_BUFFER_DROP_GROUP_STR "buffer"
#define DROP_MONITOR_TUNNEL_DROP_GROUP_STR "tunnel"
#define DROP_MONITOR_ACL_DROP_GROUP_STR    "acl"

#define ACL_DROP_DIRECTION_OFFSET     18    /* the offset to an ACL direction inside the user defined value */
#define ACL_DROP_DIRECTION_MASK       0x3   /* 2 bit of the direction indicates if it's ingress / egress / multipoint */
#define ACL_DROP_DIRECTION_INGRESS    0
#define ACL_DROP_DIRECTION_EGRESS     1
#define ACL_DROP_DIRECTION_MULTIPOINT 2
#define EXTRACT_ACL_DIRECTION(user_def_val) ((user_def_val >> ACL_DROP_DIRECTION_OFFSET) & ACL_DROP_DIRECTION_MASK)

static const char * const drop_monitor_trap_str_s[] = {
    /* L2 Drops */
    [SXD_TRAP_ID_DISCARD_ISOLATION] = "port_isolation_filter",
    [SXD_TRAP_ID_DISCARD_ING_PACKET_RSV_MAC] = "dmac_is_reserved",
    [SXD_TRAP_ID_DISCARD_ING_SWITCH_VTAG_ALLOW] = "vlan_tag_mismatch",
    [SXD_TRAP_ID_DISCARD_ING_SWITCH_VLAN] = "ingress_vlan_filter",
    [SXD_TRAP_ID_DISCARD_ING_SWITCH_STP] = "ingress_spanning_tree_filter",
    [SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_UC] = "uc_fdb_filter",
    [SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_MC_NULL] = "port_list_is_empty",
    [SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_LB] = "port_loopback_filter",
    [SXD_TRAP_ID_DISCARD_ING_PACKET_SMAC_MC] = "source_mac_is_multicast",
    [SXD_TRAP_ID_DISCARD_ING_PACKET_SMAC_DMAC] = "smac_equals_dmac",
    [SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_NO_PORTS] = "port_list_is_empty",
    [SXD_TRAP_ID_DISCARD_ING_PACKET_SMAC0] = "smac_is_zero",
    [SXD_TRAP_ID_FID_MISS] = "vlan_tag_mismatch",

    /* L3 Drops */
    [SXD_TRAP_ID_DISCARD_NON_ROUTED] = "non_routable_packet",
    [SXD_TRAP_ID_DISCARD_ROUTER2] = "blackhole_route",
    [SXD_TRAP_ID_DISCARD_ROUTER3] = "blackhole_neigh",
    [SXD_TRAP_ID_DISCARD_MC_SCOPE_IPV6_0] = "ipv6_mc_dip_reserved_scope",
    [SXD_TRAP_ID_DISCARD_MC_SCOPE_IPV6_1] = "ipv6_mc_dip_interface_local_scope",
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_NO_HDR] = "non_ip",
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_UC_DIP_MC_DMAC] = "uc_dip_over_mc_dmac",
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_DIP_LB] = "dip_is_loopback_address",
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_MC] = "sip_is_mc",
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_CLASS_E] = "sip_is_in_class_e",
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_LB] = "sip_is_loopback_address",
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_UNSP] = "sip_is_unspecified",
    [SXD_TRAP_ID_IPV6_UNSPECIFIED_SIP] = "sip_is_unspecified",
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_IP_HDR] = "ip_header_corrupted",
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_MC_DMAC] = "mc_dmac_mismatch",
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_DIP] = "sip_equals_dip",
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_BC] = "ipv4_sip_is_limited_bc",
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_DIP_LOCAL_NET] = "ipv4_dip_is_local_network",
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_DIP_LINK_LOCAL] = "ipv4_dip_is_link_local",
    [SXD_TRAP_ID_DISCARD_ROUTER_IRIF_EN] = "irif_disabled",
    [SXD_TRAP_ID_DISCARD_ROUTER_ERIF_EN] = "erif_disabled",
    [SXD_TRAP_ID_ETH_L3_LBERROR] = "uc_loopback",
    [SXD_TRAP_ID_HOST_MISS_IPV4] = "unresolved_neigh",
    [SXD_TRAP_ID_HOST_MISS_IPV6] = "unresolved_neigh",
    [SXD_TRAP_ID_DISCARD_ROUTER_LPM4] = "ipv4_lpm_miss",
    [SXD_TRAP_ID_DISCARD_ROUTER_LPM6] = "ipv6_lpm_miss",
    [SXD_TRAP_ID_ETH_L3_MTUERROR] = "mtu_value_is_too_small",
    [SXD_TRAP_ID_ETH_L3_TTLERROR] = "ttl_value_is_too_small",
    [SXD_TRAP_ID_ETH_L3_URPF_PROTECTION] = "packet_source_IP_can't_be_verified",

    /* Tunnel Drops */
    [SXD_TRAP_ID_DISCARD_OVERLAY_SWITCH_SMAC_MC] = "overlay_smac_is_mc",
    [SXD_TRAP_ID_DISCARD_OVERLAY_SWITCH_SMAC_DMAC] = "overlay_smac_equals_dmac",
    [SXD_TRAP_ID_DISCARD_OVERLAY_SWITCH_SMAC0] = "overlay_smac_is_zero",
    [SXD_TRAP_ID_DISCARD_ENC_ISOLATION] = "encap_port_isolation",
    [SXD_TRAP_ID_DISCARD_DEC_PKT] = "decap_error",
    [SXD_TRAP_ID_DISCARD_DEC_NVE_OPTIONS] = "decap_error",
    [SXD_TRAP_ID_DECAP_ECN0] = "decap_error",
    [SXD_TRAP_ID_IPIP_DECAP_ERROR] = "decap_error",
};

#define DROP_MONITOR_TRAP_STR_SIZE (sizeof(drop_monitor_trap_str_s) / sizeof(drop_monitor_trap_str_s[0]))

static const char * const drop_monitor_trap_group_str_s[] = {
    /* L2 Drops */
    [SXD_TRAP_ID_DISCARD_ISOLATION] = DROP_MONITOR_L2_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_PACKET_RSV_MAC] = DROP_MONITOR_L2_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_PACKET_SMAC0] = DROP_MONITOR_L2_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_SWITCH_VTAG_ALLOW] = DROP_MONITOR_L2_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_SWITCH_VLAN] = DROP_MONITOR_L2_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_SWITCH_STP] = DROP_MONITOR_L2_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_UC] = DROP_MONITOR_L2_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_MC_NULL] = DROP_MONITOR_L2_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_LB] = DROP_MONITOR_L2_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_PACKET_SMAC_MC] = DROP_MONITOR_L2_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_PACKET_SMAC_DMAC] = DROP_MONITOR_L2_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_NO_PORTS] = DROP_MONITOR_L2_DROP_GROUP_STR,
    [SXD_TRAP_ID_FID_MISS] = DROP_MONITOR_L2_DROP_GROUP_STR,

    /* L3 Drops */
    [SXD_TRAP_ID_DISCARD_NON_ROUTED] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ROUTER2] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ROUTER3] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_MC_SCOPE_IPV6_0] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_MC_SCOPE_IPV6_1] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_NO_HDR] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_UC_DIP_MC_DMAC] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_DIP_LB] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_MC] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_CLASS_E] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_LB] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_UNSP] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_IPV6_UNSPECIFIED_SIP] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_IP_HDR] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_MC_DMAC] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_DIP] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_BC] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_DIP_LOCAL_NET] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ING_ROUTER_DIP_LINK_LOCAL] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ROUTER_IRIF_EN] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ROUTER_ERIF_EN] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_ETH_L3_LBERROR] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_HOST_MISS_IPV4] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_HOST_MISS_IPV6] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ROUTER_LPM4] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ROUTER_LPM6] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_ETH_L3_MTUERROR] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_ETH_L3_TTLERROR] = DROP_MONITOR_L3_DROP_GROUP_STR,
    [SXD_TRAP_ID_ETH_L3_URPF_PROTECTION] = DROP_MONITOR_L3_DROP_GROUP_STR,

    /* Tunnel Drops */
    [SXD_TRAP_ID_DISCARD_OVERLAY_SWITCH_SMAC_MC] = DROP_MONITOR_TUNNEL_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_OVERLAY_SWITCH_SMAC_DMAC] = DROP_MONITOR_TUNNEL_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_OVERLAY_SWITCH_SMAC0] = DROP_MONITOR_TUNNEL_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_ENC_ISOLATION] = DROP_MONITOR_TUNNEL_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_DEC_PKT] = DROP_MONITOR_TUNNEL_DROP_GROUP_STR,
    [SXD_TRAP_ID_DISCARD_DEC_NVE_OPTIONS] = DROP_MONITOR_TUNNEL_DROP_GROUP_STR,
    [SXD_TRAP_ID_DECAP_ECN0] = DROP_MONITOR_TUNNEL_DROP_GROUP_STR,
    [SXD_TRAP_ID_IPIP_DECAP_ERROR] = DROP_MONITOR_TUNNEL_DROP_GROUP_STR,

    /* ACL Drops */
    [SXD_TRAP_ID_ACL_DROP] = DROP_MONITOR_ACL_DROP_GROUP_STR,
    [SXD_TRAP_ID_SYS_ACL_DROP] = DROP_MONITOR_ACL_DROP_GROUP_STR,

    /* Buffer Drops */
    [SXD_TRAP_ID_MIRROR_AGENT0] = DROP_MONITOR_BUFFER_DROP_GROUP_STR,
    [SXD_TRAP_ID_MIRROR_AGENT1] = DROP_MONITOR_BUFFER_DROP_GROUP_STR,
    [SXD_TRAP_ID_MIRROR_AGENT2] = DROP_MONITOR_BUFFER_DROP_GROUP_STR,
    [SXD_TRAP_ID_MIRROR_AGENT3] = DROP_MONITOR_BUFFER_DROP_GROUP_STR,
    [SXD_TRAP_ID_MIRROR_AGENT4] = DROP_MONITOR_BUFFER_DROP_GROUP_STR,
    [SXD_TRAP_ID_MIRROR_AGENT5] = DROP_MONITOR_BUFFER_DROP_GROUP_STR,
    [SXD_TRAP_ID_MIRROR_AGENT6] = DROP_MONITOR_BUFFER_DROP_GROUP_STR,
    [SXD_TRAP_ID_MIRROR_AGENT7] = DROP_MONITOR_BUFFER_DROP_GROUP_STR,
};

#define DROP_MONITOR_TRAP_GROUP_STR_SIZE     \
    (sizeof(drop_monitor_trap_group_str_s) / \
     sizeof(drop_monitor_trap_group_str_s[0]))

static const char * sx_drop_monitor_trap_str(struct completion_info *ci)
{
    if ((ci->hw_synd >= SXD_TRAP_ID_MIRROR_AGENT0) &&
        (ci->hw_synd <= SXD_TRAP_ID_MIRROR_AGENT7)) {
        if (ci->hw_synd != g_buffer_drop_trap_id) {
            return NULL;
        }

        /* Buffer Drops */
        switch (ci->mirror_reason) {
        case SXD_SPAN_MIRROR_REASON_ING_SHARED_BUFFER_DROP_E:
            return "tail_drop";

        case SXD_SPAN_MIRROR_REASON_ING_WRED_E:
            return "early_drop";

        case SXD_SPAN_MIRROR_REASON_ING_TC_CONGESTION_E:
            return "congestion_thresh_crossed";

        case SXD_SPAN_MIRROR_REASON_EGR_TC_LATENCY_E:
            return "latency_thresh_crossed";

        default:
            return NULL;
        }
    } else if ((ci->hw_synd == SXD_TRAP_ID_ACL_DROP) || (ci->hw_synd == SXD_TRAP_ID_SYS_ACL_DROP)) {
        switch (EXTRACT_ACL_DIRECTION(ci->user_def_val)) {
        case ACL_DROP_DIRECTION_INGRESS:
            return "ingress_flow_action_drop";

        case ACL_DROP_DIRECTION_EGRESS:
            return "egress_flow_action_drop";

        case ACL_DROP_DIRECTION_MULTIPOINT:
            return "flow_action_drop";

        default:
            return NULL;
        }
    } else if (ci->hw_synd < DROP_MONITOR_TRAP_STR_SIZE) {
        return drop_monitor_trap_str_s[ci->hw_synd];
    } else {
        return NULL;
    }
}

static const char * sx_drop_monitor_trap_group_str(u16 trap_id)
{
    if (trap_id < DROP_MONITOR_TRAP_GROUP_STR_SIZE) {
        return drop_monitor_trap_group_str_s[trap_id];
    }

    return NULL;
}

/* If context is NULL, it means the packet comes from a monitor RDQ, then we need to copy the skb and send it to drop monitor.
 * When a skb and its metadata (trap name, trap group name) is reported to drop monitor, drop monitor simply stores them in a list.
 * The skb and metadata will be delivered to user space later by a workqueue. Since the monitor RDQ is reusing the skb memory,
 * if we don't copy the skb, then drop monitor may deliver inconsistent packet and metadata to user space - the skb payload is overwritten
 * by a new packet but the metadata belongs to the old packet.
 */
static void sx_drop_monitor_hw_report(struct completion_info *ci, void *context)
{
    const char *trap_str = NULL;
    const char *trap_grp_str = NULL;
    u8          copy_skb = (context == NULL) ? 1 : 0;
    void       *fa_cookie_p = NULL;

#ifndef SX_FLOW_OFFLOAD_DISABLED
    u8 fa_cookie[sizeof(struct flow_action_cookie) + sizeof(u32)];
#endif


    if (!g_sx_net_dm_hw_report) {
        return;
    }

    trap_str = sx_drop_monitor_trap_str(ci);
    trap_grp_str = sx_drop_monitor_trap_group_str(ci->hw_synd);

    if ((trap_str == NULL) || (trap_grp_str == NULL)) {
        return;
    }

#ifndef SX_FLOW_OFFLOAD_DISABLED
    if ((ci->hw_synd == SXD_TRAP_ID_ACL_DROP) || (ci->hw_synd == SXD_TRAP_ID_SYS_ACL_DROP)) {
        ((struct flow_action_cookie*)fa_cookie)->cookie_len = sizeof(u32);
        memcpy(((struct flow_action_cookie*)fa_cookie)->cookie, &(ci->user_def_val), sizeof(u32));
        fa_cookie_p = (void*)fa_cookie;
    }
#endif

    g_sx_net_dm_hw_report(ci, trap_str, trap_grp_str, fa_cookie_p, copy_skb);
}

static int sx_drop_monitor_init(void)
{
    struct listener_entry    *new_listener;
    union ku_filter_critireas crit;

    new_listener = kmalloc(sizeof(*new_listener), GFP_ATOMIC);
    if (!new_listener) {
        printk(KERN_ERR "%s: Failed allocating memory for new listener\n", __func__);
        return -ENOMEM;
    }

    memset(new_listener, 0, sizeof(*new_listener));
    new_listener->swid = 0;
    crit.dont_care.sysport = 0;
    new_listener->critireas = crit;
    new_listener->handler = sx_drop_monitor_hw_report;
    new_listener->context = NULL;
    new_listener->listener_type = L2_TYPE_DONT_CARE;
    new_listener->is_default = 1;
    new_listener->rx_pkts = 0;

    g_drop_monitor_listener = new_listener;

    return 0;
}

static bool sx_drop_monitor_listener_active(void)
{
    int err;

    if (!g_drop_monitor_listener) {
        err = sx_drop_monitor_init();
        if (err) {
            printk(KERN_ERR "%s: sx_drop_monitor_init failed with err %d\n", __func__, err);
            return false;
        }
    }

    return g_sx_net_dm_hw_report;
}

void sx_drop_monitor_destroy(void)
{
    if (g_drop_monitor_listener) {
        kfree(g_drop_monitor_listener);
        g_drop_monitor_listener = NULL;
    }
}

static void sx_drop_monitor_handler(struct completion_info *ci, void *context)
{
    if (!enable_drop_monitor_report) {
        return;
    }

    sx_drop_monitor_hw_report(ci, context);
}

void sx_drop_monitor_handle_monitor_rdq(u32                     cq_ts_enabled,
                                        struct sx_cq           *cq,
                                        int                     cqe_index,
                                        struct sx_cqe_params   *cqe_params,
                                        union sx_cqe           *u_cqe,
                                        struct sx_rx_timestamp *rx_ts,
                                        bool                   *rx_ts_set,
                                        struct sk_buff         *skb)
{
    int err = 0;

    if (enable_drop_monitor_report && sx_drop_monitor_listener_active()) {
        if (cq_ts_enabled) {
            set_timestamp_of_rx_packet(cq, &cq->cqe_ts_arr[cqe_index % cq->nent].timestamp, &(cqe_params->cqe_ts),
                                       rx_ts);
        } else {
            SX_RX_TIMESTAMP_INIT(rx_ts, 0, 0, SXD_TS_TYPE_NONE);
        }
        *rx_ts_set = true;
        err = rx_skb(cq->sx_dev, skb, u_cqe, rx_ts, 1, g_drop_monitor_listener, cq->sx_dev->device_id);
        if (err) {
            printk(KERN_ERR "%s: rx_skb failed with err %d\n", __func__, err);
        }
    }
}

int sx_drop_monitor_set_buffer_drop_params(unsigned long data)
{
    struct ku_buffer_drop_params buffer_drop_params;
    int                          err = 0;

    err = copy_from_user(&buffer_drop_params, (void*)data,
                         sizeof(buffer_drop_params));
    if (err) {
        printk(KERN_ERR "%s: copy_from_user failed with err %d\n", __func__, err);
        goto out;
    }

    if (buffer_drop_params.is_set) {
        if (buffer_drop_params.trap_id > NUM_HW_SYNDROMES) {
            printk(KERN_ERR "%s: CTRL_CMD_BUFFER_DROP_PARAMS: trap ID %u is not valid\n",
                   __func__, buffer_drop_params.trap_id);
            err = -EINVAL;
            goto out;
        }
        g_buffer_drop_trap_id = buffer_drop_params.trap_id;
    } else {
        g_buffer_drop_trap_id = NUM_HW_SYNDROMES + 1;
    }

out:
    return err;
}

void sx_drop_monitor_handle_sw_queue(struct completion_info *comp_info, void *context)
{
    if (enable_drop_monitor_report && sx_drop_monitor_listener_active()) {
        g_drop_monitor_listener->handler(comp_info, context);
    }
}

int sx_drop_monitor_set_synd(unsigned int                     cmd,
                             const struct ku_synd_ioctl      *ku,
                             enum l2_type                     listener_type,
                             const union ku_filter_critireas *critireas,
                             struct sx_dev                   *dev)
{
    int err = 0;

    if (cmd == CTRL_CMD_ADD_SYND) {
        err = sx_core_add_synd(ku->swid, ku->syndrome_num,
                               listener_type, current->pid, current->comm, ku->is_default,
                               critireas, sx_drop_monitor_handler, dev,
                               CHECK_DUP_ENABLED_E, dev, &(ku->port_vlan_params), ku->is_register);
    } else {
        err = sx_core_remove_synd(ku->swid, ku->syndrome_num,
                                  listener_type, ku->is_default,
                                  critireas, dev, dev, NULL, &(ku->port_vlan_params), ku->is_register, NULL);
    }

    if (err) {
        printk(KERN_ERR "%s: %s failed with err %d", __func__,
               (cmd == CTRL_CMD_ADD_SYND) ? "sx_core_add_synd" : "sx_core_remove_synd", err);
        goto out;
    }

out:
    return err;
}
#endif /* SX_DROP_MONITOR_DISABLED */

int sx_core_register_net_dm_hw_report(sx_net_dm_hw_report_func sx_net_dm_hw_report_p)
{
    g_sx_net_dm_hw_report = sx_net_dm_hw_report_p;
    return 0;
}
EXPORT_SYMBOL(sx_core_register_net_dm_hw_report);
