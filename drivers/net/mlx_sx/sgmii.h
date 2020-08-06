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

#ifndef __SGMII_H__
#define __SGMII_H__

#include <linux/types.h>

struct sk_buff;
struct isx_meta;
struct ku_sgmii_system_cfg;
struct sx_dev;

#define SGMII_TR_ID_PREFIX  (0xc001d00d)
#define MAD_ATTR_ACCESS_REG (0xff52) /* defined in sxd_libs as IB_ATTR_ACCESS_REG */

/* *************************************************************************************** */
/* SGMII globals                                                                           */
/* *************************************************************************************** */

void sgmii_deinit(void);
uint8_t is_sgmii_supported(void);

/* *************************************************************************************** */
/* Device database functions                                                                */
/* *************************************************************************************** */

int sgmii_dev_add(int dev_id, const struct ku_dpt_sgmii_info *dpt_sgmii_info);
int sgmii_dev_del(int dev_id);
uint8_t is_sgmii_device(int dev_id);
int sgmii_dev_init(int dev_id, uint8_t init_hopf);
int sgmii_default_dev_set(int dev_id);
int sgmii_default_dev_id_get(int *dev_id);
int sgmii_dev_set_mft_info(const struct ku_sgmii_mft_info *mft_info);

/* *************************************************************************************** */
/* Transport layer functions                                                               */
/* *************************************************************************************** */

int sgmii_set_system_cfg(const struct ku_sgmii_system_cfg *sgmii_system_cfg);

int sgmii_send_emad(int                    dev_id,
                    struct sk_buff        *skb,
                    const struct isx_meta *meta);

int sgmii_send_mad(int                    dev_id,
                   struct sk_buff        *skb,
                   const struct isx_meta *meta);

int sgmii_simulate_sync_mad_ifc(struct sx_dev* dev,
                                int            dev_id,
                                u32            in_modifier,
                                u8             op_modifier,
                                void          *in_mad,
                                int            in_size,
                                void          *out_mad,
                                int            out_size);

int sgmii_send_misc(int                    dev_id,
                    struct sk_buff        *skb,
                    const struct isx_meta *meta);

int sgmii_send_cr_space_read(int      dev_id,
                             uint32_t address,
                             void    *buf,
                             int      size);

int sgmii_send_cr_space_write(int      dev_id,
                              uint32_t address,
                              void    *buf,
                              int      size);

/* *************************************************************************************** */
/* External (OOB) access-reg functions from outside the SGMII subsystem                    */
/* *************************************************************************************** */

int sgmii_emad_access_spzr(int dev_id, const struct ku_spzr_reg *reg_spzr);

/* *************************************************************************************** */
/* Misc functions                                                                          */
/* *************************************************************************************** */

int sgmii_get_mad_header_info(const uint8_t *buff,
                              uint32_t       buff_len,
                              uint32_t      *mad_hdr_offset,
                              uint64_t      *tr_id,
                              uint16_t      *attr_id);

#endif /* __SGMII_H__ */
