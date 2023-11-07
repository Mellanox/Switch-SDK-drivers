/*
 * Copyright (c) 2017-2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */


/*
 * THIS FILE IS AUTO GENERATED.
 * DO NOT MAKE ANY CHANGES!
 * They will be erased with next update.
 *
 */

#ifndef _MLXSW_REG_H
#define _MLXSW_REG_H

/* hgcr
 * ----
 *
 */
#define MLXSW_HGCR_ID 0x7000
#define MLXSW_HGCR_LEN 0x1c

uint16_t mlxsw_reg_hgcr_truncation_size_get(const char *buf);

void mlxsw_reg_hgcr_truncation_size_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_hgcr_rcv_fcs_mode_get(const char *buf);

void mlxsw_reg_hgcr_rcv_fcs_mode_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_hgcr_rcv_fcs_value_get(const char *buf);

void mlxsw_reg_hgcr_rcv_fcs_value_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_hgcr_truncation_size_prof1_get(const char *buf);

void mlxsw_reg_hgcr_truncation_size_prof1_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_hgcr_truncation_size_prof2_get(const char *buf);

void mlxsw_reg_hgcr_truncation_size_prof2_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_hgcr_tac_mirror_action_get(const char *buf);

void mlxsw_reg_hgcr_tac_mirror_action_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hgcr_tac_crawler_timer_get(const char *buf);

void mlxsw_reg_hgcr_tac_crawler_timer_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hgcr_tac_crawler_action_get(const char *buf);

void mlxsw_reg_hgcr_tac_crawler_action_set(char *buf, uint8_t val);

/* hmon
 * ----
 *
 */
#define MLXSW_HMON_ID 0x7084
#define MLXSW_HMON_LEN 0x220

uint8_t mlxsw_reg_hmon_clr_get(const char *buf);

void mlxsw_reg_hmon_clr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hmon_cprdq_get(const char *buf);

void mlxsw_reg_hmon_cprdq_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hmon_read_type_get(const char *buf);

void mlxsw_reg_hmon_read_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hmon_crdq_get(const char *buf);

void mlxsw_reg_hmon_crdq_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hmon_wqe_of_wrap_get(const char *buf);

uint32_t mlxsw_reg_hmon_wqe_overflow_high_get(const char *buf);

uint32_t mlxsw_reg_hmon_wqe_overflow_low_get(const char *buf);

uint64_t mlxsw_reg_hmon_wqe_overflow_rdq_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_hmon_wqe_overflow_rdq_set(char *buf, unsigned short outer_index, unsigned short index, uint64_t val);

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

uint8_t mlxsw_reg_hrdqt_mirror_agent_get(const char *buf);

void mlxsw_reg_hrdqt_mirror_agent_set(char *buf, uint8_t val);

/* htacg
 * -----
 *
 */
#define MLXSW_HTACG_ID 0x7023
#define MLXSW_HTACG_LEN 0x90

uint8_t mlxsw_reg_htacg_status_get(const char *buf);

uint8_t mlxsw_reg_htacg_tac_flush_get(const char *buf);

void mlxsw_reg_htacg_tac_flush_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htacg_fields_mirror_reason_get(const char *buf);

void mlxsw_reg_htacg_fields_mirror_reason_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htacg_fields_rdq_get(const char *buf);

void mlxsw_reg_htacg_fields_rdq_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_htacg_fields_trap_id_get(const char *buf);

void mlxsw_reg_htacg_fields_trap_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_htacg_fields_traffic_class_get(const char *buf);

void mlxsw_reg_htacg_fields_traffic_class_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htacg_fields_tx_get(const char *buf);

void mlxsw_reg_htacg_fields_tx_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_htacg_fields_max_mirror_cong_get(const char *buf);

void mlxsw_reg_htacg_fields_max_mirror_cong_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_htacg_fields_last_ts_get(const char *buf);

void mlxsw_reg_htacg_fields_last_ts_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_htacg_fields_packet_count_get(const char *buf);

void mlxsw_reg_htacg_fields_packet_count_set(char *buf, uint32_t val);

void mlxsw_reg_htacg_fields_byte_count_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_htacg_fields_byte_count_memcpy_to(char *buf, const char *src);

uint8_t mlxsw_reg_htacg_mask_mirror_reason_get(const char *buf);

void mlxsw_reg_htacg_mask_mirror_reason_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htacg_mask_rdq_get(const char *buf);

void mlxsw_reg_htacg_mask_rdq_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_htacg_mask_trap_id_get(const char *buf);

void mlxsw_reg_htacg_mask_trap_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_htacg_mask_traffic_class_get(const char *buf);

void mlxsw_reg_htacg_mask_traffic_class_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htacg_mask_tx_get(const char *buf);

void mlxsw_reg_htacg_mask_tx_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_htacg_mask_max_mirror_cong_get(const char *buf);

void mlxsw_reg_htacg_mask_max_mirror_cong_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_htacg_mask_last_ts_get(const char *buf);

void mlxsw_reg_htacg_mask_last_ts_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_htacg_mask_packet_count_get(const char *buf);

void mlxsw_reg_htacg_mask_packet_count_set(char *buf, uint32_t val);

void mlxsw_reg_htacg_mask_byte_count_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_htacg_mask_byte_count_memcpy_to(char *buf, const char *src);

/* hett
 * ----
 *
 */
#define MLXSW_HETT_ID 0x7089
#define MLXSW_HETT_LEN 0x14

void mlxsw_reg_hett_opcode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hett_status_get(const char *buf);

uint64_t mlxsw_reg_hett_trap_group_bitmap_get(const char *buf);

void mlxsw_reg_hett_trap_group_bitmap_set(char *buf, uint64_t val);

uint8_t mlxsw_reg_hett_trap_group_get(const char *buf);

/* hccr
 * ----
 *
 */
#define MLXSW_HCCR_ID 0x7095
#define MLXSW_HCCR_LEN 0x4

uint8_t mlxsw_reg_hccr_use_nve_opt_chk_get(const char *buf);

void mlxsw_reg_hccr_use_nve_opt_chk_set(char *buf, uint8_t val);

/* htec
 * ----
 *
 */
#define MLXSW_HTEC_ID 0x7092
#define MLXSW_HTEC_LEN 0x30

void mlxsw_reg_htec_dmac_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_htec_dmac_memcpy_to(char *buf, const char *src);

void mlxsw_reg_htec_smac_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_htec_smac_memcpy_to(char *buf, const char *src);

uint16_t mlxsw_reg_htec_ethertype_get(const char *buf);

void mlxsw_reg_htec_ethertype_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_htec_mlnx_proto_get(const char *buf);

void mlxsw_reg_htec_mlnx_proto_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htec_ver_get(const char *buf);

void mlxsw_reg_htec_ver_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htec_res_0_get(const char *buf);

void mlxsw_reg_htec_res_0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htec_op_type_get(const char *buf);

void mlxsw_reg_htec_op_type_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_htec_op_len_get(const char *buf);

void mlxsw_reg_htec_op_len_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_htec_dr_get(const char *buf);

void mlxsw_reg_htec_dr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htec_status_get(const char *buf);

void mlxsw_reg_htec_status_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htec_gas_get(const char *buf);

void mlxsw_reg_htec_gas_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htec_res_1_get(const char *buf);

void mlxsw_reg_htec_res_1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htec_stat_details_get(const char *buf);

void mlxsw_reg_htec_stat_details_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_htec_register_id_get(const char *buf);

void mlxsw_reg_htec_register_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_htec_r_get(const char *buf);

void mlxsw_reg_htec_r_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htec_method_get(const char *buf);

void mlxsw_reg_htec_method_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htec_res_2_get(const char *buf);

void mlxsw_reg_htec_res_2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htec_trap_index_get(const char *buf);

void mlxsw_reg_htec_trap_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_htec_emad_class_get(const char *buf);

void mlxsw_reg_htec_emad_class_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_htec_tid_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_htec_tid_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_htec_raw_data_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_htec_raw_data_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_htec_reg_tlv_type_get(const char *buf);

void mlxsw_reg_htec_reg_tlv_type_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_htec_res_reg_tlv_get(const char *buf);

void mlxsw_reg_htec_res_reg_tlv_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_htec_new_hdr_type_get(const char *buf);

void mlxsw_reg_htec_new_hdr_type_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_htec_res_4_new_get(const char *buf);

void mlxsw_reg_htec_res_4_new_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_htec_agg_hdr_type_get(const char *buf);

void mlxsw_reg_htec_agg_hdr_type_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_htec_res_4_agg_get(const char *buf);

void mlxsw_reg_htec_res_4_agg_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_htec_end_tlv_type_get(const char *buf);

void mlxsw_reg_htec_end_tlv_type_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_htec_end_tlv_len_get(const char *buf);

void mlxsw_reg_htec_end_tlv_len_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_htec_res_end_tlv_get(const char *buf);

void mlxsw_reg_htec_res_end_tlv_set(char *buf, uint16_t val);

/* htcr
 * ----
 *
 */
#define MLXSW_HTCR_ID 0x7093
#define MLXSW_HTCR_LEN 0x210

uint8_t mlxsw_reg_htcr_clr_get(const char *buf);

void mlxsw_reg_htcr_clr_set(char *buf, uint8_t val);

uint64_t mlxsw_reg_htcr_tac_received_pkts_get(const char *buf);

uint64_t mlxsw_reg_htcr_ingress_drop_rdq_get(const char *buf, unsigned short outer_index, unsigned short index);

/* hcpnc
 * -----
 *
 */
#define MLXSW_HCPNC_ID 0x7096
#define MLXSW_HCPNC_LEN 0x20

uint8_t mlxsw_reg_hcpnc_clr_get(const char *buf);

void mlxsw_reg_hcpnc_clr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_hcpnc_cnt_type_get(const char *buf);

void mlxsw_reg_hcpnc_cnt_type_set(char *buf, uint8_t val);

uint64_t mlxsw_reg_hcpnc_pkt_ok_cnt_get(const char *buf);

uint64_t mlxsw_reg_hcpnc_byte_ok_cnt_get(const char *buf);

uint64_t mlxsw_reg_hcpnc_pkt_discard_cnt_get(const char *buf);

/* mtpps
 * -----
 *
 */
#define MLXSW_MTPPS_ID 0x9053
#define MLXSW_MTPPS_LEN 0x38

uint8_t mlxsw_reg_mtpps_cap_number_of_pps_pins_get(const char *buf);

uint8_t mlxsw_reg_mtpps_cap_max_num_of_pps_in_pins_get(const char *buf);

uint8_t mlxsw_reg_mtpps_cap_max_num_of_pps_out_pins_get(const char *buf);

uint8_t mlxsw_reg_mtpps_cap_pin_3_mode_get(const char *buf);

uint8_t mlxsw_reg_mtpps_cap_pin_2_mode_get(const char *buf);

uint8_t mlxsw_reg_mtpps_cap_pin_1_mode_get(const char *buf);

uint8_t mlxsw_reg_mtpps_cap_pin_0_mode_get(const char *buf);

uint8_t mlxsw_reg_mtpps_cap_pin_7_mode_get(const char *buf);

uint8_t mlxsw_reg_mtpps_cap_pin_6_mode_get(const char *buf);

uint8_t mlxsw_reg_mtpps_cap_pin_5_mode_get(const char *buf);

uint8_t mlxsw_reg_mtpps_cap_pin_4_mode_get(const char *buf);

void mlxsw_reg_mtpps_field_select_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_mtpps_enable_get(const char *buf);

void mlxsw_reg_mtpps_enable_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtpps_utc_mode_get(const char *buf);

void mlxsw_reg_mtpps_utc_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtpps_pattern_get(const char *buf);

void mlxsw_reg_mtpps_pattern_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtpps_pin_mode_get(const char *buf);

void mlxsw_reg_mtpps_pin_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtpps_pin_get(const char *buf);

void mlxsw_reg_mtpps_pin_set(char *buf, uint8_t val);

uint64_t mlxsw_reg_mtpps_time_stamp_get(const char *buf);

void mlxsw_reg_mtpps_time_stamp_set(char *buf, uint64_t val);

uint16_t mlxsw_reg_mtpps_out_pulse_duration_get(const char *buf);

void mlxsw_reg_mtpps_out_pulse_duration_set(char *buf, uint16_t val);

/* mtppse
 * ------
 *
 */
#define MLXSW_MTPPSE_ID 0x9054
#define MLXSW_MTPPSE_LEN 0x10

uint8_t mlxsw_reg_mtppse_pin_get(const char *buf);

void mlxsw_reg_mtppse_pin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtppse_event_arm_get(const char *buf);

void mlxsw_reg_mtppse_event_arm_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtppse_event_generation_mode_get(const char *buf);

void mlxsw_reg_mtppse_event_generation_mode_set(char *buf, uint8_t val);

/* mtutc
 * -----
 *
 */
#define MLXSW_MTUTC_ID 0x9055
#define MLXSW_MTUTC_LEN 0x1c

uint8_t mlxsw_reg_mtutc_freq_adj_units_get(const char *buf);

void mlxsw_reg_mtutc_freq_adj_units_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtutc_log_max_freq_adjustment_get(const char *buf);

uint16_t mlxsw_reg_mtutc_log_max_phase_adjustment_get(const char *buf);

uint8_t mlxsw_reg_mtutc_operation_get(const char *buf);

void mlxsw_reg_mtutc_operation_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mtutc_freq_adjustment_get(const char *buf);

void mlxsw_reg_mtutc_freq_adjustment_set(char *buf, uint32_t val);

void mlxsw_reg_mtutc_utc_sec_set(char *buf, uint32_t val);

void mlxsw_reg_mtutc_utc_nsec_set(char *buf, uint32_t val);

void mlxsw_reg_mtutc_time_adjustment_set(char *buf, uint32_t val);

/* mtppst
 * ------
 *
 */
#define MLXSW_MTPPST_ID 0x9057
#define MLXSW_MTPPST_LEN 0x10

uint8_t mlxsw_reg_mtppst_pin_get(const char *buf);

void mlxsw_reg_mtppst_pin_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mtppst_timestamp_msb_get(const char *buf);

uint32_t mlxsw_reg_mtppst_timestamp_lsb_get(const char *buf);

/* msecq
 * -----
 *
 */
#define MLXSW_MSECQ_ID 0x9155
#define MLXSW_MSECQ_LEN 0x40

uint8_t mlxsw_reg_msecq_network_option_get(const char *buf);

uint8_t mlxsw_reg_msecq_local_ssm_code_get(const char *buf);

uint8_t mlxsw_reg_msecq_local_enhanced_ssm_code_get(const char *buf);

uint64_t mlxsw_reg_msecq_local_clock_identity_get(const char *buf);

/* msees
 * -----
 *
 */
#define MLXSW_MSEES_ID 0x9156
#define MLXSW_MSEES_LEN 0x40

uint8_t mlxsw_reg_msees_local_port_get(const char *buf);

void mlxsw_reg_msees_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_msees_pnat_get(const char *buf);

void mlxsw_reg_msees_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_msees_lp_msb_get(const char *buf);

void mlxsw_reg_msees_lp_msb_set(char *buf, uint8_t val);

void mlxsw_reg_msees_field_select_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_msees_admin_status_get(const char *buf);

void mlxsw_reg_msees_admin_status_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_msees_oper_status_get(const char *buf);

uint8_t mlxsw_reg_msees_ho_acq_get(const char *buf);

uint8_t mlxsw_reg_msees_admin_freq_measure_get(const char *buf);

void mlxsw_reg_msees_admin_freq_measure_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_msees_oper_freq_measure_get(const char *buf);

uint16_t mlxsw_reg_msees_failure_reason_get(const char *buf);

uint32_t mlxsw_reg_msees_frequency_diff_get(const char *buf);

/* mspi
 * ----
 *
 */
#define MLXSW_MSPI_ID 0x9029
#define MLXSW_MSPI_LEN 0x18

uint8_t mlxsw_reg_mspi_synce_support_get(const char *buf);

uint8_t mlxsw_reg_mspi_vendor_id_get(const char *buf);

uint16_t mlxsw_reg_mspi_config_version_id_get(const char *buf);

uint8_t mlxsw_reg_mspi_bcc_get(const char *buf);

uint8_t mlxsw_reg_mspi_obtv_get(const char *buf);

uint16_t mlxsw_reg_mspi_obs_temperature_get(const char *buf);

uint8_t mlxsw_reg_mspi_bitv_get(const char *buf);

uint16_t mlxsw_reg_mspi_bis_temperature_get(const char *buf);

/* mcion
 * -----
 *
 */
#define MLXSW_MCION_ID 0x9052
#define MLXSW_MCION_LEN 0x18

uint8_t mlxsw_reg_mcion_module_get(const char *buf);

void mlxsw_reg_mcion_module_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcion_slot_index_get(const char *buf);

void mlxsw_reg_mcion_slot_index_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mcion_module_status_bits_get(const char *buf);

uint16_t mlxsw_reg_mcion_module_status_bits_valid_get(const char *buf);

uint8_t mlxsw_reg_mcion_module_inputs_get(const char *buf);

void mlxsw_reg_mcion_module_inputs_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcion_module_inputs_mask_get(const char *buf);

void mlxsw_reg_mcion_module_inputs_mask_set(char *buf, uint8_t val);

/* mcfs
 * ----
 *
 */
#define MLXSW_MCFS_ID 0x9165
#define MLXSW_MCFS_LEN 0x20

uint8_t mlxsw_reg_mcfs_module_get(const char *buf);

void mlxsw_reg_mcfs_module_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcfs_slot_index_get(const char *buf);

void mlxsw_reg_mcfs_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcfs_freq_get(const char *buf);

void mlxsw_reg_mcfs_freq_set(char *buf, uint8_t val);

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

uint8_t mlxsw_reg_mddt_status_get(const char *buf);

uint8_t mlxsw_reg_mddt_method_get(const char *buf);

void mlxsw_reg_mddt_method_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mddt_register_id_get(const char *buf);

void mlxsw_reg_mddt_register_id_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_mddt_register_data_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mddt_register_data_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_mddt_command_payload_data_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mddt_command_payload_data_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

void mlxsw_reg_mddt_crspace_access_payload_address_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mddt_crspace_access_payload_data_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mddt_crspace_access_payload_data_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

uint8_t mlxsw_reg_mddq_provisioned_get(const char *buf);

uint8_t mlxsw_reg_mddq_sr_valid_get(const char *buf);

uint8_t mlxsw_reg_mddq_lc_ready_get(const char *buf);

uint8_t mlxsw_reg_mddq_active_get(const char *buf);

uint16_t mlxsw_reg_mddq_hw_revision_get(const char *buf);

uint16_t mlxsw_reg_mddq_ini_file_version_get(const char *buf);

uint8_t mlxsw_reg_mddq_card_type_get(const char *buf);

uint8_t mlxsw_reg_mddq_uses_flash_get(const char *buf);

uint8_t mlxsw_reg_mddq_flash_owner_get(const char *buf);

uint8_t mlxsw_reg_mddq_thermal_sd_get(const char *buf);

uint8_t mlxsw_reg_mddq_lc_pwr_on_get(const char *buf);

uint8_t mlxsw_reg_mddq_flash_id_get(const char *buf);

uint8_t mlxsw_reg_mddq_device_index_get(const char *buf);

uint16_t mlxsw_reg_mddq_fw_major_get(const char *buf);

uint16_t mlxsw_reg_mddq_device_type_get(const char *buf);

uint16_t mlxsw_reg_mddq_fw_minor_get(const char *buf);

uint16_t mlxsw_reg_mddq_fw_sub_minor_get(const char *buf);

uint8_t mlxsw_reg_mddq_max_cmd_read_size_supp_get(const char *buf);

uint8_t mlxsw_reg_mddq_max_cmd_write_size_supp_get(const char *buf);

void mlxsw_reg_mddq_device_type_name_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_mddq_slot_ascii_name_memcpy_from(const char *buf, char *dst);

/* mddc
 * ----
 *
 */
#define MLXSW_MDDC_ID 0x9163
#define MLXSW_MDDC_LEN 0x30

uint8_t mlxsw_reg_mddc_level_get(const char *buf);

void mlxsw_reg_mddc_level_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mddc_index_get(const char *buf);

void mlxsw_reg_mddc_index_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_mddc_slot_index_get(const char *buf);

void mlxsw_reg_mddc_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddc_rst_get(const char *buf);

void mlxsw_reg_mddc_rst_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mddc_device_enable_get(const char *buf);

void mlxsw_reg_mddc_device_enable_set(char *buf, uint8_t val);

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

uint8_t mlxsw_reg_mgpir_first_pluggable_interconnect_offset_get(const char *buf);

uint8_t mlxsw_reg_mgpir_max_modules_per_slot_get(const char *buf);

uint8_t mlxsw_reg_mgpir_num_of_slots_get(const char *buf);

uint8_t mlxsw_reg_mgpir_num_of_modules_get(const char *buf);

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

/* mtecr
 * -----
 *
 */
#define MLXSW_MTECR_ID 0x9109
#define MLXSW_MTECR_LEN 0x60

uint16_t mlxsw_reg_mtecr_last_sensor_get(const char *buf);

uint16_t mlxsw_reg_mtecr_sensor_count_get(const char *buf);

uint8_t mlxsw_reg_mtecr_slot_index_get(const char *buf);

void mlxsw_reg_mtecr_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtecr_internal_sensor_count_get(const char *buf);

uint32_t mlxsw_reg_mtecr_sensor_map_get(const char *buf, unsigned short outer_index, unsigned short index);

/* mtcap
 * -----
 *
 */
#define MLXSW_MTCAP_ID 0x9009
#define MLXSW_MTCAP_LEN 0x10

uint8_t mlxsw_reg_mtcap_slot_index_get(const char *buf);

void mlxsw_reg_mtcap_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtcap_sensor_count_get(const char *buf);

uint8_t mlxsw_reg_mtcap_internal_sensor_count_get(const char *buf);

uint64_t mlxsw_reg_mtcap_sensor_map_get(const char *buf);

/* mtwe
 * ----
 *
 */
#define MLXSW_MTWE_ID 0x900b
#define MLXSW_MTWE_LEN 0x10

uint32_t mlxsw_reg_mtwe_sensor_warning_get(const char *buf, unsigned short outer_index, unsigned short index);

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

uint32_t mlxsw_reg_mtewe_sensor_warning_get(const char *buf, unsigned short outer_index, unsigned short index);

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

uint32_t mlxsw_reg_mtsde_sensor_shut_down_map_get(const char *buf, unsigned short outer_index, unsigned short index);

/* mvcap
 * -----
 *
 */
#define MLXSW_MVCAP_ID 0x902e
#define MLXSW_MVCAP_LEN 0x10

uint64_t mlxsw_reg_mvcap_sensor_map_get(const char *buf);

uint8_t mlxsw_reg_mvcap_slot_index_get(const char *buf);

void mlxsw_reg_mvcap_slot_index_set(char *buf, uint8_t val);

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

/* mvcr
 * ----
 *
 */
#define MLXSW_MVCR_ID 0x900c
#define MLXSW_MVCR_LEN 0x18

uint8_t mlxsw_reg_mvcr_slot_index_get(const char *buf);

void mlxsw_reg_mvcr_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mvcr_sensor_index_get(const char *buf);

void mlxsw_reg_mvcr_sensor_index_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mvcr_voltage_sensor_value_get(const char *buf);

uint16_t mlxsw_reg_mvcr_current_sensor_value_get(const char *buf);

uint64_t mlxsw_reg_mvcr_sensor_name_get(const char *buf);

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

uint32_t mlxsw_reg_mcqi_supported_info_bitmask_get(const char *buf);

uint32_t mlxsw_reg_mcqi_component_size_get(const char *buf);

uint32_t mlxsw_reg_mcqi_max_component_size_get(const char *buf);

uint8_t mlxsw_reg_mcqi_log_mcda_word_size_get(const char *buf);

uint16_t mlxsw_reg_mcqi_mcda_max_write_size_get(const char *buf);

uint8_t mlxsw_reg_mcqi_rd_en_get(const char *buf);

uint8_t mlxsw_reg_mcqi_signed_updates_only_get(const char *buf);

void mlxsw_reg_mcqi_signed_updates_only_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_match_chip_id_get(const char *buf);

void mlxsw_reg_mcqi_match_chip_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_match_psid_get(const char *buf);

void mlxsw_reg_mcqi_match_psid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_check_user_timestamp_get(const char *buf);

void mlxsw_reg_mcqi_check_user_timestamp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_match_base_guid_mac_get(const char *buf);

void mlxsw_reg_mcqi_match_base_guid_mac_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_build_time_valid_get(const char *buf);

void mlxsw_reg_mcqi_build_time_valid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_user_defined_time_valid_get(const char *buf);

void mlxsw_reg_mcqi_user_defined_time_valid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_version_string_length_get(const char *buf);

void mlxsw_reg_mcqi_version_string_length_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mcqi_version_get(const char *buf);

void mlxsw_reg_mcqi_version_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_mcqi_build_time_seconds_get(const char *buf);

void mlxsw_reg_mcqi_build_time_seconds_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_build_time_minutes_get(const char *buf);

void mlxsw_reg_mcqi_build_time_minutes_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_build_time_hours_get(const char *buf);

void mlxsw_reg_mcqi_build_time_hours_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mcqi_build_time_year_get(const char *buf);

void mlxsw_reg_mcqi_build_time_year_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mcqi_build_time_month_get(const char *buf);

void mlxsw_reg_mcqi_build_time_month_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_build_time_day_get(const char *buf);

void mlxsw_reg_mcqi_build_time_day_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_user_defined_time_seconds_get(const char *buf);

void mlxsw_reg_mcqi_user_defined_time_seconds_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_user_defined_time_minutes_get(const char *buf);

void mlxsw_reg_mcqi_user_defined_time_minutes_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_user_defined_time_hours_get(const char *buf);

void mlxsw_reg_mcqi_user_defined_time_hours_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mcqi_user_defined_time_year_get(const char *buf);

void mlxsw_reg_mcqi_user_defined_time_year_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mcqi_user_defined_time_month_get(const char *buf);

void mlxsw_reg_mcqi_user_defined_time_month_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcqi_user_defined_time_day_get(const char *buf);

void mlxsw_reg_mcqi_user_defined_time_day_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mcqi_build_tool_version_get(const char *buf);

void mlxsw_reg_mcqi_build_tool_version_set(char *buf, uint32_t val);

void mlxsw_reg_mcqi_version_string_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_mcqi_version_string_memcpy_to(char *buf, const char *src);

uint8_t mlxsw_reg_mcqi_self_activation_get(const char *buf);

uint8_t mlxsw_reg_mcqi_pending_server_ac_power_cycle_get(const char *buf);

uint8_t mlxsw_reg_mcqi_pending_server_dc_power_cycle_get(const char *buf);

uint8_t mlxsw_reg_mcqi_pending_server_reboot_get(const char *buf);

uint8_t mlxsw_reg_mcqi_pending_fw_reset_get(const char *buf);

uint8_t mlxsw_reg_mcqi_auto_activate_get(const char *buf);

uint8_t mlxsw_reg_mcqi_all_hosts_sync_get(const char *buf);

uint8_t mlxsw_reg_mcqi_fw_image_info_bitmap_get(const char *buf);

uint8_t mlxsw_reg_mcqi_fw_image_status_bitmap_get(const char *buf);

uint8_t mlxsw_reg_mcqi_image_a_major_get(const char *buf);

uint8_t mlxsw_reg_mcqi_image_a_minor_get(const char *buf);

uint16_t mlxsw_reg_mcqi_image_a_subminor_get(const char *buf);

uint8_t mlxsw_reg_mcqi_image_b_major_get(const char *buf);

uint8_t mlxsw_reg_mcqi_image_b_minor_get(const char *buf);

uint16_t mlxsw_reg_mcqi_image_b_subminor_get(const char *buf);

uint8_t mlxsw_reg_mcqi_factory_image_major_get(const char *buf);

uint8_t mlxsw_reg_mcqi_factory_image_minor_get(const char *buf);

uint16_t mlxsw_reg_mcqi_factory_image_subminor_get(const char *buf);

uint8_t mlxsw_reg_mcqi_activation_type_get(const char *buf);

uint8_t mlxsw_reg_mcqi_management_interface_protocol_get(const char *buf);

uint16_t mlxsw_reg_mcqi_vendor_sn_get(const char *buf);

uint8_t mlxsw_reg_mcqi_vendor_id_get(const char *buf);

uint8_t mlxsw_reg_mcqi_image_version_major_get(const char *buf);

uint8_t mlxsw_reg_mcqi_image_version_minor_get(const char *buf);

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

uint32_t mlxsw_reg_mcda_data_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mcda_data_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

uint8_t mlxsw_reg_mgir_fw_info_dev_sc_get(const char *buf);

uint8_t mlxsw_reg_mgir_fw_info_latency_tlv_get(const char *buf);

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

uint16_t mlxsw_reg_mgir_fw_info_disabled_tiles_bitmap_get(const char *buf);

uint16_t mlxsw_reg_mgir_fw_info_isfu_major_get(const char *buf);

uint8_t mlxsw_reg_mgir_fw_info_encryption_get(const char *buf);

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

/* msgi
 * ----
 *
 */
#define MLXSW_MSGI_ID 0x9021
#define MLXSW_MSGI_LEN 0x80

uint32_t mlxsw_reg_msgi_serial_number_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_msgi_part_number_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_msgi_revision_get(const char *buf);

uint32_t mlxsw_reg_msgi_manufacturing_date_get(const char *buf);

uint32_t mlxsw_reg_msgi_product_name_get(const char *buf, unsigned short outer_index, unsigned short index);

/* mdir
 * ----
 *
 */
#define MLXSW_MDIR_ID 0x911a
#define MLXSW_MDIR_LEN 0x40

uint32_t mlxsw_reg_mdir_device_id_get(const char *buf, unsigned short outer_index, unsigned short index);

/* mini
 * ----
 *
 */
#define MLXSW_MINI_ID 0x905e
#define MLXSW_MINI_LEN 0x50

uint16_t mlxsw_reg_mini_index_get(const char *buf);

void mlxsw_reg_mini_index_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mini_type_get(const char *buf);

void mlxsw_reg_mini_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mini_valid_get(const char *buf);

uint8_t mlxsw_reg_mini_module_gw_num_get(const char *buf);

uint8_t mlxsw_reg_mini_spl_get(const char *buf);

/* mcam
 * ----
 *
 */
#define MLXSW_MCAM_ID 0x907f
#define MLXSW_MCAM_LEN 0x48

uint8_t mlxsw_reg_mcam_feature_group_get(const char *buf);

void mlxsw_reg_mcam_feature_group_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mcam_access_reg_group_get(const char *buf);

void mlxsw_reg_mcam_access_reg_group_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mcam_mng_access_reg_cap_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_mcam_mng_feature_cap_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

/* meccc
 * -----
 *
 */
#define MLXSW_MECCC_ID 0x905f
#define MLXSW_MECCC_LEN 0x14

uint8_t mlxsw_reg_meccc_device_index_get(const char *buf);

void mlxsw_reg_meccc_device_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_meccc_slot_index_get(const char *buf);

void mlxsw_reg_meccc_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_meccc_clr_get(const char *buf);

void mlxsw_reg_meccc_clr_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_meccc_ecc_crt_cnt_get(const char *buf);

uint8_t mlxsw_reg_meccc_ecc_ucrt_cnt_get(const char *buf);

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

void mlxsw_reg_mbct_oee_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mbct_status_get(const char *buf);

uint8_t mlxsw_reg_mbct_fsm_state_get(const char *buf);

void mlxsw_reg_mbct_data_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* mtcq
 * ----
 *
 */
#define MLXSW_MTCQ_ID 0x9065
#define MLXSW_MTCQ_LEN 0x70

uint8_t mlxsw_reg_mtcq_token_opcode_get(const char *buf);

void mlxsw_reg_mtcq_token_opcode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtcq_status_get(const char *buf);

uint16_t mlxsw_reg_mtcq_device_index_get(const char *buf);

void mlxsw_reg_mtcq_device_index_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_mtcq_keypair_uuid_get(const char *buf, unsigned short outer_index, unsigned short index);

uint64_t mlxsw_reg_mtcq_base_mac_get(const char *buf);

uint32_t mlxsw_reg_mtcq_psid_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mtcq_fw_version_memcpy_from(const char *buf, char *dst);

uint32_t mlxsw_reg_mtcq_source_address_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_mtcq_challenge_version_get(const char *buf);

uint16_t mlxsw_reg_mtcq_session_id_get(const char *buf);

uint32_t mlxsw_reg_mtcq_challenge_get(const char *buf, unsigned short outer_index, unsigned short index);

/* mtrc_cap
 * --------
 *
 */
#define MLXSW_MTRC_CAP_ID 0x9040
#define MLXSW_MTRC_CAP_STRING_DB_PARAM_BASE_LEN 0x10 /* base length, without records */
#define MLXSW_MTRC_CAP_STRING_DB_PARAM_REC_LEN 0x08 /* record length */
#define MLXSW_MTRC_CAP_STRING_DB_PARAM_REC_MAX_COUNT 8
#define MLXSW_MTRC_CAP_LEN 0x84

uint8_t mlxsw_reg_mtrc_cap_trace_owner_get(const char *buf);

void mlxsw_reg_mtrc_cap_trace_owner_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtrc_cap_trace_to_memory_get(const char *buf);

uint8_t mlxsw_reg_mtrc_cap_trc_ver_get(const char *buf);

uint8_t mlxsw_reg_mtrc_cap_num_string_db_get(const char *buf);

uint8_t mlxsw_reg_mtrc_cap_first_string_trace_get(const char *buf);

uint8_t mlxsw_reg_mtrc_cap_num_string_trace_get(const char *buf);

uint8_t mlxsw_reg_mtrc_cap_tracer_capabilities_get(const char *buf);

uint8_t mlxsw_reg_mtrc_cap_log_max_trace_buffer_size_get(const char *buf);

uint32_t mlxsw_reg_mtrc_cap_string_db_base_address_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_mtrc_cap_string_db_size_get(const char *buf, unsigned short outer_index, unsigned short index);

/* mtrc_stdb_v2
 * ------------
 *
 */
#define MLXSW_MTRC_STDB_V2_ID 0x9210
#define MLXSW_MTRC_STDB_V2_LEN 0x5a0

uint8_t mlxsw_reg_mtrc_stdb_v2_string_db_index_get(const char *buf);

void mlxsw_reg_mtrc_stdb_v2_string_db_index_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mtrc_stdb_v2_read_size_get(const char *buf);

void mlxsw_reg_mtrc_stdb_v2_read_size_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mtrc_stdb_v2_start_offset_get(const char *buf);

void mlxsw_reg_mtrc_stdb_v2_start_offset_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mtrc_stdb_v2_string_db_data_get(const char *buf, unsigned short outer_index, unsigned short index);

/* mteim
 * -----
 *
 */
#define MLXSW_MTEIM_ID 0x9118
#define MLXSW_MTEIM_LEN 0x30

uint8_t mlxsw_reg_mteim_cap_num_of_tile_get(const char *buf);

uint8_t mlxsw_reg_mteim_cap_core_dpa_get(const char *buf);

uint8_t mlxsw_reg_mteim_cap_core_main_get(const char *buf);

uint8_t mlxsw_reg_mteim_cap_core_tile_get(const char *buf);

uint8_t mlxsw_reg_mteim_is_dwsn_msb_supported_get(const char *buf);

uint8_t mlxsw_reg_mteim_is_phy_uc_supported_get(const char *buf);

uint8_t mlxsw_reg_mteim_type_core_dpa_get(const char *buf);

uint8_t mlxsw_reg_mteim_type_core_main_get(const char *buf);

uint8_t mlxsw_reg_mteim_type_core_tile_get(const char *buf);

uint8_t mlxsw_reg_mteim_first_main_core_event_id_get(const char *buf);

uint8_t mlxsw_reg_mteim_first_dpa_core_event_id_get(const char *buf);

void mlxsw_reg_mteim_first_tile_core_event_id_memcpy_from(const char *buf, char *dst);

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

/* mfrc
 * ----
 *
 */
#define MLXSW_MFRC_ID 0x9069
#define MLXSW_MFRC_LEN 0xc

uint8_t mlxsw_reg_mfrc_trigger_get(const char *buf);

void mlxsw_reg_mfrc_trigger_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfrc_e_get(const char *buf);

void mlxsw_reg_mfrc_e_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mfrc_capability_bits_get(const char *buf);

uint8_t mlxsw_reg_mfrc_en_error_notification_get(const char *buf);

void mlxsw_reg_mfrc_en_error_notification_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfrc_en_warning_notification_get(const char *buf);

void mlxsw_reg_mfrc_en_warning_notification_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfrc_en_normal_notification_get(const char *buf);

void mlxsw_reg_mfrc_en_normal_notification_set(char *buf, uint8_t val);

/* mmcr
 * ----
 *
 */
#define MLXSW_MMCR_ID 0x906c
#define MLXSW_MMCR_LEN 0x30

uint32_t mlxsw_reg_mmcr_module_sw_control_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mmcr_module_sw_control_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_mmcr_module_control_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mmcr_module_control_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* mfri
 * ----
 *
 */
#define MLXSW_MFRI_ID 0x906b
#define MLXSW_MFRI_LEN 0x30

uint8_t mlxsw_reg_mfri_port_get(const char *buf);

void mlxsw_reg_mfri_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfri_trigger_get(const char *buf);

void mlxsw_reg_mfri_trigger_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfri_thr_type_get(const char *buf);

uint16_t mlxsw_reg_mfri_field_select_get(const char *buf);

uint16_t mlxsw_reg_mfri_fields_overflow_get(const char *buf);

uint32_t mlxsw_reg_mfri_num_errors_get(const char *buf);

uint32_t mlxsw_reg_mfri_num_warnings_get(const char *buf);

uint32_t mlxsw_reg_mfri_min_value_get(const char *buf);

uint32_t mlxsw_reg_mfri_max_value_get(const char *buf);

uint32_t mlxsw_reg_mfri_consecutive_normal_get(const char *buf);

uint32_t mlxsw_reg_mfri_last_value_get(const char *buf, unsigned short outer_index, unsigned short index);

/* mfrp
 * ----
 *
 */
#define MLXSW_MFRP_ID 0x906a
#define MLXSW_MFRP_LEN 0x1c

uint8_t mlxsw_reg_mfrp_local_port_get(const char *buf);

void mlxsw_reg_mfrp_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfrp_lp_msb_get(const char *buf);

void mlxsw_reg_mfrp_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfrp_trigger_get(const char *buf);

void mlxsw_reg_mfrp_trigger_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfrp_error_thr_action_get(const char *buf);

uint8_t mlxsw_reg_mfrp_en_thr_get(const char *buf);

uint32_t mlxsw_reg_mfrp_error_thr_get(const char *buf);

uint32_t mlxsw_reg_mfrp_warning_thr_get(const char *buf);

uint32_t mlxsw_reg_mfrp_normal_thr_get(const char *buf);

uint32_t mlxsw_reg_mfrp_time_window_get(const char *buf);

uint32_t mlxsw_reg_mfrp_sampling_rate_get(const char *buf);

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

/* mprs
 * ----
 *
 */
#define MLXSW_MPRS_ID 0x9083
#define MLXSW_MPRS_LEN 0x14

uint8_t mlxsw_reg_mprs_en_l4_raw_prs_get(const char *buf);

void mlxsw_reg_mprs_en_l4_raw_prs_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mprs_prs_depth_dis_get(const char *buf);

void mlxsw_reg_mprs_prs_depth_dis_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mprs_ctipl_dis_get(const char *buf);

void mlxsw_reg_mprs_ctipl_dis_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mprs_parsing_depth_get(const char *buf);

void mlxsw_reg_mprs_parsing_depth_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_mprs_parsing_en_get(const char *buf);

void mlxsw_reg_mprs_parsing_en_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mprs_ctipl_get(const char *buf);

void mlxsw_reg_mprs_ctipl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mprs_ctipl_l2_length_get(const char *buf);

void mlxsw_reg_mprs_ctipl_l2_length_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mprs_vxlan_udp_dport_get(const char *buf);

void mlxsw_reg_mprs_vxlan_udp_dport_set(char *buf, uint16_t val);

/* mpat
 * ----
 *
 */
#define MLXSW_MPAT_ID 0x901a
#define MLXSW_MPAT_LEN 0x84

uint8_t mlxsw_reg_mpat_pa_id_get(const char *buf);

void mlxsw_reg_mpat_pa_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_session_id_get(const char *buf);

void mlxsw_reg_mpat_session_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mngr_type_get(const char *buf);

void mlxsw_reg_mpat_mngr_type_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_system_port_get(const char *buf);

void mlxsw_reg_mpat_system_port_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpat_e_get(const char *buf);

void mlxsw_reg_mpat_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_c_get(const char *buf);

void mlxsw_reg_mpat_c_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_qos_get(const char *buf);

void mlxsw_reg_mpat_qos_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_be_get(const char *buf);

void mlxsw_reg_mpat_be_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_tr_get(const char *buf);

void mlxsw_reg_mpat_tr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_nmp_get(const char *buf);

void mlxsw_reg_mpat_nmp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_imp_get(const char *buf);

void mlxsw_reg_mpat_imp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_stclass_get(const char *buf);

void mlxsw_reg_mpat_stclass_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_span_type_get(const char *buf);

void mlxsw_reg_mpat_span_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_itc_get(const char *buf);

void mlxsw_reg_mpat_itc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_tclass_get(const char *buf);

void mlxsw_reg_mpat_tclass_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_switch_prio_get(const char *buf);

void mlxsw_reg_mpat_switch_prio_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_truncation_size_get(const char *buf);

void mlxsw_reg_mpat_truncation_size_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpat_pide_get(const char *buf);

void mlxsw_reg_mpat_pide_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_pid_get(const char *buf);

void mlxsw_reg_mpat_pid_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpat_local_span_tclass_get(const char *buf);

void mlxsw_reg_mpat_local_span_tclass_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethvlan_pcp_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethvlan_pcp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethvlan_dei_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethvlan_dei_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_mpat_encap_rmtethvlan_vid_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethvlan_vid_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethvlan_vlan_et_id_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethvlan_vlan_et_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethvlan_tclass_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethvlan_tclass_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl2_swid_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl2_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl2_version_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl2_version_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl2_dpa_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl2_dpa_set(char *buf, uint8_t val);

void mlxsw_reg_mpat_mpat_encap_rmtethl2_mac_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_mpat_mpat_encap_rmtethl2_mac_memcpy_to(char *buf, const char *src);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl2_tp_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl2_tp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl2_pcp_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl2_pcp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl2_dei_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl2_dei_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_mpat_encap_rmtethl2_vid_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl2_vid_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl2_fid_msb_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl2_fid_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl2_vlan_et_id_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl2_vlan_et_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl2_tclass_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl2_tclass_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_swid_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_version_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_version_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_dpa_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_dpa_set(char *buf, uint8_t val);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_mac_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_mac_memcpy_to(char *buf, const char *src);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_protocol_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_protocol_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_dscp_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_dscp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_tp_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_tp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_pcp_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_pcp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_dei_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_dei_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_vid_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_vid_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_fid_msb_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_fid_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_vlan_et_id_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_vlan_et_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_ecn_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_ecn_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_ttl_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_ttl_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_tclass_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_tclass_set(char *buf, uint8_t val);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_smac_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_smac_memcpy_to(char *buf, const char *src);

uint32_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_dip_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_dip_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_mpat_mpat_encap_rmtethl3gre_sip_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mpat_mpat_encap_rmtethl3gre_sip_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_localib_vl_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_localib_vl_set(char *buf, uint8_t val);

void mlxsw_reg_mpat_remote_span_ib_local_ud_we_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_remote_span_ib_local_ud_sl_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_sl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_remote_span_ib_local_ud_dpa_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_dpa_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_remote_span_ib_local_ud_dlid_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_dlid_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpat_remote_span_ib_local_ud_swid_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_remote_span_ib_local_ud_version_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_version_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_remote_span_ib_local_ud_slid_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_slid_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpat_remote_span_ib_local_ud_vl_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_vl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_remote_span_ib_local_ud_se_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_se_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_remote_span_ib_local_ud_m_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_m_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_remote_span_ib_local_ud_pkey_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_pkey_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_mpat_remote_span_ib_local_ud_dest_qp_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_dest_qp_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_mpat_remote_span_ib_local_ud_ar_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_ar_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mpat_remote_span_ib_local_ud_psn_init_val_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_psn_init_val_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mpat_remote_span_ib_local_ud_qkey_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_qkey_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mpat_remote_span_ib_local_ud_src_qp_get(const char *buf);

void mlxsw_reg_mpat_remote_span_ib_local_ud_src_qp_set(char *buf, uint32_t val);

void mlxsw_reg_mpat_mpat_encap_remoteib_we_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_remoteib_sl_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_sl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_remoteib_dpa_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_dpa_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_mpat_encap_remoteib_dlid_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_dlid_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_remoteib_swid_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_remoteib_version_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_version_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_mpat_encap_remoteib_slid_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_slid_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_remoteib_vl_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_vl_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_mpat_encap_remoteib_tclass_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_tclass_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_mpat_mpat_encap_remoteib_flow_label_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_flow_label_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_remoteib_hop_limit_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_hop_limit_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mpat_mpat_encap_remoteib_sgid_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mpat_mpat_encap_remoteib_sgid_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_mpat_mpat_encap_remoteib_dgid_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mpat_mpat_encap_remoteib_dgid_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_remoteib_se_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_se_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_remoteib_m_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_m_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_mpat_encap_remoteib_pkey_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_pkey_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_mpat_mpat_encap_remoteib_dest_qp_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_dest_qp_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_mpat_mpat_encap_remoteib_ar_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_ar_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mpat_mpat_encap_remoteib_psn_init_val_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_psn_init_val_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mpat_mpat_encap_remoteib_qkey_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_qkey_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mpat_mpat_encap_remoteib_src_qp_get(const char *buf);

void mlxsw_reg_mpat_mpat_encap_remoteib_src_qp_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mpat_buffer_drop_high_get(const char *buf);

uint32_t mlxsw_reg_mpat_buffer_drop_low_get(const char *buf);

uint32_t mlxsw_reg_mpat_be_drop_high_get(const char *buf);

uint32_t mlxsw_reg_mpat_be_drop_low_get(const char *buf);

uint8_t mlxsw_reg_mpat_pc_get(const char *buf);

void mlxsw_reg_mpat_pc_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpat_multi_port_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mpat_multi_port_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

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

/* mocmi
 * -----
 *
 */
#define MLXSW_MOCMI_ID 0x9098
#define MLXSW_MOCMI_LEN 0x10

uint8_t mlxsw_reg_mocmi_local_port_get(const char *buf);

void mlxsw_reg_mocmi_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocmi_lp_msb_get(const char *buf);

void mlxsw_reg_mocmi_lp_msb_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mocmi_cond_nelp_get(const char *buf);

void mlxsw_reg_mocmi_cond_nelp_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_mocmi_cond_elp_get(const char *buf);

void mlxsw_reg_mocmi_cond_elp_set(char *buf, uint16_t val);

/* mocs
 * ----
 *
 */
#define MLXSW_MOCS_ID 0x9095
#define MLXSW_MOCS_PORT_MASK_BASE_LEN 0x20 /* base length, without records */
#define MLXSW_MOCS_GRP_MASK_BASE_LEN 0x60 /* base length, without records */
#define MLXSW_MOCS_GRP_PRF_BASE_LEN 0x80 /* base length, without records */
#define MLXSW_MOCS_PORT_MASK_BASE_LEN 0x20 /* base length, without records */
#define MLXSW_MOCS_PORT_MASK_BASE_LEN 0x20 /* base length, without records */
#define MLXSW_MOCS_PORT_MASK_BASE_LEN 0x20 /* base length, without records */
#define MLXSW_MOCS_PORT_MASK_BASE_LEN 0x20 /* base length, without records */
#define MLXSW_MOCS_PORT_MASK_BASE_LEN 0x20 /* base length, without records */
#define MLXSW_MOCS_FLOW_ESTIMATOR_RECORD_BASE_LEN 0x20 /* base length, without records */
#define MLXSW_MOCS_FLOW_ESTIMATOR_RECORD_REC_LEN 0x08 /* record length */
#define MLXSW_MOCS_FLOW_ESTIMATOR_RECORD_REC_MAX_COUNT 12
#define MLXSW_MOCS_LEN 0xc0

uint8_t mlxsw_reg_mocs_type_get(const char *buf);

void mlxsw_reg_mocs_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_clear_get(const char *buf);

void mlxsw_reg_mocs_clear_set(char *buf, uint8_t val);

void mlxsw_reg_mocs_opcode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_status_get(const char *buf);

uint64_t mlxsw_reg_mocs_event_tid_get(const char *buf);

void mlxsw_reg_mocs_event_tid_set(char *buf, uint64_t val);

uint32_t mlxsw_reg_mocs_mocs_ppcnt_port_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mocs_mocs_ppcnt_port_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_mocs_mocs_ppcnt_grp_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mocs_mocs_ppcnt_grp_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_mocs_mocs_ppcnt_tc_mask_get(const char *buf);

void mlxsw_reg_mocs_mocs_ppcnt_tc_mask_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_mocs_mocs_ppcnt_prio_mask_get(const char *buf);

void mlxsw_reg_mocs_mocs_ppcnt_prio_mask_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_mocs_mocs_ppcnt_rx_buffer_mask_get(const char *buf);

void mlxsw_reg_mocs_mocs_ppcnt_rx_buffer_mask_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_mocs_mocs_ppcnt_grp_prf_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mocs_mocs_ppcnt_grp_prf_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_mocs_mocs_mgpcb_flush_get(const char *buf);

void mlxsw_reg_mocs_mocs_mgpcb_flush_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mocs_mocs_mgpcb_num_rec_get(const char *buf);

void mlxsw_reg_mocs_mocs_mgpcb_num_rec_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mocs_mocs_mgpcb_counter_index_base_get(const char *buf);

void mlxsw_reg_mocs_mocs_mgpcb_counter_index_base_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mocs_mocs_pbsr_port_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mocs_mocs_pbsr_port_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_mocs_curr_get(const char *buf);

void mlxsw_reg_mocs_curr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_snap_get(const char *buf);

void mlxsw_reg_mocs_snap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_cells_get(const char *buf);

void mlxsw_reg_mocs_cells_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_desc_get(const char *buf);

void mlxsw_reg_mocs_desc_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mocs_mocs_ceer_port_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mocs_mocs_ceer_port_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_mocs_mocs_mafbi_flush_get(const char *buf);

void mlxsw_reg_mocs_mocs_mafbi_flush_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_mocs_mafbi_type_get(const char *buf);

void mlxsw_reg_mocs_mocs_mafbi_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mocs_mocs_mafbi_num_rec_get(const char *buf);

void mlxsw_reg_mocs_mocs_mafbi_num_rec_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mocs_mocs_mafbi_counter_index_base_get(const char *buf);

void mlxsw_reg_mocs_mocs_mafbi_counter_index_base_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_mocs_mocs_fsed_op_get(const char *buf);

void mlxsw_reg_mocs_mocs_fsed_op_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_mocs_fsed_filter_fields_get(const char *buf);

void mlxsw_reg_mocs_mocs_fsed_filter_fields_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mocs_mocs_fsed_group_id_get(const char *buf);

void mlxsw_reg_mocs_mocs_fsed_group_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mocs_mocs_fsed_entry_sem_s_get(const char *buf);

void mlxsw_reg_mocs_mocs_fsed_entry_sem_s_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_mocs_fsed_entry_activity_get(const char *buf);

void mlxsw_reg_mocs_mocs_fsed_entry_activity_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_mocs_fsed_entry_partition_id_get(const char *buf);

void mlxsw_reg_mocs_mocs_fsed_entry_partition_id_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mocs_mocs_fsed_num_rec_get(const char *buf);

void mlxsw_reg_mocs_mocs_fsed_num_rec_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_mocs_mocs_fsed_nt_get(const char *buf);

void mlxsw_reg_mocs_mocs_fsed_nt_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mocs_mocs_usacn_port_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mocs_mocs_usacn_port_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_mocs_mocs_usacn_side_get(const char *buf);

void mlxsw_reg_mocs_mocs_usacn_side_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mocs_mocs_usacn_sadb_entry_index_base_get(const char *buf);

void mlxsw_reg_mocs_mocs_usacn_sadb_entry_index_base_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_mocs_mocs_usacn_num_rec_get(const char *buf);

void mlxsw_reg_mocs_mocs_usacn_num_rec_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_mocs_mocs_utcc_port_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mocs_mocs_utcc_port_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_mocs_mocs_utcc_side_get(const char *buf);

void mlxsw_reg_mocs_mocs_utcc_side_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_mocs_utcc_utcam_counter_idx_base_get(const char *buf);

void mlxsw_reg_mocs_mocs_utcc_utcam_counter_idx_base_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocs_mocs_utcc_num_rec_get(const char *buf);

void mlxsw_reg_mocs_mocs_utcc_num_rec_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mocs_mocs_upcnt_port_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mocs_mocs_upcnt_port_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint64_t mlxsw_reg_mocs_mocs_upcnt_grp_mask_get(const char *buf);

void mlxsw_reg_mocs_mocs_upcnt_grp_mask_set(char *buf, uint64_t val);

uint16_t mlxsw_reg_mocs_flow_estimator_record_num_rec_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mocs_flow_estimator_record_num_rec_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint32_t mlxsw_reg_mocs_flow_estimator_record_counter_index_base_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mocs_flow_estimator_record_counter_index_base_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* mafcr
 * -----
 *
 */
#define MLXSW_MAFCR_ID 0x908a
#define MLXSW_MAFCR_LEN 0xc

uint8_t mlxsw_reg_mafcr_clear_get(const char *buf);

void mlxsw_reg_mafcr_clear_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mafcr_counter_accu_overflow_get(const char *buf);

uint16_t mlxsw_reg_mafcr_packets_inc_units_get(const char *buf);

uint16_t mlxsw_reg_mafcr_bytes_inc_units_get(const char *buf);

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

uint32_t mlxsw_reg_mafti_counter_index_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_mafti_bytes_inc_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_mafti_packets_inc_get(const char *buf, unsigned short outer_index, unsigned short index);

/* mafbi
 * -----
 *
 */
#define MLXSW_MAFBI_ID 0x9097
#define MLXSW_MAFBI_RECORD_BASE_LEN 0x08 /* base length, without records */
#define MLXSW_MAFBI_RECORD_REC_LEN 0x0c /* record length */
#define MLXSW_MAFBI_RECORD_REC_MAX_COUNT 64
#define MLXSW_MAFBI_LEN 0x308

uint8_t mlxsw_reg_mafbi_type_get(const char *buf);

uint8_t mlxsw_reg_mafbi_num_rec_get(const char *buf);

uint32_t mlxsw_reg_mafbi_counter_index_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_mafbi_bytes_inc_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_mafbi_packets_inc_get(const char *buf, unsigned short outer_index, unsigned short index);

/* mafri
 * -----
 *
 */
#define MLXSW_MAFRI_ID 0x908c
#define MLXSW_MAFRI_RECORD_BASE_LEN 0x10 /* base length, without records */
#define MLXSW_MAFRI_RECORD_REC_LEN 0x08 /* record length */
#define MLXSW_MAFRI_RECORD_REC_MAX_COUNT 128
#define MLXSW_MAFRI_LEN 0x410

uint8_t mlxsw_reg_mafri_fsf_get(const char *buf);

void mlxsw_reg_mafri_fsf_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mafri_event_get(const char *buf);

void mlxsw_reg_mafri_event_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mafri_num_rec_get(const char *buf);

void mlxsw_reg_mafri_num_rec_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mafri_counter_index_base_get(const char *buf);

void mlxsw_reg_mafri_counter_index_base_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mafri_user_val_get(const char *buf);

void mlxsw_reg_mafri_user_val_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mafri_bytes_inc_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_mafri_packets_inc_get(const char *buf, unsigned short outer_index, unsigned short index);

/* mopce
 * -----
 *
 */
#define MLXSW_MOPCE_ID 0x90e2
#define MLXSW_MOPCE_PERFORMANCE_COUNTER_INFO_BASE_LEN 0x10 /* base length, without records */
#define MLXSW_MOPCE_PERFORMANCE_COUNTER_INFO_REC_LEN 0x10 /* record length */
#define MLXSW_MOPCE_PERFORMANCE_COUNTER_INFO_REC_MAX_COUNT 76
#define MLXSW_MOPCE_LEN 0x4d0

uint8_t mlxsw_reg_mopce_num_rec_get(const char *buf);

void mlxsw_reg_mopce_num_rec_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mopce_hw_unit_instance_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_mopce_hw_unit_id_get(const char *buf, unsigned short outer_index, unsigned short index);

uint16_t mlxsw_reg_mopce_counter_index_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_mopce_hw_unit_sub_instance_get(const char *buf, unsigned short outer_index, unsigned short index);

uint64_t mlxsw_reg_mopce_counter_value_get(const char *buf, unsigned short outer_index, unsigned short index);

/* moca
 * ----
 *
 */
#define MLXSW_MOCA_ID 0x90e3
#define MLXSW_MOCA_LEN 0xc

uint8_t mlxsw_reg_moca_counter_type_get(const char *buf);

void mlxsw_reg_moca_counter_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_moca_counter_index_get(const char *buf);

void mlxsw_reg_moca_counter_index_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_moca_size_get(const char *buf);

void mlxsw_reg_moca_size_set(char *buf, uint32_t val);

/* mofrb
 * -----
 *
 */
#define MLXSW_MOFRB_ID 0x90e6
#define MLXSW_MOFRB_LEN 0x210

uint8_t mlxsw_reg_mofrb_clear_get(const char *buf);

void mlxsw_reg_mofrb_clear_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mofrb_num_rec_get(const char *buf);

void mlxsw_reg_mofrb_num_rec_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_mofrb_counter_index_base_get(const char *buf);

void mlxsw_reg_mofrb_counter_index_base_set(char *buf, uint32_t val);

void mlxsw_reg_mofrb_flow_estimator_bin_memcpy_from(const char *buf, char *dst);

/* mofph
 * -----
 *
 */
#define MLXSW_MOFPH_ID 0x90e4
#define MLXSW_MOFPH_LEN 0x20

uint8_t mlxsw_reg_mofph_profile_get(const char *buf);

void mlxsw_reg_mofph_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mofph_type_get(const char *buf);

void mlxsw_reg_mofph_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mofph_seed_en_get(const char *buf);

void mlxsw_reg_mofph_seed_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mofph_seed_by_sw_get(const char *buf);

void mlxsw_reg_mofph_seed_by_sw_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mofph_outer_header_enables_get(const char *buf);

void mlxsw_reg_mofph_outer_header_enables_set(char *buf, uint16_t val);

uint64_t mlxsw_reg_mofph_outer_header_hash_get(const char *buf);

void mlxsw_reg_mofph_outer_header_hash_set(char *buf, uint64_t val);

uint16_t mlxsw_reg_mofph_inner_header_enables_get(const char *buf);

void mlxsw_reg_mofph_inner_header_enables_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_mofph_inner_header_hash_get(const char *buf);

void mlxsw_reg_mofph_inner_header_hash_set(char *buf, uint32_t val);

/* mofpc
 * -----
 *
 */
#define MLXSW_MOFPC_ID 0x90e5
#define MLXSW_MOFPC_LEN 0xc

uint8_t mlxsw_reg_mofpc_profile_get(const char *buf);

void mlxsw_reg_mofpc_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mofpc_log_num_of_bins_get(const char *buf);

void mlxsw_reg_mofpc_log_num_of_bins_set(char *buf, uint8_t val);

/* mocbr
 * -----
 *
 */
#define MLXSW_MOCBR_ID 0x90e7
#define MLXSW_MOCBR_LEN 0xc

uint8_t mlxsw_reg_mocbr_e_get(const char *buf);

void mlxsw_reg_mocbr_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocbr_l_get(const char *buf);

void mlxsw_reg_mocbr_l_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mocbr_base_counter_index_get(const char *buf);

void mlxsw_reg_mocbr_base_counter_index_set(char *buf, uint32_t val);

/* mocbs
 * -----
 *
 */
#define MLXSW_MOCBS_ID 0x90e8
#define MLXSW_MOCBS_LEN 0xc

uint8_t mlxsw_reg_mocbs_op_get(const char *buf);

void mlxsw_reg_mocbs_op_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mocbs_cnt_err_get(const char *buf);

/* mtpspu
 * ------
 *
 */
#define MLXSW_MTPSPU_ID 0x9094
#define MLXSW_MTPSPU_LEN 0x8

uint16_t mlxsw_reg_mtpspu_message_type_get(const char *buf);

void mlxsw_reg_mtpspu_message_type_set(char *buf, uint16_t val);

/* mtpcpc
 * ------
 *
 */
#define MLXSW_MTPCPC_ID 0x9093
#define MLXSW_MTPCPC_LEN 0x28

uint8_t mlxsw_reg_mtpcpc_pport_get(const char *buf);

void mlxsw_reg_mtpcpc_pport_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtpcpc_local_port_get(const char *buf);

void mlxsw_reg_mtpcpc_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtpcpc_lp_msb_get(const char *buf);

void mlxsw_reg_mtpcpc_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mtpcpc_ptp_trap_en_get(const char *buf);

void mlxsw_reg_mtpcpc_ptp_trap_en_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mtpcpc_ing_correction_message_type_get(const char *buf);

void mlxsw_reg_mtpcpc_ing_correction_message_type_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_mtpcpc_egr_correction_message_type_get(const char *buf);

void mlxsw_reg_mtpcpc_egr_correction_message_type_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mtpcpc_num_domains_get(const char *buf);

void mlxsw_reg_mtpcpc_num_domains_set(char *buf, uint8_t val);

void mlxsw_reg_mtpcpc_domain_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_mtpcpc_domain_memcpy_to(char *buf, const char *src);

/* mfgd
 * ----
 *
 */
#define MLXSW_MFGD_ID 0x90f0
#define MLXSW_MFGD_LEN 0x8

uint8_t mlxsw_reg_mfgd_long_cmd_timeout_value_get(const char *buf);

void mlxsw_reg_mfgd_long_cmd_timeout_value_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfgd_en_debug_assert_get(const char *buf);

void mlxsw_reg_mfgd_en_debug_assert_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfgd_fw_fatal_event_test_get(const char *buf);

void mlxsw_reg_mfgd_fw_fatal_event_test_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfgd_fw_fatal_event_mode_get(const char *buf);

void mlxsw_reg_mfgd_fw_fatal_event_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfgd_packet_state_test_time_value_get(const char *buf);

void mlxsw_reg_mfgd_packet_state_test_time_value_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfgd_packet_state_test_action_get(const char *buf);

void mlxsw_reg_mfgd_packet_state_test_action_set(char *buf, uint8_t val);

/* modcr
 * -----
 *
 */
#define MLXSW_MODCR_ID 0x9099
#define MLXSW_MODCR_LEN 0x14

uint8_t mlxsw_reg_modcr_clear_get(const char *buf);

void mlxsw_reg_modcr_clear_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_modcr_fatal_asserts_get(const char *buf);

uint32_t mlxsw_reg_modcr_normal_asserts_get(const char *buf);

uint32_t mlxsw_reg_modcr_debug_asserts_get(const char *buf);

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

/* mfde
 * ----
 *
 */
#define MLXSW_MFDE_ID 0x9200
#define MLXSW_MFDE_LEN 0xb0

uint8_t mlxsw_reg_mfde_irisc_id_get(const char *buf);

uint8_t mlxsw_reg_mfde_severity_get(const char *buf);

uint16_t mlxsw_reg_mfde_event_id_get(const char *buf);

uint8_t mlxsw_reg_mfde_notify_fw_dump_completion_get(const char *buf);

uint8_t mlxsw_reg_mfde_method_get(const char *buf);

uint8_t mlxsw_reg_mfde_packet_state_get(const char *buf);

uint8_t mlxsw_reg_mfde_command_type_get(const char *buf);

uint8_t mlxsw_reg_mfde_mgmt_class_get(const char *buf);

uint16_t mlxsw_reg_mfde_reg_attr_id_get(const char *buf);

uint8_t mlxsw_reg_mfde_packet_state_sticky_get(const char *buf);

uint8_t mlxsw_reg_mfde_packet_cmd_type_get(const char *buf);

uint8_t mlxsw_reg_mfde_packet_interface_get(const char *buf);

uint32_t mlxsw_reg_mfde_crspace_timeout_log_address_get(const char *buf);

uint8_t mlxsw_reg_mfde_crspace_timeout_is_main_farm_get(const char *buf);

void mlxsw_reg_mfde_crspace_timeout_is_main_farm_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfde_crspace_timeout_is_iron_get(const char *buf);

void mlxsw_reg_mfde_crspace_timeout_is_iron_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfde_crspace_timeout_is_yu_get(const char *buf);

void mlxsw_reg_mfde_crspace_timeout_is_yu_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mfde_crspace_timeout_oe_get(const char *buf);

uint8_t mlxsw_reg_mfde_crspace_timeout_log_id_get(const char *buf);

uint64_t mlxsw_reg_mfde_crspace_timeout_log_ip_get(const char *buf);

uint8_t mlxsw_reg_mfde_kvd_im_stop_oe_get(const char *buf);

uint16_t mlxsw_reg_mfde_kvd_im_stop_pipes_mask_get(const char *buf);

uint32_t mlxsw_reg_mfde_fw_assert_assert_var0_get(const char *buf);

uint32_t mlxsw_reg_mfde_fw_assert_assert_var1_get(const char *buf);

uint32_t mlxsw_reg_mfde_fw_assert_assert_var2_get(const char *buf);

uint32_t mlxsw_reg_mfde_fw_assert_assert_var3_get(const char *buf);

uint32_t mlxsw_reg_mfde_fw_assert_assert_var4_get(const char *buf);

uint32_t mlxsw_reg_mfde_fw_assert_assert_existptr_get(const char *buf);

uint32_t mlxsw_reg_mfde_fw_assert_assert_callra_get(const char *buf);

uint8_t mlxsw_reg_mfde_fw_assert_test_get(const char *buf);

uint8_t mlxsw_reg_mfde_fw_assert_oe_get(const char *buf);

uint8_t mlxsw_reg_mfde_fw_assert_tile_v_get(const char *buf);

uint8_t mlxsw_reg_mfde_fw_assert_tile_index_get(const char *buf);

uint16_t mlxsw_reg_mfde_fw_assert_ext_synd_get(const char *buf);

uint32_t mlxsw_reg_mfde_fw_assert_assert_string_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_mfde_test_get(const char *buf);

uint8_t mlxsw_reg_mfde_fw_cause_get(const char *buf);

void mlxsw_reg_mfde_fw_cause_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mfde_cause_id_get(const char *buf);

uint8_t mlxsw_reg_mfde_tile_v_get(const char *buf);

uint8_t mlxsw_reg_mfde_tile_index_get(const char *buf);

/* mdif
 * ----
 *
 */
#define MLXSW_MDIF_ID 0x909a
#define MLXSW_MDIF_LEN 0x10

uint8_t mlxsw_reg_mdif_global_get(const char *buf);

void mlxsw_reg_mdif_global_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mdif_lp_msb_get(const char *buf);

void mlxsw_reg_mdif_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mdif_local_port_get(const char *buf);

void mlxsw_reg_mdif_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mdif_field_select_get(const char *buf);

void mlxsw_reg_mdif_field_select_set(char *buf, uint8_t val);

void mlxsw_reg_mdif_crc_err_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mdif_crc_lanes_mode_get(const char *buf);

void mlxsw_reg_mdif_crc_lanes_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mdif_inject_sram_ecc_get(const char *buf);

void mlxsw_reg_mdif_inject_sram_ecc_set(char *buf, uint8_t val);

/* mofrd
 * -----
 *
 */
#define MLXSW_MOFRD_ID 0x9150
#define MLXSW_MOFRD_LEN 0x54

uint8_t mlxsw_reg_mofrd_trigger_get(const char *buf);

void mlxsw_reg_mofrd_trigger_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mofrd_err_ptr_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mofrd_err_ptr_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint32_t mlxsw_reg_mofrd_num_errors_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_mofrd_num_errors_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

uint8_t mlxsw_reg_igcr_ddd_lag_mode_get(const char *buf);

void mlxsw_reg_igcr_ddd_lag_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_igcr_pisbo_get(const char *buf);

void mlxsw_reg_igcr_pisbo_set(char *buf, uint8_t val);

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

uint8_t mlxsw_reg_iedr_type_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_iedr_type_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint16_t mlxsw_reg_iedr_size_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_iedr_size_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint32_t mlxsw_reg_iedr_index_start_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_iedr_index_start_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* ieds
 * ----
 *
 */
#define MLXSW_IEDS_ID 0x3805
#define MLXSW_IEDS_LEN 0x8

uint8_t mlxsw_reg_ieds_edpr_get(const char *buf);

void mlxsw_reg_ieds_edpr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ieds_ed_status_get(const char *buf);

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

uint32_t mlxsw_reg_ifbo_outer_header_fields_enable_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ifbo_outer_header_fields_enable_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

/* ipac
 * ----
 *
 */
#define MLXSW_IPAC_ID 0x3812
#define MLXSW_IPAC_LEN 0xb0

uint8_t mlxsw_reg_ipac_profile_index_get(const char *buf);

void mlxsw_reg_ipac_profile_index_set(char *buf, uint8_t val);

void mlxsw_reg_ipac_opcode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ipac_status_get(const char *buf);

uint32_t mlxsw_reg_ipac_port_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ipac_port_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint16_t mlxsw_reg_ipac_log_op_time_get(const char *buf);

uint32_t mlxsw_reg_ipac_log_op_registers_get(const char *buf);

uint8_t mlxsw_reg_ipac_error_lp_msb_get(const char *buf);

uint8_t mlxsw_reg_ipac_error_local_port_get(const char *buf);

uint16_t mlxsw_reg_ipac_error_register_id_get(const char *buf);

uint8_t mlxsw_reg_ipac_error_status_get(const char *buf);

void mlxsw_reg_ipac_error_status_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ipac_error_entry_index_get(const char *buf);

/* ihsr
 * ----
 *
 */
#define MLXSW_IHSR_ID 0x3813
#define MLXSW_IHSR_LEN 0x50

uint8_t mlxsw_reg_ihsr_hash_profile_get(const char *buf);

void mlxsw_reg_ihsr_hash_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ihsr_gsh_get(const char *buf);

void mlxsw_reg_ihsr_gsh_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ihsr_type_get(const char *buf);

void mlxsw_reg_ihsr_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_ihsr_general_fields_get(const char *buf);

void mlxsw_reg_ihsr_general_fields_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_ihsr_outer_header_enables_get(const char *buf);

void mlxsw_reg_ihsr_outer_header_enables_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_ihsr_outer_header_fields_enable_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ihsr_outer_header_fields_enable_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint16_t mlxsw_reg_ihsr_inner_header_enables_get(const char *buf);

void mlxsw_reg_ihsr_inner_header_enables_set(char *buf, uint16_t val);

uint64_t mlxsw_reg_ihsr_inner_header_fields_enable_get(const char *buf);

void mlxsw_reg_ihsr_inner_header_fields_enable_set(char *buf, uint64_t val);

uint32_t mlxsw_reg_ihsr_cbsets_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ihsr_cbsets_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* ihscr
 * -----
 *
 */
#define MLXSW_IHSCR_ID 0x3814
#define MLXSW_IHSCR_LEN 0xa8

uint8_t mlxsw_reg_ihscr_profile_index_get(const char *buf);

void mlxsw_reg_ihscr_profile_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ihscr_l2_type_get(const char *buf);

void mlxsw_reg_ihscr_l2_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ihscr_inner_l2_type_get(const char *buf);

void mlxsw_reg_ihscr_inner_l2_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ihscr_l3_type_get(const char *buf);

void mlxsw_reg_ihscr_l3_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ihscr_inner_l3_type_get(const char *buf);

void mlxsw_reg_ihscr_inner_l3_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ihscr_ip_frag_get(const char *buf);

void mlxsw_reg_ihscr_ip_frag_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ihscr_inner_ip_frag_get(const char *buf);

void mlxsw_reg_ihscr_inner_ip_frag_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ihscr_l4_type_get(const char *buf);

void mlxsw_reg_ihscr_l4_type_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ihscr_inner_l4_type_get(const char *buf);

void mlxsw_reg_ihscr_inner_l4_type_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ihscr_tunnel_type_get(const char *buf);

void mlxsw_reg_ihscr_tunnel_type_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_ihscr_mask_inner_get(const char *buf);

void mlxsw_reg_ihscr_mask_inner_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ihscr_mask_outer_get(const char *buf);

void mlxsw_reg_ihscr_mask_outer_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ihscr_fpp_index_get(const char *buf);

void mlxsw_reg_ihscr_fpp_index_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ihscr_inner_fpp_index_get(const char *buf);

void mlxsw_reg_ihscr_inner_fpp_index_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_ihscr_ports_bitmap_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ihscr_ports_bitmap_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* ipsr
 * ----
 *
 */
#define MLXSW_IPSR_ID 0x3815
#define MLXSW_IPSR_LEN 0x14

uint8_t mlxsw_reg_ipsr_profile_index_get(const char *buf);

void mlxsw_reg_ipsr_profile_index_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ipsr_cap_size_get(const char *buf);

uint16_t mlxsw_reg_ipsr_current_size_get(const char *buf);

uint16_t mlxsw_reg_ipsr_current_entries_get(const char *buf);

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

uint32_t mlxsw_reg_icsr_data_get(const char *buf, unsigned short outer_index, unsigned short index);

/* ipfr
 * ----
 *
 */
#define MLXSW_IPFR_ID 0x3824
#define MLXSW_IPFR_LEN 0x8

uint16_t mlxsw_reg_ipfr_pgt_base_ptr_get(const char *buf);

void mlxsw_reg_ipfr_pgt_base_ptr_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ipfr_size_get(const char *buf);

void mlxsw_reg_ipfr_size_set(char *buf, uint16_t val);

/* itgcr
 * -----
 *
 */
#define MLXSW_ITGCR_ID 0x3821
#define MLXSW_ITGCR_LEN 0x8

uint8_t mlxsw_reg_itgcr_l4_validity_get(const char *buf);

void mlxsw_reg_itgcr_l4_validity_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_itgcr_def_masking_size_get(const char *buf);

void mlxsw_reg_itgcr_def_masking_size_set(char *buf, uint16_t val);

/* itpr
 * ----
 *
 */
#define MLXSW_ITPR_ID 0x3820
#define MLXSW_ITPR_LEN 0x14

uint8_t mlxsw_reg_itpr_trunc_prof_get(const char *buf);

void mlxsw_reg_itpr_trunc_prof_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_itpr_tr_size_get(const char *buf);

void mlxsw_reg_itpr_tr_size_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_itpr_dd_get(const char *buf);

void mlxsw_reg_itpr_dd_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_itpr_mode_get(const char *buf);

void mlxsw_reg_itpr_mode_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_itpr_masking_label_en_get(const char *buf);

void mlxsw_reg_itpr_masking_label_en_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_itpr_addition_masking_offset_get(const char *buf);

void mlxsw_reg_itpr_addition_masking_offset_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_itpr_addition_masking_offset_en_get(const char *buf);

void mlxsw_reg_itpr_addition_masking_offset_en_set(char *buf, uint16_t val);

/* sgcr
 * ----
 *
 */
#define MLXSW_SGCR_ID 0x2000
#define MLXSW_SGCR_LEN 0x10

uint8_t mlxsw_reg_sgcr_llb_get(const char *buf);

void mlxsw_reg_sgcr_llb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sgcr_activity_dis_get(const char *buf);

void mlxsw_reg_sgcr_activity_dis_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sgcr_lag_lookup_pgt_base_get(const char *buf);

void mlxsw_reg_sgcr_lag_lookup_pgt_base_set(char *buf, uint16_t val);

/* spad
 * ----
 *
 */
#define MLXSW_SPAD_ID 0x2002
#define MLXSW_SPAD_LEN 0x10

void mlxsw_reg_spad_base_mac_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_spad_base_mac_memcpy_to(char *buf, const char *src);

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

/* sfdb_v2
 * -------
 *
 */
#define MLXSW_SFDB_V2_ID 0x202d
#define MLXSW_SFDB_V2_LEN 0x84

uint32_t mlxsw_reg_sfdb_v2_key_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_sfdb_v2_key_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_sfdb_v2_key_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_sfdb_v2_key_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

void mlxsw_reg_sfdb_v2_action_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

void mlxsw_reg_sfdb_v2_action_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_sfdb_v2_count_updates_get(const char *buf);

/* smid_v2
 * -------
 *
 */
#define MLXSW_SMID_V2_ID 0x2034
#define MLXSW_SMID_V2_LEN 0x120

uint8_t mlxsw_reg_smid_v2_swid_get(const char *buf);

void mlxsw_reg_smid_v2_swid_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_smid_v2_mid_get(const char *buf);

void mlxsw_reg_smid_v2_mid_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_smid_v2_op_get(const char *buf);

void mlxsw_reg_smid_v2_op_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_smid_v2_smpe_valid_get(const char *buf);

void mlxsw_reg_smid_v2_smpe_valid_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_smid_v2_smpe_get(const char *buf);

void mlxsw_reg_smid_v2_smpe_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_smid_v2_port_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_smid_v2_port_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

void mlxsw_reg_smid_v2_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

uint16_t mlxsw_reg_smpu_mid_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_smpu_mid_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

/* spms_v2
 * -------
 *
 */
#define MLXSW_SPMS_V2_ID 0x2032
#define MLXSW_SPMS_V2_VID_RECORD_BASE_LEN 0x04 /* base length, without records */
#define MLXSW_SPMS_V2_VID_RECORD_REC_LEN 0x04 /* record length */
#define MLXSW_SPMS_V2_VID_RECORD_REC_MAX_COUNT 255
#define MLXSW_SPMS_V2_LEN 0x400

uint8_t mlxsw_reg_spms_v2_allv_get(const char *buf);

void mlxsw_reg_spms_v2_allv_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_spms_v2_local_port_get(const char *buf);

void mlxsw_reg_spms_v2_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_spms_v2_lp_msb_get(const char *buf);

void mlxsw_reg_spms_v2_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_spms_v2_num_rec_get(const char *buf);

void mlxsw_reg_spms_v2_num_rec_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_spms_v2_state_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_spms_v2_state_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint16_t mlxsw_reg_spms_v2_vid_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_spms_v2_vid_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

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

/* spaft
 * -----
 *
 */
#define MLXSW_SPAFT_ID 0x2010
#define MLXSW_SPAFT_LEN 0x8

uint8_t mlxsw_reg_spaft_local_port_get(const char *buf);

void mlxsw_reg_spaft_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_spaft_lp_msb_get(const char *buf);

void mlxsw_reg_spaft_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_spaft_allow_untagged_get(const char *buf);

void mlxsw_reg_spaft_allow_untagged_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_spaft_allow_priotagged_get(const char *buf);

void mlxsw_reg_spaft_allow_priotagged_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_spaft_allow_tagged_get(const char *buf);

void mlxsw_reg_spaft_allow_tagged_set(char *buf, uint8_t val);

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

/* sftr_v2
 * -------
 *
 */
#define MLXSW_SFTR_V2_ID 0x202f
#define MLXSW_SFTR_V2_LEN 0x120

uint8_t mlxsw_reg_sftr_v2_swid_get(const char *buf);

void mlxsw_reg_sftr_v2_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sftr_v2_flood_table_get(const char *buf);

void mlxsw_reg_sftr_v2_flood_table_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sftr_v2_index_get(const char *buf);

void mlxsw_reg_sftr_v2_index_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_sftr_v2_table_type_get(const char *buf);

void mlxsw_reg_sftr_v2_table_type_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sftr_v2_range_get(const char *buf);

void mlxsw_reg_sftr_v2_range_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_sftr_v2_port_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_sftr_v2_port_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

void mlxsw_reg_sftr_v2_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

/* sfdf
 * ----
 *
 */
#define MLXSW_SFDF_ID 0x2013
#define MLXSW_SFDF_LEN 0x14

uint8_t mlxsw_reg_sfdf_swid_get(const char *buf);

void mlxsw_reg_sfdf_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfdf_flush_type_get(const char *buf);

void mlxsw_reg_sfdf_flush_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfdf_imdu_get(const char *buf);

void mlxsw_reg_sfdf_imdu_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfdf_iut_get(const char *buf);

void mlxsw_reg_sfdf_iut_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfdf_st_get(const char *buf);

void mlxsw_reg_sfdf_st_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfdf_pb_v_get(const char *buf);

void mlxsw_reg_sfdf_pb_v_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfdf_pb_get(const char *buf);

void mlxsw_reg_sfdf_pb_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sfdf_flush_per_fid_fid_get(const char *buf);

void mlxsw_reg_sfdf_flush_per_fid_fid_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_sfdf_flush_per_nve_and_fid_fid_get(const char *buf);

void mlxsw_reg_sfdf_flush_per_nve_and_fid_fid_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_sfdf_system_port_get(const char *buf);

void mlxsw_reg_sfdf_system_port_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_sfdf_flush_per_port_and_fid_system_port_get(const char *buf);

void mlxsw_reg_sfdf_flush_per_port_and_fid_system_port_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_sfdf_flush_per_port_and_fid_fid_get(const char *buf);

void mlxsw_reg_sfdf_flush_per_port_and_fid_fid_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_sfdf_lag_id_get(const char *buf);

void mlxsw_reg_sfdf_lag_id_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_sfdf_flush_per_lag_and_fid_lag_id_get(const char *buf);

void mlxsw_reg_sfdf_flush_per_lag_and_fid_lag_id_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_sfdf_flush_per_lag_and_fid_fid_get(const char *buf);

void mlxsw_reg_sfdf_flush_per_lag_and_fid_fid_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_sfdf_tport_mask_get(const char *buf);

void mlxsw_reg_sfdf_tport_mask_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfdf_tport_get(const char *buf);

void mlxsw_reg_sfdf_tport_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfdf_flush_per_tunnel_port_fid_tport_mask_get(const char *buf);

void mlxsw_reg_sfdf_flush_per_tunnel_port_fid_tport_mask_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfdf_flush_per_tunnel_port_fid_tport_get(const char *buf);

void mlxsw_reg_sfdf_flush_per_tunnel_port_fid_tport_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sfdf_flush_per_tunnel_port_fid_fid_get(const char *buf);

void mlxsw_reg_sfdf_flush_per_tunnel_port_fid_fid_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_sfdf_flush_mc_dmac_uc_and_fid_fid_get(const char *buf);

void mlxsw_reg_sfdf_flush_mc_dmac_uc_and_fid_fid_set(char *buf, uint16_t val);

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

uint8_t mlxsw_reg_sfmr_cff_counter_set_type_get(const char *buf);

void mlxsw_reg_sfmr_cff_counter_set_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_sfmr_cff_counter_base_index_get(const char *buf);

void mlxsw_reg_sfmr_cff_counter_base_index_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_sfmr_cff_mid_base_get(const char *buf);

void mlxsw_reg_sfmr_cff_mid_base_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_sfmr_tunnel_port_lbf_bitmap_get(const char *buf);

void mlxsw_reg_sfmr_tunnel_port_lbf_bitmap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfmr_nve_flood_prf_id_get(const char *buf);

void mlxsw_reg_sfmr_nve_flood_prf_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfmr_cff_prf_id_get(const char *buf);

void mlxsw_reg_sfmr_cff_prf_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sfmr_smpe_valid_get(const char *buf);

void mlxsw_reg_sfmr_smpe_valid_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sfmr_smpe_get(const char *buf);

void mlxsw_reg_sfmr_smpe_set(char *buf, uint16_t val);

/* spfsr
 * -----
 *
 */
#define MLXSW_SPFSR_ID 0x2023
#define MLXSW_SPFSR_LEN 0x8

uint8_t mlxsw_reg_spfsr_local_port_get(const char *buf);

void mlxsw_reg_spfsr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_spfsr_lp_msb_get(const char *buf);

void mlxsw_reg_spfsr_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_spfsr_security_get(const char *buf);

void mlxsw_reg_spfsr_security_set(char *buf, uint8_t val);

/* sffp
 * ----
 *
 */
#define MLXSW_SFFP_ID 0x2029
#define MLXSW_SFFP_LEN 0xc

uint8_t mlxsw_reg_sffp_profile_id_get(const char *buf);

void mlxsw_reg_sffp_profile_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sffp_type_get(const char *buf);

void mlxsw_reg_sffp_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sffp_flood_offset_get(const char *buf);

void mlxsw_reg_sffp_flood_offset_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sffp_counter_en_get(const char *buf);

void mlxsw_reg_sffp_counter_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sffp_counter_offset_get(const char *buf);

void mlxsw_reg_sffp_counter_offset_set(char *buf, uint8_t val);

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

uint8_t mlxsw_reg_smpeb_update_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_smpeb_update_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint32_t mlxsw_reg_smpeb_value_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_smpeb_value_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* slmt
 * ----
 *
 */
#define MLXSW_SLMT_ID 0x2037
#define MLXSW_SLMT_LEN 0x8

uint16_t mlxsw_reg_slmt_new_lag_lookup_pgt_base_get(const char *buf);

void mlxsw_reg_slmt_new_lag_lookup_pgt_base_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_slmt_lag_cnt_get(const char *buf);

void mlxsw_reg_slmt_lag_cnt_set(char *buf, uint16_t val);

/* sfdt_v2
 * -------
 *
 */
#define MLXSW_SFDT_V2_ID 0x202e
#define MLXSW_SFDT_V2_LEN 0x2e0

uint16_t mlxsw_reg_sfdt_v2_fgl_ptr_get(const char *buf);

void mlxsw_reg_sfdt_v2_fgl_ptr_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_sfdt_v2_size_get(const char *buf);

void mlxsw_reg_sfdt_v2_size_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sfdt_v2_port_member_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_sfdt_v2_port_member_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

/* sfdat
 * -----
 *
 */
#define MLXSW_SFDAT_ID 0x2009
#define MLXSW_SFDAT_LEN 0x8

uint8_t mlxsw_reg_sfdat_swid_get(const char *buf);

void mlxsw_reg_sfdat_swid_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_sfdat_age_time_get(const char *buf);

void mlxsw_reg_sfdat_age_time_set(char *buf, uint32_t val);

/* spzr
 * ----
 *
 */
#define MLXSW_SPZR_ID 0x6002
#define MLXSW_SPZR_LEN 0x70

uint8_t mlxsw_reg_spzr_swid_get(const char *buf);

void mlxsw_reg_spzr_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_spzr_router_entity_get(const char *buf);

void mlxsw_reg_spzr_router_entity_set(char *buf, uint8_t val);

void mlxsw_reg_spzr_cm2_set(char *buf, uint8_t val);

void mlxsw_reg_spzr_ndm_set(char *buf, uint8_t val);

void mlxsw_reg_spzr_enh_sw_p0_mask_set(char *buf, uint8_t val);

void mlxsw_reg_spzr_cm_set(char *buf, uint8_t val);

void mlxsw_reg_spzr_vk_set(char *buf, uint8_t val);

void mlxsw_reg_spzr_mp_set(char *buf, uint8_t val);

void mlxsw_reg_spzr_sig_set(char *buf, uint8_t val);

void mlxsw_reg_spzr_ng_set(char *buf, uint8_t val);

void mlxsw_reg_spzr_g0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_spzr_enh_sw_p0_get(const char *buf);

void mlxsw_reg_spzr_enh_sw_p0_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_spzr_capability_mask_get(const char *buf);

void mlxsw_reg_spzr_capability_mask_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_spzr_system_image_guid_h_get(const char *buf);

void mlxsw_reg_spzr_system_image_guid_h_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_spzr_system_image_guid_l_get(const char *buf);

void mlxsw_reg_spzr_system_image_guid_l_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_spzr_guid0_h_get(const char *buf);

void mlxsw_reg_spzr_guid0_h_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_spzr_guid0_l_get(const char *buf);

void mlxsw_reg_spzr_guid0_l_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_spzr_node_guid_h_get(const char *buf);

void mlxsw_reg_spzr_node_guid_h_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_spzr_node_guid_l_get(const char *buf);

void mlxsw_reg_spzr_node_guid_l_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_spzr_capability_mask2_get(const char *buf);

void mlxsw_reg_spzr_capability_mask2_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_spzr_max_pkey_get(const char *buf);

void mlxsw_reg_spzr_node_description_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_spzr_node_description_memcpy_to(char *buf, const char *src);

/* ibfmr
 * -----
 *
 */
#define MLXSW_IBFMR_ID 0x6003
#define MLXSW_IBFMR_LEN 0x10

uint8_t mlxsw_reg_ibfmr_atm_v_get(const char *buf);

uint16_t mlxsw_reg_ibfmr_attribute_id_get(const char *buf);

uint32_t mlxsw_reg_ibfmr_attribute_modifier_get(const char *buf);

/* ibfmrc
 * ------
 *
 */
#define MLXSW_IBFMRC_ID 0x6004
#define MLXSW_IBFMRC_LEN 0x4

uint32_t mlxsw_reg_ibfmrc_attr_id_en_get(const char *buf);

void mlxsw_reg_ibfmrc_attr_id_en_set(char *buf, uint32_t val);

/* ptys
 * ----
 *
 */
#define MLXSW_PTYS_ID 0x5004
#define MLXSW_PTYS_LEN 0x44

uint8_t mlxsw_reg_ptys_reserved_high_get(const char *buf);

uint8_t mlxsw_reg_ptys_an_disable_admin_get(const char *buf);

void mlxsw_reg_ptys_an_disable_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptys_an_disable_cap_get(const char *buf);

void mlxsw_reg_ptys_ee_tx_ready_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptys_tx_ready_e_get(const char *buf);

void mlxsw_reg_ptys_tx_ready_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptys_force_tx_aba_param_get(const char *buf);

void mlxsw_reg_ptys_force_tx_aba_param_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptys_local_port_get(const char *buf);

void mlxsw_reg_ptys_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptys_pnat_get(const char *buf);

void mlxsw_reg_ptys_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptys_lp_msb_get(const char *buf);

void mlxsw_reg_ptys_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptys_port_type_get(const char *buf);

void mlxsw_reg_ptys_port_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptys_plane_ind_get(const char *buf);

void mlxsw_reg_ptys_plane_ind_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptys_transmit_allowed_get(const char *buf);

void mlxsw_reg_ptys_transmit_allowed_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptys_proto_mask_get(const char *buf);

void mlxsw_reg_ptys_proto_mask_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptys_an_status_get(const char *buf);

uint16_t mlxsw_reg_ptys_max_port_rate_get(const char *buf);

uint16_t mlxsw_reg_ptys_data_rate_oper_get(const char *buf);

uint32_t mlxsw_reg_ptys_ext_eth_proto_capability_get(const char *buf);

uint32_t mlxsw_reg_ptys_eth_proto_capability_get(const char *buf);

uint16_t mlxsw_reg_ptys_ib_link_width_capability_get(const char *buf);

uint16_t mlxsw_reg_ptys_ib_proto_capability_get(const char *buf);

uint32_t mlxsw_reg_ptys_ext_eth_proto_admin_get(const char *buf);

void mlxsw_reg_ptys_ext_eth_proto_admin_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ptys_eth_proto_admin_get(const char *buf);

void mlxsw_reg_ptys_eth_proto_admin_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_ptys_ib_link_width_admin_get(const char *buf);

void mlxsw_reg_ptys_ib_link_width_admin_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ptys_ib_proto_admin_get(const char *buf);

void mlxsw_reg_ptys_ib_proto_admin_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_ptys_ext_eth_proto_oper_get(const char *buf);

uint32_t mlxsw_reg_ptys_eth_proto_oper_get(const char *buf);

uint16_t mlxsw_reg_ptys_ib_link_width_oper_get(const char *buf);

uint16_t mlxsw_reg_ptys_ib_proto_oper_get(const char *buf);

uint8_t mlxsw_reg_ptys_xdr_2x_slow_cap_get(const char *buf);

uint8_t mlxsw_reg_ptys_force_lt_frames_cap_get(const char *buf);

uint8_t mlxsw_reg_ptys_force_lt_frames_admin_get(const char *buf);

void mlxsw_reg_ptys_force_lt_frames_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptys_ext_eth_proto_lp_valid_get(const char *buf);

uint8_t mlxsw_reg_ptys_eth_proto_lp_valid_get(const char *buf);

uint8_t mlxsw_reg_ptys_xdr_2x_slow_admin_get(const char *buf);

void mlxsw_reg_ptys_xdr_2x_slow_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptys_xdr_2x_slow_active_get(const char *buf);

uint32_t mlxsw_reg_ptys_lane_rate_oper_get(const char *buf);

uint8_t mlxsw_reg_ptys_connector_type_get(const char *buf);

uint32_t mlxsw_reg_ptys_link_partner_protocol_extended_ib_get(const char *buf);

uint32_t mlxsw_reg_ptys_link_partner_protocol_extended_eth_get(const char *buf);

uint32_t mlxsw_reg_ptys_eth_proto_lp_advertise_get(const char *buf);

uint32_t mlxsw_reg_ptys_proprietary_nvda_proto_cap_get(const char *buf);

uint32_t mlxsw_reg_ptys_proprietary_nvda_proto_admin_get(const char *buf);

void mlxsw_reg_ptys_proprietary_nvda_proto_admin_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ptys_proprietary_nvda_proto_oper_get(const char *buf);

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

uint8_t mlxsw_reg_paos_plane_ind_get(const char *buf);

void mlxsw_reg_paos_plane_ind_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_paos_oper_status_get(const char *buf);

void mlxsw_reg_paos_ase_set(char *buf, uint8_t val);

void mlxsw_reg_paos_ee_set(char *buf, uint8_t val);

void mlxsw_reg_paos_ee_ls_set(char *buf, uint8_t val);

void mlxsw_reg_paos_ee_ps_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_paos_ls_e_get(const char *buf);

void mlxsw_reg_paos_ls_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_paos_logical_state_status_get(const char *buf);

uint8_t mlxsw_reg_paos_ps_e_get(const char *buf);

void mlxsw_reg_paos_ps_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_paos_lock_en_get(const char *buf);

void mlxsw_reg_paos_lock_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_paos_sleep_cap_get(const char *buf);

uint8_t mlxsw_reg_paos_fd_get(const char *buf);

void mlxsw_reg_paos_fd_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_paos_physical_state_status_get(const char *buf);

uint8_t mlxsw_reg_paos_e_get(const char *buf);

void mlxsw_reg_paos_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_paos_lock_mode_get(const char *buf);

/* ppcnt
 * -----
 *
 */
#define MLXSW_PPCNT_ID 0x5008
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

uint8_t mlxsw_reg_ppcnt_lp_gl_get(const char *buf);

void mlxsw_reg_ppcnt_lp_gl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcnt_grp_profile_get(const char *buf);

void mlxsw_reg_ppcnt_grp_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcnt_prio_tc_get(const char *buf);

void mlxsw_reg_ppcnt_prio_tc_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_ppcnt_a_frames_transmitted_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_frames_transmitted_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_frames_received_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_frames_received_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_frame_check_sequence_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_frame_check_sequence_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_alignment_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_alignment_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_octets_transmitted_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_octets_transmitted_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_octets_received_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_octets_received_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_multicast_frames_xmitted_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_multicast_frames_xmitted_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_broadcast_frames_xmitted_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_broadcast_frames_xmitted_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_multicast_frames_received_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_multicast_frames_received_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_broadcast_frames_received_ok_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_broadcast_frames_received_ok_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_in_range_length_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_in_range_length_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_out_of_range_length_field_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_out_of_range_length_field_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_frame_too_long_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_frame_too_long_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_symbol_error_during_carrier_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_symbol_error_during_carrier_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_mac_control_frames_transmitted_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_mac_control_frames_transmitted_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_mac_control_frames_received_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_mac_control_frames_received_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_unsupported_opcodes_received_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_unsupported_opcodes_received_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_pause_mac_ctrl_frames_received_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_pause_mac_ctrl_frames_received_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_pause_mac_ctrl_frames_transmitted_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_a_pause_mac_ctrl_frames_transmitted_low_get(const char *buf);

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

uint32_t mlxsw_reg_ppcnt_ether_stats_drop_events_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_drop_events_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_broadcast_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_broadcast_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_multicast_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_multicast_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_crc_align_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_crc_align_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_undersize_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_undersize_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_oversize_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_oversize_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_fragments_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_fragments_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_jabbers_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_jabbers_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_collisions_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_collisions_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts64octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts64octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts65to127octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts65to127octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts128to255octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts128to255octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts256to511octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts256to511octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts512to1023octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts512to1023octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts1024to1518octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts1024to1518octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts1519to2047octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts1519to2047octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts2048to4095octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts2048to4095octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts4096to8191octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts4096to8191octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts8192to10239octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ether_stats_pkts8192to10239octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_dot3stats_alignment_errors_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_alignment_errors_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_alignment_errors_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_alignment_errors_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_fcs_errors_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_fcs_errors_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_fcs_errors_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_fcs_errors_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_single_collision_frames_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_single_collision_frames_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_single_collision_frames_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_single_collision_frames_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_multiple_collision_frames_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_multiple_collision_frames_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_multiple_collision_frames_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_multiple_collision_frames_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_sqe_test_errors_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_sqe_test_errors_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_sqe_test_errors_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_sqe_test_errors_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_deferred_transmissions_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_deferred_transmissions_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_deferred_transmissions_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_deferred_transmissions_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_late_collisions_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_late_collisions_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_late_collisions_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_late_collisions_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_excessive_collisions_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_excessive_collisions_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_excessive_collisions_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_excessive_collisions_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_internal_mac_transmit_errors_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_internal_mac_transmit_errors_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_internal_mac_transmit_errors_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_internal_mac_transmit_errors_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_carrier_sense_errors_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_carrier_sense_errors_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_carrier_sense_errors_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_carrier_sense_errors_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_frame_too_longs_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_frame_too_longs_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_frame_too_longs_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_frame_too_longs_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_internal_mac_receive_errors_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_internal_mac_receive_errors_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_internal_mac_receive_errors_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_internal_mac_receive_errors_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_symbol_errors_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_symbol_errors_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3stats_symbol_errors_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3stats_symbol_errors_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3control_in_unknown_opcodes_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3control_in_unknown_opcodes_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3control_in_unknown_opcodes_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3control_in_unknown_opcodes_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3in_pause_frames_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3in_pause_frames_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3in_pause_frames_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3in_pause_frames_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3out_pause_frames_high_get(const char *buf);

void mlxsw_reg_ppcnt_dot3out_pause_frames_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_dot3out_pause_frames_low_get(const char *buf);

void mlxsw_reg_ppcnt_dot3out_pause_frames_low_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcnt_port_transmit_wait_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_transmit_wait_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ecn_marked_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ecn_marked_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_no_buffer_discard_mc_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_no_buffer_discard_mc_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_ebp_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_ebp_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_ebp_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_ebp_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_buffer_almost_full_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_buffer_almost_full_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_buffer_full_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_buffer_full_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_icrc_encapsulated_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_icrc_encapsulated_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts64octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts64octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts65to127octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts65to127octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts128to255octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts128to255octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts256to511octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts256to511octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts512to1023octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts512to1023octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts1024to1518octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts1024to1518octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts1519to2047octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts1519to2047octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts2048to4095octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts2048to4095octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts4096to8191octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts4096to8191octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts8192to10239octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_stats_pkts8192to10239octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ece_marked_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ece_marked_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_int_cksm_err_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_int_cksm_err_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ingress_general_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ingress_general_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ingress_policy_engine_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ingress_policy_engine_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ingress_vlan_membership_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ingress_vlan_membership_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ingress_tag_frame_type_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ingress_tag_frame_type_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_egress_vlan_membership_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_egress_vlan_membership_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_loopback_filter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_loopback_filter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_egress_general_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_egress_general_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_egress_hoq_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_egress_hoq_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_isolation_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_isolation_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_egress_policy_engine_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_egress_policy_engine_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ingress_tx_link_down_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ingress_tx_link_down_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_egress_stp_filter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_egress_stp_filter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_egress_hoq_stall_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_egress_hoq_stall_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_egress_sll_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_egress_sll_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ingress_discard_all_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ingress_discard_all_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_llr_rx_cells_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_llr_rx_cells_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_llr_rx_error_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_llr_rx_error_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_llr_rx_crc_error_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_llr_rx_crc_error_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_llr_tx_cells_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_llr_tx_cells_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_llr_tx_ret_cells_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_llr_tx_ret_cells_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_llr_tx_ret_events_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_llr_tx_ret_events_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_uc_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_uc_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_mc_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_mc_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_bc_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_bc_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_octets_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_octets_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_uc_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_uc_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_mc_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_mc_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_bc_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_bc_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_frames_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_frames_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_pause_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_pause_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_pause_duration_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_pause_duration_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_pause_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_pause_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_pause_duration_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_tx_pause_duration_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_pause_transition_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_pause_transition_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_discards_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_discards_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_device_stall_minor_watermark_cnt_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_device_stall_minor_watermark_cnt_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_device_stall_critical_watermark_cnt_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_device_stall_critical_watermark_cnt_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_transmit_queue_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_transmit_queue_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_no_buffer_discard_uc_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_no_buffer_discard_uc_low_get(const char *buf);

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

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane4_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane4_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane5_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane5_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane6_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane6_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane7_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_phys_layer_cntrs_rs_fec_corrected_symbols_lane7_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_wred_discard_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_wred_discard_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ecn_marked_tc_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ecn_marked_tc_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_no_buffer_discard_uc_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rx_no_buffer_discard_uc_low_get(const char *buf);

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

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_float_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_effective_ber_magnitude_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_effective_ber_coef_float_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_effective_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_symbol_ber_magnitude_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_symbol_ber_coef_float_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_symbol_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane0_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_float_lane0_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane0_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane1_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_float_lane1_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane1_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane2_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_float_lane2_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane2_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane3_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_float_lane3_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane3_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane4_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_float_lane4_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane4_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane5_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_float_lane5_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane5_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane6_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_float_lane6_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_lane6_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_magnitude_lane7_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_phys_layer_stat_cntrs_raw_ber_coef_float_lane7_get(const char *buf);

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

uint16_t mlxsw_reg_ppcnt_symbol_error_counter_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_link_error_recovery_counter_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_link_downed_counter_get(const char *buf);

uint16_t mlxsw_reg_ppcnt_port_rcv_errors_get(const char *buf);

uint16_t mlxsw_reg_ppcnt_port_rcv_remote_physical_errors_get(const char *buf);

uint16_t mlxsw_reg_ppcnt_port_rcv_switch_relay_errors_get(const char *buf);

uint16_t mlxsw_reg_ppcnt_port_xmit_discards_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_port_xmit_constraint_errors_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_port_rcv_constraint_errors_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_local_link_integrity_errors_get(const char *buf);

uint8_t mlxsw_reg_ppcnt_excessive_buffer_overrun_errors_get(const char *buf);

uint16_t mlxsw_reg_ppcnt_qp1_dropped_get(const char *buf);

uint16_t mlxsw_reg_ppcnt_vl_15_dropped_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_data_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_data_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_pkts_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_pkts_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_wait_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_symbol_error_counter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_symbol_error_counter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_error_recovery_counter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_error_recovery_counter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_downed_counter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_link_downed_counter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_remote_physical_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_remote_physical_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_switch_relay_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_switch_relay_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_discards_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_discards_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_constraint_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_constraint_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_constraint_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_constraint_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_local_link_integrity_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_local_link_integrity_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_excessive_buffer_overrun_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_excessive_buffer_overrun_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_vl_15_dropped_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_vl_15_dropped_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_data_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_data_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_data_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_data_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_wait_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_wait_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_qp1_dropped_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_qp1_dropped_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_unicast_xmit_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_unicast_xmit_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_multicast_xmit_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_multicast_xmit_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_unicast_rcv_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_unicast_rcv_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_multicast_rcv_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_multicast_rcv_pkts_low_get(const char *buf);

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

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_codes_loss_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_codes_loss_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_xmit_retry_events_within_t_sec_max_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_plr_xmit_retry_events_within_t_sec_max_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_time_since_last_clear_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_plr_counters_time_since_last_clear_low_get(const char *buf);

uint64_t mlxsw_reg_ppcnt_hist_get(const char *buf, unsigned short outer_index, unsigned short index);

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

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_time_since_last_clear_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_time_since_last_clear_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_unicast_xmit_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_unicast_xmit_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_unicast_rcv_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_unicast_rcv_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_sync_header_error_counter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_sync_header_error_counter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_local_physical_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_local_physical_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_malformed_packet_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_malformed_packet_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_buffer_overrun_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_buffer_overrun_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_dlid_mapping_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_dlid_mapping_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_vl_mapping_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_vl_mapping_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_looping_errors_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_looping_errors_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_inactive_discards_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_inactive_discards_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_neighbor_mtu_discards_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_infiniband_packets_counter_port_neighbor_mtu_discards_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_data_qword_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_data_qword_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_data_qword_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_data_qword_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rq_general_error_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_rq_general_error_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_ebp_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_ebp_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_sw_hoq_lifetime_limit_discards_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_sw_hoq_lifetime_limit_discards_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_dqs2llu_xmit_wait_arb_global_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_dqs2llu_xmit_wait_arb_global_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_grxb_fecn_mark_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_grxb_fecn_mark_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_general_transmit_discard_external_contain_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_general_transmit_discard_external_contain_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_entry_quiet_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_entry_quiet_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_force_entry_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_force_entry_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_exit_local_desired_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_exit_local_desired_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_exit_local_recal_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_exit_local_recal_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_exit_local_recal_with_traffic_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_exit_local_recal_with_traffic_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_exit_local_recal_without_traffic_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_exit_local_recal_without_traffic_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_exit_remote_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_exit_remote_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_exit_remote_probably_recal_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_exit_remote_probably_recal_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_local_full_bw_exit_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_local_full_bw_exit_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_local_low_power_enter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_local_low_power_enter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_remote_full_bw_exit_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_remote_full_bw_exit_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_remote_low_power_enter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_remote_low_power_enter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_local_low_power_exit_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_local_low_power_exit_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_local_full_bw_enter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_local_full_bw_enter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_remote_low_power_exit_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_remote_low_power_exit_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_remote_full_bw_enter_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_remote_full_bw_enter_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_high_speed_steady_state_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_high_speed_steady_state_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_steady_state_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_l1_steady_state_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_other_state_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_other_state_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_time_since_last_clear_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_ppcnt_l1_general_counters_time_since_last_clear_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r8_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r8_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r16_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r16_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r_16_24_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r_16_24_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r_25_32_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r_25_32_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r_33_64_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r_33_64_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r_65_128_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r_65_128_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r_129_256_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r_129_256_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r_257_512_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r_257_512_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r_513_mtu_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_r_513_mtu_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t8_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t8_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t16_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t16_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t_16_24_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t_16_24_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t_25_32_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t_25_32_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t_33_64_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t_33_64_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t_65_128_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t_65_128_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t_129_256_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t_129_256_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t_257_512_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t_257_512_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t_513_mtu_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_cnt_t_513_mtu_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_ibg1_nvl_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_ibg1_nvl_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_ibg1_non_nvl_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_ibg1_non_nvl_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_ibg2_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_ibg2_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_ibg1_nvl_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_ibg1_nvl_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_ibg1_non_nvl_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_ibg1_non_nvl_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_ibg2_pkts_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_ibg2_pkts_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_dqs2llu_xmit_wait_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_dqs2llu_xmit_wait_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_dqs2llu_xmit_wait_arb_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_dqs2llu_xmit_wait_arb_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_pkts_vl_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_pkts_vl_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_pkts_vl15_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_pkts_vl15_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_data_vl_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_data_vl_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_data_vl15_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_rcv_data_vl15_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_pkts_vl_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_pkts_vl_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_pkts_vl15_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_pkts_vl15_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_data_vl_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_data_vl_low_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_data_vl15_high_get(const char *buf);

uint32_t mlxsw_reg_ppcnt_port_xmit_data_vl15_low_get(const char *buf);

/* ptse
 * ----
 *
 */
#define MLXSW_PTSE_ID 0x5047
#define MLXSW_PTSE_LEN 0x8

uint8_t mlxsw_reg_ptse_swid_get(const char *buf);

void mlxsw_reg_ptse_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptse_local_port_get(const char *buf);

void mlxsw_reg_ptse_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptse_lp_msb_get(const char *buf);

void mlxsw_reg_ptse_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptse_tx_ready_get(const char *buf);

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

uint8_t mlxsw_reg_pter_plane_ind_get(const char *buf);

void mlxsw_reg_pter_plane_ind_set(char *buf, uint8_t val);

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

uint32_t mlxsw_reg_pter_pter_port_page_reg_error_count_get(const char *buf);

void mlxsw_reg_pter_pter_port_page_reg_error_count_set(char *buf, uint32_t val);

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

uint8_t mlxsw_reg_prei_plane_ind_get(const char *buf);

void mlxsw_reg_prei_plane_ind_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_prei_time_res_get(const char *buf);

void mlxsw_reg_prei_time_res_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_prei_status_get(const char *buf);

uint8_t mlxsw_reg_prei_error_type_oper_get(const char *buf);

uint8_t mlxsw_reg_prei_error_type_cap_get(const char *buf);

uint8_t mlxsw_reg_prei_error_type_admin_get(const char *buf);

void mlxsw_reg_prei_error_type_admin_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_prei_error_injection_time_get(const char *buf);

void mlxsw_reg_prei_error_injection_time_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_prei_mixer_offset0_get(const char *buf);

void mlxsw_reg_prei_mixer_offset0_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_prei_mixer_offset1_get(const char *buf);

void mlxsw_reg_prei_mixer_offset1_set(char *buf, uint16_t val);

/* plar
 * ----
 *
 */
#define MLXSW_PLAR_ID 0x5068
#define MLXSW_PLAR_LEN 0x80

uint32_t mlxsw_reg_plar_local_port_allocated_get(const char *buf, unsigned short outer_index, unsigned short index);

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

uint8_t mlxsw_reg_pmaos_secondary_get(const char *buf);

uint8_t mlxsw_reg_pmaos_rev_incompatible_get(const char *buf);

uint8_t mlxsw_reg_pmaos_operational_notification_get(const char *buf);

uint8_t mlxsw_reg_pmaos_error_type_get(const char *buf);

uint8_t mlxsw_reg_pmaos_e_get(const char *buf);

void mlxsw_reg_pmaos_e_set(char *buf, uint8_t val);

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

uint16_t mlxsw_reg_pmtdb_port_num1_get(const char *buf);

uint16_t mlxsw_reg_pmtdb_port_num2_get(const char *buf);

uint16_t mlxsw_reg_pmtdb_port_num3_get(const char *buf);

uint16_t mlxsw_reg_pmtdb_port_num4_get(const char *buf);

uint16_t mlxsw_reg_pmtdb_port_num5_get(const char *buf);

uint16_t mlxsw_reg_pmtdb_port_num6_get(const char *buf);

uint16_t mlxsw_reg_pmtdb_port_num7_get(const char *buf);

uint16_t mlxsw_reg_pmtdb_port_num8_get(const char *buf);

/* pmecr
 * -----
 *
 */
#define MLXSW_PMECR_ID 0x501b
#define MLXSW_PMECR_LEN 0x20

uint8_t mlxsw_reg_pmecr_local_port_get(const char *buf);

void mlxsw_reg_pmecr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmecr_lp_msb_get(const char *buf);

void mlxsw_reg_pmecr_lp_msb_set(char *buf, uint8_t val);

void mlxsw_reg_pmecr_ee_set(char *buf, uint8_t val);

void mlxsw_reg_pmecr_eswi_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmecr_swi_get(const char *buf);

void mlxsw_reg_pmecr_swi_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmecr_e_get(const char *buf);

void mlxsw_reg_pmecr_e_set(char *buf, uint8_t val);

/* pmlpe
 * -----
 *
 */
#define MLXSW_PMLPE_ID 0x501c
#define MLXSW_PMLPE_LANE_MODULE_MAPPING_BASE_LEN 0x04 /* base length, without records */
#define MLXSW_PMLPE_LANE_MODULE_MAPPING_REC_LEN 0x04 /* record length */
#define MLXSW_PMLPE_LANE_MODULE_MAPPING_REC_MAX_COUNT 8
#define MLXSW_PMLPE_LEN 0x40

uint8_t mlxsw_reg_pmlpe_rxtx_get(const char *buf);

uint8_t mlxsw_reg_pmlpe_autosplit_get(const char *buf);

uint8_t mlxsw_reg_pmlpe_local_port_get(const char *buf);

void mlxsw_reg_pmlpe_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmlpe_lp_msb_get(const char *buf);

void mlxsw_reg_pmlpe_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmlpe_width_get(const char *buf);

uint8_t mlxsw_reg_pmlpe_rx_lane_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_pmlpe_rx_lane_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint8_t mlxsw_reg_pmlpe_tx_lane_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_pmlpe_tx_lane_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint8_t mlxsw_reg_pmlpe_slot_index_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_pmlpe_slot_index_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint8_t mlxsw_reg_pmlpe_module_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_pmlpe_module_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

/* pmsc
 * ----
 *
 */
#define MLXSW_PMSC_ID 0x501d
#define MLXSW_PMSC_LEN 0x40

uint32_t mlxsw_reg_pmsc_port_mapping_updated_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_pmsc_port_mapping_updated_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

uint8_t mlxsw_reg_pmmp_sticky_get(const char *buf);

void mlxsw_reg_pmmp_sticky_set(char *buf, uint8_t val);

void mlxsw_reg_pmmp_eeprom_override_mask_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pmmp_eeprom_override_get(const char *buf);

void mlxsw_reg_pmmp_eeprom_override_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_pmmp_pmmp_qsfp_protocol_override_layout_cable_breakout_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_qsfp_protocol_override_layout_cable_breakout_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_pmmp_qsfp_protocol_override_layout_ethernet_compliance_code_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_qsfp_protocol_override_layout_ethernet_compliance_code_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_pmmp_qsfp_protocol_override_layout_ext_ethernet_compliance_code_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_qsfp_protocol_override_layout_ext_ethernet_compliance_code_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_pmmp_qsfp_protocol_override_layout_giga_ethernet_compliance_code_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_qsfp_protocol_override_layout_giga_ethernet_compliance_code_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_mod_pwrup_maxduration_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_mod_pwrup_maxduration_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_media_type_encoding_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_media_type_encoding_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_cable_breakout_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_cable_breakout_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_host_electrical_compliance_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_host_electrical_compliance_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_dp_init_maxduration_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_dp_init_maxduration_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_app0_disabled_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_app0_disabled_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_dp_tx_on_maxduration_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_dp_tx_on_maxduration_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_dp_tx_off_maxduration_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_dp_tx_off_maxduration_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_module_media_type_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_module_media_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_media_compliance_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_media_compliance_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_cmis_override_mask_get(const char *buf);

void mlxsw_reg_pmmp_pmmp_cmis_protocol_override_layout_cmis_override_mask_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_pmmp_sfp_cable_protocol_technology_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_pmmp_sfp_cable_protocol_technology_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_pmmp_module_type_get(const char *buf);

void mlxsw_reg_pmmp_module_type_set(char *buf, uint8_t val);

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

/* pmcr
 * ----
 *
 */
#define MLXSW_PMCR_ID 0x5045
#define MLXSW_PMCR_LEN 0x20

uint8_t mlxsw_reg_pmcr_cs_sel_get(const char *buf);

void mlxsw_reg_pmcr_cs_sel_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_local_port_get(const char *buf);

void mlxsw_reg_pmcr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_lp_msb_get(const char *buf);

void mlxsw_reg_pmcr_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_error_code_response_get(const char *buf);

uint8_t mlxsw_reg_pmcr_plane_ind_get(const char *buf);

void mlxsw_reg_pmcr_plane_ind_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_db_get(const char *buf);

void mlxsw_reg_pmcr_db_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_tx_disable_override_value_get(const char *buf);

void mlxsw_reg_pmcr_tx_disable_override_value_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_tx_disable_override_cap_get(const char *buf);

uint8_t mlxsw_reg_pmcr_tx_disable_override_cntl_get(const char *buf);

void mlxsw_reg_pmcr_tx_disable_override_cntl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_cdr_override_value_get(const char *buf);

void mlxsw_reg_pmcr_cdr_override_value_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_cdr_override_cap_get(const char *buf);

uint8_t mlxsw_reg_pmcr_cdr_override_cntl_get(const char *buf);

void mlxsw_reg_pmcr_cdr_override_cntl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_rx_los_override_admin_get(const char *buf);

void mlxsw_reg_pmcr_rx_los_override_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_rx_los_override_cap_get(const char *buf);

uint8_t mlxsw_reg_pmcr_rx_los_override_cntl_get(const char *buf);

void mlxsw_reg_pmcr_rx_los_override_cntl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_rx_amp_override_value_cap_get(const char *buf);

uint8_t mlxsw_reg_pmcr_rx_amp_override_value_get(const char *buf);

void mlxsw_reg_pmcr_rx_amp_override_value_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_rx_amp_override_cap_get(const char *buf);

uint8_t mlxsw_reg_pmcr_rx_amp_override_cntl_get(const char *buf);

void mlxsw_reg_pmcr_rx_amp_override_cntl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_rx_post_emp_override_value_cap_get(const char *buf);

uint8_t mlxsw_reg_pmcr_rx_post_emp_override_value_get(const char *buf);

void mlxsw_reg_pmcr_rx_post_emp_override_value_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_rx_post_emp_override_cap_get(const char *buf);

uint8_t mlxsw_reg_pmcr_rx_post_emp_override_cntl_get(const char *buf);

void mlxsw_reg_pmcr_rx_post_emp_override_cntl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_rx_emp_override_value_cap_get(const char *buf);

uint8_t mlxsw_reg_pmcr_rx_emp_override_value_get(const char *buf);

void mlxsw_reg_pmcr_rx_emp_override_value_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_rx_emp_override_cap_get(const char *buf);

uint8_t mlxsw_reg_pmcr_rx_emp_override_cntl_get(const char *buf);

void mlxsw_reg_pmcr_rx_emp_override_cntl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_tx_adaptive_override_cap_get(const char *buf);

uint8_t mlxsw_reg_pmcr_tx_adaptive_override_cntrl_get(const char *buf);

void mlxsw_reg_pmcr_tx_adaptive_override_cntrl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_tx_adaptive_override_value_get(const char *buf);

void mlxsw_reg_pmcr_tx_adaptive_override_value_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_tx_equ_override_value_cap_get(const char *buf);

uint8_t mlxsw_reg_pmcr_tx_equ_override_value_get(const char *buf);

void mlxsw_reg_pmcr_tx_equ_override_value_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_tx_equ_override_cap_get(const char *buf);

uint8_t mlxsw_reg_pmcr_tx_equ_override_cntl_get(const char *buf);

void mlxsw_reg_pmcr_tx_equ_override_cntl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_rs_override_value_get(const char *buf);

void mlxsw_reg_pmcr_rs_override_value_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_rs_override_cntl_get(const char *buf);

void mlxsw_reg_pmcr_rs_override_cntl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_agc_override_cap_get(const char *buf);

uint8_t mlxsw_reg_pmcr_agc_override_cntl_get(const char *buf);

void mlxsw_reg_pmcr_agc_override_cntl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_ap_sel_override_value_get(const char *buf);

void mlxsw_reg_pmcr_ap_sel_override_value_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmcr_ap_sel_override_cntrl_get(const char *buf);

void mlxsw_reg_pmcr_ap_sel_override_cntrl_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pmcr_agc_target_value_get(const char *buf);

void mlxsw_reg_pmcr_agc_target_value_set(char *buf, uint16_t val);

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

/* pmpt
 * ----
 *
 */
#define MLXSW_PMPT_ID 0x5064
#define MLXSW_PMPT_LEN 0x1c

uint8_t mlxsw_reg_pmpt_e_get(const char *buf);

void mlxsw_reg_pmpt_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpt_ls_get(const char *buf);

uint8_t mlxsw_reg_pmpt_le_get(const char *buf);

void mlxsw_reg_pmpt_le_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpt_slot_index_get(const char *buf);

void mlxsw_reg_pmpt_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpt_module_get(const char *buf);

void mlxsw_reg_pmpt_module_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpt_swap_cap_get(const char *buf);

uint8_t mlxsw_reg_pmpt_invt_cap_get(const char *buf);

uint8_t mlxsw_reg_pmpt_host_media_get(const char *buf);

void mlxsw_reg_pmpt_host_media_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pmpt_lane_mask_get(const char *buf);

void mlxsw_reg_pmpt_lane_mask_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_pmpt_status_get(const char *buf);

uint32_t mlxsw_reg_pmpt_prbs_modes_cap_get(const char *buf);

uint8_t mlxsw_reg_pmpt_prbs_mode_admin_get(const char *buf);

void mlxsw_reg_pmpt_prbs_mode_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpt_swap_admin_get(const char *buf);

void mlxsw_reg_pmpt_swap_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpt_invt_admin_get(const char *buf);

void mlxsw_reg_pmpt_invt_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpt_ch_ge_get(const char *buf);

void mlxsw_reg_pmpt_ch_ge_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpt_modulation_get(const char *buf);

void mlxsw_reg_pmpt_modulation_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pmpt_lane_rate_cap_get(const char *buf);

uint16_t mlxsw_reg_pmpt_lane_rate_admin_get(const char *buf);

void mlxsw_reg_pmpt_lane_rate_admin_set(char *buf, uint16_t val);

/* pmpd
 * ----
 *
 */
#define MLXSW_PMPD_ID 0x5065
#define MLXSW_PMPD_LEN 0x30

uint8_t mlxsw_reg_pmpd_snr_cap_get(const char *buf);

uint8_t mlxsw_reg_pmpd_ber_cap_get(const char *buf);

uint8_t mlxsw_reg_pmpd_errors_cap_get(const char *buf);

uint8_t mlxsw_reg_pmpd_slot_index_get(const char *buf);

void mlxsw_reg_pmpd_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpd_module_get(const char *buf);

void mlxsw_reg_pmpd_module_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpd_host_media_get(const char *buf);

void mlxsw_reg_pmpd_host_media_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpd_lane_get(const char *buf);

void mlxsw_reg_pmpd_lane_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpd_cl_get(const char *buf);

void mlxsw_reg_pmpd_cl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmpd_status_get(const char *buf);

uint32_t mlxsw_reg_pmpd_prbs_bits_high_get(const char *buf);

uint32_t mlxsw_reg_pmpd_prbs_bits_low_get(const char *buf);

uint32_t mlxsw_reg_pmpd_prbs_errors_high_get(const char *buf);

uint32_t mlxsw_reg_pmpd_prbs_errors_low_get(const char *buf);

uint16_t mlxsw_reg_pmpd_measured_snr_get(const char *buf);

uint8_t mlxsw_reg_pmpd_ber_magnitude_get(const char *buf);

uint8_t mlxsw_reg_pmpd_ber_coef_get(const char *buf);

/* pmtm
 * ----
 *
 */
#define MLXSW_PMTM_ID 0x5067
#define MLXSW_PMTM_LEN 0x10

uint8_t mlxsw_reg_pmtm_media_width_cap_get(const char *buf);

uint8_t mlxsw_reg_pmtm_slot_index_get(const char *buf);

void mlxsw_reg_pmtm_slot_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmtm_module_get(const char *buf);

void mlxsw_reg_pmtm_module_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmtm_module_media_width_get(const char *buf);

uint8_t mlxsw_reg_pmtm_module_width_get(const char *buf);

void mlxsw_reg_pmtm_module_width_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmtm_module_type_get(const char *buf);

void mlxsw_reg_pmtm_module_type_set(char *buf, uint8_t val);

/* pplr
 * ----
 *
 */
#define MLXSW_PPLR_ID 0x5018
#define MLXSW_PPLR_LEN 0x8

uint8_t mlxsw_reg_pplr_local_port_get(const char *buf);

void mlxsw_reg_pplr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pplr_lp_msb_get(const char *buf);

void mlxsw_reg_pplr_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pplr_linkup_flow_get(const char *buf);

void mlxsw_reg_pplr_linkup_flow_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pplr_apply_im_get(const char *buf);

void mlxsw_reg_pplr_apply_im_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pplr_op_mod_get(const char *buf);

void mlxsw_reg_pplr_op_mod_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pplr_port_type_get(const char *buf);

void mlxsw_reg_pplr_port_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pplr_plane_ind_get(const char *buf);

void mlxsw_reg_pplr_plane_ind_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pplr_lb_cap_get(const char *buf);

uint16_t mlxsw_reg_pplr_lb_en_get(const char *buf);

void mlxsw_reg_pplr_lb_en_set(char *buf, uint16_t val);

/* sltp
 * ----
 *
 */
#define MLXSW_SLTP_ID 0x5027
#define MLXSW_SLTP_LEN 0x4c

uint8_t mlxsw_reg_sltp_lp_msb_get(const char *buf);

void mlxsw_reg_sltp_lp_msb_set(char *buf, uint8_t val);

void mlxsw_reg_sltp_lane_broadcast_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_status_get(const char *buf);

uint8_t mlxsw_reg_sltp_version_get(const char *buf);

uint8_t mlxsw_reg_sltp_local_port_get(const char *buf);

void mlxsw_reg_sltp_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_pnat_get(const char *buf);

void mlxsw_reg_sltp_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_tx_policy_get(const char *buf);

void mlxsw_reg_sltp_tx_policy_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_conf_mod_get(const char *buf);

void mlxsw_reg_sltp_conf_mod_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_lane_get(const char *buf);

void mlxsw_reg_sltp_lane_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_lane_speed_get(const char *buf);

void mlxsw_reg_sltp_lane_speed_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_port_type_get(const char *buf);

void mlxsw_reg_sltp_port_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_c_db_get(const char *buf);

void mlxsw_reg_sltp_c_db_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_28nm_40nm_polarity_get(const char *buf);

void mlxsw_reg_sltp_sltp_28nm_40nm_polarity_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_28nm_40nm_ob_tap0_get(const char *buf);

void mlxsw_reg_sltp_sltp_28nm_40nm_ob_tap0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_28nm_40nm_ob_tap1_get(const char *buf);

void mlxsw_reg_sltp_sltp_28nm_40nm_ob_tap1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_28nm_40nm_ob_tap2_get(const char *buf);

void mlxsw_reg_sltp_sltp_28nm_40nm_ob_tap2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_28nm_40nm_ob_leva_get(const char *buf);

void mlxsw_reg_sltp_sltp_28nm_40nm_ob_leva_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_28nm_40nm_ob_preemp_mode_get(const char *buf);

void mlxsw_reg_sltp_sltp_28nm_40nm_ob_preemp_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_28nm_40nm_ob_reg_get(const char *buf);

void mlxsw_reg_sltp_sltp_28nm_40nm_ob_reg_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_28nm_40nm_ob_bias_get(const char *buf);

void mlxsw_reg_sltp_sltp_28nm_40nm_ob_bias_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_28nm_40nm_ob_norm_get(const char *buf);

uint8_t mlxsw_reg_sltp_sltp_28nm_40nm_ob_bad_stat_get(const char *buf);

uint8_t mlxsw_reg_sltp_sltp_16nm_pre_2_tap_get(const char *buf);

void mlxsw_reg_sltp_sltp_16nm_pre_2_tap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_16nm_pre_tap_get(const char *buf);

void mlxsw_reg_sltp_sltp_16nm_pre_tap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_16nm_main_tap_get(const char *buf);

void mlxsw_reg_sltp_sltp_16nm_main_tap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_16nm_post_tap_get(const char *buf);

void mlxsw_reg_sltp_sltp_16nm_post_tap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_16nm_ob_m2lp_get(const char *buf);

void mlxsw_reg_sltp_sltp_16nm_ob_m2lp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_16nm_ob_amp_get(const char *buf);

void mlxsw_reg_sltp_sltp_16nm_ob_amp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_16nm_ob_alev_out_get(const char *buf);

void mlxsw_reg_sltp_sltp_16nm_ob_alev_out_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sltp_sltp_16nm_ob_bad_stat_get(const char *buf);

uint8_t mlxsw_reg_sltp_sltp_16nm_obplev_get(const char *buf);

void mlxsw_reg_sltp_sltp_16nm_obplev_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_16nm_obnlev_get(const char *buf);

void mlxsw_reg_sltp_sltp_16nm_obnlev_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_16nm_regn_bfm1p_get(const char *buf);

void mlxsw_reg_sltp_sltp_16nm_regn_bfm1p_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_16nm_regp_bfm1n_get(const char *buf);

void mlxsw_reg_sltp_sltp_16nm_regp_bfm1n_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sltp_main_tap_get(const char *buf);

void mlxsw_reg_sltp_main_tap_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_sltp_pre_tap_get(const char *buf);

void mlxsw_reg_sltp_pre_tap_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_sltp_post_tap_get(const char *buf);

void mlxsw_reg_sltp_post_tap_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_sltp_inner_eye_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_sltp_inner_eye_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint8_t mlxsw_reg_sltp_tx_swing_get(const char *buf);

void mlxsw_reg_sltp_tx_swing_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_7nm_vs_peer_db_get(const char *buf);

void mlxsw_reg_sltp_sltp_7nm_vs_peer_db_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_7nm_drv_amp_get(const char *buf);

void mlxsw_reg_sltp_sltp_7nm_drv_amp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_7nm_ob_bad_stat_get(const char *buf);

uint8_t mlxsw_reg_sltp_sltp_7nm_fir_pre3_get(const char *buf);

void mlxsw_reg_sltp_sltp_7nm_fir_pre3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_7nm_fir_pre2_get(const char *buf);

void mlxsw_reg_sltp_sltp_7nm_fir_pre2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_7nm_fir_pre1_get(const char *buf);

void mlxsw_reg_sltp_sltp_7nm_fir_pre1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_7nm_fir_main_get(const char *buf);

void mlxsw_reg_sltp_sltp_7nm_fir_main_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_7nm_fir_post1_get(const char *buf);

void mlxsw_reg_sltp_sltp_7nm_fir_post1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_vs_peer_db_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_vs_peer_db_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_drv_amp_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_drv_amp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_ob_bad_stat_get(const char *buf);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_fir_pre3_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_fir_pre3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_fir_pre2_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_fir_pre2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut3_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut2_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut1_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut0_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut7_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut7_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut6_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut6_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut5_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut5_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut4_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut11_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut11_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut10_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut10_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut9_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut9_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut8_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut8_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut15_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut15_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut14_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut14_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut13_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut13_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut12_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut12_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut19_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut19_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut18_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut18_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut17_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut17_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut16_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut16_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut23_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut23_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut22_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut22_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut21_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut21_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut20_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut20_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut27_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut27_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut26_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut26_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut25_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut25_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut24_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut24_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut31_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut31_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut30_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut30_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut29_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut29_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut28_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut28_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut35_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut35_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut34_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut34_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut33_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut33_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut32_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut32_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut39_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut39_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut38_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut38_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut37_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut37_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut36_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut36_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut43_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut43_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut42_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut42_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut41_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut41_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut40_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut40_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut47_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut47_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut46_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut46_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut45_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut45_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut44_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut44_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut51_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut51_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut50_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut50_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut49_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut49_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut48_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut48_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut55_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut55_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut54_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut54_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut53_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut53_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut52_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut52_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut59_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut59_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut58_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut58_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut57_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut57_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut56_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut56_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut63_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut63_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut62_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut62_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut61_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut61_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sltp_sltp_lut_7nm_lut60_get(const char *buf);

void mlxsw_reg_sltp_sltp_lut_7nm_lut60_set(char *buf, uint8_t val);

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

uint8_t mlxsw_reg_ptasv2_ib_cfg_delaytimeout_cap_get(const char *buf);

uint8_t mlxsw_reg_ptasv2_ib_cfg_delaytimeout_get(const char *buf);

void mlxsw_reg_ptasv2_ib_cfg_delaytimeout_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptasv2_ig_dme_mod_cap_get(const char *buf);

uint8_t mlxsw_reg_ptasv2_ig_dme_mod_admin_get(const char *buf);

void mlxsw_reg_ptasv2_ig_dme_mod_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptasv2_force_an_cap_get(const char *buf);

uint8_t mlxsw_reg_ptasv2_force_an_admin_get(const char *buf);

void mlxsw_reg_ptasv2_force_an_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptasv2_tuning_type_support_get(const char *buf);

uint8_t mlxsw_reg_ptasv2_tuning_type_admin_get(const char *buf);

void mlxsw_reg_ptasv2_tuning_type_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptasv2_en_larger_el_buf_get(const char *buf);

void mlxsw_reg_ptasv2_en_larger_el_buf_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptasv2_max_recovery_retries_en_get(const char *buf);

void mlxsw_reg_ptasv2_max_recovery_retries_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptasv2_phy_count_linkup_delay_get(const char *buf);

void mlxsw_reg_ptasv2_phy_count_linkup_delay_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptasv2_max_recovery_retries_get(const char *buf);

void mlxsw_reg_ptasv2_max_recovery_retries_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptasv2_lt_tuning_support_get(const char *buf);

uint8_t mlxsw_reg_ptasv2_lt_tuning_admin_get(const char *buf);

void mlxsw_reg_ptasv2_lt_tuning_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ptasv2_preset_mask_get(const char *buf);

void mlxsw_reg_ptasv2_preset_mask_set(char *buf, uint8_t val);

/* slsir
 * -----
 *
 */
#define MLXSW_SLSIR_ID 0x502c
#define MLXSW_SLSIR_LEN 0x94

uint8_t mlxsw_reg_slsir_status_get(const char *buf);

uint8_t mlxsw_reg_slsir_version_get(const char *buf);

uint8_t mlxsw_reg_slsir_local_port_get(const char *buf);

void mlxsw_reg_slsir_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slsir_pnat_get(const char *buf);

void mlxsw_reg_slsir_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slsir_lp_msb_get(const char *buf);

void mlxsw_reg_slsir_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slsir_lane_get(const char *buf);

void mlxsw_reg_slsir_lane_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slsir_port_type_get(const char *buf);

void mlxsw_reg_slsir_port_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slsir_slsir_7nm_nop_rsunf_error_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_nop_rsovf_error_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_nop_dsunf_error_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_nop_dsovf_error_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_peq_adc_overload_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_feq_adc_overload_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_cdr_error_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_imem_chksm_error_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_rx_ugl_state_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_rx_eom_ugl_state_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_rx_cal_ugl_state_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_rx_eq_ugl_state_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_tx_ugl_state_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_recovery_retries_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_imem_loading_retries_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_sd_hits_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_sd_iter_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_rd_iter_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_ae_state_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_rx_init_abort_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_rx_init_done_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_cdr_abort_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_cdr_done_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_cal_abort_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_cal_done_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_eq_abort_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_eq_done_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_eom_abort_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_eom_done_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_uphy_rev_subminor_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_bkv_revision_cln_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_bkv_revision_rx_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_uphy_rev_major_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_uphy_rev_minor_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_err_ind_it_3_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_err_ind_it_2_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_err_ind_it_1_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_7nm_err_ind_it_0_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_clear_causes_get(const char *buf);

void mlxsw_reg_slsir_slsir_5nm_clear_causes_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slsir_slsir_5nm_clear_counters_get(const char *buf);

void mlxsw_reg_slsir_slsir_5nm_clear_counters_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_slsir_slsir_5nm_sfec_align_ok_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_sfec_align_fail_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_dfd_trigger_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_nop_rsunf_error_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_nop_rsovf_error_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_nop_dsunf_error_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_nop_dsovf_error_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_peq_adc_overload_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_feq_adc_overload_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_cdr_error_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_imem_chksm_error_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_cdr_error_cnt_get(const char *buf);

uint16_t mlxsw_reg_slsir_slsir_5nm_cal_error_cnt_get(const char *buf);

uint16_t mlxsw_reg_slsir_slsir_5nm_bist_err_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_cdr_seq_done_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_cdr_seq_abort_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_rx_init_done_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_rx_init_abort_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_eq_done_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_eq_abort_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_cal_done_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_cal_abort_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_margin_done_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_margin_yield_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_eom_done_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_eom_abort_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_ae_state_get(const char *buf);

uint16_t mlxsw_reg_slsir_slsir_5nm_pll_ui_shift_cnt_get(const char *buf);

uint16_t mlxsw_reg_slsir_slsir_5nm_bin_cnt_get(const char *buf);

uint16_t mlxsw_reg_slsir_slsir_5nm_event_cnt_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_bkv_major_cln_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_bkv_minor_cln_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_bkv_major_dln_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_bkv_minor_dln_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_uphy_ver_major_get(const char *buf);

uint8_t mlxsw_reg_slsir_slsir_5nm_uphy_ver_minor_get(const char *buf);

/* pddr
 * ----
 *
 */
#define MLXSW_PDDR_ID 0x5031
#define MLXSW_PDDR_LEN 0x100

uint8_t mlxsw_reg_pddr_local_port_get(const char *buf);

void mlxsw_reg_pddr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_pnat_get(const char *buf);

void mlxsw_reg_pddr_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_lp_msb_get(const char *buf);

void mlxsw_reg_pddr_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_plane_ind_get(const char *buf);

void mlxsw_reg_pddr_plane_ind_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_port_type_get(const char *buf);

void mlxsw_reg_pddr_port_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_clr_get(const char *buf);

void mlxsw_reg_pddr_clr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_module_info_ext_get(const char *buf);

void mlxsw_reg_pddr_module_info_ext_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_dev_get(const char *buf);

void mlxsw_reg_pddr_dev_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_page_select_get(const char *buf);

void mlxsw_reg_pddr_page_select_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_proto_active_get(const char *buf);

uint8_t mlxsw_reg_pddr_neg_mode_active_get(const char *buf);

uint8_t mlxsw_reg_pddr_pd_fsm_state_get(const char *buf);

uint8_t mlxsw_reg_pddr_phy_mngr_fsm_state_get(const char *buf);

uint8_t mlxsw_reg_pddr_eth_an_fsm_state_get(const char *buf);

uint8_t mlxsw_reg_pddr_ib_phy_fsm_state_get(const char *buf);

uint8_t mlxsw_reg_pddr_phy_hst_fsm_state_get(const char *buf);

uint16_t mlxsw_reg_pddr_phy_manager_link_width_enabled_get(const char *buf);

uint16_t mlxsw_reg_pddr_phy_manager_link_proto_enabled_get(const char *buf);

uint32_t mlxsw_reg_pddr_phy_manager_link_eth_enabled_get(const char *buf);

uint16_t mlxsw_reg_pddr_core_to_phy_link_width_enabled_get(const char *buf);

uint16_t mlxsw_reg_pddr_core_to_phy_link_proto_enabled_get(const char *buf);

uint32_t mlxsw_reg_pddr_core_to_phy_link_eth_enabled_get(const char *buf);

uint16_t mlxsw_reg_pddr_cable_link_width_cap_get(const char *buf);

uint16_t mlxsw_reg_pddr_cable_link_speed_cap_get(const char *buf);

uint32_t mlxsw_reg_pddr_cable_ext_eth_proto_cap_get(const char *buf);

uint16_t mlxsw_reg_pddr_link_width_active_get(const char *buf);

uint16_t mlxsw_reg_pddr_link_speed_active_get(const char *buf);

uint32_t mlxsw_reg_pddr_link_eth_active_get(const char *buf);

uint8_t mlxsw_reg_pddr_retran_mode_active_get(const char *buf);

uint8_t mlxsw_reg_pddr_retran_mode_request_get(const char *buf);

uint16_t mlxsw_reg_pddr_loopback_mode_get(const char *buf);

uint16_t mlxsw_reg_pddr_fec_mode_active_get(const char *buf);

uint16_t mlxsw_reg_pddr_fec_mode_request_get(const char *buf);

uint16_t mlxsw_reg_pddr_profile_fec_in_use_get(const char *buf);

uint8_t mlxsw_reg_pddr_nlpn_fsm_state_get(const char *buf);

uint8_t mlxsw_reg_pddr_eth_25g_50g_fec_support_get(const char *buf);

uint8_t mlxsw_reg_pddr_eth_100g_fec_support_get(const char *buf);

uint32_t mlxsw_reg_pddr_pd_link_enabled_get(const char *buf);

uint32_t mlxsw_reg_pddr_phy_hst_link_enabled_get(const char *buf);

uint32_t mlxsw_reg_pddr_eth_an_link_enabled_get(const char *buf);

uint8_t mlxsw_reg_pddr_linkup_retry_iterations_get(const char *buf);

uint8_t mlxsw_reg_pddr_core_to_phy_state_get(const char *buf);

uint8_t mlxsw_reg_pddr_psi_fsm_state_get(const char *buf);

uint32_t mlxsw_reg_pddr_cable_proto_cap_ext_get(const char *buf);

uint16_t mlxsw_reg_pddr_group_opcode_get(const char *buf);

void mlxsw_reg_pddr_group_opcode_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pddr_monitor_opcode_get(const char *buf);

void mlxsw_reg_pddr_monitor_opcode_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pddr_advanced_opcode_get(const char *buf);

void mlxsw_reg_pddr_advanced_opcode_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pddr_user_feedback_data_get(const char *buf);

void mlxsw_reg_pddr_user_feedback_data_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pddr_user_feedback_index_get(const char *buf);

void mlxsw_reg_pddr_user_feedback_index_set(char *buf, uint16_t val);

void mlxsw_reg_pddr_status_message_memcpy_from(const char *buf, char *dst);

uint8_t mlxsw_reg_pddr_remote_device_type_get(const char *buf);

uint8_t mlxsw_reg_pddr_negotiation_mask_get(const char *buf);

uint8_t mlxsw_reg_pddr_port_notifications_get(const char *buf);

uint16_t mlxsw_reg_pddr_num_of_negotiation_attempts_get(const char *buf);

uint8_t mlxsw_reg_pddr_ib_revision_get(const char *buf);

uint8_t mlxsw_reg_pddr_lp_ib_revision_get(const char *buf);

uint8_t mlxsw_reg_pddr_hw_link_phy_state_get(const char *buf);

uint16_t mlxsw_reg_pddr_phy_manger_disable_mask_get(const char *buf);

uint32_t mlxsw_reg_pddr_pcs_phy_state_get(const char *buf);

uint32_t mlxsw_reg_pddr_lp_proto_enabled_get(const char *buf);

uint16_t mlxsw_reg_pddr_lp_fec_mode_support_get(const char *buf);

uint16_t mlxsw_reg_pddr_lp_fec_mode_request_get(const char *buf);

uint32_t mlxsw_reg_pddr_ib_last_link_down_reason_get(const char *buf);

void mlxsw_reg_pddr_eth_last_link_down_lane_memcpy_from(const char *buf, char *dst);

uint32_t mlxsw_reg_pddr_speed_deg_db_get(const char *buf);

uint32_t mlxsw_reg_pddr_degrade_grade_lane0_get(const char *buf);

uint32_t mlxsw_reg_pddr_degrade_grade_lane1_get(const char *buf);

uint32_t mlxsw_reg_pddr_degrade_grade_lane2_get(const char *buf);

uint32_t mlxsw_reg_pddr_degrade_grade_lane3_get(const char *buf);

uint8_t mlxsw_reg_pddr_num_of_presets_tested_lane4_get(const char *buf);

uint8_t mlxsw_reg_pddr_num_of_presets_tested_lane5_get(const char *buf);

uint8_t mlxsw_reg_pddr_num_of_presets_tested_lane6_get(const char *buf);

uint8_t mlxsw_reg_pddr_num_of_presets_tested_lane7_get(const char *buf);

uint16_t mlxsw_reg_pddr_kr_startup_debug_indications_4_get(const char *buf);

uint16_t mlxsw_reg_pddr_kr_startup_debug_indications_5_get(const char *buf);

uint16_t mlxsw_reg_pddr_kr_startup_debug_indications_6_get(const char *buf);

uint16_t mlxsw_reg_pddr_kr_startup_debug_indications_7_get(const char *buf);

uint8_t mlxsw_reg_pddr_num_of_presets_tested_lane0_get(const char *buf);

uint8_t mlxsw_reg_pddr_num_of_presets_tested_lane1_get(const char *buf);

uint8_t mlxsw_reg_pddr_num_of_presets_tested_lane2_get(const char *buf);

uint8_t mlxsw_reg_pddr_num_of_presets_tested_lane3_get(const char *buf);

void mlxsw_reg_pddr_kr_startup_fsm_lane_memcpy_from(const char *buf, char *dst);

uint32_t mlxsw_reg_pddr_eth_an_debug_indication_get(const char *buf);

uint8_t mlxsw_reg_pddr_cdr_not_locked_cnt_get(const char *buf);

uint8_t mlxsw_reg_pddr_fall_from_cfg_idle_cnt_get(const char *buf);

uint16_t mlxsw_reg_pddr_fall_from_cfg_idle_cdr_cnt_get(const char *buf);

uint8_t mlxsw_reg_pddr_eth_an_watchdog_cnt_get(const char *buf);

uint8_t mlxsw_reg_pddr_rounds_waited_for_peer_to_end_test_get(const char *buf);

uint16_t mlxsw_reg_pddr_ib_phy_fsm_state_trace_get(const char *buf);

uint16_t mlxsw_reg_pddr_kr_startup_debug_indications_0_get(const char *buf);

uint16_t mlxsw_reg_pddr_kr_startup_debug_indications_1_get(const char *buf);

uint16_t mlxsw_reg_pddr_kr_startup_debug_indications_2_get(const char *buf);

uint16_t mlxsw_reg_pddr_kr_startup_debug_indications_3_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_tuning_stages_lane_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_pddr_plu_rx_polarity_get(const char *buf);

uint8_t mlxsw_reg_pddr_plu_tx_polarity_get(const char *buf);

uint8_t mlxsw_reg_pddr_plu_rx_pwrup_get(const char *buf);

uint8_t mlxsw_reg_pddr_plu_tx_pwrup_get(const char *buf);

uint8_t mlxsw_reg_pddr_signal_detected_get(const char *buf);

uint8_t mlxsw_reg_pddr_plr_outstanding_cells_get(const char *buf);

uint8_t mlxsw_reg_pddr_plu_rx_speed_get(const char *buf);

uint8_t mlxsw_reg_pddr_plu_tx_speed_get(const char *buf);

uint8_t mlxsw_reg_pddr_sd_valid_get(const char *buf);

uint8_t mlxsw_reg_pddr_ib_cfg_delay_timeout_get(const char *buf);

uint8_t mlxsw_reg_pddr_irisc_status_get(const char *buf);

uint32_t mlxsw_reg_pddr_stamping_reason_get(const char *buf);

uint32_t mlxsw_reg_pddr_kr_frame_lock_tuning_failure_events_count_get(const char *buf);

uint32_t mlxsw_reg_pddr_kr_full_tuning_failure_count_get(const char *buf);

uint16_t mlxsw_reg_pddr_ib_debug_indication_get(const char *buf);

uint16_t mlxsw_reg_pddr_pm_debug_indication_get(const char *buf);

uint8_t mlxsw_reg_pddr_pd_cat_val_get(const char *buf);

uint8_t mlxsw_reg_pddr_pd_catastrophic_enum_get(const char *buf);

uint8_t mlxsw_reg_pddr_hst_cat_val_get(const char *buf);

uint8_t mlxsw_reg_pddr_hst_catastrophic_enum_get(const char *buf);

uint8_t mlxsw_reg_pddr_an_cat_val_get(const char *buf);

uint8_t mlxsw_reg_pddr_an_catastrophic_enum_get(const char *buf);

uint8_t mlxsw_reg_pddr_pm_cat_val_get(const char *buf);

uint8_t mlxsw_reg_pddr_pm_catastrophic_enum_get(const char *buf);

uint32_t mlxsw_reg_pddr_pd_debug_indication_get(const char *buf);

uint8_t mlxsw_reg_pddr_psi_collision1_get(const char *buf);

uint16_t mlxsw_reg_pddr_psi_collision2_get(const char *buf);

uint8_t mlxsw_reg_pddr_hst_mismatch_reason_get(const char *buf);

uint8_t mlxsw_reg_pddr_fp_signal_detect_count_get(const char *buf);

uint8_t mlxsw_reg_pddr_pd_count_get(const char *buf);

uint8_t mlxsw_reg_pddr_nlpn_debug_ind_mask_get(const char *buf);

uint32_t mlxsw_reg_pddr_phy2mod_speed_req_get(const char *buf);

uint8_t mlxsw_reg_pddr_eeprom_prsnt_get(const char *buf);

uint8_t mlxsw_reg_pddr_no_dme_mod_get(const char *buf);

uint8_t mlxsw_reg_pddr_one_pll_mod_get(const char *buf);

uint8_t mlxsw_reg_pddr_phy2mod_ack_lanes_get(const char *buf);

uint8_t mlxsw_reg_pddr_phy2mod_deactivate_lanes_get(const char *buf);

uint8_t mlxsw_reg_pddr_port_xmit_pkts_inc_s1_get(const char *buf);

uint8_t mlxsw_reg_pddr_port_xmit_pkts_inc_s0_get(const char *buf);

uint8_t mlxsw_reg_pddr_cnt_rx_frame_received_ok_s1_get(const char *buf);

uint8_t mlxsw_reg_pddr_cnt_rx_frame_received_ok_s0_get(const char *buf);

uint8_t mlxsw_reg_pddr_macsec_en_plt1_s1_get(const char *buf);

uint8_t mlxsw_reg_pddr_macsec_en_plt1_s0_get(const char *buf);

uint8_t mlxsw_reg_pddr_macsec_en_plt0_s1_get(const char *buf);

uint8_t mlxsw_reg_pddr_macsec_en_plt0_s0_get(const char *buf);

uint8_t mlxsw_reg_pddr_reconciliation_mux_plt1_get(const char *buf);

uint8_t mlxsw_reg_pddr_reconciliation_mux_plt0_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_bypass_mux_plt1_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_bypass_mux_plt0_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_bypass_mux_plt1_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_bypass_mux_plt0_get(const char *buf);

uint16_t mlxsw_reg_pddr_plr_rtt_hdr_threshold_get(const char *buf);

uint16_t mlxsw_reg_pddr_plr_rtt_ndr_threshold_get(const char *buf);

uint16_t mlxsw_reg_pddr_plr_rtt_xdr_threshold_get(const char *buf);

uint8_t mlxsw_reg_pddr_cable_technology_get(const char *buf);

void mlxsw_reg_pddr_cable_technology_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_cable_breakout_get(const char *buf);

void mlxsw_reg_pddr_cable_breakout_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_ext_ethernet_compliance_code_get(const char *buf);

void mlxsw_reg_pddr_ext_ethernet_compliance_code_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_ethernet_compliance_code_get(const char *buf);

void mlxsw_reg_pddr_ethernet_compliance_code_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_cable_type_get(const char *buf);

uint8_t mlxsw_reg_pddr_cable_vendor_get(const char *buf);

uint8_t mlxsw_reg_pddr_cable_length_get(const char *buf);

uint8_t mlxsw_reg_pddr_cable_identifier_get(const char *buf);

uint8_t mlxsw_reg_pddr_cable_power_class_get(const char *buf);

uint8_t mlxsw_reg_pddr_max_power_get(const char *buf);

uint8_t mlxsw_reg_pddr_cable_rx_amp_get(const char *buf);

uint8_t mlxsw_reg_pddr_cable_rx_emphasis_get(const char *buf);

uint8_t mlxsw_reg_pddr_cable_tx_equalization_get(const char *buf);

uint8_t mlxsw_reg_pddr_cable_attenuation_25g_get(const char *buf);

uint8_t mlxsw_reg_pddr_cable_attenuation_12g_get(const char *buf);

uint8_t mlxsw_reg_pddr_cable_attenuation_7g_get(const char *buf);

uint8_t mlxsw_reg_pddr_cable_attenuation_5g_get(const char *buf);

uint8_t mlxsw_reg_pddr_cable_rx_post_emphasis_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_cdr_cap_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_cdr_cap_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_cdr_state_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_cdr_state_get(const char *buf);

void mlxsw_reg_pddr_vendor_name_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_pddr_vendor_pn_memcpy_from(const char *buf, char *dst);

uint32_t mlxsw_reg_pddr_vendor_rev_get(const char *buf);

uint32_t mlxsw_reg_pddr_fw_version_get(const char *buf);

void mlxsw_reg_pddr_vendor_sn_memcpy_from(const char *buf, char *dst);

uint16_t mlxsw_reg_pddr_temperature_get(const char *buf);

uint16_t mlxsw_reg_pddr_voltage_get(const char *buf);

uint16_t mlxsw_reg_pddr_rx_power_lane0_get(const char *buf);

uint16_t mlxsw_reg_pddr_rx_power_lane1_get(const char *buf);

uint16_t mlxsw_reg_pddr_rx_power_lane2_get(const char *buf);

uint16_t mlxsw_reg_pddr_rx_power_lane3_get(const char *buf);

uint16_t mlxsw_reg_pddr_rx_power_lane4_get(const char *buf);

uint16_t mlxsw_reg_pddr_rx_power_lane5_get(const char *buf);

uint16_t mlxsw_reg_pddr_rx_power_lane6_get(const char *buf);

uint16_t mlxsw_reg_pddr_rx_power_lane7_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_power_lane0_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_power_lane1_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_power_lane2_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_power_lane3_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_power_lane4_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_power_lane5_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_power_lane6_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_power_lane7_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_bias_lane0_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_bias_lane1_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_bias_lane2_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_bias_lane3_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_bias_lane4_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_bias_lane5_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_bias_lane6_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_bias_lane7_get(const char *buf);

uint16_t mlxsw_reg_pddr_temperature_high_th_get(const char *buf);

uint16_t mlxsw_reg_pddr_temperature_low_th_get(const char *buf);

uint16_t mlxsw_reg_pddr_voltage_high_th_get(const char *buf);

uint16_t mlxsw_reg_pddr_voltage_low_th_get(const char *buf);

uint16_t mlxsw_reg_pddr_rx_power_high_th_get(const char *buf);

uint16_t mlxsw_reg_pddr_rx_power_low_th_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_power_high_th_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_power_low_th_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_bias_high_th_get(const char *buf);

uint16_t mlxsw_reg_pddr_tx_bias_low_th_get(const char *buf);

uint8_t mlxsw_reg_pddr_module_st_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_power_type_get(const char *buf);

uint8_t mlxsw_reg_pddr_did_cap_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_output_valid_cap_get(const char *buf);

void mlxsw_reg_pddr_rx_output_valid_cap_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pddr_smf_length_get(const char *buf);

uint16_t mlxsw_reg_pddr_wavelength_get(const char *buf);

uint8_t mlxsw_reg_pddr_active_set_host_compliance_code_get(const char *buf);

uint8_t mlxsw_reg_pddr_active_set_media_compliance_code_get(const char *buf);

uint8_t mlxsw_reg_pddr_ib_compliance_code_get(const char *buf);

uint8_t mlxsw_reg_pddr_nbr250_get(const char *buf);

uint8_t mlxsw_reg_pddr_nbr100_get(const char *buf);

uint8_t mlxsw_reg_pddr_monitor_cap_mask_get(const char *buf);

uint8_t mlxsw_reg_pddr_ib_width_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_st_lane0_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_st_lane1_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_st_lane2_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_st_lane3_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_st_lane4_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_st_lane5_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_st_lane6_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_st_lane7_get(const char *buf);

uint8_t mlxsw_reg_pddr_length_om2_get(const char *buf);

uint8_t mlxsw_reg_pddr_length_om3_get(const char *buf);

uint8_t mlxsw_reg_pddr_length_om4_get(const char *buf);

uint8_t mlxsw_reg_pddr_length_om5_get(const char *buf);

uint8_t mlxsw_reg_pddr_length_om1_get(const char *buf);

uint32_t mlxsw_reg_pddr_wavelength_tolerance_get(const char *buf);

uint8_t mlxsw_reg_pddr_memory_map_rev_get(const char *buf);

uint32_t mlxsw_reg_pddr_memory_map_compliance_get(const char *buf);

uint64_t mlxsw_reg_pddr_date_code_get(const char *buf);

uint8_t mlxsw_reg_pddr_connector_type_get(const char *buf);

uint32_t mlxsw_reg_pddr_vendor_oui_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_input_freq_sync_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_output_valid_get(const char *buf);

uint16_t mlxsw_reg_pddr_max_fiber_length_get(const char *buf);

uint8_t mlxsw_reg_pddr_error_code_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_invalid_fsm_sv_get(const char *buf);

uint16_t mlxsw_reg_pddr_pddr_port_events_page_layout_invalid_fsm_ps_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_kr_false_ready_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_kr_false_ready_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_mod_req_nack_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_mod_req_nack_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_mod_req_busy_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_mod_req_busy_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_mod_config_to_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_mod_config_to_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_mod_adapt_faild_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_mod_adapt_faild_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_pm_fifo_full_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_pm_fifo_full_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_protocol_check_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_protocol_check_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_input_event_sv_get(const char *buf);

uint16_t mlxsw_reg_pddr_pddr_port_events_page_layout_input_event_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_lane_mapping_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_lane_mapping_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_qsfp_zero_atten_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_qsfp_zero_atten_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_mono_reach_low_limit_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_mono_reach_low_limit_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_mono_reach_high_limit_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_mono_reach_high_limit_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_mono_flow_height_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_mono_flow_height_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_single_gains_bad_val_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_single_gains_bad_val_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_init_all_gains_bad_val_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_port_events_page_layout_init_all_gains_bad_val_get(const char *buf);

uint32_t mlxsw_reg_pddr_pddr_port_events_page_layout_clr_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_pddr_pddr_port_events_page_layout_clr_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_invalid_port_access_sv_get(const char *buf);

uint16_t mlxsw_reg_pddr_pddr_device_events_page_invalid_port_access_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_pll_state_sv_1_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_pll_state_mask_center1_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_pll_state_sv_0_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_pll_state_mask_center0_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_main_irisc_timeout_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_tile_irisc_timeout_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout0_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout1_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout2_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout3_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout4_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_cr_space_timeout_mcm_main_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_cr_space_timeout_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_cr_space_timeout_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_analog_phy_to_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_analog_phy_to_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_logical_phy_to_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_logical_phy_to_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_varactors_calib_fail_center1_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_varactors_calib_fail_center1_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_varactors_calib_fail_center0_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_varactors_calib_fail_center0_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_irisc_stuck_mask_sv_get(const char *buf);

uint32_t mlxsw_reg_pddr_pddr_device_events_page_irisc_stuck_mask_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_pll_lock_sv_1_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_pll_unlocl_mask_center1_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_pll_lock_sv_0_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_pll_unlocl_mask_center0_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_uc_stack_overflow_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_uc_crspace_timeout_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_pwr_governor_err_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_pwr_governor_err_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_iopl_err_center1_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_iopl_err_center1_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_iopl_err_center0_sv_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_iopl_err_center0_get(const char *buf);

uint32_t mlxsw_reg_pddr_pddr_device_events_page_clr_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_pddr_pddr_device_events_page_clr_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_pddr_pddr_device_events_page_main_irisc_address_get(const char *buf);

uint32_t mlxsw_reg_pddr_pddr_device_events_page_main_irisc_ip_get(const char *buf);

uint32_t mlxsw_reg_pddr_pddr_device_events_page_tile_irisc_address_get(const char *buf);

uint32_t mlxsw_reg_pddr_pddr_device_events_page_tile_irisc_ip_get(const char *buf);

uint16_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout0_address_get(const char *buf);

uint16_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout1_address_get(const char *buf);

uint16_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout2_address_get(const char *buf);

uint16_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout3_address_get(const char *buf);

uint16_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout4_address_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout0_cluster_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout1_cluster_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout2_cluster_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout3_cluster_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_plu_timeout4_cluster_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_irisc_tile_idx_get(const char *buf);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_uc_crspace_timeout_lane_get(const char *buf);

void mlxsw_reg_pddr_pddr_device_events_page_uc_crspace_timeout_lane_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_uc_crspace_timeout_cl_get(const char *buf);

void mlxsw_reg_pddr_pddr_device_events_page_uc_crspace_timeout_cl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_uc_stack_overflow_lane_get(const char *buf);

void mlxsw_reg_pddr_pddr_device_events_page_uc_stack_overflow_lane_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_pddr_device_events_page_uc_stack_overflow_cl_get(const char *buf);

void mlxsw_reg_pddr_pddr_device_events_page_uc_stack_overflow_cl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_down_blame_get(const char *buf);

uint8_t mlxsw_reg_pddr_local_reason_opcode_get(const char *buf);

uint8_t mlxsw_reg_pddr_remote_reason_opcode_get(const char *buf);

uint8_t mlxsw_reg_pddr_ts1_opcode_get(const char *buf);

uint8_t mlxsw_reg_pddr_e2e_reason_opcode_get(const char *buf);

uint8_t mlxsw_reg_pddr_cons_raw_norm_ber_get(const char *buf);

uint8_t mlxsw_reg_pddr_last_raw_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_pddr_last_raw_ber_magnitude_get(const char *buf);

uint16_t mlxsw_reg_pddr_num_of_symbol_ber_alarms_get(const char *buf);

uint8_t mlxsw_reg_pddr_min_raw_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_pddr_min_raw_ber_magnitude_get(const char *buf);

uint8_t mlxsw_reg_pddr_max_raw_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_pddr_max_raw_ber_magnitude_get(const char *buf);

uint16_t mlxsw_reg_pddr_num_of_eff_ber_alarms_get(const char *buf);

uint16_t mlxsw_reg_pddr_num_of_raw_ber_alarms_get(const char *buf);

uint32_t mlxsw_reg_pddr_time_to_link_down_to_disable_get(const char *buf);

uint32_t mlxsw_reg_pddr_time_to_link_down_to_rx_loss_get(const char *buf);

uint8_t mlxsw_reg_pddr_cons_eff_norm_ber_get(const char *buf);

uint8_t mlxsw_reg_pddr_last_eff_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_pddr_last_eff_ber_magnitude_get(const char *buf);

uint8_t mlxsw_reg_pddr_min_eff_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_pddr_min_eff_ber_magnitude_get(const char *buf);

uint8_t mlxsw_reg_pddr_cons_symbol_norm_ber_get(const char *buf);

uint8_t mlxsw_reg_pddr_max_symbol_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_pddr_max_symbol_ber_magnitude_get(const char *buf);

uint8_t mlxsw_reg_pddr_max_eff_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_pddr_max_eff_ber_magnitude_get(const char *buf);

uint8_t mlxsw_reg_pddr_last_symbol_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_pddr_last_symbol_ber_magnitude_get(const char *buf);

uint8_t mlxsw_reg_pddr_min_symbol_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_pddr_min_symbol_ber_magnitude_get(const char *buf);

uint32_t mlxsw_reg_pddr_ib_port_events_get(const char *buf);

uint32_t mlxsw_reg_pddr_etherent_port_events_get(const char *buf);

uint32_t mlxsw_reg_pddr_general_port_events_get(const char *buf);

uint8_t mlxsw_reg_pddr_up_reason_pwr_get(const char *buf);

uint8_t mlxsw_reg_pddr_up_reason_drv_get(const char *buf);

uint8_t mlxsw_reg_pddr_up_reason_mng_get(const char *buf);

uint32_t mlxsw_reg_pddr_time_to_link_up_get(const char *buf);

uint8_t mlxsw_reg_pddr_lt_cnt_get(const char *buf);

uint8_t mlxsw_reg_pddr_fast_link_up_status_get(const char *buf);

uint32_t mlxsw_reg_pddr_time_to_link_up_phy_up_to_active_get(const char *buf);

uint32_t mlxsw_reg_pddr_time_to_link_up_sd_to_phy_up_get(const char *buf);

uint32_t mlxsw_reg_pddr_time_to_link_up_disable_to_sd_get(const char *buf);

uint32_t mlxsw_reg_pddr_time_to_link_up_disable_to_pd_get(const char *buf);

uint8_t mlxsw_reg_pddr_temp_flags_get(const char *buf);

uint8_t mlxsw_reg_pddr_vcc_flags_get(const char *buf);

uint8_t mlxsw_reg_pddr_mod_fw_fault_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_fw_fault_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_los_cap_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_fault_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_los_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_cdr_lol_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_ad_eq_fault_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_power_hi_al_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_power_lo_al_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_power_hi_war_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_power_lo_war_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_bias_hi_al_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_bias_lo_al_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_bias_hi_war_get(const char *buf);

uint8_t mlxsw_reg_pddr_tx_bias_lo_war_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_los_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_cdr_lol_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_power_hi_al_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_power_lo_al_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_power_hi_war_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_power_lo_war_get(const char *buf);

uint8_t mlxsw_reg_pddr_rx_output_valid_change_get(const char *buf);

uint32_t mlxsw_reg_pddr_flag_in_use_get(const char *buf);

uint16_t mlxsw_reg_pddr_pport_get(const char *buf);

void mlxsw_reg_pddr_pport_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_pddr_trigger_active_get(const char *buf);

uint32_t mlxsw_reg_pddr_trigger_cond_state_event_val_get(const char *buf);

void mlxsw_reg_pddr_trigger_cond_state_event_val_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_pddr_trigger_cond_state_or_event_get(const char *buf);

void mlxsw_reg_pddr_trigger_cond_state_or_event_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_trigger_cond_fsm_get(const char *buf);

void mlxsw_reg_pddr_trigger_cond_fsm_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_pre_trigger_buff_mode_get(const char *buf);

void mlxsw_reg_pddr_pre_trigger_buff_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_tracer_mode_get(const char *buf);

void mlxsw_reg_pddr_tracer_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_reset_tracer_get(const char *buf);

void mlxsw_reg_pddr_reset_tracer_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_tracer_enable_get(const char *buf);

void mlxsw_reg_pddr_tracer_enable_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_pddr_fsm_mask_get(const char *buf);

void mlxsw_reg_pddr_fsm_mask_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_pddr_trigger_ptr_get(const char *buf);

uint16_t mlxsw_reg_pddr_buffer_size_get(const char *buf);

uint32_t mlxsw_reg_pddr_ptr_log_data_get(const char *buf);

uint16_t mlxsw_reg_pddr_ptr_next_write_get(const char *buf);

uint32_t mlxsw_reg_pddr_buffer_base_address_get(const char *buf);

uint8_t mlxsw_reg_pddr_fw_module_state_get(const char *buf);

uint8_t mlxsw_reg_pddr_fw_dp_state_lane7_get(const char *buf);

uint8_t mlxsw_reg_pddr_fw_dp_state_lane6_get(const char *buf);

uint8_t mlxsw_reg_pddr_fw_dp_state_lane5_get(const char *buf);

uint8_t mlxsw_reg_pddr_fw_dp_state_lane4_get(const char *buf);

uint8_t mlxsw_reg_pddr_fw_dp_state_lane3_get(const char *buf);

uint8_t mlxsw_reg_pddr_fw_dp_state_lane2_get(const char *buf);

uint8_t mlxsw_reg_pddr_fw_dp_state_lane1_get(const char *buf);

uint8_t mlxsw_reg_pddr_fw_dp_state_lane0_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_req_status_lane7_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_req_status_lane6_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_req_status_lane5_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_req_status_lane4_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_req_status_lane3_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_req_status_lane2_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_req_status_lane1_get(const char *buf);

uint8_t mlxsw_reg_pddr_dp_req_status_lane0_get(const char *buf);

uint8_t mlxsw_reg_pddr_dpsm_apply_state_lane7_get(const char *buf);

uint8_t mlxsw_reg_pddr_dpsm_apply_state_lane6_get(const char *buf);

uint8_t mlxsw_reg_pddr_dpsm_apply_state_lane5_get(const char *buf);

uint8_t mlxsw_reg_pddr_dpsm_apply_state_lane4_get(const char *buf);

uint8_t mlxsw_reg_pddr_dpsm_apply_state_lane3_get(const char *buf);

uint8_t mlxsw_reg_pddr_dpsm_apply_state_lane2_get(const char *buf);

uint8_t mlxsw_reg_pddr_dpsm_apply_state_lane1_get(const char *buf);

uint8_t mlxsw_reg_pddr_dpsm_apply_state_lane0_get(const char *buf);

uint8_t mlxsw_reg_pddr_timer_left_for_dp_active_transition_get(const char *buf);

uint8_t mlxsw_reg_pddr_timer_left_for_high_pwrt_transition_get(const char *buf);

uint8_t mlxsw_reg_pddr_isr_access_enums_get(const char *buf);

void mlxsw_reg_pddr_isr_access_enums_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pddr_isr_track_mod_get(const char *buf);

uint8_t mlxsw_reg_pddr_isr_track_enum_get(const char *buf);

uint8_t mlxsw_reg_pddr_max_isr_enum_get(const char *buf);

uint32_t mlxsw_reg_pddr_max_time_isr_get(const char *buf, unsigned short outer_index, unsigned short index);

uint16_t mlxsw_reg_pddr_info_supported_mask_get(const char *buf);

uint16_t mlxsw_reg_pddr_partner_local_port_get(const char *buf);

uint8_t mlxsw_reg_pddr_partner_module_type_get(const char *buf);

uint32_t mlxsw_reg_pddr_partner_id_lsb_get(const char *buf);

uint8_t mlxsw_reg_pddr_tracer_sel_get(const char *buf);

void mlxsw_reg_pddr_tracer_sel_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_pddr_array512_auto_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_pddr_array512_auto_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_pddr_cause_as_detected_not_on_slot_get(const char *buf);

uint8_t mlxsw_reg_pddr_cause_high_ser_get(const char *buf);

uint8_t mlxsw_reg_pddr_cause_rs_rx_lane0_symbol_error_get(const char *buf);

uint8_t mlxsw_reg_pddr_cause_tx_lane_fifo_underrun_l0_get(const char *buf);

uint8_t mlxsw_reg_pddr_cause_deskew_fifo_overrun_get(const char *buf);

uint8_t mlxsw_reg_pddr_cause_fec_rx_sync_m_reached_max0_get(const char *buf);

uint32_t mlxsw_reg_pddr_symbol_error_counter_lo_get(const char *buf);

uint32_t mlxsw_reg_pddr_symbol_error_counter_hi_get(const char *buf);

uint32_t mlxsw_reg_pddr_uncorrectable_block_counter_lo_get(const char *buf);

uint32_t mlxsw_reg_pddr_uncorrectable_block_counter_hi_get(const char *buf);

uint8_t mlxsw_reg_pddr_link_fail_due_align_loss_get(const char *buf);

uint8_t mlxsw_reg_pddr_block_lock_mask_at_fail_port1_get(const char *buf);

uint8_t mlxsw_reg_pddr_block_lock_mask_at_fail_port0_get(const char *buf);

uint32_t mlxsw_reg_pddr_link_down_counter_get(const char *buf);

uint8_t mlxsw_reg_pddr_effective_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_pddr_effective_ber_magnitude_get(const char *buf);

uint16_t mlxsw_reg_pddr_raw_ber_coef_get(const char *buf);

uint8_t mlxsw_reg_pddr_raw_ber_magnitude_get(const char *buf);

/* pptt
 * ----
 *
 */
#define MLXSW_PPTT_ID 0x5036
#define MLXSW_PPTT_LEN 0x1c

uint8_t mlxsw_reg_pptt_e_get(const char *buf);

void mlxsw_reg_pptt_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pptt_p_get(const char *buf);

void mlxsw_reg_pptt_p_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pptt_p_c_get(const char *buf);

uint8_t mlxsw_reg_pptt_dm_ig_get(const char *buf);

void mlxsw_reg_pptt_dm_ig_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pptt_sw_get(const char *buf);

void mlxsw_reg_pptt_sw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pptt_sw_c_get(const char *buf);

uint8_t mlxsw_reg_pptt_local_port_get(const char *buf);

void mlxsw_reg_pptt_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pptt_pnat_get(const char *buf);

void mlxsw_reg_pptt_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pptt_lp_msb_get(const char *buf);

void mlxsw_reg_pptt_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pptt_lane_get(const char *buf);

void mlxsw_reg_pptt_lane_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pptt_port_type_get(const char *buf);

void mlxsw_reg_pptt_port_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pptt_ls_get(const char *buf);

uint8_t mlxsw_reg_pptt_le_get(const char *buf);

void mlxsw_reg_pptt_le_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_pptt_prbs_modes_cap_get(const char *buf);

uint8_t mlxsw_reg_pptt_prbs_mode_admin_get(const char *buf);

void mlxsw_reg_pptt_prbs_mode_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pptt_pat_ch_c_get(const char *buf);

uint8_t mlxsw_reg_pptt_pat_ch_get(const char *buf);

void mlxsw_reg_pptt_pat_ch_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pptt_vs_peer_db_get(const char *buf);

void mlxsw_reg_pptt_vs_peer_db_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pptt_modulation_get(const char *buf);

void mlxsw_reg_pptt_modulation_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pptt_lane_rate_cap_get(const char *buf);

uint8_t mlxsw_reg_pptt_prbs_fec_cap_get(const char *buf);

uint16_t mlxsw_reg_pptt_lane_rate_admin_get(const char *buf);

void mlxsw_reg_pptt_lane_rate_admin_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_pptt_prbs_fec_admin_get(const char *buf);

void mlxsw_reg_pptt_prbs_fec_admin_set(char *buf, uint8_t val);

/* pprt
 * ----
 *
 */
#define MLXSW_PPRT_ID 0x5037
#define MLXSW_PPRT_LEN 0x24

uint8_t mlxsw_reg_pprt_e_get(const char *buf);

void mlxsw_reg_pprt_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_s_get(const char *buf);

void mlxsw_reg_pprt_s_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_tun_ovr_get(const char *buf);

void mlxsw_reg_pprt_tun_ovr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_p_get(const char *buf);

void mlxsw_reg_pprt_p_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_p_c_get(const char *buf);

uint8_t mlxsw_reg_pprt_dm_ig_get(const char *buf);

void mlxsw_reg_pprt_dm_ig_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_sw_get(const char *buf);

void mlxsw_reg_pprt_sw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_sw_c_get(const char *buf);

uint8_t mlxsw_reg_pprt_local_port_get(const char *buf);

void mlxsw_reg_pprt_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_pnat_get(const char *buf);

void mlxsw_reg_pprt_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_lp_msb_get(const char *buf);

void mlxsw_reg_pprt_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_lane_get(const char *buf);

void mlxsw_reg_pprt_lane_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_port_type_get(const char *buf);

void mlxsw_reg_pprt_port_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_ls_get(const char *buf);

uint8_t mlxsw_reg_pprt_le_get(const char *buf);

void mlxsw_reg_pprt_le_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_pprt_prbs_modes_cap_get(const char *buf);

uint8_t mlxsw_reg_pprt_prbs_mode_admin_get(const char *buf);

void mlxsw_reg_pprt_prbs_mode_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_tuning_type_get(const char *buf);

void mlxsw_reg_pprt_tuning_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_pat_ch_c_get(const char *buf);

uint8_t mlxsw_reg_pprt_pat_ch_get(const char *buf);

void mlxsw_reg_pprt_pat_ch_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_peq_cap_get(const char *buf);

uint8_t mlxsw_reg_pprt_peq_dis_get(const char *buf);

void mlxsw_reg_pprt_peq_dis_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_modulation_get(const char *buf);

void mlxsw_reg_pprt_modulation_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pprt_lane_rate_cap_get(const char *buf);

uint8_t mlxsw_reg_pprt_auto_pol_rev_fix_cap_get(const char *buf);

uint8_t mlxsw_reg_pprt_prbs_hist_cap_get(const char *buf);

uint8_t mlxsw_reg_pprt_prbs_fec_cap_get(const char *buf);

uint16_t mlxsw_reg_pprt_lane_rate_oper_get(const char *buf);

void mlxsw_reg_pprt_lane_rate_oper_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_pprt_auto_pol_rev_fix_en_get(const char *buf);

void mlxsw_reg_pprt_auto_pol_rev_fix_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_prbs_hist_lane_sel_get(const char *buf);

void mlxsw_reg_pprt_prbs_hist_lane_sel_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_prbs_fec_admin_get(const char *buf);

void mlxsw_reg_pprt_prbs_fec_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_prbs_rx_tuning_status_get(const char *buf);

uint8_t mlxsw_reg_pprt_prbs_lock_status_get(const char *buf);

uint8_t mlxsw_reg_pprt_prbs_lock_status_ext_get(const char *buf);

uint16_t mlxsw_reg_pprt_supported_tuning_types_get(const char *buf);

uint32_t mlxsw_reg_pprt_tuning_params_get(const char *buf);

uint8_t mlxsw_reg_pprt_lt_tuning_support_get(const char *buf);

uint8_t mlxsw_reg_pprt_lt_tuning_admin_get(const char *buf);

void mlxsw_reg_pprt_lt_tuning_admin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprt_preset_mask_get(const char *buf);

void mlxsw_reg_pprt_preset_mask_set(char *buf, uint8_t val);

/* pmdr
 * ----
 *
 */
#define MLXSW_PMDR_ID 0x503c
#define MLXSW_PMDR_LEN 0x30

uint8_t mlxsw_reg_pmdr_status_get(const char *buf);

uint8_t mlxsw_reg_pmdr_version_get(const char *buf);

uint8_t mlxsw_reg_pmdr_local_port_get(const char *buf);

void mlxsw_reg_pmdr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmdr_pnat_get(const char *buf);

void mlxsw_reg_pmdr_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmdr_gb_valid_get(const char *buf);

uint8_t mlxsw_reg_pmdr_mcm_tile_valid_get(const char *buf);

uint8_t mlxsw_reg_pmdr_scc_valid_get(const char *buf);

uint8_t mlxsw_reg_pmdr_lp_msb_get(const char *buf);

void mlxsw_reg_pmdr_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmdr_pport_get(const char *buf);

uint8_t mlxsw_reg_pmdr_module_get(const char *buf);

uint8_t mlxsw_reg_pmdr_cluster_get(const char *buf);

uint8_t mlxsw_reg_pmdr_pport_msb_get(const char *buf);

uint8_t mlxsw_reg_pmdr_clp_4x_get(const char *buf);

uint8_t mlxsw_reg_pmdr_clp_1x_get(const char *buf);

uint8_t mlxsw_reg_pmdr_gb_dp_num_get(const char *buf);

uint8_t mlxsw_reg_pmdr_split_get(const char *buf);

uint8_t mlxsw_reg_pmdr_swid_get(const char *buf);

uint8_t mlxsw_reg_pmdr_module_lane_mask_get(const char *buf);

uint8_t mlxsw_reg_pmdr_ib_port_get(const char *buf);

uint8_t mlxsw_reg_pmdr_label_port_query_get(const char *buf);

uint8_t mlxsw_reg_pmdr_local_port_query_get(const char *buf);

uint8_t mlxsw_reg_pmdr_usr_sd_4x_tx_get(const char *buf);

uint8_t mlxsw_reg_pmdr_usr_sd_4x_rx_get(const char *buf);

uint8_t mlxsw_reg_pmdr_lp_query_msb_get(const char *buf);

void mlxsw_reg_pmdr_lp_query_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmdr_slot_index_get(const char *buf);

uint8_t mlxsw_reg_pmdr_tile_cluster_get(const char *buf);

uint8_t mlxsw_reg_pmdr_mcm_tile_num_get(const char *buf);

uint8_t mlxsw_reg_pmdr_tile_pport_get(const char *buf);

uint8_t mlxsw_reg_pmdr_gearbox_die_num_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl_num_get(const char *buf);

uint8_t mlxsw_reg_pmdr_lane7_physical_rx_get(const char *buf);

uint8_t mlxsw_reg_pmdr_lane6_physical_rx_get(const char *buf);

uint32_t mlxsw_reg_pmdr_lane5_physical_rx_get(const char *buf);

uint8_t mlxsw_reg_pmdr_lane4_physical_rx_get(const char *buf);

uint8_t mlxsw_reg_pmdr_lane3_physical_rx_get(const char *buf);

uint16_t mlxsw_reg_pmdr_lane2_physical_rx_get(const char *buf);

uint8_t mlxsw_reg_pmdr_lane1_physical_rx_get(const char *buf);

uint8_t mlxsw_reg_pmdr_lane0_physical_rx_get(const char *buf);

uint8_t mlxsw_reg_pmdr_pll_index_get(const char *buf);

uint8_t mlxsw_reg_pmdr_lane7_physical_tx_get(const char *buf);

uint8_t mlxsw_reg_pmdr_lane6_physical_tx_get(const char *buf);

uint32_t mlxsw_reg_pmdr_lane5_physical_tx_get(const char *buf);

uint8_t mlxsw_reg_pmdr_lane4_physical_tx_get(const char *buf);

uint8_t mlxsw_reg_pmdr_lane3_physical_tx_get(const char *buf);

uint16_t mlxsw_reg_pmdr_lane2_physical_tx_get(const char *buf);

uint8_t mlxsw_reg_pmdr_lane1_physical_tx_get(const char *buf);

uint8_t mlxsw_reg_pmdr_lane0_physical_tx_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl7_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl6_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl5_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl4_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl3_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl2_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl1_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl0_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl15_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl14_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl13_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl12_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl11_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl10_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl9_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl8_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl23_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl22_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl21_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl20_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl19_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl18_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl17_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl16_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl31_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl30_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl29_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl28_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl27_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl26_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl25_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_vl24_lane_map_get(const char *buf);

uint8_t mlxsw_reg_pmdr_physical_tx_cluster_get(const char *buf);

uint8_t mlxsw_reg_pmdr_physical_rx_cluster_get(const char *buf);

uint16_t mlxsw_reg_pmdr_scc_hs_lanes_get(const char *buf);

/* pphcr
 * -----
 *
 */
#define MLXSW_PPHCR_ID 0x503e
#define MLXSW_PPHCR_BIN_RANGE_BASE_LEN 0x10 /* base length, without records */
#define MLXSW_PPHCR_BIN_RANGE_REC_LEN 0x04 /* record length */
#define MLXSW_PPHCR_BIN_RANGE_REC_MAX_COUNT 16
#define MLXSW_PPHCR_LEN 0x50

uint8_t mlxsw_reg_pphcr_active_hist_type_get(const char *buf);

uint8_t mlxsw_reg_pphcr_local_port_get(const char *buf);

void mlxsw_reg_pphcr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pphcr_pnat_get(const char *buf);

void mlxsw_reg_pphcr_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pphcr_lp_msb_get(const char *buf);

void mlxsw_reg_pphcr_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pphcr_we_get(const char *buf);

uint8_t mlxsw_reg_pphcr_num_of_bins_get(const char *buf);

uint8_t mlxsw_reg_pphcr_hist_type_get(const char *buf);

void mlxsw_reg_pphcr_hist_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pphcr_hist_max_measurement_get(const char *buf);

uint8_t mlxsw_reg_pphcr_hist_min_measurement_get(const char *buf);

void mlxsw_reg_pphcr_bin_range_write_mask_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_pphcr_high_val_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_pphcr_high_val_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint8_t mlxsw_reg_pphcr_low_val_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_pphcr_low_val_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

/* sllm
 * ----
 *
 */
#define MLXSW_SLLM_ID 0x505b
#define MLXSW_SLLM_LEN 0x30

uint8_t mlxsw_reg_sllm_status_get(const char *buf);

uint8_t mlxsw_reg_sllm_version_get(const char *buf);

uint8_t mlxsw_reg_sllm_local_port_get(const char *buf);

void mlxsw_reg_sllm_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_pnat_get(const char *buf);

void mlxsw_reg_sllm_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_lp_msb_get(const char *buf);

void mlxsw_reg_sllm_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_lane_get(const char *buf);

void mlxsw_reg_sllm_lane_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_port_type_get(const char *buf);

void mlxsw_reg_sllm_port_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_c_db_get(const char *buf);

void mlxsw_reg_sllm_c_db_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_lm_active_get(const char *buf);

uint8_t mlxsw_reg_sllm_lm_was_active_get(const char *buf);

uint8_t mlxsw_reg_sllm_pib_gw_lock_get(const char *buf);

uint8_t mlxsw_reg_sllm_lm_en_get(const char *buf);

void mlxsw_reg_sllm_lm_en_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sllm_lm_clk90_fl_err_max_get(const char *buf);

void mlxsw_reg_sllm_lm_clk90_fl_err_max_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_sllm_lm_clk90_fl_err_acc_get(const char *buf);

void mlxsw_reg_sllm_lm_clk90_fl_err_acc_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_sllm_ib3_max_lm_90_tries_get(const char *buf);

void mlxsw_reg_sllm_ib3_max_lm_90_tries_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_sllm_lm_counter_up_get(const char *buf);

void mlxsw_reg_sllm_lm_counter_up_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_sllm_ib1_max_lm_90_tries_get(const char *buf);

void mlxsw_reg_sllm_ib1_max_lm_90_tries_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_sllm_lm_counter_mid_get(const char *buf);

void mlxsw_reg_sllm_lm_counter_mid_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_sllm_lm_counter_dn_get(const char *buf);

void mlxsw_reg_sllm_lm_counter_dn_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_sllm_enable_lm_get(const char *buf);

void mlxsw_reg_sllm_enable_lm_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_enable_phase_maintenance_get(const char *buf);

void mlxsw_reg_sllm_enable_phase_maintenance_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_enable_offset_maintenance_get(const char *buf);

void mlxsw_reg_sllm_enable_offset_maintenance_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_lm_catastrophic_bit_get(const char *buf);

uint8_t mlxsw_reg_sllm_lm_activation_counter_get(const char *buf);

uint8_t mlxsw_reg_sllm_lm_fixes_counter_get(const char *buf);

uint8_t mlxsw_reg_sllm_lane_under_maintenance_get(const char *buf);

uint8_t mlxsw_reg_sllm_optimal_phase_get(const char *buf);

uint8_t mlxsw_reg_sllm_link_tuning_error_get(const char *buf);

uint32_t mlxsw_reg_sllm_lane_correctable_errors_get(const char *buf);

uint8_t mlxsw_reg_sllm_ctle_peq_en_get(const char *buf);

void mlxsw_reg_sllm_ctle_peq_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_peq_tsense_en_get(const char *buf);

void mlxsw_reg_sllm_peq_tsense_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_peq_f1_adapt_skip_get(const char *buf);

void mlxsw_reg_sllm_peq_f1_adapt_skip_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_vref_peq_en_get(const char *buf);

void mlxsw_reg_sllm_vref_peq_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_dffe_peq_scout_skip_get(const char *buf);

void mlxsw_reg_sllm_dffe_peq_scout_skip_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_peq_train_mode_get(const char *buf);

void mlxsw_reg_sllm_peq_train_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_peq_vref_iters_get(const char *buf);

void mlxsw_reg_sllm_peq_vref_iters_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_peq_adc_vref_step_get(const char *buf);

void mlxsw_reg_sllm_peq_adc_vref_step_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_dffe_peq_en_get(const char *buf);

void mlxsw_reg_sllm_dffe_peq_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_peq_dffe_iters_get(const char *buf);

void mlxsw_reg_sllm_peq_dffe_iters_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sllm_peq_dffe_delay_get(const char *buf);

void mlxsw_reg_sllm_peq_dffe_delay_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_sllm_ctle_peq_cnt_get(const char *buf);

uint8_t mlxsw_reg_sllm_ber_mon_mantissa_get(const char *buf);

uint8_t mlxsw_reg_sllm_ber_mon_exp_get(const char *buf);

/* ppcgp
 * -----
 *
 */
#define MLXSW_PPCGP_ID 0x5071
#define MLXSW_PPCGP_LEN 0x10

uint8_t mlxsw_reg_ppcgp_grp_profile_get(const char *buf);

void mlxsw_reg_ppcgp_grp_profile_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_ppcgp_hi_get(const char *buf);

void mlxsw_reg_ppcgp_hi_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_ppcgp_lo_get(const char *buf);

void mlxsw_reg_ppcgp_lo_set(char *buf, uint32_t val);

/* pcsr
 * ----
 *
 */
#define MLXSW_PCSR_ID 0x5049
#define MLXSW_PCSR_LEN 0x30

uint8_t mlxsw_reg_pcsr_gs_get(const char *buf);

uint8_t mlxsw_reg_pcsr_offset_get(const char *buf);

void mlxsw_reg_pcsr_offset_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_pcsr_port_status_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

/* pmtu
 * ----
 *
 */
#define MLXSW_PMTU_ID 0x5003
#define MLXSW_PMTU_LEN 0x10

uint8_t mlxsw_reg_pmtu_local_port_get(const char *buf);

void mlxsw_reg_pmtu_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmtu_lp_msb_get(const char *buf);

void mlxsw_reg_pmtu_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmtu_i_e_get(const char *buf);

void mlxsw_reg_pmtu_i_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pmtu_itre_get(const char *buf);

void mlxsw_reg_pmtu_itre_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pmtu_max_mtu_get(const char *buf);

uint16_t mlxsw_reg_pmtu_admin_mtu_get(const char *buf);

void mlxsw_reg_pmtu_admin_mtu_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pmtu_oper_mtu_get(const char *buf);

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

/* pifr_v2
 * -------
 *
 */
#define MLXSW_PIFR_V2_ID 0x50e0
#define MLXSW_PIFR_V2_LEN 0x120

uint8_t mlxsw_reg_pifr_v2_table_id_get(const char *buf);

void mlxsw_reg_pifr_v2_table_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pifr_v2_local_port_get(const char *buf);

void mlxsw_reg_pifr_v2_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pifr_v2_lp_msb_get(const char *buf);

void mlxsw_reg_pifr_v2_lp_msb_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_pifr_v2_port_filter_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_pifr_v2_port_filter_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

void mlxsw_reg_pifr_v2_port_filter_update_en_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

uint16_t mlxsw_reg_pbsr_stat_buffer_watermark_get(const char *buf, unsigned short outer_index, unsigned short index);

uint16_t mlxsw_reg_pbsr_stat_buffer_used_buffer_get(const char *buf, unsigned short outer_index, unsigned short index);

uint16_t mlxsw_reg_pbsr_stat_shared_headroom_pool_watermark_get(const char *buf);

uint16_t mlxsw_reg_pbsr_stat_shared_headroom_pool_used_buffer_get(const char *buf);

/* pllp
 * ----
 *
 */
#define MLXSW_PLLP_ID 0x504a
#define MLXSW_PLLP_LEN 0x14

uint8_t mlxsw_reg_pllp_local_port_get(const char *buf);

void mlxsw_reg_pllp_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pllp_lp_msb_get(const char *buf);

void mlxsw_reg_pllp_lp_msb_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pllp_label_port_get(const char *buf);

uint8_t mlxsw_reg_pllp_ipil_stat_get(const char *buf);

uint8_t mlxsw_reg_pllp_split_stat_get(const char *buf);

uint8_t mlxsw_reg_pllp_ipil_num_get(const char *buf);

uint8_t mlxsw_reg_pllp_split_num_get(const char *buf);

uint8_t mlxsw_reg_pllp_max_ports_width_get(const char *buf);

uint8_t mlxsw_reg_pllp_slot_num_get(const char *buf);

uint8_t mlxsw_reg_pllp_maf_get(const char *buf);

uint8_t mlxsw_reg_pllp_is_fnm_get(const char *buf);

uint8_t mlxsw_reg_pllp_rmt_id_get(const char *buf);

uint8_t mlxsw_reg_pllp_conn_type_get(const char *buf);

uint8_t mlxsw_reg_pllp_protocol_get(const char *buf);

/* ppcr
 * ----
 *
 */
#define MLXSW_PPCR_ID 0x504c
#define MLXSW_PPCR_LEN 0x10

uint8_t mlxsw_reg_ppcr_local_port_get(const char *buf);

void mlxsw_reg_ppcr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcr_lp_msb_get(const char *buf);

void mlxsw_reg_ppcr_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcr_split_get(const char *buf);

void mlxsw_reg_ppcr_split_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcr_plane_get(const char *buf);

void mlxsw_reg_ppcr_plane_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcr_aggregated_port_get(const char *buf);

void mlxsw_reg_ppcr_aggregated_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcr_p_type_get(const char *buf);

void mlxsw_reg_ppcr_p_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppcr_num_of_planes_get(const char *buf);

void mlxsw_reg_ppcr_num_of_planes_set(char *buf, uint8_t val);

/* pldt
 * ----
 *
 */
#define MLXSW_PLDT_ID 0x504d
#define MLXSW_PLDT_LEN 0xc

uint8_t mlxsw_reg_pldt_local_port_get(const char *buf);

void mlxsw_reg_pldt_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pldt_lp_msb_get(const char *buf);

void mlxsw_reg_pldt_lp_msb_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pldt_link_up_delay_get(const char *buf);

void mlxsw_reg_pldt_link_up_delay_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pldt_link_down_delay_get(const char *buf);

void mlxsw_reg_pldt_link_down_delay_set(char *buf, uint16_t val);

/* pldc
 * ----
 *
 */
#define MLXSW_PLDC_ID 0x504e
#define MLXSW_PLDC_LEN 0x14

uint8_t mlxsw_reg_pldc_clr_get(const char *buf);

void mlxsw_reg_pldc_clr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pldc_local_port_get(const char *buf);

void mlxsw_reg_pldc_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pldc_lp_msb_get(const char *buf);

void mlxsw_reg_pldc_lp_msb_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pldc_link_up_delay_cnt_get(const char *buf);

uint16_t mlxsw_reg_pldc_link_down_delay_cnt_get(const char *buf);

uint16_t mlxsw_reg_pldc_timer_expired_cnt_get(const char *buf);

uint16_t mlxsw_reg_pldc_timer_cancel_cnt_get(const char *buf);

/* plibdb
 * ------
 *
 */
#define MLXSW_PLIBDB_ID 0x50e1
#define MLXSW_PLIBDB_LEN 0x10

uint8_t mlxsw_reg_plibdb_local_port_get(const char *buf);

void mlxsw_reg_plibdb_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_plibdb_lp_msb_get(const char *buf);

void mlxsw_reg_plibdb_lp_msb_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_plibdb_ib_port_1x_get(const char *buf);

uint16_t mlxsw_reg_plibdb_ib_port_2x_get(const char *buf);

uint16_t mlxsw_reg_plibdb_ib_port_4x_get(const char *buf);

/* pbgcr
 * -----
 *
 */
#define MLXSW_PBGCR_ID 0x50ea
#define MLXSW_PBGCR_LEN 0xc

uint8_t mlxsw_reg_pbgcr_per_ptb_get(const char *buf);

void mlxsw_reg_pbgcr_per_ptb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pbgcr_ptb_index_get(const char *buf);

void mlxsw_reg_pbgcr_ptb_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pbgcr_psbtt_get(const char *buf);

void mlxsw_reg_pbgcr_psbtt_set(char *buf, uint8_t val);

void mlxsw_reg_pbgcr_user_val_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pbgcr_dib_user_value_get(const char *buf);

/* ppir
 * ----
 *
 */
#define MLXSW_PPIR_ID 0x50eb
#define MLXSW_PPIR_LEN 0x8

uint8_t mlxsw_reg_ppir_local_port_get(const char *buf);

void mlxsw_reg_ppir_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppir_lp_msb_get(const char *buf);

void mlxsw_reg_ppir_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppir_lcnf_get(const char *buf);

uint8_t mlxsw_reg_ppir_peer_p_type_get(const char *buf);

uint8_t mlxsw_reg_ppir_peer_num_of_planes_get(const char *buf);

/* phbr
 * ----
 *
 */
#define MLXSW_PHBR_ID 0x5034
#define MLXSW_PHBR_LEN 0x1c

uint8_t mlxsw_reg_phbr_local_port_get(const char *buf);

void mlxsw_reg_phbr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_phbr_lp_msb_get(const char *buf);

void mlxsw_reg_phbr_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_phbr_hist_id_get(const char *buf);

void mlxsw_reg_phbr_hist_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_phbr_mode_get(const char *buf);

void mlxsw_reg_phbr_mode_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_phbr_hist_type_get(const char *buf);

void mlxsw_reg_phbr_hist_type_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_phbr_first_bin_thr_get(const char *buf);

void mlxsw_reg_phbr_first_bin_thr_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_phbr_bin_size_get(const char *buf);

void mlxsw_reg_phbr_bin_size_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_phbr_hist_repeat_num_get(const char *buf);

void mlxsw_reg_phbr_hist_repeat_num_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_phbr_sample_time_get(const char *buf);

void mlxsw_reg_phbr_sample_time_set(char *buf, uint8_t val);

/* phrr
 * ----
 *
 */
#define MLXSW_PHRR_ID 0x5035
#define MLXSW_PHRR_LEN 0x68

uint8_t mlxsw_reg_phrr_clr_get(const char *buf);

void mlxsw_reg_phrr_clr_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_phrr_local_port_get(const char *buf);

void mlxsw_reg_phrr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_phrr_lp_msb_get(const char *buf);

void mlxsw_reg_phrr_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_phrr_hist_id_get(const char *buf);

void mlxsw_reg_phrr_hist_id_set(char *buf, uint8_t val);

uint64_t mlxsw_reg_phrr_bin_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_phrr_min_watermark_get(const char *buf);

uint32_t mlxsw_reg_phrr_max_watermark_get(const char *buf);

/* pbwc
 * ----
 *
 */
#define MLXSW_PBWC_ID 0x50e7
#define MLXSW_PBWC_LEN 0x8

uint8_t mlxsw_reg_pbwc_log_time_interval_get(const char *buf);

void mlxsw_reg_pbwc_log_time_interval_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pbwc_alpha_factor_get(const char *buf);

void mlxsw_reg_pbwc_alpha_factor_set(char *buf, uint8_t val);

/* pbwr
 * ----
 *
 */
#define MLXSW_PBWR_ID 0x50e8
#define MLXSW_PBWR_LEN 0x498

uint32_t mlxsw_reg_pbwr_local_port_bitmap_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_pbwr_local_port_bitmap_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

void mlxsw_reg_pbwr_dir_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_pbwr_bw_record_get(const char *buf, unsigned short outer_index, unsigned short index);

/* sbgcr
 * -----
 *
 */
#define MLXSW_SBGCR_ID 0xb000
#define MLXSW_SBGCR_LEN 0x8

uint8_t mlxsw_reg_sbgcr_cong_fp_get(const char *buf);

void mlxsw_reg_sbgcr_cong_fp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbgcr_tele_entity_get(const char *buf);

void mlxsw_reg_sbgcr_tele_entity_set(char *buf, uint8_t val);

/* sbsrd
 * -----
 *
 */
#define MLXSW_SBSRD_ID 0xb015
#define MLXSW_SBSRD_SHARED_BUFFER_STATUS_BASE_LEN 0x10 /* base length, without records */
#define MLXSW_SBSRD_EXT_OCCUPANCY_STATUS_BASE_LEN 0x410 /* base length, without records */
#define MLXSW_SBSRD_SHARED_BUFFER_STATUS_REC_LEN 0x08 /* record length */
#define MLXSW_SBSRD_SHARED_BUFFER_STATUS_REC_MAX_COUNT 128
#define MLXSW_SBSRD_LEN 0x450

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

uint32_t mlxsw_reg_sbsrd_buff_occupancy_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_sbsrd_max_buff_occupancy_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_sbsrd_ext_buff_occupancy_get(const char *buf, unsigned short outer_index, unsigned short index);

/* sbhbr_v2
 * --------
 *
 */
#define MLXSW_SBHBR_V2_ID 0xb011
#define MLXSW_SBHBR_V2_LEN 0x20

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

/* sbhrr_v2
 * --------
 *
 */
#define MLXSW_SBHRR_V2_ID 0xb012
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

uint64_t mlxsw_reg_sbhrr_v2_bin_get(const char *buf, unsigned short outer_index, unsigned short index);

/* sbctr
 * -----
 *
 */
#define MLXSW_SBCTR_ID 0xb00d
#define MLXSW_SBCTR_LEN 0x18

uint8_t mlxsw_reg_sbctr_ievent_get(const char *buf);

void mlxsw_reg_sbctr_ievent_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbctr_local_port_get(const char *buf);

void mlxsw_reg_sbctr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbctr_lp_msb_get(const char *buf);

void mlxsw_reg_sbctr_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbctr_dir_ing_get(const char *buf);

void mlxsw_reg_sbctr_dir_ing_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbctr_fp_get(const char *buf);

uint8_t mlxsw_reg_sbctr_entity_get(const char *buf);

uint32_t mlxsw_reg_sbctr_tclass_vector_high_get(const char *buf);

uint32_t mlxsw_reg_sbctr_tclass_vector_low_get(const char *buf);

/* sbhpc
 * -----
 *
 */
#define MLXSW_SBHPC_ID 0xb013
#define MLXSW_SBHPC_LEN 0x24

uint32_t mlxsw_reg_sbhpc_max_buff_get(const char *buf);

void mlxsw_reg_sbhpc_max_buff_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_sbhpc_buff_occupancy_get(const char *buf);

/* sbsnt
 * -----
 *
 */
#define MLXSW_SBSNT_ID 0xb020
#define MLXSW_SBSNT_LEN 0x4

uint8_t mlxsw_reg_sbsnt_take_get(const char *buf);

void mlxsw_reg_sbsnt_take_set(char *buf, uint8_t val);

/* sbsns
 * -----
 *
 */
#define MLXSW_SBSNS_ID 0xb021
#define MLXSW_SBSNS_LEN 0x18

uint8_t mlxsw_reg_sbsns_status_get(const char *buf);

uint8_t mlxsw_reg_sbsns_trigger_id_get(const char *buf);

uint32_t mlxsw_reg_sbsns_trigger_parameters_get(const char *buf);

uint8_t mlxsw_reg_sbsns_time_high_get(const char *buf);

uint32_t mlxsw_reg_sbsns_time_low_get(const char *buf);

/* sbsnte
 * ------
 *
 */
#define MLXSW_SBSNTE_ID 0xb022
#define MLXSW_SBSNTE_LEN 0x10

uint8_t mlxsw_reg_sbsnte_local_port_get(const char *buf);

void mlxsw_reg_sbsnte_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbsnte_lp_msb_get(const char *buf);

void mlxsw_reg_sbsnte_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_sbsnte_type_get(const char *buf);

void mlxsw_reg_sbsnte_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_sbsnte_tclass_en_high_get(const char *buf);

void mlxsw_reg_sbsnte_tclass_en_high_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_sbsnte_tclass_en_low_get(const char *buf);

void mlxsw_reg_sbsnte_tclass_en_low_set(char *buf, uint32_t val);

/* pgcr
 * ----
 *
 */
#define MLXSW_PGCR_ID 0x3001
#define MLXSW_PGCR_LEN 0x20

uint8_t mlxsw_reg_pgcr_update_prune_get(const char *buf);

void mlxsw_reg_pgcr_update_prune_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pgcr_pbs_table_size_get(const char *buf);

void mlxsw_reg_pgcr_pbs_table_size_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pgcr_max_eacl_get(const char *buf);

uint16_t mlxsw_reg_pgcr_max_iacl_get(const char *buf);

uint16_t mlxsw_reg_pgcr_atcam_ignore_prune_vector_get(const char *buf);

void mlxsw_reg_pgcr_atcam_ignore_prune_vector_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_pgcr_default_action_pointer_base_get(const char *buf);

void mlxsw_reg_pgcr_default_action_pointer_base_set(char *buf, uint32_t val);

/* ppbt
 * ----
 *
 */
#define MLXSW_PPBT_ID 0x3002
#define MLXSW_PPBT_LEN 0x14

uint8_t mlxsw_reg_ppbt_e_get(const char *buf);

void mlxsw_reg_ppbt_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppbt_op_get(const char *buf);

void mlxsw_reg_ppbt_op_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppbt_tport_get(const char *buf);

void mlxsw_reg_ppbt_tport_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppbt_local_port_get(const char *buf);

void mlxsw_reg_ppbt_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppbt_lp_msb_get(const char *buf);

void mlxsw_reg_ppbt_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppbt_g_get(const char *buf);

void mlxsw_reg_ppbt_g_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ppbt_acl_id_group_id_get(const char *buf);

void mlxsw_reg_ppbt_acl_id_group_id_set(char *buf, uint16_t val);

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

/* pvgt
 * ----
 *
 */
#define MLXSW_PVGT_ID 0x3009
#define MLXSW_PVGT_LEN 0x8

uint8_t mlxsw_reg_pvgt_swid_get(const char *buf);

void mlxsw_reg_pvgt_swid_set(char *buf, uint8_t val);

void mlxsw_reg_pvgt_op_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pvgt_vid_get(const char *buf);

void mlxsw_reg_pvgt_vid_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pvgt_vlan_group_get(const char *buf);

void mlxsw_reg_pvgt_vlan_group_set(char *buf, uint16_t val);

/* pvbt
 * ----
 *
 */
#define MLXSW_PVBT_ID 0x3003
#define MLXSW_PVBT_LEN 0x14

uint8_t mlxsw_reg_pvbt_swid_get(const char *buf);

void mlxsw_reg_pvbt_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pvbt_e_get(const char *buf);

void mlxsw_reg_pvbt_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pvbt_op_get(const char *buf);

void mlxsw_reg_pvbt_op_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pvbt_vlan_group_get(const char *buf);

void mlxsw_reg_pvbt_vlan_group_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_pvbt_g_get(const char *buf);

void mlxsw_reg_pvbt_g_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pvbt_acl_id_group_id_get(const char *buf);

void mlxsw_reg_pvbt_acl_id_group_id_set(char *buf, uint16_t val);

/* pemrbt
 * ------
 *
 */
#define MLXSW_PEMRBT_ID 0x3014
#define MLXSW_PEMRBT_LEN 0x14

uint8_t mlxsw_reg_pemrbt_op_get(const char *buf);

void mlxsw_reg_pemrbt_op_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pemrbt_protocol_get(const char *buf);

void mlxsw_reg_pemrbt_protocol_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pemrbt_group_id_get(const char *buf);

void mlxsw_reg_pemrbt_group_id_set(char *buf, uint16_t val);

/* perb
 * ----
 *
 */
#define MLXSW_PERB_ID 0x3040
#define MLXSW_PERB_LEN 0xe4

uint8_t mlxsw_reg_perb_pipe_stage_get(const char *buf);

void mlxsw_reg_perb_pipe_stage_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_rule_profile_index_get(const char *buf);

void mlxsw_reg_perb_rule_profile_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_op_get(const char *buf);

void mlxsw_reg_perb_op_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_perb_group_id_get(const char *buf);

void mlxsw_reg_perb_group_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_l2_flood_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_l2_flood_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_l2_mc_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_l2_mc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_l3_mc_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_l3_mc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_l2_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_l2_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_inner_l2_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_inner_l2_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_l3_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_l3_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_inner_l3_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_inner_l3_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_ip_frag_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_ip_frag_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_inner_ip_frag_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_inner_ip_frag_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_l4_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_l4_type_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_inner_l4_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_inner_l4_type_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_tunnel_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_tunnel_type_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_decap_tq_command_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_decap_tq_command_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_tq_command_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_tq_command_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_fpp_index_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_fpp_index_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_perb_perb_classifier_iport_base_classifier_inner_fpp_index_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_base_classifier_inner_fpp_index_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_perb_perb_classifier_iport_ingress_local_port_list_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_perb_perb_classifier_iport_ingress_local_port_list_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_perb_perb_classifier_iport_tunnel_port_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_iport_tunnel_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_l2_flood_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_l2_flood_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_l2_mc_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_l2_mc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_l3_mc_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_l3_mc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_l2_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_l2_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_inner_l2_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_inner_l2_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_l3_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_l3_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_inner_l3_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_inner_l3_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_ip_frag_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_ip_frag_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_inner_ip_frag_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_inner_ip_frag_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_l4_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_l4_type_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_inner_l4_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_inner_l4_type_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_tunnel_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_tunnel_type_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_decap_tq_command_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_decap_tq_command_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_tq_command_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_tq_command_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_fpp_index_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_fpp_index_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_perb_perb_classifier_irif_base_classifier_inner_fpp_index_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_base_classifier_inner_fpp_index_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_perb_perb_classifier_irif_rb_irif_group_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_irif_rb_irif_group_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_l2_flood_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_l2_flood_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_l2_mc_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_l2_mc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_l3_mc_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_l3_mc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_l2_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_l2_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_inner_l2_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_inner_l2_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_l3_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_l3_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_inner_l3_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_inner_l3_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_ip_frag_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_ip_frag_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_inner_ip_frag_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_inner_ip_frag_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_l4_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_l4_type_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_inner_l4_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_inner_l4_type_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_tunnel_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_tunnel_type_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_decap_tq_command_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_decap_tq_command_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_tq_command_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_tq_command_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_fpp_index_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_fpp_index_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_perb_perb_classifier_erif_base_classifier_inner_fpp_index_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_base_classifier_inner_fpp_index_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_perb_perb_classifier_erif_rb_erif_group_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_erif_rb_erif_group_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_l2_flood_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_l2_flood_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_l2_mc_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_l2_mc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_l3_mc_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_l3_mc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_l2_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_l2_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_inner_l2_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_inner_l2_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_l3_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_l3_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_inner_l3_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_inner_l3_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_ip_frag_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_ip_frag_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_inner_ip_frag_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_inner_ip_frag_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_l4_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_l4_type_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_inner_l4_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_inner_l4_type_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_tunnel_type_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_tunnel_type_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_decap_tq_command_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_decap_tq_command_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_tq_command_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_tq_command_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_fpp_index_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_fpp_index_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_perb_perb_classifier_eport_base_classifier_inner_fpp_index_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_base_classifier_inner_fpp_index_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_perb_perb_classifier_eport_rb_eport_group_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_rb_eport_group_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_perb_perb_classifier_eport_tunnel_port_get(const char *buf);

void mlxsw_reg_perb_perb_classifier_eport_tunnel_port_set(char *buf, uint8_t val);

/* perbrg
 * ------
 *
 */
#define MLXSW_PERBRG_ID 0x3041
#define MLXSW_PERBRG_LEN 0x10

uint16_t mlxsw_reg_perbrg_rif_get(const char *buf);

void mlxsw_reg_perbrg_rif_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_perbrg_dir_get(const char *buf);

void mlxsw_reg_perbrg_dir_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perbrg_rb_rif_group_get(const char *buf);

void mlxsw_reg_perbrg_rb_rif_group_set(char *buf, uint8_t val);

/* perbeg
 * ------
 *
 */
#define MLXSW_PERBEG_ID 0x3042
#define MLXSW_PERBEG_LEN 0x10

uint8_t mlxsw_reg_perbeg_egress_local_port_get(const char *buf);

void mlxsw_reg_perbeg_egress_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perbeg_egress_lp_msb_get(const char *buf);

void mlxsw_reg_perbeg_egress_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_perbeg_rb_eport_group_get(const char *buf);

void mlxsw_reg_perbeg_rb_eport_group_set(char *buf, uint8_t val);

/* perla
 * -----
 *
 */
#define MLXSW_PERLA_ID 0x3036
#define MLXSW_PERLA_LEN 0x8

uint16_t mlxsw_reg_perla_hw_region_get(const char *buf);

void mlxsw_reg_perla_hw_region_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_perla_lookup_region_id_get(const char *buf);

void mlxsw_reg_perla_lookup_region_id_set(char *buf, uint16_t val);

/* perar
 * -----
 *
 */
#define MLXSW_PERAR_ID 0x3026
#define MLXSW_PERAR_LEN 0x8

uint16_t mlxsw_reg_perar_region_id_get(const char *buf);

void mlxsw_reg_perar_region_id_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_perar_hw_region_get(const char *buf);

void mlxsw_reg_perar_hw_region_set(char *buf, uint16_t val);

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

uint32_t mlxsw_reg_ptcead_activity_vector_get(const char *buf, unsigned short outer_index, unsigned short index);

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

uint32_t mlxsw_reg_pefaad_index_dump_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_pefaad_index_dump_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* pprr
 * ----
 *
 */
#define MLXSW_PPRR_ID 0x3008
#define MLXSW_PPRR_LEN 0x14

uint8_t mlxsw_reg_pprr_ipv4_get(const char *buf);

void mlxsw_reg_pprr_ipv4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprr_ipv6_get(const char *buf);

void mlxsw_reg_pprr_ipv6_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprr_src_get(const char *buf);

void mlxsw_reg_pprr_src_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprr_dst_get(const char *buf);

void mlxsw_reg_pprr_dst_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprr_tcp_get(const char *buf);

void mlxsw_reg_pprr_tcp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprr_udp_get(const char *buf);

void mlxsw_reg_pprr_udp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprr_ignore_l3_get(const char *buf);

void mlxsw_reg_pprr_ignore_l3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprr_ignore_l4_get(const char *buf);

void mlxsw_reg_pprr_ignore_l4_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprr_outer_inner_get(const char *buf);

void mlxsw_reg_pprr_outer_inner_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprr_ip_length_get(const char *buf);

void mlxsw_reg_pprr_ip_length_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprr_register_index_get(const char *buf);

void mlxsw_reg_pprr_register_index_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_pprr_port_range_min_get(const char *buf);

void mlxsw_reg_pprr_port_range_min_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_pprr_port_range_max_get(const char *buf);

void mlxsw_reg_pprr_port_range_max_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_pprr_comp_type_get(const char *buf);

void mlxsw_reg_pprr_comp_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_pprr_cbset_get(const char *buf);

void mlxsw_reg_pprr_cbset_set(char *buf, uint8_t val);

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

uint8_t mlxsw_reg_ppbs_uvid_get(const char *buf);

void mlxsw_reg_ppbs_uvid_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ppbs_vid_get(const char *buf);

void mlxsw_reg_ppbs_vid_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ppbs_lag_id_get(const char *buf);

void mlxsw_reg_ppbs_lag_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_ppbs_ppbs_multicast_v_fid_get(const char *buf);

void mlxsw_reg_ppbs_ppbs_multicast_v_fid_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ppbs_ppbs_multicast_pgi_get(const char *buf);

void mlxsw_reg_ppbs_ppbs_multicast_pgi_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ppbs_ppbs_multicast_fid_get(const char *buf);

void mlxsw_reg_ppbs_ppbs_multicast_fid_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ppbs_ppbs_multicast_mid_get(const char *buf);

void mlxsw_reg_ppbs_ppbs_multicast_mid_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_ppbs_udip_get(const char *buf);

void mlxsw_reg_ppbs_udip_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_ppbs_protocol_get(const char *buf);

void mlxsw_reg_ppbs_protocol_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ppbs_gen_enc_get(const char *buf);

void mlxsw_reg_ppbs_gen_enc_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ppbs_tunnel_port_lbf_bitmap_get(const char *buf);

void mlxsw_reg_ppbs_tunnel_port_lbf_bitmap_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ppbs_ecmp_size_get(const char *buf);

void mlxsw_reg_ppbs_ecmp_size_set(char *buf, uint16_t val);

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

uint16_t mlxsw_reg_ppbs_multicast_tunnel_lbf_tunnel_port_bitmap_get(const char *buf);

void mlxsw_reg_ppbs_multicast_tunnel_lbf_tunnel_port_bitmap_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_ppbs_multicast_tunnel_ecmp_size_get(const char *buf);

void mlxsw_reg_ppbs_multicast_tunnel_ecmp_size_set(char *buf, uint16_t val);

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

uint32_t mlxsw_reg_peapbm_key_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_peapbm_key_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_peapbm_key_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_peapbm_key_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

/* qcap
 * ----
 *
 */
#define MLXSW_QCAP_ID 0x4001
#define MLXSW_QCAP_LEN 0x14

uint8_t mlxsw_reg_qcap_max_policers_per_port_get(const char *buf);

uint8_t mlxsw_reg_qcap_max_policers_global_get(const char *buf);

uint8_t mlxsw_reg_qcap_max_policers_cpu_get(const char *buf);

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

/* qtct
 * ----
 *
 */
#define MLXSW_QTCT_ID 0x400a
#define MLXSW_QTCT_LEN 0x8

uint8_t mlxsw_reg_qtct_local_port_get(const char *buf);

void mlxsw_reg_qtct_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtct_lp_msb_get(const char *buf);

void mlxsw_reg_qtct_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtct_switch_prio_get(const char *buf);

void mlxsw_reg_qtct_switch_prio_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtct_tclass_get(const char *buf);

void mlxsw_reg_qtct_tclass_set(char *buf, uint8_t val);

/* qtctm
 * -----
 *
 */
#define MLXSW_QTCTM_ID 0x401a
#define MLXSW_QTCTM_LEN 0x8

uint8_t mlxsw_reg_qtctm_local_port_get(const char *buf);

void mlxsw_reg_qtctm_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtctm_lp_msb_get(const char *buf);

void mlxsw_reg_qtctm_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtctm_mc_get(const char *buf);

void mlxsw_reg_qtctm_mc_set(char *buf, uint8_t val);

/* qsptc
 * -----
 *
 */
#define MLXSW_QSPTC_ID 0x4009
#define MLXSW_QSPTC_LEN 0x8

uint8_t mlxsw_reg_qsptc_local_iport_get(const char *buf);

void mlxsw_reg_qsptc_local_iport_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qsptc_local_eport_get(const char *buf);

void mlxsw_reg_qsptc_local_eport_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qsptc_itclass_get(const char *buf);

void mlxsw_reg_qsptc_itclass_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qsptc_tclass_get(const char *buf);

void mlxsw_reg_qsptc_tclass_set(char *buf, uint8_t val);

/* qstct
 * -----
 *
 */
#define MLXSW_QSTCT_ID 0x400b
#define MLXSW_QSTCT_LEN 0x10

uint8_t mlxsw_reg_qstct_swid_get(const char *buf);

void mlxsw_reg_qstct_swid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qstct_switch_prio_get(const char *buf);

void mlxsw_reg_qstct_switch_prio_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qstct_utclass_get(const char *buf);

void mlxsw_reg_qstct_utclass_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qstct_mtclass_get(const char *buf);

void mlxsw_reg_qstct_mtclass_set(char *buf, uint8_t val);

/* qspip
 * -----
 *
 */
#define MLXSW_QSPIP_ID 0x400e
#define MLXSW_QSPIP_LEN 0x8

uint8_t mlxsw_reg_qspip_switch_prio_get(const char *buf);

void mlxsw_reg_qspip_switch_prio_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qspip_ieee_prio_get(const char *buf);

void mlxsw_reg_qspip_ieee_prio_set(char *buf, uint8_t val);

/* qspcp
 * -----
 *
 */
#define MLXSW_QSPCP_ID 0x401e
#define MLXSW_QSPCP_LEN 0xc

uint8_t mlxsw_reg_qspcp_local_port_get(const char *buf);

void mlxsw_reg_qspcp_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qspcp_lp_msb_get(const char *buf);

void mlxsw_reg_qspcp_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qspcp_switch_prio_get(const char *buf);

void mlxsw_reg_qspcp_switch_prio_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qspcp_rx_counting_prio_get(const char *buf);

void mlxsw_reg_qspcp_rx_counting_prio_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qspcp_tx_counting_prio_get(const char *buf);

void mlxsw_reg_qspcp_tx_counting_prio_set(char *buf, uint8_t val);

/* qtttl
 * -----
 *
 */
#define MLXSW_QTTTL_ID 0x4040
#define MLXSW_QTTTL_LEN 0xc

uint8_t mlxsw_reg_qtttl_tqos_profile_get(const char *buf);

void mlxsw_reg_qtttl_tqos_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtttl_decap_ttl_get(const char *buf);

void mlxsw_reg_qtttl_decap_ttl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtttl_enc_ttlc_get(const char *buf);

void mlxsw_reg_qtttl_enc_ttlc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtttl_enc_ttl_uc_get(const char *buf);

void mlxsw_reg_qtttl_enc_ttl_uc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtttl_enc_ttl_mc_get(const char *buf);

void mlxsw_reg_qtttl_enc_ttl_mc_set(char *buf, uint8_t val);

/* qtqcr
 * -----
 *
 */
#define MLXSW_QTQCR_ID 0x4041
#define MLXSW_QTQCR_LEN 0xc

uint8_t mlxsw_reg_qtqcr_tqos_profile_get(const char *buf);

void mlxsw_reg_qtqcr_tqos_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqcr_enc_set_dscp_get(const char *buf);

void mlxsw_reg_qtqcr_enc_set_dscp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqcr_enc_set_sp_get(const char *buf);

void mlxsw_reg_qtqcr_enc_set_sp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqcr_enc_dscp_rw_get(const char *buf);

void mlxsw_reg_qtqcr_enc_dscp_rw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqcr_enc_pcp_rw_get(const char *buf);

void mlxsw_reg_qtqcr_enc_pcp_rw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqcr_dec_set_dscp_get(const char *buf);

void mlxsw_reg_qtqcr_dec_set_dscp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqcr_dec_set_sp_get(const char *buf);

void mlxsw_reg_qtqcr_dec_set_sp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqcr_dec_set_pcp_get(const char *buf);

void mlxsw_reg_qtqcr_dec_set_pcp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqcr_dec_dscp_rw_get(const char *buf);

void mlxsw_reg_qtqcr_dec_dscp_rw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqcr_dec_pcp_rw_get(const char *buf);

void mlxsw_reg_qtqcr_dec_pcp_rw_set(char *buf, uint8_t val);

/* qtqdr
 * -----
 *
 */
#define MLXSW_QTQDR_ID 0x4042
#define MLXSW_QTQDR_LEN 0x8

uint8_t mlxsw_reg_qtqdr_local_port_get(const char *buf);

void mlxsw_reg_qtqdr_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqdr_lp_msb_get(const char *buf);

void mlxsw_reg_qtqdr_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqdr_tqos_profile_get(const char *buf);

void mlxsw_reg_qtqdr_tqos_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqdr_color_get(const char *buf);

void mlxsw_reg_qtqdr_color_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqdr_switch_prio_get(const char *buf);

void mlxsw_reg_qtqdr_switch_prio_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqdr_exp_get(const char *buf);

void mlxsw_reg_qtqdr_exp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtqdr_dscp_get(const char *buf);

void mlxsw_reg_qtqdr_dscp_set(char *buf, uint8_t val);

/* qteem
 * -----
 *
 */
#define MLXSW_QTEEM_ID 0x4043
#define MLXSW_QTEEM_LEN 0xc

uint8_t mlxsw_reg_qteem_tqos_profile_get(const char *buf);

void mlxsw_reg_qteem_tqos_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qteem_overlay_ecn_get(const char *buf);

void mlxsw_reg_qteem_overlay_ecn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qteem_underlay_ecn_get(const char *buf);

void mlxsw_reg_qteem_underlay_ecn_set(char *buf, uint8_t val);

/* qtdem
 * -----
 *
 */
#define MLXSW_QTDEM_ID 0x4044
#define MLXSW_QTDEM_LEN 0xc

uint8_t mlxsw_reg_qtdem_tqos_profile_get(const char *buf);

void mlxsw_reg_qtdem_tqos_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtdem_underlay_ecn_get(const char *buf);

void mlxsw_reg_qtdem_underlay_ecn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtdem_overlay_ecn_get(const char *buf);

void mlxsw_reg_qtdem_overlay_ecn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtdem_eip_ecn_get(const char *buf);

void mlxsw_reg_qtdem_eip_ecn_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtdem_trap_en_get(const char *buf);

void mlxsw_reg_qtdem_trap_en_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_qtdem_trap_id_get(const char *buf);

void mlxsw_reg_qtdem_trap_id_set(char *buf, uint16_t val);

/* qpdpc
 * -----
 *
 */
#define MLXSW_QPDPC_ID 0x4017
#define MLXSW_QPDPC_LEN 0x8

uint8_t mlxsw_reg_qpdpc_tport_get(const char *buf);

void mlxsw_reg_qpdpc_tport_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qpdpc_local_port_get(const char *buf);

void mlxsw_reg_qpdpc_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qpdpc_lp_msb_get(const char *buf);

void mlxsw_reg_qpdpc_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qpdpc_dei_get(const char *buf);

void mlxsw_reg_qpdpc_dei_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qpdpc_pcp_get(const char *buf);

void mlxsw_reg_qpdpc_pcp_set(char *buf, uint8_t val);

/* qsll
 * ----
 *
 */
#define MLXSW_QSLL_ID 0x4015
#define MLXSW_QSLL_LEN 0x8

uint8_t mlxsw_reg_qsll_sll_time_get(const char *buf);

void mlxsw_reg_qsll_sll_time_set(char *buf, uint8_t val);

/* qptg
 * ----
 *
 */
#define MLXSW_QPTG_ID 0x4050
#define MLXSW_QPTG_LEN 0x8

uint8_t mlxsw_reg_qptg_local_port_get(const char *buf);

void mlxsw_reg_qptg_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qptg_lp_msb_get(const char *buf);

void mlxsw_reg_qptg_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qptg_rx_group_get(const char *buf);

void mlxsw_reg_qptg_rx_group_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qptg_tx_group_get(const char *buf);

void mlxsw_reg_qptg_tx_group_set(char *buf, uint8_t val);

/* qtgtc
 * -----
 *
 */
#define MLXSW_QTGTC_ID 0x4051
#define MLXSW_QTGTC_LEN 0x10

uint8_t mlxsw_reg_qtgtc_rx_group_get(const char *buf);

void mlxsw_reg_qtgtc_rx_group_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtgtc_tx_group_get(const char *buf);

void mlxsw_reg_qtgtc_tx_group_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtgtc_switch_prio_get(const char *buf);

void mlxsw_reg_qtgtc_switch_prio_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_qtgtc_tclass_get(const char *buf);

void mlxsw_reg_qtgtc_tclass_set(char *buf, uint8_t val);

/* cpqe
 * ----
 *
 */
#define MLXSW_CPQE_ID 0x2806
#define MLXSW_CPQE_LEN 0x14

uint8_t mlxsw_reg_cpqe_local_port_get(const char *buf);

void mlxsw_reg_cpqe_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cpqe_lp_msb_get(const char *buf);

void mlxsw_reg_cpqe_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cpqe_marking_percent_get(const char *buf);

void mlxsw_reg_cpqe_marking_percent_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cpqe_en_get(const char *buf);

void mlxsw_reg_cpqe_en_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_cpqe_rate_get(const char *buf);

void mlxsw_reg_cpqe_rate_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_cpqe_bs_get(const char *buf);

void mlxsw_reg_cpqe_bs_set(char *buf, uint8_t val);

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

uint32_t mlxsw_reg_cedr_detection_table_get(const char *buf, unsigned short outer_index, unsigned short index);

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

uint32_t mlxsw_reg_ceer_sip_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_ceer_dip_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_ceer_vni_get(const char *buf);

void mlxsw_reg_ceer_inner_dmac_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_ceer_inner_smac_memcpy_from(const char *buf, char *dst);

uint8_t mlxsw_reg_ceer_inner_l3_type_get(const char *buf);

uint8_t mlxsw_reg_ceer_inner_dscp_get(const char *buf);

uint8_t mlxsw_reg_ceer_inner_ecn_get(const char *buf);

uint8_t mlxsw_reg_ceer_inner_ttl_get(const char *buf);

uint8_t mlxsw_reg_ceer_inner_dont_frag_get(const char *buf);

uint32_t mlxsw_reg_ceer_inner_sip_get(const char *buf, unsigned short outer_index, unsigned short index);

uint32_t mlxsw_reg_ceer_inner_dip_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_ceer_mpls_bos_get(const char *buf);

uint8_t mlxsw_reg_ceer_mpls_exp_get(const char *buf);

uint8_t mlxsw_reg_ceer_mpls_lb0_v_get(const char *buf);

uint32_t mlxsw_reg_ceer_mpls_label0_label_id_get(const char *buf);

uint8_t mlxsw_reg_ceer_mpls_label0_ttl_get(const char *buf);

uint8_t mlxsw_reg_ceer_mpls_lb1_v_get(const char *buf);

uint32_t mlxsw_reg_ceer_mpls_label1_label_id_get(const char *buf);

uint8_t mlxsw_reg_ceer_mpls_label1_ttl_get(const char *buf);

uint8_t mlxsw_reg_ceer_mpls_lb2_v_get(const char *buf);

uint32_t mlxsw_reg_ceer_mpls_label2_label_id_get(const char *buf);

uint8_t mlxsw_reg_ceer_mpls_label2_ttl_get(const char *buf);

uint8_t mlxsw_reg_ceer_mpls_lb3_v_get(const char *buf);

uint32_t mlxsw_reg_ceer_mpls_label3_label_id_get(const char *buf);

uint8_t mlxsw_reg_ceer_mpls_label3_ttl_get(const char *buf);

uint8_t mlxsw_reg_ceer_mpls_lb4_v_get(const char *buf);

uint32_t mlxsw_reg_ceer_mpls_label4_label_id_get(const char *buf);

uint8_t mlxsw_reg_ceer_mpls_label4_ttl_get(const char *buf);

/* cwgcr
 * -----
 *
 */
#define MLXSW_CWGCR_ID 0x2801
#define MLXSW_CWGCR_LEN 0x14

uint8_t mlxsw_reg_cwgcr_en_get(const char *buf);

void mlxsw_reg_cwgcr_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwgcr_scd_get(const char *buf);

void mlxsw_reg_cwgcr_scd_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwgcr_aqs_weight_get(const char *buf);

void mlxsw_reg_cwgcr_aqs_weight_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwgcr_aqs_time_get(const char *buf);

void mlxsw_reg_cwgcr_aqs_time_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwgcr_ece_inner_en_get(const char *buf);

void mlxsw_reg_cwgcr_ece_inner_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwgcr_mece_get(const char *buf);

void mlxsw_reg_cwgcr_mece_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwgcr_cece_get(const char *buf);

void mlxsw_reg_cwgcr_cece_set(char *buf, uint8_t val);

/* cwtpm
 * -----
 *
 */
#define MLXSW_CWTPM_ID 0x2803
#define MLXSW_CWTPM_LEN 0x44

uint8_t mlxsw_reg_cwtpm_local_port_get(const char *buf);

void mlxsw_reg_cwtpm_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwtpm_pnat_get(const char *buf);

void mlxsw_reg_cwtpm_pnat_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwtpm_lp_msb_get(const char *buf);

void mlxsw_reg_cwtpm_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwtpm_traffic_class_get(const char *buf);

void mlxsw_reg_cwtpm_traffic_class_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwtpm_ece_get(const char *buf);

void mlxsw_reg_cwtpm_ece_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwtpm_ew_get(const char *buf);

void mlxsw_reg_cwtpm_ew_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwtpm_ee_get(const char *buf);

void mlxsw_reg_cwtpm_ee_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwtpm_tcp_g_get(const char *buf);

void mlxsw_reg_cwtpm_tcp_g_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwtpm_tcp_y_get(const char *buf);

void mlxsw_reg_cwtpm_tcp_y_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwtpm_tcp_r_get(const char *buf);

void mlxsw_reg_cwtpm_tcp_r_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwtpm_ntcp_g_get(const char *buf);

void mlxsw_reg_cwtpm_ntcp_g_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwtpm_ntcp_y_get(const char *buf);

void mlxsw_reg_cwtpm_ntcp_y_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_cwtpm_ntcp_r_get(const char *buf);

void mlxsw_reg_cwtpm_ntcp_r_set(char *buf, uint8_t val);

/* rigr_v2
 * -------
 *
 */
#define MLXSW_RIGR_V2_ID 0x8023
#define MLXSW_RIGR_V2_ERIF_ENTRY_BASE_LEN 0x24 /* base length, without records */
#define MLXSW_RIGR_V2_ADABE_RESERVED_BASE_LEN 0xa4 /* base length, without records */
#define MLXSW_RIGR_V2_ERIF_ENTRY_REC_LEN 0x04 /* record length */
#define MLXSW_RIGR_V2_ERIF_ENTRY_REC_MAX_COUNT 32
#define MLXSW_RIGR_V2_LEN 0xb0

uint8_t mlxsw_reg_rigr_v2_list_type_get(const char *buf);

void mlxsw_reg_rigr_v2_list_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rigr_v2_rigr_index_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_index_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_rigr_v2_vnext_get(const char *buf);

void mlxsw_reg_rigr_v2_vnext_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rigr_v2_next_rigr_index_get(const char *buf);

void mlxsw_reg_rigr_v2_next_rigr_index_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_rigr_v2_vrmid_get(const char *buf);

void mlxsw_reg_rigr_v2_vrmid_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_rigr_v2_rmid_index_get(const char *buf);

void mlxsw_reg_rigr_v2_rmid_index_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_rigr_v2_v_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rigr_v2_v_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint16_t mlxsw_reg_rigr_v2_erif_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rigr_v2_erif_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint32_t mlxsw_reg_rigr_v2_adabe_reserved_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rigr_v2_adabe_reserved_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint16_t mlxsw_reg_rigr_v2_rigr_nve_decap_uerif_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_nve_decap_uerif_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_rigr_v2_rigr_nve_decap_tqos_profile_en_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_nve_decap_tqos_profile_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rigr_v2_rigr_nve_decap_tqos_profile_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_nve_decap_tqos_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rigr_v2_rigr_nve_decap_decap_disable_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_nve_decap_decap_disable_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rigr_v2_rigr_generic_checks_mode_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_generic_checks_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rigr_v2_rigr_generic_allow_decap_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_generic_allow_decap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rigr_v2_rigr_generic_tqos_profile_l2_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_generic_tqos_profile_l2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rigr_v2_rigr_generic_tqos_profile_l3_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_generic_tqos_profile_l3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rigr_v2_rigr_generic_tunnel_port_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_generic_tunnel_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rigr_v2_rigr_generic_checks_nve_decap_disable_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_generic_checks_nve_decap_disable_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_rigr_v2_rigr_generic_irif_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_generic_irif_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_rigr_v2_rigr_generic_gre_key_check_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_generic_gre_key_check_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rigr_v2_rigr_generic_type_check_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_generic_type_check_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rigr_v2_rigr_generic_sip_check_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_generic_sip_check_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rigr_v2_rigr_generic_ipv4_usip_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_generic_ipv4_usip_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rigr_v2_rigr_generic_ipv6_usip_ptr_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_generic_ipv6_usip_ptr_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rigr_v2_rigr_generic_expected_gre_key_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_generic_expected_gre_key_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_rigr_v2_rigr_generic_uerif_get(const char *buf);

void mlxsw_reg_rigr_v2_rigr_generic_uerif_set(char *buf, uint16_t val);

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

uint32_t mlxsw_reg_rmftad_activity_vector_get(const char *buf, unsigned short outer_index, unsigned short index);

/* ratrb
 * -----
 *
 */
#define MLXSW_RATRB_ID 0x8024
#define MLXSW_RATRB_RECORD_BASE_LEN 0x20 /* base length, without records */
#define MLXSW_RATRB_DESTINATION_MAC_BASE_LEN 0x2a /* base length, without records */
#define MLXSW_RATRB_RECORD_REC_LEN 0x20 /* record length */
#define MLXSW_RATRB_RECORD_REC_MAX_COUNT 32
#define MLXSW_RATRB_LEN 0x420

uint8_t mlxsw_reg_ratrb_v_get(const char *buf);

void mlxsw_reg_ratrb_v_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_ratrb_adjacency_index_get(const char *buf);

void mlxsw_reg_ratrb_adjacency_index_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_ratrb_num_rec_get(const char *buf);

void mlxsw_reg_ratrb_num_rec_set(char *buf, uint8_t val);

void mlxsw_reg_ratrb_trap_action_set(char *buf, uint8_t val);

void mlxsw_reg_ratrb_trap_id_set(char *buf, uint16_t val);

void mlxsw_reg_ratrb_type_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

void mlxsw_reg_ratrb_size_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

void mlxsw_reg_ratrb_egress_router_interface_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

void mlxsw_reg_ratrb_counter_set_type_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

void mlxsw_reg_ratrb_counter_index_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

void mlxsw_reg_ratrb_destination_mac_memcpy_from(const char *buf, unsigned short outer_index, unsigned short index, char *dst);

void mlxsw_reg_ratrb_destination_mac_memcpy_to(char *buf, unsigned short outer_index, unsigned short index, const char *src);

uint32_t mlxsw_reg_ratrb_mpls_adjacency_nhlfe_ptr_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_mpls_adjacency_nhlfe_ptr_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_ratrb_mpls_adjacency_tqos_profile_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_mpls_adjacency_tqos_profile_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint16_t mlxsw_reg_ratrb_mpls_adjacency_ecmp_size_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_mpls_adjacency_ecmp_size_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint16_t mlxsw_reg_ratrb_mpls_adjacency_underlay_router_interface_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_mpls_adjacency_underlay_router_interface_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint8_t mlxsw_reg_ratrb_ipinip_encap_adjacency_ipip_type_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_ipinip_encap_adjacency_ipip_type_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint8_t mlxsw_reg_ratrb_ipinip_encap_adjacency_tqos_profile_en_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_ipinip_encap_adjacency_tqos_profile_en_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint8_t mlxsw_reg_ratrb_ipinip_encap_adjacency_tqos_profile_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_ipinip_encap_adjacency_tqos_profile_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint8_t mlxsw_reg_ratrb_ipinip_encap_adjacency_uirif_v_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_ipinip_encap_adjacency_uirif_v_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint16_t mlxsw_reg_ratrb_ipinip_encap_adjacency_uirif_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_ipinip_encap_adjacency_uirif_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint32_t mlxsw_reg_ratrb_ipinip_encap_adjacency_ipv4_udip_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_ipinip_encap_adjacency_ipv4_udip_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_ratrb_ipinip_encap_adjacency_ipv6_ptr_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_ipinip_encap_adjacency_ipv6_ptr_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_ratrb_l3_generic_encap_adjacency_u_ip_ver_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_l3_generic_encap_adjacency_u_ip_ver_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint8_t mlxsw_reg_ratrb_l3_generic_encap_adjacency_emt_pointer_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_l3_generic_encap_adjacency_emt_pointer_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint8_t mlxsw_reg_ratrb_l3_generic_encap_adjacency_tqos_profile_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_l3_generic_encap_adjacency_tqos_profile_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint16_t mlxsw_reg_ratrb_l3_generic_encap_adjacency_uirif_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_l3_generic_encap_adjacency_uirif_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint32_t mlxsw_reg_ratrb_l3_generic_encap_adjacency_ipv4_udip_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_l3_generic_encap_adjacency_ipv4_udip_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_ratrb_l3_generic_encap_adjacency_ipv6_ptr_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_l3_generic_encap_adjacency_ipv6_ptr_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_ratrb_l3_generic_encap_adjacency_cbset_x_select_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_l3_generic_encap_adjacency_cbset_x_select_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint8_t mlxsw_reg_ratrb_l3_generic_encap_adjacency_cbset_y_select_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_l3_generic_encap_adjacency_cbset_y_select_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint8_t mlxsw_reg_ratrb_l3_generic_encap_adjacency_cbset_x_set_en_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_l3_generic_encap_adjacency_cbset_x_set_en_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint8_t mlxsw_reg_ratrb_l3_generic_encap_adjacency_cbset_y_set_en_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_l3_generic_encap_adjacency_cbset_y_set_en_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint16_t mlxsw_reg_ratrb_l3_generic_encap_adjacency_cbset_x_val_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_l3_generic_encap_adjacency_cbset_x_val_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint16_t mlxsw_reg_ratrb_l3_generic_encap_adjacency_cbset_y_val_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_l3_generic_encap_adjacency_cbset_y_val_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint8_t mlxsw_reg_ratrb_new_header_type_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_new_header_type_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint16_t mlxsw_reg_ratrb_irif_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_irif_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint8_t mlxsw_reg_ratrb_qos_profile_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_qos_profile_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint32_t mlxsw_reg_ratrb_new_ipv4_udip_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_new_ipv4_udip_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_ratrb_new_ipv6_ptr_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_new_ipv6_ptr_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_ratrb_exp_l3_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_exp_l3_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint32_t mlxsw_reg_ratrb_relookup_ecmp_adjacency_next_adjacency_ptr_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_relookup_ecmp_adjacency_next_adjacency_ptr_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint16_t mlxsw_reg_ratrb_relookup_ecmp_adjacency_next_ecmp_size_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_relookup_ecmp_adjacency_next_ecmp_size_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint8_t mlxsw_reg_ratrb_relookup_ecmp_adjacency_rd_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_relookup_ecmp_adjacency_rd_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint16_t mlxsw_reg_ratrb_relookup_ecmp_adjacency_rehash_seed_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_relookup_ecmp_adjacency_rehash_seed_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint16_t mlxsw_reg_ratrb_relookup_lpm_adjacency_virtual_router_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_relookup_lpm_adjacency_virtual_router_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint8_t mlxsw_reg_ratrb_relookup_lpm_adjacency_rd_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_relookup_lpm_adjacency_rd_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint16_t mlxsw_reg_ratrb_relookup_lpm_adjacency_rehash_seed_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ratrb_relookup_lpm_adjacency_rehash_seed_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

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

uint8_t mlxsw_reg_rtdp_rtdp_nve_decap_tqos_profile_en_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_nve_decap_tqos_profile_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rtdp_rtdp_nve_decap_tqos_profile_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_nve_decap_tqos_profile_set(char *buf, uint8_t val);

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

uint8_t mlxsw_reg_rtdp_rtdp_ipinip_tqos_profile_en_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_ipinip_tqos_profile_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rtdp_rtdp_ipinip_tqos_profile_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_ipinip_tqos_profile_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rtdp_rtdp_ipinip_ipv4_usip_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_ipinip_ipv4_usip_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rtdp_rtdp_ipinip_ipv6_usip_ptr_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_ipinip_ipv6_usip_ptr_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rtdp_rtdp_ipinip_expected_gre_key_get(const char *buf);

void mlxsw_reg_rtdp_rtdp_ipinip_expected_gre_key_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_rtdp_checks_mode_get(const char *buf);

void mlxsw_reg_rtdp_checks_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rtdp_allow_decap_get(const char *buf);

void mlxsw_reg_rtdp_allow_decap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rtdp_tqos_profile_l2_get(const char *buf);

void mlxsw_reg_rtdp_tqos_profile_l2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rtdp_tqos_profile_l3_get(const char *buf);

void mlxsw_reg_rtdp_tqos_profile_l3_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rtdp_tunnel_port_get(const char *buf);

void mlxsw_reg_rtdp_tunnel_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rtdp_checks_nve_decap_disable_get(const char *buf);

void mlxsw_reg_rtdp_checks_nve_decap_disable_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_rtdp_irif_get(const char *buf);

void mlxsw_reg_rtdp_irif_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_rtdp_gre_key_check_get(const char *buf);

void mlxsw_reg_rtdp_gre_key_check_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rtdp_type_check_get(const char *buf);

void mlxsw_reg_rtdp_type_check_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rtdp_sip_check_get(const char *buf);

void mlxsw_reg_rtdp_sip_check_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rtdp_ipv4_usip_get(const char *buf);

void mlxsw_reg_rtdp_ipv4_usip_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rtdp_ipv6_usip_ptr_get(const char *buf);

void mlxsw_reg_rtdp_ipv6_usip_ptr_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rtdp_expected_gre_key_get(const char *buf);

void mlxsw_reg_rtdp_expected_gre_key_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_rtdp_egress_router_interface_get(const char *buf);

void mlxsw_reg_rtdp_egress_router_interface_set(char *buf, uint16_t val);

/* rips
 * ----
 *
 */
#define MLXSW_RIPS_ID 0x8021
#define MLXSW_RIPS_LEN 0x14

uint32_t mlxsw_reg_rips_index_get(const char *buf);

void mlxsw_reg_rips_index_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rips_ipv6_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rips_ipv6_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* ralta
 * -----
 *
 */
#define MLXSW_RALTA_ID 0x8010
#define MLXSW_RALTA_LEN 0x4

uint8_t mlxsw_reg_ralta_op_get(const char *buf);

void mlxsw_reg_ralta_op_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ralta_protocol_get(const char *buf);

void mlxsw_reg_ralta_protocol_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ralta_tree_id_get(const char *buf);

void mlxsw_reg_ralta_tree_id_set(char *buf, uint8_t val);

/* ralst
 * -----
 *
 */
#define MLXSW_RALST_ID 0x8011
#define MLXSW_RALST_LEN 0x104

uint8_t mlxsw_reg_ralst_root_bin_get(const char *buf);

void mlxsw_reg_ralst_root_bin_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_ralst_tree_id_get(const char *buf);

void mlxsw_reg_ralst_tree_id_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_ralst_bin_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_ralst_bin_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

/* raltb
 * -----
 *
 */
#define MLXSW_RALTB_ID 0x8012
#define MLXSW_RALTB_LEN 0x4

uint16_t mlxsw_reg_raltb_virtual_router_get(const char *buf);

void mlxsw_reg_raltb_virtual_router_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_raltb_protocol_get(const char *buf);

void mlxsw_reg_raltb_protocol_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_raltb_tree_id_get(const char *buf);

void mlxsw_reg_raltb_tree_id_set(char *buf, uint8_t val);

/* raleu
 * -----
 *
 */
#define MLXSW_RALEU_ID 0x8015
#define MLXSW_RALEU_LEN 0x30

uint8_t mlxsw_reg_raleu_protocol_get(const char *buf);

void mlxsw_reg_raleu_protocol_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_raleu_type_get(const char *buf);

void mlxsw_reg_raleu_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_raleu_mvr_get(const char *buf);

void mlxsw_reg_raleu_mvr_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_raleu_virtual_router_get(const char *buf);

void mlxsw_reg_raleu_virtual_router_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_raleu_update_field_get(const char *buf);

void mlxsw_reg_raleu_update_field_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_raleu_adjacency_index_get(const char *buf);

void mlxsw_reg_raleu_adjacency_index_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_raleu_ecmp_size_get(const char *buf);

void mlxsw_reg_raleu_ecmp_size_set(char *buf, uint16_t val);

void mlxsw_reg_raleu_new_adjacency_index_set(char *buf, uint32_t val);

void mlxsw_reg_raleu_new_ecmp_size_set(char *buf, uint16_t val);

void mlxsw_reg_raleu_arn_ptr_v_set(char *buf, uint8_t val);

void mlxsw_reg_raleu_arn_ptr_set(char *buf, uint32_t val);

void mlxsw_reg_raleu_arlpgt_ptr_set(char *buf, uint16_t val);

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

/* rmid_v2
 * -------
 *
 */
#define MLXSW_RMID_V2_ID 0x8036
#define MLXSW_RMID_V2_LEN 0xa0

uint16_t mlxsw_reg_rmid_v2_rmid_index_get(const char *buf);

void mlxsw_reg_rmid_v2_rmid_index_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_rmid_v2_rmpe_index_get(const char *buf);

void mlxsw_reg_rmid_v2_rmpe_index_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_rmid_v2_egress_port_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rmid_v2_egress_port_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

uint8_t mlxsw_reg_reiv_update_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_reiv_update_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint16_t mlxsw_reg_reiv_evid_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_reiv_evid_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

/* rngcr
 * -----
 *
 */
#define MLXSW_RNGCR_ID 0x8045
#define MLXSW_RNGCR_LEN 0xc

uint8_t mlxsw_reg_rngcr_v_get(const char *buf);

void mlxsw_reg_rngcr_v_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rngcr_nat4to6_flc_get(const char *buf);

void mlxsw_reg_rngcr_nat4to6_flc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rngcr_nat4to6_flh_get(const char *buf);

void mlxsw_reg_rngcr_nat4to6_flh_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rngcr_nat4to6_fl_prefix_get(const char *buf);

void mlxsw_reg_rngcr_nat4to6_fl_prefix_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_rngcr_nat4to6_fl_suffix_get(const char *buf);

void mlxsw_reg_rngcr_nat4to6_fl_suffix_set(char *buf, uint8_t val);

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

uint32_t mlxsw_reg_rlcme_dip_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rlcme_dip_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_rlcme_action_type_get(const char *buf);

void mlxsw_reg_rlcme_action_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rlcme_action_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rlcme_action_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

uint32_t mlxsw_reg_rlcmle_dip_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rlcmle_dip_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

uint32_t mlxsw_reg_rlcmld_dip_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rlcmld_dip_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_rlcmld_dip_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rlcmld_dip_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* rargcr
 * ------
 *
 */
#define MLXSW_RARGCR_ID 0x806a
#define MLXSW_RARGCR_LEN 0x8

uint32_t mlxsw_reg_rargcr_arft_index_base_get(const char *buf);

void mlxsw_reg_rargcr_arft_index_base_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_rargcr_arft_index_size_get(const char *buf);

void mlxsw_reg_rargcr_arft_index_size_set(char *buf, uint16_t val);

/* rarpc
 * -----
 *
 */
#define MLXSW_RARPC_ID 0x8060
#define MLXSW_RARPC_INGRESS_PORT_BASE_LEN 0x30 /* base length, without records */
#define MLXSW_RARPC_L4PORT_CMP_BASE_LEN 0xb0 /* base length, without records */
#define MLXSW_RARPC_L4PORT_CMP_REC_LEN 0x08 /* record length */
#define MLXSW_RARPC_L4PORT_CMP_REC_MAX_COUNT 4
#define MLXSW_RARPC_LEN 0xd0

uint8_t mlxsw_reg_rarpc_pc_default_get(const char *buf);

void mlxsw_reg_rarpc_pc_default_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpc_pc_entry_get(const char *buf);

void mlxsw_reg_rarpc_pc_entry_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpc_l4_inner_get(const char *buf);

void mlxsw_reg_rarpc_l4_inner_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpc_inner_must_get(const char *buf);

void mlxsw_reg_rarpc_inner_must_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpc_ar_packet_prof_id_get(const char *buf);

void mlxsw_reg_rarpc_ar_packet_prof_id_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_rarpc_switch_prio_get(const char *buf);

void mlxsw_reg_rarpc_switch_prio_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_rarpc_l3_type_get(const char *buf);

void mlxsw_reg_rarpc_l3_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpc_inner_l3_type_get(const char *buf);

void mlxsw_reg_rarpc_inner_l3_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpc_l4_type_get(const char *buf);

void mlxsw_reg_rarpc_l4_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpc_inner_l4_type_get(const char *buf);

void mlxsw_reg_rarpc_inner_l4_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpc_bth_ar_get(const char *buf);

void mlxsw_reg_rarpc_bth_ar_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpc_bth_opcode_msb_get(const char *buf);

void mlxsw_reg_rarpc_bth_opcode_msb_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rarpc_bth_opcode_lsb_get(const char *buf);

void mlxsw_reg_rarpc_bth_opcode_lsb_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_rarpc_inner_bth_ar_get(const char *buf);

void mlxsw_reg_rarpc_inner_bth_ar_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpc_inner_bth_opcode_msb_get(const char *buf);

void mlxsw_reg_rarpc_inner_bth_opcode_msb_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rarpc_inner_bth_opcode_lsb_get(const char *buf);

void mlxsw_reg_rarpc_inner_bth_opcode_lsb_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rarpc_ingress_port_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rarpc_ingress_port_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint16_t mlxsw_reg_rarpc_port_range_min_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rarpc_port_range_min_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint16_t mlxsw_reg_rarpc_port_range_max_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rarpc_port_range_max_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

uint8_t mlxsw_reg_rarpc_port_src_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rarpc_port_src_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint8_t mlxsw_reg_rarpc_comp_field_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rarpc_comp_field_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

/* rarsr
 * -----
 *
 */
#define MLXSW_RARSR_ID 0x8069
#define MLXSW_RARSR_LEN 0x8

uint16_t mlxsw_reg_rarsr_ar_srf_get(const char *buf);

void mlxsw_reg_rarsr_ar_srf_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_rarsr_ar_srt_get(const char *buf);

void mlxsw_reg_rarsr_ar_srt_set(char *buf, uint16_t val);

/* rarpr
 * -----
 *
 */
#define MLXSW_RARPR_ID 0x8061
#define MLXSW_RARPR_LEN 0x14

uint8_t mlxsw_reg_rarpr_ar_prof_id_get(const char *buf);

void mlxsw_reg_rarpr_ar_prof_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpr_prof_mode_get(const char *buf);

void mlxsw_reg_rarpr_prof_mode_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpr_elph_get(const char *buf);

void mlxsw_reg_rarpr_elph_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpr_grade_thr_free_get(const char *buf);

void mlxsw_reg_rarpr_grade_thr_free_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpr_grade_thr_busy_get(const char *buf);

void mlxsw_reg_rarpr_grade_thr_busy_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpr_srf_get(const char *buf);

void mlxsw_reg_rarpr_srf_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarpr_srt_get(const char *buf);

void mlxsw_reg_rarpr_srt_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_rarpr_time_bound_time_get(const char *buf);

void mlxsw_reg_rarpr_time_bound_time_set(char *buf, uint16_t val);

/* rarcl
 * -----
 *
 */
#define MLXSW_RARCL_ID 0x8062
#define MLXSW_RARCL_LEN 0x2c

uint8_t mlxsw_reg_rarcl_th_index_get(const char *buf);

void mlxsw_reg_rarcl_th_index_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rarcl_eport_cong_level0_get(const char *buf);

void mlxsw_reg_rarcl_eport_cong_level0_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rarcl_eport_cong_level1_get(const char *buf);

void mlxsw_reg_rarcl_eport_cong_level1_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rarcl_eport_cong_level2_get(const char *buf);

void mlxsw_reg_rarcl_eport_cong_level2_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rarcl_tc_cong_level0_get(const char *buf);

void mlxsw_reg_rarcl_tc_cong_level0_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rarcl_tc_cong_level1_get(const char *buf);

void mlxsw_reg_rarcl_tc_cong_level1_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_rarcl_tc_cong_level2_get(const char *buf);

void mlxsw_reg_rarcl_tc_cong_level2_set(char *buf, uint32_t val);

/* rarppm
 * ------
 *
 */
#define MLXSW_RARPPM_ID 0x8077
#define MLXSW_RARPPM_LEN 0x8

uint8_t mlxsw_reg_rarppm_local_port_get(const char *buf);

void mlxsw_reg_rarppm_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarppm_pool_get(const char *buf);

void mlxsw_reg_rarppm_pool_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarppm_lp_msb_get(const char *buf);

void mlxsw_reg_rarppm_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarppm_th_indx_get(const char *buf);

void mlxsw_reg_rarppm_th_indx_set(char *buf, uint8_t val);

/* rarlu
 * -----
 *
 */
#define MLXSW_RARLU_ID 0x8068
#define MLXSW_RARLU_LEN 0xc

uint8_t mlxsw_reg_rarlu_local_port_get(const char *buf);

void mlxsw_reg_rarlu_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarlu_lp_msb_get(const char *buf);

void mlxsw_reg_rarlu_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarlu_lut_en_get(const char *buf);

void mlxsw_reg_rarlu_lut_en_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rarlu_link_utiliztion_thr_get(const char *buf);

void mlxsw_reg_rarlu_link_utiliztion_thr_set(char *buf, uint32_t val);

/* rarft
 * -----
 *
 */
#define MLXSW_RARFT_ID 0x8064
#define MLXSW_RARFT_LEN 0x10

uint32_t mlxsw_reg_rarft_arft_index_get(const char *buf);

void mlxsw_reg_rarft_arft_index_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_rarft_arft_entry_in_row_get(const char *buf);

void mlxsw_reg_rarft_arft_entry_in_row_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarft_valid_get(const char *buf);

void mlxsw_reg_rarft_valid_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarft_lp_msb_get(const char *buf);

void mlxsw_reg_rarft_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarft_local_port_get(const char *buf);

void mlxsw_reg_rarft_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rarft_ar_prof_id_get(const char *buf);

void mlxsw_reg_rarft_ar_prof_id_set(char *buf, uint8_t val);

/* rarftb
 * ------
 *
 */
#define MLXSW_RARFTB_ID 0x8079
#define MLXSW_RARFTB_LEN 0x8

uint32_t mlxsw_reg_rarftb_arft_index_get(const char *buf);

void mlxsw_reg_rarftb_arft_index_set(char *buf, uint32_t val);

void mlxsw_reg_rarftb_num_of_arft_lines_set(char *buf, uint16_t val);

/* rarlpgt
 * -------
 *
 */
#define MLXSW_RARLPGT_ID 0x8065
#define MLXSW_RARLPGT_LEN 0x120

uint16_t mlxsw_reg_rarlpgt_arlpgt_index_get(const char *buf);

void mlxsw_reg_rarlpgt_arlpgt_index_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_rarlpgt_egress_port_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rarlpgt_egress_port_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_rarlpgt_egress_port_or_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_rarlpgt_egress_port_or_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* rarcc
 * -----
 *
 */
#define MLXSW_RARCC_ID 0x8067
#define MLXSW_RARCC_LEN 0x20

uint8_t mlxsw_reg_rarcc_clr_get(const char *buf);

void mlxsw_reg_rarcc_clr_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_rarcc_ar_changes_congestion_high_get(const char *buf);

uint32_t mlxsw_reg_rarcc_ar_changes_congestion_low_get(const char *buf);

uint32_t mlxsw_reg_rarcc_ar_changes_arn_high_get(const char *buf);

uint32_t mlxsw_reg_rarcc_ar_changes_arn_low_get(const char *buf);

/* rsnh
 * ----
 *
 */
#define MLXSW_RSNH_ID 0x8066
#define MLXSW_RSNH_LEN 0x10

uint8_t mlxsw_reg_rsnh_local_port_get(const char *buf);

void mlxsw_reg_rsnh_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rsnh_lp_msb_get(const char *buf);

void mlxsw_reg_rsnh_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_rsnh_p2d_en_get(const char *buf);

void mlxsw_reg_rsnh_p2d_en_set(char *buf, uint8_t val);

void mlxsw_reg_rsnh_dmac_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_rsnh_dmac_memcpy_to(char *buf, const char *src);

/* rirt
 * ----
 *
 */
#define MLXSW_RIRT_ID 0x8046
#define MLXSW_RIRT_ROUTER_ENTRY_RECORD_BASE_LEN 0x10 /* base length, without records */
#define MLXSW_RIRT_ROUTER_ENTRY_RECORD_REC_LEN 0x08 /* record length */
#define MLXSW_RIRT_ROUTER_ENTRY_RECORD_REC_MAX_COUNT 8
#define MLXSW_RIRT_LEN 0x50

uint16_t mlxsw_reg_rirt_offset_get(const char *buf);

void mlxsw_reg_rirt_offset_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_rirt_valid_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_rirt_swid_get(const char *buf, unsigned short outer_index, unsigned short index);

uint16_t mlxsw_reg_rirt_subnet_prefix_get(const char *buf, unsigned short outer_index, unsigned short index);

/* mpnhlfe
 * -------
 *
 */
#define MLXSW_MPNHLFE_ID 0x8804
#define MLXSW_MPNHLFE_LEN 0x5c

uint8_t mlxsw_reg_mpnhlfe_ca_get(const char *buf);

void mlxsw_reg_mpnhlfe_ca_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_a_get(const char *buf);

uint8_t mlxsw_reg_mpnhlfe_v_get(const char *buf);

void mlxsw_reg_mpnhlfe_v_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mpnhlfe_nhlfe_ptr_get(const char *buf);

void mlxsw_reg_mpnhlfe_nhlfe_ptr_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_mpnhlfe_forward_action_get(const char *buf);

void mlxsw_reg_mpnhlfe_forward_action_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_trap_action_get(const char *buf);

void mlxsw_reg_mpnhlfe_trap_action_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpnhlfe_trap_id_get(const char *buf);

void mlxsw_reg_mpnhlfe_trap_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpnhlfe_counter_set_type_get(const char *buf);

void mlxsw_reg_mpnhlfe_counter_set_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mpnhlfe_counter_index_get(const char *buf);

void mlxsw_reg_mpnhlfe_counter_index_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_dscp_rw_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_dscp_rw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_uecn_exp_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_uecn_exp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_usp_dscp_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_usp_dscp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_usp_exp_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_usp_exp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_exp_rw_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_exp_rw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_set_exp_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_set_exp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_exp_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_exp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_tqos_profile_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_tqos_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_bos_check_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_bos_check_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_label_action_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_label_action_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_label_id_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_label_id_set(char *buf, uint32_t val);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_dmac_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_dmac_memcpy_to(char *buf, const char *src);

uint16_t mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_egress_router_interface_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_eth_egress_router_interface_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_dscp_rw_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_dscp_rw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_uecn_exp_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_uecn_exp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_usp_dscp_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_usp_dscp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_usp_exp_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_usp_exp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_tqos_profile_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_tqos_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_irifv_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_irifv_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_irif_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_irif_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_erifv_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_erifv_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_egress_router_interface_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_egress_router_interface_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_cbset_select_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_cbset_select_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_cbset_val_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_cbset_val_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_cbset_mask_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_iprouter_cbset_mask_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_dscp_rw_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_dscp_rw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_uecn_exp_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_uecn_exp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_usp_dscp_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_usp_dscp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_usp_exp_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_usp_exp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_tqos_profile_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_tqos_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_bos_check_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_bos_check_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_irifv_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_irifv_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_irif_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_irif_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_erifv_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_erifv_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_egress_router_interface_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_egress_router_interface_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_cbset_select_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_cbset_select_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_cbset_val_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_cbset_val_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_cbset_mask_get(const char *buf);

void mlxsw_reg_mpnhlfe_mpnhlfe_param_lookups_cbset_mask_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_mpnhlfe_exp_rw_get(const char *buf);

void mlxsw_reg_mpnhlfe_exp_rw_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_set_exp_get(const char *buf);

void mlxsw_reg_mpnhlfe_set_exp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_exp_get(const char *buf);

void mlxsw_reg_mpnhlfe_exp_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_mpnhlfe_label_action_get(const char *buf);

void mlxsw_reg_mpnhlfe_label_action_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_mpnhlfe_label_id_get(const char *buf);

void mlxsw_reg_mpnhlfe_label_id_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_mpnhlfe_next_nhlfe_get(const char *buf);

void mlxsw_reg_mpnhlfe_next_nhlfe_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_mpnhlfe_ecmp_size_get(const char *buf);

void mlxsw_reg_mpnhlfe_ecmp_size_set(char *buf, uint16_t val);

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

/* tngee
 * -----
 *
 */
#define MLXSW_TNGEE_ID 0xa021
#define MLXSW_TNGEE_LEN 0x50

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

uint8_t mlxsw_reg_tngee_tngee_nve_vni_update_get(const char *buf);

void mlxsw_reg_tngee_tngee_nve_vni_update_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngee_tngee_nve_tqos_prof_en_get(const char *buf);

void mlxsw_reg_tngee_tngee_nve_tqos_prof_en_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tngee_tngee_nve_vni_get(const char *buf);

void mlxsw_reg_tngee_tngee_nve_vni_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_tngee_tngee_nve_tqos_profile_get(const char *buf);

void mlxsw_reg_tngee_tngee_nve_tqos_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngee_tngee_flex_reg_tqos_profile_get(const char *buf);

void mlxsw_reg_tngee_tngee_flex_reg_tqos_profile_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngee_tngee_flex_reg_tunnel_port_get(const char *buf);

void mlxsw_reg_tngee_tngee_flex_reg_tunnel_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngee_tngee_flex_reg_emt_pointer_get(const char *buf);

void mlxsw_reg_tngee_tngee_flex_reg_emt_pointer_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngee_tngee_flex_reg_cbset_select_get(const char *buf);

void mlxsw_reg_tngee_tngee_flex_reg_cbset_select_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngee_tngee_flex_reg_cbset_x_set_en_get(const char *buf);

void mlxsw_reg_tngee_tngee_flex_reg_cbset_x_set_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngee_tngee_flex_reg_cbset_y_set_en_get(const char *buf);

void mlxsw_reg_tngee_tngee_flex_reg_cbset_y_set_en_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_tngee_tngee_flex_reg_cbset_x_val_get(const char *buf);

void mlxsw_reg_tngee_tngee_flex_reg_cbset_x_val_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_tngee_tngee_flex_reg_cbset_y_val_get(const char *buf);

void mlxsw_reg_tngee_tngee_flex_reg_cbset_y_val_set(char *buf, uint16_t val);

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

uint32_t mlxsw_reg_tnumt_tunnel_mc_ipv4_udip_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_tnumt_tunnel_mc_ipv4_udip_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint8_t mlxsw_reg_tnumt_tunnel_mc_ipv6_size_get(const char *buf);

void mlxsw_reg_tnumt_tunnel_mc_ipv6_size_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tnumt_tunnel_mc_ipv6_udip_ptr_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_tnumt_tunnel_mc_ipv6_udip_ptr_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* tngcr
 * -----
 *
 */
#define MLXSW_TNGCR_ID 0xa001
#define MLXSW_TNGCR_LEN 0x64

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

uint8_t mlxsw_reg_tngcr_nve_udp_sport_suffix_get(const char *buf);

void mlxsw_reg_tngcr_nve_udp_sport_suffix_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_nve_group_size_mc_get(const char *buf);

void mlxsw_reg_tngcr_nve_group_size_mc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_nve_group_size_flood_get(const char *buf);

void mlxsw_reg_tngcr_nve_group_size_flood_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_learn_enable_get(const char *buf);

void mlxsw_reg_tngcr_learn_enable_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tngcr_dis_nve_opt_chk_get(const char *buf);

void mlxsw_reg_tngcr_dis_nve_opt_chk_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_tngcr_underlay_virtual_router_get(const char *buf);

void mlxsw_reg_tngcr_underlay_virtual_router_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_tngcr_underlay_rif_get(const char *buf);

void mlxsw_reg_tngcr_underlay_rif_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_tngcr_usipv4_get(const char *buf);

void mlxsw_reg_tngcr_usipv4_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_tngcr_usipv6_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_tngcr_usipv6_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_tngcr_header0_bit_set_get(const char *buf);

void mlxsw_reg_tngcr_header0_bit_set_set(char *buf, uint32_t val);

void mlxsw_reg_tngcr_nvgre_hdr_bits_en_set(char *buf, uint8_t val);

void mlxsw_reg_tngcr_geneve_hdr_bits_en_set(char *buf, uint8_t val);

void mlxsw_reg_tngcr_gpe_hdr_bits_en_set(char *buf, uint8_t val);

void mlxsw_reg_tngcr_vxlan_hdr_bits_en_set(char *buf, uint8_t val);

uint64_t mlxsw_reg_tngcr_vxlan_hdr_bits_get(const char *buf);

void mlxsw_reg_tngcr_vxlan_hdr_bits_set(char *buf, uint64_t val);

uint64_t mlxsw_reg_tngcr_gpe_hdr_bits_get(const char *buf);

void mlxsw_reg_tngcr_gpe_hdr_bits_set(char *buf, uint64_t val);

uint64_t mlxsw_reg_tngcr_geneve_hdr_bits_get(const char *buf);

void mlxsw_reg_tngcr_geneve_hdr_bits_set(char *buf, uint64_t val);

uint32_t mlxsw_reg_tngcr_nvgre_hdr_bits_get(const char *buf);

void mlxsw_reg_tngcr_nvgre_hdr_bits_set(char *buf, uint32_t val);

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

/* tnifr
 * -----
 *
 */
#define MLXSW_TNIFR_ID 0xa014
#define MLXSW_TNIFR_LEN 0x60

uint8_t mlxsw_reg_tnifr_table_id_get(const char *buf);

void mlxsw_reg_tnifr_table_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnifr_tunnel_port_get(const char *buf);

void mlxsw_reg_tnifr_tunnel_port_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tnifr_port_filter_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_tnifr_port_filter_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_tnifr_port_filter_update_en_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_tnifr_port_filter_update_en_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* tnifr_v2
 * --------
 *
 */
#define MLXSW_TNIFR_V2_ID 0xa017
#define MLXSW_TNIFR_V2_LEN 0x120

uint8_t mlxsw_reg_tnifr_v2_table_id_get(const char *buf);

void mlxsw_reg_tnifr_v2_table_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_tnifr_v2_tunnel_port_get(const char *buf);

void mlxsw_reg_tnifr_v2_tunnel_port_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_tnifr_v2_port_filter_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_tnifr_v2_port_filter_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_tnifr_v2_port_filter_update_en_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_tnifr_v2_port_filter_update_en_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

/* fgcr
 * ----
 *
 */
#define MLXSW_FGCR_ID 0x4800
#define MLXSW_FGCR_LEN 0x10

uint8_t mlxsw_reg_fgcr_flat_sec_offset_get(const char *buf);

void mlxsw_reg_fgcr_flat_sec_offset_set(char *buf, uint8_t val);

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

uint32_t mlxsw_reg_fpums_port_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_fpums_port_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

/* fmqc
 * ----
 *
 */
#define MLXSW_FMQC_ID 0x4905
#define MLXSW_FMQC_LEN 0xc

uint8_t mlxsw_reg_fmqc_s_get(const char *buf);

uint16_t mlxsw_reg_fmqc_lp_get(const char *buf);

void mlxsw_reg_fmqc_lp_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_fmqc_modifier_cluster_get(const char *buf);

/* fmtpc
 * -----
 *
 */
#define MLXSW_FMTPC_ID 0x4928
#define MLXSW_FMTPC_LEN 0x14

uint8_t mlxsw_reg_fmtpc_prog_idx_get(const char *buf);

void mlxsw_reg_fmtpc_prog_idx_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtpc_pc_get(const char *buf);

void mlxsw_reg_fmtpc_pc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtpc_op_code_get(const char *buf);

void mlxsw_reg_fmtpc_op_code_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_fmtpc_operand0_get(const char *buf);

void mlxsw_reg_fmtpc_operand0_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_fmtpc_operand1_get(const char *buf);

void mlxsw_reg_fmtpc_operand1_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_fmtpc_operand2_get(const char *buf);

void mlxsw_reg_fmtpc_operand2_set(char *buf, uint16_t val);

/* fmtpa
 * -----
 *
 */
#define MLXSW_FMTPA_ID 0x4929
#define MLXSW_FMTPA_LEN 0x10

uint8_t mlxsw_reg_fmtpa_local_port_get(const char *buf);

void mlxsw_reg_fmtpa_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtpa_lp_msb_get(const char *buf);

void mlxsw_reg_fmtpa_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtpa_prog_idx_get(const char *buf);

void mlxsw_reg_fmtpa_prog_idx_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtpa_e_get(const char *buf);

void mlxsw_reg_fmtpa_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtpa_bound_emt_get(const char *buf);

void mlxsw_reg_fmtpa_bound_emt_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_fmtpa_reg0_get(const char *buf);

void mlxsw_reg_fmtpa_reg0_set(char *buf, uint16_t val);

/* fmtb
 * ----
 *
 */
#define MLXSW_FMTB_ID 0x492a
#define MLXSW_FMTB_LEN 0x1c

uint8_t mlxsw_reg_fmtb_prog_idx_get(const char *buf);

void mlxsw_reg_fmtb_prog_idx_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtb_enable_get(const char *buf);

void mlxsw_reg_fmtb_enable_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtb_type_get(const char *buf);

void mlxsw_reg_fmtb_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtb_fence_binding_info_atomic_get(const char *buf);

void mlxsw_reg_fmtb_fence_binding_info_atomic_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtb_fence_binding_info_emt_bitmask_get(const char *buf);

void mlxsw_reg_fmtb_fence_binding_info_emt_bitmask_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtb_ram_binding_info_atomic_get(const char *buf);

void mlxsw_reg_fmtb_ram_binding_info_atomic_set(char *buf, uint8_t val);

/* fmtc
 * ----
 *
 */
#define MLXSW_FMTC_ID 0x4901
#define MLXSW_FMTC_LEN 0x4c

uint8_t mlxsw_reg_fmtc_per_port_get(const char *buf);

void mlxsw_reg_fmtc_per_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_local_port_get(const char *buf);

void mlxsw_reg_fmtc_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_lp_msb_get(const char *buf);

void mlxsw_reg_fmtc_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_emt_index_get(const char *buf);

void mlxsw_reg_fmtc_emt_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_length_cb_get(const char *buf);

void mlxsw_reg_fmtc_length_cb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_length_cb_mask_get(const char *buf);

void mlxsw_reg_fmtc_length_cb_mask_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_length_math_bitmap_get(const char *buf);

void mlxsw_reg_fmtc_length_math_bitmap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_length_math_add_pos_get(const char *buf);

void mlxsw_reg_fmtc_length_math_add_pos_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_length_math_shift_left_get(const char *buf);

void mlxsw_reg_fmtc_length_math_shift_left_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_length_math_shift_get(const char *buf);

void mlxsw_reg_fmtc_length_math_shift_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_length_get(const char *buf);

void mlxsw_reg_fmtc_length_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_update_geneve_length_get(const char *buf);

void mlxsw_reg_fmtc_update_geneve_length_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_update_udp_tcp_length_get(const char *buf);

void mlxsw_reg_fmtc_update_udp_tcp_length_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_update_ipv4_ihl_get(const char *buf);

void mlxsw_reg_fmtc_update_ipv4_ihl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_update_hbh_length_get(const char *buf);

void mlxsw_reg_fmtc_update_hbh_length_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_update_ipv6_length_get(const char *buf);

void mlxsw_reg_fmtc_update_ipv6_length_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_update_ipv4_length_get(const char *buf);

void mlxsw_reg_fmtc_update_ipv4_length_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_update_ipv4_cs_get(const char *buf);

void mlxsw_reg_fmtc_update_ipv4_cs_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_update_udp_tcp_cs_get(const char *buf);

void mlxsw_reg_fmtc_update_udp_tcp_cs_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_clear_udp_cs_get(const char *buf);

void mlxsw_reg_fmtc_clear_udp_cs_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_fmtc_max_latency_get(const char *buf);

void mlxsw_reg_fmtc_max_latency_set(char *buf, uint16_t val);

uint32_t mlxsw_reg_fmtc_latency_invalid_value_get(const char *buf);

void mlxsw_reg_fmtc_latency_invalid_value_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fmtc_buffer_fill_level_invalid_value_get(const char *buf);

void mlxsw_reg_fmtc_buffer_fill_level_invalid_value_set(char *buf, uint32_t val);

uint16_t mlxsw_reg_fmtc_enc_l2_uirif_get(const char *buf);

void mlxsw_reg_fmtc_enc_l2_uirif_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_fmtc_enc_ipv4_id_get(const char *buf);

void mlxsw_reg_fmtc_enc_ipv4_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_fmtc_enc_ipv4_flag_get(const char *buf);

void mlxsw_reg_fmtc_enc_ipv4_flag_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_fmtc_enc_ipv4_frag_offset_get(const char *buf);

void mlxsw_reg_fmtc_enc_ipv4_frag_offset_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_fmtc_enc_next_header_get(const char *buf);

void mlxsw_reg_fmtc_enc_next_header_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_enc_flc_get(const char *buf);

void mlxsw_reg_fmtc_enc_flc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_enc_flh_get(const char *buf);

void mlxsw_reg_fmtc_enc_flh_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_fmtc_enc_fl_prefix_get(const char *buf);

void mlxsw_reg_fmtc_enc_fl_prefix_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_fmtc_enc_fl_suffix_get(const char *buf);

void mlxsw_reg_fmtc_enc_fl_suffix_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtc_s0_sel_mode_get(const char *buf);

void mlxsw_reg_fmtc_s0_sel_mode_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_fmtc_s0_offset_get(const char *buf);

void mlxsw_reg_fmtc_s0_offset_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_fmtc_s1_sel_mode_get(const char *buf);

void mlxsw_reg_fmtc_s1_sel_mode_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_fmtc_s1_offset_get(const char *buf);

void mlxsw_reg_fmtc_s1_offset_set(char *buf, uint16_t val);

/* fmte
 * ----
 *
 */
#define MLXSW_FMTE_ID 0x4902
#define MLXSW_FMTE_LEN 0x14

uint8_t mlxsw_reg_fmte_per_port_get(const char *buf);

void mlxsw_reg_fmte_per_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmte_local_port_get(const char *buf);

void mlxsw_reg_fmte_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmte_lp_msb_get(const char *buf);

void mlxsw_reg_fmte_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmte_emt_index_get(const char *buf);

void mlxsw_reg_fmte_emt_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmte_entry_index_get(const char *buf);

void mlxsw_reg_fmte_entry_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmte_cmd_id_get(const char *buf);

void mlxsw_reg_fmte_cmd_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmte_iim_get(const char *buf);

void mlxsw_reg_fmte_iim_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_fmte_imm_get(const char *buf);

void mlxsw_reg_fmte_imm_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_fmte_edit_en_get(const char *buf);

void mlxsw_reg_fmte_edit_en_set(char *buf, uint8_t val);

/* fmtm
 * ----
 *
 */
#define MLXSW_FMTM_ID 0x4903
#define MLXSW_FMTM_LEN 0x8

uint8_t mlxsw_reg_fmtm_mapper_index_get(const char *buf);

void mlxsw_reg_fmtm_mapper_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtm_emt_index_in_get(const char *buf);

void mlxsw_reg_fmtm_emt_index_in_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmtm_emt_index_out_get(const char *buf);

void mlxsw_reg_fmtm_emt_index_out_set(char *buf, uint8_t val);

/* fmep
 * ----
 *
 */
#define MLXSW_FMEP_ID 0x4904
#define MLXSW_FMEP_LEN 0x8

uint8_t mlxsw_reg_fmep_global_get(const char *buf);

void mlxsw_reg_fmep_global_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmep_local_port_get(const char *buf);

void mlxsw_reg_fmep_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fmep_lp_msb_get(const char *buf);

void mlxsw_reg_fmep_lp_msb_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_fmep_ext_mod_parsing_get(const char *buf);

void mlxsw_reg_fmep_ext_mod_parsing_set(char *buf, uint16_t val);

/* fsgcr
 * -----
 *
 */
#define MLXSW_FSGCR_ID 0x4920
#define MLXSW_FSGCR_LEN 0xc

uint8_t mlxsw_reg_fsgcr_failure_on_invalid_lock_get(const char *buf);

void mlxsw_reg_fsgcr_failure_on_invalid_lock_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fsgcr_sem_lock_protection_en_get(const char *buf);

void mlxsw_reg_fsgcr_sem_lock_protection_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fsgcr_ticket_cb_index_get(const char *buf);

void mlxsw_reg_fsgcr_ticket_cb_index_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fsgcr_sem_poll_max_retries_get(const char *buf);

void mlxsw_reg_fsgcr_sem_poll_max_retries_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_fsgcr_linear_group_id_get(const char *buf);

void mlxsw_reg_fsgcr_linear_group_id_set(char *buf, uint16_t val);

/* fsdb
 * ----
 *
 */
#define MLXSW_FSDB_ID 0x4921
#define MLXSW_FSDB_LEN 0x78

uint16_t mlxsw_reg_fsdb_acl_group_id_get(const char *buf);

void mlxsw_reg_fsdb_acl_group_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_fsdb_fr_get(const char *buf);

uint8_t mlxsw_reg_fsdb_partition_id_get(const char *buf);

void mlxsw_reg_fsdb_partition_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fsdb_db_op_get(const char *buf);

void mlxsw_reg_fsdb_db_op_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fsdb_sem_op_get(const char *buf);

void mlxsw_reg_fsdb_sem_op_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fsdb_s_get(const char *buf);

uint8_t mlxsw_reg_fsdb_hit_get(const char *buf);

uint8_t mlxsw_reg_fsdb_a_get(const char *buf);

uint8_t mlxsw_reg_fsdb_sem_val_get(const char *buf);

uint16_t mlxsw_reg_fsdb_sem_lock_cnt_get(const char *buf);

uint64_t mlxsw_reg_fsdb_data_get(const char *buf);

void mlxsw_reg_fsdb_data_set(char *buf, uint64_t val);

void mlxsw_reg_fsdb_key_data_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_fsdb_key_data_memcpy_to(char *buf, const char *src);

/* fspt
 * ----
 *
 */
#define MLXSW_FSPT_ID 0x4922
#define MLXSW_FSPT_LEN 0x44

uint8_t mlxsw_reg_fspt_set_partitions_bitmap_get(const char *buf);

void mlxsw_reg_fspt_set_partitions_bitmap_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_fspt_warning_th_partition_0_get(const char *buf);

void mlxsw_reg_fspt_warning_th_partition_0_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_warning_th_partition_1_get(const char *buf);

void mlxsw_reg_fspt_warning_th_partition_1_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_warning_th_partition_2_get(const char *buf);

void mlxsw_reg_fspt_warning_th_partition_2_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_warning_th_partition_3_get(const char *buf);

void mlxsw_reg_fspt_warning_th_partition_3_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_warning_th_partition_4_get(const char *buf);

void mlxsw_reg_fspt_warning_th_partition_4_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_warning_th_partition_5_get(const char *buf);

void mlxsw_reg_fspt_warning_th_partition_5_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_warning_th_partition_6_get(const char *buf);

void mlxsw_reg_fspt_warning_th_partition_6_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_warning_th_partition_7_get(const char *buf);

void mlxsw_reg_fspt_warning_th_partition_7_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_max_th_partition_0_get(const char *buf);

void mlxsw_reg_fspt_max_th_partition_0_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_max_th_partition_1_get(const char *buf);

void mlxsw_reg_fspt_max_th_partition_1_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_max_th_partition_2_get(const char *buf);

void mlxsw_reg_fspt_max_th_partition_2_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_max_th_partition_3_get(const char *buf);

void mlxsw_reg_fspt_max_th_partition_3_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_max_th_partition_4_get(const char *buf);

void mlxsw_reg_fspt_max_th_partition_4_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_max_th_partition_5_get(const char *buf);

void mlxsw_reg_fspt_max_th_partition_5_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_max_th_partition_6_get(const char *buf);

void mlxsw_reg_fspt_max_th_partition_6_set(char *buf, uint32_t val);

uint32_t mlxsw_reg_fspt_max_th_partition_7_get(const char *buf);

void mlxsw_reg_fspt_max_th_partition_7_set(char *buf, uint32_t val);

/* fsdc
 * ----
 *
 */
#define MLXSW_FSDC_ID 0x492c
#define MLXSW_FSDC_LEN 0x10

uint8_t mlxsw_reg_fsdc_sif_get(const char *buf);

void mlxsw_reg_fsdc_sif_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fsdc_filter_fields_get(const char *buf);

void mlxsw_reg_fsdc_filter_fields_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_fsdc_group_id_get(const char *buf);

void mlxsw_reg_fsdc_group_id_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_fsdc_entry_sem_s_get(const char *buf);

void mlxsw_reg_fsdc_entry_sem_s_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fsdc_entry_activity_get(const char *buf);

void mlxsw_reg_fsdc_entry_activity_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_fsdc_entry_partition_id_get(const char *buf);

void mlxsw_reg_fsdc_entry_partition_id_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_fsdc_num_entries_get(const char *buf);

/* fsps
 * ----
 *
 */
#define MLXSW_FSPS_ID 0x4923
#define MLXSW_FSPS_LEN 0x10

uint8_t mlxsw_reg_fsps_tbm_get(const char *buf);

uint8_t mlxsw_reg_fsps_tbw_get(const char *buf);

uint8_t mlxsw_reg_fsps_partition_id_get(const char *buf);

void mlxsw_reg_fsps_partition_id_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_fsps_warning_threshold_get(const char *buf);

uint32_t mlxsw_reg_fsps_max_threshold_get(const char *buf);

uint32_t mlxsw_reg_fsps_occupancy_get(const char *buf);

/* fstm
 * ----
 *
 */
#define MLXSW_FSTM_ID 0x4924
#define MLXSW_FSTM_PORT_TICKET_INFO_BASE_LEN 0x04 /* base length, without records */
#define MLXSW_FSTM_PORT_TICKET_INFO_REC_LEN 0x04 /* record length */
#define MLXSW_FSTM_PORT_TICKET_INFO_REC_MAX_COUNT 260
#define MLXSW_FSTM_LEN 0x414

uint16_t mlxsw_reg_fstm_record_num_get(const char *buf);

void mlxsw_reg_fstm_record_num_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_fstm_ticket_machine_en_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_fstm_ticket_machine_en_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

void mlxsw_reg_fstm_lport_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

/* fsed
 * ----
 *
 */
#define MLXSW_FSED_ID 0x4925
#define MLXSW_FSED_SF_DUMP_PAGE_BASE_LEN 0x10 /* base length, without records */
#define MLXSW_FSED_KEY_54B_BASE_LEN 0x18 /* base length, without records */
#define MLXSW_FSED_RECORD_BASE_LEN 0x08 /* base length, without records */
#define MLXSW_FSED_KEY_18B_BASE_LEN 0x18 /* base length, without records */
#define MLXSW_FSED_SF_DUMP_PAGE_REC_LEN 0x58 /* record length */
#define MLXSW_FSED_SF_DUMP_PAGE_REC_MAX_COUNT 16
#define MLXSW_FSED_RECORD_REC_LEN 0x28 /* record length */
#define MLXSW_FSED_RECORD_REC_MAX_COUNT 2
#define MLXSW_FSED_LEN 0x590

uint16_t mlxsw_reg_fsed_num_pages_get(const char *buf);

uint16_t mlxsw_reg_fsed_num_of_entries_get(const char *buf);

uint8_t mlxsw_reg_fsed_mode_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_fsed_sf_page_dump_mode_0_key_54b_memcpy_from(const char *buf, unsigned short outer_index, unsigned short index, char *dst);

uint8_t mlxsw_reg_fsed_sf_page_dump_mode_0_valid_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_fsed_sf_page_dump_mode_0_key_size_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_fsed_sf_page_dump_mode_0_partition_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_fsed_sf_page_dump_mode_0_sem_s_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_fsed_sf_page_dump_mode_0_a_get(const char *buf, unsigned short outer_index, unsigned short index);

uint64_t mlxsw_reg_fsed_sf_page_dump_mode_0_data_get(const char *buf, unsigned short outer_index, unsigned short index);

uint16_t mlxsw_reg_fsed_sf_page_dump_mode_0_sem_count_get(const char *buf, unsigned short outer_index, unsigned short index);

uint16_t mlxsw_reg_fsed_sf_page_dump_mode_0_region_id_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_fsed_record_key_18b_memcpy_from(const char *buf, unsigned short outer_index, unsigned short index, char *dst);

uint8_t mlxsw_reg_fsed_record_valid_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_fsed_record_key_size_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_fsed_record_partition_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_fsed_record_sem_s_get(const char *buf, unsigned short outer_index, unsigned short index);

uint8_t mlxsw_reg_fsed_record_a_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_fsed_record_a_set(char *buf, unsigned short outer_index, unsigned short index, uint8_t val);

uint64_t mlxsw_reg_fsed_record_data_get(const char *buf, unsigned short outer_index, unsigned short index);

uint16_t mlxsw_reg_fsed_record_sem_count_get(const char *buf, unsigned short outer_index, unsigned short index);

uint16_t mlxsw_reg_fsed_record_region_id_get(const char *buf, unsigned short outer_index, unsigned short index);

/* fshe
 * ----
 *
 */
#define MLXSW_FSHE_ID 0x4926
#define MLXSW_FSHE_LEN 0x8

uint8_t mlxsw_reg_fshe_op_get(const char *buf);

void mlxsw_reg_fshe_op_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_fshe_hw_errors_get(const char *buf);

/* fsfh
 * ----
 *
 */
#define MLXSW_FSFH_ID 0x4927
#define MLXSW_FSFH_LEN 0xac

uint8_t mlxsw_reg_fsfh_failure_reason_get(const char *buf);

void mlxsw_reg_fsfh_failure_reason_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_fsfh_action_info_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_fsfh_action_info_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* xgcr
 * ----
 *
 */
#define MLXSW_XGCR_ID 0x7801
#define MLXSW_XGCR_LEN 0x8

uint8_t mlxsw_reg_xgcr_mtm_get(const char *buf);

void mlxsw_reg_xgcr_mtm_set(char *buf, uint8_t val);

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

/* xmdr
 * ----
 *
 */
#define MLXSW_XMDR_ID 0x7803
#define MLXSW_XMDR_LEN 0xa0

uint8_t mlxsw_reg_xmdr_num_rec_get(const char *buf);

void mlxsw_reg_xmdr_num_rec_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_xmdr_reply_vect_get(const char *buf);

void mlxsw_reg_xmdr_transaction_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

/* xlkbu
 * -----
 *
 */
#define MLXSW_XLKBU_ID 0x7804
#define MLXSW_XLKBU_LEN 0x140

uint8_t mlxsw_reg_xlkbu_data_type_get(const char *buf);

void mlxsw_reg_xlkbu_data_type_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_xlkbu_value_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_xlkbu_value_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_xlkbu_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_xlkbu_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_xlkbu_new_value_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_xlkbu_new_value_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

uint32_t mlxsw_reg_xlkbu_new_value_mask_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_xlkbu_new_value_mask_set(char *buf, unsigned short outer_index, unsigned short index, uint32_t val);

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

uint16_t mlxsw_reg_xralst_bin_get(const char *buf, unsigned short outer_index, unsigned short index);

void mlxsw_reg_xralst_bin_set(char *buf, unsigned short outer_index, unsigned short index, uint16_t val);

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

/* ugcap
 * -----
 *
 */
#define MLXSW_UGCAP_ID 0x6400
#define MLXSW_UGCAP_LEN 0x18

uint16_t mlxsw_reg_ugcap_max_mtu_get(const char *buf);

uint32_t mlxsw_reg_ugcap_cap_utcam_entries_get(const char *buf);

uint8_t mlxsw_reg_ugcap_cap_utcam_counters_get(const char *buf);

uint8_t mlxsw_reg_ugcap_cap_utcam_keys_get(const char *buf);

uint8_t mlxsw_reg_ugcap_cap_utcam_entries_2_key_blocks_get(const char *buf);

uint8_t mlxsw_reg_ugcap_cap_utcam_entries_4_key_blocks_get(const char *buf);

uint8_t mlxsw_reg_ugcap_cap_utcam_entries_8_key_blocks_get(const char *buf);

uint8_t mlxsw_reg_ugcap_cap_utcam_entries_12_key_blocks_get(const char *buf);

uint32_t mlxsw_reg_ugcap_cap_secy_entries_get(const char *buf);

uint32_t mlxsw_reg_ugcap_cap_sadb_entries_get(const char *buf);

/* upcap
 * -----
 *
 */
#define MLXSW_UPCAP_ID 0x6401
#define MLXSW_UPCAP_LEN 0x8

uint8_t mlxsw_reg_upcap_local_port_get(const char *buf);

void mlxsw_reg_upcap_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upcap_lp_msb_get(const char *buf);

void mlxsw_reg_upcap_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upcap_side_get(const char *buf);

void mlxsw_reg_upcap_side_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upcap_device_type_get(const char *buf);

uint8_t mlxsw_reg_upcap_gb_get(const char *buf);

uint8_t mlxsw_reg_upcap_crypto_selftest_failed_get(const char *buf);

uint8_t mlxsw_reg_upcap_mcs_get(const char *buf);

uint16_t mlxsw_reg_upcap_uengine_get(const char *buf);

/* ugcr
 * ----
 *
 */
#define MLXSW_UGCR_ID 0x6402
#define MLXSW_UGCR_LEN 0x10

uint8_t mlxsw_reg_ugcr_utrap_trunc_get(const char *buf);

void mlxsw_reg_ugcr_utrap_trunc_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_ugcr_pn_thr_get(const char *buf);

void mlxsw_reg_ugcr_pn_thr_set(char *buf, uint32_t val);

uint64_t mlxsw_reg_ugcr_xpn_pn_thr_get(const char *buf);

void mlxsw_reg_ugcr_xpn_pn_thr_set(char *buf, uint64_t val);

/* upcon
 * -----
 *
 */
#define MLXSW_UPCON_ID 0x6403
#define MLXSW_UPCON_LEN 0xc

uint8_t mlxsw_reg_upcon_local_port_get(const char *buf);

void mlxsw_reg_upcon_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upcon_lp_msb_get(const char *buf);

void mlxsw_reg_upcon_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upcon_side_get(const char *buf);

void mlxsw_reg_upcon_side_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upcon_sec_en_get(const char *buf);

void mlxsw_reg_upcon_sec_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upcon_dpol_get(const char *buf);

void mlxsw_reg_upcon_dpol_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upcon_fl_get(const char *buf);

void mlxsw_reg_upcon_fl_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upcon_inner_en_get(const char *buf);

void mlxsw_reg_upcon_inner_en_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_upcon_sci_port_id_get(const char *buf);

void mlxsw_reg_upcon_sci_port_id_set(char *buf, uint16_t val);

/* umtu
 * ----
 *
 */
#define MLXSW_UMTU_ID 0x6404
#define MLXSW_UMTU_LEN 0x8

uint8_t mlxsw_reg_umtu_local_port_get(const char *buf);

void mlxsw_reg_umtu_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_umtu_lp_msb_get(const char *buf);

void mlxsw_reg_umtu_lp_msb_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_umtu_admin_mtu_get(const char *buf);

void mlxsw_reg_umtu_admin_mtu_set(char *buf, uint16_t val);

/* uver
 * ----
 *
 */
#define MLXSW_UVER_ID 0x6410
#define MLXSW_UVER_LEN 0x8

uint16_t mlxsw_reg_uver_ether_type0_get(const char *buf);

void mlxsw_reg_uver_ether_type0_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_uver_ether_type1_get(const char *buf);

void mlxsw_reg_uver_ether_type1_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_uver_ether_type2_get(const char *buf);

void mlxsw_reg_uver_ether_type2_set(char *buf, uint16_t val);

/* upvc
 * ----
 *
 */
#define MLXSW_UPVC_ID 0x6411
#define MLXSW_UPVC_LEN 0x8

uint8_t mlxsw_reg_upvc_local_port_get(const char *buf);

void mlxsw_reg_upvc_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upvc_lp_msb_get(const char *buf);

void mlxsw_reg_upvc_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upvc_side_get(const char *buf);

void mlxsw_reg_upvc_side_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upvc_inner_et2_get(const char *buf);

void mlxsw_reg_upvc_inner_et2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upvc_et2_get(const char *buf);

void mlxsw_reg_upvc_et2_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upvc_inner_et1_get(const char *buf);

void mlxsw_reg_upvc_inner_et1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upvc_et1_get(const char *buf);

void mlxsw_reg_upvc_et1_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upvc_inner_et0_get(const char *buf);

void mlxsw_reg_upvc_inner_et0_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upvc_et0_get(const char *buf);

void mlxsw_reg_upvc_et0_set(char *buf, uint8_t val);

/* upaft
 * -----
 *
 */
#define MLXSW_UPAFT_ID 0x6412
#define MLXSW_UPAFT_LEN 0x8

uint8_t mlxsw_reg_upaft_local_port_get(const char *buf);

void mlxsw_reg_upaft_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upaft_lp_msb_get(const char *buf);

void mlxsw_reg_upaft_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upaft_side_get(const char *buf);

void mlxsw_reg_upaft_side_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upaft_allow_untagged_get(const char *buf);

void mlxsw_reg_upaft_allow_untagged_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upaft_allow_single_prio_tagged_get(const char *buf);

void mlxsw_reg_upaft_allow_single_prio_tagged_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upaft_allow_single_tagged_get(const char *buf);

void mlxsw_reg_upaft_allow_single_tagged_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upaft_allow_double_tagged_get(const char *buf);

void mlxsw_reg_upaft_allow_double_tagged_set(char *buf, uint8_t val);

/* utar
 * ----
 *
 */
#define MLXSW_UTAR_ID 0x6428
#define MLXSW_UTAR_LEN 0xc

uint16_t mlxsw_reg_utar_uengine_get(const char *buf);

void mlxsw_reg_utar_uengine_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_utar_region_id_get(const char *buf);

void mlxsw_reg_utar_region_id_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_utar_offset_get(const char *buf);

void mlxsw_reg_utar_offset_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_utar_size_get(const char *buf);

void mlxsw_reg_utar_size_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_utar_key_size_get(const char *buf);

void mlxsw_reg_utar_key_size_set(char *buf, uint8_t val);

/* upbt
 * ----
 *
 */
#define MLXSW_UPBT_ID 0x6420
#define MLXSW_UPBT_LEN 0x1c

uint8_t mlxsw_reg_upbt_local_port_get(const char *buf);

void mlxsw_reg_upbt_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upbt_lp_msb_get(const char *buf);

void mlxsw_reg_upbt_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upbt_side_get(const char *buf);

void mlxsw_reg_upbt_side_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upbt_lookup_get(const char *buf);

void mlxsw_reg_upbt_lookup_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_upbt_region_id_get(const char *buf);

void mlxsw_reg_upbt_region_id_set(char *buf, uint16_t val);

void mlxsw_reg_upbt_utcam_key_id_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_upbt_utcam_key_id_memcpy_to(char *buf, const char *src);

uint8_t mlxsw_reg_upbt_op_get(const char *buf);

void mlxsw_reg_upbt_op_set(char *buf, uint8_t val);

/* utce
 * ----
 *
 */
#define MLXSW_UTCE_ID 0x6422
#define MLXSW_UTCE_LEN 0x84

uint16_t mlxsw_reg_utce_uengine_get(const char *buf);

void mlxsw_reg_utce_uengine_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_utce_offset_get(const char *buf);

void mlxsw_reg_utce_offset_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_utce_oper_get(const char *buf);

void mlxsw_reg_utce_oper_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utce_lk_get(const char *buf);

void mlxsw_reg_utce_lk_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utce_v_get(const char *buf);

void mlxsw_reg_utce_v_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_utce_region_id_get(const char *buf);

void mlxsw_reg_utce_region_id_set(char *buf, uint16_t val);

void mlxsw_reg_utce_sec_key_blocks_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_utce_sec_key_blocks_memcpy_to(char *buf, const char *src);

void mlxsw_reg_utce_mask_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_utce_mask_memcpy_to(char *buf, const char *src);

uint8_t mlxsw_reg_utce_utce_first_lookup_forwarding_get(const char *buf);

void mlxsw_reg_utce_utce_first_lookup_forwarding_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utce_utce_first_lookup_to_utrap_get(const char *buf);

void mlxsw_reg_utce_utce_first_lookup_to_utrap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utce_utce_first_lookup_ucheck_id_get(const char *buf);

void mlxsw_reg_utce_utce_first_lookup_ucheck_id_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utce_utce_first_lookup_validate_frames_get(const char *buf);

void mlxsw_reg_utce_utce_first_lookup_validate_frames_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utce_utce_first_lookup_anchor_sec_tag_type_get(const char *buf);

void mlxsw_reg_utce_utce_first_lookup_anchor_sec_tag_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utce_utce_first_lookup_encr_clear_tag_get(const char *buf);

void mlxsw_reg_utce_utce_first_lookup_encr_clear_tag_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_utce_utce_first_lookup_secy_get(const char *buf);

void mlxsw_reg_utce_utce_first_lookup_secy_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_utce_utce_first_lookup_utcam_counter_en_get(const char *buf);

void mlxsw_reg_utce_utce_first_lookup_utcam_counter_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utce_utce_first_lookup_utcam_counter_idx_get(const char *buf);

void mlxsw_reg_utce_utce_first_lookup_utcam_counter_idx_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utce_utce_second_lookup_forwarding_get(const char *buf);

void mlxsw_reg_utce_utce_second_lookup_forwarding_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utce_utce_second_lookup_to_utrap_get(const char *buf);

void mlxsw_reg_utce_utce_second_lookup_to_utrap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utce_utce_second_lookup_ucheck_id_get(const char *buf);

void mlxsw_reg_utce_utce_second_lookup_ucheck_id_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_utce_utce_second_lookup_sadb_entry_ptr_get(const char *buf);

void mlxsw_reg_utce_utce_second_lookup_sadb_entry_ptr_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_utce_utce_second_lookup_utcam_counter_en_get(const char *buf);

void mlxsw_reg_utce_utce_second_lookup_utcam_counter_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utce_utce_second_lookup_utcam_counter_idx_get(const char *buf);

void mlxsw_reg_utce_utce_second_lookup_utcam_counter_idx_set(char *buf, uint8_t val);

/* urcr
 * ----
 *
 */
#define MLXSW_URCR_ID 0x6423
#define MLXSW_URCR_LEN 0x10

uint16_t mlxsw_reg_urcr_uengine_get(const char *buf);

void mlxsw_reg_urcr_uengine_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_urcr_src_region_id_get(const char *buf);

void mlxsw_reg_urcr_src_region_id_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_urcr_src_offset_get(const char *buf);

void mlxsw_reg_urcr_src_offset_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_urcr_oper_get(const char *buf);

void mlxsw_reg_urcr_oper_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_urcr_size_get(const char *buf);

void mlxsw_reg_urcr_size_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_urcr_dest_region_id_get(const char *buf);

void mlxsw_reg_urcr_dest_region_id_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_urcr_dest_offset_get(const char *buf);

void mlxsw_reg_urcr_dest_offset_set(char *buf, uint16_t val);

/* usadb
 * -----
 *
 */
#define MLXSW_USADB_ID 0x6424
#define MLXSW_USADB_LEN 0x34

uint16_t mlxsw_reg_usadb_uengine_get(const char *buf);

void mlxsw_reg_usadb_uengine_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_usadb_sadb_entry_index_get(const char *buf);

void mlxsw_reg_usadb_sadb_entry_index_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_usadb_op_get(const char *buf);

void mlxsw_reg_usadb_op_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_usadb_key_size_get(const char *buf);

void mlxsw_reg_usadb_key_size_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_usadb_cipher_type_get(const char *buf);

void mlxsw_reg_usadb_cipher_type_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_usadb_usadb_encr_gcm_aes_an_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_an_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_usadb_usadb_encr_gcm_aes_tci_sc_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_tci_sc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_usadb_usadb_encr_gcm_aes_tci_e_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_tci_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_usadb_usadb_encr_gcm_aes_tci_c_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_tci_c_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_usadb_usadb_encr_gcm_aes_policy_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_policy_set(char *buf, uint8_t val);

uint64_t mlxsw_reg_usadb_usadb_encr_gcm_aes_sci_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_sci_set(char *buf, uint64_t val);

uint32_t mlxsw_reg_usadb_usadb_encr_gcm_aes_next_pn_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_next_pn_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_usadb_usadb_encr_gcm_aes_conf_offset_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_conf_offset_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_an_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_an_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_tci_sc_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_tci_sc_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_tci_e_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_tci_e_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_tci_c_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_tci_c_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_policy_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_policy_set(char *buf, uint8_t val);

uint64_t mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_sci_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_sci_set(char *buf, uint64_t val);

uint64_t mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_next_pn_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_next_pn_set(char *buf, uint64_t val);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_salt_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_salt_memcpy_to(char *buf, const char *src);

uint32_t mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_ssci_get(const char *buf);

void mlxsw_reg_usadb_usadb_encr_gcm_aes_xpn_ssci_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_usadb_usadb_decr_gcm_aes_rpe_get(const char *buf);

void mlxsw_reg_usadb_usadb_decr_gcm_aes_rpe_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_usadb_usadb_decr_gcm_aes_policy_get(const char *buf);

void mlxsw_reg_usadb_usadb_decr_gcm_aes_policy_set(char *buf, uint8_t val);

uint64_t mlxsw_reg_usadb_usadb_decr_gcm_aes_sci_get(const char *buf);

void mlxsw_reg_usadb_usadb_decr_gcm_aes_sci_set(char *buf, uint64_t val);

uint32_t mlxsw_reg_usadb_usadb_decr_gcm_aes_next_pn_get(const char *buf);

void mlxsw_reg_usadb_usadb_decr_gcm_aes_next_pn_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_usadb_usadb_decr_gcm_aes_conf_offset_get(const char *buf);

void mlxsw_reg_usadb_usadb_decr_gcm_aes_conf_offset_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_usadb_usadb_decr_gcm_aes_replay_window_size_get(const char *buf);

void mlxsw_reg_usadb_usadb_decr_gcm_aes_replay_window_size_set(char *buf, uint32_t val);

uint8_t mlxsw_reg_usadb_usadb_decr_gcm_aes_xpn_rpe_get(const char *buf);

void mlxsw_reg_usadb_usadb_decr_gcm_aes_xpn_rpe_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_usadb_usadb_decr_gcm_aes_xpn_policy_get(const char *buf);

void mlxsw_reg_usadb_usadb_decr_gcm_aes_xpn_policy_set(char *buf, uint8_t val);

uint32_t mlxsw_reg_usadb_usadb_decr_gcm_aes_xpn_ssci_get(const char *buf);

void mlxsw_reg_usadb_usadb_decr_gcm_aes_xpn_ssci_set(char *buf, uint32_t val);

uint64_t mlxsw_reg_usadb_usadb_decr_gcm_aes_xpn_next_pn_get(const char *buf);

void mlxsw_reg_usadb_usadb_decr_gcm_aes_xpn_next_pn_set(char *buf, uint64_t val);

void mlxsw_reg_usadb_usadb_decr_gcm_aes_xpn_salt_memcpy_from(const char *buf, char *dst);

void mlxsw_reg_usadb_usadb_decr_gcm_aes_xpn_salt_memcpy_to(char *buf, const char *src);

uint32_t mlxsw_reg_usadb_usadb_decr_gcm_aes_xpn_replay_window_size_get(const char *buf);

void mlxsw_reg_usadb_usadb_decr_gcm_aes_xpn_replay_window_size_set(char *buf, uint32_t val);

/* usak
 * ----
 *
 */
#define MLXSW_USAK_ID 0x6425
#define MLXSW_USAK_LEN 0x24

uint16_t mlxsw_reg_usak_uengine_get(const char *buf);

void mlxsw_reg_usak_uengine_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_usak_sadb_entry_index_get(const char *buf);

void mlxsw_reg_usak_sadb_entry_index_set(char *buf, uint16_t val);

void mlxsw_reg_usak_sa_key_memcpy_to(char *buf, const char *src);

/* usacn
 * -----
 *
 */
#define MLXSW_USACN_ID 0x6426
#define MLXSW_USACN_LEN 0x28

uint16_t mlxsw_reg_usacn_uengine_get(const char *buf);

void mlxsw_reg_usacn_uengine_set(char *buf, uint16_t val);

uint16_t mlxsw_reg_usacn_sadb_entry_index_get(const char *buf);

void mlxsw_reg_usacn_sadb_entry_index_set(char *buf, uint16_t val);

uint8_t mlxsw_reg_usacn_clear_get(const char *buf);

void mlxsw_reg_usacn_clear_set(char *buf, uint8_t val);

uint64_t mlxsw_reg_usacn_in_pkts_unchecked_get(const char *buf);

uint64_t mlxsw_reg_usacn_in_pkts_late_get(const char *buf);

uint64_t mlxsw_reg_usacn_in_pkts_ok_get(const char *buf);

uint64_t mlxsw_reg_usacn_in_pkts_not_valid_get(const char *buf);

/* utcc
 * ----
 *
 */
#define MLXSW_UTCC_ID 0x6427
#define MLXSW_UTCC_LEN 0x88

uint8_t mlxsw_reg_utcc_local_port_get(const char *buf);

void mlxsw_reg_utcc_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utcc_lp_msb_get(const char *buf);

void mlxsw_reg_utcc_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utcc_side_get(const char *buf);

void mlxsw_reg_utcc_side_set(char *buf, uint8_t val);

uint16_t mlxsw_reg_utcc_clear_bitmap_get(const char *buf);

void mlxsw_reg_utcc_clear_bitmap_set(char *buf, uint16_t val);

uint64_t mlxsw_reg_utcc_counter_get(const char *buf, unsigned short outer_index, unsigned short index);

/* upcnt
 * -----
 *
 */
#define MLXSW_UPCNT_ID 0x6430
#define MLXSW_UPCNT_LEN 0x68

uint8_t mlxsw_reg_upcnt_clear_get(const char *buf);

void mlxsw_reg_upcnt_clear_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upcnt_local_port_get(const char *buf);

void mlxsw_reg_upcnt_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upcnt_lp_msb_get(const char *buf);

void mlxsw_reg_upcnt_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_upcnt_grp_get(const char *buf);

void mlxsw_reg_upcnt_grp_set(char *buf, uint8_t val);

uint64_t mlxsw_reg_upcnt_in_pkts_mtu_get(const char *buf);

uint64_t mlxsw_reg_upcnt_in_pkts_general_get(const char *buf);

uint64_t mlxsw_reg_upcnt_out_pkts_general_get(const char *buf);

uint64_t mlxsw_reg_upcnt_in_pn_overflow_get(const char *buf);

uint64_t mlxsw_reg_upcnt_out_pn_overflow_get(const char *buf);

uint64_t mlxsw_reg_upcnt_in_pause_pfc_get(const char *buf);

uint64_t mlxsw_reg_upcnt_out_pause_pfc_get(const char *buf);

uint64_t mlxsw_reg_upcnt_in_eapol_get(const char *buf);

uint64_t mlxsw_reg_upcnt_out_eapol_get(const char *buf);

uint64_t mlxsw_reg_upcnt_in_buffer_overflow_get(const char *buf);

uint64_t mlxsw_reg_upcnt_in_pkts_untagged_get(const char *buf);

uint64_t mlxsw_reg_upcnt_in_pkts_no_tag_get(const char *buf);

uint64_t mlxsw_reg_upcnt_in_pkts_bad_tag_get(const char *buf);

uint64_t mlxsw_reg_upcnt_in_pkts_no_sa_rcv_get(const char *buf);

uint64_t mlxsw_reg_upcnt_in_pkts_no_sa_discard_get(const char *buf);

uint64_t mlxsw_reg_upcnt_in_octets_validated_get(const char *buf);

uint64_t mlxsw_reg_upcnt_in_octets_decrypted_get(const char *buf);

uint64_t mlxsw_reg_upcnt_in_pkts_too_long_get(const char *buf);

uint64_t mlxsw_reg_upcnt_out_pkts_untagged_get(const char *buf);

uint64_t mlxsw_reg_upcnt_out_pkts_too_long_get(const char *buf);

uint64_t mlxsw_reg_upcnt_out_octets_protected_get(const char *buf);

uint64_t mlxsw_reg_upcnt_out_octets_encrypted_get(const char *buf);

/* uccr
 * ----
 *
 */
#define MLXSW_UCCR_ID 0x6450
#define MLXSW_UCCR_LEN 0x8

uint8_t mlxsw_reg_uccr_side_get(const char *buf);

void mlxsw_reg_uccr_side_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_uccr_count_en_get(const char *buf);

void mlxsw_reg_uccr_count_en_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_uccr_forwarding_get(const char *buf);

void mlxsw_reg_uccr_forwarding_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_uccr_to_utrap_get(const char *buf);

void mlxsw_reg_uccr_to_utrap_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_uccr_ucheck_id_get(const char *buf);

void mlxsw_reg_uccr_ucheck_id_set(char *buf, uint8_t val);

/* utfd
 * ----
 *
 */
#define MLXSW_UTFD_ID 0x6451
#define MLXSW_UTFD_LEN 0xf8

uint8_t mlxsw_reg_utfd_local_port_get(const char *buf);

void mlxsw_reg_utfd_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utfd_lp_msb_get(const char *buf);

void mlxsw_reg_utfd_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utfd_side_get(const char *buf);

void mlxsw_reg_utfd_side_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utfd_ucheck_id_get(const char *buf);

uint16_t mlxsw_reg_utfd_pending_packets_get(const char *buf);

uint8_t mlxsw_reg_utfd_frag_type_get(const char *buf);

uint16_t mlxsw_reg_utfd_frag_size_get(const char *buf);

uint32_t mlxsw_reg_utfd_time_stamp_sec_get(const char *buf);

uint32_t mlxsw_reg_utfd_time_stamp_nsec_get(const char *buf);

uint8_t mlxsw_reg_utfd_sec_act_get(const char *buf);

uint8_t mlxsw_reg_utfd_secy_v_get(const char *buf);

uint16_t mlxsw_reg_utfd_secy_get(const char *buf);

uint8_t mlxsw_reg_utfd_sadb_v_get(const char *buf);

uint16_t mlxsw_reg_utfd_sadb_entry_index_get(const char *buf);

uint32_t mlxsw_reg_utfd_data_get(const char *buf, unsigned short outer_index, unsigned short index);

/* utfc
 * ----
 *
 */
#define MLXSW_UTFC_ID 0x6452
#define MLXSW_UTFC_LEN 0x10

uint8_t mlxsw_reg_utfc_clear_get(const char *buf);

void mlxsw_reg_utfc_clear_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utfc_local_port_get(const char *buf);

void mlxsw_reg_utfc_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utfc_lp_msb_get(const char *buf);

void mlxsw_reg_utfc_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_utfc_side_get(const char *buf);

void mlxsw_reg_utfc_side_set(char *buf, uint8_t val);

uint64_t mlxsw_reg_utfc_utrapf_dropped_get(const char *buf);

/* uter
 * ----
 *
 */
#define MLXSW_UTER_ID 0x6453
#define MLXSW_UTER_LEN 0x30

uint8_t mlxsw_reg_uter_local_port_get(const char *buf);

void mlxsw_reg_uter_local_port_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_uter_lp_msb_get(const char *buf);

void mlxsw_reg_uter_lp_msb_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_uter_side_get(const char *buf);

void mlxsw_reg_uter_side_set(char *buf, uint8_t val);

uint8_t mlxsw_reg_uter_ucheck_id_get(const char *buf);

uint16_t mlxsw_reg_uter_pending_entries_get(const char *buf);

uint32_t mlxsw_reg_uter_time_stamp_sec_get(const char *buf);

uint32_t mlxsw_reg_uter_time_stamp_nsec_get(const char *buf);

uint16_t mlxsw_reg_uter_uengine_get(const char *buf);

uint16_t mlxsw_reg_uter_sadb_entry_index_get(const char *buf);



#endif /* _MLXSW_REG_H */
