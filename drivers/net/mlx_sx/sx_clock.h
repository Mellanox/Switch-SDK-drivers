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

#ifndef SX_CLOCK_H
#define SX_CLOCK_H

#include <linux/version.h>
#include <linux/types.h>

#include "sx.h"

extern int clock_activity_log;

/************************************************************************************/
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0))
#define SX_CLOCK_SETTIME        settime64
#define SX_CLOCK_GETTIME        gettime64
#define SX_CLOCK_TIMESPEC_TO_NS timespec64_to_ns
#define SX_CLOCK_NS_TO_TIMESPEC ns_to_timespec64
typedef struct timespec64 sx_clock_timespec_t;
#else
#define SX_CLOCK_SETTIME        settime
#define SX_CLOCK_GETTIME        gettime
#define SX_CLOCK_TIMESPEC_TO_NS timespec_to_ns
#define SX_CLOCK_NS_TO_TIMESPEC ns_to_timespec
typedef struct timespec sx_clock_timespec_t;
#define SX_CLOCK_USE_TIMESPEC64 (0)
#endif
/************************************************************************************/

#define SX_CLOCK_IS_DEV_SPECIFIC_CB_SUPPORTED(dev, func_name)               \
    ({                                                                      \
        struct sx_priv *__priv = sx_priv(dev);                              \
        int __err = 0;                                                      \
        u8 __is_supported = 0;                                              \
        do {                                                                \
            __err = __sx_core_dev_specific_cb_get_reference(dev);           \
            if (__err) {                                                    \
                printk(KERN_ERR "failed to get " #func_name " callback\n"); \
                break;                                                      \
            }                                                               \
            if (__priv->dev_specific_cb.func_name) {                        \
                __is_supported = 1;                                         \
            }                                                               \
            __sx_core_dev_specific_cb_release_reference(dev);               \
        } while (0);                                                        \
        __is_supported;                                                     \
    })

#define SX_CLOCK_DEV_SPECIFIC_CB(dev, func_name, ...)                       \
    ({                                                                      \
        struct sx_priv *__priv = sx_priv(dev);                              \
        int __err = 0;                                                      \
        do {                                                                \
            __err = __sx_core_dev_specific_cb_get_reference(dev);           \
            if (__err) {                                                    \
                printk(KERN_ERR "failed to get " #func_name " callback\n"); \
                break;                                                      \
            }                                                               \
            if (__priv->dev_specific_cb.func_name) {                        \
                __err = __priv->dev_specific_cb.func_name(__VA_ARGS__);     \
            }                                                               \
            __sx_core_dev_specific_cb_release_reference(dev);               \
        } while (0);                                                        \
        __err;                                                              \
    })

enum log_type {
    LOG_TYPE_STRING_E,
    LOG_TYPE_S64_E
};
struct sx_clock_log_entry {
    unsigned long jiffies;
    enum log_type type;
    union {
        char val_str[256];
        s64  val_s64;
    } value;
};
#define SX_CLOCK_ACTIVITY_LOG(priv, fmt, args ...)                                 \
    do {                                                                           \
        if (clock_activity_log) {                                                  \
            sx_clock_log_add_string(&(priv)->hw_clock.log_activity, fmt, ## args); \
        }                                                                          \
    } while (0)

struct sx_priv;
struct sx_tstamp;
struct skb_shared_hwtstamps;
struct ptp_clock_info;
struct cyclecounter;
struct sk_buff;

/* external functions */
int sx_core_clock_init(void);
void sx_core_clock_deinit(void);
int sx_core_clock_dev_init(struct sx_priv *priv);
int sx_core_clock_dev_deinit(struct sx_priv *priv);
int sx_core_clock_cqe_ts_to_utc(struct sx_priv *priv,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                                const struct timespec64 *cqe_ts,
                                struct timespec64       *utc);
#else
                                const struct timespec *cqe_ts,
                                struct timespec       *utc);
#endif

/* common functions */
int sx_clock_log_init(struct sx_clock_log_db *log_db, u32 cyc_buff_size);
void sx_clock_log_deinit(struct sx_clock_log_db *log_db);
void sx_clock_log_dump(struct sx_clock_log_db *log_db,
                       struct seq_file        *m,
                       const char             *title);
int sx_clock_log_add_string(struct sx_clock_log_db *log_db,
                            const char *fmt, ...);
void sx_clock_log_add_settime(struct sx_priv *priv, s64 value);
void sx_clock_log_add_adjtime(struct sx_priv *priv, s64 value);
void sx_clock_log_add_adjfreq(struct sx_priv *priv, s64 value);
void sx_clock_log_add_s64(struct sx_clock_log_db *log_db, s64 value);
int sx_clock_register(struct sx_priv              *priv,
                      const struct ptp_clock_info *ptp_clock_info);
int sx_clock_queue_delayed_work(struct delayed_work *dwork,
                                unsigned long        delay);
void sx_clock_fill_hwtstamp_nsec(u64 nsec, struct skb_shared_hwtstamps *hwts);

/* SPC1 functions */
int sx_clock_dev_init_spc1(struct sx_priv *priv);
int sx_clock_dev_cleanup_spc1(struct sx_priv *priv);
void sx_clock_fill_hwtstamp_spc1(struct sx_priv *priv, u64 frc, struct skb_shared_hwtstamps *hwts);
int sx_clock_dump_spc1(struct sx_priv *priv, struct seq_file *m, void *v);

/* SPC2 functions */
int sx_clock_dev_init_spc2(struct sx_priv *priv);
int sx_clock_dev_cleanup_spc2(struct sx_priv *priv);
int sx_clock_cqe_ts_to_utc_spc2(struct sx_priv *priv,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                                const struct timespec64 *cqe_ts,
                                struct timespec64       *utc);
#else
                                const struct timespec *cqe_ts,
                                struct timespec       *utc);
#endif
int sx_clock_dump_spc2(struct sx_priv *priv, struct seq_file *m, void *v);

#endif  /* SX_CLOCK_H */
