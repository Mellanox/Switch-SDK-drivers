/*
* Copyright (c) 2008-2021,  Mellanox Technologies. All rights reserved.
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

#include <linux/string.h>
#include <stdbool.h>
#include <linux/mlx_sx/auto_registers/mlxsw_item.h>
#include <linux/mlx_sx/auto_registers/reg.h>

/************************************************
 *  Global variables
 ***********************************************/


/************************************************
 *  Local variables
 ***********************************************/

/************************************************
 *  Local function declarations
 ***********************************************/


/************************************************
 *  Function implementations
 ***********************************************/
/* fmtc
 * ----
 *
 */
/* emt_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fmtc, emt_index, 0x3, 0, 8);

/* length
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, length, 0xb, 0, 8);

/* update_geneve_length
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, update_geneve_length, 0x12, 0, 1);

/* update_udp_tcp_length
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, update_udp_tcp_length, 0x13, 4, 1);

/* update_hbh_length
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, update_hbh_length, 0x13, 2, 1);

/* update_ipv6_length
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, update_ipv6_length, 0x13, 1, 1);

/* update_ipv4_length
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, update_ipv4_length, 0x13, 0, 1);

/* update_udp_tcp_cs
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, update_udp_tcp_cs, 0x17, 4, 1);

/* clear_udp_cs
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, clear_udp_cs, 0x17, 0, 1);

/* max_latency
 * Access: RW
 */
MLXSW_ITEM16(reg, fmtc, max_latency, 0x22, 0, 9);

/* latency_invalid_value
 * Access: RW
 */
MLXSW_ITEM32(reg, fmtc, latency_invalid_value, 0x24, 0, 32);

/* buffer_fill_level_invalid_value
 * Access: RW
 */
MLXSW_ITEM32(reg, fmtc, buffer_fill_level_invalid_value, 0x28, 0, 32);

/* enc_l2_ipv4_usip
 * Access: RW
 */
MLXSW_ITEM32(reg, fmtc, enc_l2_ipv4_usip, 0x30, 0, 32);

/* enc_next_header
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, enc_next_header, 0x3d, 0, 8);

/* enc_l2_ipv6_usip
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, fmtc, enc_l2_ipv6_usip, 0x40, 0, 32, 4, 0, false);

/* enc_flc
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, enc_flc, 0x50, 1, 1);

/* enc_flh
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, enc_flh, 0x50, 0, 1);

/* enc_fl_prefix
 * Access: RW
 */
MLXSW_ITEM32(reg, fmtc, enc_fl_prefix, 0x50, 8, 12);

/* enc_fl_suffix
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, enc_fl_suffix, 0x53, 0, 8);

/* icsr
 * ----
 *
 */
/* base_address
 * Access: INDEX
 */
MLXSW_ITEM32(reg, icsr, base_address, 0x4, 0, 32);

/* num_reads
 * Access: OP
 */
MLXSW_ITEM16(reg, icsr, num_reads, 0xa, 0, 9);

/* data
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, icsr, data, 0x10, 0, 32, 4, 0, false);

/* iicr
 * ----
 *
 */
/* kvh_mark_clear
 * Access: OP
 */
MLXSW_ITEM8(reg, iicr, kvh_mark_clear, 0xb, 0, 4);

/* clear_mc_rtr_tcam_value
 * Access: RW
 */
MLXSW_ITEM8(reg, iicr, clear_mc_rtr_tcam_value, 0xf, 4, 2);

/* clear_mc_rtr_tcam_mask
 * Access: RW
 */
MLXSW_ITEM8(reg, iicr, clear_mc_rtr_tcam_mask, 0xf, 0, 2);

/* clear_pe_regions_value
 * Access: OP
 */
MLXSW_ITEM16(reg, iicr, clear_pe_regions_value, 0x12, 0, 16);

/* clear_pe_regions_mask
 * Access: OP
 */
MLXSW_ITEM16(reg, iicr, clear_pe_regions_mask, 0x16, 0, 16);

/* clear_rifs_value
 * Access: OP
 */
MLXSW_ITEM16(reg, iicr, clear_rifs_value, 0x1a, 0, 16);

/* clear_rifs_mask
 * Access: OP
 */
MLXSW_ITEM16(reg, iicr, clear_rifs_mask, 0x1e, 0, 16);

/* traps_2_default
 * Access: OP
 */
MLXSW_ITEM8(reg, iicr, traps_2_default, 0x23, 0, 1);

/* fpums
 * -----
 *
 */
/* global
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fpums, global, 0x0, 4, 2);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fpums, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fpums, lp_msb, 0x2, 4, 2);

/* mask
 * Access: OP
 */
MLXSW_ITEM8(reg, fpums, mask, 0xb, 0, 8);

/* port_user_mem
 * Access: RW
 */
MLXSW_ITEM8(reg, fpums, port_user_mem, 0xf, 0, 8);

/* port_mask
 * Access: INDEX
 */
MLXSW_ITEM32_INDEXED(reg, fpums, port_mask, 0x10, 0, 32, 4, 0, false);

/* spevet
 * ------
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, spevet, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, spevet, lp_msb, 0x2, 4, 2);

/* et_vlan
 * Access: RW
 */
MLXSW_ITEM8(reg, spevet, et_vlan, 0x5, 0, 2);

/* igcr
 * ----
 *
 */
/* ddd_lpm_high_ipv6
 * Access: RW
 */
MLXSW_ITEM8(reg, igcr, ddd_lpm_high_ipv6, 0x1, 0, 8);

/* ddd_lpm_high_ipv4
 * Access: RW
 */
MLXSW_ITEM8(reg, igcr, ddd_lpm_high_ipv4, 0x3, 0, 8);

/* ddd_pe_actions_priority
 * Access: RW
 */
MLXSW_ITEM32(reg, igcr, ddd_pe_actions_priority, 0x8, 0, 24);

/* pisbo
 * Access: RW
 */
MLXSW_ITEM8(reg, igcr, pisbo, 0xf, 0, 1);

/* pemrbt
 * ------
 *
 */
/* protocol
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pemrbt, protocol, 0x3, 0, 1);

/* group_id
 * Access: RW
 */
MLXSW_ITEM16(reg, pemrbt, group_id, 0x12, 0, 16);

/* fmte
 * ----
 *
 */
/* emt_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fmte, emt_index, 0x3, 0, 8);

/* entry_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fmte, entry_index, 0x7, 0, 8);

/* cmd_id
 * Access: RW
 */
MLXSW_ITEM8(reg, fmte, cmd_id, 0xb, 0, 8);

/* imm
 * Access: RW
 */
MLXSW_ITEM16(reg, fmte, imm, 0xe, 0, 16);

/* edit_en
 * Access: RW
 */
MLXSW_ITEM8(reg, fmte, edit_en, 0x13, 0, 1);

/* fphhc
 * -----
 *
 */
/* hph
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fphhc, hph, 0x3, 0, 8);

/* my_ftlv_outer_en
 * Access: RW
 */
MLXSW_ITEM8(reg, fphhc, my_ftlv_outer_en, 0x8, 7, 1);

/* my_ftlv_inner_en
 * Access: RW
 */
MLXSW_ITEM8(reg, fphhc, my_ftlv_inner_en, 0x8, 6, 1);

/* my_ftlv_fpp
 * Access: RW
 */
MLXSW_ITEM8(reg, fphhc, my_ftlv_fpp, 0xb, 0, 8);

/* pecnee
 * ------
 *
 */
/* region_id
 * Access: RW
 */
MLXSW_ITEM16(reg, pecnee, region_id, 0xa, 0, 16);

/* region_id_mask
 * Access: RW
 */
MLXSW_ITEM16(reg, pecnee, region_id_mask, 0xe, 0, 16);

/* erp_id_bitwise
 * Access: RW
 */
MLXSW_ITEM16(reg, pecnee, erp_id_bitwise, 0x12, 0, 16);

/* ctcam
 * Access: RW
 */
MLXSW_ITEM8(reg, pecnee, ctcam, 0x17, 0, 1);

/* mtmp
 * ----
 *
 */
/* i
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mtmp, i, 0x0, 7, 1);

/* ig
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mtmp, ig, 0x0, 5, 2);

/* asic_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mtmp, asic_index, 0x0, 1, 4);

/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mtmp, slot_index, 0x1, 0, 4);

/* sensor_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, mtmp, sensor_index, 0x2, 0, 12);

/* max_operational_temperature
 * Access: RO
 */
MLXSW_ITEM16(reg, mtmp, max_operational_temperature, 0x4, 0, 16);

/* temperature
 * Access: RO
 */
MLXSW_ITEM16(reg, mtmp, temperature, 0x6, 0, 16);

/* mte
 * Access: RW
 */
MLXSW_ITEM8(reg, mtmp, mte, 0x8, 7, 1);

/* mtr
 * Access: OP
 */
MLXSW_ITEM8(reg, mtmp, mtr, 0x8, 6, 1);

/* weme
 * Access: OP
 */
MLXSW_ITEM8(reg, mtmp, weme, 0x8, 5, 1);

/* sdme
 * Access: OP
 */
MLXSW_ITEM8(reg, mtmp, sdme, 0x8, 4, 1);

/* max_temperature
 * Access: RO
 */
MLXSW_ITEM16(reg, mtmp, max_temperature, 0xa, 0, 16);

/* tee
 * Access: RW
 */
MLXSW_ITEM8(reg, mtmp, tee, 0xc, 6, 2);

/* sdee
 * Access: RW
 */
MLXSW_ITEM8(reg, mtmp, sdee, 0xc, 4, 2);

/* temperature_threshold_hi
 * Access: RW
 */
MLXSW_ITEM16(reg, mtmp, temperature_threshold_hi, 0xe, 0, 16);

/* temperature_threshold_lo
 * Access: RW
 */
MLXSW_ITEM16(reg, mtmp, temperature_threshold_lo, 0x12, 0, 16);

/* sensor_name_hi
 * Access: RO
 */
MLXSW_ITEM32(reg, mtmp, sensor_name_hi, 0x18, 0, 32);

/* sensor_name_lo
 * Access: RO
 */
MLXSW_ITEM32(reg, mtmp, sensor_name_lo, 0x1c, 0, 32);

/* tieem
 * -----
 *
 */
/* overlay_ecn
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tieem, overlay_ecn, 0x4, 0, 2);

/* underlay_ecn
 * Access: RW
 */
MLXSW_ITEM8(reg, tieem, underlay_ecn, 0x5, 0, 2);

/* pmsc
 * ----
 *
 */
/* port_mapping_updated
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, pmsc, port_mapping_updated, 0x0, 0, 32, 4, 0, false);

/* mogcr
 * -----
 *
 */
/* tele_managed
 * Access: RW
 */
MLXSW_ITEM8(reg, mogcr, tele_managed, 0x2, 0, 1);

/* ptp_iftc
 * Access: RW
 */
MLXSW_ITEM8(reg, mogcr, ptp_iftc, 0x3, 1, 1);

/* ptp_eftc
 * Access: RW
 */
MLXSW_ITEM8(reg, mogcr, ptp_eftc, 0x3, 0, 1);

/* sid
 * Access: RW
 */
MLXSW_ITEM8(reg, mogcr, sid, 0xb, 0, 1);

/* mirroring_pid_base
 * Access: RW
 */
MLXSW_ITEM16(reg, mogcr, mirroring_pid_base, 0xe, 0, 14);

/* mirror_latency_units
 * Access: RW
 */
MLXSW_ITEM16(reg, mogcr, mirror_latency_units, 0x16, 0, 16);

/* latency_histogram_units
 * Access: RW
 */
MLXSW_ITEM16(reg, mogcr, latency_histogram_units, 0x1a, 0, 16);

/* toc_fmt
 * Access: RW
 */
MLXSW_ITEM8(reg, mogcr, toc_fmt, 0x1c, 0, 1);

/* rtdp
 * ----
 *
 */
/* type
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, type, 0x0, 4, 4);

/* tunnel_index
 * Access: INDEX
 */
MLXSW_ITEM32(reg, rtdp, tunnel_index, 0x0, 0, 24);

/* rtdp_nve_decap_decap_disable
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_nve_decap_decap_disable, 0x7, 0, 4);

/* rtdp_ipinip_irif
 * Access: RW
 */
MLXSW_ITEM16(reg, rtdp, rtdp_ipinip_irif, 0x4, 0, 16);

/* rtdp_ipinip_sip_check
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_ipinip_sip_check, 0x7, 0, 3);

/* rtdp_ipinip_type_check
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_ipinip_type_check, 0x8, 0, 3);

/* rtdp_ipinip_gre_key_check
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_ipinip_gre_key_check, 0x9, 7, 1);

/* rtdp_ipinip_ipv4_usip
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, rtdp_ipinip_ipv4_usip, 0xc, 0, 32);

/* rtdp_ipinip_ipv6_usip_ptr
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, rtdp_ipinip_ipv6_usip_ptr, 0x10, 0, 24);

/* rtdp_ipinip_expected_gre_key
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, rtdp_ipinip_expected_gre_key, 0x14, 0, 32);

/* egress_router_interface
 * Access: RW
 */
MLXSW_ITEM16(reg, rtdp, egress_router_interface, 0x42, 0, 16);

/* pecner
 * ------
 *
 */
/* clear
 * Access: OP
 */
MLXSW_ITEM8(reg, pecner, clear, 0x0, 7, 1);

/* erp_initial_high
 * Access: RO
 */
MLXSW_ITEM32(reg, pecner, erp_initial_high, 0x10, 0, 32);

/* erp_initial_low
 * Access: RO
 */
MLXSW_ITEM32(reg, pecner, erp_initial_low, 0x14, 0, 32);

/* erp_post_bf_high
 * Access: RO
 */
MLXSW_ITEM32(reg, pecner, erp_post_bf_high, 0x18, 0, 32);

/* erp_post_bf_low
 * Access: RO
 */
MLXSW_ITEM32(reg, pecner, erp_post_bf_low, 0x1c, 0, 32);

/* erp_lookup_high
 * Access: RO
 */
MLXSW_ITEM32(reg, pecner, erp_lookup_high, 0x20, 0, 32);

/* erp_lookup_low
 * Access: RO
 */
MLXSW_ITEM32(reg, pecner, erp_lookup_low, 0x24, 0, 32);

/* erp_any_match_high
 * Access: RO
 */
MLXSW_ITEM32(reg, pecner, erp_any_match_high, 0x28, 0, 32);

/* erp_any_match_low
 * Access: RO
 */
MLXSW_ITEM32(reg, pecner, erp_any_match_low, 0x2c, 0, 32);

/* erp_final_match_high
 * Access: RO
 */
MLXSW_ITEM32(reg, pecner, erp_final_match_high, 0x30, 0, 32);

/* erp_final_match_low
 * Access: RO
 */
MLXSW_ITEM32(reg, pecner, erp_final_match_low, 0x34, 0, 32);

/* ifbo
 * ----
 *
 */
/* type
 * Access: RW
 */
MLXSW_ITEM8(reg, ifbo, type, 0x3, 0, 4);

/* outer_header_enables
 * Access: RW
 */
MLXSW_ITEM16(reg, ifbo, outer_header_enables, 0x12, 0, 16);

/* outer_header_fields_enable
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, ifbo, outer_header_fields_enable, 0x14, 0, 32, 4, 0, false);

/* tneem
 * -----
 *
 */
/* overlay_ecn
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tneem, overlay_ecn, 0x4, 0, 2);

/* underlay_ecn
 * Access: RW
 */
MLXSW_ITEM8(reg, tneem, underlay_ecn, 0x5, 0, 2);

/* tnifr
 * -----
 *
 */
/* tunnel_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tnifr, tunnel_port, 0x3, 0, 4);

/* port_page
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tnifr, port_page, 0x7, 0, 4);

/* port_filter
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, tnifr, port_filter, 0x20, 0, 32, 4, 0, false);

/* port_filter_update_en
 * Access: OP
 */
MLXSW_ITEM32_INDEXED(reg, tnifr, port_filter_update_en, 0x40, 0, 32, 4, 0, false);

/* peaps
 * -----
 *
 */
/* busy
 * Access: RO
 */
MLXSW_ITEM8(reg, peaps, busy, 0x0, 7, 1);

/* ovf
 * Access: RO
 */
MLXSW_ITEM8(reg, peaps, ovf, 0x0, 6, 1);

/* ct_offset
 * Access: WO
 */
MLXSW_ITEM16(reg, peaps, ct_offset, 0xa, 0, 16);

/* ct_size
 * Access: WO
 */
MLXSW_ITEM16(reg, peaps, ct_size, 0xe, 0, 16);

/* tcam_region_info
 * Access: WO
 */
MLXSW_ITEM_BUF(reg, peaps, tcam_region_info, 0x10, 16);

/* priority_start
 * Access: WO
 */
MLXSW_ITEM32(reg, peaps, priority_start, 0x20, 0, 24);

/* priority_end
 * Access: WO
 */
MLXSW_ITEM32(reg, peaps, priority_end, 0x24, 0, 24);

/* priority_inc
 * Access: WO
 */
MLXSW_ITEM32(reg, peaps, priority_inc, 0x30, 0, 24);

/* pmpe
 * ----
 *
 */
/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmpe, slot_index, 0x0, 0, 4);

/* module
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmpe, module, 0x1, 0, 8);

/* module_status
 * Access: RO
 */
MLXSW_ITEM8(reg, pmpe, module_status, 0x3, 0, 4);

/* error_type
 * Access: RO
 */
MLXSW_ITEM8(reg, pmpe, error_type, 0x6, 0, 4);

/* hcot
 * ----
 *
 */
/* trap_id
 * Access: INDEX
 */
MLXSW_ITEM16(reg, hcot, trap_id, 0x2, 0, 10);

/* key_type
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, key_type, 0x7, 0, 8);

/* key_hcot_key_ethernet_ethertype
 * Access: RW
 */
MLXSW_ITEM16(reg, hcot, key_hcot_key_ethernet_ethertype, 0x12, 0, 16);

/* key_hcot_key_ethernet_tunnel_port
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, key_hcot_key_ethernet_tunnel_port, 0x17, 0, 4);

/* key_hcot_key_next_proto_is_ipv4
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, key_hcot_key_next_proto_is_ipv4, 0x11, 0, 1);

/* key_hcot_key_next_proto_ip_proto
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, key_hcot_key_next_proto_ip_proto, 0x13, 0, 8);

/* key_hcot_key_next_proto_tunnel_port
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, key_hcot_key_next_proto_tunnel_port, 0x17, 0, 4);

/* key_hcot_key_layer4_port_is_udp
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, key_hcot_key_layer4_port_is_udp, 0x11, 1, 1);

/* key_hcot_key_layer4_port_is_ipv4
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, key_hcot_key_layer4_port_is_ipv4, 0x11, 0, 1);

/* key_hcot_key_layer4_port_l4_port
 * Access: RW
 */
MLXSW_ITEM16(reg, hcot, key_hcot_key_layer4_port_l4_port, 0x12, 0, 16);

/* key_hcot_key_layer4_port_tunnel_port
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, key_hcot_key_layer4_port_tunnel_port, 0x17, 0, 4);

/* key_hcot_key_icmp_igmp_type_is_igmp
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, key_hcot_key_icmp_igmp_type_is_igmp, 0x11, 1, 1);

/* key_hcot_key_icmp_igmp_type_is_ipv4
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, key_hcot_key_icmp_igmp_type_is_ipv4, 0x11, 0, 1);

/* key_hcot_key_icmp_igmp_type_max
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, key_hcot_key_icmp_igmp_type_max, 0x12, 0, 8);

/* key_hcot_key_icmp_igmp_type_min
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, key_hcot_key_icmp_igmp_type_min, 0x13, 0, 8);

/* key_hcot_key_icmp_igmp_type_tunnel_port
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, key_hcot_key_icmp_igmp_type_tunnel_port, 0x17, 0, 4);

/* mask_hcot_key_ethernet_ethertype
 * Access: RW
 */
MLXSW_ITEM16(reg, hcot, mask_hcot_key_ethernet_ethertype, 0x22, 0, 16);

/* mask_hcot_key_ethernet_tunnel_port
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, mask_hcot_key_ethernet_tunnel_port, 0x27, 0, 4);

/* mask_hcot_key_next_proto_is_ipv4
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, mask_hcot_key_next_proto_is_ipv4, 0x21, 0, 1);

/* mask_hcot_key_next_proto_ip_proto
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, mask_hcot_key_next_proto_ip_proto, 0x23, 0, 8);

/* mask_hcot_key_next_proto_tunnel_port
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, mask_hcot_key_next_proto_tunnel_port, 0x27, 0, 4);

/* mask_hcot_key_layer4_port_is_udp
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, mask_hcot_key_layer4_port_is_udp, 0x21, 1, 1);

/* mask_hcot_key_layer4_port_is_ipv4
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, mask_hcot_key_layer4_port_is_ipv4, 0x21, 0, 1);

/* mask_hcot_key_layer4_port_l4_port
 * Access: RW
 */
MLXSW_ITEM16(reg, hcot, mask_hcot_key_layer4_port_l4_port, 0x22, 0, 16);

/* mask_hcot_key_layer4_port_tunnel_port
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, mask_hcot_key_layer4_port_tunnel_port, 0x27, 0, 4);

/* mask_hcot_key_icmp_igmp_type_is_igmp
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, mask_hcot_key_icmp_igmp_type_is_igmp, 0x21, 1, 1);

/* mask_hcot_key_icmp_igmp_type_is_ipv4
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, mask_hcot_key_icmp_igmp_type_is_ipv4, 0x21, 0, 1);

/* mask_hcot_key_icmp_igmp_type_max
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, mask_hcot_key_icmp_igmp_type_max, 0x22, 0, 8);

/* mask_hcot_key_icmp_igmp_type_min
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, mask_hcot_key_icmp_igmp_type_min, 0x23, 0, 8);

/* mask_hcot_key_icmp_igmp_type_tunnel_port
 * Access: RW
 */
MLXSW_ITEM8(reg, hcot, mask_hcot_key_icmp_igmp_type_tunnel_port, 0x27, 0, 4);

/* fmtm
 * ----
 *
 */
/* emt_index_in
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtm, emt_index_in, 0x5, 0, 8);

/* emt_index_out
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtm, emt_index_out, 0x7, 0, 8);

/* chltm
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, chltm, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, chltm, lp_msb, 0x2, 4, 2);

/* traffic_class
 * Access: INDEX
 */
MLXSW_ITEM8(reg, chltm, traffic_class, 0x7, 0, 8);

/* hlt_table_pointer
 * Access: RW
 */
MLXSW_ITEM8(reg, chltm, hlt_table_pointer, 0x13, 0, 8);

/* mafti
 * -----
 *
 */
/* bank_id
 * Access: RO
 */
MLXSW_ITEM8(reg, mafti, bank_id, 0x1, 0, 3);

/* num_rec
 * Access: RO
 */
MLXSW_ITEM8(reg, mafti, num_rec, 0x3, 0, 8);

/* counter_index
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mafti, counter_index, MLXSW_MAFTI_RECORD_BASE_LEN, 0, 24, MLXSW_MAFTI_RECORD_REC_LEN, 0, false);

/* bytes_inc
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mafti, bytes_inc, MLXSW_MAFTI_RECORD_BASE_LEN, 0, 32, MLXSW_MAFTI_RECORD_REC_LEN, 4, false);

/* packets_inc
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mafti, packets_inc, MLXSW_MAFTI_RECORD_BASE_LEN, 0, 32, MLXSW_MAFTI_RECORD_REC_LEN, 8, false);

/* hmon
 * ----
 *
 */
/* clr
 * Access: OP
 */
MLXSW_ITEM8(reg, hmon, clr, 0x0, 7, 1);

/* cprdq
 * Access: INDEX
 */
MLXSW_ITEM8(reg, hmon, cprdq, 0x0, 6, 1);

/* crdq
 * Access: INDEX
 */
MLXSW_ITEM8(reg, hmon, crdq, 0x3, 0, 6);

/* wqe_of_wrap
 * Access: RO
 */
MLXSW_ITEM8(reg, hmon, wqe_of_wrap, 0x4, 7, 1);

/* wqe_overflow_high
 * Access: RO
 */
MLXSW_ITEM32(reg, hmon, wqe_overflow_high, 0x10, 0, 32);

/* wqe_overflow_low
 * Access: RO
 */
MLXSW_ITEM32(reg, hmon, wqe_overflow_low, 0x14, 0, 32);

/* hi
 * Access: 
 */
MLXSW_ITEM32_INDEXED(reg, hmon, hi, MLXSW_HMON_WQE_OVERFLOW_RDQ_BASE_LEN, 0, 32, MLXSW_HMON_WQE_OVERFLOW_RDQ_REC_LEN, 0, false);

/* lo
 * Access: 
 */
MLXSW_ITEM32_INDEXED(reg, hmon, lo, MLXSW_HMON_WQE_OVERFLOW_RDQ_BASE_LEN, 0, 32, MLXSW_HMON_WQE_OVERFLOW_RDQ_REC_LEN, 4, false);

/* mgpir
 * -----
 *
 */
/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mgpir, slot_index, 0x0, 4, 4);

/* device_type
 * Access: RO
 */
MLXSW_ITEM8(reg, mgpir, device_type, 0x0, 0, 4);

/* devices_per_flash
 * Access: RO
 */
MLXSW_ITEM8(reg, mgpir, devices_per_flash, 0x1, 0, 8);

/* num_of_devices
 * Access: RO
 */
MLXSW_ITEM8(reg, mgpir, num_of_devices, 0x3, 0, 8);

/* num_of_slots
 * Access: RO
 */
MLXSW_ITEM8(reg, mgpir, num_of_slots, 0x6, 0, 8);

/* num_of_modules
 * Access: RO
 */
MLXSW_ITEM8(reg, mgpir, num_of_modules, 0x7, 0, 8);

/* peapbl
 * ------
 *
 */
/* region_id
 * Access: INDEX
 */
MLXSW_ITEM16(reg, peapbl, region_id, 0x2, 0, 16);

/* c_s
 * Access: WO
 */
MLXSW_ITEM8(reg, peapbl, c_s, 0x10, 7, 1);

/* pruning_ctcam_cs
 * Access: WO
 */
MLXSW_ITEM8(reg, peapbl, pruning_ctcam_cs, 0x10, 4, 1);

/* num_rec
 * Access: WO
 */
MLXSW_ITEM8(reg, peapbl, num_rec, 0x11, 0, 8);

/* erp_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, peapbl, erp_id, 0x13, 0, 4);

/* pruning_vector_cs
 * Access: WO
 */
MLXSW_ITEM16(reg, peapbl, pruning_vector_cs, 0x16, 0, 16);

/* peapbm
 * ------
 *
 */
/* region_id
 * Access: INDEX
 */
MLXSW_ITEM16(reg, peapbm, region_id, 0x2, 0, 16);

/* c_s
 * Access: WO
 */
MLXSW_ITEM8(reg, peapbm, c_s, 0x10, 7, 1);

/* pruning_ctcam_cs
 * Access: WO
 */
MLXSW_ITEM8(reg, peapbm, pruning_ctcam_cs, 0x10, 4, 1);

/* erp_id_mask
 * Access: INDEX
 */
MLXSW_ITEM8(reg, peapbm, erp_id_mask, 0x12, 0, 4);

/* erp_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, peapbm, erp_id, 0x13, 0, 4);

/* pruning_vector_cs
 * Access: WO
 */
MLXSW_ITEM16(reg, peapbm, pruning_vector_cs, 0x16, 0, 16);

/* priority_start
 * Access: INDEX
 */
MLXSW_ITEM32(reg, peapbm, priority_start, 0x18, 0, 24);

/* priority_end
 * Access: INDEX
 */
MLXSW_ITEM32(reg, peapbm, priority_end, 0x1c, 0, 24);

/* key
 * Access: INDEX
 */
MLXSW_ITEM32_INDEXED(reg, peapbm, key, 0x20, 0, 32, 4, 0, false);

/* key_mask
 * Access: INDEX
 */
MLXSW_ITEM32_INDEXED(reg, peapbm, key_mask, 0x80, 0, 32, 4, 0, false);

/* large_entry_key_id
 * Access: INDEX
 */
MLXSW_ITEM32(reg, peapbm, large_entry_key_id, 0xe0, 0, 24);

/* large_entry_key_id_mask
 * Access: INDEX
 */
MLXSW_ITEM32(reg, peapbm, large_entry_key_id_mask, 0xe4, 0, 24);

/* delta_start
 * Access: INDEX
 */
MLXSW_ITEM16(reg, peapbm, delta_start, 0xf2, 0, 10);

/* delta_mask
 * Access: INDEX
 */
MLXSW_ITEM8(reg, peapbm, delta_mask, 0xf5, 0, 8);

/* delta_value
 * Access: INDEX
 */
MLXSW_ITEM8(reg, peapbm, delta_value, 0xf7, 0, 8);

/* pmtm
 * ----
 *
 */
/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmtm, slot_index, 0x0, 0, 4);

/* module
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmtm, module, 0x1, 0, 8);

/* module_width
 * Access: RW
 */
MLXSW_ITEM8(reg, pmtm, module_width, 0x6, 0, 5);

/* module_type
 * Access: RW
 */
MLXSW_ITEM8(reg, pmtm, module_type, 0x7, 0, 5);

/* tnqdr
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tnqdr, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tnqdr, lp_msb, 0x2, 4, 2);

/* color
 * Access: RW
 */
MLXSW_ITEM8(reg, tnqdr, color, 0x4, 0, 2);

/* switch_prio
 * Access: RW
 */
MLXSW_ITEM8(reg, tnqdr, switch_prio, 0x5, 0, 4);

/* dscp
 * Access: RW
 */
MLXSW_ITEM8(reg, tnqdr, dscp, 0x7, 0, 6);

/* sffp
 * ----
 *
 */
/* profile_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sffp, profile_id, 0x1, 0, 2);

/* type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sffp, type, 0x3, 0, 4);

/* flood_offset
 * Access: RW
 */
MLXSW_ITEM8(reg, sffp, flood_offset, 0x7, 0, 3);

/* mpcir
 * -----
 *
 */
/* all
 * Access: OP
 */
MLXSW_ITEM8(reg, mpcir, all, 0x0, 6, 2);

/* gearbox
 * Access: OP
 */
MLXSW_ITEM8(reg, mpcir, gearbox, 0x5, 0, 2);

/* leds
 * Access: OP
 */
MLXSW_ITEM8(reg, mpcir, leds, 0x6, 6, 2);

/* voltage_current
 * Access: OP
 */
MLXSW_ITEM8(reg, mpcir, voltage_current, 0x6, 4, 2);

/* power
 * Access: OP
 */
MLXSW_ITEM8(reg, mpcir, power, 0x6, 2, 2);

/* fans
 * Access: OP
 */
MLXSW_ITEM8(reg, mpcir, fans, 0x6, 0, 2);

/* thermal
 * Access: OP
 */
MLXSW_ITEM8(reg, mpcir, thermal, 0x7, 6, 2);

/* module_mng
 * Access: OP
 */
MLXSW_ITEM8(reg, mpcir, module_mng, 0x7, 4, 2);

/* cpld
 * Access: OP
 */
MLXSW_ITEM8(reg, mpcir, cpld, 0x7, 2, 2);

/* ports
 * Access: OP
 */
MLXSW_ITEM8(reg, mpcir, ports, 0x7, 0, 2);

/* gearbox_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, mpcir, gearbox_stat, 0xd, 0, 2);

/* leds_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, mpcir, leds_stat, 0xe, 6, 2);

/* voltage_current_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, mpcir, voltage_current_stat, 0xe, 4, 2);

/* power_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, mpcir, power_stat, 0xe, 2, 2);

/* fans_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, mpcir, fans_stat, 0xe, 0, 2);

/* thermal_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, mpcir, thermal_stat, 0xf, 6, 2);

/* module_mng_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, mpcir, module_mng_stat, 0xf, 4, 2);

/* cpld_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, mpcir, cpld_stat, 0xf, 2, 2);

/* ports_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, mpcir, ports_stat, 0xf, 0, 2);

/* pter
 * ----
 *
 */
/* error_page
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pter, error_page, 0x0, 0, 4);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pter, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pter, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pter, lp_msb, 0x2, 4, 2);

/* port_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pter, port_type, 0x3, 4, 4);

/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, pter, status, 0x3, 0, 4);

/* pter_phy_page_reg_error_type_oper
 * Access: RO
 */
MLXSW_ITEM8(reg, pter, pter_phy_page_reg_error_type_oper, 0x4, 0, 4);

/* pter_phy_page_reg_error_type_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pter, pter_phy_page_reg_error_type_cap, 0x6, 0, 8);

/* pter_phy_page_reg_error_type_admin
 * Access: RW
 */
MLXSW_ITEM8(reg, pter, pter_phy_page_reg_error_type_admin, 0x7, 0, 8);

/* pter_phy_page_reg_error_injection_time
 * Access: RW
 */
MLXSW_ITEM32(reg, pter, pter_phy_page_reg_error_injection_time, 0x8, 12, 16);

/* pter_phy_page_reg_ber_mantissa
 * Access: RW
 */
MLXSW_ITEM8(reg, pter, pter_phy_page_reg_ber_mantissa, 0xa, 0, 4);

/* pter_phy_page_reg_ber_exp
 * Access: RW
 */
MLXSW_ITEM8(reg, pter, pter_phy_page_reg_ber_exp, 0xb, 0, 8);

/* pter_phy_page_reg_rs_symbol_errors
 * Access: RW
 */
MLXSW_ITEM16(reg, pter, pter_phy_page_reg_rs_symbol_errors, 0xe, 0, 16);

/* pter_phy_page_reg_rs_errors_interval
 * Access: RW
 */
MLXSW_ITEM16(reg, pter, pter_phy_page_reg_rs_errors_interval, 0x12, 0, 16);

/* pter_port_page_reg_error_type_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pter, pter_port_page_reg_error_type_cap, 0x6, 0, 8);

/* pter_port_page_reg_error_type_admin
 * Access: RW
 */
MLXSW_ITEM8(reg, pter, pter_port_page_reg_error_type_admin, 0x7, 0, 8);

/* pter_port_page_reg_error_count
 * Access: RW
 */
MLXSW_ITEM8(reg, pter, pter_port_page_reg_error_count, 0xa, 4, 5);

/* smpu
 * ----
 *
 */
/* swid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, smpu, swid, 0x0, 0, 8);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, smpu, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, smpu, lp_msb, 0x2, 4, 2);

/* op
 * Access: WO
 */
MLXSW_ITEM8(reg, smpu, op, 0x4, 6, 2);

/* size
 * Access: INDEX
 */
MLXSW_ITEM16(reg, smpu, size, 0x4, 0, 9);

/* mid
 * Access: 
 */
MLXSW_ITEM16_INDEXED(reg, smpu, mid, 0x12, 0, 16, 0x4, 0x0, false);

/* cegcr
 * -----
 *
 */
/* f2e
 * Access: RW
 */
MLXSW_ITEM8(reg, cegcr, f2e, 0x3, 2, 1);

/* sticky
 * Access: RW
 */
MLXSW_ITEM8(reg, cegcr, sticky, 0x3, 1, 1);

/* max_floating_time
 * Access: RW
 */
MLXSW_ITEM16(reg, cegcr, max_floating_time, 0x6, 0, 10);

/* reference_rate
 * Access: RW
 */
MLXSW_ITEM32(reg, cegcr, reference_rate, 0x10, 0, 32);

/* elephants_thr
 * Access: RW
 */
MLXSW_ITEM32(reg, cegcr, elephants_thr, 0x14, 0, 20);

/* elephants_max_thr
 * Access: RW
 */
MLXSW_ITEM32(reg, cegcr, elephants_max_thr, 0x18, 0, 20);

/* mice_thr
 * Access: RW
 */
MLXSW_ITEM32(reg, cegcr, mice_thr, 0x1c, 0, 20);

/* pmmp
 * ----
 *
 */
/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmmp, slot_index, 0x0, 0, 4);

/* module
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmmp, module, 0x1, 0, 8);

/* eeprom_override_mask
 * Access: WO
 */
MLXSW_ITEM16(reg, pmmp, eeprom_override_mask, 0x4, 0, 16);

/* eeprom_override
 * Access: RW
 */
MLXSW_ITEM16(reg, pmmp, eeprom_override, 0x6, 0, 16);

/* qsfp_cable_protocol_technology
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, pmmp, qsfp_cable_protocol_technology, 0x8, 0, 32, 4, 0, false);

/* sfp_cable_protocol_technology
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, pmmp, sfp_cable_protocol_technology, 0x14, 0, 32, 4, 0, false);

/* cable_length
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, cable_length, 0x23, 0, 8);

/* attenuation_25g
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, attenuation_25g, 0x24, 0, 8);

/* attenuation_12g
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, attenuation_12g, 0x25, 0, 8);

/* attenuation_7g
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, attenuation_7g, 0x26, 0, 8);

/* attenuation_5g
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, attenuation_5g, 0x27, 0, 8);

/* pecnrr
 * ------
 *
 */
/* clear
 * Access: OP
 */
MLXSW_ITEM8(reg, pecnrr, clear, 0x0, 7, 1);

/* tcam_trigger_high
 * Access: RO
 */
MLXSW_ITEM32(reg, pecnrr, tcam_trigger_high, 0x10, 0, 32);

/* tcam_trigger_low
 * Access: RO
 */
MLXSW_ITEM32(reg, pecnrr, tcam_trigger_low, 0x14, 0, 32);

/* tcam_full_lookup_high
 * Access: RO
 */
MLXSW_ITEM32(reg, pecnrr, tcam_full_lookup_high, 0x18, 0, 32);

/* tcam_full_lookup_low
 * Access: RO
 */
MLXSW_ITEM32(reg, pecnrr, tcam_full_lookup_low, 0x1c, 0, 32);

/* ptcead
 * ------
 *
 */
/* op
 * Access: OP
 */
MLXSW_ITEM8(reg, ptcead, op, 0x0, 6, 2);

/* offset
 * Access: INDEX
 */
MLXSW_ITEM16(reg, ptcead, offset, 0x2, 0, 16);

/* num_rec
 * Access: OP
 */
MLXSW_ITEM16(reg, ptcead, num_rec, 0x6, 0, 13);

/* tcam_region_info
 * Access: INDEX
 */
MLXSW_ITEM_BUF(reg, ptcead, tcam_region_info, 0x10, 16);

/* activity_vector
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, ptcead, activity_vector, 0x20, 0, 32, 4, 0, false);

/* fpftt
 * -----
 *
 */
/* entry_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fpftt, entry_index, 0x3, 0, 8);

/* tran_en
 * Access: RW
 */
MLXSW_ITEM8(reg, fpftt, tran_en, 0x7, 0, 1);

/* cur_ph
 * Access: RW
 */
MLXSW_ITEM8(reg, fpftt, cur_ph, 0xb, 0, 8);

/* next_protocol_value
 * Access: RW
 */
MLXSW_ITEM16(reg, fpftt, next_protocol_value, 0xe, 0, 16);

/* next_ph_inner
 * Access: RW
 */
MLXSW_ITEM8(reg, fpftt, next_ph_inner, 0x11, 0, 1);

/* next_ph
 * Access: RW
 */
MLXSW_ITEM8(reg, fpftt, next_ph, 0x13, 0, 8);

/* mddq
 * ----
 *
 */
/* sie
 * Access: RW
 */
MLXSW_ITEM8(reg, mddq, sie, 0x0, 7, 1);

/* query_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mddq, query_type, 0x1, 0, 8);

/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mddq, slot_index, 0x3, 0, 4);

/* response_message_sequence
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, response_message_sequence, 0x5, 0, 8);

/* request_message_sequence
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mddq, request_message_sequence, 0x7, 0, 8);

/* data_valid
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, data_valid, 0x8, 7, 1);

/* query_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mddq, query_index, 0xb, 0, 8);

/* slot_info_provisioned
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, slot_info_provisioned, 0x10, 7, 1);

/* slot_info_sr_valid
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, slot_info_sr_valid, 0x10, 6, 1);

/* slot_info_lc_ready
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, slot_info_lc_ready, 0x10, 4, 2);

/* slot_info_active
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, slot_info_active, 0x10, 3, 1);

/* slot_info_hw_revision
 * Access: RO
 */
MLXSW_ITEM16(reg, mddq, slot_info_hw_revision, 0x14, 0, 16);

/* slot_info_ini_file_version
 * Access: RO
 */
MLXSW_ITEM16(reg, mddq, slot_info_ini_file_version, 0x16, 0, 16);

/* slot_info_card_type
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, slot_info_card_type, 0x1b, 0, 8);

/* device_info_uses_flash
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, device_info_uses_flash, 0x10, 7, 1);

/* device_info_flash_owner
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, device_info_flash_owner, 0x10, 6, 1);

/* device_info_thermal_sd
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, device_info_thermal_sd, 0x10, 5, 1);

/* device_info_lc_pwr_on
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, device_info_lc_pwr_on, 0x10, 4, 1);

/* device_info_flash_id
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, device_info_flash_id, 0x11, 0, 8);

/* device_info_device_index
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, device_info_device_index, 0x13, 0, 8);

/* device_info_fw_major
 * Access: RO
 */
MLXSW_ITEM16(reg, mddq, device_info_fw_major, 0x14, 0, 16);

/* device_info_device_type
 * Access: RO
 */
MLXSW_ITEM16(reg, mddq, device_info_device_type, 0x16, 0, 16);

/* device_info_fw_minor
 * Access: RO
 */
MLXSW_ITEM16(reg, mddq, device_info_fw_minor, 0x18, 0, 16);

/* device_info_fw_sub_minor
 * Access: RO
 */
MLXSW_ITEM16(reg, mddq, device_info_fw_sub_minor, 0x1a, 0, 16);

/* device_info_max_cmd_read_size_supp
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, device_info_max_cmd_read_size_supp, 0x1e, 0, 8);

/* device_info_max_cmd_write_size_supp
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, device_info_max_cmd_write_size_supp, 0x1f, 0, 8);

/* slot_name_slot_ascii_name
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mddq, slot_name_slot_ascii_name, 0x10, 0, 32, 4, 0, false);

/* tnpc
 * ----
 *
 */
/* tunnel_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tnpc, tunnel_port, 0x3, 0, 4);

/* learn_enable_v4
 * Access: RW
 */
MLXSW_ITEM8(reg, tnpc, learn_enable_v4, 0x7, 0, 1);

/* lb_tx_uc_tunnel_port
 * Access: RW
 */
MLXSW_ITEM32(reg, tnpc, lb_tx_uc_tunnel_port, 0x14, 0, 32);

/* lb_tx_mc_tunnel_port
 * Access: RW
 */
MLXSW_ITEM32(reg, tnpc, lb_tx_mc_tunnel_port, 0x18, 0, 32);

/* pecnre
 * ------
 *
 */
/* region_id
 * Access: RW
 */
MLXSW_ITEM16(reg, pecnre, region_id, 0xa, 0, 16);

/* region_id_mask
 * Access: RW
 */
MLXSW_ITEM16(reg, pecnre, region_id_mask, 0xe, 0, 16);

/* mofs
 * ----
 *
 */
/* type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mofs, type, 0x3, 0, 2);

/* register_id
 * Access: INDEX
 */
MLXSW_ITEM16(reg, mofs, register_id, 0x6, 0, 16);

/* section_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mofs, section_id, 0xa, 0, 8);

/* en
 * Access: RW
 */
MLXSW_ITEM8(reg, mofs, en, 0x11, 0, 1);

/* action
 * Access: WO
 */
MLXSW_ITEM8(reg, mofs, action, 0x13, 0, 2);

/* reg_status
 * Access: RO
 */
MLXSW_ITEM8(reg, mofs, reg_status, 0x17, 0, 2);

/* ralcm
 * -----
 *
 */
/* virtual_router
 * Access: INDEX
 */
MLXSW_ITEM16(reg, ralcm, virtual_router, 0x0, 0, 16);

/* protocol
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ralcm, protocol, 0x2, 4, 4);

/* mgir
 * ----
 *
 */
/* device_hw_revision
 * Access: RO
 */
MLXSW_ITEM16(reg, mgir, device_hw_revision, 0x0, 0, 16);

/* device_id
 * Access: RO
 */
MLXSW_ITEM16(reg, mgir, device_id, 0x2, 0, 16);

/* num_ports
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, num_ports, 0x5, 0, 8);

/* technology
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, technology, 0x6, 3, 5);

/* pvs
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, pvs, 0x7, 0, 5);

/* hw_dev_id
 * Access: RO
 */
MLXSW_ITEM16(reg, mgir, hw_dev_id, 0xa, 0, 16);

/* manufacturing_base_mac
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, mgir, manufacturing_base_mac, 0x12, 6);

/* uptime
 * Access: RO
 */
MLXSW_ITEM32(reg, mgir, uptime, 0x1c, 0, 32);

/* fw_info_string_tlv
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_string_tlv, 0x20, 4, 1);

/* fw_info_dev
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_dev, 0x20, 3, 1);

/* fw_info_debug
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_debug, 0x20, 2, 1);

/* fw_info_signed_fw
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_signed_fw, 0x20, 1, 1);

/* fw_info_secured
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_secured, 0x20, 0, 1);

/* fw_info_major
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_major, 0x21, 0, 8);

/* fw_info_minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_minor, 0x22, 0, 8);

/* fw_info_sub_minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_sub_minor, 0x23, 0, 8);

/* fw_info_build_id
 * Access: RO
 */
MLXSW_ITEM32(reg, mgir, fw_info_build_id, 0x24, 0, 32);

/* fw_info_month
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_month, 0x28, 0, 8);

/* fw_info_day
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_day, 0x29, 0, 8);

/* fw_info_year
 * Access: RO
 */
MLXSW_ITEM16(reg, mgir, fw_info_year, 0x2a, 0, 16);

/* fw_info_hour
 * Access: RO
 */
MLXSW_ITEM16(reg, mgir, fw_info_hour, 0x2e, 0, 16);

/* fw_info_psid
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, mgir, fw_info_psid, 0x30, 16);

/* fw_info_ini_file_version
 * Access: RO
 */
MLXSW_ITEM32(reg, mgir, fw_info_ini_file_version, 0x40, 0, 32);

/* fw_info_extended_major
 * Access: RO
 */
MLXSW_ITEM32(reg, mgir, fw_info_extended_major, 0x44, 0, 32);

/* fw_info_extended_minor
 * Access: RO
 */
MLXSW_ITEM32(reg, mgir, fw_info_extended_minor, 0x48, 0, 32);

/* fw_info_extended_sub_minor
 * Access: RO
 */
MLXSW_ITEM32(reg, mgir, fw_info_extended_sub_minor, 0x4c, 0, 32);

/* fw_info_isfu_major
 * Access: RO
 */
MLXSW_ITEM16(reg, mgir, fw_info_isfu_major, 0x52, 0, 16);

/* fw_info_sec_boot
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_sec_boot, 0x57, 2, 1);

/* fw_info_life_cycle
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_life_cycle, 0x57, 0, 2);

/* sw_info_major
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_major, 0x61, 0, 8);

/* sw_info_minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_minor, 0x62, 0, 8);

/* sw_info_sub_minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_sub_minor, 0x63, 0, 8);

/* sw_info_rom0_arch
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom0_arch, 0x64, 4, 4);

/* sw_info_rom0_type
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom0_type, 0x64, 0, 4);

/* sw_info_rom1_arch
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom1_arch, 0x65, 4, 4);

/* sw_info_rom1_type
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom1_type, 0x65, 0, 4);

/* sw_info_rom2_arch
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom2_arch, 0x66, 4, 4);

/* sw_info_rom2_type
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom2_type, 0x66, 0, 4);

/* sw_info_rom3_arch
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom3_arch, 0x67, 4, 4);

/* sw_info_rom3_type
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom3_type, 0x67, 0, 4);

/* sw_info_rom0_version_major
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom0_version_major, 0x68, 0, 8);

/* sw_info_rom0_version_minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom0_version_minor, 0x69, 0, 8);

/* sw_info_rom0_version_build
 * Access: RO
 */
MLXSW_ITEM16(reg, mgir, sw_info_rom0_version_build, 0x6a, 0, 16);

/* sw_info_rom1_version_major
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom1_version_major, 0x6c, 0, 8);

/* sw_info_rom1_version_minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom1_version_minor, 0x6d, 0, 8);

/* sw_info_rom1_version_build
 * Access: RO
 */
MLXSW_ITEM16(reg, mgir, sw_info_rom1_version_build, 0x6e, 0, 16);

/* sw_info_rom2_version_major
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom2_version_major, 0x70, 0, 8);

/* sw_info_rom2_version_minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom2_version_minor, 0x71, 0, 8);

/* sw_info_rom2_version_build
 * Access: RO
 */
MLXSW_ITEM16(reg, mgir, sw_info_rom2_version_build, 0x72, 0, 16);

/* sw_info_rom3_version_major
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom3_version_major, 0x74, 0, 8);

/* sw_info_rom3_version_minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, sw_info_rom3_version_minor, 0x75, 0, 8);

/* sw_info_rom3_version_build
 * Access: RO
 */
MLXSW_ITEM16(reg, mgir, sw_info_rom3_version_build, 0x76, 0, 16);

/* dev_branch_tag
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, mgir, dev_branch_tag, 0x80, 28);

/* tidem
 * -----
 *
 */
/* underlay_ecn
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tidem, underlay_ecn, 0x4, 0, 2);

/* overlay_ecn
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tidem, overlay_ecn, 0x5, 0, 2);

/* eip_ecn
 * Access: RW
 */
MLXSW_ITEM8(reg, tidem, eip_ecn, 0x6, 0, 2);

/* trap_en
 * Access: RW
 */
MLXSW_ITEM8(reg, tidem, trap_en, 0x8, 4, 4);

/* trap_id
 * Access: RW
 */
MLXSW_ITEM16(reg, tidem, trap_id, 0xa, 0, 9);

/* tigcr
 * -----
 *
 */
/* ipip_ttlc
 * Access: RW
 */
MLXSW_ITEM8(reg, tigcr, ipip_ttlc, 0x6, 0, 1);

/* ipip_ttl_uc
 * Access: RW
 */
MLXSW_ITEM8(reg, tigcr, ipip_ttl_uc, 0x7, 0, 8);

/* ipip_flc
 * Access: RW
 */
MLXSW_ITEM8(reg, tigcr, ipip_flc, 0xc, 1, 1);

/* ipip_flh
 * Access: RW
 */
MLXSW_ITEM8(reg, tigcr, ipip_flh, 0xc, 0, 1);

/* ipip_fl_prefix
 * Access: RW
 */
MLXSW_ITEM32(reg, tigcr, ipip_fl_prefix, 0xc, 8, 12);

/* ipip_fl_suffix
 * Access: RW
 */
MLXSW_ITEM8(reg, tigcr, ipip_fl_suffix, 0xf, 0, 8);

/* ipip_gre_key_for_hash
 * Access: RW
 */
MLXSW_ITEM32(reg, tigcr, ipip_gre_key_for_hash, 0x14, 8, 24);

/* rlcmld
 * ------
 *
 */
/* select
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rlcmld, select, 0x1, 0, 2);

/* filter_fields
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rlcmld, filter_fields, 0x3, 0, 8);

/* m_idx
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rlcmld, m_idx, 0x7, 0, 1);

/* protocol
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rlcmld, protocol, 0xb, 0, 4);

/* virtual_router
 * Access: INDEX
 */
MLXSW_ITEM16(reg, rlcmld, virtual_router, 0xe, 0, 16);

/* dip
 * Access: INDEX
 */
MLXSW_ITEM32_INDEXED(reg, rlcmld, dip, 0x10, 0, 32, 4, 0, false);

/* dip_mask
 * Access: INDEX
 */
MLXSW_ITEM32_INDEXED(reg, rlcmld, dip_mask, 0x20, 0, 32, 4, 0, false);

/* ceer
 * ----
 *
 */
/* clear
 * Access: OP
 */
MLXSW_ITEM8(reg, ceer, clear, 0x0, 7, 1);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ceer, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ceer, lp_msb, 0x2, 4, 2);

/* detection_entry
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ceer, detection_entry, 0x3, 0, 7);

/* det
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, det, 0x4, 7, 1);

/* l2_type
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, l2_type, 0xf, 0, 4);

/* extra_data_type
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_type, 0x10, 4, 4);

/* tunnel_type
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, tunnel_type, 0x10, 0, 4);

/* l4_type
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, l4_type, 0x11, 0, 4);

/* l3_type
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, l3_type, 0x12, 0, 4);

/* vlan_type
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, vlan_type, 0x13, 0, 4);

/* hash_valid
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, hash_valid, 0x18, 7, 1);

/* lag_hash
 * Access: RO
 */
MLXSW_ITEM16(reg, ceer, lag_hash, 0x1a, 0, 12);

/* router_hash
 * Access: RO
 */
MLXSW_ITEM16(reg, ceer, router_hash, 0x1e, 0, 12);

/* dmac
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, ceer, dmac, 0x22, 6);

/* smac
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, ceer, smac, 0x2a, 6);

/* pcp
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, pcp, 0x32, 5, 3);

/* dei
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, dei, 0x32, 4, 1);

/* vid
 * Access: RO
 */
MLXSW_ITEM16(reg, ceer, vid, 0x32, 0, 12);

/* inner_pcp
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, inner_pcp, 0x36, 5, 3);

/* inner_dei
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, inner_dei, 0x36, 4, 1);

/* inner_vid
 * Access: RO
 */
MLXSW_ITEM16(reg, ceer, inner_vid, 0x36, 0, 12);

/* dscp
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, dscp, 0x39, 2, 6);

/* ecn
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ecn, 0x39, 0, 2);

/* ttl
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ttl, 0x3a, 0, 8);

/* dont_frag
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, dont_frag, 0x3b, 0, 1);

/* sport
 * Access: RO
 */
MLXSW_ITEM16(reg, ceer, sport, 0x3c, 0, 16);

/* dport
 * Access: RO
 */
MLXSW_ITEM16(reg, ceer, dport, 0x3e, 0, 16);

/* sip
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, ceer, sip, 0x40, 0, 32, 4, 0, false);

/* dip
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, ceer, dip, 0x50, 0, 32, 4, 0, false);

/* ceer_extra_fields_vni
 * Access: RO
 */
MLXSW_ITEM32(reg, ceer, ceer_extra_fields_vni, 0x60, 0, 24);

/* ceer_extra_fields_inner_dmac
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, ceer, ceer_extra_fields_inner_dmac, 0x6a, 6);

/* ceer_extra_fields_inner_smac
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, ceer, ceer_extra_fields_inner_smac, 0x72, 6);

/* ceer_extra_fields_inner_l3_type
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_inner_l3_type, 0x7c, 0, 4);

/* ceer_extra_fields_inner_dscp
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_inner_dscp, 0x7d, 2, 6);

/* ceer_extra_fields_inner_ecn
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_inner_ecn, 0x7d, 0, 2);

/* ceer_extra_fields_inner_ttl
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_inner_ttl, 0x7e, 0, 8);

/* ceer_extra_fields_inner_dont_frag
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_inner_dont_frag, 0x7f, 0, 1);

/* ceer_extra_fields_inner_sip
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, ceer, ceer_extra_fields_inner_sip, 0x80, 0, 32, 4, 0, false);

/* ceer_extra_fields_inner_dip
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, ceer, ceer_extra_fields_inner_dip, 0x90, 0, 32, 4, 0, false);

/* ceer_extra_fields_MPLS_mpls_bos
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_MPLS_mpls_bos, 0x60, 7, 1);

/* ceer_extra_fields_MPLS_mpls_exp
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_MPLS_mpls_exp, 0x63, 0, 3);

/* ceer_extra_fields_MPLS_mpls_lb0_v
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_MPLS_mpls_lb0_v, 0x64, 7, 1);

/* ceer_extra_fields_MPLS_mpls_label0_label_id
 * Access: RO
 */
MLXSW_ITEM32(reg, ceer, ceer_extra_fields_MPLS_mpls_label0_label_id, 0x64, 8, 20);

/* ceer_extra_fields_MPLS_mpls_label0_ttl
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_MPLS_mpls_label0_ttl, 0x67, 0, 8);

/* ceer_extra_fields_MPLS_mpls_lb1_v
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_MPLS_mpls_lb1_v, 0x68, 7, 1);

/* ceer_extra_fields_MPLS_mpls_label1_label_id
 * Access: RO
 */
MLXSW_ITEM32(reg, ceer, ceer_extra_fields_MPLS_mpls_label1_label_id, 0x68, 8, 20);

/* ceer_extra_fields_MPLS_mpls_label1_ttl
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_MPLS_mpls_label1_ttl, 0x6b, 0, 8);

/* ceer_extra_fields_MPLS_mpls_lb2_v
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_MPLS_mpls_lb2_v, 0x6c, 7, 1);

/* ceer_extra_fields_MPLS_mpls_label2_label_id
 * Access: RO
 */
MLXSW_ITEM32(reg, ceer, ceer_extra_fields_MPLS_mpls_label2_label_id, 0x6c, 8, 20);

/* ceer_extra_fields_MPLS_mpls_label2_ttl
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_MPLS_mpls_label2_ttl, 0x6f, 0, 8);

/* ceer_extra_fields_MPLS_mpls_lb3_v
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_MPLS_mpls_lb3_v, 0x70, 7, 1);

/* ceer_extra_fields_MPLS_mpls_label3_label_id
 * Access: RO
 */
MLXSW_ITEM32(reg, ceer, ceer_extra_fields_MPLS_mpls_label3_label_id, 0x70, 8, 20);

/* ceer_extra_fields_MPLS_mpls_label3_ttl
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_MPLS_mpls_label3_ttl, 0x73, 0, 8);

/* ceer_extra_fields_MPLS_mpls_lb4_v
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_MPLS_mpls_lb4_v, 0x74, 7, 1);

/* ceer_extra_fields_MPLS_mpls_label4_label_id
 * Access: RO
 */
MLXSW_ITEM32(reg, ceer, ceer_extra_fields_MPLS_mpls_label4_label_id, 0x74, 8, 20);

/* ceer_extra_fields_MPLS_mpls_label4_ttl
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, ceer_extra_fields_MPLS_mpls_label4_ttl, 0x77, 0, 8);

/* pmtdb
 * -----
 *
 */
/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmtdb, slot_index, 0x0, 0, 4);

/* module
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmtdb, module, 0x1, 0, 8);

/* ports_width
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmtdb, ports_width, 0x2, 4, 4);

/* num_ports
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmtdb, num_ports, 0x2, 0, 4);

/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, pmtdb, status, 0x3, 0, 4);

/* port_num1
 * Access: RO
 */
MLXSW_ITEM8(reg, pmtdb, port_num1, 0x5, 0, 8);

/* port_num2
 * Access: RO
 */
MLXSW_ITEM8(reg, pmtdb, port_num2, 0x7, 0, 8);

/* port_num3
 * Access: RO
 */
MLXSW_ITEM8(reg, pmtdb, port_num3, 0x9, 0, 8);

/* port_num4
 * Access: RO
 */
MLXSW_ITEM8(reg, pmtdb, port_num4, 0xb, 0, 8);

/* port_num5
 * Access: RO
 */
MLXSW_ITEM8(reg, pmtdb, port_num5, 0xd, 0, 8);

/* port_num6
 * Access: RO
 */
MLXSW_ITEM8(reg, pmtdb, port_num6, 0xf, 0, 8);

/* port_num7
 * Access: RO
 */
MLXSW_ITEM8(reg, pmtdb, port_num7, 0x11, 0, 8);

/* port_num8
 * Access: RO
 */
MLXSW_ITEM8(reg, pmtdb, port_num8, 0x13, 0, 8);

/* ibfmrc
 * ------
 *
 */
/* attr_id_en
 * Access: RW
 */
MLXSW_ITEM32(reg, ibfmrc, attr_id_en, 0x0, 0, 32);

/* xralta
 * ------
 *
 */
/* op
 * Access: OP
 */
MLXSW_ITEM8(reg, xralta, op, 0x4, 4, 2);

/* protocol
 * Access: RW
 */
MLXSW_ITEM8(reg, xralta, protocol, 0x4, 0, 4);

/* tree_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, xralta, tree_id, 0x7, 0, 8);

/* mpagr
 * -----
 *
 */
/* swid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mpagr, swid, 0x0, 0, 8);

/* mngr_type
 * Access: OP
 */
MLXSW_ITEM8(reg, mpagr, mngr_type, 0x2, 0, 4);

/* trigger
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mpagr, trigger, 0x3, 0, 4);

/* enable
 * Access: RW
 */
MLXSW_ITEM8(reg, mpagr, enable, 0x4, 7, 1);

/* pa_id
 * Access: RW
 */
MLXSW_ITEM8(reg, mpagr, pa_id, 0x7, 0, 4);

/* probability_rate
 * Access: RW
 */
MLXSW_ITEM32(reg, mpagr, probability_rate, 0x8, 0, 32);

/* xltq
 * ----
 *
 */
/* xm_device_id
 * Access: RO
 */
MLXSW_ITEM16(reg, xltq, xm_device_id, 0x6, 0, 16);

/* xlt_cap_mask0
 * Access: RO
 */
MLXSW_ITEM32(reg, xltq, xlt_cap_mask0, 0x10, 0, 32);

/* cap_xlt_entries
 * Access: RO
 */
MLXSW_ITEM32(reg, xltq, cap_xlt_entries, 0x20, 0, 32);

/* cap_xlt_mtable
 * Access: RO
 */
MLXSW_ITEM32(reg, xltq, cap_xlt_mtable, 0x24, 0, 32);

/* cap_xlt_shspm_max_trees
 * Access: RO
 */
MLXSW_ITEM32(reg, xltq, cap_xlt_shspm_max_trees, 0x28, 0, 32);

/* ppcnt
 * -----
 *
 */
/* swid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppcnt, swid, 0x0, 0, 8);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppcnt, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppcnt, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppcnt, lp_msb, 0x2, 4, 2);

/* port_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppcnt, port_type, 0x2, 0, 4);

/* grp
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppcnt, grp, 0x3, 0, 6);

/* clr
 * Access: OP
 */
MLXSW_ITEM8(reg, ppcnt, clr, 0x4, 7, 1);

/* prio_tc
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppcnt, prio_tc, 0x7, 0, 5);

/* eth_802_3_cntrs_grp_data_layout_a_frames_transmitted_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_frames_transmitted_ok_high, 0x8, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_frames_transmitted_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_frames_transmitted_ok_low, 0xc, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_frames_received_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_frames_received_ok_high, 0x10, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_frames_received_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_frames_received_ok_low, 0x14, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_frame_check_sequence_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_frame_check_sequence_errors_high, 0x18, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_frame_check_sequence_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_frame_check_sequence_errors_low, 0x1c, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_alignment_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_alignment_errors_high, 0x20, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_alignment_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_alignment_errors_low, 0x24, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_octets_transmitted_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_octets_transmitted_ok_high, 0x28, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_octets_transmitted_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_octets_transmitted_ok_low, 0x2c, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_octets_received_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_octets_received_ok_high, 0x30, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_octets_received_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_octets_received_ok_low, 0x34, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_multicast_frames_xmitted_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_multicast_frames_xmitted_ok_high, 0x38, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_multicast_frames_xmitted_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_multicast_frames_xmitted_ok_low, 0x3c, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_xmitted_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_xmitted_ok_high, 0x40, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_xmitted_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_xmitted_ok_low, 0x44, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_multicast_frames_received_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_multicast_frames_received_ok_high, 0x48, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_multicast_frames_received_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_multicast_frames_received_ok_low, 0x4c, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_received_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_received_ok_high, 0x50, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_received_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_received_ok_low, 0x54, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_in_range_length_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_in_range_length_errors_high, 0x58, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_in_range_length_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_in_range_length_errors_low, 0x5c, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_out_of_range_length_field_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_out_of_range_length_field_high, 0x60, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_out_of_range_length_field_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_out_of_range_length_field_low, 0x64, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_frame_too_long_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_frame_too_long_errors_high, 0x68, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_frame_too_long_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_frame_too_long_errors_low, 0x6c, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_symbol_error_during_carrier_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_symbol_error_during_carrier_high, 0x70, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_symbol_error_during_carrier_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_symbol_error_during_carrier_low, 0x74, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_transmitted_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_transmitted_high, 0x78, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_transmitted_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_transmitted_low, 0x7c, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_received_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_received_high, 0x80, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_received_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_received_low, 0x84, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_unsupported_opcodes_received_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_unsupported_opcodes_received_high, 0x88, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_unsupported_opcodes_received_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_unsupported_opcodes_received_low, 0x8c, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_received_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_received_high, 0x90, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_received_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_received_low, 0x94, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_transmitted_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_transmitted_high, 0x98, 0, 32);

/* eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_transmitted_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_transmitted_low, 0x9c, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_in_octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_in_octets_high, 0x8, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_in_octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_in_octets_low, 0xc, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_in_ucast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_in_ucast_pkts_high, 0x10, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_in_ucast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_in_ucast_pkts_low, 0x14, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_in_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_in_discards_high, 0x18, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_in_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_in_discards_low, 0x1c, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_in_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_in_errors_high, 0x20, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_in_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_in_errors_low, 0x24, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_in_unknown_protos_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_in_unknown_protos_high, 0x28, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_in_unknown_protos_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_in_unknown_protos_low, 0x2c, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_out_octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_out_octets_high, 0x30, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_out_octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_out_octets_low, 0x34, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_out_ucast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_out_ucast_pkts_high, 0x38, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_out_ucast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_out_ucast_pkts_low, 0x3c, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_out_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_out_discards_high, 0x40, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_out_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_out_discards_low, 0x44, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_out_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_out_errors_high, 0x48, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_out_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_out_errors_low, 0x4c, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_in_multicast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_in_multicast_pkts_high, 0x50, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_in_multicast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_in_multicast_pkts_low, 0x54, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_in_broadcast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_in_broadcast_pkts_high, 0x58, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_in_broadcast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_in_broadcast_pkts_low, 0x5c, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_out_multicast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_out_multicast_pkts_high, 0x60, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_out_multicast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_out_multicast_pkts_low, 0x64, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_out_broadcast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_out_broadcast_pkts_high, 0x68, 0, 32);

/* eth_2863_cntrs_grp_data_layout_if_out_broadcast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2863_cntrs_grp_data_layout_if_out_broadcast_pkts_low, 0x6c, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_drop_events_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_drop_events_high, 0x8, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_drop_events_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_drop_events_low, 0xc, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_octets_high, 0x10, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_octets_low, 0x14, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts_high, 0x18, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts_low, 0x1c, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_broadcast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_broadcast_pkts_high, 0x20, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_broadcast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_broadcast_pkts_low, 0x24, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_multicast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_multicast_pkts_high, 0x28, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_multicast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_multicast_pkts_low, 0x2c, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_crc_align_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_crc_align_errors_high, 0x30, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_crc_align_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_crc_align_errors_low, 0x34, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_undersize_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_undersize_pkts_high, 0x38, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_undersize_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_undersize_pkts_low, 0x3c, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_oversize_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_oversize_pkts_high, 0x40, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_oversize_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_oversize_pkts_low, 0x44, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_fragments_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_fragments_high, 0x48, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_fragments_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_fragments_low, 0x4c, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_jabbers_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_jabbers_high, 0x50, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_jabbers_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_jabbers_low, 0x54, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_collisions_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_collisions_high, 0x58, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_collisions_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_collisions_low, 0x5c, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts64octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts64octets_high, 0x60, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts64octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts64octets_low, 0x64, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts65to127octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts65to127octets_high, 0x68, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts65to127octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts65to127octets_low, 0x6c, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts128to255octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts128to255octets_high, 0x70, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts128to255octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts128to255octets_low, 0x74, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts256to511octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts256to511octets_high, 0x78, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts256to511octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts256to511octets_low, 0x7c, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts512to1023octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts512to1023octets_high, 0x80, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts512to1023octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts512to1023octets_low, 0x84, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts1024to1518octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts1024to1518octets_high, 0x88, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts1024to1518octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts1024to1518octets_low, 0x8c, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts1519to2047octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts1519to2047octets_high, 0x90, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts1519to2047octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts1519to2047octets_low, 0x94, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts2048to4095octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts2048to4095octets_high, 0x98, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts2048to4095octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts2048to4095octets_low, 0x9c, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts4096to8191octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts4096to8191octets_high, 0xa0, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts4096to8191octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts4096to8191octets_low, 0xa4, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts8192to10239octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts8192to10239octets_high, 0xa8, 0, 32);

/* eth_2819_cntrs_grp_data_layout_ether_stats_pkts8192to10239octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_2819_cntrs_grp_data_layout_ether_stats_pkts8192to10239octets_low, 0xac, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_high, 0x8, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_low, 0xc, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_high, 0x10, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_low, 0x14, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_high, 0x18, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_low, 0x1c, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_high, 0x20, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_low, 0x24, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_high, 0x28, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_low, 0x2c, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_high, 0x30, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_low, 0x34, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_high, 0x38, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_low, 0x3c, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_high, 0x40, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_low, 0x44, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_high, 0x48, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_low, 0x4c, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_high, 0x50, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_low, 0x54, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_high, 0x58, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_low, 0x5c, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_high, 0x60, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_low, 0x64, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_high, 0x68, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_low, 0x6c, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_high, 0x70, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_low, 0x74, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_high, 0x78, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_low, 0x7c, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_high, 0x80, 0, 32);

/* eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_low, 0x84, 0, 32);

/* eth_extended_cntrs_grp_data_layout_port_transmit_wait_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_port_transmit_wait_high, 0x8, 0, 32);

/* eth_extended_cntrs_grp_data_layout_port_transmit_wait_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_port_transmit_wait_low, 0xc, 0, 32);

/* eth_extended_cntrs_grp_data_layout_ecn_marked_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_ecn_marked_high, 0x10, 0, 32);

/* eth_extended_cntrs_grp_data_layout_ecn_marked_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_ecn_marked_low, 0x14, 0, 32);

/* eth_extended_cntrs_grp_data_layout_no_buffer_discard_mc_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_no_buffer_discard_mc_high, 0x18, 0, 32);

/* eth_extended_cntrs_grp_data_layout_no_buffer_discard_mc_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_no_buffer_discard_mc_low, 0x1c, 0, 32);

/* eth_extended_cntrs_grp_data_layout_rx_ebp_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_rx_ebp_high, 0x20, 0, 32);

/* eth_extended_cntrs_grp_data_layout_rx_ebp_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_rx_ebp_low, 0x24, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_ebp_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_ebp_high, 0x28, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_ebp_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_ebp_low, 0x2c, 0, 32);

/* eth_extended_cntrs_grp_data_layout_rx_buffer_almost_full_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_rx_buffer_almost_full_high, 0x30, 0, 32);

/* eth_extended_cntrs_grp_data_layout_rx_buffer_almost_full_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_rx_buffer_almost_full_low, 0x34, 0, 32);

/* eth_extended_cntrs_grp_data_layout_rx_buffer_full_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_rx_buffer_full_high, 0x38, 0, 32);

/* eth_extended_cntrs_grp_data_layout_rx_buffer_full_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_rx_buffer_full_low, 0x3c, 0, 32);

/* eth_extended_cntrs_grp_data_layout_rx_icrc_encapsulated_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_rx_icrc_encapsulated_high, 0x40, 0, 32);

/* eth_extended_cntrs_grp_data_layout_rx_icrc_encapsulated_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_rx_icrc_encapsulated_low, 0x44, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts64octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts64octets_high, 0x58, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts64octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts64octets_low, 0x5c, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts65to127octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts65to127octets_high, 0x60, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts65to127octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts65to127octets_low, 0x64, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts128to255octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts128to255octets_high, 0x68, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts128to255octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts128to255octets_low, 0x6c, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts256to511octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts256to511octets_high, 0x70, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts256to511octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts256to511octets_low, 0x74, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts512to1023octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts512to1023octets_high, 0x78, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts512to1023octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts512to1023octets_low, 0x7c, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts1024to1518octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts1024to1518octets_high, 0x80, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts1024to1518octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts1024to1518octets_low, 0x84, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts1519to2047octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts1519to2047octets_high, 0x88, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts1519to2047octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts1519to2047octets_low, 0x8c, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts2048to4095octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts2048to4095octets_high, 0x90, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts2048to4095octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts2048to4095octets_low, 0x94, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts4096to8191octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts4096to8191octets_high, 0x98, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts4096to8191octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts4096to8191octets_low, 0x9c, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts8192to10239octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts8192to10239octets_high, 0xa0, 0, 32);

/* eth_extended_cntrs_grp_data_layout_tx_stats_pkts8192to10239octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_extended_cntrs_grp_data_layout_tx_stats_pkts8192to10239octets_low, 0xa4, 0, 32);

/* eth_discard_cntrs_grp_ingress_general_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_ingress_general_high, 0x8, 0, 32);

/* eth_discard_cntrs_grp_ingress_general_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_ingress_general_low, 0xc, 0, 32);

/* eth_discard_cntrs_grp_ingress_policy_engine_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_ingress_policy_engine_high, 0x10, 0, 32);

/* eth_discard_cntrs_grp_ingress_policy_engine_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_ingress_policy_engine_low, 0x14, 0, 32);

/* eth_discard_cntrs_grp_ingress_vlan_membership_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_ingress_vlan_membership_high, 0x18, 0, 32);

/* eth_discard_cntrs_grp_ingress_vlan_membership_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_ingress_vlan_membership_low, 0x1c, 0, 32);

/* eth_discard_cntrs_grp_ingress_tag_frame_type_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_ingress_tag_frame_type_high, 0x20, 0, 32);

/* eth_discard_cntrs_grp_ingress_tag_frame_type_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_ingress_tag_frame_type_low, 0x24, 0, 32);

/* eth_discard_cntrs_grp_egress_vlan_membership_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_egress_vlan_membership_high, 0x28, 0, 32);

/* eth_discard_cntrs_grp_egress_vlan_membership_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_egress_vlan_membership_low, 0x2c, 0, 32);

/* eth_discard_cntrs_grp_loopback_filter_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_loopback_filter_high, 0x30, 0, 32);

/* eth_discard_cntrs_grp_loopback_filter_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_loopback_filter_low, 0x34, 0, 32);

/* eth_discard_cntrs_grp_egress_general_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_egress_general_high, 0x38, 0, 32);

/* eth_discard_cntrs_grp_egress_general_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_egress_general_low, 0x3c, 0, 32);

/* eth_discard_cntrs_grp_egress_hoq_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_egress_hoq_high, 0x48, 0, 32);

/* eth_discard_cntrs_grp_egress_hoq_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_egress_hoq_low, 0x4c, 0, 32);

/* eth_discard_cntrs_grp_port_isolation_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_port_isolation_high, 0x50, 0, 32);

/* eth_discard_cntrs_grp_port_isolation_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_port_isolation_low, 0x54, 0, 32);

/* eth_discard_cntrs_grp_egress_policy_engine_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_egress_policy_engine_high, 0x58, 0, 32);

/* eth_discard_cntrs_grp_egress_policy_engine_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_egress_policy_engine_low, 0x5c, 0, 32);

/* eth_discard_cntrs_grp_ingress_tx_link_down_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_ingress_tx_link_down_high, 0x60, 0, 32);

/* eth_discard_cntrs_grp_ingress_tx_link_down_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_ingress_tx_link_down_low, 0x64, 0, 32);

/* eth_discard_cntrs_grp_egress_stp_filter_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_egress_stp_filter_high, 0x68, 0, 32);

/* eth_discard_cntrs_grp_egress_stp_filter_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_egress_stp_filter_low, 0x6c, 0, 32);

/* eth_discard_cntrs_grp_egress_hoq_stall_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_egress_hoq_stall_high, 0x70, 0, 32);

/* eth_discard_cntrs_grp_egress_hoq_stall_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_egress_hoq_stall_low, 0x74, 0, 32);

/* eth_discard_cntrs_grp_egress_sll_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_egress_sll_high, 0x78, 0, 32);

/* eth_discard_cntrs_grp_egress_sll_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_egress_sll_low, 0x7c, 0, 32);

/* eth_discard_cntrs_grp_ingress_discard_all_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_ingress_discard_all_high, 0x80, 0, 32);

/* eth_discard_cntrs_grp_ingress_discard_all_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_discard_cntrs_grp_ingress_discard_all_low, 0x84, 0, 32);

/* link_level_retrans_cntr_grp_data_llr_rx_cells_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, link_level_retrans_cntr_grp_data_llr_rx_cells_high, 0x8, 0, 32);

/* link_level_retrans_cntr_grp_data_llr_rx_cells_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, link_level_retrans_cntr_grp_data_llr_rx_cells_low, 0xc, 0, 32);

/* link_level_retrans_cntr_grp_data_llr_rx_error_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, link_level_retrans_cntr_grp_data_llr_rx_error_high, 0x10, 0, 32);

/* link_level_retrans_cntr_grp_data_llr_rx_error_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, link_level_retrans_cntr_grp_data_llr_rx_error_low, 0x14, 0, 32);

/* link_level_retrans_cntr_grp_data_llr_rx_crc_error_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, link_level_retrans_cntr_grp_data_llr_rx_crc_error_high, 0x18, 0, 32);

/* link_level_retrans_cntr_grp_data_llr_rx_crc_error_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, link_level_retrans_cntr_grp_data_llr_rx_crc_error_low, 0x1c, 0, 32);

/* link_level_retrans_cntr_grp_data_llr_tx_cells_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, link_level_retrans_cntr_grp_data_llr_tx_cells_high, 0x20, 0, 32);

/* link_level_retrans_cntr_grp_data_llr_tx_cells_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, link_level_retrans_cntr_grp_data_llr_tx_cells_low, 0x24, 0, 32);

/* link_level_retrans_cntr_grp_data_llr_tx_ret_cells_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, link_level_retrans_cntr_grp_data_llr_tx_ret_cells_high, 0x28, 0, 32);

/* link_level_retrans_cntr_grp_data_llr_tx_ret_cells_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, link_level_retrans_cntr_grp_data_llr_tx_ret_cells_low, 0x2c, 0, 32);

/* link_level_retrans_cntr_grp_data_llr_tx_ret_events_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, link_level_retrans_cntr_grp_data_llr_tx_ret_events_high, 0x30, 0, 32);

/* link_level_retrans_cntr_grp_data_llr_tx_ret_events_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, link_level_retrans_cntr_grp_data_llr_tx_ret_events_low, 0x34, 0, 32);

/* eth_per_prio_grp_data_layout_rx_octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_octets_high, 0x8, 0, 32);

/* eth_per_prio_grp_data_layout_rx_octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_octets_low, 0xc, 0, 32);

/* eth_per_prio_grp_data_layout_rx_uc_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_uc_frames_high, 0x10, 0, 32);

/* eth_per_prio_grp_data_layout_rx_uc_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_uc_frames_low, 0x14, 0, 32);

/* eth_per_prio_grp_data_layout_rx_mc_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_mc_frames_high, 0x18, 0, 32);

/* eth_per_prio_grp_data_layout_rx_mc_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_mc_frames_low, 0x1c, 0, 32);

/* eth_per_prio_grp_data_layout_rx_bc_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_bc_frames_high, 0x20, 0, 32);

/* eth_per_prio_grp_data_layout_rx_bc_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_bc_frames_low, 0x24, 0, 32);

/* eth_per_prio_grp_data_layout_rx_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_frames_high, 0x28, 0, 32);

/* eth_per_prio_grp_data_layout_rx_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_frames_low, 0x2c, 0, 32);

/* eth_per_prio_grp_data_layout_tx_octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_tx_octets_high, 0x30, 0, 32);

/* eth_per_prio_grp_data_layout_tx_octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_tx_octets_low, 0x34, 0, 32);

/* eth_per_prio_grp_data_layout_tx_uc_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_tx_uc_frames_high, 0x38, 0, 32);

/* eth_per_prio_grp_data_layout_tx_uc_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_tx_uc_frames_low, 0x3c, 0, 32);

/* eth_per_prio_grp_data_layout_tx_mc_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_tx_mc_frames_high, 0x40, 0, 32);

/* eth_per_prio_grp_data_layout_tx_mc_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_tx_mc_frames_low, 0x44, 0, 32);

/* eth_per_prio_grp_data_layout_tx_bc_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_tx_bc_frames_high, 0x48, 0, 32);

/* eth_per_prio_grp_data_layout_tx_bc_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_tx_bc_frames_low, 0x4c, 0, 32);

/* eth_per_prio_grp_data_layout_tx_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_tx_frames_high, 0x50, 0, 32);

/* eth_per_prio_grp_data_layout_tx_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_tx_frames_low, 0x54, 0, 32);

/* eth_per_prio_grp_data_layout_rx_pause_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_pause_high, 0x58, 0, 32);

/* eth_per_prio_grp_data_layout_rx_pause_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_pause_low, 0x5c, 0, 32);

/* eth_per_prio_grp_data_layout_rx_pause_duration_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_pause_duration_high, 0x60, 0, 32);

/* eth_per_prio_grp_data_layout_rx_pause_duration_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_pause_duration_low, 0x64, 0, 32);

/* eth_per_prio_grp_data_layout_tx_pause_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_tx_pause_high, 0x68, 0, 32);

/* eth_per_prio_grp_data_layout_tx_pause_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_tx_pause_low, 0x6c, 0, 32);

/* eth_per_prio_grp_data_layout_tx_pause_duration_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_tx_pause_duration_high, 0x70, 0, 32);

/* eth_per_prio_grp_data_layout_tx_pause_duration_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_tx_pause_duration_low, 0x74, 0, 32);

/* eth_per_prio_grp_data_layout_rx_pause_transition_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_pause_transition_high, 0x78, 0, 32);

/* eth_per_prio_grp_data_layout_rx_pause_transition_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_pause_transition_low, 0x7c, 0, 32);

/* eth_per_prio_grp_data_layout_rx_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_discards_high, 0x80, 0, 32);

/* eth_per_prio_grp_data_layout_rx_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_rx_discards_low, 0x84, 0, 32);

/* eth_per_prio_grp_data_layout_device_stall_minor_watermark_cnt_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_device_stall_minor_watermark_cnt_high, 0x88, 0, 32);

/* eth_per_prio_grp_data_layout_device_stall_minor_watermark_cnt_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_device_stall_minor_watermark_cnt_low, 0x8c, 0, 32);

/* eth_per_prio_grp_data_layout_device_stall_critical_watermark_cnt_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_device_stall_critical_watermark_cnt_high, 0x90, 0, 32);

/* eth_per_prio_grp_data_layout_device_stall_critical_watermark_cnt_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_prio_grp_data_layout_device_stall_critical_watermark_cnt_low, 0x94, 0, 32);

/* eth_per_traffic_class_layout_transmit_queue_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_traffic_class_layout_transmit_queue_high, 0x8, 0, 32);

/* eth_per_traffic_class_layout_transmit_queue_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_traffic_class_layout_transmit_queue_low, 0xc, 0, 32);

/* eth_per_traffic_class_layout_no_buffer_discard_uc_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_traffic_class_layout_no_buffer_discard_uc_high, 0x10, 0, 32);

/* eth_per_traffic_class_layout_no_buffer_discard_uc_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_traffic_class_layout_no_buffer_discard_uc_low, 0x14, 0, 32);

/* phys_layer_cntrs_time_since_last_clear_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_time_since_last_clear_high, 0x8, 0, 32);

/* phys_layer_cntrs_time_since_last_clear_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_time_since_last_clear_low, 0xc, 0, 32);

/* phys_layer_cntrs_symbol_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_symbol_errors_high, 0x10, 0, 32);

/* phys_layer_cntrs_symbol_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_symbol_errors_low, 0x14, 0, 32);

/* phys_layer_cntrs_sync_headers_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_sync_headers_errors_high, 0x18, 0, 32);

/* phys_layer_cntrs_sync_headers_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_sync_headers_errors_low, 0x1c, 0, 32);

/* phys_layer_cntrs_edpl_bip_errors_lane0_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_edpl_bip_errors_lane0_high, 0x20, 0, 32);

/* phys_layer_cntrs_edpl_bip_errors_lane0_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_edpl_bip_errors_lane0_low, 0x24, 0, 32);

/* phys_layer_cntrs_edpl_bip_errors_lane1_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_edpl_bip_errors_lane1_high, 0x28, 0, 32);

/* phys_layer_cntrs_edpl_bip_errors_lane1_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_edpl_bip_errors_lane1_low, 0x2c, 0, 32);

/* phys_layer_cntrs_edpl_bip_errors_lane2_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_edpl_bip_errors_lane2_high, 0x30, 0, 32);

/* phys_layer_cntrs_edpl_bip_errors_lane2_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_edpl_bip_errors_lane2_low, 0x34, 0, 32);

/* phys_layer_cntrs_edpl_bip_errors_lane3_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_edpl_bip_errors_lane3_high, 0x38, 0, 32);

/* phys_layer_cntrs_edpl_bip_errors_lane3_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_edpl_bip_errors_lane3_low, 0x3c, 0, 32);

/* phys_layer_cntrs_fc_fec_corrected_blocks_lane0_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_corrected_blocks_lane0_high, 0x40, 0, 32);

/* phys_layer_cntrs_fc_fec_corrected_blocks_lane0_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_corrected_blocks_lane0_low, 0x44, 0, 32);

/* phys_layer_cntrs_fc_fec_corrected_blocks_lane1_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_corrected_blocks_lane1_high, 0x48, 0, 32);

/* phys_layer_cntrs_fc_fec_corrected_blocks_lane1_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_corrected_blocks_lane1_low, 0x4c, 0, 32);

/* phys_layer_cntrs_fc_fec_corrected_blocks_lane2_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_corrected_blocks_lane2_high, 0x50, 0, 32);

/* phys_layer_cntrs_fc_fec_corrected_blocks_lane2_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_corrected_blocks_lane2_low, 0x54, 0, 32);

/* phys_layer_cntrs_fc_fec_corrected_blocks_lane3_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_corrected_blocks_lane3_high, 0x58, 0, 32);

/* phys_layer_cntrs_fc_fec_corrected_blocks_lane3_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_corrected_blocks_lane3_low, 0x5c, 0, 32);

/* phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane0_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane0_high, 0x60, 0, 32);

/* phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane0_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane0_low, 0x64, 0, 32);

/* phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane1_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane1_high, 0x68, 0, 32);

/* phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane1_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane1_low, 0x6c, 0, 32);

/* phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane2_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane2_high, 0x70, 0, 32);

/* phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane2_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane2_low, 0x74, 0, 32);

/* phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane3_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane3_high, 0x78, 0, 32);

/* phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane3_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane3_low, 0x7c, 0, 32);

/* phys_layer_cntrs_rs_fec_corrected_blocks_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_corrected_blocks_high, 0x80, 0, 32);

/* phys_layer_cntrs_rs_fec_corrected_blocks_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_corrected_blocks_low, 0x84, 0, 32);

/* phys_layer_cntrs_rs_fec_uncorrectable_blocks_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_uncorrectable_blocks_high, 0x88, 0, 32);

/* phys_layer_cntrs_rs_fec_uncorrectable_blocks_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_uncorrectable_blocks_low, 0x8c, 0, 32);

/* phys_layer_cntrs_rs_fec_no_errors_blocks_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_no_errors_blocks_high, 0x90, 0, 32);

/* phys_layer_cntrs_rs_fec_no_errors_blocks_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_no_errors_blocks_low, 0x94, 0, 32);

/* phys_layer_cntrs_rs_fec_single_error_blocks_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_single_error_blocks_high, 0x98, 0, 32);

/* phys_layer_cntrs_rs_fec_single_error_blocks_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_single_error_blocks_low, 0x9c, 0, 32);

/* phys_layer_cntrs_rs_fec_corrected_symbols_total_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_corrected_symbols_total_high, 0xa0, 0, 32);

/* phys_layer_cntrs_rs_fec_corrected_symbols_total_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_corrected_symbols_total_low, 0xa4, 0, 32);

/* phys_layer_cntrs_rs_fec_corrected_symbols_lane0_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_corrected_symbols_lane0_high, 0xa8, 0, 32);

/* phys_layer_cntrs_rs_fec_corrected_symbols_lane0_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_corrected_symbols_lane0_low, 0xac, 0, 32);

/* phys_layer_cntrs_rs_fec_corrected_symbols_lane1_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_corrected_symbols_lane1_high, 0xb0, 0, 32);

/* phys_layer_cntrs_rs_fec_corrected_symbols_lane1_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_corrected_symbols_lane1_low, 0xb4, 0, 32);

/* phys_layer_cntrs_rs_fec_corrected_symbols_lane2_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_corrected_symbols_lane2_high, 0xb8, 0, 32);

/* phys_layer_cntrs_rs_fec_corrected_symbols_lane2_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_corrected_symbols_lane2_low, 0xbc, 0, 32);

/* phys_layer_cntrs_rs_fec_corrected_symbols_lane3_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_corrected_symbols_lane3_high, 0xc0, 0, 32);

/* phys_layer_cntrs_rs_fec_corrected_symbols_lane3_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_rs_fec_corrected_symbols_lane3_low, 0xc4, 0, 32);

/* phys_layer_cntrs_link_down_events
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_link_down_events, 0xc8, 0, 32);

/* phys_layer_cntrs_successful_recovery_events
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_cntrs_successful_recovery_events, 0xcc, 0, 32);

/* eth_per_traffic_class_cong_layout_wred_discard_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_traffic_class_cong_layout_wred_discard_high, 0x8, 0, 32);

/* eth_per_traffic_class_cong_layout_wred_discard_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_traffic_class_cong_layout_wred_discard_low, 0xc, 0, 32);

/* eth_per_traffic_class_cong_layout_ecn_marked_tc_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_traffic_class_cong_layout_ecn_marked_tc_high, 0x10, 0, 32);

/* eth_per_traffic_class_cong_layout_ecn_marked_tc_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_traffic_class_cong_layout_ecn_marked_tc_low, 0x14, 0, 32);

/* eth_per_receive_buffer_grp_rx_no_buffer_discard_uc_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_receive_buffer_grp_rx_no_buffer_discard_uc_high, 0x8, 0, 32);

/* eth_per_receive_buffer_grp_rx_no_buffer_discard_uc_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_per_receive_buffer_grp_rx_no_buffer_discard_uc_low, 0xc, 0, 32);

/* phys_layer_stat_cntrs_time_since_last_clear_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_time_since_last_clear_high, 0x8, 0, 32);

/* phys_layer_stat_cntrs_time_since_last_clear_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_time_since_last_clear_low, 0xc, 0, 32);

/* phys_layer_stat_cntrs_phy_received_bits_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_received_bits_high, 0x10, 0, 32);

/* phys_layer_stat_cntrs_phy_received_bits_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_received_bits_low, 0x14, 0, 32);

/* phys_layer_stat_cntrs_phy_symbol_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_symbol_errors_high, 0x18, 0, 32);

/* phys_layer_stat_cntrs_phy_symbol_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_symbol_errors_low, 0x1c, 0, 32);

/* phys_layer_stat_cntrs_phy_corrected_bits_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_corrected_bits_high, 0x20, 0, 32);

/* phys_layer_stat_cntrs_phy_corrected_bits_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_corrected_bits_low, 0x24, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane0_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane0_high, 0x28, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane0_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane0_low, 0x2c, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane1_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane1_high, 0x30, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane1_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane1_low, 0x34, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane2_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane2_high, 0x38, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane2_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane2_low, 0x3c, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane3_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane3_high, 0x40, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane3_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane3_low, 0x44, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane4_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane4_high, 0x48, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane4_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane4_low, 0x4c, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane5_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane5_high, 0x50, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane5_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane5_low, 0x54, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane6_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane6_high, 0x58, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane6_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane6_low, 0x5c, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane7_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane7_high, 0x60, 0, 32);

/* phys_layer_stat_cntrs_phy_raw_errors_lane7_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_raw_errors_lane7_low, 0x64, 0, 32);

/* phys_layer_stat_cntrs_raw_ber_magnitude
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_magnitude, 0x6a, 0, 8);

/* phys_layer_stat_cntrs_raw_ber_coef
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_coef, 0x6b, 0, 4);

/* phys_layer_stat_cntrs_effective_ber_magnitude
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_effective_ber_magnitude, 0x6e, 0, 8);

/* phys_layer_stat_cntrs_effective_ber_coef
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_effective_ber_coef, 0x6f, 0, 4);

/* phys_layer_stat_cntrs_symbol_ber_magnitude
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_symbol_ber_magnitude, 0x72, 0, 8);

/* phys_layer_stat_cntrs_symbol_fec_ber_coef
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_symbol_fec_ber_coef, 0x73, 0, 4);

/* phys_layer_stat_cntrs_raw_ber_magnitude_lane0
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_magnitude_lane0, 0x74, 0, 8);

/* phys_layer_stat_cntrs_raw_ber_coef_lane0
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_coef_lane0, 0x75, 0, 4);

/* phys_layer_stat_cntrs_raw_ber_magnitude_lane1
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_magnitude_lane1, 0x76, 0, 8);

/* phys_layer_stat_cntrs_raw_ber_coef_lane1
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_coef_lane1, 0x77, 0, 4);

/* phys_layer_stat_cntrs_raw_ber_magnitude_lane2
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_magnitude_lane2, 0x78, 0, 8);

/* phys_layer_stat_cntrs_raw_ber_coef_lane2
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_coef_lane2, 0x79, 0, 4);

/* phys_layer_stat_cntrs_raw_ber_magnitude_lane3
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_magnitude_lane3, 0x7a, 0, 8);

/* phys_layer_stat_cntrs_raw_ber_coef_lane3
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_coef_lane3, 0x7b, 0, 4);

/* phys_layer_stat_cntrs_raw_ber_magnitude_lane4
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_magnitude_lane4, 0x7c, 0, 8);

/* phys_layer_stat_cntrs_raw_ber_coef_lane4
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_coef_lane4, 0x7d, 0, 4);

/* phys_layer_stat_cntrs_raw_ber_magnitude_lane5
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_magnitude_lane5, 0x7e, 0, 8);

/* phys_layer_stat_cntrs_raw_ber_coef_lane5
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_coef_lane5, 0x7f, 0, 4);

/* phys_layer_stat_cntrs_raw_ber_magnitude_lane6
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_magnitude_lane6, 0x80, 0, 8);

/* phys_layer_stat_cntrs_raw_ber_coef_lane6
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_coef_lane6, 0x81, 0, 4);

/* phys_layer_stat_cntrs_raw_ber_magnitude_lane7
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_magnitude_lane7, 0x82, 0, 8);

/* phys_layer_stat_cntrs_raw_ber_coef_lane7
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_raw_ber_coef_lane7, 0x83, 0, 4);

/* phys_layer_stat_cntrs_phy_effective_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_effective_errors_high, 0x84, 0, 32);

/* phys_layer_stat_cntrs_phy_effective_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, phys_layer_stat_cntrs_phy_effective_errors_low, 0x88, 0, 32);

/* eth_oob_port_cntrs_if_in_ucast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_if_in_ucast_pkts_high, 0x8, 0, 32);

/* eth_oob_port_cntrs_if_in_ucast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_if_in_ucast_pkts_low, 0xc, 0, 32);

/* eth_oob_port_cntrs_if_in_octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_if_in_octets_high, 0x10, 0, 32);

/* eth_oob_port_cntrs_if_in_octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_if_in_octets_low, 0x14, 0, 32);

/* eth_oob_port_cntrs_if_in_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_if_in_discards_high, 0x18, 0, 32);

/* eth_oob_port_cntrs_if_in_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_if_in_discards_low, 0x1c, 0, 32);

/* eth_oob_port_cntrs_if_in_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_if_in_errors_high, 0x20, 0, 32);

/* eth_oob_port_cntrs_if_in_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_if_in_errors_low, 0x24, 0, 32);

/* eth_oob_port_cntrs_ether_stats_crc_align_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_ether_stats_crc_align_errors_high, 0x28, 0, 32);

/* eth_oob_port_cntrs_ether_stats_crc_align_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_ether_stats_crc_align_errors_low, 0x2c, 0, 32);

/* eth_oob_port_cntrs_ether_stats_undersize_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_ether_stats_undersize_pkts_high, 0x30, 0, 32);

/* eth_oob_port_cntrs_ether_stats_undersize_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_ether_stats_undersize_pkts_low, 0x34, 0, 32);

/* eth_oob_port_cntrs_ether_stats_oversize_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_ether_stats_oversize_pkts_high, 0x38, 0, 32);

/* eth_oob_port_cntrs_ether_stats_oversize_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_ether_stats_oversize_pkts_low, 0x3c, 0, 32);

/* eth_oob_port_cntrs_dot3stats_symbol_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_dot3stats_symbol_errors_high, 0x40, 0, 32);

/* eth_oob_port_cntrs_dot3stats_symbol_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_dot3stats_symbol_errors_low, 0x44, 0, 32);

/* eth_oob_port_cntrs_dot3in_pause_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_dot3in_pause_frames_high, 0x48, 0, 32);

/* eth_oob_port_cntrs_dot3in_pause_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_dot3in_pause_frames_low, 0x4c, 0, 32);

/* eth_oob_port_cntrs_dot3control_in_unknown_opcodes_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_dot3control_in_unknown_opcodes_high, 0x50, 0, 32);

/* eth_oob_port_cntrs_dot3control_in_unknown_opcodes_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_dot3control_in_unknown_opcodes_low, 0x54, 0, 32);

/* eth_oob_port_cntrs_if_out_ucast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_if_out_ucast_pkts_high, 0x58, 0, 32);

/* eth_oob_port_cntrs_if_out_ucast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_if_out_ucast_pkts_low, 0x5c, 0, 32);

/* eth_oob_port_cntrs_if_out_octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_if_out_octets_high, 0x60, 0, 32);

/* eth_oob_port_cntrs_if_out_octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_if_out_octets_low, 0x64, 0, 32);

/* eth_oob_port_cntrs_dot3out_pause_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_dot3out_pause_frames_high, 0x68, 0, 32);

/* eth_oob_port_cntrs_dot3out_pause_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_dot3out_pause_frames_low, 0x6c, 0, 32);

/* eth_oob_port_cntrs_if_out_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_if_out_errors_high, 0x70, 0, 32);

/* eth_oob_port_cntrs_if_out_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_if_out_errors_low, 0x74, 0, 32);

/* eth_oob_port_cntrs_phy_time_since_last_clear_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_phy_time_since_last_clear_high, 0x78, 0, 32);

/* eth_oob_port_cntrs_phy_time_since_last_clear_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_phy_time_since_last_clear_low, 0x7c, 0, 32);

/* eth_oob_port_cntrs_phy_received_bits_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_phy_received_bits_high, 0x80, 0, 32);

/* eth_oob_port_cntrs_phy_received_bits_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_phy_received_bits_low, 0x84, 0, 32);

/* eth_oob_port_cntrs_phy_symbol_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_phy_symbol_errors_high, 0x88, 0, 32);

/* eth_oob_port_cntrs_phy_symbol_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, eth_oob_port_cntrs_phy_symbol_errors_low, 0x8c, 0, 32);

/* IB_portcntrs_attribute_grp_data_symbol_error_counter
 * Access: RO
 */
MLXSW_ITEM16(reg, ppcnt, IB_portcntrs_attribute_grp_data_symbol_error_counter, 0x8, 0, 16);

/* IB_portcntrs_attribute_grp_data_link_error_recovery_counter
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, IB_portcntrs_attribute_grp_data_link_error_recovery_counter, 0xa, 0, 8);

/* IB_portcntrs_attribute_grp_data_link_downed_counter
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, IB_portcntrs_attribute_grp_data_link_downed_counter, 0xb, 0, 8);

/* IB_portcntrs_attribute_grp_data_port_rcv_errors
 * Access: RO
 */
MLXSW_ITEM16(reg, ppcnt, IB_portcntrs_attribute_grp_data_port_rcv_errors, 0xc, 0, 16);

/* IB_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors
 * Access: RO
 */
MLXSW_ITEM16(reg, ppcnt, IB_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors, 0xe, 0, 16);

/* IB_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors
 * Access: RO
 */
MLXSW_ITEM16(reg, ppcnt, IB_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors, 0x10, 0, 16);

/* IB_portcntrs_attribute_grp_data_port_xmit_discards
 * Access: RO
 */
MLXSW_ITEM16(reg, ppcnt, IB_portcntrs_attribute_grp_data_port_xmit_discards, 0x12, 0, 16);

/* IB_portcntrs_attribute_grp_data_port_xmit_constraint_errors
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, IB_portcntrs_attribute_grp_data_port_xmit_constraint_errors, 0x14, 0, 8);

/* IB_portcntrs_attribute_grp_data_port_rcv_constraint_errors
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, IB_portcntrs_attribute_grp_data_port_rcv_constraint_errors, 0x15, 0, 8);

/* IB_portcntrs_attribute_grp_data_local_link_integrity_errors
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, IB_portcntrs_attribute_grp_data_local_link_integrity_errors, 0x17, 4, 4);

/* IB_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, IB_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors, 0x17, 0, 4);

/* IB_portcntrs_attribute_grp_data_vl_15_dropped
 * Access: RO
 */
MLXSW_ITEM16(reg, ppcnt, IB_portcntrs_attribute_grp_data_vl_15_dropped, 0x1a, 0, 16);

/* IB_portcntrs_attribute_grp_data_port_xmit_data
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_portcntrs_attribute_grp_data_port_xmit_data, 0x1c, 0, 32);

/* IB_portcntrs_attribute_grp_data_port_rcv_data
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_portcntrs_attribute_grp_data_port_rcv_data, 0x20, 0, 32);

/* IB_portcntrs_attribute_grp_data_port_xmit_pkts
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_portcntrs_attribute_grp_data_port_xmit_pkts, 0x24, 0, 32);

/* IB_portcntrs_attribute_grp_data_port_rcv_pkts
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_portcntrs_attribute_grp_data_port_rcv_pkts, 0x28, 0, 32);

/* IB_portcntrs_attribute_grp_data_port_xmit_wait
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_portcntrs_attribute_grp_data_port_xmit_wait, 0x2c, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_symbol_error_counter_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_symbol_error_counter_high, 0x8, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_symbol_error_counter_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_symbol_error_counter_low, 0xc, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_link_error_recovery_counter_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_link_error_recovery_counter_high, 0x10, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_link_error_recovery_counter_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_link_error_recovery_counter_low, 0x14, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_link_downed_counter_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_link_downed_counter_high, 0x18, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_link_downed_counter_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_link_downed_counter_low, 0x1c, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_rcv_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_rcv_errors_high, 0x20, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_rcv_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_rcv_errors_low, 0x24, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_high, 0x28, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_low, 0x2c, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_high, 0x30, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_low, 0x34, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_xmit_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_xmit_discards_high, 0x38, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_xmit_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_xmit_discards_low, 0x3c, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_xmit_constraint_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_xmit_constraint_errors_high, 0x40, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_xmit_constraint_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_xmit_constraint_errors_low, 0x44, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_rcv_constraint_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_rcv_constraint_errors_high, 0x48, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_rcv_constraint_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_rcv_constraint_errors_low, 0x4c, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_local_link_integrity_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_local_link_integrity_errors_high, 0x50, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_local_link_integrity_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_local_link_integrity_errors_low, 0x54, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_high, 0x58, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_low, 0x5c, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_vl_15_dropped_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_vl_15_dropped_high, 0x60, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_vl_15_dropped_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_vl_15_dropped_low, 0x64, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_xmit_data_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_xmit_data_high, 0x68, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_xmit_data_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_xmit_data_low, 0x6c, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_rcv_data_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_rcv_data_high, 0x70, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_rcv_data_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_rcv_data_low, 0x74, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_xmit_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_xmit_pkts_high, 0x78, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_xmit_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_xmit_pkts_low, 0x7c, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_rcv_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_rcv_pkts_high, 0x80, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_rcv_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_rcv_pkts_low, 0x84, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_xmit_wait_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_xmit_wait_high, 0x88, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_xmit_wait_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_xmit_wait_low, 0x8c, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_effective_rcv_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_effective_rcv_pkts_high, 0x90, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_effective_rcv_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_effective_rcv_pkts_low, 0x94, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_effective_rcv_data_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_effective_rcv_data_high, 0x98, 0, 32);

/* IB_long_portcntrs_attribute_grp_data_port_effective_rcv_data_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, IB_long_portcntrs_attribute_grp_data_port_effective_rcv_data_low, 0x9c, 0, 32);

/* ppcnt_plr_counters_plr_rcv_codes_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_rcv_codes_high, 0x8, 0, 32);

/* ppcnt_plr_counters_plr_rcv_codes_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_rcv_codes_low, 0xc, 0, 32);

/* ppcnt_plr_counters_plr_rcv_code_err_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_rcv_code_err_high, 0x10, 0, 32);

/* ppcnt_plr_counters_plr_rcv_code_err_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_rcv_code_err_low, 0x14, 0, 32);

/* ppcnt_plr_counters_plr_rcv_uncorrectable_code_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_rcv_uncorrectable_code_high, 0x18, 0, 32);

/* ppcnt_plr_counters_plr_rcv_uncorrectable_code_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_rcv_uncorrectable_code_low, 0x1c, 0, 32);

/* ppcnt_plr_counters_plr_xmit_codes_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_xmit_codes_high, 0x20, 0, 32);

/* ppcnt_plr_counters_plr_xmit_codes_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_xmit_codes_low, 0x24, 0, 32);

/* ppcnt_plr_counters_plr_xmit_retry_codes_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_xmit_retry_codes_high, 0x28, 0, 32);

/* ppcnt_plr_counters_plr_xmit_retry_codes_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_xmit_retry_codes_low, 0x2c, 0, 32);

/* ppcnt_plr_counters_plr_xmit_retry_events_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_xmit_retry_events_high, 0x30, 0, 32);

/* ppcnt_plr_counters_plr_xmit_retry_events_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_xmit_retry_events_low, 0x34, 0, 32);

/* ppcnt_plr_counters_plr_sync_events_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_sync_events_high, 0x38, 0, 32);

/* ppcnt_plr_counters_plr_sync_events_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_sync_events_low, 0x3c, 0, 32);

/* ppcnt_plr_counters_hi_retransmission_rate_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_hi_retransmission_rate_high, 0x40, 0, 32);

/* ppcnt_plr_counters_hi_retransmission_rate_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_hi_retransmission_rate_low, 0x44, 0, 32);

/* ppcnt_plr_counters_plr_xmit_retry_codes_within_t_sec_max_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_xmit_retry_codes_within_t_sec_max_high, 0x48, 0, 32);

/* ppcnt_plr_counters_plr_xmit_retry_codes_within_t_sec_max_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, ppcnt_plr_counters_plr_xmit_retry_codes_within_t_sec_max_low, 0x4c, 0, 32);

/* ppcnt_plr_counters_pre_plr_ber_magnitude
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, ppcnt_plr_counters_pre_plr_ber_magnitude, 0x52, 0, 8);

/* ppcnt_plr_counters_pre_plr_ber_coef
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, ppcnt_plr_counters_pre_plr_ber_coef, 0x53, 0, 4);

/* ppcnt_rs_fec_histograms_counters_hi
 * Access: 
 */
MLXSW_ITEM32_INDEXED(reg, ppcnt, ppcnt_rs_fec_histograms_counters_hi, MLXSW_PPCNT_HIST_BASE_LEN, 0, 32, MLXSW_PPCNT_HIST_REC_LEN, 0, false);

/* ppcnt_rs_fec_histograms_counters_lo
 * Access: 
 */
MLXSW_ITEM32_INDEXED(reg, ppcnt, ppcnt_rs_fec_histograms_counters_lo, MLXSW_PPCNT_HIST_BASE_LEN, 0, 32, MLXSW_PPCNT_HIST_REC_LEN, 4, false);

/* usr_xsr_physical_layer_time_since_last_clear_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_time_since_last_clear_high, 0x8, 0, 32);

/* usr_xsr_physical_layer_time_since_last_clear_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_time_since_last_clear_low, 0xc, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane0_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane0_high, 0x10, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane0_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane0_low, 0x14, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane1_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane1_high, 0x18, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane1_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane1_low, 0x1c, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane2_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane2_high, 0x20, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane2_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane2_low, 0x24, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane3_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane3_high, 0x28, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane3_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane3_low, 0x2c, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane4_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane4_high, 0x30, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane4_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane4_low, 0x34, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane5_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane5_high, 0x38, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane5_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane5_low, 0x3c, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane6_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane6_high, 0x40, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane6_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane6_low, 0x44, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane7_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane7_high, 0x48, 0, 32);

/* usr_xsr_physical_layer_fc_fec_corrected_blocks_lane7_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_corrected_blocks_lane7_low, 0x4c, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane0_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane0_high, 0x50, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane0_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane0_low, 0x54, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane1_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane1_high, 0x58, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane1_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane1_low, 0x5c, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane2_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane2_high, 0x60, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane2_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane2_low, 0x64, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane3_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane3_high, 0x68, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane3_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane3_low, 0x6c, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane4_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane4_high, 0x70, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane4_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane4_low, 0x74, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane5_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane5_high, 0x78, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane5_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane5_low, 0x7c, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane6_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane6_high, 0x80, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane6_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane6_low, 0x84, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane7_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane7_high, 0x88, 0, 32);

/* usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane7_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane7_low, 0x8c, 0, 32);

/* usr_xsr_physical_layer_link_down_events
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, usr_xsr_physical_layer_link_down_events, 0x90, 0, 32);

/* pefaad
 * ------
 *
 */
/* filter_fields
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pefaad, filter_fields, 0x3, 0, 8);

/* op
 * Access: OP
 */
MLXSW_ITEM8(reg, pefaad, op, 0x4, 0, 2);

/* num_rec
 * Access: OP
 */
MLXSW_ITEM16(reg, pefaad, num_rec, 0x6, 0, 9);

/* entry_a
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pefaad, entry_a, 0x9, 0, 1);

/* as_user_val
 * Access: INDEX
 */
MLXSW_ITEM16(reg, pefaad, as_user_val, 0x12, 0, 10);

/* index_dump
 * Access: 
 */
MLXSW_ITEM32_INDEXED(reg, pefaad, index_dump, 0x20, 0, 24, 0x4, 0x0, false);

/* pmlpe
 * -----
 *
 */
/* rxtx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmlpe, rxtx, 0x0, 7, 1);

/* autosplit
 * Access: RO
 */
MLXSW_ITEM8(reg, pmlpe, autosplit, 0x0, 6, 1);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmlpe, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmlpe, lp_msb, 0x2, 4, 2);

/* width
 * Access: RO
 */
MLXSW_ITEM8(reg, pmlpe, width, 0x3, 0, 8);

/* lane0_module_mapping
 * Access: RO
 */
MLXSW_ITEM32(reg, pmlpe, lane0_module_mapping, 0x4, 0, 32);

/* lane1_module_mapping
 * Access: RO
 */
MLXSW_ITEM32(reg, pmlpe, lane1_module_mapping, 0x8, 0, 32);

/* lane2_module_mapping
 * Access: RO
 */
MLXSW_ITEM32(reg, pmlpe, lane2_module_mapping, 0xc, 0, 32);

/* lane3_module_mapping
 * Access: RO
 */
MLXSW_ITEM32(reg, pmlpe, lane3_module_mapping, 0x10, 0, 32);

/* lane4_module_mapping
 * Access: RO
 */
MLXSW_ITEM32(reg, pmlpe, lane4_module_mapping, 0x14, 0, 32);

/* lane5_module_mapping
 * Access: RO
 */
MLXSW_ITEM32(reg, pmlpe, lane5_module_mapping, 0x18, 0, 32);

/* lane6_module_mapping
 * Access: RO
 */
MLXSW_ITEM32(reg, pmlpe, lane6_module_mapping, 0x1c, 0, 32);

/* lane7_module_mapping
 * Access: RO
 */
MLXSW_ITEM32(reg, pmlpe, lane7_module_mapping, 0x20, 0, 32);

/* chlmm
 * -----
 *
 */
/* switch_prio
 * Access: INDEX
 */
MLXSW_ITEM8(reg, chlmm, switch_prio, 0x2, 0, 4);

/* hlt_table_pointer
 * Access: RW
 */
MLXSW_ITEM8(reg, chlmm, hlt_table_pointer, 0x13, 0, 8);

/* tncr
 * ----
 *
 */
/* clear_counters
 * Access: OP
 */
MLXSW_ITEM8(reg, tncr, clear_counters, 0x0, 7, 1);

/* count_encap_high
 * Access: RO
 */
MLXSW_ITEM32(reg, tncr, count_encap_high, 0x10, 0, 32);

/* count_encap_low
 * Access: RO
 */
MLXSW_ITEM32(reg, tncr, count_encap_low, 0x14, 0, 32);

/* count_decap_high
 * Access: RO
 */
MLXSW_ITEM32(reg, tncr, count_decap_high, 0x18, 0, 32);

/* count_decap_low
 * Access: RO
 */
MLXSW_ITEM32(reg, tncr, count_decap_low, 0x1c, 0, 32);

/* count_decap_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, tncr, count_decap_errors_high, 0x20, 0, 32);

/* count_decap_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, tncr, count_decap_errors_low, 0x24, 0, 32);

/* count_decap_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, tncr, count_decap_discards_high, 0x28, 0, 32);

/* count_decap_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, tncr, count_decap_discards_low, 0x2c, 0, 32);

/* xmdr
 * ----
 *
 */
/* num_rec
 * Access: OP
 */
MLXSW_ITEM8(reg, xmdr, num_rec, 0x7, 0, 4);

/* reply_vect
 * Access: RO
 */
MLXSW_ITEM8(reg, xmdr, reply_vect, 0xb, 0, 4);

/* transaction
 * Access: WO
 */
MLXSW_ITEM32_INDEXED(reg, xmdr, transaction, 0x20, 0, 32, 4, 0, false);

/* mdfcr
 * -----
 *
 */
/* device_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mdfcr, device_type, 0x3, 0, 8);

/* all
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mdfcr, all, 0x4, 7, 1);

/* device_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, mdfcr, device_index, 0x6, 0, 12);

/* fw_status
 * Access: RO
 */
MLXSW_ITEM8(reg, mdfcr, fw_status, 0xd, 4, 4);

/* first_fw_status_device
 * Access: RO
 */
MLXSW_ITEM16(reg, mdfcr, first_fw_status_device, 0xe, 0, 12);

/* expected_fw_version
 * Access: RO
 */
MLXSW_ITEM32(reg, mdfcr, expected_fw_version, 0x10, 0, 32);

/* fw_version
 * Access: RO
 */
MLXSW_ITEM32(reg, mdfcr, fw_version, 0x14, 0, 32);

/* build_id
 * Access: RO
 */
MLXSW_ITEM16(reg, mdfcr, build_id, 0x1a, 0, 16);

/* major
 * Access: RO
 */
MLXSW_ITEM8(reg, mdfcr, major, 0x1f, 0, 8);

/* minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mdfcr, minor, 0x23, 0, 8);

/* error_id
 * Access: RO
 */
MLXSW_ITEM8(reg, mdfcr, error_id, 0x26, 3, 5);

/* mddc
 * ----
 *
 */
/* level
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mddc, level, 0x0, 0, 4);

/* index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mddc, index, 0x2, 1, 8);

/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mddc, slot_index, 0x3, 0, 4);

/* rst
 * Access: OP
 */
MLXSW_ITEM8(reg, mddc, rst, 0x4, 5, 3);

/* device_enable
 * Access: RW
 */
MLXSW_ITEM8(reg, mddc, device_enable, 0x4, 4, 1);

/* paos
 * ----
 *
 */
/* swid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, paos, swid, 0x0, 0, 8);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, paos, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, paos, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, paos, lp_msb, 0x2, 4, 2);

/* admin_status
 * Access: RW
 */
MLXSW_ITEM8(reg, paos, admin_status, 0x2, 0, 4);

/* oper_status
 * Access: RO
 */
MLXSW_ITEM8(reg, paos, oper_status, 0x3, 0, 4);

/* ase
 * Access: WO
 */
MLXSW_ITEM8(reg, paos, ase, 0x4, 7, 1);

/* ee
 * Access: WO
 */
MLXSW_ITEM8(reg, paos, ee, 0x4, 6, 1);

/* fd
 * Access: RW
 */
MLXSW_ITEM8(reg, paos, fd, 0x6, 0, 1);

/* e
 * Access: RW
 */
MLXSW_ITEM8(reg, paos, e, 0x7, 0, 2);

/* mtutc
 * -----
 *
 */
/* operation
 * Access: OP
 */
MLXSW_ITEM8(reg, mtutc, operation, 0x3, 0, 4);

/* freq_adjustment
 * Access: RW
 */
MLXSW_ITEM32(reg, mtutc, freq_adjustment, 0x4, 0, 32);

/* utc_sec
 * Access: WO
 */
MLXSW_ITEM32(reg, mtutc, utc_sec, 0x10, 0, 32);

/* utc_nsec
 * Access: WO
 */
MLXSW_ITEM32(reg, mtutc, utc_nsec, 0x14, 0, 30);

/* time_adjustment
 * Access: WO
 */
MLXSW_ITEM32(reg, mtutc, time_adjustment, 0x18, 0, 32);

/* sfmr
 * ----
 *
 */
/* update
 * Access: OP
 */
MLXSW_ITEM8(reg, sfmr, update, 0x0, 7, 1);

/* op
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, op, 0x0, 0, 4);

/* fid
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sfmr, fid, 0x2, 0, 16);

/* update_mask
 * Access: OP
 */
MLXSW_ITEM32(reg, sfmr, update_mask, 0x4, 8, 16);

/* disable_tport_encap
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, disable_tport_encap, 0x7, 0, 4);

/* flood_rsp
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, flood_rsp, 0x8, 7, 1);

/* flood_bridge_type
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, flood_bridge_type, 0x8, 4, 1);

/* fid_offset
 * Access: RW
 */
MLXSW_ITEM16(reg, sfmr, fid_offset, 0xa, 0, 16);

/* vtfp
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, vtfp, 0xc, 7, 1);

/* nve_tunnel_flood_ptr
 * Access: RW
 */
MLXSW_ITEM32(reg, sfmr, nve_tunnel_flood_ptr, 0xc, 0, 24);

/* vv
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, vv, 0x10, 7, 1);

/* vni
 * Access: RW
 */
MLXSW_ITEM32(reg, sfmr, vni, 0x10, 0, 24);

/* irif_v
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, irif_v, 0x14, 0, 1);

/* irif
 * Access: RW
 */
MLXSW_ITEM16(reg, sfmr, irif, 0x16, 0, 16);

/* decap_counter_set_type
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, decap_counter_set_type, 0x18, 0, 8);

/* decap_counter_index
 * Access: RW
 */
MLXSW_ITEM32(reg, sfmr, decap_counter_index, 0x18, 0, 24);

/* nve_flood_prf_id
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, nve_flood_prf_id, 0x26, 0, 2);

/* smpe_valid
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, smpe_valid, 0x29, 4, 1);

/* smpe
 * Access: RW
 */
MLXSW_ITEM16(reg, sfmr, smpe, 0x2a, 0, 16);

/* hrdqt
 * -----
 *
 */
/* rdq
 * Access: INDEX
 */
MLXSW_ITEM8(reg, hrdqt, rdq, 0x3, 0, 6);

/* tac_en
 * Access: RW
 */
MLXSW_ITEM8(reg, hrdqt, tac_en, 0x7, 0, 1);

/* mirror_action
 * Access: RW
 */
MLXSW_ITEM8(reg, hrdqt, mirror_action, 0x9, 0, 2);

/* mirror_agent
 * Access: RW
 */
MLXSW_ITEM8(reg, hrdqt, mirror_agent, 0xa, 0, 4);

/* host_based_mirror_reason_id
 * Access: RW
 */
MLXSW_ITEM8(reg, hrdqt, host_based_mirror_reason_id, 0xb, 0, 8);

/* mtsde
 * -----
 *
 */
/* last_sensor
 * Access: RO
 */
MLXSW_ITEM16(reg, mtsde, last_sensor, 0x0, 0, 10);

/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mtsde, slot_index, 0x2, 4, 4);

/* sensor_count
 * Access: RO
 */
MLXSW_ITEM16(reg, mtsde, sensor_count, 0x2, 0, 10);

/* sensor_shut_down_map_0
 * Access: RO
 */
MLXSW_ITEM32(reg, mtsde, sensor_shut_down_map_0, 0x4, 0, 32);

/* smpe
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, smpe, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, smpe, lp_msb, 0x2, 4, 2);

/* smpe_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, smpe, smpe_index, 0x6, 0, 16);

/* evid
 * Access: RW
 */
MLXSW_ITEM16(reg, smpe, evid, 0xa, 0, 12);

/* tiqdr
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tiqdr, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tiqdr, lp_msb, 0x2, 4, 2);

/* color
 * Access: RW
 */
MLXSW_ITEM8(reg, tiqdr, color, 0x4, 0, 2);

/* switch_prio
 * Access: RW
 */
MLXSW_ITEM8(reg, tiqdr, switch_prio, 0x5, 0, 4);

/* dscp
 * Access: RW
 */
MLXSW_ITEM8(reg, tiqdr, dscp, 0x7, 0, 6);

/* xraltb
 * ------
 *
 */
/* virtual_router
 * Access: INDEX
 */
MLXSW_ITEM16(reg, xraltb, virtual_router, 0x4, 0, 16);

/* protocol
 * Access: INDEX
 */
MLXSW_ITEM8(reg, xraltb, protocol, 0x6, 4, 4);

/* tree_id
 * Access: RW
 */
MLXSW_ITEM8(reg, xraltb, tree_id, 0x7, 0, 8);

/* tngee
 * -----
 *
 */
/* l2_enc_index
 * Access: INDEX
 */
MLXSW_ITEM32(reg, tngee, l2_enc_index, 0x0, 0, 24);

/* tunnel_type
 * Access: RW
 */
MLXSW_ITEM8(reg, tngee, tunnel_type, 0x7, 0, 4);

/* vnext
 * Access: RW
 */
MLXSW_ITEM8(reg, tngee, vnext, 0x8, 7, 1);

/* next_l2_enc_ptr
 * Access: RW
 */
MLXSW_ITEM32(reg, tngee, next_l2_enc_ptr, 0x8, 0, 24);

/* ecmp_size
 * Access: RW
 */
MLXSW_ITEM16(reg, tngee, ecmp_size, 0xe, 0, 13);

/* protocol
 * Access: RW
 */
MLXSW_ITEM8(reg, tngee, protocol, 0x10, 4, 1);

/* uirif
 * Access: RW
 */
MLXSW_ITEM16(reg, tngee, uirif, 0x12, 0, 16);

/* udip
 * Access: RW
 */
MLXSW_ITEM32(reg, tngee, udip, 0x14, 0, 32);

/* counter_set_type
 * Access: RW
 */
MLXSW_ITEM8(reg, tngee, counter_set_type, 0x3c, 0, 8);

/* counter_index
 * Access: RW
 */
MLXSW_ITEM32(reg, tngee, counter_index, 0x3c, 0, 24);

/* entry
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, tngee, entry, 0x40, 0, 32, 4, 0, false);

/* smpeb
 * -----
 *
 */
/* smpe_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, smpeb, smpe_index, 0x6, 0, 16);

/* elport_page
 * Access: INDEX
 */
MLXSW_ITEM8(reg, smpeb, elport_page, 0xb, 0, 4);

/* update
 * Access: OP
 */
MLXSW_ITEM8_INDEXED(reg, smpeb, update, MLXSW_SMPEB_ELPORT_RECORD_BASE_LEN, 7, 1, MLXSW_SMPEB_ELPORT_RECORD_REC_LEN, 0, false);

/* value
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, smpeb, value, MLXSW_SMPEB_ELPORT_RECORD_BASE_LEN, 0, 20, MLXSW_SMPEB_ELPORT_RECORD_REC_LEN, 0, false);

/* ibfmr
 * -----
 *
 */
/* atm_v
 * Access: RO
 */
MLXSW_ITEM8(reg, ibfmr, atm_v, 0x3, 0, 1);

/* attribute_id
 * Access: RO
 */
MLXSW_ITEM16(reg, ibfmr, attribute_id, 0xa, 0, 16);

/* attribute_modifier
 * Access: RO
 */
MLXSW_ITEM32(reg, ibfmr, attribute_modifier, 0xc, 0, 32);

/* ppbs
 * ----
 *
 */
/* swid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppbs, swid, 0x4, 0, 8);

/* type
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, type, 0x5, 4, 4);

/* pbs_ptr
 * Access: INDEX
 */
MLXSW_ITEM32(reg, ppbs, pbs_ptr, 0x8, 0, 24);

/* ppbs_unicast_v_fid
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, ppbs_unicast_v_fid, 0xc, 7, 1);

/* ppbs_unicast_set_vid
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, ppbs_unicast_set_vid, 0xc, 6, 1);

/* ppbs_unicast_vid
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, ppbs_unicast_vid, 0xc, 0, 12);

/* ppbs_unicast_fid
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, ppbs_unicast_fid, 0xe, 0, 16);

/* ppbs_unicast_action
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, ppbs_unicast_action, 0x10, 4, 4);

/* ppbs_unicast_system_port
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, ppbs_unicast_system_port, 0x12, 0, 16);

/* unicast_lag_uvid
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, unicast_lag_uvid, 0xe, 7, 1);

/* unicast_lag_vid
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, unicast_lag_vid, 0xe, 0, 12);

/* unicast_lag_lag_id
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, unicast_lag_lag_id, 0x12, 0, 10);

/* ppbs_multicast_v_fid
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, ppbs_multicast_v_fid, 0xc, 7, 1);

/* ppbs_multicast_pgi
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, ppbs_multicast_pgi, 0xc, 0, 13);

/* ppbs_multicast_fid
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, ppbs_multicast_fid, 0xe, 0, 16);

/* ppbs_multicast_mid
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, ppbs_multicast_mid, 0x12, 0, 16);

/* unicast_tunnel_udip
 * Access: RW
 */
MLXSW_ITEM32(reg, ppbs, unicast_tunnel_udip, 0xc, 0, 32);

/* unicast_tunnel_protocol
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, unicast_tunnel_protocol, 0x10, 3, 1);

/* unicast_tunnel_gen_enc
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, unicast_tunnel_gen_enc, 0x10, 2, 1);

/* unicast_tunnel_ecmp_size
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, unicast_tunnel_ecmp_size, 0x1a, 0, 13);

/* multicast_tunnel_underlay_mc_ptr_msb
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, multicast_tunnel_underlay_mc_ptr_msb, 0xc, 0, 16);

/* multicast_tunnel_fid
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, multicast_tunnel_fid, 0xe, 0, 16);

/* multicast_tunnel_underlay_mc_ptr_lsb
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, multicast_tunnel_underlay_mc_ptr_lsb, 0x10, 0, 8);

/* multicast_tunnel_v_fid
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, multicast_tunnel_v_fid, 0x11, 7, 1);

/* multicast_tunnel_mid
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, multicast_tunnel_mid, 0x12, 0, 16);

/* multicast_tunnel_ecmp_size
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, multicast_tunnel_ecmp_size, 0x1a, 0, 13);

/* fppc
 * ----
 *
 */
/* as_ftlv
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, as_ftlv, 0x0, 4, 1);

/* fpp
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fppc, fpp, 0x3, 0, 8);

/* empty_fph
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, empty_fph, 0x7, 0, 1);

/* field_offset_dword_prot
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, field_offset_dword_prot, 0x12, 0, 2);

/* field_offset_bytes_prot
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, field_offset_bytes_prot, 0x13, 0, 2);

/* field_mask_prot_non_tlv
 * Access: RW
 */
MLXSW_ITEM16(reg, fppc, field_mask_prot_non_tlv, 0x16, 0, 16);

/* field_mask_prot_tlv
 * Access: RW
 */
MLXSW_ITEM32(reg, fppc, field_mask_prot_tlv, 0x18, 0, 24);

/* field_offset_dword_length
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, field_offset_dword_length, 0x22, 0, 2);

/* field_offset_bytes_length
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, field_offset_bytes_length, 0x23, 0, 2);

/* field_mask_length
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, field_mask_length, 0x27, 0, 8);

/* length_math_bitmap
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, length_math_bitmap, 0x28, 4, 1);

/* length_math_add_pos
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, length_math_add_pos, 0x28, 0, 1);

/* length_math_add
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, length_math_add, 0x29, 0, 7);

/* length_math_shift_left
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, length_math_shift_left, 0x2a, 0, 1);

/* length_math_shift
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, length_math_shift, 0x2b, 0, 3);

/* fexp_st_en
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, fexp_st_en, 0x30, 7, 1);

/* fexp_st_id
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, fexp_st_id, 0x30, 0, 3);

/* fexp_st_tlv_type
 * Access: RW
 */
MLXSW_ITEM32(reg, fppc, fexp_st_tlv_type, 0x30, 0, 24);

/* fexp_of_en
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, fexp_of_en, 0x40, 7, 1);

/* fexp_of_id
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, fexp_of_id, 0x40, 0, 3);

/* fexp_of_tlv_type
 * Access: RW
 */
MLXSW_ITEM32(reg, fppc, fexp_of_tlv_type, 0x40, 0, 24);

/* field_offset_dword_fexp_of
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, field_offset_dword_fexp_of, 0x46, 0, 2);

/* field_offset_bytes_fexp_of
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, field_offset_bytes_fexp_of, 0x47, 0, 2);

/* field_mask_fexp_of
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, field_mask_fexp_of, 0x4b, 0, 8);

/* fexp_of_math_bitmap
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, fexp_of_math_bitmap, 0x4c, 4, 1);

/* fexp_of_math_add_pos
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, fexp_of_math_add_pos, 0x4c, 0, 1);

/* fexp_of_math_add
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, fexp_of_math_add, 0x4d, 0, 7);

/* fexp_of_math_shift_left
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, fexp_of_math_shift_left, 0x4e, 0, 1);

/* fexp_of_math_shift
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, fexp_of_math_shift, 0x4f, 0, 3);

/* my_ftlv_en
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, my_ftlv_en, 0x50, 7, 1);

/* my_ftlv_start
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, my_ftlv_start, 0x51, 0, 6);

/* my_ftlv_fpp
 * Access: RW
 */
MLXSW_ITEM8(reg, fppc, my_ftlv_fpp, 0x53, 0, 8);

/* mtewe
 * -----
 *
 */
/* last_sensor
 * Access: RO
 */
MLXSW_ITEM16(reg, mtewe, last_sensor, 0x0, 0, 12);

/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mtewe, slot_index, 0x2, 4, 4);

/* sensor_count
 * Access: RO
 */
MLXSW_ITEM16(reg, mtewe, sensor_count, 0x2, 0, 12);

/* sensor_warning_0
 * Access: RO
 */
MLXSW_ITEM32(reg, mtewe, sensor_warning_0, 0x4, 0, 32);

/* hgcr
 * ----
 *
 */
/* truncation_size
 * Access: RW
 */
MLXSW_ITEM16(reg, hgcr, truncation_size, 0x2, 0, 14);

/* xlkbu
 * -----
 *
 */
/* data_type
 * Access: OP
 */
MLXSW_ITEM8(reg, xlkbu, data_type, 0x7, 0, 4);

/* value
 * Access: OP
 */
MLXSW_ITEM32_INDEXED(reg, xlkbu, value, 0x40, 0, 32, 4, 0, false);

/* mask
 * Access: OP
 */
MLXSW_ITEM32_INDEXED(reg, xlkbu, mask, 0x80, 0, 32, 4, 0, false);

/* new_value
 * Access: OP
 */
MLXSW_ITEM32_INDEXED(reg, xlkbu, new_value, 0xc0, 0, 32, 4, 0, false);

/* new_value_mask
 * Access: OP
 */
MLXSW_ITEM32_INDEXED(reg, xlkbu, new_value_mask, 0x100, 0, 32, 4, 0, false);

/* xrmt
 * ----
 *
 */
/* index
 * Access: INDEX
 */
MLXSW_ITEM32(reg, xrmt, index, 0x4, 0, 20);

/* l0_val
 * Access: RW
 */
MLXSW_ITEM8(reg, xrmt, l0_val, 0x10, 0, 8);

/* l0_vec
 * Access: RW
 */
MLXSW_ITEM8(reg, xrmt, l0_vec, 0x11, 0, 8);

/* l1_val
 * Access: RW
 */
MLXSW_ITEM8(reg, xrmt, l1_val, 0x12, 0, 8);

/* l1_vec
 * Access: RW
 */
MLXSW_ITEM8(reg, xrmt, l1_vec, 0x13, 0, 8);

/* cepc
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM16(reg, cepc, local_port, 0x0, 0, 9);

/* pp
 * Access: INDEX
 */
MLXSW_ITEM8(reg, cepc, pp, 0x2, 7, 1);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, cepc, lp_msb, 0x2, 4, 2);

/* en_ed
 * Access: RW
 */
MLXSW_ITEM8(reg, cepc, en_ed, 0x7, 0, 1);

/* reiv
 * ----
 *
 */
/* port_page
 * Access: INDEX
 */
MLXSW_ITEM8(reg, reiv, port_page, 0x3, 0, 4);

/* erif
 * Access: INDEX
 */
MLXSW_ITEM16(reg, reiv, erif, 0x6, 0, 16);

/* update
 * Access: OP
 */
MLXSW_ITEM8_INDEXED(reg, reiv, update, MLXSW_REIV_ELPORT_RECORD_BASE_LEN, 7, 1, MLXSW_REIV_ELPORT_RECORD_REC_LEN, 0, false);

/* evid
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, reiv, evid, MLXSW_REIV_ELPORT_RECORD_BASE_LEN + 2, 0, 12, MLXSW_REIV_ELPORT_RECORD_REC_LEN, 0, false);

/* ppad
 * ----
 *
 */
/* single_base_mac
 * Access: OP
 */
MLXSW_ITEM8(reg, ppad, single_base_mac, 0x0, 4, 1);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppad, pnat, 0x0, 2, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppad, lp_msb, 0x0, 0, 2);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppad, local_port, 0x1, 0, 8);

/* mac
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, ppad, mac, 0x2, 6);

/* prei
 * ----
 *
 */
/* version
 * Access: RO
 */
MLXSW_ITEM8(reg, prei, version, 0x0, 0, 4);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, prei, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, prei, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, prei, lp_msb, 0x2, 4, 2);

/* ber_sel
 * Access: INDEX
 */
MLXSW_ITEM8(reg, prei, ber_sel, 0x3, 4, 3);

/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, prei, status, 0x3, 0, 2);

/* en
 * Access: WO
 */
MLXSW_ITEM8(reg, prei, en, 0x4, 7, 1);

/* ber_mantissa
 * Access: RW
 */
MLXSW_ITEM8(reg, prei, ber_mantissa, 0x6, 0, 4);

/* ber_exp
 * Access: RW
 */
MLXSW_ITEM8(reg, prei, ber_exp, 0x7, 0, 8);

/* lane_rate_cap
 * Access: RO
 */
MLXSW_ITEM16(reg, prei, lane_rate_cap, 0x8, 0, 16);

/* mixer_offset0
 * Access: RW
 */
MLXSW_ITEM16(reg, prei, mixer_offset0, 0x10, 0, 16);

/* mixer_offset1
 * Access: RW
 */
MLXSW_ITEM16(reg, prei, mixer_offset1, 0x12, 0, 16);

/* mocs
 * ----
 *
 */
/* type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mocs, type, 0x3, 0, 8);

/* clear
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, clear, 0x5, 0, 1);

/* opcode
 * Access: WO
 */
MLXSW_ITEM8(reg, mocs, opcode, 0x6, 0, 1);

/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, mocs, status, 0x7, 0, 2);

/* hi
 * Access: 
 */
MLXSW_ITEM32(reg, mocs, hi, 0x8, 0, 32);

/* lo
 * Access: 
 */
MLXSW_ITEM32(reg, mocs, lo, 0xc, 0, 32);

/* mocs_ppcnt_port_mask
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mocs, mocs_ppcnt_port_mask, 0x20, 0, 32, 4, 0, false);

/* mocs_ppcnt_grp_mask
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mocs, mocs_ppcnt_grp_mask, 0x60, 0, 32, 4, 0, false);

/* mocs_ppcnt_tc_mask
 * Access: RW
 */
MLXSW_ITEM32(reg, mocs, mocs_ppcnt_tc_mask, 0x70, 0, 32);

/* mocs_ppcnt_prio_mask
 * Access: RW
 */
MLXSW_ITEM16(reg, mocs, mocs_ppcnt_prio_mask, 0x74, 0, 16);

/* mocs_ppcnt_rx_buffer_mask
 * Access: RW
 */
MLXSW_ITEM16(reg, mocs, mocs_ppcnt_rx_buffer_mask, 0x76, 0, 16);

/* mocs_mgpcb_flush
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, mocs_mgpcb_flush, 0x20, 7, 1);

/* mocs_mgpcb_num_rec
 * Access: RW
 */
MLXSW_ITEM32(reg, mocs, mocs_mgpcb_num_rec, 0x20, 0, 24);

/* mocs_mgpcb_counter_index_base
 * Access: RW
 */
MLXSW_ITEM32(reg, mocs, mocs_mgpcb_counter_index_base, 0x24, 0, 24);

/* mocs_pbsr_port_mask
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mocs, mocs_pbsr_port_mask, 0x20, 0, 32, 4, 0, false);

/* mocs_sbsrd_curr
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, mocs_sbsrd_curr, 0x20, 7, 1);

/* mocs_sbsrd_snap
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, mocs_sbsrd_snap, 0x20, 6, 1);

/* mocs_sbsrd_cells
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, mocs_sbsrd_cells, 0x20, 5, 1);

/* mocs_sbsrd_desc
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, mocs_sbsrd_desc, 0x20, 4, 1);

/* mocs_ceer_port_mask
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mocs, mocs_ceer_port_mask, 0x20, 0, 32, 4, 0, false);

/* mocs_mafbi_flush
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, mocs_mafbi_flush, 0x20, 7, 1);

/* mocs_mafbi_type
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, mocs_mafbi_type, 0x20, 4, 2);

/* mocs_mafbi_num_rec
 * Access: RW
 */
MLXSW_ITEM32(reg, mocs, mocs_mafbi_num_rec, 0x20, 0, 24);

/* mocs_mafbi_counter_index_base
 * Access: RW
 */
MLXSW_ITEM32(reg, mocs, mocs_mafbi_counter_index_base, 0x24, 0, 24);

/* pllp
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pllp, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pllp, lp_msb, 0x2, 4, 2);

/* label_port
 * Access: RO
 */
MLXSW_ITEM8(reg, pllp, label_port, 0x3, 0, 8);

/* split_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, pllp, split_stat, 0x5, 0, 4);

/* split_num
 * Access: RO
 */
MLXSW_ITEM8(reg, pllp, split_num, 0x7, 0, 4);

/* slot_num
 * Access: RO
 */
MLXSW_ITEM8(reg, pllp, slot_num, 0xb, 0, 4);

/* qeec
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qeec, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qeec, lp_msb, 0x2, 4, 2);

/* element_hierarchy
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qeec, element_hierarchy, 0x5, 0, 4);

/* element_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qeec, element_index, 0x7, 0, 8);

/* next_element_index
 * Access: RW
 */
MLXSW_ITEM8(reg, qeec, next_element_index, 0xb, 0, 8);

/* mise
 * Access: RW
 */
MLXSW_ITEM8(reg, qeec, mise, 0xc, 7, 1);

/* ptps
 * Access: RW
 */
MLXSW_ITEM8(reg, qeec, ptps, 0xc, 5, 1);

/* pb
 * Access: RW
 */
MLXSW_ITEM8(reg, qeec, pb, 0xc, 4, 1);

/* min_shaper_rate
 * Access: RW
 */
MLXSW_ITEM32(reg, qeec, min_shaper_rate, 0xc, 0, 28);

/* mase
 * Access: RW
 */
MLXSW_ITEM8(reg, qeec, mase, 0x10, 7, 1);

/* max_shaper_rate
 * Access: RW
 */
MLXSW_ITEM32(reg, qeec, max_shaper_rate, 0x10, 0, 31);

/* pqe
 * Access: RW
 */
MLXSW_ITEM8(reg, qeec, pqe, 0x14, 7, 1);

/* phantom_queue_rate
 * Access: RW
 */
MLXSW_ITEM32(reg, qeec, phantom_queue_rate, 0x14, 0, 31);

/* de
 * Access: RW
 */
MLXSW_ITEM8(reg, qeec, de, 0x18, 7, 1);

/* dwrr
 * Access: RW
 */
MLXSW_ITEM8(reg, qeec, dwrr, 0x1a, 7, 1);

/* dwrr_weight
 * Access: RW
 */
MLXSW_ITEM8(reg, qeec, dwrr_weight, 0x1b, 0, 8);

/* min_shaper_bs
 * Access: RW
 */
MLXSW_ITEM8(reg, qeec, min_shaper_bs, 0x1d, 0, 6);

/* max_shaper_bs
 * Access: RW
 */
MLXSW_ITEM8(reg, qeec, max_shaper_bs, 0x1f, 0, 6);

/* rmftad
 * ------
 *
 */
/* op
 * Access: OP
 */
MLXSW_ITEM8(reg, rmftad, op, 0x0, 6, 2);

/* type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rmftad, type, 0x1, 4, 2);

/* offset
 * Access: INDEX
 */
MLXSW_ITEM16(reg, rmftad, offset, 0x2, 0, 16);

/* num_rec
 * Access: OP
 */
MLXSW_ITEM16(reg, rmftad, num_rec, 0x6, 0, 13);

/* activity_vector
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, rmftad, activity_vector, 0x20, 0, 32, 4, 0, false);

/* rlcmle
 * ------
 *
 */
/* protocol
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rlcmle, protocol, 0x0, 0, 4);

/* op
 * Access: OP
 */
MLXSW_ITEM8(reg, rlcmle, op, 0x1, 4, 3);

/* m_idx
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rlcmle, m_idx, 0x3, 0, 1);

/* virtual_router
 * Access: INDEX
 */
MLXSW_ITEM16(reg, rlcmle, virtual_router, 0x4, 0, 16);

/* l_value
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rlcmle, l_value, 0x7, 0, 7);

/* dip
 * Access: INDEX
 */
MLXSW_ITEM32_INDEXED(reg, rlcmle, dip, 0xc, 0, 32, 4, 0, false);

/* action_type
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcmle, action_type, 0x1f, 0, 2);

/* remote_action_trap_action
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcmle, remote_action_trap_action, 0x20, 4, 4);

/* remote_action_trap_id
 * Access: RW
 */
MLXSW_ITEM16(reg, rlcmle, remote_action_trap_id, 0x22, 0, 9);

/* remote_action_adjacency_index
 * Access: RW
 */
MLXSW_ITEM32(reg, rlcmle, remote_action_adjacency_index, 0x24, 0, 24);

/* remote_action_ecmp_size
 * Access: RW
 */
MLXSW_ITEM16(reg, rlcmle, remote_action_ecmp_size, 0x2a, 0, 13);

/* local_action_trap_action
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcmle, local_action_trap_action, 0x20, 4, 4);

/* local_action_trap_id
 * Access: RW
 */
MLXSW_ITEM16(reg, rlcmle, local_action_trap_id, 0x22, 0, 9);

/* local_action_local_erif
 * Access: RW
 */
MLXSW_ITEM16(reg, rlcmle, local_action_local_erif, 0x26, 0, 16);

/* ip2me_trap_action
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcmle, ip2me_trap_action, 0x20, 4, 4);

/* ip2me_v
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcmle, ip2me_v, 0x24, 7, 1);

/* ip2me_tunnel_ptr
 * Access: RW
 */
MLXSW_ITEM32(reg, rlcmle, ip2me_tunnel_ptr, 0x24, 0, 24);

/* counter_set_type
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcmle, counter_set_type, 0x34, 0, 8);

/* counter_index
 * Access: RW
 */
MLXSW_ITEM32(reg, rlcmle, counter_index, 0x34, 0, 24);

/* mcqi
 * ----
 *
 */
/* read_pending_component
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mcqi, read_pending_component, 0x0, 7, 1);

/* device_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, mcqi, device_index, 0x0, 0, 12);

/* component_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, mcqi, component_index, 0x2, 0, 16);

/* device_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mcqi, device_type, 0x7, 0, 8);

/* info_type
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, info_type, 0xb, 0, 5);

/* info_size
 * Access: RO
 */
MLXSW_ITEM32(reg, mcqi, info_size, 0xc, 0, 32);

/* offset
 * Access: RW
 */
MLXSW_ITEM32(reg, mcqi, offset, 0x10, 0, 32);

/* data_size
 * Access: RW
 */
MLXSW_ITEM16(reg, mcqi, data_size, 0x16, 0, 16);

/* mcqi_cap_supported_info_bitmask
 * Access: RO
 */
MLXSW_ITEM32(reg, mcqi, mcqi_cap_supported_info_bitmask, 0x18, 0, 32);

/* mcqi_cap_component_size
 * Access: RO
 */
MLXSW_ITEM32(reg, mcqi, mcqi_cap_component_size, 0x1c, 0, 32);

/* mcqi_cap_max_component_size
 * Access: RO
 */
MLXSW_ITEM32(reg, mcqi, mcqi_cap_max_component_size, 0x20, 0, 32);

/* mcqi_cap_log_mcda_word_size
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_cap_log_mcda_word_size, 0x24, 4, 4);

/* mcqi_cap_mcda_max_write_size
 * Access: RO
 */
MLXSW_ITEM16(reg, mcqi, mcqi_cap_mcda_max_write_size, 0x26, 0, 16);

/* mcqi_cap_rd_en
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_cap_rd_en, 0x28, 7, 1);

/* mcqi_cap_signed_updates_only
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, mcqi_cap_signed_updates_only, 0x28, 6, 1);

/* mcqi_cap_match_chip_id
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, mcqi_cap_match_chip_id, 0x28, 5, 1);

/* mcqi_cap_match_psid
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, mcqi_cap_match_psid, 0x28, 4, 1);

/* mcqi_cap_check_user_timestamp
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, mcqi_cap_check_user_timestamp, 0x28, 3, 1);

/* mcqi_cap_match_base_guid_mac
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, mcqi_cap_match_base_guid_mac, 0x28, 2, 1);

/* mcqi_version_build_time_valid
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, mcqi_version_build_time_valid, 0x18, 5, 1);

/* mcqi_version_user_defined_time_valid
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, mcqi_version_user_defined_time_valid, 0x18, 4, 1);

/* mcqi_version_version_string_length
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, mcqi_version_version_string_length, 0x1b, 0, 8);

/* mcqi_version_version
 * Access: RW
 */
MLXSW_ITEM32(reg, mcqi, mcqi_version_version, 0x1c, 0, 32);

/* mcqi_version_build_time_hi
 * Access: 
 */
MLXSW_ITEM32(reg, mcqi, mcqi_version_build_time_hi, 0x20, 0, 32);

/* mcqi_version_build_time_lo
 * Access: 
 */
MLXSW_ITEM32(reg, mcqi, mcqi_version_build_time_lo, 0x24, 0, 32);

/* mcqi_version_user_defined_time_hi
 * Access: 
 */
MLXSW_ITEM32(reg, mcqi, mcqi_version_user_defined_time_hi, 0x28, 0, 32);

/* mcqi_version_user_defined_time_lo
 * Access: 
 */
MLXSW_ITEM32(reg, mcqi, mcqi_version_user_defined_time_lo, 0x2c, 0, 32);

/* mcqi_version_build_tool_version
 * Access: RW
 */
MLXSW_ITEM32(reg, mcqi, mcqi_version_build_tool_version, 0x30, 0, 32);

/* mcqi_version_version_string
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, mcqi, mcqi_version_version_string, 0x38, 92);

/* mcqi_activation_method_self_activation
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_activation_method_self_activation, 0x1b, 6, 1);

/* mcqi_activation_method_pending_server_ac_power_cycle
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_activation_method_pending_server_ac_power_cycle, 0x1b, 5, 1);

/* mcqi_activation_method_pending_server_dc_power_cycle
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_activation_method_pending_server_dc_power_cycle, 0x1b, 4, 1);

/* mcqi_activation_method_pending_server_reboot
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_activation_method_pending_server_reboot, 0x1b, 3, 1);

/* mcqi_activation_method_pending_fw_reset
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_activation_method_pending_fw_reset, 0x1b, 2, 1);

/* mcqi_activation_method_auto_activate
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_activation_method_auto_activate, 0x1b, 1, 1);

/* mcqi_activation_method_all_hosts_sync
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_activation_method_all_hosts_sync, 0x1b, 0, 1);

/* mcqi_linkx_properties_fw_image_info_bitmap
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_linkx_properties_fw_image_info_bitmap, 0x19, 0, 8);

/* mcqi_linkx_properties_fw_image_status_bitmap
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_linkx_properties_fw_image_status_bitmap, 0x1b, 0, 8);

/* mcqi_linkx_properties_image_a_major
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_linkx_properties_image_a_major, 0x1e, 0, 8);

/* mcqi_linkx_properties_image_a_minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_linkx_properties_image_a_minor, 0x1f, 0, 8);

/* mcqi_linkx_properties_image_a_subminor
 * Access: RO
 */
MLXSW_ITEM16(reg, mcqi, mcqi_linkx_properties_image_a_subminor, 0x22, 0, 16);

/* mcqi_linkx_properties_image_b_major
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_linkx_properties_image_b_major, 0x26, 0, 8);

/* mcqi_linkx_properties_image_b_minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_linkx_properties_image_b_minor, 0x27, 0, 8);

/* mcqi_linkx_properties_image_b_subminor
 * Access: RO
 */
MLXSW_ITEM16(reg, mcqi, mcqi_linkx_properties_image_b_subminor, 0x2a, 0, 16);

/* mcqi_linkx_properties_factory_image_major
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_linkx_properties_factory_image_major, 0x2e, 0, 8);

/* mcqi_linkx_properties_factory_image_minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_linkx_properties_factory_image_minor, 0x2f, 0, 8);

/* mcqi_linkx_properties_factory_image_subminor
 * Access: RO
 */
MLXSW_ITEM16(reg, mcqi, mcqi_linkx_properties_factory_image_subminor, 0x32, 0, 16);

/* mcqi_linkx_properties_activation_type
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_linkx_properties_activation_type, 0x36, 2, 4);

/* mcqi_linkx_properties_management_interface_protocol
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_linkx_properties_management_interface_protocol, 0x37, 0, 6);

/* mcqi_linkx_properties_vendor_sn
 * Access: RO
 */
MLXSW_ITEM16(reg, mcqi, mcqi_linkx_properties_vendor_sn, 0x3a, 0, 16);

/* chltr
 * -----
 *
 */
/* hlt_table_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, chltr, hlt_table_index, 0x3, 0, 8);

/* high_latency_thr
 * Access: RW
 */
MLXSW_ITEM32(reg, chltr, high_latency_thr, 0x8, 0, 20);

/* tngcr
 * -----
 *
 */
/* type
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, type, 0x3, 0, 4);

/* nve_valid
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, nve_valid, 0x4, 7, 1);

/* nve_decap_ttl
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, nve_decap_ttl, 0x5, 0, 2);

/* nve_ttlc
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, nve_ttlc, 0x6, 0, 1);

/* nve_ttl_uc
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, nve_ttl_uc, 0x7, 0, 8);

/* nve_ttl_mc
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, nve_ttl_mc, 0xb, 0, 8);

/* nve_flc
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, nve_flc, 0xc, 1, 1);

/* nve_flh
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, nve_flh, 0xc, 0, 1);

/* nve_fl_prefix
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, nve_fl_prefix, 0xc, 8, 12);

/* nve_fl_suffix
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, nve_fl_suffix, 0xf, 0, 8);

/* nve_enc_orig
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, nve_enc_orig, 0x10, 7, 1);

/* nve_enc_orig_we
 * Access: WO
 */
MLXSW_ITEM8(reg, tngcr, nve_enc_orig_we, 0x10, 6, 1);

/* nve_udp_sport_type
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, nve_udp_sport_type, 0x10, 0, 1);

/* et_vlan
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, et_vlan, 0x11, 4, 2);

/* nve_udp_sport_prefix
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, nve_udp_sport_prefix, 0x12, 0, 8);

/* nve_group_size_mc
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, nve_group_size_mc, 0x1b, 0, 8);

/* nve_group_size_flood
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, nve_group_size_flood, 0x1f, 0, 8);

/* learn_enable
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, learn_enable, 0x20, 7, 1);

/* underlay_virtual_router
 * Access: RW
 */
MLXSW_ITEM16(reg, tngcr, underlay_virtual_router, 0x22, 0, 16);

/* underlay_rif
 * Access: RW
 */
MLXSW_ITEM16(reg, tngcr, underlay_rif, 0x26, 0, 16);

/* usipv4
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, usipv4, 0x28, 0, 32);

/* usipv6
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, tngcr, usipv6, 0x30, 0, 32, 4, 0, false);

/* header0_bit_set
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, header0_bit_set, 0x40, 0, 32);

/* molp
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, molp, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, molp, lp_msb, 0x2, 4, 2);

/* label_port
 * Access: RW
 */
MLXSW_ITEM16(reg, molp, label_port, 0x6, 0, 16);

/* hahcr
 * -----
 *
 */
/* sh
 * Access: RW
 */
MLXSW_ITEM8(reg, hahcr, sh, 0x2, 0, 1);

/* type
 * Access: RW
 */
MLXSW_ITEM8(reg, hahcr, type, 0x3, 0, 4);

/* general_fields
 * Access: RW
 */
MLXSW_ITEM32(reg, hahcr, general_fields, 0xc, 0, 32);

/* outer_header_enables
 * Access: RW
 */
MLXSW_ITEM16(reg, hahcr, outer_header_enables, 0x12, 0, 16);

/* outer_header_fields_enable
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, hahcr, outer_header_fields_enable, 0x14, 0, 32, 4, 0, false);

/* inner_header_enables
 * Access: RW
 */
MLXSW_ITEM16(reg, hahcr, inner_header_enables, 0x2e, 0, 16);

/* hi
 * Access: 
 */
MLXSW_ITEM32(reg, hahcr, hi, 0x30, 0, 32);

/* lo
 * Access: 
 */
MLXSW_ITEM32(reg, hahcr, lo, 0x34, 0, 32);

/* mddt
 * ----
 *
 */
/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mddt, slot_index, 0x2, 0, 4);

/* device_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mddt, device_index, 0x3, 0, 8);

/* read_size
 * Access: OP
 */
MLXSW_ITEM8(reg, mddt, read_size, 0x4, 0, 8);

/* write_size
 * Access: OP
 */
MLXSW_ITEM8(reg, mddt, write_size, 0x5, 0, 8);

/* type
 * Access: OP
 */
MLXSW_ITEM8(reg, mddt, type, 0x7, 0, 2);

/* prm_register_payload_status
 * Access: RO
 */
MLXSW_ITEM8(reg, mddt, prm_register_payload_status, 0xc, 0, 8);

/* prm_register_payload_method
 * Access: OP
 */
MLXSW_ITEM8(reg, mddt, prm_register_payload_method, 0xd, 6, 2);

/* prm_register_payload_register_id
 * Access: INDEX
 */
MLXSW_ITEM16(reg, mddt, prm_register_payload_register_id, 0xe, 0, 16);

/* prm_register_payload_register_data
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mddt, prm_register_payload_register_data, 0x10, 0, 32, 4, 0, false);

/* command_payload_data
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mddt, command_payload_data, 0xc, 0, 32, 4, 0, false);

/* crspace_access_payload_address
 * Access: WO
 */
MLXSW_ITEM32(reg, mddt, crspace_access_payload_address, 0xc, 0, 32);

/* crspace_access_payload_data
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mddt, crspace_access_payload_data, 0x10, 0, 32, 4, 0, false);

/* rips
 * ----
 *
 */
/* index
 * Access: INDEX
 */
MLXSW_ITEM32(reg, rips, index, 0x0, 0, 24);

/* ipv6
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, rips, ipv6, 0x4, 0, 32, 4, 0, false);

/* tndem
 * -----
 *
 */
/* underlay_ecn
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tndem, underlay_ecn, 0x4, 0, 2);

/* overlay_ecn
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tndem, overlay_ecn, 0x5, 0, 2);

/* eip_ecn
 * Access: RW
 */
MLXSW_ITEM8(reg, tndem, eip_ecn, 0x6, 0, 2);

/* trap_en
 * Access: RW
 */
MLXSW_ITEM8(reg, tndem, trap_en, 0x8, 4, 4);

/* trap_id
 * Access: RW
 */
MLXSW_ITEM16(reg, tndem, trap_id, 0xa, 0, 9);

/* sfdb_v2
 * -------
 *
 */
/* key
 * Access: INDEX
 */
MLXSW_ITEM32_INDEXED(reg, sfdb_v2, key, 0x0, 0, 32, 4, 0, false);

/* key_mask
 * Access: INDEX
 */
MLXSW_ITEM32_INDEXED(reg, sfdb_v2, key_mask, 0x20, 0, 32, 4, 0, false);

/* action
 * Access: WO
 */
MLXSW_ITEM32_INDEXED(reg, sfdb_v2, action, 0x40, 0, 32, 4, 0, false);

/* action_mask
 * Access: WO
 */
MLXSW_ITEM32_INDEXED(reg, sfdb_v2, action_mask, 0x60, 0, 32, 4, 0, false);

/* count_updates
 * Access: RO
 */
MLXSW_ITEM32(reg, sfdb_v2, count_updates, 0x80, 0, 32);

/* tnumt
 * -----
 *
 */
/* record_type
 * Access: RW
 */
MLXSW_ITEM8(reg, tnumt, record_type, 0x0, 4, 4);

/* underlay_mc_ptr
 * Access: INDEX
 */
MLXSW_ITEM32(reg, tnumt, underlay_mc_ptr, 0x0, 0, 24);

/* vnext
 * Access: RW
 */
MLXSW_ITEM8(reg, tnumt, vnext, 0x4, 7, 1);

/* next_underlay_mc_ptr
 * Access: RW
 */
MLXSW_ITEM32(reg, tnumt, next_underlay_mc_ptr, 0x4, 0, 24);

/* tunnel_mc_ipv4_size
 * Access: RW
 */
MLXSW_ITEM8(reg, tnumt, tunnel_mc_ipv4_size, 0xb, 0, 3);

/* tunnel_mc_ipv4_udip
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, tnumt, tunnel_mc_ipv4_udip, 0xc, 0, 32, 4, 0, false);

/* tunnel_mc_ipv6_size
 * Access: RW
 */
MLXSW_ITEM8(reg, tnumt, tunnel_mc_ipv6_size, 0xb, 0, 3);

/* tunnel_mc_ipv6_udip_ptr
 * Access: 
 */
MLXSW_ITEM32_INDEXED(reg, tnumt, tunnel_mc_ipv6_udip_ptr, 0xc, 0, 24, 0x4, 0x0, false);

/* rlcme
 * -----
 *
 */
/* protocol
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rlcme, protocol, 0x0, 0, 4);

/* op
 * Access: OP
 */
MLXSW_ITEM8(reg, rlcme, op, 0x1, 4, 3);

/* m_idx
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rlcme, m_idx, 0x3, 0, 1);

/* virtual_router
 * Access: INDEX
 */
MLXSW_ITEM16(reg, rlcme, virtual_router, 0x4, 0, 16);

/* dip
 * Access: INDEX
 */
MLXSW_ITEM32_INDEXED(reg, rlcme, dip, 0xc, 0, 32, 4, 0, false);

/* action_type
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcme, action_type, 0x1f, 0, 2);

/* action
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, rlcme, action, 0x20, 0, 32, 4, 0, false);

/* counter_set_type
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcme, counter_set_type, 0x34, 0, 8);

/* counter_index
 * Access: RW
 */
MLXSW_ITEM32(reg, rlcme, counter_index, 0x34, 0, 24);

/* action_valid
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcme, action_valid, 0x38, 1, 1);

/* l_vector
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcme, l_vector, 0x3a, 0, 4);

/* l_value
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcme, l_value, 0x3b, 0, 7);

/* fpts
 * ----
 *
 */
/* global
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fpts, global, 0x0, 7, 1);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fpts, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fpts, lp_msb, 0x2, 4, 2);

/* tran_type
 * Access: RW
 */
MLXSW_ITEM8(reg, fpts, tran_type, 0x7, 0, 4);

/* next_ph
 * Access: RW
 */
MLXSW_ITEM8(reg, fpts, next_ph, 0xb, 0, 8);

/* htacg
 * -----
 *
 */
/* go
 * Access: RW
 */
MLXSW_ITEM8(reg, htacg, go, 0x1, 0, 1);

/* grepper_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, htacg, grepper_index, 0x3, 0, 4);

/* tac_flush
 * Access: RW
 */
MLXSW_ITEM8(reg, htacg, tac_flush, 0x7, 0, 2);

/* fields_mirror_reason
 * Access: RW
 */
MLXSW_ITEM8(reg, htacg, fields_mirror_reason, 0x13, 0, 8);

/* fields_rdq
 * Access: RW
 */
MLXSW_ITEM8(reg, htacg, fields_rdq, 0x14, 0, 6);

/* fields_trap_id
 * Access: RW
 */
MLXSW_ITEM16(reg, htacg, fields_trap_id, 0x16, 0, 10);

/* fields_mirror_tclass
 * Access: RW
 */
MLXSW_ITEM8(reg, htacg, fields_mirror_tclass, 0x19, 0, 5);

/* fields_mirror_tx_acl_system_port
 * Access: RW
 */
MLXSW_ITEM8(reg, htacg, fields_mirror_tx_acl_system_port, 0x1b, 0, 8);

/* fields_max_egress_buffer_fill_level
 * Access: RW
 */
MLXSW_ITEM16(reg, htacg, fields_max_egress_buffer_fill_level, 0x1e, 0, 16);

/* fields_last_ts
 * Access: RW
 */
MLXSW_ITEM32(reg, htacg, fields_last_ts, 0x20, 0, 32);

/* fields_pkt_count
 * Access: RW
 */
MLXSW_ITEM32(reg, htacg, fields_pkt_count, 0x24, 0, 32);

/* fields_byte_count_high
 * Access: RW
 */
MLXSW_ITEM8(reg, htacg, fields_byte_count_high, 0x2b, 0, 8);

/* fields_byte_count_low
 * Access: RW
 */
MLXSW_ITEM32(reg, htacg, fields_byte_count_low, 0x2c, 0, 32);

/* mask_mirror_reason
 * Access: RW
 */
MLXSW_ITEM8(reg, htacg, mask_mirror_reason, 0x53, 0, 8);

/* mask_rdq
 * Access: RW
 */
MLXSW_ITEM8(reg, htacg, mask_rdq, 0x54, 0, 6);

/* mask_trap_id
 * Access: RW
 */
MLXSW_ITEM16(reg, htacg, mask_trap_id, 0x56, 0, 10);

/* mask_mirror_tclass
 * Access: RW
 */
MLXSW_ITEM8(reg, htacg, mask_mirror_tclass, 0x59, 0, 5);

/* mask_mirror_tx_acl_system_port
 * Access: RW
 */
MLXSW_ITEM8(reg, htacg, mask_mirror_tx_acl_system_port, 0x5b, 0, 8);

/* mask_max_egress_buffer_fill_level
 * Access: RW
 */
MLXSW_ITEM16(reg, htacg, mask_max_egress_buffer_fill_level, 0x5e, 0, 16);

/* mask_last_ts
 * Access: RW
 */
MLXSW_ITEM32(reg, htacg, mask_last_ts, 0x60, 0, 32);

/* mask_pkt_count
 * Access: RW
 */
MLXSW_ITEM32(reg, htacg, mask_pkt_count, 0x64, 0, 32);

/* mask_byte_count_high
 * Access: RW
 */
MLXSW_ITEM8(reg, htacg, mask_byte_count_high, 0x6b, 0, 8);

/* mask_byte_count_low
 * Access: RW
 */
MLXSW_ITEM32(reg, htacg, mask_byte_count_low, 0x6c, 0, 32);

/* pevpb
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pevpb, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pevpb, lp_msb, 0x2, 4, 2);

/* ev
 * Access: RW
 */
MLXSW_ITEM8(reg, pevpb, ev, 0x7, 0, 1);

/* sfgc
 * ----
 *
 */
/* type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sfgc, type, 0x3, 0, 4);

/* bridge_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sfgc, bridge_type, 0x4, 0, 3);

/* table_type
 * Access: RW
 */
MLXSW_ITEM8(reg, sfgc, table_type, 0x5, 0, 3);

/* flood_table
 * Access: RW
 */
MLXSW_ITEM8(reg, sfgc, flood_table, 0x7, 0, 6);

/* counter_set_type
 * Access: RW
 */
MLXSW_ITEM8(reg, sfgc, counter_set_type, 0xc, 0, 8);

/* counter_index
 * Access: RW
 */
MLXSW_ITEM32(reg, sfgc, counter_index, 0xc, 0, 24);

/* mid_base
 * Access: RW
 */
MLXSW_ITEM16(reg, sfgc, mid_base, 0x12, 0, 16);

/* mcion
 * -----
 *
 */
/* module
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mcion, module, 0x1, 0, 8);

/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mcion, slot_index, 0x2, 4, 4);

/* module_status_bits
 * Access: RO
 */
MLXSW_ITEM16(reg, mcion, module_status_bits, 0x6, 0, 16);

/* tiqcr
 * -----
 *
 */
/* enc_set_dscp
 * Access: RW
 */
MLXSW_ITEM8(reg, tiqcr, enc_set_dscp, 0x4, 4, 1);

/* enc_set_sp
 * Access: RW
 */
MLXSW_ITEM8(reg, tiqcr, enc_set_sp, 0x4, 0, 1);

/* enc_dscp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, tiqcr, enc_dscp_rw, 0x7, 2, 2);

/* enc_pcp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, tiqcr, enc_pcp_rw, 0x7, 0, 2);

/* dec_set_dscp
 * Access: RW
 */
MLXSW_ITEM8(reg, tiqcr, dec_set_dscp, 0x8, 4, 1);

/* dec_set_sp
 * Access: RW
 */
MLXSW_ITEM8(reg, tiqcr, dec_set_sp, 0x8, 0, 1);

/* dec_dscp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, tiqcr, dec_dscp_rw, 0xb, 2, 2);

/* dec_pcp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, tiqcr, dec_pcp_rw, 0xb, 0, 2);

/* tncr_v2
 * -------
 *
 */
/* clear_counters
 * Access: OP
 */
MLXSW_ITEM8(reg, tncr_v2, clear_counters, 0x0, 7, 1);

/* tunnel_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tncr_v2, tunnel_port, 0x3, 0, 4);

/* count_decap_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, tncr_v2, count_decap_discards_high, 0x28, 0, 32);

/* count_decap_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, tncr_v2, count_decap_discards_low, 0x2c, 0, 32);

/* count_encap_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, tncr_v2, count_encap_discards_high, 0x30, 0, 32);

/* count_encap_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, tncr_v2, count_encap_discards_low, 0x34, 0, 32);

/* pcsr
 * ----
 *
 */
/* gs
 * Access: RO
 */
MLXSW_ITEM8(reg, pcsr, gs, 0x0, 7, 1);

/* offset
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pcsr, offset, 0x3, 0, 4);

/* port_status_mask
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, pcsr, port_status_mask, 0x4, 0, 32, 4, 0, false);

/* cedr
 * ----
 *
 */
/* clear
 * Access: OP
 */
MLXSW_ITEM8(reg, cedr, clear, 0x0, 7, 1);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, cedr, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, cedr, lp_msb, 0x2, 4, 2);

/* detection_table
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, cedr, detection_table, 0x10, 0, 32, 4, 0, false);

/* xralst
 * ------
 *
 */
/* root_bin
 * Access: RW
 */
MLXSW_ITEM8(reg, xralst, root_bin, 0x5, 0, 8);

/* tree_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, xralst, tree_id, 0x7, 0, 8);

/* bin
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, xralst, bin, 0x8, 0, 16, 2, 0, false);

/* plar
 * ----
 *
 */
/* local_port_allocated
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, plar, local_port_allocated, 0x0, 0, 32, 4, 0, false);

/* iddd
 * ----
 *
 */
/* entry_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, iddd, entry_type, 0x3, 0, 8);

/* duplication
 * Access: RW
 */
MLXSW_ITEM8(reg, iddd, duplication, 0x7, 0, 5);

/* iedr
 * ----
 *
 */
/* bg
 * Access: OP
 */
MLXSW_ITEM8(reg, iedr, bg, 0x0, 0, 1);

/* num_rec
 * Access: OP
 */
MLXSW_ITEM8(reg, iedr, num_rec, 0x3, 0, 8);

/* type
 * Access: OP
 */
MLXSW_ITEM8_INDEXED(reg, iedr, type, MLXSW_IEDR_RECORD_BASE_LEN, 0, 8, MLXSW_IEDR_RECORD_REC_LEN, 0, false);

/* size
 * Access: OP
 */
MLXSW_ITEM16_INDEXED(reg, iedr, size, MLXSW_IEDR_RECORD_BASE_LEN + 2, 0, 13, MLXSW_IEDR_RECORD_REC_LEN, 0, false);

/* index_start
 * Access: OP
 */
MLXSW_ITEM32_INDEXED(reg, iedr, index_start, MLXSW_IEDR_RECORD_BASE_LEN, 0, 24, MLXSW_IEDR_RECORD_REC_LEN, 4, false);

/* ieds
 * ----
 *
 */
/* edpr
 * Access: OP
 */
MLXSW_ITEM8(reg, ieds, edpr, 0x3, 0, 1);

/* ed_status
 * Access: RO
 */
MLXSW_ITEM8(reg, ieds, ed_status, 0x7, 0, 4);

/* pmaos
 * -----
 *
 */
/* rst
 * Access: OP
 */
MLXSW_ITEM8(reg, pmaos, rst, 0x0, 7, 1);

/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmaos, slot_index, 0x0, 0, 4);

/* module
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmaos, module, 0x1, 0, 8);

/* admin_status
 * Access: RW
 */
MLXSW_ITEM8(reg, pmaos, admin_status, 0x2, 0, 4);

/* oper_status
 * Access: RO
 */
MLXSW_ITEM8(reg, pmaos, oper_status, 0x3, 0, 4);

/* ase
 * Access: WO
 */
MLXSW_ITEM8(reg, pmaos, ase, 0x4, 7, 1);

/* ee
 * Access: WO
 */
MLXSW_ITEM8(reg, pmaos, ee, 0x4, 6, 1);

/* operational_notification
 * Access: RO
 */
MLXSW_ITEM8(reg, pmaos, operational_notification, 0x5, 0, 4);

/* error_type
 * Access: RO
 */
MLXSW_ITEM8(reg, pmaos, error_type, 0x6, 0, 4);

/* e
 * Access: RW
 */
MLXSW_ITEM8(reg, pmaos, e, 0x7, 0, 2);

/* rxlte
 * -----
 *
 */
/* virtual_router
 * Access: INDEX
 */
MLXSW_ITEM16(reg, rxlte, virtual_router, 0x2, 0, 16);

/* protocol
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rxlte, protocol, 0x7, 0, 4);

/* lpm_xlt_en
 * Access: RW
 */
MLXSW_ITEM8(reg, rxlte, lpm_xlt_en, 0xb, 0, 4);

/* sbhbr_v2
 * --------
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbhbr_v2, local_port, 0x1, 0, 8);

/* pg_buff
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbhbr_v2, pg_buff, 0x2, 0, 6);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbhbr_v2, lp_msb, 0x3, 4, 2);

/* dir
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbhbr_v2, dir, 0x3, 0, 2);

/* en
 * Access: RW
 */
MLXSW_ITEM8(reg, sbhbr_v2, en, 0x7, 0, 1);

/* mode
 * Access: RW
 */
MLXSW_ITEM8(reg, sbhbr_v2, mode, 0x8, 4, 3);

/* hist_type
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sbhbr_v2, hist_type, 0xa, 0, 16);

/* hist_min_value
 * Access: RW
 */
MLXSW_ITEM32(reg, sbhbr_v2, hist_min_value, 0x10, 0, 32);

/* hist_max_value
 * Access: RW
 */
MLXSW_ITEM32(reg, sbhbr_v2, hist_max_value, 0x14, 0, 32);

/* sample_time
 * Access: RW
 */
MLXSW_ITEM8(reg, sbhbr_v2, sample_time, 0x1b, 0, 6);

/* tnqcr
 * -----
 *
 */
/* enc_set_dscp
 * Access: RW
 */
MLXSW_ITEM8(reg, tnqcr, enc_set_dscp, 0x4, 4, 1);

/* enc_set_sp
 * Access: RW
 */
MLXSW_ITEM8(reg, tnqcr, enc_set_sp, 0x4, 0, 1);

/* enc_dscp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, tnqcr, enc_dscp_rw, 0x7, 2, 2);

/* enc_pcp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, tnqcr, enc_pcp_rw, 0x7, 0, 2);

/* dec_set_dscp
 * Access: RW
 */
MLXSW_ITEM8(reg, tnqcr, dec_set_dscp, 0x8, 4, 1);

/* dec_set_sp
 * Access: RW
 */
MLXSW_ITEM8(reg, tnqcr, dec_set_sp, 0x8, 0, 1);

/* dec_set_pcp
 * Access: RW
 */
MLXSW_ITEM8(reg, tnqcr, dec_set_pcp, 0x9, 4, 1);

/* dec_dscp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, tnqcr, dec_dscp_rw, 0xb, 2, 2);

/* dec_pcp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, tnqcr, dec_pcp_rw, 0xb, 0, 2);

/* sbhrr_v2
 * --------
 *
 */
/* clr
 * Access: OP
 */
MLXSW_ITEM8(reg, sbhrr_v2, clr, 0x0, 7, 1);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbhrr_v2, local_port, 0x1, 0, 8);

/* pg_buff
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbhrr_v2, pg_buff, 0x2, 0, 6);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbhrr_v2, lp_msb, 0x3, 4, 2);

/* dir
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbhrr_v2, dir, 0x3, 0, 2);

/* hist_type
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sbhrr_v2, hist_type, 0xa, 0, 16);

/* min_sampled_high
 * Access: RO
 */
MLXSW_ITEM32(reg, sbhrr_v2, min_sampled_high, 0x10, 0, 32);

/* min_sampled_low
 * Access: RO
 */
MLXSW_ITEM32(reg, sbhrr_v2, min_sampled_low, 0x14, 0, 32);

/* max_sampled_high
 * Access: RO
 */
MLXSW_ITEM32(reg, sbhrr_v2, max_sampled_high, 0x18, 0, 32);

/* max_sampled_low
 * Access: RO
 */
MLXSW_ITEM32(reg, sbhrr_v2, max_sampled_low, 0x1c, 0, 32);

/* hi
 * Access: 
 */
MLXSW_ITEM32_INDEXED(reg, sbhrr_v2, hi, MLXSW_SBHRR_V2_BIN_BASE_LEN, 0, 32, MLXSW_SBHRR_V2_BIN_REC_LEN, 0, false);

/* lo
 * Access: 
 */
MLXSW_ITEM32_INDEXED(reg, sbhrr_v2, lo, MLXSW_SBHRR_V2_BIN_BASE_LEN, 0, 32, MLXSW_SBHRR_V2_BIN_REC_LEN, 4, false);

/* pbsr
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pbsr, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pbsr, lp_msb, 0x2, 4, 2);

/* buffer_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pbsr, buffer_type, 0x3, 0, 2);

/* clear_wm_buff_mask
 * Access: OP
 */
MLXSW_ITEM16(reg, pbsr, clear_wm_buff_mask, 0x6, 0, 10);

/* clear_wm
 * Access: OP
 */
MLXSW_ITEM8(reg, pbsr, clear_wm, 0x8, 7, 1);

/* used_shared_headroom_buffer
 * Access: RO
 */
MLXSW_ITEM16(reg, pbsr, used_shared_headroom_buffer, 0xa, 0, 16);

/* stat_buffer_watermark
 * Access: RO
 */
MLXSW_ITEM16_INDEXED(reg, pbsr, stat_buffer_watermark, MLXSW_PBSR_STAT_BUFFER_BASE_LEN + 2, 0, 16, MLXSW_PBSR_STAT_BUFFER_REC_LEN, 0, false);

/* stat_buffer_used_buffer
 * Access: RO
 */
MLXSW_ITEM16_INDEXED(reg, pbsr, stat_buffer_used_buffer, MLXSW_PBSR_STAT_BUFFER_BASE_LEN + 2, 0, 16, MLXSW_PBSR_STAT_BUFFER_REC_LEN, 4, false);

/* stat_shared_headroom_pool_watermark
 * Access: RO
 */
MLXSW_ITEM16(reg, pbsr, stat_shared_headroom_pool_watermark, 0x5e, 0, 16);

/* stat_shared_headroom_pool_used_buffer
 * Access: RO
 */
MLXSW_ITEM16(reg, pbsr, stat_shared_headroom_pool_used_buffer, 0x62, 0, 16);

/* rxltm
 * -----
 *
 */
/* m_sel_update
 * Access: OP
 */
MLXSW_ITEM8(reg, rxltm, m_sel_update, 0x0, 7, 1);

/* go_m_sel
 * Access: RW
 */
MLXSW_ITEM8(reg, rxltm, go_m_sel, 0x3, 1, 1);

/* m_sel
 * Access: RW
 */
MLXSW_ITEM8(reg, rxltm, m_sel, 0x3, 0, 1);

/* m1_val_v6
 * Access: RW
 */
MLXSW_ITEM8(reg, rxltm, m1_val_v6, 0x10, 0, 8);

/* m0_val_v6
 * Access: RW
 */
MLXSW_ITEM8(reg, rxltm, m0_val_v6, 0x11, 0, 8);

/* m1_val_v4
 * Access: RW
 */
MLXSW_ITEM8(reg, rxltm, m1_val_v4, 0x12, 0, 6);

/* m0_val_v4
 * Access: RW
 */
MLXSW_ITEM8(reg, rxltm, m0_val_v4, 0x13, 0, 6);

/* momte
 * -----
 *
 */
/* swid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, momte, swid, 0x0, 0, 8);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, momte, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, momte, lp_msb, 0x2, 4, 2);

/* mngr_type
 * Access: OP
 */
MLXSW_ITEM8(reg, momte, mngr_type, 0x2, 0, 4);

/* type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, momte, type, 0x7, 0, 8);

/* tclass_en_high
 * Access: RW
 */
MLXSW_ITEM32(reg, momte, tclass_en_high, 0x8, 0, 32);

/* tclass_en_low
 * Access: RW
 */
MLXSW_ITEM32(reg, momte, tclass_en_low, 0xc, 0, 32);

/* rmpe
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rmpe, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rmpe, lp_msb, 0x2, 4, 2);

/* rmpe_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, rmpe, rmpe_index, 0x6, 0, 16);

/* erif
 * Access: RW
 */
MLXSW_ITEM16(reg, rmpe, erif, 0xa, 0, 16);

/* svfa
 * ----
 *
 */
/* swid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, svfa, swid, 0x0, 0, 8);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, svfa, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, svfa, lp_msb, 0x2, 4, 2);

/* mapping_table
 * Access: INDEX
 */
MLXSW_ITEM8(reg, svfa, mapping_table, 0x2, 0, 3);

/* tport
 * Access: RW
 */
MLXSW_ITEM8(reg, svfa, tport, 0x3, 7, 1);

/* v
 * Access: RW
 */
MLXSW_ITEM8(reg, svfa, v, 0x3, 0, 1);

/* fid
 * Access: RW
 */
MLXSW_ITEM16(reg, svfa, fid, 0x4, 0, 16);

/* vid
 * Access: INDEX
 */
MLXSW_ITEM16(reg, svfa, vid, 0x6, 0, 12);

/* counter_set_type
 * Access: RW
 */
MLXSW_ITEM8(reg, svfa, counter_set_type, 0x8, 0, 8);

/* counter_index
 * Access: RW
 */
MLXSW_ITEM32(reg, svfa, counter_index, 0x8, 0, 24);

/* trap_action
 * Access: RW
 */
MLXSW_ITEM8(reg, svfa, trap_action, 0xc, 4, 4);

/* vni
 * Access: INDEX
 */
MLXSW_ITEM32(reg, svfa, vni, 0x10, 0, 24);

/* irif_v
 * Access: RW
 */
MLXSW_ITEM8(reg, svfa, irif_v, 0x14, 0, 1);

/* irif
 * Access: RW
 */
MLXSW_ITEM16(reg, svfa, irif, 0x16, 0, 16);

/* mafri
 * -----
 *
 */
/* num_rec
 * Access: OP
 */
MLXSW_ITEM8(reg, mafri, num_rec, 0x3, 0, 8);

/* counter_index_base
 * Access: OP
 */
MLXSW_ITEM32(reg, mafri, counter_index_base, 0x4, 0, 24);

/* bytes_inc
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mafri, bytes_inc, MLXSW_MAFRI_RECORD_BASE_LEN, 0, 32, MLXSW_MAFRI_RECORD_REC_LEN, 0, false);

/* packets_inc
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mafri, packets_inc, MLXSW_MAFRI_RECORD_BASE_LEN, 0, 32, MLXSW_MAFRI_RECORD_REC_LEN, 4, false);

/* sbsrd
 * -----
 *
 */
/* clr
 * Access: OP
 */
MLXSW_ITEM8(reg, sbsrd, clr, 0x0, 7, 1);

/* snap
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbsrd, snap, 0x0, 6, 1);

/* desc
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbsrd, desc, 0x0, 5, 1);

/* type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbsrd, type, 0x3, 0, 8);

/* num_rec
 * Access: OP
 */
MLXSW_ITEM8(reg, sbsrd, num_rec, 0x7, 0, 8);

/* fisrt_entry_index
 * Access: RO
 */
MLXSW_ITEM16(reg, sbsrd, fisrt_entry_index, 0x8, 0, 16);

/* first_lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbsrd, first_lp_msb, 0xa, 0, 2);

/* first_local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbsrd, first_local_port, 0xb, 0, 8);

/* buff_occupancy
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sbsrd, buff_occupancy, MLXSW_SBSRD_SHARED_BUFFER_STATUS_BASE_LEN, 0, 24, MLXSW_SBSRD_SHARED_BUFFER_STATUS_REC_LEN, 0, false);

/* max_buff_occupancy
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sbsrd, max_buff_occupancy, MLXSW_SBSRD_SHARED_BUFFER_STATUS_BASE_LEN, 0, 24, MLXSW_SBSRD_SHARED_BUFFER_STATUS_REC_LEN, 4, false);

/* fphtt
 * -----
 *
 */
/* entry_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fphtt, entry_index, 0x3, 0, 8);

/* tran_en
 * Access: RW
 */
MLXSW_ITEM8(reg, fphtt, tran_en, 0x7, 0, 1);

/* mcc
 * ---
 *
 */
/* time_elapsed_since_last_cmd
 * Access: RO
 */
MLXSW_ITEM16(reg, mcc, time_elapsed_since_last_cmd, 0x0, 0, 12);

/* activation_delay_sec
 * Access: RW
 */
MLXSW_ITEM8(reg, mcc, activation_delay_sec, 0x2, 0, 8);

/* instruction
 * Access: RW
 */
MLXSW_ITEM8(reg, mcc, instruction, 0x3, 0, 8);

/* component_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, mcc, component_index, 0x6, 0, 16);

/* auto_update
 * Access: WO
 */
MLXSW_ITEM8(reg, mcc, auto_update, 0x8, 7, 1);

/* update_handle
 * Access: RW
 */
MLXSW_ITEM32(reg, mcc, update_handle, 0x8, 0, 24);

/* handle_owner_type
 * Access: RO
 */
MLXSW_ITEM8(reg, mcc, handle_owner_type, 0xc, 4, 4);

/* handle_owner_host_id
 * Access: RO
 */
MLXSW_ITEM8(reg, mcc, handle_owner_host_id, 0xc, 0, 4);

/* control_progress
 * Access: RO
 */
MLXSW_ITEM8(reg, mcc, control_progress, 0xd, 0, 7);

/* error_code
 * Access: RO
 */
MLXSW_ITEM8(reg, mcc, error_code, 0xe, 0, 8);

/* control_state
 * Access: RO
 */
MLXSW_ITEM8(reg, mcc, control_state, 0xf, 0, 4);

/* component_size
 * Access: WO
 */
MLXSW_ITEM32(reg, mcc, component_size, 0x10, 0, 32);

/* device_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, mcc, device_index, 0x14, 0, 12);

/* device_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mcc, device_type, 0x17, 0, 8);

/* rejected_device_index
 * Access: RO
 */
MLXSW_ITEM16(reg, mcc, rejected_device_index, 0x18, 0, 12);

/* device_index_size
 * Access: RW
 */
MLXSW_ITEM16(reg, mcc, device_index_size, 0x1a, 0, 12);

/* sfdb
 * ----
 *
 */
/* policy
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sfdb, policy, 0x9, 0, 2);

/* update_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sfdb, update_type, 0xb, 0, 4);

/* gfid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sfdb, gfid, 0xc, 7, 1);

/* entry_fid
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sfdb, entry_fid, 0xe, 0, 16);

/* parameter
 * Access: INDEX
 */
MLXSW_ITEM32(reg, sfdb, parameter, 0x20, 0, 32);

/* parameter1
 * Access: INDEX
 */
MLXSW_ITEM32(reg, sfdb, parameter1, 0x24, 0, 32);

/* new_parameter
 * Access: WO
 */
MLXSW_ITEM32(reg, sfdb, new_parameter, 0x40, 0, 32);

/* new_parameter1
 * Access: WO
 */
MLXSW_ITEM32(reg, sfdb, new_parameter1, 0x44, 0, 32);

/* pmtps
 * -----
 *
 */
/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmtps, slot_index, 0x0, 0, 4);

/* module
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmtps, module, 0x1, 0, 8);

/* module_type_admin
 * Access: RW
 */
MLXSW_ITEM16(reg, pmtps, module_type_admin, 0xa, 0, 16);

/* module_type_connected
 * Access: RO
 */
MLXSW_ITEM16(reg, pmtps, module_type_connected, 0xe, 0, 16);

/* eth_module_c2m
 * Access: RO
 */
MLXSW_ITEM32(reg, pmtps, eth_module_c2m, 0x10, 0, 32);

/* ib_width_module_c2m
 * Access: RO
 */
MLXSW_ITEM16(reg, pmtps, ib_width_module_c2m, 0x14, 0, 16);

/* ib_speed_module_c2m
 * Access: RO
 */
MLXSW_ITEM16(reg, pmtps, ib_speed_module_c2m, 0x16, 0, 16);

/* rxltcc
 * ------
 *
 */
/* clear
 * Access: OP
 */
MLXSW_ITEM8(reg, rxltcc, clear, 0x0, 7, 1);

/* hit_ipv4_m_high
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, hit_ipv4_m_high, 0x10, 0, 32);

/* hit_ipv4_m_low
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, hit_ipv4_m_low, 0x14, 0, 32);

/* hit_ipv4_ml_high
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, hit_ipv4_ml_high, 0x18, 0, 32);

/* hit_ipv4_ml_low
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, hit_ipv4_ml_low, 0x1c, 0, 32);

/* miss_ipv4_m_high
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, miss_ipv4_m_high, 0x20, 0, 32);

/* miss_ipv4_m_low
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, miss_ipv4_m_low, 0x24, 0, 32);

/* miss_ipv4_ml_high
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, miss_ipv4_ml_high, 0x28, 0, 32);

/* miss_ipv4_ml_low
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, miss_ipv4_ml_low, 0x2c, 0, 32);

/* learned_ipv4_high
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, learned_ipv4_high, 0x30, 0, 32);

/* learned_ipv4_low
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, learned_ipv4_low, 0x34, 0, 32);

/* hit_ipv6_m_high
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, hit_ipv6_m_high, 0x40, 0, 32);

/* hit_ipv6_m_low
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, hit_ipv6_m_low, 0x44, 0, 32);

/* hit_ipv6_ml_high
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, hit_ipv6_ml_high, 0x48, 0, 32);

/* hit_ipv6_ml_low
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, hit_ipv6_ml_low, 0x4c, 0, 32);

/* miss_ipv6_m_high
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, miss_ipv6_m_high, 0x50, 0, 32);

/* miss_ipv6_m_low
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, miss_ipv6_m_low, 0x54, 0, 32);

/* miss_ipv6_ml_high
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, miss_ipv6_ml_high, 0x58, 0, 32);

/* miss_ipv6_ml_low
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, miss_ipv6_ml_low, 0x5c, 0, 32);

/* learned_ipv6_high
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, learned_ipv6_high, 0x60, 0, 32);

/* learned_ipv6_low
 * Access: RO
 */
MLXSW_ITEM32(reg, rxltcc, learned_ipv6_low, 0x64, 0, 32);

/* sbhpc
 * -----
 *
 */
/* max_buff
 * Access: RW
 */
MLXSW_ITEM32(reg, sbhpc, max_buff, 0x10, 0, 24);

/* buff_occupancy
 * Access: RO
 */
MLXSW_ITEM32(reg, sbhpc, buff_occupancy, 0x20, 0, 24);

/* mbct
 * ----
 *
 */
/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mbct, slot_index, 0x3, 0, 4);

/* ini_status
 * Access: RO
 */
MLXSW_ITEM8(reg, mbct, ini_status, 0x4, 5, 3);

/* data_size
 * Access: WO
 */
MLXSW_ITEM16(reg, mbct, data_size, 0x6, 0, 11);

/* op
 * Access: WO
 */
MLXSW_ITEM8(reg, mbct, op, 0x8, 4, 4);

/* last
 * Access: WO
 */
MLXSW_ITEM8(reg, mbct, last, 0x8, 2, 1);

/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, mbct, status, 0xc, 0, 5);

/* fsm_state
 * Access: RO
 */
MLXSW_ITEM8(reg, mbct, fsm_state, 0xd, 0, 4);

/* data
 * Access: WO
 */
MLXSW_ITEM32_INDEXED(reg, mbct, data, 0x20, 0, 32, 4, 0, false);

/* mcda
 * ----
 *
 */
/* update_handle
 * Access: RW
 */
MLXSW_ITEM32(reg, mcda, update_handle, 0x0, 0, 24);

/* offset
 * Access: RW
 */
MLXSW_ITEM32(reg, mcda, offset, 0x4, 0, 32);

/* size
 * Access: RW
 */
MLXSW_ITEM16(reg, mcda, size, 0xa, 0, 16);

/* data
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mcda, data, 0x10, 0, 32, 4, 0, false);

