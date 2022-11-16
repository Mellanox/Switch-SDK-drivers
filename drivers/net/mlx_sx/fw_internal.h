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

#ifndef SX_FW_INTERNAL_H
#define SX_FW_INTERNAL_H

#define SX_PSID_SIZE 16

#define SX_GET(dest, source, offset)            \
    do {                                        \
        void *__p = (char*)(source) + (offset); \
        switch (sizeof(dest)) {                 \
        case 1:                                 \
            (dest) = *(u8*)__p;                 \
            break;                              \
        case 2:                                 \
            (dest) = be16_to_cpup(__p);         \
            break;                              \
        case 4:                                 \
            (dest) = be32_to_cpup(__p);         \
            break;                              \
        case 8:                                 \
            (dest) = be64_to_cpup(__p);         \
            break;                              \
        default:                                \
            break;                              \
        }                                       \
    } while (0)

#define SX_PUT(dest, source, offset)             \
    do {                                         \
        void *__d = ((char*)(dest) + (offset));  \
        switch (sizeof(source)) {                \
        case 1:                                  \
            *(u8*)__d = (source);                \
            break;                               \
        case 2:                                  \
            *(__be16*)__d = cpu_to_be16(source); \
            break;                               \
        case 4:                                  \
            *(__be32*)__d = cpu_to_be32(source); \
            break;                               \
        case 8:                                  \
            *(__be64*)__d = cpu_to_be64(source); \
            break;                               \
        default:                                 \
            break;                               \
        }                                        \
    } while (0)

struct ku_operation_tlv;

typedef int (*access_reg_encode_cb_t)(u8 *inbox, void *ku_reg, void *context);
typedef int (*access_reg_decode_cb_t)(u8 *outbox, void *ku_reg, void *context);

#define SX_ACCESS_REG_F_IGNORE_FW_RET_CODE (1 << 0)
#define SX_ACCESS_REG_F_SET_AND_GET        (1 << 1)

int sx_ACCESS_REG_internal(struct sx_dev           *dev,
                           uint8_t                  dev_id,
                           uint32_t                 flags,
                           struct ku_operation_tlv *op_tlv,
                           access_reg_encode_cb_t   reg_encode_cb,
                           access_reg_decode_cb_t   reg_decode_cb,
                           u16                      reg_len,
                           void                    *ku_reg,
                           void                    *context);

void set_operation_tlv(void *inbox, struct ku_operation_tlv *op_tlv);
void get_operation_tlv(void *outbox, struct ku_operation_tlv *op_tlv);

#endif /* SX_FW_INTERNAL_H */
