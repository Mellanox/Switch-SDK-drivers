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
