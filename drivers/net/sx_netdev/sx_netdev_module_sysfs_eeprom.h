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

#ifndef SX_NETDEV_MODULE_SYSFS_EEPROM_H
#define SX_NETDEV_MODULE_SYSFS_EEPROM_H

/*
 *  create an eeprom sysfs kobject tree under <parent> kobject, with the tree like:
 *   ../<parent>/eeprom/pages/0/i2c-0x50/data
 *   ../<parent>/eeprom/pages/0/i2c-0x51/data
 *   ../<parent>/eeprom/pages/<N = 1..255>/data
 */
int sx_netdev_create_module_sysfs_eeprom_tree(struct kobject *parent, struct module_sysfs_eeprom_tree *root);

/*
 *  remove an eeprom sysfs kobject tree, with the tree like:
 *   ./eeprom/pages/0/i2c-0x50/data
 *   ./eeprom/pages/0/i2c-0x51/data
 *   ./eeprom/pages/<N = 1..255>/data
 */
void sx_netdev_delete_module_sysfs_eeprom_tree(struct module_sysfs_eeprom_tree *root);

#endif /* SX_NETDEV_MODULE_SYSFS_EEPROM_H */
