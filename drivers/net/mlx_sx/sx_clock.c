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

#include <linux/version.h>
#include <linux/clocksource.h>
#include <linux/delay.h>
#include <linux/seq_file.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include "sx_clock.h"
#include "sx.h"

static struct sx_priv          *__priv;
static struct workqueue_struct *__clock_wq;
static struct sx_clock_log_db   __log_settime;
static struct sx_clock_log_db   __log_adjtime;
static struct sx_clock_log_db   __log_adjfreq;


void sx_clock_fill_hwtstamp_nsec(u64 nsec, struct skb_shared_hwtstamps *hwts)
{
    memset(hwts, 0, sizeof(*hwts));
    hwts->hwtstamp = ns_to_ktime(nsec);
}


static int __sx_clock_init(struct sx_priv *priv)
{
    int err = 0;

    __priv = priv;

    __clock_wq = create_singlethread_workqueue("sx_clock_wq");
    if (!__clock_wq) {
        err = -ENOMEM;
        goto out;
    }

    priv->hw_clock_frc_base = ioremap(pci_resource_start(priv->dev.pdev, priv->fw.frc_bar) +
                                      priv->fw.frc_offset, 8);
    if (!priv->hw_clock_frc_base) {
        printk(KERN_ERR "could not remap FRC register\n");
        err = -ENOMEM;
        goto out;
    }

    priv->hw_clock_utc_sec = ioremap(pci_resource_start(priv->dev.pdev, priv->fw.utc_sec_bar) +
                                     priv->fw.utc_sec_offset, 4);
    if (!priv->hw_clock_utc_sec) {
        printk(KERN_ERR "could not remap UTC-sec register\n");
        err = -ENOMEM;
        goto out;
    }

    priv->hw_clock_utc_nsec = ioremap(pci_resource_start(priv->dev.pdev, priv->fw.utc_nsec_bar) +
                                      priv->fw.utc_nsec_offset, 4);
    if (!priv->hw_clock_utc_nsec) {
        printk(KERN_ERR "could not remap UTC-nsec register\n");
        err = -ENOMEM;
        goto out;
    }

    sx_clock_log_init(&__log_settime);
    sx_clock_log_init(&__log_adjfreq);
    sx_clock_log_init(&__log_adjtime);

    err = SX_CLOCK_DEV_SPECIFIC_CB(&priv->dev, sx_clock_init, priv);
    if (err) {
        printk(KERN_ERR "chip-specific clock init failed (err=%d)\n", err);
        goto out;
    }

out:

    if (err) {
        if (__clock_wq) {
            destroy_workqueue(__clock_wq);
            __clock_wq = NULL;
        }

        if (priv->hw_clock_frc_base) {
            iounmap(priv->hw_clock_frc_base);
            priv->hw_clock_frc_base = NULL;
        }

        if (priv->hw_clock_utc_sec) {
            iounmap(priv->hw_clock_utc_sec);
            priv->hw_clock_utc_sec = NULL;
        }

        if (priv->hw_clock_utc_nsec) {
            iounmap(priv->hw_clock_utc_nsec);
            priv->hw_clock_utc_nsec = NULL;
        }
    }

    return err;
}


static int __sx_clock_deinit(struct sx_priv *priv)
{
    int err;

    err = SX_CLOCK_DEV_SPECIFIC_CB(&priv->dev, sx_clock_cleanup, priv);
    if (err) {
        printk(KERN_ERR "chip-specific clock cleanup failed (err=%d)\n", err);
    }

    if (priv->tstamp.ptp) {
        ptp_clock_unregister(priv->tstamp.ptp);
        priv->tstamp.ptp = NULL;
    }

    destroy_workqueue(__clock_wq);
    iounmap(priv->hw_clock_frc_base);
    iounmap(priv->hw_clock_utc_sec);
    iounmap(priv->hw_clock_utc_nsec);
    return 0;
}


int sx_clock_register(struct sx_priv *priv, const struct ptp_clock_info *ptp_clock_info)
{
    /* Register PTP clock */
    memcpy(&priv->tstamp.ptp_info, ptp_clock_info, sizeof(priv->tstamp.ptp_info));
    snprintf(priv->tstamp.ptp_info.name, 16, "sx_ptp");

    priv->tstamp.ptp = ptp_clock_register(&priv->tstamp.ptp_info, &priv->dev.pdev->dev);
    if (IS_ERR(priv->tstamp.ptp)) {
        printk(KERN_ERR "Failed to register ptp clock.\n");
        priv->tstamp.ptp = NULL;
        return -EINVAL;
    }

    return 0;
}


int sx_clock_queue_delayed_work(struct delayed_work *dwork, unsigned long delay)
{
    return queue_delayed_work(__clock_wq, dwork, delay);
}


struct sx_dev * sx_clock_get_dev(void)
{
    return (__priv) ? &__priv->dev : NULL;
}


int sx_core_clock_cqe_ts_to_utc(struct sx_priv *priv, const struct timespec *cqe_ts, struct timespec *utc)
{
    int err;

    err = SX_CLOCK_DEV_SPECIFIC_CB(&priv->dev, sx_clock_cqe_ts_to_utc, priv, cqe_ts, utc);
    if (err) {
        printk(KERN_ERR "chip-specific clock cqe_ts_to_utc failed (err=%d)\n", err);
    }

    return err;
}


int sx_core_clock_init(struct sx_priv *priv)
{
    u8  clock_supported = SX_CLOCK_IS_DEV_SPECIFIC_CB_SUPPORTED(&priv->dev, sx_clock_init);
    int err = 0;

    if (clock_supported) {
        err = __sx_clock_init(priv);
    }

    return err;
}


int sx_core_clock_deinit(struct sx_priv *priv)
{
    u8  clock_supported = SX_CLOCK_IS_DEV_SPECIFIC_CB_SUPPORTED(&priv->dev, sx_clock_cleanup);
    int err = 0;

    if (clock_supported) {
        err = __sx_clock_deinit(priv);
    }

    return err;
}


void sx_clock_log_init(struct sx_clock_log_db *log_db)
{
    memset(log_db, 0, sizeof(*log_db));
    spin_lock_init(&log_db->lock);
}


void sx_clock_log_add(struct sx_clock_log_db *log_db, s64 value)
{
    spin_lock_bh(&log_db->lock);
    log_db->vec[log_db->next].value = value;
    log_db->vec[log_db->next].jiffies = jiffies;
    if (log_db->size < SX_CLOCK_LOG_DB_SIZE) {
        log_db->size++;
    }
    log_db->next = (log_db->next + 1) % SX_CLOCK_LOG_DB_SIZE;
    spin_unlock_bh(&log_db->lock);
}


void sx_clock_log_dump(struct sx_clock_log_db *log_db, struct seq_file *m, const char *title)
{
    u32           count, i;
    unsigned long now = jiffies;
    unsigned int  diff_msecs;

    seq_printf(m, "%s\n", title);
    seq_printf(m, "-----------------\n");

    spin_lock_bh(&log_db->lock);

    i = (log_db->next == 0) ? (SX_CLOCK_LOG_DB_SIZE - 1) : log_db->next - 1;
    count = log_db->size;

    while (count--) {
        diff_msecs = jiffies_to_msecs(now - log_db->vec[i].jiffies);

        seq_printf(m, "%-9lld   [%u.%03u secs ago]\n",
                   log_db->vec[i].value,
                   diff_msecs / 1000,
                   diff_msecs % 1000);

        if (i == 0) {
            i = SX_CLOCK_LOG_DB_SIZE - 1;
        } else {
            i--;
        }
    }

    spin_unlock_bh(&log_db->lock);

    seq_printf(m, "\n\n");
}


void sx_clock_log_add_settime(s64 value)
{
    sx_clock_log_add(&__log_settime, value);
}


void sx_clock_log_add_adjtime(s64 value)
{
    sx_clock_log_add(&__log_adjtime, value);
}


void sx_clock_log_add_adjfreq(s64 value)
{
    sx_clock_log_add(&__log_adjfreq, value);
}


int sx_dbg_clock_dump_proc_show(struct seq_file *m, void *v)
{
    struct sx_dev  *dev;
    struct sx_priv *priv;

    dev = sx_clock_get_dev();
    if (!dev) {
        return 0;
    }

    priv = sx_priv(dev);

    seq_printf(m, "HW Clock Dump\n");
    seq_printf(m, "-------------\n");

    SX_CLOCK_DEV_SPECIFIC_CB(dev, sx_clock_dump, m, v);

    sx_clock_log_dump(&__log_settime, m, "set-time log");
    sx_clock_log_dump(&__log_adjfreq, m, "adj-freq log");
    sx_clock_log_dump(&__log_adjtime, m, "adj-time log");

    seq_printf(m, "\n\n");
    return 0;
}
