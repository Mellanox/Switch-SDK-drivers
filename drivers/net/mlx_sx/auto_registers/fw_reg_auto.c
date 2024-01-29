/*
 * Copyright © 2019-2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include "../fw_internal.h"
#include "../emad.h"



/************************************************
* PMDR
***********************************************/
int __PMDR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmdr_reg *pmdr_reg = (struct ku_pmdr_reg*)ku_reg;

    mlxsw_reg_pmdr_local_port_set(inbox, pmdr_reg->local_port);
    mlxsw_reg_pmdr_pnat_set(inbox, pmdr_reg->pnat);
    mlxsw_reg_pmdr_lp_msb_set(inbox, pmdr_reg->lp_msb);
    mlxsw_reg_pmdr_lp_query_msb_set(inbox, pmdr_reg->lp_query_msb);


    return 0;
}

int __PMDR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmdr_reg *pmdr_reg = (struct ku_pmdr_reg*)ku_reg;

    pmdr_reg->status = mlxsw_reg_pmdr_status_get(outbox);
    pmdr_reg->version = mlxsw_reg_pmdr_version_get(outbox);
    pmdr_reg->local_port = mlxsw_reg_pmdr_local_port_get(outbox);
    pmdr_reg->pnat = mlxsw_reg_pmdr_pnat_get(outbox);
    pmdr_reg->gb_valid = mlxsw_reg_pmdr_gb_valid_get(outbox);
    pmdr_reg->mcm_tile_valid = mlxsw_reg_pmdr_mcm_tile_valid_get(outbox);
    pmdr_reg->scc_valid = mlxsw_reg_pmdr_scc_valid_get(outbox);
    pmdr_reg->lp_msb = mlxsw_reg_pmdr_lp_msb_get(outbox);
    pmdr_reg->pport = mlxsw_reg_pmdr_pport_get(outbox);
    pmdr_reg->module = mlxsw_reg_pmdr_module_get(outbox);
    pmdr_reg->cluster = mlxsw_reg_pmdr_cluster_get(outbox);
    pmdr_reg->clp_4x = mlxsw_reg_pmdr_clp_4x_get(outbox);
    pmdr_reg->clp_1x = mlxsw_reg_pmdr_clp_1x_get(outbox);
    pmdr_reg->gb_dp_num = mlxsw_reg_pmdr_gb_dp_num_get(outbox);
    pmdr_reg->split = mlxsw_reg_pmdr_split_get(outbox);
    pmdr_reg->swid = mlxsw_reg_pmdr_swid_get(outbox);
    pmdr_reg->module_lane_mask = mlxsw_reg_pmdr_module_lane_mask_get(outbox);
    pmdr_reg->ib_port = mlxsw_reg_pmdr_ib_port_get(outbox);
    pmdr_reg->label_port_query = mlxsw_reg_pmdr_label_port_query_get(outbox);
    pmdr_reg->local_port_query = mlxsw_reg_pmdr_local_port_query_get(outbox);
    pmdr_reg->usr_sd_4x_tx = mlxsw_reg_pmdr_usr_sd_4x_tx_get(outbox);
    pmdr_reg->usr_sd_4x_rx = mlxsw_reg_pmdr_usr_sd_4x_rx_get(outbox);
    pmdr_reg->lp_query_msb = mlxsw_reg_pmdr_lp_query_msb_get(outbox);
    pmdr_reg->slot_index = mlxsw_reg_pmdr_slot_index_get(outbox);
    pmdr_reg->tile_cluster = mlxsw_reg_pmdr_tile_cluster_get(outbox);
    pmdr_reg->mcm_tile_num = mlxsw_reg_pmdr_mcm_tile_num_get(outbox);
    pmdr_reg->tile_pport = mlxsw_reg_pmdr_tile_pport_get(outbox);
    pmdr_reg->gearbox_die_num = mlxsw_reg_pmdr_gearbox_die_num_get(outbox);
    pmdr_reg->vl_num = mlxsw_reg_pmdr_vl_num_get(outbox);
    pmdr_reg->lane7_physical_rx = mlxsw_reg_pmdr_lane7_physical_rx_get(outbox);
    pmdr_reg->lane6_physical_rx = mlxsw_reg_pmdr_lane6_physical_rx_get(outbox);
    pmdr_reg->lane5_physical_rx = mlxsw_reg_pmdr_lane5_physical_rx_get(outbox);
    pmdr_reg->lane4_physical_rx = mlxsw_reg_pmdr_lane4_physical_rx_get(outbox);
    pmdr_reg->lane3_physical_rx = mlxsw_reg_pmdr_lane3_physical_rx_get(outbox);
    pmdr_reg->lane2_physical_rx = mlxsw_reg_pmdr_lane2_physical_rx_get(outbox);
    pmdr_reg->lane1_physical_rx = mlxsw_reg_pmdr_lane1_physical_rx_get(outbox);
    pmdr_reg->lane0_physical_rx = mlxsw_reg_pmdr_lane0_physical_rx_get(outbox);
    pmdr_reg->pll_index = mlxsw_reg_pmdr_pll_index_get(outbox);
    pmdr_reg->lane7_physical_tx = mlxsw_reg_pmdr_lane7_physical_tx_get(outbox);
    pmdr_reg->lane6_physical_tx = mlxsw_reg_pmdr_lane6_physical_tx_get(outbox);
    pmdr_reg->lane5_physical_tx = mlxsw_reg_pmdr_lane5_physical_tx_get(outbox);
    pmdr_reg->lane4_physical_tx = mlxsw_reg_pmdr_lane4_physical_tx_get(outbox);
    pmdr_reg->lane3_physical_tx = mlxsw_reg_pmdr_lane3_physical_tx_get(outbox);
    pmdr_reg->lane2_physical_tx = mlxsw_reg_pmdr_lane2_physical_tx_get(outbox);
    pmdr_reg->lane1_physical_tx = mlxsw_reg_pmdr_lane1_physical_tx_get(outbox);
    pmdr_reg->lane0_physical_tx = mlxsw_reg_pmdr_lane0_physical_tx_get(outbox);
    pmdr_reg->vl7_lane_map = mlxsw_reg_pmdr_vl7_lane_map_get(outbox);
    pmdr_reg->vl6_lane_map = mlxsw_reg_pmdr_vl6_lane_map_get(outbox);
    pmdr_reg->vl5_lane_map = mlxsw_reg_pmdr_vl5_lane_map_get(outbox);
    pmdr_reg->vl4_lane_map = mlxsw_reg_pmdr_vl4_lane_map_get(outbox);
    pmdr_reg->vl3_lane_map = mlxsw_reg_pmdr_vl3_lane_map_get(outbox);
    pmdr_reg->vl2_lane_map = mlxsw_reg_pmdr_vl2_lane_map_get(outbox);
    pmdr_reg->vl1_lane_map = mlxsw_reg_pmdr_vl1_lane_map_get(outbox);
    pmdr_reg->vl0_lane_map = mlxsw_reg_pmdr_vl0_lane_map_get(outbox);
    pmdr_reg->vl15_lane_map = mlxsw_reg_pmdr_vl15_lane_map_get(outbox);
    pmdr_reg->vl14_lane_map = mlxsw_reg_pmdr_vl14_lane_map_get(outbox);
    pmdr_reg->vl13_lane_map = mlxsw_reg_pmdr_vl13_lane_map_get(outbox);
    pmdr_reg->vl12_lane_map = mlxsw_reg_pmdr_vl12_lane_map_get(outbox);
    pmdr_reg->vl11_lane_map = mlxsw_reg_pmdr_vl11_lane_map_get(outbox);
    pmdr_reg->vl10_lane_map = mlxsw_reg_pmdr_vl10_lane_map_get(outbox);
    pmdr_reg->vl9_lane_map = mlxsw_reg_pmdr_vl9_lane_map_get(outbox);
    pmdr_reg->vl8_lane_map = mlxsw_reg_pmdr_vl8_lane_map_get(outbox);
    pmdr_reg->vl23_lane_map = mlxsw_reg_pmdr_vl23_lane_map_get(outbox);
    pmdr_reg->vl22_lane_map = mlxsw_reg_pmdr_vl22_lane_map_get(outbox);
    pmdr_reg->vl21_lane_map = mlxsw_reg_pmdr_vl21_lane_map_get(outbox);
    pmdr_reg->vl20_lane_map = mlxsw_reg_pmdr_vl20_lane_map_get(outbox);
    pmdr_reg->vl19_lane_map = mlxsw_reg_pmdr_vl19_lane_map_get(outbox);
    pmdr_reg->vl18_lane_map = mlxsw_reg_pmdr_vl18_lane_map_get(outbox);
    pmdr_reg->vl17_lane_map = mlxsw_reg_pmdr_vl17_lane_map_get(outbox);
    pmdr_reg->vl16_lane_map = mlxsw_reg_pmdr_vl16_lane_map_get(outbox);
    pmdr_reg->vl31_lane_map = mlxsw_reg_pmdr_vl31_lane_map_get(outbox);
    pmdr_reg->vl30_lane_map = mlxsw_reg_pmdr_vl30_lane_map_get(outbox);
    pmdr_reg->vl29_lane_map = mlxsw_reg_pmdr_vl29_lane_map_get(outbox);
    pmdr_reg->vl28_lane_map = mlxsw_reg_pmdr_vl28_lane_map_get(outbox);
    pmdr_reg->vl27_lane_map = mlxsw_reg_pmdr_vl27_lane_map_get(outbox);
    pmdr_reg->vl26_lane_map = mlxsw_reg_pmdr_vl26_lane_map_get(outbox);
    pmdr_reg->vl25_lane_map = mlxsw_reg_pmdr_vl25_lane_map_get(outbox);
    pmdr_reg->vl24_lane_map = mlxsw_reg_pmdr_vl24_lane_map_get(outbox);
    pmdr_reg->scc_hs_lanes = mlxsw_reg_pmdr_scc_hs_lanes_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__PMDR_decode);

int sx_ACCESS_REG_PMDR(struct sx_dev *dev, struct ku_access_pmdr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PMDR_LEN >> 2) + 1;

    if (MLXSW_PMDR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMDR_encode,
                                  __PMDR_decode,
                                  reg_len_dword,
                                  &reg_data->pmdr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMDR);

int sx_EMAD_ACCESS_REG_PMDR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmdr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PMDR_LEN >> 2) + 1;

    if (MLXSW_PMDR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PMDR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PMDR_encode,
                                     __PMDR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PMDR);

/************************************************
* MTECR
***********************************************/
int __MTECR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtecr_reg *mtecr_reg = (struct ku_mtecr_reg*)ku_reg;

    mlxsw_reg_mtecr_slot_index_set(inbox, mtecr_reg->slot_index);


    return 0;
}

int __MTECR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtecr_reg *mtecr_reg = (struct ku_mtecr_reg*)ku_reg;
    uint32_t i = 0;

    mtecr_reg->last_sensor = mlxsw_reg_mtecr_last_sensor_get(outbox);
    mtecr_reg->sensor_count = mlxsw_reg_mtecr_sensor_count_get(outbox);
    mtecr_reg->slot_index = mlxsw_reg_mtecr_slot_index_get(outbox);
    mtecr_reg->internal_sensor_count = mlxsw_reg_mtecr_internal_sensor_count_get(outbox);
    for (i = 0; i < SXD_MTECR_SENSOR_MAP_NUM; i++) {
        mtecr_reg->sensor_map[i] = mlxsw_reg_mtecr_sensor_map_get(outbox, i);
    }


    return 0;
}
EXPORT_SYMBOL(__MTECR_decode);

int sx_ACCESS_REG_MTECR(struct sx_dev *dev, struct ku_access_mtecr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MTECR_LEN >> 2) + 1;

    if (MLXSW_MTECR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTECR_encode,
                                  __MTECR_decode,
                                  reg_len_dword,
                                  &reg_data->mtecr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTECR);

int sx_EMAD_ACCESS_REG_MTECR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtecr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MTECR_LEN >> 2) + 1;

    if (MLXSW_MTECR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MTECR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MTECR_encode,
                                     __MTECR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MTECR);

/************************************************
* IGCR
***********************************************/
int __IGCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_igcr_reg *igcr_reg = (struct ku_igcr_reg*)ku_reg;

    mlxsw_reg_igcr_ddd_lpm_high_ipv6_set(inbox, igcr_reg->ddd_lpm_high_ipv6);
    mlxsw_reg_igcr_ddd_lpm_high_ipv4_set(inbox, igcr_reg->ddd_lpm_high_ipv4);
    mlxsw_reg_igcr_ddd_pe_actions_priority_set(inbox, igcr_reg->ddd_pe_actions_priority);
    mlxsw_reg_igcr_ddd_lag_mode_set(inbox, igcr_reg->ddd_lag_mode);
    mlxsw_reg_igcr_pisbo_set(inbox, igcr_reg->pisbo);


    return 0;
}

int __IGCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_igcr_reg *igcr_reg = (struct ku_igcr_reg*)ku_reg;

    igcr_reg->ddd_lpm_high_ipv6 = mlxsw_reg_igcr_ddd_lpm_high_ipv6_get(outbox);
    igcr_reg->ddd_lpm_high_ipv4 = mlxsw_reg_igcr_ddd_lpm_high_ipv4_get(outbox);
    igcr_reg->ddd_pe_actions_priority = mlxsw_reg_igcr_ddd_pe_actions_priority_get(outbox);
    igcr_reg->ddd_lag_mode = mlxsw_reg_igcr_ddd_lag_mode_get(outbox);
    igcr_reg->pisbo = mlxsw_reg_igcr_pisbo_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__IGCR_decode);

int sx_ACCESS_REG_IGCR(struct sx_dev *dev, struct ku_access_igcr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_IGCR_LEN >> 2) + 1;

    if (MLXSW_IGCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __IGCR_encode,
                                  __IGCR_decode,
                                  reg_len_dword,
                                  &reg_data->igcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_IGCR);

int sx_EMAD_ACCESS_REG_IGCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_igcr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_IGCR_LEN >> 2) + 1;

    if (MLXSW_IGCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_IGCR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __IGCR_encode,
                                     __IGCR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_IGCR);

/************************************************
* MVCAP
***********************************************/
int __MVCAP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mvcap_reg *mvcap_reg = (struct ku_mvcap_reg*)ku_reg;

    mlxsw_reg_mvcap_slot_index_set(inbox, mvcap_reg->slot_index);


    return 0;
}

int __MVCAP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mvcap_reg *mvcap_reg = (struct ku_mvcap_reg*)ku_reg;

    mvcap_reg->sensor_map = mlxsw_reg_mvcap_sensor_map_get(outbox);
    mvcap_reg->slot_index = mlxsw_reg_mvcap_slot_index_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MVCAP_decode);

int sx_ACCESS_REG_MVCAP(struct sx_dev *dev, struct ku_access_mvcap_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MVCAP_LEN >> 2) + 1;

    if (MLXSW_MVCAP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MVCAP_encode,
                                  __MVCAP_decode,
                                  reg_len_dword,
                                  &reg_data->mvcap_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MVCAP);

int sx_EMAD_ACCESS_REG_MVCAP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mvcap_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MVCAP_LEN >> 2) + 1;

    if (MLXSW_MVCAP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MVCAP_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MVCAP_encode,
                                     __MVCAP_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MVCAP);

/************************************************
* MTMP
***********************************************/
int __MTMP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtmp_reg *mtmp_reg = (struct ku_mtmp_reg*)ku_reg;

    mlxsw_reg_mtmp_i_set(inbox, mtmp_reg->i);
    mlxsw_reg_mtmp_ig_set(inbox, mtmp_reg->ig);
    mlxsw_reg_mtmp_asic_index_set(inbox, mtmp_reg->asic_index);
    mlxsw_reg_mtmp_slot_index_set(inbox, mtmp_reg->slot_index);
    mlxsw_reg_mtmp_sensor_index_set(inbox, mtmp_reg->sensor_index);
    mlxsw_reg_mtmp_mte_set(inbox, mtmp_reg->mte);
    mlxsw_reg_mtmp_mtr_set(inbox, mtmp_reg->mtr);
    mlxsw_reg_mtmp_weme_set(inbox, mtmp_reg->weme);
    mlxsw_reg_mtmp_sdme_set(inbox, mtmp_reg->sdme);
    mlxsw_reg_mtmp_tee_set(inbox, mtmp_reg->tee);
    mlxsw_reg_mtmp_sdee_set(inbox, mtmp_reg->sdee);
    mlxsw_reg_mtmp_temperature_threshold_hi_set(inbox, mtmp_reg->temperature_threshold_hi);
    mlxsw_reg_mtmp_temperature_threshold_lo_set(inbox, mtmp_reg->temperature_threshold_lo);


    return 0;
}

int __MTMP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtmp_reg *mtmp_reg = (struct ku_mtmp_reg*)ku_reg;

    mtmp_reg->i = mlxsw_reg_mtmp_i_get(outbox);
    mtmp_reg->ig = mlxsw_reg_mtmp_ig_get(outbox);
    mtmp_reg->asic_index = mlxsw_reg_mtmp_asic_index_get(outbox);
    mtmp_reg->slot_index = mlxsw_reg_mtmp_slot_index_get(outbox);
    mtmp_reg->sensor_index = mlxsw_reg_mtmp_sensor_index_get(outbox);
    mtmp_reg->max_operational_temperature = mlxsw_reg_mtmp_max_operational_temperature_get(outbox);
    mtmp_reg->temperature = mlxsw_reg_mtmp_temperature_get(outbox);
    mtmp_reg->mte = mlxsw_reg_mtmp_mte_get(outbox);
    mtmp_reg->mtr = mlxsw_reg_mtmp_mtr_get(outbox);
    mtmp_reg->weme = mlxsw_reg_mtmp_weme_get(outbox);
    mtmp_reg->sdme = mlxsw_reg_mtmp_sdme_get(outbox);
    mtmp_reg->max_temperature = mlxsw_reg_mtmp_max_temperature_get(outbox);
    mtmp_reg->tee = mlxsw_reg_mtmp_tee_get(outbox);
    mtmp_reg->sdee = mlxsw_reg_mtmp_sdee_get(outbox);
    mtmp_reg->temperature_threshold_hi = mlxsw_reg_mtmp_temperature_threshold_hi_get(outbox);
    mtmp_reg->temperature_threshold_lo = mlxsw_reg_mtmp_temperature_threshold_lo_get(outbox);
    mtmp_reg->sensor_name_hi = mlxsw_reg_mtmp_sensor_name_hi_get(outbox);
    mtmp_reg->sensor_name_lo = mlxsw_reg_mtmp_sensor_name_lo_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MTMP_decode);

int sx_ACCESS_REG_MTMP(struct sx_dev *dev, struct ku_access_mtmp_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MTMP_LEN >> 2) + 1;

    if (MLXSW_MTMP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTMP_encode,
                                  __MTMP_decode,
                                  reg_len_dword,
                                  &reg_data->mtmp_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTMP);

int sx_EMAD_ACCESS_REG_MTMP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtmp_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MTMP_LEN >> 2) + 1;

    if (MLXSW_MTMP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MTMP_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MTMP_encode,
                                     __MTMP_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MTMP);

/************************************************
* MOGCR
***********************************************/
int __MOGCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mogcr_reg *mogcr_reg = (struct ku_mogcr_reg*)ku_reg;

    mlxsw_reg_mogcr_tele_managed_set(inbox, mogcr_reg->tele_managed);
    mlxsw_reg_mogcr_ptp_iftc_set(inbox, mogcr_reg->ptp_iftc);
    mlxsw_reg_mogcr_ptp_eftc_set(inbox, mogcr_reg->ptp_eftc);
    mlxsw_reg_mogcr_sid_set(inbox, mogcr_reg->sid);
    mlxsw_reg_mogcr_mirroring_pid_base_set(inbox, mogcr_reg->mirroring_pid_base);
    mlxsw_reg_mogcr_mirror_latency_units_set(inbox, mogcr_reg->mirror_latency_units);
    mlxsw_reg_mogcr_latency_histogram_units_set(inbox, mogcr_reg->latency_histogram_units);
    mlxsw_reg_mogcr_toc_fmt_set(inbox, mogcr_reg->toc_fmt);


    return 0;
}

int __MOGCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mogcr_reg *mogcr_reg = (struct ku_mogcr_reg*)ku_reg;

    mogcr_reg->tele_managed = mlxsw_reg_mogcr_tele_managed_get(outbox);
    mogcr_reg->ptp_iftc = mlxsw_reg_mogcr_ptp_iftc_get(outbox);
    mogcr_reg->ptp_eftc = mlxsw_reg_mogcr_ptp_eftc_get(outbox);
    mogcr_reg->sid = mlxsw_reg_mogcr_sid_get(outbox);
    mogcr_reg->mirroring_pid_base = mlxsw_reg_mogcr_mirroring_pid_base_get(outbox);
    mogcr_reg->mirror_latency_units = mlxsw_reg_mogcr_mirror_latency_units_get(outbox);
    mogcr_reg->latency_histogram_units = mlxsw_reg_mogcr_latency_histogram_units_get(outbox);
    mogcr_reg->toc_fmt = mlxsw_reg_mogcr_toc_fmt_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MOGCR_decode);

int sx_ACCESS_REG_MOGCR(struct sx_dev *dev, struct ku_access_mogcr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MOGCR_LEN >> 2) + 1;

    if (MLXSW_MOGCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MOGCR_encode,
                                  __MOGCR_decode,
                                  reg_len_dword,
                                  &reg_data->mogcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MOGCR);

int sx_EMAD_ACCESS_REG_MOGCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mogcr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MOGCR_LEN >> 2) + 1;

    if (MLXSW_MOGCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MOGCR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MOGCR_encode,
                                     __MOGCR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MOGCR);

/************************************************
* PDDR
***********************************************/
int __PDDR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pddr_reg *pddr_reg = (struct ku_pddr_reg*)ku_reg;
    uint32_t i = 0;

    mlxsw_reg_pddr_local_port_set(inbox, pddr_reg->local_port);
    mlxsw_reg_pddr_pnat_set(inbox, pddr_reg->pnat);
    mlxsw_reg_pddr_lp_msb_set(inbox, pddr_reg->lp_msb);
    mlxsw_reg_pddr_port_type_set(inbox, pddr_reg->port_type);
    mlxsw_reg_pddr_clr_set(inbox, pddr_reg->clr);
    mlxsw_reg_pddr_module_info_ext_set(inbox, pddr_reg->module_info_ext);
    mlxsw_reg_pddr_dev_set(inbox, pddr_reg->dev);
    mlxsw_reg_pddr_page_select_set(inbox, pddr_reg->page_select);
    switch (pddr_reg->page_select) {
    case SXD_PDDR_PAGE_SELECT_OPERATIONAL_INFO_PAGE_E:
        break;

    case SXD_PDDR_PAGE_SELECT_TROUBLESHOOTING_INFO_PAGE_E:
        mlxsw_reg_pddr_page_data_pddr_troubleshooting_page_group_opcode_set(inbox, pddr_reg->page_data.pddr_troubleshooting_page.group_opcode);
        switch (pddr_reg->page_data.pddr_troubleshooting_page.group_opcode) {
        case SXD_PDDR_GROUP_OPCODE_MONITOR_OPCODES_E:
            mlxsw_reg_pddr_page_data_pddr_troubleshooting_page_status_opcode_pddr_monitor_opcode_monitor_opcode_set(inbox, pddr_reg->page_data.pddr_troubleshooting_page.status_opcode.pddr_monitor_opcode.monitor_opcode);
            break;

        case SXD_PDDR_GROUP_OPCODE_ADVANCED_DEBUG_OPCODES_E:
            mlxsw_reg_pddr_page_data_pddr_troubleshooting_page_status_opcode_pddr_advanced_opcode_advanced_opcode_set(inbox, pddr_reg->page_data.pddr_troubleshooting_page.status_opcode.pddr_advanced_opcode.advanced_opcode);
            break;

        default:
            /* Other types not supported yet */
            break;
        }
        mlxsw_reg_pddr_page_data_pddr_troubleshooting_page_user_feedback_data_set(inbox, pddr_reg->page_data.pddr_troubleshooting_page.user_feedback_data);
        mlxsw_reg_pddr_page_data_pddr_troubleshooting_page_user_feedback_index_set(inbox, pddr_reg->page_data.pddr_troubleshooting_page.user_feedback_index);
        break;

    case SXD_PDDR_PAGE_SELECT_PHY_INFO_PAGE_E:
        mlxsw_reg_pddr_page_data_pddr_phy_info_page_ib_debug_indication_set(inbox, pddr_reg->page_data.pddr_phy_info_page.ib_debug_indication);
        break;

    case SXD_PDDR_PAGE_SELECT_MODULE_INFO_PAGE_E:
        mlxsw_reg_pddr_page_data_pddr_module_info_cable_technology_set(inbox, pddr_reg->page_data.pddr_module_info.cable_technology);
        mlxsw_reg_pddr_page_data_pddr_module_info_cable_breakout_set(inbox, pddr_reg->page_data.pddr_module_info.cable_breakout);
        mlxsw_reg_pddr_page_data_pddr_module_info_ext_ethernet_compliance_code_set(inbox, pddr_reg->page_data.pddr_module_info.ext_ethernet_compliance_code);
        mlxsw_reg_pddr_page_data_pddr_module_info_ethernet_compliance_code_set(inbox, pddr_reg->page_data.pddr_module_info.ethernet_compliance_code);
        break;

    case SXD_PDDR_PAGE_SELECT_PORT_EVENTS_PAGE_E:
        for (i = 0; i < SXD_PDDR_CLR_MASK_NUM; i++) {
            mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_clr_mask_set(inbox, i, pddr_reg->page_data.pddr_port_events_page_layout.clr_mask[i]);
        }
        break;

    case SXD_PDDR_PAGE_SELECT_DEVICE_EVENTS_PAGE_E:
        for (i = 0; i < SXD_PDDR_CLR_MASK_NUM; i++) {
            mlxsw_reg_pddr_page_data_pddr_device_events_page_clr_mask_set(inbox, i, pddr_reg->page_data.pddr_device_events_page.clr_mask[i]);
        }
        mlxsw_reg_pddr_page_data_pddr_device_events_page_uc_crspace_timeout_lane_set(inbox, pddr_reg->page_data.pddr_device_events_page.uc_crspace_timeout_lane);
        mlxsw_reg_pddr_page_data_pddr_device_events_page_uc_crspace_timeout_cl_set(inbox, pddr_reg->page_data.pddr_device_events_page.uc_crspace_timeout_cl);
        mlxsw_reg_pddr_page_data_pddr_device_events_page_uc_stack_overflow_lane_set(inbox, pddr_reg->page_data.pddr_device_events_page.uc_stack_overflow_lane);
        mlxsw_reg_pddr_page_data_pddr_device_events_page_uc_stack_overflow_cl_set(inbox, pddr_reg->page_data.pddr_device_events_page.uc_stack_overflow_cl);
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_DOWN_INFO_E:
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_DOWN_EVENTS_E:
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_UP_INFO_E:
        break;

    case SXD_PDDR_PAGE_SELECT_MODULE_LATCHED_FLAG_INFO_PAGE_E:
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_DOWN_INFO_EXT_E:
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_PARTNER_INFO_PAGE_E:
        break;

    case SXD_PDDR_PAGE_SELECT_MNG_DEBUG_PAGE_E:
        break;

    case SXD_PDDR_PAGE_SELECT_PHY_DEBUG_PAGE_E:
        mlxsw_reg_pddr_page_data_pddr_phy_debug_page_pport_set(inbox, pddr_reg->page_data.pddr_phy_debug_page.pport);
        mlxsw_reg_pddr_page_data_pddr_phy_debug_page_trigger_cond_state_event_val_set(inbox, pddr_reg->page_data.pddr_phy_debug_page.trigger_cond_state_event_val);
        mlxsw_reg_pddr_page_data_pddr_phy_debug_page_trigger_cond_state_or_event_set(inbox, pddr_reg->page_data.pddr_phy_debug_page.trigger_cond_state_or_event);
        mlxsw_reg_pddr_page_data_pddr_phy_debug_page_trigger_cond_fsm_set(inbox, pddr_reg->page_data.pddr_phy_debug_page.trigger_cond_fsm);
        mlxsw_reg_pddr_page_data_pddr_phy_debug_page_pre_trigger_buff_mode_set(inbox, pddr_reg->page_data.pddr_phy_debug_page.pre_trigger_buff_mode);
        mlxsw_reg_pddr_page_data_pddr_phy_debug_page_tracer_mode_set(inbox, pddr_reg->page_data.pddr_phy_debug_page.tracer_mode);
        mlxsw_reg_pddr_page_data_pddr_phy_debug_page_reset_tracer_set(inbox, pddr_reg->page_data.pddr_phy_debug_page.reset_tracer);
        mlxsw_reg_pddr_page_data_pddr_phy_debug_page_tracer_enable_set(inbox, pddr_reg->page_data.pddr_phy_debug_page.tracer_enable);
        mlxsw_reg_pddr_page_data_pddr_phy_debug_page_fsm_mask_set(inbox, pddr_reg->page_data.pddr_phy_debug_page.fsm_mask);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}

int __PDDR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pddr_reg *pddr_reg = (struct ku_pddr_reg*)ku_reg;
    uint32_t i = 0;

    pddr_reg->local_port = mlxsw_reg_pddr_local_port_get(outbox);
    pddr_reg->pnat = mlxsw_reg_pddr_pnat_get(outbox);
    pddr_reg->lp_msb = mlxsw_reg_pddr_lp_msb_get(outbox);
    pddr_reg->port_type = mlxsw_reg_pddr_port_type_get(outbox);
    pddr_reg->clr = mlxsw_reg_pddr_clr_get(outbox);
    pddr_reg->module_info_ext = mlxsw_reg_pddr_module_info_ext_get(outbox);
    pddr_reg->dev = mlxsw_reg_pddr_dev_get(outbox);
    pddr_reg->page_select = mlxsw_reg_pddr_page_select_get(outbox);
    switch (pddr_reg->page_select) {
    case SXD_PDDR_PAGE_SELECT_OPERATIONAL_INFO_PAGE_E:
        pddr_reg->page_data.pddr_operation_info_page.proto_active = mlxsw_reg_pddr_page_data_pddr_operation_info_page_proto_active_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.neg_mode_active = mlxsw_reg_pddr_page_data_pddr_operation_info_page_neg_mode_active_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.pd_fsm_state = mlxsw_reg_pddr_page_data_pddr_operation_info_page_pd_fsm_state_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.phy_mngr_fsm_state = mlxsw_reg_pddr_page_data_pddr_operation_info_page_phy_mngr_fsm_state_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.eth_an_fsm_state = mlxsw_reg_pddr_page_data_pddr_operation_info_page_eth_an_fsm_state_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.ib_phy_fsm_state = mlxsw_reg_pddr_page_data_pddr_operation_info_page_ib_phy_fsm_state_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.phy_hst_fsm_state = mlxsw_reg_pddr_page_data_pddr_operation_info_page_phy_hst_fsm_state_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.pm_le.pddr_phy_manager_link_enabed_ib.phy_manager_link_width_enabled = mlxsw_reg_pddr_page_data_pddr_operation_info_page_pm_le_pddr_phy_manager_link_enabed_ib_phy_manager_link_width_enabled_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.pm_le.pddr_phy_manager_link_enabed_ib.phy_manager_link_proto_enabled = mlxsw_reg_pddr_page_data_pddr_operation_info_page_pm_le_pddr_phy_manager_link_enabed_ib_phy_manager_link_proto_enabled_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.pm_le.pddr_phy_manager_link_enabed_eth.phy_manager_link_eth_enabled = mlxsw_reg_pddr_page_data_pddr_operation_info_page_pm_le_pddr_phy_manager_link_enabed_eth_phy_manager_link_eth_enabled_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.cp_le.pddr_c2p_link_enabed_ib.core_to_phy_link_width_enabled = mlxsw_reg_pddr_page_data_pddr_operation_info_page_cp_le_pddr_c2p_link_enabed_ib_core_to_phy_link_width_enabled_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.cp_le.pddr_c2p_link_enabed_ib.core_to_phy_link_proto_enabled = mlxsw_reg_pddr_page_data_pddr_operation_info_page_cp_le_pddr_c2p_link_enabed_ib_core_to_phy_link_proto_enabled_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.cp_le.pddr_c2p_link_enabed_eth.core_to_phy_link_eth_enabled = mlxsw_reg_pddr_page_data_pddr_operation_info_page_cp_le_pddr_c2p_link_enabed_eth_core_to_phy_link_eth_enabled_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.cable_proto_cap.pddr_cable_cap_ib.cable_link_width_cap = mlxsw_reg_pddr_page_data_pddr_operation_info_page_cable_proto_cap_pddr_cable_cap_ib_cable_link_width_cap_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.cable_proto_cap.pddr_cable_cap_ib.cable_link_speed_cap = mlxsw_reg_pddr_page_data_pddr_operation_info_page_cable_proto_cap_pddr_cable_cap_ib_cable_link_speed_cap_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.cable_proto_cap.pddr_cable_cap_eth.cable_ext_eth_proto_cap = mlxsw_reg_pddr_page_data_pddr_operation_info_page_cable_proto_cap_pddr_cable_cap_eth_cable_ext_eth_proto_cap_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.link_active.pddr_link_active_ib.link_width_active = mlxsw_reg_pddr_page_data_pddr_operation_info_page_link_active_pddr_link_active_ib_link_width_active_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.link_active.pddr_link_active_ib.link_speed_active = mlxsw_reg_pddr_page_data_pddr_operation_info_page_link_active_pddr_link_active_ib_link_speed_active_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.link_active.pddr_link_active_eth.link_eth_active = mlxsw_reg_pddr_page_data_pddr_operation_info_page_link_active_pddr_link_active_eth_link_eth_active_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.retran_mode_active = mlxsw_reg_pddr_page_data_pddr_operation_info_page_retran_mode_active_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.retran_mode_request = mlxsw_reg_pddr_page_data_pddr_operation_info_page_retran_mode_request_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.loopback_mode = mlxsw_reg_pddr_page_data_pddr_operation_info_page_loopback_mode_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.fec_mode_active = mlxsw_reg_pddr_page_data_pddr_operation_info_page_fec_mode_active_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.fec_mode_request = mlxsw_reg_pddr_page_data_pddr_operation_info_page_fec_mode_request_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.profile_fec_in_use = mlxsw_reg_pddr_page_data_pddr_operation_info_page_profile_fec_in_use_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.eth_25g_50g_fec_support = mlxsw_reg_pddr_page_data_pddr_operation_info_page_eth_25g_50g_fec_support_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.eth_100g_fec_support = mlxsw_reg_pddr_page_data_pddr_operation_info_page_eth_100g_fec_support_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.pd_link_enabled = mlxsw_reg_pddr_page_data_pddr_operation_info_page_pd_link_enabled_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.phy_hst_link_enabled = mlxsw_reg_pddr_page_data_pddr_operation_info_page_phy_hst_link_enabled_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.eth_an_link_enabled = mlxsw_reg_pddr_page_data_pddr_operation_info_page_eth_an_link_enabled_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.core_to_phy_state = mlxsw_reg_pddr_page_data_pddr_operation_info_page_core_to_phy_state_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.psi_fsm_state = mlxsw_reg_pddr_page_data_pddr_operation_info_page_psi_fsm_state_get(outbox);
        pddr_reg->page_data.pddr_operation_info_page.cable_proto_cap_ext = mlxsw_reg_pddr_page_data_pddr_operation_info_page_cable_proto_cap_ext_get(outbox);
        break;

    case SXD_PDDR_PAGE_SELECT_TROUBLESHOOTING_INFO_PAGE_E:
        pddr_reg->page_data.pddr_troubleshooting_page.group_opcode = mlxsw_reg_pddr_page_data_pddr_troubleshooting_page_group_opcode_get(outbox);
        switch (pddr_reg->page_data.pddr_troubleshooting_page.group_opcode) {
        case SXD_PDDR_GROUP_OPCODE_MONITOR_OPCODES_E:
            pddr_reg->page_data.pddr_troubleshooting_page.status_opcode.pddr_monitor_opcode.monitor_opcode = mlxsw_reg_pddr_page_data_pddr_troubleshooting_page_status_opcode_pddr_monitor_opcode_monitor_opcode_get(outbox);
            break;

        case SXD_PDDR_GROUP_OPCODE_ADVANCED_DEBUG_OPCODES_E:
            pddr_reg->page_data.pddr_troubleshooting_page.status_opcode.pddr_advanced_opcode.advanced_opcode = mlxsw_reg_pddr_page_data_pddr_troubleshooting_page_status_opcode_pddr_advanced_opcode_advanced_opcode_get(outbox);
            break;

        default:
            /* Other types not supported yet */
            break;
        }
        pddr_reg->page_data.pddr_troubleshooting_page.user_feedback_data = mlxsw_reg_pddr_page_data_pddr_troubleshooting_page_user_feedback_data_get(outbox);
        pddr_reg->page_data.pddr_troubleshooting_page.user_feedback_index = mlxsw_reg_pddr_page_data_pddr_troubleshooting_page_user_feedback_index_get(outbox);
        mlxsw_reg_pddr_page_data_pddr_troubleshooting_page_status_message_memcpy_from(outbox, (char *)pddr_reg->page_data.pddr_troubleshooting_page.status_message);
        break;

    case SXD_PDDR_PAGE_SELECT_PHY_INFO_PAGE_E:
        pddr_reg->page_data.pddr_phy_info_page.remote_device_type = mlxsw_reg_pddr_page_data_pddr_phy_info_page_remote_device_type_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.port_notifications = mlxsw_reg_pddr_page_data_pddr_phy_info_page_port_notifications_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.num_of_negotiation_attempts = mlxsw_reg_pddr_page_data_pddr_phy_info_page_num_of_negotiation_attempts_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.ib_revision = mlxsw_reg_pddr_page_data_pddr_phy_info_page_ib_revision_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.lp_ib_revision = mlxsw_reg_pddr_page_data_pddr_phy_info_page_lp_ib_revision_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.hw_link_phy_state = mlxsw_reg_pddr_page_data_pddr_phy_info_page_hw_link_phy_state_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.phy_manger_disable_mask = mlxsw_reg_pddr_page_data_pddr_phy_info_page_phy_manger_disable_mask_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.pcs_phy_state = mlxsw_reg_pddr_page_data_pddr_phy_info_page_pcs_phy_state_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.lp_proto_enabled = mlxsw_reg_pddr_page_data_pddr_phy_info_page_lp_proto_enabled_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.lp_fec_mode_support = mlxsw_reg_pddr_page_data_pddr_phy_info_page_lp_fec_mode_support_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.lp_fec_mode_request = mlxsw_reg_pddr_page_data_pddr_phy_info_page_lp_fec_mode_request_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.ib_last_link_down_reason = mlxsw_reg_pddr_page_data_pddr_phy_info_page_ib_last_link_down_reason_get(outbox);
        mlxsw_reg_pddr_page_data_pddr_phy_info_page_eth_last_link_down_lane_memcpy_from(outbox, (char *)pddr_reg->page_data.pddr_phy_info_page.eth_last_link_down_lane);
        pddr_reg->page_data.pddr_phy_info_page.speed_deg_db = mlxsw_reg_pddr_page_data_pddr_phy_info_page_speed_deg_db_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.degrade_grade_lane0 = mlxsw_reg_pddr_page_data_pddr_phy_info_page_degrade_grade_lane0_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.degrade_grade_lane1 = mlxsw_reg_pddr_page_data_pddr_phy_info_page_degrade_grade_lane1_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.degrade_grade_lane2 = mlxsw_reg_pddr_page_data_pddr_phy_info_page_degrade_grade_lane2_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.degrade_grade_lane3 = mlxsw_reg_pddr_page_data_pddr_phy_info_page_degrade_grade_lane3_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.num_of_presets_tested_lane0 = mlxsw_reg_pddr_page_data_pddr_phy_info_page_num_of_presets_tested_lane0_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.num_of_presets_tested_lane1 = mlxsw_reg_pddr_page_data_pddr_phy_info_page_num_of_presets_tested_lane1_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.num_of_presets_tested_lane2 = mlxsw_reg_pddr_page_data_pddr_phy_info_page_num_of_presets_tested_lane2_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.num_of_presets_tested_lane3 = mlxsw_reg_pddr_page_data_pddr_phy_info_page_num_of_presets_tested_lane3_get(outbox);
        mlxsw_reg_pddr_page_data_pddr_phy_info_page_kr_startup_fsm_lane_memcpy_from(outbox, (char *)pddr_reg->page_data.pddr_phy_info_page.kr_startup_fsm_lane);
        pddr_reg->page_data.pddr_phy_info_page.eth_an_debug_indication = mlxsw_reg_pddr_page_data_pddr_phy_info_page_eth_an_debug_indication_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.cdr_not_locked_cnt = mlxsw_reg_pddr_page_data_pddr_phy_info_page_cdr_not_locked_cnt_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.fall_from_cfg_idle_cnt = mlxsw_reg_pddr_page_data_pddr_phy_info_page_fall_from_cfg_idle_cnt_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.fall_from_cfg_idle_cdr_cnt = mlxsw_reg_pddr_page_data_pddr_phy_info_page_fall_from_cfg_idle_cdr_cnt_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.eth_an_watchdog_cnt = mlxsw_reg_pddr_page_data_pddr_phy_info_page_eth_an_watchdog_cnt_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.rounds_waited_for_peer_to_end_test = mlxsw_reg_pddr_page_data_pddr_phy_info_page_rounds_waited_for_peer_to_end_test_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.ib_phy_fsm_state_trace = mlxsw_reg_pddr_page_data_pddr_phy_info_page_ib_phy_fsm_state_trace_get(outbox);
        for (i = 0; i < SXD_PDDR_KR_STARTUP_DEBUG_INDICATIONS_NUM; i++) {
            pddr_reg->page_data.pddr_phy_info_page.kr_startup_debug_indications[i] = mlxsw_reg_pddr_page_data_pddr_phy_info_page_kr_startup_debug_indications_get(outbox, i);
        }
        pddr_reg->page_data.pddr_phy_info_page.tx_tuning_stages_lane0 = mlxsw_reg_pddr_page_data_pddr_phy_info_page_tx_tuning_stages_lane0_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.tx_tuning_stages_lane1 = mlxsw_reg_pddr_page_data_pddr_phy_info_page_tx_tuning_stages_lane1_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.tx_tuning_stages_lane2 = mlxsw_reg_pddr_page_data_pddr_phy_info_page_tx_tuning_stages_lane2_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.tx_tuning_stages_lane3 = mlxsw_reg_pddr_page_data_pddr_phy_info_page_tx_tuning_stages_lane3_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.irisc_status = mlxsw_reg_pddr_page_data_pddr_phy_info_page_irisc_status_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.stamping_reason = mlxsw_reg_pddr_page_data_pddr_phy_info_page_stamping_reason_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.kr_frame_lock_tuning_failure_events_count = mlxsw_reg_pddr_page_data_pddr_phy_info_page_kr_frame_lock_tuning_failure_events_count_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.kr_full_tuning_failure_count = mlxsw_reg_pddr_page_data_pddr_phy_info_page_kr_full_tuning_failure_count_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.ib_debug_indication = mlxsw_reg_pddr_page_data_pddr_phy_info_page_ib_debug_indication_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.pm_debug_indication = mlxsw_reg_pddr_page_data_pddr_phy_info_page_pm_debug_indication_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.pd_debug_indication = mlxsw_reg_pddr_page_data_pddr_phy_info_page_pd_debug_indication_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.psi_collision1 = mlxsw_reg_pddr_page_data_pddr_phy_info_page_psi_collision1_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.psi_collision2 = mlxsw_reg_pddr_page_data_pddr_phy_info_page_psi_collision2_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.hst_mismatch_reason = mlxsw_reg_pddr_page_data_pddr_phy_info_page_hst_mismatch_reason_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.fp_signal_detect_count = mlxsw_reg_pddr_page_data_pddr_phy_info_page_fp_signal_detect_count_get(outbox);
        pddr_reg->page_data.pddr_phy_info_page.pd_count = mlxsw_reg_pddr_page_data_pddr_phy_info_page_pd_count_get(outbox);
        break;

    case SXD_PDDR_PAGE_SELECT_MODULE_INFO_PAGE_E:
        pddr_reg->page_data.pddr_module_info.cable_technology = mlxsw_reg_pddr_page_data_pddr_module_info_cable_technology_get(outbox);
        pddr_reg->page_data.pddr_module_info.cable_breakout = mlxsw_reg_pddr_page_data_pddr_module_info_cable_breakout_get(outbox);
        pddr_reg->page_data.pddr_module_info.ext_ethernet_compliance_code = mlxsw_reg_pddr_page_data_pddr_module_info_ext_ethernet_compliance_code_get(outbox);
        pddr_reg->page_data.pddr_module_info.ethernet_compliance_code = mlxsw_reg_pddr_page_data_pddr_module_info_ethernet_compliance_code_get(outbox);
        pddr_reg->page_data.pddr_module_info.cable_type = mlxsw_reg_pddr_page_data_pddr_module_info_cable_type_get(outbox);
        pddr_reg->page_data.pddr_module_info.cable_vendor = mlxsw_reg_pddr_page_data_pddr_module_info_cable_vendor_get(outbox);
        pddr_reg->page_data.pddr_module_info.cable_length = mlxsw_reg_pddr_page_data_pddr_module_info_cable_length_get(outbox);
        pddr_reg->page_data.pddr_module_info.cable_identifier = mlxsw_reg_pddr_page_data_pddr_module_info_cable_identifier_get(outbox);
        pddr_reg->page_data.pddr_module_info.cable_power_class = mlxsw_reg_pddr_page_data_pddr_module_info_cable_power_class_get(outbox);
        pddr_reg->page_data.pddr_module_info.max_power = mlxsw_reg_pddr_page_data_pddr_module_info_max_power_get(outbox);
        pddr_reg->page_data.pddr_module_info.cable_rx_amp = mlxsw_reg_pddr_page_data_pddr_module_info_cable_rx_amp_get(outbox);
        pddr_reg->page_data.pddr_module_info.cable_rx_emphasis = mlxsw_reg_pddr_page_data_pddr_module_info_cable_rx_emphasis_get(outbox);
        pddr_reg->page_data.pddr_module_info.cable_tx_equalization = mlxsw_reg_pddr_page_data_pddr_module_info_cable_tx_equalization_get(outbox);
        pddr_reg->page_data.pddr_module_info.cable_attenuation_25g = mlxsw_reg_pddr_page_data_pddr_module_info_cable_attenuation_25g_get(outbox);
        pddr_reg->page_data.pddr_module_info.cable_attenuation_12g = mlxsw_reg_pddr_page_data_pddr_module_info_cable_attenuation_12g_get(outbox);
        pddr_reg->page_data.pddr_module_info.cable_attenuation_7g = mlxsw_reg_pddr_page_data_pddr_module_info_cable_attenuation_7g_get(outbox);
        pddr_reg->page_data.pddr_module_info.cable_attenuation_5g = mlxsw_reg_pddr_page_data_pddr_module_info_cable_attenuation_5g_get(outbox);
        pddr_reg->page_data.pddr_module_info.cable_rx_post_emphasis = mlxsw_reg_pddr_page_data_pddr_module_info_cable_rx_post_emphasis_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_cdr_cap = mlxsw_reg_pddr_page_data_pddr_module_info_rx_cdr_cap_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_cdr_cap = mlxsw_reg_pddr_page_data_pddr_module_info_tx_cdr_cap_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_cdr_state = mlxsw_reg_pddr_page_data_pddr_module_info_rx_cdr_state_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_cdr_state = mlxsw_reg_pddr_page_data_pddr_module_info_tx_cdr_state_get(outbox);
        for (i = 0; i < SXD_PDDR_VENDOR_NAME_NUM; i++) {
            pddr_reg->page_data.pddr_module_info.vendor_name[i] = mlxsw_reg_pddr_page_data_pddr_module_info_vendor_name_get(outbox, i);
        }
        for (i = 0; i < SXD_PDDR_VENDOR_PN_NUM; i++) {
            pddr_reg->page_data.pddr_module_info.vendor_pn[i] = mlxsw_reg_pddr_page_data_pddr_module_info_vendor_pn_get(outbox, i);
        }
        pddr_reg->page_data.pddr_module_info.vendor_rev = mlxsw_reg_pddr_page_data_pddr_module_info_vendor_rev_get(outbox);
        pddr_reg->page_data.pddr_module_info.fw_version = mlxsw_reg_pddr_page_data_pddr_module_info_fw_version_get(outbox);
        for (i = 0; i < SXD_PDDR_VENDOR_SN_NUM; i++) {
            pddr_reg->page_data.pddr_module_info.vendor_sn[i] = mlxsw_reg_pddr_page_data_pddr_module_info_vendor_sn_get(outbox, i);
        }
        pddr_reg->page_data.pddr_module_info.temperature = mlxsw_reg_pddr_page_data_pddr_module_info_temperature_get(outbox);
        pddr_reg->page_data.pddr_module_info.voltage = mlxsw_reg_pddr_page_data_pddr_module_info_voltage_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_power_lane0 = mlxsw_reg_pddr_page_data_pddr_module_info_rx_power_lane0_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_power_lane1 = mlxsw_reg_pddr_page_data_pddr_module_info_rx_power_lane1_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_power_lane2 = mlxsw_reg_pddr_page_data_pddr_module_info_rx_power_lane2_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_power_lane3 = mlxsw_reg_pddr_page_data_pddr_module_info_rx_power_lane3_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_power_lane4 = mlxsw_reg_pddr_page_data_pddr_module_info_rx_power_lane4_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_power_lane5 = mlxsw_reg_pddr_page_data_pddr_module_info_rx_power_lane5_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_power_lane6 = mlxsw_reg_pddr_page_data_pddr_module_info_rx_power_lane6_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_power_lane7 = mlxsw_reg_pddr_page_data_pddr_module_info_rx_power_lane7_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_power_lane0 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_power_lane0_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_power_lane1 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_power_lane1_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_power_lane2 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_power_lane2_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_power_lane3 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_power_lane3_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_power_lane4 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_power_lane4_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_power_lane5 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_power_lane5_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_power_lane6 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_power_lane6_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_power_lane7 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_power_lane7_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_bias_lane0 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_bias_lane0_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_bias_lane1 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_bias_lane1_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_bias_lane2 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_bias_lane2_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_bias_lane3 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_bias_lane3_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_bias_lane4 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_bias_lane4_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_bias_lane5 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_bias_lane5_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_bias_lane6 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_bias_lane6_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_bias_lane7 = mlxsw_reg_pddr_page_data_pddr_module_info_tx_bias_lane7_get(outbox);
        pddr_reg->page_data.pddr_module_info.temperature_high_th = mlxsw_reg_pddr_page_data_pddr_module_info_temperature_high_th_get(outbox);
        pddr_reg->page_data.pddr_module_info.temperature_low_th = mlxsw_reg_pddr_page_data_pddr_module_info_temperature_low_th_get(outbox);
        pddr_reg->page_data.pddr_module_info.voltage_high_th = mlxsw_reg_pddr_page_data_pddr_module_info_voltage_high_th_get(outbox);
        pddr_reg->page_data.pddr_module_info.voltage_low_th = mlxsw_reg_pddr_page_data_pddr_module_info_voltage_low_th_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_power_high_th = mlxsw_reg_pddr_page_data_pddr_module_info_rx_power_high_th_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_power_low_th = mlxsw_reg_pddr_page_data_pddr_module_info_rx_power_low_th_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_power_high_th = mlxsw_reg_pddr_page_data_pddr_module_info_tx_power_high_th_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_power_low_th = mlxsw_reg_pddr_page_data_pddr_module_info_tx_power_low_th_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_bias_high_th = mlxsw_reg_pddr_page_data_pddr_module_info_tx_bias_high_th_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_bias_low_th = mlxsw_reg_pddr_page_data_pddr_module_info_tx_bias_low_th_get(outbox);
        pddr_reg->page_data.pddr_module_info.module_st = mlxsw_reg_pddr_page_data_pddr_module_info_module_st_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_power_type = mlxsw_reg_pddr_page_data_pddr_module_info_rx_power_type_get(outbox);
        pddr_reg->page_data.pddr_module_info.did_cap = mlxsw_reg_pddr_page_data_pddr_module_info_did_cap_get(outbox);
        pddr_reg->page_data.pddr_module_info.smf_length = mlxsw_reg_pddr_page_data_pddr_module_info_smf_length_get(outbox);
        pddr_reg->page_data.pddr_module_info.wavelength = mlxsw_reg_pddr_page_data_pddr_module_info_wavelength_get(outbox);
        pddr_reg->page_data.pddr_module_info.active_set_host_compliance_code = mlxsw_reg_pddr_page_data_pddr_module_info_active_set_host_compliance_code_get(outbox);
        pddr_reg->page_data.pddr_module_info.active_set_media_compliance_code = mlxsw_reg_pddr_page_data_pddr_module_info_active_set_media_compliance_code_get(outbox);
        pddr_reg->page_data.pddr_module_info.ib_compliance_code = mlxsw_reg_pddr_page_data_pddr_module_info_ib_compliance_code_get(outbox);
        pddr_reg->page_data.pddr_module_info.nbr250 = mlxsw_reg_pddr_page_data_pddr_module_info_nbr250_get(outbox);
        pddr_reg->page_data.pddr_module_info.nbr100 = mlxsw_reg_pddr_page_data_pddr_module_info_nbr100_get(outbox);
        pddr_reg->page_data.pddr_module_info.monitor_cap_mask = mlxsw_reg_pddr_page_data_pddr_module_info_monitor_cap_mask_get(outbox);
        pddr_reg->page_data.pddr_module_info.ib_width = mlxsw_reg_pddr_page_data_pddr_module_info_ib_width_get(outbox);
        pddr_reg->page_data.pddr_module_info.dp_st_lane0 = mlxsw_reg_pddr_page_data_pddr_module_info_dp_st_lane0_get(outbox);
        pddr_reg->page_data.pddr_module_info.dp_st_lane1 = mlxsw_reg_pddr_page_data_pddr_module_info_dp_st_lane1_get(outbox);
        pddr_reg->page_data.pddr_module_info.dp_st_lane2 = mlxsw_reg_pddr_page_data_pddr_module_info_dp_st_lane2_get(outbox);
        pddr_reg->page_data.pddr_module_info.dp_st_lane3 = mlxsw_reg_pddr_page_data_pddr_module_info_dp_st_lane3_get(outbox);
        pddr_reg->page_data.pddr_module_info.dp_st_lane4 = mlxsw_reg_pddr_page_data_pddr_module_info_dp_st_lane4_get(outbox);
        pddr_reg->page_data.pddr_module_info.dp_st_lane5 = mlxsw_reg_pddr_page_data_pddr_module_info_dp_st_lane5_get(outbox);
        pddr_reg->page_data.pddr_module_info.dp_st_lane6 = mlxsw_reg_pddr_page_data_pddr_module_info_dp_st_lane6_get(outbox);
        pddr_reg->page_data.pddr_module_info.dp_st_lane7 = mlxsw_reg_pddr_page_data_pddr_module_info_dp_st_lane7_get(outbox);
        pddr_reg->page_data.pddr_module_info.length_om2 = mlxsw_reg_pddr_page_data_pddr_module_info_length_om2_get(outbox);
        pddr_reg->page_data.pddr_module_info.length_om3 = mlxsw_reg_pddr_page_data_pddr_module_info_length_om3_get(outbox);
        pddr_reg->page_data.pddr_module_info.length_om4 = mlxsw_reg_pddr_page_data_pddr_module_info_length_om4_get(outbox);
        pddr_reg->page_data.pddr_module_info.length_om5 = mlxsw_reg_pddr_page_data_pddr_module_info_length_om5_get(outbox);
        pddr_reg->page_data.pddr_module_info.length_om1 = mlxsw_reg_pddr_page_data_pddr_module_info_length_om1_get(outbox);
        pddr_reg->page_data.pddr_module_info.wavelength_tolerance = mlxsw_reg_pddr_page_data_pddr_module_info_wavelength_tolerance_get(outbox);
        pddr_reg->page_data.pddr_module_info.memory_map_rev = mlxsw_reg_pddr_page_data_pddr_module_info_memory_map_rev_get(outbox);
        pddr_reg->page_data.pddr_module_info.memory_map_compliance = mlxsw_reg_pddr_page_data_pddr_module_info_memory_map_compliance_get(outbox);
        pddr_reg->page_data.pddr_module_info.date_code = mlxsw_reg_pddr_page_data_pddr_module_info_date_code_get(outbox);
        pddr_reg->page_data.pddr_module_info.connector_type = mlxsw_reg_pddr_page_data_pddr_module_info_connector_type_get(outbox);
        pddr_reg->page_data.pddr_module_info.vendor_oui = mlxsw_reg_pddr_page_data_pddr_module_info_vendor_oui_get(outbox);
        pddr_reg->page_data.pddr_module_info.tx_input_freq_sync = mlxsw_reg_pddr_page_data_pddr_module_info_tx_input_freq_sync_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_input_valid = mlxsw_reg_pddr_page_data_pddr_module_info_rx_input_valid_get(outbox);
        pddr_reg->page_data.pddr_module_info.rx_output_valid = mlxsw_reg_pddr_page_data_pddr_module_info_rx_output_valid_get(outbox);
        pddr_reg->page_data.pddr_module_info.max_fiber_length = mlxsw_reg_pddr_page_data_pddr_module_info_max_fiber_length_get(outbox);
        pddr_reg->page_data.pddr_module_info.error_code = mlxsw_reg_pddr_page_data_pddr_module_info_error_code_get(outbox);
        break;

    case SXD_PDDR_PAGE_SELECT_PORT_EVENTS_PAGE_E:
        pddr_reg->page_data.pddr_port_events_page_layout.invalid_fsm_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_invalid_fsm_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.invalid_fsm_ps = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_invalid_fsm_ps_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.kr_false_ready_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_kr_false_ready_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.kr_false_ready = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_kr_false_ready_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.mod_req_nack_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_mod_req_nack_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.mod_req_nack = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_mod_req_nack_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.mod_req_busy_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_mod_req_busy_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.mod_req_busy = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_mod_req_busy_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.mod_config_to_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_mod_config_to_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.mod_config_to = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_mod_config_to_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.mod_adapt_faild_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_mod_adapt_faild_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.mod_adapt_faild = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_mod_adapt_faild_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.pm_fifo_full_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_pm_fifo_full_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.pm_fifo_full = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_pm_fifo_full_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.protocol_check_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_protocol_check_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.protocol_check = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_protocol_check_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.input_event_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_input_event_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.input_event = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_input_event_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.lane_mapping_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_lane_mapping_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.lane_mapping = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_lane_mapping_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.qsfp_zero_atten_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_qsfp_zero_atten_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.qsfp_zero_atten = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_qsfp_zero_atten_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.mono_reach_low_limit_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_mono_reach_low_limit_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.mono_reach_low_limit = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_mono_reach_low_limit_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.mono_reach_high_limit_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_mono_reach_high_limit_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.mono_reach_high_limit = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_mono_reach_high_limit_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.mono_flow_height_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_mono_flow_height_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.mono_flow_height = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_mono_flow_height_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.single_gains_bad_val_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_single_gains_bad_val_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.single_gains_bad_val = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_single_gains_bad_val_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.init_all_gains_bad_val_sv = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_init_all_gains_bad_val_sv_get(outbox);
        pddr_reg->page_data.pddr_port_events_page_layout.init_all_gains_bad_val = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_init_all_gains_bad_val_get(outbox);
        for (i = 0; i < SXD_PDDR_CLR_MASK_NUM; i++) {
            pddr_reg->page_data.pddr_port_events_page_layout.clr_mask[i] = mlxsw_reg_pddr_page_data_pddr_port_events_page_layout_clr_mask_get(outbox, i);
        }
        break;

    case SXD_PDDR_PAGE_SELECT_DEVICE_EVENTS_PAGE_E:
        pddr_reg->page_data.pddr_device_events_page.invalid_port_access_sv = mlxsw_reg_pddr_page_data_pddr_device_events_page_invalid_port_access_sv_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.invalid_port_access = mlxsw_reg_pddr_page_data_pddr_device_events_page_invalid_port_access_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.pll_state_sv_1 = mlxsw_reg_pddr_page_data_pddr_device_events_page_pll_state_sv_1_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.pll_state_mask_center1 = mlxsw_reg_pddr_page_data_pddr_device_events_page_pll_state_mask_center1_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.pll_state_sv_0 = mlxsw_reg_pddr_page_data_pddr_device_events_page_pll_state_sv_0_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.pll_state_mask_center0 = mlxsw_reg_pddr_page_data_pddr_device_events_page_pll_state_mask_center0_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.main_irisc_timeout = mlxsw_reg_pddr_page_data_pddr_device_events_page_main_irisc_timeout_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.tile_irisc_timeout = mlxsw_reg_pddr_page_data_pddr_device_events_page_tile_irisc_timeout_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout0 = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout0_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout1 = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout1_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout2 = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout2_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout3 = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout3_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout4 = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout4_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.cr_space_timeout_mcm_main = mlxsw_reg_pddr_page_data_pddr_device_events_page_cr_space_timeout_mcm_main_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.cr_space_timeout_sv = mlxsw_reg_pddr_page_data_pddr_device_events_page_cr_space_timeout_sv_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.cr_space_timeout = mlxsw_reg_pddr_page_data_pddr_device_events_page_cr_space_timeout_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.analog_phy_to_sv = mlxsw_reg_pddr_page_data_pddr_device_events_page_analog_phy_to_sv_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.analog_phy_to = mlxsw_reg_pddr_page_data_pddr_device_events_page_analog_phy_to_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.logical_phy_to_sv = mlxsw_reg_pddr_page_data_pddr_device_events_page_logical_phy_to_sv_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.logical_phy_to = mlxsw_reg_pddr_page_data_pddr_device_events_page_logical_phy_to_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.varactors_calib_fail_center1_sv = mlxsw_reg_pddr_page_data_pddr_device_events_page_varactors_calib_fail_center1_sv_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.varactors_calib_fail_center1 = mlxsw_reg_pddr_page_data_pddr_device_events_page_varactors_calib_fail_center1_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.varactors_calib_fail_center0_sv = mlxsw_reg_pddr_page_data_pddr_device_events_page_varactors_calib_fail_center0_sv_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.varactors_calib_fail_center0 = mlxsw_reg_pddr_page_data_pddr_device_events_page_varactors_calib_fail_center0_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.irisc_stuck_mask_sv = mlxsw_reg_pddr_page_data_pddr_device_events_page_irisc_stuck_mask_sv_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.irisc_stuck_mask = mlxsw_reg_pddr_page_data_pddr_device_events_page_irisc_stuck_mask_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.pll_lock_sv_1 = mlxsw_reg_pddr_page_data_pddr_device_events_page_pll_lock_sv_1_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.pll_unlocl_mask_center1 = mlxsw_reg_pddr_page_data_pddr_device_events_page_pll_unlocl_mask_center1_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.pll_lock_sv_0 = mlxsw_reg_pddr_page_data_pddr_device_events_page_pll_lock_sv_0_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.pll_unlocl_mask_center0 = mlxsw_reg_pddr_page_data_pddr_device_events_page_pll_unlocl_mask_center0_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.uc_stack_overflow = mlxsw_reg_pddr_page_data_pddr_device_events_page_uc_stack_overflow_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.uc_crspace_timeout = mlxsw_reg_pddr_page_data_pddr_device_events_page_uc_crspace_timeout_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.pwr_governor_err_sv = mlxsw_reg_pddr_page_data_pddr_device_events_page_pwr_governor_err_sv_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.pwr_governor_err = mlxsw_reg_pddr_page_data_pddr_device_events_page_pwr_governor_err_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.iopl_err_center1_sv = mlxsw_reg_pddr_page_data_pddr_device_events_page_iopl_err_center1_sv_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.iopl_err_center1 = mlxsw_reg_pddr_page_data_pddr_device_events_page_iopl_err_center1_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.iopl_err_center0_sv = mlxsw_reg_pddr_page_data_pddr_device_events_page_iopl_err_center0_sv_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.iopl_err_center0 = mlxsw_reg_pddr_page_data_pddr_device_events_page_iopl_err_center0_get(outbox);
        for (i = 0; i < SXD_PDDR_CLR_MASK_NUM; i++) {
            pddr_reg->page_data.pddr_device_events_page.clr_mask[i] = mlxsw_reg_pddr_page_data_pddr_device_events_page_clr_mask_get(outbox, i);
        }
        pddr_reg->page_data.pddr_device_events_page.main_irisc_address = mlxsw_reg_pddr_page_data_pddr_device_events_page_main_irisc_address_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.main_irisc_ip = mlxsw_reg_pddr_page_data_pddr_device_events_page_main_irisc_ip_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.tile_irisc_address = mlxsw_reg_pddr_page_data_pddr_device_events_page_tile_irisc_address_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.tile_irisc_ip = mlxsw_reg_pddr_page_data_pddr_device_events_page_tile_irisc_ip_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout0_address = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout0_address_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout1_address = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout1_address_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout2_address = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout2_address_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout3_address = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout3_address_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout4_address = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout4_address_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout0_cluster = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout0_cluster_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout1_cluster = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout1_cluster_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout2_cluster = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout2_cluster_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout3_cluster = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout3_cluster_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.plu_timeout4_cluster = mlxsw_reg_pddr_page_data_pddr_device_events_page_plu_timeout4_cluster_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.irisc_tile_idx = mlxsw_reg_pddr_page_data_pddr_device_events_page_irisc_tile_idx_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.uc_crspace_timeout_lane = mlxsw_reg_pddr_page_data_pddr_device_events_page_uc_crspace_timeout_lane_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.uc_crspace_timeout_cl = mlxsw_reg_pddr_page_data_pddr_device_events_page_uc_crspace_timeout_cl_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.uc_stack_overflow_lane = mlxsw_reg_pddr_page_data_pddr_device_events_page_uc_stack_overflow_lane_get(outbox);
        pddr_reg->page_data.pddr_device_events_page.uc_stack_overflow_cl = mlxsw_reg_pddr_page_data_pddr_device_events_page_uc_stack_overflow_cl_get(outbox);
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_DOWN_INFO_E:
        pddr_reg->page_data.pddr_link_down_info_page.down_blame = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_down_blame_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_page.local_reason_opcode = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_local_reason_opcode_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_page.remote_reason_opcode = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_remote_reason_opcode_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_page.e2e_reason_opcode = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_e2e_reason_opcode_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_page.last_ber_mantissa = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_last_ber_mantissa_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_page.last_ber_exp = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_last_ber_exp_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_page.ber_mantissa = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_ber_mantissa_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_page.ber_exp = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_ber_exp_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_page.min_ber_mantissa = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_min_ber_mantissa_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_page.min_ber_exp = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_min_ber_exp_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_page.max_ber_mantissa = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_max_ber_mantissa_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_page.max_ber_exp = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_max_ber_exp_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_page.num_of_ber_alarams = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_num_of_ber_alarams_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_page.time_to_link_down_to_disable = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_time_to_link_down_to_disable_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_page.time_to_link_down_to_rx_loss = mlxsw_reg_pddr_page_data_pddr_link_down_info_page_time_to_link_down_to_rx_loss_get(outbox);
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_DOWN_EVENTS_E:
        pddr_reg->page_data.pddr_link_down_events_page.ib_port_events = mlxsw_reg_pddr_page_data_pddr_link_down_events_page_ib_port_events_get(outbox);
        pddr_reg->page_data.pddr_link_down_events_page.etherent_port_events = mlxsw_reg_pddr_page_data_pddr_link_down_events_page_etherent_port_events_get(outbox);
        pddr_reg->page_data.pddr_link_down_events_page.general_port_events = mlxsw_reg_pddr_page_data_pddr_link_down_events_page_general_port_events_get(outbox);
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_UP_INFO_E:
        pddr_reg->page_data.pddr_link_up_info_page.up_reason_pwr = mlxsw_reg_pddr_page_data_pddr_link_up_info_page_up_reason_pwr_get(outbox);
        pddr_reg->page_data.pddr_link_up_info_page.up_reason_drv = mlxsw_reg_pddr_page_data_pddr_link_up_info_page_up_reason_drv_get(outbox);
        pddr_reg->page_data.pddr_link_up_info_page.up_reason_mng = mlxsw_reg_pddr_page_data_pddr_link_up_info_page_up_reason_mng_get(outbox);
        pddr_reg->page_data.pddr_link_up_info_page.time_to_link_up = mlxsw_reg_pddr_page_data_pddr_link_up_info_page_time_to_link_up_get(outbox);
        pddr_reg->page_data.pddr_link_up_info_page.fast_link_up_status = mlxsw_reg_pddr_page_data_pddr_link_up_info_page_fast_link_up_status_get(outbox);
        pddr_reg->page_data.pddr_link_up_info_page.time_to_link_up_phy_up_to_active = mlxsw_reg_pddr_page_data_pddr_link_up_info_page_time_to_link_up_phy_up_to_active_get(outbox);
        pddr_reg->page_data.pddr_link_up_info_page.time_to_link_up_sd_to_phy_up = mlxsw_reg_pddr_page_data_pddr_link_up_info_page_time_to_link_up_sd_to_phy_up_get(outbox);
        pddr_reg->page_data.pddr_link_up_info_page.time_to_link_up_disable_to_sd = mlxsw_reg_pddr_page_data_pddr_link_up_info_page_time_to_link_up_disable_to_sd_get(outbox);
        pddr_reg->page_data.pddr_link_up_info_page.time_to_link_up_disable_to_pd = mlxsw_reg_pddr_page_data_pddr_link_up_info_page_time_to_link_up_disable_to_pd_get(outbox);
        break;

    case SXD_PDDR_PAGE_SELECT_MODULE_LATCHED_FLAG_INFO_PAGE_E:
        pddr_reg->page_data.module_latched_flag_info.temp_flags = mlxsw_reg_pddr_page_data_module_latched_flag_info_temp_flags_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.vcc_flags = mlxsw_reg_pddr_page_data_module_latched_flag_info_vcc_flags_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.mod_fw_fault = mlxsw_reg_pddr_page_data_module_latched_flag_info_mod_fw_fault_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.dp_fw_fault = mlxsw_reg_pddr_page_data_module_latched_flag_info_dp_fw_fault_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.tx_fault = mlxsw_reg_pddr_page_data_module_latched_flag_info_tx_fault_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.tx_los = mlxsw_reg_pddr_page_data_module_latched_flag_info_tx_los_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.tx_cdr_lol = mlxsw_reg_pddr_page_data_module_latched_flag_info_tx_cdr_lol_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.tx_ad_eq_fault = mlxsw_reg_pddr_page_data_module_latched_flag_info_tx_ad_eq_fault_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.tx_power_hi_al = mlxsw_reg_pddr_page_data_module_latched_flag_info_tx_power_hi_al_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.tx_power_lo_al = mlxsw_reg_pddr_page_data_module_latched_flag_info_tx_power_lo_al_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.tx_power_hi_war = mlxsw_reg_pddr_page_data_module_latched_flag_info_tx_power_hi_war_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.tx_power_lo_war = mlxsw_reg_pddr_page_data_module_latched_flag_info_tx_power_lo_war_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.tx_bias_hi_al = mlxsw_reg_pddr_page_data_module_latched_flag_info_tx_bias_hi_al_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.tx_bias_lo_al = mlxsw_reg_pddr_page_data_module_latched_flag_info_tx_bias_lo_al_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.tx_bias_hi_war = mlxsw_reg_pddr_page_data_module_latched_flag_info_tx_bias_hi_war_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.tx_bias_lo_war = mlxsw_reg_pddr_page_data_module_latched_flag_info_tx_bias_lo_war_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.rx_los = mlxsw_reg_pddr_page_data_module_latched_flag_info_rx_los_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.rx_cdr_lol = mlxsw_reg_pddr_page_data_module_latched_flag_info_rx_cdr_lol_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.rx_power_hi_al = mlxsw_reg_pddr_page_data_module_latched_flag_info_rx_power_hi_al_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.rx_power_lo_al = mlxsw_reg_pddr_page_data_module_latched_flag_info_rx_power_lo_al_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.rx_power_hi_war = mlxsw_reg_pddr_page_data_module_latched_flag_info_rx_power_hi_war_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.rx_power_lo_war = mlxsw_reg_pddr_page_data_module_latched_flag_info_rx_power_lo_war_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.rx_input_valid_change = mlxsw_reg_pddr_page_data_module_latched_flag_info_rx_input_valid_change_get(outbox);
        pddr_reg->page_data.module_latched_flag_info.rx_output_valid_change = mlxsw_reg_pddr_page_data_module_latched_flag_info_rx_output_valid_change_get(outbox);
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_DOWN_INFO_EXT_E:
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.cause_as_detected_not_on_slot = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_cause_as_detected_not_on_slot_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.cause_high_ser = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_cause_high_ser_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.cause_rs_rx_lane0_symbol_error = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_cause_rs_rx_lane0_symbol_error_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.cause_tx_lane_fifo_underrun_l0 = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_cause_tx_lane_fifo_underrun_l0_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.cause_deskew_fifo_overrun = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_cause_deskew_fifo_overrun_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.cause_fec_rx_sync_m_reached_max0 = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_cause_fec_rx_sync_m_reached_max0_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.symbol_error_counter_lo = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_symbol_error_counter_lo_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.symbol_error_counter_hi = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_symbol_error_counter_hi_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.uncorrectable_block_counter_lo = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_uncorrectable_block_counter_lo_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.uncorrectable_block_counter_hi = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_uncorrectable_block_counter_hi_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.link_fail_due_align_loss = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_link_fail_due_align_loss_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.block_lock_mask_at_fail_port1 = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_block_lock_mask_at_fail_port1_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.block_lock_mask_at_fail_port0 = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_block_lock_mask_at_fail_port0_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.link_down_counter = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_link_down_counter_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.effective_ber_coef = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_effective_ber_coef_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.effective_ber_magnitude = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_effective_ber_magnitude_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.raw_ber_coef = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_raw_ber_coef_get(outbox);
        pddr_reg->page_data.pddr_link_down_info_ext_16nm_lr.raw_ber_magnitude = mlxsw_reg_pddr_page_data_pddr_link_down_info_ext_16nm_lr_raw_ber_magnitude_get(outbox);
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_PARTNER_INFO_PAGE_E:
        break;

    case SXD_PDDR_PAGE_SELECT_MNG_DEBUG_PAGE_E:
        pddr_reg->page_data.pddr_mng_debug_page.fw_module_state = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_fw_module_state_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.fw_dp_state_lane7 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_fw_dp_state_lane7_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.fw_dp_state_lane6 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_fw_dp_state_lane6_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.fw_dp_state_lane5 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_fw_dp_state_lane5_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.fw_dp_state_lane4 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_fw_dp_state_lane4_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.fw_dp_state_lane3 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_fw_dp_state_lane3_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.fw_dp_state_lane2 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_fw_dp_state_lane2_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.fw_dp_state_lane1 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_fw_dp_state_lane1_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.fw_dp_state_lane0 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_fw_dp_state_lane0_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dp_req_status_lane7 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dp_req_status_lane7_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dp_req_status_lane6 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dp_req_status_lane6_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dp_req_status_lane5 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dp_req_status_lane5_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dp_req_status_lane4 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dp_req_status_lane4_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dp_req_status_lane3 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dp_req_status_lane3_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dp_req_status_lane2 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dp_req_status_lane2_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dp_req_status_lane1 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dp_req_status_lane1_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dp_req_status_lane0 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dp_req_status_lane0_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dpsm_apply_state_lane7 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dpsm_apply_state_lane7_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dpsm_apply_state_lane6 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dpsm_apply_state_lane6_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dpsm_apply_state_lane5 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dpsm_apply_state_lane5_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dpsm_apply_state_lane4 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dpsm_apply_state_lane4_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dpsm_apply_state_lane3 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dpsm_apply_state_lane3_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dpsm_apply_state_lane2 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dpsm_apply_state_lane2_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dpsm_apply_state_lane1 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dpsm_apply_state_lane1_get(outbox);
        pddr_reg->page_data.pddr_mng_debug_page.dpsm_apply_state_lane0 = mlxsw_reg_pddr_page_data_pddr_mng_debug_page_dpsm_apply_state_lane0_get(outbox);
        break;

    case SXD_PDDR_PAGE_SELECT_PHY_DEBUG_PAGE_E:
        pddr_reg->page_data.pddr_phy_debug_page.pport = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_pport_get(outbox);
        pddr_reg->page_data.pddr_phy_debug_page.trigger_active = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_trigger_active_get(outbox);
        pddr_reg->page_data.pddr_phy_debug_page.trigger_cond_state_event_val = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_trigger_cond_state_event_val_get(outbox);
        pddr_reg->page_data.pddr_phy_debug_page.trigger_cond_state_or_event = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_trigger_cond_state_or_event_get(outbox);
        pddr_reg->page_data.pddr_phy_debug_page.trigger_cond_fsm = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_trigger_cond_fsm_get(outbox);
        pddr_reg->page_data.pddr_phy_debug_page.pre_trigger_buff_mode = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_pre_trigger_buff_mode_get(outbox);
        pddr_reg->page_data.pddr_phy_debug_page.tracer_mode = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_tracer_mode_get(outbox);
        pddr_reg->page_data.pddr_phy_debug_page.reset_tracer = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_reset_tracer_get(outbox);
        pddr_reg->page_data.pddr_phy_debug_page.tracer_enable = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_tracer_enable_get(outbox);
        pddr_reg->page_data.pddr_phy_debug_page.fsm_mask = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_fsm_mask_get(outbox);
        pddr_reg->page_data.pddr_phy_debug_page.trigger_ptr = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_trigger_ptr_get(outbox);
        pddr_reg->page_data.pddr_phy_debug_page.buffer_size = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_buffer_size_get(outbox);
        pddr_reg->page_data.pddr_phy_debug_page.ptr_log_data = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_ptr_log_data_get(outbox);
        pddr_reg->page_data.pddr_phy_debug_page.ptr_next_write = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_ptr_next_write_get(outbox);
        pddr_reg->page_data.pddr_phy_debug_page.buffer_base_address = mlxsw_reg_pddr_page_data_pddr_phy_debug_page_buffer_base_address_get(outbox);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}
EXPORT_SYMBOL(__PDDR_decode);

int sx_ACCESS_REG_PDDR(struct sx_dev *dev, struct ku_access_pddr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PDDR_LEN >> 2) + 1;

    if (MLXSW_PDDR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PDDR_encode,
                                  __PDDR_decode,
                                  reg_len_dword,
                                  &reg_data->pddr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PDDR);

int sx_EMAD_ACCESS_REG_PDDR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pddr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PDDR_LEN >> 2) + 1;

    if (MLXSW_PDDR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PDDR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PDDR_encode,
                                     __PDDR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PDDR);

/************************************************
* SBCTR
***********************************************/
int __SBCTR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sbctr_reg *sbctr_reg = (struct ku_sbctr_reg*)ku_reg;

    mlxsw_reg_sbctr_ievent_set(inbox, sbctr_reg->ievent);
    mlxsw_reg_sbctr_local_port_set(inbox, sbctr_reg->local_port);
    mlxsw_reg_sbctr_lp_msb_set(inbox, sbctr_reg->lp_msb);
    mlxsw_reg_sbctr_dir_ing_set(inbox, sbctr_reg->dir_ing);


    return 0;
}

int __SBCTR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sbctr_reg *sbctr_reg = (struct ku_sbctr_reg*)ku_reg;

    sbctr_reg->ievent = mlxsw_reg_sbctr_ievent_get(outbox);
    sbctr_reg->local_port = mlxsw_reg_sbctr_local_port_get(outbox);
    sbctr_reg->lp_msb = mlxsw_reg_sbctr_lp_msb_get(outbox);
    sbctr_reg->dir_ing = mlxsw_reg_sbctr_dir_ing_get(outbox);
    sbctr_reg->fp = mlxsw_reg_sbctr_fp_get(outbox);
    sbctr_reg->entity = mlxsw_reg_sbctr_entity_get(outbox);
    sbctr_reg->tclass_vector_high = mlxsw_reg_sbctr_tclass_vector_high_get(outbox);
    sbctr_reg->tclass_vector_low = mlxsw_reg_sbctr_tclass_vector_low_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__SBCTR_decode);

int sx_ACCESS_REG_SBCTR(struct sx_dev *dev, struct ku_access_sbctr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_SBCTR_LEN >> 2) + 1;

    if (MLXSW_SBCTR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SBCTR_encode,
                                  __SBCTR_decode,
                                  reg_len_dword,
                                  &reg_data->sbctr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SBCTR);

int sx_EMAD_ACCESS_REG_SBCTR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sbctr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_SBCTR_LEN >> 2) + 1;

    if (MLXSW_SBCTR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_SBCTR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __SBCTR_encode,
                                     __SBCTR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_SBCTR);

/************************************************
* HMON
***********************************************/
int __HMON_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_hmon_reg *hmon_reg = (struct ku_hmon_reg*)ku_reg;
    uint32_t i = 0;

    mlxsw_reg_hmon_clr_set(inbox, hmon_reg->clr);
    mlxsw_reg_hmon_cprdq_set(inbox, hmon_reg->cprdq);
    mlxsw_reg_hmon_read_type_set(inbox, hmon_reg->read_type);
    mlxsw_reg_hmon_crdq_set(inbox, hmon_reg->crdq);
    for (i = 0; i < SXD_HMON_WQE_OVERFLOW_RDQ_NUM; i++) {
        mlxsw_reg_hmon_wqe_overflow_rdq_set(inbox, i, hmon_reg->wqe_overflow_rdq[i]);
    }


    return 0;
}

int __HMON_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_hmon_reg *hmon_reg = (struct ku_hmon_reg*)ku_reg;
    uint32_t i = 0;

    hmon_reg->clr = mlxsw_reg_hmon_clr_get(outbox);
    hmon_reg->cprdq = mlxsw_reg_hmon_cprdq_get(outbox);
    hmon_reg->read_type = mlxsw_reg_hmon_read_type_get(outbox);
    hmon_reg->crdq = mlxsw_reg_hmon_crdq_get(outbox);
    hmon_reg->wqe_of_wrap = mlxsw_reg_hmon_wqe_of_wrap_get(outbox);
    hmon_reg->wqe_overflow_high = mlxsw_reg_hmon_wqe_overflow_high_get(outbox);
    hmon_reg->wqe_overflow_low = mlxsw_reg_hmon_wqe_overflow_low_get(outbox);
    for (i = 0; i < SXD_HMON_WQE_OVERFLOW_RDQ_NUM; i++) {
        hmon_reg->wqe_overflow_rdq[i] = mlxsw_reg_hmon_wqe_overflow_rdq_get(outbox, i);
    }


    return 0;
}
EXPORT_SYMBOL(__HMON_decode);

int sx_ACCESS_REG_HMON(struct sx_dev *dev, struct ku_access_hmon_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_HMON_LEN >> 2) + 1;

    if (MLXSW_HMON_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __HMON_encode,
                                  __HMON_decode,
                                  reg_len_dword,
                                  &reg_data->hmon_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_HMON);

int sx_EMAD_ACCESS_REG_HMON(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_hmon_reg *reg)
{
    u16 reg_len_dword = (MLXSW_HMON_LEN >> 2) + 1;

    if (MLXSW_HMON_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_HMON_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __HMON_encode,
                                     __HMON_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_HMON);

/************************************************
* MGPIR
***********************************************/
int __MGPIR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mgpir_reg *mgpir_reg = (struct ku_mgpir_reg*)ku_reg;

    mlxsw_reg_mgpir_slot_index_set(inbox, mgpir_reg->hw_info.slot_index);


    return 0;
}

int __MGPIR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mgpir_reg *mgpir_reg = (struct ku_mgpir_reg*)ku_reg;

    mgpir_reg->hw_info.slot_index = mlxsw_reg_mgpir_slot_index_get(outbox);
    mgpir_reg->hw_info.device_type = mlxsw_reg_mgpir_device_type_get(outbox);
    mgpir_reg->hw_info.devices_per_flash = mlxsw_reg_mgpir_devices_per_flash_get(outbox);
    mgpir_reg->hw_info.num_of_devices = mlxsw_reg_mgpir_num_of_devices_get(outbox);
    mgpir_reg->hw_info.first_pluggable_interconnect_offset = mlxsw_reg_mgpir_first_pluggable_interconnect_offset_get(outbox);
    mgpir_reg->hw_info.max_modules_per_slot = mlxsw_reg_mgpir_max_modules_per_slot_get(outbox);
    mgpir_reg->hw_info.num_of_slots = mlxsw_reg_mgpir_num_of_slots_get(outbox);
    mgpir_reg->hw_info.num_of_modules = mlxsw_reg_mgpir_num_of_modules_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MGPIR_decode);

int sx_ACCESS_REG_MGPIR(struct sx_dev *dev, struct ku_access_mgpir_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MGPIR_LEN >> 2) + 1;

    if (MLXSW_MGPIR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MGPIR_encode,
                                  __MGPIR_decode,
                                  reg_len_dword,
                                  &reg_data->mgpir_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MGPIR);

int sx_EMAD_ACCESS_REG_MGPIR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mgpir_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MGPIR_LEN >> 2) + 1;

    if (MLXSW_MGPIR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MGPIR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MGPIR_encode,
                                     __MGPIR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MGPIR);

/************************************************
* PMTM
***********************************************/
int __PMTM_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmtm_reg *pmtm_reg = (struct ku_pmtm_reg*)ku_reg;

    mlxsw_reg_pmtm_slot_index_set(inbox, pmtm_reg->slot_index);
    mlxsw_reg_pmtm_module_set(inbox, pmtm_reg->module);
    mlxsw_reg_pmtm_module_width_set(inbox, pmtm_reg->module_width);
    mlxsw_reg_pmtm_module_type_set(inbox, pmtm_reg->module_type);


    return 0;
}

int __PMTM_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmtm_reg *pmtm_reg = (struct ku_pmtm_reg*)ku_reg;

    pmtm_reg->media_width_cap = mlxsw_reg_pmtm_media_width_cap_get(outbox);
    pmtm_reg->slot_index = mlxsw_reg_pmtm_slot_index_get(outbox);
    pmtm_reg->module = mlxsw_reg_pmtm_module_get(outbox);
    pmtm_reg->module_media_width = mlxsw_reg_pmtm_module_media_width_get(outbox);
    pmtm_reg->module_width = mlxsw_reg_pmtm_module_width_get(outbox);
    pmtm_reg->module_type = mlxsw_reg_pmtm_module_type_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__PMTM_decode);

int sx_ACCESS_REG_PMTM(struct sx_dev *dev, struct ku_access_pmtm_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PMTM_LEN >> 2) + 1;

    if (MLXSW_PMTM_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMTM_encode,
                                  __PMTM_decode,
                                  reg_len_dword,
                                  &reg_data->pmtm_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMTM);

int sx_EMAD_ACCESS_REG_PMTM(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmtm_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PMTM_LEN >> 2) + 1;

    if (MLXSW_PMTM_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PMTM_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PMTM_encode,
                                     __PMTM_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PMTM);

/************************************************
* SLLM
***********************************************/
int __SLLM_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sllm_reg *sllm_reg = (struct ku_sllm_reg*)ku_reg;

    mlxsw_reg_sllm_local_port_set(inbox, sllm_reg->local_port);
    mlxsw_reg_sllm_pnat_set(inbox, sllm_reg->pnat);
    mlxsw_reg_sllm_lp_msb_set(inbox, sllm_reg->lp_msb);
    mlxsw_reg_sllm_lane_set(inbox, sllm_reg->lane);
    mlxsw_reg_sllm_port_type_set(inbox, sllm_reg->port_type);
    mlxsw_reg_sllm_c_db_set(inbox, sllm_reg->c_db);
    switch (sllm_reg->version) {
    case SXD_SLLM_VERSION_PROD_16NM_E:
        mlxsw_reg_sllm_page_data_sllm_16nm_lm_en_set(inbox, sllm_reg->page_data.sllm_16nm.lm_en);
        mlxsw_reg_sllm_page_data_sllm_16nm_lm_clk90_fl_err_max_set(inbox, sllm_reg->page_data.sllm_16nm.lm_clk90_fl_err_max);
        mlxsw_reg_sllm_page_data_sllm_16nm_lm_clk90_fl_err_acc_set(inbox, sllm_reg->page_data.sllm_16nm.lm_clk90_fl_err_acc);
        mlxsw_reg_sllm_page_data_sllm_16nm_ib3_max_lm_90_tries_set(inbox, sllm_reg->page_data.sllm_16nm.ib3_max_lm_90_tries);
        mlxsw_reg_sllm_page_data_sllm_16nm_lm_counter_up_set(inbox, sllm_reg->page_data.sllm_16nm.lm_counter_up);
        mlxsw_reg_sllm_page_data_sllm_16nm_ib1_max_lm_90_tries_set(inbox, sllm_reg->page_data.sllm_16nm.ib1_max_lm_90_tries);
        mlxsw_reg_sllm_page_data_sllm_16nm_lm_counter_mid_set(inbox, sllm_reg->page_data.sllm_16nm.lm_counter_mid);
        mlxsw_reg_sllm_page_data_sllm_16nm_lm_counter_dn_set(inbox, sllm_reg->page_data.sllm_16nm.lm_counter_dn);
        break;

    case SXD_SLLM_VERSION_PROD_7NM_E:
        mlxsw_reg_sllm_page_data_sllm_7nm_ctle_peq_en_set(inbox, sllm_reg->page_data.sllm_7nm.ctle_peq_en);
        mlxsw_reg_sllm_page_data_sllm_7nm_peq_tsense_en_set(inbox, sllm_reg->page_data.sllm_7nm.peq_tsense_en);
        mlxsw_reg_sllm_page_data_sllm_7nm_peq_f1_adapt_skip_set(inbox, sllm_reg->page_data.sllm_7nm.peq_f1_adapt_skip);
        mlxsw_reg_sllm_page_data_sllm_7nm_vref_peq_en_set(inbox, sllm_reg->page_data.sllm_7nm.vref_peq_en);
        mlxsw_reg_sllm_page_data_sllm_7nm_dffe_peq_scout_skip_set(inbox, sllm_reg->page_data.sllm_7nm.dffe_peq_scout_skip);
        mlxsw_reg_sllm_page_data_sllm_7nm_peq_train_mode_set(inbox, sllm_reg->page_data.sllm_7nm.peq_train_mode);
        mlxsw_reg_sllm_page_data_sllm_7nm_peq_vref_iters_set(inbox, sllm_reg->page_data.sllm_7nm.peq_vref_iters);
        mlxsw_reg_sllm_page_data_sllm_7nm_peq_adc_vref_step_set(inbox, sllm_reg->page_data.sllm_7nm.peq_adc_vref_step);
        mlxsw_reg_sllm_page_data_sllm_7nm_dffe_peq_en_set(inbox, sllm_reg->page_data.sllm_7nm.dffe_peq_en);
        mlxsw_reg_sllm_page_data_sllm_7nm_peq_dffe_iters_set(inbox, sllm_reg->page_data.sllm_7nm.peq_dffe_iters);
        mlxsw_reg_sllm_page_data_sllm_7nm_peq_dffe_delay_set(inbox, sllm_reg->page_data.sllm_7nm.peq_dffe_delay);
        break;

    case SXD_SLLM_VERSION_PROD_TBD_E:
        mlxsw_reg_sllm_page_data_sllm_usr_enable_lm_set(inbox, sllm_reg->page_data.sllm_usr.enable_lm);
        mlxsw_reg_sllm_page_data_sllm_usr_enable_phase_maintenance_set(inbox, sllm_reg->page_data.sllm_usr.enable_phase_maintenance);
        mlxsw_reg_sllm_page_data_sllm_usr_enable_offset_maintenance_set(inbox, sllm_reg->page_data.sllm_usr.enable_offset_maintenance);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}

int __SLLM_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sllm_reg *sllm_reg = (struct ku_sllm_reg*)ku_reg;

    sllm_reg->status = mlxsw_reg_sllm_status_get(outbox);
    sllm_reg->version = mlxsw_reg_sllm_version_get(outbox);
    sllm_reg->local_port = mlxsw_reg_sllm_local_port_get(outbox);
    sllm_reg->pnat = mlxsw_reg_sllm_pnat_get(outbox);
    sllm_reg->lp_msb = mlxsw_reg_sllm_lp_msb_get(outbox);
    sllm_reg->lane = mlxsw_reg_sllm_lane_get(outbox);
    sllm_reg->port_type = mlxsw_reg_sllm_port_type_get(outbox);
    sllm_reg->c_db = mlxsw_reg_sllm_c_db_get(outbox);
    switch (sllm_reg->version) {
    case SXD_SLLM_VERSION_PROD_16NM_E:
        sllm_reg->page_data.sllm_16nm.lm_active = mlxsw_reg_sllm_page_data_sllm_16nm_lm_active_get(outbox);
        sllm_reg->page_data.sllm_16nm.lm_was_active = mlxsw_reg_sllm_page_data_sllm_16nm_lm_was_active_get(outbox);
        sllm_reg->page_data.sllm_16nm.pib_gw_lock = mlxsw_reg_sllm_page_data_sllm_16nm_pib_gw_lock_get(outbox);
        sllm_reg->page_data.sllm_16nm.lm_en = mlxsw_reg_sllm_page_data_sllm_16nm_lm_en_get(outbox);
        sllm_reg->page_data.sllm_16nm.lm_clk90_fl_err_max = mlxsw_reg_sllm_page_data_sllm_16nm_lm_clk90_fl_err_max_get(outbox);
        sllm_reg->page_data.sllm_16nm.lm_clk90_fl_err_acc = mlxsw_reg_sllm_page_data_sllm_16nm_lm_clk90_fl_err_acc_get(outbox);
        sllm_reg->page_data.sllm_16nm.ib3_max_lm_90_tries = mlxsw_reg_sllm_page_data_sllm_16nm_ib3_max_lm_90_tries_get(outbox);
        sllm_reg->page_data.sllm_16nm.lm_counter_up = mlxsw_reg_sllm_page_data_sllm_16nm_lm_counter_up_get(outbox);
        sllm_reg->page_data.sllm_16nm.ib1_max_lm_90_tries = mlxsw_reg_sllm_page_data_sllm_16nm_ib1_max_lm_90_tries_get(outbox);
        sllm_reg->page_data.sllm_16nm.lm_counter_mid = mlxsw_reg_sllm_page_data_sllm_16nm_lm_counter_mid_get(outbox);
        sllm_reg->page_data.sllm_16nm.lm_counter_dn = mlxsw_reg_sllm_page_data_sllm_16nm_lm_counter_dn_get(outbox);
        break;

    case SXD_SLLM_VERSION_PROD_7NM_E:
        sllm_reg->page_data.sllm_7nm.ctle_peq_en = mlxsw_reg_sllm_page_data_sllm_7nm_ctle_peq_en_get(outbox);
        sllm_reg->page_data.sllm_7nm.peq_tsense_en = mlxsw_reg_sllm_page_data_sllm_7nm_peq_tsense_en_get(outbox);
        sllm_reg->page_data.sllm_7nm.peq_f1_adapt_skip = mlxsw_reg_sllm_page_data_sllm_7nm_peq_f1_adapt_skip_get(outbox);
        sllm_reg->page_data.sllm_7nm.vref_peq_en = mlxsw_reg_sllm_page_data_sllm_7nm_vref_peq_en_get(outbox);
        sllm_reg->page_data.sllm_7nm.dffe_peq_scout_skip = mlxsw_reg_sllm_page_data_sllm_7nm_dffe_peq_scout_skip_get(outbox);
        sllm_reg->page_data.sllm_7nm.peq_train_mode = mlxsw_reg_sllm_page_data_sllm_7nm_peq_train_mode_get(outbox);
        sllm_reg->page_data.sllm_7nm.peq_vref_iters = mlxsw_reg_sllm_page_data_sllm_7nm_peq_vref_iters_get(outbox);
        sllm_reg->page_data.sllm_7nm.peq_adc_vref_step = mlxsw_reg_sllm_page_data_sllm_7nm_peq_adc_vref_step_get(outbox);
        sllm_reg->page_data.sllm_7nm.dffe_peq_en = mlxsw_reg_sllm_page_data_sllm_7nm_dffe_peq_en_get(outbox);
        sllm_reg->page_data.sllm_7nm.peq_dffe_iters = mlxsw_reg_sllm_page_data_sllm_7nm_peq_dffe_iters_get(outbox);
        sllm_reg->page_data.sllm_7nm.peq_dffe_delay = mlxsw_reg_sllm_page_data_sllm_7nm_peq_dffe_delay_get(outbox);
        sllm_reg->page_data.sllm_7nm.ctle_peq_cnt = mlxsw_reg_sllm_page_data_sllm_7nm_ctle_peq_cnt_get(outbox);
        sllm_reg->page_data.sllm_7nm.ber_mon_mantissa = mlxsw_reg_sllm_page_data_sllm_7nm_ber_mon_mantissa_get(outbox);
        sllm_reg->page_data.sllm_7nm.ber_mon_exp = mlxsw_reg_sllm_page_data_sllm_7nm_ber_mon_exp_get(outbox);
        break;

    case SXD_SLLM_VERSION_PROD_TBD_E:
        sllm_reg->page_data.sllm_usr.enable_lm = mlxsw_reg_sllm_page_data_sllm_usr_enable_lm_get(outbox);
        sllm_reg->page_data.sllm_usr.enable_phase_maintenance = mlxsw_reg_sllm_page_data_sllm_usr_enable_phase_maintenance_get(outbox);
        sllm_reg->page_data.sllm_usr.enable_offset_maintenance = mlxsw_reg_sllm_page_data_sllm_usr_enable_offset_maintenance_get(outbox);
        sllm_reg->page_data.sllm_usr.lm_catastrophic_bit = mlxsw_reg_sllm_page_data_sllm_usr_lm_catastrophic_bit_get(outbox);
        sllm_reg->page_data.sllm_usr.lm_activation_counter = mlxsw_reg_sllm_page_data_sllm_usr_lm_activation_counter_get(outbox);
        sllm_reg->page_data.sllm_usr.lm_fixes_counter = mlxsw_reg_sllm_page_data_sllm_usr_lm_fixes_counter_get(outbox);
        sllm_reg->page_data.sllm_usr.lane_under_maintenance = mlxsw_reg_sllm_page_data_sllm_usr_lane_under_maintenance_get(outbox);
        sllm_reg->page_data.sllm_usr.optimal_phase = mlxsw_reg_sllm_page_data_sllm_usr_optimal_phase_get(outbox);
        sllm_reg->page_data.sllm_usr.link_tuning_error = mlxsw_reg_sllm_page_data_sllm_usr_link_tuning_error_get(outbox);
        sllm_reg->page_data.sllm_usr.lane_correctable_errors = mlxsw_reg_sllm_page_data_sllm_usr_lane_correctable_errors_get(outbox);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}
EXPORT_SYMBOL(__SLLM_decode);

int sx_ACCESS_REG_SLLM(struct sx_dev *dev, struct ku_access_sllm_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_SLLM_LEN >> 2) + 1;

    if (MLXSW_SLLM_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SLLM_encode,
                                  __SLLM_decode,
                                  reg_len_dword,
                                  &reg_data->sllm_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SLLM);

int sx_EMAD_ACCESS_REG_SLLM(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sllm_reg *reg)
{
    u16 reg_len_dword = (MLXSW_SLLM_LEN >> 2) + 1;

    if (MLXSW_SLLM_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_SLLM_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __SLLM_encode,
                                     __SLLM_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_SLLM);

/************************************************
* PMTU
***********************************************/
int __PMTU_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmtu_reg *pmtu_reg = (struct ku_pmtu_reg*)ku_reg;

    mlxsw_reg_pmtu_local_port_set(inbox, pmtu_reg->local_port);
    mlxsw_reg_pmtu_lp_msb_set(inbox, pmtu_reg->lp_msb);
    mlxsw_reg_pmtu_i_e_set(inbox, pmtu_reg->i_e);
    mlxsw_reg_pmtu_itre_set(inbox, pmtu_reg->itre);
    mlxsw_reg_pmtu_admin_mtu_set(inbox, pmtu_reg->admin_mtu);


    return 0;
}

int __PMTU_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmtu_reg *pmtu_reg = (struct ku_pmtu_reg*)ku_reg;

    pmtu_reg->local_port = mlxsw_reg_pmtu_local_port_get(outbox);
    pmtu_reg->lp_msb = mlxsw_reg_pmtu_lp_msb_get(outbox);
    pmtu_reg->i_e = mlxsw_reg_pmtu_i_e_get(outbox);
    pmtu_reg->itre = mlxsw_reg_pmtu_itre_get(outbox);
    pmtu_reg->max_mtu = mlxsw_reg_pmtu_max_mtu_get(outbox);
    pmtu_reg->admin_mtu = mlxsw_reg_pmtu_admin_mtu_get(outbox);
    pmtu_reg->oper_mtu = mlxsw_reg_pmtu_oper_mtu_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__PMTU_decode);

int sx_ACCESS_REG_PMTU(struct sx_dev *dev, struct ku_access_pmtu_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PMTU_LEN >> 2) + 1;

    if (MLXSW_PMTU_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMTU_encode,
                                  __PMTU_decode,
                                  reg_len_dword,
                                  &reg_data->pmtu_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMTU);

int sx_EMAD_ACCESS_REG_PMTU(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmtu_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PMTU_LEN >> 2) + 1;

    if (MLXSW_PMTU_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PMTU_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PMTU_encode,
                                     __PMTU_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PMTU);

/************************************************
* PMMP
***********************************************/
int __PMMP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmmp_reg *pmmp_reg = (struct ku_pmmp_reg*)ku_reg;
    uint32_t i = 0;

    mlxsw_reg_pmmp_slot_index_set(inbox, pmmp_reg->slot_index);
    mlxsw_reg_pmmp_module_set(inbox, pmmp_reg->module);
    mlxsw_reg_pmmp_sticky_set(inbox, pmmp_reg->sticky);
    mlxsw_reg_pmmp_eeprom_override_mask_set(inbox, pmmp_reg->eeprom_override_mask);
    mlxsw_reg_pmmp_eeprom_override_set(inbox, pmmp_reg->eeprom_override);
    switch (pmmp_reg->eeprom_override) {
    case SXD_PMMP_EEPROM_OVERRIDE_OVERRIDE_CABLE_PROTOCOLS_AND_TECHNOLOGY_FOR_QSFP_E:
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_cable_breakout_set(inbox, pmmp_reg->qsfp_cable_protocol_technology.pmmp_qsfp_protocol_override_layout.cable_breakout);
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_ethernet_compliance_code_set(inbox, pmmp_reg->qsfp_cable_protocol_technology.pmmp_qsfp_protocol_override_layout.ethernet_compliance_code);
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_ext_ethernet_compliance_code_set(inbox, pmmp_reg->qsfp_cable_protocol_technology.pmmp_qsfp_protocol_override_layout.ext_ethernet_compliance_code);
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_giga_ethernet_compliance_code_set(inbox, pmmp_reg->qsfp_cable_protocol_technology.pmmp_qsfp_protocol_override_layout.giga_ethernet_compliance_code);
        break;

    case SXD_PMMP_EEPROM_OVERRIDE_OVERRIDE_CABLE_PROTOCOLS_AND_TECHNOLOGY_FOR_SFP_E:
        break;

    case SXD_PMMP_EEPROM_OVERRIDE_IGNORE_POWER_CLASS_E:
        break;

    case SXD_PMMP_EEPROM_OVERRIDE_OVERRIDE_CABLE_LENGTH_E:
        break;

    case SXD_PMMP_EEPROM_OVERRIDE_OVERRIDE_ATTENUATION_E:
        break;

    case SXD_PMMP_EEPROM_OVERRIDE_SET_MODULE_TO_LOW_POWER_E:
        break;

    case SXD_PMMP_EEPROM_OVERRIDE_OVERRIDE_CABLE_PROTOCOLS_AND_TECHNOLOGY_FOR_CMIS_E:
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_mod_pwrup_maxduration_set(inbox, pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.mod_pwrup_maxduration);
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_cable_breakout_set(inbox, pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.cable_breakout);
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_host_electrical_compliance_set(inbox, pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.host_electrical_compliance);
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_dp_init_maxduration_set(inbox, pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.dp_init_maxduration);
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_app0_disabled_set(inbox, pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.app0_disabled);
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_dp_tx_on_maxduration_set(inbox, pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.dp_tx_on_maxduration);
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_dp_tx_off_maxduration_set(inbox, pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.dp_tx_off_maxduration);
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_module_media_type_set(inbox, pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.module_media_type);
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_media_compliance_set(inbox, pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.media_compliance);
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_cmis_override_mask_set(inbox, pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.cmis_override_mask);
        break;

    default:
        /* Other types not supported yet */
        break;
    }
    for (i = 0; i < SXD_PMMP_SFP_CABLE_PROTOCOL_TECHNOLOGY_NUM; i++) {
        mlxsw_reg_pmmp_sfp_cable_protocol_technology_set(inbox, i, pmmp_reg->sfp_cable_protocol_technology[i]);
    }
    mlxsw_reg_pmmp_cable_length_set(inbox, pmmp_reg->cable_length);
    mlxsw_reg_pmmp_attenuation_25g_set(inbox, pmmp_reg->attenuation_25g);
    mlxsw_reg_pmmp_attenuation_12g_set(inbox, pmmp_reg->attenuation_12g);
    mlxsw_reg_pmmp_attenuation_7g_set(inbox, pmmp_reg->attenuation_7g);
    mlxsw_reg_pmmp_attenuation_5g_set(inbox, pmmp_reg->attenuation_5g);


    return 0;
}

int __PMMP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmmp_reg *pmmp_reg = (struct ku_pmmp_reg*)ku_reg;
    uint32_t i = 0;

    pmmp_reg->slot_index = mlxsw_reg_pmmp_slot_index_get(outbox);
    pmmp_reg->module = mlxsw_reg_pmmp_module_get(outbox);
    pmmp_reg->sticky = mlxsw_reg_pmmp_sticky_get(outbox);
    pmmp_reg->eeprom_override = mlxsw_reg_pmmp_eeprom_override_get(outbox);
    switch (pmmp_reg->eeprom_override) {
    case SXD_PMMP_EEPROM_OVERRIDE_OVERRIDE_CABLE_PROTOCOLS_AND_TECHNOLOGY_FOR_QSFP_E:
        pmmp_reg->qsfp_cable_protocol_technology.pmmp_qsfp_protocol_override_layout.cable_breakout = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_cable_breakout_get(outbox);
        pmmp_reg->qsfp_cable_protocol_technology.pmmp_qsfp_protocol_override_layout.ethernet_compliance_code = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_ethernet_compliance_code_get(outbox);
        pmmp_reg->qsfp_cable_protocol_technology.pmmp_qsfp_protocol_override_layout.ext_ethernet_compliance_code = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_ext_ethernet_compliance_code_get(outbox);
        pmmp_reg->qsfp_cable_protocol_technology.pmmp_qsfp_protocol_override_layout.giga_ethernet_compliance_code = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_qsfp_protocol_override_layout_giga_ethernet_compliance_code_get(outbox);
        break;

    case SXD_PMMP_EEPROM_OVERRIDE_OVERRIDE_CABLE_PROTOCOLS_AND_TECHNOLOGY_FOR_SFP_E:
        break;

    case SXD_PMMP_EEPROM_OVERRIDE_IGNORE_POWER_CLASS_E:
        break;

    case SXD_PMMP_EEPROM_OVERRIDE_OVERRIDE_CABLE_LENGTH_E:
        break;

    case SXD_PMMP_EEPROM_OVERRIDE_OVERRIDE_ATTENUATION_E:
        break;

    case SXD_PMMP_EEPROM_OVERRIDE_SET_MODULE_TO_LOW_POWER_E:
        break;

    case SXD_PMMP_EEPROM_OVERRIDE_OVERRIDE_CABLE_PROTOCOLS_AND_TECHNOLOGY_FOR_CMIS_E:
        pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.mod_pwrup_maxduration = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_mod_pwrup_maxduration_get(outbox);
        pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.cable_breakout = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_cable_breakout_get(outbox);
        pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.host_electrical_compliance = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_host_electrical_compliance_get(outbox);
        pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.dp_init_maxduration = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_dp_init_maxduration_get(outbox);
        pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.app0_disabled = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_app0_disabled_get(outbox);
        pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.dp_tx_on_maxduration = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_dp_tx_on_maxduration_get(outbox);
        pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.dp_tx_off_maxduration = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_dp_tx_off_maxduration_get(outbox);
        pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.module_media_type = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_module_media_type_get(outbox);
        pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.media_compliance = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_media_compliance_get(outbox);
        pmmp_reg->qsfp_cable_protocol_technology.pmmp_cmis_protocol_override_layout.cmis_override_mask = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_pmmp_cmis_protocol_override_layout_cmis_override_mask_get(outbox);
        break;

    default:
        /* Other types not supported yet */
        break;
    }
    for (i = 0; i < SXD_PMMP_SFP_CABLE_PROTOCOL_TECHNOLOGY_NUM; i++) {
        pmmp_reg->sfp_cable_protocol_technology[i] = mlxsw_reg_pmmp_sfp_cable_protocol_technology_get(outbox, i);
    }
    pmmp_reg->cable_length = mlxsw_reg_pmmp_cable_length_get(outbox);
    pmmp_reg->attenuation_25g = mlxsw_reg_pmmp_attenuation_25g_get(outbox);
    pmmp_reg->attenuation_12g = mlxsw_reg_pmmp_attenuation_12g_get(outbox);
    pmmp_reg->attenuation_7g = mlxsw_reg_pmmp_attenuation_7g_get(outbox);
    pmmp_reg->attenuation_5g = mlxsw_reg_pmmp_attenuation_5g_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__PMMP_decode);

int sx_ACCESS_REG_PMMP(struct sx_dev *dev, struct ku_access_pmmp_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PMMP_LEN >> 2) + 1;

    if (MLXSW_PMMP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMMP_encode,
                                  __PMMP_decode,
                                  reg_len_dword,
                                  &reg_data->pmmp_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMMP);

int sx_EMAD_ACCESS_REG_PMMP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmmp_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PMMP_LEN >> 2) + 1;

    if (MLXSW_PMMP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PMMP_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PMMP_encode,
                                     __PMMP_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PMMP);

/************************************************
* SLTP
***********************************************/
int __SLTP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sltp_reg *sltp_reg = (struct ku_sltp_reg*)ku_reg;

    mlxsw_reg_sltp_lp_msb_set(inbox, sltp_reg->lp_msb);
    mlxsw_reg_sltp_local_port_set(inbox, sltp_reg->local_port);
    mlxsw_reg_sltp_pnat_set(inbox, sltp_reg->pnat);
    mlxsw_reg_sltp_tx_policy_set(inbox, sltp_reg->tx_policy);
    mlxsw_reg_sltp_conf_mod_set(inbox, sltp_reg->conf_mod);
    mlxsw_reg_sltp_lane_set(inbox, sltp_reg->lane);
    mlxsw_reg_sltp_lane_speed_set(inbox, sltp_reg->lane_speed);
    mlxsw_reg_sltp_port_type_set(inbox, sltp_reg->port_type);
    mlxsw_reg_sltp_c_db_set(inbox, sltp_reg->c_db);
    switch (sltp_reg->version) {
    case SXD_SLTP_VERSION_PROD_40NM_E:
        break;

    case SXD_SLTP_VERSION_PROD_28NM_E:
        mlxsw_reg_sltp_page_data_sltp_28nm_40nm_polarity_set(inbox, sltp_reg->page_data.sltp_28nm_40nm.polarity);
        mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_tap0_set(inbox, sltp_reg->page_data.sltp_28nm_40nm.ob_tap0);
        mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_tap1_set(inbox, sltp_reg->page_data.sltp_28nm_40nm.ob_tap1);
        mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_tap2_set(inbox, sltp_reg->page_data.sltp_28nm_40nm.ob_tap2);
        mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_leva_set(inbox, sltp_reg->page_data.sltp_28nm_40nm.ob_leva);
        mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_preemp_mode_set(inbox, sltp_reg->page_data.sltp_28nm_40nm.ob_preemp_mode);
        mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_reg_set(inbox, sltp_reg->page_data.sltp_28nm_40nm.ob_reg);
        mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_bias_set(inbox, sltp_reg->page_data.sltp_28nm_40nm.ob_bias);
        break;

    case SXD_SLTP_VERSION_PROD_16NM_E:
        mlxsw_reg_sltp_page_data_sltp_16nm_pre_2_tap_set(inbox, sltp_reg->page_data.sltp_16nm.pre_2_tap);
        mlxsw_reg_sltp_page_data_sltp_16nm_pre_tap_set(inbox, sltp_reg->page_data.sltp_16nm.pre_tap);
        mlxsw_reg_sltp_page_data_sltp_16nm_main_tap_set(inbox, sltp_reg->page_data.sltp_16nm.main_tap);
        mlxsw_reg_sltp_page_data_sltp_16nm_post_tap_set(inbox, sltp_reg->page_data.sltp_16nm.post_tap);
        mlxsw_reg_sltp_page_data_sltp_16nm_ob_m2lp_set(inbox, sltp_reg->page_data.sltp_16nm.ob_m2lp);
        mlxsw_reg_sltp_page_data_sltp_16nm_ob_amp_set(inbox, sltp_reg->page_data.sltp_16nm.ob_amp);
        mlxsw_reg_sltp_page_data_sltp_16nm_ob_alev_out_set(inbox, sltp_reg->page_data.sltp_16nm.ob_alev_out);
        break;

    case SXD_SLTP_VERSION_PROD_7NM_E:
        mlxsw_reg_sltp_page_data_sltp_7nm_drv_amp_set(inbox, sltp_reg->page_data.sltp_7nm.drv_amp);
        mlxsw_reg_sltp_page_data_sltp_7nm_fir_pre3_set(inbox, sltp_reg->page_data.sltp_7nm.fir_pre3);
        mlxsw_reg_sltp_page_data_sltp_7nm_fir_pre2_set(inbox, sltp_reg->page_data.sltp_7nm.fir_pre2);
        mlxsw_reg_sltp_page_data_sltp_7nm_fir_pre1_set(inbox, sltp_reg->page_data.sltp_7nm.fir_pre1);
        mlxsw_reg_sltp_page_data_sltp_7nm_fir_main_set(inbox, sltp_reg->page_data.sltp_7nm.fir_main);
        mlxsw_reg_sltp_page_data_sltp_7nm_fir_post1_set(inbox, sltp_reg->page_data.sltp_7nm.fir_post1);
        break;

    case SXD_SLTP_VERSION_PROD_LUT_7NM_E:
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_vs_peer_db_set(inbox, sltp_reg->page_data.sltp_lut_7nm.vs_peer_db);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_drv_amp_set(inbox, sltp_reg->page_data.sltp_lut_7nm.drv_amp);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_fir_pre3_set(inbox, sltp_reg->page_data.sltp_lut_7nm.fir_pre3);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_fir_pre2_set(inbox, sltp_reg->page_data.sltp_lut_7nm.fir_pre2);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut3_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut3);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut2_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut2);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut1_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut1);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut0_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut0);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut7_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut7);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut6_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut6);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut5_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut5);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut4_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut4);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut11_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut11);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut10_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut10);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut9_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut9);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut8_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut8);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut15_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut15);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut14_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut14);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut13_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut13);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut12_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut12);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut19_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut19);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut18_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut18);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut17_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut17);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut16_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut16);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut23_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut23);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut22_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut22);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut21_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut21);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut20_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut20);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut27_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut27);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut26_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut26);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut25_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut25);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut24_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut24);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut31_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut31);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut30_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut30);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut29_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut29);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut28_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut28);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut35_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut35);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut34_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut34);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut33_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut33);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut32_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut32);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut39_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut39);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut38_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut38);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut37_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut37);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut36_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut36);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut43_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut43);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut42_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut42);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut41_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut41);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut40_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut40);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut47_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut47);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut46_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut46);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut45_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut45);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut44_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut44);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut51_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut51);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut50_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut50);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut49_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut49);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut48_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut48);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut55_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut55);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut54_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut54);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut53_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut53);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut52_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut52);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut59_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut59);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut58_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut58);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut57_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut57);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut56_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut56);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut63_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut63);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut62_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut62);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut61_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut61);
        mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut60_set(inbox, sltp_reg->page_data.sltp_lut_7nm.lut60);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}

int __SLTP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sltp_reg *sltp_reg = (struct ku_sltp_reg*)ku_reg;

    sltp_reg->lp_msb = mlxsw_reg_sltp_lp_msb_get(outbox);
    sltp_reg->status = mlxsw_reg_sltp_status_get(outbox);
    sltp_reg->version = mlxsw_reg_sltp_version_get(outbox);
    sltp_reg->local_port = mlxsw_reg_sltp_local_port_get(outbox);
    sltp_reg->pnat = mlxsw_reg_sltp_pnat_get(outbox);
    sltp_reg->tx_policy = mlxsw_reg_sltp_tx_policy_get(outbox);
    sltp_reg->conf_mod = mlxsw_reg_sltp_conf_mod_get(outbox);
    sltp_reg->lane = mlxsw_reg_sltp_lane_get(outbox);
    sltp_reg->lane_speed = mlxsw_reg_sltp_lane_speed_get(outbox);
    sltp_reg->port_type = mlxsw_reg_sltp_port_type_get(outbox);
    sltp_reg->c_db = mlxsw_reg_sltp_c_db_get(outbox);
    switch (sltp_reg->version) {
    case SXD_SLTP_VERSION_PROD_40NM_E:
        break;

    case SXD_SLTP_VERSION_PROD_28NM_E:
        sltp_reg->page_data.sltp_28nm_40nm.polarity = mlxsw_reg_sltp_page_data_sltp_28nm_40nm_polarity_get(outbox);
        sltp_reg->page_data.sltp_28nm_40nm.ob_tap0 = mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_tap0_get(outbox);
        sltp_reg->page_data.sltp_28nm_40nm.ob_tap1 = mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_tap1_get(outbox);
        sltp_reg->page_data.sltp_28nm_40nm.ob_tap2 = mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_tap2_get(outbox);
        sltp_reg->page_data.sltp_28nm_40nm.ob_leva = mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_leva_get(outbox);
        sltp_reg->page_data.sltp_28nm_40nm.ob_preemp_mode = mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_preemp_mode_get(outbox);
        sltp_reg->page_data.sltp_28nm_40nm.ob_reg = mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_reg_get(outbox);
        sltp_reg->page_data.sltp_28nm_40nm.ob_bias = mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_bias_get(outbox);
        sltp_reg->page_data.sltp_28nm_40nm.ob_norm = mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_norm_get(outbox);
        sltp_reg->page_data.sltp_28nm_40nm.ob_bad_stat = mlxsw_reg_sltp_page_data_sltp_28nm_40nm_ob_bad_stat_get(outbox);
        break;

    case SXD_SLTP_VERSION_PROD_16NM_E:
        sltp_reg->page_data.sltp_16nm.pre_2_tap = mlxsw_reg_sltp_page_data_sltp_16nm_pre_2_tap_get(outbox);
        sltp_reg->page_data.sltp_16nm.pre_tap = mlxsw_reg_sltp_page_data_sltp_16nm_pre_tap_get(outbox);
        sltp_reg->page_data.sltp_16nm.main_tap = mlxsw_reg_sltp_page_data_sltp_16nm_main_tap_get(outbox);
        sltp_reg->page_data.sltp_16nm.post_tap = mlxsw_reg_sltp_page_data_sltp_16nm_post_tap_get(outbox);
        sltp_reg->page_data.sltp_16nm.ob_m2lp = mlxsw_reg_sltp_page_data_sltp_16nm_ob_m2lp_get(outbox);
        sltp_reg->page_data.sltp_16nm.ob_amp = mlxsw_reg_sltp_page_data_sltp_16nm_ob_amp_get(outbox);
        sltp_reg->page_data.sltp_16nm.ob_alev_out = mlxsw_reg_sltp_page_data_sltp_16nm_ob_alev_out_get(outbox);
        sltp_reg->page_data.sltp_16nm.ob_bad_stat = mlxsw_reg_sltp_page_data_sltp_16nm_ob_bad_stat_get(outbox);
        break;

    case SXD_SLTP_VERSION_PROD_7NM_E:
        sltp_reg->page_data.sltp_7nm.drv_amp = mlxsw_reg_sltp_page_data_sltp_7nm_drv_amp_get(outbox);
        sltp_reg->page_data.sltp_7nm.ob_bad_stat = mlxsw_reg_sltp_page_data_sltp_7nm_ob_bad_stat_get(outbox);
        sltp_reg->page_data.sltp_7nm.fir_pre3 = mlxsw_reg_sltp_page_data_sltp_7nm_fir_pre3_get(outbox);
        sltp_reg->page_data.sltp_7nm.fir_pre2 = mlxsw_reg_sltp_page_data_sltp_7nm_fir_pre2_get(outbox);
        sltp_reg->page_data.sltp_7nm.fir_pre1 = mlxsw_reg_sltp_page_data_sltp_7nm_fir_pre1_get(outbox);
        sltp_reg->page_data.sltp_7nm.fir_main = mlxsw_reg_sltp_page_data_sltp_7nm_fir_main_get(outbox);
        sltp_reg->page_data.sltp_7nm.fir_post1 = mlxsw_reg_sltp_page_data_sltp_7nm_fir_post1_get(outbox);
        break;

    case SXD_SLTP_VERSION_PROD_LUT_7NM_E:
        sltp_reg->page_data.sltp_lut_7nm.vs_peer_db = mlxsw_reg_sltp_page_data_sltp_lut_7nm_vs_peer_db_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.drv_amp = mlxsw_reg_sltp_page_data_sltp_lut_7nm_drv_amp_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.ob_bad_stat = mlxsw_reg_sltp_page_data_sltp_lut_7nm_ob_bad_stat_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.fir_pre3 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_fir_pre3_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.fir_pre2 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_fir_pre2_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut3 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut3_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut2 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut2_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut1 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut1_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut0 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut0_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut7 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut7_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut6 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut6_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut5 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut5_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut4 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut4_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut11 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut11_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut10 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut10_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut9 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut9_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut8 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut8_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut15 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut15_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut14 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut14_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut13 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut13_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut12 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut12_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut19 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut19_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut18 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut18_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut17 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut17_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut16 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut16_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut23 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut23_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut22 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut22_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut21 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut21_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut20 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut20_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut27 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut27_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut26 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut26_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut25 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut25_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut24 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut24_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut31 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut31_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut30 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut30_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut29 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut29_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut28 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut28_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut35 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut35_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut34 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut34_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut33 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut33_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut32 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut32_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut39 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut39_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut38 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut38_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut37 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut37_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut36 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut36_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut43 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut43_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut42 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut42_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut41 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut41_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut40 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut40_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut47 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut47_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut46 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut46_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut45 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut45_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut44 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut44_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut51 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut51_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut50 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut50_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut49 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut49_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut48 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut48_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut55 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut55_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut54 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut54_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut53 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut53_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut52 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut52_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut59 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut59_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut58 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut58_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut57 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut57_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut56 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut56_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut63 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut63_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut62 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut62_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut61 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut61_get(outbox);
        sltp_reg->page_data.sltp_lut_7nm.lut60 = mlxsw_reg_sltp_page_data_sltp_lut_7nm_lut60_get(outbox);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}
EXPORT_SYMBOL(__SLTP_decode);

int sx_ACCESS_REG_SLTP(struct sx_dev *dev, struct ku_access_sltp_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_SLTP_LEN >> 2) + 1;

    if (MLXSW_SLTP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SLTP_encode,
                                  __SLTP_decode,
                                  reg_len_dword,
                                  &reg_data->sltp_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SLTP);

int sx_EMAD_ACCESS_REG_SLTP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sltp_reg *reg)
{
    u16 reg_len_dword = (MLXSW_SLTP_LEN >> 2) + 1;

    if (MLXSW_SLTP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_SLTP_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __SLTP_encode,
                                     __SLTP_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_SLTP);

/************************************************
* PPHCR
***********************************************/
int __PPHCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pphcr_reg *pphcr_reg = (struct ku_pphcr_reg*)ku_reg;
    uint32_t i = 0;

    mlxsw_reg_pphcr_local_port_set(inbox, pphcr_reg->local_port);
    mlxsw_reg_pphcr_pnat_set(inbox, pphcr_reg->pnat);
    mlxsw_reg_pphcr_lp_msb_set(inbox, pphcr_reg->lp_msb);
    mlxsw_reg_pphcr_hist_type_set(inbox, pphcr_reg->hist_type);
    mlxsw_reg_pphcr_bin_range_write_mask_set(inbox, pphcr_reg->bin_range_write_mask);
    for (i = 0; i < SXD_PPHCR_BIN_RANGE_NUM; i++) {
        mlxsw_reg_pphcr_high_val_set(inbox, i, pphcr_reg->bin_range[i].high_val);
        mlxsw_reg_pphcr_low_val_set(inbox, i, pphcr_reg->bin_range[i].low_val);
    }


    return 0;
}

int __PPHCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pphcr_reg *pphcr_reg = (struct ku_pphcr_reg*)ku_reg;
    uint32_t i = 0;

    pphcr_reg->active_hist_type = mlxsw_reg_pphcr_active_hist_type_get(outbox);
    pphcr_reg->local_port = mlxsw_reg_pphcr_local_port_get(outbox);
    pphcr_reg->pnat = mlxsw_reg_pphcr_pnat_get(outbox);
    pphcr_reg->lp_msb = mlxsw_reg_pphcr_lp_msb_get(outbox);
    pphcr_reg->we = mlxsw_reg_pphcr_we_get(outbox);
    pphcr_reg->num_of_bins = mlxsw_reg_pphcr_num_of_bins_get(outbox);
    pphcr_reg->hist_type = mlxsw_reg_pphcr_hist_type_get(outbox);
    pphcr_reg->hist_max_measurement = mlxsw_reg_pphcr_hist_max_measurement_get(outbox);
    pphcr_reg->hist_min_measurement = mlxsw_reg_pphcr_hist_min_measurement_get(outbox);
    for (i = 0; i < SXD_PPHCR_BIN_RANGE_NUM; i++) {
        pphcr_reg->bin_range[i].high_val = mlxsw_reg_pphcr_high_val_get(outbox, i);
        pphcr_reg->bin_range[i].low_val = mlxsw_reg_pphcr_low_val_get(outbox, i);
    }


    return 0;
}
EXPORT_SYMBOL(__PPHCR_decode);

int sx_ACCESS_REG_PPHCR(struct sx_dev *dev, struct ku_access_pphcr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PPHCR_LEN >> 2) + 1;

    if (MLXSW_PPHCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPHCR_encode,
                                  __PPHCR_decode,
                                  reg_len_dword,
                                  &reg_data->pphcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPHCR);

int sx_EMAD_ACCESS_REG_PPHCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pphcr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PPHCR_LEN >> 2) + 1;

    if (MLXSW_PPHCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PPHCR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PPHCR_encode,
                                     __PPHCR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PPHCR);

/************************************************
* QCAP
***********************************************/
int __QCAP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_qcap_reg *qcap_reg = (struct ku_qcap_reg*)ku_reg;

    ((void)qcap_reg);

    return 0;
}

int __QCAP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_qcap_reg *qcap_reg = (struct ku_qcap_reg*)ku_reg;

    qcap_reg->max_policers_per_port = mlxsw_reg_qcap_max_policers_per_port_get(outbox);
    qcap_reg->max_policers_global = mlxsw_reg_qcap_max_policers_global_get(outbox);
    qcap_reg->max_policers_cpu = mlxsw_reg_qcap_max_policers_cpu_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__QCAP_decode);

int sx_ACCESS_REG_QCAP(struct sx_dev *dev, struct ku_access_qcap_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_QCAP_LEN >> 2) + 1;

    if (MLXSW_QCAP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __QCAP_encode,
                                  __QCAP_decode,
                                  reg_len_dword,
                                  &reg_data->qcap_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_QCAP);

int sx_EMAD_ACCESS_REG_QCAP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_qcap_reg *reg)
{
    u16 reg_len_dword = (MLXSW_QCAP_LEN >> 2) + 1;

    if (MLXSW_QCAP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_QCAP_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __QCAP_encode,
                                     __QCAP_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_QCAP);

/************************************************
* MTWE
***********************************************/
int __MTWE_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtwe_reg *mtwe_reg = (struct ku_mtwe_reg*)ku_reg;

    ((void)mtwe_reg);

    return 0;
}

int __MTWE_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtwe_reg *mtwe_reg = (struct ku_mtwe_reg*)ku_reg;
    uint32_t i = 0;

    for (i = 0; i < SXD_MTWE_SENSOR_WARNING_NUM; i++) {
        mtwe_reg->sensor_warning[i] = mlxsw_reg_mtwe_sensor_warning_get(outbox, i);
    }


    return 0;
}
EXPORT_SYMBOL(__MTWE_decode);

int sx_ACCESS_REG_MTWE(struct sx_dev *dev, struct ku_access_mtwe_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MTWE_LEN >> 2) + 1;

    if (MLXSW_MTWE_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTWE_encode,
                                  __MTWE_decode,
                                  reg_len_dword,
                                  &reg_data->mtwe_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTWE);

int sx_EMAD_ACCESS_REG_MTWE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtwe_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MTWE_LEN >> 2) + 1;

    if (MLXSW_MTWE_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MTWE_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MTWE_encode,
                                     __MTWE_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MTWE);

/************************************************
* MFGD
***********************************************/
int __MFGD_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfgd_reg *mfgd_reg = (struct ku_mfgd_reg*)ku_reg;

    mlxsw_reg_mfgd_en_debug_assert_set(inbox, mfgd_reg->en_debug_assert);
    mlxsw_reg_mfgd_fw_fatal_event_test_set(inbox, mfgd_reg->fw_fatal_event_test);
    mlxsw_reg_mfgd_fw_fatal_event_mode_set(inbox, mfgd_reg->fw_fatal_event_mode);


    return 0;
}

int __MFGD_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfgd_reg *mfgd_reg = (struct ku_mfgd_reg*)ku_reg;

    mfgd_reg->en_debug_assert = mlxsw_reg_mfgd_en_debug_assert_get(outbox);
    mfgd_reg->fw_fatal_event_test = mlxsw_reg_mfgd_fw_fatal_event_test_get(outbox);
    mfgd_reg->fw_fatal_event_mode = mlxsw_reg_mfgd_fw_fatal_event_mode_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MFGD_decode);

int sx_ACCESS_REG_MFGD(struct sx_dev *dev, struct ku_access_mfgd_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MFGD_LEN >> 2) + 1;

    if (MLXSW_MFGD_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFGD_encode,
                                  __MFGD_decode,
                                  reg_len_dword,
                                  &reg_data->mfgd_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFGD);

int sx_EMAD_ACCESS_REG_MFGD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mfgd_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MFGD_LEN >> 2) + 1;

    if (MLXSW_MFGD_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MFGD_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MFGD_encode,
                                     __MFGD_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MFGD);

/************************************************
* MGIR
***********************************************/
int __MGIR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mgir_reg *mgir_reg = (struct ku_mgir_reg*)ku_reg;

    ((void)mgir_reg);

    return 0;
}

int __MGIR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mgir_reg *mgir_reg = (struct ku_mgir_reg*)ku_reg;

    mgir_reg->hw_info.device_hw_revision = mlxsw_reg_mgir_device_hw_revision_get(outbox);
    mgir_reg->hw_info.device_id = mlxsw_reg_mgir_device_id_get(outbox);
    mgir_reg->hw_info.num_ports = mlxsw_reg_mgir_num_ports_get(outbox);
    mgir_reg->hw_info.technology = mlxsw_reg_mgir_technology_get(outbox);
    mgir_reg->hw_info.pvs = mlxsw_reg_mgir_pvs_get(outbox);
    mgir_reg->hw_info.hw_dev_id = mlxsw_reg_mgir_hw_dev_id_get(outbox);
    mlxsw_reg_mgir_manufacturing_base_mac_memcpy_from(outbox, (char *)mgir_reg->hw_info.manufacturing_base_mac);
    mgir_reg->hw_info.uptime = mlxsw_reg_mgir_uptime_get(outbox);
    mgir_reg->fw_info.dev_sc = mlxsw_reg_mgir_fw_info_dev_sc_get(outbox);
    mgir_reg->fw_info.latency_tlv = mlxsw_reg_mgir_fw_info_latency_tlv_get(outbox);
    mgir_reg->fw_info.string_tlv = mlxsw_reg_mgir_fw_info_string_tlv_get(outbox);
    mgir_reg->fw_info.dev = mlxsw_reg_mgir_fw_info_dev_get(outbox);
    mgir_reg->fw_info.debug = mlxsw_reg_mgir_fw_info_debug_get(outbox);
    mgir_reg->fw_info.signed_fw = mlxsw_reg_mgir_fw_info_signed_fw_get(outbox);
    mgir_reg->fw_info.secured = mlxsw_reg_mgir_fw_info_secured_get(outbox);
    mgir_reg->fw_info.major = mlxsw_reg_mgir_fw_info_major_get(outbox);
    mgir_reg->fw_info.minor = mlxsw_reg_mgir_fw_info_minor_get(outbox);
    mgir_reg->fw_info.sub_minor = mlxsw_reg_mgir_fw_info_sub_minor_get(outbox);
    mgir_reg->fw_info.build_id = mlxsw_reg_mgir_fw_info_build_id_get(outbox);
    mgir_reg->fw_info.month = mlxsw_reg_mgir_fw_info_month_get(outbox);
    mgir_reg->fw_info.day = mlxsw_reg_mgir_fw_info_day_get(outbox);
    mgir_reg->fw_info.year = mlxsw_reg_mgir_fw_info_year_get(outbox);
    mgir_reg->fw_info.hour = mlxsw_reg_mgir_fw_info_hour_get(outbox);
    mlxsw_reg_mgir_fw_info_psid_memcpy_from(outbox, (char *)mgir_reg->fw_info.psid);
    mgir_reg->fw_info.ini_file_version = mlxsw_reg_mgir_fw_info_ini_file_version_get(outbox);
    mgir_reg->fw_info.extended_major = mlxsw_reg_mgir_fw_info_extended_major_get(outbox);
    mgir_reg->fw_info.extended_minor = mlxsw_reg_mgir_fw_info_extended_minor_get(outbox);
    mgir_reg->fw_info.extended_sub_minor = mlxsw_reg_mgir_fw_info_extended_sub_minor_get(outbox);
    mgir_reg->fw_info.disabled_tiles_bitmap = mlxsw_reg_mgir_fw_info_disabled_tiles_bitmap_get(outbox);
    mgir_reg->fw_info.isfu_major = mlxsw_reg_mgir_fw_info_isfu_major_get(outbox);
    mgir_reg->fw_info.encryption = mlxsw_reg_mgir_fw_info_encryption_get(outbox);
    mgir_reg->fw_info.sec_boot = mlxsw_reg_mgir_fw_info_sec_boot_get(outbox);
    mgir_reg->fw_info.life_cycle = mlxsw_reg_mgir_fw_info_life_cycle_get(outbox);
    mgir_reg->sw_info.major = mlxsw_reg_mgir_sw_info_major_get(outbox);
    mgir_reg->sw_info.minor = mlxsw_reg_mgir_sw_info_minor_get(outbox);
    mgir_reg->sw_info.sub_minor = mlxsw_reg_mgir_sw_info_sub_minor_get(outbox);
    mgir_reg->sw_info.rom0_arch = mlxsw_reg_mgir_sw_info_rom0_arch_get(outbox);
    mgir_reg->sw_info.rom0_type = mlxsw_reg_mgir_sw_info_rom0_type_get(outbox);
    mgir_reg->sw_info.rom1_arch = mlxsw_reg_mgir_sw_info_rom1_arch_get(outbox);
    mgir_reg->sw_info.rom1_type = mlxsw_reg_mgir_sw_info_rom1_type_get(outbox);
    mgir_reg->sw_info.rom2_arch = mlxsw_reg_mgir_sw_info_rom2_arch_get(outbox);
    mgir_reg->sw_info.rom2_type = mlxsw_reg_mgir_sw_info_rom2_type_get(outbox);
    mgir_reg->sw_info.rom3_arch = mlxsw_reg_mgir_sw_info_rom3_arch_get(outbox);
    mgir_reg->sw_info.rom3_type = mlxsw_reg_mgir_sw_info_rom3_type_get(outbox);
    mgir_reg->sw_info.rom0_version.major = mlxsw_reg_mgir_sw_info_rom0_version_major_get(outbox);
    mgir_reg->sw_info.rom0_version.minor = mlxsw_reg_mgir_sw_info_rom0_version_minor_get(outbox);
    mgir_reg->sw_info.rom0_version.build = mlxsw_reg_mgir_sw_info_rom0_version_build_get(outbox);
    mgir_reg->sw_info.rom1_version.major = mlxsw_reg_mgir_sw_info_rom1_version_major_get(outbox);
    mgir_reg->sw_info.rom1_version.minor = mlxsw_reg_mgir_sw_info_rom1_version_minor_get(outbox);
    mgir_reg->sw_info.rom1_version.build = mlxsw_reg_mgir_sw_info_rom1_version_build_get(outbox);
    mgir_reg->sw_info.rom2_version.major = mlxsw_reg_mgir_sw_info_rom2_version_major_get(outbox);
    mgir_reg->sw_info.rom2_version.minor = mlxsw_reg_mgir_sw_info_rom2_version_minor_get(outbox);
    mgir_reg->sw_info.rom2_version.build = mlxsw_reg_mgir_sw_info_rom2_version_build_get(outbox);
    mgir_reg->sw_info.rom3_version.major = mlxsw_reg_mgir_sw_info_rom3_version_major_get(outbox);
    mgir_reg->sw_info.rom3_version.minor = mlxsw_reg_mgir_sw_info_rom3_version_minor_get(outbox);
    mgir_reg->sw_info.rom3_version.build = mlxsw_reg_mgir_sw_info_rom3_version_build_get(outbox);
    mlxsw_reg_mgir_dev_branch_tag_memcpy_from(outbox, (char *)mgir_reg->dev_info.dev_branch_tag);


    return 0;
}
EXPORT_SYMBOL(__MGIR_decode);

int sx_ACCESS_REG_MGIR(struct sx_dev *dev, struct ku_access_mgir_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MGIR_LEN >> 2) + 1;

    if (MLXSW_MGIR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MGIR_encode,
                                  __MGIR_decode,
                                  reg_len_dword,
                                  &reg_data->mgir_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MGIR);

int sx_EMAD_ACCESS_REG_MGIR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mgir_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MGIR_LEN >> 2) + 1;

    if (MLXSW_MGIR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MGIR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MGIR_encode,
                                     __MGIR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MGIR);

/************************************************
* RIRT
***********************************************/
int __RIRT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_rirt_reg *rirt_reg = (struct ku_rirt_reg*)ku_reg;

    mlxsw_reg_rirt_offset_set(inbox, rirt_reg->offset);


    return 0;
}

int __RIRT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_rirt_reg *rirt_reg = (struct ku_rirt_reg*)ku_reg;
    uint32_t i = 0;

    rirt_reg->offset = mlxsw_reg_rirt_offset_get(outbox);
    for (i = 0; i < SXD_RIRT_ROUTER_ENTRY_RECORD_NUM; i++) {
        rirt_reg->router_entry_record[i].valid = mlxsw_reg_rirt_valid_get(outbox, i);
        rirt_reg->router_entry_record[i].swid = mlxsw_reg_rirt_swid_get(outbox, i);
        rirt_reg->router_entry_record[i].subnet_prefix = mlxsw_reg_rirt_subnet_prefix_get(outbox, i);
    }


    return 0;
}
EXPORT_SYMBOL(__RIRT_decode);

int sx_ACCESS_REG_RIRT(struct sx_dev *dev, struct ku_access_rirt_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_RIRT_LEN >> 2) + 1;

    if (MLXSW_RIRT_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __RIRT_encode,
                                  __RIRT_decode,
                                  reg_len_dword,
                                  &reg_data->rirt_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_RIRT);

int sx_EMAD_ACCESS_REG_RIRT(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_rirt_reg *reg)
{
    u16 reg_len_dword = (MLXSW_RIRT_LEN >> 2) + 1;

    if (MLXSW_RIRT_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_RIRT_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __RIRT_encode,
                                     __RIRT_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_RIRT);

/************************************************
* PPCGP
***********************************************/
int __PPCGP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppcgp_reg *ppcgp_reg = (struct ku_ppcgp_reg*)ku_reg;

    mlxsw_reg_ppcgp_grp_profile_set(inbox, ppcgp_reg->grp_profile);
    mlxsw_reg_ppcgp_hi_set(inbox, ppcgp_reg->grp_map.hi);
    mlxsw_reg_ppcgp_lo_set(inbox, ppcgp_reg->grp_map.lo);


    return 0;
}

int __PPCGP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppcgp_reg *ppcgp_reg = (struct ku_ppcgp_reg*)ku_reg;

    ppcgp_reg->grp_profile = mlxsw_reg_ppcgp_grp_profile_get(outbox);
    ppcgp_reg->grp_map.hi = mlxsw_reg_ppcgp_hi_get(outbox);
    ppcgp_reg->grp_map.lo = mlxsw_reg_ppcgp_lo_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__PPCGP_decode);

int sx_ACCESS_REG_PPCGP(struct sx_dev *dev, struct ku_access_ppcgp_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PPCGP_LEN >> 2) + 1;

    if (MLXSW_PPCGP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPCGP_encode,
                                  __PPCGP_decode,
                                  reg_len_dword,
                                  &reg_data->ppcgp_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPCGP);

int sx_EMAD_ACCESS_REG_PPCGP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ppcgp_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PPCGP_LEN >> 2) + 1;

    if (MLXSW_PPCGP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PPCGP_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PPCGP_encode,
                                     __PPCGP_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PPCGP);

/************************************************
* CEER
***********************************************/
int __CEER_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ceer_reg *ceer_reg = (struct ku_ceer_reg*)ku_reg;

    mlxsw_reg_ceer_clear_set(inbox, ceer_reg->clear);
    mlxsw_reg_ceer_local_port_set(inbox, ceer_reg->local_port);
    mlxsw_reg_ceer_lp_msb_set(inbox, ceer_reg->lp_msb);
    mlxsw_reg_ceer_detection_entry_set(inbox, ceer_reg->detection_entry);
    switch (ceer_reg->extra_data_type) {
    case SXD_CEER_EXTRA_DATA_TYPE_NONE_E:
        break;

    case SXD_CEER_EXTRA_DATA_TYPE_TUNNEL_E:
        break;

    case SXD_CEER_EXTRA_DATA_TYPE_MPLS_E:
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}

int __CEER_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ceer_reg *ceer_reg = (struct ku_ceer_reg*)ku_reg;
    uint32_t i = 0;

    ceer_reg->clear = mlxsw_reg_ceer_clear_get(outbox);
    ceer_reg->local_port = mlxsw_reg_ceer_local_port_get(outbox);
    ceer_reg->lp_msb = mlxsw_reg_ceer_lp_msb_get(outbox);
    ceer_reg->detection_entry = mlxsw_reg_ceer_detection_entry_get(outbox);
    ceer_reg->det = mlxsw_reg_ceer_det_get(outbox);
    ceer_reg->l2_type = mlxsw_reg_ceer_l2_type_get(outbox);
    ceer_reg->extra_data_type = mlxsw_reg_ceer_extra_data_type_get(outbox);
    ceer_reg->tunnel_type = mlxsw_reg_ceer_tunnel_type_get(outbox);
    ceer_reg->l4_type = mlxsw_reg_ceer_l4_type_get(outbox);
    ceer_reg->l3_type = mlxsw_reg_ceer_l3_type_get(outbox);
    ceer_reg->vlan_type = mlxsw_reg_ceer_vlan_type_get(outbox);
    ceer_reg->hash_valid = mlxsw_reg_ceer_hash_valid_get(outbox);
    ceer_reg->lag_hash = mlxsw_reg_ceer_lag_hash_get(outbox);
    ceer_reg->router_hash = mlxsw_reg_ceer_router_hash_get(outbox);
    mlxsw_reg_ceer_dmac_memcpy_from(outbox, (char *)ceer_reg->dmac);
    mlxsw_reg_ceer_smac_memcpy_from(outbox, (char *)ceer_reg->smac);
    ceer_reg->pcp = mlxsw_reg_ceer_pcp_get(outbox);
    ceer_reg->dei = mlxsw_reg_ceer_dei_get(outbox);
    ceer_reg->vid = mlxsw_reg_ceer_vid_get(outbox);
    ceer_reg->inner_pcp = mlxsw_reg_ceer_inner_pcp_get(outbox);
    ceer_reg->inner_dei = mlxsw_reg_ceer_inner_dei_get(outbox);
    ceer_reg->inner_vid = mlxsw_reg_ceer_inner_vid_get(outbox);
    ceer_reg->dscp = mlxsw_reg_ceer_dscp_get(outbox);
    ceer_reg->ecn = mlxsw_reg_ceer_ecn_get(outbox);
    ceer_reg->ttl = mlxsw_reg_ceer_ttl_get(outbox);
    ceer_reg->dont_frag = mlxsw_reg_ceer_dont_frag_get(outbox);
    ceer_reg->sport = mlxsw_reg_ceer_sport_get(outbox);
    ceer_reg->dport = mlxsw_reg_ceer_dport_get(outbox);
    for (i = 0; i < SXD_CEER_SIP_NUM; i++) {
        ceer_reg->sip[i] = mlxsw_reg_ceer_sip_get(outbox, i);
    }
    for (i = 0; i < SXD_CEER_DIP_NUM; i++) {
        ceer_reg->dip[i] = mlxsw_reg_ceer_dip_get(outbox, i);
    }
    switch (ceer_reg->extra_data_type) {
    case SXD_CEER_EXTRA_DATA_TYPE_NONE_E:
        break;

    case SXD_CEER_EXTRA_DATA_TYPE_TUNNEL_E:
        ceer_reg->extra_data.ceer_extra_fields.vni = mlxsw_reg_ceer_extra_data_ceer_extra_fields_vni_get(outbox);
        mlxsw_reg_ceer_extra_data_ceer_extra_fields_inner_dmac_memcpy_from(outbox, (char *)ceer_reg->extra_data.ceer_extra_fields.inner_dmac);
        mlxsw_reg_ceer_extra_data_ceer_extra_fields_inner_smac_memcpy_from(outbox, (char *)ceer_reg->extra_data.ceer_extra_fields.inner_smac);
        ceer_reg->extra_data.ceer_extra_fields.inner_l3_type = mlxsw_reg_ceer_extra_data_ceer_extra_fields_inner_l3_type_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields.inner_dscp = mlxsw_reg_ceer_extra_data_ceer_extra_fields_inner_dscp_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields.inner_ecn = mlxsw_reg_ceer_extra_data_ceer_extra_fields_inner_ecn_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields.inner_ttl = mlxsw_reg_ceer_extra_data_ceer_extra_fields_inner_ttl_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields.inner_dont_frag = mlxsw_reg_ceer_extra_data_ceer_extra_fields_inner_dont_frag_get(outbox);
        for (i = 0; i < SXD_CEER_INNER_SIP_NUM; i++) {
            ceer_reg->extra_data.ceer_extra_fields.inner_sip[i] = mlxsw_reg_ceer_extra_data_ceer_extra_fields_inner_sip_get(outbox, i);
        }
        for (i = 0; i < SXD_CEER_INNER_DIP_NUM; i++) {
            ceer_reg->extra_data.ceer_extra_fields.inner_dip[i] = mlxsw_reg_ceer_extra_data_ceer_extra_fields_inner_dip_get(outbox, i);
        }
        break;

    case SXD_CEER_EXTRA_DATA_TYPE_MPLS_E:
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_bos = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_bos_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_exp = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_exp_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_lb0_v = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_lb0_v_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_label0_label_id = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_label0_label_id_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_label0_ttl = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_label0_ttl_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_lb1_v = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_lb1_v_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_label1_label_id = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_label1_label_id_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_label1_ttl = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_label1_ttl_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_lb2_v = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_lb2_v_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_label2_label_id = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_label2_label_id_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_label2_ttl = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_label2_ttl_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_lb3_v = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_lb3_v_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_label3_label_id = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_label3_label_id_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_label3_ttl = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_label3_ttl_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_lb4_v = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_lb4_v_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_label4_label_id = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_label4_label_id_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_mpls.mpls_label4_ttl = mlxsw_reg_ceer_extra_data_ceer_extra_fields_mpls_mpls_label4_ttl_get(outbox);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}
EXPORT_SYMBOL(__CEER_decode);

int sx_ACCESS_REG_CEER(struct sx_dev *dev, struct ku_access_ceer_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_CEER_LEN >> 2) + 1;

    if (MLXSW_CEER_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __CEER_encode,
                                  __CEER_decode,
                                  reg_len_dword,
                                  &reg_data->ceer_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_CEER);

int sx_EMAD_ACCESS_REG_CEER(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ceer_reg *reg)
{
    u16 reg_len_dword = (MLXSW_CEER_LEN >> 2) + 1;

    if (MLXSW_CEER_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_CEER_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __CEER_encode,
                                     __CEER_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_CEER);

/************************************************
* IBFMRC
***********************************************/
int __IBFMRC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ibfmrc_reg *ibfmrc_reg = (struct ku_ibfmrc_reg*)ku_reg;

    mlxsw_reg_ibfmrc_attr_id_en_set(inbox, ibfmrc_reg->attr_id_en);


    return 0;
}

int __IBFMRC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ibfmrc_reg *ibfmrc_reg = (struct ku_ibfmrc_reg*)ku_reg;

    ibfmrc_reg->attr_id_en = mlxsw_reg_ibfmrc_attr_id_en_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__IBFMRC_decode);

int sx_ACCESS_REG_IBFMRC(struct sx_dev *dev, struct ku_access_ibfmrc_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_IBFMRC_LEN >> 2) + 1;

    if (MLXSW_IBFMRC_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __IBFMRC_encode,
                                  __IBFMRC_decode,
                                  reg_len_dword,
                                  &reg_data->ibfmrc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_IBFMRC);

int sx_EMAD_ACCESS_REG_IBFMRC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ibfmrc_reg *reg)
{
    u16 reg_len_dword = (MLXSW_IBFMRC_LEN >> 2) + 1;

    if (MLXSW_IBFMRC_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_IBFMRC_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __IBFMRC_encode,
                                     __IBFMRC_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_IBFMRC);

/************************************************
* MECCC
***********************************************/
int __MECCC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_meccc_reg *meccc_reg = (struct ku_meccc_reg*)ku_reg;

    mlxsw_reg_meccc_device_index_set(inbox, meccc_reg->device_index);
    mlxsw_reg_meccc_slot_index_set(inbox, meccc_reg->slot_index);
    mlxsw_reg_meccc_clr_set(inbox, meccc_reg->clr);


    return 0;
}

int __MECCC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_meccc_reg *meccc_reg = (struct ku_meccc_reg*)ku_reg;

    meccc_reg->device_index = mlxsw_reg_meccc_device_index_get(outbox);
    meccc_reg->slot_index = mlxsw_reg_meccc_slot_index_get(outbox);
    meccc_reg->clr = mlxsw_reg_meccc_clr_get(outbox);
    meccc_reg->ecc_crt_cnt = mlxsw_reg_meccc_ecc_crt_cnt_get(outbox);
    meccc_reg->ecc_ucrt_cnt = mlxsw_reg_meccc_ecc_ucrt_cnt_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MECCC_decode);

int sx_ACCESS_REG_MECCC(struct sx_dev *dev, struct ku_access_meccc_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MECCC_LEN >> 2) + 1;

    if (MLXSW_MECCC_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MECCC_encode,
                                  __MECCC_decode,
                                  reg_len_dword,
                                  &reg_data->meccc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MECCC);

int sx_EMAD_ACCESS_REG_MECCC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_meccc_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MECCC_LEN >> 2) + 1;

    if (MLXSW_MECCC_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MECCC_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MECCC_encode,
                                     __MECCC_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MECCC);

/************************************************
* SMID_V2
***********************************************/
int __SMID_V2_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_smid_v2_reg *smid_v2_reg = (struct ku_smid_v2_reg*)ku_reg;
    uint32_t i = 0;

    mlxsw_reg_smid_v2_swid_set(inbox, smid_v2_reg->swid);
    mlxsw_reg_smid_v2_mid_set(inbox, smid_v2_reg->mid);
    mlxsw_reg_smid_v2_op_set(inbox, smid_v2_reg->op);
    mlxsw_reg_smid_v2_smpe_valid_set(inbox, smid_v2_reg->smpe_valid);
    mlxsw_reg_smid_v2_smpe_set(inbox, smid_v2_reg->smpe);
    for (i = 0; i < SXD_SMID_V2_PORT_NUM; i++) {
        mlxsw_reg_smid_v2_port_set(inbox, i, smid_v2_reg->port[i]);
    }
    for (i = 0; i < SXD_SMID_V2_MASK_NUM; i++) {
        mlxsw_reg_smid_v2_mask_set(inbox, i, smid_v2_reg->mask[i]);
    }


    return 0;
}

int __SMID_V2_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_smid_v2_reg *smid_v2_reg = (struct ku_smid_v2_reg*)ku_reg;
    uint32_t i = 0;

    smid_v2_reg->swid = mlxsw_reg_smid_v2_swid_get(outbox);
    smid_v2_reg->mid = mlxsw_reg_smid_v2_mid_get(outbox);
    smid_v2_reg->op = mlxsw_reg_smid_v2_op_get(outbox);
    smid_v2_reg->smpe_valid = mlxsw_reg_smid_v2_smpe_valid_get(outbox);
    smid_v2_reg->smpe = mlxsw_reg_smid_v2_smpe_get(outbox);
    for (i = 0; i < SXD_SMID_V2_PORT_NUM; i++) {
        smid_v2_reg->port[i] = mlxsw_reg_smid_v2_port_get(outbox, i);
    }


    return 0;
}
EXPORT_SYMBOL(__SMID_V2_decode);

int sx_ACCESS_REG_SMID_V2(struct sx_dev *dev, struct ku_access_smid_v2_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_SMID_V2_LEN >> 2) + 1;

    if (MLXSW_SMID_V2_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SMID_V2_encode,
                                  __SMID_V2_decode,
                                  reg_len_dword,
                                  &reg_data->smid_v2_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SMID_V2);

int sx_EMAD_ACCESS_REG_SMID_V2(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_smid_v2_reg *reg)
{
    u16 reg_len_dword = (MLXSW_SMID_V2_LEN >> 2) + 1;

    if (MLXSW_SMID_V2_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_SMID_V2_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __SMID_V2_encode,
                                     __SMID_V2_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_SMID_V2);

/************************************************
* QSTCT
***********************************************/
int __QSTCT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_qstct_reg *qstct_reg = (struct ku_qstct_reg*)ku_reg;

    mlxsw_reg_qstct_swid_set(inbox, qstct_reg->swid);
    mlxsw_reg_qstct_switch_prio_set(inbox, qstct_reg->switch_prio);
    mlxsw_reg_qstct_utclass_set(inbox, qstct_reg->utclass);
    mlxsw_reg_qstct_mtclass_set(inbox, qstct_reg->mtclass);


    return 0;
}

int __QSTCT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_qstct_reg *qstct_reg = (struct ku_qstct_reg*)ku_reg;

    qstct_reg->swid = mlxsw_reg_qstct_swid_get(outbox);
    qstct_reg->switch_prio = mlxsw_reg_qstct_switch_prio_get(outbox);
    qstct_reg->utclass = mlxsw_reg_qstct_utclass_get(outbox);
    qstct_reg->mtclass = mlxsw_reg_qstct_mtclass_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__QSTCT_decode);

int sx_ACCESS_REG_QSTCT(struct sx_dev *dev, struct ku_access_qstct_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_QSTCT_LEN >> 2) + 1;

    if (MLXSW_QSTCT_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __QSTCT_encode,
                                  __QSTCT_decode,
                                  reg_len_dword,
                                  &reg_data->qstct_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_QSTCT);

int sx_EMAD_ACCESS_REG_QSTCT(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_qstct_reg *reg)
{
    u16 reg_len_dword = (MLXSW_QSTCT_LEN >> 2) + 1;

    if (MLXSW_QSTCT_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_QSTCT_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __QSTCT_encode,
                                     __QSTCT_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_QSTCT);

/************************************************
* PMCR
***********************************************/
int __PMCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmcr_reg *pmcr_reg = (struct ku_pmcr_reg*)ku_reg;

    mlxsw_reg_pmcr_cs_sel_set(inbox, pmcr_reg->cs_sel);
    mlxsw_reg_pmcr_local_port_set(inbox, pmcr_reg->local_port);
    mlxsw_reg_pmcr_lp_msb_set(inbox, pmcr_reg->lp_msb);
    mlxsw_reg_pmcr_db_set(inbox, pmcr_reg->db);
    mlxsw_reg_pmcr_tx_disable_override_value_set(inbox, pmcr_reg->tx_disable_override_value);
    mlxsw_reg_pmcr_tx_disable_override_cntl_set(inbox, pmcr_reg->tx_disable_override_cntl);
    mlxsw_reg_pmcr_cdr_override_value_set(inbox, pmcr_reg->cdr_override_value);
    mlxsw_reg_pmcr_cdr_override_cntl_set(inbox, pmcr_reg->cdr_override_cntl);
    mlxsw_reg_pmcr_rx_los_override_admin_set(inbox, pmcr_reg->rx_los_override_admin);
    mlxsw_reg_pmcr_rx_los_override_cntl_set(inbox, pmcr_reg->rx_los_override_cntl);
    mlxsw_reg_pmcr_rx_amp_override_value_set(inbox, pmcr_reg->rx_amp_override_value);
    mlxsw_reg_pmcr_rx_amp_override_cntl_set(inbox, pmcr_reg->rx_amp_override_cntl);
    mlxsw_reg_pmcr_rx_post_emp_override_value_set(inbox, pmcr_reg->rx_post_emp_override_value);
    mlxsw_reg_pmcr_rx_post_emp_override_cntl_set(inbox, pmcr_reg->rx_post_emp_override_cntl);
    mlxsw_reg_pmcr_rx_emp_override_value_set(inbox, pmcr_reg->rx_emp_override_value);
    mlxsw_reg_pmcr_rx_emp_override_cntl_set(inbox, pmcr_reg->rx_emp_override_cntl);
    mlxsw_reg_pmcr_tx_adaptive_override_cntrl_set(inbox, pmcr_reg->tx_adaptive_override_cntrl);
    mlxsw_reg_pmcr_tx_adaptive_override_value_set(inbox, pmcr_reg->tx_adaptive_override_value);
    mlxsw_reg_pmcr_tx_equ_override_value_set(inbox, pmcr_reg->tx_equ_override_value);
    mlxsw_reg_pmcr_tx_equ_override_cntl_set(inbox, pmcr_reg->tx_equ_override_cntl);
    mlxsw_reg_pmcr_rs_override_value_set(inbox, pmcr_reg->rs_override_value);
    mlxsw_reg_pmcr_rs_override_cntl_set(inbox, pmcr_reg->rs_override_cntl);
    mlxsw_reg_pmcr_ap_sel_override_value_set(inbox, pmcr_reg->ap_sel_override_value);
    mlxsw_reg_pmcr_ap_sel_override_cntrl_set(inbox, pmcr_reg->ap_sel_override_cntrl);


    return 0;
}

int __PMCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmcr_reg *pmcr_reg = (struct ku_pmcr_reg*)ku_reg;

    pmcr_reg->cs_sel = mlxsw_reg_pmcr_cs_sel_get(outbox);
    pmcr_reg->local_port = mlxsw_reg_pmcr_local_port_get(outbox);
    pmcr_reg->lp_msb = mlxsw_reg_pmcr_lp_msb_get(outbox);
    pmcr_reg->error_code_response = mlxsw_reg_pmcr_error_code_response_get(outbox);
    pmcr_reg->db = mlxsw_reg_pmcr_db_get(outbox);
    pmcr_reg->tx_disable_override_value = mlxsw_reg_pmcr_tx_disable_override_value_get(outbox);
    pmcr_reg->tx_disable_override_cap = mlxsw_reg_pmcr_tx_disable_override_cap_get(outbox);
    pmcr_reg->tx_disable_override_cntl = mlxsw_reg_pmcr_tx_disable_override_cntl_get(outbox);
    pmcr_reg->cdr_override_value = mlxsw_reg_pmcr_cdr_override_value_get(outbox);
    pmcr_reg->cdr_override_cap = mlxsw_reg_pmcr_cdr_override_cap_get(outbox);
    pmcr_reg->cdr_override_cntl = mlxsw_reg_pmcr_cdr_override_cntl_get(outbox);
    pmcr_reg->rx_los_override_admin = mlxsw_reg_pmcr_rx_los_override_admin_get(outbox);
    pmcr_reg->rx_los_override_cap = mlxsw_reg_pmcr_rx_los_override_cap_get(outbox);
    pmcr_reg->rx_los_override_cntl = mlxsw_reg_pmcr_rx_los_override_cntl_get(outbox);
    pmcr_reg->rx_amp_override_value_cap = mlxsw_reg_pmcr_rx_amp_override_value_cap_get(outbox);
    pmcr_reg->rx_amp_override_value = mlxsw_reg_pmcr_rx_amp_override_value_get(outbox);
    pmcr_reg->rx_amp_override_cap = mlxsw_reg_pmcr_rx_amp_override_cap_get(outbox);
    pmcr_reg->rx_amp_override_cntl = mlxsw_reg_pmcr_rx_amp_override_cntl_get(outbox);
    pmcr_reg->rx_post_emp_override_value_cap = mlxsw_reg_pmcr_rx_post_emp_override_value_cap_get(outbox);
    pmcr_reg->rx_post_emp_override_value = mlxsw_reg_pmcr_rx_post_emp_override_value_get(outbox);
    pmcr_reg->rx_post_emp_override_cap = mlxsw_reg_pmcr_rx_post_emp_override_cap_get(outbox);
    pmcr_reg->rx_post_emp_override_cntl = mlxsw_reg_pmcr_rx_post_emp_override_cntl_get(outbox);
    pmcr_reg->rx_emp_override_value_cap = mlxsw_reg_pmcr_rx_emp_override_value_cap_get(outbox);
    pmcr_reg->rx_emp_override_value = mlxsw_reg_pmcr_rx_emp_override_value_get(outbox);
    pmcr_reg->rx_emp_override_cap = mlxsw_reg_pmcr_rx_emp_override_cap_get(outbox);
    pmcr_reg->rx_emp_override_cntl = mlxsw_reg_pmcr_rx_emp_override_cntl_get(outbox);
    pmcr_reg->tx_adaptive_override_cap = mlxsw_reg_pmcr_tx_adaptive_override_cap_get(outbox);
    pmcr_reg->tx_adaptive_override_cntrl = mlxsw_reg_pmcr_tx_adaptive_override_cntrl_get(outbox);
    pmcr_reg->tx_adaptive_override_value = mlxsw_reg_pmcr_tx_adaptive_override_value_get(outbox);
    pmcr_reg->tx_equ_override_value_cap = mlxsw_reg_pmcr_tx_equ_override_value_cap_get(outbox);
    pmcr_reg->tx_equ_override_value = mlxsw_reg_pmcr_tx_equ_override_value_get(outbox);
    pmcr_reg->tx_equ_override_cap = mlxsw_reg_pmcr_tx_equ_override_cap_get(outbox);
    pmcr_reg->tx_equ_override_cntl = mlxsw_reg_pmcr_tx_equ_override_cntl_get(outbox);
    pmcr_reg->rs_override_value = mlxsw_reg_pmcr_rs_override_value_get(outbox);
    pmcr_reg->rs_override_cntl = mlxsw_reg_pmcr_rs_override_cntl_get(outbox);
    pmcr_reg->ap_sel_override_value = mlxsw_reg_pmcr_ap_sel_override_value_get(outbox);
    pmcr_reg->ap_sel_override_cntrl = mlxsw_reg_pmcr_ap_sel_override_cntrl_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__PMCR_decode);

int sx_ACCESS_REG_PMCR(struct sx_dev *dev, struct ku_access_pmcr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PMCR_LEN >> 2) + 1;

    if (MLXSW_PMCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMCR_encode,
                                  __PMCR_decode,
                                  reg_len_dword,
                                  &reg_data->pmcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMCR);

int sx_EMAD_ACCESS_REG_PMCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmcr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PMCR_LEN >> 2) + 1;

    if (MLXSW_PMCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PMCR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PMCR_encode,
                                     __PMCR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PMCR);

/************************************************
* MTPPS
***********************************************/
int __MTPPS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtpps_reg *mtpps_reg = (struct ku_mtpps_reg*)ku_reg;

    mlxsw_reg_mtpps_field_select_set(inbox, mtpps_reg->field_select);
    mlxsw_reg_mtpps_enable_set(inbox, mtpps_reg->enable);
    mlxsw_reg_mtpps_utc_mode_set(inbox, mtpps_reg->utc_mode);
    mlxsw_reg_mtpps_pattern_set(inbox, mtpps_reg->pattern);
    mlxsw_reg_mtpps_pin_mode_set(inbox, mtpps_reg->pin_mode);
    mlxsw_reg_mtpps_pin_set(inbox, mtpps_reg->pin);
    mlxsw_reg_mtpps_time_stamp_set(inbox, mtpps_reg->time_stamp);
    mlxsw_reg_mtpps_out_pulse_duration_set(inbox, mtpps_reg->out_pulse_duration);


    return 0;
}

int __MTPPS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtpps_reg *mtpps_reg = (struct ku_mtpps_reg*)ku_reg;

    mtpps_reg->cap_number_of_pps_pins = mlxsw_reg_mtpps_cap_number_of_pps_pins_get(outbox);
    mtpps_reg->cap_max_num_of_pps_in_pins = mlxsw_reg_mtpps_cap_max_num_of_pps_in_pins_get(outbox);
    mtpps_reg->cap_max_num_of_pps_out_pins = mlxsw_reg_mtpps_cap_max_num_of_pps_out_pins_get(outbox);
    mtpps_reg->cap_pin_3_mode = mlxsw_reg_mtpps_cap_pin_3_mode_get(outbox);
    mtpps_reg->cap_pin_2_mode = mlxsw_reg_mtpps_cap_pin_2_mode_get(outbox);
    mtpps_reg->cap_pin_1_mode = mlxsw_reg_mtpps_cap_pin_1_mode_get(outbox);
    mtpps_reg->cap_pin_0_mode = mlxsw_reg_mtpps_cap_pin_0_mode_get(outbox);
    mtpps_reg->cap_pin_7_mode = mlxsw_reg_mtpps_cap_pin_7_mode_get(outbox);
    mtpps_reg->cap_pin_6_mode = mlxsw_reg_mtpps_cap_pin_6_mode_get(outbox);
    mtpps_reg->cap_pin_5_mode = mlxsw_reg_mtpps_cap_pin_5_mode_get(outbox);
    mtpps_reg->cap_pin_4_mode = mlxsw_reg_mtpps_cap_pin_4_mode_get(outbox);
    mtpps_reg->enable = mlxsw_reg_mtpps_enable_get(outbox);
    mtpps_reg->utc_mode = mlxsw_reg_mtpps_utc_mode_get(outbox);
    mtpps_reg->pattern = mlxsw_reg_mtpps_pattern_get(outbox);
    mtpps_reg->pin_mode = mlxsw_reg_mtpps_pin_mode_get(outbox);
    mtpps_reg->pin = mlxsw_reg_mtpps_pin_get(outbox);
    mtpps_reg->time_stamp = mlxsw_reg_mtpps_time_stamp_get(outbox);
    mtpps_reg->out_pulse_duration = mlxsw_reg_mtpps_out_pulse_duration_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MTPPS_decode);

int sx_ACCESS_REG_MTPPS(struct sx_dev *dev, struct ku_access_mtpps_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MTPPS_LEN >> 2) + 1;

    if (MLXSW_MTPPS_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTPPS_encode,
                                  __MTPPS_decode,
                                  reg_len_dword,
                                  &reg_data->mtpps_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTPPS);

int sx_EMAD_ACCESS_REG_MTPPS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtpps_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MTPPS_LEN >> 2) + 1;

    if (MLXSW_MTPPS_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MTPPS_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MTPPS_encode,
                                     __MTPPS_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MTPPS);

/************************************************
* PPCNT
***********************************************/
int __PPCNT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppcnt_reg *ppcnt_reg = (struct ku_ppcnt_reg*)ku_reg;

    mlxsw_reg_ppcnt_swid_set(inbox, ppcnt_reg->swid);
    mlxsw_reg_ppcnt_local_port_set(inbox, ppcnt_reg->local_port);
    mlxsw_reg_ppcnt_pnat_set(inbox, ppcnt_reg->pnat);
    mlxsw_reg_ppcnt_lp_msb_set(inbox, ppcnt_reg->lp_msb);
    mlxsw_reg_ppcnt_port_type_set(inbox, ppcnt_reg->port_type);
    mlxsw_reg_ppcnt_grp_set(inbox, ppcnt_reg->grp);
    mlxsw_reg_ppcnt_clr_set(inbox, ppcnt_reg->clr);
    mlxsw_reg_ppcnt_lp_gl_set(inbox, ppcnt_reg->lp_gl);
    mlxsw_reg_ppcnt_grp_profile_set(inbox, ppcnt_reg->grp_profile);
    mlxsw_reg_ppcnt_prio_tc_set(inbox, ppcnt_reg->prio_tc);
    switch (ppcnt_reg->grp) {
    case SXD_PPCNT_GRP_IEEE_802_3_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_RFC_2863_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_RFC_2819_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_RFC_3635_COUNTERS_E:
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_alignment_errors_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_alignment_errors_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_fcs_errors_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_fcs_errors_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_single_collision_frames_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_single_collision_frames_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_multiple_collision_frames_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_multiple_collision_frames_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_sqe_test_errors_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_sqe_test_errors_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_deferred_transmissions_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_deferred_transmissions_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_late_collisions_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_late_collisions_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_excessive_collisions_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_excessive_collisions_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_transmit_errors_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_transmit_errors_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_carrier_sense_errors_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_carrier_sense_errors_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_frame_too_longs_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_frame_too_longs_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_receive_errors_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_receive_errors_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_symbol_errors_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_symbol_errors_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3control_in_unknown_opcodes_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3control_in_unknown_opcodes_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3in_pause_frames_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3in_pause_frames_low);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_high_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3out_pause_frames_high);
        mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_low_set(inbox, ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3out_pause_frames_low);
        break;

    case SXD_PPCNT_GRP_ETHERNET_EXTENDED_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_ETHERNET_DISCARD_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_LINK_LEVEL_RETRANSMISSION_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_PER_PRIORITY_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_PER_TRAFFIC_CLASS_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_PHYSICAL_LAYER_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_PER_TRAFFIC_CLASS_CONGESTION_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_PER_RECEIVE_BUFFER_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_PHYSICAL_LAYER_STATISTICAL_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_OUT_OF_BAND_PORT_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_INFINIBAND_PORT_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_INFINIBAND_EXTENDED_PORT_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_PLR_COUNTERS_GROUP_E:
        break;

    case SXD_PPCNT_GRP_RS_FEC_HISTOGRAM_GROUP_E:
        break;

    case SXD_PPCNT_GRP_USR_XSR_PHYSICAL_LAYER_COUNTERS_GROUP_E:
        break;

    case SXD_PPCNT_GRP_INFINIBAND_PKTS_COUNTERS_E:
        break;

    case SXD_PPCNT_GRP_INFINIBAND_GENERAL_COUNTERS_E:
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}

int __PPCNT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppcnt_reg *ppcnt_reg = (struct ku_ppcnt_reg*)ku_reg;
    uint32_t i = 0;

    ppcnt_reg->swid = mlxsw_reg_ppcnt_swid_get(outbox);
    ppcnt_reg->local_port = mlxsw_reg_ppcnt_local_port_get(outbox);
    ppcnt_reg->pnat = mlxsw_reg_ppcnt_pnat_get(outbox);
    ppcnt_reg->lp_msb = mlxsw_reg_ppcnt_lp_msb_get(outbox);
    ppcnt_reg->port_type = mlxsw_reg_ppcnt_port_type_get(outbox);
    ppcnt_reg->grp = mlxsw_reg_ppcnt_grp_get(outbox);
    ppcnt_reg->clr = mlxsw_reg_ppcnt_clr_get(outbox);
    ppcnt_reg->lp_gl = mlxsw_reg_ppcnt_lp_gl_get(outbox);
    ppcnt_reg->grp_profile = mlxsw_reg_ppcnt_grp_profile_get(outbox);
    ppcnt_reg->prio_tc = mlxsw_reg_ppcnt_prio_tc_get(outbox);
    switch (ppcnt_reg->grp) {
    case SXD_PPCNT_GRP_IEEE_802_3_COUNTERS_E:
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_frames_transmitted_ok_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_frames_transmitted_ok_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_frames_transmitted_ok_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_frames_transmitted_ok_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_frames_received_ok_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_frames_received_ok_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_frames_received_ok_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_frames_received_ok_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_frame_check_sequence_errors_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_frame_check_sequence_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_frame_check_sequence_errors_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_frame_check_sequence_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_alignment_errors_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_alignment_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_alignment_errors_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_alignment_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_octets_transmitted_ok_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_octets_transmitted_ok_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_octets_transmitted_ok_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_octets_transmitted_ok_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_octets_received_ok_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_octets_received_ok_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_octets_received_ok_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_octets_received_ok_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_multicast_frames_xmitted_ok_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_xmitted_ok_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_multicast_frames_xmitted_ok_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_xmitted_ok_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_broadcast_frames_xmitted_ok_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_xmitted_ok_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_broadcast_frames_xmitted_ok_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_xmitted_ok_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_multicast_frames_received_ok_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_received_ok_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_multicast_frames_received_ok_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_multicast_frames_received_ok_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_broadcast_frames_received_ok_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_received_ok_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_broadcast_frames_received_ok_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_broadcast_frames_received_ok_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_in_range_length_errors_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_in_range_length_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_in_range_length_errors_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_in_range_length_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_out_of_range_length_field_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_out_of_range_length_field_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_out_of_range_length_field_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_out_of_range_length_field_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_frame_too_long_errors_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_frame_too_long_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_frame_too_long_errors_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_frame_too_long_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_symbol_error_during_carrier_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_symbol_error_during_carrier_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_symbol_error_during_carrier_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_symbol_error_during_carrier_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_mac_control_frames_transmitted_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_transmitted_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_mac_control_frames_transmitted_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_transmitted_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_mac_control_frames_received_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_received_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_mac_control_frames_received_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_mac_control_frames_received_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_unsupported_opcodes_received_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_unsupported_opcodes_received_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_unsupported_opcodes_received_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_unsupported_opcodes_received_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_pause_mac_ctrl_frames_received_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_received_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_pause_mac_ctrl_frames_received_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_received_low_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_pause_mac_ctrl_frames_transmitted_high = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_transmitted_high_get(outbox);
        ppcnt_reg->counter_set.eth_802_3_cntrs_grp_data_layout.a_pause_mac_ctrl_frames_transmitted_low = mlxsw_reg_ppcnt_counter_set_eth_802_3_cntrs_grp_data_layout_a_pause_mac_ctrl_frames_transmitted_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_RFC_2863_COUNTERS_E:
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_in_octets_high = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_in_octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_in_octets_low = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_in_octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_in_ucast_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_in_ucast_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_in_ucast_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_in_ucast_pkts_low_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_in_discards_high = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_in_discards_high_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_in_discards_low = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_in_discards_low_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_in_errors_high = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_in_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_in_errors_low = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_in_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_in_unknown_protos_high = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_in_unknown_protos_high_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_in_unknown_protos_low = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_in_unknown_protos_low_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_out_octets_high = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_out_octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_out_octets_low = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_out_octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_out_ucast_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_out_ucast_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_out_ucast_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_out_ucast_pkts_low_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_out_discards_high = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_out_discards_high_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_out_discards_low = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_out_discards_low_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_out_errors_high = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_out_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_out_errors_low = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_out_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_in_multicast_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_in_multicast_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_in_multicast_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_in_multicast_pkts_low_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_in_broadcast_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_in_broadcast_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_in_broadcast_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_in_broadcast_pkts_low_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_out_multicast_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_out_multicast_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_out_multicast_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_out_multicast_pkts_low_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_out_broadcast_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_out_broadcast_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_2863_cntrs_grp_data_layout.if_out_broadcast_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_2863_cntrs_grp_data_layout_if_out_broadcast_pkts_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_RFC_2819_COUNTERS_E:
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_drop_events_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_drop_events_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_drop_events_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_drop_events_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_octets_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_octets_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_broadcast_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_broadcast_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_broadcast_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_broadcast_pkts_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_multicast_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_multicast_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_multicast_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_multicast_pkts_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_crc_align_errors_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_crc_align_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_crc_align_errors_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_crc_align_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_undersize_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_undersize_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_undersize_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_undersize_pkts_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_oversize_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_oversize_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_oversize_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_oversize_pkts_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_fragments_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_fragments_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_fragments_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_fragments_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_jabbers_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_jabbers_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_jabbers_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_jabbers_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_collisions_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_collisions_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_collisions_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_collisions_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts64octets_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts64octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts64octets_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts64octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts65to127octets_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts65to127octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts65to127octets_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts65to127octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts128to255octets_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts128to255octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts128to255octets_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts128to255octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts256to511octets_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts256to511octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts256to511octets_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts256to511octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts512to1023octets_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts512to1023octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts512to1023octets_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts512to1023octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts1024to1518octets_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1024to1518octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts1024to1518octets_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1024to1518octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts1519to2047octets_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1519to2047octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts1519to2047octets_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts1519to2047octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts2048to4095octets_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts2048to4095octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts2048to4095octets_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts2048to4095octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts4096to8191octets_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts4096to8191octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts4096to8191octets_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts4096to8191octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts8192to10239octets_high = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts8192to10239octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts8192to10239octets_low = mlxsw_reg_ppcnt_counter_set_eth_2819_cntrs_grp_data_layout_ether_stats_pkts8192to10239octets_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_RFC_3635_COUNTERS_E:
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_alignment_errors_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_alignment_errors_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_alignment_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_fcs_errors_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_fcs_errors_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_fcs_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_single_collision_frames_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_single_collision_frames_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_single_collision_frames_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_multiple_collision_frames_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_multiple_collision_frames_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_multiple_collision_frames_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_sqe_test_errors_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_sqe_test_errors_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_sqe_test_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_deferred_transmissions_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_deferred_transmissions_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_deferred_transmissions_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_late_collisions_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_late_collisions_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_late_collisions_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_excessive_collisions_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_excessive_collisions_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_excessive_collisions_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_transmit_errors_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_transmit_errors_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_transmit_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_carrier_sense_errors_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_carrier_sense_errors_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_carrier_sense_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_frame_too_longs_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_frame_too_longs_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_frame_too_longs_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_receive_errors_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_receive_errors_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_internal_mac_receive_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_symbol_errors_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_symbol_errors_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3stats_symbol_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3control_in_unknown_opcodes_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3control_in_unknown_opcodes_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3control_in_unknown_opcodes_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3in_pause_frames_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3in_pause_frames_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3in_pause_frames_low_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3out_pause_frames_high = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_high_get(outbox);
        ppcnt_reg->counter_set.eth_3635_cntrs_grp_data_layout.dot3out_pause_frames_low = mlxsw_reg_ppcnt_counter_set_eth_3635_cntrs_grp_data_layout_dot3out_pause_frames_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_ETHERNET_EXTENDED_COUNTERS_E:
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.port_transmit_wait_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_port_transmit_wait_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.port_transmit_wait_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_port_transmit_wait_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.ecn_marked_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_ecn_marked_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.ecn_marked_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_ecn_marked_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.no_buffer_discard_mc_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_no_buffer_discard_mc_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.no_buffer_discard_mc_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_no_buffer_discard_mc_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.rx_ebp_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_rx_ebp_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.rx_ebp_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_rx_ebp_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_ebp_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_ebp_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_ebp_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_ebp_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.rx_buffer_almost_full_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_rx_buffer_almost_full_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.rx_buffer_almost_full_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_rx_buffer_almost_full_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.rx_buffer_full_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_rx_buffer_full_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.rx_buffer_full_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_rx_buffer_full_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.rx_icrc_encapsulated_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_rx_icrc_encapsulated_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.rx_icrc_encapsulated_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_rx_icrc_encapsulated_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts64octets_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts64octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts64octets_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts64octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts65to127octets_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts65to127octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts65to127octets_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts65to127octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts128to255octets_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts128to255octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts128to255octets_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts128to255octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts256to511octets_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts256to511octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts256to511octets_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts256to511octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts512to1023octets_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts512to1023octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts512to1023octets_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts512to1023octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts1024to1518octets_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1024to1518octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts1024to1518octets_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1024to1518octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts1519to2047octets_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1519to2047octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts1519to2047octets_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts1519to2047octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts2048to4095octets_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts2048to4095octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts2048to4095octets_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts2048to4095octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts4096to8191octets_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts4096to8191octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts4096to8191octets_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts4096to8191octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts8192to10239octets_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts8192to10239octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts8192to10239octets_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_stats_pkts8192to10239octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.ece_marked_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_ece_marked_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.ece_marked_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_ece_marked_low_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_int_cksm_err_high = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_int_cksm_err_high_get(outbox);
        ppcnt_reg->counter_set.eth_extended_cntrs_grp_data_layout.tx_int_cksm_err_low = mlxsw_reg_ppcnt_counter_set_eth_extended_cntrs_grp_data_layout_tx_int_cksm_err_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_ETHERNET_DISCARD_COUNTERS_E:
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.ingress_general_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_ingress_general_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.ingress_general_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_ingress_general_low_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.ingress_policy_engine_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_ingress_policy_engine_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.ingress_policy_engine_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_ingress_policy_engine_low_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.ingress_vlan_membership_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_ingress_vlan_membership_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.ingress_vlan_membership_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_ingress_vlan_membership_low_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.ingress_tag_frame_type_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_ingress_tag_frame_type_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.ingress_tag_frame_type_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_ingress_tag_frame_type_low_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.egress_vlan_membership_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_egress_vlan_membership_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.egress_vlan_membership_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_egress_vlan_membership_low_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.loopback_filter_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_loopback_filter_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.loopback_filter_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_loopback_filter_low_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.egress_general_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_egress_general_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.egress_general_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_egress_general_low_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.egress_hoq_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_egress_hoq_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.egress_hoq_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_egress_hoq_low_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.port_isolation_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_port_isolation_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.port_isolation_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_port_isolation_low_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.egress_policy_engine_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_egress_policy_engine_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.egress_policy_engine_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_egress_policy_engine_low_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.ingress_tx_link_down_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_ingress_tx_link_down_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.ingress_tx_link_down_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_ingress_tx_link_down_low_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.egress_stp_filter_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_egress_stp_filter_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.egress_stp_filter_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_egress_stp_filter_low_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.egress_hoq_stall_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_egress_hoq_stall_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.egress_hoq_stall_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_egress_hoq_stall_low_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.egress_sll_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_egress_sll_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.egress_sll_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_egress_sll_low_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.ingress_discard_all_high = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_ingress_discard_all_high_get(outbox);
        ppcnt_reg->counter_set.eth_discard_cntrs_grp.ingress_discard_all_low = mlxsw_reg_ppcnt_counter_set_eth_discard_cntrs_grp_ingress_discard_all_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_LINK_LEVEL_RETRANSMISSION_COUNTERS_E:
        ppcnt_reg->counter_set.link_level_retrans_cntr_grp_data.llr_rx_cells_high = mlxsw_reg_ppcnt_counter_set_link_level_retrans_cntr_grp_data_llr_rx_cells_high_get(outbox);
        ppcnt_reg->counter_set.link_level_retrans_cntr_grp_data.llr_rx_cells_low = mlxsw_reg_ppcnt_counter_set_link_level_retrans_cntr_grp_data_llr_rx_cells_low_get(outbox);
        ppcnt_reg->counter_set.link_level_retrans_cntr_grp_data.llr_rx_error_high = mlxsw_reg_ppcnt_counter_set_link_level_retrans_cntr_grp_data_llr_rx_error_high_get(outbox);
        ppcnt_reg->counter_set.link_level_retrans_cntr_grp_data.llr_rx_error_low = mlxsw_reg_ppcnt_counter_set_link_level_retrans_cntr_grp_data_llr_rx_error_low_get(outbox);
        ppcnt_reg->counter_set.link_level_retrans_cntr_grp_data.llr_rx_crc_error_high = mlxsw_reg_ppcnt_counter_set_link_level_retrans_cntr_grp_data_llr_rx_crc_error_high_get(outbox);
        ppcnt_reg->counter_set.link_level_retrans_cntr_grp_data.llr_rx_crc_error_low = mlxsw_reg_ppcnt_counter_set_link_level_retrans_cntr_grp_data_llr_rx_crc_error_low_get(outbox);
        ppcnt_reg->counter_set.link_level_retrans_cntr_grp_data.llr_tx_cells_high = mlxsw_reg_ppcnt_counter_set_link_level_retrans_cntr_grp_data_llr_tx_cells_high_get(outbox);
        ppcnt_reg->counter_set.link_level_retrans_cntr_grp_data.llr_tx_cells_low = mlxsw_reg_ppcnt_counter_set_link_level_retrans_cntr_grp_data_llr_tx_cells_low_get(outbox);
        ppcnt_reg->counter_set.link_level_retrans_cntr_grp_data.llr_tx_ret_cells_high = mlxsw_reg_ppcnt_counter_set_link_level_retrans_cntr_grp_data_llr_tx_ret_cells_high_get(outbox);
        ppcnt_reg->counter_set.link_level_retrans_cntr_grp_data.llr_tx_ret_cells_low = mlxsw_reg_ppcnt_counter_set_link_level_retrans_cntr_grp_data_llr_tx_ret_cells_low_get(outbox);
        ppcnt_reg->counter_set.link_level_retrans_cntr_grp_data.llr_tx_ret_events_high = mlxsw_reg_ppcnt_counter_set_link_level_retrans_cntr_grp_data_llr_tx_ret_events_high_get(outbox);
        ppcnt_reg->counter_set.link_level_retrans_cntr_grp_data.llr_tx_ret_events_low = mlxsw_reg_ppcnt_counter_set_link_level_retrans_cntr_grp_data_llr_tx_ret_events_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_PER_PRIORITY_COUNTERS_E:
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_octets_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_octets_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_uc_frames_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_uc_frames_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_uc_frames_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_uc_frames_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_mc_frames_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_mc_frames_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_mc_frames_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_mc_frames_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_bc_frames_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_bc_frames_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_bc_frames_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_bc_frames_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_frames_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_frames_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_frames_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_frames_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.tx_octets_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_tx_octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.tx_octets_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_tx_octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.tx_uc_frames_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_tx_uc_frames_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.tx_uc_frames_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_tx_uc_frames_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.tx_mc_frames_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_tx_mc_frames_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.tx_mc_frames_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_tx_mc_frames_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.tx_bc_frames_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_tx_bc_frames_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.tx_bc_frames_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_tx_bc_frames_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.tx_frames_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_tx_frames_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.tx_frames_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_tx_frames_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_pause_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_pause_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_pause_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_pause_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_pause_duration_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_pause_duration_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_pause_duration_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_pause_duration_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.tx_pause_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_tx_pause_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.tx_pause_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_tx_pause_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.tx_pause_duration_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_tx_pause_duration_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.tx_pause_duration_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_tx_pause_duration_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_pause_transition_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_pause_transition_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_pause_transition_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_pause_transition_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_discards_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_discards_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.rx_discards_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_rx_discards_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.device_stall_minor_watermark_cnt_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_device_stall_minor_watermark_cnt_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.device_stall_minor_watermark_cnt_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_device_stall_minor_watermark_cnt_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.device_stall_critical_watermark_cnt_high = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_device_stall_critical_watermark_cnt_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_prio_grp_data_layout.device_stall_critical_watermark_cnt_low = mlxsw_reg_ppcnt_counter_set_eth_per_prio_grp_data_layout_device_stall_critical_watermark_cnt_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_PER_TRAFFIC_CLASS_COUNTERS_E:
        ppcnt_reg->counter_set.eth_per_traffic_class_layout.transmit_queue_high = mlxsw_reg_ppcnt_counter_set_eth_per_traffic_class_layout_transmit_queue_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_traffic_class_layout.transmit_queue_low = mlxsw_reg_ppcnt_counter_set_eth_per_traffic_class_layout_transmit_queue_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_traffic_class_layout.no_buffer_discard_uc_high = mlxsw_reg_ppcnt_counter_set_eth_per_traffic_class_layout_no_buffer_discard_uc_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_traffic_class_layout.no_buffer_discard_uc_low = mlxsw_reg_ppcnt_counter_set_eth_per_traffic_class_layout_no_buffer_discard_uc_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_PHYSICAL_LAYER_COUNTERS_E:
        ppcnt_reg->counter_set.phys_layer_cntrs.time_since_last_clear_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_time_since_last_clear_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.time_since_last_clear_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_time_since_last_clear_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.symbol_errors_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_symbol_errors_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.symbol_errors_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_symbol_errors_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.sync_headers_errors_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_sync_headers_errors_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.sync_headers_errors_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_sync_headers_errors_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.edpl_bip_errors_lane0_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_edpl_bip_errors_lane0_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.edpl_bip_errors_lane0_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_edpl_bip_errors_lane0_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.edpl_bip_errors_lane1_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_edpl_bip_errors_lane1_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.edpl_bip_errors_lane1_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_edpl_bip_errors_lane1_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.edpl_bip_errors_lane2_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_edpl_bip_errors_lane2_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.edpl_bip_errors_lane2_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_edpl_bip_errors_lane2_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.edpl_bip_errors_lane3_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_edpl_bip_errors_lane3_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.edpl_bip_errors_lane3_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_edpl_bip_errors_lane3_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane0_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane0_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane0_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane0_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane1_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane1_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane1_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane1_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane2_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane2_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane2_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane2_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane3_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane3_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane3_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_corrected_blocks_lane3_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane0_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane0_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane0_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane0_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane1_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane1_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane1_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane1_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane2_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane2_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane2_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane2_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane3_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane3_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane3_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_fc_fec_uncorrectable_blocks_lane3_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_blocks_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_blocks_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_blocks_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_blocks_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_uncorrectable_blocks_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_uncorrectable_blocks_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_uncorrectable_blocks_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_uncorrectable_blocks_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_no_errors_blocks_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_no_errors_blocks_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_no_errors_blocks_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_no_errors_blocks_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_single_error_blocks_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_single_error_blocks_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_single_error_blocks_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_single_error_blocks_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_total_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_total_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_total_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_total_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane0_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane0_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane0_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane0_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane1_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane1_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane1_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane1_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane2_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane2_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane2_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane2_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane3_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane3_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane3_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane3_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.link_down_events = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_link_down_events_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.successful_recovery_events = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_successful_recovery_events_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane4_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane4_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane4_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane4_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane5_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane5_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane5_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane5_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane6_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane6_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane6_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane6_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane7_high = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane7_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane7_low = mlxsw_reg_ppcnt_counter_set_phys_layer_cntrs_rs_fec_corrected_symbols_lane7_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_PER_TRAFFIC_CLASS_CONGESTION_COUNTERS_E:
        ppcnt_reg->counter_set.eth_per_traffic_class_cong_layout.wred_discard_high = mlxsw_reg_ppcnt_counter_set_eth_per_traffic_class_cong_layout_wred_discard_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_traffic_class_cong_layout.wred_discard_low = mlxsw_reg_ppcnt_counter_set_eth_per_traffic_class_cong_layout_wred_discard_low_get(outbox);
        ppcnt_reg->counter_set.eth_per_traffic_class_cong_layout.ecn_marked_tc_high = mlxsw_reg_ppcnt_counter_set_eth_per_traffic_class_cong_layout_ecn_marked_tc_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_traffic_class_cong_layout.ecn_marked_tc_low = mlxsw_reg_ppcnt_counter_set_eth_per_traffic_class_cong_layout_ecn_marked_tc_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_PER_RECEIVE_BUFFER_COUNTERS_E:
        ppcnt_reg->counter_set.eth_per_receive_buffer_grp.rx_no_buffer_discard_uc_high = mlxsw_reg_ppcnt_counter_set_eth_per_receive_buffer_grp_rx_no_buffer_discard_uc_high_get(outbox);
        ppcnt_reg->counter_set.eth_per_receive_buffer_grp.rx_no_buffer_discard_uc_low = mlxsw_reg_ppcnt_counter_set_eth_per_receive_buffer_grp_rx_no_buffer_discard_uc_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_PHYSICAL_LAYER_STATISTICAL_COUNTERS_E:
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.time_since_last_clear_high = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_time_since_last_clear_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.time_since_last_clear_low = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_time_since_last_clear_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_received_bits_high = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_received_bits_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_received_bits_low = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_received_bits_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_symbol_errors_high = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_symbol_errors_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_symbol_errors_low = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_symbol_errors_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_corrected_bits_high = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_corrected_bits_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_corrected_bits_low = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_corrected_bits_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane0_high = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane0_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane0_low = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane0_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane1_high = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane1_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane1_low = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane1_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane2_high = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane2_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane2_low = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane2_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane3_high = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane3_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane3_low = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane3_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane4_high = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane4_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane4_low = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane4_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane5_high = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane5_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane5_low = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane5_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane6_high = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane6_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane6_low = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane6_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane7_high = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane7_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane7_low = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_raw_errors_lane7_low_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_coef = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_coef_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.effective_ber_magnitude = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_effective_ber_magnitude_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.effective_ber_coef = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_effective_ber_coef_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.symbol_ber_magnitude = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_symbol_ber_magnitude_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.symbol_fec_ber_coef = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_symbol_fec_ber_coef_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane0 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane0_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane0 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane0_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane1 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane1_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane1 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane1_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane2 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane2_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane2 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane2_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane3 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane3_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane3 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane3_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane4 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane4_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane4 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane4_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane5 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane5_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane5 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane5_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane6 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane6_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane6 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane6_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane7 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_magnitude_lane7_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane7 = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_raw_ber_coef_lane7_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_effective_errors_high = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_effective_errors_high_get(outbox);
        ppcnt_reg->counter_set.phys_layer_stat_cntrs.phy_effective_errors_low = mlxsw_reg_ppcnt_counter_set_phys_layer_stat_cntrs_phy_effective_errors_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_OUT_OF_BAND_PORT_COUNTERS_E:
        ppcnt_reg->counter_set.eth_oob_port_cntrs.if_in_ucast_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_if_in_ucast_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.if_in_ucast_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_if_in_ucast_pkts_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.if_in_octets_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_if_in_octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.if_in_octets_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_if_in_octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.if_in_discards_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_if_in_discards_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.if_in_discards_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_if_in_discards_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.if_in_errors_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_if_in_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.if_in_errors_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_if_in_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.ether_stats_crc_align_errors_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_ether_stats_crc_align_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.ether_stats_crc_align_errors_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_ether_stats_crc_align_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.ether_stats_undersize_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_ether_stats_undersize_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.ether_stats_undersize_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_ether_stats_undersize_pkts_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.ether_stats_oversize_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_ether_stats_oversize_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.ether_stats_oversize_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_ether_stats_oversize_pkts_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.dot3stats_symbol_errors_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_dot3stats_symbol_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.dot3stats_symbol_errors_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_dot3stats_symbol_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.dot3in_pause_frames_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_dot3in_pause_frames_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.dot3in_pause_frames_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_dot3in_pause_frames_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.dot3control_in_unknown_opcodes_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_dot3control_in_unknown_opcodes_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.dot3control_in_unknown_opcodes_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_dot3control_in_unknown_opcodes_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.if_out_ucast_pkts_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_if_out_ucast_pkts_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.if_out_ucast_pkts_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_if_out_ucast_pkts_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.if_out_octets_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_if_out_octets_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.if_out_octets_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_if_out_octets_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.dot3out_pause_frames_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_dot3out_pause_frames_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.dot3out_pause_frames_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_dot3out_pause_frames_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.if_out_errors_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_if_out_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.if_out_errors_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_if_out_errors_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.phy_time_since_last_clear_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_phy_time_since_last_clear_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.phy_time_since_last_clear_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_phy_time_since_last_clear_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.phy_received_bits_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_phy_received_bits_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.phy_received_bits_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_phy_received_bits_low_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.phy_symbol_errors_high = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_phy_symbol_errors_high_get(outbox);
        ppcnt_reg->counter_set.eth_oob_port_cntrs.phy_symbol_errors_low = mlxsw_reg_ppcnt_counter_set_eth_oob_port_cntrs_phy_symbol_errors_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_INFINIBAND_PORT_COUNTERS_E:
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.symbol_error_counter = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_symbol_error_counter_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.link_error_recovery_counter = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_link_error_recovery_counter_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.link_downed_counter = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_link_downed_counter_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.port_rcv_errors = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_port_rcv_errors_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.port_rcv_remote_physical_errors = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.port_rcv_switch_relay_errors = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.port_xmit_discards = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_port_xmit_discards_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.port_xmit_constraint_errors = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_port_xmit_constraint_errors_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.port_rcv_constraint_errors = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_port_rcv_constraint_errors_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.local_link_integrity_errors = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_local_link_integrity_errors_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.excessive_buffer_overrun_errors = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.vl_15_dropped = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_vl_15_dropped_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.port_xmit_data = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_port_xmit_data_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.port_rcv_data = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_port_rcv_data_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.port_xmit_pkts = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_port_xmit_pkts_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.port_rcv_pkts = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_port_rcv_pkts_get(outbox);
        ppcnt_reg->counter_set.ib_portcntrs_attribute_grp_data.port_xmit_wait = mlxsw_reg_ppcnt_counter_set_ib_portcntrs_attribute_grp_data_port_xmit_wait_get(outbox);
        break;

    case SXD_PPCNT_GRP_INFINIBAND_EXTENDED_PORT_COUNTERS_E:
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.symbol_error_counter_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_symbol_error_counter_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.symbol_error_counter_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_symbol_error_counter_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.link_error_recovery_counter_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_link_error_recovery_counter_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.link_error_recovery_counter_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_link_error_recovery_counter_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.link_downed_counter_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_link_downed_counter_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.link_downed_counter_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_link_downed_counter_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_errors_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_errors_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_errors_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_errors_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_remote_physical_errors_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_remote_physical_errors_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_switch_relay_errors_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_switch_relay_errors_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_discards_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_discards_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_discards_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_discards_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_constraint_errors_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_constraint_errors_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_constraint_errors_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_constraint_errors_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_constraint_errors_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_constraint_errors_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_constraint_errors_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_constraint_errors_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.local_link_integrity_errors_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_local_link_integrity_errors_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.local_link_integrity_errors_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_local_link_integrity_errors_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.excessive_buffer_overrun_errors_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.excessive_buffer_overrun_errors_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.vl_15_dropped_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_vl_15_dropped_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.vl_15_dropped_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_vl_15_dropped_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_data_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_data_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_data_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_data_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_data_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_data_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_data_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_data_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_pkts_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_pkts_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_pkts_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_pkts_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_pkts_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_pkts_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_pkts_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_rcv_pkts_low_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_wait_high = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_wait_high_get(outbox);
        ppcnt_reg->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_wait_low = mlxsw_reg_ppcnt_counter_set_ib_long_portcntrs_attribute_grp_data_port_xmit_wait_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_PLR_COUNTERS_GROUP_E:
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_rcv_codes_high = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_rcv_codes_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_rcv_codes_low = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_rcv_codes_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_rcv_code_err_high = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_rcv_code_err_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_rcv_code_err_low = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_rcv_code_err_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_rcv_uncorrectable_code_high = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_rcv_uncorrectable_code_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_rcv_uncorrectable_code_low = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_rcv_uncorrectable_code_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_xmit_codes_high = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_xmit_codes_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_xmit_codes_low = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_xmit_codes_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_xmit_retry_codes_high = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_xmit_retry_codes_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_xmit_retry_codes_low = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_xmit_retry_codes_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_xmit_retry_events_high = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_xmit_retry_events_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_xmit_retry_events_low = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_xmit_retry_events_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_sync_events_high = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_sync_events_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_sync_events_low = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_sync_events_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_codes_loss_high = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_codes_loss_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_codes_loss_low = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_codes_loss_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_xmit_retry_events_within_t_sec_max_high = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_xmit_retry_events_within_t_sec_max_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_xmit_retry_events_within_t_sec_max_low = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_xmit_retry_events_within_t_sec_max_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_RS_FEC_HISTOGRAM_GROUP_E:
        for (i = 0; i < SXD_PPCNT_HIST_NUM; i++) {
            ppcnt_reg->counter_set.ppcnt_rs_fec_histograms_counters.hist[i] = mlxsw_reg_ppcnt_counter_set_ppcnt_rs_fec_histograms_counters_hist_get(outbox, i);
        }
        break;

    case SXD_PPCNT_GRP_USR_XSR_PHYSICAL_LAYER_COUNTERS_GROUP_E:
        ppcnt_reg->counter_set.usr_xsr_physical_layer.time_since_last_clear_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_time_since_last_clear_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.time_since_last_clear_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_time_since_last_clear_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane0_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane0_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane0_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane0_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane1_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane1_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane1_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane1_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane2_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane2_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane2_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane2_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane3_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane3_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane3_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane3_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane4_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane4_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane4_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane4_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane5_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane5_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane5_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane5_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane6_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane6_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane6_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane6_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane7_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane7_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane7_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_corrected_blocks_lane7_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane0_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane0_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane0_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane0_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane1_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane1_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane1_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane1_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane2_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane2_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane2_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane2_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane3_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane3_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane3_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane3_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane4_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane4_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane4_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane4_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane5_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane5_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane5_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane5_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane6_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane6_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane6_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane6_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane7_high = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane7_high_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane7_low = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_fc_fec_uncorrectable_blocks_lane7_low_get(outbox);
        ppcnt_reg->counter_set.usr_xsr_physical_layer.link_down_events = mlxsw_reg_ppcnt_counter_set_usr_xsr_physical_layer_link_down_events_get(outbox);
        break;

    case SXD_PPCNT_GRP_INFINIBAND_PKTS_COUNTERS_E:
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.time_since_last_clear_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_time_since_last_clear_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.time_since_last_clear_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_time_since_last_clear_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_unicast_xmit_pkts_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_unicast_xmit_pkts_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_unicast_xmit_pkts_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_unicast_xmit_pkts_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_unicast_rcv_pkts_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_unicast_rcv_pkts_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_unicast_rcv_pkts_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_unicast_rcv_pkts_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.sync_header_error_counter_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_sync_header_error_counter_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.sync_header_error_counter_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_sync_header_error_counter_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_local_physical_errors_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_local_physical_errors_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_local_physical_errors_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_local_physical_errors_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_malformed_packet_errors_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_malformed_packet_errors_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_malformed_packet_errors_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_malformed_packet_errors_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_buffer_overrun_errors_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_buffer_overrun_errors_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_buffer_overrun_errors_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_buffer_overrun_errors_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_dlid_mapping_errors_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_dlid_mapping_errors_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_dlid_mapping_errors_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_dlid_mapping_errors_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_vl_mapping_errors_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_vl_mapping_errors_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_vl_mapping_errors_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_vl_mapping_errors_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_looping_errors_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_looping_errors_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_looping_errors_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_looping_errors_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_inactive_discards_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_inactive_discards_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_inactive_discards_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_inactive_discards_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_neighbor_mtu_discards_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_neighbor_mtu_discards_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_packets_counter.port_neighbor_mtu_discards_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_packets_counter_port_neighbor_mtu_discards_low_get(outbox);
        break;

    case SXD_PPCNT_GRP_INFINIBAND_GENERAL_COUNTERS_E:
        ppcnt_reg->counter_set.ppcnt_infiniband_general_counter.port_rcv_data_qword_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_general_counter_port_rcv_data_qword_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_general_counter.port_rcv_data_qword_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_general_counter_port_rcv_data_qword_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_general_counter.port_xmit_data_qword_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_general_counter_port_xmit_data_qword_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_general_counter.port_xmit_data_qword_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_general_counter_port_xmit_data_qword_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_general_counter.rq_general_error_high = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_general_counter_rq_general_error_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_infiniband_general_counter.rq_general_error_low = mlxsw_reg_ppcnt_counter_set_ppcnt_infiniband_general_counter_rq_general_error_low_get(outbox);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}
EXPORT_SYMBOL(__PPCNT_decode);

int sx_ACCESS_REG_PPCNT(struct sx_dev *dev, struct ku_access_ppcnt_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PPCNT_LEN >> 2) + 1;

    if (MLXSW_PPCNT_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPCNT_encode,
                                  __PPCNT_decode,
                                  reg_len_dword,
                                  &reg_data->ppcnt_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPCNT);

int sx_EMAD_ACCESS_REG_PPCNT(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ppcnt_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PPCNT_LEN >> 2) + 1;

    if (MLXSW_PPCNT_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PPCNT_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PPCNT_encode,
                                     __PPCNT_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PPCNT);

/************************************************
* MDIR
***********************************************/
int __MDIR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mdir_reg *mdir_reg = (struct ku_mdir_reg*)ku_reg;

    ((void)mdir_reg);

    return 0;
}

int __MDIR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mdir_reg *mdir_reg = (struct ku_mdir_reg*)ku_reg;
    uint32_t i = 0;

    for (i = 0; i < SXD_MDIR_DEVICE_ID_NUM; i++) {
        mdir_reg->device_id[i] = mlxsw_reg_mdir_device_id_get(outbox, i);
    }


    return 0;
}
EXPORT_SYMBOL(__MDIR_decode);

int sx_ACCESS_REG_MDIR(struct sx_dev *dev, struct ku_access_mdir_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MDIR_LEN >> 2) + 1;

    if (MLXSW_MDIR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MDIR_encode,
                                  __MDIR_decode,
                                  reg_len_dword,
                                  &reg_data->mdir_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MDIR);

int sx_EMAD_ACCESS_REG_MDIR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mdir_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MDIR_LEN >> 2) + 1;

    if (MLXSW_MDIR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MDIR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MDIR_encode,
                                     __MDIR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MDIR);

/************************************************
* SPZR
***********************************************/
int __SPZR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_spzr_reg *spzr_reg = (struct ku_spzr_reg*)ku_reg;

    mlxsw_reg_spzr_swid_set(inbox, spzr_reg->swid);
    mlxsw_reg_spzr_router_entity_set(inbox, spzr_reg->router_entity);
    mlxsw_reg_spzr_cm2_set(inbox, spzr_reg->cm2);
    mlxsw_reg_spzr_ndm_set(inbox, spzr_reg->ndm);
    mlxsw_reg_spzr_enh_sw_p0_mask_set(inbox, spzr_reg->enh_sw_p0_mask);
    mlxsw_reg_spzr_cm_set(inbox, spzr_reg->cm);
    mlxsw_reg_spzr_vk_set(inbox, spzr_reg->vk);
    mlxsw_reg_spzr_mp_set(inbox, spzr_reg->mp);
    mlxsw_reg_spzr_sig_set(inbox, spzr_reg->sig);
    mlxsw_reg_spzr_ng_set(inbox, spzr_reg->ng);
    mlxsw_reg_spzr_g0_set(inbox, spzr_reg->g0);
    mlxsw_reg_spzr_enh_sw_p0_set(inbox, spzr_reg->enh_sw_p0);
    mlxsw_reg_spzr_capability_mask_set(inbox, spzr_reg->capability_mask);
    mlxsw_reg_spzr_system_image_guid_h_set(inbox, spzr_reg->system_image_guid_h);
    mlxsw_reg_spzr_system_image_guid_l_set(inbox, spzr_reg->system_image_guid_l);
    mlxsw_reg_spzr_guid0_h_set(inbox, spzr_reg->guid0_h);
    mlxsw_reg_spzr_guid0_l_set(inbox, spzr_reg->guid0_l);
    mlxsw_reg_spzr_node_guid_h_set(inbox, spzr_reg->node_guid_h);
    mlxsw_reg_spzr_node_guid_l_set(inbox, spzr_reg->node_guid_l);
    mlxsw_reg_spzr_capability_mask2_set(inbox, spzr_reg->capability_mask2);
    mlxsw_reg_spzr_node_description_memcpy_to(inbox, (char *)spzr_reg->node_description);


    return 0;
}

int __SPZR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_spzr_reg *spzr_reg = (struct ku_spzr_reg*)ku_reg;

    spzr_reg->swid = mlxsw_reg_spzr_swid_get(outbox);
    spzr_reg->router_entity = mlxsw_reg_spzr_router_entity_get(outbox);
    spzr_reg->enh_sw_p0 = mlxsw_reg_spzr_enh_sw_p0_get(outbox);
    spzr_reg->capability_mask = mlxsw_reg_spzr_capability_mask_get(outbox);
    spzr_reg->system_image_guid_h = mlxsw_reg_spzr_system_image_guid_h_get(outbox);
    spzr_reg->system_image_guid_l = mlxsw_reg_spzr_system_image_guid_l_get(outbox);
    spzr_reg->guid0_h = mlxsw_reg_spzr_guid0_h_get(outbox);
    spzr_reg->guid0_l = mlxsw_reg_spzr_guid0_l_get(outbox);
    spzr_reg->node_guid_h = mlxsw_reg_spzr_node_guid_h_get(outbox);
    spzr_reg->node_guid_l = mlxsw_reg_spzr_node_guid_l_get(outbox);
    spzr_reg->capability_mask2 = mlxsw_reg_spzr_capability_mask2_get(outbox);
    spzr_reg->max_pkey = mlxsw_reg_spzr_max_pkey_get(outbox);
    mlxsw_reg_spzr_node_description_memcpy_from(outbox, (char *)spzr_reg->node_description);


    return 0;
}
EXPORT_SYMBOL(__SPZR_decode);

int sx_ACCESS_REG_SPZR(struct sx_dev *dev, struct ku_access_spzr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_SPZR_LEN >> 2) + 1;

    if (MLXSW_SPZR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SPZR_encode,
                                  __SPZR_decode,
                                  reg_len_dword,
                                  &reg_data->spzr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SPZR);

int sx_EMAD_ACCESS_REG_SPZR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_spzr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_SPZR_LEN >> 2) + 1;

    if (MLXSW_SPZR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_SPZR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __SPZR_encode,
                                     __SPZR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_SPZR);

/************************************************
* MTCAP
***********************************************/
int __MTCAP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtcap_reg *mtcap_reg = (struct ku_mtcap_reg*)ku_reg;

    mlxsw_reg_mtcap_slot_index_set(inbox, mtcap_reg->slot_index);


    return 0;
}

int __MTCAP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtcap_reg *mtcap_reg = (struct ku_mtcap_reg*)ku_reg;

    mtcap_reg->slot_index = mlxsw_reg_mtcap_slot_index_get(outbox);
    mtcap_reg->sensor_count = mlxsw_reg_mtcap_sensor_count_get(outbox);
    mtcap_reg->internal_sensor_count = mlxsw_reg_mtcap_internal_sensor_count_get(outbox);
    mtcap_reg->sensor_map = mlxsw_reg_mtcap_sensor_map_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MTCAP_decode);

int sx_ACCESS_REG_MTCAP(struct sx_dev *dev, struct ku_access_mtcap_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MTCAP_LEN >> 2) + 1;

    if (MLXSW_MTCAP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTCAP_encode,
                                  __MTCAP_decode,
                                  reg_len_dword,
                                  &reg_data->mtcap_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTCAP);

int sx_EMAD_ACCESS_REG_MTCAP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtcap_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MTCAP_LEN >> 2) + 1;

    if (MLXSW_MTCAP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MTCAP_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MTCAP_encode,
                                     __MTCAP_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MTCAP);

/************************************************
* MDFCR
***********************************************/
int __MDFCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mdfcr_reg *mdfcr_reg = (struct ku_mdfcr_reg*)ku_reg;

    mlxsw_reg_mdfcr_device_type_set(inbox, mdfcr_reg->device_type);
    mlxsw_reg_mdfcr_all_set(inbox, mdfcr_reg->all);
    mlxsw_reg_mdfcr_device_index_set(inbox, mdfcr_reg->device_index);


    return 0;
}

int __MDFCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mdfcr_reg *mdfcr_reg = (struct ku_mdfcr_reg*)ku_reg;

    mdfcr_reg->device_type = mlxsw_reg_mdfcr_device_type_get(outbox);
    mdfcr_reg->all = mlxsw_reg_mdfcr_all_get(outbox);
    mdfcr_reg->device_index = mlxsw_reg_mdfcr_device_index_get(outbox);
    mdfcr_reg->fw_status = mlxsw_reg_mdfcr_fw_status_get(outbox);
    mdfcr_reg->first_fw_status_device = mlxsw_reg_mdfcr_first_fw_status_device_get(outbox);
    mdfcr_reg->expected_fw_version = mlxsw_reg_mdfcr_expected_fw_version_get(outbox);
    mdfcr_reg->fw_version = mlxsw_reg_mdfcr_fw_version_get(outbox);
    mdfcr_reg->build_id = mlxsw_reg_mdfcr_build_id_get(outbox);
    mdfcr_reg->major = mlxsw_reg_mdfcr_major_get(outbox);
    mdfcr_reg->minor = mlxsw_reg_mdfcr_minor_get(outbox);
    mdfcr_reg->error_id = mlxsw_reg_mdfcr_error_id_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MDFCR_decode);

int sx_ACCESS_REG_MDFCR(struct sx_dev *dev, struct ku_access_mdfcr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MDFCR_LEN >> 2) + 1;

    if (MLXSW_MDFCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MDFCR_encode,
                                  __MDFCR_decode,
                                  reg_len_dword,
                                  &reg_data->mdfcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MDFCR);

int sx_EMAD_ACCESS_REG_MDFCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mdfcr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MDFCR_LEN >> 2) + 1;

    if (MLXSW_MDFCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MDFCR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MDFCR_encode,
                                     __MDFCR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MDFCR);

/************************************************
* PAOS
***********************************************/
int __PAOS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_paos_reg *paos_reg = (struct ku_paos_reg*)ku_reg;

    mlxsw_reg_paos_swid_set(inbox, paos_reg->swid);
    mlxsw_reg_paos_local_port_set(inbox, paos_reg->local_port);
    mlxsw_reg_paos_pnat_set(inbox, paos_reg->pnat);
    mlxsw_reg_paos_lp_msb_set(inbox, paos_reg->lp_msb);
    mlxsw_reg_paos_admin_status_set(inbox, paos_reg->admin_status);
    mlxsw_reg_paos_ase_set(inbox, paos_reg->ase);
    mlxsw_reg_paos_ee_set(inbox, paos_reg->ee);
    mlxsw_reg_paos_en_sleep_set(inbox, paos_reg->en_sleep);
    mlxsw_reg_paos_fd_set(inbox, paos_reg->fd);
    mlxsw_reg_paos_e_set(inbox, paos_reg->e);


    return 0;
}

int __PAOS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_paos_reg *paos_reg = (struct ku_paos_reg*)ku_reg;

    paos_reg->swid = mlxsw_reg_paos_swid_get(outbox);
    paos_reg->local_port = mlxsw_reg_paos_local_port_get(outbox);
    paos_reg->pnat = mlxsw_reg_paos_pnat_get(outbox);
    paos_reg->lp_msb = mlxsw_reg_paos_lp_msb_get(outbox);
    paos_reg->admin_status = mlxsw_reg_paos_admin_status_get(outbox);
    paos_reg->oper_status = mlxsw_reg_paos_oper_status_get(outbox);
    paos_reg->sleep_cap = mlxsw_reg_paos_sleep_cap_get(outbox);
    paos_reg->en_sleep = mlxsw_reg_paos_en_sleep_get(outbox);
    paos_reg->fd = mlxsw_reg_paos_fd_get(outbox);
    paos_reg->e = mlxsw_reg_paos_e_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__PAOS_decode);

int sx_ACCESS_REG_PAOS(struct sx_dev *dev, struct ku_access_paos_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PAOS_LEN >> 2) + 1;

    if (MLXSW_PAOS_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PAOS_encode,
                                  __PAOS_decode,
                                  reg_len_dword,
                                  &reg_data->paos_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PAOS);

int sx_EMAD_ACCESS_REG_PAOS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_paos_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PAOS_LEN >> 2) + 1;

    if (MLXSW_PAOS_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PAOS_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PAOS_encode,
                                     __PAOS_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PAOS);

/************************************************
* MTUTC
***********************************************/
int __MTUTC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtutc_reg *mtutc_reg = (struct ku_mtutc_reg*)ku_reg;

    mlxsw_reg_mtutc_operation_set(inbox, mtutc_reg->operation);
    mlxsw_reg_mtutc_freq_adjustment_set(inbox, mtutc_reg->freq_adjustment);
    mlxsw_reg_mtutc_utc_sec_set(inbox, mtutc_reg->utc_sec);
    mlxsw_reg_mtutc_utc_nsec_set(inbox, mtutc_reg->utc_nsec);
    mlxsw_reg_mtutc_time_adjustment_set(inbox, mtutc_reg->time_adjustment);


    return 0;
}

int __MTUTC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtutc_reg *mtutc_reg = (struct ku_mtutc_reg*)ku_reg;

    mtutc_reg->operation = mlxsw_reg_mtutc_operation_get(outbox);
    mtutc_reg->freq_adjustment = mlxsw_reg_mtutc_freq_adjustment_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MTUTC_decode);

int sx_ACCESS_REG_MTUTC(struct sx_dev *dev, struct ku_access_mtutc_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MTUTC_LEN >> 2) + 1;

    if (MLXSW_MTUTC_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTUTC_encode,
                                  __MTUTC_decode,
                                  reg_len_dword,
                                  &reg_data->mtutc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTUTC);

int sx_EMAD_ACCESS_REG_MTUTC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtutc_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MTUTC_LEN >> 2) + 1;

    if (MLXSW_MTUTC_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MTUTC_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MTUTC_encode,
                                     __MTUTC_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MTUTC);

/************************************************
* PTYS
***********************************************/
int __PTYS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ptys_reg *ptys_reg = (struct ku_ptys_reg*)ku_reg;

    mlxsw_reg_ptys_an_disable_admin_set(inbox, ptys_reg->an_disable_admin);
    mlxsw_reg_ptys_force_tx_aba_param_set(inbox, ptys_reg->force_tx_aba_param);
    mlxsw_reg_ptys_local_port_set(inbox, ptys_reg->local_port);
    mlxsw_reg_ptys_pnat_set(inbox, ptys_reg->pnat);
    mlxsw_reg_ptys_lp_msb_set(inbox, ptys_reg->lp_msb);
    mlxsw_reg_ptys_port_type_set(inbox, ptys_reg->port_type);
    mlxsw_reg_ptys_proto_mask_set(inbox, ptys_reg->proto_mask);
    mlxsw_reg_ptys_ext_eth_proto_admin_set(inbox, ptys_reg->ext_eth_proto_admin);
    mlxsw_reg_ptys_eth_proto_admin_set(inbox, ptys_reg->eth_proto_admin);
    mlxsw_reg_ptys_ib_link_width_admin_set(inbox, ptys_reg->ib_link_width_admin);
    mlxsw_reg_ptys_ib_proto_admin_set(inbox, ptys_reg->ib_proto_admin);
    mlxsw_reg_ptys_force_lt_frames_admin_set(inbox, ptys_reg->force_lt_frames_admin);
    mlxsw_reg_ptys_eth_proto_lp_legacy_valid_set(inbox, ptys_reg->eth_proto_lp_legacy_valid);


    return 0;
}

int __PTYS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ptys_reg *ptys_reg = (struct ku_ptys_reg*)ku_reg;

    ptys_reg->reserved_high = mlxsw_reg_ptys_reserved_high_get(outbox);
    ptys_reg->an_disable_admin = mlxsw_reg_ptys_an_disable_admin_get(outbox);
    ptys_reg->an_disable_cap = mlxsw_reg_ptys_an_disable_cap_get(outbox);
    ptys_reg->force_tx_aba_param = mlxsw_reg_ptys_force_tx_aba_param_get(outbox);
    ptys_reg->local_port = mlxsw_reg_ptys_local_port_get(outbox);
    ptys_reg->pnat = mlxsw_reg_ptys_pnat_get(outbox);
    ptys_reg->lp_msb = mlxsw_reg_ptys_lp_msb_get(outbox);
    ptys_reg->port_type = mlxsw_reg_ptys_port_type_get(outbox);
    ptys_reg->proto_mask = mlxsw_reg_ptys_proto_mask_get(outbox);
    ptys_reg->an_status = mlxsw_reg_ptys_an_status_get(outbox);
    ptys_reg->max_port_rate = mlxsw_reg_ptys_max_port_rate_get(outbox);
    ptys_reg->data_rate_oper = mlxsw_reg_ptys_data_rate_oper_get(outbox);
    ptys_reg->ext_eth_proto_capability = mlxsw_reg_ptys_ext_eth_proto_capability_get(outbox);
    ptys_reg->eth_proto_capability = mlxsw_reg_ptys_eth_proto_capability_get(outbox);
    ptys_reg->ib_link_width_capability = mlxsw_reg_ptys_ib_link_width_capability_get(outbox);
    ptys_reg->ib_proto_capability = mlxsw_reg_ptys_ib_proto_capability_get(outbox);
    ptys_reg->ext_eth_proto_admin = mlxsw_reg_ptys_ext_eth_proto_admin_get(outbox);
    ptys_reg->eth_proto_admin = mlxsw_reg_ptys_eth_proto_admin_get(outbox);
    ptys_reg->ib_link_width_admin = mlxsw_reg_ptys_ib_link_width_admin_get(outbox);
    ptys_reg->ib_proto_admin = mlxsw_reg_ptys_ib_proto_admin_get(outbox);
    ptys_reg->ext_eth_proto_oper = mlxsw_reg_ptys_ext_eth_proto_oper_get(outbox);
    ptys_reg->eth_proto_oper = mlxsw_reg_ptys_eth_proto_oper_get(outbox);
    ptys_reg->ib_link_width_oper = mlxsw_reg_ptys_ib_link_width_oper_get(outbox);
    ptys_reg->ib_proto_oper = mlxsw_reg_ptys_ib_proto_oper_get(outbox);
    ptys_reg->eth_proto_lp_valid = mlxsw_reg_ptys_eth_proto_lp_valid_get(outbox);
    ptys_reg->force_lt_frames_cap = mlxsw_reg_ptys_force_lt_frames_cap_get(outbox);
    ptys_reg->force_lt_frames_admin = mlxsw_reg_ptys_force_lt_frames_admin_get(outbox);
    ptys_reg->eth_proto_lp_legacy_valid = mlxsw_reg_ptys_eth_proto_lp_legacy_valid_get(outbox);
    ptys_reg->connector_type = mlxsw_reg_ptys_connector_type_get(outbox);
    ptys_reg->eth_proto_lp_advertise = mlxsw_reg_ptys_eth_proto_lp_advertise_get(outbox);
    ptys_reg->eth_proto_lp_legacy_advertise = mlxsw_reg_ptys_eth_proto_lp_legacy_advertise_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__PTYS_decode);

int sx_ACCESS_REG_PTYS(struct sx_dev *dev, struct ku_access_ptys_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PTYS_LEN >> 2) + 1;

    if (MLXSW_PTYS_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PTYS_encode,
                                  __PTYS_decode,
                                  reg_len_dword,
                                  &reg_data->ptys_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PTYS);

int sx_EMAD_ACCESS_REG_PTYS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ptys_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PTYS_LEN >> 2) + 1;

    if (MLXSW_PTYS_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PTYS_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PTYS_encode,
                                     __PTYS_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PTYS);

/************************************************
* PPLR
***********************************************/
int __PPLR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pplr_reg *pplr_reg = (struct ku_pplr_reg*)ku_reg;

    mlxsw_reg_pplr_local_port_set(inbox, pplr_reg->local_port);
    mlxsw_reg_pplr_lp_msb_set(inbox, pplr_reg->lp_msb);
    mlxsw_reg_pplr_op_mod_set(inbox, pplr_reg->op_mod);
    mlxsw_reg_pplr_port_type_set(inbox, pplr_reg->port_type);
    mlxsw_reg_pplr_lb_en_set(inbox, pplr_reg->lb_en);


    return 0;
}

int __PPLR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pplr_reg *pplr_reg = (struct ku_pplr_reg*)ku_reg;

    pplr_reg->local_port = mlxsw_reg_pplr_local_port_get(outbox);
    pplr_reg->lp_msb = mlxsw_reg_pplr_lp_msb_get(outbox);
    pplr_reg->op_mod = mlxsw_reg_pplr_op_mod_get(outbox);
    pplr_reg->port_type = mlxsw_reg_pplr_port_type_get(outbox);
    pplr_reg->lb_cap = mlxsw_reg_pplr_lb_cap_get(outbox);
    pplr_reg->lb_en = mlxsw_reg_pplr_lb_en_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__PPLR_decode);

int sx_ACCESS_REG_PPLR(struct sx_dev *dev, struct ku_access_pplr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PPLR_LEN >> 2) + 1;

    if (MLXSW_PPLR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPLR_encode,
                                  __PPLR_decode,
                                  reg_len_dword,
                                  &reg_data->pplr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPLR);

int sx_EMAD_ACCESS_REG_PPLR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pplr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PPLR_LEN >> 2) + 1;

    if (MLXSW_PPLR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PPLR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PPLR_encode,
                                     __PPLR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PPLR);

/************************************************
* HETT
***********************************************/
int __HETT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_hett_reg *hett_reg = (struct ku_hett_reg*)ku_reg;

    mlxsw_reg_hett_opcode_set(inbox, hett_reg->opcode);
    mlxsw_reg_hett_trap_group_bitmap_set(inbox, hett_reg->trap_group_bitmap);


    return 0;
}

int __HETT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_hett_reg *hett_reg = (struct ku_hett_reg*)ku_reg;

    hett_reg->status = mlxsw_reg_hett_status_get(outbox);
    hett_reg->trap_group_bitmap = mlxsw_reg_hett_trap_group_bitmap_get(outbox);
    hett_reg->trap_group = mlxsw_reg_hett_trap_group_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__HETT_decode);

int sx_ACCESS_REG_HETT(struct sx_dev *dev, struct ku_access_hett_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_HETT_LEN >> 2) + 1;

    if (MLXSW_HETT_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __HETT_encode,
                                  __HETT_decode,
                                  reg_len_dword,
                                  &reg_data->hett_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_HETT);

int sx_EMAD_ACCESS_REG_HETT(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_hett_reg *reg)
{
    u16 reg_len_dword = (MLXSW_HETT_LEN >> 2) + 1;

    if (MLXSW_HETT_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_HETT_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __HETT_encode,
                                     __HETT_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_HETT);

/************************************************
* MTPPST
***********************************************/
int __MTPPST_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtppst_reg *mtppst_reg = (struct ku_mtppst_reg*)ku_reg;

    mlxsw_reg_mtppst_pin_set(inbox, mtppst_reg->pin);


    return 0;
}

int __MTPPST_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtppst_reg *mtppst_reg = (struct ku_mtppst_reg*)ku_reg;

    mtppst_reg->pin = mlxsw_reg_mtppst_pin_get(outbox);
    mtppst_reg->timestamp_msb = mlxsw_reg_mtppst_timestamp_msb_get(outbox);
    mtppst_reg->timestamp_lsb = mlxsw_reg_mtppst_timestamp_lsb_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MTPPST_decode);

int sx_ACCESS_REG_MTPPST(struct sx_dev *dev, struct ku_access_mtppst_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MTPPST_LEN >> 2) + 1;

    if (MLXSW_MTPPST_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTPPST_encode,
                                  __MTPPST_decode,
                                  reg_len_dword,
                                  &reg_data->mtppst_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTPPST);

int sx_EMAD_ACCESS_REG_MTPPST(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtppst_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MTPPST_LEN >> 2) + 1;

    if (MLXSW_MTPPST_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MTPPST_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MTPPST_encode,
                                     __MTPPST_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MTPPST);

/************************************************
* IBFMR
***********************************************/
int __IBFMR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ibfmr_reg *ibfmr_reg = (struct ku_ibfmr_reg*)ku_reg;

    ((void)ibfmr_reg);

    return 0;
}

int __IBFMR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ibfmr_reg *ibfmr_reg = (struct ku_ibfmr_reg*)ku_reg;

    ibfmr_reg->atm_v = mlxsw_reg_ibfmr_atm_v_get(outbox);
    ibfmr_reg->attribute_id = mlxsw_reg_ibfmr_attribute_id_get(outbox);
    ibfmr_reg->attribute_modifier = mlxsw_reg_ibfmr_attribute_modifier_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__IBFMR_decode);

int sx_ACCESS_REG_IBFMR(struct sx_dev *dev, struct ku_access_ibfmr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_IBFMR_LEN >> 2) + 1;

    if (MLXSW_IBFMR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __IBFMR_encode,
                                  __IBFMR_decode,
                                  reg_len_dword,
                                  &reg_data->ibfmr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_IBFMR);

int sx_EMAD_ACCESS_REG_IBFMR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ibfmr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_IBFMR_LEN >> 2) + 1;

    if (MLXSW_IBFMR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_IBFMR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __IBFMR_encode,
                                     __IBFMR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_IBFMR);

/************************************************
* MSEES
***********************************************/
int __MSEES_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_msees_reg *msees_reg = (struct ku_msees_reg*)ku_reg;

    mlxsw_reg_msees_local_port_set(inbox, msees_reg->local_port);
    mlxsw_reg_msees_pnat_set(inbox, msees_reg->pnat);
    mlxsw_reg_msees_lp_msb_set(inbox, msees_reg->lp_msb);
    mlxsw_reg_msees_field_select_set(inbox, msees_reg->field_select);
    mlxsw_reg_msees_admin_status_set(inbox, msees_reg->admin_status);
    mlxsw_reg_msees_admin_freq_measure_set(inbox, msees_reg->admin_freq_measure);


    return 0;
}

int __MSEES_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_msees_reg *msees_reg = (struct ku_msees_reg*)ku_reg;

    msees_reg->local_port = mlxsw_reg_msees_local_port_get(outbox);
    msees_reg->pnat = mlxsw_reg_msees_pnat_get(outbox);
    msees_reg->lp_msb = mlxsw_reg_msees_lp_msb_get(outbox);
    msees_reg->admin_status = mlxsw_reg_msees_admin_status_get(outbox);
    msees_reg->oper_status = mlxsw_reg_msees_oper_status_get(outbox);
    msees_reg->ho_acq = mlxsw_reg_msees_ho_acq_get(outbox);
    msees_reg->admin_freq_measure = mlxsw_reg_msees_admin_freq_measure_get(outbox);
    msees_reg->oper_freq_measure = mlxsw_reg_msees_oper_freq_measure_get(outbox);
    msees_reg->failure_reason = mlxsw_reg_msees_failure_reason_get(outbox);
    msees_reg->frequency_diff = mlxsw_reg_msees_frequency_diff_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MSEES_decode);

int sx_ACCESS_REG_MSEES(struct sx_dev *dev, struct ku_access_msees_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MSEES_LEN >> 2) + 1;

    if (MLXSW_MSEES_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MSEES_encode,
                                  __MSEES_decode,
                                  reg_len_dword,
                                  &reg_data->msees_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MSEES);

int sx_EMAD_ACCESS_REG_MSEES(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_msees_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MSEES_LEN >> 2) + 1;

    if (MLXSW_MSEES_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MSEES_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MSEES_encode,
                                     __MSEES_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MSEES);

/************************************************
* SGCR
***********************************************/
int __SGCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sgcr_reg *sgcr_reg = (struct ku_sgcr_reg*)ku_reg;

    mlxsw_reg_sgcr_llb_set(inbox, sgcr_reg->llb);
    mlxsw_reg_sgcr_activity_dis_set(inbox, sgcr_reg->activity_dis);
    mlxsw_reg_sgcr_lag_lookup_pgt_base_set(inbox, sgcr_reg->lag_lookup_pgt_base);


    return 0;
}

int __SGCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sgcr_reg *sgcr_reg = (struct ku_sgcr_reg*)ku_reg;

    sgcr_reg->llb = mlxsw_reg_sgcr_llb_get(outbox);
    sgcr_reg->activity_dis = mlxsw_reg_sgcr_activity_dis_get(outbox);
    sgcr_reg->lag_lookup_pgt_base = mlxsw_reg_sgcr_lag_lookup_pgt_base_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__SGCR_decode);

int sx_ACCESS_REG_SGCR(struct sx_dev *dev, struct ku_access_sgcr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_SGCR_LEN >> 2) + 1;

    if (MLXSW_SGCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SGCR_encode,
                                  __SGCR_decode,
                                  reg_len_dword,
                                  &reg_data->sgcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SGCR);

int sx_EMAD_ACCESS_REG_SGCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sgcr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_SGCR_LEN >> 2) + 1;

    if (MLXSW_SGCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_SGCR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __SGCR_encode,
                                     __SGCR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_SGCR);

/************************************************
* MPNHLFE
***********************************************/
int __MPNHLFE_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mpnhlfe_reg *mpnhlfe_reg = (struct ku_mpnhlfe_reg*)ku_reg;

    mlxsw_reg_mpnhlfe_ca_set(inbox, mpnhlfe_reg->ca);
    mlxsw_reg_mpnhlfe_v_set(inbox, mpnhlfe_reg->v);
    mlxsw_reg_mpnhlfe_nhlfe_ptr_set(inbox, mpnhlfe_reg->nhlfe_ptr);
    mlxsw_reg_mpnhlfe_forward_action_set(inbox, mpnhlfe_reg->forward_action);
    mlxsw_reg_mpnhlfe_trap_action_set(inbox, mpnhlfe_reg->trap_action);
    mlxsw_reg_mpnhlfe_trap_id_set(inbox, mpnhlfe_reg->trap_id);
    mlxsw_reg_mpnhlfe_counter_set_type_set(inbox, mpnhlfe_reg->counter_set_type);
    mlxsw_reg_mpnhlfe_counter_index_set(inbox, mpnhlfe_reg->counter_index);
    switch (mpnhlfe_reg->forward_action) {
    case SXD_MPNHLFE_FORWARD_ACTION_FORWARD_TO_ETHERNET_E:
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_dscp_rw_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.dscp_rw);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_uecn_exp_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.uecn_exp);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_usp_dscp_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.usp_dscp);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_usp_exp_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.usp_exp);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_exp_rw_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.exp_rw);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_set_exp_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.set_exp);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_exp_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.exp);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_tqos_profile_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.tqos_profile);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_bos_check_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.bos_check);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_label_action_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.label_action);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_label_id_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.label_id);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_dmac_memcpy_to(inbox, (char *)mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.dmac);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_egress_router_interface_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.egress_router_interface);
        break;

    case SXD_MPNHLFE_FORWARD_ACTION_FORWARD_TO_IP_ROUTER_E:
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_dscp_rw_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.dscp_rw);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_uecn_exp_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.uecn_exp);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_usp_dscp_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.usp_dscp);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_usp_exp_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.usp_exp);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_tqos_profile_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.tqos_profile);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_irifv_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.irifv);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_irif_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.irif);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_erifv_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.erifv);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_egress_router_interface_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.egress_router_interface);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_cbset_select_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.cbset_select);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_cbset_val_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.cbset_val);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_cbset_mask_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.cbset_mask);
        break;

    case SXD_MPNHLFE_FORWARD_ACTION_CONTINUE_LOOKUPS_E:
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_dscp_rw_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.dscp_rw);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_uecn_exp_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.uecn_exp);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_usp_dscp_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.usp_dscp);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_usp_exp_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.usp_exp);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_tqos_profile_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.tqos_profile);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_bos_check_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.bos_check);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_irifv_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.irifv);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_irif_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.irif);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_erifv_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.erifv);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_egress_router_interface_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.egress_router_interface);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_cbset_select_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.cbset_select);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_cbset_val_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.cbset_val);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_cbset_mask_set(inbox, mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.cbset_mask);
        break;

    case SXD_MPNHLFE_FORWARD_ACTION_NEXT_NHLFE_E:
        mlxsw_reg_mpnhlfe_nhlfe_parameters_next_nhlfe_exp_rw_set(inbox, mpnhlfe_reg->nhlfe_parameters.next_nhlfe.exp_rw);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_next_nhlfe_set_exp_set(inbox, mpnhlfe_reg->nhlfe_parameters.next_nhlfe.set_exp);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_next_nhlfe_exp_set(inbox, mpnhlfe_reg->nhlfe_parameters.next_nhlfe.exp);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_next_nhlfe_label_action_set(inbox, mpnhlfe_reg->nhlfe_parameters.next_nhlfe.label_action);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_next_nhlfe_label_id_set(inbox, mpnhlfe_reg->nhlfe_parameters.next_nhlfe.label_id);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_next_nhlfe_next_nhlfe_set(inbox, mpnhlfe_reg->nhlfe_parameters.next_nhlfe.next_nhlfe);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_next_nhlfe_ecmp_size_set(inbox, mpnhlfe_reg->nhlfe_parameters.next_nhlfe.ecmp_size);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}

int __MPNHLFE_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mpnhlfe_reg *mpnhlfe_reg = (struct ku_mpnhlfe_reg*)ku_reg;

    mpnhlfe_reg->ca = mlxsw_reg_mpnhlfe_ca_get(outbox);
    mpnhlfe_reg->a = mlxsw_reg_mpnhlfe_a_get(outbox);
    mpnhlfe_reg->v = mlxsw_reg_mpnhlfe_v_get(outbox);
    mpnhlfe_reg->nhlfe_ptr = mlxsw_reg_mpnhlfe_nhlfe_ptr_get(outbox);
    mpnhlfe_reg->forward_action = mlxsw_reg_mpnhlfe_forward_action_get(outbox);
    mpnhlfe_reg->trap_action = mlxsw_reg_mpnhlfe_trap_action_get(outbox);
    mpnhlfe_reg->trap_id = mlxsw_reg_mpnhlfe_trap_id_get(outbox);
    mpnhlfe_reg->counter_set_type = mlxsw_reg_mpnhlfe_counter_set_type_get(outbox);
    mpnhlfe_reg->counter_index = mlxsw_reg_mpnhlfe_counter_index_get(outbox);
    switch (mpnhlfe_reg->forward_action) {
    case SXD_MPNHLFE_FORWARD_ACTION_FORWARD_TO_ETHERNET_E:
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.dscp_rw = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_dscp_rw_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.uecn_exp = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_uecn_exp_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.usp_dscp = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_usp_dscp_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.usp_exp = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_usp_exp_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.exp_rw = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_exp_rw_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.set_exp = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_set_exp_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.exp = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_exp_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.tqos_profile = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_tqos_profile_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.bos_check = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_bos_check_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.label_action = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_label_action_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.label_id = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_label_id_get(outbox);
        mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_dmac_memcpy_from(outbox, (char *)mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.dmac);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_eth.egress_router_interface = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_eth_egress_router_interface_get(outbox);
        break;

    case SXD_MPNHLFE_FORWARD_ACTION_FORWARD_TO_IP_ROUTER_E:
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.dscp_rw = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_dscp_rw_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.uecn_exp = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_uecn_exp_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.usp_dscp = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_usp_dscp_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.usp_exp = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_usp_exp_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.tqos_profile = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_tqos_profile_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.irifv = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_irifv_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.irif = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_irif_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.erifv = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_erifv_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.egress_router_interface = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_egress_router_interface_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.cbset_select = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_cbset_select_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.cbset_val = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_cbset_val_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_iprouter.cbset_mask = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_iprouter_cbset_mask_get(outbox);
        break;

    case SXD_MPNHLFE_FORWARD_ACTION_CONTINUE_LOOKUPS_E:
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.dscp_rw = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_dscp_rw_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.uecn_exp = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_uecn_exp_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.usp_dscp = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_usp_dscp_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.usp_exp = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_usp_exp_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.tqos_profile = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_tqos_profile_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.bos_check = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_bos_check_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.irifv = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_irifv_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.irif = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_irif_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.erifv = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_erifv_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.egress_router_interface = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_egress_router_interface_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.cbset_select = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_cbset_select_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.cbset_val = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_cbset_val_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.mpnhlfe_param_lookups.cbset_mask = mlxsw_reg_mpnhlfe_nhlfe_parameters_mpnhlfe_param_lookups_cbset_mask_get(outbox);
        break;

    case SXD_MPNHLFE_FORWARD_ACTION_NEXT_NHLFE_E:
        mpnhlfe_reg->nhlfe_parameters.next_nhlfe.exp_rw = mlxsw_reg_mpnhlfe_nhlfe_parameters_next_nhlfe_exp_rw_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.next_nhlfe.set_exp = mlxsw_reg_mpnhlfe_nhlfe_parameters_next_nhlfe_set_exp_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.next_nhlfe.exp = mlxsw_reg_mpnhlfe_nhlfe_parameters_next_nhlfe_exp_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.next_nhlfe.label_action = mlxsw_reg_mpnhlfe_nhlfe_parameters_next_nhlfe_label_action_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.next_nhlfe.label_id = mlxsw_reg_mpnhlfe_nhlfe_parameters_next_nhlfe_label_id_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.next_nhlfe.next_nhlfe = mlxsw_reg_mpnhlfe_nhlfe_parameters_next_nhlfe_next_nhlfe_get(outbox);
        mpnhlfe_reg->nhlfe_parameters.next_nhlfe.ecmp_size = mlxsw_reg_mpnhlfe_nhlfe_parameters_next_nhlfe_ecmp_size_get(outbox);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}
EXPORT_SYMBOL(__MPNHLFE_decode);

int sx_ACCESS_REG_MPNHLFE(struct sx_dev *dev, struct ku_access_mpnhlfe_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MPNHLFE_LEN >> 2) + 1;

    if (MLXSW_MPNHLFE_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MPNHLFE_encode,
                                  __MPNHLFE_decode,
                                  reg_len_dword,
                                  &reg_data->mpnhlfe_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MPNHLFE);

int sx_EMAD_ACCESS_REG_MPNHLFE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mpnhlfe_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MPNHLFE_LEN >> 2) + 1;

    if (MLXSW_MPNHLFE_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MPNHLFE_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MPNHLFE_encode,
                                     __MPNHLFE_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MPNHLFE);

/************************************************
* MTEWE
***********************************************/
int __MTEWE_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtewe_reg *mtewe_reg = (struct ku_mtewe_reg*)ku_reg;

    mlxsw_reg_mtewe_slot_index_set(inbox, mtewe_reg->slot_index);


    return 0;
}

int __MTEWE_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtewe_reg *mtewe_reg = (struct ku_mtewe_reg*)ku_reg;
    uint32_t i = 0;

    mtewe_reg->last_sensor = mlxsw_reg_mtewe_last_sensor_get(outbox);
    mtewe_reg->slot_index = mlxsw_reg_mtewe_slot_index_get(outbox);
    mtewe_reg->sensor_count = mlxsw_reg_mtewe_sensor_count_get(outbox);
    for (i = 0; i < SXD_MTEWE_SENSOR_WARNING_NUM; i++) {
        mtewe_reg->sensor_warning[i] = mlxsw_reg_mtewe_sensor_warning_get(outbox, i);
    }


    return 0;
}
EXPORT_SYMBOL(__MTEWE_decode);

int sx_ACCESS_REG_MTEWE(struct sx_dev *dev, struct ku_access_mtewe_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MTEWE_LEN >> 2) + 1;

    if (MLXSW_MTEWE_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTEWE_encode,
                                  __MTEWE_decode,
                                  reg_len_dword,
                                  &reg_data->mtewe_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTEWE);

int sx_EMAD_ACCESS_REG_MTEWE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtewe_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MTEWE_LEN >> 2) + 1;

    if (MLXSW_MTEWE_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MTEWE_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MTEWE_encode,
                                     __MTEWE_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MTEWE);

/************************************************
* MTPSPU
***********************************************/
int __MTPSPU_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtpspu_reg *mtpspu_reg = (struct ku_mtpspu_reg*)ku_reg;

    mlxsw_reg_mtpspu_message_type_set(inbox, mtpspu_reg->message_type);


    return 0;
}

int __MTPSPU_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtpspu_reg *mtpspu_reg = (struct ku_mtpspu_reg*)ku_reg;

    mtpspu_reg->message_type = mlxsw_reg_mtpspu_message_type_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MTPSPU_decode);

int sx_ACCESS_REG_MTPSPU(struct sx_dev *dev, struct ku_access_mtpspu_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MTPSPU_LEN >> 2) + 1;

    if (MLXSW_MTPSPU_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTPSPU_encode,
                                  __MTPSPU_decode,
                                  reg_len_dword,
                                  &reg_data->mtpspu_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTPSPU);

int sx_EMAD_ACCESS_REG_MTPSPU(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtpspu_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MTPSPU_LEN >> 2) + 1;

    if (MLXSW_MTPSPU_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MTPSPU_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MTPSPU_encode,
                                     __MTPSPU_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MTPSPU);

/************************************************
* SLSIR
***********************************************/
int __SLSIR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_slsir_reg *slsir_reg = (struct ku_slsir_reg*)ku_reg;

    mlxsw_reg_slsir_local_port_set(inbox, slsir_reg->local_port);
    mlxsw_reg_slsir_pnat_set(inbox, slsir_reg->pnat);
    mlxsw_reg_slsir_lp_msb_set(inbox, slsir_reg->lp_msb);
    mlxsw_reg_slsir_lane_set(inbox, slsir_reg->lane);
    mlxsw_reg_slsir_port_type_set(inbox, slsir_reg->port_type);


    return 0;
}

int __SLSIR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_slsir_reg *slsir_reg = (struct ku_slsir_reg*)ku_reg;

    slsir_reg->status = mlxsw_reg_slsir_status_get(outbox);
    slsir_reg->version = mlxsw_reg_slsir_version_get(outbox);
    slsir_reg->local_port = mlxsw_reg_slsir_local_port_get(outbox);
    slsir_reg->pnat = mlxsw_reg_slsir_pnat_get(outbox);
    slsir_reg->lp_msb = mlxsw_reg_slsir_lp_msb_get(outbox);
    slsir_reg->lane = mlxsw_reg_slsir_lane_get(outbox);
    slsir_reg->port_type = mlxsw_reg_slsir_port_type_get(outbox);
    slsir_reg->nop_rsunf_error = mlxsw_reg_slsir_nop_rsunf_error_get(outbox);
    slsir_reg->nop_rsovf_error = mlxsw_reg_slsir_nop_rsovf_error_get(outbox);
    slsir_reg->nop_dsunf_error = mlxsw_reg_slsir_nop_dsunf_error_get(outbox);
    slsir_reg->nop_dsovf_error = mlxsw_reg_slsir_nop_dsovf_error_get(outbox);
    slsir_reg->peq_adc_overload = mlxsw_reg_slsir_peq_adc_overload_get(outbox);
    slsir_reg->feq_adc_overload = mlxsw_reg_slsir_feq_adc_overload_get(outbox);
    slsir_reg->cdr_error = mlxsw_reg_slsir_cdr_error_get(outbox);
    slsir_reg->imem_chksm_error = mlxsw_reg_slsir_imem_chksm_error_get(outbox);
    slsir_reg->rx_ugl_state = mlxsw_reg_slsir_rx_ugl_state_get(outbox);
    slsir_reg->rx_eom_ugl_state = mlxsw_reg_slsir_rx_eom_ugl_state_get(outbox);
    slsir_reg->rx_cal_ugl_state = mlxsw_reg_slsir_rx_cal_ugl_state_get(outbox);
    slsir_reg->rx_eq_ugl_state = mlxsw_reg_slsir_rx_eq_ugl_state_get(outbox);
    slsir_reg->tx_ugl_state = mlxsw_reg_slsir_tx_ugl_state_get(outbox);
    slsir_reg->recovery_retries_cnt = mlxsw_reg_slsir_recovery_retries_cnt_get(outbox);
    slsir_reg->imem_loading_retries = mlxsw_reg_slsir_imem_loading_retries_get(outbox);
    slsir_reg->sd_hits_cnt = mlxsw_reg_slsir_sd_hits_cnt_get(outbox);
    slsir_reg->sd_iter_cnt = mlxsw_reg_slsir_sd_iter_cnt_get(outbox);
    slsir_reg->rd_iter_cnt = mlxsw_reg_slsir_rd_iter_cnt_get(outbox);
    slsir_reg->ae_state = mlxsw_reg_slsir_ae_state_get(outbox);
    slsir_reg->rx_init_abort_cnt = mlxsw_reg_slsir_rx_init_abort_cnt_get(outbox);
    slsir_reg->rx_init_done_cnt = mlxsw_reg_slsir_rx_init_done_cnt_get(outbox);
    slsir_reg->cdr_abort_cnt = mlxsw_reg_slsir_cdr_abort_cnt_get(outbox);
    slsir_reg->cdr_done_cnt = mlxsw_reg_slsir_cdr_done_cnt_get(outbox);
    slsir_reg->cal_abort_cnt = mlxsw_reg_slsir_cal_abort_cnt_get(outbox);
    slsir_reg->cal_done_cnt = mlxsw_reg_slsir_cal_done_cnt_get(outbox);
    slsir_reg->eq_abort_cnt = mlxsw_reg_slsir_eq_abort_cnt_get(outbox);
    slsir_reg->eq_done_cnt = mlxsw_reg_slsir_eq_done_cnt_get(outbox);
    slsir_reg->eom_abort_cnt = mlxsw_reg_slsir_eom_abort_cnt_get(outbox);
    slsir_reg->eom_done_cnt = mlxsw_reg_slsir_eom_done_cnt_get(outbox);
    slsir_reg->err_ind_it_3 = mlxsw_reg_slsir_err_ind_it_3_get(outbox);
    slsir_reg->err_ind_it_2 = mlxsw_reg_slsir_err_ind_it_2_get(outbox);
    slsir_reg->err_ind_it_1 = mlxsw_reg_slsir_err_ind_it_1_get(outbox);
    slsir_reg->err_ind_it_0 = mlxsw_reg_slsir_err_ind_it_0_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__SLSIR_decode);

int sx_ACCESS_REG_SLSIR(struct sx_dev *dev, struct ku_access_slsir_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_SLSIR_LEN >> 2) + 1;

    if (MLXSW_SLSIR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SLSIR_encode,
                                  __SLSIR_decode,
                                  reg_len_dword,
                                  &reg_data->slsir_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SLSIR);

int sx_EMAD_ACCESS_REG_SLSIR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_slsir_reg *reg)
{
    u16 reg_len_dword = (MLXSW_SLSIR_LEN >> 2) + 1;

    if (MLXSW_SLSIR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_SLSIR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __SLSIR_encode,
                                     __SLSIR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_SLSIR);

/************************************************
* PPAD
***********************************************/
int __PPAD_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppad_reg *ppad_reg = (struct ku_ppad_reg*)ku_reg;

    mlxsw_reg_ppad_single_base_mac_set(inbox, ppad_reg->single_base_mac);
    mlxsw_reg_ppad_pnat_set(inbox, ppad_reg->pnat);
    mlxsw_reg_ppad_lp_msb_set(inbox, ppad_reg->lp_msb);
    mlxsw_reg_ppad_local_port_set(inbox, ppad_reg->local_port);
    mlxsw_reg_ppad_mac_memcpy_to(inbox, (char *)ppad_reg->mac);


    return 0;
}

int __PPAD_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppad_reg *ppad_reg = (struct ku_ppad_reg*)ku_reg;

    ppad_reg->single_base_mac = mlxsw_reg_ppad_single_base_mac_get(outbox);
    ppad_reg->pnat = mlxsw_reg_ppad_pnat_get(outbox);
    ppad_reg->lp_msb = mlxsw_reg_ppad_lp_msb_get(outbox);
    ppad_reg->local_port = mlxsw_reg_ppad_local_port_get(outbox);
    mlxsw_reg_ppad_mac_memcpy_from(outbox, (char *)ppad_reg->mac);


    return 0;
}
EXPORT_SYMBOL(__PPAD_decode);

int sx_ACCESS_REG_PPAD(struct sx_dev *dev, struct ku_access_ppad_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PPAD_LEN >> 2) + 1;

    if (MLXSW_PPAD_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPAD_encode,
                                  __PPAD_decode,
                                  reg_len_dword,
                                  &reg_data->ppad_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPAD);

int sx_EMAD_ACCESS_REG_PPAD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ppad_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PPAD_LEN >> 2) + 1;

    if (MLXSW_PPAD_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PPAD_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PPAD_encode,
                                     __PPAD_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PPAD);

/************************************************
* MOCS
***********************************************/
int __MOCS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mocs_reg *mocs_reg = (struct ku_mocs_reg*)ku_reg;
    uint32_t i = 0;

    mlxsw_reg_mocs_type_set(inbox, mocs_reg->type);
    mlxsw_reg_mocs_clear_set(inbox, mocs_reg->clear);
    mlxsw_reg_mocs_opcode_set(inbox, mocs_reg->opcode);
    mlxsw_reg_mocs_event_tid_set(inbox, mocs_reg->event_tid);
    switch (mocs_reg->type) {
    case SXD_MOCS_TYPE_PPCNT_SES1_E:
        for (i = 0; i < SXD_MOCS_PORT_MASK_NUM; i++) {
            mlxsw_reg_mocs_entry_mocs_ppcnt_port_mask_set(inbox, i, mocs_reg->entry.mocs_ppcnt.port_mask[i]);
        }
        for (i = 0; i < SXD_MOCS_GRP_MASK_NUM; i++) {
            mlxsw_reg_mocs_entry_mocs_ppcnt_grp_mask_set(inbox, i, mocs_reg->entry.mocs_ppcnt.grp_mask[i]);
        }
        mlxsw_reg_mocs_entry_mocs_ppcnt_tc_mask_set(inbox, mocs_reg->entry.mocs_ppcnt.tc_mask);
        mlxsw_reg_mocs_entry_mocs_ppcnt_prio_mask_set(inbox, mocs_reg->entry.mocs_ppcnt.prio_mask);
        mlxsw_reg_mocs_entry_mocs_ppcnt_rx_buffer_mask_set(inbox, mocs_reg->entry.mocs_ppcnt.rx_buffer_mask);
        for (i = 0; i < SXD_MOCS_GRP_PRF_NUM; i++) {
            mlxsw_reg_mocs_entry_mocs_ppcnt_grp_prf_set(inbox, i, mocs_reg->entry.mocs_ppcnt.grp_prf[i]);
        }
        break;

    case SXD_MOCS_TYPE_MGPCB_E:
        mlxsw_reg_mocs_entry_mocs_mgpcb_flush_set(inbox, mocs_reg->entry.mocs_mgpcb.flush);
        mlxsw_reg_mocs_entry_mocs_mgpcb_num_rec_set(inbox, mocs_reg->entry.mocs_mgpcb.num_rec);
        mlxsw_reg_mocs_entry_mocs_mgpcb_counter_index_base_set(inbox, mocs_reg->entry.mocs_mgpcb.counter_index_base);
        break;

    case SXD_MOCS_TYPE_PBSR_E:
        for (i = 0; i < SXD_MOCS_PORT_MASK_NUM; i++) {
            mlxsw_reg_mocs_entry_mocs_pbsr_port_mask_set(inbox, i, mocs_reg->entry.mocs_pbsr.port_mask[i]);
        }
        break;

    case SXD_MOCS_TYPE_SBSRD_E:
        mlxsw_reg_mocs_entry_mocs_sbsrd_curr_set(inbox, mocs_reg->entry.mocs_sbsrd.curr);
        mlxsw_reg_mocs_entry_mocs_sbsrd_snap_set(inbox, mocs_reg->entry.mocs_sbsrd.snap);
        mlxsw_reg_mocs_entry_mocs_sbsrd_cells_set(inbox, mocs_reg->entry.mocs_sbsrd.cells);
        mlxsw_reg_mocs_entry_mocs_sbsrd_desc_set(inbox, mocs_reg->entry.mocs_sbsrd.desc);
        break;

    case SXD_MOCS_TYPE_CEER_E:
        for (i = 0; i < SXD_MOCS_PORT_MASK_NUM; i++) {
            mlxsw_reg_mocs_entry_mocs_ceer_port_mask_set(inbox, i, mocs_reg->entry.mocs_ceer.port_mask[i]);
        }
        break;

    case SXD_MOCS_TYPE_MAFBI_E:
        mlxsw_reg_mocs_entry_mocs_mafbi_flush_set(inbox, mocs_reg->entry.mocs_mafbi.flush);
        mlxsw_reg_mocs_entry_mocs_mafbi_type_set(inbox, mocs_reg->entry.mocs_mafbi.type);
        mlxsw_reg_mocs_entry_mocs_mafbi_num_rec_set(inbox, mocs_reg->entry.mocs_mafbi.num_rec);
        mlxsw_reg_mocs_entry_mocs_mafbi_counter_index_base_set(inbox, mocs_reg->entry.mocs_mafbi.counter_index_base);
        break;

    case SXD_MOCS_TYPE_MOPCE_E:
        break;

    case SXD_MOCS_TYPE_FSED_E:
        mlxsw_reg_mocs_entry_mocs_fsed_op_set(inbox, mocs_reg->entry.mocs_fsed.op);
        mlxsw_reg_mocs_entry_mocs_fsed_filter_fields_set(inbox, mocs_reg->entry.mocs_fsed.filter_fields);
        mlxsw_reg_mocs_entry_mocs_fsed_group_id_set(inbox, mocs_reg->entry.mocs_fsed.group_id);
        mlxsw_reg_mocs_entry_mocs_fsed_entry_sem_s_set(inbox, mocs_reg->entry.mocs_fsed.entry_sem_s);
        mlxsw_reg_mocs_entry_mocs_fsed_entry_activity_set(inbox, mocs_reg->entry.mocs_fsed.entry_activity);
        mlxsw_reg_mocs_entry_mocs_fsed_entry_partition_id_set(inbox, mocs_reg->entry.mocs_fsed.entry_partition_id);
        mlxsw_reg_mocs_entry_mocs_fsed_num_rec_set(inbox, mocs_reg->entry.mocs_fsed.num_rec);
        mlxsw_reg_mocs_entry_mocs_fsed_nt_set(inbox, mocs_reg->entry.mocs_fsed.nt);
        break;

    case SXD_MOCS_TYPE_USACN_E:
        for (i = 0; i < SXD_MOCS_PORT_MASK_NUM; i++) {
            mlxsw_reg_mocs_entry_mocs_usacn_port_mask_set(inbox, i, mocs_reg->entry.mocs_usacn.port_mask[i]);
        }
        mlxsw_reg_mocs_entry_mocs_usacn_side_set(inbox, mocs_reg->entry.mocs_usacn.side);
        mlxsw_reg_mocs_entry_mocs_usacn_sadb_entry_index_base_set(inbox, mocs_reg->entry.mocs_usacn.sadb_entry_index_base);
        mlxsw_reg_mocs_entry_mocs_usacn_num_rec_set(inbox, mocs_reg->entry.mocs_usacn.num_rec);
        break;

    case SXD_MOCS_TYPE_UTCC_E:
        for (i = 0; i < SXD_MOCS_PORT_MASK_NUM; i++) {
            mlxsw_reg_mocs_entry_mocs_utcc_port_mask_set(inbox, i, mocs_reg->entry.mocs_utcc.port_mask[i]);
        }
        mlxsw_reg_mocs_entry_mocs_utcc_side_set(inbox, mocs_reg->entry.mocs_utcc.side);
        mlxsw_reg_mocs_entry_mocs_utcc_utcam_counter_idx_base_set(inbox, mocs_reg->entry.mocs_utcc.utcam_counter_idx_base);
        mlxsw_reg_mocs_entry_mocs_utcc_num_rec_set(inbox, mocs_reg->entry.mocs_utcc.num_rec);
        break;

    case SXD_MOCS_TYPE_UPCNT_E:
        for (i = 0; i < SXD_MOCS_PORT_MASK_NUM; i++) {
            mlxsw_reg_mocs_entry_mocs_upcnt_port_mask_set(inbox, i, mocs_reg->entry.mocs_upcnt.port_mask[i]);
        }
        break;

    case SXD_MOCS_TYPE_MOFRB_E:
        for (i = 0; i < SXD_MOCS_FLOW_ESTIMATOR_RECORD_NUM; i++) {
            mlxsw_reg_mocs_entry_mocs_mofrb_num_rec_set(inbox, i, mocs_reg->entry.mocs_mofrb.flow_estimator_record[i].num_rec);
            mlxsw_reg_mocs_entry_mocs_mofrb_counter_index_base_set(inbox, i, mocs_reg->entry.mocs_mofrb.flow_estimator_record[i].counter_index_base);
        }
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}

int __MOCS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mocs_reg *mocs_reg = (struct ku_mocs_reg*)ku_reg;
    uint32_t i = 0;

    mocs_reg->type = mlxsw_reg_mocs_type_get(outbox);
    mocs_reg->clear = mlxsw_reg_mocs_clear_get(outbox);
    mocs_reg->status = mlxsw_reg_mocs_status_get(outbox);
    mocs_reg->event_tid = mlxsw_reg_mocs_event_tid_get(outbox);
    switch (mocs_reg->type) {
    case SXD_MOCS_TYPE_PPCNT_SES1_E:
        for (i = 0; i < SXD_MOCS_PORT_MASK_NUM; i++) {
            mocs_reg->entry.mocs_ppcnt.port_mask[i] = mlxsw_reg_mocs_entry_mocs_ppcnt_port_mask_get(outbox, i);
        }
        for (i = 0; i < SXD_MOCS_GRP_MASK_NUM; i++) {
            mocs_reg->entry.mocs_ppcnt.grp_mask[i] = mlxsw_reg_mocs_entry_mocs_ppcnt_grp_mask_get(outbox, i);
        }
        mocs_reg->entry.mocs_ppcnt.tc_mask = mlxsw_reg_mocs_entry_mocs_ppcnt_tc_mask_get(outbox);
        mocs_reg->entry.mocs_ppcnt.prio_mask = mlxsw_reg_mocs_entry_mocs_ppcnt_prio_mask_get(outbox);
        mocs_reg->entry.mocs_ppcnt.rx_buffer_mask = mlxsw_reg_mocs_entry_mocs_ppcnt_rx_buffer_mask_get(outbox);
        for (i = 0; i < SXD_MOCS_GRP_PRF_NUM; i++) {
            mocs_reg->entry.mocs_ppcnt.grp_prf[i] = mlxsw_reg_mocs_entry_mocs_ppcnt_grp_prf_get(outbox, i);
        }
        break;

    case SXD_MOCS_TYPE_MGPCB_E:
        mocs_reg->entry.mocs_mgpcb.flush = mlxsw_reg_mocs_entry_mocs_mgpcb_flush_get(outbox);
        mocs_reg->entry.mocs_mgpcb.num_rec = mlxsw_reg_mocs_entry_mocs_mgpcb_num_rec_get(outbox);
        mocs_reg->entry.mocs_mgpcb.counter_index_base = mlxsw_reg_mocs_entry_mocs_mgpcb_counter_index_base_get(outbox);
        break;

    case SXD_MOCS_TYPE_PBSR_E:
        for (i = 0; i < SXD_MOCS_PORT_MASK_NUM; i++) {
            mocs_reg->entry.mocs_pbsr.port_mask[i] = mlxsw_reg_mocs_entry_mocs_pbsr_port_mask_get(outbox, i);
        }
        break;

    case SXD_MOCS_TYPE_SBSRD_E:
        mocs_reg->entry.mocs_sbsrd.curr = mlxsw_reg_mocs_entry_mocs_sbsrd_curr_get(outbox);
        mocs_reg->entry.mocs_sbsrd.snap = mlxsw_reg_mocs_entry_mocs_sbsrd_snap_get(outbox);
        mocs_reg->entry.mocs_sbsrd.cells = mlxsw_reg_mocs_entry_mocs_sbsrd_cells_get(outbox);
        mocs_reg->entry.mocs_sbsrd.desc = mlxsw_reg_mocs_entry_mocs_sbsrd_desc_get(outbox);
        break;

    case SXD_MOCS_TYPE_CEER_E:
        for (i = 0; i < SXD_MOCS_PORT_MASK_NUM; i++) {
            mocs_reg->entry.mocs_ceer.port_mask[i] = mlxsw_reg_mocs_entry_mocs_ceer_port_mask_get(outbox, i);
        }
        break;

    case SXD_MOCS_TYPE_MAFBI_E:
        mocs_reg->entry.mocs_mafbi.flush = mlxsw_reg_mocs_entry_mocs_mafbi_flush_get(outbox);
        mocs_reg->entry.mocs_mafbi.type = mlxsw_reg_mocs_entry_mocs_mafbi_type_get(outbox);
        mocs_reg->entry.mocs_mafbi.num_rec = mlxsw_reg_mocs_entry_mocs_mafbi_num_rec_get(outbox);
        mocs_reg->entry.mocs_mafbi.counter_index_base = mlxsw_reg_mocs_entry_mocs_mafbi_counter_index_base_get(outbox);
        break;

    case SXD_MOCS_TYPE_MOPCE_E:
        break;

    case SXD_MOCS_TYPE_FSED_E:
        mocs_reg->entry.mocs_fsed.op = mlxsw_reg_mocs_entry_mocs_fsed_op_get(outbox);
        mocs_reg->entry.mocs_fsed.filter_fields = mlxsw_reg_mocs_entry_mocs_fsed_filter_fields_get(outbox);
        mocs_reg->entry.mocs_fsed.group_id = mlxsw_reg_mocs_entry_mocs_fsed_group_id_get(outbox);
        mocs_reg->entry.mocs_fsed.entry_sem_s = mlxsw_reg_mocs_entry_mocs_fsed_entry_sem_s_get(outbox);
        mocs_reg->entry.mocs_fsed.entry_activity = mlxsw_reg_mocs_entry_mocs_fsed_entry_activity_get(outbox);
        mocs_reg->entry.mocs_fsed.entry_partition_id = mlxsw_reg_mocs_entry_mocs_fsed_entry_partition_id_get(outbox);
        mocs_reg->entry.mocs_fsed.num_rec = mlxsw_reg_mocs_entry_mocs_fsed_num_rec_get(outbox);
        mocs_reg->entry.mocs_fsed.nt = mlxsw_reg_mocs_entry_mocs_fsed_nt_get(outbox);
        break;

    case SXD_MOCS_TYPE_USACN_E:
        for (i = 0; i < SXD_MOCS_PORT_MASK_NUM; i++) {
            mocs_reg->entry.mocs_usacn.port_mask[i] = mlxsw_reg_mocs_entry_mocs_usacn_port_mask_get(outbox, i);
        }
        mocs_reg->entry.mocs_usacn.side = mlxsw_reg_mocs_entry_mocs_usacn_side_get(outbox);
        mocs_reg->entry.mocs_usacn.sadb_entry_index_base = mlxsw_reg_mocs_entry_mocs_usacn_sadb_entry_index_base_get(outbox);
        mocs_reg->entry.mocs_usacn.num_rec = mlxsw_reg_mocs_entry_mocs_usacn_num_rec_get(outbox);
        break;

    case SXD_MOCS_TYPE_UTCC_E:
        for (i = 0; i < SXD_MOCS_PORT_MASK_NUM; i++) {
            mocs_reg->entry.mocs_utcc.port_mask[i] = mlxsw_reg_mocs_entry_mocs_utcc_port_mask_get(outbox, i);
        }
        mocs_reg->entry.mocs_utcc.side = mlxsw_reg_mocs_entry_mocs_utcc_side_get(outbox);
        mocs_reg->entry.mocs_utcc.utcam_counter_idx_base = mlxsw_reg_mocs_entry_mocs_utcc_utcam_counter_idx_base_get(outbox);
        mocs_reg->entry.mocs_utcc.num_rec = mlxsw_reg_mocs_entry_mocs_utcc_num_rec_get(outbox);
        break;

    case SXD_MOCS_TYPE_UPCNT_E:
        for (i = 0; i < SXD_MOCS_PORT_MASK_NUM; i++) {
            mocs_reg->entry.mocs_upcnt.port_mask[i] = mlxsw_reg_mocs_entry_mocs_upcnt_port_mask_get(outbox, i);
        }
        break;

    case SXD_MOCS_TYPE_MOFRB_E:
        for (i = 0; i < SXD_MOCS_FLOW_ESTIMATOR_RECORD_NUM; i++) {
            mocs_reg->entry.mocs_mofrb.flow_estimator_record[i].num_rec = mlxsw_reg_mocs_entry_mocs_mofrb_num_rec_get(outbox, i);
            mocs_reg->entry.mocs_mofrb.flow_estimator_record[i].counter_index_base = mlxsw_reg_mocs_entry_mocs_mofrb_counter_index_base_get(outbox, i);
        }
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}
EXPORT_SYMBOL(__MOCS_decode);

int sx_ACCESS_REG_MOCS(struct sx_dev *dev, struct ku_access_mocs_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MOCS_LEN >> 2) + 1;

    if (MLXSW_MOCS_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MOCS_encode,
                                  __MOCS_decode,
                                  reg_len_dword,
                                  &reg_data->mocs_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MOCS);

int sx_EMAD_ACCESS_REG_MOCS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mocs_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MOCS_LEN >> 2) + 1;

    if (MLXSW_MOCS_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MOCS_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MOCS_encode,
                                     __MOCS_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MOCS);

/************************************************
* PLLP
***********************************************/
int __PLLP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pllp_reg *pllp_reg = (struct ku_pllp_reg*)ku_reg;

    mlxsw_reg_pllp_local_port_set(inbox, pllp_reg->local_port);
    mlxsw_reg_pllp_lp_msb_set(inbox, pllp_reg->lp_msb);


    return 0;
}

int __PLLP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pllp_reg *pllp_reg = (struct ku_pllp_reg*)ku_reg;

    pllp_reg->local_port = mlxsw_reg_pllp_local_port_get(outbox);
    pllp_reg->lp_msb = mlxsw_reg_pllp_lp_msb_get(outbox);
    pllp_reg->label_port = mlxsw_reg_pllp_label_port_get(outbox);
    pllp_reg->ipil_stat = mlxsw_reg_pllp_ipil_stat_get(outbox);
    pllp_reg->split_stat = mlxsw_reg_pllp_split_stat_get(outbox);
    pllp_reg->ipil_num = mlxsw_reg_pllp_ipil_num_get(outbox);
    pllp_reg->split_num = mlxsw_reg_pllp_split_num_get(outbox);
    pllp_reg->max_ports_width = mlxsw_reg_pllp_max_ports_width_get(outbox);
    pllp_reg->slot_num = mlxsw_reg_pllp_slot_num_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__PLLP_decode);

int sx_ACCESS_REG_PLLP(struct sx_dev *dev, struct ku_access_pllp_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PLLP_LEN >> 2) + 1;

    if (MLXSW_PLLP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PLLP_encode,
                                  __PLLP_decode,
                                  reg_len_dword,
                                  &reg_data->pllp_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PLLP);

int sx_EMAD_ACCESS_REG_PLLP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pllp_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PLLP_LEN >> 2) + 1;

    if (MLXSW_PLLP_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PLLP_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PLLP_encode,
                                     __PLLP_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PLLP);

/************************************************
* SPAD
***********************************************/
int __SPAD_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_spad_reg *spad_reg = (struct ku_spad_reg*)ku_reg;

    mlxsw_reg_spad_base_mac_memcpy_to(inbox, (char *)spad_reg->base_mac);


    return 0;
}

int __SPAD_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_spad_reg *spad_reg = (struct ku_spad_reg*)ku_reg;

    mlxsw_reg_spad_base_mac_memcpy_from(outbox, (char *)spad_reg->base_mac);


    return 0;
}
EXPORT_SYMBOL(__SPAD_decode);

int sx_ACCESS_REG_SPAD(struct sx_dev *dev, struct ku_access_spad_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_SPAD_LEN >> 2) + 1;

    if (MLXSW_SPAD_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SPAD_encode,
                                  __SPAD_decode,
                                  reg_len_dword,
                                  &reg_data->spad_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SPAD);

int sx_EMAD_ACCESS_REG_SPAD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_spad_reg *reg)
{
    u16 reg_len_dword = (MLXSW_SPAD_LEN >> 2) + 1;

    if (MLXSW_SPAD_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_SPAD_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __SPAD_encode,
                                     __SPAD_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_SPAD);

/************************************************
* SBGCR
***********************************************/
int __SBGCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sbgcr_reg *sbgcr_reg = (struct ku_sbgcr_reg*)ku_reg;

    mlxsw_reg_sbgcr_cong_fp_set(inbox, sbgcr_reg->cong_fp);
    mlxsw_reg_sbgcr_tele_entity_set(inbox, sbgcr_reg->tele_entity);
    mlxsw_reg_sbgcr_hba_set(inbox, sbgcr_reg->hba);


    return 0;
}

int __SBGCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sbgcr_reg *sbgcr_reg = (struct ku_sbgcr_reg*)ku_reg;

    sbgcr_reg->cong_fp = mlxsw_reg_sbgcr_cong_fp_get(outbox);
    sbgcr_reg->tele_entity = mlxsw_reg_sbgcr_tele_entity_get(outbox);
    sbgcr_reg->hba = mlxsw_reg_sbgcr_hba_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__SBGCR_decode);

int sx_ACCESS_REG_SBGCR(struct sx_dev *dev, struct ku_access_sbgcr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_SBGCR_LEN >> 2) + 1;

    if (MLXSW_SBGCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SBGCR_encode,
                                  __SBGCR_decode,
                                  reg_len_dword,
                                  &reg_data->sbgcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SBGCR);

int sx_EMAD_ACCESS_REG_SBGCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sbgcr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_SBGCR_LEN >> 2) + 1;

    if (MLXSW_SBGCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_SBGCR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __SBGCR_encode,
                                     __SBGCR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_SBGCR);

/************************************************
* MCQI
***********************************************/
int __MCQI_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mcqi_reg *mcqi_reg = (struct ku_mcqi_reg*)ku_reg;

    mlxsw_reg_mcqi_read_pending_component_set(inbox, mcqi_reg->read_pending_component);
    mlxsw_reg_mcqi_device_index_set(inbox, mcqi_reg->device_index);
    mlxsw_reg_mcqi_component_index_set(inbox, mcqi_reg->component_index);
    mlxsw_reg_mcqi_device_type_set(inbox, mcqi_reg->device_type);
    mlxsw_reg_mcqi_info_type_set(inbox, mcqi_reg->info_type);
    mlxsw_reg_mcqi_offset_set(inbox, mcqi_reg->offset);
    mlxsw_reg_mcqi_data_size_set(inbox, mcqi_reg->data_size);
    switch (mcqi_reg->info_type) {
    case SXD_MCQI_INFO_TYPE_CAPABILITIES_E:
        mlxsw_reg_mcqi_data_mcqi_cap_signed_updates_only_set(inbox, mcqi_reg->data.mcqi_cap.signed_updates_only);
        mlxsw_reg_mcqi_data_mcqi_cap_match_chip_id_set(inbox, mcqi_reg->data.mcqi_cap.match_chip_id);
        mlxsw_reg_mcqi_data_mcqi_cap_match_psid_set(inbox, mcqi_reg->data.mcqi_cap.match_psid);
        mlxsw_reg_mcqi_data_mcqi_cap_check_user_timestamp_set(inbox, mcqi_reg->data.mcqi_cap.check_user_timestamp);
        mlxsw_reg_mcqi_data_mcqi_cap_match_base_guid_mac_set(inbox, mcqi_reg->data.mcqi_cap.match_base_guid_mac);
        break;

    case SXD_MCQI_INFO_TYPE_VERSION_E:
        mlxsw_reg_mcqi_data_mcqi_version_build_time_valid_set(inbox, mcqi_reg->data.mcqi_version.build_time_valid);
        mlxsw_reg_mcqi_data_mcqi_version_user_defined_time_valid_set(inbox, mcqi_reg->data.mcqi_version.user_defined_time_valid);
        mlxsw_reg_mcqi_data_mcqi_version_version_string_length_set(inbox, mcqi_reg->data.mcqi_version.version_string_length);
        mlxsw_reg_mcqi_data_mcqi_version_version_set(inbox, mcqi_reg->data.mcqi_version.version);
        mlxsw_reg_mcqi_data_mcqi_version_build_time_set(inbox, mcqi_reg->data.mcqi_version.build_time);
        mlxsw_reg_mcqi_data_mcqi_version_user_defined_time_set(inbox, mcqi_reg->data.mcqi_version.user_defined_time);
        mlxsw_reg_mcqi_data_mcqi_version_build_tool_version_set(inbox, mcqi_reg->data.mcqi_version.build_tool_version);
        mlxsw_reg_mcqi_data_mcqi_version_version_string_memcpy_to(inbox, (char *)mcqi_reg->data.mcqi_version.version_string);
        break;

    case SXD_MCQI_INFO_TYPE_ACTIVATION_METHOD_E:
        break;

    case SXD_MCQI_INFO_TYPE_LINKX_PROPERTIES_E:
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}

int __MCQI_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mcqi_reg *mcqi_reg = (struct ku_mcqi_reg*)ku_reg;

    mcqi_reg->read_pending_component = mlxsw_reg_mcqi_read_pending_component_get(outbox);
    mcqi_reg->device_index = mlxsw_reg_mcqi_device_index_get(outbox);
    mcqi_reg->component_index = mlxsw_reg_mcqi_component_index_get(outbox);
    mcqi_reg->device_type = mlxsw_reg_mcqi_device_type_get(outbox);
    mcqi_reg->info_type = mlxsw_reg_mcqi_info_type_get(outbox);
    mcqi_reg->info_size = mlxsw_reg_mcqi_info_size_get(outbox);
    mcqi_reg->offset = mlxsw_reg_mcqi_offset_get(outbox);
    mcqi_reg->data_size = mlxsw_reg_mcqi_data_size_get(outbox);
    switch (mcqi_reg->info_type) {
    case SXD_MCQI_INFO_TYPE_CAPABILITIES_E:
        mcqi_reg->data.mcqi_cap.supported_info_bitmask = mlxsw_reg_mcqi_data_mcqi_cap_supported_info_bitmask_get(outbox);
        mcqi_reg->data.mcqi_cap.component_size = mlxsw_reg_mcqi_data_mcqi_cap_component_size_get(outbox);
        mcqi_reg->data.mcqi_cap.max_component_size = mlxsw_reg_mcqi_data_mcqi_cap_max_component_size_get(outbox);
        mcqi_reg->data.mcqi_cap.log_mcda_word_size = mlxsw_reg_mcqi_data_mcqi_cap_log_mcda_word_size_get(outbox);
        mcqi_reg->data.mcqi_cap.mcda_max_write_size = mlxsw_reg_mcqi_data_mcqi_cap_mcda_max_write_size_get(outbox);
        mcqi_reg->data.mcqi_cap.rd_en = mlxsw_reg_mcqi_data_mcqi_cap_rd_en_get(outbox);
        mcqi_reg->data.mcqi_cap.signed_updates_only = mlxsw_reg_mcqi_data_mcqi_cap_signed_updates_only_get(outbox);
        mcqi_reg->data.mcqi_cap.match_chip_id = mlxsw_reg_mcqi_data_mcqi_cap_match_chip_id_get(outbox);
        mcqi_reg->data.mcqi_cap.match_psid = mlxsw_reg_mcqi_data_mcqi_cap_match_psid_get(outbox);
        mcqi_reg->data.mcqi_cap.check_user_timestamp = mlxsw_reg_mcqi_data_mcqi_cap_check_user_timestamp_get(outbox);
        mcqi_reg->data.mcqi_cap.match_base_guid_mac = mlxsw_reg_mcqi_data_mcqi_cap_match_base_guid_mac_get(outbox);
        break;

    case SXD_MCQI_INFO_TYPE_VERSION_E:
        mcqi_reg->data.mcqi_version.build_time_valid = mlxsw_reg_mcqi_data_mcqi_version_build_time_valid_get(outbox);
        mcqi_reg->data.mcqi_version.user_defined_time_valid = mlxsw_reg_mcqi_data_mcqi_version_user_defined_time_valid_get(outbox);
        mcqi_reg->data.mcqi_version.version_string_length = mlxsw_reg_mcqi_data_mcqi_version_version_string_length_get(outbox);
        mcqi_reg->data.mcqi_version.version = mlxsw_reg_mcqi_data_mcqi_version_version_get(outbox);
        mcqi_reg->data.mcqi_version.build_time = mlxsw_reg_mcqi_data_mcqi_version_build_time_get(outbox);
        mcqi_reg->data.mcqi_version.user_defined_time = mlxsw_reg_mcqi_data_mcqi_version_user_defined_time_get(outbox);
        mcqi_reg->data.mcqi_version.build_tool_version = mlxsw_reg_mcqi_data_mcqi_version_build_tool_version_get(outbox);
        mlxsw_reg_mcqi_data_mcqi_version_version_string_memcpy_from(outbox, (char *)mcqi_reg->data.mcqi_version.version_string);
        break;

    case SXD_MCQI_INFO_TYPE_ACTIVATION_METHOD_E:
        mcqi_reg->data.mcqi_activation_method.self_activation = mlxsw_reg_mcqi_data_mcqi_activation_method_self_activation_get(outbox);
        mcqi_reg->data.mcqi_activation_method.pending_server_ac_power_cycle = mlxsw_reg_mcqi_data_mcqi_activation_method_pending_server_ac_power_cycle_get(outbox);
        mcqi_reg->data.mcqi_activation_method.pending_server_dc_power_cycle = mlxsw_reg_mcqi_data_mcqi_activation_method_pending_server_dc_power_cycle_get(outbox);
        mcqi_reg->data.mcqi_activation_method.pending_server_reboot = mlxsw_reg_mcqi_data_mcqi_activation_method_pending_server_reboot_get(outbox);
        mcqi_reg->data.mcqi_activation_method.pending_fw_reset = mlxsw_reg_mcqi_data_mcqi_activation_method_pending_fw_reset_get(outbox);
        mcqi_reg->data.mcqi_activation_method.auto_activate = mlxsw_reg_mcqi_data_mcqi_activation_method_auto_activate_get(outbox);
        mcqi_reg->data.mcqi_activation_method.all_hosts_sync = mlxsw_reg_mcqi_data_mcqi_activation_method_all_hosts_sync_get(outbox);
        break;

    case SXD_MCQI_INFO_TYPE_LINKX_PROPERTIES_E:
        mcqi_reg->data.mcqi_linkx_properties.fw_image_info_bitmap = mlxsw_reg_mcqi_data_mcqi_linkx_properties_fw_image_info_bitmap_get(outbox);
        mcqi_reg->data.mcqi_linkx_properties.fw_image_status_bitmap = mlxsw_reg_mcqi_data_mcqi_linkx_properties_fw_image_status_bitmap_get(outbox);
        mcqi_reg->data.mcqi_linkx_properties.image_a_major = mlxsw_reg_mcqi_data_mcqi_linkx_properties_image_a_major_get(outbox);
        mcqi_reg->data.mcqi_linkx_properties.image_a_minor = mlxsw_reg_mcqi_data_mcqi_linkx_properties_image_a_minor_get(outbox);
        mcqi_reg->data.mcqi_linkx_properties.image_a_subminor = mlxsw_reg_mcqi_data_mcqi_linkx_properties_image_a_subminor_get(outbox);
        mcqi_reg->data.mcqi_linkx_properties.image_b_major = mlxsw_reg_mcqi_data_mcqi_linkx_properties_image_b_major_get(outbox);
        mcqi_reg->data.mcqi_linkx_properties.image_b_minor = mlxsw_reg_mcqi_data_mcqi_linkx_properties_image_b_minor_get(outbox);
        mcqi_reg->data.mcqi_linkx_properties.image_b_subminor = mlxsw_reg_mcqi_data_mcqi_linkx_properties_image_b_subminor_get(outbox);
        mcqi_reg->data.mcqi_linkx_properties.factory_image_major = mlxsw_reg_mcqi_data_mcqi_linkx_properties_factory_image_major_get(outbox);
        mcqi_reg->data.mcqi_linkx_properties.factory_image_minor = mlxsw_reg_mcqi_data_mcqi_linkx_properties_factory_image_minor_get(outbox);
        mcqi_reg->data.mcqi_linkx_properties.factory_image_subminor = mlxsw_reg_mcqi_data_mcqi_linkx_properties_factory_image_subminor_get(outbox);
        mcqi_reg->data.mcqi_linkx_properties.activation_type = mlxsw_reg_mcqi_data_mcqi_linkx_properties_activation_type_get(outbox);
        mcqi_reg->data.mcqi_linkx_properties.management_interface_protocol = mlxsw_reg_mcqi_data_mcqi_linkx_properties_management_interface_protocol_get(outbox);
        mcqi_reg->data.mcqi_linkx_properties.vendor_sn = mlxsw_reg_mcqi_data_mcqi_linkx_properties_vendor_sn_get(outbox);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}
EXPORT_SYMBOL(__MCQI_decode);

int sx_ACCESS_REG_MCQI(struct sx_dev *dev, struct ku_access_mcqi_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MCQI_LEN >> 2) + 1;

    if (MLXSW_MCQI_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MCQI_encode,
                                  __MCQI_decode,
                                  reg_len_dword,
                                  &reg_data->mcqi_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MCQI);

int sx_EMAD_ACCESS_REG_MCQI(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mcqi_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MCQI_LEN >> 2) + 1;

    if (MLXSW_MCQI_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MCQI_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MCQI_encode,
                                     __MCQI_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MCQI);

/************************************************
* PTASV2
***********************************************/
int __PTASV2_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ptasv2_reg *ptasv2_reg = (struct ku_ptasv2_reg*)ku_reg;

    mlxsw_reg_ptasv2_local_port_set(inbox, ptasv2_reg->local_port);
    mlxsw_reg_ptasv2_pnat_set(inbox, ptasv2_reg->pnat);
    mlxsw_reg_ptasv2_lp_msb_set(inbox, ptasv2_reg->lp_msb);
    mlxsw_reg_ptasv2_ib_cfg_delaytimeout_set(inbox, ptasv2_reg->ib_cfg_delaytimeout);
    mlxsw_reg_ptasv2_ig_dme_mod_admin_set(inbox, ptasv2_reg->ig_dme_mod_admin);
    mlxsw_reg_ptasv2_force_an_admin_set(inbox, ptasv2_reg->force_an_admin);
    switch (ptasv2_reg->version) {
    case SXD_PTASV2_VERSION_PRODUCTS_40NM_E:
        break;

    case SXD_PTASV2_VERSION_PRODUCTS_28NM_E:
        mlxsw_reg_ptasv2_page_data_ptasv2_28nm_tuning_type_admin_set(inbox, ptasv2_reg->page_data.ptasv2_28nm.tuning_type_admin);
        break;

    case SXD_PTASV2_VERSION_PRODUCTS_7NM_E:
        mlxsw_reg_ptasv2_page_data_ptasv2_7nm_max_recovery_retries_en_set(inbox, ptasv2_reg->page_data.ptasv2_7nm.max_recovery_retries_en);
        mlxsw_reg_ptasv2_page_data_ptasv2_7nm_phy_count_linkup_delay_set(inbox, ptasv2_reg->page_data.ptasv2_7nm.phy_count_linkup_delay);
        mlxsw_reg_ptasv2_page_data_ptasv2_7nm_max_recovery_retries_set(inbox, ptasv2_reg->page_data.ptasv2_7nm.max_recovery_retries);
        mlxsw_reg_ptasv2_page_data_ptasv2_7nm_lt_tuning_admin_set(inbox, ptasv2_reg->page_data.ptasv2_7nm.lt_tuning_admin);
        mlxsw_reg_ptasv2_page_data_ptasv2_7nm_preset_mask_set(inbox, ptasv2_reg->page_data.ptasv2_7nm.preset_mask);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}

int __PTASV2_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ptasv2_reg *ptasv2_reg = (struct ku_ptasv2_reg*)ku_reg;

    ptasv2_reg->version = mlxsw_reg_ptasv2_version_get(outbox);
    ptasv2_reg->local_port = mlxsw_reg_ptasv2_local_port_get(outbox);
    ptasv2_reg->pnat = mlxsw_reg_ptasv2_pnat_get(outbox);
    ptasv2_reg->lp_msb = mlxsw_reg_ptasv2_lp_msb_get(outbox);
    ptasv2_reg->ib_cfg_delaytimeout_cap = mlxsw_reg_ptasv2_ib_cfg_delaytimeout_cap_get(outbox);
    ptasv2_reg->ib_cfg_delaytimeout = mlxsw_reg_ptasv2_ib_cfg_delaytimeout_get(outbox);
    ptasv2_reg->ig_dme_mod_cap = mlxsw_reg_ptasv2_ig_dme_mod_cap_get(outbox);
    ptasv2_reg->ig_dme_mod_admin = mlxsw_reg_ptasv2_ig_dme_mod_admin_get(outbox);
    ptasv2_reg->force_an_cap = mlxsw_reg_ptasv2_force_an_cap_get(outbox);
    ptasv2_reg->force_an_admin = mlxsw_reg_ptasv2_force_an_admin_get(outbox);
    switch (ptasv2_reg->version) {
    case SXD_PTASV2_VERSION_PRODUCTS_40NM_E:
        break;

    case SXD_PTASV2_VERSION_PRODUCTS_28NM_E:
        ptasv2_reg->page_data.ptasv2_28nm.tuning_type_support = mlxsw_reg_ptasv2_page_data_ptasv2_28nm_tuning_type_support_get(outbox);
        ptasv2_reg->page_data.ptasv2_28nm.tuning_type_admin = mlxsw_reg_ptasv2_page_data_ptasv2_28nm_tuning_type_admin_get(outbox);
        break;

    case SXD_PTASV2_VERSION_PRODUCTS_7NM_E:
        ptasv2_reg->page_data.ptasv2_7nm.max_recovery_retries_en = mlxsw_reg_ptasv2_page_data_ptasv2_7nm_max_recovery_retries_en_get(outbox);
        ptasv2_reg->page_data.ptasv2_7nm.phy_count_linkup_delay = mlxsw_reg_ptasv2_page_data_ptasv2_7nm_phy_count_linkup_delay_get(outbox);
        ptasv2_reg->page_data.ptasv2_7nm.max_recovery_retries = mlxsw_reg_ptasv2_page_data_ptasv2_7nm_max_recovery_retries_get(outbox);
        ptasv2_reg->page_data.ptasv2_7nm.lt_tuning_support = mlxsw_reg_ptasv2_page_data_ptasv2_7nm_lt_tuning_support_get(outbox);
        ptasv2_reg->page_data.ptasv2_7nm.lt_tuning_admin = mlxsw_reg_ptasv2_page_data_ptasv2_7nm_lt_tuning_admin_get(outbox);
        ptasv2_reg->page_data.ptasv2_7nm.preset_mask = mlxsw_reg_ptasv2_page_data_ptasv2_7nm_preset_mask_get(outbox);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}
EXPORT_SYMBOL(__PTASV2_decode);

int sx_ACCESS_REG_PTASV2(struct sx_dev *dev, struct ku_access_ptasv2_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PTASV2_LEN >> 2) + 1;

    if (MLXSW_PTASV2_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PTASV2_encode,
                                  __PTASV2_decode,
                                  reg_len_dword,
                                  &reg_data->ptasv2_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PTASV2);

int sx_EMAD_ACCESS_REG_PTASV2(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ptasv2_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PTASV2_LEN >> 2) + 1;

    if (MLXSW_PTASV2_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PTASV2_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PTASV2_encode,
                                     __PTASV2_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PTASV2);

/************************************************
* MSECQ
***********************************************/
int __MSECQ_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_msecq_reg *msecq_reg = (struct ku_msecq_reg*)ku_reg;

    ((void)msecq_reg);

    return 0;
}

int __MSECQ_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_msecq_reg *msecq_reg = (struct ku_msecq_reg*)ku_reg;

    msecq_reg->network_option = mlxsw_reg_msecq_network_option_get(outbox);
    msecq_reg->local_ssm_code = mlxsw_reg_msecq_local_ssm_code_get(outbox);
    msecq_reg->local_enhanced_ssm_code = mlxsw_reg_msecq_local_enhanced_ssm_code_get(outbox);
    msecq_reg->local_clock_identity = mlxsw_reg_msecq_local_clock_identity_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MSECQ_decode);

int sx_ACCESS_REG_MSECQ(struct sx_dev *dev, struct ku_access_msecq_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MSECQ_LEN >> 2) + 1;

    if (MLXSW_MSECQ_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MSECQ_encode,
                                  __MSECQ_decode,
                                  reg_len_dword,
                                  &reg_data->msecq_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MSECQ);

int sx_EMAD_ACCESS_REG_MSECQ(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_msecq_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MSECQ_LEN >> 2) + 1;

    if (MLXSW_MSECQ_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MSECQ_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MSECQ_encode,
                                     __MSECQ_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MSECQ);

/************************************************
* MTPPSE
***********************************************/
int __MTPPSE_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtppse_reg *mtppse_reg = (struct ku_mtppse_reg*)ku_reg;

    mlxsw_reg_mtppse_pin_set(inbox, mtppse_reg->pin);
    mlxsw_reg_mtppse_event_arm_set(inbox, mtppse_reg->event_arm);
    mlxsw_reg_mtppse_event_generation_mode_set(inbox, mtppse_reg->event_generation_mode);


    return 0;
}

int __MTPPSE_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtppse_reg *mtppse_reg = (struct ku_mtppse_reg*)ku_reg;

    mtppse_reg->pin = mlxsw_reg_mtppse_pin_get(outbox);
    mtppse_reg->event_arm = mlxsw_reg_mtppse_event_arm_get(outbox);
    mtppse_reg->event_generation_mode = mlxsw_reg_mtppse_event_generation_mode_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MTPPSE_decode);

int sx_ACCESS_REG_MTPPSE(struct sx_dev *dev, struct ku_access_mtppse_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MTPPSE_LEN >> 2) + 1;

    if (MLXSW_MTPPSE_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTPPSE_encode,
                                  __MTPPSE_decode,
                                  reg_len_dword,
                                  &reg_data->mtppse_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTPPSE);

int sx_EMAD_ACCESS_REG_MTPPSE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtppse_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MTPPSE_LEN >> 2) + 1;

    if (MLXSW_MTPPSE_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MTPPSE_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MTPPSE_encode,
                                     __MTPPSE_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MTPPSE);

/************************************************
* PERAR
***********************************************/
int __PERAR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_perar_reg *perar_reg = (struct ku_perar_reg*)ku_reg;

    mlxsw_reg_perar_region_id_set(inbox, perar_reg->region_id);
    mlxsw_reg_perar_hw_region_set(inbox, perar_reg->hw_region);


    return 0;
}

int __PERAR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_perar_reg *perar_reg = (struct ku_perar_reg*)ku_reg;

    perar_reg->region_id = mlxsw_reg_perar_region_id_get(outbox);
    perar_reg->hw_region = mlxsw_reg_perar_hw_region_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__PERAR_decode);

int sx_ACCESS_REG_PERAR(struct sx_dev *dev, struct ku_access_perar_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PERAR_LEN >> 2) + 1;

    if (MLXSW_PERAR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PERAR_encode,
                                  __PERAR_decode,
                                  reg_len_dword,
                                  &reg_data->perar_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PERAR);

int sx_EMAD_ACCESS_REG_PERAR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_perar_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PERAR_LEN >> 2) + 1;

    if (MLXSW_PERAR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PERAR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PERAR_encode,
                                     __PERAR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PERAR);

/************************************************
* PEVPB
***********************************************/
int __PEVPB_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pevpb_reg *pevpb_reg = (struct ku_pevpb_reg*)ku_reg;

    mlxsw_reg_pevpb_local_port_set(inbox, pevpb_reg->local_port);
    mlxsw_reg_pevpb_lp_msb_set(inbox, pevpb_reg->lp_msb);
    mlxsw_reg_pevpb_ev_set(inbox, pevpb_reg->ev);


    return 0;
}

int __PEVPB_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pevpb_reg *pevpb_reg = (struct ku_pevpb_reg*)ku_reg;

    pevpb_reg->local_port = mlxsw_reg_pevpb_local_port_get(outbox);
    pevpb_reg->lp_msb = mlxsw_reg_pevpb_lp_msb_get(outbox);
    pevpb_reg->ev = mlxsw_reg_pevpb_ev_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__PEVPB_decode);

int sx_ACCESS_REG_PEVPB(struct sx_dev *dev, struct ku_access_pevpb_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PEVPB_LEN >> 2) + 1;

    if (MLXSW_PEVPB_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PEVPB_encode,
                                  __PEVPB_decode,
                                  reg_len_dword,
                                  &reg_data->pevpb_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PEVPB);

int sx_EMAD_ACCESS_REG_PEVPB(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pevpb_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PEVPB_LEN >> 2) + 1;

    if (MLXSW_PEVPB_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PEVPB_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PEVPB_encode,
                                     __PEVPB_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PEVPB);

/************************************************
* SFGC
***********************************************/
int __SFGC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sfgc_reg *sfgc_reg = (struct ku_sfgc_reg*)ku_reg;

    mlxsw_reg_sfgc_type_set(inbox, sfgc_reg->type);
    mlxsw_reg_sfgc_bridge_type_set(inbox, sfgc_reg->bridge_type);
    mlxsw_reg_sfgc_table_type_set(inbox, sfgc_reg->table_type);
    mlxsw_reg_sfgc_flood_table_set(inbox, sfgc_reg->flood_table);
    mlxsw_reg_sfgc_counter_set_type_set(inbox, sfgc_reg->counter_set_type);
    mlxsw_reg_sfgc_counter_index_set(inbox, sfgc_reg->counter_index);
    mlxsw_reg_sfgc_mid_base_set(inbox, sfgc_reg->mid_base);


    return 0;
}

int __SFGC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sfgc_reg *sfgc_reg = (struct ku_sfgc_reg*)ku_reg;

    sfgc_reg->type = mlxsw_reg_sfgc_type_get(outbox);
    sfgc_reg->bridge_type = mlxsw_reg_sfgc_bridge_type_get(outbox);
    sfgc_reg->table_type = mlxsw_reg_sfgc_table_type_get(outbox);
    sfgc_reg->flood_table = mlxsw_reg_sfgc_flood_table_get(outbox);
    sfgc_reg->counter_set_type = mlxsw_reg_sfgc_counter_set_type_get(outbox);
    sfgc_reg->counter_index = mlxsw_reg_sfgc_counter_index_get(outbox);
    sfgc_reg->mid_base = mlxsw_reg_sfgc_mid_base_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__SFGC_decode);

int sx_ACCESS_REG_SFGC(struct sx_dev *dev, struct ku_access_sfgc_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_SFGC_LEN >> 2) + 1;

    if (MLXSW_SFGC_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SFGC_encode,
                                  __SFGC_decode,
                                  reg_len_dword,
                                  &reg_data->sfgc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SFGC);

int sx_EMAD_ACCESS_REG_SFGC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sfgc_reg *reg)
{
    u16 reg_len_dword = (MLXSW_SFGC_LEN >> 2) + 1;

    if (MLXSW_SFGC_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_SFGC_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __SFGC_encode,
                                     __SFGC_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_SFGC);

/************************************************
* MCION
***********************************************/
int __MCION_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mcion_reg *mcion_reg = (struct ku_mcion_reg*)ku_reg;

    mlxsw_reg_mcion_module_set(inbox, mcion_reg->module);
    mlxsw_reg_mcion_slot_index_set(inbox, mcion_reg->slot_index);


    return 0;
}

int __MCION_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mcion_reg *mcion_reg = (struct ku_mcion_reg*)ku_reg;

    mcion_reg->module = mlxsw_reg_mcion_module_get(outbox);
    mcion_reg->slot_index = mlxsw_reg_mcion_slot_index_get(outbox);
    mcion_reg->module_status_bits = mlxsw_reg_mcion_module_status_bits_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MCION_decode);

int sx_ACCESS_REG_MCION(struct sx_dev *dev, struct ku_access_mcion_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MCION_LEN >> 2) + 1;

    if (MLXSW_MCION_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MCION_encode,
                                  __MCION_decode,
                                  reg_len_dword,
                                  &reg_data->mcion_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MCION);

int sx_EMAD_ACCESS_REG_MCION(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mcion_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MCION_LEN >> 2) + 1;

    if (MLXSW_MCION_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MCION_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MCION_encode,
                                     __MCION_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MCION);

/************************************************
* PCSR
***********************************************/
int __PCSR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pcsr_reg *pcsr_reg = (struct ku_pcsr_reg*)ku_reg;

    mlxsw_reg_pcsr_offset_set(inbox, pcsr_reg->offset);


    return 0;
}

int __PCSR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pcsr_reg *pcsr_reg = (struct ku_pcsr_reg*)ku_reg;
    uint32_t i = 0;

    pcsr_reg->gs = mlxsw_reg_pcsr_gs_get(outbox);
    pcsr_reg->offset = mlxsw_reg_pcsr_offset_get(outbox);
    for (i = 0; i < SXD_PCSR_PORT_STATUS_MASK_NUM; i++) {
        pcsr_reg->port_status_mask[i] = mlxsw_reg_pcsr_port_status_mask_get(outbox, i);
    }


    return 0;
}
EXPORT_SYMBOL(__PCSR_decode);

int sx_ACCESS_REG_PCSR(struct sx_dev *dev, struct ku_access_pcsr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PCSR_LEN >> 2) + 1;

    if (MLXSW_PCSR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PCSR_encode,
                                  __PCSR_decode,
                                  reg_len_dword,
                                  &reg_data->pcsr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PCSR);

int sx_EMAD_ACCESS_REG_PCSR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pcsr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PCSR_LEN >> 2) + 1;

    if (MLXSW_PCSR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PCSR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PCSR_encode,
                                     __PCSR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PCSR);

/************************************************
* MAFCR
***********************************************/
int __MAFCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mafcr_reg *mafcr_reg = (struct ku_mafcr_reg*)ku_reg;

    mlxsw_reg_mafcr_clear_set(inbox, mafcr_reg->clear);


    return 0;
}

int __MAFCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mafcr_reg *mafcr_reg = (struct ku_mafcr_reg*)ku_reg;

    mafcr_reg->clear = mlxsw_reg_mafcr_clear_get(outbox);
    mafcr_reg->counter_accu_overflow = mlxsw_reg_mafcr_counter_accu_overflow_get(outbox);
    mafcr_reg->packets_inc_units = mlxsw_reg_mafcr_packets_inc_units_get(outbox);
    mafcr_reg->bytes_inc_units = mlxsw_reg_mafcr_bytes_inc_units_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MAFCR_decode);

int sx_ACCESS_REG_MAFCR(struct sx_dev *dev, struct ku_access_mafcr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MAFCR_LEN >> 2) + 1;

    if (MLXSW_MAFCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MAFCR_encode,
                                  __MAFCR_decode,
                                  reg_len_dword,
                                  &reg_data->mafcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MAFCR);

int sx_EMAD_ACCESS_REG_MAFCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mafcr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MAFCR_LEN >> 2) + 1;

    if (MLXSW_MAFCR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MAFCR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MAFCR_encode,
                                     __MAFCR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MAFCR);

/************************************************
* SBSRD
***********************************************/
int __SBSRD_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sbsrd_reg *sbsrd_reg = (struct ku_sbsrd_reg*)ku_reg;

    mlxsw_reg_sbsrd_clr_set(inbox, sbsrd_reg->clr);
    mlxsw_reg_sbsrd_snap_set(inbox, sbsrd_reg->snap);
    mlxsw_reg_sbsrd_desc_set(inbox, sbsrd_reg->desc);
    mlxsw_reg_sbsrd_type_set(inbox, sbsrd_reg->type);
    mlxsw_reg_sbsrd_num_rec_set(inbox, sbsrd_reg->num_rec);
    mlxsw_reg_sbsrd_first_lp_msb_set(inbox, sbsrd_reg->first_lp_msb);
    mlxsw_reg_sbsrd_first_local_port_set(inbox, sbsrd_reg->first_local_port);


    return 0;
}

int __SBSRD_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sbsrd_reg *sbsrd_reg = (struct ku_sbsrd_reg*)ku_reg;
    uint32_t i = 0;

    sbsrd_reg->clr = mlxsw_reg_sbsrd_clr_get(outbox);
    sbsrd_reg->snap = mlxsw_reg_sbsrd_snap_get(outbox);
    sbsrd_reg->desc = mlxsw_reg_sbsrd_desc_get(outbox);
    sbsrd_reg->type = mlxsw_reg_sbsrd_type_get(outbox);
    sbsrd_reg->num_rec = mlxsw_reg_sbsrd_num_rec_get(outbox);
    sbsrd_reg->fisrt_entry_index = mlxsw_reg_sbsrd_fisrt_entry_index_get(outbox);
    sbsrd_reg->first_lp_msb = mlxsw_reg_sbsrd_first_lp_msb_get(outbox);
    sbsrd_reg->first_local_port = mlxsw_reg_sbsrd_first_local_port_get(outbox);
    for (i = 0; i < SXD_SBSRD_SHARED_BUFFER_STATUS_NUM; i++) {
        sbsrd_reg->shared_buffer_status[i].buff_occupancy = mlxsw_reg_sbsrd_buff_occupancy_get(outbox, i);
        sbsrd_reg->shared_buffer_status[i].max_buff_occupancy = mlxsw_reg_sbsrd_max_buff_occupancy_get(outbox, i);
    }


    return 0;
}
EXPORT_SYMBOL(__SBSRD_decode);

int sx_ACCESS_REG_SBSRD(struct sx_dev *dev, struct ku_access_sbsrd_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_SBSRD_LEN >> 2) + 1;

    if (MLXSW_SBSRD_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SBSRD_encode,
                                  __SBSRD_decode,
                                  reg_len_dword,
                                  &reg_data->sbsrd_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SBSRD);

int sx_EMAD_ACCESS_REG_SBSRD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sbsrd_reg *reg)
{
    u16 reg_len_dword = (MLXSW_SBSRD_LEN >> 2) + 1;

    if (MLXSW_SBSRD_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_SBSRD_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __SBSRD_encode,
                                     __SBSRD_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_SBSRD);

/************************************************
* QSPTC
***********************************************/
int __QSPTC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_qsptc_reg *qsptc_reg = (struct ku_qsptc_reg*)ku_reg;

    mlxsw_reg_qsptc_local_iport_set(inbox, qsptc_reg->local_iport);
    mlxsw_reg_qsptc_local_eport_set(inbox, qsptc_reg->local_eport);
    mlxsw_reg_qsptc_itclass_set(inbox, qsptc_reg->itclass);
    mlxsw_reg_qsptc_tclass_set(inbox, qsptc_reg->tclass);


    return 0;
}

int __QSPTC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_qsptc_reg *qsptc_reg = (struct ku_qsptc_reg*)ku_reg;

    qsptc_reg->local_iport = mlxsw_reg_qsptc_local_iport_get(outbox);
    qsptc_reg->local_eport = mlxsw_reg_qsptc_local_eport_get(outbox);
    qsptc_reg->itclass = mlxsw_reg_qsptc_itclass_get(outbox);
    qsptc_reg->tclass = mlxsw_reg_qsptc_tclass_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__QSPTC_decode);

int sx_ACCESS_REG_QSPTC(struct sx_dev *dev, struct ku_access_qsptc_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_QSPTC_LEN >> 2) + 1;

    if (MLXSW_QSPTC_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __QSPTC_encode,
                                  __QSPTC_decode,
                                  reg_len_dword,
                                  &reg_data->qsptc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_QSPTC);

int sx_EMAD_ACCESS_REG_QSPTC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_qsptc_reg *reg)
{
    u16 reg_len_dword = (MLXSW_QSPTC_LEN >> 2) + 1;

    if (MLXSW_QSPTC_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_QSPTC_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __QSPTC_encode,
                                     __QSPTC_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_QSPTC);

/************************************************
* IDDD
***********************************************/
int __IDDD_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_iddd_reg *iddd_reg = (struct ku_iddd_reg*)ku_reg;

    mlxsw_reg_iddd_entry_type_set(inbox, iddd_reg->entry_type);
    mlxsw_reg_iddd_duplication_set(inbox, iddd_reg->duplication);


    return 0;
}

int __IDDD_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_iddd_reg *iddd_reg = (struct ku_iddd_reg*)ku_reg;

    iddd_reg->entry_type = mlxsw_reg_iddd_entry_type_get(outbox);
    iddd_reg->duplication = mlxsw_reg_iddd_duplication_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__IDDD_decode);

int sx_ACCESS_REG_IDDD(struct sx_dev *dev, struct ku_access_iddd_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_IDDD_LEN >> 2) + 1;

    if (MLXSW_IDDD_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __IDDD_encode,
                                  __IDDD_decode,
                                  reg_len_dword,
                                  &reg_data->iddd_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_IDDD);

int sx_EMAD_ACCESS_REG_IDDD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_iddd_reg *reg)
{
    u16 reg_len_dword = (MLXSW_IDDD_LEN >> 2) + 1;

    if (MLXSW_IDDD_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_IDDD_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __IDDD_encode,
                                     __IDDD_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_IDDD);

/************************************************
* PMAOS
***********************************************/
int __PMAOS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmaos_reg *pmaos_reg = (struct ku_pmaos_reg*)ku_reg;

    mlxsw_reg_pmaos_rst_set(inbox, pmaos_reg->rst);
    mlxsw_reg_pmaos_slot_index_set(inbox, pmaos_reg->slot_index);
    mlxsw_reg_pmaos_module_set(inbox, pmaos_reg->module);
    mlxsw_reg_pmaos_admin_status_set(inbox, pmaos_reg->admin_status);
    mlxsw_reg_pmaos_ase_set(inbox, pmaos_reg->ase);
    mlxsw_reg_pmaos_ee_set(inbox, pmaos_reg->ee);
    mlxsw_reg_pmaos_e_set(inbox, pmaos_reg->e);


    return 0;
}

int __PMAOS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmaos_reg *pmaos_reg = (struct ku_pmaos_reg*)ku_reg;

    pmaos_reg->rst = mlxsw_reg_pmaos_rst_get(outbox);
    pmaos_reg->slot_index = mlxsw_reg_pmaos_slot_index_get(outbox);
    pmaos_reg->module = mlxsw_reg_pmaos_module_get(outbox);
    pmaos_reg->admin_status = mlxsw_reg_pmaos_admin_status_get(outbox);
    pmaos_reg->oper_status = mlxsw_reg_pmaos_oper_status_get(outbox);
    pmaos_reg->secondary = mlxsw_reg_pmaos_secondary_get(outbox);
    pmaos_reg->rev_incompatible = mlxsw_reg_pmaos_rev_incompatible_get(outbox);
    pmaos_reg->operational_notification = mlxsw_reg_pmaos_operational_notification_get(outbox);
    pmaos_reg->error_type = mlxsw_reg_pmaos_error_type_get(outbox);
    pmaos_reg->e = mlxsw_reg_pmaos_e_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__PMAOS_decode);

int sx_ACCESS_REG_PMAOS(struct sx_dev *dev, struct ku_access_pmaos_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PMAOS_LEN >> 2) + 1;

    if (MLXSW_PMAOS_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMAOS_encode,
                                  __PMAOS_decode,
                                  reg_len_dword,
                                  &reg_data->pmaos_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMAOS);

int sx_EMAD_ACCESS_REG_PMAOS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmaos_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PMAOS_LEN >> 2) + 1;

    if (MLXSW_PMAOS_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PMAOS_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PMAOS_encode,
                                     __PMAOS_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PMAOS);

/************************************************
* PBSR
***********************************************/
int __PBSR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pbsr_reg *pbsr_reg = (struct ku_pbsr_reg*)ku_reg;

    mlxsw_reg_pbsr_local_port_set(inbox, pbsr_reg->local_port);
    mlxsw_reg_pbsr_lp_msb_set(inbox, pbsr_reg->lp_msb);
    mlxsw_reg_pbsr_buffer_type_set(inbox, pbsr_reg->buffer_type);
    mlxsw_reg_pbsr_clear_wm_buff_mask_set(inbox, pbsr_reg->clear_wm_buff_mask);
    mlxsw_reg_pbsr_clear_wm_set(inbox, pbsr_reg->clear_wm);


    return 0;
}

int __PBSR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pbsr_reg *pbsr_reg = (struct ku_pbsr_reg*)ku_reg;
    uint32_t i = 0;

    pbsr_reg->local_port = mlxsw_reg_pbsr_local_port_get(outbox);
    pbsr_reg->lp_msb = mlxsw_reg_pbsr_lp_msb_get(outbox);
    pbsr_reg->buffer_type = mlxsw_reg_pbsr_buffer_type_get(outbox);
    pbsr_reg->clear_wm_buff_mask = mlxsw_reg_pbsr_clear_wm_buff_mask_get(outbox);
    pbsr_reg->clear_wm = mlxsw_reg_pbsr_clear_wm_get(outbox);
    pbsr_reg->used_shared_headroom_buffer = mlxsw_reg_pbsr_used_shared_headroom_buffer_get(outbox);
    for (i = 0; i < SXD_PBSR_STAT_BUFFER_NUM; i++) {
        pbsr_reg->stat_buffer[i].watermark = mlxsw_reg_pbsr_stat_buffer_watermark_get(outbox, i);
        pbsr_reg->stat_buffer[i].used_buffer = mlxsw_reg_pbsr_stat_buffer_used_buffer_get(outbox, i);
    }
    pbsr_reg->stat_shared_headroom_pool.watermark = mlxsw_reg_pbsr_stat_shared_headroom_pool_watermark_get(outbox);
    pbsr_reg->stat_shared_headroom_pool.used_buffer = mlxsw_reg_pbsr_stat_shared_headroom_pool_used_buffer_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__PBSR_decode);

int sx_ACCESS_REG_PBSR(struct sx_dev *dev, struct ku_access_pbsr_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_PBSR_LEN >> 2) + 1;

    if (MLXSW_PBSR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PBSR_encode,
                                  __PBSR_decode,
                                  reg_len_dword,
                                  &reg_data->pbsr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PBSR);

int sx_EMAD_ACCESS_REG_PBSR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pbsr_reg *reg)
{
    u16 reg_len_dword = (MLXSW_PBSR_LEN >> 2) + 1;

    if (MLXSW_PBSR_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_PBSR_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __PBSR_encode,
                                     __PBSR_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_PBSR);

/************************************************
* MSGI
***********************************************/
int __MSGI_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_msgi_reg *msgi_reg = (struct ku_msgi_reg*)ku_reg;

    ((void)msgi_reg);

    return 0;
}

int __MSGI_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_msgi_reg *msgi_reg = (struct ku_msgi_reg*)ku_reg;
    uint32_t i = 0;

    for (i = 0; i < SXD_MSGI_SERIAL_NUMBER_NUM; i++) {
        msgi_reg->serial_number[i] = mlxsw_reg_msgi_serial_number_get(outbox, i);
    }
    for (i = 0; i < SXD_MSGI_PART_NUMBER_NUM; i++) {
        msgi_reg->part_number[i] = mlxsw_reg_msgi_part_number_get(outbox, i);
    }
    msgi_reg->revision = mlxsw_reg_msgi_revision_get(outbox);
    for (i = 0; i < SXD_MSGI_PRODUCT_NAME_NUM; i++) {
        msgi_reg->product_name[i] = mlxsw_reg_msgi_product_name_get(outbox, i);
    }


    return 0;
}
EXPORT_SYMBOL(__MSGI_decode);

int sx_ACCESS_REG_MSGI(struct sx_dev *dev, struct ku_access_msgi_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MSGI_LEN >> 2) + 1;

    if (MLXSW_MSGI_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MSGI_encode,
                                  __MSGI_decode,
                                  reg_len_dword,
                                  &reg_data->msgi_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MSGI);

int sx_EMAD_ACCESS_REG_MSGI(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_msgi_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MSGI_LEN >> 2) + 1;

    if (MLXSW_MSGI_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MSGI_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MSGI_encode,
                                     __MSGI_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MSGI);

/************************************************
* MSPI
***********************************************/
int __MSPI_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mspi_reg *mspi_reg = (struct ku_mspi_reg*)ku_reg;

    ((void)mspi_reg);

    return 0;
}

int __MSPI_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mspi_reg *mspi_reg = (struct ku_mspi_reg*)ku_reg;

    mspi_reg->synce_support = mlxsw_reg_mspi_synce_support_get(outbox);
    mspi_reg->vendor_id = mlxsw_reg_mspi_vendor_id_get(outbox);
    mspi_reg->config_version_id = mlxsw_reg_mspi_config_version_id_get(outbox);
    mspi_reg->bcc = mlxsw_reg_mspi_bcc_get(outbox);
    mspi_reg->obtv = mlxsw_reg_mspi_obtv_get(outbox);
    mspi_reg->obs_temperature = mlxsw_reg_mspi_obs_temperature_get(outbox);
    mspi_reg->bitv = mlxsw_reg_mspi_bitv_get(outbox);
    mspi_reg->bis_temperature = mlxsw_reg_mspi_bis_temperature_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MSPI_decode);

int sx_ACCESS_REG_MSPI(struct sx_dev *dev, struct ku_access_mspi_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MSPI_LEN >> 2) + 1;

    if (MLXSW_MSPI_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MSPI_encode,
                                  __MSPI_decode,
                                  reg_len_dword,
                                  &reg_data->mspi_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MSPI);

int sx_EMAD_ACCESS_REG_MSPI(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mspi_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MSPI_LEN >> 2) + 1;

    if (MLXSW_MSPI_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MSPI_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MSPI_encode,
                                     __MSPI_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MSPI);

/************************************************
* MCC
***********************************************/
int __MCC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mcc_reg *mcc_reg = (struct ku_mcc_reg*)ku_reg;

    mlxsw_reg_mcc_activation_delay_sec_set(inbox, mcc_reg->activation_delay_sec);
    mlxsw_reg_mcc_instruction_set(inbox, mcc_reg->instruction);
    mlxsw_reg_mcc_component_index_set(inbox, mcc_reg->component_index);
    mlxsw_reg_mcc_auto_update_set(inbox, mcc_reg->auto_update);
    mlxsw_reg_mcc_update_handle_set(inbox, mcc_reg->update_handle);
    mlxsw_reg_mcc_component_size_set(inbox, mcc_reg->component_size);
    mlxsw_reg_mcc_device_index_set(inbox, mcc_reg->device_index);
    mlxsw_reg_mcc_device_type_set(inbox, mcc_reg->device_type);
    mlxsw_reg_mcc_device_index_size_set(inbox, mcc_reg->device_index_size);


    return 0;
}

int __MCC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mcc_reg *mcc_reg = (struct ku_mcc_reg*)ku_reg;

    mcc_reg->time_elapsed_since_last_cmd = mlxsw_reg_mcc_time_elapsed_since_last_cmd_get(outbox);
    mcc_reg->activation_delay_sec = mlxsw_reg_mcc_activation_delay_sec_get(outbox);
    mcc_reg->instruction = mlxsw_reg_mcc_instruction_get(outbox);
    mcc_reg->component_index = mlxsw_reg_mcc_component_index_get(outbox);
    mcc_reg->update_handle = mlxsw_reg_mcc_update_handle_get(outbox);
    mcc_reg->handle_owner_type = mlxsw_reg_mcc_handle_owner_type_get(outbox);
    mcc_reg->handle_owner_host_id = mlxsw_reg_mcc_handle_owner_host_id_get(outbox);
    mcc_reg->control_progress = mlxsw_reg_mcc_control_progress_get(outbox);
    mcc_reg->error_code = mlxsw_reg_mcc_error_code_get(outbox);
    mcc_reg->control_state = mlxsw_reg_mcc_control_state_get(outbox);
    mcc_reg->device_index = mlxsw_reg_mcc_device_index_get(outbox);
    mcc_reg->device_type = mlxsw_reg_mcc_device_type_get(outbox);
    mcc_reg->rejected_device_index = mlxsw_reg_mcc_rejected_device_index_get(outbox);
    mcc_reg->device_index_size = mlxsw_reg_mcc_device_index_size_get(outbox);


    return 0;
}
EXPORT_SYMBOL(__MCC_decode);

int sx_ACCESS_REG_MCC(struct sx_dev *dev, struct ku_access_mcc_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MCC_LEN >> 2) + 1;

    if (MLXSW_MCC_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MCC_encode,
                                  __MCC_decode,
                                  reg_len_dword,
                                  &reg_data->mcc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MCC);

int sx_EMAD_ACCESS_REG_MCC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mcc_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MCC_LEN >> 2) + 1;

    if (MLXSW_MCC_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MCC_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MCC_encode,
                                     __MCC_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MCC);

/************************************************
* MOPCE
***********************************************/
int __MOPCE_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mopce_reg *mopce_reg = (struct ku_mopce_reg*)ku_reg;

    mlxsw_reg_mopce_num_rec_set(inbox, mopce_reg->num_rec);


    return 0;
}

int __MOPCE_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mopce_reg *mopce_reg = (struct ku_mopce_reg*)ku_reg;
    uint32_t i = 0;

    mopce_reg->num_rec = mlxsw_reg_mopce_num_rec_get(outbox);
    for (i = 0; i < SXD_MOPCE_PERFORMANCE_COUNTER_INFO_NUM; i++) {
        mopce_reg->performance_counter_info[i].hw_unit_instance = mlxsw_reg_mopce_hw_unit_instance_get(outbox, i);
        mopce_reg->performance_counter_info[i].hw_unit_id = mlxsw_reg_mopce_hw_unit_id_get(outbox, i);
        mopce_reg->performance_counter_info[i].counter_index = mlxsw_reg_mopce_counter_index_get(outbox, i);
        mopce_reg->performance_counter_info[i].hw_unit_sub_instance = mlxsw_reg_mopce_hw_unit_sub_instance_get(outbox, i);
        mopce_reg->performance_counter_info[i].counter_value = mlxsw_reg_mopce_counter_value_get(outbox, i);
    }


    return 0;
}
EXPORT_SYMBOL(__MOPCE_decode);

int sx_ACCESS_REG_MOPCE(struct sx_dev *dev, struct ku_access_mopce_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MOPCE_LEN >> 2) + 1;

    if (MLXSW_MOPCE_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MOPCE_encode,
                                  __MOPCE_decode,
                                  reg_len_dword,
                                  &reg_data->mopce_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MOPCE);

int sx_EMAD_ACCESS_REG_MOPCE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mopce_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MOPCE_LEN >> 2) + 1;

    if (MLXSW_MOPCE_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MOPCE_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MOPCE_encode,
                                     __MOPCE_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MOPCE);

/************************************************
* MCDA
***********************************************/
int __MCDA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mcda_reg *mcda_reg = (struct ku_mcda_reg*)ku_reg;
    uint32_t i = 0;

    mlxsw_reg_mcda_update_handle_set(inbox, mcda_reg->update_handle);
    mlxsw_reg_mcda_offset_set(inbox, mcda_reg->offset);
    mlxsw_reg_mcda_size_set(inbox, mcda_reg->size);
    for (i = 0; i < SXD_MCDA_DATA_NUM; i++) {
        mlxsw_reg_mcda_data_set(inbox, i, mcda_reg->data[i]);
    }


    return 0;
}

int __MCDA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mcda_reg *mcda_reg = (struct ku_mcda_reg*)ku_reg;
    uint32_t i = 0;

    mcda_reg->update_handle = mlxsw_reg_mcda_update_handle_get(outbox);
    mcda_reg->offset = mlxsw_reg_mcda_offset_get(outbox);
    mcda_reg->size = mlxsw_reg_mcda_size_get(outbox);
    for (i = 0; i < SXD_MCDA_DATA_NUM; i++) {
        mcda_reg->data[i] = mlxsw_reg_mcda_data_get(outbox, i);
    }


    return 0;
}
EXPORT_SYMBOL(__MCDA_decode);

int sx_ACCESS_REG_MCDA(struct sx_dev *dev, struct ku_access_mcda_reg *reg_data)
{
    u16 reg_len_dword = (MLXSW_MCDA_LEN >> 2) + 1;

    if (MLXSW_MCDA_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MCDA_encode,
                                  __MCDA_decode,
                                  reg_len_dword,
                                  &reg_data->mcda_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MCDA);

int sx_EMAD_ACCESS_REG_MCDA(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mcda_reg *reg)
{
    u16 reg_len_dword = (MLXSW_MCDA_LEN >> 2) + 1;

    if (MLXSW_MCDA_LEN % 4 > 0) {
        reg_len_dword++;
    }

    return sx_emad_access_reg_common(dev,
                                     priority,
                                     method,
                                     MLXSW_MCDA_ID,
                                     reg,
                                     reg_len_dword,
                                     in_params,
                                     out_params,
                                     __MCDA_encode,
                                     __MCDA_decode);
}
EXPORT_SYMBOL(sx_EMAD_ACCESS_REG_MCDA);
