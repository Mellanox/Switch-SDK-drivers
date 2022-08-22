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

#include <linux/workqueue.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/bitops.h>
#include <linux/errno.h>
#include <linux/ethtool.h>
#include <linux/etherdevice.h>
#include <linux/string.h>
#include <linux/spinlock.h>
#include <linux/netdevice.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/tcp.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <net/ip.h>
#include <net/addrconf.h>
#include <linux/vmalloc.h>
#include <linux/if_ether.h>
#include <linux/if_vlan.h>
#include <linux/rtnetlink.h>
#include <linux/version.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/kernel_user.h>

#include "sx_netdev.h"


#define EEPROM_PAGE0_SIZE      (256)
#define EEPROM_UPPER_PAGE_SIZE (128)

static ssize_t __module_sysfs_eeprom_bin_read(struct file          *flip,
                                              struct kobject       *kobj,
                                              struct bin_attribute *attr,
                                              char                 *buf,
                                              loff_t                pos,
                                              size_t                count);
static ssize_t __module_sysfs_eeprom_bin_write(struct file          *flip,
                                               struct kobject       *kobj,
                                               struct bin_attribute *attr,
                                               char                 *buf,
                                               loff_t                pos,
                                               size_t                count);

extern int                  single_netdev_per_port_enable;
static struct bin_attribute module_eeprom_page0_attribute = __BIN_ATTR(data,
                                                                       (S_IRUGO | S_IWUSR),
                                                                       __module_sysfs_eeprom_bin_read,
                                                                       __module_sysfs_eeprom_bin_write,
                                                                       EEPROM_PAGE0_SIZE);
static struct bin_attribute module_eeprom_pagex_attribute = __BIN_ATTR(data,
                                                                       (S_IRUGO | S_IWUSR),
                                                                       __module_sysfs_eeprom_bin_read,
                                                                       __module_sysfs_eeprom_bin_write,
                                                                       EEPROM_UPPER_PAGE_SIZE);

static int __create_module_sysfs_eeprom_page0(struct kobject *parent, struct eeprom_page0_node *node)
{
    int err = 0, i;

    node->page = kobject_create_and_add("0", parent);
    if (!(node->page)) {
        err = -ENOMEM;
        goto out;
    }
    node->i2c[0] = kobject_create_and_add("i2c-0x50", node->page);
    if (!(node->page)) {
        err = -ENOMEM;
        goto phase1_err;
    }
    node->i2c[1] = kobject_create_and_add("i2c-0x51", node->page);
    if (!(node->page)) {
        err = -ENOMEM;
        goto phase2_err;
    }

    for (i = 0; i < MODULE_EEPROM_I2C_ADDR_NUM; i++) {
        err = sysfs_create_bin_file(node->i2c[i], &module_eeprom_page0_attribute);
        if (err) {
            goto phase3_err;
        }
    }

    return err;

phase3_err:
    for (; i > 0; i--) {
        sysfs_remove_bin_file(node->i2c[i - 1], &module_eeprom_page0_attribute);
    }
    kobject_put(node->i2c[1]);
phase2_err:
    kobject_put(node->i2c[0]);
phase1_err:
    kobject_put(node->page);
out:
    return err;
}

static void __delete_module_sysfs_eeprom_page0(struct eeprom_page0_node *node)
{
    int i;

    for (i = 0; i < MODULE_EEPROM_I2C_ADDR_NUM; i++) {
        sysfs_remove_bin_file(node->i2c[i], &module_eeprom_page0_attribute);
        kobject_put(node->i2c[i]);
    }
    kobject_put(node->page);
}

static int __create_module_sysfs_eeprom_pagex(struct kobject *parent, struct eeprom_pagex_node *node, int page_id)
{
    int  err = 0;
    char num_str[8];

    snprintf(num_str, sizeof(num_str), "%d", page_id);
    node->page = kobject_create_and_add(num_str, parent);
    if (!(node->page)) {
        err = -ENOMEM;
        goto out;
    }

    err = sysfs_create_bin_file(node->page, &module_eeprom_pagex_attribute);
    if (err) {
        goto phase1_err;
    }

    return err;

phase1_err:
    kobject_put(node->page);
out:
    return err;
}

static void __delete_module_sysfs_eeprom_pagex(struct eeprom_pagex_node *node)
{
    sysfs_remove_bin_file(node->page, &module_eeprom_pagex_attribute);
    kobject_put(node->page);
}

int sx_netdev_create_module_sysfs_eeprom_tree(struct kobject *parent, struct module_sysfs_eeprom_tree *root)
{
    int err = 0, i;

    root->eeprom = kobject_create_and_add("eeprom", parent);
    if (!(root->eeprom)) {
        err = -ENOMEM;
        goto out;
    }
    root->pages = kobject_create_and_add("pages", root->eeprom);
    if (!(root->pages)) {
        err = -ENOMEM;
        goto phase1_err;
    }

    err = __create_module_sysfs_eeprom_page0(root->pages, &(root->page0));
    if (err < 0) {
        goto phase2_err;
    }

    for (i = 0; i < MODULE_EEPROM_UPPER_PAGE_NUM; i++) {
        err = __create_module_sysfs_eeprom_pagex(root->pages, &(root->page[i]), i + 1);
        if (err < 0) {
            goto phase3_err;
        }
    }
    return err;

phase3_err:
    for (; i > 0; i--) {
        __delete_module_sysfs_eeprom_pagex(&(root->page[i - 1]));
    }
    __delete_module_sysfs_eeprom_page0(&(root->page0));
phase2_err:
    kobject_put(root->pages);
phase1_err:
    kobject_put(root->eeprom);
out:
    return err;
}

void sx_netdev_delete_module_sysfs_eeprom_tree(struct module_sysfs_eeprom_tree *root)
{
    int i;

    for (i = 0; i < MODULE_EEPROM_UPPER_PAGE_NUM; i++) {
        __delete_module_sysfs_eeprom_pagex(&(root->page[i]));
    }
    __delete_module_sysfs_eeprom_page0(&(root->page0));
    kobject_put(root->pages);
    kobject_put(root->eeprom);
}

static int __sx_netdev_get_net_device_by_eeprom_kobj(struct kobject *kobj, struct net_device **dev)
{
    int                 ret = 0;
    u8                  i = 0;
    u8                  j = 0;
    u32                 port = 0;
    struct net_device  *netdev = NULL;
    struct sx_net_priv *priv = NULL;
    int                 num_netdevs = single_netdev_per_port_enable ? 1 : MAX_PORT_NETDEV_NUM;

    if (!kobj) {
        printk(KERN_ERR PFX "sysfs node is NULL\n");
        ret = -EINVAL;
        goto out;
    }

    for (port = 0; port < MAX_SYSPORT_NUM; port++) {
        for (i = 0; i < num_netdevs; i++) {
            netdev = g_netdev_resources->port_netdev[PORT_TYPE_SINGLE][port][i];
            if (netdev != NULL) {
                priv = netdev_priv(netdev);
                for (j = 0; j < MODULE_EEPROM_I2C_ADDR_NUM; j++) {
                    if (kobj == priv->eeprom_kobjs->page0.i2c[j]) {
                        *dev = netdev;
                        goto out;
                    }
                }
                for (j = 0; j < MODULE_EEPROM_UPPER_PAGE_NUM; j++) {
                    if (kobj == priv->eeprom_kobjs->page[j].page) {
                        *dev = netdev;
                        goto out;
                    }
                }
            }
        }
    }

    printk(KERN_DEBUG PFX "The net device is not existed for the kobj\n");
    ret = -ENOENT;

out:
    return ret;
}

static ssize_t __module_sysfs_eeprom_bin_read(struct file          *flip,
                                              struct kobject       *kobj,
                                              struct bin_attribute *attr,
                                              char                 *buf,
                                              loff_t                pos,
                                              size_t                count)
{
    int                 ret = 0;
    int                 read_count = 0;
    struct net_device  *netdev = NULL;
    struct sx_net_priv *net_priv = NULL;

    if (pos > attr->size) {
        return 0;
    }
    if (pos + count > attr->size) {
        count = attr->size - pos;
    }
    if (count == 0) {
        return 0;
    }

    ret = __sx_netdev_get_net_device_by_eeprom_kobj(kobj, &netdev);
    if (ret) {
        printk(KERN_ERR "Failed to get the net device of the kobj, ret: %d\n", ret);
        goto out;
    }

    net_priv = netdev_priv(netdev);
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_module_sysfs_eeprom_access,
                               read_count,
                               net_priv->dev,
                               kobject_name(kobj),
                               net_priv->port,
                               MODULE_SYSFS_EEPROM_READ,
                               buf,
                               pos,
                               count);
    if (read_count < 0) {
        printk(KERN_ERR "Fails to read eeprom, status: %d.\n", read_count);
        ret = read_count;
        goto out;
    }

    return read_count;

out:
    return ret;
}

static ssize_t __module_sysfs_eeprom_bin_write(struct file          *flip,
                                               struct kobject       *kobj,
                                               struct bin_attribute *attr,
                                               char                 *buf,
                                               loff_t                pos,
                                               size_t                count)
{
    int                 ret = 0;
    int                 write_count = 0;
    struct net_device  *netdev = NULL;
    struct sx_net_priv *net_priv = NULL;

    if (pos > attr->size) {
        return 0;
    }
    if (pos + count > attr->size) {
        count = attr->size - pos;
    }
    if (count == 0) {
        return 0;
    }

    ret = __sx_netdev_get_net_device_by_eeprom_kobj(kobj, &netdev);
    if (ret) {
        printk(KERN_ERR "Failed to get the net device of the kobj, ret: %d\n", ret);
        goto out;
    }

    net_priv = netdev_priv(netdev);
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_module_sysfs_eeprom_access,
                               write_count,
                               net_priv->dev,
                               kobject_name(kobj),
                               net_priv->port,
                               MODULE_SYSFS_EEPROM_WRITE,
                               buf,
                               pos,
                               count);
    if (write_count < 0) {
        printk(KERN_ERR "Fails to read eeprom, status: %d.\n", write_count);
        ret = write_count;
        goto out;
    }

    return write_count;

out:
    return ret;
}
