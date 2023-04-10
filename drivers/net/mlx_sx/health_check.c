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

#include <linux/workqueue.h>
#include <linux/list.h>
#include <linux/seq_file.h>
#include <linux/module.h>
#include <linux/delay.h>


#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include "sx.h"
#include "dq.h"
#include "health_check.h"
#include "alloc.h"
#include "sx_dbg_dump_proc.h"
#include "dev_db.h"
#include "emad.h"

#define DEV_ID_ALL (0)

struct catas_cause_data {
    u32 catas_buf;
};

struct dq_cause_data {
    int dqn;
};

struct cmd_ifc_cause_data {
    bool is_cmd_ifc_sent_from_health;
};

struct sdk_thread_cause_data {
    const char         * msg_error;
    sxd_thread_failure_e sdk_thread_id;
};

struct external_cause_data {
    char err_msg[128];
};

struct sx_cmd_ifc {
    u64   last_cmd_ifc_counter;           /*last number of cmd that sent */
    void *mailbox_p; /* mailbox function as opaque (void*) */
    void *cmd_ctx;     /* context function as opaque (void*) */
    bool  is_last_pkt_sent_via_health;
};

struct config_sdq {
    struct sx_bitmap sdq_bitmap;
    u64              num_of_check_iter;      /*count number of check iteration that made*/
    u32              max_iter_allowed;                /*maximum time that that go bit should ACK for cmd_ifc ,GO_BIT_TIMEOUT_MSECS/periodic_time +1 */
};

struct sx_health_check_config {
    struct sx_bitmap  rdq_bitmap;
    struct sx_bitmap  last_rdq_bitmap; /* keep state upon config change */
    struct sx_bitmap  ignore_rdq_bitmap; /* will contain all WJH RDQ the need to ignore and not monitor*/
    struct config_sdq sdq;
    struct sx_cmd_ifc cmd_ifc;
    uint32_t          periodic_time;
    uint32_t          failures_num;
};

struct sx_health_dev_info {
    struct sx_dev      *dev;
    struct delayed_work main_health_check_dwork;
    struct list_head    dev_list;
    u32 __iomem        *catas_iomap;
    struct mutex        lock;

    /* following fields must be accessed within device information lock */
    struct list_head              failure_ts_list;
    struct list_head              warning_ts_list;
    u32                           failures_detected;
    u32                           warnings_detected;
    sxd_health_cause_t            fatal_cause;
    bool                          health_check_first_itr_skip_checks_func;
    struct sx_health_check_config config;
    bool                          disabled;
};

struct health_check_kernel_thread_t {
    unsigned long             jiffies;       /* time when the failure happened */
    struct list_head          list;
    char                    * name;       /*name of the kernel work queue thread */
    struct workqueue_struct * wq;
    u64                       old_counter;       /* counter status from prev iteration */
    u64                       new_counter;       /* will be increase in case the thread works as expected */
    struct delayed_work       kernel_wq_increase_cnt_dwork;
};

union sdk_health_cause_data {
    struct catas_cause_data             catas_data; /* catas event */
    struct dq_cause_data                dq_data; /* for SDQ/RDQ errors */
    struct cmd_ifc_cause_data           cmd_ifc_data; /* for cmd_ifc errors */
    struct sdk_thread_cause_data        sdk_thread_data;
    struct health_check_kernel_thread_t kernel_thread_data;
    struct external_cause_data          external_data;
};

struct issue_info {
    unsigned long               jiffies; /* time when the failure happened */
    struct list_head            list;
    sxd_health_cause_t          cause;
    bool                        has_cause_data;
    union sdk_health_cause_data cause_data;
};

struct external_cause_work {
    struct work_struct          w;
    u8                          dev_id; /* dev_id == DEV_ID_ALL means all devices */
    u32                         issue_severity;
    union sdk_health_cause_data cause_data;
};

static ssize_t __health_check_running_cntr_cb(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static struct kobj_attribute __health_check_running_counter_attr = __ATTR(health_check_running_counter,
                                                                          S_IRUGO,
                                                                          __health_check_running_cntr_cb,
                                                                          NULL);

static struct workqueue_struct *__health_check_wq = NULL;
static struct delayed_work      __health_check_ts_work;
static struct delayed_work      __kernel_workqueue_monitor_dwork;
static uint64_t                 __health_check_ts = 0;
static bool                     __health_check_ts_trigger = false;
static bool                     __health_check_wq_threads_trigger = false;
static char                     __wq_thread_name_trigger[30] = "";
static bool                     __is_first_iteration_of_kernel_wq_monitor_s = false;
static u32                      __kernel_thread_monitor_cnt = 0;
static LIST_HEAD(__kernel_thread_list);
static LIST_HEAD(__dev_info_list);
static DEFINE_MUTEX(__health_check_lock);
static DEFINE_MUTEX(__kthreads_monitor_lock);

static const char * const sx_health_thread_id_str_s[] = {
    SXD_FOREACH_OBJECT_HEALTH_THREAD_FAILURE_ID(SXD_GENERATE_STRING)
};

/************************************************
 *  Local function declarations
 ***********************************************/
const char * thread_id_str(sxd_thread_failure_e thread_id)
{
    return ((thread_id > SXD_HEALTH_THREAD_MAX_E) ?
            "Unknown" : sx_health_thread_id_str_s[thread_id]);
};

#define START_HETT_SESSION 0
#define STOP_HETT_SEASSON  1

/* must be called within the device information lock */
static void __add_issue(struct sx_health_dev_info   *info,
                        u32                          issue_severity,
                        sxd_health_cause_t           cause,
                        union sdk_health_cause_data *cause_data)
{
    struct issue_info *iter = NULL, *tmp = NULL, *new_issue = NULL;
    unsigned long      now = jiffies;
    u32               *issues_detected =
        (issue_severity == SXD_THREAD_SEVERITY_WARNING_E) ? &info->warnings_detected : &info->failures_detected;
    struct list_head *issues_ts_list =
        (issue_severity == SXD_THREAD_SEVERITY_WARNING_E) ? &info->warning_ts_list : &info->failure_ts_list;

    if (SXD_HEALTH_CAUSE_NONE != info->fatal_cause) {
        /* device is already in fatal mode, ignoring any additional issues */
        return;
    }

    /* check if there are old failures or warnings, if so remove from the list */
    list_for_each_entry_safe(iter, tmp, issues_ts_list, list) {
        if (time_after(now, iter->jiffies + info->config.failures_num * 10 * HZ)) {
            *issues_detected -= 1;
            list_del(&iter->list);
            if (new_issue == NULL) {
                new_issue = iter; /* instead of allocating a new one, use an old one */
            } else {
                kfree(iter);
            }
        } else {
            break; /* failures are in chronological order, if we're here we can stop the iteration */
        }
    }

    if (SXD_HEALTH_SEVERITY_FATAL == issue_severity) {
        info->fatal_cause = cause;
    }

    if (new_issue == NULL) { /* we have to allocate a new one */
        new_issue = kzalloc(sizeof(struct issue_info), GFP_KERNEL);

        if (new_issue == NULL) {
            printk(KERN_ERR "couldn't allocate device %u health-check failure\n", info->dev->device_id);
            return;
        }
    } else {
        memset(new_issue, 0, sizeof(struct issue_info));
    }

    INIT_LIST_HEAD(&new_issue->list);
    new_issue->jiffies = now;
    new_issue->cause = cause;
    if (cause_data) {
        new_issue->has_cause_data = true;
        memcpy(&new_issue->cause_data, cause_data, sizeof(new_issue->cause_data));
    }
    list_add_tail(&new_issue->list, issues_ts_list);
    *issues_detected += 1;
}

static void __add_issue_to_all_devices(u32                          issue_severity,
                                       sxd_health_cause_t           cause,
                                       union sdk_health_cause_data *cause_data)
{
    struct sx_health_dev_info *info;

    list_for_each_entry(info, &__dev_info_list, dev_list) {
        mutex_lock(&info->lock);
        __add_issue(info, issue_severity, cause, cause_data);
        mutex_unlock(&info->lock);
    }
}

/* check if bitmap_subset covered by bitmap , bitmap is function as the operational
 * bitmap of all the RDQ/SDQ that got hit(traps/traffic) from HW, bitmap_subset
 *  will functions as requested  RDQ/SDQ that we want to get ACK on them.
 *  if bit_id with value of 1 means we got hit (bitmap) or want to get
 *  trap(subset bitmap) on this RDQ/SDQ.
 *  if case of un match function will return the first bit equal to 1
 *  that bitmap not contain,
 *  in case bitmap contain bitmap_subset return  -1 */
static u32 __bitmaps_covered(struct sx_bitmap *bitmap, struct sx_bitmap *bitmap_subset)
{
    u32 bit_id, max, main_bit_id_value, subset_bit_id_value;

    /* bitmap and bitmap_subset share the same size */
    max = sx_bitmap_num_bits(bitmap_subset);

    for (bit_id = 0; bit_id < max; bit_id++) {
        subset_bit_id_value = sx_bitmap_test(bitmap_subset, bit_id);
        /* only in case this rdq/sdq id was requested check operation bit map */
        if (subset_bit_id_value) {
            main_bit_id_value = sx_bitmap_test(bitmap, bit_id);
            if (main_bit_id_value != subset_bit_id_value) {
                return bit_id;
            }
        }
    }
    return (u32) - 1;
}


/* must be called within the health-check lock */
static struct sx_health_dev_info * __info_find(u8 dev_id)
{
    struct sx_dev             *dev = sx_dev_db_get_dev_by_id(dev_id);
    struct sx_health_dev_info *info;

    if (!dev) {
        return NULL;
    }

    list_for_each_entry(info, &__dev_info_list, dev_list) {
        if (info->dev == dev) {
            return info;
        }
    }

    return NULL;
}

static int __write_hett(struct ku_access_hett_reg *hett, struct sx_dev *dev, const char *op)
{
    int err;

    hett->dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&hett->op_tlv, MLXSW_HETT_ID, EMAD_METHOD_WRITE);
    err = sx_ACCESS_REG_HETT(dev, hett);
    if (err) {
        printk(KERN_ERR "sx_ACCESS_REG_HETT (%s) returned with error %d\n", op, err);
    }

    return err;
}

/* calculate how many sdq iteration allowed without ACK from HW,
 * every iteration take periodic_time , max time without ACK is
 * 10000 msecs (10 seconds)   */
static u32 __sx_sdq_calc_num_of_check_iter(u32 periodic_time)
{
    return (10000 / (periodic_time * 1000)) + 1;
}

/* must be called within the device information lock */
static void __check_catas(struct sx_health_dev_info *info)
{
    union sdk_health_cause_data catas_data;
    struct sx_priv             *priv = sx_priv(info->dev);


    if (!priv->debug_trigger_state.catas) { /* debug trigger not set */
        if (!info->catas_iomap) { /* device does not support catas */
            catas_data.catas_data.catas_buf = 0;
        } else {
            catas_data.catas_data.catas_buf = swab32(__raw_readl(info->catas_iomap));
        }
    } else {
        catas_data.catas_data.catas_buf = 0xdeadbeaf;
    }

    /* Bit 0 TCAM ECC error is already covered by MECCC trap, here we only check bit 1. */
    if (catas_data.catas_data.catas_buf & 0x2) {
        __add_issue(info, SXD_THREAD_SEVERITY_FATAL_E, SXD_HEALTH_CAUSE_CATAS, &catas_data);
    }
}

/* must be called within the device information lock */
static int __start_and_check_cmd_ifc(struct sx_health_dev_info *info)
{
    struct sx_priv             *priv = sx_priv(info->dev);
    int                         err = 0;
    union sdk_health_cause_data cause_data;
    bool                        cntr_advanced = (info->config.cmd_ifc.last_cmd_ifc_counter
                                                 < priv->cmd_ifc_num_of_pck_received);

    memset(&cause_data, 0, sizeof(cause_data));

    info->config.cmd_ifc.cmd_ctx = NULL;
    info->config.cmd_ifc.mailbox_p = NULL;

    /* Check if debug trigger turn on*/
    if (priv->debug_trigger_state.cmd_ifc) {
        __add_issue(info, SXD_THREAD_SEVERITY_ERR_E, SXD_HEALTH_CAUSE_GO_BIT, &cause_data);
        goto out;
    }

    /* cmd_ifc got new ACK from last cycle */
    if (cntr_advanced) {
        info->config.cmd_ifc.last_cmd_ifc_counter = priv->cmd_ifc_num_of_pck_received;
        info->config.cmd_ifc.is_last_pkt_sent_via_health = false;
        goto out;
    }
    /* number of cmd_ifc packets not increase from last iteration  */
    /* try to acquire cmd_ifc semaphore*/
    err = sx_cmd_prepare(info->dev, SX_CMD_QUERY_FW_HCR1, &info->config.cmd_ifc.cmd_ctx);
    /*  Acquire semaphore failed ,someone from outside of health check is took it*/
    if (err) {
        /* In the prev iteration we sent cmd_ifc via health check and then
         * external cmd_ifc was taken so its mean the external cmd_ifc
         *  running less then time frame configures (1 sec in default mode) so we will sign that in this iteration packet
         *   did not sent via health check and go out
         **/
        if (info->config.cmd_ifc.is_last_pkt_sent_via_health) {
            info->config.cmd_ifc.is_last_pkt_sent_via_health = false;
            /* its not an error in this case*/
            err = 0;
            goto out;
        }

        /* packet from outside stuck on the cmd_ifc more then time frame configures*/
        cause_data.cmd_ifc_data.is_cmd_ifc_sent_from_health = info->config.cmd_ifc.is_last_pkt_sent_via_health;
        __add_issue(info, SXD_THREAD_SEVERITY_ERR_E, SXD_HEALTH_CAUSE_GO_BIT, &cause_data);
        goto out;
    }

    /* Seceded to acquire cmd_ifc semaphore*/
    /* GO bit not free - Only if sent query_fw via health check in
     * Previous cycles and got timeout  */
    if (sx_cmd_check_go_bit(info->dev, info->dev->device_id)) {
        cause_data.cmd_ifc_data.is_cmd_ifc_sent_from_health = info->config.cmd_ifc.is_last_pkt_sent_via_health;
        __add_issue(info, SXD_THREAD_SEVERITY_ERR_E, SXD_HEALTH_CAUSE_GO_BIT, &cause_data);
        goto out_release;
    }

    /* Go bit cleared and cmd-ifc can be send*/
    info->config.cmd_ifc.last_cmd_ifc_counter = priv->cmd_ifc_num_of_pck_received;
    err = sx_cmd_health_check_send(info->dev, &info->config.cmd_ifc.mailbox_p, info->config.cmd_ifc.cmd_ctx);
    /* Failed to send cmd_ifc*/
    if (err) {
        printk(KERN_ERR "Health check:Failed to send cmd_ifc \n");
        info->config.cmd_ifc.is_last_pkt_sent_via_health = false;
        goto out_release;
    }

    /* check if after 100ms cmd_ifc got ACK*/
    msleep(100);

    /* Go bit still busy and did not got ACK  */
    if (sx_cmd_check_go_bit(info->dev, info->dev->device_id)) {
        cause_data.cmd_ifc_data.is_cmd_ifc_sent_from_health = info->config.cmd_ifc.is_last_pkt_sent_via_health;
        __add_issue(info, SXD_THREAD_SEVERITY_ERR_E, SXD_HEALTH_CAUSE_GO_BIT, &cause_data);
    } else {  /* In case of got ACK after 100ms*/
        info->config.cmd_ifc.last_cmd_ifc_counter = priv->cmd_ifc_num_of_pck_received;
    }

    info->config.cmd_ifc.is_last_pkt_sent_via_health = true;

out_release:
    /* Release the semaphore*/
    sx_cmd_health_check_release(info->dev, info->config.cmd_ifc.mailbox_p, info->config.cmd_ifc.cmd_ctx);

out:
    return err;
}


static void __check_and_report_sdq_failure(struct sx_health_dev_info *info, u32 sub_bitmap_res)
{
    union sdk_health_cause_data dq_data;

    /*failure - exceed the time frame  */
    if (info->config.sdq.num_of_check_iter >= info->config.sdq.max_iter_allowed) {
        dq_data.dq_data.dqn = sub_bitmap_res;
        printk(KERN_ERR PFX "Did not receive completion for SDQ dqn (%u) \n",
               sub_bitmap_res);
        __add_issue(info, SXD_THREAD_SEVERITY_ERR_E, SXD_HEALTH_CAUSE_SDQ, &dq_data);
        /* cleaning parameters to start point*/
        info->config.sdq.num_of_check_iter = 0;
    }
}

static int __test_sdq(struct sx_dev *dev)
{
    /*FW return EMAD_STS_OK in case we send on query mode PPAD full of 0 */
    uint8_t         ppad[16] = { 0 };
    int             len = 0;
    struct sk_buff *skb = NULL;
    struct sk_buff *new_skb = NULL;
    int             ret = 0;
    int             sdq_id;
    u32             max_sdq;
    struct isx_meta meta;
    struct sx_dq   *sdq = NULL;
    struct sx_priv *priv = sx_priv(dev);

    memset(&meta, 0, sizeof(meta));
    /* 0xffffffff TID value will sign that this packet is health check packet */

    max_sdq = priv->dev_cap.max_num_sdqs;
    for (sdq_id = 0; sdq_id < max_sdq; sdq_id++) {
        sdq = priv->sdq_table.dq[sdq_id];
        /* if SDQ exist/in use */
        if (sdq) {
            ret = sx_emad_build(dev->device_id, ppad, sizeof(ppad), &skb,
                                &meta, 0xffff, 0xffff,
                                GFP_KERNEL, PPAD_REG_ID, EMAD_METHOD_QUERY);
            if (ret != 0) {
                printk(KERN_ERR "Health check:failed to send SDQ test packet (ret=%d)\n", ret);
                goto out;
            }

            /* If there's no place for the ISX header
             * need to alloc a new skb and use it instead */
            if (skb_headroom(skb) < ISX_HDR_SIZE) {
                new_skb = skb;
                len = skb->len;
                new_skb = alloc_skb(ISX_HDR_SIZE + len, GFP_KERNEL);
                if (!new_skb) {
                    if (printk_ratelimit()) {
                        printk(KERN_ERR PFX "__test_sdq"
                               "Err: failed allocating "
                               "SKB\n");
                    }
                    /* todo add counters of packets that sent and received under PRIV */

                    kfree_skb(skb); /* drop packet flow, use kfree_skb */

                    return -ENOMEM;
                }

                skb_reserve(new_skb, ISX_HDR_SIZE);
                memcpy(skb_put(new_skb, len), skb->data, len);

                /* free unused clone, use consume_skb */
                consume_skb(skb);

                ret = __sx_core_post_send(dev, new_skb, &meta, sdq_id);
                if (ret != 0) {
                    printk(KERN_ERR "__test_sdq failed to post and send"
                           " via SDQ_Id =%d ,(ret=%d)\n", sdq_id, ret);
                    goto out;
                }
                /* origin skb big enough to contain all data needed */
            } else {
                ret = __sx_core_post_send(dev, skb, &meta, sdq_id);
                if (ret != 0) {
                    printk(KERN_ERR "__test_sdq failed to post and send"
                           " via SDQ_Id =%d ,(ret=%d)\n", sdq_id, ret);
                    goto out;
                }
            }
        }
    }

out:
    return ret;
}

/* must be called within the device information lock */
static int __start_sdq_for_next_cycle(struct sx_health_dev_info *info)
{
    int             err = 0;
    struct sx_priv *priv = sx_priv(info->dev);

    /*initialize operational state RDQ bitmap*/
    sx_bitmap_clear_all(&priv->operational_state.sdq_bitmap);


    err = __test_sdq(info->dev);
    if (err) {
        printk(KERN_ERR "HEALTH CHECK :SDQ monitor- failed to sent PGCR for"
               " dev_id %d [err=%d]\n", info->dev->device_id, err);
        goto out;
    }
out:
    return err;
}

/* must be called within the device information lock */
static void __check_sdq_from_last_cycle(struct sx_health_dev_info *info)
{
    struct sx_priv *priv = sx_priv(info->dev);
    u32             sub_bitmap_res = 0;

    info->config.sdq.num_of_check_iter++;

    sub_bitmap_res = __bitmaps_covered(&priv->operational_state.sdq_bitmap, &info->config.sdq.sdq_bitmap);
    if (sub_bitmap_res != ((u32) - 1)) {
        __check_and_report_sdq_failure(info, sub_bitmap_res);
    } else {
        info->config.sdq.num_of_check_iter = 0;
    }
}

/* must be called within the device information lock */
static void __start_rdq_for_next_cycle(struct sx_health_dev_info *info)
{
    struct ku_access_hett_reg reg_hett;
    int                       err = 0;
    struct sx_priv           *priv = sx_priv(info->dev);


    /*initialize operational state RDQ bitmap*/
    sx_bitmap_clear_all(&priv->operational_state.rdq_bitmap);

    /*rdq_bitmap changed on the fly so last_rdq_bitmap will be static and will represent the HETT requested rdq_bitmap*/
    sx_bitmap_copy(&info->config.last_rdq_bitmap, &info->config.rdq_bitmap);

    /* here we mask all the WJH/ignore RDQ from the RDQ DB (that contain all the
     *  rdq that exist in the chip)*/
    info->config.last_rdq_bitmap.table[0] = (info->config.last_rdq_bitmap.table[0])
                                            & ((~info->config.ignore_rdq_bitmap.table[0]));

    memset(&reg_hett, 0, sizeof(reg_hett));
    reg_hett.hett_reg.opcode = START_HETT_SESSION;
    reg_hett.hett_reg.trap_group_bitmap = info->config.last_rdq_bitmap.table[0];
    err = __write_hett(&reg_hett, info->dev, "send trap group bitmap");

    if (err) {
        /* fatal failure will stop the health mechanism */
        __add_issue(info, SXD_THREAD_SEVERITY_FATAL_E, SXD_HEALTH_CAUSE_FW_HETT, NULL);
    }
}

/* must be called within the device information lock */
static void __check_rdq_from_last_cycle(struct sx_health_dev_info *info)
{
    uint32_t                    sub_bitmap_res = 0;
    union sdk_health_cause_data dq_data;
    struct sx_priv             *priv = sx_priv(info->dev);

    sub_bitmap_res = __bitmaps_covered(&priv->operational_state.rdq_bitmap, &info->config.last_rdq_bitmap);
    if (sub_bitmap_res != ((u32) - 1)) {
        dq_data.dq_data.dqn = sub_bitmap_res;
        __add_issue(info, SXD_THREAD_SEVERITY_ERR_E, SXD_HEALTH_CAUSE_RDQ, &dq_data);
    }
    sx_bitmap_clear_all(&info->config.last_rdq_bitmap);
}

static int __sx_health_add_sdk_thread_failure(u8 dev_id, const sdk_threads_info_t* threads_info)
{
    struct sx_health_dev_info  *info = NULL;
    union sdk_health_cause_data cause_data;


    info = __info_find(dev_id);
    if (!info) {
        return -ENODEV;
    }
    if (SXD_THREAD_SEVERITY_MAX_E < threads_info->severity) {
        printk(KERN_ERR "Health check: the given sdk thread severity = %d is out of range.\n", threads_info->severity);
        return -EPERM;
    }

    mutex_lock(&info->lock);
    cause_data.sdk_thread_data.msg_error = threads_info->error_msg;
    cause_data.sdk_thread_data.sdk_thread_id = threads_info->sdk_thread_id;
    __add_issue(info, threads_info->severity, SXD_HEALTH_CAUSE_SDK_THREADS, &cause_data);

    mutex_unlock(&info->lock);
    return 0;
}

/* MAIN THREAD of health check mechanism , sample all monitors and sent Health check event  */
static void __sx_health_check_cycle(struct work_struct *work)
{
    struct sx_health_dev_info *info = container_of(work, struct sx_health_dev_info, main_health_check_dwork.work);
    int                        err = 0;

    mutex_lock(&info->lock);

    if (info->disabled) {
        /* user removed device from health-check. */
        goto out;
    }

    /* this is an immediate check, no need for 2-step check */
    __check_catas(info);

    if (info->health_check_first_itr_skip_checks_func) {
        info->health_check_first_itr_skip_checks_func = false;
        goto health_monitor;
    }
    __check_sdq_from_last_cycle(info);
    __check_rdq_from_last_cycle(info);


health_monitor:
    __start_rdq_for_next_cycle(info);

    /* start sending packets to SDQ's in case the last SDQ check confirm new
     * season should start */
    if (info->config.sdq.num_of_check_iter == 0) {
        err = __start_sdq_for_next_cycle(info);
        if (err) {
            printk(KERN_ERR "Health check:Failed to start SDQ \n");
            goto out;
        }
    }

    err = __start_and_check_cmd_ifc(info);
    if (err) {
        printk(KERN_ERR "Health check:Failed to start or check cmd_ifc monitor err= %d \n", err);
        goto out;
    }

    if (info->fatal_cause != SXD_HEALTH_CAUSE_NONE) {
        /* Fatal failure detect: send SDK health event and stop monitoring this device */
        sx_send_health_event(info->dev->device_id, info->fatal_cause, SXD_HEALTH_SEVERITY_FATAL);
        printk(KERN_ERR "device %u found FATAL cause and is not monitored anymore!\n", info->dev->device_id);
    } else {
        if (info->failures_detected >= info->config.failures_num) {
            /* Too many failures: send SDK health event with SXD_HEALTH_CAUSE_SDK_WD cause and stop monitoring this device */
            sx_send_health_event(info->dev->device_id, SXD_HEALTH_CAUSE_SDK_WD, SXD_HEALTH_SEVERITY_FATAL);
            printk(KERN_ERR "device %u is notice too many fatal failures and is "
                   "not monitored anymore!\n", info->dev->device_id);
        } else {
            /* Too many Warnings: send SDK health event with SXD_HEALTH_CAUSE_SDK_WD cause ,
             * Note USER not expected to reset the chip */
            if (info->warnings_detected >= info->config.failures_num) {
                sx_send_health_event(info->dev->device_id, SXD_HEALTH_CAUSE_SDK_WD, SXD_HEALTH_SEVERITY_WARN);
                printk(KERN_ERR "device %u is notice too many health checks warnings!\n", info->dev->device_id);
            }
            queue_delayed_work(__health_check_wq, &info->main_health_check_dwork, info->config.periodic_time * HZ);
        }
    }
out:
    mutex_unlock(&info->lock);
}

/* must be called within the health-check lock */
static int __info_alloc(u8                          dev_id,
                        u32                         check_interval,
                        u32                         alert_threshold,
                        unsigned long               hw_groups_curr_status,
                        struct sx_health_dev_info **ret_info)
{
    struct sx_dev             *dev = NULL;
    struct sx_priv            *priv = NULL;
    struct sx_health_dev_info *info = NULL;
    resource_size_t            catas_start = 0;
    u32 __iomem               *catas_iomap = NULL;
    int                        err = 0;
    uint32_t                   dq_id = 0;
    unsigned long              flags;


    dev = sx_dev_db_get_dev_by_id(dev_id);
    if (!dev) {
        printk(KERN_ERR "failed to get device from id (id=%u)\n", dev_id);
        err = -ENODEV;
        goto out;
    }

    priv = sx_priv(dev);

    if (priv->fw.catas_size > 0) {
        catas_start = pci_resource_start(dev->pdev, priv->fw.catas_bar) + priv->fw.catas_offset;
        catas_iomap = ioremap(catas_start, priv->fw.catas_size * 4);
        if (!catas_iomap) {
            printk(KERN_ERR "failed to map internal error buffer on device %u at 0x%llx\n", dev->device_id,
                   catas_start);
            err = -ENOMEM;
            goto out;
        }
    }

    info = kzalloc(sizeof(struct sx_health_dev_info), GFP_KERNEL);
    if (!info) {
        printk(KERN_ERR "could not create a new health-check entry for device %u\n", dev->device_id);
        err = -ENOMEM;
        goto out;
    }

    info->dev = dev;
    info->catas_iomap = catas_iomap;
    info->fatal_cause = SXD_HEALTH_CAUSE_NONE;
    INIT_DELAYED_WORK(&info->main_health_check_dwork, __sx_health_check_cycle);
    INIT_LIST_HEAD(&info->dev_list);
    INIT_LIST_HEAD(&info->failure_ts_list);
    INIT_LIST_HEAD(&info->warning_ts_list);

    mutex_init(&info->lock);
    sx_bitmap_init(&info->config.last_rdq_bitmap, NUMBER_OF_RDQS);
    sx_bitmap_init(&info->config.sdq.sdq_bitmap, NUMBER_OF_SDQS);
    sx_bitmap_init(&info->config.rdq_bitmap, NUMBER_OF_RDQS);
    sx_bitmap_init(&info->config.ignore_rdq_bitmap, NUMBER_OF_RDQS);
    /* set SDQ's that are operate */
    for (dq_id = 0; dq_id < priv->dev_cap.max_num_sdqs; dq_id++) {
        /* if SDQ exist/in use */
        if (priv->sdq_table.dq[dq_id]) {
            sx_bitmap_set(&info->config.sdq.sdq_bitmap, dq_id);
        }
    }

    info->config.periodic_time = check_interval;
    info->config.failures_num = alert_threshold;
    info->config.sdq.max_iter_allowed = __sx_sdq_calc_num_of_check_iter(info->config.periodic_time);


    /* fill the rdq_bitmap with the hw_traps that exist before starting this feature */
    for (dq_id = 0; dq_id < priv->dev_cap.max_num_rdqs; dq_id++) {
        if (test_bit(dq_id, &hw_groups_curr_status)) {
            sx_bitmap_set(&info->config.rdq_bitmap, dq_id);
        }
    }
    info->health_check_first_itr_skip_checks_func = true;

    /* fill the ignore_bitmap with the WJH hw_traps that exist before starting this feature */
    /* must lock set_monitor_rdq_lock first to avoid update of new RDQ WJH in parallel
     * set_monitor_rdq_lock is locked in higher stage (under fun sx_health_check_configure) */
    spin_lock_irqsave(&priv->rdq_table.lock, flags);
    for (dq_id = 0; dq_id < priv->monitor_rdqs_count; dq_id++) {
        sx_bitmap_set(&info->config.ignore_rdq_bitmap, priv->monitor_rdqs_arr[dq_id]);
    }
    spin_unlock_irqrestore(&priv->rdq_table.lock, flags);

    list_add_tail(&info->dev_list, &__dev_info_list);
    *ret_info = info;

out:
    return err;
}

/* must be called within the health-check lock */
static void __info_dealloc(struct sx_health_dev_info *info)
{
    struct issue_info *iter = NULL, *tmp = NULL;

    printk(KERN_INFO "Health-Check: disabling monitoring on device %d\n", info->dev->device_id);

    mutex_lock(&info->lock);
    info->disabled = true;

    list_del(&info->dev_list);

    list_for_each_entry_safe(iter, tmp, &info->failure_ts_list, list) {
        list_del(&iter->list);
        kfree(iter);
    }

    list_for_each_entry_safe(iter, tmp, &info->warning_ts_list, list) {
        list_del(&iter->list);
        kfree(iter);
    }

    iounmap(info->catas_iomap);
    info->catas_iomap = NULL;
    mutex_unlock(&info->lock);

    /* the work we're about to cancel only uses 'info->lock' so it is safe to cancel it
     * synchronously inside the '__health_check_lock' lock. */
    cancel_delayed_work_sync(&info->main_health_check_dwork);
    kfree(info);
}

static void __sx_health_check_update_timestamp(struct work_struct *work)
{
    mutex_lock(&__health_check_lock);

    if (!__health_check_ts_trigger) {
        __health_check_ts++;
    }

    if (__health_check_wq) {
        queue_delayed_work(__health_check_wq, &__health_check_ts_work, HZ); /* 1 second */
    }

    mutex_unlock(&__health_check_lock);
}

/* Adding Dwork for each work queue that exist in health check kernel list*/
static void __start_kernel_threads_monitor(void)
{
    struct health_check_kernel_thread_t *iter_thread = NULL;

    list_for_each_entry(iter_thread, &__kernel_thread_list, list) {
        iter_thread->old_counter = iter_thread->new_counter;
        queue_delayed_work(iter_thread->wq, &iter_thread->kernel_wq_increase_cnt_dwork, 0); /* now */
    }
}

static void __check_kernel_threads_monitor(void)
{
    struct health_check_kernel_thread_t *iter_thread = NULL;

    list_for_each_entry(iter_thread, &__kernel_thread_list, list) {
        if (!(iter_thread->new_counter > iter_thread->old_counter)) {
            /* If we have monitored devices report on the failure to all of them */
            __add_issue_to_all_devices(SXD_THREAD_SEVERITY_ERR_E,
                                       SXD_HEALTH_CAUSE_KERNEL_THREADS,
                                       (union sdk_health_cause_data *)iter_thread);
            break;
        }
    }
}

static void __sx_health_kernel_workqueue_monitor(struct work_struct *work)
{
    /*
     * LOCKS must be in this order:
     * health-check lock
     * threads monitor lock
     * dev-info lock
     */

    mutex_lock(&__health_check_lock);
    mutex_lock(&__kthreads_monitor_lock);

    if (!list_empty(&__dev_info_list)) {
        if (__is_first_iteration_of_kernel_wq_monitor_s) {
            __is_first_iteration_of_kernel_wq_monitor_s = false;
            /*Skip the first check because nothing sent to the kernel WQ's*/
        } else {
            __check_kernel_threads_monitor();
        }

        __start_kernel_threads_monitor();
        queue_delayed_work(__health_check_wq, &__kernel_workqueue_monitor_dwork, HZ);/* every second */
    }

    mutex_unlock(&__kthreads_monitor_lock);
    mutex_unlock(&__health_check_lock);
}

static void __sx_health_inc_wq_thread_counter(struct work_struct *work)
{
    struct health_check_kernel_thread_t *iter_thread;

    iter_thread = container_of(work, struct health_check_kernel_thread_t,
                               kernel_wq_increase_cnt_dwork.work);
    mutex_lock(&__kthreads_monitor_lock);

    if (iter_thread == NULL) {
        printk(KERN_ERR "Health-Check: kernel thread %s not existing in the "
               "kernel threads list anymore and counter didn't change"
               "new counter = %llu \n", iter_thread->name, iter_thread->new_counter);
    } else {
        if (__health_check_wq_threads_trigger) {
            if (strcmp(iter_thread->name, __wq_thread_name_trigger) == 0) {
                goto out;
            } else {
                iter_thread->new_counter++;
            }
        } else {
            iter_thread->new_counter++;
        }
    }
out:
    mutex_unlock(&__kthreads_monitor_lock);
}

void sx_health_check_destroy_monitored_workqueue(struct workqueue_struct * workqueue)
{
    struct health_check_kernel_thread_t *iter_thread, *tmp = NULL;
    bool                                 wq_found_in_list = false;

    mutex_lock(&__kthreads_monitor_lock);
    list_for_each_entry_safe(iter_thread, tmp, &__kernel_thread_list, list) {
        if (workqueue == iter_thread->wq) {
            kfree(iter_thread->name);
            list_del(&iter_thread->list);
            kfree(iter_thread);
            __kernel_thread_monitor_cnt--;
            wq_found_in_list = true;
            break;
        }
    }
    if (!wq_found_in_list) {
        printk(KERN_ERR "Health-Check: kernel thread %s not existing in the "
               "kernel threads list anymore so its not removed from the "
               "list \n", iter_thread->name);
    }

    mutex_unlock(&__kthreads_monitor_lock);
    destroy_workqueue(workqueue);
}

EXPORT_SYMBOL(sx_health_check_destroy_monitored_workqueue); /*to be access to other drivers e.g BFD */

struct workqueue_struct* sx_health_check_create_monitored_workqueue(const char* name)
{
    struct health_check_kernel_thread_t *new_kernel_thread = NULL;

    mutex_lock(&__kthreads_monitor_lock);

    new_kernel_thread = kzalloc(sizeof(struct health_check_kernel_thread_t), GFP_KERNEL);

    if (new_kernel_thread == NULL) {
        printk(KERN_ERR "couldn't allocate new_kernel_thread node\n");
        goto out;
    }
    INIT_LIST_HEAD(&new_kernel_thread->list);
    INIT_DELAYED_WORK(&new_kernel_thread->kernel_wq_increase_cnt_dwork,  __sx_health_inc_wq_thread_counter);

    new_kernel_thread->jiffies = jiffies;
    new_kernel_thread->name = kstrdup(name, GFP_KERNEL);
    if (new_kernel_thread->name == NULL) {
        printk(KERN_ERR "allocate thread name %s for new_kernel_thread failed\n", name);
        kfree(new_kernel_thread);
        new_kernel_thread = NULL;
        goto out;
    }
    new_kernel_thread->wq = create_singlethread_workqueue(name);
    if (!new_kernel_thread->wq) {
        printk(KERN_ERR  "Failed to create wq %s. \n", name);
        kfree(new_kernel_thread->name);
        kfree(new_kernel_thread);
        new_kernel_thread = NULL;
        goto out;
    }
    list_add_tail(&new_kernel_thread->list, &__kernel_thread_list);
    __kernel_thread_monitor_cnt++;
out:
    mutex_unlock(&__kthreads_monitor_lock);
    return new_kernel_thread ? new_kernel_thread->wq : NULL;
}
EXPORT_SYMBOL(sx_health_check_create_monitored_workqueue); /*to be access to other drivers e.g BFD */

static int __sx_health_add_device(u8 dev_id, u32 check_interval, u32 alert_threshold, u64 hw_groups_curr_status)
{
    struct sx_health_dev_info *info = NULL;
    int                        err = 0;
    bool                       is_first_time_device_with_health_check = false;

    if (list_empty(&__dev_info_list)) {
        is_first_time_device_with_health_check = true;
    }

    info = __info_find(dev_id);
    if (!info) {
        err = __info_alloc(dev_id, check_interval, alert_threshold, hw_groups_curr_status, &info);
    } else {
        err = -EEXIST;
    }

    if (!err) {
        if (is_first_time_device_with_health_check) {
            __is_first_iteration_of_kernel_wq_monitor_s = true;
            queue_delayed_work(__health_check_wq, &__kernel_workqueue_monitor_dwork, 0); /* now */
        }
        queue_delayed_work(__health_check_wq, &info->main_health_check_dwork, 0); /* now */
    }

    return err;
}

static void __sx_health_delete_device(u8 dev_id)
{
    struct sx_health_dev_info *info = NULL;

    info = __info_find(dev_id);
    if (info) {
        __info_dealloc(info);
    }
}

int __sx_health_update_tg_locked(u8 dev_id, int hw_trap_group, bool is_add, bool is_wjh_rdq_update)
{
    struct sx_health_dev_info *info = NULL;

    info = __info_find(dev_id);
    if (!info) {
        printk(KERN_INFO "Health-Check: failed to update tg WJH because health "
               "check not enable yet on device %u\n", dev_id);
        return -ENODEV;
    }

    mutex_lock(&info->lock);

    if (is_add) {
        if (is_wjh_rdq_update) {
            printk(KERN_INFO "Health-Check: Add RDQ WJH %d to ignore list on device %u\n",
                   hw_trap_group,
                   dev_id);
            sx_bitmap_set(&info->config.ignore_rdq_bitmap, hw_trap_group);
            /*in case of create new WJH RDQ must to update the subset bitmap
             *  as well(last_rdq_bitmap) to avoid a race when comparing
             *  to operation rdq bitmap */
            sx_bitmap_free(&info->config.last_rdq_bitmap, hw_trap_group);
        } else {
            sx_bitmap_set(&info->config.rdq_bitmap, hw_trap_group);
        }
    } else {
        if (is_wjh_rdq_update) {
            printk(KERN_INFO "Health-Check: Delete RDQ WJH %d from ignore list on device %u\n",
                   hw_trap_group,
                   dev_id);
            sx_bitmap_free(&info->config.ignore_rdq_bitmap, hw_trap_group);
        } else {
            sx_bitmap_free(&info->config.rdq_bitmap, hw_trap_group);
            /*in case of deletion must to update the subset bitmap
             *  as well(last_rdq_bitmap) to avoid a race when comparing
             *  to operation rdq bitmap */
            sx_bitmap_free(&info->config.last_rdq_bitmap, hw_trap_group);
        }
    }

    mutex_unlock(&info->lock);
    return 0;
}

int sx_health_update_tg(u8 dev_id, int hw_trap_group, bool is_add, bool is_wjh_rdq_update)
{
    int ret = 0;

    mutex_lock(&__health_check_lock);

    if (!__health_check_wq) {
        ret = -ENOENT;
        goto unlock;
    }

    ret = __sx_health_update_tg_locked(dev_id, hw_trap_group, is_add, is_wjh_rdq_update);

unlock:
    mutex_unlock(&__health_check_lock);
    return ret;
}

static int __sx_health_update_sampling_params(u8 dev_id, uint32_t check_interval, uint32_t alert_threshold)
{
    struct sx_health_dev_info *info = NULL;

    info = __info_find(dev_id);
    if (!info) {
        return -ENODEV;
    }

    mutex_lock(&info->lock);

    info->config.periodic_time = check_interval;
    info->config.failures_num = alert_threshold;
    info->config.sdq.max_iter_allowed = __sx_sdq_calc_num_of_check_iter(info->config.periodic_time);

    mutex_unlock(&info->lock);
    return 0;
}

int sx_health_check_dev_init(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);
    int             ret = 0;

    ret = sx_bitmap_init(&priv->debug_trigger_state.sdq_bitmap, NUMBER_OF_SDQS);
    if (ret) {
        printk(KERN_ERR "Health check: Failed to initialize SDQs debug trigger bitmap, aborting.\n");
        goto out;
    }

    ret = sx_bitmap_init(&priv->debug_trigger_state.rdq_bitmap, NUMBER_OF_RDQS);
    if (ret) {
        printk(KERN_ERR "Health check: Failed to initialize RDQs debug trigger bitmap, aborting.\n");
        goto out;
    }
    ret = sx_bitmap_init(&priv->operational_state.sdq_bitmap, NUMBER_OF_SDQS);
    if (ret) {
        printk(KERN_ERR "Health check: Failed to initialize operational SDQs debug trigger bitmap, aborting.\n");
        goto out;
    }

    ret = sx_bitmap_init(&priv->operational_state.rdq_bitmap, NUMBER_OF_RDQS);
    if (ret) {
        printk(KERN_ERR "Health check: Failed to initialize operational SDQs debug trigger bitmap, aborting.\n");
        goto out;
    }

    priv->operational_state.catas = false;
    priv->operational_state.cmd_ifc = false;
    priv->debug_trigger_state.cmd_ifc = false;
    priv->debug_trigger_state.catas = false;

out:
    return ret;
}

void sx_health_check_dev_deinit(struct sx_dev *dev)
{
    bool cancel_workqueue_monitor = false;

    mutex_lock(&__health_check_lock);

    if (!__health_check_wq) { /* trying to delete a device while feature is disabled ... */
        goto unlock;
    }

    __sx_health_delete_device(dev->device_id);

    /* if no more devices requires health check monitor, delete __kernel_workqueue_monitor_dwork */
    if (list_empty(&__dev_info_list)) {
        cancel_workqueue_monitor = true;
    }

unlock:
    mutex_unlock(&__health_check_lock);

    if (cancel_workqueue_monitor) {
        cancel_delayed_work_sync(&__kernel_workqueue_monitor_dwork);
    }
}

int sx_health_check_init(void)
{
    int err = 0;

    printk(KERN_INFO "Health-Check: initialization\n");

    mutex_lock(&__health_check_lock);
    if (__health_check_wq) {
        err = -EEXIST;
        goto out;
    }

    __health_check_wq = create_singlethread_workqueue("sx_health_check");
    if (!__health_check_wq) {
        err = -ENOMEM;
        goto out;
    }
    /* Create the sysfs of the running counter under sys/module/sx_core/health_check_running_counter */
    err = sysfs_create_file(&(THIS_MODULE->mkobj.kobj), &(__health_check_running_counter_attr.attr));

    if (err) {
        goto out;
    }
    INIT_DELAYED_WORK(&__health_check_ts_work, __sx_health_check_update_timestamp);
    INIT_DELAYED_WORK(&__kernel_workqueue_monitor_dwork,  __sx_health_kernel_workqueue_monitor);

    queue_delayed_work(__health_check_wq, &__health_check_ts_work, 0); /* now */
out:
    mutex_unlock(&__health_check_lock);
    return err;
}

int sx_health_check_deinit(void)
{
    struct workqueue_struct *hcwq = NULL;
    int                      err = 0;

    printk(KERN_INFO "Health-Check: cleanup\n");

    mutex_lock(&__health_check_lock);

    if (!__health_check_wq) {
        printk(KERN_ERR "health check has not been started\n");
        err = -ENOENT;
        goto out;
    }

    if (!list_empty(&__dev_info_list)) {
        printk(KERN_ERR "devices are still being monitored\n");
        err = -EBUSY;
        goto out;
    }

    hcwq = __health_check_wq; /* save a temporary copy */
    __health_check_wq = NULL; /* tell everyone that feature is now disabled! */

    sysfs_remove_file(&(THIS_MODULE->mkobj.kobj), &(__health_check_running_counter_attr.attr));

out:
    mutex_unlock(&__health_check_lock);

    if (hcwq) {
        cancel_delayed_work_sync(&__health_check_ts_work);
        destroy_workqueue(hcwq);
    }

    return err;
}

int sx_health_check_configure(ku_dbg_health_check_params_t *params)
{
    int err = 0;

    /* the order of locking must be  (from out side to inside)
     * 1)__set_monitor_rdq_lock
     * 2)__health_check_lock
     * 3)info->lock
     * */
    if (SXD_HEALTH_FATAL_FAILURE_ENABLE_E == params->sxd_health_fatal_failure_detect_cmd) {
        sx_set_monitor_rdq_lock();
    }
    mutex_lock(&__health_check_lock);

    if (!__health_check_wq) {
        printk(KERN_ERR "Health-Check: feature is disabled\n");
        err = -ENOENT;
        goto unlock;
    }

    switch (params->sxd_health_fatal_failure_detect_cmd) {
    case SXD_HEALTH_FATAL_FAILURE_ENABLE_E:
        printk(KERN_INFO "Health-Check: Enable device %u\n", params->dev_id);
        err = __sx_health_add_device(params->dev_id,
                                     params->params.sampling_params.check_interval,
                                     params->params.sampling_params.alert_threshold,
                                     params->params.sampling_params.hw_groups_curr_status);
        break;

    case SXD_HEALTH_FATAL_FAILURE_DISABLE_E:
        printk(KERN_INFO "Health-Check: Disable device %u\n", params->dev_id);
        __sx_health_delete_device(params->dev_id);
        break;

    case SXD_HEALTH_FATAL_FAILURE_ADD_TRAP_GROUP_E:
        printk(KERN_INFO "Health-Check: Add trap-group %d to device %u\n",
               params->params.tg_params.hw_trap_group,
               params->dev_id);
        err = __sx_health_update_tg_locked(params->dev_id,
                                           params->params.tg_params.hw_trap_group,
                                           true,
                                           false);
        break;

    case SXD_HEALTH_FATAL_FAILURE_DELETE_TRAP_GROUP_E:
        printk(KERN_INFO "Health-Check: Delete trap-group %d from device %u\n",
               params->params.tg_params.hw_trap_group,
               params->dev_id);
        err = __sx_health_update_tg_locked(params->dev_id,
                                           params->params.tg_params.hw_trap_group,
                                           false,
                                           false);
        break;

    case SXD_HEALTH_FATAL_FAILURE_UPDATE_SAMPLE_PARAMS_E:
        printk(KERN_INFO "Health-Check: Update sampling parameters for device %u (interval=%u, threshold=%u)\n",
               params->dev_id,
               params->params.sampling_params.check_interval,
               params->params.sampling_params.alert_threshold);
        err = __sx_health_update_sampling_params(params->dev_id,
                                                 params->params.sampling_params.check_interval,
                                                 params->params.sampling_params.alert_threshold);
        break;

    case SXD_HEALTH_FATAL_FAILURE_ADD_SDK_THREAD_FAILURE_E:
        printk(KERN_INFO "Health-Check: Add SDK thread %s failure for device %u \n",
               thread_id_str(params->params.sdk_threads_info.sdk_thread_id),
               params->dev_id);
        err = __sx_health_add_sdk_thread_failure(params->dev_id,
                                                 &params->params.sdk_threads_info);
        break;

    default:
        break;
    }

unlock:
    mutex_unlock(&__health_check_lock);
    if (SXD_HEALTH_FATAL_FAILURE_ENABLE_E == params->sxd_health_fatal_failure_detect_cmd) {
        sx_set_monitor_rdq_unlock();
    }
    if (err) {
        printk(KERN_ERR "Health-Check: Operation failed (err=%d)\n", err);
    }

    return err;
}

void sx_health_check_report_dq_ok(struct sx_dev *dev, bool is_send, int dqn)
{
    struct sx_priv *priv = sx_priv(dev);

    if (is_send) {
        if (!sx_bitmap_test(&priv->debug_trigger_state.sdq_bitmap, dqn)) { /* debug trigger not set */
            sx_bitmap_set(&priv->operational_state.sdq_bitmap, dqn);
        }
    } else {
        if (!sx_bitmap_test(&priv->debug_trigger_state.rdq_bitmap, dqn)) { /* debug trigger not set */
            sx_bitmap_set(&priv->operational_state.rdq_bitmap, dqn);
        }
    }
}

static ssize_t __health_check_running_cntr_cb(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int len = 0;

    len = sprintf(buf, "%llu\n", __health_check_ts);
    return len;
}

static void __dump_bitmap(struct seq_file *m, void *v, void *context, struct sx_bitmap *bitmap)
{
    u32  i, max;
    bool found_bit;

    seq_printf(m, "\t\t");

    max = sx_bitmap_num_bits(bitmap);
    found_bit = false;
    for (i = 0; i < max; i++) {
        if (sx_bitmap_test(bitmap, i)) {
            found_bit = true;
            seq_printf(m, "%u, ", i);
        }
    }

    if (!found_bit) {
        seq_printf(m, "None");
    }

    seq_printf(m, "\n");
}

static void __dump_failure(struct seq_file *m, void *v, void *context, struct issue_info *failure)
{
    const char *cause = NULL;
    char        extra_info[sizeof(failure->cause_data)] = { 0 };

    switch (failure->cause) {
    case SXD_HEALTH_CAUSE_CATAS:
        cause = "Catas";
        if (failure->has_cause_data) {
            snprintf(extra_info, sizeof(extra_info), "Catas buf: 0x%x", failure->cause_data.catas_data.catas_buf);
        }
        break;

    case SXD_HEALTH_CAUSE_GO_BIT:
        cause = "Go bit";
        if (failure->has_cause_data) {
            snprintf(extra_info, sizeof(extra_info), "Cmd_ifc sent via health check: %s",
                     (failure->cause_data.cmd_ifc_data.is_cmd_ifc_sent_from_health) ? "Yes" : "No");
        }
        break;

    case SXD_HEALTH_CAUSE_RDQ:
        cause = "RDQ";
        if (failure->has_cause_data) {
            snprintf(extra_info, sizeof(extra_info), "RDQ#: %d", failure->cause_data.dq_data.dqn);
        }
        break;

    case SXD_HEALTH_CAUSE_SDQ:
        cause = "SDQ";
        if (failure->has_cause_data) {
            snprintf(extra_info, sizeof(extra_info), "SDQ#: %d", failure->cause_data.dq_data.dqn);
        }
        break;

    case SXD_HEALTH_CAUSE_SDK_THREADS:
        cause = thread_id_str(failure->cause_data.sdk_thread_data.sdk_thread_id);
        if (failure->has_cause_data) {
            snprintf(extra_info, sizeof(extra_info), "SDK Thread info massage #: %s",
                     failure->cause_data.sdk_thread_data.msg_error);
        }
        break;

    case SXD_HEALTH_CAUSE_KERNEL_THREADS:
        cause = "Kernel work queue thread ";
        if (failure->has_cause_data) {
            snprintf(extra_info, sizeof(extra_info), "Kernel Thread info massage #: %s",
                     failure->cause_data.kernel_thread_data.name);
        }
        break;

    case SXD_HEALTH_CAUSE_SDK_WD:
        cause = "SDK WD combination of failures";
        break;

    case SXD_HEALTH_CAUSE_FW_HETT:
        cause = "FW HETT";
        break;

    case SXD_HEALTH_CAUSE_GENERIC_E:
        cause = "Generic error";
        strncpy(extra_info, failure->cause_data.external_data.err_msg, sizeof(extra_info) - 1);
        break;

    default:
        cause = "Other";
        break;
    }
    ;

    seq_printf(m, "\t\tCause: %s, Time (Seconds ago): %u",
               cause,
               jiffies_to_msecs(jiffies - failure->jiffies) / 1000);
    if (extra_info[0]) {
        seq_printf(m, ", %s", extra_info);
    }

    seq_printf(m, "\n");
}

static void __dump_info(struct seq_file *m, void *v, void *context, struct sx_health_dev_info *info)
{
    struct issue_info                   *failure = NULL;
    struct sx_priv                      *priv;
    struct health_check_kernel_thread_t *iter_thread = NULL;

    priv = sx_priv(info->dev);

    mutex_lock(&info->lock);
    seq_printf(m, "Device ID: %u\n", info->dev->device_id);
    seq_printf(m, "\tCheck Interval: %u Milliseconds\n", (info->config.periodic_time * 1000));
    seq_printf(m, "\tAlert Threshold: %u failures\n", info->config.failures_num);
    seq_printf(m, "\tFailures detected: %u\n", info->failures_detected);
    seq_printf(m, "\tWarnings detected: %u\n", info->warnings_detected);
    seq_printf(m, "\tFatal detected : %s\n", (info->fatal_cause != SXD_HEALTH_CAUSE_NONE) ? "Yes" : "No");
    if ((info->fatal_cause == SXD_HEALTH_CAUSE_FW_HETT) || (info->fatal_cause == SXD_HEALTH_CAUSE_CATAS)) {
        seq_printf(m, "\tFatal cause %s\n", (info->fatal_cause == SXD_HEALTH_CAUSE_CATAS)
                   ? "SXD_HEALTH_CAUSE_CATAS" : "SXD_HEALTH_CAUSE_FW_HETT");
    }
    seq_printf(m, "\tMonitored SDQs:\n");
    __dump_bitmap(m, v, context, &info->config.sdq.sdq_bitmap);
    seq_printf(m, "\t\tOperational SDQs:\n");
    __dump_bitmap(m, v, context, &priv->operational_state.sdq_bitmap);
    seq_printf(m, "\t\tTrigger state SDQs:\n");
    __dump_bitmap(m, v, context, &priv->debug_trigger_state.sdq_bitmap);
    seq_printf(m, "\t\tMax_iter_allowed is %u:\n", info->config.sdq.max_iter_allowed);
    seq_printf(m, "\t\tnum_of_check_iter is %llu:\n", info->config.sdq.num_of_check_iter);
    seq_printf(m, "\n");

    seq_printf(m, "\tMonitored RDQs:\n");
    seq_printf(m, "\t\tALL RDQs in switch:\n");
    __dump_bitmap(m, v, context, &info->config.rdq_bitmap);
    seq_printf(m, "\t\tIgnore RDQs:\n");
    __dump_bitmap(m, v, context, &info->config.ignore_rdq_bitmap);
    seq_printf(m, "\t\tMonitored last RDQs:\n");
    __dump_bitmap(m, v, context, &info->config.last_rdq_bitmap);
    seq_printf(m, "\t\tOperational RDQs:\n");
    __dump_bitmap(m, v, context, &priv->operational_state.rdq_bitmap);
    seq_printf(m, "\t\tTrigger state RDQs:\n");
    __dump_bitmap(m, v, context, &priv->debug_trigger_state.rdq_bitmap);
    seq_printf(m, "\n");

    seq_printf(m, "\tMonitored Cmd_ifc:\n");
    seq_printf(m, "\t\tNumber of cmd_ifc packet received is :%llu\n", priv->cmd_ifc_num_of_pck_received);
    seq_printf(m, "\t\tCmd ifc sent via the Health check: %s\n",
               (info->config.cmd_ifc.is_last_pkt_sent_via_health) ? "Yes" : "No");
    seq_printf(m, "\t\tCmd ifc last_cmd_ifc_counter: %llu\n", info->config.cmd_ifc.last_cmd_ifc_counter);
    seq_printf(m, "\n");

    seq_printf(m, "\tMonitored Kernel threads:\n");
    seq_printf(m, "\t\tNumber of kernel threads under monitor: %u and the wq names are:\n",
               __kernel_thread_monitor_cnt);
    list_for_each_entry(iter_thread, &__kernel_thread_list, list) {
        seq_printf(m, "\t\t\t%s \n", iter_thread->name);
    }
    seq_printf(m, "\t\tTrigger state Kernel wq threads active: %s\n",
               (__health_check_wq_threads_trigger ? "Yes" : "No"));
    if (__health_check_wq_threads_trigger) {
        seq_printf(m, "\t\tTrigger state Kernel wq threads name: %s\n", __wq_thread_name_trigger);
    }
    seq_printf(m, "\n");

    seq_printf(m, "\tFailures Information:\n");

    list_for_each_entry(failure, &info->failure_ts_list, list) {
        __dump_failure(m, v, context, failure);
    }
    seq_printf(m, "\tWarning Information:\n");

    list_for_each_entry(failure, &info->warning_ts_list, list) {
        __dump_failure(m, v, context, failure);
    }

    mutex_unlock(&info->lock);
}

int sx_health_check_dump(struct seq_file *m, void *v, void *context)
{
    struct sx_health_dev_info *info;

    sx_dbg_dump_print_table_header(m, "Health-Check DUMP");

    mutex_lock(&__health_check_lock);

    list_for_each_entry(info, &__dev_info_list, dev_list) {
        __dump_info(m, v, context, info);
    }

    mutex_unlock(&__health_check_lock);
    return 0;
}

void sx_health_check_set_debug_trigger(struct sx_health_check_trigger_params *params)
{
    struct sx_health_dev_info           *info;
    struct sx_priv                      *priv = NULL;
    bool                                 is_wq_thread_name_found = false;
    struct health_check_kernel_thread_t *iter_thread = NULL;

    mutex_lock(&__health_check_lock);

    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_SYSFS) {
        printk(KERN_NOTICE "Health-Check: Trigger SYSFS failure\n");
        __health_check_ts_trigger = true;
        goto out;
    }

    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_ADD_DEV) {
        printk(KERN_NOTICE "Health-Check: Trigger Add-Device %u\n", params->dev_id);
        __sx_health_add_device(params->dev_id, 10, 3, 0); /*todo add to user params the rdq bitmap status */
        goto out;
    }

    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_DEL_DEV) {
        printk(KERN_NOTICE "Health-Check: Trigger Del-Device %u\n", params->dev_id);
        __sx_health_delete_device(params->dev_id);
        goto out;
    }

    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_KERNEL_THREADS) {
        mutex_lock(&__kthreads_monitor_lock);
        list_for_each_entry(iter_thread, &__kernel_thread_list, list) {
            if (strcmp(params->params.kthread_params.name, iter_thread->name) == 0) {
                is_wq_thread_name_found = true;
                printk(KERN_NOTICE "Health-Check: Trigger kernel thread %s failure \n",
                       params->params.kthread_params.name);
                __health_check_wq_threads_trigger = true;
                strcpy(__wq_thread_name_trigger, params->params.kthread_params.name);
                break;
            }
        }
        mutex_unlock(&__kthreads_monitor_lock);

        if (is_wq_thread_name_found == false) {
            printk(KERN_ERR "Health-Check: Trigger kernel thread %s not "
                   "part of the existing in the list of monitored wq kernel threads \n",
                   params->params.kthread_params.name);
        }
        goto out;
    }

    info = __info_find(params->dev_id);

    if (!info) {
        printk(KERN_ERR "Health-Check: device %u is not monitored\n", params->dev_id);
        goto out;
    }

    priv = sx_priv(info->dev);

    mutex_lock(&info->lock);
    switch (params->op) {
    case SX_HEALTH_CHECK_TRIGGER_OP_CATAS:
        printk(KERN_NOTICE "Health-Check: Trigger CATAS failure on device %u\n", params->dev_id);
        priv->debug_trigger_state.catas = true;
        break;

    case SX_HEALTH_CHECK_TRIGGER_OP_CMD_IFC:
        printk(KERN_NOTICE "Health-Check: Trigger CMD_IFC failure on device %u\n", params->dev_id);
        priv->debug_trigger_state.cmd_ifc = true;
        break;

    case SX_HEALTH_CHECK_TRIGGER_OP_SDQ:
        printk(KERN_NOTICE "Health-Check: Trigger SDQ %d failure on device %u\n",
               params->params.dq_params.dqn, params->dev_id);
        sx_bitmap_set(&priv->debug_trigger_state.sdq_bitmap, params->params.dq_params.dqn);
        break;

    case SX_HEALTH_CHECK_TRIGGER_OP_RDQ:
        printk(KERN_NOTICE "Health-Check: Trigger RDQ %d failure on device %u\n",
               params->params.dq_params.dqn, params->dev_id);
        sx_bitmap_set(&priv->debug_trigger_state.rdq_bitmap, params->params.dq_params.dqn);
        break;

    default:
        break;
    }
    mutex_unlock(&info->lock);

out:
    mutex_unlock(&__health_check_lock);
}


static void __external_report_work(struct work_struct *work)
{
    struct external_cause_work *ecw = container_of(work, struct external_cause_work, w);
    struct sx_health_dev_info  *info = NULL;

    mutex_lock(&__health_check_lock);

    if (ecw->dev_id == DEV_ID_ALL) {
        __add_issue_to_all_devices(ecw->issue_severity, SXD_HEALTH_CAUSE_GENERIC_E, &ecw->cause_data);
    } else {
        info = __info_find(ecw->dev_id);
        if (info) {
            mutex_lock(&info->lock);
            __add_issue(info, ecw->issue_severity, SXD_HEALTH_CAUSE_GENERIC_E, &ecw->cause_data);
            mutex_unlock(&info->lock);
        }
    }

    mutex_unlock(&__health_check_lock);
    kfree(ecw);
}

void sx_health_external_report(u8 dev_id, u32 issue_severity, const char *error_msg)
{
    struct external_cause_work *ecw;

    ecw = kzalloc(sizeof(struct external_cause_work), GFP_ATOMIC);
    if (!ecw) {
        printk(KERN_ERR "health report allocation failed: dev_id [%u], severity [%u], error [%s]\n",
               dev_id,
               issue_severity,
               ((error_msg) ? error_msg : "N/A"));
        return;
    }

    INIT_WORK(&ecw->w, __external_report_work);
    ecw->dev_id = dev_id;
    ecw->issue_severity = issue_severity;
    if (error_msg) {
        strncpy(ecw->cause_data.external_data.err_msg, error_msg, sizeof(ecw->cause_data.external_data.err_msg) - 1);
    }

    queue_work(__health_check_wq, &ecw->w);
}

void sx_health_external_report_all(u32 issue_severity, const char *error_msg)
{
    sx_health_external_report(DEV_ID_ALL, issue_severity, error_msg);
}
