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

#include "fw.h"
#include "sx.h"
#include "sgmii.h"
#include "cq.h"
#include "fw_internal.h"
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>

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
    if (reg_decode_cb && ((flags & SX_ACCESS_REG_F_SET_AND_GET) || (op_tlv->method == 0x01))) { /* 0x01 = Query */
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

/****************************************************
 * SPZR (wrapper)
 *
 * sx_ib module is calling the SPZR wrapper.
 * on OOB system, it will call the register by EMAD
 * Otherwise, it will call it with Command Interface
 ***************************************************/
int sx_ACCESS_REG_SPZR_wrapper(struct sx_dev *dev, struct ku_access_spzr_reg *reg_data)
{
    if (is_sgmii_supported()) {
        /* SPZR is called in bootstrap and when working with OOB, we don't have PCI to work with, only I2C.
         * The problem is that I2C is enabled only on one management board. We must call this register from both
         * management boards and the only way to do that is with SGMII.
         */
        return sgmii_emad_access_spzr(reg_data->dev_id, &reg_data->spzr_reg);
    }

    return sx_ACCESS_REG_SPZR(dev, reg_data);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SPZR_wrapper);

/************************************************
 * PLIB
 ***********************************************/
#define REG_LOCAL_PORT_OFFSET     0x15
#define REG_LOCAL_PORT_MSB_OFFSET 0x16
#define REG_IB_PORT_OFFSET        0x17

static int __PLIB_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_plib_reg *plib_reg = (struct ku_plib_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, plib_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, ((plib_reg->lp_msb & 0x3) << 4), REG_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, plib_reg->ib_port, REG_IB_PORT_OFFSET);

    return 0;
}

static int __PLIB_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_plib_reg *plib_reg = (struct ku_plib_reg*)ku_reg;

    SX_GET_REG_FIELD(plib_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(plib_reg->lp_msb, outbox, REG_LOCAL_PORT_MSB_OFFSET);
    plib_reg->lp_msb >>= 4;
    plib_reg->lp_msb &= 0x3;
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
#define REG_LOCAL_PORT_OFFSET         0x15
#define REG_LOCAL_PORT_MSB_OFFSET     0x16
#define REG_DIFF_RX_TX_OFFSET         0x14
#define REG_WIDTH_OFFSET              0x17
#define REG_RX_LANE_0_OFFSET          0x18
#define REG_LANE_0_OFFSET             0x19
#define REG_SLOT_0_OFFSET             0x1a
#define REG_MODULE_0_OFFSET           0x1b
#define PMLP_REG_LEN                  0x09
#define REG_BYTES_PER_ROW             4
#define PMLP_LANE_MAP_SLOT_INDEX_MASK 0x0F

static int __PMLP_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pmlp_reg *pmlp_reg = (struct ku_pmlp_reg*)ku_reg;
    u8                  tmp_u8 = 0;
    int                 i;

    tmp_u8 |= (pmlp_reg->use_different_rx_tx & 0x01) << 7;
    tmp_u8 |= (pmlp_reg->autosplit & 0x01) << 6;
    SX_PUT_REG_FIELD(inbox, tmp_u8, REG_DIFF_RX_TX_OFFSET);

    SX_PUT_REG_FIELD(inbox, pmlp_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmlp_reg->lp_msb << 4, REG_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, pmlp_reg->width, REG_WIDTH_OFFSET);
    for (i = 0; i < NUMBER_OF_SERDESES; i++) {
        SX_PUT_REG_FIELD(inbox, pmlp_reg->rx_lane[i], REG_RX_LANE_0_OFFSET + (REG_BYTES_PER_ROW * i));
        SX_PUT_REG_FIELD(inbox, pmlp_reg->lane[i], REG_LANE_0_OFFSET + (REG_BYTES_PER_ROW * i));
        tmp_u8 = pmlp_reg->slot[i];
        tmp_u8 = tmp_u8 & PMLP_LANE_MAP_SLOT_INDEX_MASK;
        SX_PUT_REG_FIELD(inbox, tmp_u8, REG_SLOT_0_OFFSET + (REG_BYTES_PER_ROW * i));
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
    SX_GET_REG_FIELD(pmlp_reg->lp_msb, outbox, REG_LOCAL_PORT_MSB_OFFSET);
    pmlp_reg->lp_msb >>= 4;
    pmlp_reg->lp_msb &= 0x3;
    SX_GET_REG_FIELD(pmlp_reg->width, outbox, REG_WIDTH_OFFSET);

    for (i = 0; i < NUMBER_OF_SERDESES; i++) {
        SX_GET_REG_FIELD(pmlp_reg->rx_lane[i], outbox, REG_RX_LANE_0_OFFSET + (REG_BYTES_PER_ROW * i));
        SX_GET_REG_FIELD(pmlp_reg->lane[i], outbox, REG_LANE_0_OFFSET + (REG_BYTES_PER_ROW * i));
        SX_GET_REG_FIELD(tmp_u8, outbox, REG_SLOT_0_OFFSET + (REG_BYTES_PER_ROW * i));
        pmlp_reg->slot[i] = tmp_u8 & PMLP_LANE_MAP_SLOT_INDEX_MASK;
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
#define REG_SWID_OFFSET                0x14
#define REG_LOCAL_PORT_OFFSET          0x15
#define REG_SUB_PORT_OFFSET            0x16
#define PSPA_REG_LOCAL_PORT_MSB_OFFSET 0x17
#define PSPA_REG_LEN                   0x03

static int __PSPA_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pspa_reg *pspa_reg = (struct ku_pspa_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, pspa_reg->swid, REG_SWID_OFFSET);
    SX_PUT_REG_FIELD(inbox, pspa_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pspa_reg->sub_port, REG_SUB_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pspa_reg->lp_msb, PSPA_REG_LOCAL_PORT_MSB_OFFSET);
    return 0;
}

static int __PSPA_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pspa_reg *pspa_reg = (struct ku_pspa_reg*)ku_reg;

    SX_GET_REG_FIELD(pspa_reg->swid, outbox, REG_SWID_OFFSET);
    SX_GET_REG_FIELD(pspa_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pspa_reg->sub_port, outbox, REG_SUB_PORT_OFFSET);
    SX_GET_REG_FIELD(pspa_reg->lp_msb, outbox, PSPA_REG_LOCAL_PORT_MSB_OFFSET);
    pspa_reg->lp_msb &= 0x3;
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
#define PPSC_REG_LOCAL_PORT_MSB_OFFSET 0x16
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
    SX_PUT_REG_FIELD(inbox, (ppsc_reg->lp_msb & 0x3) << 4, PPSC_REG_LOCAL_PORT_MSB_OFFSET);
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
    SX_GET_REG_FIELD(ppsc_reg->lp_msb, outbox, PPSC_REG_LOCAL_PORT_MSB_OFFSET);
    ppsc_reg->lp_msb >>= 4;
    ppsc_reg->lp_msb &= 0x3;
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
#define REG_TUNING_OFFSET         0x17
#define REG_LOCAL_PORT_OFFSET     0x15
#define REG_LOCAL_PORT_MSB_OFFSET 0x16
#define PCNR_REG_LEN              0x04

static int __PCNR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pcnr_reg *pcnr_reg = (struct ku_pcnr_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, pcnr_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, (pcnr_reg->lp_msb & 0x03) << 4, REG_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, pcnr_reg->tuning_override, REG_TUNING_OFFSET);
    return 0;
}

static int __PCNR_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pcnr_reg *pcnr_reg = (struct ku_pcnr_reg*)ku_reg;

    SX_GET_REG_FIELD(pcnr_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pcnr_reg->lp_msb, outbox, REG_LOCAL_PORT_MSB_OFFSET);
    pcnr_reg->lp_msb >>= 4;
    pcnr_reg->lp_msb &= 0x3;
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
#define REG_LOCAL_PORT_MSB_OFFSET        0x16
#define REG_PORT_PROFILE_MODE_OFFSET     0x1C
#define REG_STATIC_PORT_PROFILE_OFFSET   0x1D
#define REG_ACTIVE_PORT_PROFILE_OFFSET   0x1E
#define REG_RETRANSMISSION_ACTIVE_OFFSET 0x20
#define PPLM_REG_LEN                     0x06

static int __PPLM_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_pplm_reg *pplm_reg = (struct ku_pplm_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, pplm_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, (pplm_reg->lp_msb & 0x03) << 4, REG_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, pplm_reg->port_profile_mode, REG_PORT_PROFILE_MODE_OFFSET);
    SX_PUT_REG_FIELD(inbox, pplm_reg->static_port_profile, REG_STATIC_PORT_PROFILE_OFFSET);
    return 0;
}

static int __PPLM_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_pplm_reg *pplm_reg = (struct ku_pplm_reg*)ku_reg;
    u32                 retransmission_active_and_fec_mode_active;

    SX_GET_REG_FIELD(pplm_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(pplm_reg->lp_msb, outbox, REG_LOCAL_PORT_MSB_OFFSET);
    pplm_reg->lp_msb >>= 4;
    pplm_reg->lp_msb &= 0x3;
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
    SX_GET_REG_FIELD(plpc_reg->proto_mask, outbox, REG_PLPC_PROTO_MASK_OFFSET);
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
 *
 * PELC
 ***********************************************/
#define REG_PELC_OP_OFFSET             0x14
#define REG_PELC_LOCAL_PORT_OFFSET     0x15
#define REG_PELC_LOCAL_PORT_MSB_OFFSET 0x16
/* 0x17 reserved not in use */

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
    SX_PUT_REG_FIELD(inbox, (pelc_reg->lp_msb & 0x03) << 4, REG_PELC_LOCAL_PORT_MSB_OFFSET);
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
    SX_GET_REG_FIELD(pelc_reg->lp_msb, outbox, REG_PELC_LOCAL_PORT_MSB_OFFSET);
    pelc_reg->lp_msb >>= 4;
    pelc_reg->lp_msb &= 0x3;
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
#define REG_SLOT_INDEX_OFFSET         0x16
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
    u8                  tmp_u8 = 0;

    tmp_u8 = (mcia_reg->l & 0x1) << 7;
    SX_PUT_REG_FIELD(inbox, tmp_u8, REG_L_OFFSET);
    SX_PUT_REG_FIELD(inbox, mcia_reg->module, REG_MODULE_OFFSET);
    tmp_u8 = (mcia_reg->slot_index & 0x0F) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_u8, REG_SLOT_INDEX_OFFSET);
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
    u8                  tmp_u8 = 0;

    SX_GET_REG_FIELD(tmp_u8, outbox, REG_L_OFFSET);
    mcia_reg->l = tmp_u8 >> 7;
    SX_GET_REG_FIELD(mcia_reg->module, outbox, REG_MODULE_OFFSET);
    SX_GET_REG_FIELD(tmp_u8, outbox, REG_SLOT_INDEX_OFFSET);
    mcia_reg->slot_index = tmp_u8 >> 4;
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
    trap_info |= (u32)(hpkt_reg->trap_id) & 0x3FF;
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
    hpkt_reg->trap_id = trap_info & 0x3FF;
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
                                  SX_ACCESS_REG_F_SET_AND_GET,
                                  &reg_data->op_tlv,
                                  __RAW_encode,
                                  __RAW_decode,
                                  reg_len,
                                  &reg_data->raw_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_RAW);


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
#define REG_PRIO_MSB_OFFSET   0x16
#define REG_RPRIO_OFFSET      0x1b
#define QPRT_REG_LEN          0x3

static int __QPRT_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_qprt_reg *qprt_reg = (struct ku_qprt_reg*)ku_reg;
    u8                  tmp = 0;

    SX_PUT_REG_FIELD(inbox, qprt_reg->local_port, REG_LOCAL_PORT_OFFSET);
    tmp = qprt_reg->prio;
    tmp |= ((qprt_reg->lp_msb & 0x3) << 4);
    SX_PUT_REG_FIELD(inbox, tmp, REG_PRIO_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, qprt_reg->rprio, REG_RPRIO_OFFSET);
    return 0;
}

static int __QPRT_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_qprt_reg *qprt_reg = (struct ku_qprt_reg*)ku_reg;
    u8                  tmp = 0;

    SX_GET_REG_FIELD(qprt_reg->local_port, outbox, REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(tmp, outbox, REG_PRIO_MSB_OFFSET);
    qprt_reg->lp_msb = ((tmp >> 4) & 0x3);
    qprt_reg->prio = (tmp & 0xF);
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
#define REG_HTGT_MRR_PRO_RATE_OFFSET 0x54
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
    SX_PUT_REG_FIELD(inbox, htgt_reg->mirror_probability_rate, REG_HTGT_MRR_PRO_RATE_OFFSET);

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
    SX_GET_REG_FIELD(htgt_reg->mirror_probability_rate, outbox, REG_HTGT_MRR_PRO_RATE_OFFSET);

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
 * SSPR
 ***********************************************/
#define SSPR_REG_MASTER_BIT_OFFSET     0x14
#define SSPR_REG_MASTER_BIT_N          7
#define SSPR_REG_LOCAL_PORT_OFFSET     0x15
#define SSPR_REG_LOCAL_PORT_MSB_OFFSET 0x16
#define SSPR_REG_SYSTEM_PORT           0x1a
#define SSPR_REG_LEN                   0x03

static int __SSPR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sspr_reg *sspr_reg = (struct ku_sspr_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;

    tmp_val_u8 |= sspr_reg->is_master ? (1 << SSPR_REG_MASTER_BIT_N) : 0;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, SSPR_REG_MASTER_BIT_OFFSET);
    SX_PUT_REG_FIELD(inbox, sspr_reg->local_port, SSPR_REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, (sspr_reg->lp_msb & 0x03) << 4, SSPR_REG_LOCAL_PORT_MSB_OFFSET);
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
    SX_GET_REG_FIELD(sspr_reg->lp_msb, outbox, SSPR_REG_LOCAL_PORT_MSB_OFFSET);
    sspr_reg->lp_msb = (sspr_reg->lp_msb >> 4) & 0x03;
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
#define PBMC_REG_LOCAL_PORT_MSB_OFFSET 0x16
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
    SX_PUT_REG_FIELD(inbox, ((pbmc_reg->lp_msb & 0x3) << 4), PBMC_REG_LOCAL_PORT_MSB_OFFSET);
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
    u8                  temp = 0;

    SX_GET_REG_FIELD(pbmc_reg->local_port, outbox, PBMC_REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(temp, outbox, PBMC_REG_LOCAL_PORT_MSB_OFFSET);
    pbmc_reg->lp_msb = (temp >> 4) & 0x3;
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
#define PPTB_REG_MSB_CM_UM_BITS_OFFSET  0x16
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
    tmp_val_u8 = ((pptb_reg->cm & 0x1) << PPTB_REG_CM_BIT_N) | (pptb_reg->um & 0x1);
    tmp_val_u8 |= ((pptb_reg->lp_msb & 0x3) << 4);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, PPTB_REG_MSB_CM_UM_BITS_OFFSET);
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
    SX_GET_REG_FIELD(tmp_val_u8, outbox, PPTB_REG_MSB_CM_UM_BITS_OFFSET);
    pptb_reg->lp_msb = (tmp_val_u8 >> 4) & 0x3;
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
#define SPMS_REG_LOCAL_PORT_MSB_OFFSET       0x16
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
    SX_PUT_REG_FIELD(inbox, (spms_reg->lp_msb & 0x03) << 4, SPMS_REG_LOCAL_PORT_MSB_OFFSET);
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
    SX_GET_REG_FIELD(spms_reg->lp_msb, outbox, SPMS_REG_LOCAL_PORT_MSB_OFFSET);
    spms_reg->lp_msb = (spms_reg->lp_msb >> 4) & 0x03;
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
#define SPVID_REG_LOCAL_PORT_OFFSET     0x15
#define SPVID_REG_LOCAL_PORT_MSB_OFFSET 0x16
#define SPVID_REG_PORT_VID_OFFSET       0x1a
#define SPVID_REG_LEN                   0x03

static int __SPVID_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_spvid_reg *spvid_reg = (struct ku_spvid_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, spvid_reg->local_port, SPVID_REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, (spvid_reg->lp_msb & 0x3) << 4, SPVID_REG_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, spvid_reg->port_default_vid, SPVID_REG_PORT_VID_OFFSET);
    return 0;
}

static int __SPVID_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_spvid_reg *spvid_reg = (struct ku_spvid_reg*)ku_reg;

    SX_GET_REG_FIELD(spvid_reg->local_port, outbox, SPVID_REG_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(spvid_reg->lp_msb, outbox, SPVID_REG_LOCAL_PORT_MSB_OFFSET);
    spvid_reg->lp_msb >>= 4;
    spvid_reg->lp_msb &= 0x3;
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
#define PLBF_LOCAL_PORT_OFFSET     0x15
#define PLBF_LOCAL_PORT_MSB_OFFSET 0x16
#define PLBF_LBF_MODE_OFFSET       0x17
#define PLBF_REG_LEN               0x03

static int __PLBF_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_plbf_reg *plbf_reg = (struct ku_plbf_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, plbf_reg->port, PLBF_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, ((plbf_reg->lp_msb & 0x3) << 4), PLBF_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, plbf_reg->lbf_mode, PLBF_LBF_MODE_OFFSET);
    return 0;
}

static int __PLBF_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_plbf_reg *plbf_reg = (struct ku_plbf_reg*)ku_reg;
    u8                  temp = 0;

    SX_GET_REG_FIELD(plbf_reg->port, outbox, PLBF_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(temp, outbox, PLBF_LOCAL_PORT_MSB_OFFSET);
    plbf_reg->lp_msb = (temp >> 4) & 0x3;
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
    ritr_reg->ingress_counter_set.index = tmp_val_u32 & 0xFFFFFF;
    SX_GET_REG_FIELD(tmp_val_u32, outbox, REG_EGRESS_CNTR_SET_OFFSET);
    ritr_reg->egress_counter_set.type = (tmp_val_u32 >> 24) & 0xFF;
    ritr_reg->egress_counter_set.index = tmp_val_u32 & 0xFFFFFF;

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
#define REG_LOCAL_PORT_OFFSET     0x15
#define REG_LOCAL_PORT_MSB_OFFSET 0x16
#define REG_C_E_CONG_OFFSET       0x18
#define REG_C_BIT_N               7
#define REG_E_BIT_N               6
#define REG_CONG_BIT_N            5
#define REG_RATE_OFFSET           0x1C
#define REG_COUNT_DROP_OFFSET     0x20
#define MPSC_REG_LEN              0x6

static int __MPSC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mpsc_reg *mpsc_reg = (struct ku_mpsc_reg*)ku_reg;
    u8                  tmp = 0;

    SX_PUT_REG_FIELD(inbox, mpsc_reg->local_port, REG_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, (mpsc_reg->lp_msb & 0x03) << 4, REG_LOCAL_PORT_MSB_OFFSET);
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
    SX_GET_REG_FIELD(mpsc_reg->lp_msb, outbox, REG_LOCAL_PORT_MSB_OFFSET);
    mpsc_reg->lp_msb = (mpsc_reg->lp_msb >> 4) & 0x03;
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
#define REG_LP_MSB_OFFSET               0x14
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
    SX_PUT_REG_FIELD(inbox, (mlcr_reg->lp_msb & 0x3), REG_LP_MSB_OFFSET);
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
    SX_GET_REG_FIELD(mlcr_reg->lp_msb, outbox, REG_LP_MSB_OFFSET);
    mlcr_reg->lp_msb &= 0x3;
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
 * MTPCPC
 ***********************************************/
#define REG_MTPCPC_PPORT_OFFSET                   0x14
#define REG_MTPCPC_LOCAL_PORT_OFFSET              0x15
#define REG_MTPCPC_LOCAL_PORT_MSB_OFFSET          0x16
#define REG_MTPCPC_PTP_TRAP_EN_OFFSET             0x1B
#define REG_MTPCPC_ING_CORRECTION_MSG_TYPE_OFFSET 0x26
#define REG_MTPCPC_EGR_CORRECTION_MSG_TYPE_OFFSET 0x2A
#define MTPCPC_REG_LEN                            0xB

static int __MTPCPC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtpcpc_reg *mtpcpc_reg = (struct ku_mtpcpc_reg*)ku_reg;

    SX_PUT_REG_FIELD(inbox, mtpcpc_reg->pport, REG_MTPCPC_PPORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpcpc_reg->local_port, REG_MTPCPC_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, (mtpcpc_reg->lp_msb & 0x03) << 4, REG_MTPCPC_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpcpc_reg->ptp_trap_en, REG_MTPCPC_PTP_TRAP_EN_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpcpc_reg->ing_correction_msg_type, REG_MTPCPC_ING_CORRECTION_MSG_TYPE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpcpc_reg->egr_correction_msg_type, REG_MTPCPC_EGR_CORRECTION_MSG_TYPE_OFFSET);
    return 0;
}

static int __MTPCPC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mtpcpc_reg *mtpcpc_reg = (struct ku_mtpcpc_reg*)ku_reg;

    SX_GET_REG_FIELD(mtpcpc_reg->pport, outbox, REG_MTPCPC_PPORT_OFFSET);
    SX_GET_REG_FIELD(mtpcpc_reg->local_port, outbox, REG_MTPCPC_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(mtpcpc_reg->lp_msb, outbox, REG_MTPCPC_LOCAL_PORT_MSB_OFFSET);
    mtpcpc_reg->lp_msb = (mtpcpc_reg->lp_msb >> 4) & 0x03;
    SX_GET_REG_FIELD(mtpcpc_reg->ptp_trap_en, outbox, REG_MTPCPC_PTP_TRAP_EN_OFFSET);
    SX_GET_REG_FIELD(mtpcpc_reg->ing_correction_msg_type, outbox, REG_MTPCPC_ING_CORRECTION_MSG_TYPE_OFFSET);
    SX_GET_REG_FIELD(mtpcpc_reg->egr_correction_msg_type, outbox, REG_MTPCPC_EGR_CORRECTION_MSG_TYPE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_MTPCPC(struct sx_dev *dev, struct ku_access_mtpcpc_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MTPCPC_encode,
                                  __MTPCPC_decode,
                                  MTPCPC_REG_LEN,
                                  &reg_data->mtpcpc_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MTPCPC);

/************************************************
 * MTPPTR
 ***********************************************/
#define REG_MTPPTR_LOCAL_PORT_OFFSET     0x15
#define REG_MTPPTR_LOCAL_PORT_MSB_OFFSET 0x16
#define REG_MTPPTR_DIR_OFFSET            0x17
#define REG_MTPPTR_CLR_READ_ONE_OFFSET   0x18
#define REG_MTPPTR_OVF_OFFSET            0x1b
#define REG_MTPPTR_NUM_REC_OFFSET        0x1F
#define REG_MTPPTR_RECORDS_OFFSET        0x24
#define REG_CLR_BITN                     7
#define MTPPTR_REG_LEN                   0x14

static int __MTPPTR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mtpptr_reg *mtpptr_reg = (struct ku_mtpptr_reg*)ku_reg;
    u8                    clear_read_one;

    clear_read_one = mtpptr_reg->clr << REG_CLR_BITN;
    SX_PUT_REG_FIELD(inbox, mtpptr_reg->dir, REG_MTPPTR_DIR_OFFSET);
    SX_PUT_REG_FIELD(inbox, clear_read_one, REG_MTPPTR_CLR_READ_ONE_OFFSET);
    SX_PUT_REG_FIELD(inbox, mtpptr_reg->local_port, REG_MTPPTR_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, (mtpptr_reg->lp_msb & 0x03) << 4, REG_MTPPTR_LOCAL_PORT_MSB_OFFSET);
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
#define REG_SBCTC_DIR_ING_OFFSET        0x14
#define REG_SBCTC_LOCAL_PORT_OFFSET     0x15
#define REG_SBCTC_LOCAL_PORT_MSB_OFFSET 0x16
#define REG_SBCTC_MODE_OFFSET           0x17
#define REG_SBCTC_EN_CONFIG_OFFSET      0x18
#define REG_SBCTC_EVENT_OFFSET          0x1B
#define REG_SBCTC_TCLASS_EN_OFFSET      0x1C
#define REG_SBCTC_THR_MAX_OFFSET        0x24
#define REG_SBCTC_THR_MIN_OFFSET        0x28
#define SBCTC_REG_LEN                   0x7

static int __SBCTC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sbctc_reg *sbctc_reg = (struct ku_sbctc_reg*)ku_reg;
    u8                   en_config;
    u8                   tmp_val_u8 = 0;

    SX_PUT_REG_FIELD(inbox, sbctc_reg->dir_ing, REG_SBCTC_DIR_ING_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctc_reg->local_port, REG_SBCTC_LOCAL_PORT_OFFSET);
    tmp_val_u8 |= ((sbctc_reg->lp_msb & 0x3) << 4);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_SBCTC_LOCAL_PORT_MSB_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 |= (sbctc_reg->res & 1) << 4;
    tmp_val_u8 |= (sbctc_reg->mode & 1);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_SBCTC_MODE_OFFSET);
    en_config = sbctc_reg->en_config << 7;
    SX_PUT_REG_FIELD(inbox, en_config, REG_SBCTC_EN_CONFIG_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctc_reg->event, REG_SBCTC_EVENT_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctc_reg->tclass_en, REG_SBCTC_TCLASS_EN_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctc_reg->thr_max, REG_SBCTC_THR_MAX_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctc_reg->thr_min, REG_SBCTC_THR_MIN_OFFSET);
    return 0;
}

static int __SBCTC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sbctc_reg *sbctc_reg = (struct ku_sbctc_reg*)ku_reg;
    u8                   tmp_val_u8 = 0;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_SBCTC_MODE_OFFSET);
    sbctc_reg->res = (tmp_val_u8 >> 4) & 1;
    sbctc_reg->mode = tmp_val_u8 & 1;
    SX_GET_REG_FIELD(sbctc_reg->event, outbox, REG_SBCTC_EVENT_OFFSET);
    SX_GET_REG_FIELD(sbctc_reg->tclass_en, outbox, REG_SBCTC_TCLASS_EN_OFFSET);
    SX_GET_REG_FIELD(sbctc_reg->thr_max, outbox, REG_SBCTC_THR_MAX_OFFSET);
    SX_GET_REG_FIELD(sbctc_reg->thr_min, outbox, REG_SBCTC_THR_MIN_OFFSET);
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
#define REG_SBCTR_IEVENT_OFFSET      0x14
#define REG_SBCTR_LOCAL_PORT_OFFSET  0x15
#define REG_SBCTR_MSB_DIR_ING_OFFSET 0x16
#define REG_SBCTR_FP_ENTITY_OFFSET   0x17
#define REG_SBCTR_TCLASS_EN_OFFSET   0x1C
#define SBCTR_REG_LEN                0x4

static int __SBCTR_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sbctr_reg *sbctr_reg = (struct ku_sbctr_reg*)ku_reg;
    u8                   tmp = 0;

    SX_PUT_REG_FIELD(inbox, sbctr_reg->ievent, REG_SBCTR_IEVENT_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbctr_reg->local_port, REG_SBCTR_LOCAL_PORT_OFFSET);
    tmp = (((sbctr_reg->lp_msb & 0x3) << 4) | (sbctr_reg->dir_ing & 0x3));
    SX_PUT_REG_FIELD(inbox, tmp, REG_SBCTR_MSB_DIR_ING_OFFSET);
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
#define REG_PPBMP_PNAT_MSB_OFFSET            0x16
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
    u8                   pnat_lp_msb;

    pnat_lp_msb = ((ppbmp_reg->pnat & 0x03) << 6) | ((ppbmp_reg->lp_msb & 0x03) << 4);
    SX_PUT_REG_FIELD(inbox, ppbmp_reg->local_port, REG_PPBMP_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, pnat_lp_msb, REG_PPBMP_PNAT_MSB_OFFSET);
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
#define REG_PPBMC_LOCAL_PORT_OFFSET            0x15
#define REG_PPBMC_PNAT_MSB_MONITOR_TYPE_OFFSET 0x16
#define REG_PPBMC_E_EVENT_CTRL_OFFSET          0x18
#define REG_PPBMC_MONITOR_CTRL_OFFSET          0x19
#define REG_PPBMC_MONITOR_STATE_OFFSET         0x1B
#define PPBMC_REG_LEN                          0x3

static int __PPBMC_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppbmc_reg *ppbmc_reg = (struct ku_ppbmc_reg*)ku_reg;
    u8                   e_event_ctrl;
    u8                   pnat_msb_monitor_type = 0;

    SX_PUT_REG_FIELD(inbox, ppbmc_reg->local_port, REG_PPBMC_LOCAL_PORT_OFFSET);
    pnat_msb_monitor_type = (ppbmc_reg->monitor_type & 0xF);
    pnat_msb_monitor_type |= ((ppbmc_reg->pnat & 0x3) << 6);
    pnat_msb_monitor_type |= ((ppbmc_reg->lp_msb & 0x3) << 4);
    SX_PUT_REG_FIELD(inbox, pnat_msb_monitor_type, REG_PPBMC_PNAT_MSB_MONITOR_TYPE_OFFSET);
    e_event_ctrl = ppbmc_reg->e << 6 | ((ppbmc_reg->event_ctrl) & 0xF);
    SX_PUT_REG_FIELD(inbox, e_event_ctrl, REG_PPBMC_E_EVENT_CTRL_OFFSET);
    SX_PUT_REG_FIELD(inbox, ppbmc_reg->monitor_ctrl, REG_PPBMC_MONITOR_CTRL_OFFSET);
    return 0;
}

static int __PPBMC_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppbmc_reg *ppbmc_reg = (struct ku_ppbmc_reg*)ku_reg;
    u8                   e_event_ctrl;
    u8                   pnat_msb_monitor_type;

    SX_GET_REG_FIELD(pnat_msb_monitor_type, outbox, REG_PPBMC_PNAT_MSB_MONITOR_TYPE_OFFSET);
    ppbmc_reg->monitor_type = pnat_msb_monitor_type & 0xF;
    SX_GET_REG_FIELD(e_event_ctrl, outbox, REG_PPBMC_E_EVENT_CTRL_OFFSET);
    ppbmc_reg->e = (e_event_ctrl >> 6) & 0x3;
    ppbmc_reg->event_ctrl = e_event_ctrl & 0xF;
    SX_GET_REG_FIELD(ppbmc_reg->monitor_ctrl, outbox, REG_PPBMC_MONITOR_CTRL_OFFSET);
    SX_GET_REG_FIELD(ppbmc_reg->monitor_state, outbox, REG_PPBMC_MONITOR_STATE_OFFSET);
    return 0;
}

int sx_ACCESS_REG_PPBMC(struct sx_dev *dev, struct ku_access_ppbmc_reg *reg_data)
{
    if (is_sgmii_supported()) {
        /* PPBMC is called from within the driver. when working with OOB,
         * we don't have PCI to work with, only I2C. The problem is that I2C
         * is enabled only on one management board. We must call this register from both
         * management boards and the only way to do that is with SGMII.
         */
        return sgmii_emad_access_ppbmc(reg_data->dev_id,
                                       reg_data->op_tlv.method,
                                       &reg_data->ppbmc_reg);
    }

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
#define REG_PPBME_LOCAL_PORT_OFFSET            0x15
#define REG_PPBME_PNAT_MSB_MONITOR_TYPE_OFFSET 0x16
#define REG_PPBME_MONITOR_STATE_OFFSET         0x1B
#define PPBME_REG_LEN                          0x3

static int __PPBME_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_ppbme_reg *ppbme_reg = (struct ku_ppbme_reg*)ku_reg;
    u8                   pnat_msb_monitor_type;

    SX_PUT_REG_FIELD(inbox, ppbme_reg->local_port, REG_PPBME_LOCAL_PORT_OFFSET);
    pnat_msb_monitor_type = ((ppbme_reg->pnat & 0x3) << 6);
    pnat_msb_monitor_type |= ((ppbme_reg->lp_msb & 0x3) << 4);
    SX_PUT_REG_FIELD(inbox, pnat_msb_monitor_type, REG_PPBME_PNAT_MSB_MONITOR_TYPE_OFFSET);
    return 0;
}

static int __PPBME_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_ppbme_reg *ppbme_reg = (struct ku_ppbme_reg*)ku_reg;
    u8                   pnat_monitor_type;

    SX_GET_REG_FIELD(pnat_monitor_type, outbox, REG_PPBME_PNAT_MSB_MONITOR_TYPE_OFFSET);
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
 * QPCR
 ***********************************************/
#define QPCR_REG_LEN               0x28
#define QPCR_LOCAL_PORT_MSB_OFFSET 0x14
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

    tmp_val_u8 |= (qpcr_reg->lp_msb & 0x03);
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, QPCR_LOCAL_PORT_MSB_OFFSET);
    SX_PUT_REG_FIELD(inbox, qpcr_reg->port, QPCR_LOCAL_PORT_OFFSET);
    tmp_val_u16 |= (qpcr_reg->pid & 0x3fff);
    tmp_val_u16 |= (qpcr_reg->global_policer & 3) << 14;
    SX_PUT_REG_FIELD(inbox, tmp_val_u16, QPCR_GLOBAL_PID_OFFSET);
    tmp_val_u8 = 0;
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

    SX_GET_REG_FIELD(tmp_val_u8, outbox, QPCR_LOCAL_PORT_MSB_OFFSET);
    qpcr_reg->lp_msb = (tmp_val_u8 & 0x03);
    SX_GET_REG_FIELD(qpcr_reg->port, outbox, QPCR_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u16, outbox, QPCR_GLOBAL_PID_OFFSET);
    qpcr_reg->global_policer = (tmp_val_u16 >> 14) & 3;
    qpcr_reg->pid = (tmp_val_u16) & 0x3fff;

    tmp_val_u8 = 0;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, QPCR_COUNTER_OFFSET);
    qpcr_reg->clear_counter = (tmp_val_u8 >> 7) & 1;
    qpcr_reg->add_counter = (tmp_val_u8 >> 6) & 1;

    tmp_val_u8 = 0;
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
 * MFGD
 ***********************************************/
#define REG_MFGD_OFF_B3            (0x3 + REG_START_OFFSET) /* Byte 3*/
#define REG_MFGD_OFF_B2            (0x2 + REG_START_OFFSET) /* Byte 2*/
#define REG_MFGD_OFF_B5            (0x5 + REG_START_OFFSET) /* Byte 5*/
#define REG_MFGD_OFF_EGRESS_EN     (0x6 + REG_START_OFFSET) /* Byte 6&7*/
#define REG_MFGD_OFF_FW_INIT_PORTS (0x8 + REG_START_OFFSET)  /* Byte 8&9*/
#define REG_MFGD_OFF_FW_INIT_TOTAL (0xA + REG_START_OFFSET)  /* Byte 10&11*/
#define MFGD_REG_LEN               (0x3) /* 3 dwords */

static int __MFGD_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_mfgd_reg *reg = (struct ku_mfgd_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;

    /* Byte 0 RSV */
    /* Byte 1 RSV */
    /* Byte 2  */
    tmp_val_u8 = 0;
    tmp_val_u8 |= (reg->trigger_stack_overflow & 1); /* bit 8 */
    tmp_val_u8 |= (reg->fw_fatal_mode & 3) << 1; /* bits 9 & 10*/
    tmp_val_u8 |= (reg->fw_fatal_event_test & 0xf) << 3; /* bits 11*/
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_MFGD_OFF_B2);
    /* Byte 3  */
    tmp_val_u8 = 0;
    tmp_val_u8 |= (reg->fw_dci_rif_cache & 1); /* bit 0 */
    tmp_val_u8 |= (reg->fw_dci_en & 1) << 1; /* bit 1 */
    tmp_val_u8 |= (reg->fw_kvc_en & 1) << 2; /* bit 2 */
    tmp_val_u8 |= (reg->tcr_dbg_en & 1) << 3; /* bit 3 */
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_MFGD_OFF_B3);
    /* Byte 4  RSV*/
    /* Byte 5 */
    tmp_val_u8 = 0;
    tmp_val_u8 |= (reg->atcam_bf_en & 1) << 3; /* bit 19 */
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, REG_MFGD_OFF_B5);

    /* Byte 6&7 */
    SX_PUT_REG_FIELD(inbox, reg->egress_en, REG_MFGD_OFF_EGRESS_EN);
    return 0;
}

static int __MFGD_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_mfgd_reg *reg = (struct ku_mfgd_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_MFGD_OFF_B2);
    reg->trigger_stack_overflow = (tmp_val_u8 >> 0) & 1;
    reg->fw_fatal_mode = (tmp_val_u8 >> 1) & 3;
    reg->fw_fatal_event_test = (tmp_val_u8 >> 3) & 0xf;


    tmp_val_u8 = 0;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_MFGD_OFF_B3);
    reg->fw_dci_rif_cache = (tmp_val_u8 >> 0) & 1;
    reg->fw_dci_en = (tmp_val_u8 >> 1) & 1;
    reg->fw_kvc_en = (tmp_val_u8 >> 2) & 1;
    reg->tcr_dbg_en = (tmp_val_u8 >> 3) & 1;

    tmp_val_u8 = 0;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, REG_MFGD_OFF_B5);
    reg->atcam_bf_en = (tmp_val_u8 >> 3) & 1;

    SX_GET_REG_FIELD(reg->egress_en, outbox, REG_MFGD_OFF_EGRESS_EN);
    SX_GET_REG_FIELD(reg->fw_init_open_ports_time, outbox, REG_MFGD_OFF_FW_INIT_PORTS);
    SX_GET_REG_FIELD(reg->fw_init_total_time, outbox, REG_MFGD_OFF_FW_INIT_TOTAL);
    return 0;
}

int sx_ACCESS_REG_MFGD(struct sx_dev *dev, struct ku_access_mfgd_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __MFGD_encode,
                                  __MFGD_decode,
                                  MFGD_REG_LEN,
                                  &reg_data->reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_MFGD);
/************************************************
 * SBCM
 ***********************************************/
#define SBCM_REG_LEN              0xa
#define SBCM_DESC_SNAP_OFFSET     0x14
#define SBCM_LOCAL_PORT_OFFSET    0x15
#define SBCM_PG_BUFF_OFFSET       0x16
#define SBCM_MSB_DIR_OFFSET       0x17
#define SBCM_EXC_OFFSET           0x1b
#define SBCM_BUFF_OCCUP_OFFSET    0x20
#define SBCM_CLR_M_BUFF_OC_OFFSET 0x24
#define SBCM_MIN_BUFF_OFFSET      0x28
#define SBCM_INFI_M_M_BUFF_OFFSET 0x2c
#define SBCM_POOL_OFFSET          0x37

static int __SBCM_encode(u8 *inbox, void *ku_reg, void *context)
{
    struct ku_sbcm_reg *sbcm_reg = (struct ku_sbcm_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;
    u32                 tmp_val_u32 = 0;

    tmp_val_u8 |= (sbcm_reg->desc & 1) << 7;
    tmp_val_u8 |= (sbcm_reg->snap & 1) << 6;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, SBCM_DESC_SNAP_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbcm_reg->local_port, SBCM_LOCAL_PORT_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbcm_reg->pg_buff, SBCM_PG_BUFF_OFFSET);
    tmp_val_u8 = 0;
    tmp_val_u8 = (sbcm_reg->dir & 0x3);
    tmp_val_u8 |= (sbcm_reg->lp_msb & 0x3) << 4;
    SX_PUT_REG_FIELD(inbox, tmp_val_u8, SBCM_MSB_DIR_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbcm_reg->exc, SBCM_EXC_OFFSET);

    tmp_val_u32 = sbcm_reg->clr << 31;
    SX_PUT_REG_FIELD(inbox, tmp_val_u32, SBCM_CLR_M_BUFF_OC_OFFSET);

    tmp_val_u32 = 0;
    tmp_val_u32 = sbcm_reg->min_buff;
    SX_PUT_REG_FIELD(inbox, tmp_val_u32, SBCM_MIN_BUFF_OFFSET);

    tmp_val_u32 = 0;
    tmp_val_u32 = sbcm_reg->infi_max << 31;
    tmp_val_u32 |= sbcm_reg->max_buff;
    SX_PUT_REG_FIELD(inbox, tmp_val_u32, SBCM_INFI_M_M_BUFF_OFFSET);
    SX_PUT_REG_FIELD(inbox, sbcm_reg->pool, SBCM_POOL_OFFSET);
    return 0;
}


static int __SBCM_decode(u8 *outbox, void *ku_reg, void *context)
{
    struct ku_sbcm_reg *sbcm_reg = (struct ku_sbcm_reg*)ku_reg;
    u8                  tmp_val_u8 = 0;
    u32                 tmp_val_u32 = 0;

    SX_GET_REG_FIELD(tmp_val_u8, outbox, SBCM_DESC_SNAP_OFFSET);
    sbcm_reg->desc = (tmp_val_u8 >> 7) & 1;
    SX_GET_REG_FIELD(sbcm_reg->local_port, outbox, SBCM_LOCAL_PORT_OFFSET);
    SX_GET_REG_FIELD(sbcm_reg->pg_buff, outbox, SBCM_PG_BUFF_OFFSET);
    tmp_val_u8 = 0;
    SX_GET_REG_FIELD(tmp_val_u8, outbox, SBCM_MSB_DIR_OFFSET);
    sbcm_reg->dir = tmp_val_u8 & 0x3;
    sbcm_reg->lp_msb = ((tmp_val_u8 >> 4) & 0x3);
    SX_GET_REG_FIELD(sbcm_reg->exc, outbox, SBCM_EXC_OFFSET);
    SX_GET_REG_FIELD(tmp_val_u32, outbox, SBCM_CLR_M_BUFF_OC_OFFSET);
    sbcm_reg->buff_occupancy = tmp_val_u32 & 0xFFFFFF;
    SX_GET_REG_FIELD(tmp_val_u32, outbox, SBCM_CLR_M_BUFF_OC_OFFSET);
    sbcm_reg->max_buff_occupancy = tmp_val_u32 & 0xFFFFFF;
    SX_GET_REG_FIELD(tmp_val_u32, outbox, SBCM_MIN_BUFF_OFFSET);
    sbcm_reg->min_buff = tmp_val_u32 & 0xFFFFFF;
    SX_GET_REG_FIELD(tmp_val_u32, outbox, SBCM_INFI_M_M_BUFF_OFFSET);
    sbcm_reg->infi_max = (tmp_val_u32 >> 31) & 1;
    sbcm_reg->max_buff = tmp_val_u32 & 0xFFFFFF;

    SX_GET_REG_FIELD(sbcm_reg->pool, outbox, SBCM_POOL_OFFSET);
    return 0;
}

int sx_ACCESS_REG_SBCM(struct sx_dev *dev, struct ku_access_sbcm_reg *reg_data)
{
    return sx_ACCESS_REG_internal(dev,
                                  reg_data->dev_id,
                                  0,
                                  &reg_data->op_tlv,
                                  __SBCM_encode,
                                  __SBCM_decode,
                                  SBCM_REG_LEN,
                                  &reg_data->sbcm_reg,
                                  NULL);
}
EXPORT_SYMBOL(sx_ACCESS_REG_SBCM);


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
