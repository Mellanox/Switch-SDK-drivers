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
        printk(KERN_ERR "Parsing BFD command failed (%d).\n", err);
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
        printk(KERN_DEBUG "Creating char device with major:232 minor:193 \n");

        char_dev = MKDEV(232, 193); /* TODO - defined? enum? */
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
        cdev.owner = THIS_MODULE; /* TODO - is needed? already defined above */

        err = cdev_add(&cdev, char_dev, 1);
        if (err) {
            printk(KERN_ERR "Failed to create BFD char device (%d).\n", err);
            goto bail;
        }

        parse_func = func;

        printk(KERN_DEBUG "BFD char-device initialized.\n");

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

        printk(KERN_DEBUG "BFD char-device deinitialized.\n");

        g_initialized = false;
    }

    return;
}
