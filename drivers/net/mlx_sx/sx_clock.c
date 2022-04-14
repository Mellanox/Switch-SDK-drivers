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

#include <linux/version.h>
#include <linux/module.h>
#include <linux/clocksource.h>
#include <linux/delay.h>
#include <linux/seq_file.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include "sx_clock.h"
#include "sx.h"
#include "dev_db.h"

int clock_activity_log = 0;
module_param_named(clock_activity_log, clock_activity_log, int, 0644);
MODULE_PARM_DESC(clock_activity_log, "en/dis clock activity log");

static struct workqueue_struct *__clock_wq;

int sx_core_clock_init(void)
{
    __clock_wq = create_singlethread_workqueue("sx_clock_wq");
    if (!__clock_wq) {
        printk(KERN_ERR "Failed to create clock work queue.\n");
        return -ENOMEM;
    }

    return 0;
}

void sx_core_clock_deinit(void)
{
    flush_workqueue(__clock_wq);
    destroy_workqueue(__clock_wq);
    __clock_wq = NULL;
}

void sx_clock_fill_hwtstamp_nsec(u64 nsec, struct skb_shared_hwtstamps *hwts)
{
    memset(hwts, 0, sizeof(*hwts));
    hwts->hwtstamp = ns_to_ktime(nsec);
}


static int __sx_clock_dev_init(struct sx_priv *priv)
{
    int err = 0;

    sx_clock_log_init(&priv->hw_clock.log_settime, 10);
    sx_clock_log_init(&priv->hw_clock.log_adjfreq, 10);
    sx_clock_log_init(&priv->hw_clock.log_adjtime, 10);
    sx_clock_log_init(&priv->hw_clock.log_activity, 1000);

    err = SX_CLOCK_DEV_SPECIFIC_CB(&priv->dev, sx_clock_dev_init, priv);
    if (err) {
        printk(KERN_ERR "chip-specific clock init failed (err=%d)\n", err);
        goto out;
    }

out:
    if (err) {
        sx_clock_log_deinit(&priv->hw_clock.log_activity);
        sx_clock_log_deinit(&priv->hw_clock.log_adjtime);
        sx_clock_log_deinit(&priv->hw_clock.log_adjfreq);
        sx_clock_log_deinit(&priv->hw_clock.log_settime);
    }

    return err;
}


static int __sx_clock_dev_deinit(struct sx_priv *priv)
{
    int err;

    err = SX_CLOCK_DEV_SPECIFIC_CB(&priv->dev, sx_clock_dev_cleanup, priv);
    if (err) {
        printk(KERN_ERR "chip-specific clock cleanup failed (err=%d)\n", err);
    }

    if (priv->hw_clock.clock) {
        ptp_clock_unregister(priv->hw_clock.clock);
        priv->hw_clock.clock = NULL;
    }

    sx_clock_log_deinit(&priv->hw_clock.log_settime);
    sx_clock_log_deinit(&priv->hw_clock.log_adjfreq);
    sx_clock_log_deinit(&priv->hw_clock.log_adjtime);
    sx_clock_log_deinit(&priv->hw_clock.log_activity);
    return 0;
}


int sx_clock_register(struct sx_priv *priv, const struct ptp_clock_info *ptp_clock_info)
{
    /* Register PTP clock */
    memcpy(&priv->hw_clock.clock_info, ptp_clock_info, sizeof(struct ptp_clock_info));
    snprintf(priv->hw_clock.clock_info.name, 16, "sx_ptp");

    priv->hw_clock.clock = ptp_clock_register(&priv->hw_clock.clock_info, &priv->dev.pdev->dev);
    if (IS_ERR(priv->hw_clock.clock)) {
        printk(KERN_ERR "Failed to register ptp clock.\n");
        priv->hw_clock.clock = NULL;
        return -EINVAL;
    }

    return 0;
}


int sx_clock_queue_delayed_work(struct delayed_work *dwork, unsigned long delay)
{
    return queue_delayed_work(__clock_wq, dwork, delay);
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
int sx_core_clock_cqe_ts_to_utc(struct sx_priv *priv, const struct timespec64 *cqe_ts, struct timespec64 *utc)
#else
int sx_core_clock_cqe_ts_to_utc(struct sx_priv *priv, const struct timespec *cqe_ts, struct timespec *utc)
#endif
{
    int err;

    err = SX_CLOCK_DEV_SPECIFIC_CB(&priv->dev, sx_clock_cqe_ts_to_utc, priv, cqe_ts, utc);
    if (err) {
        printk(KERN_ERR "chip-specific clock cqe_ts_to_utc failed (err=%d)\n", err);
    }

    return err;
}


int sx_core_clock_dev_init(struct sx_priv *priv)
{
    u8  clock_supported = SX_CLOCK_IS_DEV_SPECIFIC_CB_SUPPORTED(&priv->dev, sx_clock_dev_init);
    int err = 0;

    if (clock_supported) {
        err = __sx_clock_dev_init(priv);
    }

    return err;
}


int sx_core_clock_dev_deinit(struct sx_priv *priv)
{
    u8  clock_supported = SX_CLOCK_IS_DEV_SPECIFIC_CB_SUPPORTED(&priv->dev, sx_clock_dev_cleanup);
    int err = 0;

    if (clock_supported) {
        err = __sx_clock_dev_deinit(priv);
    }

    return err;
}


int sx_clock_log_init(struct sx_clock_log_db *log_db, u32 cyc_buff_size)
{
    struct sx_clock_log_entry *cyc_buff;

    if (cyc_buff_size == 0) {
        return -EINVAL;
    }

    cyc_buff = kmalloc(cyc_buff_size * sizeof(struct sx_clock_log_entry), GFP_KERNEL);
    if (!cyc_buff) {
        return -ENOMEM;
    }

    memset(log_db, 0, sizeof(*log_db));
    log_db->cyc_buff = cyc_buff;
    log_db->cyc_buff_size = cyc_buff_size;
    spin_lock_init(&log_db->lock);
    return 0;
}


void sx_clock_log_deinit(struct sx_clock_log_db *log_db)
{
    if (log_db->cyc_buff) {
        kfree(log_db->cyc_buff);
    }
}


/* must be called within log lock */
static void __sx_clock_log_done(struct sx_clock_log_db *log_db)
{
    log_db->cyc_buff[log_db->next].jiffies = jiffies;
    if (log_db->size < log_db->cyc_buff_size) {
        log_db->size++;
    }
    log_db->next++;
    if (log_db->next == log_db->cyc_buff_size) {
        log_db->next = 0;
    }
}


int sx_clock_log_add_string(struct sx_clock_log_db *log_db, const char *fmt, ...)
{
    va_list args;
    int     ret;

    va_start(args, fmt);

    spin_lock_bh(&log_db->lock);
    log_db->cyc_buff[log_db->next].type = LOG_TYPE_STRING_E;
    ret = vsnprintf(log_db->cyc_buff[log_db->next].value.val_str,
                    sizeof(log_db->cyc_buff[log_db->next].value.val_str),
                    fmt,
                    args);

    __sx_clock_log_done(log_db);
    spin_unlock_bh(&log_db->lock);

    va_end(args);
    return ret;
}


void sx_clock_log_add_s64(struct sx_clock_log_db *log_db, s64 value)
{
    spin_lock_bh(&log_db->lock);
    log_db->cyc_buff[log_db->next].type = LOG_TYPE_S64_E;
    log_db->cyc_buff[log_db->next].value.val_s64 = value;
    __sx_clock_log_done(log_db);
    spin_unlock_bh(&log_db->lock);
}


void sx_clock_log_dump(struct sx_clock_log_db *log_db, struct seq_file *m, const char *title)
{
    struct tm tm;
    u64       diff_usec, msec;
    u32       count, i;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    struct timespec64 tv, now;
    ktime_get_real_ts64(&now);
#else
    struct timeval tv, now;
    do_gettimeofday(&now);
#endif

    now.tv_sec -= sys_tz.tz_minuteswest * 60;

    seq_printf(m, "%s\n", title);
    seq_printf(m, "-----------------\n");

    spin_lock_bh(&log_db->lock);

    i = (log_db->size == log_db->cyc_buff_size) ? log_db->next : 0;
    count = log_db->size;

    while (count--) {
        msec = jiffies_to_msecs(jiffies - log_db->cyc_buff[i].jiffies);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
        diff_usec = (now.tv_sec * 1000000 + now.tv_nsec / 1000) - msec * 1000;
        tv.tv_sec = diff_usec / 1000000;
        tv.tv_nsec = (diff_usec % 1000000) * 1000;
        time64_to_tm(tv.tv_sec, 0, &tm);
#else
        diff_usec = (now.tv_sec * 1000000 + now.tv_usec) - msec * 1000;
        tv.tv_sec = diff_usec / 1000000;
        tv.tv_usec = diff_usec % 1000000;
        time_to_tm(tv.tv_sec, 0, &tm);
#endif

        switch (log_db->cyc_buff[i].type) {
        case LOG_TYPE_STRING_E:
            seq_printf(m, "%04d-%02d-%02d %02d:%02d:%02d.%03u    %s\n",
                       (int)(1900 + tm.tm_year),
                       tm.tm_mon + 1,
                       tm.tm_mday,
                       tm.tm_hour,
                       tm.tm_min,
                       tm.tm_sec,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                       (u32)(tv.tv_nsec / 1000000),
#else
                       (u32)(tv.tv_usec / 1000),
#endif
                       log_db->cyc_buff[i].value.val_str);
            break;

        case LOG_TYPE_S64_E:
            seq_printf(m, "%04d-%02d-%02d %02d:%02d:%02d.%03u    %lld\n",
                       (int)(1900 + tm.tm_year),
                       tm.tm_mon + 1,
                       tm.tm_mday,
                       tm.tm_hour,
                       tm.tm_min,
                       tm.tm_sec,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                       (u32)(tv.tv_nsec / 1000000),
#else
                       (u32)(tv.tv_usec / 1000),
#endif
                       log_db->cyc_buff[i].value.val_s64);
            break;
        }

        if (++i == log_db->cyc_buff_size) {
            i = 0;
        }
    }

    spin_unlock_bh(&log_db->lock);

    seq_printf(m, "\n\n");
}


void sx_clock_log_add_settime(struct sx_priv *priv, s64 value)
{
    sx_clock_log_add_s64(&priv->hw_clock.log_settime, value);
    SX_CLOCK_ACTIVITY_LOG(priv, "SET_TIME %lld", value);
}


void sx_clock_log_add_adjtime(struct sx_priv *priv, s64 value)
{
    sx_clock_log_add_s64(&priv->hw_clock.log_adjtime, value);
    SX_CLOCK_ACTIVITY_LOG(priv, "ADJ_TIME %lld", value);
}


void sx_clock_log_add_adjfreq(struct sx_priv *priv, s64 value)
{
    sx_clock_log_add_s64(&priv->hw_clock.log_adjfreq, value);
    SX_CLOCK_ACTIVITY_LOG(priv, "ADJ_FREQ %lld", value);
}


static bool __dev_iterator_clock_dump(struct sx_dev *dev, void *context)
{
    struct sx_priv                             *priv = sx_priv(dev);
    struct sx_dev_db_iterator_seq_file_context *dec = (struct sx_dev_db_iterator_seq_file_context*)context;

    seq_printf(dec->m, "HW Clock Dump (device #%u)\n", dev->device_id);
    seq_printf(dec->m, "--------------------------\n");

    SX_CLOCK_DEV_SPECIFIC_CB(dev, sx_clock_dump, priv, dec->m, dec->v);

    sx_clock_log_dump(&priv->hw_clock.log_settime, dec->m, "set-time log");
    sx_clock_log_dump(&priv->hw_clock.log_adjfreq, dec->m, "adj-freq log");
    sx_clock_log_dump(&priv->hw_clock.log_adjtime, dec->m, "adj-time log");

    seq_printf(dec->m, "\n\n");
    return true;
}

int sx_dbg_clock_dump_proc_show(struct seq_file *m, void *v)
{
    struct sx_dev_db_iterator_seq_file_context dec = {
        .m = m,
        .v = v
    };

    sx_dev_db_iterate(__dev_iterator_clock_dump, &dec);
    return 0;
}

static bool __dev_iterator_clock_and_ptp_log_dump(struct sx_dev *dev, void *context)
{
    struct sx_priv                             *priv = sx_priv(dev);
    struct sx_dev_db_iterator_seq_file_context *dec = (struct sx_dev_db_iterator_seq_file_context*)context;

    sx_clock_log_dump(&priv->hw_clock.log_activity, dec->m, "HW Clock & PTP log");
    seq_printf(dec->m, "\n\n");

    if (!clock_activity_log) {
        seq_printf(dec->m, "clock_activity_log parameter is turned off! activity log is idle now!\n\n");
    }

    return true;
}

int sx_dbg_clock_and_ptp_log_dump_proc_show(struct seq_file *m, void *v)
{
    struct sx_dev_db_iterator_seq_file_context dec = {
        .m = m,
        .v = v
    };

    sx_dev_db_iterate(__dev_iterator_clock_and_ptp_log_dump, &dec);
    return 0;
}
