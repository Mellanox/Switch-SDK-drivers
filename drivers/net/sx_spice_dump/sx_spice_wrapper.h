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


#include <linux/netdevice.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/cmd.h>


/************************************************
 *  Local variables
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

extern struct sx_dev * g_sx_dev;

typedef struct sxd_params {
    struct sx_dev * g_sx_dev;
    uint16_t        reg_id;
} sxd_params_t;

/*typedef enum { */
/*    LOCAL_PORT, */
/*    PAGE_SELECT, */
/*    PORT_TYPE, */
/*    MAX_INDEX_TYPE */
/*} index_type_e; */

extern struct kmem_cache *__kbuffer_cache;

/************************************************
 * Functions                                    *
 ***********************************************/

int sx_spice_sxd_access(sxd_params_t *params, void * reg_data);

/*uint8_t sx_spice_tree_index_value_get(index_type_e index); */
