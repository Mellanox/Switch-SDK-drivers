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
#define PORT_IS_PRESENT(pmaos_oper_status)                             \
    ((pmaos_oper_status == SXD_PMAOS_OPER_STATUS_INITIALIZING_E) ||    \
     (pmaos_oper_status == SXD_PMAOS_OPER_STATUS_PLUGGED_ENABLED_E) || \
     (pmaos_oper_status == SXD_PMAOS_OPER_STATUS_PLUGGED_DISABLED_E))

#define PORT_IS_PRESENT_ERROR(pmaos_oper_status) \
    (pmaos_oper_status == SXD_PMAOS_OPER_STATUS_MODULE_PLUGGED_WITH_ERROR_E)


#define OP_NOT_SUPPORTED "Operation not supported"

#define MCION_STATUS_MASK_HW_PRESENT    (0x1)
#define MCION_STATUS_MASK_INTERRUPT     (0x80)
#define MCION_STATUS_MASK_POWER_GOOD    (0x200)
#define MCION_INPUT_BITS_MASK_LOW_POWER (0xD)
#define MCION_INPUT_BITS_MASK_HW_RESET  (0xE)
#define MCION_INPUT_BITS_MASK_POWER_ON  (0xB)

#define SXD_MFCS_FREQ_MIN (0)
#define SXD_MFCS_FREQ_MAX (2)
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
static ssize_t show_module_status(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t show_module_error_type(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t show_module_pddr_info(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t show_module_latched_flag_pddr_info(struct kobject *kobj, struct kobj_attribute *attr, char *buf);

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
static struct kobj_attribute module_info_attr = __ATTR(module_info, S_IRUGO, show_module_pddr_info, NULL);
static struct kobj_attribute module_latched_flag_attr = __ATTR(module_latched_flag_info,
                                                               S_IRUGO,
                                                               show_module_latched_flag_pddr_info,
                                                               NULL);
static struct kobj_attribute module_power_mode_attr = __ATTR(power_mode, S_IRUGO, show_module_power_mode, NULL);
static struct kobj_attribute module_temp_input_attr = __ATTR(input, S_IRUGO, show_module_temp_input, NULL);
static struct kobj_attribute module_temp_label_attr = __ATTR(label, S_IRUGO, show_module_temp_label, NULL);
static struct kobj_attribute module_status_attr = __ATTR(status, S_IRUGO, show_module_status, NULL);
static struct kobj_attribute module_error_type_attr = __ATTR(statuserror, S_IRUGO, show_module_error_type, NULL);

/* Independent module - begin */
static ssize_t show_module_control(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t store_module_control(struct kobject        *kobj,
                                    struct kobj_attribute *attr,
                                    const char            *buf,
                                    size_t                 len);

static struct kobj_attribute module_control_attr = __ATTR(control,
                                                          (S_IRUGO | S_IWUSR),
                                                          show_module_control,
                                                          store_module_control);

static ssize_t show_module_hw_reset(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t store_module_hw_reset(struct kobject        *kobj,
                                     struct kobj_attribute *attr,
                                     const char            *buf,
                                     size_t                 len);
static struct kobj_attribute module_hw_reset_attr = __ATTR(hw_reset,
                                                           (S_IRUGO | S_IWUSR),
                                                           show_module_hw_reset,
                                                           store_module_hw_reset);
static ssize_t show_module_low_power_mode(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t store_module_low_power_mode(struct kobject        *kobj,
                                           struct kobj_attribute *attr,
                                           const char            *buf,
                                           size_t                 len);
static struct kobj_attribute module_low_power_mode_attr = __ATTR(low_power_mode,
                                                                 (S_IRUGO | S_IWUSR),
                                                                 show_module_low_power_mode,
                                                                 store_module_low_power_mode);
static ssize_t show_module_hw_present(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static struct kobj_attribute module_hw_present_attr = __ATTR(hw_present,
                                                             (S_IRUGO),
                                                             show_module_hw_present,
                                                             NULL);
static ssize_t show_module_interrupt(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static struct kobj_attribute module_interrupt_attr = __ATTR(interrupt,
                                                            (S_IRUGO),
                                                            show_module_interrupt,
                                                            NULL);
static ssize_t show_module_power_good(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static struct kobj_attribute module_power_good_attr = __ATTR(power_good,
                                                             (S_IRUGO),
                                                             show_module_power_good,
                                                             NULL);

static ssize_t store_module_reinsert(struct kobject        *kobj,
                                     struct kobj_attribute *attr,
                                     const char            *buf,
                                     size_t                 len);
static struct kobj_attribute module_reinsert_attr = __ATTR(reinsert,
                                                           S_IWUSR,
                                                           NULL,
                                                           store_module_reinsert);

static ssize_t show_module_power_limit(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static struct kobj_attribute module_power_limit_attr = __ATTR(power_limit,
                                                              S_IRUGO,
                                                              show_module_power_limit,
                                                              NULL);


static ssize_t show_module_frequency(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t store_module_frequency(struct kobject        *kobj,
                                      struct kobj_attribute *attr,
                                      const char            *buf,
                                      size_t                 len);
static struct kobj_attribute module_frequency_attr = __ATTR(frequency,
                                                            S_IRUGO | S_IWUSR,
                                                            show_module_frequency,
                                                            store_module_frequency);

static ssize_t show_module_frequency_support(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static struct kobj_attribute module_frequency_support_attr = __ATTR(frequency_support,
                                                                    S_IRUGO,
                                                                    show_module_frequency_support,
                                                                    NULL);

/* Independent module - end */

#define VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size)            \
    do {                                                                  \
        if ((snp_res == 0) || (snp_res >= buffer_length - buffer_size)) { \
            return 0;                                                     \
        }                                                                 \
    } while (0)

int sx_core_get_module_power_on(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool *power_on_p)
{
    int                        err = 0;
    struct ku_access_pmaos_reg pmaos_reg_data;
    struct ku_access_mcion_reg mcion_reg_data;
    bool                       is_independent = false;

    *power_on_p = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }

    if (is_independent) {
        memset(&mcion_reg_data, 0, sizeof(mcion_reg_data));
        mcion_reg_data.dev_id = dev->device_id;
        sx_cmd_set_op_tlv(&mcion_reg_data.op_tlv, MLXSW_MCION_ID, EMAD_METHOD_QUERY);

        mcion_reg_data.mcion_reg.slot_index = slot_id;
        mcion_reg_data.mcion_reg.module = module_id;

        err = sx_ACCESS_REG_MCION(dev, &mcion_reg_data);
        if (err) {
            printk(KERN_ERR PFX "Failed to access MCION, err=%d\n", err);
            goto out;
        }

        if (mcion_reg_data.op_tlv.status) {
            err = -EINVAL;
            printk(KERN_ERR PFX "Failed to access MCION, status=%d\n", mcion_reg_data.op_tlv.status);
            goto out;
        }

        *power_on_p = (mcion_reg_data.mcion_reg.module_inputs >> 2) & 0x1;
    } else {
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

        if (pmaos_reg_data.pmaos_reg.admin_status != SXD_PMAOS_ADMIN_STATUS_DISABLED_BY_CONFIGURATION_E) {
            *power_on_p = true;
        }
    }

out:
    return err;
}

int sx_core_get_module_status(struct sx_dev                  *dev,
                              uint8_t                         slot_id,
                              uint8_t                         module_id,
                              struct sx_module_status_params *params)
{
    int                       err = 0;
    struct ku_access_pmpe_reg pmpe_reg_data;
    bool                      is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent) {
        params->status = SXD_PMPE_MODULE_STATUS_UNKNOWN_E;
        params->error_type = SXD_PMPE_ERROR_TYPE_MIN;
        goto out;
    }

    memset(&pmpe_reg_data, 0, sizeof(pmpe_reg_data));
    pmpe_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&pmpe_reg_data.op_tlv, MLXSW_PMPE_ID, EMAD_METHOD_QUERY);

    pmpe_reg_data.pmpe_reg.slot_index = slot_id;
    pmpe_reg_data.pmpe_reg.module = module_id;

    err = sx_ACCESS_REG_PMPE(dev, &pmpe_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access PMPE, err=%d\n", err);
        goto out;
    }

    if (pmpe_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access PMPE, status=%d\n", pmpe_reg_data.op_tlv.status);
        goto out;
    }

    params->status = pmpe_reg_data.pmpe_reg.module_status;
    params->error_type = pmpe_reg_data.pmpe_reg.error_type;

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

int sx_core_get_port_module_status(struct sx_dev *dev, uint16_t local_port, struct sx_module_status_params *params)
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

    err = sx_core_get_module_status(dev, slot_id, module_id, params);
out:
    return err;
}
EXPORT_SYMBOL(sx_core_get_port_module_status);

int sx_core_power_on_independent_module(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool power_on)
{
    int                        err = 0;
    struct ku_access_mcion_reg mcion_reg_data;

    memset(&mcion_reg_data, 0, sizeof(mcion_reg_data));
    mcion_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mcion_reg_data.op_tlv, MLXSW_MCION_ID, EMAD_METHOD_WRITE);

    mcion_reg_data.mcion_reg.slot_index = slot_id;
    mcion_reg_data.mcion_reg.module = module_id;
    mcion_reg_data.mcion_reg.module_inputs_mask = MCION_INPUT_BITS_MASK_POWER_ON;
    mcion_reg_data.mcion_reg.module_inputs = (power_on << 2);

    err = sx_ACCESS_REG_MCION(dev, &mcion_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to access MCION, err=%d\n", err);
        goto out;
    }

    if (mcion_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to access MCION, status=%d\n", mcion_reg_data.op_tlv.status);
        goto out;
    }

out:
    return err;
}

static bool __module_any_port_up_get(struct sx_priv *priv, uint8_t slot_id, uint8_t module_id)
{
    int      i = 0;
    uint16_t local_port = 0;
    bool     any_port_up = false;

    for (i = 0; i < priv->modules_to_port_map_count[slot_id][module_id]; i++) {
        local_port = priv->module_to_ports_map[slot_id][module_id][i];
        if ((priv->local_port_state[local_port] == SXD_PAOS_ADMIN_STATUS_UP_E) ||
            (priv->local_port_state[local_port] == SXD_PAOS_ADMIN_STATUS_UP_ONCE_E)) {
            any_port_up = true;
            break;
        }
    }

    return any_port_up;
}

int sx_core_power_on_off_module(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool power_on)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    unsigned long   flags;
    bool            any_port_up = false;
    bool            is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }

    spin_lock_irqsave(&priv->db_lock, flags);
    if (!power_on) {
        any_port_up = __module_any_port_up_get(priv, slot_id, module_id);
        if (any_port_up) {
            spin_unlock_irqrestore(&priv->db_lock, flags);
            err = -EACCES;
            goto out;
        }
    }
    spin_unlock_irqrestore(&priv->db_lock, flags);

    mutex_lock(&priv->module_access_mutex);
    /*No mutex should be added inside internal functions */
    if (is_independent) {
        err = sx_core_power_on_independent_module(dev, slot_id, module_id, power_on);
    } else {
        err = sx_core_set_module(dev, slot_id, module_id, power_on, 0);
    }
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

int sx_core_get_port_module_independent(struct sx_dev *dev, uint16_t local_port, bool *is_independent_p)
{
    int           err = 0;
    uint8_t       slot_id = 0;
    uint8_t       module_id = 0;
    unsigned long flags;

    *is_independent_p = false;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    err = sx_core_get_module_by_port(dev, local_port, &slot_id, &module_id);
    if (err) {
        spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    err = sx_core_get_module_control(dev, slot_id, module_id, is_independent_p);
    if (err) {
        spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
        goto out;
    }

out:
    return err;
}
EXPORT_SYMBOL(sx_core_get_port_module_independent);

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
    uint8_t                   slot_id = 0;
    uint8_t                   module_id = 0;
    unsigned long             flags;
    bool                      is_independent = false;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    err = sx_core_get_module_by_port(dev, local_port, &slot_id, &module_id);
    if (err) {
        spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent) {
        printk(KERN_ERR PFX "%s: Failed to read tx_disable: port module is independent (SW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

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
    uint8_t                   slot_id = 0;
    uint8_t                   module_id = 0;
    unsigned long             flags;
    bool                      is_independent = false;

    spin_lock_irqsave(&priv->db_lock, flags);
    err = sx_core_get_module_by_port(dev, local_port, &slot_id, &module_id);
    if (err) {
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&priv->db_lock, flags);

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }

    if (is_independent) {
        printk(KERN_ERR PFX "%s: Failed to write tx_disable: port module is independent (SW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

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

int sx_core_get_module_present(struct sx_dev                     *dev,
                               uint8_t                            slot_id,
                               uint8_t                            module_id,
                               enum sx_oper_module_present_state *present)
{
    int                        err = 0;
    struct ku_access_pmaos_reg pmaos_reg_data;
    bool                       is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent) {
        *present = SX_OPER_MODULE_NOT_PRESENT;
        goto out;
    }

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

    *present = SX_OPER_MODULE_NOT_PRESENT;
    if (PORT_IS_PRESENT(pmaos_reg_data.pmaos_reg.oper_status)) {
        *present = SX_OPER_MODULE_PRESENT;
    } else if (PORT_IS_PRESENT_ERROR(pmaos_reg_data.pmaos_reg.oper_status)) {
        *present = SX_OPER_MODULE_PRESENT_ERROR;
    }

out:
    return err;
}

int sx_core_get_port_module_present(struct sx_dev *dev, uint16_t local_port,
                                    enum sx_oper_module_present_state *present)
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
    int                               ret = 0;
    enum sx_oper_module_present_state present = SX_OPER_MODULE_NOT_PRESENT;
    int                               len = 0;
    int                               val = 0;
    struct sx_dev                    *dev = NULL;
    uint8_t                           slot_id = 0;
    uint8_t                           module_id = 0;

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

    if (present == SX_OPER_MODULE_PRESENT) {
        val = 1;
    } else if (present == SX_OPER_MODULE_PRESENT_ERROR) {
        val = 2;
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
    uint8_t                   slot_id = 0;
    uint8_t                   module_id = 0;
    unsigned long             flags;
    bool                      is_independent = false;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    err = sx_core_get_module_by_port(dev, local_port, &slot_id, &module_id);
    if (err) {
        spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent) {
        printk(KERN_ERR PFX "%s: Failed to read rx_los: port module is independent (SW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

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

static int _access_reg_pddr_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_pddr_reg * reg_data)
{
    int      buffer_size = 0, snp_res = 0;
    uint16_t local_port = 0;
    int      i = 0;
    char     str_buf[32];

    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->local_port, reg_data->lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
    buffer += snp_res;
    buffer_size += snp_res;

    switch (reg_data->page_select) {
    case SXD_PDDR_PAGE_SELECT_OPERATIONAL_INFO_PAGE_E:
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "proto_active: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.proto_active);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "neg_mode_active: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.neg_mode_active);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "pd_fsm_state: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.pd_fsm_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phy_mngr_fsm_state: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.phy_mngr_fsm_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "eth_an_fsm_state: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.eth_an_fsm_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ib_phy_fsm_state: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.ib_phy_fsm_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phy_hst_fsm_state: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.phy_hst_fsm_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phy_manager_link_width_enabled: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.phy_manager_link_enabled.pddr_phy_manager_link_enabed_ib.phy_manager_link_width_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phy_manager_link_proto_enabled: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.phy_manager_link_enabled.pddr_phy_manager_link_enabed_ib.phy_manager_link_proto_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phy_manager_link_eth_enabled: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.phy_manager_link_enabled.pddr_phy_manager_link_enabed_eth.phy_manager_link_eth_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "core_to_phy_link_width_enabled: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.core_to_phy_link_enabled.pddr_c2p_link_enabed_ib.core_to_phy_link_width_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "core_to_phy_link_proto_enabled: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.core_to_phy_link_enabled.pddr_c2p_link_enabed_ib.core_to_phy_link_proto_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "core_to_phy_link_eth_enabled: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.core_to_phy_link_enabled.pddr_c2p_link_enabed_eth.core_to_phy_link_eth_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_link_width_cap: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.cable_proto_cap.pddr_cable_cap_ib.cable_link_width_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_link_speed_cap: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.cable_proto_cap.pddr_cable_cap_ib.cable_link_speed_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_ext_eth_proto_cap: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.cable_proto_cap.pddr_cable_cap_eth.cable_ext_eth_proto_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        switch (reg_data->page_data.pddr_operation_info_page.proto_active) {
        case SXD_PDDR_PROTO_ACTIVE_INFINIBAND_E:
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "link_width_active: 0x%x\n",
                               reg_data->page_data.pddr_operation_info_page.link_active.pddr_link_active_ib.link_width_active);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "link_speed_active: 0x%x\n",
                               reg_data->page_data.pddr_operation_info_page.link_active.pddr_link_active_ib.link_speed_active);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            break;

        case SXD_PDDR_PROTO_ACTIVE_ETHERNET_E:
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "link_eth_active: 0x%x\n",
                               reg_data->page_data.pddr_operation_info_page.link_active.pddr_link_active_eth.link_eth_active);
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
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "retran_mode_active: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.retran_mode_active);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "retran_mode_request: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.retran_mode_request);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "loopback_mode: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.loopback_mode);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "fec_mode_active: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.fec_mode_active);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "fec_mode_request: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.fec_mode_request);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "profile_fec_in_use: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.profile_fec_in_use);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "nlpn_fsm_state: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.nlpn_fsm_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "eth_25g_50g_fec_support: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.eth_25g_50g_fec_support);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "eth_100g_fec_support: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.eth_100g_fec_support);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "pd_link_enabled: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.pd_link_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "phy_hst_link_enabled: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.phy_hst_link_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "eth_an_link_enabled: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.eth_an_link_enabled);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "linkup_retry_iterations: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.linkup_retry_iterations);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "core_to_phy_state: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.core_to_phy_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "psi_fsm_state: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.psi_fsm_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_proto_cap_ext: 0x%x\n",
                           reg_data->page_data.pddr_operation_info_page.cable_proto_cap_ext);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_TROUBLESHOOTING_INFO_PAGE_E:
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "group_opcode: 0x%x\n",
                           reg_data->page_data.pddr_troubleshooting_page.group_opcode);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        switch (reg_data->page_data.pddr_troubleshooting_page.group_opcode) {
        case SXD_PDDR_GROUP_OPCODE_MONITOR_OPCODES_E:
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "monitor_opcode: 0x%x\n",
                               reg_data->page_data.pddr_troubleshooting_page.status_opcode.pddr_monitor_opcode.monitor_opcode);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            break;

        case SXD_PDDR_GROUP_OPCODE_ADVANCED_DEBUG_OPCODES_E:
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "advanced_opcode: 0x%x\n",
                               reg_data->page_data.pddr_troubleshooting_page.status_opcode.pddr_advanced_opcode.advanced_opcode);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
            break;

        default:
            /* Other types not supported yet */
            break;
        }
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "user_feedback_data: 0x%x\n",
                           reg_data->page_data.pddr_troubleshooting_page.user_feedback_data);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "user_feedback_index: 0x%x\n",
                           reg_data->page_data.pddr_troubleshooting_page.user_feedback_index);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;

        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "status_message: 0x");
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;

        for (i = 0; i < SXD_PDDR_STATUS_MESSAGE_NUM; i++) {
            snp_res = snprintf(buffer,
                               buffer_length - buffer_size,
                               "%02x",
                               reg_data->page_data.pddr_troubleshooting_page.status_message[i]);
            VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
            buffer += snp_res;
            buffer_size += snp_res;
        }

        snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_MODULE_INFO_PAGE_E:
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_technology: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_technology);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_breakout: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_breakout);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ext_ethernet_compliance_code: 0x%x\n",
                           reg_data->page_data.pddr_module_info.ext_ethernet_compliance_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ethernet_compliance_code: 0x%x\n",
                           reg_data->page_data.pddr_module_info.ethernet_compliance_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_type: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_type);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_vendor: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_vendor);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_length: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_length);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_identifier: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_identifier);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_power_class: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_power_class);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "max_power: 0x%x\n",
                           reg_data->page_data.pddr_module_info.max_power);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_rx_amp: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_rx_amp);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_rx_emphasis: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_rx_emphasis);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_tx_equalization: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_tx_equalization);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_attenuation_25g: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_attenuation_25g);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_attenuation_12g: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_attenuation_12g);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_attenuation_7g: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_attenuation_7g);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_attenuation_5g: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_attenuation_5g);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "cable_rx_post_emphasis: 0x%x\n",
                           reg_data->page_data.pddr_module_info.cable_rx_post_emphasis);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_cdr_cap: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_cdr_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_cdr_cap: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_cdr_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_cdr_state: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_cdr_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_cdr_state: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_cdr_state);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;

        memset(str_buf, 0, sizeof(str_buf));
        snprintf(str_buf, SXD_PDDR_VENDOR_NAME_NUM, "%s", reg_data->page_data.pddr_module_info.vendor_name);
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vendor_name: %s\n", str_buf);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;

        memset(str_buf, 0, sizeof(str_buf));
        snprintf(str_buf, SXD_PDDR_VENDOR_PN_NUM, "%s", reg_data->page_data.pddr_module_info.vendor_pn);
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vendor_pn: %s\n", str_buf);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "vendor_rev: 0x%x\n",
                           reg_data->page_data.pddr_module_info.vendor_rev);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "fw_version: 0x%x\n",
                           reg_data->page_data.pddr_module_info.fw_version);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;

        memset(str_buf, 0, sizeof(str_buf));
        snprintf(str_buf, SXD_PDDR_VENDOR_SN_NUM, "%s", reg_data->page_data.pddr_module_info.vendor_sn);
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vendor_sn: %s\n", str_buf);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "temperature: 0x%x\n",
                           reg_data->page_data.pddr_module_info.temperature);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "voltage: 0x%x\n",
                           reg_data->page_data.pddr_module_info.voltage);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_lane0: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_power_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_lane1: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_power_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_lane2: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_power_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_lane3: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_power_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_lane4: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_power_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_lane5: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_power_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_lane6: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_power_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_lane7: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_power_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_power_lane0: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_power_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_power_lane1: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_power_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_power_lane2: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_power_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_power_lane3: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_power_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_power_lane4: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_power_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_power_lane5: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_power_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_power_lane6: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_power_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_power_lane7: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_power_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_bias_lane0: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_bias_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_bias_lane1: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_bias_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_bias_lane2: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_bias_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_bias_lane3: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_bias_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_bias_lane4: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_bias_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_bias_lane5: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_bias_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_bias_lane6: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_bias_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_bias_lane7: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_bias_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "temperature_high_th: 0x%x\n",
                           reg_data->page_data.pddr_module_info.temperature_high_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "temperature_low_th: 0x%x\n",
                           reg_data->page_data.pddr_module_info.temperature_low_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "voltage_high_th: 0x%x\n",
                           reg_data->page_data.pddr_module_info.voltage_high_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "voltage_low_th: 0x%x\n",
                           reg_data->page_data.pddr_module_info.voltage_low_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_high_th: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_power_high_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_low_th: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_power_low_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_power_high_th: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_power_high_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_power_low_th: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_power_low_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_bias_high_th: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_bias_high_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_bias_low_th: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_bias_low_th);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "module_st: 0x%x\n",
                           reg_data->page_data.pddr_module_info.module_st);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_type: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_power_type);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "did_cap: 0x%x\n",
                           reg_data->page_data.pddr_module_info.did_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_output_valid_cap: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_output_valid_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "smf_length: 0x%x\n",
                           reg_data->page_data.pddr_module_info.smf_length);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "wavelength: 0x%x\n",
                           reg_data->page_data.pddr_module_info.wavelength);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "active_set_host_compliance_code: 0x%x\n",
                           reg_data->page_data.pddr_module_info.active_set_host_compliance_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "active_set_media_compliance_code: 0x%x\n",
                           reg_data->page_data.pddr_module_info.active_set_media_compliance_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ib_compliance_code: 0x%x\n",
                           reg_data->page_data.pddr_module_info.ib_compliance_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "nbr250: 0x%x\n",
                           reg_data->page_data.pddr_module_info.nbr250);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "nbr100: 0x%x\n",
                           reg_data->page_data.pddr_module_info.nbr100);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "monitor_cap_mask: 0x%x\n",
                           reg_data->page_data.pddr_module_info.monitor_cap_mask);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "ib_width: 0x%x\n",
                           reg_data->page_data.pddr_module_info.ib_width);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dp_st_lane0: 0x%x\n",
                           reg_data->page_data.pddr_module_info.dp_st_lane0);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dp_st_lane1: 0x%x\n",
                           reg_data->page_data.pddr_module_info.dp_st_lane1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dp_st_lane2: 0x%x\n",
                           reg_data->page_data.pddr_module_info.dp_st_lane2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dp_st_lane3: 0x%x\n",
                           reg_data->page_data.pddr_module_info.dp_st_lane3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dp_st_lane4: 0x%x\n",
                           reg_data->page_data.pddr_module_info.dp_st_lane4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dp_st_lane5: 0x%x\n",
                           reg_data->page_data.pddr_module_info.dp_st_lane5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dp_st_lane6: 0x%x\n",
                           reg_data->page_data.pddr_module_info.dp_st_lane6);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dp_st_lane7: 0x%x\n",
                           reg_data->page_data.pddr_module_info.dp_st_lane7);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "length_om2: 0x%x\n",
                           reg_data->page_data.pddr_module_info.length_om2);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "length_om3: 0x%x\n",
                           reg_data->page_data.pddr_module_info.length_om3);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "length_om4: 0x%x\n",
                           reg_data->page_data.pddr_module_info.length_om4);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "length_om5: 0x%x\n",
                           reg_data->page_data.pddr_module_info.length_om5);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "length_om1: 0x%x\n",
                           reg_data->page_data.pddr_module_info.length_om1);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "wavelength_tolerance: 0x%x\n",
                           reg_data->page_data.pddr_module_info.wavelength_tolerance);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "memory_map_rev: 0x%x\n",
                           reg_data->page_data.pddr_module_info.memory_map_rev);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "memory_map_compliance: 0x%x\n",
                           reg_data->page_data.pddr_module_info.memory_map_compliance);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "date_code: 0x%llx\n",
                           reg_data->page_data.pddr_module_info.date_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "connector_type: 0x%x\n",
                           reg_data->page_data.pddr_module_info.connector_type);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "vendor_oui: 0x%x\n",
                           reg_data->page_data.pddr_module_info.vendor_oui);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_input_freq_sync: 0x%x\n",
                           reg_data->page_data.pddr_module_info.tx_input_freq_sync);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_output_valid: 0x%x\n",
                           reg_data->page_data.pddr_module_info.rx_output_valid);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "max_fiber_length: 0x%x\n",
                           reg_data->page_data.pddr_module_info.max_fiber_length);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "error_code: 0x%x\n",
                           reg_data->page_data.pddr_module_info.error_code);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_MODULE_LATCHED_FLAG_INFO_PAGE_E:
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "temp_flags: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.temp_flags);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "vcc_flags: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.vcc_flags);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "mod_fw_fault: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.mod_fw_fault);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "dp_fw_fault: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.dp_fw_fault);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_los_cap: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.rx_los_cap);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_fault: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.tx_fault);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_los: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.tx_los);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_cdr_lol: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.tx_cdr_lol);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_ad_eq_fault: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.tx_ad_eq_fault);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_power_hi_al: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.tx_power_hi_al);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_power_lo_al: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.tx_power_lo_al);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_power_hi_war: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.tx_power_hi_war);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_power_lo_war: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.tx_power_lo_war);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_bias_hi_al: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.tx_bias_hi_al);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_bias_lo_al: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.tx_bias_lo_al);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_bias_hi_war: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.tx_bias_hi_war);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "tx_bias_lo_war: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.tx_bias_lo_war);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_los: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.rx_los);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_cdr_lol: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.rx_cdr_lol);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_hi_al: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.rx_power_hi_al);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_lo_al: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.rx_power_lo_al);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_hi_war: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.rx_power_hi_war);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_power_lo_war: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.rx_power_lo_war);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "rx_output_valid_change: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.rx_output_valid_change);
        VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer,
                           buffer_length - buffer_size,
                           "flag_in_use: 0x%x\n",
                           reg_data->page_data.module_latched_flag_info.flag_in_use);
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

static ssize_t _get_pddr(struct sx_dev *dev, u16 local_port, char *buf, sxd_pddr_page_select_t page)
{
    struct ku_access_pddr_reg reg_data;
    int                       err = 0;

    memset(&reg_data, 0, sizeof(reg_data));

    reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, PDDR_REG_ID, EMAD_METHOD_QUERY);

    reg_data.pddr_reg.page_select = page;
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

    return _access_reg_pddr_data_to_buffer_print(buf, (PAGE_SIZE - 1), &reg_data.pddr_reg);

out:
    return err;
}
static ssize_t show_module_latched_flag_pddr_info(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int            ret = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;
    int            len = 0;
    uint16_t       local_ports[MAX_LANE_NUM_PER_MODULE];
    uint16_t       sysports[MAX_LANE_NUM_PER_MODULE];
    uint8_t        ports_cnt = 0;

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of module info sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n", __func__, ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_ports_by_module(dev, slot_id, module_id, local_ports, sysports, &ports_cnt);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_get_ports_by_module failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    if (ports_cnt > 0) {
        return _get_pddr(dev, local_ports[0], buf, SXD_PDDR_PAGE_SELECT_MODULE_LATCHED_FLAG_INFO_PAGE_E);
    } else {
        len = sprintf(buf, "%s", OP_NOT_SUPPORTED);
        printk(KERN_NOTICE PFX "%s: %s for %s.\n", __func__, OP_NOT_SUPPORTED, kobject_name(kobj));
        return -EOPNOTSUPP;
    }

out:
    return ret;
}
static ssize_t show_module_pddr_info(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int            ret = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;
    int            len = 0;
    uint16_t       local_ports[MAX_LANE_NUM_PER_MODULE];
    uint16_t       sysports[MAX_LANE_NUM_PER_MODULE];
    uint8_t        ports_cnt = 0;

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of module info sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n", __func__, ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_ports_by_module(dev, slot_id, module_id, local_ports, sysports, &ports_cnt);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_get_ports_by_module failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    if (ports_cnt > 0) {
        return _get_pddr(dev, local_ports[0], buf, SXD_PDDR_PAGE_SELECT_MODULE_INFO_PAGE_E);
    } else {
        len = sprintf(buf, "%s", OP_NOT_SUPPORTED);
        printk(KERN_NOTICE PFX "%s: %s for %s.\n", __func__, OP_NOT_SUPPORTED, kobject_name(kobj));
        return -EOPNOTSUPP;
    }

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
        if (ret != -ENODEV) {
            printk(KERN_ERR PFX "Failed to get module temperature information\n");
        }
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
        if (ret != -ENODEV) {
            printk(KERN_ERR PFX "Failed to get module temperature information\n");
        }
        return ret;
    }

    len = sprintf(buf, "%s\n", params.label);

    return len;
}

static ssize_t show_module_status(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                            ret = 0;
    int                            len = 0;
    struct sx_dev                 *dev = NULL;
    uint8_t                        slot_id = 0;
    uint8_t                        module_id = 0;
    struct sx_module_status_params params;

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "show_module_status: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_module_status(dev, slot_id, module_id, &params);
    if (ret) {
        printk(KERN_ERR PFX "show_module_status: sx_core_get_module_status failed (%d) for %s\n",
               ret,
               kobject_name(kobj));
        goto out;
    }

    len = sprintf(buf, "%d\n", params.status);

    return len;

out:
    return ret;
}

static ssize_t show_module_error_type(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int                            ret = 0;
    int                            len = 0;
    struct sx_dev                 *dev = NULL;
    uint8_t                        slot_id = 0;
    uint8_t                        module_id = 0;
    struct sx_module_status_params params;

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "show_module_error_type: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_module_status(dev, slot_id, module_id, &params);
    if (ret) {
        printk(KERN_ERR PFX "show_module_error_type: sx_core_get_module_status failed (%d) for %s\n",
               ret,
               kobject_name(kobj));
        goto out;
    }

    len = sprintf(buf, "%d\n", params.error_type);

    return len;

out:
    return ret;
}

int sx_core_create_module_sysfs_extension_for_indmod(struct kobject *parent)
{
    int err = 0;

    err = sysfs_create_file(parent, &(module_control_attr.attr));
    if (err) {
        goto out;
    }

    err = sysfs_create_file(parent, &(module_hw_reset_attr.attr));
    if (err) {
        goto phase1_err;
    }

    err = sysfs_create_file(parent, &(module_low_power_mode_attr.attr));
    if (err) {
        goto phase2_err;
    }

    err = sysfs_create_file(parent, &(module_hw_present_attr.attr));
    if (err) {
        goto phase3_err;
    }

    err = sysfs_create_file(parent, &(module_interrupt_attr.attr));
    if (err) {
        goto phase4_err;
    }

    err = sysfs_create_file(parent, &(module_power_good_attr.attr));
    if (err) {
        goto phase5_err;
    }

    err = sysfs_create_file(parent, &(module_reinsert_attr.attr));
    if (err) {
        goto phase6_err;
    }

    err = sysfs_create_file(parent, &(module_power_limit_attr.attr));
    if (err) {
        goto phase7_err;
    }

    err = sysfs_create_file(parent, &(module_frequency_attr.attr));
    if (err) {
        goto phase8_err;
    }

    err = sysfs_create_file(parent, &(module_frequency_support_attr.attr));
    if (err) {
        goto phase9_err;
    }

    goto out;

phase9_err:
    sysfs_remove_file(parent, &(module_frequency_attr.attr));
phase8_err:
    sysfs_remove_file(parent, &(module_power_limit_attr.attr));
phase7_err:
    sysfs_remove_file(parent, &(module_reinsert_attr.attr));
phase6_err:
    sysfs_remove_file(parent, &(module_power_good_attr.attr));
phase5_err:
    sysfs_remove_file(parent, &(module_interrupt_attr.attr));
phase4_err:
    sysfs_remove_file(parent, &(module_hw_present_attr.attr));
phase3_err:
    sysfs_remove_file(parent, &(module_low_power_mode_attr.attr));
phase2_err:
    sysfs_remove_file(parent, &(module_hw_reset_attr.attr));
phase1_err:
    sysfs_remove_file(parent, &(module_control_attr.attr));
out:
    return err;
}
EXPORT_SYMBOL(sx_core_create_module_sysfs_extension_for_indmod);

void sx_core_delete_module_sysfs_extension_for_indmod(struct kobject *parent)
{
    sysfs_remove_file(parent, &(module_control_attr.attr));
    sysfs_remove_file(parent, &(module_hw_reset_attr.attr));
    sysfs_remove_file(parent, &(module_low_power_mode_attr.attr));
    sysfs_remove_file(parent, &(module_hw_present_attr.attr));
    sysfs_remove_file(parent, &(module_interrupt_attr.attr));
    sysfs_remove_file(parent, &(module_power_good_attr.attr));
    sysfs_remove_file(parent, &(module_reinsert_attr.attr));
    sysfs_remove_file(parent, &(module_power_limit_attr.attr));
    sysfs_remove_file(parent, &(module_frequency_attr.attr));
    sysfs_remove_file(parent, &(module_frequency_support_attr.attr));
}
EXPORT_SYMBOL(sx_core_delete_module_sysfs_extension_for_indmod);

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
    err = sysfs_create_file(parent, &(module_status_attr.attr));
    if (err) {
        goto phase4_err;
    }
    err = sysfs_create_file(parent, &(module_error_type_attr.attr));
    if (err) {
        goto phase5_err;
    }

    return err;

phase5_err:
    sysfs_remove_file(parent, &(module_status_attr.attr));
phase4_err:
    sysfs_remove_file(parent, &(module_rx_los_attr.attr));
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
    sysfs_remove_file(parent, &(module_status_attr.attr));
    sysfs_remove_file(parent, &(module_error_type_attr.attr));
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
    err = sysfs_create_file(module, &(module_info_attr.attr));
    if (err) {
        goto phase4_err;
    }
    err = sysfs_create_file(module, &(module_latched_flag_attr.attr));
    if (err) {
        goto phase5_err;
    }
    temperature = kobject_create_and_add("temperature", module);
    if (temperature == NULL) {
        err = -ENOMEM;
        goto phase6_err;
    }
    err = sysfs_create_file(temperature, &(module_temp_input_attr.attr));
    if (err) {
        err = -ENOMEM;
        goto phase7_err;
    }
    err = sysfs_create_file(temperature, &(module_temp_label_attr.attr));
    if (err) {
        err = -ENOMEM;
        goto phase8_err;
    }
    root->temperature = temperature;

    return err;

phase8_err:
    sysfs_remove_file(temperature, &(module_temp_input_attr.attr));
phase7_err:
    kobject_put(temperature);
phase6_err:
    sysfs_remove_file(module, &(module_latched_flag_attr.attr));
phase5_err:
    sysfs_remove_file(module, &(module_info_attr.attr));
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
    sysfs_remove_file(root->module, &(module_latched_flag_attr.attr));
    sysfs_remove_file(root->module, &(module_info_attr.attr));
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

    if (PMPE_MODULE_PLUGGED(pmpe->module_status)) {
        present = SX_MODULE_PRESENT_PLUGGED;
    } else if (PMPE_MODULE_PLUGGED_ERROR(pmpe->module_status)) {
        present = SX_MODULE_PRESENT_PLUGGED_ERROR;
    } else {
        present = SX_MODULE_PRESENT_UNPLUGGED;
    }


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

static void __sx_mcion_dwork_handler(struct work_struct *dwork_p)
{
    mcion_dwdata_t *dwdata_p = container_of(dwork_p, mcion_dwdata_t, dwork.work);


    if (dwdata_p->hw_present) {
        sysfs_notify(dwdata_p->module, NULL, "hw_present");
    }

    if (dwdata_p->interrupt) {
        sysfs_notify(dwdata_p->module, NULL, "interrupt");
    }

    if (dwdata_p->power_good) {
        sysfs_notify(dwdata_p->module, NULL, "power_good");
    }

    kfree(dwdata_p);
}

static void __sx_handle_mcion_event(struct completion_info *comp_info, void *context)
{
    struct sxd_emad_mcion_reg      *mcion = (struct sxd_emad_mcion_reg *)comp_info->skb->data;
    struct sx_emad                 *emad_header = &mcion->emad_header;
    int                             reg_id = be16_to_cpu(emad_header->emad_op.register_id);
    uint8_t                         slot_id = 0;
    uint8_t                         module_id = 0;
    unsigned short                  type_len, ethertype;
    enum sx_module_interrupt_state  interrupt;
    enum sx_module_hw_present_state hw_present;
    enum sx_module_power_good_state power_good;
    struct sx_priv                 *priv = sx_priv(comp_info->dev);
    mcion_dwdata_t                 *dwdata_p;
    bool                            send_notify = false;

    type_len = ntohs(mcion->tlv_header.type_len);
    ethertype = ntohs(mcion->emad_header.eth_hdr.ethertype);

    if ((ethertype != ETHTYPE_EMAD) || (reg_id != MLXSW_MCION_ID) ||
        ((type_len >> EMAD_TLV_TYPE_SHIFT) != TLV_TYPE_REG_E) ||
        ((type_len & 0x7FF) != 6)) {
        printk(KERN_INFO PFX "%s: Called wrongly with ethtype = %04X and reg-id = %04X, type = %d, len = %d\n",
               __func__, comp_info->info.eth.ethtype, reg_id,
               type_len >> EMAD_TLV_TYPE_SHIFT, type_len & 0x7FF);
        return;
    }

    dwdata_p = kzalloc(sizeof(*dwdata_p), GFP_ATOMIC);
    if (!dwdata_p) {
        printk(KERN_ERR "MCION handler failed to allocated memory\n");
        return;
    }

    slot_id = ((mcion->slot_index) >> 4) & 0x0F;
    module_id = mcion->module;


    if (!(ntohs(mcion->module_status_bits_valid) & MCION_STATUS_MASK_HW_PRESENT)) {
        if (ntohs(mcion->module_status_bits) & MCION_STATUS_MASK_HW_PRESENT) {
            hw_present = SX_MODULE_HW_PRESENT_ON;
        } else {
            hw_present = SX_MODULE_HW_PRESENT_OFF;
        }

        if (hw_present != priv->module_data[slot_id][module_id].independent_params.hw_present) {
            send_notify = true;
            dwdata_p->hw_present = true;
            priv->module_data[slot_id][module_id].independent_params.hw_present = hw_present;
        }
    }

    if (!(ntohs(mcion->module_status_bits_valid) & MCION_STATUS_MASK_INTERRUPT)) {
        if (ntohs(mcion->module_status_bits) & MCION_STATUS_MASK_INTERRUPT) {
            interrupt = SX_MODULE_INTERRUPT_ON;
        } else {
            interrupt = SX_MODULE_INTERRUPT_OFF;
        }
        if (interrupt != priv->module_data[slot_id][module_id].independent_params.interrupt) {
            send_notify = true;
            dwdata_p->interrupt = true;
            priv->module_data[slot_id][module_id].independent_params.interrupt = interrupt;
        }
    }

    if (!(ntohs(mcion->module_status_bits_valid) & MCION_STATUS_MASK_POWER_GOOD)) {
        if (ntohs(mcion->module_status_bits & MCION_STATUS_MASK_POWER_GOOD)) {
            power_good = SX_MODULE_POWER_GOOD_ON;
        } else {
            power_good = SX_MODULE_POWER_GOOD_OFF;
        }
        if (power_good != priv->module_data[slot_id][module_id].independent_params.power_good) {
            send_notify = true;
            dwdata_p->power_good = true;
            priv->module_data[slot_id][module_id].independent_params.power_good = power_good;
        }
    }

    if (send_notify) {
        dwdata_p->module = priv->module_sysfs_arr[module_id].module;
        INIT_DELAYED_WORK(&dwdata_p->dwork, __sx_mcion_dwork_handler);
        /* The delayed queueing used to change context */
        queue_delayed_work(sx_glb.generic_wq, &dwdata_p->dwork, 0);
    } else {
        kfree(dwdata_p);
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

    err = sx_core_add_synd(0, SXD_TRAP_ID_MCION, L2_TYPE_DONT_CARE, 0, "sx_core", 0,
                           &crit, __sx_handle_mcion_event, NULL,
                           CHECK_DUP_ENABLED_E, dev, NULL, 1);
    if (err) {
        printk(KERN_ERR PFX "%s: Failed registering MCION event rx_handler", __func__);
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

    err = sx_core_remove_synd(0, SXD_TRAP_ID_MCION, L2_TYPE_DONT_CARE, 0,
                              &crit, NULL,
                              dev, NULL, NULL, 1, NULL);
    if (err) {
        printk(KERN_ERR PFX "%s: Failed unregistering MCION event rx_handler", __func__);
        return err;
    }


    return err;
}

int sx_core_get_module_control(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool *is_independent_p)
{
    int                       err = 0;
    struct sx_priv           *priv = sx_priv(dev);
    struct ku_access_mmcr_reg mmcr_reg_data;
    bool                      is_independent = false;

    if (priv->independent_module_params.is_independent == true) {
        memset(&mmcr_reg_data, 0, sizeof(mmcr_reg_data));
        mmcr_reg_data.dev_id = dev->device_id;
        sx_cmd_set_op_tlv(&mmcr_reg_data.op_tlv, MLXSW_MMCR_ID, EMAD_METHOD_QUERY);

        err = sx_ACCESS_REG_MMCR(dev, &mmcr_reg_data);
        if (err) {
            printk(KERN_ERR PFX "Failed to query MMCR, err=%d\n", err);
            goto out;
        }

        if (mmcr_reg_data.op_tlv.status) {
            err = -EINVAL;
            printk(KERN_ERR PFX "Failed to query MMCR, status=%d\n", mmcr_reg_data.op_tlv.status);
            goto out;
        }

        /*
         * Get MMCR bit X for module ID X.
         */
        if (SX_CORE_BITMAP_GET(mmcr_reg_data.mmcr_reg.module_sw_control,
                               SXD_MMCR_MODULE_CONTROL_MASK_NUM,
                               sizeof(mmcr_reg_data.mmcr_reg.module_sw_control[0]) * 8,
                               module_id)) {
            is_independent = true;
        } else {
            is_independent = false;
        }
    }

out:
    *is_independent_p = is_independent;
    return err;
}
EXPORT_SYMBOL(sx_core_get_module_control);

static int __module_event_enable_set(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, sxd_pmaos_e_t gen_mode)
{
    int                        err = 0;
    struct sx_priv            *priv = sx_priv(dev);
    struct ku_access_pmaos_reg pmaos_reg_data;
    bool                       release_lock = false;

    mutex_lock(&priv->module_access_mutex);
    release_lock = true;

    memset(&pmaos_reg_data, 0, sizeof(pmaos_reg_data));
    pmaos_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&pmaos_reg_data.op_tlv, PMAOS_REG_ID, EMAD_METHOD_WRITE);

    pmaos_reg_data.pmaos_reg.slot_index = slot_id;
    pmaos_reg_data.pmaos_reg.module = module_id;
    pmaos_reg_data.pmaos_reg.ase = 0; /* Don't change admin state */
    pmaos_reg_data.pmaos_reg.ee = 1;
    pmaos_reg_data.pmaos_reg.e = gen_mode;

    err = sx_ACCESS_REG_PMAOS(dev, &pmaos_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to write PMAOS, err=%d\n", err);
        goto out;
    }

    if (pmaos_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to write PMAOS, status=%d\n", pmaos_reg_data.op_tlv.status);
        goto out;
    }

out:
    if (release_lock) {
        mutex_unlock(&priv->module_access_mutex);
    }
    return err;
}

static int __module_control_set(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool enable_sw_control)
{
    int                       err = 0;
    struct sx_priv           *priv = sx_priv(dev);
    struct ku_access_mmcr_reg mmcr_reg_data;
    bool                      release_lock = false;

    memset(&mmcr_reg_data, 0, sizeof(mmcr_reg_data));
    mmcr_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mmcr_reg_data.op_tlv, MLXSW_MMCR_ID, EMAD_METHOD_WRITE);

    /*
     * Set MMCR bit X for module ID X.
     * To shift control from SW to FW matching bit in module_sw_control should be 0.
     * To shift control from FW to SW matching bit in module_sw_control should be 1.
     */
    SX_CORE_BITMAP_SET(mmcr_reg_data.mmcr_reg.module_control_mask,
                       SXD_MMCR_MODULE_CONTROL_MASK_NUM,
                       sizeof(mmcr_reg_data.mmcr_reg.module_control_mask[0]) * 8,
                       module_id);
    if (enable_sw_control) {
        SX_CORE_BITMAP_SET(mmcr_reg_data.mmcr_reg.module_sw_control,
                           SXD_MMCR_MODULE_SW_CONTROL_NUM,
                           sizeof(mmcr_reg_data.mmcr_reg.module_sw_control[0]) * 8,
                           module_id);
    }

    mutex_lock(&priv->module_access_mutex);
    release_lock = true;

    err = sx_ACCESS_REG_MMCR(dev, &mmcr_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to write MMCR, err=%d\n", err);
        goto out;
    }

    if (mmcr_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to write MMCR, status=%d\n", mmcr_reg_data.op_tlv.status);
        goto out;
    }

out:
    if (release_lock) {
        mutex_unlock(&priv->module_access_mutex);
    }
    return err;
}

int sx_core_set_module_control(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id)
{
    int             err = 0;
    struct sx_priv *priv = sx_priv(dev);
    bool            is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        printk(KERN_ERR PFX "%s: Failed to get current module control state.\n", __func__);
        goto out;
    }

    if (is_independent == false) {
        printk(KERN_ERR PFX "%s: Failed control change: module is dependent (FW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

    err = __module_control_set(dev, slot_id, module_id, false);
    if (err) {
        goto out;
    }

    /* Control change from SW to FW is valid for plugged modules.
     * When FW done with module init PMPE will be triggered.
     * To suppress this event from present sysfs, init DB with "plugged" state.
     */
    priv->module_data[slot_id][module_id].present = SX_MODULE_PRESENT_PLUGGED;

    /* Enable update events (all events) */
    err = __module_event_enable_set(dev, slot_id, module_id, SXD_PMAOS_E_GENERATE_EVENT_E);
    if (err) {
        goto out;
    }

    priv->module_data[slot_id][module_id].independent_params.hw_present = SX_MODULE_HW_PRESENT_INVALID;
    priv->module_data[slot_id][module_id].independent_params.interrupt = SX_MODULE_INTERRUPT_INVALID;
    priv->module_data[slot_id][module_id].independent_params.power_good = SX_MODULE_POWER_GOOD_INVALID;

out:
    return err;
}

static ssize_t show_module_control(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int            ret = 0;
    bool           is_independent = false;
    int            len = 0;
    int            val = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_get_module_control failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    if (is_independent) {
        val = 1;
    }

    len = sprintf(buf, "%d\n", val);

    return len;

out:
    return ret;
}

static ssize_t store_module_control(struct kobject        *kobj,
                                    struct kobj_attribute *attr,
                                    const char            *buf,
                                    size_t                 len)
{
    int            ret = 0;
    int            control = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = kstrtoint(buf, 10, &control);
    if (ret) {
        printk(KERN_ERR PFX "sysfs entry control got invalid value\n");
        ret = -EINVAL;
        goto out;
    }

    if (control != 0) {
        printk(KERN_ERR PFX "sysfs entry control got invalid value\n");
        ret = -EINVAL;
        goto out;
    }

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of control sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_set_module_control(dev, slot_id, module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_set_module_control failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    return len;

out:
    return ret;
}

int sx_core_get_module_hw_reset(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool *is_hw_reset)
{
    int                        err = 0;
    struct sx_priv            *priv = sx_priv(dev);
    struct ku_access_mcion_reg mcion_reg_data;
    bool                       release_lock = false;
    bool                       is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent == false) {
        printk(KERN_ERR PFX "%s: Failed control change: module is dependent (FW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

    memset(&mcion_reg_data, 0, sizeof(mcion_reg_data));
    mcion_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mcion_reg_data.op_tlv, MLXSW_MCION_ID, EMAD_METHOD_QUERY);

    mcion_reg_data.mcion_reg.slot_index = slot_id;
    mcion_reg_data.mcion_reg.module = module_id;


    mutex_lock(&priv->module_access_mutex);
    release_lock = true;

    err = sx_ACCESS_REG_MCION(dev, &mcion_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to query MCION, err=%d\n", err);
        goto out;
    }

    if (mcion_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to query MCION, status=%d\n", mcion_reg_data.op_tlv.status);
        goto out;
    }

    *is_hw_reset = mcion_reg_data.mcion_reg.module_inputs & 0x1;

out:
    if (release_lock) {
        mutex_unlock(&priv->module_access_mutex);
    }
    return err;
}

static ssize_t show_module_hw_reset(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int            ret = 0;
    bool           is_hw_reset = false;
    int            len = 0;
    int            val = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_module_hw_reset(dev, slot_id, module_id, &is_hw_reset);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_get_module_hw_reset failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        return ret;
    }

    if (is_hw_reset) {
        val = 1;
    }

    len = sprintf(buf, "%d\n", val);

    return len;

out:
    return ret;
}


int sx_core_set_module_hw_reset(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, int hw_reset)
{
    int                        err = 0;
    struct sx_priv            *priv = sx_priv(dev);
    struct ku_access_mcion_reg mcion_reg_data;
    bool                       release_lock = false;
    bool                       is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent == false) {
        printk(KERN_ERR PFX "%s: Failed hw reset change: module is dependent (FW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

    memset(&mcion_reg_data, 0, sizeof(mcion_reg_data));
    mcion_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mcion_reg_data.op_tlv, MLXSW_MCION_ID, EMAD_METHOD_WRITE);

    mcion_reg_data.mcion_reg.slot_index = slot_id;
    mcion_reg_data.mcion_reg.module = module_id;
    mcion_reg_data.mcion_reg.module_inputs_mask = MCION_INPUT_BITS_MASK_HW_RESET;
    mcion_reg_data.mcion_reg.module_inputs = hw_reset;


    mutex_lock(&priv->module_access_mutex);
    release_lock = true;

    err = sx_ACCESS_REG_MCION(dev, &mcion_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to write MCION, err=%d\n", err);
        goto out;
    }

    if (mcion_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to write MCION, status=%d\n", mcion_reg_data.op_tlv.status);
        goto out;
    }


out:
    if (release_lock) {
        mutex_unlock(&priv->module_access_mutex);
    }
    return err;
}


static ssize_t store_module_hw_reset(struct kobject        *kobj,
                                     struct kobj_attribute *attr,
                                     const char            *buf,
                                     size_t                 len)
{
    int            ret = 0;
    int            hw_reset = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = kstrtoint(buf, 10, &hw_reset);
    if (ret) {
        printk(KERN_ERR PFX "sysfs entry hw_reset got invalid value\n");
        ret = -EINVAL;
        goto out;
    }

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of hw_reset sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }
    if ((hw_reset != 0) && (hw_reset != 1)) {
        printk(KERN_ERR PFX "%s: Invalid hw_reset value (%d) failed  for %s\n",
               __func__,
               hw_reset,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_set_module_hw_reset(dev, slot_id, module_id, hw_reset);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_set_module_hw_reset failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    return len;

out:
    return ret;
}


int sx_core_get_module_low_power_mode(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool *is_low_power_mode)
{
    int                        err = 0;
    struct sx_priv            *priv = sx_priv(dev);
    struct ku_access_mcion_reg mcion_reg_data;
    bool                       release_lock = false;
    bool                       is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent == false) {
        printk(KERN_ERR PFX "%s: Failed control change: module is dependent (FW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

    memset(&mcion_reg_data, 0, sizeof(mcion_reg_data));
    mcion_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mcion_reg_data.op_tlv, MLXSW_MCION_ID, EMAD_METHOD_QUERY);

    mcion_reg_data.mcion_reg.slot_index = slot_id;
    mcion_reg_data.mcion_reg.module = module_id;


    mutex_lock(&priv->module_access_mutex);
    release_lock = true;

    err = sx_ACCESS_REG_MCION(dev, &mcion_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to query MCION, err=%d\n", err);
        goto out;
    }

    if (mcion_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to query MCION, status=%d\n", mcion_reg_data.op_tlv.status);
        goto out;
    }

    *is_low_power_mode = mcion_reg_data.mcion_reg.module_inputs & 0x2;

out:
    if (release_lock) {
        mutex_unlock(&priv->module_access_mutex);
    }
    return err;
}

static ssize_t show_module_low_power_mode(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int            ret = 0;
    bool           is_low_power_mode = false;
    int            len = 0;
    int            val = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_module_low_power_mode(dev, slot_id, module_id, &is_low_power_mode);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_get_module_low_power_mode failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        return ret;
    }

    if (is_low_power_mode) {
        val = 1;
    }

    len = sprintf(buf, "%d\n", val);

    return len;

out:
    return ret;
}


int sx_core_set_module_low_power_mode(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, int low_power_mode)
{
    int                        err = 0;
    struct sx_priv            *priv = sx_priv(dev);
    struct ku_access_mcion_reg mcion_reg_data;
    bool                       release_lock = false;
    bool                       is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent == false) {
        printk(KERN_ERR PFX "%s: Failed low power mode change: module is dependent (FW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

    memset(&mcion_reg_data, 0, sizeof(mcion_reg_data));
    mcion_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mcion_reg_data.op_tlv, MLXSW_MCION_ID, EMAD_METHOD_WRITE);

    mcion_reg_data.mcion_reg.slot_index = slot_id;
    mcion_reg_data.mcion_reg.module = module_id;
    mcion_reg_data.mcion_reg.module_inputs_mask = MCION_INPUT_BITS_MASK_LOW_POWER;
    mcion_reg_data.mcion_reg.module_inputs = low_power_mode << 1;


    mutex_lock(&priv->module_access_mutex);
    release_lock = true;

    err = sx_ACCESS_REG_MCION(dev, &mcion_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to write MCION, err=%d\n", err);
        goto out;
    }

    if (mcion_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to write MCION, status=%d\n", mcion_reg_data.op_tlv.status);
        goto out;
    }


out:
    if (release_lock) {
        mutex_unlock(&priv->module_access_mutex);
    }
    return err;
}


static ssize_t store_module_low_power_mode(struct kobject        *kobj,
                                           struct kobj_attribute *attr,
                                           const char            *buf,
                                           size_t                 len)
{
    int            ret = 0;
    int            low_power_mode = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = kstrtoint(buf, 10, &low_power_mode);
    if (ret) {
        printk(KERN_ERR PFX "sysfs entry low_power_mode got invalid value\n");
        ret = -EINVAL;
        goto out;
    }

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of low_power_mode sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }
    if ((low_power_mode != 0) && (low_power_mode != 1)) {
        printk(KERN_ERR PFX "%s: Invalid low_power_mode value (%d) failed  for %s\n",
               __func__,
               low_power_mode,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_set_module_low_power_mode(dev, slot_id, module_id, low_power_mode);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_set_module_hw_reset failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    return len;

out:
    return ret;
}


int sx_core_get_module_hw_present(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool *is_hw_present)
{
    int                        err = 0;
    struct sx_priv            *priv = sx_priv(dev);
    struct ku_access_mcion_reg mcion_reg_data;
    bool                       release_lock = false;
    bool                       is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent == false) {
        printk(KERN_ERR PFX "%s: Failed control change: module is dependent (FW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

    memset(&mcion_reg_data, 0, sizeof(mcion_reg_data));
    mcion_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mcion_reg_data.op_tlv, MLXSW_MCION_ID, EMAD_METHOD_QUERY);

    mcion_reg_data.mcion_reg.slot_index = slot_id;
    mcion_reg_data.mcion_reg.module = module_id;


    mutex_lock(&priv->module_access_mutex);
    release_lock = true;

    err = sx_ACCESS_REG_MCION(dev, &mcion_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to query MCION, err=%d\n", err);
        goto out;
    }

    if (mcion_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to query MCION, status=%d\n", mcion_reg_data.op_tlv.status);
        goto out;
    }
    if (mcion_reg_data.mcion_reg.module_status_bits_valid & MCION_STATUS_MASK_HW_PRESENT) {
        err = -EINVAL;
        printk(KERN_ERR PFX "MCION hw_present status is not valid, err=%d\n", err);
        goto out;
    }
    *is_hw_present = mcion_reg_data.mcion_reg.module_status_bits & MCION_STATUS_MASK_HW_PRESENT;

out:
    if (release_lock) {
        mutex_unlock(&priv->module_access_mutex);
    }
    return err;
}

static ssize_t show_module_hw_present(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int            ret = 0;
    bool           is_hw_present = false;
    int            len = 0;
    int            val = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_module_hw_present(dev, slot_id, module_id, &is_hw_present);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_get_module_hw_present failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        return ret;
    }

    if (is_hw_present) {
        val = 1;
    }

    len = sprintf(buf, "%d\n", val);

    return len;

out:
    return ret;
}


int sx_core_get_module_interrupt(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool *is_interrupt)
{
    int                        err = 0;
    struct sx_priv            *priv = sx_priv(dev);
    struct ku_access_mcion_reg mcion_reg_data;
    bool                       release_lock = false;
    bool                       is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent == false) {
        printk(KERN_ERR PFX "%s: Failed control change: module is dependent (FW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

    memset(&mcion_reg_data, 0, sizeof(mcion_reg_data));
    mcion_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mcion_reg_data.op_tlv, MLXSW_MCION_ID, EMAD_METHOD_QUERY);

    mcion_reg_data.mcion_reg.slot_index = slot_id;
    mcion_reg_data.mcion_reg.module = module_id;


    mutex_lock(&priv->module_access_mutex);
    release_lock = true;

    err = sx_ACCESS_REG_MCION(dev, &mcion_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to query MCION, err=%d\n", err);
        goto out;
    }

    if (mcion_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to query MCION, status=%d\n", mcion_reg_data.op_tlv.status);
        goto out;
    }
    if (mcion_reg_data.mcion_reg.module_status_bits_valid & MCION_STATUS_MASK_INTERRUPT) {
        err = -EINVAL;
        printk(KERN_ERR PFX "MCION interrupt status is not valid, err=%d\n", err);
        goto out;
    }
    *is_interrupt = mcion_reg_data.mcion_reg.module_status_bits & MCION_STATUS_MASK_INTERRUPT;

out:
    if (release_lock) {
        mutex_unlock(&priv->module_access_mutex);
    }
    return err;
}

static ssize_t show_module_interrupt(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int            ret = 0;
    bool           is_interrupt = false;
    int            len = 0;
    int            val = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_module_interrupt(dev, slot_id, module_id, &is_interrupt);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_get_module_interrupt failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        return ret;
    }

    if (is_interrupt) {
        val = 1;
    }

    len = sprintf(buf, "%d\n", val);

    return len;

out:
    return ret;
}


int sx_core_get_module_power_good(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, bool *is_power_good)
{
    int                        err = 0;
    struct sx_priv            *priv = sx_priv(dev);
    struct ku_access_mcion_reg mcion_reg_data;
    bool                       release_lock = false;
    bool                       is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent == false) {
        printk(KERN_ERR PFX "%s: Failed control change: module is dependent (FW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

    memset(&mcion_reg_data, 0, sizeof(mcion_reg_data));
    mcion_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mcion_reg_data.op_tlv, MLXSW_MCION_ID, EMAD_METHOD_QUERY);

    mcion_reg_data.mcion_reg.slot_index = slot_id;
    mcion_reg_data.mcion_reg.module = module_id;


    mutex_lock(&priv->module_access_mutex);
    release_lock = true;

    err = sx_ACCESS_REG_MCION(dev, &mcion_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to query MCION, err=%d\n", err);
        goto out;
    }

    if (mcion_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to query MCION, status=%d\n", mcion_reg_data.op_tlv.status);
        goto out;
    }
    if (mcion_reg_data.mcion_reg.module_status_bits_valid & MCION_STATUS_MASK_POWER_GOOD) {
        err = -EINVAL;
        printk(KERN_ERR PFX "MCION power_good status is not valid, err=%d\n", err);
        goto out;
    }
    *is_power_good = mcion_reg_data.mcion_reg.module_status_bits & MCION_STATUS_MASK_POWER_GOOD;

out:
    if (release_lock) {
        mutex_unlock(&priv->module_access_mutex);
    }
    return err;
}

static ssize_t show_module_power_good(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int            ret = 0;
    bool           is_power_good = false;
    int            len = 0;
    int            val = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_module_power_good(dev, slot_id, module_id, &is_power_good);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_get_module_power_good failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        return ret;
    }

    if (is_power_good) {
        val = 1;
    }

    len = sprintf(buf, "%d\n", val);

    return len;

out:
    return ret;
}


int sx_core_get_module_power_limit(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, int *power_limit_p)
{
    int                       err = 0;
    struct sx_priv           *priv = sx_priv(dev);
    struct ku_access_mini_reg mini_reg_data;
    bool                      release_lock = false;
    bool                      is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent == false) {
        printk(KERN_ERR PFX "%s: Failed power_limit read: module is dependent (FW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

    memset(&mini_reg_data, 0, sizeof(mini_reg_data));
    mini_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mini_reg_data.op_tlv, MLXSW_MINI_ID, EMAD_METHOD_QUERY);

    mini_reg_data.mini_reg.type = SXD_MINI_TYPE_MODULE_POWER_LEVEL_E;
    mini_reg_data.mini_reg.index = module_id;

    mutex_lock(&priv->module_access_mutex);
    release_lock = true;

    err = sx_ACCESS_REG_MINI(dev, &mini_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to query MINI, err=%d\n", err);
        goto out;
    }

    if (mini_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to query MINI, status=%d\n", mini_reg_data.op_tlv.status);
        goto out;
    }

    *power_limit_p = mini_reg_data.mini_reg.data.mini_module_power_level.spl;

out:
    if (release_lock) {
        mutex_unlock(&priv->module_access_mutex);
    }
    return err;
}

static ssize_t show_module_power_limit(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int            ret = 0;
    int            power_limit = 0;
    int            len = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_module_power_limit(dev, slot_id, module_id, &power_limit);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_get_module_power_limit failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    len = sprintf(buf, "%d\n", power_limit);

    return len;

out:
    return ret;
}

int sx_core_reinsert_module(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, int reinsert)
{
    int             err = 0;
    bool            is_independent = false;
    struct sx_priv *priv = sx_priv(dev);
    bool            any_port_up = false;
    unsigned long   flags;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent) {
        printk(KERN_ERR PFX "%s: Failed reinsert change: module is independent (SW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }

    /* Invalid operation if any port is admin up */
    spin_lock_irqsave(&priv->db_lock, flags);
    any_port_up = __module_any_port_up_get(priv, slot_id, module_id);
    if (any_port_up) {
        spin_unlock_irqrestore(&priv->db_lock, flags);
        err = -EACCES;
        goto out;
    }
    spin_unlock_irqrestore(&priv->db_lock, flags);

    /*
     * Change module control via MMCR
     * Actual module ownership will change after pmaos.admin down & pmaos.admin up */
    err = __module_control_set(dev, slot_id, module_id, true);
    if (err) {
        goto out;
    }

    err = sx_core_set_module(dev, slot_id, module_id, 0, 0);
    if (err) {
        printk(KERN_ERR PFX "Failed to disable module %d.\n", module_id);
        goto out;
    }

    msleep(reinsert);

    err = sx_core_set_module(dev, slot_id, module_id, 1, 0);
    if (err) {
        printk(KERN_ERR PFX "Failed to enable module %d.\n", module_id);
        goto out;
    }

out:
    return err;
}

static ssize_t store_module_reinsert(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len)
{
    int            ret = 0;
    int            reinsert = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = kstrtoint(buf, 10, &reinsert);
    if (ret) {
        printk(KERN_INFO PFX "sysfs entry reinsert got invalid value\n");
        goto out;
    }

    if ((reinsert < 0) || (reinsert > 10000)) {
        ret = -EINVAL;
        printk(KERN_INFO PFX "sysfs entry reinsert got invalid value (%d)\n", reinsert);
        goto out;
    }

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of reinsert sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n", __func__, ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_reinsert_module(dev, slot_id, module_id, reinsert);
    if (ret) {
        printk(KERN_ERR PFX "Failed in sx_core_reinsert_module\n");
        return ret;
    }

    return len;
out:
    return ret;
}

int sx_core_set_module_frequency(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, int frequency)
{
    int                        err = 0;
    struct sx_priv            *priv = sx_priv(dev);
    unsigned long              flags;
    struct  ku_access_mcfs_reg mcfs_reg_data;
    bool                       release_lock = false;
    bool                       is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent == false) {
        printk(KERN_ERR PFX "%s: Frequency write is supported when module is in FW control.", __func__);
        err = -EFAULT;
        goto out;
    }
    spin_lock_irqsave(&priv->db_lock, flags);
    if (priv->independent_module_params.frequency_support == false) {
        printk(KERN_ERR PFX "%s: Frequency write is not supported.", __func__);
        err = -EFAULT;
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&priv->db_lock, flags);

    memset(&mcfs_reg_data, 0, sizeof(mcfs_reg_data));
    mcfs_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mcfs_reg_data.op_tlv, MLXSW_MCFS_ID, EMAD_METHOD_WRITE);

    mcfs_reg_data.mcfs_reg.slot_index = slot_id;
    mcfs_reg_data.mcfs_reg.module = module_id;
    mcfs_reg_data.mcfs_reg.freq = frequency;


    mutex_lock(&priv->module_access_mutex);
    release_lock = true;

    err = sx_ACCESS_REG_MCFS(dev, &mcfs_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to write MCFS, err=%d\n", err);
        goto out;
    }

    if (mcfs_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to write MCFS, status=%d\n", mcfs_reg_data.op_tlv.status);
        goto out;
    }


out:
    if (release_lock) {
        mutex_unlock(&priv->module_access_mutex);
    }
    return err;
}

static ssize_t store_module_frequency(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t len)
{
    int            ret = 0;
    int            frequency = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = kstrtoint(buf, 10, &frequency);
    if (ret) {
        printk(KERN_INFO PFX "sysfs entry frequency got invalid value\n");
        goto out;
    }

    if ((frequency < SXD_MFCS_FREQ_MIN) || (frequency > SXD_MFCS_FREQ_MAX)) {
        ret = -EINVAL;
        printk(KERN_INFO PFX "sysfs entry frequency is out of range (%d)\n", frequency);
        goto out;
    }

    if (!kobj->parent) {
        printk(KERN_ERR PFX "Parent of frequency sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n", __func__, ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_set_module_frequency(dev, slot_id, module_id, frequency);
    if (ret) {
        printk(KERN_ERR PFX "Failed in sx_core_set_module_frequency\n");
        return ret;
    }

    return len;
out:
    return ret;
}


int sx_core_get_module_frequency(struct sx_dev *dev, uint8_t slot_id, uint8_t module_id, int *frequency_p)
{
    int                       err = 0;
    struct sx_priv           *priv = sx_priv(dev);
    struct ku_access_mcfs_reg mcfs_reg_data;
    bool                      release_lock = false;
    unsigned long             flags;
    bool                      is_independent = false;

    err = sx_core_get_module_control(dev, slot_id, module_id, &is_independent);
    if (err) {
        goto out;
    }
    if (is_independent == false) {
        printk(KERN_ERR PFX "%s: Failed frequency read: module is dependent (FW control).\n", __func__);
        err = -EFAULT;
        goto out;
    }
    spin_lock_irqsave(&priv->db_lock, flags);
    if (priv->independent_module_params.frequency_support == false) {
        printk(KERN_ERR PFX "%s: Frequency read is not supported.", __func__);
        err = -EFAULT;
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&priv->db_lock, flags);

    memset(&mcfs_reg_data, 0, sizeof(mcfs_reg_data));
    mcfs_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mcfs_reg_data.op_tlv, MLXSW_MCFS_ID, EMAD_METHOD_QUERY);

    mcfs_reg_data.mcfs_reg.module = module_id;
    mcfs_reg_data.mcfs_reg.slot_index = slot_id;

    mutex_lock(&priv->module_access_mutex);
    release_lock = true;

    err = sx_ACCESS_REG_MCFS(dev, &mcfs_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Failed to query MCFS, err=%d\n", err);
        goto out;
    }

    if (mcfs_reg_data.op_tlv.status) {
        err = -EINVAL;
        printk(KERN_ERR PFX "Failed to query MCFS, status=%d\n", mcfs_reg_data.op_tlv.status);
        goto out;
    }

    *frequency_p = mcfs_reg_data.mcfs_reg.freq;

out:
    if (release_lock) {
        mutex_unlock(&priv->module_access_mutex);
    }
    return err;
}

static ssize_t show_module_frequency(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int            ret = 0;
    int            frequency = 0;
    int            len = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_module_frequency(dev, slot_id, module_id, &frequency);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_get_module_frequency failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    len = sprintf(buf, "%d\n", frequency);

    return len;

out:
    return ret;
}

int sx_core_get_module_frequency_support(struct sx_dev *dev, int *frequency_support_p)
{
    int             err = 0;
    struct sx_priv *priv = sx_priv(dev);


    *frequency_support_p = priv->independent_module_params.frequency_support;

    return err;
}

static ssize_t show_module_frequency_support(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int            ret = 0;
    int            frequency_support = 0;
    int            len = 0;
    struct sx_dev *dev = NULL;
    uint8_t        slot_id = 0;
    uint8_t        module_id = 0;

    ret = __module_sysfs_get_dev_slot_module(kobj, 0, &dev, &slot_id, &module_id);
    if (ret) {
        printk(KERN_ERR PFX "%s: __module_sysfs_get_dev_slot_module failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    ret = sx_core_get_module_frequency_support(dev, &frequency_support);
    if (ret) {
        printk(KERN_ERR PFX "%s: sx_core_get_module_frequency_support failed (%d) for %s\n",
               __func__,
               ret,
               kobject_name(kobj));
        goto out;
    }

    len = sprintf(buf, "%d\n", frequency_support);

    return len;

out:
    return ret;
}
