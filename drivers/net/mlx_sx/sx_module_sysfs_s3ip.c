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

/************************************************
 *  Enum
 ***********************************************/


/************************************************
 * Globals
 ***********************************************/


/************************************************
 *  Functions
 ***********************************************/

int sx_core_get_port_module_power_on(struct sx_dev *dev, uint16_t local_port, bool *power_on)
{
    int                        err = 0;
    unsigned long              flags;
    uint8_t                    module_id = 0;
    uint8_t                    slot_id = 0;
    struct ku_access_pmaos_reg pmaos_reg_data;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    err = sx_core_get_module_by_port(dev, local_port, &slot_id, &module_id);
    if (err) {
        spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

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
EXPORT_SYMBOL(sx_core_get_port_module_power_on);

int sx_core_power_on_off_port_module(struct sx_dev *dev, uint16_t local_port, bool power_on)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    int             i = 0;
    unsigned long   flags;
    uint8_t         module_id = 0;
    uint8_t         slot_id = 0;
    bool            any_port_up = false;

    spin_lock_irqsave(&priv->db_lock, flags);

    err = sx_core_get_module_by_port(dev, local_port, &slot_id, &module_id);
    if (err) {
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }

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
EXPORT_SYMBOL(sx_core_power_on_off_port_module);

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
int sx_core_set_port_module_tx_disable(struct sx_dev *dev, uint16_t local_port, bool tx_disable)
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

int sx_core_get_port_module_present(struct sx_dev *dev, uint16_t local_port, bool *present)
{
    int                        err = 0;
    unsigned long              flags;
    uint8_t                    module_id = 0;
    uint8_t                    slot_id = 0;
    struct sx_priv            *priv = sx_priv(dev);
    struct ku_access_pmaos_reg pmaos_reg_data;

    spin_lock_irqsave(&priv->db_lock, flags);
    err = sx_core_get_module_by_port(dev, local_port, &slot_id, &module_id);
    if (err) {
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }
    spin_unlock_irqrestore(&priv->db_lock, flags);

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
EXPORT_SYMBOL(sx_core_get_port_module_present);

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
    printk(KERN_DEBUG PFX "%s (latched_flag, status_opcode:0x%x)\n", __func__, status_opcode);

    *rx_los = false;
    if (status_opcode) {
        *rx_los = true;
    }

out:
    return err;
}
EXPORT_SYMBOL(sx_core_get_port_module_rx_los);
