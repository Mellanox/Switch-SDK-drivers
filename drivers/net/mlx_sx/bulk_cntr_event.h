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

#ifndef __BULK_CNTR_EVENT_H__
#define __BULK_CNTR_EVENT_H__

#include <linux/mlx_sx/device.h>

typedef void (*sx_bulk_cntr_reg_parser_t)(const void                                *reg,
                                          u32                                        reg_len,
                                          struct sxd_bulk_cntr_buffer_layout_common *layout_common,
                                          void                                      *context);

/* function to parse multi-reg EMAD frame */
void sx_bulk_cntr_multi_emad_parse(const void               *buff,
                                   u32                       buff_len,
                                   sx_bulk_cntr_reg_parser_t reg_parser_cb,
                                   void                     *context);

void sx_bulk_cntr_handle_mocs_done(struct completion_info *ci);
void sx_bulk_cntr_handle_ppcnt(struct completion_info *ci);
void sx_bulk_cntr_handle_mgpcb(struct completion_info *ci);
void sx_bulk_cntr_handle_pbsr(struct completion_info *ci);
void sx_bulk_cntr_handle_sbsrd(struct completion_info *ci);
void sx_bulk_cntr_handle_ceer(struct completion_info *ci);

int sx_bulk_cntr_handle_ack(const sxd_bulk_cntr_event_id_t *ev_id,
                            unsigned long                   buffer_id);

#endif /* __BULK_CNTR_EVENT_H__ */
