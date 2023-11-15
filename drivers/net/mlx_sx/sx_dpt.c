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

#include <linux/skbuff.h>
#include <linux/pci.h>
#include <linux/kernel.h>
#include <linux/if_ether.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/driver.h>
#include <linux/rwlock_types.h>
#include "sx_dpt.h"
#include "sx.h"
#include "dq.h"
#include "fw.h"
#include "sx_dbg_dump_proc.h"
#include "sgmii.h"
#include "dev_db.h"

#define DEFAULT_I2C_DEV_ID (0x248) /* arbitrary value */
#define MAX_I2C_RETRIES    1

extern int tx_debug;

#include <linux/module.h>
#include <linux/mlx_sx/sx_i2c_if.h>

#ifdef SX_DEBUG
#define DPRINTK(fmt, args ...)                                     \
    do {                                                           \
        printk(KERN_ERR DRV_NAME " [%s: %s() line %d]: " fmt "\n", \
               __FILE__, __func__, __LINE__, ## args);             \
    } while (0)
#else
#define DPRINTK(fmt, args ...) \
    do {} while (0)
#endif

#define ENTER_FUNC() DPRINTK("ENTER {");
#define EXIT_FUNC()  DPRINTK("EXIT }");

#define PRINTK_ERR(fmt, args ...)                    \
    do {                                             \
        printk(KERN_ERR DRV_NAME fmt "\n", ## args); \
    } while (0)

typedef enum cr_access_method {
    CR_ACCESS_METHOD_READ = 1,
    CR_ACCESS_METHOD_WRITE,
    CR_ACCESS_METHOD_MIN = CR_ACCESS_METHOD_READ,
    CR_ACCESS_METHOD_MAX = CR_ACCESS_METHOD_WRITE,
} cr_access_method;

static const char * __dpt_type2str(int type)
{
    static char *type2str[] = {
        [DPT_PATH_INVALID] = "NONE",
        [DPT_PATH_I2C] = "I2C",
        [DPT_PATH_SGMII] = "SGMII",
        [DPT_PATH_PCI_E] = "PCIE",
        [DPT_PATH_MST] = "MST"
    };

    if ((type < DPT_PATH_MIN) || (type > DPT_PATH_MAX)) {
        return "N/A";
    }

    return type2str[type];
};


static int __cr_pcie_access(int              dev_id,
                            unsigned int     address,
                            unsigned char   *buf,
                            int              size,
                            cr_access_method access_method);

/**
 *
 * @param sx_dev
 * @param is_default
 * @return
 */
int sx_dpt_init_default_dev(struct sx_dev *sx_dev)
{
    union ku_dpt_path_info path_data;
    int                    err = 0;
    int                    cmd_path = (sx_mst_mode()) ? DPT_PATH_MST : DPT_PATH_I2C;
    const char            *cmd_path_str = (cmd_path == DPT_PATH_MST) ? "MST" : "I2C";

    memset(&path_data, 0, sizeof(path_data));

    if (cmd_path == DPT_PATH_I2C) {
        path_data.sx_i2c_info.sx_i2c_dev = DEFAULT_I2C_DEV_ID;
    }

    err = sx_dpt_add_dev_path(DEFAULT_DEVICE_ID, cmd_path, path_data, 1);
    if (err) {
        sx_err(sx_dev, "Failed adding %s path to the default device\n", cmd_path_str);
        return err;
    }

    err = sx_dpt_set_emad_path(DEFAULT_DEVICE_ID, cmd_path);
    if (err) {
        sx_err(sx_dev, "Failed setting EMAD path to %s\n", cmd_path_str);
        return err;
    }

    err = sx_dpt_set_mad_path(DEFAULT_DEVICE_ID, cmd_path);
    if (err) {
        sx_err(sx_dev, "Failed setting MAD path to %s\n", cmd_path_str);
        return err;
    }

    err = sx_dpt_set_cmd_path(DEFAULT_DEVICE_ID, cmd_path);
    if (err) {
        sx_err(sx_dev, "Failed setting command-interface path to %s\n", cmd_path_str);
        return err;
    }

    err = sx_dpt_set_cr_access_path(DEFAULT_DEVICE_ID, cmd_path);
    if (err) {
        sx_err(sx_dev, "Failed setting CR access path to %s\n", cmd_path_str);
        return err;
    }

    return 0;
}

int sx_dpt_init_dev_pci(struct sx_dev *sx_dev)
{
    union ku_dpt_path_info path_data;
    int                    dev_id = sx_dev->device_id;
    int                    err;

    printk(KERN_NOTICE "Called PCI DPT initialize with device_id: %d \n", dev_id);
    err = sx_dpt_add_dev_path(dev_id, DPT_PATH_PCI_E, path_data, 1);
    if (err) {
        sx_err(sx_dev, "Failed adding PCI path to the default device\n");
        return err;
    }

    sx_dpt_set_cmd_path(dev_id, DPT_PATH_PCI_E);
    sx_dpt_set_emad_path(dev_id, DPT_PATH_PCI_E);
    sx_dpt_set_mad_path(dev_id, DPT_PATH_PCI_E);
    sx_dpt_set_cr_access_path(dev_id, DPT_PATH_PCI_E);
    return 0;
}


static int __dpt_dump_handler(struct seq_file *m, void *v, void *context)
{
    const struct sx_dpt_info *info;
    struct sx_dev            *dev = sx_dbg_dump_get_device(m);
    int                       dev_id, first_dev = 0, last_dev = MAX_NUM_OF_REMOTE_SWITCHES;

    if (sx_core_has_predefined_devices()) {
        if (!dev) {
            return 0;
        }
        /* In a multi asic system, we will iterate on one device only -
         * the device that is associated with the proc file (dev_id) */
        dev_id = dev->device_id;
        first_dev = dev_id;
        last_dev = dev_id + 1;
    }

    seq_printf(m, "--------------------------------------------\n");
    seq_printf(m, "%-6s   %-7s   %-5s   %-5s   %-9s\n",
               "dev-id", "cmd-ifc", "emad ", "mad  ", "cr-access");
    seq_printf(m, "--------------------------------------------\n");

    for (dev_id = first_dev; dev_id < last_dev; dev_id++) {
        info = &sx_glb.sx_dpt.dpt_info[dev_id];

        if (!sx_dpt_is_valid(dev_id)) {
            continue;
        }

        seq_printf(m, "%-6d   %-7s   %-5s   %-5s   %-9s   \n",
                   dev_id,
                   __dpt_type2str(info->cmd_path),
                   __dpt_type2str(info->emad_path),
                   __dpt_type2str(info->mad_path),
                   __dpt_type2str(info->cr_access_path));
    }

    seq_printf(m, "\n");
    return 0;
}

static int sx_dpt_stub_mst_write(int offset, int len, u8 *buf)
{
    printk(KERN_ERR "MST interface is not attached [WRITE: offset=0x%x, len=%d]\n", offset, len);
    return 0;
}

static int sx_dpt_stub_mst_read(int offset, int len, u8 *buf)
{
    printk(KERN_ERR "MST interface is not attached [READ: offset=0x%x, len=%d]\n", offset, len);
    return 0;
}

int sx_dpt_init(void)
{
    int err = 0;
    int i;

    ENTER_FUNC();

    for (i = 0; i < MAX_NUM_OF_REMOTE_SWITCHES; i++) {
        sx_glb.sx_dpt.dpt_info[i].cmd_path = DPT_PATH_INVALID;
        sx_glb.sx_dpt.dpt_info[i].emad_path = DPT_PATH_INVALID;
        sx_glb.sx_dpt.dpt_info[i].mad_path = DPT_PATH_INVALID;
        sx_glb.sx_dpt.dpt_info[i].cr_access_path = DPT_PATH_INVALID;

        memset(sx_glb.sx_dpt.dpt_info[i].is_ifc_valid, 0,
               sizeof(sx_glb.sx_dpt.dpt_info[i].is_ifc_valid));
    }
    sx_glb.sx_i2c.read = sx_dpt_stub_i2c_read;
    sx_glb.sx_i2c.write = sx_dpt_stub_i2c_write;
    sx_glb.sx_i2c.read_dword = sx_dpt_stub_i2c_read_dword;
    sx_glb.sx_i2c.write_dword = sx_dpt_stub_i2c_write_dword;
    sx_glb.sx_i2c.enforce = sx_dpt_stub_i2c_enforce;
    sx_glb.sx_i2c.release = sx_dpt_stub_i2c_release;
    sx_glb.sx_i2c.get_fw_rev = NULL;
    sx_glb.sx_i2c.set_go_bit_stuck = NULL;

    sx_glb.sx_mst.write = sx_dpt_stub_mst_write;
    sx_glb.sx_mst.read = sx_dpt_stub_mst_read;

    EXIT_FUNC();
    return err;
}

bool sx_dpt_is_valid(int sx_dev_id)
{
    const struct sx_dpt_info *info = &sx_glb.sx_dpt.dpt_info[sx_dev_id];
    int                       i;

    for (i = 0; i < sizeof(info->is_ifc_valid) / sizeof(info->is_ifc_valid[0]); i++) {
        if (info->is_ifc_valid[i]) {
            return true;
        }
    }

    return false;
}

bool sx_dpt_is_path_valid(int sx_dev_id, enum  ku_dpt_path_type path)
{
    return sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[path];
}

/*
 * This function will add path to entry dev_id in DPT. The path
 * should be provided with remote device description. For
 * example , if added path is I2C than path_data should be
 * i2c_dev_id.
 */
int sx_dpt_add_dev_path(int sx_dev_id, enum ku_dpt_path_type path, union ku_dpt_path_info path_data, uint8_t is_local)
{
    int err = 0;

    ENTER_FUNC();

    if (sx_i2c_mode() && (path != DPT_PATH_I2C)) {
        printk(KERN_NOTICE "*** In I2C configuration, device set to use %s but will use I2C! ***\n",
               __dpt_type2str(path));
        path = DPT_PATH_I2C;
        memset(&path_data, 0, sizeof(path_data));
        path_data.sx_i2c_info.sx_i2c_dev = DEFAULT_I2C_DEV_ID;
    }

    if (sx_mst_mode() && (path != DPT_PATH_MST)) {
        printk(KERN_NOTICE "*** In MST configuration, device set to use %s but will use MST! ***\n",
               __dpt_type2str(path));
        path = DPT_PATH_MST;
        memset(&path_data, 0, sizeof(path_data));
    }

    switch (path) {
    case DPT_PATH_I2C:
        if (sx_glb.sx_i2c.is_registered == 0) {
            sx_dpt_reg_i2c_ifc(&sx_glb.sx_i2c);
            sx_glb.sx_i2c.is_registered = 1;
        }

        sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_i2c_info = path_data.sx_i2c_info;
        sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_I2C] = true;
        if (sx_glb.sx_i2c.get_local_mbox) {
            sx_glb.sx_i2c.get_local_mbox(
                path_data.sx_i2c_info.sx_i2c_dev,
                /* HCR2 is used for I2C commands, while HCR1 is used for PCI commands*/
                &sx_glb.sx_dpt.dpt_info[sx_dev_id].in_mb_size[HCR2],
                &sx_glb.sx_dpt.dpt_info[sx_dev_id].in_mb_offset[HCR2],
                &sx_glb.sx_dpt.dpt_info[sx_dev_id].out_mb_size[HCR2],
                &sx_glb.sx_dpt.dpt_info[sx_dev_id].out_mb_offset[HCR2]);

            printk(
                KERN_NOTICE "I2C (dev %d): In-Mailbox [offset=0x%x, size=0x%x], Out-Mailbox [offset=0x%x, size=0x%x]\n",
                sx_dev_id,
                sx_glb.sx_dpt.dpt_info[sx_dev_id].in_mb_offset[HCR2],
                sx_glb.sx_dpt.dpt_info[sx_dev_id].in_mb_size[HCR2],
                sx_glb.sx_dpt.dpt_info[sx_dev_id].out_mb_offset[HCR2],
                sx_glb.sx_dpt.dpt_info[sx_dev_id].out_mb_size[HCR2]);
        }
        if (!is_local && sx_glb.sx_i2c.get_fw_rev) {
            err = sx_glb.sx_i2c.enforce(path_data.sx_i2c_info.sx_i2c_dev);
            if (err) {
                PRINTK_ERR("I2C bus %d of device %d is not ready. "
                           "query_fw will not be performed. err=%d\n",
                           path_data.sx_i2c_info.sx_i2c_dev, sx_dev_id, err);
                err = -EBUSY;
                break;
            }

            sx_glb.sx_i2c.get_fw_rev(path_data.sx_i2c_info.sx_i2c_dev,
                                     &sx_glb.sx_dpt.dpt_info[sx_dev_id].fw_rev);
            err = sx_glb.sx_i2c.release(path_data.sx_i2c_info.sx_i2c_dev);
            if (err) {
                PRINTK_ERR("I2C bus %d of device %d is not ready. "
                           "i2c release failed. err=%d\n",
                           path_data.sx_i2c_info.sx_i2c_dev, sx_dev_id, err);
                err = -EBUSY;
                break;
            }
        }
        sx_glb.sx_dpt.dpt_info[sx_dev_id].is_local[DPT_PATH_I2C] = is_local;
        if (sx_cr_mode() && is_local) {
            err = sx_dev_db_reassign_dev_id_to_default_device(sx_dev_id);
            if (err) {
                printk(KERN_ERR "Failed to reassign default device with dev_id %u\n", sx_dev_id);
            }
        }

        break;

    case DPT_PATH_SGMII:
        if (!is_sgmii_supported()) {
            printk(KERN_ERR "SGMII is disabled\n");
            err = -EPERM;
            break;
        }

        if (sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_SGMII]) {
            printk(KERN_NOTICE "SGMII path for dev %d is already set\n", sx_dev_id);
            err = -EEXIST;
            break;
        }

        err = sgmii_dev_add(sx_dev_id, &path_data.sx_sgmii_info);
        if (err) {
            printk(KERN_ERR "Failed to add SGMII information to 'sgmii_info_to_dev_id' database (err=%d)\n", err);
            break;
        }

        memcpy(&sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_sgmii_info,
               &path_data.sx_sgmii_info,
               sizeof(sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_sgmii_info));

        sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_SGMII] = 1;
        sx_glb.sx_dpt.dpt_info[sx_dev_id].is_local[DPT_PATH_SGMII] = is_local;
        break;

    case DPT_PATH_PCI_E:
        sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_PCI_E] = true;
        sx_glb.sx_dpt.dpt_info[sx_dev_id].is_local[DPT_PATH_PCI_E] = is_local;
        if (is_local) {
            err = sx_dev_db_reassign_dev_id_to_default_device(sx_dev_id);
            if (err) {
                printk(KERN_ERR "Failed to reassign default device with dev_id %u\n", sx_dev_id);
            }
        }
        break;

    case DPT_PATH_MST:
        if (!sx_glb.sx_mst.is_registered) {
            sx_dpt_reg_mst_ifc(&sx_glb.sx_mst);
            sx_glb.sx_mst.is_registered = 1;
        }

        sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_MST] = true;
        sx_glb.sx_dpt.dpt_info[sx_dev_id].is_local[DPT_PATH_MST] = is_local;
        if (is_local) {
            err = sx_dev_db_reassign_dev_id_to_default_device(sx_dev_id);
            if (err) {
                printk(KERN_ERR "Failed to reassign default device with dev_id %u\n", sx_dev_id);
            }

            memcpy(&sx_glb.sx_dpt.dpt_info[sx_dev_id],
                   &sx_glb.sx_dpt.dpt_info[DEFAULT_DEVICE_ID],
                   sizeof(sx_glb.sx_dpt.dpt_info[sx_dev_id]));
        }

        break;

    default:
        PRINTK_ERR("Try to set invalid path to sx_dev_id: %d, dpt_path: %s\n",
                   sx_dev_id, __dpt_type2str(path));
        err = -EINVAL;
        break;
    }

    if (!err) {
        printk(KERN_INFO PFX "Successfully added path %s to device %d\n",
               __dpt_type2str(path), sx_dev_id);
    }

    EXIT_FUNC();
    return err;
}

/**
 * This function with params dev_id and path will invalidate the
 * given "path" at index DEV_ID in DPT. All other paths will
 * remains without changes.
 */
int sx_dpt_remove_dev_path(int sx_dev_id, enum ku_dpt_path_type path)
{
    int err = 0;

    ENTER_FUNC();

    if (sx_glb.sx_dpt.dpt_info[sx_dev_id].cmd_path == path) {
        PRINTK_ERR("Can't remove path because %d "
                   "is current active cmd_path.\n", path);
        return -EINVAL;
    }

    if (sx_glb.sx_dpt.dpt_info[sx_dev_id].emad_path == path) {
        PRINTK_ERR("Can't remove path because %d "
                   "is current active emad_path.\n", path);
        return -EINVAL;
    }

    if (sx_glb.sx_dpt.dpt_info[sx_dev_id].mad_path == path) {
        PRINTK_ERR("Can't remove path because %d "
                   "is current active mad_path.\n", path);
        return -EINVAL;
    }

    if (sx_glb.sx_dpt.dpt_info[sx_dev_id].cr_access_path == path) {
        PRINTK_ERR("Can't remove path because %d "
                   "is current active cr_access_path.\n", path);
        return -EINVAL;
    }

    switch (path) {
    case DPT_PATH_I2C:
        sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_I2C] =
            false;
        memset(&sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_i2c_info, 0,
               sizeof(sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_i2c_info));
        break;

    case DPT_PATH_SGMII:
        if (!is_sgmii_supported()) {
            printk(KERN_ERR "SGMII is disabled\n");
            err = -EPERM;
            break;
        }

        err = sgmii_dev_del(sx_dev_id);
        if (err) {
            PRINTK_ERR("Failed to del SGMII information from 'sgmii_info_to_dev_id' database (err=%d)\n", err);
            break;
        }

        sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_SGMII] = 0;
        memset(&sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_sgmii_info,
               0,
               sizeof(sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_sgmii_info));
        break;

    case DPT_PATH_PCI_E:
        sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_PCI_E]
            = false;
        /* coverity[bad_memset] */
        memset(&sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_pcie_info, 0,
               sizeof(sx_glb.sx_dpt.dpt_info[sx_dev_id].
                      sx_pcie_info));
        break;

    default:
        PRINTK_ERR("Invalid path.\n");
        err = -EINVAL;
    }

    if (!err) {
        printk(KERN_INFO PFX "Successfully removed path %s from device %d\n",
               __dpt_type2str(path), sx_dev_id);
    }

    EXIT_FUNC();
    return err;
}

/**
 * This function with params dev_id and path will invalidate all paths
 * at index DEV_ID in DPT.
 */
void __sx_dpt_remove_dev(int sx_dev_id)
{
    ENTER_FUNC();
    pr_debug("%s() Remove dev %d \n", __func__, sx_dev_id);

    if (sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_SGMII]) {
        if (sgmii_dev_del(sx_dev_id) != 0) {
            return; /* something went wrong */
        }

        sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_SGMII] = 0;
    }

    sx_glb.sx_dpt.dpt_info[sx_dev_id].cmd_path = DPT_PATH_INVALID;
    sx_glb.sx_dpt.dpt_info[sx_dev_id].emad_path = DPT_PATH_INVALID;
    sx_glb.sx_dpt.dpt_info[sx_dev_id].mad_path = DPT_PATH_INVALID;
    sx_glb.sx_dpt.dpt_info[sx_dev_id].cr_access_path = DPT_PATH_INVALID;

    sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_I2C] = false;
    sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_PCI_E] = false;

    memset(&sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_i2c_info, 0,
           sizeof(sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_i2c_info));
    /* coverity[bad_memset] */
    memset(&sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_pcie_info, 0,
           sizeof(sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_pcie_info));
    memset(&sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_sgmii_info, 0,
           sizeof(sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_sgmii_info));

    printk(KERN_INFO PFX "Successfully removed device %d from the DPT\n", sx_dev_id);
    EXIT_FUNC();
}

int sx_dpt_is_dev_pci_attached(int sx_dev_id)
{
    if (sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_PCI_E] &&
        (sx_glb.sx_dpt.dpt_info[sx_dev_id].cmd_path == DPT_PATH_PCI_E)) {
        return 1;
    }

    return 0;
}

int sx_dpt_remove_dev(int sx_dev_id, int restart_flow)
{
    int   err = 0;
    void *sx_dev = NULL;
    void *def_sx_dev = NULL;

    if (sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_PCI_E]) {
        sx_dev = sx_dev_db_get_dev_by_id(sx_dev_id);
    }

    if (sx_glb.sx_dpt.dpt_info[DEFAULT_DEVICE_ID].is_ifc_valid[DPT_PATH_PCI_E]) {
        def_sx_dev = sx_dev_db_get_default_device();
    }

    /*
     * if the removed device is PCI (CMD_PATH=PCI) and
     * the it is the same as default device then remove default device too
     */
    if ((sx_glb.sx_dpt.dpt_info[sx_dev_id].cmd_path == DPT_PATH_PCI_E) &&
        (sx_dev == def_sx_dev) && restart_flow) {
        __sx_dpt_remove_dev(DEFAULT_DEVICE_ID);
    }

    __sx_dpt_remove_dev(sx_dev_id);

    return err;
}

/**
 * This function is used to change dpt path : i2c , pci-e , sgmii
 * by changing the callbacks to appropriate interface functions
 * To validate if the change is succeeded need to make some
 * wr/rd to check if the new interface is working
 */
int sx_dpt_set_cmd_path(int sx_dev_id, enum  ku_dpt_path_type cmd_path)
{
    ENTER_FUNC();

    if (sx_i2c_mode() && (cmd_path != DPT_PATH_I2C)) {
        printk(
            KERN_NOTICE "*** In I2C configuration, device set to use %s for command-interface but will use I2C! ***\n",
            __dpt_type2str(cmd_path));
        cmd_path = DPT_PATH_I2C;
    }

    if (sx_mst_mode() && (cmd_path != DPT_PATH_MST)) {
        printk(
            KERN_NOTICE "*** In MST configuration, device set to use %s for command-interface but will use MST! ***\n",
            __dpt_type2str(cmd_path));
        cmd_path = DPT_PATH_MST;
    }

    if (sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[cmd_path] == false) {
        PRINTK_ERR("sx_dev_id:%d , path %d is not valid !\n", sx_dev_id, cmd_path);
        return -EINVAL;
    }

    /* change the paths */
    sx_glb.sx_dpt.dpt_info[sx_dev_id].cmd_path = cmd_path;

    EXIT_FUNC();
    return 0;
}

int sx_dpt_get_i2c_info(int sx_dev_id, struct ku_dpt_i2c_info** i2c_info)
{
    if ((i2c_info == NULL) || (sx_dev_id > MAX_NUM_OF_REMOTE_SWITCHES)) {
        return -EINVAL;
    }

    *i2c_info = &(sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_i2c_info);
    return 0;
}

int sx_dpt_get_cmd_path(int sx_dev_id)
{
    /* DEFAULT_DEVICE_ID is a WA for FW burn on local device
     * before device ID is known. Burning FW will be done through CMD IFC
     * over the PCI */
    if (!sx_cr_mode() && (sx_dev_id == DEFAULT_DEVICE_ID)) {
        return DPT_PATH_PCI_E;
    }

    return sx_glb.sx_dpt.dpt_info[sx_dev_id].cmd_path;
}

/**
 * This function is used to set the emad path in the dpt
 */
int sx_dpt_set_emad_path(int sx_dev_id, enum  ku_dpt_path_type emad_path)
{
    ENTER_FUNC();

    if (sx_i2c_mode() && (emad_path != DPT_PATH_I2C)) {
        printk(KERN_NOTICE "*** In I2C configuration, device set to use %s for EMAD but will use I2C! ***\n",
               __dpt_type2str(emad_path));
        emad_path = DPT_PATH_I2C;
    }

    if (sx_mst_mode() && (emad_path != DPT_PATH_MST)) {
        printk(KERN_NOTICE "*** In MST configuration, device set to use %s for EMAD but will use MST! ***\n",
               __dpt_type2str(emad_path));
        emad_path = DPT_PATH_MST;
    }

    if (!sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[emad_path]) {
        PRINTK_ERR("path %d is not valid !\n", emad_path);
        return -EINVAL;
    }

    /* change the paths */
    sx_glb.sx_dpt.dpt_info[sx_dev_id].emad_path = emad_path;

    EXIT_FUNC();
    return 0;
}

int sx_dpt_get_emad_path(int sx_dev_id)
{
    return sx_glb.sx_dpt.dpt_info[sx_dev_id].emad_path;
}

int sx_dpt_set_mad_path(int sx_dev_id, enum  ku_dpt_path_type mad_path)
{
    ENTER_FUNC();

    if ((sx_dev_id < 0) ||
        (sx_dev_id > MAX_NUM_OF_REMOTE_SWITCHES)) {
        PRINTK_ERR("Device id is not valid");
        return -EINVAL;
    }

    if ((mad_path < DPT_PATH_MIN) ||
        (mad_path > DPT_PATH_MAX)) {
        PRINTK_ERR("MAD path is not valid");
        return -EINVAL;
    }

    if (sx_i2c_mode() && (mad_path != DPT_PATH_I2C)) {
        printk(KERN_NOTICE "*** In I2C configuration, device set to use %s for MAD but will use I2C! ***\n",
               __dpt_type2str(mad_path));
        mad_path = DPT_PATH_I2C;
    }

    if (sx_mst_mode() && (mad_path != DPT_PATH_MST)) {
        printk(KERN_NOTICE "*** In MST configuration, device set to use %s for MAD but will use MST! ***\n",
               __dpt_type2str(mad_path));
        mad_path = DPT_PATH_MST;
    }

    if (!sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[mad_path]) {
        PRINTK_ERR("Path %d is not valid !\n", mad_path);
        return -EINVAL;
    }

    /* change the paths */
    sx_glb.sx_dpt.dpt_info[sx_dev_id].mad_path = mad_path;

    EXIT_FUNC();
    return 0;
}

int sx_dpt_set_cr_access_path(int sx_dev_id, enum ku_dpt_path_type cr_access_path)
{
    int err = 0;

    ENTER_FUNC();

    if ((sx_dev_id < 0) ||
        (sx_dev_id > MAX_NUM_OF_REMOTE_SWITCHES)) {
        PRINTK_ERR("Device id is not valid.\n");
        return -EINVAL;
    }

    if ((cr_access_path < DPT_PATH_MIN) ||
        (cr_access_path > DPT_PATH_MAX)) {
        PRINTK_ERR("CR_ACCESS path is not valid.\n");
        return -EINVAL;
    }

    if (sx_i2c_mode() && (cr_access_path != DPT_PATH_I2C)) {
        printk(KERN_NOTICE "*** In I2C configuration, device set to use %s for CR-Space but will use I2C! ***\n",
               __dpt_type2str(cr_access_path));
        cr_access_path = DPT_PATH_I2C;
    }

    if (sx_mst_mode() && (cr_access_path != DPT_PATH_MST)) {
        printk(KERN_NOTICE "*** In MST configuration, device set to use %s for CR-Space but will use MST! ***\n",
               __dpt_type2str(cr_access_path));
        cr_access_path = DPT_PATH_MST;
    }

    if (sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[cr_access_path] == false) {
        PRINTK_ERR("path %d is not valid !\n", cr_access_path);
        return -EINVAL;
    }

    /* change the path */
    sx_glb.sx_dpt.dpt_info[sx_dev_id].cr_access_path = cr_access_path;

    printk(KERN_INFO PFX "Successfully set CR_ACCESS path for device %d to %s\n",
           sx_dev_id, __dpt_type2str(cr_access_path));

    EXIT_FUNC();
    return err;
}

enum ku_dpt_path_type sx_dpt_get_cr_access_path(int sx_dev_id)
{
    return sx_glb.sx_dpt.dpt_info[sx_dev_id].cr_access_path;
}

/**
 * get HW etclass from device callback structure
 */
int sx_get_hw_etclass(struct isx_meta *meta, u8* hw_etclass)
{
    struct sx_dev *dev;
    int            err;

    dev = sx_dev_db_get_dev_by_id(meta->dev_id);
    if (!dev) {
        PRINTK_ERR("Invalid device id %d\n", meta->dev_id);
        return -EINVAL;
    }

    err = __sx_core_dev_specific_cb_get_reference(dev);
    if (err) {
        PRINTK_ERR("__sx_core_dev_specific_cb_get_reference failed for device id %d\n", meta->dev_id);
        return err;
    }

    if (sx_priv(dev)->dev_specific_cb.get_hw_etclass_cb != NULL) {
        sx_priv(dev)->dev_specific_cb.get_hw_etclass_cb(meta, hw_etclass);
    } else {
        *hw_etclass = meta->etclass;
    }
    __sx_core_dev_specific_cb_release_reference(dev);

    return 0;
}

int sx_get_sqd_num(struct sx_dev *dev, u8 swid, u8 etclass, u8 *sdq)
{
    int err = 0;

    if (dev && (sx_priv(dev)->dev_specific_cb.sx_get_sdq_num_cb != NULL)) {
        err = sx_priv(dev)->dev_specific_cb.sx_get_sdq_num_cb(dev, swid, etclass, sdq);
    } else {
        err = -EINVAL;
        printk(KERN_ERR PFX "Error retrieving sx_get_sdq_num_to_create_cb callback structure! err=[%d]\n", err);
        goto out;
    }

out:
    return err;
}

/**
 * callback structure for selecting SDQ based on condor and BAZ
 */
int sx_get_sdq(struct isx_meta *meta,
               struct sx_dev   *dev,
               enum ku_pkt_type type,
               u8               swid,
               u8               etclass,
               u8              *stclass,
               u8              *sdq,
               u8              *max_cpu_etclass_for_unlimited_mtu,
               u16             *cap_max_mtu_p)
{
    u8  hw_etclass = 0;
    int ret = 0;

    if (!dev) {
        PRINTK_ERR("get sdq: dev is NULL\n");
        return -EINVAL;
    }

    /* this func also take priv->db_lock */
    if (sx_get_hw_etclass(meta, &hw_etclass) != 0) {
        PRINTK_ERR("Error retrieving HW Etclass!\n");
        return -EINVAL;
    }

    ret = __sx_core_dev_specific_cb_get_reference(dev);
    if (ret) {
        PRINTK_ERR("__sx_core_dev_specific_cb_get_reference failed \n");
        return ret;
    }

    if (sx_priv(dev)->dev_specific_cb.max_cpu_etclass_for_unlimited_mtu != NULL) {
        *max_cpu_etclass_for_unlimited_mtu =
            sx_priv(dev)->dev_specific_cb.max_cpu_etclass_for_unlimited_mtu();
    } else {
        *max_cpu_etclass_for_unlimited_mtu = 1; /* default */
    }

    if (sx_priv(dev)->dev_specific_cb.cap_max_mtu_get_cb != NULL) {
        *cap_max_mtu_p = sx_priv(dev)->dev_specific_cb.cap_max_mtu_get_cb();
    } else {
        PRINTK_ERR("Error retrieving cap_max_mtu_get_cb callback structure!\n");
        ret = -EINVAL;
        goto out;
    }

    if (sx_priv(dev)->dev_specific_cb.sx_get_sdq_cb != NULL) {
        sx_priv(dev)->dev_specific_cb.sx_get_sdq_cb(dev, type, swid,
                                                    etclass, stclass, sdq);
    } else {
        PRINTK_ERR("Error retrieving sx_get_sdq_cb callback structure!\n");
        ret = -EINVAL;
        goto out;
    }

out:
    __sx_core_dev_specific_cb_release_reference(dev);

    return ret;
}

/**
 * callback structure for filling meta based on condor and BAZ
 */
int sx_build_isx_header(struct isx_meta *meta, struct sk_buff *skb, u8 stclass)
{
    struct sx_dev *dev = sx_dev_db_get_dev_by_id(meta->dev_id);
    u8             hw_etclass = 0;
    int            err = 0;

    if (!dev) {
        PRINTK_ERR("build isx header: dev is NULL\n");
        return -EINVAL;
    }

    /* this func also take priv->db_lock */
    if (sx_get_hw_etclass(meta, &hw_etclass) != 0) {
        PRINTK_ERR("Error retrieving HW Etclass!\n");
        return -EINVAL;
    }

    err = __sx_core_dev_specific_cb_get_reference(dev);
    if (err) {
        PRINTK_ERR("__sx_core_dev_specific_cb_get_reference failed for dev id %d \n", meta->dev_id);
        return err;
    }

    if (sx_priv(dev)->dev_specific_cb.sx_build_isx_header_cb != NULL) {
        sx_priv(dev)->dev_specific_cb.sx_build_isx_header_cb(meta, skb, stclass, hw_etclass);
    } else {
        PRINTK_ERR("Error retrieving sx_build_isx_header callback structure!\n");
        __sx_core_dev_specific_cb_release_reference(dev);
        return -EINVAL;
    }

    __sx_core_dev_specific_cb_release_reference(dev);
    return 0;
}

/**
 * This functions will send emads according emad_path defined in DPT : I2C,PCI,SGMII.
 */
int sx_dpt_send_emad(int sx_dev_id, struct sk_buff *skb, struct isx_meta *meta)
{
    int            err = 0;
    struct sx_dev *dev;

    ENTER_FUNC();

    DPRINTK(KERN_DEBUG "send emad to dev_id %d, skb: %p\n", sx_dev_id, skb);
    switch (sx_glb.sx_dpt.dpt_info[sx_dev_id].emad_path) {
    case DPT_PATH_I2C:
        PRINTK_ERR("Send emad over I2C isn't supported.\n");
        err = -EINVAL;
        sx_skb_free(skb);   /* drop packet flow, use kfree_skb */
        break;

    case DPT_PATH_SGMII:
        err = sgmii_send_emad(sx_dev_id, skb, meta);
        if (err) {
            sx_skb_free(skb);   /* drop packet flow, use kfree_skb */
        }
        break;

    case DPT_PATH_PCI_E:
        DPRINTK("Send emad over PCI-E.\n");
        dev = sx_dev_db_get_dev_by_id(sx_dev_id);
        sx_qos_emad_push_to_queue(dev, skb, meta, EMAD_PRIO_HIGH);
        break;

    default:
        PRINTK_ERR("dpt_info[%d].emad_path: %d is invalid\n",
                   sx_dev_id,
                   sx_glb.sx_dpt.dpt_info[sx_dev_id].emad_path);
        err = -EINVAL;
        sx_skb_free(skb);   /* drop packet flow, use kfree_skb */
        break;
    }

    EXIT_FUNC();
    return err;
}

/**
 * This functions will send mads according mad_path defined in DPT :
 * I2C,PCI,SGMII.
 */
int sx_dpt_send_mad(int sx_dev_id, struct sk_buff *skb, struct isx_meta *meta)
{
    int            err = 0;
    struct sx_dev *dev = sx_dev_db_get_dev_by_id(sx_dev_id);

    ENTER_FUNC();

    DPRINTK("send mad to dev_id %d, skb: %p\n", sx_dev_id, skb);
    switch (sx_glb.sx_dpt.dpt_info[sx_dev_id].mad_path) {
    case DPT_PATH_I2C:
        PRINTK_ERR("Send mad over I2C isn't supported.\n");
        err = -EINVAL;
        sx_skb_free(skb);   /* drop packet flow, use kfree_skb */
        break;

    case DPT_PATH_SGMII:
        err = sgmii_send_mad(sx_dev_id, skb, meta);
        break;

    case DPT_PATH_PCI_E:
        DPRINTK("Send mad over PCI-E\n");
        err = __sx_core_post_send(dev, skb, meta, DONT_FORCE_SDQ_ID);
        break;

    default:
        PRINTK_ERR("dpt_info[%d].mad_path: %d is INVALID !\n",
                   sx_dev_id,
                   sx_glb.sx_dpt.dpt_info[sx_dev_id].mad_path);
        err = -EINVAL;
        sx_skb_free(skb);   /* drop packet flow, use kfree_skb */
        break;
    }

    EXIT_FUNC();
    return err;
}

int sx_dpt_get_cmd_sx_dev_by_id(int sx_dev_id, struct sx_dev **dev)
{
    int ret = 0;

    ENTER_FUNC();

    *dev = NULL;
    if (sx_dev_id > MAX_NUM_OF_REMOTE_SWITCHES) {
        PRINTK_ERR("Device id is not valid\n");
        ret = -EINVAL;
        goto out;
    }

    if (sx_glb.sx_dpt.dpt_info[sx_dev_id].cmd_path == DPT_PATH_PCI_E) {
        if (sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_PCI_E] == true) {
            *dev = sx_dev_db_get_dev_by_id(sx_dev_id);
            if (!*dev) {
                PRINTK_ERR("PCIE path is configured but there is no PCI device\n");
                ret = -ENODEV;
            }
        } else {
            PRINTK_ERR("no PCIE path configured for dev_id %d\n", sx_dev_id);
            ret = -ENXIO;
            goto out;
        }
    } else {
        *dev = sx_dev_db_get_default_device();
        if (!*dev) {
            PRINTK_ERR("There is no device attached\n");
            ret = -ENODEV;
        }
    }

out:
    EXIT_FUNC();
    return ret;
}

int sx_dpt_get_i2c_dev_by_id(int sx_dev_id, int *i2c_dev)
{
    ENTER_FUNC();

    if (sx_glb.sx_dpt.dpt_info[sx_dev_id].is_ifc_valid[DPT_PATH_I2C] == false) {
        PRINTK_ERR("Path DPT_PATH_I2C is not valid.\n");
        *i2c_dev = 0;
        return -EINVAL;
    }

    *i2c_dev = sx_glb.sx_dpt.dpt_info[sx_dev_id].sx_i2c_info.sx_i2c_dev;

    EXIT_FUNC();

    return 0;
}

int sx_dpt_mst_writel(u32 offset, u32 value)
{
    sx_glb.sx_mst.write(offset, 4, (u8*)&value);
    return 0;
}

/**
 * reg - CR space address to write to
 * value - the value we want to write
 */
int sx_dpt_i2c_writel(int dev_id, u32 reg, u32 value)
{
    int err = 0;
    int i2c_dev_id;
    int i;

    ENTER_FUNC();
    err = sx_dpt_get_i2c_dev_by_id(dev_id, &i2c_dev_id);
    if (err) {
        PRINTK_ERR("sx_dpt_get_i2c_dev_by_id for dev_id: %d "
                   "failed !\n", dev_id);
        return -EINVAL;
    }

    DPRINTK("dev_id: 0x%x, i2c_dev: 0x%x, reg:0x%x, val: 0x%x\n",
            dev_id, i2c_dev_id, reg, value);

    for (i = 0; i < MAX_I2C_RETRIES; i++) {
        err = sx_glb.sx_i2c.write_dword(i2c_dev_id, reg, value);
        if (!err) {
            break;
        }
    }

    if (err) {
        printk(KERN_WARNING "sx_dpt_i2c_writel for dev_id: %d failed "
               "after %d tries!\n", dev_id, i);
        return -EINVAL;
    }

    EXIT_FUNC();
    return err;
}

int sx_dpt_mst_write_buf(u32 offset, u8 *buff, int size)
{
    sx_glb.sx_mst.write(offset, size, buff);
    return 0;
}

int sx_dpt_i2c_write_buf(int dev_id, unsigned int i2c_offset, unsigned char *buf, int size)
{
    int err = 0;
    int i2c_dev_id;
    int i;

    ENTER_FUNC();
    err = sx_dpt_get_i2c_dev_by_id(dev_id, &i2c_dev_id);
    if (err) {
        PRINTK_ERR("sx_dpt_get_i2c_dev_by_id for dev_id: "
                   "%d failed !\n", dev_id);
        return -EINVAL;
    }

    DPRINTK("dev_id: 0x%x, i2c_dev_id: 0x%x, i2c_offset:0x%x, buf: %p, "
            "size: %d\n", dev_id, i2c_dev_id,
            i2c_offset, buf, size);
    for (i = 0; i < MAX_I2C_RETRIES; i++) {
        err = sx_glb.sx_i2c.write(i2c_dev_id, i2c_offset, size, buf);
        if (!err) {
            break;
        }
    }

    if (err) {
        printk(KERN_ERR "sx_dpt_i2c_write_buf for dev_id: %d offset %u "
               "failed after %d tries! err: %d\n", dev_id, i2c_offset, i, err);
        return -EINVAL;
    }

    EXIT_FUNC();
    return err;
}

int sx_dpt_mst_read_buf(u32 offset, u8 *buff, int size)
{
    sx_glb.sx_mst.read(offset, size, buff);
    return 0;
}

int sx_dpt_i2c_read_buf(int dev_id, unsigned int i2c_offset, unsigned char *buf, int size)
{
    int err = 0;
    int i2c_dev_id;
    int i;

    ENTER_FUNC();
    err = sx_dpt_get_i2c_dev_by_id(dev_id, &i2c_dev_id);
    if (err) {
        PRINTK_ERR("sx_dpt_get_i2c_dev_by_id for dev_id: "
                   "%d failed !\n", dev_id);
        return -EINVAL;
    }

    DPRINTK("dev_id: 0x%x, i2c_dev_id: 0x%x, i2c_offset:0x%x, buf: %p, "
            "size: %d\n", dev_id, i2c_dev_id,
            i2c_offset, buf, size);

    for (i = 0; i < MAX_I2C_RETRIES; i++) {
        err = sx_glb.sx_i2c.read(i2c_dev_id, i2c_offset, size, buf);
        if (!err) {
            break;
        }
    }

    if (err) {
        PRINTK_ERR("sx_dpt_i2c_read_buf for dev_id: %d failed "
                   "after %d tries! err: %d \n", dev_id, i, err);
        return -EINVAL;
    }

    EXIT_FUNC();
    return err;
}

u32 sx_dpt_mst_readl(u32 offset, int *err)
{
    u32 ret;

    sx_glb.sx_mst.read(offset, 4, (u8*)&ret);
    *err = 0;

    return ret;
}

u32 sx_dpt_i2c_readl(int dev_id, u32 address, int *err)
{
    int value = 0;
    int i2c_dev_id;
    int i;

    ENTER_FUNC();
    *err = sx_dpt_get_i2c_dev_by_id(dev_id, &i2c_dev_id);
    if (*err) {
        PRINTK_ERR("sx_dpt_get_i2c_dev_by_id for dev_id: %d "
                   "failed !\n", dev_id);
        return 0;
    }

    for (i = 0; i < MAX_I2C_RETRIES; i++) {
        *err = sx_glb.sx_i2c.read_dword(i2c_dev_id, address, &value);
        if (!(*err)) {
            break;
        }
    }

    if (*err) {
        pr_debug("sx_dpt_i2c_readl for dev_id: %d failed "
                 "after %d tries!\n", dev_id, i);
        return 0;
    }

    if (i > 0) {
        printk(KERN_INFO "sx_dpt_i2c_read_buf for dev_id: %d "
               "succeeded after %d tries!\n", dev_id, i);
    }

    EXIT_FUNC();
    return value;
}

void sx_dump_dpt_entry(int i)
{
    const struct sx_dpt_info *dpt_info = &sx_glb.sx_dpt.dpt_info[i];

    printk(KERN_INFO "%d:   c:%s e:%s m:%s cr:%s ; ",
           i,
           __dpt_type2str(dpt_info->cmd_path),
           __dpt_type2str(dpt_info->emad_path),
           __dpt_type2str(dpt_info->mad_path),
           __dpt_type2str(dpt_info->cr_access_path));

    if (dpt_info->is_ifc_valid[DPT_PATH_I2C]) {
        printk(KERN_INFO "i2c (HCR2):0x%x mbox in 0x%x out 0x%x",
               dpt_info->sx_i2c_info.sx_i2c_dev,
               dpt_info->in_mb_offset[HCR2],
               dpt_info->out_mb_offset[HCR2]);
    }

    if (dpt_info->is_ifc_valid[DPT_PATH_MST]) {
        printk(KERN_INFO "MST (HCR2): mbox in 0x%x out 0x%x",
               dpt_info->in_mb_offset[HCR2],
               dpt_info->out_mb_offset[HCR2]);
    }

    if (dpt_info->is_ifc_valid[DPT_PATH_SGMII]) {
        printk(KERN_INFO "sgmii: DMAC %02x:%02x:%02x:%02x:%02x:%02x, VID %u",
               dpt_info->sx_sgmii_info.dmac[0],
               dpt_info->sx_sgmii_info.dmac[1],
               dpt_info->sx_sgmii_info.dmac[2],
               dpt_info->sx_sgmii_info.dmac[3],
               dpt_info->sx_sgmii_info.dmac[4],
               dpt_info->sx_sgmii_info.dmac[5],
               dpt_info->sx_sgmii_info.vid);
    }

    if (dpt_info->is_ifc_valid[DPT_PATH_PCI_E]) {
        printk(KERN_INFO "pci (HCR1): mbox in 0x%x out 0x%x",
               dpt_info->in_mb_offset[HCR1],
               dpt_info->out_mb_offset[HCR1]);
    }

    printk(KERN_INFO "\n");
}

void sx_dpt_dump(void)
{
    int cnt = 0;
    int i;

    printk(KERN_INFO "DUMP DPT:\n");
    for (i = 0; i < MAX_NUM_OF_REMOTE_SWITCHES + 1; i++) {
        if (sx_glb.sx_dpt.dpt_info[i].is_ifc_valid[DPT_PATH_I2C] ||
            sx_glb.sx_dpt.dpt_info[i].is_ifc_valid[DPT_PATH_SGMII] ||
            sx_glb.sx_dpt.dpt_info[i].is_ifc_valid[DPT_PATH_PCI_E]) {
            sx_dump_dpt_entry(i);
            cnt++;
        }
    }

    printk(KERN_INFO "Active DPT entries : %d \n", cnt);
}

void sx_dpt_set_cmd_dbg(int dev_id, int path)
{
    sx_dpt_set_cmd_path(dev_id, path);
}

void sx_dpt_reg_i2c_ifc(struct sx_i2c_ifc *i2c_ifc)
{
    sx_glb.sx_i2c.read = __symbol_get("i2c_read");
    sx_glb.sx_i2c.write = __symbol_get("i2c_write");
    sx_glb.sx_i2c.read_dword = __symbol_get("i2c_read_dword");
    sx_glb.sx_i2c.write_dword = __symbol_get("i2c_write_dword");
    sx_glb.sx_i2c.enforce = __symbol_get("i2c_enforce");
    sx_glb.sx_i2c.release = __symbol_get("i2c_release");
    sx_glb.sx_i2c.get_local_mbox = __symbol_get("i2c_get_local_mbox");
    sx_glb.sx_i2c.get_fw_rev = __symbol_get("i2c_get_fw_rev");
    sx_glb.sx_i2c.set_go_bit_stuck = __symbol_get("i2c_set_go_bit_stuck");
}
EXPORT_SYMBOL(sx_dpt_reg_i2c_ifc);

void sx_dpt_reg_mst_ifc(struct sx_mst_ifc* mst_ifc)
{
    sx_glb.sx_mst.read = __symbol_get("mst_api_read");
    sx_glb.sx_mst.write = __symbol_get("mst_api_write");
}

void sx_dpt_dereg_i2c_ifc(void)
{
    if (!sx_glb.sx_i2c.read || (sx_glb.sx_i2c.read == sx_dpt_stub_i2c_read)) {
        return;
    }

    if (sx_glb.sx_i2c.read) {
        __symbol_put("i2c_read");
    }
    if (sx_glb.sx_i2c.write) {
        __symbol_put("i2c_write");
    }
    if (sx_glb.sx_i2c.read_dword) {
        __symbol_put("i2c_read_dword");
    }
    if (sx_glb.sx_i2c.write_dword) {
        __symbol_put("i2c_write_dword");
    }
    if (sx_glb.sx_i2c.enforce) {
        __symbol_put("i2c_enforce");
    }
    if (sx_glb.sx_i2c.release) {
        __symbol_put("i2c_release");
    }
    if (sx_glb.sx_i2c.get_local_mbox) {
        __symbol_put("i2c_get_local_mbox");
    }
    if (sx_glb.sx_i2c.get_fw_rev) {
        __symbol_put("i2c_get_fw_rev");
    }
    if (sx_glb.sx_i2c.set_go_bit_stuck) {
        __symbol_put("i2c_set_go_bit_stuck");
    }
}
EXPORT_SYMBOL(sx_dpt_dereg_i2c_ifc);

void sx_dpt_dereg_mst_ifc(void)
{
    if (!sx_glb.sx_mst.read || (sx_glb.sx_mst.read == sx_dpt_stub_mst_read)) {
        return;
    }

    if (sx_glb.sx_mst.read) {
        __symbol_put("mst_api_read");
    }
    if (sx_glb.sx_mst.write) {
        __symbol_put("mst_api_write");
    }
}
EXPORT_SYMBOL(sx_dpt_dereg_mst_ifc);

int sx_dpt_stub_i2c_enforce(int i2c_dev_id)
{
    PRINTK_ERR("i2c module non registered !!!\n");

    return 0;
}

int sx_dpt_stub_i2c_release(int i2c_dev_id)
{
    PRINTK_ERR("i2c module non registered !!!\n");

    return 0;
}

int sx_dpt_stub_i2c_write(int i2c_dev_id, int offset, int len, u8 *in_out_buf)
{
    PRINTK_ERR("i2c module non registered !!!\n");

    return 0;
}

int sx_dpt_stub_i2c_read(int i2c_dev_id, int offset, int len, u8 *in_out_buf)
{
    PRINTK_ERR("i2c module not registered !\n");

    return 0;
}

int sx_dpt_stub_i2c_write_dword(int i2c_dev_id, int offset, u32 val)
{
    PRINTK_ERR("i2c module not registered!\n");

    return 0;
}

int sx_dpt_stub_i2c_read_dword(int i2c_dev_id, int offset, u32 *val)
{
    PRINTK_ERR("i2c module not registered !\n");

    return 0;
}

int sx_dpt_cr_space_read(int dev_id, unsigned int address, unsigned char *buf, int size)
{
    enum ku_dpt_path_type   cr_access_path = sx_dpt_get_cr_access_path(dev_id);
    int                     err = 0;
    struct ku_dpt_i2c_info* sx_i2c_info = NULL;

    ENTER_FUNC();

    switch (cr_access_path) {
    case (DPT_PATH_I2C):
        if (!sx_glb.sx_i2c.enforce) {
            printk(KERN_ERR PFX "enforce is NULL!!!\n");
            err = -EINVAL;
            goto out;
        }

        err = sx_dpt_get_i2c_info(dev_id, &sx_i2c_info);
        if (err) {
            printk(KERN_WARNING PFX "Can't get I2C info of device %d. "
                   "cr space read will not be performed. err = %d\n",
                   dev_id, err);
            goto out;
        }
        err = sx_glb.sx_i2c.enforce(sx_i2c_info->sx_i2c_dev);
        if (err) {
            printk(KERN_WARNING PFX "I2C bus of device %d is not ready. "
                   "cr space read will not be performed. err = %d\n",
                   dev_id, err);
            goto out;
        }

        err = sx_dpt_i2c_read_buf(dev_id, address, buf, size);
        sx_glb.sx_i2c.release(sx_i2c_info->sx_i2c_dev);
        if (err) {
            printk(KERN_WARNING PFX "I2C bus of device %d is not ready. "
                   "cr space read will not be performed. err = %d\n",
                   dev_id, err);
            goto out;
        }

        break;

    case (DPT_PATH_PCI_E):
        DPRINTK("Reading CR space using PCIE\n");

        err = __cr_pcie_access(dev_id, address, buf, size, CR_ACCESS_METHOD_READ);
        if (err) {
            printk(KERN_ERR PFX "Device ID [%u] failed on pci read access\n", dev_id);
            goto out;
        }

        break;

    case DPT_PATH_SGMII:
        err = sgmii_send_cr_space_read(dev_id, address, buf, size);
        if (err) {
            printk(
                KERN_NOTICE "failed to send CR-Space read-request device:[%d], address:[0x%x] over SGMII (err=%d)\n",
                dev_id,
                address,
                err);
            goto out;
        }

        break;

    case DPT_PATH_MST:
        err = sx_dpt_mst_read_buf(address, buf, size);
        if (err) {
            printk(KERN_WARNING "failed to read CR-Space with MST (err=%d)\n", err);
            goto out;
        }

        break;

    default:
        printk(KERN_ERR PFX "sx_dpt_cr_space_read: Can't read from CR space "
               "of device %u because the DPT path isn't valid\n", dev_id);
        err = -EINVAL;
        break;
    }

out:
    EXIT_FUNC();
    return err;
}

int sx_dpt_cr_space_write(int dev_id, unsigned int address, unsigned char *buf, int size)
{
    enum ku_dpt_path_type   cr_access_path = sx_dpt_get_cr_access_path(dev_id);
    int                     err = 0;
    struct ku_dpt_i2c_info* sx_i2c_info;

    ENTER_FUNC();

    switch (cr_access_path) {
    case (DPT_PATH_I2C):
        if (!sx_glb.sx_i2c.enforce) {
            printk(KERN_ERR PFX "enforce is NULL!!!\n");
            err = -EINVAL;
            goto out;
        }

        err = sx_dpt_get_i2c_info(dev_id, &sx_i2c_info);
        if (err) {
            printk(KERN_WARNING PFX "Can't get I2C info of device %d. "
                   "cr space read will not be performed. err = %d\n",
                   dev_id, err);
            goto out;
        }
        err = sx_glb.sx_i2c.enforce(sx_i2c_info->sx_i2c_dev);
        if (err) {
            printk(KERN_WARNING PFX "I2C bus of device %d is not ready. "
                   "cr space write will not be performed. err = %d\n",
                   dev_id, err);
            goto out;
        }

        err = sx_dpt_i2c_write_buf(dev_id, address, buf, size);
        sx_glb.sx_i2c.release(sx_i2c_info->sx_i2c_dev);
        if (err) {
            printk(KERN_WARNING PFX "I2C bus of device %d is not ready. "
                   "cr space write will not be performed. err = %d\n",
                   dev_id, err);
            goto out;
        }
        break;

    case (DPT_PATH_PCI_E):
        DPRINTK("Writing CR space using PCIE\n");

        err = __cr_pcie_access(dev_id, address, buf, size, CR_ACCESS_METHOD_WRITE);
        if (err) {
            printk(KERN_ERR PFX "Device ID [%u] failed on pcie write access\n", dev_id);
            goto out;
        }

        break;

    case DPT_PATH_SGMII:
        err = sgmii_send_cr_space_write(dev_id, address, buf, size);
        if (err) {
            printk(KERN_ERR "failed to send CR-Space write-request device:[%d], address:[0x%x] over SGMII (err=%d)\n",
                   dev_id, address, err);
            goto out;
        }

        break;

    case DPT_PATH_MST:
        err = sx_dpt_mst_write_buf(address, buf, size);
        if (err) {
            printk(KERN_WARNING "failed to write CR-Space with MST (err=%d)\n", err);
            goto out;
        }

        break;

    default:
        printk(KERN_ERR PFX "sx_dpt_cr_space_write: Can't write to CR space "
               "of device %u because the DPT path isn't valid\n", dev_id);
        err = -EINVAL;
        break;
    }

out:
    EXIT_FUNC();
    return err;
}

static int __cr_pcie_access(int              dev_id,
                            unsigned int     address,
                            unsigned char   *buff,
                            int              size,
                            cr_access_method access_method)
{
    int             err = 0;
    void __iomem   *cr_addr = NULL;
    struct sx_dev  *pcie_dev = NULL;
    struct sx_priv *priv = NULL;
    u32             bytes_processed = 0;

    if (buff == NULL) {
        printk(KERN_ERR PFX "__cr_pcie_access: Invalid buffer address for"
               "device %u\n", dev_id);
        err = -EINVAL;
        goto out;
    }

    if ((access_method < CR_ACCESS_METHOD_MIN) || (access_method > CR_ACCESS_METHOD_MAX)) {
        printk(KERN_ERR PFX "__cr_pcie_access: Can't access CR space "
               "of device %u because access method %d is invalid\n", dev_id, access_method);
        err = -EINVAL;
        goto out;
    }

    if ((size % 4) != 0) {
        printk(KERN_ERR PFX "__cr_pcie_access: size %u is invalid, must be a multiply of 4\n", size);
        err = -EINVAL;
        goto out;
    }

    if (!sx_dpt_is_dev_pci_attached(dev_id)) {
        printk(KERN_ERR PFX  "__cr_pcie_access: Device ID [%u] is not PCI device\n", dev_id);
        err = -ENODEV;
        goto out;
    }

    pcie_dev = sx_dev_db_get_dev_by_id(dev_id);
    priv = sx_priv(pcie_dev);

    /* address is offset in cr_space, so need to validate the boundaries */
    if (address > priv->cr_space_size) {
        err = -EINVAL;
        sx_err(pcie_dev, "__cr_pcie_access: Couldn't access address %u, exceeds PCI device size %u, aborting.\n",
               address, priv->cr_space_size);
        goto out;
    }

    if ((address + (unsigned long)size) > priv->cr_space_size) {
        err = -EINVAL;
        sx_err(pcie_dev, "__cr_pcie_access: Block at addr %d with size %d exceeds CR space size %d, aborting.\n",
               address, size, priv->cr_space_size);
        goto out;
    }

    cr_addr = priv->cr_space_start + address;

    switch (access_method) {
    case CR_ACCESS_METHOD_READ:
        while (bytes_processed < size) {
            (*(u32*)(buff + bytes_processed)) = readl(cr_addr + bytes_processed);
            bytes_processed += 4;
        }
        break;

    case CR_ACCESS_METHOD_WRITE:
        while (bytes_processed < size) {
            writel((*((uint32_t*)(buff + bytes_processed))), cr_addr + bytes_processed);
            bytes_processed += 4;
        }
        break;

    /* coverity[dead_error_begin] */
    default:
        printk(KERN_ERR PFX "__cr_pcie_access: Can't access CR space "
               "of device %u because access method %d is invalid\n", dev_id, access_method);
        err = -EINVAL;
        goto out;
    }

out:
    return err;
}

bool sx_dpt_dump_hanlders_per_device_init(struct sx_dev *dev, void *context)
{
    sx_dbg_dump_read_handler_register("dpt_dump", __dpt_dump_handler, NULL, dev, NULL);
    return true;
}

bool sx_dpt_dump_hanlders_per_device_deinit(struct sx_dev *dev, void *context)
{
    sx_dbg_dump_read_handler_unregister("dpt_dump", dev);
    return true;
}
