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

#ifndef __PTP_H__
#define __PTP_H__


/************************************************
 * Includes
 ***********************************************/
#include <linux/mlx_sx/kernel_user.h>

/************************************************
 *  Defines
 ***********************************************/

/************************************************
 *  Enums
 ***********************************************/
enum {
    PTP_PACKET_INGRESS = 0,
    PTP_PACKET_EGRESS  = 1
};

enum ptp_message_type {
    PTP_MSG_SYNC                  = 1 << 0,
    PTP_MSG_DELAY_REQ             = 1 << 1,
    PTP_MSG_PDELAY_REQ            = 1 << 2,
    PTP_MSG_PDELAY_RESP           = 1 << 3,
    PTP_MSG_FOLLOW_UP             = 1 << 8,
    PTP_MSG_DELAY_RESP            = 1 << 9,
    PTP_MSG_PDELAY_RESP_FOLLOW_UP = 1 << 10,
    PTP_MSG_ANNOUNCE              = 1 << 11,
    PTP_MSG_SIGNALING             = 1 << 12,
    PTP_MSG_MANAGEMENT            = 1 << 13,

    PTP_MSG_TYPE_ALL = (1 << 16) - 1,

    PTP_MSG_EVENT_ALL   = (PTP_MSG_SYNC | PTP_MSG_DELAY_REQ | PTP_MSG_PDELAY_REQ | PTP_MSG_PDELAY_RESP),
    PTP_MSG_GENERAL_ALL = (PTP_MSG_TYPE_ALL & ~(PTP_MSG_EVENT_ALL))
};

/************************************************
 * Functions
 ***********************************************/

/* external functions */
int sx_core_ptp_dev_init(struct sx_priv *priv, ptp_mode_t ptp_mode);
int sx_core_ptp_dev_cleanup(struct sx_priv *priv);

int sx_core_ptp_rx_handler(struct sx_priv         *priv,
                           struct completion_info *ci,
                           int                     cqn);
int sx_core_ptp_tx_ts_handler(struct sx_priv *priv,
                              struct sk_buff *skb,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                              const struct timespec64 *tx_ts);
#else
                              const struct timespec *tx_ts);
#endif

/* common functions */
ptp_mode_t sx_ptp_get_mode(struct sx_priv *priv);
bool sx_ptp_is_enabled(struct sx_priv *priv);
int sx_core_is_ptp_packet(struct sk_buff *skb, u8 *is_ptp_pkt);
const char * sx_core_ptp_msg_type_to_str(u8 msg_type);
int sx_dbg_ptp_dump_proc_show(struct seq_file *m, void *v, void *context);

/* SPC1 functions */
int sx_ptp_dev_init_spc1(struct sx_priv *priv, ptp_mode_t ptp_mode);
int sx_ptp_dev_cleanup_spc1(struct sx_priv *priv);
int sx_ptp_dump_spc1(struct sx_priv *priv, struct seq_file *m, void *v, void *context);
int sx_ptp_rx_handler_spc1(struct sx_priv                      *priv,
                           struct completion_info              *ci,
                           ptp_mode_t                           ptp,
                           const struct sx_ptp_packet_metadata *pkt_meta);
int sx_ptp_tx_handler_spc1(struct sx_priv                      *priv,
                           struct sk_buff                      *skb,
                           const struct sx_ptp_packet_metadata *pkt_meta);
int sx_ptp_get_supported_tx_types_spc1(struct sx_priv *priv, u32 *tx_types);
int sx_ptp_set_tx_type_spc1(struct sx_priv *priv, int tx_type);
/* SPC2 functions */
int sx_ptp_dev_init_spc2(struct sx_priv *priv, ptp_mode_t ptp_mode);
int sx_ptp_dev_cleanup_spc2(struct sx_priv *priv);
int sx_ptp_dump_spc2(struct sx_priv *priv, struct seq_file *m, void *v, void *context);
int sx_ptp_rx_handler_spc2(struct sx_priv                      *priv,
                           struct completion_info              *ci,
                           ptp_mode_t                           ptp,
                           const struct sx_ptp_packet_metadata *pkt_meta);
int sx_ptp_tx_handler_spc2(struct sx_priv                      *priv,
                           struct sk_buff                      *skb,
                           const struct sx_ptp_packet_metadata *pkt_meta);
int sx_ptp_tx_ts_handler_spc2(struct sx_priv *priv,
                              struct sk_buff *skb,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                              const struct timespec64 *tx_ts);
#else
                              const struct timespec *tx_ts);
#endif
int sx_ptp_get_supported_tx_types_spc2(struct sx_priv *priv, u32 *tx_types);
int sx_ptp_set_tx_type_spc2(struct sx_priv *priv, int tx_type);
int sx_ptp_tx_control_to_data_spc2(struct sx_priv  *priv,
                                   struct sk_buff **orig_skb,
                                   struct isx_meta *meta,
                                   u16              port,
                                   u8               is_lag,
                                   u8              *is_tagged);

#endif  /* __PTP_H__ */
