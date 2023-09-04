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

#include <linux/fs.h>

#include <linux/mlx_sx/kernel_user.h>

#include "sx.h"
#include "sgmii.h"
#include "dev_init.h"
#include "ioctl_internal.h"

long ctrl_cmd_set_sgmii_system_cfg(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_sgmii_system_cfg sgmii_system_cfg;
    int                        err;

    err = copy_from_user(&sgmii_system_cfg, (void*)data, sizeof(sgmii_system_cfg));
    if (err) {
        goto out;
    }

    err = sgmii_set_system_cfg(&sgmii_system_cfg);
    if (err) {
        goto out;
    }

    err = sx_dev_init_oob_pci(); /* detect the SwitchX on PCI */

out:
    return err;
}


long ctrl_cmd_init_sgmii_dev(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_sgmii_init_dev sgmii_init_dev;
    int                      err;

    err = copy_from_user(&sgmii_init_dev, (void*)data, sizeof(sgmii_init_dev));
    if (err) {
        goto out;
    }

    err = sgmii_dev_init(sgmii_init_dev.dev_id, sgmii_init_dev.init_hopf);

out:
    return err;
}


long ctrl_cmd_set_sgmii_default_dev(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_sgmii_default_dev default_dev_cfg;
    int                         err;

    err = copy_from_user(&default_dev_cfg, (void*)data, sizeof(default_dev_cfg));
    if (err) {
        goto out;
    }

    err = sgmii_default_dev_set(default_dev_cfg.dev_id,
                                default_dev_cfg.hopf_on_remote_mgmt ? true : false);
    if (err) {
        printk(KERN_ERR "failed to set SGMII default device (err=%d)\n", err);
    }

out:
    return err;
}


long ctrl_cmd_set_sgmii_mft_info(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_sgmii_mft_info mft_info;
    int                      err;

    err = copy_from_user(&mft_info, (void*)data, sizeof(mft_info));
    if (err) {
        goto out;
    }

    err = sgmii_dev_set_mft_info(&mft_info);
    if (err) {
        printk(KERN_ERR "failed to set SGMII MFT info (err=%d)\n", err);
    }

out:
    return err;
}
