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

#ifndef __BER_MONITOR_H__
#define __BER_MONITOR_H__

struct sx_priv;
struct completion_info;
struct ku_sx_core_db;
struct seq_file;

int sx_core_ber_monitor_init(struct sx_dev *dev);
void sx_core_ber_monitor_deinit(void);

void sx_core_ber_monitor_handle_ppbme_event(struct completion_info *ci);
int sx_core_ber_monitor_set_bitmask(u8 dev_id, u8 local_port, u8 bitmask);

int sx_core_ber_monitor_dump(struct seq_file *m, void *v);

/* The functions below MUST be called under priv->db_lock lock! */
int sx_core_ber_monitor_set_state(u8 dev_id, u8 local_port, u8 state);
int sx_core_ber_monitor_serialize(struct ku_sx_core_db __user *sx_core_db);
int sx_core_ber_monitor_deserialize(const struct ku_sx_core_db *sx_core_db);

#endif /* __BER_MONITOR_H__ */
