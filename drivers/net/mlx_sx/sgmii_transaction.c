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

#include <linux/time.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/driver.h>

#include "sgmii_internal.h"
#include "map.h"

struct sgmii_transaction_entry {
    struct sx_core_map_info      map_info;
    struct sgmii_transaction_db *tr_db;
    sgmii_transaction_id_t       tr_id;
    int                          completed;
    int                          attempts_total;
    int                          attempts_so_far;
    struct sgmii_dev            *sgmii_dev;
    struct sk_buff              *skb;
    int                          meta_is_valid;
    struct isx_meta              meta;
    void                        *context;
    int                          interval;
};
static int __sgmii_transaction_compare_cb(const void* key1, const void *key2)
{
    const sgmii_transaction_id_t tr_id1 = *(sgmii_transaction_id_t*)key1;
    const sgmii_transaction_id_t tr_id2 = *(sgmii_transaction_id_t*)key2;

    if (tr_id1 > tr_id2) {
        return 1;
    }

    if (tr_id1 < tr_id2) {
        return -1;
    }

    return 0;
}


static void __sgmii_transaction_complete(struct sk_buff                          *rx_skb,
                                         struct sgmii_transaction_entry          *entry,
                                         enum sgmii_transaction_completion_status status,
                                         struct sgmii_dev                        *rx_dev)
{
    struct sgmii_transaction_info tr_info;
    struct sgmii_transaction_db  *tr_db = entry->tr_db;

    tr_info.tr_db = tr_db;
    tr_info.tr_id = entry->tr_id;
    tr_info.orig_tx_dev = entry->sgmii_dev;
    tr_info.rx_dev = rx_dev;
    tr_info.send_attempts_so_far = entry->attempts_so_far;

    /* free original skb so it will activate its destructor (just like with PCI) */
    sx_skb_free(entry->skb);

    tr_db->transaction_completion_cb(rx_skb, status, &tr_info, entry->context);
    sgmii_dev_dec_ref(entry->sgmii_dev);
}


static void __sgmii_transaction_task(void *task_param)
{
    struct sgmii_transaction_info   tr_info;
    struct sgmii_transaction_entry *entry;
    struct sgmii_transaction_db    *tr_db;
    int                             err;

    memcpy(&entry, task_param, sizeof(entry)); /* copy the entry pointer itself */
    tr_db = entry->tr_db;

    spin_lock_bh(&tr_db->db_lock);

    if (entry->completed) {
        kfree(entry);
        goto out;
    }

    if (entry->attempts_total == entry->attempts_so_far) {
        sx_core_map_remove(&tr_db->db_map, &entry->tr_id, NULL);

        __sgmii_transaction_complete(NULL, entry, SGMII_TR_COMP_ST_TIMEDOUT, NULL);
        kfree(entry);
        goto out;
    }

    tr_info.tr_db = entry->tr_db;
    tr_info.tr_id = entry->tr_id;
    tr_info.orig_tx_dev = entry->sgmii_dev;
    tr_info.rx_dev = NULL;

    err = sgmii_send(entry->sgmii_dev,
                     entry->skb,
                     entry->meta_is_valid ? &entry->meta : NULL,
                     SGMII_PCP_HIGH,
                     tr_db->fill_control_segment_cb,
                     tr_db->fill_tx_base_header_cb);

    entry->attempts_so_far++;
    tr_info.send_attempts_so_far = entry->attempts_so_far;

    tr_db->entry_handler_cb(err, &tr_info, entry->context);

    sgmii_queue_task(__sgmii_transaction_task,
                     &entry, sizeof(entry), /* yes, sizeof pointer! */
                     msecs_to_jiffies(entry->interval));

out:
    spin_unlock_bh(&tr_db->db_lock);
}


int sgmii_transaction_check_completion(struct sgmii_transaction_db *tr_db,
                                       struct sk_buff              *rx_skb,
                                       sgmii_transaction_id_t       tr_id,
                                       struct sgmii_dev            *rx_dev)
{
    struct sx_core_map_info                 *map_info;
    struct sgmii_transaction_entry          *entry;
    enum sgmii_transaction_completion_status st;
    unsigned long                            flags;
    int                                      ret;

    /* we are called from dispatch_pkt() which holds a spinlock with IRQ off. we must keep this line ... */
    spin_lock_irqsave(&tr_db->db_lock, flags);

    ret = sx_core_map_remove(&tr_db->db_map, &tr_id, &map_info);
    if (ret) { /* transaction not found */
        spin_unlock_irqrestore(&tr_db->db_lock, flags);
        return 0;
    }

    /* if we get here, the transaction was in the map - so we know that the entry is scheduled
     * for retransmission by __sgmii_transaction_task(). the entry will not be deallocated here.
     * it will be marked as 'completed' and the worker thread will delete it eventually.
     */
    entry = container_of(map_info, struct sgmii_transaction_entry, map_info);

    st = (entry->sgmii_dev == rx_dev) ? SGMII_TR_COMP_ST_COMPLETED :
         SGMII_TR_COMP_ST_RX_DEV_MISMATCH;

    __sgmii_transaction_complete(rx_skb, entry, st, rx_dev);
    entry->completed = 1;

    spin_unlock_irqrestore(&tr_db->db_lock, flags);
    return 1;
}


int sgmii_send_transaction(struct sgmii_transaction_meta *tr_meta,
                           struct sgmii_dev              *sgmii_dev,
                           const struct isx_meta         *isx_meta,
                           void                          *context)
{
    struct sgmii_transaction_entry *entry, *existing_entry;
    struct sx_core_map_info        *existing_info;
    int                             ret = -ENOMEM;
    int                             max_attempts = 1;
    int                             interval = 100;

    entry = kmalloc(sizeof(struct sgmii_transaction_entry), GFP_ATOMIC);
    if (!entry) {
        goto free_orig_skb;
    }

    max_attempts = sgmii_get_send_attempts_by_transport(tr_meta->transport_type);
    interval = sgmii_get_send_interval_msec_by_transport(tr_meta->transport_type);

    entry->tr_db = tr_meta->tr_db;
    entry->tr_id = tr_meta->tr_id;
    entry->completed = 0;
    entry->attempts_total = max_attempts;
    entry->attempts_so_far = 0;
    entry->sgmii_dev = sgmii_dev;
    entry->skb = tr_meta->skb;
    entry->interval = interval;

    entry->meta_is_valid = (isx_meta != NULL);
    if (entry->meta_is_valid) {
        memcpy(&entry->meta, isx_meta, sizeof(entry->meta));
    }

    entry->context = context;

    spin_lock_bh(&tr_meta->tr_db->db_lock);

    ret = sx_core_map_lookup(&tr_meta->tr_db->db_map, &entry->tr_id, &existing_info);
    if (ret == 0) { /* joining an existing transaction */
        existing_entry = container_of(existing_info, struct sgmii_transaction_entry, map_info);
        existing_entry->attempts_total = max_attempts;
        ret = -EINPROGRESS;
        goto out;
    }

    ret = sx_core_map_insert(&tr_meta->tr_db->db_map, &entry->tr_id, &entry->map_info, GFP_ATOMIC);
    if (ret) {
        goto out;
    }

    sgmii_dev_inc_ref(sgmii_dev);
    sgmii_queue_task(__sgmii_transaction_task, &entry, sizeof(entry) /* yes, sizeof pointer! */, 0);

    spin_unlock_bh(&tr_meta->tr_db->db_lock);

    return 0;

out:
    spin_unlock_bh(&tr_meta->tr_db->db_lock);

    if (entry) {
        kfree(entry);
    }

free_orig_skb:

    /* no matter what, we free original skb so it will activate its destructor (just like with PCI) */
    sx_skb_free(tr_meta->skb);

    return ret;
}


int sgmii_send_transaction_sync(int                            dev_id,
                                struct sk_buff                *skb,
                                const struct isx_meta         *meta,
                                sgmii_transaction_sync_send_cb send_cb,
                                struct sk_buff               **rx_skb)
{
    struct sgmii_sync_transaction_context context;
    int                                   err;

    init_completion(&context.completion);
    err = send_cb(dev_id, skb, meta, &context); /* callback fills 'context.tr_db' and 'context.tr_id' */
    if (err) {
        return err;
    }

    do {
        err = wait_for_completion_interruptible(&context.completion);
    } while (err == -ERESTARTSYS);

    switch (context.status) {
    case SGMII_TR_COMP_ST_COMPLETED:
        err = 0;
        if (rx_skb) {
            *rx_skb = context.rx_skb;
        }
        break;

    case SGMII_TR_COMP_ST_RX_DEV_MISMATCH:
        err = -ENODEV;
        break;

    case SGMII_TR_COMP_ST_TIMEDOUT:
        err = -ETIMEDOUT;
        break;

    default:
        err = -EIO;
        break;
    }

    return err;
}


void sgmii_sync_transaction_complete(struct sgmii_sync_transaction_context   *context,
                                     struct sk_buff                          *rx_skb,
                                     enum sgmii_transaction_completion_status status)
{
    context->rx_skb = rx_skb ? skb_copy(rx_skb, GFP_ATOMIC) : NULL;
    context->status = status;
    complete(&context->completion);
}


int sgmii_transaction_db_init(struct sgmii_transaction_db       *tr_db,
                              sgmii_fill_control_segment_cb_t    fill_control_segment_cb,
                              sgmii_fill_tx_base_header_cb_t     fill_tx_base_header_cb,
                              sgmii_transaction_entry_handler_cb entry_handler_cb,
                              sgmii_transaction_completion_cb_t  transaction_completion_cb)
{
    int ret;

    if (!tr_db || !transaction_completion_cb) {
        printk(KERN_ERR "failed to initialize SGMII transaction database - invalid argument\n");
        return -EINVAL;
    }

    ret = sx_core_map_init(&tr_db->db_map, __sgmii_transaction_compare_cb, sizeof(sgmii_transaction_id_t), 0);
    if (ret) {
        printk(KERN_ERR "failed to initialize SGMII transaction database\n");
        return ret;
    }

    spin_lock_init(&tr_db->db_lock);

    tr_db->entry_handler_cb = entry_handler_cb;
    tr_db->fill_control_segment_cb = fill_control_segment_cb;
    tr_db->fill_tx_base_header_cb = fill_tx_base_header_cb;
    tr_db->transaction_completion_cb = transaction_completion_cb;

    return 0;
}
