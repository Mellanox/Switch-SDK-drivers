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

#include "mlxfw.h"
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/version.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include <linux/mlx_sx/auto_registers/reg.h>

#define SX_MLXFW_MFA2_MAX_FILENAME 128

char mfa2_file[SX_MLXFW_MFA2_MAX_FILENAME] = "";
module_param_string(mfa2_file, mfa2_file, SX_MLXFW_MFA2_MAX_FILENAME, 0444);
MODULE_PARM_DESC(mfa2_file, "mfa2_file: FW file type mfa2");

struct sx_dev *g_dev = NULL;
static int sx_mlxfw_component_query(struct mlxfw_dev *mlxfw_dev,
                                    u16               component_index,
                                    u32              *p_max_size,
                                    u8               *p_align_bits,
                                    u16              *p_max_write_size)
{
    int                       ret = 0;
    struct ku_access_mcqi_reg reg_mcqi;

    memset(&reg_mcqi, 0, sizeof(struct ku_access_mcqi_reg));

#define MLXSW_REG_MCQI_CAP_LEN      0x14
#define MLXSW_REG_MCDA_MAX_DATA_LEN 0x80

    reg_mcqi.dev_id = g_dev->device_id;
    sx_cmd_set_op_tlv(&reg_mcqi.op_tlv, MLXSW_MCQI_ID, EMAD_METHOD_QUERY);
    reg_mcqi.mcqi_reg.component_index = component_index;
    reg_mcqi.mcqi_reg.info_type = SXD_MCQI_INFO_TYPE_CAPABILITIES_E;
    reg_mcqi.mcqi_reg.offset = 0;
    reg_mcqi.mcqi_reg.data_size = MLXSW_REG_MCQI_CAP_LEN;
    ret = sx_ACCESS_REG_MCQI(g_dev, &reg_mcqi);
    if (ret) {
        pr_err("sx_ACCESS_REG_MCQI (component_query) returned with error %d\n", ret);
        return ret;
    }

    *p_max_size = reg_mcqi.mcqi_reg.data.mcqi_cap.max_component_size;
    *p_align_bits = max_t(u8, reg_mcqi.mcqi_reg.data.mcqi_cap.log_mcda_word_size, 2);
    *p_max_write_size = min_t(u16, reg_mcqi.mcqi_reg.data.mcqi_cap.mcda_max_write_size, MLXSW_REG_MCDA_MAX_DATA_LEN);

    return ret;
}

static int sx_mlxfw_fsm_lock(struct mlxfw_dev *mlxfw_dev, u32 *fwhandle)
{
    int                      ret = 0;
    struct ku_access_mcc_reg reg_mcc;

    memset(&reg_mcc, 0, sizeof(struct ku_access_mcc_reg));

    reg_mcc.dev_id = g_dev->device_id;
    sx_cmd_set_op_tlv(&reg_mcc.op_tlv, MLXSW_MCC_ID, EMAD_METHOD_QUERY);
    ret = sx_ACCESS_REG_MCC(g_dev, &reg_mcc);
    if (ret) {
        pr_err("sx_ACCESS_REG_MCC (fsm_lock) returned with error %d\n", ret);
        return ret;
    }
    *fwhandle = reg_mcc.mcc_reg.update_handle;

    if (reg_mcc.mcc_reg.control_state != SXD_MCC_CONTROL_STATE_IDLE_E) {
        pr_err("(fsm_lock) control state is not idle\n");
        return -EBUSY;
    }

    memset(&reg_mcc, 0, sizeof(struct ku_access_mcc_reg));
    reg_mcc.dev_id = g_dev->device_id;
    sx_cmd_set_op_tlv(&reg_mcc.op_tlv, MLXSW_MCC_ID, EMAD_METHOD_WRITE);
    reg_mcc.mcc_reg.instruction = SXD_MCC_INSTRUCTION_LOCK_UPDATE_HANDLE_E;
    reg_mcc.mcc_reg.component_index = 0;
    reg_mcc.mcc_reg.update_handle = *fwhandle;
    reg_mcc.mcc_reg.component_size = 0;
    ret = sx_ACCESS_REG_MCC(g_dev, &reg_mcc);
    if (ret) {
        pr_err("sx_ACCESS_REG_MCC (fsm_lock) returned with error %d\n", ret);
    }

    return ret;
}

static int sx_mlxfw_fsm_component_update(struct mlxfw_dev *mlxfw_dev,
                                         u32               fwhandle,
                                         u16               component_index,
                                         u32               component_size)
{
    int                      ret = 0;
    struct ku_access_mcc_reg reg_mcc;

    memset(&reg_mcc, 0, sizeof(struct ku_access_mcc_reg));

    reg_mcc.dev_id = g_dev->device_id;
    sx_cmd_set_op_tlv(&reg_mcc.op_tlv, MLXSW_MCC_ID, EMAD_METHOD_WRITE);
    reg_mcc.mcc_reg.instruction = SXD_MCC_INSTRUCTION_UPDATE_COMPONENT_E;
    reg_mcc.mcc_reg.component_index = component_index;
    reg_mcc.mcc_reg.update_handle = fwhandle;
    reg_mcc.mcc_reg.component_size = component_size;
    ret = sx_ACCESS_REG_MCC(g_dev, &reg_mcc);
    if (ret) {
        pr_err("sx_ACCESS_REG_MCC (fsm_component_update) returned with error %d\n", ret);
    }
    return ret;
}

static int sx_mlxfw_fsm_block_download(struct mlxfw_dev *mlxfw_dev, u32 fwhandle, u8 *data, u16 size, u32 offset)
{
    int                       ret = 0, i = 0;
    struct ku_access_mcda_reg reg_mcda;

    memset(&reg_mcda, 0, sizeof(struct ku_access_mcda_reg));

    reg_mcda.dev_id = g_dev->device_id;
    sx_cmd_set_op_tlv(&reg_mcda.op_tlv, MLXSW_MCDA_ID, EMAD_METHOD_WRITE);
    reg_mcda.mcda_reg.update_handle = fwhandle;
    reg_mcda.mcda_reg.offset = offset;
    reg_mcda.mcda_reg.size = size;
    for (i = 0; i < size / 4; i++) {
        reg_mcda.mcda_reg.data[i] = *(u32*)&data[i * 4];
    }
    ret = sx_ACCESS_REG_MCDA(g_dev, &reg_mcda);
    if (ret) {
        pr_err("sx_ACCESS_REG_MCDA (fsm_block_download) returned with error %d\n", ret);
    }
    return ret;
}

static int sx_mlxfw_fsm_component_verify(struct mlxfw_dev *mlxfw_dev, u32 fwhandle, u16 component_index)
{
    int                      ret = 0;
    struct ku_access_mcc_reg reg_mcc;

    memset(&reg_mcc, 0, sizeof(struct ku_access_mcc_reg));

    reg_mcc.dev_id = g_dev->device_id;
    sx_cmd_set_op_tlv(&reg_mcc.op_tlv, MLXSW_MCC_ID, EMAD_METHOD_WRITE);
    reg_mcc.mcc_reg.instruction = SXD_MCC_INSTRUCTION_VERIFY_COMPONENT_E;
    reg_mcc.mcc_reg.component_index = component_index;
    reg_mcc.mcc_reg.update_handle = fwhandle;
    reg_mcc.mcc_reg.component_size = 0;
    ret = sx_ACCESS_REG_MCC(g_dev, &reg_mcc);
    if (ret) {
        pr_err("sx_ACCESS_REG_MCC (fsm_component_verify) returned with error %d\n", ret);
    }
    return ret;
}

static int sx_mlxfw_fsm_activate(struct mlxfw_dev *mlxfw_dev, u32 fwhandle)
{
    int                      ret = 0;
    struct ku_access_mcc_reg reg_mcc;

    memset(&reg_mcc, 0, sizeof(struct ku_access_mcc_reg));

    reg_mcc.dev_id = g_dev->device_id;
    sx_cmd_set_op_tlv(&reg_mcc.op_tlv, MLXSW_MCC_ID, EMAD_METHOD_WRITE);
    reg_mcc.mcc_reg.instruction = SXD_MCC_INSTRUCTION_ACTIVATE_E;
    reg_mcc.mcc_reg.component_index = 0;
    reg_mcc.mcc_reg.update_handle = fwhandle;
    reg_mcc.mcc_reg.component_size = 0;
    ret = sx_ACCESS_REG_MCC(g_dev, &reg_mcc);
    if (ret) {
        pr_err("sx_ACCESS_REG_MCC (fsm_activate) returned with error %d\n", ret);
    }
    return ret;
}

static int sx_mlxfw_fsm_query_state(struct mlxfw_dev         *mlxfw_dev,
                                    u32                       fwhandle,
                                    enum sxd_mcc_control_state     *fsm_state,
                                    enum mlxfw_fsm_state_err *fsm_state_err)
{
    int                      ret = 0;
    struct ku_access_mcc_reg reg_mcc;

    memset(&reg_mcc, 0, sizeof(struct ku_access_mcc_reg));

    reg_mcc.dev_id = g_dev->device_id;
    sx_cmd_set_op_tlv(&reg_mcc.op_tlv, MLXSW_MCC_ID, EMAD_METHOD_QUERY);
    reg_mcc.mcc_reg.update_handle = fwhandle;
    ret = sx_ACCESS_REG_MCC(g_dev, &reg_mcc);
    if (ret) {
        pr_err("sx_ACCESS_REG_MCC (fsm_query_state) returned with error %d\n", ret);
        return ret;
    }

    *fsm_state = reg_mcc.mcc_reg.control_state;
    *fsm_state_err = min_t(enum mlxfw_fsm_state_err, reg_mcc.mcc_reg.error_code,
                           MLXFW_FSM_STATE_ERR_MAX);
    return ret;
}

static void sx_mlxfw_fsm_cancel(struct mlxfw_dev *mlxfw_dev, u32 fwhandle)
{
    int                      ret = 0;
    struct ku_access_mcc_reg reg_mcc;

    memset(&reg_mcc, 0, sizeof(struct ku_access_mcc_reg));

    reg_mcc.dev_id = g_dev->device_id;
    sx_cmd_set_op_tlv(&reg_mcc.op_tlv, MLXSW_MCC_ID, EMAD_METHOD_WRITE);
    reg_mcc.mcc_reg.instruction = SXD_MCC_INSTRUCTION_CANCEL_E;
    reg_mcc.mcc_reg.component_index = 0;
    reg_mcc.mcc_reg.update_handle = fwhandle;
    reg_mcc.mcc_reg.component_size = 0;
    ret = sx_ACCESS_REG_MCC(g_dev, &reg_mcc);
    if (ret) {
        pr_err("sx_ACCESS_REG_MCC (fsm_cancel) returned with error %d\n", ret);
    }
}

static void sx_mlxfw_fsm_release(struct mlxfw_dev *mlxfw_dev, u32 fwhandle)
{
    int                      ret = 0;
    struct ku_access_mcc_reg reg_mcc;

    memset(&reg_mcc, 0, sizeof(struct ku_access_mcc_reg));

    reg_mcc.dev_id = g_dev->device_id;
    sx_cmd_set_op_tlv(&reg_mcc.op_tlv, MLXSW_MCC_ID, EMAD_METHOD_WRITE);
    reg_mcc.mcc_reg.instruction = SXD_MCC_INSTRUCTION_RELEASE_UPDATE_HANDLE_E;
    reg_mcc.mcc_reg.component_index = 0;
    reg_mcc.mcc_reg.update_handle = fwhandle;
    reg_mcc.mcc_reg.component_size = 0;
    ret = sx_ACCESS_REG_MCC(g_dev, &reg_mcc);
    if (ret) {
        pr_err("sx_ACCESS_REG_MCC (fsm_release) returned with error %d\n", ret);
    }
}

static const struct mlxfw_dev_ops sx_mlxfw_dev_ops = {
    .component_query = sx_mlxfw_component_query,
    .fsm_lock = sx_mlxfw_fsm_lock,
    .fsm_component_update = sx_mlxfw_fsm_component_update,
    .fsm_block_download = sx_mlxfw_fsm_block_download,
    .fsm_component_verify = sx_mlxfw_fsm_component_verify,
    .fsm_activate = sx_mlxfw_fsm_activate,
    .fsm_query_state = sx_mlxfw_fsm_query_state,
    .fsm_cancel = sx_mlxfw_fsm_cancel,
    .fsm_release = sx_mlxfw_fsm_release
};
static int __init sx_mlxfw_init(void)
{
    int                    ret = 0;
    const struct firmware *firmware;
    struct mlxfw_dev       mlxfw_dev;

    pr_info("%s: input mfa2_file [%s]\n", __func__, mfa2_file);

    g_dev = sx_get_dev_context();

    mlxfw_dev.ops = &sx_mlxfw_dev_ops;
    mlxfw_dev.psid = g_dev->board_id;
    mlxfw_dev.psid_size = strlen(g_dev->board_id);

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 14, 0))
    ret = request_firmware(&firmware, mfa2_file, &g_dev->pdev->dev);
#else
    ret = request_firmware_direct(&firmware, mfa2_file, &g_dev->pdev->dev);
#endif
    if (ret) {
        pr_err("request_firmware_direct error (%d)\n", ret);
        goto out;
    }

    ret = mlxfw_firmware_flash(&mlxfw_dev, firmware);
    if (ret) {
        pr_err("mlxfw_firmware_flash error (%d)\n", ret);
        /* NO goto out */
    }

    release_firmware(firmware);
out:
    return ret;
}

static void __exit sx_mlxfw_cleanup(void)
{
    pr_info("%s\n", __func__);
}

module_init(sx_mlxfw_init);
module_exit(sx_mlxfw_cleanup);
