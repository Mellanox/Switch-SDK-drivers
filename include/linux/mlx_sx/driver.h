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

#ifndef SX_DRIVER_H
#define SX_DRIVER_H

#include <linux/device.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/kernel_user.h>

struct sx_dev;
enum sx_dev_event {
    SX_DEV_EVENT_CATASTROPHIC_ERROR,
    SX_DEV_EVENT_IB_SWID_UP,
    SX_DEV_EVENT_ETH_SWID_UP,
    SX_DEV_EVENT_IB_SWID_DOWN,
    SX_DEV_EVENT_ETH_SWID_DOWN,
    SX_DEV_EVENT_PORT_UP,
    SX_DEV_EVENT_PORT_DOWN,
    SX_DEV_EVENT_PORT_REINIT,
    SX_DEV_EVENT_TYPE_INTERNAL_ERROR,
    SX_DEV_EVENT_TYPE_TCA_INIT,
    SX_DEV_EVENT_MAD_IFC_ENABLE,
    SX_DEV_EVENT_ADD_SYND_NETDEV,
    SX_DEV_EVENT_REMOVE_SYND_NETDEV,
    SX_DEV_EVENT_ADD_SYND_IPOIB,
    SX_DEV_EVENT_REMOVE_SYND_IPOIB,
    SX_DEV_EVENT_DEBUG_NETDEV,
    SX_DEV_EVENT_NODE_DESC_UPDATE,
    SX_DEV_EVENT_ADD_SYND_L2_NETDEV,
    SX_DEV_EVENT_REMOVE_SYND_L2_NETDEV,
    SX_DEV_EVENT_ADD_SYND_PHY_NETDEV,
    SX_DEV_EVENT_REMOVE_SYND_PHY_NETDEV,
    SX_DEV_EVENT_TYPE_RPA_INIT,
    SX_DEV_EVENT_LAG_OPER_STATE_UPDATE,
    SX_DEV_EVENT_OFFLOAD_MARK_SET,
    SX_DEV_EVENT_GET_NETDEV_TRAP_INFO,
    SX_DEV_EVENT_ADD_SYND_PSAMPLE,
    SX_DEV_EVENT_REMOVE_SYND_PSAMPLE,
    SX_DEV_EVENT_UPDATE_SAMPLE_RATE
};

#define SX_PAGE_SIZE  4096
#define SX_PAGE_SHIFT 12

#define ETHTYPE_ARP               0x0806
#define ETHTYPE_VLAN              0x8100
#define ETHTYPE_EMAD              0x8932
#define ETHTYPE_DONT_CARE_VALUE   0
#define QPN_DONT_CARE_VALUE       0xffffffff
#define QPN_MULTICAST_VALUE       0xffffff
#define DMAC_DONT_CARE_VALUE      0
#define TID_DONT_CARE_VALUE       0
#define SYSPORT_DONT_CARE_VALUE   0
#define FWD_BY_FDB_TRAP_ID        0x01
#define SWITCHIB_QP0_TRAP_ID      0xf0
#define SWITCHIB_QP1_TRAP_ID      0xf1
#define SWITCHIB_OTHER_QP_TRAP_ID 0xf2
#define PACKET_SAMPLE_TRAP_ID     0x38
#define ROUTER_QP0_TRAP_ID        0x5e
#define FDB_TRAP_ID               0x06
#define ARP_REQUEST_TRAP_ID       0x50
#define ARP_RESPONSE_TRAP_ID      0x51
#define MIN_IPTRAP_TRAP_ID        0x1C0 /* TODO define which one will be used */

typedef enum l3_synd_type {
    L3_SYND_TYPE_GLOBAL = 0,
    L3_SYND_TYPE_PORT = 1,
    L3_SYND_TYPE_LAG = 2,
    L3_SYND_TYPE_VLAN = 3,
} l3_synd_type_e;
union sx_event_data {
    struct {
        int swid;
        u16 dev_id;
    } ib_swid_change;
    struct {
        int swid;
        int synd;
        u64 mac;
    } eth_swid_up;
    struct {
        int               swid;
        int               hw_synd;
        enum l3_synd_type type;
        u16               port;
        u16               vlan;
        u8                is_register;
    } eth_l3_synd;
    struct {
        int swid;
        int hw_synd;
        u8  is_register;
    } ipoib_synd;
    struct {
        int swid;
    } eth_swid_down;
    struct {
        int num_of_ib_swids;
        u8  swid[NUMBER_OF_SWIDS];
        u16 max_pkey;
    } tca_init;
    struct {
        uint8_t swid;
        uint8_t NodeDescription[64];
    } node_desc_update;
    struct {
        u16 lag_id;
        u8  oper_state;
    } lag_oper_state_set;
    struct {
        u8 offload_mark_set_en;
    } offload_mark_set;
    struct {
        struct ku_port_vlan_params port_vlan_params[NUM_OF_NET_DEV_TYPE][MAX_NUM_TRAPS_TO_REGISTER];
        uint16_t                   trap_ids[NUM_OF_NET_DEV_TYPE][MAX_NUM_TRAPS_TO_REGISTER];
        uint16_t                   num_of_traps[NUM_OF_NET_DEV_TYPE];
    } netdev_trap_info;
    struct {
        uint8_t                    swid;
        int                        hw_synd;
        u8                         is_register;
        struct ku_port_vlan_params port_vlan_params;
        struct ku_psample_params   psample_info;
    } psample_synd;
    struct {
        uint8_t  local_port;
        uint32_t sample_rate;
    } psample_port_sample_rate;
};
struct sx_interface {
    void * (*add)   (struct sx_dev *dev);
    void   (*remove)(struct sx_dev *dev, void *context);
    void   (*event) (struct sx_dev *dev, void *context,
                     enum sx_dev_event event,
                     union sx_event_data *event_data);
    struct list_head list;
};
struct sx_sgmii_ctrl_segment {
    u8     reserved1;
    u8     one;
    __be16 type_sdq_lp;
    __be32 reserved2[3];
} __attribute__((packed));
struct sx_ethernet_header {
    uint8_t dmac[6];
    uint8_t smac[6];
    __be16  et;
    uint8_t mlx_proto;
    uint8_t ver;
};

typedef enum check_dup {
    CHECK_DUP_DISABLED_E = 0,
    CHECK_DUP_ENABLED_E = 1
} check_dup_e;

typedef enum is_vlan_tagged {
    VLAN_UNTAGGED_E = 0,
    VLAN_PRIO_TAGGED_E = 1,
    VLAN_TAGGED_E = 2,
} is_vlan_tagged_e;

typedef enum is_rp {
    IS_RP_DONT_CARE_E = 0,
    IS_RP_FROM_RP_E = 1,
    IS_RP_NOT_FROM_RP_E = 2,
} is_rp_e;

typedef enum is_bridge {
    IS_BRIDGE_DONT_CARE_E = 0,
    IS_BRIDGE_FROM_BRIDGE_E = 1,
    IS_BRIDGE_NOT_FROM_BRIDGE_E = 2,
} is_bridge_e;

struct sx_psample_listener_context {
    u32 group_num;
    u32 refcnt;
};

int sx_core_flush_synd_by_context(void * context);
int sx_core_flush_synd_by_handler(cq_handler handler);
int sx_register_interface(struct sx_interface *intf);
void sx_unregister_interface(struct sx_interface *intf);
int sx_core_add_synd(u8                          swid,
                     u16                         hw_synd,
                     enum l2_type                type,
                     pid_t                       caller_pid,
                     u8                          is_default,
                     union ku_filter_critireas   crit,
                     cq_handler                  handler,
                     void                       *context,
                     check_dup_e                 check_dup,
                     struct sx_dev             * sx_dev,
                     struct ku_port_vlan_params *port_vlan,
                     u8                          is_register); /* is_register ==> 1=register, 0=filter. */
int sx_core_remove_synd(u8 swid, u16 hw_synd, enum l2_type type, u8 is_default,
                        union ku_filter_critireas critireas,
                        void *context, struct sx_dev* sx_dev, cq_handler handler,
                        struct ku_port_vlan_params *port_vlan, u8 is_register); /* is_register ==> 1=register, 0=filter. */
int sx_core_post_send(struct sx_dev *dev, struct sk_buff *skb,
                      struct isx_meta *meta);
int __sx_core_post_send(struct sx_dev *dev, struct sk_buff *skb,
                        struct isx_meta *meta);
void sx_skb_free(struct sk_buff *skb);
void get_lag_id_from_local_port(struct sx_dev *dev, u8 sysport, u16 *lag_id, u8 *is_lag_member);
int sx_core_get_lag_oper_state(struct sx_dev *dev, u16 lag_id, u8 *oper_state_p);
int sx_core_get_ptp_clock_index(struct sx_dev *dev, uint8_t *ptp_clock_index_p);
int sx_core_get_ptp_state(struct sx_dev *dev, uint8_t *is_ptp_enable);
int sx_core_ptp_tx_handler(struct sx_dev *dev, struct sk_buff *skb, u16 sysport_lag_id, u8 is_lag);
int sx_core_ptp_tx_control_to_data(struct sx_dev   *dev,
                                   struct sk_buff **orig_skb,
                                   struct isx_meta *meta,
                                   u16              port,
                                   u8               is_lag,
                                   u8              *is_tagged,
                                   u8               hw_ts_required);

int sx_core_get_local(struct sx_dev *dev, uint16_t lag_id, uint8_t lag_subport,
                      uint16_t *local);
int sx_core_get_prio2tc(struct sx_dev *dev,
                        uint16_t port_lag_id, uint8_t is_lag,
                        uint8_t pcp, uint8_t *tc);
int sx_core_get_pvid(struct sx_dev *dev,
                     uint16_t       port_lag_id,
                     uint8_t        is_lag,
                     uint16_t      *pvid);
int sx_core_get_vlan_tagging(struct sx_dev *dev,
                             uint16_t port_lag_id, uint8_t is_lag,
                             uint16_t vlan, uint8_t *is_vlan_tagged);
int sx_core_get_prio_tagging(struct sx_dev *dev,
                             uint16_t port_lag_id, uint8_t is_lag,
                             uint8_t *is_port_prio_tagged);
int sx_core_get_rp_vlan(struct sx_dev          *dev,
                        struct completion_info *comp_info,
                        uint16_t               *vlan_id);
int sx_core_get_swid(struct sx_dev          *dev,
                     struct completion_info *comp_info,
                     uint8_t                *swid);
int sx_core_get_phy_port_max(struct sx_dev *dev, uint16_t *port);
int sx_core_get_lag_max(struct sx_dev *dev, uint16_t *lags, uint16_t *pors_per_lag);
int sx_core_get_vlan2ip(struct sx_dev *dev,
                        uint16_t vid, uint32_t *ip_addr);
int sx_core_get_rp_rfid(struct sx_dev *dev, uint16_t port_lag_id,
                        uint8_t is_lag, uint16_t vlan_id, uint16_t *rfid);
int sx_core_get_rp_mode(struct sx_dev *dev, u8 is_lag, u16 sysport_lag_id,
                        u16 vlan_id, u8 *is_rp);

int sx_core_get_fid_by_port_vid(struct sx_dev *dev,
                                struct completion_info *comp_info, uint16_t *fid);
int sx_core_get_lag_mid(struct sx_dev *dev, u16 lag_id, u16 *mid);
int sx_core_is_eqn_cmd_ifc_only(struct sx_dev *dev, int eqn, u8 *is_cmd_ifc_only);
int sx_core_get_ib_system_port_mid(struct sx_dev *dev, u16 ib_port, u16* sys_port_mid);
int sx_core_get_send_to_port_as_data(struct sx_dev *dev, u8* send_to_port_as_data, u8 send_default);

int __sx_core_dev_specific_cb_get_reference(struct sx_dev *dev);
void __sx_core_dev_specific_cb_release_reference(struct sx_dev *dev);
int sx_core_get_rdq_num_max(struct sx_dev *dev, uint8_t *rdq_num_max_p);

int sx_core_send_mad_sync(struct sx_dev *dev,
                          int            dev_id,
                          u32            in_modifier,
                          u8             op_modifier,
                          void          *in_mad,
                          int            in_size,
                          void          *out_mad,
                          int            out_size);

int sx_core_skb_add_vlan(struct sk_buff **untagged_skb, uint16_t vid, uint16_t pcp);

#endif /* SX_DRIVER_H */
