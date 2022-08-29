/*
* Copyright (c) 2008-2021,  Mellanox Technologies. All rights reserved.
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


SX_CORE_IOCTL_ACCESS_REG_HANDLER(IGCR, ku_access_igcr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MTMP, ku_access_mtmp_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MOGCR, ku_access_mogcr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(HMON, ku_access_hmon_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MGPIR, ku_access_mgpir_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PMTM, ku_access_pmtm_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PMMP, ku_access_pmmp_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MGIR, ku_access_mgir_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(CEER, ku_access_ceer_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(IBFMRC, ku_access_ibfmrc_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PPCNT, ku_access_ppcnt_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MDFCR, ku_access_mdfcr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PAOS, ku_access_paos_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MTUTC, ku_access_mtutc_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(IBFMR, ku_access_ibfmr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PPAD, ku_access_ppad_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MOCS, ku_access_mocs_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PLLP, ku_access_pllp_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MCQI, ku_access_mcqi_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PEVPB, ku_access_pevpb_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(SFGC, ku_access_sfgc_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MCION, ku_access_mcion_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PCSR, ku_access_pcsr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(IDDD, ku_access_iddd_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PMAOS, ku_access_pmaos_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(PBSR, ku_access_pbsr_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(SBSRD, ku_access_sbsrd_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MCC, ku_access_mcc_reg);
SX_CORE_IOCTL_ACCESS_REG_HANDLER(MCDA, ku_access_mcda_reg);

const ioctl_handler_cb_t
ioctl_auto_reg_handler_table[CTRL_CMD_ACCESS_REG_MAX - CTRL_CMD_ACCESS_REG_MIN + 1] = {

    IOCTL_REG_HANDLER(IGCR),
    IOCTL_REG_HANDLER(MTMP),
    IOCTL_REG_HANDLER(MOGCR),
    IOCTL_REG_HANDLER(HMON),
    IOCTL_REG_HANDLER(MGPIR),
    IOCTL_REG_HANDLER(PMTM),
    IOCTL_REG_HANDLER(PMMP),
    IOCTL_REG_HANDLER(MGIR),
    IOCTL_REG_HANDLER(CEER),
    IOCTL_REG_HANDLER(IBFMRC),
    IOCTL_REG_HANDLER(PPCNT),
    IOCTL_REG_HANDLER(MDFCR),
    IOCTL_REG_HANDLER(PAOS),
    IOCTL_REG_HANDLER(MTUTC),
    IOCTL_REG_HANDLER(IBFMR),
    IOCTL_REG_HANDLER(PPAD),
    IOCTL_REG_HANDLER(MOCS),
    IOCTL_REG_HANDLER(PLLP),
    IOCTL_REG_HANDLER(MCQI),
    IOCTL_REG_HANDLER(PEVPB),
    IOCTL_REG_HANDLER(SFGC),
    IOCTL_REG_HANDLER(MCION),
    IOCTL_REG_HANDLER(PCSR),
    IOCTL_REG_HANDLER(IDDD),
    IOCTL_REG_HANDLER(PMAOS),
    IOCTL_REG_HANDLER(PBSR),
    IOCTL_REG_HANDLER(SBSRD),
    IOCTL_REG_HANDLER(MCC),
    IOCTL_REG_HANDLER(MCDA),
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
