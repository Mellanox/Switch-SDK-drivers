
/*
 * THIS FILE IS AUTO GENERATED.
 * DO NOT MAKE ANY CHANGES!
 * They will be erased with next update.
 *
 */

#include "sx_spice_wrapper.h"
#include "sx_spice_access_reg_auto.h"
#include "sx_spice_tree_auto.h"


/************************************************
 *  Local variables
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

static LIST_HEAD(__pmdr_list_head);
static LIST_HEAD(__mvcap_list_head);
static LIST_HEAD(__pddr_list_head);
static LIST_HEAD(__mgir_list_head);
static LIST_HEAD(__ppcnt_list_head);
static LIST_HEAD(__spzr_list_head);
static LIST_HEAD(__mtcap_list_head);
static LIST_HEAD(__ptys_list_head);
static LIST_HEAD(__mdir_list_head);
static LIST_HEAD(__spad_list_head);
static LIST_HEAD(__msgi_list_head);


/************************************************
 *  Local function declarations
 ***********************************************/

static int __pmdr_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_pmdr_reg * reg_data);
static ssize_t __pmdr_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);
static int __mvcap_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_mvcap_reg * reg_data);
static ssize_t __mvcap_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);
static int __pddr_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_pddr_reg * reg_data);
static ssize_t __pddr_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);
static int __mgir_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_mgir_reg * reg_data);
static ssize_t __mgir_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);
static int __ppcnt_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_ppcnt_reg * reg_data);
static ssize_t __ppcnt_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);
static int __spzr_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_spzr_reg * reg_data);
static ssize_t __spzr_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);
static int __mtcap_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_mtcap_reg * reg_data);
static ssize_t __mtcap_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);
static int __ptys_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_ptys_reg * reg_data);
static ssize_t __ptys_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);
static int __mdir_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_mdir_reg * reg_data);
static ssize_t __mdir_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);
static int __spad_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_spad_reg * reg_data);
static ssize_t __spad_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);
static int __msgi_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_msgi_reg * reg_data);
static ssize_t __msgi_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos);


/************************************************
 * Functions                                    *
 ***********************************************/

/* reg data to buffer print */
int __pmdr_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_pmdr_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "status: 0x%x\n", reg_data->pmdr_reg.status);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "version: 0x%x\n", reg_data->pmdr_reg.version);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->pmdr_reg.local_port, reg_data->pmdr_reg.lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->pmdr_reg.pnat);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "gb_valid: 0x%x\n", reg_data->pmdr_reg.gb_valid);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "mcm_tile_valid: 0x%x\n", reg_data->pmdr_reg.mcm_tile_valid);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pport: 0x%x\n", reg_data->pmdr_reg.pport);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "module: 0x%x\n", reg_data->pmdr_reg.module);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "cluster: 0x%x\n", reg_data->pmdr_reg.cluster);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "clp_4x: 0x%x\n", reg_data->pmdr_reg.clp_4x);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "clp_1x: 0x%x\n", reg_data->pmdr_reg.clp_1x);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "gb_dp_num: 0x%x\n", reg_data->pmdr_reg.gb_dp_num);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "split: 0x%x\n", reg_data->pmdr_reg.split);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "swid: 0x%x\n", reg_data->pmdr_reg.swid);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "module_lane_mask: 0x%x\n", reg_data->pmdr_reg.module_lane_mask);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_port: 0x%x\n", reg_data->pmdr_reg.ib_port);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "label_port_query: 0x%x\n", reg_data->pmdr_reg.label_port_query);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port_query: 0x%x\n", reg_data->pmdr_reg.local_port_query);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "usr_sd_4x_tx: 0x%x\n", reg_data->pmdr_reg.usr_sd_4x_tx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "usr_sd_4x_rx: 0x%x\n", reg_data->pmdr_reg.usr_sd_4x_rx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "slot_index: 0x%x\n", reg_data->pmdr_reg.slot_index);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "tile_cluster: 0x%x\n", reg_data->pmdr_reg.tile_cluster);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "mcm_tile_num: 0x%x\n", reg_data->pmdr_reg.mcm_tile_num);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "tile_pport: 0x%x\n", reg_data->pmdr_reg.tile_pport);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "gearbox_die_num: 0x%x\n", reg_data->pmdr_reg.gearbox_die_num);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "vl_num: 0x%x\n", reg_data->pmdr_reg.vl_num);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane7_physical_rx: 0x%x\n", reg_data->pmdr_reg.lane7_physical_rx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane6_physical_rx: 0x%x\n", reg_data->pmdr_reg.lane6_physical_rx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane5_physical_rx: 0x%x\n", reg_data->pmdr_reg.lane5_physical_rx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane4_physical_rx: 0x%x\n", reg_data->pmdr_reg.lane4_physical_rx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane3_physical_rx: 0x%x\n", reg_data->pmdr_reg.lane3_physical_rx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane2_physical_rx: 0x%x\n", reg_data->pmdr_reg.lane2_physical_rx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane1_physical_rx: 0x%x\n", reg_data->pmdr_reg.lane1_physical_rx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane0_physical_rx: 0x%x\n", reg_data->pmdr_reg.lane0_physical_rx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_index: 0x%x\n", reg_data->pmdr_reg.pll_index);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane7_physical_tx: 0x%x\n", reg_data->pmdr_reg.lane7_physical_tx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane6_physical_tx: 0x%x\n", reg_data->pmdr_reg.lane6_physical_tx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane5_physical_tx: 0x%x\n", reg_data->pmdr_reg.lane5_physical_tx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane4_physical_tx: 0x%x\n", reg_data->pmdr_reg.lane4_physical_tx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane3_physical_tx: 0x%x\n", reg_data->pmdr_reg.lane3_physical_tx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane2_physical_tx: 0x%x\n", reg_data->pmdr_reg.lane2_physical_tx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane1_physical_tx: 0x%x\n", reg_data->pmdr_reg.lane1_physical_tx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lane0_physical_tx: 0x%x\n", reg_data->pmdr_reg.lane0_physical_tx);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL7_lane_map: 0x%x\n", reg_data->pmdr_reg.VL7_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL6_lane_map: 0x%x\n", reg_data->pmdr_reg.VL6_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL5_lane_map: 0x%x\n", reg_data->pmdr_reg.VL5_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL4_lane_map: 0x%x\n", reg_data->pmdr_reg.VL4_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL3_lane_map: 0x%x\n", reg_data->pmdr_reg.VL3_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL2_lane_map: 0x%x\n", reg_data->pmdr_reg.VL2_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL1_lane_map: 0x%x\n", reg_data->pmdr_reg.VL1_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL0_lane_map: 0x%x\n", reg_data->pmdr_reg.VL0_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL15_lane_map: 0x%x\n", reg_data->pmdr_reg.VL15_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL14_lane_map: 0x%x\n", reg_data->pmdr_reg.VL14_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL13_lane_map: 0x%x\n", reg_data->pmdr_reg.VL13_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL12_lane_map: 0x%x\n", reg_data->pmdr_reg.VL12_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL11_lane_map: 0x%x\n", reg_data->pmdr_reg.VL11_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL10_lane_map: 0x%x\n", reg_data->pmdr_reg.VL10_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL9_lane_map: 0x%x\n", reg_data->pmdr_reg.VL9_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL8_lane_map: 0x%x\n", reg_data->pmdr_reg.VL8_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL23_lane_map: 0x%x\n", reg_data->pmdr_reg.VL23_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL22_lane_map: 0x%x\n", reg_data->pmdr_reg.VL22_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL21_lane_map: 0x%x\n", reg_data->pmdr_reg.VL21_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL20_lane_map: 0x%x\n", reg_data->pmdr_reg.VL20_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL19_lane_map: 0x%x\n", reg_data->pmdr_reg.VL19_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL18_lane_map: 0x%x\n", reg_data->pmdr_reg.VL18_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL17_lane_map: 0x%x\n", reg_data->pmdr_reg.VL17_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL16_lane_map: 0x%x\n", reg_data->pmdr_reg.VL16_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL31_lane_map: 0x%x\n", reg_data->pmdr_reg.VL31_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL30_lane_map: 0x%x\n", reg_data->pmdr_reg.VL30_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL29_lane_map: 0x%x\n", reg_data->pmdr_reg.VL29_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL28_lane_map: 0x%x\n", reg_data->pmdr_reg.VL28_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL27_lane_map: 0x%x\n", reg_data->pmdr_reg.VL27_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL26_lane_map: 0x%x\n", reg_data->pmdr_reg.VL26_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL25_lane_map: 0x%x\n", reg_data->pmdr_reg.VL25_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "VL24_lane_map: 0x%x\n", reg_data->pmdr_reg.VL24_lane_map);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int __mvcap_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_mvcap_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "hi: 0x%x\n", reg_data->mvcap_reg.sensor_map.hi);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lo: 0x%x\n", reg_data->mvcap_reg.sensor_map.lo);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "slot_index: 0x%x\n", reg_data->mvcap_reg.slot_index);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int __pddr_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_pddr_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint32_t index = 0;
    uint16_t local_port = 0;

    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->pddr_reg.local_port, reg_data->pddr_reg.lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->pddr_reg.pnat);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "port_type: 0x%x\n", reg_data->pddr_reg.port_type);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "clr: 0x%x\n", reg_data->pddr_reg.clr);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "module_info_ext: 0x%x\n", reg_data->pddr_reg.module_info_ext);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "dev: 0x%x\n", reg_data->pddr_reg.dev);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "page_select: 0x%x\n", reg_data->pddr_reg.page_select);
    buffer += snp_res;
    buffer_size += snp_res;
    switch (reg_data->pddr_reg.page_select) {
    case SXD_PDDR_PAGE_SELECT_OPERATIONAL_INFO_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "proto_active: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.proto_active);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "neg_mode_active: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.neg_mode_active);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pd_fsm_state: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.pd_fsm_state);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_mngr_fsm_state: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.phy_mngr_fsm_state);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_an_fsm_state: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.eth_an_fsm_state);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_phy_fsm_state: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.ib_phy_fsm_state);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_hst_fsm_state: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.phy_hst_fsm_state);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_manager_link_width_enabled: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.phy_manager_link_enabled.pddr_phy_manager_link_enabed_ib.phy_manager_link_width_enabled);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_manager_link_proto_enabled: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.phy_manager_link_enabled.pddr_phy_manager_link_enabed_ib.phy_manager_link_proto_enabled);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_manager_link_eth_enabled: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.phy_manager_link_enabled.pddr_phy_manager_link_enabed_eth.phy_manager_link_eth_enabled);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "core_to_phy_link_width_enabled: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.core_to_phy_link_enabled.pddr_c2p_link_enabed_ib.core_to_phy_link_width_enabled);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "core_to_phy_link_proto_enabled: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.core_to_phy_link_enabled.pddr_c2p_link_enabed_ib.core_to_phy_link_proto_enabled);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "core_to_phy_link_eth_enabled: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.core_to_phy_link_enabled.pddr_c2p_link_enabed_eth.core_to_phy_link_eth_enabled);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_link_width_cap: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.cable_proto_cap.pddr_cable_cap_ib.cable_link_width_cap);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_link_speed_cap: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.cable_proto_cap.pddr_cable_cap_ib.cable_link_speed_cap);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_ext_eth_proto_cap: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.cable_proto_cap.pddr_cable_cap_eth.cable_ext_eth_proto_cap);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_width_active: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.link_active.pddr_link_active_ib.link_width_active);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_speed_active: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.link_active.pddr_link_active_ib.link_speed_active);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_eth_active: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.link_active.pddr_link_active_eth.link_eth_active);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "retran_mode_active: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.retran_mode_active);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "retran_mode_request: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.retran_mode_request);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "loopback_mode: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.loopback_mode);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fec_mode_active: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.fec_mode_active);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fec_mode_request: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.fec_mode_request);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "profile_fec_in_use: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.profile_fec_in_use);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_25g_50g_fec_support: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.eth_25g_50g_fec_support);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_100g_fec_support: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.eth_100g_fec_support);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pd_link_enabled: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.pd_link_enabled);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_hst_link_enabled: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.phy_hst_link_enabled);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_an_link_enabled: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.eth_an_link_enabled);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "core_to_phy_state: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.core_to_phy_state);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "psi_fsm_state: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.psi_fsm_state);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_proto_cap_ext: 0x%x\n", reg_data->pddr_reg.page_data.pddr_operation_info_page.cable_proto_cap_ext);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_TROUBLESHOOTING_INFO_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "group_opcode: 0x%x\n", reg_data->pddr_reg.page_data.pddr_troubleshooting_page.group_opcode);
        buffer += snp_res;
        buffer_size += snp_res;
        switch (reg_data->pddr_reg.page_data.pddr_troubleshooting_page.group_opcode) {
        case SXD_PDDR_GROUP_OPCODE_MONITOR_OPCODES_E:
            snp_res = snprintf(buffer, buffer_length - buffer_size, "monitor_opcode: 0x%x\n", reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_opcode.pddr_monitor_opcode.monitor_opcode);
            buffer += snp_res;
            buffer_size += snp_res;
            break;

        case SXD_PDDR_GROUP_OPCODE_ADVANCED_DEBUG_OPCODES_E:
            snp_res = snprintf(buffer, buffer_length - buffer_size, "advanced_opcode: 0x%x\n", reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_opcode.pddr_advanced_opcode.advanced_opcode);
            buffer += snp_res;
            buffer_size += snp_res;
            break;

        default:
            /* Other types not supported yet */
            break;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "user_feedback_data: 0x%x\n", reg_data->pddr_reg.page_data.pddr_troubleshooting_page.user_feedback_data);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "user_feedback_index: 0x%x\n", reg_data->pddr_reg.page_data.pddr_troubleshooting_page.user_feedback_index);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "status_message: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[0], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[1], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[2], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[3], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[4], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[5], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[6], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[7], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[8], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[9], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[10], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[11], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[12], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[13], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[14], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[15], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[16], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[17], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[18], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[19], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[20], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[21], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[22], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[23], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[24], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[25], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[26], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[27], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[28], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[29], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[30], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[31], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[32], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[33], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[34], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[35], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[36], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[37], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[38], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[39], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[40], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[41], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[42], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[43], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[44], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[45], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[46], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[47], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[48], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[49], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[50], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[51], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[52], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[53], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[54], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[55], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[56], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[57], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[58], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[59], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[60], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[61], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[62], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[63], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[64], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[65], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[66], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[67], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[68], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[69], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[70], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[71], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[72], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[73], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[74], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[75], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[76], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[77], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[78], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[79], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[80], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[81], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[82], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[83], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[84], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[85], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[86], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[87], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[88], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[89], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[90], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[91], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[92], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[93], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[94], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[95], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[96], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[97], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[98], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[99], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[100], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[101], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[102], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[103], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[104], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[105], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[106], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[107], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[108], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[109], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[110], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[111], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[112], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[113], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[114], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[115], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[116], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[117], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[118], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[119], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[120], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[121], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[122], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[123], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[124], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[125], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[126], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[127], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[128], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[129], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[130], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[131], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[132], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[133], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[134], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[135], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[136], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[137], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[138], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[139], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[140], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[141], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[142], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[143], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[144], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[145], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[146], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[147], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[148], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[149], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[150], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[151], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[152], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[153], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[154], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[155], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[156], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[157], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[158], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[159], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[160], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[161], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[162], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[163], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[164], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[165], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[166], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[167], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[168], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[169], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[170], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[171], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[172], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[173], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[174], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[175], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[176], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[177], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[178], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[179], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[180], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[181], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[182], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[183], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[184], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[185], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[186], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[187], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[188], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[189], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[190], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[191], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[192], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[193], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[194], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[195], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[196], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[197], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[198], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[199], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[200], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[201], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[202], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[203], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[204], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[205], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[206], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[207], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[208], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[209], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[210], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[211], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[212], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[213], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[214], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[215], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[216], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[217], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[218], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[219], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[220], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[221], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[222], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[223], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[224], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[225], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[226], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[227], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[228], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[229], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[230], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[231], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[232], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[233], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[234], reg_data->pddr_reg.page_data.pddr_troubleshooting_page.status_message[235]);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_PHY_INFO_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "remote_device_type: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.remote_device_type);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_notifications: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.port_notifications);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_negotiation_attempts: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.num_of_negotiation_attempts);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_revision: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.ib_revision);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lp_ib_revision: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.lp_ib_revision);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "hw_link_phy_state: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.hw_link_phy_state);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_manger_disable_mask: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.phy_manger_disable_mask);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pcs_phy_state: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.pcs_phy_state);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lp_proto_enabled: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.lp_proto_enabled);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lp_fec_mode_support: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.lp_fec_mode_support);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lp_fec_mode_request: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.lp_fec_mode_request);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_last_link_down_reason: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.ib_last_link_down_reason);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_last_link_down_lane: 0x%02x%02x%02x%02x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.eth_last_link_down_lane[0], reg_data->pddr_reg.page_data.pddr_phy_info_page.eth_last_link_down_lane[1], reg_data->pddr_reg.page_data.pddr_phy_info_page.eth_last_link_down_lane[2], reg_data->pddr_reg.page_data.pddr_phy_info_page.eth_last_link_down_lane[3]);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "speed_deg_db: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.speed_deg_db);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "degrade_grade_lane0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.degrade_grade_lane0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "degrade_grade_lane1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.degrade_grade_lane1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "degrade_grade_lane2: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.degrade_grade_lane2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "degrade_grade_lane3: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.degrade_grade_lane3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_presets_tested_lane0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.num_of_presets_tested_lane0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_presets_tested_lane1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.num_of_presets_tested_lane1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_presets_tested_lane2: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.num_of_presets_tested_lane2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_presets_tested_lane3: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.num_of_presets_tested_lane3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_startup_fsm_lane: 0x%02x%02x%02x%02x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.kr_startup_fsm_lane[0], reg_data->pddr_reg.page_data.pddr_phy_info_page.kr_startup_fsm_lane[1], reg_data->pddr_reg.page_data.pddr_phy_info_page.kr_startup_fsm_lane[2], reg_data->pddr_reg.page_data.pddr_phy_info_page.kr_startup_fsm_lane[3]);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_an_debug_indication: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.eth_an_debug_indication);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cdr_not_locked_cnt: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.cdr_not_locked_cnt);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fall_from_cfg_idle_cnt: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.fall_from_cfg_idle_cnt);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fall_from_cfg_idle_cdr_cnt: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.fall_from_cfg_idle_cdr_cnt);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_an_watchdog_cnt: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.eth_an_watchdog_cnt);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rounds_waited_for_peer_to_end_test: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.rounds_waited_for_peer_to_end_test);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_phy_fsm_state_trace: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.ib_phy_fsm_state_trace);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_startup_debug_indications: 0x");
        buffer += snp_res;
        buffer_size += snp_res;
        for (index = 0; index < SXD_PDDR_KR_STARTUP_DEBUG_INDICATIONS_NUM; index++) {
            snp_res = snprintf(buffer, buffer_length - buffer_size, "%x", reg_data->pddr_reg.page_data.pddr_phy_info_page.kr_startup_debug_indications[index]);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_tuning_stages_lane0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.tx_tuning_stages_lane0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_tuning_stages_lane1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.tx_tuning_stages_lane1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_tuning_stages_lane2: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.tx_tuning_stages_lane2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_tuning_stages_lane3: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.tx_tuning_stages_lane3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "irisc_status: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.irisc_status);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "stamping_reason: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.stamping_reason);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_frame_lock_tuning_failure_events_count: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.kr_frame_lock_tuning_failure_events_count);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_full_tuning_failure_count: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.kr_full_tuning_failure_count);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_debug_indication: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.ib_debug_indication);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pm_debug_indication: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.pm_debug_indication);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pd_debug_indication: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.pd_debug_indication);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "psi_collision1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.psi_collision1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "psi_collision2: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.psi_collision2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "hst_mismatch_reason: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.hst_mismatch_reason);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fp_signal_detect_count: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.fp_signal_detect_count);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pd_count: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_info_page.pd_count);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_MODULE_INFO_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_technology: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_technology);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_breakout: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_breakout);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ext_ethernet_compliance_code: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.ext_ethernet_compliance_code);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ethernet_compliance_code: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.ethernet_compliance_code);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_type: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_type);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_vendor: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_vendor);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_length: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_length);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_identifier: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_identifier);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_power_class: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_power_class);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "max_power: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.max_power);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_rx_amp: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_rx_amp);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_rx_emphasis: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_rx_emphasis);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_tx_equalization: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_tx_equalization);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_attenuation_25g: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_attenuation_25g);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_attenuation_12g: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_attenuation_12g);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_attenuation_7g: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_attenuation_7g);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_attenuation_5g: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_attenuation_5g);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cable_rx_post_emphasis: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.cable_rx_post_emphasis);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_cdr_cap: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_cdr_cap);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_cdr_cap: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_cdr_cap);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_cdr_state: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_cdr_state);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_cdr_state: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_cdr_state);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vendor_name: 0x");
        buffer += snp_res;
        buffer_size += snp_res;
        for (index = 0; index < SXD_PDDR_VENDOR_NAME_NUM; index++) {
            snp_res = snprintf(buffer, buffer_length - buffer_size, "%x", reg_data->pddr_reg.page_data.pddr_module_info.vendor_name[index]);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vendor_pn: 0x");
        buffer += snp_res;
        buffer_size += snp_res;
        for (index = 0; index < SXD_PDDR_VENDOR_PN_NUM; index++) {
            snp_res = snprintf(buffer, buffer_length - buffer_size, "%x", reg_data->pddr_reg.page_data.pddr_module_info.vendor_pn[index]);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vendor_rev: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.vendor_rev);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_version: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.fw_version);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vendor_sn: 0x");
        buffer += snp_res;
        buffer_size += snp_res;
        for (index = 0; index < SXD_PDDR_VENDOR_SN_NUM; index++) {
            snp_res = snprintf(buffer, buffer_length - buffer_size, "%x", reg_data->pddr_reg.page_data.pddr_module_info.vendor_sn[index]);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "temperature: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.temperature);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "voltage: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.voltage);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_power_lane0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_power_lane1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane2: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_power_lane2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane3: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_power_lane3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane4: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_power_lane4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane5: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_power_lane5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane6: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_power_lane6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lane7: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_power_lane7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_power_lane0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_power_lane1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane2: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_power_lane2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane3: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_power_lane3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane4: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_power_lane4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane5: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_power_lane5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane6: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_power_lane6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lane7: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_power_lane7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_bias_lane0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_bias_lane1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane2: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_bias_lane2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane3: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_bias_lane3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane4: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_bias_lane4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane5: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_bias_lane5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane6: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_bias_lane6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lane7: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_bias_lane7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "temperature_high_th: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.temperature_high_th);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "temperature_low_th: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.temperature_low_th);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "voltage_high_th: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.voltage_high_th);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "voltage_low_th: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.voltage_low_th);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_high_th: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_power_high_th);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_low_th: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_power_low_th);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_high_th: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_power_high_th);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_low_th: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_power_low_th);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_high_th: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_bias_high_th);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_low_th: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_bias_low_th);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "module_st: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.module_st);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_type: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_power_type);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "did_cap: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.did_cap);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "smf_length: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.smf_length);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "wavelength: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.wavelength);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "active_set_host_compliance_code: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.active_set_host_compliance_code);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "active_set_media_compliance_code: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.active_set_media_compliance_code);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_compliance_code: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.ib_compliance_code);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "nbr250: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.nbr250);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "nbr100: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.nbr100);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "monitor_cap_mask: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.monitor_cap_mask);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_width: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.ib_width);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.dp_st_lane0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.dp_st_lane1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane2: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.dp_st_lane2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane3: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.dp_st_lane3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane4: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.dp_st_lane4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane5: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.dp_st_lane5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane6: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.dp_st_lane6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_st_lane7: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.dp_st_lane7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "length_om2: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.length_om2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "length_om3: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.length_om3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "length_om4: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.length_om4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "length_om5: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.length_om5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "length_om1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.length_om1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "wavelength_tolerance: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.wavelength_tolerance);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "memory_map_rev: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.memory_map_rev);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "memory_map_compliance: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.memory_map_compliance);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "hi: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.date_code.hi);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lo: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.date_code.lo);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "connector_type: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.connector_type);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vendor_oui: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.vendor_oui);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_input_freq_sync: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.tx_input_freq_sync);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_input_valid: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_input_valid);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_output_valid: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.rx_output_valid);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "max_fiber_length: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.max_fiber_length);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "error_code: 0x%x\n", reg_data->pddr_reg.page_data.pddr_module_info.error_code);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_PORT_EVENTS_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "invalid_fsm_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.invalid_fsm_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "invalid_fsm_ps: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.invalid_fsm_ps);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_false_ready_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.kr_false_ready_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "kr_false_ready: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.kr_false_ready);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_req_nack_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.mod_req_nack_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_req_nack: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.mod_req_nack);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_req_busy_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.mod_req_busy_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_req_busy: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.mod_req_busy);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_config_to_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.mod_config_to_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_config_to: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.mod_config_to);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_adapt_faild_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.mod_adapt_faild_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_adapt_faild: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.mod_adapt_faild);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pm_fifo_full_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.pm_fifo_full_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pm_fifo_full: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.pm_fifo_full);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "protocol_check_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.protocol_check_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "protocol_check: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.protocol_check);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "input_event_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.input_event_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "input_event: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.input_event);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lane_mapping_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.lane_mapping_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "lane_mapping: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.lane_mapping);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "qsfp_zero_atten_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.qsfp_zero_atten_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "qsfp_zero_atten: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.qsfp_zero_atten);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mono_reach_low_limit_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.mono_reach_low_limit_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mono_reach_low_limit: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.mono_reach_low_limit);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mono_reach_high_limit_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.mono_reach_high_limit_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mono_reach_high_limit: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.mono_reach_high_limit);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mono_flow_height_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.mono_flow_height_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mono_flow_height: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.mono_flow_height);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "single_gains_bad_val_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.single_gains_bad_val_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "single_gains_bad_val: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.single_gains_bad_val);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "init_all_gains_bad_val_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.init_all_gains_bad_val_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "init_all_gains_bad_val: 0x%x\n", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.init_all_gains_bad_val);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "clr_mask: 0x");
        buffer += snp_res;
        buffer_size += snp_res;
        for (index = 0; index < SXD_PDDR_CLR_MASK_NUM; index++) {
            snp_res = snprintf(buffer, buffer_length - buffer_size, "%x", reg_data->pddr_reg.page_data.pddr_port_events_page_layout.clr_mask[index]);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_DEVICE_EVENTS_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "invalid_port_access_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.invalid_port_access_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "invalid_port_access: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.invalid_port_access);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_state_sv_1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.pll_state_sv_1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_state_mask_center1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.pll_state_mask_center1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_state_sv_0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.pll_state_sv_0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_state_mask_center0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.pll_state_mask_center0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "main_irisc_timeout: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.main_irisc_timeout);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tile_irisc_timeout: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.tile_irisc_timeout);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout2: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout3: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout4: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cr_space_timeout_mcm_main: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.cr_space_timeout_mcm_main);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cr_space_timeout_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.cr_space_timeout_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cr_space_timeout: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.cr_space_timeout);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "analog_phy_to_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.analog_phy_to_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "analog_phy_to: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.analog_phy_to);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "logical_phy_to_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.logical_phy_to_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "logical_phy_to: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.logical_phy_to);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "varactors_calib_fail_center1_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.varactors_calib_fail_center1_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "varactors_calib_fail_center1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.varactors_calib_fail_center1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "varactors_calib_fail_center0_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.varactors_calib_fail_center0_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "varactors_calib_fail_center0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.varactors_calib_fail_center0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "irisc_stuck_mask_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.irisc_stuck_mask_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "irisc_stuck_mask: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.irisc_stuck_mask);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_lock_sv_1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.pll_lock_sv_1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_unlocl_mask_center1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.pll_unlocl_mask_center1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_lock_sv_0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.pll_lock_sv_0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pll_unlocl_mask_center0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.pll_unlocl_mask_center0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uc_stack_overflow: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.uc_stack_overflow);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uc_crspace_timeout: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.uc_crspace_timeout);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pwr_governor_err_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.pwr_governor_err_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pwr_governor_err: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.pwr_governor_err);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "iopl_err_center1_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.iopl_err_center1_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "iopl_err_center1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.iopl_err_center1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "iopl_err_center0_sv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.iopl_err_center0_sv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "iopl_err_center0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.iopl_err_center0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "clr_mask: 0x");
        buffer += snp_res;
        buffer_size += snp_res;
        for (index = 0; index < SXD_PDDR_CLR_MASK_NUM; index++) {
            snp_res = snprintf(buffer, buffer_length - buffer_size, "%x", reg_data->pddr_reg.page_data.pddr_device_events_page.clr_mask[index]);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "main_irisc_address: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.main_irisc_address);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "main_irisc_ip: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.main_irisc_ip);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tile_irisc_address: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.tile_irisc_address);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tile_irisc_ip: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.tile_irisc_ip);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout0_address: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout0_address);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout1_address: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout1_address);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout2_address: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout2_address);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout3_address: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout3_address);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout4_address: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout4_address);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout0_cluster: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout0_cluster);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout1_cluster: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout1_cluster);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout2_cluster: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout2_cluster);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout3_cluster: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout3_cluster);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plu_timeout4_cluster: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.plu_timeout4_cluster);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "irisc_tile_idx: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.irisc_tile_idx);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uc_crspace_timeout_lane: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.uc_crspace_timeout_lane);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uc_crspace_timeout_cl: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.uc_crspace_timeout_cl);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uc_stack_overflow_lane: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.uc_stack_overflow_lane);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uc_stack_overflow_cl: 0x%x\n", reg_data->pddr_reg.page_data.pddr_device_events_page.uc_stack_overflow_cl);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_DOWN_INFO_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "down_blame: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.down_blame);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_reason_opcode: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.local_reason_opcode);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "remote_reason_opcode: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.remote_reason_opcode);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "e2e_reason_opcode: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.e2e_reason_opcode);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "last_ber_mantissa: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.last_ber_mantissa);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "last_ber_exp: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.last_ber_exp);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ber_mantissa: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.ber_mantissa);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ber_exp: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.ber_exp);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "min_ber_mantissa: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.min_ber_mantissa);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "min_ber_exp: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.min_ber_exp);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "max_ber_mantissa: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.max_ber_mantissa);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "max_ber_exp: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.max_ber_exp);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "num_of_ber_alarams: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.num_of_ber_alarams);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_to_link_down_to_disable: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.time_to_link_down_to_disable);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_to_link_down_to_rx_loss: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_page.time_to_link_down_to_rx_loss);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_DOWN_EVENTS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_port_events: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_events_page.ib_port_events);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "etherent_port_events: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_events_page.etherent_port_events);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "general_port_events: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_events_page.general_port_events);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_UP_INFO_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "up_reason_pwr: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_up_info_page.up_reason_pwr);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "up_reason_drv: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_up_info_page.up_reason_drv);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "up_reason_mng: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_up_info_page.up_reason_mng);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_to_link_up: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_up_info_page.time_to_link_up);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fast_link_up_status: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_up_info_page.fast_link_up_status);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_to_link_up_phy_up_to_active: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_up_info_page.time_to_link_up_phy_up_to_active);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_to_link_up_sd_to_phy_up: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_up_info_page.time_to_link_up_sd_to_phy_up);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_to_link_up_disable_to_sd: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_up_info_page.time_to_link_up_disable_to_sd);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_to_link_up_disable_to_pd: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_up_info_page.time_to_link_up_disable_to_pd);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_MODULE_LATCHED_FLAG_INFO_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "temp_flags: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.temp_flags);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vcc_flags: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.vcc_flags);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "mod_fw_fault: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.mod_fw_fault);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_fw_fault: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.dp_fw_fault);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_fault: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.tx_fault);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_los: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.tx_los);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_cdr_lol: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.tx_cdr_lol);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_ad_eq_fault: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.tx_ad_eq_fault);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_hi_al: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.tx_power_hi_al);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lo_al: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.tx_power_lo_al);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_hi_war: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.tx_power_hi_war);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_power_lo_war: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.tx_power_lo_war);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_hi_al: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.tx_bias_hi_al);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lo_al: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.tx_bias_lo_al);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_hi_war: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.tx_bias_hi_war);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bias_lo_war: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.tx_bias_lo_war);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_los: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.rx_los);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_cdr_lol: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.rx_cdr_lol);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_hi_al: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.rx_power_hi_al);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lo_al: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.rx_power_lo_al);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_hi_war: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.rx_power_hi_war);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_power_lo_war: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.rx_power_lo_war);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_input_valid_change: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.rx_input_valid_change);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_output_valid_change: 0x%x\n", reg_data->pddr_reg.page_data.module_latched_flag_info.rx_output_valid_change);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_DOWN_INFO_EXT_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cause_as_detected_not_on_slot: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.cause_as_detected_not_on_slot);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cause_high_ser: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.cause_high_ser);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cause_rs_rx_lane0_symbol_error: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.cause_rs_rx_lane0_symbol_error);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cause_tx_lane_fifo_underrun_l0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.cause_tx_lane_fifo_underrun_l0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cause_deskew_fifo_overrun: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.cause_deskew_fifo_overrun);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "cause_fec_rx_sync_m_reached_max0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.cause_fec_rx_sync_m_reached_max0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_error_counter_lo: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.symbol_error_counter_lo);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_error_counter_hi: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.symbol_error_counter_hi);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uncorrectable_block_counter_lo: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.uncorrectable_block_counter_lo);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "uncorrectable_block_counter_hi: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.uncorrectable_block_counter_hi);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_fail_due_align_loss: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.link_fail_due_align_loss);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "block_lock_mask_at_fail_port1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.block_lock_mask_at_fail_port1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "block_lock_mask_at_fail_port0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.block_lock_mask_at_fail_port0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_down_counter: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.link_down_counter);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "effective_ber_coef: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.effective_ber_coef);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "effective_ber_magnitude: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.effective_ber_magnitude);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.raw_ber_coef);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude: 0x%x\n", reg_data->pddr_reg.page_data.pddr_link_down_info_ext_16nm_lr.raw_ber_magnitude);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_LINK_PARTNER_INFO_PAGE_E:
        break;

    case SXD_PDDR_PAGE_SELECT_MNG_DEBUG_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_module_state: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.fw_module_state);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane7: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.fw_dp_state_lane7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane6: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.fw_dp_state_lane6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane5: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.fw_dp_state_lane5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane4: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.fw_dp_state_lane4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane3: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.fw_dp_state_lane3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane2: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.fw_dp_state_lane2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.fw_dp_state_lane1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fw_dp_state_lane0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.fw_dp_state_lane0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane7: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dp_req_status_lane7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane6: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dp_req_status_lane6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane5: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dp_req_status_lane5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane4: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dp_req_status_lane4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane3: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dp_req_status_lane3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane2: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dp_req_status_lane2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dp_req_status_lane1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dp_req_status_lane0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dp_req_status_lane0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane7: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dpsm_apply_state_lane7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane6: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dpsm_apply_state_lane6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane5: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dpsm_apply_state_lane5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane4: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dpsm_apply_state_lane4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane3: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dpsm_apply_state_lane3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane2: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dpsm_apply_state_lane2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane1: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dpsm_apply_state_lane1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dpsm_apply_state_lane0: 0x%x\n", reg_data->pddr_reg.page_data.pddr_mng_debug_page.dpsm_apply_state_lane0);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PDDR_PAGE_SELECT_PHY_DEBUG_PAGE_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pport: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.pport);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "trigger_active: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.trigger_active);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "trigger_cond_state_event_val: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.trigger_cond_state_event_val);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "trigger_cond_state_or_event: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.trigger_cond_state_or_event);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "trigger_cond_fsm: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.trigger_cond_fsm);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pre_trigger_buff_mode: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.pre_trigger_buff_mode);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tracer_mode: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.tracer_mode);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "reset_tracer: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.reset_tracer);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tracer_enable: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.tracer_enable);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fsm_mask: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.fsm_mask);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "trigger_ptr: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.trigger_ptr);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "buffer_size: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.buffer_size);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ptr_log_data: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.ptr_log_data);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ptr_next_write: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.ptr_next_write);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "buffer_base_address: 0x%x\n", reg_data->pddr_reg.page_data.pddr_phy_debug_page.buffer_base_address);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    default:
        /* Other types not supported yet */
        break;
    }

    return buffer_size;
}

int __mgir_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_mgir_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "device_hw_revision: 0x%x\n", reg_data->mgir_reg.hw_info.device_hw_revision);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "device_id: 0x%x\n", reg_data->mgir_reg.hw_info.device_id);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "num_ports: 0x%x\n", reg_data->mgir_reg.hw_info.num_ports);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "technology: 0x%x\n", reg_data->mgir_reg.hw_info.technology);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pvs: 0x%x\n", reg_data->mgir_reg.hw_info.pvs);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "hw_dev_id: 0x%x\n", reg_data->mgir_reg.hw_info.hw_dev_id);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "module_base: 0x%x\n", reg_data->mgir_reg.hw_info.module_base);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "manufacturing_base_mac: 0x%02x%02x%02x%02x%02x%02x\n", reg_data->mgir_reg.hw_info.manufacturing_base_mac[0], reg_data->mgir_reg.hw_info.manufacturing_base_mac[1], reg_data->mgir_reg.hw_info.manufacturing_base_mac[2], reg_data->mgir_reg.hw_info.manufacturing_base_mac[3], reg_data->mgir_reg.hw_info.manufacturing_base_mac[4], reg_data->mgir_reg.hw_info.manufacturing_base_mac[5]);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "associated_module_id_31_0: 0x%x\n", reg_data->mgir_reg.hw_info.associated_module_id_31_0);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "uptime: 0x%x\n", reg_data->mgir_reg.hw_info.uptime);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "dev_sc: 0x%x\n", reg_data->mgir_reg.fw_info.dev_sc);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "latency_tlv: 0x%x\n", reg_data->mgir_reg.fw_info.latency_tlv);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "string_tlv: 0x%x\n", reg_data->mgir_reg.fw_info.string_tlv);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "dev: 0x%x\n", reg_data->mgir_reg.fw_info.dev);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "debug: 0x%x\n", reg_data->mgir_reg.fw_info.debug);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "signed_fw: 0x%x\n", reg_data->mgir_reg.fw_info.signed_fw);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "secured: 0x%x\n", reg_data->mgir_reg.fw_info.secured);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "major: 0x%x\n", reg_data->mgir_reg.fw_info.major);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "minor: 0x%x\n", reg_data->mgir_reg.fw_info.minor);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "sub_minor: 0x%x\n", reg_data->mgir_reg.fw_info.sub_minor);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "build_id: 0x%x\n", reg_data->mgir_reg.fw_info.build_id);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "month: 0x%x\n", reg_data->mgir_reg.fw_info.month);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "day: 0x%x\n", reg_data->mgir_reg.fw_info.day);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "year: 0x%x\n", reg_data->mgir_reg.fw_info.year);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "hour: 0x%x\n", reg_data->mgir_reg.fw_info.hour);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "psid: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", reg_data->mgir_reg.fw_info.psid[0], reg_data->mgir_reg.fw_info.psid[1], reg_data->mgir_reg.fw_info.psid[2], reg_data->mgir_reg.fw_info.psid[3], reg_data->mgir_reg.fw_info.psid[4], reg_data->mgir_reg.fw_info.psid[5], reg_data->mgir_reg.fw_info.psid[6], reg_data->mgir_reg.fw_info.psid[7], reg_data->mgir_reg.fw_info.psid[8], reg_data->mgir_reg.fw_info.psid[9], reg_data->mgir_reg.fw_info.psid[10], reg_data->mgir_reg.fw_info.psid[11], reg_data->mgir_reg.fw_info.psid[12], reg_data->mgir_reg.fw_info.psid[13], reg_data->mgir_reg.fw_info.psid[14], reg_data->mgir_reg.fw_info.psid[15]);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ini_file_version: 0x%x\n", reg_data->mgir_reg.fw_info.ini_file_version);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "extended_major: 0x%x\n", reg_data->mgir_reg.fw_info.extended_major);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "extended_minor: 0x%x\n", reg_data->mgir_reg.fw_info.extended_minor);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "extended_sub_minor: 0x%x\n", reg_data->mgir_reg.fw_info.extended_sub_minor);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "disabled_tiles_bitmap: 0x%x\n", reg_data->mgir_reg.fw_info.disabled_tiles_bitmap);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "isfu_major: 0x%x\n", reg_data->mgir_reg.fw_info.isfu_major);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "encryption: 0x%x\n", reg_data->mgir_reg.fw_info.encryption);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "sec_boot: 0x%x\n", reg_data->mgir_reg.fw_info.sec_boot);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "life_cycle: 0x%x\n", reg_data->mgir_reg.fw_info.life_cycle);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "major: 0x%x\n", reg_data->mgir_reg.sw_info.major);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "minor: 0x%x\n", reg_data->mgir_reg.sw_info.minor);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "sub_minor: 0x%x\n", reg_data->mgir_reg.sw_info.sub_minor);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom0_arch: 0x%x\n", reg_data->mgir_reg.sw_info.rom0_arch);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom0_type: 0x%x\n", reg_data->mgir_reg.sw_info.rom0_type);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom1_arch: 0x%x\n", reg_data->mgir_reg.sw_info.rom1_arch);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom1_type: 0x%x\n", reg_data->mgir_reg.sw_info.rom1_type);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom2_arch: 0x%x\n", reg_data->mgir_reg.sw_info.rom2_arch);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom2_type: 0x%x\n", reg_data->mgir_reg.sw_info.rom2_type);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom3_arch: 0x%x\n", reg_data->mgir_reg.sw_info.rom3_arch);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "rom3_type: 0x%x\n", reg_data->mgir_reg.sw_info.rom3_type);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "major: 0x%x\n", reg_data->mgir_reg.sw_info.rom0_version.major);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "minor: 0x%x\n", reg_data->mgir_reg.sw_info.rom0_version.minor);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "build: 0x%x\n", reg_data->mgir_reg.sw_info.rom0_version.build);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "major: 0x%x\n", reg_data->mgir_reg.sw_info.rom1_version.major);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "minor: 0x%x\n", reg_data->mgir_reg.sw_info.rom1_version.minor);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "build: 0x%x\n", reg_data->mgir_reg.sw_info.rom1_version.build);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "major: 0x%x\n", reg_data->mgir_reg.sw_info.rom2_version.major);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "minor: 0x%x\n", reg_data->mgir_reg.sw_info.rom2_version.minor);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "build: 0x%x\n", reg_data->mgir_reg.sw_info.rom2_version.build);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "major: 0x%x\n", reg_data->mgir_reg.sw_info.rom3_version.major);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "minor: 0x%x\n", reg_data->mgir_reg.sw_info.rom3_version.minor);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "build: 0x%x\n", reg_data->mgir_reg.sw_info.rom3_version.build);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "dev_branch_tag: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", reg_data->mgir_reg.dev_info.dev_branch_tag[0], reg_data->mgir_reg.dev_info.dev_branch_tag[1], reg_data->mgir_reg.dev_info.dev_branch_tag[2], reg_data->mgir_reg.dev_info.dev_branch_tag[3], reg_data->mgir_reg.dev_info.dev_branch_tag[4], reg_data->mgir_reg.dev_info.dev_branch_tag[5], reg_data->mgir_reg.dev_info.dev_branch_tag[6], reg_data->mgir_reg.dev_info.dev_branch_tag[7], reg_data->mgir_reg.dev_info.dev_branch_tag[8], reg_data->mgir_reg.dev_info.dev_branch_tag[9], reg_data->mgir_reg.dev_info.dev_branch_tag[10], reg_data->mgir_reg.dev_info.dev_branch_tag[11], reg_data->mgir_reg.dev_info.dev_branch_tag[12], reg_data->mgir_reg.dev_info.dev_branch_tag[13], reg_data->mgir_reg.dev_info.dev_branch_tag[14], reg_data->mgir_reg.dev_info.dev_branch_tag[15], reg_data->mgir_reg.dev_info.dev_branch_tag[16], reg_data->mgir_reg.dev_info.dev_branch_tag[17], reg_data->mgir_reg.dev_info.dev_branch_tag[18], reg_data->mgir_reg.dev_info.dev_branch_tag[19], reg_data->mgir_reg.dev_info.dev_branch_tag[20], reg_data->mgir_reg.dev_info.dev_branch_tag[21], reg_data->mgir_reg.dev_info.dev_branch_tag[22], reg_data->mgir_reg.dev_info.dev_branch_tag[23], reg_data->mgir_reg.dev_info.dev_branch_tag[24], reg_data->mgir_reg.dev_info.dev_branch_tag[25], reg_data->mgir_reg.dev_info.dev_branch_tag[26], reg_data->mgir_reg.dev_info.dev_branch_tag[27]);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int __ppcnt_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_ppcnt_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint32_t index = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "swid: 0x%x\n", reg_data->ppcnt_reg.swid);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->ppcnt_reg.local_port, reg_data->ppcnt_reg.lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->ppcnt_reg.pnat);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "port_type: 0x%x\n", reg_data->ppcnt_reg.port_type);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "grp: 0x%x\n", reg_data->ppcnt_reg.grp);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "clr: 0x%x\n", reg_data->ppcnt_reg.clr);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lp_gl: 0x%x\n", reg_data->ppcnt_reg.lp_gl);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "prio_tc: 0x%x\n", reg_data->ppcnt_reg.prio_tc);
    buffer += snp_res;
    buffer_size += snp_res;
    switch (reg_data->ppcnt_reg.grp) {
    case SXD_PPCNT_GRP_IEEE_802_3_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frames_transmitted_ok_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_frames_transmitted_ok_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frames_transmitted_ok_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_frames_transmitted_ok_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frames_received_ok_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_frames_received_ok_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frames_received_ok_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_frames_received_ok_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frame_check_sequence_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_frame_check_sequence_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frame_check_sequence_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_frame_check_sequence_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_alignment_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_alignment_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_alignment_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_alignment_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_octets_transmitted_ok_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_octets_transmitted_ok_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_octets_transmitted_ok_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_octets_transmitted_ok_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_octets_received_ok_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_octets_received_ok_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_octets_received_ok_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_octets_received_ok_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_multicast_frames_xmitted_ok_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_multicast_frames_xmitted_ok_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_multicast_frames_xmitted_ok_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_multicast_frames_xmitted_ok_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_broadcast_frames_xmitted_ok_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_broadcast_frames_xmitted_ok_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_broadcast_frames_xmitted_ok_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_broadcast_frames_xmitted_ok_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_multicast_frames_received_ok_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_multicast_frames_received_ok_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_multicast_frames_received_ok_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_multicast_frames_received_ok_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_broadcast_frames_received_ok_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_broadcast_frames_received_ok_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_broadcast_frames_received_ok_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_broadcast_frames_received_ok_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_in_range_length_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_in_range_length_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_in_range_length_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_in_range_length_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_out_of_range_length_field_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_out_of_range_length_field_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_out_of_range_length_field_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_out_of_range_length_field_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frame_too_long_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_frame_too_long_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_frame_too_long_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_frame_too_long_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_symbol_error_during_carrier_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_symbol_error_during_carrier_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_symbol_error_during_carrier_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_symbol_error_during_carrier_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_mac_control_frames_transmitted_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_mac_control_frames_transmitted_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_mac_control_frames_transmitted_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_mac_control_frames_transmitted_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_mac_control_frames_received_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_mac_control_frames_received_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_mac_control_frames_received_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_mac_control_frames_received_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_unsupported_opcodes_received_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_unsupported_opcodes_received_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_unsupported_opcodes_received_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_unsupported_opcodes_received_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_pause_mac_ctrl_frames_received_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_pause_mac_ctrl_frames_received_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_pause_mac_ctrl_frames_received_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_pause_mac_ctrl_frames_received_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_pause_mac_ctrl_frames_transmitted_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_pause_mac_ctrl_frames_transmitted_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "a_pause_mac_ctrl_frames_transmitted_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_802_3_cntrs_grp_data_layout.a_pause_mac_ctrl_frames_transmitted_low);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_RFC_2863_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_in_octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_in_octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_ucast_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_in_ucast_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_ucast_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_in_ucast_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_discards_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_in_discards_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_discards_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_in_discards_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_in_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_in_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_unknown_protos_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_in_unknown_protos_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_unknown_protos_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_in_unknown_protos_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_out_octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_out_octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_ucast_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_out_ucast_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_ucast_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_out_ucast_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_discards_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_out_discards_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_discards_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_out_discards_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_out_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_out_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_multicast_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_in_multicast_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_multicast_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_in_multicast_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_broadcast_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_in_broadcast_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_broadcast_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_in_broadcast_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_multicast_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_out_multicast_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_multicast_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_out_multicast_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_broadcast_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_out_broadcast_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_broadcast_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2863_cntrs_grp_data_layout.if_out_broadcast_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_RFC_2819_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_drop_events_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_drop_events_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_drop_events_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_drop_events_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_broadcast_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_broadcast_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_broadcast_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_broadcast_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_multicast_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_multicast_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_multicast_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_multicast_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_crc_align_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_crc_align_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_crc_align_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_crc_align_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_undersize_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_undersize_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_undersize_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_undersize_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_oversize_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_oversize_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_oversize_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_oversize_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_fragments_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_fragments_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_fragments_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_fragments_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_jabbers_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_jabbers_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_jabbers_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_jabbers_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_collisions_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_collisions_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_collisions_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_collisions_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts64octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts64octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts64octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts64octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts65to127octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts65to127octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts65to127octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts65to127octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts128to255octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts128to255octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts128to255octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts128to255octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts256to511octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts256to511octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts256to511octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts256to511octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts512to1023octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts512to1023octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts512to1023octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts512to1023octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts1024to1518octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts1024to1518octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts1024to1518octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts1024to1518octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts1519to2047octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts1519to2047octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts1519to2047octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts1519to2047octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts2048to4095octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts2048to4095octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts2048to4095octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts2048to4095octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts4096to8191octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts4096to8191octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts4096to8191octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts4096to8191octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts8192to10239octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts8192to10239octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_pkts8192to10239octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_2819_cntrs_grp_data_layout.ether_stats_pkts8192to10239octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_RFC_3635_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_alignment_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_alignment_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_alignment_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_alignment_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_fcs_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_fcs_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_fcs_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_fcs_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_single_collision_frames_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_single_collision_frames_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_single_collision_frames_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_single_collision_frames_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_multiple_collision_frames_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_multiple_collision_frames_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_multiple_collision_frames_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_multiple_collision_frames_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_sqe_test_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_sqe_test_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_sqe_test_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_sqe_test_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_deferred_transmissions_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_deferred_transmissions_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_deferred_transmissions_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_deferred_transmissions_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_late_collisions_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_late_collisions_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_late_collisions_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_late_collisions_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_excessive_collisions_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_excessive_collisions_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_excessive_collisions_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_excessive_collisions_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_internal_mac_transmit_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_transmit_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_internal_mac_transmit_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_transmit_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_carrier_sense_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_carrier_sense_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_carrier_sense_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_carrier_sense_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_frame_too_longs_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_frame_too_longs_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_frame_too_longs_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_frame_too_longs_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_internal_mac_receive_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_receive_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_internal_mac_receive_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_internal_mac_receive_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_symbol_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_symbol_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_symbol_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3stats_symbol_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3control_in_unknown_opcodes_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3control_in_unknown_opcodes_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3control_in_unknown_opcodes_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3control_in_unknown_opcodes_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3in_pause_frames_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3in_pause_frames_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3in_pause_frames_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3in_pause_frames_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3out_pause_frames_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3out_pause_frames_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3out_pause_frames_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_3635_cntrs_grp_data_layout.dot3out_pause_frames_low);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_ETHERNET_EXTENDED_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_transmit_wait_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.port_transmit_wait_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_transmit_wait_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.port_transmit_wait_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ecn_marked_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.ecn_marked_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ecn_marked_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.ecn_marked_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "no_buffer_discard_mc_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.no_buffer_discard_mc_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "no_buffer_discard_mc_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.no_buffer_discard_mc_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_ebp_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.rx_ebp_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_ebp_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.rx_ebp_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_ebp_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_ebp_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_ebp_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_ebp_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_buffer_almost_full_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.rx_buffer_almost_full_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_buffer_almost_full_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.rx_buffer_almost_full_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_buffer_full_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.rx_buffer_full_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_buffer_full_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.rx_buffer_full_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_icrc_encapsulated_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.rx_icrc_encapsulated_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_icrc_encapsulated_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.rx_icrc_encapsulated_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts64octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts64octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts64octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts64octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts65to127octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts65to127octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts65to127octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts65to127octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts128to255octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts128to255octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts128to255octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts128to255octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts256to511octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts256to511octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts256to511octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts256to511octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts512to1023octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts512to1023octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts512to1023octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts512to1023octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts1024to1518octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts1024to1518octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts1024to1518octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts1024to1518octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts1519to2047octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts1519to2047octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts1519to2047octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts1519to2047octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts2048to4095octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts2048to4095octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts2048to4095octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts2048to4095octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts4096to8191octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts4096to8191octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts4096to8191octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts4096to8191octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts8192to10239octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts8192to10239octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_stats_pkts8192to10239octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.tx_stats_pkts8192to10239octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ece_marked_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.ece_marked_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ece_marked_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_extended_cntrs_grp_data_layout.ece_marked_low);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_ETHERNET_DISCARD_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_general_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.ingress_general_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_general_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.ingress_general_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_policy_engine_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.ingress_policy_engine_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_policy_engine_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.ingress_policy_engine_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_vlan_membership_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.ingress_vlan_membership_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_vlan_membership_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.ingress_vlan_membership_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_tag_frame_type_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.ingress_tag_frame_type_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_tag_frame_type_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.ingress_tag_frame_type_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_vlan_membership_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.egress_vlan_membership_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_vlan_membership_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.egress_vlan_membership_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "loopback_filter_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.loopback_filter_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "loopback_filter_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.loopback_filter_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_general_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.egress_general_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_general_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.egress_general_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_hoq_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.egress_hoq_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_hoq_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.egress_hoq_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_isolation_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.port_isolation_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_isolation_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.port_isolation_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_policy_engine_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.egress_policy_engine_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_policy_engine_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.egress_policy_engine_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_tx_link_down_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.ingress_tx_link_down_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_tx_link_down_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.ingress_tx_link_down_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_stp_filter_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.egress_stp_filter_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_stp_filter_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.egress_stp_filter_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_hoq_stall_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.egress_hoq_stall_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_hoq_stall_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.egress_hoq_stall_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_sll_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.egress_sll_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "egress_sll_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.egress_sll_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_discard_all_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.ingress_discard_all_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ingress_discard_all_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_discard_cntrs_grp.ingress_discard_all_low);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_LINK_LEVEL_RETRANSMISSION_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_rx_cells_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.link_level_retrans_cntr_grp_data.llr_rx_cells_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_rx_cells_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.link_level_retrans_cntr_grp_data.llr_rx_cells_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_rx_error_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.link_level_retrans_cntr_grp_data.llr_rx_error_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_rx_error_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.link_level_retrans_cntr_grp_data.llr_rx_error_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_rx_crc_error_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.link_level_retrans_cntr_grp_data.llr_rx_crc_error_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_rx_crc_error_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.link_level_retrans_cntr_grp_data.llr_rx_crc_error_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_tx_cells_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.link_level_retrans_cntr_grp_data.llr_tx_cells_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_tx_cells_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.link_level_retrans_cntr_grp_data.llr_tx_cells_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_tx_ret_cells_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.link_level_retrans_cntr_grp_data.llr_tx_ret_cells_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_tx_ret_cells_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.link_level_retrans_cntr_grp_data.llr_tx_ret_cells_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_tx_ret_events_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.link_level_retrans_cntr_grp_data.llr_tx_ret_events_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "llr_tx_ret_events_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.link_level_retrans_cntr_grp_data.llr_tx_ret_events_low);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PER_PRIORITY_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_uc_frames_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_uc_frames_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_uc_frames_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_uc_frames_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_mc_frames_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_mc_frames_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_mc_frames_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_mc_frames_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_bc_frames_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_bc_frames_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_bc_frames_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_bc_frames_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_frames_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_frames_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_frames_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_frames_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.tx_octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.tx_octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_uc_frames_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.tx_uc_frames_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_uc_frames_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.tx_uc_frames_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_mc_frames_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.tx_mc_frames_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_mc_frames_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.tx_mc_frames_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bc_frames_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.tx_bc_frames_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_bc_frames_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.tx_bc_frames_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_frames_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.tx_frames_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_frames_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.tx_frames_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_pause_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_pause_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_pause_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_pause_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_pause_duration_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_pause_duration_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_pause_duration_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_pause_duration_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_pause_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.tx_pause_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_pause_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.tx_pause_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_pause_duration_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.tx_pause_duration_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "tx_pause_duration_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.tx_pause_duration_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_pause_transition_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_pause_transition_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_pause_transition_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_pause_transition_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_discards_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_discards_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_discards_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.rx_discards_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "device_stall_minor_watermark_cnt_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.device_stall_minor_watermark_cnt_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "device_stall_minor_watermark_cnt_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.device_stall_minor_watermark_cnt_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "device_stall_critical_watermark_cnt_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.device_stall_critical_watermark_cnt_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "device_stall_critical_watermark_cnt_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_prio_grp_data_layout.device_stall_critical_watermark_cnt_low);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PER_TRAFFIC_CLASS_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "transmit_queue_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_traffic_class_layout.transmit_queue_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "transmit_queue_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_traffic_class_layout.transmit_queue_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "no_buffer_discard_uc_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_traffic_class_layout.no_buffer_discard_uc_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "no_buffer_discard_uc_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_traffic_class_layout.no_buffer_discard_uc_low);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PHYSICAL_LAYER_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.time_since_last_clear_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.time_since_last_clear_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.symbol_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.symbol_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "sync_headers_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.sync_headers_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "sync_headers_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.sync_headers_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane0_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.edpl_bip_errors_lane0_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane0_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.edpl_bip_errors_lane0_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane1_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.edpl_bip_errors_lane1_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane1_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.edpl_bip_errors_lane1_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane2_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.edpl_bip_errors_lane2_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane2_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.edpl_bip_errors_lane2_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane3_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.edpl_bip_errors_lane3_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "edpl_bip_errors_lane3_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.edpl_bip_errors_lane3_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane0_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane0_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane0_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane0_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane1_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane1_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane1_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane1_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane2_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane2_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane2_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane2_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane3_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane3_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane3_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_corrected_blocks_lane3_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane0_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane0_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane0_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane0_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane1_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane1_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane1_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane1_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane2_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane2_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane2_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane2_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane3_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane3_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane3_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.fc_fec_uncorrectable_blocks_lane3_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_blocks_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_corrected_blocks_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_blocks_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_corrected_blocks_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_uncorrectable_blocks_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_uncorrectable_blocks_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_uncorrectable_blocks_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_uncorrectable_blocks_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_no_errors_blocks_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_no_errors_blocks_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_no_errors_blocks_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_no_errors_blocks_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_single_error_blocks_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_single_error_blocks_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_single_error_blocks_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_single_error_blocks_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_total_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_total_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_total_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_total_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane0_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane0_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane0_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane0_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane1_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane1_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane1_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane1_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane2_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane2_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane2_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane2_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane3_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane3_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rs_fec_corrected_symbols_lane3_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.rs_fec_corrected_symbols_lane3_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_down_events: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.link_down_events);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "successful_recovery_events: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_cntrs.successful_recovery_events);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PER_TRAFFIC_CLASS_CONGESTION_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "wred_discard_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_traffic_class_cong_layout.wred_discard_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "wred_discard_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_traffic_class_cong_layout.wred_discard_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ecn_marked_tc_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_traffic_class_cong_layout.ecn_marked_tc_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ecn_marked_tc_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_traffic_class_cong_layout.ecn_marked_tc_low);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PER_RECEIVE_BUFFER_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_no_buffer_discard_uc_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_receive_buffer_grp.rx_no_buffer_discard_uc_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "rx_no_buffer_discard_uc_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_per_receive_buffer_grp.rx_no_buffer_discard_uc_low);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PHYSICAL_LAYER_STATISTICAL_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.time_since_last_clear_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.time_since_last_clear_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_received_bits_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_received_bits_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_received_bits_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_received_bits_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_symbol_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_symbol_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_symbol_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_symbol_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_corrected_bits_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_corrected_bits_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_corrected_bits_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_corrected_bits_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane0_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane0_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane0_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane0_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane1_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane1_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane1_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane1_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane2_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane2_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane2_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane2_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane3_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane3_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane3_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane3_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane4_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane4_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane4_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane4_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane5_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane5_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane5_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane5_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane6_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane6_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane6_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane6_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane7_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane7_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_raw_errors_lane7_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_raw_errors_lane7_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_magnitude);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_coef);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "effective_ber_magnitude: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.effective_ber_magnitude);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "effective_ber_coef: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.effective_ber_coef);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_ber_magnitude: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.symbol_ber_magnitude);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_fec_ber_coef: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.symbol_fec_ber_coef);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane0: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane0: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane0);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane1: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane1: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane1);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane2: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane2: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane2);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane3: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane3: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane3);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane4: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane4: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane4);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane5: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane5: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane5);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane6: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane6: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane6);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_magnitude_lane7: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_magnitude_lane7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "raw_ber_coef_lane7: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.raw_ber_coef_lane7);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_effective_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_effective_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_effective_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.phys_layer_stat_cntrs.phy_effective_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_OUT_OF_BAND_PORT_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_ucast_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.if_in_ucast_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_ucast_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.if_in_ucast_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.if_in_octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.if_in_octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_discards_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.if_in_discards_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_discards_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.if_in_discards_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.if_in_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_in_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.if_in_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_crc_align_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.ether_stats_crc_align_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_crc_align_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.ether_stats_crc_align_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_undersize_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.ether_stats_undersize_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_undersize_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.ether_stats_undersize_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_oversize_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.ether_stats_oversize_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "ether_stats_oversize_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.ether_stats_oversize_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_symbol_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.dot3stats_symbol_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3stats_symbol_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.dot3stats_symbol_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3in_pause_frames_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.dot3in_pause_frames_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3in_pause_frames_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.dot3in_pause_frames_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3control_in_unknown_opcodes_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.dot3control_in_unknown_opcodes_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3control_in_unknown_opcodes_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.dot3control_in_unknown_opcodes_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_ucast_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.if_out_ucast_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_ucast_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.if_out_ucast_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_octets_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.if_out_octets_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_octets_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.if_out_octets_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3out_pause_frames_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.dot3out_pause_frames_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "dot3out_pause_frames_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.dot3out_pause_frames_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.if_out_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "if_out_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.if_out_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_time_since_last_clear_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.phy_time_since_last_clear_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_time_since_last_clear_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.phy_time_since_last_clear_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_received_bits_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.phy_received_bits_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_received_bits_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.phy_received_bits_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_symbol_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.phy_symbol_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "phy_symbol_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.eth_oob_port_cntrs.phy_symbol_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_INFINIBAND_PORT_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_error_counter: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.symbol_error_counter);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_error_recovery_counter: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.link_error_recovery_counter);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_downed_counter: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.link_downed_counter);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_errors: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.port_rcv_errors);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_remote_physical_errors: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.port_rcv_remote_physical_errors);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_switch_relay_errors: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.port_rcv_switch_relay_errors);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_discards: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.port_xmit_discards);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_constraint_errors: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.port_xmit_constraint_errors);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_constraint_errors: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.port_rcv_constraint_errors);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_link_integrity_errors: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.local_link_integrity_errors);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "excessive_buffer_overrun_errors: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.excessive_buffer_overrun_errors);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vl_15_dropped: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.vl_15_dropped);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_data: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.port_xmit_data);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_data: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.port_rcv_data);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_pkts: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.port_xmit_pkts);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_pkts: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.port_rcv_pkts);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_wait: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_portcntrs_attribute_grp_data.port_xmit_wait);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_INFINIBAND_EXTENDED_PORT_COUNTERS_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_error_counter_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.symbol_error_counter_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "symbol_error_counter_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.symbol_error_counter_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_error_recovery_counter_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.link_error_recovery_counter_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_error_recovery_counter_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.link_error_recovery_counter_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_downed_counter_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.link_downed_counter_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_downed_counter_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.link_downed_counter_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_remote_physical_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_remote_physical_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_remote_physical_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_remote_physical_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_switch_relay_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_switch_relay_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_switch_relay_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_switch_relay_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_discards_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_discards_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_discards_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_discards_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_constraint_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_constraint_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_constraint_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_constraint_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_constraint_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_constraint_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_constraint_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_constraint_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_link_integrity_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.local_link_integrity_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "local_link_integrity_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.local_link_integrity_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "excessive_buffer_overrun_errors_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.excessive_buffer_overrun_errors_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "excessive_buffer_overrun_errors_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.excessive_buffer_overrun_errors_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vl_15_dropped_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.vl_15_dropped_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "vl_15_dropped_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.vl_15_dropped_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_data_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_data_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_data_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_data_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_data_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_data_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_data_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_data_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_rcv_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_rcv_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_wait_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_wait_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_xmit_wait_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_xmit_wait_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_effective_rcv_pkts_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_effective_rcv_pkts_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_effective_rcv_pkts_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_effective_rcv_pkts_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_effective_rcv_data_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_effective_rcv_data_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "port_effective_rcv_data_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.IB_long_portcntrs_attribute_grp_data.port_effective_rcv_data_low);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_PLR_COUNTERS_GROUP_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rcv_codes_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_rcv_codes_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rcv_codes_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_rcv_codes_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rcv_code_err_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_rcv_code_err_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rcv_code_err_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_rcv_code_err_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rcv_uncorrectable_code_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_rcv_uncorrectable_code_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_rcv_uncorrectable_code_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_rcv_uncorrectable_code_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_codes_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_xmit_codes_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_codes_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_xmit_codes_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_retry_codes_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_xmit_retry_codes_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_retry_codes_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_xmit_retry_codes_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_retry_events_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_xmit_retry_events_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_retry_events_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_xmit_retry_events_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_sync_events_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_sync_events_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_sync_events_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_sync_events_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "hi_retransmission_rate_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.hi_retransmission_rate_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "hi_retransmission_rate_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.hi_retransmission_rate_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_retry_codes_within_t_sec_max_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_xmit_retry_codes_within_t_sec_max_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "plr_xmit_retry_codes_within_t_sec_max_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.plr_xmit_retry_codes_within_t_sec_max_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pre_plr_ber_magnitude: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.pre_plr_ber_magnitude);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "pre_plr_ber_coef: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_plr_counters.pre_plr_ber_coef);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    case SXD_PPCNT_GRP_RS_FEC_HISTOGRAM_GROUP_E:
        for (index = 0; index < SXD_PPCNT_HIST_NUM; index++) {
            snp_res = snprintf(buffer, buffer_length - buffer_size, "hi: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_rs_fec_histograms_counters.hist[index].hi);
            buffer += snp_res;
            buffer_size += snp_res;
            snp_res = snprintf(buffer, buffer_length - buffer_size, "lo: 0x%x\n", reg_data->ppcnt_reg.counter_set.ppcnt_rs_fec_histograms_counters.hist[index].lo);
            buffer += snp_res;
            buffer_size += snp_res;
        }
        break;

    case SXD_PPCNT_GRP_USR_XSR_PHYSICAL_LAYER_COUNTERS_GROUP_E:
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.time_since_last_clear_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "time_since_last_clear_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.time_since_last_clear_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane0_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane0_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane0_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane0_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane1_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane1_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane1_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane1_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane2_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane2_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane2_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane2_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane3_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane3_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane3_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane3_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane4_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane4_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane4_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane4_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane5_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane5_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane5_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane5_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane6_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane6_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane6_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane6_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane7_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane7_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_corrected_blocks_lane7_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_corrected_blocks_lane7_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane0_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane0_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane0_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane0_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane1_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane1_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane1_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane1_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane2_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane2_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane2_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane2_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane3_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane3_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane3_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane3_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane4_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane4_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane4_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane4_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane5_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane5_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane5_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane5_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane6_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane6_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane6_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane6_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane7_high: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane7_high);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "fc_fec_uncorrectable_blocks_lane7_low: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.fc_fec_uncorrectable_blocks_lane7_low);
        buffer += snp_res;
        buffer_size += snp_res;
        snp_res = snprintf(buffer, buffer_length - buffer_size, "link_down_events: 0x%x\n", reg_data->ppcnt_reg.counter_set.usr_xsr_physical_layer.link_down_events);
        buffer += snp_res;
        buffer_size += snp_res;
        break;

    default:
        /* Other types not supported yet */
        break;
    }

    return buffer_size;
}

int __spzr_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_spzr_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "swid: 0x%x\n", reg_data->spzr_reg.swid);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "enh_sw_p0: 0x%x\n", reg_data->spzr_reg.enh_sw_p0);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "capability_mask: 0x%x\n", reg_data->spzr_reg.capability_mask);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "system_image_guid_h: 0x%x\n", reg_data->spzr_reg.system_image_guid_h);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "system_image_guid_l: 0x%x\n", reg_data->spzr_reg.system_image_guid_l);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "node_guid_h: 0x%x\n", reg_data->spzr_reg.node_guid_h);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "node_guid_l: 0x%x\n", reg_data->spzr_reg.node_guid_l);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "capability_mask2: 0x%x\n", reg_data->spzr_reg.capability_mask2);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "max_pkey: 0x%x\n", reg_data->spzr_reg.max_pkey);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "node_description: 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", reg_data->spzr_reg.node_description[0], reg_data->spzr_reg.node_description[1], reg_data->spzr_reg.node_description[2], reg_data->spzr_reg.node_description[3], reg_data->spzr_reg.node_description[4], reg_data->spzr_reg.node_description[5], reg_data->spzr_reg.node_description[6], reg_data->spzr_reg.node_description[7], reg_data->spzr_reg.node_description[8], reg_data->spzr_reg.node_description[9], reg_data->spzr_reg.node_description[10], reg_data->spzr_reg.node_description[11], reg_data->spzr_reg.node_description[12], reg_data->spzr_reg.node_description[13], reg_data->spzr_reg.node_description[14], reg_data->spzr_reg.node_description[15], reg_data->spzr_reg.node_description[16], reg_data->spzr_reg.node_description[17], reg_data->spzr_reg.node_description[18], reg_data->spzr_reg.node_description[19], reg_data->spzr_reg.node_description[20], reg_data->spzr_reg.node_description[21], reg_data->spzr_reg.node_description[22], reg_data->spzr_reg.node_description[23], reg_data->spzr_reg.node_description[24], reg_data->spzr_reg.node_description[25], reg_data->spzr_reg.node_description[26], reg_data->spzr_reg.node_description[27], reg_data->spzr_reg.node_description[28], reg_data->spzr_reg.node_description[29], reg_data->spzr_reg.node_description[30], reg_data->spzr_reg.node_description[31], reg_data->spzr_reg.node_description[32], reg_data->spzr_reg.node_description[33], reg_data->spzr_reg.node_description[34], reg_data->spzr_reg.node_description[35], reg_data->spzr_reg.node_description[36], reg_data->spzr_reg.node_description[37], reg_data->spzr_reg.node_description[38], reg_data->spzr_reg.node_description[39], reg_data->spzr_reg.node_description[40], reg_data->spzr_reg.node_description[41], reg_data->spzr_reg.node_description[42], reg_data->spzr_reg.node_description[43], reg_data->spzr_reg.node_description[44], reg_data->spzr_reg.node_description[45], reg_data->spzr_reg.node_description[46], reg_data->spzr_reg.node_description[47], reg_data->spzr_reg.node_description[48], reg_data->spzr_reg.node_description[49], reg_data->spzr_reg.node_description[50], reg_data->spzr_reg.node_description[51], reg_data->spzr_reg.node_description[52], reg_data->spzr_reg.node_description[53], reg_data->spzr_reg.node_description[54], reg_data->spzr_reg.node_description[55], reg_data->spzr_reg.node_description[56], reg_data->spzr_reg.node_description[57], reg_data->spzr_reg.node_description[58], reg_data->spzr_reg.node_description[59], reg_data->spzr_reg.node_description[60], reg_data->spzr_reg.node_description[61], reg_data->spzr_reg.node_description[62], reg_data->spzr_reg.node_description[63]);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int __mtcap_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_mtcap_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "slot_index: 0x%x\n", reg_data->mtcap_reg.slot_index);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "sensor_count: 0x%x\n", reg_data->mtcap_reg.sensor_count);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "internal_sensor_count: 0x%x\n", reg_data->mtcap_reg.internal_sensor_count);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "hi: 0x%x\n", reg_data->mtcap_reg.sensor_map.hi);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "lo: 0x%x\n", reg_data->mtcap_reg.sensor_map.lo);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int __ptys_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_ptys_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint16_t local_port = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "reserved_high: 0x%x\n", reg_data->ptys_reg.reserved_high);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "an_disable_admin: 0x%x\n", reg_data->ptys_reg.an_disable_admin);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "an_disable_cap: 0x%x\n", reg_data->ptys_reg.an_disable_cap);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "force_tx_aba_param: 0x%x\n", reg_data->ptys_reg.force_tx_aba_param);
    buffer += snp_res;
    buffer_size += snp_res;
    SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(local_port, reg_data->ptys_reg.local_port, reg_data->ptys_reg.lp_msb);
    snp_res = snprintf(buffer, buffer_length - buffer_size, "local_port: 0x%x\n", local_port);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "pnat: 0x%x\n", reg_data->ptys_reg.pnat);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "port_type: 0x%x\n", reg_data->ptys_reg.port_type);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "proto_mask: 0x%x\n", reg_data->ptys_reg.proto_mask);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "an_status: 0x%x\n", reg_data->ptys_reg.an_status);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "max_port_rate: 0x%x\n", reg_data->ptys_reg.max_port_rate);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "data_rate_oper: 0x%x\n", reg_data->ptys_reg.data_rate_oper);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ext_eth_proto_capability: 0x%x\n", reg_data->ptys_reg.ext_eth_proto_capability);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_proto_capability: 0x%x\n", reg_data->ptys_reg.eth_proto_capability);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_link_width_capability: 0x%x\n", reg_data->ptys_reg.ib_link_width_capability);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_proto_capability: 0x%x\n", reg_data->ptys_reg.ib_proto_capability);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ext_eth_proto_admin: 0x%x\n", reg_data->ptys_reg.ext_eth_proto_admin);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_proto_admin: 0x%x\n", reg_data->ptys_reg.eth_proto_admin);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_link_width_admin: 0x%x\n", reg_data->ptys_reg.ib_link_width_admin);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_proto_admin: 0x%x\n", reg_data->ptys_reg.ib_proto_admin);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ext_eth_proto_oper: 0x%x\n", reg_data->ptys_reg.ext_eth_proto_oper);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_proto_oper: 0x%x\n", reg_data->ptys_reg.eth_proto_oper);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_link_width_oper: 0x%x\n", reg_data->ptys_reg.ib_link_width_oper);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "ib_proto_oper: 0x%x\n", reg_data->ptys_reg.ib_proto_oper);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_proto_lp_valid: 0x%x\n", reg_data->ptys_reg.eth_proto_lp_valid);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "force_kr_frames_cap: 0x%x\n", reg_data->ptys_reg.force_kr_frames_cap);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "force_kr_frames_admin: 0x%x\n", reg_data->ptys_reg.force_kr_frames_admin);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "connector_type: 0x%x\n", reg_data->ptys_reg.connector_type);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "eth_proto_lp_advertise: 0x%x\n", reg_data->ptys_reg.eth_proto_lp_advertise);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int __mdir_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_mdir_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint32_t index = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "device_id: 0x");
    buffer += snp_res;
    buffer_size += snp_res;
    for (index = 0; index < SXD_MDIR_DEVICE_ID_NUM; index++) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "%x", reg_data->mdir_reg.device_id[index]);
        buffer += snp_res;
        buffer_size += snp_res;
    }
    snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int __spad_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_spad_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "base_mac: 0x%02x%02x%02x%02x%02x%02x\n", reg_data->spad_reg.base_mac[0], reg_data->spad_reg.base_mac[1], reg_data->spad_reg.base_mac[2], reg_data->spad_reg.base_mac[3], reg_data->spad_reg.base_mac[4], reg_data->spad_reg.base_mac[5]);
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}

int __msgi_reg_data_to_buffer_print(char buffer[], size_t buffer_length, struct ku_access_msgi_reg * reg_data)
{
    int buffer_size = 0, snp_res = 0;
    uint32_t index = 0;

    snp_res = snprintf(buffer, buffer_length - buffer_size, "serial_number: 0x");
    buffer += snp_res;
    buffer_size += snp_res;
    for (index = 0; index < SXD_MSGI_SERIAL_NUMBER_NUM; index++) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "%x", reg_data->msgi_reg.serial_number[index]);
        buffer += snp_res;
        buffer_size += snp_res;
    }
    snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "part_number: 0x");
    buffer += snp_res;
    buffer_size += snp_res;
    for (index = 0; index < SXD_MSGI_PART_NUMBER_NUM; index++) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "%x", reg_data->msgi_reg.part_number[index]);
        buffer += snp_res;
        buffer_size += snp_res;
    }
    snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "revision: 0x%x\n", reg_data->msgi_reg.revision);
    buffer += snp_res;
    buffer_size += snp_res;
    snp_res = snprintf(buffer, buffer_length - buffer_size, "product_name: 0x");
    buffer += snp_res;
    buffer_size += snp_res;
    for (index = 0; index < SXD_MSGI_PRODUCT_NAME_NUM; index++) {
        snp_res = snprintf(buffer, buffer_length - buffer_size, "%x", reg_data->msgi_reg.product_name[index]);
        buffer += snp_res;
        buffer_size += snp_res;
    }
    snp_res = snprintf(buffer, buffer_length - buffer_size, "\n");
    buffer += snp_res;
    buffer_size += snp_res;

    return buffer_size;
}


/* reg read */
ssize_t __pmdr_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    sxd_params_t              sxd_params;
    struct ku_access_pmdr_reg reg_data;
    const pmdr_data_t        *data = (pmdr_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = (char*)kmem_cache_alloc(__kbuffer_cache, GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for PMDR SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(struct ku_access_pmdr_reg));

    sxd_params.g_sx_dev = g_sx_dev;
    sxd_params.reg_id = MLXSW_PMDR_ID;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_PMDR_ID, 1);
    reg_data.dev_id = 1;

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.pmdr_reg.local_port,
                                        reg_data.pmdr_reg.lp_msb,
                                        data->local_port);
    reg_data.pmdr_reg.pnat = data->pnat;


    err = sx_spice_sxd_access(&sxd_params, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = __pmdr_reg_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    kmem_cache_free(__kbuffer_cache, kbuffer);
    return size;
}

ssize_t __mvcap_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                      *kbuffer = NULL;
    int                        err = 0;
    ssize_t                    size = 0;
    ssize_t                    print_data_size = 0;
    sxd_params_t               sxd_params;
    struct ku_access_mvcap_reg reg_data;
    const mvcap_data_t        *data = (mvcap_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = (char*)kmem_cache_alloc(__kbuffer_cache, GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for MVCAP SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(struct ku_access_mvcap_reg));

    sxd_params.g_sx_dev = g_sx_dev;
    sxd_params.reg_id = MLXSW_MVCAP_ID;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_MVCAP_ID, 1);
    reg_data.dev_id = 1;
    reg_data.mvcap_reg.slot_index = data->slot_index;


    err = sx_spice_sxd_access(&sxd_params, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = __mvcap_reg_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    kmem_cache_free(__kbuffer_cache, kbuffer);
    return size;
}

ssize_t __pddr_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    sxd_params_t              sxd_params;
    struct ku_access_pddr_reg reg_data;
    const pddr_data_t        *data = (pddr_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = (char*)kmem_cache_alloc(__kbuffer_cache, GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for PDDR SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(struct ku_access_pddr_reg));

    sxd_params.g_sx_dev = g_sx_dev;
    sxd_params.reg_id = MLXSW_PDDR_ID;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_PDDR_ID, 1);
    reg_data.dev_id = 1;

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.pddr_reg.local_port,
                                        reg_data.pddr_reg.lp_msb,
                                        data->local_port);
    reg_data.pddr_reg.pnat = data->pnat;
    reg_data.pddr_reg.port_type = data->port_type;
    reg_data.pddr_reg.page_select = data->page_select;


    err = sx_spice_sxd_access(&sxd_params, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = __pddr_reg_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    kmem_cache_free(__kbuffer_cache, kbuffer);
    return size;
}

ssize_t __mgir_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    sxd_params_t              sxd_params;
    struct ku_access_mgir_reg reg_data;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = (char*)kmem_cache_alloc(__kbuffer_cache, GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for MGIR SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(struct ku_access_mgir_reg));

    sxd_params.g_sx_dev = g_sx_dev;
    sxd_params.reg_id = MLXSW_MGIR_ID;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_MGIR_ID, 1);
    reg_data.dev_id = 1;


    err = sx_spice_sxd_access(&sxd_params, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = __mgir_reg_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    kmem_cache_free(__kbuffer_cache, kbuffer);
    return size;
}

ssize_t __ppcnt_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                      *kbuffer = NULL;
    int                        err = 0;
    ssize_t                    size = 0;
    ssize_t                    print_data_size = 0;
    sxd_params_t               sxd_params;
    struct ku_access_ppcnt_reg reg_data;
    const ppcnt_data_t        *data = (ppcnt_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = (char*)kmem_cache_alloc(__kbuffer_cache, GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for PPCNT SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(struct ku_access_ppcnt_reg));

    sxd_params.g_sx_dev = g_sx_dev;
    sxd_params.reg_id = MLXSW_PPCNT_ID;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_PPCNT_ID, 1);
    reg_data.dev_id = 1;
    reg_data.ppcnt_reg.swid = data->swid;

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.ppcnt_reg.local_port,
                                        reg_data.ppcnt_reg.lp_msb,
                                        data->local_port);
    reg_data.ppcnt_reg.pnat = data->pnat;
    reg_data.ppcnt_reg.port_type = data->port_type;
    reg_data.ppcnt_reg.grp = data->grp;
    reg_data.ppcnt_reg.prio_tc = data->prio_tc;


    err = sx_spice_sxd_access(&sxd_params, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = __ppcnt_reg_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    kmem_cache_free(__kbuffer_cache, kbuffer);
    return size;
}

ssize_t __spzr_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    sxd_params_t              sxd_params;
    struct ku_access_spzr_reg reg_data;
    const spzr_data_t        *data = (spzr_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = (char*)kmem_cache_alloc(__kbuffer_cache, GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for SPZR SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(struct ku_access_spzr_reg));

    sxd_params.g_sx_dev = g_sx_dev;
    sxd_params.reg_id = MLXSW_SPZR_ID;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_SPZR_ID, 1);
    reg_data.dev_id = 1;
    reg_data.spzr_reg.swid = data->swid;


    err = sx_spice_sxd_access(&sxd_params, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = __spzr_reg_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    kmem_cache_free(__kbuffer_cache, kbuffer);
    return size;
}

ssize_t __mtcap_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                      *kbuffer = NULL;
    int                        err = 0;
    ssize_t                    size = 0;
    ssize_t                    print_data_size = 0;
    sxd_params_t               sxd_params;
    struct ku_access_mtcap_reg reg_data;
    const mtcap_data_t        *data = (mtcap_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = (char*)kmem_cache_alloc(__kbuffer_cache, GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for MTCAP SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(struct ku_access_mtcap_reg));

    sxd_params.g_sx_dev = g_sx_dev;
    sxd_params.reg_id = MLXSW_MTCAP_ID;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_MTCAP_ID, 1);
    reg_data.dev_id = 1;
    reg_data.mtcap_reg.slot_index = data->slot_index;


    err = sx_spice_sxd_access(&sxd_params, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = __mtcap_reg_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    kmem_cache_free(__kbuffer_cache, kbuffer);
    return size;
}

ssize_t __ptys_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    sxd_params_t              sxd_params;
    struct ku_access_ptys_reg reg_data;
    const ptys_data_t        *data = (ptys_data_t*)filp->f_inode->i_private;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = (char*)kmem_cache_alloc(__kbuffer_cache, GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for PTYS SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(struct ku_access_ptys_reg));

    sxd_params.g_sx_dev = g_sx_dev;
    sxd_params.reg_id = MLXSW_PTYS_ID;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_PTYS_ID, 1);
    reg_data.dev_id = 1;

    SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(reg_data.ptys_reg.local_port,
                                        reg_data.ptys_reg.lp_msb,
                                        data->local_port);
    reg_data.ptys_reg.pnat = data->pnat;
    reg_data.ptys_reg.port_type = data->port_type;
    reg_data.ptys_reg.proto_mask = data->proto_mask;


    err = sx_spice_sxd_access(&sxd_params, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = __ptys_reg_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    kmem_cache_free(__kbuffer_cache, kbuffer);
    return size;
}

ssize_t __mdir_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    sxd_params_t              sxd_params;
    struct ku_access_mdir_reg reg_data;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = (char*)kmem_cache_alloc(__kbuffer_cache, GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for MDIR SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(struct ku_access_mdir_reg));

    sxd_params.g_sx_dev = g_sx_dev;
    sxd_params.reg_id = MLXSW_MDIR_ID;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_MDIR_ID, 1);
    reg_data.dev_id = 1;


    err = sx_spice_sxd_access(&sxd_params, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = __mdir_reg_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    kmem_cache_free(__kbuffer_cache, kbuffer);
    return size;
}

ssize_t __spad_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    sxd_params_t              sxd_params;
    struct ku_access_spad_reg reg_data;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = (char*)kmem_cache_alloc(__kbuffer_cache, GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for SPAD SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(struct ku_access_spad_reg));

    sxd_params.g_sx_dev = g_sx_dev;
    sxd_params.reg_id = MLXSW_SPAD_ID;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_SPAD_ID, 1);
    reg_data.dev_id = 1;


    err = sx_spice_sxd_access(&sxd_params, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = __spad_reg_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    kmem_cache_free(__kbuffer_cache, kbuffer);
    return size;
}

ssize_t __msgi_read(struct file *filp, char *buf, size_t lbuf, loff_t *ppos)
{
    char                     *kbuffer = NULL;
    int                       err = 0;
    ssize_t                   size = 0;
    ssize_t                   print_data_size = 0;
    sxd_params_t              sxd_params;
    struct ku_access_msgi_reg reg_data;

    if (*ppos != 0) {
        return 0;
    }

    kbuffer = (char*)kmem_cache_alloc(__kbuffer_cache, GFP_KERNEL);
    if (!kbuffer) {
        printk(KERN_ERR "Failed to allocate kernel buffer for MSGI SPICE file generation\n");
        return 0;
    }

    memset(kbuffer, 0, sizeof(char) * KERNEL_BUFFER_SIZE);
    memset(&reg_data, 0, sizeof(struct ku_access_msgi_reg));

    sxd_params.g_sx_dev = g_sx_dev;
    sxd_params.reg_id = MLXSW_MSGI_ID;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, MLXSW_MSGI_ID, 1);
    reg_data.dev_id = 1;


    err = sx_spice_sxd_access(&sxd_params, &reg_data);
    if (err) {
        print_data_size = snprintf(kbuffer, sizeof(char) * 5, "N/A\n");
        size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);
        goto out;
    }

    print_data_size = __msgi_reg_data_to_buffer_print(kbuffer, sizeof(char) * KERNEL_BUFFER_SIZE, &reg_data);

    size = simple_read_from_buffer(buf, lbuf, ppos, kbuffer, print_data_size + 1);

out:
    kmem_cache_free(__kbuffer_cache, kbuffer);
    return size;
}


/* file operations */

static const struct file_operations pmdr_fops = {
    .read = __pmdr_read
};
static const struct file_operations mvcap_fops = {
    .read = __mvcap_read
};
static const struct file_operations pddr_fops = {
    .read = __pddr_read
};
static const struct file_operations mgir_fops = {
    .read = __mgir_read
};
static const struct file_operations ppcnt_fops = {
    .read = __ppcnt_read
};
static const struct file_operations spzr_fops = {
    .read = __spzr_read
};
static const struct file_operations mtcap_fops = {
    .read = __mtcap_read
};
static const struct file_operations ptys_fops = {
    .read = __ptys_read
};
static const struct file_operations mdir_fops = {
    .read = __mdir_read
};
static const struct file_operations spad_fops = {
    .read = __spad_read
};
static const struct file_operations msgi_fops = {
    .read = __msgi_read
};

/* sx_spice_access_reg file_create */

int sx_spice_access_reg_pmdr_file_create(struct dentry *parent)
{
    pmdr_data_t *pmdr = NULL;

    pmdr = kzalloc(sizeof(pmdr_data_t), GFP_KERNEL);
    if (!pmdr) {
        printk(KERN_ERR "Failed to allocate pmdr for SPICE\n");
        goto out;
    }

    list_add_tail(&pmdr->pmdr_list, &__pmdr_list_head);

    pmdr->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    pmdr->pnat = sx_spice_tree_index_value_get(PNAT);


    debugfs_create_file("PMDR", 0644, parent, (void *)pmdr, &pmdr_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_mvcap_file_create(struct dentry *parent)
{
    mvcap_data_t *mvcap = NULL;

    mvcap = kzalloc(sizeof(mvcap_data_t), GFP_KERNEL);
    if (!mvcap) {
        printk(KERN_ERR "Failed to allocate mvcap for SPICE\n");
        goto out;
    }

    list_add_tail(&mvcap->mvcap_list, &__mvcap_list_head);

    mvcap->slot_index = sx_spice_tree_index_value_get(SLOT_INDEX);


    debugfs_create_file("MVCAP", 0644, parent, (void *)mvcap, &mvcap_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_pddr_file_create(struct dentry *parent)
{
    pddr_data_t *pddr = NULL;

    pddr = kzalloc(sizeof(pddr_data_t), GFP_KERNEL);
    if (!pddr) {
        printk(KERN_ERR "Failed to allocate pddr for SPICE\n");
        goto out;
    }

    list_add_tail(&pddr->pddr_list, &__pddr_list_head);

    pddr->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    pddr->pnat = sx_spice_tree_index_value_get(PNAT);
    pddr->port_type = sx_spice_tree_index_value_get(PORT_TYPE);
    pddr->page_select = sx_spice_tree_index_value_get(PAGE_SELECT);


    debugfs_create_file("PDDR", 0644, parent, (void *)pddr, &pddr_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_mgir_file_create(struct dentry *parent)
{
    mgir_data_t *mgir = NULL;

    mgir = kzalloc(sizeof(mgir_data_t), GFP_KERNEL);
    if (!mgir) {
        printk(KERN_ERR "Failed to allocate mgir for SPICE\n");
        goto out;
    }

    list_add_tail(&mgir->mgir_list, &__mgir_list_head);



    debugfs_create_file("MGIR", 0644, parent, (void *)mgir, &mgir_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_ppcnt_file_create(struct dentry *parent)
{
    ppcnt_data_t *ppcnt = NULL;

    ppcnt = kzalloc(sizeof(ppcnt_data_t), GFP_KERNEL);
    if (!ppcnt) {
        printk(KERN_ERR "Failed to allocate ppcnt for SPICE\n");
        goto out;
    }

    list_add_tail(&ppcnt->ppcnt_list, &__ppcnt_list_head);

    ppcnt->swid = sx_spice_tree_index_value_get(SWID);
    ppcnt->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    ppcnt->pnat = sx_spice_tree_index_value_get(PNAT);
    ppcnt->port_type = sx_spice_tree_index_value_get(PORT_TYPE);
    ppcnt->grp = sx_spice_tree_index_value_get(GRP);
    ppcnt->prio_tc = sx_spice_tree_index_value_get(PRIO_TC);


    debugfs_create_file("PPCNT", 0644, parent, (void *)ppcnt, &ppcnt_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_spzr_file_create(struct dentry *parent)
{
    spzr_data_t *spzr = NULL;

    spzr = kzalloc(sizeof(spzr_data_t), GFP_KERNEL);
    if (!spzr) {
        printk(KERN_ERR "Failed to allocate spzr for SPICE\n");
        goto out;
    }

    list_add_tail(&spzr->spzr_list, &__spzr_list_head);

    spzr->swid = sx_spice_tree_index_value_get(SWID);


    debugfs_create_file("SPZR", 0644, parent, (void *)spzr, &spzr_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_mtcap_file_create(struct dentry *parent)
{
    mtcap_data_t *mtcap = NULL;

    mtcap = kzalloc(sizeof(mtcap_data_t), GFP_KERNEL);
    if (!mtcap) {
        printk(KERN_ERR "Failed to allocate mtcap for SPICE\n");
        goto out;
    }

    list_add_tail(&mtcap->mtcap_list, &__mtcap_list_head);

    mtcap->slot_index = sx_spice_tree_index_value_get(SLOT_INDEX);


    debugfs_create_file("MTCAP", 0644, parent, (void *)mtcap, &mtcap_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_ptys_file_create(struct dentry *parent)
{
    ptys_data_t *ptys = NULL;

    ptys = kzalloc(sizeof(ptys_data_t), GFP_KERNEL);
    if (!ptys) {
        printk(KERN_ERR "Failed to allocate ptys for SPICE\n");
        goto out;
    }

    list_add_tail(&ptys->ptys_list, &__ptys_list_head);

    ptys->local_port = sx_spice_tree_index_value_get(LOCAL_PORT);
    ptys->pnat = sx_spice_tree_index_value_get(PNAT);
    ptys->port_type = sx_spice_tree_index_value_get(PORT_TYPE);
    ptys->proto_mask = sx_spice_tree_index_value_get(PROTO_MASK);


    debugfs_create_file("PTYS", 0644, parent, (void *)ptys, &ptys_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_mdir_file_create(struct dentry *parent)
{
    mdir_data_t *mdir = NULL;

    mdir = kzalloc(sizeof(mdir_data_t), GFP_KERNEL);
    if (!mdir) {
        printk(KERN_ERR "Failed to allocate mdir for SPICE\n");
        goto out;
    }

    list_add_tail(&mdir->mdir_list, &__mdir_list_head);



    debugfs_create_file("MDIR", 0644, parent, (void *)mdir, &mdir_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_spad_file_create(struct dentry *parent)
{
    spad_data_t *spad = NULL;

    spad = kzalloc(sizeof(spad_data_t), GFP_KERNEL);
    if (!spad) {
        printk(KERN_ERR "Failed to allocate spad for SPICE\n");
        goto out;
    }

    list_add_tail(&spad->spad_list, &__spad_list_head);



    debugfs_create_file("SPAD", 0644, parent, (void *)spad, &spad_fops);

    return 0;

out:
    return -ENOMEM;
}

int sx_spice_access_reg_msgi_file_create(struct dentry *parent)
{
    msgi_data_t *msgi = NULL;

    msgi = kzalloc(sizeof(msgi_data_t), GFP_KERNEL);
    if (!msgi) {
        printk(KERN_ERR "Failed to allocate msgi for SPICE\n");
        goto out;
    }

    list_add_tail(&msgi->msgi_list, &__msgi_list_head);



    debugfs_create_file("MSGI", 0644, parent, (void *)msgi, &msgi_fops);

    return 0;

out:
    return -ENOMEM;
}


/* sx_spice_access_reg list_free */
void sx_spice_access_reg_pmdr_list_free(void)
{
    pmdr_data_t *iter_pmdr, *tmp_pmdr;

    list_for_each_entry_safe(iter_pmdr, tmp_pmdr, &__pmdr_list_head, pmdr_list) {
        list_del(&iter_pmdr->pmdr_list);
        kfree(iter_pmdr);
    }
}

void sx_spice_access_reg_mvcap_list_free(void)
{
    mvcap_data_t *iter_mvcap, *tmp_mvcap;

    list_for_each_entry_safe(iter_mvcap, tmp_mvcap, &__mvcap_list_head, mvcap_list) {
        list_del(&iter_mvcap->mvcap_list);
        kfree(iter_mvcap);
    }
}

void sx_spice_access_reg_pddr_list_free(void)
{
    pddr_data_t *iter_pddr, *tmp_pddr;

    list_for_each_entry_safe(iter_pddr, tmp_pddr, &__pddr_list_head, pddr_list) {
        list_del(&iter_pddr->pddr_list);
        kfree(iter_pddr);
    }
}

void sx_spice_access_reg_mgir_list_free(void)
{
    mgir_data_t *iter_mgir, *tmp_mgir;

    list_for_each_entry_safe(iter_mgir, tmp_mgir, &__mgir_list_head, mgir_list) {
        list_del(&iter_mgir->mgir_list);
        kfree(iter_mgir);
    }
}

void sx_spice_access_reg_ppcnt_list_free(void)
{
    ppcnt_data_t *iter_ppcnt, *tmp_ppcnt;

    list_for_each_entry_safe(iter_ppcnt, tmp_ppcnt, &__ppcnt_list_head, ppcnt_list) {
        list_del(&iter_ppcnt->ppcnt_list);
        kfree(iter_ppcnt);
    }
}

void sx_spice_access_reg_spzr_list_free(void)
{
    spzr_data_t *iter_spzr, *tmp_spzr;

    list_for_each_entry_safe(iter_spzr, tmp_spzr, &__spzr_list_head, spzr_list) {
        list_del(&iter_spzr->spzr_list);
        kfree(iter_spzr);
    }
}

void sx_spice_access_reg_mtcap_list_free(void)
{
    mtcap_data_t *iter_mtcap, *tmp_mtcap;

    list_for_each_entry_safe(iter_mtcap, tmp_mtcap, &__mtcap_list_head, mtcap_list) {
        list_del(&iter_mtcap->mtcap_list);
        kfree(iter_mtcap);
    }
}

void sx_spice_access_reg_ptys_list_free(void)
{
    ptys_data_t *iter_ptys, *tmp_ptys;

    list_for_each_entry_safe(iter_ptys, tmp_ptys, &__ptys_list_head, ptys_list) {
        list_del(&iter_ptys->ptys_list);
        kfree(iter_ptys);
    }
}

void sx_spice_access_reg_mdir_list_free(void)
{
    mdir_data_t *iter_mdir, *tmp_mdir;

    list_for_each_entry_safe(iter_mdir, tmp_mdir, &__mdir_list_head, mdir_list) {
        list_del(&iter_mdir->mdir_list);
        kfree(iter_mdir);
    }
}

void sx_spice_access_reg_spad_list_free(void)
{
    spad_data_t *iter_spad, *tmp_spad;

    list_for_each_entry_safe(iter_spad, tmp_spad, &__spad_list_head, spad_list) {
        list_del(&iter_spad->spad_list);
        kfree(iter_spad);
    }
}

void sx_spice_access_reg_msgi_list_free(void)
{
    msgi_data_t *iter_msgi, *tmp_msgi;

    list_for_each_entry_safe(iter_msgi, tmp_msgi, &__msgi_list_head, msgi_list) {
        list_del(&iter_msgi->msgi_list);
        kfree(iter_msgi);
    }
}

