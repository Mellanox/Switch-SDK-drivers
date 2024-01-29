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
#include <linux/vmalloc.h>

#include "sx.h"
#include "internal_log.h"
#include "sx_dbg_dump_proc.h"

#define SX_INTERNAL_LOG_ENTRY_MAX_LEN (256)

static const char *__severity_str[] = {
    [SX_INTERNAL_LOG_SEVERITY_CRITICAL_E] = "Critical",
    [SX_INTERNAL_LOG_SEVERITY_ERROR_E] = "Error",
    [SX_INTERNAL_LOG_SEVERITY_WARNING_E] = "Warning",
    [SX_INTERNAL_LOG_SEVERITY_NOTICE_E] = "Notice",
    [SX_INTERNAL_LOG_SEVERITY_INFO_E] = "Info",
    [SX_INTERNAL_LOG_SEVERITY_DEBUG_E] = "Debug"
};

#define NUM_OF_SEVERITY_LEVELS (sizeof(__severity_str) / sizeof(__severity_str[0]))
#define DUMP_NAME_PREFIX       "log___"
#define DUMP_NAME_MAX_LEN      (sizeof(DUMP_NAME_PREFIX) + SX_INTERNAL_LOG_MAX_NAME)

static LIST_HEAD(__log_list);
static DEFINE_MUTEX(__log_lock);
static uint32_t __num_of_logs = 0;

struct sx_internal_log_entry {
    unsigned long                 jiffies;
    enum sx_internal_log_severity severity;
    char                          log[SX_INTERNAL_LOG_ENTRY_MAX_LEN];
};

static const char * __internal_log_severity_to_str(enum sx_internal_log_severity severity)
{
    if ((severity >= 0) && (severity < NUM_OF_SEVERITY_LEVELS)) {
        return __severity_str[severity];
    }

    return NULL;
}

static enum sx_internal_log_severity __internal_log_str_to_severity(const char *str)
{
    int severity;

    for (severity = 0; severity < NUM_OF_SEVERITY_LEVELS; severity++) {
        if (strcasecmp(str, __severity_str[severity]) == 0) {
            return (enum sx_internal_log_severity)severity;
        }
    }

    return SX_INTERNAL_LOG_SEVERITY_INVALID_E;
}

static struct sx_internal_log * __find_log(const char *name)
{
    struct sx_internal_log *iter = NULL;

    list_for_each_entry(iter, &__log_list, list) {
        if (strcmp(iter->name, name) == 0) {
            return iter;
        }
    }

    return NULL;
}

static void __get_proc_dump_name(struct sx_internal_log *ilog, char *name)
{
    sprintf(name, "%s%s", DUMP_NAME_PREFIX, ilog->name);
}

static int __internal_log_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_internal_log       *ilog = (struct sx_internal_log*)context;
    struct sx_internal_log_entry *log_entry;
    struct sx_timeval             now;
    u32                           count, idx;
    char                          time_str[32];

    sx_dbg_get_time(&now);

    seq_printf(m, "INTERNAL LOG: %s\n", ilog->name);
    seq_printf(m, "(minimum severity: %s, current size: %u, max size: %u)\n",
               __internal_log_severity_to_str(ilog->min_severity),
               ilog->curr_num_of_entries,
               ilog->max_entries);

    seq_printf(m, "----------------------------------------------------------------------------------------------\n");

    spin_lock_bh(&ilog->lock);

    idx = (ilog->curr_num_of_entries == ilog->max_entries) ? ilog->next : 0;
    count = ilog->curr_num_of_entries;

    while (count--) {
        log_entry = &ilog->cyc_buff[idx];

        sx_dbg_jiffies_to_time_str(&now, log_entry->jiffies, time_str, sizeof(time_str));
        seq_printf(m, "%llu    %s    %-8s    %s\n",
                   ilog->running_counter - count,
                   time_str,
                   __internal_log_severity_to_str(log_entry->severity),
                   log_entry->log);

        if (++idx == ilog->max_entries) {
            idx = 0;
        }
    }

    spin_unlock_bh(&ilog->lock);

    seq_printf(m, "\n\n");
    return 0;
}

static int __internal_log_cmd(int argc, const char *argv[], void *context)
{
    struct sx_internal_log *ilog = NULL;
    const char             *log_name = NULL;
    const char             *severity_name = NULL;
    int                     err = 0, severity;

    /* USAGE:
     * log-cmd clear <log-name>
     * log-cmd set-min-severity <log-name> <severity>
     */

    if (argc < 3) {
        err = -EINVAL;
        goto out;
    }

    log_name = argv[2];

    mutex_lock(&__log_lock);

    if ((argc == 3) && (strcmp(argv[1], "clear") == 0)) {
        ilog = __find_log(log_name);
        if (!ilog) {
            err = -ENOENT;
            goto out_unlock;
        }

        spin_lock_bh(&ilog->lock);
        ilog->curr_num_of_entries = 0;
        ilog->next = 0;
        spin_unlock_bh(&ilog->lock);
    } else if ((argc == 4) && (strcmp(argv[1], "set-min-severity") == 0)) {
        severity_name = argv[3];

        ilog = __find_log(log_name);
        if (!ilog) {
            err = -ENOENT;
            goto out_unlock;
        }

        severity = __internal_log_str_to_severity(severity_name);
        if (severity == SX_INTERNAL_LOG_SEVERITY_INVALID_E) {
            err = -EINVAL;
            goto out_unlock;
        }

        spin_lock_bh(&ilog->lock);
        ilog->min_severity = severity;
        spin_unlock_bh(&ilog->lock);
    } else {
        err = -EINVAL;
    }

out_unlock:
    mutex_unlock(&__log_lock);

out:
    return err;
}

int sx_internal_log_init(struct sx_internal_log       *ilog,
                         u32                           max_entries,
                         enum sx_internal_log_severity min_severity,
                         const char                   *fmt,
                         ...)
{
    struct sx_internal_log_entry *cyc_buff = NULL;
    char                          dump_name[DUMP_NAME_MAX_LEN];
    va_list                       args;
    int                           err = 0;

    mutex_lock(&__log_lock);

    if (max_entries == 0) {
        err = -EINVAL;
        goto out;
    }

    cyc_buff = vzalloc(max_entries * sizeof(struct sx_internal_log_entry));
    if (!cyc_buff) {
        err = -ENOMEM;
        goto out;
    }

    memset(ilog, 0, sizeof(*ilog));

    va_start(args, fmt);
    vsnprintf(ilog->name, sizeof(ilog->name), fmt, args);
    va_end(args);

    __get_proc_dump_name(ilog, dump_name);
    err = sx_dbg_dump_read_handler_register(dump_name, __internal_log_dump, NULL, (void*)ilog);
    if (err) {
        printk(KERN_ERR "Internal log: failed to create proc entry '%s'\n", dump_name);
        goto dump_handler_failed;
    }

    if (__num_of_logs == 0) { /* this is the first log */
        err = sx_dbg_dump_write_handler_register("log-cmd",
                                                 "clear <log_name>\n"
                                                 "set-min-severity <log_name> <critical|error|warning|notice|info|debug>",
                                                 "Clean log",
                                                 __internal_log_cmd,
                                                 NULL);
        if (err) {
            printk(KERN_ERR "Internal log: failed to add 'log-cmd' command\n");
            goto cmd_handler_failed;
        }
    }

    ilog->max_entries = max_entries;
    ilog->min_severity = min_severity;
    ilog->cyc_buff = cyc_buff;
    ilog->next = 0;
    ilog->curr_num_of_entries = 0;
    ilog->running_counter = 0;
    spin_lock_init(&ilog->lock);

    list_add_tail(&ilog->list, &__log_list);
    __num_of_logs++;
    goto out;

cmd_handler_failed:
    sx_dbg_dump_read_handler_unregister(dump_name);

dump_handler_failed:
    vfree(cyc_buff);

out:
    mutex_unlock(&__log_lock);
    return err;
}

void sx_internal_log_deinit(struct sx_internal_log *ilog)
{
    char dump_name[DUMP_NAME_MAX_LEN];

    mutex_lock(&__log_lock);
    list_del(&ilog->list);
    __num_of_logs--;

    if (__num_of_logs == 0) { /* this is the last log */
        sx_dbg_dump_write_handler_unregister("log-cmd");
    }

    __get_proc_dump_name(ilog, dump_name);
    sx_dbg_dump_read_handler_unregister(dump_name);

    if (ilog->cyc_buff) {
        vfree(ilog->cyc_buff);
        ilog->cyc_buff = NULL;
    }

    mutex_unlock(&__log_lock);
}

int sx_internal_log_add(struct sx_internal_log *ilog, enum sx_internal_log_severity severity, const char *fmt, ...)
{
    struct sx_internal_log_entry *log_entry;
    va_list                       args;
    int                           ret;

    if (ilog->min_severity < severity) {
        return 0;
    }

    va_start(args, fmt);

    spin_lock_bh(&ilog->lock);
    log_entry = &ilog->cyc_buff[ilog->next];

    log_entry->jiffies = jiffies;
    log_entry->severity = severity;
    ret = vsnprintf(log_entry->log,
                    sizeof(log_entry->log),
                    fmt,
                    args);

    if (ilog->curr_num_of_entries < ilog->max_entries) {
        ilog->curr_num_of_entries++;
    }
    ilog->next++;
    if (ilog->next == ilog->max_entries) {
        ilog->next = 0;
    }

    ilog->running_counter++;
    spin_unlock_bh(&ilog->lock);

    va_end(args);
    return ret;
}

void sx_internal_log_dump(struct sx_internal_log *ilog, struct seq_file *m)
{
    __internal_log_dump(m, NULL, (void*)ilog);
}
