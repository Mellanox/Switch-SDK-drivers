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
