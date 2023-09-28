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
#ifndef SX_SPICE_WRAPPER_H
#define SX_SPICE_WRAPPER_H

#include <linux/netdevice.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include <linux/mlx_sx/auto_registers/mlxsw_item.h>

#define VALIDATE_ROLLBACK(snp_res, buffer_length, buffer_size)            \
    do {                                                                  \
        if ((snp_res == 0) || (snp_res >= buffer_length - buffer_size)) { \
            return 0;                                                     \
        }                                                                 \
    } while (0)

/************************************************
 *  Local variables
 ***********************************************/

#define KERNEL_BUFFER_SIZE 18000

/************************************************
 *  Type definitions
 ***********************************************/

typedef struct reg_access_params {
    struct semaphore reg_sem;
    struct mutex     reg_mutex;
} reg_access_params_t;

struct sx_spice_latency_entry {
    u16 reg_id;
    u32 latency;
};

struct sx_spice_stats {
#define MAX_LATENCY_SIZE (10)
    struct sx_spice_latency_entry max_latency[MAX_LATENCY_SIZE];
    struct sx_spice_latency_entry recent;
    u32                           num_of_max_latency_entries;
    u64                           latency_histogram[8]; /* 0-10, 11-20, 21-30, 31-40, 41-50, 51-100, 100-200, >200 */
    u64                           num_of_reg_calls;
    u64                           num_of_reg_calls_errors;
    u64                           total_fw_latency;
};

typedef struct dev_private_data {
    struct sx_dev        *dev;
    uint16_t              hw_device_id;
    bool                  eth_mode;
    uint32_t              max_local_port;
    uint8_t               max_sensor_index;
    uint8_t               max_pll_group;
    struct dentry        *asic_counters_root_inode_p;
    struct dentry        *ber_root_inode_p;
    reg_access_params_t   reg_access;
    struct list_head      spice_bulk_cntr_dev_files_list;
    bool                  is_issu_start;
    struct sx_spice_stats stats;
} dev_private_data_t;

/************************************************
 * Functions                                    *
 ***********************************************/

char * sx_spice_buffer_alloc(gfp_t gfp);
void sx_spice_buffer_free(void *kbuffer);

#define SX_SPICE_EMAD_ACCESS_REG(reg_name, dev_data, reg_data)                      \
    ({ int __err;                                                                   \
       __err = sx_spice_prepare_access_reg(dev_data);                               \
       if (__err) {                                                                 \
           sx_spice_post_access_reg((dev_data), false);                             \
       }                                                                            \
       else {                                                                       \
           struct sx_emad_in_params in_params;                                      \
           struct sx_emad_out_params out_params;                                    \
                                                                                    \
           memset(&in_params, 0, sizeof(in_params));                                \
           memset(&out_params, 0, sizeof(out_params));                              \
           in_params.silent = true; /* in case of error, don't put a log message */ \
                                                                                    \
           __err = sx_EMAD_ACCESS_REG_ ## reg_name((dev_data)->dev,                 \
                                                   EMAD_PRIO_LOW,                   \
                                                   EMAD_METHOD_QUERY,               \
                                                   &in_params,                      \
                                                   &out_params,                     \
                                                   (reg_data));                     \
           sx_spice_post_access_reg((dev_data), true);                              \
                                                                                    \
           sx_spice_add_stats((dev_data), &out_params);                             \
       }                                                                            \
       __err; })

int sx_spice_system_type_get(dev_private_data_t *priv_data);
void sx_spice_add_stats(dev_private_data_t *dev_priv, struct sx_emad_out_params *out_params);

#endif /* SX_SPICE_WRAPPER_H_ */
