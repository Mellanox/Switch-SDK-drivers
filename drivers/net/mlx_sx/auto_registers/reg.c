/*
* Copyright (c) 2008-2020,  Mellanox Technologies. All rights reserved.
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
/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mtmp, slot_index, 0x1, 0, 4);

/* sensor_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, mtmp, sensor_index, 0x2, 0, 12);

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

/* max_temperature
 * Access: RO
 */
MLXSW_ITEM16(reg, mtmp, max_temperature, 0xa, 0, 16);

/* tee
 * Access: RW
 */
MLXSW_ITEM8(reg, mtmp, tee, 0xc, 6, 2);

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

/* chltm
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, chltm, local_port, 0x1, 0, 8);

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

/* tnqdr
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tnqdr, local_port, 0x1, 0, 8);

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

/* tnpc
 * ----
 *
 */
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

/* ifbf
 * ----
 *
 */
/* pp
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ifbf, pp, 0x0, 0, 1);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ifbf, local_port, 0x1, 0, 8);

/* type
 * Access: RW
 */
MLXSW_ITEM8(reg, ifbf, type, 0x3, 0, 4);

/* seed
 * Access: RW
 */
MLXSW_ITEM32(reg, ifbf, seed, 0x8, 0, 32);

/* outer_header_enables
 * Access: RW
 */
MLXSW_ITEM16(reg, ifbf, outer_header_enables, 0x12, 0, 16);

/* outer_header_fields_enable
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, ifbf, outer_header_fields_enable, 0x14, 0, 32, 4, 0, false);

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

/* phys_layer_stat_cntrs_post_fec_ber_magnitude
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_post_fec_ber_magnitude, 0x72, 0, 8);

/* phys_layer_stat_cntrs_post_fec_ber_coef
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, phys_layer_stat_cntrs_post_fec_ber_coef, 0x73, 0, 4);

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
/* bulk_entry
 * Access: OP
 */
MLXSW_ITEM8(reg, xmdr, bulk_entry, 0x6, 0, 1);

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
/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mdfcr, slot_index, 0x1, 0, 4);

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

/* smpe
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, smpe, local_port, 0x1, 0, 8);

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

/* reiv
 * ----
 *
 */
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

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppad, local_port, 0x1, 0, 8);

/* mac
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, ppad, mac, 0x2, 6);

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
MLXSW_ITEM8(reg, mocs, status, 0x7, 0, 1);

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

/* mcqi_activation_method_pending_server_ac_power_cycle
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_activation_method_pending_server_ac_power_cycle, 0x18, 7, 1);

/* mcqi_activation_method_pending_server_dc_power_cycle
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_activation_method_pending_server_dc_power_cycle, 0x18, 6, 1);

/* mcqi_activation_method_pending_server_reboot
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_activation_method_pending_server_reboot, 0x18, 5, 1);

/* mcqi_activation_method_pending_fw_reset
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_activation_method_pending_fw_reset, 0x18, 4, 1);

/* mcqi_activation_method_auto_activate
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_activation_method_auto_activate, 0x18, 3, 1);

/* mcqi_activation_method_all_hosts_sync
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_activation_method_all_hosts_sync, 0x18, 2, 1);

/* mcqi_activation_method_device_hw_reset
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, mcqi_activation_method_device_hw_reset, 0x18, 1, 1);

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

/* pevpb
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pevpb, local_port, 0x1, 0, 8);

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

/* buffer_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pbsr, buffer_type, 0x3, 0, 2);

/* clear_wm
 * Access: OP
 */
MLXSW_ITEM8(reg, pbsr, clear_wm, 0x8, 7, 1);

/* used_shared_headroom_buffer
 * Access: RO
 */
MLXSW_ITEM16(reg, pbsr, used_shared_headroom_buffer, 0xa, 0, 16);

/* watermark
 * Access: RO
 */
MLXSW_ITEM16_INDEXED(reg, pbsr, watermark, MLXSW_PBSR_STAT_BUFFER_BASE_LEN + 2, 0, 16, MLXSW_PBSR_STAT_BUFFER_REC_LEN, 0, false);

/* used_buffer
 * Access: RO
 */
MLXSW_ITEM16_INDEXED(reg, pbsr, used_buffer, MLXSW_PBSR_STAT_BUFFER_BASE_LEN + 2, 0, 16, MLXSW_PBSR_STAT_BUFFER_REC_LEN, 4, false);

/* hi
 * Access: 
 */
MLXSW_ITEM32(reg, pbsr, hi, 0x5c, 0, 32);

/* lo
 * Access: 
 */
MLXSW_ITEM32(reg, pbsr, lo, 0x60, 0, 32);

/* rxltm
 * -----
 *
 */
/* m_sel_update
 * Access: OP
 */
MLXSW_ITEM8(reg, rxltm, m_sel_update, 0x0, 7, 1);

/* m_select
 * Access: RW
 */
MLXSW_ITEM8(reg, rxltm, m_select, 0x3, 0, 8);

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

/* mapping_table
 * Access: INDEX
 */
MLXSW_ITEM8(reg, svfa, mapping_table, 0x2, 0, 3);

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

/* mcc
 * ---
 *
 */
/* time_elapsed_since_last_cmd
 * Access: RO
 */
MLXSW_ITEM16(reg, mcc, time_elapsed_since_last_cmd, 0x0, 0, 12);

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

