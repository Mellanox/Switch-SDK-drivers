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

#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/device.h>
#include "sx.h"
#include "sgmii.h"
#include "alloc.h"

extern struct sx_globals sx_glb;
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
    union sx_event_data      *event_data, *tca_init_event_data;
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

    tca_init_event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!tca_init_event_data) {
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
                if (priv->dev.profile.swid_type[i] ==
                    SX_KU_L2_TYPE_IB) {
                    ib_swid_present = 1;
                    printk(KERN_DEBUG PFX "sx_core_add_device: "
                           "dispatching IB swid up event\n");
                    event_data->ib_swid_change.swid = i;
                    event_data->ib_swid_change.dev_id = 1;
                    dev_ctx->intf->event(&priv->dev,
                                         dev_ctx->context,
                                         SX_DEV_EVENT_IB_SWID_UP, event_data);
                    if (priv->dev.profile.ipoib_router_port_enable[i]) {
                        tca_init_event_data->tca_init.swid[tca_init_event_data->tca_init.num_of_ib_swids++] = i;
                    }
                } else if (priv->dev.profile.swid_type[i] ==
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
            if (tca_init_event_data->tca_init.num_of_ib_swids != 0) {
                tca_init_event_data->tca_init.max_pkey =
                    priv->dev.profile.max_pkey;
                dev_ctx->intf->event(&priv->dev,
                                     dev_ctx->context,
                                     SX_DEV_EVENT_TYPE_TCA_INIT,
                                     tca_init_event_data);
                dev_ctx->intf->event(&priv->dev,
                                     dev_ctx->context,
                                     SX_DEV_EVENT_TYPE_RPA_INIT,
                                     tca_init_event_data);
            }
        }

        spin_lock_irqsave(&priv->ctx_lock, flags);
        list_add_tail(&dev_ctx->list, &priv->ctx_list);
        spin_unlock_irqrestore(&priv->ctx_lock, flags);
    } else {
        kfree(dev_ctx);
    }

    kfree(tca_init_event_data);
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
    list_for_each_entry(priv, &dev_list, dev_list)
    sx_core_add_device(intf, priv);

    mutex_unlock(&intf_mutex);

    return 0;
}
EXPORT_SYMBOL(sx_register_interface);

void sx_unregister_interface(struct sx_interface *intf)
{
    struct sx_priv *priv;

    mutex_lock(&intf_mutex);
    list_for_each_entry(priv, &dev_list, dev_list)
    sx_core_remove_device(intf, priv);

    list_del(&intf->list);

    mutex_unlock(&intf_mutex);
}
EXPORT_SYMBOL(sx_unregister_interface);

struct sx_dev* sx_attach_interface(void* dev_ctx)
{
    struct sx_device_context *dev_ctx_tmp;
    struct sx_priv           *priv;
    unsigned int              found_entry = 0;
    struct sx_interface      *intf_tmp;
    struct sx_dev           * ret_dev = NULL;
    unsigned long             flags;

    if (!dev_ctx) {
        return ret_dev;
    }

    mutex_lock(&intf_mutex);
    list_for_each_entry(intf_tmp, &intf_list, list) {
        if (intf_tmp == ((struct sx_device_context*)dev_ctx)->intf) {
            found_entry = 1;
            break;
        }
    }
    if (!found_entry) {
        list_add_tail(&(((struct sx_device_context*)dev_ctx)->intf->list), &intf_list);
    }

    found_entry = 0;
    priv = list_first_entry_or_null(&dev_list, struct sx_priv, dev_list);
    if (priv) {
        spin_lock_irqsave(&priv->ctx_lock, flags);
        list_for_each_entry(dev_ctx_tmp, &priv->ctx_list, list) {
            if (dev_ctx_tmp == dev_ctx) {
                found_entry = 1;
                break;
            }
        }
        if (!found_entry) {
            list_add_tail(&(((struct sx_device_context*)dev_ctx)->list), &priv->ctx_list);
        }
        spin_unlock_irqrestore(&priv->ctx_lock, flags);
        ret_dev = &priv->dev;
    }

    mutex_unlock(&intf_mutex);
    return ret_dev;
}
EXPORT_SYMBOL(sx_attach_interface);
void* sx_detach_interface(struct sx_interface *intf, struct sx_dev *dev)
{
    struct sx_priv           *priv;
    struct sx_device_context *dev_ctx, *tmp;
    unsigned long             flags;
    void                     *ret_dev_ctx = NULL;

    if (!intf || !dev) {
        return ret_dev_ctx;
    }

    mutex_lock(&intf_mutex);
    list_for_each_entry(priv, &dev_list, dev_list) {
        if (dev == &priv->dev) {
            list_for_each_entry_safe(dev_ctx, tmp, &priv->ctx_list, list) {
                if (dev_ctx->intf == intf) {
                    spin_lock_irqsave(&priv->ctx_lock, flags);
                    list_del(&dev_ctx->list);
                    spin_unlock_irqrestore(&priv->ctx_lock, flags);
                    ret_dev_ctx = dev_ctx;
                    break;
                }
            }
            break;
        }
    }

    list_del(&intf->list);
    mutex_unlock(&intf_mutex);

    return ret_dev_ctx;
}
EXPORT_SYMBOL(sx_detach_interface);

void sx_core_dispatch_event(struct sx_dev *dev, enum sx_dev_event type, union sx_event_data *event_data)
{
    struct sx_priv           *priv = sx_priv(dev);
    struct sx_device_context *dev_ctx;

    if (is_sgmii_supported()) {
        /*
         * we need SwitchX's sx_dev for ib0 bringup!
         * leave the priv, change only the dev!
         * */
        dev = sx_glb.oob_backbone_dev;
        if (!dev) {
            printk(KERN_ERR "There is no SGMII backbone dev!\n");
            return;
        }
    }

    /* We can't hold a spinlock when dispatching a swid up/down event
     *  because sx_ib will not be able to register the
     * IB device on PPC. We might have to solve this in the
     * future for scalability. */
    spin_lock(&priv->ctx_lock);
    list_for_each_entry(dev_ctx, &priv->ctx_list, list) {
        if (dev_ctx->intf->event) {
            printk(KERN_DEBUG PFX "sx_core_dispatch_event: "
                   "dispatching the event\n");
            spin_unlock(&priv->ctx_lock);
            mutex_lock(&intf_mutex);
            dev_ctx->intf->event(dev, dev_ctx->context, type, event_data);
            mutex_unlock(&intf_mutex);
            spin_lock(&priv->ctx_lock);
        }
    }

    spin_unlock(&priv->ctx_lock);
}

int sx_core_register_device(struct sx_dev *dev)
{
    struct sx_priv      *priv = sx_priv(dev);
    struct sx_interface *intf;

    mutex_lock(&intf_mutex);
    list_add_tail(&priv->dev_list, &dev_list);
    list_for_each_entry(intf, &intf_list, list)
    sx_core_add_device(intf, priv);

    mutex_unlock(&intf_mutex);

    return 0;
}

void sx_core_unregister_device(struct sx_dev *dev)
{
    struct sx_priv      *priv = sx_priv(dev);
    struct sx_interface *intf;

    if (dev->pdev) {
        sx_core_stop_catas_poll(dev);
    }

    mutex_lock(&intf_mutex);
    list_for_each_entry(intf, &intf_list, list)
    sx_core_remove_device(intf, priv);

    list_del(&priv->dev_list);

    mutex_unlock(&intf_mutex);
}
