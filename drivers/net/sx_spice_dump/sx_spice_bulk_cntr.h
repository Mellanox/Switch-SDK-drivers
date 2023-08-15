/*
 * Copyright © 2010-2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */
#ifndef __SPICE_BULK_CNTR_DB_H__
#define __SPICE_BULK_CNTR_DB_H__

#include <linux/netdevice.h>
#include <linux/string.h>
#include <linux/mlx_sx/skb_hook.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/completion.h>
#include <linux/ktime.h>
#include <linux/jiffies.h>

/************************************************
 *  Type definitions
 ***********************************************/
/*#define SPICE_BULK_CNTR_LOG_EN*/
/*#define SPICE_BULK_CNTR_STATISTICS_LOG_EN*/
#define SPICE_BULK_COUNTERS_GENERATE_ENUM(ENUM, STR)   ENUM,
#define SPICE_BULK_COUNTERS_GENERATE_STRING(ENUM, STR) STR,

#define SPICE_BULK_CNTR_MOPCE_MIN_LBUFF 10000 /*bytes*/

#define FOREACH_SPICE_BULK_COUNTER_TYPEMASK(F)                                                                       \
    F(SPICE_BULK_CNTR_TYPE_PORT_MASK_E = 0x1 << SXD_BULK_CNTR_KEY_TYPE_PORT_E, "Port_counters")                      \
    F(SPICE_BULK_CNTR_TYPE_FLOW_MASK_E = 0x1 << SXD_BULK_CNTR_KEY_TYPE_FLOW_E, "Flow_counters")                      \
    F(SPICE_BULK_CNTR_TYPE_SHARED_BUFFER_MASK_E = 0x1 << SXD_BULK_CNTR_KEY_TYPE_SHARED_BUFFER_E,                     \
        "Shared_buffer_counters")                                                                                    \
    F(SPICE_BULK_CNTR_TYPE_HEADROOM_MASK_E = 0x1 << SXD_BULK_CNTR_KEY_TYPE_HEADROOM_E, "Headroom_counters")          \
    F(SPICE_BULK_CNTR_TYPE_ELEPHANT_MASK_E = 0x1 << SXD_BULK_CNTR_KEY_TYPE_ELEPHANT_E, "Elephant_counters")          \
    F(SPICE_BULK_CNTR_TYPE_STATEFUL_DB_MASK_E = 0x1 << SXD_BULK_CNTR_KEY_TYPE_STATEFUL_DB_E, "Stateful_DB_counters") \
    F(SPICE_BULK_CNTR_TYPE_ACCUFLOW_MASK_E = 0x1 << SXD_BULK_CNTR_KEY_TYPE_ACCUFLOW_E, "Accuflow_counters")          \
    F(SPICE_BULK_CNTR_TYPE_ISSU_MASK_E = 0x1 << SXD_BULK_CNTR_KEY_TYPE_ISSU_E, "N/A")                                \
    F(SPICE_BULK_CNTR_TYPE_PERFORMANCE_MASK_E = 0x1 << SXD_BULK_CNTR_KEY_TYPE_PERFORMANCE_E, "Performance_counters")


#define SPICE_SUPPORTED_BULK_CNTR_TRAP_MASK \
    (SPICE_BULK_CNTR_TYPE_PERFORMANCE_MASK_E)

#define FOREACH_SPICE_BULK_COUNTER_STATE(F)                                                \
    F(SPICE_BULK_COUNTER_IDLE_STATE_E = 0,                        "IDLE")                  \
    F(SPICE_BULK_COUNTER_INITIALIZED_STATE_E,                     "INITIALIZED")           \
    F(SPICE_BULK_COUNTER_CANCEL_IN_PROGRESS_STATE_E,              "CANCEL_IN_PROGRESS")    \
    F(SPICE_BULK_COUNTER_STATE_MAX_E = SPICE_BULK_COUNTER_CANCEL_IN_PROGRESS_STATE_E,  "") \
    F(SPICE_BULK_COUNTER_STATE_NUM_E = SPICE_BULK_COUNTER_STATE_MAX_E + 1,    "")

#define FOREACH_SPICE_BULK_COUNTER_OP(F)                                            \
    F(SPICE_BULK_COUNTER_INIT_OP_E = 0,                                "INIT")      \
    F(SPICE_BULK_COUNTER_DEINIT_OP_E,                                  "DEINIT")    \
    F(SPICE_BULK_COUNTER_READ_OP_E,                                    "READ")      \
    F(SPICE_BULK_COUNTER_CANCEL_OP_E,                                  "CANCEL")    \
    F(SPICE_BULK_COUNTER_TRAP_DONE_OP_E,                               "TRAP_DONE") \
    F(SPICE_BULK_COUNTER_OP_MAX_E = SPICE_BULK_COUNTER_TRAP_DONE_OP_E, "")          \
    F(SPICE_BULK_COUNTER_OP_NUM_E = SPICE_BULK_COUNTER_OP_MAX_E + 1,   "")

#define FOREACH_SPICE_BULK_COUNTER_TRANSACTION(F)                                             \
    F(SPICE_BULK_COUNTER_TR_INVALID_E = 0,                             "TRANSACTION_INVALID") \
    F(SPICE_BULK_COUNTER_TR_NEW_E,                                     "TRANSACTION_NEW")     \
    F(SPICE_BULK_COUNTER_TR_ONGOING_E,                                 "TRANSACTION_ONGOING") \
    F(SPICE_BULK_COUNTER_TR_BUSY_E,                                    "TRANSACTION_BUSY")    \
    F(SPICE_BULK_COUNTER_TR_ERROR_E,                                   "TRANSACTION_ERROR")   \
    F(SPICE_BULK_COUNTER_TR_MAX_STAT_E = SPICE_BULK_COUNTER_TR_ERROR_E,          "")          \
    F(SPICE_BULK_COUNTER_TR_STAT_NUM_E = SPICE_BULK_COUNTER_TR_MAX_STAT_E + 1,   "")


#define FOREACH_SPICE_BULK_COUNTER_TR_PROGRESS_STATE(F)               \
    F(SPICE_BULK_COUNTER_TR_IDLE_E = 0,                           "") \
    F(SPICE_BULK_COUNTER_TR_PENDING_MOCS_DONE,                    "") \
    F(SPICE_BULK_COUNTER_TR_MOCS_DONE_E,                          "") \

typedef enum spice_bulk_cntr_state {
    FOREACH_SPICE_BULK_COUNTER_STATE(SPICE_BULK_COUNTERS_GENERATE_ENUM)
} spice_bulk_cntr_state_e;

typedef enum spice_bulk_cntr_params_op {
    FOREACH_SPICE_BULK_COUNTER_OP(SPICE_BULK_COUNTERS_GENERATE_ENUM)
} spice_bulk_cntr_params_op_e;

typedef enum spice_bulk_cntr_mask {
    FOREACH_SPICE_BULK_COUNTER_TYPEMASK(SPICE_BULK_COUNTERS_GENERATE_ENUM)
} spice_bulk_cntr_mask_e;

typedef enum spice_bulk_cntr_req_status {
    FOREACH_SPICE_BULK_COUNTER_TRANSACTION(SPICE_BULK_COUNTERS_GENERATE_ENUM)
} spice_bulk_cntr_req_status_e;

typedef enum spice_bulk_cntr_tr_progress {
    FOREACH_SPICE_BULK_COUNTER_TR_PROGRESS_STATE(SPICE_BULK_COUNTERS_GENERATE_ENUM)
} spice_bulk_cntr_tr_progress_e;
/************************************************
 * Type declarations
 ***********************************************/

typedef struct spice_bulk_cntr_event_data_read {
    char   *buf;
    size_t  lbuf;
    loff_t *ppos;
} spice_bulk_cntr_event_data_read_t;

typedef struct spice_bulk_cntr_event_data_completion {
    uint16_t        hw_synd;
    struct sk_buff *skb;
} spice_bulk_cntr_event_data_completion_t;

typedef union spice_bulk_cntr_event_data {
    spice_bulk_cntr_event_data_read_t       read_data;
    spice_bulk_cntr_event_data_completion_t completion_data;
} spice_bulk_cntr_event_data_u;

typedef union spice_bulk_cntr_ku_reg {
    struct ku_mopce_reg mopce_reg;
} spice_bulk_cntr_ku_reg_u;

typedef struct reg_tlv_node {
    const void      *reg_tlv_p;
    struct list_head reg_tlv_node;
    bool             is_decoded;
} reg_tlv_node_t;

typedef struct skb_node {
    struct sk_buff  *skb;
    bool             mocs_done_ind;
    struct list_head reg_tlv_queue;
    struct list_head skb_node;
} skb_node_t;

typedef struct spice_bulk_cntr_stats {
    uint8_t num_of_received_traps;
    uint8_t num_of_dropped_traps;
    uint8_t num_of_parsed_traps;
    uint8_t num_of_parsed_reg_tlv;
    ktime_t consumer_start_time;      /*copy to user buffer starts*/
    ktime_t consumer_end_time;        /*copy to user buffer ends*/
    ktime_t producer_start_time;      /*mocs request is sent to fw*/
    ktime_t producer_end_time;        /*last trap is parsed and queued*/
} spice_bulk_cntr_stats_t;

typedef struct spice_bulk_cntr_tr_ctx {
    char                         *kbuf;
    size_t                        kbuf_alloc_size;
    size_t                        kbuf_current_size;
    sxd_bulk_cntr_event_id_t      ev_id;
    spice_bulk_cntr_state_e       state;
    spice_bulk_cntr_stats_t       stats;
    spice_bulk_cntr_ku_reg_u      reg_data;
    struct completion            *skb_queue_not_empty_p;
    struct completion            *cancel_completion_p;
    struct list_head              skb_queue;
    spice_bulk_cntr_tr_progress_e tr_progress_state;
    bool                          is_skb_inproc;
    bool                          is_mocs_done;
} spice_bulk_cntr_tr_ctx_t;

typedef struct spice_bulk_cntr_file_db {
    spice_bulk_cntr_tr_ctx_t tr_ctx;
    spinlock_t               tr_ctx_lock;
    struct mutex             tr_file_op_mutex;
} spice_bulk_cntr_file_db_t;

typedef struct spice_bulk_cntr_file_params {
    struct sx_dev                *dev;
    enum sxd_bulk_cntr_key_type_e key_type;
    spice_bulk_cntr_file_db_t     file_db;
    struct list_head              list_file_params;
} spice_bulk_cntr_file_params_t;

typedef struct spice_bulk_cntr_event_params {
    struct sx_dev                *dev;
    enum sxd_bulk_cntr_key_type_e key_type;
    spice_bulk_cntr_params_op_e   op;
    spice_bulk_cntr_event_data_u  data;
    void                         *context;
} spice_bulk_cntr_event_params_t;


/************************************************
 *  Global variables
 ***********************************************/
extern bool spice_bulk_cntr_is_issu;
/************************************************
* Global Functions                             *
************************************************/
/**
 * handle dealloc of created counter files.
 **/
void sx_spice_access_reg_bulk_counters_list_free(dev_private_data_t *dev_data);
/**
 * handle trap_id registration to sx_core.
 *
 * Supported devices:       Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] enum ku_ctrl_cmd cmd     -  CTRL_CMD_ADD_SYND / CTRL_CMD_REMOVE_SYND.
 * @param[in] struct sx_dev   *dev     -  device struct.
 * @param[in] sxd_trap_id_t    trap_id -  trap syndrom id.
 * @param[in] void            *context
 *
 * @return 0             -  operation completed successfully.
 * @return -EINVAL       -  invalid argument.
 * @return -ENODEV       -  invalid argument.
 **/
int sx_spice_bulk_cntr_listener_set(enum ku_ctrl_cmd cmd,
                                    struct sx_dev   *dev,
                                    sxd_trap_id_t    trap_id,
                                    void            *context);
/**
 * Debugfs file creation wrapper.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] *parent    -  ptr to repo/file root in the hierarchy in which the file is created.
 * @param[in] *dev_data  -  ptr to file private data.
 *
 * @return 0             -  operation completed successfully.
 * @return -ENOMEM       -  out of memory.
 * @return -ENODEV       -  no such device.
 * @return -EINVAL       -  invalid argument.
 **/
int sx_spice_access_reg_bulk_counters_file_create(struct dentry *parent, dev_private_data_t *dev_data);

/**
 * Debugfs file operation .release call back api.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] *inode    - ptr to user file inode descriptor.
 * @param[in] *filp     - ptr to user file descriptor.
 *
 * @return 0             -  operation completed successfully.
 * @return -ENOMEM       -  out of memory.
 * @return -ENODEV       -  no such device.
 * @return -EINVAL       -  invalid argument.
 **/
int sx_spice_bulk_counters_release_cb(struct inode *inode, struct file *filp);

/**
 * Debugfs file operation .read call back api.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] *filp     -  ptr to user file descriptor.
 * @param[in] *buf       -  ptr to user space buffer.
 * @param[in]  lbuf      -  size of user space buffer.
 * @param[in] *ppos      -  ptr to  user buffer offset indication.
 *
 * @return 0             -  operation completed successfully.
 * @return -ENOMEM       -  out of memory.
 * @return -ENODEV       -  no such device.
 * @return -EINVAL       -  invalid argument.
 **/
ssize_t sx_spice_bulk_counters_read_cb(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);

/**
 * Event handle api for spice bulk_cntr sub module.
 *
 * Supported devices:       Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] params_p   -  spice_bulk_cntr distribution params.
 *
 * @return 0             -  operation completed successfully.
 * @return -EINVAL       -  invalid argument.
 **/
ssize_t sx_spice_bulk_cntr_event(spice_bulk_cntr_event_params_t *params_p);

#endif /* __SPICE_BULK_CNTR_DB_H__ */
