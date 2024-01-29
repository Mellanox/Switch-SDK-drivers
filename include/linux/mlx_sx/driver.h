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

#ifndef SX_DRIVER_H
#define SX_DRIVER_H

#include <linux/seq_file.h>

#include <linux/device.h>
#include <linux/ethtool.h>
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
    SX_DEV_EVENT_MODULE_SUPPORT_SET,
    SX_DEV_EVENT_GET_NETDEV_TRAP_INFO,
    SX_DEV_EVENT_ADD_SYND_PSAMPLE,
    SX_DEV_EVENT_REMOVE_SYND_PSAMPLE,
    SX_DEV_EVENT_UPDATE_SAMPLE_RATE,
    SX_DEV_EVENT_ISSU_START,
    SX_DEV_EVENT_PRE_RESET,
    SX_DEV_EVENT_POST_RESET
};

#define SX_PAGE_SIZE  4096
#define SX_PAGE_SHIFT 12

#define ETHTYPE_ARP             0x0806
#define ETHTYPE_VLAN            0x8100
#define ETHTYPE_EMAD            0x8932
#define ETHTYPE_DONT_CARE_VALUE 0
#define QPN_DONT_CARE_VALUE     0xffffffff
#define QPN_MULTICAST_VALUE     0xffffff
#define DMAC_DONT_CARE_VALUE    0
#define TID_DONT_CARE_VALUE     0
#define SYSPORT_DONT_CARE_VALUE 0
#define SPAN_TO_CPU_TRAP_ID_ING 467
#define SPAN_TO_CPU_TRAP_ID_EGR 468

#define SENSOR_NAME_LEN_MAX 8
#define ASIC_NAME_LEN_MAX   8

#define ASIC_SYSFS_PREFIX "asic"

#define MODULE_EEPROM_UPPER_PAGE_NUM 255
#define MODULE_EEPROM_I2C_ADDR_NUM   2
#define EEPROM_PAGE0_SIZE            (256)
#define EEPROM_UPPER_PAGE_SIZE       (128)

typedef enum l3_synd_type {
    L3_SYND_TYPE_GLOBAL = 0,
    L3_SYND_TYPE_PORT   = 1,
    L3_SYND_TYPE_LAG    = 2,
    L3_SYND_TYPE_VLAN   = 3,
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
    } rpa_init;
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
        uint16_t local_port;
        uint32_t sample_rate;
    } psample_port_sample_rate;
    struct {
        u8 module_support_en;
    } module_support_set;
    struct {
        int err;
    } post_reset;
};
struct sx_interface {
    void * (*add)   (struct sx_dev *dev);
    void   (*remove)(struct sx_dev *dev, void *context);
    int    (*event) (struct sx_dev *dev, void *context,
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
    CHECK_DUP_ENABLED_E  = 1
} check_dup_e;

typedef enum is_vlan_tagged {
    VLAN_UNTAGGED_E    = 0,
    VLAN_PRIO_TAGGED_E = 1,
    VLAN_TAGGED_E      = 2,
} is_vlan_tagged_e;

typedef enum is_rp {
    IS_RP_DONT_CARE_E   = 0,
    IS_RP_FROM_RP_E     = 1,
    IS_RP_NOT_FROM_RP_E = 2,
} is_rp_e;

typedef enum is_bridge {
    IS_BRIDGE_DONT_CARE_E       = 0,
    IS_BRIDGE_FROM_BRIDGE_E     = 1,
    IS_BRIDGE_NOT_FROM_BRIDGE_E = 2,
} is_bridge_e;

struct sx_psample_listener_context {
    u32 group_num;
    u32 refcnt;
};

/* Link extended state */
enum sx_link_ext_state {
    SX_LINK_EXT_STATE_AUTONEG,
    SX_LINK_EXT_STATE_LINK_TRAINING_FAILURE,
    SX_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
    SX_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY,
    SX_LINK_EXT_STATE_NO_CABLE,
    SX_LINK_EXT_STATE_CABLE_ISSUE,
    SX_LINK_EXT_STATE_EEPROM_ISSUE,
    SX_LINK_EXT_STATE_CALIBRATION_FAILURE,
    SX_LINK_EXT_STATE_POWER_BUDGET_EXCEEDED,
    SX_LINK_EXT_STATE_OVERHEAT,
    SX_LINK_EXT_STATE_MODULE,
};

/* More information in addition to SX_LINK_EXT_STATE_AUTONEG. */
enum sx_link_ext_substate_autoneg {
    SX_LINK_EXT_SUBSTATE_AN_NO_PARTNER_DETECTED = 1,
    SX_LINK_EXT_SUBSTATE_AN_ACK_NOT_RECEIVED,
    SX_LINK_EXT_SUBSTATE_AN_NEXT_PAGE_EXCHANGE_FAILED,
    SX_LINK_EXT_SUBSTATE_AN_NO_PARTNER_DETECTED_FORCE_MODE,
    SX_LINK_EXT_SUBSTATE_AN_FEC_MISMATCH_DURING_OVERRIDE,
    SX_LINK_EXT_SUBSTATE_AN_NO_HCD,
};

/* More information in addition to SX_LINK_EXT_STATE_LINK_TRAINING_FAILURE.
 */
enum sx_link_ext_substate_link_training {
    SX_LINK_EXT_SUBSTATE_LT_KR_FRAME_LOCK_NOT_ACQUIRED = 1,
    SX_LINK_EXT_SUBSTATE_LT_KR_LINK_INHIBIT_TIMEOUT,
    SX_LINK_EXT_SUBSTATE_LT_KR_LINK_PARTNER_DID_NOT_SET_RECEIVER_READY,
    SX_LINK_EXT_SUBSTATE_LT_REMOTE_FAULT,
};

/* More information in addition to SX_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH.
 */
enum sx_link_ext_substate_link_logical_mismatch {
    SX_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_ACQUIRE_BLOCK_LOCK = 1,
    SX_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_ACQUIRE_AM_LOCK,
    SX_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_GET_ALIGN_STATUS,
    SX_LINK_EXT_SUBSTATE_LLM_FC_FEC_IS_NOT_LOCKED,
    SX_LINK_EXT_SUBSTATE_LLM_RS_FEC_IS_NOT_LOCKED,
};

/* More information in addition to SX_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY.
 */
enum sx_link_ext_substate_bad_signal_integrity {
    SX_LINK_EXT_SUBSTATE_BSI_LARGE_NUMBER_OF_PHYSICAL_ERRORS = 1,
    SX_LINK_EXT_SUBSTATE_BSI_UNSUPPORTED_RATE,
    SX_LINK_EXT_SUBSTATE_BSI_SERDES_REFERENCE_CLOCK_LOST,
    SX_LINK_EXT_SUBSTATE_BSI_SERDES_ALOS,
};

/* More information in addition to SX_LINK_EXT_STATE_CABLE_ISSUE. */
enum sx_link_ext_substate_cable_issue {
    SX_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLE = 1,
    SX_LINK_EXT_SUBSTATE_CI_CABLE_TEST_FAILURE,
};

/* More information in addition to SX_LINK_EXT_STATE_MODULE. */
enum sx_link_ext_substate_module {
    SX_LINK_EXT_SUBSTATE_MODULE_CMIS_NOT_READY = 1,
};

/* Link extended state and substate. */
struct sx_link_ext_state_info {
    enum sx_link_ext_state link_ext_state;
    union {
        enum sx_link_ext_substate_autoneg               autoneg;
        enum sx_link_ext_substate_link_training         link_training;
        enum sx_link_ext_substate_link_logical_mismatch link_logical_mismatch;
        enum sx_link_ext_substate_bad_signal_integrity  bad_signal_integrity;
        enum sx_link_ext_substate_cable_issue           cable_issue;
        enum sx_link_ext_substate_module                module;
        u8                                              __link_ext_substate;
    };
};

/**
 * enum sx_module_power_mode_policy - plug-in module power mode policy
 * @SX_MODULE_POWER_MODE_POLICY_HIGH: Module is always in high power mode.
 * @SX_MODULE_POWER_MODE_POLICY_AUTO: Module is transitioned by the host
 *  to high power mode when the first port using it is put administratively
 *  up and to low power mode when the last port using it is put
 *  administratively down.
 */
enum sx_module_power_mode_policy {
    SX_MODULE_POWER_MODE_POLICY_HIGH = 1,
    SX_MODULE_POWER_MODE_POLICY_AUTO,
};

/**
 * enum sx_module_power_mode - plug-in module power mode
 * @SX_MODULE_POWER_MODE_LOW: Module is in low power mode.
 * @SX_MODULE_POWER_MODE_HIGH: Module is in high power mode.
 */
enum sx_module_power_mode {
    SX_MODULE_POWER_MODE_LOW = 1,
    SX_MODULE_POWER_MODE_HIGH,
};

/**
 * enum sx_module_sysfs_eeprom_access - access type to module sysfs eeprom
 * @MODULE_SYSFS_EEPROM_READ: Read module sysfs eeprom.
 * @MODULE_SYSFS_EEPROM_WRITE: Write module sysfs eeprom.
 */
enum sx_module_sysfs_eeprom_access {
    MODULE_SYSFS_EEPROM_READ  = 1,
    MODULE_SYSFS_EEPROM_WRITE = 2,
};

/**
 * enum sx_module_power_on_set - power on / off module
 * @SX_MODULE_POWER_OFF: Power off module.
 * @SX_MODULE_POWER_OFF: Power on module.
 */
enum sx_module_power_on_set {
    SX_MODULE_POWER_OFF = 0,
    SX_MODULE_POWER_ON,
};

/**
 * enum sx_module_tx_disable_set - Turn on / off module TX
 * @SX_MODULE_TX_ENABLE: Turn on module TX.
 * @SX_MODULE_TX_DISABLE: Turn off module TX.
 */
enum sx_module_tx_disable_set {
    SX_MODULE_TX_DEFAULT = 0,
    SX_MODULE_TX_DISABLE,
};

/**
 * struct sx_module_power_mode_params - module power mode parameters
 * @policy: The power mode policy enforced by the host for the plug-in module.
 * @mode: The operational power mode of the plug-in module. Should be filled by
 *  device drivers on get operations.
 */
struct sx_module_power_mode_params {
    enum sx_module_power_mode_policy policy;
    enum sx_module_power_mode        mode;
};

/* function ptr prototype for bulk counters parsing
 * utilized on sx_bulk_cntr_multi_emad_parse()*/
typedef void (*sx_bulk_cntr_reg_parser_t)(const void                                *reg,
                                          u32                                        reg_len,
                                          struct sxd_bulk_cntr_buffer_layout_common *layout_common,
                                          void                                      *context);
/**
 * struct sx_temperature_params - module or asic temperature parameters
 * @highest: Highest measured temperature.
 * @input: Current temperature.
 * @label: Module or asic name.
 */
struct sx_temperature_params {
    u64  highest;
    u64  input;
    char label[SENSOR_NAME_LEN_MAX + 1];
};

typedef enum emad_prio {
    EMAD_PRIO_HIGH,
    EMAD_PRIO_LOW,
    EMAD_PRIO_MAX
} emad_prio_e;

struct sx_emad_in_params {
    bool silent;    /* [IN]  - do not log on error */
};

struct sx_emad_out_params {
    u32 fw_status;  /* [OUT] - FW status code on completion */
    u32 fw_latency; /* [OUT] - FW latency */
    u16 reg_id;     /* [OUT] - Register ID */
};

struct eeprom_page0_node {
    struct kobject *page;
    struct kobject *i2c[MODULE_EEPROM_I2C_ADDR_NUM];
};

struct eeprom_pagex_node {
    struct kobject *page;
};

struct module_sysfs_eeprom_tree {
    struct kobject          *eeprom;
    struct kobject          *pages;
    struct eeprom_page0_node page0;
    struct eeprom_pagex_node page[MODULE_EEPROM_UPPER_PAGE_NUM];
};

struct module_sysfs_node {
    struct kobject                 *module;
    struct module_sysfs_eeprom_tree eeprom_tree;
};

int sx_core_flush_synd_by_context(void * context);
int sx_core_flush_synd_by_handler(cq_handler handler);
int sx_register_interface(struct sx_interface *intf);
void sx_unregister_interface(struct sx_interface *intf);
int sx_core_add_synd(u8                                swid,
                     u16                               hw_synd,
                     enum l2_type                      type,
                     pid_t                             caller_pid,
                     const char                       *caller_name,
                     u8                                is_default,
                     const union ku_filter_critireas  *crit,
                     cq_handler                        handler,
                     void                             *context,
                     check_dup_e                       check_dup,
                     struct sx_dev                   * sx_dev,
                     const struct ku_port_vlan_params *port_vlan,
                     u8                                is_register);      /* is_register ==> 1=register, 0=filter. */
int sx_core_remove_synd(u8 swid, u16 hw_synd, enum l2_type type, u8 is_default,
                        const union ku_filter_critireas *critireas,
                        void *context, struct sx_dev* sx_dev, cq_handler handler,
                        const struct ku_port_vlan_params *port_vlan,
                        u8 is_register,     /* is_register ==> 1=register, 0=filter. */
                        u8 *synd_was_removed);
int sx_core_post_send(struct sx_dev *dev, struct sk_buff *skb,
                      struct isx_meta *meta);
int __sx_core_post_send(struct sx_dev *dev, struct sk_buff *skb, struct isx_meta *meta, u8 sdq_id);
void sx_skb_free(struct sk_buff *skb);
void sx_skb_consume(struct sk_buff *skb);
int sx_core_get_lag_oper_state(struct sx_dev *dev, u16 lag_id, u8 *oper_state_p);
int sx_core_get_ptp_clock_index(struct sx_dev *dev, uint8_t *ptp_clock_index_p);
int sx_core_get_ptp_state(struct sx_dev *dev, uint8_t *is_ptp_enable);
int sx_core_ptp_tx_handler(struct sx_dev  *dev,
                           struct sk_buff *skb,
                           u16             sysport_lag_id,
                           u8              is_lag,
                           bool           *is_ptp_pkt);
int sx_core_ptp_get_supported_tx_types(struct sx_dev *dev, u32 *tx_types);
int sx_core_ptp_set_tx_type(struct sx_dev *dev, int tx_type);
int sx_core_ptp_tx_control_to_data(struct sx_dev   *dev,
                                   struct sk_buff **orig_skb,
                                   struct isx_meta *meta,
                                   u16              port,
                                   u8               is_lag,
                                   u8              *is_tagged);

int sx_core_get_local(struct sx_dev *dev, uint16_t lag_id, uint16_t lag_subport,
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

int sx_core_get_module_by_port(struct sx_dev *dev, uint16_t local_port, uint8_t *slot, uint8_t *module);
int sx_core_update_module_power_mode(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool port_up);
int sx_core_set_module(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, uint8_t enable, uint8_t reset);
int sx_core_set_port_module_power_mode_policy(struct sx_dev                   *dev,
                                              uint16_t                         local_port,
                                              enum sx_module_power_mode_policy power_mode_policy);
int sx_core_get_port_module_power_mode(struct sx_dev                      *dev,
                                       uint16_t                            local_port,
                                       struct sx_module_power_mode_params *params);
int sx_core_reset_port_module(struct sx_dev *dev, uint16_t local_port);
int sx_core_get_port_module_temperature(struct sx_dev                *dev,
                                        uint16_t                      local_port,
                                        struct sx_temperature_params *params);
ssize_t sx_core_module_sysfs_eeprom_access(struct sx_dev                     *dev,
                                           const char                        *node_name,
                                           bool                               call_with_module_id,
                                           uint8_t                            module_id,
                                           uint16_t                           local_port,
                                           enum sx_module_sysfs_eeprom_access access,
                                           char                              *buf,
                                           loff_t                             pos,
                                           size_t                             count);
int sx_core_create_default_modules_sysfs_eeprom_tree(struct sx_dev             *dev,
                                                     struct kobject            *parent,
                                                     struct module_sysfs_node **root_arr);
void sx_core_delete_default_modules_sysfs_eeprom_tree(struct module_sysfs_node **root_arr);
int sx_core_create_module_sysfs_eeprom_tree(struct kobject                  *parent,
                                            struct module_sysfs_eeprom_tree *root,
                                            struct bin_attribute            *page0_attr,
                                            struct bin_attribute            *pagex_attr);
void sx_core_delete_module_sysfs_eeprom_tree(struct module_sysfs_eeprom_tree *root,
                                             struct bin_attribute            *page0_attr,
                                             struct bin_attribute            *pagex_attr);

int __sx_core_dev_specific_cb_get_reference(struct sx_dev *dev);
void __sx_core_dev_specific_cb_release_reference(struct sx_dev *dev);

int sx_core_send_mad_sync(struct sx_dev *dev,
                          int            dev_id,
                          u32            in_modifier,
                          u8             op_modifier,
                          void          *in_mad,
                          int            in_size,
                          void          *out_mad,
                          int            out_size);

int sx_core_skb_add_vlan(struct sk_buff **untagged_skb, uint16_t vid, uint16_t pcp);

typedef int (*sx_net_dm_hw_report_func)(struct completion_info *comp_info,
                                        const char             *trap_name,
                                        const char             *trap_grp_name,
                                        const void             *fa_cookie,
                                        u8                      copy_skb);

/* tells if driver was loaded with predefined mapping of dev_id <==> PCI bus */
bool sx_core_has_predefined_devices(void);


/* function to parse multi-reg EMAD frame */
void sx_bulk_cntr_multi_emad_parse(const void               *buff,
                                   u32                       buff_len,
                                   sx_bulk_cntr_reg_parser_t reg_parser_cb,
                                   void                     *context,
                                   bool                      is_streaming);
int bulk_cntr_db_mocs_session_acquire(enum sxd_bulk_cntr_key_type_e type);
int bulk_cntr_db_mocs_session_release(enum sxd_bulk_cntr_key_type_e type);
int sx_core_register_net_dm_hw_report(sx_net_dm_hw_report_func sx_net_dm_hw_report_p);

int sx_qos_emad_push_to_queue(struct sx_dev *dev, struct sk_buff  *skb, struct isx_meta *meta, emad_prio_e priority);

int sx_core_get_port_module_power_on(struct sx_dev *dev, uint16_t local_port, bool *power_on);
int sx_core_power_on_off_port_module(struct sx_dev *dev, uint16_t local_port, bool power_on);
int sx_core_get_port_module_tx_disable(struct sx_dev *dev, uint16_t local_port, bool *tx_disable);
int sx_core_set_port_module_tx_disable(struct sx_dev *dev, uint16_t local_port, bool tx_disable);
int sx_core_get_port_module_present(struct sx_dev *dev, uint16_t local_port, bool *present);
int sx_core_get_port_module_rx_los(struct sx_dev *dev, uint16_t local_port, bool *rx_los);

/* debug-dump APIs */
#define SX_DBG_DUMP_HEADER_MAX_LEN 150

typedef int (*sx_dbg_dump_proc_show_cb_t)(struct seq_file* seq_file, void *v, void* context);
typedef size_t (*sx_dbg_dump_proc_size_cb_t)(void);
typedef int (*sx_dbg_dump_proc_cmd_cb_t)(int argc, const char *argv[], void *context);

#define sx_dbg_dump_print_table_header(seqfile, fmt, args ...)                                                                                    \
    do {                                                                                                                                          \
        seq_printf((seqfile), fmt "\n", ## args);                                                                                                 \
        seq_printf((seqfile),                                                                                                                     \
                   "------------------------------------------------------------------------------------------------------------------------\n"); \
    } while (0)

#define sx_dbg_dump_print_empty_line(seqfile) \
    do {                                      \
        seq_printf((seqfile), "\n");          \
    } while (0)

#define sx_dbg_dump_print_separate_line(seqfile)                                                                                                  \
    do {                                                                                                                                          \
        seq_printf((seqfile),                                                                                                                     \
                   "........................................................................................................................\n"); \
    } while (0)

void sx_dbg_dump_print_header(struct seq_file *m, const char* header);

int sx_dbg_dump_read_handler_register(const char                *name,
                                      sx_dbg_dump_proc_show_cb_t show_cb,
                                      sx_dbg_dump_proc_size_cb_t size_cb,
                                      void                      *context);
void sx_dbg_dump_read_handler_unregister(const char *name);

int sx_dbg_dump_write_handler_register(const char               *cmd,
                                       const char               *usage,
                                       const char               *description,
                                       sx_dbg_dump_proc_cmd_cb_t cmd_cb,
                                       void                     *context);
void sx_dbg_dump_write_handler_unregister(const char *cmd);

#endif /* SX_DRIVER_H */
