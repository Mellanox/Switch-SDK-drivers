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
