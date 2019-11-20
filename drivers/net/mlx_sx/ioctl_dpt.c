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
#include "ioctl_internal.h"

long ctrl_cmd_add_dev_path(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_dpt_path_add dpt_path_add_data;
    struct sx_dev         *dev;
    int                    err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&dpt_path_add_data, (void*)data, sizeof(dpt_path_add_data));
    if (err) {
        goto out;
    }

    err = sx_dpt_add_dev_path(dpt_path_add_data.dev_id,
                              dpt_path_add_data.path_type,
                              dpt_path_add_data.path_info,
                              dpt_path_add_data.is_local);

out:
    return err;
}


long ctrl_cmd_remove_dev_path(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_dpt_path_add dpt_path_add_data;
    struct sx_dev         *dev;
    int                    err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&dpt_path_add_data, (void*)data, sizeof(dpt_path_add_data));
    if (err) {
        goto out;
    }

    err = sx_dpt_remove_dev_path(dpt_path_add_data.dev_id, dpt_path_add_data.path_type);

out:
    return err;
}


long ctrl_cmd_remove_dev(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_dpt_path_add dpt_path_add_data;
    struct sx_dev         *dev;
    int                    err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&dpt_path_add_data, (void*)data, sizeof(dpt_path_add_data));
    if (err) {
        goto out;
    }

    err = sx_dpt_remove_dev(dpt_path_add_data.dev_id, 0);

out:
    return err;
}


long ctrl_cmd_set_cmd_path(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_dpt_path_modify dpt_path_modify_data;
    struct sx_dev            *dev;
    int                       err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&dpt_path_modify_data, (void*)data, sizeof(dpt_path_modify_data));
    if (err) {
        goto out;
    }

    err = sx_dpt_set_cmd_path(dpt_path_modify_data.dev_id, dpt_path_modify_data.path_type);

out:
    return err;
}


long ctrl_cmd_set_mad_path(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_dpt_path_modify dpt_path_modify_data;
    struct sx_dev            *dev;
    int                       err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&dpt_path_modify_data, (void*)data, sizeof(dpt_path_modify_data));
    if (err) {
        goto out;
    }

    err = sx_dpt_set_mad_path(dpt_path_modify_data.dev_id, dpt_path_modify_data.path_type);

out:
    return err;
}


long ctrl_cmd_set_emad_path(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_dpt_path_modify dpt_path_modify_data;
    struct sx_dev            *dev;
    int                       err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&dpt_path_modify_data, (void*)data, sizeof(dpt_path_modify_data));
    if (err) {
        goto out;
    }

    err = sx_dpt_set_emad_path(dpt_path_modify_data.dev_id, dpt_path_modify_data.path_type);

out:
    return err;
}


long ctrl_cmd_set_cr_access_path(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_dpt_path_modify dpt_path_modify_data;
    struct sx_dev            *dev;
    int                       err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&dpt_path_modify_data, (void*)data, sizeof(dpt_path_modify_data));
    if (err) {
        goto out;
    }

    err = sx_dpt_set_cr_access_path(dpt_path_modify_data.dev_id, dpt_path_modify_data.path_type);

out:
    return err;
}


long ctrl_cmd_cr_space_read(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_cr_space_read read_data;
    unsigned char          *buf = NULL;
    int                     err;

    err = copy_from_user(&read_data, (void*)data, sizeof(read_data));
    if (err) {
        goto out;
    }

    buf = kmalloc(read_data.size, GFP_KERNEL);
    if (!buf) {
        err = -ENOMEM;
        goto out;
    }

    err = sx_dpt_cr_space_read(read_data.dev_id, read_data.address, buf, read_data.size);
    if (err) {
        goto out_kfree;
    }

    err = copy_to_user(read_data.data, buf, read_data.size);

out_kfree:
    kfree(buf);

out:
    return err;
}


long ctrl_cmd_cr_space_write(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_cr_space_write write_data;
    unsigned char           *buf = NULL;
    int                      err;

    err = copy_from_user(&write_data, (void*)data, sizeof(write_data));
    if (err) {
        goto out;
    }

    buf = kmalloc(write_data.size, GFP_KERNEL);
    if (!buf) {
        err = -ENOMEM;
        goto out;
    }

    err = copy_from_user(buf, write_data.data, write_data.size);
    if (err) {
        goto out_kfree;
    }

    err = sx_dpt_cr_space_write(write_data.dev_id, write_data.address, buf, write_data.size);

out_kfree:
    kfree(buf);

out:
    return err;
}
