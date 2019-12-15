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

#include <linux/vmalloc.h>

#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/cmd.h>

#include "alloc.h"
#include "sx_dpt.h"
#include "ioctl_internal.h"

/**
 * magic number for struct ku_sx_core_db.
 * The struct ku_sx_core_db passed between user space and kernel space has big size, we
 * place this magic number at the beginning and end of the struct to verify if the entire
 * struct is successfully copied between user space and kernel space.
 */
#define SX_CORE_DB_MAGIC_NUM 0xabcdabcd

static int sx_core_ioctl_set_dpt_info(struct sx_dev *dev, struct ku_sx_core_db *sx_core_db)
{
    int                    err = 0;
    int                    i;
    union ku_dpt_path_info path_info;

    for (i = 0; i < MAX_NUM_OF_REMOTE_SWITCHES; i++) {
        if (sx_core_db->dpt_info[i].is_ifc_valid[DPT_PATH_I2C]) {
            path_info.sx_i2c_info = sx_core_db->dpt_info[i].sx_i2c_info;
            err = sx_dpt_add_dev_path(i,
                                      DPT_PATH_I2C,
                                      path_info,
                                      sx_core_db->dpt_info[i].is_local[DPT_PATH_I2C]);
            if (err) {
                goto out;
            }
        }
        if (sx_core_db->dpt_info[i].is_ifc_valid[DPT_PATH_SGMII]) {
            path_info.sx_sgmii_info = sx_core_db->dpt_info[i].sx_sgmii_info;
            err = sx_dpt_add_dev_path(i,
                                      DPT_PATH_SGMII,
                                      path_info,
                                      sx_core_db->dpt_info[i].is_local[DPT_PATH_SGMII]);
            if (err) {
                goto out;
            }
        }
        if (sx_core_db->dpt_info[i].is_ifc_valid[DPT_PATH_PCI_E]) {
            path_info.sx_pcie_info = sx_core_db->dpt_info[i].sx_pcie_info;
            err = sx_dpt_add_dev_path(i,
                                      DPT_PATH_PCI_E,
                                      path_info,
                                      sx_core_db->dpt_info[i].is_local[DPT_PATH_PCI_E]);
            if (err) {
                goto out;
            }
        }
        if (sx_core_db->dpt_info[i].cmd_path != DPT_PATH_INVALID) {
            err = sx_dpt_set_cmd_path(i, sx_core_db->dpt_info[i].cmd_path);
            if (err) {
                goto out;
            }
        }
        if (sx_core_db->dpt_info[i].emad_path != DPT_PATH_INVALID) {
            err = sx_dpt_set_emad_path(i, sx_core_db->dpt_info[i].emad_path);
            if (err) {
                goto out;
            }
        }
        if (sx_core_db->dpt_info[i].mad_path != DPT_PATH_INVALID) {
            err = sx_dpt_set_mad_path(i, sx_core_db->dpt_info[i].mad_path);
            if (err) {
                goto out;
            }
        }
        if (sx_core_db->dpt_info[i].cr_access_path != DPT_PATH_INVALID) {
            err = sx_dpt_set_cr_access_path(i, sx_core_db->dpt_info[i].cr_access_path);
            if (err) {
                goto out;
            }
        }
    }

out:
    return err;
}


static int sx_core_ioctl_set_trap_group_info(struct sx_dev *dev, struct ku_sx_core_db *sx_core_db)
{
    int                       i;
    struct ku_access_htgt_reg reg_data;
    int                       err = 0;

    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.dev_id = 255;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, HTGT_REG_ID, 2); /* 2 - write */

    for (i = 0; i < NUM_OF_TRAP_GROUPS; i++) {
        memcpy(&(reg_data.htgt_reg), &(sx_core_db->trap_group_info[i]), sizeof(sx_core_db->trap_group_info[i]));
        err = sx_ACCESS_REG_HTGT(dev, &reg_data);
        if (err) {
            goto out;
        }
    }

out:
    return err;
}


static int sx_core_ioctl_set_netdev_trap_info(struct sx_dev *dev, struct ku_sx_core_db *sx_core_db)
{
    int     err = 0;
    uint8_t uc_type;
    int     i;

    for (uc_type = USER_CHANNEL_L3_NETDEV; uc_type < NUM_OF_NET_DEV_TYPE; uc_type++) {
        for (i = 0; i < sx_core_db->num_of_traps[uc_type]; i++) {
            switch (uc_type) {
            case USER_CHANNEL_L3_NETDEV:
                err =
                    sx_core_add_synd_l3(0, sx_core_db->trap_ids[uc_type][i], dev,
                                        &(sx_core_db->port_vlan_params[uc_type][i]));
                break;

            case USER_CHANNEL_LOG_PORT_NETDEV:
                err =
                    sx_core_add_synd_l2(0, sx_core_db->trap_ids[uc_type][i], dev,
                                        &(sx_core_db->port_vlan_params[uc_type][i]));
                break;

            case USER_CHANNEL_PHY_PORT_NETDEV:
                err =
                    sx_core_add_synd_phy(0, sx_core_db->trap_ids[uc_type][i], dev,
                                         &(sx_core_db->port_vlan_params[uc_type][i]));
                break;

            default:
                err = -EINVAL;
                break;
            }
            if (err) {
                goto out;
            }
        }
    }

out:
    return err;
}


static int sx_core_ioctl_set_rdq_properties(struct sx_dev *dev, struct ku_sx_core_db *sx_core_db)
{
    uint32_t i;

    for (i = 0; i < sx_core_db->ts_bitmap.max; i++) {
        if (sx_core_db->ts_bitmap.table[i]) {
            sx_bitmap_set(&sx_priv(dev)->cq_table.ts_bitmap, i);
        } else {
            sx_bitmap_free(&sx_priv(dev)->cq_table.ts_bitmap, i);
        }
    }

    for (i = 0; i < sx_core_db->high_prio_cq_bitmap.max; i++) {
        if (sx_core_db->high_prio_cq_bitmap.table[i]) {
            sx_bitmap_set(&(sx_priv(dev)->cq_table.cpu_traffic_prio.high_prio_cq_bitmap), i);
        } else {
            sx_bitmap_free(&(sx_priv(dev)->cq_table.cpu_traffic_prio.high_prio_cq_bitmap), i);
        }
    }

    return 0;
}


static int sx_core_ioctl_get_dpt_info(struct sx_dev *dev, struct ku_sx_core_db __user *sx_core_db)
{
    int                   err = 0;
    int                   i = 0;
    enum ku_dpt_path_type path_type;

    for (i = 0; i < MAX_NUM_OF_REMOTE_SWITCHES; i++) {
        if (i == DEFAULT_DEVICE_ID) {
            continue;
        }

        err = put_user(sx_glb.sx_dpt.dpt_info[i].cmd_path, &(sx_core_db->dpt_info[i].cmd_path));
        if (err) {
            goto out;
        }
        err = put_user(sx_glb.sx_dpt.dpt_info[i].emad_path, &(sx_core_db->dpt_info[i].emad_path));
        if (err) {
            goto out;
        }
        err = put_user(sx_glb.sx_dpt.dpt_info[i].mad_path, &(sx_core_db->dpt_info[i].mad_path));
        if (err) {
            goto out;
        }
        err = put_user(sx_glb.sx_dpt.dpt_info[i].cr_access_path, &(sx_core_db->dpt_info[i].cr_access_path));
        if (err) {
            goto out;
        }
        for (path_type = DPT_PATH_MIN; path_type <= DPT_PATH_MAX; path_type++) {
            err =
                put_user(sx_glb.sx_dpt.dpt_info[i].is_ifc_valid[path_type] ? 1 : 0,
                         &(sx_core_db->dpt_info[i].is_ifc_valid[path_type]));
            if (err) {
                goto out;
            }
        }
        err = copy_to_user(sx_core_db->dpt_info[i].is_local, sx_glb.sx_dpt.dpt_info[i].is_local,
                           sizeof(sx_glb.sx_dpt.dpt_info[i].is_local));
        if (err) {
            goto out;
        }
        err = copy_to_user(&(sx_core_db->dpt_info[i].sx_i2c_info), &(sx_glb.sx_dpt.dpt_info[i].sx_i2c_info),
                           sizeof(sx_glb.sx_dpt.dpt_info[i].sx_i2c_info));
        if (err) {
            goto out;
        }
        err = copy_to_user(&(sx_core_db->dpt_info[i].sx_pcie_info), &(sx_glb.sx_dpt.dpt_info[i].sx_pcie_info),
                           sizeof(sx_glb.sx_dpt.dpt_info[i].sx_pcie_info));
        if (err) {
            goto out;
        }
        err = copy_to_user(&(sx_core_db->dpt_info[i].sx_sgmii_info), &(sx_glb.sx_dpt.dpt_info[i].sx_sgmii_info),
                           sizeof(sx_glb.sx_dpt.dpt_info[i].sx_sgmii_info));
        if (err) {
            goto out;
        }
    }

out:
    return err;
}


static int sx_core_ioctl_get_swid_info(struct sx_dev *dev, struct ku_sx_core_db __user *sx_core_db)
{
    int err = 0;
    int i = 0;

    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        err = put_user((uint8_t)(dev->profile.dev_id), &(sx_core_db->swid_data[i].dev_id));
        if (err) {
            goto out;
        }
        err = put_user((uint8_t)i, &(sx_core_db->swid_data[i].swid));
        if (err) {
            goto out;
        }
        err =
            put_user((uint16_t)(sx_priv(dev)->swid_data[i].eth_swid_data.synd),
                     &(sx_core_db->swid_data[i].iptrap_synd));
        if (err) {
            goto out;
        }
        err = put_user((uint64_t)(sx_priv(dev)->swid_data[i].eth_swid_data.mac), &(sx_core_db->swid_data[i].mac));
        if (err) {
            goto out;
        }
        if (sx_bitmap_test(&sx_priv(dev)->swid_bitmap, i)) {
            err = put_user((uint8_t)1, &(sx_core_db->swid_enabled[i]));
        } else {
            err = put_user((uint8_t)0, &(sx_core_db->swid_enabled[i]));
        }
        if (err) {
            goto out;
        }
    }

out:
    return err;
}


static int sx_core_ioctl_get_trap_group_info(struct sx_dev *dev, struct ku_sx_core_db __user *sx_core_db)
{
    int                       i;
    struct ku_access_htgt_reg reg_data;
    int                       err = 0;

    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.dev_id = 255;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, HTGT_REG_ID, 1); /* 1 - query */
    reg_data.htgt_reg.swid = 0;

    for (i = 0; i < NUM_OF_TRAP_GROUPS; i++) {
        reg_data.htgt_reg.trap_group = i;
        err = sx_ACCESS_REG_HTGT(dev, &reg_data);
        if (err) {
            goto out;
        }

        err = copy_to_user(&(sx_core_db->trap_group_info[i]), &(reg_data.htgt_reg),
                           sizeof(reg_data.htgt_reg));
        if (err) {
            goto out;
        }
    }

out:
    return err;
}


static int sx_core_ioctl_get_netdev_trap_info(struct sx_dev *dev, struct ku_sx_core_db __user *sx_core_db)
{
    int                  err = 0;
    union sx_event_data *event_data = NULL;

    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        err = -ENOMEM;
        goto out;
    }

    sx_core_dispatch_event(dev, SX_DEV_EVENT_GET_NETDEV_TRAP_INFO, event_data);

    err = copy_to_user((void*)(sx_core_db->port_vlan_params), (void*)(event_data->netdev_trap_info.port_vlan_params),
                       sizeof(event_data->netdev_trap_info.port_vlan_params));
    if (err) {
        goto out;
    }

    err = copy_to_user((void*)(sx_core_db->trap_ids), (void*)(event_data->netdev_trap_info.trap_ids),
                       sizeof(event_data->netdev_trap_info.trap_ids));
    if (err) {
        goto out;
    }

    err = copy_to_user((void*)(sx_core_db->num_of_traps), (void*)(event_data->netdev_trap_info.num_of_traps),
                       sizeof(event_data->netdev_trap_info.num_of_traps));
    if (err) {
        goto out;
    }

out:
    if (event_data) {
        kfree(event_data);
    }

    return err;
}


static int sx_core_ioctl_get_rdq_properties(struct sx_dev *dev, struct ku_sx_core_db __user *sx_core_db)
{
    int      err = 0;
    uint32_t i;

    err = put_user(sx_priv(dev)->cq_table.ts_bitmap.max, &(sx_core_db->ts_bitmap.max));
    if (err) {
        goto out;
    }
    for (i = 0; i < sx_priv(dev)->cq_table.ts_bitmap.max; i++) {
        if (sx_bitmap_test(&(sx_priv(dev)->cq_table.ts_bitmap), i)) {
            err = put_user((uint8_t)1, &(sx_core_db->ts_bitmap.table[i]));
        } else {
            err = put_user((uint8_t)0, &(sx_core_db->ts_bitmap.table[i]));
        }
        if (err) {
            goto out;
        }
    }

    err =
        put_user(sx_priv(
                     dev)->cq_table.cpu_traffic_prio.high_prio_cq_bitmap.max, &(sx_core_db->high_prio_cq_bitmap.max));
    if (err) {
        goto out;
    }
    for (i = 0; i < sx_priv(dev)->cq_table.cpu_traffic_prio.high_prio_cq_bitmap.max; i++) {
        if (sx_bitmap_test(&(sx_priv(dev)->cq_table.cpu_traffic_prio.high_prio_cq_bitmap), i)) {
            err = put_user((uint8_t)1, &(sx_core_db->high_prio_cq_bitmap.table[i]));
        } else {
            err = put_user((uint8_t)0, &(sx_core_db->high_prio_cq_bitmap.table[i]));
        }
        if (err) {
            goto out;
        }
    }

out:
    return err;
}


#define SX_CORE_IOCTL_MEMCPY(field_name) \
    memcpy(sx_priv(dev)->field_name, sx_core_db->field_name, sizeof(sx_core_db->field_name))

long ctrl_cmd_restore_sx_core_db(struct file *file, unsigned int cmd, unsigned long data)
{
    int                   err = 0;
    struct ku_sx_core_db *sx_core_db = NULL;
    struct ku_sx_core_db  __user *sx_core_db_user = (struct ku_sx_core_db __user*)(data);
    struct sx_dev        *dev;
    int                   i;
    unsigned long         flags;
    bool                  db_locked = false;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    spin_lock(&dev->profile_lock);
    if (dev->profile_set) {
        spin_unlock(&dev->profile_lock);
        return -EINVAL;
    }
    spin_unlock(&dev->profile_lock);

    sx_core_db = vmalloc(sizeof(struct ku_sx_core_db));
    if (!sx_core_db) {
        printk(KERN_DEBUG PFX "can't vmalloc sx_core_db\n");
        err = -ENOMEM;
        goto out;
    }

    err = copy_from_user(sx_core_db, (void*)data, sizeof(struct ku_sx_core_db));
    if (err) {
        goto out;
    }

    if ((sx_core_db->magic_start != SX_CORE_DB_MAGIC_NUM) || (sx_core_db->magic_end != SX_CORE_DB_MAGIC_NUM)) {
        printk(KERN_ERR PFX "The sx_core_db magic number is incorrect.\n");
        err = -EINVAL;
        goto out;
    }

    err = sx_core_ioctl_set_dpt_info(dev, sx_core_db);
    if (err) {
        goto out;
    }

    err = sx_core_ioctl_set_pci_profile(dev, (unsigned long)(&(sx_core_db_user->profile.profile)), 0);
    if (err) {
        goto out;
    }

    for (i = 0; i < NUMBER_OF_SWIDS; i++) {
        if (sx_core_db->swid_enabled[i]) {
            err = sx_core_ioctl_enable_swid(dev, (unsigned long)(&(sx_core_db_user->swid_data[i])));
            if (err) {
                goto out;
            }
        }
    }

    err = sx_core_ioctl_set_trap_group_info(dev, sx_core_db);
    if (err) {
        goto out;
    }

    err = sx_core_ioctl_set_netdev_trap_info(dev, sx_core_db);
    if (err) {
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    db_locked = true;
    SX_CORE_IOCTL_MEMCPY(sysport_filter_db);
    SX_CORE_IOCTL_MEMCPY(lag_filter_db);
    SX_CORE_IOCTL_MEMCPY(pvid_sysport_db);
    SX_CORE_IOCTL_MEMCPY(pvid_lag_db);
    SX_CORE_IOCTL_MEMCPY(port_vtag_mode);
    SX_CORE_IOCTL_MEMCPY(lag_vtag_mode);
    SX_CORE_IOCTL_MEMCPY(port_prio_tagging_mode);
    SX_CORE_IOCTL_MEMCPY(lag_prio_tagging_mode);
    SX_CORE_IOCTL_MEMCPY(port_prio2tc);
    SX_CORE_IOCTL_MEMCPY(lag_prio2tc);
    SX_CORE_IOCTL_MEMCPY(local_to_swid_db);
    SX_CORE_IOCTL_MEMCPY(ib_to_local_db);
    SX_CORE_IOCTL_MEMCPY(system_to_local_db);
    SX_CORE_IOCTL_MEMCPY(local_to_system_db);
    SX_CORE_IOCTL_MEMCPY(lag_is_rp);
    SX_CORE_IOCTL_MEMCPY(lag_rp_vid);
    SX_CORE_IOCTL_MEMCPY(lag_rp_rif);
    SX_CORE_IOCTL_MEMCPY(lag_rp_rif_valid);
    SX_CORE_IOCTL_MEMCPY(lag_member_to_local_db);
    SX_CORE_IOCTL_MEMCPY(local_is_rp);
    SX_CORE_IOCTL_MEMCPY(local_rp_vid);
    SX_CORE_IOCTL_MEMCPY(port_rp_rif);
    SX_CORE_IOCTL_MEMCPY(port_rp_rif_valid);
    SX_CORE_IOCTL_MEMCPY(lag_oper_state);
    SX_CORE_IOCTL_MEMCPY(port_ber_monitor_state);
    SX_CORE_IOCTL_MEMCPY(port_ber_monitor_bitmask);
    SX_CORE_IOCTL_MEMCPY(tele_thrs_state);
    SX_CORE_IOCTL_MEMCPY(tele_thrs_tc_vec);
    SX_CORE_IOCTL_MEMCPY(truncate_size_db);
    SX_CORE_IOCTL_MEMCPY(icmp_vlan2ip_db);
    SX_CORE_IOCTL_MEMCPY(port_vid_to_fid);
    SX_CORE_IOCTL_MEMCPY(fid_to_hwfid);
    SX_CORE_IOCTL_MEMCPY(rif_id_to_hwfid);
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
    db_locked = false;

    err = sx_core_ioctl_set_rdq_properties(dev, sx_core_db);
    if (err) {
        goto out;
    }

out:
    if (sx_core_db) {
        vfree(sx_core_db);
    }

    if (db_locked) {
        spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
    }

    return err;
}


#define SX_CORE_IOCTL_COPY_TO_USER(field_name)                                             \
    err = copy_to_user((void*)(sx_core_db->field_name), (void*)(sx_priv(dev)->field_name), \
                       sizeof(sx_priv(dev)->field_name));                                  \
    if (err) {                                                                             \
        goto out;                                                                          \
    }

long ctrl_cmd_save_sx_core_db(struct file *file, unsigned int cmd, unsigned long data)
{
    int                  err = 0;
    struct ku_sx_core_db __user *sx_core_db = (struct ku_sx_core_db*)(data);
    struct sx_dev       *dev;
    unsigned long        flags;
    bool                 db_locked = false;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = sx_core_ioctl_get_dpt_info(dev, sx_core_db);
    if (err) {
        goto out;
    }

    err = sx_core_ioctl_get_pci_profile(dev, (unsigned long)(&(sx_core_db->profile)));
    if (err) {
        goto out;
    }

    err = sx_core_ioctl_get_swid_info(dev, sx_core_db);
    if (err) {
        goto out;
    }

    err = sx_core_ioctl_get_trap_group_info(dev, sx_core_db);
    if (err) {
        goto out;
    }

    err = sx_core_ioctl_get_netdev_trap_info(dev, sx_core_db);
    if (err) {
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    db_locked = true;
    SX_CORE_IOCTL_COPY_TO_USER(sysport_filter_db);
    SX_CORE_IOCTL_COPY_TO_USER(lag_filter_db);
    SX_CORE_IOCTL_COPY_TO_USER(pvid_sysport_db);
    SX_CORE_IOCTL_COPY_TO_USER(pvid_lag_db);
    SX_CORE_IOCTL_COPY_TO_USER(port_vtag_mode);
    SX_CORE_IOCTL_COPY_TO_USER(lag_vtag_mode);
    SX_CORE_IOCTL_COPY_TO_USER(port_prio_tagging_mode);
    SX_CORE_IOCTL_COPY_TO_USER(lag_prio_tagging_mode);
    SX_CORE_IOCTL_COPY_TO_USER(port_prio2tc);
    SX_CORE_IOCTL_COPY_TO_USER(lag_prio2tc);
    SX_CORE_IOCTL_COPY_TO_USER(local_to_swid_db);
    SX_CORE_IOCTL_COPY_TO_USER(ib_to_local_db);
    SX_CORE_IOCTL_COPY_TO_USER(system_to_local_db);
    SX_CORE_IOCTL_COPY_TO_USER(local_to_system_db);
    SX_CORE_IOCTL_COPY_TO_USER(lag_is_rp);
    SX_CORE_IOCTL_COPY_TO_USER(lag_rp_vid);
    SX_CORE_IOCTL_COPY_TO_USER(lag_rp_rif);
    SX_CORE_IOCTL_COPY_TO_USER(lag_rp_rif_valid);
    SX_CORE_IOCTL_COPY_TO_USER(lag_member_to_local_db);
    SX_CORE_IOCTL_COPY_TO_USER(local_is_rp);
    SX_CORE_IOCTL_COPY_TO_USER(local_rp_vid);
    SX_CORE_IOCTL_COPY_TO_USER(port_rp_rif);
    SX_CORE_IOCTL_COPY_TO_USER(port_rp_rif_valid);
    SX_CORE_IOCTL_COPY_TO_USER(lag_oper_state);
    SX_CORE_IOCTL_COPY_TO_USER(port_ber_monitor_state);
    SX_CORE_IOCTL_COPY_TO_USER(port_ber_monitor_bitmask);
    SX_CORE_IOCTL_COPY_TO_USER(tele_thrs_state);
    SX_CORE_IOCTL_COPY_TO_USER(tele_thrs_tc_vec);
    SX_CORE_IOCTL_COPY_TO_USER(truncate_size_db);
    SX_CORE_IOCTL_COPY_TO_USER(icmp_vlan2ip_db);
    SX_CORE_IOCTL_COPY_TO_USER(port_vid_to_fid);
    SX_CORE_IOCTL_COPY_TO_USER(fid_to_hwfid);
    SX_CORE_IOCTL_COPY_TO_USER(rif_id_to_hwfid);
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
    db_locked = false;

    err = sx_core_ioctl_get_rdq_properties(dev, sx_core_db);
    if (err) {
        goto out;
    }

    err = put_user(SX_CORE_DB_MAGIC_NUM, &(sx_core_db->magic_start));
    if (err) {
        goto out;
    }

    err = put_user(SX_CORE_DB_MAGIC_NUM, &(sx_core_db->magic_end));
    if (err) {
        goto out;
    }

out:
    if (db_locked) {
        spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
    }
    return err;
}


long ctrl_cmd_get_sx_core_db_restore_allowed(struct file *file, unsigned int cmd, unsigned long data)
{
    uint8_t        restore_allowed;
    struct sx_dev *dev;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    spin_lock(&dev->profile_lock);
    restore_allowed = !(dev->profile_set);
    spin_unlock(&dev->profile_lock);

    return copy_to_user((uint8_t*)data, &restore_allowed, sizeof(restore_allowed));
}


static int __validate_phy_port(struct sx_dev *dev, uint16_t port)
{
    uint16_t phy_port_max;
    int      err;

    err = sx_core_get_phy_port_max(dev, &phy_port_max);
    if (err) {
        return err;
    }

    return (port <= phy_port_max) ? 0 : -EINVAL;
}


static int __validate_lag(struct sx_dev *dev, uint16_t lag_id, uint16_t lag_member)
{
    uint16_t lag_max, lag_member_max;
    int      err;

    err = sx_core_get_lag_max(dev, &lag_max, &lag_member_max);
    if (err) {
        return err;
    }

    return (lag_id < lag_max && lag_member < lag_member_max) ? 0 : -EINVAL;
}


long ctrl_cmd_set_vid_membership(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_vid_membership_data vid_data;
    struct sx_dev                *dev;
    unsigned long                 flags;
    int                           err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&vid_data, (void*)data, sizeof(vid_data));
    if (err) {
        goto out;
    }

    if (vid_data.is_lag) {
        err = __validate_lag(dev, vid_data.lag_id, 0);
    } else {
        err = __validate_phy_port(dev, vid_data.phy_port);
    }

    if (err) {
        printk(KERN_ERR "validation error: is_lag:%u, lag_id:%u, phy_port=%u",
               vid_data.is_lag, vid_data.lag_id, vid_data.phy_port);
        goto out;
    }

    if (vid_data.vid >= SXD_MAX_VLAN_NUM) {
        printk(KERN_ERR PFX "Received VID %d is invalid\n", vid_data.vid);
        err = -EINVAL;
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (vid_data.is_lag) {
        sx_priv(dev)->lag_vtag_mode[vid_data.lag_id][vid_data.vid] = vid_data.is_tagged;
    } else {
        sx_priv(dev)->port_vtag_mode[vid_data.phy_port][vid_data.vid] = vid_data.is_tagged;
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

out:
    return err;
}


long ctrl_cmd_set_prio_tagging(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_prio_tagging_data prio_tag_data;
    struct sx_dev              *dev;
    unsigned long               flags;
    int                         err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&prio_tag_data, (void*)data, sizeof(prio_tag_data));
    if (err) {
        goto out;
    }

    if (prio_tag_data.is_lag) {
        err = __validate_lag(dev, prio_tag_data.lag_id, 0);
    } else {
        err = __validate_phy_port(dev, prio_tag_data.phy_port);
    }

    if (err) {
        printk(KERN_ERR "validation error: is_lag:%u, lag_id:%u, phy_port=%u",
               prio_tag_data.is_lag, prio_tag_data.lag_id, prio_tag_data.phy_port);
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (prio_tag_data.is_lag) {
        sx_priv(dev)->lag_prio_tagging_mode[prio_tag_data.lag_id] = prio_tag_data.is_prio_tagged;
    } else {
        sx_priv(dev)->port_prio_tagging_mode[prio_tag_data.phy_port] = prio_tag_data.is_prio_tagged;
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

out:
    return err;
}


long ctrl_cmd_set_prio_to_tc(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_prio_to_tc_data prio_to_tc_data;
    struct sx_dev            *dev;
    unsigned long             flags;
    int                       err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&prio_to_tc_data, (void*)data, sizeof(prio_to_tc_data));
    if (err) {
        goto out;
    }

    if (prio_to_tc_data.is_lag) {
        err = __validate_lag(dev, prio_to_tc_data.lag_id, 0);
    } else {
        err = __validate_phy_port(dev, prio_to_tc_data.phy_port);
    }

    if (err) {
        printk(KERN_ERR "validation error: is_lag:%u, lag_id:%u, phy_port=%u",
               prio_to_tc_data.is_lag, prio_to_tc_data.lag_id, prio_to_tc_data.phy_port);
        goto out;
    }

    if (prio_to_tc_data.priority > MAX_PRIO_NUM) {
        printk(KERN_ERR PFX "Received PRIO %d is invalid (MAX %d). \n", prio_to_tc_data.priority, MAX_PRIO_NUM);
        err = -EINVAL;
        goto out;
    }

    if (prio_to_tc_data.traffic_class > (NUMBER_OF_ETCLASSES - 1)) {
        printk(KERN_ERR PFX "Received TC %d is invalid (MAX %d).\n",
               prio_to_tc_data.traffic_class,
               (NUMBER_OF_ETCLASSES - 1));
        err = -EINVAL;
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (prio_to_tc_data.is_lag) {
        sx_priv(dev)->lag_prio2tc[prio_to_tc_data.lag_id][prio_to_tc_data.priority] = prio_to_tc_data.traffic_class;
    } else {
        sx_priv(dev)->port_prio2tc[prio_to_tc_data.phy_port][prio_to_tc_data.priority] = prio_to_tc_data.traffic_class;
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

out:
    return err;
}


long ctrl_cmd_set_local_port_to_swid(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_local_port_swid_data local_port_swid_data;
    struct sx_dev                 *dev;
    int                            err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&local_port_swid_data, (void*)data, sizeof(local_port_swid_data));
    if (err) {
        goto out;
    }

    err = __validate_phy_port(dev, local_port_swid_data.local_port);
    if (err) {
        printk(KERN_ERR PFX "Received Local port 0x%x is invalid\n",
               local_port_swid_data.local_port);
        goto out;
    }

    sx_priv(dev)->local_to_swid_db[local_port_swid_data.local_port] = local_port_swid_data.swid;

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX " sx_ioctl() (PSPA) LOC_PORT_TO_SWID lp:%d, swid: %d \n",
           local_port_swid_data.local_port,
           local_port_swid_data.swid);
#endif

out:
    return err;
}


long ctrl_cmd_set_ib_to_local_port(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_ib_local_port_data ib_local_port_data;
    struct sx_dev               *dev;
    int                          err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&ib_local_port_data, (void*)data, sizeof(ib_local_port_data));
    if (err) {
        goto out;
    }

    err = __validate_phy_port(dev, ib_local_port_data.local_port);
    if (err) {
        printk(KERN_ERR PFX "Received Local port 0x%x is invalid\n", ib_local_port_data.local_port);
        goto out;
    }

    if (ib_local_port_data.ib_port > MAX_IBPORT_NUM) {
        printk(KERN_ERR PFX "Received IB port 0x%x is invalid (max. %d) \n",
               ib_local_port_data.ib_port,
               MAX_IBPORT_NUM);
        err = -EINVAL;
        goto out;
    }

    sx_priv(dev)->ib_to_local_db[ib_local_port_data.ib_port] = ib_local_port_data.local_port;

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX " sx_ioctl() (PLIB) IB_TO_LOCAL_PORT ib_p:%d, lc_p:%d \n",
           ib_local_port_data.ib_port,
           ib_local_port_data.local_port);
#endif

out:
    return err;
}


long ctrl_cmd_set_system_to_local_port(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_system_local_port_data system_local_port_data;
    struct sx_dev                   *dev;
    unsigned long                    flags;
    int                              err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&system_local_port_data, (void*)data, sizeof(system_local_port_data));
    if (err) {
        goto out;
    }

    err = __validate_phy_port(dev, system_local_port_data.local_port);
    if (err) {
        printk(KERN_ERR PFX "Received Local port 0x%x is invalid\n", system_local_port_data.local_port);
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    sx_priv(dev)->system_to_local_db[system_local_port_data.system_port] = system_local_port_data.local_port;
    sx_priv(dev)->local_to_system_db[system_local_port_data.local_port] = system_local_port_data.system_port;
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX " sx_ioctl() (SSPR) SYSTEM_TO_LOCAL_PORT sys_p:0x%x, lc_p:%d \n",
           system_local_port_data.system_port,
           system_local_port_data.local_port);
#endif

out:
    return err;
}


long ctrl_cmd_set_port_rp_mode(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_port_rp_mode_data port_rp_mode_data;
    struct sx_dev              *dev;
    unsigned long               flags;
    uint16_t                    lag_max = 0, lag_member_max = 0;
    uint16_t                    phy_port_max = 0;
    uint16_t                    local_port;
    uint8_t                     lag_port_index;
    int                         err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&port_rp_mode_data, (void*)data, sizeof(port_rp_mode_data));
    if (err) {
        goto out;
    }

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        printk(KERN_ERR PFX "Failed to get max number of phy ports.\n");
        err = -EINVAL;
        goto out;
    }

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        printk(KERN_ERR PFX "Failed to get max number of LAGs.\n");
        err = -EINVAL;
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    if (port_rp_mode_data.is_lag) {
        if (port_rp_mode_data.lag_id >= lag_max) {
            printk(KERN_ERR PFX "Received LAG ID 0x%x is invalid\n", port_rp_mode_data.lag_id);
            err = -EINVAL;
            goto out_unlock;
        }

        sx_priv(dev)->lag_is_rp[port_rp_mode_data.lag_id] = port_rp_mode_data.is_rp;
        sx_priv(dev)->lag_rp_vid[port_rp_mode_data.lag_id] = port_rp_mode_data.vlan_id;
        sx_priv(dev)->lag_rp_rif[port_rp_mode_data.lag_id][port_rp_mode_data.vlan_id] = port_rp_mode_data.rif_id;
        /* If opcode = create = 0, set IS_RP value,
         * else opcode = delete = 1, set DONT_CARE value */
        sx_priv(dev)->lag_rp_rif_valid[port_rp_mode_data.lag_id][port_rp_mode_data.vlan_id] =
            port_rp_mode_data.is_valid;

        for (lag_port_index = 0; lag_port_index < lag_member_max; lag_port_index++) {
            local_port = sx_priv(dev)->lag_member_to_local_db[port_rp_mode_data.lag_id][lag_port_index];

            /* if the LAG is RP than assign swid 0 to this local port ,
             * because we want all RP traffic to arrive with swid 0 */
            if (local_port != 0) {
                if (port_rp_mode_data.is_rp) {
                    sx_priv(dev)->local_to_swid_db[local_port] = ROUTER_PORT_SWID;
                } else {
                    sx_priv(dev)->local_to_swid_db[local_port] = 255;
                }
            }
        }
    } else {
        local_port = sx_priv(dev)->system_to_local_db[port_rp_mode_data.sysport];

        if (local_port > phy_port_max) {
            printk(KERN_ERR PFX "Received Local %d is invalid. (MAX %d).\n", local_port, phy_port_max);
            err = -EINVAL;
            goto out_unlock;
        }

        sx_priv(dev)->local_is_rp[local_port] = port_rp_mode_data.is_rp;
        sx_priv(dev)->local_rp_vid[local_port] = port_rp_mode_data.vlan_id;
        sx_priv(dev)->port_rp_rif[local_port][port_rp_mode_data.vlan_id] = port_rp_mode_data.rif_id;

        /* If opcode = create = 0, set IS_RP value,
         * else opcode = delete = 1, set DONT_CARE value */
        sx_priv(dev)->port_rp_rif_valid[local_port][port_rp_mode_data.vlan_id] = port_rp_mode_data.is_valid;
        if (port_rp_mode_data.is_rp) {
            sx_priv(dev)->local_to_swid_db[local_port] = ROUTER_PORT_SWID;
        } else {
            sx_priv(dev)->local_to_swid_db[local_port] = 255;
        }
    }

    sx_priv(dev)->rif_id_to_hwfid[port_rp_mode_data.rif_id] = port_rp_mode_data.hw_efid;

out_unlock:
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

out:
    return err;
}


long ctrl_cmd_set_local_port_to_lag(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_local_port_to_lag_data local_to_lag_data;
    struct sx_dev                   *dev;
    unsigned long                    flags;
    uint16_t                         lag_id;
    uint16_t                         lag_port_index;
    int                              err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&local_to_lag_data, (void*)data, sizeof(local_to_lag_data));
    if (err) {
        goto out;
    }

    err = __validate_phy_port(dev, local_to_lag_data.local_port);
    if (err) {
        printk(KERN_ERR PFX "Received Local port 0x%x is invalid\n", local_to_lag_data.local_port);
        goto out;
    }

    err = __validate_lag(dev, local_to_lag_data.lag_id, local_to_lag_data.lag_port_index);
    if (err) {
        printk(KERN_ERR PFX "Received either invalid LAG ID 0x%x or invalid lag member (0x%x)\n",
               local_to_lag_data.lag_id, local_to_lag_data.lag_port_index);
        goto out;
    }

    lag_id = local_to_lag_data.lag_id;
    lag_port_index = local_to_lag_data.lag_port_index;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (local_to_lag_data.is_lag) {
        /* Adding the port to LAG */
        sx_priv(dev)->lag_member_to_local_db[lag_id][lag_port_index] = local_to_lag_data.local_port;

        /* if the LAG is RP than assign swid 0 to this local port ,
         * because we want all RP traffic to arrive with swid 0 */
        if (sx_priv(dev)->lag_is_rp[lag_id]) {
            sx_priv(dev)->local_to_swid_db[local_to_lag_data.local_port] = ROUTER_PORT_SWID;
        }
    } else {
        /* Removing the port from LAG */
        sx_priv(dev)->lag_member_to_local_db[lag_id][lag_port_index] = 0;

        /* if the LAG is RP than assign swid 255 to this local port ,
         * because we want all RP traffic to arrive with swid 0 */
        if (sx_priv(dev)->lag_is_rp[lag_id]) {
            sx_priv(dev)->local_to_swid_db[local_to_lag_data.local_port] = 255;
        }
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX " sx_ioctl() (SLCOR) LOCAL_PORT_TO_LAG is_lag:%d,lid:%d,port_id:%x,loc_port:%d\n",
           local_to_lag_data.is_lag,
           lag_id,
           lag_port_index,
           local_to_lag_data.local_port);
#endif

out:
    return err;
}


long ctrl_cmd_lag_oper_state_set(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_lag_oper_state_data lag_oper_state_data;
    union sx_event_data          *lag_state_event_data = NULL;
    struct sx_dev                *dev;
    unsigned long                 flags;
    int                           err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&lag_oper_state_data, (void*)data, sizeof(lag_oper_state_data));
    if (err) {
        goto out;
    }

    err = __validate_lag(dev, lag_oper_state_data.lag_id, 0);
    if (err) {
        printk(KERN_ERR PFX "Received LAG ID %d is invalid\n", lag_oper_state_data.lag_id);
        goto out;
    }

    lag_state_event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!lag_state_event_data) {
        err = -ENOMEM;
        goto out;
    }

    lag_state_event_data->lag_oper_state_set.lag_id = lag_oper_state_data.lag_id;
    lag_state_event_data->lag_oper_state_set.oper_state = lag_oper_state_data.oper_state;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    sx_priv(dev)->lag_oper_state[lag_oper_state_data.lag_id] = lag_oper_state_data.oper_state;
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

    sx_core_dispatch_event(dev, SX_DEV_EVENT_LAG_OPER_STATE_UPDATE, lag_state_event_data);
    kfree(lag_state_event_data);

out:
    return err;
}


long ctrl_cmd_port_ber_monitor_state_set(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_ber_monitor_state_data ber_monitor_state_data;
    struct sx_dev                   *dev;
    unsigned long                    flags;
    int                              err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&ber_monitor_state_data, (void*)data, sizeof(ber_monitor_state_data));
    if (err) {
        goto out;
    }

    if (ber_monitor_state_data.local_port > MAX_PHYPORT_NUM) {
        printk(KERN_ERR PFX "Received local_port %d is invalid (max. %d) \n",
               ber_monitor_state_data.local_port,
               MAX_PHYPORT_NUM);
        err = -EINVAL;
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    sx_priv(dev)->port_ber_monitor_state[ber_monitor_state_data.local_port] = ber_monitor_state_data.ber_monitor_state;
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

out:
    return err;
}


long ctrl_cmd_port_ber_monitor_bitmask_set(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_ber_monitor_bitmask_data ber_monitor_bitmask_data;
    struct sx_dev                     *dev;
    unsigned long                      flags;
    int                                err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&ber_monitor_bitmask_data, (void*)data, sizeof(ber_monitor_bitmask_data));
    if (err) {
        goto out;
    }

    if (ber_monitor_bitmask_data.local_port > MAX_PHYPORT_NUM) {
        printk(KERN_ERR PFX "Received local_port %d is invalid (max. %d) \n",
               ber_monitor_bitmask_data.local_port,
               MAX_PHYPORT_NUM);
        err = -EINVAL;
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    sx_priv(dev)->port_ber_monitor_bitmask[ber_monitor_bitmask_data.local_port] = ber_monitor_bitmask_data.bitmask;
    /* If BER monitor is disable: clear the operational state */
    if (ber_monitor_bitmask_data.bitmask == 0) {
        sx_priv(dev)->port_ber_monitor_state[ber_monitor_bitmask_data.local_port] = 0;
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

out:
    return err;
}


long ctrl_cmd_tele_threshold_set(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_tele_threshold_data tele_thrs_data;
    struct sx_dev                *dev;
    unsigned long                 flags;
    int                           err;

    printk(KERN_DEBUG PFX "ioctl CTRL_CMD_TELE_THRESHOLD_SET called\n");

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&tele_thrs_data, (void*)data, sizeof(tele_thrs_data));
    if (err) {
        goto out;
    }

    if (tele_thrs_data.local_port > MAX_PHYPORT_NUM) {
        printk(KERN_ERR PFX "Received local_port %d is invalid (max. %d) \n",
               tele_thrs_data.local_port,
               MAX_PHYPORT_NUM);
        err = -EINVAL;
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (tele_thrs_data.tc_vec == 0) {
        sx_priv(dev)->tele_thrs_state[tele_thrs_data.local_port] = 0;
        /* We clear tc vector DB only if all TCs were removed */
        sx_priv(dev)->tele_thrs_tc_vec[tele_thrs_data.local_port] = 0;
    } else {
        SX_TELE_THRS_VALID_SET(sx_priv(dev)->tele_thrs_state[tele_thrs_data.local_port]);
    }
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

out:
    return err;
}


long ctrl_cmd_set_vid_2_ip(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_vid2ip_data vid2ip_data;
    struct sx_dev        *dev;
    unsigned long         flags;
    int                   err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&vid2ip_data, (void*)data, sizeof(vid2ip_data));
    if (err) {
        goto out;
    }

    if (vid2ip_data.vid >= SXD_MAX_VLAN_NUM) {
        printk(KERN_ERR PFX "Received VID %d is invalid\n", vid2ip_data.vid);
        err = -EINVAL;
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    if (vid2ip_data.valid) {
        sx_priv(dev)->icmp_vlan2ip_db[vid2ip_data.vid] = vid2ip_data.ip_addr;
    } else {
        sx_priv(dev)->icmp_vlan2ip_db[vid2ip_data.vid] = 0;
    }

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

out:
    return err;
}


long ctrl_cmd_set_port_vid_to_fid_map(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_port_vlan_to_fid_map_data port_vlan_to_fid_map_data;
    struct sx_dev                      *dev;
    unsigned long                       flags;
    uint16_t                            phy_port_max = 0;
    int                                 err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&port_vlan_to_fid_map_data, (void*)data, sizeof(port_vlan_to_fid_map_data));
    if (err) {
        goto out;
    }

    err = __validate_phy_port(dev, port_vlan_to_fid_map_data.local_port);
    if (err) {
        printk(KERN_ERR PFX "Received Local port 0x%x is invalid (max. %d) \n",
               port_vlan_to_fid_map_data.local_port,
               phy_port_max);
        goto out;
    }

    if (port_vlan_to_fid_map_data.vid >= SXD_MAX_VLAN_NUM) {
        printk(KERN_ERR PFX "Received VID %d is invalid\n", port_vlan_to_fid_map_data.vid);
        err = -EINVAL;
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    if (port_vlan_to_fid_map_data.is_mapped_to_fid) {
        sx_priv(dev)->port_vid_to_fid[port_vlan_to_fid_map_data.local_port][port_vlan_to_fid_map_data.vid] =
            port_vlan_to_fid_map_data.fid;
    } else {
        sx_priv(dev)->port_vid_to_fid[port_vlan_to_fid_map_data.local_port][port_vlan_to_fid_map_data.vid] = 0;
    }

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

out:
    return err;
}


long ctrl_cmd_set_fid_to_hwfid_map(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_fid_to_hwfid_map_data fid_to_hwfid_map_data;
    struct sx_dev                  *dev;
    unsigned long                   flags;
    int                             err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&fid_to_hwfid_map_data, (void*)data, sizeof(fid_to_hwfid_map_data));
    if (err) {
        goto out;
    }

    if (fid_to_hwfid_map_data.fid >= MAX_FIDS_NUM) {
        printk(KERN_ERR PFX "Received FID %u is out of the range[0-%u]\n",
               fid_to_hwfid_map_data.fid,
               MAX_FIDS_NUM);
        err = -EINVAL;
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    sx_priv(dev)->fid_to_hwfid[fid_to_hwfid_map_data.fid] = fid_to_hwfid_map_data.hw_fid;
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

out:
    return err;
}


long ctrl_cmd_set_default_vid(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_default_vid_data default_vid_data;
    struct sx_dev             *dev;
    unsigned long              flags;
    int                        err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&default_vid_data, (void*)data, sizeof(default_vid_data));
    if (err) {
        goto out;
    }

    if (default_vid_data.is_lag) {
        err = __validate_lag(dev, default_vid_data.lag_id, 0);
        if (err) {
            printk(KERN_ERR PFX "Received LAG ID 0x%x is invalid\n", default_vid_data.lag_id);
            goto out;
        }
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (default_vid_data.is_lag) {
        sx_priv(dev)->pvid_lag_db[default_vid_data.lag_id] = default_vid_data.default_vid;
    } else {
        sx_priv(dev)->pvid_sysport_db[default_vid_data.sysport] = default_vid_data.default_vid;
    }

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

out:
    return err;
}
