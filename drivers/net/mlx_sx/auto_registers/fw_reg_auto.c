/*
 * Copyright (C) 2008-2021 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include "../fw_internal.h"



/************************************************
* IGCR
***********************************************/
int __IGCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_igcr_reg *igcr_reg = (struct ku_igcr_reg*)ku_reg;
    
    mlxsw_reg_igcr_ddd_lpm_high_ipv6_set(inbox, igcr_reg->ddd_lpm_high_ipv6);
    mlxsw_reg_igcr_ddd_lpm_high_ipv4_set(inbox, igcr_reg->ddd_lpm_high_ipv4);
    mlxsw_reg_igcr_ddd_pe_actions_priority_set(inbox, igcr_reg->ddd_pe_actions_priority);
    mlxsw_reg_igcr_pisbo_set(inbox, igcr_reg->pisbo);


    return 0;
}

int __IGCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_igcr_reg *igcr_reg = (struct ku_igcr_reg*)ku_reg;
    
    igcr_reg->ddd_lpm_high_ipv6 = mlxsw_reg_igcr_ddd_lpm_high_ipv6_get(outbox);
    igcr_reg->ddd_lpm_high_ipv4 = mlxsw_reg_igcr_ddd_lpm_high_ipv4_get(outbox);
    igcr_reg->ddd_pe_actions_priority = mlxsw_reg_igcr_ddd_pe_actions_priority_get(outbox);
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

/************************************************
* HMON
***********************************************/
int __HMON_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_hmon_reg *hmon_reg = (struct ku_hmon_reg*)ku_reg;
        uint32_t index = 0;

    mlxsw_reg_hmon_clr_set(inbox, hmon_reg->clr);
    mlxsw_reg_hmon_cprdq_set(inbox, hmon_reg->cprdq);
    mlxsw_reg_hmon_read_type_set(inbox, hmon_reg->read_type);
    mlxsw_reg_hmon_crdq_set(inbox, hmon_reg->crdq);
    for (index = 0; index < SXD_HMON_WQE_OVERFLOW_RDQ_NUM; index++) {
        mlxsw_reg_hmon_hi_set(inbox, index, hmon_reg->wqe_overflow_rdq[index].hi);
        mlxsw_reg_hmon_lo_set(inbox, index, hmon_reg->wqe_overflow_rdq[index].lo);
    }


    return 0;
}

int __HMON_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_hmon_reg *hmon_reg = (struct ku_hmon_reg*)ku_reg;
        uint32_t index = 0;

    hmon_reg->clr = mlxsw_reg_hmon_clr_get(outbox);
    hmon_reg->cprdq = mlxsw_reg_hmon_cprdq_get(outbox);
    hmon_reg->read_type = mlxsw_reg_hmon_read_type_get(outbox);
    hmon_reg->crdq = mlxsw_reg_hmon_crdq_get(outbox);
    hmon_reg->wqe_of_wrap = mlxsw_reg_hmon_wqe_of_wrap_get(outbox);
    hmon_reg->wqe_overflow_high = mlxsw_reg_hmon_wqe_overflow_high_get(outbox);
    hmon_reg->wqe_overflow_low = mlxsw_reg_hmon_wqe_overflow_low_get(outbox);
    for (index = 0; index < SXD_HMON_WQE_OVERFLOW_RDQ_NUM; index++) {
        hmon_reg->wqe_overflow_rdq[index].hi = mlxsw_reg_hmon_hi_get(outbox, index);
        hmon_reg->wqe_overflow_rdq[index].lo = mlxsw_reg_hmon_lo_get(outbox, index);
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
    
    pmtm_reg->slot_index = mlxsw_reg_pmtm_slot_index_get(outbox);
    pmtm_reg->module = mlxsw_reg_pmtm_module_get(outbox);
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

/************************************************
* PMMP
***********************************************/
int __PMMP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmmp_reg *pmmp_reg = (struct ku_pmmp_reg*)ku_reg;
        uint32_t index = 0;

    mlxsw_reg_pmmp_slot_index_set(inbox, pmmp_reg->slot_index);
    mlxsw_reg_pmmp_module_set(inbox, pmmp_reg->module);
    mlxsw_reg_pmmp_eeprom_override_mask_set(inbox, pmmp_reg->eeprom_override_mask);
    mlxsw_reg_pmmp_eeprom_override_set(inbox, pmmp_reg->eeprom_override);
    for (index = 0; index < SXD_PMMP_QSFP_CABLE_PROTOCOL_TECHNOLOGY_NUM; index++) {
        mlxsw_reg_pmmp_qsfp_cable_protocol_technology_set(inbox, index, pmmp_reg->qsfp_cable_protocol_technology[index]);
    }
    for (index = 0; index < SXD_PMMP_SFP_CABLE_PROTOCOL_TECHNOLOGY_NUM; index++) {
        mlxsw_reg_pmmp_sfp_cable_protocol_technology_set(inbox, index, pmmp_reg->sfp_cable_protocol_technology[index]);
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
        uint32_t index = 0;

    pmmp_reg->slot_index = mlxsw_reg_pmmp_slot_index_get(outbox);
    pmmp_reg->module = mlxsw_reg_pmmp_module_get(outbox);
    pmmp_reg->eeprom_override = mlxsw_reg_pmmp_eeprom_override_get(outbox);
    for (index = 0; index < SXD_PMMP_QSFP_CABLE_PROTOCOL_TECHNOLOGY_NUM; index++) {
        pmmp_reg->qsfp_cable_protocol_technology[index] = mlxsw_reg_pmmp_qsfp_cable_protocol_technology_get(outbox, index);
    }
    for (index = 0; index < SXD_PMMP_SFP_CABLE_PROTOCOL_TECHNOLOGY_NUM; index++) {
        pmmp_reg->sfp_cable_protocol_technology[index] = mlxsw_reg_pmmp_sfp_cable_protocol_technology_get(outbox, index);
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
        uint32_t index = 0;

    for (index = 0; index < SXD_MTWE_SENSOR_WARNING_NUM; index++) {
        mtwe_reg->sensor_warning[index] = mlxsw_reg_mtwe_sensor_warning_get(outbox, index);
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
    mgir_reg->fw_info.isfu_major = mlxsw_reg_mgir_fw_info_isfu_major_get(outbox);
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
        uint32_t index = 0;

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
    for (index = 0; index < SXD_CEER_SIP_NUM; index++) {
        ceer_reg->sip[index] = mlxsw_reg_ceer_sip_get(outbox, index);
    }
    for (index = 0; index < SXD_CEER_DIP_NUM; index++) {
        ceer_reg->dip[index] = mlxsw_reg_ceer_dip_get(outbox, index);
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
        for (index = 0; index < SXD_CEER_INNER_SIP_NUM; index++) {
            ceer_reg->extra_data.ceer_extra_fields.inner_sip[index] = mlxsw_reg_ceer_extra_data_ceer_extra_fields_inner_sip_get(outbox, index);
        }
        for (index = 0; index < SXD_CEER_INNER_DIP_NUM; index++) {
            ceer_reg->extra_data.ceer_extra_fields.inner_dip[index] = mlxsw_reg_ceer_extra_data_ceer_extra_fields_inner_dip_get(outbox, index);
        }
        break;

    case SXD_CEER_EXTRA_DATA_TYPE_MPLS_E:
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_bos = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_bos_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_exp = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_exp_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_lb0_v = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_lb0_v_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_label0_label_id = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_label0_label_id_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_label0_ttl = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_label0_ttl_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_lb1_v = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_lb1_v_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_label1_label_id = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_label1_label_id_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_label1_ttl = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_label1_ttl_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_lb2_v = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_lb2_v_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_label2_label_id = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_label2_label_id_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_label2_ttl = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_label2_ttl_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_lb3_v = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_lb3_v_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_label3_label_id = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_label3_label_id_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_label3_ttl = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_label3_ttl_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_lb4_v = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_lb4_v_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_label4_label_id = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_label4_label_id_get(outbox);
        ceer_reg->extra_data.ceer_extra_fields_MPLS.mpls_label4_ttl = mlxsw_reg_ceer_extra_data_ceer_extra_fields_MPLS_mpls_label4_ttl_get(outbox);
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

/************************************************
* SMID_V2
***********************************************/
int __SMID_V2_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_smid_v2_reg *smid_v2_reg = (struct ku_smid_v2_reg*)ku_reg;
        uint32_t index = 0;

    mlxsw_reg_smid_v2_swid_set(inbox, smid_v2_reg->swid);
    mlxsw_reg_smid_v2_mid_set(inbox, smid_v2_reg->mid);
    mlxsw_reg_smid_v2_op_set(inbox, smid_v2_reg->op);
    mlxsw_reg_smid_v2_smpe_valid_set(inbox, smid_v2_reg->smpe_valid);
    mlxsw_reg_smid_v2_smpe_set(inbox, smid_v2_reg->smpe);
    for (index = 0; index < SXD_SMID_V2_PORT_NUM; index++) {
        mlxsw_reg_smid_v2_port_set(inbox, index, smid_v2_reg->port[index]);
    }
    for (index = 0; index < SXD_SMID_V2_MASK_NUM; index++) {
        mlxsw_reg_smid_v2_mask_set(inbox, index, smid_v2_reg->mask[index]);
    }


    return 0;
}

int __SMID_V2_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_smid_v2_reg *smid_v2_reg = (struct ku_smid_v2_reg*)ku_reg;
        uint32_t index = 0;

    smid_v2_reg->swid = mlxsw_reg_smid_v2_swid_get(outbox);
    smid_v2_reg->mid = mlxsw_reg_smid_v2_mid_get(outbox);
    smid_v2_reg->op = mlxsw_reg_smid_v2_op_get(outbox);
    smid_v2_reg->smpe_valid = mlxsw_reg_smid_v2_smpe_valid_get(outbox);
    smid_v2_reg->smpe = mlxsw_reg_smid_v2_smpe_get(outbox);
    for (index = 0; index < SXD_SMID_V2_PORT_NUM; index++) {
        smid_v2_reg->port[index] = mlxsw_reg_smid_v2_port_get(outbox, index);
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

/************************************************
* PPCNT
***********************************************/
int __PPCNT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppcnt_reg *ppcnt_reg = (struct ku_ppcnt_reg*)ku_reg;
        uint32_t index = 0;

    mlxsw_reg_ppcnt_swid_set(inbox, ppcnt_reg->swid);
    mlxsw_reg_ppcnt_local_port_set(inbox, ppcnt_reg->local_port);
    mlxsw_reg_ppcnt_pnat_set(inbox, ppcnt_reg->pnat);
    mlxsw_reg_ppcnt_lp_msb_set(inbox, ppcnt_reg->lp_msb);
    mlxsw_reg_ppcnt_port_type_set(inbox, ppcnt_reg->port_type);
    mlxsw_reg_ppcnt_grp_set(inbox, ppcnt_reg->grp);
    mlxsw_reg_ppcnt_clr_set(inbox, ppcnt_reg->clr);
    mlxsw_reg_ppcnt_lp_gl_set(inbox, ppcnt_reg->lp_gl);
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
        for (index = 0; index < SXD_PPCNT_HIST_NUM; index++) {
            mlxsw_reg_ppcnt_counter_set_ppcnt_rs_fec_histograms_counters_hi_set(inbox, index, ppcnt_reg->counter_set.ppcnt_rs_fec_histograms_counters.hist[index].hi);
            mlxsw_reg_ppcnt_counter_set_ppcnt_rs_fec_histograms_counters_lo_set(inbox, index, ppcnt_reg->counter_set.ppcnt_rs_fec_histograms_counters.hist[index].lo);
        }
        break;

    case SXD_PPCNT_GRP_USR_XSR_PHYSICAL_LAYER_COUNTERS_GROUP_E:
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
        uint32_t index = 0;

    ppcnt_reg->swid = mlxsw_reg_ppcnt_swid_get(outbox);
    ppcnt_reg->local_port = mlxsw_reg_ppcnt_local_port_get(outbox);
    ppcnt_reg->pnat = mlxsw_reg_ppcnt_pnat_get(outbox);
    ppcnt_reg->lp_msb = mlxsw_reg_ppcnt_lp_msb_get(outbox);
    ppcnt_reg->port_type = mlxsw_reg_ppcnt_port_type_get(outbox);
    ppcnt_reg->grp = mlxsw_reg_ppcnt_grp_get(outbox);
    ppcnt_reg->clr = mlxsw_reg_ppcnt_clr_get(outbox);
    ppcnt_reg->lp_gl = mlxsw_reg_ppcnt_lp_gl_get(outbox);
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
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.symbol_error_counter = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_symbol_error_counter_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.link_error_recovery_counter = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_link_error_recovery_counter_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.link_downed_counter = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_link_downed_counter_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.port_rcv_errors = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_port_rcv_errors_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.port_rcv_remote_physical_errors = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.port_rcv_switch_relay_errors = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.port_xmit_discards = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_port_xmit_discards_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.port_xmit_constraint_errors = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_port_xmit_constraint_errors_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.port_rcv_constraint_errors = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_port_rcv_constraint_errors_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.local_link_integrity_errors = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_local_link_integrity_errors_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.excessive_buffer_overrun_errors = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.vl_15_dropped = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_vl_15_dropped_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.port_xmit_data = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_port_xmit_data_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.port_rcv_data = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_port_rcv_data_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.port_xmit_pkts = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_port_xmit_pkts_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.port_rcv_pkts = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_port_rcv_pkts_get(outbox);
        ppcnt_reg->counter_set.IB_portcntrs_attribute_grp_data.port_xmit_wait = mlxsw_reg_ppcnt_counter_set_IB_portcntrs_attribute_grp_data_port_xmit_wait_get(outbox);
        break;

    case SXD_PPCNT_GRP_INFINIBAND_EXTENDED_PORT_COUNTERS_E:
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.symbol_error_counter_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_symbol_error_counter_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.symbol_error_counter_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_symbol_error_counter_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.link_error_recovery_counter_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_link_error_recovery_counter_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.link_error_recovery_counter_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_link_error_recovery_counter_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.link_downed_counter_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_link_downed_counter_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.link_downed_counter_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_link_downed_counter_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_errors_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_rcv_errors_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_errors_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_rcv_errors_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_remote_physical_errors_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_remote_physical_errors_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_rcv_remote_physical_errors_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_switch_relay_errors_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_switch_relay_errors_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_rcv_switch_relay_errors_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_discards_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_xmit_discards_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_discards_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_xmit_discards_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_constraint_errors_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_xmit_constraint_errors_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_constraint_errors_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_xmit_constraint_errors_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_constraint_errors_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_rcv_constraint_errors_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_constraint_errors_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_rcv_constraint_errors_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.local_link_integrity_errors_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_local_link_integrity_errors_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.local_link_integrity_errors_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_local_link_integrity_errors_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.excessive_buffer_overrun_errors_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.excessive_buffer_overrun_errors_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_excessive_buffer_overrun_errors_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.vl_15_dropped_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_vl_15_dropped_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.vl_15_dropped_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_vl_15_dropped_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_data_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_xmit_data_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_data_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_xmit_data_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_data_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_rcv_data_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_data_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_rcv_data_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_pkts_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_xmit_pkts_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_pkts_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_xmit_pkts_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_pkts_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_rcv_pkts_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_pkts_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_rcv_pkts_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_wait_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_xmit_wait_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_wait_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_xmit_wait_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_effective_rcv_pkts_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_effective_rcv_pkts_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_effective_rcv_pkts_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_effective_rcv_pkts_low_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_effective_rcv_data_high = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_effective_rcv_data_high_get(outbox);
        ppcnt_reg->counter_set.IB_long_portcntrs_attribute_grp_data.port_effective_rcv_data_low = mlxsw_reg_ppcnt_counter_set_IB_long_portcntrs_attribute_grp_data_port_effective_rcv_data_low_get(outbox);
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
        ppcnt_reg->counter_set.ppcnt_plr_counters.hi_retransmission_rate_high = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_hi_retransmission_rate_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.hi_retransmission_rate_low = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_hi_retransmission_rate_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_xmit_retry_codes_within_t_sec_max_high = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_xmit_retry_codes_within_t_sec_max_high_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.plr_xmit_retry_codes_within_t_sec_max_low = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_plr_xmit_retry_codes_within_t_sec_max_low_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.pre_plr_ber_magnitude = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_pre_plr_ber_magnitude_get(outbox);
        ppcnt_reg->counter_set.ppcnt_plr_counters.pre_plr_ber_coef = mlxsw_reg_ppcnt_counter_set_ppcnt_plr_counters_pre_plr_ber_coef_get(outbox);
        break;

    case SXD_PPCNT_GRP_RS_FEC_HISTOGRAM_GROUP_E:
        for (index = 0; index < SXD_PPCNT_HIST_NUM; index++) {
            ppcnt_reg->counter_set.ppcnt_rs_fec_histograms_counters.hist[index].hi = mlxsw_reg_ppcnt_counter_set_ppcnt_rs_fec_histograms_counters_hi_get(outbox, index);
            ppcnt_reg->counter_set.ppcnt_rs_fec_histograms_counters.hist[index].lo = mlxsw_reg_ppcnt_counter_set_ppcnt_rs_fec_histograms_counters_lo_get(outbox, index);
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
        uint32_t index = 0;

    mtewe_reg->last_sensor = mlxsw_reg_mtewe_last_sensor_get(outbox);
    mtewe_reg->slot_index = mlxsw_reg_mtewe_slot_index_get(outbox);
    mtewe_reg->sensor_count = mlxsw_reg_mtewe_sensor_count_get(outbox);
    for (index = 0; index < SXD_MTEWE_SENSOR_WARNING_NUM; index++) {
        mtewe_reg->sensor_warning[index] = mlxsw_reg_mtewe_sensor_warning_get(outbox, index);
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

/************************************************
* MOCS
***********************************************/
int __MOCS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mocs_reg *mocs_reg = (struct ku_mocs_reg*)ku_reg;
        uint32_t index = 0;

    mlxsw_reg_mocs_type_set(inbox, mocs_reg->type);
    mlxsw_reg_mocs_clear_set(inbox, mocs_reg->clear);
    mlxsw_reg_mocs_opcode_set(inbox, mocs_reg->opcode);
    mlxsw_reg_mocs_hi_set(inbox, mocs_reg->event_tid.hi);
    mlxsw_reg_mocs_lo_set(inbox, mocs_reg->event_tid.lo);
    switch (mocs_reg->type) {
    case SXD_MOCS_TYPE_PPCNT_SES1_E:
        for (index = 0; index < SXD_MOCS_PORT_MASK_NUM; index++) {
            mlxsw_reg_mocs_entry_mocs_ppcnt_port_mask_set(inbox, index, mocs_reg->entry.mocs_ppcnt.port_mask[index]);
        }
        for (index = 0; index < SXD_MOCS_GRP_MASK_NUM; index++) {
            mlxsw_reg_mocs_entry_mocs_ppcnt_grp_mask_set(inbox, index, mocs_reg->entry.mocs_ppcnt.grp_mask[index]);
        }
        mlxsw_reg_mocs_entry_mocs_ppcnt_tc_mask_set(inbox, mocs_reg->entry.mocs_ppcnt.tc_mask);
        mlxsw_reg_mocs_entry_mocs_ppcnt_prio_mask_set(inbox, mocs_reg->entry.mocs_ppcnt.prio_mask);
        mlxsw_reg_mocs_entry_mocs_ppcnt_rx_buffer_mask_set(inbox, mocs_reg->entry.mocs_ppcnt.rx_buffer_mask);
        break;

    case SXD_MOCS_TYPE_MGPCB_E:
        mlxsw_reg_mocs_entry_mocs_mgpcb_flush_set(inbox, mocs_reg->entry.mocs_mgpcb.flush);
        mlxsw_reg_mocs_entry_mocs_mgpcb_num_rec_set(inbox, mocs_reg->entry.mocs_mgpcb.num_rec);
        mlxsw_reg_mocs_entry_mocs_mgpcb_counter_index_base_set(inbox, mocs_reg->entry.mocs_mgpcb.counter_index_base);
        break;

    case SXD_MOCS_TYPE_PBSR_E:
        for (index = 0; index < SXD_MOCS_PORT_MASK_NUM; index++) {
            mlxsw_reg_mocs_entry_mocs_pbsr_port_mask_set(inbox, index, mocs_reg->entry.mocs_pbsr.port_mask[index]);
        }
        break;

    case SXD_MOCS_TYPE_SBSRD_E:
        mlxsw_reg_mocs_entry_mocs_sbsrd_curr_set(inbox, mocs_reg->entry.mocs_sbsrd.curr);
        mlxsw_reg_mocs_entry_mocs_sbsrd_snap_set(inbox, mocs_reg->entry.mocs_sbsrd.snap);
        mlxsw_reg_mocs_entry_mocs_sbsrd_cells_set(inbox, mocs_reg->entry.mocs_sbsrd.cells);
        mlxsw_reg_mocs_entry_mocs_sbsrd_desc_set(inbox, mocs_reg->entry.mocs_sbsrd.desc);
        break;

    case SXD_MOCS_TYPE_CEER_E:
        for (index = 0; index < SXD_MOCS_PORT_MASK_NUM; index++) {
            mlxsw_reg_mocs_entry_mocs_ceer_port_mask_set(inbox, index, mocs_reg->entry.mocs_ceer.port_mask[index]);
        }
        break;

    case SXD_MOCS_TYPE_MAFBI_E:
        mlxsw_reg_mocs_entry_mocs_mafbi_flush_set(inbox, mocs_reg->entry.mocs_mafbi.flush);
        mlxsw_reg_mocs_entry_mocs_mafbi_type_set(inbox, mocs_reg->entry.mocs_mafbi.type);
        mlxsw_reg_mocs_entry_mocs_mafbi_num_rec_set(inbox, mocs_reg->entry.mocs_mafbi.num_rec);
        mlxsw_reg_mocs_entry_mocs_mafbi_counter_index_base_set(inbox, mocs_reg->entry.mocs_mafbi.counter_index_base);
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
        uint32_t index = 0;

    mocs_reg->type = mlxsw_reg_mocs_type_get(outbox);
    mocs_reg->clear = mlxsw_reg_mocs_clear_get(outbox);
    mocs_reg->status = mlxsw_reg_mocs_status_get(outbox);
    mocs_reg->event_tid.hi = mlxsw_reg_mocs_hi_get(outbox);
    mocs_reg->event_tid.lo = mlxsw_reg_mocs_lo_get(outbox);
    switch (mocs_reg->type) {
    case SXD_MOCS_TYPE_PPCNT_SES1_E:
        for (index = 0; index < SXD_MOCS_PORT_MASK_NUM; index++) {
            mocs_reg->entry.mocs_ppcnt.port_mask[index] = mlxsw_reg_mocs_entry_mocs_ppcnt_port_mask_get(outbox, index);
        }
        for (index = 0; index < SXD_MOCS_GRP_MASK_NUM; index++) {
            mocs_reg->entry.mocs_ppcnt.grp_mask[index] = mlxsw_reg_mocs_entry_mocs_ppcnt_grp_mask_get(outbox, index);
        }
        mocs_reg->entry.mocs_ppcnt.tc_mask = mlxsw_reg_mocs_entry_mocs_ppcnt_tc_mask_get(outbox);
        mocs_reg->entry.mocs_ppcnt.prio_mask = mlxsw_reg_mocs_entry_mocs_ppcnt_prio_mask_get(outbox);
        mocs_reg->entry.mocs_ppcnt.rx_buffer_mask = mlxsw_reg_mocs_entry_mocs_ppcnt_rx_buffer_mask_get(outbox);
        break;

    case SXD_MOCS_TYPE_MGPCB_E:
        mocs_reg->entry.mocs_mgpcb.flush = mlxsw_reg_mocs_entry_mocs_mgpcb_flush_get(outbox);
        mocs_reg->entry.mocs_mgpcb.num_rec = mlxsw_reg_mocs_entry_mocs_mgpcb_num_rec_get(outbox);
        mocs_reg->entry.mocs_mgpcb.counter_index_base = mlxsw_reg_mocs_entry_mocs_mgpcb_counter_index_base_get(outbox);
        break;

    case SXD_MOCS_TYPE_PBSR_E:
        for (index = 0; index < SXD_MOCS_PORT_MASK_NUM; index++) {
            mocs_reg->entry.mocs_pbsr.port_mask[index] = mlxsw_reg_mocs_entry_mocs_pbsr_port_mask_get(outbox, index);
        }
        break;

    case SXD_MOCS_TYPE_SBSRD_E:
        mocs_reg->entry.mocs_sbsrd.curr = mlxsw_reg_mocs_entry_mocs_sbsrd_curr_get(outbox);
        mocs_reg->entry.mocs_sbsrd.snap = mlxsw_reg_mocs_entry_mocs_sbsrd_snap_get(outbox);
        mocs_reg->entry.mocs_sbsrd.cells = mlxsw_reg_mocs_entry_mocs_sbsrd_cells_get(outbox);
        mocs_reg->entry.mocs_sbsrd.desc = mlxsw_reg_mocs_entry_mocs_sbsrd_desc_get(outbox);
        break;

    case SXD_MOCS_TYPE_CEER_E:
        for (index = 0; index < SXD_MOCS_PORT_MASK_NUM; index++) {
            mocs_reg->entry.mocs_ceer.port_mask[index] = mlxsw_reg_mocs_entry_mocs_ceer_port_mask_get(outbox, index);
        }
        break;

    case SXD_MOCS_TYPE_MAFBI_E:
        mocs_reg->entry.mocs_mafbi.flush = mlxsw_reg_mocs_entry_mocs_mafbi_flush_get(outbox);
        mocs_reg->entry.mocs_mafbi.type = mlxsw_reg_mocs_entry_mocs_mafbi_type_get(outbox);
        mocs_reg->entry.mocs_mafbi.num_rec = mlxsw_reg_mocs_entry_mocs_mafbi_num_rec_get(outbox);
        mocs_reg->entry.mocs_mafbi.counter_index_base = mlxsw_reg_mocs_entry_mocs_mafbi_counter_index_base_get(outbox);
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
    pllp_reg->split_stat = mlxsw_reg_pllp_split_stat_get(outbox);
    pllp_reg->split_num = mlxsw_reg_pllp_split_num_get(outbox);
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
        mlxsw_reg_mcqi_data_mcqi_version_build_time_hi_set(inbox, mcqi_reg->data.mcqi_version.build_time.hi);
        mlxsw_reg_mcqi_data_mcqi_version_build_time_lo_set(inbox, mcqi_reg->data.mcqi_version.build_time.lo);
        mlxsw_reg_mcqi_data_mcqi_version_user_defined_time_hi_set(inbox, mcqi_reg->data.mcqi_version.user_defined_time.hi);
        mlxsw_reg_mcqi_data_mcqi_version_user_defined_time_lo_set(inbox, mcqi_reg->data.mcqi_version.user_defined_time.lo);
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
        mcqi_reg->data.mcqi_version.build_time.hi = mlxsw_reg_mcqi_data_mcqi_version_build_time_hi_get(outbox);
        mcqi_reg->data.mcqi_version.build_time.lo = mlxsw_reg_mcqi_data_mcqi_version_build_time_lo_get(outbox);
        mcqi_reg->data.mcqi_version.user_defined_time.hi = mlxsw_reg_mcqi_data_mcqi_version_user_defined_time_hi_get(outbox);
        mcqi_reg->data.mcqi_version.user_defined_time.lo = mlxsw_reg_mcqi_data_mcqi_version_user_defined_time_lo_get(outbox);
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
        uint32_t index = 0;

    pcsr_reg->gs = mlxsw_reg_pcsr_gs_get(outbox);
    pcsr_reg->offset = mlxsw_reg_pcsr_offset_get(outbox);
    for (index = 0; index < SXD_PCSR_PORT_STATUS_MASK_NUM; index++) {
        pcsr_reg->port_status_mask[index] = mlxsw_reg_pcsr_port_status_mask_get(outbox, index);
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
        uint32_t index = 0;

    sbsrd_reg->clr = mlxsw_reg_sbsrd_clr_get(outbox);
    sbsrd_reg->snap = mlxsw_reg_sbsrd_snap_get(outbox);
    sbsrd_reg->desc = mlxsw_reg_sbsrd_desc_get(outbox);
    sbsrd_reg->type = mlxsw_reg_sbsrd_type_get(outbox);
    sbsrd_reg->num_rec = mlxsw_reg_sbsrd_num_rec_get(outbox);
    sbsrd_reg->fisrt_entry_index = mlxsw_reg_sbsrd_fisrt_entry_index_get(outbox);
    sbsrd_reg->first_lp_msb = mlxsw_reg_sbsrd_first_lp_msb_get(outbox);
    sbsrd_reg->first_local_port = mlxsw_reg_sbsrd_first_local_port_get(outbox);
    for (index = 0; index < SXD_SBSRD_SHARED_BUFFER_STATUS_NUM; index++) {
        sbsrd_reg->shared_buffer_status[index].buff_occupancy = mlxsw_reg_sbsrd_buff_occupancy_get(outbox, index);
        sbsrd_reg->shared_buffer_status[index].max_buff_occupancy = mlxsw_reg_sbsrd_max_buff_occupancy_get(outbox, index);
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
        uint32_t index = 0;

    pbsr_reg->local_port = mlxsw_reg_pbsr_local_port_get(outbox);
    pbsr_reg->lp_msb = mlxsw_reg_pbsr_lp_msb_get(outbox);
    pbsr_reg->buffer_type = mlxsw_reg_pbsr_buffer_type_get(outbox);
    pbsr_reg->clear_wm_buff_mask = mlxsw_reg_pbsr_clear_wm_buff_mask_get(outbox);
    pbsr_reg->clear_wm = mlxsw_reg_pbsr_clear_wm_get(outbox);
    pbsr_reg->used_shared_headroom_buffer = mlxsw_reg_pbsr_used_shared_headroom_buffer_get(outbox);
    for (index = 0; index < SXD_PBSR_STAT_BUFFER_NUM; index++) {
        pbsr_reg->stat_buffer[index].watermark = mlxsw_reg_pbsr_stat_buffer_watermark_get(outbox, index);
        pbsr_reg->stat_buffer[index].used_buffer = mlxsw_reg_pbsr_stat_buffer_used_buffer_get(outbox, index);
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

/************************************************
* MCDA
***********************************************/
int __MCDA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mcda_reg *mcda_reg = (struct ku_mcda_reg*)ku_reg;
        uint32_t index = 0;

    mlxsw_reg_mcda_update_handle_set(inbox, mcda_reg->update_handle);
    mlxsw_reg_mcda_offset_set(inbox, mcda_reg->offset);
    mlxsw_reg_mcda_size_set(inbox, mcda_reg->size);
    for (index = 0; index < SXD_MCDA_DATA_NUM; index++) {
        mlxsw_reg_mcda_data_set(inbox, index, mcda_reg->data[index]);
    }


    return 0;
}

int __MCDA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mcda_reg *mcda_reg = (struct ku_mcda_reg*)ku_reg;
        uint32_t index = 0;

    mcda_reg->update_handle = mlxsw_reg_mcda_update_handle_get(outbox);
    mcda_reg->offset = mlxsw_reg_mcda_offset_get(outbox);
    mcda_reg->size = mlxsw_reg_mcda_size_get(outbox);
    for (index = 0; index < SXD_MCDA_DATA_NUM; index++) {
        mcda_reg->data[index] = mlxsw_reg_mcda_data_get(outbox, index);
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
