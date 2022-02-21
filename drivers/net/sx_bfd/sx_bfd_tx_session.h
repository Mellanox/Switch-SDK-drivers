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
