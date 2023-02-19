/*
 * Copyright (C) 2008-2022 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#ifndef SX_AF_COUNTERS_H
#define SX_AF_COUNTERS_H

/************************************************
 * Includes
 ***********************************************/
#include <linux/seq_file.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/device.h>

/************************************************
 *  Defines
 ***********************************************/
#define SX_AF_COUNTERS_GENERATE_ENUM(ENUM, STR)   ENUM,
#define SX_AF_COUNTERS_GENERATE_STRING(ENUM, STR) STR,

/************************************************
 * Type declarations
 ***********************************************/
#define FOREACH_SX_AF_COUNTERS_PROC_FS_HANDLER_OP(F)                                                     \
    F(SX_AF_COUNTERS_PROC_FS_HANDLER_OP_CLEAR_E = 0,                                            "CLEAR") \
    F(SX_AF_COUNTERS_PROC_FS_HANDLER_OP_MAX_E = SX_AF_COUNTERS_PROC_FS_HANDLER_OP_CLEAR_E,      "")      \
    F(SX_AF_COUNTERS_PROC_FS_HANDLER_OP_NUM_E = SX_AF_COUNTERS_PROC_FS_HANDLER_OP_MAX_E + 1,    "")

typedef enum sx_af_counters_proc_fs_handler_op {
    FOREACH_SX_AF_COUNTERS_PROC_FS_HANDLER_OP(SX_AF_COUNTERS_GENERATE_ENUM)
} sx_af_counters_proc_fs_handler_op_e;

/************************************************
 * Functions
 ***********************************************/
int sx_af_counters_init(struct ku_accuflow_counters_params *af_params_p);
int sx_af_counters_deinit(void);
int sx_af_counters_tr_reservation_set(ku_accuflow_counters_params_data_tr_reservation_t *tr_reservation_p);
void sx_af_counters_mocs_done(void);
int sx_af_counters_user_job_schedule(struct ku_accuflow_counters_params *af_params_p);
void sx_af_counters_event_job_schedule(struct completion_info *comp_info_p);
size_t sx_af_counters_dump_size(void);
int sx_af_counters_dump(struct seq_file *m, void *v, void *context);
int sx_af_counters_proc_fs_handler(sx_af_counters_proc_fs_handler_op_e op);

#endif  /* SX_AF_COUNTERS_H */
