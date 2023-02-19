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

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/kernel_user.h>
#include "sx.h"
#include "dev_db.h"
#include "alloc.h"
#include "mmap.h"
#include "ber_monitor.h"
#include "sx_dbg_dump_proc.h"
#include "bulk_cntr_db.h"
#include "sx_af_counters.h"
#include "health_check.h"

/************************************************
 *  MACROS
 ***********************************************/

#define SEQ_FILE_SIZE     (64 * 1024)
#define DBG_DUMP_CMD_NAME "dbg_cmd"

/************************************************
 *  LOCAL VARIABLES
 ***********************************************/
struct proc_dir_entry        *__root_dir = NULL;
static struct proc_dir_entry *__sx_command_entry = NULL;
static u8                     sx_dbg_dump_proc_registered = 0;
static struct mutex           __proc_list_lock;
static LIST_HEAD(__read_proc_list);
static LIST_HEAD(__write_proc_list);

struct read_handler_info {
    struct list_head           list;
    sx_dbg_dump_proc_show_cb_t show_cb;
    sx_dbg_dump_proc_size_cb_t size_cb;
    void                      *context;
    char                      *name;
};

struct write_handler_info {
    struct list_head          list;
    sx_dbg_dump_proc_cmd_cb_t cmd_cb;
    char                     *cmd;
    char                     *usage;
    char                     *description;
    void                     *context;
};

void sx_dbg_dump_print_header(struct seq_file *m, const char* header)
{
    seq_printf(m,
               "\n========================================================================================================================\n");
    seq_printf(m, "%s", header);
    seq_printf(m,
               "\n========================================================================================================================\n\n");
}
EXPORT_SYMBOL(sx_dbg_dump_print_header);

static struct read_handler_info * __name_to_info(const char *name)
{
    struct read_handler_info *iter;

    if (!name) {
        return NULL;
    }

    list_for_each_entry(iter, &__read_proc_list, list) {
        if (strcmp(name, iter->name) == 0) {
            return iter;
        }
    }

    return NULL;
}

static struct write_handler_info * __cmd_to_info(const char *cmd)
{
    struct write_handler_info *iter;

    if (!cmd) {
        return NULL;
    }

    list_for_each_entry(iter, &__write_proc_list, list) {
        if (strcmp(cmd, iter->cmd) == 0) {
            return iter;
        }
    }

    return NULL;
}

/* ******************************************************************************* */
/* PROC DUMP INFRA FUNCTIONS                                                       */
/* ******************************************************************************* */

static int __sx_db_dump_proc_show(struct seq_file* m, void* v)
{
    struct read_handler_info *info = (struct read_handler_info*)m->private;

    seq_printf(m, "******************** DEBUG PROC FILE: %s ********************\n\n", info->name);
    return info->show_cb(m, v, info->context);
}

static int __sx_dbg_dump_proc_open(struct inode *inode, struct file *file)
{
    const char              * name = (const char*)PDE_DATA(inode);
    struct read_handler_info *iter = NULL;
    int                       ret = 0;

    mutex_lock(&__proc_list_lock);
    iter = __name_to_info(name);

    if (iter) {
        ret = single_open_size(file, __sx_db_dump_proc_show, iter, iter->size_cb ? iter->size_cb() : SEQ_FILE_SIZE);
    } else {
        printk(KERN_ERR "could not find proc file '%s' information\n", name);
        ret = -ENOENT;
    }
    mutex_unlock(&__proc_list_lock);

    return ret;
}

int sx_dbg_dump_read_handler_register(const char                *name,
                                      sx_dbg_dump_proc_show_cb_t show_cb,
                                      sx_dbg_dump_proc_size_cb_t size_cb,
                                      void                      *context)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    static const struct proc_ops __sx_dbg_dump_proc_handler = {
        .proc_open = __sx_dbg_dump_proc_open,
        .proc_read = seq_read,
        .proc_lseek = seq_lseek,
        .proc_release = single_release
    };
#else
    static const struct file_operations __sx_dbg_dump_proc_handler = {
        .owner = THIS_MODULE,
        .open = __sx_dbg_dump_proc_open,
        .read = seq_read,
        .llseek = seq_lseek,
        .release = single_release
    };
#endif

    struct proc_dir_entry    *pde;
    struct read_handler_info *read_handler_info = NULL;
    int                       err;

    if (!name || !show_cb) {
        printk(KERN_ERR "proc file name is empty or no show handler\n");
        return -EINVAL;
    }

    mutex_lock(&__proc_list_lock);

    if (__name_to_info(name)) {
        printk(KERN_ERR "proc file %s already exists\n", name);
        err = -EEXIST;
        goto error;
    }

    err = -ENOMEM;

    read_handler_info = kzalloc(sizeof(struct read_handler_info), GFP_KERNEL);
    if (read_handler_info == NULL) {
        printk(KERN_WARNING "create info for proc %s failed\n", name);
        goto error;
    }

    read_handler_info->name = kstrdup(name, GFP_KERNEL);
    if (read_handler_info->name == NULL) {
        printk(KERN_WARNING "allocate name of info for proc %s failed\n", name);
        goto error;
    }

    pde = proc_create_data(name,
                           S_IFREG | S_IRUGO,
                           __root_dir,
                           &__sx_dbg_dump_proc_handler,
                           (void*)read_handler_info->name);
    if (pde == NULL) {
        printk(KERN_WARNING "create proc %s failed\n", name);
        goto error;
    }

    INIT_LIST_HEAD(&read_handler_info->list);
    read_handler_info->show_cb = show_cb;
    read_handler_info->size_cb = size_cb;
    read_handler_info->context = context;

    list_add(&read_handler_info->list, &__read_proc_list);
    err = 0;

out:
    mutex_unlock(&__proc_list_lock);
    return err;

error:
    if (read_handler_info) {
        if (read_handler_info->name) {
            kfree(read_handler_info->name);
        }

        kfree(read_handler_info);
    }

    goto out;
}
EXPORT_SYMBOL(sx_dbg_dump_read_handler_register);

static void __sx_dbg_dump_read_handler_unregister(struct read_handler_info *read_handler_info)
{
    list_del(&read_handler_info->list);
    remove_proc_entry(read_handler_info->name, __root_dir);
    kfree(read_handler_info->name);
    kfree(read_handler_info);
}


void sx_dbg_dump_read_handler_unregister(const char *name)
{
    struct read_handler_info *read_handler_info;

    mutex_lock(&__proc_list_lock);

    read_handler_info = __name_to_info(name);
    if (read_handler_info == NULL) {
        printk(KERN_ERR "proc file %s does not exist\n", name);
    } else {
        __sx_dbg_dump_read_handler_unregister(read_handler_info);
    }

    mutex_unlock(&__proc_list_lock);
}
EXPORT_SYMBOL(sx_dbg_dump_read_handler_unregister);

int sx_dbg_dump_write_handler_register(const char               *cmd,
                                       const char               *usage,
                                       const char               *description,
                                       sx_dbg_dump_proc_cmd_cb_t cmd_cb,
                                       void                     *context)
{
    struct write_handler_info *write_handler_info = NULL;
    int                        err;

    if (!cmd || !usage || !description || !cmd_cb) {
        printk(KERN_ERR "write handler invalid arguments\n");
        return -EINVAL;
    }

    mutex_lock(&__proc_list_lock);

    if (__cmd_to_info(cmd)) {
        printk(KERN_ERR "command handler '%s' already exists\n", cmd);
        err = -EEXIST;
        goto error;
    }

    err = -ENOMEM;

    write_handler_info = kzalloc(sizeof(struct write_handler_info), GFP_KERNEL);
    if (write_handler_info == NULL) {
        printk(KERN_WARNING "create cmd proc '%s' failed\n", cmd);
        goto error;
    }

    write_handler_info->cmd = kstrdup(cmd, GFP_KERNEL);
    if (write_handler_info->cmd == NULL) {
        printk(KERN_WARNING "allocate command of info for proc %s failed\n", cmd);
        goto error;
    }

    write_handler_info->usage = kstrdup(usage, GFP_KERNEL);
    if (write_handler_info->usage == NULL) {
        printk(KERN_WARNING "allocate usage of info for proc %s failed\n", cmd);
        goto error;
    }

    write_handler_info->description = kstrdup(description, GFP_KERNEL);
    if (write_handler_info->description == NULL) {
        printk(KERN_WARNING "allocate description of info for proc %s failed\n", cmd);
        goto error;
    }

    INIT_LIST_HEAD(&write_handler_info->list);
    write_handler_info->cmd_cb = cmd_cb;
    write_handler_info->context = context;

    list_add(&write_handler_info->list, &__write_proc_list);
    err = 0;

out:
    mutex_unlock(&__proc_list_lock);
    return err;

error:
    if (write_handler_info) {
        if (write_handler_info->cmd) {
            kfree(write_handler_info->cmd);
        }

        if (write_handler_info->usage) {
            kfree(write_handler_info->usage);
        }

        if (write_handler_info->description) {
            kfree(write_handler_info->description);
        }

        kfree(write_handler_info);
    }

    goto out;
}
EXPORT_SYMBOL(sx_dbg_dump_write_handler_register);

static void __sx_dbg_dump_write_handler_unregister(struct write_handler_info *write_handler_info)
{
    list_del(&write_handler_info->list);
    kfree(write_handler_info->cmd);
    kfree(write_handler_info->usage);
    kfree(write_handler_info->description);
    kfree(write_handler_info);
}


void sx_dbg_dump_write_handler_unregister(const char *cmd)
{
    struct write_handler_info *write_handler_info;

    mutex_lock(&__proc_list_lock);

    write_handler_info = __cmd_to_info(cmd);
    if (write_handler_info == NULL) {
        printk(KERN_ERR "cmd handler '%s' does not exist\n", cmd);
    } else {
        __sx_dbg_dump_write_handler_unregister(write_handler_info);
    }

    mutex_unlock(&__proc_list_lock);
}
EXPORT_SYMBOL(sx_dbg_dump_write_handler_unregister);

static ssize_t __sx_dbg_dump_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
#define SX_WRITE_PROC_MAX_ARGS (10)

    char                       buff[1024] = { 0 };
    const char                *argv[SX_WRITE_PROC_MAX_ARGS] = { 0 };
    char                      *token = buff, *tmp = buff;
    size_t                     buff_len = sizeof(buff) - 1;
    int                        argc = 0, rc = 0;
    struct write_handler_info *info = NULL;

    if (count < buff_len) {
        buff_len = count;
    }

    if (copy_from_user(buff, buffer, buff_len) != 0) {
        return -EFAULT;
    }

    while (tmp && argc < SX_WRITE_PROC_MAX_ARGS) {
        token = strsep(&tmp, " ");
        argv[argc++] = strim(token);
    }

    if (tmp) {
        printk(KERN_ERR "too many arguments for a single command!\n");
        goto out;
    }

    mutex_lock(&__proc_list_lock);
    info = __cmd_to_info(argv[0]);
    if (info) {
        rc = info->cmd_cb(argc, argv, info->context);
        if (rc) {
            printk(KERN_ERR "command '%s' failed (err=%d)\n", argv[0], rc);
        }
    } else {
        printk(KERN_ERR "unknown command '%s'\n", argv[0]);
    }
    mutex_unlock(&__proc_list_lock);

out:
    return count;
}


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
static const struct proc_ops __sx_command_proc_handler = {
    .proc_write = __sx_dbg_dump_write
};
#else
static const struct file_operations __sx_command_proc_handler = {
    .write = __sx_dbg_dump_write
};
#endif

static int __help_dump(struct seq_file *m, void *v, void *context)
{
    struct write_handler_info *iter_w, *tmp_w;
    char                      *usage = NULL, *next = NULL;

    sx_dbg_dump_print_header(m, "Commands list");

    mutex_lock(&__proc_list_lock);

    seq_printf(m, "*** All commands should be written to /proc/dbg_dump/dbg_cmd ***\n\n");

    sx_dbg_dump_print_separate_line(m);
    list_for_each_entry_safe(iter_w, tmp_w, &__write_proc_list, list) {
        seq_printf(m, "Command: %s\n", iter_w->cmd);
        seq_printf(m, "Description: %s\n", iter_w->description);
        seq_printf(m, "Usage:\n");
        usage = iter_w->usage;
        next = iter_w->usage;
        do {
            usage = strsep(&next, "\n");
            seq_printf(m, "    %s %s\n", iter_w->cmd, usage);
            if (next) {
                next[-1] = '\n';
            }
        } while (next);
        sx_dbg_dump_print_separate_line(m);
    }

    mutex_unlock(&__proc_list_lock);
    return 0;
}

int __init sx_dbg_dump_proc_fs_init(void)
{
    const char *proc_dir_name = SX_DBG_DUMP_PROC_DIR;

    sx_dbg_dump_proc_registered = 0;
    if (sx_dbg_dump_proc_registered) {
        return -EEXIST;
    }

    mutex_init(&__proc_list_lock);

    /* Create dbg dump proc directory */
    __root_dir = proc_mkdir(proc_dir_name, NULL);
    if (__root_dir == NULL) {
        printk(KERN_WARNING "create proc dir %s failed\n", proc_dir_name);
        return -ENOMEM;
    }

    sx_dbg_dump_read_handler_register(DBG_DUMP_CMD_NAME "_help", __help_dump, NULL, NULL);
    __sx_command_entry = proc_create(DBG_DUMP_CMD_NAME,
                                     S_IFREG | S_IWUSR,
                                     __root_dir,
                                     &__sx_command_proc_handler);

    sx_dbg_dump_proc_registered = 1;
    return 0;
}

void sx_dbg_dump_proc_fs_deinit(void)
{
    struct read_handler_info  *iter_r, *tmp_r;
    struct write_handler_info *iter_w, *tmp_w;

    if (sx_dbg_dump_proc_registered == 0) {
        return;
    }

    mutex_lock(&__proc_list_lock);

    list_for_each_entry_safe(iter_r, tmp_r, &__read_proc_list, list) {
        __sx_dbg_dump_read_handler_unregister(iter_r);
    }

    list_for_each_entry_safe(iter_w, tmp_w, &__write_proc_list, list) {
        __sx_dbg_dump_write_handler_unregister(iter_w);
    }

    mutex_unlock(&__proc_list_lock);

    remove_proc_entry(DBG_DUMP_CMD_NAME, __root_dir);

    /* Remove dbg dump proc directory */
    remove_proc_entry(SX_DBG_DUMP_PROC_DIR, NULL);
    sx_dbg_dump_proc_registered = 0;
}
