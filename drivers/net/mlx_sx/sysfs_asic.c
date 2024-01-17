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
static uint8_t __max_module_num = 0;

/*********temp**********/
static ssize_t __show_asic_temp_highest(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t __show_asic_temp_input(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t __show_asic_temp_label(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static struct kobj_attribute asic_temp_highest_attr = __ATTR(highest, S_IRUGO, __show_asic_temp_highest, NULL);
static struct kobj_attribute asic_temp_input_attr = __ATTR(input, S_IRUGO, __show_asic_temp_input, NULL);
static struct kobj_attribute asic_temp_label_attr = __ATTR(label, S_IRUGO, __show_asic_temp_label, NULL);


/********performance counters********/
#define PERF_CNTR_MAX_HW_UNIT_ID_SPEC1 34
#define PERF_CNTR_MAX_HW_UNIT_ID_SPEC2 57
#define PERF_CNTR_MAX_HW_UNIT_ID_SPEC3 62
#define PERF_CNTR_MAX_HW_UNIT_ID_SPEC4 133
#define MAX_COUNTER_FILE_ROW_LEN       12 /*max hw_unit_id is 0x84, max counter is (for SPC4) 0x1f4, + 3 char for ":,\n,\0" */
#define SYSFS_MAX_BUFF_LEN             PAGE_SIZE /*buf size is sysfs is PAGE_SIZE */

static size_t perf_cntr_hw_unit_max_cntr_arr_spc1[PERF_CNTR_MAX_HW_UNIT_ID_SPEC1] =
{8, 8, 8, 0, 6, 4, 4, 8, 8, 8, 8, 4, 4, 8, 4, 8, 8, 4, 4, 8, 8, 6, 8, 8, 8, 8, 8, 4, 4, 8, 8, 4, 4, 6};

static size_t perf_cntr_hw_unit_max_cntr_arr_spc2[PERF_CNTR_MAX_HW_UNIT_ID_SPEC2] =
{4, 4, 4, 4, 16, 16, 8, 16, 16, 16, 4, 8, 8, 4, 4, 8, 4, 8, 8, 6, 8, 4, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8,
 8, 8, 8, 16, 8, 4, 4, 4, 4, 16, 16, 8, 16, 8, 16, 8, 4, 8, 4, 4, 8, 8, 16, 8, 6};

static size_t perf_cntr_hw_unit_max_cntr_arr_spc3[PERF_CNTR_MAX_HW_UNIT_ID_SPEC3] =
{4, 4, 4, 4, 16, 16, 8, 16, 16, 16, 4, 8, 8, 4, 4, 8, 4, 8, 8, 6, 8, 4, 8, 8, 8, 16, 16, 16, 16, 8, 8,
 8, 8, 8, 8, 16, 8, 4, 4, 4, 4, 16, 16, 8, 16, 8, 16, 8, 4, 8, 4, 4, 8, 8, 16, 8, 6, 8, 16, 8, 8, 16};

static size_t perf_cntr_hw_unit_max_cntr_arr_spc4[PERF_CNTR_MAX_HW_UNIT_ID_SPEC4] =
{4, 16, 0, 8, 8, 6, 0, 0, 0, 0, 16, 16, 16, 16, 16, 4, 16, 16, 16, 8, 16, 16, 16, 16, 0, 0, 0, 0, 16, 16,
 16, 8, 16, 4, 16, 8, 16, 16, 4, 16, 8, 16, 8, 16, 16, 16, 16, 8, 8, 0, 0, 0, 16, 16, 2, 8, 4, 8, 8, 16,
 4, 4, 16, 4, 8, 8, 8, 8, 16, 16, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 0, 4, 4, 0, 4,
 4, 16, 4, 4, 16, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 2, 2, 2, 2, 4, 16, 2, 2, 4, 16, 4, 16, 8, 4, 4, 4,
 4, 4, 4, 4, 20, 2};

static size_t perf_cntr_max_cntr_id_in_hw_unit_arr_spc1[PERF_CNTR_MAX_HW_UNIT_ID_SPEC1] =
{203, 86, 1204, 0, 85, 153, 136, 268, 315, 66, 21, 8, 10, 11, 5, 1029, 140, 153, 136, 268, 315,
 186, 135, 91, 91, 22, 260, 74, 11, 177, 32, 1589, 108, 85};

static size_t perf_cntr_max_cntr_id_in_hw_unit_arr_spc2[PERF_CNTR_MAX_HW_UNIT_ID_SPEC2] =
{153, 136, 128, 79, 202, 806, 1346, 134, 173, 491, 8, 69, 47, 14, 15, 12, 19, 159, 289, 16, 141,
 13, 49, 177, 210, 491, 1058, 775, 54, 15, 30, 312, 186, 43, 43, 1269, 2, 153, 136, 128, 79, 202,
 806, 1346, 134, 483, 222, 17, 72, 4439, 225, 225, 710, 399, 173, 1857, 16};

static size_t perf_cntr_max_cntr_id_in_hw_unit_arr_spc3[PERF_CNTR_MAX_HW_UNIT_ID_SPEC3] =
{153, 136, 128, 79, 156, 418, 1396, 130, 177, 519, 8, 69, 47, 14, 15, 12, 19, 238, 311, 16, 145,
 21, 49, 305, 338, 519, 1124, 843, 54, 15, 30, 410, 236, 51, 51, 1376, 9, 153, 136, 128, 79, 156,
 418, 1396, 130, 291, 222, 17, 136, 4926, 243, 243, 218, 437, 177, 971, 16, 93, 167, 1786, 1574, 89};

static size_t perf_cntr_max_cntr_id_in_hw_unit_arr_spc4[PERF_CNTR_MAX_HW_UNIT_ID_SPEC4] =
{6, 882, 0, 347, 317, 6, 0, 0, 0, 0, 588, 335, 201, 96, 69, 244, 207, 166, 55, 99, 539, 539, 1465,
 787, 0, 0, 0, 0, 1129, 2745, 655, 15, 1869, 6, 196, 1702, 502, 1869, 6, 196, 1702, 502, 302, 311,
 338, 72, 549, 5895, 3645, 0, 0, 0, 155, 20, 10, 237, 6, 411, 865, 239, 6, 264, 155, 123, 471, 115,
 241, 865, 239, 552, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 0, 6, 6, 6,
 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 777, 6, 774, 3072, 3870, 48, 6, 768, 774, 777, 271, 616,
 6, 897, 625, 6, 6, 6, 264, 264, 264, 264, 20, 10};


static ssize_t __show_asic_perf_cntr_counters(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t __store_asic_perf_cntr_counters(struct kobject        *kobj,
                                               struct kobj_attribute *attr,
                                               const char            *buf,
                                               size_t                 len);
static ssize_t __show_asic_perf_cntr_interval(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t __store_asic_perf_cntr_interval(struct kobject        *kobj,
                                               struct kobj_attribute *attr,
                                               const char            *buf,
                                               size_t                 len);
static struct kobj_attribute asic_perf_cntr_counters_attr =
    __ATTR(counters, (S_IRUGO | S_IWUSR), __show_asic_perf_cntr_counters, __store_asic_perf_cntr_counters);
static struct kobj_attribute asic_perf_cntr_interval_attr =
    __ATTR(interval, (S_IRUGO | S_IWUSR), __show_asic_perf_cntr_interval, __store_asic_perf_cntr_interval);


char * __sx_sysfs_get_str(char *buffer, char **str, const char* delimiters);
char * __sx_sysfs_get_id_str(char *buffer, char **str);
char * __sx_sysfs_get_hw_unit_counter_pair_str(char *buffer, char **str);
static int __perf_cntr_add_pair_to_counters_db(struct kobject  *kobj,
                                               int              hw_unit_id,
                                               int              counter_id,
                                               sxd_chip_types_t chip_type);
static int __perf_cntr_validate_hw_unit_id(sxd_chip_types_t chip_type, size_t hw_unit_id);
static int __perf_cntr_validate_counter_id(sxd_chip_types_t chip_type, size_t hw_unit_id, size_t counter_id);
static int __perf_cntr_validate_hw_unit_and_cntr_id(struct kobject  *kobj,
                                                    size_t           hw_unit_id,
                                                    size_t           counter_id,
                                                    sxd_chip_types_t chip_type);
static int __perf_cntr_add_new_mopct_node_to_list(struct sx_perf_cntr *perf_cntr_p,
                                                  int                  hw_unit_id,
                                                  int                  counter_id);
static struct mopct_node* __perf_cntr_allocate_mopct_node(int hw_unit_id,
                                                          int counter_id,
                                                          int group_id);


/*********************************************************************/


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
    *root_arr = NULL;
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
    /* ASIC performance counters*/
    priv->kobj[SX_KOBJECT_ASIC_PERF_CNTR] = kobject_create_and_add("performance", priv->kobj[SX_KOBJECT_ASIC]);
    if (priv->kobj[SX_KOBJECT_ASIC_PERF_CNTR] == NULL) {
        printk(KERN_ERR PFX "Failed to create asic performance sysfs\n");
        err = -ENOMEM;
        goto perf_cntr_kobj_failed;
    }

    err = sysfs_create_file(priv->kobj[SX_KOBJECT_ASIC_PERF_CNTR], &(asic_perf_cntr_counters_attr.attr));
    if (err) {
        printk(KERN_ERR PFX "Failed to create asic performance counters sysfs counters attribute\n");
        goto counters_failed;
    }
    err = sysfs_create_file(priv->kobj[SX_KOBJECT_ASIC_PERF_CNTR], &(asic_perf_cntr_interval_attr.attr));
    if (err) {
        printk(KERN_ERR PFX "Failed to create asic performance counters sysfs interval attribute\n");
        goto interval_failed;
    }


    return 0;

interval_failed:
    sysfs_remove_file(priv->kobj[SX_KOBJECT_ASIC_PERF_CNTR], &(asic_perf_cntr_interval_attr.attr));

counters_failed:
    sysfs_remove_file(priv->kobj[SX_KOBJECT_ASIC_PERF_CNTR], &(asic_perf_cntr_counters_attr.attr));

perf_cntr_kobj_failed:
    kobject_put(priv->kobj[SX_KOBJECT_ASIC]);
    sysfs_remove_file(priv->kobj[SX_KOBJECT_ASIC_TEMP], &(asic_temp_label_attr.attr));
    priv->kobj[SX_KOBJECT_ASIC] = NULL;

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

    if (priv->module_sysfs_arr) {
        if (priv->independent_module_params.module_support_type == SXD_MODULE_MASTER_MODE_SW_CONTROL_E) {
            sx_core_delete_independent_modules_sysfs_tree(&(priv->module_sysfs_arr));
        }

        sx_core_delete_default_modules_sysfs_tree(&(priv->module_sysfs_arr));
    }

    if (priv->kobj[SX_KOBJECT_ASIC_PERF_CNTR]) {
        kobject_put(priv->kobj[SX_KOBJECT_ASIC_PERF_CNTR]);
    }

    if (priv->kobj[SX_KOBJECT_ASIC_TEMP]) {
        kobject_put(priv->kobj[SX_KOBJECT_ASIC_TEMP]);
    }

    if (priv->kobj[SX_KOBJECT_ASIC]) {
        kobject_put(priv->kobj[SX_KOBJECT_ASIC]);
    }
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
        pr_debug(PFX "Temperature sensing is not supported on asic, status=0x%x\n", temperature);
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
        if (ret != -ENODEV) {
            printk(KERN_ERR PFX "Failed to get ASIC temperature highest information\n");
        }
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
        if (ret != -ENODEV) {
            printk(KERN_ERR PFX "Failed to get ASIC temperature input information\n");
        }
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
        if (ret != -ENODEV) {
            printk(KERN_ERR PFX "Failed to get ASIC temperature label information\n");
        }
        return ret;
    }

    len = sprintf(buf, "%s\n", params.label);

    return len;
}


/*performance counters*/
static int __sx_core_get_asic_perf_cntr_interval(struct kobject *kobj, int *interval)
{
    int             ret = 0;
    struct sx_dev  *dev = NULL;
    struct kobject *kobj_asic = kobj->parent;
    struct sx_priv *priv = NULL;

    ret = sx_core_asic_get_dev(kobj_asic, &dev);
    if (ret) {
        printk(KERN_ERR PFX "sysfs entry performance counters got invalid value\n");
        goto out;
    }

    priv = sx_priv(dev);

    *interval = priv->perf_cntr.interval;

out:
    return ret;
}


static int __sx_core_set_asic_perf_cntr_interval(struct kobject *kobj, int interval)
{
    int                         ret = 0;
    struct sx_dev              *dev = NULL;
    struct kobject             *kobj_asic = kobj->parent;
    struct sx_priv             *priv = NULL;
    struct ku_access_mopgcr_reg mopgcr_reg_data;


    ret = sx_core_asic_get_dev(kobj_asic, &dev);
    if (ret) {
        printk(KERN_ERR PFX "sysfs entry performance counters got invalid value\n");
        goto out;
    }

    priv = sx_priv(dev);

    priv->perf_cntr.interval = interval;

    memset(&mopgcr_reg_data, 0, sizeof(mopgcr_reg_data));
    mopgcr_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mopgcr_reg_data.op_tlv, MLXSW_MOPGCR_ID, EMAD_METHOD_WRITE);

    mopgcr_reg_data.mopgcr_reg.perf_cnt_interval = interval;

    ret = sx_ACCESS_REG_MOPGCR(dev, &mopgcr_reg_data);
    if (ret) {
        printk(KERN_ERR PFX "Failed to access MOPGCR, err=%d\n", ret);
        goto out;
    }
    if (mopgcr_reg_data.op_tlv.status) {
        ret = -EINVAL;
        printk(KERN_ERR PFX "Failed to access ,MOPGCR, status=%d\n", mopgcr_reg_data.op_tlv.status);
        goto out;
    }

out:
    return ret;
}

static int __perf_cntr_validate_counter_id(sxd_chip_types_t chip_type, size_t hw_unit_id, size_t counter_id)
{
    int ret = 0;

    switch (chip_type) {
    case SXD_CHIP_TYPE_SPECTRUM:
    case SXD_CHIP_TYPE_SPECTRUM_A1:
        if (counter_id > perf_cntr_max_cntr_id_in_hw_unit_arr_spc1[hw_unit_id]) {
            printk(KERN_ERR PFX "counter_id %lu for hw_unit_id %lu is invalid. The maximum for SPC1 is %lu\n",
                   counter_id, hw_unit_id, perf_cntr_max_cntr_id_in_hw_unit_arr_spc1[hw_unit_id]);
            ret = -EINVAL;
            goto out;
        }
        break;

    case SXD_CHIP_TYPE_SPECTRUM2:
        if (counter_id > perf_cntr_max_cntr_id_in_hw_unit_arr_spc2[hw_unit_id]) {
            printk(KERN_ERR PFX "counter_id %lu for hw_unit_id %lu is invalid. The maximum for SPC2 is %lu\n",
                   counter_id, hw_unit_id, perf_cntr_max_cntr_id_in_hw_unit_arr_spc2[hw_unit_id]);
            ret = -EINVAL;
            goto out;
        }
        break;

    case SXD_CHIP_TYPE_SPECTRUM3:
        if (counter_id > perf_cntr_max_cntr_id_in_hw_unit_arr_spc3[hw_unit_id]) {
            printk(KERN_ERR PFX "counter_id %lu for hw_unit_id %lu is invalid. The maximum for SPC3 is %lu\n",
                   counter_id, hw_unit_id, perf_cntr_max_cntr_id_in_hw_unit_arr_spc3[hw_unit_id]);
            ret = -EINVAL;
            goto out;
        }
        break;

    case SXD_CHIP_TYPE_SPECTRUM4:
        if (counter_id > perf_cntr_max_cntr_id_in_hw_unit_arr_spc4[hw_unit_id]) {
            printk(KERN_ERR PFX "counter_id %lu for hw_unit_id %lu is invalid. The maximum for SPC4 is %lu\n",
                   counter_id, hw_unit_id, perf_cntr_max_cntr_id_in_hw_unit_arr_spc4[hw_unit_id]);
            ret = -EINVAL;
            goto out;
        }
        break;

    default:
        printk(KERN_ERR PFX "chip type %u is unknown \n", chip_type);
        ret = -EINVAL;
        goto out;
    }
out:
    return ret;
}


static int __perf_cntr_validate_hw_unit_id(sxd_chip_types_t chip_type, size_t hw_unit_id)
{
    int ret = 0;


    switch (chip_type) {
    case SXD_CHIP_TYPE_SPECTRUM:
    case SXD_CHIP_TYPE_SPECTRUM_A1:
        if (hw_unit_id >= PERF_CNTR_MAX_HW_UNIT_ID_SPEC1) {
            printk(KERN_ERR PFX "hw_unit_id %lu value is invalid. The maximum for SPC1 is %u\n",
                   hw_unit_id, (PERF_CNTR_MAX_HW_UNIT_ID_SPEC1 - 1));
            ret = -EINVAL;
            goto out;
        }
        break;

    case SXD_CHIP_TYPE_SPECTRUM2:
        if (hw_unit_id >= PERF_CNTR_MAX_HW_UNIT_ID_SPEC2) {
            printk(KERN_ERR PFX "hw_unit_id %lu value is invalid. The maximum for SPC2 is %u\n",
                   hw_unit_id, (PERF_CNTR_MAX_HW_UNIT_ID_SPEC2 - 1));
            ret = -EINVAL;
            goto out;
        }
        break;

    case SXD_CHIP_TYPE_SPECTRUM3:
        if (hw_unit_id >= PERF_CNTR_MAX_HW_UNIT_ID_SPEC3) {
            printk(KERN_ERR PFX "hw_unit_id %lu value is invalid. The maximum for SPC3 is %u\n",
                   hw_unit_id, (PERF_CNTR_MAX_HW_UNIT_ID_SPEC3 - 1));
            ret = -EINVAL;
            goto out;
        }
        break;

    case SXD_CHIP_TYPE_SPECTRUM4:
        if (hw_unit_id >= PERF_CNTR_MAX_HW_UNIT_ID_SPEC4) {
            printk(KERN_ERR PFX "hw_unit_id %lu value is invalid. The maximum for SPC4 is %u\n",
                   hw_unit_id, (PERF_CNTR_MAX_HW_UNIT_ID_SPEC4 - 1));
            ret = -EINVAL;
            goto out;
        }
        break;

    default:
        printk(KERN_ERR PFX "chip type %u is unknown \n", chip_type);
        ret = -EINVAL;
        goto out;
    }
out:
    return ret;
}


static int __perf_cntr_validate_hw_unit_and_cntr_id(struct kobject  *kobj,
                                                    size_t           hw_unit_id,
                                                    size_t           counter_id,
                                                    sxd_chip_types_t chip_type)
{
    int ret = 0;


    ret = __perf_cntr_validate_hw_unit_id(chip_type, hw_unit_id);
    if (ret) {
        printk(KERN_ERR PFX "Invalid hw_unit_id\n");
        goto out;
    }

    ret = __perf_cntr_validate_counter_id(chip_type, hw_unit_id, counter_id);
    if (ret) {
        printk(KERN_ERR PFX "Invalid counter_id\n");
        goto out;
    }
out:
    return ret;
}

static int __perf_cntr_get_hw_unit_max_counters(sxd_chip_types_t chip_type, int hw_unit_id)
{
    int ret = 0;

    switch (chip_type) {
    case SXD_CHIP_TYPE_SPECTRUM:
    case SXD_CHIP_TYPE_SPECTRUM_A1:
        return perf_cntr_hw_unit_max_cntr_arr_spc1[hw_unit_id];

    case SXD_CHIP_TYPE_SPECTRUM2:
        return perf_cntr_hw_unit_max_cntr_arr_spc2[hw_unit_id];

    case SXD_CHIP_TYPE_SPECTRUM3:
        return perf_cntr_hw_unit_max_cntr_arr_spc3[hw_unit_id];

    case SXD_CHIP_TYPE_SPECTRUM4:
        return perf_cntr_hw_unit_max_cntr_arr_spc4[hw_unit_id];

    default:
        printk(KERN_ERR PFX "chip type %u is unknown \n", chip_type);
        ret = -EINVAL;
        goto out;
    }
out:
    return ret;
}


static struct mopct_node* __perf_cntr_allocate_mopct_node(int hw_unit_id, int counter_id, int group_id)
{
    struct mopct_node *mopct_node = NULL;

    mopct_node = (struct mopct_node*)kmalloc(sizeof(struct  mopct_node), GFP_KERNEL);

    if (mopct_node) {
        INIT_LIST_HEAD(&mopct_node->hw_unit_list);
        INIT_LIST_HEAD(&mopct_node->group_id_list);

        mopct_node->mopct.cnt_grp_id = group_id;
        mopct_node->mopct.enabled_counters[0] = counter_id;
        mopct_node->mopct.force = 0;
        mopct_node->mopct.hw_unit_id = hw_unit_id;
        mopct_node->mopct.num_active_counters = 1;
    }

    return mopct_node;
}


static int __perf_cntr_add_new_mopct_node_to_list(struct sx_perf_cntr *perf_cntr_p, int hw_unit_id, int counter_id)
{
    struct mopct_node *new_mopct_node = NULL;
    int                group_id = 0;
    int                ret = 0;

    if (perf_cntr_p == NULL) {
        ret = -EINVAL;
        goto out;
    }
    /*Need to add new node to the hw_unit_id and the group_id lists */
    group_id = perf_cntr_p->hw_units_arr[hw_unit_id].mopct_in_hw_unit;

    new_mopct_node = __perf_cntr_allocate_mopct_node(hw_unit_id,
                                                     counter_id,
                                                     group_id);
    if (new_mopct_node == NULL) {
        printk(KERN_ERR PFX "Cannot add new performance counters entry.\n");
        ret = -ENOMEM;
        goto out;
    }

    list_add_tail(&new_mopct_node->hw_unit_list, &perf_cntr_p->hw_units_arr[hw_unit_id].mopct_list);
    list_add(&new_mopct_node->group_id_list, &perf_cntr_p->counter_group_arr[group_id].mopct_list);

    perf_cntr_p->counter_group_arr[group_id].mopct_in_group++;
    perf_cntr_p->hw_units_arr[hw_unit_id].mopct_in_hw_unit++;


out:
    return ret;
}


static int __perf_cntr_add_pair_to_counters_db(struct kobject  *kobj,
                                               int              hw_unit_id,
                                               int              counter_id,
                                               sxd_chip_types_t chip_type)
{
    struct sx_dev     *dev = NULL;
    struct kobject    *kobj_asic = kobj->parent;
    struct sx_priv    *priv = NULL;
    struct mopct_node *last_mopct_node = NULL;
    int                hw_unit_max_counters = 0;
    int                ret = 0;


    ret = sx_core_asic_get_dev(kobj_asic, &dev);
    if (ret) {
        printk(KERN_ERR PFX "sysfs entry performance counters got invalid value\n");
        goto out;
    }

    priv = sx_priv(dev);

    /* Retrieve the hw_unit_id mopct list
     * If list is empty, add new a mopct node.
     * If list is not empty, we should look at the last mopct node,
     * We check if counters_num <= max_counters_num for the hw_unit_id.
     * If the last node still has a room, add the counter_id to the node.
     * If not, we should generate a new mopct node and add it to the end of the list.
     */
    if (list_empty(&priv->perf_cntr.hw_units_arr[hw_unit_id].mopct_list) == 0) { /* list is not empty*/
        hw_unit_max_counters = __perf_cntr_get_hw_unit_max_counters(chip_type, hw_unit_id);

        last_mopct_node = list_last_entry(&priv->perf_cntr.hw_units_arr[hw_unit_id].mopct_list,
                                          struct mopct_node,
                                          hw_unit_list);
        if (last_mopct_node->mopct.num_active_counters < hw_unit_max_counters) {
            last_mopct_node->mopct.enabled_counters[last_mopct_node->mopct.num_active_counters] = counter_id;
            last_mopct_node->mopct.num_active_counters++;
        } else {
            ret = __perf_cntr_add_new_mopct_node_to_list(&priv->perf_cntr, hw_unit_id, counter_id);
            if (ret) {
                printk(KERN_ERR PFX "failed to add new sysfs entry performance counter\n");
                goto out;
            }
        }
    } else {
        ret = __perf_cntr_add_new_mopct_node_to_list(&priv->perf_cntr, hw_unit_id, counter_id);
        if (ret) {
            printk(
                KERN_ERR PFX "failed to add new counter_id [0x%x], hw_unit_id [0x%x] for sysfs entry performance counter\n",
                counter_id,
                hw_unit_id);
            goto out;
        }
    }

out:
    return ret;
}

char * __sx_sysfs_get_str(char *buffer, char **str, const char* delimiters)
{
    char *running;
    char *token;

    running = buffer;
    token = strsep(&running, delimiters);
    if (token == NULL) {
        *str = 0;
        return NULL;
    }

    *str = token;
    return running;
}


char * __sx_sysfs_get_id_str(char *buffer, char **str)
{
    const char delimiters[] = ":";
    char      *running;

    running = __sx_sysfs_get_str(buffer, str, delimiters);
    return running;
}

char * __sx_sysfs_get_hw_unit_counter_pair_str(char *buffer, char **str)
{
    const char delimiters[] = "\r\n";
    char      *running;

    running = __sx_sysfs_get_str(buffer, str, delimiters);
    return running;
}


static ssize_t __show_asic_perf_cntr_interval(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int ret = 0;
    int interval = 0;
    int len = 0;

    ret = __sx_core_get_asic_perf_cntr_interval(kobj, &interval);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get module performance counter information\n");
        return ret;
    }

    len = sprintf(buf, "%d\n", interval);

    return len;
}


static ssize_t __store_asic_perf_cntr_interval(struct kobject        *kobj,
                                               struct kobj_attribute *attr,
                                               const char            *buf,
                                               size_t                 len)
{
    int ret = 0;
    int interval = 0;


    ret = kstrtoint(buf, 10, &interval);
    if (ret) {
        printk(KERN_ERR PFX "sysfs entry /interval got invalid value %d\n", ret);
        ret = -EINVAL;
        goto out;
    }

    /* Interval valid value is 100usec to 5sec
     * interval units are 100usec*/
    if ((interval < 1) || (interval > 50000)) {
        printk(KERN_ERR PFX "sysfs entry interval value is out of range\n");
        ret = -EINVAL;
        goto out;
    }

    ret = __sx_core_set_asic_perf_cntr_interval(kobj, interval);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get module performance counter information\n");
        goto out;
    }
    return len;

out:
    return ret;
}

static ssize_t __show_asic_perf_cntr_counters(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                ret = 0;
    struct sx_dev     *dev = NULL;
    struct kobject    *kobj_asic = kobj->parent;
    struct sx_priv    *priv = NULL;
    struct mopct_node *iter = NULL;
    int                hw_unit_index = 0;
    int                counter_index = 0;
    ssize_t            len = 0, buf_len = 0;
    char               temp_buf[MAX_COUNTER_FILE_ROW_LEN] = {""};

    ret = sx_core_asic_get_dev(kobj_asic, &dev);
    if (ret) {
        printk(KERN_ERR PFX "sysfs entry performance counters got invalid value\n");
        return ret;
    }

    priv = sx_priv(dev);

    for (hw_unit_index = 0; hw_unit_index < PERF_CNTR_MAX_HW_UNIT_ID; hw_unit_index++) {
        if (!list_empty(&priv->perf_cntr.hw_units_arr[hw_unit_index].mopct_list)) {
            list_for_each_entry(iter, &priv->perf_cntr.hw_units_arr[hw_unit_index].mopct_list, hw_unit_list){
                for (counter_index = 0; counter_index < (iter->mopct.num_active_counters); counter_index++) {
                    len = snprintf(temp_buf, MAX_COUNTER_FILE_ROW_LEN, "0x%x:0x%x\n",
                                   iter->mopct.hw_unit_id, iter->mopct.enabled_counters[counter_index]);
                    if (len < 0) {
                        printk(KERN_ERR PFX "sysfs entry performance counters internal error. \n");
                        goto out;
                    }


                    if ((buf_len + len) < (SYSFS_MAX_BUFF_LEN - 1)) {
                        strcat(buf, temp_buf);
                        buf_len += len;
                    }
                }
            }
        }
    }
    /*add the null char */
    buf_len++;
out:
    return buf_len;
}

static ssize_t __store_asic_perf_cntr_counters(struct kobject        *kobj,
                                               struct kobj_attribute *attr,
                                               const char            *buf,
                                               size_t                 len)
{
    int              ret = 0;
    struct sx_dev   *dev = NULL;
    char            *running = NULL;
    char            *hw_unit_counter_id_pair = NULL;
    char            *token = NULL;
    size_t           hw_unit_id = 0;
    size_t           counter_id = 0;
    struct kobject  *kobj_asic = kobj->parent;
    struct sx_priv  *priv = NULL;
    sxd_chip_types_t chip_type = SXD_CHIP_TYPE_UNKNOWN;
    size_t           buff_parsed_len = 0;

    ret = sx_core_asic_get_dev(kobj_asic, &dev);
    if (ret) {
        printk(KERN_ERR PFX "sysfs entry performance counters got invalid value\n");
        goto out;
    }

    priv = sx_priv(dev);
    chip_type = priv->dev_info.dev_info_ro.chip_type;

    running = (char*)buf;

    /* Parse the counters file and store in DB. The DB is array of linked lists.
     * The counter file holds a list of <hw_unit_id : counter_id>.
     * Each element in the DB array is a head of a hw_unit list.
     * The index to the DB array is the hw_unit_id.
     * Each hw_unit list builds up from MOPCT registers that stores the counters of the hw_unit_id.
     * Every node in the lists is ku_mopct_reg.
     * Every time the user opens the counters file, the DB is initialize with the new counter file content.
     */
    sx_asic_perf_counter_deinit(dev);
    sx_asic_perf_counter_init(dev);

    while (*running) {
        if (buff_parsed_len >= (len - 1)) {
            printk(KERN_NOTICE PFX "Reached end of counters file buffer. %ld \n", (len - 1));
            goto out;
        }
        running = __sx_sysfs_get_hw_unit_counter_pair_str(running, &hw_unit_counter_id_pair);
        buff_parsed_len += strlen(hw_unit_counter_id_pair); /*the hw_unit_id:counter_id length + \n . */
        buff_parsed_len++;
        printk(KERN_NOTICE PFX "buff_parsed_len: %ld, hw_unit_counter_id_pair %s\n",
               buff_parsed_len, hw_unit_counter_id_pair);

        hw_unit_counter_id_pair = __sx_sysfs_get_id_str(hw_unit_counter_id_pair, &token);
        ret = kstrtol(token, 0, &hw_unit_id);
        if (ret) {
            printk(KERN_ERR PFX "Failed to get hw unit id, err=%d, token: %s\n", ret, token);
            ret = -EINVAL;
            goto out;
        }
        hw_unit_counter_id_pair = __sx_sysfs_get_id_str(hw_unit_counter_id_pair, &token);
        ret = kstrtol(token, 0, &counter_id);
        if (ret) {
            printk(KERN_ERR PFX "Failed to get counter id, err=%d, token: %s\n", ret, token);
            ret = -EINVAL;
            goto out;
        }

        ret = __perf_cntr_validate_hw_unit_and_cntr_id(kobj, hw_unit_id, counter_id, chip_type);
        if (ret) {
            printk(KERN_ERR PFX "counter_id [0x%lx] or hw_unit_id [0x%lx] value is invalid and will be ignored.\n",
                   counter_id, hw_unit_id);
            continue;
        }
        ret = __perf_cntr_add_pair_to_counters_db(kobj, hw_unit_id, counter_id, chip_type);
        if (ret != 0) {
            printk(KERN_ERR PFX "Failed to process counter_id [0x%lx], hw_unit_id [0x%lx].\n",
                   counter_id, hw_unit_id);
            goto out;
        }
    }

out:
    return len;
}


int sx_sysfs_asic_perf_cntr_counters_db_groups_num_get(struct sx_dev *dev, size_t *perf_counter_groups_max)
{
    int             ret = 0;
    struct sx_priv *priv = NULL;
    int             i = 0;

    priv = sx_priv(dev);

    for (i = 0; i < PERF_CNTR_MAX_GROUP_ID; i++) {
        if (priv->perf_cntr.counter_group_arr[i].mopct_in_group == 0) {
            /*search for the first empty group. */
            *perf_counter_groups_max = i;
            break;
        }
    }
    return ret;
}
EXPORT_SYMBOL(sx_sysfs_asic_perf_cntr_counters_db_groups_num_get);

int sx_sysfs_asic_perf_cntr_counters_db_get(struct sx_dev *dev, const struct group_id_counters_list **counters_bank)
{
    int             ret = 0;
    struct sx_priv *priv = NULL;

    priv = sx_priv(dev);

    *counters_bank = priv->perf_cntr.counter_group_arr;

    return ret;
}
EXPORT_SYMBOL(sx_sysfs_asic_perf_cntr_counters_db_get);

ssize_t sx_asic_perf_counter_init(struct sx_dev *dev)
{
    int             err = 0;
    struct sx_priv *priv = sx_priv(dev);
    int             i = 0;

    for (i = 0; i < PERF_CNTR_MAX_HW_UNIT_ID; i++) {
        INIT_LIST_HEAD(&priv->perf_cntr.hw_units_arr[i].mopct_list);
        priv->perf_cntr.hw_units_arr[i].mopct_in_hw_unit = 0;
    }

    for (i = 0; i < PERF_CNTR_MAX_GROUP_ID; i++) {
        INIT_LIST_HEAD(&priv->perf_cntr.counter_group_arr[i].mopct_list);
        priv->perf_cntr.counter_group_arr[i].mopct_in_group = 0;
    }

    return err;
}

void sx_asic_perf_counter_deinit(struct sx_dev *dev)
{
    struct sx_priv    *priv = sx_priv(dev);
    int                i = 0;
    struct mopct_node *iter, *tmp;

    for (i = 0; i < PERF_CNTR_MAX_HW_UNIT_ID; i++) {
        list_for_each_entry_safe(iter, tmp, &priv->perf_cntr.hw_units_arr[i].mopct_list, hw_unit_list) {
            list_del(&iter->hw_unit_list);
            /* We don't free the allocation here because hw_unit_list and group_id_list are pointing to the same allocation*/
        }
    }

    for (i = 0; i < PERF_CNTR_MAX_GROUP_ID; i++) {
        list_for_each_entry_safe(iter, tmp, &priv->perf_cntr.counter_group_arr[i].mopct_list, group_id_list) {
            list_del(&iter->group_id_list);
            kfree(iter);
        }
    }

    return;
}
