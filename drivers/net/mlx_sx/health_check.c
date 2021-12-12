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

#include <linux/workqueue.h>
#include <linux/list.h>
#include <linux/seq_file.h>

#include <linux/mlx_sx/kernel_user.h>
#include "sx.h"
#include "health_check.h"
#include "alloc.h"
#include "sx_dbg_dump_proc.h"
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>


struct catas_cause_data {
    u32 catas_buf;
};

struct dq_cause_data {
    int dqn;
};

struct failure_info {
    unsigned long      jiffies; /* time when the failure happened */
    struct list_head   list;
    sxd_health_cause_t cause;
    bool               has_cause_data;
    union {
        struct catas_cause_data catas_data; /* catas event */
        struct dq_cause_data    dq_data; /* for SDQ/RDQ errors */
    } cause_data;
};

struct sx_health_check_config {
    struct sx_bitmap sdq_bitmap;
    struct sx_bitmap rdq_bitmap;
    struct sx_bitmap last_sdq_bitmap; /* keep state upon config change */
    struct sx_bitmap last_rdq_bitmap; /* keep state upon config change */
    uint32_t         periodic_time;
    uint32_t         failures_num;
};


struct sx_health_dev_info {
    struct sx_dev      *dev;
    struct delayed_work dwork;
    struct list_head    dev_list;
    u32 __iomem        *catas_iomap;
    struct mutex        lock;

    /* following fields must be accessed within device information lock */
    struct list_head              failure_ts_list;
    u32                           failures_detected;
    bool                          fatal_detected;
    bool                          health_check_first_itr_skip_checks_func;
    struct sx_health_check_config config;
};

static struct workqueue_struct *__health_check_wq = NULL;
static struct delayed_work      __health_check_ts_work;
static uint64_t                 __health_check_ts = 0;
static bool                     __health_check_ts_trigger = false;
static LIST_HEAD(__dev_info_list);
static DEFINE_MUTEX(__health_check_lock);

#define START_HETT_SESSION 0
#define STOP_HETT_SEASSON  1

/* must be called within the device information lock */
static void __add_failure(struct sx_health_dev_info *info, sxd_health_cause_t cause, void *cause_data, bool is_fatal)
{
    struct failure_info *iter = NULL, *tmp = NULL, *new_failure = NULL;
    unsigned long        now = jiffies;

    /* check if there are old failures that we can remove from the list */
    list_for_each_entry_safe(iter, tmp, &info->failure_ts_list, list) {
        if (time_after(now, iter->jiffies + info->config.failures_num * 10 * HZ)) {
            info->failures_detected--;
            list_del(&iter->list);
            if (new_failure == NULL) {
                new_failure = iter; /* instead of allocating a new one, use an old one */
            } else {
                kfree(iter);
            }
        } else {
            break; /* failures are in chronological order, if we're here we can stop the iteration */
        }
    }

    if (is_fatal && !info->fatal_detected) {
        info->fatal_detected = true;
    }

    if (new_failure == NULL) { /* we have to allocate a new one */
        new_failure = kzalloc(sizeof(struct failure_info), GFP_KERNEL);

        if (new_failure == NULL) {
            printk(KERN_ERR "couldn't allocate device %u health-check failure\n", info->dev->device_id);
            return;
        }
    } else {
        memset(new_failure, 0, sizeof(struct failure_info));
    }

    INIT_LIST_HEAD(&new_failure->list);
    new_failure->jiffies = now;
    new_failure->cause = cause;
    if (cause_data) {
        new_failure->has_cause_data = true;
        memcpy(&new_failure->cause_data, cause_data, sizeof(new_failure->cause_data));
    }
    list_add_tail(&new_failure->list, &info->failure_ts_list);
    info->failures_detected++;
}

static int __write_hett(struct ku_access_hett_reg *hett, struct sx_dev *dev, const char *op)
{
    int err;

    hett->dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&hett->op_tlv, MLXSW_HETT_ID, EMAD_METHOD_WRITE);
    err = sx_ACCESS_REG_HETT(dev, hett);
    if (err) {
        printk(KERN_ERR "sx_ACCESS_REG_HETT (%s) returned with error %d\n", op, err);
    }

    return err;
}
/* compare bit maps and return the first bit that is change, in case they identical return  -1 */
static u32 __compare_bitmaps(struct sx_bitmap *bm1, struct sx_bitmap *bm2)
{
    u32 bit_id, max, bit_id_value1, bit_id_value2;

    /* bm1 and bm2 share have the same size */
    max = sx_bitmap_num_bits(bm1);

    for (bit_id = 0; bit_id < max; bit_id++) {
        bit_id_value1 = sx_bitmap_test(bm1, bit_id);
        bit_id_value2 = sx_bitmap_test(bm2, bit_id);
        if (bit_id_value1 != bit_id_value2) {
            return bit_id;
        }
    }
    return (u32) - 1;
}

/* must be called within the device information lock */
static void __check_catas(struct sx_health_dev_info *info)
{
    struct catas_cause_data catas_data;
    struct sx_priv         *priv = sx_priv(info->dev);

    if (!priv->debug_trigger_state.catas) { /* debug trigger not set */
        if (!info->catas_iomap) { /* device does not support catas */
            catas_data.catas_buf = 0;
        } else {
            catas_data.catas_buf = swab32(__raw_readl(info->catas_iomap));
        }
    } else {
        catas_data.catas_buf = 0xdeadbeaf;
    }

    if (catas_data.catas_buf) {
        __add_failure(info, SXD_HEALTH_CAUSE_CATAS, &catas_data, true);
    }
}

/* must be called within the device information lock */
static void __check_cmd_ifc_from_last_cycle(struct sx_health_dev_info *info)
{
}

/* must be called within the device information lock */
static void __check_sdq_from_last_cycle(struct sx_health_dev_info *info)
{
}

/* must be called within the device information lock */
static void __check_rdq_from_last_cycle(struct sx_health_dev_info *info)
{
    uint32_t             bit_map_compare_res = 0;
    struct dq_cause_data dq_data;
    struct sx_priv      *priv = sx_priv(info->dev);


    bit_map_compare_res = __compare_bitmaps(&priv->operational_state.rdq_bitmap, &info->config.last_rdq_bitmap);
    if (bit_map_compare_res != ((u32) - 1)) {
        dq_data.dqn = bit_map_compare_res;
        __add_failure(info, SXD_HEALTH_CAUSE_RDQ, &dq_data, false);
    }
    sx_bitmap_clear_all(&info->config.last_rdq_bitmap);
}

/* must be called within the device information lock */
static void __start_cmd_ifc_for_next_cycle(struct sx_health_dev_info *info)
{
}

/* must be called within the device information lock */
static void __start_sdq_for_next_cycle(struct sx_health_dev_info *info)
{
}

/* must be called within the device information lock */
static void __start_rdq_for_next_cycle(struct sx_health_dev_info *info)
{
    struct ku_access_hett_reg reg_hett;
    int                       err = 0;
    struct sx_priv           *priv = sx_priv(info->dev);

    /*initialize operational state RDQ bitmap*/
    sx_bitmap_clear_all(&priv->operational_state.rdq_bitmap);

    /*rdq_bitmap changed on the fly so last_rdq_bitmap will be static and will represent the HETT requested rdq_bitmap*/
    sx_bitmap_copy(&info->config.last_rdq_bitmap, &info->config.rdq_bitmap);

    memset(&reg_hett, 0, sizeof(reg_hett));
    reg_hett.hett_reg.opcode = START_HETT_SESSION;
    reg_hett.hett_reg.trap_group_bitmap.lo = (u32)(info->config.last_rdq_bitmap.table[0] & 0xffffffff);
    reg_hett.hett_reg.trap_group_bitmap.hi = (u32)((info->config.last_rdq_bitmap.table[0] >> 32) & 0xffffffff);
    err = __write_hett(&reg_hett, info->dev, "send trap group bitmap");
    if (err) {
        /* fatal failure will stop the health mechanism */
        __add_failure(info, SXD_HEALTH_CAUSE_FW_HETT, NULL, true);
    }
}

static void __sx_health_check_cycle(struct work_struct *work)
{
    struct sx_health_dev_info *info = container_of(work, struct sx_health_dev_info, dwork.work);

    mutex_lock(&info->lock);

    /* this is an immediate check, no need for 2-step check */
    __check_catas(info);
    if (info->health_check_first_itr_skip_checks_func) {
        info->health_check_first_itr_skip_checks_func = false;
        goto health_monitor;
    }
    __check_cmd_ifc_from_last_cycle(info);
    __check_sdq_from_last_cycle(info);
    __check_rdq_from_last_cycle(info);

health_monitor:

    __start_cmd_ifc_for_next_cycle(info);
    __start_sdq_for_next_cycle(info);
    __start_rdq_for_next_cycle(info);

    if (info->fatal_detected) {
        /* too many failures: send SDK health event and stop monitoring this device */
        sx_send_health_event(info->dev->device_id, SXD_HEALTH_CAUSE_SDK_WD);
        printk(KERN_ERR "device %u is FATAL and is not monitored anymore!\n", info->dev->device_id);
    } else {
        if (info->failures_detected >= info->config.failures_num) {
            sx_send_health_event(info->dev->device_id, SXD_HEALTH_CAUSE_SDK_WD);
            printk(KERN_ERR "device %u is notice fatal failure detection !\n", info->dev->device_id);
        }
        queue_delayed_work(__health_check_wq, &info->dwork, info->config.periodic_time * HZ);
    }

    mutex_unlock(&info->lock);
}

/* must be called within the health-check lock */
static int __info_alloc(u8                          dev_id,
                        u32                         check_interval,
                        u32                         alert_threshold,
                        unsigned long               hw_groups_curr_status,
                        struct sx_health_dev_info **ret_info)
{
    struct sx_dev             *dev = NULL;
    struct sx_priv            *priv = NULL;
    struct sx_health_dev_info *info = NULL;
    resource_size_t            catas_start = 0;
    u32 __iomem               *catas_iomap = NULL;
    int                        err = 0;
    uint32_t                   dq_id = 0;

    dev = sx_dpt_get_dev_from_id(dev_id);
    if (!dev) {
        printk(KERN_ERR "failed to get device from id (id=%u)\n", dev_id);
        err = -ENODEV;
        goto out;
    }

    priv = sx_priv(dev);

    if (priv->fw.catas_size > 0) {
        catas_start = pci_resource_start(dev->pdev, priv->fw.catas_bar) + priv->fw.catas_offset;
        catas_iomap = ioremap(catas_start, priv->fw.catas_size * 4);
        if (!catas_iomap) {
            printk(KERN_ERR "failed to map internal error buffer on device %u at 0x%llx\n", dev->device_id,
                   catas_start);
            err = -ENOMEM;
            goto out;
        }
    }

    info = kzalloc(sizeof(struct sx_health_dev_info), GFP_KERNEL);
    if (!info) {
        printk(KERN_ERR "could not create a new health-check entry for device %u\n", dev->device_id);
        err = -ENOMEM;
        goto out;
    }

    info->dev = dev;
    info->catas_iomap = catas_iomap;
    INIT_DELAYED_WORK(&info->dwork, __sx_health_check_cycle);
    INIT_LIST_HEAD(&info->dev_list);
    INIT_LIST_HEAD(&info->failure_ts_list);
    mutex_init(&info->lock);
    sx_bitmap_init(&info->config.last_rdq_bitmap, NUMBER_OF_RDQS);
    sx_bitmap_init(&info->config.last_sdq_bitmap, NUMBER_OF_SDQS);
    sx_bitmap_init(&info->config.sdq_bitmap, NUMBER_OF_SDQS);
    sx_bitmap_init(&info->config.rdq_bitmap, NUMBER_OF_RDQS);

    info->config.periodic_time = check_interval;
    info->config.failures_num = alert_threshold;
    /* fill the rdq_bitmap with the hw_traps that exist before starting this feature */
    for (dq_id = 0; dq_id < 64; dq_id++) {
        if (test_bit(dq_id, &hw_groups_curr_status)) {
            sx_bitmap_set(&info->config.rdq_bitmap, dq_id);
        }
    }
    info->health_check_first_itr_skip_checks_func = true;
    list_add_tail(&info->dev_list, &__dev_info_list);
    *ret_info = info;
out:
    return err;
}

/* must be called within the health-check lock */
static void __info_dealloc(struct sx_health_dev_info *info)
{
    struct failure_info *iter = NULL, *tmp = NULL;

    cancel_delayed_work_sync(&info->dwork);
    list_del(&info->dev_list);

    mutex_lock(&info->lock);

    list_for_each_entry_safe(iter, tmp, &info->failure_ts_list, list) {
        list_del(&iter->list);
        kfree(iter);
    }

    iounmap(info->catas_iomap);
    info->catas_iomap = NULL;
    mutex_unlock(&info->lock);

    kfree(info);
}

/* must be called within the health-check lock */
static struct sx_health_dev_info * __info_find(u8 dev_id)
{
    struct sx_dev             *dev = sx_dpt_get_dev_from_id(dev_id);
    struct sx_health_dev_info *info;

    if (!dev) {
        return NULL;
    }

    list_for_each_entry(info, &__dev_info_list, dev_list) {
        if (info->dev == dev) {
            return info;
        }
    }

    return NULL;
}

static void __sx_health_check_update_timestamp(struct work_struct *work)
{
    mutex_lock(&__health_check_lock);

    if (!__health_check_ts_trigger) {
        __health_check_ts++;
    }

    if (__health_check_wq) {
        queue_delayed_work(__health_check_wq, &__health_check_ts_work, HZ); /* 1 second */
    }

    mutex_unlock(&__health_check_lock);
}

static int __sx_health_add_device(u8 dev_id, u32 check_interval, u32 alert_threshold, u64 hw_groups_curr_status)
{
    struct sx_health_dev_info *info = NULL;
    int                        err = 0;

    info = __info_find(dev_id);
    if (!info) {
        err = __info_alloc(dev_id, check_interval, alert_threshold, hw_groups_curr_status, &info);
    } else {
        err = -EEXIST;
    }

    if (!err) {
        queue_delayed_work(__health_check_wq, &info->dwork, 0); /* now */
    }

    return err;
}

static void __sx_health_delete_device(u8 dev_id)
{
    struct sx_health_dev_info *info = NULL;

    info = __info_find(dev_id);
    if (info) {
        __info_dealloc(info);
    }
}

static int __sx_health_update_tg(u8 dev_id, int hw_trap_group, bool is_add)
{
    struct sx_health_dev_info *info = NULL;

    info = __info_find(dev_id);
    if (!info) {
        return -ENODEV;
    }

    mutex_lock(&info->lock);

    if (is_add) {
        sx_bitmap_set(&info->config.rdq_bitmap, hw_trap_group);
    } else {
        sx_bitmap_free(&info->config.rdq_bitmap, hw_trap_group);
    }

    mutex_unlock(&info->lock);
    return 0;
}

static int __sx_health_update_sampling_params(u8 dev_id, uint32_t check_interval, uint32_t alert_threshold)
{
    struct sx_health_dev_info *info = NULL;

    info = __info_find(dev_id);
    if (!info) {
        return -ENODEV;
    }

    mutex_lock(&info->lock);

    info->config.periodic_time = check_interval;
    info->config.failures_num = alert_threshold;

    mutex_unlock(&info->lock);
    return 0;
}

int sx_health_check_init(void)
{
    int err = 0;

    printk(KERN_INFO "Health-Check: initialization\n");

    if (__health_check_wq) {
        err = -EEXIST;
        goto out;
    }

    __health_check_wq = create_singlethread_workqueue("sx_health_check");
    if (!__health_check_wq) {
        err = -ENOMEM;
        goto out;
    }

    INIT_DELAYED_WORK(&__health_check_ts_work, __sx_health_check_update_timestamp);
    queue_delayed_work(__health_check_wq, &__health_check_ts_work, 0); /* now */
out:
    return err;
}

int sx_health_check_deinit(void)
{
    int err = 0;

    printk(KERN_INFO "Health-Check: cleanup\n");

    if (!__health_check_wq) {
        printk(KERN_ERR "health check has not been started\n");
        err = -ENOENT;
        goto out;
    }

    if (!list_empty(&__dev_info_list)) {
        printk(KERN_ERR "devices are still being monitored\n");
        err = -EBUSY;
        goto out;
    }

    cancel_delayed_work_sync(&__health_check_ts_work);
    destroy_workqueue(__health_check_wq);

    __health_check_wq = NULL;

out:
    return err;
}

int sx_health_check_configure(ku_dbg_group_traps_and_sample_params_t *params)
{
    int err = 0;

    mutex_lock(&__health_check_lock);

    switch (params->sxd_health_fatal_failure_detect_cmd) {
    case SXD_HEALTH_FATAL_FAILURE_ENABLE_E:
        printk(KERN_INFO "Health-Check: Enable device %u\n", params->dev_id);
        err = __sx_health_add_device(params->dev_id,
                                     params->params.sampling_params.check_interval,
                                     params->params.sampling_params.alert_threshold,
                                     params->params.sampling_params.hw_groups_curr_status);
        break;

    case SXD_HEALTH_FATAL_FAILURE_DISABLE_E:
        printk(KERN_INFO "Health-Check: Disable device %u\n", params->dev_id);
        __sx_health_delete_device(params->dev_id);
        break;

    case SXD_HEALTH_FATAL_FAILURE_ADD_TRAP_GROUP_E:
        printk(KERN_INFO "Health-Check: Add trap-group %d to device %u\n",
               params->params.tg_params.hw_trap_group,
               params->dev_id);
        err = __sx_health_update_tg(params->dev_id,
                                    params->params.tg_params.hw_trap_group,
                                    true);
        break;

    case SXD_HEALTH_FATAL_FAILURE_DELETE_TRAP_GROUP_E:
        printk(KERN_INFO "Health-Check: Delete trap-group %d from device %u\n",
               params->params.tg_params.hw_trap_group,
               params->dev_id);
        err = __sx_health_update_tg(params->dev_id,
                                    params->params.tg_params.hw_trap_group,
                                    false);
        break;

    case SXD_HEALTH_FATAL_FAILURE_UPDATE_SAMPLE_PARAMS_E:
        printk(KERN_INFO "Health-Check: Update sampling parameters for device %u (interval=%u, threshold=%u)\n",
               params->dev_id,
               params->params.sampling_params.check_interval,
               params->params.sampling_params.alert_threshold);
        err = __sx_health_update_sampling_params(params->dev_id,
                                                 params->params.sampling_params.check_interval,
                                                 params->params.sampling_params.alert_threshold);
        break;

    default:
        break;
    }

    mutex_unlock(&__health_check_lock);

    if (err) {
        printk(KERN_ERR "Health-Check: Operation failed (err=%d)\n", err);
    }

    return err;
}

void sx_health_check_report_dq_ok(struct sx_dev *dev, bool is_send, int dqn)
{
    struct sx_priv *priv = sx_priv(dev);

    if (is_send) {
        if (!sx_bitmap_test(&priv->debug_trigger_state.sdq_bitmap, dqn)) { /* debug trigger not set */
            sx_bitmap_set(&priv->operational_state.sdq_bitmap, dqn);
        }
    } else {
        if (!sx_bitmap_test(&priv->debug_trigger_state.rdq_bitmap, dqn)) { /* debug trigger not set */
            sx_bitmap_set(&priv->operational_state.rdq_bitmap, dqn);
        }
    }
}

void sx_health_check_report_cmd_ifc_ok(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);

    if (!priv->debug_trigger_state.cmd_ifc) { /* debug trigger not set */
        priv->operational_state.cmd_ifc = true;
    }
}


int sx_health_check_running_counter(struct seq_file *m, void *v)
{
    seq_printf(m, "%llu\n", __health_check_ts);
    return 0;
}

static void __dump_bitmap(struct seq_file *m, void *v, struct sx_bitmap *bitmap)
{
    u32  i, max;
    bool found_bit;

    seq_printf(m, "\t\t");

    max = sx_bitmap_num_bits(bitmap);
    found_bit = false;
    for (i = 0; i < max; i++) {
        if (sx_bitmap_test(bitmap, i)) {
            found_bit = true;
            seq_printf(m, "%u, ", i);
        }
    }

    if (!found_bit) {
        seq_printf(m, "None");
    }

    seq_printf(m, "\n");
}

static void __dump_failure(struct seq_file *m, void *v, struct failure_info *failure)
{
    const char *cause = NULL;
    char        extra_info[64] = { 0 };

    switch (failure->cause) {
    case SXD_HEALTH_CAUSE_CATAS:
        cause = "Catas";
        if (failure->has_cause_data) {
            snprintf(extra_info, sizeof(extra_info), "Catas buf: 0x%x", failure->cause_data.catas_data.catas_buf);
        }
        break;

    case SXD_HEALTH_CAUSE_GO_BIT:
        cause = "Go bit";
        break;

    case SXD_HEALTH_CAUSE_RDQ:
        cause = "RDQ";
        if (failure->has_cause_data) {
            snprintf(extra_info, sizeof(extra_info), "RDQ#: %d", failure->cause_data.dq_data.dqn);
        }
        break;

    case SXD_HEALTH_CAUSE_SDQ:
        cause = "SDQ";
        if (failure->has_cause_data) {
            snprintf(extra_info, sizeof(extra_info), "SDQ#: %d", failure->cause_data.dq_data.dqn);
        }
        break;

    case SXD_HEALTH_CAUSE_SDK_WD:
        cause = "SDK WD combination of failures";
        break;

    case SXD_HEALTH_CAUSE_FW_HETT:
        cause = "FW HETT";
        break;

    default:
        cause = "Other";
        break;
    }
    ;

    seq_printf(m, "\t\tCause: %s, Time (Seconds ago): %u",
               cause,
               jiffies_to_msecs(jiffies - failure->jiffies) / 1000);
    if (extra_info[0]) {
        seq_printf(m, ", %s", extra_info);
    }

    seq_printf(m, "\n");
}

static void __dump_info(struct seq_file *m, void *v, struct sx_health_dev_info *info)
{
    struct failure_info *failure = NULL;
    struct sx_priv      *priv;

    priv = sx_priv(info->dev);

    mutex_lock(&info->lock);
    seq_printf(m, "Device ID: %u\n", info->dev->device_id);
    seq_printf(m, "\tCheck Interval: %u Milliseconds\n", (info->config.periodic_time * 1000));
    seq_printf(m, "\tAlert Threshold: %u failures\n", info->config.failures_num);
    seq_printf(m, "\tFailures detected: %u\n", info->failures_detected);
    seq_printf(m, "\tFatal detected: %s\n", (info->fatal_detected) ? "Yes" : "No");
    seq_printf(m, "\tMonitored SDQs:\n");
    __dump_bitmap(m, v, &info->config.sdq_bitmap);
    seq_printf(m, "\tMonitored last SDQs:\n");
    __dump_bitmap(m, v, &info->config.last_sdq_bitmap);
    seq_printf(m, "\tOperational RDQs:\n");
    __dump_bitmap(m, v, &priv->operational_state.sdq_bitmap);
    seq_printf(m, "\tTrigger state SDQs:\n");
    __dump_bitmap(m, v, &priv->debug_trigger_state.sdq_bitmap);

    seq_printf(m, "\tMonitored RDQs:\n");
    __dump_bitmap(m, v, &info->config.rdq_bitmap);
    seq_printf(m, "\tMonitored last RDQs:\n");
    __dump_bitmap(m, v, &info->config.last_rdq_bitmap);
    seq_printf(m, "\tOperational RDQs:\n");
    __dump_bitmap(m, v, &priv->operational_state.rdq_bitmap);
    seq_printf(m, "\tTrigger state RDQs:\n");
    __dump_bitmap(m, v, &priv->debug_trigger_state.rdq_bitmap);

    seq_printf(m, "\tFailures Information:\n");

    list_for_each_entry(failure, &info->failure_ts_list, list) {
        __dump_failure(m, v, failure);
    }

    mutex_unlock(&info->lock);
}

int sx_health_check_dump(struct seq_file *m, void *v)
{
    struct sx_health_dev_info *info;

    print_table_header(m, "Health-Check DUMP");

    mutex_lock(&__health_check_lock);

    list_for_each_entry(info, &__dev_info_list, dev_list) {
        __dump_info(m, v, info);
    }

    mutex_unlock(&__health_check_lock);
    return 0;
}

void sx_health_check_set_debug_trigger(struct sx_health_check_trigger_params *params)
{
    struct sx_health_dev_info *info;
    struct sx_priv            *priv = NULL;

    mutex_lock(&__health_check_lock);

    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_SYSFS) {
        printk(KERN_NOTICE "Health-Check: Trigger SYSFS failure\n");
        __health_check_ts_trigger = true;
        goto out;
    }

    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_ADD_DEV) {
        printk(KERN_NOTICE "Health-Check: Trigger Add-Device %u\n", params->dev_id);
        __sx_health_add_device(params->dev_id, 10, 3, 0); /*todo add to user params the rdq bitmap status */
        goto out;
    }

    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_DEL_DEV) {
        printk(KERN_NOTICE "Health-Check: Trigger Del-Device %u\n", params->dev_id);
        __sx_health_delete_device(params->dev_id);
        goto out;
    }
    info = __info_find(params->dev_id);
    priv = sx_priv(info->dev);

    if (!info) {
        printk(KERN_ERR "Health-Check: device %u is not monitored\n", params->dev_id);
        goto out;
    }

    mutex_lock(&info->lock);
    switch (params->op) {
    case SX_HEALTH_CHECK_TRIGGER_OP_CATAS:
        printk(KERN_NOTICE "Health-Check: Trigger CATAS failure on device %u\n", params->dev_id);
        priv->debug_trigger_state.catas = true;
        break;

    case SX_HEALTH_CHECK_TRIGGER_OP_CMD_IFC:
        printk(KERN_NOTICE "Health-Check: Trigger CMD_IFC failure on device %u\n", params->dev_id);
        priv->debug_trigger_state.cmd_ifc = true;
        break;

    case SX_HEALTH_CHECK_TRIGGER_OP_SDQ:
        printk(KERN_NOTICE "Health-Check: Trigger SDQ %d failure on device %u\n",
               params->params.dq_params.dqn, params->dev_id);
        sx_bitmap_set(&priv->debug_trigger_state.sdq_bitmap, params->params.dq_params.dqn);
        break;

    case SX_HEALTH_CHECK_TRIGGER_OP_RDQ:
        printk(KERN_NOTICE "Health-Check: Trigger RDQ %d failure on device %u\n",
               params->params.dq_params.dqn, params->dev_id);
        sx_bitmap_set(&priv->debug_trigger_state.rdq_bitmap, params->params.dq_params.dqn);
        break;

    default:
        break;
    }
    mutex_unlock(&info->lock);

out:
    mutex_unlock(&__health_check_lock);
}
