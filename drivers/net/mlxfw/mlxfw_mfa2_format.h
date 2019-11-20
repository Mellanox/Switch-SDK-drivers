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

#ifndef _MLXFW_MFA2_FORMAT_H
#define _MLXFW_MFA2_FORMAT_H

#include "mlxfw_mfa2_file.h"
#include "mlxfw_mfa2_tlv.h"

enum mlxfw_mfa2_tlv_type {
    MLXFW_MFA2_TLV_MULTI_PART = 0x01,
    MLXFW_MFA2_TLV_PACKAGE_DESCRIPTOR = 0x02,
    MLXFW_MFA2_TLV_COMPONENT_DESCRIPTOR = 0x04,
    MLXFW_MFA2_TLV_COMPONENT_PTR = 0x22,
    MLXFW_MFA2_TLV_PSID = 0x2A,
};
enum mlxfw_mfa2_compression_type {
    MLXFW_MFA2_COMPRESSION_TYPE_NONE,
    MLXFW_MFA2_COMPRESSION_TYPE_XZ,
};
struct mlxfw_mfa2_tlv_package_descriptor {
    __be16 num_components;
    __be16 num_devices;
    __be32 cb_offset;
    __be32 cb_archive_size;
    __be32 cb_size_h;
    __be32 cb_size_l;
    u8     padding[3];
    u8     cv_compression;
    __be32 user_data_offset;
} __packed;

MLXFW_MFA2_TLV(package_descriptor, struct mlxfw_mfa2_tlv_package_descriptor,
               MLXFW_MFA2_TLV_PACKAGE_DESCRIPTOR);

struct mlxfw_mfa2_tlv_multi {
    __be16 num_extensions;
    __be16 total_len;
} __packed;

MLXFW_MFA2_TLV(multi, struct mlxfw_mfa2_tlv_multi,
               MLXFW_MFA2_TLV_MULTI_PART);

struct mlxfw_mfa2_tlv_psid {
    u8 psid[0];
} __packed;

MLXFW_MFA2_TLV_VARSIZE(psid, struct mlxfw_mfa2_tlv_psid,
                       MLXFW_MFA2_TLV_PSID);

struct mlxfw_mfa2_tlv_component_ptr {
    __be16 storage_id;
    __be16 component_index;
    __be32 storage_address;
} __packed;

MLXFW_MFA2_TLV(component_ptr, struct mlxfw_mfa2_tlv_component_ptr,
               MLXFW_MFA2_TLV_COMPONENT_PTR);

struct mlxfw_mfa2_tlv_component_descriptor {
    __be16 pldm_classification;
    __be16 identifier;
    __be32 cb_offset_h;
    __be32 cb_offset_l;
    __be32 size;
} __packed;

MLXFW_MFA2_TLV(component_descriptor, struct mlxfw_mfa2_tlv_component_descriptor,
               MLXFW_MFA2_TLV_COMPONENT_DESCRIPTOR);

#endif /* ifndef _MLXFW_MFA2_FORMAT_H */
