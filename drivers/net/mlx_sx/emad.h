/*
 * Copyright (C) 2010-2022 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

int sx_emad_init(void);
void sx_emad_deinit(void);

int sx_emad_dev_init(struct sx_dev *dev);
void sx_emad_dev_deinit(struct sx_dev *dev);

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
