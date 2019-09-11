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

#ifndef _MLXFW_MFA2_FILE_H
#define _MLXFW_MFA2_FILE_H

#include <linux/firmware.h>
#include <linux/kernel.h>

struct mlxfw_mfa2_file {
    const struct firmware       *fw;
    const struct mlxfw_mfa2_tlv *first_dev;
    u16                          dev_count;
    const struct mlxfw_mfa2_tlv *first_component;
    u16                          component_count;
    const void                  *cb; /* components block */
    u32                          cb_archive_size; /* size of compressed components block */
};
static inline bool mlxfw_mfa2_valid_ptr(const struct mlxfw_mfa2_file *mfa2_file, const void *ptr)
{
    const void *valid_to = mfa2_file->fw->data + mfa2_file->fw->size;
    const void *valid_from = mfa2_file->fw->data;

    return ptr > valid_from && ptr < valid_to;
}

#endif
