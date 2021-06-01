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

#include <linux/string.h>
#include <linux/hash.h>
#include <linux/hashtable.h>
#include <linux/jhash.h>
#include <linux/types.h>
#include <linux/spinlock.h>

#include "sx_bfd_tx_session.h"
#include "sx_bfd_socket.h"
#include <linux/sx_bfd/sx_bfd_ctrl_cmds.h>

/*According to architecture we should support up to 1K sessions.
 * Keeping 75% load factor we need 1K/0.75 buckets = 1365 buckets.
 * rounding to power of 2 we get 2048 (11 bits) */
#define SX_BFD_SESSIONS_HASH_BITS 11
static DECLARE_HASHTABLE(tx_sessions, SX_BFD_SESSIONS_HASH_BITS);

static DEFINE_SPINLOCK(tx_sess_lock);

static bool g_initialized = false;
static void sx_bfd_tx_sess_put_no_lock(struct sx_bfd_tx_session * session)
{
    session->ref_count--;

    if (session->ref_count == 0) {
        /* Decrement ref_count on VRF and delete if no ref_count on VRF*/
        complete(&session->free_wait);
    }
}

static void sx_bfd_tx_sess_put(struct sx_bfd_tx_session * session)
{
    spin_lock_bh(&tx_sess_lock);
    sx_bfd_tx_sess_put_no_lock(session);
    spin_unlock_bh(&tx_sess_lock);
}

static void tx_timeout_handler(uint32_t session_id)
{
    struct sx_bfd_tx_session * session = NULL;

    /* lookup session */
    session = sx_bfd_tx_sess_get(session_id);

    if (session == NULL) {
        printk(KERN_ERR "TX timeout, but no session found.\n");
        /* Noting to do, session is probably deleted */
        return;
    }
    /* send packet */
    if (sx_bfd_socket_send(session->sock, (char*)session->packet, session->packet_len,
                           (struct sockaddr *)&session->peer_addr) == true) {
        /* statistics - raise statistics only if send packet success */
        atomic64_inc(&session->tx_counter);
    }

    spin_lock_bh(&tx_sess_lock);

    /* Check if during this action was command to destroy session.
     * If this command was received - don't retrigger timer. */
    if (session->deleted == 0) {
        sx_bfd_delayed_work_cancel(session->dwork);
        sx_bfd_delayed_work_dispatch(session->dwork, usecs_to_jiffies(session->interval));
    }
    spin_unlock_bh(&tx_sess_lock);
    sx_bfd_tx_sess_put(session);
}

static struct sx_bfd_tx_session_entry * sx_bfd_tx_sess_lkp_entry(uint32_t session_id)
{
    static struct sx_bfd_tx_session_entry * entry;
    unsigned long                           hash_key;

    hash_key = jhash(&session_id, sizeof(uint32_t), 0);

    hash_for_each_possible(tx_sessions, entry, node, hash_key) {
        if (entry->session_id == session_id) {
            return entry;
        }
    }

    return NULL;
}


struct sx_bfd_tx_session * sx_bfd_tx_sess_get(uint32_t session_id)
{
    struct sx_bfd_tx_session_entry *entry = NULL;

    spin_lock_bh(&tx_sess_lock);

    entry = sx_bfd_tx_sess_lkp_entry(session_id);

    if (!entry) {
        spin_unlock_bh(&tx_sess_lock);
        printk(KERN_WARNING "TX Session %u doesn't exist.\n", session_id);
        return NULL;
    }

    entry->sess->ref_count++;

    spin_unlock_bh(&tx_sess_lock);

    return entry->sess;
}


int sx_bfd_tx_sess_add(char *data, void* stats)
{
    struct bfd_offload_info         request_hdr;
    struct sx_bfd_tx_session       *session = NULL;
    struct sx_bfd_tx_session_entry *entry = NULL;
    unsigned long                   hash_key;
    int                             err = 0;

    /* <data> was received from ioctl */
    err = copy_from_user(&request_hdr, data, sizeof(struct bfd_offload_info));
    if (err) {
        printk(KERN_ERR "Failed to copy TX offload request from user.\n");
        goto bail;
    }

    /* Prepare Tx session */

    /* Allocate Tx session DS and clear it */
    session = kmalloc(sizeof(struct sx_bfd_tx_session), GFP_KERNEL);
    if (!session) {
        printk(KERN_ERR "Failed to allocate new TX session.\n");
        err = -ENOMEM;
        goto bail;
    }

    memset(session, 0, sizeof(struct sx_bfd_tx_session));

    /* Allocate place to packet inside Tx session DS
     * (this packet will be sent every timeout event) and initialize it */
    session->packet = (char*)kmalloc(request_hdr.size, GFP_KERNEL);
    if (session->packet == NULL) {
        printk(KERN_ERR "Failed to allocate packet in TX session.\n");
        err = -ENOMEM;
        goto bail;
    }

    err = copy_from_user(session->packet, data + sizeof(struct bfd_offload_info), request_hdr.size);
    if (err < 0) {
        printk(KERN_ERR "Failed to copy TX packet from user.\n");
        goto bail;
    }

    /* Initialize peer address DS - destination identification */
    if (((struct sockaddr *)&request_hdr.peer_addr)->sa_family == AF_INET) {
        /*IPv4*/
        memcpy(&session->peer_addr.peer_in,
               &request_hdr.peer_addr.peer_in,
               sizeof(struct sockaddr_in));
    } else {
        /*IPv6*/
        memcpy(&session->peer_addr.peer_in6,
               &request_hdr.peer_addr.peer_in6,
               sizeof(struct sockaddr_in6));
    }

    /* Create delayed work for handling timeout event */
    err = sx_bfd_create_delayed_work(&session->dwork, tx_timeout_handler, request_hdr.session_id);
    if (err < 0) {
        printk(KERN_ERR "Failed to create TX delayed work.\n");
        goto bail;
    }

    /* Create Tx socket - this socket is used to send the packets out.
     * As in User space we switched context to the correct namespace (VRF)
     * this socket will be create in the context of required namespace (VRF) */
    err = sx_bfd_tx_socket_create((struct sockaddr *)&request_hdr.local_addr,
                                  request_hdr.ttl,
                                  request_hdr.dscp,
                                  &session->sock,
                                  ((struct sockaddr *)&request_hdr.peer_addr)->sa_family,
                                  request_hdr.use_vrf_device,
                                  request_hdr.linux_vrf_name);
    if (err < 0) {
        printk(KERN_ERR "Failed to create TX socket.\n");
        goto bail;
    }

    /* Initialize the rest of the parameters of Tx session DS. */
    session->packet_len = request_hdr.size;
    session->interval = request_hdr.interval;
    session->ref_count = 1;
    session->vrf_id = request_hdr.vrf_id;
    session->bfd_pid = request_hdr.bfd_pid;
    init_completion(&session->free_wait);

    /* this stats change is executed on cases of update (update is del session and create session),
     * in this way the statistics are stayed the same */
    if (stats) {
        atomic64_set(&session->tx_counter, ((struct bfd_offload_session_stats *)stats)->num_control);
    }

    /* Allocate place for entry DS which will be added to hash. */
    entry = kmalloc(sizeof(struct sx_bfd_tx_session_entry), GFP_KERNEL);
    if (!entry) {
        printk(KERN_ERR "Create TX entry failed.\n");
        err = -ENOMEM;
        goto bail;
    }

    hash_key = jhash(&request_hdr.session_id, sizeof(uint32_t), 0);

    spin_lock_bh(&tx_sess_lock);

    if (sx_bfd_tx_sess_lkp_entry(request_hdr.session_id)) {
        spin_unlock_bh(&tx_sess_lock);
        printk(KERN_WARNING "TX Session already exists.\n");
        err = -EINVAL;
        goto bail;
    }

    INIT_HLIST_NODE(&entry->node);
    entry->session_id = request_hdr.session_id;
    entry->sess = session;
    hash_add(tx_sessions, &entry->node, hash_key);

    spin_unlock_bh(&tx_sess_lock);

    /* Trigger delayed work */
    sx_bfd_delayed_work_cancel(session->dwork);

    /* send an immediate tx transmit and later all delayed work will be use the session interval,
     * fix to bug 1519677 */
    sx_bfd_delayed_work_dispatch(session->dwork, 0);


    session = NULL;
    entry = NULL;

    printk(KERN_DEBUG "TX Session %u was added successfully.\n", request_hdr.session_id);

bail:
    if (session) {
        if (session->dwork) {
            sx_bfd_destroy_delayed_work(session->dwork);
        }
        if (session->packet) {
            kfree(session->packet);
        }
        if (session->sock) {
            sx_bfd_tx_socket_destroy(session->sock);
        }
        kfree(session);
    }
    if (entry) {
        kfree(entry);
    }
    return err;
}

static int tx_sess_del(uint32_t session_id, void *stats)
{
    struct sx_bfd_tx_session_entry *entry = NULL;

    /* Spinlock initialization for protection of DB
     * in user context (process) && soft_IRQ (frames from socket)*/
    spin_lock_bh(&tx_sess_lock);

    /* Get entry session for freeing it after spin_unlock
     * (free can not be called inside spinlock).
     * Moreover - we remove it from the hash - so there is no possibility
     * to take it after hash_del */
    entry = sx_bfd_tx_sess_lkp_entry(session_id);
    /* If no entry - exit from the function with err */
    if (!entry) {
        spin_unlock_bh(&tx_sess_lock);
        printk(KERN_ERR "TX session doesn't exist.\n");
        return -ENOENT;
    }

    /* Delete entry session from hash - so timeout event which is responsible
     * to send packets every period of time  won't get the session
     * and those packets won't sent out*/
    hash_del(&entry->node);

    /* Sign the session as delete .
     * Its important in the function tx_timeout_handler(sx_bfd_tx_session.c)
     * not  sx_bfd_delayed_work_cancel() && not
     * sx_bfd_delayed_work_dispatch() will be called*/
    entry->sess->deleted = 1;

    /* Call to the function which decrement ref_count and if ref_count == 0
     * no one uses this function and deleted was signed up free_wait*/
    sx_bfd_tx_sess_put_no_lock(entry->sess);

    /*spin_unlock - critical section is behind */
    spin_unlock_bh(&tx_sess_lock);

    /* Wait to complete all pending works*/
    sx_bfd_destroy_delayed_work_sync(entry->sess->dwork);

    /* Wait to notification from sx_bfd_tx_sess_put_no_lock that
     * no one is using on tx_session*/
    wait_for_completion(&entry->sess->free_wait);

    /* Destroy the socket. */
    sx_bfd_tx_socket_destroy(entry->sess->sock);

    /* read statistics before deleting session - this is used when we want to update session */
    if (stats) {
        ((struct bfd_offload_session_stats *)stats)->num_control = atomic64_read(&entry->sess->tx_counter);
    }

    /* Free the session DS */
    kfree(entry->sess->packet);
    kfree(entry->sess);
    kfree(entry);

    printk(KERN_DEBUG "tx_sess_del %d. \n", session_id);

    return 0;
}

int sx_bfd_tx_sess_del(char *data, void* stats)
{
    int                     err = 0;
    struct bfd_offload_info request_hdr;


    /* <data> was received from ioctl */
    err = copy_from_user(&request_hdr, data, sizeof(struct bfd_offload_info));
    if (err) {
        printk(KERN_ERR "Failed to copy TX offload request from user.\n");
        goto bail;
    }

    err = tx_sess_del(request_hdr.session_id, stats);
    if (err) {
        printk(KERN_ERR "Failed to delete tx_session. (session id  %u)\n", request_hdr.session_id);
        goto bail;
    }

    printk(KERN_DEBUG "tx session %u was deleted\n", request_hdr.session_id);

bail:
    return err;
}

int sx_bfd_tx_session_init(void)
{
    if (!g_initialized) {
        hash_init(tx_sessions);

        g_initialized = true;
    }

    return 0;
}

static void sx_bfd_tx_sessions_flush(void)
{
    int                                     i;
    struct hlist_node                      *tmp;
    static struct sx_bfd_tx_session_entry * entry;

    hash_for_each_safe(tx_sessions, i, tmp, entry, node) {
        tx_sess_del(entry->session_id, NULL);
    }
}

int sx_bfd_tx_session_deinit(void)
{
    if (g_initialized) {
        /*delete all sessions from DB & free DB */
        sx_bfd_tx_sessions_flush();

        g_initialized = false;
    }

    return 0;
}


int sx_bfd_get_tx_sess_stats(char * data, uint8_t clear_stats)
{
    int                          err = 0;
    struct bfd_offload_get_stats request_hdr;
    struct sx_bfd_tx_session   * session = NULL;

    /* <data> was received from ioctl */
    err = copy_from_user(&request_hdr, data, sizeof(struct bfd_offload_get_stats));
    if (err) {
        printk(KERN_ERR "Failed to copy bfd_offload_get_stats from user.\n");
        goto bail;
    }

    session = sx_bfd_tx_sess_get(request_hdr.session_id);
    if (session == NULL) {
        printk(KERN_ERR "TX timeout, but no session found.\n");
        /* Noting to do, session is probably deleted */
        return -ENOENT;
    }
    request_hdr.session_stats.num_control = atomic64_read(&session->tx_counter);
    request_hdr.session_stats.num_dropped_control = 0;
    request_hdr.session_stats.interval_average = session->interval;
    request_hdr.session_stats.interval_max = session->interval;
    request_hdr.session_stats.interval_min = session->interval;

    if (clear_stats) {
        atomic64_set(&session->tx_counter, 0);
    }

    sx_bfd_tx_sess_put(session);

    err = copy_to_user(data, &request_hdr, sizeof(struct bfd_offload_get_stats));
    if (err) {
        printk(KERN_ERR "Failed to copy bfd_offload_get_tx_stats from user.\n");
        goto bail;
    }

bail:
    return err;
}

int sx_bfd_tx_sess_update(char *data)
{
    struct bfd_offload_session_stats session_stats;
    int                              err = 0;

    memset(&session_stats, 0, sizeof(struct bfd_offload_session_stats));

    err = sx_bfd_tx_sess_del(data, (void*)&session_stats);
    if (err != 0) {
        return err;
    }

    err = sx_bfd_tx_sess_add(data, (void*)&session_stats);
    if (err != 0) {
        return err;
    }

    return err;
}
