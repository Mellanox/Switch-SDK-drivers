/*
 * Copyright (c) 2010-2019,  Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <linux/module.h>

#include <linux/mlx_sx/kernel_user.h>
#include "sx.h"
#include "sgmii_internal.h"
#include "sx_dbg_dump_proc.h"

int use_sgmii = 0;
int sgmii_send_attempts = 3;
module_param_named(sgmii_send_attempts, sgmii_send_attempts, int, 0644);
MODULE_PARM_DESC(sgmii_send_attempts, "how many attempts to send a packet");

int sgmii_cr_send_attempts = 1; /* no retries! */
module_param_named(sgmii_cr_send_attempts, sgmii_cr_send_attempts, int, 0644);
MODULE_PARM_DESC(sgmii_cr_send_attempts, "how many attempts to send a CR packet");

int sgmii_send_interval_msec = 5000; /* 5 seconds */
module_param_named(sgmii_send_interval_msec, sgmii_send_interval_msec, int, 0644);
MODULE_PARM_DESC(sgmii_send_interval_msec, "interval between sending attempts");

int sgmii_cr_send_interval_msec = 100; /* 100 milliseconds */
module_param_named(sgmii_cr_send_interval_msec, sgmii_cr_send_interval_msec, int, 0644);
MODULE_PARM_DESC(sgmii_cr_send_interval_msec, "interval between CR sending attempts");

int sgmii_rx_pps = 50000;
module_param_named(sgmii_rx_pps, sgmii_rx_pps, int, 0644);
MODULE_PARM_DESC(sgmii_rx_pps, "RX packets-per-second rate limiter");

static struct workqueue_struct *__sgmii_worker_thread = NULL;
static atomic_t                 __sgmii_wq_refcnt = ATOMIC_INIT(0);
static struct completion        __sgmii_wq_completion;
static ku_chassis_type_t        __sgmii_chassis_type = KU_CHASSIS_TYPE_INVALID;
static ku_mgmt_board_t          __sgmii_management_board = KU_MGMT_BOARD_INVALID;
static uint8_t                  __sgmii_cqe_ver = 0; /* TODO: use the enum! */
struct sgmii_task {
    struct delayed_work work;
    sgmii_task_t        task;
    uint8_t             user_data[0];
};


uint8_t is_sgmii_supported(void)
{
    return use_sgmii != 0;
}

int sgmii_get_send_attempts_by_transport(sxd_command_type_t transport_type)
{
    int max_attempts = 1;

    switch (transport_type) {
    case SXD_COMMAND_TYPE_CR_ACCESS:
        max_attempts = sgmii_get_cr_send_attempts();
        break;

    default:
        max_attempts = sgmii_get_send_attempts();
        break;
    }
    return max_attempts;
}

int sgmii_get_cr_send_attempts(void)
{
    return sgmii_cr_send_attempts;
}

int sgmii_get_send_interval_msec_by_transport(sxd_command_type_t transport_type)
{
    int interval = 100;

    switch (transport_type) {
    case SXD_COMMAND_TYPE_CR_ACCESS:
        interval = sgmii_get_cr_send_interval_msec();
        break;

    default:
        interval = sgmii_get_send_interval_msec();
        break;
    }
    return interval;
}

int sgmii_get_cr_send_interval_msec(void)
{
    return sgmii_cr_send_interval_msec;
}

int sgmii_get_send_attempts(void)
{
    return sgmii_send_attempts;
}


int sgmii_get_send_interval_msec(void)
{
    return sgmii_send_interval_msec;
}


int sgmii_get_rx_pps(void)
{
    return sgmii_rx_pps;
}


ku_chassis_type_t sgmii_get_chassis_type(void)
{
    return __sgmii_chassis_type;
}


ku_mgmt_board_t sgmii_get_management_board(void)
{
    return __sgmii_management_board;
}


uint8_t sgmii_get_cqe_ver(void)
{
    return __sgmii_cqe_ver;
}

static void __sgmii_wq_handler(struct work_struct *work)
{
    struct delayed_work *dw;
    struct sgmii_task   *sgmii_task;

    dw = to_delayed_work(work);
    sgmii_task = container_of(dw, struct sgmii_task, work);

    sgmii_task->task(sgmii_task->user_data);
    kfree(sgmii_task);
}


static int __sgmii_wq_inc_ref(void)
{
    return atomic_add_return(1, &__sgmii_wq_refcnt) > 1;
}


static void __sgmii_wq_dec_ref(void)
{
    if (atomic_dec_and_test(&__sgmii_wq_refcnt)) {
        complete(&__sgmii_wq_completion);
    }
}


static int __sgmii_wq_init(void)
{
    init_completion(&__sgmii_wq_completion);
    __sgmii_wq_inc_ref();

    __sgmii_worker_thread = create_singlethread_workqueue("sgmii_worker");
    if (!__sgmii_worker_thread) {
        printk(KERN_ERR "failed to create sgmii worker thread\n");
        return -ENOMEM;
    }

    return 0;
}


static void __sgmii_wq_deinit(void)
{
    __sgmii_wq_dec_ref();
    wait_for_completion_interruptible(&__sgmii_wq_completion);

    flush_workqueue(__sgmii_worker_thread);
    destroy_workqueue(__sgmii_worker_thread);

    __sgmii_worker_thread = NULL;
}


int sgmii_queue_task(sgmii_task_t task, const void *param_buff, int param_buff_size, unsigned long delay)
{
    struct sgmii_task *sgmii_task;
    int                ret = -EPERM;

    if (!task ||
        (param_buff_size < 0) ||
        (!param_buff && (param_buff_size > 0)) ||
        (param_buff && (param_buff_size == 0))) {
        return -EINVAL;
    }

    sgmii_task = kmalloc(sizeof(struct sgmii_task) + param_buff_size, GFP_ATOMIC);
    if (!sgmii_task) {
        return -ENOMEM;
    }

    INIT_DELAYED_WORK(&sgmii_task->work, __sgmii_wq_handler);
    sgmii_task->task = task;
    if (param_buff) {
        memcpy(sgmii_task->user_data, param_buff, param_buff_size);
    }

    if (__sgmii_wq_inc_ref()) {
        queue_delayed_work(__sgmii_worker_thread, &sgmii_task->work, delay);
        ret = 0;
    } else {
        printk(KERN_ERR "SGMII workqueue is not active!\n");
        kfree(sgmii_task);
    }

    __sgmii_wq_dec_ref();

    return ret;
}


static int __sgmii_general_info_handler(struct seq_file *m, void *v)
{
    const char       *netdev_name = sgmii_get_netdev_name();
    const char       *chassis_type = "<NOT INITIALIZED>";
    const char       *mgmt_board = "<NOT INITIALIZED>";
    uint8_t           netdev_mac[6] = { 0 };
    ku_mgmt_board_t   mb;
    ku_chassis_type_t ct;

    if (!netdev_name || (netdev_name[0] == '\0')) {
        netdev_name = "<NOT INITIALIZED>";
    } else {
        sgmii_get_netdev_mac(netdev_mac);
    }

    mb = sgmii_get_management_board();
    if (mb == KU_MGMT_BOARD_1) {
        mgmt_board = "Mgmt_1";
    } else if (mb == KU_MGMT_BOARD_2) {
        mgmt_board = "Mgmt_2";
    }

    ct = sgmii_get_chassis_type();
    if (ct == KU_CHASSIS_TYPE_BARRACUDA) {
        chassis_type = "Barracuda";
    } else if (ct == KU_CHASSIS_TYPE_MANTARAY) {
        chassis_type = "Manta Ray";
    }

    seq_printf(m, "----------------------------------------------------------------------\n");
    seq_printf(m, "SGMII general information\n");
    seq_printf(m, "----------------------------------------------------------------------\n");

    seq_printf(m, "Chassis type ................................. %s\n", chassis_type);
    seq_printf(m, "Management board ............................. %s\n", mgmt_board);
    seq_printf(m, "Network interface name ....................... %s\n", netdev_name);
    seq_printf(m, "Network interface MAC address................. %02x:%02x:%02x:%02x:%02x:%02x\n",
               netdev_mac[0], netdev_mac[1], netdev_mac[2], netdev_mac[3], netdev_mac[4], netdev_mac[5]);
    seq_printf(m, "Maximum CR send attempts ......................%d\n", sgmii_get_cr_send_attempts());
    seq_printf(m, "Interval between CR send attempts (in msec) ...%d\n", sgmii_get_cr_send_interval_msec());
    seq_printf(m, "Maximum send attempts ........................ %d\n", sgmii_get_send_attempts());
    seq_printf(m, "Interval between send attempts (in msec) ..... %d\n", sgmii_get_send_interval_msec());
    seq_printf(m, "Rate limiter (Packets-per-Second):\n");
    seq_printf(m, "    Configured ............................... %d\n", sgmii_get_rx_pps());
    seq_printf(m, "    Operational (remaining)................... %d\n", sgmii_get_operational_rx_pps());
    seq_printf(m, "Transactions in progress:\n");
    seq_printf(m, "    EMAD ..................................... %d\n", sgmii_emad_get_transactions_in_progress());
    seq_printf(m, "    MAD ...................................... %d\n", sgmii_mad_get_transactions_in_progress());
    seq_printf(m, "    CR-Space ................................. %d\n",
               sgmii_cr_space_get_transactions_in_progress());

    return 0;
}


void __sgmii_global_counters_init(void)
{
    sx_core_counter_category_init(&__sgmii_global_counters.category, "sgmii-global");

    sx_core_counter_init(&__sgmii_global_counters.category,
                         &__sgmii_global_counters.tx_not_sgmii_dev,
                         "TX - Not a SGMII device",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&__sgmii_global_counters.category,
                         &__sgmii_global_counters.tx_default_device_not_configured,
                         "TX - default device is not configured",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&__sgmii_global_counters.category,
                         &__sgmii_global_counters.tx_mad_deferred_send_failed,
                         "TX - MAD deferred packet send failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&__sgmii_global_counters.category,
                         &__sgmii_global_counters.rx_no_encap_header,
                         "RX - Encapsulation header corrupted",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&__sgmii_global_counters.category,
                         &__sgmii_global_counters.rx_rate_limiter,
                         "RX - Rate limiter notice",
                         COUNTER_SEV_NOTICE);
    sx_core_counter_init(&__sgmii_global_counters.category,
                         &__sgmii_global_counters.rx_skb_share_check_failed,
                         "RX - skb_share_check() failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&__sgmii_global_counters.category,
                         &__sgmii_global_counters.rx_skb_fragmented,
                         "RX - skb is fragmented",
                         COUNTER_SEV_INFO);
    sx_core_counter_init(&__sgmii_global_counters.category,
                         &__sgmii_global_counters.rx_skb_linearize_failed,
                         "RX - skb_linearize() failed",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&__sgmii_global_counters.category,
                         &__sgmii_global_counters.rx_src_mac_not_found,
                         "RX - Source MAC mismatch",
                         COUNTER_SEV_ERROR);
    sx_core_counter_init(&__sgmii_global_counters.category,
                         &__sgmii_global_counters.rx_zero_src_mac,
                         "RX - Zero source MAC address",
                         COUNTER_SEV_ERROR);
}


void __sgmii_global_counters_deinit(void)
{
    sx_core_counter_deinit(&__sgmii_global_counters.tx_not_sgmii_dev);
    sx_core_counter_deinit(&__sgmii_global_counters.tx_default_device_not_configured);
    sx_core_counter_deinit(&__sgmii_global_counters.tx_mad_deferred_send_failed);
    sx_core_counter_deinit(&__sgmii_global_counters.rx_no_encap_header);
    sx_core_counter_deinit(&__sgmii_global_counters.rx_rate_limiter);
    sx_core_counter_deinit(&__sgmii_global_counters.rx_skb_share_check_failed);
    sx_core_counter_deinit(&__sgmii_global_counters.rx_skb_fragmented);
    sx_core_counter_deinit(&__sgmii_global_counters.rx_skb_linearize_failed);
    sx_core_counter_deinit(&__sgmii_global_counters.rx_src_mac_not_found);
    sx_core_counter_deinit(&__sgmii_global_counters.rx_zero_src_mac);
    sx_core_counter_category_deinit(&__sgmii_global_counters.category);
}


int sgmii_set_system_cfg(const struct ku_sgmii_system_cfg *sgmii_system_cfg)
{
    int ret;

    if (sgmii_system_cfg->netdev_name[0] == '\0') {
        printk(KERN_ERR "SGMII netdev name cannot be empty!\n");
        return -EINVAL;
    }

    if (ZERO_MAC(sgmii_system_cfg->netdev_mac)) {
        printk(KERN_ERR "SGMII netdev mac cannot be all-zeros\n");
        return -EINVAL;
    }

    if ((sgmii_system_cfg->chassis_type != KU_CHASSIS_TYPE_BARRACUDA) &&
        (sgmii_system_cfg->chassis_type != KU_CHASSIS_TYPE_MANTARAY)) {
        printk(KERN_ERR "SGMII chassis type is invalid\n");
        return -EINVAL;
    }

    if ((sgmii_system_cfg->mgmt_board != KU_MGMT_BOARD_1) &&
        (sgmii_system_cfg->mgmt_board != KU_MGMT_BOARD_2)) {
        printk(KERN_ERR "SGMII management board number is invalid\n");
        return -EINVAL;
    }
    /* TODO: use the enum! */
    if ((sgmii_system_cfg->cqe_ver != 0) && (sgmii_system_cfg->cqe_ver != 2)) {
        printk(KERN_ERR "SGMII CQE version is invalid\n");
        return -EINVAL;
    }

    ret = sgmii_init();
    if (ret) {
        printk(KERN_ERR "failed in sgmii_init() (ret=%d)\n", ret);
        return ret;
    }

    __sgmii_chassis_type = sgmii_system_cfg->chassis_type;
    __sgmii_management_board = sgmii_system_cfg->mgmt_board;
    __sgmii_cqe_ver = sgmii_system_cfg->cqe_ver;
    ret = sgmii_transport_init(sgmii_system_cfg->netdev_name,
                               sgmii_system_cfg->netdev_mac,
                               __sgmii_chassis_type,
                               __sgmii_cqe_ver);

    if (ret == 0) {
        /* set MAD DPT path to SGMII for the default device (255). In this way, when default device calls sxd_dpt_send(),
         * the flow will take it to SGMII and not PCI/I2C */
        sx_glb.sx_dpt.dpt_info[DEFAULT_DEVICE_ID].is_ifc_valid[DPT_PATH_SGMII] = 1;
        ret = sx_dpt_set_mad_path(DEFAULT_DEVICE_ID, DPT_PATH_SGMII);
        if (ret) {
            printk(KERN_ERR "failed to set MAD path to SGMII on default device (%d)\n", DEFAULT_DEVICE_ID);
        }

        ret = sx_dpt_set_cr_access_path(DEFAULT_DEVICE_ID, DPT_PATH_SGMII);
        if (ret) {
            printk(KERN_ERR "failed to set CR-Access path to SGMII on default device (%d)\n", DEFAULT_DEVICE_ID);
        }
    }

    return ret;
}


int sgmii_init(void)
{
    int ret;

    ret = sx_dbg_dump_proc_fs_register("sgmii_general_info", __sgmii_general_info_handler, NULL);
    if (ret) {
        return ret;
    }

    ret = sgmii_dev_db_init();
    if (ret) {
        goto dev_db_init_failed;
    }

    ret = sgmii_emad_init();
    if (ret) {
        goto emad_init_failed;
    }

    ret = sgmii_mad_init();
    if (ret) {
        goto mad_init_failed;
    }

    ret = sgmii_cr_space_init();
    if (ret) {
        goto cr_space_init_failed;
    }

    ret = __sgmii_wq_init();
    if (ret) {
        printk(KERN_ERR "failed to create sgmii worker thread\n");
        goto sgmii_worker_failed;
    }

    __sgmii_global_counters_init();
    use_sgmii = 1;
    return 0;

sgmii_worker_failed:
    sgmii_cr_space_deinit();

cr_space_init_failed:
    sgmii_mad_deinit();

mad_init_failed:
    sgmii_emad_deinit();

emad_init_failed:
    sgmii_dev_db_deinit();

dev_db_init_failed:
    sx_dbg_dump_proc_fs_unregister("sgmii_general_info");
    return ret;
}


void sgmii_deinit(void)
{
    __sgmii_wq_deinit();

    sx_dbg_dump_proc_fs_unregister("sgmii_general_info");

    sgmii_cr_space_deinit();
    sgmii_mad_deinit();
    sgmii_emad_deinit();
    sgmii_dev_db_deinit();
    sgmii_transport_deinit();

    __sgmii_global_counters_deinit();
    use_sgmii = 0;
}
