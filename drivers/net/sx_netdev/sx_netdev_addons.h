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
    struct ethtool_stats     estats = { 0, };
    unsigned int             start;
    int                      count;
    u64                     *hw_stats;

    do {
        start = u64_stats_fetch_begin(&priv->syncp);
        memcpy(&sx_stats, &priv->stats64,
               sizeof(struct rtnl_link_stats64));
    } while (u64_stats_fetch_retry(&priv->syncp, start));

    count = port_get_sset_count(dev, ETH_SS_STATS);
    if (count <= 0) {
        goto err_out;
    }

    hw_stats = kcalloc(count, sizeof(u64), GFP_ATOMIC);
    if (!hw_stats) {
        goto err_out;
    }

    estats.n_stats = count;
    port_get_ethtool_stats(dev, &estats, hw_stats);

    stats->rx_packets = hw_stats[1] + hw_stats[2] + hw_stats[3];
    stats->rx_bytes = hw_stats[0];
    stats->multicast = hw_stats[3];
    stats->rx_errors = hw_stats[12] + hw_stats[13] + hw_stats[25] + sx_stats.rx_errors;
    stats->rx_dropped = hw_stats[8] + hw_stats[9] + hw_stats[10] + hw_stats[11] + sx_stats.rx_dropped;
    stats->rx_frame_errors = sx_stats.rx_frame_errors;

    stats->tx_packets = hw_stats[5] + hw_stats[6] + hw_stats[7];
    stats->tx_bytes = hw_stats[4];
    stats->tx_errors = hw_stats[18] + sx_stats.tx_fifo_errors;
    stats->tx_dropped = hw_stats[17] + hw_stats[19] + hw_stats[20] + sx_stats.tx_dropped;

    kfree(hw_stats);
err_out:
    return;
}

#endif /* defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) */

#endif /* __SX_NETDEV_ADDONS_H__ */
