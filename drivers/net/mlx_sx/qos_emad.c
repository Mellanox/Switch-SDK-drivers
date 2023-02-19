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

#include "qos_emad.h"
#include "sx.h"
#include "dq.h"
#include <linux/kthread.h>
#include <linux/delay.h>
#include "sx_dbg_dump_proc.h"

#define QOS_CONGESTION_THRESHOLD 5 /* Indicates high priority EMADs congestion*/

/************************************************
 *  Global variables
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

typedef struct emad_queue {
    struct list_head list;
    u32              weight;
    u64              pkts_in_prio_queue;
    u64              pkts_sent_from_prio;
    u64              pkts_send_failures;
    u64              max_pkts_in_prio_queue;
    u64              max_time_in_queue;
    unsigned long    max_time_in_queue_ts;
} emad_queue_t;

typedef struct skb_emad {
    struct sk_buff  *skb;
    struct list_head emad_list;
    struct isx_meta  meta;
    struct sx_dev   *dev;
    unsigned long    since;
} skb_emad_t;


/************************************************
 *  Local variables
 ***********************************************/

static emad_queue_t __emad_queues_arr[EMAD_PRIO_MAX]; /* array of emad queues - for each priority */

static struct semaphore __qos_emad_scheduling_thread_sem; /* thread semaphore - used to signal the thread when the thread is sleeping (if __num_of_emads = 0) */

static struct task_struct *__scheduling_emads_from_queues_thread; /* Thread pointer */

static struct kmem_cache *__emad_skb_cache; /* cache memory to be used for emad allocation when packet is pushed to qos queue */

static u32 __num_of_emads; /* Overall num of emads in the qos queues */

static bool __is_active; /* indicates we are in deinit process so no packets should be pushed to qos queue */

static bool __thread_active; /* Indicates if the thread is active so in deinit process the thread should stop. Otherwise it might sleep forever */

static spinlock_t __emad_queue_lock; /* lock before access shared resource like emad queue or num_of_emads counter */

static unsigned long __last_high_ts; /* timestamp of the last high priority emad sent to SDQ*/

static u32 __high_pkts_in_a_row; /* number of high priority emads sent to SDQ in a row*/

static struct semaphore __high_queue_sem; /* used to signal high priority emad pushed to qos queue*/


/*
 * Emad QoS debug counters
 */

static u64 __max_num_of_emads; /* The maximum number of emads in the qos queues */

static u64 __emads_sent_directly; /* Number of emads pushed directly to the sdq */

static u64 __sched_thread_loops; /* Number of scheduling thread while loops */

static u64 __sched_thread_cont_loops; /* Number of continuous scheduling thread while loops due to non empty queues */


/************************************************
 *  Local function declarations
 ***********************************************/

static void __emad_queues_init(void);

/************************************************
 *  Function implementations
 ***********************************************/

static void __emad_queues_init(void)
{
    int queue_number;

    memset(&__emad_queues_arr, 0, sizeof(emad_queue_t) * EMAD_PRIO_MAX);

    __emad_queues_arr[EMAD_PRIO_LOW].weight = 1;
    __emad_queues_arr[EMAD_PRIO_HIGH].weight = 100;

    for (queue_number = 0; queue_number < EMAD_PRIO_MAX; queue_number++) {
        INIT_LIST_HEAD(&__emad_queues_arr[queue_number].list);
    }
}

static int __qos_emad_queues_scheduling_thread(void *arg)
{
    int                  queue_number;
    int                  err = 0;
    int                  weight = 0;
    skb_emad_t          *emad_to_send = NULL;
    emad_queue_t        *emad_q;
    struct list_head     curr_emad_list;
    bool                 cont;
    u32                  queue_weight = 0;
    unsigned long        now, time_in_queue;
    unsigned long        time_passed;
    static unsigned long __cong_thr;

    pr_debug("starting scheduling emads from queues thread\n");

    __cong_thr = msecs_to_jiffies(QOS_CONGESTION_THRESHOLD);

    INIT_LIST_HEAD(&curr_emad_list);

    while (!kthread_should_stop()) {
        if (__thread_active && down_interruptible(&__qos_emad_scheduling_thread_sem)) {
            continue;
        }

        do {
            cont = false;
            __sched_thread_loops++;

            for (queue_number = EMAD_PRIO_HIGH; queue_number < EMAD_PRIO_MAX; queue_number++) {
                /*
                 * This code was added due to SDK emad synchronous mode.
                 * In synchronous mode the high packets are not aggregated in the qos queue which cause
                 * emad handling that is not aligned with qos queues desired weights.
                 *
                 * In order to guaranty correct weight scheduling, when high emads congestion is detected, the thread waits for
                 * high emad to arrive for certain timeout before switching to low priority emads handling.
                 */
                if (queue_number == EMAD_PRIO_LOW) {
                    now = jiffies;
                    time_passed = now - __last_high_ts;
                    if ((time_passed <= __cong_thr) &&
                        (__high_pkts_in_a_row < __emad_queues_arr[EMAD_PRIO_HIGH].weight)) {
                        if (down_timeout(&__high_queue_sem, __cong_thr - time_passed) != -ETIME) {
                            cont = true;
                            continue;
                        }
                    }
                }

                emad_q = &__emad_queues_arr[queue_number];

                spin_lock_bh(&__emad_queue_lock);

                if (list_empty(&emad_q->list)) {
                    spin_unlock_bh(&__emad_queue_lock);
                    continue;
                }

                if (queue_number == EMAD_PRIO_HIGH) {
                    __last_high_ts = jiffies;
                } else {
                    __high_pkts_in_a_row = 0;
                }

                list_replace_init(&emad_q->list, &curr_emad_list);

                queue_weight = emad_q->weight;

                spin_unlock_bh(&__emad_queue_lock);

                for (weight = 0; weight < queue_weight; weight++) {
                    emad_to_send = list_first_entry_or_null(&curr_emad_list, skb_emad_t, emad_list);
                    if (!emad_to_send) {
                        break;
                    }

                    now = jiffies;
                    time_in_queue = now - emad_to_send->since;
                    if (time_in_queue > emad_q->max_time_in_queue) {
                        emad_q->max_time_in_queue = time_in_queue;
                        emad_q->max_time_in_queue_ts = now;
                    }

                    list_del(&emad_to_send->emad_list);

                    err = __sx_core_post_send(emad_to_send->dev,
                                              emad_to_send->skb,
                                              &emad_to_send->meta,
                                              DONT_FORCE_SDQ_ID);
                    if (err) {
                        printk(KERN_ERR "failed to send emad to the SDQ (err=%d)\n", err);
                        emad_q->pkts_send_failures++;
                    } else {
                        emad_q->pkts_sent_from_prio++;
                    }
                    kmem_cache_free(__emad_skb_cache, emad_to_send);
                }

                spin_lock_bh(&__emad_queue_lock);
                list_splice_init(&curr_emad_list, &emad_q->list);
                __num_of_emads -= weight;
                emad_q->pkts_in_prio_queue -= weight;

                if (queue_number == EMAD_PRIO_HIGH) {
                    __high_pkts_in_a_row += weight;
                }

                if (__num_of_emads > 0) {
                    cont = true;
                }
                spin_unlock_bh(&__emad_queue_lock);
            }
            if (cont) {
                __sched_thread_cont_loops++;
            }
        } while (cont);
    }

    return 0;
}

int sx_qos_emad_init(void)
{
    int err = 0;

    __is_active = true;

    __num_of_emads = 0;

    printk(KERN_INFO "QoS Emad initialization \n");

    sema_init(&__qos_emad_scheduling_thread_sem, 1);

    spin_lock_init(&__emad_queue_lock);

    sema_init(&__high_queue_sem, 1);

    __emad_queues_init();

    __emad_skb_cache = kmem_cache_create("qos_emad", sizeof(skb_emad_t), 0, 0, NULL);

    if (!__emad_skb_cache) {
        printk(KERN_ERR "failed to allocate memory cache for qos emad\n");
        err = -ENOMEM;
        goto out;
    }
    __num_of_emads = 0;
    __max_num_of_emads = 0;
    __emads_sent_directly = 0;
    __sched_thread_loops = 0;
    __sched_thread_cont_loops = 0;
    __last_high_ts = jiffies;
    __high_pkts_in_a_row = 0;

    __thread_active = true;
    __scheduling_emads_from_queues_thread = kthread_run(__qos_emad_queues_scheduling_thread,
                                                        NULL,
                                                        "qos_emad_queues_scheduling_thread");
    if (IS_ERR(__scheduling_emads_from_queues_thread)) {
        err = PTR_ERR(__scheduling_emads_from_queues_thread);
        printk(KERN_ERR "failed to create scheduling emads from queues thread (err=%d)\n", err);
        goto out;
    }

out:
    return err;
}

void sx_qos_emad_deinit(void)
{
    int           queue_number;
    skb_emad_t   *iter_emad, *tmp_emad;
    emad_queue_t *emad_q;

    printk(KERN_INFO "QoS Emad deinit \n");

    spin_lock_bh(&__emad_queue_lock);

    for (queue_number = 0; queue_number < EMAD_PRIO_MAX; queue_number++) {
        emad_q = &__emad_queues_arr[queue_number];

        list_for_each_entry_safe(iter_emad, tmp_emad, &__emad_queues_arr[queue_number].list, emad_list) {
            list_del(&iter_emad->emad_list);
            sx_skb_consume(iter_emad->skb);
            kmem_cache_free(__emad_skb_cache, iter_emad);
        }
    }

    __is_active = false;
    spin_unlock_bh(&__emad_queue_lock);

    __thread_active = false;
    up(&__qos_emad_scheduling_thread_sem);

    up(&__high_queue_sem);

    kthread_stop(__scheduling_emads_from_queues_thread);

    if (__emad_skb_cache) {
        kmem_cache_destroy(__emad_skb_cache);
    }
}

int sx_qos_emad_push_to_queue(struct sx_dev *dev, struct sk_buff  *skb, struct isx_meta *meta, emad_prio_e priority)
{
    int           err = 0;
    skb_emad_t   *skb_p = NULL;
    emad_queue_t *emad_q;
    bool          is_send_without_thread = false;

    if ((int)priority >= EMAD_PRIO_MAX) {
        printk(KERN_ERR "qos emad priority is out of range: [%d], \n", priority);
        err = -ERANGE;
        goto err_out;
    }

    spin_lock_bh(&__emad_queue_lock);

    if ((priority == EMAD_PRIO_HIGH) && (__num_of_emads == 0)) {
        is_send_without_thread = true;
        __emads_sent_directly++;
    }

    spin_unlock_bh(&__emad_queue_lock);

    if (is_send_without_thread) {
        err = __sx_core_post_send(dev,
                                  skb,
                                  meta,
                                  DONT_FORCE_SDQ_ID);
        if (err) {
            printk(KERN_ERR "failed to send emad to the SDQ (err=%d)\n", err);
        }
        goto out;
    }

    emad_q = &__emad_queues_arr[priority];

    skb_p = (skb_emad_t*)kmem_cache_alloc(__emad_skb_cache, GFP_ATOMIC);

    if (!skb_p) {
        err = -ENOMEM;
        printk(KERN_ERR "allocation of spice skb emad failed \n");
        goto err_out;
    }

    skb_p->skb = skb;
    skb_p->dev = dev;
    skb_p->meta = *meta;

    spin_lock_bh(&__emad_queue_lock);

    if (!__is_active) {
        spin_unlock_bh(&__emad_queue_lock);
        err = -EPERM;
        kmem_cache_free(__emad_skb_cache, skb_p);
        goto err_out;
    }

    list_add_tail(&skb_p->emad_list, &emad_q->list);
    emad_q->pkts_in_prio_queue++;
    skb_p->since = jiffies;

    if (emad_q->pkts_in_prio_queue > emad_q->max_pkts_in_prio_queue) {
        emad_q->max_pkts_in_prio_queue = emad_q->pkts_in_prio_queue;
    }

    if (__num_of_emads++ == 0) {
        up(&__qos_emad_scheduling_thread_sem);
    }

    if (__num_of_emads > __max_num_of_emads) {
        __max_num_of_emads = __num_of_emads;
    }

    /* Signal scheduling thread when first emad is pushed to high priority queue */
    if ((priority == EMAD_PRIO_HIGH) && (emad_q->pkts_in_prio_queue == 1)) {
        up(&__high_queue_sem);
    }

    spin_unlock_bh(&__emad_queue_lock);

    goto out;

err_out:
    sx_skb_free(skb);

out:
    return err;
}

int sx_qos_emad_dump(struct seq_file *m, void *v, void *context)
{
    int           queue_number;
    emad_queue_t *emad_q;
    char          header[SX_DBG_DUMP_HEADER_MAX_LEN];
    char          max_time_in_queue[20];
    char          max_time_in_queue_ts[20];
    unsigned long now = jiffies;

    snprintf(header, SX_DBG_DUMP_HEADER_MAX_LEN, "EMAD Quality Of Service dump");
    sx_dbg_dump_print_header(m, header);

    if (__is_active) {
        seq_printf(m,
                   "EMAD QoS mechanism role is to prioritize EMADs sending when EMADs with different priority level exist.\n"
                   "Therefore, when only high priority EMADs exist - EMADs will be sent directly to the SDQ.\n\n");

        spin_lock_bh(&__emad_queue_lock);

        seq_printf(m, "Maximum number of EMADs in the priority queues: %llu\n\n", __max_num_of_emads);
        seq_printf(m, "Number of EMADs sent directly to FW: %llu\n\n", __emads_sent_directly);

        seq_printf(m, "\nQoS Scheduler thread: \n\n");
        seq_printf(m, "Total number of loops: %llu\n", __sched_thread_loops);
        seq_printf(m, "Number of retry loops (due to non-empty priority queues): %llu\n\n", __sched_thread_cont_loops);

        seq_printf(m, "\nHigh packets in a row: %u\n", __high_pkts_in_a_row);

        seq_printf(m, "\nthreshold msec: %u\n", QOS_CONGESTION_THRESHOLD);

        seq_printf(m, "\nQoS Priority Queues Dump: \n\n");

        seq_printf(m,
                   "%-8s  %-8s  %-15s  %-20s  %-22s  %-22s  %-22s  %-22s\n"
                   "----------------------------------------------------------------------------"
                   "----------------------------------------------------------------------------\n",
                   "Prio_Q#", "Weight",
                   "Pkts in Queue", "Max Pkts in Queue",
                   "Pkts Sent to SDQ", "Pkts Send Failures",
                   "Max Time in Q (Msec)", "Max Time TS (sec ago)");

        for (queue_number = EMAD_PRIO_HIGH; queue_number < EMAD_PRIO_MAX; queue_number++) {
            emad_q = &__emad_queues_arr[queue_number];

            snprintf(max_time_in_queue, sizeof(max_time_in_queue), "%u", jiffies_to_msecs(emad_q->max_time_in_queue));

            if (emad_q->max_time_in_queue_ts != 0) {
                snprintf(max_time_in_queue_ts, sizeof(max_time_in_queue_ts), "%u",
                         jiffies_to_msecs(now - emad_q->max_time_in_queue_ts) / 1000);
            } else {
                snprintf(max_time_in_queue_ts, sizeof(max_time_in_queue_ts), "N/A");
            }

            seq_printf(m, "%-8d  %-8u  %-15llu  %-20llu  %-22llu  %-22llu  %-22s  %-22s\n",
                       queue_number, emad_q->weight,
                       emad_q->pkts_in_prio_queue, emad_q->max_pkts_in_prio_queue,
                       emad_q->pkts_sent_from_prio, emad_q->pkts_send_failures,
                       max_time_in_queue, max_time_in_queue_ts);
        }

        spin_unlock_bh(&__emad_queue_lock);
    } else {
        seq_printf(m, "EMAD Quality Of Service Module is inactive\n");
    }

    sx_dbg_dump_print_empty_line(m);

    return 0;
}

int sx_qos_emad_counter_clear(int argc, const char *argv[], void *context)
{
    int           err = 0;
    int           queue_number;
    emad_queue_t *emad_q;

    if (argc != 1) {
        err = -EINVAL;
        goto out;
    }

    for (queue_number = EMAD_PRIO_HIGH; queue_number < EMAD_PRIO_MAX; queue_number++) {
        emad_q = &__emad_queues_arr[queue_number];

        emad_q->max_pkts_in_prio_queue = 0;
        emad_q->max_time_in_queue = 0;
        emad_q->max_time_in_queue_ts = 0;
        emad_q->pkts_sent_from_prio = 0;
        emad_q->pkts_send_failures = 0;
    }

    __max_num_of_emads = 0;
    __emads_sent_directly = 0;
    __sched_thread_loops = 0;
    __sched_thread_cont_loops = 0;

out:
    return err;
}
