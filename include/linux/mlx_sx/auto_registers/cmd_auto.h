/*
 * Copyright (C) 2008-2022 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

/************************************************
 * Structs
 ***********************************************/

/************************************************
 * Functions
 ***********************************************/

int __PMDR_encode(u8 *inbox, void *ku_reg, void *context);
int __PMDR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMDR(struct sx_dev *dev, struct ku_access_pmdr_reg *reg_data);
int __MTECR_encode(u8 *inbox, void *ku_reg, void *context);
int __MTECR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTECR(struct sx_dev *dev, struct ku_access_mtecr_reg *reg_data);
int __IGCR_encode(u8 *inbox, void *ku_reg, void *context);
int __IGCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_IGCR(struct sx_dev *dev, struct ku_access_igcr_reg *reg_data);
int __MVCAP_encode(u8 *inbox, void *ku_reg, void *context);
int __MVCAP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MVCAP(struct sx_dev *dev, struct ku_access_mvcap_reg *reg_data);
int __MTMP_encode(u8 *inbox, void *ku_reg, void *context);
int __MTMP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTMP(struct sx_dev *dev, struct ku_access_mtmp_reg *reg_data);
int __MOGCR_encode(u8 *inbox, void *ku_reg, void *context);
int __MOGCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOGCR(struct sx_dev *dev, struct ku_access_mogcr_reg *reg_data);
int __PDDR_encode(u8 *inbox, void *ku_reg, void *context);
int __PDDR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PDDR(struct sx_dev *dev, struct ku_access_pddr_reg *reg_data);
int __SBCTR_encode(u8 *inbox, void *ku_reg, void *context);
int __SBCTR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SBCTR(struct sx_dev *dev, struct ku_access_sbctr_reg *reg_data);
int __HMON_encode(u8 *inbox, void *ku_reg, void *context);
int __HMON_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_HMON(struct sx_dev *dev, struct ku_access_hmon_reg *reg_data);
int __MGPIR_encode(u8 *inbox, void *ku_reg, void *context);
int __MGPIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MGPIR(struct sx_dev *dev, struct ku_access_mgpir_reg *reg_data);
int __PMTM_encode(u8 *inbox, void *ku_reg, void *context);
int __PMTM_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMTM(struct sx_dev *dev, struct ku_access_pmtm_reg *reg_data);
int __SLLM_encode(u8 *inbox, void *ku_reg, void *context);
int __SLLM_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SLLM(struct sx_dev *dev, struct ku_access_sllm_reg *reg_data);
int __PMTU_encode(u8 *inbox, void *ku_reg, void *context);
int __PMTU_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMTU(struct sx_dev *dev, struct ku_access_pmtu_reg *reg_data);
int __PMMP_encode(u8 *inbox, void *ku_reg, void *context);
int __PMMP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMMP(struct sx_dev *dev, struct ku_access_pmmp_reg *reg_data);
int __SLTP_encode(u8 *inbox, void *ku_reg, void *context);
int __SLTP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SLTP(struct sx_dev *dev, struct ku_access_sltp_reg *reg_data);
int __PPHCR_encode(u8 *inbox, void *ku_reg, void *context);
int __PPHCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPHCR(struct sx_dev *dev, struct ku_access_pphcr_reg *reg_data);
int __QCAP_encode(u8 *inbox, void *ku_reg, void *context);
int __QCAP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_QCAP(struct sx_dev *dev, struct ku_access_qcap_reg *reg_data);
int __MTWE_encode(u8 *inbox, void *ku_reg, void *context);
int __MTWE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTWE(struct sx_dev *dev, struct ku_access_mtwe_reg *reg_data);
int __MFGD_encode(u8 *inbox, void *ku_reg, void *context);
int __MFGD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MFGD(struct sx_dev *dev, struct ku_access_mfgd_reg *reg_data);
int __MGIR_encode(u8 *inbox, void *ku_reg, void *context);
int __MGIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MGIR(struct sx_dev *dev, struct ku_access_mgir_reg *reg_data);
int __PPCGP_encode(u8 *inbox, void *ku_reg, void *context);
int __PPCGP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPCGP(struct sx_dev *dev, struct ku_access_ppcgp_reg *reg_data);
int __CEER_encode(u8 *inbox, void *ku_reg, void *context);
int __CEER_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_CEER(struct sx_dev *dev, struct ku_access_ceer_reg *reg_data);
int __IBFMRC_encode(u8 *inbox, void *ku_reg, void *context);
int __IBFMRC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_IBFMRC(struct sx_dev *dev, struct ku_access_ibfmrc_reg *reg_data);
int __MECCC_encode(u8 *inbox, void *ku_reg, void *context);
int __MECCC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MECCC(struct sx_dev *dev, struct ku_access_meccc_reg *reg_data);
int __SMID_V2_encode(u8 *inbox, void *ku_reg, void *context);
int __SMID_V2_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SMID_V2(struct sx_dev *dev, struct ku_access_smid_v2_reg *reg_data);
int __QSTCT_encode(u8 *inbox, void *ku_reg, void *context);
int __QSTCT_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_QSTCT(struct sx_dev *dev, struct ku_access_qstct_reg *reg_data);
int __MTPPS_encode(u8 *inbox, void *ku_reg, void *context);
int __MTPPS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTPPS(struct sx_dev *dev, struct ku_access_mtpps_reg *reg_data);
int __PPCNT_encode(u8 *inbox, void *ku_reg, void *context);
int __PPCNT_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPCNT(struct sx_dev *dev, struct ku_access_ppcnt_reg *reg_data);
int __MDIR_encode(u8 *inbox, void *ku_reg, void *context);
int __MDIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MDIR(struct sx_dev *dev, struct ku_access_mdir_reg *reg_data);
int __SPZR_encode(u8 *inbox, void *ku_reg, void *context);
int __SPZR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SPZR(struct sx_dev *dev, struct ku_access_spzr_reg *reg_data);
int __MTCAP_encode(u8 *inbox, void *ku_reg, void *context);
int __MTCAP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTCAP(struct sx_dev *dev, struct ku_access_mtcap_reg *reg_data);
int __MDFCR_encode(u8 *inbox, void *ku_reg, void *context);
int __MDFCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MDFCR(struct sx_dev *dev, struct ku_access_mdfcr_reg *reg_data);
int __PAOS_encode(u8 *inbox, void *ku_reg, void *context);
int __PAOS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PAOS(struct sx_dev *dev, struct ku_access_paos_reg *reg_data);
int __MTUTC_encode(u8 *inbox, void *ku_reg, void *context);
int __MTUTC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTUTC(struct sx_dev *dev, struct ku_access_mtutc_reg *reg_data);
int __PTYS_encode(u8 *inbox, void *ku_reg, void *context);
int __PTYS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PTYS(struct sx_dev *dev, struct ku_access_ptys_reg *reg_data);
int __PPLR_encode(u8 *inbox, void *ku_reg, void *context);
int __PPLR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPLR(struct sx_dev *dev, struct ku_access_pplr_reg *reg_data);
int __HETT_encode(u8 *inbox, void *ku_reg, void *context);
int __HETT_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_HETT(struct sx_dev *dev, struct ku_access_hett_reg *reg_data);
int __MTPPST_encode(u8 *inbox, void *ku_reg, void *context);
int __MTPPST_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTPPST(struct sx_dev *dev, struct ku_access_mtppst_reg *reg_data);
int __IBFMR_encode(u8 *inbox, void *ku_reg, void *context);
int __IBFMR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_IBFMR(struct sx_dev *dev, struct ku_access_ibfmr_reg *reg_data);
int __MSEES_encode(u8 *inbox, void *ku_reg, void *context);
int __MSEES_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MSEES(struct sx_dev *dev, struct ku_access_msees_reg *reg_data);
int __SGCR_encode(u8 *inbox, void *ku_reg, void *context);
int __SGCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SGCR(struct sx_dev *dev, struct ku_access_sgcr_reg *reg_data);
int __MTEWE_encode(u8 *inbox, void *ku_reg, void *context);
int __MTEWE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTEWE(struct sx_dev *dev, struct ku_access_mtewe_reg *reg_data);
int __MTPSPU_encode(u8 *inbox, void *ku_reg, void *context);
int __MTPSPU_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTPSPU(struct sx_dev *dev, struct ku_access_mtpspu_reg *reg_data);
int __SLSIR_encode(u8 *inbox, void *ku_reg, void *context);
int __SLSIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SLSIR(struct sx_dev *dev, struct ku_access_slsir_reg *reg_data);
int __PPAD_encode(u8 *inbox, void *ku_reg, void *context);
int __PPAD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPAD(struct sx_dev *dev, struct ku_access_ppad_reg *reg_data);
int __MOCS_encode(u8 *inbox, void *ku_reg, void *context);
int __MOCS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOCS(struct sx_dev *dev, struct ku_access_mocs_reg *reg_data);
int __PLLP_encode(u8 *inbox, void *ku_reg, void *context);
int __PLLP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PLLP(struct sx_dev *dev, struct ku_access_pllp_reg *reg_data);
int __SPAD_encode(u8 *inbox, void *ku_reg, void *context);
int __SPAD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SPAD(struct sx_dev *dev, struct ku_access_spad_reg *reg_data);
int __SBGCR_encode(u8 *inbox, void *ku_reg, void *context);
int __SBGCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SBGCR(struct sx_dev *dev, struct ku_access_sbgcr_reg *reg_data);
int __MCQI_encode(u8 *inbox, void *ku_reg, void *context);
int __MCQI_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MCQI(struct sx_dev *dev, struct ku_access_mcqi_reg *reg_data);
int __MSECQ_encode(u8 *inbox, void *ku_reg, void *context);
int __MSECQ_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MSECQ(struct sx_dev *dev, struct ku_access_msecq_reg *reg_data);
int __MTPPSE_encode(u8 *inbox, void *ku_reg, void *context);
int __MTPPSE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTPPSE(struct sx_dev *dev, struct ku_access_mtppse_reg *reg_data);
int __PERAR_encode(u8 *inbox, void *ku_reg, void *context);
int __PERAR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PERAR(struct sx_dev *dev, struct ku_access_perar_reg *reg_data);
int __PEVPB_encode(u8 *inbox, void *ku_reg, void *context);
int __PEVPB_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PEVPB(struct sx_dev *dev, struct ku_access_pevpb_reg *reg_data);
int __SFGC_encode(u8 *inbox, void *ku_reg, void *context);
int __SFGC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SFGC(struct sx_dev *dev, struct ku_access_sfgc_reg *reg_data);
int __MCION_encode(u8 *inbox, void *ku_reg, void *context);
int __MCION_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MCION(struct sx_dev *dev, struct ku_access_mcion_reg *reg_data);
int __PCSR_encode(u8 *inbox, void *ku_reg, void *context);
int __PCSR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PCSR(struct sx_dev *dev, struct ku_access_pcsr_reg *reg_data);
int __MAFCR_encode(u8 *inbox, void *ku_reg, void *context);
int __MAFCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MAFCR(struct sx_dev *dev, struct ku_access_mafcr_reg *reg_data);
int __SBSRD_encode(u8 *inbox, void *ku_reg, void *context);
int __SBSRD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SBSRD(struct sx_dev *dev, struct ku_access_sbsrd_reg *reg_data);
int __QSPTC_encode(u8 *inbox, void *ku_reg, void *context);
int __QSPTC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_QSPTC(struct sx_dev *dev, struct ku_access_qsptc_reg *reg_data);
int __IDDD_encode(u8 *inbox, void *ku_reg, void *context);
int __IDDD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_IDDD(struct sx_dev *dev, struct ku_access_iddd_reg *reg_data);
int __PMAOS_encode(u8 *inbox, void *ku_reg, void *context);
int __PMAOS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMAOS(struct sx_dev *dev, struct ku_access_pmaos_reg *reg_data);
int __PBSR_encode(u8 *inbox, void *ku_reg, void *context);
int __PBSR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PBSR(struct sx_dev *dev, struct ku_access_pbsr_reg *reg_data);
int __MSGI_encode(u8 *inbox, void *ku_reg, void *context);
int __MSGI_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MSGI(struct sx_dev *dev, struct ku_access_msgi_reg *reg_data);
int __MSPI_encode(u8 *inbox, void *ku_reg, void *context);
int __MSPI_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MSPI(struct sx_dev *dev, struct ku_access_mspi_reg *reg_data);
int __MCC_encode(u8 *inbox, void *ku_reg, void *context);
int __MCC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MCC(struct sx_dev *dev, struct ku_access_mcc_reg *reg_data);
int __MOPCE_encode(u8 *inbox, void *ku_reg, void *context);
int __MOPCE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOPCE(struct sx_dev *dev, struct ku_access_mopce_reg *reg_data);
int __MCDA_encode(u8 *inbox, void *ku_reg, void *context);
int __MCDA_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MCDA(struct sx_dev *dev, struct ku_access_mcda_reg *reg_data);


#endif /* SX_CMD_AUTO_H_ */

/************************************************
 *                  EOF                         *
 ***********************************************/
