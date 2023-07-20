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

#ifndef __SX_CORE_EMAD_H__
#define __SX_CORE_EMAD_H__

#include <linux/mlx_sx/driver.h>
#include "fw_internal.h"

typedef enum {
    /* Values are taken from PRM */
    SX_EMAD_STATUS_OK_E                     = 0x0,
    SX_EMAD_STATUS_BUSY_E                   = 0x1,
    SX_EMAD_STATUS_BAD_BASE_VER_E           = 0x2,
    SX_EMAD_STATUS_BAD_TLV_E                = 0x3,
    SX_EMAD_STATUS_NOT_SUPP_REG_E           = 0x4,
    SX_EMAD_STATUS_NOT_SUPP_CLASS_E         = 0x5,
    SX_EMAD_STATUS_NOT_SUPP_METHOD_E        = 0x6,
    SX_EMAD_STATUS_BAD_PARAM_E              = 0x7,
    SX_EMAD_STATUS_RESOURCE_NOT_AVAILABLE_E = 0x8,
    SX_EMAD_STATUS_LONG_PROCESS_E           = 0x9,
    SX_EMAD_STATUS_RETRY_E                  = 0xa,
    SX_EMAD_STATUS_PERIPHERAL_ERR_E         = 0xb,
    SX_EMAD_STATUS_PROFILE_NO_MEMORY_E      = 0xc,
    SX_EMAD_STATUS_ISSU_ONGOING_E           = 0xd,
    SX_EMAD_STATUS_BAD_CONFIG_E             = 0x20,
    SX_EMAD_STATUS_ERASE_EXCEEDED_E         = 0x21,
    SX_EMAD_STATUS_ERROR_E                  = 0x22,
    SX_EMAD_STATUS_REG_LENGTH_TOO_SMALL_E   = 0x24,
    SX_EMAD_STATUS_INTERNAL_ERR_E           = 0x70,
    SX_EMAD_STATUS_DROP_E                   = 0x7f
} sx_emad_status_e;

int sx_emad_init(void);
void sx_emad_deinit(void);

int sx_emad_dev_init(struct sx_dev *dev);
void sx_emad_dev_deinit(struct sx_dev *dev);

bool sx_emad_dump_hanlders_per_device_init(struct sx_dev *dev, void *context);
bool sx_emad_dump_hanlders_per_device_deinit(struct sx_dev *dev, void *context);

int sx_emad_build(sxd_dev_id_t     dev_id,
                  const u8        *reg_buff,
                  u32              reg_buff_len,
                  struct sk_buff **skb,
                  struct isx_meta *meta,
                  u32              tid_high,
                  u32              tid_low,
                  gfp_t            gfp,
                  u16              reg_id,
                  sx_emad_method_e method);

int sx_emad_access_reg_common(struct sx_dev                  *dev,
                              emad_prio_e                     priority,
                              sx_emad_method_e                method,
                              u16                             reg_id,
                              void                           *ku_reg,
                              u32                             prm_reg_len_in_dwords,
                              const struct sx_emad_in_params *in_params,
                              struct sx_emad_out_params      *out_params,
                              access_reg_encode_cb_t          encode_cb,
                              access_reg_decode_cb_t          decode_cb);

#endif /* __SX_CORE_EMAD_H__ */
