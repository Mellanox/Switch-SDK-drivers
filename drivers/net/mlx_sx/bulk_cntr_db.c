/*
 * Copyright (c) 2010-2020,  Mellanox Technologies. All rights reserved.
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

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/hashtable.h>

#include "mmap.h"
#include "bulk_cntr_db.h"

#define BULK_CNTR_MAX_IN_PROGRESS (2)

struct transaction_entry {
    unsigned long                              buffer_id; /* mmap pointer in user process */
    sxd_bulk_cntr_event_id_t                   event_id;
    u8                                         is_canceled; /* is transaction canceled by user */
    struct sxd_bulk_cntr_buffer_layout_common *common_layout; /* pointer to shared-memory from driver's perspective */
};
struct transaction_status {
    pid_t                            client_pid; /* user process ID */
    unsigned long                    buffer_id; /* mmap pointer in user process */
    enum sxd_bulk_cntr_done_status_e status; /* status of the transaction */
};
static struct transaction_entry *__in_progress[SXD_BULK_CNTR_KEY_TYPE_LAST_E];
static u32                       __in_progress_cnt = 0;
static DEFINE_SPINLOCK(__bulk_cntr_db_lock);

/* this function gets user process ID + user shared memory pointer and returns the shared memory pointer
 * from driver's perspective */
struct sxd_bulk_cntr_buffer_layout_common * __get_buffer(pid_t client_pid, unsigned long buffer_id)
{
    return (struct sxd_bulk_cntr_buffer_layout_common*)sx_mmap_user_to_kernel(client_pid, buffer_id);
}

/* add a new bulk-counter transaction */
int bulk_cntr_db_add(struct ku_bulk_cntr_transaction_add *bulk_cntr_tr_add)
{
    struct sxd_bulk_cntr_buffer_layout_common *layout_common;
    struct sxd_bulk_cntr_buffer_layout_flow   *layout_flow;
    struct transaction_entry                  *entry;
    int                                        err = 0;

    /* convert from user-process shared memory pointer to driver's pointer */
    layout_common = __get_buffer(bulk_cntr_tr_add->event_id.event_id_fields.client_id,
                                 bulk_cntr_tr_add->buffer_id);
    if (!layout_common) {
        printk(KERN_ERR "Bulk-Counter DB add - invalid buffer_id\n");
        return -EINVAL;
    }

    spin_lock_bh(&__bulk_cntr_db_lock);

    /* if the buffer is already in progress with another transaction
     *   OR
     * no more transactions allowed,
     * then we return BUSY */
    if ((__in_progress[layout_common->type] != NULL) ||
        (__in_progress_cnt == BULK_CNTR_MAX_IN_PROGRESS)) {
        err = -EBUSY;
        goto out;
    }

    entry = kmalloc(sizeof(struct transaction_entry), GFP_ATOMIC);
    if (!entry) {
        err = -ENOMEM;
        goto out;
    }

    layout_common->counters_received_so_far = 0; /* reset the numbers received for the new transaction */
    if (layout_common->type == SXD_BULK_CNTR_KEY_TYPE_FLOW_E) {
        layout_flow = (struct sxd_bulk_cntr_buffer_layout_flow*)layout_common;
        layout_flow->base_counter_id = bulk_cntr_tr_add->params.flow_params.base_counter_id;
    }

    /* save transaction data */
    entry->buffer_id = bulk_cntr_tr_add->buffer_id;
    entry->event_id = bulk_cntr_tr_add->event_id;
    entry->is_canceled = 0;
    entry->common_layout = layout_common;

    __in_progress[layout_common->type] = entry;
    __in_progress_cnt++;

out:
    spin_unlock_bh(&__bulk_cntr_db_lock);
    return err;
}


/* common delete (called from DEL/COMPLETE) of bulk-counter transaction from DB */
static void __bulk_cntr_db_del(uint32_t type, struct transaction_entry *entry)
{
    __in_progress[type] = NULL;
    __in_progress_cnt--;
    kfree(entry);
}


/* delete a bulk-counter transaction from DB */
int bulk_cntr_db_del(pid_t client_pid, unsigned long buffer_id)
{
    struct sxd_bulk_cntr_buffer_layout_common *layout_common;
    struct transaction_entry                  *entry;
    int                                        err = 0;

    /* convert from user-process shared memory pointer to driver's pointer */
    layout_common = __get_buffer(client_pid, buffer_id);
    if (!layout_common) {
        printk(KERN_ERR "Bulk-Counter DB del - invalid buffer_id\n");
        return -EINVAL;
    }

    spin_lock_bh(&__bulk_cntr_db_lock);

    /* check if there requested buffer is indeed in progress */
    entry = __in_progress[layout_common->type];
    if (!entry || (entry->buffer_id != buffer_id)) {
        err = -ENOENT;
        goto out;
    }

    /* check if the operation was canceled by the user */
    if (entry->is_canceled) { /* transaction is already canceled, waiting for MOCS_DONE to delete it */
        err = -EBUSY;
        goto out;
    }

    /* delete the transaction from DB */
    __bulk_cntr_db_del(layout_common->type, entry);

out:
    spin_unlock_bh(&__bulk_cntr_db_lock);
    return err;
}


/* cancel an operation that is in progress */
int bulk_cntr_db_cancel(pid_t client_pid, unsigned long buffer_id)
{
    struct sxd_bulk_cntr_buffer_layout_common *layout_common;
    struct transaction_entry                  *entry;
    int                                        err = 0;

    /* convert from user-process shared memory pointer to driver's pointer */
    layout_common = __get_buffer(client_pid, buffer_id);
    if (!layout_common) {
        printk(KERN_ERR "Bulk-Counter DB cancel - invalid buffer_id\n");
        return -EINVAL;
    }

    spin_lock_bh(&__bulk_cntr_db_lock);

    /* check if there requested buffer is indeed in progress */
    entry = __in_progress[layout_common->type];
    if (!entry || (entry->buffer_id != buffer_id)) {
        err = -ENOENT;
        goto out;
    }

    /* mark the transaction as 'canceled' */
    entry->is_canceled = 1;

out:
    spin_unlock_bh(&__bulk_cntr_db_lock);
    return err;
}


/* complete a transaction. called in two cases:
 * 1. MOCS_DONE event handled by the driver and no ack from SDK is required.
 * 2. Ack from SDK upon MOCS_DONE event (in cases when SDK has to do
 *    some cleanups for the transaction, e.g. unlock counter range).
 */
int bulk_cntr_db_complete(const sxd_bulk_cntr_event_id_t   *event_id,
                          unsigned long                    *buffer_id,
                          enum sxd_bulk_cntr_done_status_e *status)
{
    struct transaction_entry     *entry;
    enum sxd_bulk_cntr_key_type_e type;
    int                           err = 0;

    type = event_id->event_id_fields.type;

    spin_lock_bh(&__bulk_cntr_db_lock);

    /* check that there is an operation of type 'type' in progress */
    entry = __in_progress[type];
    if (!entry) {
        err = -ENOENT;
        goto out;
    }

    if (buffer_id) {
        *buffer_id = entry->buffer_id;
    }

    /* determine the status of the transaction to be reported to the user */
    if (entry->common_layout->num_of_counters != entry->common_layout->counters_received_so_far) {
        *status = SXD_BULK_CNTR_DONE_STATUS_ERROR;
    } else if (entry->is_canceled) {
        *status = SXD_BULK_CNTR_DONE_STATUS_CANCELED;
    } else {
        *status = SXD_BULK_CNTR_DONE_STATUS_OK;
    }

    /* delete the transaction from DB */
    __bulk_cntr_db_del(event_id->event_id_fields.type, entry);
out:
    spin_unlock_bh(&__bulk_cntr_db_lock);
    return err;
}


/* get a buffer from MOCS event_id field (upon MOCS parsing) */
int bulk_cntr_db_event_id_to_buffer(sxd_bulk_cntr_event_id_t                   *event_id,
                                    struct sxd_bulk_cntr_buffer_layout_common **layout_common)
{
    struct transaction_entry *entry;
    int                       err = 0;

    spin_lock_bh(&__bulk_cntr_db_lock);

    /* check that there is an operation of type 'type' in progress */
    entry = __in_progress[event_id->event_id_fields.type];
    if (!entry) {
        err = -ENOENT;
        goto out;
    }

    *layout_common = entry->common_layout;

out:
    spin_unlock_bh(&__bulk_cntr_db_lock);
    return err;
}
