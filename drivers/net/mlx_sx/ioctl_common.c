/*
 * Copyright (c) 2010-2019,  Mellanox Technologies. All rights reserved.
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

#include <linux/fs.h>
#include <linux/uaccess.h>

#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/kernel_user.h>

#include "sx.h"
#include "alloc.h"
#include "fw.h"

int sx_core_ioctl_enable_swid(struct sx_dev *dev, unsigned long data)
{
    int                    err = 0;
    struct ku_swid_details swid_data;

    err = copy_from_user(&swid_data, (void*)data,
                         sizeof(swid_data));
    if (err) {
        goto out;
    }

    printk(KERN_DEBUG PFX "ioctl enable_swid called with swid %d\n", swid_data.swid);
    spin_lock(&dev->profile_lock);
    if (!dev->profile_set || (swid_data.swid >= NUMBER_OF_SWIDS)
        || (dev->profile.swid_type[swid_data.swid] ==
            SX_KU_L2_TYPE_DONT_CARE) ||
        sx_bitmap_test(&sx_priv(dev)->swid_bitmap,
                       swid_data.swid)) {
        spin_unlock(&dev->profile_lock);
        return -EINVAL;
    }

    spin_unlock(&dev->profile_lock);
    err = sx_enable_swid(dev, swid_data.dev_id, swid_data.swid, swid_data.iptrap_synd, swid_data.mac);
    if (err) {
        goto out;
    }

out:
    return err;
}


int sx_core_ioctl_set_pci_profile(struct sx_dev *dev, unsigned long data, uint8_t set_profile)
{
    int                          err = 0;
    struct ku_profile            profile;
    struct profile_driver_params addition_params;

    printk(KERN_DEBUG PFX "ioctl set pci profile called\n");
    spin_lock(&dev->profile_lock);
    if (dev->profile_set == 1) {
        printk(KERN_WARNING PFX "Err: cannot set "
               "profile twice\n");
        spin_unlock(&dev->profile_lock);
        err = -EINVAL;
        goto out;
    }

    dev->profile_set = 1;
    spin_unlock(&dev->profile_lock);

    err = copy_from_user((void*)&dev->profile,
                         (void*)data, sizeof(dev->profile));
    if (err) {
        err = -ENOMEM;
        goto out;
    }

    memset(&profile, 0, sizeof(profile));
    memset(&addition_params, 0, sizeof(addition_params));
    profile.dev_id = dev->profile.dev_id;

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
        printk(KERN_DEBUG PFX "ioctl set pci profile: set cqe version (%u)\n",
               addition_params.cqe_version);
        err = sx_SET_PROFILE(dev, &profile, &addition_params);
        if (err) {
            printk(KERN_WARNING PFX "Err: fail to set profile cqe version\n");
            goto out;
        }
    }

    err = sx_handle_set_profile(dev);
    if (err) {
        spin_lock(&dev->profile_lock);
        dev->profile_set = 0;
        spin_unlock(&dev->profile_lock);
        goto out;
    }

    err = copy_to_user((void*)data, (void*)&dev->profile,
                       sizeof(dev->profile));
    if (err) {
        err = -ENOMEM;
        goto out;
    }

out:
    return err;
}


int sx_core_ioctl_get_pci_profile(struct sx_dev *dev, unsigned long data)
{
    int                        err = 0;
    struct ku_get_pci_profile *pci_prof = NULL;

    spin_lock(&dev->profile_lock);
    if (!dev->profile_set) {
        printk(KERN_WARNING PFX "Err: profile is not set\n");
        spin_unlock(&dev->profile_lock);
        err = -EINVAL;
        goto out;
    }

    pci_prof = kmalloc(sizeof(*pci_prof), GFP_ATOMIC);
    if (pci_prof == NULL) {
        printk(KERN_ERR PFX "Err: alloc of pci_prof is failed\n");
        spin_unlock(&dev->profile_lock);
        err = -ENOMEM;
        goto out;
    }

    pci_prof->pci_profile = dev->profile.pci_profile;
    pci_prof->profile = dev->profile;
    spin_unlock(&dev->profile_lock);
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


int sx_core_add_synd_l2(u8                          swid,
                        u16                         hw_synd,
                        struct sx_dev              *dev,
                        struct ku_port_vlan_params *port_vlan_params,
                        u8                          is_register)
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


int sx_core_add_synd_l3(u8                          swid,
                        u16                         hw_synd,
                        struct sx_dev              *dev,
                        struct ku_port_vlan_params *port_vlan_params,
                        u8                          is_register)
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


int sx_core_add_synd_phy(u8                          swid,
                         u16                         hw_synd,
                         struct sx_dev              *dev,
                         struct ku_port_vlan_params *port_vlan_params,
                         u8                          is_register)
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
