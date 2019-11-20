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

#include "sx_bfd_engine_data.h"
#include "sx_bfd_engine_ctrl.h"

static int __init sx_bfd_init(void)
{
    int err = 0;

    err = sx_bfd_engine_ctrl_init();
    if (err < 0) {
        printk(KERN_ERR "Kernel BFD engine control failed to initialize.\n");
        goto bail;
    }

    err = sx_bfd_engine_data_init();
    if (err < 0) {
        printk(KERN_ERR "Kernel BFD engine data failed to initialize.\n");
        goto bail;
    }

    printk(KERN_DEBUG "Kernel BFD initialized\n");

bail:
    return err;
}

static void __exit sx_bfd_deinit(void)
{
    printk(KERN_DEBUG "Kernel BFD start deinit \n");

    sx_bfd_engine_ctrl_deinit();

    sx_bfd_engine_data_deinit();

    printk(KERN_DEBUG "Kernel BFD deinitialized\n");
}

module_init(sx_bfd_init);
module_exit(sx_bfd_deinit);

MODULE_AUTHOR("Alla Segal, Dan Akunis");
MODULE_DESCRIPTION("Mellanox Switch BFD driver");
MODULE_LICENSE("Dual BSD/GPL");
