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
#include <linux/slab.h>
#include <linux/pci.h>
#include <linux/seq_file.h>
#include "dev_db.h"

static char *predefined_dev_pci_bus[MAX_NUM_OF_REMOTE_SWITCHES] = { 0 };
static int   predefined_num_of_pci_devices = 0;
module_param_array(predefined_dev_pci_bus, charp, &predefined_num_of_pci_devices,  0444);

struct sx_dev_db_entry {
    struct list_head dev_list;  /* list of valid devices */
    struct sx_dev   *dev;
    const char      *bus_name;
};
static struct sx_dev_db_entry __dev_db[MAX_NUM_OF_REMOTE_SWITCHES];
static LIST_HEAD(__valid_devices_list);
static DEFINE_SPINLOCK(__dev_db_lock);

#define DUMMY_BUS_NAME "<none>"

static int __sx_dev_db_map_dev_id_to_bus(sxd_dev_id_t dev_id, const char *bus_name)
{
    int err = 0;

    spin_lock_bh(&__dev_db_lock);

    if (__dev_db[dev_id].bus_name) {
        printk(KERN_ERR "Device_ID-to-Bus: Device %u has already bound to a bus\n", dev_id);
        err = -EEXIST;
        goto out;
    }

    __dev_db[dev_id].bus_name = kstrdup(bus_name, GFP_KERNEL);
    if (!__dev_db[dev_id].bus_name) {
        printk(KERN_ERR "Device_ID-to-Bus: failed to allocate bus name for device %d\n", dev_id);
        err = -ENOMEM;
        goto out;
    }

    printk(KERN_INFO "Device_ID-to-Bus: %u ==> %s\n", dev_id, bus_name);

out:
    spin_unlock_bh(&__dev_db_lock);
    return err;
}

static int __sx_dev_db_assign_predefined_devices(void)
{
    char dev_bus[128];
    int  dev_id;
    int  i, rc, err = -EINVAL;

    for (i = 0; i < predefined_num_of_pci_devices; i++) {
        if (strlen(predefined_dev_pci_bus[i]) >= sizeof(dev_bus)) {
            printk(KERN_ERR "Predefined device: name is too long on iteration %d\n", i);
            goto out;
        }

        rc = sscanf(predefined_dev_pci_bus[i], "%d@%s", &dev_id, dev_bus);
        if (rc != 2) {
            printk(KERN_ERR "Predefined device: name is invalid on iteration %d\n", i);
            goto out;
        }

        if (!DEV_ID_IS_VALID(dev_id)) {
            printk(KERN_ERR "Device_ID-to-Bus: invalid device ID (dev_id=%d)\n", dev_id);
            err = -EINVAL;
            goto out;
        }

        err = __sx_dev_db_map_dev_id_to_bus((sxd_dev_id_t)dev_id, dev_bus);
        if (err) {
            printk(KERN_ERR "Predefined device: cannot bind device ID to bus on iteration %d\n", i);
            goto out;
        }
    }

    err = 0;

out:
    return err;
}

int dev_db_init(void)
{
    return __sx_dev_db_assign_predefined_devices();
}

void dev_db_deinit(void)
{
    int i;

    for (i = 0; i < MAX_NUM_OF_REMOTE_SWITCHES; i++) {
        if (__dev_db[i].bus_name) {
            kfree(__dev_db[i].bus_name);
            __dev_db[i].bus_name = NULL;
        }
    }
}

static int __allocate_dev_id_legacy(sxd_dev_id_t *dev_id)
{
    int i;

    for (i = DEFAULT_DEVICE_ID; i >= 0; i--) {
        if (DEV_ID_IS_VALID(i) && !__dev_db[i].dev) {
            *dev_id = (sxd_dev_id_t)i;
            return 0;
        }
    }

    printk(KERN_ERR "Add device to database: failed to allocate device ID (legacy mode)\n");
    return -ENOENT;
}

static int __allocate_dev_id(const char *bus_name, sxd_dev_id_t *dev_id)
{
    int i;

#ifdef NO_PCI
    WARN_ON(1);
    return -EINVAL;
#endif

    for (i = 0; i < MAX_NUM_OF_REMOTE_SWITCHES; i++) {
        if (DEV_ID_IS_VALID(i) && __dev_db[i].bus_name && strstr(__dev_db[i].bus_name, bus_name)) {
            if (__dev_db[i].dev) {
                printk(KERN_ERR "Add device to database: ID %d already bound to another device\n", i);
                return -EEXIST;
            }

            *dev_id = (sxd_dev_id_t)i;
            return 0;
        }
    }

    printk(KERN_ERR "Add device to database: device's bus '%s' is not associated with ID\n", bus_name);
    return -ENOENT;
}

int sx_dev_db_add_device(struct sx_dev *dev)
{
    const char  *bus_name = DUMMY_BUS_NAME;
    sxd_dev_id_t dev_id;
    int          err = 0;

    if (!dev) {
        printk(KERN_ERR "Add device to database: invalid device\n");
        return -EINVAL;
    }

    /* not always a PCI device is attached to the SX device:
     * 1. NO_PCI configuration where we create a device that is not attached to PCI.
     * 2. On OOB system no PCI device is found on the bus so we create a non-PCI device to work with.
     *
     * In case a PCI is attached to the SX device, take the bus name from it.
     */
    if (dev->pdev) {
        bus_name = dev_name(&dev->pdev->dev);
    }

    spin_lock_bh(&__dev_db_lock);

    if (predefined_num_of_pci_devices > 0) { /* in this case, each PCI device's bus is associated with ID */
        if (!dev->pdev) {
            printk(KERN_ERR "Add device to database: there are predefined bus names but device is not on PCI\n");
            err = -EINVAL;
            goto out;
        }

        err = __allocate_dev_id(bus_name, &dev_id);
    } else { /* legacy mode, single device that is also referred as the default device */
        err = __allocate_dev_id_legacy(&dev_id);
    }

    if (err) {
        printk(KERN_ERR "failed to allocate an ID for device\n");
        goto out;
    }

    INIT_LIST_HEAD(&__dev_db[dev_id].dev_list);
    list_add_tail(&__dev_db[dev_id].dev_list, &__valid_devices_list);
    __dev_db[dev_id].dev = dev;
    dev->device_id = dev_id;

    printk(KERN_INFO "Add device to database: [id=%u, bus=%s]\n", dev_id, bus_name);

out:
    spin_unlock_bh(&__dev_db_lock);
    return err;
}

int sx_dev_db_remove_device(struct sx_dev *dev)
{
    const char *bus_name = DUMMY_BUS_NAME;
    int         err = 0;

    if (!dev) {
        printk(KERN_ERR "Remove device from database: invalid device\n");
        return -EINVAL;
    }

    if (!DEV_ID_IS_VALID(dev->device_id)) {
        printk(KERN_ERR "Remove device from database: invalid device ID (id=%u)\n", dev->device_id);
        return -EINVAL;
    }

    if (dev->pdev) {
        bus_name = dev_name(&dev->pdev->dev);
    }

    spin_lock_bh(&__dev_db_lock);

    if (!__dev_db[dev->device_id].dev) {
        printk(KERN_ERR "Remove device from database: device not found\n");
        err = -ENODEV;
        goto out;
    }

    if (__dev_db[dev->device_id].dev == __dev_db[DEFAULT_DEVICE_ID].dev) {
        printk(KERN_NOTICE "Removing the default device\n");
        __dev_db[DEFAULT_DEVICE_ID].dev = NULL;
    }

    list_del(&__dev_db[dev->device_id].dev_list);
    __dev_db[dev->device_id].dev = NULL;

    printk(KERN_INFO "Remove device from database: [id=%u, bus=%s]\n", dev->device_id, bus_name);

out:
    spin_unlock_bh(&__dev_db_lock);
    return err;
}

/* this function is used only for legacy (when predefined_num_of_pci_devices == 0):
 * we take the only device we have (that has the DEFAULT_DEVICE_ID) and assign it
 * an additional device ID.
 */
int sx_dev_db_reassign_dev_id_to_default_device(sxd_dev_id_t dev_id)
{
    int err = 0;

    if ((predefined_num_of_pci_devices > 0) || DEFAULT_DEVICE_ID_CHECK(dev_id)) {
        /* two cases when we just return and do nothing:
         * 1. predefined_num_of_pci_devices > 0  ==> There is no default device anymore.
         * 2. OOB backbone (SwitchX) PCI probe reached here with device id 254, we don't want it to be the default.
         */

        return 0;
    }

    if (!DEV_ID_IS_VALID(dev_id)) {
        printk(KERN_ERR "device ID %u is no valid\n", dev_id);
        return -EINVAL;
    }

    spin_lock_bh(&__dev_db_lock);

    if (!__dev_db[DEFAULT_DEVICE_ID].dev) {
        printk(KERN_ERR "There is no default device yet\n");
        err = -ENODEV;
        goto out;
    }

    if (__dev_db[dev_id].dev) {
        if (__dev_db[dev_id].dev != __dev_db[DEFAULT_DEVICE_ID].dev) {
            printk(KERN_ERR "device ID %u is already assigned\n", dev_id);
            err = -EEXIST;
        }
        /* else: already assigned to this device, just ignore and go out gracefully */

        goto out;
    }

    __dev_db[dev_id].dev = __dev_db[DEFAULT_DEVICE_ID].dev;
    __dev_db[dev_id].dev->device_id = dev_id;
    list_del(&__dev_db[DEFAULT_DEVICE_ID].dev_list);
    list_add_tail(&__dev_db[dev_id].dev_list, &__valid_devices_list);

    printk(KERN_INFO "Default device has a new device ID: %u\n", dev_id);

out:
    spin_unlock_bh(&__dev_db_lock);
    return err;
}

struct sx_dev * sx_dev_db_get_dev_by_id(sxd_dev_id_t dev_id)
{
    struct sx_dev *dev = NULL;

    if (!DEV_ID_IS_VALID(dev_id)) {
        printk(KERN_ERR "cannot find device %d - invalid device ID\n", (int)dev_id);
        return NULL;
    }

    spin_lock_bh(&__dev_db_lock);
    dev = __dev_db[dev_id].dev;
    spin_unlock_bh(&__dev_db_lock);

    return dev;
}

struct sx_dev * sx_dev_db_get_default_device(void)
{
    return sx_dev_db_get_dev_by_id(DEFAULT_DEVICE_ID);
}


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
struct sx_dev * sx_dev_db_get_dev_by_id_legacy(sxd_dev_id_t dev_id)
{
    struct sx_dev *dev = NULL;

    if (!DEV_ID_IS_VALID(dev_id)) {
        printk(KERN_ERR "cannot find device %d - invalid device ID\n", (int)dev_id);
        return NULL;
    }

    spin_lock_bh(&__dev_db_lock);
    dev = __dev_db[dev_id].dev;

    /* if there are predefined PCI devices, there is no default device */
    if (!dev && (predefined_num_of_pci_devices == 0)) {
        dev = __dev_db[DEFAULT_DEVICE_ID].dev;
    }
    spin_unlock_bh(&__dev_db_lock);

    return dev;
}

void sx_dev_db_iterate(sx_dev_db_iterator_cb_t iter_cb, void *context)
{
    struct sx_dev_db_entry *iter;

    spin_lock_bh(&__dev_db_lock);

    list_for_each_entry(iter, &__valid_devices_list, dev_list) {
        if (!iter_cb(iter->dev, context)) { /* callback may decide to terminate the iteration */
            break;
        }
    }

    spin_unlock_bh(&__dev_db_lock);
}


int sx_dev_db_dump(struct seq_file *m, void *v)
{
    const char    *bus_name;
    struct sx_dev *dev;
    int            i;

    seq_printf(m, "Device Database\n");
    seq_printf(m, "-------------------------------------------------------------------------------\n\n");
    seq_printf(m, "Predefined device IDs: %s\n\n", ((predefined_num_of_pci_devices > 0) ? "yes" : "no"));

    seq_printf(m, "%-3s   %-16s\n", "ID", "Bus-Name");
    seq_printf(m, "......................\n");
    spin_lock_bh(&__dev_db_lock);

    for (i = 0; i < MAX_NUM_OF_REMOTE_SWITCHES; i++) {
        if (!DEV_ID_IS_VALID(i) || !__dev_db[i].dev) {
            continue;
        }

        dev = __dev_db[i].dev;
        if (dev->pdev) {
            bus_name = dev_name(&dev->pdev->dev);
        } else {
            bus_name = DUMMY_BUS_NAME;
        }

        seq_printf(m, "%-3d   %-16s\n", i, bus_name);
    }
    spin_unlock_bh(&__dev_db_lock);

    seq_printf(m, "\n\n");
    return 0;
}
