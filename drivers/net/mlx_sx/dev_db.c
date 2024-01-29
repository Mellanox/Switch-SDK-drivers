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
#include <linux/rwsem.h>
#include <linux/rwlock_types.h>
#include <linux/rwlock.h>
#include "dev_db.h"

static char *predefined_dev_pci_bus[MAX_NUM_OF_REMOTE_SWITCHES] = { 0 };
static int   predefined_num_of_pci_devices = 0;
module_param_array(predefined_dev_pci_bus, charp, &predefined_num_of_pci_devices,  0444);

struct sx_dev_db_entry {
    struct list_head  dev_list; /* list of valid devices */
    struct sx_dev    *dev;
    const char       *bus_name;
    atomic_t          refcnt;
    struct completion delete_completion;
};
static struct sx_dev_db_entry __dev_db[MAX_NUM_OF_REMOTE_SWITCHES];
static LIST_HEAD(__valid_devices_list);
static u32 __num_of_valid_devices = 0;

/* Device database functions are called from several places: interrupt, user and kthread contexts.
 * Database updates are ONLY from user/kthread contexts. Readers, on the other hand, are from several contexts.
 *
 * Therefore we need two locks: RW spin-lock (fast-path) and RW semaphore (slow-path).
 * When updating the database, both locks are acquired.
 * When reading from the database, only the relevant lock will be called:
 * If it is a reader that can run in interrupt context, the function will use the fast-path lock.
 * If the reader is only from user/kthread context, the function will use the slow-path lock.
 */
static rwlock_t            __dev_db_fastpath_lock;
static struct rw_semaphore __dev_db_slowpath_lock;

#define DUMMY_BUS_NAME "<none>"

static void __write_lock(void)
{
    /* read the comment at the top of the file */

    /*
     * 1. database updater call this function to lock the database.
     * 2. updater MUST NOT be in interrupt context.
     * 3. lock order MUST be: acquire slow-path and then fast-path.
     **/
    down_write(&__dev_db_slowpath_lock);
    write_lock_bh(&__dev_db_fastpath_lock);
}

static void __write_unlock(void)
{
    /* read the comment at the top of the file */

    /*
     * 1. database updater call this function to unlock the database.
     * 2. updater MUST NOT be in interrupt context.
     * 3. unlock order MUST be: release fast-path and then slow-path.
     **/
    write_unlock_bh(&__dev_db_fastpath_lock);
    up_write(&__dev_db_slowpath_lock);
}

static void __read_lock_fastpath(void)
{
    /* read the comment at the top of the file */

    /*
     * 1. database reader call this function before reading from the database.
     * 2. reader can run from any context: interrupt, user, kthread.
     **/
    read_lock_bh(&__dev_db_fastpath_lock);
}

static void __read_unlock_fastpath(void)
{
    /* read the comment at the top of the file */

    /*
     * 1. database reader call this function after reading from the database.
     * 2. reader can run from any context: interrupt, user, kthread.
     **/
    read_unlock_bh(&__dev_db_fastpath_lock);
}

static void __read_lock_slowpath(void)
{
    /* read the comment at the top of the file */

    /*
     * 1. database reader call this function before reading from the database.
     * 2. reader MUST NOT run from interrupt context.
     **/
    down_read(&__dev_db_slowpath_lock);
}

static void __read_unlock_slowpath(void)
{
    /* read the comment at the top of the file */

    /*
     * 1. database reader call this function after reading from the database.
     * 2. reader MUST NOT run from interrupt context.
     **/
    up_read(&__dev_db_slowpath_lock);
}

/* MUST be called from read/write lock and only if entry is valid */
static void __add_ref(struct sx_dev_db_entry *entry)
{
    WARN_ON(atomic_read(&entry->refcnt) <= 0);
    atomic_inc(&entry->refcnt);
}

/* may be called even without locking, as long as entry is valid */
static void __dec_ref(struct sx_dev_db_entry *entry)
{
    WARN_ON(atomic_read(&entry->refcnt) <= 0);
    if (atomic_dec_and_test(&entry->refcnt)) {
        complete(&entry->delete_completion);
    }
}

static int __sx_dev_db_map_dev_id_to_bus(sxd_dev_id_t dev_id, const char *bus_name)
{
    int err = 0;

    /* this function MUST NOT be called from interrupt context */

    __write_lock();

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
    __write_unlock();
    return err;
}

static int __sx_dev_db_assign_predefined_devices(void)
{
    char dev_bus[128];
    int  dev_id;
    int  i, rc, err = 0;

    printk(KERN_INFO "Number of predefined PCI devices (Bus-to-Device_ID) is %d\n", predefined_num_of_pci_devices);

    for (i = 0; i < predefined_num_of_pci_devices; i++) {
        if (strlen(predefined_dev_pci_bus[i]) >= sizeof(dev_bus)) {
            printk(KERN_ERR "Predefined device: name is too long on iteration %d\n", i);
            err = -EINVAL;
            goto out;
        }

        rc = sscanf(predefined_dev_pci_bus[i], "%d@%s", &dev_id, dev_bus);
        if (rc != 2) {
            printk(KERN_ERR "Predefined device: name is invalid on iteration %d\n", i);
            err = -EINVAL;
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

out:
    return err;
}

int dev_db_init(void)
{
    rwlock_init(&__dev_db_fastpath_lock);
    init_rwsem(&__dev_db_slowpath_lock);
    return __sx_dev_db_assign_predefined_devices();
}

void dev_db_deinit(void)
{
    int i;

    /* this function MUST NOT be called from interrupt context */

    __write_lock();

    for (i = 0; i < MAX_NUM_OF_REMOTE_SWITCHES; i++) {
        if (__dev_db[i].bus_name) {
            kfree(__dev_db[i].bus_name);
            __dev_db[i].bus_name = NULL;
        }
    }

    __write_unlock();
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

    for (i = 0; i < MAX_NUM_OF_REMOTE_SWITCHES; i++) {
        if (DEV_ID_IS_VALID(i) && __dev_db[i].bus_name && strstr(bus_name, __dev_db[i].bus_name)) {
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

bool sx_core_has_predefined_devices(void)
{
    return predefined_num_of_pci_devices > 0;
}
EXPORT_SYMBOL(sx_core_has_predefined_devices);

int sx_dev_db_add_device(struct sx_dev *dev)
{
    const char  *bus_name = DUMMY_BUS_NAME;
    sxd_dev_id_t dev_id;
    int          err = 0;

    /* this function MUST NOT be called from interrupt context */

    if (!dev) {
        printk(KERN_ERR "Add device to database: invalid device\n");
        return -EINVAL;
    }

    /* not always a PCI device is attached to the SX device:
     * On OOB system no PCI device is found on the bus so we create a non-PCI device to work with.
     *
     * In case a PCI is attached to the SX device, take the bus name from it.
     */
    if (dev->pdev) {
        bus_name = dev_name(&dev->pdev->dev);
    }

    __write_lock();

    if (sx_core_has_predefined_devices()) { /* in this case, each PCI device's bus is associated with ID */
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
    __num_of_valid_devices++;
    __dev_db[dev_id].dev = dev;
    dev->device_id = dev_id;
    atomic_set(&__dev_db[dev_id].refcnt, 1);
    init_completion(&__dev_db[dev_id].delete_completion);

    printk(KERN_INFO "Add device to database: [id=%u, bus=%s]\n", dev_id, bus_name);

out:
    __write_unlock();
    return err;
}

int sx_dev_db_remove_device(struct sx_dev *dev)
{
    const char *bus_name = DUMMY_BUS_NAME;
    int         err = 0;

    /* this function MUST NOT be called from interrupt context */

    if (!dev) {
        printk(KERN_ERR "Remove device from database: invalid device\n");
        return -EINVAL;
    }

    /* coverity[result_independent_of_operands] */
    if (!DEV_ID_IS_VALID(dev->device_id)) {
        printk(KERN_ERR "Remove device from database: invalid device ID (id=%u)\n", dev->device_id);
        return -EINVAL;
    }

    if (dev->pdev) {
        bus_name = dev_name(&dev->pdev->dev);
    }

    __write_lock();

    if (!__dev_db[dev->device_id].dev) {
        __write_unlock();
        printk(KERN_ERR "Remove device from database: device not found\n");
        err = -ENODEV;
        goto out;
    }

    /* decrement the reference we took when the device was added */
    __dec_ref(&__dev_db[dev->device_id]);

    if (__dev_db[dev->device_id].dev == __dev_db[DEFAULT_DEVICE_ID].dev) {
        printk(KERN_NOTICE "Removing the default device\n");
        __dev_db[DEFAULT_DEVICE_ID].dev = NULL;
    }

    list_del(&__dev_db[dev->device_id].dev_list);
    __num_of_valid_devices--;

    /* at this point, the device is out of the database which means that any caller that
     * will try lookup for the device will get a NULL pointer. however, we cannot return
     * from this function until there are no references to the device because the caller
     * of this function wants to delete the device. this is the time to release the
     * fastpath lock and then wait until the last reference is released.
     * */
    write_unlock_bh(&__dev_db_fastpath_lock);

    /* waiting for 'delete_completion' - it will be signaled only when the last reference
     * of the device is released. the waiting takes place within the slowpath lock because
     * we want to make sure that __dev_db[dev_id] is not occupied in another flow of 'add_device'
     * that will override the entry while we're waiting for the last reference to be released.
     */
    wait_for_completion_interruptible(&__dev_db[dev->device_id].delete_completion);

    /* only now, where we're sure there are no references to the device, we can assign it to NULL */
    __dev_db[dev->device_id].dev = NULL;

    printk(KERN_INFO "Remove device from database: [id=%u, bus=%s]\n", dev->device_id, bus_name);
    up_write(&__dev_db_slowpath_lock); /* release the slowpath write lock */

out:
    return err;
}

/* this function is used only for legacy (when sx_core_has_predefined_devices() == false):
 * we take the only device we have (that has the DEFAULT_DEVICE_ID) and assign it
 * an additional device ID.
 */
int sx_dev_db_reassign_dev_id_to_default_device(sxd_dev_id_t dev_id)
{
    int err = 0;

    /* this function MUST NOT be called from interrupt context */

    if (sx_core_has_predefined_devices() || DEFAULT_DEVICE_ID_CHECK(dev_id)) {
        /* two cases when we just return and do nothing:
         * 1. sx_core_has_predefined_devices() is true ==> There is no default device anymore.
         * 2. OOB backbone (SwitchX) PCI probe reached here with device id 254, we don't want it to be the default.
         */

        return 0;
    }

    /* coverity[result_independent_of_operands] */
    if (!DEV_ID_IS_VALID(dev_id)) {
        printk(KERN_ERR "device ID %u is no valid\n", dev_id);
        return -EINVAL;
    }

    __write_lock();

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
    atomic_set(&__dev_db[dev_id].refcnt, 1);
    init_completion(&__dev_db[dev_id].delete_completion);
    list_del(&__dev_db[DEFAULT_DEVICE_ID].dev_list);
    list_add_tail(&__dev_db[dev_id].dev_list, &__valid_devices_list);

    printk(KERN_INFO "Default device has a new device ID: %u\n", dev_id);

out:
    __write_unlock();
    return err;
}

struct sx_dev * sx_dev_db_get_dev_by_id(sxd_dev_id_t dev_id)
{
    struct sx_dev *dev = NULL;

    /* this function can run from any context: interrupt, user, kthread */

    /* coverity[result_independent_of_operands] */
    if (!DEV_ID_IS_VALID(dev_id)) {
        printk(KERN_ERR "cannot find device %d - invalid device ID\n", (int)dev_id);
        return NULL;
    }

    /* no default device when driver is loaded with predefined PCI buses (multi ASICs PCI) */
    WARN_ON(DEFAULT_DEVICE_ID_CHECK(dev_id) && sx_core_has_predefined_devices());

    __read_lock_fastpath();
    dev = __dev_db[dev_id].dev;
    __read_unlock_fastpath();

    return dev;
}

struct sx_dev * sx_dev_db_get_default_device(void)
{
    return sx_dev_db_get_dev_by_id(DEFAULT_DEVICE_ID);
}

/* this function is running a callback function for each one of the valid
 * devices. function algorithm:
 * 1. get the slowpath read lock
 * 2. allocate an array of 'struct sx_dev_db_entry' pointers with size == number of valid devices
 * 3. iterate on the valid devices list and for each one of them:
 *    a. add reference - no one can remove the entry until reference is decremented.
 *    b. add the 'struct sx_dev_db_entry' to the local array.
 * 4. release the slowpath read lock
 *
 * at this point, the array has valid 'struct sx_dev_db_entry' entries, each one of them
 * has a reference so no one can change the 'dev' pointer within them.
 *
 * 5. iterate the array of entries and run the callback for each device (or until a callback
 *    explicitly breaks the iteration).
 * 6. iterate the array of entries and decrement the references for each one of them.
 */
int sx_dev_db_iterate(sx_dev_db_iterator_cb_t iter_cb, void *context)
{
    struct sx_dev_db_entry *iter, **iter_arr;
    int                     err = 0, i = 0, num_of_devices;
    bool                    cb_ret;

    /* this function MUST NOT be called from interrupt context */

    __read_lock_slowpath();

    num_of_devices = __num_of_valid_devices;
    iter_arr = (struct sx_dev_db_entry**)kmalloc(sizeof(struct sx_dev_db_entry*) * num_of_devices,
                                                 GFP_KERNEL);
    if (!iter_arr) {
        printk(KERN_ERR "no memory to iterate device database\n");
        err = -ENOMEM;
    } else {
        list_for_each_entry(iter, &__valid_devices_list, dev_list) {
            __add_ref(iter); /* this will keep the entry valid even if we use 'iter' out of lock */
            iter_arr[i++] = iter;
        }
    }

    __read_unlock_slowpath();

    if (err) {
        goto out;
    }

    /* now, after getting references to all devices, we can iterate them without lock */

    /* running the callback for each one of the devices (or one of the callbacks tells us to stop) */
    for (i = 0; i < num_of_devices; i++) {
        cb_ret = iter_cb(iter_arr[i]->dev, context);
        if (!cb_ret) { /* callback may decide to terminate the iteration */
            break;
        }
    }

    /* release the reference of each one of the devices */
    for (i = 0; i < num_of_devices; i++) {
        __dec_ref(iter_arr[i]);
    }

    kfree(iter_arr);

out:
    return err;
}

int sx_dev_db_dump(struct seq_file *m, void *v, void *context)
{
    const char    *bus_name;
    struct sx_dev *dev;
    int            i;

    /* this function MUST NOT be called from interrupt context */

    seq_printf(m, "Device Database\n");
    seq_printf(m, "-------------------------------------------------------------------------------\n\n");
    seq_printf(m, "Predefined device IDs: %s\n\n", (sx_core_has_predefined_devices() ? "yes" : "no"));

    seq_printf(m, "%-3s   %-16s\n", "ID", "Bus-Name");
    seq_printf(m, "......................\n");

    __read_lock_slowpath();

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
    __read_unlock_slowpath();

    seq_printf(m, "\n\n");
    return 0;
}
