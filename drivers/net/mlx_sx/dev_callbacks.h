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

#ifndef __SX_DEV_CALLBACKS_H__
#define __SX_DEV_CALLBACKS_H__

int sx_core_dev_init_switchx_cb(struct sx_dev      *dev,
                                enum sxd_chip_types chip_type,
                                bool                force);

int sx_core_dev_deinit_switchx_cb(struct sx_dev *dev);

#endif /* __SX_DEV_CALLBACKS_H__ */
