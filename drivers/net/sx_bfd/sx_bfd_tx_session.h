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

#ifndef __SX_BFD_TX_SESSION_H_
#define __SX_BFD_TX_SESSION_H_

#include <net/sock.h>
#include  <linux/completion.h>
#include  <linux/atomic.h>
#include "sx_bfd_workqueue.h"
#include <linux/sx_bfd/sx_bfd_ctrl_cmds.h>

struct sx_bfd_tx_session {
    uint32_t                vrf_id;
    uint32_t                session_id;
    uint8_t                 deleted;
    struct completion       free_wait;
    char                   *packet;
    uint32_t                packet_len;
    uint32_t                interval;
    sx_bfd_delayed_work_t * dwork;
    uint32_t                ref_count;
    struct socket         * sock;

    union {
        struct sockaddr_in  peer_in;
        struct sockaddr_in6 peer_in6;
    } peer_addr;

    atomic64_t    tx_counter;
    uint64_t      last_time; /* last time session sent a packet (msec) */
    unsigned long bfd_pid;
#if 0
    uint64_t interval_min;
    uint64_t interval_max;
    uint64_t interval_average;
#endif
};
struct sx_bfd_tx_session_entry {
    struct hlist_node         node;
    struct sx_bfd_tx_session *sess;
    uint32_t                  session_id;
};

int sx_bfd_tx_session_init(void);

int sx_bfd_tx_session_deinit(void);

int sx_bfd_tx_sess_add(char* session_params, void* stats);

struct sx_bfd_tx_session * sx_bfd_tx_sess_get(uint32_t session_id);

int sx_bfd_tx_sess_del(char *data, void* stats);

int sx_bfd_get_tx_sess_stats(char * data, uint8_t clear_stats);

int sx_bfd_tx_sess_update(char* session_params);

#endif /* __SX_BFD_TX_SESSION_H_ */
