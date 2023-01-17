/*
 * Copyright © 2010-2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */
#include "sx_spice_wrapper.h"

/************************************************
 *  Local variables
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

/************************************************
 * Functions                                    *
 ***********************************************/

bool is_ib_sel_dir_supported(dev_private_data_t *priv_data);

bool is_fom_measurment_dir_supported(dev_private_data_t *priv_data);

bool is_lane_dir_supported(dev_private_data_t *priv_data);

bool is_iterations_dir_supported(dev_private_data_t *priv_data, int idx_value);
