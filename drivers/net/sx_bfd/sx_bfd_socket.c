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

#include <linux/kernel.h>
#include <net/inet_sock.h>
#include <linux/version.h>
#include <net/ipv6.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/sched.h>
#include <linux/hash.h>
#include <linux/hashtable.h>
#include <linux/jhash.h>

#include "sx_bfd_socket.h"
#include "sx_bfd_engine_data.h"

#include <linux/sx_bfd/sx_bfd_ctrl_cmds.h>

#define SX_BFD_SINGLEHOP_PORT 3784
#define SX_BFD_MULTIHOP_PORT  4784

#define RX_HDR_IPPROTO_IP         (1 << 0)
#define RX_HDR_IPPROTO_IP_TTL     (1 << 1)
#define RX_HDR_IPPROTO_IP_PKTINFO (1 << 2)
#define RX_HDR_IPV4_COMPLETE      (RX_HDR_IPPROTO_IP | RX_HDR_IPPROTO_IP_TTL | RX_HDR_IPPROTO_IP_PKTINFO)

#define RX_HDR_IPPROTO_IPV6          (1 << 3)
#define RX_HDR_IPPROTO_IPV6_HOPLIMIT (1 << 4)
#define RX_HDR_IPPROTO_IPV6_PKTINFO  (1 << 5)
#define RX_HDR_IPV6_COMPLETE         (RX_HDR_IPPROTO_IPV6 | RX_HDR_IPPROTO_IPV6_HOPLIMIT | RX_HDR_IPPROTO_IPV6_PKTINFO)

#define HDR_RX_STATE_OK(hdr_state)                                     \
    ((((hdr_state) & RX_HDR_IPV4_COMPLETE) == RX_HDR_IPV4_COMPLETE) || \
     (((hdr_state) & RX_HDR_IPV6_COMPLETE) == RX_HDR_IPV6_COMPLETE))

#define SX_RX_VRFS_HASH_BITS 8
DECLARE_HASHTABLE(rx_vrfs, SX_RX_VRFS_HASH_BITS);

enum sx_bfd_sock_state {
    sx_bfd_sock_state_work = 0,
    sx_bfd_sock_state_dead,
};
struct rx_session_ip_vrf_hash {
    int vrf_id;
    union {
        struct in_addr  ipv4;
        struct in6_addr ipv6;
    };
};
struct sx_bfd_rx_vrf {
    struct socket *sock_single_hop;
    struct socket *sock_multi_hop;
    uint32_t       ref_count;
    uint32_t       vrf_id;
    int            deleted;
};
struct sx_bfd_rx_vrf_entry {
    struct hlist_node     node;
    struct sx_bfd_rx_vrf *vrf;
    uint32_t              vrf_id;
};

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
typedef void (*sk_data_ready_origin)(struct sock *sk, int bytes);
typedef void (*sk_destruct_origin)(struct sock *sk);
#else
typedef void (*sk_data_ready_origin)(struct sock *sk);
typedef void (*sk_destruct_origin)(struct sock *sk);
#endif

struct sx_bfd_rx_socket_user_info {
    uint32_t               vrf_id;
    unsigned long          bfd_user_space_pid;
    sk_data_ready_origin   sk_data_ready_origin_cb;
    sk_destruct_origin     sk_destruct_origin_cb;
    struct list_head       list;
    int                    ref_count;
    struct socket         *t_sock;
    enum sx_bfd_sock_type  sock_type;
    enum sx_bfd_sock_state sock_state;
    struct completion      free_wait;
};
static bool g_initialized = false;
struct sockets_scheduler {
    struct list_head scheduler_list;
    struct semaphore scheduler_sem;
    spinlock_t       scheduler_lock;
    uint8_t          scheduler_thread_active;
};
static struct sockets_scheduler scheduler;
static struct task_struct      *bfd_thread = NULL;

/* Function which sends traffic when timeout event on Tx session occurs */
bool sx_bfd_socket_send(struct socket * sock, char* buf, size_t buf_len, struct sockaddr *peer)
{
    int           len = -1;
    struct msghdr msg;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 19, 0))
    struct kvec iov;
#else
    mm_segment_t oldfs;
    struct iovec iov;
#endif


    memset(&iov, 0, sizeof(iov));
    iov.iov_base = buf;
    iov.iov_len = buf_len;

    memset(&msg, 0, sizeof(struct msghdr));
    msg.msg_name = peer;
    if (peer->sa_family == AF_INET) {
        msg.msg_namelen = sizeof(struct sockaddr_in);
    } else {
        msg.msg_namelen = sizeof(struct sockaddr_in6);
    }

 #if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 19, 0))
    len = kernel_sendmsg(sock, &msg, &iov, 1, iov.iov_len);
#else
    oldfs = get_fs();
    set_fs(KERNEL_DS);

    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    len = sock_sendmsg(sock, &msg, iov.iov_len);
    set_fs(oldfs);
#endif
    if (len < 0) {
        return false;
    }

    return true;
}


/* Function which receives data on the specified socket and fills
 * metadata parameters. */
int sx_bfd_socket_recv(struct socket *sock, char* buf, size_t buf_len, struct metadata* metadata)
{
    struct msghdr       msg;
    static char         ctrl_buf[512];
    struct cmsghdr     *cmsghdr = NULL;
    int                 size = 0, hdr_state = 0;
    int                 peer_addr_size;
    struct sockaddr_in  peer_in;
    struct in_pktinfo  *pkt_info;
    struct in6_pktinfo *pkt_info6;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 19, 0))
    struct kvec iov;
#else
    mm_segment_t oldfs;
    struct iovec iov;
#endif

    memset(metadata, 0, sizeof(struct metadata));

    if ((sock == NULL) || (sock->sk == NULL)) {
        return -EIO;
    }

    /* Prepare IOV */
    memset(&iov, 0, sizeof(iov));
    iov.iov_base = buf;
    iov.iov_len = buf_len;

    /* Prepare Message */
    msg.msg_control = ctrl_buf;
    msg.msg_controllen = sizeof(ctrl_buf);
    msg.msg_flags = 0;
    msg.msg_name = &metadata->peer_addr;
    msg.msg_namelen = sizeof(metadata->peer_addr);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 19, 0))

    /* get_fs && set_fs called inside the function */
    size = kernel_recvmsg(sock, &msg, &iov, 1,
                          iov.iov_len, msg.msg_flags);
#else
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    oldfs = get_fs();
    set_fs(KERNEL_DS);


    size = sock_recvmsg(sock, &msg, iov.iov_len, msg.msg_flags);

    set_fs(oldfs);
#endif

    if (size <= 0) {
        goto bail;
    }
    /* After receiving the packet the ctrl_buf needs to be re-initialized */
    msg.msg_control = ctrl_buf;
    msg.msg_controllen = sizeof(ctrl_buf);

    for (cmsghdr = CMSG_FIRSTHDR(&msg); cmsghdr != NULL; cmsghdr = CMSG_NXTHDR(&msg, cmsghdr)) {
        if (!CMSG_OK(&msg, cmsghdr)) {
            if (HDR_RX_STATE_OK(hdr_state)) {
                break;
            }
            return -EIO;
        }


        if (cmsghdr->cmsg_level == IPPROTO_IP) {
            hdr_state |= RX_HDR_IPPROTO_IP;

            if (cmsghdr->cmsg_type == IP_TTL) {
                hdr_state |= RX_HDR_IPPROTO_IP_TTL;
                metadata->ttl = *(int*)CMSG_DATA(cmsghdr);
            }
            if (cmsghdr->cmsg_type == IP_PKTINFO) {
                hdr_state |= RX_HDR_IPPROTO_IP_PKTINFO;
                pkt_info = (struct in_pktinfo *)CMSG_DATA(cmsghdr);
                metadata->inbound_id = pkt_info->ipi_ifindex;
                metadata->local_addr.local_in.sin_family = AF_INET;
                memcpy(&metadata->local_addr.local_in.sin_addr,
                       &pkt_info->ipi_addr,
                       sizeof(struct in_addr));
            }
        } else if (cmsghdr->cmsg_level == IPPROTO_IPV6) {
            hdr_state |= RX_HDR_IPPROTO_IPV6;
            if (cmsghdr->cmsg_type == IPV6_HOPLIMIT) {
                hdr_state |= RX_HDR_IPPROTO_IPV6_HOPLIMIT;
                metadata->ttl = *(int*)CMSG_DATA(cmsghdr);
            }
            if (cmsghdr->cmsg_type == IPV6_PKTINFO) {
                hdr_state |= RX_HDR_IPPROTO_IPV6_PKTINFO;
                pkt_info6 = (struct in6_pktinfo *)CMSG_DATA(cmsghdr);
                metadata->inbound_id = pkt_info6->ipi6_ifindex;
                metadata->local_addr.local_in6.sin6_family = AF_INET6;
                memcpy(&metadata->local_addr.local_in6.sin6_addr,
                       &pkt_info6->ipi6_addr,
                       sizeof(struct in6_addr));
            }
        }
    }

    /* Peer address */
    sock->ops->getname(sock, (struct sockaddr *)&metadata->peer_addr,
                       &peer_addr_size, 1);

    if (ipv6_addr_type(&(metadata->peer_addr.peer_in6.sin6_addr)) == IPV6_ADDR_MAPPED) {
        memset(&peer_in, 0, sizeof(struct sockaddr_in));
        peer_in.sin_family = AF_INET;
        memcpy(&peer_in.sin_addr,
               (char*)&(metadata->peer_addr.peer_in6.sin6_addr) + 12,
               4);
        memcpy(&metadata->peer_addr.peer_in, &peer_in, sizeof(struct sockaddr_in));
    }

bail:
    return size;
}

/* User specific callback which is called from
 * Linux to show that there is data received on this socket*/
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
static void sk_data_ready_custom(struct sock *sk, int bytes)
#else
static void sk_data_ready_custom(struct sock *sk)
#endif
{
    struct sx_bfd_rx_socket_user_info *user_info = NULL;
    int                                lst_empty = 0;

    /* Lock scheduler DS from other manipulation on this DS */
    spin_lock_bh(&scheduler.scheduler_lock);

    /*Get user_info which is saved in creation of the socket. */
    if (sk && sk->sk_user_data) {
        user_info = (struct sx_bfd_rx_socket_user_info *)sk->sk_user_data;
    }

    if (user_info) {
        if (user_info->sk_data_ready_origin_cb) {
            /* Call original Linux define function which is initialized in
             * socket_create function. */
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
            user_info->sk_data_ready_origin_cb(sk, bytes);
#else
            user_info->sk_data_ready_origin_cb(sk);
#endif
        }
        if (user_info->sock_state == sx_bfd_sock_state_dead) {
            /* If socket signed as DEAD - means there is process of delete socket -
             * don't take care. */
            spin_unlock_bh(&scheduler.scheduler_lock);
            return;
        }

        /* Check if the LL of sockets on which received data is empty. */
        lst_empty = list_empty(&scheduler.scheduler_list);

        /* Check if other data is waiting on this socket. */
        if (user_info->ref_count == 0) {
            /* If this arrived data (frame) is the only one -
             * add this socket to the LL sockets which should be managed. */
            list_add_tail(&user_info->list, &scheduler.scheduler_list);
        }

        /* Update counter on the packets on this socket. */
        user_info->ref_count++;

        if (lst_empty) {
            /*If LL of the sockets was empty - wake up the thread which sleep
             * if the LL of the sockets is empty. */
            up(&scheduler.scheduler_sem);
        }


        /* increment ref_counter of the socket - important when sock_destroy
         * function was called. Actually socket won't be destroyed if ref_counter
         * on socket is not 0. */
        sock_hold(sk);
    }
    /* Unlock scheduler DS to allow other manipulation on this DS */
    spin_unlock_bh(&scheduler.scheduler_lock);
}


/* Function which is called by thread */
int sk_thread_sockets_scheduler(void *data)
{
    struct sx_bfd_rx_socket_user_info *user_info = NULL;

    scheduler.scheduler_thread_active = 1;

    while (scheduler.scheduler_thread_active) {
        /* Lock scheduler DS from other manipulation on this DS */
        spin_lock_bh(&scheduler.scheduler_lock);
        /* Get the entry from LL of the sockets to be manged  */
        user_info = list_first_entry_or_null(&scheduler.scheduler_list, struct sx_bfd_rx_socket_user_info, list);
        /* Unlock scheduler DS to allow other manipulation on this DS */
        spin_unlock_bh(&scheduler.scheduler_lock);
        if (user_info) {
            BUG_ON(user_info->t_sock == NULL);
            BUG_ON(user_info->t_sock->sk == NULL);

            /*Call to the function which get real packet on the socket and
             * process it as required. */
            recv_packet(user_info->t_sock, user_info->sock_type, user_info->vrf_id, user_info->bfd_user_space_pid);

            /* Decrement ref_counter of the socket - important when sock_destroy
             * function was called. Actually socket won't be destroyed if ref_counter
             * on socket is not 0. */
            sock_put(user_info->t_sock->sk);

            /* Lock scheduler DS from other manipulation on this DS */
            spin_lock_bh(&scheduler.scheduler_lock);

            /* Decrement the number of packets waiting on this specific socket
             * being on the head of the LL  - as now we are going to manage
             * this frame*/
            user_info->ref_count--;

            if (user_info->ref_count == 0) {
                if (user_info->sock_state == sx_bfd_sock_state_dead) {
                    /* If the socket was signed as DEAD (means that there is delete socket process waiting -
                     * sign to this process that socket can be released */
                    complete(&user_info->free_wait);
                }
                /* If this is the only frame (which we are going to take care
                 * in a minute - delete this socket from the LL. */
                list_del_init(&user_info->list);
            } else {
                /*If more packets are waiting on this socket - move the socket
                 * to the tail. Avoid preemption - when one socket can be
                 * taken care all time - when other are waiting.
                 * Managing kind of RR*/
                list_move_tail(&user_info->list, &scheduler.scheduler_list);
            }
            /* Unlock scheduler DS to allow other manipulation on this DS */
            spin_unlock_bh(&scheduler.scheduler_lock);
        } else {
            /* Wait on scheduler_sem which will be "upped" by
             * sk_data_ready_custom callback when any socket notification
             * Rx Data will be arrived. */
            if (down_interruptible(&scheduler.scheduler_sem)) {
                printk(KERN_ERR "unexpected return value of down_timeout \n");
            }

            if (!scheduler.scheduler_thread_active) {
                break;
            }
        }
    }

    return 0;
}

/* Callback which allows to free all allocated user resources before
 * real socket_destroy */
void sk_user_destruct(struct sock *sk)
{
    struct sx_bfd_rx_socket_user_info * user_info;
    sk_destruct_origin                  sk_destruct_origin_cb = NULL;

    if (sk && sk->sk_user_data) {
        user_info = sk->sk_user_data;
        sk_destruct_origin_cb = user_info->sk_destruct_origin_cb;
        kfree(user_info);
        sk->sk_user_data = NULL;
        if (sk_destruct_origin_cb) {
            sk_destruct_origin_cb(sk);
        }
    }
}

static int sk_bfd_socket_bindtodevice(struct socket *sock, char *linux_vrf_name)
{
    int          err = 0;
    mm_segment_t oldfs;

    if (linux_vrf_name == NULL) {
        err = -EIO;
        goto bail;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);

    err = sock_setsockopt(sock,
                          SOL_SOCKET,
                          SO_BINDTODEVICE,
                          linux_vrf_name, BFD_LINUX_VRF_NAME_LENGTH);
    if (err < 0) {
        printk(KERN_WARNING "Failed to set BFD socket SO_BINDTODEVICE option. Err = %d\n", err);
    }

    set_fs(oldfs);

bail:
    return err;
}

int sx_bfd_rx_socket_init(uint16_t         port,
                          struct socket ** sock,
                          uint32_t         vrf_id,
                          unsigned long    bfd_user_space_pid,
                          uint8_t          use_vrf_device,
                          char            *linux_vrf_name)
{
    int                                err = 0;
    struct sockaddr_in6                s6addr;
    int                                value = 1;
    mm_segment_t                       oldfs;
    struct socket                    * t_sock;
    struct timeval                     time;
    struct sx_bfd_rx_socket_user_info *sk_user_data = NULL;
    int                                rcvbuf;

    if (linux_vrf_name == NULL) {
        printk(KERN_ERR "Unexpected NULL <linux_vrf_name>.\n");
        return -EIO;
    }

    /* Create Socket */
    if (sock_create(AF_INET6, SOCK_DGRAM, IPPROTO_UDP, &t_sock) < 0) {
        printk(KERN_ERR "Failed to create BFD socket.\n");
        return -EIO;
    }

    if (use_vrf_device) {
        if (sk_bfd_socket_bindtodevice(t_sock, linux_vrf_name) < 0) {
            printk(KERN_ERR "Failed to bind rx BFD socket to vrf device: %s.\n", linux_vrf_name);
            return -EIO;
        }
    }

    /* Set reuse flag */
    t_sock->sk->sk_reuse = 1;

    /* Fill user data with parameters which are useful when we get
     * sk_data_ready - function which shows that the specific socket is scheduled
     * to show that there is data on socket */
    sk_user_data = kmalloc(sizeof(struct sx_bfd_rx_socket_user_info), GFP_KERNEL);
    if (sk_user_data == NULL) {
        printk(KERN_ERR "Failed to allocate sk_user_data.\n");
        err = -ENOMEM;
        return err;
    }
    memset(sk_user_data, 0, sizeof(struct sx_bfd_rx_socket_user_info));
    sk_user_data->sock_state = sx_bfd_sock_state_work;
    sk_user_data->vrf_id = vrf_id;
    sk_user_data->bfd_user_space_pid = bfd_user_space_pid;
    sk_user_data->t_sock = t_sock;
    sk_user_data->sock_type = (port == SX_BFD_SINGLEHOP_PORT) ? sx_bfd_SOCK_SINGLEHOP : sx_bfd_SOCK_MULTIHOP;
    INIT_LIST_HEAD(&sk_user_data->list);
    init_completion(&sk_user_data->free_wait);

    /* Save origin sk_data_ready to use it in user sk_data_ready */
    sk_user_data->sk_data_ready_origin_cb = t_sock->sk->sk_data_ready;

    /* Save origin sk_destruct to use it in user sk_destruct */
    sk_user_data->sk_destruct_origin_cb = t_sock->sk->sk_destruct;

    /* Update socket sk_user_data with user specific DS which will be used in
     * callback function sk_data_ready */
    t_sock->sk->sk_user_data = sk_user_data;
    /* Update socket sk_data_ready with user specific callback which is called from
     * Linux to show that there is data received on this socket*/
    t_sock->sk->sk_data_ready = sk_data_ready_custom;
    /* Update socket sk_destruct with user specific callback which allows to free
     * all allocated user resources before real socket_destroy */
    t_sock->sk->sk_destruct = sk_user_destruct;

    /* bind to port */
    s6addr.sin6_family = AF_INET6;
    ipv6_addr_set(&s6addr.sin6_addr, 0, 0, 0, 0);
    s6addr.sin6_port = htons(port);
    if (t_sock->ops->bind(t_sock,
                          (struct sockaddr *)&s6addr,
                          sizeof(struct sockaddr_in6)) < 0) {
        printk(KERN_ERR "Failed to bind BFD socket to port %d.\n", port);
        return -EIO;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);

    /* set IP_RECVTTL option */
    if (t_sock->ops->setsockopt(t_sock,
                                IPPROTO_IP,
                                IP_RECVTTL,
                                (char*)&value,
                                sizeof(value)) < 0) {
        printk(KERN_WARNING "Failed to set BFD socket IP_RECVTTL option.\n");
    }

    /* set IPV6_RECVHOPLIMIT option */
    if (t_sock->ops->setsockopt(t_sock,
                                IPPROTO_IPV6,
                                IPV6_RECVHOPLIMIT,
                                (char*)&value,
                                sizeof(value)) < 0) {
        printk(KERN_WARNING "Failed to set BFD socket IPV6_RECVHOPLIMIT option.\n");
    }

    /* set IP_PKTINFO option */
    if (t_sock->ops->setsockopt(t_sock,
                                IPPROTO_IP,
                                IP_PKTINFO,
                                (char*)&value,
                                sizeof(value)) < 0) {
        printk(KERN_WARNING "Failed to set BFD socket IP_PKTINFO option.\n");
    }

    /* set IPV6_RECVPKTINFO option */
    if (t_sock->ops->setsockopt(t_sock,
                                IPPROTO_IPV6,
                                IPV6_RECVPKTINFO,
                                (char*)&value,
                                sizeof(value)) < 0) {
        printk(KERN_WARNING "Failed to set BFD socket IPV6_RECVPKTINFO option.\n");
    }

    /* set SO_RCVTIMEO option */
    time.tv_sec = 0;
    time.tv_usec = 20000;
    if (sock_setsockopt(t_sock,
                        SOL_SOCKET,
                        SO_RCVTIMEO,
                        (char*)&time,
                        sizeof(time)) < 0) {
        printk(KERN_WARNING "Failed to set BFD socket SO_RCVTIMEO option.\n");
    }

    rcvbuf = 4096 * 4096;
    if (sock_setsockopt(t_sock, SOL_SOCKET, SO_RCVBUFFORCE,
                        (char*)&rcvbuf, sizeof(rcvbuf))) {
        printk(KERN_WARNING "setting %d-byte socket receive buffer failed",
               rcvbuf);
    }

    set_fs(oldfs);

    *sock = t_sock;

    return 0;
}

int sx_bfd_tx_socket_create(struct sockaddr * local_addr,
                            uint8_t           ttl,
                            uint8_t           dscp,
                            struct socket  ** sock,
                            uint16_t          sa_family,
                            uint8_t           use_vrf_device,
                            char            * linux_vrf_name)
{
    uint32_t        addr_size;
    struct socket * t_sock = NULL;
    int             err = 0;

    if (local_addr == NULL) {
        printk(KERN_ERR "Unexpected NULL <local_addr>.\n");
        err = -EIO;
        goto bail;
    }

    if (sock == NULL) {
        printk(KERN_ERR "Unexpected NULL <sock>.\n");
        err = -EIO;
        goto bail;
    }

    if (linux_vrf_name == NULL) {
        printk(KERN_ERR "Unexpected NULL <linux_vrf_name>.\n");
        err = -EIO;
        goto bail;
    }

    /* Create Socket */
    if (sock_create(sa_family, SOCK_DGRAM, IPPROTO_UDP, &t_sock) < 0) {
        printk(KERN_ERR "Failed to create BFD socket.\n");
        err = -EIO;
        goto bail;
    }

    if (use_vrf_device) {
        if (sk_bfd_socket_bindtodevice(t_sock, linux_vrf_name) < 0) {
            printk(KERN_ERR "Failed to bind tx BFD socket to vrf device: %s.\n", linux_vrf_name);
            err = -EIO;
            goto bail;
        }
    }

    addr_size = (sa_family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
    if (t_sock->ops->bind(t_sock,
                          local_addr,
                          addr_size) < 0) {
        printk(KERN_ERR "Failed to bind BFD socket, non exist IP address.\n");
        err = -EIO;
        goto bail;
    }

    /* set TTL */
    inet_sk(t_sock->sk)->uc_ttl = ttl;
    if (sa_family == AF_INET6) {
        inet_sk(t_sock->sk)->pinet6->hop_limit = ttl;
    }

    /* set DSCP */
    inet_sk(t_sock->sk)->tos = dscp;
    if (sa_family == AF_INET6) {
        inet_sk(t_sock->sk)->pinet6->tclass = dscp;
    }

    *sock = t_sock;

    t_sock = NULL;

bail:
    if (t_sock) {
        sock_release(t_sock);
    }
    return err;
}

static unsigned long vrf_id_hash(uint32_t vrf_id)
{
    return jhash(&vrf_id, sizeof(vrf_id), 0);
}

static struct sx_bfd_rx_vrf_entry * sx_bfd_rx_vrf_lkp_entry_by_vrf_id(uint32_t vrf_id)
{
    static struct sx_bfd_rx_vrf_entry * entry;
    unsigned long                       hash_key = vrf_id_hash(vrf_id);

    hash_for_each_possible(rx_vrfs, entry, node, hash_key) {
        if (entry->vrf_id == vrf_id) {
            return entry;
        }
    }

    return NULL;
}

void * sx_bfd_rx_vrf_entry_lkp_by_vrf_id(uint32_t vrf_id)
{
    static struct sx_bfd_rx_vrf_entry * entry;
    unsigned long                       hash_key = vrf_id_hash(vrf_id);

    hash_for_each_possible(rx_vrfs, entry, node, hash_key) {
        if (entry->vrf_id == vrf_id) {
            return entry;
        }
    }

    return NULL;
}

void sx_bfd_rx_vrf_entry_free_if_needed(void *rx_vrf_entry)
{
    struct sx_bfd_rx_vrf_entry * entry_vrf = (struct sx_bfd_rx_vrf_entry *)rx_vrf_entry;

    if (entry_vrf && entry_vrf->vrf->deleted) {
        printk(KERN_DEBUG "VRF %d DELETED.\n", entry_vrf->vrf_id);
        sx_bfd_rx_socket_destroy(entry_vrf->vrf->sock_single_hop);
        sx_bfd_rx_socket_destroy(entry_vrf->vrf->sock_multi_hop);
        kfree(entry_vrf->vrf);
        kfree(entry_vrf);
    }
}

void sx_bfd_rx_vrf_hash_add(void *rx_vrf_entry)
{
    struct sx_bfd_rx_vrf_entry *entry_vrf = (struct sx_bfd_rx_vrf_entry *)rx_vrf_entry;
    unsigned long               hash_key_vrf;

    BUG_ON(entry_vrf == NULL);
    hash_key_vrf = vrf_id_hash(entry_vrf->vrf_id);
    /* Add VRF to the VRFs DB */
    hash_add(rx_vrfs,
             &entry_vrf->node,
             hash_key_vrf);
    printk(KERN_DEBUG "VRF %d ADDED.\n", entry_vrf->vrf_id);
}

/* Function which initializes VRF. */
void * sx_bfd_rx_vrf_init(uint32_t vrf_id, uint8_t use_vrf_device, char *linux_vrf_name, unsigned long bfd_pid)
{
    struct sx_bfd_rx_vrf       *vrf = NULL;
    struct sx_bfd_rx_vrf_entry *entry_vrf = NULL;
    struct sx_bfd_rx_vrf_entry *entry_vrf_ret = NULL;
    int                         err = 0;

    /* Allocate VRF DS. */
    vrf = kmalloc(sizeof(struct sx_bfd_rx_vrf), GFP_KERNEL);
    if (!vrf) {
        printk(KERN_ERR "Failed to allocate VRF DS.\n");
        err = -ENOMEM;
        goto bail;
    }
    memset(vrf, 0, sizeof(struct sx_bfd_rx_vrf));

    /* Allocate Entry_vrf DS. */
    entry_vrf = kmalloc(sizeof(struct sx_bfd_rx_vrf_entry), GFP_KERNEL);
    if (!entry_vrf) {
        printk(KERN_ERR "Create RX entry session VRF failed.\n");
        err = -ENOMEM;
        goto bail;
    }
    memset(entry_vrf, 0, sizeof(struct sx_bfd_rx_vrf_entry));

    /* Update fields of DS */
    vrf->ref_count = 1;
    vrf->vrf_id = vrf_id;

    /* Initialize Rx_socket for single_port. */
    err = sx_bfd_rx_socket_init(SX_BFD_SINGLEHOP_PORT,
                                &vrf->sock_single_hop,
                                vrf->vrf_id,
                                bfd_pid,
                                use_vrf_device,
                                linux_vrf_name);
    if (err) {
        printk(KERN_ERR "Create SX_BFD_SINGLEHOP_PORT socket failed.\n");
        err = -EIO;
        goto bail;
    }

    /* Initialize Rx_socket for multihop_port. */
    err = sx_bfd_rx_socket_init(SX_BFD_MULTIHOP_PORT,
                                &vrf->sock_multi_hop,
                                vrf->vrf_id,
                                bfd_pid,
                                use_vrf_device,
                                linux_vrf_name);
    if (err) {
        printk(KERN_ERR "Create SX_BFD_MULTIHOP_PORT socket failed.\n");
        err = -EIO;
        goto bail;
    }

    /* Update fields of entry_vrf DS */
    INIT_HLIST_NODE(&entry_vrf->node);
    entry_vrf->vrf_id = vrf_id;
    entry_vrf->vrf = vrf;

    entry_vrf_ret = entry_vrf;
    entry_vrf = NULL;
    vrf = NULL;

bail:
    if (vrf) {
        if (vrf->sock_single_hop) {
            sx_bfd_rx_socket_destroy(vrf->sock_single_hop);
        }
        if (vrf->sock_multi_hop) {
            sx_bfd_rx_socket_destroy(vrf->sock_multi_hop);
        }

        kfree(vrf);
    }

    if (entry_vrf) {
        kfree(entry_vrf);
    }

    return entry_vrf_ret;
}

void sx_bfd_rx_vrf_get(uint32_t vrf_id)
{
    struct sx_bfd_rx_vrf_entry * entry_vrf = NULL;

    entry_vrf = sx_bfd_rx_vrf_lkp_entry_by_vrf_id(vrf_id);

    BUG_ON(entry_vrf == NULL);
    if (entry_vrf) {
        entry_vrf->vrf->ref_count++;
    }
}

int sx_bfd_rx_vrf_is_sock_same(uint32_t vrf_id, struct socket *sock)
{
    struct sx_bfd_rx_vrf_entry * entry_vrf = NULL;

    entry_vrf = sx_bfd_rx_vrf_lkp_entry_by_vrf_id(vrf_id);
    BUG_ON(entry_vrf == NULL);
    BUG_ON(entry_vrf->vrf == NULL);

    if (((entry_vrf->vrf->sock_single_hop == sock) && (entry_vrf->vrf->sock_single_hop->sk == sock->sk)) ||
        ((entry_vrf->vrf->sock_multi_hop == sock) && (entry_vrf->vrf->sock_multi_hop->sk == sock->sk))) {
        return 1;
    }

    return 0;
}

void sx_bfd_rx_vrf_put(uint32_t vrf_id, int delete)
{
    struct sx_bfd_rx_vrf_entry * entry_vrf = NULL;

    entry_vrf = sx_bfd_rx_vrf_lkp_entry_by_vrf_id(vrf_id);

    if (entry_vrf) {
        entry_vrf->vrf->ref_count--;
        if (delete) {
            if (entry_vrf->vrf->ref_count == 0) {
                hash_del(&entry_vrf->node);
                entry_vrf->vrf->deleted = 1;
            }
        }
    }
}

void sx_bfd_tx_socket_destroy(struct socket * sock)
{
    sock_release(sock);
}

void sx_bfd_rx_socket_destroy(struct socket * sock)
{
    struct sx_bfd_rx_socket_user_info *sk_user_data = NULL;
    int                                wait = 1;

    /* Lock scheduler DS from other manipulation on this DS */
    spin_lock_bh(&scheduler.scheduler_lock);
    BUG_ON(sock == NULL);
    BUG_ON(sock->sk == NULL);
    sk_user_data = (struct sx_bfd_rx_socket_user_info *)sock->sk->sk_user_data;
    BUG_ON(sk_user_data == NULL);
    sk_user_data->sock_state = sx_bfd_sock_state_dead;
    wait = (sk_user_data->ref_count == 0) ? 0 : 1;
    spin_unlock_bh(&scheduler.scheduler_lock);
    /* Wait to notification from sx_bfd_rx_sess_put_no_lock that
     * no one is looking on rx_session*/
    if (wait) {
        wait_for_completion(&sk_user_data->free_wait);
    }
    sock_release(sock);
}

int sx_bfd_socket_init(void)
{
    int err = 0;

    if (!g_initialized) {
        INIT_LIST_HEAD(&scheduler.scheduler_list);
        sema_init(&scheduler.scheduler_sem, 0);
        spin_lock_init(&scheduler.scheduler_lock);

        if (bfd_thread == NULL) {
            bfd_thread = kthread_run(sk_thread_sockets_scheduler, (void*)NULL, "BFD thread");
            if (bfd_thread == NULL) {
                printk(KERN_ERR "Kernel BFD single-hop thread failed to start.\n");
                err = PTR_ERR(bfd_thread);
                goto bail;
            }
        }
        hash_init(rx_vrfs);

        g_initialized = true;
    }

bail:
    return err;

    return err;
}

void sx_bfd_socket_deinit(void)
{
    if (g_initialized) {
        scheduler.scheduler_thread_active = 0;
        up(&scheduler.scheduler_sem);
        kthread_stop(bfd_thread);

        g_initialized = false;
    }
}
