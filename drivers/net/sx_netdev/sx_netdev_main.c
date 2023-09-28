/*
 * Copyright (C) 2010-2022 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#include <linux/workqueue.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/bitops.h>
#include <linux/errno.h>
#include <linux/ethtool.h>
#include <linux/etherdevice.h>
#include <linux/string.h>
#include <linux/spinlock.h>
#include <linux/netdevice.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/tcp.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <net/ip.h>
#include <net/addrconf.h>
#include <linux/vmalloc.h>
#include <linux/if_ether.h>
#include <linux/if_vlan.h>
#include <linux/rtnetlink.h>
#include <linux/version.h>
#include <net/drop_monitor.h>
#include <net/flow_offload.h>
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0)) || defined(CONFIG_SX_RHEL_8_6)
#include <net/devlink.h>
#include <trace/events/devlink.h>
#endif

#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#if defined(CONFIG_NET_SWITCHDEV) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0))
#include <net/switchdev.h>
#endif
#include "sx_netdev.h"
#include "sx_psample.h"
#include "sx_netdev_module_sysfs_eeprom.h"
#include "synce.h"
#include "sx_netdev_module_sysfs_s3ip.h"

#define CREATE_TRACE_POINTS
#include "sx_netdev_trace.h"


/*
 * CONFIG_NET_PORT is private kernel define for a generic netlink channel
 * between the kernel and userspace switch drivers.
 * It is not defined in upstream kernel.
 */
#if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0))
#include <net/fib_notifier.h>
#include <net/ip_fib.h>
#include <net/ip6_fib.h>
#include <net/nexthop.h>
#include "sx_netdev_addons.h"
#endif

/*
 * Local define in order to allocate skb IP aligned.
 * In header asm/processor.h NET_IP_ALIGN is defined as 0.
 */
#ifdef NET_IP_ALIGN
#undef NET_IP_ALIGN
#endif
#define NET_IP_ALIGN (2)

MODULE_AUTHOR("Amos Hersch");
MODULE_DESCRIPTION("NVIDIA Switch Network Device Driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(DRV_VERSION);

int sx_netdev_rx_debug = 0;
module_param_named(sx_netdev_rx_debug, sx_netdev_rx_debug, int, 0644);
MODULE_PARM_DESC(sx_netdev_rx_debug, "en/dis rx debug for sx_netdev module");

int sx_netdev_tx_debug = 0;
module_param_named(sx_netdev_tx_debug, sx_netdev_tx_debug, int, 0644);
MODULE_PARM_DESC(sx_netdev_tx_debug, "en/dis tx debug for sx_netdev module");

int carrier_set_on_pude_disable = 0;
module_param_named(carrier_set_on_pude_disable, carrier_set_on_pude_disable, int, 0644);
MODULE_PARM_DESC(carrier_set_on_pude_disable, "en/dis carrier set on pude event");

#if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0))
int sx_netdev_tc_psample_enable = 0;
module_param_named(sx_netdev_tc_psample_enable, sx_netdev_tc_psample_enable, int, 0644);
MODULE_PARM_DESC(sx_netdev_tc_psample_enable, "en/dis tc psample support");
#endif /* if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) */

int arp_nd_mcast_sw_forwarding_enable = 0;
module_param_named(arp_nd_mcast_sw_forwarding_enable, arp_nd_mcast_sw_forwarding_enable, int, 0644);
MODULE_PARM_DESC(arp_nd_mcast_sw_forwarding_enable, "en/dis sw forwarding of mcast traffic");

int untagged_pkt_pvid_tag_disable = 0;
module_param_named(untagged_pkt_pvid_tag_disable, untagged_pkt_pvid_tag_disable, int, 0644);
MODULE_PARM_DESC(untagged_pkt_pvid_tag_disable, "en/dis PVID VLAN tag on untagged packet");

int single_netdev_per_port_enable = 0;
module_param_named(single_netdev_per_port_enable, single_netdev_per_port_enable, int, 0644);
MODULE_PARM_DESC(single_netdev_per_port_enable, "en/dis single netdevice per port");

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) || defined(CONFIG_SX_RHEL_8_6)
int change_proto_down_enable = 0;
module_param_named(change_proto_down_enable, change_proto_down_enable, int, 0644);
MODULE_PARM_DESC(change_proto_down_enable, "en/dis protodown netdev flag");

int mirror_device_en = 0;
module_param_named(mirror_device_en, mirror_device_en, int, 0644);
MODULE_PARM_DESC(mirror_device_en, "en/dis mirror device for span to cpu");

int route_offload_flags = 0;
module_param_named(route_offload_flags, route_offload_flags, int, 0644);
MODULE_PARM_DESC(route_offload_flags, "set route offload flags: 0 - off, 1 - set OFFLOAD and TRAP");
#endif

int offload_fwd_mark_en = 1;
#if defined(CONFIG_NET_SWITCHDEV) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0))
module_param_named(offload_fwd_mark_en, offload_fwd_mark_en, int, 0644);
MODULE_PARM_DESC(offload_fwd_mark_en, "1 - enable offload of packets fwd in HW, 0 - disable offload");
#endif

#if !defined(SX_DROP_MONITOR_DISABLED) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, \
                                                                                 0)) || defined(CONFIG_SX_RHEL_8_6))
int devlink_port_en = 0;
module_param_named(devlink_port_en, devlink_port_en, int, 0644);
MODULE_PARM_DESC(devlink_port_en, "1 - enable devlink port support for sx_netdev interfaces, 0 - disable devlink");
#endif

int module_support_en = 0;

#define BUILD_64BIT_COUNTER(high, low) ((u64)(high) << 32 | (low))

struct sx_ethtool_link_ext_state_opcode_mapping {
    u32                    status_opcode;
    enum sx_link_ext_state link_ext_state;
    u8                     link_ext_substate;
};

static const struct sx_ethtool_link_ext_state_opcode_mapping
    sx_link_ext_state_opcode_map[] = {
    {2, SX_LINK_EXT_STATE_AUTONEG,
     SX_LINK_EXT_SUBSTATE_AN_NO_PARTNER_DETECTED},
    {3, SX_LINK_EXT_STATE_AUTONEG,
     SX_LINK_EXT_SUBSTATE_AN_ACK_NOT_RECEIVED},
    {4, SX_LINK_EXT_STATE_AUTONEG,
     SX_LINK_EXT_SUBSTATE_AN_NEXT_PAGE_EXCHANGE_FAILED},
    {36, SX_LINK_EXT_STATE_AUTONEG,
     SX_LINK_EXT_SUBSTATE_AN_NO_PARTNER_DETECTED_FORCE_MODE},
    {38, SX_LINK_EXT_STATE_AUTONEG,
     SX_LINK_EXT_SUBSTATE_AN_FEC_MISMATCH_DURING_OVERRIDE},
    {39, SX_LINK_EXT_STATE_AUTONEG,
     SX_LINK_EXT_SUBSTATE_AN_NO_HCD},

    {5, SX_LINK_EXT_STATE_LINK_TRAINING_FAILURE,
     SX_LINK_EXT_SUBSTATE_LT_KR_FRAME_LOCK_NOT_ACQUIRED},
    {6, SX_LINK_EXT_STATE_LINK_TRAINING_FAILURE,
     SX_LINK_EXT_SUBSTATE_LT_KR_LINK_INHIBIT_TIMEOUT},
    {7, SX_LINK_EXT_STATE_LINK_TRAINING_FAILURE,
     SX_LINK_EXT_SUBSTATE_LT_KR_LINK_PARTNER_DID_NOT_SET_RECEIVER_READY},
    {8, SX_LINK_EXT_STATE_LINK_TRAINING_FAILURE, 0},
    {14, SX_LINK_EXT_STATE_LINK_TRAINING_FAILURE,
     SX_LINK_EXT_SUBSTATE_LT_REMOTE_FAULT},

    {9, SX_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
     SX_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_ACQUIRE_BLOCK_LOCK},
    {10, SX_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
     SX_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_ACQUIRE_AM_LOCK},
    {11, SX_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
     SX_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_GET_ALIGN_STATUS},
    {12, SX_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
     SX_LINK_EXT_SUBSTATE_LLM_FC_FEC_IS_NOT_LOCKED},
    {13, SX_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
     SX_LINK_EXT_SUBSTATE_LLM_RS_FEC_IS_NOT_LOCKED},

    {15, SX_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY, 0},
    {17, SX_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY,
     SX_LINK_EXT_SUBSTATE_BSI_LARGE_NUMBER_OF_PHYSICAL_ERRORS},
    {42, SX_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY,
     SX_LINK_EXT_SUBSTATE_BSI_UNSUPPORTED_RATE},

    {1024, SX_LINK_EXT_STATE_NO_CABLE, 0},

    {16, SX_LINK_EXT_STATE_CABLE_ISSUE,
     SX_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLE},
    {20, SX_LINK_EXT_STATE_CABLE_ISSUE,
     SX_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLE},
    {29, SX_LINK_EXT_STATE_CABLE_ISSUE,
     SX_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLE},
    {1025, SX_LINK_EXT_STATE_CABLE_ISSUE,
     SX_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLE},
    {1029, SX_LINK_EXT_STATE_CABLE_ISSUE,
     SX_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLE},
    {1031, SX_LINK_EXT_STATE_CABLE_ISSUE, 0},

    {1027, SX_LINK_EXT_STATE_EEPROM_ISSUE, 0},

    {23, SX_LINK_EXT_STATE_CALIBRATION_FAILURE, 0},

    {1032, SX_LINK_EXT_STATE_POWER_BUDGET_EXCEEDED, 0},

    {1030, SX_LINK_EXT_STATE_OVERHEAT, 0},

    {1042, SX_LINK_EXT_STATE_MODULE,
     SX_LINK_EXT_SUBSTATE_MODULE_CMIS_NOT_READY},
};

static ssize_t skip_tunnel_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t skip_tunnel_cb(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len);
static void __bind_unbind_sx_core(bool is_bind, struct sx_dev *dev);
static struct kobj_attribute skip_netdev_attr =
    __ATTR(skip_tunnel, S_IWUSR | S_IRUGO, skip_tunnel_show, skip_tunnel_cb);
static ssize_t store_bind_sx_core(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len);
static struct kobj_attribute bind_sx_core_attr = __ATTR(bind_sx_core, S_IWUSR, NULL, store_bind_sx_core);

static ssize_t show_module_id(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t reset_module(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len);
static ssize_t store_module_power_mode_policy(struct kobject        *kobj,
                                              struct kobj_attribute *attr,
                                              const char            *buf,
                                              size_t                 len);
static ssize_t show_module_power_mode_policy(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t show_module_power_mode(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t show_link_ext_state(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t show_module_temp_input(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t show_module_temp_label(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static struct kobj_attribute module_id_attr = __ATTR(id, S_IRUGO, show_module_id, NULL);
static struct kobj_attribute module_reset_attr = __ATTR(reset, S_IWUSR, NULL, reset_module);
static struct kobj_attribute module_power_mode_policy_attr = __ATTR(power_mode_policy,
                                                                    (S_IRUGO | S_IWUSR),
                                                                    show_module_power_mode_policy,
                                                                    store_module_power_mode_policy);
static struct kobj_attribute module_power_mode_attr = __ATTR(power_mode, S_IRUGO, show_module_power_mode, NULL);
static struct kobj_attribute link_ext_state_attr = __ATTR(link_ext_state, S_IRUGO, show_link_ext_state, NULL);
static struct kobj_attribute module_temp_input_attr = __ATTR(input, S_IRUGO, show_module_temp_input, NULL);
static struct kobj_attribute module_temp_label_attr = __ATTR(label, S_IRUGO, show_module_temp_label, NULL);

static char sx_netdev_version[] =
    PFX "NVIDIA Switch Network Device Driver "
    DRV_VERSION " (" DRV_RELDATE ")\n";
struct sx_netdev_rsc    *g_netdev_resources = NULL; /* Should be replaced in the core with sx_dev context */
struct sx_dev          * g_sx_dev = NULL;
struct net_device       *bridge_netdev_db[MAX_BRIDGE_NUM];
struct workqueue_struct *g_netdev_wq = NULL;
struct sx_core_interface sx_core_if;
u8                       g_skip_tunnel = 0;
#if !defined(SX_DROP_MONITOR_DISABLED) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, \
                                                                                 0)) || defined(CONFIG_SX_RHEL_8_6))
struct devlink *g_devlink_dummy_instance = NULL;
#endif

typedef struct pude_dwdata {
    u16                 sysport;
    int                 is_up;
    struct delayed_work dwork;
} pude_dwdata_t;

u64 sx_netdev_mac_to_u64(u8 *addr)
{
    u64 mac = 0;
    int i;

    for (i = 0; i < ETH_ALEN; i++) {
        mac <<= 8;
        mac |= addr[i];
    }
    return mac;
}

void sx_netdev_u64_to_mac(u8* addr, u64 mac)
{
    int i;

    for (i = ETH_ALEN - 1; i >= 0; i--) {
        addr[i] = (u8)(mac & 0xFF);
        mac >>= 8;
    }
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) || defined(CONFIG_SX_RHEL_8_6)
#define SPAN2CPU_IFNAME "mirror"
struct net_device *span2cpu_dev;

static bool sx_span2cpu_is_span2cpu_pkt(struct completion_info *comp_info)
{
    return comp_info->hw_synd == SPAN_TO_CPU_TRAP_ID_ING ||
           comp_info->hw_synd == SPAN_TO_CPU_TRAP_ID_EGR;
}

static void sx_span2cpu_send_to_mirror_taps(struct sk_buff *skb)
{
    skb_reset_network_header(skb);
    skb_reset_mac_len(skb);
    skb_push(skb, skb->mac_len);
    dev_queue_xmit_nit(skb, span2cpu_dev);
    skb_pull(skb, skb->mac_len);
}

/* forward declaration to be used for mirror netdevice */
void sx_netdev_setup(struct net_device *dev);

static int sx_span2cpu_create_mirror_netdev(const struct net_device_ops *netdev_ops,
                                            const struct ethtool_ops    *ethtool_ops)
{
    struct sx_net_priv *priv;

    span2cpu_dev = alloc_netdev(sizeof(struct sx_net_priv),
                                SPAN2CPU_IFNAME, NET_NAME_UNKNOWN,
                                sx_netdev_setup);

    if (!span2cpu_dev) {
        return -ENOMEM;
    }

    span2cpu_dev->features |= NETIF_F_HW_VLAN_CTAG_FILTER |
                              NETIF_F_HW_TC;
    span2cpu_dev->mtu = DEFAULT_FRAME_SIZE;

    span2cpu_dev->netdev_ops = netdev_ops;
    span2cpu_dev->ethtool_ops = ethtool_ops;
    random_ether_addr(span2cpu_dev->dev_addr);

    priv = netdev_priv(span2cpu_dev);
    priv->dev = g_sx_dev;

    rtnl_lock();
    if (register_netdevice(span2cpu_dev)) {
        rtnl_unlock();
        pr_err(PFX "Error when registering SPAN-to-CPU netdevice");
        free_netdev(span2cpu_dev);
        return -ENXIO;
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0)) || defined(CONFIG_SX_RHEL_8_6)
    dev_open(span2cpu_dev, NULL);
#else
    dev_open(span2cpu_dev);
#endif

    netif_carrier_off(span2cpu_dev);
    rtnl_unlock();

    return 0;
}

void sx_span2cpu_free_mirror_netdev(void)
{
    rtnl_lock();
    dev_close(span2cpu_dev);
    unregister_netdevice(span2cpu_dev);
    rtnl_unlock();
    free_netdev(span2cpu_dev);
}
#endif /* if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) */

/*
 * NETDEV is loaded with admin state down. User can change the admin state to UP and not the driver
 *
 *  static void netdev_adminstate_set(struct net_device *netdev, int should_rtnl_lock)
 *  {
 *   struct sx_net_priv *net_priv = netdev_priv(netdev);
 *
 *   if (should_rtnl_lock)
 *       rtnl_lock();
 *
 *   if (net_priv->admin_state) {
 *       dev_change_flags(netdev, netdev->flags | IFF_UP);
 *   } else {
 *       dev_change_flags(netdev, netdev->flags & ~IFF_UP);
 *   }
 *
 *   if (should_rtnl_lock)
 *       rtnl_unlock();
 *  }
 */

static void netdev_linkstate_set(struct net_device *netdev)
{
    struct sx_net_priv *net_priv = netdev_priv(netdev);

    if (carrier_set_on_pude_disable && net_priv->is_port_netdev && !net_priv->is_lag) {
        return;
    }

    if (net_priv->is_oper_state_up) {
        netif_carrier_on(netdev);
        netif_start_queue(netdev);
    } else {
        netif_tx_disable(netdev);
        netif_carrier_off(netdev);
    }
}

static int sx_netdev_rx_apply_vlan_logic(u8               vlan_child_exist,
                                         u8               is_tagged,
                                         struct sk_buff  *old_skb,
                                         struct sk_buff **new_skb_p,
                                         u16              pvid)
{
    struct vlan_hdr *vhdr = NULL;
    u32              vlan_tag = 0;
    u8              *p_skb_data = NULL;
    int              err = 0;
    struct sk_buff  *new_skb = NULL;

    skb_get(old_skb);
    /*
     * We copy old_skb to new_skb and add / edit vlan header if necessary.
     * The new_skb is IP align.
     */
    if (!untagged_pkt_pvid_tag_disable &&
        (is_tagged == VLAN_UNTAGGED_E) && vlan_child_exist) {
        new_skb = netdev_alloc_skb(NULL, old_skb->len + 4 + NET_IP_ALIGN);
        if (!new_skb) {
            err = -ENOMEM;
            goto out;
        }

        skb_reserve(new_skb, NET_IP_ALIGN);

        p_skb_data = skb_put(new_skb, old_skb->len + 4);
        if (!p_skb_data) {
            kfree_skb(new_skb);   /* drop flow, use kfree_skb */
            err = -ENOMEM;
            goto out;
        }

        vlan_tag = ETH_P_8021Q << 16;
        vlan_tag |= (pvid & 0x3fff);
        vlan_tag = cpu_to_be32(vlan_tag);
        memcpy(p_skb_data, old_skb->data, 12);
        memcpy(p_skb_data + 12, &vlan_tag, 4);
        memcpy(p_skb_data + 16, old_skb->data + 12, old_skb->len - 12);
    } else {
        if ((is_tagged == VLAN_PRIO_TAGGED_E) && vlan_child_exist) {
            vhdr = (struct vlan_hdr *)(old_skb->data + ETH_HLEN);
            vhdr->h_vlan_TCI = (vhdr->h_vlan_TCI & htons(~VLAN_VID_MASK)) | htons(pvid);
        }
        new_skb = netdev_alloc_skb(NULL, old_skb->len + NET_IP_ALIGN);
        if (!new_skb) {
            err = -ENOMEM;
            goto out;
        }
        skb_reserve(new_skb, NET_IP_ALIGN);
        memcpy(skb_put(new_skb, old_skb->len), old_skb->data, old_skb->len);
    }

    *new_skb_p = new_skb;

out:
    consume_skb(old_skb);   /* free unused skb, use consume_skb */
    return err;
}

static inline bool sx_is_arp_nd_on_network_port(struct completion_info *comp_info)
{
    return (comp_info->hw_synd == SXD_TRAP_ID_NVE_DECAP_ARP ||
            comp_info->hw_synd == SXD_TRAP_ID_OVERLAY_ICMPV6_CONF_TYPE);
}

#if defined(CONFIG_NET_SWITCHDEV) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0))
static void sx_skb_set_mr_fwd_mark(struct sk_buff *skb, u8 fwd_mark)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 0, 0)) || defined(CONFIG_SX_RHEL_8_6) || defined(CONFIG_SX_CENTOS_8_4)
    skb->offload_l3_fwd_mark = fwd_mark;
#else
    skb->offload_mr_fwd_mark = fwd_mark;
#endif
}
#endif

static void sx_netdev_fix_sx_skb(struct completion_info *comp_info, struct sk_buff *skb, struct net_device *netdev)
{
    struct ethhdr *eth_h = (struct ethhdr *)(skb->data);


    if (comp_info->hw_synd == SXD_TRAP_ID_ETH_L3_MTUERROR) {
        struct iphdr *ipptr;
        u32           new_checksum;
        u16           old_frag_off;

        if (be16_to_cpu(eth_h->h_proto) == ETH_P_8021Q) {
            ipptr = (struct iphdr *)(skb->data + VLAN_ETH_HLEN);
        } else {
            ipptr = (struct iphdr *)(skb->data + ETH_HLEN);
        }

        if (ipptr->version == IPVERSION) {
            /* RFC 1624 describes how to recalculate the checksum via incremental update */
            old_frag_off = be16_to_cpu(ipptr->frag_off); /* save old flags */
            if (!(old_frag_off & 0x4000)) { /* If don't fragment bit is not set */
                ipptr->frag_off = cpu_to_be16(old_frag_off | 0x4000); /* set Don't-Fragment bit */
                /* calculate the new checksum */
                new_checksum = (~old_frag_off & 0xffff) + (be16_to_cpu(ipptr->frag_off) & 0xffff); /* checksum' = ~m+m' */
                new_checksum += (~be16_to_cpu(ipptr->check) & 0xffff); /* checksum' += ~checksum */
                new_checksum = (new_checksum & 0xffff) + (new_checksum >> 16); /* Add carry if such exists */
                ipptr->check = cpu_to_be16(~(new_checksum + (new_checksum >> 16))); /* checksum' = ~checksum' */
            }
        }
    } else if (comp_info->hw_synd == SXD_TRAP_ID_ETH_L3_LBERROR) {
        memcpy(eth_h->h_dest, netdev->dev_addr, netdev->addr_len);
    }

    skb->dev = netdev;
    skb->protocol = eth_type_trans(skb, netdev);
    skb->ip_summed = CHECKSUM_UNNECESSARY; /* don't check it */

/* set offload mark of skb */
#if defined(CONFIG_NET_SWITCHDEV) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0))
    if (offload_fwd_mark_en) {
        skb->offload_fwd_mark = 1;
        if (arp_nd_mcast_sw_forwarding_enable) {
            if (sx_is_arp_nd_on_network_port(comp_info)) {
                sx_skb_set_mr_fwd_mark(skb, 0);
            } else {
                sx_skb_set_mr_fwd_mark(skb, 1);
            }
        }
    } else {
        skb->offload_fwd_mark = 0;
        sx_skb_set_mr_fwd_mark(skb, 0);
    }
#endif
}

static void sx_netdev_handle_rx(struct completion_info *comp_info, struct net_device *netdev)
{
    struct sx_net_priv         *net_priv = NULL;
    struct sk_buff             *skb;
    unsigned long               last_bit = 0;
    u8                          vlan_child_exist = 0;
    int                         ret = 0;
    struct skb_shared_hwtstamps hwts = *skb_hwtstamps(comp_info->skb);

    if (!netdev) {
        return;
    }

    if (!(netdev->flags & IFF_UP)) {
        if (sx_netdev_rx_debug) {
            printk(KERN_ERR "%s: netdev %s is down! dropping packet!\n", __func__, netdev->name);
        }
        return;
    }

    net_priv = netdev_priv(netdev);
    if (net_priv == NULL) {
        if (sx_netdev_rx_debug) {
            printk(KERN_ERR PFX "%s: net_priv is NULL\n", __func__);
        }
        return;
    }

    last_bit = find_last_bit(net_priv->active_vlans, VLAN_N_VID);
    vlan_child_exist = last_bit < VLAN_N_VID && last_bit != 0;
    ret = sx_netdev_rx_apply_vlan_logic(vlan_child_exist, comp_info->is_tagged, comp_info->skb, &skb, comp_info->vid);
    if (ret) {
        net_priv->stats.rx_dropped++;
        if (sx_netdev_rx_debug) {
            printk(KERN_ERR PFX "%s: failed to apply vlan logic\n", __func__);
        }
        return;
    }

    sx_netdev_fix_sx_skb(comp_info, skb, netdev);

    skb_hwtstamps(skb)->hwtstamp = hwts.hwtstamp;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) || defined(CONFIG_SX_RHEL_8_6)
    if (mirror_device_en && sx_span2cpu_is_span2cpu_pkt(comp_info)) {
        sx_span2cpu_send_to_mirror_taps(skb);
        dev_kfree_skb(skb);
        return;
    }
#endif

    net_priv->stats.rx_packets++;
    net_priv->stats.rx_bytes += skb->len;

    if (in_interrupt()) {
        netif_rx(skb);
    } else {
        netif_rx_ni(skb);
    }
}

static void sx_netdev_log_port_rx_pkt(struct completion_info *comp_info, void *context)
{
    /* Get routed netdev */
    u8                 i = 0, port_type = 0;
    int                num_netdevs = single_netdev_per_port_enable ? 1 : MAX_PORT_NETDEV_NUM;
    struct net_device *netdev;

    port_type = comp_info->is_lag ? PORT_TYPE_LAG : PORT_TYPE_SINGLE;

    rcu_read_lock();

    for (i = 0; i < num_netdevs; i++) {
        netdev = rcu_dereference(g_netdev_resources->port_netdev[port_type][comp_info->sysport][i]);
        if (netdev) {
            sx_netdev_handle_rx(comp_info, netdev);
        } else {
            if (sx_netdev_rx_debug) {
                printk(KERN_ERR "%s: %s %d index %d netdev is NULL! dropping packet!\n",
                       __func__,
                       comp_info->is_lag ? "lag" : "port",
                       comp_info->sysport, i);
            }
        }
    }

    rcu_read_unlock();
}

static void sx_netdev_phy_port_rx_pkt(struct completion_info *comp_info, void *context)
{
    /* Get routed netdev */
    struct net_device  *netdev = context, *port_netdev;
    struct sx_net_priv *net_priv = netdev_priv(netdev);
    uint16_t            local = comp_info->sysport;
    int                 num_netdevs;
    int                 ret = 0;
    u8                  i = 0;

    if (comp_info->is_lag) {
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_local,
                                   ret,
                                   net_priv->dev,
                                   comp_info->sysport,
                                   comp_info->lag_subport,
                                   &local);
        if (ret) {
            printk(KERN_ERR PFX "Fail to get local port from lag_id (%d) "
                   "and port index (%d)\n", comp_info->sysport, comp_info->lag_subport);
            return;
        }
    }

    num_netdevs = single_netdev_per_port_enable ? 1 : MAX_PORT_NETDEV_NUM;

    rcu_read_lock();

    for (i = 0; i < num_netdevs; i++) {
        port_netdev = rcu_dereference(g_netdev_resources->port_netdev[PORT_TYPE_SINGLE][local][i]);
        if (port_netdev) {
            sx_netdev_handle_rx(comp_info, port_netdev);
        } else {
            if (sx_netdev_rx_debug) {
                printk(KERN_ERR "%s: port %d index %d netdev is NULL! dropping packet!\n",
                       __func__, local, i);
            }
        }
    }

    rcu_read_unlock();
}


static void sx_netdev_handle_rx_pkt(struct completion_info *comp_info, void *context)
{
    struct net_device *netdev = context;

    if (netdev != NULL) {
        sx_netdev_handle_rx(comp_info, netdev);
    } else {
        if (sx_netdev_rx_debug) {
            printk(KERN_ERR "%s: netdev is NULL! dropping packet!\n", __func__);
        }
    }
}

static void __sx_netdev_pude_dwork_handler(struct work_struct *dwork_p)
{
    struct net_device  *netdev = NULL;
    struct sx_net_priv *net_priv = NULL;
    int                 i = 0;
    pude_dwdata_t      *dwdata_p = container_of(dwork_p, pude_dwdata_t, dwork.work);
    int                 is_up = dwdata_p->is_up;
    u16                 sysport = dwdata_p->sysport;

    mutex_lock(&g_netdev_resources->rsc_lock);

    /* Change port status for port netdev */
    for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
        netdev = g_netdev_resources->port_netdev[PORT_TYPE_SINGLE][sysport][i];
        if (netdev) {
            net_priv = netdev_priv(netdev);
            net_priv->is_oper_state_up = is_up;
            netdev_linkstate_set(netdev);
        }
    }

    mutex_unlock(&g_netdev_resources->rsc_lock);

    kfree(dwdata_p);
}

/* Called on every PUDE event */
static void sx_netdev_handle_pude_event(struct completion_info *comp_info, void *context)
{
    struct sxd_emad_pude_reg *pude = (struct sxd_emad_pude_reg *)comp_info->skb->data;
    struct sx_emad           *emad_header = &pude->emad_header;
    int                       reg_id = be16_to_cpu(emad_header->emad_op.register_id);
    unsigned int              logical_port = 0;
    uint16_t                  local_port = 0;
    int                       sysport = 0;
    int                       is_up = 0, is_lag = 0;
    unsigned short            type_len, ethertype;
    pude_dwdata_t            *dwdata_p;

    type_len = ntohs(pude->tlv_header.type_len);
    ethertype = ntohs(pude->emad_header.eth_hdr.ethertype);

    if ((ethertype != ETHTYPE_EMAD) || (reg_id != PUDE_REG_ID) ||
        ((type_len >> EMAD_TLV_TYPE_SHIFT) != TLV_TYPE_REG_E) ||
        ((type_len & 0x7FF) != 4)) {
        printk("%s: Called wrongly with ethtype = %04X and reg-id = %04X, type = %d, len = %d\n",
               __func__, comp_info->info.eth.ethtype, reg_id,
               type_len >> EMAD_TLV_TYPE_SHIFT, type_len & 0x7FF);
        return;
    }

    local_port = (((uint16_t)((pude->admin_status_lp_msb & 0x30) >> 4)) << 8) | pude->local_port;
    logical_port = 0x10000 + (local_port << SX_PORT_PHY_ID_OFFS);
    if (sx_netdev_sx_core_if_get_reference()) {
        if (!g_sx_dev) {
            printk(KERN_INFO PFX "g_sx_dev is NULL\n");
            sx_netdev_sx_core_if_release_reference();
            return;
        } else {
            sysport = translate_user_port_to_sysport(g_sx_dev, logical_port, &is_lag);
        }
        sx_netdev_sx_core_if_release_reference();
    } else {
        printk(KERN_INFO PFX "sx_core_if is not initialized\n");
        return;
    }
    /* if port is a LAG port do nothing */
    if (is_lag) {
        return;
    }
    is_up = pude->oper_status == SXD_PAOS_OPER_STATUS_UP_E;

    if (!carrier_set_on_pude_disable) {
        printk("%s: Called for logical port - %05X status %s\n", __func__,
               logical_port, is_up ? "UP" : "DOWN");
    }

    dwdata_p = kzalloc(sizeof(*dwdata_p), GFP_ATOMIC);
    if (!dwdata_p) {
        printk(KERN_ERR "PUDE handler failed to allocated memory\n");
        return;
    }
    dwdata_p->is_up = is_up;
    dwdata_p->sysport = sysport;
    INIT_DELAYED_WORK(&dwdata_p->dwork, __sx_netdev_pude_dwork_handler);
    /* The delayed queueing used to change context */
    queue_delayed_work(g_netdev_wq, &dwdata_p->dwork, 0);
}

static void sx_netdev_remove_vlan_header(struct sk_buff *skb)
{
    struct vlan_ethhdr *veth = NULL;

    veth = (struct vlan_ethhdr *)(skb->data);

    if (ntohs(veth->h_vlan_proto) != ETH_P_8021Q) {
        /* No vlan header */
        return;
    }

    /* set the protocol in ETH header */
    veth->h_vlan_proto = veth->h_vlan_encapsulated_proto;

    /* remove the VLAN header */
    memmove(skb->data + VLAN_HLEN, skb->data, ETH_HLEN);
    skb->mac_header += VLAN_HLEN;
    skb_pull(skb, VLAN_HLEN);

    skb_reset_network_header(skb);
    skb_reset_transport_header(skb);
    /* skb_reset_mac_len */
    skb->mac_len = skb->network_header - skb->mac_header;
}

static void __sx_netdev_handle_global_pkt(struct net_device *netdev, struct completion_info *comp_info)
{
    struct sx_net_priv *net_priv = NULL;
    int                 err = 0;
    u16                 vlan = 0;

    if (!netdev) {
        if (sx_netdev_rx_debug) {
            printk(KERN_ERR "%s: netdev is NULL! dropping packet!\n", __FUNCTION__);
        }
        return;
    }

    /* SX: if RP netdev existed than pass the packet up with this netdev */
    net_priv = netdev_priv(netdev);
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_rp_vlan, err, net_priv->dev, comp_info, &vlan);
    if (err) {
        printk(KERN_ERR PFX "Failed sx_core_get_rp_vlan(). err: %d \n", err);
    }
    comp_info->vid = vlan;
    sx_netdev_handle_rx(comp_info, netdev);
}

static void sx_netdev_handle_global_pkt(struct completion_info *comp_info, void *context)
{
    struct net_device *netdev = NULL;
    u8                 port_type = 0, i = 0;

    if (comp_info->bridge_id) {
        if ((comp_info->bridge_id < MIN_BRIDGE_ID)
            || (comp_info->bridge_id > MAX_BRIDGE_ID)) {
            printk(KERN_ERR PFX "Bridge ID %u is out of range [%u,%u]\n",
                   comp_info->bridge_id, MIN_BRIDGE_ID, MAX_BRIDGE_ID);
            return;
        }
        netdev = bridge_netdev_db[comp_info->bridge_id - MIN_BRIDGE_ID];
        __sx_netdev_handle_global_pkt(netdev, comp_info);
    } else {
        port_type = comp_info->is_lag ? PORT_TYPE_LAG : PORT_TYPE_SINGLE;

        rcu_read_lock();

        for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
            netdev = rcu_dereference(g_netdev_resources->port_netdev[port_type][comp_info->sysport][i]);
            if (netdev) {
                __sx_netdev_handle_global_pkt(netdev, comp_info);
            }
        }

        rcu_read_unlock();
    }
}

static int sx_netdev_register_global_event_handler(void)
{
    int                       err = 0;
    union ku_filter_critireas crit;

    /* Register listener for Ethernet SWID */
    memset(&crit, 0, sizeof(crit));
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd,
                               err,
                               ROUTER_PORT_SWID,
                               NUM_HW_SYNDROMES,
                               L2_TYPE_DONT_CARE,
                               0,
                               "sx_netdev",
                               0,
                               &crit,
                               sx_netdev_handle_global_pkt,
                               NULL,
                               CHECK_DUP_DISABLED_E,
                               g_sx_dev,
                               NULL,
                               1);
    if (err) {
        printk(KERN_ERR PFX "%s: Failed registering global rx_handler", __func__);
        return err;
    }
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd, err, 0, SXD_TRAP_ID_PUDE, L2_TYPE_DONT_CARE, 0, "sx_netdev", 0,
                               &crit, sx_netdev_handle_pude_event, NULL,
                               CHECK_DUP_DISABLED_E, g_sx_dev, NULL, 1);
    if (err) {
        printk(KERN_ERR PFX "%s: Failed registering PUDE event rx_handler", __func__);
        return err;
    }

    return 0;
}

static int sx_netdev_unregister_global_event_handler(void)
{
    int                       err = 0;
    union ku_filter_critireas crit;

    memset(&crit, 0, sizeof(crit));
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_remove_synd, err, ROUTER_PORT_SWID, NUM_HW_SYNDROMES, L2_TYPE_DONT_CARE, 0,
                               &crit, NULL, g_sx_dev, NULL, NULL, 1, NULL);
    if (err) {
        printk(KERN_ERR PFX "error: Failed de registering on "
               "0x%x syndrome.\n", NUM_HW_SYNDROMES);
        return err;
    }

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_remove_synd, err, 0, SXD_TRAP_ID_PUDE, L2_TYPE_DONT_CARE, 0,
                               &crit, NULL, g_sx_dev, NULL, NULL, 1, NULL);
    if (err) {
        printk(KERN_ERR PFX "error: Failed de registering on "
               "0x%x syndrome.\n", SXD_TRAP_ID_PUDE);
        return err;
    }

    CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_flush_synd_by_handler, sx_netdev_handle_global_pkt);
    return err;
}

static int __sx_netdev_uc_type_get_data(enum sx_netdev_user_channel_type uc_type,
                                        union ku_filter_critireas       *crit_p,
                                        cq_handler                      *netdev_callback_p)
{
    int                       err = 0;
    union ku_filter_critireas crit;
    cq_handler                netdev_callback = 0;

    memset(&crit, 0, sizeof(crit)); /* sets all ETH values to default */
    switch (uc_type) {
    case USER_CHANNEL_L3_NETDEV:
        netdev_callback = sx_netdev_handle_rx_pkt;
        crit.eth.from_rp = IS_RP_NOT_FROM_RP_E;
        crit.eth.from_bridge = IS_BRIDGE_NOT_FROM_BRIDGE_E;
        break;

    case USER_CHANNEL_LOG_PORT_NETDEV:
        netdev_callback = sx_netdev_log_port_rx_pkt;
        crit.eth.from_rp = IS_RP_DONT_CARE_E;
        crit.eth.from_bridge = IS_BRIDGE_DONT_CARE_E;
        break;

    case USER_CHANNEL_PHY_PORT_NETDEV:
        netdev_callback = sx_netdev_phy_port_rx_pkt;
        crit.eth.from_rp = IS_RP_DONT_CARE_E;
        crit.eth.from_bridge = IS_BRIDGE_DONT_CARE_E;
        break;

    default:
        printk("unsupported user channel type (%d).\n", uc_type);
        err = -ERANGE;
        goto out;
        break;
    }

    memcpy(crit_p, &crit, sizeof(crit));
    memcpy(netdev_callback_p, &netdev_callback, sizeof(netdev_callback));

out:
    return err;
}


static void sx_timestamp_init_config(struct hwtstamp_config *hwtstamp_config)
{
    hwtstamp_config->tx_type = HWTSTAMP_TX_OFF;
    hwtstamp_config->rx_filter = HWTSTAMP_FILTER_NONE;
}

static int sx_netdev_open(struct net_device *netdev)
{
    int                        err = 0;
    struct sx_net_priv        *net_priv = netdev_priv(netdev);
    union ku_filter_critireas  crit;
    cq_handler                 netdev_callback = 0;
    int                        i;
    u8                         uc_type = 0;
    struct ku_port_vlan_params port_vlan;

    pr_debug(PFX "%s: called\n", __func__);

    if ((!net_priv->is_lag) && ((netdev->dev_addr[0] == 0) && (netdev->dev_addr[1] == 0) &&
                                (netdev->dev_addr[2] == 0) && (netdev->dev_addr[3] == 0) &&
                                (netdev->dev_addr[4] == 0) && (netdev->dev_addr[5] == 0))) {
        printk(KERN_ERR PFX "error %s, no mac address set.\n",
               netdev->name);
        return -EINVAL;
    }

    netdev_linkstate_set(netdev);

    for (uc_type = USER_CHANNEL_L3_NETDEV; uc_type < NUM_OF_NET_DEV_TYPE; uc_type++) {
        err = __sx_netdev_uc_type_get_data(uc_type, &crit, &netdev_callback);
        if (err) {
            printk(KERN_ERR PFX "%s: Failed get crit and handler for "
                   "user channel (%d).\n", __func__, uc_type);
            goto out;
        }

        for (i = 0; i < net_priv->num_of_traps[uc_type]; i++) {
            port_vlan.port_vlan_type = net_priv->trap_ids[uc_type][i].info_type;
            port_vlan.sysport = net_priv->trap_ids[uc_type][i].sysport;
            port_vlan.lag_id = net_priv->trap_ids[uc_type][i].lag_id;
            port_vlan.vlan = net_priv->trap_ids[uc_type][i].vlan;
            CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd,
                                       err,
                                       net_priv->swid,
                                       net_priv->trap_ids[uc_type][i].synd,
                                       L2_TYPE_ETH,
                                       0,
                                       "sx_netdev",
                                       0,
                                       &crit,
                                       netdev_callback,
                                       netdev,
                                       CHECK_DUP_DISABLED_E,
                                       net_priv->dev,
                                       &port_vlan,
                                       1);
            if (err) {
                printk(KERN_ERR PFX "error %s, User channel (%d) failed registering on "
                       "0x%x syndrome.\n", netdev->name, uc_type, net_priv->trap_ids[uc_type][i].synd);
                goto out;
            }
        }
    }

    sx_timestamp_init_config(&net_priv->hwtstamp_config);

#if defined(CONFIG_NET_PORT) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)))
    port_init_ethtool_stats(netdev);
#endif

out:
    pr_debug(PFX "%s: exit\n", __func__);
    return err;
}

static int sx_netdev_stop(struct net_device *netdev)
{
    struct sx_net_priv        *net_priv = netdev_priv(netdev);
    union ku_filter_critireas  crit;
    cq_handler                 netdev_callback = 0;
    int                        i;
    u8                         uc_type = 0;
    struct ku_port_vlan_params port_vlan;

    pr_debug(PFX "%s: called\n", __func__);

    for (uc_type = USER_CHANNEL_L3_NETDEV; uc_type < NUM_OF_NET_DEV_TYPE; uc_type++) {
        if (__sx_netdev_uc_type_get_data(uc_type, &crit, &netdev_callback)) {
            printk(KERN_ERR PFX "%s: Failed get crit and handler for "
                   "user channel (%d).\n", __func__, uc_type);
            continue;
        }

        for (i = 0; i < net_priv->num_of_traps[uc_type]; i++) {
            port_vlan.port_vlan_type = net_priv->trap_ids[uc_type][i].info_type;
            port_vlan.sysport = net_priv->trap_ids[uc_type][i].sysport;
            port_vlan.lag_id = net_priv->trap_ids[uc_type][i].lag_id;
            port_vlan.vlan = net_priv->trap_ids[uc_type][i].vlan;
            CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_remove_synd, net_priv->swid, net_priv->trap_ids[uc_type][i].synd,
                                          L2_TYPE_ETH, 0, &crit, netdev, net_priv->dev,
                                          netdev_callback, &port_vlan, 1, NULL);
        }
    }

    netif_tx_disable(netdev);
    netif_carrier_off(netdev);

    pr_debug(PFX "%s: exit\n", __func__);
    return 0;
}

void sx_netdev_set_lag_oper_state(struct sx_dev *dev, u16 lag_id, u8 oper_state)
{
    struct net_device  *netdev = NULL;
    struct sx_net_priv *net_priv;
    uint16_t            lag_max = 0, lag_member_max = 0;
    int                 err = 0;
    u8                  i = 0;

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_lag_max, err, dev, &lag_max, &lag_member_max);
    if (err) {
        printk(KERN_ERR PFX "Failed to get max number of LAGs. err = %u.\n", err);
        return;
    }

    if (lag_id >= lag_max) {
        net_err_ratelimited(PFX "%s: lag_id %d is invalid. (MAX %d).\n", __func__,
                            lag_id, lag_max);
        return;
    }

    pr_debug("%s: Called for lag_id %d  status %s\n", __func__,
             lag_id, oper_state ? "UP" : "DOWN");

    mutex_lock(&g_netdev_resources->rsc_lock);

    /* Change port netdev status */
    for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
        netdev = g_netdev_resources->port_netdev[PORT_TYPE_LAG][lag_id][i];
        if (netdev) {
            net_priv = netdev_priv(netdev);
            net_priv->is_oper_state_up = oper_state;
            netdev_linkstate_set(netdev);
        }
    }

    mutex_unlock(&g_netdev_resources->rsc_lock);
}

static int sx_netdev_get_port_prio_to_tc(struct net_device *netdev, struct sk_buff *skb, uint8_t *tc)
{
    struct sx_net_priv *net_priv = netdev_priv(netdev);
    uint8_t             pcp;
    u16                 vlan_tci;
    struct vlan_ethhdr *veth = NULL;
    int                 err = 0;

    *tc = 0;

    veth = (struct vlan_ethhdr *)(skb->data);
    if (ntohs(veth->h_vlan_proto) != ETH_P_8021Q) {
        /* We can reach this case if pkt was sent from phys. port netdev */
        if (sx_netdev_tx_debug) {
            printk(KERN_DEBUG PFX "VETH proto (0x%x) is not ETH_P_8021Q !\n",
                   veth->h_vlan_proto);
        }
        *tc = SX_PACKET_DEFAULT_TC;
        return 0;
    }

    vlan_tci = ntohs(veth->h_vlan_TCI);
    pcp = (vlan_tci & SX_VLAN_PRIO_MASK) >> SX_VLAN_PRIO_SHIFT;

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_prio2tc, err, net_priv->dev,
                               net_priv->port, net_priv->is_lag, pcp, tc);

    return err;
}

static int sx_netdev_set_vlan_according_hw(struct net_device *netdev, struct sk_buff *skb)
{
    struct sx_net_priv *net_priv = netdev_priv(netdev);
    uint16_t            vlan;
    uint8_t             is_tagged, is_prio_tagged;
    struct vlan_ethhdr *veth = NULL;
    int                 err = 0;
    unsigned long       last_bit = 0;
    u8                  vlan_child_exist = 0;

    veth = (struct vlan_ethhdr *)(skb->data);
    if (ntohs(veth->h_vlan_proto) != ETH_P_8021Q) {
        /* We can reach this case if packet was sent from port netdev */
        if (sx_netdev_tx_debug) {
            printk(KERN_DEBUG PFX "%s: No vlan header.\n", __func__);
        }
        return 0;
    }

    last_bit = find_last_bit(net_priv->active_vlans, VLAN_N_VID);
    vlan_child_exist = last_bit < VLAN_N_VID && last_bit != 0;

    /* We apply vlan tagging logic only if netdev has vlan child */
    if (!vlan_child_exist) {
        if (sx_netdev_tx_debug) {
            printk(KERN_DEBUG PFX "%s: netdev (%s) No vlan child.\n", __func__, netdev->name);
        }
        return 0;
    }

    vlan = ntohs(veth->h_vlan_TCI) & VLAN_VID_MASK;
    if (vlan > 4094) {
        printk(KERN_ERR PFX "%s: VETH vlan (%d) is very big. MAX: %d.\n",
               __func__, vlan, 4094);
        return -EINVAL;
    }

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_vlan_tagging, err, net_priv->dev,
                               net_priv->port, net_priv->is_lag, vlan, &is_tagged);
    if (err) {
        printk(KERN_ERR PFX "sx_core_get_vlan_tagging is failed. err: %d\n", err);
        return err;
    }

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_prio_tagging, err, net_priv->dev,
                               net_priv->port, net_priv->is_lag, &is_prio_tagged);
    if (err) {
        printk(KERN_ERR PFX "sx_core_get_prio_tagging is failed. err: %d\n", err);
        return err;
    }

    if (sx_netdev_tx_debug) {
        printk(KERN_DEBUG PFX "is_lag:%d, port:%d, vlan (from header):%d port is_tagged:%d, port is_prio_tag:%d.\n",
               net_priv->is_lag, net_priv->port, vlan, is_tagged, is_prio_tagged);
    }

    /*
     * If port is VLAN tagged than send the packet with TAG
     * Else if port is Prio-tagged send the packet with Prio tag (zero the VLAN id)
     * Else send packet untagged
     */
    if (!is_tagged && is_prio_tagged) {
        /* port is PRIO tagged (but not VLAN tagged): send the packet prio tagged */
        veth->h_vlan_TCI &= ~(htons(VLAN_VID_MASK));
        if (sx_netdev_tx_debug) {
            printk(KERN_DEBUG PFX "Port is not vlan tag but prio tag, clear the vlan: vlan_tci:0x%x.\n",
                   veth->h_vlan_TCI);
        }
    } else if (!is_tagged && !is_prio_tagged) {
        if (sx_netdev_tx_debug) {
            printk(KERN_DEBUG PFX "Port is not vtag and not prio tag, remove vlan header.\n");
        }
        /* send the packet untagged */
        sx_netdev_remove_vlan_header(skb);
    } else {
        /* else port is VLAN tagged and send the packet as is */
        if (sx_netdev_tx_debug) {
            printk(KERN_DEBUG PFX "Port is vlan tagged. do nothing.\n");
        }
    }

    return 0;
}


static int sx_netdev_override_icmp_ip(struct net_device *netdev, struct sk_buff *skb)
{
    struct sx_net_priv *net_priv = netdev_priv(netdev);
    uint16_t            vlan;
    struct vlan_ethhdr *veth = NULL;
    int                 err = 0;
    uint32_t            ip_addr;
    struct iphdr      * iph = NULL;
    struct icmphdr    * icmph = NULL;

    veth = (struct vlan_ethhdr *)(skb->data);
    if (ntohs(veth->h_vlan_proto) != ETH_P_8021Q) {
        /* We can reach this case if pkt was sent from phys. port netdev */
        if (sx_netdev_tx_debug) {
            printk(KERN_DEBUG PFX "VETH proto (0x%x) is not ETH_P_8021Q !\n",
                   veth->h_vlan_proto);
        }
        return 0;
    }

    /* is packet icmp type 5 */

    vlan = ntohs(veth->h_vlan_TCI) & VLAN_VID_MASK;
    if (vlan > 4094) {
        printk(KERN_ERR PFX "VETH vlan (%d) is very big . MAX: %d !\n",
               vlan, 4094);
        return -EINVAL;
    }

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_vlan2ip, err, net_priv->dev, vlan, &ip_addr);
    if (err) {
        printk(KERN_ERR PFX "sx_core_get_vlan2ip is failed. err: %d\n", err);
        return err;
    }

    if (ip_addr == 0) {
        return 0;
    }

    iph = (struct iphdr*)(skb->data + sizeof(struct vlan_ethhdr));
    if (iph->protocol != IPPROTO_ICMP) {
        return 0;
    }

    icmph = (struct icmphdr *)skb_transport_header(skb);
    if (icmph->type != ICMP_REDIRECT) {
        return 0;
    }

    /* override SIP with DB IP */
    iph->saddr = htonl(ip_addr);

    /* recalc checksum */
    ip_send_check(iph);

    return 0;
}


/* change skb to hold 'control' traffic (rather than 'data' traffic) */
static int __set_as_control_traffic(struct sk_buff *skb, struct net_device *netdev, struct isx_meta *meta)
{
    struct sx_net_priv *net_priv = netdev_priv(netdev);
    uint8_t             tc;
    int                 err;

    meta->system_port_mid = net_priv->is_lag ? net_priv->mid : net_priv->port;
    meta->type = SX_PKT_TYPE_ETH_CTL_UC;

    /* Set etclass
     * SX: get tc from pcp.
     * SPC: etclass 0 (overwritten in post_send) */
    err = sx_netdev_get_port_prio_to_tc(netdev, skb, &tc);
    if (err) {
        printk(KERN_ERR PFX "%s: Err: can't get prio to tc\n", __func__);
        goto error;
    }

    meta->etclass = tc; /* High priority */
    err = sx_netdev_set_vlan_according_hw(netdev, skb);
    if (err) {
        printk(KERN_ERR PFX "%s: Err: can't set vlan according hw.\n", __func__);
        goto error;
    }

    return 0;

error:

    net_priv->stats.tx_dropped++;
    kfree_skb(skb); /* drop packet flow, use kfree_skb */
    return err;
}

static int __is_ifc_router_port(struct sk_buff    *skb,
                                struct net_device *netdev,
                                u8                *is_ifc_router_port,
                                uint16_t          *ifc_vlan)
{
    struct sx_net_priv *net_priv = netdev_priv(netdev);
    int                 err = 0;
    uint16_t            vlan = 0;
    u8                  is_from_rp = 0;
    struct vlan_ethhdr *veth = NULL;

    if ((skb == NULL) || (netdev == NULL)) {
        err = -EINVAL;
        printk(KERN_ERR PFX "%s: skb (%p) or netdev (%p) is NULL\n",
               __func__, skb, netdev);
        goto error;
    }

    veth = (struct vlan_ethhdr *)(skb->data);
    if (ntohs(veth->h_vlan_proto) == ETH_P_8021Q) {
        vlan = ntohs(veth->h_vlan_TCI) & VLAN_VID_MASK;
        if (vlan > 4094) {
            err = -EINVAL;
            printk(KERN_ERR PFX "%s: VETH vlan (%d) is very big . MAX: %d.\n",
                   __func__, vlan, 4094);
            goto error;
        }
    }
    if (vlan == 0) {
        /* packet is untagged or prio tagged */
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_pvid, err, net_priv->dev, net_priv->port,
                                   net_priv->is_lag, &vlan);
        if (err) {
            if (printk_ratelimit()) {
                printk(KERN_ERR PFX "%s: can't get pvid for port\n", __func__);
            }
            goto error;
        }
    }

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_rp_mode, err, net_priv->dev,
                               net_priv->is_lag, net_priv->port, vlan, &is_from_rp);
    if (err) {
        if (printk_ratelimit()) {
            printk(KERN_ERR PFX "%s: Can't get rp mode for port\n", __func__);
        }
        goto error;
    }

    if (is_ifc_router_port != NULL) {
        *is_ifc_router_port = is_from_rp;
    }

    if (ifc_vlan != NULL) {
        *ifc_vlan = vlan;
    }

    return err;

error:
    kfree_skb(skb); /* drop packet flow, use kfree_skb */
    net_priv->stats.tx_dropped++;
    return err;
}

static int __send_to_port_as_data(struct sk_buff *skb, struct net_device *netdev, struct isx_meta *meta, uint16_t vlan)
{
    struct sx_net_priv *net_priv = netdev_priv(netdev);
    int                 err = 0;
    uint16_t            hw_efid = 0;

    meta->type = SX_PKT_TYPE_ETH_DATA;
    meta->rx_is_router = 1;
    meta->fid_valid = 1;
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_rp_rfid, err, net_priv->dev,
                               net_priv->port, net_priv->is_lag, vlan, &hw_efid);
    if (err) {
        if (printk_ratelimit()) {
            printk(KERN_ERR PFX "%s: Can't get rp fid\n", __func__);
        }
        goto error;
    }
    meta->fid = hw_efid;

    return 0;

error:
    net_priv->stats.tx_dropped++;
    kfree_skb(skb); /* drop packet flow, use kfree_skb */
    return err;
}

struct ptp_tx_skb_info {
    bool         valid;
    u8           shinfo_tx_flags;
    struct sock *skb_sk;
    char         skb_cb[sizeof(((struct sk_buff*)NULL)->cb)];
};

static int sx_netdev_hard_start_xmit(struct sk_buff *skb, struct net_device *netdev)
{
    struct sx_net_priv    *net_priv = netdev_priv(netdev);
    int                    err = 0;
    int                    len = 0;
    struct isx_meta        meta;
    struct sk_buff        *tmp_skb = NULL;
    struct vlan_ethhdr    *veth = NULL;
    u16                    pcp = 0;
    uint16_t               ifc_vlan = 0;
    u8                     is_ifc_rp = 0;
    struct ptp_tx_skb_info ptp_skb_info = {
        .valid = false
    };
    u8                     is_tagged;
    bool                   is_ptp_pkt = false;

    if (net_priv->dev == NULL) {
        if (printk_ratelimit()) {
            printk(KERN_ERR PFX "sx_netdev_hard_start_"
                   "xmit: netdev %s net_priv->dev is NULL.\n", netdev->name);
        }
        net_priv->stats.tx_dropped++;
        kfree_skb(skb); /* drop packet flow, use kfree_skb */
        return -ENXIO;
    }

    veth = (struct vlan_ethhdr *)(skb->data);
    is_tagged = (ntohs(veth->h_vlan_proto) == ETH_P_8021Q);

    sx_netdev_override_icmp_ip(netdev, skb);

    if (sx_netdev_tx_debug) {
        printk(KERN_DEBUG PFX "%s called for (%s)\n", __func__, netdev->name);
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0)) || defined(CONFIG_SX_RHEL_7_4) || defined(CONFIG_SX_RHEL_7_6)
    netif_trans_update(netdev); /* save the timestamp */
#else
    netdev->trans_start = jiffies; /* save the timestamp */
#endif

    memset(&meta, 0, sizeof(meta));
    meta.dev_id = net_priv->dev->device_id;
    meta.lp = 0;
    meta.rdq = 0;
    meta.swid = net_priv->swid;
    meta.to_cpu = 0;

    if (net_priv->is_bridge) {
        /*
         * Bridge: send as data
         */
        meta.type = SX_PKT_TYPE_ETH_DATA;
        meta.rx_is_router = 0;
        meta.fid_valid = 1;
        meta.fid = net_priv->bridge_id;
    } else if (!net_priv->is_port_netdev) {
        /*
         * swid0_eth: send as data
         */
        meta.type = SX_PKT_TYPE_ETH_DATA;
        meta.system_port_mid = 0;
    } else if (!net_priv->send_to_port_as_data_supported) {
        /*
         * SX port: send as control
         */
        err = __set_as_control_traffic(skb, netdev, &meta);
        if (err) {
            return err;
        }
    } else { /* net_priv->send_to_port_as_data_supported == true */
             /*
              * Spc port
              */

        err = __is_ifc_router_port(skb, netdev, &is_ifc_rp, &ifc_vlan);
        if (err) {
            return err;
        }

        /*
         * If Port or LAG is router port then send as data
         * else send as Control
         */
        if (is_ifc_rp) {
            err = __send_to_port_as_data(skb, netdev, &meta, ifc_vlan);
        } else {
            err = __set_as_control_traffic(skb, netdev, &meta);
        }
        if (err) {
            return err;
        }
    }

    if (meta.type == SX_PKT_TYPE_ETH_DATA) {
        meta.rx_is_tunnel = net_priv->skip_tunnel;
    }

    if (net_priv->hwtstamp_config.tx_type != HWTSTAMP_TX_OFF) {
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_ptp_tx_handler,
                                   err,
                                   net_priv->dev,
                                   skb,
                                   net_priv->port,
                                   net_priv->is_lag,
                                   &is_ptp_pkt);

        if (err) {
            if (printk_ratelimit()) {
                printk(KERN_ERR "failed to handle PTP TX packet (err=%d)\n", err);
            }
        } else if (is_ptp_pkt) {
            /* we should save these local parameters in case skb will be replaced in this function (a VLAN
             * header should be added or not enough headroom */
            ptp_skb_info.valid = true;
            ptp_skb_info.shinfo_tx_flags = skb_shinfo(skb)->tx_flags;
            ptp_skb_info.skb_sk = skb->sk;
            memcpy(ptp_skb_info.skb_cb, skb->cb, sizeof(ptp_skb_info.skb_cb));

            /* *****************************************/
            /* Apply SPC2/3 PTP WA                     */

            CALL_SX_CORE_FUNC_WITH_RET(sx_core_ptp_tx_control_to_data,
                                       err,
                                       net_priv->dev,
                                       &skb,
                                       &meta,
                                       net_priv->port,
                                       net_priv->is_lag,
                                       &is_tagged);

            if (err) {
                kfree_skb(skb); /* drop packet flow, use kfree_skb */
                return err;
            }
        }
    }

    /* *****************************************/
    if (sx_netdev_tx_debug) {
        printk(
            KERN_INFO PFX "is_tagged:%d , skb->tx_flags:0x%x, skb->priority:%d meta.type:%d ,is_ifc_rp:%d, ifc_vlan: %d\n",
            is_tagged,
            skb_shinfo(skb)->tx_flags,
            skb->priority,
            meta.type,
            is_ifc_rp,
            ifc_vlan);
    }

    if (!is_tagged && (((skb->priority != 0) && (meta.type == SX_PKT_TYPE_ETH_DATA)) || is_ifc_rp)) {
        /* If it is a DATA packet and it is untagged, add prio tag (PCP according to skb->priority) */
        if (skb->priority > SX_VLAN_PRIO_MAX) {
            if (sx_netdev_tx_debug) {
                printk(KERN_INFO PFX "%s: skb priority is to big. set max pcp %d\n", __func__, SX_VLAN_PRIO_MAX);
            }
            pcp = SX_VLAN_PRIO_MAX;
        } else {
            pcp = skb->priority;
        }

        CALL_SX_CORE_FUNC_WITH_RET(sx_core_skb_add_vlan, err, &skb, ifc_vlan, pcp); /* skb may change pointer here ... */
        if (err) {
            if (printk_ratelimit()) {
                printk(KERN_ERR PFX "%s: Fail to alloc skb with vlan header\n", __func__);
            }

            kfree_skb(skb); /* drop packet flow, use kfree_skb */
            net_priv->stats.tx_dropped++;
            return err;
        }

        is_tagged = 1;
    }

    /* If there's no place for the ISX header
     * need to alloc a new skb and use it instead */
    tmp_skb = skb;
    len = skb->len;
    if (skb_headroom(skb) < ISX_HDR_SIZE) {
        if (sx_netdev_tx_debug) {
            printk(KERN_INFO PFX "sx_netdev_hard_start_xmit: "
                   "No place for the ISX header, allocating a new "
                   "SKB\n");
        }
        tmp_skb = alloc_skb(ISX_HDR_SIZE + len, GFP_ATOMIC);
        if (!tmp_skb) {
            if (printk_ratelimit()) {
                printk(KERN_ERR PFX "sx_netdev_hard_start_"
                       "xmit: Err: failed allocating "
                       "SKB\n");
            }
            net_priv->stats.tx_dropped++;
            kfree_skb(skb); /* drop packet flow, use kfree_skb */
            return -ENOMEM;
        }

        skb_reserve(tmp_skb, ISX_HDR_SIZE);
        memcpy(skb_put(tmp_skb, len), skb->data, len);
        consume_skb(skb);   /* free unused skb, use consume_skb */
        len += ISX_HDR_SIZE;
    }

    if (ptp_skb_info.valid) {
        /* need to override these parameters with the ones we saved in this function. skb may have replaced
         * (allocated again) and these old parameters does not exist there anymore */
        skb_shinfo(tmp_skb)->tx_flags = ptp_skb_info.shinfo_tx_flags;
        tmp_skb->sk = ptp_skb_info.skb_sk;
        memcpy(tmp_skb->cb, ptp_skb_info.skb_cb, sizeof(skb->cb));
    }

    if (sx_netdev_sx_core_if_get_reference()) {
        err = sx_core_post_send(net_priv->dev, tmp_skb, &meta);
        sx_netdev_sx_core_if_release_reference();
    } else {
        printk(KERN_INFO PFX "sx_core_if is not initialized\n");
        err = -ENXIO;
        kfree_skb(tmp_skb); /* drop packet flow, use kfree_skb */
    }

    if (err) {
        pr_debug(PFX "error %s, Failed sending packet\n",
                 netdev->name);
        net_priv->stats.tx_dropped++;
        /*
         *  We don't free the packet because sx_core_post_send free the packet in case of an error.
         *  We return NETDEV_TX_OK in case of ERROR because a nonzero return value indicates that the packet
         *  could not be transmitted at this time and the kernel will retry later.
         */
        return NETDEV_TX_OK;
    }

    net_priv->stats.tx_bytes += len;
    net_priv->stats.tx_packets++;

    return NETDEV_TX_OK;
}

static struct net_device_stats * sx_netdev_get_stats(struct net_device *netdev)
{
    struct sx_net_priv *net_priv = netdev_priv(netdev);

    return &net_priv->stats;
}

static void sx_netdev_set_multicast(struct net_device *netdev)
{
    return;
}

static int sx_netdev_set_mac(struct net_device *netdev, void *p)
{
    struct sx_net_priv *net_priv = netdev_priv(netdev);
    struct sockaddr    *addr = p;

    if (!is_valid_ether_addr(addr->sa_data)) {
        printk(KERN_INFO PFX "address not given.");
        return -EADDRNOTAVAIL;
    }

    memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);
    net_priv->mac = sx_netdev_mac_to_u64(netdev->dev_addr);

    return 0;
}

#if defined(CONFIG_NET_SWITCHDEV) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9,  \
                                                                           0)) && \
    (LINUX_VERSION_CODE < KERNEL_VERSION(5, 1, 0)) && !defined(CONFIG_SX_RHEL_8_6) && !defined(CONFIG_SX_CENTOS_8_4)
/* SWITCHDEV_ATTR_ID_PORT_PARENT_ID removed in kernel 5.1.0 */
int sx_netdev_attr_get(struct net_device *netdev, struct switchdev_attr *attr)
{
    switch (attr->id) {
    case SWITCHDEV_ATTR_ID_PORT_PARENT_ID:
        attr->u.ppid.id_len = ETH_ALEN;
        /* The attr->u.ppid.id is needed to distinguish between port that belong
         *  to SW1 and port that belong to SW2 on multi-chip platforms.
         *  Our platform is single switch so FF..FF id will be used */
        memset(attr->u.ppid.id, 0xFF, attr->u.ppid.id_len);
        break;

    default:
        return -EOPNOTSUPP;
    }

    return 0;
}

static const struct switchdev_ops sx_netdev_switchdev_ops = {
    .switchdev_port_attr_get = sx_netdev_attr_get,
};
#endif

#if defined(CONFIG_NET_SWITCHDEV) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(5, 1, 0)) || defined(CONFIG_SX_RHEL_8_6))
/* ndo_get_port_parent_id() replaced SWITCHDEV_ATTR_ID_PORT_PARENT_ID in kernel 5.1.0 */
int sx_netdev_get_port_parent_id(struct net_device *dev, struct netdev_phys_item_id *ppid)
{
    ppid->id_len = ETH_ALEN;

    /* The ppid id is needed to distinguish between port that belong
     *  to SW1 and port that belong to SW2 on multi-chip platforms.
     *  Our platform is single switch so FF..FF id will be used */
    memset(&ppid->id, 0xFF, ppid->id_len);

    return 0;
}
#endif

static int sx_netdev_change_mtu(struct net_device *netdev, int new_mtu)
{
    if ((new_mtu < ETH_ZLEN) || (new_mtu > MAX_JUMBO_FRAME_SIZE)) {
        return -EINVAL;
    }

    netdev->mtu = new_mtu;

    return 0;
}

static int sx_hwstamp_set(struct net_device *dev, struct ifreq *ifr)
{
    struct sx_net_priv    *priv = netdev_priv(dev);
    struct hwtstamp_config config;
    int                    err = 0;

    if (copy_from_user(&config, ifr->ifr_data, sizeof(config))) {
        return -EFAULT;
    }

    /* TX HW timestamp */
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_ptp_set_tx_type,
                               err,
                               priv->dev,
                               config.tx_type);
    if (err) {
        return err;
    }

    /* RX HW timestamp */
    switch (config.rx_filter) {
    case HWTSTAMP_FILTER_NONE:
        break;

    case HWTSTAMP_FILTER_ALL:
    case HWTSTAMP_FILTER_SOME:
    case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
    case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
    case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
    case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
    case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
    case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
    case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
    case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
    case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
    case HWTSTAMP_FILTER_PTP_V2_EVENT:
    case HWTSTAMP_FILTER_PTP_V2_SYNC:
    case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
        config.rx_filter = HWTSTAMP_FILTER_ALL;
        break;

    default:
        return -ERANGE;
    }

    memcpy(&priv->hwtstamp_config, &config, sizeof(config));

    return copy_to_user(ifr->ifr_data, &config,
                        sizeof(config)) ? -EFAULT : 0;
}

static int sx_netdev_do_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd)
{
    switch (cmd) {
    case SIOCSHWTSTAMP:
        return sx_hwstamp_set(netdev, ifr);

    default:
        return -EOPNOTSUPP;
    }
}

static int sx_netdev_vlan_rx_add_vid(struct net_device *netdev, __be16 proto, u16 vid)
{
    struct sx_net_priv *net_priv = netdev_priv(netdev);

    set_bit(vid, net_priv->active_vlans);

    if (sx_netdev_rx_debug) {
        printk(KERN_INFO PFX "adding VLAN:%d on netdev %s\n", vid, netdev->name);
    }
    return 0;
}

static int sx_netdev_vlan_rx_kill_vid(struct net_device *netdev, __be16 proto, u16 vid)
{
    struct sx_net_priv *net_priv = netdev_priv(netdev);

    if (sx_netdev_rx_debug) {
        printk(KERN_INFO PFX "Killing VID:%d netdev %s\n", vid, netdev->name);
    }
    clear_bit(vid, net_priv->active_vlans);
    return 0;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) || defined(CONFIG_SX_RHEL_8_6)
static int sx_change_proto_down(struct net_device *dev, bool proto_down)
{
    if (change_proto_down_enable) {
        dev->proto_down = proto_down;
    }

    return 0;
}
#endif

static const struct net_device_ops sx_netdev_ops = {
    .ndo_open = sx_netdev_open,
    .ndo_stop = sx_netdev_stop,
    .ndo_start_xmit = sx_netdev_hard_start_xmit,
    .ndo_set_mac_address = sx_netdev_set_mac,
    .ndo_set_rx_mode = sx_netdev_set_multicast,
    .ndo_do_ioctl = sx_netdev_do_ioctl,
#if defined(CONFIG_SX_RHEL_7_6)
    .extended.ndo_change_mtu = sx_netdev_change_mtu,
#else
    .ndo_change_mtu = sx_netdev_change_mtu,
#endif
    .ndo_get_stats = sx_netdev_get_stats,
    .ndo_vlan_rx_add_vid = sx_netdev_vlan_rx_add_vid,
    .ndo_vlan_rx_kill_vid = sx_netdev_vlan_rx_kill_vid,
    .ndo_tx_timeout = NULL, /* Disable the transmit timeout function.  */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) || defined(CONFIG_SX_RHEL_8_6)
#if defined(CONFIG_NET_PORT)
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 10, 0)) || defined(CONFIG_SX_RHEL_8_6)
    .ndo_setup_tc = sx_psample_setup_tc,
#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(5, 10, 0)) */
    .ndo_get_stats64 = sx_get_stats64,
#endif /* if defined(CONFIG_NET_PORT) */
    .ndo_change_proto_down = sx_change_proto_down,
#endif
#if defined(CONFIG_NET_SWITCHDEV) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(5, 1, 0)) || defined(CONFIG_SX_RHEL_8_6))
    /* ndo_get_port_parent_id() replaced SWITCHDEV_ATTR_ID_PORT_PARENT_ID in kernel 5.1.0 */
    .ndo_get_port_parent_id = sx_netdev_get_port_parent_id,
#endif
};

static int sx_netdev_module_reset(struct net_device *dev)
{
    int                 ret;
    struct sx_net_priv *net_priv = netdev_priv(dev);

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_reset_port_module, ret, net_priv->dev, net_priv->port);
    if (ret) {
        goto out;
    }

out:
    return ret;
}

static int sx_netdev_module_power_mode_policy_set(struct net_device               *dev,
                                                  enum sx_module_power_mode_policy power_mode_policy)
{
    int                 ret;
    struct sx_net_priv *net_priv = netdev_priv(dev);

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_set_port_module_power_mode_policy,
                               ret,
                               net_priv->dev,
                               net_priv->port,
                               power_mode_policy);
    if (ret) {
        goto out;
    }

out:
    return ret;
}

static int sx_netdev_module_power_mode_get(struct net_device *dev, struct sx_module_power_mode_params *params)
{
    int                 ret;
    struct sx_net_priv *net_priv = netdev_priv(dev);

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_port_module_power_mode, ret, net_priv->dev, net_priv->port, params);
    if (ret) {
        goto out;
    }

out:
    return ret;
}

static int sx_get_ts_info(struct net_device *dev, struct ethtool_ts_info *info)
{
    uint8_t             ptp_clock_index = 0, ptp_enable = 0;
    int                 ret;
    struct sx_net_priv *net_priv = netdev_priv(dev);

    ret = ethtool_op_get_ts_info(dev, info);
    if (ret) {
        return ret;
    }
    if ((!net_priv->is_port_netdev && !net_priv->is_lag) || !net_priv->dev) {
        return 0;
    }
    CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_get_ptp_state, net_priv->dev, &ptp_enable);
    if (ptp_enable) {
        CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_get_ptp_clock_index, net_priv->dev, &ptp_clock_index);
        info->phc_index = ptp_clock_index;

        info->so_timestamping |= SOF_TIMESTAMPING_TX_HARDWARE |
                                 SOF_TIMESTAMPING_RX_HARDWARE |
                                 SOF_TIMESTAMPING_RAW_HARDWARE;

        CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_ptp_get_supported_tx_types, net_priv->dev, &info->tx_types);

        info->rx_filters = (BIT(1) << HWTSTAMP_FILTER_NONE) |
                           (BIT(1) << HWTSTAMP_FILTER_ALL);
    }

    return 0;
}

struct sx_ethtool_ppcnt_stats {
    char            str[ETH_GSTRING_LEN];
    sxd_ppcnt_grp_t grp;
    u64             (*getter)(const union ppcnt_counter_set* counter_set);
};

static u64 sx_reg_ppcnt_a_frame_check_sequence_errors_get(const union ppcnt_counter_set* counter_set)
{
    return BUILD_64BIT_COUNTER(counter_set->eth_802_3_cntrs_grp_data_layout.a_frame_check_sequence_errors_high,
                               counter_set->eth_802_3_cntrs_grp_data_layout.a_frame_check_sequence_errors_low);
}

static u64 sx_reg_ppcnt_a_symbol_error_during_carrier_get(const union ppcnt_counter_set* counter_set)
{
    return BUILD_64BIT_COUNTER(counter_set->eth_802_3_cntrs_grp_data_layout.a_symbol_error_during_carrier_high,
                               counter_set->eth_802_3_cntrs_grp_data_layout.a_symbol_error_during_carrier_low);
}

static u64 sx_reg_ppcnt_symbol_errors(const union ppcnt_counter_set* counter_set)
{
    return BUILD_64BIT_COUNTER(counter_set->phys_layer_cntrs.symbol_errors_high,
                               counter_set->phys_layer_cntrs.symbol_errors_low);
}

static struct sx_ethtool_ppcnt_stats ppcnt_grp_802_3_stats[] = {
    {
        .str = "a_symbol_error_during_carrier",
        .grp = SXD_PPCNT_GRP_IEEE_802_3_COUNTERS_E,
        .getter = sx_reg_ppcnt_a_symbol_error_during_carrier_get,
    },
    {
        .str = "a_frame_check_sequence_errors",
        .grp = SXD_PPCNT_GRP_IEEE_802_3_COUNTERS_E,
        .getter = sx_reg_ppcnt_a_frame_check_sequence_errors_get,
    },
};

static struct sx_ethtool_ppcnt_stats ppcnt_grp_phys_stats[] = {
    {
        .str = "symbol_errors",
        .grp = SXD_PPCNT_GRP_PHYSICAL_LAYER_COUNTERS_E,
        .getter = sx_reg_ppcnt_symbol_errors,
    },
};

#define PPCNT_GRP_802_3_STATS_LEN ARRAY_SIZE(ppcnt_grp_802_3_stats)
#define PPCNT_GRP_PHYS_STATS_LEN  ARRAY_SIZE(ppcnt_grp_phys_stats)
#define SX_ETHTOOL_STATS_LEN      (PPCNT_GRP_802_3_STATS_LEN + PPCNT_GRP_PHYS_STATS_LEN)

static void sx_get_strings(struct net_device *dev, u32 stringset, u8 *data)
{
    u8 *p = data;
    int i = 0;

    switch (stringset) {
    case ETH_SS_STATS:
        for (i = 0; i < PPCNT_GRP_802_3_STATS_LEN; i++) {
            memcpy(p, ppcnt_grp_802_3_stats[i].str, ETH_GSTRING_LEN);
            p += ETH_GSTRING_LEN;
        }
        for (i = 0; i < PPCNT_GRP_PHYS_STATS_LEN; i++) {
            memcpy(p, ppcnt_grp_phys_stats[i].str, ETH_GSTRING_LEN);
            p += ETH_GSTRING_LEN;
        }

        break;
    }
}

static int sx_get_sset_count(struct net_device *dev, int sset)
{
    switch (sset) {
    case ETH_SS_STATS:
        return SX_ETHTOOL_STATS_LEN;

    default:
        return -EOPNOTSUPP;
    }
}

static void sx_get_ethtool_stats(struct net_device *dev, struct ethtool_stats *stats, u64 *data)
{
    int                        err = 0, i = 0, index = 0;
    struct sx_net_priv        *net_priv = netdev_priv(dev);
    struct ku_access_ppcnt_reg reg_data;

    if (!net_priv->is_port_netdev || net_priv->is_lag) {
        return;
    }

    memset(&reg_data, 0, sizeof(reg_data));

    reg_data.dev_id = net_priv->dev->device_id;
    CALL_SX_CORE_FUNC_WITHOUT_RET(sx_cmd_set_op_tlv, &reg_data.op_tlv, MLXSW_PPCNT_ID, EMAD_METHOD_QUERY);

    reg_data.ppcnt_reg.clr = 0;
    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.ppcnt_reg.local_port,
                                        reg_data.ppcnt_reg.lp_msb,
                                        net_priv->port);
    reg_data.ppcnt_reg.swid = 0;
    reg_data.ppcnt_reg.pnat = SXD_PDDR_PNAT_LOCAL_PORT_NUMBER_E;

    reg_data.ppcnt_reg.grp = SXD_PPCNT_GRP_IEEE_802_3_COUNTERS_E;
    CALL_SX_CORE_FUNC_WITH_RET(sx_ACCESS_REG_PPCNT, err, net_priv->dev, &reg_data);
    if (err) {
        return;
    }
    for (i = 0; i < PPCNT_GRP_802_3_STATS_LEN; i++) {
        data[index++] = ppcnt_grp_802_3_stats[i].getter(&reg_data.ppcnt_reg.counter_set);
    }

    memset(&reg_data.ppcnt_reg.counter_set, 0, sizeof(reg_data.ppcnt_reg.counter_set));
    reg_data.ppcnt_reg.grp = SXD_PPCNT_GRP_PHYSICAL_LAYER_COUNTERS_E;
    CALL_SX_CORE_FUNC_WITH_RET(sx_ACCESS_REG_PPCNT, err, net_priv->dev, &reg_data);
    if (err) {
        return;
    }
    for (i = 0; i < PPCNT_GRP_PHYS_STATS_LEN; i++) {
        data[index++] = ppcnt_grp_phys_stats[i].getter(&reg_data.ppcnt_reg.counter_set);
    }
}

static void __set_link_ext_state(struct sx_ethtool_link_ext_state_opcode_mapping link_ext_state_mapping,
                                 struct sx_link_ext_state_info                  *link_ext_state_info)
{
    switch (link_ext_state_mapping.link_ext_state) {
    case SX_LINK_EXT_STATE_AUTONEG:
        link_ext_state_info->autoneg =
            link_ext_state_mapping.link_ext_substate;
        break;

    case SX_LINK_EXT_STATE_LINK_TRAINING_FAILURE:
        link_ext_state_info->link_training =
            link_ext_state_mapping.link_ext_substate;
        break;

    case SX_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH:
        link_ext_state_info->link_logical_mismatch =
            link_ext_state_mapping.link_ext_substate;
        break;

    case SX_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY:
        link_ext_state_info->bad_signal_integrity =
            link_ext_state_mapping.link_ext_substate;
        break;

    case SX_LINK_EXT_STATE_CABLE_ISSUE:
        link_ext_state_info->cable_issue =
            link_ext_state_mapping.link_ext_substate;
        break;

    default:
        break;
    }

    link_ext_state_info->link_ext_state = link_ext_state_mapping.link_ext_state;
}

static int __get_link_ext_state(struct net_device *dev, struct sx_link_ext_state_info *link_ext_state_info)
{
    struct sx_net_priv       *net_priv = netdev_priv(dev);
    struct ku_access_pddr_reg reg_data;
    int                       err = 0, i = 0;
    uint32_t                  status_opcode = 0;

    if (!net_priv->is_port_netdev || net_priv->is_lag) {
        return -ENODATA;
    }

    if (netif_carrier_ok(dev)) {
        return -ENODATA;
    }

    memset(&reg_data, 0, sizeof(reg_data));

    reg_data.dev_id = net_priv->dev->device_id;
    CALL_SX_CORE_FUNC_WITHOUT_RET(sx_cmd_set_op_tlv, &reg_data.op_tlv, PDDR_REG_ID, EMAD_METHOD_QUERY);

    reg_data.pddr_reg.page_select = SXD_PDDR_PAGE_SELECT_TROUBLESHOOTING_INFO_PAGE_E;
    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.pddr_reg.local_port,
                                        reg_data.pddr_reg.lp_msb,
                                        net_priv->port);
    reg_data.pddr_reg.pnat = SXD_PDDR_PNAT_LOCAL_PORT_NUMBER_E;

    CALL_SX_CORE_FUNC_WITH_RET(sx_ACCESS_REG_PDDR, err, net_priv->dev, &reg_data);
    if (err) {
        return err;
    }

    status_opcode =
        reg_data.pddr_reg.page_data.pddr_troubleshooting_page.status_opcode.pddr_monitor_opcode.monitor_opcode;

    if (!status_opcode) {
        return -ENODATA;
    }

    for (i = 0; i < ARRAY_SIZE(sx_link_ext_state_opcode_map); i++) {
        if (sx_link_ext_state_opcode_map[i].status_opcode == status_opcode) {
            __set_link_ext_state(sx_link_ext_state_opcode_map[i], link_ext_state_info);
            return 0;
        }
    }

    return -ENODATA;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 9, 0)) || defined(CONFIG_SX_RHEL_8_6)
static int sx_get_link_ext_state(struct net_device *dev, struct ethtool_link_ext_state_info *link_ext_state_info)
{
    int                           err = 0;
    struct sx_link_ext_state_info link_ext_state;

    memset(&link_ext_state, 0, sizeof(link_ext_state));

    err = __get_link_ext_state(dev, &link_ext_state);
    if (err) {
        return err;
    }

#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 16, 0))
    if (link_ext_state.link_ext_state == SX_LINK_EXT_STATE_MODULE) {
        return -ENODATA;
    }
#endif

    link_ext_state_info->link_ext_state = link_ext_state.link_ext_state;
    link_ext_state_info->__link_ext_substate = link_ext_state.__link_ext_substate;

    return 0;
}
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
static int sx_reset_module(struct net_device *dev, u32 *flags)
{
    u32 req = *flags;
    int err = 0;

    if (!(req & ETH_RESET_PHY) &&
        !(req & (ETH_RESET_PHY << ETH_RESET_SHARED_SHIFT))) {
        goto out;
    }

    err = sx_netdev_module_reset(dev);
    if (err) {
        printk(KERN_ERR PFX "Failed to reset module on %s\n", dev->name);
        goto out;
    }

    *flags &= ~(ETH_RESET_PHY | (ETH_RESET_PHY << ETH_RESET_SHARED_SHIFT));

out:
    return err;
}

static int sx_get_module_power_mode(struct net_device                       *dev,
                                    struct ethtool_module_power_mode_params *params,
                                    struct netlink_ext_ack                  *extack)
{
    int                                err = 0;
    struct sx_module_power_mode_params power_mode_params;

    memset(&power_mode_params, 0, sizeof(power_mode_params));

    err = sx_netdev_module_power_mode_get(dev, &power_mode_params);

    if (err) {
        NL_SET_ERR_MSG_MOD(extack, "Failed to retrieve module's power mode");
        goto out;
    }

    params->mode = power_mode_params->mode;
    params->policy = power_mode_params->policy;


out:
    return err;
}

static int sx_set_module_power_mode(struct net_device                             *dev,
                                    const struct ethtool_module_power_mode_params *params,
                                    struct netlink_ext_ack                        *extack)
{
    int err = 0;

    err = sx_netdev_module_power_mode_policy_set(params->policy);

    if (err) {
        NL_SET_ERR_MSG_MOD(extack, "Failed to set module's power mode policy");
        goto out;
    }

out:
    return err;
}
#endif /* if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0)) */

const struct ethtool_ops sx_ethtool_ops = {
    .get_link = ethtool_op_get_link,
    .get_sset_count = sx_get_sset_count,
    .get_strings = sx_get_strings,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 9, 0)) || defined(CONFIG_SX_RHEL_8_6)
    .get_link_ext_state = sx_get_link_ext_state,
#endif
    .get_ts_info = sx_get_ts_info,
    .get_ethtool_stats = sx_get_ethtool_stats,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
    .set_module_power_mode = sx_set_module_power_mode,
    .get_module_power_mode = sx_get_module_power_mode,
    .reset = sx_reset_module,
#endif
};

int sx_netdev_create_port_sysfs_nodes(struct net_device *netdev)
{
    int                 err = 0;
    struct sx_net_priv *net_priv = netdev_priv(netdev);

    if (SX_PORT_TYPE_ID_GET(net_priv->log_port) != SX_PORT_TYPE_NETWORK) {
        goto out;
    }

    net_priv->kobj[SX_NET_KOBJECT_PORT] = kobject_create_and_add(netdev->name, &(THIS_MODULE->mkobj.kobj));
    if (net_priv->kobj[SX_NET_KOBJECT_PORT] == NULL) {
        err = -ENOMEM;
        goto out;
    }
    net_priv->kobj[SX_NET_KOBJECT_MODULE] = kobject_create_and_add("module", net_priv->kobj[SX_NET_KOBJECT_PORT]);
    if (net_priv->kobj[SX_NET_KOBJECT_MODULE] == NULL) {
        err = -ENOMEM;
        goto clean_up_port_kobj;
    }
    err = sysfs_create_file(net_priv->kobj[SX_NET_KOBJECT_MODULE], &(module_id_attr.attr));
    if (err) {
        goto clean_up_module_kobj;
    }

    if (module_support_en) {
        err = sysfs_create_file(net_priv->kobj[SX_NET_KOBJECT_MODULE], &(module_reset_attr.attr));
        if (err) {
            goto clean_up_module_kobj;
        }
        err = sysfs_create_file(net_priv->kobj[SX_NET_KOBJECT_MODULE], &(module_power_mode_policy_attr.attr));
        if (err) {
            goto clean_up_module_kobj;
        }
        err = sysfs_create_file(net_priv->kobj[SX_NET_KOBJECT_MODULE], &(module_power_mode_attr.attr));
        if (err) {
            goto clean_up_module_kobj;
        }
        err = sysfs_create_file(net_priv->kobj[SX_NET_KOBJECT_PORT], &(link_ext_state_attr.attr));
        if (err) {
            goto clean_up_module_kobj;
        }
    }

    net_priv->kobj[SX_NET_KOBJECT_MODULE_TEMP] =
        kobject_create_and_add("temperature", net_priv->kobj[SX_NET_KOBJECT_MODULE]);
    if (net_priv->kobj[SX_NET_KOBJECT_MODULE_TEMP] == NULL) {
        err = -ENOMEM;
        goto clean_up_module_kobj;
    }
    err = sysfs_create_file(net_priv->kobj[SX_NET_KOBJECT_MODULE_TEMP], &(module_temp_input_attr.attr));
    if (err) {
        err = -ENOMEM;
        goto clean_up_module_temp_kobj;
    }
    err = sysfs_create_file(net_priv->kobj[SX_NET_KOBJECT_MODULE_TEMP], &(module_temp_label_attr.attr));
    if (err) {
        err = -ENOMEM;
        goto clean_up_module_temp_kobj;
    }

    /* for module eeprom sysfs */
    net_priv->eeprom_kobjs = kzalloc(sizeof(*(net_priv->eeprom_kobjs)), GFP_KERNEL);
    if (!(net_priv->eeprom_kobjs)) {
        printk(KERN_ERR "port sysfs nodes handler failed to allocated memory.\n");
        err = -ENOMEM;
        goto clean_up_module_temp_kobj;
    }
    err = sx_netdev_create_module_sysfs_eeprom_tree(net_priv->kobj[SX_NET_KOBJECT_MODULE], net_priv->eeprom_kobjs);
    if (err) {
        printk(KERN_ERR "port sysfs nodes handler failed to create eeprom sysfs sub-tree.\n");
        kfree(net_priv->eeprom_kobjs);
        net_priv->eeprom_kobjs = NULL;
        err = -ENOMEM;
        goto clean_up_module_temp_kobj;
    }

    err = sx_netdev_synce_sysfs_init(net_priv->kobj[SX_NET_KOBJECT_PORT]);
    if (err) {
        goto clean_up_module_temp_kobj;
    }

    err =
        sx_netdev_create_module_sysfs_extension_for_s3ip(net_priv->kobj[SX_NET_KOBJECT_MODULE],
                                                         (module_support_en != 0));
    if (err) {
        printk(KERN_ERR "port sysfs nodes handler failed to create sysfs extension for S3IP.\n");
        goto clean_up_module_temp_kobj;
    }

    return 0;

clean_up_module_temp_kobj:
    kobject_put(net_priv->kobj[SX_NET_KOBJECT_MODULE_TEMP]);
    net_priv->kobj[SX_NET_KOBJECT_MODULE_TEMP] = NULL;

clean_up_module_kobj:
    kobject_put(net_priv->kobj[SX_NET_KOBJECT_MODULE]);
    net_priv->kobj[SX_NET_KOBJECT_MODULE] = NULL;

clean_up_port_kobj:
    kobject_put(net_priv->kobj[SX_NET_KOBJECT_PORT]);
    net_priv->kobj[SX_NET_KOBJECT_PORT] = NULL;

out:
    return err;
}

int sx_netdev_remove_port_sysfs_nodes(struct net_device *netdev)
{
    int                 err = 0;
    struct sx_net_priv *net_priv = netdev_priv(netdev);

    if (SX_PORT_TYPE_ID_GET(net_priv->log_port) != SX_PORT_TYPE_NETWORK) {
        goto out;
    }

    sx_netdev_synce_sysfs_deinit(net_priv->kobj[SX_NET_KOBJECT_PORT]);
    /* module sysfs eeprom should be cleared firstly. */
    sx_netdev_delete_module_sysfs_eeprom_tree(net_priv->eeprom_kobjs);
    kfree(net_priv->eeprom_kobjs);
    sx_netdev_delete_module_sysfs_extension_for_s3ip(net_priv->kobj[SX_NET_KOBJECT_MODULE], (module_support_en != 0));

    kobject_put(net_priv->kobj[SX_NET_KOBJECT_MODULE_TEMP]);
    kobject_put(net_priv->kobj[SX_NET_KOBJECT_MODULE]);
    kobject_put(net_priv->kobj[SX_NET_KOBJECT_PORT]);

out:
    return err;
}

int sx_netdev_devlink_port_register(struct net_device *netdev)
{
#if !defined(SX_DROP_MONITOR_DISABLED) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, \
                                                                                 0)) || defined(CONFIG_SX_RHEL_8_6))
    struct sx_net_priv       *net_priv = netdev_priv(netdev);
    struct devlink_port_attrs attrs = {};
    struct devlink_port      *devlink_port;
    int                       err = 0;

    if (!devlink_port_en) {
        return 0;
    }

    devlink_port = &net_priv->devlink_port;
    memset(devlink_port, 0, sizeof(*devlink_port));

    attrs.split = false;
#define SX_NETDEV_DEVLINK_ATTR_LANES_MAX 16
    attrs.lanes = SX_NETDEV_DEVLINK_ATTR_LANES_MAX;
    attrs.splittable = true;
    devlink_port_attrs_set(devlink_port, &attrs);

    err = devlink_port_register(g_devlink_dummy_instance, devlink_port, net_priv->log_port);
    if (err) {
        printk(KERN_ERR PFX "Error (%d) when registering devlink for netdev %s\n", err, netdev->name);
        return EFAULT;
    }
    devlink_port_type_eth_set(devlink_port, netdev);
#endif
    return 0;
}

void sx_netdev_devlink_port_unregister(struct net_device *netdev)
{
#if !defined(SX_DROP_MONITOR_DISABLED) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, \
                                                                                 0)) || defined(CONFIG_SX_RHEL_8_6))
    struct sx_net_priv *net_priv = netdev_priv(netdev);

    if (devlink_port_en) {
        devlink_port_unregister(&net_priv->devlink_port);
    }
#endif
}
#if !defined(SX_DROP_MONITOR_DISABLED) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, \
                                                                                 0)) || defined(CONFIG_SX_RHEL_8_6))
static int sx_netdev_port_split(struct devlink         *devlink,
                                unsigned int            port_index,
                                unsigned int            count,
                                struct netlink_ext_ack *extack)
{
    #if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    return port_devlink_port_split(devlink, port_index, count, extack);
    #else
    return -ENOTSUPP;
    #endif
}

static int sx_netdev_port_unsplit(struct devlink *devlink, unsigned int port_index, struct netlink_ext_ack *extack)
{
    #if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    return port_devlink_port_unsplit(devlink, port_index, extack);
    #else
    return -ENOTSUPP;
    #endif
}
#endif

int sx_netdev_register_device(struct net_device *netdev, int should_rtnl_lock, int admin_state)
{
    int                 err = 0;
    struct sx_net_priv *net_priv = netdev_priv(netdev);
    struct inet6_dev   *idev = NULL;

    pr_debug("%s: called for device %s\n", __func__, netdev->name);

#if defined(CONFIG_NET_SWITCHDEV) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9,  \
                                                                           0)) && \
    (LINUX_VERSION_CODE < KERNEL_VERSION(5, 1, 0)) && !defined(CONFIG_SX_RHEL_8_6) && !defined(CONFIG_SX_CENTOS_8_4)
    /* switchdev_ops was removed in kernel 5.1 */
    netdev->switchdev_ops = &sx_netdev_switchdev_ops;
#endif

    /* set netdev defaults and function callbacks */
    netdev->base_addr = 0;
    netdev->irq = 0;
    netdev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;

#if defined(CONFIG_NET_PORT) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)))
    if (sx_netdev_tc_psample_enable) {
        netdev->features |= NETIF_F_HW_TC;
    }
#endif /* if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) */

    sx_netdev_u64_to_mac(netdev->dev_addr, net_priv->mac);
    netdev->mtu = DEFAULT_FRAME_SIZE;

    netdev->netdev_ops = &sx_netdev_ops;
#if defined(CONFIG_NET_PORT) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)))
    netdev->ethtool_ops = &sx_cl_ethtool_ops;
#else
    netdev->ethtool_ops = &sx_ethtool_ops;
#endif

    sx_netdev_devlink_port_register(netdev);

    if (should_rtnl_lock) {
        rtnl_lock();
    }
    err = register_netdevice(netdev);

    idev = __in6_dev_get(netdev);
    if (idev) {
        idev->cnf.disable_ipv6 = 1;
    }

    if (admin_state && net_priv->mac) {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0)) || defined(CONFIG_SX_RHEL_8_6) || defined(CONFIG_SX_CENTOS_8_4)
        dev_change_flags(netdev, netdev->flags | IFF_UP, NULL);
#else
        dev_change_flags(netdev, netdev->flags | IFF_UP);
#endif
    } else {
        netif_tx_disable(netdev);
        netif_carrier_off(netdev);
    }
    if (should_rtnl_lock) {
        rtnl_unlock();
    }

    if (err) {
        printk(KERN_ERR PFX "Net Device registration "
               "has failed. err=%d\n", err);
        return err;
    }

    pr_debug("%s: exit\n", __func__);
    return 0;
}

static void sx_netdev_unregister_device(struct net_device *netdev)
{
    netif_tx_disable(netdev);
    netif_carrier_off(netdev);

    CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_flush_synd_by_context, netdev);

    unregister_netdev(netdev); /* It will call our stop function */
    free_netdev(netdev);
}

static void  * __sx_netdev_init_one_netdev(struct sx_dev *dev, int swid, int synd, u64 mac)
{
    struct sx_net_priv *net_priv;
    struct net_device  *netdev;
    int                 err;
    char                name[10];
    int                 i;
    u8                  uc = 0;

    printk(KERN_INFO PFX "Initializing\n");

    if ((swid < 0) || (swid >= NUMBER_OF_SWIDS)) { /* only swids 0-7 are allowed */
        return NULL;
    }

    sprintf(name, "swid%d_eth", swid);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0))
    netdev = alloc_netdev(sizeof(*net_priv), name, NET_NAME_UNKNOWN, ether_setup);
#else
    netdev = alloc_netdev(sizeof(*net_priv), name, ether_setup);
#endif

    if (!netdev) {
        printk(KERN_ERR PFX  "Net Device struct %s alloc failed, "
               "aborting.\n", name);
        return NULL;
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0))
    netdev->max_mtu = 0; /* do not limit the max MTU */
#endif
    netdev->hard_header_len = ETH_HLEN + ISX_HDR_SIZE;
    memset(netdev_priv(netdev), 0, sizeof(*net_priv));
    net_priv = netdev_priv(netdev);
    net_priv->swid = swid;
    net_priv->dev = dev;
    net_priv->mac = mac;
    net_priv->is_oper_state_up = 1;
    net_priv->skip_tunnel = g_skip_tunnel;
    net_priv->netdev = netdev;

    for (uc = USER_CHANNEL_L3_NETDEV; uc < NUM_OF_NET_DEV_TYPE; uc++) {
        for (i = 0; i < MAX_NUM_TRAPS_TO_REGISTER; i++) {
            net_priv->trap_ids[uc][i].synd = SX_INVALID_TRAP_ID;
        }
        net_priv->num_of_traps[uc] = 0;
    }

    err = sx_netdev_register_device(netdev, 1, 1);
    if (err) {
        goto out;
    }

    return netdev;

out:
    free_netdev(netdev);
    return NULL;
}

static int sx_netdev_init_one_netdev(struct sx_dev *dev, struct sx_netdev_rsc *resources, int swid, int synd, u64 mac)
{
    struct net_device *netdev = NULL;
    int                err = 0;

    mutex_lock(&resources->rsc_lock);

    if (g_netdev_resources->in_attach_detach == 1) {
        mutex_unlock(&resources->rsc_lock);
        printk(KERN_ERR PFX  "Can't init swid %d netdev during attach/detach \n", swid);
        return -EFAULT;
    }

    if (resources->allocated[swid]) {
        mutex_unlock(&resources->rsc_lock);
        printk(KERN_DEBUG PFX  "Net Device for swid %d was already"
               " allocated\n", swid);
        netdev = resources->sx_netdevs[swid];
        netif_carrier_on(netdev);
        netif_start_queue(netdev);
        return 0;
    }

    resources->allocated[swid] = 1;
    mutex_unlock(&resources->rsc_lock);

    netdev = __sx_netdev_init_one_netdev(dev, swid, synd, mac);

    mutex_lock(&resources->rsc_lock);
    if (netdev) {
        resources->sx_netdevs[swid] = netdev;
    } else {
        resources->allocated[swid] = 0;
        err = -EFAULT;
    }

    mutex_unlock(&resources->rsc_lock);

    return err;
}

static void sx_netdev_remove_one_netdev(struct sx_dev *dev, void *rsc, int swid)
{
    struct net_device    *netdev;
    struct sx_netdev_rsc *resources = rsc;

    mutex_lock(&resources->rsc_lock);

    if (g_netdev_resources->in_attach_detach == 1) {
        mutex_unlock(&resources->rsc_lock);
        printk(KERN_ERR PFX  "Can't remove swid %u netdev during attach/detach \n", swid);
        return;
    }

    netdev = resources->sx_netdevs[swid];
    if (!resources->allocated[swid]) {
        mutex_unlock(&resources->rsc_lock);
        return;
    }

    resources->sx_netdevs[swid] = NULL;
    resources->allocated[swid] = 0;
    mutex_unlock(&resources->rsc_lock);

    sx_netdev_unregister_device(netdev);
}

static void * sx_netdev_init_one(struct sx_dev *dev)
{
    static int            sx_netdev_version_printed = 0;
    struct sx_netdev_rsc *resources;
    int                   i;

    if (g_sx_dev) {
        printk(KERN_WARNING "netdev does not support more than one PCI device!\n");
        return NULL;
    }

    printk(KERN_DEBUG PFX "sx_netdev_init_one\n");
    if (!sx_netdev_version_printed) {
        printk(KERN_INFO "%s", sx_netdev_version);
        ++sx_netdev_version_printed;
    }

    resources = vmalloc(sizeof(*resources));
    if (!resources) {
        return NULL;
    }
    memset(resources, 0, sizeof(*resources));

    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        resources->sx_netdevs[i] = NULL;
        resources->allocated[i] = 0;
    }

    mutex_init(&resources->rsc_lock);

    g_netdev_resources = resources;
    g_sx_dev = dev;

    /* bind sx_core to netdev */
    __bind_unbind_sx_core(true, dev);

    return resources;
}

static void sx_netdev_remove_one(struct sx_dev *dev, void *rsc)
{
    int                   i;
    struct sx_netdev_rsc *resources = rsc;

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX "sx_netdev_remove_one\n");
#endif

    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        sx_netdev_remove_one_netdev(dev, resources, i);
    }

    /* unbind sx_core from netdev */
    __bind_unbind_sx_core(false, NULL);

    /* before freeing resource, we must make sure that no RCU reader is using it */
    synchronize_rcu();

    vfree(resources);
}


static int __sx_netdev_dev_synd_add(struct net_device               *netdev,
                                    enum sx_netdev_user_channel_type uc_type,
                                    void                            *rsc,
                                    u16                              synd,
                                    struct ku_port_vlan_params      *port_vlan,
                                    u8                               is_register)
{
    struct sx_net_priv       *net_priv = netdev_priv(netdev);
    int                       err = 0, i = 0;
    union ku_filter_critireas crit;
    cq_handler                netdev_callback = 0;
    int                       synd_added = 0;

    if (net_priv->num_of_traps[uc_type] == MAX_NUM_TRAPS_TO_REGISTER) {
        printk(KERN_ERR PFX "%s: swid %s Too many traps\n",
               __func__, netdev->name);
        err = -ERANGE;
        goto out;
    }

    /* validate that the trap at new index is INVALID */
    BUG_ON(net_priv->trap_ids[uc_type][net_priv->num_of_traps[uc_type]].synd != SX_INVALID_TRAP_ID);

    for (i = 0; i < net_priv->num_of_traps[uc_type]; i++) {
        if (net_priv->trap_ids[uc_type][i].synd == synd) {
            printk(KERN_INFO PFX "The synd 0x%x is already added.\n", synd);
            synd_added = 1;
        }
    }

    if (!synd_added) {
        /* add trap to traps_db */
        net_priv->trap_ids[uc_type][net_priv->num_of_traps[uc_type]].synd = synd;
        net_priv->trap_ids[uc_type][net_priv->num_of_traps[uc_type]].info_type = port_vlan->port_vlan_type;
        net_priv->trap_ids[uc_type][net_priv->num_of_traps[uc_type]].sysport = port_vlan->sysport;
        net_priv->trap_ids[uc_type][net_priv->num_of_traps[uc_type]].lag_id = port_vlan->lag_id;
        net_priv->trap_ids[uc_type][net_priv->num_of_traps[uc_type]].vlan = port_vlan->vlan;
        net_priv->num_of_traps[uc_type]++;
    }

    /* if netdev is active (opened) than config the synd, else the synd will be added after dev open */
    if (netdev->flags & IFF_UP) {
        err = __sx_netdev_uc_type_get_data(uc_type, &crit, &netdev_callback);
        if (err) {
            printk(KERN_ERR PFX "%s: Failed get crit and handler for "
                   "user channel (%d).\n", __func__, uc_type);
            goto out;
        }

        /* register the listener according to the swid */
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd, err, net_priv->swid, synd, L2_TYPE_ETH, 0, "sx_netdev", 0,
                                   &crit, netdev_callback, netdev,
                                   CHECK_DUP_ENABLED_E, net_priv->dev, port_vlan, is_register);

        if (err) {
            printk(KERN_ERR PFX "error %s, Failed registering on "
                   "0x%x syndrome.\n", netdev->name, synd);
            goto out;
        }
    }

out:
    return err;
}

static int __sx_netdev_dev_synd_remove(struct net_device               *netdev,
                                       enum sx_netdev_user_channel_type uc_type,
                                       void                            *rsc,
                                       u16                              synd,
                                       struct ku_port_vlan_params      *port_vlan,
                                       u8                               is_register)
{
    struct sx_net_priv       *net_priv = netdev_priv(netdev);
    int                       err = 0;
    u8                        trap_was_removed = 0;
    int                       i;
    union ku_filter_critireas crit;
    cq_handler                netdev_callback = 0;


    /* remove synd from sx_core driver */
    if (netdev->flags & IFF_UP) {
        err = __sx_netdev_uc_type_get_data(uc_type, &crit, &netdev_callback);
        if (err) {
            printk(KERN_ERR PFX "%s: Failed get crit and handler for "
                   "user channel (%d).\n", __func__, uc_type);
            goto out;
        }

        CALL_SX_CORE_FUNC_WITH_RET(sx_core_remove_synd, err, net_priv->swid, synd, L2_TYPE_ETH, 0,
                                   &crit, netdev, net_priv->dev, netdev_callback, port_vlan, is_register,
                                   &trap_was_removed);

        if (err) {
            printk(KERN_ERR PFX "error %s, Failed de registering on "
                   "0x%x syndrome.\n", netdev->name, synd);
            goto out;
        }
    }

    if (trap_was_removed == 0) {
        goto out;
    }

    for (i = 0; i < net_priv->num_of_traps[uc_type]; i++) {
        if (net_priv->trap_ids[uc_type][i].synd == synd) {
            printk(KERN_INFO PFX "The synd 0x%x was found and will be removed.\n", synd);
            memcpy(&(net_priv->trap_ids[uc_type][i]),
                   &(net_priv->trap_ids[uc_type][net_priv->num_of_traps[uc_type] - 1]),
                   sizeof(struct net_port_vlan_info));
            net_priv->trap_ids[uc_type][net_priv->num_of_traps[uc_type] - 1].synd = SX_INVALID_TRAP_ID;
            net_priv->num_of_traps[uc_type]--;
            break;
        }
    }

out:
    return err;
}

static void sx_netdev_set_synd_l3(struct sx_dev       *dev,
                                  void                *rsc,
                                  u16                  synd,
                                  enum sx_dev_event    event,
                                  union sx_event_data *event_data)
{
    struct sx_netdev_rsc      *resources = rsc;
    int                        i;
    int                        err;
    union ku_filter_critireas  crit;
    struct ku_port_vlan_params port_vlan;

    mutex_lock(&resources->rsc_lock);
    if (g_netdev_resources->in_attach_detach == 1) {
        mutex_unlock(&resources->rsc_lock);
        printk(KERN_ERR PFX  "Can't set l3 synd %d during attach/detach \n", synd);
        return;
    }

    memset(&port_vlan, 0, sizeof(port_vlan));
    switch (event_data->eth_l3_synd.type) {
    case L3_SYND_TYPE_GLOBAL:
        port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_GLOBAL;
        break;

    case L3_SYND_TYPE_PORT:
        port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_GLOBAL;
        port_vlan.sysport = event_data->eth_l3_synd.port;
        break;

    case L3_SYND_TYPE_LAG:
        port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_GLOBAL;
        port_vlan.lag_id = event_data->eth_l3_synd.port;
        break;

    case L3_SYND_TYPE_VLAN:
        port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_GLOBAL;
        port_vlan.vlan = event_data->eth_l3_synd.vlan;
        break;
    }

    /* go over all per swid devices */
    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        if (resources->sx_netdevs[i] != NULL) {
            if (event == SX_DEV_EVENT_ADD_SYND_NETDEV) {
                __sx_netdev_dev_synd_add(resources->sx_netdevs[i],
                                         USER_CHANNEL_L3_NETDEV,
                                         rsc,
                                         synd,
                                         &port_vlan,
                                         event_data->eth_l3_synd.is_register);
            } else {
                __sx_netdev_dev_synd_remove(resources->sx_netdevs[i],
                                            USER_CHANNEL_L3_NETDEV,
                                            rsc,
                                            synd,
                                            &port_vlan,
                                            event_data->eth_l3_synd.is_register);
            }
        }
    }

    /* register the listener according to the swid */
    memset(&crit, 0, sizeof(crit)); /* sets all ETH values to default */
    crit.eth.from_rp = IS_RP_FROM_RP_E;
    if (event == SX_DEV_EVENT_ADD_SYND_NETDEV) {
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd, err, 0, synd, L2_TYPE_ETH, 0, "sx_netdev", 0,
                                   &crit, sx_netdev_handle_global_pkt, NULL,
                                   CHECK_DUP_DISABLED_E, g_sx_dev, &port_vlan, event_data->eth_l3_synd.is_register);
        if (err) {
            printk(KERN_ERR PFX "Failed registering RP rx_handle on "
                   "syndrome %d.\n", synd);
        }
    } else {
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_remove_synd,
                                   err,
                                   0,
                                   synd,
                                   L2_TYPE_ETH,
                                   0,
                                   &crit,
                                   NULL,
                                   g_sx_dev,
                                   sx_netdev_handle_global_pkt,
                                   &port_vlan,
                                   event_data->eth_l3_synd.is_register, NULL);
        if (err) {
            printk(KERN_ERR PFX "Failed unregistering RP rx_handle on "
                   "syndrome %d.\n", synd);
        }
    }

    /* register the listener according to the swid */
    memset(&crit, 0, sizeof(crit)); /* sets all ETH values to default */
    crit.eth.from_bridge = IS_BRIDGE_FROM_BRIDGE_E;
    if (event == SX_DEV_EVENT_ADD_SYND_NETDEV) {
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd, err, 0, synd, L2_TYPE_ETH, 0, "sx_netdev", 0,
                                   &crit, sx_netdev_handle_global_pkt, NULL,
                                   CHECK_DUP_DISABLED_E, g_sx_dev, &port_vlan, event_data->eth_l3_synd.is_register);
        if (err) {
            printk(KERN_ERR PFX "Failed registering bridge rx_handle on "
                   "syndrome %d.\n", synd);
        }
    } else {
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_remove_synd,
                                   err,
                                   0,
                                   synd,
                                   L2_TYPE_ETH,
                                   0,
                                   &crit,
                                   NULL,
                                   g_sx_dev,
                                   sx_netdev_handle_global_pkt,
                                   &port_vlan,
                                   event_data->eth_l3_synd.is_register, NULL);
        if (err) {
            printk(KERN_ERR PFX "Failed unregistering bridge rx_handle on "
                   "syndrome %d.\n", synd);
        }
    }

    mutex_unlock(&resources->rsc_lock);
}

static void sx_netdev_set_synd_l2(struct sx_dev       *dev,
                                  void                *rsc,
                                  u16                  synd,
                                  enum sx_dev_event    event,
                                  union sx_event_data *event_data)
{
    struct sx_netdev_rsc      *resources = rsc;
    int                        i;
    struct ku_port_vlan_params port_vlan;

    mutex_lock(&resources->rsc_lock);
    if (g_netdev_resources->in_attach_detach == 1) {
        mutex_unlock(&resources->rsc_lock);
        printk(KERN_ERR PFX  "Can't set l2 synd %d during attach/detach \n", synd);
        return;
    }

    memset(&port_vlan, 0, sizeof(port_vlan));
    switch (event_data->eth_l3_synd.type) {
    case L3_SYND_TYPE_GLOBAL:
        port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_GLOBAL;
        break;

    case L3_SYND_TYPE_PORT:
        port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_PORT;
        port_vlan.sysport = event_data->eth_l3_synd.port;
        break;

    case L3_SYND_TYPE_LAG:
        port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_LAG;
        port_vlan.lag_id = event_data->eth_l3_synd.port;
        break;

    case L3_SYND_TYPE_VLAN:
        port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_VLAN;
        port_vlan.vlan = event_data->eth_l3_synd.vlan;
        break;
    }
    /* go over all per swid devices */
    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        if (resources->sx_netdevs[i] != NULL) {
            if (event == SX_DEV_EVENT_ADD_SYND_NETDEV) {
                __sx_netdev_dev_synd_add(resources->sx_netdevs[i], USER_CHANNEL_LOG_PORT_NETDEV, rsc, synd,
                                         &port_vlan,
                                         event_data->eth_l3_synd.is_register);
            } else {
                __sx_netdev_dev_synd_remove(resources->sx_netdevs[i],
                                            USER_CHANNEL_LOG_PORT_NETDEV,
                                            rsc,
                                            synd,
                                            &port_vlan,
                                            event_data->eth_l3_synd.is_register);
            }
        }
    }
    mutex_unlock(&resources->rsc_lock);
}

static void sx_netdev_set_synd_phy(struct sx_dev       *dev,
                                   void                *rsc,
                                   u16                  synd,
                                   enum sx_dev_event    event,
                                   union sx_event_data *event_data)
{
    struct sx_netdev_rsc      *resources = rsc;
    int                        i;
    struct ku_port_vlan_params port_vlan;

    mutex_lock(&resources->rsc_lock);
    if (g_netdev_resources->in_attach_detach == 1) {
        mutex_unlock(&resources->rsc_lock);
        printk(KERN_ERR PFX  "Can't set phy synd %d during attach/detach \n", synd);
        return;
    }

    memset(&port_vlan, 0, sizeof(port_vlan));
    switch (event_data->eth_l3_synd.type) {
    case L3_SYND_TYPE_GLOBAL:
        port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_GLOBAL;
        break;

    case L3_SYND_TYPE_PORT:
        port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_PORT;
        port_vlan.sysport = event_data->eth_l3_synd.port;
        break;

    case L3_SYND_TYPE_LAG:
        port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_LAG;
        port_vlan.lag_id = event_data->eth_l3_synd.port;
        break;

    case L3_SYND_TYPE_VLAN:
        port_vlan.port_vlan_type = KU_PORT_VLAN_PARAMS_TYPE_VLAN;
        port_vlan.vlan = event_data->eth_l3_synd.vlan;
        break;
    }

    /* go over all per swid devices */
    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        if (resources->sx_netdevs[i] != NULL) {
            if (event == SX_DEV_EVENT_ADD_SYND_NETDEV) {
                __sx_netdev_dev_synd_add(resources->sx_netdevs[i], USER_CHANNEL_PHY_PORT_NETDEV, rsc, synd,
                                         &port_vlan, event_data->eth_l3_synd.is_register);
            } else {
                __sx_netdev_dev_synd_remove(resources->sx_netdevs[i],
                                            USER_CHANNEL_PHY_PORT_NETDEV,
                                            rsc,
                                            synd,
                                            &port_vlan, event_data->eth_l3_synd.is_register);
            }
        }
    }
    mutex_unlock(&resources->rsc_lock);
}

void __sx_netdev_dump_per_dev(struct net_device *netdev)
{
    struct sx_net_priv *net_priv = netdev_priv(netdev);
    int                 i;
    u8                  uc_type = 0;
    char              * uc_str[NUM_OF_NET_DEV_TYPE] = {"USER_CHANNEL_L3_NETDEV",
                                                       "USER_CHANNEL_LOG_PORT_NETDEV",
                                                       "USER_CHANNEL_PHY_PORT_NETDEV"};

    printk("======   Netdev %s , netdev_p:%p , if_index: %d dump:   =====\n",
           netdev->name, netdev, netdev->ifindex);

    for (uc_type = USER_CHANNEL_L3_NETDEV; uc_type < NUM_OF_NET_DEV_TYPE; uc_type++) {
        printk("num of %s traps: %d\n", uc_str[uc_type], net_priv->num_of_traps[uc_type]);
        for (i = 0; i < MAX_NUM_TRAPS_TO_REGISTER; i++) {
            if (net_priv->trap_ids[uc_type][i].synd != SX_INVALID_TRAP_ID) {
                printk("trap[%d]: 0x%x\n", i, net_priv->trap_ids[uc_type][i].synd);
                printk("Filter_type %s (%d) - Port:%d, lag:%d, vlan:%d\n",
                       NET_PORT_VLAN_TYPE_TO_STR(net_priv->trap_ids[uc_type][i].info_type),
                       net_priv->trap_ids[uc_type][i].info_type,
                       net_priv->trap_ids[uc_type][i].sysport,
                       net_priv->trap_ids[uc_type][i].lag_id,
                       net_priv->trap_ids[uc_type][i].vlan);
            }
        }
    }
}

static void sx_netdev_debug_dump(struct sx_dev *dev, void *rsc)
{
    struct sx_netdev_rsc *resources = rsc;
    int                   i = 0, port = 0, port_type = 0;
    int                   max_ports[] = {
        [PORT_TYPE_SINGLE] = MAX_SYSPORT_NUM,
        [PORT_TYPE_LAG] = MAX_LAG_NUM
    };

    mutex_lock(&resources->rsc_lock);

    /* go over all per swid devices */
    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        if (resources->sx_netdevs[i] != NULL) {
            __sx_netdev_dump_per_dev(resources->sx_netdevs[i]);
        }
    }

    /* go over all per port devices */
    for (port_type = 0; port_type < PORT_TYPE_NUM; port_type++) {
        for (port = 0; port < max_ports[port_type]; port++) {
            for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
                if (resources->port_netdev[port_type][port][i] != NULL) {
                    __sx_netdev_dump_per_dev(resources->port_netdev[port_type][port][i]);
                }
            }
        }
    }

    mutex_unlock(&resources->rsc_lock);

    /* go over all bridge devices */
    for (i = 0; i < MAX_BRIDGE_NUM; i++) {
        if (bridge_netdev_db[i] != NULL) {
            __sx_netdev_dump_per_dev(bridge_netdev_db[i]);
        }
    }
}

static void sx_netdev_get_trap_info(struct sx_dev *dev, void *rsc, union sx_event_data *event_data)
{
    struct sx_netdev_rsc *resources = rsc;
    int                   i, j;
    struct sx_net_priv   *net_priv;
    uint8_t               uc_type = 0;

    mutex_lock(&resources->rsc_lock);

    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        if (resources->sx_netdevs[i] != NULL) {
            net_priv = netdev_priv(resources->sx_netdevs[i]);
            for (uc_type = USER_CHANNEL_L3_NETDEV; uc_type < NUM_OF_NET_DEV_TYPE; uc_type++) {
                event_data->netdev_trap_info.num_of_traps[uc_type] = net_priv->num_of_traps[uc_type];
                for (j = 0; j < net_priv->num_of_traps[uc_type]; j++) {
                    event_data->netdev_trap_info.trap_ids[uc_type][j] =
                        net_priv->trap_ids[uc_type][j].synd;
                    event_data->netdev_trap_info.port_vlan_params[uc_type][j].port_vlan_type =
                        net_priv->trap_ids[uc_type][j].info_type;
                    event_data->netdev_trap_info.port_vlan_params[uc_type][j].sysport =
                        net_priv->trap_ids[uc_type][j].sysport;
                    event_data->netdev_trap_info.port_vlan_params[uc_type][j].lag_id =
                        net_priv->trap_ids[uc_type][j].lag_id;
                    event_data->netdev_trap_info.port_vlan_params[uc_type][j].vlan =
                        net_priv->trap_ids[uc_type][j].vlan;
                }
            }
            /*Since the traps are registered for each swid netdev, we only need to get trap info from one swid netdev.*/
            break;
        }
    }

    mutex_unlock(&resources->rsc_lock);
}

static int sx_netdev_event(struct sx_dev       *dev,
                           void                *resources,
                           enum sx_dev_event    event,
                           union sx_event_data *event_data)
{
    int err = 0;

    switch (event) {
    case SX_DEV_EVENT_ETH_SWID_UP:
        pr_debug(PFX "sx_netdev_event: Got ETH swid up event. "
                 "dev = %p, dev_id = %u, swid = %d, "
                 "synd = 0x%x, mac = 0x%llx\n",
                 dev, dev->device_id, event_data->eth_swid_up.swid,
                 event_data->eth_swid_up.synd, event_data->eth_swid_up.mac);
        sx_netdev_init_one_netdev(dev, resources, event_data->eth_swid_up.swid,
                                  event_data->eth_swid_up.synd, event_data->eth_swid_up.mac);
        break;

    case SX_DEV_EVENT_ETH_SWID_DOWN:
        pr_debug(PFX "sx_netdev_event: Got ETH swid down event. "
                 "dev = %p, dev_id = %u, swid = %d\n",
                 dev, dev->device_id, event_data->eth_swid_down.swid);
        sx_netdev_remove_one_netdev(dev, resources, event_data->eth_swid_down.swid);
        break;

    case SX_DEV_EVENT_ADD_SYND_NETDEV:
        pr_debug(PFX "sx_netdev_event: Got ADD_SYND_L3 event. "
                 "dev = %p, dev_id = %u, trap_id = 0x%x\n",
                 dev, dev->device_id, event_data->eth_l3_synd.hw_synd);
        sx_netdev_set_synd_l3(dev, resources, event_data->eth_l3_synd.hw_synd,
                              SX_DEV_EVENT_ADD_SYND_NETDEV, event_data);
        break;

    case SX_DEV_EVENT_REMOVE_SYND_NETDEV:
        pr_debug(PFX "sx_netdev_event: Got REMOVE_SYND_L3 event. "
                 "dev = %p, dev_id = %u, trap_id = 0x%x\n",
                 dev, dev->device_id, event_data->eth_l3_synd.hw_synd);
        sx_netdev_set_synd_l3(dev, resources, event_data->eth_l3_synd.hw_synd,
                              SX_DEV_EVENT_REMOVE_SYND_NETDEV, event_data);
        break;

    case SX_DEV_EVENT_ADD_SYND_L2_NETDEV:
        pr_debug(PFX "sx_netdev_event: Got ADD_SYND_L2 event. "
                 "dev = %p, dev_id = %u, trap_id = 0x%x\n",
                 dev, dev->device_id, event_data->eth_l3_synd.hw_synd);
        sx_netdev_set_synd_l2(dev, resources, event_data->eth_l3_synd.hw_synd,
                              SX_DEV_EVENT_ADD_SYND_NETDEV, event_data);
        break;

    case SX_DEV_EVENT_REMOVE_SYND_L2_NETDEV:
        pr_debug(PFX "sx_netdev_event: Got REMOVE_SYND_L2 event. "
                 "dev = %p, dev_id = %u, trap_id = 0x%x\n",
                 dev, dev->device_id, event_data->eth_l3_synd.hw_synd);
        sx_netdev_set_synd_l2(dev, resources, event_data->eth_l3_synd.hw_synd,
                              SX_DEV_EVENT_REMOVE_SYND_NETDEV, event_data);
        break;

    case SX_DEV_EVENT_ADD_SYND_PHY_NETDEV:
        pr_debug(PFX "sx_netdev_event: Got ADD_SYND_PHY event. "
                 "dev = %p, dev_id = %u, trap_id = 0x%x\n",
                 dev, dev->device_id, event_data->eth_l3_synd.hw_synd);
        sx_netdev_set_synd_phy(dev, resources, event_data->eth_l3_synd.hw_synd,
                               SX_DEV_EVENT_ADD_SYND_NETDEV, event_data);
        break;

    case SX_DEV_EVENT_REMOVE_SYND_PHY_NETDEV:
        pr_debug(PFX "sx_netdev_event: Got REMOVE_SYND_PHY event. "
                 "dev = %p, dev_id = %u, trap_id = 0x%x\n",
                 dev, dev->device_id, event_data->eth_l3_synd.hw_synd);
        sx_netdev_set_synd_phy(dev, resources, event_data->eth_l3_synd.hw_synd,
                               SX_DEV_EVENT_REMOVE_SYND_NETDEV, event_data);
        break;

    case SX_DEV_EVENT_DEBUG_NETDEV:
        pr_debug(PFX "sx_netdev_event: Got DEBUG_NETDEV event. "
                 "dev = %p, dev_id = %u, trap_id = 0x%x\n",
                 dev, dev->device_id, event_data->eth_l3_synd.hw_synd);
        sx_netdev_debug_dump(dev, resources);
        break;

    case SX_DEV_EVENT_LAG_OPER_STATE_UPDATE:
        pr_debug(PFX "sx_netdev_event: Got LAG_OPER_STATE_UPDATE event."
                 " dev = %p, dev_id = %u, lag_id = %u, oper_state = %u\n",
                 dev, dev->device_id, event_data->lag_oper_state_set.lag_id,
                 event_data->lag_oper_state_set.oper_state);
        sx_netdev_set_lag_oper_state(dev, event_data->lag_oper_state_set.lag_id,
                                     event_data->lag_oper_state_set.oper_state);
        break;

    case SX_DEV_EVENT_OFFLOAD_MARK_SET:
        pr_debug(PFX "sx_netdev_event: Got SX_DEV_EVENT_OFFLOAD_MARK_SET event."
                 " dev = %p, dev_id = %u, event_data->offload_mark_set.offload_mark_set_en = %u\n",
                 dev, dev->device_id, event_data->offload_mark_set.offload_mark_set_en);
        offload_fwd_mark_en = event_data->offload_mark_set.offload_mark_set_en;
        break;

    case SX_DEV_EVENT_MODULE_SUPPORT_SET:
        printk(KERN_INFO PFX "sx_netdev_event: Got SX_DEV_EVENT_MODULE_SUPPORT_SET event."
               " dev = %p, dev_id = %u, event_data->module_support_set.module_support_en = %u\n",
               dev, dev->device_id, event_data->module_support_set.module_support_en);
        module_support_en = event_data->module_support_set.module_support_en;
        break;

    case SX_DEV_EVENT_GET_NETDEV_TRAP_INFO:
        pr_debug(PFX "sx_netdev_event: Got SX_DEV_EVENT_GET_NETDEV_TRAP_INFO event.\n");
        sx_netdev_get_trap_info(dev, resources, event_data);
        break;

    case SX_DEV_EVENT_ADD_SYND_PSAMPLE:
        printk(KERN_INFO PFX "sx_netdev_event: Got ADD_SYND_PSAMPLE event. "
               "dev = %p, dev_id = %u, trap_id = 0x%x\n",
               dev, dev->device_id, event_data->psample_synd.hw_synd);
        sx_psample_set_synd(dev, event_data->psample_synd.hw_synd,
                            SX_DEV_EVENT_ADD_SYND_PSAMPLE, event_data);
        break;

    case SX_DEV_EVENT_REMOVE_SYND_PSAMPLE:
        printk(KERN_INFO PFX "sx_netdev_event: Got REMOVE_SYND_PSAMPLE event. "
               "dev = %p, dev_id = %u, trap_id = 0x%x\n",
               dev, dev->device_id, event_data->psample_synd.hw_synd);
        sx_psample_set_synd(dev, event_data->psample_synd.hw_synd,
                            SX_DEV_EVENT_REMOVE_SYND_PSAMPLE, event_data);
        break;

    case SX_DEV_EVENT_UPDATE_SAMPLE_RATE:
        printk(KERN_INFO PFX "sx_netdev_event: got port sample-rate update event (rate=%u).",
               event_data->psample_port_sample_rate.sample_rate);
        sx_psample_set_port_sample_ret(event_data->psample_port_sample_rate.local_port,
                                       event_data->psample_port_sample_rate.sample_rate);
        break;

    case SX_DEV_EVENT_CATASTROPHIC_ERROR:
    default:
        break;
    }
    return err;
}

#ifndef SX_DROP_MONITOR_DISABLED
/* MUST BE CALLED UNDER RCU_LOCK */
static struct net_device* __sx_netdev_get_netdev(int port_type, u16 port)
{
    int                i;
    struct net_device *netdev = NULL;

    for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
        netdev = rcu_dereference(g_netdev_resources->port_netdev[port_type][port][i]);
        if (netdev) {
            break;
        }
    }

    return netdev;
}

/* MUST BE CALLED UNDER RCU_LOCK */
static struct net_device* sx_netdev_get_netdev(struct completion_info *comp_info)
{
    int                ret;
    u16                local_port;
    struct net_device *netdev = NULL;

    if (comp_info->is_lag) {
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_local,
                                   ret,
                                   comp_info->dev,
                                   comp_info->sysport,
                                   comp_info->lag_subport,
                                   &local_port);

        if (ret) {
            goto out;
        }

        /* When the packet comes from a member port of a LAG, try to get
         * the member port netdev first, if no member port netdev has been
         * found, then try to get the LAG netdev.
         */
        netdev = __sx_netdev_get_netdev(PORT_TYPE_SINGLE, local_port);
        if (netdev) {
            goto out;
        }
    }

    netdev = __sx_netdev_get_netdev(comp_info->is_lag ? PORT_TYPE_LAG : PORT_TYPE_SINGLE,
                                    comp_info->sysport);

out:
    return netdev;
}
#endif /* SX_DROP_MONITOR_DISABLED */

int sx_net_dm_hw_report(struct completion_info *comp_info,
                        const char             *trap_name,
                        const char             *trap_grp_name,
                        const void             *fa_cookie,
                        u8                      copy_skb)
{
    int err = 0;

#ifndef SX_DROP_MONITOR_DISABLED
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 10, 0)) && !defined(CONFIG_SX_RHEL_8_6)
    struct net_dm_hw_metadata hw_metadata = { .trap_name = trap_name, .trap_group_name = trap_grp_name };
#else
    struct devlink_trap_metadata hw_metadata = {.trap_name = trap_name, .trap_group_name = trap_grp_name };
#endif
    struct sk_buff *new_skb = NULL;

#ifndef SX_FLOW_OFFLOAD_DISABLED
    hw_metadata.fa_cookie = fa_cookie;
#endif

    rcu_read_lock();

    hw_metadata.input_dev = sx_netdev_get_netdev(comp_info);

    if (!hw_metadata.input_dev) {
        goto out;
    }

    new_skb = copy_skb ? skb_copy(comp_info->skb, GFP_ATOMIC) : skb_clone(comp_info->skb, GFP_ATOMIC);
    if (!new_skb) {
        printk(KERN_WARNING PFX "Failed to allocate memory for %s skb", copy_skb ? "copied" : "cloned");
        err = -ENOMEM;
        goto out;
    }

    trace_sx_netdev_dm_hw_report(new_skb, &hw_metadata);
    new_skb->protocol = eth_type_trans(new_skb, hw_metadata.input_dev);
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 10, 0)) && !defined(CONFIG_SX_RHEL_8_6) && !defined(CONFIG_SX_CENTOS_8_4)
    net_dm_hw_report(new_skb, &hw_metadata);
#elif !defined(CONFIG_SX_CENTOS_8_4)
    if (trace_devlink_trap_report_enabled()) {
        trace_devlink_trap_report(g_devlink_dummy_instance, new_skb, &hw_metadata);
    }
#endif
out:
    rcu_read_unlock();

    if (new_skb) {
        kfree_skb(new_skb);
    }
#endif
    return err;
}

static struct sx_interface sx_netdev_interface = {
    .add = sx_netdev_init_one,
    .remove = sx_netdev_remove_one,
    .event = sx_netdev_event
};

u8 sx_netdev_sx_core_if_get_reference(void)
{
    unsigned long flags;
    u8            is_init = 0;

    read_lock_irqsave(&(sx_core_if.access_lock), flags);
    is_init = sx_core_if.init_done;
    if (!sx_core_if.init_done) {
        read_unlock_irqrestore(&(sx_core_if.access_lock), flags);
        printk(KERN_INFO PFX "sx_core_if is not init\n");
    } else {
        atomic_inc(&sx_core_if.refcount);
        read_unlock_irqrestore(&(sx_core_if.access_lock), flags);
    }
    return is_init;
}

void sx_netdev_sx_core_if_release_reference(void)
{
    if (atomic_dec_and_test(&sx_core_if.refcount)) {
        complete(&sx_core_if.free);
    }
}

static void sx_netdev_init_sx_core_interface(void)
{
    rwlock_init(&sx_core_if.access_lock);
    init_completion(&sx_core_if.free);
    atomic_set(&sx_core_if.refcount, 1);
    sx_core_if.init_done = 1;
}

#define ATTACH_ONE_NETDEV(netdev, dev)                                                                      \
    net_priv = netdev_priv(netdev);                                                                         \
    net_priv->dev = dev;                                                                                    \
    for (uc_type = USER_CHANNEL_L3_NETDEV; uc_type < NUM_OF_NET_DEV_TYPE; uc_type++) {                      \
        err = __sx_netdev_uc_type_get_data(uc_type, &crit, &netdev_callback);                               \
        if (err) {                                                                                          \
            printk(KERN_ERR PFX "%s: Failed get crit and handler for "                                      \
                   "user channel (%d).\n", __func__, uc_type);                                              \
            continue;                                                                                       \
        }                                                                                                   \
                                                                                                            \
        for (i = 0; i < net_priv->num_of_traps[uc_type]; i++) {                                             \
            port_vlan.port_vlan_type = net_priv->trap_ids[uc_type][i].info_type;                            \
            port_vlan.sysport = net_priv->trap_ids[uc_type][i].sysport;                                     \
            port_vlan.lag_id = net_priv->trap_ids[uc_type][i].lag_id;                                       \
            port_vlan.vlan = net_priv->trap_ids[uc_type][i].vlan;                                           \
            CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd, err,                                               \
                                       net_priv->swid, net_priv->trap_ids[uc_type][i].synd, L2_TYPE_ETH, 0, \
                                       "sx_netdev", 0, &crit, netdev_callback, netdev,                      \
                                       CHECK_DUP_ENABLED_E, net_priv->dev, &port_vlan, 1);                  \
            if (err) {                                                                                      \
                printk(KERN_ERR PFX "error %s, User channel (%d) failed registering on "                    \
                       "0x%x syndrome.\n", netdev->name, uc_type, net_priv->trap_ids[uc_type][i].synd);     \
            }                                                                                               \
        }                                                                                                   \
    }

#define SX_DEV_ATTACH_ONE_NETDEV(netdev, dev) \
    net_priv = netdev_priv(netdev);           \
    net_priv->dev = dev;

#define DETACH_ONE_NETDEV(netdev)                                                       \
    netif_tx_disable(netdev);                                                           \
    netif_carrier_off(netdev);                                                          \
    net_priv = netdev_priv(netdev);                                                     \
    for (uc_type = USER_CHANNEL_L3_NETDEV; uc_type < NUM_OF_NET_DEV_TYPE; uc_type++) {  \
        if (__sx_netdev_uc_type_get_data(uc_type, &crit, &netdev_callback)) {           \
            printk(KERN_ERR PFX "%s: Failed get crit and handler for "                  \
                   "user channel (%d).\n", __func__, uc_type);                          \
            continue;                                                                   \
        }                                                                               \
                                                                                        \
        for (i = 0; i < net_priv->num_of_traps[uc_type]; i++) {                         \
            port_vlan.port_vlan_type = net_priv->trap_ids[uc_type][i].info_type;        \
            port_vlan.sysport = net_priv->trap_ids[uc_type][i].sysport;                 \
            port_vlan.lag_id = net_priv->trap_ids[uc_type][i].lag_id;                   \
            port_vlan.vlan = net_priv->trap_ids[uc_type][i].vlan;                       \
            CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_remove_synd, net_priv->swid,          \
                                          net_priv->trap_ids[uc_type][i].synd,          \
                                          L2_TYPE_ETH, 0, &crit, netdev, net_priv->dev, \
                                          netdev_callback, &port_vlan, 1, NULL);        \
        }                                                                               \
    }                                                                                   \
    net_priv->dev = NULL;                                                               \

static void attach_netdevs(struct sx_dev *dev)
{
    int                        err = 0;
    struct net_device         *netdev = NULL;
    struct sx_net_priv        *net_priv = NULL;
    union ku_filter_critireas  crit;
    cq_handler                 netdev_callback = 0;
    int                        i, j;
    u8                         uc_type = 0;
    struct ku_port_vlan_params port_vlan;
    int                        port_type = 0;
    int                        port = 0, br_id = 0;
    int                        swid = 0;
    int                        max_ports[] = {
        [PORT_TYPE_SINGLE] = MAX_SYSPORT_NUM,
        [PORT_TYPE_LAG] = MAX_LAG_NUM
    };

    mutex_lock(&g_netdev_resources->rsc_lock);
    g_netdev_resources->in_attach_detach = 1;

    for (swid = 0; swid < NUMBER_OF_SWIDS; swid++) {
        if (!g_netdev_resources->allocated[swid]) {
            continue;
        }

        netdev = g_netdev_resources->sx_netdevs[swid];
        if (netdev == NULL) {
            continue;
        }

        ATTACH_ONE_NETDEV(netdev, dev);
        netdev_linkstate_set(netdev);
    }

    for (port_type = 0; port_type < PORT_TYPE_NUM; port_type++) {
        for (port = 0; port < max_ports[port_type]; port++) {
            if (g_netdev_resources->port_allocated[port_type][port] == 0) {
                continue;
            }
            for (j = 0; j < MAX_PORT_NETDEV_NUM; j++) {
                netdev = g_netdev_resources->port_netdev[port_type][port][j];
                if (netdev != NULL) {
                    ATTACH_ONE_NETDEV(netdev, dev);
                    netdev_linkstate_set(netdev);
                }
            }
        }
    }

    for (br_id = 0; br_id < MAX_BRIDGE_NUM; br_id++) {
        netdev = bridge_netdev_db[br_id];
        if (netdev != NULL) {
            SX_DEV_ATTACH_ONE_NETDEV(netdev, dev);
            netdev_linkstate_set(netdev);
        }
    }

    g_netdev_resources->in_attach_detach = 0;
    mutex_unlock(&g_netdev_resources->rsc_lock);
}

static void detach_netdevs(void)
{
    struct net_device         *netdev = NULL;
    struct sx_net_priv        *net_priv = NULL;
    union ku_filter_critireas  crit;
    cq_handler                 netdev_callback = 0;
    int                        i;
    u8                         uc_type = 0;
    struct ku_port_vlan_params port_vlan;
    int                        j;
    int                        port_type = 0;
    int                        port = 0, br_id = 0;
    int                        swid = 0;
    int                        max_ports[] = {
        [PORT_TYPE_SINGLE] = MAX_SYSPORT_NUM,
        [PORT_TYPE_LAG] = MAX_LAG_NUM
    };

    mutex_lock(&g_netdev_resources->rsc_lock);
    g_netdev_resources->in_attach_detach = 1;

    for (swid = 0; swid < NUMBER_OF_SWIDS; swid++) {
        if (!g_netdev_resources->allocated[swid]) {
            continue;
        }

        netdev = g_netdev_resources->sx_netdevs[swid];
        if (netdev == NULL) {
            continue;
        }

        DETACH_ONE_NETDEV(netdev);
    }

    for (port_type = 0; port_type < PORT_TYPE_NUM; port_type++) {
        for (port = 0; port < max_ports[port_type]; port++) {
            if (g_netdev_resources->port_allocated[port_type][port] == 0) {
                continue;
            }
            for (j = 0; j < MAX_PORT_NETDEV_NUM; j++) {
                netdev = g_netdev_resources->port_netdev[port_type][port][j];
                if (netdev != NULL) {
                    DETACH_ONE_NETDEV(netdev);
                }
            }
        }
    }

    for (br_id = 0; br_id < MAX_BRIDGE_NUM; br_id++) {
        netdev = bridge_netdev_db[br_id];
        if (netdev != NULL) {
            DETACH_ONE_NETDEV(netdev);
        }
    }

    g_netdev_resources->in_attach_detach = 0;
    mutex_unlock(&g_netdev_resources->rsc_lock);
}

static void sx_netdev_attach_global_event_handler(void)
{
    int                       err = 0;
    union ku_filter_critireas crit;

    /* Register listener for Ethernet SWID */
    memset(&crit, 0, sizeof(crit));

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd,
                               err,
                               ROUTER_PORT_SWID,
                               NUM_HW_SYNDROMES,
                               L2_TYPE_DONT_CARE,
                               0,
                               "sx_netdev",
                               0,
                               &crit,
                               sx_netdev_handle_global_pkt,
                               NULL,
                               CHECK_DUP_ENABLED_E,
                               g_sx_dev,
                               NULL,
                               1);
    if (err) {
        printk(KERN_ERR PFX "%s: Failed registering global rx_handler", __func__);
    }
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd, err, 0, SXD_TRAP_ID_PUDE, L2_TYPE_DONT_CARE, 0, "sx_netdev", 0,
                               &crit, sx_netdev_handle_pude_event, NULL,
                               CHECK_DUP_ENABLED_E, g_sx_dev, NULL, 1);
    if (err) {
        printk(KERN_ERR PFX "%s: Failed registering PUDE event rx_handler", __func__);
    }
}

static void __skip_tunnel_default(u8 skip_tunnel)
{
    struct net_device  *netdev = NULL;
    struct sx_net_priv *net_priv = NULL;
    int                 i;
    int                 port_type = 0;
    int                 port = 0, br_id = 0;
    int                 swid = 0;
    int                 max_ports[] = {
        [PORT_TYPE_SINGLE] = MAX_SYSPORT_NUM,
        [PORT_TYPE_LAG] = MAX_LAG_NUM
    };

    printk(KERN_INFO PFX "Set default skip_tunnel (%d)\n", skip_tunnel);

    g_skip_tunnel = skip_tunnel;

    mutex_lock(&g_netdev_resources->rsc_lock);

    for (swid = 0; swid < NUMBER_OF_SWIDS; swid++) {
        if (!g_netdev_resources->allocated[swid]) {
            continue;
        }

        netdev = g_netdev_resources->sx_netdevs[swid];
        if (netdev != NULL) {
            printk(KERN_INFO PFX "Set skip_tunnel (%d) for device '%s'\n", skip_tunnel, netdev->name);
            net_priv = netdev_priv(netdev);
            net_priv->skip_tunnel = skip_tunnel;
        }
    }

    for (port_type = 0; port_type < PORT_TYPE_NUM; port_type++) {
        for (port = 0; port < max_ports[port_type]; port++) {
            if (g_netdev_resources->port_allocated[port_type][port] == 0) {
                continue;
            }
            for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
                netdev = g_netdev_resources->port_netdev[port_type][port][i];
                if (netdev != NULL) {
                    printk(KERN_INFO PFX "Set skip_tunnel (%d) for device '%s'\n", skip_tunnel, netdev->name);
                    net_priv = netdev_priv(netdev);
                    net_priv->skip_tunnel = skip_tunnel;
                }
            }
        }
    }

    for (br_id = 0; br_id < MAX_BRIDGE_NUM; br_id++) {
        netdev = bridge_netdev_db[br_id];
        if (netdev != NULL) {
            printk(KERN_INFO PFX "Set skip_tunnel (%d) for device '%s'\n", skip_tunnel, netdev->name);
            net_priv = netdev_priv(netdev);
            net_priv->skip_tunnel = skip_tunnel;
        }
    }

    mutex_unlock(&g_netdev_resources->rsc_lock);
}

static void __skip_tunnel_dev(char* dev_name, u8 skip_tunnel)
{
    struct net_device  *netdev = NULL;
    struct sx_net_priv *net_priv = NULL;

    if (dev_name == NULL) {
        printk(KERN_ERR PFX "Skip tunnel set failed: no <dev_name>\n");
        return;
    }

    netdev = dev_get_by_name(&init_net, dev_name);
    if (netdev == NULL) {
        printk(KERN_ERR PFX "Skip tunnel set failed: Device name '%s' wasn't found\n", dev_name);
        return;
    }

    printk(KERN_INFO PFX "Set skip_tunnel (%d) for net device '%s'\n", skip_tunnel, dev_name);
    net_priv = netdev_priv(netdev);
    net_priv->skip_tunnel = skip_tunnel;
    dev_put(netdev);
}

char * sx_netdev_proc_str_get_u32(char *buffer, u32 *val32)
{
    const char delimiters[] = " .,;:!-";
    char      *running;
    char      *token;

    running = (char*)buffer;
    token = strsep(&running, delimiters);
    if (token == NULL) {
        *val32 = 0;
        return NULL;
    }

    if (strstr(token, "0x")) {
        *val32 = simple_strtol(token, NULL, 16);
    } else {
        *val32 = simple_strtol(token, NULL, 10);
    }

    return running;
}

char * sx_netdev_proc_str_get_str(char *buffer, char **str)
{
    const char delimiters[] = " ,;:!-";
    char      *running;
    char      *token;

    running = buffer;
    token = strsep(&running, delimiters);
    if (token == NULL) {
        *str = 0;
        return NULL;
    }

    *str = token;
    return running;
}

static ssize_t skip_tunnel_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    struct net_device  *netdev = NULL;
    struct sx_net_priv *net_priv = NULL;
    int                 i;
    int                 port_type = 0;
    int                 port = 0, br_id = 0;
    int                 swid = 0;
    int                 max_ports[] = {
        [PORT_TYPE_SINGLE] = MAX_SYSPORT_NUM,
        [PORT_TYPE_LAG] = MAX_LAG_NUM
    };
    int                 offset = 0;

    offset = sprintf(buf, "%-15s | %s\n", "dev_name", "skip_tunnel");
    offset += sprintf(buf + offset, "------------------------------\n");
    offset += sprintf(buf + offset, "%-15s | %d\n", "default", g_skip_tunnel);

    mutex_lock(&g_netdev_resources->rsc_lock);

    for (swid = 0; swid < NUMBER_OF_SWIDS; swid++) {
        if (!g_netdev_resources->allocated[swid]) {
            continue;
        }

        netdev = g_netdev_resources->sx_netdevs[swid];
        if (netdev != NULL) {
            net_priv = netdev_priv(netdev);
            offset += sprintf(buf + offset, "%-15s | %d\n", netdev->name, net_priv->skip_tunnel);
        }
    }

    for (port_type = 0; port_type < PORT_TYPE_NUM; port_type++) {
        for (port = 0; port < max_ports[port_type]; port++) {
            if (g_netdev_resources->port_allocated[port_type][port] == 0) {
                continue;
            }
            for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
                netdev = g_netdev_resources->port_netdev[port_type][port][i];
                if (netdev != NULL) {
                    net_priv = netdev_priv(netdev);
                    offset += sprintf(buf + offset, "%-15s | %d\n", netdev->name, net_priv->skip_tunnel);
                }
            }
        }
    }

    for (br_id = 0; br_id < MAX_BRIDGE_NUM; br_id++) {
        netdev = bridge_netdev_db[br_id];
        if (netdev != NULL) {
            net_priv = netdev_priv(netdev);
            offset += sprintf(buf + offset, "%-15s | %d\n", netdev->name, net_priv->skip_tunnel);
        }
    }

    mutex_unlock(&g_netdev_resources->rsc_lock);
    return offset;
}

static ssize_t skip_tunnel_cb(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len)
{
    int   cmd = 0;
    char *p = NULL;
    char *running = NULL;
    char *cmd_str = NULL;
    u32   skip_tunnel = 0;
    char *dev_name = NULL;

    running = (char*)buf;

    running = sx_netdev_proc_str_get_str(running, &cmd_str);
    p = strstr(cmd_str, "default");
    if (p != NULL) {
        running = sx_netdev_proc_str_get_u32(running, &skip_tunnel);
        __skip_tunnel_default(skip_tunnel);
        cmd++;
    }

    p = strstr(cmd_str, "set");
    if (p != NULL) {
        running = sx_netdev_proc_str_get_str(running, &dev_name);
        running = sx_netdev_proc_str_get_u32(running, &skip_tunnel);
        __skip_tunnel_dev(dev_name, skip_tunnel);
        cmd++;
    }

    if (cmd == 0) {
        printk(KERN_INFO PFX "Available Commands for skip_tunnel:\n");
        printk(KERN_INFO PFX "  default [disable (0) / enable (1)] - Set the default device skip tunnel\n");
        printk(KERN_INFO PFX "  set [dev_name] [disable (0) / enable (1)] - Set skip tunnel for <dev_name>\n");
    }

    return len;
}

int sx_netdev_get_net_device_by_kobj(struct kobject          *kobj,
                                     struct net_device      **dev,
                                     enum sx_net_kobject_type kobj_type)
{
    int                 ret = 0;
    u8                  i = 0;
    u32                 port = 0;
    struct net_device  *netdev = NULL;
    struct sx_net_priv *priv = NULL;
    int                 num_netdevs = single_netdev_per_port_enable ? 1 : MAX_PORT_NETDEV_NUM;

    if (!kobj) {
        printk(KERN_ERR PFX "sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    mutex_lock(&g_netdev_resources->rsc_lock);

    if (kobj_type > SX_NET_KOBJECT_MAX) {
        printk(KERN_ERR PFX "kobject type is wrong\n");
        ret = -EINVAL;
        goto out;
    }

    for (port = 0; port < MAX_SYSPORT_NUM; port++) {
        for (i = 0; i < num_netdevs; i++) {
            netdev = g_netdev_resources->port_netdev[PORT_TYPE_SINGLE][port][i];
            if (netdev != NULL) {
                priv = netdev_priv(netdev);
                if (kobj == priv->kobj[kobj_type]) {
                    *dev = netdev;
                    goto out;
                }
            }
        }
    }

    printk(KERN_DEBUG PFX "The net device is not existed for the kobj\n");
    ret = -ENOENT;

out:
    mutex_unlock(&g_netdev_resources->rsc_lock);
    return ret;
}

static ssize_t show_module_id(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                 ret = 0;
    struct net_device  *netdev = NULL;
    struct sx_net_priv *net_priv = NULL;
    uint8_t             slot_id = 0;
    uint8_t             module_id = 0;
    int                 len = 0;

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of reset sysfs node is NULL\n");
        ret = -EINVAL;
        return ret;
    }

    ret = sx_netdev_get_net_device_by_kobj(kobj, &netdev, SX_NET_KOBJECT_MODULE);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get the net device of the kobj\n");
        return ret;
    }

    net_priv = netdev_priv(netdev);
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_module_by_port, ret, net_priv->dev, net_priv->port, &slot_id, &module_id);
    if (ret) {
        return ret;
    }

    len = sprintf(buf, "%u\n", module_id);

    return len;
}

static ssize_t reset_module(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len)
{
    int                ret = 0;
    int                reset = 0;
    struct net_device *netdev = NULL;

    ret = kstrtoint(buf, 10, &reset);
    if (ret) {
        printk(KERN_INFO PFX "sysfs entry reset got invalid value\n");
        return ret;
    }

    if (!reset) {
        ret = -EINVAL;
        return ret;
    }

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of reset sysfs node is NULL\n");
        ret = -EINVAL;
        return ret;
    }
    ret = sx_netdev_get_net_device_by_kobj(kobj, &netdev, SX_NET_KOBJECT_MODULE);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get the net device of the kobj\n");
        return ret;
    }

    ret = sx_netdev_module_reset(netdev);
    if (ret) {
        printk(KERN_ERR PFX "Failed in sx_netdev_module_reset\n");
        return ret;
    }

    return len;
}

static ssize_t store_module_power_mode_policy(struct kobject        *kobj,
                                              struct kobj_attribute *attr,
                                              const char            *buf,
                                              size_t                 len)
{
    int                ret = 0;
    int                power_mode_policy = 0;
    struct net_device *netdev = NULL;

    ret = kstrtoint(buf, 10, &power_mode_policy);
    if (ret) {
        printk(KERN_ERR PFX "sysfs entry power_mode_policy got invalid value\n");
        ret = -EINVAL;
        return ret;
    }

    if ((power_mode_policy != SX_MODULE_POWER_MODE_POLICY_AUTO) &&
        (power_mode_policy != SX_MODULE_POWER_MODE_POLICY_HIGH)) {
        printk(KERN_ERR PFX "sysfs entry power_mode_policy got invalid value\n");
        ret = -EINVAL;
        return ret;
    }

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of reset sysfs node is NULL\n");
        ret = -EINVAL;
        return ret;
    }

    ret = sx_netdev_get_net_device_by_kobj(kobj, &netdev, SX_NET_KOBJECT_MODULE);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get the net device of the kobj\n");
        return ret;
    }

    ret = sx_netdev_module_power_mode_policy_set(netdev, (enum sx_module_power_mode_policy)power_mode_policy);
    if (ret) {
        printk(KERN_ERR PFX "Failed in sx_netdev_module_power_mode_policy_set\n");
        return ret;
    }

    return len;
}

static ssize_t show_module_power_mode_policy(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                                ret = 0;
    struct sx_module_power_mode_params params;
    struct net_device                 *netdev = NULL;
    int                                len = 0;

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of reset sysfs node is NULL\n");
        ret = -EINVAL;
        return ret;
    }

    ret = sx_netdev_get_net_device_by_kobj(kobj, &netdev, SX_NET_KOBJECT_MODULE);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get the net device of the kobj\n");
        return ret;
    }

    memset(&params, 0, sizeof(params));

    ret = sx_netdev_module_power_mode_get(netdev, &params);
    if (ret) {
        printk(KERN_ERR PFX "Failed in sx_netdev_module_power_mode_get\n");
        return ret;
    }

    len = sprintf(buf, "%u\n", params.policy);

    return len;
}

static ssize_t show_module_power_mode(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                                ret = 0;
    struct sx_module_power_mode_params params;
    struct net_device                 *netdev = NULL;
    int                                len = 0;

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of reset sysfs node is NULL\n");
        ret = -EINVAL;
        return ret;
    }

    ret = sx_netdev_get_net_device_by_kobj(kobj, &netdev, SX_NET_KOBJECT_MODULE);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get the net device of the kobj\n");
        return ret;
    }

    memset(&params, 0, sizeof(params));

    ret = sx_netdev_module_power_mode_get(netdev, &params);
    if (ret) {
        printk(KERN_ERR PFX "Failed in sx_netdev_module_power_mode_get\n");
        return ret;
    }

    len = sprintf(buf, "%u\n", params.mode);

    return len;
}

static ssize_t show_link_ext_state(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                           ret = 0;
    struct net_device            *netdev = NULL;
    struct sx_link_ext_state_info link_ext_state_info;
    int                           len = 0;

    ret = sx_netdev_get_net_device_by_kobj(kobj, &netdev, SX_NET_KOBJECT_PORT);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get the net device of the kobj\n");
        ret = -EINVAL;
        return ret;
    }

    memset(&link_ext_state_info, 0, sizeof(link_ext_state_info));

    ret = __get_link_ext_state(netdev, &link_ext_state_info);
    if (ret) {
        printk(KERN_DEBUG PFX "Cannot get state info in __get_link_ext_state\n");
        return 0;
    }

    len = sprintf(buf, "%u %u\n", link_ext_state_info.link_ext_state, link_ext_state_info.__link_ext_substate);

    return len;
}

static int __sx_netdev_get_module_temperature(struct kobject *kobj, struct sx_temperature_params *params)
{
    int                 ret = 0;
    struct net_device  *netdev = NULL;
    struct sx_net_priv *net_priv = NULL;

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of temperature sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = sx_netdev_get_net_device_by_kobj(kobj, &netdev, SX_NET_KOBJECT_MODULE_TEMP);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get the net device of the kobj\n");
        goto out;
    }

    memset(params, 0, sizeof(struct sx_temperature_params));
    net_priv = netdev_priv(netdev);

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_port_module_temperature, ret, net_priv->dev, net_priv->port, params);
    if (ret) {
        goto out;
    }

out:
    return ret;
}

static ssize_t show_module_temp_input(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                          ret = 0;
    struct sx_temperature_params params;
    int                          len = 0;

    ret = __sx_netdev_get_module_temperature(kobj, &params);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get module temperature information\n");
        return ret;
    }

    len = sprintf(buf, "%llu\n", params.input);

    return len;
}

static ssize_t show_module_temp_label(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                          ret = 0;
    struct sx_temperature_params params;
    int                          len = 0;


    ret = __sx_netdev_get_module_temperature(kobj, &params);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get module temperature information\n");
        return ret;
    }

    len = sprintf(buf, "%s\n", params.label);

    return len;
}

static void __bind_unbind_sx_core(bool is_bind, struct sx_dev *dev)
{
    unsigned long flags;

    if (is_bind) {
        read_lock_irqsave(&sx_core_if.access_lock, flags);
        if (sx_core_if.init_done) {
            read_unlock_irqrestore(&sx_core_if.access_lock, flags);
            printk(KERN_INFO PFX "sx_core already attach\n");
            return;
        }

        read_unlock_irqrestore(&sx_core_if.access_lock, flags);
        atomic_set(&sx_core_if.refcount, 1);
        init_completion(&sx_core_if.free);

        write_lock_irqsave(&sx_core_if.access_lock, flags);
        sx_core_if.init_done = 1;
        write_unlock_irqrestore(&sx_core_if.access_lock, flags);

        sx_netdev_attach_global_event_handler();
        attach_netdevs(dev);
        CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_register_net_dm_hw_report, sx_net_dm_hw_report);
        sx_psample_init();
    } else { /* unbind */
        read_lock_irqsave(&sx_core_if.access_lock, flags);
        if (sx_core_if.init_done == 0) {
            read_unlock_irqrestore(&sx_core_if.access_lock, flags);
            printk(KERN_INFO PFX "sx_core already detached\n");
            return;
        }
        read_unlock_irqrestore(&sx_core_if.access_lock, flags);

        CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_register_net_dm_hw_report, NULL);

        detach_netdevs();
        sx_netdev_unregister_global_event_handler();
        sx_psample_cleanup();

        write_lock_irqsave(&sx_core_if.access_lock, flags);
        sx_core_if.init_done = 0;
        write_unlock_irqrestore(&sx_core_if.access_lock, flags);

        if (atomic_dec_and_test(&sx_core_if.refcount)) {
            complete(&sx_core_if.free);
        }
        wait_for_completion(&sx_core_if.free);

        if (g_sx_dev) {
            g_sx_dev = NULL;
        }
    }
}

static ssize_t store_bind_sx_core(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len)
{
    int ret;
    int is_bind;

    ret = kstrtoint(buf, 10, &is_bind);
    if (ret) {
        printk(KERN_INFO PFX "sysfs entry bind_sx_core got invalid value\n");
        return ret;
    }

    /* This sysfs entry is obsolete, we do nothing here.*/

    return len;
}

#if !defined(SX_DROP_MONITOR_DISABLED) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, \
                                                                                 0)) || defined(CONFIG_SX_RHEL_8_6))
#define DEVLINK_DUMMY_NAME "devlink_dummy"

static struct bus_type devlink_dummy_bus = {
    .name = DEVLINK_DUMMY_NAME,
    .dev_name = DEVLINK_DUMMY_NAME,
};

static struct device_driver devlink_dummy_driver = {
    .name = DEVLINK_DUMMY_NAME,
    .bus = &devlink_dummy_bus,
    .owner = THIS_MODULE,
};

static void devlink_dummy_dev_release(struct device *dev)
{
}

static struct device            devlink_dummy_dev = {
    .bus = &devlink_dummy_bus,
    .release = devlink_dummy_dev_release,
};
static const struct devlink_ops devlink_dummy_ops = {
    .port_split = sx_netdev_port_split,
    .port_unsplit = sx_netdev_port_unsplit,
};

static int __devlink_dummy_init(void)
{
    int err = 0;

    err = bus_register(&devlink_dummy_bus);
    if (err) {
        goto out;
    }

    err = driver_register(&devlink_dummy_driver);
    if (err) {
        goto err_bus_unregister;
    }

    err = device_register(&devlink_dummy_dev);
    if (err) {
        goto err_driver_unregister;
    }

    g_devlink_dummy_instance = devlink_alloc(&devlink_dummy_ops, 0);
    if (!g_devlink_dummy_instance) {
        err = -ENOMEM;
        goto err_device_unregister;
    }

    err = devlink_register(g_devlink_dummy_instance, &devlink_dummy_dev);
    if (err) {
        goto err_devlink_free;
    }
    goto out;

err_devlink_free:
    devlink_free(g_devlink_dummy_instance);
    g_devlink_dummy_instance = NULL;

err_device_unregister:
    device_unregister(&devlink_dummy_dev);

err_driver_unregister:
    driver_unregister(&devlink_dummy_driver);

err_bus_unregister:
    bus_unregister(&devlink_dummy_bus);

out:
    return err;
}

static void __devlink_dummy_exit(void)
{
    devlink_unregister(g_devlink_dummy_instance);
    devlink_free(g_devlink_dummy_instance);
    g_devlink_dummy_instance = NULL;
    device_unregister(&devlink_dummy_dev);
    driver_unregister(&devlink_dummy_driver);
    bus_unregister(&devlink_dummy_bus);
}
#endif /* if !defined(SX_DROP_MONITOR_DISABLED) && (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0)) */

#if defined(CONFIG_NET_PORT) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)))
static void sx_netdev_fib_alias_hw_flags_set(struct fib_rt_info *fri, bool offload, bool trap, bool offload_failed)
{
    fri->offload = offload;
    fri->trap = trap;
    fri->offload_failed = offload_failed;
}

static inline bool sx_netdev_is_offloaded_device(struct net_device *dev)
{
    if ((dev->netdev_ops == &sx_netdev_ops) ||
        dev->rtnl_link_ops) {
        return true;
    }

    return false;
}

static void sx_netdev_fib_new_entry4(struct fib_entry_notifier_info *fen_info)
{
    struct fib_info *fi = fen_info->fi;
    unsigned int     i;
    bool             trap = false;
    struct net      *fb_net;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0)) || defined(CONFIG_SX_RHEL_8_6)
    fb_net = &init_net;
#else
    fb_net = fen_info->info.net;
#endif

    if ((fi->fib_type == RTN_LOCAL) || (fi->fib_type == RTN_BROADCAST)) {
        trap = true;
    }

    for (i = 0; i < fib_info_num_path(fi); i++) {
        struct fib_nh_common *nhc = fib_info_nhc(fi, i);
        struct net_device    *dev = nhc->nhc_dev;

        if (dev && sx_netdev_is_offloaded_device(dev)) {
            struct fib_rt_info fri;

            fri.fi = fi;
            fri.tb_id = fen_info->tb_id;
            fri.dst = cpu_to_be32(fen_info->dst);
            fri.dst_len = fen_info->dst_len;
            fri.tos = fen_info->tos;
            fri.type = fen_info->type;
            if (trap) {
                sx_netdev_fib_alias_hw_flags_set(&fri, false, true, false);
            } else {
                sx_netdev_fib_alias_hw_flags_set(&fri, true, false, false);
            }
            fib_alias_hw_flags_set(fb_net, NULL, &fri);
        }
    }
}

static void sx_netdev_fib_new_entry6(struct fib6_entry_notifier_info *f6en_info)
{
    struct fib6_info *f6i = f6en_info->rt;
    bool              trap = false;
    struct net       *fb_net;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0)) || defined(CONFIG_SX_RHEL_8_6)
    fb_net = &init_net;
#else
    fb_net = f6en_info->info.net;
#endif

    if ((f6i->fib6_type == RTN_LOCAL) || (f6i->fib6_type == RTN_BROADCAST)) {
        trap = true;
    }

    if (f6i->nh) {
        struct nexthop *nh = f6i->nh;
        unsigned int    i;

        for (i = 0; i < nexthop_num_path(nh); i++) {
            struct fib_nh_common *nhc = nexthop_fib_nhc(nh, i);
            struct net_device    *dev = nhc->nhc_dev;

            if (dev && sx_netdev_is_offloaded_device(dev)) {
                if (trap) {
                    fib6_info_hw_flags_set(fb_net, NULL, f6i, false,
                                           true, false);
                } else {
                    fib6_info_hw_flags_set(fb_net, NULL, f6i, true,
                                           false, false);
                }
            }
        }
    } else {
        /* For ipv6 multipath routes, a notification is sent for each
         * fib6 sibling.
         */
        struct fib6_nh    *fib6_nh = f6i->fib6_nh;
        struct net_device *dev = fib6_nh->fib_nh_dev;

        if (dev && sx_netdev_is_offloaded_device(dev)) {
            if (trap) {
                fib6_info_hw_flags_set(fb_net, NULL, f6i, false, true,
                                       false);
            } else {
                fib6_info_hw_flags_set(fb_net, NULL, f6i, true, false,
                                       false);
            }
        }
    }
}

static int sx_netdev_fib_event_nb(struct notifier_block *nb, unsigned long event, void *ptr)
{
    struct fib_notifier_info *info = ptr;

    if (!route_offload_flags) {
        return NOTIFY_OK;
    }

    if ((event == FIB_EVENT_ENTRY_ADD) || (event == FIB_EVENT_ENTRY_REPLACE)) {
        if (info->family == AF_INET) {
            struct fib_entry_notifier_info *fen_info = ptr;

            sx_netdev_fib_new_entry4(fen_info);
        } else if (info->family == AF_INET6) {
            struct fib6_entry_notifier_info *f6en_info = ptr;

            sx_netdev_fib_new_entry6(f6en_info);
        }
    }

    return NOTIFY_OK;
}

static struct notifier_block sx_netdev_fib_nb = {
    .notifier_call = sx_netdev_fib_event_nb,
};
#endif /* if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) */

static int __init sx_netdev_init(void)
{
    int ret;

    printk(KERN_INFO PFX "sx_netdev_init\n");

    g_netdev_wq = create_singlethread_workqueue("sx_link");
    if (!g_netdev_wq) {
        printk(KERN_ERR PFX "Failed to create wq sx_link. \n");
        return -ENOMEM;
    }

#if defined(CONFIG_NET_PORT) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)))
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0)) || defined(CONFIG_SX_RHEL_8_6)
    ret = register_fib_notifier(&init_net, &sx_netdev_fib_nb, NULL, NULL);
#else
    ret = register_fib_notifier(&sx_netdev_fib_nb, NULL);
#endif
    if (ret < 0) {
        printk(KERN_ERR PFX "Failed to register fib notifier\n");
        goto fail_on_register_fib_notifier;
    }
#endif /* if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) */

    memset(&sx_core_if, 0, sizeof(sx_core_if));
    sx_netdev_init_sx_core_interface();

    ret = sx_register_interface(&sx_netdev_interface);
    if (ret) {
        goto fail_on_sx_register_interface;
    }

    ret = sx_netdev_register_global_event_handler();
    if (ret) {
        goto fail_on_register_global_event_handler;
    }

    ret = sx_netdev_rtnl_link_register();
    if (ret) {
        goto fail_on_netdev_rtnl_link_register;
    }

    ret = sx_bridge_rtnl_link_register();
    if (ret) {
        goto fail_on_bridge_rtnl_link_register;
    }

    ret = sysfs_create_file(&(THIS_MODULE->mkobj.kobj), &(bind_sx_core_attr.attr));
    if (ret) {
        goto fail_on_create_bind_sx_core_sysfs_file;
    }

    ret = sysfs_create_file(&(THIS_MODULE->mkobj.kobj), &(skip_netdev_attr.attr));
    if (ret) {
        goto fail_on_create_skip_netdev_sysfs_file;
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) || defined(CONFIG_SX_RHEL_8_6)
    if (mirror_device_en) {
        ret = sx_span2cpu_create_mirror_netdev(&sx_netdev_ops, &sx_ethtool_ops);
        if (ret) {
            pr_err(PFX "Error creating SPAN-to-CPU mirror interface");
            goto fail_on_create_skip_netdev_sysfs_file;
        }
    }
#endif

#if !defined(SX_DROP_MONITOR_DISABLED) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, \
                                                                                 0)) || defined(CONFIG_SX_RHEL_8_6))
    ret = __devlink_dummy_init();
    if (ret) {
        goto fail_on_devlink_dummy_init;
    }
#endif

    CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_register_net_dm_hw_report, sx_net_dm_hw_report);

    sx_psample_init();

    return 0;

#if !defined(SX_DROP_MONITOR_DISABLED) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, \
                                                                                 0)) || defined(CONFIG_SX_RHEL_8_6))
fail_on_devlink_dummy_init:
    sysfs_remove_file(&(THIS_MODULE->mkobj.kobj), &(skip_netdev_attr.attr));
    if (mirror_device_en) {
        sx_span2cpu_free_mirror_netdev();
    }
#endif

fail_on_create_skip_netdev_sysfs_file:
    sysfs_remove_file(&(THIS_MODULE->mkobj.kobj), &(bind_sx_core_attr.attr));

fail_on_create_bind_sx_core_sysfs_file:
    sx_bridge_rtnl_link_unregister();

fail_on_bridge_rtnl_link_register:
    sx_netdev_rtnl_link_unregister();

fail_on_netdev_rtnl_link_register:
    sx_netdev_unregister_global_event_handler();

fail_on_register_global_event_handler:
    sx_unregister_interface(&sx_netdev_interface);

fail_on_sx_register_interface:
#if defined(CONFIG_NET_PORT) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)))
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    unregister_fib_notifier(&init_net, &sx_netdev_fib_nb);
#else
    unregister_fib_notifier(&sx_netdev_fib_nb);
#endif
#endif /* if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) */

#if defined(CONFIG_NET_PORT) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)))
fail_on_register_fib_notifier:
#endif /* if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) */
    destroy_workqueue(g_netdev_wq);

    return ret;
}

static void __exit sx_netdev_cleanup(void)
{
    printk(KERN_INFO PFX "sx_netdev_cleanup \n");
#if !defined(SX_DROP_MONITOR_DISABLED) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, \
                                                                                 0)) || defined(CONFIG_SX_RHEL_8_6))
    __devlink_dummy_exit();
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) || defined(CONFIG_SX_RHEL_8_6)
    if (mirror_device_en) {
        sx_span2cpu_free_mirror_netdev();
    }
#endif

    sysfs_remove_file(&(THIS_MODULE->mkobj.kobj), &(skip_netdev_attr.attr));
    sysfs_remove_file(&(THIS_MODULE->mkobj.kobj), &(bind_sx_core_attr.attr));
    sx_bridge_rtnl_link_unregister();
    sx_netdev_rtnl_link_unregister();
    sx_netdev_unregister_global_event_handler();
    sx_psample_cleanup();

    if (g_netdev_wq) {
        destroy_workqueue(g_netdev_wq);
    }

    sx_unregister_interface(&sx_netdev_interface);

#if defined(CONFIG_NET_PORT) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)))
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    unregister_fib_notifier(&init_net, &sx_netdev_fib_nb);
#else
    unregister_fib_notifier(&sx_netdev_fib_nb);
#endif
#endif /* if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) */
}

module_init(sx_netdev_init);
module_exit(sx_netdev_cleanup);
