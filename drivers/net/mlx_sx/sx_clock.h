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


/************************************************
 * Includes
 ***********************************************/
#include <linux/types.h>
#include <linux/netdevice.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include "sx.h"

/************************************************
 *  Defines
 ***********************************************/
#define OFFSET_PTP_DOMAIN_NUMBER     4
#define SPC_PTP_CLOCK_FREQ_KHZ       156257 /* 6.4nSec */
#define SKB_MTPPTR_LOCAL_PORT_OFFSET 0x1D

#define PTP_RX_MAX_PPS_PER_PORT (394)
#define PTP_TX_MAX_PPS_PER_PORT (404)

#define IS_PTP_MODE_POLLING (ptp_working_mode == KU_PTP_MODE_POLLING)
#define IS_PTP_MODE_EVENTS  (ptp_working_mode == KU_PTP_MODE_EVENTS)

/************************************************
 *  Enums
 ***********************************************/
enum PTP_MESSAGE_TYPE {
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
enum ptp_counters {
    PTP_COUNTER_TOTAL,
    PTP_COUNTER_NEED_TIMESTAMP,
    PTP_COUNTER_FIFO_TRAP,
    PTP_COUNTER_GC_EVENTS,
    PTP_COUNTER_GC_RECORDS,
    PTP_COUNTER_RATE_LIMIT,
    PTP_COUNTER_FIFO_OVERFLOW,
    PTP_COUNTER_OUT_OF_MEMORY,
    PTP_COUNTER_PENDING_EVENTS,
    PTP_COUNTER_PENDING_RECORDS,
    PTP_COUNTER_LATE_MATCH,
    PTP_COUNTER_EMPTY_TS,
    PTP_COUNTER_REG_ACCESS_SUCCEEDED,
    PTP_COUNTER_REG_ACCESS_FAILED,
    PTP_COUNTER_LAST
};

#define PTP_MAX_PORTS (MAX_PHYPORT_NUM + MAX_LAG_NUM)

struct ptp_common_event_data {
    struct list_head list;
    u16              sequence_id;
    u8               msg_type;
    u8               domain_num;
    u8               need_timestamp;
    unsigned long    since;
};
struct ptp_rx_event_data {
    struct ptp_common_event_data common;
    struct completion_info      *ci;
};
struct ptp_tx_event_data {
    struct ptp_common_event_data common;
    struct sk_buff              *skb;
};

typedef void (*ptp_db_handle_cb_t)(struct ptp_common_event_data *ced, u64 frc);
typedef void (*ptp_db_gc_cb_t)(struct ptp_common_event_data *ced);

struct ptp_db {
    struct list_head   sysport_events_list[PTP_MAX_PORTS];
    struct list_head   sysport_records_list[PTP_MAX_PORTS];
    spinlock_t         sysport_lock[PTP_MAX_PORTS];
    u8                 direction;
    ptp_db_handle_cb_t handle_cb;
    ptp_db_gc_cb_t     gc_cb;
};
extern atomic64_t       ptp_counters[][PTP_COUNTER_LAST];
extern struct ptp_db    ptp_tx_db;
extern struct ptp_db    ptp_rx_db;
extern ptp_mode_t       ptp_working_mode;
extern struct semaphore ptp_polling_sem;
extern atomic64_t       ptp_rx_budget[PTP_MAX_PORTS];
extern atomic64_t       ptp_tx_budget[PTP_MAX_PORTS];

/************************************************
 * Functions
 ***********************************************/
int sx_ptp_init(struct sx_priv *priv, ptp_mode_t ptp_mode);
int sx_ptp_cleanup(struct sx_priv *priv);
int sx_ptp_pkt_parse(struct sk_buff *skb, u8 *is_ptp, u16 *evt_seqid, u8 *evt_dom_num, u8 *msg_type);
void sx_fill_hwstamp(struct sx_tstamp *tstamp, u64 timestamp, struct skb_shared_hwtstamps *hwts);

void ptp_dequeue_general_messages(u8 local_port, struct ptp_db *db);
void ptp_lookup_event(const u8 *mtpptr_buff, struct ptp_db *db);

struct ptp_rx_event_data * ptp_allocate_rx_event_data(gfp_t gfp);
void ptp_free_rx_event_data(struct ptp_rx_event_data *rx_event_data);

struct ptp_tx_event_data * ptp_allocate_tx_event_data(gfp_t gfp);
void ptp_free_tx_event_data(struct ptp_tx_event_data *tx_event_data);

#endif  /* SX_CLOCK_H */
