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

#include <linux/mlx_sx/kernel_user.h>

#include "sx.h"
#include "ioctl_internal.h"
#include "dev_init.h"

long ctrl_cmd_set_pci_profile(struct file *file, unsigned int cmd, unsigned long data)
{
    return sx_core_ioctl_set_pci_profile(NULL, data, 1);
}


long ctrl_cmd_set_pci_profile_driver_only(struct file *file, unsigned int cmd, unsigned long data)
{
    return sx_core_ioctl_set_pci_profile(NULL, data, 0);
}


long ctrl_cmd_pci_register_driver(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev *dev = sx_dev_db_get_default_device();

    printk(KERN_INFO "ioctl PCI register driver called for device\n");

    if (!dev) {
        printk(KERN_ERR "default device wasn't found\n");
        return -ENODEV;
    }

    return sx_restart_one_pci(dev);
}


long ctrl_cmd_pci_device_restart(struct file *file, unsigned int cmd, unsigned long data)
{
    sxd_dev_id_t   dev_id = (sxd_dev_id_t)data;
    struct sx_dev *dev;

    printk(KERN_INFO "ioctl PCI device restart restart called for device %u\n", dev_id);

    dev = sx_dev_db_get_dev_by_id(dev_id);

    if (!dev) {
        printk(KERN_ERR "device %u wasn't found\n", dev_id);
        return -ENODEV;
    }

    return sx_restart_one_pci(dev);
}


long ctrl_cmd_get_pci_profile(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev            *dev;
    struct ku_get_pci_profile pci_prof;
    int                       err = 0;

    err = copy_from_user(&pci_prof,
                         (void*)data, sizeof(pci_prof));

    if (err) {
        return -ENOMEM;
    }

    dev = sx_core_ioctl_get_dev(pci_prof.dev_id);
    if (!dev) {
        return -ENODEV;
    }

    return sx_core_ioctl_get_pci_profile(dev, data);
}


long ctrl_cmd_reset(struct file *file, unsigned int cmd, unsigned long data)
{
    sxd_dev_id_t   dev_id = (sxd_dev_id_t)data;
    struct sx_dev *dev;

    dev = sx_core_ioctl_get_dev(dev_id);
    if (!dev) {
        return -ENODEV;
    }

    return sx_change_configuration(dev);
}
