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

/************************************************
 * Includes
 ***********************************************/

#include <linux/sched.h>
#include <linux/pci.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/delay.h>
#include "sx.h"
#include "dq.h"
#include "cq.h"
#include "sx_dpt.h"
#include "sx_proc.h"
#include "sgmii.h"
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>

/************************************************
 *  Definitions
 ***********************************************/

#define CMD_POLL_TOKEN 0xffff

/************************************************
 *  Globals
 ***********************************************/

extern struct sx_globals sx_glb;
extern int               i2c_cmd_dump;
extern int               i2c_cmd_op;
extern int               i2c_cmd_reg_id;
extern int               i2c_cmd_dump_cnt;

/* for simulator only */
static int (*cmd_ifc_stub_func)(void *rxbuff, void *txbuf, int size,
                                u8 op_modifier, u16 opcode, u32 input_modifier, u16 token);

/************************************************
 * Functions                            *
 ***********************************************/

void mem_blk_dump(char *name, u8 *data, int len)
{
    int i;
    u8 *buf = (void*)data;
    int cnt = len;

    printk("======= %s =========\n", name);
    for (i = 0; i < cnt; i++) {
        if ((i == 0) || (i % 4 == 0)) {
            printk("\n");
            printk("0x%04x : ", i);
        }
        printk(" 0x%02x", buf[i]);
    }

    printk(KERN_INFO "\n");
}

void register_ver_cmd_ifc_stub(int (*func)(void *rxbuff, void *txbuf, int size,
                                           u8 op_modifier, u16 opcode, u32 input_modifier, u16 token))
{
    cmd_ifc_stub_func = func;
}
EXPORT_SYMBOL(register_ver_cmd_ifc_stub);

enum {
    /* command completed successfully: */
    CMD_STAT_OK = 0x00,
    /* Internal error (such as a bus error)
    * occurred while processing command: */
    CMD_STAT_INTERNAL_ERR = 0x01,
    /* Operation/command not supported or opcode modifier not supported: */
    CMD_STAT_BAD_OP = 0x02,
    /* Parameter not supported or parameter out of range: */
    CMD_STAT_BAD_PARAM = 0x03,
    /* System not enabled or bad system state: */
    CMD_STAT_BAD_SYS_STATE = 0x04,
    /* Attempt to access reserved or unallocated resource: */
    CMD_STAT_BAD_RESOURCE = 0x05,
    /* Requested resource is currently executing a command,
     * or is otherwise busy: */
    CMD_STAT_RESOURCE_BUSY = 0x06,
    /* Required capability exceeds device limits: */
    CMD_STAT_EXCEED_LIM = 0x08,
    /* Resource is not in the appropriate state or ownership: */
    CMD_STAT_BAD_RES_STATE = 0x09,
    /* Index out of range: */
    CMD_STAT_BAD_INDEX = 0x0a,
    /* FW image corrupted: */
    CMD_STAT_BAD_NVMEM = 0x0b,
    /* Bad management packet (silently discarded): */
    CMD_STAT_BAD_PKT = 0x30,
};

enum {
    HCR_IN_PARAM_OFFSET = 0x00,
    HCR_IN_MODIFIER_OFFSET = 0x08,
    HCR_OUT_PARAM_OFFSET = 0x0c,
    HCR_TOKEN_OFFSET = 0x14,
    HCR_STATUS_OFFSET = 0x18,
    HCR_OPMOD_SHIFT = 12,
    HCR_E_BIT = 22,
    HCR_GO_BIT = 23
};

enum {
#ifdef NO_PCI
    GO_BIT_TIMEOUT_MSECS = 10,
    I2C_GO_BIT_TIMEOUT_MSECS = 10
#else
    GO_BIT_TIMEOUT_MSECS = 500,
    I2C_GO_BIT_TIMEOUT_MSECS = 500
#endif
};

enum {
    SX_HCR_BASE = 0x71000,
    SX_HCR_SIZE = 0x0001c,
    SX_HCR2_BASE = 0x72000,         /* for i2c command interface */
    SX_HCR2_SIZE = 0x0001c,
};

struct sx_cmd_context {
    struct completion done;
    int               result;
    int               next;
    u64               out_param;
    u16               token;
    u16               opcode;
};
static const char * cmd_str(u16 opcode)
{
    switch (opcode) {
    case SX_CMD_MAP_FA:
        return "SX_CMD_MAP_FA";

    case SX_CMD_UNMAP_FA:
        return "SX_CMD_UNMAP_FA";

    case SX_CMD_QUERY_FW:
        return "SX_CMD_QUERY_FW";

    case SX_CMD_QUERY_RSRC:
        return "SX_CMD_QUERY_RSRC";

    case SX_CMD_QUERY_BOARDINFO:
        return "SX_CMD_QUERY_BOARDINFO";

    case SX_CMD_QUERY_AQ_CAP:
        return "SX_CMD_QUERY_AQ_CAP";

    case SX_CMD_CONFIG_PROFILE:
        return "SX_CMD_CONFIG_PROFILE";

    case SX_CMD_ACCESS_REG:
        return "SX_CMD_ACCESS_REG";

    case SX_CMD_CONF_PORT:
        return "SX_CMD_CONF_PORT";

    case SX_CMD_INIT_PORT:
        return "SX_CMD_INIT_PORT";

    case SX_CMD_CLOSE_PORT:
        return "SX_CMD_CLOSE_PORT";

    case SX_CMD_SW2HW_DQ:
        return "SX_CMD_SW2HW_DQ";

    case SX_CMD_HW2SW_DQ:
        return "SX_CMD_HW2SW_DQ";

    case SX_CMD_2ERR_DQ:
        return "SX_CMD_2ERR_DQ";

    case SX_CMD_QUERY_DQ:
        return "SX_CMD_QUERY_DQ";

    case SX_CMD_SW2HW_CQ:
        return "SX_CMD_SW2HW_CQ";

    case SX_CMD_HW2SW_CQ:
        return "SX_CMD_HW2SW_CQ";

    case SX_CMD_QUERY_CQ:
        return "SX_CMD_QUERY_CQ";

    case SX_CMD_SW2HW_EQ:
        return "SX_CMD_SW2HW_EQ";

    case SX_CMD_HW2SW_EQ:
        return "SX_CMD_HW2SW_EQ";

    case SX_CMD_QUERY_EQ:
        return "SX_CMD_QUERY_EQ";

    case SX_CMD_INIT_MAD_DEMUX:
        return "SX_CMD_INIT_MAD_DEMUX";

    case SX_CMD_MAD_IFC:
        return "SX_CMD_MAD_IFC";

    case SX_CMD_ISSU_FW:
        return "SX_CMD_ISSU_FW";

    default:
        return "Unknown command";
    }
}

static int sx_status_to_errno(u8 status)
{
    static const int trans_table[] = {
        [CMD_STAT_INTERNAL_ERR] = -EIO,
        [CMD_STAT_BAD_OP] = -EPERM,
        [CMD_STAT_BAD_PARAM] = -EINVAL,
        [CMD_STAT_BAD_SYS_STATE] = -ENXIO,
        [CMD_STAT_BAD_RESOURCE] = -EBADF,
        [CMD_STAT_RESOURCE_BUSY] = -EBUSY,
        [CMD_STAT_EXCEED_LIM] = -ENOMEM,
        [CMD_STAT_BAD_RES_STATE] = -EBADF,
        [CMD_STAT_BAD_INDEX] = -EBADF,
        [CMD_STAT_BAD_NVMEM] = -EFAULT,
        [CMD_STAT_BAD_PKT] = -EINVAL,
    };

    if ((status >= ARRAY_SIZE(trans_table)) ||
        ((status != CMD_STAT_OK) && (trans_table[status] == 0))) {
        return -EIO;
    }

    return trans_table[status];
}

static int cmd_get_hcr_pci(struct sx_dev *dev, int offset)
{
    u32 status = 0;

    if (dev->pdev) {
        status = __raw_readl(sx_priv(dev)->cmd.hcr + offset);
    }

    return status;
}

static int cmd_get_hcr_i2c(int sx_dev_id, int hcr_base, int offset, int *err)
{
#ifdef NO_PCI
    return 0;
#else
    return sx_dpt_i2c_readl(sx_dev_id, hcr_base + offset, err);
#endif
}

static u32 cmd_get_hcr_reg(struct sx_dev *dev, int sx_dev_id, int hcr_base, int offset, int cmd_path, int *err)
{
    u32 reg = 0xffff;

    if (cmd_path == DPT_PATH_I2C) {
        reg = be32_to_cpu(cmd_get_hcr_i2c(sx_dev_id, hcr_base, offset, err));
    } else if (cmd_path == DPT_PATH_PCI_E) {
        reg = be32_to_cpu((__force __be32)cmd_get_hcr_pci(dev, offset));
        *err = 0;
    } else {
        printk(KERN_CRIT "%s(): Error: unsupported cmd_path %d \n",
               __func__, cmd_path);
        *err = -EINVAL;
    }

    return reg;
}


int sx_cmd_send_mad_sync(struct sx_dev *dev,
                         int            dev_id,
                         u32            in_modifier,
                         u8             op_modifier,
                         void          *in_mad,
                         int            in_size,
                         void          *out_mad,
                         int            out_size)
{
    struct sx_cmd_mailbox *inmailbox, *outmailbox;
    void                  *inbox;
    int                    err;

    if ((in_size > SX_MAILBOX_SIZE) || (out_size > SX_MAILBOX_SIZE)) {
        return -EINVAL;
    }

    inmailbox = sx_alloc_cmd_mailbox(dev, dev_id);
    if (IS_ERR(inmailbox)) {
        return PTR_ERR(inmailbox);
    }

    outmailbox = sx_alloc_cmd_mailbox(dev, dev_id);
    if (IS_ERR(outmailbox)) {
        sx_free_cmd_mailbox(dev, inmailbox);
        return PTR_ERR(outmailbox);
    }

    inbox = inmailbox->buf;
    memcpy(inbox, in_mad, in_size);

    err = sx_cmd_box(dev, dev_id, inmailbox,
                     outmailbox, in_modifier, op_modifier,
                     SX_CMD_MAD_IFC, SX_CMD_TIME_CLASS_C, in_size);

    if (!err) {
        memcpy(out_mad, outmailbox->buf, 256);
    }

    sx_free_cmd_mailbox(dev, inmailbox);
    sx_free_cmd_mailbox(dev, outmailbox);
    return err;
}


static int cmd_pending(struct sx_dev *dev, int sx_dev_id, int cmd_path, u16 op, int *err)
{
    u32 status;

    if ((op == SX_CMD_MAD_IFC) || (op == SX_CMD_INIT_MAD_DEMUX)) {
        status = cmd_get_hcr_reg(dev, sx_dev_id, SX_HCR_BASE, HCR_STATUS_OFFSET, cmd_path, err);
    } else {
        status = cmd_get_hcr_reg(dev, sx_dev_id, SX_HCR2_BASE, HCR_STATUS_OFFSET, cmd_path, err);
    }

    return status & (1 << HCR_GO_BIT);
}

static int wait_for_cmd_pending(struct sx_dev *dev, int sx_dev_id, int cmd_path, u16 op, int timeout)
{
    int           err = 0;
    unsigned long end = 0;
    unsigned long start = 0;

    start = jiffies;
    end = msecs_to_jiffies(timeout * 10) + start;

    while (cmd_pending(dev, sx_dev_id, cmd_path, op, &err) || (err != 0)) {
        if (time_after_eq(jiffies, end)) {
#ifdef INCREASED_TIMEOUT
            end = msecs_to_jiffies(timeout * 4000) + jiffies;
            sx_warn(dev,
                    "INCREASED_TIMEOUT is set, Skipping timeout. op=%d, timeout=%d, start=%lu, end=%lu\n",
                    op,
                    timeout,
                    start,
                    end);
            cond_resched();
            continue;
#else
            sx_warn(dev, "Go bit not cleared, op=%d, timeout=%d\n", op, timeout);
            return -ETIMEDOUT;
#endif
        }
        cond_resched();
    }

    return err;
}

static int sx_cmd_post_pci(struct sx_dev         *dev,
                           struct sx_cmd_mailbox *in_mb,
                           struct sx_cmd_mailbox *out_mb,
                           u32                    in_modifier,
                           u8                     op_modifier,
                           u16                    op,
                           u16                    token,
                           int                    event)
{
    struct sx_cmd *cmd = &sx_priv(dev)->cmd;
    int            ret = -EAGAIN;
    u64            in_param = in_mb ? (in_mb->is_in_param_imm ? in_mb->imm_data : in_mb->dma) : 0;
    u64            out_param = out_mb ? out_mb->dma : 0;
    u32 __iomem   *hcr = cmd->hcr;
    int            err = 0;

    mutex_lock(&cmd->hcr_mutex);

    err = wait_for_cmd_pending(dev, dev->device_id, DPT_PATH_PCI_E, op, (event ? GO_BIT_TIMEOUT_MSECS : 0));
    if (-ETIMEDOUT == err) {
        if (!dev->dev_stuck) {
            printk(KERN_ERR "Device %d is stuck from a previous command. Aborting command %s.\n",
                   dev->device_id, cmd_str(op));

            dev->dev_stuck = 1;
        }

        goto out;
    }

    if (dev->dev_stuck) {
        printk(KERN_INFO "Device %d is no longer stuck on previous command.\n",
               dev->device_id);

        dev->dev_stuck = 0;
    }

    /*
     * We use writel (instead of something like memcpy_toio)
     * because writes of less than 32 bits to the HCR don't work
     * (and some architectures such as ia64 implement memcpy_toio
     * in terms of writeb).
     */
    __raw_writel((__force u32)cpu_to_be32(in_param >> 32),
                 hcr + 0);
    __raw_writel((__force u32)cpu_to_be32(in_param & 0xfffffffful),
                 hcr + 1);
    __raw_writel((__force u32)cpu_to_be32(in_modifier),
                 hcr + 2);
    __raw_writel((__force u32)cpu_to_be32(out_param >> 32),
                 hcr + 3);
    __raw_writel((__force u32)cpu_to_be32(out_param & 0xfffffffful),
                 hcr + 4);
    __raw_writel((__force u32)cpu_to_be32(token << 16),
                 hcr + 5);

    /* __raw_writel may not order writes. */
    wmb();

    __raw_writel((__force u32)cpu_to_be32((1 << HCR_GO_BIT) |
                                          (event ? (1 << HCR_E_BIT) : 0) |
                                          (op_modifier << HCR_OPMOD_SHIFT) |
                                          op), hcr + 6);

    /*
     * Make sure that our HCR writes don't get mixed in with
     * writes from another CPU starting a FW command.
     */
    mmiowb();
    ret = 0;

out:
    mutex_unlock(&cmd->hcr_mutex);
    return ret;
}

static inline struct sx_cmd_mailbox * sx_mailbox(dma_addr_t *dma_addr)
{
    return container_of(dma_addr, struct sx_cmd_mailbox, dma);
}

static int sx_cmd_post_i2c(struct sx_dev         *dev,
                           int                    sx_dev_id,
                           struct sx_cmd_mailbox *in_mb,
                           struct sx_cmd_mailbox *out_mb,
                           u32                    in_modifier,
                           u8                     op_modifier,
                           u16                    op,
                           u16                    token,
                           int                    event,
                           int                    in_mb_size)
{
    struct sx_cmd *cmd = &sx_priv(dev)->cmd;
    int            ret = -EAGAIN;
    u32            hcr2 = (u32)SX_HCR2_BASE;
    u32            hcr_buf[7];
    int            err = 0;
    u32            tmp_u32;

    if ((op == SX_CMD_MAD_IFC) || (op == SX_CMD_INIT_MAD_DEMUX)) {
        hcr2 = (u32)SX_HCR_BASE;     /* to enable MAD over i2c for OOB bootstrap */
    } else if ((op != SX_CMD_QUERY_FW) &&
               (op != SX_CMD_QUERY_BOARDINFO) &&
               (op != SX_CMD_CONFIG_PROFILE) &&
               (op != SX_CMD_ACCESS_REG) &&
               (op != SX_CMD_INIT_SYSTEM_M_KEY) &&
               (op != SX_CMD_ISSU_FW)) {
        sx_err(dev, "command (0x%x) not supported by I2C ifc\n", op);
        return -EINVAL;
    }

    mutex_lock(&cmd->hcr_mutex);

    err = wait_for_cmd_pending(dev, sx_dev_id, DPT_PATH_I2C, op, I2C_GO_BIT_TIMEOUT_MSECS);
    if (-EUNATCH == err) {
        sx_err(dev, "client not ready yet for "
               "sx_dev_id %d\n", sx_dev_id);
        goto out;
    } else if (-ETIMEDOUT == err) {
        sx_warn(dev, "I2C go bit not cleared\n");
        if (sx_glb.sx_i2c.set_go_bit_stuck) {
            int i2c_dev_id;
            err = sx_dpt_get_i2c_dev_by_id(
                sx_dev_id,
                &i2c_dev_id);
            if (err) {
                sx_err(dev, "sx_dpt_get_i2c_dev_by_id "
                       "for dev_id: %d "
                       "failed !\n",
                       sx_dev_id);
                return -EINVAL;
            }

            sx_glb.sx_i2c.set_go_bit_stuck(i2c_dev_id);
        }

        goto out;
    } else if (err) {
        sx_err(dev, "client return error %d, "
               "sx_dev_id %d\n", err, sx_dev_id);
        goto out;
    }

    /*
     *   Some of the commands use mailboxes. In order to use
     *   mailboxes through the i2c, special area is reserved on
     *   the i2c address space that can be used for input and
     *   output mailboxes. Such mailboxes are called Local
     *   Mailboxes. Copy the pci mailboxes to local mailboxes
     */
    if (in_mb) {
        ret = sx_dpt_i2c_write_buf(sx_dev_id,
                                   sx_glb.sx_dpt.dpt_info[sx_dev_id].in_mb_offset,
                                   in_mb->buf, in_mb_size);
        if (ret) {
            printk(KERN_DEBUG "sx_cmd_post_i2c: first write_buf "
                   "failed, err = %d\n", ret);
            goto out;
        }
    }

    /*
     *   When using a local mailbox, software
     *   should specify 0 as the Input/Output parameters.
     */
    memset(hcr_buf, 0, 28);
    hcr_buf[0] = 0;
    hcr_buf[1] = 0;
    if ((in_mb != NULL) && in_mb->is_in_param_imm) {
        tmp_u32 = in_mb->imm_data >> 32;
        hcr_buf[0] = cpu_to_be32(tmp_u32);
        tmp_u32 = in_mb->imm_data & 0xFFFFFFFF;
        hcr_buf[1] = cpu_to_be32(tmp_u32);
    }
    hcr_buf[2] = cpu_to_be32(in_modifier);
    hcr_buf[3] = 0;
    hcr_buf[4] = 0;
    hcr_buf[5] = cpu_to_be32(token << 16);
    hcr_buf[6] = cpu_to_be32((op_modifier << HCR_OPMOD_SHIFT) | op);
    ret = sx_dpt_i2c_write_buf(sx_dev_id, hcr2, (void*)hcr_buf,  28);
    if (ret) {
        printk(KERN_DEBUG "sx_cmd_post_i2c: second write_buf "
               "failed, err = %d\n", ret);
        goto out;
    }
    /* We write to go bit after writing all other HCR values */
    hcr_buf[6] |= cpu_to_be32(1 << HCR_GO_BIT);
    ret = sx_dpt_i2c_writel(
        sx_dev_id,
        hcr2 + 6 * sizeof(hcr2),
        hcr_buf[6]);
    if (ret) {
        printk(KERN_DEBUG "sx_cmd_post_i2c: first writel "
               "failed, err = %d\n", ret);
        goto out;
    }

    ret = 0;

out:
    mutex_unlock(&cmd->hcr_mutex);
    return ret;
}


static int sx_cmd_post(struct sx_dev         *dev,
                       int                    sx_dev_id,
                       struct sx_cmd_mailbox *in_mb,
                       struct sx_cmd_mailbox *out_mb,
                       u32                    in_modifier,
                       u8                     op_modifier,
                       u16                    op,
                       u16                    token,
                       int                    event,
                       int                    cmd_path,
                       int                    in_mb_size)
{
    int err = 0;

    if (cmd_path == DPT_PATH_I2C) {
        err = sx_cmd_post_i2c(dev, sx_dev_id, in_mb, out_mb,
                              in_modifier, op_modifier,
                              op, token, event, in_mb_size);
    } else if (cmd_path == DPT_PATH_PCI_E) {
        if (dev->pdev) {
            err = sx_cmd_post_pci(dev, in_mb, out_mb,
                                  in_modifier, op_modifier,
                                  op, token, event);
        }
    } else {
        printk(KERN_WARNING "%s(): Error: sx_dev_id %d unsupported "
               "cmd_path %d in_mod: 0x%x, op_mod: 0x%x "
               "op: 0x%x\n",
               __func__, sx_dev_id, cmd_path, in_modifier,
               op_modifier, op);
        err = -EINVAL;
    }

    return err;
}

static int sx_cmd_poll(struct sx_dev         *dev,
                       int                    sx_dev_id,
                       struct sx_cmd_mailbox *in_param,
                       struct sx_cmd_mailbox *out_param,
                       int                    out_is_imm,
                       u32                    in_modifier,
                       u8                     op_modifier,
                       u16                    op,
                       unsigned long          timeout,
                       int                    cmd_path,
                       int                    in_mb_size)
{
    struct sx_priv   *priv = sx_priv(dev);
    int               err = 0;
    u32               status;
    struct semaphore *poll_sem;
    int               i2c_dev_id = 0;
    int               hcr_base = SX_HCR2_BASE;

    poll_sem = (cmd_path == DPT_PATH_I2C) ?
               &priv->cmd.i2c_poll_sem : &priv->cmd.pci_poll_sem;
    down(poll_sem);

    if (cmd_path == DPT_PATH_I2C) {
        err = sx_dpt_get_i2c_dev_by_id(sx_dev_id, &i2c_dev_id);
        if (err) {
            goto out_sem;
        }

        if (!sx_glb.sx_i2c.enforce) {
            sx_err(dev, "enforce is NULL!!!\n");
            goto out_sem;
        }

        err = sx_glb.sx_i2c.enforce(i2c_dev_id);
        if (err) {
            sx_warn(dev, "I2C bus 0x%x of device %d is not ready. "
                    "command %s will not be performed. err = %d\n",
                    i2c_dev_id, sx_dev_id, cmd_str(op), err);
            goto out_sem;
        }
    }

    err = sx_cmd_post(dev, sx_dev_id, in_param, out_param, in_modifier,
                      op_modifier, op, CMD_POLL_TOKEN, 0, cmd_path, in_mb_size);
    if (err) {
        printk(KERN_WARNING "sx_cmd_poll: got err = %d "
               "from sx_cmd_post\n", err);
        goto out;
    }

#ifdef NO_PCI
    goto out;
#endif

    /*
     *  If in SW reset flow give the logic behind PCIe 100 msec to recover
     *  before read access
     */
    if ((dev->dev_sw_rst_flow == 1) && (cmd_path == DPT_PATH_PCI_E)) {
        msleep(100);
    }

    err = wait_for_cmd_pending(dev, sx_dev_id, cmd_path, op, timeout);
    if (err) {
        printk(KERN_WARNING "sx_cmd_poll: got err = %d from "
               "cmd_pending\n", err);
        goto out;
    }

    /* hcr_base is relevant only for I2C. PCI does not use this */
    if ((op == SX_CMD_MAD_IFC) || (op == SX_CMD_INIT_MAD_DEMUX)) {
        hcr_base = SX_HCR_BASE;
    } else {
        hcr_base = SX_HCR2_BASE;
    }

    if (out_is_imm && out_param) {
        out_param->imm_data =
            (u64)cmd_get_hcr_reg(dev, sx_dev_id, hcr_base,
                                 HCR_OUT_PARAM_OFFSET, cmd_path, &err) << 32 |
            (u64)cmd_get_hcr_reg(dev, sx_dev_id, hcr_base,
                                 HCR_OUT_PARAM_OFFSET + 4, cmd_path, &err);
    }

    status = cmd_get_hcr_reg(dev, sx_dev_id, hcr_base, HCR_STATUS_OFFSET, cmd_path, &err) >> 24;
    if (err) {
        printk(KERN_WARNING "Reading of HCR status after posting the "
               "mailbox has failed for %s command\n",
               cmd_str(op));
        goto out;
    }

    /*
     *  The FW writes 0x26 to status after SW reset command.
     *  Overriding to prevent error handling flow.
     */
    if ((dev->dev_sw_rst_flow == 1) &&
        (cmd_path == DPT_PATH_PCI_E) &&
        (status == 0x26)) {
        sx_info(dev, "%s. Got FW status 0x%x after SW reset\n",
                cmd_str(op), status);
        status = CMD_STAT_OK;
    }

    err = sx_status_to_errno(status);
    if (err) {
        sx_warn(dev, "%s failed. FW status = 0x%x\n", cmd_str(op), status);
    } else {
        if (cmd_path == DPT_PATH_I2C) {
            if (!err && out_param && out_param->buf) {
                memset(out_param->buf, 0, sx_glb.sx_dpt.dpt_info[sx_dev_id].out_mb_size);
                err = sx_dpt_i2c_read_buf(sx_dev_id, sx_glb.sx_dpt.dpt_info[sx_dev_id].out_mb_offset,
                                          out_param->buf, 200);
                if (err) {
                    sx_err(dev, "%s failed.error at sx_dpt_i2c_read_buf. err = %d\n", cmd_str(op), err);
                    goto out;
                }
            }
        }
    }

out:
    if (cmd_path == DPT_PATH_I2C) {
        sx_glb.sx_i2c.release(i2c_dev_id);
    }

out_sem:
    up(poll_sem);

    return err;
}

void sx_cmd_set_op_tlv(struct ku_operation_tlv *op_tlv, u32 reg_id, u8 method)
{
    op_tlv->type = 1;
    op_tlv->length = 4;
    op_tlv->dr = 0;
    op_tlv->status = 0;
    op_tlv->register_id = reg_id;
    op_tlv->r = 0;
    op_tlv->method = method; /* 0x01 = Query, 0x02 Write */
    op_tlv->op_class = 1;
    op_tlv->tid = 0;
}
EXPORT_SYMBOL(sx_cmd_set_op_tlv);

void sx_cmd_event(struct sx_dev *dev, u16 token, u8 status, u64 out_param)
{
    struct sx_priv        *priv = sx_priv(dev);
    struct sx_cmd_context *context =
        &priv->cmd.context[token & priv->cmd.token_mask];

    /* previously timed out command completing at long last */
    if (token != context->token) {
        return;
    }

    context->result = sx_status_to_errno(status);
    if (context->result) {
        sx_warn(dev, "command %s failed. FW status = %d, " \
                "driver result = %d\n",
                cmd_str(context->opcode), status, context->result);
    }

    context->out_param = out_param;
    complete(&context->done);
}
EXPORT_SYMBOL(sx_cmd_event);

static int sx_cmd_wait(struct sx_dev         *dev,
                       int                    sx_dev_id,
                       struct sx_cmd_mailbox *in_param,
                       struct sx_cmd_mailbox *out_param,
                       int                    out_is_imm,
                       u32                    in_modifier,
                       u8                     op_modifier,
                       u16                    op,
                       unsigned long          timeout,
                       int                    cmd_path)
{
    struct sx_cmd         *cmd = &sx_priv(dev)->cmd;
    struct sx_cmd_context *context;
    int                    err = 0;

    down(&cmd->event_sem);
    spin_lock(&cmd->context_lock);
    BUG_ON(cmd->free_head < 0);
    context = &cmd->context[cmd->free_head];
    context->token += cmd->token_mask + 1;
    context->opcode = op;
    cmd->free_head = context->next;
    spin_unlock(&cmd->context_lock);
    init_completion(&context->done);
#ifdef NO_PCI
    if (cmd_ifc_stub_func) {
        void *in_buf = in_param ? in_param->buf : NULL;
        void *out_buf = out_param ? out_param->buf : NULL;

        printk(KERN_INFO "Sending command 0x%x (%s) to the "
               "verification kernel module\n", op, cmd_str(op));
        err = cmd_ifc_stub_func(in_buf, out_buf, SX_MAILBOX_SIZE,
                                op_modifier, op, in_modifier, context->token);
        if (err) {
            printk(KERN_DEBUG PFX "Got error %d from cmd_ifc_stub_func", err);
        }
    } else {
        goto out;
    }
#else
    sx_cmd_post(dev, sx_dev_id, in_param, out_param, in_modifier,
                op_modifier, op, context->token, 1, cmd_path, 0);
#endif

#ifdef INCREASED_TIMEOUT
    if (!wait_for_completion_timeout(&context->done, msecs_to_jiffies(timeout * 4000))) {
#else
    if (!wait_for_completion_timeout(&context->done, msecs_to_jiffies(timeout))) {
#endif
        if (!context->done.done) {
            sx_err(dev, "command 0x%x (%s) timeout for "
                   "device %d\n", op, cmd_str(op), sx_dev_id);
            err = -EBUSY;
            goto out;
        }
    }

    err = context->result;
    if (err) {
        goto out;
    }

    if (out_is_imm && out_param) {
        out_param->imm_data = context->out_param;
    }

out:
    spin_lock(&cmd->context_lock);
    context->next = cmd->free_head;
    cmd->free_head = context - cmd->context;
    spin_unlock(&cmd->context_lock);

    up(&cmd->event_sem);
    return err;
}

void __dump_cmd(struct sx_dev         *dev,
                int                    sx_dev_id,
                struct sx_cmd_mailbox *in_param,
                struct sx_cmd_mailbox *out_param,
                int                    out_is_imm,
                u32                    in_modifier,
                u8                     op_modifier,
                u16                    op,
                unsigned long          timeout,
                int                    in_mb_size,
                int                    cmd_path)
{
    int print_cmd = 0;

    printk("%s(): in cmd_path: %d (1- i2c, 2 - pci), op:0x%x \n",
           __func__, cmd_path, op);

    if ((i2c_cmd_op == SX_DBG_CMD_OP_TYPE_ANY) ||
        ((i2c_cmd_op == 0x40) && (NULL != in_param) &&
         (i2c_cmd_reg_id == be16_to_cpu(((struct emad_operation *)
                                         (in_param->buf))->register_id)))) {
        print_cmd = 1;
    } else {
        return;
    }

    if (print_cmd && (NULL != in_param) && (NULL != in_param->buf)) {
        mem_blk_dump("CMD input dump", in_param->buf, 0x40);
    }

    if (print_cmd && (NULL != out_param) && (NULL != out_param->buf)) {
        mem_blk_dump("CMD out parameter dump", out_param->buf, 0x40);
    }

    if ((i2c_cmd_dump_cnt != 0xFFFF) && (i2c_cmd_dump_cnt > 0)) {
        i2c_cmd_dump_cnt--;
    }

    if (i2c_cmd_dump_cnt == 0) {
        i2c_cmd_dump = 0;
        i2c_cmd_dump_cnt = 0;
        i2c_cmd_op = 0xFFFF;
    }
}

int __sx_cmd(struct sx_dev         *dev,
             int                    sx_dev_id,
             struct sx_cmd_mailbox *in_param,
             struct sx_cmd_mailbox *out_param,
             int                    out_is_imm,
             u32                    in_modifier,
             u8                     op_modifier,
             u16                    op,
             unsigned long          timeout,
             int                    in_mb_size)
{
    int err = 0;
    int cmd_path = 0;

    if ((sx_dev_id == DEFAULT_DEVICE_ID) && is_sgmii_supported()) {
        err = sgmii_default_dev_id_get(&sx_dev_id);
        if (err) {
            return err;
        }
    }

    cmd_path = sx_dpt_get_cmd_path(sx_dev_id);

/*
 *   Example how to add limited registers support to PD :
 *
 *   switch (op) {
 *   case SX_CMD_ACCESS_REG:
 *   {
 *       u16 reg_id = be16_to_cpu(((struct emad_operation *)
 *               (in_param->buf))->register_id);
 *       switch (reg_id) {
 *       case PLD_REG_ID:
 * #ifdef SX_DEBUG
 *           printk(KERN_INFO PFX "__sx_cmd: Running command %s with reg_id 0x%x\n", cmd_str(op), reg_id);
 * #endif
 *           break;
 *
 *       default:
 *           printk(KERN_INFO PFX "__sx_cmd: command %s with reg_id 0x%x is not yet "
 *                   "supported. Not running it\n", cmd_str(op), reg_id);
 *           return 0;
 *       }
 *
 *       break;
 *   }
 *
 *   default:
 * #ifdef SX_DEBUG
 *       printk(KERN_INFO PFX "__sx_cmd: Running command %s\n", cmd_str(op));
 * #endif
 *       break;
 *   }
 */

#ifdef PD_BU

    /* all registers are opened */

#ifdef SX_DEBUG
    printk(KERN_INFO PFX "__sx_cmd: Running command %s\n", cmd_str(op));
#endif

#endif /* #ifdef PD_BU */

    if (cmd_path == DPT_PATH_INVALID) {
        if (op == SX_CMD_ACCESS_REG) {
            u16 reg_id = be16_to_cpu(((struct emad_operation *)
                                      (in_param->buf))->register_id);

            printk(KERN_ERR PFX "Command path in DPT for device %d is not valid. "
                   "Aborting command %s (register ID 0x%x)\n", sx_dev_id, cmd_str(op), reg_id);
        } else {
            printk(KERN_ERR PFX "Command path in DPT for device %d is not valid. "
                   "Aborting command %s\n", sx_dev_id, cmd_str(op));
        }

        return -EINVAL;
    }

    if (sx_priv(dev)->cmd.use_events && (cmd_path != DPT_PATH_I2C)) {
        err = sx_cmd_wait(dev, sx_dev_id, in_param, out_param,
                          out_is_imm, in_modifier, op_modifier,
                          op, timeout, cmd_path);
    } else {
        err = sx_cmd_poll(dev, sx_dev_id, in_param, out_param,
                          out_is_imm, in_modifier, op_modifier,
                          op, timeout, cmd_path, in_mb_size);
    }

    if (i2c_cmd_dump) {
        __dump_cmd(dev, sx_dev_id, in_param, out_param,
                   out_is_imm, in_modifier, op_modifier,
                   op, timeout, in_mb_size, cmd_path);
    }

#ifdef PD_BU
#ifdef SX_DEBUG
    if (!err) {
        printk(KERN_INFO PFX "__sx_cmd: command %s finished successfully\n", cmd_str(op));
    }
#endif
    if (err) {
        printk(KERN_INFO PFX "__sx_cmd: command %s finished with err %d\n", cmd_str(op), err);
    }
#endif
    return err;
}
EXPORT_SYMBOL(__sx_cmd);

void sx_cmd_unmap(struct sx_dev *dev)
{
    struct sx_cmd *cmd = &sx_priv(dev)->cmd;

    iounmap(cmd->hcr);
    cmd->hcr = NULL;
}

int sx_cmd_pool_create(struct sx_dev *dev)
{
    struct sx_cmd *cmd = &sx_priv(dev)->cmd;

    cmd->pool = pci_pool_create("sx_cmd", dev->pdev,
                                SX_MAILBOX_SIZE,
                                SX_MAILBOX_SIZE, 0);
    if (!cmd->pool) {
        return -ENOMEM;
    }

    return 0;
}

void sx_cmd_pool_destroy(struct sx_dev *dev)
{
    struct sx_cmd *cmd = &sx_priv(dev)->cmd;

    pci_pool_destroy(cmd->pool);
    cmd->pool = NULL;
}

int sx_cmd_init(struct sx_dev *dev)
{
    struct sx_cmd *cmd = &sx_priv(dev)->cmd;

    mutex_init(&cmd->hcr_mutex);
    sema_init(&cmd->pci_poll_sem, 1);
    sema_init(&cmd->i2c_poll_sem, 1);
    cmd->use_events = 0;
    cmd->toggle = 1;
    cmd->max_cmds = 10;

    return 0;
}

int sx_cmd_init_pci(struct sx_dev *dev)
{
    sx_priv(dev)->cmd.hcr = ioremap(pci_resource_start(dev->pdev, 0) +
                                    SX_HCR_BASE, SX_HCR_SIZE);
    if (!sx_priv(dev)->cmd.hcr) {
        sx_err(dev, "Couldn't map command register.");
        return -ENOMEM;
    }

    sx_info(dev, "map cmd: phys: 0x%llx , virtual: %p \n",
            (u64)(pci_resource_start(dev->pdev, 0) + SX_HCR_BASE),
            sx_priv(dev)->cmd.hcr);

    return 0;
}

/*
 * Switch to using events to issue FW commands (can only be called
 * after event queue for command events has been initialized).
 */
int sx_cmd_use_events(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);
    int             i;

/* #if defined(PD_BU)
 *   / The flow should be tested on Palladium/Protium once HW adds support /
 *   return 0; / No events yet... /
 #endif */

    if (priv->cmd.use_events == 1) {
        return 0;
    }

    priv->cmd.context = kmalloc(priv->cmd.max_cmds *
                                sizeof(struct sx_cmd_context), GFP_KERNEL);
    if (!priv->cmd.context) {
        return -ENOMEM;
    }

    for (i = 0; i < priv->cmd.max_cmds; ++i) {
        priv->cmd.context[i].token = i;
        priv->cmd.context[i].next = i + 1;
    }

    priv->cmd.context[priv->cmd.max_cmds - 1].next = -1;
    priv->cmd.free_head = 0;
    sema_init(&priv->cmd.event_sem, priv->cmd.max_cmds);
    spin_lock_init(&priv->cmd.context_lock);
    for (priv->cmd.token_mask = 1;
         priv->cmd.token_mask < priv->cmd.max_cmds;
         priv->cmd.token_mask <<= 1) {
        /* nothing */
    }
    --priv->cmd.token_mask;

    priv->cmd.use_events = 1;
    down(&priv->cmd.pci_poll_sem);

    return 0;
}
EXPORT_SYMBOL(sx_cmd_use_events);

/*
 * Switch back to polling (used when shutting down the device)
 */
void sx_cmd_use_polling(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);
    int             i;

    if (priv->cmd.use_events == 0) {
        return;
    }

    priv->cmd.use_events = 0;

    for (i = 0; i < priv->cmd.max_cmds; ++i) {
        down(&priv->cmd.event_sem);
    }

    kfree(priv->cmd.context);

    up(&priv->cmd.pci_poll_sem);
}
EXPORT_SYMBOL(sx_cmd_use_polling);

struct sx_cmd_mailbox * sx_alloc_cmd_mailbox(struct sx_dev *dev, int sx_dev_id)
{
    struct sx_cmd_mailbox *mailbox;

    if (!dev) {
        printk(KERN_ERR "cannot allocate mailbox on a NULL device\n");
        return ERR_PTR(-EINVAL);
    }

    mailbox = kzalloc(sizeof *mailbox, GFP_KERNEL);
    if (!mailbox) {
        return ERR_PTR(-ENOMEM);
    }

    if (!dev->pdev || is_sgmii_device(sx_dev_id)) {
        mailbox->buf = kzalloc(SX_MAILBOX_SIZE, GFP_KERNEL);
    } else {
        if (!sx_dpt_is_path_valid(dev->device_id, DPT_PATH_PCI_E)) {
            kfree(mailbox);
            return ERR_PTR(-ENOMEM);
        }

        mailbox->buf = pci_pool_alloc(sx_priv(dev)->cmd.pool,
                                      GFP_KERNEL, &mailbox->dma);
    }

    if (!mailbox->buf) {
        kfree(mailbox);
        return ERR_PTR(-ENOMEM);
    }

    return mailbox;
}
EXPORT_SYMBOL(sx_alloc_cmd_mailbox);


void sx_free_cmd_mailbox(struct sx_dev *dev, struct sx_cmd_mailbox *mailbox)
{
    if (!mailbox) {
        return;
    }

    if (!dev->pdev) {
        kfree(mailbox->buf);
    } else {
        if (mailbox->dma) {
            pci_pool_free(sx_priv(dev)->cmd.pool, mailbox->buf,
                          mailbox->dma);
        }
    }

    kfree(mailbox);
}
EXPORT_SYMBOL(sx_free_cmd_mailbox);


/************************************************
 *                  EOF                         *
 ***********************************************/
