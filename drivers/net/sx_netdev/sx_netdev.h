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

#ifndef SX_NETDEV_H
#define SX_NETDEV_H

#include <linux/workqueue.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/etherdevice.h>
#include <linux/kthread.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/netlink.h>
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0)) || defined(CONFIG_SX_RHEL_8_6)
#include <net/devlink.h>
#endif
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/net_tstamp.h>
#include <linux/if_vlan.h>
#include "sx_netdev_module_sysfs_eeprom.h"

#define DRV_NAME    "sx_netdev"
#define PFX         DRV_NAME ": "
#define DRV_VERSION "1.0"
#define DRV_RELDATE "Jan, 2012"

#define ISX_HDR_SIZE         16
#define MAX_JUMBO_FRAME_SIZE 10000
#define DEFAULT_FRAME_SIZE   9216
#define SX_INVALID_TRAP_ID   0xFFFF
#define SX_PORT_TO_ISX_LAG_ID(port) (port << 4)
#define SX_PACKET_DEFAULT_TC    5
#define TX_HEADER_RP_RIF_TO_FID (15 * 1024)
#define SX_VLAN_PRIO_MAX        7
#define MAX_PORT_NETDEV_NUM     2


static const char *net_port_vlan_type_str[] = {
    "GLOBAL",
    "PORT_VALID",
    "LAG_VALID",
    "VLAN_VALID",
};
static const int   net_port_vlan_type_str_len =
    sizeof(net_port_vlan_type_str) / sizeof(char *);
enum net_port_vlan_type {
    PORT_VLAN_TYPE_GLOBAL = 0,
    PORT_VLAN_TYPE_PORT   = 1,
    PORT_VLAN_TYPE_LAG    = 2,
    PORT_VLAN_TYPE_VLAN   = 3
};
#define NET_PORT_VLAN_TYPE_TO_STR(type)    \
    ((type < net_port_vlan_type_str_len) ? \
     net_port_vlan_type_str[type] : "Unknown type")

struct net_port_vlan_info {
    enum net_port_vlan_type info_type;
    u16                     synd;
    u16                     sysport;
    u16                     lag_id;
    u16                     vlan;
};

enum sx_net_kobject_type {
    SX_NET_KOBJECT_PORT        = 0,
    SX_NET_KOBJECT_MODULE      = 1,
    SX_NET_KOBJECT_MODULE_TEMP = 2,
    SX_NET_KOBJECT_MAX         = SX_NET_KOBJECT_MODULE_TEMP,
};

struct sx_net_priv {
    u8                               swid;
    struct net_port_vlan_info        trap_ids[NUM_OF_NET_DEV_TYPE][MAX_NUM_TRAPS_TO_REGISTER];
    u16                              num_of_traps[NUM_OF_NET_DEV_TYPE];
    struct sx_dev                   *dev;
    struct net_device_stats          stats;
    u64                              mac;
    unsigned long                    active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
    u16                              port;
    u16                              mid;
    int                              is_lag;
    int                              is_port_netdev;
    u32                              log_port;
    int                              is_oper_state_up;
    u8                               send_to_port_as_data_supported;
    int                              is_bridge;
    u16                              bridge_id; /* bridge id == fid */
    struct net_device              * netdev;
    struct delayed_work              pude_dwork; /* pude delayed work */
    struct workqueue_struct        * pude_wq;
    struct hwtstamp_config           hwtstamp_config;
    u8                               skip_tunnel;
    struct kobject                  *kobj[SX_NET_KOBJECT_MAX + 1];
    struct module_sysfs_eeprom_tree *eeprom_kobjs;
#if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0))
    struct u64_stats_sync    syncp;
    struct rtnl_link_stats64 stats64;
#endif
#if !defined(SX_DROP_MONITOR_DISABLED) && ((LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, \
                                                                                 0)) || defined(CONFIG_SX_RHEL_8_6))
    struct devlink_port devlink_port;
#endif
};

enum {
    PORT_TYPE_SINGLE = 0,
    PORT_TYPE_LAG    = 1,
    PORT_TYPE_NUM
};

struct sx_netdev_rsc {
    struct net_device *sx_netdevs[NUMBER_OF_SWIDS];
    struct mutex       rsc_lock; /* the resource's lock (for updates), for reading use RCU */
    u8                 allocated[NUMBER_OF_SWIDS];

    /* port_netdev is used by handlers that run in interrupt context.
     * any update to it must be:
     *    1. acquire the mutex (rsc_lock)
     *    2. assign a pointer with rcu_assign_pointer()
     * any read from it must be:
     *    1. under rcu_read_lock() context
     *    2. get the pointer with rcu_dereference()
     *        - OR -
     *    1. acquire the mutex (rsc_lock) and read the pointers with no restrictions.
     */
    struct net_device *port_netdev[PORT_TYPE_NUM][MAX_SYSPORT_NUM][MAX_PORT_NETDEV_NUM];
    u8                 port_allocated[PORT_TYPE_NUM][MAX_SYSPORT_NUM];
    u8                 in_attach_detach;
};

#define SX_VLAN_PRIO_MASK  0xe000         /* Priority Code Point */
#define SX_VLAN_PRIO_SHIFT 13

u64 sx_netdev_mac_to_u64(u8 *addr);
void sx_netdev_u64_to_mac(u8* addr, u64 mac);
int sx_netdev_register_device(struct net_device *netdev, int should_rtnl_lock,
                              int admin_state);
int sx_netdev_create_port_sysfs_nodes(struct net_device *netdev);
int sx_netdev_remove_port_sysfs_nodes(struct net_device *netdev);

/* Global core context */
extern struct net_device       *bridge_netdev_db[MAX_BRIDGE_NUM];
extern struct sx_netdev_rsc    *g_netdev_resources;
extern struct sx_dev           *g_sx_dev;
extern u8                       g_skip_tunnel;
extern struct workqueue_struct *g_netdev_wq;

enum {
    IFLA_SX_BRIDGE_UNSPEC,
    IFLA_SX_BRIDGE_ID,
    __IFLA_SX_BRIDGE_MAX
};
#define IFLA_SX_BRIDGE_MAX (__IFLA_SX_BRIDGE_MAX - 1)

struct sx_core_interface {
    rwlock_t          access_lock;
    atomic_t          refcount;
    u8                init_done;
    struct completion free;
};
extern struct sx_core_interface sx_core_if;

u8 sx_netdev_sx_core_if_get_reference(void);
void sx_netdev_sx_core_if_release_reference(void);

#define CALL_SX_CORE_FUNC_WITH_RET(func_name, ret, ...)          \
    if (sx_netdev_sx_core_if_get_reference()) {                  \
        ret = func_name(__VA_ARGS__);                            \
        sx_netdev_sx_core_if_release_reference();                \
    } else {                                                     \
        printk(KERN_INFO PFX "sx_core_if is not initialized\n"); \
        ret = -ENXIO;                                            \
    }

#define CALL_SX_CORE_FUNC_WITHOUT_RET(func_name, ...)            \
    if (sx_netdev_sx_core_if_get_reference()) {                  \
        func_name(__VA_ARGS__);                                  \
        sx_netdev_sx_core_if_release_reference();                \
    } else {                                                     \
        printk(KERN_INFO PFX "sx_core_if is not initialized\n"); \
    }

int sx_netdev_rtnl_link_register(void);
void sx_netdev_rtnl_link_unregister(void);
int sx_bridge_rtnl_link_register(void);
void sx_bridge_rtnl_link_unregister(void);
int sx_netdev_get_net_device_by_kobj(struct kobject          *kobj,
                                     struct net_device      **dev,
                                     enum sx_net_kobject_type kobj_type);
int sx_netdev_devlink_port_register(struct net_device *netdev);
void sx_netdev_devlink_port_unregister(struct net_device *netdev);

#endif /* SX_NETDEV_H */
