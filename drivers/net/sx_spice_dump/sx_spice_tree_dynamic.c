/*
 * Copyright © 2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include "sx_spice_tree_dynamic.h"

/************************************************
 *  Local variables
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

/************************************************
 * Functions                                    *
 ***********************************************/

int is_ib_sel_dir_supported(dev_private_data_t *priv_data, bool *is_supported)
{
    int      err = 0;
    uint16_t dev_id = 0;

    err = sx_spice_system_type_get(priv_data, &dev_id);
    if (err) {
        printk(KERN_ERR "SPICE: Failed to get system type\n");
        goto out;
    }

    /* IB select index is valid only for 16nm systems */
    switch (dev_id) {
    case SXD_MGIR_HW_DEV_ID_QUANTUM:
    case SXD_MGIR_HW_DEV_ID_SPECTRUM2:
    case SXD_MGIR_HW_DEV_ID_SPECTRUM3:
        *is_supported = true;
        break;

    case SXD_MGIR_HW_DEV_ID_QUANTUM2:
    case SXD_MGIR_HW_DEV_ID_SPECTRUM4:

    default:
        *is_supported = false;
        break;
    }

out:
    return err;
}

int is_fom_measurment_dir_supported(dev_private_data_t *priv_data, bool *is_supported)
{
    int      err = 0;
    uint16_t dev_id = 0;

    err = sx_spice_system_type_get(priv_data, &dev_id);
    if (err) {
        printk(KERN_ERR "SPICE: Failed to get system type\n");
        goto out;
    }

    /* fom_measurment OP is valid only for 7nm systems */
    switch (dev_id) {
    case SXD_MGIR_HW_DEV_ID_QUANTUM2:
    case SXD_MGIR_HW_DEV_ID_SPECTRUM4:
        *is_supported = true;
        break;

    case SXD_MGIR_HW_DEV_ID_QUANTUM:
    case SXD_MGIR_HW_DEV_ID_SPECTRUM2:
    case SXD_MGIR_HW_DEV_ID_SPECTRUM3:

    default:
        *is_supported = false;
        break;
    }

out:
    return err;
}

int is_iterations_dir_supported(dev_private_data_t *priv_data, int test_mode, bool *is_supported)
{
    int err = 0;

    *is_supported = false;

    if (test_mode == 1) {
        *is_supported = true;
    }

    return err;
}
