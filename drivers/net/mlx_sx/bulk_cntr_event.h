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

#ifndef __BULK_CNTR_EVENT_H__
#define __BULK_CNTR_EVENT_H__

#include <linux/mlx_sx/device.h>

void sx_bulk_cntr_handle_mocs_done(struct completion_info *ci);
void sx_bulk_cntr_handle_ppcnt(struct completion_info *ci);
void sx_bulk_cntr_handle_mgpcb(struct completion_info *ci);
void sx_bulk_cntr_handle_pbsr(struct completion_info *ci);
void sx_bulk_cntr_handle_sbsrd(struct completion_info *ci);

int sx_bulk_cntr_handle_ack(const sxd_bulk_cntr_event_id_t *ev_id,
                            unsigned long                   buffer_id);

#endif /* __BULK_CNTR_EVENT_H__ */
