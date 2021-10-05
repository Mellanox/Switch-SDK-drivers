/*
 * Copyright (C) 2008-2021 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

int __IGCR_encode(u8 *inbox, void *ku_reg, void *context);
int __IGCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_IGCR(struct sx_dev *dev, struct ku_access_igcr_reg *reg_data);
int __MTMP_encode(u8 *inbox, void *ku_reg, void *context);
int __MTMP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTMP(struct sx_dev *dev, struct ku_access_mtmp_reg *reg_data);
int __MOGCR_encode(u8 *inbox, void *ku_reg, void *context);
int __MOGCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOGCR(struct sx_dev *dev, struct ku_access_mogcr_reg *reg_data);
int __HMON_encode(u8 *inbox, void *ku_reg, void *context);
int __HMON_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_HMON(struct sx_dev *dev, struct ku_access_hmon_reg *reg_data);
int __MGPIR_encode(u8 *inbox, void *ku_reg, void *context);
int __MGPIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MGPIR(struct sx_dev *dev, struct ku_access_mgpir_reg *reg_data);
int __PMTM_encode(u8 *inbox, void *ku_reg, void *context);
int __PMTM_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMTM(struct sx_dev *dev, struct ku_access_pmtm_reg *reg_data);
int __PMTU_encode(u8 *inbox, void *ku_reg, void *context);
int __PMTU_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMTU(struct sx_dev *dev, struct ku_access_pmtu_reg *reg_data);
int __PMMP_encode(u8 *inbox, void *ku_reg, void *context);
int __PMMP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMMP(struct sx_dev *dev, struct ku_access_pmmp_reg *reg_data);
int __MTWE_encode(u8 *inbox, void *ku_reg, void *context);
int __MTWE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTWE(struct sx_dev *dev, struct ku_access_mtwe_reg *reg_data);
int __MGIR_encode(u8 *inbox, void *ku_reg, void *context);
int __MGIR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MGIR(struct sx_dev *dev, struct ku_access_mgir_reg *reg_data);
int __CEER_encode(u8 *inbox, void *ku_reg, void *context);
int __CEER_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_CEER(struct sx_dev *dev, struct ku_access_ceer_reg *reg_data);
int __IBFMRC_encode(u8 *inbox, void *ku_reg, void *context);
int __IBFMRC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_IBFMRC(struct sx_dev *dev, struct ku_access_ibfmrc_reg *reg_data);
int __SMID_V2_encode(u8 *inbox, void *ku_reg, void *context);
int __SMID_V2_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_SMID_V2(struct sx_dev *dev, struct ku_access_smid_v2_reg *reg_data);
int __PPCNT_encode(u8 *inbox, void *ku_reg, void *context);
int __PPCNT_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPCNT(struct sx_dev *dev, struct ku_access_ppcnt_reg *reg_data);
int __MDFCR_encode(u8 *inbox, void *ku_reg, void *context);
int __MDFCR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MDFCR(struct sx_dev *dev, struct ku_access_mdfcr_reg *reg_data);
int __PAOS_encode(u8 *inbox, void *ku_reg, void *context);
int __PAOS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PAOS(struct sx_dev *dev, struct ku_access_paos_reg *reg_data);
int __MTUTC_encode(u8 *inbox, void *ku_reg, void *context);
int __MTUTC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTUTC(struct sx_dev *dev, struct ku_access_mtutc_reg *reg_data);
int __IBFMR_encode(u8 *inbox, void *ku_reg, void *context);
int __IBFMR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_IBFMR(struct sx_dev *dev, struct ku_access_ibfmr_reg *reg_data);
int __MTEWE_encode(u8 *inbox, void *ku_reg, void *context);
int __MTEWE_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MTEWE(struct sx_dev *dev, struct ku_access_mtewe_reg *reg_data);
int __PPAD_encode(u8 *inbox, void *ku_reg, void *context);
int __PPAD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PPAD(struct sx_dev *dev, struct ku_access_ppad_reg *reg_data);
int __MOCS_encode(u8 *inbox, void *ku_reg, void *context);
int __MOCS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MOCS(struct sx_dev *dev, struct ku_access_mocs_reg *reg_data);
int __PLLP_encode(u8 *inbox, void *ku_reg, void *context);
int __PLLP_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PLLP(struct sx_dev *dev, struct ku_access_pllp_reg *reg_data);
int __MCQI_encode(u8 *inbox, void *ku_reg, void *context);
int __MCQI_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MCQI(struct sx_dev *dev, struct ku_access_mcqi_reg *reg_data);
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
int __IDDD_encode(u8 *inbox, void *ku_reg, void *context);
int __IDDD_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_IDDD(struct sx_dev *dev, struct ku_access_iddd_reg *reg_data);
int __PMAOS_encode(u8 *inbox, void *ku_reg, void *context);
int __PMAOS_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PMAOS(struct sx_dev *dev, struct ku_access_pmaos_reg *reg_data);
int __PBSR_encode(u8 *inbox, void *ku_reg, void *context);
int __PBSR_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_PBSR(struct sx_dev *dev, struct ku_access_pbsr_reg *reg_data);
int __MCC_encode(u8 *inbox, void *ku_reg, void *context);
int __MCC_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MCC(struct sx_dev *dev, struct ku_access_mcc_reg *reg_data);
int __MCDA_encode(u8 *inbox, void *ku_reg, void *context);
int __MCDA_decode(u8 *inbox, void *ku_reg, void *context);
int sx_ACCESS_REG_MCDA(struct sx_dev *dev, struct ku_access_mcda_reg *reg_data);


#endif /* SX_CMD_AUTO_H_ */

/************************************************
 *                  EOF                         *
 ***********************************************/
