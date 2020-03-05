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
