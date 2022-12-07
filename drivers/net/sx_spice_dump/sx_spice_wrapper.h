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

/************************************************
 *  Local variables
 ***********************************************/

#define KERNEL_BUFFER_SIZE 10000

#define MLXSW_SLRP_ID  0x5026
#define MLXSW_SLRIP_ID 0x5057
#define MLXSW_SLRG_ID  0x5028

/************************************************
 *  Type definitions
 ***********************************************/

typedef struct sxd_params {
    uint16_t reg_id;
} sxd_params_t;

typedef struct reg_access_params {
    struct semaphore reg_sem;
    struct mutex     reg_mutex;
} reg_access_params_t;

typedef struct dev_private_data {
    struct sx_dev      *dev;
    uint32_t            max_local_port;
    uint8_t             max_sensor_index;
    struct dentry      *asic_counters_root_inode_p;
    struct dentry      *ber_root_inode_p;
    reg_access_params_t reg_access;
    struct list_head    spice_bulk_cntr_dev_files_list;
    bool                is_issu_start;
} dev_private_data_t;

/************************************************
 * Functions                                    *
 ***********************************************/

char * sx_spice_buffer_alloc(gfp_t gfp);
void sx_spice_buffer_free(void *kbuffer);

int sx_spice_sxd_access(dev_private_data_t *priv_data, sxd_params_t *params, void * reg_data);

int sx_spice_system_type_get(dev_private_data_t *priv_data, uint16_t *dev_id);

#endif /* SX_SPICE_WRAPPER_H_ */
