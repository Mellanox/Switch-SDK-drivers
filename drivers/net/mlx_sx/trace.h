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

TRACE_EVENT(monitor_rdq_rx,
            TP_PROTO(const struct sk_buff *skb, uint16_t trap_id, const struct timespec *timestamp),

            TP_ARGS(skb, trap_id, timestamp),

            TP_STRUCT__entry(
                __field(const void *, skb)
                __field(uint16_t,     trap_id)
                __field(const void *, timestamp)
                ),

            TP_fast_assign(
                __entry->skb = skb;
                __entry->trap_id = trap_id;
                __entry->timestamp = timestamp;
                ),

            TP_printk("trap_id %u tv_sec %ld tv_nsec %ld", __entry->trap_id,
                      (long)(((const struct timespec*)__entry->timestamp)->tv_sec),
                      ((const struct timespec*)__entry->timestamp)->tv_nsec)
            );

#endif /* _SX_CORE_TRACE_H */

/* This part must be outside protection */
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE trace
#include <trace/define_trace.h>
