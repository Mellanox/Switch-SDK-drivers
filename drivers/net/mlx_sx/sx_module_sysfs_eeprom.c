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

#include <linux/module.h>
#include <linux/if_vlan.h>
#include <linux/poll.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/skb_hook.h>
#include <linux/seq_file.h>
#include <linux/ktime.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/driver.h>

#include "sx.h"
#include "alloc.h"
#include "dev_init.h"
#include "dev_db.h"

/************************************************
 *  Define
 ***********************************************/
#define EEPROM_UPPER_PAGE_OFFSET       (0x80)
#define EEPROM_MODULE_PAGE_SELECT_ADDR 127
#define MCIA_EEPROM_MAX_ACCESS_SIZE    48
#define MCIA_DWOARD_BYTE1(dword) (((dword) >> 24) & 0xFF)
#define MCIA_DWOARD_BYTE2(dword) (((dword) >> 16) & 0xFF)
#define MCIA_DWOARD_BYTE3(dword) (((dword) >> 8) & 0xFF)
#define MCIA_DWOARD_BYTE4(dword) (((dword)) & 0xFF)

#define MCIA_BYTE1_TO_DWOARD(byte) (((byte) << 24) & 0xFF000000)
#define MCIA_BYTE2_TO_DWOARD(byte) (((byte) << 16) & 0x00FF0000)
#define MCIA_BYTE3_TO_DWOARD(byte) (((byte) << 8) & 0x0000FF00)
#define MCIA_BYTE4_TO_DWOARD(byte) ((byte) & 0x000000FF)

#define FW_STATUS_BUSY          (0x1)
#define MCIA_ACCESS_MAX_RETRIES 3

/************************************************
 *  Enum
 ***********************************************/
enum eeprom_management_type {
    EEPROM_MANAGEMENT_TYPE_SFP  = 0x01,
    EEPROM_MANAGEMENT_TYPE_QSFP = 0x02,
    EEPROM_MANAGEMENT_TYPE_CMIS = 0x03,
};

enum eeprom_module_info_id {
    EEPROM_MODULE_INFO_ID_SFP            = 0x03,
    EEPROM_MODULE_INFO_ID_QSFP           = 0x0C,
    EEPROM_MODULE_INFO_ID_QSFP_PLUS      = 0x0D,
    EEPROM_MODULE_INFO_ID_QSFP28         = 0x11,
    EEPROM_MODULE_INFO_ID_QSFP_DD        = 0x18,
    EEPROM_MODULE_INFO_ID_QSFP_8X        = 0x19,
    EEPROM_MODULE_INFO_ID_SFP_DD         = 0x1A,
    EEPROM_MODULE_INFO_ID_DSFP           = 0x1B,
    EEPROM_MODULE_INFO_ID_QSFP_PLUS_CMIS = 0x1E,
};

enum mcia_module_status {
    MCIA_MODULE_STATUS_GOOD                  = 0,
    MCIA_MODULE_STATUS_NO_EEPROM_MODULE      = 0x1,
    MCIA_MODULE_STATUS_MODULE_NOT_SUPPORTED  = 0x2,
    MCIA_MODULE_STATUS_MODULE_NOT_CONNECTED  = 0x3,
    MCIA_MODULE_STATUS_MODULE_TYPE_INVALID   = 0x4,
    MCIA_MODULE_STATUS_MODULE_NOT_ACCESSIBLE = 0x5,
    MCIA_MODULE_STATUS_I2C_ERROR             = 0x9,
    MCIA_MODULE_STATUS_MODULE_DISABLED       = 0x10,
    MCIA_MODULE_STATUS_PAGE_ACCESS_FAILED    = 0x11,
};

enum mcia_module_access_type {
    MCIA_MODULE_ACCESS_TYPE_READ  = 1,
    MCIA_MODULE_ACCESS_TYPE_WRITE = 2,
};

/************************************************
 * Type declarations
 ***********************************************/
struct page_limit_bytes_segment {
    int page;
    int begin;
    int end;
};

struct page_access_segment {
    int begin;
    int end;
};

/************************************************
 * Globals
 ***********************************************/
/* entries within same page should be added adjacently and in sequence */
static struct page_limit_bytes_segment cmis_rd_limit_arr[] = {
    {0, 8, 13},
    {0, 126, 127},
    {11, 134, 135}
};

static struct page_limit_bytes_segment cmis_wr_limit_arr[] = {
    {0, 26, 26},
    {0, 31, 36},
    {0, 126, 127},
    {10, 0, 255}
};

static struct page_limit_bytes_segment sff8636_rd_limit_arr[] = {
    {0, 3, 21},
    {0, 127, 127}
};

static struct page_limit_bytes_segment sff8636_wr_limit_arr[] = {
    {0, 86, 88},
    {0, 93, 93},
    {0, 98, 99},
    {0, 100, 106},
    {0, 127, 127},
    {3, 230, 251}
};

/* SFF8472's limitation bytes are only for i2c 0x51 */
static struct page_limit_bytes_segment sff8472_rd_limit_arr[] = {
    {0, 112, 113},
    {0, 116, 117},
    {0, 127, 127}
};

static struct page_limit_bytes_segment sff8472_wr_limit_arr[] = {
    {0, 110, 110},
    {0, 114, 115},
    {0, 118, 118},
    {0, 127, 127}
};

static int cmis_rd_limit_arr_len = ARRAY_SIZE(cmis_rd_limit_arr);
static int cmis_wr_limit_arr_len = ARRAY_SIZE(cmis_wr_limit_arr);
static int sff8636_rd_limit_arr_len = ARRAY_SIZE(sff8636_rd_limit_arr);
static int sff8636_wr_limit_arr_len = ARRAY_SIZE(sff8636_wr_limit_arr);
static int sff8472_rd_limit_arr_len = ARRAY_SIZE(sff8472_rd_limit_arr);
static int sff8472_wr_limit_arr_len = ARRAY_SIZE(sff8472_wr_limit_arr);

/************************************************
 *  Functions
 ***********************************************/


static inline void __reg_mcia_pack(struct ku_mcia_reg *mcia_reg,
                                   uint8_t             module,
                                   uint8_t             lock,
                                   uint8_t             page,
                                   uint16_t            device_addr,
                                   ssize_t             size,
                                   uint8_t             i2c_addr,
                                   uint8_t             slot)
{
    mcia_reg->l = lock;
    mcia_reg->module = module;
    mcia_reg->slot_index = slot;
    mcia_reg->i2c_device_address = i2c_addr;
    mcia_reg->page_number = page;
    mcia_reg->device_address = device_addr;
    mcia_reg->size = size;
}

static int __handle_mcia_return_status(int status)
{
    int err = 0;

    switch (status) {
    case MCIA_MODULE_STATUS_GOOD:
        break;

    case MCIA_MODULE_STATUS_MODULE_NOT_CONNECTED:
    case MCIA_MODULE_STATUS_I2C_ERROR:
    case MCIA_MODULE_STATUS_MODULE_DISABLED:
    case MCIA_MODULE_STATUS_MODULE_TYPE_INVALID:
        printk(KERN_ERR "Fails to access MCIA due to unavailable hw link, status: %d.\n", status);
        err = -EIO;
        break;

    default:
        printk(KERN_ERR "Fails to access MCIA, status: %d.\n", status);
        err = -EFAULT;
    }

    return err;
}

/* Module eeprom access via MCIA may be blocked by other access via PMMP, etc., and FW will return busy to SDK. SDK should retry several times. */
static int __stateful_access_mcia(struct sx_dev *dev, struct ku_access_mcia_reg *reg_data)
{
    int err = 0;
    int try_loop = MCIA_ACCESS_MAX_RETRIES;/* FW would hold 20mSec per try. */

    while (try_loop-- > 0) {
        err = sx_ACCESS_REG_MCIA(dev, reg_data);
        if (err || reg_data->op_tlv.status) {
            if (reg_data->op_tlv.status == FW_STATUS_BUSY) {
                err = -EBUSY;
                printk(KERN_WARNING "Retry to access register MCIA again...\n");
                continue;
            }
            printk(KERN_ERR "Fails to access register MCIA, err: %d, status: %d.\n", err, reg_data->op_tlv.status);
            err = -EFAULT;
            goto out;
        }
        goto out;
    }
out:
    return err;
}

/*
 *  for page 1~255:
 *   SDK will write page number to page_selector byte 127, and set via MCIA
 *   SDK will read the page number from page_selector byte 127
 *   If the reading page is different - the page is invalid
 */
static int __validate_module_eeprom_page(struct sx_dev *dev,
                                         uint8_t        module,
                                         uint8_t        page,
                                         uint8_t        i2c_addr,
                                         uint8_t        slot,
                                         bool          *valid)
{
    int                       err = 0;
    uint8_t                   ret_page = 0;
    struct ku_access_mcia_reg reg_data;

    memset(&reg_data, 0, sizeof(reg_data));
    *valid = false;

    /* 1. write page number to page 0 page_selector byte */
    reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MCIA_REG_ID, EMAD_METHOD_WRITE);
    reg_data.mcia_reg.dword_0 |= MCIA_BYTE1_TO_DWOARD(page);

    __reg_mcia_pack(&reg_data.mcia_reg, module, 0, 0, EEPROM_MODULE_PAGE_SELECT_ADDR, 1, i2c_addr, slot);

    err = __stateful_access_mcia(dev, &reg_data);
    if (err) {
        printk(KERN_ERR "Fails to access MCIA during page validation write, err: %d.\n", err);
        goto out;
    }
    if (reg_data.mcia_reg.status) {
        err = __handle_mcia_return_status(reg_data.mcia_reg.status);
        goto out;
    }
    /* 2. read page number from page 0 page_selector byte */
    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MCIA_REG_ID, EMAD_METHOD_QUERY);

    /* due to known FW issues, we cannot read 1 bytes but 1 dword from MCIA, then extract the expected byte */
    __reg_mcia_pack(&reg_data.mcia_reg, module, 0, 0, EEPROM_MODULE_PAGE_SELECT_ADDR - 3, 4, i2c_addr, slot);

    err = __stateful_access_mcia(dev, &reg_data);
    if (err) {
        printk(KERN_ERR "Fails to access MCIA during page validation read, err: %d.\n", err);
        goto out;
    }

    if (reg_data.mcia_reg.status) {
        err = __handle_mcia_return_status(reg_data.mcia_reg.status);
        goto out;
    }
    ret_page = MCIA_DWOARD_BYTE4(reg_data.mcia_reg.dword_0);
    if (ret_page == page) {
        *valid = true;
    }

out:
    return err;
}

static int __sx_core_mcia_access(struct sx_dev             *dev,
                                 uint8_t                    access_type,
                                 uint8_t                    module,
                                 uint8_t                    page,
                                 uint16_t                   device_addr,
                                 uint8_t                    size,
                                 uint8_t                    i2c_addr,
                                 uint8_t                    slot,
                                 struct ku_access_mcia_reg *reg_data)
{
    int     err = 0;
    uint8_t lock = 0; /* suggested to be 0 by FW team. */
    uint8_t method = EMAD_METHOD_QUERY;

    if (access_type == MCIA_MODULE_ACCESS_TYPE_WRITE) {
        method = EMAD_METHOD_WRITE;
    }

    reg_data->dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&(reg_data->op_tlv), MCIA_REG_ID, method);

    __reg_mcia_pack(&(reg_data->mcia_reg), module, lock, page, device_addr, size, i2c_addr, slot);

    err = __stateful_access_mcia(dev, reg_data);
    if (err) {
        printk(
            KERN_ERR "Fails to access (%d) register MCIA (module:%d, page:%d, device_addr:%d, size:%d, i2c_addr:0x%x, slot:%d, status:%d), err: %d.\n",
            method,
            module,
            page,
            device_addr,
            size,
            i2c_addr,
            slot,
            reg_data->mcia_reg.status,
            err);
        goto out;
    }

out:
    return err;
}

static int __sx_core_get_module_type(struct sx_dev *dev, uint8_t module, uint8_t slot, uint8_t *type)
{
    int                       err = 0;
    uint8_t                   byte0 = 0;
    struct ku_access_mcia_reg reg_data;

    memset(&reg_data, 0, sizeof(reg_data));

    reg_data.dev_id = dev->device_id;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MCIA_REG_ID, EMAD_METHOD_QUERY);

    __reg_mcia_pack(&reg_data.mcia_reg, module, 0, 0, 0, 1, 0x50, slot);

    err = __stateful_access_mcia(dev, &reg_data);
    if (err) {
        printk(KERN_ERR "Fails to get module type, err: %d.\n", err);
        goto out;
    }

    if (reg_data.mcia_reg.status) {
        err = __handle_mcia_return_status(reg_data.mcia_reg.status);
        goto out;
    }
    byte0 = MCIA_DWOARD_BYTE1(reg_data.mcia_reg.dword_0);
    switch (byte0) {
    case EEPROM_MODULE_INFO_ID_SFP:
        *type = EEPROM_MANAGEMENT_TYPE_SFP;
        break;

    case EEPROM_MODULE_INFO_ID_QSFP:
    case EEPROM_MODULE_INFO_ID_QSFP_PLUS:
    case EEPROM_MODULE_INFO_ID_QSFP28:
        *type = EEPROM_MANAGEMENT_TYPE_QSFP;
        break;

    case EEPROM_MODULE_INFO_ID_QSFP_DD:
    case EEPROM_MODULE_INFO_ID_QSFP_8X:
    case EEPROM_MODULE_INFO_ID_SFP_DD:
    case EEPROM_MODULE_INFO_ID_DSFP:
    case EEPROM_MODULE_INFO_ID_QSFP_PLUS_CMIS:
        *type = EEPROM_MANAGEMENT_TYPE_CMIS;
        break;

    default:
        printk(KERN_ERR "Unknown EEPROM type: %d.\n", byte0);
        return -EFAULT;
    }

out:
    return err;
}

/*
 *  check whether buff range [buf_b, buf_e] is overlapping with a limitation byte range [limit_b, limit_e]:
 *   if yes, return true, with the overlapping range in [*hole_b, *hole_e]
 *   if no, return false
 */
static bool __range_is_overlap(loff_t buf_b, size_t buf_e, int limit_b, size_t limit_e, int *hole_b, int *hole_e)
{
    if ((buf_b > limit_e) || (buf_e < limit_b)) {
        return false;
    }

    *hole_b = buf_b;
    *hole_e = buf_e;

    if (buf_b < limit_b) {
        *hole_b = limit_b;
    }

    if (buf_e > limit_e) {
        *hole_e = limit_e;
    }

    return true;
}

/* Calculate whether any limitation holes exist in the page access range (start, len): *ret_arr_len == 0 means no holes exist. */
static int get_limit_bytes_holes_from_eeprom_page_access_range(struct page_limit_bytes_segment *limit_arr,
                                                               int                              limit_arr_len,
                                                               uint8_t                          page,
                                                               loff_t                           start,
                                                               size_t                           len,
                                                               struct page_access_segment     **ret_hole_arr,
                                                               int                             *ret_hole_arr_len)
{
    int                         err = 0;
    int                         i;
    bool                        found = false;
    int                         hole_b = 0;
    int                         hole_e = 0;
    int                         hole_num = 0;
    struct page_access_segment *holes = NULL;

    *ret_hole_arr_len = 0;

    for (i = 0; i < limit_arr_len; i++) {
        if (page == limit_arr[i].page) {
            found = true;
            break;
        }
    }
    if (!found) {
        goto out;
    }

    for (; i < limit_arr_len; i++) {
        if (page != limit_arr[i].page) {
            break;
        }
        if (__range_is_overlap(start, start + len - 1, limit_arr[i].begin, limit_arr[i].end, &hole_b, &hole_e)) {
            if (hole_b <= hole_e) {
                if (!holes) {
                    holes = kzalloc(sizeof(*holes) * limit_arr_len, GFP_KERNEL);
                    if (!holes) {
                        err = -ENOMEM;
                        goto out;
                    }
                }
                holes[hole_num].begin = hole_b;
                holes[hole_num].end = hole_e;
                hole_num++;
            }
        }
    }
    *ret_hole_arr_len = hole_num;
    *ret_hole_arr = holes;
out:
    return err;
}

/*
 *  The function should be called after get_limit_bytes_holes_from_eeprom_page_access_range(..),
 *  and it assumes that all holes should be within the page access range.
 */
static int __separate_eeprom_page_access_range_into_segments(struct page_access_segment  *hole_arr,
                                                             int                          hole_arr_len,
                                                             loff_t                       start,
                                                             size_t                       len,
                                                             struct page_access_segment **ret_arr,
                                                             int                         *ret_arr_len)
{
    int                         err = 0;
    int                         i;
    size_t                      hole_b = 0;
    size_t                      hole_e = 0;
    int                         max_segments = hole_arr_len + 1;
    int                         segments = 1;
    struct page_access_segment *segs = NULL;

    *ret_arr_len = segments;
    segs = kmalloc(sizeof(*segs) * max_segments, GFP_KERNEL);
    if (!(segs)) {
        err = -ENOMEM;
        goto out;
    }
    segs[0].begin = start;
    segs[0].end = start + len - 1;

    for (i = 0; i < hole_arr_len; i++) {
        hole_b = hole_arr[i].begin;
        hole_e = hole_arr[i].end;

        if (hole_e >= segs[segments - 1].end) {
            /* page access range is reached, and no need to compare more */
            if (hole_b == segs[segments - 1].begin) {
                segments--;
                break;
            }
            segs[segments - 1].end = hole_b - 1;
            break;
        }
        /* case: hole_e < segs[segments - 1].end */
        if (hole_b == segs[segments - 1].begin) {
            segs[segments - 1].begin = hole_e + 1;
            continue;
        }
        /* Extend a new segment */
        segs[segments].begin = hole_e + 1;
        segs[segments].end = segs[segments - 1].end;
        segs[segments - 1].end = hole_b - 1;

        segments++;
    }
    *ret_arr_len = segments;
    *ret_arr = segs;

out:
    return err;
}

static int __sx_core_get_slot_and_module(struct sx_dev *dev, uint16_t local_port, uint8_t *slot, uint8_t *module)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    unsigned long   flags;

    if (local_port > MAX_PHYPORT_NUM) {
        printk(KERN_ERR "Local port %d is invalid. (MAX %d).\n", local_port, MAX_PHYPORT_NUM);
        err = -EINVAL;
        goto out;
    }

    spin_lock_irqsave(&priv->db_lock, flags);
    *slot = priv->local_to_slot_map[local_port];
    *module = priv->local_to_module_map[local_port];
    spin_unlock_irqrestore(&priv->db_lock, flags);

    if ((*slot >= MAX_SLOT_NUM) || (*module >= MAX_MODULE_NUM)) {
        err = -EINVAL;
        printk(KERN_ERR "slot id %d or module id %d is out of range.\n", *slot, *module);
        goto out;
    }

out:
    return err;
}

/* Fetch the required params for MCIA access/check */
static int __module_sysfs_eeprom_parse_params(const char                        *node_name,
                                              loff_t                             pos,
                                              struct sx_dev                     *dev,
                                              uint16_t                           local_port,
                                              enum sx_module_sysfs_eeprom_access access,
                                              uint8_t                           *module,
                                              uint8_t                           *slot,
                                              uint8_t                           *i2c_addr,
                                              uint8_t                           *page,
                                              uint16_t                          *device_addr,
                                              struct page_limit_bytes_segment  **limit_arr,
                                              int                               *limit_arr_len)
{
    int     err = 0;
    bool    valid = false;
    uint8_t mgmt_type = 0;

    *i2c_addr = 0x50;

    err = __sx_core_get_slot_and_module(dev, local_port, slot, module);
    if (err) {
        printk(KERN_ERR "Fails to get module id, status: %d.\n", err);
        err = -EINVAL;
        goto out;
    }

    err = __sx_core_get_module_type(dev, *module, *slot, &mgmt_type);
    if (err) {
        printk(KERN_ERR PFX "Failed to get the module type, err: %d\n", err);
        goto out;
    }

    if (node_name[0] == 'i') {
        *page = 0;
        if (strcmp(node_name, "i2c-0x51") == 0) {
            *i2c_addr = 0x51;
            if (mgmt_type != EEPROM_MANAGEMENT_TYPE_SFP) {
                printk(KERN_NOTICE "Failed to access i2c address 0x51 because module type is not SFF-8472.\n");
                err = -EFAULT;
                goto out;
            }
        }
    } else {
        *page = (uint8_t)simple_strtol(node_name, NULL, 10);
        if (mgmt_type == EEPROM_MANAGEMENT_TYPE_SFP) {
            *i2c_addr = 0x51;
        }
    }

    *device_addr = pos;

    if (*page > 0) {
        /* page 0 has been verified in previous module type check */
        err = __validate_module_eeprom_page(dev, *module, *page, *i2c_addr, *slot, &valid);
        if (err) {
            printk(KERN_NOTICE "Failed to validate page %d of module %d, err: %d\n", *page, *module, err);
            err = -EFAULT;
            goto out;
        }
        if (!valid) {
            printk(KERN_NOTICE "Module %d page %d is invalid, bypass it.\n", *module, *page);
            err = -EFAULT;
            goto out;
        }
        /* add upper page offset for page 1~255 */
        *device_addr += EEPROM_UPPER_PAGE_OFFSET;
    }
    switch (mgmt_type) {
    case EEPROM_MANAGEMENT_TYPE_SFP:
        if (*i2c_addr == 0x51) {
            /* SFF8472's limitation bytes are only for i2c 0x51 */
            if (access == MODULE_SYSFS_EEPROM_READ) {
                *limit_arr = sff8472_rd_limit_arr;
                *limit_arr_len = sff8472_rd_limit_arr_len;
            } else {
                *limit_arr = sff8472_wr_limit_arr;
                *limit_arr_len = sff8472_wr_limit_arr_len;
            }
        }
        break;

    case EEPROM_MANAGEMENT_TYPE_QSFP:
        if (access == MODULE_SYSFS_EEPROM_READ) {
            *limit_arr = sff8636_rd_limit_arr;
            *limit_arr_len = sff8636_rd_limit_arr_len;
        } else {
            *limit_arr = sff8636_wr_limit_arr;
            *limit_arr_len = sff8636_wr_limit_arr_len;
        }
        break;

    case EEPROM_MANAGEMENT_TYPE_CMIS:
        if (access == MODULE_SYSFS_EEPROM_READ) {
            *limit_arr = cmis_rd_limit_arr;
            *limit_arr_len = cmis_rd_limit_arr_len;
        } else {
            *limit_arr = cmis_wr_limit_arr;
            *limit_arr_len = cmis_wr_limit_arr_len;
        }
        break;

    default:
        printk(KERN_ERR "Invalid module type %d.\n", mgmt_type);
        err = -EINVAL;
        goto out;
        break;
    }

out:
    return err;
}

ssize_t __module_sysfs_eeprom_low_level_read(struct sx_dev *dev,
                                             char          *buf,
                                             ssize_t        count,
                                             uint8_t        module,
                                             uint8_t        slot,
                                             uint8_t        page,
                                             uint16_t       device_addr,
                                             uint8_t        i2c_addr)
{
    int                       err = 0;
    ssize_t                   len, remainder;
    loff_t                    i, dw_end;
    uint8_t                   rd_len;
    uint16_t                  handled;
    uint32_t                 *dword = NULL;
    struct ku_access_mcia_reg reg_data;

    len = count;
    handled = 0;
    while (len > 0) {
        rd_len = len;
        if (len > MCIA_EEPROM_MAX_ACCESS_SIZE) {
            rd_len = MCIA_EEPROM_MAX_ACCESS_SIZE;
        }

        memset(&reg_data, 0, sizeof(reg_data));
        err = __sx_core_mcia_access(dev,
                                    MCIA_MODULE_ACCESS_TYPE_READ,
                                    module,
                                    page,
                                    device_addr + handled,
                                    rd_len,
                                    i2c_addr,
                                    slot,
                                    &reg_data);
        if (err) {
            printk(KERN_ERR "Fails to read module eeprom, status: %d.\n", err);
            if (err > 0) {
                err = -err;
            }
            goto out;
        }
        if (reg_data.mcia_reg.status) {
            err = __handle_mcia_return_status(reg_data.mcia_reg.status);
            goto out;
        }

        dword = &(reg_data.mcia_reg.dword_0);
        remainder = rd_len % 4;
        dw_end = handled + rd_len - remainder;
        for (i = handled; i < dw_end; i += 4) {
            buf[i] = MCIA_DWOARD_BYTE1(*dword);
            buf[i + 1] = MCIA_DWOARD_BYTE2(*dword);
            buf[i + 2] = MCIA_DWOARD_BYTE3(*dword);
            buf[i + 3] = MCIA_DWOARD_BYTE4(*dword);
            dword++;
        }
        if (remainder) {
            if (remainder == 3) {
                buf[i + 2] = MCIA_DWOARD_BYTE3(*dword);
            }
            if (remainder >= 2) {
                buf[i + 1] = MCIA_DWOARD_BYTE2(*dword);
            }
            if (remainder >= 1) {
                buf[i] = MCIA_DWOARD_BYTE1(*dword);
            }
        }
        len -= rd_len;
        handled += rd_len;
    }

out:
    if (err < 0) {
        return err;
    }
    return count;
}

ssize_t __module_sysfs_eeprom_low_level_write(struct sx_dev *dev,
                                              char          *buf,
                                              ssize_t        count,
                                              uint8_t        module,
                                              uint8_t        slot,
                                              uint8_t        page,
                                              uint16_t       device_addr,
                                              uint8_t        i2c_addr)
{
    int                       err = 0;
    ssize_t                   len, remainder;
    loff_t                    i, dw_end;
    uint8_t                   wr_len;
    uint16_t                  handled;
    uint32_t                 *dword = NULL;
    struct ku_access_mcia_reg reg_data;

    len = count;
    handled = 0;
    while (len > 0) {
        wr_len = len;
        if (len > MCIA_EEPROM_MAX_ACCESS_SIZE) {
            wr_len = MCIA_EEPROM_MAX_ACCESS_SIZE;
        }

        memset(&reg_data, 0, sizeof(reg_data));
        dword = &(reg_data.mcia_reg.dword_0);
        remainder = wr_len % 4;
        dw_end = handled + wr_len - remainder;
        for (i = handled; i < dw_end; i += 4) {
            *dword |= MCIA_BYTE1_TO_DWOARD(buf[i]);
            *dword |= MCIA_BYTE2_TO_DWOARD(buf[i + 1]);
            *dword |= MCIA_BYTE3_TO_DWOARD(buf[i + 2]);
            *dword |= MCIA_BYTE4_TO_DWOARD(buf[i + 3]);
            dword++;
        }
        if (remainder) {
            if (remainder == 3) {
                *dword |= MCIA_BYTE3_TO_DWOARD(buf[i + 2]);
            }
            if (remainder >= 2) {
                *dword |= MCIA_BYTE2_TO_DWOARD(buf[i + 1]);
            }
            if (remainder >= 1) {
                *dword |= MCIA_BYTE1_TO_DWOARD(buf[i]);
            }
        }

        err = __sx_core_mcia_access(dev,
                                    MCIA_MODULE_ACCESS_TYPE_WRITE,
                                    module,
                                    page,
                                    device_addr + handled,
                                    wr_len,
                                    i2c_addr,
                                    slot,
                                    &reg_data);
        if (err) {
            printk(KERN_ERR "Fails to lower level write module eeprom, status: %d.\n", err);
            if (err > 0) {
                err = -err;
            }
            goto out;
        }
        if (reg_data.mcia_reg.status) {
            err = __handle_mcia_return_status(reg_data.mcia_reg.status);
            goto out;
        }

        len -= wr_len;
        handled += wr_len;
    }
out:
    if (err < 0) {
        return err;
    }
    return count;
}

ssize_t sx_core_module_sysfs_eeprom_access(struct sx_dev                     *dev,
                                           const char                        *node_name,
                                           uint16_t                           local_port,
                                           enum sx_module_sysfs_eeprom_access access,
                                           char                              *buf,
                                           loff_t                             pos,
                                           size_t                             count)
{
    int                              err = 0;
    ssize_t                          offset, len;
    loff_t                           i;
    uint8_t                          module = 0;
    uint8_t                          slot = 0;
    uint8_t                          page = 0;
    uint8_t                          i2c_addr = 0;
    uint16_t                         device_addr;
    bool                             release_lock = false;
    struct sx_priv                  *priv = sx_priv(dev);
    struct page_limit_bytes_segment *limit_arr = NULL;
    int                              limit_arr_len = 0;
    struct page_access_segment      *hole_arr = NULL;
    int                              hole_arr_len = 0;
    struct page_access_segment      *access_segs = NULL;
    int                              access_segs_len = 0;

    mutex_lock(&priv->module_access_mutex);
    release_lock = true;

    err = __module_sysfs_eeprom_parse_params(node_name,
                                             pos,
                                             dev,
                                             local_port,
                                             access,
                                             &module,
                                             &slot,
                                             &i2c_addr,
                                             &page,
                                             &device_addr,
                                             &limit_arr,
                                             &limit_arr_len);
    if (err) {
        printk(KERN_NOTICE "Fail to parse %s and cannot access it, err: %d\n", node_name, err);
        goto err_out;
    }

    err = get_limit_bytes_holes_from_eeprom_page_access_range(limit_arr,
                                                              limit_arr_len,
                                                              page,
                                                              device_addr,
                                                              count,
                                                              &hole_arr,
                                                              &hole_arr_len);
    if (err) {
        printk(KERN_NOTICE "Fail to get limitation bytes for %s in range of (%u, %lu), err: %d\n",
               node_name,
               device_addr,
               count,
               err);
        goto err_out;
    }

    if (access == MODULE_SYSFS_EEPROM_READ) {
        memset(buf, 0, count);
    }

    if (hole_arr_len == 0) {
        /* No limitation bytes in the access scope, simply call low-level access once. */
        if (access == MODULE_SYSFS_EEPROM_READ) {
            err = __module_sysfs_eeprom_low_level_read(dev, buf, count, module, slot, page, device_addr, i2c_addr);
        } else {
            err = __module_sysfs_eeprom_low_level_write(dev, buf, count, module, slot, page, device_addr, i2c_addr);
        }
        if (err < 0) {
            printk(KERN_ERR "Fails to access (%d) module eeprom, status: %d.\n", access, err);
            goto err_out;
        }
        goto out;
    }

    err = __separate_eeprom_page_access_range_into_segments(hole_arr,
                                                            hole_arr_len,
                                                            device_addr,
                                                            count,
                                                            &access_segs,
                                                            &access_segs_len);
    if (err) {
        printk(KERN_NOTICE "Fail to separate access range (%u, %lu) for %s, err: %d\n",
               device_addr,
               count,
               node_name,
               err);
        goto err_out;
    }

    /* call low-level access for each segments separated by limitation bytes */
    for (i = 0; i < access_segs_len; i++) {
        offset = access_segs[i].begin - pos;
        if (page > 0) {
            offset -= EEPROM_UPPER_PAGE_OFFSET;
        }
        len = access_segs[i].end - access_segs[i].begin + 1;
        if (access == MODULE_SYSFS_EEPROM_READ) {
            err = __module_sysfs_eeprom_low_level_read(dev,
                                                       buf + offset,
                                                       len,
                                                       module,
                                                       slot,
                                                       page,
                                                       access_segs[i].begin,
                                                       i2c_addr);
        } else {
            err = __module_sysfs_eeprom_low_level_write(dev,
                                                        buf + offset,
                                                        len,
                                                        module,
                                                        slot,
                                                        page,
                                                        access_segs[i].begin,
                                                        i2c_addr);
        }
        if (err < 0) {
            printk(KERN_ERR "Fails to access (%d) module eeprom, status: %d.\n", access, err);
            goto err_out;
        }
    }
    kfree(access_segs);

out:
    if (hole_arr) {
        kfree(hole_arr);
    }
    mutex_unlock(&priv->module_access_mutex);
    release_lock = false;

    return count;

err_out:
    if (release_lock) {
        mutex_unlock(&priv->module_access_mutex);
    }
    if (access_segs) {
        kfree(access_segs);
    }
    if (hole_arr) {
        kfree(hole_arr);
    }
    return err;
}
EXPORT_SYMBOL(sx_core_module_sysfs_eeprom_access);
