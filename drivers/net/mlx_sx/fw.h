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

#ifndef SX_FW_H
#define SX_FW_H

#include <linux/mlx_sx/device.h>
#include "icm.h"

struct profile_driver_params {
    u8 cqe_version;
    u8 cqe_time_stamp_type;
};

int sx_SET_PROFILE(struct sx_dev *dev, struct ku_profile *profile, struct profile_driver_params *params);
int sx_GET_PROFILE(struct sx_dev *dev, struct ku_profile *profile, struct profile_driver_params *params_p);
int sx_QUERY_FW_2(struct sx_dev *dev, int sx_dev_id);
int sx_MAP_FA(struct sx_dev *dev, struct sx_icm *icm);
int sx_UNMAP_FA(struct sx_dev *dev);

#endif /* SX_FW_H */
