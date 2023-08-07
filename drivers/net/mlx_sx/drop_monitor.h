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

#ifndef SX_DROP_MONITOR_H
#define SX_DROP_MONITOR_H

#include <net/drop_monitor.h>
#include <linux/mlx_sx/driver.h>
#include "sx.h"
#include "cq.h"

#ifndef SX_DROP_MONITOR_DISABLED
void sx_drop_monitor_destroy(void);

void sx_drop_monitor_handle_monitor_rdq(u32                     cq_ts_enabled,
                                        struct sx_cq           *cq,
                                        int                     cqe_index,
                                        struct sx_cqe_params   *cqe_params,
                                        union sx_cqe           *u_cqe,
                                        struct sx_rx_timestamp *rx_ts,
                                        bool                   *rx_ts_set,
                                        struct sk_buff         *skb);

int sx_drop_monitor_set_buffer_drop_params(unsigned long data);

void sx_drop_monitor_handle_sw_queue(struct completion_info *comp_info, void *context);

int sx_drop_monitor_set_synd(unsigned int                     cmd,
                             const struct ku_synd_ioctl      *ku,
                             enum l2_type                     listener_type,
                             const union ku_filter_critireas *critireas,
                             struct sx_dev                   *dev);

#else
static inline void sx_drop_monitor_destroy(void)
{
}

static inline void sx_drop_monitor_handle_monitor_rdq(u32                     cq_ts_enabled,
                                                      struct sx_cq           *cq,
                                                      int                     cqe_index,
                                                      struct sx_cqe_params   *cqe_params,
                                                      union sx_cqe           *u_cqe,
                                                      struct sx_rx_timestamp *rx_ts,
                                                      bool                   *rx_ts_set,
                                                      struct sk_buff         *skb)
{
}

static inline int sx_drop_monitor_set_buffer_drop_params(unsigned long data)
{
    return 0;
}

static inline void sx_drop_monitor_handle_sw_queue(struct completion_info *comp_info, void *context)
{
}

static inline int sx_drop_monitor_set_synd(unsigned int                     cmd,
                                           const struct ku_synd_ioctl      *ku,
                                           enum l2_type                     listener_type,
                                           const union ku_filter_critireas *critireas,
                                           struct sx_dev                   *dev)
{
    return 0;
}

#endif /* SX_DROP_MONITOR_DISABLED */

#endif /* SX_DROP_MONITOR_H */
