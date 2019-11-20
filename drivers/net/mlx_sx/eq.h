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

#ifndef EQ_H_
#define EQ_H_

/************************************************
 * Enum
 ***********************************************/

enum SX_NUM_EQE {
    SX_NUM_COMP_EQE = 0x100,
    SX_NUM_ASYNC_EQE = 0x100,
    SX_NUM_SPARE_EQE = 0x80
};
enum SX_EQ_STATE {
    SX_EQ_STATE_ARMED = 0x01,
    SX_EQ_STATE_FIRED = 0x00,
    SX_EQ_STATE_ALWAYS_ARMED = 0x03
};
enum SX_EQ_PKT_TYPE {
    SX_EQ_PKT_TYPE_RAW_IB = 0x000,
    SX_EQ_PKT_TYPE_IB_TRANS = 0x001, /* IB transport  */
    SX_EQ_PKT_TYPE_ETH = 0x010,
    SX_EQ_PKT_TYPE_FC_IB = 0x100,    /* Fibre Channel over IB */
    SX_EQ_PKT_TYPE_FC_ETH = 0x101   /* Fibre Channel over Ethernet */
};
enum SX_EQ_TYPE {
    SX_EQ_ASYNC,
    SX_EQ_COMP,
    SX_NUM_EQ
};

/************************************************
 * Structs
 ***********************************************/

/* Event Que */
struct sx_eq_context {
    u8     int_msi_x;
    u8     reserved1;
    u8     flags;
    u8     log_eq_size;
    u16    reserved2;
    __be16 producer_counter;
    u64    reserved3;
    __be64 dma_addr[8];
};

/* Event Que Entry (Descriptor)*/
struct sx_eqe {
    union {
        u32 raw[3];
        struct {
            __be16 token;
            u8     reserved1;
            u8     status;
            __be64 out_param;
        } __attribute__((packed)) cmd;
    }   event;
    u8 type;
    u8 subtype;
    u8 cqn;
    u8 owner;   /* SW(consumer)/HW(producer) owner*/
} __attribute__((packed));

/************************************************
 * Externals
 ***********************************************/
extern struct tasklet_struct intr_tasklet;

/************************************************
 * Functions prototype
 ***********************************************/

int sx_init_eq_table(struct sx_dev *dev);
void sx_cleanup_eq_table(struct sx_dev *dev);

#endif /* EQ_H_ */

/************************************************
 *                  EOF                         *
 ***********************************************/
