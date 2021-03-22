/*
 * Copyright (c) 2010-2020,  Mellanox Technologies. All rights reserved.
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

#ifndef __BULK_CNTR_DB_H__
#define __BULK_CNTR_DB_H__

#include <linux/mlx_sx/kernel_user.h>

int bulk_cntr_db_add(struct ku_bulk_cntr_transaction_add *bulk_cntr_tr_add);
int bulk_cntr_db_del(pid_t client_pid, unsigned long buffer_id);
int bulk_cntr_db_cancel(pid_t client_pid, unsigned long buffer_id);

int bulk_cntr_db_ack(unsigned long                    buffer_id,
                     sxd_bulk_cntr_event_id_t        *ev_id,
                     enum sxd_bulk_cntr_done_status_e status);

int bulk_cntr_db_complete(const sxd_bulk_cntr_event_id_t   *event_id,
                          unsigned long                    *buffer_id,
                          enum sxd_bulk_cntr_done_status_e *status);

int bulk_cntr_db_event_id_to_buffer(sxd_bulk_cntr_event_id_t                   *event_id,
                                    struct sxd_bulk_cntr_buffer_layout_common **layout_common);

#endif /* __BULK_CNTR_DB_H__ */
