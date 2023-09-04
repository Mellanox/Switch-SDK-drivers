/*
 * Copyright © 2021-2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#ifndef __SX_NETDEV_ADDONS_H__
#define __SX_NETDEV_ADDONS_H__

#if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0))

#include "sx_netdev.h"
#include "linux/port.h"

static void sx_get_drvinfo(struct net_device *bond_dev, struct ethtool_drvinfo *drvinfo)
{
    strlcpy(drvinfo->driver, "sx_netdev", sizeof(drvinfo->driver));
    strlcpy(drvinfo->version, DRV_VERSION, sizeof(drvinfo->version));
}

static int sx_get_ts_info(struct net_device *dev, struct ethtool_ts_info *info);

static const struct ethtool_ops sx_cl_ethtool_ops = {
    #if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    .cap_link_lanes_supported = true,
    #endif
    .get_link_ksettings = port_get_link_settings,
    .set_link_ksettings = port_set_link_settings,
    .get_link = ethtool_op_get_link,
    .get_strings = port_get_strings,
    .get_ethtool_stats = port_get_ethtool_stats,
    .get_sset_count = port_get_sset_count,
    .set_phys_id = port_set_phys_id,
    .get_drvinfo = sx_get_drvinfo,
    .get_module_info = port_get_module_info,
    .get_module_eeprom = port_get_module_eeprom,
    .get_fecparam = port_get_fecparam,
    .set_fecparam = port_set_fecparam,
    .get_ts_info = sx_get_ts_info,
};

void sx_get_stats64(struct net_device *dev, struct rtnl_link_stats64 *stats)
{
    struct sx_net_priv      *priv = netdev_priv(dev);
    struct rtnl_link_stats64 sx_stats;
    unsigned int             start;

    do {
        start = u64_stats_fetch_begin(&priv->syncp);
        memcpy(&sx_stats, &priv->stats64,
               sizeof(struct rtnl_link_stats64));
    } while (u64_stats_fetch_retry(&priv->syncp, start));

    port_augment_dev_ethtool_stats(dev, &sx_stats, stats);
}

#endif /* defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) */

#endif /* __SX_NETDEV_ADDONS_H__ */
