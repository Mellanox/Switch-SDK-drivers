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

#include "fw.h"
#include "sx.h"
#include "sgmii.h"
#include "cq.h"
#include "fw_internal.h"
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/driver.h>
#include "sxd_access_reg_pddr.h"

extern struct sx_globals sx_glb;

#define REG_START_OFFSET 0x14

/* old implementation defined all register field's offsets from the beginning of the buffer (inbox/outbox)
 * and not from the beginning of the register area itself. 'auto-reg' infrastructure works with functions that
 * get the pointer to the beginning of the register area. the two definitions below adapts old implementation to
 * new one so we don't have to recalculate all offsets.
 */
#define SX_PUT_REG_FIELD(dest, source, offset) SX_PUT(dest, source, ((offset) - REG_START_OFFSET))
#define SX_GET_REG_FIELD(dest, source, offset) SX_GET(dest, source, ((offset) - REG_START_OFFSET))

int sx_ACCESS_REG_internal(struct sx_dev           *dev,
                           uint8_t                  dev_id,
                           uint32_t                 flags,
                           struct ku_operation_tlv *op_tlv,
                           access_reg_encode_cb_t   reg_encode_cb,
                           access_reg_decode_cb_t   reg_decode_cb,
                           u16                      reg_len,
                           void                    *ku_reg,
                           void                    *context)
{
#define REG_TLV_OFFSET     0x10
#define REG_TLV_TYPE       0x03
#define OPERATION_TLV_SIZE 0x10
#define IN_MB_SIZE(reg_dword_size) (((reg_dword_size) * 4) + OPERATION_TLV_SIZE)

    struct sx_cmd_mailbox *in_mailbox;
    struct sx_cmd_mailbox *out_mailbox;
    u8                    *inbox;
    u8                    *outbox;
    int                    err;
    u16                    type_len;

    if (!dev || !op_tlv || !ku_reg) {
        return -EINVAL;
    }

    in_mailbox = sx_alloc_cmd_mailbox(dev, dev_id);
    if (IS_ERR(in_mailbox)) {
        return PTR_ERR(in_mailbox);
    }

    out_mailbox = sx_alloc_cmd_mailbox(dev, dev_id);
    if (IS_ERR(out_mailbox)) {
        err = PTR_ERR(out_mailbox);
        goto out_free;
    }

    inbox = in_mailbox->buf;
    memset(inbox, 0, SX_MAILBOX_SIZE);
    outbox = out_mailbox->buf;

    set_operation_tlv(inbox, op_tlv);
    type_len = (REG_TLV_TYPE << 11) | reg_len;
    SX_PUT(inbox, type_len, REG_TLV_OFFSET);

    if (reg_encode_cb) {
        err = reg_encode_cb(inbox + REG_START_OFFSET, ku_reg, context);
        if (err) {
            goto out;
        }
    }

    err = sx_cmd_box(dev, dev_id, in_mailbox, out_mailbox, 0, 0,
                     SX_CMD_ACCESS_REG, SX_CMD_TIME_CLASS_A,
                     IN_MB_SIZE(reg_len));
    if (err) {
        if (flags & SX_ACCESS_REG_F_IGNORE_FW_RET_CODE) {
            err = 0;
        }

        goto out;
    }

    get_operation_tlv(outbox, op_tlv);
    if (reg_decode_cb && (op_tlv->method == 0x01)) { /* 0x01 = Query */
        err = reg_decode_cb(outbox + REG_START_OFFSET, ku_reg, context);
        if (err) {
            goto out;
        }
    }

out:
    sx_free_cmd_mailbox(dev, out_mailbox);

out_free:
    sx_free_cmd_mailbox(dev, in_mailbox);
    return err;
}


/************************************************
 * MGIR
 ***********************************************/
static int __MGIR_decode(u8 *outbox, void *ku_reg, void *context)
{
#define REG_HW_INFO_OFFSET                    0x14
#define REG_HW_INFO_DEVICE_HW_REVISION_OFFSET 0x0
#define REG_HW_INFO_DEVICE_ID_OFFSET          0x2
#define REG_HW_INFO_DVFS_OFFSET               0x7
#define REG_HW_INFO_UPTIME_OFFSET             0x1c

#define REG_FW_INFO_OFFSET                    0x34
#define REG_FW_INFO_MAJOR_OFFSET              0x01
#define REG_FW_INFO_MINOR_OFFSET              0x02
#define REG_FW_INFO_SUB_MINOR_OFFSET          0x03
#define REG_FW_INFO_BUILD_ID_OFFSET           0x04
#define REG_FW_INFO_MONTH_OFFSET              0x08
#define REG_FW_INFO_DAY_OFFSET                0x09
#define REG_FW_INFO_YEAR_OFFSET               0x0a
#define REG_FW_INFO_HOUR_OFFSET               0x0e
#define REG_FW_INFO_PSID_OFFSET               0x10
#define REG_FW_INFO_INI_FILE_VERSION_OFFSET   0x20
#define REG_FW_INFO_EXTENDED_MAJOR_OFFSET     0x24
#define REG_FW_INFO_EXTENDED_MINOR_OFFSET     0x28
#define REG_FW_INFO_EXTENDED_SUB_MINOR_OFFSET 0x2c

#define REG_SW_INFO_OFFSET           0x74
#define REG_SW_INFO_MAJOR_OFFSET     0x01
#define REG_SW_INFO_MINOR_OFFSET     0x02
#define REG_SW_INFO_SUB_MINOR_OFFSET 0x03

    struct ku_mgir_reg *mgir_reg = (struct ku_mgir_reg*)ku_reg;

    SX_GET_REG_FIELD(mgir_reg->hw_info.device_hw_revision,
                     outbox,
                     REG_HW_INFO_OFFSET + REG_HW_INFO_DEVICE_HW_REVISION_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->hw_info.device_id, outbox, REG_HW_INFO_OFFSET + REG_HW_INFO_DEVICE_ID_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->hw_info.dvfs, outbox, REG_HW_INFO_OFFSET + REG_HW_INFO_DVFS_OFFSET);
    mgir_reg->hw_info.dvfs &= 0x1f;

    SX_GET_REG_FIELD(mgir_reg->hw_info.uptime, outbox, REG_HW_INFO_OFFSET + REG_HW_INFO_UPTIME_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->fw_info.major, outbox, REG_FW_INFO_OFFSET + REG_FW_INFO_MAJOR_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->fw_info.minor, outbox, REG_FW_INFO_OFFSET + REG_FW_INFO_MINOR_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->fw_info.sub_minor, outbox, REG_FW_INFO_OFFSET + REG_FW_INFO_SUB_MINOR_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->fw_info.build_id, outbox, REG_FW_INFO_OFFSET + REG_FW_INFO_BUILD_ID_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->fw_info.month, outbox, REG_FW_INFO_OFFSET + REG_FW_INFO_MONTH_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->fw_info.day, outbox, REG_FW_INFO_OFFSET + REG_FW_INFO_DAY_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->fw_info.year, outbox, REG_FW_INFO_OFFSET + REG_FW_INFO_YEAR_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->fw_info.hour, outbox, REG_FW_INFO_OFFSET + REG_FW_INFO_HOUR_OFFSET);
    memcpy(mgir_reg->fw_info.psid,
           outbox - REG_START_OFFSET + REG_FW_INFO_OFFSET + REG_FW_INFO_PSID_OFFSET,
           SX_PSID_SIZE);
    SX_GET_REG_FIELD(mgir_reg->fw_info.ini_file_version,
                     outbox,
                     REG_FW_INFO_OFFSET + REG_FW_INFO_INI_FILE_VERSION_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->fw_info.extended_major, outbox, REG_FW_INFO_OFFSET + REG_FW_INFO_EXTENDED_MAJOR_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->fw_info.extended_minor, outbox, REG_FW_INFO_OFFSET + REG_FW_INFO_EXTENDED_MINOR_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->fw_info.extended_sub_minor,
                     outbox,
                     REG_FW_INFO_OFFSET + REG_FW_INFO_EXTENDED_SUB_MINOR_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->sw_info.major, outbox, REG_SW_INFO_OFFSET + REG_SW_INFO_MAJOR_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->sw_info.minor, outbox, REG_FW_INFO_OFFSET + REG_SW_INFO_MINOR_OFFSET);
    SX_GET_REG_FIELD(mgir_reg->sw_info.sub_minor, outbox, REG_SW_INFO_OFFSET + REG_SW_INFO_SUB_MINOR_OFFSET);

    return 0;
}

int sx_ACCESS_REG_MGIR(struct sx_dev *dev, struct ku_access_mgir_reg *reg_data)
{
#define MGIR_REG_LEN 0x21

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  NULL,
                                  __MGIR_decode,
                                  MGIR_REG_LEN,
                                  &reg_data->mgir_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MGIR);


/************************************************
 * PLIB
 ***********************************************/
#define REG_LOCAL_PORT_OFFSET 0x15
#define REG_IB_PORT_OFFSET    0x17

static int __PLIB_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_plib_reg *plib_reg = (struct ku_plib_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, plib_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, plib_reg->ib_port, REG_IB_PORT_OFFSET);

    return 0;
}

static int __PLIB_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_plib_reg *plib_reg = (struct ku_plib_reg*)ku_reg;

    SX_GET_REG_FIELD(plib_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(plib_reg->ib_port, outbox, REG_IB_PORT_OFFSET);

    return 0;
}

int sx_ACCESS_REG_PLIB(struct sx_dev *dev, struct ku_access_plib_reg *reg_data)
{
#define PLIB_REG_LEN 0x05

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PLIB_encode,
                                  __PLIB_decode,
                                  PLIB_REG_LEN,
                                  &reg_data->plib_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PLIB);

/************************************************
 * PMLP
 ***********************************************/
#define REG_LOCAL_PORT_OFFSET 0x15
#define REG_DIFF_RX_TX_OFFSET 0x14
#define REG_WIDTH_OFFSET      0x17
#define REG_RX_LANE_0_OFFSET  0x18
#define REG_LANE_0_OFFSET     0x19
#define REG_MODULE_0_OFFSET   0x1b
#define PMLP_REG_LEN          0x09
#define REG_BYTES_PER_ROW     4

static int __PMLP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmlp_reg *pmlp_reg = (struct ku_pmlp_reg*)ku_reg;
    u8                  tmp_u8 = 0;
    int                 i;

    tmp_u8 |= (pmlp_reg->use_different_rx_tx & 0x01) << 7;
    tmp_u8 |= (pmlp_reg->autosplit & 0x01) << 6;
    SX_PUT_REG_FIELD(inbox, tmp_u8, REG_DIFF_RX_TX_OFFSET);

    SX_PUT_REG_FIELD(inbox, pmlp_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmlp_reg->width, REG_WIDTH_OFFSET);
    for (i = 0; i < NUMBER_OF_SERDESES; i++) {
        SX_PUT_REG_FIELD(inbox, pmlp_reg->rx_lane[i], REG_RX_LANE_0_OFFSET + (REG_BYTES_PER_ROW * i));
        SX_PUT_REG_FIELD(inbox, pmlp_reg->lane[i], REG_LANE_0_OFFSET + (REG_BYTES_PER_ROW * i));
        SX_PUT_REG_FIELD(inbox, pmlp_reg->module[i], REG_MODULE_0_OFFSET + (REG_BYTES_PER_ROW * i));
    }

    return 0;
}

static int __PMLP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmlp_reg *pmlp_reg = (struct ku_pmlp_reg*)ku_reg;
    u8                  tmp_u8 = 0;
    int                 i;

    SX_GET_REG_FIELD(tmp_u8, outbox, REG_DIFF_RX_TX_OFFSET);
    pmlp_reg->use_different_rx_tx = tmp_u8 >> 7;
    SX_GET_REG_FIELD(pmlp_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pmlp_reg->width, outbox, REG_WIDTH_OFFSET);

    for (i = 0; i < NUMBER_OF_SERDESES; i++) {
        SX_GET_REG_FIELD(pmlp_reg->rx_lane[i], outbox, REG_RX_LANE_0_OFFSET + (REG_BYTES_PER_ROW * i));
        SX_GET_REG_FIELD(pmlp_reg->lane[i], outbox, REG_LANE_0_OFFSET + (REG_BYTES_PER_ROW * i));
        SX_GET_REG_FIELD(pmlp_reg->module[i], outbox, REG_MODULE_0_OFFSET + (REG_BYTES_PER_ROW * i));
    }

    return 0;
}

int sx_ACCESS_REG_PMLP(struct sx_dev *dev, struct ku_access_pmlp_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMLP_encode,
                                  __PMLP_decode,
                                  PMLP_REG_LEN,
                                  &reg_data->pmlp_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMLP);


/************************************************
 * MHSR
 ***********************************************/
#define REG_HEALTH_OFFSET 0x17
#define MHSR_REG_LEN      0x2

static int __MHSR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mhsr_reg *mhsr_reg = (struct ku_mhsr_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mhsr_reg->health, REG_HEALTH_OFFSET);
    return 0;
}

static int __MHSR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mhsr_reg *mhsr_reg = (struct ku_mhsr_reg*)ku_reg;

    SX_GET_REG_FIELD(mhsr_reg->health, outbox, REG_HEALTH_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MHSR(struct sx_dev *dev, struct ku_access_mhsr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MHSR_encode,
                                  __MHSR_decode,
                                  MHSR_REG_LEN,
                                  &reg_data->mhsr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MHSR);


/************************************************
 * PTYS
 ***********************************************/
#define REG_AN_DISABLE_AND_TX_ABA_OFFSET 0x14
#define REG_LOCAL_PORT_OFFSET            0x15
#define REG_PROTO_MASK_OFFSET            0x17
#define REG_AN_STATUS_OFFSET             0x18
#define REG_DATA_RATE_OPER_OFFSET        0x1a
#define REG_FC_CAP_OFFSET                0x1c
#define REG_ETH_CAP_OFFSET               0x20
#define REG_IB_LINK_WIDTH_CAP_OFFSET     0x24
#define REG_IB_CAP_OFFSET                0x26
#define REG_FC_ADMIN_OFFSET              0x28
#define REG_ETH_ADMIN_OFFSET             0x2c
#define REG_IB_LINK_WIDTH_ADMIN_OFFSET   0x30
#define REG_IB_ADMIN_OFFSET              0x32
#define REG_FC_OPER_OFFSET               0x34
#define REG_ETH_OPER_OFFSET              0x38
#define REG_IB_LINK_WIDTH_OPER_OFFSET    0x3c
#define REG_IB_OPER_OFFSET               0x3e
#define REG_CONNECTOR_TYPE_OFFSET        0x43
#define REG_ETH_LP_ADVERTISE_OFFSET      0x44
#define PTYS_REG_LEN                     0x11

static int __PTYS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ptys_reg *ptys_reg = (struct ku_ptys_reg*)ku_reg;
    uint8_t             an_disable_tx_aba = 0;
    uint8_t             an_status = 0;
    uint8_t             connector_type = 0;
    uint16_t            ib_link_width_capability = 0;
    uint16_t            ib_proto_capability = 0;

    an_disable_tx_aba = ptys_reg->an_disable_admin << 6;
    an_disable_tx_aba |= ptys_reg->an_disable_cap << 5;
    an_disable_tx_aba |= ptys_reg->force_tx_aba_param;
    SX_PUT_REG_FIELD(inbox, an_disable_tx_aba, REG_AN_DISABLE_AND_TX_ABA_OFFSET);
    SX_PUT_REG_FIELD(inbox, ptys_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, ptys_reg->proto_mask, REG_PROTO_MASK_OFFSET);
    an_status = ptys_reg->an_status;
    an_status = an_status << 4;
    SX_PUT_REG_FIELD(inbox, an_status, REG_AN_STATUS_OFFSET);
    SX_PUT_REG_FIELD(inbox, ptys_reg->data_rate_oper, REG_DATA_RATE_OPER_OFFSET);
    SX_PUT_REG_FIELD(inbox, ptys_reg->ext_eth_proto_capability, REG_FC_CAP_OFFSET);
    SX_PUT_REG_FIELD(inbox, ptys_reg->eth_proto_capability, REG_ETH_CAP_OFFSET);
    ib_link_width_capability = ptys_reg->ib_link_width_capability;
    SX_PUT_REG_FIELD(inbox, ib_link_width_capability, REG_IB_LINK_WIDTH_CAP_OFFSET);
    ib_proto_capability = ptys_reg->ib_proto_capability;
    SX_PUT_REG_FIELD(inbox, ib_proto_capability, REG_IB_CAP_OFFSET);
    SX_PUT_REG_FIELD(inbox, ptys_reg->ext_eth_proto_admin, REG_FC_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, ptys_reg->eth_proto_admin, REG_ETH_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, ptys_reg->ib_link_width_admin, REG_IB_LINK_WIDTH_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, ptys_reg->ib_proto_admin, REG_IB_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, ptys_reg->ext_eth_proto_oper, REG_FC_OPER_OFFSET);
    SX_PUT_REG_FIELD(inbox, ptys_reg->eth_proto_oper, REG_ETH_OPER_OFFSET);
    SX_PUT_REG_FIELD(inbox, ptys_reg->ib_link_width_oper, REG_IB_LINK_WIDTH_OPER_OFFSET);
    SX_PUT_REG_FIELD(inbox, ptys_reg->ib_proto_oper, REG_IB_OPER_OFFSET);
    connector_type = ptys_reg->connector_type;
    SX_PUT_REG_FIELD(inbox, connector_type, REG_CONNECTOR_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, ptys_reg->eth_proto_lp_advertise, REG_ETH_LP_ADVERTISE_OFFSET);

    return 0;
}

static int __PTYS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ptys_reg *ptys_reg = (struct ku_ptys_reg*)ku_reg;
    uint8_t             an_disable_tx_aba = 0;
    uint8_t             an_status = 0;
    uint8_t             connector_type = 0;
    uint16_t            ib_link_width_capability = 0;
    uint16_t            ib_proto_capability = 0;

    SX_GET_REG_FIELD(an_disable_tx_aba, outbox, REG_AN_DISABLE_AND_TX_ABA_OFFSET);
    ptys_reg->an_disable_admin = (an_disable_tx_aba >> 6) & 0x1;
    ptys_reg->an_disable_cap = (an_disable_tx_aba >> 5) & 0x1;
    ptys_reg->force_tx_aba_param = an_disable_tx_aba & 0x1;
    SX_GET_REG_FIELD(ptys_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(ptys_reg->proto_mask, outbox, REG_PROTO_MASK_OFFSET);
    SX_GET_REG_FIELD(an_status, outbox, REG_AN_STATUS_OFFSET);
    ptys_reg->an_status = an_status >> 4;
    SX_GET_REG_FIELD(ptys_reg->data_rate_oper, outbox, REG_DATA_RATE_OPER_OFFSET);
    SX_GET_REG_FIELD(ptys_reg->ext_eth_proto_capability, outbox, REG_FC_CAP_OFFSET);
    SX_GET_REG_FIELD(ptys_reg->eth_proto_capability, outbox, REG_ETH_CAP_OFFSET);
    SX_GET_REG_FIELD(ib_link_width_capability, outbox, REG_IB_LINK_WIDTH_CAP_OFFSET);
    ptys_reg->ib_link_width_capability = ib_link_width_capability;
    SX_GET_REG_FIELD(ib_proto_capability, outbox, REG_IB_CAP_OFFSET);
    ptys_reg->ib_proto_capability = ib_proto_capability;
    SX_GET_REG_FIELD(ptys_reg->ext_eth_proto_admin, outbox, REG_FC_ADMIN_OFFSET);
    SX_GET_REG_FIELD(ptys_reg->eth_proto_admin, outbox, REG_ETH_ADMIN_OFFSET);
    SX_GET_REG_FIELD(ptys_reg->ib_link_width_admin, outbox, REG_IB_LINK_WIDTH_ADMIN_OFFSET);
    SX_GET_REG_FIELD(ptys_reg->ib_proto_admin, outbox, REG_IB_ADMIN_OFFSET);
    SX_GET_REG_FIELD(ptys_reg->ext_eth_proto_oper, outbox, REG_FC_OPER_OFFSET);
    SX_GET_REG_FIELD(ptys_reg->eth_proto_oper, outbox, REG_ETH_OPER_OFFSET);
    SX_GET_REG_FIELD(ptys_reg->ib_link_width_oper, outbox, REG_IB_LINK_WIDTH_OPER_OFFSET);
    SX_GET_REG_FIELD(ptys_reg->ib_proto_oper, outbox, REG_IB_OPER_OFFSET);
    SX_GET_REG_FIELD(connector_type, outbox, REG_CONNECTOR_TYPE_OFFSET);
    ptys_reg->connector_type = connector_type;
    SX_GET_REG_FIELD(ptys_reg->eth_proto_lp_advertise, outbox, REG_ETH_LP_ADVERTISE_OFFSET);

    return 0;
}

int sx_ACCESS_REG_PTYS(struct sx_dev *dev, struct ku_access_ptys_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PTYS_encode,
                                  __PTYS_decode,
                                  PTYS_REG_LEN,
                                  &reg_data->ptys_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PTYS);


/************************************************
 * QSTCT
 ***********************************************/
#define REG_SWID_OFFSET    0x14
#define REG_PRIO_OFFSET    0x16
#define REG_UTCLASS_OFFSET 0x1b
#define REG_MTCLASS_OFFSET 0x1f
#define QSTCT_REG_LEN      0x05

static int __QSTCT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_qstct_reg *qstct_reg = (struct ku_qstct_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, qstct_reg->swid, REG_SWID_OFFSET);
    SX_PUT_REG_FIELD(inbox, qstct_reg->prio, REG_PRIO_OFFSET);
    SX_PUT_REG_FIELD(inbox, qstct_reg->utclass, REG_UTCLASS_OFFSET);
    SX_PUT_REG_FIELD(inbox, qstct_reg->mtclass, REG_MTCLASS_OFFSET);
    return 0;
}

static int __QSTCT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_qstct_reg *qstct_reg = (struct ku_qstct_reg*)ku_reg;

    SX_GET_REG_FIELD(qstct_reg->swid, outbox, REG_SWID_OFFSET);
    SX_GET_REG_FIELD(qstct_reg->prio, outbox, REG_PRIO_OFFSET);
    SX_GET_REG_FIELD(qstct_reg->utclass, outbox, REG_UTCLASS_OFFSET);
    SX_GET_REG_FIELD(qstct_reg->mtclass, outbox, REG_MTCLASS_OFFSET);
    return 0;
}

int sx_ACCESS_REG_QSTCT(struct sx_dev *dev, struct ku_access_qstct_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __QSTCT_encode,
                                  __QSTCT_decode,
                                  QSTCT_REG_LEN,
                                  &reg_data->qstct_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_QSTCT);


/************************************************
 * QSPTC
 ***********************************************/
#define REG_LOCAL_IPORT_OFFSET 0x14
#define REG_LOCAL_EPORT_OFFSET 0x15
#define REG_ITCLASS_OFFSET     0x16
#define REG_TCLASS_OFFSET      0x1b
#define QSPTC_REG_LEN          0x03

static int __QSPTC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_qsptc_reg *qsptc_reg = (struct ku_qsptc_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, qsptc_reg->local_iport, REG_LOCAL_IPORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, qsptc_reg->local_eport, REG_LOCAL_EPORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, qsptc_reg->itclass, REG_ITCLASS_OFFSET);
    SX_PUT_REG_FIELD(inbox, qsptc_reg->tclass, REG_TCLASS_OFFSET);
    return 0;
}

static int __QSPTC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_qsptc_reg *qsptc_reg = (struct ku_qsptc_reg*)ku_reg;

    SX_GET_REG_FIELD(qsptc_reg->local_iport, outbox, REG_LOCAL_IPORT_OFFSET);
    SX_GET_REG_FIELD(qsptc_reg->local_eport, outbox, REG_LOCAL_EPORT_OFFSET);
    SX_GET_REG_FIELD(qsptc_reg->itclass, outbox, REG_ITCLASS_OFFSET);
    SX_GET_REG_FIELD(qsptc_reg->tclass, outbox, REG_TCLASS_OFFSET);
    return 0;
}

int sx_ACCESS_REG_QSPTC(struct sx_dev *dev, struct ku_access_qsptc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __QSPTC_encode,
                                  __QSPTC_decode,
                                  QSPTC_REG_LEN,
                                  &reg_data->qsptc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_QSPTC);


/************************************************
 * PSPA
 ***********************************************/
#define REG_SWID_OFFSET       0x14
#define REG_LOCAL_PORT_OFFSET 0x15
#define REG_SUB_PORT_OFFSET   0x16
#define PSPA_REG_LEN          0x03

static int __PSPA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pspa_reg *pspa_reg = (struct ku_pspa_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, pspa_reg->swid, REG_SWID_OFFSET);
    SX_PUT_REG_FIELD(inbox, pspa_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pspa_reg->sub_port, REG_SUB_PORT_OFFSET);
    return 0;
}

static int __PSPA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pspa_reg *pspa_reg = (struct ku_pspa_reg*)ku_reg;

    SX_GET_REG_FIELD(pspa_reg->swid, outbox, REG_SWID_OFFSET);
    SX_GET_REG_FIELD(pspa_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pspa_reg->sub_port, outbox, REG_SUB_PORT_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PSPA(struct sx_dev *dev, struct ku_access_pspa_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PSPA_encode,
                                  __PSPA_decode,
                                  PSPA_REG_LEN,
                                  &reg_data->pspa_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PSPA);


/************************************************
 * SPZR
 ***********************************************/
#define REG_SWID_OFFSET           0x14
#define REG_NDM_OFFSET            0x16
#define REG_NDM_BIT_N             7
#define REG_ENH_SW_P0_MASK_OFFSET 0x16
#define REG_ENH_SW_P0_MASK_BIT_N  6
#define REG_CM_OFFSET             0x16
#define REG_CM_BIT_N              5
#define REG_VK_OFFSET             0x16
#define REG_VK_BIT_N              4
#define REG_MP_OFFSET             0x16
#define REG_MP_BIT_N              3
#define REG_SIG_OFFSET            0x16
#define REG_SIG_BIT_N             2
#define REG_NG_OFFSET             0x16
#define REG_NG_BIT_N              1
#define REG_G0_OFFSET             0x16
#define REG_G0_BIT_N              0
#define REG_ENH_SW_P0_OFFSET      0x17
#define REG_ENH_SW_P0_BIT_N       1
#define REG_CAP_MASK_OFFSET       0x18
#define REG_SYS_IMG_GUID_H_OFFSET 0x1c
#define REG_SYS_IMG_GUID_L_OFFSET 0x20
#define REG_GUID0_H_OFFSET        0x24
#define REG_GUID0_L_OFFSET        0x28
#define REG_NODE_GUID_H_OFFSET    0x2c
#define REG_NODE_GUID_L_OFFSET    0x30
#define REG_V_KEY_H_OFFSET        0x34
#define REG_V_KEY_L_OFFSET        0x38
#define REG_MAX_PKEY_OFFSET       0x3c
#define REG_NODE_DESC_OFFSET      0x44
#define SPZR_REG_LEN              0x41

static int __SPZR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_spzr_reg *spzr_reg = (struct ku_spzr_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;
    int                 i;

    SX_PUT_REG_FIELD(inbox, spzr_reg->swid, REG_SWID_OFFSET);
    /* Node description mask.Set to 1 to write the NodeDescription field */
    tmp_val_u8 |= (spzr_reg->ndm ? (1 << REG_NDM_BIT_N) : 0);
    /* Enhanced Switch Port 0 mask. When 1, the EnhSwP0 field is valid
     * (see below). When 0, the EnhSwP0 field is ignored */
    tmp_val_u8 |= (spzr_reg->EnhSwP0_mask ? (1 << REG_ENH_SW_P0_MASK_BIT_N) : 0);
    /* Set PortInfo:CapabilityMask to PortInfo:CapabilityMask specified */
    tmp_val_u8 |= (spzr_reg->cm ? (1 << REG_CM_BIT_N) : 0);
    /* Set the internal GSA V_Key. Incoming VendorSpecific MADs must have
     * matching V_Key to the one set by this command */
    tmp_val_u8 |= (spzr_reg->vk ? (1 << REG_VK_BIT_N) : 0);
    /* Change PKey table size to max_pkey */
    tmp_val_u8 |= (spzr_reg->mp ? (1 << REG_MP_BIT_N) : 0);
    /* Set System Image GUID to system_image_guid specified.
     *  System_image_guid and sig must be the same for all ports.*/
    tmp_val_u8 |= (spzr_reg->sig ? (1 << REG_SIG_BIT_N) : 0);
    /* Set node GUID to node_guid specified.
     *  node_guid and ng must be the same for all ports.*/
    tmp_val_u8 |= (spzr_reg->ng ? (1 << REG_NG_BIT_N) : 0);
    /* Set port GUID0 to GUID0 specified */
    tmp_val_u8 |= (spzr_reg->g0 ? (1 << REG_G0_BIT_N) : 0);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_NDM_OFFSET);

    tmp_val_u8 = 0;
    /* When set, it enables Enhanced Switch
     * Port 0. Reported in NodeInfo. Otherwise,
     * Enhanced Switch Port 0 is disabled. */
    tmp_val_u8 |= (spzr_reg->EnhSwP0 ? (1 << REG_ENH_SW_P0_BIT_N) : 0);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_ENH_SW_P0_OFFSET);
    if (spzr_reg->cm) {
        /* Sets the PortInfoCapabilityMask:
         *  Specifies the supported capabilities of this node.
         *  A bit set to 1 for affirmation of supported capability.*/
        SX_PUT_REG_FIELD(inbox, spzr_reg->capability_mask, REG_CAP_MASK_OFFSET);
    }
    if (spzr_reg->sig) {
        /* System Image GUID, takes effect only if
         * the sig bit is set. Must be the same for
         * both ports.*/
        SX_PUT_REG_FIELD(inbox, spzr_reg->system_image_guid_h_l, REG_SYS_IMG_GUID_H_OFFSET);
    }
    if (spzr_reg->g0) {
        /*EUI-64 GUID assigned by the manufacturer,
        * takes effect only if the g0 bit is set */
        SX_PUT_REG_FIELD(inbox, spzr_reg->guid0_h_l, REG_GUID0_H_OFFSET);
    }
    if (spzr_reg->ng) {
        /* Node GUID, takes effect only if the ng bit is set
         * Must be the same for both ports.*/
        SX_PUT_REG_FIELD(inbox, spzr_reg->node_guid_h_l, REG_NODE_GUID_H_OFFSET);
    }
    if (spzr_reg->vk) {
        /* The internal GSA V_Key. Incoming VendorSpecific MADs must
         * have a V_Key matching the one set by this command. If not
         * specified, then must be set to 0. 32 V_Key_l Takes effect
         * only if the VK bit is set
         */
        SX_PUT_REG_FIELD(inbox, spzr_reg->v_key_h, REG_V_KEY_H_OFFSET);
        SX_PUT_REG_FIELD(inbox, spzr_reg->v_key_l, REG_V_KEY_L_OFFSET);
    }
    if (spzr_reg->mp) {
        /* max_pkey is derived from the profile - no set.
         * Maximum pkeys for the port.
         * Must be the same for both ports.
         * Takes effect if the mp bit is set */
        SX_PUT_REG_FIELD(inbox, spzr_reg->max_pkey, REG_MAX_PKEY_OFFSET);
    }
    if (spzr_reg->ndm) {
        /* Text string that describes the node */
        for (i = 0; i < 64; i++) {
            SX_PUT_REG_FIELD(inbox, spzr_reg->NodeDescription[i], REG_NODE_DESC_OFFSET + i);
        }
    }

    return 0;
}

static int __SPZR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_spzr_reg *spzr_reg = (struct ku_spzr_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;
    int                 i;

    SX_GET_REG_FIELD(spzr_reg->swid, outbox, REG_SWID_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_NDM_OFFSET);
    spzr_reg->ndm = tmp_val_u8 & (1 << REG_NDM_BIT_N) ? 1 : 0;
    spzr_reg->EnhSwP0_mask = tmp_val_u8 & (1 << REG_ENH_SW_P0_MASK_BIT_N) ? 1 : 0;
    spzr_reg->cm = tmp_val_u8 & (1 << REG_CM_BIT_N) ? 1 : 0;
    spzr_reg->vk = tmp_val_u8 & (1 << REG_VK_BIT_N) ? 1 : 0;
    spzr_reg->mp = tmp_val_u8 & (1 << REG_MP_BIT_N) ? 1 : 0;
    spzr_reg->sig = tmp_val_u8 & (1 << REG_SIG_BIT_N) ? 1 : 0;
    spzr_reg->ng = tmp_val_u8 & (1 << REG_NG_BIT_N) ? 1 : 0;
    spzr_reg->g0 = tmp_val_u8 & (1 << REG_G0_BIT_N) ? 1 : 0;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_ENH_SW_P0_OFFSET);
    spzr_reg->EnhSwP0 = tmp_val_u8 & (1 << REG_ENH_SW_P0_BIT_N) ? 1 : 0;

    SX_GET_REG_FIELD(spzr_reg->capability_mask, outbox, REG_CAP_MASK_OFFSET);
    SX_GET_REG_FIELD(spzr_reg->system_image_guid_h_l, outbox, REG_SYS_IMG_GUID_H_OFFSET);
    SX_GET_REG_FIELD(spzr_reg->guid0_h_l, outbox, REG_GUID0_H_OFFSET);
    SX_GET_REG_FIELD(spzr_reg->node_guid_h_l, outbox, REG_NODE_GUID_H_OFFSET);
    SX_GET_REG_FIELD(spzr_reg->v_key_h, outbox, REG_V_KEY_H_OFFSET);
    SX_GET_REG_FIELD(spzr_reg->v_key_l, outbox, REG_V_KEY_L_OFFSET);
    SX_GET_REG_FIELD(spzr_reg->max_pkey, outbox, REG_MAX_PKEY_OFFSET);
    for (i = 0; i < 64; i++) {
        SX_GET_REG_FIELD(spzr_reg->NodeDescription[i], outbox, REG_NODE_DESC_OFFSET + i);
    }

    return 0;
}

int sx_ACCESS_REG_SPZR(struct sx_dev *dev, struct ku_access_spzr_reg *reg_data)
{
    if (is_sgmii_supported()) {
        /* SPZR is called in bootstrap and when working with OOB, we don't have PCI to work with, only I2C.
         * The problem is that I2C is enabled only on one management board. We must call this register from both
         * management boards and the only way to do that is with SGMII.
         */
        return sgmii_emad_access_spzr(reg_data->dev_id, &reg_data->spzr_reg);
    }

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SPZR_encode,
                                  __SPZR_decode,
                                  SPZR_REG_LEN,
                                  &reg_data->spzr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SPZR);


/************************************************
 * MJTAG
 ***********************************************/
#define MJTAG_REG_CMD_OFFSET               0x14
#define MJTAG_REG_CMD_BIT_N                6
#define MJTAG_REG_SEQ_NUM_BIT_N            0x0f
#define MJTAG_REG_SEQ_NUM_OFFSET           0x14
#define MJTAG_REG_TRANSACTIONS_SIZE_OFFSET 0x17
#define MJTAG_REG_JTAG_TRANSACTION_OFFSET  0x18
#define MJTAG_REG_TRANSACTION_TDO_BIT_N    0x03
#define MJTAG_REG_TRANSACTION_TDI_BIT_N    0x01
#define MJTAG_REG_LEN                      0x0c

static int __MJTAG_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mjtag_reg *mjtag_reg = (struct ku_mjtag_reg*)ku_reg;
    u8                   tmp_val_u8 = 0;
    int                  counter;

    tmp_val_u8 |= mjtag_reg->cmd << MJTAG_REG_CMD_BIT_N;
    tmp_val_u8 |= mjtag_reg->seq_num;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, MJTAG_REG_CMD_OFFSET);
    SX_PUT_REG_FIELD(inbox, mjtag_reg->size, MJTAG_REG_TRANSACTIONS_SIZE_OFFSET);

    for (counter = 0; counter < mjtag_reg->size; counter++) {
        tmp_val_u8 = 0;
        tmp_val_u8 |= (mjtag_reg->jtag_transaction_sets[counter].tdo & 0x01) << MJTAG_REG_TRANSACTION_TDO_BIT_N;
        tmp_val_u8 |= (mjtag_reg->jtag_transaction_sets[counter].tdi & 0x01) << MJTAG_REG_TRANSACTION_TDI_BIT_N;
        tmp_val_u8 |= (mjtag_reg->jtag_transaction_sets[counter].tms & 0x01);
        SX_PUT_REG_FIELD(inbox, tmp_val_u8, MJTAG_REG_JTAG_TRANSACTION_OFFSET + counter);
    }

    return 0;
}

static int __MJTAG_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mjtag_reg *mjtag_reg = (struct ku_mjtag_reg*)ku_reg;
    u8                   tmp_val_u8 = 0;
    int                  counter;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, MJTAG_REG_CMD_OFFSET);
    mjtag_reg->cmd = tmp_val_u8 & (1 << MJTAG_REG_CMD_BIT_N) ? 1 : 0;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, MJTAG_REG_SEQ_NUM_OFFSET);
    mjtag_reg->seq_num = tmp_val_u8 & MJTAG_REG_SEQ_NUM_BIT_N ? 1 : 0;
    SX_GET_REG_FIELD(mjtag_reg->size, outbox, MJTAG_REG_TRANSACTIONS_SIZE_OFFSET);

    for (counter = 0; counter < mjtag_reg->size; counter++) {
        SX_GET_REG_FIELD(tmp_val_u8, outbox, MJTAG_REG_JTAG_TRANSACTION_OFFSET);
        mjtag_reg->jtag_transaction_sets[counter].tdi = tmp_val_u8 & (1 << MJTAG_REG_TRANSACTION_TDI_BIT_N) ? 1 : 0;
        mjtag_reg->jtag_transaction_sets[counter].tdo = tmp_val_u8 & (1 << MJTAG_REG_TRANSACTION_TDO_BIT_N) ? 1 : 0;
        mjtag_reg->jtag_transaction_sets[counter].tms = tmp_val_u8 & 1 ? 1 : 0;
    }

    return 0;
}

int sx_ACCESS_REG_MJTAG(struct sx_dev *dev, struct ku_access_mjtag_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MJTAG_encode,
                                  __MJTAG_decode,
                                  MJTAG_REG_LEN,
                                  &reg_data->mjtag_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MJTAG);


/************************************************
 * PPSC
 ***********************************************/
#define PPSC_REG_LOCAL_PORT_OFFSET     0x15
#define PPSC_REG_LOCAL_PORT_N          0x08
#define PPSC_REG_WRPS_ADMIN_OFFSET     0x27
#define PPSC_REG_WRPS_ADMIN_N          0x04
#define PPSC_REG_WRPS_STATUS_OFFSET    0x2B
#define PPSC_REG_WRPS_STATUS_N         0x04
#define PPSC_REG_UP_THRESHOLD_OFFSET   0x2D
#define PPSC_REG_UP_THRESHOLD_N        0x08
#define PPSC_REG_DOWN_THRESHOLD_OFFSET 0x2D
#define PPSC_REG_DOWN_THRESHOLD_N      0x08
#define PPSC_REG_SRPS_ADMIN_OFFSET     0x35
#define PPSC_REG_SRPS_ADMIN_N          0x04
#define PPSC_REG_SRPS_STATUS_OFFSET    0x39
#define PPSC_REG_SRPS_STATUS_N         0x04
#define PPSC_REG_LEN                   0x0D

static int __PPSC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppsc_reg *ppsc_reg = (struct ku_ppsc_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, ppsc_reg->local_port, PPSC_REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppsc_reg->wrps_admin, PPSC_REG_WRPS_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppsc_reg->wrps_status, PPSC_REG_WRPS_STATUS_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppsc_reg->up_threshold, PPSC_REG_UP_THRESHOLD_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppsc_reg->down_threshold, PPSC_REG_DOWN_THRESHOLD_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppsc_reg->srps_admin, PPSC_REG_SRPS_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppsc_reg->srps_status, PPSC_REG_SRPS_STATUS_OFFSET);
    return 0;
}

static int __PPSC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppsc_reg *ppsc_reg = (struct ku_ppsc_reg*)ku_reg;

    SX_GET_REG_FIELD(ppsc_reg->local_port, outbox, PPSC_REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(ppsc_reg->wrps_admin, outbox, PPSC_REG_WRPS_ADMIN_OFFSET);
    SX_GET_REG_FIELD(ppsc_reg->wrps_status, outbox, PPSC_REG_WRPS_STATUS_OFFSET);
    SX_GET_REG_FIELD(ppsc_reg->up_threshold, outbox, PPSC_REG_UP_THRESHOLD_OFFSET);
    SX_GET_REG_FIELD(ppsc_reg->down_threshold, outbox, PPSC_REG_DOWN_THRESHOLD_OFFSET);
    SX_GET_REG_FIELD(ppsc_reg->srps_admin, outbox, PPSC_REG_SRPS_ADMIN_OFFSET);
    SX_GET_REG_FIELD(ppsc_reg->srps_status, outbox, PPSC_REG_SRPS_STATUS_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PPSC(struct sx_dev *dev, struct ku_access_ppsc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPSC_encode,
                                  __PPSC_decode,
                                  PPSC_REG_LEN,
                                  &reg_data->ppsc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPSC);


/************************************************
 * PCNR
 ***********************************************/
#define REG_TUNING_OFFSET     0x17
#define REG_LOCAL_PORT_OFFSET 0x15
#define PCNR_REG_LEN          0x04

static int __PCNR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pcnr_reg *pcnr_reg = (struct ku_pcnr_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, pcnr_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pcnr_reg->tuning_override, REG_TUNING_OFFSET);
    return 0;
}

static int __PCNR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pcnr_reg *pcnr_reg = (struct ku_pcnr_reg*)ku_reg;

    SX_GET_REG_FIELD(pcnr_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pcnr_reg->tuning_override, outbox, REG_TUNING_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PCNR(struct sx_dev *dev, struct ku_access_pcnr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PCNR_encode,
                                  __PCNR_decode,
                                  PCNR_REG_LEN,
                                  &reg_data->pcnr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PCNR);


/************************************************
 * PPLM
 ***********************************************/
#define REG_LOCAL_PORT_OFFSET            0x15
#define REG_PORT_PROFILE_MODE_OFFSET     0x1C
#define REG_STATIC_PORT_PROFILE_OFFSET   0x1D
#define REG_ACTIVE_PORT_PROFILE_OFFSET   0x1E
#define REG_RETRANSMISSION_ACTIVE_OFFSET 0x20
#define PPLM_REG_LEN                     0x06

static int __PPLM_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pplm_reg *pplm_reg = (struct ku_pplm_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, pplm_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pplm_reg->port_profile_mode, REG_PORT_PROFILE_MODE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pplm_reg->static_port_profile, REG_STATIC_PORT_PROFILE_OFFSET);
    return 0;
}

static int __PPLM_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pplm_reg *pplm_reg = (struct ku_pplm_reg*)ku_reg;
    u32                 retransmission_active_and_fec_mode_active;

    SX_GET_REG_FIELD(pplm_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pplm_reg->port_profile_mode, outbox, REG_PORT_PROFILE_MODE_OFFSET);
    SX_GET_REG_FIELD(pplm_reg->static_port_profile, outbox, REG_STATIC_PORT_PROFILE_OFFSET);
    SX_GET_REG_FIELD(pplm_reg->active_port_profile, outbox, REG_ACTIVE_PORT_PROFILE_OFFSET);
    SX_GET_REG_FIELD(retransmission_active_and_fec_mode_active, outbox, REG_RETRANSMISSION_ACTIVE_OFFSET);
    pplm_reg->retransmission_active = (retransmission_active_and_fec_mode_active >> 24) & 0xFF;
    pplm_reg->fec_mode_active = retransmission_active_and_fec_mode_active & 0xFFFFFF;
    return 0;
}

int sx_ACCESS_REG_PPLM(struct sx_dev *dev, struct ku_access_pplm_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPLM_encode,
                                  __PPLM_decode,
                                  PPLM_REG_LEN,
                                  &reg_data->pplm_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPLM);


/************************************************
 * PLPC
 ***********************************************/
#define REG_PROFILE_ID_OFFSET                   0x14
#define REG_PLPC_PROTO_MASK_OFFSET              0x16
#define REG_LANE_SPEED_OFFSET                   0x1A
#define REG_LPBF_OFFSET                         0x1E
#define REG_FEC_MODE_POLICY_OFFSET              0x1F
#define REG_RETRANSMISSION_CAPABILITY_OFFSET    0x20
#define REG_FEC_MODE_CAPABILITY_OFFSET          0x21
#define REG_RETRANSMISSION_SUPPORT_ADMIN_OFFSET 0x24
#define REG_FEC_MODE_SUPPORT_ADMIN_OFFSET       0x25
#define REG_RETRANSMISSION_REQUEST_ADMIN_OFFSET 0x28
#define REG_FEC_MODE_REQUEST_ADMIN_OFFSET       0x29
#define PLPC_REG_LEN                            0xB

static int __PLPC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_plpc_reg *plpc_reg = (struct ku_plpc_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, plpc_reg->profile_id, REG_PROFILE_ID_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->proto_mask, REG_PLPC_PROTO_MASK_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->lane_speed, REG_LANE_SPEED_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->lpbf, REG_LPBF_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->fec_mode_policy, REG_FEC_MODE_POLICY_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->retransmission_capability, REG_RETRANSMISSION_CAPABILITY_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->fec_mode_capability, REG_FEC_MODE_CAPABILITY_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->retransmission_support_admin, REG_RETRANSMISSION_SUPPORT_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->fec_mode_support_admin, REG_FEC_MODE_SUPPORT_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->retransmission_request_admin, REG_RETRANSMISSION_REQUEST_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, plpc_reg->fec_mode_request_admin, REG_FEC_MODE_REQUEST_ADMIN_OFFSET);
    return 0;
}

static int __PLPC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_plpc_reg *plpc_reg = (struct ku_plpc_reg*)ku_reg;

    SX_GET_REG_FIELD(plpc_reg->profile_id, outbox, REG_PROFILE_ID_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->proto_mask, outbox, REG_PROTO_MASK_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->lane_speed, outbox, REG_LANE_SPEED_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->lpbf, outbox, REG_LPBF_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->fec_mode_policy, outbox, REG_FEC_MODE_POLICY_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->retransmission_capability, outbox, REG_RETRANSMISSION_CAPABILITY_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->fec_mode_capability, outbox, REG_FEC_MODE_CAPABILITY_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->retransmission_support_admin, outbox, REG_RETRANSMISSION_SUPPORT_ADMIN_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->fec_mode_support_admin, outbox, REG_FEC_MODE_SUPPORT_ADMIN_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->retransmission_request_admin, outbox, REG_RETRANSMISSION_REQUEST_ADMIN_OFFSET);
    SX_GET_REG_FIELD(plpc_reg->fec_mode_request_admin, outbox, REG_FEC_MODE_REQUEST_ADMIN_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PLPC(struct sx_dev *dev, struct ku_access_plpc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PLPC_encode,
                                  __PLPC_decode,
                                  PLPC_REG_LEN,
                                  &reg_data->plpc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PLPC);


/************************************************
 * PMPC
 ***********************************************/
#define REG_MODULE_STATE_UPDATED_OFFSET 0x14
#define PMPC_REG_LEN                    0x09

static int __PMPC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmpc_reg *pmpc_reg = (struct ku_pmpc_reg*)ku_reg;
    int                 i;

    for (i = 0; i < 8; i++) {
        SX_PUT_REG_FIELD(inbox, pmpc_reg->module_state_updated_bitmap[i], REG_MODULE_STATE_UPDATED_OFFSET + (i * 4));
    }

    return 0;
}

static int __PMPC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmpc_reg *pmpc_reg = (struct ku_pmpc_reg*)ku_reg;
    int                 i;

    for (i = 0; i < 8; i++) {
        SX_GET_REG_FIELD(pmpc_reg->module_state_updated_bitmap[i], outbox, REG_MODULE_STATE_UPDATED_OFFSET + (i * 4));
    }

    return 0;
}

int sx_ACCESS_REG_PMPC(struct sx_dev *dev, struct ku_access_pmpc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMPC_encode,
                                  __PMPC_decode,
                                  PMPC_REG_LEN,
                                  &reg_data->pmpc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMPC);


/************************************************
 * PMPR
 ***********************************************/
#define PMPR_REG_MODULE_OFFSET          0x15
#define PMPR_REG_ATTENUATION_5G_OFFSET  0x1B
#define PMPR_REG_ATTENUATION_7G_OFFSET  0x1F
#define PMPR_REG_ATTENUATION_12G_OFFSET 0x23
#define PMPR_REG_LEN                    0x05

static int __PMPR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmpr_reg *pmpr_reg = (struct ku_pmpr_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, pmpr_reg->module, PMPR_REG_MODULE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmpr_reg->attenuation5g, PMPR_REG_ATTENUATION_5G_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmpr_reg->attenuation7g, PMPR_REG_ATTENUATION_7G_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmpr_reg->attenuation12g, PMPR_REG_ATTENUATION_12G_OFFSET);
    return 0;
}

static int __PMPR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmpr_reg *pmpr_reg = (struct ku_pmpr_reg*)ku_reg;

    SX_GET_REG_FIELD(pmpr_reg->module, outbox, PMPR_REG_MODULE_OFFSET);
    SX_GET_REG_FIELD(pmpr_reg->attenuation5g, outbox, PMPR_REG_ATTENUATION_5G_OFFSET);
    SX_GET_REG_FIELD(pmpr_reg->attenuation7g, outbox, PMPR_REG_ATTENUATION_7G_OFFSET);
    SX_GET_REG_FIELD(pmpr_reg->attenuation12g, outbox, PMPR_REG_ATTENUATION_12G_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PMPR(struct sx_dev *dev, struct ku_access_pmpr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMPR_encode,
                                  __PMPR_decode,
                                  PMPR_REG_LEN,
                                  &reg_data->pmpr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMPR);


/************************************************
 * PMAOS
 ***********************************************/
#define REG_MODULE_OFFSET       0x15
#define PMAOS_REG_LEN           0x05
#define PMAOS_ERROR_TYPE_OFFSET 0x1A
#define PMAOS_RST_OFFSET        0x14
#define PMAOS_RST_BIT_N         7
#define REG_ADMIN_STATUS_OFFSET 0x16
#define REG_OPER_STATUS_OFFSET  0x17
#define REG_ASE_OFFSET          0x18
#define REG_ASE_BIT_N           7
#define REG_EE_BIT_N            6
#define REG_E_OFFSET            0x1B

static int __PMAOS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmaos_reg *pmaos_reg = (struct ku_pmaos_reg*)ku_reg;
    u8                   tmp_val_u8 = 0;

    tmp_val_u8 |= pmaos_reg->rst ? (1 << PMAOS_RST_BIT_N) : 0;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, PMAOS_RST_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmaos_reg->module, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmaos_reg->admin_status, REG_ADMIN_STATUS_OFFSET);

    tmp_val_u8 = 0;
    tmp_val_u8 |= pmaos_reg->ase ? (1 << REG_ASE_BIT_N) : 0;
    tmp_val_u8 |= pmaos_reg->ee ? (1 << REG_EE_BIT_N) : 0;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_ASE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmaos_reg->e, REG_E_OFFSET);
    return 0;
}

static int __PMAOS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmaos_reg *pmaos_reg = (struct ku_pmaos_reg*)ku_reg;
    u8                   tmp_val_u8;

    SX_GET_REG_FIELD(pmaos_reg->module, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pmaos_reg->admin_status, outbox, REG_ADMIN_STATUS_OFFSET);
    SX_GET_REG_FIELD(pmaos_reg->oper_status, outbox, REG_OPER_STATUS_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_ASE_OFFSET);
    pmaos_reg->ase = tmp_val_u8 & (1 << REG_ASE_BIT_N) ? 1 : 0;
    pmaos_reg->ee = tmp_val_u8 & (1 << REG_EE_BIT_N) ? 1 : 0;
    SX_GET_REG_FIELD(pmaos_reg->error_type, outbox, PMAOS_ERROR_TYPE_OFFSET);
    SX_GET_REG_FIELD(pmaos_reg->e, outbox, REG_E_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PMAOS(struct sx_dev *dev, struct ku_access_pmaos_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMAOS_encode,
                                  __PMAOS_decode,
                                  PMAOS_REG_LEN,
                                  &reg_data->pmaos_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMAOS);


/************************************************
 * PMTU
 ***********************************************/
#define REG_LOCAL_PORT_OFFSET 0x15
#define REG_MAX_MTU_OFFSET    0x18
#define REG_ADMIN_MTU_OFFSET  0x1c
#define REG_OPER_MTU_OFFSET   0x20
#define PMTU_REG_LEN          0x05

static int __PMTU_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmtu_reg *pmtu_reg = (struct ku_pmtu_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, pmtu_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmtu_reg->max_mtu, REG_MAX_MTU_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmtu_reg->admin_mtu, REG_ADMIN_MTU_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmtu_reg->oper_mtu, REG_OPER_MTU_OFFSET);
    return 0;
}

static int __PMTU_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmtu_reg *pmtu_reg = (struct ku_pmtu_reg*)ku_reg;

    SX_GET_REG_FIELD(pmtu_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pmtu_reg->max_mtu, outbox, REG_MAX_MTU_OFFSET);
    SX_GET_REG_FIELD(pmtu_reg->admin_mtu, outbox, REG_ADMIN_MTU_OFFSET);
    SX_GET_REG_FIELD(pmtu_reg->oper_mtu, outbox, REG_OPER_MTU_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PMTU(struct sx_dev *dev, struct ku_access_pmtu_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMTU_encode,
                                  __PMTU_decode,
                                  PMTU_REG_LEN,
                                  &reg_data->pmtu_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMTU);


/************************************************
 * PELC
 ***********************************************/
#define REG_PELC_OP_OFFSET         0x14
#define REG_PELC_LOCAL_PORT_OFFSET 0x15

/* 0x16, 0x17 reserved not in use */

#define REG_PELC_OP_ADMIN_OFFSET      0x18
#define REG_PELC_OP_CAPABILITY_OFFSET 0x19
#define REG_PELC_OP_REQUEST_OFFSET    0x1a
#define REG_PELC_OP_ACTIVE_OFFSET     0x1b

#define REG_PELC_ADMIN_OFFSET      0x1c
#define REG_PELC_CAPABILITY_OFFSET 0x24
#define REG_PELC_REQUEST_OFFSET    0x2c
#define REG_PELC_ACTIVE_OFFSET     0x34
#define PELC_REG_LEN               0x0b

static int __PELC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pelc_reg *pelc_reg = (struct ku_pelc_reg*)ku_reg;

    pelc_reg->op <<= 4;
    SX_PUT_REG_FIELD(inbox, pelc_reg->op, REG_PELC_OP_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->local_port, REG_PELC_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->op_admin, REG_PELC_OP_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->op_capability, REG_PELC_OP_CAPABILITY_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->op_request, REG_PELC_OP_REQUEST_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->op_active, REG_PELC_OP_ACTIVE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->admin, REG_PELC_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->capability, REG_PELC_CAPABILITY_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->request, REG_PELC_REQUEST_OFFSET);
    SX_PUT_REG_FIELD(inbox, pelc_reg->active, REG_PELC_ACTIVE_OFFSET);
    return 0;
}

static int __PELC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pelc_reg *pelc_reg = (struct ku_pelc_reg*)ku_reg;

    SX_GET_REG_FIELD(pelc_reg->op, outbox, REG_PELC_OP_OFFSET);
    pelc_reg->op >>= 4;
    SX_GET_REG_FIELD(pelc_reg->local_port, outbox, REG_PELC_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->op_admin, outbox, REG_PELC_OP_ADMIN_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->op_capability, outbox, REG_PELC_OP_CAPABILITY_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->op_request, outbox, REG_PELC_OP_REQUEST_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->op_active, outbox, REG_PELC_OP_ACTIVE_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->admin, outbox, REG_PELC_ADMIN_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->capability, outbox, REG_PELC_CAPABILITY_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->request, outbox, REG_PELC_REQUEST_OFFSET);
    SX_GET_REG_FIELD(pelc_reg->active, outbox, REG_PELC_ACTIVE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PELC(struct sx_dev *dev, struct ku_access_pelc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PELC_encode,
                                  __PELC_decode,
                                  PELC_REG_LEN,
                                  &reg_data->pelc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PELC);


/************************************************
 * PVLC
 ***********************************************/
#define REG_LOCAL_PORT_OFFSET     0x15
#define REG_VL_CAP_OFFSET         0x1b
#define REG_VL_ADMIN_OFFSET       0x1f
#define REG_VL_OPERATIONAL_OFFSET 0x23
#define PVLC_REG_LEN              0x05

static int __PVLC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pvlc_reg *pvlc_reg = (struct ku_pvlc_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, pvlc_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pvlc_reg->vl_cap, REG_VL_CAP_OFFSET);
    SX_PUT_REG_FIELD(inbox, pvlc_reg->vl_admin, REG_VL_ADMIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, pvlc_reg->vl_operational, REG_VL_OPERATIONAL_OFFSET);
    return 0;
}

static int __PVLC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pvlc_reg *pvlc_reg = (struct ku_pvlc_reg*)ku_reg;

    SX_GET_REG_FIELD(pvlc_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pvlc_reg->vl_cap, outbox, REG_VL_CAP_OFFSET);
    SX_GET_REG_FIELD(pvlc_reg->vl_admin, outbox, REG_VL_ADMIN_OFFSET);
    SX_GET_REG_FIELD(pvlc_reg->vl_operational, outbox, REG_VL_OPERATIONAL_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PVLC(struct sx_dev *dev, struct ku_access_pvlc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PVLC_encode,
                                  __PVLC_decode,
                                  PVLC_REG_LEN,
                                  &reg_data->pvlc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PVLC);


/************************************************
 * MCIA
 ***********************************************/
#define REG_L_OFFSET                  0x14
#define REG_MODULE_OFFSET             0x15
#define REG_STATUS_OFFSET             0x17
#define REG_I2C_DEVICE_ADDRESS_OFFSET 0x18
#define REG_PAGE_NUMBER_OFFSET        0x19
#define REG_DEVICE_ADDRESS_OFFSET     0x1a
#define REG_SIZE_OFFSET               0x1e
#define REG_DWORD_0_OFFSET            0x24
#define REG_DWORD_1_OFFSET            0x28
#define REG_DWORD_2_OFFSET            0x2c
#define REG_DWORD_3_OFFSET            0x30
#define REG_DWORD_4_OFFSET            0x34
#define REG_DWORD_5_OFFSET            0x38
#define REG_DWORD_6_OFFSET            0x3c
#define REG_DWORD_7_OFFSET            0x40
#define REG_DWORD_8_OFFSET            0x44
#define REG_DWORD_9_OFFSET            0x48
#define REG_DWORD_10_OFFSET           0x4c
#define REG_DWORD_11_OFFSET           0x50
#define MCIA_REG_LEN                  0x11

static int __MCIA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mcia_reg *mcia_reg = (struct ku_mcia_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mcia_reg->l, REG_L_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->module, REG_MODULE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->i2c_device_address, REG_I2C_DEVICE_ADDRESS_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->page_number, REG_PAGE_NUMBER_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->device_address, REG_DEVICE_ADDRESS_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->size, REG_SIZE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_0, REG_DWORD_0_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_1, REG_DWORD_1_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_2, REG_DWORD_2_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_3, REG_DWORD_3_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_4, REG_DWORD_4_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_5, REG_DWORD_5_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_6, REG_DWORD_6_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_7, REG_DWORD_7_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_8, REG_DWORD_8_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_9, REG_DWORD_9_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_10, REG_DWORD_10_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->dword_11, REG_DWORD_11_OFFSET);
    return 0;
}

static int __MCIA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mcia_reg *mcia_reg = (struct ku_mcia_reg*)ku_reg;

    SX_GET_REG_FIELD(mcia_reg->l, outbox, REG_L_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->module, outbox, REG_MODULE_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->status, outbox, REG_STATUS_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->i2c_device_address, outbox, REG_I2C_DEVICE_ADDRESS_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->page_number, outbox, REG_PAGE_NUMBER_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->device_address, outbox, REG_DEVICE_ADDRESS_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->size, outbox, REG_SIZE_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_0, outbox, REG_DWORD_0_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_1, outbox, REG_DWORD_1_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_2, outbox, REG_DWORD_2_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_3, outbox, REG_DWORD_3_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_4, outbox, REG_DWORD_4_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_5, outbox, REG_DWORD_5_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_6, outbox, REG_DWORD_6_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_7, outbox, REG_DWORD_7_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_8, outbox, REG_DWORD_8_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_9, outbox, REG_DWORD_9_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_10, outbox, REG_DWORD_10_OFFSET);
    SX_GET_REG_FIELD(mcia_reg->dword_11, outbox, REG_DWORD_11_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MCIA(struct sx_dev *dev, struct ku_access_mcia_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MCIA_encode,
                                  __MCIA_decode,
                                  MCIA_REG_LEN,
                                  &reg_data->mcia_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MCIA);


/************************************************
 * HPKT
 ***********************************************/
#define REG_ACK_BITN         24
#define REG_ACTION_BITN      20
#define REG_TRAP_GROUP_BITN  12
#define REG_TRAP_INFO_OFFSET 0x14
#define REG_HPKT_CTRL_OFFSET 0x19
#define HPKT_REG_LEN         0x05

static int __HPKT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_hpkt_reg *hpkt_reg = (struct ku_hpkt_reg*)ku_reg;
    u32                 trap_info;

    trap_info = ((u32)(hpkt_reg->ack) & 0x1) << REG_ACK_BITN;
    trap_info |= ((u32)(hpkt_reg->action) & 0xF) << REG_ACTION_BITN;
    trap_info |= ((u32)(hpkt_reg->trap_group) & 0x3f) << REG_TRAP_GROUP_BITN;
    trap_info |= (u32)(hpkt_reg->trap_id) & 0x1FF;
    SX_PUT_REG_FIELD(inbox, trap_info, REG_TRAP_INFO_OFFSET);
    SX_PUT_REG_FIELD(inbox, hpkt_reg->control, REG_HPKT_CTRL_OFFSET);
    return 0;
}

static int __HPKT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_hpkt_reg *hpkt_reg = (struct ku_hpkt_reg*)ku_reg;
    u32                 trap_info;

    SX_GET_REG_FIELD(trap_info, outbox, REG_TRAP_INFO_OFFSET);
    hpkt_reg->ack = (trap_info >> REG_ACK_BITN) & 0x1;
    hpkt_reg->action = (trap_info >> REG_ACTION_BITN) & 0xF;
    hpkt_reg->trap_group = (trap_info >> REG_TRAP_GROUP_BITN) & 0x3F;
    hpkt_reg->trap_id = trap_info & 0x1FF;
    SX_GET_REG_FIELD(hpkt_reg->control, outbox, REG_HPKT_CTRL_OFFSET);
    return 0;
}

int sx_ACCESS_REG_HPKT(struct sx_dev *dev, struct ku_access_hpkt_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __HPKT_encode,
                                  __HPKT_decode,
                                  HPKT_REG_LEN,
                                  &reg_data->hpkt_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_HPKT);


/************************************************
 * HCAP
 ***********************************************/
#define REG_MAX_CPU_EGRESS_TCS_OFFSET  0x1b
#define REG_MAX_CPU_INGRESS_TCS_OFFSET 0x1f
#define REG_MAX_TRAP_GROUPS_OFFSET     0x23
#define REG_DR_PATHS_OFFSET            0x27
#define HCAP_REG_LEN                   0x09

static int __HCAP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_hcap_reg *hcap_reg = (struct ku_hcap_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, hcap_reg->max_cpu_egress_tclass, REG_MAX_CPU_EGRESS_TCS_OFFSET);
    SX_PUT_REG_FIELD(inbox, hcap_reg->max_cpu_ingress_tclass, REG_MAX_CPU_INGRESS_TCS_OFFSET);
    SX_PUT_REG_FIELD(inbox, hcap_reg->max_num_trap_groups, REG_MAX_TRAP_GROUPS_OFFSET);
    SX_PUT_REG_FIELD(inbox, hcap_reg->max_num_dr_paths, REG_DR_PATHS_OFFSET);
    return 0;
}

static int __HCAP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_hcap_reg *hcap_reg = (struct ku_hcap_reg*)ku_reg;

    SX_GET_REG_FIELD(hcap_reg->max_cpu_egress_tclass, outbox, REG_MAX_CPU_EGRESS_TCS_OFFSET);
    SX_GET_REG_FIELD(hcap_reg->max_cpu_ingress_tclass, outbox, REG_MAX_CPU_INGRESS_TCS_OFFSET);
    SX_GET_REG_FIELD(hcap_reg->max_num_trap_groups, outbox, REG_MAX_TRAP_GROUPS_OFFSET);
    SX_GET_REG_FIELD(hcap_reg->max_num_dr_paths, outbox, REG_DR_PATHS_OFFSET);
    return 0;
}

int sx_ACCESS_REG_HCAP(struct sx_dev *dev, struct ku_access_hcap_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __HCAP_encode,
                                  __HCAP_decode,
                                  HCAP_REG_LEN,
                                  &reg_data->hcap_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_HCAP);


/************************************************
 * MFSC
 ***********************************************/
#define REG_FAN_OFFSET 0x14
#define REG_PWM_OFFSET 0x1b
#define MFSC_REG_LEN   0x3

static int __MFSC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfsc_reg *mfsc_reg = (struct ku_mfsc_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mfsc_reg->pwm, REG_FAN_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfsc_reg->pwm_duty_cycle, REG_PWM_OFFSET);
    return 0;
}

static int __MFSC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfsc_reg *mfsc_reg = (struct ku_mfsc_reg*)ku_reg;

    SX_GET_REG_FIELD(mfsc_reg->pwm, outbox, REG_FAN_OFFSET);
    SX_GET_REG_FIELD(mfsc_reg->pwm_duty_cycle, outbox, REG_PWM_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MFSC(struct sx_dev *dev, struct ku_access_mfsc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFSC_encode,
                                  __MFSC_decode,
                                  MFSC_REG_LEN,
                                  &reg_data->mfsc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFSC);


/************************************************
 * MFSM
 ***********************************************/
#define REG_TACHO_OFFSET 0x14
#define REG_N_OFFSET     0x17
#define REG_RPM_OFFSET   0x1a
#define MFSM_REG_LEN     0x3

static int __MFSM_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfsm_reg *mfsm_reg = (struct ku_mfsm_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mfsm_reg->tacho, REG_TACHO_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfsm_reg->n, REG_N_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfsm_reg->rpm, REG_RPM_OFFSET);
    return 0;
}

static int __MFSM_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfsm_reg *mfsm_reg = (struct ku_mfsm_reg*)ku_reg;

    SX_GET_REG_FIELD(mfsm_reg->tacho, outbox, REG_TACHO_OFFSET);
    SX_GET_REG_FIELD(mfsm_reg->n, outbox, REG_N_OFFSET);
    SX_GET_REG_FIELD(mfsm_reg->rpm, outbox, REG_RPM_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MFSM(struct sx_dev *dev, struct ku_access_mfsm_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFSM_encode,
                                  __MFSM_decode,
                                  MFSM_REG_LEN,
                                  &reg_data->mfsm_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFSM);


/************************************************
 * MFSL
 ***********************************************/
#define REG_FAN_OFFSET      0x14
#define REG_EE_SHIFT        2
#define REG_FLAGS_OFFSET    0x17
#define REG_TACH_MIN_OFFSET 0x1a
#define REG_TACH_MAX_OFFSET 0x1e
#define MFSL_REG_LEN        0x3

static int __MFSL_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfsl_reg *mfsl_reg = (struct ku_mfsl_reg*)ku_reg;
    u8                  flags;

    SX_PUT_REG_FIELD(inbox, mfsl_reg->fan, REG_FAN_OFFSET);
    flags = (mfsl_reg->ee << REG_EE_SHIFT);
    flags |= mfsl_reg->ie;
    SX_PUT_REG_FIELD(inbox, flags, REG_FLAGS_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfsl_reg->tach_min, REG_TACH_MIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfsl_reg->tach_max, REG_TACH_MAX_OFFSET);
    return 0;
}

static int __MFSL_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfsl_reg *mfsl_reg = (struct ku_mfsl_reg*)ku_reg;
    u8                  flags;

    SX_GET_REG_FIELD(mfsl_reg->fan, outbox, REG_FAN_OFFSET);
    SX_GET_REG_FIELD(flags, outbox, REG_FLAGS_OFFSET);
    mfsl_reg->ee = (flags >> REG_EE_SHIFT) & 0x3;
    mfsl_reg->ie = flags & 0x1;
    SX_GET_REG_FIELD(mfsl_reg->tach_min, outbox, REG_TACH_MIN_OFFSET);
    SX_GET_REG_FIELD(mfsl_reg->tach_max, outbox, REG_TACH_MAX_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MFSL(struct sx_dev *dev, struct ku_access_mfsl_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFSL_encode,
                                  __MFSL_decode,
                                  MFSL_REG_LEN,
                                  &reg_data->mfsl_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFSL);


/************************************************
 * HDRT
 ***********************************************/
#define REG_DR_INDEX_OFFSET    0x14
#define REG_HOP_CNT_OFFSET     0x16
#define REG_FIRST_PATH_OFFSET  0x18
#define REG_NUM_OF_PATHS       0x40
#define REG_FIRST_RPATH_OFFSET (REG_FIRST_PATH_OFFSET + REG_NUM_OF_PATHS)
#define HDRT_REG_LEN           0x17

static int __HDRT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_hdrt_reg *hdrt_reg = (struct ku_hdrt_reg*)ku_reg;
    int                 i;

    SX_PUT_REG_FIELD(inbox, hdrt_reg->dr_index, REG_DR_INDEX_OFFSET);
    SX_PUT_REG_FIELD(inbox, hdrt_reg->hop_cnt, REG_HOP_CNT_OFFSET);
    for (i = 0; i < REG_NUM_OF_PATHS; i++) {
        SX_PUT_REG_FIELD(inbox, hdrt_reg->path[i], REG_FIRST_PATH_OFFSET + i);
    }

    for (i = 0; i < REG_NUM_OF_PATHS; i++) {
        SX_PUT_REG_FIELD(inbox, hdrt_reg->rpath[i], REG_FIRST_RPATH_OFFSET + i);
    }

    return 0;
}

static int __HDRT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_hdrt_reg *hdrt_reg = (struct ku_hdrt_reg*)ku_reg;
    int                 i;

    SX_GET_REG_FIELD(hdrt_reg->dr_index, outbox, REG_DR_INDEX_OFFSET);
    SX_GET_REG_FIELD(hdrt_reg->hop_cnt, outbox, REG_HOP_CNT_OFFSET);
    for (i = 0; i < REG_NUM_OF_PATHS; i++) {
        SX_GET_REG_FIELD(hdrt_reg->path[i], outbox, REG_FIRST_PATH_OFFSET + i);
    }

    for (i = 0; i < REG_NUM_OF_PATHS; i++) {
        SX_GET_REG_FIELD(hdrt_reg->rpath[i], outbox, REG_FIRST_RPATH_OFFSET + i);
    }

    return 0;
}

int sx_ACCESS_REG_HDRT(struct sx_dev *dev, struct ku_access_hdrt_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __HDRT_encode,
                                  __HDRT_decode,
                                  HDRT_REG_LEN,
                                  &reg_data->hdrt_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_HDRT);


/************************************************
 * MTBR
 ***********************************************/
#define REG_BASE_SENSOR_INDEX_OFFSET 0x16
#define REG_NUM_REC_OFFSET           0x1b
#define REG_TEMP_RECORD_OFFSET       0x24
#define REG_TEMP_IN_REC_OFFSET       0x26

static int __MTBR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtbr_reg *mtbr_reg = (struct ku_mtbr_reg*)ku_reg;
    u16                 tmp_idx;

    tmp_idx = mtbr_reg->base_sensor_index & 0xFFF;
    SX_PUT_REG_FIELD(inbox, tmp_idx, REG_BASE_SENSOR_INDEX_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtbr_reg->num_rec, REG_NUM_REC_OFFSET);
    return 0;
}

static int __MTBR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtbr_reg *mtbr_reg = (struct ku_mtbr_reg*)ku_reg;
    int                 counter;
    u16                 tmp_idx;

    SX_GET_REG_FIELD(tmp_idx, outbox, REG_BASE_SENSOR_INDEX_OFFSET);
    mtbr_reg->base_sensor_index = tmp_idx & 0xFFF;
    SX_GET_REG_FIELD(mtbr_reg->num_rec, outbox, REG_NUM_REC_OFFSET);
    for (counter = 0; counter < mtbr_reg->num_rec; counter++) {
        SX_GET_REG_FIELD(mtbr_reg->temperature_record[counter].max_temperature,
                         outbox,
                         REG_TEMP_RECORD_OFFSET + (counter * sizeof(mtbr_reg->temperature_record[0])));
        SX_GET_REG_FIELD(mtbr_reg->temperature_record[counter].temperature,
                         outbox,
                         REG_TEMP_IN_REC_OFFSET + (counter * sizeof(mtbr_reg->temperature_record[0])));
    }

    return 0;
}

int sx_ACCESS_REG_MTBR(struct sx_dev *dev, struct ku_access_mtbr_reg *reg_data)
{
    u16 mtbr_len;

    if (reg_data->mtbr_reg.num_rec > MTBR_MAX_TEMPERATURE_RECORDS) {
        printk(KERN_ERR PFX "MTBR num_rec %d is greater than max records %d.\n",
               reg_data->mtbr_reg.num_rec, MTBR_MAX_TEMPERATURE_RECORDS);
        return -EINVAL;
    }

    /* records + 5 lines according to PRM */
    mtbr_len = 5 + reg_data->mtbr_reg.num_rec;

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTBR_encode,
                                  __MTBR_decode,
                                  mtbr_len,
                                  &reg_data->mtbr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTBR);


/************************************************
 * MMDIO
 ***********************************************/
#define REG_MDIO_INDEX_OFFSET 0x15
#define REG_OPERATION_OFFSET  0x17
#define REG_ADDRESS_OFFSET    0x18
#define REG_DATA_OFFSET       0x1c
#define MMDIO_REG_LEN         0x4

static int __MMDIO_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mmdio_reg *mmdio_reg = (struct ku_mmdio_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mmdio_reg->mdio_index, REG_MDIO_INDEX_OFFSET);
    SX_PUT_REG_FIELD(inbox, mmdio_reg->operation, REG_OPERATION_OFFSET);
    SX_PUT_REG_FIELD(inbox, mmdio_reg->address, REG_ADDRESS_OFFSET);
    SX_PUT_REG_FIELD(inbox, mmdio_reg->data, REG_DATA_OFFSET);
    return 0;
}

static int __MMDIO_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mmdio_reg *mmdio_reg = (struct ku_mmdio_reg*)ku_reg;

    SX_GET_REG_FIELD(mmdio_reg->mdio_index, outbox, REG_MDIO_INDEX_OFFSET);
    SX_GET_REG_FIELD(mmdio_reg->operation, outbox, REG_OPERATION_OFFSET);
    SX_GET_REG_FIELD(mmdio_reg->address, outbox, REG_ADDRESS_OFFSET);
    SX_GET_REG_FIELD(mmdio_reg->data, outbox, REG_DATA_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MMDIO(struct sx_dev *dev, struct ku_access_mmdio_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MMDIO_encode,
                                  __MMDIO_decode,
                                  MMDIO_REG_LEN,
                                  &reg_data->mmdio_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MMDIO);


/************************************************
 * MMIA
 ***********************************************/
#define REG_OPERATION_OFFSET 0x17
#define REG_DATA_OFFSET      0x1c
#define MMIA_REG_LEN         0x4

static int __MMIA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mmia_reg *mmia_reg = (struct ku_mmia_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mmia_reg->operation, REG_OPERATION_OFFSET);
    SX_PUT_REG_FIELD(inbox, mmia_reg->data, REG_DATA_OFFSET);
    return 0;
}

static int __MMIA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mmia_reg *mmia_reg = (struct ku_mmia_reg*)ku_reg;

    SX_GET_REG_FIELD(mmia_reg->operation, outbox, REG_OPERATION_OFFSET);
    SX_GET_REG_FIELD(mmia_reg->data, outbox, REG_DATA_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MMIA(struct sx_dev *dev, struct ku_access_mmia_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MMIA_encode,
                                  __MMIA_decode,
                                  MMIA_REG_LEN,
                                  &reg_data->mmia_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MMIA);


/************************************************
 * MFPA
 ***********************************************/
#define REG_P_OFFSET                0x16
#define REG_FS_OFFSET               0x17
#define REG_FS_BITS_SHIFT           4
#define REG_BOOT_ADDRESS_OFFSET     0x18
#define REG_FLASH_NUM_OFFSET        0x27
#define REG_JEDEC_ID_OFFSET         0x28
#define REG_BLOCK_ALLIGNMENT_OFFSET 0x2d
#define REG_SECTOR_SIZE_OFFSET      0x2f
#define REG_CAPABILITY_MASK_OFFSET  0x30
#define REG_CAPABILITY_MASK_BIT_N   7
#define MFPA_REG_LEN                0x40

static int __MFPA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfpa_reg *mfpa_reg = (struct ku_mfpa_reg*)ku_reg;
    u8                  flag;

    SX_PUT_REG_FIELD(inbox, mfpa_reg->p, REG_P_OFFSET);
    flag = (u8)(mfpa_reg->fs << REG_FS_BITS_SHIFT);
    SX_PUT_REG_FIELD(inbox, flag, REG_FS_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfpa_reg->boot_address, REG_BOOT_ADDRESS_OFFSET);
    return 0;
}

static int __MFPA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfpa_reg *mfpa_reg = (struct ku_mfpa_reg*)ku_reg;
    u8                  flag;

    SX_GET_REG_FIELD(mfpa_reg->p, outbox, REG_P_OFFSET);
    SX_GET_REG_FIELD(flag, outbox, REG_FS_OFFSET);
    mfpa_reg->fs = (u8)(flag >> REG_FS_BITS_SHIFT);
    SX_GET_REG_FIELD(mfpa_reg->boot_address, outbox, REG_BOOT_ADDRESS_OFFSET);
    SX_GET_REG_FIELD(mfpa_reg->flash_num, outbox, REG_FLASH_NUM_OFFSET);
    SX_GET_REG_FIELD(mfpa_reg->jedec_id, outbox, REG_JEDEC_ID_OFFSET);
    SX_GET_REG_FIELD(mfpa_reg->block_allignment, outbox, REG_BLOCK_ALLIGNMENT_OFFSET);
    SX_GET_REG_FIELD(mfpa_reg->sector_size, outbox, REG_SECTOR_SIZE_OFFSET);
    SX_GET_REG_FIELD(flag, outbox, REG_CAPABILITY_MASK_OFFSET);
    mfpa_reg->capability_mask = (u8)(flag >> REG_CAPABILITY_MASK_BIT_N);
    return 0;
}

int sx_ACCESS_REG_MFPA(struct sx_dev *dev, struct ku_access_mfpa_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFPA_encode,
                                  __MFPA_decode,
                                  MFPA_REG_LEN,
                                  &reg_data->mfpa_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFPA);


/************************************************
 * MFBE
 ***********************************************/
#define REG_P_OFFSET            0x16
#define REG_FS_OFFSET           0x17
#define REG_FS_BITS_SHIFT       4
#define REG_MFBE_ADDRESS_OFFSET 0x1c
#define MFBE_REG_LEN            0x4

static int __MFBE_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfbe_reg *mfbe_reg = (struct ku_mfbe_reg*)ku_reg;
    u8                  flag;

    SX_PUT_REG_FIELD(inbox, mfbe_reg->p, REG_P_OFFSET);
    flag = (u8)(mfbe_reg->fs << REG_FS_BITS_SHIFT);
    SX_PUT_REG_FIELD(inbox, flag, REG_FS_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfbe_reg->address, REG_MFBE_ADDRESS_OFFSET);
    return 0;
}

static int __MFBE_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfbe_reg *mfbe_reg = (struct ku_mfbe_reg*)ku_reg;
    u8                  flag;

    SX_GET_REG_FIELD(mfbe_reg->p, outbox, REG_P_OFFSET);
    SX_GET_REG_FIELD(flag, outbox, REG_FS_OFFSET);
    mfbe_reg->fs = (u8)(flag >> REG_FS_BITS_SHIFT);
    SX_GET_REG_FIELD(mfbe_reg->address, outbox, REG_MFBE_ADDRESS_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MFBE(struct sx_dev *dev, struct ku_access_mfbe_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFBE_encode,
                                  __MFBE_decode,
                                  MFBE_REG_LEN,
                                  &reg_data->mfbe_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFBE);


/************************************************
 * MFBA
 ***********************************************/
#define REG_P_OFFSET            0x16
#define REG_FS_OFFSET           0x17
#define REG_FS_BITS_SHIFT       4
#define REG_MFBA_SIZE_OFFSET    0x1a
#define REG_MFBA_ADDRESS_OFFSET 0x1c
#define REG_MFBA_DATA_OFFSET    0x20
#define MFBA_REG_LEN            0x40

static int __MFBA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfba_reg *mfba_reg = (struct ku_mfba_reg*)ku_reg;
    u8                  flag;
    int                 i;

    SX_PUT_REG_FIELD(inbox, mfba_reg->p, REG_P_OFFSET);
    flag = (u8)(mfba_reg->fs << REG_FS_BITS_SHIFT);
    SX_PUT_REG_FIELD(inbox, flag, REG_FS_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfba_reg->size, REG_MFBA_SIZE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfba_reg->address, REG_MFBA_ADDRESS_OFFSET);
    for (i = 0; i < 192; i++) {
        SX_PUT_REG_FIELD(inbox, mfba_reg->data[i], REG_MFBA_DATA_OFFSET + i);
    }

    return 0;
}

static int __MFBA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfba_reg *mfba_reg = (struct ku_mfba_reg*)ku_reg;
    u8                  flag;
    int                 i;

    SX_GET_REG_FIELD(mfba_reg->p, outbox, REG_P_OFFSET);
    SX_GET_REG_FIELD(flag, outbox, REG_FS_OFFSET);
    mfba_reg->fs = (u8)(flag >> REG_FS_BITS_SHIFT);
    SX_GET_REG_FIELD(mfba_reg->size, outbox, REG_MFBA_SIZE_OFFSET);
    SX_GET_REG_FIELD(mfba_reg->address, outbox, REG_MFBA_ADDRESS_OFFSET);
    for (i = 0; i < 192; i++) {
        SX_GET_REG_FIELD(mfba_reg->data[i], outbox, REG_MFBA_DATA_OFFSET + i);
    }

    return 0;
}

int sx_ACCESS_REG_MFBA(struct sx_dev *dev, struct ku_access_mfba_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFBA_encode,
                                  __MFBA_decode,
                                  MFBA_REG_LEN,
                                  &reg_data->mfba_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFBA);


/************************************************
 * QCAP
 ***********************************************/
#define REG_MAX_POLICER_PER_PORT_OFFSET 0x1f
#define REG_MAX_POLICER_GLOBAL_OFFSET   0x23
#define QCAP_REG_LEN                    0x09

static int __QCAP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_qcap_reg *qcap_reg = (struct ku_qcap_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, qcap_reg->max_policers_per_port, REG_MAX_POLICER_PER_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, qcap_reg->max_policers_global, REG_MAX_POLICER_GLOBAL_OFFSET);
    return 0;
}

static int __QCAP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_qcap_reg *qcap_reg = (struct ku_qcap_reg*)ku_reg;

    SX_GET_REG_FIELD(qcap_reg->max_policers_per_port, outbox, REG_MAX_POLICER_PER_PORT_OFFSET);
    SX_GET_REG_FIELD(qcap_reg->max_policers_global, outbox, REG_MAX_POLICER_GLOBAL_OFFSET);
    return 0;
}

int sx_ACCESS_REG_QCAP(struct sx_dev *dev, struct ku_access_qcap_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __QCAP_encode,
                                  __QCAP_decode,
                                  QCAP_REG_LEN,
                                  &reg_data->qcap_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_QCAP);


/************************************************
 * RAW
 ***********************************************/
#define OP_TLV_SIZE 0x10

static int __RAW_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_raw_reg *raw_reg = (struct ku_raw_reg*)ku_reg;

    return copy_from_user(inbox, raw_reg->buff, raw_reg->size);
}

static int __RAW_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_raw_reg *raw_reg = (struct ku_raw_reg*)ku_reg;

    return copy_to_user(raw_reg->buff, outbox, raw_reg->size);
}

int sx_ACCESS_REG_RAW(struct sx_dev *dev, struct ku_access_raw_reg *reg_data)
{
    u16 reg_len;

    if (SX_MAILBOX_SIZE < OP_TLV_SIZE + reg_data->raw_reg.size) {
        sx_warn(dev, "Cannot send the raw register access request "
                "since the mailbox size %d is too small (need %d)\n",
                SX_MAILBOX_SIZE, OP_TLV_SIZE + reg_data->raw_reg.size);
        return -ENOMEM;
    }

    reg_len = reg_data->raw_reg.size / 4 + 1;

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __RAW_encode,
                                  __RAW_decode,
                                  reg_len,
                                  &reg_data->raw_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_RAW);


/************************************************
 * MTWE
 ***********************************************/
#define REG_SENSOR_WARNING_OFFSET 0x17
#define MTWE_REG_LEN              0x3

static int __MTWE_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtwe_reg *mtwe_reg = (struct ku_mtwe_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mtwe_reg->sensor_warning, REG_SENSOR_WARNING_OFFSET);
    return 0;
}

static int __MTWE_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtwe_reg *mtwe_reg = (struct ku_mtwe_reg*)ku_reg;

    SX_GET_REG_FIELD(mtwe_reg->sensor_warning, outbox, REG_SENSOR_WARNING_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MTWE(struct sx_dev *dev, struct ku_access_mtwe_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTWE_encode,
                                  __MTWE_decode,
                                  MTWE_REG_LEN,
                                  &reg_data->mtwe_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTWE);


/************************************************
 * MTCAP
 ***********************************************/
#define REG_SENSOR_COUNT_OFFSET 0x17
#define MTCAP_REG_LEN           0x3

static int __MTCAP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtcap_reg *mtcap_reg = (struct ku_mtcap_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mtcap_reg->sensor_count, REG_SENSOR_COUNT_OFFSET);
    return 0;
}

static int __MTCAP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtcap_reg *mtcap_reg = (struct ku_mtcap_reg*)ku_reg;

    SX_GET_REG_FIELD(mtcap_reg->sensor_count, outbox, REG_SENSOR_COUNT_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MTCAP(struct sx_dev *dev, struct ku_access_mtcap_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTCAP_encode,
                                  __MTCAP_decode,
                                  MTCAP_REG_LEN,
                                  &reg_data->mtcap_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTCAP);


/************************************************
 * FORE
 ***********************************************/
#define REG_FAN_UNDER_LIMIT_OFFSET 0x14
#define REG_FAN_OVER_LIMIT_OFFSET  0x18
#define FORE_REG_LEN               0x4

static int __FORE_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_fore_reg *fore_reg = (struct ku_fore_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, fore_reg->fan_under_limit, REG_FAN_UNDER_LIMIT_OFFSET);
    SX_PUT_REG_FIELD(inbox, fore_reg->fan_over_limit, REG_FAN_OVER_LIMIT_OFFSET);

    return 0;
}

static int __FORE_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_fore_reg *fore_reg = (struct ku_fore_reg*)ku_reg;

    SX_GET_REG_FIELD(fore_reg->fan_under_limit, outbox, REG_FAN_UNDER_LIMIT_OFFSET);
    SX_GET_REG_FIELD(fore_reg->fan_over_limit, outbox, REG_FAN_OVER_LIMIT_OFFSET);
    return 0;
}

int sx_ACCESS_REG_FORE(struct sx_dev *dev, struct ku_access_fore_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __FORE_encode,
                                  __FORE_decode,
                                  FORE_REG_LEN,
                                  &reg_data->fore_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_FORE);


/************************************************
 * MFCR
 ***********************************************/
#define REG_PWM_FREQ_OFFSET     0x17
#define REG_TACHO_ACTIVE_OFFSET 0x18
#define REG_PWM_ACTIVE_OFFSET   0x1b
#define MFCR_REG_LEN            0x3

static int __MFCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfcr_reg *mfcr_reg = (struct ku_mfcr_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mfcr_reg->pwm_frequency, REG_PWM_FREQ_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfcr_reg->tacho_active, REG_TACHO_ACTIVE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfcr_reg->pwm_active, REG_PWM_ACTIVE_OFFSET);
    return 0;
}

static int __MFCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfcr_reg *mfcr_reg = (struct ku_mfcr_reg*)ku_reg;

    SX_GET_REG_FIELD(mfcr_reg->pwm_frequency, outbox, REG_PWM_FREQ_OFFSET);
    SX_GET_REG_FIELD(mfcr_reg->tacho_active, outbox, REG_TACHO_ACTIVE_OFFSET);
    SX_GET_REG_FIELD(mfcr_reg->pwm_active, outbox, REG_PWM_ACTIVE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MFCR(struct sx_dev *dev, struct ku_access_mfcr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFCR_encode,
                                  __MFCR_decode,
                                  MFCR_REG_LEN,
                                  &reg_data->mfcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFCR);


/************************************************
 * MFM
 ***********************************************/
#define REG_MFM_INDEX_OFFSET   0x17
#define REG_MEMORY_OFFSET      0x1c
#define REG_MEMORY_MASK_OFFSET 0x24
#define MFM_REG_LEN            0x7

static int __MFM_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfm_reg *mfm_reg = (struct ku_mfm_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mfm_reg->index, REG_MFM_INDEX_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfm_reg->memory, REG_MEMORY_OFFSET);
    SX_PUT_REG_FIELD(inbox, mfm_reg->memory_mask, REG_MEMORY_MASK_OFFSET);
    return 0;
}

static int __MFM_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfm_reg *mfm_reg = (struct ku_mfm_reg*)ku_reg;

    SX_GET_REG_FIELD(mfm_reg->index, outbox, REG_MFM_INDEX_OFFSET);
    SX_GET_REG_FIELD(mfm_reg->memory, outbox, REG_MEMORY_OFFSET);
    SX_GET_REG_FIELD(mfm_reg->memory_mask, outbox, REG_MEMORY_MASK_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MFM(struct sx_dev *dev, struct ku_access_mfm_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFM_encode,
                                  __MFM_decode,
                                  MFM_REG_LEN,
                                  &reg_data->mfm_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFM);


/************************************************
 * QPRT
 ***********************************************/
#define REG_LOCAL_PORT_OFFSET 0x15
#define REG_PRIO_OFFSET       0x16
#define REG_RPRIO_OFFSET      0x1b
#define QPRT_REG_LEN          0x3

static int __QPRT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_qprt_reg *qprt_reg = (struct ku_qprt_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, qprt_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, qprt_reg->prio, REG_PRIO_OFFSET);
    SX_PUT_REG_FIELD(inbox, qprt_reg->rprio, REG_RPRIO_OFFSET);
    return 0;
}

static int __QPRT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_qprt_reg *qprt_reg = (struct ku_qprt_reg*)ku_reg;

    SX_GET_REG_FIELD(qprt_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(qprt_reg->prio, outbox, REG_PRIO_OFFSET);
    SX_GET_REG_FIELD(qprt_reg->rprio, outbox, REG_RPRIO_OFFSET);
    return 0;
}

int sx_ACCESS_REG_QPRT(struct sx_dev *dev, struct ku_access_qprt_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __QPRT_encode,
                                  __QPRT_decode,
                                  QPRT_REG_LEN,
                                  &reg_data->qprt_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_QPRT);


/************************************************
 * HTGT
 ***********************************************/
#define REG_HTGT_SWID_OFFSET         0x14
#define REG_HTGT_TYPE_OFFSET         0x16
#define REG_HTGT_GRP_OFFSET          0x17
#define REG_HTGT_PIDE_OFFSET         0x1A
#define REG_HTGT_PID_OFFSET          0x1B
#define REG_HTGT_MRR_ACTION_OFFSET   0x1E
#define REG_HTGT_MRR_AGENT_OFFSET    0x1F
#define REG_HTGT_PRIO_OFFSET         0x23
#define REG_HTGT_PATH_OFFSET         0x24
#define REG_HTGT_LP_CPU_TC_OFFSET    (REG_HTGT_PATH_OFFSET + 1)
#define REG_HTGT_LP_RDQ_OFFSET       (REG_HTGT_PATH_OFFSET + 3)
#define REG_HTGT_SP_STK_TC_OFFSET    (REG_HTGT_PATH_OFFSET + 0)
#define REG_HTGT_SP_CPU_TC_OFFSET    (REG_HTGT_PATH_OFFSET + 1)
#define REG_HTGT_SP_RDQ_OFFSET       (REG_HTGT_PATH_OFFSET + 3)
#define REG_HTGT_SP_SYS_PORT_OFFSET  (REG_HTGT_PATH_OFFSET + 7)
#define REG_HTGT_DRP_DR_PTR_OFFSET   (REG_HTGT_PATH_OFFSET + 3)
#define REG_HTGT_EP_MAC_47_32_OFFSET (REG_HTGT_PATH_OFFSET + 3)
#define REG_HTGT_EP_MAC_31_0_OFFSET  (REG_HTGT_PATH_OFFSET + 7)
#define REG_HTGT_EP_VID_OFFSET       (REG_HTGT_PATH_OFFSET + 0xb)
#define HTGT_REG_LEN                 0x11 /* number of 32-bits words that the register holds */

static int __HTGT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_htgt_reg *htgt_reg = (struct ku_htgt_reg*)ku_reg;
    u16                 mac_47_32;
    u32                 mac_31_0;
    u8                  tmp;

    SX_PUT_REG_FIELD(inbox, htgt_reg->swid, REG_HTGT_SWID_OFFSET);
    SX_PUT_REG_FIELD(inbox, htgt_reg->type, REG_HTGT_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, htgt_reg->trap_group, REG_HTGT_GRP_OFFSET);
    tmp = (htgt_reg->pide & 0x1) << 7;
    SX_PUT_REG_FIELD(inbox, tmp, REG_HTGT_PIDE_OFFSET);
    SX_PUT_REG_FIELD(inbox, htgt_reg->pid, REG_HTGT_PID_OFFSET);
    SX_PUT_REG_FIELD(inbox, htgt_reg->mirror_action, REG_HTGT_MRR_ACTION_OFFSET);
    SX_PUT_REG_FIELD(inbox, htgt_reg->mirror_agent, REG_HTGT_MRR_AGENT_OFFSET);
    SX_PUT_REG_FIELD(inbox, htgt_reg->priority, REG_HTGT_PRIO_OFFSET);

    switch (htgt_reg->type) {
    case HTGT_LOCAL_PATH:
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.local_path.cpu_tclass, REG_HTGT_LP_CPU_TC_OFFSET);
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.local_path.rdq, REG_HTGT_LP_RDQ_OFFSET);
        break;

    case HTGT_STACKING_PATH:
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.stacking_path.stacking_tclass, REG_HTGT_SP_STK_TC_OFFSET);
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.stacking_path.cpu_tclass, REG_HTGT_SP_CPU_TC_OFFSET);
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.stacking_path.rdq, REG_HTGT_SP_RDQ_OFFSET);
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.stacking_path.cpu_sys_port, REG_HTGT_SP_SYS_PORT_OFFSET);
        break;

    case HTGT_DR_PATH:
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.dr_path.dr_ptr, REG_HTGT_DRP_DR_PTR_OFFSET);
        break;

    case HTGT_ETH_PATH:
        mac_47_32 = (htgt_reg->path.eth_path.mac >> 32) & 0xFFFF;
        mac_31_0 = htgt_reg->path.eth_path.mac & 0xFFFFFFFF;
        SX_PUT_REG_FIELD(inbox, mac_47_32, REG_HTGT_EP_MAC_47_32_OFFSET);
        SX_PUT_REG_FIELD(inbox, mac_31_0, REG_HTGT_EP_MAC_31_0_OFFSET);
        SX_PUT_REG_FIELD(inbox, htgt_reg->path.eth_path.vid, REG_HTGT_EP_VID_OFFSET);
        break;

    case HTGT_NULL_PATH:
        break;

    default:
        printk(KERN_ERR "%s(): Incorrect HTGT path type: %d \n", __func__, htgt_reg->type);
        return -EINVAL;
    }

    return 0;
}

static int __HTGT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_htgt_reg *htgt_reg = (struct ku_htgt_reg*)ku_reg;
    u16                 mac_47_32;
    u32                 mac_31_0;
    u8                  tmp;

    SX_GET_REG_FIELD(htgt_reg->swid, outbox, REG_HTGT_SWID_OFFSET);
    SX_GET_REG_FIELD(htgt_reg->type, outbox, REG_HTGT_TYPE_OFFSET);
    SX_GET_REG_FIELD(htgt_reg->trap_group, outbox, REG_HTGT_GRP_OFFSET);
    SX_GET_REG_FIELD(tmp, outbox, REG_HTGT_PIDE_OFFSET);
    htgt_reg->pide = (tmp >> 0x7) & 0x1;
    SX_GET_REG_FIELD(htgt_reg->pid, outbox, REG_HTGT_PID_OFFSET);
    SX_GET_REG_FIELD(htgt_reg->mirror_action, outbox, REG_HTGT_MRR_ACTION_OFFSET);
    SX_GET_REG_FIELD(htgt_reg->mirror_agent, outbox, REG_HTGT_MRR_AGENT_OFFSET);
    SX_GET_REG_FIELD(htgt_reg->priority, outbox, REG_HTGT_PRIO_OFFSET);

    switch (htgt_reg->type) {
    case HTGT_LOCAL_PATH:
        SX_GET_REG_FIELD(htgt_reg->path.local_path.cpu_tclass, outbox, REG_HTGT_LP_CPU_TC_OFFSET);
        SX_GET_REG_FIELD(htgt_reg->path.local_path.rdq, outbox, REG_HTGT_LP_RDQ_OFFSET);
        break;

    case HTGT_STACKING_PATH:
        SX_GET_REG_FIELD(htgt_reg->path.stacking_path.stacking_tclass, outbox, REG_HTGT_SP_STK_TC_OFFSET);
        SX_GET_REG_FIELD(htgt_reg->path.stacking_path.cpu_tclass, outbox, REG_HTGT_SP_CPU_TC_OFFSET);
        SX_GET_REG_FIELD(htgt_reg->path.stacking_path.rdq, outbox, REG_HTGT_SP_RDQ_OFFSET);
        SX_GET_REG_FIELD(htgt_reg->path.stacking_path.cpu_sys_port, outbox, REG_HTGT_SP_SYS_PORT_OFFSET);
        break;

    case HTGT_DR_PATH:
        SX_GET_REG_FIELD(htgt_reg->path.dr_path.dr_ptr, outbox, REG_HTGT_DRP_DR_PTR_OFFSET);
        break;

    case HTGT_ETH_PATH:
        SX_GET_REG_FIELD(mac_47_32, outbox, REG_HTGT_EP_MAC_47_32_OFFSET);
        SX_GET_REG_FIELD(mac_31_0, outbox, REG_HTGT_EP_MAC_31_0_OFFSET);
        htgt_reg->path.eth_path.mac = mac_47_32;
        htgt_reg->path.eth_path.mac = (htgt_reg->path.eth_path.mac << 32) | mac_31_0;
        SX_GET_REG_FIELD(htgt_reg->path.eth_path.vid, outbox, REG_HTGT_EP_VID_OFFSET);
        break;

    case HTGT_NULL_PATH:
        break;

    default:
        printk(KERN_ERR "%s(): Incorrect HTGT path type: %d on query\n", __func__, htgt_reg->type);
        return -EINVAL;
    }

    return 0;
}

int sx_ACCESS_REG_HTGT(struct sx_dev *dev, struct ku_access_htgt_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __HTGT_encode,
                                  __HTGT_decode,
                                  HTGT_REG_LEN,
                                  &reg_data->htgt_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_HTGT);


/************************************************
 * SPAD
 ***********************************************/
#define REG_BASE_MAC_OFFSET 0x14
#define SPAD_REG_LEN        0x05

static int __SPAD_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_spad_reg *spad_reg = (struct ku_spad_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, spad_reg->base_mac, REG_BASE_MAC_OFFSET);
    return 0;
}

static int __SPAD_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_spad_reg *spad_reg = (struct ku_spad_reg*)ku_reg;

    SX_GET_REG_FIELD(spad_reg->base_mac, outbox, REG_BASE_MAC_OFFSET);
    return 0;
}

int sx_ACCESS_REG_SPAD(struct sx_dev *dev, struct ku_access_spad_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SPAD_encode,
                                  __SPAD_decode,
                                  SPAD_REG_LEN,
                                  &reg_data->spad_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SPAD);


/************************************************
 * SSPR
 ***********************************************/
#define SSPR_REG_MASTER_BIT_OFFSET 0x14
#define SSPR_REG_MASTER_BIT_N      7
#define SSPR_REG_LOCAL_PORT_OFFSET 0x15
#define SSPR_REG_SUB_PORT          0x16
#define SSPR_REG_SYSTEM_PORT       0x1a
#define SSPR_REG_LEN               0x03

static int __SSPR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sspr_reg *sspr_reg = (struct ku_sspr_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;

    tmp_val_u8 |= sspr_reg->is_master ? (1 << SSPR_REG_MASTER_BIT_N) : 0;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, SSPR_REG_MASTER_BIT_OFFSET);
    SX_PUT_REG_FIELD(inbox, sspr_reg->local_port, SSPR_REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, sspr_reg->sub_port, SSPR_REG_SUB_PORT);
    SX_PUT_REG_FIELD(inbox, sspr_reg->system_port, SSPR_REG_SYSTEM_PORT);
    return 0;
}

static int __SSPR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sspr_reg *sspr_reg = (struct ku_sspr_reg*)ku_reg;
    u8                  tmp_val_u8;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, SSPR_REG_MASTER_BIT_OFFSET);
    if (tmp_val_u8 & (1 << SSPR_REG_MASTER_BIT_N)) {
        sspr_reg->is_master = 1;
    }
    SX_GET_REG_FIELD(sspr_reg->local_port, outbox, SSPR_REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(sspr_reg->sub_port, outbox, SSPR_REG_SUB_PORT);
    SX_GET_REG_FIELD(sspr_reg->system_port, outbox, SSPR_REG_SYSTEM_PORT);
    return 0;
}

int sx_ACCESS_REG_SSPR(struct sx_dev *dev, struct ku_access_sspr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SSPR_encode,
                                  __SSPR_decode,
                                  SSPR_REG_LEN,
                                  &reg_data->sspr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SSPR);


/************************************************
 * PPAD
 ***********************************************/
#define PPAD_REG_SINGLE_BASE_MAC 0x14
#define PPAD_REG_LOCAL_PORT      0x15
#define PPAD_REG_BASE_MAC_47_32  0x16
#define PPAD_REG_BASE_MAC_31_0   0x18
#define PPAD_REG_LEN             0x05

static int __PPAD_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppad_reg *ppad_reg = (struct ku_ppad_reg*)ku_reg;
    u16                 mac_47_32;
    u32                 mac_31_0;
    u8                  tmp_single;

    mac_47_32 = (ppad_reg->mac[0] << 8) | ppad_reg->mac[1];
    mac_31_0 = (ppad_reg->mac[2] << 24) |
               (ppad_reg->mac[3] << 16) |
               (ppad_reg->mac[4] << 8); /* Last byte reserved (0) */
    if (ppad_reg->single_base_mac == 1) {
        mac_31_0 |= ppad_reg->mac[5];
        tmp_single = (ppad_reg->single_base_mac & 0x1) << 4;
        SX_PUT_REG_FIELD(inbox, tmp_single, PPAD_REG_SINGLE_BASE_MAC);
        SX_PUT_REG_FIELD(inbox, ppad_reg->local_port, PPAD_REG_LOCAL_PORT);
    }
    SX_PUT_REG_FIELD(inbox, mac_47_32, PPAD_REG_BASE_MAC_47_32);
    SX_PUT_REG_FIELD(inbox, mac_47_32, PPAD_REG_BASE_MAC_31_0);
    return 0;
}

static int __PPAD_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppad_reg *ppad_reg = (struct ku_ppad_reg*)ku_reg;
    u16                 mac_47_32;
    u32                 mac_31_0;

    SX_GET_REG_FIELD(ppad_reg->local_port, outbox, PPAD_REG_LOCAL_PORT);
    SX_GET_REG_FIELD(mac_47_32, outbox, PPAD_REG_BASE_MAC_47_32);
    SX_GET_REG_FIELD(mac_31_0, outbox, PPAD_REG_BASE_MAC_31_0);
    ppad_reg->mac[5] = (mac_31_0) & 0xff;
    ppad_reg->mac[4] = (mac_31_0 >> 8) & 0xff;
    ppad_reg->mac[3] = (mac_31_0 >> 16) & 0xff;
    ppad_reg->mac[2] = (mac_31_0 >> 24) & 0xff;
    ppad_reg->mac[1] = mac_47_32 & 0xff;
    ppad_reg->mac[0] = (mac_47_32 >> 8) & 0xff;
    return 0;
}

int sx_ACCESS_REG_PPAD(struct sx_dev *dev, struct ku_access_ppad_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPAD_encode,
                                  __PPAD_decode,
                                  PPAD_REG_LEN,
                                  &reg_data->ppad_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPAD);


/************************************************
 * SPMCR
 ***********************************************/
#define SPMCR_REG_SWID_OFFSET          0x14
#define SPMCR_REG_LOCAL_PORT_OFFSET    0x15
#define SPMCR_REG_MAX_SUB_PORT_OFFSET  0x16
#define SPMCR_REG_BASE_STAG_VID_OFFSET 0x1a
#define SPMCR_REG_LEN                  0x03

static int __SPMCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_spmcr_reg *spmcr_reg = (struct ku_spmcr_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, spmcr_reg->swid, SPMCR_REG_SWID_OFFSET);
    SX_PUT_REG_FIELD(inbox, spmcr_reg->local_port, SPMCR_REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, spmcr_reg->max_sub_port, SPMCR_REG_MAX_SUB_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, spmcr_reg->base_stag_vid, SPMCR_REG_BASE_STAG_VID_OFFSET);
    return 0;
}

static int __SPMCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_spmcr_reg *spmcr_reg = (struct ku_spmcr_reg*)ku_reg;

    SX_GET_REG_FIELD(spmcr_reg->swid, outbox, SPMCR_REG_SWID_OFFSET);
    SX_GET_REG_FIELD(spmcr_reg->local_port, outbox, SPMCR_REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(spmcr_reg->max_sub_port, outbox, SPMCR_REG_MAX_SUB_PORT_OFFSET);
    SX_GET_REG_FIELD(spmcr_reg->swid, outbox, SPMCR_REG_BASE_STAG_VID_OFFSET);
    return 0;
}

int sx_ACCESS_REG_SPMCR(struct sx_dev *dev, struct ku_access_spmcr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SPMCR_encode,
                                  __SPMCR_decode,
                                  SPMCR_REG_LEN,
                                  &reg_data->spmcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SPMCR);


/************************************************
 * PBMC
 ***********************************************/
#define PBMC_REG_LOCAL_PORT_OFFSET     0x15
#define PBMC_REG_XOF_TIMER_VAL_OFFSET  0x19
#define PBMC_REG_XOF_REFRESH_OFFSET    0x1b
#define PBMC_REG_PORT_BUFF_SIZE_OFFSET 0x1e
#define PBMC_REG_BUFF_0_OFFSET         0x20
#define PBMC_REG_LEN                   24

#define BUFF_SIZE_OFFSET 2
#define BUFF_XOFF_OFFSET 4
#define BUFF_XON_OFFSET  6

static int __PBMC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pbmc_reg *pbmc_reg = (struct ku_pbmc_reg*)ku_reg;
    int                 i;

    SX_PUT_REG_FIELD(inbox, pbmc_reg->local_port, PBMC_REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pbmc_reg->xof_timer_value, PBMC_REG_XOF_TIMER_VAL_OFFSET);
    SX_PUT_REG_FIELD(inbox, pbmc_reg->xof_refresh, PBMC_REG_XOF_REFRESH_OFFSET);
    for (i = 0; i < 10; i++) {
        int buff_offset = PBMC_REG_BUFF_0_OFFSET + 8 * i;
        SX_PUT_REG_FIELD(inbox, pbmc_reg->buffer[i].size, buff_offset + BUFF_SIZE_OFFSET);
        SX_PUT_REG_FIELD(inbox, pbmc_reg->buffer[i].xof_threshold, buff_offset + BUFF_XOFF_OFFSET);
        SX_PUT_REG_FIELD(inbox, pbmc_reg->buffer[i].xon_threshold, buff_offset + BUFF_XON_OFFSET);
    }

    return 0;
}

static int __PBMC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pbmc_reg *pbmc_reg = (struct ku_pbmc_reg*)ku_reg;
    int                 i;

    SX_GET_REG_FIELD(pbmc_reg->local_port, outbox, PBMC_REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pbmc_reg->xof_timer_value, outbox, PBMC_REG_XOF_TIMER_VAL_OFFSET);
    SX_GET_REG_FIELD(pbmc_reg->xof_refresh, outbox, PBMC_REG_XOF_REFRESH_OFFSET);
    for (i = 0; i < 10; i++) {
        int buff_offset = PBMC_REG_BUFF_0_OFFSET + 8 * i;
        SX_GET_REG_FIELD(pbmc_reg->buffer[i].size, outbox, buff_offset + BUFF_SIZE_OFFSET);
        SX_GET_REG_FIELD(pbmc_reg->buffer[i].xof_threshold, outbox, buff_offset + BUFF_XOFF_OFFSET);
        SX_GET_REG_FIELD(pbmc_reg->buffer[i].xon_threshold, outbox, buff_offset + BUFF_XON_OFFSET);
    }

    return 0;
}

int sx_ACCESS_REG_PBMC(struct sx_dev *dev, struct ku_access_pbmc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PBMC_encode,
                                  __PBMC_decode,
                                  PBMC_REG_LEN,
                                  &reg_data->pbmc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PBMC);


/************************************************
 * PPTB
 ***********************************************/
#define PPTB_REG_LOCAL_PORT_OFFSET      0x15
#define PPTB_REG_CM_UM_BITS_OFFSET      0x16
#define PPTB_REG_UM_BIT_N               0
#define PPTB_REG_CM_BIT_N               1
#define PPTB_REG_PM_OFFSET              0x17
#define PPTB_REG_PRIO_7_6_BUFF_OFFSET   0x18
#define PPTB_REG_PRIO_5_4_BUFF_OFFSET   0x19
#define PPTB_REG_PRIO_3_2_BUFF_OFFSET   0x1a
#define PPTB_REG_PRIO_1_0_BUFF_OFFSET   0x1b
#define PPTB_REG_CTRL_UNTAG_BUFF_OFFSET 0x1f
#define PPTB_REG_LEN                    0x05

static int __PPTB_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pptb_reg *pptb_reg = (struct ku_pptb_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;

    SX_PUT_REG_FIELD(inbox, pptb_reg->local_port, PPTB_REG_LOCAL_PORT_OFFSET);
    tmp_val_u8 = (pptb_reg->cm << PPTB_REG_CM_BIT_N) | pptb_reg->um;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, PPTB_REG_CM_UM_BITS_OFFSET);
    SX_PUT_REG_FIELD(inbox, pptb_reg->pm, PPTB_REG_PM_OFFSET);
    tmp_val_u8 = (pptb_reg->prio_7_buff << 4) | (pptb_reg->prio_6_buff & 0xf);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, PPTB_REG_PRIO_7_6_BUFF_OFFSET);
    tmp_val_u8 = (pptb_reg->prio_5_buff << 4) | (pptb_reg->prio_4_buff & 0xf);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, PPTB_REG_PRIO_5_4_BUFF_OFFSET);
    tmp_val_u8 = (pptb_reg->prio_3_buff << 4) | (pptb_reg->prio_2_buff & 0xf);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, PPTB_REG_PRIO_3_2_BUFF_OFFSET);
    tmp_val_u8 = (pptb_reg->prio_1_buff << 4) | (pptb_reg->prio_0_buff & 0xf);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, PPTB_REG_PRIO_1_0_BUFF_OFFSET);
    tmp_val_u8 = (pptb_reg->ctrl_buff << 4) | (pptb_reg->untagged_buff & 0xf);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, PPTB_REG_CTRL_UNTAG_BUFF_OFFSET);
    return 0;
}

static int __PPTB_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pptb_reg *pptb_reg = (struct ku_pptb_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;

    SX_GET_REG_FIELD(pptb_reg->local_port, outbox, PPTB_REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u8, outbox, PPTB_REG_CM_UM_BITS_OFFSET);
    pptb_reg->um = (tmp_val_u8 >> PPTB_REG_UM_BIT_N) & 1;
    pptb_reg->cm = (tmp_val_u8 >> PPTB_REG_CM_BIT_N) & 1;
    SX_GET_REG_FIELD(pptb_reg->pm, outbox, PPTB_REG_PM_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u8, outbox, PPTB_REG_PRIO_7_6_BUFF_OFFSET);
    pptb_reg->prio_6_buff = tmp_val_u8 & 0xf;
    pptb_reg->prio_7_buff = (tmp_val_u8 >> 4) & 0xf;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, PPTB_REG_PRIO_5_4_BUFF_OFFSET);
    pptb_reg->prio_4_buff = tmp_val_u8 & 0xf;
    pptb_reg->prio_5_buff = (tmp_val_u8 >> 4) & 0xf;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, PPTB_REG_PRIO_3_2_BUFF_OFFSET);
    pptb_reg->prio_2_buff = tmp_val_u8 & 0xf;
    pptb_reg->prio_3_buff = (tmp_val_u8 >> 4) & 0xf;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, PPTB_REG_PRIO_1_0_BUFF_OFFSET);
    pptb_reg->prio_0_buff = tmp_val_u8 & 0xf;
    pptb_reg->prio_1_buff = (tmp_val_u8 >> 4) & 0xf;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, PPTB_REG_CTRL_UNTAG_BUFF_OFFSET);
    pptb_reg->untagged_buff = tmp_val_u8 & 0xf;
    pptb_reg->ctrl_buff = (tmp_val_u8 >> 4) & 0xf;
    return 0;
}

int sx_ACCESS_REG_PPTB(struct sx_dev *dev, struct ku_access_pptb_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPTB_encode,
                                  __PPTB_decode,
                                  PPTB_REG_LEN,
                                  &reg_data->pptb_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPTB);


/************************************************
 * SMID
 ***********************************************/
#define SMID_REG_SWID_OFFSET 0x14
#define SMID_REG_MID_OFFSET  0x16

#define SMID_REG_PORTS_255_224_OFFSET 0x34
#define SMID_REG_PORTS_223_192_OFFSET 0x38
#define SMID_REG_PORTS_191_160_OFFSET 0x3c
#define SMID_REG_PORTS_159_128_OFFSET 0x40
#define SMID_REG_PORTS_127_96_OFFSET  0x44
#define SMID_REG_PORTS_95_64_OFFSET   0x48
#define SMID_REG_PORTS_63_32_OFFSET   0x4c
#define SMID_REG_PORTS_31_0_OFFSET    0x50

#define SMID_REG_PORTS_255_224_MASK_OFFSET 0x54
#define SMID_REG_PORTS_223_192_MASK_OFFSET 0x58
#define SMID_REG_PORTS_191_160_MASK_OFFSET 0x5c
#define SMID_REG_PORTS_159_128_MASK_OFFSET 0x60
#define SMID_REG_PORTS_127_96_MASK_OFFSET  0x64
#define SMID_REG_PORTS_95_64_MASK_OFFSET   0x68
#define SMID_REG_PORTS_63_32_MASK_OFFSET   0x6c
#define SMID_REG_PORTS_31_0_MASK_OFFSET    0x70

#define SMID_REG_LEN 0x19

static int __SMID_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_smid_reg *smid_reg = (struct ku_smid_reg*)ku_reg;
    u32                 tmp_val_u32;
    u32                 tmp_mask_u32;
    int                 i, j;

    SX_PUT_REG_FIELD(inbox, smid_reg->swid, SMID_REG_SWID_OFFSET);
    SX_PUT_REG_FIELD(inbox, smid_reg->mid, SMID_REG_MID_OFFSET);

    for (j = 0; j < 256; j += 32) {
        tmp_val_u32 = 0;
        tmp_mask_u32 = 0;

        for (i = 0; i < 32; i++) {
            tmp_val_u32 |= (smid_reg->ports_bitmap[j + i] ? (1 << i) : 0);
            tmp_mask_u32 |= (smid_reg->mask_bitmap[j + i] ? (1 << i) : 0);
        }

        if (j == 0) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_31_0_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_31_0_MASK_OFFSET);
        } else if (j == 32) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_63_32_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_63_32_MASK_OFFSET);
        } else if (j == 64) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_95_64_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_95_64_MASK_OFFSET);
        } else if (j == 96) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_127_96_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_127_96_MASK_OFFSET);
        } else if (j == 128) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_159_128_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_159_128_MASK_OFFSET);
        } else if (j == 160) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_191_160_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_191_160_MASK_OFFSET);
        } else if (j == 192) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_223_192_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_223_192_MASK_OFFSET);
        } else if (j == 224) {
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, SMID_REG_PORTS_255_224_OFFSET);
            SX_PUT_REG_FIELD(inbox, tmp_mask_u32, SMID_REG_PORTS_255_224_MASK_OFFSET);
        }
    }

    return 0;
}

static int __SMID_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_smid_reg *smid_reg = (struct ku_smid_reg*)ku_reg;
    u32                 tmp_val_u32;
    int                 i;

    SX_GET_REG_FIELD(smid_reg->swid, outbox, SMID_REG_SWID_OFFSET);
    SX_GET_REG_FIELD(smid_reg->mid, outbox, SMID_REG_MID_OFFSET);
    /*
     *  SX_GET_REG_FIELD(tmp_val_u32, outbox,SMID_REG_PORTS_255_224_OFFSET);
     *  SX_GET_REG_FIELD(tmp_val_u32, outbox,SMID_REG_PORTS_223_192_OFFSET);
     *  SX_GET_REG_FIELD(tmp_val_u32, outbox,SMID_REG_PORTS_191_160_OFFSET);
     *  SX_GET_REG_FIELD(tmp_val_u32, outbox,SMID_REG_PORTS_159_128_OFFSET);
     *  SX_GET_REG_FIELD(tmp_val_u32, outbox,SMID_REG_PORTS_127_96_OFFSET);
     *  SX_GET_REG_FIELD(tmp_val_u32, outbox,SMID_REG_PORTS_95_64_OFFSET);
     */
    SX_GET_REG_FIELD(tmp_val_u32, outbox, SMID_REG_PORTS_63_32_OFFSET);
    for (i = 0; i < 32; i++) {
        if (tmp_val_u32 & (1 << i)) {
            smid_reg->ports_bitmap[32 + i] = 1;
        }
    }
    SX_GET_REG_FIELD(tmp_val_u32, outbox, SMID_REG_PORTS_31_0_OFFSET);
    for (i = 0; i < 32; i++) {
        if (tmp_val_u32 & (1 << i)) {
            smid_reg->ports_bitmap[i] = 1;
        }
    }

    return 0;
}

int sx_ACCESS_REG_SMID(struct sx_dev *dev, struct ku_access_smid_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SMID_encode,
                                  __SMID_decode,
                                  SMID_REG_LEN,
                                  &reg_data->smid_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SMID);


/************************************************
 * SPMS
 ***********************************************/
#define SPMS_REG_LOCAL_PORT_OFFSET           0x15
#define SPMS_REG_VLAN_63_48_STP_STATE_OFFSET 0x18
#define SPMS_REG_VLAN_47_32_STP_STATE_OFFSET 0x1c
#define SPMS_REG_VLAN_31_16_STP_STATE_OFFSET 0x20
#define SPMS_REG_VLAN_15_0_STP_STATE_OFFSET  0x24
#define SPMS_REG_LEN                         0x06

static int __SPMS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_spms_reg *spms_reg = (struct ku_spms_reg*)ku_reg;
    u32                 tmp_val_u32;

    SX_PUT_REG_FIELD(inbox, spms_reg->local_port, SPMS_REG_LOCAL_PORT_OFFSET);
    tmp_val_u32 = 0x0C;
    SX_PUT_REG_FIELD(inbox, tmp_val_u32, SPMS_REG_VLAN_15_0_STP_STATE_OFFSET);
    tmp_val_u32 = 0;
    SX_PUT_REG_FIELD(inbox, tmp_val_u32, SPMS_REG_VLAN_31_16_STP_STATE_OFFSET);
    tmp_val_u32 = 0;
    SX_PUT_REG_FIELD(inbox, tmp_val_u32, SPMS_REG_VLAN_47_32_STP_STATE_OFFSET);
    tmp_val_u32 = 0;
    SX_PUT_REG_FIELD(inbox, tmp_val_u32, SPMS_REG_VLAN_63_48_STP_STATE_OFFSET);
    return 0;
}

static int __SPMS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_spms_reg *spms_reg = (struct ku_spms_reg*)ku_reg;
    u32                 tmp_val_u32;

    SX_GET_REG_FIELD(spms_reg->local_port, outbox, SPMS_REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u32, outbox, SPMS_REG_VLAN_15_0_STP_STATE_OFFSET);
    if (tmp_val_u32 & 0xc) {
        spms_reg->state[1] = tmp_val_u32 & 0x3;
    }

    return 0;
}

int sx_ACCESS_REG_SPMS(struct sx_dev *dev, struct ku_access_spms_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SPMS_encode,
                                  __SPMS_decode,
                                  SPMS_REG_LEN,
                                  &reg_data->spms_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SPMS);


/************************************************
 * SPVID
 ***********************************************/
#define SPVID_REG_LOCAL_PORT_OFFSET 0x15
#define SPVID_REG_SUB_PORT_OFFSET   0x16
#define SPVID_REG_PORT_VID_OFFSET   0x1a
#define SPVID_REG_LEN               0x03

static int __SPVID_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_spvid_reg *spvid_reg = (struct ku_spvid_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, spvid_reg->local_port, SPVID_REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, spvid_reg->sub_port, SPVID_REG_SUB_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, spvid_reg->port_default_vid, SPVID_REG_PORT_VID_OFFSET);
    return 0;
}

static int __SPVID_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_spvid_reg *spvid_reg = (struct ku_spvid_reg*)ku_reg;

    SX_GET_REG_FIELD(spvid_reg->local_port, outbox, SPVID_REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(spvid_reg->sub_port, outbox, SPVID_REG_SUB_PORT_OFFSET);
    SX_GET_REG_FIELD(spvid_reg->port_default_vid, outbox, SPVID_REG_PORT_VID_OFFSET);
    return 0;
}

int sx_ACCESS_REG_SPVID(struct sx_dev *dev, struct ku_access_spvid_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SPVID_encode,
                                  __SPVID_decode,
                                  SPVID_REG_LEN,
                                  &reg_data->spvid_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SPVID);


/************************************************
 * SFD
 ***********************************************/
#define SFD_REG_SWID_OFFSET            0x14
#define SFD_REG_OP_NEXT_LOCATOR_OFFSET 0x18
#define SFD_REG_NUM_RECORDS_OFFSET     0x1f
#define SFD_REG_FDB_RECORD_0_OFFSET    0x24
#define SFD_REG_WITH_SINGLE_RECORD_LEN 0x9

#define SFD_REG_FDB_RECORD_UC_SWID_OFF        0
#define SFD_REG_FDB_RECORD_UC_TYPE_POLICY_OFF 1
#define SFD_REG_FDB_RECORD_UC_MAC_47_32_OFF   2
#define SFD_REG_FDB_RECORD_UC_MAC_31_0_OFF    4
#define SFD_REG_FDB_RECORD_UC_SUB_PORT_OFF    9
#define SFD_REG_FDB_RECORD_UC_FID_VID_OFF     10
#define SFD_REG_FDB_RECORD_UC_ACTION_OFF      12
#define SFD_REG_FDB_RECORD_UC_SYSTEM_PORT_OFF 14

static int __SFD_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sfd_reg *sfd_reg = (struct ku_sfd_reg*)ku_reg;
    u8                 tmp_val_u8;
    u16                tmp_val_u16;
    u32                tmp_val_u32;
    int                i;

    SX_PUT_REG_FIELD(inbox, sfd_reg->swid, SFD_REG_SWID_OFFSET);
    tmp_val_u32 = ((sfd_reg->operation & 0x3) << 30) | (sfd_reg->record_locator & ~(0x3 << 30));
    SX_PUT_REG_FIELD(inbox, tmp_val_u32, SFD_REG_OP_NEXT_LOCATOR_OFFSET);
    SX_PUT_REG_FIELD(inbox, sfd_reg->num_records, SFD_REG_NUM_RECORDS_OFFSET);

    for (i = 0; i < sfd_reg->num_records; i++) {
        switch (sfd_reg->sfd_type[i]) {
        case SFD_TYPE_UNICAST:
        {
            int record_offset = SFD_REG_FDB_RECORD_0_OFFSET + 16 * i;
            SX_PUT_REG_FIELD(inbox, sfd_reg->swid, record_offset + SFD_REG_FDB_RECORD_UC_SWID_OFF);
            tmp_val_u8 = ((sfd_reg->sfd_type[i] & 0xF) << 4) | (sfd_reg->sfd_data_type[i].uc.policy << 2);
            SX_PUT_REG_FIELD(inbox, tmp_val_u8, record_offset + SFD_REG_FDB_RECORD_UC_TYPE_POLICY_OFF);
            tmp_val_u16 = (sfd_reg->sfd_data_type[i].uc.mac.ether_addr_octet[5] << 8) |
                          sfd_reg->sfd_data_type[i].uc.mac.ether_addr_octet[4];
            SX_PUT_REG_FIELD(inbox, tmp_val_u16, record_offset + SFD_REG_FDB_RECORD_UC_MAC_47_32_OFF);
            tmp_val_u32 = (sfd_reg->sfd_data_type[i].uc.mac.ether_addr_octet[3] << 24) |
                          (sfd_reg->sfd_data_type[i].uc.mac.ether_addr_octet[2] << 16) |
                          (sfd_reg->sfd_data_type[i].uc.mac.ether_addr_octet[1] << 8) |
                          sfd_reg->sfd_data_type[i].uc.mac.ether_addr_octet[0];
            SX_PUT_REG_FIELD(inbox, tmp_val_u32, record_offset + SFD_REG_FDB_RECORD_UC_MAC_31_0_OFF);
            SX_PUT_REG_FIELD(inbox,
                             sfd_reg->sfd_data_type[i].uc.sub_port,
                             record_offset + SFD_REG_FDB_RECORD_UC_SUB_PORT_OFF);
            SX_PUT_REG_FIELD(inbox,
                             sfd_reg->sfd_data_type[i].uc.fid_vid_type.vid,
                             record_offset + SFD_REG_FDB_RECORD_UC_FID_VID_OFF);
            tmp_val_u8 = sfd_reg->sfd_data_type[i].uc.action << 4;
            SX_PUT_REG_FIELD(inbox, tmp_val_u8, record_offset + SFD_REG_FDB_RECORD_UC_ACTION_OFF);
            SX_PUT_REG_FIELD(inbox,
                             sfd_reg->sfd_data_type[i].uc.system_port,
                             record_offset + SFD_REG_FDB_RECORD_UC_SYSTEM_PORT_OFF);
            break;
        }

        case SFD_TYPE_UNICAST_LAG:
            printk("DEMO func: skipping FDB LAG record add over i2c\n");
            break;

        case SFD_TYPE_MULTICAST:
            printk("DEMO func: skipping FDB MC record add over i2c\n");
            break;

        case SFD_TYPE_UNICAST_TUNNEL:
            printk("DEMO func: skipping FDB UC TUNNEL record add over i2c\n");
            break;

        case SFD_TYPE_MULTICAST_TUNNEL:
            printk("DEMO func: skipping FDB MC TUNNEL add over i2c\n");
            break;

        case SFD_TYPE_LEARNT_MAC_E:
            printk("DEMO func: skipping Learnt MAC record add over i2c\n");
            break;

        case SFD_TYPE_LEARNT_MAC_LAG_E:
            printk("DEMO func: skipping Learnt MAC LAG record add over i2c\n");
            break;

        case SFD_TYPE_LEARNT_MAC_TUNNEL_E:
            printk("DEMO func: skipping Learnt MAC Tunnel record add over i2c\n");
            break;

        case SFD_TYPE_AGED_MAC_E:
            printk("DEMO func: skipping Aged MAC record add over i2c\n");
            break;

        case SFD_TYPE_AGED_MAC_LAG_E:
            printk("DEMO func: skipping Aged MAC LAG record add over i2c\n");
            break;

        case SFD_TYPE_AGED_MAC_TUNNEL_E:
            printk("DEMO func: skipping Aged MAC Tunnel record add over i2c\n");
            break;
        }
    }

    return 0;
}

static int __SFD_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sfd_reg *sfd_reg = (struct ku_sfd_reg*)ku_reg;
    u8                 tmp_val_u8;
    u16                tmp_val_u16;
    u32                tmp_val_u32;

    printk("DEMO func: FDB record get over i2c will get only 1 record \n");

    SX_GET_REG_FIELD(sfd_reg->swid, outbox, SFD_REG_SWID_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u32, outbox, SFD_REG_OP_NEXT_LOCATOR_OFFSET);
    sfd_reg->operation = (tmp_val_u32 >> 30) & 0x3;
    sfd_reg->record_locator = tmp_val_u32 & ~(0x3 << 30);
    SX_GET_REG_FIELD(sfd_reg->num_records, outbox, SFD_REG_NUM_RECORDS_OFFSET);
    SX_GET_REG_FIELD(sfd_reg->swid, outbox, SFD_REG_FDB_RECORD_0_OFFSET + SFD_REG_FDB_RECORD_UC_SWID_OFF);
    SX_GET_REG_FIELD(tmp_val_u8, outbox, SFD_REG_FDB_RECORD_0_OFFSET + SFD_REG_FDB_RECORD_UC_TYPE_POLICY_OFF);
    sfd_reg->sfd_type[0] = (tmp_val_u8 >> 4) & 0xF;
    sfd_reg->sfd_data_type[0].uc.policy = (tmp_val_u8 >> 2) & 0x3;

    if (sfd_reg->sfd_type[0] != SFD_TYPE_UNICAST) {
        printk("DEMO func: FDB record get for sfd_type = %d ( != SFD_TYPE_UNICAST) not supported !!! \n",
               sfd_reg->sfd_type[0]);
        return 0;
    }

    SX_GET_REG_FIELD(tmp_val_u16, outbox, SFD_REG_FDB_RECORD_0_OFFSET + SFD_REG_FDB_RECORD_UC_MAC_47_32_OFF);
    sfd_reg->sfd_data_type[0].uc.mac.ether_addr_octet[5] = (tmp_val_u16 >> 8) & 0xff;
    sfd_reg->sfd_data_type[0].uc.mac.ether_addr_octet[4] = tmp_val_u16 & 0xff;

    SX_GET_REG_FIELD(tmp_val_u32, outbox, SFD_REG_FDB_RECORD_0_OFFSET + SFD_REG_FDB_RECORD_UC_MAC_31_0_OFF);
    sfd_reg->sfd_data_type[0].uc.mac.ether_addr_octet[3] = (tmp_val_u32 >> 24) & 0xff;
    sfd_reg->sfd_data_type[0].uc.mac.ether_addr_octet[2] = (tmp_val_u32 >> 16) & 0xff;
    sfd_reg->sfd_data_type[0].uc.mac.ether_addr_octet[1] = (tmp_val_u32 >> 8) & 0xff;
    sfd_reg->sfd_data_type[0].uc.mac.ether_addr_octet[0] = tmp_val_u32 & 0xff;

    SX_GET_REG_FIELD(sfd_reg->sfd_data_type[0].uc.sub_port,
                     outbox,
                     SFD_REG_FDB_RECORD_0_OFFSET + SFD_REG_FDB_RECORD_UC_SUB_PORT_OFF);
    SX_GET_REG_FIELD(sfd_reg->sfd_data_type[0].uc.fid_vid_type.vid,
                     outbox,
                     SFD_REG_FDB_RECORD_0_OFFSET + SFD_REG_FDB_RECORD_UC_FID_VID_OFF);

    SX_GET_REG_FIELD(tmp_val_u8, outbox, SFD_REG_FDB_RECORD_0_OFFSET + SFD_REG_FDB_RECORD_UC_ACTION_OFF);
    sfd_reg->sfd_data_type[0].uc.action = (tmp_val_u8 >> 4) & 0xf;

    SX_GET_REG_FIELD(sfd_reg->sfd_data_type[0].uc.system_port,
                     outbox,
                     SFD_REG_FDB_RECORD_0_OFFSET + SFD_REG_FDB_RECORD_UC_SYSTEM_PORT_OFF);

    return 0;
}

int sx_ACCESS_REG_SFD(struct sx_dev *dev, struct ku_access_sfd_reg *reg_data)
{
    u16 sfd_reg_len = SFD_REG_WITH_SINGLE_RECORD_LEN + (reg_data->sfd_reg.num_records - 1) * 4;

    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SFD_encode,
                                  __SFD_decode,
                                  sfd_reg_len,
                                  &reg_data->sfd_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SFD);


/************************************************
 * PLBF
 ***********************************************/
#define PLBF_LOCAL_PORT_OFFSET 0x15
#define PLBF_LBF_MODE_OFFSET   0x17
#define PLBF_REG_LEN           0x03

static int __PLBF_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_plbf_reg *plbf_reg = (struct ku_plbf_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, plbf_reg->port, PLBF_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, plbf_reg->lbf_mode, PLBF_LBF_MODE_OFFSET);
    return 0;
}

static int __PLBF_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_plbf_reg *plbf_reg = (struct ku_plbf_reg*)ku_reg;

    SX_GET_REG_FIELD(plbf_reg->port, outbox, PLBF_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(plbf_reg->lbf_mode, outbox, PLBF_LBF_MODE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PLBF(struct sx_dev *dev, struct ku_access_plbf_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PLBF_encode,
                                  __PLBF_decode,
                                  PLBF_REG_LEN,
                                  &reg_data->plbf_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PLBF);


/************************************************
 * SGCR
 ***********************************************/
#define SGCR_LLB_OFFSET 0x1b
#define SGCR_REG_LEN    0x15

static int __SGCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sgcr_reg *sgcr_reg = (struct ku_sgcr_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, sgcr_reg->llb, SGCR_LLB_OFFSET);
    return 0;
}

static int __SGCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sgcr_reg *sgcr_reg = (struct ku_sgcr_reg*)ku_reg;

    SX_GET_REG_FIELD(sgcr_reg->llb, outbox, SGCR_LLB_OFFSET);
    return 0;
}

int sx_ACCESS_REG_SGCR(struct sx_dev *dev, struct ku_access_sgcr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SGCR_encode,
                                  __SGCR_decode,
                                  SGCR_REG_LEN,
                                  &reg_data->sgcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SGCR);


/************************************************
 * MSCI
 ***********************************************/
#define MSCI_INDEX_OFFSET   0x17
#define MSCI_VERSION_OFFSET 0x18
#define MSCI_REG_LEN        0x5

static int __MSCI_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_msci_reg *msci_reg = (struct ku_msci_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, msci_reg->index, MSCI_INDEX_OFFSET);
    return 0;
}

static int __MSCI_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_msci_reg *msci_reg = (struct ku_msci_reg*)ku_reg;

    SX_GET_REG_FIELD(msci_reg->index, outbox, MSCI_INDEX_OFFSET);
    SX_GET_REG_FIELD(msci_reg->version, outbox, MSCI_VERSION_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MSCI(struct sx_dev *dev, struct ku_access_msci_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MSCI_encode,
                                  __MSCI_decode,
                                  MSCI_REG_LEN,
                                  &reg_data->msci_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MSCI);


/************************************************
 * MRSR
 ***********************************************/
#define MRSR_COMMAND_OFFSET 0x17
#define MRSR_REG_LEN        0x3

static int __MRSR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mrsr_reg *mrsr_reg = (struct ku_mrsr_reg*)ku_reg;
    u8                  tmp;

    tmp = (u8)mrsr_reg->command;
    SX_PUT_REG_FIELD(inbox, tmp, MRSR_COMMAND_OFFSET);
    return 0;
}


int sx_ACCESS_REG_MRSR(struct sx_dev *dev, struct ku_access_mrsr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  /* Ignore the error from FW regarding MRSR register */
                                  SX_ACCESS_REG_F_IGNORE_FW_RET_CODE,
                                  &reg_data->op_tlv,
                                  __MRSR_encode,
                                  NULL,
                                  MRSR_REG_LEN,
                                  &reg_data->mrsr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MRSR);


/************************************************
 * RGCR
 ***********************************************/
#define REG_EN_OFFSET           0x14
#define REG_MAX_VLAN_IFC_OFFSET 0x1A
#define REG_MAX_PORT_IFC_OFFSET 0x1E
#define REG_MAX_PKEY_IFC_OFFSET 0x22
#define REG_MAX_RIFS_OFFSET     0x26
#define REG_IPB_ALR_OFFSET      0x2A
#define REG_MCSI_RPF_OFFSET     0x2B
#define RGCR_REG_LEN            0x09

static int __RGCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_rgcr_reg *rgcr_reg = (struct ku_rgcr_reg*)ku_reg;
    u8                  tmp_val_u8;

    tmp_val_u8 = 0;
    tmp_val_u8 = (rgcr_reg->ipv4_enable & 0x1) << 7;
    tmp_val_u8 |= (rgcr_reg->ipv6_enable & 0x1) << 6;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_EN_OFFSET);
    SX_PUT_REG_FIELD(inbox, rgcr_reg->max_vlan_router_interfaces, REG_MAX_VLAN_IFC_OFFSET);
    SX_PUT_REG_FIELD(inbox, rgcr_reg->max_port_router_interfaces, REG_MAX_PORT_IFC_OFFSET);
    SX_PUT_REG_FIELD(inbox, rgcr_reg->max_pkey_router_interfaces, REG_MAX_PKEY_IFC_OFFSET);
    SX_PUT_REG_FIELD(inbox, rgcr_reg->max_router_interfaces, REG_MAX_RIFS_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 = (rgcr_reg->ipb & 0x1) << 1;
    tmp_val_u8 |= (rgcr_reg->allr & 0x1);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_IPB_ALR_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 = (rgcr_reg->mcsi & 0x1) << 4;
    tmp_val_u8 |= (rgcr_reg->rpf & 0x1);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_MCSI_RPF_OFFSET);
    return 0;
}

static int __RGCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_rgcr_reg *rgcr_reg = (struct ku_rgcr_reg*)ku_reg;
    u8                  tmp_val_u8;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_EN_OFFSET);
    rgcr_reg->ipv4_enable = (tmp_val_u8 >> 7) & 0x1;
    rgcr_reg->ipv6_enable = (tmp_val_u8 >> 6) & 0x1;
    SX_GET_REG_FIELD(rgcr_reg->max_vlan_router_interfaces, outbox, REG_MAX_VLAN_IFC_OFFSET);
    SX_GET_REG_FIELD(rgcr_reg->max_port_router_interfaces, outbox, REG_MAX_PORT_IFC_OFFSET);
    SX_GET_REG_FIELD(rgcr_reg->max_pkey_router_interfaces, outbox, REG_MAX_PKEY_IFC_OFFSET);
    SX_GET_REG_FIELD(rgcr_reg->max_router_interfaces, outbox, REG_MAX_RIFS_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_IPB_ALR_OFFSET);
    rgcr_reg->ipb = (tmp_val_u8 >> 1) & 0x1;
    rgcr_reg->allr = (tmp_val_u8) & 0x1;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_MCSI_RPF_OFFSET);
    rgcr_reg->mcsi = (tmp_val_u8 >> 4) & 0x1;
    rgcr_reg->rpf = (tmp_val_u8) & 0x1;
    return 0;
}

int sx_ACCESS_REG_RGCR(struct sx_dev *dev, struct ku_access_rgcr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __RGCR_encode,
                                  __RGCR_decode,
                                  RGCR_REG_LEN,
                                  &reg_data->rgcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_RGCR);


/************************************************
 * RTPS
 ***********************************************/
#define REG_SWID_OFFSET        0x14
#define REG_TCA_PHY_LOG_OFFSET 0x17
#define REG_SW_PHY_LOG_OFFSET  0x1B
#define RTPS_REG_LEN           0x03

static int __RTPS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_rtps_reg *rtps_reg = (struct ku_rtps_reg*)ku_reg;
    u8                  tmp_val_u8;

    SX_PUT_REG_FIELD(inbox, rtps_reg->swid, REG_SWID_OFFSET);
    tmp_val_u8 = (rtps_reg->tca_log_pstate & 0xF) << 4;
    tmp_val_u8 |= rtps_reg->tca_phy_pstate & 0xF;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_TCA_PHY_LOG_OFFSET);
    return 0;
}

static int __RTPS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_rtps_reg *rtps_reg = (struct ku_rtps_reg*)ku_reg;
    u8                  tmp_val_u8;

    SX_GET_REG_FIELD(rtps_reg->swid, outbox, REG_SWID_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_TCA_PHY_LOG_OFFSET);
    rtps_reg->tca_log_pstate = (tmp_val_u8 >> 4) & 0xF;
    rtps_reg->tca_phy_pstate = tmp_val_u8 & 0xF;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_SW_PHY_LOG_OFFSET);
    rtps_reg->switch_log_pstate = (tmp_val_u8 >> 4) & 0xF;
    rtps_reg->switch_phy_pstate = tmp_val_u8 & 0xF;
    return 0;
}

int sx_ACCESS_REG_RTPS(struct sx_dev *dev, struct ku_access_rtps_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __RTPS_encode,
                                  __RTPS_decode,
                                  RTPS_REG_LEN,
                                  &reg_data->rtps_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_RTPS);


/************************************************
 * RTCA
 ***********************************************/
#define REG_SWID_OFFSET 0x14
#define REG_LMC_OFFSET  0x15
#define REG_LID_OFFSET  0x16
#define REG_GID_OFFSET  0x18
#define GID_SIZE        16
#define RTCA_REG_LEN    0x08

static int __RTCA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_rtca_reg *rtca_reg = (struct ku_rtca_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, rtca_reg->swid, REG_SWID_OFFSET);
    SX_PUT_REG_FIELD(inbox, rtca_reg->lmc, REG_LMC_OFFSET);
    SX_PUT_REG_FIELD(inbox, rtca_reg->lid, REG_LID_OFFSET);
    return copy_from_user(inbox - REG_START_OFFSET + REG_GID_OFFSET, (uint8_t*)&(rtca_reg->gid), GID_SIZE);
}

static int __RTCA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_rtca_reg *rtca_reg = (struct ku_rtca_reg*)ku_reg;

    SX_GET_REG_FIELD(rtca_reg->swid, outbox, REG_SWID_OFFSET);
    SX_GET_REG_FIELD(rtca_reg->lmc, outbox, REG_LMC_OFFSET);
    SX_GET_REG_FIELD(rtca_reg->lid, outbox, REG_LID_OFFSET);
    return copy_to_user((uint8_t*)&(rtca_reg->gid), outbox - REG_START_OFFSET + REG_GID_OFFSET, GID_SIZE);
}

int sx_ACCESS_REG_RTCA(struct sx_dev *dev, struct ku_access_rtca_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __RTCA_encode,
                                  __RTCA_decode,
                                  RTCA_REG_LEN,
                                  &reg_data->rtca_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_RTCA);


/************************************************
 * RITR
 ***********************************************/
#define REG_ENA_IP_TYPE_MPLS_OFFSET            0x14
#define REG_RIF_OFFSET                         0x16
#define REG_FE_OFFSET                          0x18
#define REG_URPF_OFFSET                        0x19
#define REG_RITR_VRID_OFFSET                   0x1A
#define REG_RIF_PROP_VLAN_SWID_OFFSET          0x1C
#define REG_RIF_PROP_VLAN_ID_OFFSET            0x1E
#define REG_RIF_PROP_VLAN_EFID_OFFSET          0x22
#define REG_RIF_PROP_VLAN_MAC_47_32_OFFSET     0x26
#define REG_RIF_PROP_VLAN_MAC_31_0_OFFSET      0x28
#define REG_RIF_PROP_VLAN_VRRP_IPV6_OFFSET     0x32
#define REG_RIF_PROP_VLAN_VRRP_IPV4_OFFSET     0x33
#define REG_RIF_PROP_FID_SWID_OFFSET           0x1C
#define REG_RIF_PROP_FID_FID_OFFSET            0x1E
#define REG_RIF_PROP_FID_MAC_47_32_OFFSET      0x26
#define REG_RIF_PROP_FID_MAC_31_0_OFFSET       0x28
#define REG_RIF_PROP_FID_VRRP_IPV6_OFFSET      0x32
#define REG_RIF_PROP_FID_VRRP_IPV4_OFFSET      0x33
#define REG_RIF_PROP_SUB_PORT_LAG_OFFSET       0x1C
#define REG_RIF_PROP_SUB_PORT_OFFSET           0x1E
#define REG_RIF_PROP_SUB_PORT_EFID_OFFSET      0x22
#define REG_RIF_PROP_SUB_PORT_MAC_47_32_OFFSET 0x26
#define REG_RIF_PROP_SUB_PORT_MAC_31_0_OFFSET  0x28
#define REG_RIF_PROP_SUB_PORT_VID_OFFSET       0x2E
#define REG_RIF_PROP_SUB_PORT_VRRP_IPV6_OFFSET 0x32
#define REG_RIF_PROP_SUB_PORT_VRRP_IPV4_OFFSET 0x33
#define REG_RIF_PROP_IPOIB_PKEY_SWID_OFFSET    0x1C
#define REG_RIF_PROP_IPOIB_PKEY_OFFSET         0x1E
#define REG_RIF_PROP_IPOIB_PKEY_SCOPE_OFFSET   0x23
#define REG_RIF_PROP_IPOIB_PKEY_QKEY_OFFSET    0x28
#define REG_RIF_PROP_IPOIB_PKEY_QPN_OFFSET     0x2C
#define REG_RIF_PROP_IPINIP_PRTCL_TYP_OFFSET   0x1C
#define REG_RIF_PROP_IPINIP_OPT_OFFSET         0x1D
#define REG_RIF_PROP_IPINIP_UVR_OFFSET         0x1E
#define REG_RIF_PROP_IPINIP_USIP_OFFSET        0x24
#define REG_RIF_PROP_IPINIP_GRE_KEY_OFFSET     0x34
#define REG_RIF_PROP_IB_SWID_SWID_OFFSET       0x1C
#define REG_RIF_PROP_IB_SWID_LID_OFFSET        0x22
#define REG_RIF_PROP_IB_SWID_LMC_OFFSET        0x27
#define REG_RIF_PROP_IB_SWID_GUID_OFFSET       0x28
#define REG_RIF_PROP_IB_SWID_PORT_SWID_OFFSET  0x1C
#define REG_RIF_PROP_IB_SWID_PORT_PORT_OFFSET  0x1D
#define REG_RIF_PROP_IB_SWID_PORT_GUID_OFFSET  0x28
#define REG_RIF_PROP_IB_RTR_PORT_PORT_OFFSET   0x1D
#define REG_RIF_PROP_IB_RTR_PORT_GUID_OFFSET   0x28
#define REG_TTLTH_OFFSET                       0x48
#define REG_MTU_OFFSET                         0x4A
#define REG_INGRESS_CNTR_SET_OFFSET            0x4C
#define REG_EGRESS_CNTR_SET_OFFSET             0x50
#define IPV6_SIZE                              16
#define GUID_SIZE                              8
#define RITR_REG_LEN                           0x11

static int __RITR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ritr_reg *ritr_reg = (struct ku_ritr_reg*)ku_reg;
    u8                  tmp_val_u8;
    u16                 tmp_val_u16;
    u32                 tmp_val_u32;

    tmp_val_u16 = 0;
    tmp_val_u16 |= (ritr_reg->enable & 1) << 15;
    tmp_val_u16 |= (ritr_reg->valid & 1) << 14;
    tmp_val_u16 |= (ritr_reg->ipv4_enable & 1) << 13;
    tmp_val_u16 |= (ritr_reg->ipv6_enable & 1) << 12;
    tmp_val_u16 |= (ritr_reg->ipv4_mc & 1) << 11;
    tmp_val_u16 |= (ritr_reg->ipv6_mc & 1) << 10;
    tmp_val_u16 |= (ritr_reg->type & 0xF) << 6;
    tmp_val_u16 |= (ritr_reg->op & 3) << 4;
    tmp_val_u16 |= (ritr_reg->mpls & 1) << 3;
    SX_PUT_REG_FIELD(inbox, tmp_val_u16, REG_ENA_IP_TYPE_MPLS_OFFSET);
    SX_PUT_REG_FIELD(inbox, ritr_reg->router_interface, REG_RIF_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (ritr_reg->ipv4_forward_enable & 1) << 5;
    tmp_val_u8 |= (ritr_reg->ipv6_forward_enable & 1) << 4;
    tmp_val_u8 |= (ritr_reg->ipv4_forward_mc & 1) << 3;
    tmp_val_u8 |= (ritr_reg->ipv6_forward_mc & 1) << 2;
    tmp_val_u8 |= (ritr_reg->lb_en & 1);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_FE_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (ritr_reg->urpf_en_ipv4 & 1) << 7;
    tmp_val_u8 |= (ritr_reg->urpf_en_ipv6 & 1) << 6;
    tmp_val_u8 |= (ritr_reg->urpf_strict & 1) << 5;
    tmp_val_u8 |= (ritr_reg->urpf_ad & 1) << 4;
    tmp_val_u8 |= (ritr_reg->mpls_forward & 1) << 3;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_URPF_OFFSET);
    SX_PUT_REG_FIELD(inbox, ritr_reg->router, REG_RITR_VRID_OFFSET);
    switch (ritr_reg->type) {
    case VLAN_INTERFACE:
        SX_PUT_REG_FIELD(inbox, ritr_reg->rif_properties.vlan_interface.swid, REG_RIF_PROP_VLAN_SWID_OFFSET);
        SX_PUT_REG_FIELD(inbox, ritr_reg->rif_properties.vlan_interface.vlan_id, REG_RIF_PROP_VLAN_ID_OFFSET);
        SX_PUT_REG_FIELD(inbox, ritr_reg->rif_properties.vlan_interface.efid, REG_RIF_PROP_VLAN_EFID_OFFSET);
        tmp_val_u16 = (ritr_reg->rif_properties.vlan_interface.router_interface_mac[5] << 8) |
                      ritr_reg->rif_properties.vlan_interface.router_interface_mac[4];
        SX_PUT_REG_FIELD(inbox, tmp_val_u16, REG_RIF_PROP_VLAN_MAC_47_32_OFFSET);
        tmp_val_u32 = (ritr_reg->rif_properties.vlan_interface.router_interface_mac[3] << 24) |
                      (ritr_reg->rif_properties.vlan_interface.router_interface_mac[2] << 16) |
                      (ritr_reg->rif_properties.vlan_interface.router_interface_mac[1] << 8) |
                      ritr_reg->rif_properties.vlan_interface.router_interface_mac[0];
        SX_PUT_REG_FIELD(inbox, tmp_val_u32, REG_RIF_PROP_VLAN_MAC_31_0_OFFSET);
        break;

    case IB_SWID_INTERFACE:
        SX_PUT_REG_FIELD(inbox, ritr_reg->rif_properties.ib_swid_interface.swid, REG_RIF_PROP_IB_SWID_SWID_OFFSET);
        SX_PUT_REG_FIELD(inbox, ritr_reg->rif_properties.ib_swid_interface.lid, REG_RIF_PROP_IB_SWID_LID_OFFSET);
        SX_PUT_REG_FIELD(inbox, ritr_reg->rif_properties.ib_swid_interface.lmc, REG_RIF_PROP_IB_SWID_LMC_OFFSET);
        SX_PUT_REG_FIELD(inbox, ritr_reg->rif_properties.ib_swid_interface.guid, REG_RIF_PROP_IB_SWID_GUID_OFFSET);
        break;

    case FID_INTERFACE:
        break;

    case IB_SWID_PORT_INTERFACE:
        break;

    case SUB_PORT_INTERFACE:
        tmp_val_u8 = 0;
        tmp_val_u8 |= (ritr_reg->rif_properties.sub_port_interface.lag & 1);
        SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_RIF_PROP_SUB_PORT_LAG_OFFSET);
        SX_PUT_REG_FIELD(inbox, ritr_reg->rif_properties.sub_port_interface.system_port, REG_RIF_PROP_SUB_PORT_OFFSET);
        SX_PUT_REG_FIELD(inbox, ritr_reg->rif_properties.sub_port_interface.efid, REG_RIF_PROP_SUB_PORT_EFID_OFFSET);
        tmp_val_u16 = (ritr_reg->rif_properties.sub_port_interface.router_interface_mac[5] << 8) |
                      ritr_reg->rif_properties.sub_port_interface.router_interface_mac[4];
        SX_PUT_REG_FIELD(inbox, tmp_val_u16, REG_RIF_PROP_SUB_PORT_MAC_47_32_OFFSET);
        tmp_val_u32 = (ritr_reg->rif_properties.sub_port_interface.router_interface_mac[3] << 24) |
                      (ritr_reg->rif_properties.sub_port_interface.router_interface_mac[2] << 16) |
                      (ritr_reg->rif_properties.sub_port_interface.router_interface_mac[1] << 8) |
                      ritr_reg->rif_properties.sub_port_interface.router_interface_mac[0];
        SX_PUT_REG_FIELD(inbox, tmp_val_u32, REG_RIF_PROP_SUB_PORT_MAC_31_0_OFFSET);
        SX_PUT_REG_FIELD(inbox, ritr_reg->rif_properties.sub_port_interface.vlan_id, REG_RIF_PROP_SUB_PORT_VID_OFFSET);
        break;

    case IB_PORT_INTERFACE:
        break;

    case LOOPBACK_INTERFACE:
        break;

    case PKEY_INTERFACE:
        SX_PUT_REG_FIELD(inbox, ritr_reg->rif_properties.pkey_interface.swid, REG_RIF_PROP_IPOIB_PKEY_SWID_OFFSET);
        SX_PUT_REG_FIELD(inbox, ritr_reg->rif_properties.pkey_interface.pkey, REG_RIF_PROP_IPOIB_PKEY_OFFSET);
        SX_PUT_REG_FIELD(inbox, ritr_reg->rif_properties.pkey_interface.scope, REG_RIF_PROP_IPOIB_PKEY_SCOPE_OFFSET);
        SX_PUT_REG_FIELD(inbox, ritr_reg->rif_properties.pkey_interface.qkey, REG_RIF_PROP_IPOIB_PKEY_QKEY_OFFSET);
        tmp_val_u32 = ritr_reg->rif_properties.pkey_interface.qpn & 0x00ffffff;
        SX_PUT_REG_FIELD(inbox, tmp_val_u32, REG_RIF_PROP_IPOIB_PKEY_QPN_OFFSET);
        break;

    default:
        break;
    }

    SX_PUT_REG_FIELD(inbox, ritr_reg->ttl_threshold, REG_TTLTH_OFFSET);
    SX_PUT_REG_FIELD(inbox, ritr_reg->mtu, REG_MTU_OFFSET);
    tmp_val_u32 = ritr_reg->ingress_counter_set.type << 24;
    tmp_val_u32 |= ritr_reg->ingress_counter_set.index;
    SX_PUT_REG_FIELD(inbox, tmp_val_u32, REG_INGRESS_CNTR_SET_OFFSET);
    tmp_val_u32 = ritr_reg->egress_counter_set.type << 24;
    tmp_val_u32 |= ritr_reg->egress_counter_set.index;
    SX_PUT_REG_FIELD(inbox, tmp_val_u32, REG_EGRESS_CNTR_SET_OFFSET);
    return 0;
}

static int __RITR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ritr_reg *ritr_reg = (struct ku_ritr_reg*)ku_reg;
    u8                  tmp_val_u8;
    u16                 tmp_val_u16;
    u32                 tmp_val_u32;

    SX_GET_REG_FIELD(tmp_val_u16, outbox, REG_ENA_IP_TYPE_MPLS_OFFSET);
    ritr_reg->enable = (tmp_val_u16 >> 15) & 1;
    ritr_reg->valid = (tmp_val_u16 >> 14) & 1;
    ritr_reg->ipv4_enable = (tmp_val_u16 >> 13) & 1;
    ritr_reg->ipv6_enable = (tmp_val_u16 >> 12) & 1;
    ritr_reg->ipv4_mc = (tmp_val_u16 >> 11) & 1;
    ritr_reg->ipv6_mc = (tmp_val_u16 >> 10) & 1;
    ritr_reg->type = (tmp_val_u16 >> 6) & 0xF;
    ritr_reg->op = (tmp_val_u16 >> 4) & 3;
    ritr_reg->mpls = (tmp_val_u16 >> 3) & 1;
    SX_GET_REG_FIELD(ritr_reg->router_interface, outbox, REG_RIF_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_FE_OFFSET);
    ritr_reg->ipv4_forward_enable = (tmp_val_u8 >> 5) & 1;
    ritr_reg->ipv6_forward_enable = (tmp_val_u8 >> 4) & 1;
    ritr_reg->ipv4_forward_mc = (tmp_val_u8 >> 3) & 1;
    ritr_reg->ipv6_forward_mc = (tmp_val_u8 >> 2) & 1;
    ritr_reg->lb_en = tmp_val_u8 & 1;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_URPF_OFFSET);
    ritr_reg->urpf_en_ipv4 = (tmp_val_u8 >> 7) & 1;
    ritr_reg->urpf_en_ipv6 = (tmp_val_u8 >> 6) & 1;
    ritr_reg->urpf_strict = (tmp_val_u8 >> 5) & 1;
    ritr_reg->urpf_ad = (tmp_val_u8 >> 4) & 1;
    ritr_reg->mpls_forward = (tmp_val_u8 >> 3) & 1;
    SX_GET_REG_FIELD(ritr_reg->router, outbox, REG_RITR_VRID_OFFSET);
    switch (ritr_reg->type) {
    case VLAN_INTERFACE:
        SX_GET_REG_FIELD(ritr_reg->rif_properties.vlan_interface.swid, outbox, REG_RIF_PROP_VLAN_SWID_OFFSET);
        SX_GET_REG_FIELD(tmp_val_u16, outbox, REG_RIF_PROP_VLAN_ID_OFFSET);
        ritr_reg->rif_properties.vlan_interface.vlan_id = tmp_val_u16 & 0x0fff;
        SX_GET_REG_FIELD(ritr_reg->rif_properties.vlan_interface.efid, outbox, REG_RIF_PROP_VLAN_EFID_OFFSET);
        SX_GET_REG_FIELD(tmp_val_u16, outbox, REG_RIF_PROP_VLAN_MAC_47_32_OFFSET);
        ritr_reg->rif_properties.vlan_interface.router_interface_mac[5] = (tmp_val_u16 >> 8) & 0xff;
        ritr_reg->rif_properties.vlan_interface.router_interface_mac[4] = tmp_val_u16 & 0xff;
        SX_GET_REG_FIELD(tmp_val_u32, outbox, REG_RIF_PROP_VLAN_MAC_31_0_OFFSET);
        ritr_reg->rif_properties.vlan_interface.router_interface_mac[3] = (tmp_val_u32 >> 24) & 0xff;
        ritr_reg->rif_properties.vlan_interface.router_interface_mac[2] = (tmp_val_u32 >> 16) & 0xff;
        ritr_reg->rif_properties.vlan_interface.router_interface_mac[1] = (tmp_val_u32 >> 8) & 0xff;
        ritr_reg->rif_properties.vlan_interface.router_interface_mac[0] = tmp_val_u32 & 0xff;
        break;

    case IB_SWID_INTERFACE:
        SX_GET_REG_FIELD(ritr_reg->rif_properties.ib_swid_interface.swid, outbox, REG_RIF_PROP_IB_SWID_SWID_OFFSET);
        SX_GET_REG_FIELD(ritr_reg->rif_properties.ib_swid_interface.lid, outbox, REG_RIF_PROP_IB_SWID_LID_OFFSET);
        SX_GET_REG_FIELD(ritr_reg->rif_properties.ib_swid_interface.lmc, outbox, REG_RIF_PROP_IB_SWID_LMC_OFFSET);
        SX_GET_REG_FIELD(ritr_reg->rif_properties.ib_swid_interface.guid, outbox, REG_RIF_PROP_IB_SWID_GUID_OFFSET);
        break;

    case FID_INTERFACE:
        break;

    case IB_SWID_PORT_INTERFACE:
        break;

    case SUB_PORT_INTERFACE:
        SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_RIF_PROP_SUB_PORT_LAG_OFFSET);
        ritr_reg->rif_properties.sub_port_interface.lag = tmp_val_u8 & 1;
        SX_GET_REG_FIELD(ritr_reg->rif_properties.sub_port_interface.system_port, outbox,
                         REG_RIF_PROP_SUB_PORT_OFFSET);
        SX_GET_REG_FIELD(ritr_reg->rif_properties.sub_port_interface.efid, outbox, REG_RIF_PROP_SUB_PORT_EFID_OFFSET);
        SX_GET_REG_FIELD(tmp_val_u16, outbox, REG_RIF_PROP_SUB_PORT_MAC_47_32_OFFSET);
        ritr_reg->rif_properties.sub_port_interface.router_interface_mac[5] = (tmp_val_u16 >> 8) & 0xff;
        ritr_reg->rif_properties.sub_port_interface.router_interface_mac[4] = tmp_val_u16 & 0xff;
        SX_GET_REG_FIELD(tmp_val_u32, outbox, REG_RIF_PROP_SUB_PORT_MAC_31_0_OFFSET);
        ritr_reg->rif_properties.sub_port_interface.router_interface_mac[3] = (tmp_val_u32 >> 24) & 0xff;
        ritr_reg->rif_properties.sub_port_interface.router_interface_mac[2] = (tmp_val_u32 >> 16) & 0xff;
        ritr_reg->rif_properties.sub_port_interface.router_interface_mac[1] = (tmp_val_u32 >> 8) & 0xff;
        ritr_reg->rif_properties.sub_port_interface.router_interface_mac[0] = tmp_val_u32 & 0xff;
        SX_GET_REG_FIELD(ritr_reg->rif_properties.sub_port_interface.vlan_id, outbox,
                         REG_RIF_PROP_SUB_PORT_VID_OFFSET);
        break;

    case IB_PORT_INTERFACE:
        break;

    case LOOPBACK_INTERFACE:
        break;

    case PKEY_INTERFACE:
        SX_GET_REG_FIELD(ritr_reg->rif_properties.pkey_interface.swid, outbox, REG_RIF_PROP_IPOIB_PKEY_SWID_OFFSET);
        SX_GET_REG_FIELD(ritr_reg->rif_properties.pkey_interface.pkey, outbox, REG_RIF_PROP_IPOIB_PKEY_OFFSET);
        SX_GET_REG_FIELD(ritr_reg->rif_properties.pkey_interface.scope, outbox, REG_RIF_PROP_IPOIB_PKEY_SCOPE_OFFSET);
        SX_GET_REG_FIELD(ritr_reg->rif_properties.pkey_interface.qkey, outbox, REG_RIF_PROP_IPOIB_PKEY_QKEY_OFFSET);
        SX_GET_REG_FIELD(tmp_val_u32, outbox, REG_RIF_PROP_IPOIB_PKEY_QPN_OFFSET);
        ritr_reg->rif_properties.pkey_interface.qpn = tmp_val_u32 & 0x00ffffff;
        break;

    default:
        break;
    }

    SX_GET_REG_FIELD(ritr_reg->ttl_threshold, outbox, REG_TTLTH_OFFSET);
    SX_GET_REG_FIELD(ritr_reg->mtu, outbox, REG_MTU_OFFSET);

    SX_GET_REG_FIELD(tmp_val_u32, outbox, REG_INGRESS_CNTR_SET_OFFSET);
    ritr_reg->ingress_counter_set.type = (tmp_val_u32 >> 24) & 0xFF;
    ritr_reg->ingress_counter_set.type = tmp_val_u32 & 0xFFFFFF;
    SX_GET_REG_FIELD(tmp_val_u32, outbox, REG_EGRESS_CNTR_SET_OFFSET);
    ritr_reg->egress_counter_set.type = (tmp_val_u32 >> 24) & 0xFF;
    ritr_reg->egress_counter_set.type = tmp_val_u32 & 0xFFFFFF;

    return 0;
}

int sx_ACCESS_REG_RITR(struct sx_dev *dev, struct ku_access_ritr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __RITR_encode,
                                  __RITR_decode,
                                  RITR_REG_LEN,
                                  &reg_data->ritr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_RITR);


/************************************************
 * RUFT
 ***********************************************/
#define REG_VALID_TYPE_OFFSET     0x14
#define REG_OP_ACT_OFFSET         0x15
#define REG_OFFSET                0x16
#define REG_RUFT_VRID_OFFSET      0x18
#define REG_DIP_OFFSET            0x24
#define REG_DIP_MASK_OFFSET       0x34
#define REG_ECMP_HASH_OFFSET      0x68
#define REG_ECMP_HASH_MASK_OFFSET 0x6C
#define REG_TRAP_ACTION_OFFSET    0x74
#define REG_TRAP_GROUP_OFFSET     0x75
#define REG_TRAP_ID_OFFSET        0x76
#define REG_MIRROR_DST_OFFSET     0x78
#define REG_PRIO_QOS_OFFSET       0x79
#define REG_EGRESS_RIF_OFFSET     0x86
#define REG_ECMP_SIZE_OFFSET      0x88
#define REG_TABLE_OFFSET          0x89
#define REG_ADJ_IDX_OFFSET        0x8A
#define RUFT_REG_LEN              0x1F

static int __RUFT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ruft_reg *ruft_reg = (struct ku_ruft_reg*)ku_reg;
    u8                  tmp_val_u8;
    u16                 tmp_val_u16;
    int                 i;

    tmp_val_u8 = 0;
    tmp_val_u8 |= (ruft_reg->valid & 1) << 7;
    tmp_val_u8 |= (ruft_reg->route_type & 3);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_VALID_TYPE_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (ruft_reg->operation & 7) << 4;
    tmp_val_u8 |= (ruft_reg->activity & 1);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_OP_ACT_OFFSET);
    SX_PUT_REG_FIELD(inbox, ruft_reg->offset, REG_OFFSET);
    SX_PUT_REG_FIELD(inbox, ruft_reg->router, REG_RUFT_VRID_OFFSET);
    for (i = 0; i <= 3; i++) {
        SX_PUT_REG_FIELD(inbox, ruft_reg->destination_ip[i], (REG_DIP_OFFSET + (i * 4)));
        SX_PUT_REG_FIELD(inbox, ruft_reg->destination_ip_mask[i], (REG_DIP_MASK_OFFSET + (i * 4)));
    }
    SX_PUT_REG_FIELD(inbox, ruft_reg->ecmp_hash, REG_ECMP_HASH_OFFSET);
    SX_PUT_REG_FIELD(inbox, ruft_reg->ecmp_hash_mask, REG_ECMP_HASH_MASK_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (ruft_reg->route_action & 0xf) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_TRAP_ACTION_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (ruft_reg->trap_group & 0xf);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_TRAP_GROUP_OFFSET);
    tmp_val_u16 = 0;
    tmp_val_u16 |= (ruft_reg->trap_id & 0x01ff);
    SX_PUT_REG_FIELD(inbox, tmp_val_u16, REG_TRAP_ID_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (ruft_reg->mirror_enable & 1) << 7;
    tmp_val_u8 |= (ruft_reg->mirror_dst & 7);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_MIRROR_DST_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (ruft_reg->prio & 7) << 4;
    tmp_val_u8 |= (ruft_reg->qos & 3);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_PRIO_QOS_OFFSET);
    SX_PUT_REG_FIELD(inbox, ruft_reg->egress_rif, REG_EGRESS_RIF_OFFSET);
    tmp_val_u8 = ruft_reg->ecmp_size;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_ECMP_SIZE_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (ruft_reg->table & 7);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_TABLE_OFFSET);
    SX_PUT_REG_FIELD(inbox, ruft_reg->adjacency_index, REG_ADJ_IDX_OFFSET);
    return 0;
}

static int __RUFT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ruft_reg *ruft_reg = (struct ku_ruft_reg*)ku_reg;
    u8                  tmp_val_u8;
    u16                 tmp_val_u16;
    int                 i;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_VALID_TYPE_OFFSET);
    ruft_reg->valid = (tmp_val_u8 >> 7) & 1;
    ruft_reg->route_type = tmp_val_u8 & 3;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_OP_ACT_OFFSET);
    ruft_reg->operation = (tmp_val_u8 >> 4) & 7;
    ruft_reg->activity = tmp_val_u8 & 1;
    SX_GET_REG_FIELD(ruft_reg->offset, outbox, REG_OFFSET);
    SX_GET_REG_FIELD(ruft_reg->router, outbox, REG_RUFT_VRID_OFFSET);
    for (i = 0; i <= 3; i++) {
        SX_GET_REG_FIELD(ruft_reg->destination_ip[i], outbox, (REG_DIP_OFFSET + (i * 4)));
        SX_GET_REG_FIELD(ruft_reg->destination_ip_mask[i], outbox, (REG_DIP_MASK_OFFSET + (i * 4)));
    }
    SX_GET_REG_FIELD(ruft_reg->ecmp_hash, outbox, REG_ECMP_HASH_OFFSET);
    SX_GET_REG_FIELD(ruft_reg->ecmp_hash_mask, outbox, REG_ECMP_HASH_MASK_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_TRAP_ACTION_OFFSET);
    ruft_reg->route_action = (tmp_val_u8 >> 4) & 0xf;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_TRAP_GROUP_OFFSET);
    ruft_reg->trap_group = tmp_val_u8 & 0xf;
    SX_GET_REG_FIELD(tmp_val_u16, outbox, REG_TRAP_ID_OFFSET);
    ruft_reg->trap_id = tmp_val_u16 & 0x01ff;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_MIRROR_DST_OFFSET);
    ruft_reg->mirror_enable = (tmp_val_u8 >> 7) & 1;
    ruft_reg->mirror_dst = tmp_val_u8 & 7;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_PRIO_QOS_OFFSET);
    ruft_reg->prio = (tmp_val_u8 >> 4) & 7;
    ruft_reg->qos = tmp_val_u8 & 3;
    SX_GET_REG_FIELD(ruft_reg->egress_rif, outbox, REG_EGRESS_RIF_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_ECMP_SIZE_OFFSET);
    ruft_reg->ecmp_size = tmp_val_u8;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_TABLE_OFFSET);
    ruft_reg->table = tmp_val_u8 & 7;
    SX_GET_REG_FIELD(ruft_reg->adjacency_index, outbox, REG_ADJ_IDX_OFFSET);
    return 0;
}

int sx_ACCESS_REG_RUFT(struct sx_dev *dev, struct ku_access_ruft_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __RUFT_encode,
                                  __RUFT_decode,
                                  RUFT_REG_LEN,
                                  &reg_data->ruft_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_RUFT);


/************************************************
 * MPSC
 ***********************************************/
#define REG_LOCAL_PORT_OFFSET 0x15
#define REG_C_E_CONG_OFFSET   0x18
#define REG_C_BIT_N           7
#define REG_E_BIT_N           6
#define REG_CONG_BIT_N        5
#define REG_RATE_OFFSET       0x1C
#define REG_COUNT_DROP_OFFSET 0x20
#define MPSC_REG_LEN          0x6

static int __MPSC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mpsc_reg *mpsc_reg = (struct ku_mpsc_reg*)ku_reg;
    u8                  tmp = 0;

    SX_PUT_REG_FIELD(inbox, mpsc_reg->local_port, REG_LOCAL_PORT_OFFSET);
    tmp |= mpsc_reg->clear_count ? (1 << REG_C_BIT_N) : 0;
    tmp |= mpsc_reg->enable ? (1 << REG_E_BIT_N) : 0;
    tmp |= mpsc_reg->cong ? (1 << REG_CONG_BIT_N) : 0;
    SX_PUT_REG_FIELD(inbox, tmp, REG_C_E_CONG_OFFSET);
    SX_PUT_REG_FIELD(inbox, mpsc_reg->rate, REG_RATE_OFFSET);
    return 0;
}

static int __MPSC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mpsc_reg *mpsc_reg = (struct ku_mpsc_reg*)ku_reg;
    u8                  tmp;

    SX_GET_REG_FIELD(mpsc_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(tmp, outbox, REG_C_E_CONG_OFFSET);
    mpsc_reg->enable = tmp & (1 << REG_E_BIT_N) ? 1 : 0;
    mpsc_reg->cong = tmp & (1 << REG_CONG_BIT_N) ? 1 : 0;
    SX_GET_REG_FIELD(mpsc_reg->rate, outbox, REG_RATE_OFFSET);
    SX_GET_REG_FIELD(mpsc_reg->count_drops, outbox, REG_COUNT_DROP_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MPSC(struct sx_dev *dev, struct ku_access_mpsc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MPSC_encode,
                                  __MPSC_decode,
                                  MPSC_REG_LEN,
                                  &reg_data->mpsc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MPSC);


/************************************************
 * MLCR
 ***********************************************/
#define REG_LOCAL_PORT_OFFSET           0x15
#define REG_LED_TYPE_OFFSET             0x17
#define REG_BEACON_DURATION_OFFSET      0x1a
#define REG_BEACON_REMAIN_OFFSET        0x1e
#define REG_CAP_LOCAL_OR_UID_ONLY_BIT_N 4
#define MLCR_REG_LEN                    0x4

static int __MLCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mlcr_reg *mlcr_reg = (struct ku_mlcr_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mlcr_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, mlcr_reg->led_type, REG_LED_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mlcr_reg->beacon_duration, REG_BEACON_DURATION_OFFSET);
    SX_PUT_REG_FIELD(inbox, mlcr_reg->beacon_remain, REG_BEACON_REMAIN_OFFSET);
    return 0;
}

static int __MLCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mlcr_reg *mlcr_reg = (struct ku_mlcr_reg*)ku_reg;
    u8                  tmp_u8;

    SX_GET_REG_FIELD(mlcr_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(tmp_u8, outbox, REG_LED_TYPE_OFFSET);
    mlcr_reg->cap_local_or_uid_only = tmp_u8 & (1 << REG_CAP_LOCAL_OR_UID_ONLY_BIT_N) ? 1 : 0;
    mlcr_reg->led_type = tmp_u8 & 0xf;
    SX_GET_REG_FIELD(mlcr_reg->beacon_duration, outbox, REG_BEACON_DURATION_OFFSET);
    SX_GET_REG_FIELD(mlcr_reg->beacon_remain, outbox, REG_BEACON_REMAIN_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MLCR(struct sx_dev *dev, struct ku_access_mlcr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MLCR_encode,
                                  __MLCR_decode,
                                  MLCR_REG_LEN,
                                  &reg_data->mlcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MLCR);


/************************************************
 * MOGCR
 ***********************************************/
#define PTP_EFTC_BIT                          0
#define PTP_IFTC_BIT                          1
#define REG_MOGCR_FTC_OFFSET                  0x17
#define REG_MOGCR_MIRROR_LATENCY_SCALE_OFFSET 0x1A
#define MOGCR_REG_LEN                         0x2

static int __MOGCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mogcr_reg *mogcr_reg = (struct ku_mogcr_reg*)ku_reg;
    u8                   ftc = 0;

    ftc |= mogcr_reg->ptp_iftc << PTP_IFTC_BIT;
    ftc |= mogcr_reg->ptp_eftc << PTP_EFTC_BIT;
    SX_PUT_REG_FIELD(inbox, ftc, REG_MOGCR_FTC_OFFSET);
    SX_PUT_REG_FIELD(inbox, mogcr_reg->mirror_latency_scale, REG_MOGCR_MIRROR_LATENCY_SCALE_OFFSET);
    return 0;
}

static int __MOGCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mogcr_reg *mogcr_reg = (struct ku_mogcr_reg*)ku_reg;
    u8                   ftc;

    SX_GET_REG_FIELD(ftc, outbox, REG_MOGCR_FTC_OFFSET);
    mogcr_reg->ptp_iftc = !!(ftc & PTP_IFTC_BIT);
    mogcr_reg->ptp_eftc = !!(ftc & PTP_EFTC_BIT);
    SX_GET_REG_FIELD(mogcr_reg->mirror_latency_scale, outbox, REG_MOGCR_MIRROR_LATENCY_SCALE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MOGCR(struct sx_dev *dev, struct ku_access_mogcr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MOGCR_encode,
                                  __MOGCR_decode,
                                  MOGCR_REG_LEN,
                                  &reg_data->mogcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MOGCR);


/************************************************
 * MTPPPC
 ***********************************************/
#define REG_MTPPPC_WRITE_ENABLE_OFFSET           0x17
#define REG_MTPPPC_ING_TIMESTAMP_MSG_TYPE_OFFSET 0x1E
#define REG_MTPPPC_EGR_TIMESTAMP_MSG_TYPE_OFFSET 0x22
#define REG_MTPPPC_GM_LOCAL_PORT_0_OFFSET        0x37
#define REG_MTPPPC_GM_LOCAL_PORT_1_OFFSET        0x3A
#define MTPPPC_REG_LEN                           0x6

static int __MTPPPC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtpppc_reg *mtpppc_reg = (struct ku_mtpppc_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mtpppc_reg->we, REG_MTPPPC_WRITE_ENABLE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpppc_reg->ing_timestape_message_type, REG_MTPPPC_ING_TIMESTAMP_MSG_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpppc_reg->egr_timestape_message_type, REG_MTPPPC_EGR_TIMESTAMP_MSG_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpppc_reg->gm_local_port_0, REG_MTPPPC_GM_LOCAL_PORT_0_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpppc_reg->gm_local_port_1, REG_MTPPPC_GM_LOCAL_PORT_1_OFFSET);
    return 0;
}

static int __MTPPPC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtpppc_reg *mtpppc_reg = (struct ku_mtpppc_reg*)ku_reg;

    SX_GET_REG_FIELD(mtpppc_reg->ing_timestape_message_type, outbox, REG_MTPPPC_ING_TIMESTAMP_MSG_TYPE_OFFSET);
    SX_GET_REG_FIELD(mtpppc_reg->egr_timestape_message_type, outbox, REG_MTPPPC_EGR_TIMESTAMP_MSG_TYPE_OFFSET);
    SX_GET_REG_FIELD(mtpppc_reg->gm_local_port_0, outbox, REG_MTPPPC_GM_LOCAL_PORT_0_OFFSET);
    SX_GET_REG_FIELD(mtpppc_reg->gm_local_port_1, outbox, REG_MTPPPC_GM_LOCAL_PORT_1_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MTPPPC(struct sx_dev *dev, struct ku_access_mtpppc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTPPPC_encode,
                                  __MTPPPC_decode,
                                  MTPPPC_REG_LEN,
                                  &reg_data->mtpppc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTPPPC);


/************************************************
 * MTPTPT
 ***********************************************/
#define REG_MTPTPT_TRAP_ID_OFFSET  0x17
#define REG_MTPTPT_MSG_TYPE_OFFSET 0x1a
#define MTPTPT_REG_LEN             0x6

static int __MTPTPT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtptpt_reg *mtptpt_reg = (struct ku_mtptpt_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mtptpt_reg->trap_id, REG_MTPTPT_TRAP_ID_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtptpt_reg->message_type, REG_MTPTPT_MSG_TYPE_OFFSET);
    return 0;
}

static int __MTPTPT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtptpt_reg *mtptpt_reg = (struct ku_mtptpt_reg*)ku_reg;

    SX_GET_REG_FIELD(mtptpt_reg->trap_id, outbox, REG_MTPTPT_TRAP_ID_OFFSET);
    SX_GET_REG_FIELD(mtptpt_reg->message_type, outbox, REG_MTPTPT_MSG_TYPE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MTPTPT(struct sx_dev *dev, struct ku_access_mtptpt_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTPTPT_encode,
                                  __MTPTPT_decode,
                                  MTPTPT_REG_LEN,
                                  &reg_data->mtptpt_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTPTPT);


/************************************************
 * MTPPTR
 ***********************************************/
#define REG_MTPPTR_LOCAL_PORT_OFFSET   0x15
#define REG_MTPPTR_DIR_OFFSET          0x17
#define REG_MTPPTR_CLR_READ_ONE_OFFSET 0x18
#define REG_MTPPTR_OVF_OFFSET          0x1b
#define REG_MTPPTR_NUM_REC_OFFSET      0x1F
#define REG_MTPPTR_RECORDS_OFFSET      0x24
#define REG_CLR_BITN                   7
#define MTPPTR_REG_LEN                 0x14

static int __MTPPTR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtpptr_reg *mtpptr_reg = (struct ku_mtpptr_reg*)ku_reg;
    u8                    clear_read_one;

    clear_read_one = mtpptr_reg->clr << REG_CLR_BITN;
    SX_PUT_REG_FIELD(inbox, mtpptr_reg->dir, REG_MTPPTR_DIR_OFFSET);
    SX_PUT_REG_FIELD(inbox, clear_read_one, REG_MTPPTR_CLR_READ_ONE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpptr_reg->local_port, REG_MTPPTR_LOCAL_PORT_OFFSET);
    return 0;
}

static int __MTPPTR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtpptr_reg *mtpptr_reg = (struct ku_mtpptr_reg*)ku_reg;
    u8                    to_host_order = *(u8*)context;
    int                   start_record_offset = REG_MTPPTR_RECORDS_OFFSET;
    int                   i;

    if (to_host_order) {
        SX_GET_REG_FIELD(mtpptr_reg->num_record, outbox, REG_MTPPTR_NUM_REC_OFFSET);
        SX_GET_REG_FIELD(mtpptr_reg->ovf, outbox, REG_MTPPTR_OVF_OFFSET);
        start_record_offset = REG_MTPPTR_RECORDS_OFFSET;
        for (i = 0; i < mtpptr_reg->num_record; i++) {
            SX_GET_REG_FIELD(mtpptr_reg->records[i].domain_number, outbox, start_record_offset + 3);
            SX_GET_REG_FIELD(mtpptr_reg->records[i].message_type, outbox, start_record_offset + 2);
            SX_GET_REG_FIELD(mtpptr_reg->records[i].sequence_id, outbox, start_record_offset + 6);
            SX_GET_REG_FIELD(mtpptr_reg->records[i].timestamp, outbox, start_record_offset + 8);
            start_record_offset += 16;
        }
    } else {
        /* keep it in network order */
        memcpy(mtpptr_reg, outbox, sizeof(*mtpptr_reg));
    }

    return 0;
}

int sx_ACCESS_REG_MTPPTR(struct sx_dev *dev, struct ku_access_mtpptr_reg *reg_data, u8 to_host_order)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTPPTR_encode,
                                  __MTPPTR_decode,
                                  MTPPTR_REG_LEN,
                                  &reg_data->mtpptr_reg,
                                  (void*)&to_host_order);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTPPTR);

/************************************************
 * MTPPS
 ***********************************************/
#define REG_MTPPS_CAP_NUMBER_OF_PPS_PINS_OFFSET           0x15
#define REG_MTPPS_CAP_MAX_NUM_OF_PPS_IN_PINS              0x16
#define REG_MTPPS_CAP_MAX_NUM_OF_PPS_OUT_PINS             0x17
#define REG_MTPPS_CAP_PIN_3_MODE_OFFSET                   0x1c
#define REG_MTPPS_CAP_PIN_2_MODE_OFFSET                   0x1d
#define REG_MTPPS_CAP_PIN_1_MODE_OFFSET                   0x1e
#define REG_MTPPS_CAP_PIN_0_MODE_OFFSET                   0x1f
#define REG_MTPPS_CAP_PIN_7_MODE_OFFSET                   0x20
#define REG_MTPPS_CAP_PIN_6_MODE_OFFSET                   0x21
#define REG_MTPPS_CAP_PIN_5_MODE_OFFSET                   0x22
#define REG_MTPPS_CAP_PIN_4_MODE_OFFSET                   0x23
#define REG_MTPPS_FIELD_SELECT_OFFSET                     0x24
#define REG_MTPPS_ENABLE_OFFSET                           0x34
#define REG_MTPPS_PATTERN_OFFSET                          0x35
#define REG_MTPPS_PIN_MODE_OFFSET                         0x36
#define REG_MTPPS_PIN_OFFSET                              0x37
#define REG_MTPPS_TIME_STAMP_OFFSET                       0x3c
#define REG_MTPPS_OUT_PULSE_DURATION_OFFSET               0x46
#define REG_MTPPS_OUT_PERIODIC_ADJUSTMENT_OFFSET          0x44
#define REG_MTPPS_ENHANCED_OUT_PERIODIC_ADJUSTMENT_OFFSET 0x48
#define REG_MTPPS_NPPS_OFFSET                             0x4f
#define MTPPS_REG_LEN                                     15

static int __MTPPS_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtpps_reg *mtpps_reg = (struct ku_mtpps_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mtpps_reg->field_select, REG_MTPPS_FIELD_SELECT_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpps_reg->enable, REG_MTPPS_ENABLE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpps_reg->pattern, REG_MTPPS_PATTERN_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpps_reg->pin_mode, REG_MTPPS_PIN_MODE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpps_reg->pin, REG_MTPPS_PIN_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpps_reg->time_stamp, REG_MTPPS_TIME_STAMP_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpps_reg->out_pulse_duration, REG_MTPPS_OUT_PULSE_DURATION_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpps_reg->out_periodic_adjustment, REG_MTPPS_OUT_PERIODIC_ADJUSTMENT_OFFSET);
    SX_PUT_REG_FIELD(inbox,
                     mtpps_reg->enhanced_out_periodic_adjustment,
                     REG_MTPPS_ENHANCED_OUT_PERIODIC_ADJUSTMENT_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpps_reg->npps, REG_MTPPS_NPPS_OFFSET);
    return 0;
}

static int __MTPPS_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtpps_reg *mtpps_reg = (struct ku_mtpps_reg*)ku_reg;

    SX_GET_REG_FIELD(mtpps_reg->cap_number_of_pps_pins, outbox, REG_MTPPS_CAP_NUMBER_OF_PPS_PINS_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->cap_number_of_pps_pins, outbox, REG_MTPPS_CAP_NUMBER_OF_PPS_PINS_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->cap_max_num_of_pps_in_pins, outbox, REG_MTPPS_CAP_MAX_NUM_OF_PPS_IN_PINS);
    SX_GET_REG_FIELD(mtpps_reg->cap_max_num_of_pps_out_pins, outbox, REG_MTPPS_CAP_MAX_NUM_OF_PPS_OUT_PINS);
    SX_GET_REG_FIELD(mtpps_reg->cap_pin_0_mode, outbox, REG_MTPPS_CAP_PIN_0_MODE_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->cap_pin_1_mode, outbox, REG_MTPPS_CAP_PIN_1_MODE_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->cap_pin_2_mode, outbox, REG_MTPPS_CAP_PIN_2_MODE_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->cap_pin_3_mode, outbox, REG_MTPPS_CAP_PIN_3_MODE_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->cap_pin_4_mode, outbox, REG_MTPPS_CAP_PIN_4_MODE_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->cap_pin_5_mode, outbox, REG_MTPPS_CAP_PIN_5_MODE_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->cap_pin_6_mode, outbox, REG_MTPPS_CAP_PIN_6_MODE_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->cap_pin_7_mode, outbox, REG_MTPPS_CAP_PIN_7_MODE_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->enable, outbox, REG_MTPPS_ENABLE_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->pattern, outbox, REG_MTPPS_PATTERN_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->pin_mode, outbox, REG_MTPPS_PIN_MODE_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->time_stamp, outbox, REG_MTPPS_TIME_STAMP_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->out_pulse_duration, outbox, REG_MTPPS_OUT_PULSE_DURATION_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->out_periodic_adjustment, outbox, REG_MTPPS_OUT_PERIODIC_ADJUSTMENT_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->enhanced_out_periodic_adjustment,
                     outbox,
                     REG_MTPPS_ENHANCED_OUT_PERIODIC_ADJUSTMENT_OFFSET);
    SX_GET_REG_FIELD(mtpps_reg->npps, outbox, REG_MTPPS_NPPS_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MTPPS(struct sx_dev *dev, struct ku_access_mtpps_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTPPS_encode,
                                  __MTPPS_decode,
                                  MTPPS_REG_LEN,
                                  &reg_data->mtpps_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTPPS);


/************************************************
 * SBCTC
 ***********************************************/
#define REG_SBCTC_LOCAL_PORT_OFFSET 0x15
#define REG_SBCTC_EN_CONFIG_OFFSET  0x18
#define REG_SBCTC_EVENT_OFFSET      0x1B
#define REG_SBCTC_TCLASS_EN_OFFSET  0x1C
#define REG_SBCTC_THR_MAX_OFFSET    0x24
#define SBCTC_REG_LEN               0x6

static int __SBCTC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sbctc_reg *sbctc_reg = (struct ku_sbctc_reg*)ku_reg;
    u8                   en_config;

    SX_PUT_REG_FIELD(inbox, sbctc_reg->local_port, REG_SBCTC_LOCAL_PORT_OFFSET);
    en_config = sbctc_reg->en_config << 7;
    SX_PUT_REG_FIELD(inbox, en_config, REG_SBCTC_EN_CONFIG_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctc_reg->event, REG_SBCTC_EVENT_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctc_reg->tclass_en, REG_SBCTC_TCLASS_EN_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctc_reg->thr_max, REG_SBCTC_THR_MAX_OFFSET);
    return 0;
}

static int __SBCTC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sbctc_reg *sbctc_reg = (struct ku_sbctc_reg*)ku_reg;

    SX_GET_REG_FIELD(sbctc_reg->event, outbox, REG_SBCTC_EVENT_OFFSET);
    SX_GET_REG_FIELD(sbctc_reg->tclass_en, outbox, REG_SBCTC_TCLASS_EN_OFFSET);
    SX_GET_REG_FIELD(sbctc_reg->thr_max, outbox, REG_SBCTC_THR_MAX_OFFSET);
    return 0;
}

int sx_ACCESS_REG_SBCTC(struct sx_dev *dev, struct ku_access_sbctc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SBCTC_encode,
                                  __SBCTC_decode,
                                  SBCTC_REG_LEN,
                                  &reg_data->sbctc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SBCTC);


/************************************************
 * SBGCR
 ***********************************************/
#define REG_SBGCR_TELE_ENTITY_FP_OFFSET 0x17
#define SBGCR_REG_LEN                   0x3

static int __SBGCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sbgcr_reg *sbgcr_reg = (struct ku_sbgcr_reg*)ku_reg;
    u8                   fp_entity;

    fp_entity = sbgcr_reg->tele_entity | (sbgcr_reg->cong_fp << 4);
    SX_PUT_REG_FIELD(inbox, fp_entity, REG_SBGCR_TELE_ENTITY_FP_OFFSET);
    return 0;
}

static int __SBGCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sbgcr_reg *sbgcr_reg = (struct ku_sbgcr_reg*)ku_reg;

    SX_GET_REG_FIELD(sbgcr_reg->tele_entity, outbox, REG_SBGCR_TELE_ENTITY_FP_OFFSET);
    return 0;
}

int sx_ACCESS_REG_SBGCR(struct sx_dev *dev, struct ku_access_sbgcr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SBGCR_encode,
                                  __SBGCR_decode,
                                  SBGCR_REG_LEN,
                                  &reg_data->sbgcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SBGCR);


/************************************************
 * SBCTR
 ***********************************************/
#define REG_SBCTR_IEVENT_OFFSET     0x14
#define REG_SBCTR_LOCAL_PORT_OFFSET 0x15
#define REG_SBCTR_FP_ENTITY_OFFSET  0x17
#define REG_SBCTR_TCLASS_EN_OFFSET  0x1C
#define SBCTR_REG_LEN               0x4

static int __SBCTR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sbctr_reg *sbctr_reg = (struct ku_sbctr_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, sbctr_reg->ievent, REG_SBCTR_IEVENT_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctr_reg->local_port, REG_SBCTR_LOCAL_PORT_OFFSET);
    return 0;
}

static int __SBCTR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sbctr_reg *sbctr_reg = (struct ku_sbctr_reg*)ku_reg;
    u8                   fp_entity;

    SX_GET_REG_FIELD(fp_entity, outbox, REG_SBCTR_FP_ENTITY_OFFSET);
    sbctr_reg->fp = (fp_entity >> 4) & 0x1;
    sbctr_reg->entity = fp_entity & 0x03;
    SX_GET_REG_FIELD(sbctr_reg->tclass_vec, outbox, REG_SBCTR_TCLASS_EN_OFFSET);
    return 0;
}

int sx_ACCESS_REG_SBCTR(struct sx_dev *dev, struct ku_access_sbctr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SBCTR_encode,
                                  __SBCTR_decode,
                                  SBCTR_REG_LEN,
                                  &reg_data->sbctr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SBCTR);


/************************************************
 * PPBMP
 ***********************************************/
#define REG_PPBMP_LOCAL_PORT_OFFSET          0x15
#define REG_PPBMP_PNAT_OFFSET                0x16
#define REG_PPBMP_MONITOR_GROUP_OFFSET       0x17
#define REG_PPBMP_ALARM_TH_MANTISSA_OFFSET   0x18
#define REG_PPBMP_ALARM_TH_EXP_OFFSET        0x19
#define REG_PPBMP_WARNING_TH_MANTISSA_OFFSET 0x1A
#define REG_PPBMP_WARNING_TH_EXP_OFFSET      0x1B
#define REG_PPBMP_NORMAL_TH_MANTISSA_OFFSET  0x1C
#define REG_PPBMP_NORMAL_TH_EXP_OFFSET       0x1D
#define PPBMP_REG_LEN                        0x3

static int __PPBMP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppbmp_reg *ppbmp_reg = (struct ku_ppbmp_reg*)ku_reg;
    u8                   pnat;

    pnat = ppbmp_reg->pnat >> 6;
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->local_port, REG_PPBMP_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pnat, REG_PPBMP_PNAT_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->monitor_group, REG_PPBMP_MONITOR_GROUP_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->monitor_params.alarm_th_mantissa, REG_PPBMP_ALARM_TH_MANTISSA_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->monitor_params.alarm_th_exp, REG_PPBMP_ALARM_TH_EXP_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->monitor_params.warning_th_mantissa, REG_PPBMP_WARNING_TH_MANTISSA_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->monitor_params.warning_th_exp, REG_PPBMP_WARNING_TH_EXP_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->monitor_params.normal_th_mantissa, REG_PPBMP_NORMAL_TH_MANTISSA_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->monitor_params.normal_th_exp, REG_PPBMP_NORMAL_TH_EXP_OFFSET);
    return 0;
}

static int __PPBMP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppbmp_reg *ppbmp_reg = (struct ku_ppbmp_reg*)ku_reg;

    SX_GET_REG_FIELD(ppbmp_reg->monitor_params.alarm_th_mantissa, outbox, REG_PPBMP_ALARM_TH_MANTISSA_OFFSET);
    SX_GET_REG_FIELD(ppbmp_reg->monitor_params.alarm_th_exp, outbox, REG_PPBMP_ALARM_TH_EXP_OFFSET);
    SX_GET_REG_FIELD(ppbmp_reg->monitor_params.warning_th_mantissa, outbox, REG_PPBMP_WARNING_TH_MANTISSA_OFFSET);
    SX_GET_REG_FIELD(ppbmp_reg->monitor_params.warning_th_exp, outbox, REG_PPBMP_WARNING_TH_EXP_OFFSET);
    SX_GET_REG_FIELD(ppbmp_reg->monitor_params.normal_th_mantissa, outbox, REG_PPBMP_NORMAL_TH_MANTISSA_OFFSET);
    SX_GET_REG_FIELD(ppbmp_reg->monitor_params.normal_th_exp, outbox, REG_PPBMP_NORMAL_TH_EXP_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PPBMP(struct sx_dev *dev, struct ku_access_ppbmp_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPBMP_encode,
                                  __PPBMP_decode,
                                  PPBMP_REG_LEN,
                                  &reg_data->ppbmp_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPBMP);


/************************************************
 * PPBMC
 ***********************************************/
#define REG_PPBMC_LOCAL_PORT_OFFSET        0x15
#define REG_PPBMC_PNAT_MONITOR_TYPE_OFFSET 0x16
#define REG_PPBMC_E_EVENT_CTRL_OFFSET      0x18
#define REG_PPBMC_MONITOR_CTRL_OFFSET      0x19
#define REG_PPBMC_MONITOR_STATE_OFFSET     0x1B
#define PPBMC_REG_LEN                      0x3

static int __PPBMC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppbmc_reg *ppbmc_reg = (struct ku_ppbmc_reg*)ku_reg;
    u8                   e_event_ctrl;
    u8                   pnat_monitor_type;

    e_event_ctrl = ppbmc_reg->e << 6 | ((ppbmc_reg->event_ctrl) & 0xF);
    pnat_monitor_type = ppbmc_reg->pnat << 6;
    SX_PUT_REG_FIELD(inbox, ppbmc_reg->local_port, REG_PPBMC_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pnat_monitor_type, REG_PPBMC_PNAT_MONITOR_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, e_event_ctrl, REG_PPBMC_E_EVENT_CTRL_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmc_reg->monitor_ctrl, REG_PPBMC_MONITOR_CTRL_OFFSET);
    return 0;
}

static int __PPBMC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppbmc_reg *ppbmc_reg = (struct ku_ppbmc_reg*)ku_reg;
    u8                   e_event_ctrl;
    u8                   pnat_monitor_type;

    SX_GET_REG_FIELD(pnat_monitor_type, outbox, REG_PPBMC_PNAT_MONITOR_TYPE_OFFSET);
    ppbmc_reg->monitor_type = pnat_monitor_type & 0xF;
    SX_GET_REG_FIELD(e_event_ctrl, outbox, REG_PPBMC_E_EVENT_CTRL_OFFSET);
    ppbmc_reg->e = (e_event_ctrl >> 6) & 0x3;
    ppbmc_reg->event_ctrl = e_event_ctrl & 0xF;
    SX_GET_REG_FIELD(ppbmc_reg->monitor_ctrl, outbox, REG_PPBMC_MONITOR_CTRL_OFFSET);
    SX_GET_REG_FIELD(ppbmc_reg->monitor_state, outbox, REG_PPBMC_MONITOR_STATE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PPBMC(struct sx_dev *dev, struct ku_access_ppbmc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPBMC_encode,
                                  __PPBMC_decode,
                                  PPBMC_REG_LEN,
                                  &reg_data->ppbmc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPBMC);


/************************************************
 * PPBME
 ***********************************************/
#define REG_PPBME_LOCAL_PORT_OFFSET        0x15
#define REG_PPBME_PNAT_MONITOR_TYPE_OFFSET 0x16
#define REG_PPBME_MONITOR_STATE_OFFSET     0x1B
#define PPBME_REG_LEN                      0x3

static int __PPBME_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppbme_reg *ppbme_reg = (struct ku_ppbme_reg*)ku_reg;
    u8                   pnat_monitor_type;

    pnat_monitor_type = (ppbme_reg->pnat << 6);
    SX_PUT_REG_FIELD(inbox, ppbme_reg->local_port, REG_PPBME_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pnat_monitor_type, REG_PPBME_PNAT_MONITOR_TYPE_OFFSET);
    return 0;
}

static int __PPBME_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppbme_reg *ppbme_reg = (struct ku_ppbme_reg*)ku_reg;
    u8                   pnat_monitor_type;

    SX_GET_REG_FIELD(pnat_monitor_type, outbox, REG_PPBME_PNAT_MONITOR_TYPE_OFFSET);
    ppbme_reg->monitor_type = pnat_monitor_type & 0xF;
    SX_GET_REG_FIELD(ppbme_reg->monitor_state, outbox, REG_PPBME_MONITOR_STATE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PPBME(struct sx_dev *dev, struct ku_access_ppbme_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PPBME_encode,
                                  __PPBME_decode,
                                  PPBME_REG_LEN,
                                  &reg_data->ppbme_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PPBME);


/************************************************
 * PDDR
 ***********************************************/
#define REG_LOCAL_PORT_OFFSET  0x15
#define REG_PNAT_OFFSET        0x16
#define REG_PAGE_SELECT_OFFSET 0x1B
#define REG_PAGE_DATA_OFFSET   0x1C
#define PDDR_REG_LEN           (0x40)

static int __PDDR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pddr_reg *pddr_reg = (struct ku_pddr_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, pddr_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pddr_reg->pnat << 6, REG_PNAT_OFFSET);
    SX_PUT_REG_FIELD(inbox, ((char)pddr_reg->page_select), REG_PAGE_SELECT_OFFSET);
    return 0;
}

static int __PDDR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pddr_reg *pddr_reg = (struct ku_pddr_reg*)ku_reg;

    switch ((pddr_page_options_t)pddr_reg->page_select) {
    case PDDR_PAGE_OPT_OPR_INFO_E:
        convert_pddr_oper_info((sxd_emad_pddr_oper_info_t*)(outbox - REG_START_OFFSET + REG_PAGE_DATA_OFFSET),
                               &pddr_reg->response.oper_info);
        break;

    case PDDR_PAGE_OPT_PHY_INFO_E:
        convert_pddr_phy_info((sxd_emad_pddr_phy_info_t*)(outbox - REG_START_OFFSET + REG_PAGE_DATA_OFFSET),
                              &pddr_reg->response.phy_info);
        break;

    case PDDR_PAGE_OPT_TROUBLESHOOT_E:
        covert_pddr_troubleshooting_info(
            (sx_emad_pddr_troubleshooting_info_t*)(outbox - REG_START_OFFSET + REG_PAGE_DATA_OFFSET),
            &pddr_reg->response.troubleshooting_info);
        break;

    case PDDR_PAGE_OPT_MODULE_INFO_E:
        convert_pddr_module_info((sxd_emad_pddr_module_info_t*)(outbox - REG_START_OFFSET + REG_PAGE_DATA_OFFSET),
                                 &pddr_reg->response.module_info);
        break;

    default:
        return -EINVAL;
    }

    return 0;
}

int sx_ACCESS_REG_PDDR(struct sx_dev *dev, struct ku_access_pddr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PDDR_encode,
                                  __PDDR_decode,
                                  PDDR_REG_LEN,
                                  &reg_data->pddr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PDDR);


/************************************************
 * MCION
 ***********************************************/
#define REG_MODULE_OFFSET               0x15
#define MCION_REG_LEN                   0x07
#define MCION_MODULE_STATUS_BITS_OFFSET 0x1a
#define MCION_MODULE_INPUTS_OFFSET      0x23
#define MCION_MODULE_INPUTS_MASK_OFFSET 0x27

static int __MCION_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mcion_reg *mcion_reg = (struct ku_mcion_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mcion_reg->module, REG_MODULE_OFFSET);
    SX_PUT_REG_FIELD(inbox, (mcion_reg->module_inputs & 0xF), MCION_MODULE_INPUTS_OFFSET);
    SX_PUT_REG_FIELD(inbox, (mcion_reg->module_inputs_mask & 0xF), MCION_MODULE_INPUTS_MASK_OFFSET);
    return 0;
}

static int __MCION_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mcion_reg *mcion_reg = (struct ku_mcion_reg*)ku_reg;
    u8                   tmp_u8;

    SX_GET_REG_FIELD(mcion_reg->module_status_bits, outbox, MCION_MODULE_STATUS_BITS_OFFSET);
    SX_GET_REG_FIELD(tmp_u8, outbox, MCION_MODULE_INPUTS_OFFSET);
    mcion_reg->module_inputs = tmp_u8 & 0xF;
    return 0;
}

int sx_ACCESS_REG_MCION(struct sx_dev *dev, struct ku_access_mcion_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MCION_encode,
                                  __MCION_decode,
                                  MCION_REG_LEN,
                                  &reg_data->mcion_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MCION);


/************************************************
 * PMMP
 ***********************************************/
#define REG_MODULE_OFFSET                               0x15
#define PMMP_REG_LEN                                    0x0c
#define PMMP_EEPROM_OVERRIDE_OFFSET                     0x1a
#define PMMP_QSFP_CABLE_BREAKOUT_OFFSET                 0x1e
#define PMMP_QSFP_ETHERNET_COMPLIANCE_CODE_OFFSET       0x1f
#define PMMP_QSFP_EXT_ETHERNET_COMPLIANCE_CODE_OFFSET   0x22
#define PMMP_QSFP_GIGA_ETHERNET_COMPLIANCE_CODE_OFFSET  0x23
#define PMMP_SFP_BIT_RATE_OFFSET                        0x29
#define PMMP_SFP_CABLE_TECHNOLOGY_OFFSET                0x2a
#define PMMP_SFP_TENGIG_ETHERNET_COMPLIANCE_CODE_OFFSET 0x2b
#define PMMP_SFP_EXT_ETHERNET_COMPLIANCE_CODE_OFFSET    0x2e
#define PMMP_SFP_ETHERNET_COMPLIANCE_CODE_OFFSET        0x2f
#define PMMP_CABLE_LENGTH_OFFSET                        0x37
#define PMMP_ATTENUATION_12G_OFFSET                     0x39
#define PMMP_ATTENUATION_7G_OFFSET                      0x3a
#define PMMP_ATTENUATION_5G_OFFSET                      0x3b
#define PMMP_MODULE_IDENTIFIER_OFFSET                   0x3f

static int __PMMP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmmp_reg *pmmp_reg = (struct ku_pmmp_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, pmmp_reg->module, REG_MODULE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmmp_reg->eeprom_override, PMMP_EEPROM_OVERRIDE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmmp_reg->qsfp_cable_breakout, PMMP_QSFP_CABLE_BREAKOUT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmmp_reg->qsfp_ethernet_compliance_code, PMMP_QSFP_ETHERNET_COMPLIANCE_CODE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmmp_reg->qsfp_ext_ethernet_compliance_code,
                     PMMP_QSFP_EXT_ETHERNET_COMPLIANCE_CODE_OFFSET);
    SX_PUT_REG_FIELD(inbox,
                     pmmp_reg->qsfp_giga_ethernet_compliance_code,
                     PMMP_QSFP_GIGA_ETHERNET_COMPLIANCE_CODE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmmp_reg->sfp_bit_rate, PMMP_SFP_BIT_RATE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmmp_reg->sfp_cable_technology, PMMP_SFP_CABLE_TECHNOLOGY_OFFSET);
    SX_PUT_REG_FIELD(inbox,
                     pmmp_reg->sfp_tengig_ethernet_compliance_code,
                     PMMP_SFP_TENGIG_ETHERNET_COMPLIANCE_CODE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmmp_reg->sfp_ext_ethernet_compliance_code, PMMP_SFP_EXT_ETHERNET_COMPLIANCE_CODE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmmp_reg->sfp_ethernet_compliance_code, PMMP_SFP_ETHERNET_COMPLIANCE_CODE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmmp_reg->cable_length, PMMP_CABLE_LENGTH_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmmp_reg->attenuation_12g, PMMP_ATTENUATION_12G_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmmp_reg->attenuation_7g, PMMP_ATTENUATION_7G_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmmp_reg->attenuation_5g, PMMP_ATTENUATION_5G_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmmp_reg->module_identifier, PMMP_MODULE_IDENTIFIER_OFFSET);
    return 0;
}

static int __PMMP_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pmmp_reg *pmmp_reg = (struct ku_pmmp_reg*)ku_reg;

    SX_GET_REG_FIELD(pmmp_reg->eeprom_override, outbox, PMMP_EEPROM_OVERRIDE_OFFSET);
    SX_GET_REG_FIELD(pmmp_reg->qsfp_cable_breakout, outbox, PMMP_QSFP_CABLE_BREAKOUT_OFFSET);
    SX_GET_REG_FIELD(pmmp_reg->qsfp_ethernet_compliance_code, outbox, PMMP_QSFP_ETHERNET_COMPLIANCE_CODE_OFFSET);
    SX_GET_REG_FIELD(pmmp_reg->qsfp_ext_ethernet_compliance_code, outbox,
                     PMMP_QSFP_EXT_ETHERNET_COMPLIANCE_CODE_OFFSET);
    SX_GET_REG_FIELD(pmmp_reg->qsfp_giga_ethernet_compliance_code,
                     outbox,
                     PMMP_QSFP_GIGA_ETHERNET_COMPLIANCE_CODE_OFFSET);
    SX_GET_REG_FIELD(pmmp_reg->sfp_bit_rate, outbox, PMMP_SFP_BIT_RATE_OFFSET);
    SX_GET_REG_FIELD(pmmp_reg->sfp_cable_technology, outbox, PMMP_SFP_CABLE_TECHNOLOGY_OFFSET);
    SX_GET_REG_FIELD(pmmp_reg->sfp_tengig_ethernet_compliance_code,
                     outbox,
                     PMMP_SFP_TENGIG_ETHERNET_COMPLIANCE_CODE_OFFSET);
    SX_GET_REG_FIELD(pmmp_reg->sfp_ext_ethernet_compliance_code, outbox, PMMP_SFP_EXT_ETHERNET_COMPLIANCE_CODE_OFFSET);
    SX_GET_REG_FIELD(pmmp_reg->sfp_ethernet_compliance_code, outbox, PMMP_SFP_ETHERNET_COMPLIANCE_CODE_OFFSET);
    SX_GET_REG_FIELD(pmmp_reg->cable_length, outbox, PMMP_CABLE_LENGTH_OFFSET);
    SX_GET_REG_FIELD(pmmp_reg->attenuation_12g, outbox, PMMP_ATTENUATION_12G_OFFSET);
    SX_GET_REG_FIELD(pmmp_reg->attenuation_7g, outbox, PMMP_ATTENUATION_7G_OFFSET);
    SX_GET_REG_FIELD(pmmp_reg->attenuation_5g, outbox, PMMP_ATTENUATION_5G_OFFSET);
    SX_GET_REG_FIELD(pmmp_reg->module_identifier, outbox, PMMP_MODULE_IDENTIFIER_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PMMP(struct sx_dev *dev, struct ku_access_pmmp_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __PMMP_encode,
                                  __PMMP_decode,
                                  PMMP_REG_LEN,
                                  &reg_data->pmmp_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_PMMP);


/************************************************
 * QPCR
 ***********************************************/
#define QPCR_REG_LEN               0x28
#define QPCR_LOCAL_PORT_OFFSET     0x15
#define QPCR_GLOBAL_PID_OFFSET     0x16
#define QPCR_COUNTER_OFFSET        0x18
#define QPCR_COLOR_TO_TYPE_OFFSET  0x1a
#define QPCR_MODE_OFFSET           0x1b
#define QPCR_CBS_OFFSET            0x1c
#define QPCR_EBS_OFFSET            0x1d
#define QPCR_CIR_OFFSET            0x20
#define QPCR_EIR_OFFSET            0x24
#define QPCR_EXCEED_ACTION_OFFSET  0x2b
#define QPCR_VIOLATE_ACTION_OFFSET 0x2f
#define QPCR_VIOLATE_COUNT_OFFSET  0x34

static int __QPCR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_qpcr_reg *qpcr_reg = (struct ku_qpcr_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;
    u16                 tmp_val_u16 = 0;

    SX_PUT_REG_FIELD(inbox, qpcr_reg->port, QPCR_LOCAL_PORT_OFFSET);
    tmp_val_u16 |= (qpcr_reg->pid & 0x3fff);
    tmp_val_u16 |= (qpcr_reg->global_policer & 3) << 14;
    SX_PUT_REG_FIELD(inbox, tmp_val_u16, QPCR_GLOBAL_PID_OFFSET);
    tmp_val_u8 |= (qpcr_reg->clear_counter & 1) << 7;
    tmp_val_u8 |= (qpcr_reg->add_counter & 1) << 6;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, QPCR_COUNTER_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (qpcr_reg->color_aware & 1) << 7;
    tmp_val_u8 |= (qpcr_reg->use_bytes & 1) << 6;
    tmp_val_u8 |= (qpcr_reg->ir_units & 1) << 4;
    tmp_val_u8 |= (qpcr_reg->type & 3);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, QPCR_COLOR_TO_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->mode, QPCR_MODE_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->committed_burst_size, QPCR_CBS_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->extended_burst_size, QPCR_EBS_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->committed_information_rate, QPCR_CIR_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->excess_information_rate, QPCR_EIR_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->exceed_action, QPCR_EXCEED_ACTION_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->violate_action, QPCR_VIOLATE_ACTION_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->violate_count, QPCR_VIOLATE_COUNT_OFFSET);
    return 0;
}

static int __QPCR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_qpcr_reg *qpcr_reg = (struct ku_qpcr_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;
    u16                 tmp_val_u16 = 0;

    SX_GET_REG_FIELD(qpcr_reg->port, outbox, QPCR_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u16, outbox, QPCR_GLOBAL_PID_OFFSET);
    qpcr_reg->global_policer = (tmp_val_u16 >> 14) & 3;
    qpcr_reg->pid = (tmp_val_u16) & 0x3fff;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, QPCR_COUNTER_OFFSET);
    qpcr_reg->clear_counter = (tmp_val_u8 >> 7) & 1;
    qpcr_reg->add_counter = (tmp_val_u8 >> 6) & 1;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, QPCR_COLOR_TO_TYPE_OFFSET);
    qpcr_reg->color_aware = (tmp_val_u8 >> 7) & 1;
    qpcr_reg->use_bytes = (tmp_val_u8 >> 6) & 1;
    qpcr_reg->ir_units = (tmp_val_u8 >> 4) & 1;
    qpcr_reg->type = (tmp_val_u8) & 3;

    SX_GET_REG_FIELD(qpcr_reg->mode, outbox, QPCR_MODE_OFFSET);
    SX_GET_REG_FIELD(qpcr_reg->committed_burst_size, outbox, QPCR_CBS_OFFSET);
    SX_GET_REG_FIELD(qpcr_reg->extended_burst_size, outbox, QPCR_EBS_OFFSET);
    SX_GET_REG_FIELD(qpcr_reg->committed_information_rate, outbox, QPCR_CIR_OFFSET);
    SX_GET_REG_FIELD(qpcr_reg->excess_information_rate, outbox, QPCR_EIR_OFFSET);
    SX_GET_REG_FIELD(qpcr_reg->exceed_action, outbox, QPCR_EXCEED_ACTION_OFFSET);
    SX_GET_REG_FIELD(qpcr_reg->violate_action, outbox, QPCR_VIOLATE_ACTION_OFFSET);
    SX_GET_REG_FIELD(qpcr_reg->violate_count, outbox, QPCR_VIOLATE_COUNT_OFFSET);
    return 0;
}

int sx_ACCESS_REG_QPCR(struct sx_dev *dev, struct ku_access_qpcr_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __QPCR_encode,
                                  __QPCR_decode,
                                  QPCR_REG_LEN,
                                  &reg_data->qpcr_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_QPCR);


/************************************************
 * RAW_BUFF
 ***********************************************/

int sx_ACCESS_REG_RAW_BUFF(struct sx_dev *dev, struct ku_access_reg_raw_buff *raw_data)
{
    struct sx_cmd_mailbox *in_mailbox;
    struct sx_cmd_mailbox *out_mailbox;
    u32                   *inbox;
    u32                   *outbox;
    int                    err;

    if (SX_MAILBOX_SIZE < raw_data->raw_buff.size) {
        sx_warn(dev, "Cannot send the raw register access request "
                "since the mailbox size is too small\n");
        return -ENOMEM;
    }

    in_mailbox = sx_alloc_cmd_mailbox(dev, raw_data->dev_id);
    if (IS_ERR(in_mailbox)) {
        return PTR_ERR(in_mailbox);
    }

    out_mailbox = sx_alloc_cmd_mailbox(dev, raw_data->dev_id);
    if (IS_ERR(out_mailbox)) {
        err = PTR_ERR(out_mailbox);
        goto out_free;
    }

    inbox = in_mailbox->buf;
    memset(inbox, 0, SX_MAILBOX_SIZE);
    outbox = out_mailbox->buf;

    err = copy_from_user(inbox, raw_data->raw_buff.buff,
                         raw_data->raw_buff.size);
    if (err) {
        goto out;
    }

    err = sx_cmd_box(dev, raw_data->dev_id, in_mailbox, out_mailbox, 0, 0,
                     SX_CMD_ACCESS_REG, SX_CMD_TIME_CLASS_A,
                     raw_data->raw_buff.size);
    if (err) {
        goto out;
    }

    err = copy_to_user(raw_data->raw_buff.buff, outbox,
                       raw_data->raw_buff.size);

out:
    sx_free_cmd_mailbox(dev, out_mailbox);
out_free:
    sx_free_cmd_mailbox(dev, in_mailbox);
    return err;
}
