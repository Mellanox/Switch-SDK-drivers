/*
 * Copyright (c) 2021-2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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


#include <linux/mlx_sx/auto_registers/cmd_auto.h>

#include "sx_spice_access_reg_auto.h"
#include "sx_spice_tree_auto.h"

#define VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size)            \
    do {                                                                  \
        if ((snp_res == 0) || (snp_res >= buffer_length - buffer_size)) { \
            return 0;                                                     \
        }                                                                 \
    } while (0)

/************************************************
 *  Local variables
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

static LIST_HEAD(__mtcap_list_head);
static LIST_HEAD(__mvcap_list_head);
static LIST_HEAD(__mtmp_list_head);
static LIST_HEAD(__mgir_list_head);
static LIST_HEAD(__msgi_list_head);
static LIST_HEAD(__mdir_list_head);
static LIST_HEAD(__mopce_list_head);
static LIST_HEAD(__spad_list_head);
static LIST_HEAD(__spzr_list_head);
static LIST_HEAD(__ptys_list_head);
static LIST_HEAD(__ppcnt_list_head);
static LIST_HEAD(__sltp_list_head);
static LIST_HEAD(__pddr_list_head);
static LIST_HEAD(__pmdr_list_head);
static LIST_HEAD(__pphcr_list_head);
static LIST_HEAD(__sllm_list_head);


/************************************************
 *  Local function declarations
 ***********************************************/

int sx_spice_prepare_access_reg(dev_private_data_t *priv_data)
{
    int err = 0;

    mutex_lock(&priv_data->reg_access.reg_mutex);

    if (down_timeout(&priv_data->reg_access.reg_sem, msecs_to_jiffies(0)) == -ETIME) {
        pr_debug("SPICE: FW is busy, can't send SPICE query");
        err = -EBUSY;
    }

    return err;
}

void sx_spice_post_access_reg(dev_private_data_t *priv_data, bool sem_acquired)
{
    if (sem_acquired) {
        up(&priv_data->reg_access.reg_sem);
    }
    mutex_unlock(&priv_data->reg_access.reg_mutex);
}



/************************************************
 * Functions                                    *
 ***********************************************/

/* reg data to buffer print */
int sx_spice_access_reg_mtcap_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_mtcap_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "slot_index: 0x%x\n", reg_data->slot_index);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "sensor_count: 0x%x\n", reg_data->sensor_count);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "internal_sensor_count: 0x%x\n", reg_data->internal_sensor_count);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "sensor_map: 0x%llx\n", reg_data->sensor_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int sx_spice_access_reg_mvcap_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_mvcap_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "sensor_map: 0x%llx\n", reg_data->sensor_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "slot_index: 0x%x\n", reg_data->slot_index);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int sx_spice_access_reg_mtmp_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_mtmp_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "i: 0x%x\n", reg_data->i);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ig: 0x%x\n", reg_data->ig);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "asic_index: 0x%x\n", reg_data->asic_index);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "slot_index: 0x%x\n", reg_data->slot_index);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "sensor_index: 0x%x\n", reg_data->sensor_index);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "max_operational_temperature: 0x%x\n", reg_data->max_operational_temperature);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "temperature: 0x%x\n", reg_data->temperature);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "mte: 0x%x\n", reg_data->mte);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "mtr: 0x%x\n", reg_data->mtr);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "weme: 0x%x\n", reg_data->weme);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "sdme: 0x%x\n", reg_data->sdme);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "max_temperature: 0x%x\n", reg_data->max_temperature);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "tee: 0x%x\n", reg_data->tee);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "sdee: 0x%x\n", reg_data->sdee);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "temperature_threshold_hi: 0x%x\n", reg_data->temperature_threshold_hi);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "temperature_threshold_lo: 0x%x\n", reg_data->temperature_threshold_lo);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "sensor_name_hi: 0x%x\n", reg_data->sensor_name_hi);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "sensor_name_lo: 0x%x\n", reg_data->sensor_name_lo);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int sx_spice_access_reg_mgir_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_mgir_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "device_hw_revision: 0x%x\n", reg_data->hw_info.device_hw_revision);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "device_id: 0x%x\n", reg_data->hw_info.device_id);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "num_ports: 0x%x\n", reg_data->hw_info.num_ports);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "technology: 0x%x\n", reg_data->hw_info.technology);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pvs: 0x%x\n", reg_data->hw_info.pvs);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "hw_dev_id: 0x%x\n", reg_data->hw_info.hw_dev_id);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "manufacturing_base_mac: 0x%02x%02x%02x%02x%02x%02x\n", reg_data->hw_info.manufacturing_base_mac[0], reg_data->hw_info.manufacturing_base_mac[1], reg_data->hw_info.manufacturing_base_mac[2], reg_data->hw_info.manufacturing_base_mac[3], reg_data->hw_info.manufacturing_base_mac[4], reg_data->hw_info.manufacturing_base_mac[5]);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "uptime: 0x%x\n", reg_data->hw_info.uptime);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "dev_sc: 0x%x\n", reg_data->fw_info.dev_sc);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "latency_tlv: 0x%x\n", reg_data->fw_info.latency_tlv);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "string_tlv: 0x%x\n", reg_data->fw_info.string_tlv);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "dev: 0x%x\n", reg_data->fw_info.dev);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "debug: 0x%x\n", reg_data->fw_info.debug);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "signed_fw: 0x%x\n", reg_data->fw_info.signed_fw);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "secured: 0x%x\n", reg_data->fw_info.secured);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "major: 0x%x\n", reg_data->fw_info.major);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "minor: 0x%x\n", reg_data->fw_info.minor);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "sub_minor: 0x%x\n", reg_data->fw_info.sub_minor);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "build_id: 0x%x\n", reg_data->fw_info.build_id);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "month: 0x%x\n", reg_data->fw_info.month);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "day: 0x%x\n", reg_data->fw_info.day);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "year: 0x%x\n", reg_data->fw_info.year);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "hour: 0x%x\n", reg_data->fw_info.hour);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "psid: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", reg_data->fw_info.psid[0], reg_data->fw_info.psid[1], reg_data->fw_info.psid[2], reg_data->fw_info.psid[3], reg_data->fw_info.psid[4], reg_data->fw_info.psid[5], reg_data->fw_info.psid[6], reg_data->fw_info.psid[7], reg_data->fw_info.psid[8], reg_data->fw_info.psid[9], reg_data->fw_info.psid[10], reg_data->fw_info.psid[11], reg_data->fw_info.psid[12], reg_data->fw_info.psid[13], reg_data->fw_info.psid[14], reg_data->fw_info.psid[15]);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ini_file_version: 0x%x\n", reg_data->fw_info.ini_file_version);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "extended_major: 0x%x\n", reg_data->fw_info.extended_major);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "extended_minor: 0x%x\n", reg_data->fw_info.extended_minor);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "extended_sub_minor: 0x%x\n", reg_data->fw_info.extended_sub_minor);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "disabled_tiles_bitmap: 0x%x\n", reg_data->fw_info.disabled_tiles_bitmap);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "isfu_major: 0x%x\n", reg_data->fw_info.isfu_major);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "encryption: 0x%x\n", reg_data->fw_info.encryption);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "sec_boot: 0x%x\n", reg_data->fw_info.sec_boot);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "life_cycle: 0x%x\n", reg_data->fw_info.life_cycle);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "major: 0x%x\n", reg_data->sw_info.major);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "minor: 0x%x\n", reg_data->sw_info.minor);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "sub_minor: 0x%x\n", reg_data->sw_info.sub_minor);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom0_arch: 0x%x\n", reg_data->sw_info.rom0_arch);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom0_type: 0x%x\n", reg_data->sw_info.rom0_type);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom1_arch: 0x%x\n", reg_data->sw_info.rom1_arch);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom1_type: 0x%x\n", reg_data->sw_info.rom1_type);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom2_arch: 0x%x\n", reg_data->sw_info.rom2_arch);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom2_type: 0x%x\n", reg_data->sw_info.rom2_type);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom3_arch: 0x%x\n", reg_data->sw_info.rom3_arch);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom3_type: 0x%x\n", reg_data->sw_info.rom3_type);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "major: 0x%x\n", reg_data->sw_info.rom0_version.major);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "minor: 0x%x\n", reg_data->sw_info.rom0_version.minor);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "build: 0x%x\n", reg_data->sw_info.rom0_version.build);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "major: 0x%x\n", reg_data->sw_info.rom1_version.major);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "minor: 0x%x\n", reg_data->sw_info.rom1_version.minor);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "build: 0x%x\n", reg_data->sw_info.rom1_version.build);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "major: 0x%x\n", reg_data->sw_info.rom2_version.major);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "minor: 0x%x\n", reg_data->sw_info.rom2_version.minor);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "build: 0x%x\n", reg_data->sw_info.rom2_version.build);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "major: 0x%x\n", reg_data->sw_info.rom3_version.major);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "minor: 0x%x\n", reg_data->sw_info.rom3_version.minor);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "build: 0x%x\n", reg_data->sw_info.rom3_version.build);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "dev_branch_tag: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", reg_data->dev_info.dev_branch_tag[0], reg_data->dev_info.dev_branch_tag[1], reg_data->dev_info.dev_branch_tag[2], reg_data->dev_info.dev_branch_tag[3], reg_data->dev_info.dev_branch_tag[4], reg_data->dev_info.dev_branch_tag[5], reg_data->dev_info.dev_branch_tag[6], reg_data->dev_info.dev_branch_tag[7], reg_data->dev_info.dev_branch_tag[8], reg_data->dev_info.dev_branch_tag[9], reg_data->dev_info.dev_branch_tag[10], reg_data->dev_info.dev_branch_tag[11], reg_data->dev_info.dev_branch_tag[12], reg_data->dev_info.dev_branch_tag[13], reg_data->dev_info.dev_branch_tag[14], reg_data->dev_info.dev_branch_tag[15], reg_data->dev_info.dev_branch_tag[16], reg_data->dev_info.dev_branch_tag[17], reg_data->dev_info.dev_branch_tag[18], reg_data->dev_info.dev_branch_tag[19], reg_data->dev_info.dev_branch_tag[20], reg_data->dev_info.dev_branch_tag[21], reg_data->dev_info.dev_branch_tag[22], reg_data->dev_info.dev_branch_tag[23], reg_data->dev_info.dev_branch_tag[24], reg_data->dev_info.dev_branch_tag[25], reg_data->dev_info.dev_branch_tag[26], reg_data->dev_info.dev_branch_tag[27]);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int sx_spice_access_reg_msgi_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_msgi_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint32_t i = 0;

    for (i = 0; i < SXD_MSGI_SERIAL_NUMBER_NUM; i++) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "serial_number[%d]: 0x%x\n", i, reg_data->serial_number[i]);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }
    snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    for (i = 0; i < SXD_MSGI_PART_NUMBER_NUM; i++) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "part_number[%d]: 0x%x\n", i, reg_data->part_number[i]);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }
    snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "revision: 0x%x\n", reg_data->revision);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "manufacturing_date: 0x%x\n", reg_data->manufacturing_date);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    for (i = 0; i < SXD_MSGI_PRODUCT_NAME_NUM; i++) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "product_name[%d]: 0x%x\n", i, reg_data->product_name[i]);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }
    snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int sx_spice_access_reg_mdir_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_mdir_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint32_t i = 0;

    for (i = 0; i < SXD_MDIR_DEVICE_ID_NUM; i++) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "device_id[%d]: 0x%x\n", i, reg_data->device_id[i]);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }
    snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int sx_spice_access_reg_mopce_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_mopce_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint32_t i = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "num_rec: 0x%x\n", reg_data->num_rec);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    for (i = 0; i < SXD_MOPCE_PERFORMANCE_COUNTER_INFO_NUM; i++) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "hw_unit_instance: 0x%x\n", reg_data->performance_counter_info[i].hw_unit_instance);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "hw_unit_id: 0x%x\n", reg_data->performance_counter_info[i].hw_unit_id);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "counter_index: 0x%x\n", reg_data->performance_counter_info[i].counter_index);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "hw_unit_sub_instance: 0x%x\n", reg_data->performance_counter_info[i].hw_unit_sub_instance);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "counter_value: 0x%llx\n", reg_data->performance_counter_info[i].counter_value);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }

    return buffer_size;
}

int sx_spice_access_reg_spad_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_spad_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "base_mac: 0x%02x%02x%02x%02x%02x%02x\n", reg_data->base_mac[0], reg_data->base_mac[1], reg_data->base_mac[2], reg_data->base_mac[3], reg_data->base_mac[4], reg_data->base_mac[5]);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int sx_spice_access_reg_spzr_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_spzr_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "swid: 0x%x\n", reg_data->swid);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "router_entity: 0x%x\n", reg_data->router_entity);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "enh_sw_p0: 0x%x\n", reg_data->enh_sw_p0);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "capability_mask: 0x%x\n", reg_data->capability_mask);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "system_image_guid_h: 0x%x\n", reg_data->system_image_guid_h);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "system_image_guid_l: 0x%x\n", reg_data->system_image_guid_l);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "guid0_h: 0x%x\n", reg_data->guid0_h);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "guid0_l: 0x%x\n", reg_data->guid0_l);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "node_guid_h: 0x%x\n", reg_data->node_guid_h);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "node_guid_l: 0x%x\n", reg_data->node_guid_l);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "capability_mask2: 0x%x\n", reg_data->capability_mask2);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "max_pkey: 0x%x\n", reg_data->max_pkey);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "node_description: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", reg_data->node_description[0], reg_data->node_description[1], reg_data->node_description[2], reg_data->node_description[3], reg_data->node_description[4], reg_data->node_description[5], reg_data->node_description[6], reg_data->node_description[7], reg_data->node_description[8], reg_data->node_description[9], reg_data->node_description[10], reg_data->node_description[11], reg_data->node_description[12], reg_data->node_description[13], reg_data->node_description[14], reg_data->node_description[15], reg_data->node_description[16], reg_data->node_description[17], reg_data->node_description[18], reg_data->node_description[19], reg_data->node_description[20], reg_data->node_description[21], reg_data->node_description[22], reg_data->node_description[23], reg_data->node_description[24], reg_data->node_description[25], reg_data->node_description[26], reg_data->node_description[27], reg_data->node_description[28], reg_data->node_description[29], reg_data->node_description[30], reg_data->node_description[31], reg_data->node_description[32], reg_data->node_description[33], reg_data->node_description[34], reg_data->node_description[35], reg_data->node_description[36], reg_data->node_description[37], reg_data->node_description[38], reg_data->node_description[39], reg_data->node_description[40], reg_data->node_description[41], reg_data->node_description[42], reg_data->node_description[43], reg_data->node_description[44], reg_data->node_description[45], reg_data->node_description[46], reg_data->node_description[47], reg_data->node_description[48], reg_data->node_description[49], reg_data->node_description[50], reg_data->node_description[51], reg_data->node_description[52], reg_data->node_description[53], reg_data->node_description[54], reg_data->node_description[55], reg_data->node_description[56], reg_data->node_description[57], reg_data->node_description[58], reg_data->node_description[59], reg_data->node_description[60], reg_data->node_description[61], reg_data->node_description[62], reg_data->node_description[63]);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int sx_spice_access_reg_ptys_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_ptys_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "reserved_high: 0x%x\n", reg_data->reserved_high);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "an_disable_admin: 0x%x\n", reg_data->an_disable_admin);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "an_disable_cap: 0x%x\n", reg_data->an_disable_cap);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_ready_e: 0x%x\n", reg_data->tx_ready_e);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "force_tx_aba_param: 0x%x\n", reg_data->force_tx_aba_param);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->local_port, reg_data->lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->pnat);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "port_type: 0x%x\n", reg_data->port_type);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "plane_ind: 0x%x\n", reg_data->plane_ind);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "transmit_allowed: 0x%x\n", reg_data->transmit_allowed);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "proto_mask: 0x%x\n", reg_data->proto_mask);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "an_status: 0x%x\n", reg_data->an_status);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "max_port_rate: 0x%x\n", reg_data->max_port_rate);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "data_rate_oper: 0x%x\n", reg_data->data_rate_oper);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ext_eth_proto_capability: 0x%x\n", reg_data->ext_eth_proto_capability);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_proto_capability: 0x%x\n", reg_data->eth_proto_capability);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_link_width_capability: 0x%x\n", reg_data->ib_link_width_capability);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_proto_capability: 0x%x\n", reg_data->ib_proto_capability);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ext_eth_proto_admin: 0x%x\n", reg_data->ext_eth_proto_admin);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_proto_admin: 0x%x\n", reg_data->eth_proto_admin);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_link_width_admin: 0x%x\n", reg_data->ib_link_width_admin);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_proto_admin: 0x%x\n", reg_data->ib_proto_admin);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ext_eth_proto_oper: 0x%x\n", reg_data->ext_eth_proto_oper);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_proto_oper: 0x%x\n", reg_data->eth_proto_oper);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_link_width_oper: 0x%x\n", reg_data->ib_link_width_oper);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_proto_oper: 0x%x\n", reg_data->ib_proto_oper);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "xdr_2x_slow_cap: 0x%x\n", reg_data->xdr_2x_slow_cap);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "force_lt_frames_cap: 0x%x\n", reg_data->force_lt_frames_cap);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "force_lt_frames_admin: 0x%x\n", reg_data->force_lt_frames_admin);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ext_eth_proto_lp_valid: 0x%x\n", reg_data->ext_eth_proto_lp_valid);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_proto_lp_valid: 0x%x\n", reg_data->eth_proto_lp_valid);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "xdr_2x_slow_admin: 0x%x\n", reg_data->xdr_2x_slow_admin);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "xdr_2x_slow_active: 0x%x\n", reg_data->xdr_2x_slow_active);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane_rate_oper: 0x%x\n", reg_data->lane_rate_oper);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "connector_type: 0x%x\n", reg_data->connector_type);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    switch (reg_data->proto_mask) {
    case SXD_PTYS_PROTO_MASK_INFINIBAND_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_partner_protocol_extended_ib: 0x%x\n", reg_data->lp_advertised_proto_ext.ptys_lp_ext_ib.link_partner_protocol_extended_ib);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PTYS_PROTO_MASK_RESERVED_E:
        break;

    case SXD_PTYS_PROTO_MASK_ETHERNET_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_partner_protocol_extended_eth: 0x%x\n", reg_data->lp_advertised_proto_ext.ptys_lp_ext_eth.link_partner_protocol_extended_eth);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    default:
        /* Other types not supported yet */
        break;
    }
    snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_proto_lp_advertise: 0x%x\n", reg_data->eth_proto_lp_advertise);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "proprietary_nvda_proto_cap: 0x%x\n", reg_data->proprietary_nvda_proto_cap);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "proprietary_nvda_proto_admin: 0x%x\n", reg_data->proprietary_nvda_proto_admin);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "proprietary_nvda_proto_oper: 0x%x\n", reg_data->proprietary_nvda_proto_oper);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int sx_spice_access_reg_ppcnt_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_ppcnt_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint32_t i = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "swid: 0x%x\n", reg_data->swid);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->local_port, reg_data->lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->pnat);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "port_type: 0x%x\n", reg_data->port_type);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "grp: 0x%x\n", reg_data->grp);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "clr: 0x%x\n", reg_data->clr);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lp_gl: 0x%x\n", reg_data->lp_gl);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "grp_profile: 0x%x\n", reg_data->grp_profile);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "prio_tc: 0x%x\n", reg_data->prio_tc);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    switch (reg_data->grp) {
    case SXD_PPCNT_GRP_IEEE_802_3_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frames_transmitted_ok_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_frames_transmitted_ok_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frames_transmitted_ok_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_frames_transmitted_ok_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frames_received_ok_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_frames_received_ok_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frames_received_ok_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_frames_received_ok_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frame_check_sequence_errors_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_frame_check_sequence_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frame_check_sequence_errors_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_frame_check_sequence_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_alignment_errors_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_alignment_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_alignment_errors_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_alignment_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_octets_transmitted_ok_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_octets_transmitted_ok_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_octets_transmitted_ok_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_octets_transmitted_ok_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_octets_received_ok_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_octets_received_ok_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_octets_received_ok_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_octets_received_ok_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_multicast_frames_xmitted_ok_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_multicast_frames_xmitted_ok_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_multicast_frames_xmitted_ok_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_multicast_frames_xmitted_ok_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_broadcast_frames_xmitted_ok_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_broadcast_frames_xmitted_ok_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_broadcast_frames_xmitted_ok_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_broadcast_frames_xmitted_ok_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_multicast_frames_received_ok_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_multicast_frames_received_ok_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_multicast_frames_received_ok_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_multicast_frames_received_ok_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_broadcast_frames_received_ok_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_broadcast_frames_received_ok_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_broadcast_frames_received_ok_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_broadcast_frames_received_ok_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_in_range_length_errors_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_in_range_length_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_in_range_length_errors_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_in_range_length_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_out_of_range_length_field_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_out_of_range_length_field_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_out_of_range_length_field_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_out_of_range_length_field_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frame_too_long_errors_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_frame_too_long_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frame_too_long_errors_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_frame_too_long_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_symbol_error_during_carrier_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_symbol_error_during_carrier_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_symbol_error_during_carrier_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_symbol_error_during_carrier_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_mac_control_frames_transmitted_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_mac_control_frames_transmitted_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_mac_control_frames_transmitted_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_mac_control_frames_transmitted_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_mac_control_frames_received_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_mac_control_frames_received_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_mac_control_frames_received_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_mac_control_frames_received_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_unsupported_opcodes_received_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_unsupported_opcodes_received_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_unsupported_opcodes_received_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_unsupported_opcodes_received_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_pause_mac_ctrl_frames_received_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_pause_mac_ctrl_frames_received_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_pause_mac_ctrl_frames_received_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_pause_mac_ctrl_frames_received_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_pause_mac_ctrl_frames_transmitted_high: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_pause_mac_ctrl_frames_transmitted_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_pause_mac_ctrl_frames_transmitted_low: 0x%x\n", reg_data->counter_set.eth_802_3_cntrs_grp_data_layout.a_pause_mac_ctrl_frames_transmitted_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_RFC_2863_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_octets_high: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_in_octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_octets_low: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_in_octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_ucast_pkts_high: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_in_ucast_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_ucast_pkts_low: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_in_ucast_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_discards_high: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_in_discards_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_discards_low: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_in_discards_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_errors_high: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_in_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_errors_low: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_in_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_unknown_protos_high: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_in_unknown_protos_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_unknown_protos_low: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_in_unknown_protos_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_octets_high: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_out_octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_octets_low: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_out_octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_ucast_pkts_high: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_out_ucast_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_ucast_pkts_low: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_out_ucast_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_discards_high: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_out_discards_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_discards_low: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_out_discards_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_errors_high: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_out_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_errors_low: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_out_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_multicast_pkts_high: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_in_multicast_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_multicast_pkts_low: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_in_multicast_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_broadcast_pkts_high: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_in_broadcast_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_broadcast_pkts_low: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_in_broadcast_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_multicast_pkts_high: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_out_multicast_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_multicast_pkts_low: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_out_multicast_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_broadcast_pkts_high: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_out_broadcast_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_broadcast_pkts_low: 0x%x\n", reg_data->counter_set.eth_2863_cntrs_grp_data_layout.if_out_broadcast_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_RFC_2819_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_drop_events_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_drop_events_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_drop_events_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_drop_events_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_octets_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_octets_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_broadcast_pkts_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_broadcast_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_broadcast_pkts_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_broadcast_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_multicast_pkts_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_multicast_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_multicast_pkts_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_multicast_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_crc_align_errors_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_crc_align_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_crc_align_errors_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_crc_align_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_undersize_pkts_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_undersize_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_undersize_pkts_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_undersize_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_oversize_pkts_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_oversize_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_oversize_pkts_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_oversize_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_fragments_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_fragments_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_fragments_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_fragments_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_jabbers_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_jabbers_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_jabbers_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_jabbers_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_collisions_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_collisions_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_collisions_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_collisions_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts64octets_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts64octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts64octets_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts64octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts65to127octets_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts65to127octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts65to127octets_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts65to127octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts128to255octets_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts128to255octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts128to255octets_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts128to255octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts256to511octets_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts256to511octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts256to511octets_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts256to511octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts512to1023octets_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts512to1023octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts512to1023octets_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts512to1023octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts1024to1518octets_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts1024to1518octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts1024to1518octets_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts1024to1518octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts1519to2047octets_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts1519to2047octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts1519to2047octets_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts1519to2047octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts2048to4095octets_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts2048to4095octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts2048to4095octets_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts2048to4095octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts4096to8191octets_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts4096to8191octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts4096to8191octets_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts4096to8191octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts8192to10239octets_high: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts8192to10239octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts8192to10239octets_low: 0x%x\n", reg_data->counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts8192to10239octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_RFC_3635_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_alignment_errors_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_alignment_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_alignment_errors_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_alignment_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_fcs_errors_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_fcs_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_fcs_errors_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_fcs_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_single_collision_frames_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_single_collision_frames_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_single_collision_frames_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_single_collision_frames_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_multiple_collision_frames_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_multiple_collision_frames_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_multiple_collision_frames_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_multiple_collision_frames_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_sqe_test_errors_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_sqe_test_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_sqe_test_errors_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_sqe_test_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_deferred_transmissions_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_deferred_transmissions_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_deferred_transmissions_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_deferred_transmissions_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_late_collisions_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_late_collisions_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_late_collisions_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_late_collisions_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_excessive_collisions_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_excessive_collisions_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_excessive_collisions_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_excessive_collisions_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_internal_mac_transmit_errors_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_transmit_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_internal_mac_transmit_errors_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_transmit_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_carrier_sense_errors_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_carrier_sense_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_carrier_sense_errors_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_carrier_sense_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_frame_too_longs_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_frame_too_longs_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_frame_too_longs_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_frame_too_longs_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_internal_mac_receive_errors_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_receive_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_internal_mac_receive_errors_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_receive_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_symbol_errors_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_symbol_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_symbol_errors_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_symbol_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3control_in_unknown_opcodes_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3control_in_unknown_opcodes_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3control_in_unknown_opcodes_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3control_in_unknown_opcodes_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3in_pause_frames_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3in_pause_frames_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3in_pause_frames_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3in_pause_frames_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3out_pause_frames_high: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3out_pause_frames_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3out_pause_frames_low: 0x%x\n", reg_data->counter_set.eth_3635_cntrs_grp_data_layout.dot3out_pause_frames_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_ETHERNET_EXTENDED_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_transmit_wait_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.port_transmit_wait_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_transmit_wait_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.port_transmit_wait_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ecn_marked_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.ecn_marked_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ecn_marked_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.ecn_marked_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "no_buffer_discard_mc_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.no_buffer_discard_mc_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "no_buffer_discard_mc_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.no_buffer_discard_mc_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_ebp_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.rx_ebp_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_ebp_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.rx_ebp_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_ebp_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_ebp_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_ebp_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_ebp_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_buffer_almost_full_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.rx_buffer_almost_full_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_buffer_almost_full_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.rx_buffer_almost_full_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_buffer_full_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.rx_buffer_full_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_buffer_full_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.rx_buffer_full_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_icrc_encapsulated_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.rx_icrc_encapsulated_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_icrc_encapsulated_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.rx_icrc_encapsulated_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts64octets_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts64octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts64octets_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts64octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts65to127octets_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts65to127octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts65to127octets_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts65to127octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts128to255octets_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts128to255octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts128to255octets_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts128to255octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts256to511octets_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts256to511octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts256to511octets_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts256to511octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts512to1023octets_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts512to1023octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts512to1023octets_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts512to1023octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts1024to1518octets_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts1024to1518octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts1024to1518octets_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts1024to1518octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts1519to2047octets_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts1519to2047octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts1519to2047octets_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts1519to2047octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts2048to4095octets_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts2048to4095octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts2048to4095octets_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts2048to4095octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts4096to8191octets_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts4096to8191octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts4096to8191octets_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts4096to8191octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts8192to10239octets_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts8192to10239octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts8192to10239octets_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts8192to10239octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ece_marked_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.ece_marked_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ece_marked_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.ece_marked_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_int_cksm_err_high: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_int_cksm_err_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_int_cksm_err_low: 0x%x\n", reg_data->counter_set.eth_extended_cntrs_grp_data_layout.tx_int_cksm_err_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_ETHERNET_DISCARD_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_general_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.ingress_general_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_general_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.ingress_general_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_policy_engine_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.ingress_policy_engine_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_policy_engine_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.ingress_policy_engine_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_vlan_membership_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.ingress_vlan_membership_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_vlan_membership_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.ingress_vlan_membership_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_tag_frame_type_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.ingress_tag_frame_type_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_tag_frame_type_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.ingress_tag_frame_type_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_vlan_membership_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.egress_vlan_membership_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_vlan_membership_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.egress_vlan_membership_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "loopback_filter_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.loopback_filter_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "loopback_filter_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.loopback_filter_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_general_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.egress_general_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_general_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.egress_general_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_hoq_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.egress_hoq_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_hoq_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.egress_hoq_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_isolation_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.port_isolation_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_isolation_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.port_isolation_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_policy_engine_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.egress_policy_engine_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_policy_engine_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.egress_policy_engine_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_tx_link_down_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.ingress_tx_link_down_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_tx_link_down_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.ingress_tx_link_down_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_stp_filter_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.egress_stp_filter_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_stp_filter_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.egress_stp_filter_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_hoq_stall_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.egress_hoq_stall_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_hoq_stall_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.egress_hoq_stall_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_sll_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.egress_sll_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_sll_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.egress_sll_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_discard_all_high: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.ingress_discard_all_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_discard_all_low: 0x%x\n", reg_data->counter_set.eth_discard_cntrs_grp.ingress_discard_all_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_LINK_LEVEL_RETRANSMISSION_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_rx_cells_high: 0x%x\n", reg_data->counter_set.link_level_retrans_cntr_grp_data.llr_rx_cells_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_rx_cells_low: 0x%x\n", reg_data->counter_set.link_level_retrans_cntr_grp_data.llr_rx_cells_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_rx_error_high: 0x%x\n", reg_data->counter_set.link_level_retrans_cntr_grp_data.llr_rx_error_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_rx_error_low: 0x%x\n", reg_data->counter_set.link_level_retrans_cntr_grp_data.llr_rx_error_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_rx_crc_error_high: 0x%x\n", reg_data->counter_set.link_level_retrans_cntr_grp_data.llr_rx_crc_error_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_rx_crc_error_low: 0x%x\n", reg_data->counter_set.link_level_retrans_cntr_grp_data.llr_rx_crc_error_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_tx_cells_high: 0x%x\n", reg_data->counter_set.link_level_retrans_cntr_grp_data.llr_tx_cells_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_tx_cells_low: 0x%x\n", reg_data->counter_set.link_level_retrans_cntr_grp_data.llr_tx_cells_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_tx_ret_cells_high: 0x%x\n", reg_data->counter_set.link_level_retrans_cntr_grp_data.llr_tx_ret_cells_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_tx_ret_cells_low: 0x%x\n", reg_data->counter_set.link_level_retrans_cntr_grp_data.llr_tx_ret_cells_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_tx_ret_events_high: 0x%x\n", reg_data->counter_set.link_level_retrans_cntr_grp_data.llr_tx_ret_events_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_tx_ret_events_low: 0x%x\n", reg_data->counter_set.link_level_retrans_cntr_grp_data.llr_tx_ret_events_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PER_PRIORITY_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_octets_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_octets_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_uc_frames_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_uc_frames_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_uc_frames_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_uc_frames_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_mc_frames_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_mc_frames_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_mc_frames_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_mc_frames_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_bc_frames_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_bc_frames_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_bc_frames_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_bc_frames_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_frames_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_frames_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_frames_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_frames_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_octets_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.tx_octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_octets_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.tx_octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_uc_frames_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.tx_uc_frames_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_uc_frames_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.tx_uc_frames_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_mc_frames_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.tx_mc_frames_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_mc_frames_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.tx_mc_frames_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bc_frames_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.tx_bc_frames_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bc_frames_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.tx_bc_frames_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_frames_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.tx_frames_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_frames_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.tx_frames_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_pause_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_pause_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_pause_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_pause_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_pause_duration_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_pause_duration_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_pause_duration_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_pause_duration_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_pause_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.tx_pause_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_pause_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.tx_pause_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_pause_duration_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.tx_pause_duration_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_pause_duration_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.tx_pause_duration_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_pause_transition_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_pause_transition_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_pause_transition_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_pause_transition_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_discards_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_discards_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_discards_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.rx_discards_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "device_stall_minor_watermark_cnt_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.device_stall_minor_watermark_cnt_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "device_stall_minor_watermark_cnt_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.device_stall_minor_watermark_cnt_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "device_stall_critical_watermark_cnt_high: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.device_stall_critical_watermark_cnt_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "device_stall_critical_watermark_cnt_low: 0x%x\n", reg_data->counter_set.eth_per_prio_grp_data_layout.device_stall_critical_watermark_cnt_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PER_TRAFFIC_CLASS_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "transmit_queue_high: 0x%x\n", reg_data->counter_set.eth_per_traffic_class_layout.transmit_queue_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "transmit_queue_low: 0x%x\n", reg_data->counter_set.eth_per_traffic_class_layout.transmit_queue_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "no_buffer_discard_uc_high: 0x%x\n", reg_data->counter_set.eth_per_traffic_class_layout.no_buffer_discard_uc_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "no_buffer_discard_uc_low: 0x%x\n", reg_data->counter_set.eth_per_traffic_class_layout.no_buffer_discard_uc_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PHYSICAL_LAYER_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.time_since_last_clear_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.time_since_last_clear_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_errors_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.symbol_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_errors_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.symbol_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "sync_headers_errors_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.sync_headers_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "sync_headers_errors_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.sync_headers_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane0_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.edpl_bip_errors_lane0_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane0_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.edpl_bip_errors_lane0_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane1_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.edpl_bip_errors_lane1_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane1_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.edpl_bip_errors_lane1_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane2_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.edpl_bip_errors_lane2_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane2_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.edpl_bip_errors_lane2_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane3_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.edpl_bip_errors_lane3_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane3_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.edpl_bip_errors_lane3_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane0_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane0_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane0_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane0_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane1_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane1_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane1_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane1_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane2_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane2_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane2_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane2_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane3_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane3_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane3_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane3_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane0_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane0_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane0_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane0_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane1_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane1_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane1_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane1_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane2_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane2_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane2_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane2_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane3_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane3_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane3_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane3_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_blocks_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_blocks_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_blocks_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_blocks_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_uncorrectable_blocks_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_uncorrectable_blocks_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_uncorrectable_blocks_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_uncorrectable_blocks_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_no_errors_blocks_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_no_errors_blocks_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_no_errors_blocks_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_no_errors_blocks_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_single_error_blocks_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_single_error_blocks_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_single_error_blocks_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_single_error_blocks_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_total_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_total_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_total_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_total_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane0_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane0_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane0_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane0_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane1_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane1_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane1_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane1_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane2_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane2_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane2_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane2_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane3_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane3_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane3_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane3_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_down_events: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.link_down_events);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "successful_recovery_events: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.successful_recovery_events);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane4_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane4_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane4_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane4_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane5_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane5_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane5_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane5_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane6_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane6_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane6_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane6_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane7_high: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane7_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane7_low: 0x%x\n", reg_data->counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane7_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PER_TRAFFIC_CLASS_CONGESTION_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "wred_discard_high: 0x%x\n", reg_data->counter_set.eth_per_traffic_class_cong_layout.wred_discard_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "wred_discard_low: 0x%x\n", reg_data->counter_set.eth_per_traffic_class_cong_layout.wred_discard_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ecn_marked_tc_high: 0x%x\n", reg_data->counter_set.eth_per_traffic_class_cong_layout.ecn_marked_tc_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ecn_marked_tc_low: 0x%x\n", reg_data->counter_set.eth_per_traffic_class_cong_layout.ecn_marked_tc_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PER_RECEIVE_BUFFER_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_no_buffer_discard_uc_high: 0x%x\n", reg_data->counter_set.eth_per_receive_buffer_grp.rx_no_buffer_discard_uc_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_no_buffer_discard_uc_low: 0x%x\n", reg_data->counter_set.eth_per_receive_buffer_grp.rx_no_buffer_discard_uc_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PHYSICAL_LAYER_STATISTICAL_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_high: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.time_since_last_clear_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_low: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.time_since_last_clear_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_received_bits_high: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_received_bits_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_received_bits_low: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_received_bits_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_symbol_errors_high: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_symbol_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_symbol_errors_low: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_symbol_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_corrected_bits_high: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_corrected_bits_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_corrected_bits_low: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_corrected_bits_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane0_high: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane0_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane0_low: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane0_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane1_high: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane1_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane1_low: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane1_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane2_high: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane2_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane2_low: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane2_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane3_high: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane3_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane3_low: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane3_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane4_high: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane4_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane4_low: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane4_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane5_high: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane5_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane5_low: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane5_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane6_high: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane6_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane6_low: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane6_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane7_high: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane7_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane7_low: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane7_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_float: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_float);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "effective_ber_magnitude: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.effective_ber_magnitude);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "effective_ber_coef_float: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.effective_ber_coef_float);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "effective_ber_coef: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.effective_ber_coef);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_ber_magnitude: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.symbol_ber_magnitude);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_ber_coef_float: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.symbol_ber_coef_float);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_ber_coef: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.symbol_ber_coef);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane0: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_float_lane0: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_float_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane0: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane1: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_float_lane1: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_float_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane1: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane2: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_float_lane2: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_float_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane2: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane3: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_float_lane3: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_float_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane3: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane4: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_float_lane4: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_float_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane4: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane5: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_float_lane5: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_float_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane5: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane6: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_float_lane6: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_float_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane6: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane7: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_float_lane7: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_float_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane7: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_effective_errors_high: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_effective_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_effective_errors_low: 0x%x\n", reg_data->counter_set.phys_layer_stat_cntrs.phy_effective_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_OUT_OF_BAND_PORT_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_ucast_pkts_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.if_in_ucast_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_ucast_pkts_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.if_in_ucast_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_octets_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.if_in_octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_octets_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.if_in_octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_discards_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.if_in_discards_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_discards_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.if_in_discards_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_errors_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.if_in_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_errors_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.if_in_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_crc_align_errors_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.ether_stats_crc_align_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_crc_align_errors_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.ether_stats_crc_align_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_undersize_pkts_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.ether_stats_undersize_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_undersize_pkts_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.ether_stats_undersize_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_oversize_pkts_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.ether_stats_oversize_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_oversize_pkts_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.ether_stats_oversize_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_symbol_errors_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.dot3stats_symbol_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_symbol_errors_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.dot3stats_symbol_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3in_pause_frames_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.dot3in_pause_frames_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3in_pause_frames_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.dot3in_pause_frames_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3control_in_unknown_opcodes_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.dot3control_in_unknown_opcodes_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3control_in_unknown_opcodes_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.dot3control_in_unknown_opcodes_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_ucast_pkts_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.if_out_ucast_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_ucast_pkts_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.if_out_ucast_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_octets_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.if_out_octets_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_octets_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.if_out_octets_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3out_pause_frames_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.dot3out_pause_frames_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3out_pause_frames_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.dot3out_pause_frames_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_errors_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.if_out_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_errors_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.if_out_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_time_since_last_clear_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.phy_time_since_last_clear_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_time_since_last_clear_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.phy_time_since_last_clear_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_received_bits_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.phy_received_bits_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_received_bits_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.phy_received_bits_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_symbol_errors_high: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.phy_symbol_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_symbol_errors_low: 0x%x\n", reg_data->counter_set.eth_oob_port_cntrs.phy_symbol_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_INFINIBAND_PORT_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_error_counter: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.symbol_error_counter);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_error_recovery_counter: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.link_error_recovery_counter);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_downed_counter: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.link_downed_counter);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_errors: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.port_rcv_errors);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_remote_physical_errors: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.port_rcv_remote_physical_errors);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_switch_relay_errors: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.port_rcv_switch_relay_errors);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_discards: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.port_xmit_discards);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_constraint_errors: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.port_xmit_constraint_errors);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_constraint_errors: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.port_rcv_constraint_errors);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_link_integrity_errors: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.local_link_integrity_errors);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "excessive_buffer_overrun_errors: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.excessive_buffer_overrun_errors);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "qp1_dropped: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.qp1_dropped);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vl_15_dropped: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.vl_15_dropped);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_data: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.port_xmit_data);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_data: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.port_rcv_data);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_pkts: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.port_xmit_pkts);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_pkts: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.port_rcv_pkts);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_wait: 0x%x\n", reg_data->counter_set.ib_portcntrs_attribute_grp_data.port_xmit_wait);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_INFINIBAND_EXTENDED_PORT_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_error_counter_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.symbol_error_counter_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_error_counter_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.symbol_error_counter_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_error_recovery_counter_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.link_error_recovery_counter_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_error_recovery_counter_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.link_error_recovery_counter_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_downed_counter_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.link_downed_counter_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_downed_counter_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.link_downed_counter_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_errors_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_errors_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_remote_physical_errors_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_remote_physical_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_remote_physical_errors_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_remote_physical_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_switch_relay_errors_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_switch_relay_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_switch_relay_errors_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_switch_relay_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_discards_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_discards_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_discards_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_discards_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_constraint_errors_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_constraint_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_constraint_errors_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_constraint_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_constraint_errors_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_constraint_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_constraint_errors_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_constraint_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_link_integrity_errors_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.local_link_integrity_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_link_integrity_errors_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.local_link_integrity_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "excessive_buffer_overrun_errors_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.excessive_buffer_overrun_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "excessive_buffer_overrun_errors_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.excessive_buffer_overrun_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vl_15_dropped_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.vl_15_dropped_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vl_15_dropped_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.vl_15_dropped_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_data_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_data_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_data_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_data_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_data_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_data_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_data_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_data_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_pkts_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_pkts_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_pkts_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_pkts_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_rcv_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_wait_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_wait_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_wait_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_xmit_wait_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "qp1_dropped_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.qp1_dropped_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "qp1_dropped_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.qp1_dropped_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_unicast_xmit_pkts_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_unicast_xmit_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_unicast_xmit_pkts_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_unicast_xmit_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_multicast_xmit_pkts_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_multicast_xmit_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_multicast_xmit_pkts_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_multicast_xmit_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_unicast_rcv_pkts_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_unicast_rcv_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_unicast_rcv_pkts_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_unicast_rcv_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_multicast_rcv_pkts_high: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_multicast_rcv_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_multicast_rcv_pkts_low: 0x%x\n", reg_data->counter_set.ib_long_portcntrs_attribute_grp_data.port_multicast_rcv_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PLR_COUNTERS_GROUP_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rcv_codes_high: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_rcv_codes_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rcv_codes_low: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_rcv_codes_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rcv_code_err_high: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_rcv_code_err_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rcv_code_err_low: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_rcv_code_err_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rcv_uncorrectable_code_high: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_rcv_uncorrectable_code_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rcv_uncorrectable_code_low: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_rcv_uncorrectable_code_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_codes_high: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_xmit_codes_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_codes_low: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_xmit_codes_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_retry_codes_high: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_xmit_retry_codes_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_retry_codes_low: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_xmit_retry_codes_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_retry_events_high: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_xmit_retry_events_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_retry_events_low: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_xmit_retry_events_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_sync_events_high: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_sync_events_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_sync_events_low: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_sync_events_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_codes_loss_high: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_codes_loss_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_codes_loss_low: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_codes_loss_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_retry_events_within_t_sec_max_high: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_xmit_retry_events_within_t_sec_max_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_retry_events_within_t_sec_max_low: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.plr_xmit_retry_events_within_t_sec_max_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_high: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.time_since_last_clear_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_low: 0x%x\n", reg_data->counter_set.ppcnt_plr_counters.time_since_last_clear_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_RS_FEC_HISTOGRAM_GROUP_E:
        for (i = 0; i < SXD_PPCNT_HIST_NUM; i++) {
            snp_res = snprintf(buffer, buffer_length - buffer_size, "hist[%d]: 0x%llx\n", i, reg_data->counter_set.ppcnt_rs_fec_histograms_counters.hist[i]);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_USR_XSR_PHYSICAL_LAYER_COUNTERS_GROUP_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.time_since_last_clear_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.time_since_last_clear_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane0_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane0_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane0_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane0_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane1_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane1_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane1_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane1_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane2_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane2_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane2_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane2_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane3_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane3_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane3_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane3_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane4_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane4_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane4_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane4_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane5_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane5_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane5_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane5_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane6_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane6_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane6_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane6_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane7_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane7_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane7_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane7_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane0_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane0_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane0_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane0_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane1_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane1_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane1_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane1_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane2_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane2_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane2_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane2_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane3_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane3_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane3_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane3_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane4_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane4_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane4_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane4_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane5_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane5_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane5_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane5_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane6_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane6_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane6_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane6_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane7_high: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane7_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane7_low: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane7_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_down_events: 0x%x\n", reg_data->counter_set.usr_xsr_physical_layer.link_down_events);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_INFINIBAND_PKTS_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.time_since_last_clear_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.time_since_last_clear_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_unicast_xmit_pkts_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_unicast_xmit_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_unicast_xmit_pkts_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_unicast_xmit_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_unicast_rcv_pkts_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_unicast_rcv_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_unicast_rcv_pkts_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_unicast_rcv_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "sync_header_error_counter_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.sync_header_error_counter_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "sync_header_error_counter_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.sync_header_error_counter_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_local_physical_errors_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_local_physical_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_local_physical_errors_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_local_physical_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_malformed_packet_errors_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_malformed_packet_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_malformed_packet_errors_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_malformed_packet_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_buffer_overrun_errors_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_buffer_overrun_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_buffer_overrun_errors_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_buffer_overrun_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_dlid_mapping_errors_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_dlid_mapping_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_dlid_mapping_errors_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_dlid_mapping_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_vl_mapping_errors_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_vl_mapping_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_vl_mapping_errors_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_vl_mapping_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_looping_errors_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_looping_errors_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_looping_errors_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_looping_errors_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_inactive_discards_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_inactive_discards_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_inactive_discards_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_inactive_discards_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_neighbor_mtu_discards_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_neighbor_mtu_discards_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_neighbor_mtu_discards_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packets_counter.port_neighbor_mtu_discards_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_INFINIBAND_GENERAL_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_data_qword_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.port_rcv_data_qword_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_data_qword_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.port_rcv_data_qword_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_data_qword_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.port_xmit_data_qword_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_data_qword_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.port_xmit_data_qword_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rq_general_error_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.rq_general_error_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rq_general_error_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.rq_general_error_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_ebp_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.port_xmit_ebp_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_ebp_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.port_xmit_ebp_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_sw_hoq_lifetime_limit_discards_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.port_sw_hoq_lifetime_limit_discards_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_sw_hoq_lifetime_limit_discards_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.port_sw_hoq_lifetime_limit_discards_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dqs2llu_xmit_wait_arb_global_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.dqs2llu_xmit_wait_arb_global_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dqs2llu_xmit_wait_arb_global_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.dqs2llu_xmit_wait_arb_global_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "grxb_fecn_mark_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.grxb_fecn_mark_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "grxb_fecn_mark_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.grxb_fecn_mark_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "general_transmit_discard_external_contain_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.general_transmit_discard_external_contain_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "general_transmit_discard_external_contain_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_general_counter.general_transmit_discard_external_contain_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_L1_GENERAL_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_entry_quiet_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_entry_quiet_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_entry_quiet_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_entry_quiet_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_force_entry_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_force_entry_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_force_entry_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_force_entry_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_exit_local_desired_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_exit_local_desired_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_exit_local_desired_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_exit_local_desired_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_exit_local_recal_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_exit_local_recal_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_exit_local_recal_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_exit_local_recal_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_exit_local_recal_with_traffic_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_exit_local_recal_with_traffic_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_exit_local_recal_with_traffic_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_exit_local_recal_with_traffic_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_exit_local_recal_without_traffic_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_exit_local_recal_without_traffic_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_exit_local_recal_without_traffic_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_exit_local_recal_without_traffic_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_exit_remote_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_exit_remote_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_exit_remote_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_exit_remote_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_exit_remote_probably_recal_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_exit_remote_probably_recal_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_exit_remote_probably_recal_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_exit_remote_probably_recal_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_full_bw_exit_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.local_full_bw_exit_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_full_bw_exit_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.local_full_bw_exit_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_low_power_enter_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.local_low_power_enter_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_low_power_enter_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.local_low_power_enter_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "remote_full_bw_exit_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.remote_full_bw_exit_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "remote_full_bw_exit_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.remote_full_bw_exit_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "remote_low_power_enter_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.remote_low_power_enter_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "remote_low_power_enter_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.remote_low_power_enter_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_low_power_exit_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.local_low_power_exit_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_low_power_exit_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.local_low_power_exit_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_full_bw_enter_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.local_full_bw_enter_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_full_bw_enter_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.local_full_bw_enter_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "remote_low_power_exit_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.remote_low_power_exit_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "remote_low_power_exit_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.remote_low_power_exit_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "remote_full_bw_enter_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.remote_full_bw_enter_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "remote_full_bw_enter_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.remote_full_bw_enter_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "high_speed_steady_state_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.high_speed_steady_state_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "high_speed_steady_state_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.high_speed_steady_state_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_steady_state_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_steady_state_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "l1_steady_state_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.l1_steady_state_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "other_state_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.other_state_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "other_state_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.other_state_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_high: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.time_since_last_clear_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_low: 0x%x\n", reg_data->counter_set.ppcnt_l1_general_counters.time_since_last_clear_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_INFINIBAND_PACKET_SIZE_HISTOGRAM_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r8_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r8_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r8_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r8_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r16_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r16_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r16_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r16_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r_16_24_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r_16_24_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r_16_24_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r_16_24_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r_25_32_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r_25_32_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r_25_32_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r_25_32_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r_33_64_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r_33_64_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r_33_64_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r_33_64_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r_65_128_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r_65_128_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r_65_128_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r_65_128_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r_129_256_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r_129_256_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r_129_256_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r_129_256_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r_257_512_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r_257_512_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r_257_512_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r_257_512_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r_513_mtu_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r_513_mtu_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_r_513_mtu_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_r_513_mtu_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t8_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t8_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t8_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t8_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t16_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t16_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t16_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t16_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t_16_24_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t_16_24_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t_16_24_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t_16_24_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t_25_32_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t_25_32_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t_25_32_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t_25_32_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t_33_64_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t_33_64_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t_33_64_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t_33_64_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t_65_128_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t_65_128_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t_65_128_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t_65_128_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t_129_256_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t_129_256_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t_129_256_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t_129_256_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t_257_512_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t_257_512_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t_257_512_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t_257_512_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t_513_mtu_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t_513_mtu_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_t_513_mtu_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_packet_histograms.cnt_t_513_mtu_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PACKET_TYPE_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_ibg1_nvl_pkts_high: 0x%x\n", reg_data->counter_set.ppcnt_packet_type_counter.port_rcv_ibg1_nvl_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_ibg1_nvl_pkts_low: 0x%x\n", reg_data->counter_set.ppcnt_packet_type_counter.port_rcv_ibg1_nvl_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_ibg1_non_nvl_pkts_high: 0x%x\n", reg_data->counter_set.ppcnt_packet_type_counter.port_rcv_ibg1_non_nvl_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_ibg1_non_nvl_pkts_low: 0x%x\n", reg_data->counter_set.ppcnt_packet_type_counter.port_rcv_ibg1_non_nvl_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_ibg2_pkts_high: 0x%x\n", reg_data->counter_set.ppcnt_packet_type_counter.port_rcv_ibg2_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_ibg2_pkts_low: 0x%x\n", reg_data->counter_set.ppcnt_packet_type_counter.port_rcv_ibg2_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_ibg1_nvl_pkts_high: 0x%x\n", reg_data->counter_set.ppcnt_packet_type_counter.port_xmit_ibg1_nvl_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_ibg1_nvl_pkts_low: 0x%x\n", reg_data->counter_set.ppcnt_packet_type_counter.port_xmit_ibg1_nvl_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_ibg1_non_nvl_pkts_high: 0x%x\n", reg_data->counter_set.ppcnt_packet_type_counter.port_xmit_ibg1_non_nvl_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_ibg1_non_nvl_pkts_low: 0x%x\n", reg_data->counter_set.ppcnt_packet_type_counter.port_xmit_ibg1_non_nvl_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_ibg2_pkts_high: 0x%x\n", reg_data->counter_set.ppcnt_packet_type_counter.port_xmit_ibg2_pkts_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_ibg2_pkts_low: 0x%x\n", reg_data->counter_set.ppcnt_packet_type_counter.port_xmit_ibg2_pkts_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_INFINIBAND_VL_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dqs2llu_xmit_wait_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.dqs2llu_xmit_wait_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dqs2llu_xmit_wait_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.dqs2llu_xmit_wait_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dqs2llu_xmit_wait_arb_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.dqs2llu_xmit_wait_arb_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dqs2llu_xmit_wait_arb_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.dqs2llu_xmit_wait_arb_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_pkts_vl_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_rcv_pkts_vl_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_pkts_vl_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_rcv_pkts_vl_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_pkts_vl15_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_rcv_pkts_vl15_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_pkts_vl15_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_rcv_pkts_vl15_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_data_vl_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_rcv_data_vl_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_data_vl_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_rcv_data_vl_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_data_vl15_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_rcv_data_vl15_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_data_vl15_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_rcv_data_vl15_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_pkts_vl_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_xmit_pkts_vl_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_pkts_vl_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_xmit_pkts_vl_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_pkts_vl15_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_xmit_pkts_vl15_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_pkts_vl15_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_xmit_pkts_vl15_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_data_vl_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_xmit_data_vl_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_data_vl_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_xmit_data_vl_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_data_vl15_high: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_xmit_data_vl15_high);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_data_vl15_low: 0x%x\n", reg_data->counter_set.ppcnt_infiniband_vl_counter.port_xmit_data_vl15_low);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    default:
        /* Other types not supported yet */
        break;
    }

    return buffer_size;
}

int sx_spice_access_reg_sltp_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_sltp_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint32_t i = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "status: 0x%x\n", reg_data->status);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "version: 0x%x\n", reg_data->version);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->local_port, reg_data->lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->pnat);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_policy: 0x%x\n", reg_data->tx_policy);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "conf_mod: 0x%x\n", reg_data->conf_mod);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane: 0x%x\n", reg_data->lane);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane_speed: 0x%x\n", reg_data->lane_speed);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "port_type: 0x%x\n", reg_data->port_type);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "c_db: 0x%x\n", reg_data->c_db);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    if ((reg_data->port_type == SXD_SLTP_PORT_TYPE_NETWORK_PORT_E) && (reg_data->version == SXD_SLTP_VERSION_PROD_40NM_E || reg_data->version == SXD_SLTP_VERSION_PROD_28NM_E)) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "polarity: 0x%x\n", reg_data->page_data.sltp_28nm_40nm.polarity);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_tap0: 0x%x\n", reg_data->page_data.sltp_28nm_40nm.ob_tap0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_tap1: 0x%x\n", reg_data->page_data.sltp_28nm_40nm.ob_tap1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_tap2: 0x%x\n", reg_data->page_data.sltp_28nm_40nm.ob_tap2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_leva: 0x%x\n", reg_data->page_data.sltp_28nm_40nm.ob_leva);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_preemp_mode: 0x%x\n", reg_data->page_data.sltp_28nm_40nm.ob_preemp_mode);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_reg: 0x%x\n", reg_data->page_data.sltp_28nm_40nm.ob_reg);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_bias: 0x%x\n", reg_data->page_data.sltp_28nm_40nm.ob_bias);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_norm: 0x%x\n", reg_data->page_data.sltp_28nm_40nm.ob_norm);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_bad_stat: 0x%x\n", reg_data->page_data.sltp_28nm_40nm.ob_bad_stat);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }

    if ((reg_data->port_type == SXD_SLTP_PORT_TYPE_NETWORK_PORT_E || reg_data->port_type == SXD_SLTP_PORT_TYPE_INTERNAL_IC_LR_PORT_E) && (reg_data->version == SXD_SLTP_VERSION_PROD_16NM_E)) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pre_2_tap: 0x%x\n", reg_data->page_data.sltp_16nm.pre_2_tap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pre_tap: 0x%x\n", reg_data->page_data.sltp_16nm.pre_tap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "main_tap: 0x%x\n", reg_data->page_data.sltp_16nm.main_tap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "post_tap: 0x%x\n", reg_data->page_data.sltp_16nm.post_tap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_m2lp: 0x%x\n", reg_data->page_data.sltp_16nm.ob_m2lp);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_amp: 0x%x\n", reg_data->page_data.sltp_16nm.ob_amp);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_alev_out: 0x%x\n", reg_data->page_data.sltp_16nm.ob_alev_out);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_bad_stat: 0x%x\n", reg_data->page_data.sltp_16nm.ob_bad_stat);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "obplev: 0x%x\n", reg_data->page_data.sltp_16nm.obplev);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "obnlev: 0x%x\n", reg_data->page_data.sltp_16nm.obnlev);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "regn_bfm1p: 0x%x\n", reg_data->page_data.sltp_16nm.regn_bfm1p);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "regp_bfm1n: 0x%x\n", reg_data->page_data.sltp_16nm.regp_bfm1n);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }

    if ((reg_data->port_type == SXD_SLTP_PORT_TYPE_NEAREND_PORT_E || reg_data->port_type == SXD_SLTP_PORT_TYPE_FAREND_PORT_E) && (reg_data->version == SXD_SLTP_VERSION_PROD_28NM_E)) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "main_tap: 0x%x\n", reg_data->page_data.sltp_gearbox.main_tap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pre_tap: 0x%x\n", reg_data->page_data.sltp_gearbox.pre_tap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "post_tap: 0x%x\n", reg_data->page_data.sltp_gearbox.post_tap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        for (i = 0; i < SXD_SLTP_INNER_EYE_NUM; i++) {
            snp_res = snprintf(buffer, buffer_length - buffer_size, "inner_eye[%d]: 0x%x\n", i, reg_data->page_data.sltp_gearbox.inner_eye[i]);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_swing: 0x%x\n", reg_data->page_data.sltp_gearbox.tx_swing);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }

    if ((reg_data->port_type == SXD_SLTP_PORT_TYPE_NETWORK_PORT_E || reg_data->port_type == SXD_SLTP_PORT_TYPE_INTERNAL_IC_LR_PORT_E) && (reg_data->version == SXD_SLTP_VERSION_PROD_7NM_E)) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vs_peer_db: 0x%x\n", reg_data->page_data.sltp_7nm.vs_peer_db);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "drv_amp: 0x%x\n", reg_data->page_data.sltp_7nm.drv_amp);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_bad_stat: 0x%x\n", reg_data->page_data.sltp_7nm.ob_bad_stat);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fir_pre3: 0x%x\n", reg_data->page_data.sltp_7nm.fir_pre3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fir_pre2: 0x%x\n", reg_data->page_data.sltp_7nm.fir_pre2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fir_pre1: 0x%x\n", reg_data->page_data.sltp_7nm.fir_pre1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fir_main: 0x%x\n", reg_data->page_data.sltp_7nm.fir_main);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fir_post1: 0x%x\n", reg_data->page_data.sltp_7nm.fir_post1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }

    if ((reg_data->port_type == SXD_SLTP_PORT_TYPE_NETWORK_PORT_E || reg_data->port_type == SXD_SLTP_PORT_TYPE_INTERNAL_IC_LR_PORT_E) && (reg_data->version == SXD_SLTP_VERSION_PROD_7NM_E)) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vs_peer_db: 0x%x\n", reg_data->page_data.sltp_lut_7nm.vs_peer_db);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "drv_amp: 0x%x\n", reg_data->page_data.sltp_lut_7nm.drv_amp);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ob_bad_stat: 0x%x\n", reg_data->page_data.sltp_lut_7nm.ob_bad_stat);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fir_pre3: 0x%x\n", reg_data->page_data.sltp_lut_7nm.fir_pre3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fir_pre2: 0x%x\n", reg_data->page_data.sltp_lut_7nm.fir_pre2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut3: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut2: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut1: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut0: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut7: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut6: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut5: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut4: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut11: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut11);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut10: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut10);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut9: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut9);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut8: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut8);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut15: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut15);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut14: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut14);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut13: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut13);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut12: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut12);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut19: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut19);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut18: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut18);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut17: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut17);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut16: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut16);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut23: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut23);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut22: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut22);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut21: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut21);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut20: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut20);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut27: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut27);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut26: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut26);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut25: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut25);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut24: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut24);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut31: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut31);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut30: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut30);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut29: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut29);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut28: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut28);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut35: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut35);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut34: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut34);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut33: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut33);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut32: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut32);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut39: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut39);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut38: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut38);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut37: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut37);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut36: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut36);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut43: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut43);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut42: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut42);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut41: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut41);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut40: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut40);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut47: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut47);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut46: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut46);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut45: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut45);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut44: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut44);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut51: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut51);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut50: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut50);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut49: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut49);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut48: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut48);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut55: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut55);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut54: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut54);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut53: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut53);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut52: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut52);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut59: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut59);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut58: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut58);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut57: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut57);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut56: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut56);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut63: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut63);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut62: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut62);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut61: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut61);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lut60: 0x%x\n", reg_data->page_data.sltp_lut_7nm.lut60);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }


    return buffer_size;
}

int sx_spice_access_reg_pddr_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_pddr_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint32_t i = 0;
    uint32_t j = 0;
    uint16_t local_port = 0;

    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->local_port, reg_data->lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->pnat);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "plane_ind: 0x%x\n", reg_data->plane_ind);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "port_type: 0x%x\n", reg_data->port_type);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "clr: 0x%x\n", reg_data->clr);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "module_info_ext: 0x%x\n", reg_data->module_info_ext);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "dev: 0x%x\n", reg_data->dev);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "page_select: 0x%x\n", reg_data->page_select);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    switch (reg_data->page_select) {
    case SXD_PDDR_PAGE_SELECT_OPERATIONAL_INFO_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "proto_active: 0x%x\n", reg_data->page_data.pddr_operation_info_page.proto_active);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "neg_mode_active: 0x%x\n", reg_data->page_data.pddr_operation_info_page.neg_mode_active);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pd_fsm_state: 0x%x\n", reg_data->page_data.pddr_operation_info_page.pd_fsm_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_mngr_fsm_state: 0x%x\n", reg_data->page_data.pddr_operation_info_page.phy_mngr_fsm_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_an_fsm_state: 0x%x\n", reg_data->page_data.pddr_operation_info_page.eth_an_fsm_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_phy_fsm_state: 0x%x\n", reg_data->page_data.pddr_operation_info_page.ib_phy_fsm_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_hst_fsm_state: 0x%x\n", reg_data->page_data.pddr_operation_info_page.phy_hst_fsm_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_manager_link_width_enabled: 0x%x\n", reg_data->page_data.pddr_operation_info_page.phy_manager_link_enabled.pddr_phy_manager_link_enabed_ib.phy_manager_link_width_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_manager_link_proto_enabled: 0x%x\n", reg_data->page_data.pddr_operation_info_page.phy_manager_link_enabled.pddr_phy_manager_link_enabed_ib.phy_manager_link_proto_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_manager_link_eth_enabled: 0x%x\n", reg_data->page_data.pddr_operation_info_page.phy_manager_link_enabled.pddr_phy_manager_link_enabed_eth.phy_manager_link_eth_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "core_to_phy_link_width_enabled: 0x%x\n", reg_data->page_data.pddr_operation_info_page.core_to_phy_link_enabled.pddr_c2p_link_enabed_ib.core_to_phy_link_width_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "core_to_phy_link_proto_enabled: 0x%x\n", reg_data->page_data.pddr_operation_info_page.core_to_phy_link_enabled.pddr_c2p_link_enabed_ib.core_to_phy_link_proto_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "core_to_phy_link_eth_enabled: 0x%x\n", reg_data->page_data.pddr_operation_info_page.core_to_phy_link_enabled.pddr_c2p_link_enabed_eth.core_to_phy_link_eth_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_link_width_cap: 0x%x\n", reg_data->page_data.pddr_operation_info_page.cable_proto_cap.pddr_cable_cap_ib.cable_link_width_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_link_speed_cap: 0x%x\n", reg_data->page_data.pddr_operation_info_page.cable_proto_cap.pddr_cable_cap_ib.cable_link_speed_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_ext_eth_proto_cap: 0x%x\n", reg_data->page_data.pddr_operation_info_page.cable_proto_cap.pddr_cable_cap_eth.cable_ext_eth_proto_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        switch (reg_data->page_data.pddr_operation_info_page.proto_active) {
        case SXD_PDDR_PROTO_ACTIVE_INFINIBAND_E:
            snp_res = snprintf(buffer, buffer_length - buffer_size, "link_width_active: 0x%x\n", reg_data->page_data.pddr_operation_info_page.link_active.pddr_link_active_ib.link_width_active);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer, buffer_length - buffer_size, "link_speed_active: 0x%x\n", reg_data->page_data.pddr_operation_info_page.link_active.pddr_link_active_ib.link_speed_active);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            break;

        case SXD_PDDR_PROTO_ACTIVE_ETHERNET_E:
            snp_res = snprintf(buffer, buffer_length - buffer_size, "link_eth_active: 0x%x\n", reg_data->page_data.pddr_operation_info_page.link_active.pddr_link_active_eth.link_eth_active);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            break;

        case SXD_PDDR_PROTO_ACTIVE_NVLINK_E:
            break;

        default:
            /* Other types not supported yet */
            break;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "retran_mode_active: 0x%x\n", reg_data->page_data.pddr_operation_info_page.retran_mode_active);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "retran_mode_request: 0x%x\n", reg_data->page_data.pddr_operation_info_page.retran_mode_request);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "loopback_mode: 0x%x\n", reg_data->page_data.pddr_operation_info_page.loopback_mode);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fec_mode_active: 0x%x\n", reg_data->page_data.pddr_operation_info_page.fec_mode_active);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fec_mode_request: 0x%x\n", reg_data->page_data.pddr_operation_info_page.fec_mode_request);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "profile_fec_in_use: 0x%x\n", reg_data->page_data.pddr_operation_info_page.profile_fec_in_use);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "nlpn_fsm_state: 0x%x\n", reg_data->page_data.pddr_operation_info_page.nlpn_fsm_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_25g_50g_fec_support: 0x%x\n", reg_data->page_data.pddr_operation_info_page.eth_25g_50g_fec_support);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_100g_fec_support: 0x%x\n", reg_data->page_data.pddr_operation_info_page.eth_100g_fec_support);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pd_link_enabled: 0x%x\n", reg_data->page_data.pddr_operation_info_page.pd_link_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_hst_link_enabled: 0x%x\n", reg_data->page_data.pddr_operation_info_page.phy_hst_link_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_an_link_enabled: 0x%x\n", reg_data->page_data.pddr_operation_info_page.eth_an_link_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "linkup_retry_iterations: 0x%x\n", reg_data->page_data.pddr_operation_info_page.linkup_retry_iterations);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "core_to_phy_state: 0x%x\n", reg_data->page_data.pddr_operation_info_page.core_to_phy_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "psi_fsm_state: 0x%x\n", reg_data->page_data.pddr_operation_info_page.psi_fsm_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_proto_cap_ext: 0x%x\n", reg_data->page_data.pddr_operation_info_page.cable_proto_cap_ext);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_TROUBLESHOOTING_INFO_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "group_opcode: 0x%x\n", reg_data->page_data.pddr_troubleshooting_page.group_opcode);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        switch (reg_data->page_data.pddr_troubleshooting_page.group_opcode) {
        case SXD_PDDR_GROUP_OPCODE_MONITOR_OPCODES_E:
            snp_res = snprintf(buffer, buffer_length - buffer_size, "monitor_opcode: 0x%x\n", reg_data->page_data.pddr_troubleshooting_page.status_opcode.pddr_monitor_opcode.monitor_opcode);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            break;

        case SXD_PDDR_GROUP_OPCODE_ADVANCED_DEBUG_OPCODES_E:
            snp_res = snprintf(buffer, buffer_length - buffer_size, "advanced_opcode: 0x%x\n", reg_data->page_data.pddr_troubleshooting_page.status_opcode.pddr_advanced_opcode.advanced_opcode);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            break;

        default:
            /* Other types not supported yet */
            break;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "user_feedback_data: 0x%x\n", reg_data->page_data.pddr_troubleshooting_page.user_feedback_data);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "user_feedback_index: 0x%x\n", reg_data->page_data.pddr_troubleshooting_page.user_feedback_index);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "status_message: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", reg_data->page_data.pddr_troubleshooting_page.status_message[0], reg_data->page_data.pddr_troubleshooting_page.status_message[1], reg_data->page_data.pddr_troubleshooting_page.status_message[2], reg_data->page_data.pddr_troubleshooting_page.status_message[3], reg_data->page_data.pddr_troubleshooting_page.status_message[4], reg_data->page_data.pddr_troubleshooting_page.status_message[5], reg_data->page_data.pddr_troubleshooting_page.status_message[6], reg_data->page_data.pddr_troubleshooting_page.status_message[7], reg_data->page_data.pddr_troubleshooting_page.status_message[8], reg_data->page_data.pddr_troubleshooting_page.status_message[9], reg_data->page_data.pddr_troubleshooting_page.status_message[10], reg_data->page_data.pddr_troubleshooting_page.status_message[11], reg_data->page_data.pddr_troubleshooting_page.status_message[12], reg_data->page_data.pddr_troubleshooting_page.status_message[13], reg_data->page_data.pddr_troubleshooting_page.status_message[14], reg_data->page_data.pddr_troubleshooting_page.status_message[15], reg_data->page_data.pddr_troubleshooting_page.status_message[16], reg_data->page_data.pddr_troubleshooting_page.status_message[17], reg_data->page_data.pddr_troubleshooting_page.status_message[18], reg_data->page_data.pddr_troubleshooting_page.status_message[19], reg_data->page_data.pddr_troubleshooting_page.status_message[20], reg_data->page_data.pddr_troubleshooting_page.status_message[21], reg_data->page_data.pddr_troubleshooting_page.status_message[22], reg_data->page_data.pddr_troubleshooting_page.status_message[23], reg_data->page_data.pddr_troubleshooting_page.status_message[24], reg_data->page_data.pddr_troubleshooting_page.status_message[25], reg_data->page_data.pddr_troubleshooting_page.status_message[26], reg_data->page_data.pddr_troubleshooting_page.status_message[27], reg_data->page_data.pddr_troubleshooting_page.status_message[28], reg_data->page_data.pddr_troubleshooting_page.status_message[29], reg_data->page_data.pddr_troubleshooting_page.status_message[30], reg_data->page_data.pddr_troubleshooting_page.status_message[31], reg_data->page_data.pddr_troubleshooting_page.status_message[32], reg_data->page_data.pddr_troubleshooting_page.status_message[33], reg_data->page_data.pddr_troubleshooting_page.status_message[34], reg_data->page_data.pddr_troubleshooting_page.status_message[35], reg_data->page_data.pddr_troubleshooting_page.status_message[36], reg_data->page_data.pddr_troubleshooting_page.status_message[37], reg_data->page_data.pddr_troubleshooting_page.status_message[38], reg_data->page_data.pddr_troubleshooting_page.status_message[39], reg_data->page_data.pddr_troubleshooting_page.status_message[40], reg_data->page_data.pddr_troubleshooting_page.status_message[41], reg_data->page_data.pddr_troubleshooting_page.status_message[42], reg_data->page_data.pddr_troubleshooting_page.status_message[43], reg_data->page_data.pddr_troubleshooting_page.status_message[44], reg_data->page_data.pddr_troubleshooting_page.status_message[45], reg_data->page_data.pddr_troubleshooting_page.status_message[46], reg_data->page_data.pddr_troubleshooting_page.status_message[47], reg_data->page_data.pddr_troubleshooting_page.status_message[48], reg_data->page_data.pddr_troubleshooting_page.status_message[49], reg_data->page_data.pddr_troubleshooting_page.status_message[50], reg_data->page_data.pddr_troubleshooting_page.status_message[51], reg_data->page_data.pddr_troubleshooting_page.status_message[52], reg_data->page_data.pddr_troubleshooting_page.status_message[53], reg_data->page_data.pddr_troubleshooting_page.status_message[54], reg_data->page_data.pddr_troubleshooting_page.status_message[55], reg_data->page_data.pddr_troubleshooting_page.status_message[56], reg_data->page_data.pddr_troubleshooting_page.status_message[57], reg_data->page_data.pddr_troubleshooting_page.status_message[58], reg_data->page_data.pddr_troubleshooting_page.status_message[59], reg_data->page_data.pddr_troubleshooting_page.status_message[60], reg_data->page_data.pddr_troubleshooting_page.status_message[61], reg_data->page_data.pddr_troubleshooting_page.status_message[62], reg_data->page_data.pddr_troubleshooting_page.status_message[63], reg_data->page_data.pddr_troubleshooting_page.status_message[64], reg_data->page_data.pddr_troubleshooting_page.status_message[65], reg_data->page_data.pddr_troubleshooting_page.status_message[66], reg_data->page_data.pddr_troubleshooting_page.status_message[67], reg_data->page_data.pddr_troubleshooting_page.status_message[68], reg_data->page_data.pddr_troubleshooting_page.status_message[69], reg_data->page_data.pddr_troubleshooting_page.status_message[70], reg_data->page_data.pddr_troubleshooting_page.status_message[71], reg_data->page_data.pddr_troubleshooting_page.status_message[72], reg_data->page_data.pddr_troubleshooting_page.status_message[73], reg_data->page_data.pddr_troubleshooting_page.status_message[74], reg_data->page_data.pddr_troubleshooting_page.status_message[75], reg_data->page_data.pddr_troubleshooting_page.status_message[76], reg_data->page_data.pddr_troubleshooting_page.status_message[77], reg_data->page_data.pddr_troubleshooting_page.status_message[78], reg_data->page_data.pddr_troubleshooting_page.status_message[79], reg_data->page_data.pddr_troubleshooting_page.status_message[80], reg_data->page_data.pddr_troubleshooting_page.status_message[81], reg_data->page_data.pddr_troubleshooting_page.status_message[82], reg_data->page_data.pddr_troubleshooting_page.status_message[83], reg_data->page_data.pddr_troubleshooting_page.status_message[84], reg_data->page_data.pddr_troubleshooting_page.status_message[85], reg_data->page_data.pddr_troubleshooting_page.status_message[86], reg_data->page_data.pddr_troubleshooting_page.status_message[87], reg_data->page_data.pddr_troubleshooting_page.status_message[88], reg_data->page_data.pddr_troubleshooting_page.status_message[89], reg_data->page_data.pddr_troubleshooting_page.status_message[90], reg_data->page_data.pddr_troubleshooting_page.status_message[91], reg_data->page_data.pddr_troubleshooting_page.status_message[92], reg_data->page_data.pddr_troubleshooting_page.status_message[93], reg_data->page_data.pddr_troubleshooting_page.status_message[94], reg_data->page_data.pddr_troubleshooting_page.status_message[95], reg_data->page_data.pddr_troubleshooting_page.status_message[96], reg_data->page_data.pddr_troubleshooting_page.status_message[97], reg_data->page_data.pddr_troubleshooting_page.status_message[98], reg_data->page_data.pddr_troubleshooting_page.status_message[99], reg_data->page_data.pddr_troubleshooting_page.status_message[100], reg_data->page_data.pddr_troubleshooting_page.status_message[101], reg_data->page_data.pddr_troubleshooting_page.status_message[102], reg_data->page_data.pddr_troubleshooting_page.status_message[103], reg_data->page_data.pddr_troubleshooting_page.status_message[104], reg_data->page_data.pddr_troubleshooting_page.status_message[105], reg_data->page_data.pddr_troubleshooting_page.status_message[106], reg_data->page_data.pddr_troubleshooting_page.status_message[107], reg_data->page_data.pddr_troubleshooting_page.status_message[108], reg_data->page_data.pddr_troubleshooting_page.status_message[109], reg_data->page_data.pddr_troubleshooting_page.status_message[110], reg_data->page_data.pddr_troubleshooting_page.status_message[111], reg_data->page_data.pddr_troubleshooting_page.status_message[112], reg_data->page_data.pddr_troubleshooting_page.status_message[113], reg_data->page_data.pddr_troubleshooting_page.status_message[114], reg_data->page_data.pddr_troubleshooting_page.status_message[115], reg_data->page_data.pddr_troubleshooting_page.status_message[116], reg_data->page_data.pddr_troubleshooting_page.status_message[117], reg_data->page_data.pddr_troubleshooting_page.status_message[118], reg_data->page_data.pddr_troubleshooting_page.status_message[119], reg_data->page_data.pddr_troubleshooting_page.status_message[120], reg_data->page_data.pddr_troubleshooting_page.status_message[121], reg_data->page_data.pddr_troubleshooting_page.status_message[122], reg_data->page_data.pddr_troubleshooting_page.status_message[123], reg_data->page_data.pddr_troubleshooting_page.status_message[124], reg_data->page_data.pddr_troubleshooting_page.status_message[125], reg_data->page_data.pddr_troubleshooting_page.status_message[126], reg_data->page_data.pddr_troubleshooting_page.status_message[127], reg_data->page_data.pddr_troubleshooting_page.status_message[128], reg_data->page_data.pddr_troubleshooting_page.status_message[129], reg_data->page_data.pddr_troubleshooting_page.status_message[130], reg_data->page_data.pddr_troubleshooting_page.status_message[131], reg_data->page_data.pddr_troubleshooting_page.status_message[132], reg_data->page_data.pddr_troubleshooting_page.status_message[133], reg_data->page_data.pddr_troubleshooting_page.status_message[134], reg_data->page_data.pddr_troubleshooting_page.status_message[135], reg_data->page_data.pddr_troubleshooting_page.status_message[136], reg_data->page_data.pddr_troubleshooting_page.status_message[137], reg_data->page_data.pddr_troubleshooting_page.status_message[138], reg_data->page_data.pddr_troubleshooting_page.status_message[139], reg_data->page_data.pddr_troubleshooting_page.status_message[140], reg_data->page_data.pddr_troubleshooting_page.status_message[141], reg_data->page_data.pddr_troubleshooting_page.status_message[142], reg_data->page_data.pddr_troubleshooting_page.status_message[143], reg_data->page_data.pddr_troubleshooting_page.status_message[144], reg_data->page_data.pddr_troubleshooting_page.status_message[145], reg_data->page_data.pddr_troubleshooting_page.status_message[146], reg_data->page_data.pddr_troubleshooting_page.status_message[147], reg_data->page_data.pddr_troubleshooting_page.status_message[148], reg_data->page_data.pddr_troubleshooting_page.status_message[149], reg_data->page_data.pddr_troubleshooting_page.status_message[150], reg_data->page_data.pddr_troubleshooting_page.status_message[151], reg_data->page_data.pddr_troubleshooting_page.status_message[152], reg_data->page_data.pddr_troubleshooting_page.status_message[153], reg_data->page_data.pddr_troubleshooting_page.status_message[154], reg_data->page_data.pddr_troubleshooting_page.status_message[155], reg_data->page_data.pddr_troubleshooting_page.status_message[156], reg_data->page_data.pddr_troubleshooting_page.status_message[157], reg_data->page_data.pddr_troubleshooting_page.status_message[158], reg_data->page_data.pddr_troubleshooting_page.status_message[159], reg_data->page_data.pddr_troubleshooting_page.status_message[160], reg_data->page_data.pddr_troubleshooting_page.status_message[161], reg_data->page_data.pddr_troubleshooting_page.status_message[162], reg_data->page_data.pddr_troubleshooting_page.status_message[163], reg_data->page_data.pddr_troubleshooting_page.status_message[164], reg_data->page_data.pddr_troubleshooting_page.status_message[165], reg_data->page_data.pddr_troubleshooting_page.status_message[166], reg_data->page_data.pddr_troubleshooting_page.status_message[167], reg_data->page_data.pddr_troubleshooting_page.status_message[168], reg_data->page_data.pddr_troubleshooting_page.status_message[169], reg_data->page_data.pddr_troubleshooting_page.status_message[170], reg_data->page_data.pddr_troubleshooting_page.status_message[171], reg_data->page_data.pddr_troubleshooting_page.status_message[172], reg_data->page_data.pddr_troubleshooting_page.status_message[173], reg_data->page_data.pddr_troubleshooting_page.status_message[174], reg_data->page_data.pddr_troubleshooting_page.status_message[175], reg_data->page_data.pddr_troubleshooting_page.status_message[176], reg_data->page_data.pddr_troubleshooting_page.status_message[177], reg_data->page_data.pddr_troubleshooting_page.status_message[178], reg_data->page_data.pddr_troubleshooting_page.status_message[179], reg_data->page_data.pddr_troubleshooting_page.status_message[180], reg_data->page_data.pddr_troubleshooting_page.status_message[181], reg_data->page_data.pddr_troubleshooting_page.status_message[182], reg_data->page_data.pddr_troubleshooting_page.status_message[183], reg_data->page_data.pddr_troubleshooting_page.status_message[184], reg_data->page_data.pddr_troubleshooting_page.status_message[185], reg_data->page_data.pddr_troubleshooting_page.status_message[186], reg_data->page_data.pddr_troubleshooting_page.status_message[187], reg_data->page_data.pddr_troubleshooting_page.status_message[188], reg_data->page_data.pddr_troubleshooting_page.status_message[189], reg_data->page_data.pddr_troubleshooting_page.status_message[190], reg_data->page_data.pddr_troubleshooting_page.status_message[191], reg_data->page_data.pddr_troubleshooting_page.status_message[192], reg_data->page_data.pddr_troubleshooting_page.status_message[193], reg_data->page_data.pddr_troubleshooting_page.status_message[194], reg_data->page_data.pddr_troubleshooting_page.status_message[195], reg_data->page_data.pddr_troubleshooting_page.status_message[196], reg_data->page_data.pddr_troubleshooting_page.status_message[197], reg_data->page_data.pddr_troubleshooting_page.status_message[198], reg_data->page_data.pddr_troubleshooting_page.status_message[199], reg_data->page_data.pddr_troubleshooting_page.status_message[200], reg_data->page_data.pddr_troubleshooting_page.status_message[201], reg_data->page_data.pddr_troubleshooting_page.status_message[202], reg_data->page_data.pddr_troubleshooting_page.status_message[203], reg_data->page_data.pddr_troubleshooting_page.status_message[204], reg_data->page_data.pddr_troubleshooting_page.status_message[205], reg_data->page_data.pddr_troubleshooting_page.status_message[206], reg_data->page_data.pddr_troubleshooting_page.status_message[207], reg_data->page_data.pddr_troubleshooting_page.status_message[208], reg_data->page_data.pddr_troubleshooting_page.status_message[209], reg_data->page_data.pddr_troubleshooting_page.status_message[210], reg_data->page_data.pddr_troubleshooting_page.status_message[211], reg_data->page_data.pddr_troubleshooting_page.status_message[212], reg_data->page_data.pddr_troubleshooting_page.status_message[213], reg_data->page_data.pddr_troubleshooting_page.status_message[214], reg_data->page_data.pddr_troubleshooting_page.status_message[215], reg_data->page_data.pddr_troubleshooting_page.status_message[216], reg_data->page_data.pddr_troubleshooting_page.status_message[217], reg_data->page_data.pddr_troubleshooting_page.status_message[218], reg_data->page_data.pddr_troubleshooting_page.status_message[219], reg_data->page_data.pddr_troubleshooting_page.status_message[220], reg_data->page_data.pddr_troubleshooting_page.status_message[221], reg_data->page_data.pddr_troubleshooting_page.status_message[222], reg_data->page_data.pddr_troubleshooting_page.status_message[223], reg_data->page_data.pddr_troubleshooting_page.status_message[224], reg_data->page_data.pddr_troubleshooting_page.status_message[225], reg_data->page_data.pddr_troubleshooting_page.status_message[226], reg_data->page_data.pddr_troubleshooting_page.status_message[227], reg_data->page_data.pddr_troubleshooting_page.status_message[228], reg_data->page_data.pddr_troubleshooting_page.status_message[229], reg_data->page_data.pddr_troubleshooting_page.status_message[230], reg_data->page_data.pddr_troubleshooting_page.status_message[231], reg_data->page_data.pddr_troubleshooting_page.status_message[232], reg_data->page_data.pddr_troubleshooting_page.status_message[233], reg_data->page_data.pddr_troubleshooting_page.status_message[234], reg_data->page_data.pddr_troubleshooting_page.status_message[235]);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_PHY_INFO_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "remote_device_type: 0x%x\n", reg_data->page_data.pddr_phy_info_page.remote_device_type);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "negotiation_mask: 0x%x\n", reg_data->page_data.pddr_phy_info_page.negotiation_mask);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_notifications: 0x%x\n", reg_data->page_data.pddr_phy_info_page.port_notifications);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_negotiation_attempts: 0x%x\n", reg_data->page_data.pddr_phy_info_page.num_of_negotiation_attempts);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_revision: 0x%x\n", reg_data->page_data.pddr_phy_info_page.ib_revision);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lp_ib_revision: 0x%x\n", reg_data->page_data.pddr_phy_info_page.lp_ib_revision);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "hw_link_phy_state: 0x%x\n", reg_data->page_data.pddr_phy_info_page.hw_link_phy_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_manger_disable_mask: 0x%x\n", reg_data->page_data.pddr_phy_info_page.phy_manger_disable_mask);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pcs_phy_state: 0x%x\n", reg_data->page_data.pddr_phy_info_page.pcs_phy_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lp_proto_enabled: 0x%x\n", reg_data->page_data.pddr_phy_info_page.lp_proto_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lp_fec_mode_support: 0x%x\n", reg_data->page_data.pddr_phy_info_page.lp_fec_mode_support);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lp_fec_mode_request: 0x%x\n", reg_data->page_data.pddr_phy_info_page.lp_fec_mode_request);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_last_link_down_reason: 0x%x\n", reg_data->page_data.pddr_phy_info_page.ib_last_link_down_reason);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_last_link_down_lane: 0x%02x%02x%02x%02x\n", reg_data->page_data.pddr_phy_info_page.eth_last_link_down_lane[0], reg_data->page_data.pddr_phy_info_page.eth_last_link_down_lane[1], reg_data->page_data.pddr_phy_info_page.eth_last_link_down_lane[2], reg_data->page_data.pddr_phy_info_page.eth_last_link_down_lane[3]);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "speed_deg_db: 0x%x\n", reg_data->page_data.pddr_phy_info_page.speed_deg_db);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "degrade_grade_lane0: 0x%x\n", reg_data->page_data.pddr_phy_info_page.degrade_grade_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "degrade_grade_lane1: 0x%x\n", reg_data->page_data.pddr_phy_info_page.degrade_grade_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "degrade_grade_lane2: 0x%x\n", reg_data->page_data.pddr_phy_info_page.degrade_grade_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "degrade_grade_lane3: 0x%x\n", reg_data->page_data.pddr_phy_info_page.degrade_grade_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_presets_tested_lane4: 0x%x\n", reg_data->page_data.pddr_phy_info_page.num_of_presets_tested_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_presets_tested_lane5: 0x%x\n", reg_data->page_data.pddr_phy_info_page.num_of_presets_tested_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_presets_tested_lane6: 0x%x\n", reg_data->page_data.pddr_phy_info_page.num_of_presets_tested_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_presets_tested_lane7: 0x%x\n", reg_data->page_data.pddr_phy_info_page.num_of_presets_tested_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_startup_debug_indications_4: 0x%x\n", reg_data->page_data.pddr_phy_info_page.kr_startup_debug_indications_4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_startup_debug_indications_5: 0x%x\n", reg_data->page_data.pddr_phy_info_page.kr_startup_debug_indications_5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_startup_debug_indications_6: 0x%x\n", reg_data->page_data.pddr_phy_info_page.kr_startup_debug_indications_6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_startup_debug_indications_7: 0x%x\n", reg_data->page_data.pddr_phy_info_page.kr_startup_debug_indications_7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_presets_tested_lane0: 0x%x\n", reg_data->page_data.pddr_phy_info_page.num_of_presets_tested_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_presets_tested_lane1: 0x%x\n", reg_data->page_data.pddr_phy_info_page.num_of_presets_tested_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_presets_tested_lane2: 0x%x\n", reg_data->page_data.pddr_phy_info_page.num_of_presets_tested_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_presets_tested_lane3: 0x%x\n", reg_data->page_data.pddr_phy_info_page.num_of_presets_tested_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_startup_fsm_lane: 0x%02x%02x%02x%02x%02x%02x%02x%02x\n", reg_data->page_data.pddr_phy_info_page.kr_startup_fsm_lane[0], reg_data->page_data.pddr_phy_info_page.kr_startup_fsm_lane[1], reg_data->page_data.pddr_phy_info_page.kr_startup_fsm_lane[2], reg_data->page_data.pddr_phy_info_page.kr_startup_fsm_lane[3], reg_data->page_data.pddr_phy_info_page.kr_startup_fsm_lane[4], reg_data->page_data.pddr_phy_info_page.kr_startup_fsm_lane[5], reg_data->page_data.pddr_phy_info_page.kr_startup_fsm_lane[6], reg_data->page_data.pddr_phy_info_page.kr_startup_fsm_lane[7]);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_an_debug_indication: 0x%x\n", reg_data->page_data.pddr_phy_info_page.eth_an_debug_indication);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cdr_not_locked_cnt: 0x%x\n", reg_data->page_data.pddr_phy_info_page.cdr_not_locked_cnt);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fall_from_cfg_idle_cnt: 0x%x\n", reg_data->page_data.pddr_phy_info_page.fall_from_cfg_idle_cnt);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fall_from_cfg_idle_cdr_cnt: 0x%x\n", reg_data->page_data.pddr_phy_info_page.fall_from_cfg_idle_cdr_cnt);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_an_watchdog_cnt: 0x%x\n", reg_data->page_data.pddr_phy_info_page.eth_an_watchdog_cnt);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rounds_waited_for_peer_to_end_test: 0x%x\n", reg_data->page_data.pddr_phy_info_page.rounds_waited_for_peer_to_end_test);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_phy_fsm_state_trace: 0x%x\n", reg_data->page_data.pddr_phy_info_page.ib_phy_fsm_state_trace);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_startup_debug_indications_0: 0x%x\n", reg_data->page_data.pddr_phy_info_page.kr_startup_debug_indications_0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_startup_debug_indications_1: 0x%x\n", reg_data->page_data.pddr_phy_info_page.kr_startup_debug_indications_1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_startup_debug_indications_2: 0x%x\n", reg_data->page_data.pddr_phy_info_page.kr_startup_debug_indications_2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_startup_debug_indications_3: 0x%x\n", reg_data->page_data.pddr_phy_info_page.kr_startup_debug_indications_3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        for (i = 0; i < SXD_PDDR_TX_TUNING_STAGES_LANE_NUM; i++) {
            snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_tuning_stages_lane[%d]: 0x%x\n", i, reg_data->page_data.pddr_phy_info_page.tx_tuning_stages_lane[i]);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_rx_polarity: 0x%x\n", reg_data->page_data.pddr_phy_info_page.plu_rx_polarity);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_tx_polarity: 0x%x\n", reg_data->page_data.pddr_phy_info_page.plu_tx_polarity);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_rx_pwrup: 0x%x\n", reg_data->page_data.pddr_phy_info_page.plu_rx_pwrup);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_tx_pwrup: 0x%x\n", reg_data->page_data.pddr_phy_info_page.plu_tx_pwrup);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "signal_detected: 0x%x\n", reg_data->page_data.pddr_phy_info_page.signal_detected);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_outstanding_cells: 0x%x\n", reg_data->page_data.pddr_phy_info_page.plr_outstanding_cells);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_rx_speed: 0x%x\n", reg_data->page_data.pddr_phy_info_page.plu_rx_speed);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_tx_speed: 0x%x\n", reg_data->page_data.pddr_phy_info_page.plu_tx_speed);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "sd_valid: 0x%x\n", reg_data->page_data.pddr_phy_info_page.sd_valid);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_cfg_delay_timeout: 0x%x\n", reg_data->page_data.pddr_phy_info_page.ib_cfg_delay_timeout);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "irisc_status: 0x%x\n", reg_data->page_data.pddr_phy_info_page.irisc_status);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "stamping_reason: 0x%x\n", reg_data->page_data.pddr_phy_info_page.stamping_reason);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_frame_lock_tuning_failure_events_count: 0x%x\n", reg_data->page_data.pddr_phy_info_page.kr_frame_lock_tuning_failure_events_count);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_full_tuning_failure_count: 0x%x\n", reg_data->page_data.pddr_phy_info_page.kr_full_tuning_failure_count);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_debug_indication: 0x%x\n", reg_data->page_data.pddr_phy_info_page.ib_debug_indication);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pm_debug_indication: 0x%x\n", reg_data->page_data.pddr_phy_info_page.pm_debug_indication);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pd_cat_val: 0x%x\n", reg_data->page_data.pddr_phy_info_page.pd_cat_val);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pd_catastrophic_enum: 0x%x\n", reg_data->page_data.pddr_phy_info_page.pd_catastrophic_enum);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "hst_cat_val: 0x%x\n", reg_data->page_data.pddr_phy_info_page.hst_cat_val);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "hst_catastrophic_enum: 0x%x\n", reg_data->page_data.pddr_phy_info_page.hst_catastrophic_enum);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "an_cat_val: 0x%x\n", reg_data->page_data.pddr_phy_info_page.an_cat_val);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "an_catastrophic_enum: 0x%x\n", reg_data->page_data.pddr_phy_info_page.an_catastrophic_enum);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pm_cat_val: 0x%x\n", reg_data->page_data.pddr_phy_info_page.pm_cat_val);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pm_catastrophic_enum: 0x%x\n", reg_data->page_data.pddr_phy_info_page.pm_catastrophic_enum);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pd_debug_indication: 0x%x\n", reg_data->page_data.pddr_phy_info_page.pd_debug_indication);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "psi_collision1: 0x%x\n", reg_data->page_data.pddr_phy_info_page.psi_collision1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "psi_collision2: 0x%x\n", reg_data->page_data.pddr_phy_info_page.psi_collision2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "hst_mismatch_reason: 0x%x\n", reg_data->page_data.pddr_phy_info_page.hst_mismatch_reason);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fp_signal_detect_count: 0x%x\n", reg_data->page_data.pddr_phy_info_page.fp_signal_detect_count);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pd_count: 0x%x\n", reg_data->page_data.pddr_phy_info_page.pd_count);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "nlpn_debug_ind_mask: 0x%x\n", reg_data->page_data.pddr_phy_info_page.nlpn_debug_ind_mask);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy2mod_speed_req: 0x%x\n", reg_data->page_data.pddr_phy_info_page.phy2mod_speed_req);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eeprom_prsnt: 0x%x\n", reg_data->page_data.pddr_phy_info_page.eeprom_prsnt);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "no_dme_mod: 0x%x\n", reg_data->page_data.pddr_phy_info_page.no_dme_mod);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "one_pll_mod: 0x%x\n", reg_data->page_data.pddr_phy_info_page.one_pll_mod);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy2mod_ack_lanes: 0x%x\n", reg_data->page_data.pddr_phy_info_page.phy2mod_ack_lanes);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy2mod_deactivate_lanes: 0x%x\n", reg_data->page_data.pddr_phy_info_page.phy2mod_deactivate_lanes);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_pkts_inc_s1: 0x%x\n", reg_data->page_data.pddr_phy_info_page.port_xmit_pkts_inc_s1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_pkts_inc_s0: 0x%x\n", reg_data->page_data.pddr_phy_info_page.port_xmit_pkts_inc_s0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_rx_frame_received_ok_s1: 0x%x\n", reg_data->page_data.pddr_phy_info_page.cnt_rx_frame_received_ok_s1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cnt_rx_frame_received_ok_s0: 0x%x\n", reg_data->page_data.pddr_phy_info_page.cnt_rx_frame_received_ok_s0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "macsec_en_plt1_s1: 0x%x\n", reg_data->page_data.pddr_phy_info_page.macsec_en_plt1_s1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "macsec_en_plt1_s0: 0x%x\n", reg_data->page_data.pddr_phy_info_page.macsec_en_plt1_s0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "macsec_en_plt0_s1: 0x%x\n", reg_data->page_data.pddr_phy_info_page.macsec_en_plt0_s1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "macsec_en_plt0_s0: 0x%x\n", reg_data->page_data.pddr_phy_info_page.macsec_en_plt0_s0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "reconciliation_mux_plt1: 0x%x\n", reg_data->page_data.pddr_phy_info_page.reconciliation_mux_plt1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "reconciliation_mux_plt0: 0x%x\n", reg_data->page_data.pddr_phy_info_page.reconciliation_mux_plt0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bypass_mux_plt1: 0x%x\n", reg_data->page_data.pddr_phy_info_page.tx_bypass_mux_plt1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bypass_mux_plt0: 0x%x\n", reg_data->page_data.pddr_phy_info_page.tx_bypass_mux_plt0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_bypass_mux_plt1: 0x%x\n", reg_data->page_data.pddr_phy_info_page.rx_bypass_mux_plt1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_bypass_mux_plt0: 0x%x\n", reg_data->page_data.pddr_phy_info_page.rx_bypass_mux_plt0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rtt_hdr_threshold: 0x%x\n", reg_data->page_data.pddr_phy_info_page.plr_rtt_hdr_threshold);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rtt_ndr_threshold: 0x%x\n", reg_data->page_data.pddr_phy_info_page.plr_rtt_ndr_threshold);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rtt_xdr_threshold: 0x%x\n", reg_data->page_data.pddr_phy_info_page.plr_rtt_xdr_threshold);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_MODULE_INFO_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_technology: 0x%x\n", reg_data->page_data.pddr_module_info.cable_technology);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_breakout: 0x%x\n", reg_data->page_data.pddr_module_info.cable_breakout);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ext_ethernet_compliance_code: 0x%x\n", reg_data->page_data.pddr_module_info.ext_ethernet_compliance_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ethernet_compliance_code: 0x%x\n", reg_data->page_data.pddr_module_info.ethernet_compliance_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_type: 0x%x\n", reg_data->page_data.pddr_module_info.cable_type);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_vendor: 0x%x\n", reg_data->page_data.pddr_module_info.cable_vendor);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_length: 0x%x\n", reg_data->page_data.pddr_module_info.cable_length);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_identifier: 0x%x\n", reg_data->page_data.pddr_module_info.cable_identifier);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_power_class: 0x%x\n", reg_data->page_data.pddr_module_info.cable_power_class);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "max_power: 0x%x\n", reg_data->page_data.pddr_module_info.max_power);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_rx_amp: 0x%x\n", reg_data->page_data.pddr_module_info.cable_rx_amp);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_rx_emphasis: 0x%x\n", reg_data->page_data.pddr_module_info.cable_rx_emphasis);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_tx_equalization: 0x%x\n", reg_data->page_data.pddr_module_info.cable_tx_equalization);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_attenuation_25g: 0x%x\n", reg_data->page_data.pddr_module_info.cable_attenuation_25g);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_attenuation_12g: 0x%x\n", reg_data->page_data.pddr_module_info.cable_attenuation_12g);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_attenuation_7g: 0x%x\n", reg_data->page_data.pddr_module_info.cable_attenuation_7g);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_attenuation_5g: 0x%x\n", reg_data->page_data.pddr_module_info.cable_attenuation_5g);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_rx_post_emphasis: 0x%x\n", reg_data->page_data.pddr_module_info.cable_rx_post_emphasis);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_cdr_cap: 0x%x\n", reg_data->page_data.pddr_module_info.rx_cdr_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_cdr_cap: 0x%x\n", reg_data->page_data.pddr_module_info.tx_cdr_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_cdr_state: 0x%x\n", reg_data->page_data.pddr_module_info.rx_cdr_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_cdr_state: 0x%x\n", reg_data->page_data.pddr_module_info.tx_cdr_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vendor_name: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", reg_data->page_data.pddr_module_info.vendor_name[0], reg_data->page_data.pddr_module_info.vendor_name[1], reg_data->page_data.pddr_module_info.vendor_name[2], reg_data->page_data.pddr_module_info.vendor_name[3], reg_data->page_data.pddr_module_info.vendor_name[4], reg_data->page_data.pddr_module_info.vendor_name[5], reg_data->page_data.pddr_module_info.vendor_name[6], reg_data->page_data.pddr_module_info.vendor_name[7], reg_data->page_data.pddr_module_info.vendor_name[8], reg_data->page_data.pddr_module_info.vendor_name[9], reg_data->page_data.pddr_module_info.vendor_name[10], reg_data->page_data.pddr_module_info.vendor_name[11], reg_data->page_data.pddr_module_info.vendor_name[12], reg_data->page_data.pddr_module_info.vendor_name[13], reg_data->page_data.pddr_module_info.vendor_name[14], reg_data->page_data.pddr_module_info.vendor_name[15]);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vendor_pn: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", reg_data->page_data.pddr_module_info.vendor_pn[0], reg_data->page_data.pddr_module_info.vendor_pn[1], reg_data->page_data.pddr_module_info.vendor_pn[2], reg_data->page_data.pddr_module_info.vendor_pn[3], reg_data->page_data.pddr_module_info.vendor_pn[4], reg_data->page_data.pddr_module_info.vendor_pn[5], reg_data->page_data.pddr_module_info.vendor_pn[6], reg_data->page_data.pddr_module_info.vendor_pn[7], reg_data->page_data.pddr_module_info.vendor_pn[8], reg_data->page_data.pddr_module_info.vendor_pn[9], reg_data->page_data.pddr_module_info.vendor_pn[10], reg_data->page_data.pddr_module_info.vendor_pn[11], reg_data->page_data.pddr_module_info.vendor_pn[12], reg_data->page_data.pddr_module_info.vendor_pn[13], reg_data->page_data.pddr_module_info.vendor_pn[14], reg_data->page_data.pddr_module_info.vendor_pn[15]);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vendor_rev: 0x%x\n", reg_data->page_data.pddr_module_info.vendor_rev);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_version: 0x%x\n", reg_data->page_data.pddr_module_info.fw_version);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vendor_sn: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", reg_data->page_data.pddr_module_info.vendor_sn[0], reg_data->page_data.pddr_module_info.vendor_sn[1], reg_data->page_data.pddr_module_info.vendor_sn[2], reg_data->page_data.pddr_module_info.vendor_sn[3], reg_data->page_data.pddr_module_info.vendor_sn[4], reg_data->page_data.pddr_module_info.vendor_sn[5], reg_data->page_data.pddr_module_info.vendor_sn[6], reg_data->page_data.pddr_module_info.vendor_sn[7], reg_data->page_data.pddr_module_info.vendor_sn[8], reg_data->page_data.pddr_module_info.vendor_sn[9], reg_data->page_data.pddr_module_info.vendor_sn[10], reg_data->page_data.pddr_module_info.vendor_sn[11], reg_data->page_data.pddr_module_info.vendor_sn[12], reg_data->page_data.pddr_module_info.vendor_sn[13], reg_data->page_data.pddr_module_info.vendor_sn[14], reg_data->page_data.pddr_module_info.vendor_sn[15]);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "temperature: 0x%x\n", reg_data->page_data.pddr_module_info.temperature);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "voltage: 0x%x\n", reg_data->page_data.pddr_module_info.voltage);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane0: 0x%x\n", reg_data->page_data.pddr_module_info.rx_power_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane1: 0x%x\n", reg_data->page_data.pddr_module_info.rx_power_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane2: 0x%x\n", reg_data->page_data.pddr_module_info.rx_power_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane3: 0x%x\n", reg_data->page_data.pddr_module_info.rx_power_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane4: 0x%x\n", reg_data->page_data.pddr_module_info.rx_power_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane5: 0x%x\n", reg_data->page_data.pddr_module_info.rx_power_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane6: 0x%x\n", reg_data->page_data.pddr_module_info.rx_power_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane7: 0x%x\n", reg_data->page_data.pddr_module_info.rx_power_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane0: 0x%x\n", reg_data->page_data.pddr_module_info.tx_power_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane1: 0x%x\n", reg_data->page_data.pddr_module_info.tx_power_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane2: 0x%x\n", reg_data->page_data.pddr_module_info.tx_power_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane3: 0x%x\n", reg_data->page_data.pddr_module_info.tx_power_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane4: 0x%x\n", reg_data->page_data.pddr_module_info.tx_power_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane5: 0x%x\n", reg_data->page_data.pddr_module_info.tx_power_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane6: 0x%x\n", reg_data->page_data.pddr_module_info.tx_power_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane7: 0x%x\n", reg_data->page_data.pddr_module_info.tx_power_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane0: 0x%x\n", reg_data->page_data.pddr_module_info.tx_bias_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane1: 0x%x\n", reg_data->page_data.pddr_module_info.tx_bias_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane2: 0x%x\n", reg_data->page_data.pddr_module_info.tx_bias_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane3: 0x%x\n", reg_data->page_data.pddr_module_info.tx_bias_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane4: 0x%x\n", reg_data->page_data.pddr_module_info.tx_bias_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane5: 0x%x\n", reg_data->page_data.pddr_module_info.tx_bias_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane6: 0x%x\n", reg_data->page_data.pddr_module_info.tx_bias_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane7: 0x%x\n", reg_data->page_data.pddr_module_info.tx_bias_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "temperature_high_th: 0x%x\n", reg_data->page_data.pddr_module_info.temperature_high_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "temperature_low_th: 0x%x\n", reg_data->page_data.pddr_module_info.temperature_low_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "voltage_high_th: 0x%x\n", reg_data->page_data.pddr_module_info.voltage_high_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "voltage_low_th: 0x%x\n", reg_data->page_data.pddr_module_info.voltage_low_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_high_th: 0x%x\n", reg_data->page_data.pddr_module_info.rx_power_high_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_low_th: 0x%x\n", reg_data->page_data.pddr_module_info.rx_power_low_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_high_th: 0x%x\n", reg_data->page_data.pddr_module_info.tx_power_high_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_low_th: 0x%x\n", reg_data->page_data.pddr_module_info.tx_power_low_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_high_th: 0x%x\n", reg_data->page_data.pddr_module_info.tx_bias_high_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_low_th: 0x%x\n", reg_data->page_data.pddr_module_info.tx_bias_low_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "module_st: 0x%x\n", reg_data->page_data.pddr_module_info.module_st);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_type: 0x%x\n", reg_data->page_data.pddr_module_info.rx_power_type);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "did_cap: 0x%x\n", reg_data->page_data.pddr_module_info.did_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_output_valid_cap: 0x%x\n", reg_data->page_data.pddr_module_info.rx_output_valid_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "smf_length: 0x%x\n", reg_data->page_data.pddr_module_info.smf_length);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "wavelength: 0x%x\n", reg_data->page_data.pddr_module_info.wavelength);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "active_set_host_compliance_code: 0x%x\n", reg_data->page_data.pddr_module_info.active_set_host_compliance_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "active_set_media_compliance_code: 0x%x\n", reg_data->page_data.pddr_module_info.active_set_media_compliance_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_compliance_code: 0x%x\n", reg_data->page_data.pddr_module_info.ib_compliance_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "nbr250: 0x%x\n", reg_data->page_data.pddr_module_info.nbr250);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "nbr100: 0x%x\n", reg_data->page_data.pddr_module_info.nbr100);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "monitor_cap_mask: 0x%x\n", reg_data->page_data.pddr_module_info.monitor_cap_mask);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_width: 0x%x\n", reg_data->page_data.pddr_module_info.ib_width);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane0: 0x%x\n", reg_data->page_data.pddr_module_info.dp_st_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane1: 0x%x\n", reg_data->page_data.pddr_module_info.dp_st_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane2: 0x%x\n", reg_data->page_data.pddr_module_info.dp_st_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane3: 0x%x\n", reg_data->page_data.pddr_module_info.dp_st_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane4: 0x%x\n", reg_data->page_data.pddr_module_info.dp_st_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane5: 0x%x\n", reg_data->page_data.pddr_module_info.dp_st_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane6: 0x%x\n", reg_data->page_data.pddr_module_info.dp_st_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane7: 0x%x\n", reg_data->page_data.pddr_module_info.dp_st_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "length_om2: 0x%x\n", reg_data->page_data.pddr_module_info.length_om2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "length_om3: 0x%x\n", reg_data->page_data.pddr_module_info.length_om3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "length_om4: 0x%x\n", reg_data->page_data.pddr_module_info.length_om4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "length_om5: 0x%x\n", reg_data->page_data.pddr_module_info.length_om5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "length_om1: 0x%x\n", reg_data->page_data.pddr_module_info.length_om1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "wavelength_tolerance: 0x%x\n", reg_data->page_data.pddr_module_info.wavelength_tolerance);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "memory_map_rev: 0x%x\n", reg_data->page_data.pddr_module_info.memory_map_rev);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "memory_map_compliance: 0x%x\n", reg_data->page_data.pddr_module_info.memory_map_compliance);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "date_code: 0x%llx\n", reg_data->page_data.pddr_module_info.date_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "connector_type: 0x%x\n", reg_data->page_data.pddr_module_info.connector_type);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vendor_oui: 0x%x\n", reg_data->page_data.pddr_module_info.vendor_oui);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_input_freq_sync: 0x%x\n", reg_data->page_data.pddr_module_info.tx_input_freq_sync);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_output_valid: 0x%x\n", reg_data->page_data.pddr_module_info.rx_output_valid);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "max_fiber_length: 0x%x\n", reg_data->page_data.pddr_module_info.max_fiber_length);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "error_code: 0x%x\n", reg_data->page_data.pddr_module_info.error_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_PORT_EVENTS_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "invalid_fsm_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.invalid_fsm_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "invalid_fsm_ps: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.invalid_fsm_ps);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_false_ready_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.kr_false_ready_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_false_ready: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.kr_false_ready);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_req_nack_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.mod_req_nack_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_req_nack: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.mod_req_nack);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_req_busy_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.mod_req_busy_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_req_busy: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.mod_req_busy);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_config_to_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.mod_config_to_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_config_to: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.mod_config_to);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_adapt_faild_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.mod_adapt_faild_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_adapt_faild: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.mod_adapt_faild);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pm_fifo_full_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.pm_fifo_full_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pm_fifo_full: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.pm_fifo_full);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "protocol_check_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.protocol_check_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "protocol_check: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.protocol_check);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "input_event_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.input_event_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "input_event: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.input_event);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lane_mapping_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.lane_mapping_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lane_mapping: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.lane_mapping);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "qsfp_zero_atten_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.qsfp_zero_atten_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "qsfp_zero_atten: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.qsfp_zero_atten);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mono_reach_low_limit_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.mono_reach_low_limit_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mono_reach_low_limit: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.mono_reach_low_limit);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mono_reach_high_limit_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.mono_reach_high_limit_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mono_reach_high_limit: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.mono_reach_high_limit);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mono_flow_height_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.mono_flow_height_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mono_flow_height: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.mono_flow_height);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "single_gains_bad_val_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.single_gains_bad_val_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "single_gains_bad_val: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.single_gains_bad_val);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "init_all_gains_bad_val_sv: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.init_all_gains_bad_val_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "init_all_gains_bad_val: 0x%x\n", reg_data->page_data.pddr_port_events_page_layout.init_all_gains_bad_val);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        for (i = 0; i < SXD_PDDR_CLR_MASK_NUM; i++) {
            snp_res = snprintf(buffer, buffer_length - buffer_size, "clr_mask[%d]: 0x%x\n", i, reg_data->page_data.pddr_port_events_page_layout.clr_mask[i]);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_DEVICE_EVENTS_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "invalid_port_access_sv: 0x%x\n", reg_data->page_data.pddr_device_events_page.invalid_port_access_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "invalid_port_access: 0x%x\n", reg_data->page_data.pddr_device_events_page.invalid_port_access);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_state_sv_1: 0x%x\n", reg_data->page_data.pddr_device_events_page.pll_state_sv_1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_state_mask_center1: 0x%x\n", reg_data->page_data.pddr_device_events_page.pll_state_mask_center1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_state_sv_0: 0x%x\n", reg_data->page_data.pddr_device_events_page.pll_state_sv_0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_state_mask_center0: 0x%x\n", reg_data->page_data.pddr_device_events_page.pll_state_mask_center0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "main_irisc_timeout: 0x%x\n", reg_data->page_data.pddr_device_events_page.main_irisc_timeout);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tile_irisc_timeout: 0x%x\n", reg_data->page_data.pddr_device_events_page.tile_irisc_timeout);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout0: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout1: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout2: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout3: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout4: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cr_space_timeout_mcm_main: 0x%x\n", reg_data->page_data.pddr_device_events_page.cr_space_timeout_mcm_main);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cr_space_timeout_sv: 0x%x\n", reg_data->page_data.pddr_device_events_page.cr_space_timeout_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cr_space_timeout: 0x%x\n", reg_data->page_data.pddr_device_events_page.cr_space_timeout);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "analog_phy_to_sv: 0x%x\n", reg_data->page_data.pddr_device_events_page.analog_phy_to_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "analog_phy_to: 0x%x\n", reg_data->page_data.pddr_device_events_page.analog_phy_to);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "logical_phy_to_sv: 0x%x\n", reg_data->page_data.pddr_device_events_page.logical_phy_to_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "logical_phy_to: 0x%x\n", reg_data->page_data.pddr_device_events_page.logical_phy_to);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "varactors_calib_fail_center1_sv: 0x%x\n", reg_data->page_data.pddr_device_events_page.varactors_calib_fail_center1_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "varactors_calib_fail_center1: 0x%x\n", reg_data->page_data.pddr_device_events_page.varactors_calib_fail_center1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "varactors_calib_fail_center0_sv: 0x%x\n", reg_data->page_data.pddr_device_events_page.varactors_calib_fail_center0_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "varactors_calib_fail_center0: 0x%x\n", reg_data->page_data.pddr_device_events_page.varactors_calib_fail_center0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "irisc_stuck_mask_sv: 0x%x\n", reg_data->page_data.pddr_device_events_page.irisc_stuck_mask_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "irisc_stuck_mask: 0x%x\n", reg_data->page_data.pddr_device_events_page.irisc_stuck_mask);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_lock_sv_1: 0x%x\n", reg_data->page_data.pddr_device_events_page.pll_lock_sv_1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_unlocl_mask_center1: 0x%x\n", reg_data->page_data.pddr_device_events_page.pll_unlocl_mask_center1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_lock_sv_0: 0x%x\n", reg_data->page_data.pddr_device_events_page.pll_lock_sv_0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_unlocl_mask_center0: 0x%x\n", reg_data->page_data.pddr_device_events_page.pll_unlocl_mask_center0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uc_stack_overflow: 0x%x\n", reg_data->page_data.pddr_device_events_page.uc_stack_overflow);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uc_crspace_timeout: 0x%x\n", reg_data->page_data.pddr_device_events_page.uc_crspace_timeout);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pwr_governor_err_sv: 0x%x\n", reg_data->page_data.pddr_device_events_page.pwr_governor_err_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pwr_governor_err: 0x%x\n", reg_data->page_data.pddr_device_events_page.pwr_governor_err);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "iopl_err_center1_sv: 0x%x\n", reg_data->page_data.pddr_device_events_page.iopl_err_center1_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "iopl_err_center1: 0x%x\n", reg_data->page_data.pddr_device_events_page.iopl_err_center1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "iopl_err_center0_sv: 0x%x\n", reg_data->page_data.pddr_device_events_page.iopl_err_center0_sv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "iopl_err_center0: 0x%x\n", reg_data->page_data.pddr_device_events_page.iopl_err_center0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        for (i = 0; i < SXD_PDDR_CLR_MASK_NUM; i++) {
            snp_res = snprintf(buffer, buffer_length - buffer_size, "clr_mask[%d]: 0x%x\n", i, reg_data->page_data.pddr_device_events_page.clr_mask[i]);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "main_irisc_address: 0x%x\n", reg_data->page_data.pddr_device_events_page.main_irisc_address);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "main_irisc_ip: 0x%x\n", reg_data->page_data.pddr_device_events_page.main_irisc_ip);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tile_irisc_address: 0x%x\n", reg_data->page_data.pddr_device_events_page.tile_irisc_address);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tile_irisc_ip: 0x%x\n", reg_data->page_data.pddr_device_events_page.tile_irisc_ip);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout0_address: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout0_address);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout1_address: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout1_address);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout2_address: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout2_address);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout3_address: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout3_address);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout4_address: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout4_address);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout0_cluster: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout0_cluster);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout1_cluster: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout1_cluster);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout2_cluster: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout2_cluster);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout3_cluster: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout3_cluster);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout4_cluster: 0x%x\n", reg_data->page_data.pddr_device_events_page.plu_timeout4_cluster);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "irisc_tile_idx: 0x%x\n", reg_data->page_data.pddr_device_events_page.irisc_tile_idx);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uc_crspace_timeout_lane: 0x%x\n", reg_data->page_data.pddr_device_events_page.uc_crspace_timeout_lane);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uc_crspace_timeout_cl: 0x%x\n", reg_data->page_data.pddr_device_events_page.uc_crspace_timeout_cl);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uc_stack_overflow_lane: 0x%x\n", reg_data->page_data.pddr_device_events_page.uc_stack_overflow_lane);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uc_stack_overflow_cl: 0x%x\n", reg_data->page_data.pddr_device_events_page.uc_stack_overflow_cl);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_DOWN_INFO_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "down_blame: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.down_blame);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_reason_opcode: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.local_reason_opcode);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "remote_reason_opcode: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.remote_reason_opcode);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ts1_opcode: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.ts1_opcode);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "e2e_reason_opcode: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.e2e_reason_opcode);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cons_raw_norm_ber: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.cons_raw_norm_ber);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "last_raw_ber_coef: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.last_raw_ber_coef);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "last_raw_ber_magnitude: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.last_raw_ber_magnitude);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_symbol_ber_alarms: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.num_of_symbol_ber_alarms);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "min_raw_ber_coef: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.min_raw_ber_coef);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "min_raw_ber_magnitude: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.min_raw_ber_magnitude);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "max_raw_ber_coef: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.max_raw_ber_coef);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "max_raw_ber_magnitude: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.max_raw_ber_magnitude);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_eff_ber_alarms: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.num_of_eff_ber_alarms);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_raw_ber_alarms: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.num_of_raw_ber_alarms);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_to_link_down_to_disable: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.time_to_link_down_to_disable);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_to_link_down_to_rx_loss: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.time_to_link_down_to_rx_loss);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cons_eff_norm_ber: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.cons_eff_norm_ber);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "last_eff_ber_coef: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.last_eff_ber_coef);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "last_eff_ber_magnitude: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.last_eff_ber_magnitude);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "min_eff_ber_coef: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.min_eff_ber_coef);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "min_eff_ber_magnitude: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.min_eff_ber_magnitude);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cons_symbol_norm_ber: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.cons_symbol_norm_ber);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "max_symbol_ber_coef: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.max_symbol_ber_coef);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "max_symbol_ber_magnitude: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.max_symbol_ber_magnitude);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "max_eff_ber_coef: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.max_eff_ber_coef);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "max_eff_ber_magnitude: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.max_eff_ber_magnitude);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "last_symbol_ber_coef: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.last_symbol_ber_coef);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "last_symbol_ber_magnitude: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.last_symbol_ber_magnitude);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "min_symbol_ber_coef: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.min_symbol_ber_coef);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "min_symbol_ber_magnitude: 0x%x\n", reg_data->page_data.pddr_link_down_info_page.min_symbol_ber_magnitude);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_DOWN_EVENTS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_port_events: 0x%x\n", reg_data->page_data.pddr_link_down_events_page.ib_port_events);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "etherent_port_events: 0x%x\n", reg_data->page_data.pddr_link_down_events_page.etherent_port_events);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "general_port_events: 0x%x\n", reg_data->page_data.pddr_link_down_events_page.general_port_events);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_UP_INFO_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "up_reason_pwr: 0x%x\n", reg_data->page_data.pddr_link_up_info_page.up_reason_pwr);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "up_reason_drv: 0x%x\n", reg_data->page_data.pddr_link_up_info_page.up_reason_drv);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "up_reason_mng: 0x%x\n", reg_data->page_data.pddr_link_up_info_page.up_reason_mng);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_to_link_up: 0x%x\n", reg_data->page_data.pddr_link_up_info_page.time_to_link_up);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lt_cnt: 0x%x\n", reg_data->page_data.pddr_link_up_info_page.lt_cnt);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fast_link_up_status: 0x%x\n", reg_data->page_data.pddr_link_up_info_page.fast_link_up_status);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_to_link_up_phy_up_to_active: 0x%x\n", reg_data->page_data.pddr_link_up_info_page.time_to_link_up_phy_up_to_active);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_to_link_up_sd_to_phy_up: 0x%x\n", reg_data->page_data.pddr_link_up_info_page.time_to_link_up_sd_to_phy_up);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_to_link_up_disable_to_sd: 0x%x\n", reg_data->page_data.pddr_link_up_info_page.time_to_link_up_disable_to_sd);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_to_link_up_disable_to_pd: 0x%x\n", reg_data->page_data.pddr_link_up_info_page.time_to_link_up_disable_to_pd);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_MODULE_LATCHED_FLAG_INFO_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "temp_flags: 0x%x\n", reg_data->page_data.module_latched_flag_info.temp_flags);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vcc_flags: 0x%x\n", reg_data->page_data.module_latched_flag_info.vcc_flags);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_fw_fault: 0x%x\n", reg_data->page_data.module_latched_flag_info.mod_fw_fault);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_fw_fault: 0x%x\n", reg_data->page_data.module_latched_flag_info.dp_fw_fault);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_los_cap: 0x%x\n", reg_data->page_data.module_latched_flag_info.rx_los_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_fault: 0x%x\n", reg_data->page_data.module_latched_flag_info.tx_fault);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_los: 0x%x\n", reg_data->page_data.module_latched_flag_info.tx_los);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_cdr_lol: 0x%x\n", reg_data->page_data.module_latched_flag_info.tx_cdr_lol);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_ad_eq_fault: 0x%x\n", reg_data->page_data.module_latched_flag_info.tx_ad_eq_fault);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_hi_al: 0x%x\n", reg_data->page_data.module_latched_flag_info.tx_power_hi_al);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lo_al: 0x%x\n", reg_data->page_data.module_latched_flag_info.tx_power_lo_al);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_hi_war: 0x%x\n", reg_data->page_data.module_latched_flag_info.tx_power_hi_war);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lo_war: 0x%x\n", reg_data->page_data.module_latched_flag_info.tx_power_lo_war);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_hi_al: 0x%x\n", reg_data->page_data.module_latched_flag_info.tx_bias_hi_al);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lo_al: 0x%x\n", reg_data->page_data.module_latched_flag_info.tx_bias_lo_al);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_hi_war: 0x%x\n", reg_data->page_data.module_latched_flag_info.tx_bias_hi_war);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lo_war: 0x%x\n", reg_data->page_data.module_latched_flag_info.tx_bias_lo_war);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_los: 0x%x\n", reg_data->page_data.module_latched_flag_info.rx_los);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_cdr_lol: 0x%x\n", reg_data->page_data.module_latched_flag_info.rx_cdr_lol);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_hi_al: 0x%x\n", reg_data->page_data.module_latched_flag_info.rx_power_hi_al);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lo_al: 0x%x\n", reg_data->page_data.module_latched_flag_info.rx_power_lo_al);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_hi_war: 0x%x\n", reg_data->page_data.module_latched_flag_info.rx_power_hi_war);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lo_war: 0x%x\n", reg_data->page_data.module_latched_flag_info.rx_power_lo_war);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_output_valid_change: 0x%x\n", reg_data->page_data.module_latched_flag_info.rx_output_valid_change);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "flag_in_use: 0x%x\n", reg_data->page_data.module_latched_flag_info.flag_in_use);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_DOWN_INFO_EXT_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cause_as_detected_not_on_slot: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.cause_as_detected_not_on_slot);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cause_high_ser: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.cause_high_ser);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cause_rs_rx_lane0_symbol_error: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.cause_rs_rx_lane0_symbol_error);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cause_tx_lane_fifo_underrun_l0: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.cause_tx_lane_fifo_underrun_l0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cause_deskew_fifo_overrun: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.cause_deskew_fifo_overrun);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cause_fec_rx_sync_m_reached_max0: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.cause_fec_rx_sync_m_reached_max0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_error_counter_lo: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.symbol_error_counter_lo);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_error_counter_hi: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.symbol_error_counter_hi);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uncorrectable_block_counter_lo: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.uncorrectable_block_counter_lo);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uncorrectable_block_counter_hi: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.uncorrectable_block_counter_hi);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_fail_due_align_loss: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.link_fail_due_align_loss);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "block_lock_mask_at_fail_port1: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.block_lock_mask_at_fail_port1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "block_lock_mask_at_fail_port0: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.block_lock_mask_at_fail_port0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_down_counter: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.link_down_counter);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "effective_ber_coef: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.effective_ber_coef);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "effective_ber_magnitude: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.effective_ber_magnitude);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.raw_ber_coef);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude: 0x%x\n", reg_data->page_data.pddr_link_down_info_ext_16nm_lr.raw_ber_magnitude);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_PARTNER_INFO_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "info_supported_mask: 0x%x\n", reg_data->page_data.pddr_link_partner_info.info_supported_mask);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "partner_local_port: 0x%x\n", reg_data->page_data.pddr_link_partner_info.partner_local_port);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "partner_module_type: 0x%x\n", reg_data->page_data.pddr_link_partner_info.partner_module_type);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "partner_id_lsb: 0x%x\n", reg_data->page_data.pddr_link_partner_info.partner_id_lsb);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_PHY_ISR_TRACKING_INFO_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "isr_access_enums: 0x%x\n", reg_data->page_data.pddr_phy_isr_tracking_info_page.isr_access_enums);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "isr_track_mod: 0x%x\n", reg_data->page_data.pddr_phy_isr_tracking_info_page.isr_track_mod);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "isr_track_enum: 0x%x\n", reg_data->page_data.pddr_phy_isr_tracking_info_page.isr_track_enum);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "max_isr_enum: 0x%x\n", reg_data->page_data.pddr_phy_isr_tracking_info_page.max_isr_enum);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        for (i = 0; i < SXD_PDDR_MAX_TIME_ISR_NUM; i++) {
            snp_res = snprintf(buffer, buffer_length - buffer_size, "max_time_isr[%d]: 0x%x\n", i, reg_data->page_data.pddr_phy_isr_tracking_info_page.max_time_isr[i]);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_DOWN_INFO_BUFFER_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tracer_sel: 0x%x\n", reg_data->page_data.pddr_link_down_info_buffer_page.tracer_sel);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        for (i = 0; i < SXD_PDDR_LINK_DOWN_TRACER_NUM; i++) {
            for (j = 0; j < SXD_PDDR_ARRAY512_AUTO_NUM; j++) {
                snp_res = snprintf(buffer, buffer_length - buffer_size, "array512_auto[%d]: 0x%x\n", j, reg_data->page_data.pddr_link_down_info_buffer_page.link_down_tracer[i].array512_auto[j]);
                VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
                buffer += snp_res;
                buffer_size += snp_res;
            }
            snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        break;

    case SXD_PDDR_PAGE_SELECT_MNG_DEBUG_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_module_state: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.fw_module_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane7: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.fw_dp_state_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane6: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.fw_dp_state_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane5: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.fw_dp_state_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane4: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.fw_dp_state_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane3: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.fw_dp_state_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane2: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.fw_dp_state_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane1: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.fw_dp_state_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane0: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.fw_dp_state_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane7: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dp_req_status_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane6: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dp_req_status_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane5: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dp_req_status_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane4: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dp_req_status_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane3: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dp_req_status_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane2: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dp_req_status_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane1: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dp_req_status_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane0: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dp_req_status_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane7: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dpsm_apply_state_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane6: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dpsm_apply_state_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane5: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dpsm_apply_state_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane4: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dpsm_apply_state_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane3: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dpsm_apply_state_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane2: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dpsm_apply_state_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane1: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dpsm_apply_state_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane0: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.dpsm_apply_state_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "timer_left_for_dp_active_transition: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.timer_left_for_dp_active_transition);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "timer_left_for_high_pwrt_transition: 0x%x\n", reg_data->page_data.pddr_mng_debug_page.timer_left_for_high_pwrt_transition);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_PHY_DEBUG_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pport: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.pport);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "trigger_active: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.trigger_active);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "trigger_cond_state_event_val: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.trigger_cond_state_event_val);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "trigger_cond_state_or_event: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.trigger_cond_state_or_event);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "trigger_cond_fsm: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.trigger_cond_fsm);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pre_trigger_buff_mode: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.pre_trigger_buff_mode);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tracer_mode: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.tracer_mode);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "reset_tracer: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.reset_tracer);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tracer_enable: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.tracer_enable);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fsm_mask: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.fsm_mask);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "trigger_ptr: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.trigger_ptr);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "buffer_size: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.buffer_size);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ptr_log_data: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.ptr_log_data);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ptr_next_write: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.ptr_next_write);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "buffer_base_address: 0x%x\n", reg_data->page_data.pddr_phy_debug_page.buffer_base_address);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    default:
        /* Other types not supported yet */
        break;
    }

    return buffer_size;
}

int sx_spice_access_reg_pmdr_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_pmdr_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "status: 0x%x\n", reg_data->status);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "version: 0x%x\n", reg_data->version);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->local_port, reg_data->lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->pnat);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "gb_valid: 0x%x\n", reg_data->gb_valid);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "mcm_tile_valid: 0x%x\n", reg_data->mcm_tile_valid);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "scc_valid: 0x%x\n", reg_data->scc_valid);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pport: 0x%x\n", reg_data->pport);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "module: 0x%x\n", reg_data->module);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "cluster: 0x%x\n", reg_data->cluster);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pport_msb: 0x%x\n", reg_data->pport_msb);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "clp_4x: 0x%x\n", reg_data->clp_4x);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "clp_1x: 0x%x\n", reg_data->clp_1x);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "gb_dp_num: 0x%x\n", reg_data->gb_dp_num);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "split: 0x%x\n", reg_data->split);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "swid: 0x%x\n", reg_data->swid);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "module_lane_mask: 0x%x\n", reg_data->module_lane_mask);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_port: 0x%x\n", reg_data->ib_port);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "label_port_query: 0x%x\n", reg_data->label_port_query);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port_query: 0x%x\n", reg_data->local_port_query);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "usr_sd_4x_tx: 0x%x\n", reg_data->usr_sd_4x_tx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "usr_sd_4x_rx: 0x%x\n", reg_data->usr_sd_4x_rx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lp_query_msb: 0x%x\n", reg_data->lp_query_msb);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "slot_index: 0x%x\n", reg_data->slot_index);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "tile_cluster: 0x%x\n", reg_data->tile_cluster);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "mcm_tile_num: 0x%x\n", reg_data->mcm_tile_num);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "tile_pport: 0x%x\n", reg_data->tile_pport);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "gearbox_die_num: 0x%x\n", reg_data->gearbox_die_num);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl_num: 0x%x\n", reg_data->vl_num);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane7_physical_rx: 0x%x\n", reg_data->lane7_physical_rx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane6_physical_rx: 0x%x\n", reg_data->lane6_physical_rx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane5_physical_rx: 0x%x\n", reg_data->lane5_physical_rx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane4_physical_rx: 0x%x\n", reg_data->lane4_physical_rx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane3_physical_rx: 0x%x\n", reg_data->lane3_physical_rx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane2_physical_rx: 0x%x\n", reg_data->lane2_physical_rx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane1_physical_rx: 0x%x\n", reg_data->lane1_physical_rx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane0_physical_rx: 0x%x\n", reg_data->lane0_physical_rx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_index: 0x%x\n", reg_data->pll_index);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane7_physical_tx: 0x%x\n", reg_data->lane7_physical_tx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane6_physical_tx: 0x%x\n", reg_data->lane6_physical_tx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane5_physical_tx: 0x%x\n", reg_data->lane5_physical_tx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane4_physical_tx: 0x%x\n", reg_data->lane4_physical_tx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane3_physical_tx: 0x%x\n", reg_data->lane3_physical_tx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane2_physical_tx: 0x%x\n", reg_data->lane2_physical_tx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane1_physical_tx: 0x%x\n", reg_data->lane1_physical_tx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane0_physical_tx: 0x%x\n", reg_data->lane0_physical_tx);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl7_lane_map: 0x%x\n", reg_data->vl7_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl6_lane_map: 0x%x\n", reg_data->vl6_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl5_lane_map: 0x%x\n", reg_data->vl5_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl4_lane_map: 0x%x\n", reg_data->vl4_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl3_lane_map: 0x%x\n", reg_data->vl3_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl2_lane_map: 0x%x\n", reg_data->vl2_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl1_lane_map: 0x%x\n", reg_data->vl1_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl0_lane_map: 0x%x\n", reg_data->vl0_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl15_lane_map: 0x%x\n", reg_data->vl15_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl14_lane_map: 0x%x\n", reg_data->vl14_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl13_lane_map: 0x%x\n", reg_data->vl13_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl12_lane_map: 0x%x\n", reg_data->vl12_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl11_lane_map: 0x%x\n", reg_data->vl11_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl10_lane_map: 0x%x\n", reg_data->vl10_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl9_lane_map: 0x%x\n", reg_data->vl9_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl8_lane_map: 0x%x\n", reg_data->vl8_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl23_lane_map: 0x%x\n", reg_data->vl23_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl22_lane_map: 0x%x\n", reg_data->vl22_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl21_lane_map: 0x%x\n", reg_data->vl21_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl20_lane_map: 0x%x\n", reg_data->vl20_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl19_lane_map: 0x%x\n", reg_data->vl19_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl18_lane_map: 0x%x\n", reg_data->vl18_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl17_lane_map: 0x%x\n", reg_data->vl17_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl16_lane_map: 0x%x\n", reg_data->vl16_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl31_lane_map: 0x%x\n", reg_data->vl31_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl30_lane_map: 0x%x\n", reg_data->vl30_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl29_lane_map: 0x%x\n", reg_data->vl29_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl28_lane_map: 0x%x\n", reg_data->vl28_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl27_lane_map: 0x%x\n", reg_data->vl27_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl26_lane_map: 0x%x\n", reg_data->vl26_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl25_lane_map: 0x%x\n", reg_data->vl25_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl24_lane_map: 0x%x\n", reg_data->vl24_lane_map);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "physical_tx_cluster: 0x%x\n", reg_data->physical_tx_cluster);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "physical_rx_cluster: 0x%x\n", reg_data->physical_rx_cluster);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "scc_hs_lanes: 0x%x\n", reg_data->scc_hs_lanes);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int sx_spice_access_reg_pphcr_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_pphcr_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint32_t i = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "active_hist_type: 0x%x\n", reg_data->active_hist_type);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->local_port, reg_data->lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->pnat);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "we: 0x%x\n", reg_data->we);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_bins: 0x%x\n", reg_data->num_of_bins);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "hist_type: 0x%x\n", reg_data->hist_type);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "hist_max_measurement: 0x%x\n", reg_data->hist_max_measurement);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "hist_min_measurement: 0x%x\n", reg_data->hist_min_measurement);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    for (i = 0; i < SXD_PPHCR_BIN_RANGE_NUM; i++) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "high_val: 0x%x\n", reg_data->bin_range[i].high_val);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "low_val: 0x%x\n", reg_data->bin_range[i].low_val);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }

    return buffer_size;
}

int sx_spice_access_reg_sllm_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_sllm_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "status: 0x%x\n", reg_data->status);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "version: 0x%x\n", reg_data->version);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->local_port, reg_data->lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->pnat);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane: 0x%x\n", reg_data->lane);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "port_type: 0x%x\n", reg_data->port_type);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "c_db: 0x%x\n", reg_data->c_db);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;
    if ((reg_data->port_type == SXD_SLLM_PORT_TYPE_NETWORK_PORT_E) && (reg_data->version == SXD_SLLM_VERSION_PROD_16NM_E)) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lm_active: 0x%x\n", reg_data->page_data.sllm_16nm.lm_active);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lm_was_active: 0x%x\n", reg_data->page_data.sllm_16nm.lm_was_active);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pib_gw_lock: 0x%x\n", reg_data->page_data.sllm_16nm.pib_gw_lock);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lm_en: 0x%x\n", reg_data->page_data.sllm_16nm.lm_en);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lm_clk90_fl_err_max: 0x%x\n", reg_data->page_data.sllm_16nm.lm_clk90_fl_err_max);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lm_clk90_fl_err_acc: 0x%x\n", reg_data->page_data.sllm_16nm.lm_clk90_fl_err_acc);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib3_max_lm_90_tries: 0x%x\n", reg_data->page_data.sllm_16nm.ib3_max_lm_90_tries);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lm_counter_up: 0x%x\n", reg_data->page_data.sllm_16nm.lm_counter_up);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib1_max_lm_90_tries: 0x%x\n", reg_data->page_data.sllm_16nm.ib1_max_lm_90_tries);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lm_counter_mid: 0x%x\n", reg_data->page_data.sllm_16nm.lm_counter_mid);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lm_counter_dn: 0x%x\n", reg_data->page_data.sllm_16nm.lm_counter_dn);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }

    if ((reg_data->port_type == SXD_SLLM_PORT_TYPE_USR_MAIN_E || reg_data->port_type == SXD_SLLM_PORT_TYPE_USR_TILE_E) && (reg_data->version == SXD_SLLM_VERSION_PROD_16NM_E)) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "enable_lm: 0x%x\n", reg_data->page_data.sllm_usr.enable_lm);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "enable_phase_maintenance: 0x%x\n", reg_data->page_data.sllm_usr.enable_phase_maintenance);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "enable_offset_maintenance: 0x%x\n", reg_data->page_data.sllm_usr.enable_offset_maintenance);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lm_catastrophic_bit: 0x%x\n", reg_data->page_data.sllm_usr.lm_catastrophic_bit);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lm_activation_counter: 0x%x\n", reg_data->page_data.sllm_usr.lm_activation_counter);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lm_fixes_counter: 0x%x\n", reg_data->page_data.sllm_usr.lm_fixes_counter);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lane_under_maintenance: 0x%x\n", reg_data->page_data.sllm_usr.lane_under_maintenance);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "optimal_phase: 0x%x\n", reg_data->page_data.sllm_usr.optimal_phase);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_tuning_error: 0x%x\n", reg_data->page_data.sllm_usr.link_tuning_error);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lane_correctable_errors: 0x%x\n", reg_data->page_data.sllm_usr.lane_correctable_errors);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }

    if ((reg_data->port_type == SXD_SLLM_PORT_TYPE_NETWORK_PORT_E) && (reg_data->version == SXD_SLLM_VERSION_PROD_7NM_E)) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ctle_peq_en: 0x%x\n", reg_data->page_data.sllm_7nm.ctle_peq_en);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "peq_tsense_en: 0x%x\n", reg_data->page_data.sllm_7nm.peq_tsense_en);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "peq_f1_adapt_skip: 0x%x\n", reg_data->page_data.sllm_7nm.peq_f1_adapt_skip);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vref_peq_en: 0x%x\n", reg_data->page_data.sllm_7nm.vref_peq_en);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dffe_peq_scout_skip: 0x%x\n", reg_data->page_data.sllm_7nm.dffe_peq_scout_skip);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "peq_train_mode: 0x%x\n", reg_data->page_data.sllm_7nm.peq_train_mode);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "peq_vref_iters: 0x%x\n", reg_data->page_data.sllm_7nm.peq_vref_iters);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "peq_adc_vref_step: 0x%x\n", reg_data->page_data.sllm_7nm.peq_adc_vref_step);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dffe_peq_en: 0x%x\n", reg_data->page_data.sllm_7nm.dffe_peq_en);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "peq_dffe_iters: 0x%x\n", reg_data->page_data.sllm_7nm.peq_dffe_iters);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "peq_dffe_delay: 0x%x\n", reg_data->page_data.sllm_7nm.peq_dffe_delay);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ctle_peq_cnt: 0x%x\n", reg_data->page_data.sllm_7nm.ctle_peq_cnt);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ber_mon_mantissa: 0x%x\n", reg_data->page_data.sllm_7nm.ber_mon_mantissa);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ber_mon_exp: 0x%x\n", reg_data->page_data.sllm_7nm.ber_mon_exp);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
    }


    return buffer_size;
}


/* reg read */
ssize_t sx_spice_access_reg_mtcap_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                      *kbuffer = NULL;
    int                        err = 0;
    ssize_t                    size = 0;
    ssize_t                    print_data_size = 0;
    struct ku_mtcap_reg reg_data;
    const mtcap_data_t        *data = (mtcap_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for MTCAP SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.slot_index = data->slot_index;


    err = SX_SPICE_EMAD_ACCESS_REG(MTCAP, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_mtcap_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_mvcap_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                      *kbuffer = NULL;
    int                        err = 0;
    ssize_t                    size = 0;
    ssize_t                    print_data_size = 0;
    struct ku_mvcap_reg reg_data;
    const mvcap_data_t        *data = (mvcap_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for MVCAP SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.slot_index = data->slot_index;


    err = SX_SPICE_EMAD_ACCESS_REG(MVCAP, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_mvcap_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_mtmp_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    struct ku_mtmp_reg reg_data;
    const mtmp_data_t        *data = (mtmp_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for MTMP SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.i = data->i;
    reg_data.ig = data->ig;
    reg_data.asic_index = data->asic_index;
    reg_data.slot_index = data->slot_index;
    reg_data.sensor_index = data->sensor_index;


    err = SX_SPICE_EMAD_ACCESS_REG(MTMP, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_mtmp_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_mgir_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    struct ku_mgir_reg reg_data;
    const mgir_data_t        *data = (mgir_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for MGIR SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));


    err = SX_SPICE_EMAD_ACCESS_REG(MGIR, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_mgir_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_msgi_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    struct ku_msgi_reg reg_data;
    const msgi_data_t        *data = (msgi_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for MSGI SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));


    err = SX_SPICE_EMAD_ACCESS_REG(MSGI, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_msgi_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_mdir_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    struct ku_mdir_reg reg_data;
    const mdir_data_t        *data = (mdir_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for MDIR SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));


    err = SX_SPICE_EMAD_ACCESS_REG(MDIR, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_mdir_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_mopce_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                      *kbuffer = NULL;
    int                        err = 0;
    ssize_t                    size = 0;
    ssize_t                    print_data_size = 0;
    struct ku_mopce_reg reg_data;
    const mopce_data_t        *data = (mopce_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for MOPCE SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));


    err = SX_SPICE_EMAD_ACCESS_REG(MOPCE, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_mopce_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_spad_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    struct ku_spad_reg reg_data;
    const spad_data_t        *data = (spad_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for SPAD SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));


    err = SX_SPICE_EMAD_ACCESS_REG(SPAD, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_spad_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_spzr_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    struct ku_spzr_reg reg_data;
    const spzr_data_t        *data = (spzr_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for SPZR SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.swid = data->swid;
    reg_data.router_entity = data->router_entity;


    err = SX_SPICE_EMAD_ACCESS_REG(SPZR, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_spzr_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_ptys_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    struct ku_ptys_reg reg_data;
    const ptys_data_t        *data = (ptys_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for PTYS SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.local_port,
                                        reg_data.lp_msb,
                                        data->local_port);
    reg_data.pnat = data->pnat;
    reg_data.port_type = data->port_type;
    reg_data.plane_ind = data->plane_ind;
    reg_data.proto_mask = data->proto_mask;


    err = SX_SPICE_EMAD_ACCESS_REG(PTYS, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_ptys_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_ppcnt_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                      *kbuffer = NULL;
    int                        err = 0;
    ssize_t                    size = 0;
    ssize_t                    print_data_size = 0;
    struct ku_ppcnt_reg reg_data;
    const ppcnt_data_t        *data = (ppcnt_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for PPCNT SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.swid = data->swid;

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.local_port,
                                        reg_data.lp_msb,
                                        data->local_port);
    reg_data.pnat = data->pnat;
    reg_data.port_type = data->port_type;
    reg_data.grp = data->grp;
    reg_data.grp_profile = data->grp_profile;
    reg_data.prio_tc = data->prio_tc;


    err = SX_SPICE_EMAD_ACCESS_REG(PPCNT, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_ppcnt_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_sltp_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    struct ku_sltp_reg reg_data;
    const sltp_data_t        *data = (sltp_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for SLTP SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.local_port,
                                        reg_data.lp_msb,
                                        data->local_port);
    reg_data.pnat = data->pnat;
    reg_data.lane = data->lane;
    reg_data.port_type = data->port_type;


    err = SX_SPICE_EMAD_ACCESS_REG(SLTP, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_sltp_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_pddr_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    struct ku_pddr_reg reg_data;
    const pddr_data_t        *data = (pddr_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for PDDR SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.local_port,
                                        reg_data.lp_msb,
                                        data->local_port);
    reg_data.pnat = data->pnat;
    reg_data.plane_ind = data->plane_ind;
    reg_data.port_type = data->port_type;
    reg_data.page_select = data->page_select;


    err = SX_SPICE_EMAD_ACCESS_REG(PDDR, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_pddr_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_pmdr_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    struct ku_pmdr_reg reg_data;
    const pmdr_data_t        *data = (pmdr_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for PMDR SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.local_port,
                                        reg_data.lp_msb,
                                        data->local_port);
    reg_data.pnat = data->pnat;


    err = SX_SPICE_EMAD_ACCESS_REG(PMDR, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_pmdr_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_pphcr_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                      *kbuffer = NULL;
    int                        err = 0;
    ssize_t                    size = 0;
    ssize_t                    print_data_size = 0;
    struct ku_pphcr_reg reg_data;
    const pphcr_data_t        *data = (pphcr_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for PPHCR SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.local_port,
                                        reg_data.lp_msb,
                                        data->local_port);
    reg_data.pnat = data->pnat;
    reg_data.hist_type = data->hist_type;


    err = SX_SPICE_EMAD_ACCESS_REG(PPHCR, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_pphcr_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}

ssize_t sx_spice_access_reg_sllm_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    struct ku_sllm_reg reg_data;
    const sllm_data_t        *data = (sllm_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = sx_spice_buffer_alloc(GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for SLLM SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(reg_data));

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.local_port,
                                        reg_data.lp_msb,
                                        data->local_port);
    reg_data.pnat = data->pnat;
    reg_data.lane = data->lane;
    reg_data.port_type = data->port_type;


    err = SX_SPICE_EMAD_ACCESS_REG(SLLM, data->dev_data, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = sx_spice_access_reg_sllm_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    sx_spice_buffer_free(kbuffer);
    return size;
}


/* file operations */

static const struct file_operations mtcap_fops = {
    .read = sx_spice_access_reg_mtcap_read
};
static const struct file_operations mvcap_fops = {
    .read = sx_spice_access_reg_mvcap_read
};
static const struct file_operations mtmp_fops = {
    .read = sx_spice_access_reg_mtmp_read
};
static const struct file_operations mgir_fops = {
    .read = sx_spice_access_reg_mgir_read
};
static const struct file_operations msgi_fops = {
    .read = sx_spice_access_reg_msgi_read
};
static const struct file_operations mdir_fops = {
    .read = sx_spice_access_reg_mdir_read
};
static const struct file_operations mopce_fops = {
    .read = sx_spice_access_reg_mopce_read
};
static const struct file_operations spad_fops = {
    .read = sx_spice_access_reg_spad_read
};
static const struct file_operations spzr_fops = {
    .read = sx_spice_access_reg_spzr_read
};
static const struct file_operations ptys_fops = {
    .read = sx_spice_access_reg_ptys_read
};
static const struct file_operations ppcnt_fops = {
    .read = sx_spice_access_reg_ppcnt_read
};
static const struct file_operations sltp_fops = {
    .read = sx_spice_access_reg_sltp_read
};
static const struct file_operations pddr_fops = {
    .read = sx_spice_access_reg_pddr_read
};
static const struct file_operations pmdr_fops = {
    .read = sx_spice_access_reg_pmdr_read
};
static const struct file_operations pphcr_fops = {
    .read = sx_spice_access_reg_pphcr_read
};
static const struct file_operations sllm_fops = {
    .read = sx_spice_access_reg_sllm_read
};

/* sx_spice_access_reg file_create */

int sx_spice_access_reg_mtcap_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    mtcap_data_t *mtcap = NULL;

    mtcap = kzalloc(sizeof(mtcap_data_t), GFP_KERNEL);
    if (!mtcap) {
        printk(KERN_ERR "Failed to allocate mtcap for SPICE\n");
        goto out;
    }

    list_add_tail(&mtcap->mtcap_list, &__mtcap_list_head);

    mtcap->dev_data = dev_data;
    mtcap->slot_index = sx_spice_tree_index_value_get(SLOT_INDEX);


    debugfs_create_file("MTCAP", 0644, parent, (void *)mtcap, &mtcap_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_mvcap_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    mvcap_data_t *mvcap = NULL;

    mvcap = kzalloc(sizeof(mvcap_data_t), GFP_KERNEL);
    if (!mvcap) {
        printk(KERN_ERR "Failed to allocate mvcap for SPICE\n");
        goto out;
    }

    list_add_tail(&mvcap->mvcap_list, &__mvcap_list_head);

    mvcap->dev_data = dev_data;
    mvcap->slot_index = sx_spice_tree_index_value_get(SLOT_INDEX);


    debugfs_create_file("MVCAP", 0644, parent, (void *)mvcap, &mvcap_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_mtmp_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    mtmp_data_t *mtmp = NULL;

    mtmp = kzalloc(sizeof(mtmp_data_t), GFP_KERNEL);
    if (!mtmp) {
        printk(KERN_ERR "Failed to allocate mtmp for SPICE\n");
        goto out;
    }

    list_add_tail(&mtmp->mtmp_list, &__mtmp_list_head);

    mtmp->dev_data = dev_data;
    mtmp->i = sx_spice_tree_index_value_get(I);
    mtmp->ig = sx_spice_tree_index_value_get(IG);
    mtmp->asic_index = sx_spice_tree_index_value_get(ASIC_INDEX);
    mtmp->slot_index = sx_spice_tree_index_value_get(SLOT_INDEX);
    mtmp->sensor_index = sx_spice_tree_index_value_get(SENSOR_INDEX);


    debugfs_create_file("MTMP", 0644, parent, (void *)mtmp, &mtmp_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_mgir_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    mgir_data_t *mgir = NULL;

    mgir = kzalloc(sizeof(mgir_data_t), GFP_KERNEL);
    if (!mgir) {
        printk(KERN_ERR "Failed to allocate mgir for SPICE\n");
        goto out;
    }

    list_add_tail(&mgir->mgir_list, &__mgir_list_head);

    mgir->dev_data = dev_data;


    debugfs_create_file("MGIR", 0644, parent, (void *)mgir, &mgir_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_msgi_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    msgi_data_t *msgi = NULL;

    msgi = kzalloc(sizeof(msgi_data_t), GFP_KERNEL);
    if (!msgi) {
        printk(KERN_ERR "Failed to allocate msgi for SPICE\n");
        goto out;
    }

    list_add_tail(&msgi->msgi_list, &__msgi_list_head);

    msgi->dev_data = dev_data;


    debugfs_create_file("MSGI", 0644, parent, (void *)msgi, &msgi_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_mdir_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    mdir_data_t *mdir = NULL;

    mdir = kzalloc(sizeof(mdir_data_t), GFP_KERNEL);
    if (!mdir) {
        printk(KERN_ERR "Failed to allocate mdir for SPICE\n");
        goto out;
    }

    list_add_tail(&mdir->mdir_list, &__mdir_list_head);

    mdir->dev_data = dev_data;


    debugfs_create_file("MDIR", 0644, parent, (void *)mdir, &mdir_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_mopce_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    mopce_data_t *mopce = NULL;

    mopce = kzalloc(sizeof(mopce_data_t), GFP_KERNEL);
    if (!mopce) {
        printk(KERN_ERR "Failed to allocate mopce for SPICE\n");
        goto out;
    }

    list_add_tail(&mopce->mopce_list, &__mopce_list_head);

    mopce->dev_data = dev_data;


    debugfs_create_file("MOPCE", 0644, parent, (void *)mopce, &mopce_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_spad_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    spad_data_t *spad = NULL;

    spad = kzalloc(sizeof(spad_data_t), GFP_KERNEL);
    if (!spad) {
        printk(KERN_ERR "Failed to allocate spad for SPICE\n");
        goto out;
    }

    list_add_tail(&spad->spad_list, &__spad_list_head);

    spad->dev_data = dev_data;


    debugfs_create_file("SPAD", 0644, parent, (void *)spad, &spad_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_spzr_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    spzr_data_t *spzr = NULL;

    spzr = kzalloc(sizeof(spzr_data_t), GFP_KERNEL);
    if (!spzr) {
        printk(KERN_ERR "Failed to allocate spzr for SPICE\n");
        goto out;
    }

    list_add_tail(&spzr->spzr_list, &__spzr_list_head);

    spzr->dev_data = dev_data;
    spzr->swid = sx_spice_tree_index_value_get(SWID);
    spzr->router_entity = sx_spice_tree_index_value_get(ROUTER_ENTITY);


    debugfs_create_file("SPZR", 0644, parent, (void *)spzr, &spzr_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_ptys_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    ptys_data_t *ptys = NULL;

    ptys = kzalloc(sizeof(ptys_data_t), GFP_KERNEL);
    if (!ptys) {
        printk(KERN_ERR "Failed to allocate ptys for SPICE\n");
        goto out;
    }

    list_add_tail(&ptys->ptys_list, &__ptys_list_head);

    ptys->dev_data = dev_data;
    ptys->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    ptys->pnat = sx_spice_tree_index_value_get(PNAT);
    ptys->port_type = sx_spice_tree_index_value_get(PORT_TYPE);
    ptys->plane_ind = sx_spice_tree_index_value_get(PLANE_IND);
    ptys->proto_mask = sx_spice_tree_index_value_get(PROTO_MASK);


    debugfs_create_file("PTYS", 0644, parent, (void *)ptys, &ptys_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_ppcnt_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    ppcnt_data_t *ppcnt = NULL;

    ppcnt = kzalloc(sizeof(ppcnt_data_t), GFP_KERNEL);
    if (!ppcnt) {
        printk(KERN_ERR "Failed to allocate ppcnt for SPICE\n");
        goto out;
    }

    list_add_tail(&ppcnt->ppcnt_list, &__ppcnt_list_head);

    ppcnt->dev_data = dev_data;
    ppcnt->swid = sx_spice_tree_index_value_get(SWID);
    ppcnt->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    ppcnt->pnat = sx_spice_tree_index_value_get(PNAT);
    ppcnt->port_type = sx_spice_tree_index_value_get(PORT_TYPE);
    ppcnt->grp = sx_spice_tree_index_value_get(GRP);
    ppcnt->grp_profile = sx_spice_tree_index_value_get(GRP_PROFILE);
    ppcnt->prio_tc = sx_spice_tree_index_value_get(PRIO_TC);


    debugfs_create_file("PPCNT", 0644, parent, (void *)ppcnt, &ppcnt_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_sltp_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    sltp_data_t *sltp = NULL;

    sltp = kzalloc(sizeof(sltp_data_t), GFP_KERNEL);
    if (!sltp) {
        printk(KERN_ERR "Failed to allocate sltp for SPICE\n");
        goto out;
    }

    list_add_tail(&sltp->sltp_list, &__sltp_list_head);

    sltp->dev_data = dev_data;
    sltp->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    sltp->pnat = sx_spice_tree_index_value_get(PNAT);
    sltp->lane = sx_spice_tree_index_value_get(LANE);
    sltp->port_type = sx_spice_tree_index_value_get(PORT_TYPE);


    debugfs_create_file("SLTP", 0644, parent, (void *)sltp, &sltp_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_pddr_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    pddr_data_t *pddr = NULL;

    pddr = kzalloc(sizeof(pddr_data_t), GFP_KERNEL);
    if (!pddr) {
        printk(KERN_ERR "Failed to allocate pddr for SPICE\n");
        goto out;
    }

    list_add_tail(&pddr->pddr_list, &__pddr_list_head);

    pddr->dev_data = dev_data;
    pddr->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    pddr->pnat = sx_spice_tree_index_value_get(PNAT);
    pddr->plane_ind = sx_spice_tree_index_value_get(PLANE_IND);
    pddr->port_type = sx_spice_tree_index_value_get(PORT_TYPE);
    pddr->page_select = sx_spice_tree_index_value_get(PAGE_SELECT);


    debugfs_create_file("PDDR", 0644, parent, (void *)pddr, &pddr_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_pmdr_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    pmdr_data_t *pmdr = NULL;

    pmdr = kzalloc(sizeof(pmdr_data_t), GFP_KERNEL);
    if (!pmdr) {
        printk(KERN_ERR "Failed to allocate pmdr for SPICE\n");
        goto out;
    }

    list_add_tail(&pmdr->pmdr_list, &__pmdr_list_head);

    pmdr->dev_data = dev_data;
    pmdr->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    pmdr->pnat = sx_spice_tree_index_value_get(PNAT);


    debugfs_create_file("PMDR", 0644, parent, (void *)pmdr, &pmdr_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_pphcr_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    pphcr_data_t *pphcr = NULL;

    pphcr = kzalloc(sizeof(pphcr_data_t), GFP_KERNEL);
    if (!pphcr) {
        printk(KERN_ERR "Failed to allocate pphcr for SPICE\n");
        goto out;
    }

    list_add_tail(&pphcr->pphcr_list, &__pphcr_list_head);

    pphcr->dev_data = dev_data;
    pphcr->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    pphcr->pnat = sx_spice_tree_index_value_get(PNAT);
    pphcr->hist_type = sx_spice_tree_index_value_get(HIST_TYPE);


    debugfs_create_file("PPHCR", 0644, parent, (void *)pphcr, &pphcr_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_sllm_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    sllm_data_t *sllm = NULL;

    sllm = kzalloc(sizeof(sllm_data_t), GFP_KERNEL);
    if (!sllm) {
        printk(KERN_ERR "Failed to allocate sllm for SPICE\n");
        goto out;
    }

    list_add_tail(&sllm->sllm_list, &__sllm_list_head);

    sllm->dev_data = dev_data;
    sllm->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    sllm->pnat = sx_spice_tree_index_value_get(PNAT);
    sllm->lane = sx_spice_tree_index_value_get(LANE);
    sllm->port_type = sx_spice_tree_index_value_get(PORT_TYPE);


    debugfs_create_file("SLLM", 0644, parent, (void *)sllm, &sllm_fops);

    return 0;

out:
    return -ENOMEM;
}


/* sx_spice_access_reg list_free */
void sx_spice_access_reg_mtcap_list_free(void)
{
    mtcap_data_t *iter_mtcap, *tmp_mtcap;

    list_for_each_entry_safe(iter_mtcap, tmp_mtcap, &__mtcap_list_head, mtcap_list) {
        list_del(&iter_mtcap->mtcap_list);
        kfree(iter_mtcap);
    }
}

void sx_spice_access_reg_mvcap_list_free(void)
{
    mvcap_data_t *iter_mvcap, *tmp_mvcap;

    list_for_each_entry_safe(iter_mvcap, tmp_mvcap, &__mvcap_list_head, mvcap_list) {
        list_del(&iter_mvcap->mvcap_list);
        kfree(iter_mvcap);
    }
}

void sx_spice_access_reg_mtmp_list_free(void)
{
    mtmp_data_t *iter_mtmp, *tmp_mtmp;

    list_for_each_entry_safe(iter_mtmp, tmp_mtmp, &__mtmp_list_head, mtmp_list) {
        list_del(&iter_mtmp->mtmp_list);
        kfree(iter_mtmp);
    }
}

void sx_spice_access_reg_mgir_list_free(void)
{
    mgir_data_t *iter_mgir, *tmp_mgir;

    list_for_each_entry_safe(iter_mgir, tmp_mgir, &__mgir_list_head, mgir_list) {
        list_del(&iter_mgir->mgir_list);
        kfree(iter_mgir);
    }
}

void sx_spice_access_reg_msgi_list_free(void)
{
    msgi_data_t *iter_msgi, *tmp_msgi;

    list_for_each_entry_safe(iter_msgi, tmp_msgi, &__msgi_list_head, msgi_list) {
        list_del(&iter_msgi->msgi_list);
        kfree(iter_msgi);
    }
}

void sx_spice_access_reg_mdir_list_free(void)
{
    mdir_data_t *iter_mdir, *tmp_mdir;

    list_for_each_entry_safe(iter_mdir, tmp_mdir, &__mdir_list_head, mdir_list) {
        list_del(&iter_mdir->mdir_list);
        kfree(iter_mdir);
    }
}

void sx_spice_access_reg_mopce_list_free(void)
{
    mopce_data_t *iter_mopce, *tmp_mopce;

    list_for_each_entry_safe(iter_mopce, tmp_mopce, &__mopce_list_head, mopce_list) {
        list_del(&iter_mopce->mopce_list);
        kfree(iter_mopce);
    }
}

void sx_spice_access_reg_spad_list_free(void)
{
    spad_data_t *iter_spad, *tmp_spad;

    list_for_each_entry_safe(iter_spad, tmp_spad, &__spad_list_head, spad_list) {
        list_del(&iter_spad->spad_list);
        kfree(iter_spad);
    }
}

void sx_spice_access_reg_spzr_list_free(void)
{
    spzr_data_t *iter_spzr, *tmp_spzr;

    list_for_each_entry_safe(iter_spzr, tmp_spzr, &__spzr_list_head, spzr_list) {
        list_del(&iter_spzr->spzr_list);
        kfree(iter_spzr);
    }
}

void sx_spice_access_reg_ptys_list_free(void)
{
    ptys_data_t *iter_ptys, *tmp_ptys;

    list_for_each_entry_safe(iter_ptys, tmp_ptys, &__ptys_list_head, ptys_list) {
        list_del(&iter_ptys->ptys_list);
        kfree(iter_ptys);
    }
}

void sx_spice_access_reg_ppcnt_list_free(void)
{
    ppcnt_data_t *iter_ppcnt, *tmp_ppcnt;

    list_for_each_entry_safe(iter_ppcnt, tmp_ppcnt, &__ppcnt_list_head, ppcnt_list) {
        list_del(&iter_ppcnt->ppcnt_list);
        kfree(iter_ppcnt);
    }
}

void sx_spice_access_reg_sltp_list_free(void)
{
    sltp_data_t *iter_sltp, *tmp_sltp;

    list_for_each_entry_safe(iter_sltp, tmp_sltp, &__sltp_list_head, sltp_list) {
        list_del(&iter_sltp->sltp_list);
        kfree(iter_sltp);
    }
}

void sx_spice_access_reg_pddr_list_free(void)
{
    pddr_data_t *iter_pddr, *tmp_pddr;

    list_for_each_entry_safe(iter_pddr, tmp_pddr, &__pddr_list_head, pddr_list) {
        list_del(&iter_pddr->pddr_list);
        kfree(iter_pddr);
    }
}

void sx_spice_access_reg_pmdr_list_free(void)
{
    pmdr_data_t *iter_pmdr, *tmp_pmdr;

    list_for_each_entry_safe(iter_pmdr, tmp_pmdr, &__pmdr_list_head, pmdr_list) {
        list_del(&iter_pmdr->pmdr_list);
        kfree(iter_pmdr);
    }
}

void sx_spice_access_reg_pphcr_list_free(void)
{
    pphcr_data_t *iter_pphcr, *tmp_pphcr;

    list_for_each_entry_safe(iter_pphcr, tmp_pphcr, &__pphcr_list_head, pphcr_list) {
        list_del(&iter_pphcr->pphcr_list);
        kfree(iter_pphcr);
    }
}

void sx_spice_access_reg_sllm_list_free(void)
{
    sllm_data_t *iter_sllm, *tmp_sllm;

    list_for_each_entry_safe(iter_sllm, tmp_sllm, &__sllm_list_head, sllm_list) {
        list_del(&iter_sllm->sllm_list);
        kfree(iter_sllm);
    }
}

