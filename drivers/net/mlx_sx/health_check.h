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

#ifndef __HEALTH_CHECK_H__
#define __HEALTH_CHECK_H__

#include <linux/mlx_sx/kernel_user.h>

enum sx_health_check_trigger_op {
    SX_HEALTH_CHECK_TRIGGER_OP_ADD_DEV,
    SX_HEALTH_CHECK_TRIGGER_OP_DEL_DEV,
    SX_HEALTH_CHECK_TRIGGER_OP_SYSFS,
    SX_HEALTH_CHECK_TRIGGER_OP_CATAS,
    SX_HEALTH_CHECK_TRIGGER_OP_CMD_IFC,
    SX_HEALTH_CHECK_TRIGGER_OP_SDQ,
    SX_HEALTH_CHECK_TRIGGER_OP_RDQ,
    SX_HEALTH_CHECK_TRIGGER_OP_CANCEL_ALL,
    SX_HEALTH_CHECK_TRIGGER_OP_KERNEL_THREADS,
    SX_HEALTH_CHECK_TRIGGER_OP_FW_FATAL_EVENT_TEST,
    SX_HEALTH_CHECK_TRIGGER_OP_FW_CAUSE_TEST,
    SX_HEALTH_CHECK_TRIGGER_OP_FW_ASSERT_TEST,
    SX_HEALTH_CHECK_TRIGGER_OP_FW_TILE_ASSERT_TEST,
    SX_HEALTH_CHECK_TRIGGER_OP_FW_TILE_FATAL_CAUSE_TEST,
    SX_HEALTH_CHECK_TRIGGER_OP_FW_PLL_FATAL_CAUSE_TEST
};

struct sx_health_check_trigger_params {
    enum sx_health_check_trigger_op op;
    u8                              dev_id;
    union {
        struct dq_params {
            int dqn;
        } dq_params;
        struct kthread_params {
            char* name;
        } kthread_params;
    } params;
    bool fatal_error_mode_active;
};

int sx_health_check_dev_init(struct sx_dev *dev);
void sx_health_check_dev_deinit(struct sx_dev *dev);
int sx_health_check_init(void);
int sx_health_check_deinit(void);
int sx_health_check_configure(ku_dbg_health_check_params_t *params);
void sx_health_check_report_dq_ok(struct sx_dev *dev, bool is_send, int dqn);
void sx_health_check_report_cmd_ifc_ok(struct sx_dev *dev);

int sx_health_check_dump(struct seq_file *m, void *v, void *context);

void sx_health_check_set_debug_trigger(struct sx_health_check_trigger_params *params);

int sx_health_update_tg(u8 dev_id, int hw_trap_group, bool is_add, bool is_wjh_rdq_update);

void sx_health_external_report(u8                                 dev_id,
                               u32                                issue_severity,
                               u32                                issue_cause,
                               u8                                 irisc_id,
                               sxd_health_external_report_data_t *data,
                               const char                        *error_msg);
void sx_health_external_report_all(u32 issue_severity, u32 issue_cause, const char *error_msg);
void sx_health_check_mfde_error_update(struct ku_mfde_reg *mfde_reg,  struct sx_dev * dev);
void sx_health_check_meccc_error_update(struct ku_meccc_reg *meccc_reg,  struct sx_dev * dev);
void sx_health_check_fshe_error_update(struct sx_dev * dev);

#endif /* __HEALTH_CHECK_H__ */
