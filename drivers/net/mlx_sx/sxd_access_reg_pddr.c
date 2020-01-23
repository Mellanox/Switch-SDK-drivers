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

#ifndef __KERNEL__
#include <complib/cl_byteswap_osd.h>
#include <complib/cl_types.h>
#include <sx/sxd/sxd_status.h>
#include <string.h>
#else
#include <asm/byteorder.h>
#define cl_ntoh32          be32_to_cpu
#define cl_ntoh16          be16_to_cpu
#define SXD_STATUS_SUCCESS 0
#define FALSE              0
#define TRUE               (!FALSE)
#endif

#include "sxd_access_reg_pddr.h"

/************************************************
 *  Local function declarations
 ***********************************************/

static void __convert_pddr_pcs_phy_state_to_kernel_info(struct pcs_phy_state *kernel_info_p,
                                                        uint32_t              pcs_phy_state);
static void __convert_pddr_speed_deg_db_to_kernel_info(struct pddr_speed_deg_db *kernel_info_p,
                                                       uint32_t                  speed_deg_db);
/************************************************
 *  Function implementations
 ***********************************************/

sxd_status_t convert_pddr_module_info(sxd_emad_pddr_module_info_t  *reg_module_info_p,
                                      struct pddr_module_info_resp *user_kernel_info_p)
{
    int i = 0;

    user_kernel_info_p->cable_technology = reg_module_info_p->cable_technology;
    user_kernel_info_p->cable_breakout = reg_module_info_p->cable_breakout;
    user_kernel_info_p->ext_ethernet_compliance_code = reg_module_info_p->ext_ethernet_compliance_code;
    user_kernel_info_p->ethernet_compliance_code = reg_module_info_p->ethernet_compliance_code;
    user_kernel_info_p->cable_type = (reg_module_info_p->cable_type_and_cable_vendor >> 4) & 0xF;
    user_kernel_info_p->cable_vendor = reg_module_info_p->cable_type_and_cable_vendor & 0xF;
    user_kernel_info_p->cable_length = reg_module_info_p->cable_length;
    user_kernel_info_p->cable_identifier = reg_module_info_p->cable_identifier;
    user_kernel_info_p->cable_power_class = reg_module_info_p->cable_power_class;
    user_kernel_info_p->cable_rx_amp = reg_module_info_p->cable_rx_amp;
    user_kernel_info_p->cable_rx_emphasis = reg_module_info_p->cable_rx_emphasis;
    user_kernel_info_p->cable_tx_equalization = reg_module_info_p->cable_tx_equalization;
    user_kernel_info_p->cable_attenuation_12g = reg_module_info_p->cable_attenuation_12g;
    user_kernel_info_p->cable_attenuation_7g = reg_module_info_p->cable_attenuation_7g;
    user_kernel_info_p->cable_attenuation_5g = reg_module_info_p->cable_attenuation_5g;
    user_kernel_info_p->rx_cdr_cap = (reg_module_info_p->rx_tx_cdr_cap >> 4) & 0xF;
    user_kernel_info_p->tx_cdr_cap = reg_module_info_p->rx_tx_cdr_cap & 0xF;
    user_kernel_info_p->tx_cdr_state = reg_module_info_p->tx_cdr_state;
    user_kernel_info_p->rx_cdr_state = reg_module_info_p->rx_cdr_state;
    user_kernel_info_p->vendor_name = cl_ntoh32(reg_module_info_p->vendor_name);
    user_kernel_info_p->vendor_pn = cl_ntoh32(reg_module_info_p->vendor_pn);
    user_kernel_info_p->fw_version = cl_ntoh16(reg_module_info_p->fw_version);
    user_kernel_info_p->vendor_rev = cl_ntoh16(reg_module_info_p->vendor_rev);
    user_kernel_info_p->vendor_sn = cl_ntoh32(reg_module_info_p->vendor_sn);
    user_kernel_info_p->temperature = cl_ntoh16(reg_module_info_p->temperature);
    user_kernel_info_p->voltage = cl_ntoh16(reg_module_info_p->voltage);

    for (i = 0; i < NUMBER_OF_SERDESES; i++) {
        user_kernel_info_p->rx_power_lane[i] = cl_ntoh16(reg_module_info_p->rx_power_lane[i]);
        user_kernel_info_p->tx_power_lane[i] = cl_ntoh16(reg_module_info_p->tx_power_lane[i]);
    }

    user_kernel_info_p->temperature_high_th = cl_ntoh16(reg_module_info_p->temperature_high_th);
    user_kernel_info_p->temperature_low_th = cl_ntoh16(reg_module_info_p->temperature_low_th);
    user_kernel_info_p->voltage_high_th = cl_ntoh16(reg_module_info_p->voltage_high_th);
    user_kernel_info_p->voltage_low_th = cl_ntoh16(reg_module_info_p->voltage_low_th);
    user_kernel_info_p->rx_power_high_th = cl_ntoh16(reg_module_info_p->rx_power_high_th);
    user_kernel_info_p->rx_power_low_th = cl_ntoh16(reg_module_info_p->rx_power_low_th);
    user_kernel_info_p->tx_power_high_th = cl_ntoh16(reg_module_info_p->tx_power_high_th);
    user_kernel_info_p->tx_power_low_th = cl_ntoh16(reg_module_info_p->tx_power_low_th);
    user_kernel_info_p->tx_bias_high_th = cl_ntoh16(reg_module_info_p->tx_bias_high_th);
    user_kernel_info_p->tx_bias_low_th = cl_ntoh16(reg_module_info_p->tx_bias_low_th);
    user_kernel_info_p->wavelength = cl_ntoh16(reg_module_info_p->wavelength);

    return SXD_STATUS_SUCCESS;
}

sxd_status_t convert_pddr_phy_info(sxd_emad_pddr_phy_info_t  *reg_oper_info_p,
                                   struct pddr_phy_info_resp *user_kernel_info_p)
{
    int     i = 0;
    uint8_t kr_vals;

    user_kernel_info_p->remote_device = ((remote_device_type_t)reg_oper_info_p->remote_device_type);
    user_kernel_info_p->port_notifications = ((port_notifications_t)reg_oper_info_p->port_notifications);
    user_kernel_info_p->neg_attempts = cl_ntoh16(reg_oper_info_p->num_of_negotiations_attempts);
    user_kernel_info_p->ib_revision = reg_oper_info_p->ib_revision;
    user_kernel_info_p->lp_ib_revision = reg_oper_info_p->lp_ib_revision;
    user_kernel_info_p->hw_link_phy_state = ((hw_link_phy_state_t)reg_oper_info_p->hw_link_phy_state);
    user_kernel_info_p->phy_mgr_disable_mask_bitmap = cl_ntoh16(reg_oper_info_p->phy_manager_disable_mask);

    __convert_pddr_pcs_phy_state_to_kernel_info(&user_kernel_info_p->pcs_phy_state, cl_ntoh32(
                                                    reg_oper_info_p->pcs_phy_state));

    user_kernel_info_p->lp_proto_enabled.eth = cl_ntoh32(reg_oper_info_p->lp_proto_enabled);
    user_kernel_info_p->lp_fec_mode_supported = cl_ntoh16(reg_oper_info_p->lp_fec_mode_support);
    user_kernel_info_p->lp_fec_mode_req = cl_ntoh16(reg_oper_info_p->lp_fec_mode_request);
    user_kernel_info_p->ib_last_link_down_reason = cl_ntoh32(reg_oper_info_p->ib_last_link_down_reason);

    __convert_pddr_speed_deg_db_to_kernel_info(&user_kernel_info_p->speed_deg,
                                               cl_ntoh32(((uint32_t)reg_oper_info_p->speed_deg_db)));

    kr_vals = ((cl_ntoh32(reg_oper_info_p->eth_an_debug_indication) >> 15) & 0xF);

    for (i = 0; i < NUMBER_OF_SERDESES; i++) {
        user_kernel_info_p->eth_lastlink_down_lane[i] = reg_oper_info_p->eth_last_link_down_lane[i];
        user_kernel_info_p->degrade_grade_lane[i] = cl_ntoh32(reg_oper_info_p->degrade_grade_lane[i]) >> 8;
        user_kernel_info_p->kr_startup_fsm_lane[i] = reg_oper_info_p->kr_startup_fsm_lane[i];
        user_kernel_info_p->ib_phy_fsm_state_trace = cl_ntoh16(reg_oper_info_p->ib_phy_fsm_state_trace);
        user_kernel_info_p->eth_an_debug_indication.kr_strtup_failure_mask[i] = ((1 << i) & kr_vals) ? TRUE : FALSE;
        user_kernel_info_p->kr_startup_debug_indication[i] =
            cl_ntoh16(reg_oper_info_p->kr_startup_debug_indecation[i]);
    }

    user_kernel_info_p->eth_an_debug_indication.debug_indication =
        (cl_ntoh32(reg_oper_info_p->eth_an_debug_indication)) & 0x7FF;
    user_kernel_info_p->irisc_status = reg_oper_info_p->irisc_status;
    user_kernel_info_p->stamping_reason = cl_ntoh32(reg_oper_info_p->stamping_reason);
    return SXD_STATUS_SUCCESS;
}

sxd_status_t covert_pddr_troubleshooting_info(sx_emad_pddr_troubleshooting_info_t   *reg_info_p,
                                              struct pddr_troubleshooting_info_resp *user_kernel_info_p)
{
    user_kernel_info_p->group_opcode = cl_ntoh16(reg_info_p->group_opcode);
    user_kernel_info_p->status_opcode = cl_ntoh32(reg_info_p->status_code);
    strncpy((char*)user_kernel_info_p->status_message, (char*)reg_info_p->status_message,
            sizeof(user_kernel_info_p->status_message));
    return SXD_STATUS_SUCCESS;
}

static void __convert_pddr_pcs_phy_state_to_kernel_info(struct pcs_phy_state *kernel_info_p, uint32_t pcs_phy_state)
{
    int serdes_iter = 0;

#define ALIGN_STATUS_OFFSET 24
#define HI_BER_OFFSET       25
#define BLOCK_LOCK_OFFSET   0
#define AM_LOCK_OFFSET      8
#define FEC_LOCK_OFFSET     16

#define DOES_PHY_STATE_MARKED(LOCK_OFFSET, SERDES_OFFSET) (pcs_phy_state & (1 << (SERDES_OFFSET + LOCK_OFFSET)))

    memset(kernel_info_p, 0, sizeof(*kernel_info_p));
    for (serdes_iter = 0; serdes_iter < NUMBER_OF_SERDESES; serdes_iter++) {
        if (DOES_PHY_STATE_MARKED(BLOCK_LOCK_OFFSET, serdes_iter)) {
            kernel_info_p->state_bitmap[serdes_iter] |= PCS_PHY_STATE_BLOCK_LOCK_E;
        }
        if (DOES_PHY_STATE_MARKED(AM_LOCK_OFFSET, serdes_iter)) {
            kernel_info_p->state_bitmap[serdes_iter] |= PCS_PHY_STATE_AM_LOCK_E;
        }
        if (DOES_PHY_STATE_MARKED(FEC_LOCK_OFFSET, serdes_iter)) {
            kernel_info_p->state_bitmap[serdes_iter] |= PCS_PHY_STATE_FEC_LOCK_E;
        }
    }

    kernel_info_p->hi_ber = DOES_PHY_STATE_MARKED(HI_BER_OFFSET, 0) ? TRUE : FALSE;
    kernel_info_p->align_state = DOES_PHY_STATE_MARKED(ALIGN_STATUS_OFFSET, 0) ? TRUE : FALSE;
}

static void __convert_pddr_speed_deg_db_to_kernel_info(struct pddr_speed_deg_db *kernel_info_p, uint32_t speed_deg_db)
{
    int serdes_iter = 0;

#define SPEED_DB_VALID_OFFSET               0
#define SPEED_DEG_SERDES_RX_DB_VALID_OFFSET 1
#define RX_REVERSAL_OFFSET                  4
#define TX_REVERSAL_OFFSET                  5
#define FAILED_QDR_OFFSET                   8
#define FAILED_FDR_OFFSET                   12
#define FAILED_EDR_OFFSET                   16
#define FAILED_PEER_TEST_OFFSET             20
#define FIRST_TEST_SPEED_OFFSET             27

#define DOES_FAILURE_MARKED(FAILURE_OFFSET, SERDES_OFFSET) (speed_deg_db & (1 << (SERDES_OFFSET + FAILURE_OFFSET)))


    memset(kernel_info_p, 0, sizeof(*kernel_info_p));
    for (serdes_iter = 0; serdes_iter < NUMBER_OF_SERDESES; serdes_iter++) {
        if (DOES_FAILURE_MARKED(FAILED_QDR_OFFSET, serdes_iter)) {
            kernel_info_p->lane_failure[serdes_iter] |= LANE_FAILURE_QDR_E;
        }
        if (DOES_FAILURE_MARKED(FAILED_FDR_OFFSET, serdes_iter)) {
            kernel_info_p->lane_failure[serdes_iter] |= LANE_FAILURE_FDR_E;
        }
        if (DOES_FAILURE_MARKED(FAILED_EDR_OFFSET, serdes_iter)) {
            kernel_info_p->lane_failure[serdes_iter] |= LANE_FAILURE_EDR_E;
        }
        if (DOES_FAILURE_MARKED(FAILED_PEER_TEST_OFFSET, serdes_iter)) {
            kernel_info_p->lane_failure[serdes_iter] |= LANE_FAILURE_PEER_TEST_E;
        }
    }
    kernel_info_p->speed_degr_db_valid = DOES_FAILURE_MARKED(SPEED_DB_VALID_OFFSET, 0) ? TRUE : FALSE;
    kernel_info_p->speed_degr_serdes_rx_db_valid =
        DOES_FAILURE_MARKED(SPEED_DEG_SERDES_RX_DB_VALID_OFFSET, 0) ? TRUE : FALSE;
    kernel_info_p->rx_reversal = DOES_FAILURE_MARKED(RX_REVERSAL_OFFSET, 0) ? TRUE : FALSE;
    kernel_info_p->tx_reversal = DOES_FAILURE_MARKED(TX_REVERSAL_OFFSET, 0) ? TRUE : FALSE;
    kernel_info_p->first_test_speed = DOES_FAILURE_MARKED(FIRST_TEST_SPEED_OFFSET, 0) ? TRUE : FALSE;
}

sxd_status_t convert_pddr_oper_info(sxd_emad_pddr_oper_info_t  *req_oper_info_p,
                                    struct pddr_oper_info_resp *user_kernel_info_p)
{
    user_kernel_info_p->port_neg_mode = ((neg_mode_t)(req_oper_info_p->proto_active_and_neg_mode_active & 0xF));
    user_kernel_info_p->port_protocol = ((req_oper_info_p->proto_active_and_neg_mode_active >> 4) & 0xF);
    user_kernel_info_p->phy_mgr_fsm_state = req_oper_info_p->phy_mngr_fsm_state;
    user_kernel_info_p->autoneg_fsm_state = req_oper_info_p->eth_an_fsm_state;
    user_kernel_info_p->ib_phy_fsm_state = req_oper_info_p->ib_phy_fsm_state;

    user_kernel_info_p->admin_state.ib_admin.phy_mgr_link_width_enabled = cl_ntoh16(
        req_oper_info_p->phy_manager_link_width_enabled);
    user_kernel_info_p->admin_state.ib_admin.phy_manager_link_proto_enabled = cl_ntoh16(
        req_oper_info_p->phy_manager_link_proto_enabled);
    user_kernel_info_p->admin_state.ib_admin.core_to_phy_link_width_enabled = cl_ntoh16(
        req_oper_info_p->core_to_phy_link_width_enabled);
    user_kernel_info_p->admin_state.ib_admin.core_to_phy_link_proto_enabled = cl_ntoh16(
        req_oper_info_p->core_to_phy_link_proto_enabled);
    user_kernel_info_p->admin_state.ib_admin.link_width_active = cl_ntoh16(req_oper_info_p->link_width_active);
    user_kernel_info_p->admin_state.ib_admin.link_speed_active = cl_ntoh16(req_oper_info_p->link_speed_active);
    user_kernel_info_p->cable_proto_cap = cl_ntoh32(req_oper_info_p->cable_proto_cap);

    user_kernel_info_p->retransmit_mode_active = ((retransmit_mode_t)req_oper_info_p->retran_mode_active);
    user_kernel_info_p->retransmit_mode_requested = ((retransmit_mode_t)req_oper_info_p->retran_mode_request);
    user_kernel_info_p->loopback_mode = ((loopback_mode_t)req_oper_info_p->loopback_mode);
    user_kernel_info_p->fec_mode_active = ((fec_mode_t)cl_ntoh16(req_oper_info_p->fec_mode_active));
    user_kernel_info_p->fec_mode_req = ((fec_mode_t)cl_ntoh16(req_oper_info_p->fec_mode_request));
    user_kernel_info_p->profile_fec_in_use = cl_ntoh16(req_oper_info_p->profile_fec_in_use);
    user_kernel_info_p->eth_25g_50g_fec_support = (req_oper_info_p->eth_fec_support >> 4) & 0xF;
    user_kernel_info_p->eth_100g_fec_support = req_oper_info_p->eth_fec_support & 0xF;

    return SXD_STATUS_SUCCESS;
}
