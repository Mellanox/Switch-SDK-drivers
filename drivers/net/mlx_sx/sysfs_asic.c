/*
 * Copyright (C) 2010-2023 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of NVIDIA CORPORATION & AFFILIATES, Ltd.
 * (the "Company") and all right, title, and interest in and to the software product,
 * including all associated intellectual property rights, are and shall
 * remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 *
 */

#include <linux/module.h>
#include <linux/string.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/driver.h>

#include "sx.h"
#include "dev_db.h"

static ssize_t __show_asic_temp_highest(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t __show_asic_temp_input(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t __show_asic_temp_label(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static struct kobj_attribute asic_temp_highest_attr = __ATTR(highest, S_IRUGO, __show_asic_temp_highest, NULL);
static struct kobj_attribute asic_temp_input_attr = __ATTR(input, S_IRUGO, __show_asic_temp_input, NULL);
static struct kobj_attribute asic_temp_label_attr = __ATTR(label, S_IRUGO, __show_asic_temp_label, NULL);

int sx_sysfs_asic_create(struct sx_dev *dev)
{
    int             err = 0;
    struct sx_priv *priv = sx_priv(dev);
    char            object_name[ASIC_NAME_LEN_MAX + 1];
    uint8_t         asic_id = 0;

    memset(object_name, 0, sizeof(object_name));

    if (sx_core_has_predefined_devices()) {
        asic_id = dev->device_id - 1;
    } else {
        asic_id = 0;
    }

    sprintf(object_name, "%s%d", ASIC_SYSFS_PREFIX, asic_id);

    priv->kobj[SX_KOBJECT_ASIC] = kobject_create_and_add(object_name, &(THIS_MODULE->mkobj.kobj));
    if (priv->kobj[SX_KOBJECT_ASIC] == NULL) {
        printk(KERN_ERR PFX "Failed to create asic sysfs\n");
        err = -ENOMEM;
        goto out;
    }
    priv->kobj[SX_KOBJECT_ASIC_TEMP] = kobject_create_and_add("temperature", priv->kobj[SX_KOBJECT_ASIC]);
    if (priv->kobj[SX_KOBJECT_ASIC_TEMP] == NULL) {
        printk(KERN_ERR PFX "Failed to create asic temperature sysfs\n");
        err = -ENOMEM;
        goto temperature_kobj_failed;
    }

    err = sysfs_create_file(priv->kobj[SX_KOBJECT_ASIC_TEMP], &(asic_temp_highest_attr.attr));
    if (err) {
        printk(KERN_ERR PFX "Failed to create asic temperature sysfs highest attribute\n");
        goto highest_failed;
    }
    err = sysfs_create_file(priv->kobj[SX_KOBJECT_ASIC_TEMP], &(asic_temp_input_attr.attr));
    if (err) {
        printk(KERN_ERR PFX "Failed to create asic temperature sysfs input attribute\n");
        goto input_failed;
    }
    err = sysfs_create_file(priv->kobj[SX_KOBJECT_ASIC_TEMP], &(asic_temp_label_attr.attr));
    if (err) {
        printk(KERN_ERR PFX "Failed to create asic temperature sysfs label attribute\n");
        goto label_failed;
    }

    err = sx_core_create_default_modules_sysfs_eeprom_tree(dev,
                                                           priv->kobj[SX_KOBJECT_ASIC],
                                                           &(priv->module_eeprom_arr));
    if (err) {
        printk(KERN_ERR "module sysfs nodes handler failed to create eeprom sysfs sub-tree.\n");
        goto eeprom_tree_failed;
    }

    return 0;

eeprom_tree_failed:
    sysfs_remove_file(priv->kobj[SX_KOBJECT_ASIC_TEMP], &(asic_temp_label_attr.attr));

label_failed:
    sysfs_remove_file(priv->kobj[SX_KOBJECT_ASIC_TEMP], &(asic_temp_input_attr.attr));

input_failed:
    sysfs_remove_file(priv->kobj[SX_KOBJECT_ASIC_TEMP], &(asic_temp_highest_attr.attr));

highest_failed:
    kobject_put(priv->kobj[SX_KOBJECT_ASIC_TEMP]);
    priv->kobj[SX_KOBJECT_ASIC_TEMP] = NULL;

temperature_kobj_failed:
    kobject_put(priv->kobj[SX_KOBJECT_ASIC]);
    priv->kobj[SX_KOBJECT_ASIC] = NULL;

out:
    return err;
}

void sx_sysfs_asic_remove(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);

    sx_core_delete_default_modules_sysfs_eeprom_tree(&(priv->module_eeprom_arr));
    kobject_put(priv->kobj[SX_KOBJECT_ASIC_TEMP]);
    kobject_put(priv->kobj[SX_KOBJECT_ASIC]);
}

static int __init_mtmp(struct sx_dev *dev, uint8_t slot_id, uint16_t sensor_index)
{
    int                       err = 0;
    struct ku_access_mtmp_reg mtmp_reg_data;

    memset(&mtmp_reg_data, 0, sizeof(mtmp_reg_data));
    sx_cmd_set_op_tlv(&mtmp_reg_data.op_tlv, MLXSW_MTMP_ID, EMAD_METHOD_QUERY);
    mtmp_reg_data.dev_id = dev->device_id;
    mtmp_reg_data.mtmp_reg.sensor_index = sensor_index;
    mtmp_reg_data.mtmp_reg.slot_index = slot_id;

    err = sx_ACCESS_REG_MTMP(dev, &mtmp_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access MTMP, err=%d\n", err);
        goto out;
    }

    if (mtmp_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access MTMP, status=%d\n", mtmp_reg_data.op_tlv.status);
        goto out;
    }

    if (mtmp_reg_data.mtmp_reg.mte == 1) {
        goto out;
    }

    sx_cmd_set_op_tlv(&mtmp_reg_data.op_tlv, MLXSW_MTMP_ID, EMAD_METHOD_WRITE);
    mtmp_reg_data.mtmp_reg.mte = 1;
    mtmp_reg_data.mtmp_reg.mtr = 1;

    err = sx_ACCESS_REG_MTMP(dev, &mtmp_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access MTMP, err=%d\n", err);
        goto out;
    }

    if (mtmp_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access MTMP, status=%d\n", mtmp_reg_data.op_tlv.status);
        goto out;
    }

out:
    return err;
}

int sx_sysfs_asic_init_tempeature(struct sx_dev *dev)
{
    int                        err = 0;
    uint32_t                   sensor_idx = 0;
    struct ku_access_mtecr_reg mtecr_reg_data;

    memset(&mtecr_reg_data, 0, sizeof(mtecr_reg_data));
    sx_cmd_set_op_tlv(&mtecr_reg_data.op_tlv, MLXSW_MTECR_ID, EMAD_METHOD_QUERY);
    mtecr_reg_data.dev_id = dev->device_id;
    mtecr_reg_data.mtecr_reg.slot_index = 0;

    err = sx_ACCESS_REG_MTECR(dev, &mtecr_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access MTECR, err=%d\n", err);
        goto out;
    }

    if (mtecr_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access MTECR, status=%d\n", mtecr_reg_data.op_tlv.status);
        goto out;
    }

    err = __init_mtmp(dev, 0, sensor_idx);
    if (err) {
        printk(KERN_ERR PFX "Failed to init MTMP, err=%d\n", err);
        goto out;
    }

out:
    return err;
}

static int __sx_core_get_asic_temperature(struct kobject *kobj, struct sx_temperature_params *params)
{
    int                       ret = 0;
    long                      asic_id = 0;
    sxd_dev_id_t              dev_id = 0;
    struct sx_dev            *dev = NULL;
    struct kobject           *kobj_asic = kobj->parent;
    uint16_t                  temperature = 0;
    struct ku_access_mtbr_reg mtbr_reg_data;

    if (!kobj_asic) {
        printk(KERN_ERR PFX "asic sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = kstrtol(kobj_asic->name + strlen(ASIC_SYSFS_PREFIX), 0, &asic_id);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get asic id, err=%d\n", ret);
        goto out;
    }

    if (sx_core_has_predefined_devices()) {
        dev_id = (sxd_dev_id_t)(asic_id + 1);
        dev = sx_dev_db_get_dev_by_id(dev_id);
    } else {
        dev = sx_dev_db_get_default_device();
    }

    if (!dev) {
        printk(KERN_ERR PFX "Failed to get device\n");
        ret = -ENODEV;
        goto out;
    }

    memset(params, 0, sizeof(struct sx_temperature_params));

    memset(&mtbr_reg_data, 0, sizeof(mtbr_reg_data));
    mtbr_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mtbr_reg_data.op_tlv, MTBR_REG_ID, EMAD_METHOD_QUERY);

    mtbr_reg_data.mtbr_reg.base_sensor_index = 0;
    mtbr_reg_data.mtbr_reg.slot_index = 0;
    mtbr_reg_data.mtbr_reg.num_rec = 1;

    ret = sx_ACCESS_REG_MTBR(dev, &mtbr_reg_data);
    if (ret) {
        printk(KERN_ERR PFX "Failed to access MTBR, err=%d\n", ret);
        goto out;
    }
    if (mtbr_reg_data.op_tlv.status) {
        ret = -EINVAL;
        printk(KERN_ERR PFX "Failed to access MTBR, status=%d\n", mtbr_reg_data.op_tlv.status);
        goto out;
    }

    temperature = mtbr_reg_data.mtbr_reg.temperature_record[0].temperature;
    if ((temperature == 0) || (temperature == SXD_MTBR_NO_CABLE) || (temperature == SXD_MTBR_NO_READ) ||
        (temperature == SXD_MTBR_INVALID_INDEX) || (temperature == SXD_MTBR_READ_FAILED) ||
        (temperature == SXD_MTBR_NO_SENSOR)) {
        ret = -ENODEV;
        printk(KERN_ERR PFX "Temperature sensing is not supported on asic, status=0x%x\n", temperature);
        goto out;
    }

    params->highest = mtbr_reg_data.mtbr_reg.temperature_record[0].max_temperature;
    params->input = mtbr_reg_data.mtbr_reg.temperature_record[0].temperature;

    sprintf(params->label, "Asic%ld", asic_id);

out:
    return ret;
}

static ssize_t __show_asic_temp_highest(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                          ret = 0;
    struct sx_temperature_params params;
    int                          len = 0;


    ret = __sx_core_get_asic_temperature(kobj, &params);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get module temperature information\n");
        return ret;
    }

    len = sprintf(buf, "%llu\n", params.highest);

    return len;
}

static ssize_t __show_asic_temp_input(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                          ret = 0;
    struct sx_temperature_params params;
    int                          len = 0;

    ret = __sx_core_get_asic_temperature(kobj, &params);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get module temperature information\n");
        return ret;
    }

    len = sprintf(buf, "%llu\n", params.input);

    return len;
}

static ssize_t __show_asic_temp_label(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                          ret = 0;
    struct sx_temperature_params params;
    int                          len = 0;


    ret = __sx_core_get_asic_temperature(kobj, &params);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get module temperature information\n");
        return ret;
    }

    len = sprintf(buf, "%s\n", params.label);

    return len;
}
