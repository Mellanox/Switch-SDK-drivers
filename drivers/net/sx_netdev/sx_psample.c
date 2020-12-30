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

#if IS_ENABLED(CONFIG_PSAMPLE)

#include <linux/module.h>

#include <linux/if_vlan.h>
#include <net/psample.h>

#include <linux/mlx_sx/driver.h>

#include "sx_netdev.h"
#include "sx_psample.h"

#define MAX_PSAMPLE_LISTENERS (16)

struct psample_listener_context {
    struct sx_psample_listener_context sx_psample_context; /* must be first in this struct! */
    struct list_head                   listeners_list;
    struct psample_group              *group;
};

static LIST_HEAD(__psample_listener_db);
static uint32_t __psample_listener_db_size = 0;
static DEFINE_MUTEX(__psample_listener_db_lock);

static uint32_t __psample_port_rate_db[MAX_PHYPORT_NUM];
static void __psample_handler(struct completion_info* ci, void *context)
{
    struct psample_listener_context *listener_ctx = (struct psample_listener_context*)context;
    unsigned long                    flags;
    u32                              ingress_ifindex = 0;
    u32                              rate = 0;
    u16                              local_port;
    int                              i, ret;

    if (ci->is_lag) {
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_local,
                                   ret,
                                   ci->dev,
                                   ci->sysport, /* lad-id */
                                   ci->lag_subport,
                                   &local_port);

        if (ret) {
            goto skip_local_port;
        }
    } else {
        local_port = ci->sysport;
    }

    if (local_port >= MAX_PHYPORT_NUM) {
        goto skip_local_port;
    }

    /* there may be 2 net-devices on the same sysport.
     * only one of them will get the psample packet (the first one).
     * unfortunately, the lock is acquired by the heavy spin_lock_irqsave() and not
     * spin_lock_bh() because we're called from dispatch_pkt() which holds its own
     * lock with spin_lock_irqsave().
     */
    spin_lock_irqsave(&g_netdev_resources->rsc_lock, flags);
    for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
        if (g_netdev_resources->port_netdev[PORT_TYPE_SINGLE][local_port][i] != NULL) {
            ingress_ifindex = g_netdev_resources->port_netdev[PORT_TYPE_SINGLE][local_port][i]->ifindex;
            break;
        }
    }
    spin_unlock_irqrestore(&g_netdev_resources->rsc_lock, flags);

    rate = __psample_port_rate_db[local_port];

skip_local_port:

    psample_sample_packet(listener_ctx->group,
                          ci->skb,
                          ci->original_packet_size,
                          ingress_ifindex,
                          0, /* egress_ifindex */
                          rate);
}


/* must be called when DB is locked! */
static struct psample_listener_context * __db_lookup(u32 group_id)
{
    struct psample_listener_context *iter;

    list_for_each_entry(iter, &__psample_listener_db, listeners_list) {
        if (iter->sx_psample_context.group_num == group_id) {
            return iter;
        }
    }

    return NULL;
}


static int __psample_synd_add(struct sx_dev *dev, u16 synd, union sx_event_data *event_data)
{
    union ku_filter_critireas        crit;
    struct psample_listener_context *listener_ctx;
    u32                              group_id;
    int                              err = 0;

    memset(&crit, 0, sizeof(crit));
    group_id = event_data->psample_synd.psample_info.group_id;

    mutex_lock(&__psample_listener_db_lock);

    listener_ctx = __db_lookup(group_id);
    if (listener_ctx) {
        printk(KERN_INFO "PSAMPLE [add group_id=%u]: listener already exists, adding reference\n", group_id);
        goto listener_ctx_ready;
    }

    if (__psample_listener_db_size == MAX_PSAMPLE_LISTENERS) {
        printk(KERN_ERR "PSAMPLE [add group_id=%u]: database is full, cannot add another entry\n", group_id);
        err = -EUSERS;
        goto out;
    }

    listener_ctx = kzalloc(sizeof(struct psample_listener_context), GFP_KERNEL);
    if (!listener_ctx) {
        printk(KERN_ERR "PSAMPLE [add group_id=%u]: could not allocate context\n", group_id);
        err = -ENOMEM;
        goto out;
    }

    listener_ctx->sx_psample_context.group_num = group_id;
    listener_ctx->sx_psample_context.refcnt = 0;
    INIT_LIST_HEAD(&listener_ctx->listeners_list);
    listener_ctx->group = psample_group_get(&init_net, group_id);

    if (!listener_ctx->group) {
        printk(KERN_ERR "PSAMPLE [add group_id=%u]: could not get group\n", group_id);
        err = -ENOMEM;
        goto cleanup;
    }

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd,
                               err,
                               event_data->psample_synd.swid,
                               event_data->psample_synd.hw_synd,
                               L2_TYPE_ETH,
                               0,
                               0,
                               crit,
                               __psample_handler,
                               listener_ctx,
                               CHECK_DUP_DISABLED_E,
                               dev,
                               &event_data->psample_synd.port_vlan_params,
                               event_data->psample_synd.is_register);

    if (err) {
        printk(KERN_ERR "PSAMPLE [add group_id=%u]: could not add synd listener (err=%d)\n", group_id, err);
        goto cleanup;
    }

    list_add_tail(&listener_ctx->listeners_list, &__psample_listener_db);
    __psample_listener_db_size++;

listener_ctx_ready:
    listener_ctx->sx_psample_context.refcnt++;

cleanup:
    if (err) {
        /* at this point, it is guaranteed that listener_ctx is a new valid allocation */
        if (listener_ctx->group) {
            psample_group_put(listener_ctx->group);
        }

        kfree(listener_ctx);
    }

out:
    mutex_unlock(&__psample_listener_db_lock);
    return err;
}


static int __psample_synd_remove(struct sx_dev *dev, u16 synd, union sx_event_data *event_data)
{
    union ku_filter_critireas        crit;
    struct psample_listener_context *listener_ctx;
    u32                              group_id;
    int                              err = 0;

    memset(&crit, 0, sizeof(crit));
    group_id = event_data->psample_synd.psample_info.group_id;

    mutex_lock(&__psample_listener_db_lock);

    listener_ctx = __db_lookup(group_id);
    if (!listener_ctx) { /* did not find it in DB */
        printk(KERN_ERR "PSAMPLE [del group_id=%u]: could not find listener in database\n", group_id);
        err = -ENOENT;
        goto out;
    }

    if (--listener_ctx->sx_psample_context.refcnt > 0) {
        printk(KERN_INFO "PSAMPLE [del group_id=%u]: listener still has references\n", group_id);
        goto out;
    }

    /* when entry is removed from DB, it is guaranteed that the PSAMPLE handler is not in
     * the middle of execution [dispatch_pkt() that runs the handler and sx_core_remove_synd()
     * share the same lock] */
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_remove_synd,
                               err,
                               event_data->psample_synd.swid,
                               event_data->psample_synd.hw_synd,
                               L2_TYPE_ETH,
                               0,
                               crit,
                               listener_ctx,
                               dev,
                               __psample_handler,
                               &event_data->psample_synd.port_vlan_params,
                               event_data->psample_synd.is_register);

    if (err) {
        listener_ctx->sx_psample_context.refcnt++; /* rollback */
        printk(KERN_ERR "PSAMPLE [del group_id=%u]: could not remove synd listener (err=%d)\n", group_id, err);
        goto out;
    }

    list_del(&listener_ctx->listeners_list);
    psample_group_put(listener_ctx->group);
    kfree(listener_ctx);

    __psample_listener_db_size--;

out:
    mutex_unlock(&__psample_listener_db_lock);
    return err;
}


void sx_psample_set_synd(struct sx_dev *dev, u16 synd, enum sx_dev_event event, union sx_event_data *event_data)
{
    switch (event) {
    case SX_DEV_EVENT_ADD_SYND_PSAMPLE:
        __psample_synd_add(dev, synd, event_data);
        break;

    case SX_DEV_EVENT_REMOVE_SYND_PSAMPLE:
        __psample_synd_remove(dev, synd, event_data);
        break;

    default:
        printk(KERN_ERR "invalid PSAMPLE sx-dev-event (event=%d)\n", event);
        break;
    }
}


void sx_psample_set_port_sample_ret(u8 local_port, u32 rate)
{
    if (local_port >= MAX_PHYPORT_NUM) {
        printk(KERN_ERR "PSAMPLE sample rate update got invalid local port (%u)\n", local_port);
    } else {
        printk(KERN_INFO "PSAMPLE - update port %u sampling rate to %u\n", local_port, rate);
        __psample_port_rate_db[local_port] = rate;
    }
}


void sx_psample_cleanup(void)
{
    CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_flush_synd_by_handler, __psample_handler);
}

#endif /* IS_ENABLED(CONFIG_PSAMPLE) */
