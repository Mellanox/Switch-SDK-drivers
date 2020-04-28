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

static struct sx_clock_log_db __log_settime;
static struct sx_clock_log_db __log_adjtime;
static struct sx_clock_log_db __log_adjfreq;
static inline void __read_cr_space_utc(sx_clock_timespec_t *ts)
{
    struct sx_dev *dev;
    u64            hw_utc;

    dev = sx_clock_get_dev();

    hw_utc = swab64(__raw_readq(sx_priv(dev)->hw_clock_utc_base));
    ts->tv_nsec = hw_utc & 0xffffffff;
    ts->tv_sec = hw_utc >> 32;
}


static int __write_mtutc(struct ku_access_mtutc_reg *mtutc, const char *op)
{
    struct sx_dev *dev = sx_clock_get_dev();
    int            err;

    mtutc->dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&mtutc->op_tlv, MTUTC_REG_ID, EMAD_METHOD_WRITE);
    err = sx_ACCESS_REG_MTUTC(dev, mtutc);
    if (err) {
        printk(KERN_ERR "sx_ACCESS_REG_MTUTC (%s) returned with error %d\n", op, err);
    }

    return err;
}


static int __adjfreq_spc2(struct ptp_clock_info *ptp, s32 delta)
{
    struct ku_access_mtutc_reg reg_mtutc;
    int                        err;
    s32                        orig_delta = delta;

    delta = -delta;

    memset(&reg_mtutc, 0, sizeof(reg_mtutc));
    reg_mtutc.mtutc_reg.operation = 3; /* ADJUST_FREQ UTC */
    reg_mtutc.mtutc_reg.freq_adjustment = delta;
    err = __write_mtutc(&reg_mtutc, "adj-freq");
    if (!err) {
        sx_clock_log_add(&__log_adjfreq, orig_delta);
    }

    return err;
}


static int __gettime_spc2(struct ptp_clock_info *ptp, sx_clock_timespec_t *ts)
{
    __read_cr_space_utc(ts);
    return 0;
}


static int __settime_spc2(struct ptp_clock_info *ptp, const sx_clock_timespec_t *ts)
{
    struct ku_access_mtutc_reg reg_mtutc;
    int                        err;

    memset(&reg_mtutc, 0, sizeof(reg_mtutc));
    reg_mtutc.mtutc_reg.operation = 1; /* SET_TIME_IMMEDIATE */
    reg_mtutc.mtutc_reg.utc_sec = ts->tv_sec;
    reg_mtutc.mtutc_reg.utc_nsec = ts->tv_nsec;
    err = __write_mtutc(&reg_mtutc, "set-time");
    if (!err) {
        sx_clock_log_add(&__log_settime, ((s64)(ts->tv_sec * NSEC_PER_SEC)) + ts->tv_nsec);
    }

    return err;
}


static int __adjtime_spc2(struct ptp_clock_info *ptp, s64 delta)
{
    struct ku_access_mtutc_reg reg_mtutc;
    sx_clock_timespec_t        hw_utc;
    u64                        nsec;
    int                        err;

    if ((delta < -32768) || (delta > 32767)) { /* if it is out of range, convert it to 'set_time' */
        __read_cr_space_utc(&hw_utc);
        nsec = SX_CLOCK_TIMESPEC_TO_NS(&hw_utc);
        nsec += delta;

        hw_utc.tv_sec = nsec / NSEC_PER_SEC;
        hw_utc.tv_nsec = nsec % NSEC_PER_SEC;
        err = __settime_spc2(ptp, &hw_utc);
    } else {
        memset(&reg_mtutc, 0, sizeof(reg_mtutc));
        reg_mtutc.mtutc_reg.operation = 2; /* ADJUST_TIME */
        reg_mtutc.mtutc_reg.time_adjustment = (int)delta;
        err = __write_mtutc(&reg_mtutc, "adj-time");
    }

    if (!err) {
        sx_clock_log_add(&__log_adjtime, delta);
    }

    return err;
}


static const struct ptp_clock_info __clock_info_spc2 = {
    .owner = THIS_MODULE,
    .max_adj = INT_MAX,
    .n_alarm = 0,
    .n_ext_ts = 0,
    .n_per_out = 0,
    .pps = 0,
    .adjfreq = __adjfreq_spc2,
    .adjtime = __adjtime_spc2,
    .SX_CLOCK_GETTIME = __gettime_spc2,
    .SX_CLOCK_SETTIME = __settime_spc2,
    .enable = NULL,
};


int sx_clock_cqe_ts_to_utc_spc2(struct sx_priv *priv, const struct timespec *cqe_ts, struct timespec *utc)
{
    u64 utc_sec = swab32(__raw_readl(priv->hw_clock_utc_base));
    u8  utc_sec_8bit;

    utc_sec_8bit = utc_sec & 0xff; /* CQEv2 UTC ==> 8bits seconds, 30bits nano-seconds */

    if (utc_sec_8bit >= cqe_ts->tv_sec) {
        utc->tv_sec = utc_sec - (utc_sec_8bit - cqe_ts->tv_sec);
    } else {
        utc->tv_sec = utc_sec - 256 + (cqe_ts->tv_sec - utc_sec_8bit);
    }

    utc->tv_nsec = cqe_ts->tv_nsec;
    return 0;
}


int sx_clock_init_spc2(struct sx_priv *priv)
{
    sx_clock_log_init(&__log_settime);
    sx_clock_log_init(&__log_adjfreq);
    sx_clock_log_init(&__log_adjtime);

    return sx_clock_register(priv, &__clock_info_spc2);
}


int sx_clock_cleanup_spc2(struct sx_priv *priv)
{
    return 0;
}


int sx_clock_dump_spc2(struct seq_file *m, void *v)
{
    struct sx_dev      *dev;
    struct timespec     linux_ts;
    sx_clock_timespec_t cr_space_ts;

    dev = sx_clock_get_dev();

    __read_cr_space_utc(&cr_space_ts);
    getnstimeofday(&linux_ts);

    seq_printf(m, "Hardware UTC:  %u.%09u\n", (u32)cr_space_ts.tv_sec, (u32)cr_space_ts.tv_nsec);
    seq_printf(m, "Linux UTC:     %u.%09u\n", (u32)linux_ts.tv_sec, (u32)linux_ts.tv_nsec);
    seq_printf(m, "\n\n");

    sx_clock_log_dump(&__log_settime, m, "set-time log");
    sx_clock_log_dump(&__log_adjfreq, m, "adj-freq log");
    sx_clock_log_dump(&__log_adjtime, m, "adj-time log");
    return 0;
}
