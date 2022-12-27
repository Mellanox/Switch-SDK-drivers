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

#ifndef SX_NETDEV_MODULE_SYSFS_S3IP_H
#define SX_NETDEV_MODULE_SYSFS_S3IP_H

/*
 *  create extended S3IP sysfs kobjects under <parent> kobject, with the tree like:
 *   ../<parent>/power_on
 *   ../<parent>/tx_disable
 *   ../<parent>/present
 *   ../<parent>/rx_los
 */
int sx_netdev_create_module_sysfs_extension_for_s3ip(struct kobject *parent, bool module_support_enable);

/*
 *  remove those extended S3IP sysfs kobjects under <parent> kobject:
 *   ../<parent>/power_on
 *   ../<parent>/tx_disable
 *   ../<parent>/present
 *   ../<parent>/rx_los
 */
void sx_netdev_delete_module_sysfs_extension_for_s3ip(struct kobject *parent, bool module_support_enable);

#endif /* SX_NETDEV_MODULE_SYSFS_S3IP_H */
