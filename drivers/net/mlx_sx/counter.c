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

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/rwlock_types.h>

#include "sx_dbg_dump_proc.h"
#include "counter.h"

/* this lock is used with spin_lock_irqsave/spin_unlock_irqrestore because IB drivers do some operations
 * with the sx_core driver (that may involve counter registration) under their spin_lock with interrupts disabled.
 * We must align with this lock method even although this is ugly ...
 */
static spinlock_t __sx_core_counter_lock;

static LIST_HEAD(sx_core_counter_category_list);
static size_t __seq_file_size = 4 * 1024; /* initial size */

typedef void (*counter_iterator_cb)(struct sx_core_counter *counter, void *context);
typedef int (*counter_dump_filter_cb)(const struct sx_core_counter *counter, u64 since_startup);

struct dump_counters_context {
    struct seq_file                 *m;
    void                            *v;
    counter_dump_filter_cb           filter_cb;
    struct sx_core_counter_category *last_category;
};
static const char * severity_to_str(enum sx_core_counter_severity severity)
{
    static const char *sev_to_str[] = {
        [COUNTER_SEV_NONE] = "",
        [COUNTER_SEV_INFO] = "[Inf]",
        [COUNTER_SEV_NOTICE] = "[Ntc]",
        [COUNTER_SEV_ERROR] = "[Err]"
    };

    if (severity >= sizeof(sev_to_str) / sizeof(sev_to_str[0])) {
        severity = COUNTER_SEV_NONE;
    }

    return sev_to_str[severity];
}


static u8 __category_exists(const struct sx_core_counter_category *counter_category)
{
    const struct sx_core_counter_category *iter;

    list_for_each_entry(iter, &sx_core_counter_category_list, list_categories) {
        if (strcmp(iter->name, counter_category->name) == 0) {
            return 1;
        }
    }

    return 0;
}


static u8 __counter_exists(const struct sx_core_counter_category *counter_category,
                           const struct sx_core_counter          *counter)
{
    const struct sx_core_counter *iter_counter;

    list_for_each_entry(iter_counter, &counter_category->list_counters, list_counters) {
        if (strcmp(iter_counter->name, counter->name) == 0) {
            return 1;
        }
    }

    return 0;
}


static int __sx_core_counter_category_register(struct sx_core_counter_category *counter_category)
{
    unsigned long flags;
    int           ret = 0;

    spin_lock_irqsave(&__sx_core_counter_lock, flags);
    if (__category_exists(counter_category)) {
        printk(KERN_ERR "counter category %s already exists\n", counter_category->name);
        ret = -EEXIST;
    } else {
        list_add_tail(&counter_category->list_categories, &sx_core_counter_category_list);
    }

    spin_unlock_irqrestore(&__sx_core_counter_lock, flags);
    return ret;
}


int sx_core_counter_category_init(struct sx_core_counter_category* counter_category, const char* name)
{
    if (!counter_category || !name || (strlen(name) > MAX_COUNTER_CATEGORY_NAME_LEN)) {
        printk(KERN_ERR "failed to init counter category [%s] - invalid parameter\n",
               (name ? name : "<NULL>"));
        return -EINVAL;
    }

    INIT_LIST_HEAD(&counter_category->list_categories);
    INIT_LIST_HEAD(&counter_category->list_counters);
    strcpy(counter_category->name, name);
    counter_category->num_of_counters = 0;
    return __sx_core_counter_category_register(counter_category);
}

EXPORT_SYMBOL(sx_core_counter_category_init);


int sx_core_counter_category_deinit(struct sx_core_counter_category *counter_category)
{
    unsigned long flags;
    int           ret = 0;

    if (!counter_category) {
        printk(KERN_ERR "NULL counter category\n");
        return -EINVAL;
    }

    spin_lock_irqsave(&__sx_core_counter_lock, flags);
    if (counter_category->num_of_counters > 0) {
        printk(KERN_ERR "failed to deinit counter category %s - category not empty\n",
               counter_category->name);
        ret = -ENOTEMPTY;
    } else {
        list_del(&counter_category->list_categories);
    }

    spin_unlock_irqrestore(&__sx_core_counter_lock, flags);
    return ret;
}

EXPORT_SYMBOL(sx_core_counter_category_deinit);


static int __sx_core_counter_register(struct sx_core_counter_category *counter_category,
                                      struct sx_core_counter         * counter)
{
    unsigned long flags;
    int           ret = 0;

    spin_lock_irqsave(&__sx_core_counter_lock, flags);
    if (!__category_exists(counter_category)) {
        printk(KERN_ERR "failed to register counter %s - category %s does not exist\n",
               counter->name, counter_category->name);
        ret = -ENOENT;
        goto done;
    }

    if (__counter_exists(counter_category, counter)) {
        printk(KERN_ERR "failed to register counter %s - already exists in category %s\n",
               counter->name, counter_category->name);
        ret = -EEXIST;
        goto done;
    }

    counter->counter_category = counter_category;
    list_add_tail(&counter->list_counters, &counter_category->list_counters);
    counter_category->num_of_counters++;
    __seq_file_size += 200; /* for each counter add 200 bytes to the seq_file size */

done:

    spin_unlock_irqrestore(&__sx_core_counter_lock, flags);
    return ret;
}


int sx_core_counter_init(struct sx_core_counter_category *counter_category,
                         struct sx_core_counter          *counter,
                         const char                      *name,
                         enum sx_core_counter_severity    severity)
{
    if (!counter_category || !counter || !name || (strlen(name) > MAX_COUNTER_NAME_LEN)) {
        printk(KERN_ERR "failed to init counter [%s] - invalid argument\n",
               (name ? name : "<NULL>"));
        return -EINVAL;
    }

    INIT_LIST_HEAD(&counter->list_counters);
    strcpy(counter->name, name);
    counter->severity = severity;
    counter->last_time = 0;
    counter->clear_count = 0;
    counter->show_count = 0;
    atomic64_set(&counter->since_startup, 0);

    return __sx_core_counter_register(counter_category, counter);
}

EXPORT_SYMBOL(sx_core_counter_init);
static void __sx_core_counter_unregister(struct sx_core_counter *counter)
{
    unsigned long flags;

    spin_lock_irqsave(&__sx_core_counter_lock, flags);

    list_del(&counter->list_counters);
    counter->counter_category->num_of_counters--;
    counter->counter_category = NULL;
    __seq_file_size -= 200;  /* for each counter subtract 200 bytes from the seq_file size */

    spin_unlock_irqrestore(&__sx_core_counter_lock, flags);
}


int sx_core_counter_deinit(struct sx_core_counter *counter)
{
    if (!counter) {
        printk(KERN_ERR "failed to deinit counter - invalid argument\n");
        return -EINVAL;
    }

    __sx_core_counter_unregister(counter);
    return 0;
}

EXPORT_SYMBOL(sx_core_counter_deinit);


void sx_core_counter_increment(struct sx_core_counter* counter)
{
    atomic64_inc(&counter->since_startup);
    counter->last_time = jiffies;
}

EXPORT_SYMBOL(sx_core_counter_increment);


static void __msecs_to_human_time(unsigned long j, char* human_time, u32 humen_time_size)
{
    unsigned long msecs = jiffies_to_msecs(j);
    u16           _msecs;
    u8            _secs;
    u8            _mins;
    u8            _hours;
    u16           _days;

#define MSEC_IN_SEC  (1000U)
#define MSEC_IN_MIN  (60000U)
#define MSEC_IN_HOUR (3600000U)
#define MSEC_IN_DAY  (86400000U)

    _days = msecs / MSEC_IN_DAY;
    msecs -= _days * MSEC_IN_DAY;

    _hours = msecs / MSEC_IN_HOUR;
    msecs -= _hours * MSEC_IN_HOUR;

    _mins = msecs / MSEC_IN_MIN;
    msecs -= _mins * MSEC_IN_MIN;

    _secs = msecs / MSEC_IN_SEC;
    msecs -= _secs * MSEC_IN_SEC;

    _msecs = (u16)msecs;

    snprintf(human_time, humen_time_size, "%uD %02u:%02u:%02u.%03u",
             _days, _hours, _mins, _secs, _msecs);
}


static void __iterate_counters(counter_iterator_cb iter_cb, void *context)
{
    struct sx_core_counter_category *counter_category;
    struct sx_core_counter          *counter;

    spin_lock_bh(&__sx_core_counter_lock);

    list_for_each_entry(counter_category, &sx_core_counter_category_list, list_categories) {
        list_for_each_entry(counter, &counter_category->list_counters, list_counters) {
            iter_cb(counter, context);
        }
    }

    spin_unlock_bh(&__sx_core_counter_lock);
}


static void __dump_one_counter(struct sx_core_counter *counter, void *context)
{
    struct dump_counters_context *dmp_ctx = (struct dump_counters_context*)context;
    u8                            print_category_name = (counter->counter_category != dmp_ctx->last_category);
    char                          str_last_time[20] = "";
    u64                           since_startup = atomic64_read(&counter->since_startup);

    if (dmp_ctx->filter_cb && dmp_ctx->filter_cb(counter, since_startup)) {
        return;
    }

    if (counter->last_time > 0) {
        __msecs_to_human_time(jiffies - counter->last_time, str_last_time, sizeof(str_last_time));
    }

    seq_printf(dmp_ctx->m,
               "%-36s %-8s %-48s %-20s %-20llu %-20llu %-20llu\n",
               (print_category_name ? counter->counter_category->name : ""),
               severity_to_str(counter->severity),
               counter->name,
               str_last_time,
               since_startup,
               since_startup - counter->clear_count,
               since_startup - counter->show_count);

    counter->show_count = since_startup;
    dmp_ctx->last_category = counter->counter_category;
}


static void __dump_counters(struct seq_file *m, void *v, counter_dump_filter_cb filter_cb)
{
    struct dump_counters_context context = {
        .m = m,
        .v = v,
        .filter_cb = filter_cb,
        .last_category = NULL
    };

    seq_printf(m,
               "%-36s %-8s %-48s %-20s %-20s %-20s %-20s\n",
               "Category", "Severity", "Name", "Last-Time", "Since-Startup", "Since-Clear", "Since-Show");
    seq_printf(m,
               "==================================== "
               "======== "
               "================================================ "
               "==================== "
               "==================== "
               "==================== "
               "====================\n");

    __iterate_counters(__dump_one_counter, &context);
}


static int proc_counters(struct seq_file *m, void *v)
{
    __dump_counters(m, v, NULL);
    return 0;
}


static int __filter_active_since_startup(const struct sx_core_counter *counter, u64 since_startup)
{
    return (since_startup == 0);
}


static int proc_counters_active_since_startup(struct seq_file *m, void *v)
{
    __dump_counters(m, v, __filter_active_since_startup);
    return 0;
}


static int __filter_active_since_clear(const struct sx_core_counter *counter, u64 since_startup)
{
    return (since_startup == counter->clear_count);
}


static int proc_counters_active_active_since_clear(struct seq_file *m, void *v)
{
    __dump_counters(m, v, __filter_active_since_clear);
    return 0;
}


static int __filter_active_since_show(const struct sx_core_counter *counter, u64 since_startup)
{
    return (since_startup == counter->show_count);
}


static int proc_counters_active_since_show(struct seq_file *m, void *v)
{
    __dump_counters(m, v, __filter_active_since_show);
    return 0;
}


static void __clear_counter_cb(struct sx_core_counter *counter, void *context)
{
    counter->clear_count = atomic64_read(&counter->since_startup);
}


static int proc_clear_counters(struct seq_file *m, void *v)
{
    __iterate_counters(__clear_counter_cb, NULL);
    return 0;
}


static size_t __counters_seq_file_size(void)
{
    return __seq_file_size;
}


int __init sx_core_counters_init(void)
{
    sx_dbg_dump_proc_fs_register("counters",
                                 proc_counters,
                                 __counters_seq_file_size);
    sx_dbg_dump_proc_fs_register("counters_active_since_startup",
                                 proc_counters_active_since_startup,
                                 __counters_seq_file_size);
    sx_dbg_dump_proc_fs_register("counters_active_since_clear",
                                 proc_counters_active_active_since_clear,
                                 __counters_seq_file_size);
    sx_dbg_dump_proc_fs_register("counters_active_since_show",
                                 proc_counters_active_since_show,
                                 __counters_seq_file_size);
    sx_dbg_dump_proc_fs_register("clear_counters", proc_clear_counters, NULL);

    spin_lock_init(&__sx_core_counter_lock);
    return 0;
}


void sx_core_counters_deinit(void)
{
    sx_dbg_dump_proc_fs_unregister("counters");
    sx_dbg_dump_proc_fs_unregister("counters_active_since_startup");
    sx_dbg_dump_proc_fs_unregister("counters_active_since_clear");
    sx_dbg_dump_proc_fs_unregister("counters_active_since_show");
    sx_dbg_dump_proc_fs_unregister("clear_counters");
}
