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

/************************************************
 * Includes
 ***********************************************/

#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/mlx_sx/device.h>
#include "sx.h"

/************************************************
 * Definitions
 ***********************************************/

enum {
    SX_CATAS_POLL_INTERVAL = 5 * HZ,
};

/************************************************
 * Globals
 ***********************************************/

static DEFINE_SPINLOCK(catas_lock);
static LIST_HEAD(catas_list);

static int internal_err_reset = 1;
module_param(internal_err_reset, int, 0644);
MODULE_PARM_DESC(internal_err_reset,
                 "Reset device on internal errors if non-zero (default 1)");

/************************************************
 * Functions
 ***********************************************/

static void dump_err_buf(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);
    int             i;

    sx_err(dev, "Internal error detected:\n");
    for (i = 0; i < priv->fw.catas_size; ++i) {
        sx_err(dev, "  buf[%02x]: %08x\n",
               i, swab32(__raw_readl(priv->catas_err.map + i)));
    }
}

static void poll_catas(unsigned long dev_ptr)
{
    struct sx_dev  *dev = (struct sx_dev *)dev_ptr;
    struct sx_priv *priv = sx_priv(dev);

    if (__raw_readl(priv->catas_err.map)) {
        dump_err_buf(dev);

        sx_send_health_event(dev->device_id, SXD_HEALTH_CAUSE_CATAS);

        sx_core_dispatch_event(dev,
                               SX_DEV_EVENT_CATASTROPHIC_ERROR, NULL);

        if (internal_err_reset) {
            spin_lock(&catas_lock);
            list_add(&priv->catas_err.list, &catas_list);
            spin_unlock(&catas_lock);
            queue_work(dev->generic_wq, &dev->catas_work);
        }
    } else {
        mod_timer(&priv->catas_err.timer,
                  round_jiffies(jiffies + SX_CATAS_POLL_INTERVAL));
    }
}

static void catas_reset(struct work_struct *work)
{
    struct sx_priv *priv, *tmppriv;
    struct sx_dev  *dev;
    unsigned long   flags;

    LIST_HEAD(tlist);
    int ret;

    spin_lock_irqsave(&catas_lock, flags);
    list_splice_init(&catas_list, &tlist);
    spin_unlock_irqrestore(&catas_lock, flags);

    list_for_each_entry_safe(priv, tmppriv, &tlist, catas_err.list) {
        ret = sx_restart_one_pci(priv->dev.pdev);
        dev = &priv->dev;
        if (ret) {
            sx_err(dev, "Reset failed (%d)\n", ret);
        } else {
            sx_dbg(dev, "Reset succeeded\n");
        }
    }
}

void sx_core_start_catas_poll(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);

    if (dev->catas_poll_running) {
        return;
    }

    INIT_LIST_HEAD(&priv->catas_err.list);
    init_timer(&priv->catas_err.timer);
    priv->catas_err.map = NULL;

    if (!priv->fw.catas_size) {
        return;
    }

    priv->catas_err.map =
        ioremap(pci_resource_start(dev->pdev, priv->fw.catas_bar) +
                priv->fw.catas_offset, priv->fw.catas_size * 4);
    if (!priv->catas_err.map) {
        sx_warn(dev, "Failed to map internal error buffer at 0x%llx\n",
                pci_resource_start(dev->pdev, priv->fw.catas_bar) +
                priv->fw.catas_offset);
        return;
    }

    priv->catas_err.timer.data = (unsigned long)dev;
    priv->catas_err.timer.function = poll_catas;
    priv->catas_err.timer.expires =
        round_jiffies(jiffies + SX_CATAS_POLL_INTERVAL);
    add_timer(&priv->catas_err.timer);
    dev->catas_poll_running = 1;
}

void sx_core_stop_catas_poll(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);

    if (!dev->catas_poll_running) {
        return;
    }

    del_timer_sync(&priv->catas_err.timer);
    if (priv->catas_err.map) {
        iounmap(priv->catas_err.map);
    }

    dev->catas_poll_running = 0;
}

int sx_core_catas_init(struct sx_dev *dev)
{
    INIT_WORK(&dev->catas_work, catas_reset);
    dev->catas_poll_running = 0;

    dev->generic_wq = create_singlethread_workqueue("sx_err");
    if (!dev->generic_wq) {
        return -ENOMEM;
    }

    return 0;
}

void sx_core_catas_cleanup(struct sx_dev *dev)
{
    destroy_workqueue(dev->generic_wq);
}
