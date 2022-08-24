/*
 * Copyright © 2010-2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include <linux/version.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/if_arp.h>
#include <linux/rtnetlink.h>
#include <linux/netlink.h>
#include <net/netlink.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/skb_hook.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/cmd.h>
#include "sx_spice_tree_auto.h"
#include "sx_spice_wrapper.h"
#include "sx_spice_access_reg_auto.h"

MODULE_AUTHOR("Lior Kaplan");
MODULE_DESCRIPTION("Spice-Dump driver");
MODULE_LICENSE("Dual BSD/GPL");

/************************************************
 *  Local variables
 ***********************************************/
struct sx_dev * g_sx_dev = NULL;

struct kmem_cache *__kbuffer_cache;

bool g_system_info_init_done = false;


/************************************************
 *  Type definitions
 ***********************************************/

/************************************************
 * Functions                                    *
 ***********************************************/

int __sx_spice_system_type_get(uint16_t *dev_id);
int __sx_spice_tree_create(void);


static void * sx_spice_register(struct sx_dev *dev)
{
    g_sx_dev = dev;
    return 0;
}

static void sx_spice_unregister(struct sx_dev *dev, void *rsc)
{
    g_sx_dev = NULL;
}

static struct sx_interface sx_spice_interface = {
    .add = sx_spice_register,
    .remove = sx_spice_unregister
};

static int cache_create(void)
{
    __kbuffer_cache = kmem_cache_create("spice_kbuffer", sizeof(char) * KERNEL_BUFFER_SIZE, 0, 0, NULL);
    if (!__kbuffer_cache) {
        printk(KERN_ERR "failed to allocate memory cache for spice kernel buffer\n");
        return -ENOMEM;
    }
    return 0;
}

static void cache_destroy(void)
{
    if (__kbuffer_cache) {
        kmem_cache_destroy(__kbuffer_cache);
    }
}

int sx_spice_sxd_access(sxd_params_t *params, void * reg_data)
{
    int err = 0;

    switch (params->reg_id) {
    case MLXSW_PDDR_ID:
        err = sx_ACCESS_REG_PDDR(params->g_sx_dev, (struct ku_access_pddr_reg *)reg_data);
        if (err) {
            printk(KERN_ERR "SPICE: sx_ACCESS_REG_PDDR failed with err: %d\n", err);
            goto out;
        }
        if (((struct ku_access_pddr_reg *)reg_data)->op_tlv.status) {
            goto fw_error;
        }
        break;

    case MLXSW_PPCNT_ID:
        err = sx_ACCESS_REG_PPCNT(params->g_sx_dev, (struct ku_access_ppcnt_reg *)reg_data);
        if (err) {
            printk(KERN_ERR "SPICE: sx_ACCESS_REG_PPCNT failed with err: %d\n", err);
            goto out;
        }
        if (((struct ku_access_ppcnt_reg *)reg_data)->op_tlv.status) {
            goto fw_error;
        }
        break;

    case MLXSW_PMDR_ID:
        err = sx_ACCESS_REG_PMDR(params->g_sx_dev, (struct ku_access_pmdr_reg *)reg_data);
        if (err) {
            printk(KERN_ERR "SPICE: sx_ACCESS_REG_PMDR failed with err: %d\n", err);
            goto out;
        }
        if (((struct ku_access_pmdr_reg *)reg_data)->op_tlv.status) {
            goto fw_error;
        }
        break;

    case MLXSW_PTYS_ID:
        err = sx_ACCESS_REG_PTYS(params->g_sx_dev, (struct ku_access_ptys_reg *)reg_data);
        if (err) {
            printk(KERN_ERR "SPICE: sx_ACCESS_REG_PTYS failed with err: %d\n", err);
            goto out;
        }
        if (((struct ku_access_ptys_reg *)reg_data)->op_tlv.status) {
            goto fw_error;
        }
        break;

    case MLXSW_MSGI_ID:
        err = sx_ACCESS_REG_MSGI(params->g_sx_dev, (struct ku_access_msgi_reg *)reg_data);
        if (err) {
            printk(KERN_ERR "SPICE: sx_ACCESS_REG_MSGI failed with err: %d\n", err);
            goto out;
        }
        if (((struct ku_access_msgi_reg *)reg_data)->op_tlv.status) {
            goto fw_error;
        }
        break;

    case MLXSW_MGIR_ID:
        err = sx_ACCESS_REG_MGIR(params->g_sx_dev, (struct ku_access_mgir_reg *)reg_data);
        if (err) {
            printk(KERN_ERR "SPICE: sx_ACCESS_REG_MGIR failed with err: %d\n", err);
            goto out;
        }
        if (((struct ku_access_mgir_reg *)reg_data)->op_tlv.status) {
            goto fw_error;
        }
        break;

    case MLXSW_MDIR_ID:
        err = sx_ACCESS_REG_MDIR(params->g_sx_dev, (struct ku_access_mdir_reg *)reg_data);
        if (err) {
            printk(KERN_ERR "SPICE: sx_ACCESS_REG_MDIR failed with err: %d\n", err);
            goto out;
        }
        if (((struct ku_access_mdir_reg *)reg_data)->op_tlv.status) {
            goto fw_error;
        }
        break;

    case MLXSW_MVCAP_ID:
        err = sx_ACCESS_REG_MVCAP(params->g_sx_dev, (struct ku_access_mvcap_reg *)reg_data);
        if (err) {
            printk(KERN_ERR "SPICE: sx_ACCESS_REG_MVCAP failed with err: %d\n", err);
            goto out;
        }
        if (((struct ku_access_mvcap_reg *)reg_data)->op_tlv.status) {
            goto fw_error;
        }
        break;

    case MLXSW_SLTP_ID:
        err = sx_ACCESS_REG_SLTP(params->g_sx_dev, (struct ku_access_sltp_reg *)reg_data);
        if (err) {
            printk(KERN_ERR "SPICE: sx_ACCESS_REG_SLTP failed with err: %d\n", err);
            goto out;
        }
        if (((struct ku_access_sltp_reg *)reg_data)->op_tlv.status) {
            goto fw_error;
        }
        break;

    case MLXSW_SLLM_ID:
        err = sx_ACCESS_REG_SLLM(params->g_sx_dev, (struct ku_access_sllm_reg *)reg_data);
        if (err) {
            printk(KERN_ERR "SPICE: sx_ACCESS_REG_SLLM failed with err: %d\n", err);
            goto out;
        }
        if (((struct ku_access_sllm_reg *)reg_data)->op_tlv.status) {
            goto fw_error;
        }
        break;

    case MLXSW_SPAD_ID:
        err = sx_ACCESS_REG_SPAD(params->g_sx_dev, (struct ku_access_spad_reg *)reg_data);
        if (err) {
            printk(KERN_ERR "SPICE: sx_ACCESS_REG_SPAD failed with err: %d\n", err);
            goto out;
        }
        if (((struct ku_access_spad_reg *)reg_data)->op_tlv.status) {
            goto fw_error;
        }
        break;

    case MLXSW_SPZR_ID:
        err = sx_ACCESS_REG_SPZR(params->g_sx_dev, (struct ku_access_spzr_reg *)reg_data);
        if (err) {
            printk(KERN_ERR "SPICE: sx_ACCESS_REG_SPZR failed with err: %d\n", err);
            goto out;
        }
        if (((struct ku_access_spzr_reg *)reg_data)->op_tlv.status) {
            goto fw_error;
        }
        break;

    case MLXSW_MTCAP_ID:
        err = sx_ACCESS_REG_MTCAP(params->g_sx_dev, (struct ku_access_mtcap_reg *)reg_data);
        if (err) {
            printk(KERN_ERR "SPICE: sx_ACCESS_REG_MTCAP failed with err: %d\n", err);
            goto out;
        }
        if (((struct ku_access_mtcap_reg *)reg_data)->op_tlv.status) {
            goto fw_error;
        }
        break;

    default:
        printk(KERN_ERR "SPICE: incorrect reg_id: 0x%u\n", params->reg_id);
    }
out:
    return err;
fw_error:
    return ((struct ku_access_ppcnt_reg *)reg_data)->op_tlv.status;
}

int __init sx_spice_dump_init(void)
{
    int err = 0;

    err = sx_register_interface(&sx_spice_interface);
    if (err) {
        printk(KERN_ERR "Failed to register SPICE kernel module\n");
        goto out;
    }

    err = cache_create();
    if (err) {
        printk(KERN_ERR "Failed to create cache for SPICE\n");
        goto cache_create_failed;
    }

    err = sx_spice_tree_init();
    if (err) {
        printk(KERN_ERR "SPICE: Failed to initialize spice tree module\n");
        goto sx_spice_tree_init_failed;
    }

    err = __sx_spice_tree_create();
    if (err) {
        printk(KERN_ERR "SPICE: Failed to create ber tree\n");
        goto sx_spice_tree_create_failed;
    }

    return err;

sx_spice_tree_create_failed:
    sx_spice_tree_deinit();

sx_spice_tree_init_failed:
    cache_destroy();

cache_create_failed:
    sx_unregister_interface(&sx_spice_interface);

out:
    return err;
}


void sx_spice_dump_exit(void)
{
    printk(KERN_ERR "%s", __FUNCTION__);

    printk(KERN_INFO "finish spice-dump\n");

    sx_unregister_interface(&sx_spice_interface);

    cache_destroy();

    sx_spice_access_reg_pddr_list_free();

    sx_spice_access_reg_ppcnt_list_free();

    sx_spice_access_reg_spzr_list_free();

    sx_spice_access_reg_pmdr_list_free();

    sx_spice_access_reg_ptys_list_free();

    sx_spice_access_reg_mtcap_list_free();

    sx_spice_access_reg_mvcap_list_free();

    sx_spice_tree_deinit();

    g_system_info_init_done = false;
}

module_init(sx_spice_dump_init);
module_exit(sx_spice_dump_exit);


int __sx_spice_system_type_get(uint16_t *dev_id)
{
    int                       err = 0;
    sxd_params_t              sxd_params;
    struct ku_access_mgir_reg reg_data;

    if (!g_system_info_init_done) {
        memset(&reg_data, 0, sizeof(struct ku_access_mgir_reg));
        memset(&sxd_params, 0, sizeof(sxd_params_t));

        sxd_params.g_sx_dev = g_sx_dev;
        sxd_params.reg_id = MLXSW_MGIR_ID;
        sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_MGIR_ID, 1);
        reg_data.dev_id = 1;

        err = sx_spice_sxd_access(&sxd_params, &reg_data);
        if (err) {
            printk(KERN_ERR "SPICE: Failed to get system info from MGIR register\n");
            goto out;
        }

        *dev_id = reg_data.mgir_reg.hw_info.device_id;

        g_system_info_init_done = true;
    }

out:
    return err;
}

int __sx_spice_tree_create(void)
{
    int      err = 0;
    uint16_t dev_id = 0;

    err = __sx_spice_system_type_get(&dev_id);
    if (err) {
        printk(KERN_ERR "SPICE: Failed to get system type\n");
        goto out;
    }

    switch (dev_id) {
    case SXD_MGIR_HW_DEV_ID_SWITCH_IB:
    case SXD_MGIR_HW_DEV_ID_SWITCH_IB2:
    case SXD_MGIR_HW_DEV_ID_QUANTUM:
    case SXD_MGIR_HW_DEV_ID_QUANTUM2:
        err = sx_spice_tree_ber_ib_create();
        if (err) {
            printk(KERN_ERR "SPICE: Failed to create IB ber tree\n");
            goto out;
        }
        break;

    case SXD_MGIR_HW_DEV_ID_SPECTRUM:
    case SXD_MGIR_HW_DEV_ID_SPECTRUM2:
    case SXD_MGIR_HW_DEV_ID_SPECTRUM3:
    case SXD_MGIR_HW_DEV_ID_SPECTRUM4:
        err = sx_spice_tree_ber_eth_create();
        if (err) {
            printk(KERN_ERR "SPICE: Failed to create ETH ber tree\n");
            goto out;
        }
        break;

    default:
        printk(KERN_ERR "ERROR: Unresolved device id (%u)\n", dev_id);
        return -EFAULT;
    }

out:
    return err;
}
