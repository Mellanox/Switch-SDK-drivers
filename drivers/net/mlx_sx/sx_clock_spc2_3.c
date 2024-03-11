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

#include <linux/clocksource.h>
#include <linux/delay.h>
#include <linux/seq_file.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include <linux/kernel.h>
#include <uapi/linux/ptp_clock.h>
#include "sx_clock.h"
#include "sx.h"
#include "dev_db.h"
#include <linux/mlx_sx/auto_registers/reg.h>

#define READ_HW_UTC_SEC(priv)  (swab32(__raw_readl((priv)->hw_clock.hwd.spc2.utc_sec)))
#define READ_HW_UTC_NSEC(priv) (swab32(__raw_readl((priv)->hw_clock.hwd.spc2.utc_nsec)))

#define ADJPHASE_OFFSET 54
#define IS_ADJPHASE_SUPPORTED_BY_HW(feature_cap_mask1) ((feature_cap_mask1) & (1 << (ADJPHASE_OFFSET - 32)))
#define IS_VALID_ADJPHASE_VALUE(p_sx_priv, val)                    \
    (((val) >= (p_sx_priv)->hw_clock.hwd.spc2.min_phase_adj_ns) && \
     ((val) <= (p_sx_priv)->hw_clock.hwd.spc2.max_phase_adj_ns))

enum {
    PTP_PPS_PIN_MODE_IN  = 0x0,
    PTP_PPS_PIN_MODE_OUT = 0x1,
};

enum {
    PTP_PPS_OUT_PATTERN_PULSE    = 0x0,
    PTP_PPS_OUT_PATTERN_PERIODIC = 0x1,
};

enum {
    PTP_PPS_EVENT_MODE_DISABLE       = 0x0,
    PTP_PPS_EVENT_MODE_REPETETIVE    = 0x1,
    PTP_PPS_EVENT_MODE_ONCE_TILL_ARM = 0x2,
};

static int __ptp_pps_extts_configure(struct sx_priv           *priv,
                                     struct ptp_clock_request *rq,
                                     int                       on);
static int __ptp_pps_perout_configure(struct sx_priv           *priv,
                                      struct ptp_clock_request *rq,
                                      int                       on);
static int __ptp_pps_configure(struct sx_priv           *priv,
                               struct ptp_clock_request *rq,
                               int                       on);

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


static void __print_mtutc(const char *title, const struct ku_mtutc_reg *mtutc)
{
    printk(KERN_NOTICE "%s MTUTC {\n"
           "  freq_adj_units=%u, \n"
           "  log_max_freq_adjustment=%u, \n"
           "  operation=%u, \n"
           "  freq_adjustment=%u, \n"
           "  utc_sec=%u, \n"
           "  utc_nsec=%u, \n"
           "  time_adjustment=%u\n"
           "}\n",
           title,
           mtutc->freq_adj_units,
           mtutc->log_max_freq_adjustment,
           mtutc->operation,
           mtutc->freq_adjustment,
           mtutc->utc_sec,
           mtutc->utc_nsec,
           mtutc->time_adjustment);
}

static int __write_mtutc(struct sx_priv *priv, struct ku_access_mtutc_reg *mtutc, const char *op)
{
    struct ku_access_mtutc_reg mtutc_hw;
    int                        err, err2;

    mtutc->dev_id = priv->dev.device_id;
    sx_cmd_set_op_tlv(&mtutc->op_tlv, MTUTC_REG_ID, EMAD_METHOD_WRITE);
    err = sx_ACCESS_REG_MTUTC(&priv->dev, mtutc);
    if (err) {
        printk(KERN_ERR "sx_ACCESS_REG_MTUTC (%s) returned with error %d\n", op, err);

        /* MTUTC may stall the HW. FW knows how to identify this case and returns error for the register.
         * For offline debug analysis, in this case we need the current MTUTC values (in HW) and the
         * newly (erroneous) MTUTC values */

        memset(&mtutc_hw, 0, sizeof(mtutc_hw));
        mtutc_hw.dev_id = priv->dev.device_id;
        sx_cmd_set_op_tlv(&mtutc_hw.op_tlv, MTUTC_REG_ID, EMAD_METHOD_QUERY);
        err2 = sx_ACCESS_REG_MTUTC(&priv->dev, &mtutc_hw);
        if (!err2) {
            __print_mtutc("HW", &mtutc_hw.mtutc_reg);
        }

        __print_mtutc("Erroneous", &mtutc->mtutc_reg);
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
        sx_clock_dbg_add_setter(priv);
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
        sx_clock_dbg_add_setter(priv);
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
        sx_clock_dbg_add_setter(priv);
        sx_clock_log_add_adjtime(priv, delta);
    }

    return err;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 8, 0))
static int __init_adjphase_params(struct sx_priv *priv)
{
    struct ku_access_mtutc_reg reg_mtutc;
    struct ku_access_mcam_reg  reg_mcam;
    int                        err = 0;
    u8                         log_max_phase_adjustment = 0;
    bool                       adjphase_supported = false;

    memset(&reg_mcam, 0, sizeof(reg_mcam));
    reg_mcam.dev_id = priv->dev.device_id;
    sx_cmd_set_op_tlv(&reg_mcam.op_tlv, MLXSW_MCAM_ID, EMAD_METHOD_QUERY);
    reg_mcam.mcam_reg.feature_group = 0;
    reg_mcam.mcam_reg.access_reg_group = 0;
    err = sx_ACCESS_REG_MCAM(&priv->dev, &reg_mcam);
    if (err) {
        printk(KERN_ERR "Cannot query whether phase adjustment is supported, error: %d\n", err);
        err = -EFAULT;
        goto out;
    }

    if (IS_ADJPHASE_SUPPORTED_BY_HW(reg_mcam.mcam_reg.mng_feature_cap_mask[1])) {
        adjphase_supported = true;
    }
    if (!adjphase_supported) {
        pr_debug("ADJ_PHASE is not supported by the asic.\n");
        goto out;
    }

    memset(&reg_mtutc, 0, sizeof(reg_mtutc));
    reg_mtutc.dev_id = priv->dev.device_id;
    sx_cmd_set_op_tlv(&reg_mtutc.op_tlv, MTUTC_REG_ID, EMAD_METHOD_QUERY);
    err = sx_ACCESS_REG_MTUTC(&priv->dev, &reg_mtutc);
    if (err) {
        printk(KERN_ERR "sx_ACCESS_REG_MTUTC query returned with error %d\n", err);
        err = -EFAULT;
        goto out;
    }

    log_max_phase_adjustment = reg_mtutc.mtutc_reg.log_max_phase_adjustment;
    priv->hw_clock.hwd.spc2.min_phase_adj_ns = -(1 << log_max_phase_adjustment);
    priv->hw_clock.hwd.spc2.max_phase_adj_ns = 1 << log_max_phase_adjustment;

    printk(KERN_NOTICE "phase adjustment is supported, with log_max_phase_adjustment being %u.\n",
           log_max_phase_adjustment);
out:
    priv->hw_clock.hwd.spc2.is_phase_adj_supported = adjphase_supported;
    return err;
}

static int __adjphase_spc2(struct ptp_clock_info *ptp, s32 delta)
{
    struct sx_priv            *priv = container_of(ptp, struct sx_priv, hw_clock.clock_info);
    struct ku_access_mtutc_reg reg_mtutc;
    int                        err;

    if (!priv->hw_clock.hwd.spc2.is_phase_adj_supported) {
        return -EOPNOTSUPP;
    }
    if (!IS_VALID_ADJPHASE_VALUE(priv, delta)) {
        return -EINVAL;
    }

    memset(&reg_mtutc, 0, sizeof(reg_mtutc));
    reg_mtutc.mtutc_reg.operation = SXD_MTUTC_OPERATION_ADJUST_PHASE_E;
    reg_mtutc.mtutc_reg.time_adjustment = delta;
    err = __write_mtutc(priv, &reg_mtutc, "adj-phase");

    if (!err) {
        sx_clock_dbg_add_setter(priv);
        sx_clock_log_add_adjtime(priv, delta);
    } else {
        err = -EFAULT;
    }

    return err;
}
#endif /* if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 8, 0)) */

static u64 __perout_conf_real_time(s64 sec, u32 nsec)
{
    return ((u64)nsec) | ((u64)sec << 32);
}

static int __ptp_pps_enable(struct ptp_clock_info *ptp, struct ptp_clock_request *rq, int on)
{
    struct sx_priv *priv = container_of(ptp, struct sx_priv, hw_clock.clock_info);

    switch (rq->type) {
    case PTP_CLK_REQ_EXTTS:
        return __ptp_pps_extts_configure(priv, rq, on);

    case PTP_CLK_REQ_PEROUT:
        return __ptp_pps_perout_configure(priv, rq, on);

    case PTP_CLK_REQ_PPS:
        return __ptp_pps_configure(priv, rq, on);

    default:
        return -EOPNOTSUPP;
    }
    return 0;
}

static int __ptp_pps_verify(struct ptp_clock_info *ptp, unsigned int pin, enum ptp_pin_function func,
                            unsigned int chan)
{
    struct sx_priv *priv = container_of(ptp, struct sx_priv, hw_clock.clock_info);

    if (pin >= priv->hw_clock.clock_info.n_pins) {
        return -EINVAL;
    }

    switch (func) {
    case PTP_PF_NONE:
        return 0;

    case PTP_PF_EXTTS:
        return !(priv->hw_clock.hwd.spc2.pps_info.pin_caps[pin] &
                 SXD_MTPPS_CAP_PIN_0_MODE_SUPPORT_PPS_IN_E);

    case PTP_PF_PEROUT:
        return !(priv->hw_clock.hwd.spc2.pps_info.pin_caps[pin] &
                 SXD_MTPPS_CAP_PIN_0_MODE_SUPPORT_PPS_OUT_E);

    default:
        return -EOPNOTSUPP;
    }
}

static const struct ptp_clock_info __clock_info_spc2 = {
    .owner = THIS_MODULE,
    .max_adj = INT_MAX,
    .n_alarm = 0,
    .n_ext_ts = 0,
    .n_per_out = 0,
    .pps = 1,
    .adjfreq = __adjfreq_spc2,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 8, 0))
    .adjphase = __adjphase_spc2,
#endif
    .adjtime = __adjtime_spc2,
    .SX_CLOCK_GETTIME = __gettime_spc2,
    .SX_CLOCK_SETTIME = __settime_spc2,
    .enable = __ptp_pps_enable,
    .verify = __ptp_pps_verify,
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

/* In kernel version 4.19 ptp_find_pin() use internal lock, but the function is called inside a lock
 * In kernel version 5.X the function was changed to work without the lock.
 * when migrating to it the calls to ptp_find_pin_no_lock() can be replaced with the kernel function ptp_find_pin() */
int ptp_find_pin_no_lock(struct ptp_clock_info *ptp, enum ptp_pin_function func, unsigned int chan)
{
    struct ptp_pin_desc *pin = NULL;
    int                  i;

    for (i = 0; i < ptp->n_pins; i++) {
        if ((ptp->pin_config[i].func == func) &&
            (ptp->pin_config[i].chan == chan)) {
            pin = &ptp->pin_config[i];
            break;
        }
    }

    return pin ? i : -1;
}

int sx_pps_system_type_get(struct sx_priv *priv, int *dev_id)
{
    int                       err = 0;
    struct ku_access_mgir_reg reg_data;

    memset(&reg_data, 0, sizeof(struct ku_access_mgir_reg));

    reg_data.dev_id = priv->dev.device_id;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MGIR_REG_ID, EMAD_METHOD_QUERY);

    err = sx_ACCESS_REG_MGIR(&priv->dev, &reg_data);
    if (err) {
        printk(KERN_ERR "PPS: Failed to get system info from MGIR register, err=%d\n", err);
        return err;
    }

    *dev_id = reg_data.mgir_reg.hw_info.device_id;

    return err;
}

static int __ptp_pps_perout_configure(struct sx_priv *priv, struct ptp_clock_request *rq, int on)
{
    u8  pin_mode = 0;
    u8  pattern = 0;
    u32 field_select = 0;
    int err = 0;
    int pin = -1;
    s64 period_ns;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 9, 0))
    s64 duration_ns;
#endif
    u64                         time_stamp = 0;
    struct timespec64           ts;
    struct ku_access_mtpps_reg  mtpps;
    struct ku_access_mtppse_reg mtppse;
    u16                         out_pulse_duration = 0;
    u8                          utc_mode = 0;

    /* Reject requests with unsupported flags, currently only out pulse duration is supported */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 9, 0))
    if (rq->perout.flags & ~PTP_PEROUT_DUTY_CYCLE) {
        return -EOPNOTSUPP;
    }
#else
    if (rq->perout.flags) {
        return -EOPNOTSUPP;
    }
#endif

    if (rq->perout.index >= priv->hw_clock.clock_info.n_pins) {
        return -EINVAL;
    }

    field_select = SXD_MTPPS_FIELD_SELECT_ENABLE_E;
    pin = ptp_find_pin_no_lock(&priv->hw_clock.clock_info, PTP_PF_PEROUT, rq->perout.index);
    if (pin < 0) {
        return -EBUSY;
    }

    if (on) {
        pin_mode = PTP_PPS_PIN_MODE_OUT;
        pattern = PTP_PPS_OUT_PATTERN_PERIODIC;
        utc_mode = SXD_MTPPS_UTC_MODE_UTC_E;
        ts.tv_sec = rq->perout.period.sec;
        ts.tv_nsec = rq->perout.period.nsec;
        period_ns = timespec64_to_ns(&ts);
        /* Currently only one-pulse-per-second is supported, that says the period can only be 1 second */
        if (period_ns != 1000000000LL) {
            return -EINVAL;
        }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 9, 0))
        if (rq->perout.flags & PTP_PEROUT_DUTY_CYCLE) {
            ts.tv_sec = rq->perout.on.sec;
            ts.tv_nsec = rq->perout.on.nsec;
            duration_ns = timespec64_to_ns(&ts);
            /* The out pulse duration should be less than the period */
            if (duration_ns >= period_ns) {
                return -EINVAL;
            }

            /* Convert to milliseconds, if out pulse duration is 0, device default will be used */
            out_pulse_duration = duration_ns / 1000000;
        }
#else
/* For kernels that doesn't support duty cycle flag, leave the out pulse duration as 0, then device default will be used */
#endif

        time_stamp = __perout_conf_real_time(rq->perout.start.sec, rq->perout.start.nsec);

        field_select |= SXD_MTPPS_FIELD_SELECT_PIN_MODE_E |
                        SXD_MTPPS_FIELD_SELECT_PATTERN_E |
                        SXD_MTPPS_FIELD_SELECT_TIME_STAMP_E |
                        SXD_MTPPS_FIELD_SELECT_OUT_PULSE_DURATION_E |
                        SXD_MTPPS_FIELD_SELECT_UTC_MODE_E;
    }

    memset(&mtpps, 0, sizeof(mtpps));
    mtpps.dev_id = priv->dev.device_id;
    sx_cmd_set_op_tlv(&mtpps.op_tlv, MTPPS_REG_ID, EMAD_METHOD_WRITE);

    mtpps.mtpps_reg.pin = pin;
    mtpps.mtpps_reg.pin_mode = pin_mode;
    mtpps.mtpps_reg.pattern = pattern;
    mtpps.mtpps_reg.enable = on;
    mtpps.mtpps_reg.utc_mode = utc_mode;
    mtpps.mtpps_reg.time_stamp = time_stamp;
    mtpps.mtpps_reg.field_select = field_select;
    mtpps.mtpps_reg.out_pulse_duration = out_pulse_duration;

    err = sx_ACCESS_REG_MTPPS(&priv->dev, &mtpps);
    if (err) {
        printk(KERN_ERR "PPS perout configure: failed to set MTPPS, err=%d\n", err);
        return err;
    }

    memset(&mtppse, 0, sizeof(mtppse));
    mtppse.dev_id = priv->dev.device_id;
    sx_cmd_set_op_tlv(&mtppse.op_tlv, MTPPSE_REG_ID, EMAD_METHOD_WRITE);

    mtppse.mtppse_reg.pin = pin;
    mtppse.mtppse_reg.event_generation_mode = SXD_MTPPSE_EVENT_GENERATION_MODE_REPETITIVE_EVENTS_E & on;

    err = sx_ACCESS_REG_MTPPSE(&priv->dev, &mtppse);
    if (err) {
        printk(KERN_ERR "PPS perout configure: failed to set MTPPSE, err=%d\n", err);
        return err;
    }

    return err;
}

static int __ptp_pps_configure(struct sx_priv *priv, struct ptp_clock_request *rq, int on)
{
    priv->hw_clock.hwd.spc2.pps_info.enabled = !!on;

    return 0;
}

static int __ptp_pps_extts_configure(struct sx_priv *priv, struct ptp_clock_request *rq, int on)
{
    int                         err = 0;
    int                         pin = -1;
    u32                         field_select = 0;
    u8                          pin_mode = 0;
    u8                          pattern = 0;
    struct ku_access_mtpps_reg  mtpps;
    struct ku_access_mtppse_reg mtppse;

    /* Reject requests with unsupported flags */
    if (rq->extts.flags & ~(PTP_ENABLE_FEATURE |
                            PTP_RISING_EDGE |
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 4, 0))
                            PTP_FALLING_EDGE |
                            PTP_STRICT_FLAGS)) {
#else
                            PTP_FALLING_EDGE)) {
#endif
        return -EOPNOTSUPP;
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 4, 0))
    /* Reject requests to enable time stamping on both edges. */
    if ((rq->extts.flags & PTP_STRICT_FLAGS) &&
        (rq->extts.flags & PTP_ENABLE_FEATURE) &&
        ((rq->extts.flags & PTP_EXTTS_EDGES) == PTP_EXTTS_EDGES)) {
        return -EOPNOTSUPP;
    }
#endif

    if (rq->extts.index >= priv->hw_clock.clock_info.n_pins) {
        return -EINVAL;
    }

    pin = ptp_find_pin_no_lock(&priv->hw_clock.clock_info, PTP_PF_EXTTS, rq->extts.index);
    if (pin < 0) {
        return -EBUSY;
    }

    if (on) {
        pin_mode = PTP_PPS_PIN_MODE_IN;
        pattern = !!(rq->extts.flags & PTP_FALLING_EDGE);
        field_select = SXD_MTPPS_FIELD_SELECT_PIN_MODE_E |
                       SXD_MTPPS_FIELD_SELECT_PATTERN_E |
                       SXD_MTPPS_FIELD_SELECT_ENABLE_E;
    } else {
        field_select = SXD_MTPPS_FIELD_SELECT_ENABLE_E;
    }

    memset(&mtpps, 0, sizeof(mtpps));
    mtpps.dev_id = priv->dev.device_id;
    sx_cmd_set_op_tlv(&mtpps.op_tlv, MTPPS_REG_ID, EMAD_METHOD_WRITE);

    mtpps.mtpps_reg.pin = pin;
    mtpps.mtpps_reg.pin_mode = pin_mode;
    mtpps.mtpps_reg.pattern = pattern;
    mtpps.mtpps_reg.enable = on;
    mtpps.mtpps_reg.field_select = field_select;

    err = sx_ACCESS_REG_MTPPS(&priv->dev, &mtpps);
    if (err) {
        printk(KERN_ERR "PPS extts configure: failed to set MTPPS, err=%d\n", err);
        return err;
    }

    memset(&mtppse, 0, sizeof(mtppse));
    mtppse.dev_id = priv->dev.device_id;
    sx_cmd_set_op_tlv(&mtppse.op_tlv, MTPPSE_REG_ID, EMAD_METHOD_WRITE);

    mtppse.mtppse_reg.pin = pin;
    mtppse.mtppse_reg.event_generation_mode = SXD_MTPPSE_EVENT_GENERATION_MODE_REPETITIVE_EVENTS_E & !!on;

    err = sx_ACCESS_REG_MTPPSE(&priv->dev, &mtppse);
    if (err) {
        printk(KERN_ERR "PPS extts configure: failed to set MTPPSE, err=%d\n", err);
        return err;
    }

    return 0;
}

static int __ptp_pps_capabilities_get(struct sx_priv *priv)
{
    int                        err = 0;
    struct ku_access_mtpps_reg mtpps;

    memset(&mtpps, 0, sizeof(mtpps));
    mtpps.dev_id = priv->dev.device_id;
    sx_cmd_set_op_tlv(&mtpps.op_tlv, MTPPS_REG_ID, EMAD_METHOD_QUERY);

    err = sx_ACCESS_REG_MTPPS(&priv->dev, &mtpps);
    if (err) {
        printk(KERN_ERR "failed to query MTPPS, err=%d\n", err);
    }

    priv->hw_clock.clock_info.n_ext_ts = mtpps.mtpps_reg.cap_max_num_of_pps_in_pins;
    priv->hw_clock.clock_info.n_per_out = mtpps.mtpps_reg.cap_max_num_of_pps_out_pins;
    priv->hw_clock.clock_info.n_pins = mtpps.mtpps_reg.cap_number_of_pps_pins;

    priv->hw_clock.hwd.spc2.pps_info.pin_caps[0] = mtpps.mtpps_reg.cap_pin_0_mode;
    priv->hw_clock.hwd.spc2.pps_info.pin_caps[1] = mtpps.mtpps_reg.cap_pin_1_mode;
    priv->hw_clock.hwd.spc2.pps_info.pin_caps[2] = mtpps.mtpps_reg.cap_pin_2_mode;
    priv->hw_clock.hwd.spc2.pps_info.pin_caps[3] = mtpps.mtpps_reg.cap_pin_3_mode;
    priv->hw_clock.hwd.spc2.pps_info.pin_caps[4] = mtpps.mtpps_reg.cap_pin_4_mode;
    priv->hw_clock.hwd.spc2.pps_info.pin_caps[5] = mtpps.mtpps_reg.cap_pin_5_mode;
    priv->hw_clock.hwd.spc2.pps_info.pin_caps[6] = mtpps.mtpps_reg.cap_pin_6_mode;
    priv->hw_clock.hwd.spc2.pps_info.pin_caps[7] = mtpps.mtpps_reg.cap_pin_7_mode;

    priv->hw_clock.hwd.spc2.pps_info.enabled = 0;

    return err;
}

static int __ptp_pps_pin_mode_get(struct sx_priv *priv, u8 pin)
{
    int                        err;
    struct ku_access_mtpps_reg mtpps;

    /* get pin capability from mtpps */
    memset(&mtpps, 0, sizeof(mtpps));
    mtpps.dev_id = priv->dev.device_id;
    mtpps.mtpps_reg.field_select = SXD_MTPPS_FIELD_SELECT_PIN_MODE_E;
    mtpps.mtpps_reg.pin = pin;
    sx_cmd_set_op_tlv(&mtpps.op_tlv, MTPPS_REG_ID, EMAD_METHOD_QUERY);
    err = sx_ACCESS_REG_MTPPS(&priv->dev, &mtpps);
    if (err) {
        printk(KERN_ERR "failed to query MTPPS, err=%d\n", err);
        return PTP_PF_NONE;
    }

    switch (mtpps.mtpps_reg.pin_mode) {
    case SXD_MTPPS_PIN_MODE_PPS_IN_E:
        return PTP_PF_EXTTS;

    case SXD_MTPPS_PIN_MODE_PPS_OUT_E:
        return PTP_PF_PEROUT;

    case SXD_MTPPS_PIN_MODE_VIRTUAL_PIN_E:
    case SXD_MTPPS_PIN_MODE_PPS_OUT_AND_VIRTUAL_PIN_E:
        return PTP_PF_NONE;
    }

    return PTP_PF_NONE;
}

static int __ptp_pps_pin_config_init(struct sx_priv *priv)
{
    int i;

    if (!(priv->hw_clock.clock_info.n_pins)) {
        return 0;
    }

    priv->hw_clock.clock_info.pin_config =
        kzalloc(priv->hw_clock.clock_info.n_pins * sizeof(*priv->hw_clock.clock_info.pin_config),
                GFP_KERNEL);
    if (!priv->hw_clock.clock_info.pin_config) {
        printk(KERN_ERR "failed to allocate PPS pin config\n");
        return -1;
    }

    for (i = 0; i < priv->hw_clock.clock_info.n_pins; i++) {
        snprintf(priv->hw_clock.clock_info.pin_config[i].name,
                 sizeof(priv->hw_clock.clock_info.pin_config[i].name),
                 "mlx_sxd_pps%d", i);
        priv->hw_clock.clock_info.pin_config[i].index = i;
        priv->hw_clock.clock_info.pin_config[i].func = __ptp_pps_pin_mode_get(priv, i);
        priv->hw_clock.clock_info.pin_config[i].chan = 0;
    }

    return 0;
}

static int __ptp_pps_init(struct sx_priv *priv)
{
    int err = 0;

    err = __ptp_pps_capabilities_get(priv);
    if (err) {
        printk(KERN_ERR "failed to get PPS capabilities, err=%d\n", err);
        return err;
    }

    err = __ptp_pps_pin_config_init(priv);
    if (err) {
        printk(KERN_ERR "failed to init PPS pin config, err=%d\n", err);
    }

    return err;
}

int sx_clock_dev_init_spc2(struct sx_priv *priv)
{
    int err = 0;
    int sys_type = 0;

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

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 8, 0))
    err = __init_adjphase_params(priv);
    if (err) {
        printk(KERN_ERR "failed to query phase adjustment related params clock (err=%d)\n", err);
        goto failed_reg;
    }
#endif

    err = sx_clock_register(priv, &__clock_info_spc2);
    if (err) {
        printk(KERN_ERR "failed to register clock (err=%d)\n", err);
        goto failed_reg;
    }

    err = sx_pps_system_type_get(priv, &sys_type);
    if (err) {
        printk(KERN_ERR "failed to retrieve system type (err=%d)\n", err);
        goto failed_reg;
    }

    /* WA: PPS is temporarily supported only for SPC2 */
    if (sys_type == SXD_MGIR_HW_DEV_ID_SPECTRUM2) {
        err = __ptp_pps_init(priv);
        if (err) {
            printk(KERN_ERR "failed to init PPS, err=%d\n", err);
            goto failed_pps;
        }
    }


    return 0;

failed_pps:
    priv->hw_clock.clock_info.enable = NULL;
    priv->hw_clock.clock_info.verify = NULL;
    kfree(priv->hw_clock.clock_info.pin_config);

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

    priv->hw_clock.clock_info.enable = NULL;
    priv->hw_clock.clock_info.verify = NULL;
    kfree(priv->hw_clock.clock_info.pin_config);

    return 0;
}

int sx_clock_dump_spc2(struct sx_priv *priv, struct seq_file *m, void *v, void *context)
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

void sx_core_ptp_handle_mtppst_event(struct completion_info *ci)
{
    struct ptp_clock_event   ptp_event;
    struct ptp_clock       * clock = (sx_priv(ci->dev)->hw_clock.clock);
    struct ptp_clock_info  * clock_info = &(sx_priv(ci->dev)->hw_clock.clock_info);
    struct ptp_pps         * pps_info = &(sx_priv(ci->dev)->hw_clock.hwd.spc2.pps_info);
    struct sx_internal_log * pps_log = &(sx_priv(ci->dev)->ptp.hwd.spc2.log_pps_events);
    struct ku_mtppst_reg     mtppst_reg;
    int                      err;
    u8                     * mtppst_outbox = (u8*)ci->skb->data + sizeof(struct sx_emad) +
                                             sizeof(struct sxd_emad_tlv_reg);

    err = __MTPPST_decode(mtppst_outbox, &mtppst_reg, NULL);
    if (err) {
        printk(KERN_ERR "__MTPPST_decode returned with error %d\n", err);
        return;
    }

    if (mtppst_reg.pin > clock_info->n_pins) {
        printk(KERN_ERR "PPS clock event unsupported pin=%d\n", mtppst_reg.pin);
        return;
    }

    switch (clock_info->pin_config[mtppst_reg.pin].func) {
    case PTP_PF_EXTTS:
        ptp_event.index = mtppst_reg.pin;
        ptp_event.timestamp = (((u64)mtppst_reg.timestamp_msb) * 1000000000) + mtppst_reg.timestamp_lsb;
        if (pps_info->enabled) {
            ptp_event.type = PTP_CLOCK_PPSUSR;
            ptp_event.pps_times.ts_real =
                ns_to_timespec64(ptp_event.timestamp);
        } else {
            ptp_event.type = PTP_CLOCK_EXTTS;
        }
        ptp_clock_event(clock, &ptp_event);

        sx_int_log_info(pps_log, "func=%d, index=%d, ts=%ld, type=%d",
                        clock_info->pin_config[mtppst_reg.pin].func,
                        ptp_event.index,
                        ptp_event.timestamp,
                        ptp_event.type);
        break;

    case PTP_PF_PEROUT:
        printk(KERN_ERR "Unsupported PPS clock OUT event\n");
        break;

    default:
        printk(KERN_ERR "PPS clock event unsupported pin function=0x%x, pin=%d\n",
               clock_info->pin_config[mtppst_reg.pin].func, mtppst_reg.pin);
    }
}
