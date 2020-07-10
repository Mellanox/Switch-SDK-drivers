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

#ifndef SX_TRACE_FUNC_H
#define SX_TRACE_FUNC_H

#include <linux/mlx_sx/kernel_user.h>
#include <linux/skbuff.h>
#include <linux/version.h>
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
#include <linux/bpf.h>
#endif

#define SKB_MARK_DROP 19
#define FILTER_TP_HW_PORT(is_lag, sysport_lag_id) ((is_lag << 16) | sysport_lag_id)
#define AGG_TP_HW_PORT(is_lag, lag_subport, sysport_lag_id) \
    ((((uint32_t)(is_lag)) << 24) | (((uint32_t)(lag_subport)) << 16) | ((uint32_t)(sysport_lag_id)))


/* aggregation trace point */
typedef void (*sx_core_rdq_agg_trace_point_func)(struct sk_buff        *skb,
                                                 uint16_t               trap_id,
                                                 uint32_t               acl_user_id,
                                                 const struct timespec *timestamp,
                                                 uint8_t                mirror_reason,
                                                 uint32_t               port);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0))
#define SX_CORE_AGG_TRACE_FUNC(rdq_no) trace_sx_rdq_rx_agg_ ## rdq_no
extern sx_core_rdq_agg_trace_point_func sx_core_rdq_agg_trace_points[NUMBER_OF_RDQS];
#else
#define SX_CORE_AGG_TRACE_FUNC(rdq_no)        \
    {                                         \
        trace_sx_rdq_rx_agg_ ## rdq_no ## _0, \
        trace_sx_rdq_rx_agg_ ## rdq_no ## _1, \
        trace_sx_rdq_rx_agg_ ## rdq_no ## _2, \
        trace_sx_rdq_rx_agg_ ## rdq_no ## _3, \
        trace_sx_rdq_rx_agg_ ## rdq_no ## _4, \
        trace_sx_rdq_rx_agg_ ## rdq_no ## _5, \
        trace_sx_rdq_rx_agg_ ## rdq_no ## _6, \
    }

extern sx_core_rdq_agg_trace_point_func sx_core_rdq_agg_trace_points[NUMBER_OF_RDQS][SX_AGG_TRACE_POINT_NUM_PER_RDQ];
#endif

void sx_core_call_rdq_agg_trace_point_func(int                    dqn,
                                           struct sk_buff        *skb,
                                           uint16_t               trap_id,
                                           uint32_t               acl_user_id,
                                           const struct timespec *timestamp,
                                           uint8_t                mirror_reason,
                                           uint32_t               port);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
/* filter trace point */
int sx_core_call_rdq_filter_trace_point_func(struct bpf_prog* bpf_prog_p,
                                             struct sk_buff  *skb,
                                             uint32_t         port,
                                             uint16_t         trap_id,
                                             uint32_t         acl_user_id);
#endif

#endif /* SX_TRACE_FUNC_H */
