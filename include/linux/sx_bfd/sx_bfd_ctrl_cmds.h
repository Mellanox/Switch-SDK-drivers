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

#ifndef __SX_BFD_CTRL_CMDS_H_
#define __SX_BFD_CTRL_CMDS_H_

#ifdef __KERNEL__
#include <linux/in.h>
#include <linux/in6.h>
#endif

#define BFD_LINUX_VRF_NAME_LENGTH 16

/*
 *  BFD message types
 */
enum sx_bfd_cmd {
    /*
     *  Start BFD TX offloading.
     *  Message format is defined in struct bfd_tx_offload.
     */
    SX_BFD_CMD_START_TX_OFFLOAD,

    /*
     *  Update BFD TX offloading.
     *  Message format is defined in struct bfd_tx_offload.
     */
    SX_BFD_CMD_UPDATE_TX_OFFLOAD,

    /*
     *  DO NOT TOUCH - enum = 2 is not working for ioctl
     */
    SX_BFD_CMD_INVALID,

    /*
     *  Stop TX offloading.
     *  Message format is defined in struct stop_bfd_offload.
     */
    SX_BFD_CMD_STOP_TX_OFFLOAD,

    /*
     *  Start BFD RX offloading.
     *  Message format is defined in struct bfd_rx_offload.
     */
    SX_BFD_CMD_START_RX_OFFLOAD,

    /*
     *  Update BFD RX offloading.
     *  Message format is defined in struct bfd_rx_offload.
     */
    SX_BFD_CMD_UPDATE_RX_OFFLOAD,

    /*
     *  Stop RX offloading.
     *  Message format is defined in struct stop_bfd_offload.
     */
    SX_BFD_CMD_STOP_RX_OFFLOAD,

    /*
     *  Get RX session statistics.
     *  Message format is defined in struct bfd_stats_req.
     */
    SX_BFD_CMD_GET_RX_STATS,

    /*
     *  Get TX session statistics.
     *  Message format is defined in struct bfd_stats_req.
     */
    SX_BFD_CMD_GET_TX_STATS,

    /*
     *  Get & Clear RX session statistics.
     *  Message format is defined in struct bfd_stats_req.
     */
    SX_BFD_CMD_GET_AND_CLEAR_RX_STATS,

    /*
     *  Get & Clear TX session statistics.
     *  Message format is defined in struct bfd_stats_req.
     */
    SX_BFD_CMD_GET_AND_CLEAR_TX_STATS,
};

struct __attribute__((__packed__)) bfd_offload_info {
    int      vrf_id;
    uint8_t  use_vrf_device;
    char     linux_vrf_name[BFD_LINUX_VRF_NAME_LENGTH + 1];
    uint32_t session_id;
    uint64_t session_opaque_data;

    union {
        struct sockaddr_in  local_in;
        struct sockaddr_in6 local_in6;
    } local_addr;

    uint8_t ttl;
    uint8_t dscp;

    /*
     *  Tx, Rx - Peer IP address
     */
    union {
        struct sockaddr_in  peer_in;
        struct sockaddr_in6 peer_in6;
    } peer_addr;

    /*
     *  Interval between BFD control packets
     *  Tx - This is minimum interval (microsec) that local system
     *       should use for transmitting BFD frames. (0 - reserved)
     *  Rx - This is the minimum interval (microsec) between received
     *       BFD Control frames, that this system is capable of supporting.
     *       (0 - No BFD frames to transit from Tx peer system)
     */
    uint32_t interval;

    /*
     *  Length of BFD control packet
     */
    size_t        size;
    unsigned long bfd_pid;
    char          bfd_packet[0];
};

enum bfd_session_type {
    BFD_RX_SESSION,
    BFD_TX_SESSION,
};

struct __attribute__((__packed__)) bfd_offload_session_stats {
    uint64_t num_control;
    uint64_t num_dropped_control;
    uint64_t last_time;
    uint64_t interval_min;
    uint64_t interval_max;
    uint64_t interval_average;
    uint8_t  remote_heard;
};

struct __attribute__((__packed__)) bfd_offload_get_stats {
    uint8_t                          session_type;
    uint32_t                         session_id;
    struct bfd_offload_session_stats session_stats;
};

struct bfd_timeout_event {
    uint32_t      session_id;
    uint64_t      opaque_data;
    unsigned long bfd_pid;
};

struct __attribute__((__packed__)) bfd_packet_event {
    uint32_t session_id;
    uint32_t timeout;
    uint32_t opaque_data_valid;
    uint64_t opaque_data;
    union {
        struct sockaddr_in  peer_in;
        struct sockaddr_in6 peer_in6;
    } peer_addr;
    union {
        struct sockaddr_in  local_in;
        struct sockaddr_in6 local_in6;
    } local_addr;
    int           inbound_id;
    int           ttl;
    unsigned long bfd_pid;
    uint32_t      packet_size;
    char          packet[0];
};


#endif /* __SX_BFD_CTRL_CMDS_H_ */
