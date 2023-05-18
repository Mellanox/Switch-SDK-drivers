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

#ifndef SX_NETDEV_SYNCE_H
#define SX_NETDEV_SYNCE_H

#include <linux/netdevice.h>
#include <linux/kobject.h>

int sx_netdev_synce_sysfs_init(struct kobject *netdev);
void sx_netdev_synce_sysfs_deinit(struct kobject *netdev);


#endif /* SX_NETDEV_SYNCE_H */
