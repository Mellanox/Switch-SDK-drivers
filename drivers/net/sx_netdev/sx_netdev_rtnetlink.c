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

#include <linux/module.h>
#include <linux/init.h>
#include <linux/errno.h>
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
#include <linux/vmalloc.h>
#include <linux/if_ether.h>
#include <linux/if_vlan.h>
#include <linux/rtnetlink.h>

#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/kernel_user.h>
#include "sx_netdev.h"
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/auto_registers/reg.h>

static void sx_netdev_setup(struct net_device *dev)
{
    struct sx_net_priv *net_priv = netdev_priv(dev);

    printk(KERN_INFO PFX "%s: called\n", __func__);

    memset(net_priv, 0, sizeof(*net_priv));
    ether_setup(dev);
    dev->hard_header_len = ETH_HLEN + ISX_HDR_SIZE;
    net_priv->netdev = dev;
    INIT_DELAYED_WORK(&net_priv->pude_dwork, sx_netdev_dwork_func);
}

static int sx_netdev_validate(struct nlattr *tb[], struct nlattr *data[])
{
    __u32    id;
    int      is_lag;
    int      err = 0;
    uint16_t lag_max = 0, lag_member_max = 0;

    printk(KERN_INFO PFX "%s: called\n", __func__);

    if (tb[IFLA_ADDRESS]) {
        if (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN) {
            pr_debug("invalid link address (not ethernet)\n");
            return -EINVAL;
        }

        if (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS]))) {
            pr_debug("invalid all zero ethernet address\n");
            return -EADDRNOTAVAIL;
        }
    }

    if (!data) {
        printk(KERN_INFO PFX "%s: Data invalid\n", __func__);
        return -EINVAL;
    }

    if (!data[IFLA_SX_NETDEV_SWID]) {
        printk(KERN_INFO PFX "%s: SWID doesn't exists\n", __func__);
        return -EINVAL;
    }

    id = nla_get_u32(data[IFLA_SX_NETDEV_SWID]);
    if (id >= NUMBER_OF_SWIDS) {
        printk(KERN_INFO PFX "%s: SWID is out of range - %d\n", __func__, id);
        return -ERANGE;
    }

    if (data[IFLA_SX_NETDEV_PORT]) {
        if (sx_netdev_sx_core_if_get_reference()) {
            if (sx_core_if.translate_user_port_to_sysport && g_sx_dev) {
                id = sx_core_if.translate_user_port_to_sysport(g_sx_dev, nla_get_u32(
                                                                   data[IFLA_SX_NETDEV_PORT]), &is_lag);
            } else {
                printk(KERN_INFO PFX "%s: sx_core_if.translate_user_port_to_sysport or g_sx_dev is NULL\n", __func__);
                sx_netdev_sx_core_if_release_reference();
                return -ENXIO;
            }
            sx_netdev_sx_core_if_release_reference();
        } else {
            printk(KERN_INFO PFX "sx_core_if is not initialized\n");
            return -ENXIO;
        }
        if (id >= MAX_SYSPORT_NUM) {
            printk(KERN_INFO PFX "%s: PORT is out of range - %d\n", __func__, id);
            return -ERANGE;
        }
        if (is_lag) {
            CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_lag_max, err, g_sx_dev, &lag_max, &lag_member_max);
            if (err) {
                printk(KERN_ERR PFX "Failed to get max number of LAGs. err = %d.\n", err);
                return err;
            }

            if (id >= lag_max) {
                printk(KERN_INFO PFX "%s: LAG is out of range - %d\n", __func__, id);
                return -ERANGE;
            }
        }
    }

    printk(KERN_INFO PFX "%s: exit\n", __func__);
    return 0;
}

static size_t sx_netdev_get_size(const struct net_device *dev)
{
    return nla_total_size(sizeof(__u32)) +  /* IFLA_SX_NETDEV_SWID */
           nla_total_size(sizeof(__u32)) + /* IFLA_SX_NETDEV_PORT */
           0;
}

static int sx_netdev_fill_info(struct sk_buff *skb, const struct net_device *dev)
{
    struct sx_net_priv *net_priv = netdev_priv(dev);

    if (nla_put_u32(skb, IFLA_SX_NETDEV_SWID, net_priv->swid)) {
        goto nla_put_failure;
    }

    if (nla_put_u32(skb, IFLA_SX_NETDEV_PORT, net_priv->log_port)) {
        goto nla_put_failure;
    }

    return 0;

nla_put_failure:
    return -EMSGSIZE;
}

static int sx_netdev_oper_state_get(struct sx_dev *dev, u32 log_port, u8 *is_oper_state_up)
{
    int                       err = 0;
    struct ku_access_paos_reg paos_reg_data;

    memset(&paos_reg_data, 0, sizeof(struct ku_access_paos_reg));

    if (SX_PORT_TYPE_ID_GET(log_port) == SX_PORT_TYPE_LAG) {
        if (sx_netdev_sx_core_if_get_reference()) {
            if (!sx_core_if.sx_core_get_lag_oper_state || !dev) {
                printk(KERN_INFO PFX "sx_core_if.sx_core_get_lag_oper_state or dev is NULL\n");
                err = -ENXIO;
            } else {
                err = sx_core_if.sx_core_get_lag_oper_state(dev, SX_PORT_LAG_ID_GET(log_port), is_oper_state_up);
            }
            sx_netdev_sx_core_if_release_reference();
        } else {
            printk(KERN_INFO PFX "sx_core_if is not initialized\n");
            err = -ENXIO;
        }
        if (err) {
            printk(KERN_INFO PFX "%s: Unable to get lag [0x%x] oper state."
                   " err = %d\n", __func__, log_port, err);
            *is_oper_state_up = 0;
        }
        printk(KERN_INFO PFX "%s: LAG port state for 0x%x = %d\n", __func__,
               log_port, *is_oper_state_up);
    } else { /* the port is a system port */
             /* Query port state via PAOS register */
        CALL_SX_CORE_FUNC_WITHOUT_RET(sx_cmd_set_op_tlv, &paos_reg_data.op_tlv, MLXSW_PAOS_ID, EMAD_METHOD_QUERY);

        paos_reg_data.paos_reg.local_port = SX_PORT_PHY_ID_GET(log_port);
        paos_reg_data.paos_reg.admin_status = 0;
        paos_reg_data.paos_reg.oper_status = 0;
        paos_reg_data.paos_reg.ase = 0;
        paos_reg_data.paos_reg.ee = 0;
        paos_reg_data.paos_reg.e = 0;

        if (sx_netdev_sx_core_if_get_reference()) {
            if (!sx_core_if.sx_ACCESS_REG_PAOS || !dev) {
                printk(KERN_INFO PFX "sx_core_if.sx_ACCESS_REG_PAOS or dev is NULL\n");
                err = -ENXIO;
            } else {
                paos_reg_data.dev_id = dev->device_id;
                err = sx_core_if.sx_ACCESS_REG_PAOS(dev, &paos_reg_data);
            }
            sx_netdev_sx_core_if_release_reference();
        } else {
            printk(KERN_INFO PFX "sx_core_if is not initialized\n");
            err = -ENXIO;
        }
        if (err) {
            printk(KERN_INFO PFX "%s: Unable to get port state, port = 0x%x err = %d\n", __func__, log_port, err);
            paos_reg_data.paos_reg.oper_status = 0;
        }
        printk(KERN_INFO PFX "%s: Port state for 0x%x = %d\n", __func__, log_port, paos_reg_data.paos_reg.oper_status);
        *is_oper_state_up = (paos_reg_data.paos_reg.oper_status == PORT_OPER_STATUS_UP);
    }
    return err;
}

static int sx_netdev_port_mac_get(struct sx_dev *dev, u32 log_port, u64 *mac)
{
    int                       err = 0;
    struct ku_access_ppad_reg ppad_reg_data;
    u8                        dev_addr[ETH_ALEN];

    memset(&ppad_reg_data, 0, sizeof(struct ku_access_ppad_reg));
    memset(&dev_addr, 0, sizeof(dev_addr));

    /* Read MAC address */
    if (SX_PORT_TYPE_ID_GET(log_port) == SX_PORT_TYPE_LAG) {
        *mac = 0;
    } else { /* the port is a system port */
        CALL_SX_CORE_FUNC_WITHOUT_RET(sx_cmd_set_op_tlv, &ppad_reg_data.op_tlv, PPAD_REG_ID, EMAD_METHOD_QUERY);

        if (sx_netdev_sx_core_if_get_reference()) {
            if (!sx_core_if.sx_ACCESS_REG_PPAD || !dev) {
                printk(KERN_INFO PFX "sx_core_if.sx_ACCESS_REG_PPAD or dev is NULL\n");
                err = -ENXIO;
            } else {
                ppad_reg_data.dev_id = dev->device_id;
                ppad_reg_data.ppad_reg.single_base_mac = 1;
                ppad_reg_data.ppad_reg.local_port = SX_PORT_PHY_ID_GET(log_port);
                err = sx_core_if.sx_ACCESS_REG_PPAD(dev, &ppad_reg_data);
            }
            sx_netdev_sx_core_if_release_reference();
        } else {
            printk(KERN_INFO PFX "sx_core_if is not initialized\n");
            err = -ENXIO;
        }
        if (err) {
            printk(KERN_INFO PFX "%s: Unable to get port MAC address, err = %d\n", __func__, err);
            random_ether_addr(dev_addr);
        } else {
            memcpy(dev_addr, ppad_reg_data.ppad_reg.mac, ETH_ALEN);
        }
    }
    *mac = sx_netdev_mac_to_u64(dev_addr);
    return err;
}

static int sx_netdev_newlink(struct net *net, struct net_device *dev, struct nlattr *tb[], struct nlattr *data[])
{
    struct sx_net_priv *net_priv = netdev_priv(dev);
    int                 swid = 0;
    int                 err = 0;
    int                 i = 0;
    u32                 logical_port = 0;
    u8                  uc_type = 0;
    u8                  oper_state = 0;
    u16                 sys_port = 0;
    u64                 mac = 0;
    u8                  port_type = 0;

    printk(KERN_INFO PFX "%s: called\n", __func__);

    if (!data[IFLA_SX_NETDEV_SWID]) {
        return -EINVAL;
    }
    if (!data[IFLA_SX_NETDEV_PORT]) {
        return -EINVAL;
    }

    swid = nla_get_u32(data[IFLA_SX_NETDEV_SWID]);
    if (swid >= NUMBER_OF_SWIDS) {
        printk(KERN_INFO PFX "%s: SWID is out of range - %d\n", __func__, swid);
        return -EINVAL;
    }

    if ((swid != ROUTER_PORT_SWID) && !g_netdev_resources->sx_netdevs[swid]) {
        printk(KERN_INFO PFX "%s: SWID %d, doesn't exists\n", __func__, swid);
        return -EINVAL;
    }

    logical_port = nla_get_u32(data[IFLA_SX_NETDEV_PORT]);

    net_priv->swid = swid;
    net_priv->dev = g_sx_dev;
    if (!net_priv->dev) {
        printk(KERN_INFO PFX "g_sx_dev is NULL\n");
        return -ENXIO;
    }

    if (sx_netdev_sx_core_if_get_reference()) {
        if (!sx_core_if.translate_user_port_to_sysport || !g_sx_dev) {
            printk(KERN_INFO PFX "sx_core_if.translate_user_port_to_sysport or g_sx_dev is NULL\n");
            err = -ENXIO;
        } else {
            sys_port = sx_core_if.translate_user_port_to_sysport(g_sx_dev, logical_port, &net_priv->is_lag);
        }
        sx_netdev_sx_core_if_release_reference();
    } else {
        printk(KERN_INFO PFX "sx_core_if is not initialized\n");
        err = -ENXIO;
    }

    if (err) {
        return err;
    }
    net_priv->port = sys_port;
    net_priv->log_port = logical_port;
    net_priv->is_port_netdev = 1;
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_send_to_port_as_data,
                               err,
                               net_priv->dev,
                               &net_priv->send_to_port_as_data_supported,
                               1);
    if (err) {
        printk(KERN_ERR PFX  "sx_core_get_send_to_port_as_data failed, err: %d \n", err);
        return err;
    }

    /* mark as alloc in DB */
    port_type = net_priv->is_lag ? PORT_TYPE_LAG : PORT_TYPE_SINGLE;
    spin_lock(&g_netdev_resources->rsc_lock);
    if (g_netdev_resources->port_allocated[port_type][net_priv->port] == MAX_PORT_NETDEV_NUM) {
        spin_unlock(&g_netdev_resources->rsc_lock);
        printk(KERN_ERR PFX  "No more resources - Max Net Device for port %u was already"
               " allocated\n", sys_port);
        return -EEXIST;
    }
    g_netdev_resources->port_allocated[port_type][net_priv->port]++;
    spin_unlock(&g_netdev_resources->rsc_lock);

    /* Get MAC address */
    err = sx_netdev_port_mac_get(net_priv->dev, logical_port, &mac);
    if (err) {
        printk(KERN_INFO PFX "%s: Unable to get mac, port = %d,"
               " is_lag = %d, err = %d\n", __func__, net_priv->port, net_priv->is_lag, err);
        mac = 0;
    }
    net_priv->mac = mac;

    net_priv->skip_tunnel = g_skip_tunnel;

    printk(KERN_INFO PFX "%s: Newly device %s log port 0x%x MAC address = %llx\n",
           __func__,
           dev->name,
           logical_port,
           net_priv->mac);

    /* Init trap DB */
    for (uc_type = USER_CHANNEL_L3_NETDEV; uc_type < NUM_OF_NET_DEV_TYPE; uc_type++) {
        for (i = 0; i < MAX_NUM_TRAPS_TO_REGISTER; i++) {
            net_priv->trap_ids[uc_type][i].synd = SX_INVALID_TRAP_ID;
        }
        net_priv->num_of_traps[uc_type] = 0;
    }

    /* Get LAG mid */
    if (net_priv->is_lag) {
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_lag_mid, err, net_priv->dev, net_priv->port, &(net_priv->mid));
        if (err) {
            printk(KERN_INFO PFX "%s: sx_core_get_lag_mid() failed error - %d\n", __func__, err);
            net_priv->mid = net_priv->port + 0x100;
        }
    }

    /* Register device */
    err = sx_netdev_register_device(dev, 0, 0);
    if (err) {
        printk(KERN_INFO PFX "%s: sx_netdev_register_device() failed error - %d\n", __func__, err);
        spin_lock(&g_netdev_resources->rsc_lock);
        g_netdev_resources->port_allocated[port_type][net_priv->port]--;
        spin_unlock(&g_netdev_resources->rsc_lock);
        return -ENXIO;
    }

    /* Add netdev to resources db */
    port_type = net_priv->is_lag ? PORT_TYPE_LAG : PORT_TYPE_SINGLE;
    for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
        if (g_netdev_resources->port_netdev[port_type][net_priv->port][i] == NULL) {
            g_netdev_resources->port_netdev[port_type][net_priv->port][i] = dev;
            break;
        }
    }

    /* Get operational state */
    err = sx_netdev_oper_state_get(net_priv->dev, logical_port, &oper_state);
    if (err) {
        printk(KERN_INFO PFX "%s: Unable to get port state, port = %d,"
               " is_lag = %d, err = %d\n", __func__, net_priv->port, net_priv->is_lag, err);
        oper_state = 0;
    }
    net_priv->is_oper_state_up = oper_state;

    printk(KERN_INFO PFX "%s: exit\n", __func__);

    return 0;
}

static void sx_netdev_dellink(struct net_device *dev, struct list_head *head)
{
    unsigned long       flags;
    struct sx_net_priv *net_priv = netdev_priv(dev);
    u8                  port_type = 0, i = 0;

    printk(KERN_INFO PFX "%s: called for %s\n", __func__, dev->name);

    port_type = net_priv->is_lag ? PORT_TYPE_LAG : PORT_TYPE_SINGLE;

    spin_lock_irqsave(&g_netdev_resources->rsc_lock, flags);
    for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
        if (g_netdev_resources->port_netdev[port_type][net_priv->port][i] == dev) {
            g_netdev_resources->port_netdev[port_type][net_priv->port][i] = NULL;
            break;
        }
    }
    g_netdev_resources->port_allocated[port_type][net_priv->port]--;
    spin_unlock_irqrestore(&g_netdev_resources->rsc_lock, flags);

    netif_tx_disable(dev);
    netif_carrier_off(dev);

    CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_flush_synd_by_context, dev);

    unregister_netdevice_queue(dev, head);

    printk(KERN_INFO PFX "%s: exit\n", __func__);
}


static const struct nla_policy                 sx_netdev_policy[IFLA_SX_NETDEV_MAX + 1] = {
    [IFLA_SX_NETDEV_SWID] = { .type = NLA_U32 },
    [IFLA_SX_NETDEV_PORT] = { .type = NLA_U32 },
};
static struct rtnl_link_ops sx_netdev_link_ops __read_mostly = {
    .kind = "sx_netdev",
    .maxtype = IFLA_SX_NETDEV_MAX,
    .policy = sx_netdev_policy,
    .priv_size = sizeof(struct sx_net_priv),
    .setup = sx_netdev_setup,
    .validate = sx_netdev_validate,
    .newlink = sx_netdev_newlink,
    .dellink = sx_netdev_dellink,
    .get_size = sx_netdev_get_size,
    .fill_info = sx_netdev_fill_info
};

int sx_netdev_rtnl_link_register()
{
    return rtnl_link_register(&sx_netdev_link_ops);
}

void sx_netdev_rtnl_link_unregister()
{
    rtnl_link_unregister(&sx_netdev_link_ops);
}
