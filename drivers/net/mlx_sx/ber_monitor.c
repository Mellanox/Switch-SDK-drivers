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

#include <linux/types.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/seq_file.h>

#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/cmd.h>

#include "sx.h"
#include "sx_dbg_dump_proc.h"
#include "ber_monitor.h"

#define BM_PORT_INFO_ARR_SIZE ((MAX_PHYPORT_NUM)+1)
#define BM_DEV_ARR_SIZE       ((MAX_NUM_OF_REMOTE_SWITCHES)+1)

struct ber_bitmask_set_work_data {
    struct completion *wq_completion;
    u8                 dev_id;
    u8                 local_port;
    u8                 bitmask;
    int                ret;
    struct work_struct work;
};
struct ber_work_data {
    u8                  dev_id;
    u8                  local_port;
    struct delayed_work dwork;
};
struct ber_monitor_dev_db {
    u8 port_ber_monitor_bitmask[BM_PORT_INFO_ARR_SIZE];
    u8 port_ber_monitor_state[BM_PORT_INFO_ARR_SIZE];
};
static struct ber_monitor_dev_db *__ber_monitor_db[BM_DEV_ARR_SIZE];
static struct sx_priv            *__priv = NULL;

int sx_core_ber_monitor_init(struct sx_dev *dev)
{
    int err = 0;

    printk(KERN_INFO "Ber-Monitor (init)\n");

    if (!dev) {
        printk(KERN_ERR "Ber-Monitor (init): no device to work on\n");
        err = -EINVAL;
        goto out;
    }

    memset(__ber_monitor_db, 0, sizeof(__ber_monitor_db));
    __priv = sx_priv(dev);

out:
    return err;
}

void sx_core_ber_monitor_deinit(void)
{
    unsigned long flags;
    int           dev_id;

    printk(KERN_INFO "Ber-Monitor (deinit)\n");

    if (!__priv) {
        return;
    }

    spin_lock_irqsave(&__priv->db_lock, flags);

    for (dev_id = 0; dev_id < BM_DEV_ARR_SIZE; dev_id++) {
        if (__ber_monitor_db[dev_id]) {
            kfree(__ber_monitor_db[dev_id]);
        }
    }

    spin_unlock_irqrestore(&__priv->db_lock, flags);
    __priv = NULL;
}

static int __create_ber_monitor_dev_db(u8 dev_id)
{
    __ber_monitor_db[dev_id] = kzalloc(sizeof(struct ber_monitor_dev_db), GFP_ATOMIC);
    return __ber_monitor_db[dev_id] != NULL ? 0 : -ENOMEM;
}

/* function should be called when sx_priv->db_lock is locked */
int sx_core_ber_monitor_set_state(u8 dev_id, u8 local_port, u8 state)
{
    int err = 0;

    if (local_port > MAX_PHYPORT_NUM) {
        printk(KERN_ERR "Ber-Monitor (set-state): local port %u is invalid (max. %u)\n",
               local_port,
               MAX_PHYPORT_NUM);
        err = -EINVAL;
        goto out;
    }

    if (!__ber_monitor_db[dev_id]) {
        err = __create_ber_monitor_dev_db(dev_id);
        if (err) {
            goto out;
        }
    }

    __ber_monitor_db[dev_id]->port_ber_monitor_state[local_port] = state;

out:
    return err;
}

static void __ber_monitor_bitmask_work_handler(struct work_struct *work)
{
    struct ber_bitmask_set_work_data *ber_wdata = container_of(work,
                                                               struct ber_bitmask_set_work_data,
                                                               work);
    unsigned long flags;
    u8            dev_id = ber_wdata->dev_id;
    u8            local_port = ber_wdata->local_port;
    u8            bitmask = ber_wdata->bitmask;
    int           err = 0;

    spin_lock_irqsave(&__priv->db_lock, flags);

    if (!__ber_monitor_db[dev_id]) {
        err = __create_ber_monitor_dev_db(dev_id);
        if (err) {
            ber_wdata->ret = err;
            goto unlock;
        }
    }

    __ber_monitor_db[dev_id]->port_ber_monitor_bitmask[local_port] = bitmask;

    /* If BER monitor is disable: clear the operational state */
    if (bitmask == 0) {
        __ber_monitor_db[dev_id]->port_ber_monitor_state[local_port] = 0;
    }

unlock:
    spin_unlock_irqrestore(&__priv->db_lock, flags);
    complete(ber_wdata->wq_completion);
}

/* this call should be out of the lock, it will schedule a work to do the job
 * inside of the lock
 */
int sx_core_ber_monitor_set_bitmask(u8 dev_id, u8 local_port, u8 bitmask)
{
    struct completion                __ber_wq_completion;
    struct ber_bitmask_set_work_data ber_wdata;
    int                              err = 0;

    if (!__priv) {
        printk(KERN_ERR "Ber-Monitor (set-bitmask): no device to work on\n");
        err = -ENODEV;
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
    queue_work(__priv->dev.generic_wq, &ber_wdata.work);

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

/* function should be called when sx_priv->db_lock is locked */
int sx_core_ber_monitor_serialize(struct ku_sx_core_db __user *sx_core_db)
{
    int dev_id;
    int err = 0;

    for (dev_id = 0; dev_id < BM_DEV_ARR_SIZE; dev_id++) {
        if (__ber_monitor_db[dev_id]) {
            err = copy_to_user(&sx_core_db->port_ber_monitor_bitmask[dev_id],
                               &__ber_monitor_db[dev_id]->port_ber_monitor_bitmask,
                               sizeof(sx_core_db->port_ber_monitor_bitmask[dev_id]));
            if (err) {
                goto out;
            }

            err = copy_to_user(&sx_core_db->port_ber_monitor_state[dev_id],
                               &__ber_monitor_db[dev_id]->port_ber_monitor_state,
                               sizeof(sx_core_db->port_ber_monitor_state[dev_id]));
            if (err) {
                goto out;
            }
        } else {
            err = clear_user(&sx_core_db->port_ber_monitor_bitmask[dev_id],
                             sizeof(sx_core_db->port_ber_monitor_bitmask[dev_id]));
            if (err) {
                goto out;
            }

            err = clear_user(&sx_core_db->port_ber_monitor_state[dev_id],
                             sizeof(sx_core_db->port_ber_monitor_state[dev_id]));
            if (err) {
                goto out;
            }
        }
    }

out:
    if (err) {
        printk(KERN_ERR "Ber-Monitor (serialize): internal error (err=%d)\n", err);
    }

    return err;
}

/* function should be called when sx_priv->db_lock is locked */
int sx_core_ber_monitor_deserialize(const struct ku_sx_core_db *sx_core_db)
{
    int dev_id = 0;
    int local_port = 0;
    u8  state = 0;
    u8  bitmask = 0;
    int err = 0;

    for (dev_id = 0; dev_id < BM_DEV_ARR_SIZE; dev_id++) {
        for (local_port = 0; local_port < BM_PORT_INFO_ARR_SIZE; local_port++) {
            state = sx_core_db->port_ber_monitor_state[dev_id][local_port];
            bitmask = sx_core_db->port_ber_monitor_bitmask[dev_id][local_port];

            if (bitmask) { /* ber-monitor is enabled on the port */
                if (!__ber_monitor_db[dev_id]) {
                    err = __create_ber_monitor_dev_db(dev_id);
                    if (err) {
                        goto out;
                    }
                }

                __ber_monitor_db[dev_id]->port_ber_monitor_state[local_port] = state;
                __ber_monitor_db[dev_id]->port_ber_monitor_bitmask[local_port] = bitmask;
            }
        }
    }

out:
    if (err) {
        printk(KERN_ERR "Ber-Monitor (deserialize): internal error (err=%d)\n", err);
    }

    return err;
}

static void __ber_monitor_work_handler(struct work_struct *work)
{
    struct ber_work_data      *ber_wdata = container_of(work, struct ber_work_data, dwork.work);
    struct ku_access_ppbmc_reg ppbmc_reg_data;
    int                        err = 0, to_rearm = 0;
    unsigned long              flags;

    memset(&ppbmc_reg_data, 0, sizeof(ppbmc_reg_data));

    ppbmc_reg_data.dev_id = ber_wdata->dev_id;
    sx_cmd_set_op_tlv(&ppbmc_reg_data.op_tlv, PPBMC_REG_ID, 1);
    ppbmc_reg_data.ppbmc_reg.local_port = ber_wdata->local_port;

    spin_lock_irqsave(&__priv->db_lock, flags);
    if (__ber_monitor_db[ber_wdata->dev_id]->port_ber_monitor_bitmask[ber_wdata->local_port]) {
        to_rearm = 1;
    }
    spin_unlock_irqrestore(&__priv->db_lock, flags);

    if (!to_rearm) {
        if (printk_ratelimit()) {
            printk(KERN_NOTICE "Ber-Monitor (event-handler): "
                   "local port [dev-id=%u, local_port=%u] is disabled, skip re-arm\n",
                   ber_wdata->dev_id, ber_wdata->local_port);
        }

        goto out;
    }

    /* Read PPBMC */
    err = sx_ACCESS_REG_PPBMC(&__priv->dev, &ppbmc_reg_data);
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
    sx_cmd_set_op_tlv(&ppbmc_reg_data.op_tlv, PPBMC_REG_ID, 2);

    /* Set PPBMC */
    err = sx_ACCESS_REG_PPBMC(&__priv->dev, &ppbmc_reg_data);
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
    struct ber_work_data      *ber_wdata = NULL;
    u8                         monitor_state = 0, old_monitor_state = 0, ber_monitor_bitmask = 0;
    unsigned long              flags;

    if (!__priv) {
        printk(KERN_ERR "Ber-Monitor (event-handler): no device to work on\n");
        return;
    }

    if (!__ber_monitor_db[ci->device_id]) {
        printk(KERN_ERR "Ber-Monitor (event-handler) [dev_id=%u]: "
               "received event from an unknown device\n",
               ci->device_id);
    }

    if (ppbme->local_port > MAX_PHYPORT_NUM) {
        printk(KERN_ERR "Ber-Monitor (event-handler) [dev_id=%u, local_port=%u]: "
               "received invalid port (max. %d)\n",
               ci->device_id, ppbme->local_port, MAX_PHYPORT_NUM);
        return;
    }

    if (printk_ratelimit()) {
        printk(KERN_NOTICE "Ber-Monitor (event-handler): [dev=%u, port=%u]\n",
               ci->device_id, ppbme->local_port);
    }

    spin_lock_irqsave(&__priv->db_lock, flags);
    old_monitor_state = __ber_monitor_db[ci->device_id]->port_ber_monitor_state[ppbme->local_port];
    __ber_monitor_db[ci->device_id]->port_ber_monitor_state[ppbme->local_port] = ppbme->monitor_state;
    ber_monitor_bitmask = __ber_monitor_db[ci->device_id]->port_ber_monitor_bitmask[ppbme->local_port];
    spin_unlock_irqrestore(&__priv->db_lock, flags);

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
               ci->device_id, ppbme->local_port);
        return;
    }

    ber_wdata->dev_id = ci->device_id;
    ber_wdata->local_port = ppbme->local_port;
    INIT_DELAYED_WORK(&ber_wdata->dwork, __ber_monitor_work_handler);
    queue_delayed_work(__priv->dev.generic_wq, &ber_wdata->dwork, 0);
}

int sx_core_ber_monitor_dump(struct seq_file *m, void *v)
{
    const char  * state_2_str[] = {"Disable", "Normal", "Warning", "Alarm"};
    const char  * bitmask_2_str[] = {"Disable", "N", "W", "NW", "A", "AN", "AW", "ANW"};
    char          dev_and_port[20];
    unsigned long flags;
    int           dev_id = 0;
    int           local_port = 0;
    u8            bitmask = 0;
    u8            state = 0;

    if (!__priv) {
        return 0;
    }

    print_header(m, "BER monitor dump");

    print_table_header(m, "%-11s| %-11s| %-11s",
                       "dev/port", "bitmask", "state");

    spin_lock_irqsave(&__priv->db_lock, flags);

    for (dev_id = 0; dev_id < BM_DEV_ARR_SIZE; dev_id++) {
        if (!__ber_monitor_db[dev_id]) {
            continue;
        }

        for (local_port = 0; local_port < BM_PORT_INFO_ARR_SIZE; local_port++) {
            if (__ber_monitor_db[dev_id]->port_ber_monitor_bitmask[local_port] != 0) {
                bitmask = __ber_monitor_db[dev_id]->port_ber_monitor_bitmask[local_port];
                state = __ber_monitor_db[dev_id]->port_ber_monitor_state[local_port];
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
        }
    }

    spin_unlock_irqrestore(&__priv->db_lock, flags);

    print_empty_line(m);
    return 0;
}
