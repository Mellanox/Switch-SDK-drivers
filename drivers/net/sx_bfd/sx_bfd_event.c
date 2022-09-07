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

#include <linux/kernel.h>

#include "sx_bfd_event.h"
#include <linux/sx_bfd/sx_bfd_ctrl_cmds.h>
#include <linux/mlx_sx/kernel_user.h>

#define SX_BFD_USER_PORT 3786

extern int send_trap(const void    *buf,
                     const uint32_t buf_size,
                     uint16_t       trap_id,
                     u8             is_from_user,
                     u8             device_id,
                     pid_t          target_pid,
                     gfp_t          gfp_mask);

void sx_bfd_event_send_packet(struct sx_bfd_rx_session *session,
                              char                     *packet,
                              uint32_t                  size,
                              struct metadata          *metadata,
                              unsigned long             bfd_user_space_pid)
{
    struct bfd_packet_event *event_msg = NULL;
    uint8_t                  family;
    int                      event_msg_size = 0;

    /*calculate the size of the packet which will be sent via packet event
     * which include not only packet received on the socket but additional
     * parameters which user space BFD stack will use
     */
    event_msg_size = sizeof(struct bfd_packet_event) + size;

    /* Allocate event_msg to send via packet trap*/
    event_msg = kmalloc(event_msg_size, GFP_ATOMIC);
    if (!event_msg) {
        printk(KERN_ERR "event_msg allocation failed (event_msg_size:%d, pkt_size:%d).\n",
               event_msg_size, size);
        goto out;
    }

    /* Fill all relevant information. */
    event_msg->timeout = 0;
    if (session) {
        /*Session exists*/
        /* session_id - kernel uses and will be used by Update session in Kernel
         * when the response from user space will come */
        event_msg->session_id = session->session_id;
        /* opaque_data_valid - Show to user space BFD stack that the session exists*/
        event_msg->opaque_data_valid = 1;
        /* opaque_data - the identify user space BFD stack uses for managing BFD*/
        event_msg->opaque_data = session->session_opaque_data;
    } else {
        /* Session doesn't exist*/
        /* opaque_data_valid - Show to user space BFD stack that the session
         *  doesn't exist*/
        event_msg->opaque_data_valid = 0;
    }

    /* bfd_pid - to show to user space what VRF context is used*/
    event_msg->bfd_pid = bfd_user_space_pid;

    /* Fill address received from the frame */
    family = ((struct sockaddr*)&metadata->peer_addr)->sa_family;
    if (family == AF_INET) {
        event_msg->peer_addr.peer_in.sin_family = AF_INET;
        memcpy(&event_msg->peer_addr.peer_in.sin_addr, &metadata->peer_addr.peer_in.sin_addr, sizeof(struct in_addr));
        event_msg->peer_addr.peer_in.sin_port = metadata->peer_addr.peer_in.sin_port;
    } else {
        event_msg->peer_addr.peer_in.sin_family = AF_INET6;
        memcpy(&event_msg->peer_addr.peer_in6.sin6_addr, &metadata->peer_addr.peer_in6.sin6_addr,
               sizeof(struct in6_addr));
        event_msg->peer_addr.peer_in6.sin6_port = metadata->peer_addr.peer_in6.sin6_port;
    }
    family = ((struct sockaddr*)&metadata->local_addr)->sa_family;
    if (family == AF_INET) {
        event_msg->local_addr.local_in.sin_family = AF_INET;
        memcpy(&event_msg->local_addr.local_in.sin_addr,
               &metadata->local_addr.local_in.sin_addr,
               sizeof(struct in_addr));
        event_msg->local_addr.local_in.sin_port = metadata->local_addr.local_in.sin_port;
    } else {
        event_msg->local_addr.local_in.sin_family = AF_INET6;
        memcpy(&event_msg->local_addr.local_in6.sin6_addr, &metadata->local_addr.local_in6.sin6_addr,
               sizeof(struct in6_addr));
        event_msg->local_addr.local_in6.sin6_port = metadata->local_addr.local_in6.sin6_port;
    }

    /* Fill the rest of required parameters */
    event_msg->ttl = metadata->ttl;
    event_msg->inbound_id = metadata->inbound_id;
    event_msg->packet_size = size;
    memcpy(event_msg->packet, packet, size);

    if (send_trap(event_msg,
                  event_msg_size,
                  SXD_TRAP_ID_BFD_PACKET_EVENT, 0, 1, 0, GFP_ATOMIC) != 0) {
        printk(KERN_ERR "Failed to send data trap 0x%x for session (%d).\n",
               SXD_TRAP_ID_BFD_PACKET_EVENT,
               session ? session->session_id : -1);
    }

out:
    if (event_msg) {
        kfree(event_msg);
    }
}

void sx_bfd_event_send_timeout(struct sx_bfd_rx_session *session)
{
    struct bfd_timeout_event event;

    /* Fill with parameters TIMOUT_EVENT which will be received in user space
     * via trap and taking care in BFD STACK */
    event.session_id = session->session_id;
    event.opaque_data = session->session_opaque_data;
    event.bfd_pid = session->bfd_pid;

    /*Send the trap */
    if (send_trap(&event,
                  sizeof(struct bfd_timeout_event),
                  SXD_TRAP_ID_BFD_TIMEOUT_EVENT, 0, 1, 0, GFP_ATOMIC) != 0) {
        printk(KERN_ERR "Failed to send timeout trap 0x%x for session_id %d and VRF %d.\n",
               SXD_TRAP_ID_BFD_TIMEOUT_EVENT,
               session->session_id, session->vrf_id);
    }
}
