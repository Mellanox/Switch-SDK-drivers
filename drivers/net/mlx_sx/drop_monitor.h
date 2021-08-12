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

int sx_drop_monitor_set_synd(unsigned int               cmd,
                             struct ku_synd_ioctl      *ku,
                             enum l2_type               listener_type,
                             union ku_filter_critireas *critireas,
                             struct sx_dev             *dev);

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

static inline int sx_drop_monitor_set_synd(unsigned int               cmd,
                                           struct ku_synd_ioctl      *ku,
                                           enum l2_type               listener_type,
                                           union ku_filter_critireas *critireas,
                                           struct sx_dev             *dev)
{
    return 0;
}

#endif /* SX_DROP_MONITOR_DISABLED */

#endif /* SX_DROP_MONITOR_H */
