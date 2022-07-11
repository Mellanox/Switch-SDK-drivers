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

#include <linux/workqueue.h>
#include <linux/list.h>
#include <linux/seq_file.h>
#include <linux/module.h>

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


struct catas_cause_data {
    u32 catas_buf;
};

struct dq_cause_data {
    int dqn;
};

struct cmd_ifc_cause_data {
    bool is_cmd_ifc_sent_from_health;
};


struct sx_cmd_ifc {
    bool  last_cmd_ifc_sent_via_health;
    u64   last_cmd_ifc_counter;           /*last number of cmd that sent */
    u64   num_of_check_iter;           /*count number of check iteration that made*/
    u32   max_iter_allowed;           /*maximum time that that go bit should ACK for cmd_ifc ,GO_BIT_TIMEOUT_MSECS/periodic_time +1 */
    void *mailbox_p; /* mailbox function as opaque (void*) */
    void *cmd_ctx;     /* context function as opaque (void*) */
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
    struct delayed_work cmd_ifc_check_dwork;
    struct list_head    dev_list;
    u32 __iomem        *catas_iomap;
    struct mutex        lock;

    /* following fields must be accessed within device information lock */
    struct list_head              failure_ts_list;
    u32                           failures_detected;
    sxd_health_cause_t            fatal_cause;
    bool                          health_check_first_itr_skip_checks_func;
    struct sx_health_check_config config;
    struct completion             cmd_ifc_completion;
    bool                          disabled;
};

union sdk_health_cause_data {
    struct catas_cause_data   catas_data; /* catas event */
    struct dq_cause_data      dq_data; /* for SDQ/RDQ errors */
    struct cmd_ifc_cause_data cmd_ifc_data;    /* for cmd_ifc errors */
};

struct failure_info {
    unsigned long               jiffies; /* time when the failure happened */
    struct list_head            list;
    sxd_health_cause_t          cause;
    bool                        has_cause_data;
    union sdk_health_cause_data cause_data;
};

/*static struct kobject* __running_counter_kobj_s_p = NULL; */

static ssize_t __health_check_running_cntr_cb(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static struct kobj_attribute __health_check_running_counter_attr = __ATTR(health_check_running_counter,
                                                                          S_IRUGO,
                                                                          __health_check_running_cntr_cb,
                                                                          NULL);

static struct workqueue_struct *__health_check_wq = NULL;
static struct delayed_work      __health_check_ts_work;
static uint64_t                 __health_check_ts = 0;
static bool                     __health_check_ts_trigger = false;
static LIST_HEAD(__dev_info_list);
static DEFINE_MUTEX(__health_check_lock);

#define START_HETT_SESSION 0
#define STOP_HETT_SEASSON  1

/* must be called within the device information lock */
static void __add_failure(struct sx_health_dev_info   *info,
                          sxd_health_cause_t           cause,
                          union sdk_health_cause_data *cause_data,
                          bool                         is_fatal)
{
    struct failure_info *iter = NULL, *tmp = NULL, *new_failure = NULL;
    unsigned long        now = jiffies;

    /* check if there are old failures that we can remove from the list */
    list_for_each_entry_safe(iter, tmp, &info->failure_ts_list, list) {
        if (time_after(now, iter->jiffies + info->config.failures_num * 10 * HZ)) {
            info->failures_detected--;
            list_del(&iter->list);
            if (new_failure == NULL) {
                new_failure = iter; /* instead of allocating a new one, use an old one */
            } else {
                kfree(iter);
            }
        } else {
            break; /* failures are in chronological order, if we're here we can stop the iteration */
        }
    }

    if (is_fatal) {
        info->fatal_cause = cause;
    }

    if (new_failure == NULL) { /* we have to allocate a new one */
        new_failure = kzalloc(sizeof(struct failure_info), GFP_KERNEL);

        if (new_failure == NULL) {
            printk(KERN_ERR "couldn't allocate device %u health-check failure\n", info->dev->device_id);
            return;
        }
    } else {
        memset(new_failure, 0, sizeof(struct failure_info));
    }

    INIT_LIST_HEAD(&new_failure->list);
    new_failure->jiffies = now;
    new_failure->cause = cause;
    if (cause_data) {
        new_failure->has_cause_data = true;
        memcpy(&new_failure->cause_data, cause_data, sizeof(new_failure->cause_data));
    }
    list_add_tail(&new_failure->list, &info->failure_ts_list);
    info->failures_detected++;
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

    if (catas_data.catas_data.catas_buf) {
        __add_failure(info, SXD_HEALTH_CAUSE_CATAS, &catas_data, true);
    }
}

/* must be called within the device information lock */
/* this fun will be called only if in the last iteration we got ACK or
 *  reporting on failure on cmd_ifc */
static int __start_cmd_ifc_for_next_cycle(struct sx_health_dev_info *info)
{
    struct sx_priv *priv = sx_priv(info->dev);
    int             err = 0;


    info->config.cmd_ifc.cmd_ctx = NULL;
    info->config.cmd_ifc.mailbox_p = NULL;

    /* cmd_ifc is in the pipe already no need to send new cmd_ifc*/
    if (sx_cmd_check_go_bit(info->dev, info->dev->device_id)) {
        /* save the last received packet to compare in the next check cmd_ifc cycle*/
        info->config.cmd_ifc.last_cmd_ifc_counter = priv->cmd_ifc_num_of_pck_received;
        info->config.cmd_ifc.last_cmd_ifc_sent_via_health = false;
        goto out;
    }

    err = sx_cmd_prepare(info->dev, SX_CMD_QUERY_FW_HCR1, &info->config.cmd_ifc.cmd_ctx);
    if (err) { /* it's not an error, just indication that someone is calling CMD-IFC.
                *  we'll wait for next cycle */
        /* save the last received packet to compare in the next check cmd_ifc cycle*/
        info->config.cmd_ifc.last_cmd_ifc_counter = priv->cmd_ifc_num_of_pck_received;
        info->config.cmd_ifc.last_cmd_ifc_sent_via_health = false;
        return 0;
    }

    /* save the number of cmd_ifc that received before sending new one */
    info->config.cmd_ifc.last_cmd_ifc_counter = priv->cmd_ifc_num_of_pck_received;
    info->config.cmd_ifc.last_cmd_ifc_sent_via_health = true;
    err = sx_cmd_health_check_send(info->dev, &info->config.cmd_ifc.mailbox_p, info->config.cmd_ifc.cmd_ctx);
    if (err) {
        printk(KERN_ERR "Health check:Failed to send cmd_ifc \n");
        sx_cmd_health_check_release(info->dev, info->config.cmd_ifc.mailbox_p, info->config.cmd_ifc.cmd_ctx);
        info->config.cmd_ifc.last_cmd_ifc_sent_via_health = false;

        goto out;
    }

    /* start tracking if go bit goes down due to our sending */
    queue_delayed_work(__health_check_wq, &info->cmd_ifc_check_dwork, 0); /* now */
out:
    return err;
}

/*
 * This function checking if this iteration failure is under the time frame that allowed for cmd_ifc
 *  to wait for response from HW or not, in case its not allowed it will report on failure
 *  and set the iteration number to 0 for starting new season of checking , if its also cmd ifc that sent from the health
 *  Mechanism it will stop the cmd_ifc response thread and release hcr and mailbox*/

static void __check_and_report_cmd_ifc_failure(struct sx_health_dev_info *info,
                                               bool                       last_cmd_ifc_sent_via_health_check)
{
    union sdk_health_cause_data cmd_ifc_data;

    memset(&cmd_ifc_data, 0, sizeof(cmd_ifc_data));

    /*failure - exceed the time frame  */
    if (info->config.cmd_ifc.num_of_check_iter >= info->config.cmd_ifc.max_iter_allowed) {
        /* failure and health check sent the last cmd_ifc packet need to cancel the work and release*/
        if (last_cmd_ifc_sent_via_health_check) {
            /* stop the 100 millisecond monitor thread that check if cmd_ifc got hit */
            cancel_delayed_work_sync(&info->cmd_ifc_check_dwork);
            /* free hcr mutex and mailbox and then free the cmd semaphore*/
            sx_cmd_health_check_release(info->dev, info->config.cmd_ifc.mailbox_p, info->config.cmd_ifc.cmd_ctx);

            cmd_ifc_data.cmd_ifc_data.is_cmd_ifc_sent_from_health = last_cmd_ifc_sent_via_health_check;
        }

        __add_failure(info, SXD_HEALTH_CAUSE_GO_BIT, &cmd_ifc_data, false);
        /* cleaning params to start point
         * note: no touching last_cmd_ifc_sent_via_health because we want to keep monitor
         * if we will get hit via the relevant thread*/
        info->config.cmd_ifc.num_of_check_iter = 0;
        cmd_ifc_data.cmd_ifc_data.is_cmd_ifc_sent_from_health = false;
    }
}

/* must be called within the device information lock */
static void __check_cmd_ifc_from_last_cycle(struct sx_health_dev_info *info)
{
    struct sx_priv *priv = sx_priv(info->dev);
    bool            cntr_advanced = (info->config.cmd_ifc.last_cmd_ifc_counter
                                     < priv->cmd_ifc_num_of_pck_received);


    info->config.cmd_ifc.num_of_check_iter++;

    /* update if debug trigger set from external user*/
    sx_health_check_report_cmd_ifc_ok(info->dev);

    /* cmd_ifc got ACK and don'nt block by debug trigger */
    if (cntr_advanced && priv->operational_state.cmd_ifc) {
        /* prepare for next health check cmd_ifc cycle */
        info->config.cmd_ifc.num_of_check_iter = 0;
    }
    /* cmd_ifc not got ACK  */
    else {
        __check_and_report_cmd_ifc_failure(info, info->config.cmd_ifc.last_cmd_ifc_sent_via_health);
    }
}

static void __check_and_report_sdq_failure(struct sx_health_dev_info *info, u32 sub_bitmap_res)
{
    union sdk_health_cause_data dq_data;

    /*failure - exceed the time frame  */
    if (info->config.sdq.num_of_check_iter >= info->config.sdq.max_iter_allowed) {
        dq_data.dq_data.dqn = sub_bitmap_res;
        printk(KERN_ERR PFX "Did not receive completion for SDQ dqn (%u) \n",
               sub_bitmap_res);
        __add_failure(info, SXD_HEALTH_CAUSE_SDQ, &dq_data, false);
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
            ret = emad_build(dev->device_id, ppad, sizeof(ppad), &skb,
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
                    kfree_skb(skb);
                    return -ENOMEM;
                }

                skb_reserve(new_skb, ISX_HDR_SIZE);
                memcpy(skb_put(new_skb, len), skb->data, len);
                kfree_skb(skb);

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
    reg_hett.hett_reg.trap_group_bitmap.lo = (u32)(info->config.last_rdq_bitmap.table[0] & 0xffffffff);
    reg_hett.hett_reg.trap_group_bitmap.hi = (u32)((info->config.last_rdq_bitmap.table[0] >> 32) & 0xffffffff);
    err = __write_hett(&reg_hett, info->dev, "send trap group bitmap");

    if (err) {
        /* fatal failure will stop the health mechanism */
        __add_failure(info, SXD_HEALTH_CAUSE_FW_HETT, NULL, true);
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
        __add_failure(info, SXD_HEALTH_CAUSE_RDQ, &dq_data, false);
    }
    sx_bitmap_clear_all(&info->config.last_rdq_bitmap);
}
/* must be called within the device information lock
 * cmd_ifc thread that sample if got ACK from device */
static void __sx_health_check_cmd_ifc_response(struct work_struct *work)
{
    struct sx_health_dev_info *info = container_of(work, struct sx_health_dev_info, cmd_ifc_check_dwork.work);
    struct sx_priv            *priv = sx_priv(info->dev);
    bool                       go_bit_up = sx_cmd_check_go_bit(info->dev, info->dev->device_id);


    if (!go_bit_up) {
        /* we got ACK from the device */
        priv->cmd_ifc_num_of_pck_received++;
        info->config.cmd_ifc.last_cmd_ifc_sent_via_health = false;

        /* unlock mutex ,free mailbox ,release cmd semaphore (mailbox_p touched only
         *  by the cmd_ifc health send function so there is no race issue)  */
        sx_cmd_health_check_release(info->dev, info->config.cmd_ifc.mailbox_p,
                                    info->config.cmd_ifc.cmd_ctx);
        if (info->disabled) {
            complete(&info->cmd_ifc_completion);
        }
    } else {
        queue_delayed_work(__health_check_wq, &info->cmd_ifc_check_dwork, (HZ / 10));
    }
}

static void __sx_health_check_cycle(struct work_struct *work)
{
    struct sx_health_dev_info *info = container_of(work, struct sx_health_dev_info, main_health_check_dwork.work);
    int                        err = 0;


    mutex_lock(&info->lock);
    /* If user try to disabled the health check stop the main health check thread */
    if (info->disabled) {
        goto out;
    }

    /* this is an immediate check, no need for 2-step check */
    __check_catas(info);

    if (info->health_check_first_itr_skip_checks_func) {
        info->health_check_first_itr_skip_checks_func = false;
        goto health_monitor;
    }
    __check_cmd_ifc_from_last_cycle(info);
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

    /* NO MATTER WHAT, CMD-IFC CHECK MUST BE THE LAST OPERATION HERE AS IT
     * ACQUIRES THE CMD-IFC SEMAPHORE THAT IS ALSO NEEDED BY RDQ CHECK (HETT)*/
    /* start cmd_ifc in case the last cmd_ifc check packet wasn't found in the pipe  */
    if (info->config.cmd_ifc.num_of_check_iter == 0) {
        err = __start_cmd_ifc_for_next_cycle(info);
        if (err) {
            printk(KERN_ERR "Health check:Failed to start cmd_ifc \n");
            goto out;
        }
    }

    if (info->fatal_cause != SXD_HEALTH_CAUSE_NONE) {
        /* Fatal failure detect: send SDK health event and stop monitoring this device */
        sx_send_health_event(info->dev->device_id, info->fatal_cause);
        printk(KERN_ERR "device %u is FATAL and is not monitored anymore!\n", info->dev->device_id);
    } else {
        /* Too many failures: send SDK health event with SXD_HEALTH_CAUSE_SDK_WD cause */
        if (info->failures_detected >= info->config.failures_num) {
            sx_send_health_event(info->dev->device_id, SXD_HEALTH_CAUSE_SDK_WD);
            printk(KERN_ERR "device %u is notice fatal failure detection !\n", info->dev->device_id);
        }
        queue_delayed_work(__health_check_wq, &info->main_health_check_dwork, info->config.periodic_time * HZ);
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
    INIT_DELAYED_WORK(&info->cmd_ifc_check_dwork, __sx_health_check_cmd_ifc_response);
    INIT_LIST_HEAD(&info->dev_list);
    INIT_LIST_HEAD(&info->failure_ts_list);
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

    info->config.cmd_ifc.max_iter_allowed = sx_cmd_calc_num_of_check_iter(info->config.periodic_time);

    /* fill the rdq_bitmap with the hw_traps that exist before starting this feature */
    for (dq_id = 0; dq_id < priv->dev_cap.max_num_rdqs; dq_id++) {
        if (test_bit(dq_id, &hw_groups_curr_status)) {
            sx_bitmap_set(&info->config.rdq_bitmap, dq_id);
        }
    }
    /* fill the ignore_bitmap with the WJH hw_traps that exist before starting this feature */
    spin_lock_irqsave(&priv->rdq_table.lock, flags);
    for (dq_id = 0; dq_id < priv->monitor_rdqs_count; dq_id++) {
        sx_bitmap_set(&info->config.ignore_rdq_bitmap, priv->monitor_rdqs_arr[dq_id]);
    }
    spin_unlock_irqrestore(&priv->rdq_table.lock, flags);


    info->health_check_first_itr_skip_checks_func = true;
    list_add_tail(&info->dev_list, &__dev_info_list);
    *ret_info = info;
out:
    return err;
}

/* must be called within the health-check lock */
static void __info_dealloc(struct sx_health_dev_info *info)
{
    struct failure_info *iter = NULL, *tmp = NULL;

    printk(KERN_INFO "Health-Check: disabling monitoring on device %d\n", info->dev->device_id);

    mutex_lock(&info->lock);

    init_completion(&info->cmd_ifc_completion);
    info->disabled = true;

    cancel_delayed_work_sync(&info->main_health_check_dwork);

    if (info->config.cmd_ifc.last_cmd_ifc_sent_via_health) {
        if (!wait_for_completion_timeout(&info->cmd_ifc_completion, msecs_to_jiffies(10000))) {
            cancel_delayed_work_sync(&info->cmd_ifc_check_dwork);
            sx_cmd_health_check_release(info->dev, info->config.cmd_ifc.mailbox_p, info->config.cmd_ifc.cmd_ctx);
        }
    }

    list_del(&info->dev_list);

    list_for_each_entry_safe(iter, tmp, &info->failure_ts_list, list) {
        list_del(&iter->list);
        kfree(iter);
    }

    iounmap(info->catas_iomap);
    info->catas_iomap = NULL;
    mutex_unlock(&info->lock);

    kfree(info);
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

static int __sx_health_add_device(u8 dev_id, u32 check_interval, u32 alert_threshold, u64 hw_groups_curr_status)
{
    struct sx_health_dev_info *info = NULL;
    int                        err = 0;

    info = __info_find(dev_id);
    if (!info) {
        err = __info_alloc(dev_id, check_interval, alert_threshold, hw_groups_curr_status, &info);
    } else {
        err = -EEXIST;
    }

    if (!err) {
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

int sx_health_update_tg(u8 dev_id, int hw_trap_group, bool is_add, bool is_wjh_rdq_update)
{
    struct sx_health_dev_info *info = NULL;

    info = __info_find(dev_id);
    if (!info) {
        return -ENODEV;
    }

    mutex_lock(&info->lock);

    if (is_add) {
        if (is_wjh_rdq_update) {
            sx_bitmap_set(&info->config.ignore_rdq_bitmap, hw_trap_group);
        } else {
            sx_bitmap_set(&info->config.rdq_bitmap, hw_trap_group);
        }
    } else {
        if (is_wjh_rdq_update) {
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
    info->config.cmd_ifc.max_iter_allowed = sx_cmd_calc_num_of_check_iter(info->config.periodic_time);
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
    mutex_lock(&__health_check_lock);
    __sx_health_delete_device(dev->device_id);
    mutex_unlock(&__health_check_lock);
}

int sx_health_check_init(void)
{
    int err = 0;

    printk(KERN_INFO "Health-Check: initialization\n");

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
    queue_delayed_work(__health_check_wq, &__health_check_ts_work, 0); /* now */
out:
    return err;
}

int sx_health_check_deinit(void)
{
    int err = 0;

    printk(KERN_INFO "Health-Check: cleanup\n");

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

    sysfs_remove_file(&(THIS_MODULE->mkobj.kobj), &(__health_check_running_counter_attr.attr));

    cancel_delayed_work_sync(&__health_check_ts_work);
    destroy_workqueue(__health_check_wq);

    __health_check_wq = NULL;

out:
    return err;
}

int sx_health_check_configure(ku_dbg_group_traps_and_sample_params_t *params)
{
    int err = 0;

    mutex_lock(&__health_check_lock);

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
        err = sx_health_update_tg(params->dev_id,
                                  params->params.tg_params.hw_trap_group,
                                  true,
                                  false);
        break;

    case SXD_HEALTH_FATAL_FAILURE_DELETE_TRAP_GROUP_E:
        printk(KERN_INFO "Health-Check: Delete trap-group %d from device %u\n",
               params->params.tg_params.hw_trap_group,
               params->dev_id);
        err = sx_health_update_tg(params->dev_id,
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

    default:
        break;
    }

    mutex_unlock(&__health_check_lock);

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

void sx_health_check_report_cmd_ifc_ok(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);

    if (!priv->debug_trigger_state.cmd_ifc) { /* debug trigger not set */
        priv->operational_state.cmd_ifc = true;
    }
}


static ssize_t __health_check_running_cntr_cb(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int len = 0;

    len = sprintf(buf, "%llu\n", __health_check_ts);
    return len;
}

static void __dump_bitmap(struct seq_file *m, void *v, struct sx_bitmap *bitmap)
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

static void __dump_failure(struct seq_file *m, void *v, struct failure_info *failure)
{
    const char *cause = NULL;
    char        extra_info[64] = { 0 };

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

    case SXD_HEALTH_CAUSE_SDK_WD:
        cause = "SDK WD combination of failures";
        break;

    case SXD_HEALTH_CAUSE_FW_HETT:
        cause = "FW HETT";
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

static void __dump_info(struct seq_file *m, void *v, struct sx_health_dev_info *info)
{
    struct failure_info *failure = NULL;
    struct sx_priv      *priv;

    priv = sx_priv(info->dev);

    mutex_lock(&info->lock);
    seq_printf(m, "Device ID: %u\n", info->dev->device_id);
    seq_printf(m, "\tCheck Interval: %u Milliseconds\n", (info->config.periodic_time * 1000));
    seq_printf(m, "\tAlert Threshold: %u failures\n", info->config.failures_num);
    seq_printf(m, "\tFailures detected: %u\n", info->failures_detected);
    seq_printf(m, "\tFatal detected : %s\n", (info->fatal_cause != SXD_HEALTH_CAUSE_NONE) ? "Yes" : "No");
    if ((info->fatal_cause == SXD_HEALTH_CAUSE_FW_HETT) || (info->fatal_cause == SXD_HEALTH_CAUSE_CATAS)) {
        seq_printf(m, "\tFatal cause %s\n", (info->fatal_cause == SXD_HEALTH_CAUSE_CATAS)
                   ? "SXD_HEALTH_CAUSE_CATAS" : "SXD_HEALTH_CAUSE_FW_HETT");
    }
    seq_printf(m, "\tMonitored SDQs:\n");
    __dump_bitmap(m, v, &info->config.sdq.sdq_bitmap);
    seq_printf(m, "\t\tOperational SDQs:\n");
    __dump_bitmap(m, v, &priv->operational_state.sdq_bitmap);
    seq_printf(m, "\t\tTrigger state SDQs:\n");
    __dump_bitmap(m, v, &priv->debug_trigger_state.sdq_bitmap);
    seq_printf(m, "\t\tMax_iter_allowed is %u:\n", info->config.sdq.max_iter_allowed);
    seq_printf(m, "\t\tnum_of_check_iter is %llu:\n", info->config.sdq.num_of_check_iter);


    seq_printf(m, "\n");


    seq_printf(m, "\tMonitored RDQs INFO:\n");
    seq_printf(m, "\tALL RDQs in switch:\n");
    __dump_bitmap(m, v, &info->config.rdq_bitmap);
    seq_printf(m, "\tIgnore RDQs:\n");
    __dump_bitmap(m, v, &info->config.ignore_rdq_bitmap);
    seq_printf(m, "\t\tMonitored last RDQs:\n");
    __dump_bitmap(m, v, &info->config.last_rdq_bitmap);
    seq_printf(m, "\t\tOperational RDQs:\n");
    __dump_bitmap(m, v, &priv->operational_state.rdq_bitmap);
    seq_printf(m, "\t\tTrigger state RDQs:\n");
    __dump_bitmap(m, v, &priv->debug_trigger_state.rdq_bitmap);
    seq_printf(m, "\n");

    seq_printf(m, "\tMonitored Cmd_ifc:\n");
    seq_printf(m, "\t\tNumber of cmd_ifc packet received is :%llu\n", priv->cmd_ifc_num_of_pck_received);
    seq_printf(m, "\t\tCmd ifc sent via the Health check: %s\n",
               (info->config.cmd_ifc.last_cmd_ifc_sent_via_health) ? "Yes" : "No");
    seq_printf(m, "\t\tCmd ifc max_iter_allowed: %u\n", info->config.cmd_ifc.max_iter_allowed);
    seq_printf(m, "\t\tCmd ifc num_of_check_iter: %llu\n", info->config.cmd_ifc.num_of_check_iter);
    seq_printf(m, "\t\tCmd ifc last_cmd_ifc_counter: %llu\n", info->config.cmd_ifc.last_cmd_ifc_counter);
    seq_printf(m, "\n");


    seq_printf(m, "\tFailures Information:\n");

    list_for_each_entry(failure, &info->failure_ts_list, list) {
        __dump_failure(m, v, failure);
    }

    mutex_unlock(&info->lock);
}

int sx_health_check_dump(struct seq_file *m, void *v)
{
    struct sx_health_dev_info *info;

    print_table_header(m, "Health-Check DUMP");

    mutex_lock(&__health_check_lock);

    list_for_each_entry(info, &__dev_info_list, dev_list) {
        __dump_info(m, v, info);
    }

    mutex_unlock(&__health_check_lock);
    return 0;
}

void sx_health_check_set_debug_trigger(struct sx_health_check_trigger_params *params)
{
    struct sx_health_dev_info *info;
    struct sx_priv            *priv = NULL;

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
        priv->operational_state.cmd_ifc = false;
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
