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

#include <linux/mlx_sx/kernel_user.h>

#include "sx.h"
#include "ioctl_internal.h"

long ctrl_cmd_set_pci_profile(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev *dev;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);
    return sx_core_ioctl_set_pci_profile(dev, data, 1);
}


long ctrl_cmd_set_pci_profile_driver_only(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev *dev;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);
    return sx_core_ioctl_set_pci_profile(dev, data, 0);
}


long ctrl_cmd_pci_register_driver(struct file *file, unsigned int cmd, unsigned long data)
{
    return register_driver_with_pci();
}


long ctrl_cmd_pci_device_restart(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev *tmp_dev = NULL, *curr_dev = NULL;
    u8             found = 0;

    printk(KERN_DEBUG PFX "ioctl device restart called for device %lu\n", data);

    spin_lock(&sx_glb.pci_devs_lock);

    list_for_each_entry_safe(curr_dev, tmp_dev, &sx_glb.pci_devs_list, list) {
        if (curr_dev->device_id == data) {
            found = 1;
            break;
        }
    }

    spin_unlock(&sx_glb.pci_devs_lock);

    if (!found) {
        printk(KERN_ERR "ioctl device restart: the device wasn't found\n");
        return -ENODEV;
    }

    return sx_restart_one_pci(curr_dev->pdev);
}


long ctrl_cmd_get_pci_profile(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev *dev;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);
    return sx_core_ioctl_get_pci_profile(dev, data);
}


long ctrl_cmd_reset(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev *dev;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);
    return sx_change_configuration(dev);
}
