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

#include <linux/clocksource.h>
#include <linux/pci.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/ptp_classify.h>
#include <linux/interrupt.h>
#include <linux/udp.h>
#include <linux/ipv6.h>
#include <linux/kthread.h>
#include <linux/if_vlan.h>
#include <net/sock.h>
#include "sx_clock.h"
#include "cq.h"
#include <linux/version.h>
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0) && (defined(RHEL_MAJOR) && defined(RHEL_MINOR) && RHEL_MAJOR == 7 && \
    (RHEL_MINOR == 2 || RHEL_MINOR == 3)))
    #include <linux/timecounter.h>
#endif

#define PTP_GC_TIME         (5 * HZ) /* Event with age of more than 5 seconds should be garbage-collected */
#define PTP_LATE_MATCH_TIME (HZ / 4) /* matching after 1/4 second or longer is 'late match' */

extern struct sx_globals        sx_glb;
struct sx_priv                 *__priv = NULL;
static struct kmem_cache       *__records_cache;
static struct kmem_cache       *__rx_event_cache;
static struct kmem_cache       *__tx_event_cache;
static struct task_struct      *__ptp_rx_polling_thread;
static struct workqueue_struct *__ptp_wq;
static struct delayed_work      __gc_dwork;
static struct delayed_work      __per_sec_dwork;
static struct delayed_work      __set_hw_time_dwork;
struct ptp_record {
    struct list_head     list;
    unsigned long        since;
    struct mtpptr_record mtpptr;
};
struct ptp_db     ptp_tx_db;
struct ptp_db     ptp_rx_db;
ptp_mode_t        ptp_working_mode = KU_PTP_MODE_DISABLED;
struct semaphore  ptp_polling_sem;
atomic64_t        ptp_rx_budget[PTP_MAX_PORTS];
atomic64_t        ptp_tx_budget[PTP_MAX_PORTS];
atomic64_t        ptp_counters[2][PTP_COUNTER_LAST];
static atomic64_t ptp_records_dist[2][SX_MAX_PTP_RECORDS + 1];
static void __gc_db(int sysport, struct ptp_db *db, u8 gc_all)
{
    struct ptp_common_event_data *iter_common, *tmp_common;
    struct ptp_record            *iter_rec, *tmp_rec;
    unsigned long                 now = jiffies;

    spin_lock_bh(&db->sysport_lock[sysport]);

    list_for_each_entry_safe(iter_common, tmp_common, &db->sysport_events_list[sysport], list) {
        if (gc_all || time_after(now, iter_common->since + PTP_GC_TIME)) {
            list_del(&iter_common->list);
            db->gc_cb(iter_common);
            atomic64_inc(&ptp_counters[db->direction][PTP_COUNTER_GC_EVENTS]);
            atomic64_dec(&ptp_counters[db->direction][PTP_COUNTER_PENDING_EVENTS]);
        } else {
            break; /* events are placed in the list in chronological order */
        }
    }

    list_for_each_entry_safe(iter_rec, tmp_rec, &db->sysport_records_list[sysport], list) {
        if (gc_all || time_after(now, iter_rec->since + PTP_GC_TIME)) {
            list_del(&iter_rec->list);
            kmem_cache_free(__records_cache, iter_rec);
            atomic64_inc(&ptp_counters[db->direction][PTP_COUNTER_GC_RECORDS]);
            atomic64_dec(&ptp_counters[db->direction][PTP_COUNTER_PENDING_RECORDS]);
        } else {
            break; /* records are placed in the list in chronological order */
        }
    }

    spin_unlock_bh(&db->sysport_lock[sysport]);
}


/* garbage collection for RX/TX events and records */
static void __gc(struct work_struct *work)
{
    int sysport;

    for (sysport = 0; sysport < PTP_MAX_PORTS; sysport++) {
        __gc_db(sysport, &ptp_rx_db, 0);
        __gc_db(sysport, &ptp_tx_db, 0);
    }

    queue_delayed_work(__priv->dev.generic_wq, &__gc_dwork, PTP_GC_TIME);
}


static void __ptp_reset_budget(void)
{
    int i;

    for (i = 0; i < PTP_MAX_PORTS; i++) {
        atomic64_set(&ptp_rx_budget[i], PTP_RX_MAX_PPS_PER_PORT);
    }

    for (i = 0; i < PTP_MAX_PORTS; i++) {
        atomic64_set(&ptp_tx_budget[i], PTP_TX_MAX_PPS_PER_PORT);
    }
}


static u64 sx_read_hw_internal_timer(const struct cyclecounter *cc)
{
    struct sx_tstamp *tstamp = container_of(cc, struct sx_tstamp, cycles);
    u64               hw_time = 0, hw_time_h = 0, hw_time_l = 0;

    /* For mitigating lsb wrap-around it is recommended to read the
     * free_running_clock_high, free_running_clock_low, free_running_clock_high.
     * If the 2 high values are different then we do a re-read */
    hw_time_h = __raw_readl(sx_priv(tstamp->dev)->ptp_hw_frc_base + 4);
    hw_time_l = __raw_readl(sx_priv(tstamp->dev)->ptp_hw_frc_base);
    if (hw_time_h != __raw_readl(sx_priv(tstamp->dev)->ptp_hw_frc_base + 4)) {
        hw_time_h = __raw_readl(sx_priv(tstamp->dev)->ptp_hw_frc_base + 4);
        hw_time_l = __raw_readl(sx_priv(tstamp->dev)->ptp_hw_frc_base);
    }

    hw_time = hw_time_h << 32 | hw_time_l;
    return swab64(hw_time) & cc->mask;
}


#ifndef __PPC__

/* SHOULD BE CALLED UNDER timecounter LOCK! */
static cycle_t __ns2cyc(const struct timecounter *tc, s64 nsec)
{
    nsec <<= tc->cc->shift;
    nsec = div_u64(nsec, tc->cc->mult);

    return (cycle_t)nsec;
}


static void __set_hw_time(struct work_struct *work)
{
    struct sx_tstamp          *tstamp = &__priv->tstamp;
    struct ku_access_mtpps_reg reg_mtpps;
    struct ku_access_mtutc_reg reg_mtutc;
    cycle_t                    curr_frc, pps_frc;
    u64                        curr_nsec = 0, nsec_till_full_sec;
    int                        freq_adj;
    bool                       time_adj;
    int                        err;

/* if we're in the 9/10 of a sec or higher, it is too close for use. wait for next second */
#define TOO_CLOSE_TO_NEXT_SEC (NSEC_PER_SEC / 10)

find_good_timing:

    spin_lock_bh(&tstamp->lock);

    curr_frc = (cycle_t)sx_read_hw_internal_timer(&tstamp->cycles);
    curr_nsec = timecounter_cyc2time(&tstamp->clock, curr_frc);
    nsec_till_full_sec = NSEC_PER_SEC - ((curr_nsec) % (NSEC_PER_SEC));

    if (nsec_till_full_sec <= TOO_CLOSE_TO_NEXT_SEC) {
        spin_unlock_bh(&tstamp->lock);
        msleep(100);
        goto find_good_timing;
    }

    freq_adj = tstamp->freq_adj;
    time_adj = tstamp->time_adj;
    tstamp->freq_adj = 0;
    tstamp->time_adj = false;

    spin_unlock_bh(&tstamp->lock);

    if (!time_adj && (freq_adj == 0)) {
        goto out;
    }

    pps_frc = curr_frc + __ns2cyc(&tstamp->clock, nsec_till_full_sec);

    /* SET PPS */
    memset(&reg_mtpps, 0, sizeof(reg_mtpps));
    reg_mtpps.dev_id = tstamp->dev->device_id;
    sx_cmd_set_op_tlv(&reg_mtpps.op_tlv, MTPPS_REG_ID, EMAD_METHOD_WRITE);
    reg_mtpps.mtpps_reg.enable = 1;
    reg_mtpps.mtpps_reg.pin_mode = 2; /* virtual pin */
    reg_mtpps.mtpps_reg.pin = 7; /* 7 is the only pin we can work on */
    reg_mtpps.mtpps_reg.time_stamp = pps_frc;
    err = sx_ACCESS_REG_MTPPS(tstamp->dev, &reg_mtpps);
    if (err) {
        printk(KERN_ERR "sx_ACCESS_REG_MTPPS (set_pps) returned with error %d\n", err);
    }

    if (freq_adj != 0) {
        /* ADJUST FREQ */
        memset(&reg_mtutc, 0, sizeof(reg_mtutc));
        reg_mtutc.dev_id = tstamp->dev->device_id;
        sx_cmd_set_op_tlv(&reg_mtutc.op_tlv, MTUTC_REG_ID, EMAD_METHOD_WRITE);
        reg_mtutc.mtutc_reg.operation = 3; /* ADJUST_FREQ */
        reg_mtutc.mtutc_reg.freq_adjustment = freq_adj;
        err = sx_ACCESS_REG_MTUTC(tstamp->dev, &reg_mtutc);
        if (err) {
            printk(KERN_ERR "sx_ACCESS_REG_MTUTC (adj_freq) returned with error %d\n", err);
        }
    }

    /* SET TIME */
    memset(&reg_mtutc, 0, sizeof(reg_mtutc));
    reg_mtutc.dev_id = tstamp->dev->device_id;
    sx_cmd_set_op_tlv(&reg_mtutc.op_tlv, MTUTC_REG_ID, EMAD_METHOD_WRITE);
    reg_mtutc.mtutc_reg.operation = 0; /* SET_TIME_AT_NEXT_SEC */
    reg_mtutc.mtutc_reg.utc_sec = curr_nsec / NSEC_PER_SEC + 1;
    err = sx_ACCESS_REG_MTUTC(tstamp->dev, &reg_mtutc);
    if (err) {
        printk(KERN_ERR "sx_ACCESS_REG_MTUTC (set_time) returned with error %d\n", err);
    }

out:

    queue_delayed_work(__ptp_wq, &__set_hw_time_dwork, HZ);
}
#else /* __PPC__ */
static void __set_hw_time(struct work_struct *work)
{
}
#endif /* __PPC__ */


/* This function runs once per second */
static void __per_sec(struct work_struct *work)
{
    __ptp_reset_budget();
    queue_delayed_work(__priv->dev.generic_wq, &__per_sec_dwork, HZ);
}


int sx_ptp_pkt_parse(struct sk_buff *skb, u8 *is_ptp, u16 *evt_seqid, u8 *evt_domnum, u8 *evt_msgtype)
{
    u16             *seqid_p;
    unsigned int     offset = 0, is_ptp_pkt = 0;
    u8              *msgtype_p, *domnum_p, *data = skb->data;
    struct vlan_hdr *vhdr = NULL;
    struct udphdr   *udp = NULL;
    struct ethhdr   *ehdr = (struct ethhdr *)data;
    struct iphdr    *ip_hdr = NULL;
    struct ipv6hdr  *ip6_hdr = NULL;
    u16              ether_type = be16_to_cpu(ehdr->h_proto);

    offset += ETH_HLEN;

    /*PTP_V2_VLAN*/
    if (ether_type == ETH_P_8021Q) {
        vhdr = (struct vlan_hdr *)(data + offset);
        offset += VLAN_HLEN;
        ether_type = be16_to_cpu(vhdr->h_vlan_encapsulated_proto);
    }

    switch (ether_type) {
    case ETH_P_1588:    /*PTP_V2_L2*/
        is_ptp_pkt = 1;
        break;

    case ETH_P_IP:    /*PTP_V2_IPV4*/
        ip_hdr = (struct iphdr *)(data + offset);
        if (ip_hdr->protocol == IPPROTO_UDP) {
            udp = (struct udphdr *)(data + offset + (ip_hdr->ihl << 2));
            if (be16_to_cpu(udp->dest) == 319) {
                offset += (ip_hdr->ihl << 2) + UDP_HLEN;
                is_ptp_pkt = 1;
            }
        }
        break;

    case ETH_P_IPV6:    /*PTP_V2_IPV6*/
        ip6_hdr = (struct ipv6hdr *)(data + offset);
        if (ip6_hdr->nexthdr == IPPROTO_UDP) {
            udp = (struct udphdr *)(data + offset + IP6_HLEN);
            if (be16_to_cpu(udp->dest) == 319) {
                offset += IP6_HLEN + UDP_HLEN;
                is_ptp_pkt = 1;
            }
        }
        break;

    default:
        if (is_ptp != NULL) {
            *is_ptp = is_ptp_pkt;
        }
        return -1;
    }

    if (skb->len + ETH_HLEN < offset + OFF_PTP_SEQUENCE_ID + sizeof(*seqid_p)) {
        return -1;
    }

    msgtype_p = data + offset;
    seqid_p = (u16*)(data + offset + OFF_PTP_SEQUENCE_ID);
    domnum_p = (u8*)(data + offset + OFFSET_PTP_DOMAIN_NUMBER);

    if (is_ptp != NULL) {
        *is_ptp = is_ptp_pkt;
    }

    if (evt_seqid != NULL) {
        *evt_seqid = ntohs(*seqid_p);
    }

    if (evt_msgtype != NULL) {
        *evt_msgtype = *msgtype_p & 0xf;
    }

    if (evt_domnum != NULL) {
        *evt_domnum = *domnum_p;
    }

    return 0;
}


void sx_fill_hwstamp(struct sx_tstamp *tstamp, u64 timestamp, struct skb_shared_hwtstamps *hwts)
{
    u64           nsec;
    unsigned long flags;

    spin_lock_irqsave(&tstamp->lock, flags);
    nsec = timecounter_cyc2time(&tstamp->clock, timestamp);
    spin_unlock_irqrestore(&tstamp->lock, flags);

    memset(hwts, 0, sizeof(*hwts));
    hwts->hwtstamp = ns_to_ktime(nsec);
}


static int sx_ptp_adjtime(struct ptp_clock_info *ptp, s64 delta)
{
    struct sx_tstamp *tstamp = container_of(ptp, struct sx_tstamp, ptp_info);

    spin_lock_bh(&tstamp->lock);
    tstamp->clock.nsec += delta;
    tstamp->time_adj = true;
    spin_unlock_bh(&tstamp->lock);
    return 0;
}

static int sx_ptp_adjfreq(struct ptp_clock_info *ptp, s32 delta)
{
    struct sx_tstamp *tstamp = container_of(ptp, struct sx_tstamp, ptp_info);
    u64               adj;
    u32               diff;
    int               neg_adj = 0;

    if (delta < 0) {
        neg_adj = 1;
        delta = -delta;
    }

    if (delta > ptp->max_adj) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "sx_ptp_adjfreq: "
                   "Cannot adjust the clock with delta %u greater than max %u\n",
                   delta, ptp->max_adj);
        }
        return -EINVAL;
    }

    adj = tstamp->nominal_c_mult;
    adj *= delta;
    diff = div_u64(adj, NSEC_PER_SEC);
    spin_lock_bh(&tstamp->lock);
    timecounter_read(&tstamp->clock);
    tstamp->cycles.mult = neg_adj ? tstamp->nominal_c_mult - diff :
                          tstamp->nominal_c_mult + diff;
    tstamp->freq_adj += delta;
    spin_unlock_bh(&tstamp->lock);
    return 0;
}

static int sx_ptp_gettime(struct ptp_clock_info *ptp, struct timespec *ts)
{
    struct sx_tstamp *tstamp = container_of(ptp, struct sx_tstamp, ptp_info);
    u64               ns;

    spin_lock_bh(&tstamp->lock);
    ns = timecounter_read(&tstamp->clock);
    spin_unlock_bh(&tstamp->lock);
    *ts = ns_to_timespec(ns);

    return 0;
}


static int sx_ptp_settime(struct ptp_clock_info *ptp, const struct timespec *ts)
{
    struct sx_tstamp *tstamp = container_of(ptp, struct sx_tstamp, ptp_info);
    u64               ns = timespec_to_ns(ts);

    spin_lock_bh(&tstamp->lock);
    timecounter_init(&tstamp->clock, &tstamp->cycles, ns);
    tstamp->time_adj = true;
    spin_unlock_bh(&tstamp->lock);
    return 0;
}


static void sx_timestamp_overflow(struct work_struct *work)
{
    struct delayed_work *dwork = to_delayed_work(work);
    struct sx_tstamp    *tstamp = container_of(dwork, struct sx_tstamp,
                                               overflow_work);
    unsigned long flags;

    spin_lock_irqsave(&tstamp->lock, flags);
    timecounter_read(&tstamp->clock);
    spin_unlock_irqrestore(&tstamp->lock, flags);

    queue_delayed_work(tstamp->dev->generic_wq, &tstamp->overflow_work, tstamp->overflow_period);
}

static const struct ptp_clock_info sx_ptp_clock_info = {
    .owner = THIS_MODULE,
    .max_adj = 100000000,    /* Max adjacency of 100ms */
    .n_alarm = 0,
    .n_ext_ts = 0,
    .n_per_out = 0,
    .pps = 0,
    .adjfreq = sx_ptp_adjfreq,
    .adjtime = sx_ptp_adjtime,
    .gettime = sx_ptp_gettime,
    .settime = sx_ptp_settime,
    .enable = NULL,
};
static int sx_timestamp_init(struct sx_priv *priv)
{
    struct sx_tstamp *tstamp = &priv->tstamp;
    struct sx_dev    *dev = &priv->dev;
    u64               ns;

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0) && (defined(RHEL_MAJOR) && defined(RHEL_MINOR) && RHEL_MAJOR == 7 && \
    (RHEL_MINOR == 2 || RHEL_MINOR == 3)))
    u64 frac = 0;
#endif

    spin_lock_init(&tstamp->lock);
    tstamp->cycles.read = sx_read_hw_internal_timer;

    /*
     *  This value is being calculated on newer kernel versions using the function clocks_calc_mult_shift
     *  with parameters:
     *  from: frequency to convert from. On Spectrum, from=156257000 (6.4nSec)
     *  to: frequency to convert to. On our usage, to=1000000000L
     *  maxsec guaranteed runtime conversion range in second, according to arch, On Spectrum, max_sec=2
     *
     *  This is the necessary shift value to convert the HW clock to UTC without a wraparound
     * */
    tstamp->cycles.shift = 29;

    tstamp->cycles.mult = clocksource_khz2mult(SPC_PTP_CLOCK_FREQ_KHZ,
                                               tstamp->cycles.shift);

    tstamp->nominal_c_mult = tstamp->cycles.mult;
    tstamp->freq_adj = 0;
    tstamp->time_adj = false;
    tstamp->cycles.mask = CLOCKSOURCE_MASK(64);
    tstamp->dev = &priv->dev;

    timecounter_init(&tstamp->clock, &tstamp->cycles,
                     ktime_to_ns(ktime_get_real()));

    /* Calculate period in seconds to call the overflow watchdog - to make
     * sure counter is checked at least once every wrap around.
     */

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0) && (defined(RHEL_MAJOR) && defined(RHEL_MINOR) && RHEL_MAJOR == 7 && \
    (RHEL_MINOR == 2 || RHEL_MINOR == 3)))
    ns = cyclecounter_cyc2ns(&tstamp->cycles, tstamp->cycles.mask, frac, &frac);
#else
    ns = cyclecounter_cyc2ns(&tstamp->cycles, tstamp->cycles.mask);
#endif

    do_div(ns, NSEC_PER_SEC / 2 / HZ);

    /* keep periodic read from clock every 1/8 second and avoid it from wrap-around */
    tstamp->overflow_period = HZ / 8;

    INIT_DELAYED_WORK(&tstamp->overflow_work, sx_timestamp_overflow);

    if (tstamp->overflow_period) {
        queue_delayed_work(dev->generic_wq, &tstamp->overflow_work, 0);
    } else {
        sx_warn(dev, "invalid overflow period, overflow_work is not scheduled.\n");
    }

    /* Register PTP clock */
    tstamp->ptp_info = sx_ptp_clock_info;
    snprintf(tstamp->ptp_info.name, 16, "sx_ptp");

#ifndef __PPC__
    tstamp->ptp = ptp_clock_register(&tstamp->ptp_info,
                                     &priv->dev.pdev->dev);
    if (IS_ERR(tstamp->ptp)) {
        sx_err(dev, "Failed to register ptp clock.\n");
        tstamp->ptp = NULL;
        return -EINVAL;
    }
#endif

    tstamp->is_ptp_enable = 1;

    return 0;
}

static int sx_timestamp_cleanup(struct sx_priv *priv)
{
#ifndef __PPC__
    if (priv->tstamp.ptp) {
        ptp_clock_unregister(priv->tstamp.ptp);
        priv->tstamp.ptp = NULL;
    }
#endif

    priv->tstamp.is_ptp_enable = 0;

    cancel_delayed_work_sync(&priv->tstamp.overflow_work);

    return 0;
}


static void __ptp_event_handler_rx(struct ptp_common_event_data *ced, u64 frc)
{
    struct ptp_rx_event_data *rx_event_data;

    rx_event_data = container_of(ced, struct ptp_rx_event_data, common);

    if (frc != 0) {
        sx_fill_hwstamp(&__priv->tstamp, frc, skb_hwtstamps(rx_event_data->ci->skb));
    } else if (ced->need_timestamp) {
        atomic64_inc(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_EMPTY_TS]);
    }

    dispatch_pkt(&__priv->dev, rx_event_data->ci, rx_event_data->ci->hw_synd, 1);
    ptp_free_rx_event_data(rx_event_data);
}


static void __ptp_gc_cb_rx(struct ptp_common_event_data *ced)
{
    struct ptp_rx_event_data *rx_event_data;

    rx_event_data = container_of(ced, struct ptp_rx_event_data, common);
    ptp_free_rx_event_data(rx_event_data);
}


static void __ptp_event_handler_tx(struct ptp_common_event_data *ced, u64 frc)
{
    struct skb_shared_hwtstamps hwts;
    struct ptp_tx_event_data   *tx_event_data;

    tx_event_data = container_of(ced, struct ptp_tx_event_data, common);

    if (frc != 0) {
        sx_fill_hwstamp(&__priv->tstamp, frc, &hwts);
        skb_tstamp_tx(tx_event_data->skb, &hwts);
    } else {
        skb_tstamp_tx(tx_event_data->skb, NULL);
        atomic64_inc(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_EMPTY_TS]);
    }

    ptp_free_tx_event_data(tx_event_data);
}


static void __ptp_gc_cb_tx(struct ptp_common_event_data *ced)
{
    struct ptp_tx_event_data *tx_event_data;

    tx_event_data = container_of(ced, struct ptp_tx_event_data, common);
    ptp_free_tx_event_data(tx_event_data);
}


void ptp_dequeue_general_messages(u8 local_port, struct ptp_db *db)
{
    struct ptp_common_event_data *ced, *tmp;

    list_for_each_entry_safe(ced, tmp, &db->sysport_events_list[local_port], list) {
        if (ced->need_timestamp) {
            break;
        }

        list_del(&ced->list);
        atomic64_dec(&ptp_counters[db->direction][PTP_COUNTER_PENDING_EVENTS]);
        db->handle_cb(ced, 0);
    }
}


static u8 __match_record_with_event(const struct mtpptr_record *record, u8 local_port, struct ptp_db *db)
{
    struct ptp_common_event_data *ced, *found = NULL;
    u64                           frc;

    list_for_each_entry(ced, &db->sysport_events_list[local_port], list) {
        if (ced->need_timestamp &&
            (record->domain_number == ced->domain_num) &&
            (record->message_type == ced->msg_type) &&
            (be16_to_cpu(record->sequence_id) == ced->sequence_id)) {
            found = ced;
            break;
        }
    }

    if (!found) {
        return 0;
    }

    do {
        ced = list_entry(db->sysport_events_list[local_port].next, struct ptp_common_event_data, list);

        if (ced == found) {
            frc = be64_to_cpu(record->timestamp);

            if (time_after(jiffies, ced->since + PTP_LATE_MATCH_TIME)) {
                atomic64_inc(&ptp_counters[db->direction][PTP_COUNTER_LATE_MATCH]);
            }
        } else {
            frc = 0;
        }

        list_del(&ced->list);
        atomic64_dec(&ptp_counters[db->direction][PTP_COUNTER_PENDING_EVENTS]);
        db->handle_cb(ced, frc);
    } while (ced != found);

    return 1;
}


void ptp_lookup_event(const u8 *mtpptr_buff, struct ptp_db *db)
{
    const struct mtpptr_record *record;
    struct ptp_record          *rec, *tmp_rec;
    struct ptp_record          *to_cache;
    u8                          local_port;
    u8                          ovf;
    u8                          num_rec;
    u8                          found;
    int                         i;

    local_port = mtpptr_buff[1];
    ovf = !!mtpptr_buff[7];
    num_rec = mtpptr_buff[11];
    record = (struct mtpptr_record*)&mtpptr_buff[16];

    if (ovf) {
        atomic64_inc(&ptp_counters[db->direction][PTP_COUNTER_FIFO_OVERFLOW]);
    }

    if ((num_rec >= 0) && (num_rec <= SX_MAX_PTP_RECORDS)) {
        atomic64_inc(&ptp_records_dist[db->direction][num_rec]);
    }

    if (num_rec == 0) {
        return;
    }

    spin_lock_bh(&db->sysport_lock[local_port]);

    /* try to find matches for old records that are still pending */
    list_for_each_entry_safe(rec, tmp_rec, &db->sysport_records_list[local_port], list) {
        found = __match_record_with_event(&rec->mtpptr, local_port, db);

        if (found) {
            list_del(&rec->list);
            kmem_cache_free(__records_cache, rec);
            atomic64_dec(&ptp_counters[db->direction][PTP_COUNTER_PENDING_RECORDS]);
        }
    }

    /* try to find matches for current records and save records that has no matched event */
    for (i = 0; i < num_rec; i++) {
        found = __match_record_with_event(&record[i], local_port, db);

        if (!found) {
            to_cache = (struct ptp_record*)kmem_cache_alloc(__records_cache, GFP_ATOMIC);
            if (!to_cache) {
                atomic64_inc(&ptp_counters[db->direction][PTP_COUNTER_OUT_OF_MEMORY]);
            } else {
                to_cache->since = jiffies;
                INIT_LIST_HEAD(&to_cache->list);
                memcpy(&to_cache->mtpptr, &record[i], sizeof(to_cache->mtpptr));

                list_add_tail(&to_cache->list, &db->sysport_records_list[local_port]);
                atomic64_inc(&ptp_counters[db->direction][PTP_COUNTER_PENDING_RECORDS]);
            }
        }
    }

    ptp_dequeue_general_messages(local_port, db);

    spin_unlock_bh(&db->sysport_lock[local_port]);
}


static void __delete_caches(void)
{
    if (__records_cache) {
        kmem_cache_destroy(__records_cache);
    }

    if (__tx_event_cache) {
        kmem_cache_destroy(__tx_event_cache);
    }

    if (__rx_event_cache) {
        kmem_cache_destroy(__rx_event_cache);
    }
}


static int __create_caches(void)
{
    __records_cache = kmem_cache_create("ptp_record", sizeof(struct ptp_record), 0, 0, NULL);
    if (!__records_cache) {
        printk(KERN_ERR "failed to allocate memory cache for PTP TX events\n");
        goto error;
    }

    __tx_event_cache = kmem_cache_create("ptp_tx_event_data", sizeof(struct ptp_tx_event_data), 0, 0, NULL);
    if (!__tx_event_cache) {
        printk(KERN_ERR "failed to allocate memory cache for PTP TX events\n");
        goto error;
    }

    __rx_event_cache = kmem_cache_create("ptp_rx_event_data", sizeof(struct ptp_rx_event_data), 0, 0, NULL);
    if (!__rx_event_cache) {
        printk(KERN_ERR "failed to allocate memory cache for PTP RX events\n");
        goto error;
    }

    return 0;

error:
    __delete_caches();
    return -ENOMEM;
}


struct ptp_rx_event_data * ptp_allocate_rx_event_data(gfp_t gfp)
{
    return (struct ptp_rx_event_data*)kmem_cache_alloc(__rx_event_cache, gfp);
}


void ptp_free_rx_event_data(struct ptp_rx_event_data *rx_event_data)
{
    sx_skb_free(rx_event_data->ci->skb);
    kfree(rx_event_data->ci);
    kmem_cache_free(__rx_event_cache, rx_event_data);
}


struct ptp_tx_event_data * ptp_allocate_tx_event_data(gfp_t gfp)
{
    return (struct ptp_tx_event_data*)kmem_cache_alloc(__tx_event_cache, gfp);
}


void ptp_free_tx_event_data(struct ptp_tx_event_data *tx_event_data)
{
    if (tx_event_data->skb) {
        sock_put(tx_event_data->skb->sk);
        sx_skb_free(tx_event_data->skb); /* just release the reference we took when tx_event_data was allocated */
    }

    kmem_cache_free(__tx_event_cache, tx_event_data);
}


static int __sx_clock_rx_polling_thread(void *data)
{
    struct ku_access_mtpptr_reg ku_mtpptr;
    int                         local_port;
    int                         err;
    u8                          has_events;

    while (!kthread_should_stop()) {
        err = down_timeout(&ptp_polling_sem, 1 * HZ);
        if (err == -ETIME) { /* return to wait */
            continue;
        }

        for (local_port = 0; local_port < PTP_MAX_PORTS; local_port++) {
            spin_lock_bh(&ptp_rx_db.sysport_lock[local_port]);
            has_events = !list_empty(&ptp_rx_db.sysport_events_list[local_port]);
            spin_unlock_bh(&ptp_rx_db.sysport_lock[local_port]);

            if (!has_events) {
                continue;
            }

            memset(&ku_mtpptr, 0, sizeof(ku_mtpptr));

            ku_mtpptr.dev_id = __priv->dev.device_id;
            sx_cmd_set_op_tlv(&ku_mtpptr.op_tlv, MTPPTR_REG_ID, 1);
            ku_mtpptr.mtpptr_reg.clr = 1;
            ku_mtpptr.mtpptr_reg.dir = PTP_PACKET_INGRESS;
            ku_mtpptr.mtpptr_reg.local_port = local_port;

            err = sx_ACCESS_REG_MTPPTR(&__priv->dev, &ku_mtpptr, 0);
            if (err) {
                atomic64_inc(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_REG_ACCESS_FAILED]);
            } else {
                atomic64_inc(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_REG_ACCESS_SUCCEEDED]);
                ptp_lookup_event((u8*)&ku_mtpptr.mtpptr_reg, &ptp_rx_db);
            }
        }
    }

    return 0;
}


static void __init_db(struct ptp_db *db, u8 direction, ptp_db_handle_cb_t handle_cb, ptp_db_gc_cb_t gc_cb)
{
    int i;

    db->handle_cb = handle_cb;
    db->gc_cb = gc_cb;
    db->direction = direction;

    for (i = 0; i < PTP_MAX_PORTS; i++) {
        spin_lock_init(&db->sysport_lock[i]);
        INIT_LIST_HEAD(&db->sysport_events_list[i]);
        INIT_LIST_HEAD(&db->sysport_records_list[i]);
    }
}


int sx_ptp_init(struct sx_priv *priv, ptp_mode_t ptp_mode)
{
    int                         i = 0, err = 0;
    struct ku_access_mtpppc_reg mtpppc_reg_data;
    struct ku_access_mtptpt_reg mtptpt_reg_data;
    struct ku_access_mogcr_reg  mogcr_reg_data;
    struct sx_dev              *dev = &priv->dev;

    __priv = priv;
    ptp_working_mode = ptp_mode;
    sema_init(&ptp_polling_sem, 0);

    __ptp_wq = create_singlethread_workqueue("ptp_wq");
    if (!__ptp_wq) {
        err = -ENOMEM;
        goto out;
    }

    err = __create_caches();
    if (err) {
        goto out;
    }

    for (i = 0; i < PTP_COUNTER_LAST; i++) {
        atomic64_set(&ptp_counters[PTP_PACKET_INGRESS][i], 0);
        atomic64_set(&ptp_counters[PTP_PACKET_EGRESS][i], 0);
    }

    for (i = 0; i <= SX_MAX_PTP_RECORDS; i++) {
        atomic64_set(&ptp_records_dist[PTP_PACKET_INGRESS][i], 0);
        atomic64_set(&ptp_records_dist[PTP_PACKET_EGRESS][i], 0);
    }

    for (i = 0; i < PTP_MAX_PORTS; i++) {
        atomic64_set(&ptp_rx_budget[i], 0);
    }

    for (i = 0; i < PTP_MAX_PORTS; i++) {
        atomic64_set(&ptp_tx_budget[i], 0);
    }

    memset(&mtpppc_reg_data, 0, sizeof(mtpppc_reg_data));
    memset(&mtptpt_reg_data, 0, sizeof(mtptpt_reg_data));
    memset(&mogcr_reg_data, 0, sizeof(mogcr_reg_data));

    mogcr_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mogcr_reg_data.op_tlv, MOGCR_REG_ID, 2);
    mogcr_reg_data.mogcr_reg.ptp_iftc = 1; /* always clear after read */
    mogcr_reg_data.mogcr_reg.ptp_eftc = 1; /* always clear after read */
    err = sx_ACCESS_REG_MOGCR(dev, &mogcr_reg_data);
    if (err) {
        sx_err(dev, "Failed to configure register MOGCR\n");
        goto out;
    }

    mtpppc_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mtpppc_reg_data.op_tlv, MTPPPC_REG_ID, 2);

    mtpppc_reg_data.mtpppc_reg.egr_timestape_message_type = PTP_MSG_SYNC |
                                                            PTP_MSG_DELAY_REQ | PTP_MSG_PDELAY_REQ |
                                                            PTP_MSG_PDELAY_RESP;
    mtpppc_reg_data.mtpppc_reg.ing_timestape_message_type = PTP_MSG_SYNC |
                                                            PTP_MSG_DELAY_REQ | PTP_MSG_PDELAY_REQ |
                                                            PTP_MSG_PDELAY_RESP;
    err = sx_ACCESS_REG_MTPPPC(dev, &mtpppc_reg_data);
    if (err) {
        sx_err(dev, "Failed to configure register mtpppc.\n");
        goto out;
    }

    /* Configure trap PTP0 for event ptp message types */
    mtptpt_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mtptpt_reg_data.op_tlv, MTPTPT_REG_ID, 2);

    mtptpt_reg_data.mtptpt_reg.trap_id = 0;
    mtptpt_reg_data.mtptpt_reg.message_type = PTP_MSG_SYNC |
                                              PTP_MSG_DELAY_REQ | PTP_MSG_PDELAY_REQ | PTP_MSG_PDELAY_RESP;
    err = sx_ACCESS_REG_MTPTPT(dev, &mtptpt_reg_data);
    if (err) {
        sx_err(dev, "Failed to configure register mtptpt.\n");
        goto out;
    }

    /* Configure trap PTP1 for general ptp message types */
    memset(&mtptpt_reg_data, 0, sizeof(mtptpt_reg_data));
    mtptpt_reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mtptpt_reg_data.op_tlv, MTPTPT_REG_ID, 2);

    mtptpt_reg_data.mtptpt_reg.trap_id = 1;
    mtptpt_reg_data.mtptpt_reg.message_type = PTP_MSG_FOLLOW_UP |
                                              PTP_MSG_DELAY_RESP | PTP_MSG_PDELAY_RESP_FOLLOW_UP | PTP_MSG_ANNOUNCE |
                                              PTP_MSG_SIGNALING | PTP_MSG_MANAGEMENT;

    err = sx_ACCESS_REG_MTPTPT(dev, &mtptpt_reg_data);
    if (err) {
        sx_err(dev, "Failed to configure register mtptpt.\n");
        goto out;
    }

    priv->ptp_hw_frc_base = ioremap(pci_resource_start(priv->dev.pdev, priv->fw.frc_bar) +
                                    priv->fw.frc_offset, 8);

    __init_db(&ptp_rx_db, PTP_PACKET_INGRESS, __ptp_event_handler_rx, __ptp_gc_cb_rx);
    __init_db(&ptp_tx_db, PTP_PACKET_EGRESS, __ptp_event_handler_tx, __ptp_gc_cb_tx);

    err = sx_timestamp_init(priv);
    if (err) {
        sx_err(dev, "Failed to init timestamp.\n");
        goto out;
    }

    priv->ptp_cqn = -1;

    if (IS_PTP_MODE_POLLING) {
        __ptp_rx_polling_thread = kthread_run(__sx_clock_rx_polling_thread, NULL, "ptp_rx_polling");
        if (!__ptp_rx_polling_thread) {
            sx_err(dev, "failed to create PTP RX polling thread\n");
            err = -ENOMEM;
            goto out;
        }
    }

    INIT_DELAYED_WORK(&__gc_dwork, __gc);
    queue_delayed_work(priv->dev.generic_wq, &__gc_dwork, 0);

    INIT_DELAYED_WORK(&__per_sec_dwork, __per_sec);
    queue_delayed_work(priv->dev.generic_wq, &__per_sec_dwork, 0);

    INIT_DELAYED_WORK(&__set_hw_time_dwork, __set_hw_time);
    queue_delayed_work(__ptp_wq, &__set_hw_time_dwork, 0);

out:

    if (err) {
        if (__ptp_rx_polling_thread) {
            kthread_stop(__ptp_rx_polling_thread);
        }

        if (&priv->tstamp.is_ptp_enable) {
            sx_timestamp_cleanup(priv);
        }

        __delete_caches();

        if (__ptp_wq) {
            destroy_workqueue(__ptp_wq);
        }

        if (priv->ptp_hw_frc_base) {
            iounmap(priv->ptp_hw_frc_base);
        }
    }

    return err;
}

int sx_ptp_cleanup(struct sx_priv *priv)
{
    int /*i = 0,*/ err = 0;
    struct sx_dev *dev = &priv->dev;
    int            sysport;

    cancel_delayed_work_sync(&__gc_dwork);
    cancel_delayed_work_sync(&__per_sec_dwork);
    cancel_delayed_work_sync(&__set_hw_time_dwork);

    if (IS_PTP_MODE_POLLING) {
        kthread_stop(__ptp_rx_polling_thread);
    }

    for (sysport = 0; sysport < PTP_MAX_PORTS; sysport++) {
        __gc_db(sysport, &ptp_rx_db, 1);
        __gc_db(sysport, &ptp_tx_db, 1);
    }

    err = sx_timestamp_cleanup(priv);
    if (err) {
        sx_err(dev, "Failed to clean timestamp.\n");
        goto out;
    }

    __delete_caches();
    destroy_workqueue(__ptp_wq);

    iounmap(priv->ptp_hw_frc_base);

    ptp_working_mode = KU_PTP_MODE_DISABLED;

out:
    return err;
}


static void __dump_db(struct seq_file *m, const char *title, struct ptp_db *db)
{
    struct ptp_common_event_data *iter_common, *tmp_common;
    struct ptp_record            *iter_rec, *tmp_rec;
    unsigned long                 now = jiffies;
    int                           sysport;

    seq_printf(m, "%s\n", title);
    seq_printf(m, "=================================\n");

    for (sysport = 0; sysport < PTP_MAX_PORTS; sysport++) {
        spin_lock_bh(&db->sysport_lock[sysport]);

        if (!list_empty(&db->sysport_events_list[sysport]) || !list_empty(&db->sysport_records_list[sysport])) {
            seq_printf(m, "System Port: %d\n", sysport);
            seq_printf(m, "---------------\n");

            list_for_each_entry_safe(iter_common, tmp_common, &db->sysport_events_list[sysport], list) {
                seq_printf(m, "    EVENT   Seq:%5u  Type:%3u  Domain:%3u  Need_TS:%u  Msec_Ago:%lu\n",
                           iter_common->sequence_id,
                           iter_common->msg_type,
                           iter_common->domain_num,
                           iter_common->need_timestamp,
                           ((now - iter_common->since) * 1000) / HZ);
            }

            list_for_each_entry_safe(iter_rec, tmp_rec, &db->sysport_records_list[sysport], list) {
                seq_printf(m, "    RECORD  Seq:%5u  Type:%3u  Domain:%3u  FRC=%llu  Msec_Ago:%lu\n",
                           be16_to_cpu(iter_rec->mtpptr.sequence_id),
                           iter_rec->mtpptr.message_type,
                           iter_rec->mtpptr.domain_number,
                           be64_to_cpu(iter_rec->mtpptr.timestamp),
                           ((now - iter_rec->since) * 1000) / HZ);
            }
        }

        spin_unlock_bh(&db->sysport_lock[sysport]);
    }

    seq_printf(m, "\n\n");
}


int sx_dbg_ptp_dump_proc_show(struct seq_file *m, void *v)
{
    char section[40];
    int  i;

    seq_printf(m, "PTP DUMP\n");
    seq_printf(m, "--------\n");

    switch (ptp_working_mode) {
    case KU_PTP_MODE_DISABLED:
        seq_printf(m, "PTP mode: Disabled\n");
        return 0;

    case KU_PTP_MODE_EVENTS:
        seq_printf(m, "PTP mode: Events\n");
        break;

    case KU_PTP_MODE_POLLING:
        seq_printf(m, "PTP mode: Polling\n");
        break;

    default:
        seq_printf(m, "PTP mode: N/A\n");
        return 0;
    }

    seq_printf(m, "PTP CQn: %d\n\n", __priv->ptp_cqn);

    seq_printf(m, "%-40s   %-15s   %-15s\n", "Counter", "RX", "TX");
    seq_printf(m, "-----------------------------------------------------------------------------\n");

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Total packets",
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_TOTAL]),
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_TOTAL]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Timestamp required",
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_NEED_TIMESTAMP]),
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_NEED_TIMESTAMP]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "FIFO traps",
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_FIFO_TRAP]),
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_FIFO_TRAP]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Events removed by GC",
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_GC_EVENTS]),
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_GC_EVENTS]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Records removed by GC",
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_GC_RECORDS]),
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_GC_RECORDS]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Rate limiter violation",
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_RATE_LIMIT]),
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_RATE_LIMIT]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "HW FIFO overflow",
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_FIFO_OVERFLOW]),
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_FIFO_OVERFLOW]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "FW polling succeeded",
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_REG_ACCESS_SUCCEEDED]),
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_REG_ACCESS_SUCCEEDED]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "FW polling failed",
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_REG_ACCESS_FAILED]),
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_REG_ACCESS_FAILED]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Late match",
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_LATE_MATCH]),
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_LATE_MATCH]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "No matching timestamp",
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_EMPTY_TS]),
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_EMPTY_TS]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Dropped - Out of memory",
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_OUT_OF_MEMORY]),
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_OUT_OF_MEMORY]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Pending packets",
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_PENDING_EVENTS]),
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_PENDING_EVENTS]));

    seq_printf(m, "%-40s   %-15llu   %-15llu\n",
               "Pending records",
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_INGRESS][PTP_COUNTER_PENDING_RECORDS]),
               (u64)atomic64_read(&ptp_counters[PTP_PACKET_EGRESS][PTP_COUNTER_PENDING_RECORDS]));

    seq_printf(m, "\n");

    for (i = 0; i <= SX_MAX_PTP_RECORDS; i++) {
        sprintf(section, "%d-records polling/traps", i);
        seq_printf(m, "%-40s   %-15llu   %-15llu\n",
                   section,
                   (u64)atomic64_read(&ptp_records_dist[PTP_PACKET_INGRESS][i]),
                   (u64)atomic64_read(&ptp_records_dist[PTP_PACKET_EGRESS][i]));
    }

    seq_printf(m, "\n\n");

    __dump_db(m, "RX Database", &ptp_rx_db);
    __dump_db(m, "TX Database", &ptp_tx_db);

    return 0;
}
