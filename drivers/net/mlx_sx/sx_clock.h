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

#ifndef SX_CLOCK_H
#define SX_CLOCK_H

#include <linux/types.h>

/************************************************************************************/
/* this definition may change in kernel_backports patches! don't touch it here! */
#define SX_CLOCK_USE_TIMESPEC64 (0)

/* these definitions should only be used with clock callbacks.
 * in other places driver may use its own timespec structure (timespec or timespec64).
 */

#if SX_CLOCK_USE_TIMESPEC64
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
#endif
/************************************************************************************/

#define SX_CLOCK_IS_DEV_SPECIFIC_CB_SUPPORTED(dev, func_name)                \
    ({                                                                       \
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

#define SX_CLOCK_DEV_SPECIFIC_CB(dev, func_name, ...)                        \
    ({                                                                       \
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
struct sx_clock_log_db {
    struct sx_clock_log_entry *cyc_buff;
    u32                        cyc_buff_size;
    spinlock_t                 lock;
    u32                        size;
    u32                        next;
};
extern int                    clock_activity_log;
extern struct sx_clock_log_db __log_activity;
#define SX_CLOCK_ACTIVITY_LOG(fmt, args ...)                        \
    do {                                                            \
        if (clock_activity_log) {                                   \
            sx_clock_log_add_string(&__log_activity, fmt, ## args); \
        }                                                           \
    } while (0)

struct sx_priv;
struct sx_tstamp;
struct skb_shared_hwtstamps;
struct ptp_clock_info;
struct cyclecounter;
struct sk_buff;

/* external functions */
int sx_core_clock_init(struct sx_priv *priv);
int sx_core_clock_deinit(struct sx_priv *priv);
int sx_core_clock_cqe_ts_to_utc(struct sx_priv        *priv,
                                const struct timespec *cqe_ts,
                                struct timespec       *utc);

/* common functions */
int sx_clock_log_init(struct sx_clock_log_db *log_db, u32 cyc_buff_size);
void sx_clock_log_deinit(struct sx_clock_log_db *log_db);
void sx_clock_log_dump(struct sx_clock_log_db *log_db,
                       struct seq_file        *m,
                       const char             *title);
void sx_clock_log_add_settime(s64 value);
void sx_clock_log_add_adjtime(s64 value);
void sx_clock_log_add_adjfreq(s64 value);
int sx_clock_log_add_string(struct sx_clock_log_db *log_db, const char *fmt, ...);
void sx_clock_log_add_s64(struct sx_clock_log_db *log_db, s64 value);
int sx_clock_register(struct sx_priv              *priv,
                      const struct ptp_clock_info *ptp_clock_info);
struct sx_dev * sx_clock_get_dev(void);
int sx_clock_queue_delayed_work(struct delayed_work *dwork,
                                unsigned long        delay);
void sx_clock_fill_hwtstamp_nsec(u64 nsec, struct skb_shared_hwtstamps *hwts);

/* SPC1 functions */
int sx_clock_init_spc1(struct sx_priv *priv);
int sx_clock_cleanup_spc1(struct sx_priv *priv);
void sx_clock_fill_hwtstamp_spc1(u64 frc, struct skb_shared_hwtstamps *hwts);
int sx_clock_dump_spc1(struct seq_file *m, void *v);

/* SPC2 functions */
int sx_clock_init_spc2(struct sx_priv *priv);
int sx_clock_cleanup_spc2(struct sx_priv *priv);
int sx_clock_cqe_ts_to_utc_spc2(struct sx_priv        *priv,
                                const struct timespec *cqe_ts,
                                struct timespec       *utc);
int sx_clock_dump_spc2(struct seq_file *m, void *v);

#endif  /* SX_CLOCK_H */
