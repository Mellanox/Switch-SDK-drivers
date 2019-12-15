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

#include <linux/version.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/if_arp.h>
#include <linux/rtnetlink.h>
#include <linux/netlink.h>
#include <net/netlink.h>

#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/skb_hook.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 13, 0)
#define NETLINK_TAP_SUPPORTED 1
#elif defined(RHEL_RELEASE_CODE) && LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0)
#define NETLINK_TAP_SUPPORTED 1
#else
#define NETLINK_TAP_SUPPORTED 0
#endif

int emad_dump_rx;
MODULE_PARM_DESC(emad_dump_rx, "en/dis RX EMAD netlink notifications");
module_param_named(emad_dump_rx, emad_dump_rx, int, 0444);

int emad_dump_tx;
MODULE_PARM_DESC(emad_dump_tx, "en/dis TX EMAD netlink notifications");
module_param_named(emad_dump_tx, emad_dump_tx, int, 0444);

MODULE_AUTHOR("Dan Akunis");
MODULE_DESCRIPTION("Emad-Dump driver");
MODULE_LICENSE("Dual BSD/GPL");


#if NETLINK_TAP_SUPPORTED

/************************************************
 *  Local variables
 ***********************************************/
static struct sock             *__sx_emad_dump_nl_sk = NULL;
static struct net_device      * __nl_dev = NULL;
static struct netlink_tap       __nl_tap;
static struct workqueue_struct *__work_queue = NULL;

/************************************************
 *  Type definitions
 ***********************************************/
struct sx_emad_dump_nl_msghdr {
    u32 devindex;
    u32 reserved;
};
enum sx_emad_dump_nl_direction {
    SX_EMAD_DUMP_NL_DIRECTION_TX, /* SW --> HW */
    SX_EMAD_DUMP_NL_DIRECTION_RX  /* HW --> SW */
};

enum {
    SX_EMAD_DUMP_NL_ATTR_UNSPEC,
    SX_EMAD_DUMP_NL_ATTR_PAYLOAD,   /* data */
    SX_EMAD_DUMP_NL_ATTR_TYPE,      /* u32 */
    SX_EMAD_DUMP_NL_ATTR_DIRECTION, /* u8 */

    __SX_EMAD_DUMP_NL_ATTR_MAX,
    SX_EMAD_DUMP_NL_ATTR_MAX = __SX_EMAD_DUMP_NL_ATTR_MAX - 1
};

struct skb_to_dump {
    struct work_struct             work;
    struct sk_buff                *skb;
    enum sx_emad_dump_nl_direction direction;
};
static netdev_tx_t __emad_dump_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
    consume_skb(skb);
    return NETDEV_TX_OK;
}


static int __emad_dump_open(struct net_device *dev)
{
    __nl_tap.dev = dev;
    __nl_tap.module = THIS_MODULE;
    return netlink_add_tap(&__nl_tap);
}


static int __emad_dump_stop(struct net_device *dev)
{
    return netlink_remove_tap(&__nl_tap);
}


static const struct net_device_ops __emad_dump_ops = {
    .ndo_open = __emad_dump_open,
    .ndo_stop = __emad_dump_stop,
    .ndo_start_xmit = __emad_dump_start_xmit
};
static void __emad_dump_setup(struct net_device *dev)
{
    dev->type = ARPHRD_NETLINK;
    dev->netdev_ops = &__emad_dump_ops;
    dev->destructor = free_netdev;
    dev->features = NETIF_F_SG | NETIF_F_FRAGLIST;
    dev->flags = IFF_NOARP;
    dev->mtu = 8 * 1024;
}

/************************************************
 * Functions                                    *
 ***********************************************/

static int __nl_hwmsg_notify(const struct sk_buff *skb, enum sx_emad_dump_nl_direction direction)
{
    struct sx_emad_dump_nl_msghdr *hdr;
    struct nlmsghdr               *nlh;
    struct sk_buff                *skb_new;

    skb_new = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
    if (!skb_new) {
        return -ENOMEM;
    }

    nlh = nlmsg_put(skb_new, 0, 0, 0, sizeof(*hdr), 0);
    if (!nlh) {
        goto nla_put_failure;
    }

    hdr = nlmsg_data(nlh);
    hdr->devindex = 0;
    hdr->reserved = 0;

    if (nla_put(skb_new, SX_EMAD_DUMP_NL_ATTR_PAYLOAD, skb->len, skb->data)) {
        goto nla_put_failure;
    }

    if (nla_put_u32(skb_new, SX_EMAD_DUMP_NL_ATTR_TYPE, 0)) {
        goto nla_put_failure;
    }

    if (nla_put_u8(skb_new, SX_EMAD_DUMP_NL_ATTR_DIRECTION, direction)) {
        goto nla_put_failure;
    }

    nlmsg_end(skb_new, nlh);

    nlmsg_notify(__sx_emad_dump_nl_sk, skb_new, 0, SX_NL_GRP_EMAD_DUMP, 0, GFP_ATOMIC);
    return 0;

nla_put_failure:
    nlmsg_free(skb_new);
    return -EMSGSIZE;
}


static void __work_handler(struct work_struct *work)
{
    struct skb_to_dump *skb_to_dump = container_of(work, struct skb_to_dump, work);
    int                 err;

    err = __nl_hwmsg_notify(skb_to_dump->skb, skb_to_dump->direction);
    if (err && net_ratelimit()) {
        printk(KERN_ERR "__work_handler failed (err=%d)\n", err);
    }

    kfree_skb(skb_to_dump->skb);
    kfree(skb_to_dump);
}


static void __queue_skb_to_worker_thread(struct sk_buff *skb, enum sx_emad_dump_nl_direction direction)
{
    struct skb_to_dump *skb_to_dump = kmalloc(sizeof(struct skb_to_dump), GFP_ATOMIC);

    if (!skb_to_dump && net_ratelimit()) {
        printk(KERN_ERR "EMAD_DUMP [direction: %d]: failed to allocate skb to dump\n", direction);
        return;
    }

    skb_to_dump->direction = direction;
    skb_to_dump->skb = skb_clone(skb, GFP_ATOMIC);
    if (!skb_to_dump->skb && net_ratelimit()) {
        printk(KERN_ERR "EMAD_DUMP [direction: %d]: failed on skb_clone()\n", direction);
        kfree(skb_to_dump);
        return;
    }

    INIT_WORK(&skb_to_dump->work, __work_handler);
    queue_work(__work_queue, &skb_to_dump->work);
}


static void __emad_dump_hook_rx(struct sx_dev *sx_dev, struct sk_buff *skb, void *context)
{
    __queue_skb_to_worker_thread(skb, SX_EMAD_DUMP_NL_DIRECTION_RX);
}


static void __emad_dump_hook_tx(struct sx_dev *sx_dev, struct sk_buff *skb, void *context)
{
    __queue_skb_to_worker_thread(skb, SX_EMAD_DUMP_NL_DIRECTION_TX);
}


int __init sx_emad_dump_init(void)
{
    struct netlink_kernel_cfg cfg;
    int                       err, netdev_registered = 0;

    if (!emad_dump_rx && !emad_dump_tx) {
        printk(KERN_ERR "emad-dump is disabled on RX and TX\n");
        return -EINVAL;
    }

    memset(&cfg, 0, sizeof(cfg));
    cfg.groups = SX_NL_GRP_MAX;

    __work_queue = create_singlethread_workqueue("emad_dump_queue");
    if (!__work_queue) {
        printk(KERN_ERR "failed to create work queue for emad_dump\n");
        return -ENOMEM;
    }

    __sx_emad_dump_nl_sk = netlink_kernel_create(&init_net, NETLINK_EMAD_DUMP, &cfg);
    if (!__sx_emad_dump_nl_sk) {
        printk(KERN_ERR "failed to create netlink socket (probably netlink unit/family is in use)\n");
        err = -ENOMEM;
        goto nl_create_failed;
    }

    __nl_dev = alloc_netdev(0, "emad_dump", __emad_dump_setup);
    if (!__nl_dev) {
        printk(KERN_ERR "failed to create netlink monitor device\n");
        err = -ENOMEM;
        goto alloc_netdev_failed;
    }

    rtnl_lock();
    err = register_netdevice(__nl_dev);
    rtnl_unlock();

    if (err) {
        printk(KERN_ERR "failed to register netlink monitor device (err=%d)\n", err);
        goto reg_netdev_failed;
    }

    netdev_registered = 1;

    if (emad_dump_rx) {
        printk(KERN_INFO "start emad-dump on RX\n");

        err = sx_core_skb_hook_rx_register(__emad_dump_hook_rx, NULL);
        if (err) {
            printk(KERN_ERR "failed to register RX emad-dump hook\n");
            goto rx_skb_hook_failed;
        }
    }

    if (emad_dump_tx) {
        printk(KERN_INFO "start emad-dump on TX\n");

        err = sx_core_skb_hook_tx_register(__emad_dump_hook_tx, NULL);
        if (err) {
            printk(KERN_ERR "failed to register TX emad-dump hook\n");
            goto tx_skb_hook_failed;
        }
    }

    return 0;

tx_skb_hook_failed:
    if (emad_dump_rx) {
        sx_core_skb_hook_rx_unregister(__emad_dump_hook_rx);
    }

rx_skb_hook_failed:
    unregister_netdev(__nl_dev);

reg_netdev_failed:
    if (!netdev_registered) { /* we're here because of direct 'goto reg_netdev_failed'. */
        free_netdev(__nl_dev);
    }

alloc_netdev_failed:
    netlink_kernel_release(__sx_emad_dump_nl_sk);

nl_create_failed:
    destroy_workqueue(__work_queue);

    return err;
}


void sx_emad_dump_exit(void)
{
    printk(KERN_ERR "%s", __FUNCTION__);

    if (emad_dump_rx) {
        printk(KERN_INFO "finish emad-dump on RX\n");
        sx_core_skb_hook_rx_unregister(__emad_dump_hook_rx);
    }

    if (emad_dump_tx) {
        printk(KERN_INFO "finish emad-dump on TX\n");
        sx_core_skb_hook_tx_unregister(__emad_dump_hook_tx);
    }

    unregister_netdev(__nl_dev);
    netlink_kernel_release(__sx_emad_dump_nl_sk);
    destroy_workqueue(__work_queue);
}

#else /* NETLINK_TAP_SUPPORTED */

int __init sx_emad_dump_init(void)
{
    printk(KERN_ERR "emad-dump is not supported on this kernel version\n");
    return -EOPNOTSUPP;
}


void sx_emad_dump_exit(void)
{
}

#endif /* NETLINK_TAP_SUPPORTED */

module_init(sx_emad_dump_init);
module_exit(sx_emad_dump_exit);
