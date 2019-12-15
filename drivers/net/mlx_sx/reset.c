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

#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/device.h>
#include "sx.h"
#include "dq.h"
#include "alloc.h"

static int reset_trigger = 1;
module_param_named(reset_trigger, reset_trigger, int, 0644);
MODULE_PARM_DESC(reset_trigger, "a trigger to perform chip reset");

#define RESET_TRIGGER_TIMEOUT       (10 * HZ)
#define SX_RESET_TIMEOUT_JIFFIES    (2 * HZ)
#define SX_SYSTEM_STATUS_REG_OFFSET 0xA1844
#define SX_SYSTEM_STATUS_REG_SIZE   4         /* byte */
#define SX_SYSTEM_STATUS_REG_MASK   0xFF
#define SX_SYSTEM_STATUS_ENABLED    0x5E
#ifdef INCREASED_TIMEOUT
    #define SX_SW_RESET_TIMEOUT_MSECS (25 * 60 * 1000)           /* 15 minutes */
#else
    #define SX_SW_RESET_TIMEOUT_MSECS (5 * 1000)           /* 5 seconds */
#endif
#define SX_HCA_HEADERS_SIZE 256

static int legacy_sx_reset(struct sx_dev *dev);
static int reset_dev_by_mrsr_reg(struct sx_dev *dev);
static int sdk_sx_reset(struct sx_dev *dev);

/* wait for device to come up after reset, depending on device type.
 * SwitchX                                                      - 3 seconds timeout.
 * Spectrum, SwitchIB, SwitchIB2	- wait for FW ready control register.
 */
static int perform_dev_sw_reset(struct sx_dev *dev)
{
    int err = 0;

    if (!dev) {
        sx_err(dev, "%s: dev argument is null, err [%d]\n", __func__, err);
        return -EINVAL;
    }

    switch (dev->pdev->device) {
    /* SwitchX */
    case SWITCHX_PCI_DEV_ID:
        err = legacy_sx_reset(dev);
        if (err) {
            sx_err(dev, "legacy_sx_reset failed, err [%d]\n", err);
            goto out;
        }

        break;

    /* Spectrum, SwitchIB */
    case SPECTRUM_PCI_DEV_ID:     /* no break */
    case SPECTRUM2_PCI_DEV_ID:     /* no break */
    case SWITCH_IB_PCI_DEV_ID:     /* no break */
    case SWITCH_IB2_PCI_DEV_ID:
    case QUANTUM_PCI_DEV_ID:
        err = sdk_sx_reset(dev);
        if (err) {
            sx_err(dev, "%s: sdk_sx_reset failed, err [%d]\n", __func__, err);
            err = legacy_sx_reset(dev);
            goto out;
        }

        break;

    default:
        err = -ENODEV;
        sx_err(dev, "%s: unsupported device type [%d], err [%d]\n", __func__,
               dev->pdev->device, err);
        goto out;
        break;
    }

out:
    return err;
}

static int reset_dev_by_mrsr_reg(struct sx_dev *dev)
{
    int                       err = 0;
    struct ku_access_mrsr_reg reg_data;

    memset(&reg_data, 0, sizeof(reg_data));

    reg_data.dev_id = dev->device_id;
    reg_data.op_tlv.type = TLV_TYPE_OPERATION_E;
    reg_data.op_tlv.length = TLV_LEN;
    reg_data.op_tlv.dr = 0;
    reg_data.op_tlv.status = 0;
    reg_data.op_tlv.register_id = MRSR_REG_ID;
    reg_data.op_tlv.r = TLV_REQUEST;
    reg_data.op_tlv.method = EMAD_METHOD_WRITE;
    reg_data.op_tlv.op_class = EMAD_CLASS_REG_ACCESS;
    reg_data.op_tlv.tid = 0;

    reg_data.mrsr_reg.command = SXD_MRSR_CMD_SW_RESET;

    err = sx_ACCESS_REG_MRSR(dev, &reg_data);
    if (err) {
        printk(KERN_ERR "Failed accessing MRSR for SW reset command, err [%d]\n", err);
        goto out;
    }

out:
    return err;
}

static int sdk_sx_reset(struct sx_dev *dev)
{
    int           err = 0;
    unsigned long end = 0, start = 0;
    void __iomem *sys_status = NULL;
    bool          system_enabled = false;
    u32           val = 0;
    u32           wait_for_reset = 0;

    printk(KERN_INFO PFX "performing SW reset\n");

    /* actually hit reset */
    dev->dev_sw_rst_flow = 1;
    err = reset_dev_by_mrsr_reg(dev);
    if (err) {
        printk(KERN_ERR "Failed filling MRSR data, err [%d]\n", err);
        goto out;
    }

    sys_status = ioremap(pci_resource_start(dev->pdev, 0) + SX_SYSTEM_STATUS_REG_OFFSET, SX_SYSTEM_STATUS_REG_SIZE);
    if (!sys_status) {
        err = -ENOMEM;
        sx_err(dev, "%s: Couldn't map HCA reset register, err [%d]\n", __func__, err);
        goto out;
    }

    /* first, verify system status is not enabled, due to MRSR emad */
    system_enabled = true;
    val = ioread32be(sys_status);
    if (SX_SYSTEM_STATUS_ENABLED != (val & SX_SYSTEM_STATUS_REG_MASK)) {
        system_enabled = false;
    }

    if (system_enabled) {
        err = -ETIME;
        sx_err(dev, "%s: system is still enabled after sending MRSR SW reset emad, err [%d]\n", __func__, err);
        iounmap(sys_status);
        goto out;
    }

    /* Wait before accessing device */
#ifndef INCREASED_TIMEOUT
    msleep(2000);
#else
#define WAIT_FOR_PCI_RESET 1500000 /* timeout should be greater than the time needed by the model to complete PCI Reset */

    printk(KERN_INFO PFX "Waiting %u ms before accessing the device", WAIT_FOR_PCI_RESET);
    msleep(WAIT_FOR_PCI_RESET);
#endif

    if (dev->pdev->device == QUANTUM_PCI_DEV_ID) {
        wait_for_reset = 12000; /* Timeout for Quantum was increased to 12s until FW stabilizes its flow. */
    } else if (dev->pdev->device == SPECTRUM2_PCI_DEV_ID) {
        /* for now, until we do it in a proper way, always wait up to 15 minutes (!) for switch reset.
         * we have a special case with Tigris, in which there is an upgrade for the gearbox FWs and it might take up to 10 minutes.
         * here in the SDK, will give a grace of 5 more minutes for the switch to reset.
         */
        wait_for_reset = 15 * 60 * 1000; /* 15 minutes */
    } else {
        wait_for_reset = SX_SW_RESET_TIMEOUT_MSECS;
    }

    start = jiffies;
    end = jiffies + msecs_to_jiffies(wait_for_reset);
    do {
        val = ioread32be(sys_status);
        if (SX_SYSTEM_STATUS_ENABLED == (val & SX_SYSTEM_STATUS_REG_MASK)) {
            system_enabled = true;
            printk(KERN_INFO "reset: system_enabled change to [%s], time: %u[ms]\n",
                   system_enabled ? "true" : "false", jiffies_to_msecs(jiffies - start));
            break;
        }
        cond_resched();
    } while (time_before(jiffies, end));

    if (system_enabled == false) {
        err = -ETIME;
        sx_err(dev, "%s: system status timeout, err [%d]\n", __func__, err);
    }

    iounmap(sys_status);

out:
    dev->dev_sw_rst_flow = 0;
    return err;
}

/* This function saves PCI headers for restoration after SW reset,
 * using __restore_headers_data, according to device type.
 * SwitchX                                                      - Saves and restores PCI headers.
 * Spectrum, SwitchIB, SwitchIB2	- Doesn't save PCI headers.
 *
 *
 * @param dev[in]				- sx device.
 * @param hca_header_p[in/out]	- hca headers, must be size of SX_HCA_HEADERS_SIZE.
 */
static int __save_headers_data(struct sx_dev *dev, u32* hca_header_p)
{
    int err = 0;
    int i = 0;
    int pcie_cap = 0;

    if (!dev) {
        return -EINVAL;
        printk(KERN_ERR "%s: dev argument is null, err [%d]\n", __func__, err);
    }

    /* SwitchX */
    if (!hca_header_p) {
        return -EINVAL;
        printk(KERN_ERR "%s: hca_header_p argument is null, err [%d]\n", __func__, err);
    }
    memset(hca_header_p, 0, SX_HCA_HEADERS_SIZE);

    pcie_cap = pci_find_capability(dev->pdev, PCI_CAP_ID_EXP);

    /* We skip config space offsets 22
     * and 23 since those have a special meaning.
     */
    for (i = 0; i < 64; ++i) {
        if ((i == 22) || (i == 23)) {
            continue;
        }
        if (pci_read_config_dword(dev->pdev, i * 4, hca_header_p + i)) {
            err = -ENODEV;
            sx_err(dev, "%s: Couldn't save HCA PCI header, aborting, err[%d]\n", __func__, err);
            goto out;
        }
    }

out:
    return err;
}


/* This function restores PCI headers after SW reset, according to
 * headers as saved by __save_headers_data, according to device type.
 * SwitchX                                                      - Restores and restores PCI headers.
 * Spectrum, SwitchIB, SwitchIB2	- Doesn't restore PCI headers.
 *
 *
 * @param dev[in]				- sx device.
 * @param hca_header_p[in]	    - hca headers, must be size of SX_HCA_HEADERS_SIZE.
 */
static int __restore_headers_data(struct sx_dev *dev, u32* hca_header_p)
{
    int err = 0;
    int pcie_cap;
    int i = 0;
    u16 devctl = 0;
    u16 linkctl = 0;

    if (!dev) {
        return -EINVAL;
        printk(KERN_ERR "%s: dev argument is null, err [%d]\n", __func__, err);
    }

    /* SwitchX */
    if (!hca_header_p) {
        return -EINVAL;
        printk(KERN_ERR "%s: hca_header_p argument is null, err [%d]\n", __func__, err);
    }

    /* restore PCIE headers to restore after reset from hca_header_p */
    /* Now restore the PCI headers */
    pcie_cap = pci_find_capability(dev->pdev, PCI_CAP_ID_EXP);
    if (pcie_cap) {
        devctl = hca_header_p[(pcie_cap + PCI_EXP_DEVCTL) / 4];
        if (pci_write_config_word(dev->pdev, pcie_cap + PCI_EXP_DEVCTL, devctl)) {
            err = -ENODEV;
            sx_err(dev, "%s: Couldn't restore HCA PCI Express "
                   "Device Control register, aborting, err[%d]\n", __func__, err);
            goto out;
        }

        linkctl = hca_header_p[(pcie_cap + PCI_EXP_LNKCTL) / 4];
        if (pci_write_config_word(dev->pdev, pcie_cap + PCI_EXP_LNKCTL,
                                  linkctl)) {
            err = -ENODEV;
            sx_err(dev, "%s: Couldn't restore HCA PCI Express "
                   "Link control register, aborting, err[%d]\n", __func__, err);
            goto out;
        }
    }

    for (i = 0; i < 16; ++i) {
        if (i * 4 == PCI_COMMAND) {
            continue;
        }

        if (pci_write_config_dword(dev->pdev, i * 4, hca_header_p[i])) {
            err = -ENODEV;
            sx_err(dev, "%s: Couldn't restore HCA reg %x, aborting, err[%d]\n", __func__, i, err);
            goto out;
        }
    }

    if (pci_write_config_dword(dev->pdev, PCI_COMMAND,
                               hca_header_p[PCI_COMMAND / 4])) {
        err = -ENODEV;
        sx_err(dev, "%s: Couldn't restore HCA COMMAND, aborting, err[%d]\n", __func__, err);
        goto out;
    }

out:
    return err;
}


/* This function is used to read system status from FW
 *
 * @param dev[in]				- sx device.
 * @param system_status[out]	- system status.
 */

int get_system_status(struct sx_dev *dev, u16 *system_status)
{
    int           err = 0;
    u32           val = 0;
    void __iomem *sys_status_addr = NULL;

    if (!dev) {
        err = -EINVAL;
        printk(KERN_ERR "%s: Given null device parameter, err [%d]\n", __func__, err);
        goto out;
    }
    if (!system_status) {
        err = -EINVAL;
        sx_err(dev, "%s: Given null system status device parameter, err [%d]\n", __func__, err);
        goto out;
    }

    sys_status_addr =
        ioremap(pci_resource_start(dev->pdev, 0) + SX_SYSTEM_STATUS_REG_OFFSET, SX_SYSTEM_STATUS_REG_SIZE);
    if (!sys_status_addr) {
        err = -ENOMEM;
        sx_err(dev, "%s: Couldn't map HCA reset register, err [%d]\n", __func__, err);
        goto out;
    }

    val = ioread32be(sys_status_addr);
    *system_status = val & SX_SYSTEM_STATUS_REG_MASK;

    iounmap(sys_status_addr);

out:
    return err;
}

/* taken as is from the IS4 driver, we might need to remove the part where we
 * save the pci config headers before the reset, and restore them afterwards.
 * Depends on the decision of the FW guys. */
int legacy_sx_reset(struct sx_dev *dev)
{
    void __iomem *reset;
    u16           vendor = 0xffff;
    unsigned long end;
    int           err = 0;

    printk(KERN_INFO PFX "performing legacy SW reset\n");

    if (!dev->pdev) {
        sx_err(dev, "SW reset will not be executed since PCI device is not present");
    }

#define SX_RESET_BASE   0xf0000
#define SX_RESET_SIZE   0x404
#define SX_SEM_OFFSET   0x400
#define SX_SEM_BIT      (1 << 31)
#define SX_RESET_OFFSET 0x10
#define SX_RESET_VALUE  swab32(1)

#ifndef INCREASED_TIMEOUT
#define SX_SEM_TIMEOUT_JIFFIES (10 * HZ)
#else
#define SX_SEM_TIMEOUT_JIFFIES (100 * HZ)
#endif
#define SX_RESET_TIMEOUT_JIFFIES (2 * HZ)

    /*
     * Reset the chip.  This is somewhat ugly because we have to
     * save off the PCI header before reset and then restore it
     * after the chip reboots.  We skip config space offsets 22
     * and 23 since those have a special meaning.
     */
    reset = ioremap(pci_resource_start(dev->pdev, 0) + SX_RESET_BASE,
                    SX_RESET_SIZE);
    if (!reset) {
        err = -ENOMEM;
        sx_err(dev, "Couldn't map HCA reset register, aborting.\n");
        goto out;
    }

    /* actually hit reset */
    writel(SX_RESET_VALUE, reset + SX_RESET_OFFSET);
    iounmap(reset);

    /* Wait three seconds before accessing device */
#ifndef INCREASED_TIMEOUT
    msleep(3000);
#else
    msleep(180000);
#endif

    end = jiffies + SX_RESET_TIMEOUT_JIFFIES;
    do {
        if (!pci_read_config_word(dev->pdev, PCI_VENDOR_ID, &vendor) &&
            (vendor != 0xffff)) {
            break;
        }

        msleep(1);
    } while (time_before(jiffies, end));

    if (vendor == 0xffff) {
        err = -ENODEV;
        sx_err(dev, "PCI device did not come back after reset, aborting.\n");
        goto out;
    }

out:
    return err;
}

int sx_reset(struct sx_dev *dev, u8 perform_chip_reset)
{
    u32          *hca_header = NULL;
    u16           vendor = 0xffff;
    unsigned long end;
    int           err = 0;

    if ((dev == NULL) || !dev->pdev) {
        sx_err(dev, "SW reset will not be executed since PCI device is not present");
        err = -ENODEV;
        goto out;
    }

    if (SWITCHX_PCI_DEV_ID == dev->pdev->device) {
        hca_header = kmalloc(SX_HCA_HEADERS_SIZE, GFP_KERNEL);
        if (!hca_header) {
            err = -ENOMEM;
            sx_err(dev, "%s: Couldn't allocate memory to save HCA "
                   "PCI header, aborting, err[%d]\n", __func__, err);
            goto out;
        }

        err = __save_headers_data(dev, hca_header);
        if (err) {
            sx_err(dev, "PCI device reset failed saving PCI headers data, err [%d].\n", err);
            goto out;
        }
    }

    /* return device to use polling */
    sx_cmd_use_polling(dev);

    if (reset_trigger) {
        sx_info(dev, "reset trigger is already set\n");
    } else {
        sx_info(dev, "waiting for reset trigger\n");

        end = jiffies + RESET_TRIGGER_TIMEOUT;

        while (!reset_trigger && time_before(jiffies, end)) {
            msleep(100);
        }

        if (reset_trigger) {
            sx_info(dev, "reset trigger is set\n");
        } else {
            sx_err(dev, "reset trigger timeout. self triggering.\n");
            reset_trigger = 1;
        }
    }

    if (perform_chip_reset) {
        printk(KERN_DEBUG "Performing chip reset in this phase\n");
        err = perform_dev_sw_reset(dev);
        if (err) {
            sx_err(dev, "PCI device reset failed waiting for device, err [%d].\n", err);
            goto out;
        }

        end = jiffies + SX_RESET_TIMEOUT_JIFFIES;
        do {
            if (!pci_read_config_word(dev->pdev, PCI_VENDOR_ID, &vendor) &&
                (vendor != 0xffff)) {
                break;
            }

            msleep(1);
        } while (time_before(jiffies, end));

        if (vendor == 0xffff) {
            err = -ENODEV;
            sx_err(dev, "PCI device did not come back after reset, aborting.\n");
            goto out;
        }
    } else {
        printk(KERN_DEBUG "Did not perform chip reset in this phase\n");
    }

    if (SWITCHX_PCI_DEV_ID == dev->pdev->device) {
        /* Now restore the PCI headers */
        err = __restore_headers_data(dev, hca_header);
        if (err) {
            sx_err(dev, "PCI device reset failed restoring PCI headers data, err [%d].\n", err);
            goto out;
        }
    }

out:
    if (hca_header) {
        kfree(hca_header);
    }
    return err;
}
