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

#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/cmd.h>

#include "sx.h"
#include "sgmii.h"
#include "alloc.h"
#include "ioctl_internal.h"
#include "health_check.h"


long ctrl_cmd_query_fw(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_query_fw query_fw;
    struct sx_dev     *dev;
    int                err;

    err = copy_from_user(&query_fw, (struct ku_query_fw *)data, sizeof(query_fw));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(query_fw.dev_id);
    if (!dev) {
        return -ENODEV;
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

    err = copy_from_user(&mad_demux, (struct ku_mad_demux*)data, sizeof(mad_demux));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(mad_demux.dev_id);
    if (!dev) {
        return -ENODEV;
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

    err = copy_from_user(&query_rsrc, (struct ku_query_rsrc *)data, sizeof(query_rsrc));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(query_rsrc.dev_id);
    if (!dev) {
        return -ENODEV;
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
    int                        err = 0;

    err = copy_from_user(&board_info, (struct ku_query_board_info *)data, sizeof(board_info));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(board_info.dev_id);
    if (!dev) {
        return -ENODEV;
    }

    err = sx_QUERY_BOARDINFO(dev, &board_info);
    if (err) {
        goto out;
    }

    err = copy_to_user((void*)data, &board_info, sizeof(board_info));

out:
    return err;
}

long ctrl_cmd_memory_to_cpu_map(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev       *dev;
    int                  err = 0;
    struct ku_map_memory map_memory;

    dev = sx_core_ioctl_get_dev(DEFAULT_DEVICE_ID);
    if (!dev) {
        return -ENODEV;
    }

    if (sx_priv(dev)->fw.pp_icm != NULL) {
        printk(KERN_INFO PFX "pp_icm is NOT null.\n");
        sx_free_icm(dev, sx_priv(dev)->fw.pp_icm, 0);
        sx_priv(dev)->fw.pp_icm = NULL;
    }

    memset(&map_memory, 0, sizeof(map_memory));
    err = copy_from_user(&map_memory, (void*)data, sizeof(map_memory));
    if (err) {
        goto out;
    }

    sx_priv(dev)->fw.pp_icm = sx_alloc_icm(dev, map_memory.mem_size, GFP_HIGHUSER | __GFP_NOWARN, 0);
    if (sx_priv(dev)->fw.pp_icm == NULL) {
        sx_err(dev, "Couldn't allocate Port Profile memory area, aborting.\n");
        err = -ENOMEM;
        goto out;
    }

    err = sx_MAP_FA(dev, sx_priv(dev)->fw.pp_icm, map_memory.mem_type);
    if (err != 0) {
        sx_err(dev, "MAP_FA command failed, aborting.\n");
        sx_free_icm(dev, sx_priv(dev)->fw.pp_icm, 0);
        goto out;
    }
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
    struct sx_priv              *priv;
    int                          err;

    memset(&addition_params, 0, sizeof(addition_params));
    err = copy_from_user(&profile, (void*)data, sizeof(profile));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(profile.dev_id);
    if (!dev) {
        return -ENODEV;
    }

    priv = sx_priv(dev);

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

    if ((is_sgmii_supported() && !priv->profile.dev_profile_set) || sx_dpt_is_dev_pci_attached(profile.dev_id)) {
        priv->profile.dev_profile = profile;

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
                spin_lock(&priv->profile.profile_lock);
                priv->profile.dev_profile_set = false;
                spin_unlock(&priv->profile.profile_lock);
                goto out;
            }
        }

        /* Mark profile set */
        spin_lock(&priv->profile.profile_lock);
        priv->profile.dev_profile_set = true;
        spin_unlock(&priv->profile.profile_lock);
    }

out:
    return err;
}


long ctrl_cmd_get_device_profile(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_profile profile;
    int               err;
    struct sx_dev    *dev;

    err = copy_from_user(&profile, (void*)data, sizeof(profile));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(profile.dev_id);
    if (!dev) {
        return -ENODEV;
    }

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

long ctrl_cmd_set_kvh_cache_params(struct file *file, unsigned int cmd, unsigned long data)
{
    struct profile_kvh_params kvh_params;
    struct sx_dev            *dev;
    int                       err;

    err = copy_from_user(&kvh_params, (void*)data, sizeof(kvh_params));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(DEFAULT_DEVICE_ID);
    if (!dev) {
        return -ENODEV;
    }

    if (dev->device_id != DEFAULT_DEVICE_ID) {
        err = sx_SET_KVH_CACHE_PARAMS(dev, &kvh_params);
        if (err) {
            goto out;
        }
    }

out:
    return err;
}

long ctrl_cmd_get_kvh_cache_params(struct file *file, unsigned int cmd, unsigned long data)
{
    struct profile_kvh_params kvh_params;
    int                       err;
    struct sx_dev            *dev;

    dev = sx_core_ioctl_get_dev(DEFAULT_DEVICE_ID);
    if (!dev) {
        return -ENODEV;
    }

    err = sx_GET_KVH_CACHE_PARAMS(dev, &kvh_params);
    if (err) {
        goto out;
    }

    err = copy_to_user((void*)data, &kvh_params, sizeof(kvh_params));
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

    err = copy_from_user(&system_m_key, (struct ku_system_m_key *)data, sizeof(system_m_key));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(system_m_key.dev_id);
    if (!dev) {
        return -ENODEV;
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

    err = copy_from_user(&system_m_key, (struct ku_system_m_key *)data, sizeof(system_m_key));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(system_m_key.dev_id);
    if (!dev) {
        return -ENODEV;
    }

    err = sx_GET_SYSTEM_M_KEY(dev, &system_m_key);
    if (err) {
        goto out;
    }

    err = copy_to_user((void*)data, &system_m_key, sizeof(system_m_key));

out:
    return err;
}

long ctrl_cmd_send_fatal_failure_detect_info_set(struct file *file, unsigned int cmd, unsigned long data)
{
    ku_dbg_health_check_params_t params;
    struct sx_dev               *dev = NULL;
    int                          err = 0;

    err = copy_from_user(&params, (struct ku_dbg_health_check_params_t *)data, sizeof(params));
    if (err) {
        goto out;
    }

    dev = sx_core_ioctl_get_dev(params.dev_id);
    if (!dev) {
        return -ENODEV;
    }

    err = sx_health_check_configure(&params);

out:
    return err;
}
