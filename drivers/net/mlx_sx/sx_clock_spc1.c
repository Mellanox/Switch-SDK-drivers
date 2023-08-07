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

#include <linux/clocksource.h>
#include <linux/delay.h>
#include <linux/seq_file.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include "sx_clock.h"
#include "sx.h"
#include "dev_db.h"

#define SPC1_CLOCK_FREQ_KHZ (156257)  /* 6.4 nSec/cycle */

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0))
typedef u64 cycle_t;
#endif

static u64 __read_hw_clock_spc1(const struct cyclecounter *cc)
{
    struct sx_priv *priv = container_of(cc, struct sx_priv, hw_clock.hwd.spc1.cycles);
    u64             hw_time = 0;
    u32             hw_time_h1 = 0, hw_time_l = 0, hw_time_h2 = 0;

    /* For mitigating lsb wrap-around it is recommended to read the
     * free_running_clock_high, free_running_clock_low, free_running_clock_high.
     * If the 2 high values are different then we do a re-read */
    hw_time_h1 = swab32(__raw_readl(priv->hw_clock.hwd.spc1.frc_base));
    hw_time_l = swab32(__raw_readl(priv->hw_clock.hwd.spc1.frc_base + 4));
    hw_time_h2 = swab32(__raw_readl(priv->hw_clock.hwd.spc1.frc_base));
    if (hw_time_h1 != hw_time_h2) {
        hw_time_l = swab32(__raw_readl(priv->hw_clock.hwd.spc1.frc_base + 4));
    }

    hw_time = (u64)hw_time_h2 << 32 | (u64)hw_time_l;
    return hw_time & cc->mask;
}


/* SHOULD BE CALLED UNDER timecounter LOCK! */
static u64 __nsec2frc(const struct timecounter *tc, s64 nsec)
{
    nsec <<= tc->cc->shift;
    nsec = div_u64(nsec, tc->cc->mult);

    return (u64)nsec;
}


static u64 __frc2nsec(struct sx_priv *priv, u64 frc)
{
    u64           nsec;
    unsigned long flags;

    spin_lock_irqsave(&priv->hw_clock.hwd.spc1.clock_lock, flags);
    nsec = timecounter_cyc2time(&priv->hw_clock.hwd.spc1.clock, frc);
    spin_unlock_irqrestore(&priv->hw_clock.hwd.spc1.clock_lock, flags);

    SX_CLOCK_ACTIVITY_LOG(priv,
                          SX_INTERNAL_LOG_SEVERITY_INFO_E,
                          "FRC_to_NSEC [frc=%llu, nsec=%llu]",
                          frc,
                          nsec);

    return nsec;
}


static void __sx_timestamp_overflow(struct work_struct *work)
{
    struct delayed_work *dwork = to_delayed_work(work);
    struct sx_priv      *priv = container_of(dwork, struct sx_priv, hw_clock.hwd.spc1.overflow_dwork);

    spin_lock_bh(&priv->hw_clock.hwd.spc1.clock_lock);
    timecounter_read(&priv->hw_clock.hwd.spc1.clock);
    spin_unlock_bh(&priv->hw_clock.hwd.spc1.clock_lock);

    sx_clock_queue_delayed_work(&priv->hw_clock.hwd.spc1.overflow_dwork,
                                priv->hw_clock.hwd.spc1.overflow_period);
}


static void __periodic_set_hw_time_spc1(struct work_struct *work)
{
    struct delayed_work *dwork = to_delayed_work(work);
    struct sx_priv      *priv = container_of(dwork,
                                             struct sx_priv,
                                             hw_clock.hwd.spc1.set_hw_time_dwork);
    struct ku_access_mtpps_reg reg_mtpps;
    struct ku_access_mtutc_reg reg_mtutc;
    u64                        curr_frc, pps_frc;
    u64                        curr_nsec = 0, nsec_till_full_sec;
    int                        freq_adj;
    bool                       time_adj;
    int                        err;

/* if we're in the 9/10 of a sec or higher, it is too close for use. wait for next second */
#define TOO_CLOSE_TO_NEXT_SEC (NSEC_PER_SEC / 10)

find_good_timing:

    spin_lock_bh(&priv->hw_clock.hwd.spc1.clock_lock);

    curr_frc = __read_hw_clock_spc1(&priv->hw_clock.hwd.spc1.cycles);
    curr_nsec = timecounter_cyc2time(&priv->hw_clock.hwd.spc1.clock, curr_frc);
    nsec_till_full_sec = NSEC_PER_SEC - ((curr_nsec) % (NSEC_PER_SEC));

    if (nsec_till_full_sec <= TOO_CLOSE_TO_NEXT_SEC) {
        spin_unlock_bh(&priv->hw_clock.hwd.spc1.clock_lock);
        SX_CLOCK_ACTIVITY_LOG(
            priv,
            SX_INTERNAL_LOG_SEVERITY_INFO_E,
            "Too close to next-sec, wait 100msec [curr_frc=%llu, curr_nsec=%llu, nsec_till_full_sec=%llu]",
            curr_frc,
            curr_nsec,
            nsec_till_full_sec);

        msleep(100);
        goto find_good_timing;
    }

    freq_adj = priv->hw_clock.hwd.spc1.freq_adj;
    time_adj = priv->hw_clock.hwd.spc1.time_adj;
    priv->hw_clock.hwd.spc1.freq_adj = 0;
    priv->hw_clock.hwd.spc1.time_adj = false;

    spin_unlock_bh(&priv->hw_clock.hwd.spc1.clock_lock);

    if (!time_adj && (freq_adj == 0)) {
        goto out;
    }

    pps_frc = curr_frc + __nsec2frc(&priv->hw_clock.hwd.spc1.clock, nsec_till_full_sec);

    /* SET PPS */

    SX_CLOCK_ACTIVITY_LOG(priv,
                          SX_INTERNAL_LOG_SEVERITY_INFO_E,
                          "PERIODIC MTPPS [curr_frc=%llu, curr_nsec=%llu, pps_frc=%llu, nsec_till_full_sec=%llu]",
                          curr_frc,
                          curr_nsec,
                          pps_frc,
                          nsec_till_full_sec);

    memset(&reg_mtpps, 0, sizeof(reg_mtpps));
    reg_mtpps.dev_id = priv->dev.device_id;
    sx_cmd_set_op_tlv(&reg_mtpps.op_tlv, MTPPS_REG_ID, EMAD_METHOD_WRITE);
    reg_mtpps.mtpps_reg.enable = 1;
    reg_mtpps.mtpps_reg.pin_mode = 2; /* virtual pin */
    reg_mtpps.mtpps_reg.pin = 7; /* 7 is the only pin we can work on */
    reg_mtpps.mtpps_reg.time_stamp = pps_frc;
    err = sx_ACCESS_REG_MTPPS(&priv->dev, &reg_mtpps);
    if (err) {
        printk(KERN_ERR "sx_ACCESS_REG_MTPPS (set_pps) returned with error %d\n", err);
    }

    if (freq_adj != 0) {
        /* ADJUST FREQ */

        SX_CLOCK_ACTIVITY_LOG(priv,
                              SX_INTERNAL_LOG_SEVERITY_INFO_E,
                              "PERIODIC MTUTC [freq_adj=%d]",
                              freq_adj);

        memset(&reg_mtutc, 0, sizeof(reg_mtutc));
        reg_mtutc.dev_id = priv->dev.device_id;
        sx_cmd_set_op_tlv(&reg_mtutc.op_tlv, MTUTC_REG_ID, EMAD_METHOD_WRITE);
        reg_mtutc.mtutc_reg.operation = 3; /* ADJUST_FREQ */
        reg_mtutc.mtutc_reg.freq_adjustment = freq_adj;
        err = sx_ACCESS_REG_MTUTC(&priv->dev, &reg_mtutc);
        if (err) {
            printk(KERN_ERR "sx_ACCESS_REG_MTUTC (adj_freq) returned with error %d\n", err);
        }
    }

    /* SET TIME */

    SX_CLOCK_ACTIVITY_LOG(priv,
                          SX_INTERNAL_LOG_SEVERITY_INFO_E,
                          "PERIODIC MTUTC [utc_sec=%llu, nsec_till_full_sec=%llu]",
                          curr_nsec / NSEC_PER_SEC + 1,
                          nsec_till_full_sec);

    memset(&reg_mtutc, 0, sizeof(reg_mtutc));
    reg_mtutc.dev_id = priv->dev.device_id;
    sx_cmd_set_op_tlv(&reg_mtutc.op_tlv, MTUTC_REG_ID, EMAD_METHOD_WRITE);
    reg_mtutc.mtutc_reg.operation = 0; /* SET_TIME_AT_NEXT_SEC */
    reg_mtutc.mtutc_reg.utc_sec = curr_nsec / NSEC_PER_SEC + 1;
    err = sx_ACCESS_REG_MTUTC(&priv->dev, &reg_mtutc);
    if (err) {
        printk(KERN_ERR "sx_ACCESS_REG_MTUTC (set_time) returned with error %d\n", err);
    }

out:

    sx_clock_queue_delayed_work(&priv->hw_clock.hwd.spc1.set_hw_time_dwork, HZ);
}


static int __adjtime_spc1(struct ptp_clock_info *ptp, s64 delta)
{
    struct sx_priv *priv = container_of(ptp, struct sx_priv, hw_clock.clock_info);

    spin_lock_bh(&priv->hw_clock.hwd.spc1.clock_lock);
    priv->hw_clock.hwd.spc1.clock.nsec += delta;
    priv->hw_clock.hwd.spc1.time_adj = true;
    spin_unlock_bh(&priv->hw_clock.hwd.spc1.clock_lock);

    sx_clock_dbg_add_setter(priv);
    sx_clock_log_add_adjtime(priv, delta);
    return 0;
}

static int __adjfreq_spc1(struct ptp_clock_info *ptp, s32 delta)
{
    struct sx_priv *priv = container_of(ptp, struct sx_priv, hw_clock.clock_info);
    u64             adj;
    u32             diff;
    int             neg_adj = 0;

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

    adj = priv->hw_clock.hwd.spc1.nominal_c_mult;
    adj *= delta;
    diff = div_u64(adj, NSEC_PER_SEC);
    spin_lock_bh(&priv->hw_clock.hwd.spc1.clock_lock);
    timecounter_read(&priv->hw_clock.hwd.spc1.clock);
    priv->hw_clock.hwd.spc1.cycles.mult = neg_adj ?
                                          priv->hw_clock.hwd.spc1.nominal_c_mult - diff :
                                          priv->hw_clock.hwd.spc1.nominal_c_mult + diff;
    priv->hw_clock.hwd.spc1.freq_adj += delta;
    spin_unlock_bh(&priv->hw_clock.hwd.spc1.clock_lock);

    sx_clock_dbg_add_setter(priv);
    sx_clock_log_add_adjfreq(priv, delta);
    return 0;
}

static int __gettime_spc1(struct ptp_clock_info *ptp, sx_clock_timespec_t *ts)
{
    struct sx_priv *priv = container_of(ptp, struct sx_priv, hw_clock.clock_info);
    u64             ns;

    spin_lock_bh(&priv->hw_clock.hwd.spc1.clock_lock);
    ns = timecounter_read(&priv->hw_clock.hwd.spc1.clock);
    spin_unlock_bh(&priv->hw_clock.hwd.spc1.clock_lock);
    *ts = SX_CLOCK_NS_TO_TIMESPEC(ns);

    return 0;
}


static int __settime_spc1(struct ptp_clock_info *ptp, const sx_clock_timespec_t *ts)
{
    struct sx_priv *priv = container_of(ptp, struct sx_priv, hw_clock.clock_info);
    u64             ns = SX_CLOCK_TIMESPEC_TO_NS(ts);

    spin_lock_bh(&priv->hw_clock.hwd.spc1.clock_lock);
    timecounter_init(&priv->hw_clock.hwd.spc1.clock,
                     &priv->hw_clock.hwd.spc1.cycles,
                     ns);
    priv->hw_clock.hwd.spc1.time_adj = true;
    spin_unlock_bh(&priv->hw_clock.hwd.spc1.clock_lock);

    sx_clock_dbg_add_setter(priv);
    sx_clock_log_add_settime(priv, ((s64)(ts->tv_sec * NSEC_PER_SEC)) + ts->tv_nsec);
    return 0;
}


static const struct ptp_clock_info __clock_info_spc1 = {
    .owner = THIS_MODULE,
    .max_adj = 100000000,    /* Max adjacency of 100ms */
    .n_alarm = 0,
    .n_ext_ts = 0,
    .n_per_out = 0,
    .pps = 0,
    .adjfreq = __adjfreq_spc1,
    .adjtime = __adjtime_spc1,
    .SX_CLOCK_GETTIME = __gettime_spc1,
    .SX_CLOCK_SETTIME = __settime_spc1,
    .enable = NULL,
};


int sx_clock_dev_init_spc1(struct sx_priv *priv)
{
    u64 ns;
    int err;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0)) || defined(CONFIG_SX_RHEL_7_4) || defined(CONFIG_SX_RHEL_7_6)
    u64 frac = 0;
#endif

    priv->hw_clock.hwd.spc1.frc_base = ioremap(pci_resource_start(priv->dev.pdev, priv->fw.frc_bar) +
                                               priv->fw.frc_offset, 8);
    if (!priv->hw_clock.hwd.spc1.frc_base) {
        printk(KERN_ERR "could not remap FRC register\n");
        err = -ENOMEM;
        goto out_err;
    }

    spin_lock_init(&priv->hw_clock.hwd.spc1.clock_lock);
    priv->hw_clock.hwd.spc1.cycles.read = __read_hw_clock_spc1;

    printk(KERN_INFO "HW clock frequency: %u KHz\n", SPC1_CLOCK_FREQ_KHZ);

    /*
     *  This value is being calculated on newer kernel versions using the function clocks_calc_mult_shift
     *  with parameters:
     *  from: frequency to convert from ==> SPC1: 156257000 (6.4 nSec), SPC2/3: 1000000000 (1 nSec)
     *  to: frequency to convert to. On our usage, to=1000000000L
     *  maxsec guaranteed runtime conversion range in second, according to arch, On Spectrum, max_sec=2
     *
     *  This is the necessary shift value to convert the HW clock to UTC without a wraparound
     * */

    priv->hw_clock.hwd.spc1.cycles.shift = 29;
    priv->hw_clock.hwd.spc1.cycles.mult =
        clocksource_khz2mult(SPC1_CLOCK_FREQ_KHZ, priv->hw_clock.hwd.spc1.cycles.shift);
    priv->hw_clock.hwd.spc1.nominal_c_mult = priv->hw_clock.hwd.spc1.cycles.mult;
    priv->hw_clock.hwd.spc1.freq_adj = 0;
    priv->hw_clock.hwd.spc1.time_adj = false;
    priv->hw_clock.hwd.spc1.cycles.mask = CLOCKSOURCE_MASK(64);

    timecounter_init(&priv->hw_clock.hwd.spc1.clock,
                     &priv->hw_clock.hwd.spc1.cycles,
                     ktime_to_ns(ktime_get_real()));

    /* Calculate period in seconds to call the overflow watchdog - to make
     * sure counter is checked at least once every wrap around.
     */

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0)) || defined(CONFIG_SX_RHEL_7_4) || defined(CONFIG_SX_RHEL_7_6)
    ns = cyclecounter_cyc2ns(&priv->hw_clock.hwd.spc1.cycles,
                             priv->hw_clock.hwd.spc1.cycles.mask,
                             frac, &frac);
#else
    ns = cyclecounter_cyc2ns(&priv->hw_clock.hwd.spc1.cycles,
                             priv->hw_clock.hwd.spc1.cycles.mask);
#endif

    do_div(ns, NSEC_PER_SEC / 2 / HZ);

    /* keep periodic read from clock every 1/8 second and avoid it from wrap-around */
    priv->hw_clock.hwd.spc1.overflow_period = HZ / 8;
    INIT_DELAYED_WORK(&priv->hw_clock.hwd.spc1.overflow_dwork, __sx_timestamp_overflow);
    sx_clock_queue_delayed_work(&priv->hw_clock.hwd.spc1.overflow_dwork, 0);

    err = sx_clock_register(priv, &__clock_info_spc1);
    if (err) {
        cancel_delayed_work_sync(&priv->hw_clock.hwd.spc1.overflow_dwork);
        goto out_err;
    }

    INIT_DELAYED_WORK(&priv->hw_clock.hwd.spc1.set_hw_time_dwork, __periodic_set_hw_time_spc1);
    sx_clock_queue_delayed_work(&priv->hw_clock.hwd.spc1.set_hw_time_dwork, 0);

    return 0;

out_err:
    if (priv->hw_clock.hwd.spc1.frc_base) {
        iounmap(priv->hw_clock.hwd.spc1.frc_base);
        priv->hw_clock.hwd.spc1.frc_base = NULL;
    }

    return err;
}


int sx_clock_dev_cleanup_spc1(struct sx_priv *priv)
{
    cancel_delayed_work_sync(&priv->hw_clock.hwd.spc1.set_hw_time_dwork);
    cancel_delayed_work_sync(&priv->hw_clock.hwd.spc1.overflow_dwork);
    iounmap(priv->hw_clock.hwd.spc1.frc_base);
    priv->hw_clock.hwd.spc1.frc_base = NULL;

    return 0;
}


void sx_clock_fill_hwtstamp_spc1(struct sx_priv *priv, u64 frc, struct skb_shared_hwtstamps *hwts)
{
    u64 nsec = __frc2nsec(priv, frc);

    sx_clock_fill_hwtstamp_nsec(nsec, hwts);
}

int sx_clock_dump_spc1(struct sx_priv *priv, struct seq_file *m, void *v, void *context)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    struct timespec64 linux_ts;
#else
    struct timespec linux_ts;
#endif
    u64 frc, nsec;

    spin_lock_bh(&priv->hw_clock.hwd.spc1.clock_lock);
    frc = __read_hw_clock_spc1(&priv->hw_clock.hwd.spc1.cycles);
    spin_unlock_bh(&priv->hw_clock.hwd.spc1.clock_lock);

    nsec = __frc2nsec(priv, frc);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    ktime_get_real_ts64(&linux_ts);
#else
    getnstimeofday(&linux_ts);
#endif

    seq_printf(m, "Hardware FRC:             %llu\n", frc);
    seq_printf(m, "Hardware time (from FRC): %u.%09u\n", (u32)(nsec / NSEC_PER_SEC), (u32)(nsec % NSEC_PER_SEC));
    seq_printf(m, "Linux UTC:                %u.%09u\n", (u32)linux_ts.tv_sec, (u32)linux_ts.tv_nsec);
    seq_printf(m, "\n\n");
    return 0;
}
