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

#include <linux/debugfs.h>
#include "sx_spice_wrapper.h"

/************************************************
 *  Local variables
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

typedef struct slrip_data {
    uint16_t            local_port;
    uint8_t             pnat;
    uint8_t             lane;
    uint8_t             port_type;
    uint8_t             ib_sel;
    struct list_head    slrip_list;
    dev_private_data_t *dev_data;
} slrip_data_t;

typedef struct slrg_data {
    uint16_t            local_port;
    uint8_t             pnat;
    uint8_t             lane;
    uint8_t             port_type;
    uint8_t             test_mode;
    struct list_head    slrg_list;
    dev_private_data_t *dev_data;
} slrg_data_t;

typedef struct slrp_data {
    uint16_t            local_port;
    uint8_t             pnat;
    uint8_t             lane;
    uint8_t             port_type;
    struct list_head    slrp_list;
    dev_private_data_t *dev_data;
} slrp_data_t;

/************************************************
 * Functions                                    *
 ***********************************************/

int sx_spice_access_reg_slrip_file_create(struct dentry *parent, dev_private_data_t *dev_data);
void sx_spice_access_reg_slrip_list_free(void);

int sx_spice_access_reg_slrg_file_create(struct dentry *parent, dev_private_data_t *dev_data);
void sx_spice_access_reg_slrg_list_free(void);

int sx_spice_access_reg_slrp_file_create(struct dentry *parent, dev_private_data_t *dev_data);
void sx_spice_access_reg_slrp_list_free(void);
