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

#include <linux/filter.h>
#include "trace.h"
#include "trace_func.h"

typedef struct wjh_filter_ebpf_prog_args {
    u64             pad;
    struct sk_buff *skb;
    u32             hw_port;
    u16             trap_id;
    u32             acl_user_id;
} wjh_filter_ebpf_prog_args_t;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0))
sx_core_rdq_agg_trace_point_func sx_core_rdq_agg_trace_points[NUMBER_OF_RDQS] = {
#else
sx_core_rdq_agg_trace_point_func sx_core_rdq_agg_trace_points[NUMBER_OF_RDQS][SX_AGG_TRACE_POINT_NUM_PER_RDQ] = {
#endif
    SX_CORE_AGG_TRACE_FUNC(0),
    SX_CORE_AGG_TRACE_FUNC(1),
    SX_CORE_AGG_TRACE_FUNC(2),
    SX_CORE_AGG_TRACE_FUNC(3),
    SX_CORE_AGG_TRACE_FUNC(4),
    SX_CORE_AGG_TRACE_FUNC(5),
    SX_CORE_AGG_TRACE_FUNC(6),
    SX_CORE_AGG_TRACE_FUNC(7),
    SX_CORE_AGG_TRACE_FUNC(8),
    SX_CORE_AGG_TRACE_FUNC(9),
    SX_CORE_AGG_TRACE_FUNC(10),
    SX_CORE_AGG_TRACE_FUNC(11),
    SX_CORE_AGG_TRACE_FUNC(12),
    SX_CORE_AGG_TRACE_FUNC(13),
    SX_CORE_AGG_TRACE_FUNC(14),
    SX_CORE_AGG_TRACE_FUNC(15),
    SX_CORE_AGG_TRACE_FUNC(16),
    SX_CORE_AGG_TRACE_FUNC(17),
    SX_CORE_AGG_TRACE_FUNC(18),
    SX_CORE_AGG_TRACE_FUNC(19),
    SX_CORE_AGG_TRACE_FUNC(20),
    SX_CORE_AGG_TRACE_FUNC(21),
    SX_CORE_AGG_TRACE_FUNC(22),
    SX_CORE_AGG_TRACE_FUNC(23),
    SX_CORE_AGG_TRACE_FUNC(24),
    SX_CORE_AGG_TRACE_FUNC(25),
    SX_CORE_AGG_TRACE_FUNC(26),
    SX_CORE_AGG_TRACE_FUNC(27),
    SX_CORE_AGG_TRACE_FUNC(28),
    SX_CORE_AGG_TRACE_FUNC(29),
    SX_CORE_AGG_TRACE_FUNC(30),
    SX_CORE_AGG_TRACE_FUNC(31),
    SX_CORE_AGG_TRACE_FUNC(32),
    SX_CORE_AGG_TRACE_FUNC(33),
    SX_CORE_AGG_TRACE_FUNC(34),
    SX_CORE_AGG_TRACE_FUNC(35),
    SX_CORE_AGG_TRACE_FUNC(36),
    SX_CORE_AGG_TRACE_FUNC(37),
    SX_CORE_AGG_TRACE_FUNC(38),
    SX_CORE_AGG_TRACE_FUNC(39),
    SX_CORE_AGG_TRACE_FUNC(40),
    SX_CORE_AGG_TRACE_FUNC(41),
    SX_CORE_AGG_TRACE_FUNC(42),
    SX_CORE_AGG_TRACE_FUNC(43),
    SX_CORE_AGG_TRACE_FUNC(44),
    SX_CORE_AGG_TRACE_FUNC(45),
    SX_CORE_AGG_TRACE_FUNC(46),
    SX_CORE_AGG_TRACE_FUNC(47),
    SX_CORE_AGG_TRACE_FUNC(48),
    SX_CORE_AGG_TRACE_FUNC(49),
    SX_CORE_AGG_TRACE_FUNC(50),
    SX_CORE_AGG_TRACE_FUNC(51),
    SX_CORE_AGG_TRACE_FUNC(52),
    SX_CORE_AGG_TRACE_FUNC(53),
    SX_CORE_AGG_TRACE_FUNC(54),
    SX_CORE_AGG_TRACE_FUNC(55),
    SX_CORE_AGG_TRACE_FUNC(56)
};

void sx_core_call_rdq_agg_trace_point_func(int dqn,
                                           struct sk_buff *skb,
                                           uint16_t trap_id,
                                           uint32_t acl_user_id,
                                           const struct timespec *timestamp)
{
#if (LINUX_VERSION_CODE < KERNEL_VERSION(4, 15, 0))
    int i = 0;
#endif

    if (dqn < 0 || dqn >= NUMBER_OF_RDQS)
        return;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0))
    if (sx_core_rdq_agg_trace_points[dqn] == NULL)
        return;

    sx_core_rdq_agg_trace_points[dqn](skb, trap_id, acl_user_id, timestamp);
#else
    for (i = 0; i < SX_AGG_TRACE_POINT_NUM_PER_RDQ; i++) {
        if (sx_core_rdq_agg_trace_points[dqn][i] != NULL) {
            sx_core_rdq_agg_trace_points[dqn][i](skb, trap_id, acl_user_id, timestamp);
        }
    }
#endif
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
int sx_core_call_rdq_filter_trace_point_func(struct bpf_prog* bpf_prog_p,
                                             struct sk_buff  *skb,
                                             uint32_t         port,
                                             uint16_t         trap_id,
                                             uint32_t         acl_user_id)
{
    wjh_filter_ebpf_prog_args_t bpf_args;
    int                         err = 0;

    if (bpf_prog_p != NULL) {
        bpf_args.skb = skb;
        bpf_args.hw_port = port;
        bpf_args.trap_id = trap_id;
        bpf_args.acl_user_id = acl_user_id;
        err = BPF_PROG_RUN(bpf_prog_p, (void*)&bpf_args);
        if (err != 0) {
            skb->mark = SKB_MARK_DROP;
        }
    }

    return err;
}
#endif
