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

#ifndef __SX_DBG_DUMP_PROC_H__
#define __SX_DBG_DUMP_PROC_H__

#include <linux/seq_file.h>
#include <linux/proc_fs.h>

#define HEADER_MAX_LEN 150

typedef int (*dbg_dump_proc_show_cb_t)(struct seq_file* seq_file, void *v, void* context);
typedef size_t (*dbg_dump_proc_size_cb_t)(void);
typedef int (*dbg_dump_proc_cmd_cb_t)(int argc, const char *argv[], void *context);

#define print_table_header(seqfile, fmt, args ...)                                                                                                \
    do {                                                                                                                                          \
        seq_printf((seqfile), fmt "\n", ## args);                                                                                                 \
        seq_printf((seqfile),                                                                                                                     \
                   "------------------------------------------------------------------------------------------------------------------------\n"); \
    } while (0)

#define print_empty_line(seqfile)    \
    do {                             \
        seq_printf((seqfile), "\n"); \
    } while (0)

#define print_separate_line(seqfile)                                                                                                              \
    do {                                                                                                                                          \
        seq_printf((seqfile),                                                                                                                     \
                   "........................................................................................................................\n"); \
    } while (0)

/************************************************
 *  Function declarations
 ***********************************************/

int sx_dbg_dump_proc_fs_init(void);
void sx_dbg_dump_proc_fs_deinit(void);

int sx_dbg_dump_read_handler_register(const char             *name,
                                      dbg_dump_proc_show_cb_t show_cb,
                                      dbg_dump_proc_size_cb_t size_cb,
                                      void                   *context);
void sx_dbg_dump_read_handler_unregister(const char *name);

int sx_dbg_dump_write_handler_register(const char            *cmd,
                                       const char            *usage,
                                       const char            *description,
                                       dbg_dump_proc_cmd_cb_t cmd_cb,
                                       void                  *context);
void sx_dbg_dump_write_handler_unregister(const char *cmd);

void print_header(struct seq_file *m, const char* header);

#endif /* __SX_DBG_DUMP_PROC_H__ */
