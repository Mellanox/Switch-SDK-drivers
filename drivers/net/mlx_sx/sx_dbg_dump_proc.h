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

#ifndef __SX_DBG_DUMP_PROC_H__
#define __SX_DBG_DUMP_PROC_H__

bool sx_dbg_dump_proc_fs_init(struct sx_dev *dev, void *context);
bool sx_dbg_dump_proc_fs_deinit(struct sx_dev *dev, void *context);
struct sx_dev * sx_dbg_dump_get_device(struct seq_file *m);
void sx_dbg_dump_proc_fs_remove_parent_proc_folder(void);

struct sx_name_device_tuple {
    const char  *name;
    sxd_dev_id_t dev_id;
};

struct read_handler_info {
    struct list_head            list;
    sx_dbg_dump_proc_show_cb_t  show_cb;
    sx_dbg_dump_proc_size_cb_t  size_cb;
    void                       *context;
    struct sx_name_device_tuple read_handler_struct_key;
};


#endif /* __SX_DBG_DUMP_PROC_H__ */
