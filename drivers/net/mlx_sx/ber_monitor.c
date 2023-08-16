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

#include <linux/types.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/seq_file.h>

#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/cmd.h>

#include "sx.h"
#include "dev_db.h"
#include "sx_dbg_dump_proc.h"
#include "ber_monitor.h"

struct ber_bitmask_set_work_data {
    struct completion *wq_completion;
    sxd_dev_id_t       dev_id;
    u16                local_port;
    u8                 bitmask;
    int                ret;
    struct work_struct work;
};
struct ber_work_data {
    sxd_dev_id_t        dev_id;
    u16                 local_port;
    struct delayed_work dwork;
};

static struct workqueue_struct *__ber_monitor_wq = NULL;
static struct ber_monitor_info *__ber_monitor_db[(MAX_NUM_OF_REMOTE_SWITCHES)+1];
static DEFINE_SPINLOCK(__ber_monitor_lock);

int sx_core_ber_monitor_init(void)
{
    printk(KERN_INFO "Ber-Monitor (init)\n");

    __ber_monitor_wq = sx_health_check_create_monitored_workqueue("ber_monitor");
    if (!__ber_monitor_wq) {
        return -ENOMEM;
    }

    return 0;
}

/* must be called within a lock */
static int __create_ber_monitor_dev_db(sxd_dev_id_t dev_id)
{
    __ber_monitor_db[dev_id] = kzalloc(sizeof(struct ber_monitor_info), GFP_ATOMIC);
    return __ber_monitor_db[dev_id] != NULL ? 0 : -ENOMEM;
}

/* must be called within the ber_monitor lock */
static struct ber_monitor_info * __dev_id_to_bm_info(sxd_dev_id_t dev_id, bool create_new)
{
    struct sx_dev           *dev = NULL;
    struct ber_monitor_info *bm_info = NULL;
    int                      err = 0;

    /* first, we try to find the device in the PCI device database. If it is not found there
     * (We're on a IB director system), we'll create the BER info here.
     */
    dev = sx_dev_db_get_dev_by_id(dev_id);
    if (dev) {
        bm_info = &sx_priv(dev)->ber_monitor_info;
    } else {
        if (!__ber_monitor_db[dev_id]) {
            if (!create_new) {
                bm_info = ERR_PTR(-ENODEV);
                goto out;
            }

            /* we need a dev pointer here, so we get it from the default device (even if it is a fake one) */
            dev = sx_dev_db_get_default_device();
            if (!dev) {
                printk(KERN_ERR "Ber-Monitor: could not find default device\n");
                bm_info = ERR_PTR(-ENODEV);
                goto out;
            }

            err = __create_ber_monitor_dev_db(dev_id);
            if (err) {
                bm_info = ERR_PTR(err);
                goto out;
            }

            __ber_monitor_db[dev_id]->dev = dev;
        }

        bm_info = __ber_monitor_db[dev_id];
    }

out:
    return bm_info;
}

void sx_core_ber_monitor_deinit(void)
{
    struct ber_monitor_info *bm_info = NULL;
    sxd_dev_id_t             dev_id;

    printk(KERN_INFO "Ber-Monitor (deinit)\n");

    spin_lock_bh(&__ber_monitor_lock);

    /* coverity[result_independent_of_operands] */
    for (dev_id = 1; DEV_ID_IS_VALID(dev_id); dev_id++) {
        if (DEFAULT_DEVICE_ID_CHECK(dev_id)) {
            continue;
        }

        bm_info = __dev_id_to_bm_info(dev_id, false);
        if (PTR_ERR(bm_info)) {
            continue;
        }

        kfree(bm_info);
    }

    memset(__ber_monitor_db, 0, sizeof(__ber_monitor_db));
    spin_unlock_bh(&__ber_monitor_lock);

    flush_workqueue(__ber_monitor_wq);
    sx_health_check_destroy_monitored_workqueue(__ber_monitor_wq);
}

void sx_core_ber_monitor_dev_init(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);

    memset(&priv->ber_monitor_info, 0, sizeof(priv->ber_monitor_info));
    priv->ber_monitor_info.dev = dev;
}

void sx_core_ber_monitor_dev_deinit(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);

    memset(&priv->ber_monitor_info, 0, sizeof(priv->ber_monitor_info));
}

int sx_core_ber_monitor_set_state(sxd_dev_id_t dev_id, u16 local_port, u8 state)
{
    struct ber_monitor_info *bm_info = NULL;
    int                      err = 0;

    /* coverity[result_independent_of_operands] */
    if (!DEV_ID_IS_VALID(dev_id)) {
        printk(KERN_ERR "Ber-Monitor (set-state): device ID %u is invalid\n", dev_id);
        err = -EINVAL;
        goto out;
    }

    if (local_port > MAX_PHYPORT_NUM) {
        printk(KERN_ERR "Ber-Monitor (set-state): local port %u is invalid (max. %u)\n",
               local_port,
               MAX_PHYPORT_NUM);
        err = -EINVAL;
        goto out;
    }

    spin_lock_bh(&__ber_monitor_lock);

    bm_info = __dev_id_to_bm_info(dev_id, true);
    if (IS_ERR(bm_info)) {
        err = PTR_ERR(bm_info);
    } else {
        bm_info->port_ber_monitor_state[local_port] = state;
    }

    spin_unlock_bh(&__ber_monitor_lock);
out:
    return err;
}

static void __ber_monitor_bitmask_work_handler(struct work_struct *work)
{
    struct ber_bitmask_set_work_data *ber_wdata = container_of(work,
                                                               struct ber_bitmask_set_work_data,
                                                               work);
    struct ber_monitor_info *bm_info = NULL;
    sxd_dev_id_t             dev_id = ber_wdata->dev_id;
    u16                      local_port = ber_wdata->local_port;
    u8                       bitmask = ber_wdata->bitmask;

    spin_lock_bh(&__ber_monitor_lock);

    bm_info = __dev_id_to_bm_info(dev_id, true);
    if (IS_ERR(bm_info)) {
        ber_wdata->ret = PTR_ERR(bm_info);
    } else {
        bm_info->port_ber_monitor_bitmask[local_port] = bitmask;

        /* If BER monitor is disabled, clear the operational state */
        if (bitmask == 0) {
            bm_info->port_ber_monitor_state[local_port] = 0;
        }
    }

    spin_unlock_bh(&__ber_monitor_lock);
    complete(ber_wdata->wq_completion);
}

/* this call should be out of the lock, it will schedule a work to do the job
 * inside of the lock
 */
int sx_core_ber_monitor_set_bitmask(sxd_dev_id_t dev_id, u16 local_port, u8 bitmask)
{
    struct completion                __ber_wq_completion;
    struct ber_bitmask_set_work_data ber_wdata;
    int                              err = 0;

    /* coverity[result_independent_of_operands] */
    if (!DEV_ID_IS_VALID(dev_id)) {
        printk(KERN_ERR "Ber-Monitor (set-bitmask): device ID %u is invalid\n", dev_id);
        err = -EINVAL;
        goto out;
    }

    if (local_port > MAX_PHYPORT_NUM) {
        printk(KERN_ERR PFX "Ber-Monitor (set-bitmask): local_port %u is invalid (max. %u)\n",
               local_port,
               MAX_PHYPORT_NUM);
        err = -EINVAL;
        goto out;
    }

    memset(&ber_wdata, 0, sizeof(ber_wdata));

    /* The ber monitor DB update is done in worker thread to prevent
     * race between DB update and PPBME handler */
    init_completion(&__ber_wq_completion);
    ber_wdata.dev_id = dev_id;
    ber_wdata.local_port = local_port;
    ber_wdata.bitmask = bitmask;
    ber_wdata.wq_completion = &__ber_wq_completion;
    INIT_WORK(&ber_wdata.work, __ber_monitor_bitmask_work_handler);
    queue_work(__ber_monitor_wq, &ber_wdata.work);

    /* Wait for DB update completion for synchronous ioctl */
    wait_for_completion_interruptible(&__ber_wq_completion);
    err = ber_wdata.ret;

    if (err) {
        printk(KERN_ERR "Ber-Monitor (set-bitmask): failed to set bitmask (dev=%u, port=%u, bitmask=%u)\n",
               dev_id, local_port, bitmask);
    }

out:
    return err;
}

static void __ber_monitor_work_handler(struct work_struct *work)
{
    struct ber_work_data      *ber_wdata = container_of(work, struct ber_work_data, dwork.work);
    struct ku_access_ppbmc_reg ppbmc_reg_data;
    struct ber_monitor_info   *bm_info = NULL;
    int                        err = 0, to_rearm = 0;

    memset(&ppbmc_reg_data, 0, sizeof(ppbmc_reg_data));

    ppbmc_reg_data.dev_id = ber_wdata->dev_id;
    sx_cmd_set_op_tlv(&ppbmc_reg_data.op_tlv, PPBMC_REG_ID, EMAD_METHOD_QUERY);

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(ppbmc_reg_data.ppbmc_reg.local_port,
                                        ppbmc_reg_data.ppbmc_reg.lp_msb,
                                        ber_wdata->local_port);

    spin_lock_bh(&__ber_monitor_lock);
    bm_info = __dev_id_to_bm_info(ber_wdata->dev_id, true);
    if (IS_ERR(bm_info)) {
        spin_unlock_bh(&__ber_monitor_lock);
        goto out;
    }

    if (bm_info->port_ber_monitor_bitmask[ber_wdata->local_port]) {
        to_rearm = 1;
    }
    spin_unlock_bh(&__ber_monitor_lock);

    if (!to_rearm) {
        if (printk_ratelimit()) {
            printk(KERN_NOTICE "Ber-Monitor (event-handler): "
                   "local port [dev-id=%u, local_port=%u] is disabled, skip re-arm\n",
                   ber_wdata->dev_id, ber_wdata->local_port);
        }

        goto out;
    }

    /* Read PPBMC */
    err = sx_ACCESS_REG_PPBMC_wrapper(bm_info->dev, EMAD_METHOD_QUERY, &ppbmc_reg_data);
    if (err) {
        printk(KERN_ERR "Ber-Monitor (event-handler) [dev_id=%u, local_port=%u]: "
               "query PPBMC failed (err %d)\n",
               ber_wdata->dev_id, ber_wdata->local_port, err);
    }

    /* If armed - no need to re-arm */
    if (ppbmc_reg_data.ppbmc_reg.e != 0) {
        if (printk_ratelimit()) {
            printk(KERN_NOTICE "Ber-Monitor (event-handler): Already armed, skip re-arm "
                   "[dev=%u, port=%u, to_rearm=%u, e=%u)\n",
                   ber_wdata->dev_id, ber_wdata->local_port, to_rearm, ppbmc_reg_data.ppbmc_reg.e);
        }
        goto out;
    }

    ppbmc_reg_data.ppbmc_reg.e = 2; /* Generate single event */
    ppbmc_reg_data.ppbmc_reg.monitor_type = 0; /* monitor type is RO field */
    sx_cmd_set_op_tlv(&ppbmc_reg_data.op_tlv, PPBMC_REG_ID, EMAD_METHOD_WRITE);

    /* Set PPBMC */
    err = sx_ACCESS_REG_PPBMC_wrapper(bm_info->dev, EMAD_METHOD_WRITE, &ppbmc_reg_data);
    if (err) {
        printk(KERN_ERR PFX "Ber-Monitor (event-handler) [dev_id=%u, local_port=%u]: "
               "set PPBMC failed (err %d)\n",
               ber_wdata->dev_id, ber_wdata->local_port, err);
    }

out:
    /* Free memory */
    kfree(ber_wdata);
}

/* this call should be out of the lock */
void sx_core_ber_monitor_handle_ppbme_event(struct completion_info *ci)
{
    struct sxd_emad_ppbme_reg* ppbme = (struct sxd_emad_ppbme_reg *)ci->skb->data;
    struct ber_monitor_info   *bm_info = NULL;
    struct ber_work_data      *ber_wdata = NULL;
    u8                         monitor_state = 0, old_monitor_state = 0, ber_monitor_bitmask = 0;
    u16                        local_port = 0;

    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, ppbme->local_port, ((ppbme->pnat_msb_monitor_type >> 4) & 0x3));

    /* coverity[result_independent_of_operands] */
    if (!DEV_ID_IS_VALID(ci->device_id)) {
        printk(KERN_ERR "Ber-Monitor (set-bitmask): device ID %u is invalid\n", ci->device_id);
        return;
    }

    if (local_port > MAX_PHYPORT_NUM) {
        printk(KERN_ERR "Ber-Monitor (event-handler) [dev_id=%u, local_port=%u]: "
               "received invalid port (max. %d)\n",
               ci->device_id, local_port, MAX_PHYPORT_NUM);
        return;
    }

    spin_lock_bh(&__ber_monitor_lock);

    bm_info = __dev_id_to_bm_info(ci->device_id, true);
    if (IS_ERR(bm_info)) {
        spin_unlock_bh(&__ber_monitor_lock);
        return;
    }

    if (printk_ratelimit()) {
        printk(KERN_NOTICE "Ber-Monitor (event-handler): [dev=%u, port=%u]\n",
               ci->device_id, local_port);
    }

    old_monitor_state = bm_info->port_ber_monitor_state[local_port];
    bm_info->port_ber_monitor_state[local_port] = ppbme->monitor_state;
    ber_monitor_bitmask = bm_info->port_ber_monitor_bitmask[local_port];

    spin_unlock_bh(&__ber_monitor_lock);

    /* If monitor state didn't change: silently drop the event */
    monitor_state = ppbme->monitor_state;
    if (old_monitor_state == monitor_state) {
        ci->info.dont_care.drop_enable = 1;
        goto rearm;
    }

    /* If user didn't request to be notified for the received monitor state:
     * Silently drop the event  */
    if (monitor_state == 0) {
        ci->info.dont_care.drop_enable = 1;
    } else if ((1 << (monitor_state - 1)) & ber_monitor_bitmask) {
        ci->info.dont_care.drop_enable = 0;
    } else {
        ci->info.dont_care.drop_enable = 1;
    }

rearm:
    /* Re-arm */
    ber_wdata = kzalloc(sizeof(*ber_wdata), GFP_ATOMIC);
    if (!ber_wdata) {
        printk(KERN_ERR "Ber-Monitor (event-handler) [dev_id=%u, local_port=%u]: "
               "failed to allocate re-arm event\n",
               ci->device_id, local_port);
        return;
    }

    ber_wdata->dev_id = ci->device_id;
    ber_wdata->local_port = local_port;
    INIT_DELAYED_WORK(&ber_wdata->dwork, __ber_monitor_work_handler);
    queue_delayed_work(__ber_monitor_wq, &ber_wdata->dwork, 0);
}

int sx_core_ber_monitor_dump(struct seq_file *m, void *v, void *context)
{
    struct ber_monitor_info *bm_info = NULL;
    const char             * state_2_str[] = {"Disable", "Normal", "Warning", "Alarm"};
    const char             * bitmask_2_str[] = {"Disable", "N", "W", "NW", "A", "AN", "AW", "ANW"};
    char                     dev_and_port[20];
    sxd_dev_id_t             dev_id = 0;
    int                      local_port = 0;
    u8                       bitmask = 0;
    u8                       state = 0;
    struct sx_dev          * dev = sx_dbg_dump_get_device(m);

    if (!dev) {
        return 0;
    }
    dev_id = dev->device_id;
    sx_dbg_dump_print_header(m, "BER monitor dump");

    sx_dbg_dump_print_table_header(m, "%-11s| %-11s| %-11s",
                                   "dev/port", "bitmask", "state");

    spin_lock_bh(&__ber_monitor_lock);

    /* coverity[result_independent_of_operands] */

    bm_info = __dev_id_to_bm_info(dev_id, false);

    if (IS_ERR(bm_info)) {
        return 0;
    }

    if (bm_info->port_ber_monitor_bitmask[local_port] != 0) {
        bitmask = bm_info->port_ber_monitor_bitmask[local_port];
        state = bm_info->port_ber_monitor_state[local_port];
        snprintf(dev_and_port, sizeof(dev_and_port), "%u/%u", dev_id, local_port);

        if ((bitmask < 8) && (state < 4)) {
            seq_printf(m, "%-11s| %-11s| %-11s\n",
                       dev_and_port,
                       bitmask_2_str[bitmask],
                       state_2_str[state]);
        } else {
            seq_printf(m, "%-11s| %-11d| %-11d\n",
                       dev_and_port,
                       bitmask,
                       state);
        }
    }

    spin_unlock_bh(&__ber_monitor_lock);

    sx_dbg_dump_print_empty_line(m);
    return 0;
}
