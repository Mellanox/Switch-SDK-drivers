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
#include "trace_func.h"

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
void sx_core_call_rdq_agg_trace_point_func(struct sx_priv        *priv,
                                           int                    dqn,
                                           struct sk_buff        *skb,
                                           uint16_t               trap_id,
                                           uint32_t               acl_user_id,
                                           const struct timespec *timestamp,
                                           uint8_t                mirror_reason,
                                           uint32_t               port)
{
    int                      i = 0;
    u32                     *cb_data = (u32*)(bpf_skb_cb(skb));
    u32                      cb_data_orig[5];
    struct bpf_skb_data_end *cb = (struct bpf_skb_data_end *)skb->cb;

    memcpy(cb_data_orig, cb_data, sizeof(cb_data_orig));
    cb->data_end = skb->data + SX_MAX_MSG_SIZE;

    cb_data[0] = (((uint32_t)trap_id) << 16) | mirror_reason;
    cb_data[1] = acl_user_id;
    cb_data[2] = timestamp->tv_sec;
    cb_data[3] = timestamp->tv_nsec;
    cb_data[4] = port;

    for (i = 0; i < SX_AGG_EBPF_PROG_NUM_PER_RDQ; i++) {
        if (priv->agg_ebpf_progs[dqn][i] != NULL) {
            rcu_read_lock();
            BPF_PROG_RUN(priv->agg_ebpf_progs[dqn][i], skb);
            rcu_read_unlock();
        }
    }

    memcpy(cb_data, cb_data_orig, sizeof(cb_data_orig));
}

int sx_core_call_rdq_filter_trace_point_func(struct bpf_prog* bpf_prog_p,
                                             struct sk_buff  *skb,
                                             uint32_t         port,
                                             uint16_t         trap_id,
                                             uint32_t         acl_user_id)
{
    int                      err = 0;
    u32                     *cb_data = (u32*)(bpf_skb_cb(skb));
    u32                      cb_data_orig[3];
    struct bpf_skb_data_end *cb = (struct bpf_skb_data_end *)skb->cb;

    if (bpf_prog_p != NULL) {
        memcpy(cb_data_orig, cb_data, sizeof(cb_data_orig));
        cb->data_end = skb->data + SX_MAX_MSG_SIZE;
        cb_data[0] = port;
        cb_data[1] = trap_id;
        cb_data[2] = acl_user_id;

        rcu_read_lock();
        err = BPF_PROG_RUN(bpf_prog_p, skb);
        rcu_read_unlock();
        if (err != 0) {
            skb->mark = SKB_MARK_DROP;
        } else {
            skb->mark = 0;
        }
        memcpy(cb_data, cb_data_orig, sizeof(cb_data_orig));
    }

    return err;
}
#endif /* if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0)) */
