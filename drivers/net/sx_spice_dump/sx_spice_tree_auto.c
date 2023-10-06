/*
 * Copyright (c) 2021-2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#include <linux/mlx_sx/kernel_user.h>
#include "sx_spice_tree_auto.h"
#include "sx_spice_access_reg.h"
#include "sx_spice_access_reg_auto.h"
#include "sx_spice_tree_dynamic.h"
#include "sx_spice_bulk_cntr.h"

/************************************************
 *  Global variables
 ***********************************************/


/************************************************
 *  Local variables
 ***********************************************/
static uint16_t indexes_arr_g[MAX_INDEX_TYPE];

static index_type_data_t port_type_data_arr_g[6];
static index_type_data_t grp_data_arr_g[20];
static index_type_data_t page_select_data_arr_g[13];
static index_type_data_t slot_index_data_arr_g[1];
static index_type_data_t proto_mask_data_arr_g[2];
static index_type_data_t ib_sel_data_arr_g[4];
static index_type_data_t unit_data_arr_g[2];

static char index_set_eth_port_type_lane_arr_g[6][8];
static char index_set_eth_port_type_grp_arr_g[6][20];
static char index_set_ib_port_type_lane_arr_g[6][8];
static char index_set_ib_port_type_grp_arr_g[6][20];

static struct dentry * root_p;
static struct dentry * asic_counters_p;
static struct dentry * ber_p;


/************************************************
 *  Local function declarations
 ***********************************************/
static void port_type_arr_init(void);
static void grp_arr_init(void);
static void page_select_arr_init(void);
static void slot_index_arr_init(void);
static void proto_mask_arr_init(void);
static void ib_sel_arr_init(void);
static void unit_arr_init(void);

static void enum_index_arr_init(void);

static void index_set_eth_port_type_lane_arr_init(void);
static void index_set_eth_port_type_grp_arr_init(void);
static void index_set_ib_port_type_lane_arr_init(void);
static void index_set_ib_port_type_grp_arr_init(void);

static void index_sets_arr_init(void);


/************************************************
 *  Function implementations
 ***********************************************/
uint16_t sx_spice_tree_index_value_get(index_type_e index)
{
    return indexes_arr_g[index];
}

static void port_type_arr_init(void)
{
    memset(&port_type_data_arr_g, 0, sizeof(index_type_data_t) * 6);

    port_type_data_arr_g[0].field_value = 0;
    sprintf(port_type_data_arr_g[0].field_name, "Network");
    port_type_data_arr_g[1].field_value = 1;
    sprintf(port_type_data_arr_g[1].field_name, "Near_end_point");
    port_type_data_arr_g[2].field_value = 2;
    sprintf(port_type_data_arr_g[2].field_name, "Internal_RC_LR");
    port_type_data_arr_g[3].field_value = 3;
    sprintf(port_type_data_arr_g[3].field_name, "Far_end");
    port_type_data_arr_g[4].field_value = 4;
    sprintf(port_type_data_arr_g[4].field_name, "USR_main");
    port_type_data_arr_g[5].field_value = 5;
    sprintf(port_type_data_arr_g[5].field_name, "USR_tile");

}

static void grp_arr_init(void)
{
    memset(&grp_data_arr_g, 0, sizeof(index_type_data_t) * 20);

    grp_data_arr_g[0].field_value = 0x0;
    sprintf(grp_data_arr_g[0].field_name, "IEEE_802_3");
    grp_data_arr_g[1].field_value = 0x1;
    sprintf(grp_data_arr_g[1].field_name, "RFC_2863");
    grp_data_arr_g[2].field_value = 0x2;
    sprintf(grp_data_arr_g[2].field_name, "RFC_2819");
    grp_data_arr_g[3].field_value = 0x3;
    sprintf(grp_data_arr_g[3].field_name, "RFC_3635");
    grp_data_arr_g[4].field_value = 0x5;
    sprintf(grp_data_arr_g[4].field_name, "Ethernet_Extended");
    grp_data_arr_g[5].field_value = 0x6;
    sprintf(grp_data_arr_g[5].field_name, "Ethernet_Discard");
    grp_data_arr_g[6].field_value = 0x8;
    sprintf(grp_data_arr_g[6].field_name, "Link_Level_Retransmission");
    grp_data_arr_g[7].field_value = 0x10;
    sprintf(grp_data_arr_g[7].field_name, "Per_Priority");
    grp_data_arr_g[8].field_value = 0x11;
    sprintf(grp_data_arr_g[8].field_name, "Per_Traffic_Class");
    grp_data_arr_g[9].field_value = 0x12;
    sprintf(grp_data_arr_g[9].field_name, "Physical_layer");
    grp_data_arr_g[10].field_value = 0x13;
    sprintf(grp_data_arr_g[10].field_name, "Per_Traffic_Class_Congestion");
    grp_data_arr_g[11].field_value = 0x15;
    sprintf(grp_data_arr_g[11].field_name, "Per_Receive_Buffer");
    grp_data_arr_g[12].field_value = 0x16;
    sprintf(grp_data_arr_g[12].field_name, "Physical_Layer_Statistical");
    grp_data_arr_g[13].field_value = 0x19;
    sprintf(grp_data_arr_g[13].field_name, "Out_of_Band_Port");
    grp_data_arr_g[14].field_value = 0x20;
    sprintf(grp_data_arr_g[14].field_name, "InfiniBand_Port");
    grp_data_arr_g[15].field_value = 0x21;
    sprintf(grp_data_arr_g[15].field_name, "InfiniBand_Extended_Port");
    grp_data_arr_g[16].field_value = 0x22;
    sprintf(grp_data_arr_g[16].field_name, "PLR_counters_group");
    grp_data_arr_g[17].field_value = 0x23;
    sprintf(grp_data_arr_g[17].field_name, "RS_FEC_Histogram_group");
    grp_data_arr_g[18].field_value = 0x24;
    sprintf(grp_data_arr_g[18].field_name, "USR_XSR_Physical_layer_counters_group");
    grp_data_arr_g[19].field_value = 0x25;
    sprintf(grp_data_arr_g[19].field_name, "Infiniband_pkts_counters");

}

static void page_select_arr_init(void)
{
    memset(&page_select_data_arr_g, 0, sizeof(index_type_data_t) * 13);

    page_select_data_arr_g[0].field_value = 0;
    sprintf(page_select_data_arr_g[0].field_name, "Operational_info_page");
    page_select_data_arr_g[1].field_value = 1;
    sprintf(page_select_data_arr_g[1].field_name, "Troubleshooting_info_page");
    page_select_data_arr_g[2].field_value = 2;
    sprintf(page_select_data_arr_g[2].field_name, "Phy_info_page");
    page_select_data_arr_g[3].field_value = 3;
    sprintf(page_select_data_arr_g[3].field_name, "Module_info_page");
    page_select_data_arr_g[4].field_value = 4;
    sprintf(page_select_data_arr_g[4].field_name, "Port_events_page");
    page_select_data_arr_g[5].field_value = 5;
    sprintf(page_select_data_arr_g[5].field_name, "Device_events_page");
    page_select_data_arr_g[6].field_value = 6;
    sprintf(page_select_data_arr_g[6].field_name, "Link_down_info");
    page_select_data_arr_g[7].field_value = 7;
    sprintf(page_select_data_arr_g[7].field_name, "Link_down_events");
    page_select_data_arr_g[8].field_value = 8;
    sprintf(page_select_data_arr_g[8].field_name, "Link_up_info");
    page_select_data_arr_g[9].field_value = 9;
    sprintf(page_select_data_arr_g[9].field_name, "Module_latched_flag_info_page");
    page_select_data_arr_g[10].field_value = 10;
    sprintf(page_select_data_arr_g[10].field_name, "link_down_info_ext");
    page_select_data_arr_g[11].field_value = 0xFE;
    sprintf(page_select_data_arr_g[11].field_name, "mng_debug_page");
    page_select_data_arr_g[12].field_value = 0XFF;
    sprintf(page_select_data_arr_g[12].field_name, "phy_debug_page");

}

static void slot_index_arr_init(void)
{
    memset(&slot_index_data_arr_g, 0, sizeof(index_type_data_t) * 1);

    slot_index_data_arr_g[0].field_value = 0;
    sprintf(slot_index_data_arr_g[0].field_name, "Main_board");

}

static void proto_mask_arr_init(void)
{
    memset(&proto_mask_data_arr_g, 0, sizeof(index_type_data_t) * 2);

    proto_mask_data_arr_g[0].field_value = 0;
    sprintf(proto_mask_data_arr_g[0].field_name, "InfiniBand");
    proto_mask_data_arr_g[1].field_value = 2;
    sprintf(proto_mask_data_arr_g[1].field_name, "Ethernet");

}

static void ib_sel_arr_init(void)
{
    memset(&ib_sel_data_arr_g, 0, sizeof(index_type_data_t) * 4);

    ib_sel_data_arr_g[0].field_value = 0;
    sprintf(ib_sel_data_arr_g[0].field_name, "IB0");
    ib_sel_data_arr_g[1].field_value = 1;
    sprintf(ib_sel_data_arr_g[1].field_name, "IB1");
    ib_sel_data_arr_g[2].field_value = 2;
    sprintf(ib_sel_data_arr_g[2].field_name, "IB2");
    ib_sel_data_arr_g[3].field_value = 3;
    sprintf(ib_sel_data_arr_g[3].field_name, "IB3");

}

static void unit_arr_init(void)
{
    memset(&unit_data_arr_g, 0, sizeof(index_type_data_t) * 2);

    unit_data_arr_g[0].field_value = 0;
    sprintf(unit_data_arr_g[0].field_name, "DLN");
    unit_data_arr_g[1].field_value = 1;
    sprintf(unit_data_arr_g[1].field_name, "CLN");

}

static void index_set_eth_port_type_lane_arr_init(void)
{
    memset(&index_set_eth_port_type_lane_arr_g, 0, sizeof(index_set_eth_port_type_lane_arr_g));

    index_set_eth_port_type_lane_arr_g[0][1] = 1;
    index_set_eth_port_type_lane_arr_g[0][6] = 1;
    index_set_eth_port_type_lane_arr_g[0][2] = 1;
    index_set_eth_port_type_lane_arr_g[0][0] = 1;
    index_set_eth_port_type_lane_arr_g[0][7] = 1;
    index_set_eth_port_type_lane_arr_g[0][5] = 1;
    index_set_eth_port_type_lane_arr_g[0][3] = 1;
    index_set_eth_port_type_lane_arr_g[0][4] = 1;
}

static void index_set_eth_port_type_grp_arr_init(void)
{
    memset(&index_set_eth_port_type_grp_arr_g, 0, sizeof(index_set_eth_port_type_grp_arr_g));

    index_set_eth_port_type_grp_arr_g[0][9] = 1;
    index_set_eth_port_type_grp_arr_g[0][17] = 1;
    index_set_eth_port_type_grp_arr_g[0][12] = 1;
    index_set_eth_port_type_grp_arr_g[4][9] = 1;
    index_set_eth_port_type_grp_arr_g[0][5] = 1;
    index_set_eth_port_type_grp_arr_g[2][12] = 1;
    index_set_eth_port_type_grp_arr_g[1][12] = 1;
    index_set_eth_port_type_grp_arr_g[3][12] = 1;
    index_set_eth_port_type_grp_arr_g[5][9] = 1;
    index_set_eth_port_type_grp_arr_g[5][12] = 1;
}

static void index_set_ib_port_type_lane_arr_init(void)
{
    memset(&index_set_ib_port_type_lane_arr_g, 0, sizeof(index_set_ib_port_type_lane_arr_g));

    index_set_ib_port_type_lane_arr_g[0][1] = 1;
    index_set_ib_port_type_lane_arr_g[0][6] = 1;
    index_set_ib_port_type_lane_arr_g[0][2] = 1;
    index_set_ib_port_type_lane_arr_g[0][0] = 1;
    index_set_ib_port_type_lane_arr_g[0][7] = 1;
    index_set_ib_port_type_lane_arr_g[0][5] = 1;
    index_set_ib_port_type_lane_arr_g[0][3] = 1;
    index_set_ib_port_type_lane_arr_g[0][4] = 1;
}

static void index_set_ib_port_type_grp_arr_init(void)
{
    memset(&index_set_ib_port_type_grp_arr_g, 0, sizeof(index_set_ib_port_type_grp_arr_g));

    index_set_ib_port_type_grp_arr_g[0][9] = 1;
    index_set_ib_port_type_grp_arr_g[0][17] = 1;
    index_set_ib_port_type_grp_arr_g[0][12] = 1;
    index_set_ib_port_type_grp_arr_g[4][9] = 1;
    index_set_ib_port_type_grp_arr_g[0][14] = 1;
    index_set_ib_port_type_grp_arr_g[2][12] = 1;
    index_set_ib_port_type_grp_arr_g[1][12] = 1;
    index_set_ib_port_type_grp_arr_g[0][19] = 1;
    index_set_ib_port_type_grp_arr_g[3][12] = 1;
    index_set_ib_port_type_grp_arr_g[0][15] = 1;
    index_set_ib_port_type_grp_arr_g[5][9] = 1;
    index_set_ib_port_type_grp_arr_g[5][12] = 1;
}

static void enum_index_arr_init(void)
{
    port_type_arr_init();
    grp_arr_init();
    page_select_arr_init();
    slot_index_arr_init();
    proto_mask_arr_init();
    ib_sel_arr_init();
    unit_arr_init();

}

static void index_sets_arr_init(void)
{
    index_set_eth_port_type_lane_arr_init();
    index_set_eth_port_type_grp_arr_init();
    index_set_ib_port_type_lane_arr_init();
    index_set_ib_port_type_grp_arr_init();

}

int sx_spice_tree_init(void)
{
    printk(KERN_INFO "sx_spice_tree_init\n");

    enum_index_arr_init();
    index_sets_arr_init();

    root_p = debugfs_create_dir("nvswitch", NULL);
    if (!root_p) {
        goto allocation_failed;
    }

    return 0;

allocation_failed:
    debugfs_remove_recursive(root_p);
    return -ENOMEM;
}

void sx_spice_tree_deinit(void)
{
    printk(KERN_INFO "In sx_spice_tree_deinit function \n");
    debugfs_remove_recursive(root_p);
}

int sx_spice_tree_asic_counters_app_dir_create(void)
{
    asic_counters_p = debugfs_create_dir("asic_counters", root_p);
    if (!asic_counters_p) {
        goto allocation_failed;
    }

    return 0;

allocation_failed:
    return -ENOMEM;
}

int sx_spice_tree_asic_counters_eth_create(dev_private_data_t *dev_data)
{
    int  err;
    char dname[60] = { 0 };

    struct dentry * asic_p;



    printk(KERN_INFO "sx_spice_tree_asic_counters_eth_create\n");

    snprintf(dname, sizeof(dname), "ASIC.%d", dev_data->dev->device_id);
    asic_p = debugfs_create_dir(dname, asic_counters_p);
    if (!asic_p) {
        goto allocation_failed;
    }

    dev_data->asic_counters_root_inode_p = asic_p;

    err = sx_spice_access_reg_bulk_counters_file_create(asic_p, dev_data);
    if (err) {
        goto allocation_failed;
    }

    return 0;

allocation_failed:
    debugfs_remove_recursive(asic_p);
    return -ENOMEM;
}

int sx_spice_tree_ber_app_dir_create(void)
{
    ber_p = debugfs_create_dir("ber", root_p);
    if (!ber_p) {
        goto allocation_failed;
    }

    return 0;

allocation_failed:
    return -ENOMEM;
}

int sx_spice_tree_ber_eth_create(dev_private_data_t *dev_data)
{
    int  err;
    char dname[60] = { 0 };

    struct dentry * asic_p;
    struct dentry * i_p;
    struct dentry * grp_p;
    struct dentry * sensor_index_p;
    struct dentry * page_select_p;
    struct dentry * fom_measurment_p;
    struct dentry * ib_sel_p;
    struct dentry * pll_group_p;
    struct dentry * proto_mask_p;
    struct dentry * lane_p;
    struct dentry * unit_p;
    struct dentry * slot_index_p;
    struct dentry * local_port_p;
    struct dentry * port_type_p;

    int i_it = 0;
    int grp_it = 0;
    int sensor_index_it = 0;
    int page_select_it = 0;
    int fom_measurment_it = 0;
    int ib_sel_it = 0;
    int pll_group_it = 0;
    int proto_mask_it = 0;
    int lane_it = 0;
    int unit_it = 0;
    int slot_index_it = 0;
    int local_port_it = 0;
    int port_type_it = 0;


    printk(KERN_INFO "sx_spice_tree_ber_eth_create\n");

    snprintf(dname, sizeof(dname), "ASIC.%d", dev_data->dev->device_id);
    asic_p = debugfs_create_dir(dname, ber_p);
    if (!asic_p) {
        goto allocation_failed;
    }

    dev_data->ber_root_inode_p = asic_p;

    indexes_arr_g[PNAT] = 0;
    indexes_arr_g[SWID] = 0;
    indexes_arr_g[PRIO_TC] = 0;
    indexes_arr_g[GRP_PROFILE] = 0;
    indexes_arr_g[TEST_MODE] = 0;
    indexes_arr_g[HIST_TYPE] = 0;
    indexes_arr_g[IG] = 0;
    indexes_arr_g[ASIC_INDEX] = 0;
    indexes_arr_g[ENUM_INIT] = 0;
    indexes_arr_g[DB_INDEX] = 0;
    indexes_arr_g[DB] = 0;
    indexes_arr_g[PLANE_IND] = 0;
    err = sx_spice_access_reg_msgi_file_create(asic_p, dev_data);
    if (err) {
        goto allocation_failed;
    }
    err = sx_spice_access_reg_mgir_file_create(asic_p, dev_data);
    if (err) {
        goto allocation_failed;
    }
    err = sx_spice_access_reg_mdir_file_create(asic_p, dev_data);
    if (err) {
        goto allocation_failed;
    }
    err = sx_spice_access_reg_spad_file_create(asic_p, dev_data);
    if (err) {
        goto allocation_failed;
    }
    for (pll_group_it = 1; pll_group_it <= dev_data->max_pll_group; pll_group_it++) {
        snprintf(dname, sizeof(dname), "pll_group.%d", pll_group_it );
        pll_group_p = debugfs_create_dir(dname, asic_p);
        if (!pll_group_p) {
            goto allocation_failed;
        }
        indexes_arr_g[PLL_GROUP] = pll_group_it;

        err = sx_spice_access_reg_ppll_file_create(pll_group_p, dev_data);
        if (err) {
            goto allocation_failed;
        }
    }
    for (local_port_it = 1; local_port_it <= dev_data->max_local_port; local_port_it++) {
        snprintf(dname, sizeof(dname), "local_port.%d", local_port_it );
        local_port_p = debugfs_create_dir(dname, asic_p);
        if (!local_port_p) {
            goto allocation_failed;
        }
        indexes_arr_g[LOCAL_PORT] = local_port_it;

        err = sx_spice_access_reg_pmdr_file_create(local_port_p, dev_data);
        if (err) {
            goto allocation_failed;
        }
        err = sx_spice_access_reg_pphcr_file_create(local_port_p, dev_data);
        if (err) {
            goto allocation_failed;
        }
        for (port_type_it = 0; port_type_it < 6; port_type_it++) {
            snprintf(dname, sizeof(dname), "port_type.%s.0x%X",
                port_type_data_arr_g[port_type_it].field_name,
                port_type_data_arr_g[port_type_it].field_value);
            port_type_p = debugfs_create_dir(dname, local_port_p);

            if (!port_type_p) {
                goto allocation_failed;
            }
            indexes_arr_g[PORT_TYPE] = port_type_data_arr_g[port_type_it].field_value;

            for (lane_it = 0; lane_it <= 7; lane_it++) {
                if (index_set_eth_port_type_lane_arr_g[port_type_it][lane_it]) {
                    snprintf(dname, sizeof(dname), "lane.%d", lane_it );
                    lane_p = debugfs_create_dir(dname, port_type_p);
                    if (!lane_p) {
                        goto allocation_failed;
                    }
                    indexes_arr_g[LANE] = lane_it;

                    if (is_ib_sel_dir_supported(dev_data)) {
                        for (ib_sel_it = 0; ib_sel_it < 4; ib_sel_it++) {
                            snprintf(dname, sizeof(dname), "ib_sel.%s.0x%X",
                                ib_sel_data_arr_g[ib_sel_it].field_name,
                                ib_sel_data_arr_g[ib_sel_it].field_value);
                            ib_sel_p = debugfs_create_dir(dname, lane_p);

                            if (!ib_sel_p) {
                                goto allocation_failed;
                            }
                            indexes_arr_g[IB_SEL] = ib_sel_data_arr_g[ib_sel_it].field_value;

                            err = sx_spice_access_reg_slrip_file_create(ib_sel_p, dev_data);
                            if (err) {
                                goto allocation_failed;
                            }
                        }
                     } else {
                        err = sx_spice_access_reg_slrip_file_create(lane_p, dev_data);
                        if (err) {
                            goto allocation_failed;
                        }
                     }

                    if (is_fom_measurment_dir_supported(dev_data)) {
                        for (fom_measurment_it = 0; fom_measurment_it <= 15; fom_measurment_it++) {
                            snprintf(dname, sizeof(dname), "fom_measurment.%d", fom_measurment_it );
                            fom_measurment_p = debugfs_create_dir(dname, lane_p);
                            if (!fom_measurment_p) {
                                goto allocation_failed;
                            }
                            indexes_arr_g[FOM_MEASURMENT] = fom_measurment_it;

                            err = sx_spice_access_reg_slrg_file_create(fom_measurment_p, dev_data);
                            if (err) {
                                goto allocation_failed;
                            }
                        }
                     } else {
                        err = sx_spice_access_reg_slrg_file_create(lane_p, dev_data);
                        if (err) {
                            goto allocation_failed;
                        }
                     }

                    err = sx_spice_access_reg_slrp_file_create(lane_p, dev_data);
                    if (err) {
                        goto allocation_failed;
                    }
                    err = sx_spice_access_reg_sltp_file_create(lane_p, dev_data);
                    if (err) {
                        goto allocation_failed;
                    }
                    err = sx_spice_access_reg_sllm_file_create(lane_p, dev_data);
                    if (err) {
                        goto allocation_failed;
                    }
                }
            }
            for (grp_it = 0; grp_it < 20; grp_it++) {
                if (index_set_eth_port_type_grp_arr_g[port_type_it][grp_it]) {
                    snprintf(dname, sizeof(dname), "grp.%s.0x%X",
                        grp_data_arr_g[grp_it].field_name,
                        grp_data_arr_g[grp_it].field_value);
                    grp_p = debugfs_create_dir(dname, port_type_p);

                    if (!grp_p) {
                        goto allocation_failed;
                    }
                    indexes_arr_g[GRP] = grp_data_arr_g[grp_it].field_value;

                    err = sx_spice_access_reg_ppcnt_file_create(grp_p, dev_data);
                    if (err) {
                        goto allocation_failed;
                    }
                }
            }
            for (proto_mask_it = 0; proto_mask_it < 2; proto_mask_it++) {
                snprintf(dname, sizeof(dname), "proto_mask.%s.0x%X",
                    proto_mask_data_arr_g[proto_mask_it].field_name,
                    proto_mask_data_arr_g[proto_mask_it].field_value);
                proto_mask_p = debugfs_create_dir(dname, port_type_p);

                if (!proto_mask_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[PROTO_MASK] = proto_mask_data_arr_g[proto_mask_it].field_value;

                err = sx_spice_access_reg_ptys_file_create(proto_mask_p, dev_data);
                if (err) {
                    goto allocation_failed;
                }
            }
            for (page_select_it = 0; page_select_it < 13; page_select_it++) {
                snprintf(dname, sizeof(dname), "page_select.%s.0x%X",
                    page_select_data_arr_g[page_select_it].field_name,
                    page_select_data_arr_g[page_select_it].field_value);
                page_select_p = debugfs_create_dir(dname, port_type_p);

                if (!page_select_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[PAGE_SELECT] = page_select_data_arr_g[page_select_it].field_value;

                err = sx_spice_access_reg_pddr_file_create(page_select_p, dev_data);
                if (err) {
                    goto allocation_failed;
                }
            }
        }
        if (is_lane_dir_supported(dev_data)) {
            for (lane_it = 0; lane_it <= 7; lane_it++) {
                snprintf(dname, sizeof(dname), "lane.%d", lane_it );
                lane_p = debugfs_create_dir(dname, local_port_p);
                if (!lane_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[LANE] = lane_it;

                for (unit_it = 0; unit_it < 2; unit_it++) {
                    snprintf(dname, sizeof(dname), "unit.%s.0x%X",
                        unit_data_arr_g[unit_it].field_name,
                        unit_data_arr_g[unit_it].field_value);
                    unit_p = debugfs_create_dir(dname, lane_p);

                    if (!unit_p) {
                        goto allocation_failed;
                    }
                    indexes_arr_g[UNIT] = unit_data_arr_g[unit_it].field_value;

                    err = sx_spice_access_reg_peucg_file_create(unit_p, dev_data);
                    if (err) {
                        goto allocation_failed;
                    }
                }
            }
         }
    }
    for (slot_index_it = 0; slot_index_it < 1; slot_index_it++) {
        snprintf(dname, sizeof(dname), "slot_index.%s.0x%X",
            slot_index_data_arr_g[slot_index_it].field_name,
            slot_index_data_arr_g[slot_index_it].field_value);
        slot_index_p = debugfs_create_dir(dname, asic_p);

        if (!slot_index_p) {
            goto allocation_failed;
        }
        indexes_arr_g[SLOT_INDEX] = slot_index_data_arr_g[slot_index_it].field_value;

        err = sx_spice_access_reg_mvcap_file_create(slot_index_p, dev_data);
        if (err) {
            goto allocation_failed;
        }
        err = sx_spice_access_reg_mtcap_file_create(slot_index_p, dev_data);
        if (err) {
            goto allocation_failed;
        }
        for (i_it = 0; i_it <= 0; i_it++) {
            snprintf(dname, sizeof(dname), "i.%d", i_it );
            i_p = debugfs_create_dir(dname, slot_index_p);
            if (!i_p) {
                goto allocation_failed;
            }
            indexes_arr_g[I] = i_it;

            for (sensor_index_it = 0; sensor_index_it <= dev_data->max_sensor_index; sensor_index_it++) {
                snprintf(dname, sizeof(dname), "sensor_index.%d", sensor_index_it );
                sensor_index_p = debugfs_create_dir(dname, i_p);
                if (!sensor_index_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[SENSOR_INDEX] = sensor_index_it;

                err = sx_spice_access_reg_mtmp_file_create(sensor_index_p, dev_data);
                if (err) {
                    goto allocation_failed;
                }
            }
            for (sensor_index_it = 64; sensor_index_it <= 127; sensor_index_it++) {
                snprintf(dname, sizeof(dname), "sensor_index.%d", sensor_index_it );
                sensor_index_p = debugfs_create_dir(dname, i_p);
                if (!sensor_index_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[SENSOR_INDEX] = sensor_index_it;

                err = sx_spice_access_reg_mtmp_file_create(sensor_index_p, dev_data);
                if (err) {
                    goto allocation_failed;
                }
            }
            for (sensor_index_it = 256; sensor_index_it <= 263; sensor_index_it++) {
                snprintf(dname, sizeof(dname), "sensor_index.%d", sensor_index_it );
                sensor_index_p = debugfs_create_dir(dname, i_p);
                if (!sensor_index_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[SENSOR_INDEX] = sensor_index_it;

                err = sx_spice_access_reg_mtmp_file_create(sensor_index_p, dev_data);
                if (err) {
                    goto allocation_failed;
                }
            }
        }
        for (i_it = 1; i_it <= 1; i_it++) {
            snprintf(dname, sizeof(dname), "i.%d", i_it );
            i_p = debugfs_create_dir(dname, slot_index_p);
            if (!i_p) {
                goto allocation_failed;
            }
            indexes_arr_g[I] = i_it;

            for (sensor_index_it = 1; sensor_index_it <= 150; sensor_index_it++) {
                snprintf(dname, sizeof(dname), "sensor_index.%d", sensor_index_it );
                sensor_index_p = debugfs_create_dir(dname, i_p);
                if (!sensor_index_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[SENSOR_INDEX] = sensor_index_it;

                err = sx_spice_access_reg_mtmp_file_create(sensor_index_p, dev_data);
                if (err) {
                    goto allocation_failed;
                }
            }
        }
    }

    return 0;

allocation_failed:
    debugfs_remove_recursive(asic_p);
    return -ENOMEM;
}

int sx_spice_tree_ber_ib_create(dev_private_data_t *dev_data)
{
    int  err;
    char dname[60] = { 0 };

    struct dentry * asic_p;
    struct dentry * i_p;
    struct dentry * router_entity_p;
    struct dentry * grp_p;
    struct dentry * sensor_index_p;
    struct dentry * page_select_p;
    struct dentry * fom_measurment_p;
    struct dentry * ib_sel_p;
    struct dentry * pll_group_p;
    struct dentry * proto_mask_p;
    struct dentry * lane_p;
    struct dentry * unit_p;
    struct dentry * slot_index_p;
    struct dentry * local_port_p;
    struct dentry * port_type_p;

    int i_it = 0;
    int router_entity_it = 0;
    int grp_it = 0;
    int sensor_index_it = 0;
    int page_select_it = 0;
    int fom_measurment_it = 0;
    int ib_sel_it = 0;
    int pll_group_it = 0;
    int proto_mask_it = 0;
    int lane_it = 0;
    int unit_it = 0;
    int slot_index_it = 0;
    int local_port_it = 0;
    int port_type_it = 0;


    printk(KERN_INFO "sx_spice_tree_ber_ib_create\n");

    snprintf(dname, sizeof(dname), "ASIC.%d", dev_data->dev->device_id);
    asic_p = debugfs_create_dir(dname, ber_p);
    if (!asic_p) {
        goto allocation_failed;
    }

    dev_data->ber_root_inode_p = asic_p;

    indexes_arr_g[PNAT] = 0;
    indexes_arr_g[SWID] = 0;
    indexes_arr_g[PRIO_TC] = 0;
    indexes_arr_g[GRP_PROFILE] = 0;
    indexes_arr_g[IG] = 0;
    indexes_arr_g[ASIC_INDEX] = 0;
    indexes_arr_g[HIST_TYPE] = 0;
    indexes_arr_g[ENUM_INIT] = 0;
    indexes_arr_g[DB_INDEX] = 0;
    indexes_arr_g[DB] = 0;
    indexes_arr_g[PLANE_IND] = 0;
    err = sx_spice_access_reg_msgi_file_create(asic_p, dev_data);
    if (err) {
        goto allocation_failed;
    }
    err = sx_spice_access_reg_mgir_file_create(asic_p, dev_data);
    if (err) {
        goto allocation_failed;
    }
    err = sx_spice_access_reg_mdir_file_create(asic_p, dev_data);
    if (err) {
        goto allocation_failed;
    }
    for (router_entity_it = 0; router_entity_it <= 1; router_entity_it++) {
        snprintf(dname, sizeof(dname), "router_entity.%d", router_entity_it );
        router_entity_p = debugfs_create_dir(dname, asic_p);
        if (!router_entity_p) {
            goto allocation_failed;
        }
        indexes_arr_g[ROUTER_ENTITY] = router_entity_it;

        err = sx_spice_access_reg_spzr_file_create(router_entity_p, dev_data);
        if (err) {
            goto allocation_failed;
        }
    }
    for (pll_group_it = 1; pll_group_it <= dev_data->max_pll_group; pll_group_it++) {
        snprintf(dname, sizeof(dname), "pll_group.%d", pll_group_it );
        pll_group_p = debugfs_create_dir(dname, asic_p);
        if (!pll_group_p) {
            goto allocation_failed;
        }
        indexes_arr_g[PLL_GROUP] = pll_group_it;

        err = sx_spice_access_reg_ppll_file_create(pll_group_p, dev_data);
        if (err) {
            goto allocation_failed;
        }
    }
    for (local_port_it = 1; local_port_it <= dev_data->max_local_port; local_port_it++) {
        snprintf(dname, sizeof(dname), "local_port.%d", local_port_it );
        local_port_p = debugfs_create_dir(dname, asic_p);
        if (!local_port_p) {
            goto allocation_failed;
        }
        indexes_arr_g[LOCAL_PORT] = local_port_it;

        err = sx_spice_access_reg_pmdr_file_create(local_port_p, dev_data);
        if (err) {
            goto allocation_failed;
        }
        err = sx_spice_access_reg_pphcr_file_create(local_port_p, dev_data);
        if (err) {
            goto allocation_failed;
        }
        for (port_type_it = 0; port_type_it < 6; port_type_it++) {
            snprintf(dname, sizeof(dname), "port_type.%s.0x%X",
                port_type_data_arr_g[port_type_it].field_name,
                port_type_data_arr_g[port_type_it].field_value);
            port_type_p = debugfs_create_dir(dname, local_port_p);

            if (!port_type_p) {
                goto allocation_failed;
            }
            indexes_arr_g[PORT_TYPE] = port_type_data_arr_g[port_type_it].field_value;

            for (lane_it = 0; lane_it <= 7; lane_it++) {
                if (index_set_ib_port_type_lane_arr_g[port_type_it][lane_it]) {
                    snprintf(dname, sizeof(dname), "lane.%d", lane_it );
                    lane_p = debugfs_create_dir(dname, port_type_p);
                    if (!lane_p) {
                        goto allocation_failed;
                    }
                    indexes_arr_g[LANE] = lane_it;

                    if (is_ib_sel_dir_supported(dev_data)) {
                        for (ib_sel_it = 0; ib_sel_it < 4; ib_sel_it++) {
                            snprintf(dname, sizeof(dname), "ib_sel.%s.0x%X",
                                ib_sel_data_arr_g[ib_sel_it].field_name,
                                ib_sel_data_arr_g[ib_sel_it].field_value);
                            ib_sel_p = debugfs_create_dir(dname, lane_p);

                            if (!ib_sel_p) {
                                goto allocation_failed;
                            }
                            indexes_arr_g[IB_SEL] = ib_sel_data_arr_g[ib_sel_it].field_value;

                            err = sx_spice_access_reg_slrip_file_create(ib_sel_p, dev_data);
                            if (err) {
                                goto allocation_failed;
                            }
                        }
                     } else {
                        err = sx_spice_access_reg_slrip_file_create(lane_p, dev_data);
                        if (err) {
                            goto allocation_failed;
                        }
                     }

                    if (is_fom_measurment_dir_supported(dev_data)) {
                        for (fom_measurment_it = 0; fom_measurment_it <= 15; fom_measurment_it++) {
                            snprintf(dname, sizeof(dname), "fom_measurment.%d", fom_measurment_it );
                            fom_measurment_p = debugfs_create_dir(dname, lane_p);
                            if (!fom_measurment_p) {
                                goto allocation_failed;
                            }
                            indexes_arr_g[FOM_MEASURMENT] = fom_measurment_it;

                            err = sx_spice_access_reg_slrg_file_create(fom_measurment_p, dev_data);
                            if (err) {
                                goto allocation_failed;
                            }
                        }
                     } else {
                        err = sx_spice_access_reg_slrg_file_create(lane_p, dev_data);
                        if (err) {
                            goto allocation_failed;
                        }
                     }

                    err = sx_spice_access_reg_slrp_file_create(lane_p, dev_data);
                    if (err) {
                        goto allocation_failed;
                    }
                    err = sx_spice_access_reg_sltp_file_create(lane_p, dev_data);
                    if (err) {
                        goto allocation_failed;
                    }
                    err = sx_spice_access_reg_sllm_file_create(lane_p, dev_data);
                    if (err) {
                        goto allocation_failed;
                    }
                }
            }
            for (grp_it = 0; grp_it < 20; grp_it++) {
                if (index_set_ib_port_type_grp_arr_g[port_type_it][grp_it]) {
                    snprintf(dname, sizeof(dname), "grp.%s.0x%X",
                        grp_data_arr_g[grp_it].field_name,
                        grp_data_arr_g[grp_it].field_value);
                    grp_p = debugfs_create_dir(dname, port_type_p);

                    if (!grp_p) {
                        goto allocation_failed;
                    }
                    indexes_arr_g[GRP] = grp_data_arr_g[grp_it].field_value;

                    err = sx_spice_access_reg_ppcnt_file_create(grp_p, dev_data);
                    if (err) {
                        goto allocation_failed;
                    }
                }
            }
            for (proto_mask_it = 0; proto_mask_it < 2; proto_mask_it++) {
                snprintf(dname, sizeof(dname), "proto_mask.%s.0x%X",
                    proto_mask_data_arr_g[proto_mask_it].field_name,
                    proto_mask_data_arr_g[proto_mask_it].field_value);
                proto_mask_p = debugfs_create_dir(dname, port_type_p);

                if (!proto_mask_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[PROTO_MASK] = proto_mask_data_arr_g[proto_mask_it].field_value;

                err = sx_spice_access_reg_ptys_file_create(proto_mask_p, dev_data);
                if (err) {
                    goto allocation_failed;
                }
            }
            for (page_select_it = 0; page_select_it < 13; page_select_it++) {
                snprintf(dname, sizeof(dname), "page_select.%s.0x%X",
                    page_select_data_arr_g[page_select_it].field_name,
                    page_select_data_arr_g[page_select_it].field_value);
                page_select_p = debugfs_create_dir(dname, port_type_p);

                if (!page_select_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[PAGE_SELECT] = page_select_data_arr_g[page_select_it].field_value;

                err = sx_spice_access_reg_pddr_file_create(page_select_p, dev_data);
                if (err) {
                    goto allocation_failed;
                }
            }
        }
        if (is_lane_dir_supported(dev_data)) {
            for (lane_it = 0; lane_it <= 7; lane_it++) {
                snprintf(dname, sizeof(dname), "lane.%d", lane_it );
                lane_p = debugfs_create_dir(dname, local_port_p);
                if (!lane_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[LANE] = lane_it;

                for (unit_it = 0; unit_it < 2; unit_it++) {
                    snprintf(dname, sizeof(dname), "unit.%s.0x%X",
                        unit_data_arr_g[unit_it].field_name,
                        unit_data_arr_g[unit_it].field_value);
                    unit_p = debugfs_create_dir(dname, lane_p);

                    if (!unit_p) {
                        goto allocation_failed;
                    }
                    indexes_arr_g[UNIT] = unit_data_arr_g[unit_it].field_value;

                    err = sx_spice_access_reg_peucg_file_create(unit_p, dev_data);
                    if (err) {
                        goto allocation_failed;
                    }
                }
            }
         }
    }
    for (slot_index_it = 0; slot_index_it < 1; slot_index_it++) {
        snprintf(dname, sizeof(dname), "slot_index.%s.0x%X",
            slot_index_data_arr_g[slot_index_it].field_name,
            slot_index_data_arr_g[slot_index_it].field_value);
        slot_index_p = debugfs_create_dir(dname, asic_p);

        if (!slot_index_p) {
            goto allocation_failed;
        }
        indexes_arr_g[SLOT_INDEX] = slot_index_data_arr_g[slot_index_it].field_value;

        err = sx_spice_access_reg_mvcap_file_create(slot_index_p, dev_data);
        if (err) {
            goto allocation_failed;
        }
        err = sx_spice_access_reg_mtcap_file_create(slot_index_p, dev_data);
        if (err) {
            goto allocation_failed;
        }
        for (i_it = 0; i_it <= 0; i_it++) {
            snprintf(dname, sizeof(dname), "i.%d", i_it );
            i_p = debugfs_create_dir(dname, slot_index_p);
            if (!i_p) {
                goto allocation_failed;
            }
            indexes_arr_g[I] = i_it;

            for (sensor_index_it = 0; sensor_index_it <= dev_data->max_sensor_index; sensor_index_it++) {
                snprintf(dname, sizeof(dname), "sensor_index.%d", sensor_index_it );
                sensor_index_p = debugfs_create_dir(dname, i_p);
                if (!sensor_index_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[SENSOR_INDEX] = sensor_index_it;

                err = sx_spice_access_reg_mtmp_file_create(sensor_index_p, dev_data);
                if (err) {
                    goto allocation_failed;
                }
            }
            for (sensor_index_it = 64; sensor_index_it <= 127; sensor_index_it++) {
                snprintf(dname, sizeof(dname), "sensor_index.%d", sensor_index_it );
                sensor_index_p = debugfs_create_dir(dname, i_p);
                if (!sensor_index_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[SENSOR_INDEX] = sensor_index_it;

                err = sx_spice_access_reg_mtmp_file_create(sensor_index_p, dev_data);
                if (err) {
                    goto allocation_failed;
                }
            }
            for (sensor_index_it = 256; sensor_index_it <= 263; sensor_index_it++) {
                snprintf(dname, sizeof(dname), "sensor_index.%d", sensor_index_it );
                sensor_index_p = debugfs_create_dir(dname, i_p);
                if (!sensor_index_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[SENSOR_INDEX] = sensor_index_it;

                err = sx_spice_access_reg_mtmp_file_create(sensor_index_p, dev_data);
                if (err) {
                    goto allocation_failed;
                }
            }
        }
        for (i_it = 1; i_it <= 1; i_it++) {
            snprintf(dname, sizeof(dname), "i.%d", i_it );
            i_p = debugfs_create_dir(dname, slot_index_p);
            if (!i_p) {
                goto allocation_failed;
            }
            indexes_arr_g[I] = i_it;

            for (sensor_index_it = 1; sensor_index_it <= 150; sensor_index_it++) {
                snprintf(dname, sizeof(dname), "sensor_index.%d", sensor_index_it );
                sensor_index_p = debugfs_create_dir(dname, i_p);
                if (!sensor_index_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[SENSOR_INDEX] = sensor_index_it;

                err = sx_spice_access_reg_mtmp_file_create(sensor_index_p, dev_data);
                if (err) {
                    goto allocation_failed;
                }
            }
        }
    }

    return 0;

allocation_failed:
    debugfs_remove_recursive(asic_p);
    return -ENOMEM;
}



