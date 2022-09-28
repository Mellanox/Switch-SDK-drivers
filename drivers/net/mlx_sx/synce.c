/*
 * Copyright (C) 2010-2022 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include "sx.h"
#include "dev_db.h"
#include "synce.h"

enum {
    SX_SYNCE_VENDOR_SI_TIME = 0,
    SX_SYNCE_VENDOR_RENESAS = 1,
    SX_SYNCE_VENDOR_TI      = 2,
    SX_SYNCE_VENDOR_LAST,
};

static const char* sx_synce_vendor_names[] = {
    [SX_SYNCE_VENDOR_SI_TIME] = "SI Time",
    [SX_SYNCE_VENDOR_RENESAS] = "Renesas",
    [SX_SYNCE_VENDOR_TI] = "TI",
};

static ssize_t __show_synce_enabled(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t __show_synce_vendor(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t __show_synce_config_id(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t __show_synce_burn_count(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t __show_synce_local_clock_identity(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t __show_synce_local_ssm_code(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t __show_synce_local_enhanced_ssm_code(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static struct kobj_attribute enabled_attr = __ATTR(synce_enabled,
                                                   S_IRUGO,
                                                   __show_synce_enabled,
                                                   NULL);
static struct kobj_attribute vendor_attr = __ATTR(synce_vendor,
                                                  S_IRUGO,
                                                  __show_synce_vendor,
                                                  NULL);
static struct kobj_attribute config_id_attr = __ATTR(synce_config_id,
                                                     S_IRUGO,
                                                     __show_synce_config_id,
                                                     NULL);
static struct kobj_attribute burn_count_attr = __ATTR(synce_burn_count,
                                                      S_IRUGO,
                                                      __show_synce_burn_count,
                                                      NULL);
static struct kobj_attribute local_clock_identity_attr = __ATTR(synce_local_clock_identity,
                                                                S_IRUGO,
                                                                __show_synce_local_clock_identity,
                                                                NULL);

static struct kobj_attribute local_ssm_code_attr = __ATTR(synce_local_ssm_code,
                                                          S_IRUGO,
                                                          __show_synce_local_ssm_code,
                                                          NULL);
static struct kobj_attribute local_enhanced_ssm_code_attr = __ATTR(synce_local_enhanced_ssm_code,
                                                                   S_IRUGO,
                                                                   __show_synce_local_enhanced_ssm_code,
                                                                   NULL);

static struct attribute* synce_attrs[] = {
    &enabled_attr.attr,
    &vendor_attr.attr,
    &config_id_attr.attr,
    &burn_count_attr.attr,
    &local_clock_identity_attr.attr,
    &local_ssm_code_attr.attr,
    &local_enhanced_ssm_code_attr.attr,
};

static bool __synce_supported = false;

static const char* __get_synce_vendor_name(int id)
{
    if ((id >= SX_SYNCE_VENDOR_SI_TIME) && (id < SX_SYNCE_VENDOR_LAST)) {
        return sx_synce_vendor_names[id];
    }

    return "Unknown";
}

static struct sx_dev* __get_sx_dev(void)
{
    struct sx_dev *dev = NULL;
    int            dev_id;

    if (!sx_core_has_predefined_devices()) {
        return sx_dev_db_get_default_device();
    }

    for (dev_id = 1; DEV_ID_IS_VALID(dev_id); dev_id++) {
        if (DEFAULT_DEVICE_ID_CHECK(dev_id)) {
            continue;
        }

        dev = sx_dev_db_get_dev_by_id(dev_id);
        if (dev) {
            break;
        }
    }

    return dev;
}

/*
 * This need to called with PCI restart lock held, in case the dev pointer is released by PCI restart procedure.
 */
static int __get_mspi_and_sx_dev(struct ku_access_mspi_reg *mspi_reg, struct sx_dev **dev_out)
{
    struct sx_dev *dev;
    int            err;

    dev = __get_sx_dev();
    if (!dev) {
        printk(KERN_ERR PFX "%s: Could not find a valid device\n", __func__);
        err = -ENODEV;
        goto out;
    }

    memset(mspi_reg, 0, sizeof(*mspi_reg));
    mspi_reg->dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mspi_reg->op_tlv, MLXSW_MSPI_ID, EMAD_METHOD_QUERY);
    err = sx_ACCESS_REG_MSPI(dev, mspi_reg);
    if (err) {
        goto out;
    }
    if (dev_out) {
        *dev_out = dev;
    }
    return 0;

out:
    return err;
}

static int __get_mspi(struct ku_access_mspi_reg *mspi_reg)
{
    int err;

    down_read(&sx_glb.pci_restart_lock);
    err = __get_mspi_and_sx_dev(mspi_reg, NULL);
    up_read(&sx_glb.pci_restart_lock);
    return err;
}

static int __get_msecq(struct ku_access_msecq_reg *msecq_reg)
{
    struct ku_access_mspi_reg mspi_reg;
    struct sx_dev            *dev;
    int                       err;

    down_read(&sx_glb.pci_restart_lock);
    err = __get_mspi_and_sx_dev(&mspi_reg, &dev);
    if (err) {
        goto out_unlock;
    }

    if (!mspi_reg.mspi_reg.synce_support) {
        err = -EOPNOTSUPP;
        goto out_unlock;
    }

    memset(msecq_reg, 0, sizeof(*msecq_reg));
    msecq_reg->dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&msecq_reg->op_tlv, MLXSW_MSECQ_ID, EMAD_METHOD_QUERY);
    err = sx_ACCESS_REG_MSECQ(dev, msecq_reg);

out_unlock:
    up_read(&sx_glb.pci_restart_lock);
    return err;
}

static ssize_t __show_synce_enabled(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    struct ku_access_mspi_reg mspi_reg;
    int                       err;

    err = __get_mspi(&mspi_reg);
    if (err) {
        return err;
    }

    return sprintf(buf, "%u\n", !!mspi_reg.mspi_reg.synce_support);
}

static ssize_t __show_synce_vendor(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    struct ku_access_mspi_reg mspi_reg;
    int                       err;

    err = __get_mspi(&mspi_reg);
    if (err) {
        return err;
    }

    if (!mspi_reg.mspi_reg.synce_support) {
        return -EOPNOTSUPP;
    }

    return sprintf(buf, "%s\n", __get_synce_vendor_name(mspi_reg.mspi_reg.vendor_id));
}

static ssize_t __show_synce_config_id(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    struct ku_access_mspi_reg mspi_reg;
    int                       err;

    err = __get_mspi(&mspi_reg);
    if (err) {
        return err;
    }

    if (!mspi_reg.mspi_reg.synce_support) {
        return -EOPNOTSUPP;
    }

    return sprintf(buf, "%u\n", mspi_reg.mspi_reg.config_version_id);
}

static ssize_t __show_synce_burn_count(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    struct ku_access_mspi_reg mspi_reg;
    int                       err;

    err = __get_mspi(&mspi_reg);
    if (err) {
        return err;
    }

    if (!mspi_reg.mspi_reg.synce_support) {
        return -EOPNOTSUPP;
    }

    return sprintf(buf, "%u\n", mspi_reg.mspi_reg.bcc);
}

static ssize_t __show_synce_local_clock_identity(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    struct ku_access_msecq_reg msecq_reg;
    int                        err;

    err = __get_msecq(&msecq_reg);
    if (err) {
        return err;
    }

    return sprintf(buf, "%llu\n", msecq_reg.msecq_reg.local_clock_identity);
}

static ssize_t __show_synce_local_ssm_code(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    struct ku_access_msecq_reg msecq_reg;
    int                        err;

    err = __get_msecq(&msecq_reg);
    if (err) {
        return err;
    }

    return sprintf(buf, "%u\n", msecq_reg.msecq_reg.local_ssm_code);
}

static ssize_t __show_synce_local_enhanced_ssm_code(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    struct ku_access_msecq_reg msecq_reg;
    int                        err;

    err = __get_msecq(&msecq_reg);
    if (err) {
        return err;
    }

    return sprintf(buf, "%u\n", msecq_reg.msecq_reg.local_enhanced_ssm_code);
}

int sx_core_synce_init_spectrum(void)
{
    int err;
    int i;

    for (i = 0; i < ARRAY_SIZE(synce_attrs); i++) {
        err = sysfs_create_file(&(THIS_MODULE->mkobj.kobj), synce_attrs[i]);
        if (err) {
            goto err_sysfs_create_file;
        }
    }

    return 0;

err_sysfs_create_file:
    for (i--; i >= 0; i--) {
        sysfs_remove_file(&(THIS_MODULE->mkobj.kobj), synce_attrs[i]);
    }
    return err;
}

void sx_core_synce_deinit_spectrum(void)
{
    int i;

    for (i = 0; i < ARRAY_SIZE(synce_attrs); i++) {
        sysfs_remove_file(&(THIS_MODULE->mkobj.kobj), synce_attrs[i]);
    }
}

int sx_core_synce_init(void)
{
    int            err;
    struct sx_dev *dev;

    dev = __get_sx_dev();
    if (!dev) {
        printk(KERN_ERR PFX "%s: Could not find a valid device\n", __func__);
        return -ENODEV;
    }

    err = __sx_core_dev_specific_cb_get_reference(dev);
    if (err) {
        printk(KERN_ERR PFX "%s: Could not get device specific callback\n", __func__);
        return err;
    }
    if (sx_priv(dev)->dev_specific_cb.synce_init_cb != NULL) {
        err = sx_priv(dev)->dev_specific_cb.synce_init_cb();
        if (!err) {
            __synce_supported = true;
        }
    }
    __sx_core_dev_specific_cb_release_reference(dev);
    return err;
}

void sx_core_synce_deinit(void)
{
    int            err;
    struct sx_dev *dev;

    dev = __get_sx_dev();
    if (!dev) {
        printk(KERN_ERR PFX "%s: Could not find a valid device\n", __func__);
        return;
    }

    err = __sx_core_dev_specific_cb_get_reference(dev);
    if (err) {
        printk(KERN_ERR PFX "%s: Could not get device specific callback\n", __func__);
        return;
    }
    if (sx_priv(dev)->dev_specific_cb.synce_deinit_cb != NULL) {
        sx_priv(dev)->dev_specific_cb.synce_deinit_cb();
    }
    __sx_core_dev_specific_cb_release_reference(dev);
}

int sx_core_synce_dump(struct seq_file *m, void *v, void *context)
{
    int                       err;
    struct ku_access_mspi_reg mspi_reg;

    if (!__synce_supported) {
        return 0;
    }

    err = __get_mspi(&mspi_reg);
    if (err) {
        return err;
    }

    seq_printf(m, "SyncE dump:\n");
    if (!mspi_reg.mspi_reg.synce_support) {
        seq_printf(m, "SyncE supported: No\n");
        return 0;
    } else {
        seq_printf(m, "SyncE supported: Yes\n");
    }

    seq_printf(m, "Vendor ID: %s\n", __get_synce_vendor_name(mspi_reg.mspi_reg.vendor_id));
    seq_printf(m, "Configuration version ID: %u\n", mspi_reg.mspi_reg.config_version_id);
    seq_printf(m, "Burned configuration count: %u\n", mspi_reg.mspi_reg.bcc);
    if (mspi_reg.mspi_reg.obtv) {
        seq_printf(m, "On board temperature valid: Yes\n");
        seq_printf(m, "On board sensor temperature: %u\n", mspi_reg.mspi_reg.obs_temperature);
    } else {
        seq_printf(m, "On board temperature valid: No\n");
    }
    if (mspi_reg.mspi_reg.bitv) {
        seq_printf(m, "Built in OCXO sensor temperature valid: Yes\n");
        seq_printf(m, "Built in sensor temperature: %u\n", mspi_reg.mspi_reg.bis_temperature);
    } else {
        seq_printf(m, "Built in OCXO sensor temperature valid: No\n");
    }
    return 0;
}
