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

#ifndef __SX_I2C_IF_H_
#define __SX_I2C_IF_H_

struct sx_i2c_ifc {
    int (*write)(int i2c_dev_id, int offset, int len, u8 *in_out_buf);
    int (*read)(int i2c_dev_id, int offset, int len, u8 *in_out_buf);
    int (*write_dword)(int i2c_dev_id, int offset, u32 val);
    int (*read_dword)(int i2c_dev_id, int offset, u32 *val);
    int (*enforce)(int i2c_dev_id);
    int (*release)(int i2c_dev_id);
    int (*get_local_mbox)(int i2c_dev_id, u32 *mb_size_in,
                          u32 *mb_offset_in, u32 *mb_size_out, u32 *mb_offset_out);
    int (*get_fw_rev)(int i2c_dev_id, u64 *fw_rev);
    int (*set_go_bit_stuck)(int i2c_dev_id);
    u8  is_registered;
};

void sx_dpt_reg_i2c_ifc(struct sx_i2c_ifc *i2c_ifc);

void sx_dpt_dereg_i2c_ifc(void);

#endif /* __SX_I2C_IF_ */
