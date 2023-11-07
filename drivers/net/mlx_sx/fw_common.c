/*
 * Copyright (C) 2010-2023 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#include "fw.h"
#include "fw_internal.h"
#include <linux/mlx_sx/kernel_user.h>

void set_operation_tlv(void *inbox, struct ku_operation_tlv *op_tlv)
{
    u16 type_len = 0;
    u8  dr_status = 0;
    u8  r_method = 0;

#define TYPE_LEN_OFFSET    0x00
#define DR_STATUS_OFFSET   0x02
#define REGISTER_ID_OFFSET 0x04
#define R_METHOD_OFFSET    0x06
#define CLASS_OFFSET       0x07
#define TID_OFFSET         0x08

    type_len = op_tlv->length | (op_tlv->type << 11);
    SX_PUT(inbox, type_len, TYPE_LEN_OFFSET);
    dr_status = op_tlv->status | (op_tlv->dr << 7);
    SX_PUT(inbox, dr_status, DR_STATUS_OFFSET);
    SX_PUT(inbox, op_tlv->register_id, REGISTER_ID_OFFSET);
    r_method = op_tlv->method | (op_tlv->r << 7);
    SX_PUT(inbox, r_method, R_METHOD_OFFSET);
    SX_PUT(inbox, op_tlv->op_class, CLASS_OFFSET);
    SX_PUT(inbox, op_tlv->tid, TID_OFFSET);
}


void get_operation_tlv(void *outbox, struct ku_operation_tlv *op_tlv)
{
    u16 type_len = 0;
    u8  dr_status = 0;
    u8  r_method = 0;

#define TYPE_LEN_OFFSET    0x00
#define DR_STATUS_OFFSET   0x02
#define REGISTER_ID_OFFSET 0x04
#define R_METHOD_OFFSET    0x06
#define CLASS_OFFSET       0x07
#define TID_OFFSET         0x08

    SX_GET(type_len, outbox, TYPE_LEN_OFFSET);
    op_tlv->length = type_len & 0x7ff;
    op_tlv->type = type_len >> 11;
    SX_GET(dr_status, outbox, DR_STATUS_OFFSET);
    op_tlv->status = dr_status & 0x7f;
    op_tlv->dr = dr_status >> 7;
    SX_GET(op_tlv->register_id, outbox, REGISTER_ID_OFFSET);
    SX_GET(r_method, outbox, R_METHOD_OFFSET);
    op_tlv->method = r_method & 0x7f;
    op_tlv->r = r_method >> 7;
    SX_GET(op_tlv->op_class, outbox, CLASS_OFFSET);
    SX_GET(op_tlv->tid, outbox, TID_OFFSET);

    /* validate TLV header integrity */
    if (op_tlv->length != 4 /* length of operation TLV */) {
        printk(KERN_ERR "ERROR: Operation TLV is invalid: length=%u\n", op_tlv->length);
        print_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 16, 1, outbox, 16, 0);
        dump_stack();
        return;
    }

    /* validate TLV header integrity */
    if (op_tlv->type != TLV_TYPE_OPERATION_E) {
        printk(KERN_ERR "ERROR: Operation TLV is invalid: type=%u\n", op_tlv->type);
        print_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 16, 1, outbox, 16, 0);
        dump_stack();
        return;
    }
}
