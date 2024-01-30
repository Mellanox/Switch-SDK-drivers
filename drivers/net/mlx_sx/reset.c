/*
 * Copyright (C) 2010-2023 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

static int debug_fw_trace_boot_flow = 0;
module_param_named(debug_fw_trace_boot_flow, debug_fw_trace_boot_flow, int, 0644);
MODULE_PARM_DESC(debug_fw_trace_boot_flow, "only for debug environment - enable when debugging FW boot flow");

static int force_reset_type = 0;
module_param_named(force_reset_type, force_reset_type, int, 0644);
MODULE_PARM_DESC(force_reset_type, "force reset type: 1 - SW_RSR, 2 - PCI_DIS_RST");

extern int skip_reset;

#define RESET_TRIGGER_TIMEOUT            (10 * HZ)
#define SX_RESET_TIMEOUT_JIFFIES         (2 * HZ)
#define SX_SYSTEM_STATUS_REG_OFFSET      0xA1844
#define SX_SYSTEM_STATUS_REG_OFFSET_QTM3 0x152080
#define SX_SYSTEM_STATUS_REG_SIZE        4    /* byte */
#define SX_SYSTEM_STATUS_REG_MASK        0xFF
#define SX_SYSTEM_STATUS_ENABLED         0x5E
#ifdef INCREASED_TIMEOUT
    #define SX_SW_RESET_TIMEOUT_MSECS (25 * 60 * 1000)           /* 15 minutes */
#else
    #define SX_SW_RESET_TIMEOUT_MSECS (5 * 1000)           /* 5 seconds */
#endif
#if defined(INCREASED_TIMEOUT)
#define SX_PCI_TOGGLE_TIMEOUT_MS       (20 * 60 * 1000)   /* 20 minutes */
#define SX_PCI_LINK_DOWN_TIME          (1 * 60 * 1000)    /* 1 minute */
#define SX_PCI_WAIT_AFTER_LINK_UP_TIME (7 * 60 * 1000)    /* 7 minutes */
#define SX_WAIT_WHEN_NO_LNKCAP_DLLLARC (5 * 60 * 1000)    /* 5 minutes */
#else
#define SX_PCI_TOGGLE_TIMEOUT_MS       (2 * 1000)         /* 2 seconds */
#define SX_PCI_LINK_DOWN_TIME          (500)              /* 500 msec */
#define SX_PCI_WAIT_AFTER_LINK_UP_TIME (500)              /* 500 msec */
#define SX_WAIT_WHEN_NO_LNKCAP_DLLLARC (1000)
#endif
#define SX_HCA_HEADERS_SIZE 256

static int __legacy_reset_SwitchX(struct sx_dev *dev);
static int __legacy_reset(struct sx_dev *dev, u16 asic_id);
static int __reset_dev_by_mrsr_reg(struct sx_dev *dev, enum sxd_mrsr_command reset_command);
static int __sdk_sx_reset(struct sx_dev *dev, u16 asic_id);

/* wait for device to come up after reset, depending on device type.
 * SwitchX                                                      - 3 seconds timeout.
 * Spectrum, SwitchIB, SwitchIB2	- wait for FW ready control register.
 */
static int __perform_dev_sw_reset(struct sx_dev *dev, u16 asic_id)
{
    int err = 0;

    switch (asic_id) {
    /* SwitchX */
    case SWITCHX_PCI_DEV_ID:
        err = __legacy_reset_SwitchX(dev);
        if (err) {
            sx_err(dev, "legacy reset for SwitchX failed, err [%d]\n", err);
            goto out;
        }

        break;

    /* Spectrum, SwitchIB */
    case SPECTRUM_PCI_DEV_ID:     /* no break */
    case SPECTRUM2_PCI_DEV_ID:     /* no break */
    case SPECTRUM3_PCI_DEV_ID: /* no break */
    case SPECTRUM4_PCI_DEV_ID: /* no break */
    case SWITCH_IB_PCI_DEV_ID:     /* no break */
    case SWITCH_IB2_PCI_DEV_ID:
    case QUANTUM_PCI_DEV_ID:
    case QUANTUM2_PCI_DEV_ID:
    case QUANTUM3_PCI_DEV_ID:
        err = __sdk_sx_reset(dev, asic_id);
        if (err == -EOPNOTSUPP) {
            sx_warn(dev, "normal reset is not supported, fallback to legacy reset\n");

            /* PCI-Toggle is not supported (SimX), don't print an error. fallback to legacy reset */
            err = __legacy_reset(dev, asic_id);
            if (err) {
                sx_err(dev, "chip legacy reset failed, err [%d]\n", err);
                goto out;
            }
        } else if (err) {
            sx_err(dev, "chip reset failed, err [%d]\n", err);
        }

        break;

    default:
        err = -ENODEV;
        sx_err(dev, "%s: unsupported device type [%d], err [%d]\n", __func__,
               asic_id, err);
        goto out;
        break;
    }

out:
    return err;
}

static int __reset_dev_by_mrsr_reg(struct sx_dev *dev, enum sxd_mrsr_command reset_command)
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

    reg_data.mrsr_reg.command = reset_command;

    err = sx_ACCESS_REG_MRSR(dev, &reg_data);
    if (err) {
        printk(KERN_ERR "Failed accessing MRSR for SW reset command, err [%d]\n", err);
        goto out;
    }

out:
    return err;
}

static int __wait_for_system_ready(struct sx_dev *dev, u16 asic_id, u32 wait_for_reset_msec, u32 *time_waited_msec)
{
    unsigned long start;
    unsigned long end;
    int           ret = 0;
    u16           val = 0xffff, prev_val = 0xffff;
    bool          system_ready = false;

    start = jiffies;
    end = jiffies + msecs_to_jiffies(wait_for_reset_msec);

    printk(KERN_INFO "device=%u, wait up to %lu seconds (HZ=%u)\n",
           asic_id,
           (end - start) / HZ,
           HZ);

    do {
        ret = get_system_status(dev, &val);
        if (ret) {
            break;
        }

        if (prev_val == 0xffff) { /* only in 1st iteration */
            prev_val = val;
        }

        if (val != prev_val) {
            printk(KERN_NOTICE "Device %u status changed to 0x%x\n", dev->device_id, val);
            prev_val = val;
        }

        if (val == SX_SYSTEM_STATUS_ENABLED) {
            if (time_waited_msec != NULL) {
                *time_waited_msec = jiffies_to_msecs(jiffies - start);
            }

            system_ready = true;
            break;
        }

        msleep(100);
    } while (time_before(jiffies, end));

    if (!system_ready) {
        printk(KERN_NOTICE "Device %u is not ready, current status is 0x%x\n",
               dev->device_id,
               val);
        return -ETIME;
    }

    return 0;
}


static u32 __get_chip_reset_duration(struct sx_dev *dev, u16 asic_id)
{
    u32 duration;

    switch (asic_id) {
    case QUANTUM_PCI_DEV_ID:
    case QUANTUM2_PCI_DEV_ID:
    case QUANTUM3_PCI_DEV_ID:
        duration = 15 * 1000; /* 15 seconds */
        break;

    case SPECTRUM2_PCI_DEV_ID:
    case SPECTRUM3_PCI_DEV_ID:
    case SPECTRUM4_PCI_DEV_ID:
        duration = 5 * 60 * 1000; /* 5 minutes */
        break;

    default:
        duration = SX_SW_RESET_TIMEOUT_MSECS;
        break;
    }

#if defined(PD_BU) && defined(QUANTUM3_BU)
    duration = 20 * 60 * 1000; /* wait 20 minutes for reset on palladium */
#endif

    return duration;
}

static unsigned int __get_chip_system_status_offset(u16 asic_id)
{
    unsigned int offset = SX_SYSTEM_STATUS_REG_OFFSET;

    if (QUANTUM3_PCI_DEV_ID == asic_id) {
        offset = SX_SYSTEM_STATUS_REG_OFFSET_QTM3;
    }

    return offset;
}

void sdk_chip_reset_type_sw_reset(enum chip_reset_type *chip_reset_type_p)
{
    if (chip_reset_type_p == NULL) {
        printk(KERN_ERR "chip reset type get : chip_reset_type_p is NULL.\n");
        return;
    }

    *chip_reset_type_p = CHIP_RESET_TYPE_SW_RESET;

    return;
}

void sdk_chip_reset_type_reset_by_pci_disable(enum chip_reset_type *chip_reset_type_p)
{
    if (chip_reset_type_p == NULL) {
        printk(KERN_ERR "chip reset type get : chip_reset_type_p is NULL.\n");
        return;
    }

    *chip_reset_type_p = CHIP_RESET_TYPE_RESET_BY_PCI_DISABLE;

    /* if used force reset type then use it */
    if ((force_reset_type == CHIP_RESET_TYPE_SW_RESET) ||
        (force_reset_type == CHIP_RESET_TYPE_RESET_BY_PCI_DISABLE)) {
        printk(KERN_INFO "chip reset type forced to type : %s \n",
               force_reset_type == CHIP_RESET_TYPE_SW_RESET ? "SW_RST (1)" : "RST_BY_PCI_DIS (2)");
        *chip_reset_type_p = force_reset_type;
    }

    return;
}


static int __sdk_chip_sw_reset(struct sx_dev *dev, u16 asic_id)
{
    struct sx_priv *priv = sx_priv(dev);
    u32             wait_for_reset, time_waited;
    int             err = 0;

    wait_for_reset = __get_chip_reset_duration(dev, asic_id);

    printk(KERN_INFO "wait for system to be ready before reset\n");

    err = __wait_for_system_ready(dev, asic_id, wait_for_reset, &time_waited);
    if (err) {
        printk(KERN_ERR "system is not ready and cannot be reset (err=%d)!\n", err);
        goto out;
    }

    printk(KERN_INFO "system is ready for reset [waited %u msec], performing reset now\n", time_waited);

    /* actually hit reset */
    priv->dev_sw_rst_flow = true;
    err = __reset_dev_by_mrsr_reg(dev, SXD_MRSR_CMD_SW_RESET);
    if (err) {
        printk(KERN_ERR "Failed filling MRSR data, err [%d]\n", err);
        goto out;
    }

    /* verify that system status is not enabled due to MRSR */
    err = __wait_for_system_ready(dev, asic_id, 0, &time_waited);
    if (err != -ETIME) {
        /* we've got a problem. system is enabled immediately after reset.
         * it means that the reset did not actually work. */

        printk(KERN_ERR "system is ready immediately after a reset command has been sent (err=%d)\n", err);
        err = -EFAULT;
        goto out;
    }

    /* now wait for reset to be completed */
    err = __wait_for_system_ready(dev, asic_id, wait_for_reset, &time_waited);
    if (err) {
        printk(KERN_ERR "system status timeout after reset! (err=%d)\n", err);
        goto out;
    }

    printk(KERN_INFO "system is ready after reset [waited %u msec]\n", time_waited);
    priv->reset_info.duration_msec = time_waited;

out:
    priv->dev_sw_rst_flow = false;
    return err;
}


static int __pci_link_toggle(struct sx_dev * dev)
{
    struct pci_bus *bridge_bus = dev->pdev->bus;
    struct pci_dev *bridge = bridge_bus->self;
    u16             reg16, dev_id, sdev_id;
    unsigned long   timeout, start_time;
    struct pci_dev *sdev;
    int             cap, err;
    u32             reg32;

    /* Check that all functions under the pci bridge are PFs of
     * this device otherwise fail this function.
     */
    err = pci_read_config_word(dev->pdev, PCI_DEVICE_ID, &dev_id);
    if (err) {
        printk(KERN_ERR "pci_read_config_word failed , err: %d\n", err);
        return err;
    }

    list_for_each_entry(sdev, &bridge_bus->devices, bus_list) {
        err = pci_read_config_word(sdev, PCI_DEVICE_ID, &sdev_id);
        if (err) {
            printk(KERN_ERR "pci_read_config_word failed , err: %d\n", err);
            return err;
        }
        if (sdev_id != dev_id) {
            printk(KERN_ERR "sdev_id %d (0x%x) != dev_id %d (0x%x) \n", sdev_id, sdev_id, dev_id, dev_id);
            return -EPERM;
        }
    }

    printk(KERN_INFO "Toggle PCI link for dev id : %d (%x) \n", dev_id, dev_id);

    cap = pci_find_capability(bridge, PCI_CAP_ID_EXP);
    if (!cap) {
        printk(KERN_WARNING "pci_find_capability failed , cap: %d\n", cap);
        return -EOPNOTSUPP;
    }

    list_for_each_entry(sdev, &bridge_bus->devices, bus_list) {
        pci_save_state(sdev);
        pci_cfg_access_lock(sdev);
    }

    /* PCI link toggle */
    printk(KERN_INFO "Set bridge link DOWN\n");
    err = pci_read_config_word(bridge, cap + PCI_EXP_LNKCTL, &reg16);
    if (err) {
        printk(KERN_ERR "bridge pci_read_config_word cap + PCI_EXP_LNKCTL failed , err: %d\n", err);
        goto restore;
    }
    reg16 |= PCI_EXP_LNKCTL_LD;
    err = pci_write_config_word(bridge, cap + PCI_EXP_LNKCTL, reg16);
    if (err) {
        printk(KERN_ERR "bridge pci_write_config_word cap + PCI_EXP_LNKCTL failed , err: %d\n", err);
        goto restore;
    }

    msleep(SX_PCI_LINK_DOWN_TIME);

    printk(KERN_INFO "Set bridge link UP\n");
    reg16 &= ~PCI_EXP_LNKCTL_LD;
    err = pci_write_config_word(bridge, cap + PCI_EXP_LNKCTL, reg16);
    if (err) {
        goto restore;
    }

    printk(KERN_INFO "Waiting for bridge link to be UP\n");
    msleep(SX_PCI_WAIT_AFTER_LINK_UP_TIME);

    /* Check link */
    err = pci_read_config_dword(bridge, cap + PCI_EXP_LNKCAP, &reg32);
    if (err) {
        goto restore;
    }
    if (!(reg32 & PCI_EXP_LNKCAP_DLLLARC)) {
        printk(KERN_INFO "No PCI link reporting capability (0x%08x)\n", reg32);
        msleep(SX_WAIT_WHEN_NO_LNKCAP_DLLLARC);
        goto restore;
    }

    start_time = jiffies;
    timeout = jiffies + msecs_to_jiffies(SX_PCI_TOGGLE_TIMEOUT_MS);
    do {
        err = pci_read_config_word(bridge, cap + PCI_EXP_LNKSTA, &reg16);
        if (err) {
            goto restore;
        }
        if (reg16 & PCI_EXP_LNKSTA_DLLLA) {
            break;
        }
        msleep(20);
    } while (!time_after(jiffies, timeout));

    if (reg16 & PCI_EXP_LNKSTA_DLLLA) {
        printk(KERN_INFO "PCI Link up  (0x%04x) after %lu jiffies\n", reg16, start_time - jiffies);
    } else {
        printk(KERN_ERR "PCI link not ready (0x%04x) after %u ms\n",
               reg16, SX_PCI_TOGGLE_TIMEOUT_MS);
        err = -ETIMEDOUT;
    }

restore:
    list_for_each_entry(sdev, &bridge_bus->devices, bus_list) {
        pci_cfg_access_unlock(sdev);
        pci_restore_state(sdev);
    }

    return err;
}


static int __sdk_chip_sw_reset_by_pci_toggling(struct sx_dev *dev, u16 asic_id)
{
    struct sx_priv *priv = sx_priv(dev);
    u32             wait_for_reset, time_waited;
    int             err = 0;

    wait_for_reset = __get_chip_reset_duration(dev, asic_id);

    printk(KERN_INFO "wait for system to be ready before PCI reset\n");

    err = __wait_for_system_ready(dev, asic_id, wait_for_reset, &time_waited);
    if (err) {
        printk(KERN_ERR "system is not ready and cannot be reset (err=%d)!\n", err);
        goto out;
    }

    printk(KERN_INFO "system is ready for PCI reset [waited %u msec], performing reset now\n",
           time_waited);

    /* Enable reset by PCI disable */
    priv->dev_sw_rst_flow = true;
    err = __reset_dev_by_mrsr_reg(dev, SXD_MRSR_CMD_RESET_AT_PCI_DISABLE);
    if (err) {
        printk(KERN_ERR "Failed filling MRSR data, err [%d]\n", err);
        goto out;
    }

    printk(KERN_INFO "Performing PCI link toggle.\n");

    /* actually hit reset */
    err = __pci_link_toggle(dev);
    if (err == -EOPNOTSUPP) {
        printk(KERN_WARNING "system doesn't support Bridge PCI link toggling\n");
        goto out;
    } else if (err) {
        printk(KERN_ERR "__pci_link_toggle failed, no reset done, err %d\n", err);
        err = -EINVAL;
        goto out;
    }

    printk(KERN_INFO "wait for system to be ready after PCI link toggle.\n");

    /* now wait for reset to be completed */
    err = __wait_for_system_ready(dev, asic_id, wait_for_reset, &time_waited);
    if (err) {
        printk(KERN_ERR "system status timeout after reset! (err=%d)\n", err);
        goto out;
    }

    printk(KERN_INFO "system is ready after reset [waited %u msec]\n", time_waited);
    priv->reset_info.duration_msec = time_waited;

out:
    priv->dev_sw_rst_flow = false;
    return err;
}

static int __get_chip_reset_type(struct sx_dev *dev, enum chip_reset_type *chip_reset_type_p)
{
    int rc = 0;

    *chip_reset_type_p = 0;

    if (!dev) {
        printk(KERN_ERR PFX "sx_core_get_chip_reset_type: dev is NULL\n");
        return -EINVAL;
    }

    rc = __sx_core_dev_specific_cb_get_reference(dev);
    if (rc) {
        printk(KERN_ERR PFX "__sx_core_dev_specific_cb_get_reference failed.\n");
        return rc;
    }

    if (sx_priv(dev)->dev_specific_cb.get_chip_reset_type_cb != NULL) {
        sx_priv(dev)->dev_specific_cb.get_chip_reset_type_cb(chip_reset_type_p);
    } else {
        printk(KERN_ERR PFX "Error retrieving chip_reset_type callback\n");
        __sx_core_dev_specific_cb_release_reference(dev);
        return -EINVAL;
    }

    __sx_core_dev_specific_cb_release_reference(dev);

    return 0;
}


static int __sdk_sx_reset(struct sx_dev *dev, u16 asic_id)
{
    int                  err = 0;
    struct sx_priv      *priv = sx_priv(dev);
    enum chip_reset_type chip_reset_type = CHIP_RESET_TYPE_INVALID;

    err = __get_chip_reset_type(dev, &chip_reset_type);
    if (err) {
        printk(KERN_ERR "failed to get default reset command for dev %p! (err=%d)\n",
               dev, err);
        goto out;
    }

    switch (chip_reset_type) {
    case CHIP_RESET_TYPE_SW_RESET:
        err = __sdk_chip_sw_reset(dev, asic_id);
        break;

    case CHIP_RESET_TYPE_RESET_BY_PCI_DISABLE:
        err = __sdk_chip_sw_reset_by_pci_toggling(dev, asic_id);
        break;

    default:
        err = -EINVAL;
        printk(KERN_ERR "unsupported reset command %d (err=%d)\n",
               chip_reset_type, err);
        goto out;
    }

    if (!err) {
        priv->reset_info.last_chip_reset_type = chip_reset_type;
    } else {
        priv->reset_info.last_chip_reset_type = CHIP_RESET_TYPE_INVALID;
    }

out:
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
    unsigned int  system_status_reg_offset = __get_chip_system_status_offset(dev->pdev->device);

    if (!dev) {
        printk(KERN_ERR "Get-System-Status: device is NULL\n");
        err = -EINVAL;
        goto out;
    }

    if (!system_status) {
        sx_err(dev, "Get-System-Status: system status is NULL\n");
        err = -EINVAL;
        goto out;
    }

    if (unlikely(sx_cr_mode())) {
        err = sx_dpt_cr_space_read(dev->device_id, system_status_reg_offset, (unsigned char*)&val, sizeof(val));
        if (err) {
            printk(KERN_ERR "Get-System-Status: failed to read system status via I2C, err=%d\n", err);
            goto out;
        }

        val = be32_to_cpu(val);
    } else {
        sys_status_addr = ioremap(pci_resource_start(dev->pdev, 0) + system_status_reg_offset,
                                  SX_SYSTEM_STATUS_REG_SIZE);
        if (!sys_status_addr) {
            err = -ENOMEM;
            sx_err(dev, "Get-System-Status: couldn't map system status register\n");
            goto out;
        }

        val = ioread32be(sys_status_addr);
        iounmap(sys_status_addr);
    }

    *system_status = val & SX_SYSTEM_STATUS_REG_MASK;

out:
    return err;
}


static int __do_legacy_reset(struct sx_dev *dev)
{
    void __iomem *reset;
    int           err = 0;

#define SX_RESET_BASE  0xf0010
#define SX_RESET_SIZE  (4)
#define SX_RESET_VALUE swab32(1)

    /*
     * Reset the chip.  This is somewhat ugly because we have to
     * save off the PCI header before reset and then restore it
     * after the chip reboots.  We skip config space offsets 22
     * and 23 since those have a special meaning.
     */
    reset = ioremap(pci_resource_start(dev->pdev, 0) + SX_RESET_BASE, SX_RESET_SIZE);
    if (!reset) {
        err = -ENOMEM;
        sx_err(dev, "Couldn't map reset register, aborting.\n");
        goto out;
    }

    /* actually hit reset */
    writel(SX_RESET_VALUE, reset);
    iounmap(reset);

    /* Wait three seconds before accessing device */
#ifndef INCREASED_TIMEOUT
    msleep(3000);
#else
    msleep(180000);
#endif

out:
    return err;
}


static int __legacy_reset_SwitchX(struct sx_dev *dev)
{
    u16           vendor = 0xffff;
    unsigned long end;
    int           err = 0;

    printk(KERN_INFO PFX "performing SwitchX legacy reset\n");

    if (!dev->pdev) {
        sx_err(dev, "SW reset will not be executed since PCI device is not present");
        err = -ENODEV;
        goto out;
    }

    err = __do_legacy_reset(dev);
    if (err) {
        sx_err(dev, "failed SwitchX legacy reset [err=%d]\n", err);
        goto out;
    }

    /* SwitchX does not support System_Status register, so we will poll the vendor-id */
    end = jiffies + SX_RESET_TIMEOUT_JIFFIES;
    do {
        if (!pci_read_config_word(dev->pdev, PCI_VENDOR_ID, &vendor) && (vendor != 0xffff)) {
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

static int __legacy_reset(struct sx_dev *dev, u16 asic_id)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    u32             wait_for_reset, time_waited;

    printk(KERN_INFO PFX "performing legacy SW reset\n");

    if (!dev->pdev) {
        sx_err(dev, "SW reset will not be executed since PCI device is not present");
        err = -ENODEV;
        goto out;
    }

    wait_for_reset = __get_chip_reset_duration(dev, asic_id);

    /* we fall-back from MRSR to legacy reset. it is not a common flow.
     * in legacy reset we will wait double the time that we did on MRSR! */
    wait_for_reset *= 2;

    printk(KERN_INFO "wait for system to be ready before legacy reset\n");

    err = __wait_for_system_ready(dev, asic_id, wait_for_reset, &time_waited);
    if (err) {
        printk(KERN_ERR "system is not ready and cannot be reset (err=%d)!\n", err);
        goto out;
    }

    printk(KERN_INFO "system is ready for reset [waited %u msec], performing legacy reset now\n", time_waited);

    priv->dev_sw_rst_flow = true;

    err = __do_legacy_reset(dev);
    if (err) {
        sx_err(dev, "failed chip legacy reset [err=%d]\n", err);
        goto out;
    }

    /* now wait for reset to be completed */
    err = __wait_for_system_ready(dev, asic_id, wait_for_reset, &time_waited);
    if (err) {
        printk(KERN_ERR "system status timeout after legacy reset! (err=%d)\n", err);
        goto out;
    }

    printk(KERN_INFO "system is ready after legacy reset [waited %u msec]\n", time_waited);

out:
    priv->dev_sw_rst_flow = false;
    return err;
}

int sx_reset(struct sx_dev *dev, u16 asic_id, u8 perform_chip_reset)
{
    u32                 *hca_header = NULL;
    u16                  vendor = 0xffff;
    unsigned long        end;
    int                  err = 0;
    bool                 is_pre_reset_event = false;
    union sx_event_data *event_data = NULL;

    if (skip_reset) {
        printk(KERN_WARNING "Skipping ASIC reset on demand!\n");
        return 0;
    }

    if ((dev == NULL) || (!sx_cr_mode() && !dev->pdev)) {
        printk(KERN_ERR "SW reset will not be executed since PCI device is not present\n");
        err = -ENODEV;
        goto out;
    }

    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        printk(KERN_ERR PFX "Failed to allocate memory for event data.\n");
        err = -ENOMEM;
        goto out;
    }

    if (!sx_cr_mode() && (SWITCHX_PCI_DEV_ID == asic_id)) {
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
        sx_info(dev, "Performing chip reset in this phase\n");

        err = sx_core_dispatch_event(dev, SX_DEV_EVENT_PRE_RESET, NULL);
        is_pre_reset_event = true;
        if (err) {
            sx_err(dev, "PRE_RESET event failed, err [%d].\n", err);
            goto out;
        }

        err = __perform_dev_sw_reset(dev, asic_id);
        if (err) {
            sx_err(dev, "PCI device reset failed waiting for device, err [%d].\n", err);
            goto out;
        }

        if (!sx_cr_mode()) {
            end = jiffies + SX_RESET_TIMEOUT_JIFFIES;
            do {
                if (!pci_read_config_word(dev->pdev, PCI_VENDOR_ID, &vendor) && (vendor != 0xffff)) {
                    break;
                }

                msleep(1);
            } while (time_before(jiffies, end));

            if (vendor == 0xffff) {
                err = -ENODEV;
                sx_err(dev, "PCI device did not come back after reset, aborting.\n");
                goto out;
            }
        }
    } else {
        sx_info(dev, "Did not perform chip reset in this phase. Check system is ready.\n");

        if (!debug_fw_trace_boot_flow) {
            /* check that system is in ready state */
            err = __wait_for_system_ready(dev, asic_id, 0, NULL);
            if (err) {
                err = -ENODEV;
                printk(KERN_ERR "system is not ready.\n");
                goto out;
            }
        }
    }

    if (SWITCHX_PCI_DEV_ID == asic_id) {
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

    if (event_data) {
        if (is_pre_reset_event) {
            event_data->post_reset.err = err;
            err = sx_core_dispatch_event(dev, SX_DEV_EVENT_POST_RESET, event_data);
            if (err) {
                sx_err(dev, "POST_RESET event failed, err [%d].\n", err);
            }
            err = event_data->post_reset.err;
        }

        kfree(event_data);
    }

    return err;
}
