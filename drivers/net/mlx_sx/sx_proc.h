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

#ifndef __SX_PROC_H__
#define __SX_PROC_H__

int sx_core_init_proc_fs(void);
void sx_core_close_proc_fs(void);

void sx_dpt_dump(void);
void sx_dpt_set_cmd_dbg(int dev_id, int path);
void sx_proc_dbg_wr(int width, unsigned long addr, unsigned long val);
void sx_proc_dbg_rd(int width, unsigned long addr, unsigned long *val);
void __sx_proc_dump_swids(struct sx_dev *dev);
void __sx_proc_dump_sdq(struct sx_dev *dev);
void __sx_proc_dump_rdq(struct sx_dev *dev);
void __sx_proc_set_dev_profile(struct sx_dev *dev);
void __dump_stats(struct sx_dev* sx_dev);
int sx_proc_handle_access_reg_auto(struct sx_dev *dev, char *p,
                                   u32 dev_id, u32 reg_id, char *running);
char * sx_proc_str_get_u32(char *buffer, u32 *val32);

#define SX_DBG_PACKET_TYPE_ANY 0xFFFF
#define SX_DBG_EMAD_TYPE_ANY   0xFFFF
#define SX_DBG_CMD_OP_TYPE_ANY 0xFFFF
#define SX_DBG_REG_TYPE_ANY    0xFFFF

#define SX_DBG_COUNT_UNLIMITED 0xFFFF

#define SX_PROC_DUMP_PKT_DISABLE 0
#define SX_PROC_DUMP_PKT_RX      1
#define SX_PROC_DUMP_PKT_TX      2

#define SX_DBG_DISABLE 0
#define SX_DBG_ENABLE  1

#endif
