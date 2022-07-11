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

#ifndef SX_FW_H
#define SX_FW_H

#include <linux/mlx_sx/device.h>
#include "icm.h"

#define NUM_OF_HCRS 2
#define HCR1        0
#define HCR2        1

struct profile_driver_params {
    u8 cqe_version;
    u8 cqe_time_stamp_type;
};

int sx_SET_PROFILE(struct sx_dev *dev, struct ku_profile *profile, struct profile_driver_params *params);
int sx_GET_PROFILE(struct sx_dev *dev, struct ku_profile *profile, struct profile_driver_params *params_p);
int sx_SET_KVH_CACHE_PARAMS(struct sx_dev             *dev,
                            struct profile_kvh_params *kvh_params);
int sx_GET_KVH_CACHE_PARAMS(struct sx_dev             *dev,
                            struct profile_kvh_params *kvh_params_p);
int sx_QUERY_FW_2(struct sx_dev *dev, int sx_dev_id, bool enforce_hcr1);
int sx_MAP_FA(struct sx_dev *dev, struct sx_icm *icm, sxd_map_memory_type_e type);
int sx_UNMAP_FA(struct sx_dev *dev);

#endif /* SX_FW_H */
