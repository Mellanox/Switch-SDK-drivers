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

#include <linux/filter.h>
#include "trace_func.h"

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
void sx_core_call_rdq_agg_trace_point_func(struct sx_priv             *priv,
                                           int                         dqn,
                                           u16                         rdq_max_buff_size,
                                           struct sk_buff             *skb,
                                           const struct sx_cqe_params *cqe_params_p,
#if (LINUX_VERSION_CODE >=                                             KERNEL_VERSION(5, \
                                                                          10,            \
                                                                          0))
                                           const struct timespec64 *timestamp)
#else
                                           const struct timespec      *timestamp)
#endif
{
    int                      i = 0;
    u32                     *cb_data = (u32*)(bpf_skb_cb(skb));
    u32                      cb_data_orig[5];
    u32                      hash_orig = skb->hash;
    u32                      iif_orig = skb->skb_iif;
    struct bpf_skb_data_end *cb = (struct bpf_skb_data_end *)skb->cb;

    memcpy(cb_data_orig, cb_data, sizeof(cb_data_orig));
    cb->data_end = skb->data + rdq_max_buff_size;

    /* maximum 12 uint32 cb data */
    /* 0: trap_id (10 bits) + mirror congestion (16 bits) */
    /* 1: user def val (20 bits) + mirror reason (8 bits) */
    /* 2: tv_sec (32 bits) */
    /* 3: tv nsec (32 bits) */
    /* 4: hw port (25 bits) */
    /* hash: mirror tclass (8 bits) + mirror latency (24 bits) */
    /* iif: dest hw port (25 bits) */
    cb_data[0] = (((uint32_t)cqe_params_p->trap_id) << 16) | cqe_params_p->mirror_cong;
    cb_data[1] = (cqe_params_p->user_def_val_orig_pkt_len << 8) | cqe_params_p->mirror_reason;
    cb_data[2] = (timestamp == NULL) ? 0 : timestamp->tv_sec;
    cb_data[3] = (timestamp == NULL) ? 0 : timestamp->tv_nsec;
    cb_data[4] = AGG_TP_HW_PORT(cqe_params_p->is_lag, cqe_params_p->lag_subport, cqe_params_p->sysport_lag_id);
    skb->hash = (cqe_params_p->mirror_tclass << 24) | cqe_params_p->mirror_lantency;
    skb->skb_iif = AGG_TP_HW_PORT(cqe_params_p->dest_is_lag,
                                  cqe_params_p->dest_lag_subport,
                                  cqe_params_p->dest_sysport_lag_id);

    for (i = 0; i < SX_AGG_EBPF_PROG_NUM_PER_RDQ; i++) {
        if (priv->agg_ebpf_progs[dqn][i] != NULL) {
            rcu_read_lock();
            BPF_PROG_RUN(priv->agg_ebpf_progs[dqn][i], skb);
            rcu_read_unlock();
        }
    }

    memcpy(cb_data, cb_data_orig, sizeof(cb_data_orig));
    skb->hash = hash_orig;
    skb->skb_iif = iif_orig;
}

int sx_core_call_rdq_filter_trace_point_func(struct bpf_prog            *bpf_prog_p,
                                             struct sk_buff             *skb,
                                             const struct sx_cqe_params *cqe_params_p,
                                             u16                         rdq_max_buff_size)
{
    int                      err = 0;
    u32                     *cb_data = (u32*)(bpf_skb_cb(skb));
    u32                      cb_data_orig[4];
    struct bpf_skb_data_end *cb = (struct bpf_skb_data_end *)skb->cb;

    if (bpf_prog_p != NULL) {
        memcpy(cb_data_orig, cb_data, sizeof(cb_data_orig));
        cb->data_end = skb->data + rdq_max_buff_size;
        cb_data[0] = FILTER_TP_HW_PORT(cqe_params_p->is_lag, cqe_params_p->sysport_lag_id);
        cb_data[1] = cqe_params_p->trap_id;
        cb_data[2] = cqe_params_p->user_def_val_orig_pkt_len;
        cb_data[3] = cqe_params_p->mirror_reason;

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
