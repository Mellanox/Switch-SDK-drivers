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

#include <linux/fs.h>

#include <linux/mlx_sx/kernel_user.h>

#include "sx.h"
#include "sgmii.h"
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

    err = sx_oob_pci_init(); /* detect the SwitchX on PCI */

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

    err = sgmii_default_dev_set(default_dev_cfg.dev_id);
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
