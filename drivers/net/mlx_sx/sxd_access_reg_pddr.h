/*
 * Copyright (C) Mellanox Technologies, Ltd. 2010-2020 ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Mellanox Technologies, Ltd.
 * (the "Company") and all right, title, and interest in and to the software product,
 * including all associated intellectual property rights, are and shall
 * remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 *
 */

#ifndef __SXD_ACCESS_REG_PDDR_H__
#define __SXD_ACCESS_REG_PDDR_H__

/************************************************
 *  Local Defines
 ***********************************************/

/************************************************
 *  Local Macros
 ***********************************************/

/************************************************
 *  Local Type definitions
 ***********************************************/

/************************************************
 *  Macros
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

/************************************************
 *  Global variables
 ***********************************************/

/************************************************
 *  Function declarations
 ***********************************************/
#ifndef __KERNEL__
#include <sx/sxd/sxd_status.h>
#include <sx/sxd/kernel_user.h>
#include <complib/cl_packon.h>
#else
#include <linux/time.h>
#include <linux/mlx_sx/kernel_user.h>
#define PACK_SUFFIX  __attribute__((packed))
#define sxd_status_t int
#endif

/**
 * sxd_emad_pddr_oper_info_t structure is used to return pddr register
 * oper info.
 */

typedef struct sxd_emad_oper_info {
    uint8_t  reserved1;
    uint8_t  proto_active_and_neg_mode_active;
    uint8_t  reserved2[2];
    uint8_t  phy_mngr_fsm_state;
    uint8_t  eth_an_fsm_state;
    uint8_t  ib_phy_fsm_state;
    uint8_t  reserved3;
    uint16_t phy_manager_link_width_enabled;
    uint16_t phy_manager_link_proto_enabled;
    uint16_t core_to_phy_link_width_enabled;
    uint16_t core_to_phy_link_proto_enabled;
    uint32_t cable_proto_cap;
    uint16_t link_width_active;
    uint16_t link_speed_active;
    uint8_t  retran_mode_active;
    uint8_t  retran_mode_request;
    uint8_t  reserved4;
    uint8_t  loopback_mode;
    uint16_t fec_mode_active;
    uint16_t fec_mode_request;
    uint16_t profile_fec_in_use;
    uint8_t  reserved5;
    uint8_t  eth_fec_support;
} PACK_SUFFIX sxd_emad_pddr_oper_info_t;

/**
 * sxd_emad_pddr_phy_info_t structure is used to return pddr register
 * physical info.
 */

typedef struct sxd_emad_pddr_phy_info {
    uint8_t  remote_device_type;
    uint8_t  reserved1[2];
    uint8_t  port_notifications;
    uint16_t num_of_negotiations_attempts;
    uint8_t  ib_revision;
    uint8_t  lp_ib_revision;
    uint8_t  hw_link_phy_state;
    uint8_t  reserved2;
    uint16_t phy_manager_disable_mask;
    uint32_t pcs_phy_state;
    uint32_t lp_proto_enabled;
    uint16_t lp_fec_mode_support;
    uint16_t lp_fec_mode_request;
    uint32_t ib_last_link_down_reason;
    uint8_t  eth_last_link_down_lane[NUMBER_OF_SERDESES];
    uint32_t speed_deg_db;
    uint32_t degrade_grade_lane[NUMBER_OF_SERDESES];
    uint8_t  kr_startup_fsm_lane[NUMBER_OF_SERDESES];
    uint16_t ib_phy_fsm_state_trace;
    uint32_t eth_an_debug_indication;
    uint16_t kr_startup_debug_indecation[NUMBER_OF_SERDESES];
    uint8_t  reserved7[3];
    uint8_t  irisc_status;
    uint32_t stamping_reason;
    uint32_t reserved8;
} PACK_SUFFIX sxd_emad_pddr_phy_info_t;


/**
 * sxd_emad_pddr_module_info_t structure is used to return pddr register
 * module info.
 */

typedef struct sxd_emad_pddr_module_info {
    uint8_t  cable_technology;
    uint8_t  cable_breakout;
    uint8_t  ext_ethernet_compliance_code;
    uint8_t  ethernet_compliance_code;
    uint8_t  cable_type_and_cable_vendor;
    uint8_t  cable_length;
    uint8_t  cable_identifier;
    uint8_t  cable_power_class;
    uint8_t  reserved1;
    uint8_t  cable_rx_amp;
    uint8_t  cable_rx_emphasis;
    uint8_t  cable_tx_equalization;
    uint8_t  reserve2;
    uint8_t  cable_attenuation_12g;
    uint8_t  cable_attenuation_7g;
    uint8_t  cable_attenuation_5g;
    uint8_t  reserved3;
    uint8_t  rx_tx_cdr_cap;
    uint8_t  rx_cdr_state;
    uint8_t  tx_cdr_state;
    uint32_t vendor_name;
    uint32_t vendor_pn;
    uint16_t vendor_rev;
    uint16_t fw_version;
    uint32_t vendor_sn;
    uint16_t temperature;
    uint16_t voltage;
    uint16_t rx_power_lane[NUMBER_OF_SERDESES];
    uint16_t tx_power_lane[NUMBER_OF_SERDESES];
    uint16_t temperature_high_th;
    uint16_t temperature_low_th;
    uint16_t voltage_high_th;
    uint16_t voltage_low_th;
    uint16_t rx_power_high_th;
    uint16_t rx_power_low_th;
    uint16_t tx_power_high_th;
    uint16_t tx_power_low_th;
    uint16_t tx_bias_high_th;
    uint16_t tx_bias_low_th;
    uint16_t reserved6;
    uint16_t wavelength;
} PACK_SUFFIX sxd_emad_pddr_module_info_t;

typedef struct sx_emad_pddr_troubleshooting_info {
    uint16_t reserved1;
    uint16_t group_opcode;
    uint32_t status_code;
    uint16_t user_feedback_data;
    uint16_t user_feedback_index;
    uint8_t  status_message[236];
} PACK_SUFFIX sx_emad_pddr_troubleshooting_info_t;

#ifndef __KERNEL__
#include <complib/cl_packoff.h>
#endif

sxd_status_t convert_pddr_oper_info(sxd_emad_pddr_oper_info_t  *req_oper_info_p,
                                    struct pddr_oper_info_resp *user_kernel_info_p);
sxd_status_t convert_pddr_phy_info(sxd_emad_pddr_phy_info_t  *req_oper_info_p,
                                   struct pddr_phy_info_resp *user_kernel_info_p);
sxd_status_t convert_pddr_module_info(sxd_emad_pddr_module_info_t  *reg_module_info_p,
                                      struct pddr_module_info_resp *user_kernel_info_p);
sxd_status_t covert_pddr_troubleshooting_info(sx_emad_pddr_troubleshooting_info_t   *reg_info_p,
                                              struct pddr_troubleshooting_info_resp *user_kernel_info_p);

#endif /* __SXD_ACCESS_REG_PDDR_H__ */
