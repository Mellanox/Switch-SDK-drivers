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

#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/cmd.h>

#include "sx.h"
#include "sgmii.h"
#include "alloc.h"
#include "ioctl_internal.h"

long ctrl_cmd_query_fw(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_query_fw query_fw;
    struct sx_dev     *dev;
    int                err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&query_fw, (struct ku_query_fw *)data, sizeof(query_fw));
    if (err) {
        goto out;
    }

    err = sx_QUERY_FW(dev, &query_fw);
    if (err) {
        goto out;
    }

    err = copy_to_user((void*)data, &query_fw, sizeof(query_fw));

out:
    return err;
}


long ctrl_cmd_mad_demux(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_mad_demux mad_demux;
    struct sx_dev      *dev;
    int                 err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&mad_demux, (struct ku_mad_demux*)data, sizeof(mad_demux));
    if (err) {
        goto out;
    }

    err = sx_MAD_DEMUX(dev, mad_demux.dev_id, mad_demux.enable);

out:
    return err;
}


long ctrl_cmd_query_rsrc(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_query_rsrc query_rsrc;
    struct sx_dev       *dev;
    int                  err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&query_rsrc, (struct ku_query_rsrc *)data, sizeof(query_rsrc));
    if (err) {
        goto out;
    }

    err = sx_QUERY_RSRC(dev, &query_rsrc);
    if (err) {
        goto out;
    }

    err = copy_to_user((void*)data, &query_rsrc, sizeof(query_rsrc));

out:
    return err;
}


long ctrl_cmd_query_board_info(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_query_board_info board_info;
    struct sx_dev             *dev;
    int                        err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = sx_QUERY_BOARDINFO(dev, &board_info);
    if (err) {
        goto out;
    }

    err = copy_to_user((void*)data, &board_info, sizeof(board_info));

out:
    return err;
}


long ctrl_cmd_set_device_profile(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_profile            profile;
    struct ku_swid_config       *swid_config_type_arr = &profile.swid0_config_type;
    struct profile_driver_params addition_params;
    u8                           swid;
    struct sx_dev               *dev;
    int                          err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    memset(&addition_params, 0, sizeof(addition_params));
    err = copy_from_user(&profile, (void*)data, sizeof(profile));
    if (err) {
        goto out;
    }

    if (profile.dev_id != DEFAULT_DEVICE_ID) {
        err = __sx_core_dev_specific_cb_get_reference(dev);
        if (err) {
            printk(KERN_ERR PFX "__sx_core_dev_specific_cb_get_reference failed.\n");
            goto out;
        }

        __sx_core_dev_specific_cb_release_reference(dev);

        err = sx_SET_PROFILE(dev, &profile, &addition_params);
        if (err) {
            goto out;
        }
    }

    /*
     * if chip is PCI attached or using SGMII, set the global profile and
     * create ib devices if needed
     */

    if ((is_sgmii_supported() && !dev->dev_profile_set) || sx_dpt_is_dev_pci_attached(profile.dev_id)) {
        sx_glb.profile = profile;

        /*
         * set events for all IB enabled swids if
         * swid is enabled
         * */
        for (swid = 0; swid < NUMBER_OF_SWIDS; swid++) {
            /* if swid isn't enabled skip it */
            if (!sx_bitmap_test(&sx_priv(dev)->swid_bitmap, swid)) {
                continue;
            }

            /* check the swid is IB in device profile */
            if (swid_config_type_arr->type != KU_SWID_TYPE_INFINIBAND) {
                continue;
            }

            err = sx_send_enable_ib_swid_events(dev, swid);
            if (err) {
                spin_lock(&dev->profile_lock);
                dev->dev_profile_set = 0;
                spin_unlock(&dev->profile_lock);
                goto out;
            }
        }

        /* Mark profile set */
        spin_lock(&dev->profile_lock);
        dev->dev_profile_set = 1;
        spin_unlock(&dev->profile_lock);
    }

out:
    return err;
}


long ctrl_cmd_get_device_profile(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_profile profile;
    int               err;
    struct sx_dev    *dev;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = sx_GET_PROFILE(dev, &profile, NULL);
    if (err) {
        goto out;
    }

    err = copy_to_user((void*)data, &profile, sizeof(profile));
    if (err) {
        goto out;
    }

out:
    return err;
}


long ctrl_cmd_set_system_mkey(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_system_m_key system_m_key;
    struct sx_dev         *dev;
    int                    err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&system_m_key, (struct ku_system_m_key *)data, sizeof(system_m_key));
    if (err) {
        goto out;
    }

    err = sx_SET_SYSTEM_M_KEY(dev, &system_m_key);
    if (err) {
        goto out;
    }

    err = copy_to_user((void*)data, &system_m_key, sizeof(system_m_key));

out:
    return err;
}


long ctrl_cmd_get_system_mkey(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_system_m_key system_m_key;
    struct sx_dev         *dev;
    int                    err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&system_m_key, (struct ku_system_m_key *)data, sizeof(system_m_key));
    if (err) {
        goto out;
    }

    err = sx_GET_SYSTEM_M_KEY(dev, &system_m_key);
    if (err) {
        goto out;
    }

    err = copy_to_user((void*)data, &system_m_key, sizeof(system_m_key));

out:
    return err;
}
