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

#include <linux/module.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include "../sx_dpt.h"
#include "../sx.h"
#include "../ioctl_internal.h"

/************************************************
 *  Global
 ***********************************************/


SX_CORE_IOCTL_ACCESS_REG_HANDLER(HMON, ku_access_hmon_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(HETT, ku_access_hett_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MTPPS, ku_access_mtpps_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MTPPSE, ku_access_mtppse_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MTUTC, ku_access_mtutc_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MTPPST, ku_access_mtppst_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MSECQ, ku_access_msecq_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MSEES, ku_access_msees_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MSPI, ku_access_mspi_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MCION, ku_access_mcion_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MCFS, ku_access_mcfs_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MGPIR, ku_access_mgpir_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MDFCR, ku_access_mdfcr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MTECR, ku_access_mtecr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MTCAP, ku_access_mtcap_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MVCAP, ku_access_mvcap_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MTMP, ku_access_mtmp_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MGIR, ku_access_mgir_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MSGI, ku_access_msgi_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MDIR, ku_access_mdir_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MINI, ku_access_mini_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MCAM, ku_access_mcam_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MECCC, ku_access_meccc_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MFRC, ku_access_mfrc_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MMCR, ku_access_mmcr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MFRI, ku_access_mfri_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MFRP, ku_access_mfrp_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MOGCR, ku_access_mogcr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MOCS, ku_access_mocs_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MOPCE, ku_access_mopce_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MOCA, ku_access_moca_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MOFRB, ku_access_mofrb_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MOFPH, ku_access_mofph_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MOFPC, ku_access_mofpc_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MTPSPU, ku_access_mtpspu_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MTPCPC, ku_access_mtpcpc_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MFGD, ku_access_mfgd_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MFDE, ku_access_mfde_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MOFRD, ku_access_mofrd_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(SGCR, ku_access_sgcr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(SPAD, ku_access_spad_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(SMID_V2, ku_access_smid_v2_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(SPZR, ku_access_spzr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(IBFMR, ku_access_ibfmr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(IBFMRC, ku_access_ibfmrc_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PTYS, ku_access_ptys_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PAOS, ku_access_paos_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PPCNT, ku_access_ppcnt_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PMAOS, ku_access_pmaos_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PMPE, ku_access_pmpe_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PMMP, ku_access_pmmp_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PMCR, ku_access_pmcr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PMTM, ku_access_pmtm_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PPLR, ku_access_pplr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(SLTP, ku_access_sltp_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(SLSIR, ku_access_slsir_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PDDR, ku_access_pddr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PMDR, ku_access_pmdr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PPHCR, ku_access_pphcr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(SLLM, ku_access_sllm_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PPCGP, ku_access_ppcgp_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PCSR, ku_access_pcsr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PMTU, ku_access_pmtu_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PPAD, ku_access_ppad_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PBSR, ku_access_pbsr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PLLP, ku_access_pllp_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PPCR, ku_access_ppcr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PLIBDB, ku_access_plibdb_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PPIR, ku_access_ppir_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(SBGCR, ku_access_sbgcr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(SBSRD, ku_access_sbsrd_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(SBCTR, ku_access_sbctr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PERAR, ku_access_perar_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(CEER, ku_access_ceer_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(RIRT, ku_access_rirt_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(FSED, ku_access_fsed_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(FSHE, ku_access_fshe_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(USACN, ku_access_usacn_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(UTCC, ku_access_utcc_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(UPCNT, ku_access_upcnt_reg);

const ioctl_handler_cb_t
ioctl_auto_reg_handler_table[CTRL_CMD_ACCESS_REG_MAX - CTRL_CMD_ACCESS_REG_MIN + 1] = {

    IOCTL_REG_HANDLER(HMON),
    IOCTL_REG_HANDLER(HETT),
    IOCTL_REG_HANDLER(MTPPS),
    IOCTL_REG_HANDLER(MTPPSE),
    IOCTL_REG_HANDLER(MTUTC),
    IOCTL_REG_HANDLER(MTPPST),
    IOCTL_REG_HANDLER(MSECQ),
    IOCTL_REG_HANDLER(MSEES),
    IOCTL_REG_HANDLER(MSPI),
    IOCTL_REG_HANDLER(MCION),
    IOCTL_REG_HANDLER(MCFS),
    IOCTL_REG_HANDLER(MGPIR),
    IOCTL_REG_HANDLER(MDFCR),
    IOCTL_REG_HANDLER(MTECR),
    IOCTL_REG_HANDLER(MTCAP),
    IOCTL_REG_HANDLER(MVCAP),
    IOCTL_REG_HANDLER(MTMP),
    IOCTL_REG_HANDLER(MGIR),
    IOCTL_REG_HANDLER(MSGI),
    IOCTL_REG_HANDLER(MDIR),
    IOCTL_REG_HANDLER(MINI),
    IOCTL_REG_HANDLER(MCAM),
    IOCTL_REG_HANDLER(MECCC),
    IOCTL_REG_HANDLER(MFRC),
    IOCTL_REG_HANDLER(MMCR),
    IOCTL_REG_HANDLER(MFRI),
    IOCTL_REG_HANDLER(MFRP),
    IOCTL_REG_HANDLER(MOGCR),
    IOCTL_REG_HANDLER(MOCS),
    IOCTL_REG_HANDLER(MOPCE),
    IOCTL_REG_HANDLER(MOCA),
    IOCTL_REG_HANDLER(MOFRB),
    IOCTL_REG_HANDLER(MOFPH),
    IOCTL_REG_HANDLER(MOFPC),
    IOCTL_REG_HANDLER(MTPSPU),
    IOCTL_REG_HANDLER(MTPCPC),
    IOCTL_REG_HANDLER(MFGD),
    IOCTL_REG_HANDLER(MFDE),
    IOCTL_REG_HANDLER(MOFRD),
    IOCTL_REG_HANDLER(SGCR),
    IOCTL_REG_HANDLER(SPAD),
    IOCTL_REG_HANDLER(SMID_V2),
    IOCTL_REG_HANDLER(SPZR),
    IOCTL_REG_HANDLER(IBFMR),
    IOCTL_REG_HANDLER(IBFMRC),
    IOCTL_REG_HANDLER(PTYS),
    IOCTL_REG_HANDLER(PAOS),
    IOCTL_REG_HANDLER(PPCNT),
    IOCTL_REG_HANDLER(PMAOS),
    IOCTL_REG_HANDLER(PMPE),
    IOCTL_REG_HANDLER(PMMP),
    IOCTL_REG_HANDLER(PMCR),
    IOCTL_REG_HANDLER(PMTM),
    IOCTL_REG_HANDLER(PPLR),
    IOCTL_REG_HANDLER(SLTP),
    IOCTL_REG_HANDLER(SLSIR),
    IOCTL_REG_HANDLER(PDDR),
    IOCTL_REG_HANDLER(PMDR),
    IOCTL_REG_HANDLER(PPHCR),
    IOCTL_REG_HANDLER(SLLM),
    IOCTL_REG_HANDLER(PPCGP),
    IOCTL_REG_HANDLER(PCSR),
    IOCTL_REG_HANDLER(PMTU),
    IOCTL_REG_HANDLER(PPAD),
    IOCTL_REG_HANDLER(PBSR),
    IOCTL_REG_HANDLER(PLLP),
    IOCTL_REG_HANDLER(PPCR),
    IOCTL_REG_HANDLER(PLIBDB),
    IOCTL_REG_HANDLER(PPIR),
    IOCTL_REG_HANDLER(SBGCR),
    IOCTL_REG_HANDLER(SBSRD),
    IOCTL_REG_HANDLER(SBCTR),
    IOCTL_REG_HANDLER(PERAR),
    IOCTL_REG_HANDLER(CEER),
    IOCTL_REG_HANDLER(RIRT),
    IOCTL_REG_HANDLER(FSED),
    IOCTL_REG_HANDLER(FSHE),
    IOCTL_REG_HANDLER(USACN),
    IOCTL_REG_HANDLER(UTCC),
    IOCTL_REG_HANDLER(UPCNT),
};

/************************************************
 *  Define
 ***********************************************/

/************************************************
 *  Enum
 ***********************************************/

/************************************************
 *  MODULE settings
 ***********************************************/

/************************************************
 *  Functions
 ***********************************************/

/************************************************
 *  MODULE init/exit
 ***********************************************/

/************************************************
 *                  EOF                         *
 ***********************************************/
