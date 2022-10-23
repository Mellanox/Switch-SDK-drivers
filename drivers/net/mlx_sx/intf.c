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

#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/device.h>
#include "sx.h"
#include "sgmii.h"
#include "alloc.h"
#include "health_check.h"

struct sx_device_context {
    struct list_head     list;
    struct sx_interface *intf;
    void                *context;
};

static LIST_HEAD(intf_list);
static LIST_HEAD(dev_list);
static DEFINE_MUTEX(intf_mutex);

static void sx_core_add_device(struct sx_interface *intf, struct sx_priv *priv)
{
    struct sx_device_context *dev_ctx;
    union sx_event_data      *event_data, *rpa_init_event_data;
    int                       i;
    unsigned long             flags;
    u8                        ib_swid_present = 0;

    dev_ctx = kmalloc(sizeof *dev_ctx, GFP_KERNEL);
    if (!dev_ctx) {
        return;
    }

    event_data = kmalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        kfree(dev_ctx);
        return;
    }

    rpa_init_event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!rpa_init_event_data) {
        kfree(dev_ctx);
        kfree(event_data);
        return;
    }

    dev_ctx->intf = intf;
    dev_ctx->context = intf->add(&priv->dev);

    if (dev_ctx->context) {
        for (i = 0; i < NUMBER_OF_SWIDS; i++) {
            memset(event_data, 0, sizeof(*event_data));
            if (sx_bitmap_test(&priv->swid_bitmap, i)) {
                if (priv->profile.pci_profile.swid_type[i] ==
                    SX_KU_L2_TYPE_IB) {
                    ib_swid_present = 1;
                    printk(KERN_DEBUG PFX "sx_core_add_device: "
                           "dispatching IB swid up event\n");
                    event_data->ib_swid_change.swid = i;
                    event_data->ib_swid_change.dev_id = 1;
                    dev_ctx->intf->event(&priv->dev,
                                         dev_ctx->context,
                                         SX_DEV_EVENT_IB_SWID_UP, event_data);
                    if (priv->profile.pci_profile.ipoib_router_port_enable[i]) {
                        rpa_init_event_data->rpa_init.swid[rpa_init_event_data->rpa_init.num_of_ib_swids++] = i;
                    }
                } else if (priv->profile.pci_profile.swid_type[i] ==
                           SX_KU_L2_TYPE_ETH) {
                    printk(KERN_DEBUG PFX "sx_core_add_device: "
                           "dispatching ETH swid up event\n");
                    event_data->eth_swid_up.swid = i;
                    event_data->eth_swid_up.synd = priv->swid_data[i].eth_swid_data.synd;
                    event_data->eth_swid_up.mac = priv->swid_data[i].eth_swid_data.mac;
                    dev_ctx->intf->event(&priv->dev, dev_ctx->context,
                                         SX_DEV_EVENT_ETH_SWID_UP, event_data); /* TODO: send the right trap id and mac */
                }
            }
        }

        if (ib_swid_present) {
            if (rpa_init_event_data->rpa_init.num_of_ib_swids != 0) {
                rpa_init_event_data->rpa_init.max_pkey =
                    priv->profile.pci_profile.max_pkey;
                dev_ctx->intf->event(&priv->dev,
                                     dev_ctx->context,
                                     SX_DEV_EVENT_TYPE_RPA_INIT,
                                     rpa_init_event_data);
            }
        }

        spin_lock_irqsave(&priv->ctx_lock, flags);
        list_add_tail(&dev_ctx->list, &priv->ctx_list);
        spin_unlock_irqrestore(&priv->ctx_lock, flags);
    } else {
        kfree(dev_ctx);
    }

    kfree(rpa_init_event_data);
    kfree(event_data);
}

static void sx_core_remove_device(struct sx_interface *intf, struct sx_priv *priv)
{
    struct sx_device_context *dev_ctx, *tmp;
    unsigned long             flags;

    list_for_each_entry_safe(dev_ctx, tmp, &priv->ctx_list, list) {
        if (dev_ctx->intf == intf) {
            spin_lock_irqsave(&priv->ctx_lock, flags);
            list_del(&dev_ctx->list);
            spin_unlock_irqrestore(&priv->ctx_lock, flags);

            intf->remove(&priv->dev, dev_ctx->context);
            kfree(dev_ctx);
            return;
        }
    }
}

int sx_register_interface(struct sx_interface *intf)
{
    struct sx_priv *priv;

    if (!intf->add || !intf->remove) {
        return -EINVAL;
    }

    mutex_lock(&intf_mutex);
    list_add_tail(&intf->list, &intf_list);
    list_for_each_entry(priv, &dev_list, dev_list) {
        sx_core_add_device(intf, priv);
    }

    mutex_unlock(&intf_mutex);

    return 0;
}
EXPORT_SYMBOL(sx_register_interface);

void sx_unregister_interface(struct sx_interface *intf)
{
    struct sx_priv *priv;

    mutex_lock(&intf_mutex);
    list_for_each_entry(priv, &dev_list, dev_list) {
        sx_core_remove_device(intf, priv);
    }

    list_del(&intf->list);

    mutex_unlock(&intf_mutex);
}
EXPORT_SYMBOL(sx_unregister_interface);

int sx_core_dispatch_event(struct sx_dev *dev, enum sx_dev_event type, union sx_event_data *event_data)
{
    struct sx_priv           *priv = sx_priv(dev);
    struct sx_device_context *dev_ctx, *tmp;
    int                       err, err_ret = 0;

    /* We can't hold a spinlock when dispatching a swid up/down event
     *  because sx_ib will not be able to register the
     * IB device on PPC. We might have to solve this in the
     * future for scalability. */
    spin_lock(&priv->ctx_lock);
    list_for_each_entry_safe(dev_ctx, tmp, &priv->ctx_list, list) {
        if (dev_ctx->intf->event) {
            pr_debug(PFX "sx_core_dispatch_event: "
                     "dispatching the event\n");
            spin_unlock(&priv->ctx_lock);
            mutex_lock(&intf_mutex);
            err = dev_ctx->intf->event(dev, dev_ctx->context, type, event_data);
            if (err && (err_ret == 0)) {
                err_ret = err;
            }
            mutex_unlock(&intf_mutex);
            spin_lock(&priv->ctx_lock);
        }
    }

    spin_unlock(&priv->ctx_lock);
    return err_ret;
}

int sx_core_register_device(struct sx_dev *dev)
{
    struct sx_priv      *priv = sx_priv(dev);
    struct sx_interface *intf;

    mutex_lock(&intf_mutex);
    list_add_tail(&priv->dev_list, &dev_list);
    list_for_each_entry(intf, &intf_list, list) {
        sx_core_add_device(intf, priv);
    }

    mutex_unlock(&intf_mutex);

    return 0;
}

void sx_core_unregister_device(struct sx_dev *dev)
{
    struct sx_priv      *priv = sx_priv(dev);
    struct sx_interface *intf;

    mutex_lock(&intf_mutex);
    list_for_each_entry(intf, &intf_list, list) {
        sx_core_remove_device(intf, priv);
    }

    list_del(&priv->dev_list);

    mutex_unlock(&intf_mutex);
}
