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

#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include "../sx_proc.h"

#define PROC_DUMP(fmt, args ...) printk(KERN_ERR fmt, ## args)

int sx_proc_handle_access_reg_auto(struct sx_dev *dev, char *p, u32 dev_id, u32 reg_id, char *running)
{
    int err = 0;
    u32 access_method = 1;
    u32 temp = 0;

    switch (reg_id) {
    case MLXSW_PAOS_ID:
    {
        struct ku_access_paos_reg reg_data;
        memset(&reg_data, 0, sizeof(reg_data));
        reg_data.dev_id = dev_id;
        running = sx_proc_str_get_u32(running, &access_method);
        sx_cmd_set_op_tlv(&reg_data.op_tlv, reg_id, access_method);

        if (access_method == 2) {
            running = sx_proc_str_get_u32(running, &temp);
            reg_data.paos_reg.swid = (u8)temp;
            running = sx_proc_str_get_u32(running, &temp);
            reg_data.paos_reg.local_port = (u8)temp;
            running = sx_proc_str_get_u32(running, &temp);
                reg_data.paos_reg.lp_msb = (u8)temp;
                running = sx_proc_str_get_u32(running, &temp);
            reg_data.paos_reg.admin_status = (u8)temp;
            running = sx_proc_str_get_u32(running, &temp);
            reg_data.paos_reg.oper_status = (u8)temp;
            running = sx_proc_str_get_u32(running, &temp);
            reg_data.paos_reg.ase = (u8)temp;
            running = sx_proc_str_get_u32(running, &temp);
            reg_data.paos_reg.ee = (u8)temp;
            running = sx_proc_str_get_u32(running, &temp);
            reg_data.paos_reg.e = (u8)temp;
            PROC_DUMP("Executing ACCESS_REG_PAOS write command\n");
            err = sx_ACCESS_REG_PAOS(dev, &reg_data);
            if (err) {
                goto out;
            }
            PROC_DUMP("Finished executing write ACCESS_REG_PAOS command.\n");
        } else if (access_method == 1) {
            running = sx_proc_str_get_u32(running, &temp);
            reg_data.paos_reg.swid = (u8)temp;

            running = sx_proc_str_get_u32(running, &temp);
            reg_data.paos_reg.local_port = (u8)temp;

            running = sx_proc_str_get_u32(running, &temp);
                reg_data.paos_reg.lp_msb = (u8)temp;

                running = sx_proc_str_get_u32(running, &temp);
            reg_data.paos_reg.admin_status = (u8)temp;

            running = sx_proc_str_get_u32(running, &temp);
            reg_data.paos_reg.oper_status = (u8)temp;

            running = sx_proc_str_get_u32(running, &temp);
            reg_data.paos_reg.ase = (u8)temp;

            running = sx_proc_str_get_u32(running, &temp);
            reg_data.paos_reg.ee = (u8)temp;

            running = sx_proc_str_get_u32(running, &temp);
            reg_data.paos_reg.e = (u8)temp;

            PROC_DUMP("Executing ACCESS_REG_PAOS read command\n");
            err = sx_ACCESS_REG_PAOS(dev, &reg_data);
            if (err) {
                goto out;
            }
            PROC_DUMP("Finished executing read ACCESS_REG_PAOS command.\n");

            PROC_DUMP("swid = %u\n", reg_data.paos_reg.swid);
            PROC_DUMP("local_port = %u\n", reg_data.paos_reg.local_port);
                PROC_DUMP("lp_msb = %u\n", reg_data.paos_reg.lp_msb);
            PROC_DUMP("admin_status = %u\n", reg_data.paos_reg.admin_status);
            PROC_DUMP("oper_status = %u\n", reg_data.paos_reg.oper_status);
            PROC_DUMP("ase = %u\n", reg_data.paos_reg.ase);
            PROC_DUMP("ee = %u\n", reg_data.paos_reg.ee);
            PROC_DUMP("e = %u\n", reg_data.paos_reg.e);
        } else {
            PROC_DUMP("Wrong access method %d\n", access_method);
        }
        break;
    }

    case MLXSW_IBFMRC_ID:
    {
        struct ku_access_ibfmrc_reg reg_data;
        memset(&reg_data, 0, sizeof(reg_data));
        reg_data.dev_id = dev_id;
        running = sx_proc_str_get_u32(running, &access_method);
        sx_cmd_set_op_tlv(&reg_data.op_tlv, reg_id, access_method);

        if (access_method == 2) {
            running = sx_proc_str_get_u32(running, &temp);
            reg_data.ibfmrc_reg.attr_id_en = (u32)temp;
            PROC_DUMP("Executing ACCESS_REG_IBFMRC write command\n");
            PROC_DUMP("attr_id_en = %08x\n", reg_data.ibfmrc_reg.attr_id_en);
            err = sx_ACCESS_REG_IBFMRC(dev, &reg_data);
            if (err) {
                PROC_DUMP("Failed ACCESS_REG_IBFMRC write command\n");
                goto out;
            }
            PROC_DUMP("Finished executing write ACCESS_REG_IBFMRC command.\n");
        } else if (access_method == 1) {
            PROC_DUMP("Executing ACCESS_REG_IBFMRC read command\n");
            err = sx_ACCESS_REG_IBFMRC(dev, &reg_data);
            if (err) {
                PROC_DUMP("Failed ACCESS_REG_IBFMRC read command\n");
                goto out;
            }
            PROC_DUMP("Finished executing read ACCESS_REG_IBFMRC command.\n");
            PROC_DUMP("attr_id_en = %u\n", reg_data.ibfmrc_reg.attr_id_en);
        } else {
            PROC_DUMP("Wrong access method %d\n", access_method);
        }
        break;
    }

    default:
        return EINVAL;
    }

out:
    return err;
}
