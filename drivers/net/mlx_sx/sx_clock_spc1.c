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
#include <linux/delay.h>
#include <linux/seq_file.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include "sx_clock.h"
#include "sx.h"

#define SPC1_CLOCK_FREQ_KHZ (156257)  /* 6.4 nSec/cycle */

static struct delayed_work __set_hw_time_dwork;
static u64 __read_hw_clock_spc1(const struct cyclecounter *cc)
{
    struct sx_tstamp *tstamp = container_of(cc, struct sx_tstamp, cycles);
    u64               hw_time = 0, hw_time_h = 0, hw_time_l = 0;

    /* For mitigating lsb wrap-around it is recommended to read the
     * free_running_clock_high, free_running_clock_low, free_running_clock_high.
     * If the 2 high values are different then we do a re-read */
    hw_time_h = __raw_readl(sx_priv(tstamp->dev)->hw_clock_frc_base + 4);
    hw_time_l = __raw_readl(sx_priv(tstamp->dev)->hw_clock_frc_base);
    if (hw_time_h != __raw_readl(sx_priv(tstamp->dev)->hw_clock_frc_base + 4)) {
        hw_time_h = __raw_readl(sx_priv(tstamp->dev)->hw_clock_frc_base + 4);
        hw_time_l = __raw_readl(sx_priv(tstamp->dev)->hw_clock_frc_base);
    }

    hw_time = hw_time_h << 32 | hw_time_l;
    return swab64(hw_time) & cc->mask;
}


/* SHOULD BE CALLED UNDER timecounter LOCK! */
static u64 __nsec2frc(const struct timecounter *tc, s64 nsec)
{
    nsec <<= tc->cc->shift;
    nsec = div_u64(nsec, tc->cc->mult);

    return (u64)nsec;
}


static u64 __frc2nsec(u64 frc)
{
    struct sx_priv *priv = sx_priv(sx_clock_get_dev());
    u64             nsec;
    unsigned long   flags;

    spin_lock_irqsave(&priv->tstamp.lock, flags);
    nsec = timecounter_cyc2time(&priv->tstamp.clock, frc);
    spin_unlock_irqrestore(&priv->tstamp.lock, flags);

    SX_CLOCK_ACTIVITY_LOG("FRC_to_NSEC [frc=%llu, nsec=%llu]",
                          frc,
                          nsec);

    return nsec;
}


static void __sx_timestamp_overflow(struct work_struct *work)
{
    struct delayed_work *dwork = to_delayed_work(work);
    struct sx_tstamp    *tstamp = container_of(dwork, struct sx_tstamp,
                                               overflow_work);

    spin_lock_bh(&tstamp->lock);
    timecounter_read(&tstamp->clock);
    spin_unlock_bh(&tstamp->lock);

    sx_clock_queue_delayed_work(&tstamp->overflow_work, tstamp->overflow_period);
}


static void __periodic_set_hw_time_spc1(struct work_struct *work)
{
    struct sx_tstamp          *tstamp;
    struct ku_access_mtpps_reg reg_mtpps;
    struct ku_access_mtutc_reg reg_mtutc;
    u64                        curr_frc, pps_frc;
    u64                        curr_nsec = 0, nsec_till_full_sec;
    int                        freq_adj;
    bool                       time_adj;
    int                        err;

    tstamp = &sx_priv(sx_clock_get_dev())->tstamp;

/* if we're in the 9/10 of a sec or higher, it is too close for use. wait for next second */
#define TOO_CLOSE_TO_NEXT_SEC (NSEC_PER_SEC / 10)

find_good_timing:

    spin_lock_bh(&tstamp->lock);

    curr_frc = __read_hw_clock_spc1(&tstamp->cycles);
    curr_nsec = timecounter_cyc2time(&tstamp->clock, curr_frc);
    nsec_till_full_sec = NSEC_PER_SEC - ((curr_nsec) % (NSEC_PER_SEC));

    if (nsec_till_full_sec <= TOO_CLOSE_TO_NEXT_SEC) {
        spin_unlock_bh(&tstamp->lock);
        SX_CLOCK_ACTIVITY_LOG(
            "Too close to next-sec, wait 100msec [curr_frc=%llu, curr_nsec=%llu, nsec_till_full_sec=%llu]",
            curr_frc,
            curr_nsec,
            nsec_till_full_sec);

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

    pps_frc = curr_frc + __nsec2frc(&tstamp->clock, nsec_till_full_sec);

    /* SET PPS */

    SX_CLOCK_ACTIVITY_LOG("PERIODIC MTPPS [curr_frc=%llu, curr_nsec=%llu, pps_frc=%llu, nsec_till_full_sec=%llu]",
                          curr_frc,
                          curr_nsec,
                          pps_frc,
                          nsec_till_full_sec);

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

        SX_CLOCK_ACTIVITY_LOG("PERIODIC MTUTC [freq_adj=%d]",
                              freq_adj);

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

    SX_CLOCK_ACTIVITY_LOG("PERIODIC MTUTC [utc_sec=%llu]",
                          curr_nsec / NSEC_PER_SEC + 1,
                          nsec_till_full_sec);

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

    sx_clock_queue_delayed_work(&__set_hw_time_dwork, HZ);
}


static int __adjtime_spc1(struct ptp_clock_info *ptp, s64 delta)
{
    struct sx_tstamp *tstamp = container_of(ptp, struct sx_tstamp, ptp_info);

    spin_lock_bh(&tstamp->lock);
    tstamp->clock.nsec += delta;
    tstamp->time_adj = true;
    spin_unlock_bh(&tstamp->lock);

    sx_clock_log_add_adjtime(delta);
    return 0;
}

static int __adjfreq_spc1(struct ptp_clock_info *ptp, s32 delta)
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

    sx_clock_log_add_adjfreq(delta);
    return 0;
}

static int __gettime_spc1(struct ptp_clock_info *ptp, sx_clock_timespec_t *ts)
{
    struct sx_tstamp *tstamp = container_of(ptp, struct sx_tstamp, ptp_info);
    u64               ns;

    spin_lock_bh(&tstamp->lock);
    ns = timecounter_read(&tstamp->clock);
    spin_unlock_bh(&tstamp->lock);
    *ts = SX_CLOCK_NS_TO_TIMESPEC(ns);

    return 0;
}


static int __settime_spc1(struct ptp_clock_info *ptp, const sx_clock_timespec_t *ts)
{
    struct sx_tstamp *tstamp = container_of(ptp, struct sx_tstamp, ptp_info);
    u64               ns = SX_CLOCK_TIMESPEC_TO_NS(ts);

    spin_lock_bh(&tstamp->lock);
    timecounter_init(&tstamp->clock, &tstamp->cycles, ns);
    tstamp->time_adj = true;
    spin_unlock_bh(&tstamp->lock);

    sx_clock_log_add_settime(((s64)(ts->tv_sec * NSEC_PER_SEC)) + ts->tv_nsec);
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


int sx_clock_init_spc1(struct sx_priv *priv)
{
    struct sx_tstamp *tstamp = &priv->tstamp;
    u64               ns;
    int               err;

    spin_lock_init(&tstamp->lock);
    tstamp->cycles.read = __read_hw_clock_spc1;

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

    tstamp->cycles.shift = 29;
    tstamp->cycles.mult = clocksource_khz2mult(SPC1_CLOCK_FREQ_KHZ, tstamp->cycles.shift);
    tstamp->nominal_c_mult = tstamp->cycles.mult;
    tstamp->freq_adj = 0;
    tstamp->time_adj = false;
    tstamp->cycles.mask = CLOCKSOURCE_MASK(64);
    tstamp->dev = &priv->dev;

    timecounter_init(&tstamp->clock, &tstamp->cycles, ktime_to_ns(ktime_get_real()));

    /* Calculate period in seconds to call the overflow watchdog - to make
     * sure counter is checked at least once every wrap around.
     */

    ns = cyclecounter_cyc2ns(&tstamp->cycles, tstamp->cycles.mask);
    do_div(ns, NSEC_PER_SEC / 2 / HZ);

    /* keep periodic read from clock every 1/8 second and avoid it from wrap-around */
    tstamp->overflow_period = HZ / 8;
    INIT_DELAYED_WORK(&tstamp->overflow_work, __sx_timestamp_overflow);
    sx_clock_queue_delayed_work(&tstamp->overflow_work, 0);

    err = sx_clock_register(priv, &__clock_info_spc1);
    if (err) {
        cancel_delayed_work_sync(&tstamp->overflow_work);
        return err;
    }

    INIT_DELAYED_WORK(&__set_hw_time_dwork, __periodic_set_hw_time_spc1);
    sx_clock_queue_delayed_work(&__set_hw_time_dwork, 0);

    return 0;
}


int sx_clock_cleanup_spc1(struct sx_priv *priv)
{
    cancel_delayed_work_sync(&__set_hw_time_dwork);
    cancel_delayed_work_sync(&priv->tstamp.overflow_work);

    return 0;
}


void sx_clock_fill_hwtstamp_spc1(u64 frc, struct skb_shared_hwtstamps *hwts)
{
    u64 nsec = __frc2nsec(frc);

    sx_clock_fill_hwtstamp_nsec(nsec, hwts);
}


int sx_clock_dump_spc1(struct seq_file *m, void *v)
{
    struct sx_dev    *dev;
    struct sx_tstamp *tstamp;
    struct timespec   linux_ts;
    u64               frc, nsec;


    dev = sx_clock_get_dev();
    tstamp = &sx_priv(dev)->tstamp;

    spin_lock_bh(&tstamp->lock);
    frc = __read_hw_clock_spc1(&tstamp->cycles);
    spin_unlock_bh(&tstamp->lock);

    nsec = __frc2nsec(frc);

    getnstimeofday(&linux_ts);

    seq_printf(m, "Hardware FRC:             %llu\n", frc);
    seq_printf(m, "Hardware time (from FRC): %u.%09u\n", (u32)(nsec / NSEC_PER_SEC), (u32)(nsec % NSEC_PER_SEC));
    seq_printf(m, "Linux UTC:                %u.%09u\n", (u32)linux_ts.tv_sec, (u32)linux_ts.tv_nsec);
    seq_printf(m, "\n\n");

    return 0;
}
