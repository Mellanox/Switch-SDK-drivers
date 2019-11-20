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

#ifndef _MLXFW_MFA2_H
#define _MLXFW_MFA2_H

#include <linux/firmware.h>
#include "mlxfw.h"

struct mlxfw_mfa2_component {
    u16 index;
    u32 data_size;
    u8 *data;
};
struct mlxfw_mfa2_file;

bool mlxfw_mfa2_check(const struct firmware *fw);

struct mlxfw_mfa2_file * mlxfw_mfa2_file_init(const struct firmware *fw);

int mlxfw_mfa2_file_component_count(const struct mlxfw_mfa2_file *mfa2_file,
                                    const char *psid, u32 psid_size,
                                    u32 *p_count);

struct mlxfw_mfa2_component * mlxfw_mfa2_file_component_get(const struct mlxfw_mfa2_file *mfa2_file,
                                                            const char *psid, int psid_size,
                                                            int component_index);

void mlxfw_mfa2_file_component_put(struct mlxfw_mfa2_component *component);

void mlxfw_mfa2_file_fini(struct mlxfw_mfa2_file *mfa2_file);

#endif
