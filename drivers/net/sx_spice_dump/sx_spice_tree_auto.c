/*
 * Copyright © 2021-2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
#include "sx_spice_access_reg_auto.h"

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

static struct dentry * root_p;
static struct dentry * ber_p;
static struct dentry * ber_p;
static struct dentry * local_port_p;
static struct dentry * port_type_p;
static struct dentry * grp_p;
static struct dentry * page_select_p;
static struct dentry * slot_index_p;
static struct dentry * proto_mask_p;

static int local_port_it = 0;
static int port_type_it = 0;
static int grp_it = 0;
static int page_select_it = 0;
static int slot_index_it = 0;
static int proto_mask_it = 0;


/************************************************
 *  Local function declarations
 ***********************************************/
static void port_type_arr_init(void);
static void grp_arr_init(void);
static void page_select_arr_init(void);
static void slot_index_arr_init(void);
static void proto_mask_arr_init(void);

static void enum_index_arr_init(void);


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

static void enum_index_arr_init(void)
{
    port_type_arr_init();
    grp_arr_init();
    page_select_arr_init();
    slot_index_arr_init();
    proto_mask_arr_init();
}

int sx_spice_tree_init(void)
{
    printk(KERN_INFO "sx_spice_tree_init\n");

    enum_index_arr_init();

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
    printk(KERN_ERR "In sx_spice_tree_deinit function \n");
    debugfs_remove_recursive(root_p);
}

int sx_spice_tree_ber_eth_create(void)
{
    int  err;
    char dname[60] = { 0 };

    printk(KERN_INFO "sx_spice_tree_ber_eth_create\n");

    ber_p = debugfs_create_dir("ber", root_p);
    if (!ber_p) {
        goto allocation_failed;
    }

    indexes_arr_g[PNAT] = 0;
    indexes_arr_g[SWID] = 0;
    indexes_arr_g[PRIO_TC] = 0;
    err = sx_spice_access_reg_msgi_file_create(ber_p);
    if (err) {
        goto allocation_failed;
    }
    err = sx_spice_access_reg_mgir_file_create(ber_p);
    if (err) {
        goto allocation_failed;
    }
    err = sx_spice_access_reg_mdir_file_create(ber_p);
    if (err) {
        goto allocation_failed;
    }
    err = sx_spice_access_reg_spad_file_create(ber_p);
    if (err) {
        goto allocation_failed;
    }
    for (local_port_it = 1; local_port_it <= 128; local_port_it++) {
        snprintf(dname, sizeof(dname), "local_port.%d", local_port_it);
        local_port_p = debugfs_create_dir(dname, ber_p);
        if (!local_port_p) {
            goto allocation_failed;
        }
        indexes_arr_g[LOCAL_PORT] = local_port_it;

        err = sx_spice_access_reg_pmdr_file_create(local_port_p);
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

            for (grp_it = 0; grp_it < 20; grp_it++) {
                snprintf(dname, sizeof(dname), "grp.%s.0x%X",
                         grp_data_arr_g[grp_it].field_name,
                         grp_data_arr_g[grp_it].field_value);
                grp_p = debugfs_create_dir(dname, port_type_p);

                if (!grp_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[GRP] = grp_data_arr_g[grp_it].field_value;

                err = sx_spice_access_reg_ppcnt_file_create(grp_p);
                if (err) {
                    goto allocation_failed;
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

                err = sx_spice_access_reg_ptys_file_create(proto_mask_p);
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

                err = sx_spice_access_reg_pddr_file_create(page_select_p);
                if (err) {
                    goto allocation_failed;
                }
            }
        }
    }
    for (slot_index_it = 0; slot_index_it < 1; slot_index_it++) {
        snprintf(dname, sizeof(dname), "slot_index.%s.0x%X",
                 slot_index_data_arr_g[slot_index_it].field_name,
                 slot_index_data_arr_g[slot_index_it].field_value);
        slot_index_p = debugfs_create_dir(dname, ber_p);

        if (!slot_index_p) {
            goto allocation_failed;
        }
        indexes_arr_g[SLOT_INDEX] = slot_index_data_arr_g[slot_index_it].field_value;

        err = sx_spice_access_reg_mvcap_file_create(slot_index_p);
        if (err) {
            goto allocation_failed;
        }
        err = sx_spice_access_reg_mtcap_file_create(slot_index_p);
        if (err) {
            goto allocation_failed;
        }
    }

    return 0;

allocation_failed:
    debugfs_remove_recursive(ber_p);
    return -ENOMEM;
}

void sx_spice_tree_ber_eth_destroy(void)
{
    printk(KERN_ERR "In sx_spice_tree_ber_eth_destroy function \n");
    debugfs_remove_recursive(ber_p);
}

int sx_spice_tree_ber_ib_create(void)
{
    int  err;
    char dname[60] = { 0 };

    printk(KERN_INFO "sx_spice_tree_ber_ib_create\n");

    ber_p = debugfs_create_dir("ber", root_p);
    if (!ber_p) {
        goto allocation_failed;
    }

    indexes_arr_g[PNAT] = 0;
    indexes_arr_g[SWID] = 0;
    indexes_arr_g[PRIO_TC] = 0;
    err = sx_spice_access_reg_msgi_file_create(ber_p);
    if (err) {
        goto allocation_failed;
    }
    err = sx_spice_access_reg_mgir_file_create(ber_p);
    if (err) {
        goto allocation_failed;
    }
    err = sx_spice_access_reg_mdir_file_create(ber_p);
    if (err) {
        goto allocation_failed;
    }
    err = sx_spice_access_reg_spzr_file_create(ber_p);
    if (err) {
        goto allocation_failed;
    }
    for (local_port_it = 1; local_port_it <= 128; local_port_it++) {
        snprintf(dname, sizeof(dname), "local_port.%d", local_port_it);
        local_port_p = debugfs_create_dir(dname, ber_p);
        if (!local_port_p) {
            goto allocation_failed;
        }
        indexes_arr_g[LOCAL_PORT] = local_port_it;

        err = sx_spice_access_reg_pmdr_file_create(local_port_p);
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

            for (grp_it = 0; grp_it < 20; grp_it++) {
                snprintf(dname, sizeof(dname), "grp.%s.0x%X",
                         grp_data_arr_g[grp_it].field_name,
                         grp_data_arr_g[grp_it].field_value);
                grp_p = debugfs_create_dir(dname, port_type_p);

                if (!grp_p) {
                    goto allocation_failed;
                }
                indexes_arr_g[GRP] = grp_data_arr_g[grp_it].field_value;

                err = sx_spice_access_reg_ppcnt_file_create(grp_p);
                if (err) {
                    goto allocation_failed;
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

                err = sx_spice_access_reg_ptys_file_create(proto_mask_p);
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

                err = sx_spice_access_reg_pddr_file_create(page_select_p);
                if (err) {
                    goto allocation_failed;
                }
            }
        }
    }
    for (slot_index_it = 0; slot_index_it < 1; slot_index_it++) {
        snprintf(dname, sizeof(dname), "slot_index.%s.0x%X",
                 slot_index_data_arr_g[slot_index_it].field_name,
                 slot_index_data_arr_g[slot_index_it].field_value);
        slot_index_p = debugfs_create_dir(dname, ber_p);

        if (!slot_index_p) {
            goto allocation_failed;
        }
        indexes_arr_g[SLOT_INDEX] = slot_index_data_arr_g[slot_index_it].field_value;

        err = sx_spice_access_reg_mvcap_file_create(slot_index_p);
        if (err) {
            goto allocation_failed;
        }
        err = sx_spice_access_reg_mtcap_file_create(slot_index_p);
        if (err) {
            goto allocation_failed;
        }
    }

    return 0;

allocation_failed:
    debugfs_remove_recursive(ber_p);
    return -ENOMEM;
}

void sx_spice_tree_ber_ib_destroy(void)
{
    printk(KERN_ERR "In sx_spice_tree_ber_ib_destroy function \n");
    debugfs_remove_recursive(ber_p);
}
