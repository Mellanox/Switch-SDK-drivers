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

#ifndef __SX_DBG_DUMP_PROC_H__
#define __SX_DBG_DUMP_PROC_H__

#include <linux/seq_file.h>
#include <linux/proc_fs.h>

typedef int (*dbg_dump_proc_show_cb_t)(struct seq_file* seq_file, void* v);
typedef size_t (*dbg_dump_proc_size_cb_t)(void);

/************************************************
 *  Function declarations
 ***********************************************/

int sx_dbg_dump_proc_fs_init(void);
void sx_dbg_dump_proc_fs_deinit(void);

int sx_dbg_dump_proc_fs_register(const char *name, dbg_dump_proc_show_cb_t show_cb, dbg_dump_proc_size_cb_t size_cb);
void sx_dbg_dump_proc_fs_unregister(const char *name);

const char * trap_id_str(u16 trap_id);

#endif /* __SX_DBG_DUMP_PROC_H__ */
