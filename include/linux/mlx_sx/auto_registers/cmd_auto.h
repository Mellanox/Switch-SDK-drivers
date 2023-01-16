/*
 * Copyright © 2010-2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

int __PMDR_encode(u8 *inbox, void *ku_reg, void *context);
int __PMDR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMDR(struct sx_dev *dev, struct ku_access_pmdr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PMDR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmdr_reg *reg);
int __MTECR_encode(u8 *inbox, void *ku_reg, void *context);
int __MTECR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTECR(struct sx_dev *dev, struct ku_access_mtecr_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTECR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtecr_reg *reg);
int __IGCR_encode(u8 *inbox, void *ku_reg, void *context);
int __IGCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_IGCR(struct sx_dev *dev, struct ku_access_igcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_IGCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_igcr_reg *reg);
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
int __MOGCR_encode(u8 *inbox, void *ku_reg, void *context);
int __MOGCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOGCR(struct sx_dev *dev, struct ku_access_mogcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_MOGCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mogcr_reg *reg);
int __PDDR_encode(u8 *inbox, void *ku_reg, void *context);
int __PDDR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PDDR(struct sx_dev *dev, struct ku_access_pddr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PDDR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pddr_reg *reg);
int __SBCTR_encode(u8 *inbox, void *ku_reg, void *context);
int __SBCTR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SBCTR(struct sx_dev *dev, struct ku_access_sbctr_reg *reg_data);
int sx_EMAD_ACCESS_REG_SBCTR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sbctr_reg *reg);
int __HMON_encode(u8 *inbox, void *ku_reg, void *context);
int __HMON_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_HMON(struct sx_dev *dev, struct ku_access_hmon_reg *reg_data);
int sx_EMAD_ACCESS_REG_HMON(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_hmon_reg *reg);
int __MGPIR_encode(u8 *inbox, void *ku_reg, void *context);
int __MGPIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MGPIR(struct sx_dev *dev, struct ku_access_mgpir_reg *reg_data);
int sx_EMAD_ACCESS_REG_MGPIR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mgpir_reg *reg);
int __PMTM_encode(u8 *inbox, void *ku_reg, void *context);
int __PMTM_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMTM(struct sx_dev *dev, struct ku_access_pmtm_reg *reg_data);
int sx_EMAD_ACCESS_REG_PMTM(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmtm_reg *reg);
int __SLLM_encode(u8 *inbox, void *ku_reg, void *context);
int __SLLM_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SLLM(struct sx_dev *dev, struct ku_access_sllm_reg *reg_data);
int sx_EMAD_ACCESS_REG_SLLM(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sllm_reg *reg);
int __PMTU_encode(u8 *inbox, void *ku_reg, void *context);
int __PMTU_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMTU(struct sx_dev *dev, struct ku_access_pmtu_reg *reg_data);
int sx_EMAD_ACCESS_REG_PMTU(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmtu_reg *reg);
int __PMMP_encode(u8 *inbox, void *ku_reg, void *context);
int __PMMP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMMP(struct sx_dev *dev, struct ku_access_pmmp_reg *reg_data);
int sx_EMAD_ACCESS_REG_PMMP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmmp_reg *reg);
int __SLTP_encode(u8 *inbox, void *ku_reg, void *context);
int __SLTP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SLTP(struct sx_dev *dev, struct ku_access_sltp_reg *reg_data);
int sx_EMAD_ACCESS_REG_SLTP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sltp_reg *reg);
int __PPHCR_encode(u8 *inbox, void *ku_reg, void *context);
int __PPHCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPHCR(struct sx_dev *dev, struct ku_access_pphcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PPHCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pphcr_reg *reg);
int __QCAP_encode(u8 *inbox, void *ku_reg, void *context);
int __QCAP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_QCAP(struct sx_dev *dev, struct ku_access_qcap_reg *reg_data);
int sx_EMAD_ACCESS_REG_QCAP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_qcap_reg *reg);
int __MTWE_encode(u8 *inbox, void *ku_reg, void *context);
int __MTWE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTWE(struct sx_dev *dev, struct ku_access_mtwe_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTWE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtwe_reg *reg);
int __MFGD_encode(u8 *inbox, void *ku_reg, void *context);
int __MFGD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MFGD(struct sx_dev *dev, struct ku_access_mfgd_reg *reg_data);
int sx_EMAD_ACCESS_REG_MFGD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mfgd_reg *reg);
int __MGIR_encode(u8 *inbox, void *ku_reg, void *context);
int __MGIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MGIR(struct sx_dev *dev, struct ku_access_mgir_reg *reg_data);
int sx_EMAD_ACCESS_REG_MGIR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mgir_reg *reg);
int __RIRT_encode(u8 *inbox, void *ku_reg, void *context);
int __RIRT_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_RIRT(struct sx_dev *dev, struct ku_access_rirt_reg *reg_data);
int sx_EMAD_ACCESS_REG_RIRT(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_rirt_reg *reg);
int __PPCGP_encode(u8 *inbox, void *ku_reg, void *context);
int __PPCGP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPCGP(struct sx_dev *dev, struct ku_access_ppcgp_reg *reg_data);
int sx_EMAD_ACCESS_REG_PPCGP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ppcgp_reg *reg);
int __CEER_encode(u8 *inbox, void *ku_reg, void *context);
int __CEER_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_CEER(struct sx_dev *dev, struct ku_access_ceer_reg *reg_data);
int sx_EMAD_ACCESS_REG_CEER(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ceer_reg *reg);
int __IBFMRC_encode(u8 *inbox, void *ku_reg, void *context);
int __IBFMRC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_IBFMRC(struct sx_dev *dev, struct ku_access_ibfmrc_reg *reg_data);
int sx_EMAD_ACCESS_REG_IBFMRC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ibfmrc_reg *reg);
int __MECCC_encode(u8 *inbox, void *ku_reg, void *context);
int __MECCC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MECCC(struct sx_dev *dev, struct ku_access_meccc_reg *reg_data);
int sx_EMAD_ACCESS_REG_MECCC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_meccc_reg *reg);
int __SMID_V2_encode(u8 *inbox, void *ku_reg, void *context);
int __SMID_V2_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SMID_V2(struct sx_dev *dev, struct ku_access_smid_v2_reg *reg_data);
int sx_EMAD_ACCESS_REG_SMID_V2(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_smid_v2_reg *reg);
int __QSTCT_encode(u8 *inbox, void *ku_reg, void *context);
int __QSTCT_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_QSTCT(struct sx_dev *dev, struct ku_access_qstct_reg *reg_data);
int sx_EMAD_ACCESS_REG_QSTCT(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_qstct_reg *reg);
int __PMCR_encode(u8 *inbox, void *ku_reg, void *context);
int __PMCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMCR(struct sx_dev *dev, struct ku_access_pmcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PMCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmcr_reg *reg);
int __MTPPS_encode(u8 *inbox, void *ku_reg, void *context);
int __MTPPS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTPPS(struct sx_dev *dev, struct ku_access_mtpps_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTPPS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtpps_reg *reg);
int __PPCNT_encode(u8 *inbox, void *ku_reg, void *context);
int __PPCNT_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPCNT(struct sx_dev *dev, struct ku_access_ppcnt_reg *reg_data);
int sx_EMAD_ACCESS_REG_PPCNT(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ppcnt_reg *reg);
int __MDIR_encode(u8 *inbox, void *ku_reg, void *context);
int __MDIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MDIR(struct sx_dev *dev, struct ku_access_mdir_reg *reg_data);
int sx_EMAD_ACCESS_REG_MDIR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mdir_reg *reg);
int __SPZR_encode(u8 *inbox, void *ku_reg, void *context);
int __SPZR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SPZR(struct sx_dev *dev, struct ku_access_spzr_reg *reg_data);
int sx_EMAD_ACCESS_REG_SPZR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_spzr_reg *reg);
int __MTCAP_encode(u8 *inbox, void *ku_reg, void *context);
int __MTCAP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTCAP(struct sx_dev *dev, struct ku_access_mtcap_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTCAP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtcap_reg *reg);
int __MDFCR_encode(u8 *inbox, void *ku_reg, void *context);
int __MDFCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MDFCR(struct sx_dev *dev, struct ku_access_mdfcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_MDFCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mdfcr_reg *reg);
int __PAOS_encode(u8 *inbox, void *ku_reg, void *context);
int __PAOS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PAOS(struct sx_dev *dev, struct ku_access_paos_reg *reg_data);
int sx_EMAD_ACCESS_REG_PAOS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_paos_reg *reg);
int __MTUTC_encode(u8 *inbox, void *ku_reg, void *context);
int __MTUTC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTUTC(struct sx_dev *dev, struct ku_access_mtutc_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTUTC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtutc_reg *reg);
int __PTYS_encode(u8 *inbox, void *ku_reg, void *context);
int __PTYS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PTYS(struct sx_dev *dev, struct ku_access_ptys_reg *reg_data);
int sx_EMAD_ACCESS_REG_PTYS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ptys_reg *reg);
int __PPLR_encode(u8 *inbox, void *ku_reg, void *context);
int __PPLR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPLR(struct sx_dev *dev, struct ku_access_pplr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PPLR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pplr_reg *reg);
int __HETT_encode(u8 *inbox, void *ku_reg, void *context);
int __HETT_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_HETT(struct sx_dev *dev, struct ku_access_hett_reg *reg_data);
int sx_EMAD_ACCESS_REG_HETT(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_hett_reg *reg);
int __MTPPST_encode(u8 *inbox, void *ku_reg, void *context);
int __MTPPST_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTPPST(struct sx_dev *dev, struct ku_access_mtppst_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTPPST(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtppst_reg *reg);
int __IBFMR_encode(u8 *inbox, void *ku_reg, void *context);
int __IBFMR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_IBFMR(struct sx_dev *dev, struct ku_access_ibfmr_reg *reg_data);
int sx_EMAD_ACCESS_REG_IBFMR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ibfmr_reg *reg);
int __MSEES_encode(u8 *inbox, void *ku_reg, void *context);
int __MSEES_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MSEES(struct sx_dev *dev, struct ku_access_msees_reg *reg_data);
int sx_EMAD_ACCESS_REG_MSEES(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_msees_reg *reg);
int __SGCR_encode(u8 *inbox, void *ku_reg, void *context);
int __SGCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SGCR(struct sx_dev *dev, struct ku_access_sgcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_SGCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sgcr_reg *reg);
int __MPNHLFE_encode(u8 *inbox, void *ku_reg, void *context);
int __MPNHLFE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MPNHLFE(struct sx_dev *dev, struct ku_access_mpnhlfe_reg *reg_data);
int sx_EMAD_ACCESS_REG_MPNHLFE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mpnhlfe_reg *reg);
int __MTEWE_encode(u8 *inbox, void *ku_reg, void *context);
int __MTEWE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTEWE(struct sx_dev *dev, struct ku_access_mtewe_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTEWE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtewe_reg *reg);
int __MTPSPU_encode(u8 *inbox, void *ku_reg, void *context);
int __MTPSPU_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTPSPU(struct sx_dev *dev, struct ku_access_mtpspu_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTPSPU(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtpspu_reg *reg);
int __SLSIR_encode(u8 *inbox, void *ku_reg, void *context);
int __SLSIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SLSIR(struct sx_dev *dev, struct ku_access_slsir_reg *reg_data);
int sx_EMAD_ACCESS_REG_SLSIR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_slsir_reg *reg);
int __PPAD_encode(u8 *inbox, void *ku_reg, void *context);
int __PPAD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPAD(struct sx_dev *dev, struct ku_access_ppad_reg *reg_data);
int sx_EMAD_ACCESS_REG_PPAD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ppad_reg *reg);
int __MOCS_encode(u8 *inbox, void *ku_reg, void *context);
int __MOCS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOCS(struct sx_dev *dev, struct ku_access_mocs_reg *reg_data);
int sx_EMAD_ACCESS_REG_MOCS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mocs_reg *reg);
int __PLLP_encode(u8 *inbox, void *ku_reg, void *context);
int __PLLP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PLLP(struct sx_dev *dev, struct ku_access_pllp_reg *reg_data);
int sx_EMAD_ACCESS_REG_PLLP(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pllp_reg *reg);
int __SPAD_encode(u8 *inbox, void *ku_reg, void *context);
int __SPAD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SPAD(struct sx_dev *dev, struct ku_access_spad_reg *reg_data);
int sx_EMAD_ACCESS_REG_SPAD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_spad_reg *reg);
int __SBGCR_encode(u8 *inbox, void *ku_reg, void *context);
int __SBGCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SBGCR(struct sx_dev *dev, struct ku_access_sbgcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_SBGCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sbgcr_reg *reg);
int __MCQI_encode(u8 *inbox, void *ku_reg, void *context);
int __MCQI_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MCQI(struct sx_dev *dev, struct ku_access_mcqi_reg *reg_data);
int sx_EMAD_ACCESS_REG_MCQI(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mcqi_reg *reg);
int __PTASV2_encode(u8 *inbox, void *ku_reg, void *context);
int __PTASV2_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PTASV2(struct sx_dev *dev, struct ku_access_ptasv2_reg *reg_data);
int sx_EMAD_ACCESS_REG_PTASV2(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_ptasv2_reg *reg);
int __MSECQ_encode(u8 *inbox, void *ku_reg, void *context);
int __MSECQ_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MSECQ(struct sx_dev *dev, struct ku_access_msecq_reg *reg_data);
int sx_EMAD_ACCESS_REG_MSECQ(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_msecq_reg *reg);
int __MTPPSE_encode(u8 *inbox, void *ku_reg, void *context);
int __MTPPSE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTPPSE(struct sx_dev *dev, struct ku_access_mtppse_reg *reg_data);
int sx_EMAD_ACCESS_REG_MTPPSE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mtppse_reg *reg);
int __PERAR_encode(u8 *inbox, void *ku_reg, void *context);
int __PERAR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PERAR(struct sx_dev *dev, struct ku_access_perar_reg *reg_data);
int sx_EMAD_ACCESS_REG_PERAR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_perar_reg *reg);
int __PEVPB_encode(u8 *inbox, void *ku_reg, void *context);
int __PEVPB_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PEVPB(struct sx_dev *dev, struct ku_access_pevpb_reg *reg_data);
int sx_EMAD_ACCESS_REG_PEVPB(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pevpb_reg *reg);
int __SFGC_encode(u8 *inbox, void *ku_reg, void *context);
int __SFGC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SFGC(struct sx_dev *dev, struct ku_access_sfgc_reg *reg_data);
int sx_EMAD_ACCESS_REG_SFGC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sfgc_reg *reg);
int __MCION_encode(u8 *inbox, void *ku_reg, void *context);
int __MCION_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MCION(struct sx_dev *dev, struct ku_access_mcion_reg *reg_data);
int sx_EMAD_ACCESS_REG_MCION(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mcion_reg *reg);
int __PCSR_encode(u8 *inbox, void *ku_reg, void *context);
int __PCSR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PCSR(struct sx_dev *dev, struct ku_access_pcsr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PCSR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pcsr_reg *reg);
int __MAFCR_encode(u8 *inbox, void *ku_reg, void *context);
int __MAFCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MAFCR(struct sx_dev *dev, struct ku_access_mafcr_reg *reg_data);
int sx_EMAD_ACCESS_REG_MAFCR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mafcr_reg *reg);
int __SBSRD_encode(u8 *inbox, void *ku_reg, void *context);
int __SBSRD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SBSRD(struct sx_dev *dev, struct ku_access_sbsrd_reg *reg_data);
int sx_EMAD_ACCESS_REG_SBSRD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_sbsrd_reg *reg);
int __QSPTC_encode(u8 *inbox, void *ku_reg, void *context);
int __QSPTC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_QSPTC(struct sx_dev *dev, struct ku_access_qsptc_reg *reg_data);
int sx_EMAD_ACCESS_REG_QSPTC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_qsptc_reg *reg);
int __IDDD_encode(u8 *inbox, void *ku_reg, void *context);
int __IDDD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_IDDD(struct sx_dev *dev, struct ku_access_iddd_reg *reg_data);
int sx_EMAD_ACCESS_REG_IDDD(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_iddd_reg *reg);
int __PMAOS_encode(u8 *inbox, void *ku_reg, void *context);
int __PMAOS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMAOS(struct sx_dev *dev, struct ku_access_pmaos_reg *reg_data);
int sx_EMAD_ACCESS_REG_PMAOS(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pmaos_reg *reg);
int __PBSR_encode(u8 *inbox, void *ku_reg, void *context);
int __PBSR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PBSR(struct sx_dev *dev, struct ku_access_pbsr_reg *reg_data);
int sx_EMAD_ACCESS_REG_PBSR(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_pbsr_reg *reg);
int __MSGI_encode(u8 *inbox, void *ku_reg, void *context);
int __MSGI_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MSGI(struct sx_dev *dev, struct ku_access_msgi_reg *reg_data);
int sx_EMAD_ACCESS_REG_MSGI(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_msgi_reg *reg);
int __MSPI_encode(u8 *inbox, void *ku_reg, void *context);
int __MSPI_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MSPI(struct sx_dev *dev, struct ku_access_mspi_reg *reg_data);
int sx_EMAD_ACCESS_REG_MSPI(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mspi_reg *reg);
int __MCC_encode(u8 *inbox, void *ku_reg, void *context);
int __MCC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MCC(struct sx_dev *dev, struct ku_access_mcc_reg *reg_data);
int sx_EMAD_ACCESS_REG_MCC(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mcc_reg *reg);
int __MOPCE_encode(u8 *inbox, void *ku_reg, void *context);
int __MOPCE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOPCE(struct sx_dev *dev, struct ku_access_mopce_reg *reg_data);
int sx_EMAD_ACCESS_REG_MOPCE(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mopce_reg *reg);
int __MCDA_encode(u8 *inbox, void *ku_reg, void *context);
int __MCDA_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MCDA(struct sx_dev *dev, struct ku_access_mcda_reg *reg_data);
int sx_EMAD_ACCESS_REG_MCDA(struct sx_dev *dev,
                          emad_prio_e priority,
                          sx_emad_method_e method,
                          const struct sx_emad_in_params *in_params,
                          struct sx_emad_out_params *out_params,
                          struct ku_mcda_reg *reg);


#endif /* SX_CMD_AUTO_H_ */

/************************************************
 *                  EOF                         *
 ***********************************************/
