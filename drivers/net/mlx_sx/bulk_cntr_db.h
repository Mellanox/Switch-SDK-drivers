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

#ifndef __BULK_CNTR_DB_H__
#define __BULK_CNTR_DB_H__

#include <linux/seq_file.h>
#include <linux/mlx_sx/kernel_user.h>

int bulk_cntr_db_add(struct ku_bulk_cntr_transaction_add *bulk_cntr_tr_add);
int bulk_cntr_db_del(pid_t client_pid, unsigned long buffer_id);
int bulk_cntr_db_cancel(pid_t client_pid, unsigned long buffer_id);

int bulk_cntr_db_ack(unsigned long                    buffer_id,
                     sxd_bulk_cntr_event_id_t        *ev_id,
                     enum sxd_bulk_cntr_done_status_e status);

int bulk_cntr_db_complete(const sxd_bulk_cntr_event_id_t   *event_id,
                          unsigned long                    *buffer_id,
                          enum sxd_bulk_cntr_done_status_e *status,
                          uint32_t                         *cookie);

int bulk_cntr_db_in_progress_get(enum sxd_bulk_cntr_key_type_e type, u8 *in_progress_p);
int bulk_cntr_db_in_progress(struct ku_bulk_cntr_transaction *bulk_cntr_tr_in_progress, void *data);

int bulk_cntr_db_event_id_to_buffer(sxd_bulk_cntr_event_id_t                   *event_id,
                                    struct sxd_bulk_cntr_buffer_layout_common **layout_common);

int bulk_cntr_db_per_prio_cache_set(struct ku_bulk_cntr_per_prio_cache *bulk_cntr_per_prio_cache);

int bulk_cntr_db_per_prio_cache_entry_get(uint16_t local_port, uint16_t prio, sxd_port_cntr_prio_t **cache_entry);

int bulk_cntr_db_mocs_session_acquire(enum sxd_bulk_cntr_key_type_e type);
int bulk_cntr_db_mocs_session_release(enum sxd_bulk_cntr_key_type_e type);
int bulk_cntr_db_dump(struct seq_file *m, void *v, void *context);

#endif /* __BULK_CNTR_DB_H__ */
