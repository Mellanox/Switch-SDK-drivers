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

#include "fw.h"
#include "fw_internal.h"
#include <linux/mlx_sx/kernel_user.h>

#define MCIA_REG_ID 0x9014

enum {
    MCIA_INVALID_PORT         = 0x17,
    MCIA_PORT_NOT_SUPP        = 0x27,
    MCIA_NOT_CONNECTED        = 0x37,
    MCIA_NO_EEPROM            = 0x47,
    MCIA_INVALID_PAGE         = 0x57,
    MCIA_INVALID_DEVICE_ADDR  = 0x67,
    MCIA_INVALID_I2C_DEV_ADDR = 0x77,
    MCIA_CABLE_NOT_SUPP       = 0x87,
    MCIA_I2C_ERROR            = 0x97
};

static const char * mcia_err_str(u8 status)
{
    switch (status) {
    case MCIA_INVALID_PORT:
        return "Invalid port";

    case MCIA_PORT_NOT_SUPP:
        return "Port not supported";

    case MCIA_NOT_CONNECTED:
        return "Not connected";

    case MCIA_NO_EEPROM:
        return "No EEPROM";

    case MCIA_INVALID_PAGE:
        return "Invalid page";

    case MCIA_INVALID_DEVICE_ADDR:
        return "Invalid device address";

    case MCIA_INVALID_I2C_DEV_ADDR:
        return "Invalid I2C device address";

    case MCIA_CABLE_NOT_SUPP:
        return "Cable not supported";

    case MCIA_I2C_ERROR:
        return "I2C";

    default:
        return "Unknown";
    }
}


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

    if (op_tlv->status) {
        if (op_tlv->register_id != MCIA_REG_ID) {
            printk(KERN_WARNING "get_operation_tlv: Err: Got status 0x%x for register 0x%x\n",
                   op_tlv->status, op_tlv->register_id);
        } else {
            printk(KERN_WARNING "MCIA register reported %s error\n", mcia_err_str(op_tlv->status));
        }
    }
}
