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

#include <linux/skbuff.h>
#include <linux/rwlock_types.h>
#include <linux/mlx_sx/skb_hook.h>

static struct list_head __skb_hook_list_rx;
static struct list_head __skb_hook_list_tx;
static spinlock_t       __skb_hook_lock;
struct sx_skb_hook {
    struct list_head hook_list;
    sx_skb_hook_cb_t hook_cb;
    void            *user_context;
};


void sx_core_skb_hook_init(void)
{
    spin_lock_init(&__skb_hook_lock);
    INIT_LIST_HEAD(&__skb_hook_list_rx);
    INIT_LIST_HEAD(&__skb_hook_list_tx);
}


static int __sx_core_hook_register(sx_skb_hook_cb_t hook_cb, void *user_context, struct list_head *hook_list)
{
    struct sx_skb_hook *hook, *iter;
    unsigned long       flags;
    int                 err = 0;

    if (hook_cb == NULL) {
        return -EINVAL;
    }

    hook = kmalloc(sizeof(struct sx_skb_hook), GFP_KERNEL);
    if (!hook) {
        return -ENOMEM;
    }

    hook->hook_cb = hook_cb;
    hook->user_context = user_context;
    INIT_LIST_HEAD(&hook->hook_list);

    spin_lock_irqsave(&__skb_hook_lock, flags);

    list_for_each_entry(iter, hook_list, hook_list) {
        if (iter->hook_cb == hook_cb) {
            err = -EEXIST;
            break;
        }
    }

    if (err == 0) {
        list_add_tail(&hook->hook_list, hook_list);
    }

    spin_unlock_irqrestore(&__skb_hook_lock, flags);

    if (err) {
        kfree(hook);
    }

    return err;
}


static int __sx_core_hook_unregister(sx_skb_hook_cb_t hook_cb, struct list_head *hook_list)
{
    struct sx_skb_hook *iter;
    unsigned long       flags;
    int                 err = -ENOENT;

    if (hook_cb == NULL) {
        return -EINVAL;
    }

    spin_lock_irqsave(&__skb_hook_lock, flags);

    list_for_each_entry(iter, hook_list, hook_list) {
        if (iter->hook_cb == hook_cb) {
            err = 0;
            break;
        }
    }

    if (err == 0) {
        list_del(&iter->hook_list);
    }

    spin_unlock_irqrestore(&__skb_hook_lock, flags);

    if (err == 0) {
        kfree(iter);
    }

    return err;
}


static void __sx_core_skb_hook_call(struct sx_dev *sx_dev, struct sk_buff *skb, const struct list_head *hook_list)
{
    struct sx_skb_hook *iter;
    unsigned long       flags;

    spin_lock_irqsave(&__skb_hook_lock, flags);

    list_for_each_entry(iter, hook_list, hook_list) {
        iter->hook_cb(sx_dev, skb, iter->user_context);
    }

    spin_unlock_irqrestore(&__skb_hook_lock, flags);
}


int sx_core_skb_hook_rx_register(sx_skb_hook_cb_t hook_cb, void *user_context)
{
    return __sx_core_hook_register(hook_cb, user_context, &__skb_hook_list_rx);
}
EXPORT_SYMBOL(sx_core_skb_hook_rx_register);


int sx_core_skb_hook_rx_unregister(sx_skb_hook_cb_t hook_cb)
{
    return __sx_core_hook_unregister(hook_cb, &__skb_hook_list_rx);
}
EXPORT_SYMBOL(sx_core_skb_hook_rx_unregister);


void sx_core_skb_hook_rx_call(struct sx_dev *sx_dev, struct sk_buff *skb)
{
    __sx_core_skb_hook_call(sx_dev, skb, &__skb_hook_list_rx);
}


int sx_core_skb_hook_tx_register(sx_skb_hook_cb_t hook_cb, void *user_context)
{
    return __sx_core_hook_register(hook_cb, user_context, &__skb_hook_list_tx);
}
EXPORT_SYMBOL(sx_core_skb_hook_tx_register);


int sx_core_skb_hook_tx_unregister(sx_skb_hook_cb_t hook_cb)
{
    return __sx_core_hook_unregister(hook_cb, &__skb_hook_list_tx);
}
EXPORT_SYMBOL(sx_core_skb_hook_tx_unregister);


void sx_core_skb_hook_tx_call(struct sx_dev *sx_dev, struct sk_buff *skb)
{
    __sx_core_skb_hook_call(sx_dev, skb, &__skb_hook_list_tx);
}
