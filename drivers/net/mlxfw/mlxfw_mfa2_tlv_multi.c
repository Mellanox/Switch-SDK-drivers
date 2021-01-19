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

#define pr_fmt(fmt) "MFA2: " fmt

#include "mlxfw_mfa2_tlv_multi.h"
#include <uapi/linux/netlink.h>

#define MLXFW_MFA2_TLV_TOTAL_SIZE(tlv) \
    NLA_ALIGN(sizeof(*(tlv)) + be16_to_cpu((tlv)->len))

const struct mlxfw_mfa2_tlv * mlxfw_mfa2_tlv_multi_child(const struct mlxfw_mfa2_file      *mfa2_file,
                                                         const struct mlxfw_mfa2_tlv_multi *multi)
{
    size_t multi_len;

    multi_len = NLA_ALIGN(sizeof(struct mlxfw_mfa2_tlv_multi));
    return mlxfw_mfa2_tlv_get(mfa2_file, (void*)multi + multi_len);
}

const struct mlxfw_mfa2_tlv * mlxfw_mfa2_tlv_next(const struct mlxfw_mfa2_file *mfa2_file,
                                                  const struct mlxfw_mfa2_tlv  *tlv)
{
    const struct mlxfw_mfa2_tlv_multi *multi;
    u16                                tlv_len;
    void                              *next;

    tlv_len = MLXFW_MFA2_TLV_TOTAL_SIZE(tlv);

    if (tlv->type == MLXFW_MFA2_TLV_MULTI_PART) {
        multi = mlxfw_mfa2_tlv_multi_get(mfa2_file, tlv);
        if (!multi) {
            pr_err("multi TLV get error\n");
            return NULL;
        }
        tlv_len = NLA_ALIGN(tlv_len + be16_to_cpu(multi->total_len));
    }

    next = (void*)tlv + tlv_len;
    return mlxfw_mfa2_tlv_get(mfa2_file, next);
}

const struct mlxfw_mfa2_tlv * mlxfw_mfa2_tlv_advance(const struct mlxfw_mfa2_file *mfa2_file,
                                                     const struct mlxfw_mfa2_tlv  *from_tlv,
                                                     u16                           count)
{
    const struct mlxfw_mfa2_tlv *tlv;
    u16                          idx;

    mlxfw_mfa2_tlv_foreach(mfa2_file, tlv, idx, from_tlv, count)
    if (!tlv) {
        return NULL;
    }
    return tlv;
}

const struct mlxfw_mfa2_tlv * mlxfw_mfa2_tlv_multi_child_find(const struct mlxfw_mfa2_file      *mfa2_file,
                                                              const struct mlxfw_mfa2_tlv_multi *multi,
                                                              enum mlxfw_mfa2_tlv_type           type,
                                                              u16                                index)
{
    const struct mlxfw_mfa2_tlv *tlv;
    u16                          skip = 0;
    u16                          idx;

    mlxfw_mfa2_tlv_multi_foreach(mfa2_file, tlv, idx, multi) {
        if (!tlv) {
            pr_err("TLV parsing error\n");
            return NULL;
        }
        if (tlv->type == type) {
            if (skip++ == index) {
                return tlv;
            }
        }
    }
    return NULL;
}

int mlxfw_mfa2_tlv_multi_child_count(const struct mlxfw_mfa2_file      *mfa2_file,
                                     const struct mlxfw_mfa2_tlv_multi *multi,
                                     enum mlxfw_mfa2_tlv_type           type,
                                     u16                               *p_count)
{
    const struct mlxfw_mfa2_tlv *tlv;
    u16                          count = 0;
    u16                          idx;

    mlxfw_mfa2_tlv_multi_foreach(mfa2_file, tlv, idx, multi) {
        if (!tlv) {
            pr_err("TLV parsing error\n");
            return -EINVAL;
        }

        if (tlv->type == type) {
            count++;
        }
    }
    *p_count = count;
    return 0;
}
