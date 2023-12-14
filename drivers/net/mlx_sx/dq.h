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

#ifndef DQ_H_
#define DQ_H_

#define SX_WQE_SHIFT 5
#define SX_DESC_SIZE 32
/************************************************
 * Includes
 ***********************************************/

#include <linux/mlx_sx/device.h>
#include "sx.h"


/************************************************
 * Structs
 ***********************************************/

/* DQ (SDQ/RDQ context) */
struct sx_dq_context {
    u8     cq;
    u8     sdq_tclass;
    u8     reserved1;
    u8     log2_dq_sz;
    u32    reserved2;
    u32    reserved3;
    u32    reserved4;
    __be64 dma_addr[8];   /* DQE buffer dma addresses */
    /* Physical Address of Descriptor Queue page <i> (i=0,1,...,7) */
};
#define DONT_FORCE_SDQ_ID 0xff

/************************************************
 * Functions
 ***********************************************/
void sx_core_post_recv(struct sx_dq *rdq, struct sk_buff *skb);
void sx_core_repost_recv(struct sx_dq *rdq);
int sx_core_init_sdq_table(struct sx_dev *dev);
int sx_core_init_rdq_table(struct sx_dev *dev);
int sx_core_create_sdq(struct sx_dev *dev, int nent,
                       u8 dqn, struct sx_dq **sdq_p);
int sx_core_create_rdq(struct sx_dev *dev, int nent,
                       u8 dqn, struct sx_dq **rdq_p);

void sx_core_destroy_sdq_table(struct sx_dev *dev, u8 free_table);
void sx_core_destroy_rdq_table(struct sx_dev *dev, u8 free_table);
void sx_core_destroy_sdq(struct sx_dev *dev, struct sx_dq *dq);
void sx_core_destroy_rdq(struct sx_dev *dev, struct sx_dq *dq);
int sx_add_pkts_to_sdq(struct sx_dq *sdq);
int sx_hw2sw_dq(struct sx_dev *dev, struct sx_dq *dq);
int sx_dq_modify_2err(struct sx_dev *dev, struct sx_dq *dq);
int sx_flush_dq(struct sx_dev *dev, struct sx_dq *dq, bool update_flushing_state);

int sx_core_add_rdq_to_monitor_rdq_list(struct sx_dq *dq);
void sx_core_del_rdq_from_monitor_rdq_list(struct sx_dq *dq);

#endif /* DQ_H_ */
/************************************************
 *                  EOF                         *
 ***********************************************/
