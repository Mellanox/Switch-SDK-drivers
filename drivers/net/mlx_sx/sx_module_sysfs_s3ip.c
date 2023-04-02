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
#include <linux/if_vlan.h>
#include <linux/poll.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/skb_hook.h>
#include <linux/seq_file.h>
#include <linux/ktime.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/errno.h>

#include <linux/mlx_sx/auto_registers/cmd_auto.h>

#include "sx.h"
#include "alloc.h"
#include "dev_init.h"
#include "dev_db.h"

/************************************************
 *  Define
 ***********************************************/
#define PORT_IS_PRESENT(pmaos_oper_status)                                       \
    ((pmaos_oper_status == SXD_PMAOS_OPER_STATUS_INITIALIZING_E) ||              \
     (pmaos_oper_status == SXD_PMAOS_OPER_STATUS_PLUGGED_ENABLED_E) ||           \
     (pmaos_oper_status == SXD_PMAOS_OPER_STATUS_MODULE_PLUGGED_WITH_ERROR_E) || \
     (pmaos_oper_status == SXD_PMAOS_OPER_STATUS_PLUGGED_DISABLED_E))

#define OP_NOT_SUPPORTED "Operation not supported"
/************************************************
 *  Enum
 ***********************************************/


/************************************************
 * Globals
 ***********************************************/


/************************************************
 *  Functions
 ***********************************************/
static ssize_t show_module_power_on(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t store_module_power_on(struct kobject        *kobj,
                                     struct kobj_attribute *attr,
                                     const char            *buf,
                                     size_t                 len);
static ssize_t show_module_tx_disable(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t store_module_tx_disable(struct kobject        *kobj,
                                       struct kobj_attribute *attr,
                                       const char            *buf,
                                       size_t                 len);
static ssize_t show_module_present(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t show_module_rx_los(struct kobject *kobj, struct kobj_attribute *attr, char *buf);

static ssize_t show_module_id(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t reset_module(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len);
static ssize_t store_module_power_mode_policy(struct kobject        *kobj,
                                              struct kobj_attribute *attr,
                                              const char            *buf,
                                              size_t                 len);
static ssize_t show_module_power_mode_policy(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t show_module_power_mode(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t show_module_temp_input(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t show_module_temp_label(struct kobject *kobj, struct kobj_attribute *attr, char *buf);

static struct kobj_attribute module_power_on_attr = __ATTR(power_on,
                                                           (S_IRUGO | S_IWUSR),
                                                           show_module_power_on,
                                                           store_module_power_on);
static struct kobj_attribute module_tx_disable_attr = __ATTR(tx_disable,
                                                             (S_IRUGO | S_IWUSR),
                                                             show_module_tx_disable,
                                                             store_module_tx_disable);
static struct kobj_attribute module_present_attr = __ATTR(present, S_IRUGO, show_module_present, NULL);
static struct kobj_attribute module_rx_los_attr = __ATTR(rx_los, S_IRUGO, show_module_rx_los, NULL);

static struct kobj_attribute module_id_attr = __ATTR(id, S_IRUGO, show_module_id, NULL);
static struct kobj_attribute module_reset_attr = __ATTR(reset, S_IWUSR, NULL, reset_module);
static struct kobj_attribute module_power_mode_policy_attr = __ATTR(power_mode_policy,
                                                                    (S_IRUGO | S_IWUSR),
                                                                    show_module_power_mode_policy,
                                                                    store_module_power_mode_policy);
static struct kobj_attribute module_power_mode_attr = __ATTR(power_mode, S_IRUGO, show_module_power_mode, NULL);
static struct kobj_attribute module_temp_input_attr = __ATTR(input, S_IRUGO, show_module_temp_input, NULL);
static struct kobj_attribute module_temp_label_attr = __ATTR(label, S_IRUGO, show_module_temp_label, NULL);

int sx_core_get_module_power_on(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool          *power_on)
{
    int                        err = 0;
    struct ku_access_pmaos_reg pmaos_reg_data;

    memset(&pmaos_reg_data, 0, sizeof(pmaos_reg_data));
    pmaos_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&pmaos_reg_data.op_tlv, PMAOS_REG_ID, EMAD_METHOD_QUERY);

    pmaos_reg_data.pmaos_reg.slot_index = slot_id;
    pmaos_reg_data.pmaos_reg.module = module_id;

    err = sx_ACCESS_REG_PMAOS(dev, &pmaos_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access PMAOS, err=%d\n", err);
        goto out;
    }

    if (pmaos_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access PMAOS, status=%d\n", pmaos_reg_data.op_tlv.status);
        goto out;
    }

    *power_on = false;
    if (pmaos_reg_data.pmaos_reg.admin_status != SXD_PMAOS_ADMIN_STATUS_DISABLED_BY_CONFIGURATION_E) {
        *power_on = true;
    }

out:
    return err;
}

int sx_core_get_port_module_power_on(struct sx_dev *dev, uint16_t local_port, bool          *power_on)
{
    int           err = 0;
    unsigned long flags;
    uint8_t       slot_id = 0;
    uint8_t       module_id = 0;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    err = sx_core_get_module_by_port(dev, local_port, &slot_id, &module_id);
    if (err) {
        spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    err = sx_core_get_module_power_on(dev, slot_id, module_id, power_on);
out:
    return err;
}
EXPORT_SYMBOL(sx_core_get_port_module_power_on);

int sx_core_power_on_off_module(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool power_on)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    int             i = 0;
    unsigned long   flags;
    bool            any_port_up = false;
    uint16_t        local_port = 0;

    spin_lock_irqsave(&priv->db_lock, flags);
    if (!power_on) {
        for (i = 0; i < priv->modules_to_port_map_count[slot_id][module_id]; i++) {
            local_port = priv->module_to_ports_map[slot_id][module_id][i];
            if ((priv->local_port_state[local_port] == SXD_PAOS_ADMIN_STATUS_UP_E) ||
                (priv->local_port_state[local_port] == SXD_PAOS_ADMIN_STATUS_UP_ONCE_E)) {
                any_port_up = true;
                break;
            }
        }

        if (any_port_up) {
            spin_unlock_irqrestore(&priv->db_lock, flags);
            err = -EACCES;
            goto out;
        }
    }
    spin_unlock_irqrestore(&priv->db_lock, flags);

    mutex_lock(&priv->module_access_mutex);
    err = sx_core_set_module(dev, slot_id, module_id, power_on, 0);
    if (err) {
        mutex_unlock(&priv->module_access_mutex);
        goto out;
    }
    mutex_unlock(&priv->module_access_mutex);

out:
    return err;
}

int sx_core_power_on_off_port_module(struct sx_dev *dev, uint16_t local_port, bool power_on)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    unsigned long   flags;
    uint8_t         slot_id = 0;
    uint8_t         module_id = 0;

    spin_lock_irqsave(&priv->db_lock, flags);
    err = sx_core_get_module_by_port(dev, local_port, &slot_id, &module_id);
    if (err) {
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&priv->db_lock, flags);

    err = sx_core_power_on_off_module(dev, slot_id, module_id, power_on);

out:
    return err;
}
EXPORT_SYMBOL(sx_core_power_on_off_port_module);

/*
 *   sx_core module sysfs nodes of non-eeprom are like:
 *       ./sx_core/$asic/$module_id/x_s3ip_x
 *       ./sx_core/$asic/$module_id/x_non-s3ip_x
 *       ./sx_core/$asic/$module_id/temperature/x
 */
static int __module_sysfs_get_dev_slot_module(struct kobject *kobj,
                                              uint8_t         module_pos,
                                              struct sx_dev **dev,
                                              uint8_t        *slot,
                                              uint8_t        *module)
{
    int             ret = 0;
    int             module_id = 0;
    int             mod_offset = 0;
    struct kobject *kobj_module = kobj;

    if (!kobj) {
        printk(KERN_ERR PFX "Invalid kobj %s\n", kobject_name(kobj));
        ret = -EINVAL;
        goto out;
    }

    if (!(*dev) && !slot && !module) {
        printk(KERN_ERR PFX "Wrong dev, slot, module for kobj %s\n", kobject_name(kobj));
        ret = -EINVAL;
        goto out;
    }

    mod_offset = module_pos;
    for ( ; mod_offset > 0; mod_offset--) {
        if (kobj_module) {
            kobj_module = kobj_module->parent;
        }
    }
    if (!kobj_module) {
        printk(KERN_ERR PFX "Invalid sysfs node entry because of no finding module kobject: kobj %s\n",
               kobject_name(kobj));
        ret = -EINVAL;
        goto out;
    }

    ret = kstrtoint(kobj_module->name + strlen(MODULE_NODE_SYSFS_PREFIX), 10, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "Invalid sysfs node entry because of wrong module kobject: kobj %s\n", kobject_name(kobj));
        ret = -EINVAL;
        goto out;
    }

    if (module_id > MAX_MODULE_NUM - 1) {
        printk(KERN_ERR PFX "Invalid module value %d for sysfs kobject %s\n", module_id, kobject_name(kobj));
        goto out;
    }

    ret = sx_core_asic_get_dev(kobj_module->parent, dev);
    if (ret) {
        printk(KERN_ERR PFX "sysfs entry power_on got invalid value\n");
        goto out;
    }

    if (module) {
        *module = module_id;
    }

    if (slot) {
        *slot = sx_priv(*dev)->module_to_slot_map[module_id];
    }

out:
    return ret;
}


static ssize_t show_module_power_on(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int            ret = 0;
    bool           power_on = false;
    int            len = 0;
    int            val = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "show_module_power_on: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_module_power_on(dev, slot_id, module_id, &power_on);
    if (ret) {
        printk(KERN_ERR PFX "show_module_power_on: sx_core_get_module_power_on failed (%d) for %s\n",
               ret,
               kobject_name(kobj));
        return ret;
    }

    if (power_on) {
        val = 1;
    }

    len = sprintf(buf, "%d\n", val);

    return len;

out:
    return ret;
}

static ssize_t store_module_power_on(struct kobject        *kobj,
                                     struct kobj_attribute *attr,
                                     const char            *buf,
                                     size_t                 len)
{
    int            ret = 0;
    int            power_on = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = kstrtoint(buf, 10, &power_on);
    if (ret) {
        printk(KERN_ERR PFX "sysfs entry power_on got invalid value\n");
        ret = -EINVAL;
        goto out;
    }

    if ((power_on != SX_MODULE_POWER_ON) &&
        (power_on != SX_MODULE_POWER_OFF)) {
        printk(KERN_ERR PFX "sysfs entry power_on got invalid value\n");
        ret = -EINVAL;
        goto out;
    }

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of power_on sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "store_module_power_on: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_power_on_off_module(dev, slot_id, module_id, (power_on == SX_MODULE_POWER_ON));
    if (ret) {
        printk(KERN_ERR PFX "store_module_power_on: sx_core_power_on_off_module failed (%d) for %s\n",
               ret,
               kobject_name(kobj));
        goto out;
    }

    return len;

out:
    return ret;
}


static int __get_port_module_pmcr_data(struct sx_dev             *dev,
                                       uint16_t                   local_port,
                                       struct ku_access_pmcr_reg *pmcr_reg_data)
{
    int err = 0;

    memset(pmcr_reg_data, 0, sizeof(*pmcr_reg_data));
    pmcr_reg_data->dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&pmcr_reg_data->op_tlv, MLXSW_PMCR_ID, EMAD_METHOD_QUERY);

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(pmcr_reg_data->pmcr_reg.local_port,
                                        pmcr_reg_data->pmcr_reg.lp_msb,
                                        local_port);

    err = sx_ACCESS_REG_PMCR(dev, pmcr_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access PMCR, err=%d\n", err);
        err = -EIO;
        goto out;
    }

    if (pmcr_reg_data->op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access PMCR, status=%d\n", pmcr_reg_data->op_tlv.status);
        goto out;
    }

    if (pmcr_reg_data->pmcr_reg.tx_disable_override_cap == 0) {
        printk(KERN_NOTICE PFX "TX_DISABLE is not supported on the port(0x%x)'s module\n", local_port);
    }

out:
    return err;
}

int sx_core_get_port_module_tx_disable(struct sx_dev *dev, uint16_t local_port, bool *tx_disable)
{
    int                       err = 0;
    struct ku_access_pmcr_reg pmcr_reg_data;

    err = __get_port_module_pmcr_data(dev, local_port, &pmcr_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to get the port(0x%x) module's pmcr data, err=%d\n", local_port, err);
        goto out;
    }

    *tx_disable = false;
    if ((pmcr_reg_data.pmcr_reg.tx_disable_override_cntl == 2) &&
        (pmcr_reg_data.pmcr_reg.tx_disable_override_value == 1)) {
        *tx_disable = true;
    }

out:
    return err;
}
EXPORT_SYMBOL(sx_core_get_port_module_tx_disable);

/* Notice: according to PRM PMCR, tx_disable will take effect after the port becomes admin_enable again. */
int sx_core_set_port_module_tx_disable(struct sx_dev *dev, uint16_t local_port, bool tx_disable)/*TBD: to "Not supported" */
{
    struct sx_priv           *priv = sx_priv(dev);
    int                       err = 0;
    struct ku_access_pmcr_reg pmcr_reg_data;
    bool                      release_lock = false;

    err = __get_port_module_pmcr_data(dev, local_port, &pmcr_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to get the port(0x%x) module's pmcr data, err=%d\n", local_port, err);
        goto out;
    }

    pmcr_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&pmcr_reg_data.op_tlv, MLXSW_PMCR_ID, EMAD_METHOD_WRITE);

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(pmcr_reg_data.pmcr_reg.local_port,
                                        pmcr_reg_data.pmcr_reg.lp_msb,
                                        local_port);
    pmcr_reg_data.pmcr_reg.tx_disable_override_cntl = 0;
    if (tx_disable) {
        pmcr_reg_data.pmcr_reg.tx_disable_override_cntl = 2;
        pmcr_reg_data.pmcr_reg.tx_disable_override_value = 1;
    }

    mutex_lock(&priv->module_access_mutex);
    release_lock = true;

    err = sx_ACCESS_REG_PMCR(dev, &pmcr_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to write PMCR, err=%d\n", err);
        goto out;
    }

    if (pmcr_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to write PMCR, status=%d\n", pmcr_reg_data.op_tlv.status);
        goto out;
    }

out:
    if (release_lock) {
        mutex_unlock(&priv->module_access_mutex);
    }
    return err;
}
EXPORT_SYMBOL(sx_core_set_port_module_tx_disable);

/* sysfs entry "tx_disable" under sx_core will be further determined by arch team */
static ssize_t show_module_tx_disable(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    SX_CORE_UNUSED_PARAM(attr);
    SX_CORE_UNUSED_PARAM(buf);

    sprintf(buf, "%s", OP_NOT_SUPPORTED);
    printk(KERN_NOTICE PFX "%s: %s for %s.\n", __func__, OP_NOT_SUPPORTED, kobject_name(kobj));

    return -EOPNOTSUPP;
}

static ssize_t store_module_tx_disable(struct kobject        *kobj,
                                       struct kobj_attribute *attr,
                                       const char            *buf,
                                       size_t                 len)
{
    SX_CORE_UNUSED_PARAM(attr);
    SX_CORE_UNUSED_PARAM(buf);
    SX_CORE_UNUSED_PARAM(len);

    printk(KERN_NOTICE PFX "%s: %s for %s.\n", __func__, OP_NOT_SUPPORTED, kobject_name(kobj));
    return -EOPNOTSUPP;
}

int sx_core_get_module_present(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool          *present)
{
    int                        err = 0;
    struct ku_access_pmaos_reg pmaos_reg_data;

    memset(&pmaos_reg_data, 0, sizeof(pmaos_reg_data));
    pmaos_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&pmaos_reg_data.op_tlv, PMAOS_REG_ID, EMAD_METHOD_QUERY);

    pmaos_reg_data.pmaos_reg.slot_index = slot_id;
    pmaos_reg_data.pmaos_reg.module = module_id;

    err = sx_ACCESS_REG_PMAOS(dev, &pmaos_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access PMAOS, err=%d\n", err);
        goto out;
    }

    if (pmaos_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access PMAOS, status=%d\n", pmaos_reg_data.op_tlv.status);
        goto out;
    }

    *present = false;
    if (PORT_IS_PRESENT(pmaos_reg_data.pmaos_reg.oper_status)) {
        *present = true;
    }

out:
    return err;
}

int sx_core_get_port_module_present(struct sx_dev *dev, uint16_t local_port, bool          *present)
{
    int             err = 0;
    unsigned long   flags;
    struct sx_priv *priv = sx_priv(dev);
    uint8_t         slot_id = 0;
    uint8_t         module_id = 0;

    spin_lock_irqsave(&priv->db_lock, flags);
    err = sx_core_get_module_by_port(dev, local_port, &slot_id, &module_id);
    if (err) {
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&priv->db_lock, flags);

    err = sx_core_get_module_present(dev, slot_id, module_id, present);
out:
    return err;
}
EXPORT_SYMBOL(sx_core_get_port_module_present);

static ssize_t show_module_present(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int            ret = 0;
    bool           present = false;
    int            len = 0;
    int            val = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "show_module_power_on: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_module_present(dev, slot_id, module_id, &present);
    if (ret) {
        printk(KERN_ERR PFX "Failed in sx_netdev_module_get_present\n");
        goto out;
    }

    if (present) {
        val = 1;
    }

    len = sprintf(buf, "%d\n", val);

    return len;

out:
    return ret;
}

int sx_core_get_port_module_rx_los(struct sx_dev *dev, uint16_t local_port, bool *rx_los)
{
    struct ku_access_pddr_reg reg_data;
    int                       err = 0;
    uint8_t                   status_opcode = 0;

    memset(&reg_data, 0, sizeof(reg_data));

    reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, PDDR_REG_ID, EMAD_METHOD_QUERY);

    reg_data.pddr_reg.page_select = SXD_PDDR_PAGE_SELECT_MODULE_LATCHED_FLAG_INFO_PAGE_E;
    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.pddr_reg.local_port,
                                        reg_data.pddr_reg.lp_msb,
                                        local_port);
    reg_data.pddr_reg.pnat = SXD_PDDR_PNAT_LOCAL_PORT_NUMBER_E;

    err = sx_ACCESS_REG_PDDR(dev, &reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to call sx_ACCESS_REG_PDDR (err:%d)\n", err);
        goto out;
    }

    if (reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access PDDR, status=%d\n", reg_data.op_tlv.status);
        goto out;
    }

    status_opcode =
        reg_data.pddr_reg.page_data.module_latched_flag_info.rx_los;
    pr_debug(PFX "%s (latched_flag, status_opcode:0x%x)\n", __func__, status_opcode);

    *rx_los = false;
    if (status_opcode) {
        *rx_los = true;
    }

out:
    return err;
}
EXPORT_SYMBOL(sx_core_get_port_module_rx_los);

/* sysfs entry "rx_los" under sx_core will be further determined by arch team */
static ssize_t show_module_rx_los(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int len = 0;

    len = sprintf(buf, "%s", OP_NOT_SUPPORTED);
    printk(KERN_NOTICE PFX "%s: %s for %s.\n", __func__, OP_NOT_SUPPORTED, kobject_name(kobj));
    return -EOPNOTSUPP;
}

static ssize_t show_module_id(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int            ret = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;
    int            len = 0;

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of reset sysfs node is NULL\n");
        ret = -EINVAL;
        return ret;
    }

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n", __func__, ret,
               kobject_name(kobj));
        goto out;
    }

    len = sprintf(buf, "%u\n", module_id);
    return len;

out:
    return ret;
}

static ssize_t reset_module(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len)
{
    int            ret = 0;
    int            reset = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = kstrtoint(buf, 10, &reset);
    if (ret) {
        printk(KERN_INFO PFX "sysfs entry reset got invalid value\n");
        goto out;
    }

    if (!reset) {
        ret = -EINVAL;
        goto out;
    }

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of reset sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n", __func__, ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_reset_module(dev, slot_id, module_id);
    if (ret) {
        printk(KERN_ERR PFX "Failed in sx_core_reset_module\n");
        return ret;
    }

    return len;
out:
    return ret;
}

static ssize_t store_module_power_mode_policy(struct kobject        *kobj,
                                              struct kobj_attribute *attr,
                                              const char            *buf,
                                              size_t                 len)
{
    int            ret = 0;
    int            power_mode_policy = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = kstrtoint(buf, 10, &power_mode_policy);
    if (ret) {
        printk(KERN_ERR PFX "sysfs entry power_mode_policy got invalid value\n");
        ret = -EINVAL;
        goto out;
    }

    if ((power_mode_policy != SX_MODULE_POWER_MODE_POLICY_AUTO) &&
        (power_mode_policy != SX_MODULE_POWER_MODE_POLICY_HIGH)) {
        printk(KERN_ERR PFX "sysfs entry power_mode_policy got invalid value\n");
        ret = -EINVAL;
        goto out;
    }

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of reset sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n", __func__, ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_set_module_power_mode_policy(dev,
                                               slot_id,
                                               module_id,
                                               (enum sx_module_power_mode_policy)power_mode_policy);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_set_module_power_mode_policy failed (%d) for %s\n", __func__, ret,
               kobject_name(kobj));
        goto out;
    }

    return len;
out:
    return ret;
}

static ssize_t show_module_power_mode_policy(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                                ret = 0;
    struct sx_module_power_mode_params params;
    struct sx_dev                     *dev = NULL;
    uint8_t                            slot_id = 0;
    uint8_t                            module_id = 0;
    int                                len = 0;

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of reset sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n", __func__, ret,
               kobject_name(kobj));
        goto out;
    }

    memset(&params, 0, sizeof(params));

    ret = sx_core_get_module_power_mode(dev, slot_id, module_id, &params);
    if (ret) {
        printk(KERN_ERR PFX "Failed in sx_core_get_module_power_mode\n");
        goto out;
    }

    len = sprintf(buf, "%u\n", params.policy);

    return len;

out:
    return ret;
}

static ssize_t show_module_power_mode(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                                ret = 0;
    struct sx_module_power_mode_params params;
    struct sx_dev                     *dev = NULL;
    uint8_t                            slot_id = 0;
    uint8_t                            module_id = 0;
    int                                len = 0;

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of reset sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n", __func__, ret,
               kobject_name(kobj));
        goto out;
    }

    memset(&params, 0, sizeof(params));

    ret = sx_core_get_module_power_mode(dev, slot_id, module_id, &params);
    if (ret) {
        printk(KERN_ERR PFX "Failed in sx_core_get_module_power_mode\n");
        goto out;
    }

    len = sprintf(buf, "%u\n", params.mode);

    return len;
out:
    return ret;
}

static int __sx_core_get_module_temperature(struct kobject *kobj, struct sx_temperature_params *params)
{
    int            ret = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of temperature sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = __module_sysfs_get_dev_slot_module(kobj, 1, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n", __func__, ret,
               kobject_name(kobj));
        goto out;
    }

    memset(params, 0, sizeof(struct sx_temperature_params));
    ret = sx_core_get_module_temperature(dev, slot_id, module_id, params);
    if (ret) {
        goto out;
    }

out:
    return ret;
}

static ssize_t show_module_temp_input(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                          ret = 0;
    struct sx_temperature_params params;
    int                          len = 0;

    ret = __sx_core_get_module_temperature(kobj, &params);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get module temperature information\n");
        return ret;
    }

    len = sprintf(buf, "%llu\n", params.input);

    return len;
}

static ssize_t show_module_temp_label(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                          ret = 0;
    struct sx_temperature_params params;
    int                          len = 0;


    ret = __sx_core_get_module_temperature(kobj, &params);
    if (ret) {
        printk(KERN_ERR PFX "Failed to get module temperature information\n");
        return ret;
    }

    len = sprintf(buf, "%s\n", params.label);

    return len;
}

int sx_core_create_module_sysfs_extension_for_s3ip(struct kobject *parent)
{
    int err = 0;

    err = sysfs_create_file(parent, &(module_power_on_attr.attr));
    if (err) {
        goto out;
    }
    err = sysfs_create_file(parent, &(module_tx_disable_attr.attr));
    if (err) {
        goto phase1_err;
    }
    err = sysfs_create_file(parent, &(module_present_attr.attr));
    if (err) {
        goto phase2_err;
    }
    err = sysfs_create_file(parent, &(module_rx_los_attr.attr));
    if (err) {
        goto phase3_err;
    }

    return err;

phase3_err:
    sysfs_remove_file(parent, &(module_present_attr.attr));
phase2_err:
    sysfs_remove_file(parent, &(module_tx_disable_attr.attr));
phase1_err:
    sysfs_remove_file(parent, &(module_power_on_attr.attr));
out:
    return err;
}
EXPORT_SYMBOL(sx_core_create_module_sysfs_extension_for_s3ip);

void sx_core_delete_module_sysfs_extension_for_s3ip(struct kobject *parent)
{
    sysfs_remove_file(parent, &(module_power_on_attr.attr));
    sysfs_remove_file(parent, &(module_rx_los_attr.attr));
    sysfs_remove_file(parent, &(module_present_attr.attr));
    sysfs_remove_file(parent, &(module_tx_disable_attr.attr));
}
EXPORT_SYMBOL(sx_core_delete_module_sysfs_extension_for_s3ip);

/* for misc module sysfs entries under sx_core: id, reset, power_mode_policy, power_mode */
int sx_core_create_module_sysfs_extension_for_misc(struct module_sysfs_node *root)
{
    int             err = 0;
    struct kobject *module = root->module;
    struct kobject *temperature = NULL;

    err = sysfs_create_file(module, &(module_id_attr.attr));
    if (err) {
        goto out;
    }

    err = sysfs_create_file(module, &(module_reset_attr.attr));
    if (err) {
        goto phase1_err;
    }
    err = sysfs_create_file(module, &(module_power_mode_policy_attr.attr));
    if (err) {
        goto phase2_err;
    }
    err = sysfs_create_file(module, &(module_power_mode_attr.attr));
    if (err) {
        goto phase3_err;
    }

    temperature = kobject_create_and_add("temperature", module);
    if (temperature == NULL) {
        err = -ENOMEM;
        goto phase4_err;
    }
    err = sysfs_create_file(temperature, &(module_temp_input_attr.attr));
    if (err) {
        err = -ENOMEM;
        goto phase5_err;
    }
    err = sysfs_create_file(temperature, &(module_temp_label_attr.attr));
    if (err) {
        err = -ENOMEM;
        goto phase6_err;
    }
    root->temperature = temperature;

    return err;

phase6_err:
    sysfs_remove_file(temperature, &(module_temp_input_attr.attr));
phase5_err:
    kobject_put(temperature);
phase4_err:
    sysfs_remove_file(module, &(module_power_mode_attr.attr));
phase3_err:
    sysfs_remove_file(module, &(module_power_mode_policy_attr.attr));
phase2_err:
    sysfs_remove_file(module, &(module_reset_attr.attr));
phase1_err:
    sysfs_remove_file(module, &(module_id_attr.attr));
out:
    return err;
}
EXPORT_SYMBOL(sx_core_create_module_sysfs_extension_for_misc);

void sx_core_delete_module_sysfs_extension_for_misc(struct module_sysfs_node *root)
{
    sysfs_remove_file(root->temperature, &(module_temp_label_attr.attr));
    sysfs_remove_file(root->temperature, &(module_temp_input_attr.attr));
    kobject_put(root->temperature);
    sysfs_remove_file(root->module, &(module_power_mode_attr.attr));
    sysfs_remove_file(root->module, &(module_power_mode_policy_attr.attr));
    sysfs_remove_file(root->module, &(module_reset_attr.attr));
    sysfs_remove_file(root->module, &(module_id_attr.attr));
}
EXPORT_SYMBOL(sx_core_delete_module_sysfs_extension_for_misc);

static void __sx_pmpe_dwork_handler(struct work_struct *dwork_p)
{
    pmpe_dwdata_t *dwdata_p = container_of(dwork_p, pmpe_dwdata_t, dwork.work);

    sysfs_notify(dwdata_p->module, NULL, "present");

    kfree(dwdata_p);
}

static void __sx_handle_pmpe_event(struct completion_info *comp_info, void *context)
{
    struct sxd_emad_pmpe_reg    *pmpe = (struct sxd_emad_pmpe_reg *)comp_info->skb->data;
    struct sx_emad              *emad_header = &pmpe->emad_header;
    int                          reg_id = be16_to_cpu(emad_header->emad_op.register_id);
    uint8_t                      slot_id = 0;
    uint8_t                      module_id = 0;
    unsigned short               type_len, ethertype;
    enum sx_module_present_state present = SX_MODULE_PRESENT_INVALID;
    struct sx_priv              *priv = sx_priv(comp_info->dev);
    pmpe_dwdata_t               *dwdata_p;

    type_len = ntohs(pmpe->tlv_header.type_len);
    ethertype = ntohs(pmpe->emad_header.eth_hdr.ethertype);

    if ((ethertype != ETHTYPE_EMAD) || (reg_id != MLXSW_PMPE_ID) ||
        ((type_len >> EMAD_TLV_TYPE_SHIFT) != TLV_TYPE_REG_E) ||
        ((type_len & 0x7FF) != 4)) {
        printk(KERN_INFO PFX "%s: Called wrongly with ethtype = %04X and reg-id = %04X, type = %d, len = %d\n",
               __func__, comp_info->info.eth.ethtype, reg_id,
               type_len >> EMAD_TLV_TYPE_SHIFT, type_len & 0x7FF);
        return;
    }

    slot_id = pmpe->slot_index;
    module_id = pmpe->module;

    present = (PMPE_MODULE_PLUGGED(pmpe->module_status)) ? SX_MODULE_PRESENT_PLUGGED : SX_MODULE_PRESENT_UNPLUGGED;

    if (present != priv->module_data[slot_id][module_id].present) {
        priv->module_data[slot_id][module_id].present = present;
        dwdata_p = kzalloc(sizeof(*dwdata_p), GFP_ATOMIC);
        if (!dwdata_p) {
            printk(KERN_ERR "PMPE handler failed to allocated memory\n");
            return;
        }
        dwdata_p->module = priv->module_sysfs_arr[module_id].module;
        INIT_DELAYED_WORK(&dwdata_p->dwork, __sx_pmpe_dwork_handler);
        /* The delayed queueing used to change context */
        queue_delayed_work(sx_glb.generic_wq, &dwdata_p->dwork, 0);
    }
}

int sx_module_sysfs_register_module_event_handler(struct sx_dev *dev)
{
    int                       err = 0;
    union ku_filter_critireas crit;

    err = sx_core_add_synd(0, SXD_TRAP_ID_PMPE, L2_TYPE_DONT_CARE, 0, "sx_core", 0,
                           &crit, __sx_handle_pmpe_event, NULL,
                           CHECK_DUP_ENABLED_E, dev, NULL, 1);
    if (err) {
        printk(KERN_ERR PFX "%s: Failed registering PMPE event rx_handler", __func__);
        return err;
    }

    return err;
}

int sx_module_sysfs_unregister_module_event_handler(struct sx_dev *dev)
{
    int                       err = 0;
    union ku_filter_critireas crit;

    err = sx_core_remove_synd(0, SXD_TRAP_ID_PMPE, L2_TYPE_DONT_CARE, 0,
                              &crit, NULL,
                              dev, NULL, NULL, 1, NULL);
    if (err) {
        printk(KERN_ERR PFX "%s: Failed unregistering PMPE event rx_handler", __func__);
        return err;
    }

    return err;
}
