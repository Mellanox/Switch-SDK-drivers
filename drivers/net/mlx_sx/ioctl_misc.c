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
#include "sx_af_counters.h"

static bool g_sdk_health_en[MAX_NUM_OF_REMOTE_SWITCHES + 1] = {0};
static DEFINE_MUTEX(sdk_health_mutex);

bool sdk_health_test_and_disable(uint8_t dev_id)
{
    bool ret = false;

    /* coverity[result_independent_of_operands] */
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
    /* coverity[result_independent_of_operands] */
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

    /* coverity[result_independent_of_operands] */
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
    struct sx_dev  *dev;
    struct sx_priv *priv;

    dev = sx_core_ioctl_get_dev(DEFAULT_DEVICE_ID);
    if (!dev) {
        return -ENODEV;
    }

    priv = sx_priv(dev);
    return copy_to_user((void*)data, (void*)&priv->dev_cap, sizeof(priv->dev_cap));
}


long ctrl_cmd_issu_fw(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev *dev;
    int            err = 0;
    u8             status = 0;
    u8             retry_num = 0;

    dev = sx_core_ioctl_get_dev(DEFAULT_DEVICE_ID);
    if (!dev) {
        return -ENODEV;
    }

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
    return sx_core_ioctl_enable_swid(NULL, data);
}


long ctrl_cmd_disable_swid(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_swid_details swid_data;
    struct sx_dev         *dev;
    struct sx_priv        *priv;
    int                    err;

    printk(KERN_DEBUG PFX "ioctl disable_swid called\n");
    err = copy_from_user(&swid_data, (void*)data, sizeof(swid_data));
    if (err) {
        return err;
    }

    dev = sx_core_ioctl_get_dev(swid_data.dev_id);
    if (!dev) {
        return -ENODEV;
    }

    priv = sx_priv(dev);

    spin_lock(&priv->profile.profile_lock);
    if (!priv->profile.pci_profile_set || (swid_data.swid >= NUMBER_OF_SWIDS) ||
        !sx_bitmap_test(&priv->swid_bitmap, swid_data.swid)) {
        spin_unlock(&priv->profile.profile_lock);
        return -EINVAL;
    }

    spin_unlock(&priv->profile.profile_lock);
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

    err = copy_from_user(&admin_status_data, (void*)data, sizeof(admin_status_data));
    if (err) {
        return err;
    }

    dev = sx_core_ioctl_get_dev(admin_status_data.dev_id);
    if (!dev) {
        return -ENODEV;
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

    err = copy_from_user(&ptp_mode, (void*)data, sizeof(ptp_mode));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(DEFAULT_DEVICE_ID);
    if (!dev) {
        return -ENODEV;
    }

    if ((ptp_mode.ptp_mode != KU_PTP_MODE_EVENTS) &&
        (ptp_mode.ptp_mode != KU_PTP_MODE_POLLING) &&
        (ptp_mode.ptp_mode != KU_PTP_MODE_DISABLED)) {
        err = -EINVAL;
        goto out;
    }

    if (ptp_mode.ptp_mode != KU_PTP_MODE_DISABLED) {
        err = sx_core_ptp_dev_init(sx_priv(dev), ptp_mode.ptp_mode);
        if (err) {
            printk(KERN_ERR PFX "__sx_core_ptp_init failed, err:%d\n", err);
        }
    } else { /* ptp_mode.ptp_mode == KU_PTP_MODE_DISABLED */
        err = sx_core_ptp_dev_cleanup(sx_priv(dev));
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

    err = copy_from_user(&node_desc, (struct ku_ib_node_description*)data, sizeof(node_desc));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(node_desc.dev_id);
    if (!dev) {
        return -ENODEV;
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

    err = copy_from_user(&event_params, (struct ku_ib_node_description*)data, sizeof(event_params));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(DEFAULT_DEVICE_ID);
    if (!dev) {
        return -ENODEV;
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

    dev = sx_core_ioctl_get_dev(DEFAULT_DEVICE_ID);
    if (!dev) {
        return -ENODEV;
    }

    if (!dev->pdev) {
        printk(KERN_ERR "ISSU-in-progress: PCI device is not attached\n");
        err = -ENODEV;
        goto out;
    }

    err = sx_core_dispatch_event(dev, SX_DEV_EVENT_ISSU_START, NULL);

    if (err) {
        printk(KERN_ERR PFX "ISSU event failed, err:%d\n", err);
        goto out;
    } else {
        kobject_uevent(&dev->pdev->dev.kobj, event); /* tell HW management that ASIC is accessible/inaccessible */
    }

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
 * The reason we return current->tgid:
 * 1. When client calls sxd_memory_map to create shared memory between kernel and application,
 *    the kernel mmap implementation is using current->tgid, which is the real PID of the client
 *    process, no matter the client process is inside a docker container or on a host.
 * 2. Inside a docker container, the getpid system call returns PID from the docker
 *    PID name space, but not the real PID. We need to provide a generic way for the client
 *    process to get the real PID, which should work for both docker and non-docker scenarios.
 */
long ctrl_cmd_client_pid_get(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_client_pid_get client_pid;
    int                      err;

    client_pid.pid = current->tgid;
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

long ctrl_cmd_accuflow_set(struct file *file, unsigned int cmd, unsigned long data)
{
    int                                err = 0;
    struct ku_accuflow_counters_params params;

    err = copy_from_user(&params, (void*)data, sizeof(params));
    if (err) {
        goto out;
    }

    switch (params.op) {
    case KU_ACCUFLOW_COUNTERS_PARAMS_OP_INIT_E:
        err = sx_af_counters_init(&params);
        goto out;

    case KU_ACCUFLOW_COUNTERS_PARAMS_OP_DEINIT_E:
        err = sx_af_counters_deinit();
        goto out;

    case KU_ACCUFLOW_COUNTERS_PARAMS_OP_TRASACTION_RESERVATION_E:
        err = sx_af_counters_tr_reservation_set(&params.op_data.tr_reservation);
        goto out;

    default:
        err = sx_af_counters_user_job_schedule(&params);
        if ((err == 0) && (params.op == KU_ACCUFLOW_COUNTERS_PARAMS_OP_READ_E)) {
            err = copy_to_user((void*)data, &params, sizeof(params));
        }
        goto out;
    }

out:
    return err;
}

long ctrl_cmd_port_module_update(struct file *file, unsigned int cmd, unsigned long data)
{
    int                                 err = 0;
    struct sx_dev                      *dev;
    struct sx_priv                     *priv;
    struct ku_port_module_update_params params;
    unsigned long                       flags;
    bool                                port_up = false;

    dev = sx_core_ioctl_get_dev(DEFAULT_DEVICE_ID);
    if (!dev) {
        return -ENODEV;
    }

    priv = sx_priv(dev);

    err = copy_from_user(&params, (void*)data, sizeof(params));
    if (err) {
        goto out;
    }

    if ((params.admin_status == SXD_PAOS_ADMIN_STATUS_UP_E) ||
        (params.admin_status == SXD_PAOS_ADMIN_STATUS_UP_ONCE_E)) {
        port_up = true;
    }

    if (!port_up) {
        spin_lock_irqsave(&priv->db_lock, flags);
        priv->local_port_state[params.local_port] = params.admin_status;
        spin_unlock_irqrestore(&priv->db_lock, flags);
    }

    err = sx_core_update_module_power_mode(dev, params.slot_id, params.module_id, port_up);
    if (err) {
        printk(KERN_ERR PFX "Failed in sx_core_update_module_power_mode.\n");
        goto out;
    }

    if (port_up) {
        spin_lock_irqsave(&priv->db_lock, flags);
        priv->local_port_state[params.local_port] = params.admin_status;
        spin_unlock_irqrestore(&priv->db_lock, flags);
    }

    mutex_lock(&priv->module_access_mutex);
    err = sx_core_set_module(dev, params.slot_id, params.module_id, 1, 0);
    if (err) {
        printk(KERN_ERR PFX "Failed in sx_core_set_module.\n");
        mutex_unlock(&priv->module_access_mutex);
        goto out;
    }
    mutex_unlock(&priv->module_access_mutex);

out:
    return err;
}

long ctrl_cmd_module_support_enable(struct file *file, unsigned int cmd, unsigned long data)
{
    int                  err = 0;
    union sx_event_data *module_support_event_data = NULL;
    struct sx_dev       *dev;

    dev = sx_core_ioctl_get_dev(DEFAULT_DEVICE_ID);
    if (!dev) {
        return -ENODEV;
    }

    module_support_event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!module_support_event_data) {
        err = -ENOMEM;
        goto out;
    }

    module_support_event_data->module_support_set.module_support_en = 1;

    sx_core_dispatch_event(dev, SX_DEV_EVENT_MODULE_SUPPORT_SET, module_support_event_data);

    kfree(module_support_event_data);

out:
    return err;
}

static int sx_core_ioctl_port_module_map_set(struct sx_dev *dev, struct ku_port_module_map_set_params *params)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    int             i = 0, j = 0;
    uint8_t         module_id = params->module_id;
    uint8_t         slot_id = params->slot_id;
    uint16_t        local_port = params->local_port;
    unsigned long   flags;
    uint16_t        phy_port_max = 0;
    uint8_t         locked = 0;

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        printk(KERN_ERR PFX "Failed to get max number of phy ports.\n");
        err = -EINVAL;
        goto out;
    }

    if (local_port > phy_port_max) {
        net_err_ratelimited(PFX "Local port %d is invalid. (MAX %d).\n",
                            local_port, phy_port_max);
        err = -EINVAL;
        goto out;
    }

    if ((slot_id >= MAX_SLOT_NUM) || (module_id >= MAX_MODULE_NUM)) {
        err = -EINVAL;
        net_err_ratelimited(PFX "slot id %d or module id %d is out of range.\n", slot_id, module_id);
        goto out;
    }

    spin_lock_irqsave(&priv->db_lock, flags);
    locked = 1;

    if (params->is_set) {
        /* Set mapping */
        for (i = 0; i < priv->modules_to_port_map_count[slot_id][module_id]; i++) {
            if (priv->module_to_ports_map[slot_id][module_id][i] == local_port) {
                goto out;
            }
        }

        if (priv->modules_to_port_map_count[slot_id][module_id] == MAX_LANE_NUM_PER_MODULE) {
            /* modules to port map is full */
            err = -EPERM;
            printk(KERN_ERR PFX "Modules to port map is full.\n");
            goto out;
        }
        priv->module_to_ports_map[slot_id][module_id][priv->modules_to_port_map_count[slot_id][module_id]] =
            local_port;
        priv->modules_to_port_map_count[slot_id][module_id]++;
        priv->local_to_module_map[local_port] = module_id;
        priv->local_to_slot_map[local_port] = slot_id;
    } else {
        /* Delete mapping */
        if (((priv->local_to_slot_map[local_port] != slot_id) ||
             (priv->local_to_module_map[local_port] != module_id)) ||
            (priv->modules_to_port_map_count[slot_id][module_id] == 0)) {
            goto out;
        }
        for (i = 0; i < priv->modules_to_port_map_count[slot_id][module_id]; i++) {
            if (priv->module_to_ports_map[slot_id][module_id][i] == local_port) {
                for (j = i; j < priv->modules_to_port_map_count[slot_id][module_id] - 1; j++) {
                    priv->module_to_ports_map[slot_id][module_id][j] =
                        priv->module_to_ports_map[slot_id][module_id][j + 1];
                }
                priv->modules_to_port_map_count[slot_id][module_id]--;
                break;
            }
        }
    }

out:
    if (locked) {
        spin_unlock_irqrestore(&priv->db_lock, flags);
    }
    return err;
}

long ctrl_cmd_port_module_map_set(struct file *file, unsigned int cmd, unsigned long data)
{
    int                             err = 0;
    struct sx_dev                  *dev;
    ku_port_module_map_set_params_t params;

    err = copy_from_user(&params, (void*)data, sizeof(params));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(params.dev_id);
    if (!dev) {
        return -ENODEV;
    }

    err = sx_core_ioctl_port_module_map_set(dev, &params);
    if (err) {
        goto out;
    }

out:
    return err;
}
