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
#include <linux/mlx_sx/auto_registers/cmd_auto.h>

#include "sx.h"
#include "dev_db.h"

#define MCAM_GROUP2_CONTOL_MASK_END_ID (0x917F)

static ssize_t __show_asic_temp_highest(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t __show_asic_temp_input(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t __show_asic_temp_label(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static struct kobj_attribute asic_temp_highest_attr = __ATTR(highest, S_IRUGO, __show_asic_temp_highest, NULL);
static struct kobj_attribute asic_temp_input_attr = __ATTR(input, S_IRUGO, __show_asic_temp_input, NULL);
static struct kobj_attribute asic_temp_label_attr = __ATTR(label, S_IRUGO, __show_asic_temp_label, NULL);

static uint8_t __max_module_num = 0;


static int __read_frequency_support_to_db(struct sx_dev *dev)
{
    int                       err = 0;
    struct sx_priv           *priv = sx_priv(dev);
    struct ku_access_mcam_reg mcam_reg_data;
    bool                      frequency_support = false;

    memset(&mcam_reg_data, 0, sizeof(mcam_reg_data));
    mcam_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mcam_reg_data.op_tlv, MLXSW_MCAM_ID, EMAD_METHOD_QUERY);
    mcam_reg_data.mcam_reg.access_reg_group = SXD_MCAM_ACCESS_REG_GROUP_REGISTER_IDS_0X9100_E;

    err = sx_ACCESS_REG_MCAM(dev, &mcam_reg_data);
    if (err) {
        printk(KERN_NOTICE PFX "Failed to query MCAM, err=%d\n", err);
        goto out;
    }

    if (mcam_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_NOTICE PFX "Failed to query MCAM, status=%d\n", mcam_reg_data.op_tlv.status);
        goto out;
    }

    if (SX_CORE_BITMAP_GET(mcam_reg_data.mcam_reg.mng_access_reg_cap_mask,
                           SXD_MCAM_MNG_ACCESS_REG_CAP_MASK_NUM,
                           sizeof(mcam_reg_data.mcam_reg.mng_access_reg_cap_mask[0]) * 8,
                           (MLXSW_MCFS_ID & 0xff))) {
        frequency_support = true;
    } else {
        frequency_support = false;
    }

out:
    priv->independent_module_params.frequency_support = frequency_support;
    return err;
}

static int __init_max_module_num(struct sx_dev *dev)
{
    int                        err = 0;
    struct ku_access_mgpir_reg reg_data;

    reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_MGPIR_ID, EMAD_METHOD_QUERY);
    reg_data.mgpir_reg.hw_info.slot_index = 0; /*slot is set 0 by default */

    err = sx_ACCESS_REG_MGPIR(dev, &reg_data);
    if (err || reg_data.op_tlv.status) {
        printk(KERN_ERR "Fails to access register MGPIR, err: %d, status: %d.\n", err, reg_data.op_tlv.status);
        err = -EFAULT;
        goto out;
    }
    __max_module_num = reg_data.mgpir_reg.hw_info.num_of_modules;/*max_modules_per_slot seems always 0 during test */
    printk(KERN_INFO "__max_module_num:%d.\n", __max_module_num);

out:
    return err;
}

int sx_core_asic_get_dev(struct kobject *asic_kobj, struct sx_dev **dev)
{
    int          ret = 0;
    sxd_dev_id_t dev_id = 0;
    long         asic_id = 0;

    ret = kstrtol(asic_kobj->name + strlen(ASIC_SYSFS_PREFIX), 0, &asic_id);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get asic id, err=%d\n", ret);
        ret = -EINVAL;
        goto out;
    }

    if (sx_core_has_predefined_devices()) {
        dev_id = (sxd_dev_id_t)(asic_id + 1);
        *dev = sx_dev_db_get_dev_by_id(dev_id);
    } else {
        *dev = sx_dev_db_get_default_device();
    }

    if (!(*dev)) {
        printk(KERN_ERR PFX "Failed to get device\n");
        ret = -ENODEV;
        goto out;
    }

out:
    return ret;
}

int sx_core_create_default_modules_sysfs_tree(struct sx_dev             *dev,
                                              struct kobject            *parent,
                                              struct module_sysfs_node **root_arr)
{
    int     err = 0;
    uint8_t i, j, k, l;
    char    mod_name[16];

    err = __init_max_module_num(dev);
    if (err) {
        printk(KERN_ERR "module sysfs nodes handler failed to get maximum module number.\n");
        goto out;
    }

    if (!__max_module_num) {
        printk(KERN_NOTICE "module eeprom sysfs will not be created because __max_module_num is %d.\n",
               __max_module_num);
        goto out;
    }

    *root_arr = kzalloc(__max_module_num * sizeof(struct module_sysfs_node), GFP_KERNEL);
    if (!(*root_arr)) {
        printk(KERN_ERR "module sysfs nodes handler failed to allocated memory.\n");
        err = -ENOMEM;
        goto out;
    }

    /* for module eeprom sysfs */
    for (i = 0; i < __max_module_num; i++) {
        memset(mod_name, 0, sizeof(mod_name));
        sprintf(mod_name, "%s%d", MODULE_NODE_SYSFS_PREFIX, i);
        (*root_arr)[i].module = kobject_create_and_add(mod_name, parent);
        if (!((*root_arr)[i].module)) {
            err = -ENOMEM;
            goto phase1_err;
        }
    }

    for (j = 0; j < __max_module_num; j++) {
        err = sx_core_create_module_sysfs_default_eeprom_tree((*root_arr)[j].module,
                                                              &((*root_arr)[j].eeprom_tree));
        if (err) {
            printk(KERN_ERR "module sysfs nodes handler failed to create eeprom sysfs sub-tree.\n");
            err = -ENOMEM;
            goto phase2_err;
        }
    }

    for (k = 0; k < __max_module_num; k++) {
        err = sx_core_create_module_sysfs_extension_for_s3ip((*root_arr)[k].module);
        if (err) {
            printk(KERN_ERR "module sysfs nodes handler failed to create s3ip sysfs sub-tree.\n");
            err = -ENOMEM;
            goto phase3_err;
        }
    }

    for (l = 0; l < __max_module_num; l++) {
        err = sx_core_create_module_sysfs_extension_for_misc((*root_arr + l));
        if (err) {
            printk(KERN_ERR "module sysfs nodes handler failed to create s3ip sysfs sub-tree.\n");
            err = -ENOMEM;
            goto phase4_err;
        }
    }

    return err;

phase4_err:
    for (; l > 0; l--) {
        sx_core_delete_module_sysfs_extension_for_misc((*root_arr + l - 1));
    }

phase3_err:
    for (; k > 0; k--) {
        sx_core_delete_module_sysfs_extension_for_s3ip((*root_arr)[k - 1].module);
    }
phase2_err:
    for (; j > 0; j--) {
        sx_core_delete_module_sysfs_default_eeprom_tree(&((*root_arr)[j - 1].eeprom_tree));
    }
phase1_err:
    for (; i > 0; i--) {
        kobject_put((*root_arr)[i - 1].module);
    }
    kfree(*root_arr);
out:
    return err;
}

void sx_core_delete_default_modules_sysfs_tree(struct module_sysfs_node **root_arr)
{
    uint8_t i;

    if (!__max_module_num) {
        return;
    }

    for (i = 0; i < __max_module_num; i++) {
        sx_core_delete_module_sysfs_default_eeprom_tree(&((*root_arr)[i].eeprom_tree));
        sx_core_delete_module_sysfs_extension_for_s3ip((*root_arr)[i].module);
        sx_core_delete_module_sysfs_extension_for_misc((*root_arr + i));
        kobject_put((*root_arr)[i].module);
    }
    kfree(*root_arr);
    *root_arr = NULL;
}

int sx_core_create_independent_modules_sysfs_tree(struct sx_dev *dev, struct module_sysfs_node **root_arr)
{
    int     err = 0;
    uint8_t k;

    for (k = 0; k < __max_module_num; k++) {
        err = sx_core_create_module_sysfs_extension_for_indmod((*root_arr)[k].module);
        if (err) {
            printk(KERN_ERR "module sysfs nodes handler failed to create independent module sysfs sub-tree.\n");
            err = -ENOMEM;
            goto out;
        }
    }

    return err;


out:
    for (; k > 0; k--) {
        sx_core_delete_module_sysfs_extension_for_indmod((*root_arr)[k - 1].module);
    }

    return err;
}

void sx_core_delete_independent_modules_sysfs_tree(struct module_sysfs_node **root_arr)
{
    uint8_t i;

    for (i = 0; i < __max_module_num; i++) {
        sx_core_delete_module_sysfs_extension_for_indmod((*root_arr)[i].module);
    }
}

int sx_sysfs_asic_independent_init(struct sx_dev *dev)
{
    int             err = 0;
    struct sx_priv *priv = sx_priv(dev);
    uint8_t         i = 0, j = 0;

    priv->independent_module_params.frequency_support = false;
    err = sx_core_create_independent_modules_sysfs_tree(dev,
                                                        &(priv->module_sysfs_arr));
    if (err) {
        goto out;
    }

    for (i = 0; i < MAX_SLOT_NUM; i++) {
        for (j = 0; j < MAX_MODULE_NUM; j++) {
            priv->module_data[i][j].independent_params.hw_present = SX_MODULE_HW_PRESENT_INVALID;
            priv->module_data[i][j].independent_params.interrupt = SX_MODULE_INTERRUPT_INVALID;
            priv->module_data[i][j].independent_params.power_good = SX_MODULE_POWER_GOOD_INVALID;
        }
    }

    priv->independent_module_params.is_independent = true;

    err = __read_frequency_support_to_db(dev);
    if (err) {
        printk(KERN_NOTICE "Failed to read frequency support, err: %d.\n", err);
        err = 0;
    }

out:
    return err;
}

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

    err = sx_core_create_default_modules_sysfs_tree(dev,
                                                    priv->kobj[SX_KOBJECT_ASIC],
                                                    &(priv->module_sysfs_arr));
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

    if (priv->independent_module_params.is_independent) {
        sx_core_delete_independent_modules_sysfs_tree(&(priv->module_sysfs_arr));
    }
    sx_core_delete_default_modules_sysfs_tree(&(priv->module_sysfs_arr));
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
