/*
 * Copyright (C) 2008-2022 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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
  
/*
 * THIS FILE IS AUTO GENERATED.
 * DO NOT MAKE ANY CHANGES!
 * They will be erased with next update.
 *
 */

#ifndef _MLXSW_REG_H
#define _MLXSW_REG_H

/* icsr
 * ----
 *
 */
#define MLXSW_ICSR_ID 0x38f0
#define MLXSW_ICSR_LEN 0x410

uint32_t mlxsw_reg_icsr_base_address_get(const char *buf);

void mlxsw_reg_icsr_base_address_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_icsr_num_reads_get(const char *buf);

void mlxsw_reg_icsr_num_reads_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_icsr_data_get(const char *buf, unsigned short index);

/* iicr
 * ----
 *
 */
#define MLXSW_IICR_ID 0x3811
#define MLXSW_IICR_LEN 0x24

uint8_t mlxsw_reg_iicr_kvh_mark_clear_get(const char *buf);

void mlxsw_reg_iicr_kvh_mark_clear_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_iicr_clear_mc_rtr_tcam_value_get(const char *buf);

void mlxsw_reg_iicr_clear_mc_rtr_tcam_value_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_iicr_clear_mc_rtr_tcam_mask_get(const char *buf);

void mlxsw_reg_iicr_clear_mc_rtr_tcam_mask_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_iicr_clear_pe_regions_value_get(const char *buf);

void mlxsw_reg_iicr_clear_pe_regions_value_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_iicr_clear_pe_regions_mask_get(const char *buf);

void mlxsw_reg_iicr_clear_pe_regions_mask_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_iicr_clear_rifs_value_get(const char *buf);

void mlxsw_reg_iicr_clear_rifs_value_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_iicr_clear_rifs_mask_get(const char *buf);

void mlxsw_reg_iicr_clear_rifs_mask_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_iicr_traps_2_default_get(const char *buf);

void mlxsw_reg_iicr_traps_2_default_set(char *buf, uint8_t val);

/* fpums
 * -----
 *
 */
#define MLXSW_FPUMS_ID 0x4801
#define MLXSW_FPUMS_LEN 0x50

uint8_t mlxsw_reg_fpums_global_get(const char *buf);

void mlxsw_reg_fpums_global_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fpums_local_port_get(const char *buf);

void mlxsw_reg_fpums_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fpums_lp_msb_get(const char *buf);

void mlxsw_reg_fpums_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fpums_mask_get(const char *buf);

void mlxsw_reg_fpums_mask_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fpums_port_user_mem_get(const char *buf);

void mlxsw_reg_fpums_port_user_mem_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_fpums_port_mask_get(const char *buf, unsigned short index);

void mlxsw_reg_fpums_port_mask_set(char *buf, unsigned short index, uint32_t val);

/* spevet
 * ------
 *
 */
#define MLXSW_SPEVET_ID 0x202a
#define MLXSW_SPEVET_LEN 0x8

uint8_t mlxsw_reg_spevet_local_port_get(const char *buf);

void mlxsw_reg_spevet_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_spevet_lp_msb_get(const char *buf);

void mlxsw_reg_spevet_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_spevet_et_vlan_get(const char *buf);

void mlxsw_reg_spevet_et_vlan_set(char *buf, uint8_t val);

/* igcr
 * ----
 *
 */
#define MLXSW_IGCR_ID 0x3801
#define MLXSW_IGCR_LEN 0x10

uint8_t mlxsw_reg_igcr_ddd_lpm_high_ipv6_get(const char *buf);

void mlxsw_reg_igcr_ddd_lpm_high_ipv6_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_igcr_ddd_lpm_high_ipv4_get(const char *buf);

void mlxsw_reg_igcr_ddd_lpm_high_ipv4_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_igcr_ddd_pe_actions_priority_get(const char *buf);

void mlxsw_reg_igcr_ddd_pe_actions_priority_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_igcr_pisbo_get(const char *buf);

void mlxsw_reg_igcr_pisbo_set(char *buf, uint8_t val);

/* pemrbt
 * ------
 *
 */
#define MLXSW_PEMRBT_ID 0x3014
#define MLXSW_PEMRBT_LEN 0x14

uint8_t mlxsw_reg_pemrbt_protocol_get(const char *buf);

void mlxsw_reg_pemrbt_protocol_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pemrbt_group_id_get(const char *buf);

void mlxsw_reg_pemrbt_group_id_set(char *buf, uint16_t val);

/* fphhc
 * -----
 *
 */
#define MLXSW_FPHHC_ID 0x4880
#define MLXSW_FPHHC_LEN 0xc

uint8_t mlxsw_reg_fphhc_hph_get(const char *buf);

void mlxsw_reg_fphhc_hph_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fphhc_my_ftlv_outer_en_get(const char *buf);

void mlxsw_reg_fphhc_my_ftlv_outer_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fphhc_my_ftlv_inner_en_get(const char *buf);

void mlxsw_reg_fphhc_my_ftlv_inner_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fphhc_my_ftlv_fpp_get(const char *buf);

void mlxsw_reg_fphhc_my_ftlv_fpp_set(char *buf, uint8_t val);

/* pecnee
 * ------
 *
 */
#define MLXSW_PECNEE_ID 0x3032
#define MLXSW_PECNEE_LEN 0x18

uint16_t mlxsw_reg_pecnee_region_id_get(const char *buf);

void mlxsw_reg_pecnee_region_id_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pecnee_region_id_mask_get(const char *buf);

void mlxsw_reg_pecnee_region_id_mask_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pecnee_erp_id_bitwise_get(const char *buf);

void mlxsw_reg_pecnee_erp_id_bitwise_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_pecnee_ctcam_get(const char *buf);

void mlxsw_reg_pecnee_ctcam_set(char *buf, uint8_t val);

/* mtmp
 * ----
 *
 */
#define MLXSW_MTMP_ID 0x900a
#define MLXSW_MTMP_LEN 0x20

uint8_t mlxsw_reg_mtmp_i_get(const char *buf);

void mlxsw_reg_mtmp_i_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtmp_ig_get(const char *buf);

void mlxsw_reg_mtmp_ig_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtmp_asic_index_get(const char *buf);

void mlxsw_reg_mtmp_asic_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtmp_slot_index_get(const char *buf);

void mlxsw_reg_mtmp_slot_index_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mtmp_sensor_index_get(const char *buf);

void mlxsw_reg_mtmp_sensor_index_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_mtmp_max_operational_temperature_get(const char *buf);

uint16_t mlxsw_reg_mtmp_temperature_get(const char *buf);

uint8_t mlxsw_reg_mtmp_mte_get(const char *buf);

void mlxsw_reg_mtmp_mte_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtmp_mtr_get(const char *buf);

void mlxsw_reg_mtmp_mtr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtmp_weme_get(const char *buf);

void mlxsw_reg_mtmp_weme_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtmp_sdme_get(const char *buf);

void mlxsw_reg_mtmp_sdme_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mtmp_max_temperature_get(const char *buf);

uint8_t mlxsw_reg_mtmp_tee_get(const char *buf);

void mlxsw_reg_mtmp_tee_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtmp_sdee_get(const char *buf);

void mlxsw_reg_mtmp_sdee_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mtmp_temperature_threshold_hi_get(const char *buf);

void mlxsw_reg_mtmp_temperature_threshold_hi_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_mtmp_temperature_threshold_lo_get(const char *buf);

void mlxsw_reg_mtmp_temperature_threshold_lo_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_mtmp_sensor_name_hi_get(const char *buf);

uint32_t mlxsw_reg_mtmp_sensor_name_lo_get(const char *buf);

/* tieem
 * -----
 *
 */
#define MLXSW_TIEEM_ID 0xa812
#define MLXSW_TIEEM_LEN 0xc

uint8_t mlxsw_reg_tieem_overlay_ecn_get(const char *buf);

void mlxsw_reg_tieem_overlay_ecn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tieem_underlay_ecn_get(const char *buf);

void mlxsw_reg_tieem_underlay_ecn_set(char *buf, uint8_t val);

/* pmsc
 * ----
 *
 */
#define MLXSW_PMSC_ID 0x501d
#define MLXSW_PMSC_LEN 0x40

uint32_t mlxsw_reg_pmsc_port_mapping_updated_get(const char *buf, unsigned short index);

void mlxsw_reg_pmsc_port_mapping_updated_set(char *buf, unsigned short index, uint32_t val);

/* mogcr
 * -----
 *
 */
#define MLXSW_MOGCR_ID 0x9086
#define MLXSW_MOGCR_LEN 0x20

uint8_t mlxsw_reg_mogcr_tele_managed_get(const char *buf);

void mlxsw_reg_mogcr_tele_managed_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mogcr_ptp_iftc_get(const char *buf);

void mlxsw_reg_mogcr_ptp_iftc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mogcr_ptp_eftc_get(const char *buf);

void mlxsw_reg_mogcr_ptp_eftc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mogcr_sid_get(const char *buf);

void mlxsw_reg_mogcr_sid_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mogcr_mirroring_pid_base_get(const char *buf);

void mlxsw_reg_mogcr_mirroring_pid_base_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_mogcr_mirror_latency_units_get(const char *buf);

void mlxsw_reg_mogcr_mirror_latency_units_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_mogcr_latency_histogram_units_get(const char *buf);

void mlxsw_reg_mogcr_latency_histogram_units_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mogcr_toc_fmt_get(const char *buf);

void mlxsw_reg_mogcr_toc_fmt_set(char *buf, uint8_t val);

/* rtdp
 * ----
 *
 */
#define MLXSW_RTDP_ID 0x8020
#define MLXSW_RTDP_LEN 0x44

uint8_t mlxsw_reg_rtdp_type_get(const char *buf);

void mlxsw_reg_rtdp_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rtdp_tunnel_index_get(const char *buf);

void mlxsw_reg_rtdp_tunnel_index_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_rtdp_rtdp_nve_decap_decap_disable_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_nve_decap_decap_disable_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_rtdp_rtdp_ipinip_irif_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_ipinip_irif_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_rtdp_rtdp_ipinip_sip_check_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_ipinip_sip_check_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rtdp_rtdp_ipinip_type_check_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_ipinip_type_check_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rtdp_rtdp_ipinip_gre_key_check_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_ipinip_gre_key_check_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rtdp_rtdp_ipinip_ipv4_usip_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_ipinip_ipv4_usip_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rtdp_rtdp_ipinip_ipv6_usip_ptr_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_ipinip_ipv6_usip_ptr_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rtdp_rtdp_ipinip_expected_gre_key_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_ipinip_expected_gre_key_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_rtdp_egress_router_interface_get(const char *buf);

void mlxsw_reg_rtdp_egress_router_interface_set(char *buf, uint16_t val);

/* pecner
 * ------
 *
 */
#define MLXSW_PECNER_ID 0x3033
#define MLXSW_PECNER_LEN 0x38

uint8_t mlxsw_reg_pecner_clear_get(const char *buf);

void mlxsw_reg_pecner_clear_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_pecner_erp_initial_high_get(const char *buf);

uint32_t mlxsw_reg_pecner_erp_initial_low_get(const char *buf);

uint32_t mlxsw_reg_pecner_erp_post_bf_high_get(const char *buf);

uint32_t mlxsw_reg_pecner_erp_post_bf_low_get(const char *buf);

uint32_t mlxsw_reg_pecner_erp_lookup_high_get(const char *buf);

uint32_t mlxsw_reg_pecner_erp_lookup_low_get(const char *buf);

uint32_t mlxsw_reg_pecner_erp_any_match_high_get(const char *buf);

uint32_t mlxsw_reg_pecner_erp_any_match_low_get(const char *buf);

uint32_t mlxsw_reg_pecner_erp_final_match_high_get(const char *buf);

uint32_t mlxsw_reg_pecner_erp_final_match_low_get(const char *buf);

/* ifbo
 * ----
 *
 */
#define MLXSW_IFBO_ID 0x3810
#define MLXSW_IFBO_LEN 0x28

uint8_t mlxsw_reg_ifbo_type_get(const char *buf);

void mlxsw_reg_ifbo_type_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ifbo_outer_header_enables_get(const char *buf);

void mlxsw_reg_ifbo_outer_header_enables_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_ifbo_outer_header_fields_enable_get(const char *buf, unsigned short index);

void mlxsw_reg_ifbo_outer_header_fields_enable_set(char *buf, unsigned short index, uint32_t val);

/* tneem
 * -----
 *
 */
#define MLXSW_TNEEM_ID 0xa012
#define MLXSW_TNEEM_LEN 0xc

uint8_t mlxsw_reg_tneem_overlay_ecn_get(const char *buf);

void mlxsw_reg_tneem_overlay_ecn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tneem_underlay_ecn_get(const char *buf);

void mlxsw_reg_tneem_underlay_ecn_set(char *buf, uint8_t val);

/* tnifr
 * -----
 *
 */
#define MLXSW_TNIFR_ID 0xa014
#define MLXSW_TNIFR_LEN 0x60

uint8_t mlxsw_reg_tnifr_tunnel_port_get(const char *buf);

void mlxsw_reg_tnifr_tunnel_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnifr_port_page_get(const char *buf);

void mlxsw_reg_tnifr_port_page_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tnifr_port_filter_get(const char *buf, unsigned short index);

void mlxsw_reg_tnifr_port_filter_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_tnifr_port_filter_update_en_get(const char *buf, unsigned short index);

void mlxsw_reg_tnifr_port_filter_update_en_set(char *buf, unsigned short index, uint32_t val);

/* peaps
 * -----
 *
 */
#define MLXSW_PEAPS_ID 0x302d
#define MLXSW_PEAPS_LEN 0x34

uint8_t mlxsw_reg_peaps_busy_get(const char *buf);

uint8_t mlxsw_reg_peaps_ovf_get(const char *buf);

void mlxsw_reg_peaps_ct_offset_set(char *buf, uint16_t val);

void mlxsw_reg_peaps_ct_size_set(char *buf, uint16_t val);

void mlxsw_reg_peaps_tcam_region_info_memcpy_to(char *buf, const char *src);

void mlxsw_reg_peaps_priority_start_set(char *buf, uint32_t val);

void mlxsw_reg_peaps_priority_end_set(char *buf, uint32_t val);

void mlxsw_reg_peaps_priority_inc_set(char *buf, uint32_t val);

/* pmpe
 * ----
 *
 */
#define MLXSW_PMPE_ID 0x5024
#define MLXSW_PMPE_LEN 0x10

uint8_t mlxsw_reg_pmpe_slot_index_get(const char *buf);

void mlxsw_reg_pmpe_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpe_module_get(const char *buf);

void mlxsw_reg_pmpe_module_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpe_module_status_get(const char *buf);

uint8_t mlxsw_reg_pmpe_error_type_get(const char *buf);

/* hcot
 * ----
 *
 */
#define MLXSW_HCOT_ID 0x7087
#define MLXSW_HCOT_LEN 0x30

uint16_t mlxsw_reg_hcot_trap_id_get(const char *buf);

void mlxsw_reg_hcot_trap_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_hcot_key_type_get(const char *buf);

void mlxsw_reg_hcot_key_type_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_hcot_key_hcot_key_ethernet_ethertype_get(const char *buf);

void mlxsw_reg_hcot_key_hcot_key_ethernet_ethertype_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_hcot_key_hcot_key_ethernet_tunnel_port_get(const char *buf);

void mlxsw_reg_hcot_key_hcot_key_ethernet_tunnel_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_key_hcot_key_next_proto_is_ipv4_get(const char *buf);

void mlxsw_reg_hcot_key_hcot_key_next_proto_is_ipv4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_key_hcot_key_next_proto_ip_proto_get(const char *buf);

void mlxsw_reg_hcot_key_hcot_key_next_proto_ip_proto_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_key_hcot_key_next_proto_tunnel_port_get(const char *buf);

void mlxsw_reg_hcot_key_hcot_key_next_proto_tunnel_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_key_hcot_key_layer4_port_is_udp_get(const char *buf);

void mlxsw_reg_hcot_key_hcot_key_layer4_port_is_udp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_key_hcot_key_layer4_port_is_ipv4_get(const char *buf);

void mlxsw_reg_hcot_key_hcot_key_layer4_port_is_ipv4_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_hcot_key_hcot_key_layer4_port_l4_port_get(const char *buf);

void mlxsw_reg_hcot_key_hcot_key_layer4_port_l4_port_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_hcot_key_hcot_key_layer4_port_tunnel_port_get(const char *buf);

void mlxsw_reg_hcot_key_hcot_key_layer4_port_tunnel_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_key_hcot_key_icmp_igmp_type_is_igmp_get(const char *buf);

void mlxsw_reg_hcot_key_hcot_key_icmp_igmp_type_is_igmp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_key_hcot_key_icmp_igmp_type_is_ipv4_get(const char *buf);

void mlxsw_reg_hcot_key_hcot_key_icmp_igmp_type_is_ipv4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_key_hcot_key_icmp_igmp_type_max_get(const char *buf);

void mlxsw_reg_hcot_key_hcot_key_icmp_igmp_type_max_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_key_hcot_key_icmp_igmp_type_min_get(const char *buf);

void mlxsw_reg_hcot_key_hcot_key_icmp_igmp_type_min_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_key_hcot_key_icmp_igmp_type_tunnel_port_get(const char *buf);

void mlxsw_reg_hcot_key_hcot_key_icmp_igmp_type_tunnel_port_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_hcot_mask_hcot_key_ethernet_ethertype_get(const char *buf);

void mlxsw_reg_hcot_mask_hcot_key_ethernet_ethertype_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_hcot_mask_hcot_key_ethernet_tunnel_port_get(const char *buf);

void mlxsw_reg_hcot_mask_hcot_key_ethernet_tunnel_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_mask_hcot_key_next_proto_is_ipv4_get(const char *buf);

void mlxsw_reg_hcot_mask_hcot_key_next_proto_is_ipv4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_mask_hcot_key_next_proto_ip_proto_get(const char *buf);

void mlxsw_reg_hcot_mask_hcot_key_next_proto_ip_proto_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_mask_hcot_key_next_proto_tunnel_port_get(const char *buf);

void mlxsw_reg_hcot_mask_hcot_key_next_proto_tunnel_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_mask_hcot_key_layer4_port_is_udp_get(const char *buf);

void mlxsw_reg_hcot_mask_hcot_key_layer4_port_is_udp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_mask_hcot_key_layer4_port_is_ipv4_get(const char *buf);

void mlxsw_reg_hcot_mask_hcot_key_layer4_port_is_ipv4_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_hcot_mask_hcot_key_layer4_port_l4_port_get(const char *buf);

void mlxsw_reg_hcot_mask_hcot_key_layer4_port_l4_port_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_hcot_mask_hcot_key_layer4_port_tunnel_port_get(const char *buf);

void mlxsw_reg_hcot_mask_hcot_key_layer4_port_tunnel_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_mask_hcot_key_icmp_igmp_type_is_igmp_get(const char *buf);

void mlxsw_reg_hcot_mask_hcot_key_icmp_igmp_type_is_igmp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_mask_hcot_key_icmp_igmp_type_is_ipv4_get(const char *buf);

void mlxsw_reg_hcot_mask_hcot_key_icmp_igmp_type_is_ipv4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_mask_hcot_key_icmp_igmp_type_max_get(const char *buf);

void mlxsw_reg_hcot_mask_hcot_key_icmp_igmp_type_max_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_mask_hcot_key_icmp_igmp_type_min_get(const char *buf);

void mlxsw_reg_hcot_mask_hcot_key_icmp_igmp_type_min_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcot_mask_hcot_key_icmp_igmp_type_tunnel_port_get(const char *buf);

void mlxsw_reg_hcot_mask_hcot_key_icmp_igmp_type_tunnel_port_set(char *buf, uint8_t val);

/* chltm
 * -----
 *
 */
#define MLXSW_CHLTM_ID 0x2811
#define MLXSW_CHLTM_LEN 0x14

uint8_t mlxsw_reg_chltm_local_port_get(const char *buf);

void mlxsw_reg_chltm_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_chltm_lp_msb_get(const char *buf);

void mlxsw_reg_chltm_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_chltm_traffic_class_get(const char *buf);

void mlxsw_reg_chltm_traffic_class_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_chltm_hlt_table_pointer_get(const char *buf);

void mlxsw_reg_chltm_hlt_table_pointer_set(char *buf, uint8_t val);

/* mafti
 * -----
 *
 */
#define MLXSW_MAFTI_ID 0x908b
#define MLXSW_MAFTI_RECORD_BASE_LEN 0x08 /* base length, without records */
#define MLXSW_MAFTI_RECORD_REC_LEN 0x0c /* record length */
#define MLXSW_MAFTI_RECORD_REC_MAX_COUNT 64
#define MLXSW_MAFTI_LEN 0x308

uint8_t mlxsw_reg_mafti_bank_id_get(const char *buf);

uint8_t mlxsw_reg_mafti_num_rec_get(const char *buf);

uint32_t mlxsw_reg_mafti_counter_index_get(const char *buf, unsigned short index);

uint32_t mlxsw_reg_mafti_bytes_inc_get(const char *buf, unsigned short index);

uint32_t mlxsw_reg_mafti_packets_inc_get(const char *buf, unsigned short index);

/* hmon
 * ----
 *
 */
#define MLXSW_HMON_ID 0x7084
#define MLXSW_HMON_WQE_OVERFLOW_RDQ_BASE_LEN 0x20 /* base length, without records */
#define MLXSW_HMON_WQE_OVERFLOW_RDQ_REC_LEN 0x08 /* record length */
#define MLXSW_HMON_WQE_OVERFLOW_RDQ_REC_MAX_COUNT 64
#define MLXSW_HMON_LEN 0x220

uint8_t mlxsw_reg_hmon_clr_get(const char *buf);

void mlxsw_reg_hmon_clr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hmon_cprdq_get(const char *buf);

void mlxsw_reg_hmon_cprdq_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hmon_crdq_get(const char *buf);

void mlxsw_reg_hmon_crdq_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hmon_wqe_of_wrap_get(const char *buf);

uint32_t mlxsw_reg_hmon_wqe_overflow_high_get(const char *buf);

uint32_t mlxsw_reg_hmon_wqe_overflow_low_get(const char *buf);

uint32_t mlxsw_reg_hmon_hi_get(const char *buf, unsigned short index);

void mlxsw_reg_hmon_hi_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_hmon_lo_get(const char *buf, unsigned short index);

void mlxsw_reg_hmon_lo_set(char *buf, unsigned short index, uint32_t val);

/* mgpir
 * -----
 *
 */
#define MLXSW_MGPIR_ID 0x9100
#define MLXSW_MGPIR_LEN 0xa0

uint8_t mlxsw_reg_mgpir_slot_index_get(const char *buf);

void mlxsw_reg_mgpir_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mgpir_device_type_get(const char *buf);

uint8_t mlxsw_reg_mgpir_devices_per_flash_get(const char *buf);

uint8_t mlxsw_reg_mgpir_num_of_devices_get(const char *buf);

uint8_t mlxsw_reg_mgpir_num_of_slots_get(const char *buf);

uint8_t mlxsw_reg_mgpir_num_of_modules_get(const char *buf);

/* peapbl
 * ------
 *
 */
#define MLXSW_PEAPBL_ID 0x3024
#define MLXSW_PEAPBL_LEN 0x20

uint16_t mlxsw_reg_peapbl_region_id_get(const char *buf);

void mlxsw_reg_peapbl_region_id_set(char *buf, uint16_t val);

void mlxsw_reg_peapbl_c_s_set(char *buf, uint8_t val);

void mlxsw_reg_peapbl_pruning_ctcam_cs_set(char *buf, uint8_t val);

void mlxsw_reg_peapbl_num_rec_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_peapbl_erp_id_get(const char *buf);

void mlxsw_reg_peapbl_erp_id_set(char *buf, uint8_t val);

void mlxsw_reg_peapbl_pruning_vector_cs_set(char *buf, uint16_t val);

/* peapbm
 * ------
 *
 */
#define MLXSW_PEAPBM_ID 0x3025
#define MLXSW_PEAPBM_LEN 0xf8

uint16_t mlxsw_reg_peapbm_region_id_get(const char *buf);

void mlxsw_reg_peapbm_region_id_set(char *buf, uint16_t val);

void mlxsw_reg_peapbm_c_s_set(char *buf, uint8_t val);

void mlxsw_reg_peapbm_pruning_ctcam_cs_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_peapbm_erp_id_mask_get(const char *buf);

void mlxsw_reg_peapbm_erp_id_mask_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_peapbm_erp_id_get(const char *buf);

void mlxsw_reg_peapbm_erp_id_set(char *buf, uint8_t val);

void mlxsw_reg_peapbm_pruning_vector_cs_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_peapbm_priority_start_get(const char *buf);

void mlxsw_reg_peapbm_priority_start_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_peapbm_priority_end_get(const char *buf);

void mlxsw_reg_peapbm_priority_end_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_peapbm_key_get(const char *buf, unsigned short index);

void mlxsw_reg_peapbm_key_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_peapbm_key_mask_get(const char *buf, unsigned short index);

void mlxsw_reg_peapbm_key_mask_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_peapbm_large_entry_key_id_get(const char *buf);

void mlxsw_reg_peapbm_large_entry_key_id_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_peapbm_large_entry_key_id_mask_get(const char *buf);

void mlxsw_reg_peapbm_large_entry_key_id_mask_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_peapbm_delta_start_get(const char *buf);

void mlxsw_reg_peapbm_delta_start_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_peapbm_delta_mask_get(const char *buf);

void mlxsw_reg_peapbm_delta_mask_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_peapbm_delta_value_get(const char *buf);

void mlxsw_reg_peapbm_delta_value_set(char *buf, uint8_t val);

/* pmtm
 * ----
 *
 */
#define MLXSW_PMTM_ID 0x5067
#define MLXSW_PMTM_LEN 0x10

uint8_t mlxsw_reg_pmtm_slot_index_get(const char *buf);

void mlxsw_reg_pmtm_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmtm_module_get(const char *buf);

void mlxsw_reg_pmtm_module_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmtm_module_width_get(const char *buf);

void mlxsw_reg_pmtm_module_width_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmtm_module_type_get(const char *buf);

void mlxsw_reg_pmtm_module_type_set(char *buf, uint8_t val);

/* tnqdr
 * -----
 *
 */
#define MLXSW_TNQDR_ID 0xa011
#define MLXSW_TNQDR_LEN 0x8

uint8_t mlxsw_reg_tnqdr_local_port_get(const char *buf);

void mlxsw_reg_tnqdr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnqdr_lp_msb_get(const char *buf);

void mlxsw_reg_tnqdr_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnqdr_color_get(const char *buf);

void mlxsw_reg_tnqdr_color_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnqdr_switch_prio_get(const char *buf);

void mlxsw_reg_tnqdr_switch_prio_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnqdr_dscp_get(const char *buf);

void mlxsw_reg_tnqdr_dscp_set(char *buf, uint8_t val);

/* sffp
 * ----
 *
 */
#define MLXSW_SFFP_ID 0x2029
#define MLXSW_SFFP_LEN 0x8

uint8_t mlxsw_reg_sffp_profile_id_get(const char *buf);

void mlxsw_reg_sffp_profile_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sffp_type_get(const char *buf);

void mlxsw_reg_sffp_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sffp_flood_offset_get(const char *buf);

void mlxsw_reg_sffp_flood_offset_set(char *buf, uint8_t val);

/* mpcir
 * -----
 *
 */
#define MLXSW_MPCIR_ID 0x905a
#define MLXSW_MPCIR_LEN 0x10

uint8_t mlxsw_reg_mpcir_all_get(const char *buf);

void mlxsw_reg_mpcir_all_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpcir_gearbox_get(const char *buf);

void mlxsw_reg_mpcir_gearbox_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpcir_leds_get(const char *buf);

void mlxsw_reg_mpcir_leds_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpcir_voltage_current_get(const char *buf);

void mlxsw_reg_mpcir_voltage_current_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpcir_power_get(const char *buf);

void mlxsw_reg_mpcir_power_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpcir_fans_get(const char *buf);

void mlxsw_reg_mpcir_fans_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpcir_thermal_get(const char *buf);

void mlxsw_reg_mpcir_thermal_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpcir_module_mng_get(const char *buf);

void mlxsw_reg_mpcir_module_mng_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpcir_cpld_get(const char *buf);

void mlxsw_reg_mpcir_cpld_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpcir_ports_get(const char *buf);

void mlxsw_reg_mpcir_ports_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpcir_gearbox_stat_get(const char *buf);

uint8_t mlxsw_reg_mpcir_leds_stat_get(const char *buf);

uint8_t mlxsw_reg_mpcir_voltage_current_stat_get(const char *buf);

uint8_t mlxsw_reg_mpcir_power_stat_get(const char *buf);

uint8_t mlxsw_reg_mpcir_fans_stat_get(const char *buf);

uint8_t mlxsw_reg_mpcir_thermal_stat_get(const char *buf);

uint8_t mlxsw_reg_mpcir_module_mng_stat_get(const char *buf);

uint8_t mlxsw_reg_mpcir_cpld_stat_get(const char *buf);

uint8_t mlxsw_reg_mpcir_ports_stat_get(const char *buf);

/* pter
 * ----
 *
 */
#define MLXSW_PTER_ID 0x5055
#define MLXSW_PTER_LEN 0x20

uint8_t mlxsw_reg_pter_error_page_get(const char *buf);

void mlxsw_reg_pter_error_page_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pter_local_port_get(const char *buf);

void mlxsw_reg_pter_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pter_pnat_get(const char *buf);

void mlxsw_reg_pter_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pter_lp_msb_get(const char *buf);

void mlxsw_reg_pter_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pter_port_type_get(const char *buf);

void mlxsw_reg_pter_port_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pter_status_get(const char *buf);

uint8_t mlxsw_reg_pter_pter_phy_page_reg_error_type_oper_get(const char *buf);

uint8_t mlxsw_reg_pter_pter_phy_page_reg_error_type_cap_get(const char *buf);

uint8_t mlxsw_reg_pter_pter_phy_page_reg_error_type_admin_get(const char *buf);

void mlxsw_reg_pter_pter_phy_page_reg_error_type_admin_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_pter_pter_phy_page_reg_error_injection_time_get(const char *buf);

void mlxsw_reg_pter_pter_phy_page_reg_error_injection_time_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_pter_pter_phy_page_reg_ber_mantissa_get(const char *buf);

void mlxsw_reg_pter_pter_phy_page_reg_ber_mantissa_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pter_pter_phy_page_reg_ber_exp_get(const char *buf);

void mlxsw_reg_pter_pter_phy_page_reg_ber_exp_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pter_pter_phy_page_reg_rs_symbol_errors_get(const char *buf);

void mlxsw_reg_pter_pter_phy_page_reg_rs_symbol_errors_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pter_pter_phy_page_reg_rs_errors_interval_get(const char *buf);

void mlxsw_reg_pter_pter_phy_page_reg_rs_errors_interval_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_pter_pter_port_page_reg_error_type_cap_get(const char *buf);

uint8_t mlxsw_reg_pter_pter_port_page_reg_error_type_admin_get(const char *buf);

void mlxsw_reg_pter_pter_port_page_reg_error_type_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pter_pter_port_page_reg_error_count_get(const char *buf);

void mlxsw_reg_pter_pter_port_page_reg_error_count_set(char *buf, uint8_t val);

/* smpu
 * ----
 *
 */
#define MLXSW_SMPU_ID 0x2006
#define MLXSW_SMPU_LEN 0x410

uint8_t mlxsw_reg_smpu_swid_get(const char *buf);

void mlxsw_reg_smpu_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_smpu_local_port_get(const char *buf);

void mlxsw_reg_smpu_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_smpu_lp_msb_get(const char *buf);

void mlxsw_reg_smpu_lp_msb_set(char *buf, uint8_t val);

void mlxsw_reg_smpu_op_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_smpu_size_get(const char *buf);

void mlxsw_reg_smpu_size_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_smpu_mid_get(const char *buf, unsigned short index);

void mlxsw_reg_smpu_mid_set(char *buf, unsigned short index, uint16_t val);

/* cegcr
 * -----
 *
 */
#define MLXSW_CEGCR_ID 0x2820
#define MLXSW_CEGCR_LEN 0x20

uint8_t mlxsw_reg_cegcr_f2e_get(const char *buf);

void mlxsw_reg_cegcr_f2e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cegcr_sticky_get(const char *buf);

void mlxsw_reg_cegcr_sticky_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_cegcr_max_floating_time_get(const char *buf);

void mlxsw_reg_cegcr_max_floating_time_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_cegcr_reference_rate_get(const char *buf);

void mlxsw_reg_cegcr_reference_rate_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_cegcr_elephants_thr_get(const char *buf);

void mlxsw_reg_cegcr_elephants_thr_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_cegcr_elephants_max_thr_get(const char *buf);

void mlxsw_reg_cegcr_elephants_max_thr_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_cegcr_mice_thr_get(const char *buf);

void mlxsw_reg_cegcr_mice_thr_set(char *buf, uint32_t val);

/* pmmp
 * ----
 *
 */
#define MLXSW_PMMP_ID 0x5044
#define MLXSW_PMMP_LEN 0x28

uint8_t mlxsw_reg_pmmp_slot_index_get(const char *buf);

void mlxsw_reg_pmmp_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_module_get(const char *buf);

void mlxsw_reg_pmmp_module_set(char *buf, uint8_t val);

void mlxsw_reg_pmmp_eeprom_override_mask_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pmmp_eeprom_override_get(const char *buf);

void mlxsw_reg_pmmp_eeprom_override_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_pmmp_qsfp_cable_protocol_technology_get(const char *buf, unsigned short index);

void mlxsw_reg_pmmp_qsfp_cable_protocol_technology_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_pmmp_sfp_cable_protocol_technology_get(const char *buf, unsigned short index);

void mlxsw_reg_pmmp_sfp_cable_protocol_technology_set(char *buf, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_pmmp_cable_length_get(const char *buf);

void mlxsw_reg_pmmp_cable_length_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_attenuation_25g_get(const char *buf);

void mlxsw_reg_pmmp_attenuation_25g_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_attenuation_12g_get(const char *buf);

void mlxsw_reg_pmmp_attenuation_12g_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_attenuation_7g_get(const char *buf);

void mlxsw_reg_pmmp_attenuation_7g_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_attenuation_5g_get(const char *buf);

void mlxsw_reg_pmmp_attenuation_5g_set(char *buf, uint8_t val);

/* pecnrr
 * ------
 *
 */
#define MLXSW_PECNRR_ID 0x3031
#define MLXSW_PECNRR_LEN 0x20

uint8_t mlxsw_reg_pecnrr_clear_get(const char *buf);

void mlxsw_reg_pecnrr_clear_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_pecnrr_tcam_trigger_high_get(const char *buf);

uint32_t mlxsw_reg_pecnrr_tcam_trigger_low_get(const char *buf);

uint32_t mlxsw_reg_pecnrr_tcam_full_lookup_high_get(const char *buf);

uint32_t mlxsw_reg_pecnrr_tcam_full_lookup_low_get(const char *buf);

/* ptcead
 * ------
 *
 */
#define MLXSW_PTCEAD_ID 0x3028
#define MLXSW_PTCEAD_LEN 0x220

uint8_t mlxsw_reg_ptcead_op_get(const char *buf);

void mlxsw_reg_ptcead_op_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ptcead_offset_get(const char *buf);

void mlxsw_reg_ptcead_offset_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ptcead_num_rec_get(const char *buf);

void mlxsw_reg_ptcead_num_rec_set(char *buf, uint16_t val);

void mlxsw_reg_ptcead_tcam_region_info_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_ptcead_tcam_region_info_memcpy_to(char *buf, const char *src);

uint32_t mlxsw_reg_ptcead_activity_vector_get(const char *buf, unsigned short index);

/* fpftt
 * -----
 *
 */
#define MLXSW_FPFTT_ID 0x4882
#define MLXSW_FPFTT_LEN 0x14

uint8_t mlxsw_reg_fpftt_entry_index_get(const char *buf);

void mlxsw_reg_fpftt_entry_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fpftt_tran_en_get(const char *buf);

void mlxsw_reg_fpftt_tran_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fpftt_cur_ph_get(const char *buf);

void mlxsw_reg_fpftt_cur_ph_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_fpftt_next_protocol_value_get(const char *buf);

void mlxsw_reg_fpftt_next_protocol_value_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_fpftt_next_ph_inner_get(const char *buf);

void mlxsw_reg_fpftt_next_ph_inner_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fpftt_next_ph_get(const char *buf);

void mlxsw_reg_fpftt_next_ph_set(char *buf, uint8_t val);

/* mddq
 * ----
 *
 */
#define MLXSW_MDDQ_ID 0x9161
#define MLXSW_MDDQ_LEN 0x30

uint8_t mlxsw_reg_mddq_sie_get(const char *buf);

void mlxsw_reg_mddq_sie_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddq_query_type_get(const char *buf);

void mlxsw_reg_mddq_query_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddq_slot_index_get(const char *buf);

void mlxsw_reg_mddq_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddq_response_message_sequence_get(const char *buf);

uint8_t mlxsw_reg_mddq_request_message_sequence_get(const char *buf);

void mlxsw_reg_mddq_request_message_sequence_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddq_data_valid_get(const char *buf);

uint8_t mlxsw_reg_mddq_query_index_get(const char *buf);

void mlxsw_reg_mddq_query_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddq_slot_info_provisioned_get(const char *buf);

uint8_t mlxsw_reg_mddq_slot_info_sr_valid_get(const char *buf);

uint8_t mlxsw_reg_mddq_slot_info_lc_ready_get(const char *buf);

uint8_t mlxsw_reg_mddq_slot_info_active_get(const char *buf);

uint16_t mlxsw_reg_mddq_slot_info_hw_revision_get(const char *buf);

uint16_t mlxsw_reg_mddq_slot_info_ini_file_version_get(const char *buf);

uint8_t mlxsw_reg_mddq_slot_info_card_type_get(const char *buf);

uint8_t mlxsw_reg_mddq_device_info_uses_flash_get(const char *buf);

uint8_t mlxsw_reg_mddq_device_info_flash_owner_get(const char *buf);

uint8_t mlxsw_reg_mddq_device_info_thermal_sd_get(const char *buf);

uint8_t mlxsw_reg_mddq_device_info_lc_pwr_on_get(const char *buf);

uint8_t mlxsw_reg_mddq_device_info_flash_id_get(const char *buf);

uint8_t mlxsw_reg_mddq_device_info_device_index_get(const char *buf);

uint16_t mlxsw_reg_mddq_device_info_fw_major_get(const char *buf);

uint16_t mlxsw_reg_mddq_device_info_device_type_get(const char *buf);

uint16_t mlxsw_reg_mddq_device_info_fw_minor_get(const char *buf);

uint16_t mlxsw_reg_mddq_device_info_fw_sub_minor_get(const char *buf);

uint8_t mlxsw_reg_mddq_device_info_max_cmd_read_size_supp_get(const char *buf);

uint8_t mlxsw_reg_mddq_device_info_max_cmd_write_size_supp_get(const char *buf);

uint32_t mlxsw_reg_mddq_slot_name_slot_ascii_name_get(const char *buf, unsigned short index);

/* tnpc
 * ----
 *
 */
#define MLXSW_TNPC_ID 0xa020
#define MLXSW_TNPC_LEN 0x1c

uint8_t mlxsw_reg_tnpc_tunnel_port_get(const char *buf);

void mlxsw_reg_tnpc_tunnel_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnpc_learn_enable_v4_get(const char *buf);

void mlxsw_reg_tnpc_learn_enable_v4_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tnpc_lb_tx_uc_tunnel_port_get(const char *buf);

void mlxsw_reg_tnpc_lb_tx_uc_tunnel_port_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_tnpc_lb_tx_mc_tunnel_port_get(const char *buf);

void mlxsw_reg_tnpc_lb_tx_mc_tunnel_port_set(char *buf, uint32_t val);

/* pecnre
 * ------
 *
 */
#define MLXSW_PECNRE_ID 0x3030
#define MLXSW_PECNRE_LEN 0x10

uint16_t mlxsw_reg_pecnre_region_id_get(const char *buf);

void mlxsw_reg_pecnre_region_id_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pecnre_region_id_mask_get(const char *buf);

void mlxsw_reg_pecnre_region_id_mask_set(char *buf, uint16_t val);

/* mofs
 * ----
 *
 */
#define MLXSW_MOFS_ID 0x90f8
#define MLXSW_MOFS_LEN 0x18

uint8_t mlxsw_reg_mofs_type_get(const char *buf);

void mlxsw_reg_mofs_type_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mofs_register_id_get(const char *buf);

void mlxsw_reg_mofs_register_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mofs_section_id_get(const char *buf);

void mlxsw_reg_mofs_section_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mofs_en_get(const char *buf);

void mlxsw_reg_mofs_en_set(char *buf, uint8_t val);

void mlxsw_reg_mofs_action_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mofs_reg_status_get(const char *buf);

/* ralcm
 * -----
 *
 */
#define MLXSW_RALCM_ID 0x8017
#define MLXSW_RALCM_LEN 0x4

uint16_t mlxsw_reg_ralcm_virtual_router_get(const char *buf);

void mlxsw_reg_ralcm_virtual_router_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_ralcm_protocol_get(const char *buf);

void mlxsw_reg_ralcm_protocol_set(char *buf, uint8_t val);

/* mgir
 * ----
 *
 */
#define MLXSW_MGIR_ID 0x9020
#define MLXSW_MGIR_LEN 0xa0

uint16_t mlxsw_reg_mgir_device_hw_revision_get(const char *buf);

uint16_t mlxsw_reg_mgir_device_id_get(const char *buf);

uint8_t mlxsw_reg_mgir_num_ports_get(const char *buf);

uint8_t mlxsw_reg_mgir_technology_get(const char *buf);

uint8_t mlxsw_reg_mgir_pvs_get(const char *buf);

uint16_t mlxsw_reg_mgir_hw_dev_id_get(const char *buf);

void mlxsw_reg_mgir_manufacturing_base_mac_memcpy_from(const char *buf, char *dst);

uint32_t mlxsw_reg_mgir_uptime_get(const char *buf);

uint8_t mlxsw_reg_mgir_fw_info_string_tlv_get(const char *buf);

uint8_t mlxsw_reg_mgir_fw_info_dev_get(const char *buf);

uint8_t mlxsw_reg_mgir_fw_info_debug_get(const char *buf);

uint8_t mlxsw_reg_mgir_fw_info_signed_fw_get(const char *buf);

uint8_t mlxsw_reg_mgir_fw_info_secured_get(const char *buf);

uint8_t mlxsw_reg_mgir_fw_info_major_get(const char *buf);

uint8_t mlxsw_reg_mgir_fw_info_minor_get(const char *buf);

uint8_t mlxsw_reg_mgir_fw_info_sub_minor_get(const char *buf);

uint32_t mlxsw_reg_mgir_fw_info_build_id_get(const char *buf);

uint8_t mlxsw_reg_mgir_fw_info_month_get(const char *buf);

uint8_t mlxsw_reg_mgir_fw_info_day_get(const char *buf);

uint16_t mlxsw_reg_mgir_fw_info_year_get(const char *buf);

uint16_t mlxsw_reg_mgir_fw_info_hour_get(const char *buf);

void mlxsw_reg_mgir_fw_info_psid_memcpy_from(const char *buf, char *dst);

uint32_t mlxsw_reg_mgir_fw_info_ini_file_version_get(const char *buf);

uint32_t mlxsw_reg_mgir_fw_info_extended_major_get(const char *buf);

uint32_t mlxsw_reg_mgir_fw_info_extended_minor_get(const char *buf);

uint32_t mlxsw_reg_mgir_fw_info_extended_sub_minor_get(const char *buf);

uint16_t mlxsw_reg_mgir_fw_info_isfu_major_get(const char *buf);

uint8_t mlxsw_reg_mgir_fw_info_sec_boot_get(const char *buf);

uint8_t mlxsw_reg_mgir_fw_info_life_cycle_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_major_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_minor_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_sub_minor_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom0_arch_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom0_type_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom1_arch_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom1_type_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom2_arch_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom2_type_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom3_arch_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom3_type_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom0_version_major_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom0_version_minor_get(const char *buf);

uint16_t mlxsw_reg_mgir_sw_info_rom0_version_build_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom1_version_major_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom1_version_minor_get(const char *buf);

uint16_t mlxsw_reg_mgir_sw_info_rom1_version_build_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom2_version_major_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom2_version_minor_get(const char *buf);

uint16_t mlxsw_reg_mgir_sw_info_rom2_version_build_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom3_version_major_get(const char *buf);

uint8_t mlxsw_reg_mgir_sw_info_rom3_version_minor_get(const char *buf);

uint16_t mlxsw_reg_mgir_sw_info_rom3_version_build_get(const char *buf);

void mlxsw_reg_mgir_dev_branch_tag_memcpy_from(const char *buf, char *dst);

/* tidem
 * -----
 *
 */
#define MLXSW_TIDEM_ID 0xa813
#define MLXSW_TIDEM_LEN 0xc

uint8_t mlxsw_reg_tidem_underlay_ecn_get(const char *buf);

void mlxsw_reg_tidem_underlay_ecn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tidem_overlay_ecn_get(const char *buf);

void mlxsw_reg_tidem_overlay_ecn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tidem_eip_ecn_get(const char *buf);

void mlxsw_reg_tidem_eip_ecn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tidem_trap_en_get(const char *buf);

void mlxsw_reg_tidem_trap_en_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_tidem_trap_id_get(const char *buf);

void mlxsw_reg_tidem_trap_id_set(char *buf, uint16_t val);

/* tigcr
 * -----
 *
 */
#define MLXSW_TIGCR_ID 0xa801
#define MLXSW_TIGCR_LEN 0x18

uint8_t mlxsw_reg_tigcr_ipip_ttlc_get(const char *buf);

void mlxsw_reg_tigcr_ipip_ttlc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tigcr_ipip_ttl_uc_get(const char *buf);

void mlxsw_reg_tigcr_ipip_ttl_uc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tigcr_ipip_flc_get(const char *buf);

void mlxsw_reg_tigcr_ipip_flc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tigcr_ipip_flh_get(const char *buf);

void mlxsw_reg_tigcr_ipip_flh_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tigcr_ipip_fl_prefix_get(const char *buf);

void mlxsw_reg_tigcr_ipip_fl_prefix_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_tigcr_ipip_fl_suffix_get(const char *buf);

void mlxsw_reg_tigcr_ipip_fl_suffix_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tigcr_ipip_gre_key_for_hash_get(const char *buf);

void mlxsw_reg_tigcr_ipip_gre_key_for_hash_set(char *buf, uint32_t val);

/* rlcmld
 * ------
 *
 */
#define MLXSW_RLCMLD_ID 0x8055
#define MLXSW_RLCMLD_LEN 0x30

uint8_t mlxsw_reg_rlcmld_select_get(const char *buf);

void mlxsw_reg_rlcmld_select_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rlcmld_filter_fields_get(const char *buf);

void mlxsw_reg_rlcmld_filter_fields_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rlcmld_m_idx_get(const char *buf);

void mlxsw_reg_rlcmld_m_idx_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rlcmld_protocol_get(const char *buf);

void mlxsw_reg_rlcmld_protocol_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_rlcmld_virtual_router_get(const char *buf);

void mlxsw_reg_rlcmld_virtual_router_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_rlcmld_dip_get(const char *buf, unsigned short index);

void mlxsw_reg_rlcmld_dip_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_rlcmld_dip_mask_get(const char *buf, unsigned short index);

void mlxsw_reg_rlcmld_dip_mask_set(char *buf, unsigned short index, uint32_t val);

/* ceer
 * ----
 *
 */
#define MLXSW_CEER_ID 0x2823
#define MLXSW_CEER_LEN 0xa0

uint8_t mlxsw_reg_ceer_clear_get(const char *buf);

void mlxsw_reg_ceer_clear_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ceer_local_port_get(const char *buf);

void mlxsw_reg_ceer_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ceer_lp_msb_get(const char *buf);

void mlxsw_reg_ceer_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ceer_detection_entry_get(const char *buf);

void mlxsw_reg_ceer_detection_entry_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ceer_det_get(const char *buf);

uint8_t mlxsw_reg_ceer_l2_type_get(const char *buf);

uint8_t mlxsw_reg_ceer_extra_data_type_get(const char *buf);

uint8_t mlxsw_reg_ceer_tunnel_type_get(const char *buf);

uint8_t mlxsw_reg_ceer_l4_type_get(const char *buf);

uint8_t mlxsw_reg_ceer_l3_type_get(const char *buf);

uint8_t mlxsw_reg_ceer_vlan_type_get(const char *buf);

uint8_t mlxsw_reg_ceer_hash_valid_get(const char *buf);

uint16_t mlxsw_reg_ceer_lag_hash_get(const char *buf);

uint16_t mlxsw_reg_ceer_router_hash_get(const char *buf);

void mlxsw_reg_ceer_dmac_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_ceer_smac_memcpy_from(const char *buf, char *dst);

uint8_t mlxsw_reg_ceer_pcp_get(const char *buf);

uint8_t mlxsw_reg_ceer_dei_get(const char *buf);

uint16_t mlxsw_reg_ceer_vid_get(const char *buf);

uint8_t mlxsw_reg_ceer_inner_pcp_get(const char *buf);

uint8_t mlxsw_reg_ceer_inner_dei_get(const char *buf);

uint16_t mlxsw_reg_ceer_inner_vid_get(const char *buf);

uint8_t mlxsw_reg_ceer_dscp_get(const char *buf);

uint8_t mlxsw_reg_ceer_ecn_get(const char *buf);

uint8_t mlxsw_reg_ceer_ttl_get(const char *buf);

uint8_t mlxsw_reg_ceer_dont_frag_get(const char *buf);

uint16_t mlxsw_reg_ceer_sport_get(const char *buf);

uint16_t mlxsw_reg_ceer_dport_get(const char *buf);

uint32_t mlxsw_reg_ceer_sip_get(const char *buf, unsigned short index);

uint32_t mlxsw_reg_ceer_dip_get(const char *buf, unsigned short index);

uint32_t mlxsw_reg_ceer_ceer_extra_fields_vni_get(const char *buf);

void mlxsw_reg_ceer_ceer_extra_fields_inner_dmac_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_ceer_ceer_extra_fields_inner_smac_memcpy_from(const char *buf, char *dst);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_inner_l3_type_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_inner_dscp_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_inner_ecn_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_inner_ttl_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_inner_dont_frag_get(const char *buf);

uint32_t mlxsw_reg_ceer_ceer_extra_fields_inner_sip_get(const char *buf, unsigned short index);

uint32_t mlxsw_reg_ceer_ceer_extra_fields_inner_dip_get(const char *buf, unsigned short index);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_bos_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_exp_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_lb0_v_get(const char *buf);

uint32_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_label0_label_id_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_label0_ttl_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_lb1_v_get(const char *buf);

uint32_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_label1_label_id_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_label1_ttl_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_lb2_v_get(const char *buf);

uint32_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_label2_label_id_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_label2_ttl_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_lb3_v_get(const char *buf);

uint32_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_label3_label_id_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_label3_ttl_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_lb4_v_get(const char *buf);

uint32_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_label4_label_id_get(const char *buf);

uint8_t mlxsw_reg_ceer_ceer_extra_fields_MPLS_mpls_label4_ttl_get(const char *buf);

/* pmtdb
 * -----
 *
 */
#define MLXSW_PMTDB_ID 0x501a
#define MLXSW_PMTDB_LEN 0x40

uint8_t mlxsw_reg_pmtdb_slot_index_get(const char *buf);

void mlxsw_reg_pmtdb_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmtdb_module_get(const char *buf);

void mlxsw_reg_pmtdb_module_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmtdb_ports_width_get(const char *buf);

void mlxsw_reg_pmtdb_ports_width_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmtdb_num_ports_get(const char *buf);

void mlxsw_reg_pmtdb_num_ports_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmtdb_status_get(const char *buf);

uint8_t mlxsw_reg_pmtdb_port_num1_get(const char *buf);

uint8_t mlxsw_reg_pmtdb_port_num2_get(const char *buf);

uint8_t mlxsw_reg_pmtdb_port_num3_get(const char *buf);

uint8_t mlxsw_reg_pmtdb_port_num4_get(const char *buf);

uint8_t mlxsw_reg_pmtdb_port_num5_get(const char *buf);

uint8_t mlxsw_reg_pmtdb_port_num6_get(const char *buf);

uint8_t mlxsw_reg_pmtdb_port_num7_get(const char *buf);

uint8_t mlxsw_reg_pmtdb_port_num8_get(const char *buf);

/* ibfmrc
 * ------
 *
 */
#define MLXSW_IBFMRC_ID 0x6004
#define MLXSW_IBFMRC_LEN 0x4

uint32_t mlxsw_reg_ibfmrc_attr_id_en_get(const char *buf);

void mlxsw_reg_ibfmrc_attr_id_en_set(char *buf, uint32_t val);

/* xralta
 * ------
 *
 */
#define MLXSW_XRALTA_ID 0x7811
#define MLXSW_XRALTA_LEN 0x8

uint8_t mlxsw_reg_xralta_op_get(const char *buf);

void mlxsw_reg_xralta_op_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_xralta_protocol_get(const char *buf);

void mlxsw_reg_xralta_protocol_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_xralta_tree_id_get(const char *buf);

void mlxsw_reg_xralta_tree_id_set(char *buf, uint8_t val);

/* mpagr
 * -----
 *
 */
#define MLXSW_MPAGR_ID 0x9089
#define MLXSW_MPAGR_LEN 0xc

uint8_t mlxsw_reg_mpagr_swid_get(const char *buf);

void mlxsw_reg_mpagr_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpagr_mngr_type_get(const char *buf);

void mlxsw_reg_mpagr_mngr_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpagr_trigger_get(const char *buf);

void mlxsw_reg_mpagr_trigger_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpagr_enable_get(const char *buf);

void mlxsw_reg_mpagr_enable_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpagr_pa_id_get(const char *buf);

void mlxsw_reg_mpagr_pa_id_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mpagr_probability_rate_get(const char *buf);

void mlxsw_reg_mpagr_probability_rate_set(char *buf, uint32_t val);

/* xltq
 * ----
 *
 */
#define MLXSW_XLTQ_ID 0x7802
#define MLXSW_XLTQ_LEN 0x2c

uint16_t mlxsw_reg_xltq_xm_device_id_get(const char *buf);

uint32_t mlxsw_reg_xltq_xlt_cap_mask0_get(const char *buf);

uint32_t mlxsw_reg_xltq_cap_xlt_entries_get(const char *buf);

uint32_t mlxsw_reg_xltq_cap_xlt_mtable_get(const char *buf);

uint32_t mlxsw_reg_xltq_cap_xlt_shspm_max_trees_get(const char *buf);

/* ppcnt
 * -----
 *
 */
#define MLXSW_PPCNT_ID 0x5008
#define MLXSW_PPCNT_HIST_BASE_LEN 0x08 /* base length, without records */
#define MLXSW_PPCNT_HIST_REC_LEN 0x08 /* record length */
#define MLXSW_PPCNT_HIST_REC_MAX_COUNT 16
#define MLXSW_PPCNT_LEN 0x100

uint8_t mlxsw_reg_ppcnt_swid_get(const char *buf);

void mlxsw_reg_ppcnt_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcnt_local_port_get(const char *buf);

void mlxsw_reg_ppcnt_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcnt_pnat_get(const char *buf);

void mlxsw_reg_ppcnt_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcnt_lp_msb_get(const char *buf);

void mlxsw_reg_ppcnt_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcnt_port_type_get(const char *buf);

void mlxsw_reg_ppcnt_port_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcnt_grp_get(const char *buf);

void mlxsw_reg_ppcnt_grp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcnt_clr_get(const char *buf);

void mlxsw_reg_ppcnt_clr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcnt_prio_tc_get(const char *buf);

void mlxsw_reg_ppcnt_prio_tc_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_frames_transmitted_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_frames_transmitted_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_frames_received_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_frames_received_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_frame_check_sequence_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_frame_check_sequence_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_alignment_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_alignment_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_octets_transmitted_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_octets_transmitted_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_octets_received_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_octets_received_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_xmitted_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_xmitted_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_xmitted_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_xmitted_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_received_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_received_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_received_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_received_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_in_range_length_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_in_range_length_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_out_of_range_length_field_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_out_of_range_length_field_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_frame_too_long_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_frame_too_long_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_symbol_error_during_carrier_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_symbol_error_during_carrier_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_transmitted_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_transmitted_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_received_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_received_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_unsupported_opcodes_received_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_unsupported_opcodes_received_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_received_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_received_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_transmitted_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_transmitted_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_in_octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_in_octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_in_ucast_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_in_ucast_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_in_discards_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_in_discards_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_in_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_in_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_in_unknown_protos_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_in_unknown_protos_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_out_octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_out_octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_out_ucast_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_out_ucast_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_out_discards_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_out_discards_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_out_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_out_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_in_multicast_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_in_multicast_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_in_broadcast_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_in_broadcast_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_out_multicast_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_out_multicast_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_out_broadcast_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2863_cntrs_grp_data_layout_if_out_broadcast_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_drop_events_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_drop_events_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_broadcast_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_broadcast_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_multicast_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_multicast_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_crc_align_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_crc_align_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_undersize_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_undersize_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_oversize_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_oversize_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_fragments_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_fragments_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_jabbers_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_jabbers_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_collisions_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_collisions_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts64octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts64octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts65to127octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts65to127octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts128to255octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts128to255octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts256to511octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts256to511octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts512to1023octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts512to1023octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1024to1518octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1024to1518octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1519to2047octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1519to2047octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts2048to4095octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts2048to4095octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts4096to8191octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts4096to8191octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts8192to10239octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_2819_cntrs_grp_data_layout_ether_stats_pkts8192to10239octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_high_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_low_get(const char *buf);

void mlxsw_reg_ppcnt_eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_port_transmit_wait_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_port_transmit_wait_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_ecn_marked_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_ecn_marked_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_no_buffer_discard_mc_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_no_buffer_discard_mc_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_rx_ebp_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_rx_ebp_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_ebp_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_ebp_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_rx_buffer_almost_full_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_rx_buffer_almost_full_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_rx_buffer_full_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_rx_buffer_full_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_rx_icrc_encapsulated_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_rx_icrc_encapsulated_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts64octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts64octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts65to127octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts65to127octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts128to255octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts128to255octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts256to511octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts256to511octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts512to1023octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts512to1023octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1024to1518octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1024to1518octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1519to2047octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1519to2047octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts2048to4095octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts2048to4095octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts4096to8191octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts4096to8191octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts8192to10239octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_extended_cntrs_grp_data_layout_tx_stats_pkts8192to10239octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_ingress_general_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_ingress_general_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_ingress_policy_engine_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_ingress_policy_engine_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_ingress_vlan_membership_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_ingress_vlan_membership_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_ingress_tag_frame_type_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_ingress_tag_frame_type_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_egress_vlan_membership_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_egress_vlan_membership_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_loopback_filter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_loopback_filter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_egress_general_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_egress_general_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_egress_hoq_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_egress_hoq_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_port_isolation_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_port_isolation_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_egress_policy_engine_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_egress_policy_engine_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_ingress_tx_link_down_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_ingress_tx_link_down_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_egress_stp_filter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_egress_stp_filter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_egress_hoq_stall_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_egress_hoq_stall_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_egress_sll_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_egress_sll_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_ingress_discard_all_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_discard_cntrs_grp_ingress_discard_all_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_level_retrans_cntr_grp_data_llr_rx_cells_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_level_retrans_cntr_grp_data_llr_rx_cells_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_level_retrans_cntr_grp_data_llr_rx_error_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_level_retrans_cntr_grp_data_llr_rx_error_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_level_retrans_cntr_grp_data_llr_rx_crc_error_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_level_retrans_cntr_grp_data_llr_rx_crc_error_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_level_retrans_cntr_grp_data_llr_tx_cells_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_level_retrans_cntr_grp_data_llr_tx_cells_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_level_retrans_cntr_grp_data_llr_tx_ret_cells_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_level_retrans_cntr_grp_data_llr_tx_ret_cells_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_level_retrans_cntr_grp_data_llr_tx_ret_events_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_level_retrans_cntr_grp_data_llr_tx_ret_events_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_uc_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_uc_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_mc_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_mc_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_bc_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_bc_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_tx_octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_tx_octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_tx_uc_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_tx_uc_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_tx_mc_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_tx_mc_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_tx_bc_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_tx_bc_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_tx_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_tx_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_pause_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_pause_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_pause_duration_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_pause_duration_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_tx_pause_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_tx_pause_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_tx_pause_duration_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_tx_pause_duration_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_pause_transition_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_pause_transition_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_discards_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_rx_discards_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_device_stall_minor_watermark_cnt_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_device_stall_minor_watermark_cnt_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_device_stall_critical_watermark_cnt_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_prio_grp_data_layout_device_stall_critical_watermark_cnt_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_traffic_class_layout_transmit_queue_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_traffic_class_layout_transmit_queue_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_traffic_class_layout_no_buffer_discard_uc_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_traffic_class_layout_no_buffer_discard_uc_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_time_since_last_clear_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_time_since_last_clear_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_symbol_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_symbol_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_sync_headers_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_sync_headers_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_edpl_bip_errors_lane0_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_edpl_bip_errors_lane0_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_edpl_bip_errors_lane1_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_edpl_bip_errors_lane1_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_edpl_bip_errors_lane2_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_edpl_bip_errors_lane2_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_edpl_bip_errors_lane3_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_edpl_bip_errors_lane3_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_corrected_blocks_lane0_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_corrected_blocks_lane0_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_corrected_blocks_lane1_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_corrected_blocks_lane1_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_corrected_blocks_lane2_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_corrected_blocks_lane2_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_corrected_blocks_lane3_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_corrected_blocks_lane3_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane0_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane0_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane1_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane1_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane2_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane2_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane3_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane3_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_blocks_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_blocks_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_uncorrectable_blocks_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_uncorrectable_blocks_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_no_errors_blocks_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_no_errors_blocks_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_single_error_blocks_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_single_error_blocks_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_total_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_total_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane0_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane0_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane1_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane1_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane2_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane2_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane3_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane3_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_link_down_events_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_successful_recovery_events_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_traffic_class_cong_layout_wred_discard_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_traffic_class_cong_layout_wred_discard_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_traffic_class_cong_layout_ecn_marked_tc_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_traffic_class_cong_layout_ecn_marked_tc_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_receive_buffer_grp_rx_no_buffer_discard_uc_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_per_receive_buffer_grp_rx_no_buffer_discard_uc_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_time_since_last_clear_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_time_since_last_clear_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_received_bits_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_received_bits_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_symbol_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_symbol_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_corrected_bits_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_corrected_bits_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane0_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane0_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane1_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane1_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane2_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane2_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane3_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane3_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane4_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane4_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane5_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane5_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane6_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane6_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane7_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_raw_errors_lane7_low_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_effective_ber_magnitude_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_effective_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_symbol_ber_magnitude_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_symbol_fec_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane0_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane0_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane1_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane1_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane2_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane2_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane3_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane3_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane4_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane4_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane5_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane5_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane6_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane6_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane7_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane7_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_effective_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_phy_effective_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_if_in_ucast_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_if_in_ucast_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_if_in_octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_if_in_octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_if_in_discards_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_if_in_discards_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_if_in_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_if_in_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_ether_stats_crc_align_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_ether_stats_crc_align_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_ether_stats_undersize_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_ether_stats_undersize_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_ether_stats_oversize_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_ether_stats_oversize_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_dot3stats_symbol_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_dot3stats_symbol_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_dot3in_pause_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_dot3in_pause_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_dot3control_in_unknown_opcodes_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_dot3control_in_unknown_opcodes_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_if_out_ucast_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_if_out_ucast_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_if_out_octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_if_out_octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_dot3out_pause_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_dot3out_pause_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_if_out_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_if_out_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_phy_time_since_last_clear_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_phy_time_since_last_clear_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_phy_received_bits_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_phy_received_bits_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_phy_symbol_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_eth_oob_port_cntrs_phy_symbol_errors_low_get(const char *buf);

uint16_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_symbol_error_counter_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_link_error_recovery_counter_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_link_downed_counter_get(const char *buf);

uint16_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_port_rcv_errors_get(const char *buf);

uint16_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_get(const char *buf);

uint16_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_get(const char *buf);

uint16_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_port_xmit_discards_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_port_xmit_constraint_errors_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_port_rcv_constraint_errors_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_local_link_integrity_errors_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_get(const char *buf);

uint16_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_vl_15_dropped_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_port_xmit_data_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_port_rcv_data_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_port_xmit_pkts_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_port_rcv_pkts_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_portcntrs_attribute_grp_data_port_xmit_wait_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_symbol_error_counter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_symbol_error_counter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_link_error_recovery_counter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_link_error_recovery_counter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_link_downed_counter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_link_downed_counter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_rcv_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_rcv_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_xmit_discards_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_xmit_discards_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_xmit_constraint_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_xmit_constraint_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_rcv_constraint_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_rcv_constraint_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_local_link_integrity_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_local_link_integrity_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_vl_15_dropped_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_vl_15_dropped_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_xmit_data_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_xmit_data_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_rcv_data_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_rcv_data_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_xmit_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_xmit_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_rcv_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_rcv_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_xmit_wait_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_xmit_wait_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_effective_rcv_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_effective_rcv_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_effective_rcv_data_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_IB_long_portcntrs_attribute_grp_data_port_effective_rcv_data_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_rcv_codes_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_rcv_codes_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_rcv_code_err_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_rcv_code_err_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_rcv_uncorrectable_code_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_rcv_uncorrectable_code_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_xmit_codes_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_xmit_codes_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_xmit_retry_codes_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_xmit_retry_codes_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_xmit_retry_events_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_xmit_retry_events_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_sync_events_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_sync_events_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_hi_retransmission_rate_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_hi_retransmission_rate_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_xmit_retry_codes_within_t_sec_max_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_xmit_retry_codes_within_t_sec_max_low_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_ppcnt_plr_counters_pre_plr_ber_magnitude_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_ppcnt_plr_counters_pre_plr_ber_coef_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_rs_fec_histograms_counters_hi_get(const char *buf, unsigned short index);

void mlxsw_reg_ppcnt_ppcnt_rs_fec_histograms_counters_hi_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_ppcnt_ppcnt_rs_fec_histograms_counters_lo_get(const char *buf, unsigned short index);

void mlxsw_reg_ppcnt_ppcnt_rs_fec_histograms_counters_lo_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_time_since_last_clear_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_time_since_last_clear_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane0_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane0_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane1_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane1_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane2_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane2_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane3_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane3_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane4_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane4_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane5_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane5_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane6_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane6_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane7_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane7_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane0_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane0_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane1_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane1_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane2_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane2_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane3_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane3_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane4_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane4_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane5_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane5_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane6_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane6_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane7_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane7_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_usr_xsr_physical_layer_link_down_events_get(const char *buf);

/* pefaad
 * ------
 *
 */
#define MLXSW_PEFAAD_ID 0x3029
#define MLXSW_PEFAAD_LEN 0x420

uint8_t mlxsw_reg_pefaad_filter_fields_get(const char *buf);

void mlxsw_reg_pefaad_filter_fields_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pefaad_op_get(const char *buf);

void mlxsw_reg_pefaad_op_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pefaad_num_rec_get(const char *buf);

void mlxsw_reg_pefaad_num_rec_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_pefaad_entry_a_get(const char *buf);

void mlxsw_reg_pefaad_entry_a_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pefaad_as_user_val_get(const char *buf);

void mlxsw_reg_pefaad_as_user_val_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_pefaad_index_dump_get(const char *buf, unsigned short index);

void mlxsw_reg_pefaad_index_dump_set(char *buf, unsigned short index, uint32_t val);

/* pmlpe
 * -----
 *
 */
#define MLXSW_PMLPE_ID 0x501c
#define MLXSW_PMLPE_LEN 0x40

uint8_t mlxsw_reg_pmlpe_rxtx_get(const char *buf);

uint8_t mlxsw_reg_pmlpe_autosplit_get(const char *buf);

uint8_t mlxsw_reg_pmlpe_local_port_get(const char *buf);

void mlxsw_reg_pmlpe_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmlpe_lp_msb_get(const char *buf);

void mlxsw_reg_pmlpe_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmlpe_width_get(const char *buf);

uint32_t mlxsw_reg_pmlpe_lane0_module_mapping_get(const char *buf);

uint32_t mlxsw_reg_pmlpe_lane1_module_mapping_get(const char *buf);

uint32_t mlxsw_reg_pmlpe_lane2_module_mapping_get(const char *buf);

uint32_t mlxsw_reg_pmlpe_lane3_module_mapping_get(const char *buf);

uint32_t mlxsw_reg_pmlpe_lane4_module_mapping_get(const char *buf);

uint32_t mlxsw_reg_pmlpe_lane5_module_mapping_get(const char *buf);

uint32_t mlxsw_reg_pmlpe_lane6_module_mapping_get(const char *buf);

uint32_t mlxsw_reg_pmlpe_lane7_module_mapping_get(const char *buf);

/* chlmm
 * -----
 *
 */
#define MLXSW_CHLMM_ID 0x2812
#define MLXSW_CHLMM_LEN 0x14

uint8_t mlxsw_reg_chlmm_switch_prio_get(const char *buf);

void mlxsw_reg_chlmm_switch_prio_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_chlmm_hlt_table_pointer_get(const char *buf);

void mlxsw_reg_chlmm_hlt_table_pointer_set(char *buf, uint8_t val);

/* tncr
 * ----
 *
 */
#define MLXSW_TNCR_ID 0xa002
#define MLXSW_TNCR_LEN 0x30

uint8_t mlxsw_reg_tncr_clear_counters_get(const char *buf);

void mlxsw_reg_tncr_clear_counters_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tncr_count_encap_high_get(const char *buf);

uint32_t mlxsw_reg_tncr_count_encap_low_get(const char *buf);

uint32_t mlxsw_reg_tncr_count_decap_high_get(const char *buf);

uint32_t mlxsw_reg_tncr_count_decap_low_get(const char *buf);

uint32_t mlxsw_reg_tncr_count_decap_errors_high_get(const char *buf);

uint32_t mlxsw_reg_tncr_count_decap_errors_low_get(const char *buf);

uint32_t mlxsw_reg_tncr_count_decap_discards_high_get(const char *buf);

uint32_t mlxsw_reg_tncr_count_decap_discards_low_get(const char *buf);

/* xmdr
 * ----
 *
 */
#define MLXSW_XMDR_ID 0x7803
#define MLXSW_XMDR_LEN 0xa0

uint8_t mlxsw_reg_xmdr_num_rec_get(const char *buf);

void mlxsw_reg_xmdr_num_rec_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_xmdr_reply_vect_get(const char *buf);

void mlxsw_reg_xmdr_transaction_set(char *buf, unsigned short index, uint32_t val);

/* mdfcr
 * -----
 *
 */
#define MLXSW_MDFCR_ID 0x9101
#define MLXSW_MDFCR_LEN 0x60

uint8_t mlxsw_reg_mdfcr_device_type_get(const char *buf);

void mlxsw_reg_mdfcr_device_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mdfcr_all_get(const char *buf);

void mlxsw_reg_mdfcr_all_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mdfcr_device_index_get(const char *buf);

void mlxsw_reg_mdfcr_device_index_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mdfcr_fw_status_get(const char *buf);

uint16_t mlxsw_reg_mdfcr_first_fw_status_device_get(const char *buf);

uint32_t mlxsw_reg_mdfcr_expected_fw_version_get(const char *buf);

uint32_t mlxsw_reg_mdfcr_fw_version_get(const char *buf);

uint16_t mlxsw_reg_mdfcr_build_id_get(const char *buf);

uint8_t mlxsw_reg_mdfcr_major_get(const char *buf);

uint8_t mlxsw_reg_mdfcr_minor_get(const char *buf);

uint8_t mlxsw_reg_mdfcr_error_id_get(const char *buf);

/* mddc
 * ----
 *
 */
#define MLXSW_MDDC_ID 0x9163
#define MLXSW_MDDC_LEN 0x30

uint8_t mlxsw_reg_mddc_level_get(const char *buf);

void mlxsw_reg_mddc_level_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddc_index_get(const char *buf);

void mlxsw_reg_mddc_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddc_slot_index_get(const char *buf);

void mlxsw_reg_mddc_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddc_rst_get(const char *buf);

void mlxsw_reg_mddc_rst_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddc_device_enable_get(const char *buf);

void mlxsw_reg_mddc_device_enable_set(char *buf, uint8_t val);

/* paos
 * ----
 *
 */
#define MLXSW_PAOS_ID 0x5006
#define MLXSW_PAOS_LEN 0x10

uint8_t mlxsw_reg_paos_swid_get(const char *buf);

void mlxsw_reg_paos_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_paos_local_port_get(const char *buf);

void mlxsw_reg_paos_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_paos_pnat_get(const char *buf);

void mlxsw_reg_paos_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_paos_lp_msb_get(const char *buf);

void mlxsw_reg_paos_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_paos_admin_status_get(const char *buf);

void mlxsw_reg_paos_admin_status_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_paos_oper_status_get(const char *buf);

void mlxsw_reg_paos_ase_set(char *buf, uint8_t val);

void mlxsw_reg_paos_ee_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_paos_fd_get(const char *buf);

void mlxsw_reg_paos_fd_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_paos_e_get(const char *buf);

void mlxsw_reg_paos_e_set(char *buf, uint8_t val);

/* mtutc
 * -----
 *
 */
#define MLXSW_MTUTC_ID 0x9055
#define MLXSW_MTUTC_LEN 0x1c

uint8_t mlxsw_reg_mtutc_operation_get(const char *buf);

void mlxsw_reg_mtutc_operation_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mtutc_freq_adjustment_get(const char *buf);

void mlxsw_reg_mtutc_freq_adjustment_set(char *buf, uint32_t val);

void mlxsw_reg_mtutc_utc_sec_set(char *buf, uint32_t val);

void mlxsw_reg_mtutc_utc_nsec_set(char *buf, uint32_t val);

void mlxsw_reg_mtutc_time_adjustment_set(char *buf, uint32_t val);

/* sfmr
 * ----
 *
 */
#define MLXSW_SFMR_ID 0x201f
#define MLXSW_SFMR_LEN 0x2c

uint8_t mlxsw_reg_sfmr_update_get(const char *buf);

void mlxsw_reg_sfmr_update_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfmr_op_get(const char *buf);

void mlxsw_reg_sfmr_op_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sfmr_fid_get(const char *buf);

void mlxsw_reg_sfmr_fid_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_sfmr_update_mask_get(const char *buf);

void mlxsw_reg_sfmr_update_mask_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_sfmr_disable_tport_encap_get(const char *buf);

void mlxsw_reg_sfmr_disable_tport_encap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfmr_flood_rsp_get(const char *buf);

void mlxsw_reg_sfmr_flood_rsp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfmr_flood_bridge_type_get(const char *buf);

void mlxsw_reg_sfmr_flood_bridge_type_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sfmr_fid_offset_get(const char *buf);

void mlxsw_reg_sfmr_fid_offset_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_sfmr_vtfp_get(const char *buf);

void mlxsw_reg_sfmr_vtfp_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_sfmr_nve_tunnel_flood_ptr_get(const char *buf);

void mlxsw_reg_sfmr_nve_tunnel_flood_ptr_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_sfmr_vv_get(const char *buf);

void mlxsw_reg_sfmr_vv_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_sfmr_vni_get(const char *buf);

void mlxsw_reg_sfmr_vni_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_sfmr_irif_v_get(const char *buf);

void mlxsw_reg_sfmr_irif_v_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sfmr_irif_get(const char *buf);

void mlxsw_reg_sfmr_irif_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_sfmr_decap_counter_set_type_get(const char *buf);

void mlxsw_reg_sfmr_decap_counter_set_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_sfmr_decap_counter_index_get(const char *buf);

void mlxsw_reg_sfmr_decap_counter_index_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_sfmr_nve_flood_prf_id_get(const char *buf);

void mlxsw_reg_sfmr_nve_flood_prf_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfmr_smpe_valid_get(const char *buf);

void mlxsw_reg_sfmr_smpe_valid_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sfmr_smpe_get(const char *buf);

void mlxsw_reg_sfmr_smpe_set(char *buf, uint16_t val);

/* hrdqt
 * -----
 *
 */
#define MLXSW_HRDQT_ID 0x7022
#define MLXSW_HRDQT_LEN 0xc

uint8_t mlxsw_reg_hrdqt_rdq_get(const char *buf);

void mlxsw_reg_hrdqt_rdq_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hrdqt_tac_en_get(const char *buf);

void mlxsw_reg_hrdqt_tac_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hrdqt_mirror_action_get(const char *buf);

void mlxsw_reg_hrdqt_mirror_action_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hrdqt_mirror_agent_get(const char *buf);

void mlxsw_reg_hrdqt_mirror_agent_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hrdqt_host_based_mirror_reason_id_get(const char *buf);

void mlxsw_reg_hrdqt_host_based_mirror_reason_id_set(char *buf, uint8_t val);

/* mtsde
 * -----
 *
 */
#define MLXSW_MTSDE_ID 0x910c
#define MLXSW_MTSDE_LEN 0x5c

uint16_t mlxsw_reg_mtsde_last_sensor_get(const char *buf);

uint8_t mlxsw_reg_mtsde_slot_index_get(const char *buf);

void mlxsw_reg_mtsde_slot_index_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mtsde_sensor_count_get(const char *buf);

uint32_t mlxsw_reg_mtsde_sensor_shut_down_map_0_get(const char *buf);

/* smpe
 * ----
 *
 */
#define MLXSW_SMPE_ID 0x202b
#define MLXSW_SMPE_LEN 0xc

uint8_t mlxsw_reg_smpe_local_port_get(const char *buf);

void mlxsw_reg_smpe_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_smpe_lp_msb_get(const char *buf);

void mlxsw_reg_smpe_lp_msb_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_smpe_smpe_index_get(const char *buf);

void mlxsw_reg_smpe_smpe_index_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_smpe_evid_get(const char *buf);

void mlxsw_reg_smpe_evid_set(char *buf, uint16_t val);

/* tiqdr
 * -----
 *
 */
#define MLXSW_TIQDR_ID 0xa811
#define MLXSW_TIQDR_LEN 0x8

uint8_t mlxsw_reg_tiqdr_local_port_get(const char *buf);

void mlxsw_reg_tiqdr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tiqdr_lp_msb_get(const char *buf);

void mlxsw_reg_tiqdr_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tiqdr_color_get(const char *buf);

void mlxsw_reg_tiqdr_color_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tiqdr_switch_prio_get(const char *buf);

void mlxsw_reg_tiqdr_switch_prio_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tiqdr_dscp_get(const char *buf);

void mlxsw_reg_tiqdr_dscp_set(char *buf, uint8_t val);

/* xraltb
 * ------
 *
 */
#define MLXSW_XRALTB_ID 0x7813
#define MLXSW_XRALTB_LEN 0x8

uint16_t mlxsw_reg_xraltb_virtual_router_get(const char *buf);

void mlxsw_reg_xraltb_virtual_router_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_xraltb_protocol_get(const char *buf);

void mlxsw_reg_xraltb_protocol_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_xraltb_tree_id_get(const char *buf);

void mlxsw_reg_xraltb_tree_id_set(char *buf, uint8_t val);

/* tngee
 * -----
 *
 */
#define MLXSW_TNGEE_ID 0xa021
#define MLXSW_TNGEE_LEN 0x60

uint32_t mlxsw_reg_tngee_l2_enc_index_get(const char *buf);

void mlxsw_reg_tngee_l2_enc_index_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_tngee_tunnel_type_get(const char *buf);

void mlxsw_reg_tngee_tunnel_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngee_vnext_get(const char *buf);

void mlxsw_reg_tngee_vnext_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tngee_next_l2_enc_ptr_get(const char *buf);

void mlxsw_reg_tngee_next_l2_enc_ptr_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_tngee_ecmp_size_get(const char *buf);

void mlxsw_reg_tngee_ecmp_size_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_tngee_protocol_get(const char *buf);

void mlxsw_reg_tngee_protocol_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_tngee_uirif_get(const char *buf);

void mlxsw_reg_tngee_uirif_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_tngee_udip_get(const char *buf);

void mlxsw_reg_tngee_udip_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_tngee_counter_set_type_get(const char *buf);

void mlxsw_reg_tngee_counter_set_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tngee_counter_index_get(const char *buf);

void mlxsw_reg_tngee_counter_index_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_tngee_entry_get(const char *buf, unsigned short index);

void mlxsw_reg_tngee_entry_set(char *buf, unsigned short index, uint32_t val);

/* smpeb
 * -----
 *
 */
#define MLXSW_SMPEB_ID 0x202c
#define MLXSW_SMPEB_ELPORT_RECORD_BASE_LEN 0x20 /* base length, without records */
#define MLXSW_SMPEB_ELPORT_RECORD_REC_LEN 0x04 /* record length */
#define MLXSW_SMPEB_ELPORT_RECORD_REC_MAX_COUNT 256
#define MLXSW_SMPEB_LEN 0x420

uint16_t mlxsw_reg_smpeb_smpe_index_get(const char *buf);

void mlxsw_reg_smpeb_smpe_index_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_smpeb_elport_page_get(const char *buf);

void mlxsw_reg_smpeb_elport_page_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_smpeb_update_get(const char *buf, unsigned short index);

void mlxsw_reg_smpeb_update_set(char *buf, unsigned short index, uint8_t val);

uint32_t mlxsw_reg_smpeb_value_get(const char *buf, unsigned short index);

void mlxsw_reg_smpeb_value_set(char *buf, unsigned short index, uint32_t val);

/* ibfmr
 * -----
 *
 */
#define MLXSW_IBFMR_ID 0x6003
#define MLXSW_IBFMR_LEN 0x10

uint8_t mlxsw_reg_ibfmr_atm_v_get(const char *buf);

uint16_t mlxsw_reg_ibfmr_attribute_id_get(const char *buf);

uint32_t mlxsw_reg_ibfmr_attribute_modifier_get(const char *buf);

/* ppbs
 * ----
 *
 */
#define MLXSW_PPBS_ID 0x300c
#define MLXSW_PPBS_LEN 0x1c

uint8_t mlxsw_reg_ppbs_swid_get(const char *buf);

void mlxsw_reg_ppbs_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppbs_type_get(const char *buf);

void mlxsw_reg_ppbs_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_ppbs_pbs_ptr_get(const char *buf);

void mlxsw_reg_ppbs_pbs_ptr_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_ppbs_ppbs_unicast_v_fid_get(const char *buf);

void mlxsw_reg_ppbs_ppbs_unicast_v_fid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppbs_ppbs_unicast_set_vid_get(const char *buf);

void mlxsw_reg_ppbs_ppbs_unicast_set_vid_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ppbs_ppbs_unicast_vid_get(const char *buf);

void mlxsw_reg_ppbs_ppbs_unicast_vid_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ppbs_ppbs_unicast_fid_get(const char *buf);

void mlxsw_reg_ppbs_ppbs_unicast_fid_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_ppbs_ppbs_unicast_action_get(const char *buf);

void mlxsw_reg_ppbs_ppbs_unicast_action_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ppbs_ppbs_unicast_system_port_get(const char *buf);

void mlxsw_reg_ppbs_ppbs_unicast_system_port_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_ppbs_unicast_lag_uvid_get(const char *buf);

void mlxsw_reg_ppbs_unicast_lag_uvid_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ppbs_unicast_lag_vid_get(const char *buf);

void mlxsw_reg_ppbs_unicast_lag_vid_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ppbs_unicast_lag_lag_id_get(const char *buf);

void mlxsw_reg_ppbs_unicast_lag_lag_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_ppbs_ppbs_multicast_v_fid_get(const char *buf);

void mlxsw_reg_ppbs_ppbs_multicast_v_fid_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ppbs_ppbs_multicast_pgi_get(const char *buf);

void mlxsw_reg_ppbs_ppbs_multicast_pgi_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ppbs_ppbs_multicast_fid_get(const char *buf);

void mlxsw_reg_ppbs_ppbs_multicast_fid_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ppbs_ppbs_multicast_mid_get(const char *buf);

void mlxsw_reg_ppbs_ppbs_multicast_mid_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_ppbs_unicast_tunnel_udip_get(const char *buf);

void mlxsw_reg_ppbs_unicast_tunnel_udip_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_ppbs_unicast_tunnel_protocol_get(const char *buf);

void mlxsw_reg_ppbs_unicast_tunnel_protocol_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppbs_unicast_tunnel_gen_enc_get(const char *buf);

void mlxsw_reg_ppbs_unicast_tunnel_gen_enc_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ppbs_unicast_tunnel_ecmp_size_get(const char *buf);

void mlxsw_reg_ppbs_unicast_tunnel_ecmp_size_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ppbs_multicast_tunnel_underlay_mc_ptr_msb_get(const char *buf);

void mlxsw_reg_ppbs_multicast_tunnel_underlay_mc_ptr_msb_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ppbs_multicast_tunnel_fid_get(const char *buf);

void mlxsw_reg_ppbs_multicast_tunnel_fid_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_ppbs_multicast_tunnel_underlay_mc_ptr_lsb_get(const char *buf);

void mlxsw_reg_ppbs_multicast_tunnel_underlay_mc_ptr_lsb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppbs_multicast_tunnel_v_fid_get(const char *buf);

void mlxsw_reg_ppbs_multicast_tunnel_v_fid_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ppbs_multicast_tunnel_mid_get(const char *buf);

void mlxsw_reg_ppbs_multicast_tunnel_mid_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ppbs_multicast_tunnel_ecmp_size_get(const char *buf);

void mlxsw_reg_ppbs_multicast_tunnel_ecmp_size_set(char *buf, uint16_t val);

/* fppc
 * ----
 *
 */
#define MLXSW_FPPC_ID 0x4881
#define MLXSW_FPPC_LEN 0x60

uint8_t mlxsw_reg_fppc_as_ftlv_get(const char *buf);

void mlxsw_reg_fppc_as_ftlv_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_fpp_get(const char *buf);

void mlxsw_reg_fppc_fpp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_empty_fph_get(const char *buf);

void mlxsw_reg_fppc_empty_fph_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_field_offset_dword_prot_get(const char *buf);

void mlxsw_reg_fppc_field_offset_dword_prot_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_field_offset_bytes_prot_get(const char *buf);

void mlxsw_reg_fppc_field_offset_bytes_prot_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_fppc_field_mask_prot_non_tlv_get(const char *buf);

void mlxsw_reg_fppc_field_mask_prot_non_tlv_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_fppc_field_mask_prot_tlv_get(const char *buf);

void mlxsw_reg_fppc_field_mask_prot_tlv_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_fppc_field_offset_dword_length_get(const char *buf);

void mlxsw_reg_fppc_field_offset_dword_length_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_field_offset_bytes_length_get(const char *buf);

void mlxsw_reg_fppc_field_offset_bytes_length_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_field_mask_length_get(const char *buf);

void mlxsw_reg_fppc_field_mask_length_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_length_math_bitmap_get(const char *buf);

void mlxsw_reg_fppc_length_math_bitmap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_length_math_add_pos_get(const char *buf);

void mlxsw_reg_fppc_length_math_add_pos_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_length_math_add_get(const char *buf);

void mlxsw_reg_fppc_length_math_add_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_length_math_shift_left_get(const char *buf);

void mlxsw_reg_fppc_length_math_shift_left_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_length_math_shift_get(const char *buf);

void mlxsw_reg_fppc_length_math_shift_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_fexp_st_en_get(const char *buf);

void mlxsw_reg_fppc_fexp_st_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_fexp_st_id_get(const char *buf);

void mlxsw_reg_fppc_fexp_st_id_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_fppc_fexp_st_tlv_type_get(const char *buf);

void mlxsw_reg_fppc_fexp_st_tlv_type_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_fppc_fexp_of_en_get(const char *buf);

void mlxsw_reg_fppc_fexp_of_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_fexp_of_id_get(const char *buf);

void mlxsw_reg_fppc_fexp_of_id_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_fppc_fexp_of_tlv_type_get(const char *buf);

void mlxsw_reg_fppc_fexp_of_tlv_type_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_fppc_field_offset_dword_fexp_of_get(const char *buf);

void mlxsw_reg_fppc_field_offset_dword_fexp_of_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_field_offset_bytes_fexp_of_get(const char *buf);

void mlxsw_reg_fppc_field_offset_bytes_fexp_of_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_field_mask_fexp_of_get(const char *buf);

void mlxsw_reg_fppc_field_mask_fexp_of_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_fexp_of_math_bitmap_get(const char *buf);

void mlxsw_reg_fppc_fexp_of_math_bitmap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_fexp_of_math_add_pos_get(const char *buf);

void mlxsw_reg_fppc_fexp_of_math_add_pos_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_fexp_of_math_add_get(const char *buf);

void mlxsw_reg_fppc_fexp_of_math_add_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_fexp_of_math_shift_left_get(const char *buf);

void mlxsw_reg_fppc_fexp_of_math_shift_left_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_fexp_of_math_shift_get(const char *buf);

void mlxsw_reg_fppc_fexp_of_math_shift_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_my_ftlv_en_get(const char *buf);

void mlxsw_reg_fppc_my_ftlv_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_my_ftlv_start_get(const char *buf);

void mlxsw_reg_fppc_my_ftlv_start_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fppc_my_ftlv_fpp_get(const char *buf);

void mlxsw_reg_fppc_my_ftlv_fpp_set(char *buf, uint8_t val);

/* mtewe
 * -----
 *
 */
#define MLXSW_MTEWE_ID 0x910b
#define MLXSW_MTEWE_LEN 0x5c

uint16_t mlxsw_reg_mtewe_last_sensor_get(const char *buf);

uint8_t mlxsw_reg_mtewe_slot_index_get(const char *buf);

void mlxsw_reg_mtewe_slot_index_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mtewe_sensor_count_get(const char *buf);

uint32_t mlxsw_reg_mtewe_sensor_warning_0_get(const char *buf);

/* hgcr
 * ----
 *
 */
#define MLXSW_HGCR_ID 0x7000
#define MLXSW_HGCR_LEN 0x10

uint16_t mlxsw_reg_hgcr_truncation_size_get(const char *buf);

void mlxsw_reg_hgcr_truncation_size_set(char *buf, uint16_t val);

/* xlkbu
 * -----
 *
 */
#define MLXSW_XLKBU_ID 0x7804
#define MLXSW_XLKBU_LEN 0x140

uint8_t mlxsw_reg_xlkbu_data_type_get(const char *buf);

void mlxsw_reg_xlkbu_data_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_xlkbu_value_get(const char *buf, unsigned short index);

void mlxsw_reg_xlkbu_value_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_xlkbu_mask_get(const char *buf, unsigned short index);

void mlxsw_reg_xlkbu_mask_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_xlkbu_new_value_get(const char *buf, unsigned short index);

void mlxsw_reg_xlkbu_new_value_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_xlkbu_new_value_mask_get(const char *buf, unsigned short index);

void mlxsw_reg_xlkbu_new_value_mask_set(char *buf, unsigned short index, uint32_t val);

/* xrmt
 * ----
 *
 */
#define MLXSW_XRMT_ID 0x7810
#define MLXSW_XRMT_LEN 0x14

uint32_t mlxsw_reg_xrmt_index_get(const char *buf);

void mlxsw_reg_xrmt_index_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_xrmt_l0_val_get(const char *buf);

void mlxsw_reg_xrmt_l0_val_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_xrmt_l0_vec_get(const char *buf);

void mlxsw_reg_xrmt_l0_vec_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_xrmt_l1_val_get(const char *buf);

void mlxsw_reg_xrmt_l1_val_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_xrmt_l1_vec_get(const char *buf);

void mlxsw_reg_xrmt_l1_vec_set(char *buf, uint8_t val);

/* cepc
 * ----
 *
 */
#define MLXSW_CEPC_ID 0x2821
#define MLXSW_CEPC_LEN 0x8

uint16_t mlxsw_reg_cepc_local_port_get(const char *buf);

void mlxsw_reg_cepc_local_port_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_cepc_pp_get(const char *buf);

void mlxsw_reg_cepc_pp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cepc_lp_msb_get(const char *buf);

void mlxsw_reg_cepc_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cepc_en_ed_get(const char *buf);

void mlxsw_reg_cepc_en_ed_set(char *buf, uint8_t val);

/* reiv
 * ----
 *
 */
#define MLXSW_REIV_ID 0x8034
#define MLXSW_REIV_ELPORT_RECORD_BASE_LEN 0x20 /* base length, without records */
#define MLXSW_REIV_ELPORT_RECORD_REC_LEN 0x04 /* record length */
#define MLXSW_REIV_ELPORT_RECORD_REC_MAX_COUNT 256
#define MLXSW_REIV_LEN 0x420

uint8_t mlxsw_reg_reiv_port_page_get(const char *buf);

void mlxsw_reg_reiv_port_page_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_reiv_erif_get(const char *buf);

void mlxsw_reg_reiv_erif_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_reiv_update_get(const char *buf, unsigned short index);

void mlxsw_reg_reiv_update_set(char *buf, unsigned short index, uint8_t val);

uint16_t mlxsw_reg_reiv_evid_get(const char *buf, unsigned short index);

void mlxsw_reg_reiv_evid_set(char *buf, unsigned short index, uint16_t val);

/* ppad
 * ----
 *
 */
#define MLXSW_PPAD_ID 0x5005
#define MLXSW_PPAD_LEN 0x10

uint8_t mlxsw_reg_ppad_single_base_mac_get(const char *buf);

void mlxsw_reg_ppad_single_base_mac_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppad_pnat_get(const char *buf);

void mlxsw_reg_ppad_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppad_lp_msb_get(const char *buf);

void mlxsw_reg_ppad_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppad_local_port_get(const char *buf);

void mlxsw_reg_ppad_local_port_set(char *buf, uint8_t val);

void mlxsw_reg_ppad_mac_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_ppad_mac_memcpy_to(char *buf, const char *src);

/* prei
 * ----
 *
 */
#define MLXSW_PREI_ID 0x5058
#define MLXSW_PREI_LEN 0x18

uint8_t mlxsw_reg_prei_version_get(const char *buf);

uint8_t mlxsw_reg_prei_local_port_get(const char *buf);

void mlxsw_reg_prei_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_prei_pnat_get(const char *buf);

void mlxsw_reg_prei_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_prei_lp_msb_get(const char *buf);

void mlxsw_reg_prei_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_prei_ber_sel_get(const char *buf);

void mlxsw_reg_prei_ber_sel_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_prei_status_get(const char *buf);

void mlxsw_reg_prei_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_prei_ber_mantissa_get(const char *buf);

void mlxsw_reg_prei_ber_mantissa_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_prei_ber_exp_get(const char *buf);

void mlxsw_reg_prei_ber_exp_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_prei_lane_rate_cap_get(const char *buf);

uint16_t mlxsw_reg_prei_mixer_offset0_get(const char *buf);

void mlxsw_reg_prei_mixer_offset0_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_prei_mixer_offset1_get(const char *buf);

void mlxsw_reg_prei_mixer_offset1_set(char *buf, uint16_t val);

/* mocs
 * ----
 *
 */
#define MLXSW_MOCS_ID 0x9095
#define MLXSW_MOCS_LEN 0x78

uint8_t mlxsw_reg_mocs_type_get(const char *buf);

void mlxsw_reg_mocs_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_clear_get(const char *buf);

void mlxsw_reg_mocs_clear_set(char *buf, uint8_t val);

void mlxsw_reg_mocs_opcode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_status_get(const char *buf);

uint32_t mlxsw_reg_mocs_hi_get(const char *buf);

void mlxsw_reg_mocs_hi_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mocs_lo_get(const char *buf);

void mlxsw_reg_mocs_lo_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mocs_mocs_ppcnt_port_mask_get(const char *buf, unsigned short index);

void mlxsw_reg_mocs_mocs_ppcnt_port_mask_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_mocs_mocs_ppcnt_grp_mask_get(const char *buf, unsigned short index);

void mlxsw_reg_mocs_mocs_ppcnt_grp_mask_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_mocs_mocs_ppcnt_tc_mask_get(const char *buf);

void mlxsw_reg_mocs_mocs_ppcnt_tc_mask_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_mocs_mocs_ppcnt_prio_mask_get(const char *buf);

void mlxsw_reg_mocs_mocs_ppcnt_prio_mask_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_mocs_mocs_ppcnt_rx_buffer_mask_get(const char *buf);

void mlxsw_reg_mocs_mocs_ppcnt_rx_buffer_mask_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mocs_mocs_mgpcb_flush_get(const char *buf);

void mlxsw_reg_mocs_mocs_mgpcb_flush_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mocs_mocs_mgpcb_num_rec_get(const char *buf);

void mlxsw_reg_mocs_mocs_mgpcb_num_rec_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mocs_mocs_mgpcb_counter_index_base_get(const char *buf);

void mlxsw_reg_mocs_mocs_mgpcb_counter_index_base_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mocs_mocs_pbsr_port_mask_get(const char *buf, unsigned short index);

void mlxsw_reg_mocs_mocs_pbsr_port_mask_set(char *buf, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_mocs_mocs_sbsrd_curr_get(const char *buf);

void mlxsw_reg_mocs_mocs_sbsrd_curr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_mocs_sbsrd_snap_get(const char *buf);

void mlxsw_reg_mocs_mocs_sbsrd_snap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_mocs_sbsrd_cells_get(const char *buf);

void mlxsw_reg_mocs_mocs_sbsrd_cells_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_mocs_sbsrd_desc_get(const char *buf);

void mlxsw_reg_mocs_mocs_sbsrd_desc_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mocs_mocs_ceer_port_mask_get(const char *buf, unsigned short index);

void mlxsw_reg_mocs_mocs_ceer_port_mask_set(char *buf, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_mocs_mocs_mafbi_flush_get(const char *buf);

void mlxsw_reg_mocs_mocs_mafbi_flush_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_mocs_mafbi_type_get(const char *buf);

void mlxsw_reg_mocs_mocs_mafbi_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mocs_mocs_mafbi_num_rec_get(const char *buf);

void mlxsw_reg_mocs_mocs_mafbi_num_rec_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mocs_mocs_mafbi_counter_index_base_get(const char *buf);

void mlxsw_reg_mocs_mocs_mafbi_counter_index_base_set(char *buf, uint32_t val);

/* pllp
 * ----
 *
 */
#define MLXSW_PLLP_ID 0x504a
#define MLXSW_PLLP_LEN 0x10

uint8_t mlxsw_reg_pllp_local_port_get(const char *buf);

void mlxsw_reg_pllp_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pllp_lp_msb_get(const char *buf);

void mlxsw_reg_pllp_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pllp_label_port_get(const char *buf);

uint8_t mlxsw_reg_pllp_split_stat_get(const char *buf);

uint8_t mlxsw_reg_pllp_split_num_get(const char *buf);

uint8_t mlxsw_reg_pllp_slot_num_get(const char *buf);

/* qeec
 * ----
 *
 */
#define MLXSW_QEEC_ID 0x400d
#define MLXSW_QEEC_LEN 0x20

uint8_t mlxsw_reg_qeec_local_port_get(const char *buf);

void mlxsw_reg_qeec_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qeec_lp_msb_get(const char *buf);

void mlxsw_reg_qeec_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qeec_element_hierarchy_get(const char *buf);

void mlxsw_reg_qeec_element_hierarchy_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qeec_element_index_get(const char *buf);

void mlxsw_reg_qeec_element_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qeec_next_element_index_get(const char *buf);

void mlxsw_reg_qeec_next_element_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qeec_mise_get(const char *buf);

void mlxsw_reg_qeec_mise_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qeec_ptps_get(const char *buf);

void mlxsw_reg_qeec_ptps_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qeec_pb_get(const char *buf);

void mlxsw_reg_qeec_pb_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_qeec_min_shaper_rate_get(const char *buf);

void mlxsw_reg_qeec_min_shaper_rate_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_qeec_mase_get(const char *buf);

void mlxsw_reg_qeec_mase_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_qeec_max_shaper_rate_get(const char *buf);

void mlxsw_reg_qeec_max_shaper_rate_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_qeec_pqe_get(const char *buf);

void mlxsw_reg_qeec_pqe_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_qeec_phantom_queue_rate_get(const char *buf);

void mlxsw_reg_qeec_phantom_queue_rate_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_qeec_de_get(const char *buf);

void mlxsw_reg_qeec_de_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qeec_dwrr_get(const char *buf);

void mlxsw_reg_qeec_dwrr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qeec_dwrr_weight_get(const char *buf);

void mlxsw_reg_qeec_dwrr_weight_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qeec_min_shaper_bs_get(const char *buf);

void mlxsw_reg_qeec_min_shaper_bs_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qeec_max_shaper_bs_get(const char *buf);

void mlxsw_reg_qeec_max_shaper_bs_set(char *buf, uint8_t val);

/* rmftad
 * ------
 *
 */
#define MLXSW_RMFTAD_ID 0x8028
#define MLXSW_RMFTAD_LEN 0x220

uint8_t mlxsw_reg_rmftad_op_get(const char *buf);

void mlxsw_reg_rmftad_op_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rmftad_type_get(const char *buf);

void mlxsw_reg_rmftad_type_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_rmftad_offset_get(const char *buf);

void mlxsw_reg_rmftad_offset_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_rmftad_num_rec_get(const char *buf);

void mlxsw_reg_rmftad_num_rec_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_rmftad_activity_vector_get(const char *buf, unsigned short index);

/* rlcmle
 * ------
 *
 */
#define MLXSW_RLCMLE_ID 0x8054
#define MLXSW_RLCMLE_LEN 0x38

uint8_t mlxsw_reg_rlcmle_protocol_get(const char *buf);

void mlxsw_reg_rlcmle_protocol_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rlcmle_op_get(const char *buf);

void mlxsw_reg_rlcmle_op_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rlcmle_m_idx_get(const char *buf);

void mlxsw_reg_rlcmle_m_idx_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_rlcmle_virtual_router_get(const char *buf);

void mlxsw_reg_rlcmle_virtual_router_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_rlcmle_l_value_get(const char *buf);

void mlxsw_reg_rlcmle_l_value_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rlcmle_dip_get(const char *buf, unsigned short index);

void mlxsw_reg_rlcmle_dip_set(char *buf, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_rlcmle_action_type_get(const char *buf);

void mlxsw_reg_rlcmle_action_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rlcmle_remote_action_trap_action_get(const char *buf);

void mlxsw_reg_rlcmle_remote_action_trap_action_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_rlcmle_remote_action_trap_id_get(const char *buf);

void mlxsw_reg_rlcmle_remote_action_trap_id_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_rlcmle_remote_action_adjacency_index_get(const char *buf);

void mlxsw_reg_rlcmle_remote_action_adjacency_index_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_rlcmle_remote_action_ecmp_size_get(const char *buf);

void mlxsw_reg_rlcmle_remote_action_ecmp_size_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_rlcmle_local_action_trap_action_get(const char *buf);

void mlxsw_reg_rlcmle_local_action_trap_action_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_rlcmle_local_action_trap_id_get(const char *buf);

void mlxsw_reg_rlcmle_local_action_trap_id_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_rlcmle_local_action_local_erif_get(const char *buf);

void mlxsw_reg_rlcmle_local_action_local_erif_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_rlcmle_ip2me_trap_action_get(const char *buf);

void mlxsw_reg_rlcmle_ip2me_trap_action_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rlcmle_ip2me_v_get(const char *buf);

void mlxsw_reg_rlcmle_ip2me_v_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rlcmle_ip2me_tunnel_ptr_get(const char *buf);

void mlxsw_reg_rlcmle_ip2me_tunnel_ptr_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_rlcmle_counter_set_type_get(const char *buf);

void mlxsw_reg_rlcmle_counter_set_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rlcmle_counter_index_get(const char *buf);

void mlxsw_reg_rlcmle_counter_index_set(char *buf, uint32_t val);

/* mcqi
 * ----
 *
 */
#define MLXSW_MCQI_ID 0x9061
#define MLXSW_MCQI_LEN 0x94

uint8_t mlxsw_reg_mcqi_read_pending_component_get(const char *buf);

void mlxsw_reg_mcqi_read_pending_component_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mcqi_device_index_get(const char *buf);

void mlxsw_reg_mcqi_device_index_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_mcqi_component_index_get(const char *buf);

void mlxsw_reg_mcqi_component_index_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mcqi_device_type_get(const char *buf);

void mlxsw_reg_mcqi_device_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_info_type_get(const char *buf);

void mlxsw_reg_mcqi_info_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mcqi_info_size_get(const char *buf);

uint32_t mlxsw_reg_mcqi_offset_get(const char *buf);

void mlxsw_reg_mcqi_offset_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_mcqi_data_size_get(const char *buf);

void mlxsw_reg_mcqi_data_size_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_mcqi_mcqi_cap_supported_info_bitmask_get(const char *buf);

uint32_t mlxsw_reg_mcqi_mcqi_cap_component_size_get(const char *buf);

uint32_t mlxsw_reg_mcqi_mcqi_cap_max_component_size_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_cap_log_mcda_word_size_get(const char *buf);

uint16_t mlxsw_reg_mcqi_mcqi_cap_mcda_max_write_size_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_cap_rd_en_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_cap_signed_updates_only_get(const char *buf);

void mlxsw_reg_mcqi_mcqi_cap_signed_updates_only_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_mcqi_cap_match_chip_id_get(const char *buf);

void mlxsw_reg_mcqi_mcqi_cap_match_chip_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_mcqi_cap_match_psid_get(const char *buf);

void mlxsw_reg_mcqi_mcqi_cap_match_psid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_mcqi_cap_check_user_timestamp_get(const char *buf);

void mlxsw_reg_mcqi_mcqi_cap_check_user_timestamp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_mcqi_cap_match_base_guid_mac_get(const char *buf);

void mlxsw_reg_mcqi_mcqi_cap_match_base_guid_mac_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_mcqi_version_build_time_valid_get(const char *buf);

void mlxsw_reg_mcqi_mcqi_version_build_time_valid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_mcqi_version_user_defined_time_valid_get(const char *buf);

void mlxsw_reg_mcqi_mcqi_version_user_defined_time_valid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_mcqi_version_version_string_length_get(const char *buf);

void mlxsw_reg_mcqi_mcqi_version_version_string_length_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mcqi_mcqi_version_version_get(const char *buf);

void mlxsw_reg_mcqi_mcqi_version_version_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mcqi_mcqi_version_build_time_hi_get(const char *buf);

void mlxsw_reg_mcqi_mcqi_version_build_time_hi_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mcqi_mcqi_version_build_time_lo_get(const char *buf);

void mlxsw_reg_mcqi_mcqi_version_build_time_lo_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mcqi_mcqi_version_user_defined_time_hi_get(const char *buf);

void mlxsw_reg_mcqi_mcqi_version_user_defined_time_hi_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mcqi_mcqi_version_user_defined_time_lo_get(const char *buf);

void mlxsw_reg_mcqi_mcqi_version_user_defined_time_lo_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mcqi_mcqi_version_build_tool_version_get(const char *buf);

void mlxsw_reg_mcqi_mcqi_version_build_tool_version_set(char *buf, uint32_t val);

void mlxsw_reg_mcqi_mcqi_version_version_string_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_mcqi_mcqi_version_version_string_memcpy_to(char *buf, const char *src);

uint8_t mlxsw_reg_mcqi_mcqi_activation_method_self_activation_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_activation_method_pending_server_ac_power_cycle_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_activation_method_pending_server_dc_power_cycle_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_activation_method_pending_server_reboot_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_activation_method_pending_fw_reset_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_activation_method_auto_activate_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_activation_method_all_hosts_sync_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_linkx_properties_fw_image_info_bitmap_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_linkx_properties_fw_image_status_bitmap_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_linkx_properties_image_a_major_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_linkx_properties_image_a_minor_get(const char *buf);

uint16_t mlxsw_reg_mcqi_mcqi_linkx_properties_image_a_subminor_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_linkx_properties_image_b_major_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_linkx_properties_image_b_minor_get(const char *buf);

uint16_t mlxsw_reg_mcqi_mcqi_linkx_properties_image_b_subminor_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_linkx_properties_factory_image_major_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_linkx_properties_factory_image_minor_get(const char *buf);

uint16_t mlxsw_reg_mcqi_mcqi_linkx_properties_factory_image_subminor_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_linkx_properties_activation_type_get(const char *buf);

uint8_t mlxsw_reg_mcqi_mcqi_linkx_properties_management_interface_protocol_get(const char *buf);

uint16_t mlxsw_reg_mcqi_mcqi_linkx_properties_vendor_sn_get(const char *buf);

/* chltr
 * -----
 *
 */
#define MLXSW_CHLTR_ID 0x2810
#define MLXSW_CHLTR_LEN 0xc

uint8_t mlxsw_reg_chltr_hlt_table_index_get(const char *buf);

void mlxsw_reg_chltr_hlt_table_index_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_chltr_high_latency_thr_get(const char *buf);

void mlxsw_reg_chltr_high_latency_thr_set(char *buf, uint32_t val);

/* tngcr
 * -----
 *
 */
#define MLXSW_TNGCR_ID 0xa001
#define MLXSW_TNGCR_LEN 0x44

uint8_t mlxsw_reg_tngcr_type_get(const char *buf);

void mlxsw_reg_tngcr_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_nve_valid_get(const char *buf);

void mlxsw_reg_tngcr_nve_valid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_nve_decap_ttl_get(const char *buf);

void mlxsw_reg_tngcr_nve_decap_ttl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_nve_ttlc_get(const char *buf);

void mlxsw_reg_tngcr_nve_ttlc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_nve_ttl_uc_get(const char *buf);

void mlxsw_reg_tngcr_nve_ttl_uc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_nve_ttl_mc_get(const char *buf);

void mlxsw_reg_tngcr_nve_ttl_mc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_nve_flc_get(const char *buf);

void mlxsw_reg_tngcr_nve_flc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_nve_flh_get(const char *buf);

void mlxsw_reg_tngcr_nve_flh_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tngcr_nve_fl_prefix_get(const char *buf);

void mlxsw_reg_tngcr_nve_fl_prefix_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_tngcr_nve_fl_suffix_get(const char *buf);

void mlxsw_reg_tngcr_nve_fl_suffix_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_nve_enc_orig_get(const char *buf);

void mlxsw_reg_tngcr_nve_enc_orig_set(char *buf, uint8_t val);

void mlxsw_reg_tngcr_nve_enc_orig_we_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_nve_udp_sport_type_get(const char *buf);

void mlxsw_reg_tngcr_nve_udp_sport_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_et_vlan_get(const char *buf);

void mlxsw_reg_tngcr_et_vlan_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_nve_udp_sport_prefix_get(const char *buf);

void mlxsw_reg_tngcr_nve_udp_sport_prefix_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_nve_group_size_mc_get(const char *buf);

void mlxsw_reg_tngcr_nve_group_size_mc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_nve_group_size_flood_get(const char *buf);

void mlxsw_reg_tngcr_nve_group_size_flood_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_learn_enable_get(const char *buf);

void mlxsw_reg_tngcr_learn_enable_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_tngcr_underlay_virtual_router_get(const char *buf);

void mlxsw_reg_tngcr_underlay_virtual_router_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_tngcr_underlay_rif_get(const char *buf);

void mlxsw_reg_tngcr_underlay_rif_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_tngcr_usipv4_get(const char *buf);

void mlxsw_reg_tngcr_usipv4_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_tngcr_usipv6_get(const char *buf, unsigned short index);

void mlxsw_reg_tngcr_usipv6_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_tngcr_header0_bit_set_get(const char *buf);

void mlxsw_reg_tngcr_header0_bit_set_set(char *buf, uint32_t val);

/* molp
 * ----
 *
 */
#define MLXSW_MOLP_ID 0x90f9
#define MLXSW_MOLP_LEN 0x8

uint8_t mlxsw_reg_molp_local_port_get(const char *buf);

void mlxsw_reg_molp_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_molp_lp_msb_get(const char *buf);

void mlxsw_reg_molp_lp_msb_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_molp_label_port_get(const char *buf);

void mlxsw_reg_molp_label_port_set(char *buf, uint16_t val);

/* hahcr
 * -----
 *
 */
#define MLXSW_HAHCR_ID 0x7021
#define MLXSW_HAHCR_LEN 0x38

uint8_t mlxsw_reg_hahcr_sh_get(const char *buf);

void mlxsw_reg_hahcr_sh_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hahcr_type_get(const char *buf);

void mlxsw_reg_hahcr_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_hahcr_general_fields_get(const char *buf);

void mlxsw_reg_hahcr_general_fields_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_hahcr_outer_header_enables_get(const char *buf);

void mlxsw_reg_hahcr_outer_header_enables_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_hahcr_outer_header_fields_enable_get(const char *buf, unsigned short index);

void mlxsw_reg_hahcr_outer_header_fields_enable_set(char *buf, unsigned short index, uint32_t val);

uint16_t mlxsw_reg_hahcr_inner_header_enables_get(const char *buf);

void mlxsw_reg_hahcr_inner_header_enables_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_hahcr_hi_get(const char *buf);

void mlxsw_reg_hahcr_hi_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_hahcr_lo_get(const char *buf);

void mlxsw_reg_hahcr_lo_set(char *buf, uint32_t val);

/* ptasv2
 * ------
 *
 */
#define MLXSW_PTASV2_ID 0x502e
#define MLXSW_PTASV2_LEN 0x30

uint8_t mlxsw_reg_ptasv2_version_get(const char *buf);

uint8_t mlxsw_reg_ptasv2_local_port_get(const char *buf);

void mlxsw_reg_ptasv2_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptasv2_pnat_get(const char *buf);

void mlxsw_reg_ptasv2_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptasv2_lp_msb_get(const char *buf);

void mlxsw_reg_ptasv2_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptasv2_ig_dme_mod_cap_get(const char *buf);

uint8_t mlxsw_reg_ptasv2_ig_dme_mod_admin_get(const char *buf);

void mlxsw_reg_ptasv2_ig_dme_mod_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptasv2_force_an_cap_get(const char *buf);

uint8_t mlxsw_reg_ptasv2_force_an_admin_get(const char *buf);

void mlxsw_reg_ptasv2_force_an_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptasv2_tuning_type_support_get(const char *buf);

uint8_t mlxsw_reg_ptasv2_tuning_type_admin_get(const char *buf);

void mlxsw_reg_ptasv2_tuning_type_admin_set(char *buf, uint8_t val);

/* mddt
 * ----
 *
 */
#define MLXSW_MDDT_ID 0x9160
#define MLXSW_MDDT_LEN 0x110

uint8_t mlxsw_reg_mddt_slot_index_get(const char *buf);

void mlxsw_reg_mddt_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddt_device_index_get(const char *buf);

void mlxsw_reg_mddt_device_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddt_read_size_get(const char *buf);

void mlxsw_reg_mddt_read_size_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddt_write_size_get(const char *buf);

void mlxsw_reg_mddt_write_size_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddt_type_get(const char *buf);

void mlxsw_reg_mddt_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddt_prm_register_payload_status_get(const char *buf);

uint8_t mlxsw_reg_mddt_prm_register_payload_method_get(const char *buf);

void mlxsw_reg_mddt_prm_register_payload_method_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mddt_prm_register_payload_register_id_get(const char *buf);

void mlxsw_reg_mddt_prm_register_payload_register_id_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_mddt_prm_register_payload_register_data_get(const char *buf, unsigned short index);

void mlxsw_reg_mddt_prm_register_payload_register_data_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_mddt_command_payload_data_get(const char *buf, unsigned short index);

void mlxsw_reg_mddt_command_payload_data_set(char *buf, unsigned short index, uint32_t val);

void mlxsw_reg_mddt_crspace_access_payload_address_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mddt_crspace_access_payload_data_get(const char *buf, unsigned short index);

void mlxsw_reg_mddt_crspace_access_payload_data_set(char *buf, unsigned short index, uint32_t val);

/* rips
 * ----
 *
 */
#define MLXSW_RIPS_ID 0x8021
#define MLXSW_RIPS_LEN 0x14

uint32_t mlxsw_reg_rips_index_get(const char *buf);

void mlxsw_reg_rips_index_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rips_ipv6_get(const char *buf, unsigned short index);

void mlxsw_reg_rips_ipv6_set(char *buf, unsigned short index, uint32_t val);

/* tndem
 * -----
 *
 */
#define MLXSW_TNDEM_ID 0xa013
#define MLXSW_TNDEM_LEN 0xc

uint8_t mlxsw_reg_tndem_underlay_ecn_get(const char *buf);

void mlxsw_reg_tndem_underlay_ecn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tndem_overlay_ecn_get(const char *buf);

void mlxsw_reg_tndem_overlay_ecn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tndem_eip_ecn_get(const char *buf);

void mlxsw_reg_tndem_eip_ecn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tndem_trap_en_get(const char *buf);

void mlxsw_reg_tndem_trap_en_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_tndem_trap_id_get(const char *buf);

void mlxsw_reg_tndem_trap_id_set(char *buf, uint16_t val);

/* sfdb_v2
 * -------
 *
 */
#define MLXSW_SFDB_V2_ID 0x202d
#define MLXSW_SFDB_V2_LEN 0x84

uint32_t mlxsw_reg_sfdb_v2_key_get(const char *buf, unsigned short index);

void mlxsw_reg_sfdb_v2_key_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_sfdb_v2_key_mask_get(const char *buf, unsigned short index);

void mlxsw_reg_sfdb_v2_key_mask_set(char *buf, unsigned short index, uint32_t val);

void mlxsw_reg_sfdb_v2_action_set(char *buf, unsigned short index, uint32_t val);

void mlxsw_reg_sfdb_v2_action_mask_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_sfdb_v2_count_updates_get(const char *buf);

/* tnumt
 * -----
 *
 */
#define MLXSW_TNUMT_ID 0xa003
#define MLXSW_TNUMT_LEN 0x20

uint8_t mlxsw_reg_tnumt_record_type_get(const char *buf);

void mlxsw_reg_tnumt_record_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tnumt_underlay_mc_ptr_get(const char *buf);

void mlxsw_reg_tnumt_underlay_mc_ptr_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_tnumt_vnext_get(const char *buf);

void mlxsw_reg_tnumt_vnext_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tnumt_next_underlay_mc_ptr_get(const char *buf);

void mlxsw_reg_tnumt_next_underlay_mc_ptr_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_tnumt_tunnel_mc_ipv4_size_get(const char *buf);

void mlxsw_reg_tnumt_tunnel_mc_ipv4_size_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tnumt_tunnel_mc_ipv4_udip_get(const char *buf, unsigned short index);

void mlxsw_reg_tnumt_tunnel_mc_ipv4_udip_set(char *buf, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_tnumt_tunnel_mc_ipv6_size_get(const char *buf);

void mlxsw_reg_tnumt_tunnel_mc_ipv6_size_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tnumt_tunnel_mc_ipv6_udip_ptr_get(const char *buf, unsigned short index);

void mlxsw_reg_tnumt_tunnel_mc_ipv6_udip_ptr_set(char *buf, unsigned short index, uint32_t val);

/* rlcme
 * -----
 *
 */
#define MLXSW_RLCME_ID 0x8053
#define MLXSW_RLCME_LEN 0x3c

uint8_t mlxsw_reg_rlcme_protocol_get(const char *buf);

void mlxsw_reg_rlcme_protocol_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rlcme_op_get(const char *buf);

void mlxsw_reg_rlcme_op_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rlcme_m_idx_get(const char *buf);

void mlxsw_reg_rlcme_m_idx_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_rlcme_virtual_router_get(const char *buf);

void mlxsw_reg_rlcme_virtual_router_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_rlcme_dip_get(const char *buf, unsigned short index);

void mlxsw_reg_rlcme_dip_set(char *buf, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_rlcme_action_type_get(const char *buf);

void mlxsw_reg_rlcme_action_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rlcme_action_get(const char *buf, unsigned short index);

void mlxsw_reg_rlcme_action_set(char *buf, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_rlcme_counter_set_type_get(const char *buf);

void mlxsw_reg_rlcme_counter_set_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rlcme_counter_index_get(const char *buf);

void mlxsw_reg_rlcme_counter_index_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_rlcme_action_valid_get(const char *buf);

void mlxsw_reg_rlcme_action_valid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rlcme_l_vector_get(const char *buf);

void mlxsw_reg_rlcme_l_vector_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rlcme_l_value_get(const char *buf);

void mlxsw_reg_rlcme_l_value_set(char *buf, uint8_t val);

/* fpts
 * ----
 *
 */
#define MLXSW_FPTS_ID 0x4884
#define MLXSW_FPTS_LEN 0xc

uint8_t mlxsw_reg_fpts_global_get(const char *buf);

void mlxsw_reg_fpts_global_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fpts_local_port_get(const char *buf);

void mlxsw_reg_fpts_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fpts_lp_msb_get(const char *buf);

void mlxsw_reg_fpts_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fpts_tran_type_get(const char *buf);

void mlxsw_reg_fpts_tran_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fpts_next_ph_get(const char *buf);

void mlxsw_reg_fpts_next_ph_set(char *buf, uint8_t val);

/* htacg
 * -----
 *
 */
#define MLXSW_HTACG_ID 0x7023
#define MLXSW_HTACG_LEN 0x90

uint8_t mlxsw_reg_htacg_go_get(const char *buf);

void mlxsw_reg_htacg_go_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htacg_grepper_index_get(const char *buf);

void mlxsw_reg_htacg_grepper_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htacg_tac_flush_get(const char *buf);

void mlxsw_reg_htacg_tac_flush_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htacg_fields_mirror_reason_get(const char *buf);

void mlxsw_reg_htacg_fields_mirror_reason_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htacg_fields_rdq_get(const char *buf);

void mlxsw_reg_htacg_fields_rdq_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_htacg_fields_trap_id_get(const char *buf);

void mlxsw_reg_htacg_fields_trap_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_htacg_fields_mirror_tclass_get(const char *buf);

void mlxsw_reg_htacg_fields_mirror_tclass_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htacg_fields_mirror_tx_acl_system_port_get(const char *buf);

void mlxsw_reg_htacg_fields_mirror_tx_acl_system_port_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_htacg_fields_max_egress_buffer_fill_level_get(const char *buf);

void mlxsw_reg_htacg_fields_max_egress_buffer_fill_level_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_htacg_fields_last_ts_get(const char *buf);

void mlxsw_reg_htacg_fields_last_ts_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_htacg_fields_pkt_count_get(const char *buf);

void mlxsw_reg_htacg_fields_pkt_count_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_htacg_fields_byte_count_high_get(const char *buf);

void mlxsw_reg_htacg_fields_byte_count_high_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_htacg_fields_byte_count_low_get(const char *buf);

void mlxsw_reg_htacg_fields_byte_count_low_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_htacg_mask_mirror_reason_get(const char *buf);

void mlxsw_reg_htacg_mask_mirror_reason_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htacg_mask_rdq_get(const char *buf);

void mlxsw_reg_htacg_mask_rdq_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_htacg_mask_trap_id_get(const char *buf);

void mlxsw_reg_htacg_mask_trap_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_htacg_mask_mirror_tclass_get(const char *buf);

void mlxsw_reg_htacg_mask_mirror_tclass_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htacg_mask_mirror_tx_acl_system_port_get(const char *buf);

void mlxsw_reg_htacg_mask_mirror_tx_acl_system_port_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_htacg_mask_max_egress_buffer_fill_level_get(const char *buf);

void mlxsw_reg_htacg_mask_max_egress_buffer_fill_level_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_htacg_mask_last_ts_get(const char *buf);

void mlxsw_reg_htacg_mask_last_ts_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_htacg_mask_pkt_count_get(const char *buf);

void mlxsw_reg_htacg_mask_pkt_count_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_htacg_mask_byte_count_high_get(const char *buf);

void mlxsw_reg_htacg_mask_byte_count_high_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_htacg_mask_byte_count_low_get(const char *buf);

void mlxsw_reg_htacg_mask_byte_count_low_set(char *buf, uint32_t val);

/* pevpb
 * -----
 *
 */
#define MLXSW_PEVPB_ID 0x302e
#define MLXSW_PEVPB_LEN 0x8

uint8_t mlxsw_reg_pevpb_local_port_get(const char *buf);

void mlxsw_reg_pevpb_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pevpb_lp_msb_get(const char *buf);

void mlxsw_reg_pevpb_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pevpb_ev_get(const char *buf);

void mlxsw_reg_pevpb_ev_set(char *buf, uint8_t val);

/* sfgc
 * ----
 *
 */
#define MLXSW_SFGC_ID 0x2011
#define MLXSW_SFGC_LEN 0x14

uint8_t mlxsw_reg_sfgc_type_get(const char *buf);

void mlxsw_reg_sfgc_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfgc_bridge_type_get(const char *buf);

void mlxsw_reg_sfgc_bridge_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfgc_table_type_get(const char *buf);

void mlxsw_reg_sfgc_table_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfgc_flood_table_get(const char *buf);

void mlxsw_reg_sfgc_flood_table_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfgc_counter_set_type_get(const char *buf);

void mlxsw_reg_sfgc_counter_set_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_sfgc_counter_index_get(const char *buf);

void mlxsw_reg_sfgc_counter_index_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_sfgc_mid_base_get(const char *buf);

void mlxsw_reg_sfgc_mid_base_set(char *buf, uint16_t val);

/* mcion
 * -----
 *
 */
#define MLXSW_MCION_ID 0x9052
#define MLXSW_MCION_LEN 0xc

uint8_t mlxsw_reg_mcion_module_get(const char *buf);

void mlxsw_reg_mcion_module_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcion_slot_index_get(const char *buf);

void mlxsw_reg_mcion_slot_index_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mcion_module_status_bits_get(const char *buf);

/* tiqcr
 * -----
 *
 */
#define MLXSW_TIQCR_ID 0xa810
#define MLXSW_TIQCR_LEN 0xc

uint8_t mlxsw_reg_tiqcr_enc_set_dscp_get(const char *buf);

void mlxsw_reg_tiqcr_enc_set_dscp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tiqcr_enc_set_sp_get(const char *buf);

void mlxsw_reg_tiqcr_enc_set_sp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tiqcr_enc_dscp_rw_get(const char *buf);

void mlxsw_reg_tiqcr_enc_dscp_rw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tiqcr_enc_pcp_rw_get(const char *buf);

void mlxsw_reg_tiqcr_enc_pcp_rw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tiqcr_dec_set_dscp_get(const char *buf);

void mlxsw_reg_tiqcr_dec_set_dscp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tiqcr_dec_set_sp_get(const char *buf);

void mlxsw_reg_tiqcr_dec_set_sp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tiqcr_dec_dscp_rw_get(const char *buf);

void mlxsw_reg_tiqcr_dec_dscp_rw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tiqcr_dec_pcp_rw_get(const char *buf);

void mlxsw_reg_tiqcr_dec_pcp_rw_set(char *buf, uint8_t val);

/* tncr_v2
 * -------
 *
 */
#define MLXSW_TNCR_V2_ID 0xa004
#define MLXSW_TNCR_V2_LEN 0x38

uint8_t mlxsw_reg_tncr_v2_clear_counters_get(const char *buf);

void mlxsw_reg_tncr_v2_clear_counters_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tncr_v2_tunnel_port_get(const char *buf);

void mlxsw_reg_tncr_v2_tunnel_port_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tncr_v2_count_decap_discards_high_get(const char *buf);

uint32_t mlxsw_reg_tncr_v2_count_decap_discards_low_get(const char *buf);

uint32_t mlxsw_reg_tncr_v2_count_encap_discards_high_get(const char *buf);

uint32_t mlxsw_reg_tncr_v2_count_encap_discards_low_get(const char *buf);

/* pcsr
 * ----
 *
 */
#define MLXSW_PCSR_ID 0x5049
#define MLXSW_PCSR_LEN 0x30

uint8_t mlxsw_reg_pcsr_gs_get(const char *buf);

uint8_t mlxsw_reg_pcsr_offset_get(const char *buf);

void mlxsw_reg_pcsr_offset_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_pcsr_port_status_mask_get(const char *buf, unsigned short index);

/* cedr
 * ----
 *
 */
#define MLXSW_CEDR_ID 0x2822
#define MLXSW_CEDR_LEN 0x20

uint8_t mlxsw_reg_cedr_clear_get(const char *buf);

void mlxsw_reg_cedr_clear_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cedr_local_port_get(const char *buf);

void mlxsw_reg_cedr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cedr_lp_msb_get(const char *buf);

void mlxsw_reg_cedr_lp_msb_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_cedr_detection_table_get(const char *buf, unsigned short index);

/* xralst
 * ------
 *
 */
#define MLXSW_XRALST_ID 0x7812
#define MLXSW_XRALST_LEN 0x108

uint8_t mlxsw_reg_xralst_root_bin_get(const char *buf);

void mlxsw_reg_xralst_root_bin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_xralst_tree_id_get(const char *buf);

void mlxsw_reg_xralst_tree_id_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_xralst_bin_get(const char *buf, unsigned short index);

void mlxsw_reg_xralst_bin_set(char *buf, unsigned short index, uint16_t val);

/* plar
 * ----
 *
 */
#define MLXSW_PLAR_ID 0x5068
#define MLXSW_PLAR_LEN 0x80

uint32_t mlxsw_reg_plar_local_port_allocated_get(const char *buf, unsigned short index);

/* iddd
 * ----
 *
 */
#define MLXSW_IDDD_ID 0x3802
#define MLXSW_IDDD_LEN 0x8

uint8_t mlxsw_reg_iddd_entry_type_get(const char *buf);

void mlxsw_reg_iddd_entry_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_iddd_duplication_get(const char *buf);

void mlxsw_reg_iddd_duplication_set(char *buf, uint8_t val);

/* iedr
 * ----
 *
 */
#define MLXSW_IEDR_ID 0x3804
#define MLXSW_IEDR_RECORD_BASE_LEN 0x10 /* base length, without records */
#define MLXSW_IEDR_RECORD_REC_LEN 0x08 /* record length */
#define MLXSW_IEDR_RECORD_REC_MAX_COUNT 64
#define MLXSW_IEDR_LEN 0x210

uint8_t mlxsw_reg_iedr_bg_get(const char *buf);

void mlxsw_reg_iedr_bg_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_iedr_num_rec_get(const char *buf);

void mlxsw_reg_iedr_num_rec_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_iedr_type_get(const char *buf, unsigned short index);

void mlxsw_reg_iedr_type_set(char *buf, unsigned short index, uint8_t val);

uint16_t mlxsw_reg_iedr_size_get(const char *buf, unsigned short index);

void mlxsw_reg_iedr_size_set(char *buf, unsigned short index, uint16_t val);

uint32_t mlxsw_reg_iedr_index_start_get(const char *buf, unsigned short index);

void mlxsw_reg_iedr_index_start_set(char *buf, unsigned short index, uint32_t val);

/* ieds
 * ----
 *
 */
#define MLXSW_IEDS_ID 0x3805
#define MLXSW_IEDS_LEN 0x8

uint8_t mlxsw_reg_ieds_edpr_get(const char *buf);

void mlxsw_reg_ieds_edpr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ieds_ed_status_get(const char *buf);

/* pmaos
 * -----
 *
 */
#define MLXSW_PMAOS_ID 0x5012
#define MLXSW_PMAOS_LEN 0x10

uint8_t mlxsw_reg_pmaos_rst_get(const char *buf);

void mlxsw_reg_pmaos_rst_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmaos_slot_index_get(const char *buf);

void mlxsw_reg_pmaos_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmaos_module_get(const char *buf);

void mlxsw_reg_pmaos_module_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmaos_admin_status_get(const char *buf);

void mlxsw_reg_pmaos_admin_status_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmaos_oper_status_get(const char *buf);

void mlxsw_reg_pmaos_ase_set(char *buf, uint8_t val);

void mlxsw_reg_pmaos_ee_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmaos_operational_notification_get(const char *buf);

uint8_t mlxsw_reg_pmaos_error_type_get(const char *buf);

uint8_t mlxsw_reg_pmaos_e_get(const char *buf);

void mlxsw_reg_pmaos_e_set(char *buf, uint8_t val);

/* rxlte
 * -----
 *
 */
#define MLXSW_RXLTE_ID 0x8050
#define MLXSW_RXLTE_LEN 0xc

uint16_t mlxsw_reg_rxlte_virtual_router_get(const char *buf);

void mlxsw_reg_rxlte_virtual_router_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_rxlte_protocol_get(const char *buf);

void mlxsw_reg_rxlte_protocol_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rxlte_lpm_xlt_en_get(const char *buf);

void mlxsw_reg_rxlte_lpm_xlt_en_set(char *buf, uint8_t val);

/* sbhbr_v2
 * --------
 *
 */
#define MLXSW_SBHBR_V2_ID 0xb011
#define MLXSW_SBHBR_V2_LEN 0x1c

uint8_t mlxsw_reg_sbhbr_v2_local_port_get(const char *buf);

void mlxsw_reg_sbhbr_v2_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbhbr_v2_pg_buff_get(const char *buf);

void mlxsw_reg_sbhbr_v2_pg_buff_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbhbr_v2_lp_msb_get(const char *buf);

void mlxsw_reg_sbhbr_v2_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbhbr_v2_dir_get(const char *buf);

void mlxsw_reg_sbhbr_v2_dir_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbhbr_v2_en_get(const char *buf);

void mlxsw_reg_sbhbr_v2_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbhbr_v2_mode_get(const char *buf);

void mlxsw_reg_sbhbr_v2_mode_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sbhbr_v2_hist_type_get(const char *buf);

void mlxsw_reg_sbhbr_v2_hist_type_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_sbhbr_v2_hist_min_value_get(const char *buf);

void mlxsw_reg_sbhbr_v2_hist_min_value_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_sbhbr_v2_hist_max_value_get(const char *buf);

void mlxsw_reg_sbhbr_v2_hist_max_value_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_sbhbr_v2_sample_time_get(const char *buf);

void mlxsw_reg_sbhbr_v2_sample_time_set(char *buf, uint8_t val);

/* tnqcr
 * -----
 *
 */
#define MLXSW_TNQCR_ID 0xa010
#define MLXSW_TNQCR_LEN 0xc

uint8_t mlxsw_reg_tnqcr_enc_set_dscp_get(const char *buf);

void mlxsw_reg_tnqcr_enc_set_dscp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnqcr_enc_set_sp_get(const char *buf);

void mlxsw_reg_tnqcr_enc_set_sp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnqcr_enc_dscp_rw_get(const char *buf);

void mlxsw_reg_tnqcr_enc_dscp_rw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnqcr_enc_pcp_rw_get(const char *buf);

void mlxsw_reg_tnqcr_enc_pcp_rw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnqcr_dec_set_dscp_get(const char *buf);

void mlxsw_reg_tnqcr_dec_set_dscp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnqcr_dec_set_sp_get(const char *buf);

void mlxsw_reg_tnqcr_dec_set_sp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnqcr_dec_set_pcp_get(const char *buf);

void mlxsw_reg_tnqcr_dec_set_pcp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnqcr_dec_dscp_rw_get(const char *buf);

void mlxsw_reg_tnqcr_dec_dscp_rw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnqcr_dec_pcp_rw_get(const char *buf);

void mlxsw_reg_tnqcr_dec_pcp_rw_set(char *buf, uint8_t val);

/* sbhrr_v2
 * --------
 *
 */
#define MLXSW_SBHRR_V2_ID 0xb012
#define MLXSW_SBHRR_V2_BIN_BASE_LEN 0x40 /* base length, without records */
#define MLXSW_SBHRR_V2_BIN_REC_LEN 0x08 /* record length */
#define MLXSW_SBHRR_V2_BIN_REC_MAX_COUNT 10
#define MLXSW_SBHRR_V2_LEN 0x90

uint8_t mlxsw_reg_sbhrr_v2_clr_get(const char *buf);

void mlxsw_reg_sbhrr_v2_clr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbhrr_v2_local_port_get(const char *buf);

void mlxsw_reg_sbhrr_v2_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbhrr_v2_pg_buff_get(const char *buf);

void mlxsw_reg_sbhrr_v2_pg_buff_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbhrr_v2_lp_msb_get(const char *buf);

void mlxsw_reg_sbhrr_v2_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbhrr_v2_dir_get(const char *buf);

void mlxsw_reg_sbhrr_v2_dir_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sbhrr_v2_hist_type_get(const char *buf);

void mlxsw_reg_sbhrr_v2_hist_type_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_sbhrr_v2_min_sampled_high_get(const char *buf);

uint32_t mlxsw_reg_sbhrr_v2_min_sampled_low_get(const char *buf);

uint32_t mlxsw_reg_sbhrr_v2_max_sampled_high_get(const char *buf);

uint32_t mlxsw_reg_sbhrr_v2_max_sampled_low_get(const char *buf);

uint32_t mlxsw_reg_sbhrr_v2_hi_get(const char *buf, unsigned short index);

void mlxsw_reg_sbhrr_v2_hi_set(char *buf, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_sbhrr_v2_lo_get(const char *buf, unsigned short index);

void mlxsw_reg_sbhrr_v2_lo_set(char *buf, unsigned short index, uint32_t val);

/* pbsr
 * ----
 *
 */
#define MLXSW_PBSR_ID 0x5038
#define MLXSW_PBSR_STAT_BUFFER_BASE_LEN 0x0c /* base length, without records */
#define MLXSW_PBSR_STAT_BUFFER_REC_LEN 0x08 /* record length */
#define MLXSW_PBSR_STAT_BUFFER_REC_MAX_COUNT 10
#define MLXSW_PBSR_LEN 0x64

uint8_t mlxsw_reg_pbsr_local_port_get(const char *buf);

void mlxsw_reg_pbsr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pbsr_lp_msb_get(const char *buf);

void mlxsw_reg_pbsr_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pbsr_buffer_type_get(const char *buf);

void mlxsw_reg_pbsr_buffer_type_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pbsr_clear_wm_buff_mask_get(const char *buf);

void mlxsw_reg_pbsr_clear_wm_buff_mask_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_pbsr_clear_wm_get(const char *buf);

void mlxsw_reg_pbsr_clear_wm_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pbsr_used_shared_headroom_buffer_get(const char *buf);

uint16_t mlxsw_reg_pbsr_stat_buffer_watermark_get(const char *buf, unsigned short index);

uint16_t mlxsw_reg_pbsr_stat_buffer_used_buffer_get(const char *buf, unsigned short index);

uint16_t mlxsw_reg_pbsr_stat_shared_headroom_pool_watermark_get(const char *buf);

uint16_t mlxsw_reg_pbsr_stat_shared_headroom_pool_used_buffer_get(const char *buf);

/* rxltm
 * -----
 *
 */
#define MLXSW_RXLTM_ID 0x8051
#define MLXSW_RXLTM_LEN 0x14

uint8_t mlxsw_reg_rxltm_m_sel_update_get(const char *buf);

void mlxsw_reg_rxltm_m_sel_update_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rxltm_go_m_sel_get(const char *buf);

void mlxsw_reg_rxltm_go_m_sel_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rxltm_m_sel_get(const char *buf);

void mlxsw_reg_rxltm_m_sel_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rxltm_m1_val_v6_get(const char *buf);

void mlxsw_reg_rxltm_m1_val_v6_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rxltm_m0_val_v6_get(const char *buf);

void mlxsw_reg_rxltm_m0_val_v6_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rxltm_m1_val_v4_get(const char *buf);

void mlxsw_reg_rxltm_m1_val_v4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rxltm_m0_val_v4_get(const char *buf);

void mlxsw_reg_rxltm_m0_val_v4_set(char *buf, uint8_t val);

/* momte
 * -----
 *
 */
#define MLXSW_MOMTE_ID 0x908d
#define MLXSW_MOMTE_LEN 0x10

uint8_t mlxsw_reg_momte_swid_get(const char *buf);

void mlxsw_reg_momte_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_momte_local_port_get(const char *buf);

void mlxsw_reg_momte_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_momte_lp_msb_get(const char *buf);

void mlxsw_reg_momte_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_momte_mngr_type_get(const char *buf);

void mlxsw_reg_momte_mngr_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_momte_type_get(const char *buf);

void mlxsw_reg_momte_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_momte_tclass_en_high_get(const char *buf);

void mlxsw_reg_momte_tclass_en_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_momte_tclass_en_low_get(const char *buf);

void mlxsw_reg_momte_tclass_en_low_set(char *buf, uint32_t val);

/* rmpe
 * ----
 *
 */
#define MLXSW_RMPE_ID 0x8031
#define MLXSW_RMPE_LEN 0xc

uint8_t mlxsw_reg_rmpe_local_port_get(const char *buf);

void mlxsw_reg_rmpe_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rmpe_lp_msb_get(const char *buf);

void mlxsw_reg_rmpe_lp_msb_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_rmpe_rmpe_index_get(const char *buf);

void mlxsw_reg_rmpe_rmpe_index_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_rmpe_erif_get(const char *buf);

void mlxsw_reg_rmpe_erif_set(char *buf, uint16_t val);

/* svfa
 * ----
 *
 */
#define MLXSW_SVFA_ID 0x201c
#define MLXSW_SVFA_LEN 0x18

uint8_t mlxsw_reg_svfa_swid_get(const char *buf);

void mlxsw_reg_svfa_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_svfa_local_port_get(const char *buf);

void mlxsw_reg_svfa_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_svfa_lp_msb_get(const char *buf);

void mlxsw_reg_svfa_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_svfa_mapping_table_get(const char *buf);

void mlxsw_reg_svfa_mapping_table_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_svfa_tport_get(const char *buf);

void mlxsw_reg_svfa_tport_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_svfa_v_get(const char *buf);

void mlxsw_reg_svfa_v_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_svfa_fid_get(const char *buf);

void mlxsw_reg_svfa_fid_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_svfa_vid_get(const char *buf);

void mlxsw_reg_svfa_vid_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_svfa_counter_set_type_get(const char *buf);

void mlxsw_reg_svfa_counter_set_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_svfa_counter_index_get(const char *buf);

void mlxsw_reg_svfa_counter_index_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_svfa_trap_action_get(const char *buf);

void mlxsw_reg_svfa_trap_action_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_svfa_vni_get(const char *buf);

void mlxsw_reg_svfa_vni_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_svfa_irif_v_get(const char *buf);

void mlxsw_reg_svfa_irif_v_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_svfa_irif_get(const char *buf);

void mlxsw_reg_svfa_irif_set(char *buf, uint16_t val);

/* mafri
 * -----
 *
 */
#define MLXSW_MAFRI_ID 0x908c
#define MLXSW_MAFRI_RECORD_BASE_LEN 0x10 /* base length, without records */
#define MLXSW_MAFRI_RECORD_REC_LEN 0x08 /* record length */
#define MLXSW_MAFRI_RECORD_REC_MAX_COUNT 32
#define MLXSW_MAFRI_LEN 0x110

uint8_t mlxsw_reg_mafri_num_rec_get(const char *buf);

void mlxsw_reg_mafri_num_rec_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mafri_counter_index_base_get(const char *buf);

void mlxsw_reg_mafri_counter_index_base_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mafri_bytes_inc_get(const char *buf, unsigned short index);

uint32_t mlxsw_reg_mafri_packets_inc_get(const char *buf, unsigned short index);

/* sbsrd
 * -----
 *
 */
#define MLXSW_SBSRD_ID 0xb015
#define MLXSW_SBSRD_SHARED_BUFFER_STATUS_BASE_LEN 0x10 /* base length, without records */
#define MLXSW_SBSRD_SHARED_BUFFER_STATUS_REC_LEN 0x08 /* record length */
#define MLXSW_SBSRD_SHARED_BUFFER_STATUS_REC_MAX_COUNT 128
#define MLXSW_SBSRD_LEN 0x410

uint8_t mlxsw_reg_sbsrd_clr_get(const char *buf);

void mlxsw_reg_sbsrd_clr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbsrd_snap_get(const char *buf);

void mlxsw_reg_sbsrd_snap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbsrd_desc_get(const char *buf);

void mlxsw_reg_sbsrd_desc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbsrd_type_get(const char *buf);

void mlxsw_reg_sbsrd_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbsrd_num_rec_get(const char *buf);

void mlxsw_reg_sbsrd_num_rec_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sbsrd_fisrt_entry_index_get(const char *buf);

uint8_t mlxsw_reg_sbsrd_first_lp_msb_get(const char *buf);

void mlxsw_reg_sbsrd_first_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbsrd_first_local_port_get(const char *buf);

void mlxsw_reg_sbsrd_first_local_port_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_sbsrd_buff_occupancy_get(const char *buf, unsigned short index);

uint32_t mlxsw_reg_sbsrd_max_buff_occupancy_get(const char *buf, unsigned short index);

/* fphtt
 * -----
 *
 */
#define MLXSW_FPHTT_ID 0x4883
#define MLXSW_FPHTT_LEN 0x8

uint8_t mlxsw_reg_fphtt_entry_index_get(const char *buf);

void mlxsw_reg_fphtt_entry_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fphtt_tran_en_get(const char *buf);

void mlxsw_reg_fphtt_tran_en_set(char *buf, uint8_t val);

/* mcc
 * ---
 *
 */
#define MLXSW_MCC_ID 0x9062
#define MLXSW_MCC_LEN 0x20

uint16_t mlxsw_reg_mcc_time_elapsed_since_last_cmd_get(const char *buf);

uint8_t mlxsw_reg_mcc_activation_delay_sec_get(const char *buf);

void mlxsw_reg_mcc_activation_delay_sec_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcc_instruction_get(const char *buf);

void mlxsw_reg_mcc_instruction_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mcc_component_index_get(const char *buf);

void mlxsw_reg_mcc_component_index_set(char *buf, uint16_t val);

void mlxsw_reg_mcc_auto_update_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mcc_update_handle_get(const char *buf);

void mlxsw_reg_mcc_update_handle_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_mcc_handle_owner_type_get(const char *buf);

uint8_t mlxsw_reg_mcc_handle_owner_host_id_get(const char *buf);

uint8_t mlxsw_reg_mcc_control_progress_get(const char *buf);

uint8_t mlxsw_reg_mcc_error_code_get(const char *buf);

uint8_t mlxsw_reg_mcc_control_state_get(const char *buf);

void mlxsw_reg_mcc_component_size_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_mcc_device_index_get(const char *buf);

void mlxsw_reg_mcc_device_index_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mcc_device_type_get(const char *buf);

void mlxsw_reg_mcc_device_type_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mcc_rejected_device_index_get(const char *buf);

uint16_t mlxsw_reg_mcc_device_index_size_get(const char *buf);

void mlxsw_reg_mcc_device_index_size_set(char *buf, uint16_t val);

/* sfdb
 * ----
 *
 */
#define MLXSW_SFDB_ID 0x2028
#define MLXSW_SFDB_LEN 0x48

uint8_t mlxsw_reg_sfdb_policy_get(const char *buf);

void mlxsw_reg_sfdb_policy_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfdb_update_type_get(const char *buf);

void mlxsw_reg_sfdb_update_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfdb_gfid_get(const char *buf);

void mlxsw_reg_sfdb_gfid_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sfdb_entry_fid_get(const char *buf);

void mlxsw_reg_sfdb_entry_fid_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_sfdb_parameter_get(const char *buf);

void mlxsw_reg_sfdb_parameter_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_sfdb_parameter1_get(const char *buf);

void mlxsw_reg_sfdb_parameter1_set(char *buf, uint32_t val);

void mlxsw_reg_sfdb_new_parameter_set(char *buf, uint32_t val);

void mlxsw_reg_sfdb_new_parameter1_set(char *buf, uint32_t val);

/* pmtps
 * -----
 *
 */
#define MLXSW_PMTPS_ID 0x5060
#define MLXSW_PMTPS_LEN 0x20

uint8_t mlxsw_reg_pmtps_slot_index_get(const char *buf);

void mlxsw_reg_pmtps_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmtps_module_get(const char *buf);

void mlxsw_reg_pmtps_module_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pmtps_module_type_admin_get(const char *buf);

void mlxsw_reg_pmtps_module_type_admin_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pmtps_module_type_connected_get(const char *buf);

uint32_t mlxsw_reg_pmtps_eth_module_c2m_get(const char *buf);

uint16_t mlxsw_reg_pmtps_ib_width_module_c2m_get(const char *buf);

uint16_t mlxsw_reg_pmtps_ib_speed_module_c2m_get(const char *buf);

/* rxltcc
 * ------
 *
 */
#define MLXSW_RXLTCC_ID 0x8052
#define MLXSW_RXLTCC_LEN 0x68

uint8_t mlxsw_reg_rxltcc_clear_get(const char *buf);

void mlxsw_reg_rxltcc_clear_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rxltcc_hit_ipv4_m_high_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_hit_ipv4_m_low_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_hit_ipv4_ml_high_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_hit_ipv4_ml_low_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_miss_ipv4_m_high_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_miss_ipv4_m_low_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_miss_ipv4_ml_high_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_miss_ipv4_ml_low_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_learned_ipv4_high_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_learned_ipv4_low_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_hit_ipv6_m_high_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_hit_ipv6_m_low_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_hit_ipv6_ml_high_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_hit_ipv6_ml_low_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_miss_ipv6_m_high_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_miss_ipv6_m_low_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_miss_ipv6_ml_high_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_miss_ipv6_ml_low_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_learned_ipv6_high_get(const char *buf);

uint32_t mlxsw_reg_rxltcc_learned_ipv6_low_get(const char *buf);

/* sbhpc
 * -----
 *
 */
#define MLXSW_SBHPC_ID 0xb013
#define MLXSW_SBHPC_LEN 0x24

uint32_t mlxsw_reg_sbhpc_max_buff_get(const char *buf);

void mlxsw_reg_sbhpc_max_buff_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_sbhpc_buff_occupancy_get(const char *buf);

/* mbct
 * ----
 *
 */
#define MLXSW_MBCT_ID 0x9120
#define MLXSW_MBCT_LEN 0x420

uint8_t mlxsw_reg_mbct_slot_index_get(const char *buf);

void mlxsw_reg_mbct_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mbct_ini_status_get(const char *buf);

void mlxsw_reg_mbct_data_size_set(char *buf, uint16_t val);

void mlxsw_reg_mbct_op_set(char *buf, uint8_t val);

void mlxsw_reg_mbct_last_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mbct_status_get(const char *buf);

uint8_t mlxsw_reg_mbct_fsm_state_get(const char *buf);

void mlxsw_reg_mbct_data_set(char *buf, unsigned short index, uint32_t val);

/* mcda
 * ----
 *
 */
#define MLXSW_MCDA_ID 0x9063
#define MLXSW_MCDA_LEN 0x90

uint32_t mlxsw_reg_mcda_update_handle_get(const char *buf);

void mlxsw_reg_mcda_update_handle_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mcda_offset_get(const char *buf);

void mlxsw_reg_mcda_offset_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_mcda_size_get(const char *buf);

void mlxsw_reg_mcda_size_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_mcda_data_get(const char *buf, unsigned short index);

void mlxsw_reg_mcda_data_set(char *buf, unsigned short index, uint32_t val);



#endif /* _MLXSW_REG_H */
