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
#include "sx_spice_wrapper.h"

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
    PLL_GROUP,
    LOCAL_PORT,
    LANE,
    FOM_MEASURMENT,
    I,
    SENSOR_INDEX,
    ROUTER_ENTITY,
    TEST_MODE,
    ENUM_INIT,
    IG,
    SWID,
    DB_INDEX,
    ASIC_INDEX,
    PNAT,
    HIST_TYPE,
    DB,
    GRP_PROFILE,
    PRIO_TC,
    PORT_TYPE,
    GRP,
    PAGE_SELECT,
    SLOT_INDEX,
    PROTO_MASK,
    IB_SEL,
    UNIT,
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
int sx_spice_tree_asic_counters_app_dir_create(void);
int sx_spice_tree_asic_counters_eth_create(dev_private_data_t *dev_data);
int sx_spice_tree_ber_app_dir_create(void);
int sx_spice_tree_ber_eth_create(dev_private_data_t *dev_data);
int sx_spice_tree_ber_ib_create(dev_private_data_t *dev_data);

