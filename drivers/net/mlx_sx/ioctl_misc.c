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
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/pagemap.h>
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
#include "dev_init.h"

/*defines for host memory read ioctl*/
#define NUM_PAGES_IN_PAGE_ARRY                                   (SX_ICM_ALLOC_SIZE / PAGE_SIZE) /* 2M/4K = 512 */
#define MLX_TRACE_PAGE_OFFSET_IN_HOST_MEM_ALLOCATED_MAP_FA_PAGES 5
#define MLX_TRACE_MAX_PAGE_NUM                                   512
#define MAX_CHUNK_PAGE_NUM                                       (SX_ICM_CHUNK_LEN * NUM_PAGES_IN_PAGE_ARRY)

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
    sxd_dev_id_t    device_id = DEFAULT_DEVICE_ID;

    if (sx_core_has_predefined_devices()) {
        device_id = get_device_id_from_fd(file);
    }

    dev = sx_core_ioctl_get_dev(device_id);
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
    sxd_dev_id_t   device_id = DEFAULT_DEVICE_ID;

    if (sx_core_has_predefined_devices()) {
        device_id = get_device_id_from_fd(file);
    }

    dev = sx_core_ioctl_get_dev(device_id);
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
    return sx_core_ioctl_enable_swid(file, NULL, data);
}


long ctrl_cmd_disable_swid(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_swid_details swid_data;
    struct sx_dev         *dev;
    struct sx_priv        *priv;
    int                    err;

    pr_debug(PFX "ioctl disable_swid called\n");
    err = copy_from_user(&swid_data, (void*)data, sizeof(swid_data));
    if (err) {
        return err;
    }

    if (sx_core_has_predefined_devices()) {
        swid_data.dev_id = get_device_id_from_fd(file);
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

long ctrl_cmd_rearm_module_event(struct file *file, unsigned int cmd, unsigned long data)
{
    int                          err = 0;
    struct sx_dev               *dev;
    struct ku_rearm_module_event rearm;

    err = copy_from_user(&rearm, (void*)data, sizeof(rearm));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(rearm.dev_id);
    if (!dev) {
        return -ENODEV;
    }

    err =
        sx_core_rearm_module_event(dev, rearm.slot, rearm.module, (sxd_pmaos_e_t)rearm.gen_mode,
                                   &(rearm.ret));
    if (err) {
        printk(KERN_ERR PFX "Failed in sx_core_rearm_module_event.\n");
        goto out;
    }

    err = copy_to_user((void*)data, &rearm, sizeof(rearm));
    if (err) {
        goto out;
    }
out:
    return err;
}


long ctrl_cmd_set_ptp_mode(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_ptp_mode ptp_mode;
    struct sx_dev     *dev;
    int                err;
    sxd_dev_id_t       device_id = DEFAULT_DEVICE_ID;

    err = copy_from_user(&ptp_mode, (void*)data, sizeof(ptp_mode));
    if (err) {
        goto out;
    }

    if (sx_core_has_predefined_devices()) {
        device_id = get_device_id_from_fd(file);
    }

    dev = sx_core_ioctl_get_dev(device_id);
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

    if (sx_core_has_predefined_devices()) {
        node_desc.dev_id = get_device_id_from_fd(file);
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
    sxd_dev_id_t              device_id = DEFAULT_DEVICE_ID;

    err = copy_from_user(&event_params, (struct ku_ib_node_description*)data, sizeof(event_params));
    if (err) {
        goto out;
    }

    if (sx_core_has_predefined_devices()) {
        device_id = get_device_id_from_fd(file);
    }

    dev = sx_core_ioctl_get_dev(device_id);
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


long ctrl_cmd_bulk_cntr_tr_continue_ack(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_bulk_cntr_transaction_ack bulk_cntr_tr_ack;
    int                                 err;

    err = copy_from_user(&bulk_cntr_tr_ack, (void*)data, sizeof(bulk_cntr_tr_ack));
    if (err) {
        goto out;
    }

    err = sx_bulk_cntr_handle_continue_ack(&bulk_cntr_tr_ack.event_id, bulk_cntr_tr_ack.buffer_id);
    if (err) {
        goto out;
    }

out:
    return err;
}

long ctrl_cmd_send_issu_notification(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev  *dev = NULL;
    struct sx_priv *priv = NULL;
    int             err = 0, event = 0;
    sxd_dev_id_t    device_id = DEFAULT_DEVICE_ID;
    bool            is_using_independent_module = false;

    /* 'data' is not a pointer but a boolean value:
     * 0 - ISSU finished, FW/ASIC is accessible
     * 1 - ISSU started, FW/ASIC is inaccessible
     */
    event = (!!data) ? KOBJ_OFFLINE : KOBJ_ONLINE;

    if (sx_core_has_predefined_devices()) {
        device_id = get_device_id_from_fd(file);
    }

    dev = sx_core_ioctl_get_dev(device_id);
    if (!dev) {
        return -ENODEV;
    }

    if (!dev->pdev) {
        printk(KERN_ERR "ISSU-in-progress: PCI device is not attached\n");
        err = -ENODEV;
        goto out;
    }

    priv = sx_priv(dev);

    err = sx_core_dispatch_event(dev, SX_DEV_EVENT_ISSU_START, NULL);
    if (err) {
        printk(KERN_ERR PFX "ISSU event failed, err:%d\n", err);
        goto out;
    }

    is_using_independent_module = (SX_GET_FW_CAP(priv, SX_FW_CAP_MOD_SUPPORT_MASK, SX_FW_CAP_MOD_SUPPORT_OFFSET) &&
                                   (priv->profile.dev_profile.set_mask_0_63 & SX_INDEPENDENT_MODULE_MASK) &&
                                   (priv->profile.dev_profile.module_master_fw_default != 0 /* not legacy mode */));

    /* tell HW management that ASIC is accessible/inaccessible only if not using independent-module feature */
    if (!is_using_independent_module) {
        sx_send_udev_event(dev->pdev, NULL, event, "ISSU notification");
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

long ctrl_cmd_bulk_cntr_stateful_db_keys_write(struct file *file, unsigned int cmd, unsigned long data)
{
    ku_stateful_db_translated_entry_t translated_entry;
    int                               err;


    err = copy_from_user(&translated_entry, (void *)data,
                         sizeof(ku_stateful_db_translated_entry_t));


    if (err) {
        printk(KERN_ERR PFX "Failed to copy translated stateful DB entry, err:%d\n", err);
        goto out;
    }


    err = bulk_cntr_stateful_db_entry_write(&translated_entry);
    if (err) {
        printk(KERN_ERR PFX "Failed to write translated stateful DB entry, err:%d\n", err);
        goto out;
    }


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

    if (sx_core_has_predefined_devices()) {
        sdk_health_ctl.dev_id = get_device_id_from_fd(file);
    }

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

    if (sx_core_has_predefined_devices()) {
        sdk_health_ctl.dev_id = get_device_id_from_fd(file);
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
    sxd_dev_id_t                        device_id = DEFAULT_DEVICE_ID;

    if (sx_core_has_predefined_devices()) {
        device_id = get_device_id_from_fd(file);
    }

    dev = sx_core_ioctl_get_dev(device_id);
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
        priv->module_to_slot_map[module_id] = slot_id;
    } else {
        /* Delete mapping */
        if (((priv->local_to_slot_map[local_port] != slot_id) ||
             (priv->local_to_module_map[local_port] != module_id)) ||
            (priv->modules_to_port_map_count[slot_id][module_id] == 0)) {
            goto out;
        }
        if (priv->module_to_slot_map[module_id] == slot_id) {
            priv->module_to_slot_map[module_id] = 0;
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

    if (sx_core_has_predefined_devices()) {
        params.dev_id = get_device_id_from_fd(file);
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

long ctrl_cmd_set_dev_info(struct file *file, unsigned int cmd, unsigned long data)
{
    sxd_dev_id_t       dev_id = DEFAULT_DEVICE_ID;
    int                err = 0;
    struct ku_dev_info dev_info;
    struct sx_dev     *dev;
    struct sx_priv    *priv;

    err = copy_from_user(&dev_info, (void*)data, sizeof(dev_info));
    if (err) {
        goto out;
    }

    if (sx_core_has_predefined_devices()) {
        dev_id = get_device_id_from_fd(file);
    } else {
        dev_id = dev_info.dev_id;
    }

    dev = sx_core_ioctl_get_dev(dev_id);
    if (!dev) {
        return -ENODEV;
    }

    priv = sx_priv(dev);
    memcpy(&(priv->dev_info.dev_info_set), &(dev_info.dev_info.dev_info_set), sizeof(dev_info.dev_info.dev_info_set));

out:
    return err;
}

long ctrl_cmd_get_dev_info(struct file *file, unsigned int cmd, unsigned long data)
{
    sxd_dev_id_t       dev_id = DEFAULT_DEVICE_ID;
    struct sx_dev     *dev;
    int                err = 0;
    struct ku_dev_info dev_info;
    struct sx_priv    *priv;

    err = copy_from_user(&dev_info, (void*)data, sizeof(dev_info));
    if (err) {
        goto out;
    }

    if (sx_core_has_predefined_devices()) {
        dev_id = get_device_id_from_fd(file);
        dev_info.dev_id = dev_id;
    } else {
        dev_id = dev_info.dev_id;
    }
    dev = sx_core_ioctl_get_dev(dev_id);
    if (!dev) {
        return -ENODEV;
    }

    priv = sx_priv(dev);
    memcpy(&dev_info.dev_info, &priv->dev_info, sizeof(dev_info.dev_info));

    err = copy_to_user((void*)data, &dev_info, sizeof(dev_info));
    if (err) {
        goto out;
    }

out:
    return err;
}


long ctrl_cmd_read_host_mem_page(struct file *file, unsigned int cmd, unsigned long data)
{
    sxd_dev_id_t                  dev_id = DEFAULT_DEVICE_ID;
    struct sx_dev                *dev;
    int                           err = 0;
    struct ku_host_mem_read_page *host_mem_pg_p;
    struct sx_priv               *priv;
    struct sx_icm_iter            iter;
    void                         *vm = NULL;
    struct page                  *page_arr = NULL;
    uint32_t                      pg_index = 0; /* in all the host memory page allocation for FW */
    uint32_t                      mem_index = 0; /* index in mem array (chunk.mem[]) */
    uint32_t                      page_arr_index = 0; /* index in the page array that mem[] element points to */


    host_mem_pg_p = (struct ku_host_mem_read_page*)kmalloc(sizeof(struct ku_host_mem_read_page), GFP_KERNEL);
    if (host_mem_pg_p == NULL) {
        printk(KERN_ERR PFX "Failed to allocate %ld bytes.\n", PAGE_SIZE);
        err = -ENOMEM;
        goto out;
    }

    err = copy_from_user(host_mem_pg_p, (void*)data, sizeof(*host_mem_pg_p));
    if (err) {
        goto out_and_free;
    }

    if (sx_core_has_predefined_devices()) {
        dev_id = get_device_id_from_fd(file);
    } else {
        dev_id = host_mem_pg_p->dev_id;
    }
    dev = sx_core_ioctl_get_dev(dev_id);
    if (!dev) {
        err = -ENODEV;
        goto out_and_free;
    }

    if (host_mem_pg_p->page_index > MLX_TRACE_MAX_PAGE_NUM) {
        printk(KERN_ERR PFX "Failed to get next mlx trace page from host memory,"
               " The page index [%d] is out of range (%d).\n", host_mem_pg_p->page_index, MLX_TRACE_MAX_PAGE_NUM);
        err = -EINVAL;
        goto out_and_free;
    }

    /*
     * priv->fw.fw_icm points to linked list of chunks,  Each Chunk has mem[] array.
     * mem[] has SX_ICM_CHUNK_LEN elements. Each element points to array of pages ( page is 4096B),
     * Maximum array of pages length is NUM_PAGES_IN_PAGE_ARRY.
     *
     * Currently, FW asks for 521 pages, and the layout is:
     * chunk[0].mem[0]-> 1 allocation * 512 pages (2M)
     * chunk[0].mem[1]-> 1 allocation * 8 pages,
     * chunk[0].mem[2]-> 1 allocation * 1 pages
     * 512 + 8 + 1 = 521 which is priv->fw.fw_pages.
     */

    /* The page index in the allocated pages = MLX_TRACE page offset in the allocated pages + MLX_TRACE page offset*/
    pg_index = MLX_TRACE_PAGE_OFFSET_IN_HOST_MEM_ALLOCATED_MAP_FA_PAGES + host_mem_pg_p->page_index;

    priv = sx_priv(dev);

    /*1. Get the right chunk in the linked list */
    for (sx_icm_first(priv->fw.fw_icm, &iter);
         !sx_icm_last(&iter);
         sx_icm_next(&iter)) {
        if (pg_index < MAX_CHUNK_PAGE_NUM) {
            break;
        }
        pg_index -= MAX_CHUNK_PAGE_NUM;
    }

    if (iter.chunk == NULL) {
        printk(KERN_ERR PFX "Failed to get host memory allocated chunk.\n");
        err = -EINVAL;
        goto out_and_free;
    }
    /*2. Get the right element in chunk.mem[]. */
    mem_index = pg_index / NUM_PAGES_IN_PAGE_ARRY;
    page_arr_index = pg_index % NUM_PAGES_IN_PAGE_ARRY;

    /* Get the page array (remove the meta data)*/
    page_arr = sg_page(&iter.chunk->mem[mem_index]);

    /*3. Get the right page from the page array */
    vm = kmap(&page_arr[page_arr_index]);
    if (vm == NULL) {
        printk(PFX "couldn't get MLX buffer page [%d].\n", host_mem_pg_p->page_index);
        err = -EINVAL;
        goto out_and_free;
    }

    memcpy(host_mem_pg_p->pg_data_arr, vm, PAGE_SIZE);
    kunmap(&page_arr[page_arr_index]);

    err = copy_to_user((void*)data, host_mem_pg_p, sizeof(*host_mem_pg_p));
    if (err) {
        goto out_and_free;
    }
out_and_free:
    kfree(host_mem_pg_p);

out:
    return err;
}
