/*
 * Copyright © 2018-2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
/* fsfh
 * ----
 *
 */
/* failure_reason
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fsfh, failure_reason, 0x3, 0, 3);

/* action_info
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, fsfh, action_info, 0x4, 0, 32, 4, 0, false);

/* fmtc
 * ----
 *
 */
/* emt_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fmtc, emt_index, 0x3, 0, 8);

/* length_cb
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, length_cb, 0x6, 0, 8);

/* length_cb_mask
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, length_cb_mask, 0x7, 0, 8);

/* length_math_bitmap
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, length_math_bitmap, 0x8, 4, 1);

/* length_math_add_pos
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, length_math_add_pos, 0x8, 0, 1);

/* length_math_shift_left
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, length_math_shift_left, 0x9, 4, 1);

/* length_math_shift
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, length_math_shift, 0x9, 0, 3);

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

/* update_ipv4_ihl
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, update_ipv4_ihl, 0x13, 3, 1);

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

/* update_ipv4_cs
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, update_ipv4_cs, 0x17, 5, 1);

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

/* enc_l2_uirif
 * Access: RW
 */
MLXSW_ITEM16(reg, fmtc, enc_l2_uirif, 0x32, 0, 16);

/* enc_ipv4_id
 * Access: RW
 */
MLXSW_ITEM16(reg, fmtc, enc_ipv4_id, 0x38, 0, 16);

/* enc_ipv4_flag
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, enc_ipv4_flag, 0x3a, 5, 3);

/* enc_ipv4_frag_offset
 * Access: RW
 */
MLXSW_ITEM16(reg, fmtc, enc_ipv4_frag_offset, 0x3a, 0, 13);

/* enc_next_header
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, enc_next_header, 0x3d, 0, 8);

/* enc_flc
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, enc_flc, 0x40, 1, 1);

/* enc_flh
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, enc_flh, 0x40, 0, 1);

/* enc_fl_prefix
 * Access: RW
 */
MLXSW_ITEM32(reg, fmtc, enc_fl_prefix, 0x40, 8, 12);

/* enc_fl_suffix
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, enc_fl_suffix, 0x43, 0, 8);

/* s0_sel_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, s0_sel_mode, 0x45, 0, 3);

/* s0_offset
 * Access: RW
 */
MLXSW_ITEM16(reg, fmtc, s0_offset, 0x46, 0, 9);

/* s1_sel_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtc, s1_sel_mode, 0x49, 0, 3);

/* s1_offset
 * Access: RW
 */
MLXSW_ITEM16(reg, fmtc, s1_offset, 0x4a, 0, 9);

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
 * Access: OP
 */
MLXSW_ITEM8(reg, iicr, clear_mc_rtr_tcam_value, 0xf, 4, 2);

/* clear_mc_rtr_tcam_mask
 * Access: OP
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

/* pmdr
 * ----
 *
 */
/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, status, 0x0, 4, 4);

/* version
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, version, 0x0, 0, 4);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmdr, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmdr, pnat, 0x2, 6, 2);

/* gb_valid
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, gb_valid, 0x2, 5, 1);

/* mcm_tile_valid
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, mcm_tile_valid, 0x2, 4, 1);

/* scc_valid
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, scc_valid, 0x2, 3, 1);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmdr, lp_msb, 0x3, 0, 2);

/* pport
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, pport, 0x4, 0, 8);

/* module
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, module, 0x5, 0, 8);

/* cluster
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, cluster, 0x6, 0, 7);

/* clp_4x
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, clp_4x, 0x7, 4, 2);

/* clp_1x
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, clp_1x, 0x7, 0, 2);

/* gb_dp_num
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, gb_dp_num, 0x8, 3, 5);

/* split
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, split, 0x8, 0, 3);

/* swid
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, swid, 0x9, 0, 8);

/* module_lane_mask
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, module_lane_mask, 0xa, 0, 8);

/* ib_port
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, ib_port, 0xb, 0, 8);

/* label_port_query
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, label_port_query, 0xc, 0, 7);

/* local_port_query
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, local_port_query, 0xd, 0, 8);

/* usr_sd_4x_tx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, usr_sd_4x_tx, 0xe, 6, 2);

/* usr_sd_4x_rx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, usr_sd_4x_rx, 0xe, 4, 2);

/* lp_query_msb
 * Access: RW
 */
MLXSW_ITEM8(reg, pmdr, lp_query_msb, 0xf, 0, 2);

/* slot_index
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, slot_index, 0x10, 4, 4);

/* tile_cluster
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, tile_cluster, 0x10, 0, 4);

/* mcm_tile_num
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, mcm_tile_num, 0x11, 0, 8);

/* tile_pport
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, tile_pport, 0x12, 0, 5);

/* gearbox_die_num
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, gearbox_die_num, 0x13, 0, 7);

/* vl_num
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl_num, 0x14, 3, 5);

/* lane7_physical_rx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, lane7_physical_rx, 0x15, 5, 3);

/* lane6_physical_rx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, lane6_physical_rx, 0x15, 2, 3);

/* lane5_physical_rx
 * Access: RO
 */
MLXSW_ITEM32(reg, pmdr, lane5_physical_rx, 0x14, 15, 3);

/* lane4_physical_rx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, lane4_physical_rx, 0x16, 4, 3);

/* lane3_physical_rx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, lane3_physical_rx, 0x16, 1, 3);

/* lane2_physical_rx
 * Access: RO
 */
MLXSW_ITEM16(reg, pmdr, lane2_physical_rx, 0x16, 6, 3);

/* lane1_physical_rx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, lane1_physical_rx, 0x17, 3, 3);

/* lane0_physical_rx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, lane0_physical_rx, 0x17, 0, 3);

/* pll_index
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, pll_index, 0x18, 0, 8);

/* lane7_physical_tx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, lane7_physical_tx, 0x19, 5, 3);

/* lane6_physical_tx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, lane6_physical_tx, 0x19, 2, 3);

/* lane5_physical_tx
 * Access: RO
 */
MLXSW_ITEM32(reg, pmdr, lane5_physical_tx, 0x18, 15, 3);

/* lane4_physical_tx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, lane4_physical_tx, 0x1a, 4, 3);

/* lane3_physical_tx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, lane3_physical_tx, 0x1a, 1, 3);

/* lane2_physical_tx
 * Access: RO
 */
MLXSW_ITEM16(reg, pmdr, lane2_physical_tx, 0x1a, 6, 3);

/* lane1_physical_tx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, lane1_physical_tx, 0x1b, 3, 3);

/* lane0_physical_tx
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, lane0_physical_tx, 0x1b, 0, 3);

/* vl7_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl7_lane_map, 0x1c, 4, 4);

/* vl6_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl6_lane_map, 0x1c, 0, 4);

/* vl5_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl5_lane_map, 0x1d, 4, 4);

/* vl4_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl4_lane_map, 0x1d, 0, 4);

/* vl3_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl3_lane_map, 0x1e, 4, 4);

/* vl2_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl2_lane_map, 0x1e, 0, 4);

/* vl1_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl1_lane_map, 0x1f, 4, 4);

/* vl0_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl0_lane_map, 0x1f, 0, 4);

/* vl15_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl15_lane_map, 0x20, 4, 4);

/* vl14_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl14_lane_map, 0x20, 0, 4);

/* vl13_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl13_lane_map, 0x21, 4, 4);

/* vl12_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl12_lane_map, 0x21, 0, 4);

/* vl11_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl11_lane_map, 0x22, 4, 4);

/* vl10_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl10_lane_map, 0x22, 0, 4);

/* vl9_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl9_lane_map, 0x23, 4, 4);

/* vl8_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl8_lane_map, 0x23, 0, 4);

/* vl23_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl23_lane_map, 0x24, 4, 4);

/* vl22_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl22_lane_map, 0x24, 0, 4);

/* vl21_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl21_lane_map, 0x25, 4, 4);

/* vl20_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl20_lane_map, 0x25, 0, 4);

/* vl19_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl19_lane_map, 0x26, 4, 4);

/* vl18_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl18_lane_map, 0x26, 0, 4);

/* vl17_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl17_lane_map, 0x27, 4, 4);

/* vl16_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl16_lane_map, 0x27, 0, 4);

/* vl31_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl31_lane_map, 0x28, 4, 4);

/* vl30_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl30_lane_map, 0x28, 0, 4);

/* vl29_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl29_lane_map, 0x29, 4, 4);

/* vl28_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl28_lane_map, 0x29, 0, 4);

/* vl27_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl27_lane_map, 0x2a, 4, 4);

/* vl26_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl26_lane_map, 0x2a, 0, 4);

/* vl25_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl25_lane_map, 0x2b, 4, 4);

/* vl24_lane_map
 * Access: RO
 */
MLXSW_ITEM8(reg, pmdr, vl24_lane_map, 0x2b, 0, 4);

/* scc_hs_lanes
 * Access: RO
 */
MLXSW_ITEM16(reg, pmdr, scc_hs_lanes, 0x2e, 0, 16);

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

/* mtecr
 * -----
 *
 */
/* last_sensor
 * Access: RO
 */
MLXSW_ITEM16(reg, mtecr, last_sensor, 0x0, 0, 12);

/* sensor_count
 * Access: RO
 */
MLXSW_ITEM16(reg, mtecr, sensor_count, 0x2, 0, 12);

/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mtecr, slot_index, 0x4, 4, 4);

/* internal_sensor_count
 * Access: RO
 */
MLXSW_ITEM8(reg, mtecr, internal_sensor_count, 0x7, 0, 7);

/* sensor_map
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mtecr, sensor_map, 0x8, 0, 32, 4, 0, false);

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

/* ddd_lag_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, igcr, ddd_lag_mode, 0xe, 0, 4);

/* pisbo
 * Access: RW
 */
MLXSW_ITEM8(reg, igcr, pisbo, 0xf, 0, 1);

/* pemrbt
 * ------
 *
 */
/* op
 * Access: RW
 */
MLXSW_ITEM8(reg, pemrbt, op, 0x1, 4, 3);

/* protocol
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pemrbt, protocol, 0x3, 0, 1);

/* group_id
 * Access: RW
 */
MLXSW_ITEM16(reg, pemrbt, group_id, 0x12, 0, 16);

/* sfdf
 * ----
 *
 */
/* swid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sfdf, swid, 0x0, 0, 8);

/* flush_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sfdf, flush_type, 0x4, 4, 4);

/* imdu
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sfdf, imdu, 0x4, 2, 1);

/* iut
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sfdf, iut, 0x4, 1, 1);

/* st
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sfdf, st, 0x4, 0, 1);

/* pb_v
 * Access: RW
 */
MLXSW_ITEM8(reg, sfdf, pb_v, 0x6, 0, 1);

/* pb
 * Access: RW
 */
MLXSW_ITEM8(reg, sfdf, pb, 0x7, 0, 3);

/* parameter_flush_per_fid_fid
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sfdf, parameter_flush_per_fid_fid, 0xe, 0, 16);

/* parameter_flush_per_nve_and_fid_fid
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sfdf, parameter_flush_per_nve_and_fid_fid, 0xe, 0, 16);

/* parameter_flush_per_port_system_port
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sfdf, parameter_flush_per_port_system_port, 0xe, 0, 16);

/* parameter_flush_per_port_and_fid_system_port
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sfdf, parameter_flush_per_port_and_fid_system_port, 0xa, 0, 16);

/* parameter_flush_per_port_and_fid_fid
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sfdf, parameter_flush_per_port_and_fid_fid, 0xe, 0, 16);

/* parameter_flush_per_lag_lag_id
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sfdf, parameter_flush_per_lag_lag_id, 0xe, 0, 10);

/* parameter_flush_per_lag_and_fid_lag_id
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sfdf, parameter_flush_per_lag_and_fid_lag_id, 0xa, 0, 10);

/* parameter_flush_per_lag_and_fid_fid
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sfdf, parameter_flush_per_lag_and_fid_fid, 0xe, 0, 16);

/* parameter_flush_per_tunnel_port_tport_mask
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sfdf, parameter_flush_per_tunnel_port_tport_mask, 0x9, 0, 4);

/* parameter_flush_per_tunnel_port_tport
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sfdf, parameter_flush_per_tunnel_port_tport, 0xb, 0, 4);

/* parameter_flush_per_tunnel_port_fid_tport_mask
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sfdf, parameter_flush_per_tunnel_port_fid_tport_mask, 0x9, 0, 4);

/* parameter_flush_per_tunnel_port_fid_tport
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sfdf, parameter_flush_per_tunnel_port_fid_tport, 0xb, 0, 4);

/* parameter_flush_per_tunnel_port_fid_fid
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sfdf, parameter_flush_per_tunnel_port_fid_fid, 0xe, 0, 16);

/* parameter_flush_mc_dmac_uc_and_fid_fid
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sfdf, parameter_flush_mc_dmac_uc_and_fid_fid, 0xe, 0, 16);

/* qtqcr
 * -----
 *
 */
/* tqos_profile
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qtqcr, tqos_profile, 0x3, 0, 4);

/* enc_set_dscp
 * Access: RW
 */
MLXSW_ITEM8(reg, qtqcr, enc_set_dscp, 0x4, 4, 1);

/* enc_set_sp
 * Access: RW
 */
MLXSW_ITEM8(reg, qtqcr, enc_set_sp, 0x4, 0, 1);

/* enc_dscp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, qtqcr, enc_dscp_rw, 0x7, 2, 2);

/* enc_pcp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, qtqcr, enc_pcp_rw, 0x7, 0, 2);

/* dec_set_dscp
 * Access: RW
 */
MLXSW_ITEM8(reg, qtqcr, dec_set_dscp, 0x8, 4, 1);

/* dec_set_sp
 * Access: RW
 */
MLXSW_ITEM8(reg, qtqcr, dec_set_sp, 0x8, 0, 1);

/* dec_set_pcp
 * Access: RW
 */
MLXSW_ITEM8(reg, qtqcr, dec_set_pcp, 0x9, 4, 1);

/* dec_dscp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, qtqcr, dec_dscp_rw, 0xb, 2, 2);

/* dec_pcp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, qtqcr, dec_pcp_rw, 0xb, 0, 2);

/* rsnh
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rsnh, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rsnh, lp_msb, 0x2, 4, 2);

/* p2d_en
 * Access: RW
 */
MLXSW_ITEM8(reg, rsnh, p2d_en, 0x7, 0, 1);

/* dmac
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, rsnh, dmac, 0xa, 6);

/* qtct
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qtct, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qtct, lp_msb, 0x2, 4, 2);

/* switch_prio
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qtct, switch_prio, 0x3, 0, 4);

/* tclass
 * Access: RW
 */
MLXSW_ITEM8(reg, qtct, tclass, 0x7, 0, 4);

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

/* iim
 * Access: RW
 */
MLXSW_ITEM8(reg, fmte, iim, 0xd, 0, 1);

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

/* sftr_v2
 * -------
 *
 */
/* swid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sftr_v2, swid, 0x0, 0, 8);

/* flood_table
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sftr_v2, flood_table, 0x1, 0, 6);

/* index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sftr_v2, index, 0x2, 0, 16);

/* table_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sftr_v2, table_type, 0x5, 0, 3);

/* range
 * Access: INDEX
 */
MLXSW_ITEM16(reg, sftr_v2, range, 0x6, 0, 16);

/* port
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sftr_v2, port, 0x20, 0, 32, 4, 0, false);

/* mask
 * Access: WO
 */
MLXSW_ITEM32_INDEXED(reg, sftr_v2, mask, 0xa0, 0, 32, 4, 0, false);

/* pgcr
 * ----
 *
 */
/* update_prune
 * Access: OP
 */
MLXSW_ITEM8(reg, pgcr, update_prune, 0x0, 7, 1);

/* pbs_table_size
 * Access: RW
 */
MLXSW_ITEM16(reg, pgcr, pbs_table_size, 0x2, 0, 16);

/* max_eacl
 * Access: RO
 */
MLXSW_ITEM16(reg, pgcr, max_eacl, 0x8, 0, 16);

/* max_iacl
 * Access: RO
 */
MLXSW_ITEM16(reg, pgcr, max_iacl, 0xa, 0, 16);

/* atcam_ignore_prune_vector
 * Access: RW
 */
MLXSW_ITEM16(reg, pgcr, atcam_ignore_prune_vector, 0x16, 0, 16);

/* default_action_pointer_base
 * Access: RW
 */
MLXSW_ITEM32(reg, pgcr, default_action_pointer_base, 0x1c, 0, 24);

/* mvcap
 * -----
 *
 */
/* sensor_map
 * Access: RO
 */
MLXSW_ITEM64(reg, mvcap, sensor_map, 0x0, 0, 64);

/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mvcap, slot_index, 0xb, 0, 4);

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

/* raleu
 * -----
 *
 */
/* protocol
 * Access: INDEX
 */
MLXSW_ITEM8(reg, raleu, protocol, 0x0, 0, 4);

/* type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, raleu, type, 0x1, 4, 2);

/* virtual_router
 * Access: INDEX
 */
MLXSW_ITEM16(reg, raleu, virtual_router, 0x2, 0, 16);

/* adjacency_index
 * Access: INDEX
 */
MLXSW_ITEM32(reg, raleu, adjacency_index, 0x10, 0, 24);

/* ecmp_size
 * Access: INDEX
 */
MLXSW_ITEM16(reg, raleu, ecmp_size, 0x16, 0, 13);

/* new_adjacency_index
 * Access: WO
 */
MLXSW_ITEM32(reg, raleu, new_adjacency_index, 0x20, 0, 24);

/* new_ecmp_size
 * Access: WO
 */
MLXSW_ITEM16(reg, raleu, new_ecmp_size, 0x26, 0, 13);

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

/* qtqdr
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qtqdr, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qtqdr, lp_msb, 0x2, 4, 2);

/* tqos_profile
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qtqdr, tqos_profile, 0x3, 0, 4);

/* color
 * Access: RW
 */
MLXSW_ITEM8(reg, qtqdr, color, 0x4, 0, 2);

/* switch_prio
 * Access: RW
 */
MLXSW_ITEM8(reg, qtqdr, switch_prio, 0x5, 0, 4);

/* exp
 * Access: RW
 */
MLXSW_ITEM8(reg, qtqdr, exp, 0x6, 0, 3);

/* dscp
 * Access: RW
 */
MLXSW_ITEM8(reg, qtqdr, dscp, 0x7, 0, 6);

/* rigr_v2
 * -------
 *
 */
/* list_type
 * Access: RW
 */
MLXSW_ITEM8(reg, rigr_v2, list_type, 0x1, 4, 4);

/* rigr_index
 * Access: INDEX
 */
MLXSW_ITEM32(reg, rigr_v2, rigr_index, 0x4, 0, 24);

/* vnext
 * Access: RW
 */
MLXSW_ITEM8(reg, rigr_v2, vnext, 0x8, 7, 1);

/* next_rigr_index
 * Access: RW
 */
MLXSW_ITEM32(reg, rigr_v2, next_rigr_index, 0x8, 0, 24);

/* erif_list_rigr_erif_list_vrmid
 * Access: RW
 */
MLXSW_ITEM8(reg, rigr_v2, erif_list_rigr_erif_list_vrmid, 0x20, 7, 1);

/* erif_list_rigr_erif_list_rmid_index
 * Access: RW
 */
MLXSW_ITEM16(reg, rigr_v2, erif_list_rigr_erif_list_rmid_index, 0x22, 0, 16);

/* erif_list_rigr_erif_list_v
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, rigr_v2, erif_list_rigr_erif_list_v, MLXSW_RIGR_V2_ERIF_ENTRY_BASE_LEN, 7, 1, MLXSW_RIGR_V2_ERIF_ENTRY_REC_LEN, 0, false);

/* erif_list_rigr_erif_list_erif
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, rigr_v2, erif_list_rigr_erif_list_erif, MLXSW_RIGR_V2_ERIF_ENTRY_BASE_LEN + 2, 0, 16, MLXSW_RIGR_V2_ERIF_ENTRY_REC_LEN, 0, false);

/* erif_list_rigr_erif_list_adabe_reserved
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, rigr_v2, erif_list_rigr_erif_list_adabe_reserved, 0xa4, 0, 32, 4, 0, false);

/* erif_list_rigr_nve_decap_uerif
 * Access: RW
 */
MLXSW_ITEM16(reg, rigr_v2, erif_list_rigr_nve_decap_uerif, 0x22, 0, 16);

/* erif_list_rigr_nve_decap_tqos_profile_en
 * Access: OP
 */
MLXSW_ITEM8(reg, rigr_v2, erif_list_rigr_nve_decap_tqos_profile_en, 0x24, 7, 1);

/* erif_list_rigr_nve_decap_tqos_profile
 * Access: RW
 */
MLXSW_ITEM8(reg, rigr_v2, erif_list_rigr_nve_decap_tqos_profile, 0x24, 0, 4);

/* erif_list_rigr_nve_decap_decap_disable
 * Access: RW
 */
MLXSW_ITEM8(reg, rigr_v2, erif_list_rigr_nve_decap_decap_disable, 0x27, 0, 4);

/* erif_list_rigr_generic_checks_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, rigr_v2, erif_list_rigr_generic_checks_mode, 0x22, 0, 2);

/* erif_list_rigr_generic_allow_decap
 * Access: RW
 */
MLXSW_ITEM8(reg, rigr_v2, erif_list_rigr_generic_allow_decap, 0x23, 0, 3);

/* erif_list_rigr_generic_tqos_profile_l2
 * Access: RW
 */
MLXSW_ITEM8(reg, rigr_v2, erif_list_rigr_generic_tqos_profile_l2, 0x24, 0, 4);

/* erif_list_rigr_generic_tqos_profile_l3
 * Access: RW
 */
MLXSW_ITEM8(reg, rigr_v2, erif_list_rigr_generic_tqos_profile_l3, 0x25, 0, 4);

/* erif_list_rigr_generic_tunnel_port
 * Access: RW
 */
MLXSW_ITEM8(reg, rigr_v2, erif_list_rigr_generic_tunnel_port, 0x27, 0, 4);

/* erif_list_rigr_generic_checks_nve_decap_disable
 * Access: RW
 */
MLXSW_ITEM8(reg, rigr_v2, erif_list_rigr_generic_checks_nve_decap_disable, 0x28, 0, 4);

/* erif_list_rigr_generic_irif
 * Access: RW
 */
MLXSW_ITEM16(reg, rigr_v2, erif_list_rigr_generic_irif, 0x2a, 0, 16);

/* erif_list_rigr_generic_gre_key_check
 * Access: RW
 */
MLXSW_ITEM8(reg, rigr_v2, erif_list_rigr_generic_gre_key_check, 0x2d, 0, 1);

/* erif_list_rigr_generic_type_check
 * Access: RW
 */
MLXSW_ITEM8(reg, rigr_v2, erif_list_rigr_generic_type_check, 0x2e, 0, 3);

/* erif_list_rigr_generic_sip_check
 * Access: RW
 */
MLXSW_ITEM8(reg, rigr_v2, erif_list_rigr_generic_sip_check, 0x2f, 0, 3);

/* erif_list_rigr_generic_ipv4_usip
 * Access: RW
 */
MLXSW_ITEM32(reg, rigr_v2, erif_list_rigr_generic_ipv4_usip, 0x30, 0, 32);

/* erif_list_rigr_generic_ipv6_usip_ptr
 * Access: RW
 */
MLXSW_ITEM32(reg, rigr_v2, erif_list_rigr_generic_ipv6_usip_ptr, 0x34, 0, 24);

/* erif_list_rigr_generic_expected_gre_key
 * Access: RW
 */
MLXSW_ITEM32(reg, rigr_v2, erif_list_rigr_generic_expected_gre_key, 0x38, 0, 32);

/* erif_list_rigr_generic_uerif
 * Access: RW
 */
MLXSW_ITEM16(reg, rigr_v2, erif_list_rigr_generic_uerif, 0x3e, 0, 16);

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

/* rtdp_entry_rtdp_nve_decap_tqos_profile_en
 * Access: OP
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_nve_decap_tqos_profile_en, 0x6, 7, 1);

/* rtdp_entry_rtdp_nve_decap_tqos_profile
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_nve_decap_tqos_profile, 0x6, 0, 4);

/* rtdp_entry_rtdp_nve_decap_decap_disable
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_nve_decap_decap_disable, 0x7, 0, 4);

/* rtdp_entry_rtdp_ipinip_irif
 * Access: RW
 */
MLXSW_ITEM16(reg, rtdp, rtdp_entry_rtdp_ipinip_irif, 0x4, 0, 16);

/* rtdp_entry_rtdp_ipinip_sip_check
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_ipinip_sip_check, 0x7, 0, 3);

/* rtdp_entry_rtdp_ipinip_type_check
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_ipinip_type_check, 0x8, 0, 3);

/* rtdp_entry_rtdp_ipinip_gre_key_check
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_ipinip_gre_key_check, 0x9, 7, 1);

/* rtdp_entry_rtdp_ipinip_tqos_profile_en
 * Access: OP
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_ipinip_tqos_profile_en, 0xb, 7, 1);

/* rtdp_entry_rtdp_ipinip_tqos_profile
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_ipinip_tqos_profile, 0xb, 0, 4);

/* rtdp_entry_rtdp_ipinip_ipv4_usip
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, rtdp_entry_rtdp_ipinip_ipv4_usip, 0xc, 0, 32);

/* rtdp_entry_rtdp_ipinip_ipv6_usip_ptr
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, rtdp_entry_rtdp_ipinip_ipv6_usip_ptr, 0x10, 0, 24);

/* rtdp_entry_rtdp_ipinip_expected_gre_key
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, rtdp_entry_rtdp_ipinip_expected_gre_key, 0x14, 0, 32);

/* rtdp_entry_rtdp_generic_checks_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_generic_checks_mode, 0x6, 0, 2);

/* rtdp_entry_rtdp_generic_allow_decap
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_generic_allow_decap, 0x7, 0, 3);

/* rtdp_entry_rtdp_generic_tqos_profile_l2
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_generic_tqos_profile_l2, 0x8, 0, 4);

/* rtdp_entry_rtdp_generic_tqos_profile_l3
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_generic_tqos_profile_l3, 0x9, 0, 4);

/* rtdp_entry_rtdp_generic_tunnel_port
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_generic_tunnel_port, 0xb, 0, 4);

/* rtdp_entry_rtdp_generic_checks_nve_decap_disable
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_generic_checks_nve_decap_disable, 0xc, 0, 4);

/* rtdp_entry_rtdp_generic_irif
 * Access: RW
 */
MLXSW_ITEM16(reg, rtdp, rtdp_entry_rtdp_generic_irif, 0xe, 0, 16);

/* rtdp_entry_rtdp_generic_gre_key_check
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_generic_gre_key_check, 0x11, 0, 1);

/* rtdp_entry_rtdp_generic_type_check
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_generic_type_check, 0x12, 0, 3);

/* rtdp_entry_rtdp_generic_sip_check
 * Access: RW
 */
MLXSW_ITEM8(reg, rtdp, rtdp_entry_rtdp_generic_sip_check, 0x13, 0, 3);

/* rtdp_entry_rtdp_generic_ipv4_usip
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, rtdp_entry_rtdp_generic_ipv4_usip, 0x14, 0, 32);

/* rtdp_entry_rtdp_generic_ipv6_usip_ptr
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, rtdp_entry_rtdp_generic_ipv6_usip_ptr, 0x18, 0, 24);

/* rtdp_entry_rtdp_generic_expected_gre_key
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, rtdp_entry_rtdp_generic_expected_gre_key, 0x1c, 0, 32);

/* egress_router_interface
 * Access: RW
 */
MLXSW_ITEM16(reg, rtdp, egress_router_interface, 0x42, 0, 16);

/* uter
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, uter, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, uter, lp_msb, 0x2, 4, 2);

/* side
 * Access: INDEX
 */
MLXSW_ITEM8(reg, uter, side, 0x2, 0, 4);

/* ucheck_id
 * Access: RO
 */
MLXSW_ITEM8(reg, uter, ucheck_id, 0x5, 0, 8);

/* pending_entries
 * Access: RO
 */
MLXSW_ITEM16(reg, uter, pending_entries, 0x6, 0, 16);

/* time_stamp_sec
 * Access: RO
 */
MLXSW_ITEM32(reg, uter, time_stamp_sec, 0x8, 0, 32);

/* time_stamp_nsec
 * Access: RO
 */
MLXSW_ITEM32(reg, uter, time_stamp_nsec, 0xc, 0, 30);

/* entry
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, uter, entry, 0x10, 0, 32, 4, 0, false);

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

/* qtdem
 * -----
 *
 */
/* tqos_profile
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qtdem, tqos_profile, 0x3, 0, 4);

/* underlay_ecn
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qtdem, underlay_ecn, 0x4, 0, 2);

/* overlay_ecn
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qtdem, overlay_ecn, 0x5, 0, 2);

/* eip_ecn
 * Access: RW
 */
MLXSW_ITEM8(reg, qtdem, eip_ecn, 0x6, 0, 2);

/* trap_en
 * Access: RW
 */
MLXSW_ITEM8(reg, qtdem, trap_en, 0x8, 4, 4);

/* trap_id
 * Access: RW
 */
MLXSW_ITEM16(reg, qtdem, trap_id, 0xa, 0, 10);

/* tnifr
 * -----
 *
 */
/* table_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tnifr, table_id, 0x0, 4, 4);

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

/* usacn
 * -----
 *
 */
/* uengine
 * Access: INDEX
 */
MLXSW_ITEM16(reg, usacn, uengine, 0x0, 0, 16);

/* sadb_entry_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, usacn, sadb_entry_index, 0x2, 0, 16);

/* clear
 * Access: OP
 */
MLXSW_ITEM8(reg, usacn, clear, 0x7, 0, 1);

/* in_pkts_unchecked
 * Access: RO
 */
MLXSW_ITEM64(reg, usacn, in_pkts_unchecked, 0x8, 0, 64);

/* in_pkts_late
 * Access: RO
 */
MLXSW_ITEM64(reg, usacn, in_pkts_late, 0x10, 0, 64);

/* in_pkts_ok
 * Access: RO
 */
MLXSW_ITEM64(reg, usacn, in_pkts_ok, 0x18, 0, 64);

/* in_pkts_not_valid
 * Access: RO
 */
MLXSW_ITEM64(reg, usacn, in_pkts_not_valid, 0x20, 0, 64);

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

/* pddr
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pddr, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pddr, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pddr, lp_msb, 0x2, 4, 2);

/* port_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pddr, port_type, 0x3, 4, 4);

/* clr
 * Access: OP
 */
MLXSW_ITEM8(reg, pddr, clr, 0x4, 7, 1);

/* module_info_ext
 * Access: RW
 */
MLXSW_ITEM8(reg, pddr, module_info_ext, 0x4, 5, 2);

/* dev
 * Access: OP
 */
MLXSW_ITEM8(reg, pddr, dev, 0x4, 4, 1);

/* page_select
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pddr, page_select, 0x7, 0, 8);

/* page_data_pddr_operation_info_page_proto_active
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_operation_info_page_proto_active, 0x9, 4, 4);

/* page_data_pddr_operation_info_page_neg_mode_active
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_operation_info_page_neg_mode_active, 0x9, 0, 4);

/* page_data_pddr_operation_info_page_pd_fsm_state
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_operation_info_page_pd_fsm_state, 0xb, 0, 8);

/* page_data_pddr_operation_info_page_phy_mngr_fsm_state
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_operation_info_page_phy_mngr_fsm_state, 0xc, 0, 8);

/* page_data_pddr_operation_info_page_eth_an_fsm_state
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_operation_info_page_eth_an_fsm_state, 0xd, 0, 8);

/* page_data_pddr_operation_info_page_ib_phy_fsm_state
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_operation_info_page_ib_phy_fsm_state, 0xe, 0, 8);

/* page_data_pddr_operation_info_page_phy_hst_fsm_state
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_operation_info_page_phy_hst_fsm_state, 0xf, 0, 8);

/* page_data_pddr_operation_info_page_pm_le_pddr_phy_manager_link_enabed_ib_phy_manager_link_width_enabled
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_operation_info_page_pm_le_pddr_phy_manager_link_enabed_ib_phy_manager_link_width_enabled, 0x10, 0, 16);

/* page_data_pddr_operation_info_page_pm_le_pddr_phy_manager_link_enabed_ib_phy_manager_link_proto_enabled
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_operation_info_page_pm_le_pddr_phy_manager_link_enabed_ib_phy_manager_link_proto_enabled, 0x12, 0, 16);

/* page_data_pddr_operation_info_page_pm_le_pddr_phy_manager_link_enabed_eth_phy_manager_link_eth_enabled
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_operation_info_page_pm_le_pddr_phy_manager_link_enabed_eth_phy_manager_link_eth_enabled, 0x10, 0, 32);

/* page_data_pddr_operation_info_page_cp_le_pddr_c2p_link_enabed_ib_core_to_phy_link_width_enabled
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_operation_info_page_cp_le_pddr_c2p_link_enabed_ib_core_to_phy_link_width_enabled, 0x14, 0, 16);

/* page_data_pddr_operation_info_page_cp_le_pddr_c2p_link_enabed_ib_core_to_phy_link_proto_enabled
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_operation_info_page_cp_le_pddr_c2p_link_enabed_ib_core_to_phy_link_proto_enabled, 0x16, 0, 16);

/* page_data_pddr_operation_info_page_cp_le_pddr_c2p_link_enabed_eth_core_to_phy_link_eth_enabled
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_operation_info_page_cp_le_pddr_c2p_link_enabed_eth_core_to_phy_link_eth_enabled, 0x14, 0, 32);

/* page_data_pddr_operation_info_page_cable_proto_cap_pddr_cable_cap_ib_cable_link_width_cap
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_operation_info_page_cable_proto_cap_pddr_cable_cap_ib_cable_link_width_cap, 0x18, 0, 16);

/* page_data_pddr_operation_info_page_cable_proto_cap_pddr_cable_cap_ib_cable_link_speed_cap
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_operation_info_page_cable_proto_cap_pddr_cable_cap_ib_cable_link_speed_cap, 0x1a, 0, 16);

/* page_data_pddr_operation_info_page_cable_proto_cap_pddr_cable_cap_eth_cable_ext_eth_proto_cap
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_operation_info_page_cable_proto_cap_pddr_cable_cap_eth_cable_ext_eth_proto_cap, 0x18, 0, 32);

/* page_data_pddr_operation_info_page_link_active_pddr_link_active_ib_link_width_active
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_operation_info_page_link_active_pddr_link_active_ib_link_width_active, 0x1c, 0, 16);

/* page_data_pddr_operation_info_page_link_active_pddr_link_active_ib_link_speed_active
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_operation_info_page_link_active_pddr_link_active_ib_link_speed_active, 0x1e, 0, 16);

/* page_data_pddr_operation_info_page_link_active_pddr_link_active_eth_link_eth_active
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_operation_info_page_link_active_pddr_link_active_eth_link_eth_active, 0x1c, 0, 32);

/* page_data_pddr_operation_info_page_retran_mode_active
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_operation_info_page_retran_mode_active, 0x20, 0, 8);

/* page_data_pddr_operation_info_page_retran_mode_request
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_operation_info_page_retran_mode_request, 0x21, 0, 8);

/* page_data_pddr_operation_info_page_loopback_mode
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_operation_info_page_loopback_mode, 0x23, 0, 8);

/* page_data_pddr_operation_info_page_fec_mode_active
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_operation_info_page_fec_mode_active, 0x24, 0, 16);

/* page_data_pddr_operation_info_page_fec_mode_request
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_operation_info_page_fec_mode_request, 0x26, 0, 16);

/* page_data_pddr_operation_info_page_profile_fec_in_use
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_operation_info_page_profile_fec_in_use, 0x28, 0, 16);

/* page_data_pddr_operation_info_page_eth_25g_50g_fec_support
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_operation_info_page_eth_25g_50g_fec_support, 0x2b, 4, 4);

/* page_data_pddr_operation_info_page_eth_100g_fec_support
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_operation_info_page_eth_100g_fec_support, 0x2b, 0, 4);

/* page_data_pddr_operation_info_page_pd_link_enabled
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_operation_info_page_pd_link_enabled, 0x2c, 0, 32);

/* page_data_pddr_operation_info_page_phy_hst_link_enabled
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_operation_info_page_phy_hst_link_enabled, 0x30, 0, 32);

/* page_data_pddr_operation_info_page_eth_an_link_enabled
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_operation_info_page_eth_an_link_enabled, 0x34, 0, 32);

/* page_data_pddr_operation_info_page_core_to_phy_state
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_operation_info_page_core_to_phy_state, 0x3a, 0, 4);

/* page_data_pddr_operation_info_page_psi_fsm_state
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_operation_info_page_psi_fsm_state, 0x3b, 0, 4);

/* page_data_pddr_operation_info_page_cable_proto_cap_ext
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_operation_info_page_cable_proto_cap_ext, 0x3c, 0, 32);

/* page_data_pddr_troubleshooting_page_group_opcode
 * Access: INDEX
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_troubleshooting_page_group_opcode, 0xa, 0, 16);

/* page_data_pddr_troubleshooting_page_status_opcode_pddr_monitor_opcode_monitor_opcode
 * Access: RW
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_troubleshooting_page_status_opcode_pddr_monitor_opcode_monitor_opcode, 0xe, 0, 16);

/* page_data_pddr_troubleshooting_page_status_opcode_pddr_advanced_opcode_advanced_opcode
 * Access: RW
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_troubleshooting_page_status_opcode_pddr_advanced_opcode_advanced_opcode, 0xe, 0, 16);

/* page_data_pddr_troubleshooting_page_user_feedback_data
 * Access: RW
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_troubleshooting_page_user_feedback_data, 0x10, 0, 16);

/* page_data_pddr_troubleshooting_page_user_feedback_index
 * Access: RW
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_troubleshooting_page_user_feedback_index, 0x12, 0, 16);

/* page_data_pddr_troubleshooting_page_status_message
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, pddr, page_data_pddr_troubleshooting_page_status_message, 0x14, 236);

/* page_data_pddr_phy_info_page_remote_device_type
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_remote_device_type, 0x8, 0, 8);

/* page_data_pddr_phy_info_page_port_notifications
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_port_notifications, 0xb, 0, 8);

/* page_data_pddr_phy_info_page_num_of_negotiation_attempts
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_phy_info_page_num_of_negotiation_attempts, 0xc, 0, 16);

/* page_data_pddr_phy_info_page_ib_revision
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_ib_revision, 0xe, 0, 8);

/* page_data_pddr_phy_info_page_lp_ib_revision
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_lp_ib_revision, 0xf, 0, 8);

/* page_data_pddr_phy_info_page_hw_link_phy_state
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_hw_link_phy_state, 0x10, 0, 8);

/* page_data_pddr_phy_info_page_phy_manger_disable_mask
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_phy_info_page_phy_manger_disable_mask, 0x12, 0, 16);

/* page_data_pddr_phy_info_page_pcs_phy_state
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_info_page_pcs_phy_state, 0x14, 0, 32);

/* page_data_pddr_phy_info_page_lp_proto_enabled
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_info_page_lp_proto_enabled, 0x18, 0, 32);

/* page_data_pddr_phy_info_page_lp_fec_mode_support
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_phy_info_page_lp_fec_mode_support, 0x1c, 0, 16);

/* page_data_pddr_phy_info_page_lp_fec_mode_request
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_phy_info_page_lp_fec_mode_request, 0x1e, 0, 16);

/* page_data_pddr_phy_info_page_ib_last_link_down_reason
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_info_page_ib_last_link_down_reason, 0x20, 0, 32);

/* page_data_pddr_phy_info_page_eth_last_link_down_lane
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, pddr, page_data_pddr_phy_info_page_eth_last_link_down_lane, 0x24, 4);

/* page_data_pddr_phy_info_page_speed_deg_db
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_info_page_speed_deg_db, 0x2c, 0, 32);

/* page_data_pddr_phy_info_page_degrade_grade_lane0
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_info_page_degrade_grade_lane0, 0x30, 0, 24);

/* page_data_pddr_phy_info_page_degrade_grade_lane1
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_info_page_degrade_grade_lane1, 0x34, 0, 24);

/* page_data_pddr_phy_info_page_degrade_grade_lane2
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_info_page_degrade_grade_lane2, 0x38, 0, 24);

/* page_data_pddr_phy_info_page_degrade_grade_lane3
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_info_page_degrade_grade_lane3, 0x3c, 0, 24);

/* page_data_pddr_phy_info_page_num_of_presets_tested_lane0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_num_of_presets_tested_lane0, 0x4c, 0, 5);

/* page_data_pddr_phy_info_page_num_of_presets_tested_lane1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_num_of_presets_tested_lane1, 0x4d, 0, 5);

/* page_data_pddr_phy_info_page_num_of_presets_tested_lane2
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_num_of_presets_tested_lane2, 0x4e, 0, 5);

/* page_data_pddr_phy_info_page_num_of_presets_tested_lane3
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_num_of_presets_tested_lane3, 0x4f, 0, 5);

/* page_data_pddr_phy_info_page_kr_startup_fsm_lane
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, pddr, page_data_pddr_phy_info_page_kr_startup_fsm_lane, 0x50, 4);

/* page_data_pddr_phy_info_page_eth_an_debug_indication
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_info_page_eth_an_debug_indication, 0x58, 0, 32);

/* page_data_pddr_phy_info_page_cdr_not_locked_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_cdr_not_locked_cnt, 0x5c, 5, 3);

/* page_data_pddr_phy_info_page_fall_from_cfg_idle_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_fall_from_cfg_idle_cnt, 0x5c, 2, 3);

/* page_data_pddr_phy_info_page_fall_from_cfg_idle_cdr_cnt
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_phy_info_page_fall_from_cfg_idle_cdr_cnt, 0x5c, 7, 3);

/* page_data_pddr_phy_info_page_eth_an_watchdog_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_eth_an_watchdog_cnt, 0x5d, 5, 2);

/* page_data_pddr_phy_info_page_rounds_waited_for_peer_to_end_test
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_rounds_waited_for_peer_to_end_test, 0x5d, 0, 5);

/* page_data_pddr_phy_info_page_ib_phy_fsm_state_trace
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_phy_info_page_ib_phy_fsm_state_trace, 0x5e, 0, 16);

/* page_data_pddr_phy_info_page_kr_startup_debug_indications
 * Access: RO
 */
MLXSW_ITEM16_INDEXED(reg, pddr, page_data_pddr_phy_info_page_kr_startup_debug_indications, 0x60, 0, 16, 2, 0, false);

/* page_data_pddr_phy_info_page_tx_tuning_stages_lane0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_tx_tuning_stages_lane0, 0x68, 4, 4);

/* page_data_pddr_phy_info_page_tx_tuning_stages_lane1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_tx_tuning_stages_lane1, 0x68, 0, 4);

/* page_data_pddr_phy_info_page_tx_tuning_stages_lane2
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_tx_tuning_stages_lane2, 0x69, 4, 4);

/* page_data_pddr_phy_info_page_tx_tuning_stages_lane3
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_tx_tuning_stages_lane3, 0x69, 0, 4);

/* page_data_pddr_phy_info_page_irisc_status
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_irisc_status, 0x73, 0, 4);

/* page_data_pddr_phy_info_page_stamping_reason
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_info_page_stamping_reason, 0x74, 0, 32);

/* page_data_pddr_phy_info_page_kr_frame_lock_tuning_failure_events_count
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_info_page_kr_frame_lock_tuning_failure_events_count, 0x78, 0, 32);

/* page_data_pddr_phy_info_page_kr_full_tuning_failure_count
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_info_page_kr_full_tuning_failure_count, 0x7c, 0, 32);

/* page_data_pddr_phy_info_page_ib_debug_indication
 * Access: RW
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_phy_info_page_ib_debug_indication, 0x80, 0, 16);

/* page_data_pddr_phy_info_page_pm_debug_indication
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_phy_info_page_pm_debug_indication, 0x82, 0, 16);

/* page_data_pddr_phy_info_page_pd_debug_indication
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_info_page_pd_debug_indication, 0x88, 0, 32);

/* page_data_pddr_phy_info_page_psi_collision1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_psi_collision1, 0x8c, 3, 5);

/* page_data_pddr_phy_info_page_psi_collision2
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_phy_info_page_psi_collision2, 0x8c, 6, 5);

/* page_data_pddr_phy_info_page_hst_mismatch_reason
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_hst_mismatch_reason, 0x8d, 0, 2);

/* page_data_pddr_phy_info_page_fp_signal_detect_count
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_fp_signal_detect_count, 0x8e, 0, 6);

/* page_data_pddr_phy_info_page_pd_count
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_info_page_pd_count, 0x8f, 0, 6);

/* page_data_pddr_module_info_cable_technology
 * Access: RW
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_technology, 0x8, 0, 8);

/* page_data_pddr_module_info_cable_breakout
 * Access: RW
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_breakout, 0x9, 0, 8);

/* page_data_pddr_module_info_ext_ethernet_compliance_code
 * Access: RW
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_ext_ethernet_compliance_code, 0xa, 0, 8);

/* page_data_pddr_module_info_ethernet_compliance_code
 * Access: RW
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_ethernet_compliance_code, 0xb, 0, 8);

/* page_data_pddr_module_info_cable_type
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_type, 0xc, 4, 4);

/* page_data_pddr_module_info_cable_vendor
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_vendor, 0xc, 0, 4);

/* page_data_pddr_module_info_cable_length
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_length, 0xd, 0, 8);

/* page_data_pddr_module_info_cable_identifier
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_identifier, 0xe, 0, 8);

/* page_data_pddr_module_info_cable_power_class
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_power_class, 0xf, 0, 8);

/* page_data_pddr_module_info_max_power
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_max_power, 0x10, 0, 8);

/* page_data_pddr_module_info_cable_rx_amp
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_rx_amp, 0x11, 0, 8);

/* page_data_pddr_module_info_cable_rx_emphasis
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_rx_emphasis, 0x12, 0, 8);

/* page_data_pddr_module_info_cable_tx_equalization
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_tx_equalization, 0x13, 0, 8);

/* page_data_pddr_module_info_cable_attenuation_25g
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_attenuation_25g, 0x14, 0, 8);

/* page_data_pddr_module_info_cable_attenuation_12g
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_attenuation_12g, 0x15, 0, 8);

/* page_data_pddr_module_info_cable_attenuation_7g
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_attenuation_7g, 0x16, 0, 8);

/* page_data_pddr_module_info_cable_attenuation_5g
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_attenuation_5g, 0x17, 0, 8);

/* page_data_pddr_module_info_cable_rx_post_emphasis
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_cable_rx_post_emphasis, 0x18, 0, 8);

/* page_data_pddr_module_info_rx_cdr_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_rx_cdr_cap, 0x19, 4, 4);

/* page_data_pddr_module_info_tx_cdr_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_tx_cdr_cap, 0x19, 0, 4);

/* page_data_pddr_module_info_rx_cdr_state
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_rx_cdr_state, 0x1a, 0, 8);

/* page_data_pddr_module_info_tx_cdr_state
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_tx_cdr_state, 0x1b, 0, 8);

/* page_data_pddr_module_info_vendor_name
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, pddr, page_data_pddr_module_info_vendor_name, 0x1c, 0, 32, 4, 0, false);

/* page_data_pddr_module_info_vendor_pn
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, pddr, page_data_pddr_module_info_vendor_pn, 0x2c, 0, 32, 4, 0, false);

/* page_data_pddr_module_info_vendor_rev
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_module_info_vendor_rev, 0x3c, 0, 32);

/* page_data_pddr_module_info_fw_version
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_module_info_fw_version, 0x40, 0, 32);

/* page_data_pddr_module_info_vendor_sn
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, pddr, page_data_pddr_module_info_vendor_sn, 0x44, 0, 32, 4, 0, false);

/* page_data_pddr_module_info_temperature
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_temperature, 0x54, 0, 16);

/* page_data_pddr_module_info_voltage
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_voltage, 0x56, 0, 16);

/* page_data_pddr_module_info_rx_power_lane0
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_rx_power_lane0, 0x58, 0, 16);

/* page_data_pddr_module_info_rx_power_lane1
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_rx_power_lane1, 0x5a, 0, 16);

/* page_data_pddr_module_info_rx_power_lane2
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_rx_power_lane2, 0x5c, 0, 16);

/* page_data_pddr_module_info_rx_power_lane3
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_rx_power_lane3, 0x5e, 0, 16);

/* page_data_pddr_module_info_rx_power_lane4
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_rx_power_lane4, 0x60, 0, 16);

/* page_data_pddr_module_info_rx_power_lane5
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_rx_power_lane5, 0x62, 0, 16);

/* page_data_pddr_module_info_rx_power_lane6
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_rx_power_lane6, 0x64, 0, 16);

/* page_data_pddr_module_info_rx_power_lane7
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_rx_power_lane7, 0x66, 0, 16);

/* page_data_pddr_module_info_tx_power_lane0
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_power_lane0, 0x68, 0, 16);

/* page_data_pddr_module_info_tx_power_lane1
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_power_lane1, 0x6a, 0, 16);

/* page_data_pddr_module_info_tx_power_lane2
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_power_lane2, 0x6c, 0, 16);

/* page_data_pddr_module_info_tx_power_lane3
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_power_lane3, 0x6e, 0, 16);

/* page_data_pddr_module_info_tx_power_lane4
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_power_lane4, 0x70, 0, 16);

/* page_data_pddr_module_info_tx_power_lane5
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_power_lane5, 0x72, 0, 16);

/* page_data_pddr_module_info_tx_power_lane6
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_power_lane6, 0x74, 0, 16);

/* page_data_pddr_module_info_tx_power_lane7
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_power_lane7, 0x76, 0, 16);

/* page_data_pddr_module_info_tx_bias_lane0
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_bias_lane0, 0x78, 0, 16);

/* page_data_pddr_module_info_tx_bias_lane1
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_bias_lane1, 0x7a, 0, 16);

/* page_data_pddr_module_info_tx_bias_lane2
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_bias_lane2, 0x7c, 0, 16);

/* page_data_pddr_module_info_tx_bias_lane3
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_bias_lane3, 0x7e, 0, 16);

/* page_data_pddr_module_info_tx_bias_lane4
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_bias_lane4, 0x80, 0, 16);

/* page_data_pddr_module_info_tx_bias_lane5
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_bias_lane5, 0x82, 0, 16);

/* page_data_pddr_module_info_tx_bias_lane6
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_bias_lane6, 0x84, 0, 16);

/* page_data_pddr_module_info_tx_bias_lane7
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_bias_lane7, 0x86, 0, 16);

/* page_data_pddr_module_info_temperature_high_th
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_temperature_high_th, 0x88, 0, 16);

/* page_data_pddr_module_info_temperature_low_th
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_temperature_low_th, 0x8a, 0, 16);

/* page_data_pddr_module_info_voltage_high_th
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_voltage_high_th, 0x8c, 0, 16);

/* page_data_pddr_module_info_voltage_low_th
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_voltage_low_th, 0x8e, 0, 16);

/* page_data_pddr_module_info_rx_power_high_th
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_rx_power_high_th, 0x90, 0, 16);

/* page_data_pddr_module_info_rx_power_low_th
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_rx_power_low_th, 0x92, 0, 16);

/* page_data_pddr_module_info_tx_power_high_th
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_power_high_th, 0x94, 0, 16);

/* page_data_pddr_module_info_tx_power_low_th
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_power_low_th, 0x96, 0, 16);

/* page_data_pddr_module_info_tx_bias_high_th
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_bias_high_th, 0x98, 0, 16);

/* page_data_pddr_module_info_tx_bias_low_th
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_tx_bias_low_th, 0x9a, 0, 16);

/* page_data_pddr_module_info_module_st
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_module_st, 0x9c, 5, 3);

/* page_data_pddr_module_info_rx_power_type
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_rx_power_type, 0x9c, 4, 1);

/* page_data_pddr_module_info_did_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_did_cap, 0x9c, 3, 1);

/* page_data_pddr_module_info_smf_length
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_smf_length, 0x9c, 0, 10);

/* page_data_pddr_module_info_wavelength
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_wavelength, 0x9e, 0, 16);

/* page_data_pddr_module_info_active_set_host_compliance_code
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_active_set_host_compliance_code, 0xa0, 0, 8);

/* page_data_pddr_module_info_active_set_media_compliance_code
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_active_set_media_compliance_code, 0xa1, 0, 8);

/* page_data_pddr_module_info_ib_compliance_code
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_ib_compliance_code, 0xa3, 0, 8);

/* page_data_pddr_module_info_nbr250
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_nbr250, 0xa4, 0, 8);

/* page_data_pddr_module_info_nbr100
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_nbr100, 0xa5, 0, 8);

/* page_data_pddr_module_info_monitor_cap_mask
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_monitor_cap_mask, 0xa6, 0, 8);

/* page_data_pddr_module_info_ib_width
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_ib_width, 0xa7, 0, 6);

/* page_data_pddr_module_info_dp_st_lane0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_dp_st_lane0, 0xa8, 4, 4);

/* page_data_pddr_module_info_dp_st_lane1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_dp_st_lane1, 0xa8, 0, 4);

/* page_data_pddr_module_info_dp_st_lane2
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_dp_st_lane2, 0xa9, 4, 4);

/* page_data_pddr_module_info_dp_st_lane3
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_dp_st_lane3, 0xa9, 0, 4);

/* page_data_pddr_module_info_dp_st_lane4
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_dp_st_lane4, 0xaa, 4, 4);

/* page_data_pddr_module_info_dp_st_lane5
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_dp_st_lane5, 0xaa, 0, 4);

/* page_data_pddr_module_info_dp_st_lane6
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_dp_st_lane6, 0xab, 4, 4);

/* page_data_pddr_module_info_dp_st_lane7
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_dp_st_lane7, 0xab, 0, 4);

/* page_data_pddr_module_info_length_om2
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_length_om2, 0xac, 0, 8);

/* page_data_pddr_module_info_length_om3
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_length_om3, 0xad, 0, 8);

/* page_data_pddr_module_info_length_om4
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_length_om4, 0xae, 0, 8);

/* page_data_pddr_module_info_length_om5
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_length_om5, 0xaf, 0, 8);

/* page_data_pddr_module_info_length_om1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_length_om1, 0xb0, 0, 8);

/* page_data_pddr_module_info_wavelength_tolerance
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_module_info_wavelength_tolerance, 0xb0, 8, 16);

/* page_data_pddr_module_info_memory_map_rev
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_memory_map_rev, 0xb3, 0, 8);

/* page_data_pddr_module_info_memory_map_compliance
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_module_info_memory_map_compliance, 0xb4, 0, 32);

/* page_data_pddr_module_info_date_code
 * Access: RO
 */
MLXSW_ITEM64(reg, pddr, page_data_pddr_module_info_date_code, 0xb8, 0, 64);

/* page_data_pddr_module_info_connector_type
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_connector_type, 0xc0, 0, 8);

/* page_data_pddr_module_info_vendor_oui
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_module_info_vendor_oui, 0xc0, 0, 24);

/* page_data_pddr_module_info_tx_input_freq_sync
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_tx_input_freq_sync, 0xc5, 0, 2);

/* page_data_pddr_module_info_rx_input_valid
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_rx_input_valid, 0xc6, 0, 8);

/* page_data_pddr_module_info_rx_output_valid
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_rx_output_valid, 0xc7, 0, 8);

/* page_data_pddr_module_info_max_fiber_length
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_module_info_max_fiber_length, 0xc8, 0, 16);

/* page_data_pddr_module_info_error_code
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_module_info_error_code, 0xcb, 0, 4);

/* page_data_pddr_port_events_page_layout_invalid_fsm_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_invalid_fsm_sv, 0x8, 7, 1);

/* page_data_pddr_port_events_page_layout_invalid_fsm_ps
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_port_events_page_layout_invalid_fsm_ps, 0xa, 0, 16);

/* page_data_pddr_port_events_page_layout_kr_false_ready_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_kr_false_ready_sv, 0xd, 1, 1);

/* page_data_pddr_port_events_page_layout_kr_false_ready
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_kr_false_ready, 0xd, 0, 1);

/* page_data_pddr_port_events_page_layout_mod_req_nack_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_mod_req_nack_sv, 0xe, 3, 1);

/* page_data_pddr_port_events_page_layout_mod_req_nack
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_mod_req_nack, 0xe, 2, 1);

/* page_data_pddr_port_events_page_layout_mod_req_busy_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_mod_req_busy_sv, 0xe, 1, 1);

/* page_data_pddr_port_events_page_layout_mod_req_busy
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_mod_req_busy, 0xe, 0, 1);

/* page_data_pddr_port_events_page_layout_mod_config_to_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_mod_config_to_sv, 0xf, 7, 1);

/* page_data_pddr_port_events_page_layout_mod_config_to
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_mod_config_to, 0xf, 6, 1);

/* page_data_pddr_port_events_page_layout_mod_adapt_faild_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_mod_adapt_faild_sv, 0xf, 5, 1);

/* page_data_pddr_port_events_page_layout_mod_adapt_faild
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_mod_adapt_faild, 0xf, 4, 1);

/* page_data_pddr_port_events_page_layout_pm_fifo_full_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_pm_fifo_full_sv, 0xf, 3, 1);

/* page_data_pddr_port_events_page_layout_pm_fifo_full
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_pm_fifo_full, 0xf, 2, 1);

/* page_data_pddr_port_events_page_layout_protocol_check_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_protocol_check_sv, 0xf, 1, 1);

/* page_data_pddr_port_events_page_layout_protocol_check
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_protocol_check, 0xf, 0, 1);

/* page_data_pddr_port_events_page_layout_input_event_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_input_event_sv, 0x10, 7, 1);

/* page_data_pddr_port_events_page_layout_input_event
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_port_events_page_layout_input_event, 0x12, 0, 16);

/* page_data_pddr_port_events_page_layout_lane_mapping_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_lane_mapping_sv, 0x17, 3, 1);

/* page_data_pddr_port_events_page_layout_lane_mapping
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_lane_mapping, 0x17, 2, 1);

/* page_data_pddr_port_events_page_layout_qsfp_zero_atten_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_qsfp_zero_atten_sv, 0x17, 1, 1);

/* page_data_pddr_port_events_page_layout_qsfp_zero_atten
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_qsfp_zero_atten, 0x17, 0, 1);

/* page_data_pddr_port_events_page_layout_mono_reach_low_limit_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_mono_reach_low_limit_sv, 0x1a, 1, 1);

/* page_data_pddr_port_events_page_layout_mono_reach_low_limit
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_mono_reach_low_limit, 0x1a, 0, 1);

/* page_data_pddr_port_events_page_layout_mono_reach_high_limit_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_mono_reach_high_limit_sv, 0x1b, 7, 1);

/* page_data_pddr_port_events_page_layout_mono_reach_high_limit
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_mono_reach_high_limit, 0x1b, 6, 1);

/* page_data_pddr_port_events_page_layout_mono_flow_height_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_mono_flow_height_sv, 0x1b, 5, 1);

/* page_data_pddr_port_events_page_layout_mono_flow_height
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_mono_flow_height, 0x1b, 4, 1);

/* page_data_pddr_port_events_page_layout_single_gains_bad_val_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_single_gains_bad_val_sv, 0x1b, 3, 1);

/* page_data_pddr_port_events_page_layout_single_gains_bad_val
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_single_gains_bad_val, 0x1b, 2, 1);

/* page_data_pddr_port_events_page_layout_init_all_gains_bad_val_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_init_all_gains_bad_val_sv, 0x1b, 1, 1);

/* page_data_pddr_port_events_page_layout_init_all_gains_bad_val
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_port_events_page_layout_init_all_gains_bad_val, 0x1b, 0, 1);

/* page_data_pddr_port_events_page_layout_clr_mask
 * Access: OP
 */
MLXSW_ITEM32_INDEXED(reg, pddr, page_data_pddr_port_events_page_layout_clr_mask, 0x28, 0, 32, 4, 0, false);

/* page_data_pddr_device_events_page_invalid_port_access_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_invalid_port_access_sv, 0x8, 7, 1);

/* page_data_pddr_device_events_page_invalid_port_access
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_device_events_page_invalid_port_access, 0xa, 0, 16);

/* page_data_pddr_device_events_page_pll_state_sv_1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_pll_state_sv_1, 0xc, 0, 1);

/* page_data_pddr_device_events_page_pll_state_mask_center1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_pll_state_mask_center1, 0xd, 0, 4);

/* page_data_pddr_device_events_page_pll_state_sv_0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_pll_state_sv_0, 0xe, 0, 1);

/* page_data_pddr_device_events_page_pll_state_mask_center0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_pll_state_mask_center0, 0xf, 0, 4);

/* page_data_pddr_device_events_page_main_irisc_timeout
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_main_irisc_timeout, 0x10, 7, 1);

/* page_data_pddr_device_events_page_tile_irisc_timeout
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_tile_irisc_timeout, 0x10, 6, 1);

/* page_data_pddr_device_events_page_plu_timeout0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_plu_timeout0, 0x10, 5, 1);

/* page_data_pddr_device_events_page_plu_timeout1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_plu_timeout1, 0x10, 4, 1);

/* page_data_pddr_device_events_page_plu_timeout2
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_plu_timeout2, 0x10, 3, 1);

/* page_data_pddr_device_events_page_plu_timeout3
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_plu_timeout3, 0x10, 2, 1);

/* page_data_pddr_device_events_page_plu_timeout4
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_plu_timeout4, 0x10, 1, 1);

/* page_data_pddr_device_events_page_cr_space_timeout_mcm_main
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_cr_space_timeout_mcm_main, 0x11, 2, 1);

/* page_data_pddr_device_events_page_cr_space_timeout_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_cr_space_timeout_sv, 0x11, 1, 1);

/* page_data_pddr_device_events_page_cr_space_timeout
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_cr_space_timeout, 0x11, 0, 1);

/* page_data_pddr_device_events_page_analog_phy_to_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_analog_phy_to_sv, 0x13, 7, 1);

/* page_data_pddr_device_events_page_analog_phy_to
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_analog_phy_to, 0x13, 6, 1);

/* page_data_pddr_device_events_page_logical_phy_to_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_logical_phy_to_sv, 0x13, 5, 1);

/* page_data_pddr_device_events_page_logical_phy_to
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_logical_phy_to, 0x13, 4, 1);

/* page_data_pddr_device_events_page_varactors_calib_fail_center1_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_varactors_calib_fail_center1_sv, 0x13, 3, 1);

/* page_data_pddr_device_events_page_varactors_calib_fail_center1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_varactors_calib_fail_center1, 0x13, 2, 1);

/* page_data_pddr_device_events_page_varactors_calib_fail_center0_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_varactors_calib_fail_center0_sv, 0x13, 1, 1);

/* page_data_pddr_device_events_page_varactors_calib_fail_center0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_varactors_calib_fail_center0, 0x13, 0, 1);

/* page_data_pddr_device_events_page_irisc_stuck_mask_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_irisc_stuck_mask_sv, 0x14, 7, 1);

/* page_data_pddr_device_events_page_irisc_stuck_mask
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_device_events_page_irisc_stuck_mask, 0x14, 0, 24);

/* page_data_pddr_device_events_page_pll_lock_sv_1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_pll_lock_sv_1, 0x1c, 0, 1);

/* page_data_pddr_device_events_page_pll_unlocl_mask_center1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_pll_unlocl_mask_center1, 0x1d, 0, 4);

/* page_data_pddr_device_events_page_pll_lock_sv_0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_pll_lock_sv_0, 0x1e, 0, 1);

/* page_data_pddr_device_events_page_pll_unlocl_mask_center0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_pll_unlocl_mask_center0, 0x1f, 0, 4);

/* page_data_pddr_device_events_page_uc_stack_overflow
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_uc_stack_overflow, 0x20, 1, 1);

/* page_data_pddr_device_events_page_uc_crspace_timeout
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_uc_crspace_timeout, 0x20, 0, 1);

/* page_data_pddr_device_events_page_pwr_governor_err_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_pwr_governor_err_sv, 0x21, 1, 1);

/* page_data_pddr_device_events_page_pwr_governor_err
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_pwr_governor_err, 0x21, 0, 1);

/* page_data_pddr_device_events_page_iopl_err_center1_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_iopl_err_center1_sv, 0x23, 3, 1);

/* page_data_pddr_device_events_page_iopl_err_center1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_iopl_err_center1, 0x23, 2, 1);

/* page_data_pddr_device_events_page_iopl_err_center0_sv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_iopl_err_center0_sv, 0x23, 1, 1);

/* page_data_pddr_device_events_page_iopl_err_center0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_iopl_err_center0, 0x23, 0, 1);

/* page_data_pddr_device_events_page_clr_mask
 * Access: OP
 */
MLXSW_ITEM32_INDEXED(reg, pddr, page_data_pddr_device_events_page_clr_mask, 0x28, 0, 32, 4, 0, false);

/* page_data_pddr_device_events_page_main_irisc_address
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_device_events_page_main_irisc_address, 0x48, 0, 32);

/* page_data_pddr_device_events_page_main_irisc_ip
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_device_events_page_main_irisc_ip, 0x4c, 0, 32);

/* page_data_pddr_device_events_page_tile_irisc_address
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_device_events_page_tile_irisc_address, 0x50, 0, 32);

/* page_data_pddr_device_events_page_tile_irisc_ip
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_device_events_page_tile_irisc_ip, 0x54, 0, 32);

/* page_data_pddr_device_events_page_plu_timeout0_address
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_device_events_page_plu_timeout0_address, 0x58, 0, 16);

/* page_data_pddr_device_events_page_plu_timeout1_address
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_device_events_page_plu_timeout1_address, 0x5a, 0, 16);

/* page_data_pddr_device_events_page_plu_timeout2_address
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_device_events_page_plu_timeout2_address, 0x5c, 0, 16);

/* page_data_pddr_device_events_page_plu_timeout3_address
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_device_events_page_plu_timeout3_address, 0x5e, 0, 16);

/* page_data_pddr_device_events_page_plu_timeout4_address
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_device_events_page_plu_timeout4_address, 0x60, 0, 16);

/* page_data_pddr_device_events_page_plu_timeout0_cluster
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_plu_timeout0_cluster, 0x64, 0, 6);

/* page_data_pddr_device_events_page_plu_timeout1_cluster
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_plu_timeout1_cluster, 0x65, 0, 6);

/* page_data_pddr_device_events_page_plu_timeout2_cluster
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_plu_timeout2_cluster, 0x66, 0, 6);

/* page_data_pddr_device_events_page_plu_timeout3_cluster
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_plu_timeout3_cluster, 0x67, 0, 6);

/* page_data_pddr_device_events_page_plu_timeout4_cluster
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_plu_timeout4_cluster, 0x68, 0, 6);

/* page_data_pddr_device_events_page_irisc_tile_idx
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_irisc_tile_idx, 0x6b, 0, 4);

/* page_data_pddr_device_events_page_uc_crspace_timeout_lane
 * Access: RW
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_uc_crspace_timeout_lane, 0x6c, 0, 3);

/* page_data_pddr_device_events_page_uc_crspace_timeout_cl
 * Access: RW
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_uc_crspace_timeout_cl, 0x6d, 0, 6);

/* page_data_pddr_device_events_page_uc_stack_overflow_lane
 * Access: RW
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_uc_stack_overflow_lane, 0x6e, 0, 3);

/* page_data_pddr_device_events_page_uc_stack_overflow_cl
 * Access: RW
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_device_events_page_uc_stack_overflow_cl, 0x6f, 0, 6);

/* page_data_pddr_link_down_info_page_down_blame
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_page_down_blame, 0xb, 0, 4);

/* page_data_pddr_link_down_info_page_local_reason_opcode
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_page_local_reason_opcode, 0xf, 0, 8);

/* page_data_pddr_link_down_info_page_remote_reason_opcode
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_page_remote_reason_opcode, 0x13, 0, 8);

/* page_data_pddr_link_down_info_page_e2e_reason_opcode
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_page_e2e_reason_opcode, 0x17, 0, 8);

/* page_data_pddr_link_down_info_page_last_ber_mantissa
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_page_last_ber_mantissa, 0x18, 0, 4);

/* page_data_pddr_link_down_info_page_last_ber_exp
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_page_last_ber_exp, 0x19, 0, 8);

/* page_data_pddr_link_down_info_page_ber_mantissa
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_page_ber_mantissa, 0x1a, 0, 4);

/* page_data_pddr_link_down_info_page_ber_exp
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_page_ber_exp, 0x1b, 0, 8);

/* page_data_pddr_link_down_info_page_min_ber_mantissa
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_page_min_ber_mantissa, 0x1c, 0, 4);

/* page_data_pddr_link_down_info_page_min_ber_exp
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_page_min_ber_exp, 0x1d, 0, 8);

/* page_data_pddr_link_down_info_page_max_ber_mantissa
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_page_max_ber_mantissa, 0x1e, 0, 4);

/* page_data_pddr_link_down_info_page_max_ber_exp
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_page_max_ber_exp, 0x1f, 0, 8);

/* page_data_pddr_link_down_info_page_num_of_ber_alarams
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_link_down_info_page_num_of_ber_alarams, 0x22, 0, 16);

/* page_data_pddr_link_down_info_page_time_to_link_down_to_disable
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_down_info_page_time_to_link_down_to_disable, 0x24, 0, 32);

/* page_data_pddr_link_down_info_page_time_to_link_down_to_rx_loss
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_down_info_page_time_to_link_down_to_rx_loss, 0x28, 0, 32);

/* page_data_pddr_link_down_events_page_ib_port_events
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_down_events_page_ib_port_events, 0x8, 0, 32);

/* page_data_pddr_link_down_events_page_etherent_port_events
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_down_events_page_etherent_port_events, 0x10, 0, 32);

/* page_data_pddr_link_down_events_page_general_port_events
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_down_events_page_general_port_events, 0x18, 0, 32);

/* page_data_pddr_link_up_info_page_up_reason_pwr
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_up_info_page_up_reason_pwr, 0x9, 0, 4);

/* page_data_pddr_link_up_info_page_up_reason_drv
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_up_info_page_up_reason_drv, 0xa, 0, 4);

/* page_data_pddr_link_up_info_page_up_reason_mng
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_up_info_page_up_reason_mng, 0xb, 0, 4);

/* page_data_pddr_link_up_info_page_time_to_link_up
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_up_info_page_time_to_link_up, 0xc, 0, 32);

/* page_data_pddr_link_up_info_page_fast_link_up_status
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_up_info_page_fast_link_up_status, 0x13, 0, 4);

/* page_data_pddr_link_up_info_page_time_to_link_up_phy_up_to_active
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_up_info_page_time_to_link_up_phy_up_to_active, 0x14, 0, 32);

/* page_data_pddr_link_up_info_page_time_to_link_up_sd_to_phy_up
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_up_info_page_time_to_link_up_sd_to_phy_up, 0x18, 0, 32);

/* page_data_pddr_link_up_info_page_time_to_link_up_disable_to_sd
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_up_info_page_time_to_link_up_disable_to_sd, 0x1c, 0, 32);

/* page_data_pddr_link_up_info_page_time_to_link_up_disable_to_pd
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_up_info_page_time_to_link_up_disable_to_pd, 0x20, 0, 32);

/* page_data_module_latched_flag_info_temp_flags
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_temp_flags, 0x8, 4, 4);

/* page_data_module_latched_flag_info_vcc_flags
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_vcc_flags, 0x8, 0, 4);

/* page_data_module_latched_flag_info_mod_fw_fault
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_mod_fw_fault, 0x9, 7, 1);

/* page_data_module_latched_flag_info_dp_fw_fault
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_dp_fw_fault, 0x9, 6, 1);

/* page_data_module_latched_flag_info_tx_fault
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_tx_fault, 0xc, 0, 8);

/* page_data_module_latched_flag_info_tx_los
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_tx_los, 0xd, 0, 8);

/* page_data_module_latched_flag_info_tx_cdr_lol
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_tx_cdr_lol, 0xe, 0, 8);

/* page_data_module_latched_flag_info_tx_ad_eq_fault
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_tx_ad_eq_fault, 0xf, 0, 8);

/* page_data_module_latched_flag_info_tx_power_hi_al
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_tx_power_hi_al, 0x10, 0, 8);

/* page_data_module_latched_flag_info_tx_power_lo_al
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_tx_power_lo_al, 0x11, 0, 8);

/* page_data_module_latched_flag_info_tx_power_hi_war
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_tx_power_hi_war, 0x12, 0, 8);

/* page_data_module_latched_flag_info_tx_power_lo_war
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_tx_power_lo_war, 0x13, 0, 8);

/* page_data_module_latched_flag_info_tx_bias_hi_al
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_tx_bias_hi_al, 0x14, 0, 8);

/* page_data_module_latched_flag_info_tx_bias_lo_al
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_tx_bias_lo_al, 0x15, 0, 8);

/* page_data_module_latched_flag_info_tx_bias_hi_war
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_tx_bias_hi_war, 0x16, 0, 8);

/* page_data_module_latched_flag_info_tx_bias_lo_war
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_tx_bias_lo_war, 0x17, 0, 8);

/* page_data_module_latched_flag_info_rx_los
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_rx_los, 0x18, 0, 8);

/* page_data_module_latched_flag_info_rx_cdr_lol
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_rx_cdr_lol, 0x19, 0, 8);

/* page_data_module_latched_flag_info_rx_power_hi_al
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_rx_power_hi_al, 0x1c, 0, 8);

/* page_data_module_latched_flag_info_rx_power_lo_al
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_rx_power_lo_al, 0x1d, 0, 8);

/* page_data_module_latched_flag_info_rx_power_hi_war
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_rx_power_hi_war, 0x1e, 0, 8);

/* page_data_module_latched_flag_info_rx_power_lo_war
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_rx_power_lo_war, 0x1f, 0, 8);

/* page_data_module_latched_flag_info_rx_input_valid_change
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_rx_input_valid_change, 0x22, 0, 8);

/* page_data_module_latched_flag_info_rx_output_valid_change
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_module_latched_flag_info_rx_output_valid_change, 0x23, 0, 8);

/* page_data_pddr_phy_debug_page_pport
 * Access: INDEX
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_phy_debug_page_pport, 0x8, 6, 8);

/* page_data_pddr_phy_debug_page_trigger_active
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_debug_page_trigger_active, 0x9, 5, 1);

/* page_data_pddr_phy_debug_page_trigger_cond_state_event_val
 * Access: INDEX
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_debug_page_trigger_cond_state_event_val, 0x8, 14, 7);

/* page_data_pddr_phy_debug_page_trigger_cond_state_or_event
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_debug_page_trigger_cond_state_or_event, 0xa, 5, 1);

/* page_data_pddr_phy_debug_page_trigger_cond_fsm
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_debug_page_trigger_cond_fsm, 0xa, 0, 5);

/* page_data_pddr_phy_debug_page_pre_trigger_buff_mode
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_debug_page_pre_trigger_buff_mode, 0xb, 5, 3);

/* page_data_pddr_phy_debug_page_tracer_mode
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_debug_page_tracer_mode, 0xb, 2, 3);

/* page_data_pddr_phy_debug_page_reset_tracer
 * Access: OP
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_debug_page_reset_tracer, 0xb, 1, 1);

/* page_data_pddr_phy_debug_page_tracer_enable
 * Access: OP
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_phy_debug_page_tracer_enable, 0xb, 0, 1);

/* page_data_pddr_phy_debug_page_fsm_mask
 * Access: INDEX
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_debug_page_fsm_mask, 0xc, 0, 32);

/* page_data_pddr_phy_debug_page_trigger_ptr
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_debug_page_trigger_ptr, 0x10, 12, 12);

/* page_data_pddr_phy_debug_page_buffer_size
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_phy_debug_page_buffer_size, 0x12, 0, 12);

/* page_data_pddr_phy_debug_page_ptr_log_data
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_debug_page_ptr_log_data, 0x14, 12, 12);

/* page_data_pddr_phy_debug_page_ptr_next_write
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_phy_debug_page_ptr_next_write, 0x16, 0, 12);

/* page_data_pddr_phy_debug_page_buffer_base_address
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_phy_debug_page_buffer_base_address, 0x18, 0, 32);

/* page_data_pddr_mng_debug_page_fw_module_state
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_fw_module_state, 0xb, 0, 4);

/* page_data_pddr_mng_debug_page_fw_dp_state_lane7
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_fw_dp_state_lane7, 0xc, 4, 4);

/* page_data_pddr_mng_debug_page_fw_dp_state_lane6
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_fw_dp_state_lane6, 0xc, 0, 4);

/* page_data_pddr_mng_debug_page_fw_dp_state_lane5
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_fw_dp_state_lane5, 0xd, 4, 4);

/* page_data_pddr_mng_debug_page_fw_dp_state_lane4
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_fw_dp_state_lane4, 0xd, 0, 4);

/* page_data_pddr_mng_debug_page_fw_dp_state_lane3
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_fw_dp_state_lane3, 0xe, 4, 4);

/* page_data_pddr_mng_debug_page_fw_dp_state_lane2
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_fw_dp_state_lane2, 0xe, 0, 4);

/* page_data_pddr_mng_debug_page_fw_dp_state_lane1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_fw_dp_state_lane1, 0xf, 4, 4);

/* page_data_pddr_mng_debug_page_fw_dp_state_lane0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_fw_dp_state_lane0, 0xf, 0, 4);

/* page_data_pddr_mng_debug_page_dp_req_status_lane7
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dp_req_status_lane7, 0x10, 4, 4);

/* page_data_pddr_mng_debug_page_dp_req_status_lane6
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dp_req_status_lane6, 0x10, 0, 4);

/* page_data_pddr_mng_debug_page_dp_req_status_lane5
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dp_req_status_lane5, 0x11, 4, 4);

/* page_data_pddr_mng_debug_page_dp_req_status_lane4
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dp_req_status_lane4, 0x11, 0, 4);

/* page_data_pddr_mng_debug_page_dp_req_status_lane3
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dp_req_status_lane3, 0x12, 4, 4);

/* page_data_pddr_mng_debug_page_dp_req_status_lane2
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dp_req_status_lane2, 0x12, 0, 4);

/* page_data_pddr_mng_debug_page_dp_req_status_lane1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dp_req_status_lane1, 0x13, 4, 4);

/* page_data_pddr_mng_debug_page_dp_req_status_lane0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dp_req_status_lane0, 0x13, 0, 4);

/* page_data_pddr_mng_debug_page_dpsm_apply_state_lane7
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dpsm_apply_state_lane7, 0x14, 4, 4);

/* page_data_pddr_mng_debug_page_dpsm_apply_state_lane6
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dpsm_apply_state_lane6, 0x14, 0, 4);

/* page_data_pddr_mng_debug_page_dpsm_apply_state_lane5
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dpsm_apply_state_lane5, 0x15, 4, 4);

/* page_data_pddr_mng_debug_page_dpsm_apply_state_lane4
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dpsm_apply_state_lane4, 0x15, 0, 4);

/* page_data_pddr_mng_debug_page_dpsm_apply_state_lane3
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dpsm_apply_state_lane3, 0x16, 4, 4);

/* page_data_pddr_mng_debug_page_dpsm_apply_state_lane2
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dpsm_apply_state_lane2, 0x16, 0, 4);

/* page_data_pddr_mng_debug_page_dpsm_apply_state_lane1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dpsm_apply_state_lane1, 0x17, 4, 4);

/* page_data_pddr_mng_debug_page_dpsm_apply_state_lane0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_mng_debug_page_dpsm_apply_state_lane0, 0x17, 0, 4);

/* page_data_pddr_link_down_info_ext_16nm_lr_cause_as_detected_not_on_slot
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_cause_as_detected_not_on_slot, 0x9, 6, 2);

/* page_data_pddr_link_down_info_ext_16nm_lr_cause_high_ser
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_cause_high_ser, 0x9, 4, 2);

/* page_data_pddr_link_down_info_ext_16nm_lr_cause_rs_rx_lane0_symbol_error
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_cause_rs_rx_lane0_symbol_error, 0x9, 2, 2);

/* page_data_pddr_link_down_info_ext_16nm_lr_cause_tx_lane_fifo_underrun_l0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_cause_tx_lane_fifo_underrun_l0, 0x9, 0, 2);

/* page_data_pddr_link_down_info_ext_16nm_lr_cause_deskew_fifo_overrun
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_cause_deskew_fifo_overrun, 0xa, 0, 8);

/* page_data_pddr_link_down_info_ext_16nm_lr_cause_fec_rx_sync_m_reached_max0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_cause_fec_rx_sync_m_reached_max0, 0xb, 0, 8);

/* page_data_pddr_link_down_info_ext_16nm_lr_symbol_error_counter_lo
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_symbol_error_counter_lo, 0xc, 0, 32);

/* page_data_pddr_link_down_info_ext_16nm_lr_symbol_error_counter_hi
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_symbol_error_counter_hi, 0x10, 0, 32);

/* page_data_pddr_link_down_info_ext_16nm_lr_uncorrectable_block_counter_lo
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_uncorrectable_block_counter_lo, 0x14, 0, 32);

/* page_data_pddr_link_down_info_ext_16nm_lr_uncorrectable_block_counter_hi
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_uncorrectable_block_counter_hi, 0x18, 0, 32);

/* page_data_pddr_link_down_info_ext_16nm_lr_link_fail_due_align_loss
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_link_fail_due_align_loss, 0x1e, 0, 1);

/* page_data_pddr_link_down_info_ext_16nm_lr_block_lock_mask_at_fail_port1
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_block_lock_mask_at_fail_port1, 0x1f, 4, 4);

/* page_data_pddr_link_down_info_ext_16nm_lr_block_lock_mask_at_fail_port0
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_block_lock_mask_at_fail_port0, 0x1f, 0, 4);

/* page_data_pddr_link_down_info_ext_16nm_lr_link_down_counter
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_link_down_counter, 0x20, 0, 32);

/* page_data_pddr_link_down_info_ext_16nm_lr_effective_ber_coef
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_effective_ber_coef, 0x25, 0, 8);

/* page_data_pddr_link_down_info_ext_16nm_lr_effective_ber_magnitude
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_effective_ber_magnitude, 0x26, 4, 4);

/* page_data_pddr_link_down_info_ext_16nm_lr_raw_ber_coef
 * Access: RO
 */
MLXSW_ITEM16(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_raw_ber_coef, 0x26, 4, 8);

/* page_data_pddr_link_down_info_ext_16nm_lr_raw_ber_magnitude
 * Access: RO
 */
MLXSW_ITEM8(reg, pddr, page_data_pddr_link_down_info_ext_16nm_lr_raw_ber_magnitude, 0x27, 0, 4);

/* sbctr
 * -----
 *
 */
/* ievent
 * Access: OP
 */
MLXSW_ITEM8(reg, sbctr, ievent, 0x0, 7, 1);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbctr, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbctr, lp_msb, 0x2, 4, 2);

/* dir_ing
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbctr, dir_ing, 0x2, 0, 2);

/* fp
 * Access: RO
 */
MLXSW_ITEM8(reg, sbctr, fp, 0x3, 4, 1);

/* entity
 * Access: RO
 */
MLXSW_ITEM8(reg, sbctr, entity, 0x3, 0, 2);

/* tclass_vector_high
 * Access: RO
 */
MLXSW_ITEM32(reg, sbctr, tclass_vector_high, 0x8, 0, 32);

/* tclass_vector_low
 * Access: RO
 */
MLXSW_ITEM32(reg, sbctr, tclass_vector_low, 0xc, 0, 32);

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

/* qteem
 * -----
 *
 */
/* tqos_profile
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qteem, tqos_profile, 0x3, 0, 4);

/* overlay_ecn
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qteem, overlay_ecn, 0x4, 0, 2);

/* underlay_ecn
 * Access: RW
 */
MLXSW_ITEM8(reg, qteem, underlay_ecn, 0x5, 0, 2);

/* upcon
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upcon, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upcon, lp_msb, 0x2, 4, 2);

/* side
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upcon, side, 0x2, 0, 4);

/* sec_en
 * Access: RW
 */
MLXSW_ITEM8(reg, upcon, sec_en, 0x4, 0, 4);

/* dpol
 * Access: RW
 */
MLXSW_ITEM8(reg, upcon, dpol, 0x5, 4, 1);

/* fl
 * Access: RW
 */
MLXSW_ITEM8(reg, upcon, fl, 0x5, 0, 1);

/* inner_en
 * Access: RW
 */
MLXSW_ITEM8(reg, upcon, inner_en, 0x7, 0, 8);

/* sci_port_id
 * Access: RW
 */
MLXSW_ITEM16(reg, upcon, sci_port_id, 0xa, 0, 16);

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

/* read_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, hmon, read_type, 0x2, 0, 2);

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

/* wqe_overflow_rdq
 * Access: RW
 */
MLXSW_ITEM64_INDEXED(reg, hmon, wqe_overflow_rdq, 0x20, 0, 64, 8, 0, false);

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

/* first_pluggable_interconnect_offset
 * Access: RO
 */
MLXSW_ITEM8(reg, mgpir, first_pluggable_interconnect_offset, 0x4, 0, 8);

/* max_modules_per_slot
 * Access: RO
 */
MLXSW_ITEM8(reg, mgpir, max_modules_per_slot, 0x5, 0, 8);

/* num_of_slots
 * Access: RO
 */
MLXSW_ITEM8(reg, mgpir, num_of_slots, 0x6, 0, 8);

/* num_of_modules
 * Access: RO
 */
MLXSW_ITEM8(reg, mgpir, num_of_modules, 0x7, 0, 8);

/* fmtb
 * ----
 *
 */
/* prog_idx
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fmtb, prog_idx, 0x3, 0, 2);

/* enable
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtb, enable, 0x7, 0, 1);

/* type
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtb, type, 0x13, 0, 2);

/* bind_info_fence_binding_info_atomic
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtb, bind_info_fence_binding_info_atomic, 0x15, 0, 1);

/* bind_info_fence_binding_info_emt_bitmask
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtb, bind_info_fence_binding_info_emt_bitmask, 0x17, 0, 8);

/* bind_info_ram_binding_info_atomic
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtb, bind_info_ram_binding_info_atomic, 0x15, 0, 1);

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
/* media_width_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pmtm, media_width_cap, 0x0, 7, 1);

/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmtm, slot_index, 0x0, 0, 4);

/* module
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmtm, module, 0x1, 0, 8);

/* module_media_width
 * Access: RO
 */
MLXSW_ITEM8(reg, pmtm, module_media_width, 0x5, 0, 5);

/* module_width
 * Access: RW
 */
MLXSW_ITEM8(reg, pmtm, module_width, 0x6, 0, 5);

/* module_type
 * Access: RW
 */
MLXSW_ITEM8(reg, pmtm, module_type, 0x7, 0, 5);

/* fspt
 * ----
 *
 */
/* set_partitions_bitmap
 * Access: OP
 */
MLXSW_ITEM8(reg, fspt, set_partitions_bitmap, 0x3, 0, 8);

/* warning_th_partition_0
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, warning_th_partition_0, 0x4, 0, 19);

/* warning_th_partition_1
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, warning_th_partition_1, 0x8, 0, 19);

/* warning_th_partition_2
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, warning_th_partition_2, 0xc, 0, 19);

/* warning_th_partition_3
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, warning_th_partition_3, 0x10, 0, 19);

/* warning_th_partition_4
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, warning_th_partition_4, 0x14, 0, 19);

/* warning_th_partition_5
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, warning_th_partition_5, 0x18, 0, 19);

/* warning_th_partition_6
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, warning_th_partition_6, 0x1c, 0, 19);

/* warning_th_partition_7
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, warning_th_partition_7, 0x20, 0, 19);

/* max_th_partition_0
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, max_th_partition_0, 0x24, 0, 19);

/* max_th_partition_1
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, max_th_partition_1, 0x28, 0, 19);

/* max_th_partition_2
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, max_th_partition_2, 0x2c, 0, 19);

/* max_th_partition_3
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, max_th_partition_3, 0x30, 0, 19);

/* max_th_partition_4
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, max_th_partition_4, 0x34, 0, 19);

/* max_th_partition_5
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, max_th_partition_5, 0x38, 0, 19);

/* max_th_partition_6
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, max_th_partition_6, 0x3c, 0, 19);

/* max_th_partition_7
 * Access: RW
 */
MLXSW_ITEM32(reg, fspt, max_th_partition_7, 0x40, 0, 19);

/* spfsr
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, spfsr, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, spfsr, lp_msb, 0x2, 4, 2);

/* security
 * Access: RW
 */
MLXSW_ITEM8(reg, spfsr, security, 0x4, 7, 1);

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

/* counter_en
 * Access: RW
 */
MLXSW_ITEM8(reg, sffp, counter_en, 0xa, 0, 1);

/* counter_offset
 * Access: RW
 */
MLXSW_ITEM8(reg, sffp, counter_offset, 0xb, 0, 3);

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

/* pmecr
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmecr, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmecr, lp_msb, 0x2, 4, 2);

/* ee
 * Access: WO
 */
MLXSW_ITEM8(reg, pmecr, ee, 0x4, 6, 1);

/* eswi
 * Access: WO
 */
MLXSW_ITEM8(reg, pmecr, eswi, 0x4, 0, 1);

/* swi
 * Access: RW
 */
MLXSW_ITEM8(reg, pmecr, swi, 0x6, 0, 1);

/* e
 * Access: RW
 */
MLXSW_ITEM8(reg, pmecr, e, 0x7, 0, 2);

/* spaft
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, spaft, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, spaft, lp_msb, 0x2, 4, 2);

/* allow_untagged
 * Access: RW
 */
MLXSW_ITEM8(reg, spaft, allow_untagged, 0x4, 7, 1);

/* allow_priotagged
 * Access: RW
 */
MLXSW_ITEM8(reg, spaft, allow_priotagged, 0x4, 6, 1);

/* allow_tagged
 * Access: RW
 */
MLXSW_ITEM8(reg, spaft, allow_tagged, 0x4, 5, 1);

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

/* page_data_pter_phy_page_reg_error_type_oper
 * Access: RO
 */
MLXSW_ITEM8(reg, pter, page_data_pter_phy_page_reg_error_type_oper, 0x4, 0, 4);

/* page_data_pter_phy_page_reg_error_type_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pter, page_data_pter_phy_page_reg_error_type_cap, 0x6, 0, 8);

/* page_data_pter_phy_page_reg_error_type_admin
 * Access: RW
 */
MLXSW_ITEM8(reg, pter, page_data_pter_phy_page_reg_error_type_admin, 0x7, 0, 8);

/* page_data_pter_phy_page_reg_error_injection_time
 * Access: RW
 */
MLXSW_ITEM32(reg, pter, page_data_pter_phy_page_reg_error_injection_time, 0x8, 12, 16);

/* page_data_pter_phy_page_reg_ber_mantissa
 * Access: RW
 */
MLXSW_ITEM8(reg, pter, page_data_pter_phy_page_reg_ber_mantissa, 0xa, 0, 4);

/* page_data_pter_phy_page_reg_ber_exp
 * Access: RW
 */
MLXSW_ITEM8(reg, pter, page_data_pter_phy_page_reg_ber_exp, 0xb, 0, 8);

/* page_data_pter_phy_page_reg_rs_symbol_errors
 * Access: RW
 */
MLXSW_ITEM16(reg, pter, page_data_pter_phy_page_reg_rs_symbol_errors, 0xe, 0, 16);

/* page_data_pter_phy_page_reg_rs_errors_interval
 * Access: RW
 */
MLXSW_ITEM16(reg, pter, page_data_pter_phy_page_reg_rs_errors_interval, 0x12, 0, 16);

/* page_data_pter_port_page_reg_error_type_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pter, page_data_pter_port_page_reg_error_type_cap, 0x6, 0, 8);

/* page_data_pter_port_page_reg_error_type_admin
 * Access: RW
 */
MLXSW_ITEM8(reg, pter, page_data_pter_port_page_reg_error_type_admin, 0x7, 0, 8);

/* page_data_pter_port_page_reg_error_count
 * Access: RW
 */
MLXSW_ITEM32(reg, pter, page_data_pter_port_page_reg_error_count, 0x8, 12, 5);

/* upcnt
 * -----
 *
 */
/* clear
 * Access: OP
 */
MLXSW_ITEM8(reg, upcnt, clear, 0x0, 7, 1);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upcnt, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upcnt, lp_msb, 0x2, 4, 2);

/* grp
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upcnt, grp, 0x3, 0, 6);

/* counter_set_upcnt_group0_in_pkts_mtu
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group0_in_pkts_mtu, 0x8, 0, 64);

/* counter_set_upcnt_group0_in_pkts_general
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group0_in_pkts_general, 0x10, 0, 64);

/* counter_set_upcnt_group0_out_pkts_general
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group0_out_pkts_general, 0x18, 0, 64);

/* counter_set_upcnt_group0_in_pn_overflow
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group0_in_pn_overflow, 0x20, 0, 64);

/* counter_set_upcnt_group0_out_pn_overflow
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group0_out_pn_overflow, 0x28, 0, 64);

/* counter_set_upcnt_group0_in_pause_pfc
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group0_in_pause_pfc, 0x30, 0, 64);

/* counter_set_upcnt_group0_out_pause_pfc
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group0_out_pause_pfc, 0x38, 0, 64);

/* counter_set_upcnt_group0_in_eapol
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group0_in_eapol, 0x40, 0, 64);

/* counter_set_upcnt_group0_out_eapol
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group0_out_eapol, 0x48, 0, 64);

/* counter_set_upcnt_group0_in_buffer_overflow
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group0_in_buffer_overflow, 0x50, 0, 64);

/* counter_set_upcnt_group1_in_pkts_untagged
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group1_in_pkts_untagged, 0x8, 0, 64);

/* counter_set_upcnt_group1_in_pkts_no_tag
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group1_in_pkts_no_tag, 0x10, 0, 64);

/* counter_set_upcnt_group1_in_pkts_bad_tag
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group1_in_pkts_bad_tag, 0x18, 0, 64);

/* counter_set_upcnt_group1_in_pkts_no_sa_rcv
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group1_in_pkts_no_sa_rcv, 0x20, 0, 64);

/* counter_set_upcnt_group1_in_pkts_no_sa_discard
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group1_in_pkts_no_sa_discard, 0x28, 0, 64);

/* counter_set_upcnt_group1_in_octets_validated
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group1_in_octets_validated, 0x30, 0, 64);

/* counter_set_upcnt_group1_in_octets_decrypted
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group1_in_octets_decrypted, 0x38, 0, 64);

/* counter_set_upcnt_group1_in_pkts_too_long
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group1_in_pkts_too_long, 0x40, 0, 64);

/* counter_set_upcnt_group1_out_pkts_untagged
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group1_out_pkts_untagged, 0x48, 0, 64);

/* counter_set_upcnt_group1_out_pkts_too_long
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group1_out_pkts_too_long, 0x50, 0, 64);

/* counter_set_upcnt_group1_out_octets_protected
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group1_out_octets_protected, 0x58, 0, 64);

/* counter_set_upcnt_group1_out_octets_encrypted
 * Access: RO
 */
MLXSW_ITEM64(reg, upcnt, counter_set_upcnt_group1_out_octets_encrypted, 0x60, 0, 64);

/* sllm
 * ----
 *
 */
/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, sllm, status, 0x0, 4, 4);

/* version
 * Access: RO
 */
MLXSW_ITEM8(reg, sllm, version, 0x0, 0, 4);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sllm, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sllm, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sllm, lp_msb, 0x2, 4, 2);

/* lane
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sllm, lane, 0x2, 0, 4);

/* port_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sllm, port_type, 0x3, 4, 4);

/* c_db
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, c_db, 0x3, 0, 1);

/* page_data_sllm_16nm_lm_active
 * Access: RO
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_16nm_lm_active, 0x4, 7, 1);

/* page_data_sllm_16nm_lm_was_active
 * Access: RO
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_16nm_lm_was_active, 0x4, 6, 1);

/* page_data_sllm_16nm_pib_gw_lock
 * Access: RO
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_16nm_pib_gw_lock, 0x4, 5, 1);

/* page_data_sllm_16nm_lm_en
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_16nm_lm_en, 0x5, 0, 2);

/* page_data_sllm_16nm_lm_clk90_fl_err_max
 * Access: RW
 */
MLXSW_ITEM16(reg, sllm, page_data_sllm_16nm_lm_clk90_fl_err_max, 0x6, 0, 16);

/* page_data_sllm_16nm_lm_clk90_fl_err_acc
 * Access: RW
 */
MLXSW_ITEM32(reg, sllm, page_data_sllm_16nm_lm_clk90_fl_err_acc, 0x8, 0, 32);

/* page_data_sllm_16nm_ib3_max_lm_90_tries
 * Access: RW
 */
MLXSW_ITEM16(reg, sllm, page_data_sllm_16nm_ib3_max_lm_90_tries, 0xc, 6, 10);

/* page_data_sllm_16nm_lm_counter_up
 * Access: RW
 */
MLXSW_ITEM32(reg, sllm, page_data_sllm_16nm_lm_counter_up, 0xc, 0, 20);

/* page_data_sllm_16nm_ib1_max_lm_90_tries
 * Access: RW
 */
MLXSW_ITEM16(reg, sllm, page_data_sllm_16nm_ib1_max_lm_90_tries, 0x10, 6, 10);

/* page_data_sllm_16nm_lm_counter_mid
 * Access: RW
 */
MLXSW_ITEM32(reg, sllm, page_data_sllm_16nm_lm_counter_mid, 0x10, 0, 20);

/* page_data_sllm_16nm_lm_counter_dn
 * Access: RW
 */
MLXSW_ITEM32(reg, sllm, page_data_sllm_16nm_lm_counter_dn, 0x14, 0, 20);

/* page_data_sllm_usr_enable_lm
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_usr_enable_lm, 0x4, 7, 1);

/* page_data_sllm_usr_enable_phase_maintenance
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_usr_enable_phase_maintenance, 0x4, 6, 1);

/* page_data_sllm_usr_enable_offset_maintenance
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_usr_enable_offset_maintenance, 0x4, 5, 1);

/* page_data_sllm_usr_lm_catastrophic_bit
 * Access: RO
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_usr_lm_catastrophic_bit, 0x4, 0, 1);

/* page_data_sllm_usr_lm_activation_counter
 * Access: RO
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_usr_lm_activation_counter, 0x6, 0, 6);

/* page_data_sllm_usr_lm_fixes_counter
 * Access: RO
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_usr_lm_fixes_counter, 0x7, 0, 6);

/* page_data_sllm_usr_lane_under_maintenance
 * Access: RO
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_usr_lane_under_maintenance, 0x9, 0, 6);

/* page_data_sllm_usr_optimal_phase
 * Access: RO
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_usr_optimal_phase, 0xa, 0, 6);

/* page_data_sllm_usr_link_tuning_error
 * Access: RO
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_usr_link_tuning_error, 0xb, 0, 8);

/* page_data_sllm_usr_lane_correctable_errors
 * Access: RO
 */
MLXSW_ITEM32(reg, sllm, page_data_sllm_usr_lane_correctable_errors, 0xc, 0, 32);

/* page_data_sllm_7nm_ctle_peq_en
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_7nm_ctle_peq_en, 0x7, 0, 1);

/* page_data_sllm_7nm_peq_tsense_en
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_7nm_peq_tsense_en, 0x8, 7, 1);

/* page_data_sllm_7nm_peq_f1_adapt_skip
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_7nm_peq_f1_adapt_skip, 0x8, 6, 1);

/* page_data_sllm_7nm_vref_peq_en
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_7nm_vref_peq_en, 0x8, 5, 1);

/* page_data_sllm_7nm_dffe_peq_scout_skip
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_7nm_dffe_peq_scout_skip, 0x8, 4, 1);

/* page_data_sllm_7nm_peq_train_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_7nm_peq_train_mode, 0x9, 4, 4);

/* page_data_sllm_7nm_peq_vref_iters
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_7nm_peq_vref_iters, 0xb, 4, 4);

/* page_data_sllm_7nm_peq_adc_vref_step
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_7nm_peq_adc_vref_step, 0xd, 4, 2);

/* page_data_sllm_7nm_dffe_peq_en
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_7nm_dffe_peq_en, 0xd, 0, 1);

/* page_data_sllm_7nm_peq_dffe_iters
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_7nm_peq_dffe_iters, 0xf, 4, 4);

/* page_data_sllm_7nm_peq_dffe_delay
 * Access: RW
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_7nm_peq_dffe_delay, 0xf, 0, 4);

/* page_data_sllm_7nm_ctle_peq_cnt
 * Access: RO
 */
MLXSW_ITEM16(reg, sllm, page_data_sllm_7nm_ctle_peq_cnt, 0x10, 0, 16);

/* page_data_sllm_7nm_ber_mon_mantissa
 * Access: RO
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_7nm_ber_mon_mantissa, 0x12, 0, 4);

/* page_data_sllm_7nm_ber_mon_exp
 * Access: RO
 */
MLXSW_ITEM8(reg, sllm, page_data_sllm_7nm_ber_mon_exp, 0x13, 0, 8);

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

/* pmtu
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmtu, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmtu, lp_msb, 0x2, 4, 2);

/* i_e
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmtu, i_e, 0x3, 4, 2);

/* itre
 * Access: RW
 */
MLXSW_ITEM8(reg, pmtu, itre, 0x3, 0, 1);

/* max_mtu
 * Access: RO
 */
MLXSW_ITEM16(reg, pmtu, max_mtu, 0x4, 0, 16);

/* admin_mtu
 * Access: RW
 */
MLXSW_ITEM16(reg, pmtu, admin_mtu, 0x8, 0, 16);

/* oper_mtu
 * Access: RO
 */
MLXSW_ITEM16(reg, pmtu, oper_mtu, 0xc, 0, 16);

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

/* sticky
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, sticky, 0x3, 0, 1);

/* eeprom_override_mask
 * Access: WO
 */
MLXSW_ITEM16(reg, pmmp, eeprom_override_mask, 0x4, 0, 16);

/* eeprom_override
 * Access: RW
 */
MLXSW_ITEM16(reg, pmmp, eeprom_override, 0x6, 0, 16);

/* qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_cable_breakout
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_cable_breakout, 0xa, 0, 8);

/* qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_ethernet_compliance_code
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_ethernet_compliance_code, 0xb, 0, 8);

/* qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_ext_ethernet_compliance_code
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_ext_ethernet_compliance_code, 0xe, 0, 8);

/* qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_giga_ethernet_compliance_code
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_giga_ethernet_compliance_code, 0xf, 0, 8);

/* qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_mod_pwrup_maxduration
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_mod_pwrup_maxduration, 0x8, 4, 4);

/* qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_cable_breakout
 * Access: RW
 */
MLXSW_ITEM32(reg, pmmp, qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_cable_breakout, 0x8, 8, 13);

/* qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_host_electrical_compliance
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_host_electrical_compliance, 0xb, 0, 8);

/* qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_dp_init_maxduration
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_dp_init_maxduration, 0xc, 4, 4);

/* qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_app0_disabled
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_app0_disabled, 0xc, 0, 1);

/* qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_dp_tx_on_maxduration
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_dp_tx_on_maxduration, 0xd, 4, 4);

/* qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_dp_tx_off_maxduration
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_dp_tx_off_maxduration, 0xd, 0, 4);

/* qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_module_media_type
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_module_media_type, 0xe, 0, 8);

/* qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_media_compliance
 * Access: RW
 */
MLXSW_ITEM8(reg, pmmp, qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_media_compliance, 0xf, 0, 8);

/* qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_cmis_override_mask
 * Access: RW
 */
MLXSW_ITEM16(reg, pmmp, qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_cmis_override_mask, 0x12, 0, 16);

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

/* upbt
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upbt, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upbt, lp_msb, 0x2, 4, 2);

/* side
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upbt, side, 0x2, 0, 4);

/* lookup
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upbt, lookup, 0x3, 0, 1);

/* region_id
 * Access: RW
 */
MLXSW_ITEM16(reg, upbt, region_id, 0x6, 0, 16);

/* utcam_key_id
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, upbt, utcam_key_id, 0x8, 0, 32, 4, 0, false);

/* op
 * Access: OP
 */
MLXSW_ITEM8(reg, upbt, op, 0x1b, 0, 2);

/* fmep
 * ----
 *
 */
/* global
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fmep, global, 0x0, 7, 1);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fmep, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fmep, lp_msb, 0x2, 4, 2);

/* ext_mod_parsing
 * Access: RW
 */
MLXSW_ITEM16(reg, fmep, ext_mod_parsing, 0x6, 0, 9);

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

/* rarlpgt
 * -------
 *
 */
/* arlpgt_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, rarlpgt, arlpgt_index, 0x2, 0, 16);

/* egress_port
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, rarlpgt, egress_port, 0x20, 0, 32, 4, 0, false);

/* egress_port_or
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, rarlpgt, egress_port_or, 0xa0, 0, 32, 4, 0, false);

/* utar
 * ----
 *
 */
/* uengine
 * Access: INDEX
 */
MLXSW_ITEM16(reg, utar, uengine, 0x0, 0, 16);

/* region_id
 * Access: INDEX
 */
MLXSW_ITEM16(reg, utar, region_id, 0x2, 0, 16);

/* offset
 * Access: RW
 */
MLXSW_ITEM16(reg, utar, offset, 0x4, 0, 16);

/* size
 * Access: RW
 */
MLXSW_ITEM16(reg, utar, size, 0x6, 0, 16);

/* key_size
 * Access: RW
 */
MLXSW_ITEM8(reg, utar, key_size, 0xb, 0, 4);

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

/* pvgt
 * ----
 *
 */
/* swid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pvgt, swid, 0x0, 0, 8);

/* op
 * Access: WO
 */
MLXSW_ITEM8(reg, pvgt, op, 0x1, 4, 3);

/* vid
 * Access: INDEX
 */
MLXSW_ITEM16(reg, pvgt, vid, 0x2, 0, 12);

/* vlan_group
 * Access: RW
 */
MLXSW_ITEM16(reg, pvgt, vlan_group, 0x6, 0, 12);

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

/* data_slot_info_provisioned
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, data_slot_info_provisioned, 0x10, 7, 1);

/* data_slot_info_sr_valid
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, data_slot_info_sr_valid, 0x10, 6, 1);

/* data_slot_info_lc_ready
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, data_slot_info_lc_ready, 0x10, 4, 2);

/* data_slot_info_active
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, data_slot_info_active, 0x10, 3, 1);

/* data_slot_info_hw_revision
 * Access: RO
 */
MLXSW_ITEM16(reg, mddq, data_slot_info_hw_revision, 0x14, 0, 16);

/* data_slot_info_ini_file_version
 * Access: RO
 */
MLXSW_ITEM16(reg, mddq, data_slot_info_ini_file_version, 0x16, 0, 16);

/* data_slot_info_card_type
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, data_slot_info_card_type, 0x1b, 0, 8);

/* data_device_info_uses_flash
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, data_device_info_uses_flash, 0x10, 7, 1);

/* data_device_info_flash_owner
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, data_device_info_flash_owner, 0x10, 6, 1);

/* data_device_info_thermal_sd
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, data_device_info_thermal_sd, 0x10, 5, 1);

/* data_device_info_lc_pwr_on
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, data_device_info_lc_pwr_on, 0x10, 4, 1);

/* data_device_info_flash_id
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, data_device_info_flash_id, 0x11, 0, 8);

/* data_device_info_device_index
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, data_device_info_device_index, 0x13, 0, 8);

/* data_device_info_fw_major
 * Access: RO
 */
MLXSW_ITEM16(reg, mddq, data_device_info_fw_major, 0x14, 0, 16);

/* data_device_info_device_type
 * Access: RO
 */
MLXSW_ITEM16(reg, mddq, data_device_info_device_type, 0x16, 0, 16);

/* data_device_info_fw_minor
 * Access: RO
 */
MLXSW_ITEM16(reg, mddq, data_device_info_fw_minor, 0x18, 0, 16);

/* data_device_info_fw_sub_minor
 * Access: RO
 */
MLXSW_ITEM16(reg, mddq, data_device_info_fw_sub_minor, 0x1a, 0, 16);

/* data_device_info_max_cmd_read_size_supp
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, data_device_info_max_cmd_read_size_supp, 0x1e, 0, 8);

/* data_device_info_max_cmd_write_size_supp
 * Access: RO
 */
MLXSW_ITEM8(reg, mddq, data_device_info_max_cmd_write_size_supp, 0x1f, 0, 8);

/* data_device_info_device_type_name
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, mddq, data_device_info_device_type_name, 0x20, 8);

/* data_slot_name_slot_ascii_name
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, mddq, data_slot_name_slot_ascii_name, 0x10, 20);

/* fsdb
 * ----
 *
 */
/* acl_group_id
 * Access: INDEX
 */
MLXSW_ITEM16(reg, fsdb, acl_group_id, 0x2, 0, 16);

/* fr
 * Access: RO
 */
MLXSW_ITEM8(reg, fsdb, fr, 0x5, 0, 3);

/* partition_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fsdb, partition_id, 0x6, 0, 3);

/* db_op
 * Access: OP
 */
MLXSW_ITEM8(reg, fsdb, db_op, 0x7, 4, 3);

/* sem_op
 * Access: OP
 */
MLXSW_ITEM8(reg, fsdb, sem_op, 0x7, 0, 2);

/* s
 * Access: RO
 */
MLXSW_ITEM8(reg, fsdb, s, 0x8, 7, 1);

/* hit
 * Access: RO
 */
MLXSW_ITEM8(reg, fsdb, hit, 0x8, 2, 1);

/* a
 * Access: RO
 */
MLXSW_ITEM8(reg, fsdb, a, 0x8, 1, 1);

/* sem_val
 * Access: RO
 */
MLXSW_ITEM8(reg, fsdb, sem_val, 0x8, 0, 1);

/* sem_lock_cnt
 * Access: RO
 */
MLXSW_ITEM16(reg, fsdb, sem_lock_cnt, 0xa, 0, 16);

/* data
 * Access: RW
 */
MLXSW_ITEM64(reg, fsdb, data, 0x10, 0, 64);

/* key_data
 * Access: INDEX
 */
MLXSW_ITEM_BUF(reg, fsdb, key_data, 0x18, 96);

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

/* mdif
 * ----
 *
 */
/* global
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mdif, global, 0x0, 7, 1);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mdif, lp_msb, 0x2, 4, 2);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mdif, local_port, 0x3, 0, 8);

/* field_select
 * Access: OP
 */
MLXSW_ITEM8(reg, mdif, field_select, 0x7, 0, 3);

/* crc_err_mode
 * Access: WO
 */
MLXSW_ITEM8(reg, mdif, crc_err_mode, 0xb, 1, 1);

/* crc_lanes_mode
 * Access: OP
 */
MLXSW_ITEM8(reg, mdif, crc_lanes_mode, 0xb, 0, 1);

/* inject_sram_ecc
 * Access: OP
 */
MLXSW_ITEM8(reg, mdif, inject_sram_ecc, 0xf, 0, 1);

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

/* sltp
 * ----
 *
 */
/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sltp, lp_msb, 0x0, 6, 2);

/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, sltp, status, 0x0, 4, 2);

/* version
 * Access: RO
 */
MLXSW_ITEM8(reg, sltp, version, 0x0, 0, 4);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sltp, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sltp, pnat, 0x2, 6, 2);

/* tx_policy
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, tx_policy, 0x2, 5, 1);

/* conf_mod
 * Access: OP
 */
MLXSW_ITEM8(reg, sltp, conf_mod, 0x2, 4, 1);

/* lane
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sltp, lane, 0x2, 0, 4);

/* lane_speed
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, lane_speed, 0x3, 4, 4);

/* port_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sltp, port_type, 0x3, 1, 3);

/* c_db
 * Access: OP
 */
MLXSW_ITEM8(reg, sltp, c_db, 0x3, 0, 1);

/* page_data_sltp_28nm_40nm_polarity
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_28nm_40nm_polarity, 0x8, 0, 1);

/* page_data_sltp_28nm_40nm_ob_tap0
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_28nm_40nm_ob_tap0, 0x9, 0, 8);

/* page_data_sltp_28nm_40nm_ob_tap1
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_28nm_40nm_ob_tap1, 0xa, 0, 8);

/* page_data_sltp_28nm_40nm_ob_tap2
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_28nm_40nm_ob_tap2, 0xb, 0, 8);

/* page_data_sltp_28nm_40nm_ob_leva
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_28nm_40nm_ob_leva, 0xd, 4, 4);

/* page_data_sltp_28nm_40nm_ob_preemp_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_28nm_40nm_ob_preemp_mode, 0xd, 0, 4);

/* page_data_sltp_28nm_40nm_ob_reg
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_28nm_40nm_ob_reg, 0xe, 0, 8);

/* page_data_sltp_28nm_40nm_ob_bias
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_28nm_40nm_ob_bias, 0xf, 0, 8);

/* page_data_sltp_28nm_40nm_ob_norm
 * Access: RO
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_28nm_40nm_ob_norm, 0x10, 7, 1);

/* page_data_sltp_28nm_40nm_ob_bad_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_28nm_40nm_ob_bad_stat, 0x10, 5, 2);

/* page_data_sltp_16nm_pre_2_tap
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_16nm_pre_2_tap, 0x8, 0, 8);

/* page_data_sltp_16nm_pre_tap
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_16nm_pre_tap, 0x9, 0, 8);

/* page_data_sltp_16nm_main_tap
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_16nm_main_tap, 0xa, 0, 8);

/* page_data_sltp_16nm_post_tap
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_16nm_post_tap, 0xb, 0, 8);

/* page_data_sltp_16nm_ob_m2lp
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_16nm_ob_m2lp, 0xc, 1, 7);

/* page_data_sltp_16nm_ob_amp
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_16nm_ob_amp, 0xe, 0, 7);

/* page_data_sltp_16nm_ob_alev_out
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_16nm_ob_alev_out, 0xf, 0, 5);

/* page_data_sltp_16nm_ob_bad_stat
 * Access: RO
 */
MLXSW_ITEM16(reg, sltp, page_data_sltp_16nm_ob_bad_stat, 0x10, 0, 16);

/* page_data_sltp_7nm_drv_amp
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_7nm_drv_amp, 0x4, 0, 6);

/* page_data_sltp_7nm_ob_bad_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_7nm_ob_bad_stat, 0x5, 0, 8);

/* page_data_sltp_7nm_fir_pre3
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_7nm_fir_pre3, 0x6, 0, 8);

/* page_data_sltp_7nm_fir_pre2
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_7nm_fir_pre2, 0x7, 0, 8);

/* page_data_sltp_7nm_fir_pre1
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_7nm_fir_pre1, 0x8, 0, 8);

/* page_data_sltp_7nm_fir_main
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_7nm_fir_main, 0x9, 0, 8);

/* page_data_sltp_7nm_fir_post1
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_7nm_fir_post1, 0xa, 0, 8);

/* page_data_sltp_lut_7nm_vs_peer_db
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_vs_peer_db, 0x4, 6, 2);

/* page_data_sltp_lut_7nm_drv_amp
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_drv_amp, 0x4, 0, 6);

/* page_data_sltp_lut_7nm_ob_bad_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_ob_bad_stat, 0x5, 0, 8);

/* page_data_sltp_lut_7nm_fir_pre3
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_fir_pre3, 0x6, 0, 8);

/* page_data_sltp_lut_7nm_fir_pre2
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_fir_pre2, 0x7, 0, 8);

/* page_data_sltp_lut_7nm_lut3
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut3, 0xc, 0, 8);

/* page_data_sltp_lut_7nm_lut2
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut2, 0xd, 0, 8);

/* page_data_sltp_lut_7nm_lut1
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut1, 0xe, 0, 8);

/* page_data_sltp_lut_7nm_lut0
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut0, 0xf, 0, 8);

/* page_data_sltp_lut_7nm_lut7
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut7, 0x10, 0, 8);

/* page_data_sltp_lut_7nm_lut6
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut6, 0x11, 0, 8);

/* page_data_sltp_lut_7nm_lut5
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut5, 0x12, 0, 8);

/* page_data_sltp_lut_7nm_lut4
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut4, 0x13, 0, 8);

/* page_data_sltp_lut_7nm_lut11
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut11, 0x14, 0, 8);

/* page_data_sltp_lut_7nm_lut10
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut10, 0x15, 0, 8);

/* page_data_sltp_lut_7nm_lut9
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut9, 0x16, 0, 8);

/* page_data_sltp_lut_7nm_lut8
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut8, 0x17, 0, 8);

/* page_data_sltp_lut_7nm_lut15
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut15, 0x18, 0, 8);

/* page_data_sltp_lut_7nm_lut14
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut14, 0x19, 0, 8);

/* page_data_sltp_lut_7nm_lut13
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut13, 0x1a, 0, 8);

/* page_data_sltp_lut_7nm_lut12
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut12, 0x1b, 0, 8);

/* page_data_sltp_lut_7nm_lut19
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut19, 0x1c, 0, 8);

/* page_data_sltp_lut_7nm_lut18
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut18, 0x1d, 0, 8);

/* page_data_sltp_lut_7nm_lut17
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut17, 0x1e, 0, 8);

/* page_data_sltp_lut_7nm_lut16
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut16, 0x1f, 0, 8);

/* page_data_sltp_lut_7nm_lut23
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut23, 0x20, 0, 8);

/* page_data_sltp_lut_7nm_lut22
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut22, 0x21, 0, 8);

/* page_data_sltp_lut_7nm_lut21
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut21, 0x22, 0, 8);

/* page_data_sltp_lut_7nm_lut20
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut20, 0x23, 0, 8);

/* page_data_sltp_lut_7nm_lut27
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut27, 0x24, 0, 8);

/* page_data_sltp_lut_7nm_lut26
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut26, 0x25, 0, 8);

/* page_data_sltp_lut_7nm_lut25
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut25, 0x26, 0, 8);

/* page_data_sltp_lut_7nm_lut24
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut24, 0x27, 0, 8);

/* page_data_sltp_lut_7nm_lut31
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut31, 0x28, 0, 8);

/* page_data_sltp_lut_7nm_lut30
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut30, 0x29, 0, 8);

/* page_data_sltp_lut_7nm_lut29
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut29, 0x2a, 0, 8);

/* page_data_sltp_lut_7nm_lut28
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut28, 0x2b, 0, 8);

/* page_data_sltp_lut_7nm_lut35
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut35, 0x2c, 0, 8);

/* page_data_sltp_lut_7nm_lut34
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut34, 0x2d, 0, 8);

/* page_data_sltp_lut_7nm_lut33
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut33, 0x2e, 0, 8);

/* page_data_sltp_lut_7nm_lut32
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut32, 0x2f, 0, 8);

/* page_data_sltp_lut_7nm_lut39
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut39, 0x30, 0, 8);

/* page_data_sltp_lut_7nm_lut38
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut38, 0x31, 0, 8);

/* page_data_sltp_lut_7nm_lut37
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut37, 0x32, 0, 8);

/* page_data_sltp_lut_7nm_lut36
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut36, 0x33, 0, 8);

/* page_data_sltp_lut_7nm_lut43
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut43, 0x34, 0, 8);

/* page_data_sltp_lut_7nm_lut42
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut42, 0x35, 0, 8);

/* page_data_sltp_lut_7nm_lut41
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut41, 0x36, 0, 8);

/* page_data_sltp_lut_7nm_lut40
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut40, 0x37, 0, 8);

/* page_data_sltp_lut_7nm_lut47
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut47, 0x38, 0, 8);

/* page_data_sltp_lut_7nm_lut46
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut46, 0x39, 0, 8);

/* page_data_sltp_lut_7nm_lut45
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut45, 0x3a, 0, 8);

/* page_data_sltp_lut_7nm_lut44
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut44, 0x3b, 0, 8);

/* page_data_sltp_lut_7nm_lut51
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut51, 0x3c, 0, 8);

/* page_data_sltp_lut_7nm_lut50
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut50, 0x3d, 0, 8);

/* page_data_sltp_lut_7nm_lut49
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut49, 0x3e, 0, 8);

/* page_data_sltp_lut_7nm_lut48
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut48, 0x3f, 0, 8);

/* page_data_sltp_lut_7nm_lut55
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut55, 0x40, 0, 8);

/* page_data_sltp_lut_7nm_lut54
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut54, 0x41, 0, 8);

/* page_data_sltp_lut_7nm_lut53
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut53, 0x42, 0, 8);

/* page_data_sltp_lut_7nm_lut52
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut52, 0x43, 0, 8);

/* page_data_sltp_lut_7nm_lut59
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut59, 0x44, 0, 8);

/* page_data_sltp_lut_7nm_lut58
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut58, 0x45, 0, 8);

/* page_data_sltp_lut_7nm_lut57
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut57, 0x46, 0, 8);

/* page_data_sltp_lut_7nm_lut56
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut56, 0x47, 0, 8);

/* page_data_sltp_lut_7nm_lut63
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut63, 0x48, 0, 8);

/* page_data_sltp_lut_7nm_lut62
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut62, 0x49, 0, 8);

/* page_data_sltp_lut_7nm_lut61
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut61, 0x4a, 0, 8);

/* page_data_sltp_lut_7nm_lut60
 * Access: RW
 */
MLXSW_ITEM8(reg, sltp, page_data_sltp_lut_7nm_lut60, 0x4b, 0, 8);

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

/* fmqc
 * ----
 *
 */
/* s
 * Access: RO
 */
MLXSW_ITEM8(reg, fmqc, s, 0x1, 0, 1);

/* lp
 * Access: INDEX
 */
MLXSW_ITEM16(reg, fmqc, lp, 0x2, 0, 10);

/* modifier_cluster
 * Access: RO
 */
MLXSW_ITEM16(reg, fmqc, modifier_cluster, 0x6, 0, 11);

/* pphcr
 * -----
 *
 */
/* active_hist_type
 * Access: RO
 */
MLXSW_ITEM8(reg, pphcr, active_hist_type, 0x0, 4, 4);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pphcr, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pphcr, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pphcr, lp_msb, 0x2, 4, 2);

/* we
 * Access: RO
 */
MLXSW_ITEM8(reg, pphcr, we, 0x3, 0, 1);

/* num_of_bins
 * Access: RO
 */
MLXSW_ITEM8(reg, pphcr, num_of_bins, 0x5, 0, 8);

/* hist_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pphcr, hist_type, 0x7, 0, 4);

/* hist_max_measurement
 * Access: RO
 */
MLXSW_ITEM8(reg, pphcr, hist_max_measurement, 0x9, 0, 8);

/* hist_min_measurement
 * Access: RO
 */
MLXSW_ITEM8(reg, pphcr, hist_min_measurement, 0xb, 0, 8);

/* bin_range_write_mask
 * Access: WO
 */
MLXSW_ITEM16(reg, pphcr, bin_range_write_mask, 0xe, 0, 16);

/* high_val
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, pphcr, high_val, MLXSW_PPHCR_BIN_RANGE_BASE_LEN + 1, 0, 4, MLXSW_PPHCR_BIN_RANGE_REC_LEN, 0, false);

/* low_val
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, pphcr, low_val, MLXSW_PPHCR_BIN_RANGE_BASE_LEN + 3, 0, 4, MLXSW_PPHCR_BIN_RANGE_REC_LEN, 0, false);

/* qcap
 * ----
 *
 */
/* max_policers_per_port
 * Access: RO
 */
MLXSW_ITEM8(reg, qcap, max_policers_per_port, 0xb, 0, 8);

/* max_policers_global
 * Access: RO
 */
MLXSW_ITEM8(reg, qcap, max_policers_global, 0xf, 0, 8);

/* max_policers_cpu
 * Access: RO
 */
MLXSW_ITEM8(reg, qcap, max_policers_cpu, 0x13, 0, 8);

/* mtwe
 * ----
 *
 */
/* sensor_warning
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mtwe, sensor_warning, 0x0, 0, 32, 4, 0, false);

/* mfgd
 * ----
 *
 */
/* en_debug_assert
 * Access: RW
 */
MLXSW_ITEM8(reg, mfgd, en_debug_assert, 0x1, 0, 1);

/* fw_fatal_event_test
 * Access: OP
 */
MLXSW_ITEM8(reg, mfgd, fw_fatal_event_test, 0x2, 3, 4);

/* fw_fatal_event_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, mfgd, fw_fatal_event_mode, 0x2, 1, 2);

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

/* fw_info_dev_sc
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_dev_sc, 0x20, 6, 1);

/* fw_info_latency_tlv
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_latency_tlv, 0x20, 5, 1);

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

/* fw_info_disabled_tiles_bitmap
 * Access: RO
 */
MLXSW_ITEM16(reg, mgir, fw_info_disabled_tiles_bitmap, 0x50, 0, 16);

/* fw_info_isfu_major
 * Access: RO
 */
MLXSW_ITEM16(reg, mgir, fw_info_isfu_major, 0x52, 0, 16);

/* fw_info_encryption
 * Access: RO
 */
MLXSW_ITEM8(reg, mgir, fw_info_encryption, 0x57, 3, 1);

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

/* rirt
 * ----
 *
 */
/* offset
 * Access: INDEX
 */
MLXSW_ITEM16(reg, rirt, offset, 0x2, 0, 12);

/* valid
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg, rirt, valid, MLXSW_RIRT_ROUTER_ENTRY_RECORD_BASE_LEN, 7, 1, MLXSW_RIRT_ROUTER_ENTRY_RECORD_REC_LEN, 0, false);

/* swid
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg, rirt, swid, MLXSW_RIRT_ROUTER_ENTRY_RECORD_BASE_LEN + 3, 0, 3, MLXSW_RIRT_ROUTER_ENTRY_RECORD_REC_LEN, 0, false);

/* subnet_prefix
 * Access: RO
 */
MLXSW_ITEM16_INDEXED(reg, rirt, subnet_prefix, MLXSW_RIRT_ROUTER_ENTRY_RECORD_BASE_LEN + 2, 0, 16, MLXSW_RIRT_ROUTER_ENTRY_RECORD_REC_LEN, 4, false);

/* modcr
 * -----
 *
 */
/* clear
 * Access: OP
 */
MLXSW_ITEM8(reg, modcr, clear, 0x0, 7, 1);

/* fatal_asserts
 * Access: RO
 */
MLXSW_ITEM32(reg, modcr, fatal_asserts, 0x8, 0, 32);

/* normal_asserts
 * Access: RO
 */
MLXSW_ITEM32(reg, modcr, normal_asserts, 0xc, 0, 32);

/* debug_asserts
 * Access: RO
 */
MLXSW_ITEM32(reg, modcr, debug_asserts, 0x10, 0, 32);

/* uccr
 * ----
 *
 */
/* side
 * Access: INDEX
 */
MLXSW_ITEM8(reg, uccr, side, 0x2, 0, 4);

/* count_en
 * Access: RW
 */
MLXSW_ITEM8(reg, uccr, count_en, 0x4, 4, 1);

/* forwarding
 * Access: RW
 */
MLXSW_ITEM8(reg, uccr, forwarding, 0x4, 0, 2);

/* to_utrap
 * Access: RW
 */
MLXSW_ITEM8(reg, uccr, to_utrap, 0x5, 0, 2);

/* ucheck_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, uccr, ucheck_id, 0x7, 0, 8);

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

/* ralta
 * -----
 *
 */
/* op
 * Access: OP
 */
MLXSW_ITEM8(reg, ralta, op, 0x0, 4, 2);

/* protocol
 * Access: RW
 */
MLXSW_ITEM8(reg, ralta, protocol, 0x0, 0, 4);

/* tree_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ralta, tree_id, 0x3, 0, 8);

/* mocmi
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mocmi, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mocmi, lp_msb, 0x2, 4, 2);

/* cond_nelp
 * Access: RW
 */
MLXSW_ITEM16(reg, mocmi, cond_nelp, 0xa, 0, 16);

/* cond_elp
 * Access: RW
 */
MLXSW_ITEM16(reg, mocmi, cond_elp, 0xe, 0, 16);

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

/* ppcgp
 * -----
 *
 */
/* grp_profile
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppcgp, grp_profile, 0x3, 0, 3);

/* hi
 * Access: 
 */
MLXSW_ITEM32(reg, ppcgp, hi, 0x4, 0, 32);

/* lo
 * Access: 
 */
MLXSW_ITEM32(reg, ppcgp, lo, 0x8, 0, 32);

/* raltb
 * -----
 *
 */
/* virtual_router
 * Access: INDEX
 */
MLXSW_ITEM16(reg, raltb, virtual_router, 0x0, 0, 16);

/* protocol
 * Access: INDEX
 */
MLXSW_ITEM8(reg, raltb, protocol, 0x2, 4, 4);

/* tree_id
 * Access: RW
 */
MLXSW_ITEM8(reg, raltb, tree_id, 0x3, 0, 8);

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

/* extra_data_ceer_extra_fields_vni
 * Access: RO
 */
MLXSW_ITEM32(reg, ceer, extra_data_ceer_extra_fields_vni, 0x60, 0, 24);

/* extra_data_ceer_extra_fields_inner_dmac
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, ceer, extra_data_ceer_extra_fields_inner_dmac, 0x6a, 6);

/* extra_data_ceer_extra_fields_inner_smac
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, ceer, extra_data_ceer_extra_fields_inner_smac, 0x72, 6);

/* extra_data_ceer_extra_fields_inner_l3_type
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_inner_l3_type, 0x7c, 0, 4);

/* extra_data_ceer_extra_fields_inner_dscp
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_inner_dscp, 0x7d, 2, 6);

/* extra_data_ceer_extra_fields_inner_ecn
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_inner_ecn, 0x7d, 0, 2);

/* extra_data_ceer_extra_fields_inner_ttl
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_inner_ttl, 0x7e, 0, 8);

/* extra_data_ceer_extra_fields_inner_dont_frag
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_inner_dont_frag, 0x7f, 0, 1);

/* extra_data_ceer_extra_fields_inner_sip
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, ceer, extra_data_ceer_extra_fields_inner_sip, 0x80, 0, 32, 4, 0, false);

/* extra_data_ceer_extra_fields_inner_dip
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, ceer, extra_data_ceer_extra_fields_inner_dip, 0x90, 0, 32, 4, 0, false);

/* extra_data_ceer_extra_fields_mpls_mpls_bos
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_bos, 0x60, 7, 1);

/* extra_data_ceer_extra_fields_mpls_mpls_exp
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_exp, 0x63, 0, 3);

/* extra_data_ceer_extra_fields_mpls_mpls_lb0_v
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_lb0_v, 0x64, 7, 1);

/* extra_data_ceer_extra_fields_mpls_mpls_label0_label_id
 * Access: RO
 */
MLXSW_ITEM32(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_label0_label_id, 0x64, 8, 20);

/* extra_data_ceer_extra_fields_mpls_mpls_label0_ttl
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_label0_ttl, 0x67, 0, 8);

/* extra_data_ceer_extra_fields_mpls_mpls_lb1_v
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_lb1_v, 0x68, 7, 1);

/* extra_data_ceer_extra_fields_mpls_mpls_label1_label_id
 * Access: RO
 */
MLXSW_ITEM32(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_label1_label_id, 0x68, 8, 20);

/* extra_data_ceer_extra_fields_mpls_mpls_label1_ttl
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_label1_ttl, 0x6b, 0, 8);

/* extra_data_ceer_extra_fields_mpls_mpls_lb2_v
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_lb2_v, 0x6c, 7, 1);

/* extra_data_ceer_extra_fields_mpls_mpls_label2_label_id
 * Access: RO
 */
MLXSW_ITEM32(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_label2_label_id, 0x6c, 8, 20);

/* extra_data_ceer_extra_fields_mpls_mpls_label2_ttl
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_label2_ttl, 0x6f, 0, 8);

/* extra_data_ceer_extra_fields_mpls_mpls_lb3_v
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_lb3_v, 0x70, 7, 1);

/* extra_data_ceer_extra_fields_mpls_mpls_label3_label_id
 * Access: RO
 */
MLXSW_ITEM32(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_label3_label_id, 0x70, 8, 20);

/* extra_data_ceer_extra_fields_mpls_mpls_label3_ttl
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_label3_ttl, 0x73, 0, 8);

/* extra_data_ceer_extra_fields_mpls_mpls_lb4_v
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_lb4_v, 0x74, 7, 1);

/* extra_data_ceer_extra_fields_mpls_mpls_label4_label_id
 * Access: RO
 */
MLXSW_ITEM32(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_label4_label_id, 0x74, 8, 20);

/* extra_data_ceer_extra_fields_mpls_mpls_label4_ttl
 * Access: RO
 */
MLXSW_ITEM8(reg, ceer, extra_data_ceer_extra_fields_mpls_mpls_label4_ttl, 0x77, 0, 8);

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
MLXSW_ITEM16(reg, pmtdb, port_num1, 0x4, 0, 10);

/* port_num2
 * Access: RO
 */
MLXSW_ITEM16(reg, pmtdb, port_num2, 0x6, 0, 10);

/* port_num3
 * Access: RO
 */
MLXSW_ITEM16(reg, pmtdb, port_num3, 0x8, 0, 10);

/* port_num4
 * Access: RO
 */
MLXSW_ITEM16(reg, pmtdb, port_num4, 0xa, 0, 10);

/* port_num5
 * Access: RO
 */
MLXSW_ITEM16(reg, pmtdb, port_num5, 0xc, 0, 10);

/* port_num6
 * Access: RO
 */
MLXSW_ITEM16(reg, pmtdb, port_num6, 0xe, 0, 10);

/* port_num7
 * Access: RO
 */
MLXSW_ITEM16(reg, pmtdb, port_num7, 0x10, 0, 10);

/* port_num8
 * Access: RO
 */
MLXSW_ITEM16(reg, pmtdb, port_num8, 0x12, 0, 10);

/* ibfmrc
 * ------
 *
 */
/* attr_id_en
 * Access: RW
 */
MLXSW_ITEM32(reg, ibfmrc, attr_id_en, 0x0, 0, 32);

/* meccc
 * -----
 *
 */
/* device_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, meccc, device_index, 0x1, 0, 8);

/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, meccc, slot_index, 0x3, 0, 4);

/* clr
 * Access: OP
 */
MLXSW_ITEM8(reg, meccc, clr, 0x7, 0, 1);

/* ecc_crt_cnt
 * Access: RO
 */
MLXSW_ITEM32(reg, meccc, ecc_crt_cnt, 0xc, 0, 32);

/* ecc_ucrt_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, meccc, ecc_ucrt_cnt, 0x13, 0, 8);

/* utce
 * ----
 *
 */
/* uengine
 * Access: INDEX
 */
MLXSW_ITEM16(reg, utce, uengine, 0x0, 0, 16);

/* offset
 * Access: INDEX
 */
MLXSW_ITEM16(reg, utce, offset, 0x2, 0, 16);

/* oper
 * Access: OP
 */
MLXSW_ITEM8(reg, utce, oper, 0x4, 0, 3);

/* lk
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, lk, 0x5, 1, 1);

/* v
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, v, 0x5, 0, 1);

/* region_id
 * Access: RW
 */
MLXSW_ITEM16(reg, utce, region_id, 0x6, 0, 16);

/* sec_key_blocks
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, utce, sec_key_blocks, 0x8, 56);

/* mask
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, utce, mask, 0x40, 56);

/* action_utce_first_lookup_forwarding
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, action_utce_first_lookup_forwarding, 0x78, 0, 2);

/* action_utce_first_lookup_to_utrap
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, action_utce_first_lookup_to_utrap, 0x79, 0, 2);

/* action_utce_first_lookup_ucheck_id
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, action_utce_first_lookup_ucheck_id, 0x7b, 0, 8);

/* action_utce_first_lookup_validate_frames
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, action_utce_first_lookup_validate_frames, 0x7c, 4, 2);

/* action_utce_first_lookup_anchor_sec_tag_type
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, action_utce_first_lookup_anchor_sec_tag_type, 0x7c, 0, 2);

/* action_utce_first_lookup_encr_clear_tag
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, action_utce_first_lookup_encr_clear_tag, 0x7d, 0, 2);

/* action_utce_first_lookup_secy
 * Access: RW
 */
MLXSW_ITEM16(reg, utce, action_utce_first_lookup_secy, 0x7e, 0, 16);

/* action_utce_first_lookup_utcam_counter_en
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, action_utce_first_lookup_utcam_counter_en, 0x82, 0, 1);

/* action_utce_first_lookup_utcam_counter_idx
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, action_utce_first_lookup_utcam_counter_idx, 0x83, 0, 8);

/* action_utce_second_lookup_forwarding
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, action_utce_second_lookup_forwarding, 0x78, 0, 2);

/* action_utce_second_lookup_to_utrap
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, action_utce_second_lookup_to_utrap, 0x79, 0, 2);

/* action_utce_second_lookup_ucheck_id
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, action_utce_second_lookup_ucheck_id, 0x7b, 0, 8);

/* action_utce_second_lookup_sadb_entry_ptr
 * Access: RW
 */
MLXSW_ITEM16(reg, utce, action_utce_second_lookup_sadb_entry_ptr, 0x7e, 0, 16);

/* action_utce_second_lookup_utcam_counter_en
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, action_utce_second_lookup_utcam_counter_en, 0x82, 0, 1);

/* action_utce_second_lookup_utcam_counter_idx
 * Access: RW
 */
MLXSW_ITEM8(reg, utce, action_utce_second_lookup_utcam_counter_idx, 0x83, 0, 8);

/* tnifr_v2
 * --------
 *
 */
/* table_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tnifr_v2, table_id, 0x0, 4, 4);

/* tunnel_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, tnifr_v2, tunnel_port, 0x3, 0, 4);

/* port_filter
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, tnifr_v2, port_filter, 0x20, 0, 32, 4, 0, false);

/* port_filter_update_en
 * Access: OP
 */
MLXSW_ITEM32_INDEXED(reg, tnifr_v2, port_filter_update_en, 0xa0, 0, 32, 4, 0, false);

/* smid_v2
 * -------
 *
 */
/* swid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, smid_v2, swid, 0x0, 0, 8);

/* mid
 * Access: INDEX
 */
MLXSW_ITEM16(reg, smid_v2, mid, 0x2, 0, 16);

/* op
 * Access: OP
 */
MLXSW_ITEM8(reg, smid_v2, op, 0x7, 0, 4);

/* smpe_valid
 * Access: RW
 */
MLXSW_ITEM8(reg, smid_v2, smpe_valid, 0x9, 4, 1);

/* smpe
 * Access: RW
 */
MLXSW_ITEM16(reg, smid_v2, smpe, 0xa, 0, 16);

/* port
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, smid_v2, port, 0x20, 0, 32, 4, 0, false);

/* mask
 * Access: WO
 */
MLXSW_ITEM32_INDEXED(reg, smid_v2, mask, 0xa0, 0, 32, 4, 0, false);

/* qstct
 * -----
 *
 */
/* swid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qstct, swid, 0x0, 0, 8);

/* switch_prio
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qstct, switch_prio, 0x2, 0, 4);

/* utclass
 * Access: RW
 */
MLXSW_ITEM8(reg, qstct, utclass, 0x7, 0, 3);

/* mtclass
 * Access: RW
 */
MLXSW_ITEM8(reg, qstct, mtclass, 0xb, 0, 3);

/* pmcr
 * ----
 *
 */
/* cs_sel
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmcr, cs_sel, 0x0, 0, 2);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmcr, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pmcr, lp_msb, 0x2, 4, 2);

/* error_code_response
 * Access: RO
 */
MLXSW_ITEM8(reg, pmcr, error_code_response, 0x2, 0, 4);

/* db
 * Access: OP
 */
MLXSW_ITEM8(reg, pmcr, db, 0x3, 0, 1);

/* tx_disable_override_value
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, tx_disable_override_value, 0x4, 0, 2);

/* tx_disable_override_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pmcr, tx_disable_override_cap, 0x5, 2, 1);

/* tx_disable_override_cntl
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, tx_disable_override_cntl, 0x5, 0, 2);

/* cdr_override_value
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, cdr_override_value, 0x6, 0, 4);

/* cdr_override_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pmcr, cdr_override_cap, 0x7, 2, 2);

/* cdr_override_cntl
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, cdr_override_cntl, 0x7, 0, 2);

/* rx_los_override_admin
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, rx_los_override_admin, 0x8, 0, 2);

/* rx_los_override_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pmcr, rx_los_override_cap, 0x9, 2, 1);

/* rx_los_override_cntl
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, rx_los_override_cntl, 0x9, 0, 2);

/* rx_amp_override_value_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pmcr, rx_amp_override_value_cap, 0xa, 4, 4);

/* rx_amp_override_value
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, rx_amp_override_value, 0xa, 0, 4);

/* rx_amp_override_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pmcr, rx_amp_override_cap, 0xb, 2, 1);

/* rx_amp_override_cntl
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, rx_amp_override_cntl, 0xb, 0, 2);

/* rx_post_emp_override_value_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pmcr, rx_post_emp_override_value_cap, 0xc, 4, 4);

/* rx_post_emp_override_value
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, rx_post_emp_override_value, 0xc, 0, 4);

/* rx_post_emp_override_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pmcr, rx_post_emp_override_cap, 0xd, 2, 1);

/* rx_post_emp_override_cntl
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, rx_post_emp_override_cntl, 0xd, 0, 2);

/* rx_emp_override_value_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pmcr, rx_emp_override_value_cap, 0xe, 4, 4);

/* rx_emp_override_value
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, rx_emp_override_value, 0xe, 0, 4);

/* rx_emp_override_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pmcr, rx_emp_override_cap, 0xf, 2, 1);

/* rx_emp_override_cntl
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, rx_emp_override_cntl, 0xf, 0, 2);

/* tx_adaptive_override_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pmcr, tx_adaptive_override_cap, 0x10, 2, 1);

/* tx_adaptive_override_cntrl
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, tx_adaptive_override_cntrl, 0x10, 0, 2);

/* tx_adaptive_override_value
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, tx_adaptive_override_value, 0x11, 1, 1);

/* tx_equ_override_value_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pmcr, tx_equ_override_value_cap, 0x12, 4, 4);

/* tx_equ_override_value
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, tx_equ_override_value, 0x12, 0, 4);

/* tx_equ_override_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, pmcr, tx_equ_override_cap, 0x13, 2, 1);

/* tx_equ_override_cntl
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, tx_equ_override_cntl, 0x13, 0, 2);

/* rs_override_value
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, rs_override_value, 0x16, 0, 4);

/* rs_override_cntl
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, rs_override_cntl, 0x17, 0, 2);

/* ap_sel_override_value
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, ap_sel_override_value, 0x1a, 0, 4);

/* ap_sel_override_cntrl
 * Access: RW
 */
MLXSW_ITEM8(reg, pmcr, ap_sel_override_cntrl, 0x1b, 0, 2);

/* mtpps
 * -----
 *
 */
/* cap_number_of_pps_pins
 * Access: RO
 */
MLXSW_ITEM8(reg, mtpps, cap_number_of_pps_pins, 0x1, 0, 4);

/* cap_max_num_of_pps_in_pins
 * Access: RO
 */
MLXSW_ITEM8(reg, mtpps, cap_max_num_of_pps_in_pins, 0x2, 0, 4);

/* cap_max_num_of_pps_out_pins
 * Access: RO
 */
MLXSW_ITEM8(reg, mtpps, cap_max_num_of_pps_out_pins, 0x3, 0, 4);

/* cap_pin_3_mode
 * Access: RO
 */
MLXSW_ITEM8(reg, mtpps, cap_pin_3_mode, 0x8, 0, 4);

/* cap_pin_2_mode
 * Access: RO
 */
MLXSW_ITEM8(reg, mtpps, cap_pin_2_mode, 0x9, 0, 4);

/* cap_pin_1_mode
 * Access: RO
 */
MLXSW_ITEM8(reg, mtpps, cap_pin_1_mode, 0xa, 0, 4);

/* cap_pin_0_mode
 * Access: RO
 */
MLXSW_ITEM8(reg, mtpps, cap_pin_0_mode, 0xb, 0, 4);

/* cap_pin_7_mode
 * Access: RO
 */
MLXSW_ITEM8(reg, mtpps, cap_pin_7_mode, 0xc, 0, 4);

/* cap_pin_6_mode
 * Access: RO
 */
MLXSW_ITEM8(reg, mtpps, cap_pin_6_mode, 0xd, 0, 4);

/* cap_pin_5_mode
 * Access: RO
 */
MLXSW_ITEM8(reg, mtpps, cap_pin_5_mode, 0xe, 0, 4);

/* cap_pin_4_mode
 * Access: RO
 */
MLXSW_ITEM8(reg, mtpps, cap_pin_4_mode, 0xf, 0, 4);

/* field_select
 * Access: WO
 */
MLXSW_ITEM32(reg, mtpps, field_select, 0x10, 0, 32);

/* enable
 * Access: RW
 */
MLXSW_ITEM8(reg, mtpps, enable, 0x20, 7, 1);

/* utc_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, mtpps, utc_mode, 0x20, 6, 1);

/* pattern
 * Access: RW
 */
MLXSW_ITEM8(reg, mtpps, pattern, 0x21, 0, 4);

/* pin_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, mtpps, pin_mode, 0x22, 0, 4);

/* pin
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mtpps, pin, 0x23, 0, 8);

/* time_stamp
 * Access: RW
 */
MLXSW_ITEM64(reg, mtpps, time_stamp, 0x28, 0, 64);

/* out_pulse_duration
 * Access: RW
 */
MLXSW_ITEM16(reg, mtpps, out_pulse_duration, 0x30, 0, 16);

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

/* pifr_v2
 * -------
 *
 */
/* table_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pifr_v2, table_id, 0x0, 4, 4);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pifr_v2, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pifr_v2, lp_msb, 0x2, 4, 2);

/* port_filter
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, pifr_v2, port_filter, 0x20, 0, 32, 4, 0, false);

/* port_filter_update_en
 * Access: WO
 */
MLXSW_ITEM32_INDEXED(reg, pifr_v2, port_filter_update_en, 0xa0, 0, 32, 4, 0, false);

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

/* lp_gl
 * Access: OP
 */
MLXSW_ITEM8(reg, ppcnt, lp_gl, 0x4, 6, 1);

/* grp_profile
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppcnt, grp_profile, 0x7, 5, 3);

/* prio_tc
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppcnt, prio_tc, 0x7, 0, 5);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_frames_transmitted_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_frames_transmitted_ok_high, 0x8, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_frames_transmitted_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_frames_transmitted_ok_low, 0xc, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_frames_received_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_frames_received_ok_high, 0x10, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_frames_received_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_frames_received_ok_low, 0x14, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_frame_check_sequence_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_frame_check_sequence_errors_high, 0x18, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_frame_check_sequence_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_frame_check_sequence_errors_low, 0x1c, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_alignment_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_alignment_errors_high, 0x20, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_alignment_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_alignment_errors_low, 0x24, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_octets_transmitted_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_octets_transmitted_ok_high, 0x28, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_octets_transmitted_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_octets_transmitted_ok_low, 0x2c, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_octets_received_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_octets_received_ok_high, 0x30, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_octets_received_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_octets_received_ok_low, 0x34, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_xmitted_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_xmitted_ok_high, 0x38, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_xmitted_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_xmitted_ok_low, 0x3c, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_xmitted_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_xmitted_ok_high, 0x40, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_xmitted_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_xmitted_ok_low, 0x44, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_received_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_received_ok_high, 0x48, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_received_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_received_ok_low, 0x4c, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_received_ok_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_received_ok_high, 0x50, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_received_ok_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_received_ok_low, 0x54, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_in_range_length_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_in_range_length_errors_high, 0x58, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_in_range_length_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_in_range_length_errors_low, 0x5c, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_out_of_range_length_field_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_out_of_range_length_field_high, 0x60, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_out_of_range_length_field_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_out_of_range_length_field_low, 0x64, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_frame_too_long_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_frame_too_long_errors_high, 0x68, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_frame_too_long_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_frame_too_long_errors_low, 0x6c, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_symbol_error_during_carrier_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_symbol_error_during_carrier_high, 0x70, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_symbol_error_during_carrier_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_symbol_error_during_carrier_low, 0x74, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_transmitted_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_transmitted_high, 0x78, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_transmitted_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_transmitted_low, 0x7c, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_received_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_received_high, 0x80, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_received_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_received_low, 0x84, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_unsupported_opcodes_received_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_unsupported_opcodes_received_high, 0x88, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_unsupported_opcodes_received_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_unsupported_opcodes_received_low, 0x8c, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_received_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_received_high, 0x90, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_received_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_received_low, 0x94, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_transmitted_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_transmitted_high, 0x98, 0, 32);

/* counter_set_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_transmitted_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_transmitted_low, 0x9c, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_in_octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_in_octets_high, 0x8, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_in_octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_in_octets_low, 0xc, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_in_ucast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_in_ucast_pkts_high, 0x10, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_in_ucast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_in_ucast_pkts_low, 0x14, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_in_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_in_discards_high, 0x18, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_in_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_in_discards_low, 0x1c, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_in_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_in_errors_high, 0x20, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_in_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_in_errors_low, 0x24, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_in_unknown_protos_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_in_unknown_protos_high, 0x28, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_in_unknown_protos_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_in_unknown_protos_low, 0x2c, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_out_octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_out_octets_high, 0x30, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_out_octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_out_octets_low, 0x34, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_out_ucast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_out_ucast_pkts_high, 0x38, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_out_ucast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_out_ucast_pkts_low, 0x3c, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_out_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_out_discards_high, 0x40, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_out_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_out_discards_low, 0x44, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_out_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_out_errors_high, 0x48, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_out_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_out_errors_low, 0x4c, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_in_multicast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_in_multicast_pkts_high, 0x50, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_in_multicast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_in_multicast_pkts_low, 0x54, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_in_broadcast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_in_broadcast_pkts_high, 0x58, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_in_broadcast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_in_broadcast_pkts_low, 0x5c, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_out_multicast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_out_multicast_pkts_high, 0x60, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_out_multicast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_out_multicast_pkts_low, 0x64, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_out_broadcast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_out_broadcast_pkts_high, 0x68, 0, 32);

/* counter_set_eth_2863_cntrs_grp_data_layout_if_out_broadcast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2863_cntrs_grp_data_layout_if_out_broadcast_pkts_low, 0x6c, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_drop_events_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_drop_events_high, 0x8, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_drop_events_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_drop_events_low, 0xc, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_octets_high, 0x10, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_octets_low, 0x14, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts_high, 0x18, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts_low, 0x1c, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_broadcast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_broadcast_pkts_high, 0x20, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_broadcast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_broadcast_pkts_low, 0x24, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_multicast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_multicast_pkts_high, 0x28, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_multicast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_multicast_pkts_low, 0x2c, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_crc_align_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_crc_align_errors_high, 0x30, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_crc_align_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_crc_align_errors_low, 0x34, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_undersize_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_undersize_pkts_high, 0x38, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_undersize_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_undersize_pkts_low, 0x3c, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_oversize_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_oversize_pkts_high, 0x40, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_oversize_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_oversize_pkts_low, 0x44, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_fragments_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_fragments_high, 0x48, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_fragments_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_fragments_low, 0x4c, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_jabbers_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_jabbers_high, 0x50, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_jabbers_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_jabbers_low, 0x54, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_collisions_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_collisions_high, 0x58, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_collisions_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_collisions_low, 0x5c, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts64octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts64octets_high, 0x60, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts64octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts64octets_low, 0x64, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts65to127octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts65to127octets_high, 0x68, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts65to127octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts65to127octets_low, 0x6c, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts128to255octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts128to255octets_high, 0x70, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts128to255octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts128to255octets_low, 0x74, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts256to511octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts256to511octets_high, 0x78, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts256to511octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts256to511octets_low, 0x7c, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts512to1023octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts512to1023octets_high, 0x80, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts512to1023octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts512to1023octets_low, 0x84, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1024to1518octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1024to1518octets_high, 0x88, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1024to1518octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1024to1518octets_low, 0x8c, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1519to2047octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1519to2047octets_high, 0x90, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1519to2047octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1519to2047octets_low, 0x94, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts2048to4095octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts2048to4095octets_high, 0x98, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts2048to4095octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts2048to4095octets_low, 0x9c, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts4096to8191octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts4096to8191octets_high, 0xa0, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts4096to8191octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts4096to8191octets_low, 0xa4, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts8192to10239octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts8192to10239octets_high, 0xa8, 0, 32);

/* counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts8192to10239octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts8192to10239octets_low, 0xac, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_high, 0x8, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_low, 0xc, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_high, 0x10, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_low, 0x14, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_high, 0x18, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_low, 0x1c, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_high, 0x20, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_low, 0x24, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_high, 0x28, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_low, 0x2c, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_high, 0x30, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_low, 0x34, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_high, 0x38, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_low, 0x3c, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_high, 0x40, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_low, 0x44, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_high, 0x48, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_low, 0x4c, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_high, 0x50, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_low, 0x54, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_high, 0x58, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_low, 0x5c, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_high, 0x60, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_low, 0x64, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_high, 0x68, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_low, 0x6c, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_high, 0x70, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_low, 0x74, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_high, 0x78, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_low, 0x7c, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_high
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_high, 0x80, 0, 32);

/* counter_set_eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_low
 * Access: RW
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_low, 0x84, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_port_transmit_wait_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_port_transmit_wait_high, 0x8, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_port_transmit_wait_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_port_transmit_wait_low, 0xc, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_ecn_marked_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_ecn_marked_high, 0x10, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_ecn_marked_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_ecn_marked_low, 0x14, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_no_buffer_discard_mc_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_no_buffer_discard_mc_high, 0x18, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_no_buffer_discard_mc_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_no_buffer_discard_mc_low, 0x1c, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_rx_ebp_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_rx_ebp_high, 0x20, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_rx_ebp_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_rx_ebp_low, 0x24, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_ebp_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_ebp_high, 0x28, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_ebp_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_ebp_low, 0x2c, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_rx_buffer_almost_full_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_rx_buffer_almost_full_high, 0x30, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_rx_buffer_almost_full_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_rx_buffer_almost_full_low, 0x34, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_rx_buffer_full_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_rx_buffer_full_high, 0x38, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_rx_buffer_full_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_rx_buffer_full_low, 0x3c, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_rx_icrc_encapsulated_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_rx_icrc_encapsulated_high, 0x40, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_rx_icrc_encapsulated_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_rx_icrc_encapsulated_low, 0x44, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts64octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts64octets_high, 0x58, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts64octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts64octets_low, 0x5c, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts65to127octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts65to127octets_high, 0x60, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts65to127octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts65to127octets_low, 0x64, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts128to255octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts128to255octets_high, 0x68, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts128to255octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts128to255octets_low, 0x6c, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts256to511octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts256to511octets_high, 0x70, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts256to511octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts256to511octets_low, 0x74, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts512to1023octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts512to1023octets_high, 0x78, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts512to1023octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts512to1023octets_low, 0x7c, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1024to1518octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1024to1518octets_high, 0x80, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1024to1518octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1024to1518octets_low, 0x84, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1519to2047octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1519to2047octets_high, 0x88, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1519to2047octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1519to2047octets_low, 0x8c, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts2048to4095octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts2048to4095octets_high, 0x90, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts2048to4095octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts2048to4095octets_low, 0x94, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts4096to8191octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts4096to8191octets_high, 0x98, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts4096to8191octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts4096to8191octets_low, 0x9c, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts8192to10239octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts8192to10239octets_high, 0xa0, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts8192to10239octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts8192to10239octets_low, 0xa4, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_ece_marked_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_ece_marked_high, 0xa8, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_ece_marked_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_ece_marked_low, 0xac, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_int_cksm_err_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_int_cksm_err_high, 0xb0, 0, 32);

/* counter_set_eth_extended_cntrs_grp_data_layout_tx_int_cksm_err_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_extended_cntrs_grp_data_layout_tx_int_cksm_err_low, 0xb4, 0, 32);

/* counter_set_eth_discard_cntrs_grp_ingress_general_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_ingress_general_high, 0x8, 0, 32);

/* counter_set_eth_discard_cntrs_grp_ingress_general_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_ingress_general_low, 0xc, 0, 32);

/* counter_set_eth_discard_cntrs_grp_ingress_policy_engine_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_ingress_policy_engine_high, 0x10, 0, 32);

/* counter_set_eth_discard_cntrs_grp_ingress_policy_engine_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_ingress_policy_engine_low, 0x14, 0, 32);

/* counter_set_eth_discard_cntrs_grp_ingress_vlan_membership_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_ingress_vlan_membership_high, 0x18, 0, 32);

/* counter_set_eth_discard_cntrs_grp_ingress_vlan_membership_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_ingress_vlan_membership_low, 0x1c, 0, 32);

/* counter_set_eth_discard_cntrs_grp_ingress_tag_frame_type_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_ingress_tag_frame_type_high, 0x20, 0, 32);

/* counter_set_eth_discard_cntrs_grp_ingress_tag_frame_type_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_ingress_tag_frame_type_low, 0x24, 0, 32);

/* counter_set_eth_discard_cntrs_grp_egress_vlan_membership_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_egress_vlan_membership_high, 0x28, 0, 32);

/* counter_set_eth_discard_cntrs_grp_egress_vlan_membership_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_egress_vlan_membership_low, 0x2c, 0, 32);

/* counter_set_eth_discard_cntrs_grp_loopback_filter_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_loopback_filter_high, 0x30, 0, 32);

/* counter_set_eth_discard_cntrs_grp_loopback_filter_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_loopback_filter_low, 0x34, 0, 32);

/* counter_set_eth_discard_cntrs_grp_egress_general_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_egress_general_high, 0x38, 0, 32);

/* counter_set_eth_discard_cntrs_grp_egress_general_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_egress_general_low, 0x3c, 0, 32);

/* counter_set_eth_discard_cntrs_grp_egress_hoq_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_egress_hoq_high, 0x48, 0, 32);

/* counter_set_eth_discard_cntrs_grp_egress_hoq_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_egress_hoq_low, 0x4c, 0, 32);

/* counter_set_eth_discard_cntrs_grp_port_isolation_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_port_isolation_high, 0x50, 0, 32);

/* counter_set_eth_discard_cntrs_grp_port_isolation_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_port_isolation_low, 0x54, 0, 32);

/* counter_set_eth_discard_cntrs_grp_egress_policy_engine_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_egress_policy_engine_high, 0x58, 0, 32);

/* counter_set_eth_discard_cntrs_grp_egress_policy_engine_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_egress_policy_engine_low, 0x5c, 0, 32);

/* counter_set_eth_discard_cntrs_grp_ingress_tx_link_down_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_ingress_tx_link_down_high, 0x60, 0, 32);

/* counter_set_eth_discard_cntrs_grp_ingress_tx_link_down_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_ingress_tx_link_down_low, 0x64, 0, 32);

/* counter_set_eth_discard_cntrs_grp_egress_stp_filter_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_egress_stp_filter_high, 0x68, 0, 32);

/* counter_set_eth_discard_cntrs_grp_egress_stp_filter_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_egress_stp_filter_low, 0x6c, 0, 32);

/* counter_set_eth_discard_cntrs_grp_egress_hoq_stall_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_egress_hoq_stall_high, 0x70, 0, 32);

/* counter_set_eth_discard_cntrs_grp_egress_hoq_stall_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_egress_hoq_stall_low, 0x74, 0, 32);

/* counter_set_eth_discard_cntrs_grp_egress_sll_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_egress_sll_high, 0x78, 0, 32);

/* counter_set_eth_discard_cntrs_grp_egress_sll_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_egress_sll_low, 0x7c, 0, 32);

/* counter_set_eth_discard_cntrs_grp_ingress_discard_all_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_ingress_discard_all_high, 0x80, 0, 32);

/* counter_set_eth_discard_cntrs_grp_ingress_discard_all_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_discard_cntrs_grp_ingress_discard_all_low, 0x84, 0, 32);

/* counter_set_link_level_retrans_cntr_grp_data_llr_rx_cells_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_link_level_retrans_cntr_grp_data_llr_rx_cells_high, 0x8, 0, 32);

/* counter_set_link_level_retrans_cntr_grp_data_llr_rx_cells_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_link_level_retrans_cntr_grp_data_llr_rx_cells_low, 0xc, 0, 32);

/* counter_set_link_level_retrans_cntr_grp_data_llr_rx_error_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_link_level_retrans_cntr_grp_data_llr_rx_error_high, 0x10, 0, 32);

/* counter_set_link_level_retrans_cntr_grp_data_llr_rx_error_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_link_level_retrans_cntr_grp_data_llr_rx_error_low, 0x14, 0, 32);

/* counter_set_link_level_retrans_cntr_grp_data_llr_rx_crc_error_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_link_level_retrans_cntr_grp_data_llr_rx_crc_error_high, 0x18, 0, 32);

/* counter_set_link_level_retrans_cntr_grp_data_llr_rx_crc_error_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_link_level_retrans_cntr_grp_data_llr_rx_crc_error_low, 0x1c, 0, 32);

/* counter_set_link_level_retrans_cntr_grp_data_llr_tx_cells_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_link_level_retrans_cntr_grp_data_llr_tx_cells_high, 0x20, 0, 32);

/* counter_set_link_level_retrans_cntr_grp_data_llr_tx_cells_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_link_level_retrans_cntr_grp_data_llr_tx_cells_low, 0x24, 0, 32);

/* counter_set_link_level_retrans_cntr_grp_data_llr_tx_ret_cells_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_link_level_retrans_cntr_grp_data_llr_tx_ret_cells_high, 0x28, 0, 32);

/* counter_set_link_level_retrans_cntr_grp_data_llr_tx_ret_cells_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_link_level_retrans_cntr_grp_data_llr_tx_ret_cells_low, 0x2c, 0, 32);

/* counter_set_link_level_retrans_cntr_grp_data_llr_tx_ret_events_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_link_level_retrans_cntr_grp_data_llr_tx_ret_events_high, 0x30, 0, 32);

/* counter_set_link_level_retrans_cntr_grp_data_llr_tx_ret_events_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_link_level_retrans_cntr_grp_data_llr_tx_ret_events_low, 0x34, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_octets_high, 0x8, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_octets_low, 0xc, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_uc_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_uc_frames_high, 0x10, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_uc_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_uc_frames_low, 0x14, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_mc_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_mc_frames_high, 0x18, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_mc_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_mc_frames_low, 0x1c, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_bc_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_bc_frames_high, 0x20, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_bc_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_bc_frames_low, 0x24, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_frames_high, 0x28, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_frames_low, 0x2c, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_tx_octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_tx_octets_high, 0x30, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_tx_octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_tx_octets_low, 0x34, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_tx_uc_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_tx_uc_frames_high, 0x38, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_tx_uc_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_tx_uc_frames_low, 0x3c, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_tx_mc_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_tx_mc_frames_high, 0x40, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_tx_mc_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_tx_mc_frames_low, 0x44, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_tx_bc_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_tx_bc_frames_high, 0x48, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_tx_bc_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_tx_bc_frames_low, 0x4c, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_tx_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_tx_frames_high, 0x50, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_tx_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_tx_frames_low, 0x54, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_pause_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_pause_high, 0x58, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_pause_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_pause_low, 0x5c, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_pause_duration_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_pause_duration_high, 0x60, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_pause_duration_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_pause_duration_low, 0x64, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_tx_pause_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_tx_pause_high, 0x68, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_tx_pause_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_tx_pause_low, 0x6c, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_tx_pause_duration_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_tx_pause_duration_high, 0x70, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_tx_pause_duration_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_tx_pause_duration_low, 0x74, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_pause_transition_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_pause_transition_high, 0x78, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_pause_transition_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_pause_transition_low, 0x7c, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_discards_high, 0x80, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_rx_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_rx_discards_low, 0x84, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_device_stall_minor_watermark_cnt_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_device_stall_minor_watermark_cnt_high, 0x88, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_device_stall_minor_watermark_cnt_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_device_stall_minor_watermark_cnt_low, 0x8c, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_device_stall_critical_watermark_cnt_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_device_stall_critical_watermark_cnt_high, 0x90, 0, 32);

/* counter_set_eth_per_prio_grp_data_layout_device_stall_critical_watermark_cnt_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_prio_grp_data_layout_device_stall_critical_watermark_cnt_low, 0x94, 0, 32);

/* counter_set_eth_per_traffic_class_layout_transmit_queue_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_traffic_class_layout_transmit_queue_high, 0x8, 0, 32);

/* counter_set_eth_per_traffic_class_layout_transmit_queue_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_traffic_class_layout_transmit_queue_low, 0xc, 0, 32);

/* counter_set_eth_per_traffic_class_layout_no_buffer_discard_uc_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_traffic_class_layout_no_buffer_discard_uc_high, 0x10, 0, 32);

/* counter_set_eth_per_traffic_class_layout_no_buffer_discard_uc_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_traffic_class_layout_no_buffer_discard_uc_low, 0x14, 0, 32);

/* counter_set_phys_layer_cntrs_time_since_last_clear_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_time_since_last_clear_high, 0x8, 0, 32);

/* counter_set_phys_layer_cntrs_time_since_last_clear_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_time_since_last_clear_low, 0xc, 0, 32);

/* counter_set_phys_layer_cntrs_symbol_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_symbol_errors_high, 0x10, 0, 32);

/* counter_set_phys_layer_cntrs_symbol_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_symbol_errors_low, 0x14, 0, 32);

/* counter_set_phys_layer_cntrs_sync_headers_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_sync_headers_errors_high, 0x18, 0, 32);

/* counter_set_phys_layer_cntrs_sync_headers_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_sync_headers_errors_low, 0x1c, 0, 32);

/* counter_set_phys_layer_cntrs_edpl_bip_errors_lane0_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_edpl_bip_errors_lane0_high, 0x20, 0, 32);

/* counter_set_phys_layer_cntrs_edpl_bip_errors_lane0_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_edpl_bip_errors_lane0_low, 0x24, 0, 32);

/* counter_set_phys_layer_cntrs_edpl_bip_errors_lane1_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_edpl_bip_errors_lane1_high, 0x28, 0, 32);

/* counter_set_phys_layer_cntrs_edpl_bip_errors_lane1_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_edpl_bip_errors_lane1_low, 0x2c, 0, 32);

/* counter_set_phys_layer_cntrs_edpl_bip_errors_lane2_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_edpl_bip_errors_lane2_high, 0x30, 0, 32);

/* counter_set_phys_layer_cntrs_edpl_bip_errors_lane2_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_edpl_bip_errors_lane2_low, 0x34, 0, 32);

/* counter_set_phys_layer_cntrs_edpl_bip_errors_lane3_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_edpl_bip_errors_lane3_high, 0x38, 0, 32);

/* counter_set_phys_layer_cntrs_edpl_bip_errors_lane3_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_edpl_bip_errors_lane3_low, 0x3c, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane0_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane0_high, 0x40, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane0_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane0_low, 0x44, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane1_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane1_high, 0x48, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane1_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane1_low, 0x4c, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane2_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane2_high, 0x50, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane2_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane2_low, 0x54, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane3_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane3_high, 0x58, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane3_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane3_low, 0x5c, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane0_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane0_high, 0x60, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane0_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane0_low, 0x64, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane1_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane1_high, 0x68, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane1_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane1_low, 0x6c, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane2_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane2_high, 0x70, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane2_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane2_low, 0x74, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane3_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane3_high, 0x78, 0, 32);

/* counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane3_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane3_low, 0x7c, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_blocks_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_blocks_high, 0x80, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_blocks_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_blocks_low, 0x84, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_uncorrectable_blocks_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_uncorrectable_blocks_high, 0x88, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_uncorrectable_blocks_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_uncorrectable_blocks_low, 0x8c, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_no_errors_blocks_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_no_errors_blocks_high, 0x90, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_no_errors_blocks_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_no_errors_blocks_low, 0x94, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_single_error_blocks_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_single_error_blocks_high, 0x98, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_single_error_blocks_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_single_error_blocks_low, 0x9c, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_total_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_total_high, 0xa0, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_total_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_total_low, 0xa4, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane0_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane0_high, 0xa8, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane0_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane0_low, 0xac, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane1_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane1_high, 0xb0, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane1_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane1_low, 0xb4, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane2_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane2_high, 0xb8, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane2_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane2_low, 0xbc, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane3_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane3_high, 0xc0, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane3_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane3_low, 0xc4, 0, 32);

/* counter_set_phys_layer_cntrs_link_down_events
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_link_down_events, 0xc8, 0, 32);

/* counter_set_phys_layer_cntrs_successful_recovery_events
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_successful_recovery_events, 0xcc, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane4_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane4_high, 0xd0, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane4_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane4_low, 0xd4, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane5_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane5_high, 0xd8, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane5_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane5_low, 0xdc, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane6_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane6_high, 0xe0, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane6_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane6_low, 0xe4, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane7_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane7_high, 0xe8, 0, 32);

/* counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane7_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane7_low, 0xec, 0, 32);

/* counter_set_eth_per_traffic_class_cong_layout_wred_discard_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_traffic_class_cong_layout_wred_discard_high, 0x8, 0, 32);

/* counter_set_eth_per_traffic_class_cong_layout_wred_discard_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_traffic_class_cong_layout_wred_discard_low, 0xc, 0, 32);

/* counter_set_eth_per_traffic_class_cong_layout_ecn_marked_tc_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_traffic_class_cong_layout_ecn_marked_tc_high, 0x10, 0, 32);

/* counter_set_eth_per_traffic_class_cong_layout_ecn_marked_tc_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_traffic_class_cong_layout_ecn_marked_tc_low, 0x14, 0, 32);

/* counter_set_eth_per_receive_buffer_grp_rx_no_buffer_discard_uc_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_receive_buffer_grp_rx_no_buffer_discard_uc_high, 0x8, 0, 32);

/* counter_set_eth_per_receive_buffer_grp_rx_no_buffer_discard_uc_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_per_receive_buffer_grp_rx_no_buffer_discard_uc_low, 0xc, 0, 32);

/* counter_set_phys_layer_stat_cntrs_time_since_last_clear_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_time_since_last_clear_high, 0x8, 0, 32);

/* counter_set_phys_layer_stat_cntrs_time_since_last_clear_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_time_since_last_clear_low, 0xc, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_received_bits_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_received_bits_high, 0x10, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_received_bits_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_received_bits_low, 0x14, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_symbol_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_symbol_errors_high, 0x18, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_symbol_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_symbol_errors_low, 0x1c, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_corrected_bits_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_corrected_bits_high, 0x20, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_corrected_bits_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_corrected_bits_low, 0x24, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane0_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane0_high, 0x28, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane0_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane0_low, 0x2c, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane1_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane1_high, 0x30, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane1_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane1_low, 0x34, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane2_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane2_high, 0x38, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane2_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane2_low, 0x3c, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane3_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane3_high, 0x40, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane3_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane3_low, 0x44, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane4_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane4_high, 0x48, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane4_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane4_low, 0x4c, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane5_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane5_high, 0x50, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane5_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane5_low, 0x54, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane6_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane6_high, 0x58, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane6_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane6_low, 0x5c, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane7_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane7_high, 0x60, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane7_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane7_low, 0x64, 0, 32);

/* counter_set_phys_layer_stat_cntrs_raw_ber_magnitude
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_magnitude, 0x6a, 0, 8);

/* counter_set_phys_layer_stat_cntrs_raw_ber_coef
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_coef, 0x6b, 0, 4);

/* counter_set_phys_layer_stat_cntrs_effective_ber_magnitude
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_effective_ber_magnitude, 0x6e, 0, 8);

/* counter_set_phys_layer_stat_cntrs_effective_ber_coef
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_effective_ber_coef, 0x6f, 0, 4);

/* counter_set_phys_layer_stat_cntrs_symbol_ber_magnitude
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_symbol_ber_magnitude, 0x72, 0, 8);

/* counter_set_phys_layer_stat_cntrs_symbol_fec_ber_coef
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_symbol_fec_ber_coef, 0x73, 0, 4);

/* counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane0
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane0, 0x74, 0, 8);

/* counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane0
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane0, 0x75, 0, 4);

/* counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane1
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane1, 0x76, 0, 8);

/* counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane1
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane1, 0x77, 0, 4);

/* counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane2
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane2, 0x78, 0, 8);

/* counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane2
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane2, 0x79, 0, 4);

/* counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane3
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane3, 0x7a, 0, 8);

/* counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane3
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane3, 0x7b, 0, 4);

/* counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane4
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane4, 0x7c, 0, 8);

/* counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane4
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane4, 0x7d, 0, 4);

/* counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane5
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane5, 0x7e, 0, 8);

/* counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane5
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane5, 0x7f, 0, 4);

/* counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane6
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane6, 0x80, 0, 8);

/* counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane6
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane6, 0x81, 0, 4);

/* counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane7
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane7, 0x82, 0, 8);

/* counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane7
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane7, 0x83, 0, 4);

/* counter_set_phys_layer_stat_cntrs_phy_effective_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_effective_errors_high, 0x84, 0, 32);

/* counter_set_phys_layer_stat_cntrs_phy_effective_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_phys_layer_stat_cntrs_phy_effective_errors_low, 0x88, 0, 32);

/* counter_set_eth_oob_port_cntrs_if_in_ucast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_if_in_ucast_pkts_high, 0x8, 0, 32);

/* counter_set_eth_oob_port_cntrs_if_in_ucast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_if_in_ucast_pkts_low, 0xc, 0, 32);

/* counter_set_eth_oob_port_cntrs_if_in_octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_if_in_octets_high, 0x10, 0, 32);

/* counter_set_eth_oob_port_cntrs_if_in_octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_if_in_octets_low, 0x14, 0, 32);

/* counter_set_eth_oob_port_cntrs_if_in_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_if_in_discards_high, 0x18, 0, 32);

/* counter_set_eth_oob_port_cntrs_if_in_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_if_in_discards_low, 0x1c, 0, 32);

/* counter_set_eth_oob_port_cntrs_if_in_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_if_in_errors_high, 0x20, 0, 32);

/* counter_set_eth_oob_port_cntrs_if_in_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_if_in_errors_low, 0x24, 0, 32);

/* counter_set_eth_oob_port_cntrs_ether_stats_crc_align_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_ether_stats_crc_align_errors_high, 0x28, 0, 32);

/* counter_set_eth_oob_port_cntrs_ether_stats_crc_align_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_ether_stats_crc_align_errors_low, 0x2c, 0, 32);

/* counter_set_eth_oob_port_cntrs_ether_stats_undersize_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_ether_stats_undersize_pkts_high, 0x30, 0, 32);

/* counter_set_eth_oob_port_cntrs_ether_stats_undersize_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_ether_stats_undersize_pkts_low, 0x34, 0, 32);

/* counter_set_eth_oob_port_cntrs_ether_stats_oversize_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_ether_stats_oversize_pkts_high, 0x38, 0, 32);

/* counter_set_eth_oob_port_cntrs_ether_stats_oversize_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_ether_stats_oversize_pkts_low, 0x3c, 0, 32);

/* counter_set_eth_oob_port_cntrs_dot3stats_symbol_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_dot3stats_symbol_errors_high, 0x40, 0, 32);

/* counter_set_eth_oob_port_cntrs_dot3stats_symbol_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_dot3stats_symbol_errors_low, 0x44, 0, 32);

/* counter_set_eth_oob_port_cntrs_dot3in_pause_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_dot3in_pause_frames_high, 0x48, 0, 32);

/* counter_set_eth_oob_port_cntrs_dot3in_pause_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_dot3in_pause_frames_low, 0x4c, 0, 32);

/* counter_set_eth_oob_port_cntrs_dot3control_in_unknown_opcodes_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_dot3control_in_unknown_opcodes_high, 0x50, 0, 32);

/* counter_set_eth_oob_port_cntrs_dot3control_in_unknown_opcodes_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_dot3control_in_unknown_opcodes_low, 0x54, 0, 32);

/* counter_set_eth_oob_port_cntrs_if_out_ucast_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_if_out_ucast_pkts_high, 0x58, 0, 32);

/* counter_set_eth_oob_port_cntrs_if_out_ucast_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_if_out_ucast_pkts_low, 0x5c, 0, 32);

/* counter_set_eth_oob_port_cntrs_if_out_octets_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_if_out_octets_high, 0x60, 0, 32);

/* counter_set_eth_oob_port_cntrs_if_out_octets_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_if_out_octets_low, 0x64, 0, 32);

/* counter_set_eth_oob_port_cntrs_dot3out_pause_frames_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_dot3out_pause_frames_high, 0x68, 0, 32);

/* counter_set_eth_oob_port_cntrs_dot3out_pause_frames_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_dot3out_pause_frames_low, 0x6c, 0, 32);

/* counter_set_eth_oob_port_cntrs_if_out_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_if_out_errors_high, 0x70, 0, 32);

/* counter_set_eth_oob_port_cntrs_if_out_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_if_out_errors_low, 0x74, 0, 32);

/* counter_set_eth_oob_port_cntrs_phy_time_since_last_clear_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_phy_time_since_last_clear_high, 0x78, 0, 32);

/* counter_set_eth_oob_port_cntrs_phy_time_since_last_clear_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_phy_time_since_last_clear_low, 0x7c, 0, 32);

/* counter_set_eth_oob_port_cntrs_phy_received_bits_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_phy_received_bits_high, 0x80, 0, 32);

/* counter_set_eth_oob_port_cntrs_phy_received_bits_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_phy_received_bits_low, 0x84, 0, 32);

/* counter_set_eth_oob_port_cntrs_phy_symbol_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_phy_symbol_errors_high, 0x88, 0, 32);

/* counter_set_eth_oob_port_cntrs_phy_symbol_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_eth_oob_port_cntrs_phy_symbol_errors_low, 0x8c, 0, 32);

/* counter_set_ib_portcntrs_attribute_grp_data_symbol_error_counter
 * Access: RO
 */
MLXSW_ITEM16(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_symbol_error_counter, 0x8, 0, 16);

/* counter_set_ib_portcntrs_attribute_grp_data_link_error_recovery_counter
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_link_error_recovery_counter, 0xa, 0, 8);

/* counter_set_ib_portcntrs_attribute_grp_data_link_downed_counter
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_link_downed_counter, 0xb, 0, 8);

/* counter_set_ib_portcntrs_attribute_grp_data_port_rcv_errors
 * Access: RO
 */
MLXSW_ITEM16(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_port_rcv_errors, 0xc, 0, 16);

/* counter_set_ib_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors
 * Access: RO
 */
MLXSW_ITEM16(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors, 0xe, 0, 16);

/* counter_set_ib_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors
 * Access: RO
 */
MLXSW_ITEM16(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors, 0x10, 0, 16);

/* counter_set_ib_portcntrs_attribute_grp_data_port_xmit_discards
 * Access: RO
 */
MLXSW_ITEM16(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_port_xmit_discards, 0x12, 0, 16);

/* counter_set_ib_portcntrs_attribute_grp_data_port_xmit_constraint_errors
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_port_xmit_constraint_errors, 0x14, 0, 8);

/* counter_set_ib_portcntrs_attribute_grp_data_port_rcv_constraint_errors
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_port_rcv_constraint_errors, 0x15, 0, 8);

/* counter_set_ib_portcntrs_attribute_grp_data_local_link_integrity_errors
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_local_link_integrity_errors, 0x17, 4, 4);

/* counter_set_ib_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors
 * Access: RO
 */
MLXSW_ITEM8(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors, 0x17, 0, 4);

/* counter_set_ib_portcntrs_attribute_grp_data_vl_15_dropped
 * Access: RO
 */
MLXSW_ITEM16(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_vl_15_dropped, 0x1a, 0, 16);

/* counter_set_ib_portcntrs_attribute_grp_data_port_xmit_data
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_port_xmit_data, 0x1c, 0, 32);

/* counter_set_ib_portcntrs_attribute_grp_data_port_rcv_data
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_port_rcv_data, 0x20, 0, 32);

/* counter_set_ib_portcntrs_attribute_grp_data_port_xmit_pkts
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_port_xmit_pkts, 0x24, 0, 32);

/* counter_set_ib_portcntrs_attribute_grp_data_port_rcv_pkts
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_port_rcv_pkts, 0x28, 0, 32);

/* counter_set_ib_portcntrs_attribute_grp_data_port_xmit_wait
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_portcntrs_attribute_grp_data_port_xmit_wait, 0x2c, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_symbol_error_counter_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_symbol_error_counter_high, 0x8, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_symbol_error_counter_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_symbol_error_counter_low, 0xc, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_link_error_recovery_counter_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_link_error_recovery_counter_high, 0x10, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_link_error_recovery_counter_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_link_error_recovery_counter_low, 0x14, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_link_downed_counter_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_link_downed_counter_high, 0x18, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_link_downed_counter_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_link_downed_counter_low, 0x1c, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_errors_high, 0x20, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_errors_low, 0x24, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_high, 0x28, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_low, 0x2c, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_high, 0x30, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_low, 0x34, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_discards_high, 0x38, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_discards_low, 0x3c, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_constraint_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_constraint_errors_high, 0x40, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_constraint_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_constraint_errors_low, 0x44, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_constraint_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_constraint_errors_high, 0x48, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_constraint_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_constraint_errors_low, 0x4c, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_local_link_integrity_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_local_link_integrity_errors_high, 0x50, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_local_link_integrity_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_local_link_integrity_errors_low, 0x54, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_high, 0x58, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_low, 0x5c, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_vl_15_dropped_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_vl_15_dropped_high, 0x60, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_vl_15_dropped_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_vl_15_dropped_low, 0x64, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_data_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_data_high, 0x68, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_data_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_data_low, 0x6c, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_data_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_data_high, 0x70, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_data_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_data_low, 0x74, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_pkts_high, 0x78, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_pkts_low, 0x7c, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_pkts_high, 0x80, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_pkts_low, 0x84, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_wait_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_wait_high, 0x88, 0, 32);

/* counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_wait_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_wait_low, 0x8c, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_rcv_codes_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_rcv_codes_high, 0x8, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_rcv_codes_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_rcv_codes_low, 0xc, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_rcv_code_err_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_rcv_code_err_high, 0x10, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_rcv_code_err_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_rcv_code_err_low, 0x14, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_rcv_uncorrectable_code_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_rcv_uncorrectable_code_high, 0x18, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_rcv_uncorrectable_code_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_rcv_uncorrectable_code_low, 0x1c, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_xmit_codes_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_xmit_codes_high, 0x20, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_xmit_codes_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_xmit_codes_low, 0x24, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_xmit_retry_codes_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_xmit_retry_codes_high, 0x28, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_xmit_retry_codes_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_xmit_retry_codes_low, 0x2c, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_xmit_retry_events_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_xmit_retry_events_high, 0x30, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_xmit_retry_events_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_xmit_retry_events_low, 0x34, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_sync_events_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_sync_events_high, 0x38, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_sync_events_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_sync_events_low, 0x3c, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_codes_loss_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_codes_loss_high, 0x40, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_codes_loss_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_codes_loss_low, 0x44, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_xmit_retry_events_within_t_sec_max_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_xmit_retry_events_within_t_sec_max_high, 0x48, 0, 32);

/* counter_set_ppcnt_plr_counters_plr_xmit_retry_events_within_t_sec_max_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_plr_counters_plr_xmit_retry_events_within_t_sec_max_low, 0x4c, 0, 32);

/* counter_set_ppcnt_rs_fec_histograms_counters_hist
 * Access: RO
 */
MLXSW_ITEM64_INDEXED(reg, ppcnt, counter_set_ppcnt_rs_fec_histograms_counters_hist, 0x8, 0, 64, 8, 0, false);

/* counter_set_usr_xsr_physical_layer_time_since_last_clear_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_time_since_last_clear_high, 0x8, 0, 32);

/* counter_set_usr_xsr_physical_layer_time_since_last_clear_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_time_since_last_clear_low, 0xc, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane0_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane0_high, 0x10, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane0_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane0_low, 0x14, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane1_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane1_high, 0x18, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane1_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane1_low, 0x1c, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane2_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane2_high, 0x20, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane2_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane2_low, 0x24, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane3_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane3_high, 0x28, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane3_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane3_low, 0x2c, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane4_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane4_high, 0x30, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane4_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane4_low, 0x34, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane5_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane5_high, 0x38, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane5_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane5_low, 0x3c, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane6_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane6_high, 0x40, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane6_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane6_low, 0x44, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane7_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane7_high, 0x48, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane7_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane7_low, 0x4c, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane0_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane0_high, 0x50, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane0_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane0_low, 0x54, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane1_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane1_high, 0x58, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane1_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane1_low, 0x5c, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane2_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane2_high, 0x60, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane2_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane2_low, 0x64, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane3_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane3_high, 0x68, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane3_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane3_low, 0x6c, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane4_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane4_high, 0x70, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane4_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane4_low, 0x74, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane5_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane5_high, 0x78, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane5_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane5_low, 0x7c, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane6_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane6_high, 0x80, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane6_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane6_low, 0x84, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane7_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane7_high, 0x88, 0, 32);

/* counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane7_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane7_low, 0x8c, 0, 32);

/* counter_set_usr_xsr_physical_layer_link_down_events
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_usr_xsr_physical_layer_link_down_events, 0x90, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_time_since_last_clear_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_time_since_last_clear_high, 0x8, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_time_since_last_clear_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_time_since_last_clear_low, 0xc, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_unicast_xmit_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_unicast_xmit_pkts_high, 0x10, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_unicast_xmit_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_unicast_xmit_pkts_low, 0x14, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_unicast_rcv_pkts_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_unicast_rcv_pkts_high, 0x18, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_unicast_rcv_pkts_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_unicast_rcv_pkts_low, 0x1c, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_sync_header_error_counter_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_sync_header_error_counter_high, 0x20, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_sync_header_error_counter_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_sync_header_error_counter_low, 0x24, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_local_physical_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_local_physical_errors_high, 0x28, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_local_physical_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_local_physical_errors_low, 0x2c, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_malformed_packet_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_malformed_packet_errors_high, 0x30, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_malformed_packet_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_malformed_packet_errors_low, 0x34, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_buffer_overrun_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_buffer_overrun_errors_high, 0x38, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_buffer_overrun_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_buffer_overrun_errors_low, 0x3c, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_dlid_mapping_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_dlid_mapping_errors_high, 0x40, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_dlid_mapping_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_dlid_mapping_errors_low, 0x44, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_vl_mapping_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_vl_mapping_errors_high, 0x48, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_vl_mapping_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_vl_mapping_errors_low, 0x4c, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_looping_errors_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_looping_errors_high, 0x50, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_looping_errors_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_looping_errors_low, 0x54, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_inactive_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_inactive_discards_high, 0x58, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_inactive_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_inactive_discards_low, 0x5c, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_neighbor_mtu_discards_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_neighbor_mtu_discards_high, 0x60, 0, 32);

/* counter_set_ppcnt_infiniband_packets_counter_port_neighbor_mtu_discards_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_packets_counter_port_neighbor_mtu_discards_low, 0x64, 0, 32);

/* counter_set_ppcnt_infiniband_general_counter_port_rcv_data_qword_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_general_counter_port_rcv_data_qword_high, 0x8, 0, 32);

/* counter_set_ppcnt_infiniband_general_counter_port_rcv_data_qword_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_general_counter_port_rcv_data_qword_low, 0xc, 0, 32);

/* counter_set_ppcnt_infiniband_general_counter_port_xmit_data_qword_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_general_counter_port_xmit_data_qword_high, 0x10, 0, 32);

/* counter_set_ppcnt_infiniband_general_counter_port_xmit_data_qword_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_general_counter_port_xmit_data_qword_low, 0x14, 0, 32);

/* counter_set_ppcnt_infiniband_general_counter_rq_general_error_high
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_general_counter_rq_general_error_high, 0x18, 0, 32);

/* counter_set_ppcnt_infiniband_general_counter_rq_general_error_low
 * Access: RO
 */
MLXSW_ITEM32(reg, ppcnt, counter_set_ppcnt_infiniband_general_counter_rq_general_error_low, 0x1c, 0, 32);

/* cpqe
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, cpqe, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, cpqe, lp_msb, 0x2, 4, 2);

/* marking_percent
 * Access: RW
 */
MLXSW_ITEM8(reg, cpqe, marking_percent, 0x9, 0, 7);

/* en
 * Access: RW
 */
MLXSW_ITEM8(reg, cpqe, en, 0xc, 7, 1);

/* rate
 * Access: RW
 */
MLXSW_ITEM32(reg, cpqe, rate, 0xc, 0, 31);

/* bs
 * Access: RW
 */
MLXSW_ITEM8(reg, cpqe, bs, 0x13, 0, 6);

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

/* rx_lane
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, pmlpe, rx_lane, MLXSW_PMLPE_LANE_MODULE_MAPPING_BASE_LEN, 0, 4, MLXSW_PMLPE_LANE_MODULE_MAPPING_REC_LEN, 0, false);

/* tx_lane
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, pmlpe, tx_lane, MLXSW_PMLPE_LANE_MODULE_MAPPING_BASE_LEN + 1, 0, 4, MLXSW_PMLPE_LANE_MODULE_MAPPING_REC_LEN, 0, false);

/* slot_index
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, pmlpe, slot_index, MLXSW_PMLPE_LANE_MODULE_MAPPING_BASE_LEN + 2, 0, 4, MLXSW_PMLPE_LANE_MODULE_MAPPING_REC_LEN, 0, false);

/* module
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, pmlpe, module, MLXSW_PMLPE_LANE_MODULE_MAPPING_BASE_LEN + 3, 0, 8, MLXSW_PMLPE_LANE_MODULE_MAPPING_REC_LEN, 0, false);

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

/* rarlu
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rarlu, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rarlu, lp_msb, 0x2, 4, 2);

/* lut_en
 * Access: RW
 */
MLXSW_ITEM8(reg, rarlu, lut_en, 0x4, 7, 1);

/* link_utiliztion_thr
 * Access: RW
 */
MLXSW_ITEM32(reg, rarlu, link_utiliztion_thr, 0x4, 0, 31);

/* sbsns
 * -----
 *
 */
/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, sbsns, status, 0x3, 0, 1);

/* trigger_id
 * Access: RO
 */
MLXSW_ITEM8(reg, sbsns, trigger_id, 0x7, 0, 8);

/* trigger_parameters
 * Access: RO
 */
MLXSW_ITEM32(reg, sbsns, trigger_parameters, 0x8, 0, 32);

/* time_high
 * Access: RO
 */
MLXSW_ITEM8(reg, sbsns, time_high, 0x13, 0, 6);

/* time_low
 * Access: RO
 */
MLXSW_ITEM32(reg, sbsns, time_low, 0x14, 0, 32);

/* mdir
 * ----
 *
 */
/* device_id
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mdir, device_id, 0x0, 0, 32, 4, 0, false);

/* spzr
 * ----
 *
 */
/* swid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, spzr, swid, 0x0, 0, 8);

/* router_entity
 * Access: INDEX
 */
MLXSW_ITEM8(reg, spzr, router_entity, 0x1, 1, 1);

/* cm2
 * Access: WO
 */
MLXSW_ITEM8(reg, spzr, cm2, 0x1, 0, 1);

/* ndm
 * Access: WO
 */
MLXSW_ITEM8(reg, spzr, ndm, 0x2, 7, 1);

/* enh_sw_p0_mask
 * Access: WO
 */
MLXSW_ITEM8(reg, spzr, enh_sw_p0_mask, 0x2, 6, 1);

/* cm
 * Access: WO
 */
MLXSW_ITEM8(reg, spzr, cm, 0x2, 5, 1);

/* vk
 * Access: WO
 */
MLXSW_ITEM8(reg, spzr, vk, 0x2, 4, 1);

/* mp
 * Access: WO
 */
MLXSW_ITEM8(reg, spzr, mp, 0x2, 3, 1);

/* sig
 * Access: WO
 */
MLXSW_ITEM8(reg, spzr, sig, 0x2, 2, 1);

/* ng
 * Access: WO
 */
MLXSW_ITEM8(reg, spzr, ng, 0x2, 1, 1);

/* g0
 * Access: WO
 */
MLXSW_ITEM8(reg, spzr, g0, 0x2, 0, 1);

/* enh_sw_p0
 * Access: RW
 */
MLXSW_ITEM8(reg, spzr, enh_sw_p0, 0x3, 1, 1);

/* capability_mask
 * Access: RW
 */
MLXSW_ITEM32(reg, spzr, capability_mask, 0x4, 0, 32);

/* system_image_guid_h
 * Access: RW
 */
MLXSW_ITEM32(reg, spzr, system_image_guid_h, 0x8, 0, 32);

/* system_image_guid_l
 * Access: RW
 */
MLXSW_ITEM32(reg, spzr, system_image_guid_l, 0xc, 0, 32);

/* guid0_h
 * Access: RW
 */
MLXSW_ITEM32(reg, spzr, guid0_h, 0x10, 0, 32);

/* guid0_l
 * Access: RW
 */
MLXSW_ITEM32(reg, spzr, guid0_l, 0x14, 0, 32);

/* node_guid_h
 * Access: RW
 */
MLXSW_ITEM32(reg, spzr, node_guid_h, 0x18, 0, 32);

/* node_guid_l
 * Access: RW
 */
MLXSW_ITEM32(reg, spzr, node_guid_l, 0x1c, 0, 32);

/* capability_mask2
 * Access: RW
 */
MLXSW_ITEM32(reg, spzr, capability_mask2, 0x28, 0, 32);

/* max_pkey
 * Access: RO
 */
MLXSW_ITEM16(reg, spzr, max_pkey, 0x2c, 0, 16);

/* node_description
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, spzr, node_description, 0x30, 64);

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

/* mtcap
 * -----
 *
 */
/* slot_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mtcap, slot_index, 0x1, 0, 4);

/* sensor_count
 * Access: RO
 */
MLXSW_ITEM8(reg, mtcap, sensor_count, 0x3, 0, 7);

/* internal_sensor_count
 * Access: RO
 */
MLXSW_ITEM8(reg, mtcap, internal_sensor_count, 0x7, 0, 7);

/* sensor_map
 * Access: RO
 */
MLXSW_ITEM64(reg, mtcap, sensor_map, 0x8, 0, 64);

/* fsgcr
 * -----
 *
 */
/* failure_on_invalid_lock
 * Access: RW
 */
MLXSW_ITEM8(reg, fsgcr, failure_on_invalid_lock, 0x3, 1, 1);

/* sem_lock_protection_en
 * Access: RW
 */
MLXSW_ITEM8(reg, fsgcr, sem_lock_protection_en, 0x3, 0, 1);

/* ticket_cb_index
 * Access: RW
 */
MLXSW_ITEM8(reg, fsgcr, ticket_cb_index, 0x5, 0, 4);

/* sem_poll_max_retries
 * Access: RW
 */
MLXSW_ITEM8(reg, fsgcr, sem_poll_max_retries, 0x7, 0, 8);

/* linear_group_id
 * Access: RW
 */
MLXSW_ITEM16(reg, fsgcr, linear_group_id, 0xa, 0, 16);

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

/* ugcap
 * -----
 *
 */
/* max_mtu
 * Access: RO
 */
MLXSW_ITEM16(reg, ugcap, max_mtu, 0x2, 0, 16);

/* cap_utcam_entries
 * Access: RO
 */
MLXSW_ITEM32(reg, ugcap, cap_utcam_entries, 0x4, 0, 32);

/* cap_utcam_counters
 * Access: RO
 */
MLXSW_ITEM8(reg, ugcap, cap_utcam_counters, 0xa, 0, 8);

/* cap_utcam_keys
 * Access: RO
 */
MLXSW_ITEM8(reg, ugcap, cap_utcam_keys, 0xb, 0, 8);

/* cap_utcam_entries_2_key_blocks
 * Access: RO
 */
MLXSW_ITEM8(reg, ugcap, cap_utcam_entries_2_key_blocks, 0xc, 0, 8);

/* cap_utcam_entries_4_key_blocks
 * Access: RO
 */
MLXSW_ITEM8(reg, ugcap, cap_utcam_entries_4_key_blocks, 0xd, 0, 8);

/* cap_utcam_entries_8_key_blocks
 * Access: RO
 */
MLXSW_ITEM8(reg, ugcap, cap_utcam_entries_8_key_blocks, 0xe, 0, 8);

/* cap_utcam_entries_12_key_blocks
 * Access: RO
 */
MLXSW_ITEM8(reg, ugcap, cap_utcam_entries_12_key_blocks, 0xf, 0, 8);

/* cap_secy_entries
 * Access: RO
 */
MLXSW_ITEM32(reg, ugcap, cap_secy_entries, 0x10, 0, 32);

/* cap_sadb_entries
 * Access: RO
 */
MLXSW_ITEM32(reg, ugcap, cap_sadb_entries, 0x14, 0, 32);

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
MLXSW_ITEM32(reg, mddc, index, 0x0, 9, 8);

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

/* sleep_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, paos, sleep_cap, 0x6, 6, 1);

/* en_sleep
 * Access: RW
 */
MLXSW_ITEM8(reg, paos, en_sleep, 0x6, 4, 1);

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

/* cff_counter_set_type
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, cff_counter_set_type, 0x1c, 0, 8);

/* cff_counter_base_index
 * Access: RW
 */
MLXSW_ITEM32(reg, sfmr, cff_counter_base_index, 0x1c, 0, 24);

/* cff_mid_base
 * Access: RW
 */
MLXSW_ITEM16(reg, sfmr, cff_mid_base, 0x22, 0, 16);

/* tunnel_port_lbf_bitmap
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, tunnel_port_lbf_bitmap, 0x25, 0, 4);

/* nve_flood_prf_id
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, nve_flood_prf_id, 0x26, 0, 2);

/* cff_prf_id
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, cff_prf_id, 0x27, 0, 2);

/* smpe_valid
 * Access: RW
 */
MLXSW_ITEM8(reg, sfmr, smpe_valid, 0x29, 4, 1);

/* smpe
 * Access: RW
 */
MLXSW_ITEM16(reg, sfmr, smpe, 0x2a, 0, 16);

/* ptys
 * ----
 *
 */
/* reserved_high
 * Access: RO
 */
MLXSW_ITEM8(reg, ptys, reserved_high, 0x0, 7, 1);

/* an_disable_admin
 * Access: RW
 */
MLXSW_ITEM8(reg, ptys, an_disable_admin, 0x0, 6, 1);

/* an_disable_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, ptys, an_disable_cap, 0x0, 5, 1);

/* force_tx_aba_param
 * Access: RW
 */
MLXSW_ITEM8(reg, ptys, force_tx_aba_param, 0x0, 0, 1);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ptys, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ptys, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ptys, lp_msb, 0x2, 4, 2);

/* port_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ptys, port_type, 0x2, 0, 4);

/* proto_mask
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ptys, proto_mask, 0x3, 0, 3);

/* an_status
 * Access: RO
 */
MLXSW_ITEM8(reg, ptys, an_status, 0x4, 4, 4);

/* max_port_rate
 * Access: RO
 */
MLXSW_ITEM16(reg, ptys, max_port_rate, 0x4, 0, 12);

/* data_rate_oper
 * Access: RO
 */
MLXSW_ITEM16(reg, ptys, data_rate_oper, 0x6, 0, 16);

/* ext_eth_proto_capability
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, ext_eth_proto_capability, 0x8, 0, 32);

/* eth_proto_capability
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, eth_proto_capability, 0xc, 0, 32);

/* ib_link_width_capability
 * Access: RO
 */
MLXSW_ITEM16(reg, ptys, ib_link_width_capability, 0x10, 0, 16);

/* ib_proto_capability
 * Access: RO
 */
MLXSW_ITEM16(reg, ptys, ib_proto_capability, 0x12, 0, 16);

/* ext_eth_proto_admin
 * Access: RW
 */
MLXSW_ITEM32(reg, ptys, ext_eth_proto_admin, 0x14, 0, 32);

/* eth_proto_admin
 * Access: RW
 */
MLXSW_ITEM32(reg, ptys, eth_proto_admin, 0x18, 0, 32);

/* ib_link_width_admin
 * Access: RW
 */
MLXSW_ITEM16(reg, ptys, ib_link_width_admin, 0x1c, 0, 16);

/* ib_proto_admin
 * Access: RW
 */
MLXSW_ITEM16(reg, ptys, ib_proto_admin, 0x1e, 0, 16);

/* ext_eth_proto_oper
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, ext_eth_proto_oper, 0x20, 0, 32);

/* eth_proto_oper
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, eth_proto_oper, 0x24, 0, 32);

/* ib_link_width_oper
 * Access: RO
 */
MLXSW_ITEM16(reg, ptys, ib_link_width_oper, 0x28, 0, 16);

/* ib_proto_oper
 * Access: RO
 */
MLXSW_ITEM16(reg, ptys, ib_proto_oper, 0x2a, 0, 16);

/* eth_proto_lp_valid
 * Access: RO
 */
MLXSW_ITEM8(reg, ptys, eth_proto_lp_valid, 0x2c, 7, 1);

/* force_lt_frames_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, ptys, force_lt_frames_cap, 0x2c, 6, 1);

/* force_lt_frames_admin
 * Access: RW
 */
MLXSW_ITEM8(reg, ptys, force_lt_frames_admin, 0x2c, 4, 2);

/* eth_proto_lp_legacy_valid
 * Access: RW
 */
MLXSW_ITEM8(reg, ptys, eth_proto_lp_legacy_valid, 0x2c, 3, 1);

/* connector_type
 * Access: RO
 */
MLXSW_ITEM8(reg, ptys, connector_type, 0x2f, 0, 4);

/* eth_proto_lp_advertise
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, eth_proto_lp_advertise, 0x30, 0, 32);

/* eth_proto_lp_legacy_advertise
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, eth_proto_lp_legacy_advertise, 0x34, 0, 32);

/* upvid
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upvid, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upvid, lp_msb, 0x2, 4, 2);

/* side
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upvid, side, 0x2, 0, 4);

/* pvid
 * Access: RW
 */
MLXSW_ITEM16(reg, upvid, pvid, 0x6, 0, 12);

/* umtu
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, umtu, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, umtu, lp_msb, 0x2, 4, 2);

/* admin_mtu
 * Access: RW
 */
MLXSW_ITEM16(reg, umtu, admin_mtu, 0x4, 0, 16);

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

/* sensor_shut_down_map
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mtsde, sensor_shut_down_map, 0x4, 0, 32, 4, 0, false);

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

/* pplr
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pplr, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pplr, lp_msb, 0x2, 4, 2);

/* op_mod
 * Access: OP
 */
MLXSW_ITEM8(reg, pplr, op_mod, 0x2, 0, 1);

/* port_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pplr, port_type, 0x3, 4, 4);

/* lb_cap
 * Access: RO
 */
MLXSW_ITEM16(reg, pplr, lb_cap, 0x4, 0, 12);

/* lb_en
 * Access: RW
 */
MLXSW_ITEM16(reg, pplr, lb_en, 0x6, 0, 12);

/* upvc
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upvc, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upvc, lp_msb, 0x2, 4, 2);

/* side
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upvc, side, 0x2, 0, 4);

/* inner_et2
 * Access: RW
 */
MLXSW_ITEM8(reg, upvc, inner_et2, 0x5, 1, 1);

/* et2
 * Access: RW
 */
MLXSW_ITEM8(reg, upvc, et2, 0x5, 0, 1);

/* inner_et1
 * Access: RW
 */
MLXSW_ITEM8(reg, upvc, inner_et1, 0x6, 1, 1);

/* et1
 * Access: RW
 */
MLXSW_ITEM8(reg, upvc, et1, 0x6, 0, 1);

/* inner_et0
 * Access: RW
 */
MLXSW_ITEM8(reg, upvc, inner_et0, 0x7, 1, 1);

/* et0
 * Access: RW
 */
MLXSW_ITEM8(reg, upvc, et0, 0x7, 0, 1);

/* hett
 * ----
 *
 */
/* opcode
 * Access: WO
 */
MLXSW_ITEM8(reg, hett, opcode, 0x2, 0, 1);

/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, hett, status, 0x3, 0, 2);

/* trap_group_bitmap
 * Access: INDEX
 */
MLXSW_ITEM64(reg, hett, trap_group_bitmap, 0x8, 0, 64);

/* trap_group
 * Access: RO
 */
MLXSW_ITEM8(reg, hett, trap_group, 0x13, 0, 8);

/* mtppst
 * ------
 *
 */
/* pin
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mtppst, pin, 0x3, 0, 8);

/* timestamp_msb
 * Access: RO
 */
MLXSW_ITEM32(reg, mtppst, timestamp_msb, 0x8, 0, 32);

/* timestamp_lsb
 * Access: RO
 */
MLXSW_ITEM32(reg, mtppst, timestamp_lsb, 0xc, 0, 32);

/* xgcr
 * ----
 *
 */
/* mtm
 * Access: RW
 */
MLXSW_ITEM8(reg, xgcr, mtm, 0x7, 0, 4);

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

/* entry_tngee_nve_vni_update
 * Access: RW
 */
MLXSW_ITEM8(reg, tngee, entry_tngee_nve_vni_update, 0x40, 7, 1);

/* entry_tngee_nve_tqos_prof_en
 * Access: OP
 */
MLXSW_ITEM8(reg, tngee, entry_tngee_nve_tqos_prof_en, 0x40, 6, 1);

/* entry_tngee_nve_vni
 * Access: RW
 */
MLXSW_ITEM32(reg, tngee, entry_tngee_nve_vni, 0x40, 0, 24);

/* entry_tngee_nve_tqos_profile
 * Access: RW
 */
MLXSW_ITEM8(reg, tngee, entry_tngee_nve_tqos_profile, 0x47, 0, 4);

/* entry_tngee_flex_reg_tqos_profile
 * Access: RW
 */
MLXSW_ITEM8(reg, tngee, entry_tngee_flex_reg_tqos_profile, 0x40, 0, 4);

/* entry_tngee_flex_reg_tunnel_port
 * Access: RW
 */
MLXSW_ITEM8(reg, tngee, entry_tngee_flex_reg_tunnel_port, 0x43, 0, 4);

/* entry_tngee_flex_reg_emt_pointer
 * Access: RW
 */
MLXSW_ITEM8(reg, tngee, entry_tngee_flex_reg_emt_pointer, 0x47, 0, 8);

/* entry_tngee_flex_reg_cbset_select
 * Access: RW
 */
MLXSW_ITEM8(reg, tngee, entry_tngee_flex_reg_cbset_select, 0x4a, 0, 2);

/* entry_tngee_flex_reg_cbset_x_set_en
 * Access: RW
 */
MLXSW_ITEM8(reg, tngee, entry_tngee_flex_reg_cbset_x_set_en, 0x4b, 1, 1);

/* entry_tngee_flex_reg_cbset_y_set_en
 * Access: RW
 */
MLXSW_ITEM8(reg, tngee, entry_tngee_flex_reg_cbset_y_set_en, 0x4b, 0, 1);

/* entry_tngee_flex_reg_cbset_x_val
 * Access: RW
 */
MLXSW_ITEM16(reg, tngee, entry_tngee_flex_reg_cbset_x_val, 0x4c, 0, 16);

/* entry_tngee_flex_reg_cbset_y_val
 * Access: RW
 */
MLXSW_ITEM16(reg, tngee, entry_tngee_flex_reg_cbset_y_val, 0x4e, 0, 16);

/* spms_v2
 * -------
 *
 */
/* allv
 * Access: OP
 */
MLXSW_ITEM8(reg, spms_v2, allv, 0x0, 7, 1);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, spms_v2, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, spms_v2, lp_msb, 0x2, 4, 2);

/* num_rec
 * Access: INDEX
 */
MLXSW_ITEM8(reg, spms_v2, num_rec, 0x3, 0, 8);

/* state
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, spms_v2, state, MLXSW_SPMS_V2_VID_RECORD_BASE_LEN + 2, 4, 2, MLXSW_SPMS_V2_VID_RECORD_REC_LEN, 0, false);

/* vid
 * Access: INDEX
 */
MLXSW_ITEM16_INDEXED(reg, spms_v2, vid, MLXSW_SPMS_V2_VID_RECORD_BASE_LEN + 2, 0, 12, MLXSW_SPMS_V2_VID_RECORD_REC_LEN, 0, false);

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

/* usadb
 * -----
 *
 */
/* uengine
 * Access: INDEX
 */
MLXSW_ITEM16(reg, usadb, uengine, 0x0, 0, 16);

/* sadb_entry_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, usadb, sadb_entry_index, 0x2, 0, 16);

/* op
 * Access: OP
 */
MLXSW_ITEM8(reg, usadb, op, 0x6, 4, 2);

/* key_size
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, key_size, 0x7, 4, 1);

/* cipher_type
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, cipher_type, 0x7, 0, 2);

/* entry_usadb_encr_gcm_aes_an
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_encr_gcm_aes_an, 0x9, 4, 2);

/* entry_usadb_encr_gcm_aes_tci_sc
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_encr_gcm_aes_tci_sc, 0x9, 2, 1);

/* entry_usadb_encr_gcm_aes_tci_e
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_encr_gcm_aes_tci_e, 0x9, 1, 1);

/* entry_usadb_encr_gcm_aes_tci_c
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_encr_gcm_aes_tci_c, 0x9, 0, 1);

/* entry_usadb_encr_gcm_aes_policy
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_encr_gcm_aes_policy, 0xb, 0, 1);

/* entry_usadb_encr_gcm_aes_sci
 * Access: RW
 */
MLXSW_ITEM64(reg, usadb, entry_usadb_encr_gcm_aes_sci, 0x10, 0, 64);

/* entry_usadb_encr_gcm_aes_next_pn
 * Access: RW
 */
MLXSW_ITEM32(reg, usadb, entry_usadb_encr_gcm_aes_next_pn, 0x18, 0, 32);

/* entry_usadb_encr_gcm_aes_conf_offset
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_encr_gcm_aes_conf_offset, 0x23, 0, 8);

/* entry_usadb_encr_gcm_aes_xpn_an
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_encr_gcm_aes_xpn_an, 0x9, 4, 2);

/* entry_usadb_encr_gcm_aes_xpn_tci_sc
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_encr_gcm_aes_xpn_tci_sc, 0x9, 2, 1);

/* entry_usadb_encr_gcm_aes_xpn_tci_e
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_encr_gcm_aes_xpn_tci_e, 0x9, 1, 1);

/* entry_usadb_encr_gcm_aes_xpn_tci_c
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_encr_gcm_aes_xpn_tci_c, 0x9, 0, 1);

/* entry_usadb_encr_gcm_aes_xpn_policy
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_encr_gcm_aes_xpn_policy, 0xb, 0, 1);

/* entry_usadb_encr_gcm_aes_xpn_sci
 * Access: RW
 */
MLXSW_ITEM64(reg, usadb, entry_usadb_encr_gcm_aes_xpn_sci, 0x10, 0, 64);

/* entry_usadb_encr_gcm_aes_xpn_next_pn
 * Access: RW
 */
MLXSW_ITEM64(reg, usadb, entry_usadb_encr_gcm_aes_xpn_next_pn, 0x18, 0, 64);

/* entry_usadb_encr_gcm_aes_xpn_salt
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, usadb, entry_usadb_encr_gcm_aes_xpn_salt, 0x20, 12);

/* entry_usadb_encr_gcm_aes_xpn_ssci
 * Access: RW
 */
MLXSW_ITEM32(reg, usadb, entry_usadb_encr_gcm_aes_xpn_ssci, 0x30, 0, 32);

/* entry_usadb_decr_gcm_aes_rpe
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_decr_gcm_aes_rpe, 0xa, 0, 1);

/* entry_usadb_decr_gcm_aes_policy
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_decr_gcm_aes_policy, 0xb, 0, 1);

/* entry_usadb_decr_gcm_aes_sci
 * Access: RW
 */
MLXSW_ITEM64(reg, usadb, entry_usadb_decr_gcm_aes_sci, 0x10, 0, 64);

/* entry_usadb_decr_gcm_aes_next_pn
 * Access: RW
 */
MLXSW_ITEM32(reg, usadb, entry_usadb_decr_gcm_aes_next_pn, 0x18, 0, 32);

/* entry_usadb_decr_gcm_aes_conf_offset
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_decr_gcm_aes_conf_offset, 0x23, 0, 8);

/* entry_usadb_decr_gcm_aes_replay_window_size
 * Access: RW
 */
MLXSW_ITEM32(reg, usadb, entry_usadb_decr_gcm_aes_replay_window_size, 0x24, 0, 32);

/* entry_usadb_decr_gcm_aes_xpn_rpe
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_decr_gcm_aes_xpn_rpe, 0xa, 0, 1);

/* entry_usadb_decr_gcm_aes_xpn_policy
 * Access: RW
 */
MLXSW_ITEM8(reg, usadb, entry_usadb_decr_gcm_aes_xpn_policy, 0xb, 0, 1);

/* entry_usadb_decr_gcm_aes_xpn_ssci
 * Access: RW
 */
MLXSW_ITEM32(reg, usadb, entry_usadb_decr_gcm_aes_xpn_ssci, 0x14, 0, 32);

/* entry_usadb_decr_gcm_aes_xpn_next_pn
 * Access: RW
 */
MLXSW_ITEM64(reg, usadb, entry_usadb_decr_gcm_aes_xpn_next_pn, 0x18, 0, 64);

/* entry_usadb_decr_gcm_aes_xpn_salt
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, usadb, entry_usadb_decr_gcm_aes_xpn_salt, 0x20, 12);

/* entry_usadb_decr_gcm_aes_xpn_replay_window_size
 * Access: RW
 */
MLXSW_ITEM32(reg, usadb, entry_usadb_decr_gcm_aes_xpn_replay_window_size, 0x2c, 0, 32);

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

/* sbsnte
 * ------
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbsnte, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbsnte, lp_msb, 0x2, 4, 2);

/* type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, sbsnte, type, 0x7, 0, 8);

/* tclass_en_high
 * Access: RW
 */
MLXSW_ITEM32(reg, sbsnte, tclass_en_high, 0x8, 0, 32);

/* tclass_en_low
 * Access: RW
 */
MLXSW_ITEM32(reg, sbsnte, tclass_en_low, 0xc, 0, 32);

/* qspcp
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qspcp, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qspcp, lp_msb, 0x2, 4, 2);

/* switch_prio
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qspcp, switch_prio, 0x3, 0, 4);

/* rx_counting_prio
 * Access: RW
 */
MLXSW_ITEM8(reg, qspcp, rx_counting_prio, 0x7, 0, 3);

/* tx_counting_prio
 * Access: RW
 */
MLXSW_ITEM8(reg, qspcp, tx_counting_prio, 0xb, 0, 3);

/* rngcr
 * -----
 *
 */
/* v
 * Access: RW
 */
MLXSW_ITEM8(reg, rngcr, v, 0x0, 7, 1);

/* nat4to6_flh
 * Access: RW
 */
MLXSW_ITEM8(reg, rngcr, nat4to6_flh, 0x0, 0, 1);

/* nat4to6_fl_prefix
 * Access: RW
 */
MLXSW_ITEM32(reg, rngcr, nat4to6_fl_prefix, 0x0, 8, 12);

/* nat4to6_fl_suffix
 * Access: RW
 */
MLXSW_ITEM8(reg, rngcr, nat4to6_fl_suffix, 0x3, 0, 8);

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

/* pbs_record_ppbs_unicast_v_fid
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, pbs_record_ppbs_unicast_v_fid, 0xc, 7, 1);

/* pbs_record_ppbs_unicast_set_vid
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, pbs_record_ppbs_unicast_set_vid, 0xc, 6, 1);

/* pbs_record_ppbs_unicast_vid
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_ppbs_unicast_vid, 0xc, 0, 12);

/* pbs_record_ppbs_unicast_fid
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_ppbs_unicast_fid, 0xe, 0, 16);

/* pbs_record_ppbs_unicast_action
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, pbs_record_ppbs_unicast_action, 0x10, 4, 4);

/* pbs_record_ppbs_unicast_system_port
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_ppbs_unicast_system_port, 0x12, 0, 16);

/* pbs_record_unicast_lag_uvid
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, pbs_record_unicast_lag_uvid, 0xe, 7, 1);

/* pbs_record_unicast_lag_vid
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_unicast_lag_vid, 0xe, 0, 12);

/* pbs_record_unicast_lag_lag_id
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_unicast_lag_lag_id, 0x12, 0, 10);

/* pbs_record_ppbs_multicast_v_fid
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, pbs_record_ppbs_multicast_v_fid, 0xc, 7, 1);

/* pbs_record_ppbs_multicast_pgi
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_ppbs_multicast_pgi, 0xc, 0, 13);

/* pbs_record_ppbs_multicast_fid
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_ppbs_multicast_fid, 0xe, 0, 16);

/* pbs_record_ppbs_multicast_mid
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_ppbs_multicast_mid, 0x12, 0, 16);

/* pbs_record_unicast_tunnel_udip
 * Access: RW
 */
MLXSW_ITEM32(reg, ppbs, pbs_record_unicast_tunnel_udip, 0xc, 0, 32);

/* pbs_record_unicast_tunnel_protocol
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, pbs_record_unicast_tunnel_protocol, 0x10, 3, 1);

/* pbs_record_unicast_tunnel_gen_enc
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, pbs_record_unicast_tunnel_gen_enc, 0x10, 2, 1);

/* pbs_record_unicast_tunnel_tunnel_port_lbf_bitmap
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_unicast_tunnel_tunnel_port_lbf_bitmap, 0x16, 0, 16);

/* pbs_record_unicast_tunnel_ecmp_size
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_unicast_tunnel_ecmp_size, 0x1a, 0, 13);

/* pbs_record_multicast_tunnel_underlay_mc_ptr_msb
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_multicast_tunnel_underlay_mc_ptr_msb, 0xc, 0, 16);

/* pbs_record_multicast_tunnel_fid
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_multicast_tunnel_fid, 0xe, 0, 16);

/* pbs_record_multicast_tunnel_underlay_mc_ptr_lsb
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, pbs_record_multicast_tunnel_underlay_mc_ptr_lsb, 0x10, 0, 8);

/* pbs_record_multicast_tunnel_v_fid
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbs, pbs_record_multicast_tunnel_v_fid, 0x11, 7, 1);

/* pbs_record_multicast_tunnel_mid
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_multicast_tunnel_mid, 0x12, 0, 16);

/* pbs_record_multicast_tunnel_lbf_tunnel_port_bitmap
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_multicast_tunnel_lbf_tunnel_port_bitmap, 0x16, 0, 16);

/* pbs_record_multicast_tunnel_ecmp_size
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbs, pbs_record_multicast_tunnel_ecmp_size, 0x1a, 0, 13);

/* ppbt
 * ----
 *
 */
/* e
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppbt, e, 0x0, 7, 1);

/* op
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbt, op, 0x0, 4, 3);

/* tport
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppbt, tport, 0x0, 0, 1);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppbt, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ppbt, lp_msb, 0x2, 4, 2);

/* g
 * Access: RW
 */
MLXSW_ITEM8(reg, ppbt, g, 0x10, 7, 1);

/* acl_id_group_id
 * Access: RW
 */
MLXSW_ITEM16(reg, ppbt, acl_id_group_id, 0x12, 0, 16);

/* msees
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, msees, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, msees, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, msees, lp_msb, 0x2, 4, 2);

/* field_select
 * Access: WO
 */
MLXSW_ITEM32(reg, msees, field_select, 0x4, 0, 32);

/* admin_status
 * Access: RW
 */
MLXSW_ITEM8(reg, msees, admin_status, 0x8, 4, 4);

/* oper_status
 * Access: RO
 */
MLXSW_ITEM8(reg, msees, oper_status, 0x8, 0, 4);

/* ho_acq
 * Access: RO
 */
MLXSW_ITEM8(reg, msees, ho_acq, 0x9, 7, 1);

/* admin_freq_measure
 * Access: RW
 */
MLXSW_ITEM8(reg, msees, admin_freq_measure, 0xa, 2, 1);

/* oper_freq_measure
 * Access: RO
 */
MLXSW_ITEM8(reg, msees, oper_freq_measure, 0xa, 1, 1);

/* failure_reason
 * Access: RO
 */
MLXSW_ITEM16(reg, msees, failure_reason, 0xa, 0, 9);

/* frequency_diff
 * Access: RO
 */
MLXSW_ITEM32(reg, msees, frequency_diff, 0xc, 0, 32);

/* sgcr
 * ----
 *
 */
/* llb
 * Access: RW
 */
MLXSW_ITEM8(reg, sgcr, llb, 0x7, 0, 1);

/* activity_dis
 * Access: RW
 */
MLXSW_ITEM8(reg, sgcr, activity_dis, 0xb, 0, 8);

/* lag_lookup_pgt_base
 * Access: RW
 */
MLXSW_ITEM16(reg, sgcr, lag_lookup_pgt_base, 0xe, 0, 16);

/* mpnhlfe
 * -------
 *
 */
/* ca
 * Access: OP
 */
MLXSW_ITEM8(reg, mpnhlfe, ca, 0x0, 7, 1);

/* a
 * Access: RO
 */
MLXSW_ITEM8(reg, mpnhlfe, a, 0x1, 0, 1);

/* v
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, v, 0x4, 7, 1);

/* nhlfe_ptr
 * Access: INDEX
 */
MLXSW_ITEM32(reg, mpnhlfe, nhlfe_ptr, 0x4, 0, 24);

/* forward_action
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, forward_action, 0xb, 0, 4);

/* trap_action
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, trap_action, 0xc, 4, 4);

/* trap_id
 * Access: RW
 */
MLXSW_ITEM16(reg, mpnhlfe, trap_id, 0xe, 0, 9);

/* counter_set_type
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, counter_set_type, 0x10, 0, 8);

/* counter_index
 * Access: RW
 */
MLXSW_ITEM32(reg, mpnhlfe, counter_index, 0x10, 0, 24);

/* nhlfe_parameters_mpnhlfe_param_eth_dscp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_eth_dscp_rw, 0x30, 4, 2);

/* nhlfe_parameters_mpnhlfe_param_eth_uecn_exp
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_eth_uecn_exp, 0x30, 2, 1);

/* nhlfe_parameters_mpnhlfe_param_eth_usp_dscp
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_eth_usp_dscp, 0x30, 1, 1);

/* nhlfe_parameters_mpnhlfe_param_eth_usp_exp
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_eth_usp_exp, 0x30, 0, 1);

/* nhlfe_parameters_mpnhlfe_param_eth_exp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_eth_exp_rw, 0x31, 4, 2);

/* nhlfe_parameters_mpnhlfe_param_eth_set_exp
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_eth_set_exp, 0x31, 3, 1);

/* nhlfe_parameters_mpnhlfe_param_eth_exp
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_eth_exp, 0x31, 0, 3);

/* nhlfe_parameters_mpnhlfe_param_eth_tqos_profile
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_eth_tqos_profile, 0x32, 4, 4);

/* nhlfe_parameters_mpnhlfe_param_eth_bos_check
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_eth_bos_check, 0x33, 0, 2);

/* nhlfe_parameters_mpnhlfe_param_eth_label_action
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_eth_label_action, 0x34, 0, 3);

/* nhlfe_parameters_mpnhlfe_param_eth_label_id
 * Access: RW
 */
MLXSW_ITEM32(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_eth_label_id, 0x34, 0, 20);

/* nhlfe_parameters_mpnhlfe_param_eth_dmac
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_eth_dmac, 0x3a, 6);

/* nhlfe_parameters_mpnhlfe_param_eth_egress_router_interface
 * Access: RW
 */
MLXSW_ITEM16(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_eth_egress_router_interface, 0x42, 0, 16);

/* nhlfe_parameters_mpnhlfe_param_iprouter_dscp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_iprouter_dscp_rw, 0x30, 4, 2);

/* nhlfe_parameters_mpnhlfe_param_iprouter_uecn_exp
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_iprouter_uecn_exp, 0x30, 2, 1);

/* nhlfe_parameters_mpnhlfe_param_iprouter_usp_dscp
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_iprouter_usp_dscp, 0x30, 1, 1);

/* nhlfe_parameters_mpnhlfe_param_iprouter_usp_exp
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_iprouter_usp_exp, 0x30, 0, 1);

/* nhlfe_parameters_mpnhlfe_param_iprouter_tqos_profile
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_iprouter_tqos_profile, 0x31, 0, 4);

/* nhlfe_parameters_mpnhlfe_param_iprouter_irifv
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_iprouter_irifv, 0x3c, 0, 1);

/* nhlfe_parameters_mpnhlfe_param_iprouter_irif
 * Access: RW
 */
MLXSW_ITEM16(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_iprouter_irif, 0x3e, 0, 16);

/* nhlfe_parameters_mpnhlfe_param_iprouter_erifv
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_iprouter_erifv, 0x40, 0, 1);

/* nhlfe_parameters_mpnhlfe_param_iprouter_egress_router_interface
 * Access: RW
 */
MLXSW_ITEM16(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_iprouter_egress_router_interface, 0x42, 0, 16);

/* nhlfe_parameters_mpnhlfe_param_iprouter_cbset_select
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_iprouter_cbset_select, 0x4b, 0, 3);

/* nhlfe_parameters_mpnhlfe_param_iprouter_cbset_val
 * Access: RW
 */
MLXSW_ITEM16(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_iprouter_cbset_val, 0x4e, 0, 16);

/* nhlfe_parameters_mpnhlfe_param_iprouter_cbset_mask
 * Access: RW
 */
MLXSW_ITEM16(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_iprouter_cbset_mask, 0x52, 0, 16);

/* nhlfe_parameters_mpnhlfe_param_lookups_dscp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_lookups_dscp_rw, 0x30, 4, 2);

/* nhlfe_parameters_mpnhlfe_param_lookups_uecn_exp
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_lookups_uecn_exp, 0x30, 2, 1);

/* nhlfe_parameters_mpnhlfe_param_lookups_usp_dscp
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_lookups_usp_dscp, 0x30, 1, 1);

/* nhlfe_parameters_mpnhlfe_param_lookups_usp_exp
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_lookups_usp_exp, 0x30, 0, 1);

/* nhlfe_parameters_mpnhlfe_param_lookups_tqos_profile
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_lookups_tqos_profile, 0x31, 0, 4);

/* nhlfe_parameters_mpnhlfe_param_lookups_bos_check
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_lookups_bos_check, 0x33, 0, 2);

/* nhlfe_parameters_mpnhlfe_param_lookups_irifv
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_lookups_irifv, 0x3c, 0, 1);

/* nhlfe_parameters_mpnhlfe_param_lookups_irif
 * Access: RW
 */
MLXSW_ITEM16(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_lookups_irif, 0x3e, 0, 16);

/* nhlfe_parameters_mpnhlfe_param_lookups_erifv
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_lookups_erifv, 0x40, 0, 1);

/* nhlfe_parameters_mpnhlfe_param_lookups_egress_router_interface
 * Access: RW
 */
MLXSW_ITEM16(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_lookups_egress_router_interface, 0x42, 0, 16);

/* nhlfe_parameters_mpnhlfe_param_lookups_cbset_select
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_lookups_cbset_select, 0x4b, 0, 3);

/* nhlfe_parameters_mpnhlfe_param_lookups_cbset_val
 * Access: RW
 */
MLXSW_ITEM16(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_lookups_cbset_val, 0x4e, 0, 16);

/* nhlfe_parameters_mpnhlfe_param_lookups_cbset_mask
 * Access: RW
 */
MLXSW_ITEM16(reg, mpnhlfe, nhlfe_parameters_mpnhlfe_param_lookups_cbset_mask, 0x52, 0, 16);

/* nhlfe_parameters_next_nhlfe_exp_rw
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_next_nhlfe_exp_rw, 0x31, 4, 2);

/* nhlfe_parameters_next_nhlfe_set_exp
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_next_nhlfe_set_exp, 0x31, 3, 1);

/* nhlfe_parameters_next_nhlfe_exp
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_next_nhlfe_exp, 0x31, 0, 3);

/* nhlfe_parameters_next_nhlfe_label_action
 * Access: RW
 */
MLXSW_ITEM8(reg, mpnhlfe, nhlfe_parameters_next_nhlfe_label_action, 0x34, 0, 3);

/* nhlfe_parameters_next_nhlfe_label_id
 * Access: RW
 */
MLXSW_ITEM32(reg, mpnhlfe, nhlfe_parameters_next_nhlfe_label_id, 0x34, 0, 20);

/* nhlfe_parameters_next_nhlfe_next_nhlfe
 * Access: RW
 */
MLXSW_ITEM32(reg, mpnhlfe, nhlfe_parameters_next_nhlfe_next_nhlfe, 0x40, 0, 24);

/* nhlfe_parameters_next_nhlfe_ecmp_size
 * Access: RW
 */
MLXSW_ITEM16(reg, mpnhlfe, nhlfe_parameters_next_nhlfe_ecmp_size, 0x46, 0, 13);

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

/* sensor_warning
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mtewe, sensor_warning, 0x4, 0, 32, 4, 0, false);

/* mtpspu
 * ------
 *
 */
/* message_type
 * Access: RW
 */
MLXSW_ITEM16(reg, mtpspu, message_type, 0x6, 0, 16);

/* hgcr
 * ----
 *
 */
/* truncation_size
 * Access: RW
 */
MLXSW_ITEM16(reg, hgcr, truncation_size, 0x2, 0, 14);

/* truncation_size_prof1
 * Access: RW
 */
MLXSW_ITEM16(reg, hgcr, truncation_size_prof1, 0x12, 0, 14);

/* truncation_size_prof2
 * Access: RW
 */
MLXSW_ITEM16(reg, hgcr, truncation_size_prof2, 0x16, 0, 14);

/* tac_crawler_timer
 * Access: RW
 */
MLXSW_ITEM8(reg, hgcr, tac_crawler_timer, 0x1a, 0, 5);

/* tac_crawler_action
 * Access: RW
 */
MLXSW_ITEM8(reg, hgcr, tac_crawler_action, 0x1b, 0, 2);

/* fgcr
 * ----
 *
 */
/* flat_sec_offset
 * Access: RW
 */
MLXSW_ITEM8(reg, fgcr, flat_sec_offset, 0x3, 0, 8);

/* utfc
 * ----
 *
 */
/* clear
 * Access: OP
 */
MLXSW_ITEM8(reg, utfc, clear, 0x0, 7, 1);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, utfc, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, utfc, lp_msb, 0x2, 4, 2);

/* side
 * Access: INDEX
 */
MLXSW_ITEM8(reg, utfc, side, 0x2, 0, 4);

/* utrapf_dropped
 * Access: RO
 */
MLXSW_ITEM64(reg, utfc, utrapf_dropped, 0x8, 0, 64);

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

/* qspip
 * -----
 *
 */
/* switch_prio
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qspip, switch_prio, 0x3, 0, 4);

/* ieee_prio
 * Access: RW
 */
MLXSW_ITEM8(reg, qspip, ieee_prio, 0x7, 0, 3);

/* slsir
 * -----
 *
 */
/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, status, 0x0, 4, 4);

/* version
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, version, 0x0, 0, 4);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slsir, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slsir, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slsir, lp_msb, 0x2, 4, 2);

/* lane
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slsir, lane, 0x2, 0, 4);

/* port_type
 * Access: INDEX
 */
MLXSW_ITEM8(reg, slsir, port_type, 0x3, 4, 4);

/* nop_rsunf_error
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, nop_rsunf_error, 0x7, 7, 1);

/* nop_rsovf_error
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, nop_rsovf_error, 0x7, 6, 1);

/* nop_dsunf_error
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, nop_dsunf_error, 0x7, 5, 1);

/* nop_dsovf_error
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, nop_dsovf_error, 0x7, 4, 1);

/* peq_adc_overload
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, peq_adc_overload, 0x7, 3, 1);

/* feq_adc_overload
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, feq_adc_overload, 0x7, 2, 1);

/* cdr_error
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, cdr_error, 0x7, 1, 1);

/* imem_chksm_error
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, imem_chksm_error, 0x7, 0, 1);

/* rx_ugl_state
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, rx_ugl_state, 0x8, 4, 4);

/* rx_eom_ugl_state
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, rx_eom_ugl_state, 0x8, 0, 2);

/* rx_cal_ugl_state
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, rx_cal_ugl_state, 0x9, 5, 3);

/* rx_eq_ugl_state
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, rx_eq_ugl_state, 0x9, 0, 3);

/* tx_ugl_state
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, tx_ugl_state, 0xb, 0, 4);

/* recovery_retries_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, recovery_retries_cnt, 0xc, 4, 4);

/* imem_loading_retries
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, imem_loading_retries, 0xc, 0, 3);

/* sd_hits_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, sd_hits_cnt, 0xd, 0, 8);

/* sd_iter_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, sd_iter_cnt, 0xe, 0, 8);

/* rd_iter_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, rd_iter_cnt, 0xf, 0, 8);

/* ae_state
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, ae_state, 0x11, 0, 5);

/* rx_init_abort_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, rx_init_abort_cnt, 0x12, 0, 8);

/* rx_init_done_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, rx_init_done_cnt, 0x13, 0, 8);

/* cdr_abort_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, cdr_abort_cnt, 0x14, 0, 8);

/* cdr_done_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, cdr_done_cnt, 0x15, 0, 8);

/* cal_abort_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, cal_abort_cnt, 0x16, 0, 8);

/* cal_done_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, cal_done_cnt, 0x17, 0, 8);

/* eq_abort_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, eq_abort_cnt, 0x18, 0, 8);

/* eq_done_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, eq_done_cnt, 0x19, 0, 8);

/* eom_abort_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, eom_abort_cnt, 0x1a, 0, 8);

/* eom_done_cnt
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, eom_done_cnt, 0x1b, 0, 8);

/* err_ind_it_3
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, err_ind_it_3, 0x20, 0, 4);

/* err_ind_it_2
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, err_ind_it_2, 0x21, 0, 4);

/* err_ind_it_1
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, err_ind_it_1, 0x22, 0, 4);

/* err_ind_it_0
 * Access: RO
 */
MLXSW_ITEM8(reg, slsir, err_ind_it_0, 0x23, 0, 4);

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

/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, prei, status, 0x3, 0, 4);

/* error_type_oper
 * Access: RO
 */
MLXSW_ITEM8(reg, prei, error_type_oper, 0x4, 0, 4);

/* error_type_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, prei, error_type_cap, 0x6, 0, 8);

/* error_type_admin
 * Access: RW
 */
MLXSW_ITEM8(reg, prei, error_type_admin, 0x7, 0, 8);

/* error_injection_time
 * Access: RW
 */
MLXSW_ITEM32(reg, prei, error_injection_time, 0x8, 12, 16);

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
MLXSW_ITEM8(reg, mocs, clear, 0x5, 0, 2);

/* opcode
 * Access: WO
 */
MLXSW_ITEM8(reg, mocs, opcode, 0x6, 0, 1);

/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, mocs, status, 0x7, 0, 2);

/* event_tid
 * Access: RW
 */
MLXSW_ITEM64(reg, mocs, event_tid, 0x8, 0, 64);

/* entry_mocs_ppcnt_port_mask
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mocs, entry_mocs_ppcnt_port_mask, 0x20, 0, 32, 4, 0, false);

/* entry_mocs_ppcnt_grp_mask
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mocs, entry_mocs_ppcnt_grp_mask, 0x60, 0, 32, 4, 0, false);

/* entry_mocs_ppcnt_tc_mask
 * Access: RW
 */
MLXSW_ITEM32(reg, mocs, entry_mocs_ppcnt_tc_mask, 0x70, 0, 32);

/* entry_mocs_ppcnt_prio_mask
 * Access: RW
 */
MLXSW_ITEM16(reg, mocs, entry_mocs_ppcnt_prio_mask, 0x74, 0, 16);

/* entry_mocs_ppcnt_rx_buffer_mask
 * Access: RW
 */
MLXSW_ITEM16(reg, mocs, entry_mocs_ppcnt_rx_buffer_mask, 0x76, 0, 16);

/* entry_mocs_ppcnt_grp_prf
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mocs, entry_mocs_ppcnt_grp_prf, 0x80, 0, 32, 4, 0, false);

/* entry_mocs_mgpcb_flush
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_mgpcb_flush, 0x20, 7, 1);

/* entry_mocs_mgpcb_num_rec
 * Access: RW
 */
MLXSW_ITEM32(reg, mocs, entry_mocs_mgpcb_num_rec, 0x20, 0, 24);

/* entry_mocs_mgpcb_counter_index_base
 * Access: RW
 */
MLXSW_ITEM32(reg, mocs, entry_mocs_mgpcb_counter_index_base, 0x24, 0, 24);

/* entry_mocs_pbsr_port_mask
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mocs, entry_mocs_pbsr_port_mask, 0x20, 0, 32, 4, 0, false);

/* entry_mocs_sbsrd_curr
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_sbsrd_curr, 0x20, 7, 1);

/* entry_mocs_sbsrd_snap
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_sbsrd_snap, 0x20, 6, 1);

/* entry_mocs_sbsrd_cells
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_sbsrd_cells, 0x20, 5, 1);

/* entry_mocs_sbsrd_desc
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_sbsrd_desc, 0x20, 4, 1);

/* entry_mocs_ceer_port_mask
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mocs, entry_mocs_ceer_port_mask, 0x20, 0, 32, 4, 0, false);

/* entry_mocs_mafbi_flush
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_mafbi_flush, 0x20, 7, 1);

/* entry_mocs_mafbi_type
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_mafbi_type, 0x20, 4, 2);

/* entry_mocs_mafbi_num_rec
 * Access: RW
 */
MLXSW_ITEM32(reg, mocs, entry_mocs_mafbi_num_rec, 0x20, 0, 24);

/* entry_mocs_mafbi_counter_index_base
 * Access: RW
 */
MLXSW_ITEM32(reg, mocs, entry_mocs_mafbi_counter_index_base, 0x24, 0, 24);

/* entry_mocs_fsed_op
 * Access: OP
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_fsed_op, 0x22, 0, 2);

/* entry_mocs_fsed_filter_fields
 * Access: OP
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_fsed_filter_fields, 0x23, 0, 4);

/* entry_mocs_fsed_group_id
 * Access: INDEX
 */
MLXSW_ITEM16(reg, mocs, entry_mocs_fsed_group_id, 0x24, 0, 16);

/* entry_mocs_fsed_entry_sem_s
 * Access: OP
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_fsed_entry_sem_s, 0x26, 1, 1);

/* entry_mocs_fsed_entry_activity
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_fsed_entry_activity, 0x26, 0, 1);

/* entry_mocs_fsed_entry_partition_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_fsed_entry_partition_id, 0x27, 0, 3);

/* entry_mocs_fsed_num_rec
 * Access: RW
 */
MLXSW_ITEM32(reg, mocs, entry_mocs_fsed_num_rec, 0x28, 0, 20);

/* entry_mocs_fsed_nt
 * Access: OP
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_fsed_nt, 0x2f, 0, 1);

/* entry_mocs_usacn_port_mask
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mocs, entry_mocs_usacn_port_mask, 0x20, 0, 32, 4, 0, false);

/* entry_mocs_usacn_side
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_usacn_side, 0x63, 0, 4);

/* entry_mocs_usacn_sadb_entry_index_base
 * Access: RW
 */
MLXSW_ITEM16(reg, mocs, entry_mocs_usacn_sadb_entry_index_base, 0x64, 0, 16);

/* entry_mocs_usacn_num_rec
 * Access: RW
 */
MLXSW_ITEM16(reg, mocs, entry_mocs_usacn_num_rec, 0x66, 0, 16);

/* entry_mocs_utcc_port_mask
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mocs, entry_mocs_utcc_port_mask, 0x20, 0, 32, 4, 0, false);

/* entry_mocs_utcc_side
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_utcc_side, 0x63, 0, 4);

/* entry_mocs_utcc_utcam_counter_idx_base
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_utcc_utcam_counter_idx_base, 0x66, 0, 8);

/* entry_mocs_utcc_num_rec
 * Access: RW
 */
MLXSW_ITEM8(reg, mocs, entry_mocs_utcc_num_rec, 0x67, 0, 8);

/* entry_mocs_upcnt_port_mask
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mocs, entry_mocs_upcnt_port_mask, 0x20, 0, 32, 4, 0, false);

/* entry_mocs_mofrb_num_rec
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, mocs, entry_mocs_mofrb_num_rec, MLXSW_MOCS_FLOW_ESTIMATOR_RECORD_BASE_LEN + 2, 0, 11, MLXSW_MOCS_FLOW_ESTIMATOR_RECORD_REC_LEN, 0, false);

/* entry_mocs_mofrb_counter_index_base
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mocs, entry_mocs_mofrb_counter_index_base, MLXSW_MOCS_FLOW_ESTIMATOR_RECORD_BASE_LEN, 0, 24, MLXSW_MOCS_FLOW_ESTIMATOR_RECORD_REC_LEN, 4, false);

/* ipac
 * ----
 *
 */
/* profile_index
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ipac, profile_index, 0x2, 0, 4);

/* opcode
 * Access: WO
 */
MLXSW_ITEM8(reg, ipac, opcode, 0x6, 0, 2);

/* status
 * Access: RO
 */
MLXSW_ITEM8(reg, ipac, status, 0x7, 0, 2);

/* port_mask
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, ipac, port_mask, 0x20, 0, 32, 4, 0, false);

/* log_op_time
 * Access: RO
 */
MLXSW_ITEM16(reg, ipac, log_op_time, 0xa2, 0, 16);

/* log_op_registers
 * Access: RO
 */
MLXSW_ITEM32(reg, ipac, log_op_registers, 0xa4, 0, 32);

/* error_lp_msb
 * Access: RO
 */
MLXSW_ITEM8(reg, ipac, error_lp_msb, 0xa8, 0, 2);

/* error_local_port
 * Access: RO
 */
MLXSW_ITEM8(reg, ipac, error_local_port, 0xa9, 0, 8);

/* error_register_id
 * Access: RO
 */
MLXSW_ITEM16(reg, ipac, error_register_id, 0xaa, 0, 16);

/* error_status
 * Access: RW
 */
MLXSW_ITEM8(reg, ipac, error_status, 0xad, 0, 7);

/* error_entry_index
 * Access: RO
 */
MLXSW_ITEM16(reg, ipac, error_entry_index, 0xae, 0, 16);

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
MLXSW_ITEM16(reg, pllp, label_port, 0x2, 0, 10);

/* ipil_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, pllp, ipil_stat, 0x4, 0, 4);

/* split_stat
 * Access: RO
 */
MLXSW_ITEM8(reg, pllp, split_stat, 0x5, 0, 4);

/* ipil_num
 * Access: RO
 */
MLXSW_ITEM8(reg, pllp, ipil_num, 0x6, 0, 4);

/* split_num
 * Access: RO
 */
MLXSW_ITEM8(reg, pllp, split_num, 0x7, 0, 4);

/* max_ports_width
 * Access: RO
 */
MLXSW_ITEM8(reg, pllp, max_ports_width, 0x9, 0, 4);

/* slot_num
 * Access: RO
 */
MLXSW_ITEM8(reg, pllp, slot_num, 0xb, 0, 4);

/* spad
 * ----
 *
 */
/* base_mac
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, spad, base_mac, 0x2, 6);

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

/* action_remote_action_trap_action
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcmle, action_remote_action_trap_action, 0x20, 4, 4);

/* action_remote_action_trap_id
 * Access: RW
 */
MLXSW_ITEM16(reg, rlcmle, action_remote_action_trap_id, 0x22, 0, 9);

/* action_remote_action_adjacency_index
 * Access: RW
 */
MLXSW_ITEM32(reg, rlcmle, action_remote_action_adjacency_index, 0x24, 0, 24);

/* action_remote_action_ecmp_size
 * Access: RW
 */
MLXSW_ITEM16(reg, rlcmle, action_remote_action_ecmp_size, 0x2a, 0, 13);

/* action_local_action_trap_action
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcmle, action_local_action_trap_action, 0x20, 4, 4);

/* action_local_action_trap_id
 * Access: RW
 */
MLXSW_ITEM16(reg, rlcmle, action_local_action_trap_id, 0x22, 0, 9);

/* action_local_action_local_erif
 * Access: RW
 */
MLXSW_ITEM16(reg, rlcmle, action_local_action_local_erif, 0x26, 0, 16);

/* action_ip2me_trap_action
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcmle, action_ip2me_trap_action, 0x20, 4, 4);

/* action_ip2me_v
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcmle, action_ip2me_v, 0x24, 7, 1);

/* action_ip2me_tunnel_ptr
 * Access: RW
 */
MLXSW_ITEM32(reg, rlcmle, action_ip2me_tunnel_ptr, 0x24, 0, 24);

/* counter_set_type
 * Access: RW
 */
MLXSW_ITEM8(reg, rlcmle, counter_set_type, 0x34, 0, 8);

/* counter_index
 * Access: RW
 */
MLXSW_ITEM32(reg, rlcmle, counter_index, 0x34, 0, 24);

/* sbsnt
 * -----
 *
 */
/* take
 * Access: OP
 */
MLXSW_ITEM8(reg, sbsnt, take, 0x3, 0, 2);

/* rarft
 * -----
 *
 */
/* arft_index
 * Access: INDEX
 */
MLXSW_ITEM32(reg, rarft, arft_index, 0x0, 0, 20);

/* arft_entry_in_row
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rarft, arft_entry_in_row, 0x7, 0, 4);

/* valid
 * Access: RW
 */
MLXSW_ITEM8(reg, rarft, valid, 0x9, 0, 1);

/* lp_msb
 * Access: RW
 */
MLXSW_ITEM8(reg, rarft, lp_msb, 0xa, 0, 2);

/* local_port
 * Access: RW
 */
MLXSW_ITEM8(reg, rarft, local_port, 0xb, 0, 8);

/* ar_prof_id
 * Access: RW
 */
MLXSW_ITEM8(reg, rarft, ar_prof_id, 0xf, 0, 4);

/* sbgcr
 * -----
 *
 */
/* cong_fp
 * Access: RW
 */
MLXSW_ITEM8(reg, sbgcr, cong_fp, 0x3, 4, 1);

/* tele_entity
 * Access: RW
 */
MLXSW_ITEM8(reg, sbgcr, tele_entity, 0x3, 0, 2);

/* hba
 * Access: RW
 */
MLXSW_ITEM8(reg, sbgcr, hba, 0xb, 0, 1);

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

/* data_mcqi_cap_supported_info_bitmask
 * Access: RO
 */
MLXSW_ITEM32(reg, mcqi, data_mcqi_cap_supported_info_bitmask, 0x18, 0, 32);

/* data_mcqi_cap_component_size
 * Access: RO
 */
MLXSW_ITEM32(reg, mcqi, data_mcqi_cap_component_size, 0x1c, 0, 32);

/* data_mcqi_cap_max_component_size
 * Access: RO
 */
MLXSW_ITEM32(reg, mcqi, data_mcqi_cap_max_component_size, 0x20, 0, 32);

/* data_mcqi_cap_log_mcda_word_size
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_cap_log_mcda_word_size, 0x24, 4, 4);

/* data_mcqi_cap_mcda_max_write_size
 * Access: RO
 */
MLXSW_ITEM16(reg, mcqi, data_mcqi_cap_mcda_max_write_size, 0x26, 0, 16);

/* data_mcqi_cap_rd_en
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_cap_rd_en, 0x28, 7, 1);

/* data_mcqi_cap_signed_updates_only
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_cap_signed_updates_only, 0x28, 6, 1);

/* data_mcqi_cap_match_chip_id
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_cap_match_chip_id, 0x28, 5, 1);

/* data_mcqi_cap_match_psid
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_cap_match_psid, 0x28, 4, 1);

/* data_mcqi_cap_check_user_timestamp
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_cap_check_user_timestamp, 0x28, 3, 1);

/* data_mcqi_cap_match_base_guid_mac
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_cap_match_base_guid_mac, 0x28, 2, 1);

/* data_mcqi_version_build_time_valid
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_version_build_time_valid, 0x18, 5, 1);

/* data_mcqi_version_user_defined_time_valid
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_version_user_defined_time_valid, 0x18, 4, 1);

/* data_mcqi_version_version_string_length
 * Access: RW
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_version_version_string_length, 0x1b, 0, 8);

/* data_mcqi_version_version
 * Access: RW
 */
MLXSW_ITEM32(reg, mcqi, data_mcqi_version_version, 0x1c, 0, 32);

/* data_mcqi_version_build_time
 * Access: RW
 */
MLXSW_ITEM64(reg, mcqi, data_mcqi_version_build_time, 0x20, 0, 64);

/* data_mcqi_version_user_defined_time
 * Access: RW
 */
MLXSW_ITEM64(reg, mcqi, data_mcqi_version_user_defined_time, 0x28, 0, 64);

/* data_mcqi_version_build_tool_version
 * Access: RW
 */
MLXSW_ITEM32(reg, mcqi, data_mcqi_version_build_tool_version, 0x30, 0, 32);

/* data_mcqi_version_version_string
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, mcqi, data_mcqi_version_version_string, 0x38, 92);

/* data_mcqi_activation_method_self_activation
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_activation_method_self_activation, 0x1b, 6, 1);

/* data_mcqi_activation_method_pending_server_ac_power_cycle
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_activation_method_pending_server_ac_power_cycle, 0x1b, 5, 1);

/* data_mcqi_activation_method_pending_server_dc_power_cycle
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_activation_method_pending_server_dc_power_cycle, 0x1b, 4, 1);

/* data_mcqi_activation_method_pending_server_reboot
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_activation_method_pending_server_reboot, 0x1b, 3, 1);

/* data_mcqi_activation_method_pending_fw_reset
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_activation_method_pending_fw_reset, 0x1b, 2, 1);

/* data_mcqi_activation_method_auto_activate
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_activation_method_auto_activate, 0x1b, 1, 1);

/* data_mcqi_activation_method_all_hosts_sync
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_activation_method_all_hosts_sync, 0x1b, 0, 1);

/* data_mcqi_linkx_properties_fw_image_info_bitmap
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_linkx_properties_fw_image_info_bitmap, 0x19, 0, 8);

/* data_mcqi_linkx_properties_fw_image_status_bitmap
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_linkx_properties_fw_image_status_bitmap, 0x1b, 0, 8);

/* data_mcqi_linkx_properties_image_a_major
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_linkx_properties_image_a_major, 0x1e, 0, 8);

/* data_mcqi_linkx_properties_image_a_minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_linkx_properties_image_a_minor, 0x1f, 0, 8);

/* data_mcqi_linkx_properties_image_a_subminor
 * Access: RO
 */
MLXSW_ITEM16(reg, mcqi, data_mcqi_linkx_properties_image_a_subminor, 0x22, 0, 16);

/* data_mcqi_linkx_properties_image_b_major
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_linkx_properties_image_b_major, 0x26, 0, 8);

/* data_mcqi_linkx_properties_image_b_minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_linkx_properties_image_b_minor, 0x27, 0, 8);

/* data_mcqi_linkx_properties_image_b_subminor
 * Access: RO
 */
MLXSW_ITEM16(reg, mcqi, data_mcqi_linkx_properties_image_b_subminor, 0x2a, 0, 16);

/* data_mcqi_linkx_properties_factory_image_major
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_linkx_properties_factory_image_major, 0x2e, 0, 8);

/* data_mcqi_linkx_properties_factory_image_minor
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_linkx_properties_factory_image_minor, 0x2f, 0, 8);

/* data_mcqi_linkx_properties_factory_image_subminor
 * Access: RO
 */
MLXSW_ITEM16(reg, mcqi, data_mcqi_linkx_properties_factory_image_subminor, 0x32, 0, 16);

/* data_mcqi_linkx_properties_activation_type
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_linkx_properties_activation_type, 0x36, 2, 4);

/* data_mcqi_linkx_properties_management_interface_protocol
 * Access: RO
 */
MLXSW_ITEM8(reg, mcqi, data_mcqi_linkx_properties_management_interface_protocol, 0x37, 0, 6);

/* data_mcqi_linkx_properties_vendor_sn
 * Access: RO
 */
MLXSW_ITEM16(reg, mcqi, data_mcqi_linkx_properties_vendor_sn, 0x3a, 0, 16);

/* rargcr
 * ------
 *
 */
/* arft_index_base
 * Access: RW
 */
MLXSW_ITEM32(reg, rargcr, arft_index_base, 0x0, 0, 20);

/* arft_index_size
 * Access: RW
 */
MLXSW_ITEM16(reg, rargcr, arft_index_size, 0x6, 0, 16);

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

/* rarsr
 * -----
 *
 */
/* ar_srf
 * Access: RW
 */
MLXSW_ITEM16(reg, rarsr, ar_srf, 0x2, 0, 16);

/* ar_srt
 * Access: RW
 */
MLXSW_ITEM16(reg, rarsr, ar_srt, 0x6, 0, 16);

/* usak
 * ----
 *
 */
/* uengine
 * Access: INDEX
 */
MLXSW_ITEM16(reg, usak, uengine, 0x0, 0, 16);

/* sadb_entry_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, usak, sadb_entry_index, 0x2, 0, 16);

/* sa_key
 * Access: WO
 */
MLXSW_ITEM32_INDEXED(reg, usak, sa_key, 0x4, 0, 32, 4, 0, false);

/* utcc
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, utcc, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, utcc, lp_msb, 0x2, 4, 2);

/* side
 * Access: INDEX
 */
MLXSW_ITEM8(reg, utcc, side, 0x2, 0, 4);

/* clear_bitmap
 * Access: OP
 */
MLXSW_ITEM16(reg, utcc, clear_bitmap, 0x6, 0, 16);

/* counter
 * Access: RO
 */
MLXSW_ITEM64_INDEXED(reg, utcc, counter, 0x8, 0, 64, 8, 0, false);

/* ratrb
 * -----
 *
 */
/* v
 * Access: OP
 */
MLXSW_ITEM8(reg, ratrb, v, 0x0, 7, 1);

/* adjacency_index
 * Access: INDEX
 */
MLXSW_ITEM32(reg, ratrb, adjacency_index, 0x0, 0, 24);

/* num_rec
 * Access: OP
 */
MLXSW_ITEM8(reg, ratrb, num_rec, 0x7, 0, 8);

/* trap_action
 * Access: WO
 */
MLXSW_ITEM8(reg, ratrb, trap_action, 0x8, 4, 4);

/* trap_id
 * Access: WO
 */
MLXSW_ITEM16(reg, ratrb, trap_id, 0xa, 0, 9);

/* type
 * Access: WO
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, type, MLXSW_RATRB_RECORD_BASE_LEN, 4, 4, MLXSW_RATRB_RECORD_REC_LEN, 0, false);

/* size
 * Access: WO
 */
MLXSW_ITEM16_INDEXED(reg, ratrb, size, MLXSW_RATRB_RECORD_BASE_LEN, 0, 12, MLXSW_RATRB_RECORD_REC_LEN, 0, false);

/* egress_router_interface
 * Access: WO
 */
MLXSW_ITEM16_INDEXED(reg, ratrb, egress_router_interface, MLXSW_RATRB_RECORD_BASE_LEN + 2, 0, 16, MLXSW_RATRB_RECORD_REC_LEN, 0, false);

/* counter_set_type
 * Access: WO
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, counter_set_type, MLXSW_RATRB_RECORD_BASE_LEN, 0, 8, MLXSW_RATRB_RECORD_REC_LEN, 4, false);

/* counter_index
 * Access: WO
 */
MLXSW_ITEM32_INDEXED(reg, ratrb, counter_index, MLXSW_RATRB_RECORD_BASE_LEN, 0, 24, MLXSW_RATRB_RECORD_REC_LEN, 4, false);

/* adjacency_parameters_eth_adjacency_destination_mac
 * Access: RW
 */
MLXSW_ITEM_BUF_INDEXED(reg, ratrb, adjacency_parameters_eth_adjacency_destination_mac, MLXSW_RATRB_RECORD_BASE_LEN, 0x6, 0x20, 10);

/* adjacency_parameters_mpls_adjacency_nhlfe_ptr
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, ratrb, adjacency_parameters_mpls_adjacency_nhlfe_ptr, MLXSW_RATRB_RECORD_BASE_LEN, 0, 24, MLXSW_RATRB_RECORD_REC_LEN, 8, false);

/* adjacency_parameters_mpls_adjacency_tqos_profile
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_mpls_adjacency_tqos_profile, MLXSW_RATRB_RECORD_BASE_LEN, 0, 4, MLXSW_RATRB_RECORD_REC_LEN, 12, false);

/* adjacency_parameters_mpls_adjacency_ecmp_size
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, ratrb, adjacency_parameters_mpls_adjacency_ecmp_size, MLXSW_RATRB_RECORD_BASE_LEN + 2, 0, 13, MLXSW_RATRB_RECORD_REC_LEN, 12, false);

/* adjacency_parameters_mpls_adjacency_underlay_router_interface
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, ratrb, adjacency_parameters_mpls_adjacency_underlay_router_interface, MLXSW_RATRB_RECORD_BASE_LEN + 2, 0, 16, MLXSW_RATRB_RECORD_REC_LEN, 24, false);

/* adjacency_parameters_ipinip_encap_adjacency_ipip_type
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_ipinip_encap_adjacency_ipip_type, MLXSW_RATRB_RECORD_BASE_LEN + 1, 0, 4, MLXSW_RATRB_RECORD_REC_LEN, 8, false);

/* adjacency_parameters_ipinip_encap_adjacency_tqos_profile_en
 * Access: OP
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_ipinip_encap_adjacency_tqos_profile_en, MLXSW_RATRB_RECORD_BASE_LEN, 7, 1, MLXSW_RATRB_RECORD_REC_LEN, 12, false);

/* adjacency_parameters_ipinip_encap_adjacency_tqos_profile
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_ipinip_encap_adjacency_tqos_profile, MLXSW_RATRB_RECORD_BASE_LEN, 0, 4, MLXSW_RATRB_RECORD_REC_LEN, 12, false);

/* adjacency_parameters_ipinip_encap_adjacency_uirif_v
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_ipinip_encap_adjacency_uirif_v, MLXSW_RATRB_RECORD_BASE_LEN + 1, 0, 1, MLXSW_RATRB_RECORD_REC_LEN, 12, false);

/* adjacency_parameters_ipinip_encap_adjacency_uirif
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, ratrb, adjacency_parameters_ipinip_encap_adjacency_uirif, MLXSW_RATRB_RECORD_BASE_LEN + 2, 0, 16, MLXSW_RATRB_RECORD_REC_LEN, 12, false);

/* adjacency_parameters_ipinip_encap_adjacency_ipv4_udip
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, ratrb, adjacency_parameters_ipinip_encap_adjacency_ipv4_udip, MLXSW_RATRB_RECORD_BASE_LEN, 0, 32, MLXSW_RATRB_RECORD_REC_LEN, 16, false);

/* adjacency_parameters_ipinip_encap_adjacency_ipv6_ptr
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, ratrb, adjacency_parameters_ipinip_encap_adjacency_ipv6_ptr, MLXSW_RATRB_RECORD_BASE_LEN, 0, 24, MLXSW_RATRB_RECORD_REC_LEN, 20, false);

/* adjacency_parameters_l3_generic_encap_adjacency_u_ip_ver
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_l3_generic_encap_adjacency_u_ip_ver, MLXSW_RATRB_RECORD_BASE_LEN + 1, 0, 4, MLXSW_RATRB_RECORD_REC_LEN, 8, false);

/* adjacency_parameters_l3_generic_encap_adjacency_emt_pointer
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_l3_generic_encap_adjacency_emt_pointer, MLXSW_RATRB_RECORD_BASE_LEN + 3, 0, 8, MLXSW_RATRB_RECORD_REC_LEN, 8, false);

/* adjacency_parameters_l3_generic_encap_adjacency_tqos_profile
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_l3_generic_encap_adjacency_tqos_profile, MLXSW_RATRB_RECORD_BASE_LEN, 0, 4, MLXSW_RATRB_RECORD_REC_LEN, 12, false);

/* adjacency_parameters_l3_generic_encap_adjacency_uirif
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, ratrb, adjacency_parameters_l3_generic_encap_adjacency_uirif, MLXSW_RATRB_RECORD_BASE_LEN + 2, 0, 16, MLXSW_RATRB_RECORD_REC_LEN, 12, false);

/* adjacency_parameters_l3_generic_encap_adjacency_ipv4_udip
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, ratrb, adjacency_parameters_l3_generic_encap_adjacency_ipv4_udip, MLXSW_RATRB_RECORD_BASE_LEN, 0, 32, MLXSW_RATRB_RECORD_REC_LEN, 16, false);

/* adjacency_parameters_l3_generic_encap_adjacency_ipv6_ptr
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, ratrb, adjacency_parameters_l3_generic_encap_adjacency_ipv6_ptr, MLXSW_RATRB_RECORD_BASE_LEN, 0, 24, MLXSW_RATRB_RECORD_REC_LEN, 20, false);

/* adjacency_parameters_l3_generic_encap_adjacency_cbset_x_select
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_l3_generic_encap_adjacency_cbset_x_select, MLXSW_RATRB_RECORD_BASE_LEN, 0, 3, MLXSW_RATRB_RECORD_REC_LEN, 24, false);

/* adjacency_parameters_l3_generic_encap_adjacency_cbset_y_select
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_l3_generic_encap_adjacency_cbset_y_select, MLXSW_RATRB_RECORD_BASE_LEN + 1, 0, 3, MLXSW_RATRB_RECORD_REC_LEN, 24, false);

/* adjacency_parameters_l3_generic_encap_adjacency_cbset_x_set_en
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_l3_generic_encap_adjacency_cbset_x_set_en, MLXSW_RATRB_RECORD_BASE_LEN + 3, 1, 1, MLXSW_RATRB_RECORD_REC_LEN, 24, false);

/* adjacency_parameters_l3_generic_encap_adjacency_cbset_y_set_en
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_l3_generic_encap_adjacency_cbset_y_set_en, MLXSW_RATRB_RECORD_BASE_LEN + 3, 0, 1, MLXSW_RATRB_RECORD_REC_LEN, 24, false);

/* adjacency_parameters_l3_generic_encap_adjacency_cbset_x_val
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, ratrb, adjacency_parameters_l3_generic_encap_adjacency_cbset_x_val, MLXSW_RATRB_RECORD_BASE_LEN, 0, 16, MLXSW_RATRB_RECORD_REC_LEN, 28, false);

/* adjacency_parameters_l3_generic_encap_adjacency_cbset_y_val
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, ratrb, adjacency_parameters_l3_generic_encap_adjacency_cbset_y_val, MLXSW_RATRB_RECORD_BASE_LEN + 2, 0, 16, MLXSW_RATRB_RECORD_REC_LEN, 28, false);

/* adjacency_parameters_ip_gw_adjacency_new_header_type
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_ip_gw_adjacency_new_header_type, MLXSW_RATRB_RECORD_BASE_LEN, 0, 4, MLXSW_RATRB_RECORD_REC_LEN, 8, false);

/* adjacency_parameters_ip_gw_adjacency_irif
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, ratrb, adjacency_parameters_ip_gw_adjacency_irif, MLXSW_RATRB_RECORD_BASE_LEN + 2, 0, 16, MLXSW_RATRB_RECORD_REC_LEN, 8, false);

/* adjacency_parameters_ip_gw_adjacency_qos_profile
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_ip_gw_adjacency_qos_profile, MLXSW_RATRB_RECORD_BASE_LEN, 0, 4, MLXSW_RATRB_RECORD_REC_LEN, 12, false);

/* adjacency_parameters_ip_gw_adjacency_new_ipv4_udip
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, ratrb, adjacency_parameters_ip_gw_adjacency_new_ipv4_udip, MLXSW_RATRB_RECORD_BASE_LEN, 0, 32, MLXSW_RATRB_RECORD_REC_LEN, 16, false);

/* adjacency_parameters_ip_gw_adjacency_new_ipv6_ptr
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, ratrb, adjacency_parameters_ip_gw_adjacency_new_ipv6_ptr, MLXSW_RATRB_RECORD_BASE_LEN, 0, 24, MLXSW_RATRB_RECORD_REC_LEN, 20, false);

/* adjacency_parameters_ip_gw_adjacency_exp_l3
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_ip_gw_adjacency_exp_l3, MLXSW_RATRB_RECORD_BASE_LEN + 3, 0, 2, MLXSW_RATRB_RECORD_REC_LEN, 24, false);

/* adjacency_parameters_relookup_ecmp_adjacency_next_adjacency_ptr
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, ratrb, adjacency_parameters_relookup_ecmp_adjacency_next_adjacency_ptr, MLXSW_RATRB_RECORD_BASE_LEN, 0, 24, MLXSW_RATRB_RECORD_REC_LEN, 8, false);

/* adjacency_parameters_relookup_ecmp_adjacency_next_ecmp_size
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, ratrb, adjacency_parameters_relookup_ecmp_adjacency_next_ecmp_size, MLXSW_RATRB_RECORD_BASE_LEN + 2, 0, 13, MLXSW_RATRB_RECORD_REC_LEN, 12, false);

/* adjacency_parameters_relookup_ecmp_adjacency_rd
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_relookup_ecmp_adjacency_rd, MLXSW_RATRB_RECORD_BASE_LEN + 1, 0, 1, MLXSW_RATRB_RECORD_REC_LEN, 16, false);

/* adjacency_parameters_relookup_ecmp_adjacency_rehash_seed
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, ratrb, adjacency_parameters_relookup_ecmp_adjacency_rehash_seed, MLXSW_RATRB_RECORD_BASE_LEN + 2, 0, 16, MLXSW_RATRB_RECORD_REC_LEN, 16, false);

/* adjacency_parameters_relookup_lpm_adjacency_virtual_router
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, ratrb, adjacency_parameters_relookup_lpm_adjacency_virtual_router, MLXSW_RATRB_RECORD_BASE_LEN + 2, 0, 16, MLXSW_RATRB_RECORD_REC_LEN, 8, false);

/* adjacency_parameters_relookup_lpm_adjacency_rd
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, ratrb, adjacency_parameters_relookup_lpm_adjacency_rd, MLXSW_RATRB_RECORD_BASE_LEN + 1, 0, 1, MLXSW_RATRB_RECORD_REC_LEN, 16, false);

/* adjacency_parameters_relookup_lpm_adjacency_rehash_seed
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, ratrb, adjacency_parameters_relookup_lpm_adjacency_rehash_seed, MLXSW_RATRB_RECORD_BASE_LEN + 2, 0, 16, MLXSW_RATRB_RECORD_REC_LEN, 16, false);

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

/* nve_udp_sport_suffix
 * Access: RW
 */
MLXSW_ITEM8(reg, tngcr, nve_udp_sport_suffix, 0x13, 0, 8);

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

/* qtttl
 * -----
 *
 */
/* tqos_profile
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qtttl, tqos_profile, 0x3, 0, 4);

/* decap_ttl
 * Access: RW
 */
MLXSW_ITEM8(reg, qtttl, decap_ttl, 0x5, 0, 2);

/* enc_ttlc
 * Access: RW
 */
MLXSW_ITEM8(reg, qtttl, enc_ttlc, 0x6, 0, 1);

/* enc_ttl_uc
 * Access: RW
 */
MLXSW_ITEM8(reg, qtttl, enc_ttl_uc, 0x7, 0, 8);

/* enc_ttl_mc
 * Access: RW
 */
MLXSW_ITEM8(reg, qtttl, enc_ttl_mc, 0xb, 0, 8);

/* ptasv2
 * ------
 *
 */
/* version
 * Access: RO
 */
MLXSW_ITEM8(reg, ptasv2, version, 0x0, 0, 4);

/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ptasv2, local_port, 0x1, 0, 8);

/* pnat
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ptasv2, pnat, 0x2, 6, 2);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ptasv2, lp_msb, 0x2, 4, 2);

/* ib_cfg_delaytimeout_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, ptasv2, ib_cfg_delaytimeout_cap, 0x2, 2, 1);

/* ib_cfg_delaytimeout
 * Access: RW
 */
MLXSW_ITEM8(reg, ptasv2, ib_cfg_delaytimeout, 0x2, 0, 2);

/* ig_dme_mod_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, ptasv2, ig_dme_mod_cap, 0x3, 3, 1);

/* ig_dme_mod_admin
 * Access: RW
 */
MLXSW_ITEM8(reg, ptasv2, ig_dme_mod_admin, 0x3, 2, 1);

/* force_an_cap
 * Access: RO
 */
MLXSW_ITEM8(reg, ptasv2, force_an_cap, 0x3, 1, 1);

/* force_an_admin
 * Access: RW
 */
MLXSW_ITEM8(reg, ptasv2, force_an_admin, 0x3, 0, 1);

/* page_data_ptasv2_28nm_tuning_type_support
 * Access: RO
 */
MLXSW_ITEM8(reg, ptasv2, page_data_ptasv2_28nm_tuning_type_support, 0x9, 0, 4);

/* page_data_ptasv2_28nm_tuning_type_admin
 * Access: RW
 */
MLXSW_ITEM8(reg, ptasv2, page_data_ptasv2_28nm_tuning_type_admin, 0xb, 0, 4);

/* page_data_ptasv2_7nm_max_recovery_retries_en
 * Access: RW
 */
MLXSW_ITEM8(reg, ptasv2, page_data_ptasv2_7nm_max_recovery_retries_en, 0x8, 7, 1);

/* page_data_ptasv2_7nm_phy_count_linkup_delay
 * Access: RW
 */
MLXSW_ITEM8(reg, ptasv2, page_data_ptasv2_7nm_phy_count_linkup_delay, 0xa, 0, 2);

/* page_data_ptasv2_7nm_max_recovery_retries
 * Access: RW
 */
MLXSW_ITEM8(reg, ptasv2, page_data_ptasv2_7nm_max_recovery_retries, 0xb, 0, 4);

/* page_data_ptasv2_7nm_lt_tuning_support
 * Access: RO
 */
MLXSW_ITEM8(reg, ptasv2, page_data_ptasv2_7nm_lt_tuning_support, 0xd, 0, 8);

/* page_data_ptasv2_7nm_lt_tuning_admin
 * Access: RW
 */
MLXSW_ITEM8(reg, ptasv2, page_data_ptasv2_7nm_lt_tuning_admin, 0xf, 0, 8);

/* page_data_ptasv2_7nm_preset_mask
 * Access: RW
 */
MLXSW_ITEM8(reg, ptasv2, page_data_ptasv2_7nm_preset_mask, 0x13, 0, 5);

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

/* payload_prm_register_payload_status
 * Access: RO
 */
MLXSW_ITEM8(reg, mddt, payload_prm_register_payload_status, 0xc, 0, 8);

/* payload_prm_register_payload_method
 * Access: OP
 */
MLXSW_ITEM8(reg, mddt, payload_prm_register_payload_method, 0xd, 6, 2);

/* payload_prm_register_payload_register_id
 * Access: INDEX
 */
MLXSW_ITEM16(reg, mddt, payload_prm_register_payload_register_id, 0xe, 0, 16);

/* payload_prm_register_payload_register_data
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mddt, payload_prm_register_payload_register_data, 0x10, 0, 32, 4, 0, false);

/* payload_command_payload_data
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mddt, payload_command_payload_data, 0xc, 0, 32, 4, 0, false);

/* payload_crspace_access_payload_address
 * Access: WO
 */
MLXSW_ITEM32(reg, mddt, payload_crspace_access_payload_address, 0xc, 0, 32);

/* payload_crspace_access_payload_data
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mddt, payload_crspace_access_payload_data, 0x10, 0, 32, 4, 0, false);

/* msecq
 * -----
 *
 */
/* network_option
 * Access: RO
 */
MLXSW_ITEM8(reg, msecq, network_option, 0x6, 4, 2);

/* local_ssm_code
 * Access: RO
 */
MLXSW_ITEM8(reg, msecq, local_ssm_code, 0x6, 0, 4);

/* local_enhanced_ssm_code
 * Access: RO
 */
MLXSW_ITEM8(reg, msecq, local_enhanced_ssm_code, 0x7, 0, 8);

/* local_clock_identity
 * Access: RO
 */
MLXSW_ITEM64(reg, msecq, local_clock_identity, 0x8, 0, 64);

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

/* ralst
 * -----
 *
 */
/* root_bin
 * Access: RW
 */
MLXSW_ITEM8(reg, ralst, root_bin, 0x1, 0, 8);

/* tree_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ralst, tree_id, 0x3, 0, 8);

/* bin
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, ralst, bin, 0x4, 0, 16, 2, 0, false);

/* upcap
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upcap, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upcap, lp_msb, 0x2, 4, 2);

/* side
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upcap, side, 0x2, 0, 4);

/* device_type
 * Access: RO
 */
MLXSW_ITEM8(reg, upcap, device_type, 0x3, 0, 8);

/* gb
 * Access: RO
 */
MLXSW_ITEM8(reg, upcap, gb, 0x4, 7, 1);

/* crypto_selftest_failed
 * Access: RO
 */
MLXSW_ITEM8(reg, upcap, crypto_selftest_failed, 0x4, 6, 1);

/* mcs
 * Access: RO
 */
MLXSW_ITEM8(reg, upcap, mcs, 0x5, 0, 1);

/* uengine
 * Access: RO
 */
MLXSW_ITEM16(reg, upcap, uengine, 0x6, 0, 16);

/* mtppse
 * ------
 *
 */
/* pin
 * Access: INDEX
 */
MLXSW_ITEM8(reg, mtppse, pin, 0x3, 0, 8);

/* event_arm
 * Access: RW
 */
MLXSW_ITEM8(reg, mtppse, event_arm, 0x4, 7, 1);

/* event_generation_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, mtppse, event_generation_mode, 0x7, 0, 4);

/* mafbi
 * -----
 *
 */
/* type
 * Access: RO
 */
MLXSW_ITEM8(reg, mafbi, type, 0x0, 0, 2);

/* num_rec
 * Access: RO
 */
MLXSW_ITEM8(reg, mafbi, num_rec, 0x3, 0, 8);

/* entry_mafbi_entry_type0_counter_index
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mafbi, entry_mafbi_entry_type0_counter_index, MLXSW_MAFBI_RECORD_BASE_LEN, 0, 24, MLXSW_MAFBI_RECORD_REC_LEN, 0, false);

/* entry_mafbi_entry_type0_bytes_inc
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mafbi, entry_mafbi_entry_type0_bytes_inc, MLXSW_MAFBI_RECORD_BASE_LEN, 0, 32, MLXSW_MAFBI_RECORD_REC_LEN, 4, false);

/* entry_mafbi_entry_type0_packets_inc
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mafbi, entry_mafbi_entry_type0_packets_inc, MLXSW_MAFBI_RECORD_BASE_LEN, 0, 32, MLXSW_MAFBI_RECORD_REC_LEN, 8, false);

/* rarpc
 * -----
 *
 */
/* pc_default
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rarpc, pc_default, 0x2, 0, 1);

/* pc_entry
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rarpc, pc_entry, 0x3, 0, 8);

/* l4_inner
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpc, l4_inner, 0x6, 1, 1);

/* inner_must
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpc, inner_must, 0x6, 0, 1);

/* ar_packet_prof_id
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpc, ar_packet_prof_id, 0x7, 0, 4);

/* switch_prio
 * Access: RW
 */
MLXSW_ITEM16(reg, rarpc, switch_prio, 0x12, 0, 16);

/* l3_type
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpc, l3_type, 0x14, 0, 8);

/* inner_l3_type
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpc, inner_l3_type, 0x15, 0, 8);

/* l4_type
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpc, l4_type, 0x16, 0, 8);

/* inner_l4_type
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpc, inner_l4_type, 0x17, 0, 8);

/* bth_ar
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpc, bth_ar, 0x1a, 0, 2);

/* bth_opcode_msb
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpc, bth_opcode_msb, 0x1b, 0, 8);

/* bth_opcode_lsb
 * Access: RW
 */
MLXSW_ITEM32(reg, rarpc, bth_opcode_lsb, 0x1c, 0, 32);

/* inner_bth_ar
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpc, inner_bth_ar, 0x22, 0, 2);

/* inner_bth_opcode_msb
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpc, inner_bth_opcode_msb, 0x23, 0, 8);

/* inner_bth_opcode_lsb
 * Access: RW
 */
MLXSW_ITEM32(reg, rarpc, inner_bth_opcode_lsb, 0x24, 0, 32);

/* ingress_port
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, rarpc, ingress_port, 0x30, 0, 32, 4, 0, false);

/* port_range_min
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, rarpc, port_range_min, MLXSW_RARPC_L4PORT_CMP_BASE_LEN, 0, 16, MLXSW_RARPC_L4PORT_CMP_REC_LEN, 0, false);

/* port_range_max
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, rarpc, port_range_max, MLXSW_RARPC_L4PORT_CMP_BASE_LEN + 2, 0, 16, MLXSW_RARPC_L4PORT_CMP_REC_LEN, 0, false);

/* port_src
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, rarpc, port_src, MLXSW_RARPC_L4PORT_CMP_BASE_LEN + 3, 4, 1, MLXSW_RARPC_L4PORT_CMP_REC_LEN, 4, false);

/* comp_field
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, rarpc, comp_field, MLXSW_RARPC_L4PORT_CMP_BASE_LEN + 3, 0, 2, MLXSW_RARPC_L4PORT_CMP_REC_LEN, 4, false);

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

/* urcr
 * ----
 *
 */
/* uengine
 * Access: INDEX
 */
MLXSW_ITEM16(reg, urcr, uengine, 0x2, 0, 16);

/* src_region_id
 * Access: INDEX
 */
MLXSW_ITEM16(reg, urcr, src_region_id, 0x4, 0, 16);

/* src_offset
 * Access: INDEX
 */
MLXSW_ITEM16(reg, urcr, src_offset, 0x6, 0, 16);

/* oper
 * Access: OP
 */
MLXSW_ITEM8(reg, urcr, oper, 0x9, 0, 2);

/* size
 * Access: INDEX
 */
MLXSW_ITEM16(reg, urcr, size, 0xa, 0, 16);

/* dest_region_id
 * Access: INDEX
 */
MLXSW_ITEM16(reg, urcr, dest_region_id, 0xc, 0, 16);

/* dest_offset
 * Access: INDEX
 */
MLXSW_ITEM16(reg, urcr, dest_offset, 0xe, 0, 16);

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

/* record_tunnel_mc_ipv4_size
 * Access: RW
 */
MLXSW_ITEM8(reg, tnumt, record_tunnel_mc_ipv4_size, 0xb, 0, 3);

/* record_tunnel_mc_ipv4_udip
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, tnumt, record_tunnel_mc_ipv4_udip, 0xc, 0, 32, 4, 0, false);

/* record_tunnel_mc_ipv6_size
 * Access: RW
 */
MLXSW_ITEM8(reg, tnumt, record_tunnel_mc_ipv6_size, 0xb, 0, 3);

/* record_tunnel_mc_ipv6_udip_ptr
 * Access: 
 */
MLXSW_ITEM32_INDEXED(reg, tnumt, record_tunnel_mc_ipv6_udip_ptr, 0xc, 0, 24, 0x4, 0x0, false);

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

/* fshe
 * ----
 *
 */
/* op
 * Access: OP
 */
MLXSW_ITEM8(reg, fshe, op, 0x3, 0, 2);

/* hw_errors
 * Access: RO
 */
MLXSW_ITEM32(reg, fshe, hw_errors, 0x4, 0, 32);

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

/* rarpr
 * -----
 *
 */
/* ar_prof_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, rarpr, ar_prof_id, 0x3, 0, 4);

/* prof_mode
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpr, prof_mode, 0x7, 0, 4);

/* elph
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpr, elph, 0x8, 0, 1);

/* grade_thr_free
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpr, grade_thr_free, 0xa, 0, 3);

/* grade_thr_busy
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpr, grade_thr_busy, 0xb, 0, 3);

/* srf
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpr, srf, 0xf, 1, 1);

/* srt
 * Access: RW
 */
MLXSW_ITEM8(reg, rarpr, srt, 0xf, 0, 1);

/* time_bound_time
 * Access: RW
 */
MLXSW_ITEM16(reg, rarpr, time_bound_time, 0x12, 0, 10);

/* perar
 * -----
 *
 */
/* region_id
 * Access: INDEX
 */
MLXSW_ITEM16(reg, perar, region_id, 0x2, 0, 16);

/* hw_region
 * Access: RW
 */
MLXSW_ITEM16(reg, perar, hw_region, 0x6, 0, 16);

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

/* qtctm
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qtctm, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qtctm, lp_msb, 0x2, 4, 2);

/* mc
 * Access: RW
 */
MLXSW_ITEM8(reg, qtctm, mc, 0x7, 0, 1);

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

/* fsps
 * ----
 *
 */
/* tbm
 * Access: RO
 */
MLXSW_ITEM8(reg, fsps, tbm, 0x2, 1, 1);

/* tbw
 * Access: RO
 */
MLXSW_ITEM8(reg, fsps, tbw, 0x2, 0, 1);

/* partition_id
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fsps, partition_id, 0x3, 0, 3);

/* warning_threshold
 * Access: RO
 */
MLXSW_ITEM32(reg, fsps, warning_threshold, 0x4, 0, 19);

/* max_threshold
 * Access: RO
 */
MLXSW_ITEM32(reg, fsps, max_threshold, 0x8, 0, 19);

/* occupancy
 * Access: RO
 */
MLXSW_ITEM32(reg, fsps, occupancy, 0xc, 0, 32);

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

/* rarcc
 * -----
 *
 */
/* clr
 * Access: OP
 */
MLXSW_ITEM8(reg, rarcc, clr, 0x0, 7, 1);

/* ar_changes_congestion_high
 * Access: RO
 */
MLXSW_ITEM32(reg, rarcc, ar_changes_congestion_high, 0x10, 0, 32);

/* ar_changes_congestion_low
 * Access: RO
 */
MLXSW_ITEM32(reg, rarcc, ar_changes_congestion_low, 0x14, 0, 32);

/* ar_changes_arn_high
 * Access: RO
 */
MLXSW_ITEM32(reg, rarcc, ar_changes_arn_high, 0x18, 0, 32);

/* ar_changes_arn_low
 * Access: RO
 */
MLXSW_ITEM32(reg, rarcc, ar_changes_arn_low, 0x1c, 0, 32);

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

/* upaft
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upaft, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upaft, lp_msb, 0x2, 4, 2);

/* side
 * Access: INDEX
 */
MLXSW_ITEM8(reg, upaft, side, 0x2, 0, 4);

/* allow_untagged
 * Access: RW
 */
MLXSW_ITEM8(reg, upaft, allow_untagged, 0x4, 7, 1);

/* allow_single_prio_tagged
 * Access: RW
 */
MLXSW_ITEM8(reg, upaft, allow_single_prio_tagged, 0x4, 6, 1);

/* allow_single_tagged
 * Access: RW
 */
MLXSW_ITEM8(reg, upaft, allow_single_tagged, 0x4, 5, 1);

/* allow_double_tagged
 * Access: RW
 */
MLXSW_ITEM8(reg, upaft, allow_double_tagged, 0x4, 4, 1);

/* rmid_v2
 * -------
 *
 */
/* rmid_index
 * Access: INDEX
 */
MLXSW_ITEM16(reg, rmid_v2, rmid_index, 0x2, 0, 16);

/* rmpe_index
 * Access: RW
 */
MLXSW_ITEM16(reg, rmid_v2, rmpe_index, 0x6, 0, 16);

/* egress_port
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, rmid_v2, egress_port, 0x20, 0, 32, 4, 0, false);

/* rarcl
 * -----
 *
 */
/* eport_cong_level0
 * Access: RW
 */
MLXSW_ITEM32(reg, rarcl, eport_cong_level0, 0x10, 0, 24);

/* eport_cong_level1
 * Access: RW
 */
MLXSW_ITEM32(reg, rarcl, eport_cong_level1, 0x14, 0, 24);

/* eport_cong_level2
 * Access: RW
 */
MLXSW_ITEM32(reg, rarcl, eport_cong_level2, 0x18, 0, 24);

/* ugcr
 * ----
 *
 */
/* utrap_trunc
 * Access: RW
 */
MLXSW_ITEM8(reg, ugcr, utrap_trunc, 0x2, 0, 8);

/* pn_thr
 * Access: RW
 */
MLXSW_ITEM32(reg, ugcr, pn_thr, 0x4, 0, 32);

/* xpn_pn_thr
 * Access: RW
 */
MLXSW_ITEM64(reg, ugcr, xpn_pn_thr, 0x8, 0, 64);

/* mafcr
 * -----
 *
 */
/* clear
 * Access: OP
 */
MLXSW_ITEM8(reg, mafcr, clear, 0x0, 7, 1);

/* counter_accu_overflow
 * Access: RO
 */
MLXSW_ITEM32(reg, mafcr, counter_accu_overflow, 0x4, 0, 32);

/* packets_inc_units
 * Access: RO
 */
MLXSW_ITEM16(reg, mafcr, packets_inc_units, 0x8, 0, 16);

/* bytes_inc_units
 * Access: RO
 */
MLXSW_ITEM16(reg, mafcr, bytes_inc_units, 0xa, 0, 16);

/* pvbt
 * ----
 *
 */
/* swid
 * Access: INDEX
 */
MLXSW_ITEM8(reg, pvbt, swid, 0x0, 0, 8);

/* op
 * Access: RW
 */
MLXSW_ITEM8(reg, pvbt, op, 0x1, 4, 3);

/* vlan_group
 * Access: INDEX
 */
MLXSW_ITEM16(reg, pvbt, vlan_group, 0x2, 0, 12);

/* g
 * Access: RW
 */
MLXSW_ITEM8(reg, pvbt, g, 0x10, 7, 1);

/* acl_id_group_id
 * Access: RW
 */
MLXSW_ITEM16(reg, pvbt, acl_id_group_id, 0x12, 0, 16);

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
MLXSW_ITEM8(reg, sbsrd, first_lp_msb, 0xa, 0, 4);

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

/* fstm
 * ----
 *
 */
/* record_num
 * Access: OP
 */
MLXSW_ITEM16(reg, fstm, record_num, 0x2, 0, 9);

/* ticket_machine_en
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, fstm, ticket_machine_en, MLXSW_FSTM_PORT_TICKET_INFO_BASE_LEN + 2, 7, 1, MLXSW_FSTM_PORT_TICKET_INFO_REC_LEN, 0, false);

/* lport
 * Access: WO
 */
MLXSW_ITEM16_INDEXED(reg, fstm, lport, MLXSW_FSTM_PORT_TICKET_INFO_BASE_LEN + 2, 0, 10, MLXSW_FSTM_PORT_TICKET_INFO_REC_LEN, 0, false);

/* plar
 * ----
 *
 */
/* local_port_allocated
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, plar, local_port_allocated, 0x0, 0, 32, 4, 0, false);

/* qsptc
 * -----
 *
 */
/* local_iport
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qsptc, local_iport, 0x0, 0, 8);

/* local_eport
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qsptc, local_eport, 0x1, 0, 8);

/* itclass
 * Access: INDEX
 */
MLXSW_ITEM8(reg, qsptc, itclass, 0x2, 0, 3);

/* tclass
 * Access: RW
 */
MLXSW_ITEM8(reg, qsptc, tclass, 0x7, 0, 3);

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

/* secondary
 * Access: RO
 */
MLXSW_ITEM8(reg, pmaos, secondary, 0x4, 5, 1);

/* rev_incompatible
 * Access: RO
 */
MLXSW_ITEM8(reg, pmaos, rev_incompatible, 0x4, 4, 1);

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

/* bin
 * Access: RO
 */
MLXSW_ITEM64_INDEXED(reg, sbhrr_v2, bin, 0x40, 0, 64, 8, 0, false);

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

/* msgi
 * ----
 *
 */
/* serial_number
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, msgi, serial_number, 0x0, 0, 32, 4, 0, false);

/* part_number
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, msgi, part_number, 0x20, 0, 32, 4, 0, false);

/* revision
 * Access: RO
 */
MLXSW_ITEM32(reg, msgi, revision, 0x38, 0, 32);

/* product_name
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, msgi, product_name, 0x40, 0, 32, 4, 0, false);

/* uver
 * ----
 *
 */
/* ether_type0
 * Access: RW
 */
MLXSW_ITEM16(reg, uver, ether_type0, 0x0, 0, 16);

/* ether_type1
 * Access: RW
 */
MLXSW_ITEM16(reg, uver, ether_type1, 0x2, 0, 16);

/* ether_type2
 * Access: RW
 */
MLXSW_ITEM16(reg, uver, ether_type2, 0x4, 0, 16);

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
 * Access: INDEX
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

/* fmtpa
 * -----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fmtpa, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fmtpa, lp_msb, 0x2, 4, 2);

/* prog_idx
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fmtpa, prog_idx, 0x3, 0, 2);

/* e
 * Access: OP
 */
MLXSW_ITEM8(reg, fmtpa, e, 0x4, 7, 1);

/* bound_emt
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtpa, bound_emt, 0x7, 0, 3);

/* reg0
 * Access: RW
 */
MLXSW_ITEM16(reg, fmtpa, reg0, 0xa, 0, 16);

/* queue_id
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtpa, queue_id, 0xf, 0, 8);

/* mafri
 * -----
 *
 */
/* fsf
 * Access: OP
 */
MLXSW_ITEM8(reg, mafri, fsf, 0x0, 0, 1);

/* event
 * Access: OP
 */
MLXSW_ITEM8(reg, mafri, event, 0x1, 0, 1);

/* num_rec
 * Access: OP
 */
MLXSW_ITEM8(reg, mafri, num_rec, 0x3, 0, 8);

/* counter_index_base
 * Access: OP
 */
MLXSW_ITEM32(reg, mafri, counter_index_base, 0x4, 0, 24);

/* user_val
 * Access: RW
 */
MLXSW_ITEM32(reg, mafri, user_val, 0x8, 0, 32);

/* bytes_inc
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mafri, bytes_inc, MLXSW_MAFRI_RECORD_BASE_LEN, 0, 32, MLXSW_MAFRI_RECORD_REC_LEN, 0, false);

/* packets_inc
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mafri, packets_inc, MLXSW_MAFRI_RECORD_BASE_LEN, 0, 32, MLXSW_MAFRI_RECORD_REC_LEN, 4, false);

/* fmtpc
 * -----
 *
 */
/* prog_idx
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fmtpc, prog_idx, 0x1, 0, 2);

/* pc
 * Access: INDEX
 */
MLXSW_ITEM8(reg, fmtpc, pc, 0x3, 0, 6);

/* op_code
 * Access: RW
 */
MLXSW_ITEM8(reg, fmtpc, op_code, 0x7, 0, 8);

/* operand0
 * Access: RW
 */
MLXSW_ITEM16(reg, fmtpc, operand0, 0xa, 0, 16);

/* operand1
 * Access: RW
 */
MLXSW_ITEM16(reg, fmtpc, operand1, 0xe, 0, 16);

/* operand2
 * Access: RW
 */
MLXSW_ITEM16(reg, fmtpc, operand2, 0x12, 0, 16);

/* ihsr
 * ----
 *
 */
/* hash_profile
 * Access: INDEX
 */
MLXSW_ITEM8(reg, ihsr, hash_profile, 0x1, 0, 3);

/* gsh
 * Access: RW
 */
MLXSW_ITEM8(reg, ihsr, gsh, 0x2, 0, 3);

/* type
 * Access: RW
 */
MLXSW_ITEM8(reg, ihsr, type, 0x3, 0, 4);

/* general_fields
 * Access: RW
 */
MLXSW_ITEM32(reg, ihsr, general_fields, 0xc, 0, 32);

/* outer_header_enables
 * Access: RW
 */
MLXSW_ITEM16(reg, ihsr, outer_header_enables, 0x12, 0, 16);

/* outer_header_fields_enable
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, ihsr, outer_header_fields_enable, 0x14, 0, 32, 4, 0, false);

/* inner_header_enables
 * Access: RW
 */
MLXSW_ITEM16(reg, ihsr, inner_header_enables, 0x2e, 0, 16);

/* inner_header_fields_enable
 * Access: RW
 */
MLXSW_ITEM64(reg, ihsr, inner_header_fields_enable, 0x30, 0, 64);

/* mspi
 * ----
 *
 */
/* synce_support
 * Access: RO
 */
MLXSW_ITEM8(reg, mspi, synce_support, 0x0, 7, 1);

/* vendor_id
 * Access: RO
 */
MLXSW_ITEM8(reg, mspi, vendor_id, 0x3, 0, 4);

/* config_version_id
 * Access: RO
 */
MLXSW_ITEM16(reg, mspi, config_version_id, 0x6, 0, 16);

/* bcc
 * Access: RO
 */
MLXSW_ITEM8(reg, mspi, bcc, 0xb, 0, 8);

/* obtv
 * Access: RO
 */
MLXSW_ITEM8(reg, mspi, obtv, 0x10, 7, 1);

/* obs_temperature
 * Access: RO
 */
MLXSW_ITEM16(reg, mspi, obs_temperature, 0x12, 0, 16);

/* bitv
 * Access: RO
 */
MLXSW_ITEM8(reg, mspi, bitv, 0x14, 7, 1);

/* bis_temperature
 * Access: RO
 */
MLXSW_ITEM16(reg, mspi, bis_temperature, 0x16, 0, 16);

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

/* mopce
 * -----
 *
 */
/* num_rec
 * Access: RW
 */
MLXSW_ITEM8(reg, mopce, num_rec, 0x3, 0, 7);

/* hw_unit_instance
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg, mopce, hw_unit_instance, MLXSW_MOPCE_PERFORMANCE_COUNTER_INFO_BASE_LEN + 1, 0, 8, MLXSW_MOPCE_PERFORMANCE_COUNTER_INFO_REC_LEN, 0, false);

/* hw_unit_id
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg, mopce, hw_unit_id, MLXSW_MOPCE_PERFORMANCE_COUNTER_INFO_BASE_LEN + 3, 0, 8, MLXSW_MOPCE_PERFORMANCE_COUNTER_INFO_REC_LEN, 0, false);

/* counter_index
 * Access: RO
 */
MLXSW_ITEM16_INDEXED(reg, mopce, counter_index, MLXSW_MOPCE_PERFORMANCE_COUNTER_INFO_BASE_LEN, 0, 9, MLXSW_MOPCE_PERFORMANCE_COUNTER_INFO_REC_LEN, 4, false);

/* hw_unit_sub_instance
 * Access: RO
 */
MLXSW_ITEM8_INDEXED(reg, mopce, hw_unit_sub_instance, MLXSW_MOPCE_PERFORMANCE_COUNTER_INFO_BASE_LEN + 3, 0, 8, MLXSW_MOPCE_PERFORMANCE_COUNTER_INFO_REC_LEN, 4, false);

/* counter_value
 * Access: RO
 */
MLXSW_ITEM64_INDEXED(reg, mopce, counter_value, MLXSW_MOPCE_PERFORMANCE_COUNTER_INFO_BASE_LEN, 0, 64, MLXSW_MOPCE_PERFORMANCE_COUNTER_INFO_REC_LEN, 8, false);

/* mfde
 * ----
 *
 */
/* irisc_id
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, irisc_id, 0x0, 0, 8);

/* severity
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, severity, 0x1, 0, 8);

/* event_id
 * Access: RO
 */
MLXSW_ITEM16(reg, mfde, event_id, 0x2, 0, 16);

/* method
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, method, 0x4, 5, 1);

/* long_process
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, long_process, 0x4, 4, 1);

/* command_type
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, command_type, 0x4, 0, 2);

/* mgmt_class
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, mgmt_class, 0x5, 0, 8);

/* reg_attr_id
 * Access: RO
 */
MLXSW_ITEM16(reg, mfde, reg_attr_id, 0x6, 0, 16);

/* event_params_crspace_timeout_log_address
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, event_params_crspace_timeout_log_address, 0x10, 0, 32);

/* event_params_crspace_timeout_oe
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, event_params_crspace_timeout_oe, 0x14, 0, 1);

/* event_params_crspace_timeout_log_id
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, event_params_crspace_timeout_log_id, 0x17, 0, 4);

/* event_params_crspace_timeout_log_ip
 * Access: RO
 */
MLXSW_ITEM64(reg, mfde, event_params_crspace_timeout_log_ip, 0x18, 0, 64);

/* event_params_kvd_im_stop_oe
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, event_params_kvd_im_stop_oe, 0x10, 0, 1);

/* event_params_kvd_im_stop_pipes_mask
 * Access: RO
 */
MLXSW_ITEM16(reg, mfde, event_params_kvd_im_stop_pipes_mask, 0x12, 0, 16);

/* event_params_fw_assert_assert_var0
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, event_params_fw_assert_assert_var0, 0x10, 0, 32);

/* event_params_fw_assert_assert_var1
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, event_params_fw_assert_assert_var1, 0x14, 0, 32);

/* event_params_fw_assert_assert_var2
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, event_params_fw_assert_assert_var2, 0x18, 0, 32);

/* event_params_fw_assert_assert_var3
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, event_params_fw_assert_assert_var3, 0x1c, 0, 32);

/* event_params_fw_assert_assert_var4
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, event_params_fw_assert_assert_var4, 0x20, 0, 32);

/* event_params_fw_assert_assert_existptr
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, event_params_fw_assert_assert_existptr, 0x24, 0, 32);

/* event_params_fw_assert_assert_callra
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, event_params_fw_assert_assert_callra, 0x28, 0, 32);

/* event_params_fw_assert_test
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, event_params_fw_assert_test, 0x2c, 7, 1);

/* event_params_fw_assert_oe
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, event_params_fw_assert_oe, 0x2c, 0, 1);

/* event_params_fw_assert_tile_v
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, event_params_fw_assert_tile_v, 0x2d, 7, 1);

/* event_params_fw_assert_tile_index
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, event_params_fw_assert_tile_index, 0x2d, 0, 6);

/* event_params_fw_assert_ext_synd
 * Access: RO
 */
MLXSW_ITEM16(reg, mfde, event_params_fw_assert_ext_synd, 0x2e, 0, 16);

/* event_params_fw_assert_assert_string
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mfde, event_params_fw_assert_assert_string, 0x30, 0, 32, 4, 0, false);

/* event_params_fatal_cause_test
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, event_params_fatal_cause_test, 0x10, 7, 1);

/* event_params_fatal_cause_fw_cause
 * Access: RW
 */
MLXSW_ITEM8(reg, mfde, event_params_fatal_cause_fw_cause, 0x10, 6, 1);

/* event_params_fatal_cause_cause_id
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, event_params_fatal_cause_cause_id, 0x10, 0, 18);

/* event_params_fatal_cause_tile_v
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, event_params_fatal_cause_tile_v, 0x15, 7, 1);

/* event_params_fatal_cause_tile_index
 * Access: RO
 */
MLXSW_ITEM8(reg, mfde, event_params_fatal_cause_tile_index, 0x15, 0, 6);

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

/* oee
 * Access: WO
 */
MLXSW_ITEM8(reg, mbct, oee, 0x8, 1, 1);

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

/* utfd
 * ----
 *
 */
/* local_port
 * Access: INDEX
 */
MLXSW_ITEM8(reg, utfd, local_port, 0x1, 0, 8);

/* lp_msb
 * Access: INDEX
 */
MLXSW_ITEM8(reg, utfd, lp_msb, 0x2, 4, 2);

/* side
 * Access: INDEX
 */
MLXSW_ITEM8(reg, utfd, side, 0x2, 0, 4);

/* ucheck_id
 * Access: RO
 */
MLXSW_ITEM8(reg, utfd, ucheck_id, 0x5, 0, 8);

/* pending_packets
 * Access: RO
 */
MLXSW_ITEM16(reg, utfd, pending_packets, 0x6, 0, 16);

/* frag_type
 * Access: RO
 */
MLXSW_ITEM8(reg, utfd, frag_type, 0x9, 0, 2);

/* frag_size
 * Access: RO
 */
MLXSW_ITEM16(reg, utfd, frag_size, 0xa, 0, 10);

/* time_stamp_sec
 * Access: RO
 */
MLXSW_ITEM32(reg, utfd, time_stamp_sec, 0xc, 0, 32);

/* time_stamp_nsec
 * Access: RO
 */
MLXSW_ITEM32(reg, utfd, time_stamp_nsec, 0x10, 0, 30);

/* sec_act
 * Access: RO
 */
MLXSW_ITEM8(reg, utfd, sec_act, 0x14, 0, 1);

/* secy_v
 * Access: RO
 */
MLXSW_ITEM8(reg, utfd, secy_v, 0x15, 0, 1);

/* secy
 * Access: RO
 */
MLXSW_ITEM16(reg, utfd, secy, 0x16, 0, 16);

/* sadb_v
 * Access: RO
 */
MLXSW_ITEM8(reg, utfd, sadb_v, 0x19, 0, 1);

/* sadb_entry_index
 * Access: RO
 */
MLXSW_ITEM16(reg, utfd, sadb_entry_index, 0x1a, 0, 16);

/* data
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, utfd, data, 0x20, 0, 32, 4, 0, false);

