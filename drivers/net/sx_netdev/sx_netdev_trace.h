/*
 * Copyright (c) 2010-2021,  Mellanox Technologies. All rights reserved.
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
#define TRACE_SYSTEM sx_netdev

#if !defined(_SX_NETDEV_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#define _SX_NETDEV_TRACE_H

#include <linux/skbuff.h>
#include <linux/tracepoint.h>

TRACE_EVENT(sx_netdev_dm_hw_report,
            TP_PROTO(struct sk_buff *skb, const void *metadata),

            TP_ARGS(skb, metadata),

            TP_STRUCT__entry(
                __field(struct sk_buff *, skb)
                __field(const void *,     metadata)
                ),

            TP_fast_assign(
                __entry->skb = skb;
                __entry->metadata = metadata;
                ),

            TP_printk("skb %p metadata %p", __entry->skb, __entry->metadata)
            );

#endif /* _SX_NETDEV_TRACE_H */

/* This part must be outside protection */
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE sx_netdev_trace
#include <trace/define_trace.h>
