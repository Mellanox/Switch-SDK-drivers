/*
 * Copyright (C) 2010-2023 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#if IS_ENABLED(CONFIG_PSAMPLE)

#include <linux/module.h>

#include <linux/if_vlan.h>
#include <net/psample.h>

#include <linux/mlx_sx/driver.h>

#if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0))
#include <net/pkt_cls.h>
#include <net/tc_act/tc_sample.h>

extern int sx_netdev_tc_psample_enable;
#endif /* if defined(CONFIG_NET_PORT) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) */

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

static uint32_t __psample_port_rate_db[MAX_PHYPORT_NUM + 1];

static struct workqueue_struct *psample_wq = NULL;

struct psample_work_data {
    struct work_struct    work;
    struct psample_group *group;
    struct sk_buff       *skb;
    u32                   original_packet_size;
    u32                   ingress_ifindex;
    u32                   egress_ifindex;
    u32                   rate;
#if defined(PSAMPLE_MD_EXTENDED_ATTR) || defined(CONFIG_SX_RHEL_8_6) || defined(CONFIG_SX_CENTOS_8_4) || \
    (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 13, 0))
    struct psample_metadata md;
#endif
};

#ifdef PSAMPLE_MD_EXTENDED_ATTR

static void psample_wq_add_work_ext(struct psample_group    *group,
                                    struct completion_info  *ci,
                                    u32                      rate,
                                    struct psample_metadata *md);
#else
static void psample_wq_add_work(struct psample_group   *group,
                                struct completion_info *ci,
                                u32                     ingress_ifindex,
                                u32                     egress_ifindex,
                                u32                     rate);
#endif


#ifdef PSAMPLE_MD_EXTENDED_ATTR

static void __psample_sample_packet_ext(struct completion_info* ci,
                                        struct psample_group   *group,
                                        u32                     ingress_ifindex,
                                        u32                     egress_ifindex,
                                        u32                     rate)
{
    struct psample_metadata md = {};

    md.trunc_size = ci->skb->len;     /* truncation supported on psample level */
    md.in_ifindex = ingress_ifindex;
    md.out_ifindex = egress_ifindex;

    /* The fields below are relevant only for packets that mirrored to CPU */
    if ((ci->hw_synd >= SXD_TRAP_ID_MIRROR_AGENT0) &&
        (ci->hw_synd <= SXD_TRAP_ID_MIRROR_AGENT7)) {
        md.out_tc_valid = (ci->mirror_tclass == SX_CQE_MIRROR_TCLASS_INVALID) ? 0 : 1;
        if (md.out_tc_valid) {
            md.out_tc = ci->mirror_tclass;
        }

        /* Congestion level in units of 8KB of the egress traffic class of the original
         * packet that does mirroring to the CPU.
         * Value of 0xFFFF means that the congestion level is invalid.
         */
        md.out_tc_occ_valid = (ci->mirror_cong == SX_CQE_MIRROR_CONG_INVALID) ? 0 : 1;
        if (md.out_tc_occ_valid) {
            md.out_tc_occ = ci->mirror_cong;
            md.out_tc_occ <<= SX_CQE_MIRROR_CONG_SHIFT;
        }

        /* The latency units are determined according to MOGCR.mirror_latency_units.
         * It defaults to 64 nanoseconds.
         * Value of 0xFFFFFF means that the latency value is invalid.
         */
        md.latency_valid = (ci->mirror_lantency == SX_CQE_MIRROR_LATENCY_INVALID) ? 0 : 1;
        if (md.latency_valid) {
            md.latency = ci->mirror_lantency;
            md.latency <<= SX_CQE_MIRROR_LATENCY_SHIFT;
        }
    }

    psample_wq_add_work_ext(group, ci, rate, &md);
}

#endif /* #ifndef PSAMPLE_MD_EXTENDED_ATTR */

static void __psample_handler(struct completion_info* ci, void *context)
{
    struct psample_listener_context *listener_ctx = (struct psample_listener_context*)context;
    struct net_device               *netdev;
    u32                              ingress_ifindex = 0, egress_ifindex = 0;
    u32                              rate = 0;
    u16                              ingress_local_port = INVALID_LOCAL_PORT;
    u16                              egress_local_port = INVALID_LOCAL_PORT;
    int                              i, ret;

    /*
     * find ingress local port
     */
    if (ci->is_lag) {
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_local,
                                   ret,
                                   ci->dev,
                                   ci->sysport, /* lad-id */
                                   ci->lag_subport,
                                   &ingress_local_port);

        if (ret) {
            goto skip_local_port;
        }
    } else {
        ingress_local_port = ci->sysport;
    }

    if (ingress_local_port > MAX_PHYPORT_NUM) {
        goto skip_local_port;
    }

    /*
     * find egress local port
     */
    if (ci->dest_is_lag) {
        CALL_SX_CORE_FUNC_WITH_RET(sx_core_get_local,
                                   ret,
                                   ci->dev,
                                   ci->dest_sysport, /* lad-id */
                                   ci->dest_lag_subport,
                                   &egress_local_port);

        if (ret) {
            egress_local_port = INVALID_LOCAL_PORT;
        }
    } else {
        egress_local_port = ci->dest_sysport;
    }


    /* there may be 2 net-devices on the same sysport.
     * only one of them will get the psample packet (the first one).
     */
    rcu_read_lock();

    for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
        netdev = rcu_dereference(g_netdev_resources->port_netdev[PORT_TYPE_SINGLE][ingress_local_port][i]);
        if (netdev) {
            ingress_ifindex = netdev->ifindex;
            break;
        }
    }

    if (egress_local_port <= MAX_PHYPORT_NUM) {
        for (i = 0; i < MAX_PORT_NETDEV_NUM; i++) {
            netdev = rcu_dereference(g_netdev_resources->port_netdev[PORT_TYPE_SINGLE][egress_local_port][i]);
            if (netdev) {
                egress_ifindex = netdev->ifindex;
                break;
            }
        }
    }

    rcu_read_unlock();

    rate = __psample_port_rate_db[ingress_local_port];

skip_local_port:

#ifdef PSAMPLE_MD_EXTENDED_ATTR
    __psample_sample_packet_ext(ci, listener_ctx->group, ingress_ifindex,
                                egress_ifindex, rate);
#else
    psample_wq_add_work(listener_ctx->group, ci, ingress_ifindex, egress_ifindex, rate);
#endif
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


static int __psample_listener_get(u32 group_id, struct psample_listener_context **listener_ctx_pp)
{
    union ku_filter_critireas        crit;
    struct psample_listener_context *listener_ctx = NULL;
    int                              err = 0, is_listener_allocated = 0;

    memset(&crit, 0, sizeof(crit));

    listener_ctx = __db_lookup(group_id);
    if (listener_ctx == NULL) {
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
        is_listener_allocated = 1;

        listener_ctx->sx_psample_context.group_num = group_id;
        listener_ctx->sx_psample_context.refcnt = 0;
        INIT_LIST_HEAD(&listener_ctx->listeners_list);
        listener_ctx->group = psample_group_get(&init_net, group_id);

        if (!listener_ctx->group) {
            printk(KERN_ERR "PSAMPLE [add group_id=%u]: could not get group\n", group_id);
            err = -ENOMEM;
            goto cleanup;
        }

        list_add_tail(&listener_ctx->listeners_list, &__psample_listener_db);
        __psample_listener_db_size++;
    }

    listener_ctx->sx_psample_context.refcnt++;
    *listener_ctx_pp = listener_ctx;

cleanup:
    /* error can happen only in case of newly allocated listener */
    if (err) {
        /* at this point, it is guaranteed that listener_ctx is a new valid allocation */
        if (listener_ctx->group) {
            psample_group_put(listener_ctx->group);
        }

        if (is_listener_allocated) {
            kfree(listener_ctx);
            listener_ctx = NULL;
        }
    }

out:
    return err;
}


static int __psample_listener_put(u32 group_id)
{
    union ku_filter_critireas        crit;
    struct psample_listener_context *listener_ctx;
    int                              err = 0;

    memset(&crit, 0, sizeof(crit));

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

    list_del(&listener_ctx->listeners_list);
    psample_group_put(listener_ctx->group);
    kfree(listener_ctx);

    __psample_listener_db_size--;

out:
    return err;
}


static int __psample_synd_add(struct sx_dev *dev, u16 synd, union sx_event_data *event_data)
{
    union ku_filter_critireas        crit;
    struct psample_listener_context *listener_ctx = NULL;
    u32                              group_id;
    int                              err = 0;

    memset(&crit, 0, sizeof(crit));
    group_id = event_data->psample_synd.psample_info.group_id;

    mutex_lock(&__psample_listener_db_lock);

    err = __psample_listener_get(group_id, &listener_ctx);
    if (err) {
        printk(KERN_ERR "__psample_listener_get failed for group_id=%u (err=%d)\n", group_id, err);
        goto out;
    }

    CALL_SX_CORE_FUNC_WITH_RET(sx_core_add_synd,
                               err,
                               event_data->psample_synd.swid,
                               event_data->psample_synd.hw_synd,
                               L2_TYPE_ETH,
                               0,
                               "sx_psample",
                               0,
                               &crit,
                               __psample_handler,
                               listener_ctx,
                               CHECK_DUP_DISABLED_E,
                               dev,
                               &event_data->psample_synd.port_vlan_params,
                               event_data->psample_synd.is_register);

    if (err) {
        printk(KERN_ERR "PSAMPLE [add group_id=%u]: could not add synd listener (err=%d)\n", group_id, err);
        goto out;
    }

out:
    if (err && (listener_ctx != NULL)) {
        __psample_listener_put(group_id);
    }

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

    /* when entry is removed from DB, it is guaranteed that the PSAMPLE handler is not in
     * the middle of execution [dispatch_pkt() that runs the handler and sx_core_remove_synd()
     * share the same lock] */
    CALL_SX_CORE_FUNC_WITH_RET(sx_core_remove_synd,
                               err,
                               event_data->psample_synd.swid,
                               event_data->psample_synd.hw_synd,
                               L2_TYPE_ETH,
                               0,
                               &crit,
                               listener_ctx,
                               dev,
                               __psample_handler,
                               &event_data->psample_synd.port_vlan_params,
                               event_data->psample_synd.is_register, NULL);

    if (err) {
        listener_ctx->sx_psample_context.refcnt++; /* rollback */
        printk(KERN_ERR "PSAMPLE [del group_id=%u]: could not remove synd listener (err=%d)\n", group_id, err);
        goto out;
    }

    __psample_listener_put(group_id);

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


void sx_psample_set_port_sample_ret(u16 local_port, u32 rate)
{
    if (local_port > MAX_PHYPORT_NUM) {
        printk(KERN_ERR "PSAMPLE sample rate update got invalid local port (%u)\n", local_port);
    } else {
        printk(KERN_INFO "PSAMPLE - update port %u sampling rate to %u\n", local_port, rate);
        __psample_port_rate_db[local_port] = rate;
    }
}

static void psample_work_handler(struct work_struct *work)
{
    struct psample_work_data * data = (struct psample_work_data *)work;

#if defined(PSAMPLE_MD_EXTENDED_ATTR) || defined(CONFIG_SX_RHEL_8_6) || defined(CONFIG_SX_CENTOS_8_4) || \
    (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 13, 0))
    psample_sample_packet(data->group, data->skb, data->rate, &data->md);
#else
    psample_sample_packet(data->group, data->skb, data->original_packet_size,
                          data->ingress_ifindex, data->egress_ifindex, data->rate);
#endif
    consume_skb(data->skb); /* free unused skb, use consume_skb */
    kfree(data);
}

static void __psample_wq_add_work(struct psample_work_data * external_data)
{
    struct psample_work_data * data;
    bool                       rc;

    data = kmalloc(sizeof(struct psample_work_data), GFP_ATOMIC);
    if (data == NULL) {
        printk(KERN_ERR "PSAMPLE : failed to alloc work_data \n");
        return;
    }
    INIT_WORK(&data->work, psample_work_handler);
    data->group = external_data->group;
    skb_get(external_data->skb);
    data->skb = external_data->skb;
    data->rate = external_data->rate;
#ifdef PSAMPLE_MD_EXTENDED_ATTR
    data->md = external_data->md;
#else
    data->original_packet_size = external_data->original_packet_size;
    data->ingress_ifindex = external_data->ingress_ifindex;
    data->egress_ifindex = external_data->egress_ifindex;
#endif

    rc = queue_work(psample_wq, &data->work);
    if (rc == false) {
        kfree_skb(data->skb); /* drop flow, use kfree_skb */
        kfree(data);
    }
}

#ifdef PSAMPLE_MD_EXTENDED_ATTR

static void psample_wq_add_work_ext(struct psample_group    *group,
                                    struct completion_info  *ci,
                                    u32                      rate,
                                    struct psample_metadata *md)
{
    struct psample_work_data data;

    data.group = group;
    data.skb = ci->skb;
    data.rate = rate;
    data.md = *md;

    __psample_wq_add_work(&data);
}

#else

static void psample_wq_add_work(struct psample_group   *group,
                                struct completion_info *ci,
                                u32                     ingress_ifindex,
                                u32                     egress_ifindex,
                                u32                     rate)
{
    struct psample_work_data data;

    data.group = group;
    data.skb = ci->skb;
    data.rate = rate;
    data.original_packet_size = ci->original_packet_size;
    data.ingress_ifindex = ingress_ifindex;
    data.egress_ifindex = egress_ifindex;

    __psample_wq_add_work(&data);
}

#endif

static void psample_wq_init(void)
{
    if (psample_wq == NULL) {
        psample_wq = create_workqueue("psample_wq");
    }
}

static void psample_wq_deinit(void)
{
    if (psample_wq != NULL) {
        flush_workqueue(psample_wq);
        destroy_workqueue(psample_wq);
        psample_wq = NULL;
    }
}

void sx_psample_init(void)
{
    psample_wq_init();
}

void sx_psample_cleanup(void)
{
    struct psample_listener_context *psample_listener_context_p;
    struct list_head                *pos, *q;

    psample_wq_deinit();

    CALL_SX_CORE_FUNC_WITHOUT_RET(sx_core_flush_synd_by_handler, __psample_handler);

    mutex_lock(&__psample_listener_db_lock);

    if (!list_empty(&__psample_listener_db)) {
        list_for_each_safe(pos, q, &__psample_listener_db) {
            psample_listener_context_p = list_entry(pos, struct psample_listener_context,
                                                    listeners_list);
            list_del(&psample_listener_context_p->listeners_list);
            psample_group_put(psample_listener_context_p->group);
            kfree(psample_listener_context_p);
            __psample_listener_db_size--;
        }
    }

    mutex_unlock(&__psample_listener_db_lock);
}

#if defined(CONFIG_NET_PORT) &&                         \
    (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) && \
    (LINUX_VERSION_CODE < KERNEL_VERSION(5, 10, 0))
static int sx_psample_add_cls_matchall_sample(struct sx_net_priv             *sx_port,
                                              struct tc_cls_matchall_offload *cls,
                                              const struct tc_action         *a,
                                              bool                            ingress)
{
    return 0;
}

static void sx_psample_del_cls_matchall_sample(struct sx_net_priv *sx_port, bool ingress)
{
}

static int sx_psample_add_cls_matchall(struct sx_net_priv *sx_port, struct tc_cls_matchall_offload *f, bool ingress)
{
    __be16                  protocol = f->common.protocol;
    const struct tc_action *a;
    int                     err;

    if (!tcf_exts_has_one_action(f->exts)) {
        netdev_err(sx_port->netdev,
                   "only singular actions are supported\n");
        return -EOPNOTSUPP;
    }

    a = tcf_exts_first_action(f->exts);

    if (is_tcf_sample(a) && (protocol == htons(ETH_P_ALL))) {
        err = sx_psample_add_cls_matchall_sample(sx_port, f, a, ingress);
    } else {
        err = -EOPNOTSUPP;
    }

    return err;
}

static void sx_psample_del_cls_matchall(struct sx_net_priv *sx_port, struct tc_cls_matchall_offload *f, bool ingress)
{
    sx_psample_del_cls_matchall_sample(sx_port, ingress);
}

static int sx_psample_setup_tc_cls_matchall(struct sx_net_priv             *sx_port,
                                            struct tc_cls_matchall_offload *f,
                                            bool                            ingress)
{
    switch (f->command) {
    case TC_CLSMATCHALL_REPLACE:
        return sx_psample_add_cls_matchall(sx_port, f, ingress);

    case TC_CLSMATCHALL_DESTROY:
        sx_psample_del_cls_matchall(sx_port, f, ingress);
        return 0;

    default:
        return -EOPNOTSUPP;
    }
}

static int sx_psample_setup_tc_block_cb(enum tc_setup_type type, void *type_data, void *cb_priv, bool ingress)
{
    struct sx_net_priv *sx_port = cb_priv;

    switch (type) {
    case TC_SETUP_CLSMATCHALL:
        if (!tc_cls_can_offload_and_chain0(sx_port->netdev, type_data)) {
            return -EOPNOTSUPP;
        }

        return sx_psample_setup_tc_cls_matchall(sx_port, type_data, ingress);

    default:
        return -EOPNOTSUPP;
    }
}

static int sx_psample_setup_tc_block_cb_ingress(enum tc_setup_type type, void *type_data, void *cb_priv)
{
    return sx_psample_setup_tc_block_cb(type, type_data, cb_priv, true);
}

static int sx_psample_setup_tc_block_cb_egress(enum tc_setup_type type, void *type_data, void *cb_priv)
{
    return sx_psample_setup_tc_block_cb(type, type_data, cb_priv, false);
}

static int sx_psample_setup_tc_block(struct sx_net_priv *sx_port, struct tc_block_offload *f)
{
    tc_setup_cb_t *cb;

    if (f->binder_type == TCF_BLOCK_BINDER_TYPE_CLSACT_INGRESS) {
        cb = sx_psample_setup_tc_block_cb_ingress;
    } else if (f->binder_type == TCF_BLOCK_BINDER_TYPE_CLSACT_EGRESS) {
        cb = sx_psample_setup_tc_block_cb_egress;
    } else {
        return -EOPNOTSUPP;
    }

    switch (f->command) {
    case TC_BLOCK_BIND:
        return tcf_block_cb_register(f->block, cb, sx_port, sx_port,
                                     f->extack);

    case TC_BLOCK_UNBIND:
        tcf_block_cb_unregister(f->block, cb, sx_port);
        return 0;

    default:
        return -EOPNOTSUPP;
    }
}

int sx_psample_setup_tc(struct net_device *dev, enum tc_setup_type type, void *type_data)
{
    struct sx_net_priv *sx_port = netdev_priv(dev);

    if (!sx_netdev_tc_psample_enable || (type != TC_SETUP_BLOCK)) {
        return -EOPNOTSUPP;
    }

    return sx_psample_setup_tc_block(sx_port, type_data);
}
#endif /* if defined(CONFIG_NET_PORT) && \
        *     (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)) && \
        *     (LINUX_VERSION_CODE < KERNEL_VERSION(5, 10, 0)) */

#endif /* IS_ENABLED(CONFIG_PSAMPLE) */
