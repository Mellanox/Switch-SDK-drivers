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

#define DEV_ID_ALL                 (0)
#define START_HETT_SESSION         0
#define STOP_HETT_SEASSON          1
#define FW_SOS_TEST                0x1
#define FW_SOS_LOG_MAX_SIZE        256
#define HEALTH_CHECK_EVENT_MSG_MAX 512
#define FW_SOS_IRON_RISC           1
#define FW_SOS_EXECUTED_EMAD       1
#define FW_SOS_TEST                0x1
#define CAUSE_OFFSET_MASK          0x1F
#define DEFAULT_ALERT_THRESHOLD    3
#define DEFAULT_CHECK_INTERVAL     1

#define SX_HEALTH_HIGH_SEVERITY(severity) ((severity) <= SXD_HEALTH_SEVERITY_WARN)

/*
 * Currently there is no FW design about device_index and slot_index in MECCC, we don't know the valid ranges for device_index and slot_index.
 * FW always returns the ECC statistics for device_index 0 and slot_index 0, so here we only define a single software cache for device_index 0 and slot_index 0.
 * If FW supports multiple device_index/slot_index in the future, then we need to define the software cache for all possible combinations of device_index/slot_index.
 */
typedef struct sxd_mgmt_ecc_stats {
    uint32_t ecc_corrected;   /**< Indicate amount of ECC correctable events */
    uint32_t ecc_uncorrected; /**< Indicate amount of ECC uncorrectable events */
} sxd_mgmt_ecc_stats_t;

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
    char err_msg[HEALTH_CHECK_EVENT_MSG_MAX];
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
    struct sx_bitmap      rdq_bitmap;
    struct sx_bitmap      last_rdq_bitmap; /* keep state upon config change */
    struct sx_bitmap      ignore_rdq_bitmap; /* will contain all WJH RDQ the need to ignore and not monitor*/
    struct config_sdq     sdq;
    struct sx_cmd_ifc     cmd_ifc;
    uint32_t              periodic_time;
    uint32_t              failures_num;
    sxd_health_severity_t min_severity;
};

struct sx_health_dev_info {
    struct sx_dev      *dev;
    struct delayed_work main_health_check_dwork;
    struct list_head    dev_list;
    u32 __iomem        *catas_iomap;
    struct mutex        lock;

    /* following fields must be accessed within device information lock */
    struct list_head              issues_list;
    u32                           major_issues_detected; /* error or higher */
    u32                           minor_issues_detected; /* warning or lower */
    sxd_health_cause_t            fatal_cause;
    sxd_event_health_data_t       event_extra_data;
    sxd_mgmt_ecc_stats_t          ecc_stats;
    bool                          health_check_first_itr_skip_checks_func;
    struct sx_health_check_config config;
    bool                          disabled;
    bool                          fatal_error_mode_active;
    bool                          issu_on;
    bool                          issu_signal_done;
    struct completion            *wq_issu_cyc_completion;
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
    sxd_health_severity_t       severity;
    unsigned long               jiffies; /* time when the failure happened */
    struct list_head            list;
    sxd_health_cause_t          cause;
    bool                        has_cause_data;
    union sdk_health_cause_data cause_data;
    sxd_event_health_data_t     event_data;
    u8                          irisc_id;
};

struct external_cause_work {
    struct work_struct                w;
    u8                                dev_id; /* dev_id == DEV_ID_ALL means all devices */
    u32                               issue_severity;
    u32                               issue_cause;
    u8                                irisc_id;
    union sdk_health_cause_data       cause_data;
    sxd_health_external_report_data_t data;
};

struct mfde_work {
    struct ku_mfde_reg mfde;
    struct sx_dev     *dev;
    struct work_struct w;
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

/************************************************
 *  Local function declarations
 ***********************************************/

static const char * const sxd_health_thread_id_str_s[] = {
    SXD_FOREACH_OBJECT_HEALTH_THREAD_FAILURE_ID(SXD_GENERATE_STRING)
};

static const char * thread_id_str(sxd_thread_failure_e thread_id)
{
    return ((thread_id > SXD_HEALTH_THREAD_MAX_E) ?
            "Unknown" : sxd_health_thread_id_str_s[thread_id]);
};

static const char * const sxd_cause_type_str_s[] = {
    SXD_FOREACH_OBJECT_HEALTH_CAUSE(SXD_GENERATE_STRING)
};

static const char * sxd_cause_type_str(sxd_health_cause_t idx)
{
    return ((idx > SXD_HEALTH_CAUSE_MAX_E) ?
            "Unknown" : sxd_cause_type_str_s[idx]);
};

static const char * __severity_to_str(sxd_health_severity_t severity)
{
    const char *str;

    switch (severity) {
    case SXD_HEALTH_SEVERITY_FATAL:
        str = "Fatal";
        break;

    case SXD_HEALTH_SEVERITY_WARN:
        str = "Warning";
        break;

    case SXD_HEALTH_SEVERITY_NOTICE:
        str = "Notice";
        break;

    default:
        str = "N/A";
        break;
    }

    return str;
}

static int __get_kernel_crtimeout_print(char          *print_message,
                                        uint8_t        irisc,
                                        uint8_t        log_id,
                                        uint8_t        emad_or_cmd,
                                        struct sx_dev *dev)
{
    int                 err = 0;
    enum sxd_chip_types chip_type = SXD_CHIP_TYPE_UNKNOWN;
    struct sx_priv     *priv = sx_priv(dev);
    bool                iron_emad = false;
    bool                sma_access = false;
    bool                pci_tools_api = false;
    bool                regular_iric = false;

    chip_type = priv->dev_info.dev_info_ro.chip_type;
    /*decide which cr master caused  crspace timeout according to chip type */
    switch (chip_type) {
    case SXD_CHIP_TYPE_SPECTRUM2:
    case SXD_CHIP_TYPE_QUANTUM:
    case SXD_CHIP_TYPE_SPECTRUM:
    case SXD_CHIP_TYPE_SPECTRUM_A1:
    case SXD_CHIP_TYPE_SWITCH_IB:
    case SXD_CHIP_TYPE_SWITCH_IB2:
        if ((log_id == 0) || ((log_id >= 2) && (log_id <= 7))) {
            regular_iric = true;
        }
        if (log_id == 9) {
            pci_tools_api = true;
        }
        if (log_id == 11) {
            sma_access = true;
        }
        break;

    case SXD_CHIP_TYPE_SPECTRUM3:
    case SXD_CHIP_TYPE_SPECTRUM4:
    case SXD_CHIP_TYPE_QUANTUM2:
    case SXD_CHIP_TYPE_QUANTUM3:
        if ((log_id == 0) || ((log_id >= 2) && (log_id <= 9))) {
            regular_iric = true;
        }
        if (log_id == 11) {
            pci_tools_api = true;
        }
        if (log_id == 12) {
            sma_access = true;
        }
        break;

    default:
        err = 1;
        printk(KERN_ERR "Health check: cr-timeout print failed, unsupported ASIC type:[%d]\n",
               chip_type);
        goto out;
        break;
    }


    if ((irisc == FW_SOS_IRON_RISC) && (log_id == FW_SOS_IRON_RISC) && (emad_or_cmd == FW_SOS_EXECUTED_EMAD) &&
        (iron_emad == true)) {
        strcpy(print_message, "Crspace timeout is due to EMAD/ICMD execution");
        goto out;
    }

    if ((pci_tools_api == true) || ((irisc == 1) && (iron_emad == false))) {
        strcpy(print_message, "Crspace timeout is due to Tools or FW dump me API");
        goto out;
    }

    if ((regular_iric == true) && (log_id != irisc)) {
        strcpy(print_message, "Crspace timeout is due to internal FW process");
        goto out;
    }

    if (regular_iric == true) {
        strcpy(print_message, "Crspace timeout is due to EMAD/ICMD execution");
        goto out;
    }

    if (sma_access == true) {
        strcpy(print_message, "crspace timeout is sue to external access via HOST");
        goto out;
    }

    strcpy(print_message, "crspace timeout case is unknown. Check FW");
    printk(KERN_ERR "Health check: Selected print: %s\n", print_message);
out:
    return err;
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
void sx_health_check_fshe_error_update(struct sx_dev * dev)
{
    sxd_event_health_notification_t   sdk_health;
    sxd_health_external_report_data_t event_ext_data;

    memset(&event_ext_data, 0, sizeof(sxd_health_external_report_data_t));
    memset(&sdk_health, 0, sizeof(sdk_health));

    sdk_health.severity = SXD_HEALTH_SEVERITY_FATAL;
    sdk_health.cause = SXD_HEALTH_CAUSE_STATEFUL_DB_ORDERING_E;

    sx_health_external_report(dev->device_id,
                              sdk_health.severity,
                              sdk_health.cause,
                              DBG_ALL_IRICS,
                              &event_ext_data,
                              "FSHE event raised stateful DB ordering issue");
}
/*Meccc trap that received in the kernel side  */
void sx_health_check_meccc_error_update(struct ku_meccc_reg *meccc_reg,  struct sx_dev * dev)
{
    sxd_health_external_report_data_t data;

    memset(&data, 0, sizeof(sxd_health_external_report_data_t));

    data.extra_data_event.ecc_data.device_index = meccc_reg->device_index;
    data.extra_data_event.ecc_data.slot_index = meccc_reg->slot_index;
    data.ecc_stats.ecc_uncorrected = meccc_reg->ecc_ucrt_cnt;
    data.ecc_stats.ecc_corrected = meccc_reg->ecc_crt_cnt;

    /* the severity will be update in a lower level */
    sx_health_external_report(dev->device_id,
                              SXD_HEALTH_SEVERITY_NOTICE,
                              SXD_HEALTH_CAUSE_ECC_E,
                              DBG_ALL_IRICS,
                              &data,
                              "MECCC event raised ECC corrected/uncorrected");
}

/* must be called within the device information lock */
static void __add_issue(struct sx_health_dev_info   *info,
                        u32                          issue_severity,
                        sxd_health_cause_t           cause,
                        uint8_t                      irisc_id,
                        union sdk_health_cause_data *cause_data,
                        sxd_event_health_data_t     *event_data)
{
    struct issue_info *new_issue = NULL;


    if (SXD_HEALTH_CAUSE_NONE != info->fatal_cause) {
        /* device is already in fatal mode, ignoring any additional issues */
        return;
    }

    if (SXD_HEALTH_SEVERITY_FATAL == issue_severity) {
        info->fatal_cause = cause;
        if (event_data) {
            memcpy(&info->event_extra_data, event_data, sizeof(info->event_extra_data));
        }
    }

    new_issue = kzalloc(sizeof(struct issue_info), GFP_KERNEL);
    if (new_issue == NULL) {
        printk(KERN_ERR "Health check: couldn't allocate device %u health-check failure\n", info->dev->device_id);
        return;
    }

    INIT_LIST_HEAD(&new_issue->list);
    new_issue->severity = issue_severity;
    new_issue->jiffies = jiffies;
    new_issue->cause = cause;
    new_issue->irisc_id = irisc_id;

    if (cause_data) {
        new_issue->has_cause_data = true;
        memcpy(&new_issue->cause_data, cause_data, sizeof(new_issue->cause_data));
    }
    if (event_data) {
        memcpy(&new_issue->event_data, event_data, sizeof(new_issue->event_data));
    }

    list_add_tail(&new_issue->list, &info->issues_list);
    if (SX_HEALTH_HIGH_SEVERITY(issue_severity)) {
        info->major_issues_detected++;
    } else {
        info->minor_issues_detected++;
    }

    /*
     * send an event if its severity is equal to or higher than the minimum severity the user asked for.
     * Don't care about FATAL event, it will be raised elsewhere.
     * NOTE: higher severity = lower numeric value.
     **/
    if ((info->config.min_severity >= issue_severity) && (issue_severity != SXD_HEALTH_SEVERITY_FATAL)) {
        sx_send_health_event(info->dev->device_id, cause, issue_severity, irisc_id, event_data, NULL);
        printk(KERN_NOTICE "Health check issue found: device=%d, cause=%s cause id=%d, severity=%s irisc_id=0x%x\n",
               info->dev->device_id,
               sxd_cause_type_str(cause),
               cause,
               __severity_to_str(issue_severity),
               irisc_id);
    }
}

static void __add_issue_to_all_devices(u32                          issue_severity,
                                       sxd_health_cause_t           cause,
                                       u8                           irisc_id,
                                       union sdk_health_cause_data *cause_data)
{
    struct sx_health_dev_info *info;

    list_for_each_entry(info, &__dev_info_list, dev_list) {
        mutex_lock(&info->lock);
        __add_issue(info, issue_severity, cause, irisc_id, cause_data, NULL);
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

static int __write_hett(struct ku_access_hett_reg *hett, struct sx_dev *dev, const char *op)
{
    int err;

    hett->dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&hett->op_tlv, MLXSW_HETT_ID, EMAD_METHOD_WRITE);
    err = sx_ACCESS_REG_HETT(dev, hett);
    if (err) {
        printk(KERN_ERR "Health check:sx_ACCESS_REG_HETT (%s) returned with error %d\n", op, err);
    }

    return err;
}

static int __read_meccc_and_update_ecc_stas(struct ku_access_meccc_reg *meccc,
                                            struct sx_health_dev_info  *info,
                                            const char                 *op)
{
    int err = 0;

    meccc->dev_id = info->dev->device_id;
    sx_cmd_set_op_tlv(&meccc->op_tlv, MLXSW_MECCC_ID, EMAD_METHOD_QUERY);
    err = sx_ACCESS_REG_MECCC(info->dev, meccc);
    if (err) {
        printk(KERN_ERR "Health check:sx_ACCESS_REG_MECCC (%s) returned with error %d\n", op, err);
        goto out;
    }
    info->ecc_stats.ecc_corrected = meccc->meccc_reg.ecc_crt_cnt;
    info->ecc_stats.ecc_uncorrected = meccc->meccc_reg.ecc_ucrt_cnt;
out:
    return err;
}

static int __read_write_mfgd(struct ku_access_mfgd_reg *mfgd, struct sx_dev *dev, sx_emad_method_e cmd, const char *op)
{
    int err;

    mfgd->dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mfgd->op_tlv, MLXSW_MFGD_ID, cmd);
    err = sx_ACCESS_REG_MFGD(dev, mfgd);
    if (err) {
        printk(KERN_ERR "Health check: sx_ACCESS_REG_MFGD (%s) returned with error %d\n", op, err);
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
        __add_issue(info, SXD_HEALTH_SEVERITY_FATAL, SXD_HEALTH_CAUSE_CATAS, DBG_ALL_IRICS, &catas_data, NULL);
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
        __add_issue(info, SXD_HEALTH_SEVERITY_WARN, SXD_HEALTH_CAUSE_GO_BIT, DBG_ALL_IRICS, &cause_data, NULL);
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
        __add_issue(info, SXD_HEALTH_SEVERITY_WARN, SXD_HEALTH_CAUSE_GO_BIT, DBG_ALL_IRICS, &cause_data, NULL);
        goto out;
    }

    /* Seceded to acquire cmd_ifc semaphore*/
    /* GO bit not free - Only if sent query_fw via health check in
     * Previous cycles and got timeout  */
    if (sx_cmd_check_go_bit(info->dev, info->dev->device_id)) {
        cause_data.cmd_ifc_data.is_cmd_ifc_sent_from_health = info->config.cmd_ifc.is_last_pkt_sent_via_health;
        __add_issue(info, SXD_HEALTH_SEVERITY_WARN, SXD_HEALTH_CAUSE_GO_BIT, DBG_ALL_IRICS, &cause_data, NULL);
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
        __add_issue(info, SXD_HEALTH_SEVERITY_WARN, SXD_HEALTH_CAUSE_GO_BIT, DBG_ALL_IRICS, &cause_data, NULL);
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
        printk(KERN_NOTICE PFX "Health check:Did not receive completion for SDQ dqn (%u) \n",
               sub_bitmap_res);
        __add_issue(info, SXD_HEALTH_SEVERITY_WARN, SXD_HEALTH_CAUSE_SDQ, DBG_ALL_IRICS,  &dq_data, NULL);
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
                    printk(KERN_ERR "Health check:__test_sdq failed to post and send"
                           " via SDQ_Id =%d ,(ret=%d)\n", sdq_id, ret);
                    goto out;
                }
                /* origin skb big enough to contain all data needed */
            } else {
                ret = __sx_core_post_send(dev, skb, &meta, sdq_id);
                if (ret != 0) {
                    printk(KERN_ERR "Health check:_test_sdq failed to post and send"
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
        printk(KERN_ERR "Health check :SDQ monitor- failed to sent PGCR for"
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
        __add_issue(info, SXD_HEALTH_SEVERITY_FATAL, SXD_HEALTH_CAUSE_FW_HETT, DBG_ALL_IRICS, NULL, NULL);
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
        __add_issue(info, SXD_HEALTH_SEVERITY_WARN, SXD_HEALTH_CAUSE_RDQ, DBG_ALL_IRICS, &dq_data, NULL);
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

    mutex_lock(&info->lock);
    cause_data.sdk_thread_data.msg_error = threads_info->error_msg;
    cause_data.sdk_thread_data.sdk_thread_id = threads_info->sdk_thread_id;
    __add_issue(info, threads_info->severity, SXD_HEALTH_CAUSE_SDK_THREADS, DBG_ALL_IRICS, &cause_data, NULL);

    mutex_unlock(&info->lock);
    return 0;
}
static int __sx_health_add_sdk_emad_timeout_failure(u8 dev_id)
{
    struct sx_health_dev_info  *info = NULL;
    union sdk_health_cause_data cause_data;


    info = __info_find(dev_id);
    if (!info) {
        return -ENODEV;
    }

    mutex_lock(&info->lock);
    __add_issue(info, SXD_HEALTH_SEVERITY_FATAL, SXD_HEALTH_CAUSE_EMAD_TIMEOUT, DBG_ALL_IRICS, &cause_data, NULL);

    mutex_unlock(&info->lock);
    return 0;
}


static int __sx_health_set_issu_on(u8 dev_id, struct completion *cyc_finish_wq_completion)
{
    struct sx_health_dev_info *info = NULL;

    info = __info_find(dev_id);
    if (!info) {
        return -ENODEV;
    }

    mutex_lock(&info->lock);
    if (info->issu_on) {
        goto out;
    }

    init_completion(cyc_finish_wq_completion);
    info->issu_on = true;
    info->issu_signal_done = false;
    info->wq_issu_cyc_completion = cyc_finish_wq_completion;

out:
    mutex_unlock(&info->lock);

    return 0;
}


static int __sx_health_set_issu_off(u8 dev_id)
{
    struct sx_health_dev_info *info = NULL;

    info = __info_find(dev_id);
    if (!info) {
        return -ENODEV;
    }

    mutex_lock(&info->lock);
    if (!info->issu_on) {
        goto out;
    }

    info->issu_on = false;
    info->issu_signal_done = false;
    info->health_check_first_itr_skip_checks_func = true;

out:
    mutex_unlock(&info->lock);

    return 0;
}

/* must be called within the device information lock */
static void __remove_old_issues(struct sx_health_dev_info *info)
{
    struct issue_info *iter, *tmp;
    unsigned long      now = jiffies;

    list_for_each_entry_safe(iter, tmp, &info->issues_list, list) {
        if (time_after(now, iter->jiffies + info->config.failures_num * 10 * HZ)) {
            if (SX_HEALTH_HIGH_SEVERITY(iter->severity)) {
                info->major_issues_detected--;
            } else {
                info->minor_issues_detected--;
            }

            list_del(&iter->list);
            kfree(iter);
        } else {
            break; /* failures are in chronological order, if we're here we can stop the iteration */
        }
    }
}

/* MAIN THREAD of health check mechanism , sample all monitors and sent Health check event  */
static void __sx_health_check_cycle(struct work_struct *work)
{
    struct sx_health_dev_info *info = container_of(work, struct sx_health_dev_info, main_health_check_dwork.work);
    int                        err = 0;
    struct issue_info         *failure = NULL;

    mutex_lock(&info->lock);

    if (info->disabled) {
        /* user removed device from health-check. */
        goto out;
    }

    /* this is an immediate check, no need for 2-step check */
    __check_catas(info);

    if (info->issu_on) {
        if (!info->issu_signal_done) {
            complete(info->wq_issu_cyc_completion);
            info->issu_signal_done = true;
        }
        goto issu_supported_features;
    }

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

issu_supported_features:
    failure = list_last_entry(&info->issues_list, struct issue_info, list);
    if (info->fatal_cause != SXD_HEALTH_CAUSE_NONE) {
        /* Fatal failure detect: send SDK health event and stop monitoring this device */

        sx_send_health_event(info->dev->device_id,
                             info->fatal_cause,
                             SXD_HEALTH_SEVERITY_FATAL,
                             failure->irisc_id,
                             &info->event_extra_data,
                             NULL);
        printk(KERN_ERR "SXD_HEALTH_FATAL:On device %u cause ='%s' [id = %d]- Stopping further device monitoring!\n",
               info->dev->device_id, sxd_cause_type_str(info->fatal_cause), info->fatal_cause);
    } else if (info->major_issues_detected >= info->config.failures_num) {
        /* Too many failures: send SDK health event with SXD_HEALTH_CAUSE_SDK_WD cause and stop monitoring this device */

        info->fatal_cause = SXD_HEALTH_CAUSE_SDK_WD;

        sx_send_health_event(info->dev->device_id,
                             SXD_HEALTH_CAUSE_SDK_WD,
                             SXD_HEALTH_SEVERITY_FATAL,
                             failure->irisc_id,
                             NULL,
                             NULL);
        printk(
            KERN_ERR "SXD_HEALTH_FATAL:device %u is set to FATAL because of too many major issues - Stopping further device monitoring!\n",
            info->dev->device_id);
    } else {
        __remove_old_issues(info);
        queue_delayed_work(__health_check_wq, &info->main_health_check_dwork, info->config.periodic_time * HZ);
    }

out:
    mutex_unlock(&info->lock);
}

static int __sx_health_send_mfgd(struct sx_dev                 *dev,
                                 bool                           enable,
                                 bool                           fatal_error_mode_active,
                                 sxd_mfgd_fw_fatal_event_test_t fw_fatal_event_test)
{
    struct ku_access_mfgd_reg reg_mfgd;
    int                       err = 0;

    memset(&reg_mfgd, 0, sizeof(reg_mfgd));
    /*get sdk_fatal_error_mode to determine which state to set fw_fatal_mode*/
    err = __read_write_mfgd(&reg_mfgd,
                            dev,
                            EMAD_METHOD_QUERY,
                            "send mfgd fw fatal health check trigger with read mode");
    if (err) {
        printk(KERN_ERR "Health check:Failed to read MFGD %u\n", dev->device_id);
    }
    /*"Get should have handled this, set the "1" defaults or all hell breaks loose */
    /*    reg_mfgd.fw_dci_rif_cache = true; */
    /*    reg_mfgd.fw_dci_en = true; */
    /*    reg_mfgd.fw_kvc_en = true; */
    /*    reg_mfgd.atcam_bf_en = true; */
    /*    reg_mfgd.egress_en = 0xFF; */
    /*  */
    if (enable) {
        reg_mfgd.mfgd_reg.fw_fatal_event_mode =
            (fatal_error_mode_active) ? SXD_MFGD_FW_FATAL_EVENT_MODE_CHECK_FW_FATAL_STOP_FW_E :
            SXD_MFGD_FW_FATAL_EVENT_MODE_CHECK_FW_FATAL_E;
        reg_mfgd.mfgd_reg.en_debug_assert = (fatal_error_mode_active) ? 1 : 0;
    } else {/*disable */
        reg_mfgd.mfgd_reg.fw_fatal_event_mode = SXD_MFGD_FW_FATAL_EVENT_MODE_DONT_CHECK_FW_FATAL_E;
        reg_mfgd.mfgd_reg.en_debug_assert = false;
    }
    reg_mfgd.mfgd_reg.fw_fatal_event_test = fw_fatal_event_test;

    err =
        __read_write_mfgd(&reg_mfgd, dev, EMAD_METHOD_WRITE, "send mfgd fw fatal health check trigger on write mode");
    if (err) {
        printk(KERN_ERR "Health check:Failed to write MFGD %u\n", dev->device_id);
    }

    return err;
}

/* must be called within the health-check lock */
static int __info_alloc(u8                          dev_id,
                        sampling_params_t         * params,
                        struct sx_health_dev_info **ret_info,
                        bool                        fatal_error_mode_active)
{
    struct sx_dev             *dev = NULL;
    struct sx_priv            *priv = NULL;
    struct sx_health_dev_info *info = NULL;
    resource_size_t            catas_start = 0;
    u32 __iomem               *catas_iomap = NULL;
    int                        err = 0;
    uint32_t                   dq_id = 0;
    unsigned long              flags;
    bool                       mfgd_enable = true;
    unsigned long              hw_groups_curr_status;
    struct ku_access_meccc_reg reg_meccc;


    dev = sx_dev_db_get_dev_by_id(dev_id);
    if (!dev) {
        printk(KERN_ERR "Health check:failed to get device from id (id=%u)\n", dev_id);
        err = -ENODEV;
        goto out;
    }

    priv = sx_priv(dev);

    if (priv->fw.catas_size > 0) {
        catas_start = pci_resource_start(dev->pdev, priv->fw.catas_bar) + priv->fw.catas_offset;
        catas_iomap = ioremap(catas_start, priv->fw.catas_size * 4);
        if (!catas_iomap) {
            printk(KERN_ERR "Health check:failed to map internal error buffer on device %u at 0x%llx\n",
                   dev->device_id,
                   catas_start);
            err = -ENOMEM;
            goto out;
        }
    }

    info = kzalloc(sizeof(struct sx_health_dev_info), GFP_KERNEL);
    if (!info) {
        printk(KERN_ERR "Health check:could not create a new health-check entry for device %u\n", dev->device_id);
        err = -ENOMEM;
        goto out;
    }

    info->dev = dev;
    info->catas_iomap = catas_iomap;
    info->fatal_cause = SXD_HEALTH_CAUSE_NONE;
    info->issu_on = params->issu_on;
    if (info->issu_on) {
        info->issu_signal_done = true;
    }

    INIT_DELAYED_WORK(&info->main_health_check_dwork, __sx_health_check_cycle);
    INIT_LIST_HEAD(&info->dev_list);
    INIT_LIST_HEAD(&info->issues_list);

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

    info->config.periodic_time = params->check_interval;
    info->config.failures_num = params->alert_threshold;
    info->config.sdq.max_iter_allowed = __sx_sdq_calc_num_of_check_iter(info->config.periodic_time);
    info->config.min_severity = params->min_severity;

    hw_groups_curr_status = params->hw_groups_curr_status;
    /* fill the rdq_bitmap with the hw_traps that exist before starting this feature */
    for (dq_id = 0; dq_id < priv->dev_cap.max_num_rdqs; dq_id++) {
        if (test_bit(dq_id, &hw_groups_curr_status)) {
            sx_bitmap_set(&info->config.rdq_bitmap, dq_id);
        }
    }
    info->health_check_first_itr_skip_checks_func = true;
    info->fatal_error_mode_active = fatal_error_mode_active;
    err = __sx_health_send_mfgd(dev, mfgd_enable, fatal_error_mode_active, SXD_MFGD_FW_FATAL_EVENT_TEST_DONT_TEST_E);
    if (err) {
        goto out;
    }

    /* fill the ignore_bitmap with the WJH hw_traps that exist before starting this feature */
    /* must lock set_monitor_rdq_lock first to avoid update of new RDQ WJH in parallel
     * set_monitor_rdq_lock is locked in higher stage (under fun sx_health_check_configure) */
    spin_lock_irqsave(&priv->rdq_table.lock, flags);
    for (dq_id = 0; dq_id < priv->monitor_rdqs_count; dq_id++) {
        sx_bitmap_set(&info->config.ignore_rdq_bitmap, priv->monitor_rdqs_arr[dq_id]);
    }
    spin_unlock_irqrestore(&priv->rdq_table.lock, flags);

    switch (priv->dev_info.dev_info_ro.chip_type) {
    case SXD_CHIP_TYPE_SPECTRUM:
    case SXD_CHIP_TYPE_SPECTRUM2:
    case SXD_CHIP_TYPE_SPECTRUM3:
    case SXD_CHIP_TYPE_SPECTRUM4:
        memset(&reg_meccc, 0, sizeof(reg_meccc));

        /* Currently only device_index 0 and slot_index 0 is supported for MECCC ,see more details where sxd_mgmt_ecc_stats defined*/
        reg_meccc.meccc_reg.device_index = 0;
        reg_meccc.meccc_reg.slot_index = 0;

        err = __read_meccc_and_update_ecc_stas(&reg_meccc, info, "Read ecc counters");
        break;

    default:
        break;
    }

    list_add_tail(&info->dev_list, &__dev_info_list);
    *ret_info = info;

out:
    return err;
}

/* must be called within the health-check lock */
static void __info_dealloc(struct sx_health_dev_info *info)
{
    struct issue_info *iter = NULL, *tmp = NULL;
    int                err = 0;
    bool               mfgd_enable = false;
    struct sx_priv    *priv = sx_priv(info->dev);

    printk(KERN_INFO "Health-Check: disabling monitoring on device %d\n", info->dev->device_id);

    mutex_lock(&info->lock);
    info->disabled = true;
    err = __sx_health_send_mfgd(info->dev,
                                mfgd_enable,
                                info->fatal_error_mode_active,
                                SXD_MFGD_FW_FATAL_EVENT_TEST_DONT_TEST_E);
    if (err) {
        printk(KERN_INFO "Health-Check: failed to disabling fw fatal monitoring (MFGD) on device %d\n",
               info->dev->device_id);
    }
    /* clear all debug triggers */
    __health_check_ts_trigger = false;
    priv->debug_trigger_state.catas = false;
    priv->debug_trigger_state.cmd_ifc = false;
    sx_bitmap_clear_all(&priv->debug_trigger_state.sdq_bitmap);
    sx_bitmap_clear_all(&priv->debug_trigger_state.rdq_bitmap);
    __health_check_wq_threads_trigger = false;

    list_del(&info->dev_list);

    list_for_each_entry_safe(iter, tmp, &info->issues_list, list) {
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
            __add_issue_to_all_devices(SXD_HEALTH_SEVERITY_WARN,
                                       SXD_HEALTH_CAUSE_KERNEL_THREADS,
                                       DBG_ALL_IRICS,
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
        printk(KERN_ERR "Health check:couldn't allocate new_kernel_thread node\n");
        goto out;
    }
    INIT_LIST_HEAD(&new_kernel_thread->list);
    INIT_DELAYED_WORK(&new_kernel_thread->kernel_wq_increase_cnt_dwork,  __sx_health_inc_wq_thread_counter);

    new_kernel_thread->jiffies = jiffies;
    new_kernel_thread->name = kstrdup(name, GFP_KERNEL);
    if (new_kernel_thread->name == NULL) {
        printk(KERN_ERR "Health check:allocate thread name %s for new_kernel_thread failed\n", name);
        kfree(new_kernel_thread);
        new_kernel_thread = NULL;
        goto out;
    }
    new_kernel_thread->wq = create_singlethread_workqueue(name);
    if (!new_kernel_thread->wq) {
        printk(KERN_ERR  "Health check: Failed to create wq %s. \n", name);
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

static int __sx_health_add_device(u8 dev_id, sampling_params_t * params, bool fatal_error_mode_active)
{
    struct sx_health_dev_info *info = NULL;
    int                        err = 0;
    bool                       is_first_time_device_with_health_check = false;

    if (list_empty(&__dev_info_list)) {
        is_first_time_device_with_health_check = true;
    }

    info = __info_find(dev_id);
    if (!info) {
        err = __info_alloc(dev_id,
                           params,
                           &info,
                           fatal_error_mode_active);
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

static int __sx_health_update_sampling_params(u8                    dev_id,
                                              uint32_t              check_interval,
                                              uint32_t              alert_threshold,
                                              sxd_health_severity_t min_severity)
{
    struct sx_health_dev_info *info = NULL;

    info = __info_find(dev_id);
    if (!info) {
        return -ENODEV;
    }

    mutex_lock(&info->lock);

    info->config.periodic_time = check_interval;
    info->config.failures_num = alert_threshold;
    info->config.min_severity = min_severity;
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
        printk(KERN_ERR "Health check:: Failed to initialize SDQs debug trigger bitmap, aborting.\n");
        goto out;
    }

    ret = sx_bitmap_init(&priv->debug_trigger_state.rdq_bitmap, NUMBER_OF_RDQS);
    if (ret) {
        printk(KERN_ERR "Health check:: Failed to initialize RDQs debug trigger bitmap, aborting.\n");
        goto out;
    }
    ret = sx_bitmap_init(&priv->operational_state.sdq_bitmap, NUMBER_OF_SDQS);
    if (ret) {
        printk(KERN_ERR "Health check:: Failed to initialize operational SDQs debug trigger bitmap, aborting.\n");
        goto out;
    }

    ret = sx_bitmap_init(&priv->operational_state.rdq_bitmap, NUMBER_OF_RDQS);
    if (ret) {
        printk(KERN_ERR "Health check:: Failed to initialize operational SDQs debug trigger bitmap, aborting.\n");
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
        printk(KERN_ERR "Health check has not been started\n");
        err = -ENOENT;
        goto out;
    }

    if (!list_empty(&__dev_info_list)) {
        printk(KERN_ERR "Health check: devices are still being monitored\n");
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
    int               err = 0;
    struct completion cyc_finish_wq_completion;

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
        printk(KERN_INFO "Health-Check: Enable device %u, issu_on %d\n",
               params->dev_id,
               params->params.sampling_params.issu_on);
        err = __sx_health_add_device(params->dev_id,
                                     &params->params.sampling_params,
                                     params->fatal_error_mode_active);
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
        printk(
            KERN_INFO "Health-Check: Update sampling parameters for device %u (interval=%u, threshold=%u min_severity=%s)\n",
            params->dev_id,
            params->params.sampling_params.check_interval,
            params->params.sampling_params.alert_threshold,
            __severity_to_str(params->params.sampling_params.min_severity));

        err = __sx_health_update_sampling_params(params->dev_id,
                                                 params->params.sampling_params.check_interval,
                                                 params->params.sampling_params.alert_threshold,
                                                 params->params.sampling_params.min_severity);
        break;

    case SXD_HEALTH_FATAL_FAILURE_ADD_SDK_THREAD_FAILRE_E:
        printk(KERN_INFO "Health-Check: Add SDK thread %s failure for device %u \n",
               thread_id_str(params->params.sdk_threads_info.sdk_thread_id),
               params->dev_id);
        err = __sx_health_add_sdk_thread_failure(params->dev_id,
                                                 &params->params.sdk_threads_info);
        break;

    case SXD_HEALTH_FATAL_FAILURE_ADD_EMAD_TIMEOUT_FAILURE_E:
        printk(KERN_INFO "Health-Check: Add timeout error for device %u \n", params->dev_id);
        err = __sx_health_add_sdk_emad_timeout_failure(params->dev_id);
        break;

    case SXD_HEALTH_FATAL_FAILURE_ISSU_ON_E:
        printk(KERN_INFO "Health-Check: Set ISSU on mode for device %u\n",  params->dev_id);
        err = __sx_health_set_issu_on(params->dev_id, &cyc_finish_wq_completion);
        break;

    case SXD_HEALTH_FATAL_FAILURE_ISSU_OFF_E:
        printk(KERN_INFO "Health-Check: Set ISSU off mode for device %u\n",  params->dev_id);
        err = __sx_health_set_issu_off(params->dev_id);
        break;

    default:
        break;
    }

unlock:
    mutex_unlock(&__health_check_lock);
    if (SXD_HEALTH_FATAL_FAILURE_ENABLE_E == params->sxd_health_fatal_failure_detect_cmd) {
        sx_set_monitor_rdq_unlock();
    }
    if (SXD_HEALTH_FATAL_FAILURE_ISSU_ON_E == params->sxd_health_fatal_failure_detect_cmd) {
        /* Wait for check cycle to finish, after the cycle is done SDK can continue with the ISSU process. */
        wait_for_completion_interruptible(&cyc_finish_wq_completion);
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
    int  rmin = -1, rmax = -1;
    bool found_bit, bit_test;

    max = sx_bitmap_num_bits(bitmap);
    found_bit = false;
    for (i = 0; i < max; i++) {
        bit_test = sx_bitmap_test(bitmap, i);
        if (bit_test) {
            found_bit = true;
            if (rmin == -1) {
                rmin = (int)i;
            }

            rmax = i;
        }

        if ((rmin != -1) && (!bit_test || (i == max - 1))) {
            if (rmin == rmax) {
                seq_printf(m, "%d, ", rmin);
            } else {
                seq_printf(m, "%d-%d, ", rmin, rmax);
            }

            rmin = -1;
            rmax = -1;
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
    const char *severity_str = NULL;

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

    case SXD_HEALTH_CAUSE_FW_MFGD:
        cause = "FW MFGD not sent properly";
        break;

    case SXD_HEALTH_CAUSE_PLL_E:
        cause = "PLL error";
        break;

    case SXD_HEALTH_CAUSE_STATEFUL_DB_ORDERING_E:
        cause = "Stateful DB reordering issue";
        break;

    case SXD_HEALTH_CAUSE_FW:
        cause = "FW fatal error - MFDE trap";
        if (failure->has_cause_data) {
            snprintf(extra_info, sizeof(extra_info), " %s",
                     failure->cause_data.external_data.err_msg);
        }
        break;

    case SXD_HEALTH_CAUSE_EMAD_TIMEOUT:
        cause = "Emad timeout issue";
        break;

    case SXD_HEALTH_CAUSE_ECC_E:
        cause = "ECC";
        break;

    case SXD_HEALTH_CAUSE_GENERIC_E:
        cause = "Generic error";
        strncpy(extra_info, failure->cause_data.external_data.err_msg, sizeof(extra_info) - 1);
        break;

    case SXD_HEALTH_CAUSE_NO_CMDIFC_COMPLETION:
        cause = "Command interface timeout SXD_HEALTH_CAUSE_NO_CMDIFC_COMPLETION";
        break;

    default:
        cause = "Other";
        break;
    }
    ;

    severity_str = __severity_to_str(failure->severity);
    seq_printf(m, "        [%s] Cause: %s, Time (Seconds ago): %u",
               severity_str,
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
    seq_printf(m, "    Check Interval ................................... %u msec\n",
               (info->config.periodic_time * 1000));
    seq_printf(m, "    Alert Threshold .................................. %u failures\n",
               info->config.failures_num);
    seq_printf(m, "    Minimum Severity ................................. %s (%d)\n",
               __severity_to_str(info->config.min_severity),
               info->config.min_severity);
    seq_printf(m, "    Major issues detected ............................ %u\n", info->major_issues_detected);
    seq_printf(m, "    Minor issues detected ............................ %u\n", info->minor_issues_detected);
    seq_printf(m, "    Fatal detected ................................... %s\n",
               (info->fatal_cause != SXD_HEALTH_CAUSE_NONE) ? "Yes" : "No");
    seq_printf(m, "    Fatal-Error-Mode enabled ......................... %s\n",
               (info->fatal_error_mode_active) ? "Yes" : "No");
    seq_printf(m, "    ISSU On .......................................... %s\n",
               (info->issu_on) ? "Yes" : "No");
    seq_printf(m, "    ISSU signal done ................................. %s\n",
               (info->issu_signal_done) ? "Yes" : "No");
    seq_printf(m, "\n");

    seq_printf(m, "    ECC Counters\n");
    seq_printf(m, "        Correctable .................................. %u\n", info->ecc_stats.ecc_corrected);
    seq_printf(m, "        Uncorrectable ................................ %u\n", info->ecc_stats.ecc_uncorrected);
    seq_printf(m, "\n");

    seq_printf(m, "    SDQs\n");
    seq_printf(m, "        All .......................................... ");
    __dump_bitmap(m, v, context, &info->config.sdq.sdq_bitmap);
    seq_printf(m, "        Operational .................................. ");
    __dump_bitmap(m, v, context, &priv->operational_state.sdq_bitmap);
    seq_printf(m, "        Debug trigger ................................ ");
    __dump_bitmap(m, v, context, &priv->debug_trigger_state.sdq_bitmap);
    seq_printf(m, "        Max iterations allowed ....................... %u\n",
               info->config.sdq.max_iter_allowed);
    seq_printf(m, "        Current iteration ............................ %llu\n",
               info->config.sdq.num_of_check_iter);
    seq_printf(m, "\n");

    seq_printf(m, "    RDQs\n");
    seq_printf(m, "        All .......................................... ");
    __dump_bitmap(m, v, context, &info->config.rdq_bitmap);
    seq_printf(m, "        Ignored ...................................... ");
    __dump_bitmap(m, v, context, &info->config.ignore_rdq_bitmap);
    seq_printf(m, "        Monitored last cycle ......................... ");
    __dump_bitmap(m, v, context, &info->config.last_rdq_bitmap);
    seq_printf(m, "        Operational .................................. ");
    __dump_bitmap(m, v, context, &priv->operational_state.rdq_bitmap);
    seq_printf(m, "        Debug trigger ................................ ");
    __dump_bitmap(m, v, context, &priv->debug_trigger_state.rdq_bitmap);
    seq_printf(m, "\n");

    seq_printf(m, "    Command Interface\n");
    seq_printf(m, "        Packets received ............................. %llu\n",
               priv->cmd_ifc_num_of_pck_received);
    seq_printf(m, "        Last packet sent via health-check ............ %s\n",
               (info->config.cmd_ifc.is_last_pkt_sent_via_health) ? "Yes" : "No");
    seq_printf(m, "        Previous cycle counter ....................... %llu\n",
               info->config.cmd_ifc.last_cmd_ifc_counter);
    seq_printf(m, "\n");

    seq_printf(m, "    Kernel Threads\n");
    seq_printf(m, "        Operational .................................. %u\n",
               __kernel_thread_monitor_cnt);
    list_for_each_entry(iter_thread, &__kernel_thread_list, list) {
        seq_printf(m, "            %s \n", iter_thread->name);
    }
    seq_printf(m, "        Debug trigger ................................ %s\n",
               (__health_check_wq_threads_trigger ? "Yes" : "No"));
    if (__health_check_wq_threads_trigger) {
        seq_printf(m, "        Debug trigger thread ..................... %s\n",
                   __wq_thread_name_trigger);
    }
    seq_printf(m, "\n");

    seq_printf(m, "    Issues\n");

    list_for_each_entry(failure, &info->issues_list, list) {
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
    bool                                 mfgd_enable = true;
    int                                  err = 0;
    sampling_params_t                    sampling_params;

    mutex_lock(&__health_check_lock);

    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_SYSFS) {
        printk(KERN_NOTICE "Health-Check: Trigger SYSFS failure\n");
        __health_check_ts_trigger = true;
        goto out;
    }

    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_ADD_DEV) {
        printk(KERN_NOTICE "Health-Check: Trigger Add-Device %u\n", params->dev_id);
        sampling_params.alert_threshold = DEFAULT_ALERT_THRESHOLD;
        sampling_params.check_interval = DEFAULT_CHECK_INTERVAL;
        sampling_params.min_severity = SXD_HEALTH_SEVERITY_FATAL;

        __sx_health_add_device(params->dev_id, &sampling_params, params->fatal_error_mode_active);
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

    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_FW_FATAL_EVENT_TEST) {
        printk(KERN_NOTICE "Health-Check: Trigger FW fatal test with SX_HEALTH_CHECK_TRIGGER_OP_FW_FATAL_EVENT_TEST\n");
        err = __sx_health_send_mfgd(info->dev,
                                    mfgd_enable,
                                    info->fatal_error_mode_active,
                                    SXD_MFGD_FW_FATAL_EVENT_TEST_TRIGGER_FW_FATAL_EVENT_E);
        goto out;
    }
    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_FW_CAUSE_TEST) {
        printk(KERN_NOTICE "Health-Check: Trigger FW fatal test with SX_HEALTH_CHECK_TRIGGER_OP_FW_CAUSE_TEST\n");
        err = __sx_health_send_mfgd(info->dev,
                                    mfgd_enable,
                                    info->fatal_error_mode_active,
                                    SXD_MFGD_FW_FATAL_EVENT_TEST_TRIGGER_FATAL_CAUSE_E);

        goto out;
    }
    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_FW_ASSERT_TEST) {
        printk(KERN_NOTICE "Health-Check: Trigger FW fatal test with SX_HEALTH_CHECK_TRIGGER_OP_FW_ASSERT_TEST\n");
        err = __sx_health_send_mfgd(info->dev,
                                    mfgd_enable,
                                    info->fatal_error_mode_active,
                                    SXD_MFGD_FW_FATAL_EVENT_TEST_TRIGGER_FWASSERT_E);

        goto out;
    }
    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_FW_TILE_ASSERT_TEST) {
        printk(KERN_NOTICE "Health-Check: Trigger FW fatal test with SX_HEALTH_CHECK_TRIGGER_OP_FW_TILE_ASSERT_TEST\n");
        err = __sx_health_send_mfgd(info->dev,
                                    mfgd_enable,
                                    info->fatal_error_mode_active,
                                    SXD_MFGD_FW_FATAL_EVENT_TEST_TRIGGER_TILE_ASSERT_E);

        goto out;
    }
    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_FW_TILE_FATAL_CAUSE_TEST) {
        printk(
            KERN_NOTICE "Health-Check: Trigger FW fatal test with SX_HEALTH_CHECK_TRIGGER_OP_FW_TILE_FATAL_CAUSE_TEST\n");
        err = __sx_health_send_mfgd(info->dev,
                                    mfgd_enable,
                                    info->fatal_error_mode_active,
                                    SXD_MFGD_FW_FATAL_EVENT_TEST_TRIGGER_TILE_FATAL_CAUSE_E);
        goto out;
    }
    if (params->op == SX_HEALTH_CHECK_TRIGGER_OP_FW_PLL_FATAL_CAUSE_TEST) {
        printk(
            KERN_NOTICE "Health-Check: Trigger FW fatal test with SX_HEALTH_CHECK_TRIGGER_OP_FW_PLL_FATAL_CAUSE_TEST\n");
        err = __sx_health_send_mfgd(info->dev,
                                    mfgd_enable,
                                    info->fatal_error_mode_active,
                                    SXD_MFGD_FW_FATAL_EVENT_TEST_TRIGGER_FW_PLL_LOCK_CAUSE_E);
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

    case SX_HEALTH_CHECK_TRIGGER_OP_CANCEL_ALL:
        printk(KERN_NOTICE "Health-Check: Cancel all debug triggers on device %u\n", params->dev_id);
        priv->debug_trigger_state.catas = false;
        priv->debug_trigger_state.cmd_ifc = false;
        sx_bitmap_clear_all(&priv->debug_trigger_state.rdq_bitmap);
        sx_bitmap_clear_all(&priv->debug_trigger_state.sdq_bitmap);
        break;

    default:
        break;
    }
    mutex_unlock(&info->lock);

out:
    mutex_unlock(&__health_check_lock);
}

/*This function check if one of the ECC counters raise, if so in case of correction ecc sent  */
static bool __check_and_update_ecc_counters(struct sx_health_dev_info *info, struct external_cause_work *ecw)
{
    bool is_corrected = false;
    bool is_uncorrected = false;

    if (ecw->data.ecc_stats.ecc_corrected + ecw->data.ecc_stats.ecc_uncorrected == 1) {
        /* this condition is true if:
         * 1. this is the first ECC event since chip reset.
         * 2. this is the first ECC event since someone cleared MECCC counters
         */

        is_corrected = (ecw->data.ecc_stats.ecc_corrected > 0);
        is_uncorrected = (ecw->data.ecc_stats.ecc_uncorrected > 0);
    } else if (ecw->data.ecc_stats.ecc_corrected > info->ecc_stats.ecc_corrected) {
        is_corrected = true;
    } else if (ecw->data.ecc_stats.ecc_uncorrected > info->ecc_stats.ecc_uncorrected) {
        is_uncorrected = true;
    }

    if (is_corrected) {
        info->ecc_stats.ecc_corrected = ecw->data.ecc_stats.ecc_corrected;
        ecw->data.extra_data_event.ecc_data.ecc_stats.ecc_corrected = ecw->data.ecc_stats.ecc_corrected;

        printk(KERN_NOTICE "Health-Check :Correctable ECC event received from device [%u]\n", info->dev->device_id);
        ecw->issue_severity = SXD_HEALTH_SEVERITY_NOTICE;
    } else if (is_uncorrected) {
        info->ecc_stats.ecc_uncorrected = ecw->data.ecc_stats.ecc_uncorrected;
        ecw->data.extra_data_event.ecc_data.ecc_stats.ecc_uncorrected = ecw->data.ecc_stats.ecc_uncorrected;

        printk(KERN_NOTICE "Health-Check: Uncorrectable ECC event received from device [%u]\n", info->dev->device_id);
        ecw->issue_severity = SXD_HEALTH_SEVERITY_FATAL;
    } else {
        printk(KERN_NOTICE "Health check: ECC event received from device [%u] but no indication for changes.",
               info->dev->device_id);
    }

    return is_corrected || is_uncorrected;
}

static bool __check_external_report(struct sx_health_dev_info *info, struct external_cause_work *ecw)
{
    bool ret = true;

    switch (ecw->issue_cause) {
    case SXD_HEALTH_CAUSE_ECC_E:
        /* this call may change health-severity in 'ecw' */
        if (!__check_and_update_ecc_counters(info, ecw)) {
            printk(KERN_NOTICE "Health check: ECC raised on device %u but no indication for uncorrectable events.",
                   info->dev->device_id);
            ret = false;
        }

        break;

    default:
        break;
    }

    return ret;
}

static void __external_report_work(struct work_struct *work)
{
    struct external_cause_work *ecw = container_of(work, struct external_cause_work, w);
    struct sx_health_dev_info  *info = NULL;

    mutex_lock(&__health_check_lock);

    if (ecw->dev_id == DEV_ID_ALL) {
        __add_issue_to_all_devices(ecw->issue_severity, SXD_HEALTH_CAUSE_GENERIC_E,  ecw->irisc_id, &ecw->cause_data);
    } else {
        info = __info_find(ecw->dev_id);
        if (info) {
            mutex_lock(&info->lock);

            if (__check_external_report(info, ecw)) {
                __add_issue(info, ecw->issue_severity, ecw->issue_cause, ecw->irisc_id, &ecw->cause_data,
                            &ecw->data.extra_data_event);
            }

            mutex_unlock(&info->lock);
        }
    }

    mutex_unlock(&__health_check_lock);
    kfree(ecw);
}

void sx_health_external_report(u8                                 dev_id,
                               u32                                issue_severity,
                               u32                                issue_cause,
                               u8                                 irisc_id,
                               sxd_health_external_report_data_t *data,
                               const char                        *error_msg)
{
    struct external_cause_work *ecw;

    ecw = kzalloc(sizeof(struct external_cause_work), GFP_ATOMIC);
    if (!ecw) {
        printk(KERN_ERR "Health check:health report allocation failed: dev_id [%u], severity [%u], error [%s]\n",
               dev_id,
               issue_severity,
               ((error_msg) ? error_msg : "N/A"));
        return;
    }

    INIT_WORK(&ecw->w, __external_report_work);
    ecw->dev_id = dev_id;
    ecw->issue_severity = issue_severity;
    ecw->issue_cause = issue_cause;
    ecw->irisc_id = irisc_id;

    if (data) {
        memcpy(&ecw->data, data, sizeof(sxd_health_external_report_data_t));
    }

    if (error_msg) {
        strncpy(ecw->cause_data.external_data.err_msg, error_msg, sizeof(ecw->cause_data.external_data.err_msg) - 1);
    }

    queue_work(__health_check_wq, &ecw->w);
}

void sx_health_external_report_all(u32 issue_severity, u32 issue_cause, const char *error_msg)
{
    sxd_health_external_report_data_t event_ext_data;

    memset(&event_ext_data, 0, sizeof(sxd_health_external_report_data_t));

    sx_health_external_report(DEV_ID_ALL, issue_severity, issue_cause, DBG_ALL_IRICS, &event_ext_data, error_msg);
}

static void __mfde_work(struct work_struct *work)
{
    struct mfde_work                 *mfde_w = container_of(work, struct mfde_work, w);
    struct ku_mfde_reg               *mfde_reg = &mfde_w->mfde;
    struct sx_dev                    *dev = mfde_w->dev;
    struct external_cause_work       *ecw;
    int                               err, index;
    int                               cause_reg, cause_offset, tile;
    uint64_t                          log_ip = 0;
    char                            * assert_string;
    char                              print_message[FW_SOS_LOG_MAX_SIZE] = {0};
    sxd_event_health_notification_t   sdk_health;
    sxd_health_external_report_data_t event_ext_data;
    char                              error_msg[HEALTH_CHECK_EVENT_MSG_MAX] = {0};
    struct sx_health_dev_info        *info = NULL;

    mutex_lock(&__health_check_lock);

    info = __info_find(dev->device_id);
    if (!info) {
        printk(KERN_NOTICE "Health check Disabled: got MFDE event but will not monitor!!!\n");
        mutex_unlock(&__health_check_lock);
        goto out;
    }
    mutex_unlock(&__health_check_lock);

    memset(&sdk_health, 0, sizeof(sdk_health));
    memset(&event_ext_data, 0, sizeof(sxd_health_external_report_data_t));

    sdk_health.irisc_id = mfde_reg->irisc_id;
    sdk_health.severity = SXD_HEALTH_SEVERITY_FATAL;
    sdk_health.cause = SXD_HEALTH_CAUSE_FW;

    switch (mfde_reg->event_id) {
    case SXD_MFDE_EVENT_ID_CRSPACE_TIMEOUT_E:
        log_ip = mfde_reg->event_params.crspace_timeout.log_ip;
        err = __get_kernel_crtimeout_print(print_message, mfde_reg->irisc_id,
                                           mfde_reg->event_params.crspace_timeout.log_id,
                                           mfde_reg->command_type,  dev);
        if (err) {
            printk(KERN_ERR "Health check: failed to get kernel crspace timeout print err =%d\n", err);
            return;
        }
        snprintf(error_msg,
                 sizeof(error_msg),
                 "SXD_HEALTH_FW_FATAL: FW CR Space timeout: irisc_id = [%d], log_address = [0x%x], old_event = [%d], is_yu = [%d], is_iron = [%d], is_main_farm = [%d], log_id = [%d], log_ip = [0x%llx] [%s]\n",
                 mfde_reg->irisc_id,
                 mfde_reg->event_params.crspace_timeout.log_address,
                 mfde_reg->event_params.crspace_timeout.oe,
                 mfde_reg->event_params.crspace_timeout.is_yu,
                 mfde_reg->event_params.crspace_timeout.is_iron,
                 mfde_reg->event_params.crspace_timeout.is_main_farm,
                 mfde_reg->event_params.crspace_timeout.log_id,
                 log_ip,
                 print_message);
        printk(KERN_ERR "%s", error_msg);
        break;

    case SXD_MFDE_EVENT_ID_KVD_IM_STOP_E:
        snprintf(error_msg,
                 sizeof(error_msg),
                 "SXD_HEALTH_FW_FATAL: FW KVM Stopped: irisc_id = [%d],  old_event = [%d], pipe mask = [%d]\n",
                 mfde_reg->irisc_id,
                 mfde_reg->event_params.kvd_im_stop.oe,
                 mfde_reg->event_params.kvd_im_stop.pipes_mask);
        printk(KERN_ERR "%s", error_msg);
        break;

    case SXD_MFDE_EVENT_ID_TEST_E:
        snprintf(error_msg, sizeof(error_msg), "FW test event\n");
        printk(KERN_NOTICE "%s", error_msg);
        break;

    case SXD_MFDE_EVENT_ID_FW_ASSERT_E:

        assert_string = "N/A";
        /* if assert_string from FW is not empty */
        if (mfde_reg->event_params.fw_assert.assert_string[0]) {
            for (index = 0; index < SXD_MFDE_ASSERT_STRING_NUM; index++) {
                mfde_reg->event_params.fw_assert.assert_string[index] =
                    be32_to_cpu(mfde_reg->event_params.fw_assert.assert_string[index]);
            }
            assert_string = (char *)mfde_reg->event_params.fw_assert.assert_string;
            /* make sure string is NULL terminated */
            *(assert_string +
              (SXD_MFDE_ASSERT_STRING_NUM * sizeof(mfde_reg->event_params.fw_assert.assert_string[0]) -
               1)) = '\0';
        }

        snprintf(error_msg,
                 sizeof(error_msg),
                 "SXD_HEALTH_FW_FATAL: FW Assert: assert_string = [%s], irisc_id = [%d], assert id = [0x%x], assert_var0 = [0x%x], assert_var1 = [0x%x], assert_var2 = [0x%x],"
                 " assert_var3 = [0x%x], assert_var4 = [0x%x], assert_existptr = [0x%x], assert_callra = [0x%x],"
                 " ext_synd = [0x%x], old_event = [0x%x], tile_v = [0x%x], tile_index = [0x%x]\n",
                 assert_string,
                 mfde_reg->irisc_id,
                 mfde_reg->event_params.fw_assert.ext_synd,
                 mfde_reg->event_params.fw_assert.assert_var0,
                 mfde_reg->event_params.fw_assert.assert_var1,
                 mfde_reg->event_params.fw_assert.assert_var2,
                 mfde_reg->event_params.fw_assert.assert_var3,
                 mfde_reg->event_params.fw_assert.assert_var4,
                 mfde_reg->event_params.fw_assert.assert_existptr,
                 mfde_reg->event_params.fw_assert.assert_callra,
                 mfde_reg->event_params.fw_assert.ext_synd,
                 mfde_reg->event_params.fw_assert.oe,
                 mfde_reg->event_params.fw_assert.tile_v,
                 mfde_reg->event_params.fw_assert.tile_index);
        if (mfde_reg->event_params.fw_assert.test != FW_SOS_TEST) {
            printk(KERN_ERR "%s", error_msg);
        } else {
            printk(KERN_WARNING "%s", error_msg);
        }

        break;

    case SXD_MFDE_EVENT_ID_FATAL_CAUSE_E:

        cause_reg = mfde_reg->event_params.fatal_cause.cause_id >> 5;
        cause_offset = mfde_reg->event_params.fatal_cause.cause_id & CAUSE_OFFSET_MASK;
        if ((mfde_reg->event_params.fatal_cause.fw_cause) &&
            (mfde_reg->event_params.fatal_cause.cause_id ==
             SXD_MFDE_FW_FATAL_CASUE_ID_CORE_PLL_LOCK_FAILURE_E)) {
            sdk_health.cause = SXD_HEALTH_CAUSE_PLL_E;
        }

        if (true == mfde_reg->event_params.fatal_cause.tile_v) {
            tile = mfde_reg->event_params.fatal_cause.tile_index;
            snprintf(error_msg,
                     sizeof(error_msg),
                     "SXD_HEALTH_FW_FATAL: FW Fatal:fw_cause = [0x%x], cause_id = [0x%x], irisc_id = [%d], tile_index = [0x%x]\n",
                     mfde_reg->event_params.fatal_cause.fw_cause,
                     mfde_reg->event_params.fatal_cause.cause_id,
                     mfde_reg->irisc_id,
                     tile);
            if (mfde_reg->event_params.fatal_cause.test == FW_SOS_TEST) {
                printk(KERN_WARNING " %s", error_msg);
            } else {
                printk(KERN_ERR " %s", error_msg);
            }
        } else {
            /* tile is not valid / no tile */
            snprintf(error_msg,
                     sizeof(error_msg),
                     "SXD_HEALTH_FW_FATAL: FW Fatal:fw_cause = [0x%x], cause_id = [0x%x], irisc_id = [%d]\n",
                     mfde_reg->event_params.fatal_cause.fw_cause,
                     mfde_reg->event_params.fatal_cause.cause_id,
                     mfde_reg->irisc_id);
            if (mfde_reg->event_params.fatal_cause.test == FW_SOS_TEST) {
                printk(KERN_WARNING " %s", error_msg);
            } else {
                printk(KERN_ERR " %s", error_msg);
            }
        }

        break;

    case SXD_MFDE_EVENT_ID_LONG_CMD_TIMEOUT_E:
        snprintf(error_msg,
                 sizeof(error_msg),
                 "SXD_HEALTH_FW_FATAL: FW Long Command Timeout: irisc_id = [%d],  reg_attr_id = [%d], mgmt_class = [%d], method = [%d], \n",
                 mfde_reg->irisc_id,
                 mfde_reg->reg_attr_id,
                 mfde_reg->mgmt_class,
                 mfde_reg->method);
        printk(KERN_ERR "%s", error_msg);
        sdk_health.severity = SXD_HEALTH_SEVERITY_WARN;
        sdk_health.cause = SXD_HEALTH_CAUSE_FW_LONG_COMMAND;
        break;

    default:
        printk(KERN_ERR "Health check: the given event id =%d is out of range", mfde_reg->event_id);
        goto out;
    }


    ecw = kmalloc(sizeof(struct external_cause_work), GFP_KERNEL);
    if (ecw == NULL) {
        printk(KERN_ERR "Health check- failed to allocate work");
        goto out;
    }

    ecw->dev_id = dev->device_id;
    ecw->issue_severity = sdk_health.severity;
    ecw->issue_cause = sdk_health.cause;
    ecw->irisc_id = mfde_reg->irisc_id;
    memcpy(&ecw->data, &event_ext_data, sizeof(sxd_health_external_report_data_t));
    strncpy(ecw->cause_data.external_data.err_msg, error_msg, sizeof(ecw->cause_data.external_data.err_msg) - 1);

    __external_report_work(&ecw->w);

out:
    kfree(mfde_w);
}

void sx_health_check_mfde_error_update(struct ku_mfde_reg *mfde_reg,  struct sx_dev * dev)
{
    struct mfde_work *mfde_w;

    /*must to allocate mfde_W because we move
     *  to new context from atomic (trap flow) to new work that health check will handle */
    mfde_w = kmalloc(sizeof(struct mfde_work), GFP_ATOMIC);
    if (mfde_w == NULL) {
        printk(KERN_ERR "Health check- failed to allocate work");
    }

    INIT_WORK(&mfde_w->w, __mfde_work);
    memcpy(&mfde_w->mfde, mfde_reg, sizeof(struct ku_mfde_reg));
    mfde_w->dev = dev;
    queue_work(__health_check_wq, &mfde_w->w);
}

/*
 * This function is running under the listeners DB lock, which means that 'listener' pointer
 * is valid in the entire flow of this function
 */
void sx_health_handle_new_listener(struct sx_dev *dev, struct listener_entry *listener)
{
    struct sx_health_dev_info *info = NULL;
    struct issue_info         *failure = NULL;
    sxd_health_severity_t      last_sev = SXD_HEALTH_SEVERITY_NOTICE;

    mutex_lock(&__health_check_lock);

    info = __info_find(dev->device_id);
    if (info) {
        mutex_lock(&info->lock);

        list_for_each_entry(failure, &info->issues_list, list) {
            last_sev = failure->severity;
            if (info->config.min_severity >= failure->severity) {
                sx_send_health_event(dev->device_id,
                                     failure->cause,
                                     failure->severity,
                                     failure->irisc_id,
                                     &failure->event_data,
                                     listener);
            }
        }

        if ((last_sev != SXD_HEALTH_SEVERITY_FATAL) && (info->fatal_cause != SXD_HEALTH_CAUSE_NONE)) {
            failure = list_last_entry(&info->issues_list, struct issue_info, list);
            sx_send_health_event(dev->device_id,
                                 info->fatal_cause,
                                 SXD_HEALTH_SEVERITY_FATAL,
                                 failure->irisc_id,
                                 &info->event_extra_data,
                                 listener);
        }

        mutex_unlock(&info->lock);
    }

    mutex_unlock(&__health_check_lock);
}
