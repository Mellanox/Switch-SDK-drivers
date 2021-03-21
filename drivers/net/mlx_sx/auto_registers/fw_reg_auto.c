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

#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include "../fw_internal.h"



/************************************************
* IGCR
***********************************************/
static int __IGCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_igcr_reg *igcr_reg = (struct ku_igcr_reg*)ku_reg;
    
    mlxsw_reg_igcr_ddd_lpm_high_ipv6_set(inbox, igcr_reg->ddd_lpm_high_ipv6);
    mlxsw_reg_igcr_ddd_lpm_high_ipv4_set(inbox, igcr_reg->ddd_lpm_high_ipv4);
    mlxsw_reg_igcr_ddd_pe_actions_priority_set(inbox, igcr_reg->ddd_pe_actions_priority);
    mlxsw_reg_igcr_pisbo_set(inbox, igcr_reg->pisbo);


    return 0;
}

static int __IGCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_igcr_reg *igcr_reg = (struct ku_igcr_reg*)ku_reg;
    
    igcr_reg->ddd_lpm_high_ipv6 = mlxsw_reg_igcr_ddd_lpm_high_ipv6_get(outbox);
    igcr_reg->ddd_lpm_high_ipv4 = mlxsw_reg_igcr_ddd_lpm_high_ipv4_get(outbox);
    igcr_reg->ddd_pe_actions_priority = mlxsw_reg_igcr_ddd_pe_actions_priority_get(outbox);
    igcr_reg->pisbo = mlxsw_reg_igcr_pisbo_get(outbox);


    return 0;
}

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
static int __MTMP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtmp_reg *mtmp_reg = (struct ku_mtmp_reg*)ku_reg;
    
    mlxsw_reg_mtmp_slot_index_set(inbox, mtmp_reg->slot_index);
    mlxsw_reg_mtmp_sensor_index_set(inbox, mtmp_reg->sensor_index);
    mlxsw_reg_mtmp_mte_set(inbox, mtmp_reg->mte);
    mlxsw_reg_mtmp_mtr_set(inbox, mtmp_reg->mtr);
    mlxsw_reg_mtmp_tee_set(inbox, mtmp_reg->tee);
    mlxsw_reg_mtmp_temperature_threshold_hi_set(inbox, mtmp_reg->temperature_threshold_hi);
    mlxsw_reg_mtmp_temperature_threshold_lo_set(inbox, mtmp_reg->temperature_threshold_lo);


    return 0;
}

static int __MTMP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtmp_reg *mtmp_reg = (struct ku_mtmp_reg*)ku_reg;
    
    mtmp_reg->slot_index = mlxsw_reg_mtmp_slot_index_get(outbox);
    mtmp_reg->sensor_index = mlxsw_reg_mtmp_sensor_index_get(outbox);
    mtmp_reg->temperature = mlxsw_reg_mtmp_temperature_get(outbox);
    mtmp_reg->mte = mlxsw_reg_mtmp_mte_get(outbox);
    mtmp_reg->mtr = mlxsw_reg_mtmp_mtr_get(outbox);
    mtmp_reg->max_temperature = mlxsw_reg_mtmp_max_temperature_get(outbox);
    mtmp_reg->tee = mlxsw_reg_mtmp_tee_get(outbox);
    mtmp_reg->temperature_threshold_hi = mlxsw_reg_mtmp_temperature_threshold_hi_get(outbox);
    mtmp_reg->temperature_threshold_lo = mlxsw_reg_mtmp_temperature_threshold_lo_get(outbox);
    mtmp_reg->sensor_name_hi = mlxsw_reg_mtmp_sensor_name_hi_get(outbox);
    mtmp_reg->sensor_name_lo = mlxsw_reg_mtmp_sensor_name_lo_get(outbox);


    return 0;
}

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
static int __MOGCR_encode(u8 *inbox, void *ku_reg, void *context)
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

static int __MOGCR_decode(u8 *outbox, void *ku_reg, void *context)
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
static int __HMON_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_hmon_reg *hmon_reg = (struct ku_hmon_reg*)ku_reg;
        uint32_t index = 0;

    mlxsw_reg_hmon_clr_set(inbox, hmon_reg->clr);
    mlxsw_reg_hmon_cprdq_set(inbox, hmon_reg->cprdq);
    mlxsw_reg_hmon_crdq_set(inbox, hmon_reg->crdq);
    for (index = 0; index < SXD_HMON_WQE_OVERFLOW_RDQ_NUM; index++) {
        mlxsw_reg_hmon_hi_set(inbox, index, hmon_reg->wqe_overflow_rdq[index].hi);
        mlxsw_reg_hmon_lo_set(inbox, index, hmon_reg->wqe_overflow_rdq[index].lo);
    }


    return 0;
}

static int __HMON_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_hmon_reg *hmon_reg = (struct ku_hmon_reg*)ku_reg;
        uint32_t index = 0;

    hmon_reg->clr = mlxsw_reg_hmon_clr_get(outbox);
    hmon_reg->cprdq = mlxsw_reg_hmon_cprdq_get(outbox);
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
static int __MGPIR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mgpir_reg *mgpir_reg = (struct ku_mgpir_reg*)ku_reg;
    
    mlxsw_reg_mgpir_slot_index_set(inbox, mgpir_reg->hw_info.slot_index);


    return 0;
}

static int __MGPIR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mgpir_reg *mgpir_reg = (struct ku_mgpir_reg*)ku_reg;
    
    mgpir_reg->hw_info.slot_index = mlxsw_reg_mgpir_slot_index_get(outbox);
    mgpir_reg->hw_info.device_type = mlxsw_reg_mgpir_device_type_get(outbox);
    mgpir_reg->hw_info.devices_per_flash = mlxsw_reg_mgpir_devices_per_flash_get(outbox);
    mgpir_reg->hw_info.num_of_devices = mlxsw_reg_mgpir_num_of_devices_get(outbox);
    mgpir_reg->hw_info.num_of_slots = mlxsw_reg_mgpir_num_of_slots_get(outbox);
    mgpir_reg->hw_info.num_of_modules = mlxsw_reg_mgpir_num_of_modules_get(outbox);


    return 0;
}

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
* PMMP
***********************************************/
static int __PMMP_encode(u8 *inbox, void *ku_reg, void *context)
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

static int __PMMP_decode(u8 *outbox, void *ku_reg, void *context)
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
* MGIR
***********************************************/
static int __MGIR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mgir_reg *mgir_reg = (struct ku_mgir_reg*)ku_reg;
    
    ((void)mgir_reg);

    return 0;
}

static int __MGIR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mgir_reg *mgir_reg = (struct ku_mgir_reg*)ku_reg;
    
    mgir_reg->hw_info.device_hw_revision = mlxsw_reg_mgir_device_hw_revision_get(outbox);
    mgir_reg->hw_info.device_id = mlxsw_reg_mgir_device_id_get(outbox);
    mgir_reg->hw_info.num_ports = mlxsw_reg_mgir_num_ports_get(outbox);
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
* IBFMRC
***********************************************/
static int __IBFMRC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ibfmrc_reg *ibfmrc_reg = (struct ku_ibfmrc_reg*)ku_reg;
    
    mlxsw_reg_ibfmrc_attr_id_en_set(inbox, ibfmrc_reg->attr_id_en);


    return 0;
}

static int __IBFMRC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ibfmrc_reg *ibfmrc_reg = (struct ku_ibfmrc_reg*)ku_reg;
    
    ibfmrc_reg->attr_id_en = mlxsw_reg_ibfmrc_attr_id_en_get(outbox);


    return 0;
}

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
* MDFCR
***********************************************/
static int __MDFCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mdfcr_reg *mdfcr_reg = (struct ku_mdfcr_reg*)ku_reg;
    
    mlxsw_reg_mdfcr_slot_index_set(inbox, mdfcr_reg->slot_index);
    mlxsw_reg_mdfcr_device_type_set(inbox, mdfcr_reg->device_type);
    mlxsw_reg_mdfcr_all_set(inbox, mdfcr_reg->all);
    mlxsw_reg_mdfcr_device_index_set(inbox, mdfcr_reg->device_index);


    return 0;
}

static int __MDFCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mdfcr_reg *mdfcr_reg = (struct ku_mdfcr_reg*)ku_reg;
    
    mdfcr_reg->slot_index = mlxsw_reg_mdfcr_slot_index_get(outbox);
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
static int __PAOS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_paos_reg *paos_reg = (struct ku_paos_reg*)ku_reg;
    
    mlxsw_reg_paos_swid_set(inbox, paos_reg->swid);
    mlxsw_reg_paos_local_port_set(inbox, paos_reg->local_port);
    mlxsw_reg_paos_pnat_set(inbox, paos_reg->pnat);
    mlxsw_reg_paos_admin_status_set(inbox, paos_reg->admin_status);
    mlxsw_reg_paos_ase_set(inbox, paos_reg->ase);
    mlxsw_reg_paos_ee_set(inbox, paos_reg->ee);
    mlxsw_reg_paos_e_set(inbox, paos_reg->e);


    return 0;
}

static int __PAOS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_paos_reg *paos_reg = (struct ku_paos_reg*)ku_reg;
    
    paos_reg->swid = mlxsw_reg_paos_swid_get(outbox);
    paos_reg->local_port = mlxsw_reg_paos_local_port_get(outbox);
    paos_reg->pnat = mlxsw_reg_paos_pnat_get(outbox);
    paos_reg->admin_status = mlxsw_reg_paos_admin_status_get(outbox);
    paos_reg->oper_status = mlxsw_reg_paos_oper_status_get(outbox);
    paos_reg->e = mlxsw_reg_paos_e_get(outbox);


    return 0;
}

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
static int __MTUTC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtutc_reg *mtutc_reg = (struct ku_mtutc_reg*)ku_reg;
    
    mlxsw_reg_mtutc_operation_set(inbox, mtutc_reg->operation);
    mlxsw_reg_mtutc_freq_adjustment_set(inbox, mtutc_reg->freq_adjustment);
    mlxsw_reg_mtutc_utc_sec_set(inbox, mtutc_reg->utc_sec);
    mlxsw_reg_mtutc_utc_nsec_set(inbox, mtutc_reg->utc_nsec);
    mlxsw_reg_mtutc_time_adjustment_set(inbox, mtutc_reg->time_adjustment);


    return 0;
}

static int __MTUTC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtutc_reg *mtutc_reg = (struct ku_mtutc_reg*)ku_reg;
    
    mtutc_reg->operation = mlxsw_reg_mtutc_operation_get(outbox);
    mtutc_reg->freq_adjustment = mlxsw_reg_mtutc_freq_adjustment_get(outbox);


    return 0;
}

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
static int __IBFMR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ibfmr_reg *ibfmr_reg = (struct ku_ibfmr_reg*)ku_reg;
    
    ((void)ibfmr_reg);

    return 0;
}

static int __IBFMR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ibfmr_reg *ibfmr_reg = (struct ku_ibfmr_reg*)ku_reg;
    
    ibfmr_reg->atm_v = mlxsw_reg_ibfmr_atm_v_get(outbox);
    ibfmr_reg->attribute_id = mlxsw_reg_ibfmr_attribute_id_get(outbox);
    ibfmr_reg->attribute_modifier = mlxsw_reg_ibfmr_attribute_modifier_get(outbox);


    return 0;
}

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
* PPAD
***********************************************/
static int __PPAD_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppad_reg *ppad_reg = (struct ku_ppad_reg*)ku_reg;
    
    mlxsw_reg_ppad_single_base_mac_set(inbox, ppad_reg->single_base_mac);
    mlxsw_reg_ppad_pnat_set(inbox, ppad_reg->pnat);
    mlxsw_reg_ppad_local_port_set(inbox, ppad_reg->local_port);
    mlxsw_reg_ppad_mac_memcpy_to(inbox, (char *)ppad_reg->mac);


    return 0;
}

static int __PPAD_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppad_reg *ppad_reg = (struct ku_ppad_reg*)ku_reg;
    
    ppad_reg->single_base_mac = mlxsw_reg_ppad_single_base_mac_get(outbox);
    ppad_reg->pnat = mlxsw_reg_ppad_pnat_get(outbox);
    ppad_reg->local_port = mlxsw_reg_ppad_local_port_get(outbox);
    mlxsw_reg_ppad_mac_memcpy_from(outbox, (char *)ppad_reg->mac);


    return 0;
}

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
static int __MOCS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mocs_reg *mocs_reg = (struct ku_mocs_reg*)ku_reg;
        uint32_t index = 0;

    mlxsw_reg_mocs_type_set(inbox, mocs_reg->type);
    mlxsw_reg_mocs_clear_set(inbox, mocs_reg->clear);
    mlxsw_reg_mocs_opcode_set(inbox, mocs_reg->opcode);
    mlxsw_reg_mocs_hi_set(inbox, mocs_reg->event_tid.hi);
    mlxsw_reg_mocs_lo_set(inbox, mocs_reg->event_tid.lo);
    for (index = 0; index < SXD_MOCS_PORT_MASK_NUM; index++) {
        mlxsw_reg_mocs_mocs_ppcnt_port_mask_set(inbox, index, mocs_reg->entry.mocs_ppcnt.port_mask[index]);
    }
    for (index = 0; index < SXD_MOCS_GRP_MASK_NUM; index++) {
        mlxsw_reg_mocs_mocs_ppcnt_grp_mask_set(inbox, index, mocs_reg->entry.mocs_ppcnt.grp_mask[index]);
    }
    mlxsw_reg_mocs_mocs_ppcnt_tc_mask_set(inbox, mocs_reg->entry.mocs_ppcnt.tc_mask);
    mlxsw_reg_mocs_mocs_ppcnt_prio_mask_set(inbox, mocs_reg->entry.mocs_ppcnt.prio_mask);
    mlxsw_reg_mocs_mocs_ppcnt_rx_buffer_mask_set(inbox, mocs_reg->entry.mocs_ppcnt.rx_buffer_mask);
    mlxsw_reg_mocs_mocs_mgpcb_num_rec_set(inbox, mocs_reg->entry.mocs_mgpcb.num_rec);
    mlxsw_reg_mocs_mocs_mgpcb_counter_index_base_set(inbox, mocs_reg->entry.mocs_mgpcb.counter_index_base);
    for (index = 0; index < SXD_MOCS_PORT_MASK_NUM; index++) {
        mlxsw_reg_mocs_mocs_pbsr_port_mask_set(inbox, index, mocs_reg->entry.mocs_pbsr.port_mask[index]);
    }
    mlxsw_reg_mocs_mocs_sbsrd_curr_set(inbox, mocs_reg->entry.mocs_sbsrd.curr);
    mlxsw_reg_mocs_mocs_sbsrd_snap_set(inbox, mocs_reg->entry.mocs_sbsrd.snap);
    mlxsw_reg_mocs_mocs_sbsrd_cells_set(inbox, mocs_reg->entry.mocs_sbsrd.cells);
    mlxsw_reg_mocs_mocs_sbsrd_desc_set(inbox, mocs_reg->entry.mocs_sbsrd.desc);


    return 0;
}

static int __MOCS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mocs_reg *mocs_reg = (struct ku_mocs_reg*)ku_reg;
        uint32_t index = 0;

    mocs_reg->type = mlxsw_reg_mocs_type_get(outbox);
    mocs_reg->clear = mlxsw_reg_mocs_clear_get(outbox);
    mocs_reg->status = mlxsw_reg_mocs_status_get(outbox);
    mocs_reg->event_tid.hi = mlxsw_reg_mocs_hi_get(outbox);
    mocs_reg->event_tid.lo = mlxsw_reg_mocs_lo_get(outbox);
    for (index = 0; index < SXD_MOCS_PORT_MASK_NUM; index++) {
        mocs_reg->entry.mocs_ppcnt.port_mask[index] = mlxsw_reg_mocs_mocs_ppcnt_port_mask_get(outbox, index);
    }
    for (index = 0; index < SXD_MOCS_GRP_MASK_NUM; index++) {
        mocs_reg->entry.mocs_ppcnt.grp_mask[index] = mlxsw_reg_mocs_mocs_ppcnt_grp_mask_get(outbox, index);
    }
    mocs_reg->entry.mocs_ppcnt.tc_mask = mlxsw_reg_mocs_mocs_ppcnt_tc_mask_get(outbox);
    mocs_reg->entry.mocs_ppcnt.prio_mask = mlxsw_reg_mocs_mocs_ppcnt_prio_mask_get(outbox);
    mocs_reg->entry.mocs_ppcnt.rx_buffer_mask = mlxsw_reg_mocs_mocs_ppcnt_rx_buffer_mask_get(outbox);
    mocs_reg->entry.mocs_mgpcb.num_rec = mlxsw_reg_mocs_mocs_mgpcb_num_rec_get(outbox);
    mocs_reg->entry.mocs_mgpcb.counter_index_base = mlxsw_reg_mocs_mocs_mgpcb_counter_index_base_get(outbox);
    for (index = 0; index < SXD_MOCS_PORT_MASK_NUM; index++) {
        mocs_reg->entry.mocs_pbsr.port_mask[index] = mlxsw_reg_mocs_mocs_pbsr_port_mask_get(outbox, index);
    }
    mocs_reg->entry.mocs_sbsrd.curr = mlxsw_reg_mocs_mocs_sbsrd_curr_get(outbox);
    mocs_reg->entry.mocs_sbsrd.snap = mlxsw_reg_mocs_mocs_sbsrd_snap_get(outbox);
    mocs_reg->entry.mocs_sbsrd.cells = mlxsw_reg_mocs_mocs_sbsrd_cells_get(outbox);
    mocs_reg->entry.mocs_sbsrd.desc = mlxsw_reg_mocs_mocs_sbsrd_desc_get(outbox);


    return 0;
}

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
* MCQI
***********************************************/
static int __MCQI_encode(u8 *inbox, void *ku_reg, void *context)
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
        mlxsw_reg_mcqi_mcqi_cap_signed_updates_only_set(inbox, mcqi_reg->data.mcqi_cap.signed_updates_only);
        mlxsw_reg_mcqi_mcqi_cap_match_chip_id_set(inbox, mcqi_reg->data.mcqi_cap.match_chip_id);
        mlxsw_reg_mcqi_mcqi_cap_match_psid_set(inbox, mcqi_reg->data.mcqi_cap.match_psid);
        mlxsw_reg_mcqi_mcqi_cap_check_user_timestamp_set(inbox, mcqi_reg->data.mcqi_cap.check_user_timestamp);
        mlxsw_reg_mcqi_mcqi_cap_match_base_guid_mac_set(inbox, mcqi_reg->data.mcqi_cap.match_base_guid_mac);
        break;

    case SXD_MCQI_INFO_TYPE_VERSION_E:
        mlxsw_reg_mcqi_mcqi_version_build_time_valid_set(inbox, mcqi_reg->data.mcqi_version.build_time_valid);
        mlxsw_reg_mcqi_mcqi_version_user_defined_time_valid_set(inbox, mcqi_reg->data.mcqi_version.user_defined_time_valid);
        mlxsw_reg_mcqi_mcqi_version_version_string_length_set(inbox, mcqi_reg->data.mcqi_version.version_string_length);
        mlxsw_reg_mcqi_mcqi_version_version_set(inbox, mcqi_reg->data.mcqi_version.version);
        mlxsw_reg_mcqi_mcqi_version_build_time_hi_set(inbox, mcqi_reg->data.mcqi_version.build_time.hi);
        mlxsw_reg_mcqi_mcqi_version_build_time_lo_set(inbox, mcqi_reg->data.mcqi_version.build_time.lo);
        mlxsw_reg_mcqi_mcqi_version_user_defined_time_hi_set(inbox, mcqi_reg->data.mcqi_version.user_defined_time.hi);
        mlxsw_reg_mcqi_mcqi_version_user_defined_time_lo_set(inbox, mcqi_reg->data.mcqi_version.user_defined_time.lo);
        mlxsw_reg_mcqi_mcqi_version_build_tool_version_set(inbox, mcqi_reg->data.mcqi_version.build_tool_version);
        mlxsw_reg_mcqi_mcqi_version_version_string_memcpy_to(inbox, (char *)mcqi_reg->data.mcqi_version.version_string);
        break;

    case SXD_MCQI_INFO_TYPE_ACTIVATION_METHOD_E:
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}

static int __MCQI_decode(u8 *outbox, void *ku_reg, void *context)
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
        mcqi_reg->data.mcqi_cap.supported_info_bitmask = mlxsw_reg_mcqi_mcqi_cap_supported_info_bitmask_get(outbox);
        mcqi_reg->data.mcqi_cap.component_size = mlxsw_reg_mcqi_mcqi_cap_component_size_get(outbox);
        mcqi_reg->data.mcqi_cap.max_component_size = mlxsw_reg_mcqi_mcqi_cap_max_component_size_get(outbox);
        mcqi_reg->data.mcqi_cap.log_mcda_word_size = mlxsw_reg_mcqi_mcqi_cap_log_mcda_word_size_get(outbox);
        mcqi_reg->data.mcqi_cap.mcda_max_write_size = mlxsw_reg_mcqi_mcqi_cap_mcda_max_write_size_get(outbox);
        mcqi_reg->data.mcqi_cap.rd_en = mlxsw_reg_mcqi_mcqi_cap_rd_en_get(outbox);
        mcqi_reg->data.mcqi_cap.signed_updates_only = mlxsw_reg_mcqi_mcqi_cap_signed_updates_only_get(outbox);
        mcqi_reg->data.mcqi_cap.match_chip_id = mlxsw_reg_mcqi_mcqi_cap_match_chip_id_get(outbox);
        mcqi_reg->data.mcqi_cap.match_psid = mlxsw_reg_mcqi_mcqi_cap_match_psid_get(outbox);
        mcqi_reg->data.mcqi_cap.check_user_timestamp = mlxsw_reg_mcqi_mcqi_cap_check_user_timestamp_get(outbox);
        mcqi_reg->data.mcqi_cap.match_base_guid_mac = mlxsw_reg_mcqi_mcqi_cap_match_base_guid_mac_get(outbox);
        break;

    case SXD_MCQI_INFO_TYPE_VERSION_E:
        mcqi_reg->data.mcqi_version.build_time_valid = mlxsw_reg_mcqi_mcqi_version_build_time_valid_get(outbox);
        mcqi_reg->data.mcqi_version.user_defined_time_valid = mlxsw_reg_mcqi_mcqi_version_user_defined_time_valid_get(outbox);
        mcqi_reg->data.mcqi_version.version_string_length = mlxsw_reg_mcqi_mcqi_version_version_string_length_get(outbox);
        mcqi_reg->data.mcqi_version.version = mlxsw_reg_mcqi_mcqi_version_version_get(outbox);
        mcqi_reg->data.mcqi_version.build_time.hi = mlxsw_reg_mcqi_mcqi_version_build_time_hi_get(outbox);
        mcqi_reg->data.mcqi_version.build_time.lo = mlxsw_reg_mcqi_mcqi_version_build_time_lo_get(outbox);
        mcqi_reg->data.mcqi_version.user_defined_time.hi = mlxsw_reg_mcqi_mcqi_version_user_defined_time_hi_get(outbox);
        mcqi_reg->data.mcqi_version.user_defined_time.lo = mlxsw_reg_mcqi_mcqi_version_user_defined_time_lo_get(outbox);
        mcqi_reg->data.mcqi_version.build_tool_version = mlxsw_reg_mcqi_mcqi_version_build_tool_version_get(outbox);
        mlxsw_reg_mcqi_mcqi_version_version_string_memcpy_from(outbox, (char *)mcqi_reg->data.mcqi_version.version_string);
        break;

    case SXD_MCQI_INFO_TYPE_ACTIVATION_METHOD_E:
        mcqi_reg->data.mcqi_activation_method.pending_server_ac_power_cycle = mlxsw_reg_mcqi_mcqi_activation_method_pending_server_ac_power_cycle_get(outbox);
        mcqi_reg->data.mcqi_activation_method.pending_server_dc_power_cycle = mlxsw_reg_mcqi_mcqi_activation_method_pending_server_dc_power_cycle_get(outbox);
        mcqi_reg->data.mcqi_activation_method.pending_server_reboot = mlxsw_reg_mcqi_mcqi_activation_method_pending_server_reboot_get(outbox);
        mcqi_reg->data.mcqi_activation_method.pending_fw_reset = mlxsw_reg_mcqi_mcqi_activation_method_pending_fw_reset_get(outbox);
        mcqi_reg->data.mcqi_activation_method.auto_activate = mlxsw_reg_mcqi_mcqi_activation_method_auto_activate_get(outbox);
        mcqi_reg->data.mcqi_activation_method.all_hosts_sync = mlxsw_reg_mcqi_mcqi_activation_method_all_hosts_sync_get(outbox);
        mcqi_reg->data.mcqi_activation_method.device_hw_reset = mlxsw_reg_mcqi_mcqi_activation_method_device_hw_reset_get(outbox);
        break;

    default:
        /* Other types not supported yet */
        break;
    }


    return 0;
}

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
static int __PEVPB_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pevpb_reg *pevpb_reg = (struct ku_pevpb_reg*)ku_reg;
    
    mlxsw_reg_pevpb_local_port_set(inbox, pevpb_reg->local_port);
    mlxsw_reg_pevpb_ev_set(inbox, pevpb_reg->ev);


    return 0;
}

static int __PEVPB_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pevpb_reg *pevpb_reg = (struct ku_pevpb_reg*)ku_reg;
    
    pevpb_reg->local_port = mlxsw_reg_pevpb_local_port_get(outbox);
    pevpb_reg->ev = mlxsw_reg_pevpb_ev_get(outbox);


    return 0;
}

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
static int __SFGC_encode(u8 *inbox, void *ku_reg, void *context)
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

static int __SFGC_decode(u8 *outbox, void *ku_reg, void *context)
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
static int __MCION_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mcion_reg *mcion_reg = (struct ku_mcion_reg*)ku_reg;
    
    mlxsw_reg_mcion_module_set(inbox, mcion_reg->module);
    mlxsw_reg_mcion_slot_index_set(inbox, mcion_reg->slot_index);


    return 0;
}

static int __MCION_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mcion_reg *mcion_reg = (struct ku_mcion_reg*)ku_reg;
    
    mcion_reg->module = mlxsw_reg_mcion_module_get(outbox);
    mcion_reg->slot_index = mlxsw_reg_mcion_slot_index_get(outbox);
    mcion_reg->module_status_bits = mlxsw_reg_mcion_module_status_bits_get(outbox);


    return 0;
}

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
static int __PCSR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pcsr_reg *pcsr_reg = (struct ku_pcsr_reg*)ku_reg;
    
    mlxsw_reg_pcsr_offset_set(inbox, pcsr_reg->offset);


    return 0;
}

static int __PCSR_decode(u8 *outbox, void *ku_reg, void *context)
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
* IDDD
***********************************************/
static int __IDDD_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_iddd_reg *iddd_reg = (struct ku_iddd_reg*)ku_reg;
    
    mlxsw_reg_iddd_entry_type_set(inbox, iddd_reg->entry_type);
    mlxsw_reg_iddd_duplication_set(inbox, iddd_reg->duplication);


    return 0;
}

static int __IDDD_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_iddd_reg *iddd_reg = (struct ku_iddd_reg*)ku_reg;
    
    iddd_reg->entry_type = mlxsw_reg_iddd_entry_type_get(outbox);
    iddd_reg->duplication = mlxsw_reg_iddd_duplication_get(outbox);


    return 0;
}

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
static int __PMAOS_encode(u8 *inbox, void *ku_reg, void *context)
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

static int __PMAOS_decode(u8 *outbox, void *ku_reg, void *context)
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
* MCC
***********************************************/
static int __MCC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mcc_reg *mcc_reg = (struct ku_mcc_reg*)ku_reg;
    
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

static int __MCC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mcc_reg *mcc_reg = (struct ku_mcc_reg*)ku_reg;
    
    mcc_reg->time_elapsed_since_last_cmd = mlxsw_reg_mcc_time_elapsed_since_last_cmd_get(outbox);
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
static int __MCDA_encode(u8 *inbox, void *ku_reg, void *context)
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

static int __MCDA_decode(u8 *outbox, void *ku_reg, void *context)
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
