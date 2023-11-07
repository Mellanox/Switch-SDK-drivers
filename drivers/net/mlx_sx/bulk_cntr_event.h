/*
 * Copyright (C) 2010-2023 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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
#include <linux/mlx_sx/driver.h>

void sx_bulk_cntr_handle_mocs_done(struct completion_info *ci);
void sx_bulk_cntr_handle_ppcnt(struct completion_info *ci);
void sx_bulk_cntr_handle_mgpcb(struct completion_info *ci);
void sx_bulk_cntr_handle_pbsr(struct completion_info *ci);
void sx_bulk_cntr_handle_sbsrd(struct completion_info *ci);
void sx_bulk_cntr_handle_ceer(struct completion_info *ci);
void sx_bulk_cntr_handle_fsed(struct completion_info *ci);
void sx_bulk_cntr_handle_mofrb(struct completion_info *ci);
void sx_bulk_cntr_handle_upcnt(struct completion_info *ci);
void sx_bulk_cntr_handle_utcc(struct completion_info *ci);
void sx_bulk_cntr_handle_usacn(struct completion_info *ci);

int sx_bulk_cntr_handle_ack(const sxd_bulk_cntr_event_id_t *ev_id,
                            unsigned long                   buffer_id);
int sx_bulk_cntr_handle_continue_ack(const sxd_bulk_cntr_event_id_t *ev_id,
                                     unsigned long                   buffer_id);
int bulk_cntr_stateful_db_entry_write(ku_stateful_db_translated_entry_t *entry_p);

#endif /* __BULK_CNTR_EVENT_H__ */
