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

#define READ_HW_UTC_SEC(priv)  (swab32(__raw_readl((priv)->hw_clock.hwd.spc2.utc_sec)))
#define READ_HW_UTC_NSEC(priv) (swab32(__raw_readl((priv)->hw_clock.hwd.spc2.utc_nsec)))

static inline void __read_cr_space_utc(struct sx_priv *priv, sx_clock_timespec_t *ts)
{
    u32 tmp_sec;

    /* to prevent race-condition when reading sec/nsec from HW, do the following:
     * 1) read seconds to SEC_1
     * 2) read nanoseconds to NSEC
     * 3) read seconds again to SEC_2
     *
     * if (SEC_1 == SEC_2) everything's fine. otherwise, do the steps again.
     *
     * this algorithm is also in use by FW when reading 64bit counters on a 32bit HW.
     *
     */

    do {
        ts->tv_sec = READ_HW_UTC_SEC(priv);
        ts->tv_nsec = READ_HW_UTC_NSEC(priv);
        tmp_sec = READ_HW_UTC_SEC(priv);
    } while (ts->tv_sec != tmp_sec);
}


static int __write_mtutc(struct sx_priv *priv, struct ku_access_mtutc_reg *mtutc, const char *op)
{
    int err;

    mtutc->dev_id = priv->dev.device_id;
    sx_cmd_set_op_tlv(&mtutc->op_tlv, MTUTC_REG_ID, EMAD_METHOD_WRITE);
    err = sx_ACCESS_REG_MTUTC(&priv->dev, mtutc);
    if (err) {
        printk(KERN_ERR "sx_ACCESS_REG_MTUTC (%s) returned with error %d\n", op, err);
    }

    return err;
}


static int __adjfreq_spc2(struct ptp_clock_info *ptp, s32 delta)
{
    struct sx_priv            *priv = container_of(ptp, struct sx_priv, hw_clock.clock_info);
    struct ku_access_mtutc_reg reg_mtutc;
    int                        err;
    s32                        orig_delta = delta;

    delta = -delta;

    memset(&reg_mtutc, 0, sizeof(reg_mtutc));
    reg_mtutc.mtutc_reg.operation = 3; /* ADJUST_FREQ UTC */
    reg_mtutc.mtutc_reg.freq_adjustment = delta;
    err = __write_mtutc(priv, &reg_mtutc, "adj-freq");
    if (!err) {
        sx_clock_log_add_adjfreq(priv, orig_delta);
    }

    return err;
}


static int __gettime_spc2(struct ptp_clock_info *ptp, sx_clock_timespec_t *ts)
{
    struct sx_priv *priv = container_of(ptp, struct sx_priv, hw_clock.clock_info);

    __read_cr_space_utc(priv, ts);
    return 0;
}


static int __settime_spc2(struct ptp_clock_info *ptp, const sx_clock_timespec_t *ts)
{
    struct sx_priv            *priv = container_of(ptp, struct sx_priv, hw_clock.clock_info);
    struct ku_access_mtutc_reg reg_mtutc;
    int                        err;

    memset(&reg_mtutc, 0, sizeof(reg_mtutc));
    reg_mtutc.mtutc_reg.operation = 1; /* SET_TIME_IMMEDIATE */
    reg_mtutc.mtutc_reg.utc_sec = ts->tv_sec;
    reg_mtutc.mtutc_reg.utc_nsec = ts->tv_nsec;
    err = __write_mtutc(priv, &reg_mtutc, "set-time");
    if (!err) {
        sx_clock_log_add_settime(priv, ((s64)(ts->tv_sec * NSEC_PER_SEC)) + ts->tv_nsec);
    }

    return err;
}


static int __adjtime_spc2(struct ptp_clock_info *ptp, s64 delta)
{
    struct sx_priv            *priv = container_of(ptp, struct sx_priv, hw_clock.clock_info);
    struct ku_access_mtutc_reg reg_mtutc;
    sx_clock_timespec_t        hw_utc;
    u64                        nsec;
    int                        err;

    if ((delta < -32768) || (delta > 32767)) { /* if it is out of range, convert it to 'set_time' */
        __read_cr_space_utc(priv, &hw_utc);
        nsec = SX_CLOCK_TIMESPEC_TO_NS(&hw_utc);
        nsec += delta;

        hw_utc.tv_sec = nsec / NSEC_PER_SEC;
        hw_utc.tv_nsec = nsec % NSEC_PER_SEC;
        err = __settime_spc2(ptp, &hw_utc);
    } else {
        memset(&reg_mtutc, 0, sizeof(reg_mtutc));
        reg_mtutc.mtutc_reg.operation = 2; /* ADJUST_TIME */
        reg_mtutc.mtutc_reg.time_adjustment = (int)delta;
        err = __write_mtutc(priv, &reg_mtutc, "adj-time");
    }

    if (!err) {
        sx_clock_log_add_adjtime(priv, delta);
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


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
int sx_clock_cqe_ts_to_utc_spc2(struct sx_priv *priv, const struct timespec64 *cqe_ts, struct timespec64 *utc)
#else
int sx_clock_cqe_ts_to_utc_spc2(struct sx_priv *priv, const struct timespec *cqe_ts, struct timespec *utc)
#endif
{
    u64 utc_sec = READ_HW_UTC_SEC(priv);
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


int sx_clock_dev_init_spc2(struct sx_priv *priv)
{
    int err = 0;

    priv->hw_clock.hwd.spc2.utc_sec = ioremap(pci_resource_start(priv->dev.pdev, priv->fw.utc_sec_bar) +
                                              priv->fw.utc_sec_offset, 4);
    if (!priv->hw_clock.hwd.spc2.utc_sec) {
        printk(KERN_ERR "could not remap UTC-sec register\n");
        err = -ENOMEM;
        goto failed_utc;
    }

    priv->hw_clock.hwd.spc2.utc_nsec = ioremap(pci_resource_start(priv->dev.pdev,
                                                                  priv->fw.utc_nsec_bar) +
                                               priv->fw.utc_nsec_offset,
                                               4);
    if (!priv->hw_clock.hwd.spc2.utc_nsec) {
        printk(KERN_ERR "could not remap UTC-nsec register\n");
        err = -ENOMEM;
        goto failed_nsec;
    }

    err = sx_clock_register(priv, &__clock_info_spc2);
    if (err) {
        printk(KERN_ERR "failed to register clock (err=%d)\n", err);
        goto failed_reg;
    }

    return 0;

failed_reg:
    iounmap(priv->hw_clock.hwd.spc2.utc_nsec);
    priv->hw_clock.hwd.spc2.utc_nsec = NULL;

failed_nsec:
    iounmap(priv->hw_clock.hwd.spc2.utc_sec);
    priv->hw_clock.hwd.spc2.utc_sec = NULL;

failed_utc:
    return err;
}

int sx_clock_dev_cleanup_spc2(struct sx_priv *priv)
{
    iounmap(priv->hw_clock.hwd.spc2.utc_sec);
    priv->hw_clock.hwd.spc2.utc_sec = NULL;

    iounmap(priv->hw_clock.hwd.spc2.utc_nsec);
    priv->hw_clock.hwd.spc2.utc_nsec = NULL;

    return 0;
}

int sx_clock_dump_spc2(struct sx_priv *priv, struct seq_file *m, void *v)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    struct timespec64 linux_ts;
#else
    struct timespec linux_ts;
#endif
    sx_clock_timespec_t cr_space_ts;

    __read_cr_space_utc(priv, &cr_space_ts);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    ktime_get_real_ts64(&linux_ts);
#else
    getnstimeofday(&linux_ts);
#endif

    seq_printf(m, "Hardware UTC:  %u.%09u\n", (u32)cr_space_ts.tv_sec, (u32)cr_space_ts.tv_nsec);
    seq_printf(m, "Linux UTC:     %u.%09u\n", (u32)linux_ts.tv_sec, (u32)linux_ts.tv_nsec);
    seq_printf(m, "\n\n");
    return 0;
}
