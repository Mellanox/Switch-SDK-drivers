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
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <net/ipv6.h>

#include "sx_bfd_engine_data.h"
#include "sx_bfd_socket.h"
#include "sx_bfd_event.h"
#include "sx_bfd_rx_session.h"
#include "sx_bfd_workqueue.h"


#define MAX_BFD_SIZE 128

void recv_packet(struct socket        *t_sock,
                 enum sx_bfd_sock_type sock_type,
                 uint32_t              vrf_id,
                 unsigned long         bfd_user_space_pid)
{
    char                      buf[MAX_BFD_SIZE];
    struct metadata           metadata;
    int                       len;
    struct sx_bfd_rx_session *session;
    struct ip_addr            ip_addr;
    unsigned long             current_jiffies, received_packet_msec;

    /* Get the packet received on the socket.
     * Its UDP socket - here we will get frame frame and not number of frames
     * in one shot.*/
    len = sx_bfd_socket_recv(t_sock, buf, MAX_BFD_SIZE, &metadata);

    /* Check if any frame was received - len <= 0 - no frame received */
    if (len <= 0) {
        return;
    }

    /* Get IP to check if session in DB. */
    memset(&ip_addr, 0, sizeof(struct ip_addr));

    ip_addr.family = ((struct sockaddr*)&metadata.peer_addr)->sa_family;
    if (ip_addr.family == AF_INET) {
        memcpy(&ip_addr.ipv4, &metadata.peer_addr.peer_in.sin_addr, sizeof(struct in_addr));
    } else {
        memcpy(&ip_addr.ipv6, &metadata.peer_addr.peer_in6.sin6_addr, sizeof(struct in6_addr));
    }

    /* Get session */
    session = sx_bfd_rx_sess_get_by_ip_vrf(&ip_addr, vrf_id, t_sock);
    if (!session) {
        /* If session is not found - send the packet to user space to take care. */
        sx_bfd_event_send_packet(NULL, buf, len, &metadata, bfd_user_space_pid);
        return;
    }


    /* Validate the frame. */
    if ((sock_type == sx_bfd_SOCK_SINGLEHOP) && (metadata.ttl != 0) && (metadata.ttl != 255)) {
        /* If frame is not valid - send this frame to user space via trap
         * and increment dropped_packet counter as it will be dropped in user space */
        sx_bfd_event_send_packet(session, buf, len, &metadata, bfd_user_space_pid);
        atomic64_inc(&session->dropped_packets);
        /* Release the ref_counter on session and delete from DB if required */
        sx_bfd_rx_sess_put(session);
        return;
    }

    /* Restart timer */
    rx_delayed_work_dispatch(session);

    /* Update field that identify that we heard from remote side */
    atomic_set(&session->remote_heard, true);


    atomic64_inc(&session->rx_counter);
    current_jiffies = jiffies;
    received_packet_msec = jiffies_to_msecs(current_jiffies);
    session->last_time = received_packet_msec;

    /* Check if this is the packet we are expecting */
    if ((session->packet_len != len) ||
        (memcmp(buf, session->packet, len) != 0)) {
        /* If its not expected packet send it to user space */
        sx_bfd_event_send_packet(session, buf, len, &metadata, bfd_user_space_pid);
    }

    /* Decrement the ref_count of the session and remove it from DB if required */
    sx_bfd_rx_sess_put(session);
}


int sx_bfd_engine_data_init(void)
{
    int err;

    err = sx_bfd_socket_init();
    if (err < 0) {
        printk(KERN_ERR "Kernel BFD socket failed to initialize.\n");
        goto bail;
    }

bail:
    return err;
}

void sx_bfd_engine_data_deinit(void)
{
    sx_bfd_socket_deinit();
}
