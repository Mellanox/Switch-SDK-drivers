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

#ifndef __BER_MONITOR_H__
#define __BER_MONITOR_H__

struct sx_priv;
struct completion_info;
struct ku_sx_core_db;
struct seq_file;

int sx_core_ber_monitor_init(void);
void sx_core_ber_monitor_deinit(void);

void sx_core_ber_monitor_dev_init(struct sx_dev *dev);
void sx_core_ber_monitor_dev_deinit(struct sx_dev *dev);

void sx_core_ber_monitor_handle_ppbme_event(struct completion_info *ci);
int sx_core_ber_monitor_set_bitmask(sxd_dev_id_t dev_id, u16 local_port, u8 bitmask);

int sx_core_ber_monitor_dump(struct seq_file *m, void *v, void *context);

/* The functions below MUST be called under priv->db_lock lock! */
int sx_core_ber_monitor_set_state(sxd_dev_id_t dev_id, u16 local_port, u8 state);

#endif /* __BER_MONITOR_H__ */
