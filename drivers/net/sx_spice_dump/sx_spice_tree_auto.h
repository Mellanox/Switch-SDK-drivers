/*
 * Copyright © 2018-2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

/************************************************
 *  Defines
 ***********************************************/

/************************************************
 *  Macros
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

typedef struct index_type_data {
    char    field_name[50];
    uint8_t field_value;
} index_type_data_t;


typedef enum {
    LOCAL_PORT,
    PRIO_TC,
    PNAT,
    SWID,
    PORT_TYPE,
    GRP,
    PAGE_SELECT,
    SLOT_INDEX,
    PROTO_MASK,
    MAX_INDEX_TYPE
} index_type_e;

/************************************************
 *  Global variables
 ***********************************************/

/************************************************
 *  Function declarations
 ***********************************************/

int sx_spice_tree_init(void);
void sx_spice_tree_deinit(void);
uint16_t sx_spice_tree_index_value_get(index_type_e index);
int sx_spice_tree_ber_eth_create(void);
void sx_spice_tree_ber_eth_destroy(void);
int sx_spice_tree_ber_ib_create(void);
void sx_spice_tree_ber_ib_destroy(void);
