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
MODULE_DESCRIPTION("NVIDIA Switch BFD driver");
MODULE_LICENSE("Dual BSD/GPL");
