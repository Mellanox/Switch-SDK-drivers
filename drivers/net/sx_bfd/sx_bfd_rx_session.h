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

#ifndef __SX_BFD_RX_SESSION_H_
#define __SX_BFD_RX_SESSION_H_

#include <net/sock.h>
#include <linux/atomic.h>
#include "sx_bfd_workqueue.h"
#include <linux/sx_bfd/sx_bfd_ctrl_cmds.h>

struct ip_addr {
    uint8_t family;
    union {
        struct in_addr  ipv4;
        struct in6_addr ipv6;
    };
};
struct sx_bfd_rx_session {
    uint32_t                vrf_id;
    uint32_t                session_id;
    uint8_t                 deleted;
    struct completion       free_wait;
    char                   *packet;
    uint32_t                packet_len;
    uint32_t                interval;
    uint32_t                ref_count;
    sx_bfd_delayed_work_t * dwork;
    uint64_t                session_opaque_data;
    struct ip_addr          ip_addr;
    atomic64_t              rx_counter;
    atomic64_t              dropped_packets;
    uint64_t                last_time; /* last time a packet was received */
    atomic_t                remote_heard;
    unsigned long           bfd_pid;
};

int sx_bfd_rx_session_init(void);

int sx_bfd_rx_session_deinit(void);

struct sx_bfd_rx_session * sx_bfd_rx_sess_get_by_ip_vrf(struct ip_addr * ip_addr,
                                                        uint32_t         vrf_id,
                                                        struct socket   *t_sock);
struct sx_bfd_rx_session * sx_bfd_rx_sess_get_by_id(uint32_t session_id);

void sx_bfd_rx_sess_put(struct sx_bfd_rx_session * session);

int sx_bfd_rx_sess_add(char * data);

int sx_bfd_rx_sess_del(char * data);

void rx_delayed_work_dispatch(struct sx_bfd_rx_session * session);

int sx_bfd_get_rx_sess_stats(char* data, uint8_t clear_stats);

int sx_bfd_rx_sess_update(char* data);

#endif /* __SX_BFD_RX_SESSION_H_ */
