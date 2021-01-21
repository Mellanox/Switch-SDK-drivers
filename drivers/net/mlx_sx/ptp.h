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

#ifndef __PTP_H__
#define __PTP_H__


/************************************************
 * Includes
 ***********************************************/
#include <linux/mlx_sx/kernel_user.h>

/************************************************
 *  Defines
 ***********************************************/

#define PTP_MAX_PORTS (MAX_PHYPORT_NUM + MAX_LAG_NUM)

/************************************************
 *  Enums
 ***********************************************/
enum {
    PTP_PACKET_INGRESS = 0,
    PTP_PACKET_EGRESS = 1
};

enum ptp_message_type {
    PTP_MSG_SYNC = 1 << 0,
    PTP_MSG_DELAY_REQ = 1 << 1,
    PTP_MSG_PDELAY_REQ = 1 << 2,
    PTP_MSG_PDELAY_RESP = 1 << 3,
    PTP_MSG_FOLLOW_UP = 1 << 8,
    PTP_MSG_DELAY_RESP = 1 << 9,
    PTP_MSG_PDELAY_RESP_FOLLOW_UP = 1 << 10,
    PTP_MSG_ANNOUNCE = 1 << 11,
    PTP_MSG_SIGNALING = 1 << 12,
    PTP_MSG_MANAGEMENT = 1 << 13,

    PTP_MSG_TYPE_ALL = (1 << 16) - 1,

    PTP_MSG_EVENT_ALL = (PTP_MSG_SYNC | PTP_MSG_DELAY_REQ | PTP_MSG_PDELAY_REQ | PTP_MSG_PDELAY_RESP),
    PTP_MSG_GENERAL_ALL = (PTP_MSG_TYPE_ALL & ~(PTP_MSG_EVENT_ALL))
};
struct sx_ptp_packet_fields {
    u16 seqid;
    u8  domain;
    u8  msg_type;
};
struct sx_ptp_packet_metadata {
    u16                         sysport_lag_id;
    u8                          timestamp_required;
    struct sx_ptp_packet_fields pkt_fields;
};

/************************************************
 * Functions
 ***********************************************/

/* external functions */
int sx_core_ptp_init(struct sx_priv *priv, ptp_mode_t ptp_mode);
int sx_core_ptp_cleanup(struct sx_priv *priv);

int sx_core_ptp_rx_handler(struct sx_priv         *priv,
                           struct completion_info *ci,
                           int                     cqn);
int sx_core_ptp_tx_ts_handler(struct sx_priv        *priv,
                              struct sk_buff        *skb,
                              const struct timespec *tx_ts);

/* common functions */
ptp_mode_t sx_ptp_get_mode(void);
int sx_core_is_ptp_packet(struct sk_buff *skb, u8 *is_ptp_pkt);

/* SPC1 functions */
int sx_ptp_init_spc1(struct sx_priv *priv, ptp_mode_t ptp_mode);
int sx_ptp_cleanup_spc1(struct sx_priv *priv);
int sx_ptp_dump_spc1(struct seq_file *m, void *v);
int sx_ptp_rx_handler_spc1(struct sx_priv                      *priv,
                           struct completion_info              *ci,
                           ptp_mode_t                           ptp,
                           const struct sx_ptp_packet_metadata *pkt_meta);
int sx_ptp_tx_handler_spc1(struct sx_priv                      *priv,
                           struct sk_buff                      *skb,
                           const struct sx_ptp_packet_metadata *pkt_meta);

/* SPC2 functions */
int sx_ptp_init_spc2(struct sx_priv *priv, ptp_mode_t ptp_mode);
int sx_ptp_cleanup_spc2(struct sx_priv *priv);
int sx_ptp_dump_spc2(struct seq_file *m, void *v);
int sx_ptp_rx_handler_spc2(struct sx_priv                      *priv,
                           struct completion_info              *ci,
                           ptp_mode_t                           ptp,
                           const struct sx_ptp_packet_metadata *pkt_meta);
int sx_ptp_tx_handler_spc2(struct sx_priv                      *priv,
                           struct sk_buff                      *skb,
                           const struct sx_ptp_packet_metadata *pkt_meta);
int sx_ptp_tx_ts_handler_spc2(struct sx_priv        *priv,
                              struct sk_buff        *skb,
                              const struct timespec *tx_ts);
int sx_ptp_tx_control_to_data_spc2(struct sx_priv  *priv,
                                   struct sk_buff **orig_skb,
                                   struct isx_meta *meta,
                                   u16              port,
                                   u8               is_lag,
                                   u8              *is_tagged,
                                   u8               hw_ts_required);

#endif  /* __PTP_H__ */
