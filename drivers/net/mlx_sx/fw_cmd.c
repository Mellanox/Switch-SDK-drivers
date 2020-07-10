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
static void get_board_id(void *vsd, char *board_id)
{
#define VSD_OFFSET_SX_BOARD_ID 0xd0

    memset(board_id, 0, SX_BOARD_ID_LEN);
    memcpy(board_id, vsd + VSD_OFFSET_SX_BOARD_ID, SX_PSID_SIZE);
}


int sx_QUERY_RSRC(struct sx_dev *dev, struct ku_query_rsrc* query_rsrc)
{
    struct sx_cmd_mailbox *mailbox;
    u32                   *outbox;
    u16                    resource_id;
    u64                    resource_val;
    int                    err = 0;
    int                    index, i;

#define MLXSW_CMD_QUERY_RESOURCES_TABLE_END_ID 0xffff
#define MLXSW_CMD_QUERY_RESOURCES_MAX_QUERIES  100
#define MLXSW_CMD_QUERY_RESOURCES_PER_QUERY    32
#define QUERY_RSRC_RESOURCE_ID_OFFSET          0x00 /* index * rsrc entry + 2 */
#define QUERY_RSRC_RESOURCE_VAL_OFFSET         0x00 /* pull the 64 bits and extract the 40 bits*/
#define QUERY_RSRC_RESOURCE_ENTRY_SIZE         0x08
#define QUERY_RSRC_RESOURCE_VAL_WIDTH_BITS     40

    mailbox = sx_alloc_cmd_mailbox(dev, dev->device_id);
    if (IS_ERR(mailbox)) {
        return PTR_ERR(mailbox);
    }

    for (index = 0; index < MLXSW_CMD_QUERY_RESOURCES_MAX_QUERIES;
         index++) {
        memset(mailbox->buf, 0, SX_MAILBOX_SIZE);
        outbox = mailbox->buf;

        err = sx_cmd_box(dev, dev->device_id, 0, mailbox, index, 0,
                         SX_CMD_QUERY_RSRC, SX_CMD_TIME_CLASS_A, 0);
        if (err) {
            goto out;
        }

        for (i = 0; i < MLXSW_CMD_QUERY_RESOURCES_PER_QUERY; i++) {
            SX_GET(resource_id, outbox,
                   (i * QUERY_RSRC_RESOURCE_ENTRY_SIZE) + QUERY_RSRC_RESOURCE_ID_OFFSET);
            if (resource_id == MLXSW_CMD_QUERY_RESOURCES_TABLE_END_ID) {
                return 0;
            }
            if (resource_id == query_rsrc->rsrc_id) {
                SX_GET(resource_val, outbox, (i * QUERY_RSRC_RESOURCE_ENTRY_SIZE) + QUERY_RSRC_RESOURCE_VAL_OFFSET);
                query_rsrc->rsrc_val = ((1ull << QUERY_RSRC_RESOURCE_VAL_WIDTH_BITS) - 1) & resource_val;
                goto out;
            }
        }
    }

out:
    sx_free_cmd_mailbox(dev, mailbox);
    return err;
}

#define QUERY_FW_IN_MB_SIZE 0x5c
int sx_QUERY_FW(struct sx_dev *dev, struct ku_query_fw* query_fw)
{
    struct sx_fw           fw;
    struct sx_cmd         *cmd = &sx_priv(dev)->cmd;
    struct sx_cmd_mailbox *mailbox;
    u32                   *outbox;
    int                    err = 0;
    int                    target_dev_id;

    fw.local_in_mb_size = 0;
    fw.local_out_mb_offset = 0;
    fw.fw_icm = 0;
    fw.local_in_mb_offset = 0;
    fw.local_out_mb_size = 0;

    if (NULL == query_fw) {
        target_dev_id = dev->device_id;
    } else {
        target_dev_id = query_fw->dev_id;
    }

    if (DEFAULT_DEVICE_ID < target_dev_id) {
        printk(KERN_NOTICE "dev_id %d exceeded range : 1 - %d",
               target_dev_id, target_dev_id);
        return -EINVAL;
    }

#define QUERY_FW_VER_OFFSET            0x00
#define QUERY_FW_CORE_CLOCK_OFFSET     0x08
#define QUERY_FW_DEBUG_TRACE_OFFSET    0x0c
#define QUERY_FW_SMKEY_OFFSET          0x0c
#define QUERY_FW_FW_HOUR_OFFSET        0x10
#define QUERY_FW_FW_MINUTES_OFFSET     0x11
#define QUERY_FW_FW_SECONDS_OFFSET     0x12
#define QUERY_FW_FW_YEAR_OFFSET        0x14
#define QUERY_FW_FW_MONTH_OFFSET       0x16
#define QUERY_FW_FW_DAY_OFFSET         0x17
#define QUERY_FW_ERR_START_OFFSET      0x30
#define QUERY_FW_ERR_SIZE_OFFSET       0x38
#define QUERY_FW_ERR_BAR_OFFSET        0x3c
#define QUERY_FW_CLR_INT_BASE_OFFSET   0x20
#define QUERY_FW_CLR_INT_BAR_OFFSET    0x28
#define QUERY_FW_DB_PAGE_OFFSET_OFFSET 0x40
#define QUERY_FW_DB_PAGE_BAR_OFFSET    0x48
#define QUERY_FW_FRC_OFFSET            0x50
#define QUERY_FW_FRC_BAR_OFFSET        0x58
#define QUERY_FW_UTC_SEC_OFFSET        0x70
#define QUERY_FW_UTC_SEC_BAR_OFFSET    0x78
#define QUERY_FW_UTC_NSEC_OFFSET       0x80
#define QUERY_FW_UTC_NSEC_BAR_OFFSET   0x88
#define QUERY_FW_SIZE_OFFSET           0x00

    mailbox = sx_alloc_cmd_mailbox(dev, target_dev_id);
    if (IS_ERR(mailbox)) {
        return PTR_ERR(mailbox);
    }
    outbox = mailbox->buf;
    err = sx_cmd_box(dev, target_dev_id, 0, mailbox, 0, 0,
                     SX_CMD_QUERY_FW, SX_CMD_TIME_CLASS_A,
                     QUERY_FW_IN_MB_SIZE);
    if (err) {
        goto out;
    }

    SX_GET(fw.fw_pages, outbox, QUERY_FW_SIZE_OFFSET);
    SX_GET(fw.fw_ver,   outbox, QUERY_FW_VER_OFFSET);
    /*
     * FW subminor version is at more significant bits than minor
     * version, so swap here.
     */
    fw.fw_ver = (fw.fw_ver & 0xffff00000000ull) |
                ((fw.fw_ver & 0xffff0000ull) >> 16) |
                ((fw.fw_ver & 0x0000ffffull) << 16);
    dev->fw_ver = fw.fw_ver;
    SX_GET(fw.core_clock,  outbox, QUERY_FW_CORE_CLOCK_OFFSET);
    SX_GET(fw.debug_trace, outbox, QUERY_FW_DEBUG_TRACE_OFFSET);
    fw.debug_trace = fw.debug_trace >> 7;
    SX_GET(fw.smkey, outbox, QUERY_FW_SMKEY_OFFSET);
    fw.smkey = (fw.smkey >> 6) & 1;
    cmd->max_cmds = 1;
    sx_dbg(dev, "FW version %012llx, max commands %d\n",
           (unsigned long long)fw.fw_ver, cmd->max_cmds);
    SX_GET(fw.catas_offset, outbox, QUERY_FW_ERR_START_OFFSET);
    SX_GET(fw.catas_size,   outbox, QUERY_FW_ERR_SIZE_OFFSET);
    SX_GET(fw.catas_bar,    outbox, QUERY_FW_ERR_BAR_OFFSET);
    fw.catas_bar = (fw.catas_bar >> 6) * 2;
    sx_dbg(dev, "Error buffer offset at 0x%llx, size 0x%x in BAR %u\n",
           (unsigned long long)fw.catas_offset, fw.catas_size,
           fw.catas_bar);
    SX_GET(fw.clr_int_base, outbox, QUERY_FW_CLR_INT_BASE_OFFSET);
    SX_GET(fw.clr_int_bar,  outbox, QUERY_FW_CLR_INT_BAR_OFFSET);
    fw.clr_int_bar = (fw.clr_int_bar >> 6) * 2;
    sx_dbg(dev, "FW size %d KB\n", fw.fw_pages << 2);
    sx_dbg(dev, "Clear int base at 0x%llx, in BAR %u\n",
           (unsigned long long)fw.clr_int_base, fw.clr_int_bar);
    SX_GET(fw.doorbell_page_offset, outbox,
           QUERY_FW_DB_PAGE_OFFSET_OFFSET);
    SX_GET(fw.doorbell_page_bar,    outbox, QUERY_FW_DB_PAGE_BAR_OFFSET);
    SX_GET(fw.frc_offset, outbox, QUERY_FW_FRC_OFFSET);
    SX_GET(fw.frc_bar,    outbox, QUERY_FW_FRC_BAR_OFFSET);
    SX_GET(fw.utc_sec_offset, outbox, QUERY_FW_UTC_SEC_OFFSET);
    SX_GET(fw.utc_sec_bar, outbox, QUERY_FW_UTC_SEC_BAR_OFFSET);
    SX_GET(fw.utc_nsec_offset, outbox, QUERY_FW_UTC_NSEC_OFFSET);
    SX_GET(fw.utc_nsec_bar, outbox, QUERY_FW_UTC_NSEC_BAR_OFFSET);
    SX_GET(fw.fw_hour,    outbox, QUERY_FW_FW_HOUR_OFFSET);
    SX_GET(fw.fw_minutes, outbox, QUERY_FW_FW_MINUTES_OFFSET);
    SX_GET(fw.fw_seconds, outbox, QUERY_FW_FW_SECONDS_OFFSET);
    SX_GET(fw.fw_year,    outbox, QUERY_FW_FW_YEAR_OFFSET);
    SX_GET(fw.fw_month,   outbox, QUERY_FW_FW_MONTH_OFFSET);
    SX_GET(fw.fw_day,     outbox, QUERY_FW_FW_DAY_OFFSET);

    if (NULL != query_fw) {
        query_fw->core_clk = fw.core_clock;
        query_fw->dt = fw.debug_trace;
        query_fw->smkey = fw.smkey;
        query_fw->fw_year = fw.fw_year;
        query_fw->fw_month = fw.fw_month;
        query_fw->fw_day = fw.fw_day;
        query_fw->fw_hour = fw.fw_hour;
        query_fw->fw_minutes = fw.fw_minutes;
        query_fw->fw_seconds = fw.fw_seconds;
        query_fw->fw_rev = fw.fw_ver;
        query_fw->frc_offset = fw.frc_offset;
        query_fw->frc_bar = fw.frc_bar;
        query_fw->utc_sec_offset = fw.utc_sec_offset;
        query_fw->utc_sec_bar = fw.utc_sec_bar;
        query_fw->utc_nsec_offset = fw.utc_nsec_offset;
        query_fw->utc_nsec_bar = fw.utc_nsec_bar;
    }

    if ((0 == sx_priv(dev)->is_fw_initialized) &&
        ((DPT_PATH_PCI_E == sx_glb.sx_dpt.dpt_info[target_dev_id].cmd_path) ||
         is_sgmii_device(target_dev_id))) {
        memcpy(&sx_priv(dev)->fw, &fw, sizeof(fw));
        sx_priv(dev)->is_fw_initialized = 1;
    }

out:
    sx_free_cmd_mailbox(dev, mailbox);
    return err;
}
EXPORT_SYMBOL(sx_QUERY_FW);

int sx_QUERY_FW_2(struct sx_dev *dev, int sx_dev_id)
{
    struct sx_fw          *fw = &sx_priv(dev)->fw;
    struct sx_cmd_mailbox *mailbox;
    int                    err = 0;
    u32                    out_mb_info, in_mb_info;

#define QUERY_FW_OUT_MB_INFO_OFFSET 0x00
#define QUERY_FW_IN_MB_INFO_OFFSET  0x04
    mailbox = sx_alloc_cmd_mailbox(dev, dev->device_id);
    if (IS_ERR(mailbox)) {
        return PTR_ERR(mailbox);
    }
    mailbox->imm_data = 0ULL;
    err = sx_cmd_imm(dev, sx_dev_id, 0, mailbox, 0, 1, SX_CMD_QUERY_FW,
                     SX_CMD_TIME_CLASS_A, QUERY_FW_IN_MB_SIZE);
    if (err) {
        goto out;
    }

    in_mb_info = mailbox->imm_data >> 32;
    out_mb_info = mailbox->imm_data & 0xFFFFFFFFUL;

    /* TODO: what about endianness?? */
    if (dev->device_id == sx_dev_id) {
        fw->local_in_mb_offset = (in_mb_info & 0x000FFFFF);
        fw->local_in_mb_size = in_mb_info >> 20;
        fw->local_out_mb_offset = (out_mb_info & 0x000FFFFF);
        fw->local_out_mb_size = out_mb_info >> 20;
    }
#ifdef SX_DEBUG
    printk(KERN_INFO PFX "sx_QUERY_FW_2 for dev_id %u before:\n"
           "in_mb_offset=0x%x\n"
           "in_mb_size=%u\n"
           "out_mb_offset=0x%x\n"
           "out_mb_size=%u\n",
           sx_dev_id,
           sx_glb.sx_dpt.dpt_info[sx_dev_id].in_mb_offset,
           sx_glb.sx_dpt.dpt_info[sx_dev_id].in_mb_size,
           sx_glb.sx_dpt.dpt_info[sx_dev_id].out_mb_offset,
           sx_glb.sx_dpt.dpt_info[sx_dev_id].out_mb_size);
#endif
    sx_glb.sx_dpt.dpt_info[sx_dev_id].in_mb_offset = (in_mb_info & 0x000FFFFF);
    sx_glb.sx_dpt.dpt_info[sx_dev_id].in_mb_size = in_mb_info >> 20;
    sx_glb.sx_dpt.dpt_info[sx_dev_id].out_mb_offset = (out_mb_info & 0x000FFFFF);
    sx_glb.sx_dpt.dpt_info[sx_dev_id].out_mb_size = out_mb_info >> 20;
#ifdef SX_DEBUG
    printk(KERN_INFO PFX "sx_QUERY_FW_2 for dev_id %u results:\n"
           "in_mb_offset=0x%x\n"
           "in_mb_size=%u\n"
           "out_mb_offset=0x%x\n"
           "out_mb_size=%u\n",
           sx_dev_id,
           sx_glb.sx_dpt.dpt_info[sx_dev_id].in_mb_offset,
           sx_glb.sx_dpt.dpt_info[sx_dev_id].in_mb_size,
           sx_glb.sx_dpt.dpt_info[sx_dev_id].out_mb_offset,
           sx_glb.sx_dpt.dpt_info[sx_dev_id].out_mb_size);
#endif
out:
    sx_free_cmd_mailbox(dev, mailbox);
    return err;
}

static int sx_map_cmd(struct sx_dev *dev, u16 op, struct sx_icm *icm)
{
    struct sx_cmd_mailbox *mailbox;
    struct sx_icm_iter     iter;
    __be64                *pages;
    int                    lg;
    int                    nent = 0;
    int                    i;
    int                    err = 0;
    int                    ts = 0, tc = 0;

    mailbox = sx_alloc_cmd_mailbox(dev, dev->device_id);
    if (IS_ERR(mailbox)) {
        return PTR_ERR(mailbox);
    }
    memset(mailbox->buf, 0, SX_MAILBOX_SIZE);
    pages = mailbox->buf;

    for (sx_icm_first(icm, &iter);
         !sx_icm_last(&iter);
         sx_icm_next(&iter)) {
        /*
         * We have to pass pages that are aligned to their
         * size, so find the least significant 1 in the
         * address or size and use that as our log2 size.
         */
        lg = ffs(sx_icm_addr(&iter) | sx_icm_size(&iter)) - 1;
        if (lg < SX_ICM_PAGE_SHIFT) {
            sx_warn(dev, "Got FW area not aligned to "
                    "%d (%llx/%lx).\n", SX_ICM_PAGE_SIZE,
                    (unsigned long long)sx_icm_addr(&iter),
                    sx_icm_size(&iter));
            err = -EINVAL;
            goto out;
        }

        for (i = 0; i < (sx_icm_size(&iter) >> lg); ++i) {
            pages[nent] =
                cpu_to_be64((sx_icm_addr(&iter) + (i << lg)) |
                            (lg - SX_ICM_PAGE_SHIFT));
            ts += 1 << (lg - 10);
            ++tc;

            if (++nent == SX_MAILBOX_SIZE / 16) {
                err = sx_cmd(dev, dev->device_id, mailbox,
                             nent, 0, op,
                             SX_CMD_TIME_CLASS_B,
                             sx_priv(dev)->fw.local_in_mb_size);
                if (err) {
                    goto out;
                }
                nent = 0;
            }
        }
    }

    if (nent) {
        err = sx_cmd(dev, dev->device_id, mailbox, nent, 0, op,
                     SX_CMD_TIME_CLASS_B, 0);
    }
    if (err) {
        goto out;
    }

    switch (op) {
    case SX_CMD_MAP_FA:
        sx_dbg(dev, "Mapped %d chunks/%d KB for FW.\n", tc, ts);
        break;
    }

out:
    sx_free_cmd_mailbox(dev, mailbox);
    return err;
}


int sx_MAP_FA(struct sx_dev *dev, struct sx_icm *icm)
{
    return sx_map_cmd(dev, SX_CMD_MAP_FA, icm);
}

int sx_UNMAP_FA(struct sx_dev *dev)
{
    return sx_cmd(dev, dev->device_id, 0, 0, 0, SX_CMD_UNMAP_FA,
                  SX_CMD_TIME_CLASS_B,
                  sx_priv(dev)->fw.local_in_mb_size);
}

int sx_QUERY_AQ_CAP(struct sx_dev *dev)
{
    struct sx_cmd_mailbox *mailbox;
    u32                   *outbox;
    u8                     field;
    int                    err;
    struct sx_dev_cap     *dev_cap = &dev->dev_cap;

#define QUERY_DEV_CAP_MAX_SDQ_SZ_OFFSET 0x0
#define QUERY_DEV_CAP_MAX_SDQ_OFFSET    0x3
#define QUERY_DEV_CAP_MAX_RDQ_SZ_OFFSET 0x4
#define QUERY_DEV_CAP_MAX_RDQ_OFFSET    0x7
#define QUERY_DEV_CAP_MAX_CQ_SZ_OFFSET  0x8
#define QUERY_DEV_CAP_MAX_CQ_OFFSET     0xb
#define QUERY_DEV_CAP_MAX_EQ_SZ_OFFSET  0xc
#define QUERY_DEV_CAP_MAX_EQ_OFFSET     0xf
#define QUERY_DEV_CAP_MAX_SG_SQ_OFFSET  0x12
#define QUERY_DEV_CAP_MAX_SG_RQ_OFFSET  0x13

    mailbox = sx_alloc_cmd_mailbox(dev, dev->device_id);
    if (IS_ERR(mailbox)) {
        return PTR_ERR(mailbox);
    }
    outbox = mailbox->buf;

    err = sx_cmd_box(dev, dev->device_id, 0, mailbox, 0, 0,
                     SX_CMD_QUERY_AQ_CAP, SX_CMD_TIME_CLASS_A, 0);

    if (err) {
        goto out;
    }

    SX_GET(field, outbox, QUERY_DEV_CAP_MAX_SDQ_SZ_OFFSET);
    dev_cap->log_max_sdq_sz = min((int)field, SX_MAX_LOG_DQ_SIZE);
    SX_GET(field, outbox, QUERY_DEV_CAP_MAX_SDQ_OFFSET);
    dev_cap->max_num_sdqs = field;
    SX_GET(field, outbox, QUERY_DEV_CAP_MAX_RDQ_SZ_OFFSET);
    dev_cap->log_max_rdq_sz = min((int)field, SX_MAX_LOG_DQ_SIZE);
    SX_GET(field, outbox, QUERY_DEV_CAP_MAX_RDQ_OFFSET);
    dev_cap->max_num_rdqs = field;
    SX_GET(field, outbox, QUERY_DEV_CAP_MAX_CQ_SZ_OFFSET);
    dev_cap->log_max_cq_sz = min((int)field, SX_MAX_LOG_CQ_SIZE);
    SX_GET(field, outbox, QUERY_DEV_CAP_MAX_CQ_OFFSET);
    dev_cap->max_num_cqs = field;
    SX_GET(field, outbox, QUERY_DEV_CAP_MAX_EQ_SZ_OFFSET);
    dev_cap->log_max_eq_sz = field;
    SX_GET(field, outbox, QUERY_DEV_CAP_MAX_EQ_OFFSET);
    dev_cap->max_num_eqs = field;
    SX_GET(field, outbox, QUERY_DEV_CAP_MAX_SG_SQ_OFFSET);
    dev_cap->max_sg_sq = field;
    SX_GET(field, outbox, QUERY_DEV_CAP_MAX_SG_RQ_OFFSET);
    dev_cap->max_sg_rq = field;

    sx_dbg(dev, "Log Max SDQ sz: %d, num SDQs: %d\n",
           dev_cap->log_max_sdq_sz, dev_cap->max_num_sdqs);
    sx_dbg(dev, "Log Max RDQ sz: %d, num RDQs: %d\n",
           dev_cap->log_max_rdq_sz, dev_cap->max_num_rdqs);
    sx_dbg(dev, "Log Max CQ sz: %d, num CQs: %d\n",
           dev_cap->log_max_cq_sz, dev_cap->max_num_cqs);
    sx_dbg(dev, "Log Max EQ sz: %d, num EQs: %d\n",
           dev_cap->log_max_eq_sz, dev_cap->max_num_eqs);

out:
    sx_free_cmd_mailbox(dev, mailbox);
    return err;
}
EXPORT_SYMBOL(sx_QUERY_AQ_CAP);

int sx_QUERY_BOARDINFO(struct sx_dev *dev, struct ku_query_board_info *board)
{
    struct sx_cmd_mailbox *mailbox;
    u32                   *outbox;
    int                    err;
    u8                     xm_exis_and_num_ports;

#define QUERY_ADAPTER_XM_EXIST_AND_PORTS_NUM_OFFSET 0x03
#define QUERY_ADAPTER_XM_PORTS_OFFSET               0x04
#define QUERY_ADAPTER_INTA_PIN_OFFSET               0x10
#define QUERY_ADAPTER_VSD_VENDOR_ID_OFFSET          0x1e
#define QUERY_ADAPTER_VSD_OFFSET                    0x20
#define QUERY_ADAPTER_XM_EXIST_BITMASK              0x01 /* bit 1 */
#define QUERY_ADAPTER_XM_PORTS_NUM_BITMASK          0x07 /* bits 0-2 after right shift*/
#define QUERY_ADAPTER_XM_PORTS_NUM_INTERNAL_OFFSET  4

    memset(board, 0, sizeof(*board));
    mailbox = sx_alloc_cmd_mailbox(dev, dev->device_id);
    if (IS_ERR(mailbox)) {
        return PTR_ERR(mailbox);
    }

    outbox = mailbox->buf;
    err = sx_cmd_box(dev, dev->device_id, 0, mailbox, 0, 0,
                     SX_CMD_QUERY_BOARDINFO, SX_CMD_TIME_CLASS_A, 0);
    if (err) {
        goto out;
    }

    SX_GET(xm_exis_and_num_ports, outbox,
           QUERY_ADAPTER_XM_EXIST_AND_PORTS_NUM_OFFSET);
    board->xm_exists = (xm_exis_and_num_ports & QUERY_ADAPTER_XM_EXIST_BITMASK);

    board->xm_num_local_ports =
        (xm_exis_and_num_ports >> QUERY_ADAPTER_XM_PORTS_NUM_INTERNAL_OFFSET) & QUERY_ADAPTER_XM_PORTS_NUM_BITMASK;

    SX_GET(board->xm_local_ports[3], outbox, QUERY_ADAPTER_XM_PORTS_OFFSET);
    SX_GET(board->xm_local_ports[2], outbox, QUERY_ADAPTER_XM_PORTS_OFFSET + 1);
    SX_GET(board->xm_local_ports[1], outbox, QUERY_ADAPTER_XM_PORTS_OFFSET + 2);
    SX_GET(board->xm_local_ports[0], outbox, QUERY_ADAPTER_XM_PORTS_OFFSET + 3);

    SX_GET(board->vsd_vendor_id, outbox,
           QUERY_ADAPTER_VSD_VENDOR_ID_OFFSET);
    SX_GET(board->inta_pin, outbox, QUERY_ADAPTER_INTA_PIN_OFFSET);
    sx_dbg(dev, "sx_QUERY_ADAPTER: inta_pin = 0x%x\n", board->inta_pin);

    if (board->vsd_vendor_id == PCI_VENDOR_ID_MELLANOX) {
        get_board_id(outbox + QUERY_ADAPTER_VSD_OFFSET / 4,
                     board->board_id);
    }

out:
    sx_free_cmd_mailbox(dev, mailbox);
    return err;
}
EXPORT_SYMBOL(sx_QUERY_BOARDINFO);

#define PROFILE_SET_MASK_H_OFFSET                  0x00
#define PROFILE_SET_MASK_L_OFFSET                  0x08
#define PROFILE_MAX_VEPA_OFFSET                    0x13
#define PROFILE_MAX_LAG_OFFSET                     0x16
#define PROFILE_MAX_PORT_OFFSET                    0x1a
#define PROFILE_MAX_MID_OFFSET                     0x1e
#define PROFILE_MAX_PGT_OFFSET                     0x22
#define PROFILE_MAX_SYSPORT_OFFSET                 0x26
#define PROFILE_MAX_VLANS_OFFSET                   0x2a
#define PROFILE_MAX_REGIONS_OFFSET                 0x2e
#define PROFILE_MAX_FLOOD_TABLES_OFFSET            0x31
#define PROFILE_MAX_PER_VID_FLOOD_TABLES_OFFSET    0x32
#define PROFILE_FLOOD_MODE_OFFSET                  0x33
#define PROFILE_MAX_FID_OFFSET_FLOOD_TABLES_OFFSET 0x34
#define PROFILE_FID_OFFSET_TABLE_SIZE_OFFSET       0x36
#define PROFILE_MAX_PER_FID_FLOOD_TABLE_OFFSET     0x38
#define PROFILE_PER_FID_TABLE_SIZE_OFFSET          0x3A
#define PROFILE_MAX_FID_OFFSET                     0x3E
#define PROFILE_MAX_IB_MC_OFFSET                   0x42
#define PROFILE_MAX_PKEY_OFFSET                    0x46
#define PROFILE_AR_SEC_OFFSET                      0x4c
#define PROFILE_AR_GRP_CAP_OFFSET                  0x4e
#define PROFILE_ARN_OFFSET                         0x50
#define PROFILE_ARN_BIT_N                          7
#define PROFILE_UBRIDGE_SPLIT_READY_OFFSET         0x53
#define PROFILE_SPLIT_READY_BIT_N                  1
#define PROFILE_UBRIDGE_BIT_N                      4
#define PROFILE_KVD_LINEAR_SIZE_OFFSET             0x54
#define PROFILE_KVD_HASH_SINGLE_SIZE_OFFSET        0x58
#define PROFILE_KVD_HASH_DOUBLE_SIZE_OFFSET        0x5C
#define PROFILE_SWID_0_CONF_OFFSET                 0x60
#define PROFILE_SWID_1_CONF_OFFSET                 0x68
#define PROFILE_SWID_2_CONF_OFFSET                 0x70
#define PROFILE_SWID_3_CONF_OFFSET                 0x78
#define PROFILE_SWID_4_CONF_OFFSET                 0x80
#define PROFILE_SWID_5_CONF_OFFSET                 0x88
#define PROFILE_SWID_6_CONF_OFFSET                 0x90
#define PROFILE_SWID_7_CONF_OFFSET                 0x98
#define PROFILE_IB_RTR_FLAGS_OFFSET                0xa0
#define PROFILE_IB_RTR_EN_BIT_N                    7
#define PROFILE_IB_RTR_ECMP_BIT_N                  6
#define PROFILE_IB_RTR_MCF_BIT_N                   5
#define PROFILE_IB_RTR_ECMP_LID_RANGE_OFFSET       0xa2
#define PROFILE_CQE_TIME_STAMP_TYPE_OFFSET         0xb2
#define PROFILE_CQE_VERSION_OFFSET                 0xb3
#define PROFILE_RESERVED1_OFFSET                   0xb4
#define CONFIG_PROFILE_MB_SIZE                     0xb8
int sx_GET_PROFILE(struct sx_dev *dev, struct ku_profile *profile, struct profile_driver_params *params_p)
{
    struct sx_cmd_mailbox       *mailbox;
    u32                         *outbox;
    int                          err;
    u8                           tmp;
    struct profile_driver_params params;

    memset(profile, 0, sizeof(*profile));
    memset(&params, 0, sizeof(params));
    mailbox = sx_alloc_cmd_mailbox(dev, profile->dev_id);
    if (IS_ERR(mailbox)) {
        return PTR_ERR(mailbox);
    }

    outbox = mailbox->buf;
    err = sx_cmd_box(dev, dev->device_id, 0, mailbox, 0, 0x2,
                     SX_CMD_CONFIG_PROFILE, SX_CMD_TIME_CLASS_A,
                     CONFIG_PROFILE_MB_SIZE);
    if (err) {
        goto out;
    }

    SX_GET(profile->max_vepa_channels, outbox, PROFILE_MAX_VEPA_OFFSET);
    SX_GET(profile->max_lag, outbox, PROFILE_MAX_LAG_OFFSET);
    SX_GET(profile->max_port_per_lag, outbox, PROFILE_MAX_PORT_OFFSET);
    SX_GET(profile->max_mid, outbox, PROFILE_MAX_MID_OFFSET);
    SX_GET(profile->max_pgt, outbox, PROFILE_MAX_PGT_OFFSET);
    SX_GET(profile->max_system_port, outbox, PROFILE_MAX_SYSPORT_OFFSET);
    SX_GET(profile->max_active_vlans, outbox, PROFILE_MAX_VLANS_OFFSET);
    SX_GET(profile->max_regions, outbox, PROFILE_MAX_REGIONS_OFFSET);
    SX_GET(profile->max_flood_tables, outbox, PROFILE_MAX_FLOOD_TABLES_OFFSET);
    SX_GET(profile->max_per_vid_flood_tables, outbox,
           PROFILE_MAX_PER_VID_FLOOD_TABLES_OFFSET);
    SX_GET(profile->flood_mode, outbox, PROFILE_FLOOD_MODE_OFFSET);
    SX_GET(profile->max_fid_offset_flood_tables, outbox, PROFILE_MAX_FID_OFFSET_FLOOD_TABLES_OFFSET);
    SX_GET(profile->fid_offset_table_size, outbox, PROFILE_FID_OFFSET_TABLE_SIZE_OFFSET);
    SX_GET(profile->max_per_fid_flood_table, outbox, PROFILE_MAX_PER_FID_FLOOD_TABLE_OFFSET);
    SX_GET(profile->per_fid_table_size, outbox, PROFILE_PER_FID_TABLE_SIZE_OFFSET);
    SX_GET(profile->max_ib_mc, outbox, PROFILE_MAX_IB_MC_OFFSET);
    SX_GET(profile->max_pkey, outbox, PROFILE_MAX_PKEY_OFFSET);
    SX_GET(profile->ar_sec, outbox, PROFILE_AR_SEC_OFFSET);
    SX_GET(profile->adaptive_routing_group_cap, outbox, PROFILE_AR_GRP_CAP_OFFSET);
    SX_GET(profile->arn, outbox, PROFILE_ARN_OFFSET);
    profile->arn = profile->arn >> PROFILE_ARN_BIT_N;
    SX_GET(profile->split_ready, outbox, PROFILE_UBRIDGE_SPLIT_READY_OFFSET);
    profile->split_ready = (profile->split_ready >> PROFILE_SPLIT_READY_BIT_N) & 0x1;
    SX_GET(profile->ubridge_mode, outbox, PROFILE_UBRIDGE_SPLIT_READY_OFFSET);
    profile->ubridge_mode = (profile->ubridge_mode >> PROFILE_UBRIDGE_BIT_N) & 0x1;
    SX_GET(profile->kvd_linear_size, outbox, PROFILE_KVD_LINEAR_SIZE_OFFSET);
    SX_GET(profile->kvd_hash_single_size, outbox, PROFILE_KVD_HASH_SINGLE_SIZE_OFFSET);
    SX_GET(profile->kvd_hash_double_size, outbox, PROFILE_KVD_HASH_DOUBLE_SIZE_OFFSET);
    SX_GET(tmp, outbox, PROFILE_SWID_0_CONF_OFFSET + 1);
    profile->swid0_config_type.type = tmp >> 4;
    SX_GET(tmp, outbox, PROFILE_SWID_1_CONF_OFFSET + 1);
    profile->swid1_config_type.type = tmp >> 4;
    SX_GET(tmp, outbox, PROFILE_SWID_2_CONF_OFFSET + 1);
    profile->swid2_config_type.type = tmp >> 4;
    SX_GET(tmp, outbox, PROFILE_SWID_3_CONF_OFFSET + 1);
    profile->swid3_config_type.type = tmp >> 4;
    SX_GET(tmp, outbox, PROFILE_SWID_4_CONF_OFFSET + 1);
    profile->swid4_config_type.type = tmp >> 4;
    SX_GET(tmp, outbox, PROFILE_SWID_5_CONF_OFFSET + 1);
    profile->swid5_config_type.type = tmp >> 4;
    SX_GET(tmp, outbox, PROFILE_SWID_6_CONF_OFFSET + 1);
    profile->swid6_config_type.type = tmp >> 4;
    SX_GET(tmp, outbox, PROFILE_SWID_7_CONF_OFFSET + 1);
    profile->swid7_config_type.type = tmp >> 4;
    SX_GET(profile->swid0_config_type.properties, outbox,
           PROFILE_SWID_0_CONF_OFFSET + 3);
    SX_GET(profile->swid1_config_type.properties, outbox,
           PROFILE_SWID_1_CONF_OFFSET + 3);
    SX_GET(profile->swid2_config_type.properties, outbox,
           PROFILE_SWID_2_CONF_OFFSET + 3);
    SX_GET(profile->swid3_config_type.properties, outbox,
           PROFILE_SWID_3_CONF_OFFSET + 3);
    SX_GET(profile->swid4_config_type.properties, outbox,
           PROFILE_SWID_4_CONF_OFFSET + 3);
    SX_GET(profile->swid5_config_type.properties, outbox,
           PROFILE_SWID_5_CONF_OFFSET + 3);
    SX_GET(profile->swid6_config_type.properties, outbox,
           PROFILE_SWID_6_CONF_OFFSET + 3);
    SX_GET(profile->swid7_config_type.properties, outbox,
           PROFILE_SWID_7_CONF_OFFSET + 3);
    SX_GET(tmp, outbox, PROFILE_IB_RTR_FLAGS_OFFSET);
    profile->ib_router_en = (tmp >> PROFILE_IB_RTR_EN_BIT_N) & 0x1;
    profile->ib_router_ecmp = (tmp >> PROFILE_IB_RTR_ECMP_BIT_N) & 0x1;
    profile->ib_router_mcf = (tmp >> PROFILE_IB_RTR_MCF_BIT_N) & 0x1;
    SX_GET(profile->ib_router_ecmp_lid_range, outbox, PROFILE_IB_RTR_ECMP_LID_RANGE_OFFSET);
    SX_GET(params.cqe_time_stamp_type, outbox, PROFILE_CQE_TIME_STAMP_TYPE_OFFSET);
    SX_GET(params.cqe_version, outbox, PROFILE_CQE_VERSION_OFFSET);
    SX_GET(profile->reserved1, outbox, PROFILE_RESERVED1_OFFSET);

    if (params_p != NULL) {
        memcpy(params_p, &params, sizeof(*params_p));
    }

out:
    sx_free_cmd_mailbox(dev, mailbox);
    return err;
}
EXPORT_SYMBOL(sx_GET_PROFILE);

int sx_SET_PROFILE(struct sx_dev *dev, struct ku_profile *profile, struct profile_driver_params *params)
{
    struct sx_cmd_mailbox *mailbox;
    u32                   *inbox;
    int                    err;
    u8                     temp_u8 = 0;

    mailbox = sx_alloc_cmd_mailbox(dev, profile->dev_id);
    if (IS_ERR(mailbox)) {
        return PTR_ERR(mailbox);
    }

    inbox = mailbox->buf;
    memset(inbox, 0, SX_MAILBOX_SIZE);
    SX_PUT(inbox, profile->set_mask_0_63, PROFILE_SET_MASK_L_OFFSET);
    SX_PUT(inbox, profile->set_mask_64_127, PROFILE_SET_MASK_H_OFFSET);
    SX_PUT(inbox, profile->max_vepa_channels, PROFILE_MAX_VEPA_OFFSET);
    SX_PUT(inbox, profile->max_lag, PROFILE_MAX_LAG_OFFSET);
    SX_PUT(inbox, profile->max_port_per_lag, PROFILE_MAX_PORT_OFFSET);
    SX_PUT(inbox, profile->max_mid, PROFILE_MAX_MID_OFFSET);
    SX_PUT(inbox, profile->max_pgt, PROFILE_MAX_PGT_OFFSET);
    SX_PUT(inbox, profile->max_system_port,
           PROFILE_MAX_SYSPORT_OFFSET);
    SX_PUT(inbox, profile->max_active_vlans, PROFILE_MAX_VLANS_OFFSET);
    SX_PUT(inbox, profile->max_regions, PROFILE_MAX_REGIONS_OFFSET);
    SX_PUT(inbox, profile->max_flood_tables, PROFILE_MAX_FLOOD_TABLES_OFFSET);
    SX_PUT(inbox, profile->max_per_vid_flood_tables,
           PROFILE_MAX_PER_VID_FLOOD_TABLES_OFFSET);
    SX_PUT(inbox, profile->flood_mode, PROFILE_FLOOD_MODE_OFFSET);
    SX_PUT(inbox, profile->max_fid_offset_flood_tables, PROFILE_MAX_FID_OFFSET_FLOOD_TABLES_OFFSET);
    SX_PUT(inbox, profile->fid_offset_table_size, PROFILE_FID_OFFSET_TABLE_SIZE_OFFSET);
    SX_PUT(inbox, profile->max_per_fid_flood_table, PROFILE_MAX_PER_FID_FLOOD_TABLE_OFFSET);
    SX_PUT(inbox, profile->per_fid_table_size, PROFILE_PER_FID_TABLE_SIZE_OFFSET);
    SX_PUT(inbox, profile->max_fid, PROFILE_MAX_FID_OFFSET);
    SX_PUT(inbox, profile->max_ib_mc, PROFILE_MAX_IB_MC_OFFSET);
    SX_PUT(inbox, profile->max_pkey, PROFILE_MAX_PKEY_OFFSET);
    SX_PUT(inbox, profile->ar_sec, PROFILE_AR_SEC_OFFSET);
    SX_PUT(inbox, profile->adaptive_routing_group_cap, PROFILE_AR_GRP_CAP_OFFSET);
    SX_PUT(inbox, (u8)(profile->arn << PROFILE_ARN_BIT_N), PROFILE_ARN_OFFSET);
    temp_u8 = (u8)((!!(profile->split_ready)) << PROFILE_SPLIT_READY_BIT_N);
    temp_u8 |= (u8)((!!(profile->ubridge_mode)) << PROFILE_UBRIDGE_BIT_N);
    SX_PUT(inbox, temp_u8, PROFILE_UBRIDGE_SPLIT_READY_OFFSET);
    SX_PUT(inbox, profile->kvd_linear_size, PROFILE_KVD_LINEAR_SIZE_OFFSET);
    SX_PUT(inbox, profile->kvd_hash_single_size, PROFILE_KVD_HASH_SINGLE_SIZE_OFFSET);
    SX_PUT(inbox, profile->kvd_hash_double_size, PROFILE_KVD_HASH_DOUBLE_SIZE_OFFSET);
    SX_PUT(inbox, profile->swid0_config_type.mask,
           PROFILE_SWID_0_CONF_OFFSET);
    SX_PUT(inbox, profile->swid0_config_type.properties,
           PROFILE_SWID_0_CONF_OFFSET + 3);
    temp_u8 = (u8)(profile->swid0_config_type.type << 4);
    SX_PUT(inbox, temp_u8, PROFILE_SWID_0_CONF_OFFSET + 1);
    SX_PUT(inbox, profile->swid1_config_type.mask,
           PROFILE_SWID_1_CONF_OFFSET);
    SX_PUT(inbox, profile->swid1_config_type.properties,
           PROFILE_SWID_1_CONF_OFFSET + 3);
    temp_u8 = (u8)(profile->swid1_config_type.type << 4);
    SX_PUT(inbox, temp_u8, PROFILE_SWID_1_CONF_OFFSET + 1);
    SX_PUT(inbox, profile->swid2_config_type.mask,
           PROFILE_SWID_2_CONF_OFFSET);
    SX_PUT(inbox, profile->swid2_config_type.properties,
           PROFILE_SWID_2_CONF_OFFSET + 3);
    temp_u8 = (u8)(profile->swid2_config_type.type << 4);
    SX_PUT(inbox, temp_u8, PROFILE_SWID_2_CONF_OFFSET + 1);
    SX_PUT(inbox, profile->swid3_config_type.mask,
           PROFILE_SWID_3_CONF_OFFSET);
    SX_PUT(inbox, profile->swid3_config_type.properties,
           PROFILE_SWID_3_CONF_OFFSET + 3);
    temp_u8 = (u8)(profile->swid3_config_type.type << 4);
    SX_PUT(inbox, temp_u8, PROFILE_SWID_3_CONF_OFFSET + 1);
    SX_PUT(inbox, profile->swid4_config_type.mask,
           PROFILE_SWID_4_CONF_OFFSET);
    SX_PUT(inbox, profile->swid4_config_type.properties,
           PROFILE_SWID_4_CONF_OFFSET + 3);
    temp_u8 = (u8)(profile->swid4_config_type.type << 4);
    SX_PUT(inbox, temp_u8, PROFILE_SWID_4_CONF_OFFSET + 1);
    SX_PUT(inbox, profile->swid5_config_type.mask,
           PROFILE_SWID_5_CONF_OFFSET);
    SX_PUT(inbox, profile->swid5_config_type.properties,
           PROFILE_SWID_5_CONF_OFFSET + 3);
    temp_u8 = (u8)(profile->swid5_config_type.type << 4);
    SX_PUT(inbox, temp_u8, PROFILE_SWID_5_CONF_OFFSET + 1);
    SX_PUT(inbox, profile->swid6_config_type.mask,
           PROFILE_SWID_6_CONF_OFFSET);
    SX_PUT(inbox, profile->swid6_config_type.properties,
           PROFILE_SWID_6_CONF_OFFSET + 3);
    temp_u8 = (u8)(profile->swid6_config_type.type << 4);
    SX_PUT(inbox, temp_u8, PROFILE_SWID_6_CONF_OFFSET + 1);
    SX_PUT(inbox, profile->swid7_config_type.mask,
           PROFILE_SWID_7_CONF_OFFSET);
    SX_PUT(inbox, profile->swid7_config_type.properties,
           PROFILE_SWID_7_CONF_OFFSET + 3);
    temp_u8 = (u8)(profile->swid7_config_type.type << 4);
    SX_PUT(inbox, temp_u8, PROFILE_SWID_7_CONF_OFFSET + 1);
    SX_PUT(inbox, profile->reserved1, PROFILE_RESERVED1_OFFSET);
    temp_u8 = (u8)((profile->ib_router_en & 0x1) << PROFILE_IB_RTR_EN_BIT_N |
                   (profile->ib_router_ecmp & 0x1) << PROFILE_IB_RTR_ECMP_BIT_N |
                   (profile->ib_router_mcf & 0x1) << PROFILE_IB_RTR_MCF_BIT_N);
    SX_PUT(inbox, temp_u8, PROFILE_IB_RTR_FLAGS_OFFSET);
    SX_PUT(inbox, profile->ib_router_ecmp_lid_range, PROFILE_IB_RTR_ECMP_LID_RANGE_OFFSET);
    SX_PUT(inbox, params->cqe_time_stamp_type, PROFILE_CQE_TIME_STAMP_TYPE_OFFSET);
    SX_PUT(inbox, params->cqe_version, PROFILE_CQE_VERSION_OFFSET);

    err = sx_cmd(dev, profile->dev_id, mailbox, 0, 1, SX_CMD_CONFIG_PROFILE,
                 SX_CMD_TIME_CLASS_A, CONFIG_PROFILE_MB_SIZE);

    sx_free_cmd_mailbox(dev, mailbox);
    return err;
}

int sx_SET_SYSTEM_M_KEY(struct sx_dev *dev, struct ku_system_m_key *system_m_key)
{
    struct sx_cmd_mailbox *mailbox;
    int                    err;

#define INIT_SYSTEM_M_KEY_MB_SIZE 0x08

    mailbox = sx_alloc_cmd_mailbox(dev, system_m_key->dev_id);
    if (IS_ERR(mailbox)) {
        return PTR_ERR(mailbox);
    }

    mailbox->imm_data = system_m_key->system_m_key;
    mailbox->is_in_param_imm = 1;

    err = sx_cmd(dev, system_m_key->dev_id, mailbox, 0, 1, SX_CMD_INIT_SYSTEM_M_KEY,
                 SX_CMD_TIME_CLASS_A, INIT_SYSTEM_M_KEY_MB_SIZE);

    sx_free_cmd_mailbox(dev, mailbox);
    return err;
}
EXPORT_SYMBOL(sx_SET_SYSTEM_M_KEY);

int sx_GET_SYSTEM_M_KEY(struct sx_dev *dev, struct ku_system_m_key *system_m_key)
{
    struct sx_cmd_mailbox *mailbox;
    int                    err;

#define INIT_SYSTEM_M_KEY_MB_SIZE 0x08

    mailbox = sx_alloc_cmd_mailbox(dev, system_m_key->dev_id);
    if (IS_ERR(mailbox)) {
        return PTR_ERR(mailbox);
    }

    err = sx_cmd_imm(dev, system_m_key->dev_id, 0, mailbox, 0, 2, SX_CMD_INIT_SYSTEM_M_KEY,
                     SX_CMD_TIME_CLASS_A, INIT_SYSTEM_M_KEY_MB_SIZE);
    if (err) {
        goto out;
    }

    system_m_key->system_m_key = mailbox->imm_data;

out:
    sx_free_cmd_mailbox(dev, mailbox);
    return err;
}
EXPORT_SYMBOL(sx_GET_SYSTEM_M_KEY);

int sx_ISSU_FW_START(struct sx_dev *dev)
{
    return sx_cmd(dev, dev->device_id, 0, 0, 1 /* start issu fw */, SX_CMD_ISSU_FW,
                  SX_CMD_TIME_CLASS_A, sx_priv(dev)->fw.local_in_mb_size);
}

int sx_ISSU_FW_STATUS_GET(struct sx_dev *dev, u8 *issu_fw_status)
{
    struct sx_cmd_mailbox *mailbox;
    int                    err = 0;

#define INIT_ISSU_FW_MB_SIZE 0x08

    mailbox = sx_alloc_cmd_mailbox(dev, dev->device_id);
    if (IS_ERR(mailbox)) {
        return PTR_ERR(mailbox);
    }

    mailbox->imm_data = 0ULL;
    err = sx_cmd_imm(dev, dev->device_id, 0, mailbox, 0, 2 /* get status */, SX_CMD_ISSU_FW,
                     SX_CMD_TIME_CLASS_A, INIT_ISSU_FW_MB_SIZE);
    if (err) {
        goto out;
    }

    *issu_fw_status = mailbox->imm_data & 0x1;

out:
    sx_free_cmd_mailbox(dev, mailbox);
    return err;
}


int sx_MAD_DEMUX(struct sx_dev *sx_dev, int dev_id, u8 enable)
{
    static const uint8_t   mad_demux_enable_cmd[] = {
        0x00, 0x02, 0x10, 0x00, /* qp0_method_mask=[trap], qp0_attribute_mask_all_ports=[sm_info]           */
        0x00, 0x00, 0x00, 0x00, /* reserved                                                                 */
        0x00, 0x00, 0x00, 0x03, /* qp0_attribute_mask_port_zero=[port_info,pkey_table]                      */
        0x00, 0x00, 0x09, 0x00, /* other_class_flags=[sa,qp0_res]                                           */
        0x80, 0x01, 0x00, 0x00, /* perf_flag=[1], perf_method_mask=[get_response_method]                    */
        0x00, 0x00, 0x00, 0x00, /* reserved                                                                 */
        0x80, 0x03, 0x00, 0x00, /* bm_flag=[1], bm_method_mask=[get_response_method,trap_method]            */
        0x00, 0x00, 0x00, 0x00, /* reserved                                                                 */
        0x80, 0x01, 0x00, 0x00, /* vs9_flag=[1], vs9_method_mask=[get_response_method]                      */
        0x00, 0x00, 0x00, 0x00, /* reserved                                                                 */
        0x80, 0x01, 0x00, 0x00, /* vs10_flag=[1], vs10_method_mask=[get_response_method]                    */
        0x00, 0x00, 0x00, 0x00, /* reserved                                                                 */
        0x80, 0x03, 0x00, 0x00, /* cc_flag=[1], cc_method_mask=[get_response_method,trap_method]            */
    };
    struct sx_cmd_mailbox *mailbox;
    int                    err;

    mailbox = sx_alloc_cmd_mailbox(sx_dev, dev_id);
    if (IS_ERR(mailbox)) {
        return PTR_ERR(mailbox);
    }

    if (enable) {
        memcpy(mailbox->buf, mad_demux_enable_cmd, sizeof(mad_demux_enable_cmd));
        memset(mailbox->buf + sizeof(mad_demux_enable_cmd), 0, 256 - sizeof(mad_demux_enable_cmd)); /* padding */
    } else { /* disable */
        memset(mailbox->buf, 0, 256); /* disable command is all zeros */
    }

    err = sx_cmd(sx_dev, dev_id, mailbox, 0, 0, SX_CMD_INIT_MAD_DEMUX, SX_CMD_TIME_CLASS_C, 256);

    sx_free_cmd_mailbox(sx_dev, mailbox);
    return err;
}

int sx_QUERY_CQ(struct sx_dev *dev, u8 cqn, struct ku_query_cq *cq_context_p)
{
    u32                   *outbox;
    int                    err;
    int                    target_dev_id;
    u32                    in_modifier = cqn & 0xffffff;
    u8                     cqe_ver_eqn, st;
    u16                    last_notified_counter;
    struct sx_cmd_mailbox *mailbox;

#define REG_MODULE_OFFSET                 0x15
#define QUERY_CQ_LEN                      0x50
#define QUERY_CQ_CQE_VER_EQN_OFFSET       0x0
#define QUERY_CQ_ST_OFFSET                0x2
#define QUERY_CQ_LOG_CQ_SIZE_OFFSET       0x3
#define QUERY_CQ_PROD_PTR_OFFSET          0x6
#define QUERY_CQ_LAST_NOTIFIED_PRT_OFFSET 0xa

    target_dev_id = DEFAULT_DEVICE_ID;

    mailbox = sx_alloc_cmd_mailbox(dev, target_dev_id);
    if (IS_ERR(mailbox)) {
        return PTR_ERR(mailbox);
    }
    outbox = mailbox->buf;
    err = sx_cmd_box(dev, target_dev_id, 0, mailbox, in_modifier, 0,
                     SX_CMD_QUERY_CQ, SX_CMD_TIME_CLASS_A,
                     QUERY_CQ_LEN);
    if (err) {
        goto out;
    }

    SX_GET(cqe_ver_eqn, outbox, QUERY_CQ_CQE_VER_EQN_OFFSET);
    cq_context_p->eq_num = cqe_ver_eqn & 0x1;

    SX_GET(st, outbox, QUERY_CQ_ST_OFFSET);
    SX_GET(cq_context_p->log_cq_size, outbox, QUERY_CQ_LOG_CQ_SIZE_OFFSET);
    SX_GET(cq_context_p->producer_counter, outbox, QUERY_CQ_PROD_PTR_OFFSET);
    SX_GET(last_notified_counter, outbox, QUERY_CQ_LAST_NOTIFIED_PRT_OFFSET);

    sx_dbg(dev, "cqn:%d, cq_ver:%d, eqn:%d, st:%d, log_cq_size:%d, prod_cnt:%u, last_n_cnt:%u\n",
           cqn,
           (cqe_ver_eqn >> 4),
           cq_context_p->eq_num,
           st,
           cq_context_p->log_cq_size,
           cq_context_p->producer_counter,
           last_notified_counter
           );

out:
    sx_free_cmd_mailbox(dev, mailbox);
    return err;
}
EXPORT_SYMBOL(sx_QUERY_CQ);
