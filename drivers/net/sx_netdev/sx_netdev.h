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
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/net_tstamp.h>

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
    PORT_VLAN_TYPE_PORT = 1,
    PORT_VLAN_TYPE_LAG = 2,
    PORT_VLAN_TYPE_VLAN = 3
};
struct net_port_vlan_info {
    enum net_port_vlan_type info_type;
    u16                     synd;
    u16                     sysport;
    u16                     lag_id;
    u16                     vlan;
};
struct sx_net_priv {
    u8                        swid;
    struct net_port_vlan_info trap_ids[NUM_OF_NET_DEV_TYPE][MAX_NUM_TRAPS_TO_REGISTER];
    u16                       num_of_traps[NUM_OF_NET_DEV_TYPE];
    struct sx_dev            *dev;
    struct net_device_stats   stats;
    u64                       mac;
    unsigned long             active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
    u16                       port;
    u16                       mid;
    int                       is_lag;
    int                       is_port_netdev;
    u32                       log_port;
    int                       is_oper_state_up;
    u8                        send_to_port_as_data_supported;
    int                       is_bridge;
    u16                       bridge_id;   /* bridge id == fid */
    struct net_device       * netdev;
    struct delayed_work       pude_dwork;   /* pude delayed work */
    struct workqueue_struct * pude_wq;
    struct hwtstamp_config    hwtstamp_config;
    u8                        skip_tunnel;
};

enum {
    PORT_TYPE_SINGLE = 0,
    PORT_TYPE_LAG = 1,
    PORT_TYPE_NUM
};

struct sx_netdev_rsc {
    struct net_device *sx_netdevs[NUMBER_OF_SWIDS];
    spinlock_t         rsc_lock; /* the resource's lock */
    u8                 allocated[NUMBER_OF_SWIDS];
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

/* Global core context */
extern struct net_device    *bridge_netdev_db[MAX_BRIDGE_NUM];
extern struct sx_netdev_rsc *g_netdev_resources;
extern struct sx_dev        *g_sx_dev;
extern u8                    g_skip_tunnel;

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
    int               (*sx_core_flush_synd_by_context)(void * context);
    u16               (*translate_user_port_to_sysport)(struct sx_dev *dev, u32 log_port, int* is_lag);
    u32               (*translate_sysport_to_user_port)(struct sx_dev *dev, u16 port, u8 is_lag);
    int               (*sx_core_get_lag_oper_state)(struct sx_dev *dev, u16 lag_id, u8 *oper_state_p);
    void              (*sx_cmd_set_op_tlv)(struct ku_operation_tlv *op_tlv, u32 reg_id, u8 method);
    int               (*sx_ACCESS_REG_PAOS)(struct sx_dev *dev, struct ku_access_paos_reg *reg_data);
    int               (*sx_ACCESS_REG_PPAD)(struct sx_dev *dev, struct ku_access_ppad_reg *reg_data);
    int               (*sx_core_get_lag_mid)(struct sx_dev *dev, u16 lag_id, u16 *mid);
    int               (*sx_core_get_rp_vlan)(struct sx_dev *dev, struct completion_info *comp_info, uint16_t *vlan_id);
    int               (*sx_core_add_synd)(u8                          swid,
                                          u16                         hw_synd,
                                          enum l2_type                type,
                                          pid_t                       caller_pid,
                                          u8                          is_default,
                                          union ku_filter_critireas   crit,
                                          cq_handler                  handler,
                                          void                       *context,
                                          check_dup_e                 check_dup,
                                          struct sx_dev              *sx_dev,
                                          struct ku_port_vlan_params *port_vlan,
                                          u8                          is_register);
    int (*sx_core_remove_synd)(u8                          swid,
                               u16                         hw_synd,
                               enum l2_type                type,
                               u8                          is_default,
                               union ku_filter_critireas   critireas,
                               void                       *context,
                               struct sx_dev              *sx_dev,
                               cq_handler                  handler,
                               struct ku_port_vlan_params *port_vlan,
                               u8                          is_register);
    int (*sx_core_flush_synd_by_handler)(cq_handler handler);
    int (*sx_core_get_prio2tc)(struct sx_dev *dev, uint16_t port_lag_id, uint8_t is_lag, uint8_t pcp, uint8_t *tc);
    int (*sx_core_get_vlan_tagging)(struct sx_dev *dev,
                                    uint16_t       port_lag_id,
                                    uint8_t        is_lag,
                                    uint16_t       vlan,
                                    uint8_t       *is_vlan_tagged);
    int (*sx_core_get_prio_tagging)(struct sx_dev *dev,
                                    uint16_t       port_lag_id,
                                    uint8_t        is_lag,
                                    uint8_t       *is_port_prio_tagged);
    int (*sx_core_get_vlan2ip)(struct sx_dev *dev, uint16_t vid, uint32_t *ip_addr);
    int (*sx_core_get_pvid)(struct sx_dev *dev,
                            uint16_t       sysport_lag_id,
                            uint8_t        is_lag,
                            uint16_t      *pvid);
    int (*sx_core_get_rp_rfid)(struct sx_dev *dev, uint16_t port_lag_id,
                               uint8_t is_lag, uint16_t vlan_id, uint16_t *rfid);
    int            (*sx_core_get_send_to_port_as_data)(struct sx_dev *dev, u8* send_to_port_as_data, u8 send_default);
    int            (*sx_core_post_send)(struct sx_dev *dev, struct sk_buff *skb, struct isx_meta *meta);
    int            (*sx_register_interface)(struct sx_interface *intf);
    void           (*sx_unregister_interface)(struct sx_interface *intf);
    void           (*sx_core_cleanup_dynamic_data)(void);
    int            (*sx_core_get_local)(struct sx_dev *dev, uint16_t lag_id, uint8_t lag_subport, uint16_t *local_p);
    struct sx_dev* (*sx_attach_interface)(void *dev_ctx);
    void         * (*sx_detach_interface)(struct sx_interface *intf, struct sx_dev *dev);
    int            (*sx_core_get_ptp_state)(struct sx_dev *dev, uint8_t *is_ptp_enable);
    int            (*sx_core_get_ptp_clock_index)(struct sx_dev *dev, uint8_t *ptp_clock_index_p);
    int            (*sx_core_ptp_tx_handler)(struct sx_dev *dev, struct sk_buff *skb, u16 sysport_lag_id, u8 is_lag);
    int            (*sx_core_get_lag_max)(struct sx_dev *dev, uint16_t *lags, uint16_t *pors_per_lag);
    int            (*sx_core_get_rp_mode)(struct sx_dev *dev, u8 is_lag, u16 sysport_lag_id, u16 vlan_id, u8 *is_rp);
    int            (*sx_core_skb_add_vlan)(struct sk_buff **untagged_skb, uint16_t vid, uint16_t pcp);
    int            (*sx_core_ptp_tx_control_to_data)(struct sx_dev   *dev,
                                                     struct sk_buff **orig_skb,
                                                     struct isx_meta *meta,
                                                     u16              port,
                                                     u8               is_lag,
                                                     u8              *is_tagged,
                                                     u8               hw_ts_required);
};
extern struct sx_core_interface sx_core_if;

u8 sx_netdev_sx_core_if_get_reference(void);
void sx_netdev_sx_core_if_release_reference(void);

#define CALL_SX_CORE_FUNC_WITH_RET(func_name, ret, ...)                 \
    if (sx_netdev_sx_core_if_get_reference()) {                         \
        if (sx_core_if.func_name) {                                     \
            ret = sx_core_if.func_name(__VA_ARGS__);                    \
        } else {                                                        \
            printk(KERN_INFO PFX "sx_core_if."#func_name " is NULL\n"); \
            ret = -ENXIO;                                               \
        }                                                               \
        sx_netdev_sx_core_if_release_reference();                       \
    } else {                                                            \
        printk(KERN_INFO PFX "sx_core_if is not initialized\n");        \
        ret = -ENXIO;                                                   \
    }

#define CALL_SX_CORE_FUNC_WITHOUT_RET(func_name, ...)                   \
    if (sx_netdev_sx_core_if_get_reference()) {                         \
        if (sx_core_if.func_name) {                                     \
            sx_core_if.func_name(__VA_ARGS__);                          \
        } else {                                                        \
            printk(KERN_INFO PFX "sx_core_if."#func_name " is NULL\n"); \
        }                                                               \
        sx_netdev_sx_core_if_release_reference();                       \
    } else {                                                            \
        printk(KERN_INFO PFX "sx_core_if is not initialized\n");        \
    }

int sx_netdev_rtnl_link_register(void);
void sx_netdev_rtnl_link_unregister(void);
int sx_bridge_rtnl_link_register(void);
void sx_bridge_rtnl_link_unregister(void);
void sx_netdev_dwork_func(struct work_struct *pude_dwork);

#endif /* SX_NETDEV_H */
