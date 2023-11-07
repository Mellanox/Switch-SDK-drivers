/*
 * Copyright (c) 2010-2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */


/*
 * THIS FILE IS AUTO GENERATED.
 * DO NOT MAKE ANY CHANGES!
 * They will be erased with next update.
 *
 */

#ifndef SX_CMD_AUTO_H_
#define SX_CMD_AUTO_H_

/************************************************
 * Includes
 ***********************************************/

#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/kernel_user.h>

/************************************************
 * Structs
 ***********************************************/

/************************************************
 * Functions
 ***********************************************/

int __HMON_encode(u8 *inbox, void *ku_reg, void *context);
int __HMON_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_HMON(struct sx_dev *dev, struct ku_access_hmon_reg *reg_data);
int sx_EMAD_ACCESS_REG_HMON(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_hmon_reg *reg);
int __HETT_encode(u8 *inbox, void *ku_reg, void *context);
int __HETT_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_HETT(struct sx_dev *dev, struct ku_access_hett_reg *reg_data);
int sx_EMAD_ACCESS_REG_HETT(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_hett_reg *reg);
int __MTPPS_encode(u8 *inbox, void *ku_reg, void *context);
int __MTPPS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTPPS(struct sx_dev *dev, struct ku_access_mtpps_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTPPS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtpps_reg *reg);
int __MTPPSE_encode(u8 *inbox, void *ku_reg, void *context);
int __MTPPSE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTPPSE(struct sx_dev *dev, struct ku_access_mtppse_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTPPSE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtppse_reg *reg);
int __MTUTC_encode(u8 *inbox, void *ku_reg, void *context);
int __MTUTC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTUTC(struct sx_dev *dev, struct ku_access_mtutc_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTUTC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtutc_reg *reg);
int __MTPPST_encode(u8 *inbox, void *ku_reg, void *context);
int __MTPPST_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTPPST(struct sx_dev *dev, struct ku_access_mtppst_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTPPST(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtppst_reg *reg);
int __MSECQ_encode(u8 *inbox, void *ku_reg, void *context);
int __MSECQ_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MSECQ(struct sx_dev *dev, struct ku_access_msecq_reg *reg_data);
int sx_EMAD_ACCESS_REG_MSECQ(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_msecq_reg *reg);
int __MSEES_encode(u8 *inbox, void *ku_reg, void *context);
int __MSEES_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MSEES(struct sx_dev *dev, struct ku_access_msees_reg *reg_data);
int sx_EMAD_ACCESS_REG_MSEES(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_msees_reg *reg);
int __MSPI_encode(u8 *inbox, void *ku_reg, void *context);
int __MSPI_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MSPI(struct sx_dev *dev, struct ku_access_mspi_reg *reg_data);
int sx_EMAD_ACCESS_REG_MSPI(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mspi_reg *reg);
int __MCION_encode(u8 *inbox, void *ku_reg, void *context);
int __MCION_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MCION(struct sx_dev *dev, struct ku_access_mcion_reg *reg_data);
int sx_EMAD_ACCESS_REG_MCION(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mcion_reg *reg);
int __MCFS_encode(u8 *inbox, void *ku_reg, void *context);
int __MCFS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MCFS(struct sx_dev *dev, struct ku_access_mcfs_reg *reg_data);
int sx_EMAD_ACCESS_REG_MCFS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mcfs_reg *reg);
int __MGPIR_encode(u8 *inbox, void *ku_reg, void *context);
int __MGPIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MGPIR(struct sx_dev *dev, struct ku_access_mgpir_reg *reg_data);
int sx_EMAD_ACCESS_REG_MGPIR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mgpir_reg *reg);
int __MDFCR_encode(u8 *inbox, void *ku_reg, void *context);
int __MDFCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MDFCR(struct sx_dev *dev, struct ku_access_mdfcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_MDFCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mdfcr_reg *reg);
int __MTECR_encode(u8 *inbox, void *ku_reg, void *context);
int __MTECR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTECR(struct sx_dev *dev, struct ku_access_mtecr_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTECR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtecr_reg *reg);
int __MTCAP_encode(u8 *inbox, void *ku_reg, void *context);
int __MTCAP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTCAP(struct sx_dev *dev, struct ku_access_mtcap_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTCAP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtcap_reg *reg);
int __MVCAP_encode(u8 *inbox, void *ku_reg, void *context);
int __MVCAP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MVCAP(struct sx_dev *dev, struct ku_access_mvcap_reg *reg_data);
int sx_EMAD_ACCESS_REG_MVCAP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mvcap_reg *reg);
int __MTMP_encode(u8 *inbox, void *ku_reg, void *context);
int __MTMP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTMP(struct sx_dev *dev, struct ku_access_mtmp_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTMP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtmp_reg *reg);
int __MGIR_encode(u8 *inbox, void *ku_reg, void *context);
int __MGIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MGIR(struct sx_dev *dev, struct ku_access_mgir_reg *reg_data);
int sx_EMAD_ACCESS_REG_MGIR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mgir_reg *reg);
int __MSGI_encode(u8 *inbox, void *ku_reg, void *context);
int __MSGI_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MSGI(struct sx_dev *dev, struct ku_access_msgi_reg *reg_data);
int sx_EMAD_ACCESS_REG_MSGI(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_msgi_reg *reg);
int __MDIR_encode(u8 *inbox, void *ku_reg, void *context);
int __MDIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MDIR(struct sx_dev *dev, struct ku_access_mdir_reg *reg_data);
int sx_EMAD_ACCESS_REG_MDIR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mdir_reg *reg);
int __MINI_encode(u8 *inbox, void *ku_reg, void *context);
int __MINI_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MINI(struct sx_dev *dev, struct ku_access_mini_reg *reg_data);
int sx_EMAD_ACCESS_REG_MINI(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mini_reg *reg);
int __MCAM_encode(u8 *inbox, void *ku_reg, void *context);
int __MCAM_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MCAM(struct sx_dev *dev, struct ku_access_mcam_reg *reg_data);
int sx_EMAD_ACCESS_REG_MCAM(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mcam_reg *reg);
int __MECCC_encode(u8 *inbox, void *ku_reg, void *context);
int __MECCC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MECCC(struct sx_dev *dev, struct ku_access_meccc_reg *reg_data);
int sx_EMAD_ACCESS_REG_MECCC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_meccc_reg *reg);
int __MFRC_encode(u8 *inbox, void *ku_reg, void *context);
int __MFRC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MFRC(struct sx_dev *dev, struct ku_access_mfrc_reg *reg_data);
int sx_EMAD_ACCESS_REG_MFRC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mfrc_reg *reg);
int __MMCR_encode(u8 *inbox, void *ku_reg, void *context);
int __MMCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MMCR(struct sx_dev *dev, struct ku_access_mmcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_MMCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mmcr_reg *reg);
int __MFRI_encode(u8 *inbox, void *ku_reg, void *context);
int __MFRI_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MFRI(struct sx_dev *dev, struct ku_access_mfri_reg *reg_data);
int sx_EMAD_ACCESS_REG_MFRI(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mfri_reg *reg);
int __MFRP_encode(u8 *inbox, void *ku_reg, void *context);
int __MFRP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MFRP(struct sx_dev *dev, struct ku_access_mfrp_reg *reg_data);
int sx_EMAD_ACCESS_REG_MFRP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mfrp_reg *reg);
int __MOGCR_encode(u8 *inbox, void *ku_reg, void *context);
int __MOGCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOGCR(struct sx_dev *dev, struct ku_access_mogcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_MOGCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mogcr_reg *reg);
int __MOCS_encode(u8 *inbox, void *ku_reg, void *context);
int __MOCS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOCS(struct sx_dev *dev, struct ku_access_mocs_reg *reg_data);
int sx_EMAD_ACCESS_REG_MOCS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mocs_reg *reg);
int __MOPCE_encode(u8 *inbox, void *ku_reg, void *context);
int __MOPCE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOPCE(struct sx_dev *dev, struct ku_access_mopce_reg *reg_data);
int sx_EMAD_ACCESS_REG_MOPCE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mopce_reg *reg);
int __MOCA_encode(u8 *inbox, void *ku_reg, void *context);
int __MOCA_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOCA(struct sx_dev *dev, struct ku_access_moca_reg *reg_data);
int sx_EMAD_ACCESS_REG_MOCA(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_moca_reg *reg);
int __MOFRB_encode(u8 *inbox, void *ku_reg, void *context);
int __MOFRB_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOFRB(struct sx_dev *dev, struct ku_access_mofrb_reg *reg_data);
int sx_EMAD_ACCESS_REG_MOFRB(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mofrb_reg *reg);
int __MOFPH_encode(u8 *inbox, void *ku_reg, void *context);
int __MOFPH_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOFPH(struct sx_dev *dev, struct ku_access_mofph_reg *reg_data);
int sx_EMAD_ACCESS_REG_MOFPH(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mofph_reg *reg);
int __MOFPC_encode(u8 *inbox, void *ku_reg, void *context);
int __MOFPC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOFPC(struct sx_dev *dev, struct ku_access_mofpc_reg *reg_data);
int sx_EMAD_ACCESS_REG_MOFPC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mofpc_reg *reg);
int __MTPSPU_encode(u8 *inbox, void *ku_reg, void *context);
int __MTPSPU_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTPSPU(struct sx_dev *dev, struct ku_access_mtpspu_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTPSPU(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtpspu_reg *reg);
int __MTPCPC_encode(u8 *inbox, void *ku_reg, void *context);
int __MTPCPC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTPCPC(struct sx_dev *dev, struct ku_access_mtpcpc_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTPCPC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtpcpc_reg *reg);
int __MFGD_encode(u8 *inbox, void *ku_reg, void *context);
int __MFGD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MFGD(struct sx_dev *dev, struct ku_access_mfgd_reg *reg_data);
int sx_EMAD_ACCESS_REG_MFGD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mfgd_reg *reg);
int __MFDE_encode(u8 *inbox, void *ku_reg, void *context);
int __MFDE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MFDE(struct sx_dev *dev, struct ku_access_mfde_reg *reg_data);
int sx_EMAD_ACCESS_REG_MFDE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mfde_reg *reg);
int __MOFRD_encode(u8 *inbox, void *ku_reg, void *context);
int __MOFRD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOFRD(struct sx_dev *dev, struct ku_access_mofrd_reg *reg_data);
int sx_EMAD_ACCESS_REG_MOFRD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mofrd_reg *reg);
int __SGCR_encode(u8 *inbox, void *ku_reg, void *context);
int __SGCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SGCR(struct sx_dev *dev, struct ku_access_sgcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_SGCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sgcr_reg *reg);
int __SPAD_encode(u8 *inbox, void *ku_reg, void *context);
int __SPAD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SPAD(struct sx_dev *dev, struct ku_access_spad_reg *reg_data);
int sx_EMAD_ACCESS_REG_SPAD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_spad_reg *reg);
int __SMID_V2_encode(u8 *inbox, void *ku_reg, void *context);
int __SMID_V2_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SMID_V2(struct sx_dev *dev, struct ku_access_smid_v2_reg *reg_data);
int sx_EMAD_ACCESS_REG_SMID_V2(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_smid_v2_reg *reg);
int __SPZR_encode(u8 *inbox, void *ku_reg, void *context);
int __SPZR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SPZR(struct sx_dev *dev, struct ku_access_spzr_reg *reg_data);
int sx_EMAD_ACCESS_REG_SPZR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_spzr_reg *reg);
int __IBFMR_encode(u8 *inbox, void *ku_reg, void *context);
int __IBFMR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_IBFMR(struct sx_dev *dev, struct ku_access_ibfmr_reg *reg_data);
int sx_EMAD_ACCESS_REG_IBFMR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ibfmr_reg *reg);
int __IBFMRC_encode(u8 *inbox, void *ku_reg, void *context);
int __IBFMRC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_IBFMRC(struct sx_dev *dev, struct ku_access_ibfmrc_reg *reg_data);
int sx_EMAD_ACCESS_REG_IBFMRC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ibfmrc_reg *reg);
int __PTYS_encode(u8 *inbox, void *ku_reg, void *context);
int __PTYS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PTYS(struct sx_dev *dev, struct ku_access_ptys_reg *reg_data);
int sx_EMAD_ACCESS_REG_PTYS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ptys_reg *reg);
int __PAOS_encode(u8 *inbox, void *ku_reg, void *context);
int __PAOS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PAOS(struct sx_dev *dev, struct ku_access_paos_reg *reg_data);
int sx_EMAD_ACCESS_REG_PAOS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_paos_reg *reg);
int __PPCNT_encode(u8 *inbox, void *ku_reg, void *context);
int __PPCNT_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPCNT(struct sx_dev *dev, struct ku_access_ppcnt_reg *reg_data);
int sx_EMAD_ACCESS_REG_PPCNT(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ppcnt_reg *reg);
int __PMAOS_encode(u8 *inbox, void *ku_reg, void *context);
int __PMAOS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMAOS(struct sx_dev *dev, struct ku_access_pmaos_reg *reg_data);
int sx_EMAD_ACCESS_REG_PMAOS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmaos_reg *reg);
int __PMPE_encode(u8 *inbox, void *ku_reg, void *context);
int __PMPE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMPE(struct sx_dev *dev, struct ku_access_pmpe_reg *reg_data);
int sx_EMAD_ACCESS_REG_PMPE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmpe_reg *reg);
int __PMMP_encode(u8 *inbox, void *ku_reg, void *context);
int __PMMP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMMP(struct sx_dev *dev, struct ku_access_pmmp_reg *reg_data);
int sx_EMAD_ACCESS_REG_PMMP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmmp_reg *reg);
int __PMCR_encode(u8 *inbox, void *ku_reg, void *context);
int __PMCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMCR(struct sx_dev *dev, struct ku_access_pmcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PMCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmcr_reg *reg);
int __PMTM_encode(u8 *inbox, void *ku_reg, void *context);
int __PMTM_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMTM(struct sx_dev *dev, struct ku_access_pmtm_reg *reg_data);
int sx_EMAD_ACCESS_REG_PMTM(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmtm_reg *reg);
int __PPLR_encode(u8 *inbox, void *ku_reg, void *context);
int __PPLR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPLR(struct sx_dev *dev, struct ku_access_pplr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PPLR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pplr_reg *reg);
int __SLTP_encode(u8 *inbox, void *ku_reg, void *context);
int __SLTP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SLTP(struct sx_dev *dev, struct ku_access_sltp_reg *reg_data);
int sx_EMAD_ACCESS_REG_SLTP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sltp_reg *reg);
int __SLSIR_encode(u8 *inbox, void *ku_reg, void *context);
int __SLSIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SLSIR(struct sx_dev *dev, struct ku_access_slsir_reg *reg_data);
int sx_EMAD_ACCESS_REG_SLSIR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_slsir_reg *reg);
int __PDDR_encode(u8 *inbox, void *ku_reg, void *context);
int __PDDR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PDDR(struct sx_dev *dev, struct ku_access_pddr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PDDR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pddr_reg *reg);
int __PMDR_encode(u8 *inbox, void *ku_reg, void *context);
int __PMDR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMDR(struct sx_dev *dev, struct ku_access_pmdr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PMDR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmdr_reg *reg);
int __PPHCR_encode(u8 *inbox, void *ku_reg, void *context);
int __PPHCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPHCR(struct sx_dev *dev, struct ku_access_pphcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PPHCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pphcr_reg *reg);
int __SLLM_encode(u8 *inbox, void *ku_reg, void *context);
int __SLLM_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SLLM(struct sx_dev *dev, struct ku_access_sllm_reg *reg_data);
int sx_EMAD_ACCESS_REG_SLLM(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sllm_reg *reg);
int __PPCGP_encode(u8 *inbox, void *ku_reg, void *context);
int __PPCGP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPCGP(struct sx_dev *dev, struct ku_access_ppcgp_reg *reg_data);
int sx_EMAD_ACCESS_REG_PPCGP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ppcgp_reg *reg);
int __PCSR_encode(u8 *inbox, void *ku_reg, void *context);
int __PCSR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PCSR(struct sx_dev *dev, struct ku_access_pcsr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PCSR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pcsr_reg *reg);
int __PMTU_encode(u8 *inbox, void *ku_reg, void *context);
int __PMTU_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMTU(struct sx_dev *dev, struct ku_access_pmtu_reg *reg_data);
int sx_EMAD_ACCESS_REG_PMTU(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmtu_reg *reg);
int __PPAD_encode(u8 *inbox, void *ku_reg, void *context);
int __PPAD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPAD(struct sx_dev *dev, struct ku_access_ppad_reg *reg_data);
int sx_EMAD_ACCESS_REG_PPAD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ppad_reg *reg);
int __PBSR_encode(u8 *inbox, void *ku_reg, void *context);
int __PBSR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PBSR(struct sx_dev *dev, struct ku_access_pbsr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PBSR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pbsr_reg *reg);
int __PLLP_encode(u8 *inbox, void *ku_reg, void *context);
int __PLLP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PLLP(struct sx_dev *dev, struct ku_access_pllp_reg *reg_data);
int sx_EMAD_ACCESS_REG_PLLP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pllp_reg *reg);
int __PPCR_encode(u8 *inbox, void *ku_reg, void *context);
int __PPCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPCR(struct sx_dev *dev, struct ku_access_ppcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PPCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ppcr_reg *reg);
int __PLIBDB_encode(u8 *inbox, void *ku_reg, void *context);
int __PLIBDB_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PLIBDB(struct sx_dev *dev, struct ku_access_plibdb_reg *reg_data);
int sx_EMAD_ACCESS_REG_PLIBDB(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_plibdb_reg *reg);
int __PPIR_encode(u8 *inbox, void *ku_reg, void *context);
int __PPIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPIR(struct sx_dev *dev, struct ku_access_ppir_reg *reg_data);
int sx_EMAD_ACCESS_REG_PPIR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ppir_reg *reg);
int __SBGCR_encode(u8 *inbox, void *ku_reg, void *context);
int __SBGCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SBGCR(struct sx_dev *dev, struct ku_access_sbgcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_SBGCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sbgcr_reg *reg);
int __SBSRD_encode(u8 *inbox, void *ku_reg, void *context);
int __SBSRD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SBSRD(struct sx_dev *dev, struct ku_access_sbsrd_reg *reg_data);
int sx_EMAD_ACCESS_REG_SBSRD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sbsrd_reg *reg);
int __SBCTR_encode(u8 *inbox, void *ku_reg, void *context);
int __SBCTR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SBCTR(struct sx_dev *dev, struct ku_access_sbctr_reg *reg_data);
int sx_EMAD_ACCESS_REG_SBCTR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sbctr_reg *reg);
int __PERAR_encode(u8 *inbox, void *ku_reg, void *context);
int __PERAR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PERAR(struct sx_dev *dev, struct ku_access_perar_reg *reg_data);
int sx_EMAD_ACCESS_REG_PERAR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_perar_reg *reg);
int __CEER_encode(u8 *inbox, void *ku_reg, void *context);
int __CEER_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_CEER(struct sx_dev *dev, struct ku_access_ceer_reg *reg_data);
int sx_EMAD_ACCESS_REG_CEER(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ceer_reg *reg);
int __RIRT_encode(u8 *inbox, void *ku_reg, void *context);
int __RIRT_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_RIRT(struct sx_dev *dev, struct ku_access_rirt_reg *reg_data);
int sx_EMAD_ACCESS_REG_RIRT(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_rirt_reg *reg);
int __FSED_encode(u8 *inbox, void *ku_reg, void *context);
int __FSED_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_FSED(struct sx_dev *dev, struct ku_access_fsed_reg *reg_data);
int sx_EMAD_ACCESS_REG_FSED(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_fsed_reg *reg);
int __FSHE_encode(u8 *inbox, void *ku_reg, void *context);
int __FSHE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_FSHE(struct sx_dev *dev, struct ku_access_fshe_reg *reg_data);
int sx_EMAD_ACCESS_REG_FSHE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_fshe_reg *reg);
int __USACN_encode(u8 *inbox, void *ku_reg, void *context);
int __USACN_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_USACN(struct sx_dev *dev, struct ku_access_usacn_reg *reg_data);
int sx_EMAD_ACCESS_REG_USACN(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_usacn_reg *reg);
int __UTCC_encode(u8 *inbox, void *ku_reg, void *context);
int __UTCC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_UTCC(struct sx_dev *dev, struct ku_access_utcc_reg *reg_data);
int sx_EMAD_ACCESS_REG_UTCC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_utcc_reg *reg);
int __UPCNT_encode(u8 *inbox, void *ku_reg, void *context);
int __UPCNT_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_UPCNT(struct sx_dev *dev, struct ku_access_upcnt_reg *reg_data);
int sx_EMAD_ACCESS_REG_UPCNT(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_upcnt_reg *reg);


#endif /* SX_CMD_AUTO_H_ */

/************************************************
 *                  EOF                         *
 ***********************************************/
