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
#include <linux/mutex.h>

#include "sx_bfd_rx_session.h"
#include "sx_bfd_event.h"
#include <linux/sx_bfd/sx_bfd_ctrl_cmds.h>

/*According to architecture we should support up to 1K sessions.
 * Keeping 75% load factor we need 1K/0.75 buckets = 1365 buckets.
 * rounding to power of 2 we get 2048 (11 bits) */
#define SX_BFD_SESSIONS_HASH_BITS 11
DECLARE_HASHTABLE(rx_sessions, SX_BFD_SESSIONS_HASH_BITS);

static DEFINE_SPINLOCK(rx_sess_lock);
static DEFINE_MUTEX(rx_db_lock);

static bool g_initialized = false;
struct sx_bfd_rx_session_entry {
    struct hlist_node         node;
    struct sx_bfd_rx_session *sess;
    uint32_t                  session_id;
};


void rx_delayed_work_dispatch(struct sx_bfd_rx_session * session)
{
    spin_lock_bh(&rx_sess_lock);
    if (session->deleted == 0) {
        sx_bfd_delayed_work_cancel(session->dwork);
        sx_bfd_delayed_work_dispatch(session->dwork, usecs_to_jiffies(session->interval));
    }
    spin_unlock_bh(&rx_sess_lock);
}

/* Function which called when timeout interval occurs */
static void rx_timeout_handler(uint32_t session_id)
{
    struct sx_bfd_rx_session * session = NULL;

    /* lookup session */

    session = sx_bfd_rx_sess_get_by_id(session_id);
    if (!session) {
        printk(KERN_ERR "RX timeout, but no session found.\n");
        /* Noting to do, session is probably deleted */
        return;
    }

    atomic_set(&session->remote_heard, false);

    sx_bfd_event_send_timeout(session);

    rx_delayed_work_dispatch(session);

    sx_bfd_rx_sess_put(session);
}


static unsigned long ip_addr_hash(struct ip_addr * ip_addr)
{
    unsigned long hash_key;

    if (ip_addr->family == AF_INET) {
        hash_key = jhash(&ip_addr->ipv4, sizeof(struct in_addr), 0);
    } else {
        hash_key = jhash(&ip_addr->ipv6, sizeof(struct in6_addr), 0);
    }

    return hash_key;
}


static int ip_addr_compare(struct ip_addr * ip_addr1, struct ip_addr * ip_addr2)
{
    if (ip_addr1->family != ip_addr2->family) {
        return 1;
    }

    if (ip_addr1->family == AF_INET) {
        return memcmp(&ip_addr1->ipv4, &ip_addr2->ipv4, sizeof(struct in_addr));
    } else {
        return memcmp(&ip_addr1->ipv6, &ip_addr2->ipv6, sizeof(struct in6_addr));
    }
}

/* Function returns  sx_bfd_rx_session_entry which saved in DB according to IP and VRF*/
static struct sx_bfd_rx_session_entry * sx_bfd_rx_sess_lkp_entry_by_ip_addr_vrf(struct ip_addr * ip_addr, int vrf_id)
{
    static struct sx_bfd_rx_session_entry * entry;
    unsigned long                           hash_key;

    hash_key = ip_addr_hash(ip_addr);

    hash_for_each_possible(rx_sessions, entry, node, hash_key) {
        if (!ip_addr_compare(ip_addr, &entry->sess->ip_addr) &&
            (entry->sess->vrf_id == vrf_id)) {
            return entry;
        }
    }

    return NULL;
}

/* Function returns  sx_bfd_rx_session_entry which saved in DB according to session_id*/
static struct sx_bfd_rx_session_entry * sx_bfd_rx_sess_lkp_entry_by_id(uint32_t session_id)
{
    static struct sx_bfd_rx_session_entry * entry;
    int                                     bucket;

    hash_for_each(rx_sessions, bucket, entry, node) {
        if (session_id == entry->session_id) {
            return entry;
        }
    }

    return NULL;
}

/* Function returns session based of the specific IP and VRF */
struct sx_bfd_rx_session * sx_bfd_rx_sess_get_by_ip_vrf(struct ip_addr * ip_addr,
                                                        uint32_t         vrf_id,
                                                        struct socket   *t_sock)
{
    struct sx_bfd_rx_session_entry *entry = NULL;
    int                             same = 0;

    /* protect critical DB */
    spin_lock_bh(&rx_sess_lock);

    /* Get session DS from DB according IP and VRF*/
    entry = sx_bfd_rx_sess_lkp_entry_by_ip_addr_vrf(ip_addr, vrf_id);
    if (!entry) {
        spin_unlock_bh(&rx_sess_lock);
        return NULL;
    }

    same = sx_bfd_rx_vrf_is_sock_same(entry->sess->vrf_id, t_sock);
    if (!same) {
        spin_unlock_bh(&rx_sess_lock);
        return NULL;
    }

    /*Increment ref_count of session to prevent this session being removed when
     * process using session handler
     */
    entry->sess->ref_count++;

    /*Increment ref_count of VRF to prevent this VRF being removed when
     * process using VRF handler
     */
    sx_bfd_rx_vrf_get(entry->sess->vrf_id);

    /* release protection */
    spin_unlock_bh(&rx_sess_lock);

    return entry->sess;
}

/* Function return session of the specific session_id */
struct sx_bfd_rx_session * sx_bfd_rx_sess_get_by_id(uint32_t session_id)
{
    struct sx_bfd_rx_session_entry *entry = NULL;

    /* protect critical DB */
    spin_lock_bh(&rx_sess_lock);

    /* Get session DS from DB according session_id*/
    entry = sx_bfd_rx_sess_lkp_entry_by_id(session_id);
    if (!entry) {
        spin_unlock_bh(&rx_sess_lock);
        return NULL;
    }

    /*Increment ref_count of session to prevent this session being removed when
     * process using session handler
     */
    entry->sess->ref_count++;

    /*Increment ref_count of VRF to prevent this VRF being removed when
     * process using VRF handler
     */
    sx_bfd_rx_vrf_get(entry->sess->vrf_id);

    /* release protection */
    spin_unlock_bh(&rx_sess_lock);

    return entry->sess;
}


/* Function take cares for session ref_counter (decrement) and
 * VRF ref_counter (decrement) without lock.
 * spin_lock should be called outside this function.
 * If ref_count == 0 (it means that delete_session command was called and still
 * some process used session handler) wake_up should be called on variable
 * which delete_rx_session function waiting - to be sure no other process uses
 * this session and session DS can be safely freed.
 * If session ref_count == 0 should delete VRF from DB, as its the last session
 * belongs to this VRF
 */
static void sx_bfd_rx_sess_put_no_lock(struct sx_bfd_rx_session * session)
{
    session->ref_count--;

    if (session->ref_count == 0) {
        /* Decrement ref_count on VRF and delete if no ref_count on VRF*/
        sx_bfd_rx_vrf_put(session->vrf_id, 1);
        complete(&session->free_wait);
    } else {
        /* Decrement ref_count on VRF */
        sx_bfd_rx_vrf_put(session->vrf_id, 0);
    }
}


/* Function calls another function to take care for session ref_counter and
 * VRF ref_counter under spin_lock
 */
void sx_bfd_rx_sess_put(struct sx_bfd_rx_session * session)
{
    spin_lock_bh(&rx_sess_lock);
    sx_bfd_rx_sess_put_no_lock(session);
    spin_unlock_bh(&rx_sess_lock);
}

static int rx_sess_add(struct bfd_offload_info *request_hdr, char *data, int update, void *stats)
{
    struct sx_bfd_rx_session       *session = NULL;
    struct sx_bfd_rx_session_entry *entry_session = NULL;
    unsigned long                   hash_key;
    int                             err = 0;
    void                           *entry_vrf = NULL;

    if (update) {
        BUG_ON(stats == NULL);
    }
    /* Allocate session*/
    session = kmalloc(sizeof(struct sx_bfd_rx_session), GFP_KERNEL);
    if (!session) {
        printk(KERN_ERR "Failed to allocate new RX session.\n");
        err = -ENOMEM;
        goto bail;
    }
    memset(session, 0, sizeof(struct sx_bfd_rx_session));

    /* Allocate session additional DS - packet. Received packet will be compared to this packet
     * In the case received packet will not be equal to this packet notification to user space
     * will be done via trap. */
    session->packet = (char*)kmalloc(request_hdr->size, GFP_KERNEL);
    if (session->packet == NULL) {
        printk(KERN_ERR "Failed to allocate packet in RX session.\n");
        err = -ENOMEM;
        goto bail;
    }

    /* Update packet itself */
    err = copy_from_user(session->packet, data + sizeof(struct bfd_offload_info), request_hdr->size);
    if (err < 0) {
        printk(KERN_ERR "Failed to copy RX packet from user.\n");
        goto bail;
    }

    /* Update session DS with peer address received from user space */
    session->ip_addr.family = ((struct sockaddr *)&request_hdr->peer_addr)->sa_family;
    if (session->ip_addr.family == AF_INET) {
        /*IPv4*/
        memcpy(&session->ip_addr.ipv4,
               &request_hdr->peer_addr.peer_in.sin_addr,
               sizeof(struct in_addr));
    } else {
        /*IPv6*/
        memcpy(&session->ip_addr.ipv6,
               &request_hdr->peer_addr.peer_in6.sin6_addr,
               sizeof(struct in6_addr));
    }

    /* Update session DS with peer address received from user space */
    err = sx_bfd_create_delayed_work(&session->dwork, rx_timeout_handler, request_hdr->session_id);
    if (err < 0) {
        printk(KERN_ERR "Failed to create RX delayed work.\n");
        goto bail;
    }

    /* Update session DS with additional parameters */
    session->packet_len = request_hdr->size;
    session->interval = request_hdr->interval;
    session->session_opaque_data = request_hdr->session_opaque_data;
    session->session_id = request_hdr->session_id;
    session->vrf_id = request_hdr->vrf_id;
    session->ref_count = 1;
    session->bfd_pid = request_hdr->bfd_pid;

    if (update) {
        /* this stats change is executed on cases of update (update is del session and create session),
         * in this way the statistics are stayed the same */
        atomic64_set(&session->rx_counter, ((struct bfd_offload_session_stats *)stats)->num_control);
        atomic64_set(&session->dropped_packets, ((struct bfd_offload_session_stats *)stats)->num_dropped_control);
    }

    /* Allocate entry_session for hash*/
    entry_session = kmalloc(sizeof(struct sx_bfd_rx_session_entry), GFP_KERNEL);
    if (!entry_session) {
        printk(KERN_ERR "Create RX entry session failed.\n");
        err = -ENOMEM;
        goto bail;
    }

    /* Spinlock initialization for protection of DB
     * in user context (process) && soft_IRQ (frames from socket)*/
    spin_lock_bh(&rx_sess_lock);

    hash_key = ip_addr_hash(&session->ip_addr);
    if (sx_bfd_rx_sess_lkp_entry_by_ip_addr_vrf(&session->ip_addr,
                                                session->vrf_id)) {
        spin_unlock_bh(&rx_sess_lock);
        printk(KERN_WARNING "RX session already exists.\n");
        err = -EINVAL;
        goto bail;
    }

    /*get entry VRF for incrementing ref_counter in spinlock if needed*/
    entry_vrf = sx_bfd_rx_vrf_entry_lkp_by_vrf_id(request_hdr->vrf_id);
    if (entry_vrf) {
        /*Increment ref_count of VRF to prevent this VRF being removed when
         * process using VRF handler
         */
        sx_bfd_rx_vrf_get(request_hdr->vrf_id);
    } else {
        if (update) {
            BUG_ON(entry_vrf == NULL);
        }
        /* no VRF exists and need to create DS for VRF.
         * Unlock rx_sess_lock - as VRF_Init uses malloc and it can not be
         * done in spinlock */
        spin_unlock_bh(&rx_sess_lock);

        entry_vrf = sx_bfd_rx_vrf_init(session->vrf_id, request_hdr->use_vrf_device, request_hdr->linux_vrf_name, request_hdr->bfd_pid);
        if (!entry_vrf) {
            printk(KERN_ERR "Initialization of VRF/socket FAILED.\n");
            err = -EINVAL;
            goto bail;
        }
        /* Spinlock  - as hash_add should be under protection*/
        spin_lock_bh(&rx_sess_lock);

        /*add vrf to DB under spinlock of session*/
        sx_bfd_rx_vrf_hash_add(entry_vrf);
    }


    /* Initialize entry_session DS for hash */
    INIT_HLIST_NODE(&entry_session->node);
    entry_session->sess = session;
    entry_session->session_id = request_hdr->session_id;
    init_completion(&session->free_wait);
    hash_add(rx_sessions,
             &entry_session->node,
             hash_key);

    if (update) {
        /* To avoid on update to remove and add VRF - in delete process
         * we performed additional get - here we need to release this additional
         * ref_count */
        sx_bfd_rx_vrf_put(request_hdr->vrf_id, 0);
    }
    spin_unlock_bh(&rx_sess_lock);

    /* Queue delayed work initialization*/
    rx_delayed_work_dispatch(session);

    /* set everything to NULL for not freeing it in bail */
    session = NULL;
    entry_session = NULL;

bail:

    /* Free the allocated DS in the case there were ERRORS */
    if (session) {
        if (session->dwork) {
            sx_bfd_destroy_delayed_work(session->dwork);
        }
        if (session->packet) {
            kfree(session->packet);
        }
        kfree(session);
    }

    if (entry_session) {
        kfree(entry_session);
    }
    return err;
}

int sx_bfd_rx_sess_add(char * data)
{
    struct bfd_offload_info request_hdr;
    int                     err = 0;

    /* Mutex lock for protection of DB in user context (process)
     * We prevent of executing more than 1 commands of add_rx_session/del_rx_session
     * simultaneously - as we need protect VRF from races.*/
    mutex_lock(&rx_db_lock);

    /* Prepare session DS for DB*/

    /* Copy data from user space*/
    err = copy_from_user(&request_hdr, data, sizeof(struct bfd_offload_info));
    if (err < 0) {
        printk(KERN_ERR "Failed to copy RX offload request from user.\n");
        goto bail;
    }

    err = rx_sess_add(&request_hdr, data, 0, NULL);
    if (err < 0) {
        printk(KERN_ERR "rx_sess_add for session %d VRF %d FAILED.\n", request_hdr.session_id, request_hdr.vrf_id);
        goto bail;
    }

    printk(KERN_DEBUG "Session added session_id %d VRF %d.\n",
           request_hdr.session_id, request_hdr.vrf_id);

bail:
    mutex_unlock(&rx_db_lock);
    return err;
}

static int rx_sess_del(uint32_t session_id, int update, void *stats)
{
    struct sx_bfd_rx_session_entry *entry = NULL;
    void                           *entry_vrf = NULL;

    if (update) {
        BUG_ON(stats == NULL);
    }
    /* Spinlock initialization for protection of DB
     * in user context (process) && soft_IRQ (frames from socket)*/
    spin_lock_bh(&rx_sess_lock);

    /* Get entry session for freeing it after spin_unlock
     * (free can not be called inside spinlock).
     * Moreover - we remove it from the hash - so there is no possibility
     * to take it after hash_del */
    entry = sx_bfd_rx_sess_lkp_entry_by_id(session_id);
    /* If no entry - exit from the function with err */
    if (!entry) {
        spin_unlock_bh(&rx_sess_lock);
        printk(KERN_ERR "RX session doesn't exist.\n");
        return -ENOENT;
    }

    if (update) {
        /* To avoid on update to remove and add VRF - in update process
         * we performed additional get - and in add we need to release this additional
         * ref_count on VRF*/
        sx_bfd_rx_vrf_get(entry->sess->vrf_id);
        ((struct bfd_offload_session_stats *)stats)->num_control = atomic64_read(&entry->sess->rx_counter);
    } else {
        /* Get entry session for freeing it after spin_unlock
         * (free can not be called inside spinlock).
         * Moreover - we remove session from the hash - so we will not be able
         * to take it after hash_del */
        entry_vrf = sx_bfd_rx_vrf_entry_lkp_by_vrf_id(entry->sess->vrf_id);
        BUG_ON(entry_vrf == NULL);
    }
    /* Delete entry session from hash - so new arrived packets (data plane)
     * won't get the session and those packets will be sent to user space
     * via packet event trap*/
    hash_del(&entry->node);

    /* Sign the session as delete (only from command
     * delete_rx_session it can come).
     * Its important in the function rx_delayed_work_dispatch(sx_bfd_rx_session.c)
     * not  sx_bfd_delayed_work_dispatch again if the session signed as deleted*/
    entry->sess->deleted = 1;

    /* Call to the function which decrement ref_count and taking care of VRF
     * (decrement ref_count of VRF and remove it from hash in the case this session
     * only one which belongs to this VRF*/
    sx_bfd_rx_sess_put_no_lock(entry->sess);

    /*spin_unlock - critical section is behind */
    spin_unlock_bh(&rx_sess_lock);

    /* Wait to complete all pending works*/
    sx_bfd_destroy_delayed_work_sync(entry->sess->dwork);

    /* Wait to notification from sx_bfd_rx_sess_put_no_lock that
     * no one is looking on rx_session*/
    wait_for_completion(&entry->sess->free_wait);

    if (update == 0) {
        /* Free VRF DS in the case this session was the only one
         * belonging to this VRF . If we came here from update - don't
         * free it.*/
        sx_bfd_rx_vrf_entry_free_if_needed(entry_vrf);
    }

    /* Free the session DS */
    kfree(entry->sess->packet);
    kfree(entry->sess);
    kfree(entry);

    return 0;
}

int sx_bfd_rx_sess_del(char * data)
{
    int                     err = 0;
    struct bfd_offload_info request_hdr;


    /* Mutex lock for protection of DB in user context (process)
     * We prevent of executing more than 1 commands of add_rx_session/del_rx_session
     * simultaneously - as we need protect VRF from races.*/
    mutex_lock(&rx_db_lock);

    /* <data> was received from ioctl */
    err = copy_from_user(&request_hdr, data, sizeof(struct bfd_offload_info));
    if (err) {
        printk(KERN_ERR "Failed to copy RX offload request from user.\n");
        goto bail;
    }

    /* Delete session */
    err = rx_sess_del(request_hdr.session_id, 0, NULL);
    if (err) {
        printk(KERN_ERR "Failed to delete rx_session %d.\n", request_hdr.session_id);
        goto bail;
    }
    printk(KERN_DEBUG "rx session %u was deleted\n", request_hdr.session_id);

bail:
/*mutex_unlock - no care about entering new command*/
    mutex_unlock(&rx_db_lock);
    return err;
}


int sx_bfd_rx_session_init(void)
{
    if (!g_initialized) {
        hash_init(rx_sessions);
        sx_bfd_socket_init();
        g_initialized = true;
    }

    return 0;
}

static void sx_bfd_rx_sessions_flush(void)
{
    int                                     i;
    struct hlist_node                      *tmp;
    static struct sx_bfd_rx_session_entry * entry;

    /* Delete all sessions from DB */
    hash_for_each_safe(rx_sessions, i, tmp, entry, node) {
        rx_sess_del(entry->session_id, 0, NULL);
    }
}

int sx_bfd_rx_session_deinit(void)
{
    if (g_initialized) {
        /* Delete all sessions from DB */
        sx_bfd_rx_sessions_flush();

        g_initialized = false;
    }
    return 0;
}


int sx_bfd_get_rx_sess_stats(char * data, uint8_t clear_stats)
{
    int                          err = 0;
    struct bfd_offload_get_stats request_hdr;
    struct sx_bfd_rx_session   * session = NULL;

    /* <data> was received from ioctl - copy from user space to kernel*/
    err = copy_from_user(&request_hdr, data, sizeof(struct bfd_offload_get_stats));
    if (err) {
        printk(KERN_ERR "Failed to copy bfd_offload_get_stats from user.\n");
        goto bail;
    }

    /* Get session DS from DB and update (increment) ref_count on session and VRF*/
    session = sx_bfd_rx_sess_get_by_id(request_hdr.session_id);
    if (!session) {
        printk(KERN_DEBUG "RX session doesn't exist.\n");
        goto bail;
    }

    /* Update DS which will be returned to user space */
    request_hdr.session_stats.num_control = atomic64_read(&session->rx_counter);
    request_hdr.session_stats.num_dropped_control = atomic64_read(&session->dropped_packets);
    request_hdr.session_stats.remote_heard = atomic_read(&session->remote_heard);
    request_hdr.session_stats.last_time = session->last_time;

    /* not really measuring interval time - using the configured interval time */
    request_hdr.session_stats.interval_average = session->interval;
    request_hdr.session_stats.interval_max = session->interval;
    request_hdr.session_stats.interval_min = session->interval;

    if (clear_stats) {
        atomic64_set(&session->rx_counter, 0);
        atomic64_set(&session->dropped_packets, 0);
    }

    /* Get session DS from DB and update (decrement) ref_count on session and VRF*/
    sx_bfd_rx_sess_put(session);

    /* copy from kernel to user space */
    err = copy_to_user(data, &request_hdr, sizeof(struct bfd_offload_get_stats));
    if (err) {
        printk(KERN_ERR "Failed to copy bfd_offload_get_stats from user.\n");
        goto bail;
    }

bail:
    return err;
}


int sx_bfd_rx_sess_update(char *data)
{
    struct bfd_offload_session_stats session_stats;
    int                              err = 0;
    struct bfd_offload_info          request_hdr;


    /* Mutex lock for protection of DB in user context (process)
     * We prevent of executing more than 1 commands of add_rx_session/del_rx_session
     * simultaneously - as we need protect VRF from races.*/
    mutex_lock(&rx_db_lock);

    memset(&session_stats, 0, sizeof(struct bfd_offload_session_stats));

    /* <data> was received from ioctl */
    err = copy_from_user(&request_hdr, data, sizeof(struct bfd_offload_info));
    if (err) {
        printk(KERN_ERR "Failed to copy RX offload request from user.\n");
        goto bail;
    }

    err = rx_sess_del(request_hdr.session_id, 1, (void*)&session_stats);
    if (err != 0) {
        printk(KERN_ERR "Failed to delete rx_session %d.\n", request_hdr.session_id);
        goto bail;
    }

    err = rx_sess_add(&request_hdr, data, 1, (void*)&session_stats);
    if (err != 0) {
        printk(KERN_ERR "Failed to add rx_session %d.\n.\n", request_hdr.session_id);
        goto bail;
    }

    printk(KERN_DEBUG "Session session_id %d VRF %d updated.\n",
           request_hdr.session_id, request_hdr.vrf_id);

bail:
    mutex_unlock(&rx_db_lock);
    return err;
}
