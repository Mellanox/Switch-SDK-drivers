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

#include <linux/module.h>
#include <linux/pci.h>
#include <linux/dma-mapping.h>
#include <linux/delay.h>
#include <linux/vmalloc.h>

#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/cmd.h>

#include "sx.h"
#include "alloc.h"
#include "sx_af_counters.h"
#include "cq.h"
#include "dq.h"
#include "sx_clock.h"
#include "ptp.h"
#include "ber_monitor.h"
#include "dev_db.h"
#include "dev_init.h"
#include "dev_callbacks.h"
#include "health_check.h"
#include "emad.h"
#include "sgmii.h"

/****************************************************************************************
 * MODULE PARAMETERS
 ***************************************************************************************/

#ifdef CONFIG_PCI_MSI
static int msi_x = 1;
module_param(msi_x, int, 0444);
MODULE_PARM_DESC(msi_x, "attempt to use MSI-X if nonzero");
#else /* CONFIG_PCI_MSI */
static int msi_x = 0;
#endif /* CONFIG_PCI_MSI */

int chip_info_type = -1;
module_param_named(chip_info_type, chip_info_type, int, 0444);
MODULE_PARM_DESC(chip_info_type, "chip_info: type");

int chip_info_revision = -1;
module_param_named(chip_info_revision, chip_info_revision, int, 0444);
MODULE_PARM_DESC(chip_info_revision, "chip_info: revision");

char chip_info_psid[16] = "";
module_param_string(chip_info_psid, chip_info_psid, 16, 0444);
MODULE_PARM_DESC(chip_info_psid, "chip_info: psid");

int g_chip_type = 0;
module_param_named(g_chip_type,
                   g_chip_type, int, 0644);
MODULE_PARM_DESC(g_chip_type, " set chip type for NO PCI and SGMII");

extern int skip_reset;

/****************************************************************************************
 * forward declaration of static symbols
 ***************************************************************************************/

struct pci_restart_saved_params {
    sxd_dev_id_t                  dev_id;
    struct listeners_and_rf_info *listeners;
    struct kobject               *kobj[SX_KOBJECT_MAX + 1];
    struct module_sysfs_node     *module_sysfs_arr;
    struct sx_device_info_set     dev_info_set;
};

static int __pci_probe_common(struct pci_dev                  *pdev,
                              const struct pci_device_id      *id,
                              struct sx_dev                  **new_dev,
                              struct pci_restart_saved_params *saved_params);
static void __pci_remove_common(struct pci_dev *pdev, bool keep_listeners);
#ifndef SXD_KERNEL_DISABLE_PCI_DRV_SHUTDOWN
static void __pci_shutdown_common(struct pci_dev *pdev);
#endif

static int __pci_probe_core(struct pci_dev *pdev, const struct pci_device_id *id);
static void __pci_remove_core(struct pci_dev *pdev);
#ifndef SXD_KERNEL_DISABLE_PCI_DRV_SHUTDOWN
static void __pci_shutdown_core(struct pci_dev *pdev);
#endif

static int __pci_probe_oob(struct pci_dev *pdev, const struct pci_device_id *id);
static void __pci_remove_oob(struct pci_dev *pdev);
#ifndef SXD_KERNEL_DISABLE_PCI_DRV_SHUTDOWN
static void __pci_shutdown_oob(struct pci_dev *pdev);
#endif

static int __sx_core_init_cb(struct sx_dev *dev, uint16_t device_id, uint16_t device_hw_revision);
static int __sx_load_fw(struct sx_dev *dev);
static void __sx_core_disconnect_all_trap_groups(struct sx_dev *dev);

static struct sx_priv * __create_dummy_device(int chip_type, struct pci_dev *pdev);
static void __remove_dummy_device(struct sx_priv *priv);

/****************************************************************************************
 * STATIC VARIABLES
 ***************************************************************************************/

#define SX_SINGLE_ASIC_DEFAULT_DEV_ID (1)

/* in use by probe function. must be accessed within pci_restart_lock! */
static struct sx_pci_probe_params {
    bool do_reset;
    u32  total_probes;
    u32  successful_probes;
    u32  fw_boot_failures;
    u32  total_removes;
    bool is_oob;
} __probe_params;

/****************************************************************************************
 * core PCI driver structures
 ***************************************************************************************/
static struct pci_device_id __sx_pci_table[] = {
    /* Spectrum PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM_PCI_DEV_ID) },

    /* Spectrum 'in flash recovery mode' PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM_FLASH_MODE_PCI_DEV_ID) },

    /* Spectrum2 PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM2_PCI_DEV_ID) },

    /* Spectrum2 'in flash recovery mode' PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM2_FLASH_MODE_PCI_DEV_ID) },

    /* Spectrum3 PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM3_PCI_DEV_ID) },

    /* Spectrum3 'in flash recovery mode' PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM3_FLASH_MODE_PCI_DEV_ID) },

    /* Spectrum4 PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM4_PCI_DEV_ID) },

    /* Spectrum4 'in flash recovery mode' PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM4_FLASH_MODE_PCI_DEV_ID) },

    /* Spectrum4 'RMA' PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM4_RMA_PCI_DEV_ID) },

    /* SwitchIB PCI device ID */
    { PCI_VDEVICE(MELLANOX, SWITCH_IB_PCI_DEV_ID) },

    /* SwitchIB 'in flash recovery mode' PCI device ID */
    { PCI_VDEVICE(MELLANOX, SWITCH_IB_FLASH_MODE_PCI_DEV_ID) },

    /* SwitchIB2 PCI device ID */
    { PCI_VDEVICE(MELLANOX, SWITCH_IB2_PCI_DEV_ID) },

    /* SwitchIB2 'in flash recovery mode' PCI device ID */
    { PCI_VDEVICE(MELLANOX, SWITCH_IB2_FLASH_MODE_PCI_DEV_ID) },

    /* Quantum PCI device ID */
    { PCI_VDEVICE(MELLANOX, QUANTUM_PCI_DEV_ID) },

    /* Quantum 'in flash recovery mode' PCI device ID */
    { PCI_VDEVICE(MELLANOX, QUANTUM_FLASH_MODE_PCI_DEV_ID) },

    /* Quantum2 PCI device ID */
    { PCI_VDEVICE(MELLANOX, QUANTUM2_PCI_DEV_ID) },

    /* Quantum2 'in flash recovery mode' PCI device ID */
    { PCI_VDEVICE(MELLANOX, QUANTUM2_FLASH_MODE_PCI_DEV_ID) },

    /* Quantum3 PCI device ID */
    { PCI_VDEVICE(MELLANOX, QUANTUM3_PCI_DEV_ID) },

    /* Quantum3 'in flash recovery mode' PCI device ID */
    { PCI_VDEVICE(MELLANOX, QUANTUM3_FLASH_MODE_PCI_DEV_ID) },

    { 0, }
};

MODULE_DEVICE_TABLE(pci, __sx_pci_table);

static struct pci_driver __sx_driver = {
    .name = DRV_NAME,
    .id_table = __sx_pci_table,
    .probe = __pci_probe_core,
    .remove = __pci_remove_core,
#ifndef SXD_KERNEL_DISABLE_PCI_DRV_SHUTDOWN
    .shutdown = __pci_shutdown_core
#endif
};

/****************************************************************************************
 * OOB PCI backbone driver structures
 ***************************************************************************************/
static struct pci_device_id __sx_oob_pci_table[] = {
    /* SwitchX PCI device ID */
    { PCI_VDEVICE(MELLANOX, SWITCHX_PCI_DEV_ID) },
    { 0, }
};

MODULE_DEVICE_TABLE(pci, __sx_oob_pci_table);

static struct pci_driver __sx_oob_driver = {
    .name = DRV_NAME "_oob",
    .id_table = __sx_oob_pci_table,
    .probe = __pci_probe_oob,
    .remove = __pci_remove_oob,
#ifndef SXD_KERNEL_DISABLE_PCI_DRV_SHUTDOWN
    .shutdown = __pci_shutdown_oob
#endif
};

/****************************************************************************************
 * STATIC functions
 ***************************************************************************************/
static void __sx_close_board(struct sx_dev *dev)
{
    sx_UNMAP_FA(dev);
    sx_free_icm(dev, sx_priv(dev)->fw.fw_icm, 0);
    sx_free_icm(dev, sx_priv(dev)->fw.pp_icm, 0);
}

static void __sx_cr_space_cleanup(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);

    iounmap(priv->cr_space_start);
    priv->cr_space_size = 0;
}

static void __sx_setup_sx_cleanup(struct sx_dev *dev)
{
    sx_af_counters_deinit();
    sx_core_destroy_rdq_table(dev, true);
    sx_core_destroy_sdq_table(dev, true);
    sx_cmd_use_polling(dev);
    sx_cleanup_eq_table(dev);
    sx_core_destroy_cq_table(dev);
}

static int __sx_map_cr_space_area(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);

    priv->cr_space_size = pci_resource_end(dev->pdev, 0) -
                          pci_resource_start(dev->pdev, 0);
    priv->cr_space_start = ioremap(pci_resource_start(dev->pdev, 0),
                                   priv->cr_space_size);
    if (!priv->cr_space_start) {
        printk(KERN_ERR "%s(): cr_space ioremap failed \n", __func__);
        return -EINVAL;
    }

    pr_debug("%s(): map cr_space area p:0x%llx, size:%d, cr_space start:%p \n",
             __func__,  pci_resource_start(dev->pdev, 0), priv->cr_space_size, priv->cr_space_start);

    return 0;
}

static void __sx_doorbell_cleanup(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);

    iounmap(priv->db_base);
}

static void __sx_enable_msi_x(struct sx_dev *dev)
{
    struct sx_priv   *priv = sx_priv(dev);
    struct msix_entry entry;
    int               err;
    int               i;

    if (msi_x) {
        entry.entry = 0;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0))
        err = pci_enable_msix_range(dev->pdev, &entry, 1, 1);
#else
        err = pci_enable_msix(dev->pdev, &entry, 1);
        if (err > 0) {
            printk(KERN_INFO PFX "Only %d MSI-X vectors available, "
                   "not using MSI-X\n", err);

            goto no_msi;
        }
#endif
        if (err < 0) {
            pr_debug(PFX "Failed enabling MSI-X interrupts. "
                     "Going to use standard interrupts instead\n");

            goto no_msi;
        }

        sx_info(dev, "MSI-X interrupts were enabled successfully\n");
        for (i = 0; i < SX_NUM_EQ; ++i) {
            priv->eq_table.eq[i].irq = entry.vector;
        }

        priv->flags |= SX_FLAG_MSI_X;
        return;
    }

no_msi:
    msi_x = 0;
    for (i = 0; i < SX_NUM_EQ; ++i) {
        priv->eq_table.eq[i].irq = dev->pdev->irq;
    }
}

static int __sx_init_chip_callbacks(struct sx_dev *dev)
{
    struct ku_access_mgir_reg reg_data;
    int                       err;
    int                       retry_num = 0;
    bool                      ok = false;

    /*
     *   This is a workaround to race condition happens when FW
     *   boot isn't finished and we start to read MGIR.
     *   We post the in_mailbox but FW zero GO bit. So we think
     *   that command is done.
     *   After this race we get 0 in all MGIR fields.
     *   The temporary solution is to reread again.
     *   The real solution should provide interface to read HEALTH
     *   bits which will indicate that FW boot is finished.
     */
    while (retry_num < 3) {
        memset(&reg_data, 0, sizeof(reg_data));
        reg_data.dev_id = dev->device_id;
        reg_data.op_tlv.type = 1;
        reg_data.op_tlv.length = 4;
        reg_data.op_tlv.dr = 0;
        reg_data.op_tlv.status = 0;
        reg_data.op_tlv.register_id = 0x9020; /* MGIR register ID */
        reg_data.op_tlv.r = 0;
        reg_data.op_tlv.method = EMAD_METHOD_QUERY;
        reg_data.op_tlv.op_class = 1;
        reg_data.op_tlv.tid = 0;

        err = sx_ACCESS_REG_MGIR(dev, &reg_data);
        if (!err && (reg_data.mgir_reg.hw_info.device_id != 0)) {
            ok = true;
            break;
        }

        msleep(500 * retry_num);
        retry_num++;
    }

    if (!ok) {
        printk(KERN_ERR "Failed to get chip information\n");
        err = -EFAULT;
        goto out;
    }

    memcpy(&sx_priv(dev)->dev_info.dev_info_ro.mgir, &reg_data.mgir_reg, sizeof(struct ku_mgir_reg));

    chip_info_type = reg_data.mgir_reg.hw_info.device_id;
    chip_info_revision = reg_data.mgir_reg.hw_info.device_hw_revision;
    strncpy(chip_info_psid, (const char*)reg_data.mgir_reg.fw_info.psid, sizeof(chip_info_psid) - 1);

    err = __sx_core_init_cb(dev, chip_info_type, chip_info_revision);
    if (err) {
        printk(KERN_ERR "Failed to set callbacks for device (dev_id=%u)\n", dev->device_id);
    }

out:
    return err;
}

static int __sx_init_board(struct sx_dev *dev)
{
    struct sx_priv            *priv = sx_priv(dev);
    int                        err;
    struct ku_query_board_info board;

    err = sx_QUERY_FW(dev, NULL);
    if (err) {
        sx_err(dev, "QUERY_FW command failed, aborting.\n");
        return err;
    }

    /* init local mailboxes */
    err = sx_QUERY_FW_2(dev, dev->device_id, HCR1);
    if (err) {
        sx_err(dev, "QUERY_FW_2 command failed, aborting.\n");
        return err;
    }

    priv->bar0_dbregs_offset = priv->fw.doorbell_page_offset;
    priv->bar0_dbregs_bar = priv->fw.doorbell_page_bar;

    err = __sx_load_fw(dev);
    if (err) {
        sx_err(dev, "Failed to start FW, aborting.\n");
        return err;
    }

    err = sx_QUERY_AQ_CAP(dev);
    if (err) {
        sx_err(dev, "QUERY_AQ_CAP command failed, aborting.\n");
        goto err_stop_fw;
    }
    priv->dev_cap.max_num_cpu_egress_tcs = 12;
    priv->dev_cap.max_num_cpu_ingress_tcs = 16;

    err = sx_QUERY_BOARDINFO(dev, &board);
    if (err) {
        sx_err(dev, "QUERY_BOARDINFO command failed, aborting.\n");
        goto err_stop_fw;
    }

    priv->xm.exists = board.xm_exists;
    priv->xm.num_local_ports = board.xm_num_local_ports;
    memcpy(priv->xm.local_ports, board.xm_local_ports, sizeof(priv->xm.local_ports));
    priv->eq_table.inta_pin = board.inta_pin;
    memcpy(priv->board_id, board.board_id, sizeof(priv->board_id));
    priv->vsd_vendor_id = board.vsd_vendor_id;
    return 0;

err_stop_fw:
    sx_UNMAP_FA(dev);
    sx_free_icm(dev, priv->fw.fw_icm, 0);

    return err;
}

static int __sx_core_init_cb(struct sx_dev *dev, uint16_t device_id, uint16_t device_hw_revision)
{
    struct sx_priv     *priv = sx_priv(dev);
    int                 err = 0;
    enum sxd_chip_types chip_type;

    switch (device_id) {
    case SXD_MGIR_HW_DEV_ID_SX:
        if (device_hw_revision == 0xA1) {
            chip_type = SXD_CHIP_TYPE_SWITCHX_A1;
        } else if (device_hw_revision == 0xA2) {
            chip_type = SXD_CHIP_TYPE_SWITCHX_A2;
        } else if (device_hw_revision == 0xA0) {
            printk(KERN_ERR PFX "The SwitchX device revision is A0, "
                   "and therefore it is not supported by SX driver\n");
            return -EFAULT;
        } else {
            printk(KERN_ERR PFX "The SwitchX device revision (0x%x) "
                   "is not supported by SX driver\n", device_hw_revision);
            return -EFAULT;
        }
        break;

    case SXD_MGIR_HW_DEV_ID_SWITCH_IB:
        chip_type = SXD_CHIP_TYPE_SWITCH_IB;
        break;

    case SXD_MGIR_HW_DEV_ID_SPECTRUM:
        if (device_hw_revision == 0xA1) {
            chip_type = SXD_CHIP_TYPE_SPECTRUM_A1;
        } else if (device_hw_revision == 0xA0) {
            chip_type = SXD_CHIP_TYPE_SPECTRUM;
        } else {
            printk(KERN_ERR PFX "The Spectrum device revision (0x%x) "
                   "is not supported by SX driver\n", device_hw_revision);
            return -EFAULT;
        }
        break;

    case SXD_MGIR_HW_DEV_ID_SWITCH_IB2:
        chip_type = SXD_CHIP_TYPE_SWITCH_IB2;
        break;

    case SXD_MGIR_HW_DEV_ID_QUANTUM:
        chip_type = SXD_CHIP_TYPE_QUANTUM;
        break;

    case SXD_MGIR_HW_DEV_ID_QUANTUM2:
        chip_type = SXD_CHIP_TYPE_QUANTUM2;
        break;

    case SXD_MGIR_HW_DEV_ID_QUANTUM3:
        chip_type = SXD_CHIP_TYPE_QUANTUM3;
        break;

    case SXD_MGIR_HW_DEV_ID_SPECTRUM2:
        chip_type = SXD_CHIP_TYPE_SPECTRUM2;
        break;

    case SXD_MGIR_HW_DEV_ID_SPECTRUM3:
        chip_type = SXD_CHIP_TYPE_SPECTRUM3;
        break;

    case SXD_MGIR_HW_DEV_ID_SPECTRUM4:
        chip_type = SXD_CHIP_TYPE_SPECTRUM4;
        break;

    default:
        printk(KERN_ERR PFX "ERROR: Unresolved chip type. device_id (%u)\n", device_id);
        return -EFAULT;
    }

    err = sx_core_dev_init_switchx_cb(dev, chip_type, 0);
    if (err) {
        printk(KERN_ERR PFX "callback device init failed for device (%u)\n",
               priv->profile.pci_profile.dev_id);
        return err;
    }

    return err;
}

/**
 * Update the device's cap struct with the default capabilities of the HW
 * (number of RDQs, SDQs, CQs Etc.)
 */
static void __set_default_capabilities(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);

    priv->dev_cap.log_max_rdq_sz = SX_MAX_LOG_DQ_SIZE;
    priv->dev_cap.log_max_sdq_sz = SX_MAX_LOG_DQ_SIZE;
    priv->dev_cap.log_max_cq_sz = 10;

    priv->dev_cap.max_num_rdqs = NUMBER_OF_RDQS;
    priv->dev_cap.max_num_sdqs = NUMBER_OF_SDQS;
    priv->dev_cap.max_num_cqs = NUMBER_OF_RDQS + NUMBER_OF_SDQS;

    priv->dev_cap.max_num_cpu_egress_tcs = 12;
    priv->dev_cap.max_num_cpu_ingress_tcs = 16;
}

static int __sx_load_fw(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err;

    priv->fw.fw_icm = sx_alloc_icm(dev, priv->fw.fw_pages,
                                   GFP_HIGHUSER | __GFP_NOWARN, 0);
    if (!priv->fw.fw_icm) {
        sx_err(dev, "Couldn't allocate FW area, aborting.\n");
        return -ENOMEM;
    }

    err = sx_MAP_FA(dev, priv->fw.fw_icm, SXD_MAP_MEMORY_TYPE_FW_LOAD_E);
    if (err) {
        sx_err(dev, "MAP_FA command failed, aborting.\n");
        goto err_free;
    }

    return 0;

err_free:
    sx_free_icm(dev, priv->fw.fw_icm, 0);
    return err;
}

static int __sx_map_doorbell_area(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);

    priv->db_base =
        ioremap(pci_resource_start(dev->pdev, priv->bar0_dbregs_bar)
                + priv->bar0_dbregs_offset,
                SX_DBELL_REGION_SIZE);
    if (!priv->db_base) {
        printk(KERN_ERR "%s(): bar: %d doorbell base: is NULL \n",
               __func__, priv->bar0_dbregs_bar);

        return -EINVAL;
    }

    pr_debug("%s(): bar: %d dev->db_base phys: 0x%llx , doorbell base: %p \n",
             __func__,
             priv->bar0_dbregs_bar,
             pci_resource_start(dev->pdev, priv->bar0_dbregs_bar)
             + priv->bar0_dbregs_offset,
             priv->db_base);

    return 0;
}

static int __sx_setup_sx(struct sx_dev *dev)
{
    int err = 0;

    err = sx_init_eq_table(dev);
    if (err) {
        sx_err(dev, "Failed to initialize "
               "event queue table, aborting.\n");
        goto out_ret;
    }

    err = sx_cmd_use_events(dev);
    if (err) {
        sx_err(dev, "Failed to switch to event-driven "
               "firmware commands, aborting.\n");
        goto err_eq_table_free;
    }

    err = sx_core_init_cq_table(dev);
    if (err) {
        sx_err(dev, "Failed to initialize CQ table, aborting.\n");
        goto err_cmd_poll;
    }

    err = sx_core_init_sdq_table(dev);
    if (err) {
        sx_err(dev, "Failed to initialize SDQ table, aborting.\n");
        goto err_cq_table_free;
    }

    err = sx_core_init_rdq_table(dev);
    if (err) {
        sx_err(dev, "Failed to initialize RDQ table, aborting.\n");
        goto err_sdq_table_free;
    }

    return 0;

err_sdq_table_free:
    sx_core_destroy_sdq_table(dev, true);

err_cq_table_free:
    sx_core_destroy_cq_table(dev);

err_cmd_poll:
    sx_cmd_use_polling(dev);

err_eq_table_free:
    sx_cleanup_eq_table(dev);

out_ret:
    return err;
}

static bool __check_fw_boot_status(struct pci_dev *pdev, struct sx_priv **priv)
{
    struct sx_priv           *dummy_priv = NULL;
    const char               *busname = dev_name(&pdev->dev);
    unsigned short            pci_dev_id = pdev->device;
    enum sxd_fw_boot_status_e fw_boot_status = SXD_FW_BOOT_STATUS_OK_E;
    int                       chip_type = 0;

    switch (pci_dev_id) {
    case SPECTRUM_FLASH_MODE_PCI_DEV_ID:
        chip_info_type = SPECTRUM_PCI_DEV_ID;
        chip_type = SXD_CHIP_TYPE_SPECTRUM;
        fw_boot_status = SXD_FW_BOOT_STATUS_IN_FLASH_RECOVERY_E;
        printk(KERN_ERR "FW-Status: Spectrum on bus %s is in 'Flash Mode' status\n", busname);
        break;

    case SPECTRUM2_FLASH_MODE_PCI_DEV_ID:
        chip_info_type = SPECTRUM2_PCI_DEV_ID;
        chip_type = SXD_CHIP_TYPE_SPECTRUM2;
        fw_boot_status = SXD_FW_BOOT_STATUS_IN_FLASH_RECOVERY_E;
        printk(KERN_ERR "FW-Status: Spectrum-2 on bus %s is in 'Flash Mode' status\n", busname);
        break;

    case SPECTRUM3_FLASH_MODE_PCI_DEV_ID:
        chip_info_type = SPECTRUM3_PCI_DEV_ID;
        chip_type = SXD_CHIP_TYPE_SPECTRUM3;
        fw_boot_status = SXD_FW_BOOT_STATUS_IN_FLASH_RECOVERY_E;
        printk(KERN_ERR "FW-Status: Spectrum-3 on bus %s is in 'Flash Mode' status\n", busname);
        break;

    case SPECTRUM4_FLASH_MODE_PCI_DEV_ID:
        chip_info_type = SPECTRUM4_PCI_DEV_ID;
        chip_type = SXD_CHIP_TYPE_SPECTRUM4;
        fw_boot_status = SXD_FW_BOOT_STATUS_IN_FLASH_RECOVERY_E;
        printk(KERN_ERR "FW-Status: Spectrum-4 on bus %s is in 'Flash Mode' status\n", busname);
        break;

    case SPECTRUM4_RMA_PCI_DEV_ID:
        chip_info_type = SPECTRUM4_PCI_DEV_ID;
        chip_type = SXD_CHIP_TYPE_SPECTRUM4;
        fw_boot_status = SXD_FW_BOOT_STATUS_RMA_E;
        printk(KERN_ERR "FW-Status: Spectrum-4 on bus %s is in 'RMA' status\n", busname);
        break;

    case SWITCH_IB_FLASH_MODE_PCI_DEV_ID:
        chip_info_type = SWITCH_IB_PCI_DEV_ID;
        chip_type = SXD_CHIP_TYPE_SWITCH_IB;
        fw_boot_status = SXD_FW_BOOT_STATUS_IN_FLASH_RECOVERY_E;
        printk(KERN_ERR "FW-Status: Switch-IB on bus %s is in 'Flash Mode' status\n", busname);
        break;

    case SWITCH_IB2_FLASH_MODE_PCI_DEV_ID:
        chip_info_type = SWITCH_IB2_PCI_DEV_ID;
        chip_type = SXD_CHIP_TYPE_SWITCH_IB2;
        fw_boot_status = SXD_FW_BOOT_STATUS_IN_FLASH_RECOVERY_E;
        printk(KERN_ERR "FW-Status: Switch-IB/2 on bus %s is in 'Flash Mode' status\n", busname);
        break;

    case QUANTUM_FLASH_MODE_PCI_DEV_ID:
        chip_info_type = QUANTUM_PCI_DEV_ID;
        chip_info_revision = 0;
        chip_type = SXD_CHIP_TYPE_QUANTUM;
        fw_boot_status = SXD_FW_BOOT_STATUS_IN_FLASH_RECOVERY_E;
        printk(KERN_ERR "FW-Status: Quantum on bus %s is in 'Flash Mode' status\n", busname);
        break;

    case QUANTUM2_FLASH_MODE_PCI_DEV_ID:
        chip_info_type = QUANTUM2_PCI_DEV_ID;
        chip_type = SXD_CHIP_TYPE_QUANTUM2;
        fw_boot_status = SXD_FW_BOOT_STATUS_IN_FLASH_RECOVERY_E;
        printk(KERN_ERR "FW-Status: Quantum-2 on bus %s is in 'Flash Mode' status\n", busname);
        break;

    case QUANTUM3_FLASH_MODE_PCI_DEV_ID:
        chip_info_type = QUANTUM3_PCI_DEV_ID;
        chip_type = SXD_CHIP_TYPE_QUANTUM3;
        fw_boot_status = SXD_FW_BOOT_STATUS_IN_FLASH_RECOVERY_E;
        printk(KERN_ERR "FW-Status: Quantum-3 on bus %s is in 'Flash Mode' status\n", busname);
        break;

    default:
        return true; /* everything's fine with this device, no fw-boot issue */
    }

    dummy_priv = __create_dummy_device(chip_type, pdev);
    if (dummy_priv) {
        dummy_priv->dev.pdev = NULL;
        dummy_priv->dev_info.dev_info_ro.chip_type = chip_type;
        dummy_priv->dev_info.dev_info_ro.fw_boot_status = fw_boot_status;
    }

    *priv = dummy_priv;
    return false;
}

static int __pci_probe_common(struct pci_dev                  *pdev,
                              const struct pci_device_id      *id,
                              struct sx_dev                  **new_dev,
                              struct pci_restart_saved_params *saved_params)
{
    struct sx_priv *priv = NULL;
    struct sx_dev  *dev = NULL;
    sxd_dev_id_t    dev_id = 0;
    int             err = 0;

    /* at this point 'pci_restart_lock' must be acquired (write lock)! */
    BUG_ON(!rwsem_is_locked(&sx_glb.pci_restart_lock));

    __probe_params.total_probes++;

    printk(KERN_INFO PFX "Probe %s(%d) device %u\n", __FUNCTION__, __LINE__, \
           pdev->device);

    if (!__check_fw_boot_status(pdev, &priv)) {
        if (!priv) {
            err = -ENODEV;
        } else {
            __probe_params.fw_boot_failures++;
        }

        err = sx_dev_db_pdev_to_dev_id(pdev, &dev_id);
        if (err) {
            printk(KERN_ERR "failed to get device ID from PCI-device (err=%d)\n", err);
        } else {
            err = sx_add_char_dev(&sx_glb.cdev, dev_id);
        }

        goto out;
    }

    err = sx_core_init_one(&priv, saved_params);
    if (err) {
        dev_err(&pdev->dev, "sx_core_init_one failed with err: %d , aborting.\n",
                err);
        goto out;
    }

    dev = &priv->dev;

    err = pci_enable_device(pdev);
    if (err) {
        dev_err(&pdev->dev, "Cannot enable PCI device, aborting.\n");
        goto err_enable_pdev;
    }

    /* Check for BARs. Length of PCI space: LOG2_CR_BAR_SIZE
     * We expect BAR0:
     * - 1MB in Baz;
     * - 4MB in Pelican;
     * - 16MB in Quantum, Phoenix;
     * - 64MB in Firebird;
     * - 128MB in Blackbird;
     * - 256MB in Albatross, Quantum3;
     */
    if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM) ||
        ((pci_resource_len(pdev, 0) != 1 << 20) &&
         (pci_resource_len(pdev, 0) != 1 << 22) &&
         (pci_resource_len(pdev, 0) != 1 << 24) &&
         (pci_resource_len(pdev, 0) != 1 << 26) &&
         (pci_resource_len(pdev, 0) != 1 << 27) &&
         (pci_resource_len(pdev, 0) != 1 << 28))) {
        dev_err(&pdev->dev, "Missing BAR0, aborting. Flags: %#lx Len: %#llx \n",
                pci_resource_flags(pdev, 0), pci_resource_len(pdev, 0));
        err = -ENODEV;
        goto err_disable_pdev;
    }

    err = pci_request_region(pdev, 0, DRV_NAME);
    if (err) {
        dev_err(&pdev->dev, "Cannot request control region, "
                "aborting.\n");
        goto err_disable_pdev;
    }

    pci_set_master(pdev);
    err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
    if (err) {
        dev_warn(&pdev->dev, "Warning: couldn't set both DMA mask and coherent DMA mask to 64-Bit "
                 "DMA mask.\n");
        err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
        if (err) {
            dev_err(&pdev->dev, "Failed to set both DMA mask and coherent DMA mask to 32-Bit, aborting.\n");
            goto err_release_bar0;
        }
    }


    dev->pdev = pdev;

    if (sx_cmd_pool_create(dev)) {
        sx_err(dev, "Failed to create command buffer pool, aborting.\n");
        goto err_release_bar0;
    }

    if (sx_cmd_init_pci(dev)) {
        sx_err(dev, "Failed to initialize command interface, aborting.\n");
        goto err_free_pool;
    }

    pci_set_drvdata(pdev, dev);

    err = sx_dev_db_add_device(dev); /* also allocated the device ID */
    if (err) {
        goto err_free_pool;
    }

    err = sx_dpt_init_dev_pci(dev);
    if (err) {
        sx_err(dev, "Failed initializing default PCI device "
               "attributes in the DPT, aborting.\n");
        goto err_remove_device;
    }

    /*
     * user may need to load (ONLY) the driver and take CR-Space dump ["modprobe sx_core skip_reset=1"].
     * To do this, the driver must be loaded with skip_reset=1. In this case, and only on a single-ASIC system,
     * the default device reassignment (from dev_id=255 to dev_id=1) is done internally here and not by the user
     * with ioctl(CTRL_CMD_ADD_DEV_PATH). Only after this, dev_id=1 is valid to access from sxd-libs in order
     * to get CR-Space dump.
     */
    if (skip_reset && !sx_core_has_predefined_devices()) {
        printk(KERN_NOTICE "in SKIP_RESET mode, reassigning device ID 255 to device ID %d\n",
               SX_SINGLE_ASIC_DEFAULT_DEV_ID);
        err = sx_dev_db_reassign_dev_id_to_default_device(SX_SINGLE_ASIC_DEFAULT_DEV_ID);
        if (err) {
            printk(KERN_ERR "failed to reassign dev_id 255 to dev_id %d internally\n", SX_SINGLE_ASIC_DEFAULT_DEV_ID);
            goto err_remove_device;
        }

        /* set the same access rights in DPT table */
        memcpy(&sx_glb.sx_dpt.dpt_info[SX_SINGLE_ASIC_DEFAULT_DEV_ID],
               &sx_glb.sx_dpt.dpt_info[DEFAULT_DEVICE_ID],
               sizeof(sx_glb.sx_dpt.dpt_info[SX_SINGLE_ASIC_DEFAULT_DEV_ID]));
    }

    err = __sx_init_chip_callbacks(dev);
    if (err) {
        goto err_remove_device;
    }

#if defined(PD_BU) && !defined(PD_BU_ENABLE_SW_RESET)
    printk(KERN_INFO PFX "Performing SW reset is SKIPPED in PD mode.\n");
#else
    err = sx_reset(dev, dev->pdev->device, __probe_params.do_reset);
    if (err) {
        sx_err(dev, "Failed to reset HW, aborting.\n");
        goto err_remove_device;
    }
#endif

    err = __sx_init_board(dev);
    if (err) {
        goto err_cmd;
    }

    __sx_enable_msi_x(dev);
    err = __sx_map_doorbell_area(dev);
    if (err) {
        goto err_dbell;
    }

    err = __sx_map_cr_space_area(dev);
    if (err) {
        goto err_cr_space;
    }

    err = __sx_setup_sx(dev);
    if ((err == -EBUSY) && (priv->flags & SX_FLAG_MSI_X)) {
        priv->flags &= ~SX_FLAG_MSI_X;
        pci_disable_msix(dev->pdev);
        err = __sx_setup_sx(dev);
    }

    if (err) {
        goto err_cr_space_clean;
    }

    sx_emad_dev_init(dev);

    priv->global_flushing = false;
    priv->dev_stuck = false;
    priv->dev_stuck_time = 0;

    err = sx_core_clock_dev_init(priv);
    if (err) {
        sx_err(dev, "Failed to initialize clock. aborting.\n");
        goto out_setup_sx_cleanup;
    }

    err = sx_core_cr_dump_init(priv);
    if (err) {
        sx_err(dev, "Couldn't start cr_dump. Aborting.\n");
        goto out_crdump_failed;
    }

    if (!__probe_params.is_oob) {
        err = sx_sysfs_asic_create(dev);
        if (err) {
            sx_err(dev, "Failed to create ASIC sysfs\n");
            goto out_sysfs_failed;
        }

        err = sx_module_sysfs_register_module_event_handler(dev);
        if (err) {
            sx_err(dev, "Failed to register module event\n");
            goto out_module_event_failed;
        }

        err = sx_sysfs_asic_init_tempeature(dev);
        if (err) {
            sx_err(dev, "Failed to initialize temperature monitoring\n");
            goto out_temperature_failed;
        }
    }

    __probe_params.successful_probes++;

    if (__probe_params.do_reset && !SX_IS_FW_CAP(priv, SX_FW_CAP_IND_MOD)) {
        /* udev event for system management purpose:
         * - only if chip was reset or warm_boot
         * - it is raised here only if FW does not support independent-module
         */
        sx_send_udev_event(pdev, priv, KOBJ_ADD, "After chip reset");
    }

    if (new_dev) {
        *new_dev = dev;
    }

    if (saved_params) { /* PCI_RESTART flow */
        dev->device_id = saved_params->dev_id;
        sx_dpt_init_dev_pci(dev);

        /* no need to create a new char device, it is already created in old PCI life */
    } else { /* Normal probe flow, need to create a new char device */
        if (DEFAULT_DEVICE_ID_CHECK(dev->device_id)) {
            err = sx_add_char_dev(&sx_glb.cdev, 1 /* Use minor 1 for char device */);
        } else {
            err = sx_add_char_dev(&sx_glb.cdev, dev->device_id);
        }

        if (err) {
            sx_err(dev, "Failed to add character device. Aborting.\n");
            goto out_char_dev_failed;
        }
    }

    err = sx_core_register_device(dev);
    if (err) {
        sx_err(dev, "Failed to register the device, aborting.\n");
        goto out_register_failed;
    }

    priv->registered = true;

    return 0;

out_register_failed:
out_char_dev_failed:
out_temperature_failed:
    sx_module_sysfs_unregister_module_event_handler(dev);

out_module_event_failed:
    sx_sysfs_asic_remove(dev);

out_sysfs_failed:
    sx_core_cr_dump_deinit(priv);

out_crdump_failed:
    sx_core_clock_dev_deinit(priv);

out_setup_sx_cleanup:
    __sx_setup_sx_cleanup(dev);

err_cr_space_clean:
    __sx_cr_space_cleanup(dev);

err_cr_space:
    __sx_doorbell_cleanup(dev);

err_dbell:
    if (priv->flags & SX_FLAG_MSI_X) {
        pci_disable_msix(pdev);
    }

    __sx_close_board(dev);

err_remove_device:
    sx_dev_db_remove_device(dev);

err_free_pool:
    sx_cmd_pool_destroy(dev);

err_cmd:
    sx_cmd_unmap(dev);

err_release_bar0:
    pci_release_region(pdev, 0);

err_disable_pdev:
    pci_disable_device(pdev);
    pci_set_drvdata(pdev, NULL);

err_enable_pdev:
    sx_core_remove_one(priv, false);

out:
    return err;
}

/* The purpose of keep_listeners is to let the function know whether to
 * deallocate the original listeners database or not. This flag is used in
 * the PCI restart flow.
 */
static void __pci_remove_common(struct pci_dev *pdev, bool keep_listeners)
{
    struct sx_priv *priv;
    struct sx_dev  *dev;
    int             i;

    /* at this point 'pci_restart_lock' must be acquired (write lock)! */
    BUG_ON(!rwsem_is_locked(&sx_glb.pci_restart_lock));

    __probe_params.total_removes++;

    dev = pci_get_drvdata(pdev);
    if (!dev) {
        return;
    }

    priv = sx_priv(dev);

    if (sx_core_fw_is_faulty(dev)) {
        __remove_dummy_device(priv);
        return;
    }

    sx_module_sysfs_unregister_module_event_handler(dev);

    sx_sysfs_asic_remove(dev);

    /* must be called before any CQ/DQ shutdown so there will be no race with the
     * asynchronous health-check mechanism
     */
    sx_health_check_dev_deinit(dev);

    pci_set_drvdata(pdev, NULL);

    if (priv->kobj_add_done) {
        /* udev event for system management purpose (only if chip was reset enable or warm boot) */
        sx_send_udev_event(pdev, priv, KOBJ_REMOVE, "Unregistering from PCI");
    }

    if (priv->registered) {
        sx_core_unregister_device(dev);
        priv->registered = false;
    }

    /*
     * Disconnect all trap groups before flush and destroy
     */
    __sx_core_disconnect_all_trap_groups(dev);

    sx_emad_dev_deinit(dev);

    priv->global_flushing = true;

    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        if (sx_bitmap_test(&priv->swid_bitmap, i)) {
            sx_disable_swid(dev, i);
        }
    }

    __sx_setup_sx_cleanup(dev);
    __sx_cr_space_cleanup(dev);
    __sx_doorbell_cleanup(dev);

    sx_core_ptp_dev_cleanup(priv);
    sx_core_cr_dump_deinit(priv);
    sx_core_clock_dev_deinit(priv);

    if (priv->flags & SX_FLAG_MSI_X) {
        pci_disable_msix(dev->pdev);
    }

    sx_UNMAP_FA(dev);
    sx_free_icm(dev, priv->fw.fw_icm, 0);
    sx_free_icm(dev, priv->fw.pp_icm, 0);
    sx_cmd_pool_destroy(dev);
    sx_cmd_unmap(dev);

    pci_release_region(pdev, 0);
    pci_disable_device(pdev);

    sx_dev_db_remove_device(dev);
    sx_core_remove_one(priv, keep_listeners);
}

#ifndef SXD_KERNEL_DISABLE_PCI_DRV_SHUTDOWN
static void __pci_shutdown_common(struct pci_dev *pdev)
{
    struct sx_dev *dev = NULL;

    pr_debug(PFX "Shutdown PCI driver\n");

    down_write(&sx_glb.pci_restart_lock);

    dev = pci_get_drvdata(pdev);

    if (!dev) {
        printk(KERN_ERR "PCI shutdown - could not get SX device!\n");
    } else {
        __pci_remove_core(pdev);
    }

    up_write(&sx_glb.pci_restart_lock);
}
#endif

static int __pci_probe_core(struct pci_dev *pdev, const struct pci_device_id *id)
{
    printk(KERN_NOTICE "found a PCI core device\n");
    return __pci_probe_common(pdev, id, NULL, NULL);
}

static void __pci_remove_core(struct pci_dev *pdev)
{
    printk(KERN_NOTICE "remove a PCI core device\n");
    __pci_remove_common(pdev, false);
    sx_glb.pci_drivers_in_use &= ~PCI_DRIVER_F_SX_DRIVER;
}

#ifndef SXD_KERNEL_DISABLE_PCI_DRV_SHUTDOWN
static void __pci_shutdown_core(struct pci_dev *pdev)
{
    printk(KERN_NOTICE "shutdown a PCI core device\n");
    __pci_shutdown_common(pdev);
}
#endif

static int __pci_probe_oob(struct pci_dev *pdev, const struct pci_device_id *id)
{
    printk(KERN_NOTICE "found a PCI OOB backbone device\n");
    return __pci_probe_common(pdev, id, &sx_glb.oob_backbone_dev, NULL);
}

static void __pci_remove_oob(struct pci_dev *pdev)
{
    printk(KERN_NOTICE "remove a PCI OOB backbone device\n");
    __pci_remove_common(pdev, false);
    sx_glb.pci_drivers_in_use &= ~PCI_DRIVER_F_SX_OOB_DRIVER;
}

#ifndef SXD_KERNEL_DISABLE_PCI_DRV_SHUTDOWN
static void __pci_shutdown_oob(struct pci_dev *pdev)
{
    printk(KERN_NOTICE "shutdown a PCI OOB backbone device\n");
    __pci_shutdown_common(pdev);
}
#endif

static int __pci_register_common(struct pci_driver *driver,
                                 bool               do_reset,
                                 u32               *total_probes,
                                 u32               *successful_probes,
                                 u32                driver_flag)
{
    bool unreg_driver = false;
    int  ret = 0;

    /* at this point 'pci_restart_lock' must be acquired (write lock)! */
    BUG_ON(!rwsem_is_locked(&sx_glb.pci_restart_lock));

    memset(&__probe_params, 0, sizeof(__probe_params));
    __probe_params.do_reset = do_reset;
    __probe_params.is_oob = (driver_flag == PCI_DRIVER_F_SX_OOB_DRIVER) ? true : false;


    ret = pci_register_driver(driver);
    if (ret < 0) {
        printk(KERN_ERR "pci_register_driver() failed (err=%d)\n", ret);
        goto out;
    }

    if (__probe_params.total_probes == 0) {
        printk(KERN_ERR "pci_register_driver() returned successfully but probe function not called\n");
        unreg_driver = true;
        goto out;
    }

    if (__probe_params.total_probes != __probe_params.successful_probes + __probe_params.fw_boot_failures) {
        printk(KERN_ERR "pci_register_driver() returned successfully but probe function failed\n");
        unreg_driver = true;
        ret = -EIO;
        goto out;
    }

    sx_glb.pci_drivers_in_use |= driver_flag;

out:
    if (unreg_driver) {
        pci_unregister_driver(driver);
    }

    *total_probes = __probe_params.total_probes;
    *successful_probes = __probe_params.successful_probes;
    return ret;
}

static void __pci_unregister_common(struct pci_driver *driver, u32 *total_removes, u32 driver_flag)
{
    /* at this point 'pci_restart_lock' must be acquired (write lock)! */
    BUG_ON(!rwsem_is_locked(&sx_glb.pci_restart_lock));

    memset(&__probe_params, 0, sizeof(__probe_params));

    if (sx_glb.pci_drivers_in_use & driver_flag) {
        pci_unregister_driver(driver);
        *total_removes = __probe_params.total_removes;
    }
}

static void __sx_core_disconnect_all_trap_groups(struct sx_dev *dev)
{
    int err;

    if (dev == NULL) {
        printk(KERN_ERR PFX "sx_core_disconnect_all_trap_groups: dev is NULL \n");
        return;
    }

    err = __sx_core_dev_specific_cb_get_reference(dev);
    if (err) {
        printk(KERN_ERR PFX " dev_specific_cb_get_ref failed. Failed disconnect trap groups.\n");
        return;
    }

    if (sx_priv(dev)->dev_specific_cb.sx_disconnect_all_trap_groups_cb != NULL) {
        sx_priv(dev)->dev_specific_cb.sx_disconnect_all_trap_groups_cb(dev);
    }
    __sx_core_dev_specific_cb_release_reference(dev);
}

/****************************************************************************************
 * NON-STATIC functions
 ***************************************************************************************/

void sx_send_udev_event(struct pci_dev *pdev, struct sx_priv *priv, enum kobject_action action, const char *origin)
{
    char        sdk_env[] = "SX_CORE_EVENT=1";
    char       *envp_ext[] = { sdk_env, NULL };
    const char *action_str = NULL;

    switch (action) {
    case KOBJ_ADD:
        if (!priv) {
            printk(KERN_ERR "Device private data is NULL, will not send UDEV KOBJ_ADD event\n");
            return;
        }

        priv->kobj_add_done = true;
        action_str = "KOBJ_ADD";
        break;

    case KOBJ_REMOVE:
        if (!priv) {
            printk(KERN_ERR "Device private data is NULL, will not send UDEV KOBJ_REMOVE event\n");
            return;
        }

        priv->kobj_add_done = false;
        action_str = "KOBJ_REMOVE";
        break;

    case KOBJ_ONLINE:
        action_str = "KOBJ_ONLINE";
        break;

    case KOBJ_OFFLINE:
        action_str = "KOBJ_OFFLINE";
        break;

    default:
        action_str = "N/A";
        break;
    }

    if (!origin) {
        origin = "N/A";
    }

    printk(KERN_NOTICE "sending UDEV event from sx-core driver [bus=%s, action=%d (%s), origin='%s']\n",
           dev_name(&pdev->dev), action, action_str, origin);

    kobject_uevent_env(&pdev->dev.kobj, action, envp_ext);
}

static int __cr_mode_get_mailboxes(struct sx_dev *dev)
{
    int ret;

    if (sx_i2c_mode()) {
        /* sx_dpt_init_default_dev() eventually calls get_local_mbox() of the I2C driver
         * and it will initialize the mailboxes in DPT and in the I2C driver itself */
        ret = sx_dpt_init_default_dev(dev);
    } else { /* MST mode */
        ret = sx_QUERY_FW_2(dev, dev->device_id, HCR2);
    }

    if (ret) {
        printk(KERN_ERR "CR-Mode: Failed to get mailboxes (err=%d)\n", ret);
    }

    return ret;
}

const char * sx_get_chip_type_str(sxd_chip_types_t chip_type)
{
    const char *ret;

    switch (chip_type) {
    case SXD_CHIP_TYPE_SWITCHX_A2:
        ret = "SwitchX-A2";
        break;

    case SXD_CHIP_TYPE_SWITCHX_A1:
        ret = "SwitchX-A1";
        break;

    case SXD_CHIP_TYPE_SWITCHX_A0:
        ret = "SwitchX-A0";
        break;

    case SXD_CHIP_TYPE_SWITCH_IB:
        ret = "Switch-IB";
        break;

    case SXD_CHIP_TYPE_SPECTRUM:
        ret = "Spectrum-1";
        break;

    case SXD_CHIP_TYPE_SWITCH_IB2:
        ret = "Switch-IB/2";
        break;

    case SXD_CHIP_TYPE_SPECTRUM_A1:
        ret = "Spectrum-A1";
        break;

    case SXD_CHIP_TYPE_SPECTRUM2:
        ret = "Spectrum-2";
        break;

    case SXD_CHIP_TYPE_QUANTUM:
        ret = "Quantum";
        break;

    case SXD_CHIP_TYPE_SPECTRUM3:
        ret = "Spectrum-3";
        break;

    case SXD_CHIP_TYPE_QUANTUM2:
        ret = "Quantum-2";
        break;

    case SXD_CHIP_TYPE_SPECTRUM4:
        ret = "Spectrum-4";
        break;

    case SXD_CHIP_TYPE_QUANTUM3:
        ret = "Quantum-3";
        break;

    default:
        ret = "N/A";
    }

    return ret;
}

int sx_dev_init_cr_device(bool reset_chip)
{
    struct sx_priv *priv = NULL;
    struct sx_dev  *dev = NULL;
    int             ret = 0;

    printk(KERN_INFO "Running in CR-Space configuration, creating device\n");

    ret = sx_core_init_one(&priv, NULL);
    if (ret) {
        printk(KERN_ERR "Failed to create CR-Space device (err=%d)\n", ret);
        goto out;
    }

    INIT_LIST_HEAD(&priv->cr_mode.tx_queue);
    spin_lock_init(&priv->cr_mode.tx_queue_lock);
    dev = &priv->dev;

    ret = sx_dev_db_add_device(dev); /* also allocated the device ID */
    if (ret) {
        printk(KERN_ERR "Failed to add CR-Space device to database (err=%d)\n", ret);
        goto out_remove_one;
    }

    ret = __cr_mode_get_mailboxes(dev);
    if (ret) {
        printk(KERN_ERR "Failed to get mailboxes before reset (err=%d)\n", ret);
        goto out_remove_from_db;
    }

    ret = __sx_init_chip_callbacks(dev);
    if (ret) {
        printk(KERN_ERR "Failed to initialize common board information on CR-Space device (err=%d)\n", ret);
        goto out_remove_from_db;
    }

    ret = sx_reset(dev, chip_info_type, (reset_chip) ? 1 : 0);
    if (ret) {
        printk(KERN_ERR "Failed to reset CR-Space device (err=%d)\n", ret);
        goto out_remove_from_db;
    }

    ret = sx_add_char_dev(&sx_glb.cdev, 1 /* Use minor 1 for char device */);
    if (ret) {
        printk(KERN_ERR "Failed to add character device (err=%d). Aborting.\n", ret);
        goto out_remove_from_db;
    }

    ret = sx_core_register_device(dev);
    if (ret) {
        printk(KERN_ERR "Failed to register the device, aborting.\n");
        goto out_remove_from_db;
    }

    priv->registered = true;

    /*
     * after reset, we should ask for the mailboxes again
     * (maybe there is a new FW version loaded with different mailbox layout)
     */
    ret = __cr_mode_get_mailboxes(dev);
    if (ret) {
        printk(KERN_ERR "Failed to get mailboxes after reset (err=%d)\n", ret);
        goto out_remove_from_db;
    }

    if (reset_chip) {
        if ((sx_glb.sx_dpt.dpt_info[dev->device_id].in_mb_size[HCR2] < 0x800) ||
            (sx_glb.sx_dpt.dpt_info[dev->device_id].out_mb_size[HCR2] < 0x800)) {
            printk(KERN_ERR "HCR2 (Dev %d): In CR-Space mode, mailboxes must be at least 0x800 in size!\n",
                   dev->device_id);
            printk(KERN_ERR "If you just burned a new FW image, try to reload the I2C driver\n");
            ret = -ENOBUFS;
            goto out_remove_from_db;
        }
    }

    ret = sx_cr_polling_thread_init(dev);
    if (ret) {
        printk(KERN_ERR "Failed to initialize CR-Space polling thread (err=%d)\n", ret);
        goto out_remove_from_db;
    }

    return 0;

out_remove_from_db:
    sx_dev_db_remove_device(dev);

out_remove_one:
    sx_core_remove_one(priv, false);

out:
    return ret;
}

void sx_dev_deinit_cr_device(void)
{
    struct sx_priv *priv = NULL;
    struct sx_dev  *dev = NULL;

    dev = sx_dev_db_get_default_device();
    if (!dev) {
        printk(KERN_ERR "Did not find CR-Space device\n");
        return;
    }

    priv = sx_priv(dev);

    sx_cr_polling_thread_deinit(dev);

    if (priv->registered) {
        sx_core_unregister_device(dev);
        priv->registered = false;
    }

    sx_dev_db_remove_device(dev);
    sx_core_remove_one(priv, false);
}

int sx_dev_init_core_pci(bool do_reset, u32 *total_probes, u32 *successful_probes)
{
    int ret = 0;

    down_write(&sx_glb.pci_restart_lock);
    ret = __pci_register_common(&__sx_driver,
                                do_reset,
                                total_probes,
                                successful_probes,
                                PCI_DRIVER_F_SX_DRIVER);
    up_write(&sx_glb.pci_restart_lock);
    return ret;
}

void sx_dev_deinit_core_pci(u32 *total_removes)
{
    down_write(&sx_glb.pci_restart_lock);
    __pci_unregister_common(&__sx_driver, total_removes, PCI_DRIVER_F_SX_DRIVER);
    up_write(&sx_glb.pci_restart_lock);
}

int sx_dev_init_oob_pci(void)
{
    u32 total = 0, ok = 0;
    int err = 0;

    printk(KERN_INFO "OOB: initializing SwitchX device on PCI\n");

    down_write(&sx_glb.pci_restart_lock);

    err = __pci_register_common(&__sx_oob_driver,
                                true,
                                &total,
                                &ok,
                                PCI_DRIVER_F_SX_OOB_DRIVER);

    up_write(&sx_glb.pci_restart_lock);

    if (err) {
        printk(KERN_ERR "OOB: pci_register_driver() failed (err=%d)\n", err);
        goto out;
    }

    if (total == 0) {
        printk(KERN_ERR "OOB: SwitchX device was not found!\n");
        err = -ENODEV;
        goto out;
    }

    printk(KERN_INFO "OOB: SwitchX device was successfully initialized on PCI\n");

out:
    return err;
}


void sx_dev_deinit_oob_pci(void)
{
    u32 dummy = 0;

    printk(KERN_INFO "OOB: deinitializing SwitchX device on PCI\n");

    down_write(&sx_glb.pci_restart_lock);
    __pci_unregister_common(&__sx_oob_driver, &dummy, PCI_DRIVER_F_SX_OOB_DRIVER);
    up_write(&sx_glb.pci_restart_lock);
}

int sx_restart_one_pci(struct sx_dev *dev)
{
    struct sx_dev                  *new_dev = NULL;
    struct sx_priv                 *priv = NULL;
    struct pci_dev                 *pdev = NULL;
    struct pci_restart_saved_params saved_params;
    int                             err = 0;

    printk(KERN_INFO "RESTART PCI DEVICE %u\n", dev->device_id);

    if (!dev->pdev) {
        printk(KERN_ERR PFX "sx_restart_one_pci error: dev or pdev are NULL, exit \n");
        return -ENODEV;
    }

    priv = sx_priv(dev);

    /* save old device's information for the new device */
    memset(&saved_params, 0, sizeof(saved_params));
    saved_params.dev_id = dev->device_id;
    saved_params.listeners = priv->listeners_and_rf_db.info;
    memcpy(saved_params.kobj, priv->kobj, sizeof(saved_params.kobj)); /* save sysfs info */
    saved_params.module_sysfs_arr = priv->module_sysfs_arr; /* save module eeprom sysfs info */
    memcpy(&saved_params.dev_info_set, &priv->dev_info.dev_info_set, sizeof(saved_params.dev_info_set));

    /* must keep 'dev->pdev' because 'dev' is about to be deallocated and then allocated again */
    pdev = dev->pdev;

    /* enable chip reset from sx_restart_one_pci even
     * if driver was loaded with __perform_chip_reset = 0
     * for example in case of WARM boot*/

    down_write(&sx_glb.pci_restart_lock);

    memset(&__probe_params, 0, sizeof(__probe_params));
    __probe_params.do_reset = true;

    __pci_remove_common(pdev, true);
    err = __pci_probe_common(pdev, NULL, &new_dev, &saved_params);
    if (err) {
        printk(KERN_ERR "__pci_probe_common failed with err: %d \n", err);
        goto out;
    }

out:
    up_write(&sx_glb.pci_restart_lock);

    return err;
}

int sx_core_init_one(struct sx_priv **sx_priv, struct pci_restart_saved_params *saved_params)
{
    struct sx_priv *priv;
    struct sx_dev  *dev;
    int             i, j, err;

    if (!sx_priv) {
        printk(KERN_ERR PFX "Invalid param %s\n", __func__);
        return -EINVAL;
    }

    priv = vmalloc(sizeof(struct sx_priv));
    if (!priv) {
        printk(KERN_ERR PFX "Device struct alloc failed, aborting.\n");
        err = -ENOMEM;
        goto out;
    }
    memset(priv, 0, sizeof *priv);
    dev = &priv->dev;

    mutex_init(&priv->listeners_and_rf_db.lock);
    if (saved_params) {
        priv->listeners_and_rf_db.info = saved_params->listeners;
        priv->module_sysfs_arr = saved_params->module_sysfs_arr;
        memcpy(&priv->kobj, saved_params->kobj, sizeof(priv->kobj));
        memcpy(&priv->dev_info.dev_info_set, &saved_params->dev_info_set, sizeof(priv->dev_info.dev_info_set));
    } else {
        priv->listeners_and_rf_db.info = kmalloc(sizeof(struct listeners_and_rf_info), GFP_KERNEL);
        if (!priv->listeners_and_rf_db.info) {
            printk(KERN_ERR PFX "Device listeners database allocation failed. aborting.\n");
            err = -ENOMEM;
            goto out_free_priv;
        }

        for (i = 0; i < NUM_HW_SYNDROMES + 1; i++) {
            INIT_LIST_HEAD(&priv->listeners_and_rf_db.info->per_synd_list[i]);
        }
    }

    /* default pvid for all ports is 1 */
    for (i = 0; i < MAX_SYSPORT_NUM; i++) {
        if (i < MAX_LAG_NUM) {
            priv->pvid_lag_db[i] = 1;
        }

        priv->pvid_sysport_db[i] = 1;
    }

    /* initialize lag_filter_db with invalid value */
    for (i = 0; i < NUM_HW_SYNDROMES; i++) {
        for (j = 0; j < MAX_LAG_PORTS_IN_FILTER; j++) {
            priv->lag_filter_db[i][j] = LAG_ID_INVALID;
        }
    }

    /* initialize fid to hw_fid mapping with invalid value */
    for (i = 0; i < MAX_FIDS_NUM; i++) {
        priv->fid_to_hwfid[i] = INVALID_HW_FID_ID;
    }

    /* initialize rif to hw_fid mapping with invalid value */
    for (i = 0; i < MAX_RIFS_NUM; i++) {
        priv->rif_id_to_hwfid[i] = INVALID_HW_FID_ID;
        memset(&priv->rif_data[i], 0, sizeof(priv->rif_data[0]));
    }

    for (i = 0; i < MAX_SLOT_NUM; i++) {
        for (j = 0; j < MAX_MODULE_NUM; j++) {
            priv->module_data[i][j].power_mode_policy = SX_MODULE_POWER_MODE_POLICY_HIGH;
        }
    }

    if (sx_cr_mode()) {
        /* in CR mode we're polling for port state only on active ports:
         * active port: swid != 255
         * inactive port: swid = 255
         *
         * by default, keep all local ports to swid 0 because IB does not always
         * use this mapping. only in CR-Mode we explicitly inactivate all ports by default.
         */
        for (i = 0; i < MAX_PHYPORT_NUM + 1; i++) {
            priv->local_to_swid_db[i] = 255; /* invalid swid */
        }
    }

    mutex_init(&priv->module_access_mutex);

    for (i = 0; i < MAX_MONITOR_RDQ_NUM; i++) {
        priv->monitor_rdqs_arr[i] = RDQ_INVALID_ID;
    }

    /* no default device when there are predefined devices or on OOB system */
    if (!sx_core_has_predefined_devices() && !is_sgmii_supported()) {
        err = sx_dpt_init_default_dev(dev);
        if (err) {
            sx_err(dev, "Failed initializing default device "
                   "attributes in the DPT, aborting.\n");
            goto out_free_priv;
        }
    }

    err = sx_cmd_init(dev);
    if (err) {
        sx_err(dev, "Failed initializing command interface, aborting.\n");
        goto out_free_priv;
    }

    spin_lock_init(&priv->profile.profile_lock);
    priv->profile.pci_profile_set = false;
    priv->profile.dev_profile_set = false;
    priv->profile.first_ib_swid = true;
    priv->dev_sw_rst_flow = false;
    spin_lock_init(&priv->ctx_lock);
    spin_lock_init(&priv->db_lock);
    INIT_LIST_HEAD(&priv->ctx_list);
    INIT_LIST_HEAD(&priv->dev_list);
    atomic_set(&priv->cq_backup_polling_refcnt, 0);
    atomic_set(&priv->dev_specific_cb_refcnt, 0);
    init_waitqueue_head(&priv->dev_specific_cb_not_in_use);
    priv->pause_cqn = -1;
    priv->force_iter_monitor_cq = -1;
    priv->force_iter_low_prio_cq = -1;
    priv->force_iter_high_prio_cq = -1;

    err = sx_bitmap_init(&priv->swid_bitmap, NUMBER_OF_SWIDS);
    if (err) {
        sx_err(dev, "Failed to initialize SWIDs bitmap, aborting.\n");
        goto out_free_priv;
    }

    __set_default_capabilities(dev);
    memset(&priv->stats, 0, sizeof(priv->stats));

    sx_core_ber_monitor_dev_init(dev);

    err = sx_health_check_dev_init(dev);
    if (err) {
        goto out_unregister;
    }

    if (sx_priv != NULL) {
        *sx_priv = priv;
    }

    return 0;

out_unregister:
    sx_core_ber_monitor_dev_deinit(dev);

out_free_priv:
    if (priv->listeners_and_rf_db.info) {
        kfree(priv->listeners_and_rf_db.info);
        priv->listeners_and_rf_db.info = NULL;
    }

    vfree(priv);

out:
    return err;
}

void sx_core_remove_one(struct sx_priv *priv, bool keep_listeners)
{
    struct sx_dev *dev = &priv->dev;

    if (priv->registered) {
        sx_core_unregister_device(dev);
        priv->registered = false;
    }

    sx_core_ber_monitor_dev_deinit(dev);
    sx_dpt_remove_dev(dev->device_id, 1);
    sx_core_dev_deinit_switchx_cb(dev);

    if (priv->listeners_and_rf_db.info && !keep_listeners) {
        kfree(priv->listeners_and_rf_db.info);
        priv->listeners_and_rf_db.info = NULL;
    }

    vfree(priv);
}

static struct sx_priv * __create_dummy_device(int chip_type, struct pci_dev *pdev)
{
    struct sx_priv *priv = NULL;
    int             ret = 0;

    if (chip_type == 0) {
        printk(KERN_ERR PFX "Chip type is not defined for device.\n");
        goto out;
    }

    ret = sx_core_init_one(&priv, NULL);
    if (ret) {
        printk(KERN_ERR PFX "Couldn't initialize the device. Aborting...\n");
        goto out;
    }

    ret = sx_core_dev_init_switchx_cb(&priv->dev, chip_type, 0);
    if (ret) {
        printk(KERN_ERR PFX "callback dev init failed for device (%u)\n",
               priv->profile.pci_profile.dev_id);
        goto out_remove_one;
    }

    ret = sx_dev_db_add_device(&priv->dev); /* also allocated the device ID */
    if (ret) {
        goto out_remove_one;
    }

    ret = sx_dpt_init_dev_pci(&priv->dev);
    if (ret) {
        goto out_remove_device;
    }

    ret = sx_core_register_device(&priv->dev);
    if (ret) {
        printk(KERN_ERR "Failed to register the device, aborting.\n");
        goto out_remove_device;
    }

    priv->registered = true;

    if (pdev) {
        priv->dev.pdev = pdev;
        pci_set_drvdata(pdev, &priv->dev);
    }

    return priv;

out_remove_device:
    sx_dev_db_remove_device(&priv->dev);

out_remove_one:
    sx_core_remove_one(priv, false);

out:
    return NULL;
}

static void __remove_dummy_device(struct sx_priv *priv)
{
    if (priv->dev.pdev) {
        pci_set_drvdata(priv->dev.pdev, NULL);
        priv->dev.pdev = NULL;
    }

    if (priv->registered) {
        sx_core_unregister_device(&priv->dev);
        priv->registered = false;
    }

    sx_dev_db_remove_device(&priv->dev);
    sx_core_remove_one(priv, false);
}

/*
 * when does the driver create a fake device:
 * 1. when a problem occurs and there is no PCI device detected on the bus.
 * 2. on OOB system.
 */
int sx_core_create_fake_device(struct sx_priv **priv_pp)
{
    struct sx_priv *priv = NULL;

    printk(KERN_INFO "creating fake device\n");

    if (g_chip_type == 0) {
        printk(KERN_ERR PFX "Chip type is not defined for device.\n");
        return -EINVAL;
    }

    priv = __create_dummy_device(g_chip_type, NULL);
    if (!priv) {
        return -EFAULT;
    }

    sx_glb.fake_dev = &priv->dev;
    *priv_pp = priv;
    return 0;
}

void sx_core_remove_fake_device(struct sx_priv *priv)
{
    __remove_dummy_device(priv);
    sx_glb.fake_dev = NULL;
}

bool sx_core_fw_is_faulty(struct sx_dev *dev)
{
    return (sx_priv(dev)->dev_info.dev_info_ro.fw_boot_status != SXD_FW_BOOT_STATUS_OK_E);
}
