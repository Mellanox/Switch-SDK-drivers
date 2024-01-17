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
