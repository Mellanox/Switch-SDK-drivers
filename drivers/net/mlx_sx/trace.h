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

#undef TRACE_SYSTEM
#define TRACE_SYSTEM sx_core

#if !defined(_SX_CORE_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#define _SX_CORE_TRACE_H

#include <linux/tracepoint.h>
#include <linux/skbuff.h>
#include <linux/version.h>

DECLARE_EVENT_CLASS(sx_rdq_rx_agg,
                    TP_PROTO(struct sk_buff *skb, uint16_t trap_id, uint32_t acl_user_id,
                             const struct timespec *timestamp, uint8_t mirror_reason,
                             uint32_t port),

                    TP_ARGS(skb, trap_id, acl_user_id, timestamp, mirror_reason, port),

                    TP_STRUCT__entry(
                        __field(const void *, skb)
                        __field(uint16_t,     trap_id)
                        __field(uint32_t,     acl_user_id)
                        __field(const void *, timestamp)
                        __field(uint8_t,      mirror_reason)
                        __field(uint32_t,     port)
                        ),

                    TP_fast_assign(
                        __entry->skb = skb;
                        __entry->trap_id = trap_id;
                        __entry->acl_user_id = acl_user_id;
                        __entry->timestamp = timestamp;
                        __entry->mirror_reason = mirror_reason;
                        __entry->port = port;
                        ),

                    TP_printk("trap_id %u acl_user_id %u tv_sec %ld tv_nsec %ld mirror_reason %u port %u",
                              __entry->trap_id,
                              __entry->acl_user_id,
                              (long)(((const struct timespec*)__entry->timestamp)->tv_sec),
                              ((const struct timespec*)__entry->timestamp)->tv_nsec,
                              __entry->mirror_reason,
                              __entry->port)
                    );

#define SX_CORE_DEFINE_AGG_EVENT1(rdq_no)                                           \
    DEFINE_EVENT(sx_rdq_rx_agg, sx_rdq_rx_agg_ ## rdq_no,                           \
                 TP_PROTO(struct sk_buff *skb,                                      \
                          uint16_t trap_id,                                         \
                          uint32_t acl_user_id,                                     \
                          const struct timespec *timestamp,                         \
                          uint8_t mirror_reason,                                    \
                          uint32_t port),                                           \
                 TP_ARGS(skb, trap_id, acl_user_id, timestamp, mirror_reason, port) \
                 )

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0))
#define SX_CORE_DEFINE_AGG_EVENT(rdq_no) SX_CORE_DEFINE_AGG_EVENT1(rdq_no)
#else
/*
 * In Linux kernels <= 4.15.0, attaching multiple eBPF programs to a single trace point is not supported,
 * we need to define multiple trace points for each RDQ so as to support attaching multiple eBPF programs
 * to one RDQ.
 */
#define SX_AGG_TRACE_POINT_NUM_PER_RDQ 6
#define SX_CORE_DEFINE_AGG_EVENT(rdq_no)     \
    SX_CORE_DEFINE_AGG_EVENT1(rdq_no ## _0); \
    SX_CORE_DEFINE_AGG_EVENT1(rdq_no ## _1); \
    SX_CORE_DEFINE_AGG_EVENT1(rdq_no ## _2); \
    SX_CORE_DEFINE_AGG_EVENT1(rdq_no ## _3); \
    SX_CORE_DEFINE_AGG_EVENT1(rdq_no ## _4); \
    SX_CORE_DEFINE_AGG_EVENT1(rdq_no ## _5)
#endif

/* When NUMBER_OF_RDQS is modified, please modify the below definitions as well. */
SX_CORE_DEFINE_AGG_EVENT(0);
SX_CORE_DEFINE_AGG_EVENT(1);
SX_CORE_DEFINE_AGG_EVENT(2);
SX_CORE_DEFINE_AGG_EVENT(3);
SX_CORE_DEFINE_AGG_EVENT(4);
SX_CORE_DEFINE_AGG_EVENT(5);
SX_CORE_DEFINE_AGG_EVENT(6);
SX_CORE_DEFINE_AGG_EVENT(7);
SX_CORE_DEFINE_AGG_EVENT(8);
SX_CORE_DEFINE_AGG_EVENT(9);
SX_CORE_DEFINE_AGG_EVENT(10);
SX_CORE_DEFINE_AGG_EVENT(11);
SX_CORE_DEFINE_AGG_EVENT(12);
SX_CORE_DEFINE_AGG_EVENT(13);
SX_CORE_DEFINE_AGG_EVENT(14);
SX_CORE_DEFINE_AGG_EVENT(15);
SX_CORE_DEFINE_AGG_EVENT(16);
SX_CORE_DEFINE_AGG_EVENT(17);
SX_CORE_DEFINE_AGG_EVENT(18);
SX_CORE_DEFINE_AGG_EVENT(19);
SX_CORE_DEFINE_AGG_EVENT(20);
SX_CORE_DEFINE_AGG_EVENT(21);
SX_CORE_DEFINE_AGG_EVENT(22);
SX_CORE_DEFINE_AGG_EVENT(23);
SX_CORE_DEFINE_AGG_EVENT(24);
SX_CORE_DEFINE_AGG_EVENT(25);
SX_CORE_DEFINE_AGG_EVENT(26);
SX_CORE_DEFINE_AGG_EVENT(27);
SX_CORE_DEFINE_AGG_EVENT(28);
SX_CORE_DEFINE_AGG_EVENT(29);
SX_CORE_DEFINE_AGG_EVENT(30);
SX_CORE_DEFINE_AGG_EVENT(31);
SX_CORE_DEFINE_AGG_EVENT(32);
SX_CORE_DEFINE_AGG_EVENT(33);
SX_CORE_DEFINE_AGG_EVENT(34);
SX_CORE_DEFINE_AGG_EVENT(35);
SX_CORE_DEFINE_AGG_EVENT(36);
SX_CORE_DEFINE_AGG_EVENT(37);
SX_CORE_DEFINE_AGG_EVENT(38);
SX_CORE_DEFINE_AGG_EVENT(39);
SX_CORE_DEFINE_AGG_EVENT(40);
SX_CORE_DEFINE_AGG_EVENT(41);
SX_CORE_DEFINE_AGG_EVENT(42);
SX_CORE_DEFINE_AGG_EVENT(43);
SX_CORE_DEFINE_AGG_EVENT(44);
SX_CORE_DEFINE_AGG_EVENT(45);
SX_CORE_DEFINE_AGG_EVENT(46);
SX_CORE_DEFINE_AGG_EVENT(47);
SX_CORE_DEFINE_AGG_EVENT(48);
SX_CORE_DEFINE_AGG_EVENT(49);
SX_CORE_DEFINE_AGG_EVENT(50);
SX_CORE_DEFINE_AGG_EVENT(51);
SX_CORE_DEFINE_AGG_EVENT(52);
SX_CORE_DEFINE_AGG_EVENT(53);
SX_CORE_DEFINE_AGG_EVENT(54);
SX_CORE_DEFINE_AGG_EVENT(55);
SX_CORE_DEFINE_AGG_EVENT(56);

#endif /* _SX_CORE_TRACE_H */

/* This part must be outside protection */
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE trace
#include <trace/define_trace.h>
