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
#include <linux/delay.h>
#include <linux/sched.h>

#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/kernel_user.h>
#include "sx.h"
#include "alloc.h"
#include "ptp.h"
#include "sgmii.h"
#include "ioctl_internal.h"
#include "bulk_cntr_event.h"
#include "bulk_cntr_db.h"

static bool g_sdk_health_en[MAX_NUM_OF_REMOTE_SWITCHES + 1] = {0};
static DEFINE_MUTEX(sdk_health_mutex);

bool sdk_health_test_and_disable(uint8_t dev_id)
{
    bool ret = false;

    if ((dev_id == 0) || (dev_id >= MAX_NUM_OF_REMOTE_SWITCHES)) {
        return false;
    }

    mutex_lock(&sdk_health_mutex);
    ret = g_sdk_health_en[dev_id];
    g_sdk_health_en[dev_id] = 0;
    mutex_unlock(&sdk_health_mutex);

    return ret;
}


void sdk_health_set(uint8_t dev_id, bool is_enabled)
{
    if ((dev_id == 0) || (dev_id > MAX_NUM_OF_REMOTE_SWITCHES)) {
        return;
    }

    mutex_lock(&sdk_health_mutex);
    g_sdk_health_en[dev_id] = is_enabled;
    mutex_unlock(&sdk_health_mutex);
}

bool sdk_health_get(uint8_t dev_id)
{
    bool is_enabled;

    if ((dev_id == 0) || (dev_id > MAX_NUM_OF_REMOTE_SWITCHES)) {
        return false;
    }

    mutex_lock(&sdk_health_mutex);
    is_enabled = g_sdk_health_en[dev_id];
    mutex_unlock(&sdk_health_mutex);
    return is_enabled;
}

long ctrl_cmd_get_capabilities(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev *dev;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);
    return copy_to_user((void*)data, (void*)&dev->dev_cap, sizeof(dev->dev_cap));
}


long ctrl_cmd_issu_fw(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev *dev;
    int            err = 0;
    u8             status = 0;
    u8             retry_num = 0;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);
#define NUM_OF_QUERIES 20
    /* Verify ISSU FW state is idle */
    err = sx_ISSU_FW_STATUS_GET(dev, &status);
    if (err) {
        printk(KERN_ERR PFX "Fail to get ISSU FW state.\n");
        goto out;
    }

    if (status) {
        printk(KERN_ERR PFX "Fail to start ISSU FW: Cannot start while ISSU FW ongoing.\n");
        err = -EPERM;
        goto out;
    }

    /* Perform ISSU FW */
    err = sx_ISSU_FW_START(dev);
    if (err) {
        printk(KERN_ERR PFX "Fail to start ISSU FW.\n");
        goto out;
    }

    /* Wait for ISSU FW to end */
    while (retry_num < NUM_OF_QUERIES) {
        err = sx_ISSU_FW_STATUS_GET(dev, &status);
        if (err) {
            printk(KERN_ERR PFX "Fail to get ISSU FW state.\n");
            goto out;
        }
        if (status) {
            msleep(10);
            retry_num++;
        } else {
            printk(KERN_INFO PFX "ISSU FW DONE.\n");
            break;
        }
    }

    if (retry_num >= NUM_OF_QUERIES) {
        printk(KERN_ERR PFX "ISSU FW timeout.\n");
        err = -ETIME;
        goto out;
    }

out:
    return err;
}


long ctrl_cmd_enable_swid(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev *dev;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);
    return sx_core_ioctl_enable_swid(dev, data);
}


long ctrl_cmd_disable_swid(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_swid_details swid_data;
    struct sx_dev         *dev;
    int                    err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    printk(KERN_DEBUG PFX "ioctl disable_swid called\n");
    err = copy_from_user(&swid_data, (void*)data, sizeof(swid_data));
    if (err) {
        return err;
    }

    spin_lock(&dev->profile_lock);
    if (!dev->profile_set || (swid_data.swid >= NUMBER_OF_SWIDS) ||
        !sx_bitmap_test(&sx_priv(dev)->swid_bitmap, swid_data.swid)) {
        spin_unlock(&dev->profile_lock);
        return -EINVAL;
    }

    spin_unlock(&dev->profile_lock);
    sx_disable_swid(dev, swid_data.swid);
    return 0;
}

#ifdef SW_PUDE_EMULATION
/* PUDE WA for NOS (PUDE events are handled by SDK). Needed for BU. */
long ctrl_cmd_set_port_admin_status(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_admin_status_data admin_status_data;
    struct sx_dev              *dev;
    unsigned long               flags;
    int                         err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&admin_status_data, (void*)data, sizeof(admin_status_data));
    if (err) {
        return err;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    sx_priv(dev)->admin_status_sysport_db[admin_status_data.sysport] = admin_status_data.admin_status;
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    return 0;
}
#endif /* SW_PUDE_EMULATION */


long ctrl_cmd_set_ptp_mode(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_ptp_mode ptp_mode;
    struct sx_dev     *dev;
    int                err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&ptp_mode, (void*)data, sizeof(ptp_mode));
    if (err) {
        goto out;
    }

    if ((ptp_mode.ptp_mode != KU_PTP_MODE_EVENTS) &&
        (ptp_mode.ptp_mode != KU_PTP_MODE_POLLING) &&
        (ptp_mode.ptp_mode != KU_PTP_MODE_DISABLED)) {
        err = -EINVAL;
        goto out;
    }

    if (ptp_mode.ptp_mode != KU_PTP_MODE_DISABLED) {
        err = sx_core_ptp_init(sx_priv(dev), ptp_mode.ptp_mode);
        if (err) {
            printk(KERN_ERR PFX "__sx_core_ptp_init failed, err:%d\n", err);
        }
    } else { /* ptp_mode.ptp_mode == KU_PTP_MODE_DISABLED */
        err = sx_core_ptp_cleanup(sx_priv(dev));
        if (err) {
            printk(KERN_ERR PFX "__sx_core_ptp_cleanup failed, err:%d\n", err);
        }
    }

out:
    return err;
}


static uint8_t __sx_is_default_device(int dev_id)
{
    int default_dev_id;
    int ret;

    if (is_sgmii_supported()) { /* Chassis managed by OOB network */
        ret = sgmii_default_dev_id_get(&default_dev_id);
        return (ret) ? 0 : (dev_id == default_dev_id);
    }

    /* Chassis managed by PCI & in-band network */
    return (sx_glb.sx_dpt.dpt_info[dev_id].cmd_path == DPT_PATH_PCI_E);
}


long ctrl_cmd_set_sw_ib_node_desc(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_ib_node_description node_desc;
    union sx_event_data          *event_data;
    struct sx_dev                *dev;
    int                           err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&node_desc, (struct ku_ib_node_description*)data, sizeof(node_desc));
    if (err) {
        goto out;
    }

    if (!__sx_is_default_device(node_desc.dev_id)) {
        /* setting node description only on chassis's default device. ignoring silently. */
        goto out;
    }

    printk(KERN_INFO "Setting node description on device %u\n", node_desc.dev_id);

    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        err = -ENOMEM;
        goto out;
    }

    event_data->node_desc_update.swid = node_desc.swid;
    memcpy(event_data->node_desc_update.NodeDescription,
           node_desc.node_description,
           sizeof(event_data->node_desc_update.NodeDescription));

    sx_core_dispatch_event(dev, SX_DEV_EVENT_NODE_DESC_UPDATE, event_data);
    kfree(event_data);

out:
    return err;
}


long ctrl_cmd_set_sw_ib_up_down(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_ib_swid_up_down event_params;
    union sx_event_data      *event_data;
    struct sx_dev            *dev;
    int                       err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&event_params, (struct ku_ib_node_description*)data, sizeof(event_params));
    if (err) {
        goto out;
    }

    printk(KERN_INFO "Setting swid [%u] device [%u] [%s]\n",
           event_params.swid,
           event_params.dev_id,
           event_params.up ? "up" : "down");

    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        err = -ENOMEM;
        goto out;
    }

    event_data->ib_swid_change.swid = event_params.swid;
    event_data->ib_swid_change.dev_id = event_params.dev_id;

    sx_core_dispatch_event(dev, event_params.up ? SX_DEV_EVENT_IB_SWID_UP : SX_DEV_EVENT_IB_SWID_DOWN, event_data);
    kfree(event_data);

out:
    return err;
}


long ctrl_cmd_bulk_cntr_tr_add(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_bulk_cntr_transaction_add bulk_cntr_tr_add;
    int                                 err;

    err = copy_from_user(&bulk_cntr_tr_add, (void*)data, sizeof(bulk_cntr_tr_add));
    if (err) {
        goto out;
    }

    err = bulk_cntr_db_add(&bulk_cntr_tr_add);

out:
    return err;
}


long ctrl_cmd_bulk_cntr_tr_del(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_bulk_cntr_transaction bulk_cntr_tr_del;
    int                             err;

    err = copy_from_user(&bulk_cntr_tr_del, (void*)data, sizeof(bulk_cntr_tr_del));
    if (err) {
        goto out;
    }

    err = bulk_cntr_db_del(bulk_cntr_tr_del.client_pid, bulk_cntr_tr_del.buffer_id);

out:
    return err;
}


long ctrl_cmd_bulk_cntr_tr_cancel(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_bulk_cntr_transaction bulk_cntr_tr_cancel;
    int                             err;

    err = copy_from_user(&bulk_cntr_tr_cancel, (void*)data, sizeof(bulk_cntr_tr_cancel));
    if (err) {
        goto out;
    }

    err = bulk_cntr_db_cancel(bulk_cntr_tr_cancel.client_pid, bulk_cntr_tr_cancel.buffer_id);

out:
    return err;
}


long ctrl_cmd_bulk_cntr_tr_ack(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_bulk_cntr_transaction_ack bulk_cntr_tr_ack;
    int                                 err;

    err = copy_from_user(&bulk_cntr_tr_ack, (void*)data, sizeof(bulk_cntr_tr_ack));
    if (err) {
        goto out;
    }

    err = sx_bulk_cntr_handle_ack(&bulk_cntr_tr_ack.event_id, bulk_cntr_tr_ack.buffer_id);
    if (err) {
        goto out;
    }

out:
    return err;
}


long ctrl_cmd_send_issu_notification(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev *dev = NULL;
    int            err = 0, event = 0;

    /* 'data' is not a pointer but a boolean value:
     * 0 - ISSU finished, FW/ASIC is accessible
     * 1 - ISSU started, FW/ASIC is inaccessible
     */
    event = (!!data) ? KOBJ_OFFLINE : KOBJ_ONLINE;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);
    if (!dev->pdev) {
        printk(KERN_ERR "ISSU-in-progress: PCI device is not attached\n");
        err = -ENODEV;
        goto out;
    }

    kobject_uevent(&dev->pdev->dev.kobj, event); /* tell HW management that ASIC is accessible/inaccessible */

out:
    return err;
}

long ctrl_cmd_bulk_cntr_tr_in_progress(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_bulk_cntr_transaction bulk_cntr_tr_in_progress;
    int                             err;

    err = copy_from_user(&bulk_cntr_tr_in_progress, (void*)data, sizeof(bulk_cntr_tr_in_progress));
    if (err) {
        goto out;
    }

    err = bulk_cntr_db_in_progress(&bulk_cntr_tr_in_progress, (void*)data);
    if (err) {
        goto out;
    }

out:
    return err;
}

long ctrl_cmd_bulk_cntr_per_prio_cache_set(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_bulk_cntr_per_prio_cache bulk_cntr_per_prio_cache;
    int                                err;

    err = copy_from_user(&bulk_cntr_per_prio_cache, (void*)data, sizeof(bulk_cntr_per_prio_cache));
    if (err) {
        goto out;
    }

    err = bulk_cntr_db_per_prio_cache_set(&bulk_cntr_per_prio_cache);

out:
    return err;
}

/*
 * The reason we return current->pid:
 * 1. When client calls sxd_memory_map to create shared memory between kernel and application,
 *    the kernel mmap implementation is using current->pid, which is the real PID of the client
 *    process, no matter the client process is inside a docker container or on a host.
 * 2. Inside a docker container, the getpid system call returns PID from the docker
 *    PID name space, but not the real PID. We need to provide a generic way for the client
 *    process to get the real PID, which should work for both docker and non-docker scenarios.
 */
long ctrl_cmd_client_pid_get(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_client_pid_get client_pid;
    int                      err;

    client_pid.pid = current->pid;
    err = copy_to_user((void*)data, &client_pid, sizeof(client_pid));
    if (err) {
        goto out;
    }

out:
    return err;
}

long ctrl_cmd_sdk_health_set(struct file *file, unsigned int cmd, unsigned long data)
{
    int                                err;
    struct ku_sdk_health_event_control sdk_health_ctl;

    err = copy_from_user(&sdk_health_ctl, (void*)data, sizeof(sdk_health_ctl));
    if (err) {
        goto out;
    }
    sdk_health_set(sdk_health_ctl.dev_id, sdk_health_ctl.enable);

out:
    return err;
}

long ctrl_cmd_sdk_health_get(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_sdk_health_event_control sdk_health_ctl;
    int                                err;

    err = copy_from_user(&sdk_health_ctl, (void*)data, sizeof(sdk_health_ctl));
    if (err) {
        goto out;
    }
    if (sdk_health_ctl.get_and_disable) {
        sdk_health_ctl.enable = sdk_health_test_and_disable(sdk_health_ctl.dev_id);
    } else {
        sdk_health_ctl.enable = sdk_health_get(sdk_health_ctl.dev_id);
    }
    err = copy_to_user((void*)data, &sdk_health_ctl, sizeof(sdk_health_ctl));
    if (err) {
        goto out;
    }

out:
    return err;
}
