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

#include <linux/types.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <net/sock.h>

#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include <linux/mlx_sx/auto_registers/reg.h>

#include "cq.h"
#include "sx_clock.h"
#include "ptp.h"
#include "dev_db.h"

#define PTP_GC_TIME   (5 * HZ)       /* Event with age of more than 5 seconds should be garbage-collected */
#define MTPPTR_OFFSET (0x24)

static struct kmem_cache  *__records_cache;
static struct kmem_cache  *__rx_event_cache;
static struct kmem_cache  *__tx_event_cache;
static struct semaphore    __ptp_polling_sem;
static struct task_struct *__ptp_rx_polling_thread;
static atomic_t            __ptp_rx_polling_thread_users = ATOMIC_INIT(0);

static struct ptp_rx_event_data * __ptp_allocate_rx_event_data(gfp_t                                gfp,
                                                               struct completion_info              *ci,
                                                               const struct sx_ptp_packet_metadata *pkt_meta)
{
    struct ptp_rx_event_data *rx_event;

    rx_event = (struct ptp_rx_event_data*)kmem_cache_alloc(__rx_event_cache, gfp);

    if (rx_event) {
        INIT_LIST_HEAD(&rx_event->common.list);
        rx_event->common.pkt_fields.seqid = pkt_meta->pkt_fields.seqid;
        rx_event->common.pkt_fields.domain = pkt_meta->pkt_fields.domain;
        rx_event->common.pkt_fields.msg_type = pkt_meta->pkt_fields.msg_type;
        rx_event->common.need_timestamp = pkt_meta->timestamp_required;
        rx_event->common.since = jiffies;
        rx_event->ci = ci;
    }

    return rx_event;
}


static void __ptp_free_rx_event_data(struct ptp_rx_event_data *rx_event_data)
{
    sx_skb_consume(rx_event_data->ci->skb); /* free unused skb, use consume_skb */
    kfree(rx_event_data->ci);
    kmem_cache_free(__rx_event_cache, rx_event_data);
}


static struct ptp_tx_event_data * __ptp_allocate_tx_event_data(gfp_t                                gfp,
                                                               struct sk_buff                      *skb,
                                                               const struct sx_ptp_packet_metadata *pkt_meta)
{
    struct ptp_tx_event_data *tx_event;

    tx_event = (struct ptp_tx_event_data*)kmem_cache_alloc(__tx_event_cache, gfp);

    if (tx_event) {
        INIT_LIST_HEAD(&tx_event->common.list);
        tx_event->skb = skb_get(skb); /* need to add reference so skb will not be deleted until FIFO event */
        tx_event->common.pkt_fields.seqid = pkt_meta->pkt_fields.seqid;
        tx_event->common.pkt_fields.domain = pkt_meta->pkt_fields.domain;
        tx_event->common.pkt_fields.msg_type = pkt_meta->pkt_fields.msg_type;
        tx_event->common.need_timestamp = 1;
        tx_event->common.since = jiffies;
    }

    return tx_event;
}


static void __ptp_free_tx_event_data(struct ptp_tx_event_data *tx_event_data)
{
    if (tx_event_data->skb) {
        sx_skb_consume(tx_event_data->skb); /* just release the reference we took when tx_event_data was allocated */
    }

    kmem_cache_free(__tx_event_cache, tx_event_data);
}


static struct ptp_record * __ptp_allocate_record_data(gfp_t gfp, const struct mtpptr_record *record)
{
    struct ptp_record *record_data;

    record_data = (struct ptp_record*)kmem_cache_alloc(__records_cache, gfp);

    if (record_data) {
        record_data->since = jiffies;
        INIT_LIST_HEAD(&record_data->list);
        memcpy(&record_data->mtpptr, record, sizeof(record_data->mtpptr));
    }

    return record_data;
}


static void __ptp_free_record_data(struct ptp_record *record_data)
{
    kmem_cache_free(__records_cache, record_data);
}


static void __gc_db(struct sx_priv *priv, int sysport, struct ptp_db *db, bool gc_all)
{
    struct ptp_common_event_data *iter_common, *tmp_common;
    struct ptp_record            *iter_rec, *tmp_rec;
    unsigned long                 now = jiffies;

    spin_lock_bh(&db->sysport_lock[sysport]);

    list_for_each_entry_safe(iter_common, tmp_common, &db->sysport_events_list[sysport], list) {
        if (gc_all || time_after(now, iter_common->since + PTP_GC_TIME)) {
            sx_int_log_error(&priv->ptp.log,
                             "GC (missing timestamp): Event={dir=%s, port=%d, seq=%u, domain=%u, msg_type=%u}",
                             (db == &priv->ptp.hwd.spc1.rx_db) ? "RX" : "TX",
                             sysport,
                             iter_common->pkt_fields.seqid,
                             iter_common->pkt_fields.domain,
                             iter_common->pkt_fields.msg_type);

            list_del(&iter_common->list);
            db->gc_cb(iter_common);
            atomic64_inc(&priv->ptp.hwd.spc1.counters[db->direction][PTP_COUNTER_SPC1_GC_EVENTS]);
            atomic64_dec(&priv->ptp.hwd.spc1.counters[db->direction][
                             PTP_COUNTER_SPC1_PENDING_EVENTS]);
        } else {
            break; /* events are placed in the list in chronological order */
        }
    }

    list_for_each_entry_safe(iter_rec, tmp_rec, &db->sysport_records_list[sysport], list) {
        if (gc_all || time_after(now, iter_rec->since + PTP_GC_TIME)) {
            sx_int_log_error(&priv->ptp.log,
                             "GC (missing event): Record={dir=%s, port=%d, seq=%u, domain=%u, msg_type=%u}",
                             (db == &priv->ptp.hwd.spc1.rx_db) ? "RX" : "TX",
                             sysport,
                             be16_to_cpu(iter_rec->mtpptr.sequence_id),
                             iter_rec->mtpptr.domain_number,
                             iter_rec->mtpptr.message_type);

            list_del(&iter_rec->list);
            __ptp_free_record_data(iter_rec);
            atomic64_inc(&priv->ptp.hwd.spc1.counters[db->direction][PTP_COUNTER_SPC1_GC_RECORDS]);
            atomic64_dec(&priv->ptp.hwd.spc1.counters[db->direction][
                             PTP_COUNTER_SPC1_PENDING_RECORDS]);
        } else {
            break; /* records are placed in the list in chronological order */
        }
    }

    spin_unlock_bh(&db->sysport_lock[sysport]);
}


/* garbage collection for RX/TX events and records */
static void __gc(struct work_struct *work)
{
    struct delayed_work *dwork = to_delayed_work(work);
    struct sx_priv      *priv = container_of(dwork, struct sx_priv, ptp.hwd.spc1.gc_dwork);
    int                  sysport;

    for (sysport = 0; sysport < PTP_MAX_PORTS; sysport++) {
        __gc_db(priv, sysport, &priv->ptp.hwd.spc1.rx_db, false);
        __gc_db(priv, sysport, &priv->ptp.hwd.spc1.tx_db, false);
    }

    sx_clock_queue_delayed_work(&priv->ptp.hwd.spc1.gc_dwork, PTP_GC_TIME);
}


static void __ptp_event_handler_rx(struct sx_priv *priv, struct ptp_common_event_data *ced, u64 frc)
{
    struct ptp_rx_event_data *rx_event_data;

    rx_event_data = container_of(ced, struct ptp_rx_event_data, common);

    if (frc != 0) {
        sx_clock_fill_hwtstamp_spc1(priv, frc, skb_hwtstamps(rx_event_data->ci->skb));
    } else if (ced->need_timestamp) {
        sx_int_log_error(&priv->ptp.log,
                         "No matching timestamp: Event={dir=RX, port=%d, seq=%u, domain=%u, msg_type=%u}",
                         rx_event_data->ci->sysport,
                         ced->pkt_fields.seqid,
                         ced->pkt_fields.domain,
                         ced->pkt_fields.msg_type);

        atomic64_inc(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][PTP_COUNTER_SPC1_EMPTY_TS]);
    }

    dispatch_pkt(&priv->dev, rx_event_data->ci, rx_event_data->ci->hw_synd, 1);
    __ptp_free_rx_event_data(rx_event_data);
}


static void __ptp_gc_cb_rx(struct ptp_common_event_data *ced)
{
    struct ptp_rx_event_data *rx_event_data;

    rx_event_data = container_of(ced, struct ptp_rx_event_data, common);
    __ptp_free_rx_event_data(rx_event_data);
}


static void __ptp_event_handler_tx(struct sx_priv *priv, struct ptp_common_event_data *ced, u64 frc)
{
    struct ptp_tx_event_data   *tx_event_data;
    struct skb_shared_hwtstamps hwts, *p_hwts;

    tx_event_data = container_of(ced, struct ptp_tx_event_data, common);

    if (frc == 0) {
        sx_int_log_error(&priv->ptp.log,
                         "No matching timestamp: Event={dir=TX, seq=%u, domain=%u, msg_type=%u}",
                         ced->pkt_fields.seqid,
                         ced->pkt_fields.domain,
                         ced->pkt_fields.msg_type);

        p_hwts = NULL;
        atomic64_inc(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][PTP_COUNTER_SPC1_EMPTY_TS]);
    } else {
        p_hwts = &hwts;
        sx_clock_fill_hwtstamp_spc1(priv, frc, p_hwts);
    }

    skb_tstamp_tx(tx_event_data->skb, p_hwts);
    __ptp_free_tx_event_data(tx_event_data);
}


static void __ptp_gc_cb_tx(struct ptp_common_event_data *ced)
{
    struct ptp_tx_event_data *tx_event_data;

    tx_event_data = container_of(ced, struct ptp_tx_event_data, common);
    __ptp_free_tx_event_data(tx_event_data);
}


static void __ptp_dequeue_general_messages(struct sx_priv *priv, u16 local_port, struct ptp_db *db)
{
    struct ptp_common_event_data *ced, *tmp;

    list_for_each_entry_safe(ced, tmp, &db->sysport_events_list[local_port], list) {
        if (ced->need_timestamp) {
            break;
        }

        list_del(&ced->list);
        atomic64_dec(&priv->ptp.hwd.spc1.counters[db->direction][PTP_COUNTER_SPC1_PENDING_EVENTS]);
        db->handle_cb(priv, ced, 0);
    }
}


static u8 __is_match(const struct sx_ptp_packet_fields *pkt_fields, const struct mtpptr_record *record)
{
    return ((record->domain_number == pkt_fields->domain) &&
            (record->message_type == pkt_fields->msg_type) &&
            (be16_to_cpu(record->sequence_id) == pkt_fields->seqid));
}


static unsigned long __event_and_record_time_diff(struct sx_priv *priv,
                                                  u8              direction,
                                                  unsigned long   event_time,
                                                  unsigned long   record_time)
{
    unsigned long diff = (event_time >= record_time) ?
                         event_time - record_time :
                         record_time - event_time;

    if (diff > priv->ptp.hwd.spc1.max_diff[direction]) {
        priv->ptp.hwd.spc1.max_diff[direction] = diff;
        priv->ptp.hwd.spc1.max_diff_ts[direction] = jiffies;
    }

    return diff;
}


static u8 __match_record_with_event(struct sx_priv             *priv,
                                    const struct mtpptr_record *record,
                                    u16                         local_port,
                                    struct ptp_db              *db,
                                    unsigned long               record_time)
{
    struct ptp_common_event_data *ced, *found = NULL;
    unsigned long                 diff;
    u64                           frc;

    list_for_each_entry(ced, &db->sysport_events_list[local_port], list) {
        if (ced->need_timestamp && __is_match(&ced->pkt_fields, record)) {
            found = ced;
            break;
        }
    }

    if (!found) {
        return 0;
    }

    do {
        ced = list_entry(db->sysport_events_list[local_port].next, struct ptp_common_event_data, list);

        if (ced == found) {
            diff = __event_and_record_time_diff(priv, db->direction, ced->since, record_time);
            frc = be64_to_cpu(record->timestamp);

            SX_CLOCK_ACTIVITY_LOG(priv,
                                  SX_INTERNAL_LOG_SEVERITY_INFO_E,
                                  "%s MATCH [port=%u, seq=%u, domain=%u, msg_type=%u, "
                                  "pkt_jiffies=%lu, rec_jiffies=%lu, diff_msec=%u, frc=%llu]",
                                  (db == &priv->ptp.hwd.spc1.rx_db) ? "RX" : "TX",
                                  local_port,
                                  ced->pkt_fields.seqid,
                                  ced->pkt_fields.domain,
                                  ced->pkt_fields.msg_type,
                                  ced->since,
                                  record_time,
                                  jiffies_to_msecs(diff),
                                  frc);
        } else {
            frc = 0;
        }

        list_del(&ced->list);
        atomic64_dec(&priv->ptp.hwd.spc1.counters[db->direction][PTP_COUNTER_SPC1_PENDING_EVENTS]);
        db->handle_cb(priv, ced, frc);
    } while (ced != found);

    return 1;
}


static void __ptp_lookup_event(struct sx_priv *priv, const u8 *mtpptr_buff, struct ptp_db *db)
{
    const struct mtpptr_record *record;
    struct ptp_record          *to_cache;
    unsigned long               now = jiffies;
    u16                         local_port;
    u8                          ovf;
    u8                          num_rec;
    u8                          found;
    int                         i;

    local_port = mtpptr_buff[1];
    ovf = !!mtpptr_buff[7];
    num_rec = mtpptr_buff[11];
    record = (struct mtpptr_record*)&mtpptr_buff[16];

    if (ovf) {
        sx_int_log_error(&priv->ptp.log,
                         "FIFO overflow: dir=%s, port=%u",
                         (db == &priv->ptp.hwd.spc1.rx_db) ? "RX" : "TX",
                         local_port);

        atomic64_inc(&priv->ptp.hwd.spc1.counters[db->direction][PTP_COUNTER_SPC1_FIFO_OVERFLOW]);
    }

    if (num_rec <= PTP_MAX_RECORDS) {
        atomic64_inc(&priv->ptp.hwd.spc1.records_dist[db->direction][num_rec]);
    }

    if (num_rec == 0) {
        return;
    }

    spin_lock_bh(&db->sysport_lock[local_port]);

    /* try to find matches for current records and save records that has no matched event */
    for (i = 0; i < num_rec; i++) {
        SX_CLOCK_ACTIVITY_LOG(priv,
                              SX_INTERNAL_LOG_SEVERITY_INFO_E,
                              "%s record [port=%u, seq=%u, domain=%u, msg_type=%u, frc=%llu]",
                              (db == &priv->ptp.hwd.spc1.rx_db) ? "RX" : "TX",
                              local_port,
                              be16_to_cpu(record[i].sequence_id),
                              record[i].domain_number,
                              record[i].message_type,
                              be64_to_cpu(record[i].timestamp));

        found = __match_record_with_event(priv,
                                          &record[i],
                                          local_port,
                                          db,
                                          now);

        if (!found) {
            atomic64_inc(&priv->ptp.hwd.spc1.counters[db->direction][
                             PTP_COUNTER_SPC1_RECORD_ARRIVED_FIRST]);

            to_cache = __ptp_allocate_record_data(GFP_ATOMIC, &record[i]);
            if (!to_cache) {
                sx_int_log_error(&priv->ptp.log,
                                 "Allocation of records failed: dir=%s, port=%u",
                                 (db == &priv->ptp.hwd.spc1.rx_db) ? "RX" : "TX",
                                 local_port);

                atomic64_inc(&priv->ptp.hwd.spc1.counters[db->direction][
                                 PTP_COUNTER_SPC1_OUT_OF_MEMORY]);
            } else {
                list_add_tail(&to_cache->list, &db->sysport_records_list[local_port]);
                atomic64_inc(&priv->ptp.hwd.spc1.counters[db->direction][
                                 PTP_COUNTER_SPC1_PENDING_RECORDS]);
            }
        }
    }

    __ptp_dequeue_general_messages(priv, local_port, db);

    spin_unlock_bh(&db->sysport_lock[local_port]);
}


static u8 __match_event_with_record_rx(struct sx_priv *priv, struct ptp_rx_event_data *rx_event, u16 local_port)
{
    struct ptp_record *rec = NULL;
    unsigned long      diff;
    u64                frc;
    u8                 found = 0;

    list_for_each_entry(rec, &priv->ptp.hwd.spc1.rx_db.sysport_records_list[local_port], list) {
        if (__is_match(&rx_event->common.pkt_fields, &rec->mtpptr)) {
            found = 1;
            break;
        }
    }

    if (!found) {
        return 0;
    }

    diff = __event_and_record_time_diff(priv, PTP_PACKET_INGRESS, jiffies, rec->since);
    frc = be64_to_cpu(rec->mtpptr.timestamp);

    SX_CLOCK_ACTIVITY_LOG(priv,
                          SX_INTERNAL_LOG_SEVERITY_INFO_E,
                          "RX MATCH [port=%u, seq=%u, domain=%u, msg_type=%u, "
                          "pkt_jiffies=%lu, rec_jiffies=%lu, diff_msec=%u, frc=%llu]",
                          local_port,
                          rx_event->common.pkt_fields.seqid,
                          rx_event->common.pkt_fields.domain,
                          rx_event->common.pkt_fields.msg_type,
                          jiffies,
                          rec->since,
                          jiffies_to_msecs(diff),
                          frc);

    list_del(&rec->list);
    __ptp_free_record_data(rec);

    atomic64_dec(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][PTP_COUNTER_SPC1_PENDING_RECORDS]);
    priv->ptp.hwd.spc1.rx_db.handle_cb(priv, &rx_event->common, frc);
    return 1;
}


static void __delete_caches(void)
{
    if (__records_cache) {
        kmem_cache_destroy(__records_cache);
    }

    if (__tx_event_cache) {
        kmem_cache_destroy(__tx_event_cache);
    }

    if (__rx_event_cache) {
        kmem_cache_destroy(__rx_event_cache);
    }
}


static int __create_caches(void)
{
    __records_cache = kmem_cache_create("ptp_record", sizeof(struct ptp_record), 0, 0, NULL);
    if (!__records_cache) {
        printk(KERN_ERR "failed to allocate memory cache for PTP TX events\n");
        goto error;
    }

    __tx_event_cache = kmem_cache_create("ptp_tx_event_data", sizeof(struct ptp_tx_event_data), 0, 0, NULL);
    if (!__tx_event_cache) {
        printk(KERN_ERR "failed to allocate memory cache for PTP TX events\n");
        goto error;
    }

    __rx_event_cache = kmem_cache_create("ptp_rx_event_data", sizeof(struct ptp_rx_event_data), 0, 0, NULL);
    if (!__rx_event_cache) {
        printk(KERN_ERR "failed to allocate memory cache for PTP RX events\n");
        goto error;
    }

    return 0;

error:
    __delete_caches();
    return -ENOMEM;
}

static bool __rx_polling_dev_iterator(struct sx_dev *dev, void *context)
{
    struct sx_priv             *priv = sx_priv(dev);
    struct ku_access_mtpptr_reg ku_mtpptr;
    int                         local_port;
    int                         err;
    u8                          has_events;

    if (sx_ptp_get_mode(priv) != KU_PTP_MODE_POLLING) {
        goto out;
    }

    for (local_port = 0; local_port < PTP_MAX_PORTS; local_port++) {
        spin_lock_bh(&priv->ptp.hwd.spc1.rx_db.sysport_lock[local_port]);
        has_events = !list_empty(&priv->ptp.hwd.spc1.rx_db.sysport_events_list[local_port]);
        spin_unlock_bh(&priv->ptp.hwd.spc1.rx_db.sysport_lock[local_port]);

        if (!has_events) {
            continue;
        }

        memset(&ku_mtpptr, 0, sizeof(ku_mtpptr));

        ku_mtpptr.dev_id = dev->device_id;
        sx_cmd_set_op_tlv(&ku_mtpptr.op_tlv, MTPPTR_REG_ID, 1);
        ku_mtpptr.mtpptr_reg.clr = 1;
        ku_mtpptr.mtpptr_reg.dir = PTP_PACKET_INGRESS;

        SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(ku_mtpptr.mtpptr_reg.local_port,
                                            ku_mtpptr.mtpptr_reg.lp_msb,
                                            local_port);

        err = sx_ACCESS_REG_MTPPTR(dev, &ku_mtpptr, 0);
        if (err) {
            sx_int_log_error(&priv->ptp.log,
                             "FIFO polling failed: dir=RX, port=%d", local_port);

            atomic64_inc(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                             PTP_COUNTER_SPC1_REG_ACCESS_FAILED]);
        } else {
            atomic64_inc(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                             PTP_COUNTER_SPC1_REG_ACCESS_SUCCEEDED]);
            __ptp_lookup_event(priv, (u8*)&ku_mtpptr.mtpptr_reg, &priv->ptp.hwd.spc1.rx_db);
        }
    }

out:
    return true;
}

static int __sx_clock_rx_polling_thread(void *data)
{
    int err = 0;

    while (!kthread_should_stop()) {
        err = down_timeout(&__ptp_polling_sem, 1 * HZ);
        if (err == -ETIME) { /* return to wait */
            continue;
        }

        sx_dev_db_iterate(__rx_polling_dev_iterator, NULL);
    }

    return 0;
}


static void __init_db(struct ptp_db *db, u8 direction, ptp_db_handle_cb_t handle_cb, ptp_db_gc_cb_t gc_cb)
{
    int i;

    db->handle_cb = handle_cb;
    db->gc_cb = gc_cb;
    db->direction = direction;

    for (i = 0; i < PTP_MAX_PORTS; i++) {
        spin_lock_init(&db->sysport_lock[i]);
        INIT_LIST_HEAD(&db->sysport_events_list[i]);
        INIT_LIST_HEAD(&db->sysport_records_list[i]);
    }
}


static void __dump_db(struct seq_file *m, const char *title, struct ptp_db *db)
{
    struct ptp_common_event_data *iter_common, *tmp_common;
    struct ptp_record            *iter_rec, *tmp_rec;
    unsigned long                 now = jiffies;
    int                           sysport;

    seq_printf(m, "\n\n");

    seq_printf(m, "%s\n", title);
    seq_printf(m, "=================================\n");

    for (sysport = 0; sysport < PTP_MAX_PORTS; sysport++) {
        spin_lock_bh(&db->sysport_lock[sysport]);

        if (!list_empty(&db->sysport_events_list[sysport]) || !list_empty(&db->sysport_records_list[sysport])) {
            seq_printf(m, "System Port: %d\n", sysport);
            seq_printf(m, "---------------\n");

            list_for_each_entry_safe(iter_common, tmp_common, &db->sysport_events_list[sysport], list) {
                seq_printf(m, "    EVENT   Seq:%5u  Type:%3u  Domain:%3u  Need_TS:%u  Msec_Ago:%lu\n",
                           iter_common->pkt_fields.seqid,
                           iter_common->pkt_fields.msg_type,
                           iter_common->pkt_fields.domain,
                           iter_common->need_timestamp,
                           ((now - iter_common->since) * 1000) / HZ);
            }

            list_for_each_entry_safe(iter_rec, tmp_rec, &db->sysport_records_list[sysport], list) {
                seq_printf(m, "    RECORD  Seq:%5u  Type:%3u  Domain:%3u  FRC=%llu  Msec_Ago:%lu\n",
                           be16_to_cpu(iter_rec->mtpptr.sequence_id),
                           iter_rec->mtpptr.message_type,
                           iter_rec->mtpptr.domain_number,
                           be64_to_cpu(iter_rec->mtpptr.timestamp),
                           ((now - iter_rec->since) * 1000) / HZ);
            }
        }

        spin_unlock_bh(&db->sysport_lock[sysport]);
    }
}


int sx_ptp_dev_init_spc1(struct sx_priv *priv, ptp_mode_t ptp_mode)
{
    struct ku_access_mogcr_reg  mogcr_reg_data;
    struct ku_access_mtpppc_reg mtpppc_reg_data;
    struct sx_dev              *dev = &priv->dev;
    int                         i, err;

    if ((ptp_mode != KU_PTP_MODE_POLLING) &&
        (ptp_mode != KU_PTP_MODE_EVENTS)) {
        printk(KERN_ERR "invalid PTP mode for SPC: %u\n", ptp_mode);
        return -EINVAL;
    }

    memset(&mogcr_reg_data, 0, sizeof(mogcr_reg_data));
    mogcr_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mogcr_reg_data.op_tlv, MLXSW_MOGCR_ID, 2);
    mogcr_reg_data.mogcr_reg.ptp_iftc = 1; /* always clear after read */
    mogcr_reg_data.mogcr_reg.ptp_eftc = 1; /* always clear after read */
    err = sx_ACCESS_REG_MOGCR(dev, &mogcr_reg_data);
    if (err) {
        printk(KERN_ERR "Failed to configure register MOGCR\n");
        goto out;
    }

    memset(&mtpppc_reg_data, 0, sizeof(mtpppc_reg_data));
    mtpppc_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mtpppc_reg_data.op_tlv, MTPPPC_REG_ID, 2);
    mtpppc_reg_data.mtpppc_reg.egr_timestape_message_type = PTP_MSG_SYNC |
                                                            PTP_MSG_DELAY_REQ | PTP_MSG_PDELAY_REQ |
                                                            PTP_MSG_PDELAY_RESP;
    mtpppc_reg_data.mtpppc_reg.ing_timestape_message_type = PTP_MSG_SYNC |
                                                            PTP_MSG_DELAY_REQ | PTP_MSG_PDELAY_REQ |
                                                            PTP_MSG_PDELAY_RESP;
    err = sx_ACCESS_REG_MTPPPC(dev, &mtpppc_reg_data);
    if (err) {
        sx_err(dev, "Failed to configure register mtpppc.\n");
        goto out;
    }

    sema_init(&__ptp_polling_sem, 0);

    err = __create_caches();
    if (err) {
        goto out;
    }

    __init_db(&priv->ptp.hwd.spc1.rx_db, PTP_PACKET_INGRESS, __ptp_event_handler_rx,
              __ptp_gc_cb_rx);
    __init_db(&priv->ptp.hwd.spc1.tx_db, PTP_PACKET_EGRESS, __ptp_event_handler_tx,
              __ptp_gc_cb_tx);

    if (ptp_mode == KU_PTP_MODE_POLLING) {
        if (atomic_inc_return(&__ptp_rx_polling_thread_users) == 1) { /* first one here */
            __ptp_rx_polling_thread = kthread_run(__sx_clock_rx_polling_thread, NULL, "ptp_rx_polling");
            if (IS_ERR(__ptp_rx_polling_thread)) {
                atomic_dec(&__ptp_rx_polling_thread_users);
                err = PTR_ERR(__ptp_rx_polling_thread);
                printk(KERN_ERR "failed to create PTP RX polling thread (err=%d)\n", err);
                goto polling_thread_failed;
            }
        }
    }

    for (i = 0; i < PTP_COUNTER_SPC1_LAST; i++) {
        atomic64_set(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][i], 0);
        atomic64_set(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][i], 0);
    }

    INIT_DELAYED_WORK(&priv->ptp.hwd.spc1.gc_dwork, __gc);
    sx_clock_queue_delayed_work(&priv->ptp.hwd.spc1.gc_dwork, 0);
    return 0;

polling_thread_failed:
    __delete_caches();

out:
    return err;
}


int sx_ptp_dev_cleanup_spc1(struct sx_priv *priv)
{
    int sysport;

    cancel_delayed_work_sync(&priv->ptp.hwd.spc1.gc_dwork);

    if (sx_ptp_get_mode(priv) == KU_PTP_MODE_POLLING) {
        if (atomic_dec_and_test(&__ptp_rx_polling_thread_users)) { /* last one here */
            kthread_stop(__ptp_rx_polling_thread);
            __ptp_rx_polling_thread = NULL;
        }
    }

    for (sysport = 0; sysport < PTP_MAX_PORTS; sysport++) {
        __gc_db(priv, sysport, &priv->ptp.hwd.spc1.rx_db, true);
        __gc_db(priv, sysport, &priv->ptp.hwd.spc1.tx_db, true);
    }

    __delete_caches();

    return 0;
}


int sx_ptp_rx_handler_spc1(struct sx_priv                      *priv,
                           struct completion_info              *ci,
                           ptp_mode_t                           ptp_mode,
                           const struct sx_ptp_packet_metadata *pkt_meta)
{
    struct ptp_rx_event_data *rx_ptp_event;
    u8                        found = 0;

    if (ci->hw_synd == SXD_TRAP_ID_PTP_ING_EVENT) {
        atomic64_inc(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][PTP_COUNTER_SPC1_FIFO_TRAP]);
        if (ptp_mode == KU_PTP_MODE_EVENTS) {
            __ptp_lookup_event(priv, ci->skb->data + MTPPTR_OFFSET, &priv->ptp.hwd.spc1.rx_db);
        }

        sx_skb_consume(ci->skb);   /* free unused packet */
        goto free_ci;
    }

    if (ci->hw_synd == SXD_TRAP_ID_PTP_EGR_EVENT) {
        atomic64_inc(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][PTP_COUNTER_SPC1_FIFO_TRAP]);
        __ptp_lookup_event(priv, ci->skb->data + MTPPTR_OFFSET, &priv->ptp.hwd.spc1.tx_db);

        sx_skb_consume(ci->skb);   /* free unused packet */
        goto free_ci;
    }

    /* if we get here, the trap must be PTP0, PTP1 or LLDP */
    rx_ptp_event = __ptp_allocate_rx_event_data(GFP_ATOMIC, ci, pkt_meta);
    if (!rx_ptp_event) {
        sx_int_log_error(&priv->ptp.log,
                         "Allocation of event failed: dir=RX, port=%u",
                         pkt_meta->sysport_lag_id);

        atomic64_inc(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                         PTP_COUNTER_SPC1_OUT_OF_MEMORY]);
        sx_skb_free(ci->skb);   /* drop packet flow, use kfree_skb */
        goto free_ci;
    }

    SX_CLOCK_ACTIVITY_LOG(priv,
                          SX_INTERNAL_LOG_SEVERITY_INFO_E,
                          "RX packet [port=%u, seq=%u, domain=%u, msg_type=%u, ts_required=%u]",
                          pkt_meta->sysport_lag_id,
                          pkt_meta->pkt_fields.seqid,
                          pkt_meta->pkt_fields.domain,
                          pkt_meta->pkt_fields.msg_type,
                          pkt_meta->timestamp_required);

    spin_lock_bh(&priv->ptp.hwd.spc1.rx_db.sysport_lock[pkt_meta->sysport_lag_id]);

    if (pkt_meta->timestamp_required && (ptp_mode == KU_PTP_MODE_EVENTS)) {
        found = __match_event_with_record_rx(priv, rx_ptp_event, pkt_meta->sysport_lag_id);
    }

    if (!found) {
        list_add_tail(&rx_ptp_event->common.list,
                      &priv->ptp.hwd.spc1.rx_db.sysport_events_list[pkt_meta->sysport_lag_id]);
        atomic64_inc(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                         PTP_COUNTER_SPC1_PENDING_EVENTS]);

        if (!pkt_meta->timestamp_required) {
            __ptp_dequeue_general_messages(priv,
                                           pkt_meta->sysport_lag_id,
                                           &priv->ptp.hwd.spc1.rx_db);
        } else if (sx_ptp_get_mode(priv) == KU_PTP_MODE_POLLING) {
            up(&__ptp_polling_sem);
        } else {
            atomic64_inc(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                             PTP_COUNTER_SPC1_EVENT_ARRIVED_FIRST]);
        }
    }

    spin_unlock_bh(&priv->ptp.hwd.spc1.rx_db.sysport_lock[pkt_meta->sysport_lag_id]);
    goto out;

free_ci:
    kfree(ci);

out:
    return 0;
}


int sx_ptp_tx_handler_spc1(struct sx_priv *priv, struct sk_buff *skb, const struct sx_ptp_packet_metadata *pkt_meta)
{
    struct ptp_tx_event_data *ptp_event;
    unsigned long             flags;

    ptp_event = __ptp_allocate_tx_event_data(GFP_ATOMIC, skb, pkt_meta);
    if (!ptp_event) {
        sx_int_log_error(&priv->ptp.log,
                         "Allocation of event failed: dir=TX, port=%u",
                         pkt_meta->sysport_lag_id);

        atomic64_inc(
            &priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][PTP_COUNTER_SPC1_OUT_OF_MEMORY]);
        return -ENOMEM;
    }

    /* on TX, packet always comes before the timestamp */
    atomic64_inc(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][
                     PTP_COUNTER_SPC1_EVENT_ARRIVED_FIRST]);

    SX_CLOCK_ACTIVITY_LOG(priv,
                          SX_INTERNAL_LOG_SEVERITY_INFO_E,
                          "TX packet [port=%u, seq=%u, domain=%u, msg_type=%u, ts_required=1]",
                          pkt_meta->sysport_lag_id,
                          pkt_meta->pkt_fields.seqid,
                          pkt_meta->pkt_fields.domain,
                          pkt_meta->pkt_fields.msg_type);

    spin_lock_irqsave(&priv->ptp.hwd.spc1.tx_db.sysport_lock[pkt_meta->sysport_lag_id], flags);
    list_add_tail(&ptp_event->common.list,
                  &priv->ptp.hwd.spc1.tx_db.sysport_events_list[pkt_meta->sysport_lag_id]);
    atomic64_inc(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][PTP_COUNTER_SPC1_PENDING_EVENTS]);
    spin_unlock_irqrestore(&priv->ptp.hwd.spc1.tx_db.sysport_lock[pkt_meta->sysport_lag_id],
                           flags);
    return 0;
}

int sx_ptp_get_supported_tx_types_spc1(struct sx_priv *priv, u32 *tx_types)
{
    *tx_types = BIT(1) << HWTSTAMP_TX_ON;
    return 0;
}

int sx_ptp_set_tx_type_spc1(struct sx_priv *priv, int tx_type)
{
    int err = 0;

    switch (tx_type) {
    case HWTSTAMP_TX_OFF:
    case HWTSTAMP_TX_ON: /* 2-Step PTP boundary clock */
        break;

    default:
        err = -ERANGE;
    }

    return err;
}

int sx_ptp_dump_spc1(struct sx_priv *priv, struct seq_file *m, void *v, void *context)
{
    unsigned long now = jiffies;
    char          str_rx[40], str_tx[40];
    char          section[40];
    int           i;

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "FIFO traps",
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_SPC1_FIFO_TRAP]),
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC1_FIFO_TRAP]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Events removed by GC",
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_SPC1_GC_EVENTS]),
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC1_GC_EVENTS]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Records removed by GC",
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_SPC1_GC_RECORDS]),
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC1_GC_RECORDS]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "HW FIFO overflow",
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_SPC1_FIFO_OVERFLOW]),
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC1_FIFO_OVERFLOW]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "FW polling succeeded",
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_SPC1_REG_ACCESS_SUCCEEDED]),
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC1_REG_ACCESS_SUCCEEDED]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "FW polling failed",
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_SPC1_REG_ACCESS_FAILED]),
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC1_REG_ACCESS_FAILED]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "No matching timestamp",
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_SPC1_EMPTY_TS]),
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC1_EMPTY_TS]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Dropped - Out of memory",
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_SPC1_OUT_OF_MEMORY]),
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC1_OUT_OF_MEMORY]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Pending packets",
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_SPC1_PENDING_EVENTS]),
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC1_PENDING_EVENTS]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Pending records",
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_SPC1_PENDING_RECORDS]),
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC1_PENDING_RECORDS]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Event arrived before record",
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_SPC1_EVENT_ARRIVED_FIRST]),
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC1_EVENT_ARRIVED_FIRST]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Record arrived before event",
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_INGRESS][
                                      PTP_COUNTER_SPC1_RECORD_ARRIVED_FIRST]),
               (u64)atomic64_read(&priv->ptp.hwd.spc1.counters[PTP_PACKET_EGRESS][
                                      PTP_COUNTER_SPC1_RECORD_ARRIVED_FIRST]));

    seq_printf(m, "%-40s   %-15u   %-15u\n",
               "Max diff (msec) between record and event",
               jiffies_to_msecs(priv->ptp.hwd.spc1.max_diff[PTP_PACKET_INGRESS]),
               jiffies_to_msecs(priv->ptp.hwd.spc1.max_diff[PTP_PACKET_EGRESS]));

    if (priv->ptp.hwd.spc1.max_diff_ts[PTP_PACKET_INGRESS] != 0) {
        snprintf(str_rx, sizeof(str_rx), "%u",
                 jiffies_to_msecs(now - priv->ptp.hwd.spc1.max_diff_ts[PTP_PACKET_INGRESS]) / 1000);
    } else {
        snprintf(str_rx, sizeof(str_rx), "N/A");
    }

    if (priv->ptp.hwd.spc1.max_diff_ts[PTP_PACKET_EGRESS] != 0) {
        snprintf(str_tx,
                 sizeof(str_tx),
                 "%u",
                 jiffies_to_msecs(now - priv->ptp.hwd.spc1.max_diff_ts[PTP_PACKET_EGRESS]) / 1000);
    } else {
        snprintf(str_tx, sizeof(str_tx), "N/A");
    }

    seq_printf(m, "%-40s   %-15s   %-15s\n",
               "Timestamp (sec ago) of max diff",
               str_rx,
               str_tx);

    seq_printf(m, "\n");

    for (i = 0; i <= PTP_MAX_RECORDS; i++) {
        sprintf(section, "%d-records polling/traps", i);
        seq_printf(m, "%-40s   %-15llu   %-15llu\n",
                   section,
                   (u64)atomic64_read(&priv->ptp.hwd.spc1.records_dist[PTP_PACKET_INGRESS][i]),
                   (u64)atomic64_read(&priv->ptp.hwd.spc1.records_dist[PTP_PACKET_EGRESS][i]));
    }

    seq_printf(m, "\n");

    __dump_db(m, "RX Database", &priv->ptp.hwd.spc1.rx_db);
    __dump_db(m, "TX Database", &priv->ptp.hwd.spc1.tx_db);

    seq_printf(m, "\n");

    sx_internal_log_dump(&priv->ptp.log, m);

    return 0;
}
