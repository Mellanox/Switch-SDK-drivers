/*
 * Copyright © 2010-2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
#include <linux/vmalloc.h>
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
#include "sx_spice_access_reg.h"
#include "sx_spice_bulk_cntr.h"
#include "sx_spice_uphy_reg_auto.h"

MODULE_AUTHOR("Lior Kaplan");
MODULE_DESCRIPTION("Spice-Dump driver");
MODULE_LICENSE("Dual BSD/GPL");

#define MLXSW_PPLL_ID 0x5030

/************************************************
 *  Local variables
 ***********************************************/

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 16, 0))
static struct kmem_cache *__kbuffer_cache;
#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 16, 0)) */

/************************************************
 *  Type definitions
 ***********************************************/

/************************************************
 * Functions                                    *
 ***********************************************/


static int __sx_spice_tree_create(dev_private_data_t *dev_priv);
static int __sx_spice_tree_app_directories_create(void);
static int __sx_spice_sensor_count_get(dev_private_data_t *priv_data);
static int __sx_spice_pll_group_num_get(dev_private_data_t *priv_data);
static int __sx_spice_bulk_cntr_init(dev_private_data_t *dev_data);
static int __sx_spice_bulk_cntr_deinit(dev_private_data_t *dev_data);
static void __sx_spice_access_reg_lists_free(void);

void sx_spice_add_stats(dev_private_data_t *dev_priv, struct sx_emad_out_params *out_params)
{
    static const u32              histogram_ranges[] = { 10, 20, 30, 40, 50, 100, 200, UINT_MAX };
    struct sx_spice_latency_entry tmp;
    bool                          need_to_sort = false;
    int                           i, j;

    BUILD_BUG_ON(sizeof(histogram_ranges) / sizeof(histogram_ranges[0]) !=
                 sizeof(dev_priv->stats.latency_histogram) / sizeof(dev_priv->stats.latency_histogram[0]));

    /* add to histogram */
    for (i = 0; i < sizeof(histogram_ranges) / sizeof(histogram_ranges[0]); i++) {
        if (out_params->fw_latency <= histogram_ranges[i]) {
            dev_priv->stats.latency_histogram[i]++;
            break;
        }
    }

    /* add to max latency chart */
    if (dev_priv->stats.num_of_max_latency_entries < MAX_LATENCY_SIZE) {
        dev_priv->stats.max_latency[dev_priv->stats.num_of_max_latency_entries].reg_id = out_params->reg_id;
        dev_priv->stats.max_latency[dev_priv->stats.num_of_max_latency_entries].latency = out_params->fw_latency;
        dev_priv->stats.num_of_max_latency_entries++;
        need_to_sort = true;
    } else if (out_params->fw_latency > dev_priv->stats.max_latency[MAX_LATENCY_SIZE - 1].latency) {
        dev_priv->stats.max_latency[MAX_LATENCY_SIZE - 1].reg_id = out_params->reg_id;
        dev_priv->stats.max_latency[MAX_LATENCY_SIZE - 1].latency = out_params->fw_latency;
        need_to_sort = true;
    }

    if (need_to_sort) {
        for (i = 0; i < dev_priv->stats.num_of_max_latency_entries; i++) {
            for (j = i + 1; j < dev_priv->stats.num_of_max_latency_entries; j++) {
                if (dev_priv->stats.max_latency[i].latency < dev_priv->stats.max_latency[j].latency) {
                    tmp = dev_priv->stats.max_latency[i];
                    dev_priv->stats.max_latency[i] = dev_priv->stats.max_latency[j];
                    dev_priv->stats.max_latency[j] = tmp;
                }
            }
        }
    }

    /* update last entry */
    dev_priv->stats.recent.reg_id = out_params->reg_id;
    dev_priv->stats.recent.latency = out_params->fw_latency;

    dev_priv->stats.num_of_reg_calls++;
    if (out_params->fw_status != 0) {
        dev_priv->stats.num_of_reg_calls_errors++;
    }
    dev_priv->stats.total_fw_latency += out_params->fw_latency;
}

static int __spice_stats_dump(struct seq_file *m, void *v, void *context)
{
    dev_private_data_t *dev_data = (dev_private_data_t*)context;
    u32                 aver_latency = 0;
    int                 i;

    seq_printf(m, "SPICE stats (device #%u)\n", dev_data->dev->device_id);
    seq_printf(m, "\n");

    seq_printf(m, "Latency histogram (usecs)\n");
    seq_printf(m, "\t<= 10:   %llu\n", dev_data->stats.latency_histogram[0]);
    seq_printf(m, "\t11-20:   %llu\n", dev_data->stats.latency_histogram[1]);
    seq_printf(m, "\t21-30:   %llu\n", dev_data->stats.latency_histogram[2]);
    seq_printf(m, "\t31-40:   %llu\n", dev_data->stats.latency_histogram[3]);
    seq_printf(m, "\t41-50:   %llu\n", dev_data->stats.latency_histogram[4]);
    seq_printf(m, "\t51-100:  %llu\n", dev_data->stats.latency_histogram[5]);
    seq_printf(m, "\t101-200: %llu\n", dev_data->stats.latency_histogram[6]);
    seq_printf(m, "\t> 200:   %llu\n", dev_data->stats.latency_histogram[7]);
    seq_printf(m, "\n");

    seq_printf(m, "Recent entry stats\n");
    if (dev_data->stats.recent.reg_id != 0) {
        seq_printf(m, "\treg_id: 0x%04x    latency: %u\n",
                   dev_data->stats.recent.reg_id,
                   dev_data->stats.recent.latency);
    }
    seq_printf(m, "\n");

    seq_printf(m, "Max latency (usecs)\n");
    for (i = 0; i < dev_data->stats.num_of_max_latency_entries; i++) {
        seq_printf(m, "\treg_id: 0x%04x    latency: %u\n",
                   dev_data->stats.max_latency[i].reg_id,
                   dev_data->stats.max_latency[i].latency);
    }
    seq_printf(m, "\n");

    if (dev_data->stats.num_of_reg_calls > 0) {
        aver_latency = dev_data->stats.total_fw_latency / dev_data->stats.num_of_reg_calls;
    }

    seq_printf(m, "Total register calls:    %llu\n", dev_data->stats.num_of_reg_calls);
    seq_printf(m, "Failed register calls:   %llu\n", dev_data->stats.num_of_reg_calls_errors);
    seq_printf(m, "Average latency (usecs): %u\n", aver_latency);
    seq_printf(m, "\n");

    return 0;
}

static void * sx_spice_register(struct sx_dev *dev)
{
    int                 err = 0;
    dev_private_data_t *priv_data;

    priv_data = vmalloc(sizeof(*priv_data));
    if (!priv_data) {
        return NULL;
    }
    memset(priv_data, 0, sizeof(dev_private_data_t));

    mutex_init(&priv_data->reg_access.reg_mutex);

    sema_init(&priv_data->reg_access.reg_sem, 1);

    priv_data->dev = dev;

    priv_data->is_available = sx_core_is_profile_set(dev);

    err = sx_spice_system_type_get(priv_data);
    if (err) {
        printk(KERN_ERR "SPICE: Failed to get system type\n");
        vfree(priv_data);
        return NULL;
    }

    err = __sx_spice_tree_create(priv_data);
    if (err) {
        if (err == -EFAULT) {
            printk(KERN_ERR "SPICE: SPICE isn't supported with dev_id: %d \n", priv_data->hw_device_id);
            vfree(priv_data);
            return NULL;
        }
        printk(KERN_ERR "SPICE: Failed to create tree\n");
    }

    if (priv_data->eth_mode) {
        err = __sx_spice_bulk_cntr_init(priv_data);
        if (err) {
            printk(KERN_ERR "SPICE: Failed to init spice_bulk_cntr\n");
        }
    }

    if ((priv_data->hw_device_id == SXD_MGIR_HW_DEV_ID_QUANTUM2) ||
        (priv_data->hw_device_id == SXD_MGIR_HW_DEV_ID_SPECTRUM4)) {
        err = sx_spice_uphy_reg_init();
        if (err) {
            printk(KERN_ERR "SPICE: Failed to initialize uPHY reg module\n");
        }
    }

    sx_dbg_dump_read_handler_register("spice_stats", __spice_stats_dump, NULL, dev, priv_data);

    return priv_data;
}

static void sx_spice_unregister(struct sx_dev *dev, void *private_data)
{
    dev_private_data_t *priv_data = (dev_private_data_t*)private_data;

    if (priv_data->is_available) {
        if (down_timeout(&priv_data->reg_access.reg_sem, msecs_to_jiffies(5000)) == -ETIME) {
            printk(KERN_ERR "SPICE: FW is busy, cannot proceed with spice deinit process");
        }
    }

    sx_dbg_dump_read_handler_unregister("spice_stats", dev);

    if (priv_data->eth_mode) {
        /*deinit bulk_cntr registered files for device*/
        __sx_spice_bulk_cntr_deinit(priv_data);

        /*free bulk_cntr registered files for device*/
        sx_spice_access_reg_bulk_counters_list_free(priv_data);

        debugfs_remove_recursive(priv_data->asic_counters_root_inode_p);
    }

    debugfs_remove_recursive(priv_data->ber_root_inode_p);

    vfree(priv_data);
}

static int sx_spice_event(struct sx_dev       *dev,
                          void                *resources,
                          enum sx_dev_event    event,
                          union sx_event_data *event_data)
{
    dev_private_data_t *dev_data = (dev_private_data_t*)resources;
    int                 err = 0;

    switch (event) {
    case SX_DEV_EVENT_ISSU_START:
    case SX_DEV_EVENT_PRE_RESET:
        printk(KERN_NOTICE "sx_spice_event: Got ISSU/PRE_RESET start event. "
               "dev = %p, dev_id = %u",
               dev, dev->device_id);
        if (down_timeout(&dev_data->reg_access.reg_sem, msecs_to_jiffies(5000)) == -ETIME) {
            err = -ETIMEDOUT;
            goto out;
        }

        if (dev_data->eth_mode) {
            /*update issu indication for bulk_cntr*/
            spice_bulk_cntr_is_issu = true;
            /*unregister bulk counter*/
            err = __sx_spice_bulk_cntr_deinit(dev_data);
            if (err) {
                printk(KERN_ERR "SPICE: Failed to unregister spice_bulk_cntr "
                       "for device_id: %d on ISSU/PRE_RESET start event\n", dev->device_id);
                goto out;
            }
        }
        dev_data->is_available = false;
        break;

    case SX_DEV_EVENT_POST_SET_PROFILE:
        printk(KERN_NOTICE "sx_spice_event: Got POST RESET event. "
               "dev = %p, dev_id = %u",
               dev, dev->device_id);
        up(&dev_data->reg_access.reg_sem);

        if (dev_data->eth_mode) {
            /*register bulk counter*/
            err = __sx_spice_bulk_cntr_init(dev_data);
            if (err) {
                printk(KERN_ERR "SPICE: Failed to register spice_bulk_cntr"
                       "for device_id: %d on POST_RESET start event\n", dev->device_id);
                goto out;
            }
            spice_bulk_cntr_is_issu = false;
        }
        dev_data->is_available = true;
        break;

    default:
        break;
    }

out:
    return err;
}

static struct sx_interface sx_spice_interface = {
    .add = sx_spice_register,
    .remove = sx_spice_unregister,
    .event = sx_spice_event
};

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 16, 0))
static int cache_create(void)
{
    __kbuffer_cache = kmem_cache_create_usercopy("spice_kbuffer",
                                                 KERNEL_BUFFER_SIZE,
                                                 0,
                                                 0,
                                                 0,
                                                 KERNEL_BUFFER_SIZE,
                                                 NULL);
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
#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 16, 0)) */

char * sx_spice_buffer_alloc(gfp_t gfp)
{
    char *kbuffer;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 16, 0))
    kbuffer = (char*)kmem_cache_alloc(__kbuffer_cache, gfp);
#else
    kbuffer = (char*)kmalloc(KERNEL_BUFFER_SIZE, gfp);
#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 16, 0)) */

    return kbuffer;
}

void sx_spice_buffer_free(void *kbuffer)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 16, 0))
    kmem_cache_free(__kbuffer_cache, kbuffer);
#else
    kfree(kbuffer);
#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 16, 0)) */
}

static int __sx_spice_tree_app_directories_create(void)
{
    int err = 0;

    err = sx_spice_tree_ber_app_dir_create();
    if (err) {
        printk(KERN_ERR "SPICE: Failed to create root directory for BER application\n");
        goto out;
    }

    err = sx_spice_tree_asic_counters_app_dir_create();
    if (err) {
        printk(KERN_ERR "SPICE: Failed to create root directory for asic_counters application\n");
        goto out;
    }
out:
    return err;
}

int __init sx_spice_dump_init(void)
{
    int err = 0;

    err = sx_spice_tree_init();
    if (err) {
        printk(KERN_ERR "SPICE: Failed to initialize spice tree module\n");
        goto out;
    }
    err = __sx_spice_tree_app_directories_create();
    if (err) {
        printk(KERN_ERR "SPICE: Failed to initialize spice tree module\n");
        goto out;
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 16, 0))
    err = cache_create();
    if (err) {
        printk(KERN_ERR "Failed to create cache for SPICE\n");
        goto cache_create_failed;
    }
#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 16, 0)) */

    err = sx_register_interface(&sx_spice_interface);
    if (err) {
        printk(KERN_ERR "Failed to register SPICE kernel module\n");
        goto sx_register_failed;
    }

    return err;

sx_register_failed:
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 16, 0))
    cache_destroy();

cache_create_failed:
#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 16, 0)) */
    sx_spice_tree_deinit();

out:
    return err;
}

static int __sx_spice_bulk_cntr_init(dev_private_data_t *dev_data)
{
    int                            err = 0;
    spice_bulk_cntr_file_params_t *iter;
    spice_bulk_cntr_event_params_t bulk_cntr_params;

    memset(&bulk_cntr_params, 0, sizeof(spice_bulk_cntr_event_params_t));

    /*init each created file*/
    list_for_each_entry(iter, &dev_data->spice_bulk_cntr_dev_files_list, list_file_params) {
        bulk_cntr_params.op = SPICE_BULK_COUNTER_INIT_OP_E;
        bulk_cntr_params.dev = iter->dev;
        bulk_cntr_params.key_type = iter->key_type;
        bulk_cntr_params.context = &iter->file_db;

        mutex_lock(&iter->file_db.tr_file_op_mutex);
        err = sx_spice_bulk_cntr_event(&bulk_cntr_params);
        if (err) {
            printk(KERN_ERR "%s: Failed to initialize spice bulk counters type: %d on device: %d\n",
                   __func__, iter->key_type, iter->dev->device_id);
            mutex_unlock(&iter->file_db.tr_file_op_mutex);
            goto out;
        }
        mutex_unlock(&iter->file_db.tr_file_op_mutex);

#ifdef SPICE_BULK_CNTR_LOG_EN
        printk(KERN_INFO "%s: successfully initialized spice bulk counter type:%d of device_id: %d\n",
               __func__, iter->key_type, iter->dev->device_id);
#endif
    }

    /*register to mocs_done trap*/
    err = sx_spice_bulk_cntr_listener_set(CTRL_CMD_ADD_SYND,
                                          dev_data->dev,
                                          SXD_TRAP_ID_MOCS_DONE,
                                          (void *)&dev_data->spice_bulk_cntr_dev_files_list);
    if (err) {
        printk(KERN_ERR "%s: failed to set trap_id SXD_TRAP_ID_MOCS_DONE", __func__);
        goto out;
    }

out:
    return err;
}

static int __sx_spice_bulk_cntr_deinit(dev_private_data_t *dev_data)
{
    int                            err = 0;
    spice_bulk_cntr_file_params_t *iter;
    spice_bulk_cntr_event_params_t bulk_cntr_params;

    memset(&bulk_cntr_params, 0, sizeof(spice_bulk_cntr_event_params_t));

    /*deinit each created file*/
    list_for_each_entry(iter, &dev_data->spice_bulk_cntr_dev_files_list, list_file_params) {
        bulk_cntr_params.op = SPICE_BULK_COUNTER_DEINIT_OP_E;
        bulk_cntr_params.dev = iter->dev;
        bulk_cntr_params.key_type = iter->key_type;
        bulk_cntr_params.context = &iter->file_db;

        mutex_lock(&iter->file_db.tr_file_op_mutex);
        err = sx_spice_bulk_cntr_event(&bulk_cntr_params);
        if (err) {
            printk(KERN_ERR "%s: Failed to deinit spice bulk counters type: %d on device: %d\n",
                   __func__, iter->key_type, iter->dev->device_id);
            mutex_unlock(&iter->file_db.tr_file_op_mutex);
            goto out;
        }
        mutex_unlock(&iter->file_db.tr_file_op_mutex);

#ifdef SPICE_BULK_CNTR_LOG_EN
        printk(KERN_INFO "%s: successfully deinit spice bulk counter type:%d of device_id: %d\n",
               __func__, iter->key_type, iter->dev->device_id);
#endif
    }
    /*unregister to mocs_done trap once tr files are done*/
    err = sx_spice_bulk_cntr_listener_set(CTRL_CMD_REMOVE_SYND,
                                          dev_data->dev,
                                          SXD_TRAP_ID_MOCS_DONE,
                                          (void *)&dev_data->spice_bulk_cntr_dev_files_list);
    if (err) {
        printk(KERN_ERR "%s: failed to remove trap_id SXD_TRAP_ID_MOCS_DONE", __func__);
        goto out;
    }

out:
    return err;
}

static void __sx_spice_access_reg_lists_free(void)
{
    sx_spice_access_reg_pddr_list_free();

    sx_spice_access_reg_ppcnt_list_free();

    sx_spice_access_reg_spzr_list_free();

    sx_spice_access_reg_pmdr_list_free();

    sx_spice_access_reg_ptys_list_free();

    sx_spice_access_reg_mtcap_list_free();

    sx_spice_access_reg_mvcap_list_free();

    sx_spice_access_reg_msgi_list_free();

    sx_spice_access_reg_mgir_list_free();

    sx_spice_access_reg_mdir_list_free();

    sx_spice_access_reg_sltp_list_free();

    sx_spice_access_reg_sllm_list_free();

    sx_spice_access_reg_spad_list_free();

    sx_spice_access_reg_slrip_list_free();

    sx_spice_access_reg_slrg_list_free();

    sx_spice_access_reg_pphcr_list_free();

    sx_spice_access_reg_mtmp_list_free();

    sx_spice_access_reg_slrp_list_free();

    sx_spice_access_reg_peucg_list_free();

    sx_spice_access_reg_ppll_list_free();
}

void sx_spice_dump_exit(void)
{
    printk(KERN_ERR "%s", __FUNCTION__);

    printk(KERN_INFO "finish spice-dump\n");

    sx_unregister_interface(&sx_spice_interface);

    sx_spice_tree_deinit();

    sx_spice_uphy_reg_deinit();

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 16, 0))
    cache_destroy();
#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 16, 0)) */

    __sx_spice_access_reg_lists_free();
}

module_init(sx_spice_dump_init);
module_exit(sx_spice_dump_exit);


int sx_spice_system_type_get(dev_private_data_t *priv_data)
{
    int                       err = 0;
    struct ku_access_mgir_reg reg_data;

    memset(&reg_data, 0, sizeof(struct ku_access_mgir_reg));

    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_MGIR_ID, 1);
    reg_data.dev_id = priv_data->dev->device_id;
    err = sx_ACCESS_REG_MGIR(priv_data->dev, &reg_data);
    if (err) {
        printk(KERN_ERR "SPICE: Failed to get system info from MGIR register\n");
        goto out;
    }

    priv_data->hw_device_id = reg_data.mgir_reg.hw_info.device_id;

out:
    return err;
}

static int __sx_spice_sensor_count_get(dev_private_data_t *priv_data)
{
    int                        err = 0;
    struct ku_access_mtcap_reg reg_data;

    memset(&reg_data, 0, sizeof(struct ku_access_mtcap_reg));
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_MTCAP_ID, EMAD_METHOD_QUERY);
    reg_data.dev_id = priv_data->dev->device_id;

    err = sx_ACCESS_REG_MTCAP(priv_data->dev, &reg_data);
    if (err) {
        printk(KERN_ERR "SPICE: Failed to get system info from MLXSW_MTCAP_ID register\n");
        goto out;
    }
    priv_data->max_sensor_index = reg_data.mtcap_reg.sensor_count;

out:
    return err;
}

static int __sx_spice_pll_group_num_get(dev_private_data_t *priv_data)
{
    int                       err = 0;
    struct ku_access_ppll_reg reg_data;

    memset(&reg_data, 0, sizeof(reg_data));
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_PPLL_ID, 1);
    reg_data.dev_id = priv_data->dev->device_id;
    err = sx_ACCESS_REG_PPLL(priv_data->dev, &reg_data);
    if (err) {
        printk(KERN_ERR "SPICE: Failed to get num of pll groups from PPLL register\n");
        goto out;
    }

    priv_data->max_pll_group = reg_data.ppll_reg.num_pll_groups;

out:
    return err;
}

static int __sx_spice_tree_create(dev_private_data_t *dev_priv)
{
    int                  err = 0;
    struct ku_query_rsrc query_rsrc;

    memset(&query_rsrc, 0, sizeof(struct ku_query_rsrc));

    query_rsrc.rsrc_id = KU_RES_ID_CAP_MAX_SWITCH_PORTS;

    if (!dev_priv) {
        printk(KERN_ERR "SPICE: in __sx_spice_tree_create dev is NULL\n");
        goto out;
    }

    err = sx_QUERY_RSRC(dev_priv->dev, &query_rsrc);
    if (err) {
        printk(KERN_ERR "SPICE: Failed to retrieve system number of ports\n");
        goto out;
    }

    dev_priv->max_local_port = query_rsrc.rsrc_val;

    err = __sx_spice_sensor_count_get(dev_priv);
    if (err) {
        printk(KERN_ERR "SPICE: Failed to get ambient sensor count\n");
        goto out;
    }

    err = __sx_spice_pll_group_num_get(dev_priv);
    if (err) {
        printk(KERN_ERR "SPICE: Failed to get pll group count\n");
        goto out;
    }

    switch (dev_priv->hw_device_id) {
    case SXD_MGIR_HW_DEV_ID_QUANTUM:
    case SXD_MGIR_HW_DEV_ID_QUANTUM2:
        err = sx_spice_tree_ber_ib_create(dev_priv);
        if (err) {
            printk(KERN_ERR "SPICE: Failed to create IB ber tree\n");
            goto out;
        }
        break;

    case SXD_MGIR_HW_DEV_ID_SPECTRUM2:
    case SXD_MGIR_HW_DEV_ID_SPECTRUM3:
    case SXD_MGIR_HW_DEV_ID_SPECTRUM4:
        dev_priv->eth_mode = true;

        err = sx_spice_tree_ber_eth_create(dev_priv);
        if (err) {
            printk(KERN_ERR "SPICE: Failed to create ETH ber tree\n");
            goto out;
        }

        err = sx_spice_tree_asic_counters_eth_create(dev_priv);
        if (err) {
            printk(KERN_ERR "SPICE: Failed to create ETH asic_counters tree\n");
            goto out;
        }
        break;

    default:
        printk(KERN_ERR "ERROR: Unresolved device id (%u)\n", dev_priv->hw_device_id);
        return -EFAULT;
    }

out:
    return err;
}
