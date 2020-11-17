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

#ifndef __SGMII_INTERNAL_H__
#define __SGMII_INTERNAL_H__

#include <linux/types.h>
#include <linux/if_vlan.h>

#include <linux/mlx_sx/kernel_user.h>
#include "sgmii.h"
#include "counter.h"
#include "map.h"

struct sgmii_control_segment;
struct sgmii_tx_base_header_version_0;
extern struct sx_globals sx_glb;
extern int               rx_debug;
extern int               rx_dump;
extern int               tx_debug;
extern int               tx_dump;

/* *************************************************************************************** */
/* SGMII misc                                                                              */
/* *************************************************************************************** */

int sgmii_init(void);

int sgmii_get_send_interval_msec_by_transport(sxd_command_type_t transport_type);
int sgmii_get_send_attempts_by_transport(sxd_command_type_t transport_type);
int sgmii_get_cr_send_attempts(void);
int sgmii_get_cr_send_interval_msec(void);
int sgmii_get_send_attempts(void);
int sgmii_get_send_interval_msec(void);
int sgmii_get_rx_pps(void);

ku_chassis_type_t sgmii_get_chassis_type(void);
ku_mgmt_board_t sgmii_get_management_board(void);
uint8_t sgmii_get_cqe_ver(void);

typedef void (*sgmii_task_t)(void *task_param);
int sgmii_queue_task(sgmii_task_t task, const void *param_buff, int param_buff_size, unsigned long delay);

static inline void __sgmii_bit_field_set(u32 *target, u32 lsb, u32 msb, u32 val)
{
    const u32 mask = (1 << (msb - lsb + 1)) - 1;

    (*target) |= (val & mask) << lsb;
}

static inline void __sgmii_64bit_field_set(u32 *_32bit_h, u32 *_32bit_l, u64 val)
{
    __sgmii_bit_field_set(_32bit_h, 0, 31, (u32)(val >> 32));
    __sgmii_bit_field_set(_32bit_l, 0, 31, (u32)(val & 0xffffffff));
}

/* *************************************************************************************** */
/* SGMII device database                                                                   */
/* *************************************************************************************** */

struct sgmii_dev_counters {
    struct sx_core_counter_category category;
    struct sx_core_counter          emad_tx;
    struct sx_core_counter          emad_rx;
    struct sx_core_counter          emad_timeout;
    struct sx_core_counter          emad_terminated;
    struct sx_core_counter          emad_retransmission;
    struct sx_core_counter          emad_send_failed;
    struct sx_core_counter          emad_transaction_init_failed;
    struct sx_core_counter          emad_transaction_completed;
    struct sx_core_counter          emad_dev_mismatch;
    struct sx_core_counter          emad_unsolicited;
    struct sx_core_counter          mad_tx;
    struct sx_core_counter          mad_rx;
    struct sx_core_counter          mad_timeout;
    struct sx_core_counter          mad_terminated;
    struct sx_core_counter          mad_retransmission;
    struct sx_core_counter          mad_send_failed;
    struct sx_core_counter          mad_unrecognized_packet;
    struct sx_core_counter          mad_transaction_init_failed;
    struct sx_core_counter          mad_transaction_completed;
    struct sx_core_counter          mad_dev_mismatch;
    struct sx_core_counter          cr_space_invalid_size;
    struct sx_core_counter          cr_space_skb_alloc_failed;
    struct sx_core_counter          cr_space_read;
    struct sx_core_counter          cr_space_write;
    struct sx_core_counter          cr_space_rx;
    struct sx_core_counter          cr_space_timeout;
    struct sx_core_counter          cr_space_retransmission;
    struct sx_core_counter          cr_space_send_failed;
    struct sx_core_counter          cr_space_transaction_init_failed;
    struct sx_core_counter          cr_space_transaction_completed;
    struct sx_core_counter          cr_space_interrupted;
    struct sx_core_counter          misc_tx;
    struct sx_core_counter          misc_send_failed;
    struct sx_core_counter          tx_invalid_argument;
    struct sx_core_counter          tx_invalid_metadata;
    struct sx_core_counter          tx_sgmii_not_initialized;
    struct sx_core_counter          tx_skb_cow_failed;
    struct sx_core_counter          tx_skb_clone_failed;
    struct sx_core_counter          tx_skb_fragmented;
    struct sx_core_counter          tx_netdev_carrier_down;
    struct sx_core_counter          tx_exceeds_mtu;
    struct sx_core_counter          tx_dev_queue_xmit_failed;
    struct sx_core_counter          tx_ok;
    struct sx_core_counter          rx_untagged_frame;
    struct sx_core_counter          rx_warn_vlan_mismatch;
    struct sx_core_counter          rx_invalid_ethertype;
    struct sx_core_counter          rx_cqe_trimmed;
    struct sx_core_counter          rx_cqev0_handler_failed;
    struct sx_core_counter          rx_cqev2_handler_failed;
    struct sx_core_counter          rx_cqev0_ok;
    struct sx_core_counter          rx_cqev2_ok;
    struct sx_core_counter          cr_space_default_device_not_configured;
    struct sx_core_counter          cr_space_dev_mismatch;
    struct sx_core_counter          cr_space_invalid_oob_checks;
    struct sx_core_counter          cr_space_invalid_trap_id;
    struct sx_core_counter          cr_space_misc_failed;
    struct sx_core_counter          cr_space_unsolicited;
    struct sx_core_counter          cr_space_snipped_data;
};
struct sgmii_global_counters {
    struct sx_core_counter_category category;

    /* TX */
    struct sx_core_counter tx_not_sgmii_dev;
    struct sx_core_counter tx_default_device_not_configured;
    struct sx_core_counter tx_mad_deferred_send_failed;

    /* RX */
    struct sx_core_counter rx_rate_limiter;
    struct sx_core_counter rx_skb_share_check_failed;
    struct sx_core_counter rx_skb_fragmented;
    struct sx_core_counter rx_skb_linearize_failed;
    struct sx_core_counter rx_no_encap_header;
    struct sx_core_counter rx_zero_src_mac;
    struct sx_core_counter rx_src_mac_not_found;
};
extern struct sgmii_global_counters __sgmii_global_counters;
struct sgmii_dev;

int sgmii_dev_db_init(void);
void sgmii_dev_db_deinit(void);
int sgmii_dev_get_by_mac(const uint8_t *mac, struct sgmii_dev **sgmii_dev);
int sgmii_dev_get_by_id(int dev_id, struct sgmii_dev **sgmii_dev);
void sgmii_dev_inc_ref(struct sgmii_dev *sgmii_dev);
void sgmii_dev_dec_ref(struct sgmii_dev *sgmii_dev);

struct sgmii_dev_counters * sgmii_dev_get_counters(struct sgmii_dev *sgmii_dev);
#define SGMII_DEV_INC_COUNTER(dev, counter) COUNTER_INC(&sgmii_dev_get_counters(dev)->counter)

const struct ku_dpt_sgmii_info * sgmii_dev_get_dpt_info(const struct sgmii_dev *sgmii_dev);
int sgmii_dev_get_id(const struct sgmii_dev *sgmii_dev);

/* *************************************************************************************** */
/* SGMII transport                                                                         */
/* *************************************************************************************** */

#define ZERO_MAC(mac)               (!((mac)[0] || (mac)[1] || (mac)[2] || (mac)[3] || (mac)[4] || (mac)[5]))
#define CONVERT_TO_NETWORK_ORDER(x) do { (x) = htonl(x); } while (0)

enum {
    SGMII_PCP_BEST_EFFORT = 0,
    SGMII_PCP_LOW = 2,
    SGMII_PCP_MED = 3,
    SGMII_PCP_HIGH = 7,
    SGMII_PCP_FROM_METADATA = 255
};

typedef void (*sgmii_fill_control_segment_cb_t)(const struct isx_meta        *meta,
                                                struct sgmii_control_segment *control_segment);
typedef void (*sgmii_fill_tx_base_header_cb_t)(const struct isx_meta                 *meta,
                                               struct sgmii_tx_base_header_version_0 *tx_base_header);


struct sgmii_encapsulation_header_tx {
    struct vlan_ethhdr eth_vlan_hdr;
    u16                ver_reserved;
} __attribute__((packed));
struct sgmii_control_segment {
    __be32 line_0; /* swid, ipcs, dmc, isx, dr_tq, type, send_flow, lp */
    __be32 line_1; /* cr_ver */
    __be32 line_2; /* reserved */
    __be32 line_3; /* reserved */
} __attribute__((packed));
struct sgmii_tx_base_header_version_0 {
    __be32 line_0; /* version, ctl, u/l, mc, protocol, etclass, drop precedence, swid */
    __be32 line_1; /* system_port_mid, ingress trap, ctclass3, rdq, cpu_signature */
    __be32 line_2; /* lag_sub_port, rp_system_port_lag_id */
    __be32 line_3; /* signature, stclass, local_source_port, emad, src_lag, type */
} __attribute__((packed));


int sgmii_transport_init(const char       *netdev_name,
                         const uint8_t    *netdev_mac,
                         ku_chassis_type_t chassis_type,
                         uint8_t           cqe_ver);

void sgmii_transport_deinit(void);

const char * sgmii_get_netdev_name(void);
int sgmii_get_netdev_mac(uint8_t *netdev_mac);

void sgmii_fill_common_control_segment(const struct isx_meta        *meta,
                                       struct sgmii_control_segment *control_seg);

void sgmii_fill_common_tx_base_header(const struct isx_meta                 *meta,
                                      struct sgmii_tx_base_header_version_0 *tx_base_header);

int sgmii_rx_skb_cb_dev_id_get(struct sk_buff *skb, struct sgmii_dev **sgmii_dev);

int sgmii_get_operational_rx_pps(void);

int sgmii_send(struct sgmii_dev               *sgmii_dev,
               struct sk_buff                 *skb,
               const struct isx_meta          *meta,
               u8                              pcp,
               sgmii_fill_control_segment_cb_t fill_control_segment_cb,
               sgmii_fill_tx_base_header_cb_t  fill_tx_base_header_cb);

/* *************************************************************************************** */
/* SGMII transaction                                                                       */
/* *************************************************************************************** */

enum sgmii_transaction_completion_status {
    SGMII_TR_COMP_ST_COMPLETED,
    SGMII_TR_COMP_ST_RX_DEV_MISMATCH,
    SGMII_TR_COMP_ST_TIMEDOUT,
};

typedef uint64_t sgmii_transaction_id_t;

struct sgmii_sync_transaction_context {
    struct sgmii_transaction_db             *tr_db;
    sgmii_transaction_id_t                   tr_id;
    struct completion                        completion;
    struct sk_buff                          *rx_skb; /* the skb that completed the transaction */
    enum sgmii_transaction_completion_status status;
};
struct sgmii_transaction_meta {
    struct sgmii_transaction_db *tr_db;
    sgmii_transaction_id_t       tr_id;
    struct sk_buff              *skb;
    sxd_command_type_t           transport_type;
};
struct sgmii_transaction_db;
struct sgmii_transaction_info;
struct sgmii_transaction_meta;

typedef void (*sgmii_transaction_entry_handler_cb)(int                            err,
                                                   struct sgmii_transaction_info *tr_info,
                                                   void                          *context);
typedef void (*sgmii_transaction_completion_cb_t)(struct sk_buff                          *rx_skb,
                                                  enum sgmii_transaction_completion_status status,
                                                  struct sgmii_transaction_info           *tr_info,
                                                  void                                    *context);

typedef int (*sgmii_transaction_sync_send_cb)(int                                    dev_id,
                                              struct sk_buff                        *skb,
                                              const struct isx_meta                 *meta,
                                              struct sgmii_sync_transaction_context *context);

struct sgmii_transaction_db {
    struct sx_core_map                 db_map;
    spinlock_t                         db_lock;
    sgmii_fill_control_segment_cb_t    fill_control_segment_cb;
    sgmii_fill_tx_base_header_cb_t     fill_tx_base_header_cb;
    sgmii_transaction_entry_handler_cb entry_handler_cb;
    sgmii_transaction_completion_cb_t  transaction_completion_cb;
};
struct sgmii_transaction_info {
    struct sgmii_transaction_db *tr_db;
    sgmii_transaction_id_t       tr_id;
    struct sgmii_dev            *rx_dev;
    struct sgmii_dev            *orig_tx_dev;
    int                          send_attempts_so_far;
};

int sgmii_transaction_db_init(struct sgmii_transaction_db       *tr_db,
                              sgmii_fill_control_segment_cb_t    fill_control_segment_cb,
                              sgmii_fill_tx_base_header_cb_t     fill_tx_base_header_cb,
                              sgmii_transaction_entry_handler_cb entry_handler_cb,
                              sgmii_transaction_completion_cb_t  transaction_completion_cb);

int sgmii_transaction_check_completion(struct sgmii_transaction_db *tr_db,
                                       struct sk_buff              *rx_skb,
                                       sgmii_transaction_id_t       tr_id,
                                       struct sgmii_dev            *rx_dev);

int sgmii_send_transaction(struct sgmii_transaction_meta *tr_meta,
                           struct sgmii_dev              *sgmii_dev,
                           const struct isx_meta         *isx_meta,
                           void                          *context);

int sgmii_send_transaction_sync(int                            dev_id,
                                struct sk_buff                *skb,
                                const struct isx_meta         *meta,
                                sgmii_transaction_sync_send_cb send_cb,
                                struct sk_buff               **rx_skb);

void sgmii_sync_transaction_complete(struct sgmii_sync_transaction_context   *context,
                                     struct sk_buff                          *rx_skb,
                                     enum sgmii_transaction_completion_status status);

/* *************************************************************************************** */
/* SGMII EMAD                                                                              */
/* *************************************************************************************** */

int sgmii_emad_init(void);
void sgmii_emad_deinit(void);
int sgmii_emad_get_transactions_in_progress(void);

int sgmii_emad_access_ppad(int dev_id, const struct ku_ppad_reg *reg_ppad);
int sgmii_emad_access_hopf(int dev_id, const struct ku_hopf_reg *reg_hopf);

/* *************************************************************************************** */
/* SGMII MAD                                                                               */
/* *************************************************************************************** */

int sgmii_mad_init(void);
void sgmii_mad_deinit(void);
int sgmii_mad_get_transactions_in_progress(void);

/* *************************************************************************************** */
/* SGMII CR-Space                                                                          */
/* *************************************************************************************** */

int sgmii_cr_space_init(void);
void sgmii_cr_space_deinit(void);

int sgmii_cr_space_get_transactions_in_progress(void);
uint8_t sgmii_cr_space_check_for_response(struct sgmii_dev *sgmii_dev, struct sk_buff *skb);


#endif /* __SGMII_INTERNAL_H__ */
