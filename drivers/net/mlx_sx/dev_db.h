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

#ifndef __DEV_DB_H__
#define __DEV_DB_H__

#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/kernel_user.h>

int sx_dev_db_set_dev_by_id(sxd_dev_id_t dev_id, struct sx_dev *dev);
struct sx_dev * sx_dev_db_get_dev_by_id(sxd_dev_id_t dev_id);
struct sx_dev * sx_dev_db_get_default_device(void);
int sx_dev_db_add_device(struct sx_dev *dev);
int sx_dev_db_remove_device(struct sx_dev *dev);
int sx_dev_db_reassign_dev_id_to_default_device(sxd_dev_id_t dev_id);

int dev_db_init(void);
void dev_db_deinit(void);

int sx_dev_db_dump(struct seq_file *m, void *v, void *context);

struct sx_dev_db_iterator_seq_file_context {
    struct seq_file *m;
    void            *v;
    void            *context;
};

typedef bool (*sx_dev_db_iterator_cb_t)(struct sx_dev *dev, void *context);
int sx_dev_db_iterate(sx_dev_db_iterator_cb_t iter_cb, void *context);

#endif /* __DEV_DB_H__ */
