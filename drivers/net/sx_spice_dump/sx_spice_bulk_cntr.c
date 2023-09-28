/*
 * Copyright (C) 2010-2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/cmd.h>
#include  <linux/debugfs.h>
#include "sx_spice_wrapper.h"
#include "sx_spice_access_reg_auto.h"
#include "sx_spice_bulk_cntr.h"

/************************************************
 * Type definitions                             *
 ***********************************************/
#define MAX_ALLOC_KBUF_SIZE 150000 /*bytes*/
#define WAIT_TIME_OUT       5000  /*5 sec*/
#define SPICE_EMAD_HDR_TO_TID(skb)                       \
    (be64_to_cpu(((struct emad_operation*)((skb)->data + \
                                           sizeof(struct sx_eth_hdr)))->tid))
/************************************************
* Static Functions declaration                  *
************************************************/

/***********************************************/
/****************Inline helpers*****************/
/***********************************************/
static inline void __sx_spice_bulk_cntr_state_set(spice_bulk_cntr_file_db_t *file_db,
                                                  spice_bulk_cntr_state_e    state);
static inline void __sx_spice_bulk_cntr_state_get(spice_bulk_cntr_file_db_t *file_db,
                                                  spice_bulk_cntr_state_e   *state);
static inline void __sx_spice_bulk_cntr_generate_event_id(pid_t                         client_pid,
                                                          enum sxd_bulk_cntr_key_type_e key_type,
                                                          sxd_bulk_cntr_event_id_t     *ev_id);
static inline void __sx_spice_bulk_cntr_cap_kbuffer_size(spice_bulk_cntr_file_db_t *file_db, size_t lbuf,
                                                         loff_t *ppos, size_t *kbuf_size);
static inline void __sx_spice_bulk_cntr_ctx_finalize(enum sxd_bulk_cntr_key_type_e key_type,
                                                     spice_bulk_cntr_file_db_t    *file_db);
#ifdef SPICE_BULK_CNTR_STATISTICS_LOG_EN
static inline void __sx_spice_bulk_cntr_print_stats(spice_bulk_cntr_file_db_t *file_db);
#endif
static inline int __sx_spice_bulk_cntr_get_trap_id(enum sxd_bulk_cntr_key_type_e key_type, sxd_trap_id_t *trap_id);
static inline int __sx_spice_bulk_cntr_get_mocs_type_id(enum sxd_bulk_cntr_key_type_e key_type,
                                                        sxd_mocs_type_t              *mocs_type_id_p);
static inline int __sx_spice_bulk_cntr_verify_lbuf(enum sxd_bulk_cntr_key_type_e key_type, size_t lbuf);
static inline spice_bulk_cntr_file_db_t * __sx_spice_bulk_cntr_file_db_get(sxd_bulk_cntr_event_id_t ev_id,
                                                                           void                    *context);
/***********************************************/
/******************Operational******************/
/***********************************************/
static void __sx_spice_bulk_cntr_handle_completion_event(struct completion_info *comp_info, void *context);
static int __sx_spice_bulk_cntr_init_mocs(struct sx_dev                  *dev,
                                          struct ku_mocs_reg             *reg_data,
                                          const sxd_bulk_cntr_event_id_t *ev_id,
                                          uint8_t                         clear,
                                          uint8_t                         opcode,
                                          enum sxd_bulk_cntr_key_type_e   key_type);
static int __reg_tlv_decode(enum sxd_bulk_cntr_key_type_e key_type,
                            const void                   *reg_tlv,
                            spice_bulk_cntr_ku_reg_u     *reg_data);
static void __reg_tlv_enqueue(const void                                *reg_tlv,
                              uint32_t                                   reg_len,
                              struct sxd_bulk_cntr_buffer_layout_common *layout_common __attribute__((unused)),
                              void                                      *context);

static int __spice_bulk_cntr_reg_data_to_buffer_print(enum sxd_bulk_cntr_key_type_e key_type,
                                                      char                          buffer[],
                                                      size_t                        buffer_length,
                                                      spice_bulk_cntr_ku_reg_u     *reg_data);
static int __sx_spice_bulk_cntr_alloc_kbuf(spice_bulk_cntr_file_db_t *file_db,
                                           size_t lbuf, char **kbuf,
                                           size_t *kbuf_alloc_size, size_t *kbuf_current_size);
static int __sx_spice_bulk_cntr_tr_status_get(spice_bulk_cntr_file_db_t    *file_db,
                                              enum sxd_bulk_cntr_key_type_e key_type,
                                              char                         *requested_buf,
                                              loff_t                       *requested_ppos,
                                              spice_bulk_cntr_req_status_e *req_status);
static int __sx_spice_bulk_cntr_tr_set(spice_bulk_cntr_event_params_t *params_p);

static ssize_t __sx_spice_bulk_cntr_tr_ongoing(spice_bulk_cntr_event_params_t *params_p);

/***********************************************/
/***********file operation handlers*************/
/***********************************************/
static int __sx_spice_bulk_cntr_file_init(spice_bulk_cntr_event_params_t *params_p);
static int __sx_spice_bulk_cntr_file_tr_start_on_idle(spice_bulk_cntr_event_params_t *params_p);
static int __sx_spice_bulk_cntr_file_deinit(spice_bulk_cntr_event_params_t *params_p);
static int __sx_spice_bulk_cntr_file_tr_start(spice_bulk_cntr_event_params_t *params_p);
static int __sx_spice_bulk_cntr_file_tr_cancel(spice_bulk_cntr_event_params_t *params_p);
static int __sx_spice_bulk_cntr_file_trap_done(spice_bulk_cntr_event_params_t *params_p);
static int __sx_spice_bulk_cntr_file_trap_done_on_cancel(spice_bulk_cntr_event_params_t *params);

/************************************************
 *  Local variables
 ***********************************************/
static const char * const spice_bulk_cntr_state_e_str_s[] = {
    FOREACH_SPICE_BULK_COUNTER_STATE(SPICE_BULK_COUNTERS_GENERATE_STRING)
};

static const struct file_operations spice_bulk_cntr_fops = {
    .read = sx_spice_bulk_counters_read_cb,
    .release = sx_spice_bulk_counters_release_cb
};

static const char * const spice_bulk_cntr_op_e_str_s[] = {
    FOREACH_SPICE_BULK_COUNTER_OP(SPICE_BULK_COUNTERS_GENERATE_STRING)
};

static const char * const spice_bulk_cntr_mask_e_str_s[] = {
    FOREACH_SPICE_BULK_COUNTER_TYPEMASK(SPICE_BULK_COUNTERS_GENERATE_STRING)
};

static const char * const spice_bulk_cntr_transaction_e_str_s[] = {
    FOREACH_SPICE_BULK_COUNTER_TRANSACTION(SPICE_BULK_COUNTERS_GENERATE_STRING)
};

/************************************************
 * Global variables                             *
 ***********************************************/
bool spice_bulk_cntr_is_issu = false;

/************************************************
 * Static Functions definition                  *
 ***********************************************/

#ifdef SPICE_BULK_CNTR_LOG_EN
static const char * __sx_spice_bulk_cntr_state_e_str(spice_bulk_cntr_state_e state)
{
    return (state < SPICE_BULK_COUNTER_STATE_NUM_E) ? spice_bulk_cntr_state_e_str_s[state] : "Unknown";
}

static const char * __sx_spice_bulk_cntr_op_e_str(spice_bulk_cntr_params_op_e op)
{
    return (op < SPICE_BULK_COUNTER_OP_NUM_E) ? spice_bulk_cntr_op_e_str_s[op] : "Unknown";
}

static const char * __sx_spice_bulk_cntr_transaction_e_str(spice_bulk_cntr_req_status_e status)
{
    return (status < SPICE_BULK_COUNTER_TR_STAT_NUM_E) ? spice_bulk_cntr_transaction_e_str_s[status] : "Unknown";
}
#endif

static const char * __sx_spice_bulk_cntr_type_mask_e_str(enum sxd_bulk_cntr_key_type_e key_type)
{
    return (key_type < SXD_BULK_CNTR_KEY_TYPE_LAST_E) ? spice_bulk_cntr_mask_e_str_s[key_type] : "Unknown";
}

static inline void __sx_spice_bulk_cntr_state_set(spice_bulk_cntr_file_db_t *file_db, spice_bulk_cntr_state_e state)
{
#ifdef SPICE_BULK_CNTR_LOG_EN
    printk(KERN_INFO "%s: current state: %s new state: %s", __func__,
           __sx_spice_bulk_cntr_state_e_str(file_db->tr_ctx.state),
           __sx_spice_bulk_cntr_state_e_str(state));
#endif
    file_db->tr_ctx.state = state;
}

static inline void __sx_spice_bulk_cntr_state_get(spice_bulk_cntr_file_db_t *file_db, spice_bulk_cntr_state_e   *state)
{
    *state = file_db->tr_ctx.state;
}

static inline void __sx_spice_bulk_cntr_generate_event_id(pid_t                         client_pid,
                                                          enum sxd_bulk_cntr_key_type_e key_type,
                                                          sxd_bulk_cntr_event_id_t     *ev_id)
{
    static uint64_t event_id = 0;

    event_id++;
    ev_id->event_id_fields.client_id = client_pid;
    ev_id->event_id_fields.type = key_type;
    ev_id->event_id_fields.id = event_id;
}

static inline void __sx_spice_bulk_cntr_cap_kbuffer_size(spice_bulk_cntr_file_db_t *file_db,
                                                         size_t                     lbuf,
                                                         loff_t                    *ppos,
                                                         size_t                    *kbuf_size)
{
    /* during fragmented transaction .read call backs the user may change the allocated buffer size
     * to different size than initially allocated on the first iteration. if the copy is ongoing, we dont want
     * to linger on memory realloc - thus we can either use the initially allocated size in case lbuf > kbuf_alloc_size
     * or cap the current buffer size otherwise.
     */
    if (*ppos) {
        *kbuf_size = (lbuf >= file_db->tr_ctx.kbuf_alloc_size) ? file_db->tr_ctx.kbuf_alloc_size : lbuf;
        file_db->tr_ctx.kbuf_current_size = *kbuf_size;
    } else {
        *kbuf_size = file_db->tr_ctx.kbuf_current_size;
    }
}

static inline void __sx_spice_bulk_cntr_ctx_finalize(enum sxd_bulk_cntr_key_type_e key_type,
                                                     spice_bulk_cntr_file_db_t    *file_db)
{
    skb_node_t     *iter_skb, *tmp_skb;
    reg_tlv_node_t *iter_reg, *tmp_reg;

    /*unregister bulk_cntr sx_core*/
    bulk_cntr_db_mocs_session_release(key_type);

    /*init transaction specific in db*/
    file_db->tr_ctx.tr_progress_state = SPICE_BULK_COUNTER_TR_IDLE_E;
    file_db->tr_ctx.ev_id.event_id_value = 0;
    file_db->tr_ctx.is_mocs_done = false;
    file_db->tr_ctx.is_skb_inproc = 0;
    memset(&file_db->tr_ctx.stats, 0, sizeof(spice_bulk_cntr_stats_t));

    /*release skb reference and free list if not empty*/

    list_for_each_entry_safe(iter_skb, tmp_skb, &file_db->tr_ctx.skb_queue, skb_node) {
        /* free all reg_tlv that are enqueued to skb_node*/
        list_for_each_entry_safe(iter_reg, tmp_reg, &iter_skb->reg_tlv_queue, reg_tlv_node) {
            list_del(&iter_reg->reg_tlv_node);
            kfree(iter_reg);
        }
        /*continue to release reference and free skb*/
        sx_skb_consume(iter_skb->skb);
        list_del(&iter_skb->skb_node);
        kfree(iter_skb);
    }

    /*free completion*/
    if (file_db->tr_ctx.skb_queue_not_empty_p) {
        kfree(file_db->tr_ctx.skb_queue_not_empty_p);
        file_db->tr_ctx.skb_queue_not_empty_p = NULL;
    }
}

#ifdef SPICE_BULK_CNTR_STATISTICS_LOG_EN
static inline void __sx_spice_bulk_cntr_print_stats(spice_bulk_cntr_file_db_t *file_db)
{
    /*mark time stamp for copy end*/
    file_db->tr_ctx.stats.consumer_end_time = ktime_get_real();
    printk(KERN_INFO " %s: !!!!!!!!!!!!!!!!!!Transaction Done!!!!!!!!!!!!!!!!!!!\n", __func__);
    printk(KERN_INFO " %s: Producer round trip:        %llu [mocs request : mocs done]\n", __func__,
           ktime_sub(file_db->tr_ctx.stats.producer_end_time, file_db->tr_ctx.stats.producer_start_time));
    printk(KERN_INFO " %s: Consumer round trip:        %llu [copy start : copy end]\n", __func__,
           ktime_sub(file_db->tr_ctx.stats.consumer_end_time, file_db->tr_ctx.stats.consumer_start_time));
    printk(KERN_INFO " %s: Producer consumer overlap:  %llu [copy start : mocs done]\n", __func__,
           ktime_sub(file_db->tr_ctx.stats.producer_end_time, file_db->tr_ctx.stats.consumer_start_time));
    printk(KERN_INFO " %s: Transaction round trip:     %llu [mocs request : copy end]\n\n", __func__,
           ktime_sub(file_db->tr_ctx.stats.consumer_end_time, file_db->tr_ctx.stats.producer_start_time));

    printk(KERN_INFO " %s: Number of received traps:   %d\n", __func__, file_db->tr_ctx.stats.num_of_received_traps);
    printk(KERN_INFO " %s: Number of dropped traps:    %d\n", __func__, file_db->tr_ctx.stats.num_of_dropped_traps);
    printk(KERN_INFO " %s: Number of parsed traps:     %d\n", __func__, file_db->tr_ctx.stats.num_of_parsed_traps);
    printk(KERN_INFO " %s: Number of parsed reg_tlv's: %d\n", __func__, file_db->tr_ctx.stats.num_of_parsed_reg_tlv);
}
#endif

static inline int __sx_spice_bulk_cntr_get_trap_id(enum sxd_bulk_cntr_key_type_e key_type, sxd_trap_id_t *trap_id_p)
{
    int err = 0;

    switch (key_type) {
    case SXD_BULK_CNTR_KEY_TYPE_PERFORMANCE_E:
        *trap_id_p = SXD_TRAP_ID_MOPCE;
        break;

    default:
        err = -EINVAL;
        printk(KERN_ERR "%s: invalid argument for key_type_e %d err: %d", __func__,
               key_type, err);
        break;
    }
    return err;
}

static inline int __sx_spice_bulk_cntr_get_mocs_type_id(enum sxd_bulk_cntr_key_type_e key_type,
                                                        sxd_mocs_type_t              *mocs_type_id_p)
{
    int err = 0;

    switch (key_type) {
    case SXD_BULK_CNTR_KEY_TYPE_PERFORMANCE_E:
        *mocs_type_id_p = SXD_MOCS_TYPE_MOPCE_E;
        break;

    default:
        err = -EINVAL;
        printk(KERN_ERR "%s: invalid argument for key_type_e %d err: %d", __func__,
               key_type, err);
        break;
    }
    return err;
}

static inline int __sx_spice_bulk_cntr_verify_lbuf(enum sxd_bulk_cntr_key_type_e key_type, size_t lbuf)
{
    int    err = 0;
    size_t min_size = 0;

    switch (key_type) {
    case SXD_BULK_CNTR_KEY_TYPE_PERFORMANCE_E:
        min_size = SPICE_BULK_CNTR_MOPCE_MIN_LBUFF;
        break;

    default:
        err = -EINVAL;
        printk(KERN_ERR "%s: invalid argument for key_type_e %d err: %d", __func__,
               key_type, err);
        break;
    }

    if (lbuf < min_size) {
        err = -EPERM;
        printk(KERN_INFO "%s: Read operation not permitted insufficient buffer size lbuf: %zu"
               " reallocate with minimal size of :%zu bytes\n", __func__, lbuf, min_size);
    }

    return err;
}

static inline spice_bulk_cntr_file_db_t * __sx_spice_bulk_cntr_file_db_get(sxd_bulk_cntr_event_id_t ev_id,
                                                                           void                    *context)
{
    struct list_head              *dev_files_list = (struct list_head *)context;
    spice_bulk_cntr_file_params_t *iter;
    spice_bulk_cntr_file_db_t    * ret = NULL;

    list_for_each_entry(iter, dev_files_list, list_file_params) {
        if (iter->key_type == ev_id.event_id_fields.type) {
            ret = &iter->file_db;
            break;
        }
    }

    return ret;
}

static void __sx_spice_bulk_cntr_handle_completion_event(struct completion_info *comp_info, void *context)
{
    struct sk_buff                *skb = comp_info->skb;
    uint16_t                       hw_synd = comp_info->hw_synd;
    spice_bulk_cntr_event_params_t params;
    uint64_t                       emad_tid;
    spice_bulk_cntr_file_db_t     *file_db = NULL;


    /*drop at this stage if not spice transaction*/
    emad_tid = SPICE_EMAD_HDR_TO_TID(comp_info->skb);
    if (!emad_tid) {
        printk(KERN_ERR "%s: syndrom: 0x%x invalid event_id", __func__, hw_synd);
        goto out;
    }
    /*in case the spice_bulk cntr is listening for mocs done in parallel
     * to other module we'll receive their mocs done as well.
     * in such case we either drop the trap in the file_db search (no common counter type registered)
     * or either in the event_id comparison*/
    if (hw_synd == SXD_TRAP_ID_MOCS_DONE) {
        file_db = __sx_spice_bulk_cntr_file_db_get((sxd_bulk_cntr_event_id_t)emad_tid, context);
        if (!file_db) {
            printk(KERN_ERR "%s: syndrom: 0x%x unable to match file_db", __func__, hw_synd);
            goto out;
        }
    } else {
        file_db = (spice_bulk_cntr_file_db_t *)context;
    }

    /*update trap received stat*/
    file_db->tr_ctx.stats.num_of_received_traps++;

    if (emad_tid != file_db->tr_ctx.ev_id.event_id_value) {
        /* emad_tid and event_id should be equal for all mocs traps */
        printk(KERN_ERR "%s: syndrom: 0x%x unable to match event_id from db emad_tid=%llu, event_tid=%llu "
               "file_db ptr: [%p] dropping skb\n", __func__,
               hw_synd, emad_tid, file_db->tr_ctx.ev_id.event_id_value, file_db);
        file_db->tr_ctx.stats.num_of_dropped_traps++;
        goto out;
    }
#ifdef SPICE_BULK_CNTR_LOG_EN
    printk(KERN_INFO "%s: syndrom: 0x%x trapped successfully: emad_tid=%llu, event_tid=%llu\n", __func__,
           hw_synd, emad_tid, file_db->tr_ctx.ev_id.event_id_value);
#endif

    /*fill event params*/
    params.dev = comp_info->dev;
    params.key_type = file_db->tr_ctx.ev_id.event_id_fields.type;
    params.op = SPICE_BULK_COUNTER_TRAP_DONE_OP_E;
    params.data.completion_data.skb = skb;
    params.data.completion_data.hw_synd = hw_synd;
    params.context = (void *)file_db;

    /*trigger internal event*/
    sx_spice_bulk_cntr_event(&params);

out:
    return;
}

static int __sx_spice_bulk_cntr_init_mocs(struct sx_dev                  *dev,
                                          struct ku_mocs_reg             *reg_data,
                                          const sxd_bulk_cntr_event_id_t *ev_id,
                                          uint8_t                         clear,
                                          uint8_t                         opcode,
                                          enum sxd_bulk_cntr_key_type_e   key_type)
{
    int err = 0;

    if (ev_id) {
        reg_data->event_tid = ev_id->event_id_value;
    } else { /* in 'cancel' operation */
        reg_data->event_tid = 0;
    }

    reg_data->clear = clear;
    reg_data->opcode = opcode;

    err = __sx_spice_bulk_cntr_get_mocs_type_id(key_type, &reg_data->type);
    if (err) {
        printk(KERN_ERR "%s: invalid argument for key_type_e %d err: %d", __func__,
               key_type, err);
        goto out;
    }

out:
    return err;
}

static int __reg_tlv_decode(enum sxd_bulk_cntr_key_type_e key_type,
                            const void                   *reg_tlv,
                            spice_bulk_cntr_ku_reg_u     *reg_data)
{
    int err = 0;

    switch (key_type) {
    case SXD_BULK_CNTR_KEY_TYPE_PERFORMANCE_E:
        err = __MOPCE_decode((u8*)reg_tlv, &reg_data->mopce_reg, NULL);
        if (err) {
            err = -EFAULT;
            printk(KERN_ERR "%s: failed to decode MOPCE reg_tlv", __func__);
            goto out;
        }
        break;

    default:
        err = -EINVAL;
        printk(KERN_ERR "%s: invalid argument for key_type_e %d err: %d", __func__,
               key_type, err);
        break;
    }

out:
    return err;
}

static void __reg_tlv_enqueue(const void                                *reg_tlv,
                              uint32_t                                   reg_len,
                              struct sxd_bulk_cntr_buffer_layout_common *layout_common __attribute__((unused)),
                              void                                      *context)
{
    skb_node_t      *skb_node_p = (skb_node_t *)context;
    reg_tlv_node_t * reg_tlv_node_p = NULL;

    /* allocate reg_tlv node*/
    reg_tlv_node_p = (reg_tlv_node_t *)kzalloc(sizeof(reg_tlv_node_t), GFP_ATOMIC);
    if (reg_tlv_node_p == NULL) {
        printk(KERN_ERR "%s: Memory allocation for spice bulk cntr"
               " reg_tlv_node_p failed - dropping reg_tlv: [%p]\n", __func__, reg_tlv);
        goto out;
    }
    /* update buff pointer on node*/
    reg_tlv_node_p->reg_tlv_p = reg_tlv;

    /*enqueue to reg_tlv_queue - no need for protection as the consumer thread will only approach the
     * reg_tlv list when all reg_tlv's are enqueued*/
    list_add_tail(&reg_tlv_node_p->reg_tlv_node, &skb_node_p->reg_tlv_queue);

out:
    return;
}

static int __spice_bulk_cntr_reg_data_to_buffer_print(enum sxd_bulk_cntr_key_type_e key_type,
                                                      char                          buffer[],
                                                      size_t                        buffer_length,
                                                      spice_bulk_cntr_ku_reg_u     *reg_data)
{
    int buffer_size = 0;

    switch (key_type) {
    case SXD_BULK_CNTR_KEY_TYPE_PERFORMANCE_E:
        buffer_size = sx_spice_access_reg_mopce_data_to_buffer_print(buffer, buffer_length, &reg_data->mopce_reg);
        break;

    default:
        buffer_size = -EINVAL;
        printk(KERN_ERR "%s: invalid argument for key_type_e %d err: %d", __func__,
               key_type, buffer_size);
        break;
    }

    return buffer_size;
}

static int __sx_spice_bulk_cntr_alloc_kbuf(spice_bulk_cntr_file_db_t *file_db,
                                           size_t                     lbuf,
                                           char                     **kbuf,
                                           size_t                    *kbuf_alloc_size,
                                           size_t                    *kbuf_current_size)
{
    int    err = 0;
    size_t ksize;

    /*limit the buffer size user can request*/
    ksize = (lbuf > MAX_ALLOC_KBUF_SIZE) ? MAX_ALLOC_KBUF_SIZE : lbuf;
    /*first time usage allocate kernel buffer to build the string content for the user*/
    if (!file_db->tr_ctx.kbuf) {
        *kbuf = (char *)kzalloc(sizeof(char) * ksize, GFP_KERNEL);
        if (*kbuf == NULL) {
            err = -ENOMEM;
            printk(KERN_ERR "%s: Memory allocation for Spice bulk cntr"
                   " kbuf_p failed err : %d \n", __func__, err);
            goto out;
        }
        *kbuf_alloc_size = ksize;
    } else { /* kbuf is already allocated */
        /* in case the user send a buffer which is larger than the current allocated
         * kernel buffer - realloc as we want to utilize maximum size in single copy session*/
        if (ksize > file_db->tr_ctx.kbuf_alloc_size) {
            *kbuf = (char *)kzalloc(sizeof(char) * ksize, GFP_KERNEL);
            if (*kbuf == NULL) {
                err = -ENOMEM;
                printk(KERN_ERR "%s: Memory reallocation for Spice bulk cntr"
                       " kbuf_p failed err : %d \n", __func__, err);
                goto out;
            }
            kfree(file_db->tr_ctx.kbuf);
            *kbuf_alloc_size = ksize;
        } else {
            *kbuf = file_db->tr_ctx.kbuf;
            *kbuf_alloc_size = file_db->tr_ctx.kbuf_alloc_size;
        }
    }
    *kbuf_current_size = ksize;

out:
    return err;
}

static int __sx_spice_bulk_cntr_tr_status_get(spice_bulk_cntr_file_db_t    *file_db,
                                              enum sxd_bulk_cntr_key_type_e key_type,
                                              char                         *requested_buf,
                                              loff_t                       *requested_ppos,
                                              spice_bulk_cntr_req_status_e *req_status)
{
    int                           err = 0;
    spice_bulk_cntr_tr_progress_e tr_progress_state = SPICE_BULK_COUNTER_TR_IDLE_E;

    spin_lock_bh(&file_db->tr_ctx_lock);
    tr_progress_state = file_db->tr_ctx.tr_progress_state;
    /* either :
     * tr_progress_state IDLE with new transaction (ppos = 0)
     * tr_progress_state !IDLE and receive new read from different thread (ppos = 0).
     * tr_progress_state !IDLE and receive ppos != 0 which indicates an ongoing copy*/
    if ((SPICE_BULK_COUNTER_TR_IDLE_E != tr_progress_state) && (0 != *requested_ppos)) {         /*ongoing copy*/
        *req_status = SPICE_BULK_COUNTER_TR_ONGOING_E;
    } else if ((SPICE_BULK_COUNTER_TR_IDLE_E == tr_progress_state) && (0 == *requested_ppos)) {  /* trigger new transaction*/
        *req_status = SPICE_BULK_COUNTER_TR_NEW_E;
    } else if ((SPICE_BULK_COUNTER_TR_IDLE_E != tr_progress_state) && (0 == *requested_ppos)) {  /*new request while in ongoing copy*/
        *req_status = SPICE_BULK_COUNTER_TR_BUSY_E;
    } else {                                                        /*if we pass here - issue with user*/
        *req_status = SPICE_BULK_COUNTER_TR_ERROR_E;
    }
    spin_unlock_bh(&file_db->tr_ctx_lock);

    return err;
}

static int __sx_spice_bulk_cntr_tr_set(spice_bulk_cntr_event_params_t *params)
{
    int                           err = 0;
    struct ku_mocs_reg            reg_data;
    sxd_bulk_cntr_event_id_t      ev_id;
    pid_t                         client_pid = current->tgid;
    struct sx_dev                *dev = params->dev;
    char                         *kbuf = NULL;
    size_t                        lbuf = params->data.read_data.lbuf;
    size_t                        kbuf_alloc_size = 0, kbuf_current_size = 0;
    struct completion            *skb_queue_not_empty_p = NULL;
    enum sxd_bulk_cntr_key_type_e key_type = params->key_type;
    struct sx_emad_in_params      in_params;
    spice_bulk_cntr_file_db_t    *file_db = (spice_bulk_cntr_file_db_t *)params->context;

    memset(&reg_data, 0, sizeof(reg_data));
    memset(&in_params, 0, sizeof(in_params));

    in_params.silent = true;

    if (params->op == SPICE_BULK_COUNTER_CANCEL_OP_E) {
        /*init mocs reg*/
        err = __sx_spice_bulk_cntr_init_mocs(dev, &reg_data, NULL /*ev_id*/, 0 /*READ*/, 1 /* cancel */, key_type);
        if (err) {
            printk(KERN_ERR "%s: invalid argument for key_type_e %d err: %d", __func__,
                   key_type, err);
            goto out;
        }
    } else {/*SPICE_BULK_COUNTER_READ_OP_E*/
        /*allocate kernel buffer*/
        err = __sx_spice_bulk_cntr_alloc_kbuf(file_db, lbuf, &kbuf, &kbuf_alloc_size, &kbuf_current_size);
        if (err) {
            printk(KERN_ERR "%s: Memory allocation for Spice bulk cntr"
                   " kbuf_p failed err : %d \n", __func__, err);
            goto out;
        }

        /*allocate completion - dynamically per new transaction*/
        skb_queue_not_empty_p = (struct completion *)kmalloc(sizeof(struct completion), GFP_KERNEL);
        if (skb_queue_not_empty_p == NULL) {
            err = -ENOMEM;
            printk(KERN_ERR "%s: Memory allocation for Spice bulk cntr"
                   " skb_queue_not_empty_p failed err : %d \n", __func__, err);
            goto completion_rollback;
        }
        /*init completion*/
        init_completion(skb_queue_not_empty_p);

        /*generate event id to hook on trap*/
        __sx_spice_bulk_cntr_generate_event_id(client_pid, key_type, &ev_id);

        /* init mocs */
        err = __sx_spice_bulk_cntr_init_mocs(dev, &reg_data, &ev_id, 0 /*READ*/, 0 /* start */, key_type);
        if (err) {
            printk(KERN_ERR "%s: invalid argument for key_type_e %d err: %d", __func__,
                   key_type, err);
            goto init_mocs_rollback;
        }

        /*register to sx_driver db only to enforce the BULK_CNTR_MAX_IN_PROGRESS restriction
         * and update internal db both actions should be atomic*/
        spin_lock_bh(&file_db->tr_ctx_lock);
        err = bulk_cntr_db_mocs_session_acquire(key_type);
        if (err) {
            printk(KERN_ERR "%s: ,transaction for counter type: %d denied  - "
                   "exceed's the maximal allowed number of MOCS sessions ", __func__, key_type);

            spin_unlock_bh(&file_db->tr_ctx_lock);
            goto session_acquire_rollback;
        }

        file_db->tr_ctx.is_mocs_done = false;
        file_db->tr_ctx.tr_progress_state = SPICE_BULK_COUNTER_TR_PENDING_MOCS_DONE;
        file_db->tr_ctx.ev_id = ev_id;
        file_db->tr_ctx.kbuf = kbuf;
        file_db->tr_ctx.kbuf_alloc_size = kbuf_alloc_size;
        file_db->tr_ctx.kbuf_current_size = kbuf_current_size;
        file_db->tr_ctx.skb_queue_not_empty_p = skb_queue_not_empty_p;
        spin_unlock_bh(&file_db->tr_ctx_lock);
    }

    /*send IFC */
    err = sx_EMAD_ACCESS_REG_MOCS(dev, EMAD_PRIO_LOW, EMAD_METHOD_WRITE, &in_params, NULL, &reg_data);
    if (err) {
        printk(KERN_ERR "SPICE: sx_ACCESS_REG_MOCS failed with err: %d\n", err);
        goto mocs_set_rollback;
    }

    return err;

/*roll backs*/
mocs_set_rollback:
    bulk_cntr_db_mocs_session_release(key_type);
    file_db->tr_ctx.tr_progress_state = SPICE_BULK_COUNTER_TR_IDLE_E;
session_acquire_rollback:
init_mocs_rollback:
    kfree(skb_queue_not_empty_p);
completion_rollback:
    kfree(kbuf);
out:
    return err;
}

static ssize_t __sx_spice_bulk_cntr_tr_ongoing(spice_bulk_cntr_event_params_t *params_p)
{
    spice_bulk_cntr_file_db_t *file_db = (spice_bulk_cntr_file_db_t *)params_p->context;

    /*user*/
    char                         *buf = params_p->data.read_data.buf;
    size_t                        lbuf = params_p->data.read_data.lbuf;
    loff_t                       *user_ppos = params_p->data.read_data.ppos;
    enum sxd_bulk_cntr_key_type_e key_type = params_p->key_type;

    /*kernel*/
    char              *kbuf_iter = file_db->tr_ctx.kbuf;
    size_t             kbuf_size_cnt = 0, kbuf_size = file_db->tr_ctx.kbuf_current_size;
    loff_t             kbuf_ppos = 0;
    ssize_t            ret = 0, print_data_size = 0;
    skb_node_t        *skb_node = NULL;
    reg_tlv_node_t    *reg_tlv_node = NULL;
    struct completion *skb_queue_not_empty_p = file_db->tr_ctx.skb_queue_not_empty_p;

    /* mocs done indication is expected to be found on the last skb of the queue
     * when parsed the db indication below is set as an indication for the next cb
     * that the copy routine is done (return 0 to user)*/
    if (file_db->tr_ctx.is_mocs_done) {
#ifdef SPICE_BULK_CNTR_STATISTICS_LOG_EN
        __sx_spice_bulk_cntr_print_stats(file_db);
#endif
        goto tr_finalize;
    }

    /* cap the kernel buffer size not to exceed the lbuf provided by user*/
    __sx_spice_bulk_cntr_cap_kbuffer_size(file_db, lbuf, user_ppos, &kbuf_size);

    /* copy routine loop - sweep the skb queue and for each in process skb
    * process all reg_tlv's that are queued (copy data to kernel buffer)*/
    while (true) {
        if (!file_db->tr_ctx.is_skb_inproc) {
            /* if we need to pull a new skb we wait for the completion done counter in order to make sure
             * the traps and the consumer thread are synced i.e we dont try to pop list node before the first one is enqueued.
             */
            if (wait_for_completion_interruptible_timeout(skb_queue_not_empty_p,
                                                          msecs_to_jiffies(WAIT_TIME_OUT)) == 0) {
                ret = -ETIMEDOUT;
                printk(KERN_ERR "%s: spice bulk counters timed out after %d [msec] with no completion skb_queue \n",
                       __func__,
                       WAIT_TIME_OUT);
                goto tr_finalize;
            }
        }

        skb_node = list_first_entry_or_null(&file_db->tr_ctx.skb_queue, skb_node_t, skb_node);
        if (!skb_node) {
            ret = -EFAULT;
            printk(KERN_ERR " %s: invalid state - skb_queue is empty ", __func__);
            goto tr_finalize;
        }
        file_db->tr_ctx.is_skb_inproc = true;

        /* if the mocs_done bool is set on the skb its an indication for the last trap on the queue.
         * thus we pass the mocs_done indication to the global file db and continue to flush the current
         * kernel buffer content to the user.the indication will end the transaction in the next read cb.
         */
        if (skb_node->mocs_done_ind) {
            file_db->tr_ctx.is_mocs_done = true;
            break;
        }

        /* pop reg_tlv entry from the queue on the current skb node
         * no lock protection is needed as we only start parsing once all reg_tlv's are enqueued*/
        reg_tlv_node = list_first_entry_or_null(&skb_node->reg_tlv_queue, reg_tlv_node_t, reg_tlv_node);
        if (reg_tlv_node) {
            /* each reg_tlv in the list is decoded once, and the binary data is kept in the file_db
             * in case the transaction will consist of several user read call backs.*/
            if (!reg_tlv_node->is_decoded) {
                ret = __reg_tlv_decode(key_type, reg_tlv_node->reg_tlv_p, &file_db->tr_ctx.reg_data);
                if (ret) {
                    printk(KERN_ERR "%s: failed to decode reg_tlv", __func__);
                    goto tr_finalize;
                }
                reg_tlv_node->is_decoded = true;
            }

            print_data_size = __spice_bulk_cntr_reg_data_to_buffer_print(key_type, kbuf_iter,
                                                                         kbuf_size - kbuf_size_cnt,
                                                                         &file_db->tr_ctx.reg_data);

            /* all counters were copied successfully if print_data_size > 0
             * therefore we can dequeue and free the reg_tlv*/
            if (print_data_size > 0) {
#ifdef SPICE_BULK_CNTR_LOG_EN
                printk(KERN_INFO " %s: COPY DONE reg_tlv: [%p] of skb: [%p] \n",
                       __func__, reg_tlv_node->reg_tlv_p, skb_node->skb);
#endif
                kbuf_size_cnt += print_data_size;
                kbuf_iter += print_data_size;
                list_del(&reg_tlv_node->reg_tlv_node);
                kfree(reg_tlv_node);
                file_db->tr_ctx.stats.num_of_parsed_reg_tlv++;
            } else {
                /* there was no sufficient kbuf mem to copy the entire reg_tlv content, in this case
                 * break the loop and wait for a new user buffer to copy the current reg_tlv in the
                 * next read call back .*/
#ifdef SPICE_BULK_CNTR_LOG_EN
                printk(
                    KERN_INFO "%s: insufficient buffer space - reg_tlv: [%p] of skb: [%p] wasn't copied - waiting for next read cb\n",
                    __func__,
                    reg_tlv_node->reg_tlv_p,
                    skb_node->skb);
#endif
                break;
            }
        } else {
            /* in case reg_tlv list is empty i.e finished copy of all
             * reg_tlv's on the skb node  - dequeue/release skb, and continue to next skb*/
            spin_lock_bh(&file_db->tr_ctx_lock);
            list_del(&skb_node->skb_node);
            spin_unlock_bh(&file_db->tr_ctx_lock);
            sx_skb_consume(skb_node->skb);
            kfree(skb_node);
            file_db->tr_ctx.is_skb_inproc = false;
            file_db->tr_ctx.stats.num_of_parsed_traps++;
        }
    }

    if (kbuf_size_cnt) {
        ret = simple_read_from_buffer(buf, lbuf, &kbuf_ppos, file_db->tr_ctx.kbuf, kbuf_size_cnt);
        if (ret < 0) {
            printk(KERN_ERR "%s: simple_read_from_buffer failure err: %zu\n", __func__, ret);
            goto tr_finalize;
        }
        /*shift global user buff offset */
        *user_ppos += kbuf_ppos;
    }
#ifdef SPICE_BULK_CNTR_LOG_EN
    printk(KERN_INFO "%s: user buf: [%p] lbuf: %zu user_ppos: %llu kbuf [%p]\n",
           __func__,
           buf,
           lbuf,
           *user_ppos,
           file_db->tr_ctx.kbuf);
    printk(KERN_INFO "%s: kbuf_size_cnt: %zu returned size for the user is : %zu\n", __func__, kbuf_size_cnt, ret);
#endif

    return ret;

tr_finalize:
    spin_lock_bh(&file_db->tr_ctx_lock);
    __sx_spice_bulk_cntr_ctx_finalize(key_type, file_db);
    spin_unlock_bh(&file_db->tr_ctx_lock);
    return ret;
}

/************************************************
 *          IDLE_STATE event handlers           *
 ***********************************************/

/*SPICE_BULK_COUNTER_INIT_OP_E*/
static int __sx_spice_bulk_cntr_file_init(spice_bulk_cntr_event_params_t *params)
{
    int                           err = 0;
    sxd_trap_id_t                 trap_id = 0;
    enum sxd_bulk_cntr_key_type_e key_type = params->key_type;
    spice_bulk_cntr_file_db_t    *file_db = (spice_bulk_cntr_file_db_t *)params->context;


    /*Converts the counter type id (sxd_bulk_cntr_key_type_e) to the corresponding
     * trap enumeration (sxd_trap_id_t)*/
    err = __sx_spice_bulk_cntr_get_trap_id(key_type, &trap_id);

    /*register spice bulk cntr as a listener for the trap id */
    err = sx_spice_bulk_cntr_listener_set(CTRL_CMD_ADD_SYND, params->dev, trap_id, (void *)file_db);
    if (err) {
        printk(KERN_ERR "%s: failed to set trap_id : 0x%x", __func__, trap_id);
        goto out;
    }

    /*update db with init data change state */
    spin_lock_bh(&file_db->tr_ctx_lock);
    __sx_spice_bulk_cntr_state_set(file_db, SPICE_BULK_COUNTER_INITIALIZED_STATE_E);
    spin_unlock_bh(&file_db->tr_ctx_lock);

out:
    return err;
}

/*SPICE_BULK_COUNTER_READ_OP_E*/
static int __sx_spice_bulk_cntr_file_tr_start_on_idle(spice_bulk_cntr_event_params_t *params_p)
{
    int err = -EBUSY;

    if (spice_bulk_cntr_is_issu) {
        printk(KERN_ERR "%s: In service software update - FW is busy"
               "unable to query counter type: %d for device_id: %d\n", __func__,
               params_p->key_type, params_p->dev->device_id);
    } else {
        printk(KERN_ERR "%s: spice_bulk_cntr module is not initialized"
               "unable to query counter type: %d for device_id: %d\n", __func__,
               params_p->key_type, params_p->dev->device_id);
    }

    return err;
}

/************************************************
 *      INITIALIZED_STATE event handlers        *
 ***********************************************/

/*SPICE_BULK_COUNTER_DEINIT_OP_E*/
static int __sx_spice_bulk_cntr_file_deinit(spice_bulk_cntr_event_params_t *params)
{
    int                           err = 0;
    sxd_trap_id_t                 trap_id = 0;
    enum sxd_bulk_cntr_key_type_e key_type = params->key_type;
    spice_bulk_cntr_file_db_t    *file_db = (spice_bulk_cntr_file_db_t  *)params->context;
    struct completion             cancel_completion;
    bool                          is_locked = false;

    /*Converts the counter type id (sxd_bulk_cntr_key_type_e) to the corresponding
     * trap enumeration (sxd_trap_id_t) and unregister from listening*/
    __sx_spice_bulk_cntr_get_trap_id(key_type, &trap_id);
    err = sx_spice_bulk_cntr_listener_set(CTRL_CMD_REMOVE_SYND, params->dev, trap_id, (void *)file_db);
    if (err) {
        printk(KERN_ERR "%s: %s op: %d failed with err %d", __func__,
               "sx_spice_bulk_cntr_listener_set", CTRL_CMD_REMOVE_SYND, err);
        goto out;
    }

    spin_lock_bh(&file_db->tr_ctx_lock);
    is_locked = true;

    switch (file_db->tr_ctx.tr_progress_state) {
    case SPICE_BULK_COUNTER_TR_PENDING_MOCS_DONE:

        /*init completion*/
        init_completion(&cancel_completion);
        file_db->tr_ctx.cancel_completion_p = &cancel_completion;

        __sx_spice_bulk_cntr_state_set(file_db, SPICE_BULK_COUNTER_CANCEL_IN_PROGRESS_STATE_E);
        /* still waiting for MOCS_DONE from FW. - wait
         * until received to end the transaction */
        spin_unlock_bh(&file_db->tr_ctx_lock);
        is_locked = false;

        /*wait for completion*/
        if (wait_for_completion_interruptible_timeout(&cancel_completion, msecs_to_jiffies(WAIT_TIME_OUT)) == 0) {
            err = -ETIMEDOUT;
            printk(KERN_ERR "%s: spice bulk counters timed out after %d [msec] with no completion \n",
                   __func__,
                   WAIT_TIME_OUT);
            goto out;
        }
        /*init completion_p on db*/
        file_db->tr_ctx.cancel_completion_p = NULL;

    /* FALLTHROUGH */
    case SPICE_BULK_COUNTER_TR_MOCS_DONE_E:
        if (!is_locked) {
            spin_lock_bh(&file_db->tr_ctx_lock);
            is_locked = true;
        }
        /*finalize transaction*/
        __sx_spice_bulk_cntr_ctx_finalize(params->key_type, file_db);

        break;

    default:
        break;
    }

    /*free kernel buffer*/
    if (file_db->tr_ctx.kbuf) {
        kfree(file_db->tr_ctx.kbuf);
    }

    /*set IDLE state */
    __sx_spice_bulk_cntr_state_set(file_db, SPICE_BULK_COUNTER_IDLE_STATE_E);

out:
    if (is_locked) {
        spin_unlock_bh(&file_db->tr_ctx_lock);
    }
    return err;
}

/*SPICE_BULK_COUNTER_READ_OP_E*/
static int __sx_spice_bulk_cntr_file_tr_start(spice_bulk_cntr_event_params_t *params)
{
    int                           err = 0;
    ssize_t                       size = 0;
    enum sxd_bulk_cntr_key_type_e key_type = params->key_type;
    spice_bulk_cntr_req_status_e  req_status = SPICE_BULK_COUNTER_TR_INVALID_E;
    char                         *buf = params->data.read_data.buf;
    size_t                        lbuf = params->data.read_data.lbuf;
    loff_t                       *ppos = params->data.read_data.ppos;
    spice_bulk_cntr_file_db_t    *file_db = (spice_bulk_cntr_file_db_t *)params->context;

    err = __sx_spice_bulk_cntr_verify_lbuf(key_type, lbuf);
    if (err) {
        printk(KERN_ERR "%s: Read operation not permitted for counter type : %d insufficient buffer size.\n"
               , __func__, key_type);
        goto out;
    }
    err = __sx_spice_bulk_cntr_tr_status_get(file_db, key_type, buf, ppos, &req_status);
#ifdef SPICE_BULK_CNTR_LOG_EN
    printk(KERN_INFO "%s: transaction status: %s", __func__, __sx_spice_bulk_cntr_transaction_e_str(req_status));
#endif

    switch (req_status) {
    case SPICE_BULK_COUNTER_TR_NEW_E:
        file_db->tr_ctx.stats.producer_start_time = ktime_get_real();
        err = __sx_spice_bulk_cntr_tr_set(params);
        /*mark time stamp for copy start*/
        file_db->tr_ctx.stats.consumer_start_time = ktime_get_real();
        if (err) {
            printk(KERN_ERR "%s: Mocs transaction failure counter type: %d  err : %d", __func__, key_type, err);
            goto out;
        }

    /* FALLTHROUGH */
    case SPICE_BULK_COUNTER_TR_ONGOING_E:

        size = __sx_spice_bulk_cntr_tr_ongoing(params);
        if (size < 0) {
            err = size;
            printk(KERN_ERR "%s: Mocs transaction unable to execute for counter type: %d  err : %d",
                   __func__, key_type, err);
            goto out;
        }
        break;

    case SPICE_BULK_COUNTER_TR_BUSY_E:
        err = -EBUSY;
        printk(KERN_ERR "%s: Mocs transaction unable to execute for counter type: %d  err : %d",
               __func__,
               key_type,
               err);
        break;

    case SPICE_BULK_COUNTER_TR_ERROR_E:
        err = -EINVAL;
        printk(KERN_ERR "%s: Mocs transaction unable to execute for counter type: %d  err : %d",
               __func__,
               key_type,
               err);
        break;

    default:
        break;
    }

out:
    if (err) {
        return err;
    } else {
        return size;
    }
}

/*SPICE_BULK_COUNTER_CANCEL_OP_E*/
static int __sx_spice_bulk_cntr_file_tr_cancel(spice_bulk_cntr_event_params_t *params)
{
    int                        err = 0;
    spice_bulk_cntr_file_db_t *file_db = (spice_bulk_cntr_file_db_t *)params->context;
    struct completion          cancel_completion;
    bool                       is_locked = false;

    spin_lock_bh(&file_db->tr_ctx_lock);
    is_locked = true;

#ifdef SPICE_BULK_CNTR_LOG_EN
    printk(KERN_INFO " %s: tr_progress_state: %d \n",
           __func__, file_db->tr_ctx.tr_progress_state);
#endif

    switch (file_db->tr_ctx.tr_progress_state) {
    case SPICE_BULK_COUNTER_TR_PENDING_MOCS_DONE:
        /*init completion*/
        init_completion(&cancel_completion);
        file_db->tr_ctx.cancel_completion_p = &cancel_completion;
        __sx_spice_bulk_cntr_state_set(file_db, SPICE_BULK_COUNTER_CANCEL_IN_PROGRESS_STATE_E);
        /* still waiting for MOCS_DONE from FW. - wait
         * until received to end the transaction */
        spin_unlock_bh(&file_db->tr_ctx_lock);
        is_locked = false;

        /*wait for completion*/
        if (wait_for_completion_interruptible_timeout(&cancel_completion, msecs_to_jiffies(WAIT_TIME_OUT)) == 0) {
            err = -ETIMEDOUT;
            printk(KERN_ERR "%s: spice bulk counters timed out after %d [msec] with no completion \n",
                   __func__,
                   WAIT_TIME_OUT);
            goto out;
        }

        /*init completion_p on db*/
        file_db->tr_ctx.cancel_completion_p = NULL;

    /* FALLTHROUGH */
    case SPICE_BULK_COUNTER_TR_MOCS_DONE_E:
        if (!is_locked) {
            spin_lock_bh(&file_db->tr_ctx_lock);
            is_locked = true;
        }
        /*finalize transaction*/
        __sx_spice_bulk_cntr_ctx_finalize(params->key_type, file_db);
        /*back to initialized state */
        __sx_spice_bulk_cntr_state_set(file_db, SPICE_BULK_COUNTER_INITIALIZED_STATE_E);
        break;

    default:
        break;
    }

out:
    if (is_locked) {
        spin_unlock_bh(&file_db->tr_ctx_lock);
    }
    return err;
}

/*SPICE_BULK_COUNTER_TRAP_DONE_OP_E*/
static int __sx_spice_bulk_cntr_file_trap_done(spice_bulk_cntr_event_params_t *params)
{
    int                        err = 0;
    spice_bulk_cntr_file_db_t *file_db = (spice_bulk_cntr_file_db_t *)params->context;
    skb_node_t                *node_p = NULL;
    uint16_t                   hw_synd = params->data.completion_data.hw_synd;

    /* allocate list node*/
    node_p = (skb_node_t *)kzalloc(sizeof(skb_node_t), GFP_ATOMIC);
    if (!node_p) {
        err = -ENOMEM;
        printk(KERN_ERR "%s: Memory allocation for Spice bulk cntr"
               " node_p failed dropping trap id: 0x%x\n", __func__, hw_synd);
        goto out;
    }

    /*reference the buffer - release when copy is done*/
    skb_get(params->data.completion_data.skb);
    node_p->skb = params->data.completion_data.skb;
    /* initialize reg_tlv queue*/
    INIT_LIST_HEAD(&node_p->reg_tlv_queue);

    /*need to protect skb queue approach consumer/producer should be synced */
    spin_lock_bh(&file_db->tr_ctx_lock);
    list_add_tail(&node_p->skb_node, &file_db->tr_ctx.skb_queue);
    spin_unlock_bh(&file_db->tr_ctx_lock);

    if (hw_synd == SXD_TRAP_ID_MOCS_DONE) {
        node_p->mocs_done_ind = true;
        file_db->tr_ctx.tr_progress_state = SPICE_BULK_COUNTER_TR_MOCS_DONE_E;
        /*mark time stamp for end of trap enqueue - take stamp after each one*/
        file_db->tr_ctx.stats.producer_end_time = ktime_get_real();
    } else {
        sx_bulk_cntr_multi_emad_parse(node_p->skb->data, node_p->skb->len,
                                      __reg_tlv_enqueue, (void *)node_p, true);
    }
    complete(file_db->tr_ctx.skb_queue_not_empty_p);

#ifdef SPICE_BULK_CNTR_LOG_EN
    printk(KERN_INFO "%s: Trap completed synd: 0x%x skb : [%p] is queued \n", __func__,
           hw_synd, node_p->skb);
#endif

out:
    return err;
}

/************************************************
 *   CANCEL_IN_PROGRESS_STATE event handlers    *
 ***********************************************/

/*SPICE_BULK_COUNTER_TRAP_DONE_OP_E*/
static int __sx_spice_bulk_cntr_file_trap_done_on_cancel(spice_bulk_cntr_event_params_t *params)
{
    spice_bulk_cntr_file_db_t *file_db = (spice_bulk_cntr_file_db_t *)params->context;
    uint16_t                   hw_synd = params->data.completion_data.hw_synd;

    /* other traps in canceled state are dropped*/
    /* receive mocs_done while in cancel - only release the waiting thread
     */
    spin_lock_bh(&file_db->tr_ctx_lock);
    if (hw_synd == SXD_TRAP_ID_MOCS_DONE) {
        file_db->tr_ctx.tr_progress_state = SPICE_BULK_COUNTER_TR_MOCS_DONE_E;
        if (file_db->tr_ctx.cancel_completion_p) {
            complete(file_db->tr_ctx.cancel_completion_p);
        }
    } else {
        file_db->tr_ctx.stats.num_of_dropped_traps++;
    }
    spin_unlock_bh(&file_db->tr_ctx_lock);

    return 0;
}

/************************************************
 *                     API                      *
 ***********************************************/

void sx_spice_access_reg_bulk_counters_list_free(dev_private_data_t *dev_data)
{
    spice_bulk_cntr_file_params_t *iter, *tmp;

    list_for_each_entry_safe(iter, tmp, &dev_data->spice_bulk_cntr_dev_files_list, list_file_params) {
        list_del(&iter->list_file_params);
        kfree(iter);
    }
}

int sx_spice_bulk_cntr_listener_set(enum ku_ctrl_cmd cmd,
                                    struct sx_dev   *dev,
                                    sxd_trap_id_t    trap_id,
                                    void            *context)
{
    struct ku_synd_ioctl      ku;
    union ku_filter_critireas critireas;
    enum l2_type              listener_type = L2_TYPE_DONT_CARE;
    int                       err = 0;

    memset(&ku, 0, sizeof(ku));
    memset(&critireas, 0, sizeof(critireas));

    ku.swid = SWID_NUM_DONT_CARE;
    ku.is_default = 0;
    ku.is_register = 1;
    ku.syndrome_num = trap_id;


    if (cmd == CTRL_CMD_ADD_SYND) {
        err = sx_core_add_synd(ku.swid, ku.syndrome_num,
                               listener_type, current->pid, current->comm, ku.is_default,
                               &critireas, __sx_spice_bulk_cntr_handle_completion_event, context,
                               CHECK_DUP_ENABLED_E, dev, &(ku.port_vlan_params), ku.is_register);
    } else {
        err = sx_core_remove_synd(ku.swid, ku.syndrome_num,
                                  listener_type, ku.is_default,
                                  &critireas, context, dev, NULL, &(ku.port_vlan_params), ku.is_register, NULL);
    }

    if (err) {
        printk(KERN_ERR "%s: %s failed with err %d", __func__,
               (cmd == CTRL_CMD_ADD_SYND) ? "sx_core_add_synd" : "sx_core_remove_synd", err);
        goto out;
    }

#ifdef  SPICE_BULK_CNTR_LOG_EN
    printk(KERN_INFO "%s: successfully executed %s num: 0x%x file db ptr: [%p]", __func__,
           (cmd == CTRL_CMD_ADD_SYND) ? "sx_core_add_synd" : "sx_core_remove_synd", ku.syndrome_num, context);
#endif

out:
    return err;
}

int sx_spice_access_reg_bulk_counters_file_create(struct dentry *parent, dev_private_data_t *dev_data)
{
    spice_bulk_cntr_file_params_t *file_params = NULL;
    enum sxd_bulk_cntr_key_type_e  typeidx = 0;

    /*list file_params per counter for each device_id*/
    INIT_LIST_HEAD(&dev_data->spice_bulk_cntr_dev_files_list);

    /*create file per supported counter type */
    for (; typeidx < SXD_BULK_CNTR_KEY_TYPE_LAST_E; typeidx++) {
        if (SPICE_SUPPORTED_BULK_CNTR_TRAP_MASK & (0x1 << typeidx)) {
            file_params = (spice_bulk_cntr_file_params_t *)kzalloc(sizeof(spice_bulk_cntr_file_params_t), GFP_KERNEL);
            if (!file_params) {
                printk(KERN_ERR " %s: Failed to allocate private data for counter type: %d\n", __func__, typeidx);
                goto out;
            }

            list_add_tail(&file_params->list_file_params, &dev_data->spice_bulk_cntr_dev_files_list);

            file_params->dev = dev_data->dev;
            file_params->key_type = typeidx;
            /*init file_db lock skb list and file operation mutex*/
            spin_lock_init(&file_params->file_db.tr_ctx_lock);
            INIT_LIST_HEAD(&file_params->file_db.tr_ctx.skb_queue);
            mutex_init(&file_params->file_db.tr_file_op_mutex);
            debugfs_create_file(__sx_spice_bulk_cntr_type_mask_e_str(typeidx),
                                0644,
                                parent,
                                (void *)file_params,
                                &spice_bulk_cntr_fops);
        }
    }
    return 0;
out:
    return -ENOMEM;
}

int sx_spice_bulk_counters_release_cb(struct inode *inode, struct file *filp)
{
    int                            err = 0;
    spice_bulk_cntr_event_params_t tr_params;
    spice_bulk_cntr_file_params_t *file_params = (spice_bulk_cntr_file_params_t *)filp->f_inode->i_private;

    memset(&tr_params, 0, sizeof(spice_bulk_cntr_event_params_t));

    mutex_lock(&file_params->file_db.tr_file_op_mutex);
    tr_params.op = SPICE_BULK_COUNTER_CANCEL_OP_E;
    tr_params.dev = file_params->dev;
    tr_params.key_type = file_params->key_type;
    tr_params.context = (void *)&file_params->file_db;

    /*invoke cancel op */
    err = sx_spice_bulk_cntr_event(&tr_params);
    mutex_unlock(&file_params->file_db.tr_file_op_mutex);

    return err;
}

ssize_t sx_spice_bulk_counters_read_cb(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    int                            err = 0;
    ssize_t                        size = 0;
    spice_bulk_cntr_event_params_t tr_params;
    spice_bulk_cntr_file_params_t *file_params = (spice_bulk_cntr_file_params_t *)filp->f_inode->i_private;

    memset(&tr_params, 0, sizeof(spice_bulk_cntr_event_params_t));


    if (NULL == buf) {
        err = -EINVAL;
        printk(KERN_ERR "%s: invalid NULL argument", __func__);
        goto out;
    }
    mutex_lock(&file_params->file_db.tr_file_op_mutex);
    tr_params.op = SPICE_BULK_COUNTER_READ_OP_E;
    tr_params.dev = file_params->dev;
    tr_params.key_type = file_params->key_type;
    tr_params.data.read_data.buf = buf;
    tr_params.data.read_data.lbuf = lbuf;
    tr_params.data.read_data.ppos = ppos;
    tr_params.context = (void *)&file_params->file_db;
    /*invoke read op */
    size = sx_spice_bulk_cntr_event(&tr_params);
    mutex_unlock(&file_params->file_db.tr_file_op_mutex);

    return size;
out:
    return err;
}

ssize_t sx_spice_bulk_cntr_event(spice_bulk_cntr_event_params_t *params_p)
{
    ssize_t                    err = 0;
    spice_bulk_cntr_state_e    state = SPICE_BULK_COUNTER_IDLE_STATE_E;
    struct sx_dev             *dev = params_p->dev;
    spice_bulk_cntr_file_db_t *file_db = (spice_bulk_cntr_file_db_t *)params_p->context;

    if (!file_db) {
        printk(KERN_ERR "%s: db is not initialized invalid device_id : %d", __func__, dev->device_id);
        goto out;
    }

    spin_lock_bh(&file_db->tr_ctx_lock);
    __sx_spice_bulk_cntr_state_get(file_db, &state);
    spin_unlock_bh(&file_db->tr_ctx_lock);

#ifdef SPICE_BULK_CNTR_LOG_EN
    printk(KERN_INFO "%s: Invoke event: [%s]  on [%s] state on device_id : %d counter type: %d",
           __func__,
           __sx_spice_bulk_cntr_op_e_str(params_p->op),
           __sx_spice_bulk_cntr_state_e_str(state),
           dev->device_id,
           params_p->key_type);
#endif
    /*invoke state handlers*/
    switch (state) {
    case SPICE_BULK_COUNTER_IDLE_STATE_E:
        switch (params_p->op) {
        case SPICE_BULK_COUNTER_INIT_OP_E:
            err = __sx_spice_bulk_cntr_file_init(params_p);
            break;

        case SPICE_BULK_COUNTER_READ_OP_E:
            err = __sx_spice_bulk_cntr_file_tr_start_on_idle(params_p);
            break;

        default:/*ignore*/
            break;
        }
        break;

    case SPICE_BULK_COUNTER_INITIALIZED_STATE_E:
        switch (params_p->op) {
        case SPICE_BULK_COUNTER_DEINIT_OP_E:
            err = __sx_spice_bulk_cntr_file_deinit(params_p);
            break;

        case SPICE_BULK_COUNTER_READ_OP_E:
            err = __sx_spice_bulk_cntr_file_tr_start(params_p);
            break;

        case SPICE_BULK_COUNTER_CANCEL_OP_E:
            err = __sx_spice_bulk_cntr_file_tr_cancel(params_p);
            break;

        case SPICE_BULK_COUNTER_TRAP_DONE_OP_E:
            err = __sx_spice_bulk_cntr_file_trap_done(params_p);
            break;

        default:/*ignore*/
            break;
        }
        break;

    case SPICE_BULK_COUNTER_CANCEL_IN_PROGRESS_STATE_E:
        switch (params_p->op) {
        case SPICE_BULK_COUNTER_TRAP_DONE_OP_E:
            err = __sx_spice_bulk_cntr_file_trap_done_on_cancel(params_p);

        default:/*ignore*/
            break;
        }
        break;


    default:
        break;
    }

out:
    return err;
}
