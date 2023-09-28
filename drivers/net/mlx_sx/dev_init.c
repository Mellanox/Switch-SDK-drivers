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
#include <linux/delay.h>
#include <linux/vmalloc.h>

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

/****************************************************************************************
 * forward declaration of static symbols
 ***************************************************************************************/

struct pci_restart_saved_params {
    sxd_dev_id_t                  dev_id;
    struct listeners_and_rf_info *listeners;
    struct kobject               *kobj[SX_KOBJECT_MAX + 1];
    struct module_sysfs_node     *module_eeprom_arr;
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

/****************************************************************************************
 * STATIC VARIABLES
 ***************************************************************************************/

/* in use by probe function. must be accessed within pci_restart_lock! */
static struct sx_pci_probe_params {
    bool do_reset;
    u32  total_probes;
    u32  successful_probes;
    u32  total_removes;
    bool is_oob;
} __probe_params;

/****************************************************************************************
 * core PCI driver structures
 ***************************************************************************************/
static struct pci_device_id __sx_pci_table[] = {
    /* Spectrum PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM_PCI_DEV_ID) },

    /* Spectrum2 PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM2_PCI_DEV_ID) },

    /* Spectrum3 PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM3_PCI_DEV_ID) },

    /* Spectrum4 PCI device ID */
    { PCI_VDEVICE(MELLANOX, SPECTRUM4_PCI_DEV_ID) },

    /* SwitchIB PCI device ID */
    { PCI_VDEVICE(MELLANOX, SWITCH_IB_PCI_DEV_ID) },

    /* SwitchIB2 PCI device ID */
    { PCI_VDEVICE(MELLANOX, SWITCH_IB2_PCI_DEV_ID) },

    /* Quantum PCI device ID */
    { PCI_VDEVICE(MELLANOX, QUANTUM_PCI_DEV_ID) },

    /* Quantum2 PCI device ID */
    { PCI_VDEVICE(MELLANOX, QUANTUM2_PCI_DEV_ID) },

    /* Quantum3 PCI device ID */
    { PCI_VDEVICE(MELLANOX, QUANTUM3_PCI_DEV_ID) },

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

    printk(KERN_DEBUG "%s(): map cr_space area p:0x%llx, size:%d, cr_space start:%p \n",
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
            printk(KERN_DEBUG PFX "Failed enabling MSI-X interrupts. "
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

static int __sx_init_board(struct sx_dev *dev)
{
    struct sx_priv            *priv = sx_priv(dev);
    int                        err;
    struct ku_query_board_info board;
    struct ku_access_mgir_reg  reg_data;
    int                        retry_num = 0;

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
        reg_data.op_tlv.method = 1; /* Query */
        reg_data.op_tlv.op_class = 1;
        reg_data.op_tlv.tid = 0;

        err = sx_ACCESS_REG_MGIR(dev, &reg_data);
        /* Only if we managed to read MGIR successfully we check the HW revision
         * to see it's not A0 */
        if (!err && !reg_data.op_tlv.status &&
            (reg_data.mgir_reg.hw_info.device_id == SXD_MGIR_HW_DEV_ID_SX) &&
            (reg_data.mgir_reg.hw_info.device_hw_revision == SXD_MGIR_HW_REV_ID_A0)) {
            printk(KERN_ERR PFX "The SwitchX device revision is A0, "
                   "and therefore it is not supported by SX driver\n");
            return -EFAULT;
        }

        if (reg_data.mgir_reg.hw_info.device_id != 0) {
            break;
        }

        msleep(500 * retry_num);
        retry_num++;
    }

    chip_info_type = reg_data.mgir_reg.hw_info.device_id;
    chip_info_revision = reg_data.mgir_reg.hw_info.device_hw_revision;
    strncpy(chip_info_psid, (const char*)reg_data.mgir_reg.fw_info.psid, sizeof(chip_info_psid) - 1);

    err = __sx_core_init_cb(dev, reg_data.mgir_reg.hw_info.device_id,
                            reg_data.mgir_reg.hw_info.device_hw_revision);
    if (err) {
        printk(KERN_ERR PFX "callback dev init failed for device (%u)\n",
               priv->profile.pci_profile.dev_id);
        return err;
    }

    err = sx_QUERY_FW(dev, NULL);
    if (err) {
        sx_err(dev, "QUERY_FW command failed, aborting.\n");
        return err;
    }

    /* init local mailboxes */
    err = sx_QUERY_FW_2(dev, dev->device_id, false);
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

    printk(KERN_DEBUG "%s(): bar: %d dev->db_base phys: 0x%llx , doorbell base: %p \n",
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

static int __pci_probe_common(struct pci_dev                  *pdev,
                              const struct pci_device_id      *id,
                              struct sx_dev                  **new_dev,
                              struct pci_restart_saved_params *saved_params)
{
    struct sx_priv *priv = NULL;
    struct sx_dev  *dev = NULL;
    int             err = 0;

    /* at this point 'pci_restart_lock' must be acquired (write lock)! */
    BUG_ON(!rwsem_is_locked(&sx_glb.pci_restart_lock));

    __probe_params.total_probes++;

    printk(KERN_INFO PFX "Probe %s(%d) device %u\n", __FUNCTION__, __LINE__, \
           pdev->device);
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
    err = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
    if (err) {
        dev_warn(&pdev->dev, "Warning: couldn't set 64-bit PCI "
                 "DMA mask.\n");
        err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
        if (err) {
            dev_err(&pdev->dev, "Can't set PCI DMA mask, aborting.\n");
            goto err_release_bar0;
        }
    }

    err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
    if (err) {
        dev_warn(&pdev->dev, "Warning: couldn't set 64-bit "
                 "consistent PCI DMA mask.\n");
        err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
        if (err) {
            dev_err(&pdev->dev, "Can't set consistent PCI DMA "
                    "mask, aborting.\n");
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

#if defined(PD_BU)
    printk(KERN_INFO PFX "Performing SW reset is SKIPPED in PD mode.\n");
#else
    err = sx_reset(dev, __probe_params.do_reset);
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

        err = sx_sysfs_asic_init_tempeature(dev);
        if (err) {
            sx_err(dev, "Failed to initialize temperature monitoring\n");
            goto out_temperature_failed;
        }
    }

    __probe_params.successful_probes++;
    priv->created_on_pci_probe = true;

    if (__probe_params.do_reset) {
        /* udev event for system management purpose (only if chip was reset or warm_boot) */
        kobject_uevent(&pdev->dev.kobj, KOBJ_ADD);
        priv->kobj_add_done = true;
    }

    if (new_dev) {
        *new_dev = dev;
    }

    if (saved_params) {
        dev->device_id = saved_params->dev_id;
        sx_dpt_init_dev_pci(dev);
    }

    err = sx_core_register_device(dev);
    if (err) {
        sx_err(dev, "Failed to register the device, aborting.\n");
        goto out_register_failed;
    }

    priv->registered = true;

    return 0;

out_register_failed:
    sx_core_cr_dump_deinit(priv);

out_temperature_failed:
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

    sx_sysfs_asic_remove(dev);

    /* must be called before any CQ/DQ shutdown so there will be no race with the
     * asynchronous health-check mechanism
     */
    sx_health_check_dev_deinit(dev);

    priv = sx_priv(dev);

    pci_set_drvdata(pdev, NULL);

    if (priv->kobj_add_done) {
        /* udev event for system management purpose (only if chip was reset enable or warm boot) */
        kobject_uevent(&pdev->dev.kobj, KOBJ_REMOVE);
        priv->kobj_add_done = false;
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

    printk(KERN_DEBUG PFX "Shutdown PCI driver\n");

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

    if (__probe_params.total_probes != __probe_params.successful_probes) {
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
    struct pci_dev                 *pdev = NULL;
    struct pci_restart_saved_params saved_params;
    int                             err = 0;

    printk(KERN_INFO "RESTART PCI DEVICE %u\n", dev->device_id);

    if (!dev->pdev) {
        printk(KERN_ERR PFX "sx_restart_one_pci error: dev or pdev are NULL, exit \n");
        return -ENODEV;
    }

    /* save old device's information for the new device */
    memset(&saved_params, 0, sizeof(saved_params));
    saved_params.dev_id = dev->device_id;
    saved_params.listeners = sx_priv(dev)->listeners_and_rf_db.info;
    memcpy(saved_params.kobj, sx_priv(dev)->kobj, sizeof(saved_params.kobj)); /* save sysfs info */
    saved_params.module_eeprom_arr = sx_priv(dev)->module_eeprom_arr; /* save module eeprom sysfs info */

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

    spin_lock_init(&priv->listeners_and_rf_db.lock);
    if (saved_params) {
        priv->listeners_and_rf_db.info = saved_params->listeners;
        priv->module_eeprom_arr = saved_params->module_eeprom_arr;
        memcpy(&priv->kobj, saved_params->kobj, sizeof(priv->kobj));
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

    mutex_init(&priv->module_access_mutex);

    for (i = 0; i < MAX_MONITOR_RDQ_NUM; i++) {
        priv->monitor_rdqs_arr[i] = RDQ_INVALID_ID;
    }

    if (!sx_core_has_predefined_devices()) { /* no default device when there are predefined devices */
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
    sx_core_cr_dump_deinit(priv);

    sx_dpt_remove_dev(dev->device_id, 1);

    sx_core_dev_deinit_switchx_cb(dev);


    if (priv->listeners_and_rf_db.info && !keep_listeners) {
        kfree(priv->listeners_and_rf_db.info);
        priv->listeners_and_rf_db.info = NULL;
    }

    vfree(priv);
}

/*
 * when does the driver create a fake device:
 * 1. when a problem occurs and there is no PCI device detected on the bus.
 * 2. on OOB system.
 */
int sx_core_create_fake_device(struct sx_priv **priv_pp)
{
    struct sx_priv *priv = NULL;
    int             ret = 0;

    printk(KERN_INFO "creating fake device\n");

    if (g_chip_type == 0) {
        printk(KERN_ERR PFX "Chip type is not defined for device.\n");
        ret = -EINVAL;
        goto out;
    }

    ret = sx_core_init_one(&priv, NULL);
    if (ret) {
        printk(KERN_ERR PFX "Couldn't initialize the device. Aborting...\n");
        goto out;
    }

    ret = sx_core_dev_init_switchx_cb(&priv->dev, g_chip_type, 0);
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
    sx_glb.fake_dev = &priv->dev;
    *priv_pp = priv;
    return 0;

out_remove_device:
    sx_dev_db_remove_device(&priv->dev);

out_remove_one:
    sx_core_remove_one(priv, false);

out:
    return ret;
}
