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

#ifndef SX_TRACE_FUNC_H
#define SX_TRACE_FUNC_H

#include <linux/mlx_sx/kernel_user.h>
#include <linux/skbuff.h>
#include <linux/version.h>
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
#include <linux/bpf.h>
#endif
#include "sx.h"

#define SKB_MARK_DROP 19
#define FILTER_TP_HW_PORT(is_lag, sysport_lag_id) ((is_lag << 16) | sysport_lag_id)
#define AGG_TP_HW_PORT(is_lag, lag_subport, sysport_lag_id) \
    ((((uint32_t)(is_lag)) << 24) | (((uint32_t)(lag_subport)) << 16) | ((uint32_t)(sysport_lag_id)))


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
void sx_core_call_rdq_agg_trace_point_func(struct sx_priv *priv,
                                           int dqn,
                                           u16 rdq_max_buff_size,
                                           struct sk_buff *skb,
                                           const struct sx_cqe_params *cqe_params_p,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                                           const struct timespec64    *timestamp);
#else
                                           const struct timespec      *timestamp);
#endif

/* filter trace point */
int sx_core_call_rdq_filter_trace_point_func(struct bpf_prog            *bpf_prog_p,
                                             struct sk_buff             *skb,
                                             const struct sx_cqe_params *cqe_params_p,
                                             u16                         rdq_max_buff_size);
#endif

#endif /* SX_TRACE_FUNC_H */
