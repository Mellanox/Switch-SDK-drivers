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

#ifndef SX_CQ_H
#define SX_CQ_H

/************************************************
 * Includes
 ***********************************************/

#include <linux/types.h>
#include "sx.h"

#define CQN_INVALID 255

#define ETH_CRC_LENGTH 4
#define IB_CRC_LENGTH  6

/* do we need to put timestamp on packets? */
#define IS_CQ_WORKING_WITH_TIMESTAMP(dev, cqn) \
    (sx_bitmap_test(&sx_priv(dev)->cq_table.ts_bitmap, (cqn)))

/* do we need to put HW (not Linux) timestamp on packets? */
#define IS_CQ_WORKING_WITH_HW_TIMESTAMP(dev, cqn) \
    (sx_bitmap_test(&sx_priv(dev)->cq_table.ts_hw_utc_bitmap, (cqn)))

/************************************************
 * Enums
 ***********************************************/

enum {
    SX_CQE_OWNER_MASK = 0x01,
    SX_CQE_IS_SEND_MASK = 0x40,
    SX_CQE_IS_ERR_MASK = 0x80,
    SX_CQE_DQN_MASK = 0x1f,
    SX_CQE_DQN_MSB_MASK = 0x4000,
    SX_CQE_DQN_MSB_SHIFT = 5,
};

/************************************************
 * Structures
 ***********************************************/

struct sx_cq_context {
    u8     eq_num;   /* 0 or 1 */
    u8     reserved1;
    u8     flags;
    u8     log_cq_size;
    u16    reserved2;
    __be16 producer_counter;
    u16    reserved3;
    u16    reserved4;
    u32    reserved5;
    __be64 dma_addr[8];   /* CQE buffer dma addresses */
};
struct sx_cqe_v0 {
    u8     vlan2_lag_subport;
    u8     lag;
    __be16 system_port_lag_id;
    __be16 wqe_counter;
    __be16 dqn5_byte_count;
    __be16 ulp_crc_vlan_flow;
    __be16 trap_id;
    __be16 reserved1;
    u8     type_swid;
    u8     e_sr_dqn_owner;
};
struct sx_cqe_v1 {
    u8     version_e_sr_packet_ok_rp_lag;
    u8     rp_lag_subport;
    __be16 rp_system_port_lag_id;
    __be16 wqe_counter;
    __be16 isx_ulp_crc_byte_count;
    __be16 vlan;
    __be16 sma_check_id_trap_id;
    __be16 time_stamp;
    u8     type_swid_crc;
    u8     dqn_owner;
};
struct sx_cqe_v2 {
    u8     version_e_sr_packet_ok_rp_lag;
    u8     rp_lag_subport;
    __be16 rp_system_port_lag_id;
    __be16 wqe_counter;
    __be16 isx_ulp_crc_byte_count;
    __be16 vlan_mirror_cong2;
    __be16 sma_check_id_trap_id;
    __be16 time_stamp1;
    u8     type_swid_crc;
    u8     dqn;
    u8     mirror_tclass_mirror_elph_ep_lag;
    u8     ep_lag_subport;
    __be16 ep_system_port_lag_id;
    __be32 mirror_cong1_user_def_val_orig_pkt_len;
    __be32 mirror_reason_time_stamp_type_time_stamp2;
    __be16 mirror_latency2;
    u8     mirror_latency1;
    u8     pe2cqe_token_owner;
};
union sx_cqe {
    struct sx_cqe_v0 *v0;
    struct sx_cqe_v1 *v1;
    struct sx_cqe_v2 *v2;
};

/************************************************
 * Globals
 ***********************************************/
#ifdef CONFIG_SX_DEBUG
extern int sx_debug_cqn;
#endif
/************************************************
 * Inline Functions
 ***********************************************/

static inline void sx_cq_arm(struct sx_cq *cq)
{
#ifndef NO_PCI
    unsigned long flags;

    sx_priv(cq->sx_dev)->cq_last_time_armed[cq->cqn] = jiffies;
    spin_lock_irqsave(&cq->rearm_lock, flags);

    /*
     * Make sure that descriptors are written before
     * doorbell.
     */
    wmb();

    __raw_writel((__force u32)cpu_to_be32(cq->cons_index & 0xffff),
                 cq->arm_db);

    mmiowb();
    spin_unlock_irqrestore(&cq->rearm_lock, flags);
#endif
}

/* Update the Consumer Index */
static inline void sx_cq_set_ci(struct sx_cq *cq)
{
#ifndef NO_PCI
    /*
     * Make sure that descriptors are written before
     * doorbell.
     */
    wmb();

    __raw_writel((__force u32)cpu_to_be32((cq->cons_index + cq->nent) &
                                          0xffff), cq->set_ci_db);

    mmiowb();
#endif
}

/************************************************
 * Functions
 ***********************************************/
int dispatch_pkt(struct sx_dev *dev, struct completion_info *ci, u16 hw_synd, int dispatch_default);
int sx_core_init_cq_table(struct sx_dev *dev);
void sx_core_destroy_cq_table(struct sx_dev *dev);
int sx_core_create_cq(struct sx_dev *dev, int nent, struct sx_cq **cq, u8 cqn);
void sx_core_destroy_cq(struct sx_dev *dev, struct sx_cq *cq);
int sx_cq_completion(struct sx_dev *dev, u32 cqn, u16 weight, const struct timespec *timestamp,
                     struct sx_bitmap *prio_bitmap);
void sx_core_dump_synd_tbl(struct sx_dev *dev);
int rx_skb(void *context, struct sk_buff *skb, union sx_cqe *u_cqe, const struct sx_rx_timestamp *rx_timestamp,
           int is_from_monitor_rdq, struct listener_entry* force_listener, u8 dev_id);
void sx_get_cqe_all_versions(struct sx_cq *cq, uint32_t n, union sx_cqe *cqe_p);
int sx_cq_credit_thread_handler(void *cq_ctx);
void wqe_sync_for_cpu(struct sx_dq *dq, int idx);
int iterate_active_cqs(struct sx_dev *dev, struct sx_bitmap *active_cq_bitmap);
void sx_cq_show_cq(struct sx_dev *dev, int cqn);
void sx_cq_dump_cq(struct sx_dev *dev, int cqn);
void sx_cq_flush_rdq(struct sx_dev *my_dev, int idx);
void sx_printk_cqe_v0(union sx_cqe *u_cqe);
void sx_printk_cqe_v2(union sx_cqe *u_cqe);
void sx_fill_ci_from_cqe_v0(struct completion_info *ci, union sx_cqe *u_cqe);
void sx_fill_ci_from_cqe_v2(struct completion_info *ci, union sx_cqe *u_cqe);
void sx_fill_params_from_cqe_v0(union sx_cqe *u_cqe, u16 *hw_synd_p, u8  *is_isx_p,
                                u16 *byte_count_p, u8 *dqn_p, u8  *crc_present_p);
void sx_fill_params_from_cqe_v2(union sx_cqe *u_cqe, u16 *hw_synd_p, u8  *is_isx_p,
                                u16 *byte_count_p, u8 *dqn_p, u8  *crc_present_p);
void sx_init_cq_db_v0(struct sx_cq *tcq, u8 cqn, u8 *cqe_ver);
void sx_init_cq_db_spc(struct sx_cq *tcq, u8 cqn, u8 *cqe_ver);
void sx_init_cq_db_v2(struct sx_cq *tcq, u8 cqn, u8 *cqe_ver);

void set_timestamp_of_rx_packet(struct sx_cq                 *cq,
                                const struct timespec        *linux_ts,
                                const struct sx_rx_timestamp *cqe_ts,
                                struct sx_rx_timestamp       *rx_ts);

#endif /* SX_CQ_H */

/************************************************
 *                  EOF                         *
 ***********************************************/
