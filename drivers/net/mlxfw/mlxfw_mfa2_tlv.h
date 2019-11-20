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

#ifndef _MLXFW_MFA2_TLV_H
#define _MLXFW_MFA2_TLV_H

#include <linux/kernel.h>
#include "mlxfw_mfa2_file.h"

struct mlxfw_mfa2_tlv {
    u8     version;
    u8     type;
    __be16 len;
    u8     data[0];
} __packed;
static inline const struct mlxfw_mfa2_tlv * mlxfw_mfa2_tlv_get(const struct mlxfw_mfa2_file *mfa2_file,
                                                               const void                   *ptr)
{
    if (!mlxfw_mfa2_valid_ptr(mfa2_file, ptr) ||
        !mlxfw_mfa2_valid_ptr(mfa2_file, ptr + sizeof(struct mlxfw_mfa2_tlv))) {
        return NULL;
    }
    return ptr;
}

static inline const void * mlxfw_mfa2_tlv_payload_get(const struct mlxfw_mfa2_file *mfa2_file,
                                                      const struct mlxfw_mfa2_tlv  *tlv,
                                                      u8                            payload_type,
                                                      size_t                        payload_size,
                                                      bool                          varsize)
{
    void *tlv_top;

    tlv_top = (void*)tlv + be16_to_cpu(tlv->len) - 1;
    if (!mlxfw_mfa2_valid_ptr(mfa2_file, tlv) ||
        !mlxfw_mfa2_valid_ptr(mfa2_file, tlv_top)) {
        return NULL;
    }
    if (tlv->type != payload_type) {
        return NULL;
    }
    if (varsize && (be16_to_cpu(tlv->len) < payload_size)) {
        return NULL;
    }
    if (!varsize && (be16_to_cpu(tlv->len) != payload_size)) {
        return NULL;
    }

    return tlv->data;
}

#define MLXFW_MFA2_TLV(name, payload_type, tlv_type)                         \
    static inline const payload_type *                                       \
    mlxfw_mfa2_tlv_ ## name ## _get(const struct mlxfw_mfa2_file *mfa2_file, \
                                    const struct mlxfw_mfa2_tlv *tlv)        \
    {                                                                        \
        return mlxfw_mfa2_tlv_payload_get(mfa2_file, tlv,                    \
                                          tlv_type, sizeof(payload_type),    \
                                          false);                            \
    }

#define MLXFW_MFA2_TLV_VARSIZE(name, payload_type, tlv_type)                 \
    static inline const payload_type *                                       \
    mlxfw_mfa2_tlv_ ## name ## _get(const struct mlxfw_mfa2_file *mfa2_file, \
                                    const struct mlxfw_mfa2_tlv *tlv)        \
    {                                                                        \
        return mlxfw_mfa2_tlv_payload_get(mfa2_file, tlv,                    \
                                          tlv_type, sizeof(payload_type),    \
                                          true);                             \
    }

#endif /* ifndef _MLXFW_MFA2_TLV_H */
