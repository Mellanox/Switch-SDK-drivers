/*
 * Copyright (C) 2008-2023 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#ifndef SX_AF_DBG_INFO_H
#define SX_AF_DBG_INFO_H

/************************************************
 * Includes
 ***********************************************/
#include <linux/seq_file.h>
#include <linux/ktime.h>
#include <linux/mlx_sx/auto_registers/reg.h>

/************************************************
 *  Defines
 ***********************************************/

/************************************************
 * Type declarations
 ***********************************************/
typedef struct mafbi_reg {
    char reg[MLXSW_MAFBI_LEN];
} mafbi_reg_t;

typedef struct mafti_reg {
    char reg[MLXSW_MAFTI_LEN];
} mafti_reg_t;

typedef struct mafri_reg {
    char reg[MLXSW_MAFRI_LEN];
} mafri_reg_t;

typedef struct mocs_reg {
    char reg[MLXSW_MOCS_LEN];
} mocs_reg_t;

#define SX_GENERATE_ENUM(ENUM, STR) ENUM,
#define FOREACH_CBUF_RECORD_TYPE(F)                                  \
    F(CBUF_RECORD_TYPE_MAFBI_E = 0,                         "MAFBI") \
    F(CBUF_RECORD_TYPE_MAFTI_E,                             "MAFTI") \
    F(CBUF_RECORD_TYPE_MAFRI_E,                             "MAFRI") \
    F(CBUF_RECORD_TYPE_MOCS_E,                              "MOCS")  \
    F(CBUF_RECORD_TYPE_MAX_E = CBUF_RECORD_TYPE_MOCS_E,     "")      \
    F(CBUF_RECORD_TYPE_NUM_E = CBUF_RECORD_TYPE_MAX_E + 1,  "")

typedef enum cbuf_record_type {
    FOREACH_CBUF_RECORD_TYPE(SX_GENERATE_ENUM) \
} cbuf_record_type_e;

typedef union cbuf_record_data {
    mafbi_reg_t mafbi_reg;
    mafti_reg_t mafti_reg;
    mafri_reg_t mafri_reg;
    mocs_reg_t  mocs_reg;
} cbuf_record_data_t;

typedef struct cbuf_record {
    cbuf_record_type_e type;
    cbuf_record_data_t data;
    ktime_t            ts;
} cbuf_record_t;

/************************************************
 * Functions
 ***********************************************/
int sx_af_dbg_info_init(void);
void sx_af_dbg_info_deinit(void);
int sx_af_dbg_info_clear(void);
int sx_af_dbg_info_push(cbuf_record_t *record_p);
int sx_af_dbg_info_dump(struct seq_file *m, void *v, void *context);

#endif  /* SX_AF_DBG_INFO_H */
