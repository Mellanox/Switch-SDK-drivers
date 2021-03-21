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

#ifndef _MLXFW_H
#define _MLXFW_H

#include <linux/firmware.h>
#include <linux/mlx_sx/kernel_user.h>

enum mlxfw_fsm_state_err {
    MLXFW_FSM_STATE_ERR_OK,
    MLXFW_FSM_STATE_ERR_ERROR,
    MLXFW_FSM_STATE_ERR_REJECTED_DIGEST_ERR,
    MLXFW_FSM_STATE_ERR_REJECTED_NOT_APPLICABLE,
    MLXFW_FSM_STATE_ERR_REJECTED_UNKNOWN_KEY,
    MLXFW_FSM_STATE_ERR_REJECTED_AUTH_FAILED,
    MLXFW_FSM_STATE_ERR_REJECTED_UNSIGNED,
    MLXFW_FSM_STATE_ERR_REJECTED_KEY_NOT_APPLICABLE,
    MLXFW_FSM_STATE_ERR_REJECTED_BAD_FORMAT,
    MLXFW_FSM_STATE_ERR_BLOCKED_PENDING_RESET,
    MLXFW_FSM_STATE_ERR_MAX,
};
struct mlxfw_dev;
struct mlxfw_dev_ops {
    int (*component_query)(struct mlxfw_dev *mlxfw_dev, u16 component_index,
                           u32 *p_max_size, u8 *p_align_bits,
                           u16 *p_max_write_size);

    int (*fsm_lock)(struct mlxfw_dev *mlxfw_dev, u32 *fwhandle);

    int (*fsm_component_update)(struct mlxfw_dev *mlxfw_dev, u32 fwhandle,
                                u16 component_index, u32 component_size);

    int (*fsm_block_download)(struct mlxfw_dev *mlxfw_dev, u32 fwhandle,
                              u8 *data, u16 size, u32 offset);

    int (*fsm_component_verify)(struct mlxfw_dev *mlxfw_dev, u32 fwhandle,
                                u16 component_index);

    int (*fsm_activate)(struct mlxfw_dev *mlxfw_dev, u32 fwhandle);

    int (*fsm_query_state)(struct mlxfw_dev *mlxfw_dev, u32 fwhandle,
                           enum sxd_mcc_control_state *fsm_state,
                           enum mlxfw_fsm_state_err *fsm_state_err);

    void (*fsm_cancel)(struct mlxfw_dev *mlxfw_dev, u32 fwhandle);

    void (*fsm_release)(struct mlxfw_dev *mlxfw_dev, u32 fwhandle);
};
struct mlxfw_dev {
    const struct mlxfw_dev_ops *ops;
    const char                 *psid;
    u16                         psid_size;
};

#if IS_REACHABLE(CONFIG_MLXFW)
int mlxfw_firmware_flash(struct mlxfw_dev      *mlxfw_dev,
                         const struct firmware *firmware);
#else
static inline
int mlxfw_firmware_flash(struct mlxfw_dev *mlxfw_dev, const struct firmware *firmware)
{
    return -EOPNOTSUPP;
}
#endif

#endif /* ifndef _MLXFW_H */
