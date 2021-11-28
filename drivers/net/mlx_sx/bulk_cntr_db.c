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
#include <linux/uaccess.h>

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
static sxd_port_per_prio_counter_cache_t *__per_prio_counter_cache = NULL;

/* this function gets user process ID + user shared memory pointer and returns the shared memory pointer
 * from driver's perspective */
struct sxd_bulk_cntr_buffer_layout_common * __get_buffer(pid_t client_pid, unsigned long buffer_id)
{
    return (struct sxd_bulk_cntr_buffer_layout_common*)sx_mmap_user_to_kernel(client_pid, buffer_id);
}

static void __init_elephant_layout(struct sxd_bulk_cntr_buffer_layout_elephant *layout_elephant_p,
                                   struct sxd_bulk_cntr_params_elephant        *elephant_params_p)
{
    int total_ports = 0, i = 0, j = 0;

    memcpy(&layout_elephant_p->port_mask, &elephant_params_p->port_mask,
           sizeof(layout_elephant_p->port_mask));

    for (i = 0; i < SXD_COS_ELEPHANT_PORT_MASK_NUM; i++) {
        for (j = 0; j < 32; j++) {
            if (layout_elephant_p->port_mask[i] & (1 << j)) {
                total_ports++;
            }
        }
    }

    memset(&layout_elephant_p->port_flows, 0, sizeof(layout_elephant_p->port_flows));
    memset(&layout_elephant_p->data, 0, sizeof(layout_elephant_p->data[0]) * total_ports *
           SXD_COS_ELEPHANT_FLOW_ID_NUM_MAX);
}

/* add a new bulk-counter transaction */
int bulk_cntr_db_add(struct ku_bulk_cntr_transaction_add *bulk_cntr_tr_add)
{
    struct sxd_bulk_cntr_buffer_layout_common        *layout_common;
    struct sxd_bulk_cntr_buffer_layout_flow          *layout_flow;
    struct sxd_bulk_cntr_buffer_layout_shared_buffer *layout_shared_buffer;
    struct sxd_bulk_cntr_buffer_layout_headroom      *layout_headroom;
    struct sxd_bulk_cntr_buffer_layout_port          *layout_port;
    struct sxd_bulk_cntr_buffer_layout_elephant      *layout_elephant;
    struct transaction_entry                         *entry;
    int                                               i = 0, j = 0;
    int                                               err = 0;

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
    switch (layout_common->type) {
    case SXD_BULK_CNTR_KEY_TYPE_FLOW_E:
        layout_flow = (struct sxd_bulk_cntr_buffer_layout_flow*)layout_common;
        layout_flow->base_counter_id = bulk_cntr_tr_add->params.flow_params.base_counter_id;
        break;

    case SXD_BULK_CNTR_KEY_TYPE_SHARED_BUFFER_E:
        layout_shared_buffer = (struct sxd_bulk_cntr_buffer_layout_shared_buffer*)layout_common;
        layout_common->num_of_counters = bulk_cntr_tr_add->params.shared_buffer_params.num_of_counters;
        layout_shared_buffer->port_idx = 0;
        layout_shared_buffer->pg_tc_sp_idx = 0;
        layout_shared_buffer->port_pool_idx = 0;
        layout_shared_buffer->pool_idx = 0;
        layout_shared_buffer->last_type = SXD_BULK_CNTR_SB_TYPE_INVALID;
        layout_shared_buffer->mc_pool_id = bulk_cntr_tr_add->params.shared_buffer_params.mc_pool_id;
        memcpy(layout_shared_buffer->port_mask, bulk_cntr_tr_add->params.shared_buffer_params.port_mask,
               sizeof(uint32_t) * SXD_BULK_CNTR_PORT_MASK_NUM);
        memcpy(layout_shared_buffer->sw_pool_id, bulk_cntr_tr_add->params.shared_buffer_params.sw_pool_id,
               sizeof(uint32_t) * SXD_BULK_CNTR_TOTAL_POOL_MAX_NUM);
        memset(layout_shared_buffer->port, 0, sizeof(sxd_bulk_cntr_shared_buffer_port_t) * SXD_BULK_CNTR_PORT_NUM);
        for (i = 0; i < SXD_BULK_CNTR_PORT_NUM; i++) {
            for (j = 0; j < SXD_BULK_CNTR_POOL_NUM; j++) {
                layout_shared_buffer->port[i].rx_per_pool[j].sw_pool_id = SXD_BULK_CNTR_POOL_ID_INVALID;
                layout_shared_buffer->port[i].tx_per_pool[j].sw_pool_id = SXD_BULK_CNTR_POOL_ID_INVALID;
                layout_shared_buffer->port[i].rx_per_pool_desc[j].sw_pool_id = SXD_BULK_CNTR_POOL_ID_INVALID;
                layout_shared_buffer->port[i].tx_per_pool_desc[j].sw_pool_id = SXD_BULK_CNTR_POOL_ID_INVALID;
            }
        }
        memset(layout_shared_buffer->mc_port, 0, sizeof(sxd_bulk_cntr_shared_buffer_mc_port_t) *
               SXD_BULK_CNTR_PORT_NUM);
        memset(&layout_shared_buffer->mc_switch_prio, 0, sizeof(sxd_bulk_cntr_shared_buffer_mc_sp_t));
        memset(&layout_shared_buffer->pool, 0, sizeof(sxd_bulk_cntr_shared_buffer_pool_t));
        for (i = 0; i < SXD_BULK_CNTR_TOTAL_POOL_MAX_NUM; i++) {
            layout_shared_buffer->pool.statistics[i].sw_pool_id = SXD_BULK_CNTR_POOL_ID_INVALID;
        }

        break;

    case SXD_BULK_CNTR_KEY_TYPE_HEADROOM_E:
        layout_headroom = (struct sxd_bulk_cntr_buffer_layout_headroom*)layout_common;
        layout_common->num_of_counters = bulk_cntr_tr_add->params.headroom_params.num_of_counters;
        memcpy(layout_headroom->port_width, bulk_cntr_tr_add->params.headroom_params.port_width,
               sizeof(uint8_t) * SXD_BULK_CNTR_PORT_NUM);
        memcpy(layout_headroom->port_mask, bulk_cntr_tr_add->params.headroom_params.port_mask,
               sizeof(uint32_t) * SXD_BULK_CNTR_PORT_NUM);
        memset(layout_headroom->headroom, 0, sizeof(sxd_bulk_cntr_headroom_port_t) * SXD_BULK_CNTR_PORT_NUM);
        break;

    case SXD_BULK_CNTR_KEY_TYPE_PORT_E:
        layout_common->num_of_counters = bulk_cntr_tr_add->params.port_params.number_of_counters;
        layout_port = (struct sxd_bulk_cntr_buffer_layout_port*)layout_common;
        memcpy(&(layout_port->mappings),
               &(bulk_cntr_tr_add->params.port_params.mappings),
               sizeof(layout_port->mappings));
        memset(layout_port->counters, 0, sizeof(layout_port->counters[0]) * (layout_port->counters_size));
        break;

    case SXD_BULK_CNTR_KEY_TYPE_ELEPHANT_E:
        layout_elephant = (struct sxd_bulk_cntr_buffer_layout_elephant *)layout_common;
        __init_elephant_layout(layout_elephant, &bulk_cntr_tr_add->params.elephant_params);
        break;

    default:
        break;
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
                          enum sxd_bulk_cntr_done_status_e *status,
                          uint32_t                         *cookie)
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
    if (entry->is_canceled) {
        *status = SXD_BULK_CNTR_DONE_STATUS_CANCELED;
    } else if (entry->common_layout->num_of_counters != entry->common_layout->counters_received_so_far) {
        *status = SXD_BULK_CNTR_DONE_STATUS_ERROR;
    } else {
        *status = SXD_BULK_CNTR_DONE_STATUS_OK;
    }

    if (cookie) {
        *cookie = entry->common_layout->cookie;
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

int bulk_cntr_db_per_prio_cache_set(struct ku_bulk_cntr_per_prio_cache *bulk_cntr_per_prio_cache)
{
    int err = 0;

    spin_lock_bh(&__bulk_cntr_db_lock);

    if (bulk_cntr_per_prio_cache->is_set) {
        __per_prio_counter_cache = (sxd_port_per_prio_counter_cache_t*)sx_mmap_user_to_kernel(
            bulk_cntr_per_prio_cache->pid,
            bulk_cntr_per_prio_cache->user_ptr);
        if (!__per_prio_counter_cache) {
            printk(KERN_ERR "Bulk-Counter DB per prio cache set - invalid buffer_id\n");
            err = -EINVAL;
            goto out;
        }
    } else {
        __per_prio_counter_cache = NULL;
    }

out:
    spin_unlock_bh(&__bulk_cntr_db_lock);
    return err;
}

int bulk_cntr_db_per_prio_cache_entry_get(uint16_t local_port, uint16_t prio, sxd_port_cntr_prio_t **cache_entry)
{
    int err = 0;

    spin_lock_bh(&__bulk_cntr_db_lock);

    if (!__per_prio_counter_cache) {
        err = -ENOENT;
        goto out;
    }

    if ((local_port > MAX_PHYPORT_NUM) || (prio > SXD_PORT_PRIO_ID_MAX) || (!cache_entry)) {
        err = -EINVAL;
        goto out;
    }

    *cache_entry = &(__per_prio_counter_cache->counters[local_port][prio]);

out:
    spin_unlock_bh(&__bulk_cntr_db_lock);
    return err;
}

int bulk_cntr_db_in_progress(struct ku_bulk_cntr_transaction *bulk_cntr_tr_in_progress, void *data)
{
    int err = 0;

    if (bulk_cntr_tr_in_progress->type >= SXD_BULK_CNTR_KEY_TYPE_LAST_E) {
        err = -EINVAL;
        printk(KERN_ERR "Bulk-Counter DB in progress - invalid type: %u\n", bulk_cntr_tr_in_progress->type);
        goto out;
    }

    bulk_cntr_tr_in_progress->in_progress = (__in_progress[bulk_cntr_tr_in_progress->type] != NULL);
    err = copy_to_user((void*)data, bulk_cntr_tr_in_progress, sizeof(*bulk_cntr_tr_in_progress));
    if (err) {
        goto out;
    }

out:
    return err;
}
