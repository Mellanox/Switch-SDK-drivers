/*
 * Copyright (C) 2008-2021 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

/************************************************
 * Includes
 ***********************************************/
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/ktime.h>
#include "sx.h"
#include "dev_db.h"

/************************************************
 * Definitions
 ***********************************************/
#define SX_CR_DUMP_CMD_MEM_SIZE                     0x00020
#define SX_CR_DUMP_CMD_MEM_OPCODE_OFFSET            0
#define SX_CR_DUMP_CMD_MEM_STATUS_OFFSET            0x4
#define SX_CR_DUMP_CMD_MEM_HOST_BASE_ADDR_OFFSET    0x8
#define SX_CR_DUMP_CMD_MEM_HOST_SIZE_ALLOCET_OFFSET 0x10
#define SX_CR_DUMP_CMD_MEM_HOST_SIZE_USED_OFFSET    0x18
#define SX_CR_DUMP_LAYER1_TIMER_SLEEP_US            2000
#define SX_CR_DUMP_WAIT_TIME_AFTER_CANCEL_FW        1000
#define SX_CR_DUMP_DEFAULT_HOST_SIZE                (64 * 1024 * 1024)

#define ROUNDUP(val, align) \
    ((((val) / (align)) * (align)) + (((val) % (align)) ? (align) : 0))

enum {
    SX_CR_DUMP_FW_STATUS_IDLE = 0,
    SX_CR_DUMP_FW_STATUS_ONGOING,
    SX_CR_DUMP_FW_STATUS_PENGDING,
};

/************************************************
 * Globals
 ***********************************************/
extern struct sx_globals sx_glb;
static u32               __cap_dump_host_size_flat = SX_CR_DUMP_DEFAULT_HOST_SIZE;
static u32               __cap_dump_host_size_gw = SX_CR_DUMP_DEFAULT_HOST_SIZE;
static u32               __cap_dump_host_size_gdb = SX_CR_DUMP_DEFAULT_HOST_SIZE;
static u8                __dumped_sn = 0;
static u16               __trans_sn = 0;
static u32               __dumped_bytes = 0;
static u32               __cr_dump_memblk_size = SX_CR_DUMP_MEMBLK_SIZE;
static dma_addr_t        __dma_addr = 0;
static bool              __dma_buff_used = false;
static int               __dma_size = 0;
static bool              __gdb_dump_mode = false;

/************************************************
 * Functions
 ***********************************************/
static bool __fw_in_idle_status(struct sx_dev *dev, u8 *ret_opcode, u8 *ret_status);
static bool __fw_in_pending_status(struct sx_dev *dev, u8 *ret_opcode, u8 *ret_status);
static void __get_cr_dump_ret(struct sx_dev *dev, struct sx_cr_dump_cmd_mem *cr_dump_ret);
static int __set_fw_cancel(struct sx_dev *dev);
static int __fw_crdump_precheck(struct sx_dev *dev, dma_addr_t dma_addr, u8 opcode, int dump_size);
static int __fw_crdump_postcheck(struct sx_dev *dev, u8 opcode, unsigned char *buf,
                                 struct sx_cr_dump_ret *cr_dump_ret);
static void __virt_unmap_dma_bus(struct sx_dev *dev, dma_addr_t dma_addr, int size);
static int __virt_map_dma_bus(struct sx_dev *dev, void *virt_addr, int size, dma_addr_t *dma_addr);


static bool __fw_in_idle_status(struct sx_dev *dev, u8 *ret_opcode, u8 *ret_status)
{
    u32             tmp = 0;
    u8              opcode = 0, status = 0;
    struct sx_priv *priv = sx_priv(dev);

    opcode = be32_to_cpu(__raw_readl(priv->cr_dump_base)) & 0xFF;
    tmp = be32_to_cpu(__raw_readl(priv->cr_dump_base + SX_CR_DUMP_CMD_MEM_STATUS_OFFSET));
    status = tmp & 0xFF;

    if (ret_opcode) {
        *ret_opcode = opcode;
    }
    if (ret_status) {
        *ret_status = status;
    }

    return (status == SX_CR_DUMP_FW_STATUS_IDLE) && (opcode == SX_CR_DUMP_OP_NOP);
}

static bool __fw_in_pending_status(struct sx_dev *dev, u8 *ret_opcode, u8 *ret_status)
{
    u32             tmp = 0;
    u8              opcode = 0, status = 0;
    struct sx_priv *priv = sx_priv(dev);

    opcode = be32_to_cpu(__raw_readl(priv->cr_dump_base)) & 0xFF;
    tmp = be32_to_cpu(__raw_readl(priv->cr_dump_base + SX_CR_DUMP_CMD_MEM_STATUS_OFFSET));
    status = tmp & 0xFF;

    if (ret_opcode) {
        *ret_opcode = opcode;
    }
    if (ret_status) {
        *ret_status = status;
    }

    return (status == SX_CR_DUMP_FW_STATUS_PENGDING) && (opcode == SX_CR_DUMP_OP_NOP);
}

static void __get_cr_dump_ret(struct sx_dev *dev, struct sx_cr_dump_cmd_mem *cr_dump_ret)
{
    u32             tmp = 0;
    u32             size_h = 0, size_l = 0;
    struct sx_priv *priv = sx_priv(dev);

    cr_dump_ret->opcode = be32_to_cpu(__raw_readl(priv->cr_dump_base)) & 0xFF;

    tmp = be32_to_cpu(__raw_readl(priv->cr_dump_base + SX_CR_DUMP_CMD_MEM_STATUS_OFFSET));
    cr_dump_ret->trans_sn = tmp >> 16 & 0xFFFF;
    cr_dump_ret->dump_sn = tmp >> 8 & 0xFF;
    cr_dump_ret->status = tmp & 0xFF;

    size_h = be32_to_cpu(__raw_readl(priv->cr_dump_base + SX_CR_DUMP_CMD_MEM_HOST_SIZE_USED_OFFSET));
    size_l = be32_to_cpu(__raw_readl(priv->cr_dump_base + SX_CR_DUMP_CMD_MEM_HOST_SIZE_USED_OFFSET + 4));
    cr_dump_ret->host_size_used = (u64)size_h << 32 | (u64)size_l;
    if (cr_dump_ret->host_size_used > __cr_dump_memblk_size) {
        /* the conflict should be within FW logic, and SDK dumps within the limit queried from FW */
        printk(
            KERN_ERR "host_size_used is too big (0x%llx), size (MSB:0x%x, LSB:0x%x) may be wrong, and reduce it to sent blk size 0x%x\n",
            cr_dump_ret->host_size_used,
            size_h,
            size_l,
            __cr_dump_memblk_size);
        cr_dump_ret->host_size_used = __cr_dump_memblk_size;
    }
}

static void __clear_dma_map(struct sx_dev *dev, bool *dma_used, dma_addr_t *dma_addr, int *dma_size)
{
    if (*dma_used) {
        __virt_unmap_dma_bus(dev, *dma_addr, *dma_size);
        *dma_used = false;
        *dma_size = 0;
    }
}

/*
 *  After setting FW cancel, FW is expected to be IDLE within 1 ms at most.
 *  FW should be in fatal error status if it is still not IDLE.
 */
static int __set_fw_cancel(struct sx_dev *dev)
{
    u8              opcode = 0, status = 0;
    int             err = 0;
    struct sx_priv *priv = sx_priv(dev);

    __raw_writel((__force u32)cpu_to_be32(SX_CR_DUMP_OP_CANCEL & 0xff), priv->cr_dump_base);

    if (!__fw_in_idle_status(dev, &opcode, &status)) {
        usleep_range(SX_CR_DUMP_WAIT_TIME_AFTER_CANCEL_FW, SX_CR_DUMP_WAIT_TIME_AFTER_CANCEL_FW + 10);
        if (!__fw_in_idle_status(dev, &opcode, &status)) {
            printk(KERN_CRIT "%s(): FW cannot cancel (status %d, opcode %d).\n",
                   __func__, status, opcode);
            err = SX_CR_DUMP_RET_FATAL_FW_ERR;
            goto out;
        }
    }
out:
    __clear_dma_map(dev, &__dma_buff_used, &__dma_addr, &__dma_size);
    return err;
}

/*
 *  Check cr_dump base addr, size be 4KB align;
 *  Check dumped size + dump size will not override cap_dump_host_size.
 *  If any check fails, set FW cancel and return error.
 */
static int __fw_crdump_precheck(struct sx_dev *dev, dma_addr_t dma_addr, u8 opcode, int dump_size)
{
    static u32 cap_dump_host_size = 0;
    int        err = 0, err2 = 0;

    if (dump_size % SXD_CR_DUMP_HOST_MEM_ALIGN || dma_addr % SXD_CR_DUMP_HOST_MEM_ALIGN) {
        printk(
            KERN_ERR "ERROR: FW params error: host base address (0x%llx) or host size (0x%x) are not %d bytes aligned.\n",
            dma_addr,
            dump_size,
            SXD_CR_DUMP_HOST_MEM_ALIGN);
        err = SX_CR_DUMP_RET_CANCEL_FW_PARAM_MISALIGN;
        goto out;
    }

    __cr_dump_memblk_size = dump_size;
    __gdb_dump_mode = false;

    switch (opcode) {
    case SX_CR_DUMP_OP_START_FLAT:
        __dumped_bytes = 0;
        cap_dump_host_size = __cap_dump_host_size_flat;
        break;

    case SX_CR_DUMP_OP_START_GW:
        __dumped_bytes = 0;
        cap_dump_host_size = __cap_dump_host_size_gw;
        break;

    case SX_CR_DUMP_OP_START_GDB:
        __dumped_bytes = 0;
        cap_dump_host_size = ROUNDUP(__cap_dump_host_size_gdb, SXD_CR_DUMP_HOST_MEM_ALIGN);
        __gdb_dump_mode = true;
        break;

    default:
        break;
    }

    if (__dumped_bytes + dump_size > cap_dump_host_size) {
        printk(
            KERN_ERR "Total cr_dump dump size (%u) is too big to be handled by FW: Total cr_dump size (dumped:%u, to be dumped:%u) is bigger than cap_dump_host_size (%u).\n",
            __dumped_bytes + dump_size,
            __dumped_bytes,
            dump_size,
            cap_dump_host_size);
        err = SX_CR_DUMP_RET_CANCEL_DUMP_SIZE_OVERFLOW;
        goto out;
    }
out:
    if (err) {
        err2 = __set_fw_cancel(dev);
        if (err2) {
            printk(
                KERN_ERR "FATAL FW ERROR: cannot cancel FW cr-dump after a fw cr-dump pre-check error (%d), opcode (%d).\n",
                err,
                opcode);
        }
    }
    return err;
}

/*
 *  Check dump_sn, trans_sn, dumped_size after one FW cr_dump. If some error occurs, set FW cancel and return error.
 */
static int __fw_crdump_postcheck(struct sx_dev *dev, u8 opcode, unsigned char *buf, struct sx_cr_dump_ret *cr_dump_ret)
{
    int err = 0, err2 = 0;
    u32 dw1 = 0, dw2 = 0;

    __get_cr_dump_ret(dev, &(cr_dump_ret->ret_cmd_mem));
    if (cr_dump_ret->ret_cmd_mem.host_size_used > __cr_dump_memblk_size) {
        printk(KERN_ERR "cr_dump: returned host_size_used (%llu) is bigger than allocated memory block size: %u.\n",
               cr_dump_ret->ret_cmd_mem.host_size_used,
               __cr_dump_memblk_size);
        err = SX_CR_DUMP_RET_CANCEL_FW_WRITE_OVERWRITE;
        goto out;
    }

    switch (opcode) {
    case SX_CR_DUMP_OP_START_FLAT:
    case SX_CR_DUMP_OP_START_GW:
    case SX_CR_DUMP_OP_START_GDB:
    case SX_CR_DUMP_OP_START_WAIT:
        __dumped_sn = cr_dump_ret->ret_cmd_mem.dump_sn;
        __trans_sn = 0;
        break;

    case SX_CR_DUMP_OP_CONT:
    case SX_CR_DUMP_OP_CONT_WAIT:
        if (__dumped_sn != cr_dump_ret->ret_cmd_mem.dump_sn) {
            printk(KERN_ERR "cr_dump dump_sn mismatch: return value (%u), expected value (%u).\n",
                   cr_dump_ret->ret_cmd_mem.dump_sn,
                   __dumped_sn);
            err = SX_CR_DUMP_RET_CANCEL_DUMPSN_ERR;
            goto out;
        }
        __trans_sn++;
        if (__trans_sn != cr_dump_ret->ret_cmd_mem.trans_sn) {
            printk(KERN_ERR "cr_dump trans_sn mismatch: return value (%u), expected value (%u).\n",
                   cr_dump_ret->ret_cmd_mem.trans_sn,
                   __trans_sn);
            err = SX_CR_DUMP_RET_CANCEL_TRANSSN_ERR;
            goto out;
        }
        break;

    default:
        printk(KERN_NOTICE "no need to check opcode (%u).\n", opcode);
        goto out;
    }

    if (cr_dump_ret->ret_cmd_mem.host_size_used >= SX_CR_DUMP_CANARY_BYTE_NUM) {
        dw1 = be32_to_cpu(*(u32 *)(buf + cr_dump_ret->ret_cmd_mem.host_size_used - SX_CR_DUMP_CANARY_BYTE_NUM));
        dw2 = be32_to_cpu(*(u32 *)(buf + cr_dump_ret->ret_cmd_mem.host_size_used - SX_CR_DUMP_CANARY_BYTE_NUM + 4));
        if ((dw1 != SX_CR_DUMP_CANARY_MAGIC_WORD) || (dw2 != SX_CR_DUMP_CANARY_MAGIC_WORD)) {
            printk(KERN_ERR "cr_dump canary word mismatch: return value (0x%X, 0x%X), expected value (0x%X, 0x%X).\n",
                   dw1, dw2, SX_CR_DUMP_CANARY_MAGIC_WORD, SX_CR_DUMP_CANARY_MAGIC_WORD);
            err = SX_CR_DUMP_RET_CANCEL_FW_WRITE_OVERWRITE;
            goto out;
        }
    }
    __dumped_bytes += cr_dump_ret->ret_cmd_mem.host_size_used;

out:
    if (err) {
        err2 = __set_fw_cancel(dev);
        if (err2) {
            printk(
                KERN_ERR "FATAL FW ERROR: cannot cancel FW cr-dump after a fw cr-dump post-check error (%d), opcode (%d).\n",
                err,
                opcode);
        }
    }
    return err;
}
static void __virt_unmap_dma_bus(struct sx_dev *dev, dma_addr_t dma_addr, int size)
{
    dma_unmap_single(&dev->pdev->dev, dma_addr, size, DMA_BIDIRECTIONAL);
}

static int __virt_map_dma_bus(struct sx_dev *dev, void *virt_addr, int size, dma_addr_t *dma_addr)
{
    int err = 0;

    *dma_addr = dma_map_single(&dev->pdev->dev, virt_addr, size, DMA_BIDIRECTIONAL);
    if (dma_mapping_error(&dev->pdev->dev, *dma_addr)) {
        printk(
            KERN_ERR PFX "__virt_map_dma_bus: failed to map (dma_map_single) virtual_addr(0x%p, physical_addr: 0x%llx) to dma bus address\n",
            virt_addr,
            virt_to_phys(virt_addr));
        err = -ENOMEM;
        goto out;
    }
out:
    if (err) {
        printk(KERN_ERR PFX "__virt_map_dma_bus: err (%d)\n", err);
    }
    return err;
}

static bool __skip_setting_fw(u8 ret_opcode)
{
    return ((ret_opcode == SX_CR_DUMP_OP_START_WAIT) || (ret_opcode == SX_CR_DUMP_OP_CONT_WAIT));
}

static int __trigger_fw_cr_dump(struct sx_dev         *dev,
                                u8                     opcode,
                                unsigned char         *buf,
                                int                    size,
                                struct sx_cr_dump_ret *cr_dump_ret)
{
    u8              ret_opcode = 0, ret_status = 0;
    u32             lay1_waited_num = 0;
    u32             cr_dump_wait_us = 0;
    int             err = 0;
    struct sx_priv *priv = sx_priv(dev);

    if (!__skip_setting_fw(opcode)) {
        if (!__dma_buff_used) {
            err = __virt_map_dma_bus(dev, buf, size, &__dma_addr);
            if (err) {
                goto out;
            }
            __dma_buff_used = true;
            __dma_size = size;
        }
        err = __fw_crdump_precheck(dev, __dma_addr, opcode, size);
        if (err) {
            goto out;
        }

        dma_sync_single_for_device(&dev->pdev->dev, __dma_addr, size, DMA_BIDIRECTIONAL);
        __raw_writel((__force u32)cpu_to_be32((__force u64)(__dma_addr >> 32) & 0xfffffffful),
                     priv->cr_dump_base + SX_CR_DUMP_CMD_MEM_HOST_BASE_ADDR_OFFSET);     /*MSB */
        __raw_writel((__force u32)cpu_to_be32((__force u64)__dma_addr & 0xfffffffful),
                     priv->cr_dump_base + SX_CR_DUMP_CMD_MEM_HOST_BASE_ADDR_OFFSET + 4); /*lSB */

        __raw_writel((__force u32)cpu_to_be32(0), priv->cr_dump_base + SX_CR_DUMP_CMD_MEM_HOST_SIZE_ALLOCET_OFFSET); /*MSB */
        __raw_writel((__force u32)cpu_to_be32((size) & 0xfffffffful),
                     priv->cr_dump_base + SX_CR_DUMP_CMD_MEM_HOST_SIZE_ALLOCET_OFFSET + 4);                          /*LSB */

        /* make sure all other stuff written before triggering opcode. */
        wmb();

        __raw_writel((__force u32)cpu_to_be32(opcode & 0xff), priv->cr_dump_base + SX_CR_DUMP_CMD_MEM_OPCODE_OFFSET);
    } else {
        if (!__dma_buff_used) {
            printk(
                KERN_ERR "__trigger_fw_cr_dump: wrong opcode (%d) to continue waiting because no dma transaction on-going (dma:0x%llx, dma_size:%d).\n",
                opcode,
                __dma_addr,
                __dma_size);
        }
    }

    /* LAYER1 timeout value is not greater than 3*IN_WAIT_FW_DUMP_MS. */
    do {
        if (lay1_waited_num == 0) {
            cr_dump_wait_us = SX_SECURE_DUMP_MIN_WAIT_FW_DUMP_MS(__cr_dump_memblk_size, __gdb_dump_mode) * 1000;
            if (cr_dump_wait_us == 0) {
                printk(KERN_ERR "mistaken memory block (%u), and wait time (%u).\n",
                       __cr_dump_memblk_size,
                       cr_dump_wait_us);
                cr_dump_wait_us = 40000; /* wait time for default 512KB memory block */
            }
            usleep_range(cr_dump_wait_us, cr_dump_wait_us + 10);
            /* the remaining timeout is 2 X cr_dump_wait_us */
            cr_dump_wait_us =
                SX_SECURE_DUMP_MAX_WAIT_FW_DUMP_MS(__cr_dump_memblk_size, __gdb_dump_mode) * 1000 - cr_dump_wait_us;
        } else {
            usleep_range(SX_CR_DUMP_LAYER1_TIMER_SLEEP_US, SX_CR_DUMP_LAYER1_TIMER_SLEEP_US + 10);
        }
        if (__fw_in_idle_status(dev, &ret_opcode, &ret_status)) {
            dma_sync_single_for_cpu(&dev->pdev->dev, __dma_addr, __dma_size, DMA_BIDIRECTIONAL);
            err = __fw_crdump_postcheck(dev, opcode, buf, cr_dump_ret);
            if (err) {
                goto out;
            }
            err = SX_CR_DUMP_RET_FINISH;
            goto out;
        }
        if (ret_status == SX_CR_DUMP_FW_STATUS_PENGDING) {
            dma_sync_single_for_cpu(&dev->pdev->dev, __dma_addr, __dma_size, DMA_BIDIRECTIONAL);
            err = __fw_crdump_postcheck(dev, opcode, buf, cr_dump_ret);
            if (err) {
                goto out;
            }
            err = SX_CR_DUMP_RET_TO_BE_CONT;
            goto out;
        }
        /* FW should still be ONGOING */
        if (ret_status != SX_CR_DUMP_FW_STATUS_ONGOING) {
            printk(KERN_CRIT "%s(): FW status (%d) is invalid (opcode: %d), and FW may be mess-up.\n",
                   __func__, ret_status, ret_opcode);
            err = SX_CR_DUMP_RET_FATAL_FW_ERR;
            goto out;
        }
        lay1_waited_num++;
    } while (lay1_waited_num < (cr_dump_wait_us / SX_CR_DUMP_LAYER1_TIMER_SLEEP_US));

    printk(KERN_NOTICE "cr_dump LAYER1 timeout, lay1_waited_num (%u).\n", lay1_waited_num);
    err = SX_CR_DUMP_RET_LAYER1_TIMEOUT;
out:
    if (err != SX_CR_DUMP_RET_LAYER1_TIMEOUT) {
        __clear_dma_map(dev, &__dma_buff_used, &__dma_addr, &__dma_size);
    }
    return err;
}
int sx_core_cr_dump_start(struct sx_dev         *dev,
                          int                    type,
                          unsigned char         *buf,
                          int                    size,
                          struct sx_cr_dump_ret *cr_dump_ret)
{
    u8  opcode = 0, status = 0;
    int check_ret = 0;

    switch (type) {
    case SX_CR_DUMP_OP_START_FLAT:
        opcode = SX_CR_DUMP_OP_START_FLAT;
        break;

    case SX_CR_DUMP_OP_START_GDB:
        opcode = SX_CR_DUMP_OP_START_GDB;
        break;

    case SX_CR_DUMP_OP_START_GW:
        printk(KERN_ERR "cr_dump type (%u) is not supported.\n", type);
        return -EFAULT;

    default:
        printk(KERN_ERR "ERROR: wrong cr_dump type (%u).\n", type);
        return -EFAULT;
    }

    if (!__fw_in_idle_status(dev, NULL, &status)) {
        printk(KERN_ERR "ERROR: cannot start cr-dump, because old dump is not finished.\n");
        /* Abnormal FW state, and should try to set FW cancel to recover FW */
        check_ret = __set_fw_cancel(dev);
        if (check_ret) {
            printk(KERN_ERR "FATAL FW ERROR: cannot cancel FW cr-dump while starting a cr-dump.\n");
            return check_ret;
        }
        return SX_CR_DUMP_RET_CANCEL_OLD_DUMP;
    }

    return __trigger_fw_cr_dump(dev, opcode, buf, size, cr_dump_ret);
}


int sx_core_cr_dump_continue(struct sx_dev         *dev,
                             int                    type,
                             unsigned char         *buf,
                             int                    size,
                             struct sx_cr_dump_ret *cr_dump_ret)
{
    u8  opcode = 0, status = 0;
    int check_ret = 0;

    if (!__fw_in_pending_status(dev, &opcode, &status)) {
        printk(
            KERN_ERR "ERROR: cannot continue cr-dump, because of fw status (%d) not being PENDING. Try to set FW CANCEL.\n",
            status);
        /* Abnormal FW state, and should try to set FW cancel to recover FW */
        check_ret = __set_fw_cancel(dev);
        if (check_ret) {
            printk(KERN_ERR "FATAL FW ERROR: cannot cancel FW cr-dump while continue a ongoing cr-dump.\n");
            return check_ret;
        }
        return SX_CR_DUMP_RET_CANCEL_MESS_FW;
    }

    return __trigger_fw_cr_dump(dev, SX_CR_DUMP_OP_CONT, buf, size, cr_dump_ret);
}

int sx_core_cr_dump_cancel(struct sx_dev *dev)
{
    int err = 0;

    err = __set_fw_cancel(dev);
    if (!err) {
        err = SX_CR_DUMP_RET_CANCEL_GENERAL;
    }
    return err;
}

static int __parse_cr_dump_params(struct ku_cr_dump *params, struct sx_dev **dev, u8 *opcode)
{
    int err = 0;

    if (params->opcode != SX_CR_DUMP_OP_INVALID) {
        *opcode = params->opcode;
    } else {
        if (params->size == 0) {
            *opcode = SX_CR_DUMP_OP_CANCEL;
        } else if (params->dumped_size == 0) {
            *opcode = SX_CR_DUMP_OP_START_FLAT;
        } else if (params->dumped_size > 0) {
            *opcode = SX_CR_DUMP_OP_CONT;
        }
    }

    *dev = sx_dev_db_get_dev_by_id(params->dev_id);
    if (!(*dev)) {
        printk(KERN_ERR PFX "Failed to get device from ID %d\n", params->dev_id);
        goto out;
    }

out:
    return err;
}

int sx_core_cr_dump_handler(struct ku_cr_dump *read_data, unsigned char *buf)
{
    struct sx_dev *dev = NULL;
    int            err;
    u8             opcode;

    err = __parse_cr_dump_params(read_data, &dev, &opcode);
    if (err) {
        printk(KERN_ERR PFX "ctrl_cmd_cr_dump: Fails to parse syscall params (dev_id: %d), err = %d\n",
               read_data->dev_id, err);
        goto out;
    }

    switch (opcode) {
    case SX_CR_DUMP_OP_CANCEL:
        err = sx_core_cr_dump_cancel(dev);
        break;

    case SX_CR_DUMP_OP_START_FLAT:
    case SX_CR_DUMP_OP_START_GDB:
        err = sx_core_cr_dump_start(dev, opcode, buf, read_data->size, &(read_data->ret));
        break;

    case SX_CR_DUMP_OP_CONT:
        err = sx_core_cr_dump_continue(dev, opcode, buf, read_data->size, &(read_data->ret));
        break;

    case SX_CR_DUMP_OP_START_WAIT:
        err = __trigger_fw_cr_dump(dev, opcode, buf, read_data->size, &(read_data->ret));
        break;

    case SX_CR_DUMP_OP_CONT_WAIT:
        err = __trigger_fw_cr_dump(dev, opcode, buf, read_data->size, &(read_data->ret));
        break;

    case SX_CR_DUMP_OP_START_GW:
        printk(KERN_ERR "cr_dump opcode (%u) is not supported.\n", opcode);
        err = SX_CR_DUMP_RET_NOT_SUPPORTED;
        break;

    default:
        printk(KERN_ERR "ERROR: wrong cr_dump opcode (%u).\n", opcode);
        err = SX_CR_DUMP_RET_NOT_SUPPORTED;
        break;
    }
    if (err > 0) {
        switch (err) {
        case SX_CR_DUMP_RET_NOT_SUPPORTED:
        case SX_CR_DUMP_RET_CANCEL_GENERAL:
        case SX_CR_DUMP_RET_CANCEL_OLD_DUMP:
        case SX_CR_DUMP_RET_CANCEL_MESS_FW:
        case SX_CR_DUMP_RET_CANCEL_FW_PARAM_MISALIGN:
        case SX_CR_DUMP_RET_CANCEL_DUMP_SIZE_OVERFLOW:
        case SX_CR_DUMP_RET_CANCEL_DUMPSN_ERR:
        case SX_CR_DUMP_RET_CANCEL_TRANSSN_ERR:
        case SX_CR_DUMP_RET_CANCEL_FW_WRITE_OVERWRITE:
        case SX_CR_DUMP_RET_CANCEL_CANARY_ERR:
        case SX_CR_DUMP_RET_FATAL_FW_ERR:
            printk(KERN_ERR PFX "sx_core_cr_dump_handler(): Fails to call opcode (%d), err = %d\n",
                   read_data->opcode, err);
            break;

        case SX_CR_DUMP_RET_FINISH:
        case SX_CR_DUMP_RET_TO_BE_CONT:
        case SX_CR_DUMP_RET_LAYER1_TIMEOUT:
            break;

        default:
            printk(KERN_ERR PFX "sx_core_cr_dump_handler(): Fails to call opcode (%d), unknown err = %d\n",
                   read_data->opcode, err);
            break;
        }
        read_data->ret.ret_code = err;
        err = 0;
    } else {
        read_data->ret.ret_code = 0;
    }

out:
    return err;
}

int sx_core_cr_dump_get_cap_dump_host_size(u8 opcode, struct sx_cr_dump_ret *ret)
{
    int err = 0;

    switch (opcode) {
    case SX_CR_DUMP_OP_GET_GDB_DUMP_LIMIT:
        ret->ret_cmd_mem.host_size_used = __cap_dump_host_size_gdb;
        break;

    default:
        printk(KERN_ERR "ERROR: wrong cr_dump opcode (%u).\n", opcode);
        err = SX_CR_DUMP_RET_NOT_SUPPORTED;
        break;
    }
    if (ret->ret_cmd_mem.host_size_used == 0) {
        err = SX_CR_DUMP_RET_NOT_SUPPORTED;
    }
    ret->ret_code = err;

    return err;
}

int sx_core_cr_dump_init(struct sx_priv *priv)
{
    priv->cr_dump_base = ioremap(pci_resource_start(priv->dev.pdev,
                                                    priv->fw.cr_dump_bar) + priv->fw.cr_dump_offset,
                                 SX_CR_DUMP_CMD_MEM_SIZE);
    if (!priv->cr_dump_base) {
        printk("Couldn't map cr dump command mem register, aborting.\n");
        return -ENOMEM;
    }
    if (priv->fw.cap_dump_host_size_flat > 0) {
        __cap_dump_host_size_flat = priv->fw.cap_dump_host_size_flat;
    }
    if (priv->fw.cap_dump_host_size_gw > 0) {
        __cap_dump_host_size_gw = priv->fw.cap_dump_host_size_gw;
    }
    if (priv->fw.cap_dump_host_size_gdb > 0) {
        __cap_dump_host_size_gdb = priv->fw.cap_dump_host_size_gdb;
    }
    printk(
        KERN_NOTICE "cr_dump init: cap_dump_host_size_flat:%u, cap_dump_host_size_gw:%u, cap_dump_host_size_gdb:%u.\n",
        __cap_dump_host_size_flat,
        __cap_dump_host_size_gw,
        __cap_dump_host_size_gdb
        );

    return 0;
}

void sx_core_cr_dump_deinit(struct sx_priv *priv)
{
    iounmap(priv->cr_dump_base);
}
