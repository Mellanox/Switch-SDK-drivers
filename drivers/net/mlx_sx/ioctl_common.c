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

#include <linux/fs.h>
#include <linux/uaccess.h>

#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/kernel_user.h>

#include "sx.h"
#include "dev_db.h"
#include "dev_init.h"
#include "alloc.h"
#include "fw.h"

struct sx_dev * sx_core_ioctl_get_dev(sxd_dev_id_t dev_id)
{
    /* at some point the sx_dev will be determined from the file->private_data->dev_id
     * (when there are multiple char-devices, one per ASIC) and not from a passed dev_id
     * parameter. so in the future we will have another parameter to this function: file *filp.
     */
    struct sx_dev *dev;

    /* this function is used to get a sx_dev structure associated with a device ID
     * or the default device if no such device exists:
     *     - On 2U systems (with 2 ASICs), there is no default device. each ASIC has its own
     *       sx_dev instance.
     *     - On 1U systems (with 1 ASIC), the default device is a reference to the real device.
     *       (both pointers in __dev_db refer to the same sx_dev instance.
     *     - On director systems, there is only one sx_dev instance that represents all ASICs
     *       in the chassis - so if slot of 'dev_id' is empty, the default device sx_dev instance
     *       will be returned.
     */

    /* there are several commands that don't initialize their device ID (dev_id == 0).
     * in this case, we'll look for the default device.
     */
    if (dev_id == 0) {
        dev_id = DEFAULT_DEVICE_ID;
    }

    dev = sx_dev_db_get_dev_by_id(dev_id);
    if (!dev && (dev_id != DEFAULT_DEVICE_ID)) {
        dev = sx_dev_db_get_dev_by_id(DEFAULT_DEVICE_ID);
    }

    if (!dev) {
        printk(KERN_WARNING "ioctl - Device %u doesn't exist\n", dev_id);
    }

    return dev;
}

int sx_core_ioctl_enable_swid(struct file *file, struct sx_dev *dev, unsigned long data)
{
    struct sx_priv        *priv = NULL;
    int                    err = 0;
    struct ku_swid_details swid_data;

    err = copy_from_user(&swid_data, (void*)data,
                         sizeof(swid_data));
    if (err) {
        goto out;
    }

    if (sx_core_has_predefined_devices()) {
        swid_data.dev_id = get_device_id_from_fd(file);
    }

    if (!dev) {
        dev = sx_core_ioctl_get_dev(swid_data.dev_id);
        if (!dev) {
            return -ENODEV;
        }
    }

    priv = sx_priv(dev);

    if (sx_core_fw_is_faulty(dev)) {
        printk(KERN_NOTICE "Enable SWID: Faulty FW - ignoring.\n");
        return 0;
    }

    pr_debug(PFX "ioctl enable_swid called with swid %d\n", swid_data.swid);
    spin_lock(&priv->profile.profile_lock);
    if (!sx_cr_mode() && ((!priv->profile.pci_profile_set) || (swid_data.swid >= NUMBER_OF_SWIDS)
                          || (priv->profile.pci_profile.swid_type[swid_data.swid] ==
                              SX_KU_L2_TYPE_DONT_CARE) ||
                          sx_bitmap_test(&sx_priv(dev)->swid_bitmap,
                                         swid_data.swid))) {
        spin_unlock(&priv->profile.profile_lock);
        return -EINVAL;
    }

    spin_unlock(&priv->profile.profile_lock);
    err = sx_enable_swid(dev, swid_data.dev_id, swid_data.swid, swid_data.iptrap_synd, swid_data.mac);
    if (err) {
        goto out;
    }

out:
    return err;
}


int sx_core_ioctl_set_pci_profile(struct file *file, struct sx_dev *dev, unsigned long data, uint8_t set_profile)
{
    struct sx_priv              *priv = NULL;
    int                          err = 0;
    struct sx_pci_profile        pci_profile;
    struct ku_profile            profile;
    struct profile_driver_params addition_params;

    err = copy_from_user((void*)&pci_profile,
                         (void*)data, sizeof(pci_profile));
    if (err) {
        err = -ENOMEM;
        goto out;
    }

    if (sx_core_has_predefined_devices()) {
        pci_profile.dev_id = get_device_id_from_fd(file);
    }

    if (!dev) {
        dev = sx_core_ioctl_get_dev(pci_profile.dev_id);
        if (!dev) {
            return -ENODEV;
        }
    }

    priv = sx_priv(dev);

    if (sx_core_fw_is_faulty(dev)) {
        printk(KERN_NOTICE "Set PCI Profile: Faulty FW - ignoring.\n");
        return 0;
    }

    memcpy(&priv->profile.pci_profile, &pci_profile, sizeof(priv->profile.pci_profile));

    pr_debug(PFX "ioctl set pci profile called\n");
    spin_lock(&priv->profile.profile_lock);
    if (priv->profile.pci_profile_set) {
        printk(KERN_WARNING PFX "Err: cannot set "
               "profile twice\n");
        spin_unlock(&priv->profile.profile_lock);
        err = -EINVAL;
        goto out;
    }

    priv->profile.pci_profile_set = true;
    spin_unlock(&priv->profile.profile_lock);

    memset(&profile, 0, sizeof(profile));
    memset(&addition_params, 0, sizeof(addition_params));
    profile.dev_id = priv->profile.pci_profile.dev_id;

    err = __sx_core_dev_specific_cb_get_reference(dev);
    if (err) {
        printk(KERN_ERR PFX "__sx_core_dev_specific_cb_get_reference failed.\n");
        goto out;
    }

    if (sx_priv(dev)->dev_specific_cb.sx_set_device_profile_update_cb != NULL) {
        sx_priv(dev)->dev_specific_cb.sx_set_device_profile_update_cb(&profile, &addition_params);
    }

    __sx_core_dev_specific_cb_release_reference(dev);

    /*
     * Bug SW #1134997:
     * On modular systems like Orca, we should NEVER call sx_SET_PROFILE() on slave board!
     * The problem is that when we configure PCI profile, we should also set the CQE version to work with,
     * and it is done only with sx_SET_PROFILE().
     * Temporary fix is NOT to call sx_SET_PROFILE() if CQE version is 0 (backward compatible). For modular
     * systems with CQE version other than 0, we should find a better solution.
     */

    if ((profile.dev_id != DEFAULT_DEVICE_ID) && (addition_params.cqe_version != 0) && set_profile) {
        pr_debug(PFX "ioctl set pci profile: set cqe version (%u)\n",
                 addition_params.cqe_version);
        err = sx_SET_PROFILE(dev, &profile, &addition_params);
        if (err) {
            printk(KERN_WARNING PFX "Err: fail to set profile cqe version\n");
            goto out;
        }
    }

    err = sx_handle_set_profile(dev);
    if (err) {
        spin_lock(&priv->profile.profile_lock);
        priv->profile.pci_profile_set = false;
        spin_unlock(&priv->profile.profile_lock);
        goto out;
    }

    err = copy_to_user((void*)data, (void*)&priv->profile.pci_profile,
                       sizeof(priv->profile.pci_profile));
    if (err) {
        err = -ENOMEM;
        goto out;
    }

out:
    return err;
}


int sx_core_ioctl_get_pci_profile(struct sx_dev *dev, unsigned long data)
{
    struct sx_priv            *priv = sx_priv(dev);
    int                        err = 0;
    struct ku_get_pci_profile *pci_prof = NULL;

    spin_lock(&priv->profile.profile_lock);
    if (!priv->profile.pci_profile_set) {
        printk(KERN_WARNING PFX "Err: profile is not set\n");
        spin_unlock(&priv->profile.profile_lock);
        err = -EINVAL;
        goto out;
    }

    pci_prof = kmalloc(sizeof(*pci_prof), GFP_ATOMIC);
    if (pci_prof == NULL) {
        printk(KERN_ERR PFX "Err: alloc of pci_prof is failed\n");
        spin_unlock(&priv->profile.profile_lock);
        err = -ENOMEM;
        goto out;
    }

    pci_prof->pci_profile = priv->profile.pci_profile.pci_profile;
    pci_prof->profile = priv->profile.pci_profile;
    spin_unlock(&priv->profile.profile_lock);
    err = copy_to_user((struct ku_get_pci_profile *)data,
                       pci_prof, sizeof(*pci_prof));

    if (pci_prof != NULL) {
        kfree(pci_prof);
    }

    if (err) {
        err = -ENOMEM;
        goto out;
    }

out:
    return err;
}


int sx_core_add_synd_l2(u8                                swid,
                        u16                               hw_synd,
                        struct sx_dev                    *dev,
                        const struct ku_port_vlan_params *port_vlan_params,
                        u8                                is_register)
{
    union sx_event_data *event_data;

    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        return -ENOMEM;
    }

    event_data->eth_l3_synd.swid = swid;
    event_data->eth_l3_synd.hw_synd = hw_synd;
    event_data->eth_l3_synd.is_register = is_register;
    switch (port_vlan_params->port_vlan_type) {
    case KU_PORT_VLAN_PARAMS_TYPE_GLOBAL:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_GLOBAL;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_PORT:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_PORT;
        event_data->eth_l3_synd.port = port_vlan_params->sysport;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_LAG:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_LAG;
        event_data->eth_l3_synd.port = port_vlan_params->lag_id;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_VLAN:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_VLAN;
        event_data->eth_l3_synd.vlan = port_vlan_params->vlan;
        break;

    default:
        break;
    }

    sx_core_dispatch_event(dev, SX_DEV_EVENT_ADD_SYND_L2_NETDEV, event_data);
    kfree(event_data);

    return 0;
}


int sx_core_add_synd_l3(u8                                swid,
                        u16                               hw_synd,
                        struct sx_dev                    *dev,
                        const struct ku_port_vlan_params *port_vlan_params,
                        u8                                is_register)
{
    union sx_event_data *event_data;

    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        return -ENOMEM;
    }

    event_data->eth_l3_synd.swid = swid;
    event_data->eth_l3_synd.hw_synd = hw_synd;
    event_data->eth_l3_synd.is_register = is_register;
    switch (port_vlan_params->port_vlan_type) {
    case KU_PORT_VLAN_PARAMS_TYPE_GLOBAL:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_GLOBAL;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_PORT:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_PORT;
        event_data->eth_l3_synd.port = port_vlan_params->sysport;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_LAG:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_LAG;
        event_data->eth_l3_synd.port = port_vlan_params->lag_id;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_VLAN:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_VLAN;
        event_data->eth_l3_synd.vlan = port_vlan_params->vlan;
        break;

    default:
        break;
    }

    sx_core_dispatch_event(dev, SX_DEV_EVENT_ADD_SYND_NETDEV, event_data);
    kfree(event_data);

    return 0;
}


int sx_core_add_synd_phy(u8                                swid,
                         u16                               hw_synd,
                         struct sx_dev                    *dev,
                         const struct ku_port_vlan_params *port_vlan_params,
                         u8                                is_register)
{
    union sx_event_data *event_data;

    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        return -ENOMEM;
    }

    event_data->eth_l3_synd.swid = swid;
    event_data->eth_l3_synd.hw_synd = hw_synd;
    event_data->eth_l3_synd.is_register = is_register;
    switch (port_vlan_params->port_vlan_type) {
    case KU_PORT_VLAN_PARAMS_TYPE_GLOBAL:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_GLOBAL;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_PORT:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_PORT;
        event_data->eth_l3_synd.port = port_vlan_params->sysport;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_LAG:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_LAG;
        event_data->eth_l3_synd.port = port_vlan_params->lag_id;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_VLAN:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_VLAN;
        event_data->eth_l3_synd.vlan = port_vlan_params->vlan;
        break;

    default:
        break;
    }
    sx_core_dispatch_event(dev, SX_DEV_EVENT_ADD_SYND_PHY_NETDEV, event_data);
    kfree(event_data);

    return 0;
}
