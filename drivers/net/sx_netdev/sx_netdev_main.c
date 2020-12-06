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

#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/kernel_user.h>
#ifdef CONFIG_NET_SWITCHDEV
#include <net/switchdev.h>
#endif
#include "sx_netdev.h"
#include "sx_psample.h"

/*
 * Local define in order to allocate skb IP aligned.
 * In header asm/processor.h NET_IP_ALIGN is defined as 0.
 */
#ifdef NET_IP_ALIGN
#undef NET_IP_ALIGN
#endif
#define NET_IP_ALIGN (2)

MODULE_AUTHOR("Amos Hersch");
MODULE_DESCRIPTION("Mellanox SwitchX Network Device Driver");
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

int offload_fwd_mark_en = 1;
#ifdef CONFIG_NET_SWITCHDEV
module_param_named(offload_fwd_mark_en, offload_fwd_mark_en, int, 0644);
MODULE_PARM_DESC(offload_fwd_mark_en, "1 - enable offload of packets fwd in HW, 0 - disable offload");
#endif

static ssize_t skip_tunnel_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t skip_tunnel_cb(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len);
static struct kobj_attribute skip_netdev_attr =
    __ATTR(skip_tunnel, S_IWUSR | S_IRUGO, skip_tunnel_show, skip_tunnel_cb);
static ssize_t store_bind_sx_core(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len);
static struct kobj_attribute bind_sx_core_attr = __ATTR(bind_sx_core, S_IWUSR, NULL, store_bind_sx_core);
static char                  sx_netdev_version[] =
    PFX "Mellanox SwitchX Network Device Driver "
    DRV_VERSION " (" DRV_RELDATE ")\n";
struct sx_netdev_rsc    *g_netdev_resources = NULL; /* Should be replaced in the core with sx_dev context */
struct sx_dev          * g_sx_dev = NULL;
struct net_device       *bridge_netdev_db[MAX_BRIDGE_NUM];
struct workqueue_struct *netdev_wq;
struct sx_core_interface sx_core_if;
void                    *g_dev_ctx = NULL;
u8                       g_skip_tunnel = 0;

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

    if (carrier_set_on_pude_disable) {
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
    if ((is_tagged == VLAN_UNTAGGED_E) && vlan_child_exist) {
        new_skb = netdev_alloc_skb(NULL, old_skb->len + 4 + NET_IP_ALIGN);
        if (!new_skb) {
            err = -ENOMEM;
            goto out;
        }

        skb_reserve(new_skb, NET_IP_ALIGN);

        p_skb_data = skb_put(new_skb, old_skb->len + 4);
        if (!p_skb_data) {
            kfree_skb(new_skb);
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
    kfree_skb(old_skb);
    return err;
}

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
#ifdef CONFIG_NET_SWITCHDEV
    if (offload_fwd_mark_en) {
        skb->offload_fwd_mark = 1;
    } else {
        skb->offload_fwd_mark = 0;
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

    net_priv->stats.rx_packets++;
    net_priv->stats.rx_bytes += skb->len;

    netif_rx(skb);
}

static void sx_netdev_log_port_rx_pkt(struct completion_info *comp_info, void *context)
{
    /* Get routed netdev */
    u8 i = 0, port_type = 0;

    port_type = comp_info->is_lag ? PORT_TYPE_LAG : PORT_TYPE_SINGLE;
    for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
        if (g_netdev_resources->port_netdev[port_type][comp_info->sysport][i] != NULL) {
            sx_netdev_handle_rx(comp_info, g_netdev_resources->port_netdev[port_type][comp_info->sysport][i]);
        } else {
            if (sx_netdev_rx_debug) {
                printk(KERN_ERR "%s: %s %d index %d netdev is NULL! dropping packet!\n",
                       __func__,
                       comp_info->is_lag ? "lag" : "port",
                       comp_info->sysport, i);
            }
        }
    }
}

static void sx_netdev_phy_port_rx_pkt(struct completion_info *comp_info, void *context)
{
    /* Get routed netdev */
    struct net_device  *netdev = context;
    struct sx_net_priv *net_priv = netdev_priv(netdev);
    uint16_t            local = comp_info->sysport;
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

    for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
        if (g_netdev_resources->port_netdev[PORT_TYPE_SINGLE][local][i] != NULL) {
            sx_netdev_handle_rx(comp_info, g_netdev_resources->port_netdev[PORT_TYPE_SINGLE][local][i]);
        } else {
            if (sx_netdev_rx_debug) {
                printk(KERN_ERR "%s: port %d index %d netdev is NULL! dropping packet!\n",
                       __func__, local, i);
            }
        }
    }
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

void sx_netdev_dwork_func(struct work_struct *pude_dwork)
{
    struct sx_net_priv *net_priv = container_of(pude_dwork, struct sx_net_priv, pude_dwork.work);
    struct net_device  *netdev = net_priv->netdev;

    if (netdev == NULL) {
        printk(KERN_ERR PFX "Error: net_priv->netdev is NULL !!!\n");
        return;
    }

    netdev_linkstate_set(netdev);
}

/* Called on every PUDE event */
static void __sx_netdev_scedule_work(struct sx_net_priv *net_priv)
{
    /* the delayed queueing used to change context */
    queue_delayed_work(netdev_wq, &net_priv->pude_dwork, 0);
}

/* Called on every PUDE event */
static void sx_netdev_handle_pude_event(struct completion_info *comp_info, void *context)
{
    struct net_device        *netdev = NULL;
    struct sxd_emad_pude_reg* pude = (struct sxd_emad_pude_reg *)comp_info->skb->data;
    struct sx_emad           *emad_header = &pude->emad_header;
    struct sx_net_priv       *net_priv;
    int                       reg_id = be16_to_cpu(emad_header->emad_op.register_id);
    unsigned int              logical_port = 0;
    int                       sysport = 0;
    int                       is_up = 0, is_lag = 0, i = 0;
    unsigned short            type_len, ethertype;

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

    logical_port = 0x10000 + (pude->local_port << SX_PORT_PHY_ID_OFFS);
    if (sx_netdev_sx_core_if_get_reference()) {
        if (!sx_core_if.translate_user_port_to_sysport || !g_sx_dev) {
            printk(KERN_INFO PFX "sx_core_if.translate_user_port_to_sysport or g_sx_dev is NULL\n");
            sx_netdev_sx_core_if_release_reference();
            return;
        } else {
            sysport = sx_core_if.translate_user_port_to_sysport(g_sx_dev, logical_port, &is_lag);
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
    is_up = pude->oper_status == PORT_OPER_STATUS_UP;

    printk("%s: Called for logical port - %05X status %s\n", __func__,
           logical_port, is_up ? "UP" : "DOWN");

    /* Change port status for port netdev */
    for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
        netdev = g_netdev_resources->port_netdev[PORT_TYPE_SINGLE][sysport][i];
        if (netdev) {
            net_priv = netdev_priv(netdev);
            net_priv->is_oper_state_up = is_up;
            __sx_netdev_scedule_work(net_priv);
        }
    }
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
        for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
            netdev = g_netdev_resources->port_netdev[port_type][comp_info->sysport][i];
            __sx_netdev_handle_global_pkt(netdev, comp_info);
        }
    }
}

static int sx_netdev_register_global_event_handler(void)
{
    int                       err = 0;
    union ku_filter_critireas crit;

    /* Register listener for Ethernet SWID */
    memset(&crit, 0, sizeof(crit));
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd, err, ROUTER_PORT_SWID, NUM_HW_SYNDROMES, L2_TYPE_DONT_CARE, 0, 0,
                               crit, sx_netdev_handle_global_pkt, NULL,
                               CHECK_DUP_DISABLED_E, NULL, NULL, 1);
    if (err) {
        printk(KERN_ERR PFX "%s: Failed registering global rx_handler", __func__);
        return err;
    }
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd, err, 0, SXD_TRAP_ID_PUDE, L2_TYPE_DONT_CARE, 0, 0,
                               crit, sx_netdev_handle_pude_event, NULL,
                               CHECK_DUP_DISABLED_E, NULL, NULL, 1);
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
                               crit, NULL, NULL, NULL, NULL, 1);
    if (err) {
        printk(KERN_ERR PFX "error: Failed de registering on "
               "0x%x syndrome.\n", NUM_HW_SYNDROMES);
        return err;
    }

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_remove_synd, err, 0, SXD_TRAP_ID_PUDE, L2_TYPE_DONT_CARE, 0,
                               crit, NULL, NULL, NULL, NULL, 1);
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

    if (crit_p == NULL) {
        printk(KERN_ERR PFX "%s: crit_p is NULL.\n", __func__);
        err = -ERANGE;
        goto out;
    }
    if (netdev_callback_p == NULL) {
        printk(KERN_ERR PFX "%s: netdev_callback_p is NULL.\n", __func__);
        err = -ERANGE;
        goto out;
    }

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

    printk(KERN_INFO PFX "%s: called\n", __func__);

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
                                       0,
                                       crit,
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

out:
    printk(KERN_INFO PFX "%s: exit\n", __func__);
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

    printk(KERN_INFO PFX "%s: called\n", __func__);

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
                                          L2_TYPE_ETH, 0, crit, netdev, net_priv->dev,
                                          netdev_callback, &port_vlan, 1);
        }
    }

    netif_tx_disable(netdev);
    netif_carrier_off(netdev);

    printk(KERN_INFO PFX "%s: exit\n", __func__);
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

    printk("%s: Called for lag_id %d  status %s\n", __func__,
           lag_id, oper_state ? "UP" : "DOWN");

    /* Change port netdev status */
    for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
        netdev = g_netdev_resources->port_netdev[PORT_TYPE_LAG][lag_id][i];
        if (netdev) {
            net_priv = netdev_priv(netdev);
            net_priv->is_oper_state_up = oper_state;
            netdev_linkstate_set(netdev);
        }
    }
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
    kfree_skb(skb);
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
    kfree_skb(skb);
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
    kfree_skb(skb);
    return err;
}

static int sx_netdev_hard_start_xmit(struct sk_buff *skb, struct net_device *netdev)
{
    struct sx_net_priv *net_priv = netdev_priv(netdev);
    int                 err = 0;
    int                 len = 0;
    struct isx_meta     meta;
    struct sk_buff     *tmp_skb = NULL;
    struct vlan_ethhdr *veth = NULL;
    u16                 pcp = 0;
    uint16_t            ifc_vlan = 0;
    u8                  is_ifc_rp = 0;
    u8                  tx_hw_timestamp = 0, tx_hw_timestamp_flags = 0;
    struct sock        *tx_hw_timestamp_sock = NULL;
    u8                  is_tagged;

    if (net_priv->dev == NULL) {
        if (printk_ratelimit()) {
            printk(KERN_ERR PFX "sx_netdev_hard_start_"
                   "xmit: netdev %s net_priv->dev is NULL.\n", netdev->name);
        }
        net_priv->stats.tx_dropped++;
        kfree_skb(skb);
        return -ENXIO;
    }

    veth = (struct vlan_ethhdr *)(skb->data);
    is_tagged = (ntohs(veth->h_vlan_proto) == ETH_P_8021Q);

    sx_netdev_override_icmp_ip(netdev, skb);

    if (sx_netdev_tx_debug) {
        printk(KERN_DEBUG PFX "%s called for (%s)\n", __func__, netdev->name);
    }
    netdev->trans_start = jiffies; /* save the timestamp */

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

    if ((net_priv->hwtstamp_config.tx_type == HWTSTAMP_TX_ON) &&
        unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)) {
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_ptp_tx_handler,
                                   err,
                                   net_priv->dev,
                                   skb,
                                   net_priv->port,
                                   net_priv->is_lag);

        if (err) {
            if (printk_ratelimit()) {
                printk(KERN_ERR "failed to handle PTP TX packet (err=%d)\n", err);
            }
        } else {
            /* we should save these local parameters in case skb will be replaced in this function (a VLAN
             * header should be added or not enough headroom */
            tx_hw_timestamp = 1;
            tx_hw_timestamp_flags = skb_shinfo(skb)->tx_flags;
            tx_hw_timestamp_sock = skb->sk;
        }
    }

    /* *****************************************/
    /* Apply SPC2/3 PTP WA                     */

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_ptp_tx_control_to_data,
                               err,
                               net_priv->dev,
                               &skb,
                               &meta,
                               net_priv->port,
                               net_priv->is_lag,
                               &is_tagged,
                               tx_hw_timestamp);

    if (err) {
        kfree_skb(skb);
        return err;
    }

    /* *****************************************/

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

            kfree_skb(skb);
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
            kfree_skb(skb);
            return -ENOMEM;
        }

        skb_reserve(tmp_skb, ISX_HDR_SIZE);
        memcpy(skb_put(tmp_skb, len), skb->data, len);
        kfree_skb(skb);
        len += ISX_HDR_SIZE;
    }

    if (tx_hw_timestamp) {
        /* need to override these parameters with the ones we saved in this function. skb may have replaced
         * (allocated again) and these old parameters does not exist there anymore */
        skb_shinfo(tmp_skb)->tx_flags = tx_hw_timestamp_flags;
        tmp_skb->sk = tx_hw_timestamp_sock;
    }

    if (sx_netdev_sx_core_if_get_reference()) {
        if (sx_core_if.sx_core_post_send) {
            err = sx_core_if.sx_core_post_send(net_priv->dev, tmp_skb, &meta);
        } else {
            printk(KERN_INFO PFX "sx_core_if.sx_core_post_send is NULL\n");
            err = -ENXIO;
            kfree_skb(tmp_skb);
        }
        sx_netdev_sx_core_if_release_reference();
    } else {
        printk(KERN_INFO PFX "sx_core_if is not initialized\n");
        err = -ENXIO;
        kfree_skb(tmp_skb);
    }

    if (err) {
        printk(KERN_ERR PFX "error %s, Failed sending packet\n",
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

#ifdef CONFIG_NET_SWITCHDEV
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

    if (copy_from_user(&config, ifr->ifr_data, sizeof(config))) {
        return -EFAULT;
    }

    /* TX HW timestamp */
    switch (config.tx_type) {
    case HWTSTAMP_TX_OFF:
    case HWTSTAMP_TX_ON:
        break;

    default:
        return -ERANGE;
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

static const struct net_device_ops sx_netdev_ops = {
    .ndo_open = sx_netdev_open,
    .ndo_stop = sx_netdev_stop,
    .ndo_start_xmit = sx_netdev_hard_start_xmit,
    .ndo_set_mac_address = sx_netdev_set_mac,
    .ndo_set_rx_mode = sx_netdev_set_multicast,
    .ndo_do_ioctl = sx_netdev_do_ioctl,
    .ndo_change_mtu = sx_netdev_change_mtu,
    .ndo_get_stats = sx_netdev_get_stats,
    .ndo_vlan_rx_add_vid = sx_netdev_vlan_rx_add_vid,
    .ndo_vlan_rx_kill_vid = sx_netdev_vlan_rx_kill_vid,
    .ndo_tx_timeout = NULL, /* Disable the transmit timeout function.  */
};
static int sx_get_ts_info(struct net_device *dev, struct ethtool_ts_info *info)
{
    uint8_t             ptp_clock_index = 0, ptp_enable = 0;
    int                 ret;
    struct sx_net_priv *net_priv = netdev_priv(dev);

    ret = ethtool_op_get_ts_info(dev, info);
    if (ret) {
        return ret;
    }
    if (!net_priv->is_port_netdev && !net_priv->is_lag) {
        return 0;
    }
    CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_get_ptp_state, net_priv->dev, &ptp_enable);
    if (ptp_enable) {
        CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_get_ptp_clock_index, net_priv->dev, &ptp_clock_index);
        info->phc_index = ptp_clock_index;

        info->so_timestamping |= SOF_TIMESTAMPING_TX_HARDWARE |
                                 SOF_TIMESTAMPING_RX_HARDWARE |
                                 SOF_TIMESTAMPING_RAW_HARDWARE;

        info->tx_types = (BIT(1) << HWTSTAMP_TX_OFF) |
                         (BIT(1) << HWTSTAMP_TX_ON);
        info->rx_filters = (BIT(1) << HWTSTAMP_FILTER_NONE) |
                           (BIT(1) << HWTSTAMP_FILTER_ALL);
    }

    return 0;
}

const struct ethtool_ops sx_ethtool_ops = {
    .get_ts_info = sx_get_ts_info,
};

int sx_netdev_register_device(struct net_device *netdev, int should_rtnl_lock, int admin_state)
{
    int                 err = 0;
    struct sx_net_priv *net_priv = netdev_priv(netdev);
    struct inet6_dev   *idev = NULL;

    printk(KERN_INFO PFX "%s: called for device %s\n", __func__, netdev->name);

#ifdef CONFIG_NET_SWITCHDEV
    netdev->switchdev_ops = &sx_netdev_switchdev_ops;
#endif

    /* set netdev defaults and function callbacks */
    netdev->base_addr = 0;
    netdev->irq = 0;
    netdev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;

    sx_netdev_u64_to_mac(netdev->dev_addr, net_priv->mac);
    netdev->mtu = DEFAULT_FRAME_SIZE;

    netdev->netdev_ops = &sx_netdev_ops;
    netdev->ethtool_ops = &sx_ethtool_ops;
    if (should_rtnl_lock) {
        rtnl_lock();
    }
    err = register_netdevice(netdev);

    idev = __in6_dev_get(netdev);
    if (idev) {
        idev->cnf.disable_ipv6 = 1;
    }

    if (admin_state && net_priv->mac) {
        dev_change_flags(netdev, netdev->flags | IFF_UP);
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

    printk(KERN_INFO PFX "%s: exit\n", __func__);
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
    netdev = alloc_netdev(sizeof(*net_priv), name, ether_setup);
    if (!netdev) {
        printk(KERN_ERR PFX  "Net Device struct %s alloc failed, "
               "aborting.\n", name);
        return NULL;
    }

    netdev->hard_header_len = ETH_HLEN + ISX_HDR_SIZE;
    memset(netdev_priv(netdev), 0, sizeof(*net_priv));
    net_priv = netdev_priv(netdev);
    net_priv->swid = swid;
    net_priv->dev = dev;
    net_priv->mac = mac;
    net_priv->is_oper_state_up = 1;
    net_priv->skip_tunnel = g_skip_tunnel;
    net_priv->netdev = netdev;
    INIT_DELAYED_WORK(&net_priv->pude_dwork, sx_netdev_dwork_func);

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
    unsigned long      flags;

    spin_lock_irqsave(&resources->rsc_lock, flags);

    if (g_netdev_resources->in_attach_detach == 1) {
        spin_unlock_irqrestore(&resources->rsc_lock, flags);
        printk(KERN_ERR PFX  "Can't init swid %d netdev during attach/detach \n", swid);
        return -EFAULT;
    }

    if (resources->allocated[swid]) {
        spin_unlock_irqrestore(&resources->rsc_lock, flags);
        printk(KERN_ERR PFX  "Net Device for swid %d was already"
               " allocated\n", swid);
        return -EFAULT;
    }

    resources->allocated[swid] = 1;
    spin_unlock_irqrestore(&resources->rsc_lock, flags);
    netdev = __sx_netdev_init_one_netdev(dev, swid, synd, mac);
    if (!netdev) {
        spin_lock_irqsave(&resources->rsc_lock, flags);
        resources->allocated[swid] = 0;
        spin_unlock_irqrestore(&resources->rsc_lock, flags);

        return -EFAULT;
    }

    resources->sx_netdevs[swid] = netdev;

    return 0;
}

static void sx_netdev_remove_one_netdev(struct sx_dev *dev, void *rsc, int swid)
{
    struct net_device    *netdev;
    struct sx_netdev_rsc *resources = rsc;
    unsigned long         flags;

    spin_lock_irqsave(&resources->rsc_lock, flags);

    if (g_netdev_resources->in_attach_detach == 1) {
        spin_unlock_irqrestore(&resources->rsc_lock, flags);
        printk(KERN_ERR PFX  "Can't remove swid %u netdev during attach/detach \n", swid);
        return;
    }

    netdev = resources->sx_netdevs[swid];
    if (!resources->allocated[swid]) {
        spin_unlock_irqrestore(&resources->rsc_lock, flags);
        return;
    }

    resources->sx_netdevs[swid] = NULL;
    resources->allocated[swid] = 0;
    spin_unlock_irqrestore(&resources->rsc_lock, flags);
    sx_netdev_unregister_device(netdev);
}

static void * sx_netdev_init_one(struct sx_dev *dev)
{
    static int            sx_netdev_version_printed = 0;
    struct sx_netdev_rsc *resources;
    int                   i;

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

    spin_lock_init(&resources->rsc_lock);

    g_netdev_resources = resources;
    g_sx_dev = dev;

    return resources;
}

static void sx_netdev_remove_one(struct sx_dev *dev, void *rsc)
{
    int                   i;
    struct sx_netdev_rsc *resources = rsc;
    uint16_t              lag_max = 0, lag_member_max = 0;
    int                   err = 0;

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX "sx_netdev_remove_one\n");
#endif
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_lag_max, err, dev, &lag_max, &lag_member_max);
    if (err) {
        printk(KERN_ERR PFX "Failed to get max number of LAGs. err = %u.\n", err);
        return;
    }

    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        sx_netdev_remove_one_netdev(dev, resources, i);
    }

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
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd, err, net_priv->swid, synd, L2_TYPE_ETH, 0, 0,
                                   crit, netdev_callback, netdev,
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
    int                       trap_was_found = 0;
    int                       i;
    union ku_filter_critireas crit;
    cq_handler                netdev_callback = 0;

    for (i = 0; i < net_priv->num_of_traps[uc_type]; i++) {
        if (net_priv->trap_ids[uc_type][i].synd == synd) {
            printk(KERN_INFO PFX "The synd 0x%x was found and will be removed.\n", synd);
            memcpy(&(net_priv->trap_ids[uc_type][i]),
                   &(net_priv->trap_ids[uc_type][net_priv->num_of_traps[uc_type] - 1]),
                   sizeof(struct net_port_vlan_info));
            net_priv->trap_ids[uc_type][net_priv->num_of_traps[uc_type] - 1].synd = SX_INVALID_TRAP_ID;
            net_priv->num_of_traps[uc_type]--;
            trap_was_found = 1;
            break;
        }
    }

    if (trap_was_found && (netdev->flags & IFF_UP)) {
        err = __sx_netdev_uc_type_get_data(uc_type, &crit, &netdev_callback);
        if (err) {
            printk(KERN_ERR PFX "%s: Failed get crit and handler for "
                   "user channel (%d).\n", __func__, uc_type);
            goto out;
        }

        CALL_SX_CORE_FUNC_WITH_RET(sx_core_remove_synd, err, net_priv->swid, synd, L2_TYPE_ETH, 0,
                                   crit, netdev, net_priv->dev, netdev_callback, port_vlan, is_register);

        if (err) {
            printk(KERN_ERR PFX "error %s, Failed de registering on "
                   "0x%x syndrome.\n", netdev->name, synd);
            goto out;
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
    unsigned long              flags;
    int                        i;
    int                        err;
    union ku_filter_critireas  crit;
    struct ku_port_vlan_params port_vlan;

    spin_lock_irqsave(&resources->rsc_lock, flags);
    if (g_netdev_resources->in_attach_detach == 1) {
        spin_unlock_irqrestore(&resources->rsc_lock, flags);
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
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd, err, 0, synd, L2_TYPE_ETH, 0, 0,
                                   crit, sx_netdev_handle_global_pkt, NULL,
                                   CHECK_DUP_DISABLED_E, NULL, &port_vlan, event_data->eth_l3_synd.is_register);
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
                                   crit,
                                   NULL,
                                   NULL,
                                   sx_netdev_handle_global_pkt,
                                   &port_vlan,
                                   event_data->eth_l3_synd.is_register);
        if (err) {
            printk(KERN_ERR PFX "Failed unregistering RP rx_handle on "
                   "syndrome %d.\n", synd);
        }
    }

    /* register the listener according to the swid */
    memset(&crit, 0, sizeof(crit)); /* sets all ETH values to default */
    crit.eth.from_bridge = IS_BRIDGE_FROM_BRIDGE_E;
    if (event == SX_DEV_EVENT_ADD_SYND_NETDEV) {
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd, err, 0, synd, L2_TYPE_ETH, 0, 0,
                                   crit, sx_netdev_handle_global_pkt, NULL,
                                   CHECK_DUP_DISABLED_E, NULL, &port_vlan, event_data->eth_l3_synd.is_register);
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
                                   crit,
                                   NULL,
                                   NULL,
                                   sx_netdev_handle_global_pkt,
                                   &port_vlan,
                                   event_data->eth_l3_synd.is_register);
        if (err) {
            printk(KERN_ERR PFX "Failed unregistering bridge rx_handle on "
                   "syndrome %d.\n", synd);
        }
    }

    spin_unlock_irqrestore(&resources->rsc_lock, flags);
}

static void sx_netdev_set_synd_l2(struct sx_dev       *dev,
                                  void                *rsc,
                                  u16                  synd,
                                  enum sx_dev_event    event,
                                  union sx_event_data *event_data)
{
    struct sx_netdev_rsc      *resources = rsc;
    unsigned long              flags;
    int                        i;
    struct ku_port_vlan_params port_vlan;

    spin_lock_irqsave(&resources->rsc_lock, flags);
    if (g_netdev_resources->in_attach_detach == 1) {
        spin_unlock_irqrestore(&resources->rsc_lock, flags);
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
    spin_unlock_irqrestore(&resources->rsc_lock, flags);
}

static void sx_netdev_set_synd_phy(struct sx_dev       *dev,
                                   void                *rsc,
                                   u16                  synd,
                                   enum sx_dev_event    event,
                                   union sx_event_data *event_data)
{
    struct sx_netdev_rsc      *resources = rsc;
    unsigned long              flags;
    int                        i;
    struct ku_port_vlan_params port_vlan;

    spin_lock_irqsave(&resources->rsc_lock, flags);
    if (g_netdev_resources->in_attach_detach == 1) {
        spin_unlock_irqrestore(&resources->rsc_lock, flags);
        printk(KERN_ERR PFX  "Can't set phy synd %d during attach/detach \n", synd);
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
    spin_unlock_irqrestore(&resources->rsc_lock, flags);
}

void __sx_netdev_dump_per_dev(struct net_device *netdev)
{
    struct sx_net_priv *net_priv = netdev_priv(netdev);
    int                 i;
    u8                  uc_type = 0;
    char              * uc_str[NUM_OF_NET_DEV_TYPE] = {"USER_CHANNEL_L3_NETDEV",
                                                       "USER_CHANNEL_LOG_PORT_NETDEV",
                                                       "USER_CHANNEL_PHY_PORT_NETDEV"};

    printk("======   Netdev %s dump:   =====\n", netdev->name);

    for (uc_type = USER_CHANNEL_L3_NETDEV; uc_type < NUM_OF_NET_DEV_TYPE; uc_type++) {
        printk("num of %s traps: %d\n", uc_str[uc_type], net_priv->num_of_traps[uc_type]);
        for (i = 0; i < MAX_NUM_TRAPS_TO_REGISTER; i++) {
            if (net_priv->trap_ids[uc_type][i].synd != SX_INVALID_TRAP_ID) {
                printk("trap[%d]: 0x%x\n", i, net_priv->trap_ids[uc_type][i].synd);
                printk("Filter_type %s - Port:%d, lag:%d, vlan:%d\n",
                       net_port_vlan_type_str[net_priv->trap_ids[uc_type][i].info_type],
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
    unsigned long         flags;
    int                   i = 0, port = 0, port_type = 0;
    int                   max_ports[] = {
        [PORT_TYPE_SINGLE] = MAX_SYSPORT_NUM,
        [PORT_TYPE_LAG] = MAX_LAG_NUM
    };

    spin_lock_irqsave(&resources->rsc_lock, flags);

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

    spin_unlock_irqrestore(&resources->rsc_lock, flags);

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
    unsigned long         flags;
    int                   i, j;
    struct sx_net_priv   *net_priv;
    uint8_t               uc_type = 0;

    spin_lock_irqsave(&resources->rsc_lock, flags);

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

    spin_unlock_irqrestore(&resources->rsc_lock, flags);
}

static void sx_netdev_event(struct sx_dev       *dev,
                            void                *resources,
                            enum sx_dev_event    event,
                            union sx_event_data *event_data)
{
    switch (event) {
    case SX_DEV_EVENT_ETH_SWID_UP:
        printk(KERN_INFO PFX "sx_netdev_event: Got ETH swid up event. "
               "dev = %p, dev_id = %u, swid = %d, "
               "synd = 0x%x, mac = 0x%llx\n",
               dev, dev->device_id, event_data->eth_swid_up.swid,
               event_data->eth_swid_up.synd, event_data->eth_swid_up.mac);
        sx_netdev_init_one_netdev(dev, resources, event_data->eth_swid_up.swid,
                                  event_data->eth_swid_up.synd, event_data->eth_swid_up.mac);
        return;

    case SX_DEV_EVENT_ETH_SWID_DOWN:
        printk(KERN_INFO PFX "sx_netdev_event: Got ETH swid down event. "
               "dev = %p, dev_id = %u, swid = %d\n",
               dev, dev->device_id, event_data->eth_swid_down.swid);
        sx_netdev_remove_one_netdev(dev, resources, event_data->eth_swid_down.swid);
        return;

    case SX_DEV_EVENT_ADD_SYND_NETDEV:
        printk(KERN_INFO PFX "sx_netdev_event: Got ADD_SYND_L3 event. "
               "dev = %p, dev_id = %u, trap_id = 0x%x\n",
               dev, dev->device_id, event_data->eth_l3_synd.hw_synd);
        sx_netdev_set_synd_l3(dev, resources, event_data->eth_l3_synd.hw_synd,
                              SX_DEV_EVENT_ADD_SYND_NETDEV, event_data);
        break;

    case SX_DEV_EVENT_REMOVE_SYND_NETDEV:
        printk(KERN_INFO PFX "sx_netdev_event: Got REMOVE_SYND_L3 event. "
               "dev = %p, dev_id = %u, trap_id = 0x%x\n",
               dev, dev->device_id, event_data->eth_l3_synd.hw_synd);
        sx_netdev_set_synd_l3(dev, resources, event_data->eth_l3_synd.hw_synd,
                              SX_DEV_EVENT_REMOVE_SYND_NETDEV, event_data);
        break;

    case SX_DEV_EVENT_ADD_SYND_L2_NETDEV:
        printk(KERN_INFO PFX "sx_netdev_event: Got ADD_SYND_L2 event. "
               "dev = %p, dev_id = %u, trap_id = 0x%x\n",
               dev, dev->device_id, event_data->eth_l3_synd.hw_synd);
        sx_netdev_set_synd_l2(dev, resources, event_data->eth_l3_synd.hw_synd,
                              SX_DEV_EVENT_ADD_SYND_NETDEV, event_data);
        break;

    case SX_DEV_EVENT_REMOVE_SYND_L2_NETDEV:
        printk(KERN_INFO PFX "sx_netdev_event: Got REMOVE_SYND_L2 event. "
               "dev = %p, dev_id = %u, trap_id = 0x%x\n",
               dev, dev->device_id, event_data->eth_l3_synd.hw_synd);
        sx_netdev_set_synd_l2(dev, resources, event_data->eth_l3_synd.hw_synd,
                              SX_DEV_EVENT_REMOVE_SYND_NETDEV, event_data);
        break;

    case SX_DEV_EVENT_ADD_SYND_PHY_NETDEV:
        printk(KERN_INFO PFX "sx_netdev_event: Got ADD_SYND_PHY event. "
               "dev = %p, dev_id = %u, trap_id = 0x%x\n",
               dev, dev->device_id, event_data->eth_l3_synd.hw_synd);
        sx_netdev_set_synd_phy(dev, resources, event_data->eth_l3_synd.hw_synd,
                               SX_DEV_EVENT_ADD_SYND_NETDEV, event_data);
        break;

    case SX_DEV_EVENT_REMOVE_SYND_PHY_NETDEV:
        printk(KERN_INFO PFX "sx_netdev_event: Got REMOVE_SYND_PHY event. "
               "dev = %p, dev_id = %u, trap_id = 0x%x\n",
               dev, dev->device_id, event_data->eth_l3_synd.hw_synd);
        sx_netdev_set_synd_phy(dev, resources, event_data->eth_l3_synd.hw_synd,
                               SX_DEV_EVENT_REMOVE_SYND_NETDEV, event_data);
        break;

    case SX_DEV_EVENT_DEBUG_NETDEV:
        printk(KERN_INFO PFX "sx_netdev_event: Got DEBUG_NETDEV event. "
               "dev = %p, dev_id = %u, trap_id = 0x%x\n",
               dev, dev->device_id, event_data->eth_l3_synd.hw_synd);
        sx_netdev_debug_dump(dev, resources);
        break;

    case SX_DEV_EVENT_LAG_OPER_STATE_UPDATE:
        printk(KERN_INFO PFX "sx_netdev_event: Got LAG_OPER_STATE_UPDATE event."
               " dev = %p, dev_id = %u, lag_id = %u, oper_state = %u\n",
               dev, dev->device_id, event_data->lag_oper_state_set.lag_id,
               event_data->lag_oper_state_set.oper_state);
        sx_netdev_set_lag_oper_state(dev, event_data->lag_oper_state_set.lag_id,
                                     event_data->lag_oper_state_set.oper_state);
        break;

    case SX_DEV_EVENT_OFFLOAD_MARK_SET:
        printk(KERN_INFO PFX "sx_netdev_event: Got SX_DEV_EVENT_OFFLOAD_MARK_SET event."
               " dev = %p, dev_id = %u, event_data->offload_mark_set.offload_mark_set_en = %u\n",
               dev, dev->device_id, event_data->offload_mark_set.offload_mark_set_en);
        offload_fwd_mark_en = event_data->offload_mark_set.offload_mark_set_en;
        break;

    case SX_DEV_EVENT_GET_NETDEV_TRAP_INFO:
        printk(KERN_INFO PFX "sx_netdev_event: Got SX_DEV_EVENT_GET_NETDEV_TRAP_INFO event.\n");
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
        return;
    }
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

#define INIT_ONE_SX_CORE_FUNC(func_name) \
    sx_core_if.func_name = __symbol_get(#func_name);

#define DEINIT_ONE_SX_CORE_FUNC(func_name) \
    if (sx_core_if.func_name) {__symbol_put(#func_name); }

static void sx_netdev_init_sx_core_interface(void)
{
    rwlock_init(&sx_core_if.access_lock);
    init_completion(&sx_core_if.free);
    atomic_set(&sx_core_if.refcount, 1);
    INIT_ONE_SX_CORE_FUNC(sx_core_flush_synd_by_context);
    INIT_ONE_SX_CORE_FUNC(translate_user_port_to_sysport);
    INIT_ONE_SX_CORE_FUNC(translate_sysport_to_user_port);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_lag_oper_state);
    INIT_ONE_SX_CORE_FUNC(sx_cmd_set_op_tlv);
    INIT_ONE_SX_CORE_FUNC(sx_ACCESS_REG_PAOS);
    INIT_ONE_SX_CORE_FUNC(sx_ACCESS_REG_PPAD);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_lag_mid);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_rp_vlan);
    INIT_ONE_SX_CORE_FUNC(sx_core_add_synd);
    INIT_ONE_SX_CORE_FUNC(sx_core_remove_synd);
    INIT_ONE_SX_CORE_FUNC(sx_core_flush_synd_by_handler);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_prio2tc);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_vlan_tagging);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_prio_tagging);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_vlan2ip);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_pvid);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_rp_rfid);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_send_to_port_as_data);
    INIT_ONE_SX_CORE_FUNC(sx_core_post_send);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_local);
    INIT_ONE_SX_CORE_FUNC(sx_register_interface);
    INIT_ONE_SX_CORE_FUNC(sx_unregister_interface);
    INIT_ONE_SX_CORE_FUNC(sx_attach_interface);
    INIT_ONE_SX_CORE_FUNC(sx_detach_interface);
    INIT_ONE_SX_CORE_FUNC(sx_core_cleanup_dynamic_data);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_ptp_state);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_ptp_clock_index);
    INIT_ONE_SX_CORE_FUNC(sx_core_ptp_tx_handler);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_lag_max);
    INIT_ONE_SX_CORE_FUNC(sx_core_get_rp_mode);
    INIT_ONE_SX_CORE_FUNC(sx_core_skb_add_vlan);
    INIT_ONE_SX_CORE_FUNC(sx_core_ptp_tx_control_to_data);

    sx_core_if.init_done = 1;
}

static void sx_netdev_deinit_sx_core_interface(void)
{
    DEINIT_ONE_SX_CORE_FUNC(sx_core_flush_synd_by_context);
    DEINIT_ONE_SX_CORE_FUNC(translate_user_port_to_sysport);
    DEINIT_ONE_SX_CORE_FUNC(translate_sysport_to_user_port);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_lag_oper_state);
    DEINIT_ONE_SX_CORE_FUNC(sx_cmd_set_op_tlv);
    DEINIT_ONE_SX_CORE_FUNC(sx_ACCESS_REG_PAOS);
    DEINIT_ONE_SX_CORE_FUNC(sx_ACCESS_REG_PPAD);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_lag_mid);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_rp_vlan);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_add_synd);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_remove_synd);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_flush_synd_by_handler);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_prio2tc);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_vlan_tagging);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_prio_tagging);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_vlan2ip);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_pvid);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_rp_rfid);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_send_to_port_as_data);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_post_send);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_local);
    DEINIT_ONE_SX_CORE_FUNC(sx_register_interface);
    DEINIT_ONE_SX_CORE_FUNC(sx_unregister_interface);
    DEINIT_ONE_SX_CORE_FUNC(sx_attach_interface);
    DEINIT_ONE_SX_CORE_FUNC(sx_detach_interface);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_cleanup_dynamic_data);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_ptp_state);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_ptp_clock_index);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_ptp_tx_handler);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_lag_max);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_get_rp_mode);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_skb_add_vlan);
    DEINIT_ONE_SX_CORE_FUNC(sx_core_ptp_tx_control_to_data);
}

#define GET_ONE_SX_CORE_FUNC(func_name)               \
    if (!(sx_core_if.func_name)) {                    \
        func_name ## _tmp = __symbol_get(#func_name); \
    }

#define PUT_ONE_SX_CORE_FUNC(func_name) \
    if (func_name ## _tmp) {            \
        __symbol_put(#func_name);       \
    }

#define ASSIGN_ONE_FUNC_PTR(func_name)            \
    if (!(sx_core_if.func_name)) {                \
        sx_core_if.func_name = func_name ## _tmp; \
    }

#define EMPTY_ONE_FUNC_PTR(func_name)         \
    func_name ## _tmp = sx_core_if.func_name; \
    if (sx_core_if.func_name) {               \
        sx_core_if.func_name = NULL;          \
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
                                       0, crit, netdev_callback, netdev,                                    \
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

#define DETACH_ONE_NETDEV(netdev)                                                      \
    netif_tx_disable(netdev);                                                          \
    netif_carrier_off(netdev);                                                         \
    net_priv = netdev_priv(netdev);                                                    \
    for (uc_type = USER_CHANNEL_L3_NETDEV; uc_type < NUM_OF_NET_DEV_TYPE; uc_type++) { \
        if (__sx_netdev_uc_type_get_data(uc_type, &crit, &netdev_callback)) {          \
            printk(KERN_ERR PFX "%s: Failed get crit and handler for "                 \
                   "user channel (%d).\n", __func__, uc_type);                         \
            continue;                                                                  \
        }                                                                              \
                                                                                       \
        for (i = 0; i < net_priv->num_of_traps[uc_type]; i++) {                        \
            port_vlan.port_vlan_type = net_priv->trap_ids[uc_type][i].info_type;       \
            port_vlan.sysport = net_priv->trap_ids[uc_type][i].sysport;                \
            port_vlan.lag_id = net_priv->trap_ids[uc_type][i].lag_id;                  \
            port_vlan.vlan = net_priv->trap_ids[uc_type][i].vlan;                      \
            CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_remove_synd, net_priv->swid,         \
                                          net_priv->trap_ids[uc_type][i].synd,         \
                                          L2_TYPE_ETH, 0, crit, netdev, net_priv->dev, \
                                          netdev_callback, &port_vlan, 1);             \
        }                                                                              \
    }                                                                                  \
    net_priv->dev = NULL;                                                              \

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
    unsigned long              flags;
    int                        port_type = 0;
    int                        port = 0, br_id = 0;
    int                        swid = 0;
    int                        max_ports[] = {
        [PORT_TYPE_SINGLE] = MAX_SYSPORT_NUM,
        [PORT_TYPE_LAG] = MAX_LAG_NUM
    };

    spin_lock_irqsave(&g_netdev_resources->rsc_lock, flags);
    g_netdev_resources->in_attach_detach = 1;
    spin_unlock_irqrestore(&g_netdev_resources->rsc_lock, flags);

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

    spin_lock_irqsave(&g_netdev_resources->rsc_lock, flags);
    g_netdev_resources->in_attach_detach = 0;
    spin_unlock_irqrestore(&g_netdev_resources->rsc_lock, flags);
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
    unsigned long              flags;
    int                        j;
    int                        port_type = 0;
    int                        port = 0, br_id = 0;
    int                        swid = 0;
    int                        max_ports[] = {
        [PORT_TYPE_SINGLE] = MAX_SYSPORT_NUM,
        [PORT_TYPE_LAG] = MAX_LAG_NUM
    };

    spin_lock_irqsave(&g_netdev_resources->rsc_lock, flags);
    g_netdev_resources->in_attach_detach = 1;
    spin_unlock_irqrestore(&g_netdev_resources->rsc_lock, flags);

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

    spin_lock_irqsave(&g_netdev_resources->rsc_lock, flags);
    g_netdev_resources->in_attach_detach = 0;
    spin_unlock_irqrestore(&g_netdev_resources->rsc_lock, flags);
}

static void sx_netdev_attach_global_event_handler(void)
{
    int                       err = 0;
    union ku_filter_critireas crit;

    /* Register listener for Ethernet SWID */
    memset(&crit, 0, sizeof(crit));

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd, err, ROUTER_PORT_SWID, NUM_HW_SYNDROMES, L2_TYPE_DONT_CARE, 0, 0,
                               crit, sx_netdev_handle_global_pkt, NULL,
                               CHECK_DUP_ENABLED_E, NULL, NULL, 1);
    if (err) {
        printk(KERN_ERR PFX "%s: Failed registering global rx_handler", __func__);
    }
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd, err, 0, SXD_TRAP_ID_PUDE, L2_TYPE_DONT_CARE, 0, 0,
                               crit, sx_netdev_handle_pude_event, NULL,
                               CHECK_DUP_ENABLED_E, NULL, NULL, 1);
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

static ssize_t store_bind_sx_core(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len)
{
    int            ret;
    int            value;
    unsigned long  flags;
    struct sx_dev *dev = NULL;
    void          *dev_ctx = NULL;
    void          *sx_core_flush_synd_by_context_tmp = NULL;
    void          *translate_user_port_to_sysport_tmp = NULL;
    void          *translate_sysport_to_user_port_tmp = NULL;
    void          *sx_core_get_lag_oper_state_tmp = NULL;
    void          *sx_cmd_set_op_tlv_tmp = NULL;
    void          *sx_ACCESS_REG_PAOS_tmp = NULL;
    void          *sx_ACCESS_REG_PPAD_tmp = NULL;
    void          *sx_core_get_lag_mid_tmp = NULL;
    void          *sx_core_get_rp_vlan_tmp = NULL;
    void          *sx_core_add_synd_tmp = NULL;
    void          *sx_core_remove_synd_tmp = NULL;
    void          *sx_core_flush_synd_by_handler_tmp = NULL;
    void          *sx_core_get_prio2tc_tmp = NULL;
    void          *sx_core_get_vlan_tagging_tmp = NULL;
    void          *sx_core_get_prio_tagging_tmp = NULL;
    void          *sx_core_get_vlan2ip_tmp = NULL;
    void          *sx_core_get_pvid_tmp = NULL;
    void          *sx_core_get_rp_rfid_tmp = NULL;
    void          *sx_core_get_send_to_port_as_data_tmp = NULL;
    void          *sx_core_post_send_tmp = NULL;
    void          *sx_core_get_local_tmp = NULL;
    void          *sx_register_interface_tmp = NULL;
    void          *sx_unregister_interface_tmp = NULL;
    void          *sx_attach_interface_tmp = NULL;
    void          *sx_detach_interface_tmp = NULL;
    void          *sx_core_cleanup_dynamic_data_tmp = NULL;
    void          *sx_core_get_rp_mode_tmp = NULL;
    void          *sx_core_skb_add_vlan_tmp = NULL;
    void          *sx_core_ptp_tx_control_to_data_tmp = NULL;

    ret = kstrtoint(buf, 10, &value);
    if (ret) {
        printk(KERN_INFO PFX "sysfs entry bind_sx_core got invalid value\n");
        return ret;
    }

    if (value) {
        read_lock_irqsave(&sx_core_if.access_lock, flags);
        if (sx_core_if.init_done) {
            read_unlock_irqrestore(&sx_core_if.access_lock, flags);
            printk(KERN_INFO PFX "sx_core already attach\n");
            return len;
        }
        read_unlock_irqrestore(&sx_core_if.access_lock, flags);
        atomic_set(&sx_core_if.refcount, 1);
        init_completion(&sx_core_if.free);

        GET_ONE_SX_CORE_FUNC(sx_core_flush_synd_by_context);
        GET_ONE_SX_CORE_FUNC(translate_user_port_to_sysport);
        GET_ONE_SX_CORE_FUNC(translate_sysport_to_user_port);
        GET_ONE_SX_CORE_FUNC(sx_core_get_lag_oper_state);
        GET_ONE_SX_CORE_FUNC(sx_cmd_set_op_tlv);
        GET_ONE_SX_CORE_FUNC(sx_ACCESS_REG_PAOS);
        GET_ONE_SX_CORE_FUNC(sx_ACCESS_REG_PPAD);
        GET_ONE_SX_CORE_FUNC(sx_core_get_lag_mid);
        GET_ONE_SX_CORE_FUNC(sx_core_get_rp_vlan);
        GET_ONE_SX_CORE_FUNC(sx_core_add_synd);
        GET_ONE_SX_CORE_FUNC(sx_core_remove_synd);
        GET_ONE_SX_CORE_FUNC(sx_core_flush_synd_by_handler);
        GET_ONE_SX_CORE_FUNC(sx_core_get_prio2tc);
        GET_ONE_SX_CORE_FUNC(sx_core_get_vlan_tagging);
        GET_ONE_SX_CORE_FUNC(sx_core_get_prio_tagging);
        GET_ONE_SX_CORE_FUNC(sx_core_get_vlan2ip);
        GET_ONE_SX_CORE_FUNC(sx_core_get_pvid);
        GET_ONE_SX_CORE_FUNC(sx_core_get_rp_rfid);
        GET_ONE_SX_CORE_FUNC(sx_core_get_send_to_port_as_data);
        GET_ONE_SX_CORE_FUNC(sx_core_post_send);
        GET_ONE_SX_CORE_FUNC(sx_core_get_local);
        GET_ONE_SX_CORE_FUNC(sx_core_get_rp_mode);
        GET_ONE_SX_CORE_FUNC(sx_register_interface);
        GET_ONE_SX_CORE_FUNC(sx_unregister_interface);
        GET_ONE_SX_CORE_FUNC(sx_detach_interface);
        GET_ONE_SX_CORE_FUNC(sx_core_cleanup_dynamic_data);
        GET_ONE_SX_CORE_FUNC(sx_core_skb_add_vlan);
        GET_ONE_SX_CORE_FUNC(sx_core_ptp_tx_control_to_data);

        if (!sx_core_if.sx_attach_interface) {
            sx_core_if.sx_attach_interface = __symbol_get("sx_attach_interface");
        }

        if (sx_core_if.sx_attach_interface) {
            dev = sx_core_if.sx_attach_interface(g_dev_ctx);
            if (dev) {
                g_dev_ctx = NULL;
            }
        }

        ASSIGN_ONE_FUNC_PTR(sx_core_flush_synd_by_context);
        ASSIGN_ONE_FUNC_PTR(translate_user_port_to_sysport);
        ASSIGN_ONE_FUNC_PTR(translate_sysport_to_user_port);
        ASSIGN_ONE_FUNC_PTR(sx_core_get_lag_oper_state);
        ASSIGN_ONE_FUNC_PTR(sx_cmd_set_op_tlv);
        ASSIGN_ONE_FUNC_PTR(sx_ACCESS_REG_PAOS);
        ASSIGN_ONE_FUNC_PTR(sx_ACCESS_REG_PPAD);
        ASSIGN_ONE_FUNC_PTR(sx_core_get_lag_mid);
        ASSIGN_ONE_FUNC_PTR(sx_core_get_rp_vlan);
        ASSIGN_ONE_FUNC_PTR(sx_core_add_synd);
        ASSIGN_ONE_FUNC_PTR(sx_core_remove_synd);
        ASSIGN_ONE_FUNC_PTR(sx_core_flush_synd_by_handler);
        ASSIGN_ONE_FUNC_PTR(sx_core_get_prio2tc);
        ASSIGN_ONE_FUNC_PTR(sx_core_get_vlan_tagging);
        ASSIGN_ONE_FUNC_PTR(sx_core_get_prio_tagging);
        ASSIGN_ONE_FUNC_PTR(sx_core_get_vlan2ip);
        ASSIGN_ONE_FUNC_PTR(sx_core_get_pvid);
        ASSIGN_ONE_FUNC_PTR(sx_core_get_rp_rfid);
        ASSIGN_ONE_FUNC_PTR(sx_core_get_send_to_port_as_data);
        ASSIGN_ONE_FUNC_PTR(sx_core_post_send);
        ASSIGN_ONE_FUNC_PTR(sx_core_get_local);
        ASSIGN_ONE_FUNC_PTR(sx_core_get_rp_mode);
        ASSIGN_ONE_FUNC_PTR(sx_register_interface);
        ASSIGN_ONE_FUNC_PTR(sx_unregister_interface);
        ASSIGN_ONE_FUNC_PTR(sx_detach_interface);
        ASSIGN_ONE_FUNC_PTR(sx_core_cleanup_dynamic_data);
        ASSIGN_ONE_FUNC_PTR(sx_core_skb_add_vlan);
        ASSIGN_ONE_FUNC_PTR(sx_core_ptp_tx_control_to_data);

        if (dev) {
            g_sx_dev = dev;
        }

        write_lock_irqsave(&sx_core_if.access_lock, flags);
        sx_core_if.init_done = 1;
        write_unlock_irqrestore(&sx_core_if.access_lock, flags);

        /* cleanup is called in attach because attach called after device reset */
        if (sx_core_if.sx_core_cleanup_dynamic_data) {
            sx_core_if.sx_core_cleanup_dynamic_data();
        }

        sx_netdev_attach_global_event_handler();
        attach_netdevs(dev);
    } else {
        read_lock_irqsave(&sx_core_if.access_lock, flags);
        if (sx_core_if.init_done == 0) {
            read_unlock_irqrestore(&sx_core_if.access_lock, flags);
            printk(KERN_INFO PFX "sx_core already detach\n");
            return len;
        }
        read_unlock_irqrestore(&sx_core_if.access_lock, flags);

        detach_netdevs();
        sx_netdev_unregister_global_event_handler();
        sx_psample_cleanup();
        dev = g_sx_dev;

        write_lock_irqsave(&sx_core_if.access_lock, flags);
        sx_core_if.init_done = 0;
        write_unlock_irqrestore(&sx_core_if.access_lock, flags);

        if (atomic_dec_and_test(&sx_core_if.refcount)) {
            complete(&sx_core_if.free);
        }
        wait_for_completion(&sx_core_if.free);

        EMPTY_ONE_FUNC_PTR(sx_core_flush_synd_by_context);
        EMPTY_ONE_FUNC_PTR(translate_user_port_to_sysport);
        EMPTY_ONE_FUNC_PTR(translate_sysport_to_user_port);
        EMPTY_ONE_FUNC_PTR(sx_core_get_lag_oper_state);
        EMPTY_ONE_FUNC_PTR(sx_cmd_set_op_tlv);
        EMPTY_ONE_FUNC_PTR(sx_ACCESS_REG_PAOS);
        EMPTY_ONE_FUNC_PTR(sx_ACCESS_REG_PPAD);
        EMPTY_ONE_FUNC_PTR(sx_core_get_lag_mid);
        EMPTY_ONE_FUNC_PTR(sx_core_get_rp_vlan);
        EMPTY_ONE_FUNC_PTR(sx_core_add_synd);
        EMPTY_ONE_FUNC_PTR(sx_core_remove_synd);
        EMPTY_ONE_FUNC_PTR(sx_core_flush_synd_by_handler);
        EMPTY_ONE_FUNC_PTR(sx_core_get_prio2tc);
        EMPTY_ONE_FUNC_PTR(sx_core_get_vlan_tagging);
        EMPTY_ONE_FUNC_PTR(sx_core_get_prio_tagging);
        EMPTY_ONE_FUNC_PTR(sx_core_get_vlan2ip);
        EMPTY_ONE_FUNC_PTR(sx_core_get_pvid);
        EMPTY_ONE_FUNC_PTR(sx_core_get_rp_rfid);
        EMPTY_ONE_FUNC_PTR(sx_core_get_send_to_port_as_data);
        EMPTY_ONE_FUNC_PTR(sx_core_post_send);
        EMPTY_ONE_FUNC_PTR(sx_core_get_local);
        EMPTY_ONE_FUNC_PTR(sx_core_get_rp_mode);
        EMPTY_ONE_FUNC_PTR(sx_register_interface);
        EMPTY_ONE_FUNC_PTR(sx_unregister_interface);
        EMPTY_ONE_FUNC_PTR(sx_attach_interface);
        EMPTY_ONE_FUNC_PTR(sx_core_cleanup_dynamic_data);
        EMPTY_ONE_FUNC_PTR(sx_core_skb_add_vlan);
        EMPTY_ONE_FUNC_PTR(sx_core_ptp_tx_control_to_data);

        if (g_sx_dev) {
            g_sx_dev = NULL;
        }

        if (sx_core_if.sx_detach_interface) {
            dev_ctx = sx_core_if.sx_detach_interface(&sx_netdev_interface, dev);
            if (dev_ctx) {
                g_dev_ctx = dev_ctx;
            }
            __symbol_put("sx_detach_interface");
            sx_core_if.sx_detach_interface = NULL;
        }

        PUT_ONE_SX_CORE_FUNC(sx_core_flush_synd_by_context);
        PUT_ONE_SX_CORE_FUNC(translate_user_port_to_sysport);
        PUT_ONE_SX_CORE_FUNC(translate_sysport_to_user_port);
        PUT_ONE_SX_CORE_FUNC(sx_core_get_lag_oper_state);
        PUT_ONE_SX_CORE_FUNC(sx_cmd_set_op_tlv);
        PUT_ONE_SX_CORE_FUNC(sx_ACCESS_REG_PAOS);
        PUT_ONE_SX_CORE_FUNC(sx_ACCESS_REG_PPAD);
        PUT_ONE_SX_CORE_FUNC(sx_core_get_lag_mid);
        PUT_ONE_SX_CORE_FUNC(sx_core_get_rp_vlan);
        PUT_ONE_SX_CORE_FUNC(sx_core_add_synd);
        PUT_ONE_SX_CORE_FUNC(sx_core_remove_synd);
        PUT_ONE_SX_CORE_FUNC(sx_core_flush_synd_by_handler);
        PUT_ONE_SX_CORE_FUNC(sx_core_get_prio2tc);
        PUT_ONE_SX_CORE_FUNC(sx_core_get_vlan_tagging);
        PUT_ONE_SX_CORE_FUNC(sx_core_get_prio_tagging);
        PUT_ONE_SX_CORE_FUNC(sx_core_get_vlan2ip);
        PUT_ONE_SX_CORE_FUNC(sx_core_get_pvid);
        PUT_ONE_SX_CORE_FUNC(sx_core_get_rp_rfid);
        PUT_ONE_SX_CORE_FUNC(sx_core_get_send_to_port_as_data);
        PUT_ONE_SX_CORE_FUNC(sx_core_post_send);
        PUT_ONE_SX_CORE_FUNC(sx_core_get_local);
        PUT_ONE_SX_CORE_FUNC(sx_core_get_rp_mode);
        PUT_ONE_SX_CORE_FUNC(sx_register_interface);
        PUT_ONE_SX_CORE_FUNC(sx_unregister_interface);
        PUT_ONE_SX_CORE_FUNC(sx_attach_interface);
        PUT_ONE_SX_CORE_FUNC(sx_core_cleanup_dynamic_data);
        PUT_ONE_SX_CORE_FUNC(sx_core_skb_add_vlan);
        PUT_ONE_SX_CORE_FUNC(sx_core_ptp_tx_control_to_data);
    }

    return len;
}

static int __init sx_netdev_init(void)
{
    int ret;

    printk(KERN_INFO PFX "sx_netdev_init\n");

    netdev_wq = create_singlethread_workqueue("sx_link");
    if (!netdev_wq) {
        printk(KERN_ERR PFX "Failed to create wq sx_link. \n");
        return -ENOMEM;
    }

    memset(&sx_core_if, 0, sizeof(sx_core_if));
    sx_netdev_init_sx_core_interface();

    if (!sx_core_if.sx_register_interface) {
        ret = -ENXIO;
        goto fail_on_sx_register_interface;
    }

    ret = sx_core_if.sx_register_interface(&sx_netdev_interface);
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
        goto fail_on_sysfs_create_file;
    }

    ret = sysfs_create_file(&(THIS_MODULE->mkobj.kobj), &(skip_netdev_attr.attr));
    if (ret) {
        goto fail_on_sysfs_create_file;
    }

    return 0;

fail_on_sysfs_create_file:
    sx_bridge_rtnl_link_unregister();

fail_on_bridge_rtnl_link_register:
    sx_netdev_rtnl_link_unregister();

fail_on_netdev_rtnl_link_register:
    sx_netdev_unregister_global_event_handler();

fail_on_register_global_event_handler:
    if (sx_core_if.sx_unregister_interface) {
        sx_core_if.sx_unregister_interface(&sx_netdev_interface);
    }

fail_on_sx_register_interface:
    sx_netdev_deinit_sx_core_interface();

    return ret;
}

static void __exit sx_netdev_cleanup(void)
{
    printk(KERN_INFO PFX "sx_netdev_cleanup \n");
    sysfs_remove_file(&(THIS_MODULE->mkobj.kobj), &(skip_netdev_attr.attr));
    sysfs_remove_file(&(THIS_MODULE->mkobj.kobj), &(bind_sx_core_attr.attr));
    sx_bridge_rtnl_link_unregister();
    sx_netdev_rtnl_link_unregister();
    sx_netdev_unregister_global_event_handler();
    sx_psample_cleanup();

    if (netdev_wq) {
        destroy_workqueue(netdev_wq);
    }

    if (sx_core_if.sx_unregister_interface) {
        sx_core_if.sx_unregister_interface(&sx_netdev_interface);
    } else {
        sx_netdev_remove_one(g_sx_dev, g_netdev_resources);
    }

    if (g_dev_ctx) {
        kfree(g_dev_ctx);
    }

    sx_netdev_deinit_sx_core_interface();
}

module_init(sx_netdev_init);
module_exit(sx_netdev_cleanup);
