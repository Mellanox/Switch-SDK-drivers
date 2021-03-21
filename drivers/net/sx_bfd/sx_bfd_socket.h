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

#ifndef __SX_BFD_SOCKET_H_
#define __SX_BFD_SOCKET_H_

#include <net/sock.h>

struct metadata {
    union {
        struct sockaddr_in  peer_in;
        struct sockaddr_in6 peer_in6;
    } peer_addr;
    union {
        struct sockaddr_in  local_in;
        struct sockaddr_in6 local_in6;
    } local_addr;
    int inbound_id;
    int ttl;
};
enum sx_bfd_sock_type {
    sx_bfd_SOCK_SINGLEHOP = 0,
    sx_bfd_SOCK_MULTIHOP,
    sx_bfd_SOCK_NUM
};


bool sx_bfd_socket_send(struct socket * sock, char* buf, size_t buf_len, struct sockaddr *peer);
int sx_bfd_socket_recv(struct socket *sock,
                       char* buf, size_t buf_len, struct metadata* metadata);

int sx_bfd_tx_socket_create(struct sockaddr * local_addr,
                            uint8_t           ttl,
                            uint8_t           dscp,
                            struct socket  ** sock,
                            uint16_t          sa_family,
                            uint8_t           use_vrf_device,
                            char            * linux_vrf_name);
int sx_bfd_rx_socket_init(uint16_t         port,
                          struct socket ** sock,
                          uint32_t         vrf_id,
                          unsigned long    bfd_user_space_pid,
                          uint8_t          use_vrf_device,
                          char            *linux_vrf_name);

void sx_bfd_tx_socket_destroy(struct socket * sock);
void sx_bfd_rx_socket_destroy(struct socket * sock);

int sx_bfd_socket_init(void);
void sx_bfd_socket_deinit(void);

void sx_bfd_rx_vrf_get(uint32_t vrf_id);
void sx_bfd_rx_vrf_put(uint32_t vrf_id, int delete);
void * sx_bfd_rx_vrf_init(uint32_t vrf_id, uint8_t use_vrf_device, char *linux_vrf_name, unsigned long bfd_pid);
void sx_bfd_rx_vrf_entry_free_if_needed(void *rx_vrf_entry);
void * sx_bfd_rx_vrf_entry_lkp_by_vrf_id(uint32_t vrf_id);
void sx_bfd_rx_vrf_hash_add(void *rx_vrf_entry);
int sx_bfd_rx_vrf_is_sock_same(uint32_t vrf_id, struct socket *sock);


#endif /* __SX_BFD_SOCKET_H_ */
