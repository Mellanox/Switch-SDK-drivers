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

struct sx_mst_ifc {
    int (*write)(int offset, int len, u8 *buf);
    int (*read)(int offset, int len, u8 *buf);
    u8  is_registered;
};

void sx_dpt_reg_i2c_ifc(struct sx_i2c_ifc *i2c_ifc);
void sx_dpt_reg_mst_ifc(struct sx_mst_ifc *mst_ifc);

void sx_dpt_dereg_i2c_ifc(void);
void sx_dpt_dereg_mst_ifc(void);

#endif /* __SX_I2C_IF_ */
