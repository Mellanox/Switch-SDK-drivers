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

/************************************************
 * Includes
 ***********************************************/
#include <asm/barrier.h>
#include <linux/err.h>
#include <linux/string.h>
#include <linux/stddef.h>
#include <linux/vmalloc.h>
#include <linux/workqueue.h>
#include <linux/completion.h>
#include <linux/ktime.h>
#include <linux/jiffies.h>

#include <linux/mlx_sx/auto_registers/reg.h>

#include "sx_af_dbg_info.h"
#include "sx_af_counters.h"
#include "sx.h"
#include "mmap.h"
#include "bulk_cntr_event.h"
#include "bulk_cntr_db.h"

/************************************************
 * Defines
 ***********************************************/
#define SX_AF_COUNTERS_DUMP_SIZE (100 * 1024 * 1024)

/************************************************
 * Type declarations
 ***********************************************/
struct sx_af_counters_ctx {
    u16                          packets_inc_unit;
    u16                          bytes_inc_unit;
    u32                          prm_cntr_lines_per_bank;
    u8                           prm_cntr_banks;
    u8                           prm_cntr_lines_flow_both;
    u8                           prm_cntr_type_flow_both;
    u32                          prm_cntr_start_idx_offset;
    u32                          af_counters_num;
    u64                         *af_counters_buffer_p;
    struct workqueue_struct     *af_counters_wq_p;
    sxd_bulk_cntr_refresh_attr_t refresh_attr;
};

typedef union sx_af_counters_work_data {
    struct sk_buff                    *skb_p;
    struct ku_accuflow_counters_params af_params;
} sx_af_counters_work_data_t;

struct sx_af_counters_work {
    struct sx_dev                           *dev_p;
    struct completion                       *completion_p;
    struct sxd_bulk_cntr_buffer_layout_flow *layout_flow;
    sx_af_counters_work_data_t               data;
    struct work_struct                       ws;
    ktime_t                                  ktime;
};

typedef struct sxd_emad_mafti_reg {
    char reg[MLXSW_MAFTI_LEN];
} sxd_emad_mafti_reg_t;

typedef struct sxd_emad_mafri_reg {
    char reg[MLXSW_MAFRI_LEN];
} sxd_emad_mafri_reg_t;

typedef struct sxd_emad_mafbi_reg {
    char reg[MLXSW_MAFBI_LEN];
} sxd_emad_mafbi_reg_t;

typedef struct sx_af_critical_issues_stats {
    u32 reserved;
} sx_af_critical_issues_stats_t;

typedef struct sx_af_reg_record_stats {
    u32 counter_index;
    u32 packets_inc;
    u32 bytes_inc;
} sx_af_reg_record_stats_t;

typedef struct sx_af_reg_stats {
    sx_af_reg_record_stats_t min_bytes_records;
    sx_af_reg_record_stats_t max_bytes_records;
    sx_af_reg_record_stats_t min_packets_records;
    sx_af_reg_record_stats_t max_packets_records;
} sx_af_reg_stats_t;

typedef struct sx_af_regs_stats {
    sx_af_reg_stats_t mafti;
    sx_af_reg_stats_t mafbi;
    sx_af_reg_stats_t mafri;
} sx_af_regs_stats_t;

typedef struct sx_af_refresh_stats {
    u32     in_progress;
    u32     canceled;
    ktime_t start;
    ktime_t end;
    ktime_t duration;
    u32     num_of_mafbi_traps;
    u32     num_of_mafbi_regs_drops;
    u32     num_of_mafbi_regs;
    u32     num_of_mafti_traps;
    u32     num_of_mafti_regs_drops;
    u32     num_of_mafti_regs;
} sx_af_refresh_stats_t;

typedef struct sx_af_refresh_all_stats {
    u32                   total_refresh_cnt;
    u32                   completed_refresh_cnt;
    sx_af_refresh_stats_t last_refresh;
    sx_af_refresh_stats_t min_refresh;
    sx_af_refresh_stats_t max_refresh;
} sx_af_refresh_all_stats_t;

typedef struct sx_af_counters_user_jobs_stats {
    u32 drops;
} sx_af_counters_user_jobs_stats_t;

typedef struct sx_af_counters_event_jobs_stats {
    ktime_t timer;
    u32     mafti_in_1s;
    u32     max_mafti_in_1s;
    u32     mafti_outside_refresh;
    u32     mafti_drops_reg_len;
    u32     mafti_drops_counter_idx;
    u32     mafti_drops;
    u32     mafbi_drops_reg_len;
    u32     mafbi_drops_rec_type;
    u32     mafbi_drops_counter_idx;
    u32     mafbi_drops;
    u32     mafri_drops_reg_len;
    u32     mafri_drops_counter_idx;
    u32     mafri_drops;
    u32     unknown_drops;
    u32     num_of_mafri_traps;
    u32     num_of_mafri_regs_drops;
    u32     num_of_mafri_regs;
    u32     num_of_mafbi_traps;
    u32     num_of_mafbi_regs_drops;
    u32     num_of_mafbi_regs;
    u32     num_of_mafti_traps;
    u32     num_of_mafti_regs_drops;
    u32     num_of_mafti_regs;
} sx_af_counters_event_jobs_stats_t;

typedef struct sx_af_stats {
    sx_af_critical_issues_stats_t     critical_issues;
    sx_af_regs_stats_t                regs;
    sx_af_refresh_all_stats_t         refresh_all;
    sx_af_counters_user_jobs_stats_t  user_jobs;
    sx_af_counters_event_jobs_stats_t event_jobs;
} sx_af_stats_t;

/************************************************
 * Globals
 ***********************************************/
extern int sx_af_counters_dbg_info_gathering;
extern int sx_af_counters_dbg_info_print_in_hex;

static DEFINE_SPINLOCK(g_af_lock);
static struct sx_af_counters_ctx g_af_counters_ctx;
static bool                      g_af_counters_initialized = false;
static bool                      g_af_deinit_in_progress = false;
static sx_af_stats_t             g_af_stats;

/************************************************
 * Functions
 ***********************************************/
static inline int __sx_af_counters_context_acquire(void);
static inline void __sx_af_counters_context_release(void);
static int __sx_af_counters_buffer_init(u32 counters_num);
static inline void __sx_af_counters_buffer_deinit(void);
static void __sx_af_counters_mafbi_handler_cb(struct work_struct *work_p);
static void __sx_af_counters_mafti_handler_cb(struct work_struct *work_p);
static void __sx_af_counters_mafri_handler_cb(struct work_struct *work_p);
static void __sx_af_counters_alloc_handler_cb(struct work_struct *work_p);
static void __sx_af_counters_move_handler_cb(struct work_struct *work_p);
static void __sx_af_counters_clear_handler_cb(struct work_struct *work_p);
static void __sx_af_counters_read_handler_cb(struct work_struct *work_p);
static void __sx_af_counters_tr_handler_cb(struct work_struct *work_p);
static inline int __sx_af_counters_can_init(void);
static inline int __sx_af_counters_states_set(bool init_state, bool deinit_in_progress);
static inline int __sx_af_counters_ctx_init(struct ku_accuflow_counters_params *af_params_p);
static inline int __sx_af_counters_init_state_set(void);
static inline int __sx_af_counters_deinit_state_in_progress_set(void);
static inline int __sx_af_counters_ctx_deinit(void);
static inline int __sx_af_counters_deinit_state_set(void);
static inline u32 __sx_af_counters_prm_index_to_zero_based(u32 prm_index);
static inline u32 __sx_af_counters_prm_indices_num_get(void);
static void __sx_af_counters_dump(struct seq_file *m, void *v, void *context);

static void __mafbi_parser(const void                                *mafbi_reg,
                           u32                                        reg_len,
                           struct sxd_bulk_cntr_buffer_layout_common *layout_common,
                           void                                      *context);
static void __mafti_parser(const void                                *mafti_reg,
                           u32                                        reg_len,
                           struct sxd_bulk_cntr_buffer_layout_common *layout_common,
                           void                                      *context);
static void __mafri_parser(const void                                *mafri_reg,
                           u32                                        reg_len,
                           struct sxd_bulk_cntr_buffer_layout_common *layout_common,
                           void                                      *context);

static void __sx_af_counters_ktime_dump(struct seq_file *m,
                                        void            *v,
                                        void            *context,
                                        char            *prefix_str_p,
                                        ktime_t         *ktime_p,
                                        char            *suffix_str_p);

static inline void __sx_af_counters_stats_init(void);
static inline void __sx_af_counters_stats_refresh_start(void);
static inline void __sx_af_counters_stats_refresh_cancel(void);
static inline void __sx_af_counters_stats_refresh_end(void);
static inline void __sx_af_counters_stats_mafti_perf_set(ktime_t *ktime_p);
static inline void __sx_af_counters_stats_event_jobs_drop_set(struct completion_info *comp_info_p);
static inline void __sx_af_counters_stats_event_jobs_set(struct completion_info *comp_info_p);
static inline void __sx_af_counters_stats_mafti_set(void);
static inline void __sx_af_counters_stats_mafri_set(void);
static inline void __sx_af_counters_stats_mafbi_set(void);
static inline void __sx_af_counters_stats_mafti_drop_set(void);
static inline void __sx_af_counters_stats_mafri_drop_set(void);
static inline void __sx_af_counters_stats_mafbi_drop_set(void);
static inline void __sx_af_counters_stats_refresh_dump(struct seq_file       *m,
                                                       void                  *v,
                                                       void                  *context,
                                                       sx_af_refresh_stats_t *af_refresh_stats_p);
static inline void __sx_af_counters_stats_reg_dump(struct seq_file   *m,
                                                   void              *v,
                                                   void              *context,
                                                   sx_af_reg_stats_t *af_reg_stats_p);
static void __sx_af_counters_stats_dump(struct seq_file *m, void *v, void *context);

static inline void __sx_af_counters_stats_reg_record_update(sx_af_reg_record_stats_t *record_stats_p,
                                                            u32                       counter_index,
                                                            u32                       bytes_inc,
                                                            u32                       packets_inc);
static inline void __sx_af_counters_stats_reg_record_analyze(sx_af_reg_stats_t *reg_stats_p,
                                                             u32                counter_index,
                                                             u32                bytes_inc,
                                                             u32                packets_inc);
static inline void __sx_af_counters_stats_mafbi_record_analyze(u32 counter_index,
                                                               u32 bytes_inc,
                                                               u32 packets_inc);
static inline void __sx_af_counters_stats_mafti_record_analyze(u32 counter_index,
                                                               u32 bytes_inc,
                                                               u32 packets_inc);
static inline void __sx_af_counters_stats_mafri_record_analyze(u32 counter_index,
                                                               u32 bytes_inc,
                                                               u32 packets_inc);

/************************************************
 * Functions
 ***********************************************/
static inline u32 __sx_af_counters_prm_index_to_zero_based(u32 prm_index)
{
    return prm_index - g_af_counters_ctx.prm_cntr_start_idx_offset;
}

static inline u32 __sx_af_counters_prm_indices_num_get(void)
{
    return g_af_counters_ctx.af_counters_num * g_af_counters_ctx.prm_cntr_lines_flow_both;
}

static inline int __sx_af_counters_can_init(void)
{
    int err = 0;

    spin_lock_bh(&g_af_lock);

    if (g_af_counters_initialized != false) {
        err = -EINVAL;
        printk(KERN_ERR PFX "%s: Accumulated counters have already been initialized, err [%d]\n",
               __func__, err);
        goto out;
    }

    if (g_af_deinit_in_progress != false) {
        err = -EINVAL;
        printk(KERN_ERR PFX "%s: The deinitialization of Accumulated counters is in progress, err [%d]\n",
               __func__, err);
        goto out;
    }

out:
    spin_unlock_bh(&g_af_lock);
    return err;
}

static inline int __sx_af_counters_states_set(bool init_state, bool deinit_in_progress)
{
    spin_lock_bh(&g_af_lock);
    g_af_counters_initialized = init_state;
    g_af_deinit_in_progress = deinit_in_progress;
    spin_unlock_bh(&g_af_lock);
    return 0;
}

static inline void __sx_af_counters_stats_init(void)
{
    memset(&g_af_stats, 0, sizeof(g_af_stats));
    g_af_stats.refresh_all.min_refresh.duration = ktime_set(1, 0);
    g_af_stats.regs.mafti.min_bytes_records.bytes_inc = U32_MAX;
    g_af_stats.regs.mafti.min_packets_records.packets_inc = U32_MAX;
    g_af_stats.regs.mafbi.min_bytes_records.bytes_inc = U32_MAX;
    g_af_stats.regs.mafbi.min_packets_records.packets_inc = U32_MAX;
}

static inline int __sx_af_counters_ctx_init(struct ku_accuflow_counters_params *af_params_p)
{
    int  err = 0;
    bool is_buffer_initialized = false;
    bool is_wq_initialized = false;

    __sx_af_counters_stats_init();

    err = __sx_af_counters_buffer_init(af_params_p->op_data.init_data.prm_counters_num);
    if (err) {
        printk(KERN_ERR PFX "%s: Failed to initialize kernel buffer for Accumulated counters, err [%d]\n",
               __func__, err);
        goto out;
    }
    is_buffer_initialized = true;

    g_af_counters_ctx.af_counters_wq_p = sx_health_check_create_monitored_workqueue("accuflow_wq");
    if (IS_ERR(g_af_counters_ctx.af_counters_wq_p)) {
        err = -ENOMEM;
        printk(KERN_ERR PFX "%s: Failed to create a work queue for Accumulated counters, err [%d]\n",
               __func__, err);
        goto out;
    }
    is_wq_initialized = true;

    g_af_counters_ctx.packets_inc_unit = af_params_p->op_data.init_data.packets_inc_unit;
    g_af_counters_ctx.bytes_inc_unit = af_params_p->op_data.init_data.bytes_inc_unit;
    g_af_counters_ctx.prm_cntr_lines_per_bank = af_params_p->op_data.init_data.prm_cntr_lines_per_bank;
    g_af_counters_ctx.prm_cntr_banks = af_params_p->op_data.init_data.prm_cntr_banks;
    g_af_counters_ctx.prm_cntr_lines_flow_both = af_params_p->op_data.init_data.prm_cntr_lines_flow_both;
    g_af_counters_ctx.prm_cntr_type_flow_both = af_params_p->op_data.init_data.prm_cntr_type_flow_both;
    g_af_counters_ctx.prm_cntr_start_idx_offset = af_params_p->op_data.init_data.prm_cntr_start_idx_offset;

    err = sx_af_dbg_info_init();
    if (err) {
        printk(KERN_ERR PFX "%s: Failed to initialize debug infrastructure for Accumulated counters, err [%d]\n",
               __func__, err);
        goto out;
    }

out:
    if (err) {
        if (is_wq_initialized) {
            sx_health_check_destroy_monitored_workqueue(g_af_counters_ctx.af_counters_wq_p);
            g_af_counters_ctx.af_counters_wq_p = NULL;
        }
        if (is_buffer_initialized) {
            __sx_af_counters_buffer_deinit();
        }
    }

    return err;
}

static inline int __sx_af_counters_init_state_set(void)
{
    return __sx_af_counters_states_set(true, false);
}

int sx_af_counters_init(struct ku_accuflow_counters_params *af_params_p)
{
    int err = 0;

    err = __sx_af_counters_can_init();
    if (err) {
        goto out;
    }

    mb();

    err = __sx_af_counters_ctx_init(af_params_p);
    if (err) {
        goto out;
    }

    mb();

    __sx_af_counters_init_state_set();

out:
    if (err) {
        sx_af_counters_deinit();
    }
    return err;
}

static inline int __sx_af_counters_deinit_state_in_progress_set(void)
{
    int err = 0;

    if (__sx_af_counters_context_acquire()) {
        printk(KERN_NOTICE "%s: Trying to de-initialize Accumulated counters module "
               "when it is uninitialized! \n", __func__);
        err = -EINVAL;
        goto out;
    }

    g_af_deinit_in_progress = true;

    __sx_af_counters_context_release();

out:
    return err;
}

static inline int __sx_af_counters_ctx_deinit(void)
{
    sx_health_check_destroy_monitored_workqueue(g_af_counters_ctx.af_counters_wq_p);
    g_af_counters_ctx.af_counters_wq_p = NULL;

    mb();

    sx_af_dbg_info_deinit();

    __sx_af_counters_buffer_deinit();

    return 0;
}

static inline int __sx_af_counters_deinit_state_set(void)
{
    return __sx_af_counters_states_set(false, false);
}

int sx_af_counters_deinit(void)
{
    int err = 0;

    err = __sx_af_counters_deinit_state_in_progress_set();
    if (err) {
        goto out;
    }

    mb();

    __sx_af_counters_ctx_deinit();

    mb();

    __sx_af_counters_deinit_state_set();

out:
    return err;
}

static inline int __sx_af_counters_context_acquire(void)
{
    if ((g_af_counters_initialized == false) || (g_af_deinit_in_progress != false)) {
        return -EINVAL;
    }

    spin_lock_bh(&g_af_lock);

    if ((g_af_counters_initialized == false) || (g_af_deinit_in_progress != false)) {
        spin_unlock_bh(&g_af_lock);
        return -EINVAL;
    }

    return 0;
}

static inline void __sx_af_counters_context_release(void)
{
    spin_unlock_bh(&g_af_lock);
}

static int __sx_af_counters_buffer_init(u32 counters_num)
{
    int err = 0;

    g_af_counters_ctx.af_counters_num = counters_num;
    g_af_counters_ctx.af_counters_buffer_p = vmalloc(counters_num * 2 * sizeof(u64));
    if (g_af_counters_ctx.af_counters_buffer_p == NULL) {
        err = -ENOMEM;
        printk(KERN_ERR PFX "%s: failed to allocate memory for Accumulated counters buffer, err [%d]\n",
               __func__, err);
        goto out;
    }

    memset(g_af_counters_ctx.af_counters_buffer_p, 0, counters_num * 2 * sizeof(u64));

out:
    if (err) {
        if (g_af_counters_ctx.af_counters_buffer_p) {
            vfree(g_af_counters_ctx.af_counters_buffer_p);
            g_af_counters_ctx.af_counters_buffer_p = NULL;
        }
    }

    return err;
}

static inline void __sx_af_counters_buffer_deinit(void)
{
    if (g_af_counters_ctx.af_counters_buffer_p) {
        vfree(g_af_counters_ctx.af_counters_buffer_p);
        g_af_counters_ctx.af_counters_buffer_p = NULL;
    } else {
        printk(KERN_ERR PFX "%s: g_af_counters_ctx.af_counters_buffer_p is NULL \n",
               __func__);
    }
}

static int __sx_af_counter_refresh_done_event_send(void)
{
    sxd_bulk_cntr_refresh_done_notification_t event;
    int                                       err;

    memset(&event, 0, sizeof(event));
    memcpy(&event.counter_refresh_attr, &g_af_counters_ctx.refresh_attr, sizeof(event.counter_refresh_attr));

    err = send_trap(&event,
                    sizeof(event),
                    SXD_TRAP_ID_BULK_COUNTER_REFRESH_DONE_EVENT,
                    0, /* is_from_user */
                    1, /* device_id */
                    TARGET_PID_DONT_CARE,
                    GFP_ATOMIC);
    if (err) {
        printk(KERN_ERR "failed to send notification for bulk-counter refresh completion.\n");
    }

    return err;
}

int sx_af_counters_tr_reservation_set(ku_accuflow_counters_params_data_tr_reservation_t *tr_reservation_p)
{
    int err = 0;

    switch (tr_reservation_p->action) {
    case KU_ACCUFLOW_COUNTERS_PARAMS_DATA_TR_RESERVATION_ACTION_ACQUIRE_E:
        err = bulk_cntr_db_mocs_session_acquire(SXD_BULK_CNTR_KEY_TYPE_ACCUFLOW_E);
        if (err) {
            goto out;
        }

        memcpy(&g_af_counters_ctx.refresh_attr, &(tr_reservation_p->refresh_attr),
               sizeof(g_af_counters_ctx.refresh_attr));

        __sx_af_counters_stats_refresh_start();
        break;

    case KU_ACCUFLOW_COUNTERS_PARAMS_DATA_TR_RESERVATION_ACTION_RELEASE_E:
        err = bulk_cntr_db_mocs_session_release(SXD_BULK_CNTR_KEY_TYPE_ACCUFLOW_E);
        if (err) {
            goto out;
        }

        memset(&g_af_counters_ctx.refresh_attr, 0, sizeof(g_af_counters_ctx.refresh_attr));
        __sx_af_counters_stats_refresh_cancel();
        break;

    default:
        printk(KERN_ERR "Invalid action for the refresh reservation: %d.\n",
               tr_reservation_p->action);
        err = -EINVAL;
        goto out;
    }

out:
    return err;
}

void sx_af_counters_mocs_done(void)
{
    __sx_af_counter_refresh_done_event_send();
    mb();
    bulk_cntr_db_mocs_session_release(SXD_BULK_CNTR_KEY_TYPE_ACCUFLOW_E);
    mb();
    __sx_af_counters_stats_refresh_end();
}

int sx_af_counters_user_job_schedule(struct ku_accuflow_counters_params *af_params_p)
{
    int                                        err = 0;
    struct sx_af_counters_work                *af_counter_work_p = NULL;
    u8                                         locked = false;
    u8                                         tr_set = false;
    struct completion                          read_completion;
    struct ku_bulk_cntr_transaction_add        bulk_cntr_tr_add;
    bool                                       wq_err = false;
    struct sxd_bulk_cntr_buffer_layout_common *layout_common = NULL;

    af_counter_work_p = kmalloc(sizeof(*af_counter_work_p), GFP_KERNEL);
    if (af_counter_work_p == NULL) {
        err = -ENOMEM;
        printk(KERN_ERR PFX "Memory allocation for Accumulated counter data failed, "
               "dropping a user job request [type %d] \n",
               af_params_p->op);
        goto out;
    }

    memset(af_counter_work_p, 0, sizeof(struct sx_af_counters_work));
    memcpy(&af_counter_work_p->data.af_params, af_params_p, sizeof(struct ku_accuflow_counters_params));

    switch (af_params_p->op) {
    case KU_ACCUFLOW_COUNTERS_PARAMS_OP_ALLOC_E:
        INIT_WORK(&af_counter_work_p->ws, __sx_af_counters_alloc_handler_cb);
        break;

    case KU_ACCUFLOW_COUNTERS_PARAMS_OP_MOVE_E:
        INIT_WORK(&af_counter_work_p->ws, __sx_af_counters_move_handler_cb);
        break;

    case KU_ACCUFLOW_COUNTERS_PARAMS_OP_CLEAR_E:
        INIT_WORK(&af_counter_work_p->ws, __sx_af_counters_clear_handler_cb);
        break;

    case KU_ACCUFLOW_COUNTERS_PARAMS_OP_READ_E:
        INIT_WORK(&af_counter_work_p->ws, __sx_af_counters_read_handler_cb);

        init_completion(&read_completion);
        af_counter_work_p->completion_p = &read_completion;
        break;

    case KU_ACCUFLOW_COUNTERS_PARAMS_OP_TRASACTION_START_E:
        INIT_WORK(&af_counter_work_p->ws, __sx_af_counters_tr_handler_cb);

        if (af_params_p->op_data.transaction_data.cancel == 0) {
            layout_common = (struct sxd_bulk_cntr_buffer_layout_common *)sx_mmap_user_to_kernel(
                af_params_p->op_data.transaction_data.ev_id.event_id_fields.client_id,
                af_params_p->op_data.transaction_data.buffer_id);
            if (!layout_common) {
                err = -EINVAL;
                printk(KERN_ERR PFX "Failed to start an Accumulated transaction - event id %llu, buffer_id %lu \n",
                       af_params_p->op_data.transaction_data.ev_id.event_id_value,
                       af_params_p->op_data.transaction_data.buffer_id);
                goto out;
            }

            af_counter_work_p->layout_flow = (struct sxd_bulk_cntr_buffer_layout_flow*)layout_common;
            af_counter_work_p->layout_flow->base_counter_id = af_params_p->op_data.transaction_data.base_counter_id;

            bulk_cntr_tr_add.buffer_id = af_params_p->op_data.transaction_data.buffer_id;
            bulk_cntr_tr_add.event_id = af_params_p->op_data.transaction_data.ev_id;
            bulk_cntr_tr_add.params.flow_params.base_counter_id =
                af_params_p->op_data.transaction_data.base_counter_id;
            err = bulk_cntr_db_add(&bulk_cntr_tr_add);
            if (err) {
                goto out;
            }
            tr_set = true;
        } else {
            err = bulk_cntr_db_cancel(af_params_p->op_data.transaction_data.ev_id.event_id_fields.client_id,
                                      af_params_p->op_data.transaction_data.buffer_id);
            goto out;
        }
        break;

    default:
        printk(KERN_ERR PFX "Unknown Accumulated operation: %d.\n", af_params_p->op);
        err = -EINVAL;
        goto out;
    }

    if (__sx_af_counters_context_acquire()) {
        err = -EINVAL;
        goto out;
    }
    locked = true;

    wq_err = queue_work(g_af_counters_ctx.af_counters_wq_p, &af_counter_work_p->ws);
    if (wq_err == false) {
        err = -EAGAIN;
        printk(KERN_WARNING PFX "Failed to schedule the Accumulated counter ws, dropping RX packet\n");
        goto out;
    }

out:
    if (locked) {
        __sx_af_counters_context_release();
    }

    if (af_params_p->op == KU_ACCUFLOW_COUNTERS_PARAMS_OP_READ_E) {
        if (!err) {
            /* 1s = 1000 msecs
             *  the refresh of all accumulated counters can take up to 300 msecs
             *  and if in the same time SDK does the relocation/freeing of accumulated counters
             *  than it can up to 400 msecs. On average it should be much faster.
             *  Even if the refresh is in progress, a read op should still be schedule
             *  in between multi-reg MAFBI EMADs.
             *  So the timeout of 2 sec is big enough. */
            if (wait_for_completion_timeout(&read_completion, msecs_to_jiffies(2000)) == 0) {
                err = -ETIMEDOUT;
                printk(KERN_ERR PFX "After the 2 seconds wait, the Accumulated thread still didn't return a counter \n");
            } else if (af_counter_work_p) {
                memcpy(af_params_p, &af_counter_work_p->data.af_params, sizeof(struct ku_accuflow_counters_params));
                kfree(af_counter_work_p);
            }
        }
    } else {
        if (err) {
            if (tr_set) {
                bulk_cntr_db_del(af_params_p->op_data.transaction_data.ev_id.event_id_fields.client_id,
                                 af_params_p->op_data.transaction_data.buffer_id);
            }

            if (af_counter_work_p) {
                kfree(af_counter_work_p);
            }
        }
    }

    return err;
}

static void __sx_af_counters_alloc_handler_cb(struct work_struct *work_p)
{
    struct sx_af_counters_work *af_work_p = container_of(work_p, struct sx_af_counters_work, ws);
    u32                         index = 0;
    sxd_flow_counter_set_t     *counter_p = NULL;

    index = __sx_af_counters_prm_index_to_zero_based(af_work_p->data.af_params.op_data.alloc_data.prm_counter_idx);
    if (index >= __sx_af_counters_prm_indices_num_get()) {
        printk(KERN_ERR PFX "Failed to allocate a counter because of invalid index %u [%u, %u]\n",
               index, af_work_p->data.af_params.op_data.alloc_data.prm_counter_idx,
               g_af_counters_ctx.prm_cntr_start_idx_offset);
        goto out;
    }
    counter_p = (sxd_flow_counter_set_t *)&g_af_counters_ctx.af_counters_buffer_p[index];

    for (index = 0;
         index < af_work_p->data.af_params.op_data.alloc_data.num_of_counters;
         index++, counter_p++) {
        counter_p->flow_counter_bytes = 0;
        counter_p->flow_counter_packets = 0;
    }

out:
    kfree(af_work_p);
}

static void __sx_af_counters_move_handler_cb(struct work_struct *work_p)
{
    struct sx_af_counters_work *af_work_p = container_of(work_p, struct sx_af_counters_work, ws);
    u32                         idx = 0;
    u32                         old_index = 0;
    u32                         new_index = 0;
    sxd_flow_counter_set_t     *old_counter_p = NULL;
    sxd_flow_counter_set_t     *new_counter_p = NULL;

    old_index = __sx_af_counters_prm_index_to_zero_based(
        af_work_p->data.af_params.op_data.move_data.old_prm_counter_idx);
    if (old_index >= __sx_af_counters_prm_indices_num_get()) {
        printk(KERN_ERR PFX "Failed to move counters data because of invalid old index %u [%u, %u]\n",
               old_index, af_work_p->data.af_params.op_data.move_data.old_prm_counter_idx,
               g_af_counters_ctx.prm_cntr_start_idx_offset);
        goto out;
    }
    old_counter_p = (sxd_flow_counter_set_t *)&g_af_counters_ctx.af_counters_buffer_p[old_index];

    new_index = __sx_af_counters_prm_index_to_zero_based(
        af_work_p->data.af_params.op_data.move_data.new_prm_counter_idx);
    if (new_index >= __sx_af_counters_prm_indices_num_get()) {
        printk(KERN_ERR PFX "Failed to move counters data because of invalid new index %u [%u, %u]\n",
               new_index, af_work_p->data.af_params.op_data.move_data.new_prm_counter_idx,
               g_af_counters_ctx.prm_cntr_start_idx_offset);
        goto out;
    }
    new_counter_p = (sxd_flow_counter_set_t *)&g_af_counters_ctx.af_counters_buffer_p[new_index];

    for (idx = 0;
         idx < af_work_p->data.af_params.op_data.move_data.num_of_counters;
         idx++, new_counter_p++, old_counter_p++) {
        new_counter_p->flow_counter_bytes = old_counter_p->flow_counter_bytes;
        new_counter_p->flow_counter_packets = old_counter_p->flow_counter_packets;
    }

out:
    kfree(af_work_p);
}

static void __sx_af_counters_clear_handler_cb(struct work_struct *work_p)
{
    struct sx_af_counters_work *af_work_p = container_of(work_p, struct sx_af_counters_work, ws);
    u32                         zero_based_counter_index = 0;
    u32                         idx = 0;
    sxd_flow_counter_set_t     *counter_p = NULL;

    zero_based_counter_index = __sx_af_counters_prm_index_to_zero_based(
        af_work_p->data.af_params.op_data.clear_data.prm_counter_idx);
    if (zero_based_counter_index >= __sx_af_counters_prm_indices_num_get()) {
        printk(KERN_ERR PFX "Failed to clear a counter because of invalid index %u [%u, %u]\n",
               zero_based_counter_index, af_work_p->data.af_params.op_data.clear_data.prm_counter_idx,
               g_af_counters_ctx.prm_cntr_start_idx_offset);
        goto out;
    }

    counter_p = (sxd_flow_counter_set_t *)&g_af_counters_ctx.af_counters_buffer_p[zero_based_counter_index];

    for (;
         idx < af_work_p->data.af_params.op_data.clear_data.num_of_counters;
         idx++, counter_p++) {
        counter_p->flow_counter_bytes = 0;
        counter_p->flow_counter_packets = 0;
    }

out:
    kfree(af_work_p);
}

static void __sx_af_counters_read_handler_cb(struct work_struct *work_p)
{
    struct sx_af_counters_work *af_work_p = container_of(work_p, struct sx_af_counters_work, ws);
    u32                         zero_based_counter_index = 0;
    u32                         counters_read = 0;
    sxd_flow_counter_set_t     *counter_p = NULL;

    zero_based_counter_index = __sx_af_counters_prm_index_to_zero_based(
        af_work_p->data.af_params.op_data.read_data.prm_counter_idx);
    if (zero_based_counter_index >= __sx_af_counters_prm_indices_num_get()) {
        printk(KERN_ERR PFX "Failed to read a counter because of invalid index %u [%u, %u]\n",
               zero_based_counter_index, af_work_p->data.af_params.op_data.read_data.prm_counter_idx,
               g_af_counters_ctx.prm_cntr_start_idx_offset);
        goto out;
    }
    counter_p = (sxd_flow_counter_set_t *)&g_af_counters_ctx.af_counters_buffer_p[zero_based_counter_index];

    for (;
         counters_read < af_work_p->data.af_params.op_data.read_data.num_of_counters;
         counters_read++, counter_p++) {
        af_work_p->data.af_params.op_data.read_data.counters_values[counters_read].flow_counter_bytes =
            counter_p->flow_counter_bytes;
        af_work_p->data.af_params.op_data.read_data.counters_values[counters_read].flow_counter_packets =
            counter_p->flow_counter_packets;
    }

out:
    complete(af_work_p->completion_p);
}

static void __sx_af_counters_tr_handler_cb(struct work_struct *work_p)
{
    struct sx_af_counters_work *af_work_p = container_of(work_p,
                                                         struct sx_af_counters_work,
                                                         ws);
    struct ku_accuflow_counters_params      *af_params_p = &af_work_p->data.af_params;
    u32                                      index = 0;
    sxd_flow_counter_set_t                  *counter_p = NULL;
    struct sxd_bulk_cntr_buffer_layout_flow *layout_flow = af_work_p->layout_flow;
    int                                      err = 0;
    u8                                       in_progress = 0;

    index =
        __sx_af_counters_prm_index_to_zero_based(af_work_p->data.af_params.op_data.transaction_data.prm_counter_id);
    if (index >= __sx_af_counters_prm_indices_num_get()) {
        printk(KERN_ERR PFX "Failed to start a transaction for counters because of invalid index %u [%u, %u]\n",
               index, af_work_p->data.af_params.op_data.transaction_data.prm_counter_id,
               g_af_counters_ctx.prm_cntr_start_idx_offset);
        goto out;
    }
    counter_p = (sxd_flow_counter_set_t *)&g_af_counters_ctx.af_counters_buffer_p[index];

    err = bulk_cntr_db_in_progress_get(SXD_BULK_CNTR_KEY_TYPE_ACCUFLOW_E, &in_progress);
    if (err) {
        goto out;
    }

    if (in_progress) {
        memcpy(layout_flow->counters, counter_p,
               sizeof(sxd_flow_counter_set_t) * af_params_p->op_data.transaction_data.num_of_counters);

        if (af_params_p->op_data.transaction_data.clear) {
            memset(counter_p, 0,
                   sizeof(sxd_flow_counter_set_t) * af_params_p->op_data.transaction_data.num_of_counters);
        }

        layout_flow->common.counters_received_so_far = layout_flow->common.num_of_counters;
    }

    err = sx_bulk_cntr_handle_ack(&af_params_p->op_data.transaction_data.ev_id,
                                  af_params_p->op_data.transaction_data.buffer_id);
    if (err) {
        goto out;
    }

out:
    kfree(af_work_p);
}

void sx_af_counters_event_job_schedule(struct completion_info *comp_info_p)
{
    int                         err = 0;
    u8                          skb_got = false;
    struct sx_af_counters_work *af_counter_work_p = NULL;
    struct sx_dev              *sx_dev_p = comp_info_p->dev;
    struct sk_buff             *skb_p = comp_info_p->skb;
    bool                        wq_err = false;
    bool                        locked = false;

    if (__sx_af_counters_context_acquire()) {
        err = -EINVAL;
        goto out;
    }
    locked = true;

    af_counter_work_p = kmalloc(sizeof(*af_counter_work_p), GFP_ATOMIC);
    if (af_counter_work_p == NULL) {
        __sx_af_counters_stats_event_jobs_drop_set(comp_info_p);
        err = -ENOMEM;
        printk(KERN_WARNING PFX "Memory allocation for Accumulated counter data failed, "
               "dropping an Accumulated event job\n");
        goto out;
    }

    af_counter_work_p->ktime = ktime_get_real();

    af_counter_work_p->dev_p = sx_dev_p;
    af_counter_work_p->data.skb_p = skb_p;
    if (comp_info_p->hw_synd == SXD_TRAP_ID_ACCU_FLOW_INC) {
        INIT_WORK(&af_counter_work_p->ws, __sx_af_counters_mafti_handler_cb);
        __sx_af_counters_stats_mafti_perf_set(&af_counter_work_p->ktime);
    } else if (comp_info_p->hw_synd == SXD_TRAP_ID_MAFBI) {
        INIT_WORK(&af_counter_work_p->ws, __sx_af_counters_mafbi_handler_cb);
    } else if (comp_info_p->hw_synd == SXD_TRAP_ID_MAFRI) {
        INIT_WORK(&af_counter_work_p->ws, __sx_af_counters_mafri_handler_cb);
    } else {
        __sx_af_counters_stats_event_jobs_drop_set(comp_info_p);
        err = -EINVAL;
        printk(KERN_WARNING PFX "Unexpected event in the Accumulated handler");
        goto out;
    }

    skb_get(skb_p);
    skb_got = true;

    wq_err = queue_work(g_af_counters_ctx.af_counters_wq_p, &af_counter_work_p->ws);
    if (wq_err == false) {
        __sx_af_counters_stats_event_jobs_drop_set(comp_info_p);
        err = -EAGAIN;
        printk(KERN_WARNING PFX "Failed to schedule an Accumulated event job\n");
        goto out;
    }

    __sx_af_counters_stats_event_jobs_set(comp_info_p);

out:
    if (locked) {
        __sx_af_counters_context_release();
    }

    if (err) {
        if (af_counter_work_p) {
            kfree(af_counter_work_p);
        }

        if (skb_got) {
            kfree_skb(skb_p);   /* drop packet flow, use kfree_skb */
        }
    }

    return;
}

static void __sx_af_counters_mafti_handler_cb(struct work_struct *work_p)
{
    struct sx_af_counters_work *af_work_p = container_of(work_p, struct sx_af_counters_work, ws);

    sx_bulk_cntr_multi_emad_parse(af_work_p->data.skb_p->data,
                                  af_work_p->data.skb_p->len,
                                  __mafti_parser,
                                  af_work_p, false);

    consume_skb(af_work_p->data.skb_p); /* free unused skb, use consume_skb */
    kfree(af_work_p);
}

static void __sx_af_counters_mafri_handler_cb(struct work_struct *work_p)
{
    struct sx_af_counters_work *af_work_p = container_of(work_p, struct sx_af_counters_work, ws);

    sx_bulk_cntr_multi_emad_parse(af_work_p->data.skb_p->data,
                                  af_work_p->data.skb_p->len,
                                  __mafri_parser,
                                  af_work_p, false);

    consume_skb(af_work_p->data.skb_p); /* free unused skb, use consume_skb */
    kfree(af_work_p);
}


static inline void __sx_af_counters_stats_reg_record_update(sx_af_reg_record_stats_t *record_stats_p,
                                                            u32                       counter_index,
                                                            u32                       bytes_inc,
                                                            u32                       packets_inc)
{
    record_stats_p->bytes_inc = bytes_inc;
    record_stats_p->packets_inc = packets_inc;
    record_stats_p->counter_index = counter_index;
}

static inline void __sx_af_counters_stats_reg_record_analyze(sx_af_reg_stats_t *reg_stats_p,
                                                             u32                counter_index,
                                                             u32                bytes_inc,
                                                             u32                packets_inc)
{
    if (bytes_inc > reg_stats_p->max_bytes_records.bytes_inc) {
        __sx_af_counters_stats_reg_record_update(&reg_stats_p->max_bytes_records,
                                                 counter_index, bytes_inc, packets_inc);
    }

    if (packets_inc > reg_stats_p->max_packets_records.packets_inc) {
        __sx_af_counters_stats_reg_record_update(&reg_stats_p->max_packets_records,
                                                 counter_index, bytes_inc, packets_inc);
    }

    if (bytes_inc < reg_stats_p->min_bytes_records.bytes_inc) {
        __sx_af_counters_stats_reg_record_update(&reg_stats_p->min_bytes_records,
                                                 counter_index, bytes_inc, packets_inc);
    }

    if (packets_inc < reg_stats_p->min_packets_records.packets_inc) {
        __sx_af_counters_stats_reg_record_update(&reg_stats_p->min_packets_records,
                                                 counter_index, bytes_inc, packets_inc);
    }
}


static inline void __sx_af_counters_stats_mafbi_record_analyze(u32 counter_index, u32 bytes_inc, u32 packets_inc)
{
    __sx_af_counters_stats_reg_record_analyze(&g_af_stats.regs.mafbi, counter_index, bytes_inc, packets_inc);
}

static inline void __sx_af_counters_stats_mafti_record_analyze(u32 counter_index, u32 bytes_inc, u32 packets_inc)
{
    __sx_af_counters_stats_reg_record_analyze(&g_af_stats.regs.mafti, counter_index, bytes_inc, packets_inc);
}

static inline void __sx_af_counters_stats_mafri_record_analyze(u32 counter_index, u32 bytes_inc, u32 packets_inc)
{
    __sx_af_counters_stats_reg_record_analyze(&g_af_stats.regs.mafri, counter_index, bytes_inc, packets_inc);
}

static void __mafti_parser(const void                                *mafti_reg,
                           u32                                        reg_len,
                           struct sxd_bulk_cntr_buffer_layout_common *layout_common,
                           void                                      *context)
{
    struct sx_af_counters_work *af_work_p = (struct sx_af_counters_work *)context;
    const sxd_emad_mafti_reg_t *mafti = (const sxd_emad_mafti_reg_t *)mafti_reg;
    u8                          num_rec = 0;
    u8                          index = 0;
    u32                         counter_index = 0;
    u64                         bytes_inc = 0;
    u64                         packets_inc = 0;
    sxd_flow_counter_set_t     *counter_p = NULL;
    cbuf_record_t               record;

    if (reg_len != MLXSW_MAFTI_LEN) {
        printk(KERN_ERR PFX "MAFTI parse: reg_len is less than expected len (reg_len=%u, expected=%u)\n",
               reg_len, MLXSW_MAFTI_LEN);
        g_af_stats.event_jobs.mafti_drops_reg_len++;
        __sx_af_counters_stats_mafti_drop_set();
        return;
    }

    num_rec = mlxsw_reg_mafti_num_rec_get(mafti->reg);
    for (index = 0; index < num_rec; index++) {
        counter_index = __sx_af_counters_prm_index_to_zero_based(mlxsw_reg_mafti_counter_index_get(mafti->reg, 0,
                                                                                                   index));
        if (counter_index >= __sx_af_counters_prm_indices_num_get()) {
            printk(KERN_ERR PFX "counter_index %u exceeds number of counters %u \n",
                   counter_index, __sx_af_counters_prm_indices_num_get());
            g_af_stats.event_jobs.mafti_drops_counter_idx++;
            __sx_af_counters_stats_mafti_drop_set();
            continue;
        }

        bytes_inc = mlxsw_reg_mafti_bytes_inc_get(mafti->reg, 0, index);
        packets_inc = mlxsw_reg_mafti_packets_inc_get(mafti->reg, 0, index);

        counter_p = (sxd_flow_counter_set_t *)&g_af_counters_ctx.af_counters_buffer_p[counter_index];

        counter_p->flow_counter_bytes += bytes_inc * g_af_counters_ctx.bytes_inc_unit +
                                         packets_inc * g_af_counters_ctx.packets_inc_unit * 64;

        counter_p->flow_counter_packets += packets_inc * g_af_counters_ctx.packets_inc_unit;

        __sx_af_counters_stats_mafti_record_analyze(counter_index, bytes_inc, packets_inc);
    }

    if (sx_af_counters_dbg_info_gathering) {
        memset(&record, 0, sizeof(record));
        record.type = CBUF_RECORD_TYPE_MAFTI_E;
        memcpy(record.data.mafti_reg.reg, mafti->reg, sizeof(mafti->reg));
        memcpy(&record.ts, &af_work_p->ktime, sizeof(record.ts));
        sx_af_dbg_info_push(&record);
    }

    __sx_af_counters_stats_mafti_set();
}

static void __mafri_parser(const void                                *mafri_reg,
                           u32                                        reg_len,
                           struct sxd_bulk_cntr_buffer_layout_common *layout_common,
                           void                                      *context)
{
    struct sx_af_counters_work *af_work_p = (struct sx_af_counters_work *)context;
    const sxd_emad_mafri_reg_t *mafri = (const sxd_emad_mafri_reg_t *)mafri_reg;
    u8                          num_rec = 0;
    u8                          index = 0;
    u32                         counter_index = 0;
    u64                         bytes_inc = 0;
    u64                         packets_inc = 0;
    sxd_flow_counter_set_t     *counter_p = NULL;
    cbuf_record_t               record;

    if (reg_len != MLXSW_MAFRI_LEN) {
        printk(KERN_ERR PFX "MAFRI parse: reg_len is less than expected len (reg_len=%u, expected=%u)\n",
               reg_len, MLXSW_MAFRI_LEN);
        g_af_stats.event_jobs.mafri_drops_reg_len++;
        __sx_af_counters_stats_mafri_drop_set();
        return;
    }

    num_rec = mlxsw_reg_mafri_num_rec_get(mafri->reg);
    counter_index = __sx_af_counters_prm_index_to_zero_based(mlxsw_reg_mafri_counter_index_base_get(mafri->reg));
    if (counter_index >= __sx_af_counters_prm_indices_num_get()) {
        printk(KERN_ERR PFX "counter_index %u exceeds number of counters %u \n",
               counter_index, __sx_af_counters_prm_indices_num_get());
        g_af_stats.event_jobs.mafri_drops_counter_idx++;
        __sx_af_counters_stats_mafri_drop_set();
        return;
    }
    counter_p = (sxd_flow_counter_set_t *)&g_af_counters_ctx.af_counters_buffer_p[counter_index];

    for (index = 0; index < num_rec; index++, counter_p++) {
        bytes_inc = mlxsw_reg_mafri_bytes_inc_get(mafri->reg, 0, index);
        packets_inc = mlxsw_reg_mafri_packets_inc_get(mafri->reg, 0, index);

        counter_p->flow_counter_bytes += bytes_inc * g_af_counters_ctx.bytes_inc_unit +
                                         packets_inc * g_af_counters_ctx.packets_inc_unit * 64;

        counter_p->flow_counter_packets += packets_inc * g_af_counters_ctx.packets_inc_unit;

        __sx_af_counters_stats_mafri_record_analyze(counter_index, bytes_inc, packets_inc);
    }

    if (sx_af_counters_dbg_info_gathering) {
        memset(&record, 0, sizeof(record));
        record.type = CBUF_RECORD_TYPE_MAFRI_E;
        memcpy(record.data.mafri_reg.reg, mafri->reg, sizeof(mafri->reg));
        memcpy(&record.ts, &af_work_p->ktime, sizeof(record.ts));
        sx_af_dbg_info_push(&record);
    }

    __sx_af_counters_stats_mafri_set();
}

static void __sx_af_counters_mafbi_handler_cb(struct work_struct *work_p)
{
    struct sx_af_counters_work *af_work_p = container_of(work_p, struct sx_af_counters_work, ws);

    sx_bulk_cntr_multi_emad_parse(af_work_p->data.skb_p->data,
                                  af_work_p->data.skb_p->len,
                                  __mafbi_parser,
                                  af_work_p, false);

    consume_skb(af_work_p->data.skb_p); /* free unused skb, use consume_skb */
    kfree(af_work_p);
}

static void __mafbi_parser(const void                                *mafbi_reg,
                           u32                                        reg_len,
                           struct sxd_bulk_cntr_buffer_layout_common *layout_common,
                           void                                      *context)
{
    struct sx_af_counters_work *af_work_p = (struct sx_af_counters_work *)context;
    const sxd_emad_mafbi_reg_t *mafbi = (const sxd_emad_mafbi_reg_t *)mafbi_reg;
    u8                          num_rec = 0;
    u8                          index = 0;
    u32                         counter_index = 0;
    u64                         bytes_inc = 0;
    u64                         packets_inc = 0;
    sxd_flow_counter_set_t     *counter_p = NULL;
    cbuf_record_t               record;

    if (reg_len != MLXSW_MAFBI_LEN) {
        printk(KERN_ERR PFX "MAFBI parse: reg_len is less than expected len (reg_len=%u, expected=%u)\n",
               reg_len, MLXSW_MAFBI_LEN);
        g_af_stats.event_jobs.mafbi_drops_reg_len++;
        __sx_af_counters_stats_mafbi_drop_set();
        return;
    }

    if (mlxsw_reg_mafbi_type_get(mafbi->reg) != SXD_MAFBI_TYPE_ENTRY_TYPE0_E) {
        printk(KERN_ERR PFX "MAFBI parse: Unexpected type - %u (expected=%u)\n",
               mlxsw_reg_mafbi_type_get(mafbi->reg), SXD_MAFBI_TYPE_ENTRY_TYPE0_E);
        g_af_stats.event_jobs.mafbi_drops_rec_type++;
        __sx_af_counters_stats_mafbi_drop_set();
        return;
    }

    num_rec = mlxsw_reg_mafbi_num_rec_get(mafbi->reg);
    for (index = 0; index < num_rec; index++) {
        counter_index = __sx_af_counters_prm_index_to_zero_based(mlxsw_reg_mafbi_counter_index_get(
                                                                     mafbi->reg, 0,
                                                                     index));
        if (counter_index >= __sx_af_counters_prm_indices_num_get()) {
            printk(KERN_ERR PFX "counter_index %u exceeds number of counters %u \n",
                   counter_index, __sx_af_counters_prm_indices_num_get());
            g_af_stats.event_jobs.mafbi_drops_counter_idx++;
            __sx_af_counters_stats_mafbi_drop_set();
            continue;
        }

        bytes_inc = mlxsw_reg_mafbi_bytes_inc_get(mafbi->reg, 0, index);
        packets_inc = mlxsw_reg_mafbi_packets_inc_get(mafbi->reg, 0, index);

        counter_p = (sxd_flow_counter_set_t *)&g_af_counters_ctx.af_counters_buffer_p[counter_index];

        counter_p->flow_counter_packets += packets_inc * g_af_counters_ctx.packets_inc_unit;

        counter_p->flow_counter_bytes += bytes_inc * g_af_counters_ctx.bytes_inc_unit +
                                         packets_inc * g_af_counters_ctx.packets_inc_unit * 64;

        __sx_af_counters_stats_mafbi_record_analyze(counter_index, bytes_inc, packets_inc);
    }

    if (sx_af_counters_dbg_info_gathering) {
        memset(&record, 0, sizeof(record));
        record.type = CBUF_RECORD_TYPE_MAFBI_E;
        memcpy(record.data.mafbi_reg.reg, mafbi->reg, sizeof(mafbi->reg));
        memcpy(&record.ts, &af_work_p->ktime, sizeof(record.ts));
        sx_af_dbg_info_push(&record);
    }

    __sx_af_counters_stats_mafbi_set();
}

size_t sx_af_counters_dump_size(void)
{
    return SX_AF_COUNTERS_DUMP_SIZE;
}

static void __sx_af_counters_ktime_dump(struct seq_file *m,
                                        void            *v,
                                        void            *context,
                                        char            *prefix_str_p,
                                        ktime_t         *ktime_p,
                                        char            *suffix_str_p)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    #define TV_SEC_FMT "%lld"
    struct timespec64 ts = ktime_to_timespec64(*ktime_p);
#else
    #define TV_SEC_FMT "%ld"
    struct timespec ts = ktime_to_timespec(*ktime_p);
#endif

    seq_printf(m, "%s " TV_SEC_FMT " s, %ld ms (%ld ns) %s",
               prefix_str_p, ts.tv_sec, ts.tv_nsec / 1000000, ts.tv_nsec,
               suffix_str_p);
}

static void __sx_af_counters_dump(struct seq_file *m, void *v, void *context)
{
    u32                     index = 0;
    u32                     num_of_counters = 0;
    sxd_flow_counter_set_t *counter_p = NULL;
    ktime_t                 time_now = ktime_get_real();

    num_of_counters = g_af_counters_ctx.af_counters_num / g_af_counters_ctx.prm_cntr_lines_flow_both;

    seq_printf(m, "\tDebug info gathering         : %d\n", sx_af_counters_dbg_info_gathering);
    seq_printf(m, "\tDebug info in hex            : %d\n", sx_af_counters_dbg_info_print_in_hex);
    seq_printf(m, "\tpackets_inc_unit             : %u\n", g_af_counters_ctx.packets_inc_unit);
    seq_printf(m, "\tbytes_inc_unit               : %u\n", g_af_counters_ctx.bytes_inc_unit);
    seq_printf(m, "\tprm_cntr_lines_per_bank      : %u\n", g_af_counters_ctx.prm_cntr_lines_per_bank);
    seq_printf(m, "\tprm_cntr_banks               : %u\n", g_af_counters_ctx.prm_cntr_banks);
    seq_printf(m, "\tprm_cntr_lines_flow_both     : %u\n", g_af_counters_ctx.prm_cntr_lines_flow_both);
    seq_printf(m, "\tprm_cntr_type_flow_both      : %u\n", g_af_counters_ctx.prm_cntr_type_flow_both);
    seq_printf(m, "\tprm_cntr_start_idx_offset    : %u\n", g_af_counters_ctx.prm_cntr_start_idx_offset);
    seq_printf(m, "\tRefresh cookie               : %u\n", g_af_counters_ctx.refresh_attr.cookie);
    seq_printf(m, "\tNumber of PRM counters       : %u\n", g_af_counters_ctx.af_counters_num);
    seq_printf(m, "\tNumber of Accuflow counters  : %u\n", num_of_counters);
    __sx_af_counters_ktime_dump(m, v, context, "\tTime now                     :", &time_now, "\n");

    seq_printf(m, "\tCounters' values:\n");

    counter_p = (sxd_flow_counter_set_t *)&g_af_counters_ctx.af_counters_buffer_p[index];

    for (;
         index < num_of_counters;
         index++, counter_p++) {
        if ((counter_p->flow_counter_bytes == 0) && (counter_p->flow_counter_packets == 0)) {
            continue;
        }

        seq_printf(m, "\tcounter #%u:\t\t[ %llu bytes | %llu packets ]\n",
                   index,
                   counter_p->flow_counter_bytes,
                   counter_p->flow_counter_packets);
    }
}

int sx_af_counters_dump(struct seq_file *m, void *v, void *context)
{
    seq_printf(m, "Accumulated counters:\n");
    seq_printf(m, "\tInitialized                  : %d\n", g_af_counters_initialized);
    seq_printf(m, "\tDeinit in progress           : %d\n", g_af_deinit_in_progress);

    if (!__sx_af_counters_context_acquire()) {
        __sx_af_counters_dump(m, v, context);
        __sx_af_counters_context_release();
    }

    seq_printf(m, "\n");

    __sx_af_counters_stats_dump(m, v, context);

    seq_printf(m, "\n");

    sx_af_dbg_info_dump(m, v, context);

    return 0;
}

int sx_af_counters_proc_fs_handler(sx_af_counters_proc_fs_handler_op_e op)
{
    int err = 0;

    switch (op) {
    case SX_AF_COUNTERS_PROC_FS_HANDLER_OP_CLEAR_E:
        err = sx_af_dbg_info_clear();
        break;

    default:
        printk(KERN_NOTICE PFX "Accumulated proc fs: received unknown operation - %d\n", op);
        break;
    }

    return err;
}

static void __sx_af_counters_stats_refresh_dump(struct seq_file       *m,
                                                void                  *v,
                                                void                  *context,
                                                sx_af_refresh_stats_t *af_refresh_stats_p)
{
    seq_printf(m, "\t\tcanceled                 : %u \n", af_refresh_stats_p->canceled);
    __sx_af_counters_ktime_dump(m, v, context, "\t\tstart                    :", &af_refresh_stats_p->start, "\n");
    __sx_af_counters_ktime_dump(m, v, context, "\t\tend                      :", &af_refresh_stats_p->end, "\n");
    __sx_af_counters_ktime_dump(m, v, context, "\t\tduration                 :", &af_refresh_stats_p->duration, "\n");
    seq_printf(m, "\t\tnum_of_mafbi_traps       : %u \n", af_refresh_stats_p->num_of_mafbi_traps);
    seq_printf(m, "\t\tnum_of_mafbi_regs_drops  : %u \n", af_refresh_stats_p->num_of_mafbi_regs_drops);
    seq_printf(m, "\t\tnum_of_mafbi_regs        : %u \n", af_refresh_stats_p->num_of_mafbi_regs);
    seq_printf(m, "\t\tnum_of_mafti_traps       : %u \n", af_refresh_stats_p->num_of_mafti_traps);
    seq_printf(m, "\t\tnum_of_mafti_regs_drops  : %u \n", af_refresh_stats_p->num_of_mafti_regs_drops);
    seq_printf(m, "\t\tnum_of_mafti_regs        : %u \n", af_refresh_stats_p->num_of_mafti_regs);
}

static void __sx_af_counters_stats_reg_dump(struct seq_file   *m,
                                            void              *v,
                                            void              *context,
                                            sx_af_reg_stats_t *af_reg_stats_p)
{
    seq_printf(m, "\t\t\tmin_bytes_records.counter_index    : %u \n", af_reg_stats_p->min_bytes_records.counter_index);
    seq_printf(m, "\t\t\tmin_bytes_records.packets_inc      : %u \n", af_reg_stats_p->min_bytes_records.packets_inc);
    seq_printf(m, "\t\t\tmin_bytes_records.bytes_inc        : %u \n", af_reg_stats_p->min_bytes_records.bytes_inc);
    seq_printf(m, "\t\t\tmax_bytes_records.counter_index    : %u \n", af_reg_stats_p->max_bytes_records.counter_index);
    seq_printf(m, "\t\t\tmax_bytes_records.packets_inc      : %u \n", af_reg_stats_p->max_bytes_records.packets_inc);
    seq_printf(m, "\t\t\tmax_bytes_records.bytes_inc        : %u \n", af_reg_stats_p->max_bytes_records.bytes_inc);
    seq_printf(m, "\t\t\tmin_packets_records.counter_index  : %u \n",
               af_reg_stats_p->min_packets_records.counter_index);
    seq_printf(m, "\t\t\tmin_packets_records.packets_inc    : %u \n", af_reg_stats_p->min_packets_records.packets_inc);
    seq_printf(m, "\t\t\tmin_packets_records.bytes_inc      : %u \n", af_reg_stats_p->min_packets_records.bytes_inc);
    seq_printf(m, "\t\t\tmax_packets_records.counter_index  : %u \n",
               af_reg_stats_p->max_packets_records.counter_index);
    seq_printf(m, "\t\t\tmax_packets_records.packets_inc    : %u \n", af_reg_stats_p->max_packets_records.packets_inc);
    seq_printf(m, "\t\t\tmax_packets_records.bytes_inc      : %u \n", af_reg_stats_p->max_packets_records.bytes_inc);
}

static void __sx_af_counters_stats_dump(struct seq_file *m, void *v, void *context)
{
    seq_printf(m, "Accumulated counters' statistics:\n");
    seq_printf(m, "\tTotal number of refreshes     : %u \n", g_af_stats.refresh_all.total_refresh_cnt);
    seq_printf(m, "\tCompleted number of refreshes : %u \n", g_af_stats.refresh_all.completed_refresh_cnt);

    seq_printf(m, "\tLatest refresh:\n");
    __sx_af_counters_stats_refresh_dump(m, v, context, &g_af_stats.refresh_all.last_refresh);

    seq_printf(m, "\tShortest refresh:\n");
    __sx_af_counters_stats_refresh_dump(m, v, context, &g_af_stats.refresh_all.min_refresh);

    seq_printf(m, "\tLongest refresh:\n");
    __sx_af_counters_stats_refresh_dump(m, v, context, &g_af_stats.refresh_all.max_refresh);

    seq_printf(m, "\tEvent jobs:\n");
    __sx_af_counters_ktime_dump(m, v, context, "\t\ttimer                    :", &g_af_stats.event_jobs.timer, "\n");
    seq_printf(m, "\t\tmafti_in_1s             : %u \n", g_af_stats.event_jobs.mafti_in_1s);
    seq_printf(m, "\t\tmax_mafti_in_1s         : %u \n", g_af_stats.event_jobs.max_mafti_in_1s);
    seq_printf(m, "\t\tmafti_outside_refresh   : %u \n", g_af_stats.event_jobs.mafti_outside_refresh);
    seq_printf(m, "\t\tmafti_drops_reg_len     : %u \n", g_af_stats.event_jobs.mafti_drops_reg_len);
    seq_printf(m, "\t\tmafti_drops_counter_idx : %u \n", g_af_stats.event_jobs.mafti_drops_counter_idx);
    seq_printf(m, "\t\tmafti_drops             : %u \n", g_af_stats.event_jobs.mafti_drops);
    seq_printf(m, "\t\tmafbi_drops_reg_len     : %u \n", g_af_stats.event_jobs.mafbi_drops_reg_len);
    seq_printf(m, "\t\tmafbi_drops_rec_type    : %u \n", g_af_stats.event_jobs.mafbi_drops_rec_type);
    seq_printf(m, "\t\tmafbi_drops_counter_idx : %u \n", g_af_stats.event_jobs.mafbi_drops_counter_idx);
    seq_printf(m, "\t\tmafbi_drops             : %u \n", g_af_stats.event_jobs.mafbi_drops);
    seq_printf(m, "\t\tmafbi_drops_reg_len     : %u \n", g_af_stats.event_jobs.mafri_drops_reg_len);
    seq_printf(m, "\t\tmafri_drops_counter_idx : %u \n", g_af_stats.event_jobs.mafri_drops_counter_idx);
    seq_printf(m, "\t\tmafri_drops             : %u \n", g_af_stats.event_jobs.mafri_drops);
    seq_printf(m, "\t\tunknown_drops            : %u \n", g_af_stats.event_jobs.unknown_drops);
    seq_printf(m, "\t\tnum_of_mafri_traps       : %u \n", g_af_stats.event_jobs.num_of_mafri_traps);
    seq_printf(m, "\t\tnum_of_mafri_regs_drops  : %u \n", g_af_stats.event_jobs.num_of_mafri_regs_drops);
    seq_printf(m, "\t\tnum_of_mafri_regs        : %u \n", g_af_stats.event_jobs.num_of_mafri_regs);
    seq_printf(m, "\t\tnum_of_mafbi_traps       : %u \n", g_af_stats.event_jobs.num_of_mafbi_traps);
    seq_printf(m, "\t\tnum_of_mafbi_regs_drops  : %u \n", g_af_stats.event_jobs.num_of_mafbi_regs_drops);
    seq_printf(m, "\t\tnum_of_mafbi_regs        : %u \n", g_af_stats.event_jobs.num_of_mafbi_regs);
    seq_printf(m, "\t\tnum_of_mafti_traps       : %u \n", g_af_stats.event_jobs.num_of_mafti_traps);
    seq_printf(m, "\t\tnum_of_mafti_regs_drops  : %u \n", g_af_stats.event_jobs.num_of_mafti_regs_drops);
    seq_printf(m, "\t\tnum_of_mafti_regs        : %u \n", g_af_stats.event_jobs.num_of_mafti_regs);

    seq_printf(m, "\tUser jobs:\n");
    seq_printf(m, "\t\tdrops            : %u \n", g_af_stats.user_jobs.drops);

    seq_printf(m, "\tRegisters:\n");
    seq_printf(m, "\t\tMafti:\n");
    __sx_af_counters_stats_reg_dump(m, v, context, &g_af_stats.regs.mafti);
    seq_printf(m, "\t\tMafbi:\n");
    __sx_af_counters_stats_reg_dump(m, v, context, &g_af_stats.regs.mafbi);
}

static inline void __sx_af_counters_stats_refresh_start(void)
{
    memset(&g_af_stats.refresh_all.last_refresh,
           0,
           sizeof(g_af_stats.refresh_all.last_refresh));
    g_af_stats.refresh_all.last_refresh.start = ktime_get_real();
    g_af_stats.refresh_all.last_refresh.in_progress = 1;
}

static inline void __sx_af_counters_stats_refresh_cancel(void)
{
    g_af_stats.refresh_all.last_refresh.in_progress = 0;
    g_af_stats.refresh_all.last_refresh.canceled = 1;
}

static inline void __sx_af_counters_stats_refresh_end(void)
{
    g_af_stats.refresh_all.total_refresh_cnt++;

    g_af_stats.refresh_all.last_refresh.in_progress = 0;

    g_af_stats.refresh_all.last_refresh.end = ktime_get_real();
    g_af_stats.refresh_all.last_refresh.duration = ktime_sub(g_af_stats.refresh_all.last_refresh.end,
                                                             g_af_stats.refresh_all.last_refresh.start);

    if (g_af_stats.refresh_all.last_refresh.canceled) {
        return;
    }

    g_af_stats.refresh_all.completed_refresh_cnt++;

    if (ktime_after(g_af_stats.refresh_all.last_refresh.duration, g_af_stats.refresh_all.max_refresh.duration)) {
        memcpy(&g_af_stats.refresh_all.max_refresh,
               &g_af_stats.refresh_all.last_refresh,
               sizeof(g_af_stats.refresh_all.last_refresh));
    }

    if (ktime_before(g_af_stats.refresh_all.last_refresh.duration, g_af_stats.refresh_all.min_refresh.duration)) {
        memcpy(&g_af_stats.refresh_all.min_refresh,
               &g_af_stats.refresh_all.last_refresh,
               sizeof(g_af_stats.refresh_all.last_refresh));
    }
}

static inline void __sx_af_counters_stats_event_jobs_drop_set(struct completion_info *comp_info_p)
{
    if (comp_info_p->hw_synd == SXD_TRAP_ID_ACCU_FLOW_INC) {
        g_af_stats.event_jobs.mafti_drops++;
    } else if (comp_info_p->hw_synd == SXD_TRAP_ID_MAFBI) {
        g_af_stats.event_jobs.mafbi_drops++;
    } else if (comp_info_p->hw_synd == SXD_TRAP_ID_MAFRI) {
        g_af_stats.event_jobs.mafri_drops++;
    } else {
        g_af_stats.event_jobs.unknown_drops++;
    }
}

static inline void __sx_af_counters_stats_mafti_perf_set(ktime_t *ktime_p)
{
    g_af_stats.event_jobs.mafti_in_1s++;

    if (ktime_ms_delta(*ktime_p, g_af_stats.event_jobs.timer) >= 1000) {
        if (g_af_stats.event_jobs.mafti_in_1s > g_af_stats.event_jobs.max_mafti_in_1s) {
            g_af_stats.event_jobs.max_mafti_in_1s = g_af_stats.event_jobs.mafti_in_1s;
        }
        g_af_stats.event_jobs.timer = *ktime_p;
        g_af_stats.event_jobs.mafti_in_1s = 0;
    }
}

static inline void __sx_af_counters_stats_event_jobs_set(struct completion_info *comp_info_p)
{
    if (comp_info_p->hw_synd == SXD_TRAP_ID_ACCU_FLOW_INC) {
        if (g_af_stats.refresh_all.last_refresh.in_progress) {
            g_af_stats.refresh_all.last_refresh.num_of_mafti_traps++;
        } else {
            g_af_stats.event_jobs.mafti_outside_refresh++;
        }
        g_af_stats.event_jobs.num_of_mafti_traps++;
    } else if (comp_info_p->hw_synd == SXD_TRAP_ID_MAFBI) {
        g_af_stats.refresh_all.last_refresh.num_of_mafbi_traps++;
        g_af_stats.event_jobs.num_of_mafbi_traps++;
    } else if (comp_info_p->hw_synd == SXD_TRAP_ID_MAFRI) {
        g_af_stats.event_jobs.num_of_mafri_traps++;
    }
}

static inline void __sx_af_counters_stats_mafti_set(void)
{
    g_af_stats.refresh_all.last_refresh.num_of_mafti_regs++;
    g_af_stats.event_jobs.num_of_mafti_regs++;
}

static inline void __sx_af_counters_stats_mafri_set(void)
{
    g_af_stats.event_jobs.num_of_mafri_regs++;
}

static inline void __sx_af_counters_stats_mafbi_set(void)
{
    g_af_stats.refresh_all.last_refresh.num_of_mafbi_regs++;
    g_af_stats.event_jobs.num_of_mafbi_regs++;
}

static inline void __sx_af_counters_stats_mafti_drop_set(void)
{
    g_af_stats.refresh_all.last_refresh.num_of_mafti_regs_drops++;
    g_af_stats.event_jobs.num_of_mafti_regs_drops++;
}

static inline void __sx_af_counters_stats_mafri_drop_set(void)
{
    g_af_stats.event_jobs.num_of_mafri_regs_drops++;
}

static inline void __sx_af_counters_stats_mafbi_drop_set(void)
{
    g_af_stats.refresh_all.last_refresh.num_of_mafbi_regs_drops++;
    g_af_stats.event_jobs.num_of_mafbi_regs_drops++;
}
