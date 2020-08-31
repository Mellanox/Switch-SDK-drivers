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

#ifndef SX_CMD_H_
#define SX_CMD_H_

/************************************************
 * Includes
 ***********************************************/

#include <linux/dma-mapping.h>

#include <linux/mlx_sx/device.h>

enum {
    /* initialization and teardown commands */
    SX_CMD_MAP_FA = 0xfff,
    SX_CMD_UNMAP_FA = 0xffe,
    SX_CMD_QUERY_FW = 0x4,
    SX_CMD_QUERY_BOARDINFO = 0x6,
    SX_CMD_QUERY_AQ_CAP = 0x3,
    SX_CMD_CONFIG_PROFILE = 0x100,
    SX_CMD_QUERY_RSRC = 0x101,
    SX_CMD_ISSU_FW = 0x102,

    /* General commands */
    SX_CMD_ACCESS_REG = 0x40,

    /* port commands */
    SX_CMD_CONF_PORT = 0xc,
    SX_CMD_INIT_PORT = 0x9,
    SX_CMD_CLOSE_PORT = 0xa,

    /* DQ commands */
    SX_CMD_SW2HW_DQ = 0x201,
    SX_CMD_HW2SW_DQ = 0x202,
    SX_CMD_2ERR_DQ = 0x1e,
    SX_CMD_QUERY_DQ = 0x22,

    /* CQ commands */
    SX_CMD_SW2HW_CQ = 0x16,
    SX_CMD_HW2SW_CQ = 0x17,
    SX_CMD_QUERY_CQ = 0x18,

    /* EQ commands */
    SX_CMD_SW2HW_EQ = 0x13,
    SX_CMD_HW2SW_EQ = 0x14,
    SX_CMD_QUERY_EQ = 0x15,

    /* Infiniband commands */
    SX_CMD_INIT_MAD_DEMUX = 0x203,
    SX_CMD_INIT_SYSTEM_M_KEY = 0x204,
    SX_CMD_MAD_IFC = 0x24,
};
#ifndef INCREASED_TIMEOUT
enum {
    SX_CMD_TIME_CLASS_A = 10000,
    SX_CMD_TIME_CLASS_B = 10000,
    SX_CMD_TIME_CLASS_C = 10000,
};
#else
enum {
    SX_CMD_TIME_CLASS_A = 10000,
    SX_CMD_TIME_CLASS_B = 10000,
    SX_CMD_TIME_CLASS_C = 10000,
};
#endif
enum {
    SX_MAILBOX_SIZE = 4096
};

struct sx_dev;


/************************************************
 * Structs
 ***********************************************/
struct sx_cmd_mailbox {
    void      *buf;
    dma_addr_t dma;
    u64        imm_data;
    u8         is_in_param_imm;
    u8         is_out_param_imm;
};

typedef void generic_reg_data;
typedef int (*sx_ACCESS_REG_generic)(struct sx_dev *dev, generic_reg_data *reg_data);

/************************************************
 * Functions
 ***********************************************/
int __sx_cmd(struct sx_dev *dev, int sx_dev_id,
             struct sx_cmd_mailbox *in_param,
             struct sx_cmd_mailbox *out_param,
             int out_is_imm, u32 in_modifier, u8 op_modifier,
             u16 op, unsigned long timeout, int in_mb_size);

/* Invoke a command with no output parameter */
static inline int sx_cmd(struct sx_dev         *dev,
                         int                    sx_dev_id,
                         struct sx_cmd_mailbox *in_param,
                         u32                    in_modifier,
                         u8                     op_modifier,
                         u16                    op,
                         unsigned long          timeout,
                         int                    in_mb_size)
{
    return __sx_cmd(dev, sx_dev_id, in_param, NULL, 0, in_modifier,
                    op_modifier, op, timeout, in_mb_size);
}

/* Invoke a command with an output mailbox */
static inline int sx_cmd_box(struct sx_dev         *dev,
                             int                    sx_dev_id,
                             struct sx_cmd_mailbox *in_param,
                             struct sx_cmd_mailbox *out_param,
                             u32                    in_modifier,
                             u8                     op_modifier,
                             u16                    op,
                             unsigned long          timeout,
                             int                    in_mb_size)
{
    return __sx_cmd(dev, sx_dev_id, in_param, out_param, 0, in_modifier,
                    op_modifier, op, timeout, in_mb_size);
}

/*
 * Invoke a command with an immediate output parameter (and copy the
 * output into the caller's out_param pointer after the command
 * executes).
 */
static inline int sx_cmd_imm(struct sx_dev         *dev,
                             int                    sx_dev_id,
                             struct sx_cmd_mailbox *in_param,
                             struct sx_cmd_mailbox *out_param,
                             u32                    in_modifier,
                             u8                     op_modifier,
                             u16                    op,
                             unsigned long          timeout,
                             int                    in_mb_size)
{
    return __sx_cmd(dev, sx_dev_id,  in_param, out_param, 1,
                    in_modifier, op_modifier, op, timeout, in_mb_size);
}

void sx_cmd_set_op_tlv(struct ku_operation_tlv *op_tlv, u32 reg_id, u8 method);
struct sx_cmd_mailbox * sx_alloc_cmd_mailbox(struct sx_dev *dev, int sx_dev_id);
void sx_free_cmd_mailbox(struct sx_dev *dev, struct sx_cmd_mailbox *mailbox);
void sx_cmd_event(struct sx_dev *dev, u16 token, u8 status, u64 out_param);
int sx_cmd_use_events(struct sx_dev *dev);
void sx_cmd_use_polling(struct sx_dev *dev);

int sx_cmd_send_mad_sync(struct sx_dev *dev,
                         int            dev_id,
                         u32            in_modifier,
                         u8             op_modifier,
                         void          *in_mad,
                         int            in_size,
                         void          *out_mad,
                         int            out_size);

int sx_ACCESS_REG_SPZR(struct sx_dev *dev, struct ku_access_spzr_reg *reg_data);
int sx_QUERY_FW(struct sx_dev *dev, struct ku_query_fw* query_fw);
int sx_QUERY_CQ(struct sx_dev *dev, u8 cqn, struct ku_query_cq *cq_context_p);
int sx_QUERY_RSRC(struct sx_dev *dev, struct ku_query_rsrc* query_rsrc);
int sx_QUERY_AQ_CAP(struct sx_dev *dev);
int sx_QUERY_BOARDINFO(struct sx_dev *dev, struct ku_query_board_info *adapter);
int sx_ACCESS_REG_MGIR(struct sx_dev *dev, struct ku_access_mgir_reg *reg_data);
int sx_ACCESS_REG_PLIB(struct sx_dev *dev, struct ku_access_plib_reg *reg_data);
int sx_ACCESS_REG_PMLP(struct sx_dev *dev, struct ku_access_pmlp_reg *reg_data);
int sx_ACCESS_REG_PTYS(struct sx_dev *dev, struct ku_access_ptys_reg *reg_data);
int sx_ACCESS_REG_QSTCT(struct sx_dev *dev, struct ku_access_qstct_reg *reg_data);
int sx_ACCESS_REG_QSPTC(struct sx_dev *dev, struct ku_access_qsptc_reg *reg_data);
int sx_ACCESS_REG_PSPA(struct sx_dev *dev, struct ku_access_pspa_reg *reg_data);
int sx_ACCESS_REG_PPLM(struct sx_dev *dev, struct ku_access_pplm_reg *reg_data);
int sx_ACCESS_REG_PLPC(struct sx_dev *dev, struct ku_access_plpc_reg *reg_data);
int sx_ACCESS_REG_PMPC(struct sx_dev *dev, struct ku_access_pmpc_reg *reg_data);
int sx_ACCESS_REG_MJTAG(struct sx_dev *dev, struct ku_access_mjtag_reg *reg_data);
int sx_ACCESS_REG_PMPR(struct sx_dev *dev, struct ku_access_pmpr_reg *reg_data);
int sx_ACCESS_REG_PMTU(struct sx_dev *dev, struct ku_access_pmtu_reg *reg_data);
int sx_ACCESS_REG_PDDR(struct sx_dev *dev, struct ku_access_pddr_reg *reg_data);
int sx_ACCESS_REG_PELC(struct sx_dev *dev, struct ku_access_pelc_reg *reg_data);
int sx_ACCESS_REG_HTGT(struct sx_dev *dev, struct ku_access_htgt_reg *reg_data);
int sx_ACCESS_REG_MFSC(struct sx_dev *dev, struct ku_access_mfsc_reg *reg_data);
int sx_ACCESS_REG_MFSM(struct sx_dev *dev, struct ku_access_mfsm_reg *reg_data);
int sx_ACCESS_REG_MFSL(struct sx_dev *dev, struct ku_access_mfsl_reg *reg_data);
int sx_ACCESS_REG_PVLC(struct sx_dev *dev, struct ku_access_pvlc_reg *reg_data);
int sx_ACCESS_REG_MCIA(struct sx_dev *dev, struct ku_access_mcia_reg *reg_data);
int sx_ACCESS_REG_HPKT(struct sx_dev *dev, struct ku_access_hpkt_reg *reg_data);
int sx_ACCESS_REG_HCAP(struct sx_dev *dev, struct ku_access_hcap_reg *reg_data);
int sx_ACCESS_REG_HDRT(struct sx_dev *dev, struct ku_access_hdrt_reg *reg_data);
int sx_ACCESS_REG_QPRT(struct sx_dev *dev, struct ku_access_qprt_reg *reg_data);
int sx_ACCESS_REG_MFCR(struct sx_dev *dev, struct ku_access_mfcr_reg *reg_data);
int sx_ACCESS_REG_FORE(struct sx_dev *dev, struct ku_access_fore_reg *reg_data);
int sx_ACCESS_REG_MTCAP(struct sx_dev *dev, struct ku_access_mtcap_reg *reg_data);
int sx_ACCESS_REG_MTBR(struct sx_dev *dev, struct ku_access_mtbr_reg *reg_data);
int sx_ACCESS_REG_MTWE(struct sx_dev *dev, struct ku_access_mtwe_reg *reg_data);
int sx_ACCESS_REG_MMDIO(struct sx_dev *dev, struct ku_access_mmdio_reg *reg_data);
int sx_ACCESS_REG_MMIA(struct sx_dev *dev, struct ku_access_mmia_reg *reg_data);
int sx_ACCESS_REG_MFPA(struct sx_dev *dev, struct ku_access_mfpa_reg *reg_data);
int sx_ACCESS_REG_MFBE(struct sx_dev *dev, struct ku_access_mfbe_reg *reg_data);
int sx_ACCESS_REG_MFBA(struct sx_dev *dev, struct ku_access_mfba_reg *reg_data);
int sx_ACCESS_REG_QCAP(struct sx_dev *dev, struct ku_access_qcap_reg *reg_data);
int sx_ACCESS_REG_RAW(struct sx_dev *dev, struct ku_access_raw_reg *reg_data);
int sx_ACCESS_REG_RAW_BUFF(struct sx_dev *dev, struct ku_access_reg_raw_buff *raw_data);
int sx_ACCESS_REG_PMAOS(struct sx_dev *dev, struct ku_access_pmaos_reg *reg_data);
int sx_ACCESS_REG_MFM(struct sx_dev *dev, struct ku_access_mfm_reg *reg_data);
int sx_ACCESS_REG_SPAD(struct sx_dev *dev, struct ku_access_spad_reg *reg_data);
int sx_ACCESS_REG_SSPR(struct sx_dev *dev, struct ku_access_sspr_reg *reg_data);
int sx_ACCESS_REG_SPMCR(struct sx_dev *dev, struct ku_access_spmcr_reg *reg_data);
int sx_ACCESS_REG_PBMC(struct sx_dev *dev, struct ku_access_pbmc_reg *reg_data);
int sx_ACCESS_REG_PPTB(struct sx_dev *dev, struct ku_access_pptb_reg *reg_data);
int sx_ACCESS_REG_SMID(struct sx_dev *dev, struct ku_access_smid_reg *reg_data);
int sx_ACCESS_REG_SPVID(struct sx_dev *dev, struct ku_access_spvid_reg *reg_data);
int sx_ACCESS_REG_SFD(struct sx_dev *dev, struct ku_access_sfd_reg *reg_data);
int sx_ACCESS_REG_PPSC(struct sx_dev *dev, struct ku_access_ppsc_reg *reg_data);
int sx_ACCESS_REG_PLBF(struct sx_dev *dev, struct ku_access_plbf_reg *reg_data);
int sx_ACCESS_REG_MHSR(struct sx_dev *dev, struct ku_access_mhsr_reg *reg_data);
int sx_ACCESS_REG_SGCR(struct sx_dev *dev, struct ku_access_sgcr_reg *reg_data);
int sx_ACCESS_REG_MSCI(struct sx_dev *dev, struct ku_access_msci_reg *reg_data);
int sx_ACCESS_REG_MRSR(struct sx_dev *dev, struct ku_access_mrsr_reg *reg_data);
int sx_ACCESS_REG_RGCR(struct sx_dev *dev, struct ku_access_rgcr_reg *reg_data);
int sx_ACCESS_REG_RTPS(struct sx_dev *dev, struct ku_access_rtps_reg *reg_data);
int sx_ACCESS_REG_RTCA(struct sx_dev *dev, struct ku_access_rtca_reg *reg_data);
int sx_ACCESS_REG_RITR(struct sx_dev *dev, struct ku_access_ritr_reg *reg_data);
int sx_ACCESS_REG_RUFT(struct sx_dev *dev, struct ku_access_ruft_reg *reg_data);
int sx_ACCESS_REG_MPSC(struct sx_dev *dev, struct ku_access_mpsc_reg *reg_data);
int sx_SET_SYSTEM_M_KEY(struct sx_dev *dev, struct ku_system_m_key *system_m_key);
int sx_GET_SYSTEM_M_KEY(struct sx_dev *dev, struct ku_system_m_key *system_m_key);
int sx_ACCESS_REG_MLCR(struct sx_dev *dev, struct ku_access_mlcr_reg *reg_data);
int sx_ACCESS_REG_PCNR(struct sx_dev *dev, struct ku_access_pcnr_reg *reg_data);
int sx_ACCESS_REG_MTPPPC(struct sx_dev *dev, struct ku_access_mtpppc_reg *reg_data);
int sx_ACCESS_REG_MTPPTR(struct sx_dev *dev, struct ku_access_mtpptr_reg *reg_data, u8 to_host_order);
int sx_ACCESS_REG_MTPTPT(struct sx_dev *dev, struct ku_access_mtptpt_reg *reg_data);
int sx_ACCESS_REG_MTPCPC(struct sx_dev *dev, struct ku_access_mtpcpc_reg *reg_data);
int sx_ACCESS_REG_MTPPS(struct sx_dev *dev, struct ku_access_mtpps_reg *reg_data);
int sx_ACCESS_REG_SBCTC(struct sx_dev *dev, struct ku_access_sbctc_reg *reg_data);
int sx_ACCESS_REG_SBCTR(struct sx_dev *dev, struct ku_access_sbctr_reg *reg_data);
int sx_ACCESS_REG_SBGCR(struct sx_dev *dev, struct ku_access_sbgcr_reg *reg_data);
int sx_ACCESS_REG_PPBMP(struct sx_dev *dev, struct ku_access_ppbmp_reg *reg_data);
int sx_ACCESS_REG_PPBMC(struct sx_dev *dev, struct ku_access_ppbmc_reg *reg_data);
int sx_ACCESS_REG_PPBME(struct sx_dev *dev, struct ku_access_ppbme_reg *reg_data);
int sx_ACCESS_REG_MCION(struct sx_dev *dev, struct ku_access_mcion_reg *reg_data);
int sx_ACCESS_REG_PMMP(struct sx_dev *dev, struct ku_access_pmmp_reg *reg_data);
int sx_ACCESS_REG_QPCR(struct sx_dev *dev, struct ku_access_qpcr_reg *reg_data);
int sx_ACCESS_REG_SBCM(struct sx_dev *dev, struct ku_access_sbcm_reg *reg_data);
int sx_ACCESS_REG_MFGD(struct sx_dev *dev, struct ku_access_mfgd_reg *reg_data);
int sx_ISSU_FW_START(struct sx_dev *dev);
int sx_ISSU_FW_STATUS_GET(struct sx_dev *dev, u8 *issu_fw_status);

int sx_MAD_DEMUX(struct sx_dev *sx_dev, int dev_id, uint8_t enable);

#endif /* SX_CMD_H_ */

/************************************************
 *                  EOF                         *
 ***********************************************/
