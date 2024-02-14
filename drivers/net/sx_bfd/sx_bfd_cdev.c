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

#include "sx_bfd_cdev.h"

#include <linux/fs.h>
#include <linux/cdev.h>


static struct cdev    cdev;
static parse_cmd_func parse_func;
static bool           g_initialized = false;
static long sx_bfd_ioctl(struct file *fp __attribute__((unused)), unsigned int cmd, unsigned long data)
{
    int err = 0;

    err = parse_func((char*)data, cmd);
    if (err < 0) {
        printk(KERN_ERR "Parsing BFD command %d failed (err:%d).\n", cmd, err);
        goto bail;
    }

bail:
    return err;
}


static const struct file_operations sx_bfd_fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = sx_bfd_ioctl      /* As of Linux kernel 2.6.11 need to use unlocked_ioctl */
};

int sx_bfd_cdev_init(parse_cmd_func func)
{
    int          err = 0;
    static dev_t char_dev;

    if (!g_initialized) {
        pr_debug("Creating char device with major:232 minor:193 \n");

        char_dev = MKDEV(232, 193);
        err = register_chrdev_region(char_dev, 1, "bfdcdev");
        if (err) {
            printk(KERN_INFO "Couldn't register the default device number. "
                   "Trying to allocate one dynamically\n");
            err = alloc_chrdev_region(&char_dev, 193, 1, "bfdcdev");
            if (err) {
                printk(KERN_ERR "Couldn't register device number.");
                goto bail;
            }
        }

        cdev_init(&cdev, &sx_bfd_fops);

        err = cdev_add(&cdev, char_dev, 1);
        if (err) {
            printk(KERN_ERR "Failed to create BFD char device (%d).\n", err);
            goto bail;
        }

        parse_func = func;

        pr_debug("BFD char-device initialized.\n");

        g_initialized = true;
    }

bail:
    return err;
}


void sx_bfd_cdev_deinit(void)
{
    if (g_initialized) {
        cdev_del(&cdev);
        unregister_chrdev_region(cdev.dev, 1);

        pr_debug("BFD char-device deinitialized.\n");

        g_initialized = false;
    }

    return;
}
