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

#include <linux/debugfs.h>
#include "sx_spice_wrapper.h"
#include "sx_spice_uphy_reg_auto.h"

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

typedef struct peucg_data {
    uint8_t             unit;
    uint16_t            local_port;
    uint8_t             pnat;
    uint8_t             lane;
    uint8_t             enum_init;
    uint16_t            db_index;
    struct list_head    peucg_list;
    dev_private_data_t *dev_data;
} peucg_data_t;

typedef struct ppll_data {
    uint8_t             pll_group;
    struct list_head    ppll_list;
    dev_private_data_t *dev_data;
} ppll_data_t;

/************************************************
 * Functions                                    *
 ***********************************************/

int sx_spice_access_reg_slrip_file_create(struct dentry *parent, dev_private_data_t *dev_data);
void sx_spice_access_reg_slrip_list_free(void);
int sx_spice_access_reg_slrip_reg_data_to_buffer_print(char                  buffer[],
                                                       size_t                buffer_length,
                                                       struct ku_slrip_reg * reg_data);
ssize_t sx_spice_access_reg_slrip_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);

int sx_spice_access_reg_slrg_file_create(struct dentry *parent, dev_private_data_t *dev_data);
void sx_spice_access_reg_slrg_list_free(void);
int sx_spice_access_reg_slrg_reg_data_to_buffer_print(char                 buffer[],
                                                      size_t               buffer_length,
                                                      struct ku_slrg_reg * reg_data);
ssize_t sx_spice_access_reg_slrg_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);

int sx_spice_access_reg_slrp_file_create(struct dentry *parent, dev_private_data_t *dev_data);
void sx_spice_access_reg_slrp_list_free(void);
int sx_spice_access_reg_slrp_reg_data_to_buffer_print(char                 buffer[],
                                                      size_t               buffer_length,
                                                      struct ku_slrp_reg * reg_data);
ssize_t sx_spice_access_reg_slrp_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);

int sx_spice_access_reg_peucg_file_create(struct dentry *parent, dev_private_data_t *dev_data);
int sx_spice_access_reg_peucg_data_to_buffer_print(char                 *buffer,
                                                   size_t                buffer_length,
                                                   struct ku_peucg_reg * reg_data);
ssize_t sx_spice_access_reg_peucg_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);
void sx_spice_access_reg_peucg_list_free(void);

int sx_spice_access_reg_ppll_file_create(struct dentry *parent, dev_private_data_t *dev_data);
int sx_spice_access_reg_ppll_data_to_buffer_print(char                 buffer[],
                                                  size_t               buffer_length,
                                                  struct ku_ppll_reg * reg_data);
ssize_t sx_spice_access_reg_ppll_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);
void sx_spice_access_reg_ppll_list_free(void);
