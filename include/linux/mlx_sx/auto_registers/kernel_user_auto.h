/*
 * Copyright (C) 2008-2022 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
  
/*
 * THIS FILE IS AUTO GENERATED.
 * DO NOT MAKE ANY CHANGES!
 * They will be erased with next update.
 *
 */

/**
 * ku_fmtc_reg structure is used to store the FMTC register parameters
 */
struct ku_fmtc_reg {
    uint8_t emt_index;
    uint8_t length;
    uint8_t update_geneve_length;
    uint8_t update_udp_tcp_length;
    uint8_t update_hbh_length;
    uint8_t update_ipv6_length;
    uint8_t update_ipv4_length;
    uint8_t update_udp_tcp_cs;
    uint8_t clear_udp_cs;
    uint16_t max_latency;
    uint32_t latency_invalid_value;
    uint32_t buffer_fill_level_invalid_value;
    uint16_t enc_l2_uirif;
    uint16_t enc_ipv4_id;
    uint8_t enc_ipv4_flag;
    uint16_t enc_ipv4_frag_offset;
    uint8_t enc_next_header;
    uint8_t enc_flc;
    uint8_t enc_flh;
    uint16_t enc_fl_prefix;
    uint8_t enc_fl_suffix;
};

/**
 * ku_access_fmtc_reg structure is used to store the access register FMTC command parameters
 */
struct ku_access_fmtc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_fmtc_reg      fmtc_reg; /**< fmtc_reg - fmtc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_ICSR_DATA_NUM 256

/**
 * ku_icsr_reg structure is used to store the ICSR register parameters
 */
struct ku_icsr_reg {
    uint32_t base_address;
    uint16_t num_reads;
    uint32_t data[SXD_ICSR_DATA_NUM];
};

/**
 * ku_access_icsr_reg structure is used to store the access register ICSR command parameters
 */
struct ku_access_icsr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_icsr_reg      icsr_reg; /**< icsr_reg - icsr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_iicr_reg structure is used to store the IICR register parameters
 */
struct ku_iicr_reg {
    uint8_t kvh_mark_clear;
    uint8_t clear_mc_rtr_tcam_value;
    uint8_t clear_mc_rtr_tcam_mask;
    uint16_t clear_pe_regions_value;
    uint16_t clear_pe_regions_mask;
    uint16_t clear_rifs_value;
    uint16_t clear_rifs_mask;
    uint8_t traps_2_default;
};

/**
 * ku_access_iicr_reg structure is used to store the access register IICR command parameters
 */
struct ku_access_iicr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_iicr_reg      iicr_reg; /**< iicr_reg - iicr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_FPUMS_PORT_MASK_NUM 16

/**
 * ku_fpums_reg structure is used to store the FPUMS register parameters
 */
struct ku_fpums_reg {
    uint8_t global;
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t mask;
    uint8_t port_user_mem;
    uint32_t port_mask[SXD_FPUMS_PORT_MASK_NUM];
};

/**
 * ku_access_fpums_reg structure is used to store the access register FPUMS command parameters
 */
struct ku_access_fpums_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_fpums_reg     fpums_reg; /**< fpums_reg - fpums register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_pmdr_reg structure is used to store the PMDR register parameters
 */
struct ku_pmdr_reg {
    uint8_t status;
    uint8_t version;
    uint8_t local_port;
    uint8_t pnat;
    uint8_t gb_valid;
    uint8_t mcm_tile_valid;
    uint8_t lp_msb;
    uint8_t pport;
    uint8_t module;
    uint8_t cluster;
    uint8_t clp_4x;
    uint8_t clp_1x;
    uint8_t gb_dp_num;
    uint8_t split;
    uint8_t swid;
    uint8_t module_lane_mask;
    uint8_t ib_port;
    uint8_t label_port_query;
    uint8_t local_port_query;
    uint8_t usr_sd_4x_tx;
    uint8_t usr_sd_4x_rx;
    uint8_t slot_index;
    uint8_t tile_cluster;
    uint8_t mcm_tile_num;
    uint8_t tile_pport;
    uint8_t gearbox_die_num;
    uint8_t vl_num;
    uint8_t lane7_physical_rx;
    uint8_t lane6_physical_rx;
    uint8_t lane5_physical_rx;
    uint8_t lane4_physical_rx;
    uint8_t lane3_physical_rx;
    uint8_t lane2_physical_rx;
    uint8_t lane1_physical_rx;
    uint8_t lane0_physical_rx;
    uint8_t pll_index;
    uint8_t lane7_physical_tx;
    uint8_t lane6_physical_tx;
    uint8_t lane5_physical_tx;
    uint8_t lane4_physical_tx;
    uint8_t lane3_physical_tx;
    uint8_t lane2_physical_tx;
    uint8_t lane1_physical_tx;
    uint8_t lane0_physical_tx;
    uint8_t VL7_lane_map;
    uint8_t VL6_lane_map;
    uint8_t VL5_lane_map;
    uint8_t VL4_lane_map;
    uint8_t VL3_lane_map;
    uint8_t VL2_lane_map;
    uint8_t VL1_lane_map;
    uint8_t VL0_lane_map;
    uint8_t VL15_lane_map;
    uint8_t VL14_lane_map;
    uint8_t VL13_lane_map;
    uint8_t VL12_lane_map;
    uint8_t VL11_lane_map;
    uint8_t VL10_lane_map;
    uint8_t VL9_lane_map;
    uint8_t VL8_lane_map;
    uint8_t VL23_lane_map;
    uint8_t VL22_lane_map;
    uint8_t VL21_lane_map;
    uint8_t VL20_lane_map;
    uint8_t VL19_lane_map;
    uint8_t VL18_lane_map;
    uint8_t VL17_lane_map;
    uint8_t VL16_lane_map;
    uint8_t VL31_lane_map;
    uint8_t VL30_lane_map;
    uint8_t VL29_lane_map;
    uint8_t VL28_lane_map;
    uint8_t VL27_lane_map;
    uint8_t VL26_lane_map;
    uint8_t VL25_lane_map;
    uint8_t VL24_lane_map;
};

/**
 * ku_access_pmdr_reg structure is used to store the access register PMDR command parameters
 */
struct ku_access_pmdr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmdr_reg      pmdr_reg; /**< pmdr_reg - pmdr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_spevet_et_vlan {
    SXD_SPEVET_ET_VLAN_ETHER_TYPE0_E = 0x0,
    SXD_SPEVET_ET_VLAN_ETHER_TYPE1_E = 0x1,
    SXD_SPEVET_ET_VLAN_ETHER_TYPE2_E = 0x2,
    SXD_SPEVET_ET_VLAN_MIN = SXD_SPEVET_ET_VLAN_ETHER_TYPE0_E,
    SXD_SPEVET_ET_VLAN_MAX = SXD_SPEVET_ET_VLAN_ETHER_TYPE2_E
} sxd_spevet_et_vlan_t;

/**
 * ku_spevet_reg structure is used to store the SPEVET register parameters
 */
struct ku_spevet_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    sxd_spevet_et_vlan_t et_vlan;
};

/**
 * ku_access_spevet_reg structure is used to store the access register SPEVET command parameters
 */
struct ku_access_spevet_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_spevet_reg    spevet_reg; /**< spevet_reg - spevet register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_igcr_reg structure is used to store the IGCR register parameters
 */
struct ku_igcr_reg {
    uint8_t ddd_lpm_high_ipv6;
    uint8_t ddd_lpm_high_ipv4;
    uint32_t ddd_pe_actions_priority;
    uint8_t pisbo;
};

/**
 * ku_access_igcr_reg structure is used to store the access register IGCR command parameters
 */
struct ku_access_igcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_igcr_reg      igcr_reg; /**< igcr_reg - igcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_pemrbt_reg structure is used to store the PEMRBT register parameters
 */
struct ku_pemrbt_reg {
    uint8_t op;
    uint8_t protocol;
    uint16_t group_id;
};

/**
 * ku_access_pemrbt_reg structure is used to store the access register PEMRBT command parameters
 */
struct ku_access_pemrbt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pemrbt_reg    pemrbt_reg; /**< pemrbt_reg - pemrbt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_qtqcr_reg structure is used to store the QTQCR register parameters
 */
struct ku_qtqcr_reg {
    uint8_t tqos_profile;
    uint8_t enc_set_dscp;
    uint8_t enc_set_sp;
    uint8_t enc_dscp_rw;
    uint8_t enc_pcp_rw;
    uint8_t dec_set_dscp;
    uint8_t dec_set_sp;
    uint8_t dec_set_pcp;
    uint8_t dec_dscp_rw;
    uint8_t dec_pcp_rw;
};

/**
 * ku_access_qtqcr_reg structure is used to store the access register QTQCR command parameters
 */
struct ku_access_qtqcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qtqcr_reg     qtqcr_reg; /**< qtqcr_reg - qtqcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_RSNH_DMAC_NUM 6

/**
 * ku_rsnh_reg structure is used to store the RSNH register parameters
 */
struct ku_rsnh_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t p2d_en;
    uint8_t dmac[SXD_RSNH_DMAC_NUM];
};

/**
 * ku_access_rsnh_reg structure is used to store the access register RSNH command parameters
 */
struct ku_access_rsnh_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rsnh_reg      rsnh_reg; /**< rsnh_reg - rsnh register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_fmte_reg structure is used to store the FMTE register parameters
 */
struct ku_fmte_reg {
    uint8_t emt_index;
    uint8_t entry_index;
    uint8_t cmd_id;
    uint16_t imm;
    uint8_t edit_en;
};

/**
 * ku_access_fmte_reg structure is used to store the access register FMTE command parameters
 */
struct ku_access_fmte_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_fmte_reg      fmte_reg; /**< fmte_reg - fmte register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_fphhc_reg structure is used to store the FPHHC register parameters
 */
struct ku_fphhc_reg {
    uint8_t hph;
    uint8_t my_ftlv_outer_en;
    uint8_t my_ftlv_inner_en;
    uint8_t my_ftlv_fpp;
};

/**
 * ku_access_fphhc_reg structure is used to store the access register FPHHC command parameters
 */
struct ku_access_fphhc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_fphhc_reg     fphhc_reg; /**< fphhc_reg - fphhc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_pecnee_reg structure is used to store the PECNEE register parameters
 */
struct ku_pecnee_reg {
    uint16_t region_id;
    uint16_t region_id_mask;
    uint16_t erp_id_bitwise;
    uint8_t ctcam;
};

/**
 * ku_access_pecnee_reg structure is used to store the access register PECNEE command parameters
 */
struct ku_access_pecnee_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pecnee_reg    pecnee_reg; /**< pecnee_reg - pecnee register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_SFTR_V2_PORT_NUM 32

#define SXD_SFTR_V2_MASK_NUM 32

/**
 * ku_sftr_v2_reg structure is used to store the SFTR_V2 register parameters
 */
struct ku_sftr_v2_reg {
    uint8_t swid;
    uint8_t flood_table;
    uint16_t index;
    uint8_t table_type;
    uint16_t range;
    uint32_t port[SXD_SFTR_V2_PORT_NUM];
    uint32_t mask[SXD_SFTR_V2_MASK_NUM];
};

/**
 * ku_access_sftr_v2_reg structure is used to store the access register SFTR_V2 command parameters
 */
struct ku_access_sftr_v2_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sftr_v2_reg   sftr_v2_reg; /**< sftr_v2_reg - sftr_v2 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

typedef struct sxd_mvcap_sensor_map {
    uint32_t hi;
    uint32_t lo;
} sxd_mvcap_sensor_map_t;

/**
 * ku_mvcap_reg structure is used to store the MVCAP register parameters
 */
struct ku_mvcap_reg {
    sxd_mvcap_sensor_map_t sensor_map;
    uint8_t slot_index;
};

/**
 * ku_access_mvcap_reg structure is used to store the access register MVCAP command parameters
 */
struct ku_access_mvcap_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mvcap_reg     mvcap_reg; /**< mvcap_reg - mvcap register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_mtmp_tee {
    SXD_MTMP_TEE_DO_NOT_GENERATE_EVENT_E = 0x0,
    SXD_MTMP_TEE_GENERATE_EVENT_E = 0x1,
    SXD_MTMP_TEE_GENERATE_SINGLE_EVENT_E = 0x2,
    SXD_MTMP_TEE_MIN = SXD_MTMP_TEE_DO_NOT_GENERATE_EVENT_E,
    SXD_MTMP_TEE_MAX = SXD_MTMP_TEE_GENERATE_SINGLE_EVENT_E
} sxd_mtmp_tee_t;

/**
 * ku_mtmp_reg structure is used to store the MTMP register parameters
 */
struct ku_mtmp_reg {
    uint8_t i;
    uint8_t ig;
    uint8_t asic_index;
    uint8_t slot_index;
    uint16_t sensor_index;
    uint16_t max_operational_temperature;
    uint16_t temperature;
    uint8_t mte;
    uint8_t mtr;
    uint8_t weme;
    uint8_t sdme;
    uint16_t max_temperature;
    sxd_mtmp_tee_t tee;
    uint8_t sdee;
    uint16_t temperature_threshold_hi;
    uint16_t temperature_threshold_lo;
    uint32_t sensor_name_hi;
    uint32_t sensor_name_lo;
};

/**
 * ku_access_mtmp_reg structure is used to store the access register MTMP command parameters
 */
struct ku_access_mtmp_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mtmp_reg      mtmp_reg; /**< mtmp_reg - mtmp register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_tieem_reg structure is used to store the TIEEM register parameters
 */
struct ku_tieem_reg {
    uint8_t overlay_ecn;
    uint8_t underlay_ecn;
};

/**
 * ku_access_tieem_reg structure is used to store the access register TIEEM command parameters
 */
struct ku_access_tieem_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tieem_reg     tieem_reg; /**< tieem_reg - tieem register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_PMSC_PORT_MAPPING_UPDATED_NUM 8

/**
 * ku_pmsc_reg structure is used to store the PMSC register parameters
 */
struct ku_pmsc_reg {
    uint32_t port_mapping_updated[SXD_PMSC_PORT_MAPPING_UPDATED_NUM];
};

/**
 * ku_access_pmsc_reg structure is used to store the access register PMSC command parameters
 */
struct ku_access_pmsc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmsc_reg      pmsc_reg; /**< pmsc_reg - pmsc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_mogcr_toc_fmt {
    SXD_MOGCR_TOC_FMT_FREE_RUNNING_CLOCK_E = 0x0,
    SXD_MOGCR_TOC_FMT_UTC_E = 0x1,
    SXD_MOGCR_TOC_FMT_MIN = SXD_MOGCR_TOC_FMT_FREE_RUNNING_CLOCK_E,
    SXD_MOGCR_TOC_FMT_MAX = SXD_MOGCR_TOC_FMT_UTC_E
} sxd_mogcr_toc_fmt_t;

/**
 * ku_mogcr_reg structure is used to store the MOGCR register parameters
 */
struct ku_mogcr_reg {
    uint8_t tele_managed;
    uint8_t ptp_iftc;
    uint8_t ptp_eftc;
    uint8_t sid;
    uint16_t mirroring_pid_base;
    uint16_t mirror_latency_units;
    uint16_t latency_histogram_units;
    sxd_mogcr_toc_fmt_t toc_fmt;
};

/**
 * ku_access_mogcr_reg structure is used to store the access register MOGCR command parameters
 */
struct ku_access_mogcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mogcr_reg     mogcr_reg; /**< mogcr_reg - mogcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_qtqdr_reg structure is used to store the QTQDR register parameters
 */
struct ku_qtqdr_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t tqos_profile;
    uint8_t color;
    uint8_t switch_prio;
    uint8_t exp;
    uint8_t dscp;
};

/**
 * ku_access_qtqdr_reg structure is used to store the access register QTQDR command parameters
 */
struct ku_access_qtqdr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qtqdr_reg     qtqdr_reg; /**< qtqdr_reg - qtqdr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_rtdp_type {
    SXD_RTDP_TYPE_NVE_E = 0x0,
    SXD_RTDP_TYPE_IPINIP_E = 0x1,
    SXD_RTDP_TYPE_GENERIC_DECAP_E = 0x2,
    SXD_RTDP_TYPE_MIN = SXD_RTDP_TYPE_NVE_E,
    SXD_RTDP_TYPE_MAX = SXD_RTDP_TYPE_GENERIC_DECAP_E
} sxd_rtdp_type_t;

typedef struct sxd_rtdp_rtdp_nve_decap {
    uint8_t tqos_profile_en;
    uint8_t tqos_profile;
    uint8_t decap_disable;
} sxd_rtdp_rtdp_nve_decap_t;

typedef struct sxd_rtdp_rtdp_ipinip {
    uint16_t irif;
    uint8_t sip_check;
    uint8_t type_check;
    uint8_t gre_key_check;
    uint8_t tqos_profile_en;
    uint8_t tqos_profile;
    uint32_t ipv4_usip;
    uint32_t ipv6_usip_ptr;
    uint32_t expected_gre_key;
} sxd_rtdp_rtdp_ipinip_t;

typedef struct sxd_rtdp_rtdp_generic {
    uint8_t checks_mode;
    uint8_t allow_decap;
    uint8_t tqos_profile_l2;
    uint8_t tqos_profile_l3;
    uint8_t tunnel_port;
    uint8_t checks_nve_decap_disable;
    uint16_t irif;
    uint8_t gre_key_check;
    uint8_t type_check;
    uint8_t sip_check;
    uint32_t ipv4_usip;
    uint32_t ipv6_usip_ptr;
    uint32_t expected_gre_key;
} sxd_rtdp_rtdp_generic_t;

union rtdp_rtdp_entry {
    sxd_rtdp_rtdp_nve_decap_t rtdp_nve_decap;
    sxd_rtdp_rtdp_ipinip_t rtdp_ipinip;
    sxd_rtdp_rtdp_generic_t rtdp_generic;
};

/**
 * ku_rtdp_reg structure is used to store the RTDP register parameters
 */
struct ku_rtdp_reg {
    sxd_rtdp_type_t type;
    uint32_t tunnel_index;
    union rtdp_rtdp_entry rtdp_entry;
    uint16_t egress_router_interface;
};

/**
 * ku_access_rtdp_reg structure is used to store the access register RTDP command parameters
 */
struct ku_access_rtdp_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rtdp_reg      rtdp_reg; /**< rtdp_reg - rtdp register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_pecner_reg structure is used to store the PECNER register parameters
 */
struct ku_pecner_reg {
    uint8_t clear;
    uint32_t erp_initial_high;
    uint32_t erp_initial_low;
    uint32_t erp_post_bf_high;
    uint32_t erp_post_bf_low;
    uint32_t erp_lookup_high;
    uint32_t erp_lookup_low;
    uint32_t erp_any_match_high;
    uint32_t erp_any_match_low;
    uint32_t erp_final_match_high;
    uint32_t erp_final_match_low;
};

/**
 * ku_access_pecner_reg structure is used to store the access register PECNER command parameters
 */
struct ku_access_pecner_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pecner_reg    pecner_reg; /**< pecner_reg - pecner register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_IFBO_OUTER_HEADER_FIELDS_ENABLE_NUM 5

/**
 * ku_ifbo_reg structure is used to store the IFBO register parameters
 */
struct ku_ifbo_reg {
    uint8_t type;
    uint16_t outer_header_enables;
    uint32_t outer_header_fields_enable[SXD_IFBO_OUTER_HEADER_FIELDS_ENABLE_NUM];
};

/**
 * ku_access_ifbo_reg structure is used to store the access register IFBO command parameters
 */
struct ku_access_ifbo_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ifbo_reg      ifbo_reg; /**< ifbo_reg - ifbo register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_tneem_reg structure is used to store the TNEEM register parameters
 */
struct ku_tneem_reg {
    uint8_t overlay_ecn;
    uint8_t underlay_ecn;
};

/**
 * ku_access_tneem_reg structure is used to store the access register TNEEM command parameters
 */
struct ku_access_tneem_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tneem_reg     tneem_reg; /**< tneem_reg - tneem register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_qtdem_reg structure is used to store the QTDEM register parameters
 */
struct ku_qtdem_reg {
    uint8_t tqos_profile;
    uint8_t underlay_ecn;
    uint8_t overlay_ecn;
    uint8_t eip_ecn;
    uint8_t trap_en;
    uint16_t trap_id;
};

/**
 * ku_access_qtdem_reg structure is used to store the access register QTDEM command parameters
 */
struct ku_access_qtdem_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qtdem_reg     qtdem_reg; /**< qtdem_reg - qtdem register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_TNIFR_PORT_FILTER_NUM 8

#define SXD_TNIFR_PORT_FILTER_UPDATE_EN_NUM 8

/**
 * ku_tnifr_reg structure is used to store the TNIFR register parameters
 */
struct ku_tnifr_reg {
    uint8_t table_id;
    uint8_t tunnel_port;
    uint32_t port_filter[SXD_TNIFR_PORT_FILTER_NUM];
    uint32_t port_filter_update_en[SXD_TNIFR_PORT_FILTER_UPDATE_EN_NUM];
};

/**
 * ku_access_tnifr_reg structure is used to store the access register TNIFR command parameters
 */
struct ku_access_tnifr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tnifr_reg     tnifr_reg; /**< tnifr_reg - tnifr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_PEAPS_TCAM_REGION_INFO_NUM 16

/**
 * ku_peaps_reg structure is used to store the PEAPS register parameters
 */
struct ku_peaps_reg {
    uint8_t busy;
    uint8_t ovf;
    uint16_t ct_offset;
    uint16_t ct_size;
    uint8_t tcam_region_info[SXD_PEAPS_TCAM_REGION_INFO_NUM];
    uint32_t priority_start;
    uint32_t priority_end;
    uint32_t priority_inc;
};

/**
 * ku_access_peaps_reg structure is used to store the access register PEAPS command parameters
 */
struct ku_access_peaps_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_peaps_reg     peaps_reg; /**< peaps_reg - peaps register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_pmpe_error_type {
    SXD_PMPE_ERROR_TYPE_POWER_BUDGET_EXCEEDED_E = 0x0,
    SXD_PMPE_ERROR_TYPE_LONG_RANGE_FOR_NON_MLNX_CABLE_OR_MODULE_E = 0x1,
    SXD_PMPE_ERROR_TYPE_BUS_STUCK_E = 0x2,
    SXD_PMPE_ERROR_TYPE_BAD_OR_UNSUPPORTED_EEPROM_E = 0x3,
    SXD_PMPE_ERROR_TYPE_ENFORCE_PART_NUMBER_LIST_E = 0x4,
    SXD_PMPE_ERROR_TYPE_UNSUPPORTED_CABLE_E = 0x5,
    SXD_PMPE_ERROR_TYPE_HIGH_TEMPERATURE_E = 0x6,
    SXD_PMPE_ERROR_TYPE_BAD_CABLE_E = 0x7,
    SXD_PMPE_ERROR_TYPE_PMD_TYPE_IS_NOT_ENABLED_E = 0x8,
    SXD_PMPE_ERROR_TYPE_PCIE_SYSTEM_POWER_SLOT_EXCEEDED_E = 0xc,
    SXD_PMPE_ERROR_TYPE_MIN = SXD_PMPE_ERROR_TYPE_POWER_BUDGET_EXCEEDED_E,
    SXD_PMPE_ERROR_TYPE_MAX = SXD_PMPE_ERROR_TYPE_PCIE_SYSTEM_POWER_SLOT_EXCEEDED_E
} sxd_pmpe_error_type_t;

/**
 * ku_pmpe_reg structure is used to store the PMPE register parameters
 */
struct ku_pmpe_reg {
    uint8_t slot_index;
    uint8_t module;
    uint8_t module_status;
    sxd_pmpe_error_type_t error_type;
};

/**
 * ku_access_pmpe_reg structure is used to store the access register PMPE command parameters
 */
struct ku_access_pmpe_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmpe_reg      pmpe_reg; /**< pmpe_reg - pmpe register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_hcot_tunnel_port {
    SXD_HCOT_TUNNEL_PORT_NVE_E = 0x1,
    SXD_HCOT_TUNNEL_PORT_VPLS_E = 0x2,
    SXD_HCOT_TUNNEL_PORT_FLEX_TUNNEL0_E = 0x4,
    SXD_HCOT_TUNNEL_PORT_FLEX_TUNNEL1_E = 0x8,
    SXD_HCOT_TUNNEL_PORT_MIN = SXD_HCOT_TUNNEL_PORT_NVE_E,
    SXD_HCOT_TUNNEL_PORT_MAX = SXD_HCOT_TUNNEL_PORT_FLEX_TUNNEL1_E
} sxd_hcot_tunnel_port_t;


typedef enum sxd_hcot_key_type {
    SXD_HCOT_KEY_TYPE_ETHERTYPE_E = 0x0,
    SXD_HCOT_KEY_TYPE_NEXT_PROTO_E = 0x1,
    SXD_HCOT_KEY_TYPE_LAYER4_PORT_E = 0x2,
    SXD_HCOT_KEY_TYPE_ICMP_IGMP_TYPE_E = 0x3,
    SXD_HCOT_KEY_TYPE_MIN = SXD_HCOT_KEY_TYPE_ETHERTYPE_E,
    SXD_HCOT_KEY_TYPE_MAX = SXD_HCOT_KEY_TYPE_ICMP_IGMP_TYPE_E
} sxd_hcot_key_type_t;

typedef struct sxd_hcot_hcot_key_ethernet {
    uint16_t ethertype;
    sxd_hcot_tunnel_port_t tunnel_port;
} sxd_hcot_hcot_key_ethernet_t;

typedef struct sxd_hcot_hcot_key_next_proto {
    uint8_t is_ipv4;
    uint8_t ip_proto;
    sxd_hcot_tunnel_port_t tunnel_port;
} sxd_hcot_hcot_key_next_proto_t;

typedef struct sxd_hcot_hcot_key_layer4_port {
    uint8_t is_udp;
    uint8_t is_ipv4;
    uint16_t l4_port;
    sxd_hcot_tunnel_port_t tunnel_port;
} sxd_hcot_hcot_key_layer4_port_t;

typedef struct sxd_hcot_hcot_key_icmp_igmp_type {
    uint8_t is_igmp;
    uint8_t is_ipv4;
    uint8_t max;
    uint8_t min;
    sxd_hcot_tunnel_port_t tunnel_port;
} sxd_hcot_hcot_key_icmp_igmp_type_t;

union hcot_key {
    sxd_hcot_hcot_key_ethernet_t hcot_key_ethernet;
    sxd_hcot_hcot_key_next_proto_t hcot_key_next_proto;
    sxd_hcot_hcot_key_layer4_port_t hcot_key_layer4_port;
    sxd_hcot_hcot_key_icmp_igmp_type_t hcot_key_icmp_igmp_type;
};

union hcot_mask {
    sxd_hcot_hcot_key_ethernet_t hcot_key_ethernet;
    sxd_hcot_hcot_key_next_proto_t hcot_key_next_proto;
    sxd_hcot_hcot_key_layer4_port_t hcot_key_layer4_port;
    sxd_hcot_hcot_key_icmp_igmp_type_t hcot_key_icmp_igmp_type;
};

/**
 * ku_hcot_reg structure is used to store the HCOT register parameters
 */
struct ku_hcot_reg {
    uint16_t trap_id;
    sxd_hcot_key_type_t key_type;
    union hcot_key key;
    union hcot_mask mask;
};

/**
 * ku_access_hcot_reg structure is used to store the access register HCOT command parameters
 */
struct ku_access_hcot_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_hcot_reg      hcot_reg; /**< hcot_reg - hcot register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_pddr_core_to_phy_link_proto_enabled {
    SXD_PDDR_CORE_TO_PHY_LINK_PROTO_ENABLED_SDR_E = 0x1,
    SXD_PDDR_CORE_TO_PHY_LINK_PROTO_ENABLED_DDR_E = 0x2,
    SXD_PDDR_CORE_TO_PHY_LINK_PROTO_ENABLED_QDR_E = 0x4,
    SXD_PDDR_CORE_TO_PHY_LINK_PROTO_ENABLED_FDR10_E = 0x8,
    SXD_PDDR_CORE_TO_PHY_LINK_PROTO_ENABLED_FDR_E = 0x10,
    SXD_PDDR_CORE_TO_PHY_LINK_PROTO_ENABLED_EDR_E = 0x20,
    SXD_PDDR_CORE_TO_PHY_LINK_PROTO_ENABLED_HDR_E = 0x40,
    SXD_PDDR_CORE_TO_PHY_LINK_PROTO_ENABLED_NDR_E = 0x80,
    SXD_PDDR_CORE_TO_PHY_LINK_PROTO_ENABLED_MIN = SXD_PDDR_CORE_TO_PHY_LINK_PROTO_ENABLED_SDR_E,
    SXD_PDDR_CORE_TO_PHY_LINK_PROTO_ENABLED_MAX = SXD_PDDR_CORE_TO_PHY_LINK_PROTO_ENABLED_NDR_E
} sxd_pddr_core_to_phy_link_proto_enabled_t;


typedef enum sxd_pddr_cable_link_speed_cap {
    SXD_PDDR_CABLE_LINK_SPEED_CAP_SDR_E = 0x1,
    SXD_PDDR_CABLE_LINK_SPEED_CAP_DDR_E = 0x2,
    SXD_PDDR_CABLE_LINK_SPEED_CAP_QDR_E = 0x4,
    SXD_PDDR_CABLE_LINK_SPEED_CAP_FDR10_E = 0x8,
    SXD_PDDR_CABLE_LINK_SPEED_CAP_FDR_E = 0x10,
    SXD_PDDR_CABLE_LINK_SPEED_CAP_EDR_E = 0x20,
    SXD_PDDR_CABLE_LINK_SPEED_CAP_HDR_E = 0x40,
    SXD_PDDR_CABLE_LINK_SPEED_CAP_NDR_E = 0x80,
    SXD_PDDR_CABLE_LINK_SPEED_CAP_MIN = SXD_PDDR_CABLE_LINK_SPEED_CAP_SDR_E,
    SXD_PDDR_CABLE_LINK_SPEED_CAP_MAX = SXD_PDDR_CABLE_LINK_SPEED_CAP_NDR_E
} sxd_pddr_cable_link_speed_cap_t;


typedef enum sxd_pddr_link_speed_active {
    SXD_PDDR_LINK_SPEED_ACTIVE_SDR_E = 0x1,
    SXD_PDDR_LINK_SPEED_ACTIVE_DDR_E = 0x2,
    SXD_PDDR_LINK_SPEED_ACTIVE_QDR_E = 0x4,
    SXD_PDDR_LINK_SPEED_ACTIVE_FDR10_E = 0x8,
    SXD_PDDR_LINK_SPEED_ACTIVE_FDR_E = 0x10,
    SXD_PDDR_LINK_SPEED_ACTIVE_EDR_E = 0x20,
    SXD_PDDR_LINK_SPEED_ACTIVE_HDR_E = 0x40,
    SXD_PDDR_LINK_SPEED_ACTIVE_NDR_E = 0x80,
    SXD_PDDR_LINK_SPEED_ACTIVE_MIN = SXD_PDDR_LINK_SPEED_ACTIVE_SDR_E,
    SXD_PDDR_LINK_SPEED_ACTIVE_MAX = SXD_PDDR_LINK_SPEED_ACTIVE_NDR_E
} sxd_pddr_link_speed_active_t;


typedef enum sxd_pddr_neg_mode_active {
    SXD_PDDR_NEG_MODE_ACTIVE_PROTOCOL_WAS_NOT_NEGOTIATED_E = 0x0,
    SXD_PDDR_NEG_MODE_ACTIVE_MLPN_REV0_NEGOTIATED_E = 0x1,
    SXD_PDDR_NEG_MODE_ACTIVE_CL73_ETHERNET_NEGOTIATED_E = 0x2,
    SXD_PDDR_NEG_MODE_ACTIVE_PROTOCOL_ACCORDING_TO_PARALLEL_DETECT_E = 0x3,
    SXD_PDDR_NEG_MODE_ACTIVE_STANDARD_IB_NEGOTIATED_E = 0x4,
    SXD_PDDR_NEG_MODE_ACTIVE_MIN = SXD_PDDR_NEG_MODE_ACTIVE_PROTOCOL_WAS_NOT_NEGOTIATED_E,
    SXD_PDDR_NEG_MODE_ACTIVE_MAX = SXD_PDDR_NEG_MODE_ACTIVE_STANDARD_IB_NEGOTIATED_E
} sxd_pddr_neg_mode_active_t;


typedef enum sxd_pddr_phy_mngr_fsm_state {
    SXD_PDDR_PHY_MNGR_FSM_STATE_DISABLED_E = 0x0,
    SXD_PDDR_PHY_MNGR_FSM_STATE_OPEN_PORT_E = 0x1,
    SXD_PDDR_PHY_MNGR_FSM_STATE_POLLING_E = 0x2,
    SXD_PDDR_PHY_MNGR_FSM_STATE_ACTIVE_OR_LINKUP_E = 0x3,
    SXD_PDDR_PHY_MNGR_FSM_STATE_CLOSE_PORT_E = 0x4,
    SXD_PDDR_PHY_MNGR_FSM_STATE_PHY_UP_E = 0x5,
    SXD_PDDR_PHY_MNGR_FSM_STATE_RX_DISABLE_E = 0x7,
    SXD_PDDR_PHY_MNGR_FSM_STATE_MIN = SXD_PDDR_PHY_MNGR_FSM_STATE_DISABLED_E,
    SXD_PDDR_PHY_MNGR_FSM_STATE_MAX = SXD_PDDR_PHY_MNGR_FSM_STATE_RX_DISABLE_E
} sxd_pddr_phy_mngr_fsm_state_t;


typedef enum sxd_pddr_ib_phy_fsm_state {
    SXD_PDDR_IB_PHY_FSM_STATE_IB_AN_FSM_DISABLED_E = 0x0,
    SXD_PDDR_IB_PHY_FSM_STATE_IB_AN_FSM_INITIALY_E = 0x1,
    SXD_PDDR_IB_PHY_FSM_STATE_IB_AN_FSM_RCVR_CFG_E = 0x2,
    SXD_PDDR_IB_PHY_FSM_STATE_IB_AN_FSM_CFG_TEST_E = 0x3,
    SXD_PDDR_IB_PHY_FSM_STATE_IB_AN_FSM_WAIT_RMT_TEST_E = 0x4,
    SXD_PDDR_IB_PHY_FSM_STATE_IB_AN_FSM_WAIT_CFG_ENHANCED_E = 0x5,
    SXD_PDDR_IB_PHY_FSM_STATE_IB_AN_FSM_CFG_IDLE_E = 0x6,
    SXD_PDDR_IB_PHY_FSM_STATE_IB_AN_FSM_LINK_UP_E = 0x7,
    SXD_PDDR_IB_PHY_FSM_STATE_IB_AN_FSM_POLLING_E = 0x8,
    SXD_PDDR_IB_PHY_FSM_STATE_IB_AN_FSM_SYNC_CHECK_E = 0x9,
    SXD_PDDR_IB_PHY_FSM_STATE_MIN = SXD_PDDR_IB_PHY_FSM_STATE_IB_AN_FSM_DISABLED_E,
    SXD_PDDR_IB_PHY_FSM_STATE_MAX = SXD_PDDR_IB_PHY_FSM_STATE_IB_AN_FSM_SYNC_CHECK_E
} sxd_pddr_ib_phy_fsm_state_t;


typedef enum sxd_pddr_retran_mode_active {
    SXD_PDDR_RETRAN_MODE_ACTIVE_NO_RETRANSMISSION_E = 0x0,
    SXD_PDDR_RETRAN_MODE_ACTIVE_LLR_E = 0x1,
    SXD_PDDR_RETRAN_MODE_ACTIVE_MIN = SXD_PDDR_RETRAN_MODE_ACTIVE_NO_RETRANSMISSION_E,
    SXD_PDDR_RETRAN_MODE_ACTIVE_MAX = SXD_PDDR_RETRAN_MODE_ACTIVE_LLR_E
} sxd_pddr_retran_mode_active_t;


typedef enum sxd_pddr_retran_mode_request {
    SXD_PDDR_RETRAN_MODE_REQUEST_NO_RETRANSMISSION_E = 0x0,
    SXD_PDDR_RETRAN_MODE_REQUEST_LLR_E = 0x1,
    SXD_PDDR_RETRAN_MODE_REQUEST_MIN = SXD_PDDR_RETRAN_MODE_REQUEST_NO_RETRANSMISSION_E,
    SXD_PDDR_RETRAN_MODE_REQUEST_MAX = SXD_PDDR_RETRAN_MODE_REQUEST_LLR_E
} sxd_pddr_retran_mode_request_t;


typedef enum sxd_pddr_loopback_mode {
    SXD_PDDR_LOOPBACK_MODE_NO_LOOPBACK_ACTIVE_E = 0x0,
    SXD_PDDR_LOOPBACK_MODE_PHY_REMOTE_LOOPBACK_E = 0x1,
    SXD_PDDR_LOOPBACK_MODE_PHY_LOCAL_LOOPBACK_E = 0x2,
    SXD_PDDR_LOOPBACK_MODE_EXTERNAL_LOCAL_LOOPBACK_E = 0x4,
    SXD_PDDR_LOOPBACK_MODE_NEAR_END_ANALOG_LOOPBACK_E = 0x8,
    SXD_PDDR_LOOPBACK_MODE_NEAR_END_DIGITAL_LOOPBACK_E = 0x10,
    SXD_PDDR_LOOPBACK_MODE_LL_LOCAL_LOOPBACK_E = 0x80,
    SXD_PDDR_LOOPBACK_MODE_MIN = SXD_PDDR_LOOPBACK_MODE_NO_LOOPBACK_ACTIVE_E,
    SXD_PDDR_LOOPBACK_MODE_MAX = SXD_PDDR_LOOPBACK_MODE_LL_LOCAL_LOOPBACK_E
} sxd_pddr_loopback_mode_t;


typedef enum sxd_pddr_fec_mode_active {
    SXD_PDDR_FEC_MODE_ACTIVE_NO_FEC_E = 0x0,
    SXD_PDDR_FEC_MODE_ACTIVE_FIRECODE_FEC_E = 0x1,
    SXD_PDDR_FEC_MODE_ACTIVE_STANDARD_RS_FEC_E = 0x2,
    SXD_PDDR_FEC_MODE_ACTIVE_STANDARD_LL_RS_FEC_E = 0x3,
    SXD_PDDR_FEC_MODE_ACTIVE_RESERVED_E = 0x4,
    SXD_PDDR_FEC_MODE_ACTIVE_INTERLEAVED_STANDARD_RS_E = 0x6,
    SXD_PDDR_FEC_MODE_ACTIVE_STANDARD_RS_E = 0x7,
    SXD_PDDR_FEC_MODE_ACTIVE_ZERO_LATENCY_FEC_E = 0x8,
    SXD_PDDR_FEC_MODE_ACTIVE_ETHERNET_CONSORTIUM_LL_50G_RS_FEC_E = 0x9,
    SXD_PDDR_FEC_MODE_ACTIVE_INTERLEAVED_ETHERNET_CONSORTIUM_LL_50G_RS_FEC_E = 0xa,
    SXD_PDDR_FEC_MODE_ACTIVE_INTERLEAVED_STANDARD_RS_FEC_PLR_E = 0xb,
    SXD_PDDR_FEC_MODE_ACTIVE_RS_E = 0xc,
    SXD_PDDR_FEC_MODE_ACTIVE_LL_E = 0xd,
    SXD_PDDR_FEC_MODE_ACTIVE_ETHERNET_CONSORTIUM_LL_50G_RS_FEC_PLR_E = 0xe,
    SXD_PDDR_FEC_MODE_ACTIVE_INTERLEAVED_ETHERNET_CONSORTIUM_LL_50G_RS_FEC_PLR_E = 0xf,
    SXD_PDDR_FEC_MODE_ACTIVE_MIN = SXD_PDDR_FEC_MODE_ACTIVE_NO_FEC_E,
    SXD_PDDR_FEC_MODE_ACTIVE_MAX = SXD_PDDR_FEC_MODE_ACTIVE_INTERLEAVED_ETHERNET_CONSORTIUM_LL_50G_RS_FEC_PLR_E
} sxd_pddr_fec_mode_active_t;


typedef enum sxd_pddr_core_to_phy_state {
    SXD_PDDR_CORE_TO_PHY_STATE_PHY_STATE_POLLING_E = 0x2,
    SXD_PDDR_CORE_TO_PHY_STATE_PHY_STATE_DISABLE_E = 0x3,
    SXD_PDDR_CORE_TO_PHY_STATE_PHY_STATE_LINKUP_E = 0x5,
    SXD_PDDR_CORE_TO_PHY_STATE_MIN = SXD_PDDR_CORE_TO_PHY_STATE_PHY_STATE_POLLING_E,
    SXD_PDDR_CORE_TO_PHY_STATE_MAX = SXD_PDDR_CORE_TO_PHY_STATE_PHY_STATE_LINKUP_E
} sxd_pddr_core_to_phy_state_t;


typedef enum sxd_pddr_psi_fsm_state {
    SXD_PDDR_PSI_FSM_STATE_PSI_FSM_IDLE_E = 0x0,
    SXD_PDDR_PSI_FSM_STATE_PSI_FSM_WAIT4UCDONE_E = 0x1,
    SXD_PDDR_PSI_FSM_STATE_PSI_FSM_SAFE_OPEN_CLOSE_E = 0x2,
    SXD_PDDR_PSI_FSM_STATE_PSI_ERROR_STATE_E = 0x3,
    SXD_PDDR_PSI_FSM_STATE_MIN = SXD_PDDR_PSI_FSM_STATE_PSI_FSM_IDLE_E,
    SXD_PDDR_PSI_FSM_STATE_MAX = SXD_PDDR_PSI_FSM_STATE_PSI_ERROR_STATE_E
} sxd_pddr_psi_fsm_state_t;


typedef enum sxd_pddr_cable_proto_cap_ext {
    SXD_PDDR_CABLE_PROTO_CAP_EXT_SDR_1X_E = 0x1,
    SXD_PDDR_CABLE_PROTO_CAP_EXT_SDR_2X_E = 0x2,
    SXD_PDDR_CABLE_PROTO_CAP_EXT_SDR_4X_E = 0x4,
    SXD_PDDR_CABLE_PROTO_CAP_EXT_FDR_4X_E = 0x1000,
    SXD_PDDR_CABLE_PROTO_CAP_EXT_EDR_2X_E = 0x4000,
    SXD_PDDR_CABLE_PROTO_CAP_EXT_EDR_4X_E = 0x8000,
    SXD_PDDR_CABLE_PROTO_CAP_EXT_HDR_1X_E = 0x10000,
    SXD_PDDR_CABLE_PROTO_CAP_EXT_HDR_2X_E = 0x20000,
    SXD_PDDR_CABLE_PROTO_CAP_EXT_HDR_4X_E = 0x40000,
    SXD_PDDR_CABLE_PROTO_CAP_EXT_NDR_2X_E = 0x200000,
    SXD_PDDR_CABLE_PROTO_CAP_EXT_NDR_4X_E = 0x400000,
    SXD_PDDR_CABLE_PROTO_CAP_EXT_MIN = SXD_PDDR_CABLE_PROTO_CAP_EXT_SDR_1X_E,
    SXD_PDDR_CABLE_PROTO_CAP_EXT_MAX = SXD_PDDR_CABLE_PROTO_CAP_EXT_NDR_4X_E
} sxd_pddr_cable_proto_cap_ext_t;

#define SXD_PDDR_STATUS_MESSAGE_NUM 236


typedef enum sxd_pddr_group_opcode {
    SXD_PDDR_GROUP_OPCODE_MONITOR_OPCODES_E = 0x0,
    SXD_PDDR_GROUP_OPCODE_ADVANCED_DEBUG_OPCODES_E = 0x1,
    SXD_PDDR_GROUP_OPCODE_MIN = SXD_PDDR_GROUP_OPCODE_MONITOR_OPCODES_E,
    SXD_PDDR_GROUP_OPCODE_MAX = SXD_PDDR_GROUP_OPCODE_ADVANCED_DEBUG_OPCODES_E
} sxd_pddr_group_opcode_t;

#define SXD_PDDR_ETH_LAST_LINK_DOWN_LANE_NUM 4

#define SXD_PDDR_KR_STARTUP_FSM_LANE_NUM 4

#define SXD_PDDR_KR_STARTUP_DEBUG_INDICATIONS_NUM 4


typedef enum sxd_pddr_ib_debug_indication {
    SXD_PDDR_IB_DEBUG_INDICATION_CAUSE_PLR_TX_MAX_OUTSTANDING_CELLS_E = 0x1,
    SXD_PDDR_IB_DEBUG_INDICATION_MIN = SXD_PDDR_IB_DEBUG_INDICATION_CAUSE_PLR_TX_MAX_OUTSTANDING_CELLS_E,
    SXD_PDDR_IB_DEBUG_INDICATION_MAX = SXD_PDDR_IB_DEBUG_INDICATION_CAUSE_PLR_TX_MAX_OUTSTANDING_CELLS_E
} sxd_pddr_ib_debug_indication_t;


typedef enum sxd_pddr_pm_debug_indication {
    SXD_PDDR_PM_DEBUG_INDICATION_PHY_TEST_MODE_E = 0x1,
    SXD_PDDR_PM_DEBUG_INDICATION_FORCE_MODE_EN_E = 0x2,
    SXD_PDDR_PM_DEBUG_INDICATION_MIN = SXD_PDDR_PM_DEBUG_INDICATION_PHY_TEST_MODE_E,
    SXD_PDDR_PM_DEBUG_INDICATION_MAX = SXD_PDDR_PM_DEBUG_INDICATION_FORCE_MODE_EN_E
} sxd_pddr_pm_debug_indication_t;


typedef enum sxd_pddr_pd_debug_indication {
    SXD_PDDR_PD_DEBUG_INDICATION_SPEED_CHANGE_HIGH_SPEED_MODULE_E = 0x1,
    SXD_PDDR_PD_DEBUG_INDICATION_FALSE_POSITIVE_SIGNAL_DETECT_E = 0x2,
    SXD_PDDR_PD_DEBUG_INDICATION_NV2NV_FORCE_E = 0x4,
    SXD_PDDR_PD_DEBUG_INDICATION_BAD_KR_MASK_E = 0x8,
    SXD_PDDR_PD_DEBUG_INDICATION_KR_MLX_PEER_E = 0x10,
    SXD_PDDR_PD_DEBUG_INDICATION_ENTERED_SIGNAL_DETECT_E = 0x20,
    SXD_PDDR_PD_DEBUG_INDICATION_ENTERED_RATE_CONFIG_E = 0x40,
    SXD_PDDR_PD_DEBUG_INDICATION_ENTERED_ACTIVATE_SUNFSM_E = 0x80,
    SXD_PDDR_PD_DEBUG_INDICATION_ENTERED_DONE_E = 0x100,
    SXD_PDDR_PD_DEBUG_INDICATION_ENTERED_SUBFSM_FAIL_E = 0x200,
    SXD_PDDR_PD_DEBUG_INDICATION_MIN = SXD_PDDR_PD_DEBUG_INDICATION_SPEED_CHANGE_HIGH_SPEED_MODULE_E,
    SXD_PDDR_PD_DEBUG_INDICATION_MAX = SXD_PDDR_PD_DEBUG_INDICATION_ENTERED_SUBFSM_FAIL_E
} sxd_pddr_pd_debug_indication_t;

#define SXD_PDDR_VENDOR_NAME_NUM 4

#define SXD_PDDR_VENDOR_PN_NUM 4

#define SXD_PDDR_VENDOR_SN_NUM 4


typedef enum sxd_pddr_cable_type {
    SXD_PDDR_CABLE_TYPE_UNIDENTIFIED_E = 0x0,
    SXD_PDDR_CABLE_TYPE_ACTIVE_CABLE_E = 0x1,
    SXD_PDDR_CABLE_TYPE_OPTICAL_MODULE_E = 0x2,
    SXD_PDDR_CABLE_TYPE_PASSIVE_COPPER_CABLE_E = 0x3,
    SXD_PDDR_CABLE_TYPE_CABLE_UNPLUGGED_E = 0x4,
    SXD_PDDR_CABLE_TYPE_TWISTED_PAIR_E = 0x5,
    SXD_PDDR_CABLE_TYPE_MIN = SXD_PDDR_CABLE_TYPE_UNIDENTIFIED_E,
    SXD_PDDR_CABLE_TYPE_MAX = SXD_PDDR_CABLE_TYPE_TWISTED_PAIR_E
} sxd_pddr_cable_type_t;


typedef enum sxd_pddr_cable_vendor {
    SXD_PDDR_CABLE_VENDOR_OTHER_E = 0x0,
    SXD_PDDR_CABLE_VENDOR_MELLANOX_E = 0x1,
    SXD_PDDR_CABLE_VENDOR_KNOWN_OUI_E = 0x2,
    SXD_PDDR_CABLE_VENDOR_NVIDIA_E = 0x3,
    SXD_PDDR_CABLE_VENDOR_MIN = SXD_PDDR_CABLE_VENDOR_OTHER_E,
    SXD_PDDR_CABLE_VENDOR_MAX = SXD_PDDR_CABLE_VENDOR_NVIDIA_E
} sxd_pddr_cable_vendor_t;


typedef enum sxd_pddr_module_st {
    SXD_PDDR_MODULE_ST_RESERVED_E = 0x0,
    SXD_PDDR_MODULE_ST_LOWPWR_STATE_E = 0x1,
    SXD_PDDR_MODULE_ST_PWRUP_STATE_E = 0x2,
    SXD_PDDR_MODULE_ST_READY_STATE_E = 0x3,
    SXD_PDDR_MODULE_ST_PWRDN_STATE_E = 0x4,
    SXD_PDDR_MODULE_ST_FAULT_STATE_E = 0x5,
    SXD_PDDR_MODULE_ST_MIN = SXD_PDDR_MODULE_ST_RESERVED_E,
    SXD_PDDR_MODULE_ST_MAX = SXD_PDDR_MODULE_ST_FAULT_STATE_E
} sxd_pddr_module_st_t;


typedef enum sxd_pddr_rx_power_type {
    SXD_PDDR_RX_POWER_TYPE_OMA_E = 0x0,
    SXD_PDDR_RX_POWER_TYPE_AVERAGE_POWER_E = 0x1,
    SXD_PDDR_RX_POWER_TYPE_MIN = SXD_PDDR_RX_POWER_TYPE_OMA_E,
    SXD_PDDR_RX_POWER_TYPE_MAX = SXD_PDDR_RX_POWER_TYPE_AVERAGE_POWER_E
} sxd_pddr_rx_power_type_t;


typedef enum sxd_pddr_dp_st_lane0 {
    SXD_PDDR_DP_ST_LANE0_DPDEACTIVATED_E = 0x1,
    SXD_PDDR_DP_ST_LANE0_DPINIT_E = 0x2,
    SXD_PDDR_DP_ST_LANE0_DPDEINIT_E = 0x3,
    SXD_PDDR_DP_ST_LANE0_DPACTIVATED_E = 0x4,
    SXD_PDDR_DP_ST_LANE0_DPTXTURNON_E = 0x5,
    SXD_PDDR_DP_ST_LANE0_DPTXTURNOFF_E = 0x6,
    SXD_PDDR_DP_ST_LANE0_DPINITIALIZED_E = 0x7,
    SXD_PDDR_DP_ST_LANE0_MIN = SXD_PDDR_DP_ST_LANE0_DPDEACTIVATED_E,
    SXD_PDDR_DP_ST_LANE0_MAX = SXD_PDDR_DP_ST_LANE0_DPINITIALIZED_E
} sxd_pddr_dp_st_lane0_t;


typedef enum sxd_pddr_tx_input_freq_sync {
    SXD_PDDR_TX_INPUT_FREQ_SYNC_TX_INPUT_LANES_1_8_E = 0x0,
    SXD_PDDR_TX_INPUT_FREQ_SYNC_TX_INPUT_LANES_1_4_AND_5_E = 0x1,
    SXD_PDDR_TX_INPUT_FREQ_SYNC_TX_INPUT_LANES_1_2_AND_3_4_AND_5_6_AND_7_8_E = 0x2,
    SXD_PDDR_TX_INPUT_FREQ_SYNC_LANES_MAY_BE_ASYNCHRONOUS_IN_FREQUENCY_E = 0x3,
    SXD_PDDR_TX_INPUT_FREQ_SYNC_MIN = SXD_PDDR_TX_INPUT_FREQ_SYNC_TX_INPUT_LANES_1_8_E,
    SXD_PDDR_TX_INPUT_FREQ_SYNC_MAX = SXD_PDDR_TX_INPUT_FREQ_SYNC_LANES_MAY_BE_ASYNCHRONOUS_IN_FREQUENCY_E
} sxd_pddr_tx_input_freq_sync_t;


typedef enum sxd_pddr_error_code {
    SXD_PDDR_ERROR_CODE_CONFIGUNDEFINED_E = 0x0,
    SXD_PDDR_ERROR_CODE_CONFIGSUCCESS_E = 0x1,
    SXD_PDDR_ERROR_CODE_CONFIGREJECTED_E = 0x2,
    SXD_PDDR_ERROR_CODE_CONFIGREJECTEDINVALIDAPPSEL_E = 0x3,
    SXD_PDDR_ERROR_CODE_CONFIGREJECTEDINVALIDDATAPATH_E = 0x4,
    SXD_PDDR_ERROR_CODE_CONFIGREJECTEDINVALIDSI_E = 0x5,
    SXD_PDDR_ERROR_CODE_CONFIGREJECTEDLANESINUSE_E = 0x6,
    SXD_PDDR_ERROR_CODE_CONFIGREJECTEDPARTIALDATAPATH_E = 0x7,
    SXD_PDDR_ERROR_CODE_CONFIGINPROGRESS_E = 0xc,
    SXD_PDDR_ERROR_CODE_MIN = SXD_PDDR_ERROR_CODE_CONFIGUNDEFINED_E,
    SXD_PDDR_ERROR_CODE_MAX = SXD_PDDR_ERROR_CODE_CONFIGINPROGRESS_E
} sxd_pddr_error_code_t;

#define SXD_PDDR_CLR_MASK_NUM 8


typedef enum sxd_pddr_down_blame {
    SXD_PDDR_DOWN_BLAME_UNKNOWN_E = 0x0,
    SXD_PDDR_DOWN_BLAME_LOCAL_PHY_E = 0x1,
    SXD_PDDR_DOWN_BLAME_REMOTE_PHY_E = 0x2,
    SXD_PDDR_DOWN_BLAME_MIN = SXD_PDDR_DOWN_BLAME_UNKNOWN_E,
    SXD_PDDR_DOWN_BLAME_MAX = SXD_PDDR_DOWN_BLAME_REMOTE_PHY_E
} sxd_pddr_down_blame_t;


typedef enum sxd_pddr_local_reason_opcode {
    SXD_PDDR_LOCAL_REASON_OPCODE_NO_LINK_DOWN_INDICATION_E = 0x0,
    SXD_PDDR_LOCAL_REASON_OPCODE_UNKNOWN_REASON_E = 0x1,
    SXD_PDDR_LOCAL_REASON_OPCODE_HI_SER_OR_HI_BER_E = 0x2,
    SXD_PDDR_LOCAL_REASON_OPCODE_BLOCK_LOCK_LOSS_E = 0x3,
    SXD_PDDR_LOCAL_REASON_OPCODE_ALIGNMENT_LOSS_E = 0x4,
    SXD_PDDR_LOCAL_REASON_OPCODE_FEC_SYNC_LOSS_E = 0x5,
    SXD_PDDR_LOCAL_REASON_OPCODE_PLL_LOCK_LOSS_E = 0x6,
    SXD_PDDR_LOCAL_REASON_OPCODE_FIFO_OVERFLOW_E = 0x7,
    SXD_PDDR_LOCAL_REASON_OPCODE_FALSE_SKIP_CONDITION_E = 0x8,
    SXD_PDDR_LOCAL_REASON_OPCODE_MINOR_ERROR_THRESHOLD_EXCEEDED_E = 0x9,
    SXD_PDDR_LOCAL_REASON_OPCODE_PHYSICAL_LAYER_RETRANSMISSION_TIMEOUT_E = 0xa,
    SXD_PDDR_LOCAL_REASON_OPCODE_HEARTBEAT_ERRORS_E = 0xb,
    SXD_PDDR_LOCAL_REASON_OPCODE_LINK_LAYER_CREDIT_MONITORING_WATCHDOG_E = 0xc,
    SXD_PDDR_LOCAL_REASON_OPCODE_LINK_LAYER_INTEGRITY_THRESHOLD_EXCEEDED_E = 0xd,
    SXD_PDDR_LOCAL_REASON_OPCODE_LINK_LAYER_BUFFER_OVERRUN_E = 0xe,
    SXD_PDDR_LOCAL_REASON_OPCODE_DOWN_BY_OUTBAND_COMMAND_WITH_HEALTHY_LINK_E = 0xf,
    SXD_PDDR_LOCAL_REASON_OPCODE_DOWN_BY_OUTBAND_COMMAND_FOR_LINK_WITH_HI_BER_E = 0x10,
    SXD_PDDR_LOCAL_REASON_OPCODE_DOWN_BY_INBAND_COMMAND_WITH_HEALTHY_LINK_E = 0x11,
    SXD_PDDR_LOCAL_REASON_OPCODE_DOWN_BY_INBAND_COMMAND_FOR_LINK_WITH_HI_BER_E = 0x12,
    SXD_PDDR_LOCAL_REASON_OPCODE_DOWN_BY_VERIFICATION_GW_E = 0x13,
    SXD_PDDR_LOCAL_REASON_OPCODE_RECEIVED_REMOTE_FAULT_E = 0x14,
    SXD_PDDR_LOCAL_REASON_OPCODE_RECEIVED_TS1_E = 0x15,
    SXD_PDDR_LOCAL_REASON_OPCODE_DOWN_BY_MANAGEMENT_COMMAND_E = 0x16,
    SXD_PDDR_LOCAL_REASON_OPCODE_CABLE_WAS_UNPLUGGED_E = 0x17,
    SXD_PDDR_LOCAL_REASON_OPCODE_CABLE_ACCESS_ISSUE_E = 0x18,
    SXD_PDDR_LOCAL_REASON_OPCODE_THERMAL_SHUTDOWN_E = 0x19,
    SXD_PDDR_LOCAL_REASON_OPCODE_CURRENT_ISSUE_E = 0x1a,
    SXD_PDDR_LOCAL_REASON_OPCODE_POWER_BUDGET_E = 0x1b,
    SXD_PDDR_LOCAL_REASON_OPCODE_MIN = SXD_PDDR_LOCAL_REASON_OPCODE_NO_LINK_DOWN_INDICATION_E,
    SXD_PDDR_LOCAL_REASON_OPCODE_MAX = SXD_PDDR_LOCAL_REASON_OPCODE_POWER_BUDGET_E
} sxd_pddr_local_reason_opcode_t;


typedef enum sxd_pddr_ib_port_events {
    SXD_PDDR_IB_PORT_EVENTS_TS_AT_LINKUP_E = 0x1,
    SXD_PDDR_IB_PORT_EVENTS_IBL_LINK_RETRAIN_E = 0x2,
    SXD_PDDR_IB_PORT_EVENTS_RX_COMSKP_TIMEOUT_E = 0x4,
    SXD_PDDR_IB_PORT_EVENTS_MINOR_THRESHOLD_REACHED_E = 0x8,
    SXD_PDDR_IB_PORT_EVENTS_WATCH_DOG_E = 0x10,
    SXD_PDDR_IB_PORT_EVENTS_EXCESSIVE_BUFFER_E = 0x20,
    SXD_PDDR_IB_PORT_EVENTS_LLI_ERR_E = 0x40,
    SXD_PDDR_IB_PORT_EVENTS_LLR_LINK_RETRAIN_E = 0x80,
    SXD_PDDR_IB_PORT_EVENTS_BLOCK_LOCK_E = 0x100,
    SXD_PDDR_IB_PORT_EVENTS_SKIP_OR_COM_ALIGNMENT_LOSS_E = 0x200,
    SXD_PDDR_IB_PORT_EVENTS_FEC_LOCK_LOSS_E = 0x400,
    SXD_PDDR_IB_PORT_EVENTS_MAD_DOWN_COMMAND_E = 0x800,
    SXD_PDDR_IB_PORT_EVENTS_MIN = SXD_PDDR_IB_PORT_EVENTS_TS_AT_LINKUP_E,
    SXD_PDDR_IB_PORT_EVENTS_MAX = SXD_PDDR_IB_PORT_EVENTS_MAD_DOWN_COMMAND_E
} sxd_pddr_ib_port_events_t;


typedef enum sxd_pddr_etherent_port_events {
    SXD_PDDR_ETHERENT_PORT_EVENTS_REMOTE_FAULT_AT_LINKUP_E = 0x1,
    SXD_PDDR_ETHERENT_PORT_EVENTS_PCS_HI_BER_EVENT_E = 0x2,
    SXD_PDDR_ETHERENT_PORT_EVENTS_FEC_HI_SER_EVENT_E = 0x4,
    SXD_PDDR_ETHERENT_PORT_EVENTS_BLOCK_LOCK_LOSS_E = 0x8,
    SXD_PDDR_ETHERENT_PORT_EVENTS_ALIGNMENT_LOSS_E = 0x10,
    SXD_PDDR_ETHERENT_PORT_EVENTS_FEC_BLOCK_LOCK_LOSS_E = 0x20,
    SXD_PDDR_ETHERENT_PORT_EVENTS_MIN = SXD_PDDR_ETHERENT_PORT_EVENTS_REMOTE_FAULT_AT_LINKUP_E,
    SXD_PDDR_ETHERENT_PORT_EVENTS_MAX = SXD_PDDR_ETHERENT_PORT_EVENTS_FEC_BLOCK_LOCK_LOSS_E
} sxd_pddr_etherent_port_events_t;


typedef enum sxd_pddr_general_port_events {
    SXD_PDDR_GENERAL_PORT_EVENTS_FIFO_FULL_ERR_E = 0x1,
    SXD_PDDR_GENERAL_PORT_EVENTS_PAOS_DOWN_COMMAND_E = 0x2,
    SXD_PDDR_GENERAL_PORT_EVENTS_DISABLE_MASK_EVENT_E = 0x4,
    SXD_PDDR_GENERAL_PORT_EVENTS_PORT_EVENT_E = 0x8,
    SXD_PDDR_GENERAL_PORT_EVENTS_DEVICE_EVENT_E = 0x10,
    SXD_PDDR_GENERAL_PORT_EVENTS_SPIKE_DETECTED_E = 0x20,
    SXD_PDDR_GENERAL_PORT_EVENTS_MIN = SXD_PDDR_GENERAL_PORT_EVENTS_FIFO_FULL_ERR_E,
    SXD_PDDR_GENERAL_PORT_EVENTS_MAX = SXD_PDDR_GENERAL_PORT_EVENTS_SPIKE_DETECTED_E
} sxd_pddr_general_port_events_t;


typedef enum sxd_pddr_temp_flags {
    SXD_PDDR_TEMP_FLAGS_HIGH_TEMP_ALARM_E = 0x1,
    SXD_PDDR_TEMP_FLAGS_LOW_TEMP_ALARM_E = 0x2,
    SXD_PDDR_TEMP_FLAGS_HIGH_TEMP_WARNING_E = 0x4,
    SXD_PDDR_TEMP_FLAGS_LOW_TEMP_WARNING_E = 0x8,
    SXD_PDDR_TEMP_FLAGS_MIN = SXD_PDDR_TEMP_FLAGS_HIGH_TEMP_ALARM_E,
    SXD_PDDR_TEMP_FLAGS_MAX = SXD_PDDR_TEMP_FLAGS_LOW_TEMP_WARNING_E
} sxd_pddr_temp_flags_t;


typedef enum sxd_pddr_vcc_flags {
    SXD_PDDR_VCC_FLAGS_HIGH_VCC_ALARM_E = 0x1,
    SXD_PDDR_VCC_FLAGS_LOW_VCC_ALARM_E = 0x2,
    SXD_PDDR_VCC_FLAGS_HIGH_VCC_WARNING_E = 0x4,
    SXD_PDDR_VCC_FLAGS_LOW_VCC_WARNING_E = 0x8,
    SXD_PDDR_VCC_FLAGS_MIN = SXD_PDDR_VCC_FLAGS_HIGH_VCC_ALARM_E,
    SXD_PDDR_VCC_FLAGS_MAX = SXD_PDDR_VCC_FLAGS_LOW_VCC_WARNING_E
} sxd_pddr_vcc_flags_t;


typedef enum sxd_pddr_fw_module_state {
    SXD_PDDR_FW_MODULE_STATE_MS_READ_CHOOSE_MODULE_E = 0x0,
    SXD_PDDR_FW_MODULE_STATE_MS_READ_DEACTIVATE_LANES_STATE_E = 0x1,
    SXD_PDDR_FW_MODULE_STATE_MS_READ_VERFIY_MODULE_STATE_E = 0x2,
    SXD_PDDR_FW_MODULE_STATE_MS_READ_SET_APPLY_E = 0x3,
    SXD_PDDR_FW_MODULE_STATE_MS_READ_SET_DATAPATH_INIT_E = 0x4,
    SXD_PDDR_FW_MODULE_STATE_MS_READ_UPDATE_MODULE_DB_ACTIVE_SET_E = 0x5,
    SXD_PDDR_FW_MODULE_STATE_MS_READ_MODULE_STATE_READ_E = 0x6,
    SXD_PDDR_FW_MODULE_STATE_MS_READ_FINISH_E = 0x7,
    SXD_PDDR_FW_MODULE_STATE_MIN = SXD_PDDR_FW_MODULE_STATE_MS_READ_CHOOSE_MODULE_E,
    SXD_PDDR_FW_MODULE_STATE_MAX = SXD_PDDR_FW_MODULE_STATE_MS_READ_FINISH_E
} sxd_pddr_fw_module_state_t;


typedef enum sxd_pddr_fw_dp_state_lane7 {
    SXD_PDDR_FW_DP_STATE_LANE7_LANE_STATE_NOT_IN_USE_E = 0x0,
    SXD_PDDR_FW_DP_STATE_LANE7_LANE_STATE_DEACTIVATE_PAOS_E = 0x1,
    SXD_PDDR_FW_DP_STATE_LANE7_LANE_STATE_DEACTIVATE_SPEED_OR_APPLY_CHANGE_E = 0x2,
    SXD_PDDR_FW_DP_STATE_LANE7_LANE_STATE_VERIFY_E = 0x3,
    SXD_PDDR_FW_DP_STATE_LANE7_LANE_STATE_SET_APPLY_E = 0x4,
    SXD_PDDR_FW_DP_STATE_LANE7_LANE_STATE_UPDATE_MODULE_DB_ACTIVE_SET_E = 0x5,
    SXD_PDDR_FW_DP_STATE_LANE7_LANE_STATE_ACTIVATE_LANE_E = 0x6,
    SXD_PDDR_FW_DP_STATE_LANE7_LANE_STATE_VERIFY_ACTIVATE_E = 0x7,
    SXD_PDDR_FW_DP_STATE_LANE7_LANE_STATE_ACTIVE_E = 0x8,
    SXD_PDDR_FW_DP_STATE_LANE7_MIN = SXD_PDDR_FW_DP_STATE_LANE7_LANE_STATE_NOT_IN_USE_E,
    SXD_PDDR_FW_DP_STATE_LANE7_MAX = SXD_PDDR_FW_DP_STATE_LANE7_LANE_STATE_ACTIVE_E
} sxd_pddr_fw_dp_state_lane7_t;


typedef enum sxd_pddr_dp_req_status_lane7 {
    SXD_PDDR_DP_REQ_STATUS_LANE7_CONFIG_UNDEFINED_E = 0x0,
    SXD_PDDR_DP_REQ_STATUS_LANE7_CONFIG_SUCCESS_E = 0x1,
    SXD_PDDR_DP_REQ_STATUS_LANE7_CONFIG_REJECTEC_UNKOWN_REASON_E = 0x2,
    SXD_PDDR_DP_REQ_STATUS_LANE7_CONFIG_REJECTEC_INVALID_APPSEL_E = 0x3,
    SXD_PDDR_DP_REQ_STATUS_LANE7_CONFIG_REJECTEC_INVALID_DATAPATH_E = 0x4,
    SXD_PDDR_DP_REQ_STATUS_LANE7_CONFIG_REJECTEC_INVALID_SI_E = 0x5,
    SXD_PDDR_DP_REQ_STATUS_LANE7_CONFIG_REJECTEC_LANE_IN_USE_E = 0x6,
    SXD_PDDR_DP_REQ_STATUS_LANE7_CONFIG_REJECTEC_PARTIAL_DATAPATH_E = 0x7,
    SXD_PDDR_DP_REQ_STATUS_LANE7_CONFIG_FAILED_E = 0xb,
    SXD_PDDR_DP_REQ_STATUS_LANE7_CONFIG_IN_PROGRESS_E = 0xc,
    SXD_PDDR_DP_REQ_STATUS_LANE7_CUSTOM_REJECTED_VENDOR_SPECIFIC_E = 0xd,
    SXD_PDDR_DP_REQ_STATUS_LANE7_MIN = SXD_PDDR_DP_REQ_STATUS_LANE7_CONFIG_UNDEFINED_E,
    SXD_PDDR_DP_REQ_STATUS_LANE7_MAX = SXD_PDDR_DP_REQ_STATUS_LANE7_CUSTOM_REJECTED_VENDOR_SPECIFIC_E
} sxd_pddr_dp_req_status_lane7_t;


typedef enum sxd_pddr_pnat {
    SXD_PDDR_PNAT_LOCAL_PORT_NUMBER_E = 0x0,
    SXD_PDDR_PNAT_IB_OR_LABEL_PORT_NUMBER_E = 0x1,
    SXD_PDDR_PNAT_MIN = SXD_PDDR_PNAT_LOCAL_PORT_NUMBER_E,
    SXD_PDDR_PNAT_MAX = SXD_PDDR_PNAT_IB_OR_LABEL_PORT_NUMBER_E
} sxd_pddr_pnat_t;


typedef enum sxd_pddr_port_type {
    SXD_PDDR_PORT_TYPE_NETWORK_PORT_E = 0x0,
    SXD_PDDR_PORT_TYPE_NEAR_END_PORT_E = 0x1,
    SXD_PDDR_PORT_TYPE_INTERNAL_IC_LR_PORT_E = 0x2,
    SXD_PDDR_PORT_TYPE_FAR_END_PORT_E = 0x3,
    SXD_PDDR_PORT_TYPE_USR_MAIN_E = 0x4,
    SXD_PDDR_PORT_TYPE_USR_TILE_E = 0x5,
    SXD_PDDR_PORT_TYPE_MIN = SXD_PDDR_PORT_TYPE_NETWORK_PORT_E,
    SXD_PDDR_PORT_TYPE_MAX = SXD_PDDR_PORT_TYPE_USR_TILE_E
} sxd_pddr_port_type_t;


typedef enum sxd_pddr_module_info_ext {
    SXD_PDDR_MODULE_INFO_EXT_DBM_E = 0x0,
    SXD_PDDR_MODULE_INFO_EXT_UW_E = 0x1,
    SXD_PDDR_MODULE_INFO_EXT_MIN = SXD_PDDR_MODULE_INFO_EXT_DBM_E,
    SXD_PDDR_MODULE_INFO_EXT_MAX = SXD_PDDR_MODULE_INFO_EXT_UW_E
} sxd_pddr_module_info_ext_t;


typedef enum sxd_pddr_page_select {
    SXD_PDDR_PAGE_SELECT_OPERATIONAL_INFO_PAGE_E = 0x0,
    SXD_PDDR_PAGE_SELECT_TROUBLESHOOTING_INFO_PAGE_E = 0x1,
    SXD_PDDR_PAGE_SELECT_PHY_INFO_PAGE_E = 0x2,
    SXD_PDDR_PAGE_SELECT_MODULE_INFO_PAGE_E = 0x3,
    SXD_PDDR_PAGE_SELECT_PORT_EVENTS_PAGE_E = 0x4,
    SXD_PDDR_PAGE_SELECT_DEVICE_EVENTS_PAGE_E = 0x5,
    SXD_PDDR_PAGE_SELECT_LINK_DOWN_INFO_E = 0x6,
    SXD_PDDR_PAGE_SELECT_LINK_DOWN_EVENTS_E = 0x7,
    SXD_PDDR_PAGE_SELECT_LINK_UP_INFO_E = 0x8,
    SXD_PDDR_PAGE_SELECT_MODULE_LATCHED_FLAG_INFO_PAGE_E = 0x9,
    SXD_PDDR_PAGE_SELECT_LINK_DOWN_INFO_EXT_E = 0xa,
    SXD_PDDR_PAGE_SELECT_LINK_PARTNER_INFO_PAGE_E = 0xb,
    SXD_PDDR_PAGE_SELECT_MNG_DEBUG_PAGE_E = 0xfe,
    SXD_PDDR_PAGE_SELECT_PHY_DEBUG_PAGE_E = 0xff,
    SXD_PDDR_PAGE_SELECT_MIN = SXD_PDDR_PAGE_SELECT_OPERATIONAL_INFO_PAGE_E,
    SXD_PDDR_PAGE_SELECT_MAX = SXD_PDDR_PAGE_SELECT_PHY_DEBUG_PAGE_E
} sxd_pddr_page_select_t;

typedef struct sxd_pddr_pddr_phy_manager_link_enabed_ib {
    uint16_t phy_manager_link_width_enabled;
    uint16_t phy_manager_link_proto_enabled;
} sxd_pddr_pddr_phy_manager_link_enabed_ib_t;

typedef struct sxd_pddr_pddr_phy_manager_link_enabed_eth {
    uint32_t phy_manager_link_eth_enabled;
} sxd_pddr_pddr_phy_manager_link_enabed_eth_t;

union pddr_phy_manager_link_enabled {
    sxd_pddr_pddr_phy_manager_link_enabed_ib_t pddr_phy_manager_link_enabed_ib;
    sxd_pddr_pddr_phy_manager_link_enabed_eth_t pddr_phy_manager_link_enabed_eth;
};

typedef struct sxd_pddr_pddr_c2p_link_enabed_ib {
    uint16_t core_to_phy_link_width_enabled;
    sxd_pddr_core_to_phy_link_proto_enabled_t core_to_phy_link_proto_enabled;
} sxd_pddr_pddr_c2p_link_enabed_ib_t;

typedef struct sxd_pddr_pddr_c2p_link_enabed_eth {
    uint32_t core_to_phy_link_eth_enabled;
} sxd_pddr_pddr_c2p_link_enabed_eth_t;

union pddr_core_to_phy_link_enabled {
    sxd_pddr_pddr_c2p_link_enabed_ib_t pddr_c2p_link_enabed_ib;
    sxd_pddr_pddr_c2p_link_enabed_eth_t pddr_c2p_link_enabed_eth;
};

typedef struct sxd_pddr_pddr_cable_cap_ib {
    uint16_t cable_link_width_cap;
    sxd_pddr_cable_link_speed_cap_t cable_link_speed_cap;
} sxd_pddr_pddr_cable_cap_ib_t;

typedef struct sxd_pddr_pddr_cable_cap_eth {
    uint32_t cable_ext_eth_proto_cap;
} sxd_pddr_pddr_cable_cap_eth_t;

union pddr_cable_proto_cap {
    sxd_pddr_pddr_cable_cap_ib_t pddr_cable_cap_ib;
    sxd_pddr_pddr_cable_cap_eth_t pddr_cable_cap_eth;
};

typedef struct sxd_pddr_pddr_link_active_ib {
    uint16_t link_width_active;
    sxd_pddr_link_speed_active_t link_speed_active;
} sxd_pddr_pddr_link_active_ib_t;

typedef struct sxd_pddr_pddr_link_active_eth {
    uint32_t link_eth_active;
} sxd_pddr_pddr_link_active_eth_t;

union pddr_link_active {
    sxd_pddr_pddr_link_active_ib_t pddr_link_active_ib;
    sxd_pddr_pddr_link_active_eth_t pddr_link_active_eth;
};

typedef struct sxd_pddr_pddr_operation_info_page {
    uint8_t proto_active;
    sxd_pddr_neg_mode_active_t neg_mode_active;
    uint8_t pd_fsm_state;
    sxd_pddr_phy_mngr_fsm_state_t phy_mngr_fsm_state;
    uint8_t eth_an_fsm_state;
    sxd_pddr_ib_phy_fsm_state_t ib_phy_fsm_state;
    uint8_t phy_hst_fsm_state;
    union pddr_phy_manager_link_enabled phy_manager_link_enabled;
    union pddr_core_to_phy_link_enabled core_to_phy_link_enabled;
    union pddr_cable_proto_cap cable_proto_cap;
    union pddr_link_active link_active;
    sxd_pddr_retran_mode_active_t retran_mode_active;
    sxd_pddr_retran_mode_request_t retran_mode_request;
    sxd_pddr_loopback_mode_t loopback_mode;
    sxd_pddr_fec_mode_active_t fec_mode_active;
    uint16_t fec_mode_request;
    uint16_t profile_fec_in_use;
    uint8_t eth_25g_50g_fec_support;
    uint8_t eth_100g_fec_support;
    uint32_t pd_link_enabled;
    uint32_t phy_hst_link_enabled;
    uint32_t eth_an_link_enabled;
    sxd_pddr_core_to_phy_state_t core_to_phy_state;
    sxd_pddr_psi_fsm_state_t psi_fsm_state;
    sxd_pddr_cable_proto_cap_ext_t cable_proto_cap_ext;
} sxd_pddr_pddr_operation_info_page_t;

typedef struct sxd_pddr_pddr_monitor_opcode {
    uint16_t monitor_opcode;
} sxd_pddr_pddr_monitor_opcode_t;

typedef struct sxd_pddr_pddr_advanced_opcode {
    uint16_t advanced_opcode;
} sxd_pddr_pddr_advanced_opcode_t;

union pddr_status_opcode {
    sxd_pddr_pddr_monitor_opcode_t pddr_monitor_opcode;
    sxd_pddr_pddr_advanced_opcode_t pddr_advanced_opcode;
};

typedef struct sxd_pddr_pddr_troubleshooting_page {
    sxd_pddr_group_opcode_t group_opcode;
    union pddr_status_opcode status_opcode;
    uint16_t user_feedback_data;
    uint16_t user_feedback_index;
    uint8_t status_message[SXD_PDDR_STATUS_MESSAGE_NUM];
} sxd_pddr_pddr_troubleshooting_page_t;

typedef struct sxd_pddr_pddr_phy_info_page {
    uint8_t remote_device_type;
    uint8_t port_notifications;
    uint16_t num_of_negotiation_attempts;
    uint8_t ib_revision;
    uint8_t lp_ib_revision;
    uint8_t hw_link_phy_state;
    uint16_t phy_manger_disable_mask;
    uint32_t pcs_phy_state;
    uint32_t lp_proto_enabled;
    uint16_t lp_fec_mode_support;
    uint16_t lp_fec_mode_request;
    uint32_t ib_last_link_down_reason;
    uint8_t eth_last_link_down_lane[SXD_PDDR_ETH_LAST_LINK_DOWN_LANE_NUM];
    uint32_t speed_deg_db;
    uint32_t degrade_grade_lane0;
    uint32_t degrade_grade_lane1;
    uint32_t degrade_grade_lane2;
    uint32_t degrade_grade_lane3;
    uint8_t num_of_presets_tested_lane0;
    uint8_t num_of_presets_tested_lane1;
    uint8_t num_of_presets_tested_lane2;
    uint8_t num_of_presets_tested_lane3;
    uint8_t kr_startup_fsm_lane[SXD_PDDR_KR_STARTUP_FSM_LANE_NUM];
    uint32_t eth_an_debug_indication;
    uint8_t rounds_waited_for_peer_to_end_test;
    uint16_t ib_phy_fsm_state_trace;
    uint16_t kr_startup_debug_indications[SXD_PDDR_KR_STARTUP_DEBUG_INDICATIONS_NUM];
    uint8_t tx_tuning_stages_lane0;
    uint8_t tx_tuning_stages_lane1;
    uint8_t tx_tuning_stages_lane2;
    uint8_t tx_tuning_stages_lane3;
    uint8_t irisc_status;
    uint32_t stamping_reason;
    uint32_t kr_frame_lock_tuning_failure_events_count;
    uint32_t kr_full_tuning_failure_count;
    sxd_pddr_ib_debug_indication_t ib_debug_indication;
    sxd_pddr_pm_debug_indication_t pm_debug_indication;
    sxd_pddr_pd_debug_indication_t pd_debug_indication;
    uint8_t psi_collision1;
    uint8_t psi_collision2;
    uint8_t hst_mismatch_reason;
    uint8_t fp_signal_detect_count;
    uint8_t pd_count;
} sxd_pddr_pddr_phy_info_page_t;

typedef struct sxd_pddr_date_code {
    uint32_t hi;
    uint32_t lo;
} sxd_pddr_date_code_t;

typedef struct sxd_pddr_pddr_module_info {
    uint8_t cable_technology;
    uint8_t cable_breakout;
    uint8_t ext_ethernet_compliance_code;
    uint8_t ethernet_compliance_code;
    sxd_pddr_cable_type_t cable_type;
    sxd_pddr_cable_vendor_t cable_vendor;
    uint8_t cable_length;
    uint8_t cable_identifier;
    uint8_t cable_power_class;
    uint8_t max_power;
    uint8_t cable_rx_amp;
    uint8_t cable_rx_emphasis;
    uint8_t cable_tx_equalization;
    uint8_t cable_attenuation_25g;
    uint8_t cable_attenuation_12g;
    uint8_t cable_attenuation_7g;
    uint8_t cable_attenuation_5g;
    uint8_t cable_rx_post_emphasis;
    uint8_t rx_cdr_cap;
    uint8_t tx_cdr_cap;
    uint8_t rx_cdr_state;
    uint8_t tx_cdr_state;
    uint32_t vendor_name[SXD_PDDR_VENDOR_NAME_NUM];
    uint32_t vendor_pn[SXD_PDDR_VENDOR_PN_NUM];
    uint32_t vendor_rev;
    uint32_t fw_version;
    uint32_t vendor_sn[SXD_PDDR_VENDOR_SN_NUM];
    uint16_t temperature;
    uint16_t voltage;
    uint16_t rx_power_lane0;
    uint16_t rx_power_lane1;
    uint16_t rx_power_lane2;
    uint16_t rx_power_lane3;
    uint16_t rx_power_lane4;
    uint16_t rx_power_lane5;
    uint16_t rx_power_lane6;
    uint16_t rx_power_lane7;
    uint16_t tx_power_lane0;
    uint16_t tx_power_lane1;
    uint16_t tx_power_lane2;
    uint16_t tx_power_lane3;
    uint16_t tx_power_lane4;
    uint16_t tx_power_lane5;
    uint16_t tx_power_lane6;
    uint16_t tx_power_lane7;
    uint16_t tx_bias_lane0;
    uint16_t tx_bias_lane1;
    uint16_t tx_bias_lane2;
    uint16_t tx_bias_lane3;
    uint16_t tx_bias_lane4;
    uint16_t tx_bias_lane5;
    uint16_t tx_bias_lane6;
    uint16_t tx_bias_lane7;
    uint16_t temperature_high_th;
    uint16_t temperature_low_th;
    uint16_t voltage_high_th;
    uint16_t voltage_low_th;
    uint16_t rx_power_high_th;
    uint16_t rx_power_low_th;
    uint16_t tx_power_high_th;
    uint16_t tx_power_low_th;
    uint16_t tx_bias_high_th;
    uint16_t tx_bias_low_th;
    sxd_pddr_module_st_t module_st;
    sxd_pddr_rx_power_type_t rx_power_type;
    uint8_t did_cap;
    uint16_t smf_length;
    uint16_t wavelength;
    uint8_t active_set_host_compliance_code;
    uint8_t active_set_media_compliance_code;
    uint8_t ib_compliance_code;
    uint8_t nbr250;
    uint8_t nbr100;
    uint8_t monitor_cap_mask;
    uint8_t ib_width;
    sxd_pddr_dp_st_lane0_t dp_st_lane0;
    uint8_t dp_st_lane1;
    uint8_t dp_st_lane2;
    uint8_t dp_st_lane3;
    uint8_t dp_st_lane4;
    uint8_t dp_st_lane5;
    uint8_t dp_st_lane6;
    uint8_t dp_st_lane7;
    uint8_t length_om2;
    uint8_t length_om3;
    uint8_t length_om4;
    uint8_t length_om5;
    uint8_t length_om1;
    uint16_t wavelength_tolerance;
    uint8_t memory_map_rev;
    uint32_t memory_map_compliance;
    sxd_pddr_date_code_t date_code;
    uint8_t connector_type;
    uint32_t vendor_oui;
    sxd_pddr_tx_input_freq_sync_t tx_input_freq_sync;
    uint8_t rx_input_valid;
    uint8_t rx_output_valid;
    uint16_t max_fiber_length;
    sxd_pddr_error_code_t error_code;
} sxd_pddr_pddr_module_info_t;

typedef struct sxd_pddr_pddr_port_events_page_layout {
    uint8_t invalid_fsm_sv;
    uint16_t invalid_fsm_ps;
    uint8_t kr_false_ready_sv;
    uint8_t kr_false_ready;
    uint8_t mod_req_nack_sv;
    uint8_t mod_req_nack;
    uint8_t mod_req_busy_sv;
    uint8_t mod_req_busy;
    uint8_t mod_config_to_sv;
    uint8_t mod_config_to;
    uint8_t mod_adapt_faild_sv;
    uint8_t mod_adapt_faild;
    uint8_t pm_fifo_full_sv;
    uint8_t pm_fifo_full;
    uint8_t protocol_check_sv;
    uint8_t protocol_check;
    uint8_t input_event_sv;
    uint16_t input_event;
    uint8_t lane_mapping_sv;
    uint8_t lane_mapping;
    uint8_t qsfp_zero_atten_sv;
    uint8_t qsfp_zero_atten;
    uint8_t mono_reach_low_limit_sv;
    uint8_t mono_reach_low_limit;
    uint8_t mono_reach_high_limit_sv;
    uint8_t mono_reach_high_limit;
    uint8_t mono_flow_height_sv;
    uint8_t mono_flow_height;
    uint8_t single_gains_bad_val_sv;
    uint8_t single_gains_bad_val;
    uint8_t init_all_gains_bad_val_sv;
    uint8_t init_all_gains_bad_val;
    uint32_t clr_mask[SXD_PDDR_CLR_MASK_NUM];
} sxd_pddr_pddr_port_events_page_layout_t;

typedef struct sxd_pddr_pddr_device_events_page {
    uint8_t invalid_port_access_sv;
    uint16_t invalid_port_access;
    uint8_t pll_state_sv_1;
    uint8_t pll_state_mask_center1;
    uint8_t pll_state_sv_0;
    uint8_t pll_state_mask_center0;
    uint8_t main_irisc_timeout;
    uint8_t tile_irisc_timeout;
    uint8_t plu_timeout0;
    uint8_t plu_timeout1;
    uint8_t plu_timeout2;
    uint8_t plu_timeout3;
    uint8_t plu_timeout4;
    uint8_t cr_space_timeout_mcm_main;
    uint8_t cr_space_timeout_sv;
    uint8_t cr_space_timeout;
    uint8_t analog_phy_to_sv;
    uint8_t analog_phy_to;
    uint8_t logical_phy_to_sv;
    uint8_t logical_phy_to;
    uint8_t varactors_calib_fail_center1_sv;
    uint8_t varactors_calib_fail_center1;
    uint8_t varactors_calib_fail_center0_sv;
    uint8_t varactors_calib_fail_center0;
    uint8_t irisc_stuck_mask_sv;
    uint32_t irisc_stuck_mask;
    uint8_t pll_lock_sv_1;
    uint8_t pll_unlocl_mask_center1;
    uint8_t pll_lock_sv_0;
    uint8_t pll_unlocl_mask_center0;
    uint8_t uc_stack_overflow;
    uint8_t uc_crspace_timeout;
    uint8_t pwr_governor_err_sv;
    uint8_t pwr_governor_err;
    uint8_t iopl_err_center1_sv;
    uint8_t iopl_err_center1;
    uint8_t iopl_err_center0_sv;
    uint8_t iopl_err_center0;
    uint32_t clr_mask[SXD_PDDR_CLR_MASK_NUM];
    uint32_t main_irisc_address;
    uint32_t main_irisc_ip;
    uint32_t tile_irisc_address;
    uint32_t tile_irisc_ip;
    uint16_t plu_timeout0_address;
    uint16_t plu_timeout1_address;
    uint16_t plu_timeout2_address;
    uint16_t plu_timeout3_address;
    uint16_t plu_timeout4_address;
    uint8_t plu_timeout0_cluster;
    uint8_t plu_timeout1_cluster;
    uint8_t plu_timeout2_cluster;
    uint8_t plu_timeout3_cluster;
    uint8_t plu_timeout4_cluster;
    uint8_t irisc_tile_idx;
    uint8_t uc_crspace_timeout_lane;
    uint8_t uc_crspace_timeout_cl;
    uint8_t uc_stack_overflow_lane;
    uint8_t uc_stack_overflow_cl;
} sxd_pddr_pddr_device_events_page_t;

typedef struct sxd_pddr_pddr_link_down_info_page {
    sxd_pddr_down_blame_t down_blame;
    sxd_pddr_local_reason_opcode_t local_reason_opcode;
    uint8_t remote_reason_opcode;
    uint8_t e2e_reason_opcode;
    uint8_t last_ber_mantissa;
    uint8_t last_ber_exp;
    uint8_t ber_mantissa;
    uint8_t ber_exp;
    uint8_t min_ber_mantissa;
    uint8_t min_ber_exp;
    uint8_t max_ber_mantissa;
    uint8_t max_ber_exp;
    uint16_t num_of_ber_alarams;
    uint32_t time_to_link_down_to_disable;
    uint32_t time_to_link_down_to_rx_loss;
} sxd_pddr_pddr_link_down_info_page_t;

typedef struct sxd_pddr_pddr_link_down_events_page {
    sxd_pddr_ib_port_events_t ib_port_events;
    sxd_pddr_etherent_port_events_t etherent_port_events;
    sxd_pddr_general_port_events_t general_port_events;
} sxd_pddr_pddr_link_down_events_page_t;

typedef struct sxd_pddr_pddr_link_up_info_page {
    uint8_t up_reason_pwr;
    uint8_t up_reason_drv;
    uint8_t up_reason_mng;
    uint32_t time_to_link_up;
    uint8_t fast_link_up_status;
    uint32_t time_to_link_up_phy_up_to_active;
    uint32_t time_to_link_up_sd_to_phy_up;
    uint32_t time_to_link_up_disable_to_sd;
    uint32_t time_to_link_up_disable_to_pd;
} sxd_pddr_pddr_link_up_info_page_t;

typedef struct sxd_pddr_module_latched_flag_info {
    sxd_pddr_temp_flags_t temp_flags;
    sxd_pddr_vcc_flags_t vcc_flags;
    uint8_t mod_fw_fault;
    uint8_t dp_fw_fault;
    uint8_t tx_fault;
    uint8_t tx_los;
    uint8_t tx_cdr_lol;
    uint8_t tx_ad_eq_fault;
    uint8_t tx_power_hi_al;
    uint8_t tx_power_lo_al;
    uint8_t tx_power_hi_war;
    uint8_t tx_power_lo_war;
    uint8_t tx_bias_hi_al;
    uint8_t tx_bias_lo_al;
    uint8_t tx_bias_hi_war;
    uint8_t tx_bias_lo_war;
    uint8_t rx_los;
    uint8_t rx_cdr_lol;
    uint8_t rx_power_hi_al;
    uint8_t rx_power_lo_al;
    uint8_t rx_power_hi_war;
    uint8_t rx_power_lo_war;
    uint8_t rx_input_valid_change;
    uint8_t rx_output_valid_change;
} sxd_pddr_module_latched_flag_info_t;

typedef struct sxd_pddr_pddr_phy_debug_page {
    uint8_t pport;
    uint8_t trigger_active;
    uint8_t trigger_cond_state_event_val;
    uint8_t trigger_cond_state_or_event;
    uint8_t trigger_cond_fsm;
    uint8_t pre_trigger_buff_mode;
    uint8_t tracer_mode;
    uint8_t reset_tracer;
    uint8_t tracer_enable;
    uint32_t fsm_mask;
    uint16_t trigger_ptr;
    uint16_t buffer_size;
    uint16_t ptr_log_data;
    uint16_t ptr_next_write;
    uint32_t buffer_base_address;
} sxd_pddr_pddr_phy_debug_page_t;

typedef struct sxd_pddr_pddr_mng_debug_page {
    sxd_pddr_fw_module_state_t fw_module_state;
    sxd_pddr_fw_dp_state_lane7_t fw_dp_state_lane7;
    uint8_t fw_dp_state_lane6;
    uint8_t fw_dp_state_lane5;
    uint8_t fw_dp_state_lane4;
    uint8_t fw_dp_state_lane3;
    uint8_t fw_dp_state_lane2;
    uint8_t fw_dp_state_lane1;
    uint8_t fw_dp_state_lane0;
    sxd_pddr_dp_req_status_lane7_t dp_req_status_lane7;
    uint8_t dp_req_status_lane6;
    uint8_t dp_req_status_lane5;
    uint8_t dp_req_status_lane4;
    uint8_t dp_req_status_lane3;
    uint8_t dp_req_status_lane2;
    uint8_t dp_req_status_lane1;
    uint8_t dp_req_status_lane0;
    uint8_t dpsm_apply_state_lane7;
    uint8_t dpsm_apply_state_lane6;
    uint8_t dpsm_apply_state_lane5;
    uint8_t dpsm_apply_state_lane4;
    uint8_t dpsm_apply_state_lane3;
    uint8_t dpsm_apply_state_lane2;
    uint8_t dpsm_apply_state_lane1;
    uint8_t dpsm_apply_state_lane0;
} sxd_pddr_pddr_mng_debug_page_t;

typedef struct sxd_pddr_pddr_link_down_info_ext_16nm_lr {
    uint8_t cause_as_detected_not_on_slot;
    uint8_t cause_high_ser;
    uint8_t cause_rs_rx_lane0_symbol_error;
    uint8_t cause_tx_lane_fifo_underrun_l0;
    uint8_t cause_deskew_fifo_overrun;
    uint8_t cause_fec_rx_sync_m_reached_max0;
    uint32_t symbol_error_counter_lo;
    uint32_t symbol_error_counter_hi;
    uint32_t uncorrectable_block_counter_lo;
    uint32_t uncorrectable_block_counter_hi;
    uint8_t link_fail_due_align_loss;
    uint8_t block_lock_mask_at_fail_port1;
    uint8_t block_lock_mask_at_fail_port0;
    uint32_t link_down_counter;
    uint8_t effective_ber_coef;
    uint8_t effective_ber_magnitude;
    uint8_t raw_ber_coef;
    uint8_t raw_ber_magnitude;
} sxd_pddr_pddr_link_down_info_ext_16nm_lr_t;

union pddr_page_data {
    sxd_pddr_pddr_operation_info_page_t pddr_operation_info_page;
    sxd_pddr_pddr_troubleshooting_page_t pddr_troubleshooting_page;
    sxd_pddr_pddr_phy_info_page_t pddr_phy_info_page;
    sxd_pddr_pddr_module_info_t pddr_module_info;
    sxd_pddr_pddr_port_events_page_layout_t pddr_port_events_page_layout;
    sxd_pddr_pddr_device_events_page_t pddr_device_events_page;
    sxd_pddr_pddr_link_down_info_page_t pddr_link_down_info_page;
    sxd_pddr_pddr_link_down_events_page_t pddr_link_down_events_page;
    sxd_pddr_pddr_link_up_info_page_t pddr_link_up_info_page;
    sxd_pddr_module_latched_flag_info_t module_latched_flag_info;
    sxd_pddr_pddr_phy_debug_page_t pddr_phy_debug_page;
    sxd_pddr_pddr_mng_debug_page_t pddr_mng_debug_page;
    sxd_pddr_pddr_link_down_info_ext_16nm_lr_t pddr_link_down_info_ext_16nm_lr;
};

/**
 * ku_pddr_reg structure is used to store the PDDR register parameters
 */
struct ku_pddr_reg {
    uint8_t local_port;
    sxd_pddr_pnat_t pnat;
    uint8_t lp_msb;
    sxd_pddr_port_type_t port_type;
    uint8_t clr;
    sxd_pddr_module_info_ext_t module_info_ext;
    uint8_t dev;
    sxd_pddr_page_select_t page_select;
    union pddr_page_data page_data;
};

/**
 * ku_access_pddr_reg structure is used to store the access register PDDR command parameters
 */
struct ku_access_pddr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pddr_reg      pddr_reg; /**< pddr_reg - pddr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_fmtm_reg structure is used to store the FMTM register parameters
 */
struct ku_fmtm_reg {
    uint8_t emt_index_in;
    uint8_t emt_index_out;
};

/**
 * ku_access_fmtm_reg structure is used to store the access register FMTM command parameters
 */
struct ku_access_fmtm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_fmtm_reg      fmtm_reg; /**< fmtm_reg - fmtm register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_chltm_reg structure is used to store the CHLTM register parameters
 */
struct ku_chltm_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t traffic_class;
    uint8_t hlt_table_pointer;
};

/**
 * ku_access_chltm_reg structure is used to store the access register CHLTM command parameters
 */
struct ku_access_chltm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_chltm_reg     chltm_reg; /**< chltm_reg - chltm register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MAFTI_RECORD_NUM 64

typedef struct sxd_mafti_record {
    uint32_t counter_index;
    uint32_t bytes_inc;
    uint32_t packets_inc;
} sxd_mafti_record_t;

/**
 * ku_mafti_reg structure is used to store the MAFTI register parameters
 */
struct ku_mafti_reg {
    uint8_t num_rec;
    sxd_mafti_record_t record[SXD_MAFTI_RECORD_NUM];
};

/**
 * ku_access_mafti_reg structure is used to store the access register MAFTI command parameters
 */
struct ku_access_mafti_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mafti_reg     mafti_reg; /**< mafti_reg - mafti register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_qteem_reg structure is used to store the QTEEM register parameters
 */
struct ku_qteem_reg {
    uint8_t tqos_profile;
    uint8_t overlay_ecn;
    uint8_t underlay_ecn;
};

/**
 * ku_access_qteem_reg structure is used to store the access register QTEEM command parameters
 */
struct ku_access_qteem_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qteem_reg     qteem_reg; /**< qteem_reg - qteem register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_HMON_WQE_OVERFLOW_RDQ_NUM 64

typedef struct sxd_hmon_wqe_overflow_rdq {
    uint32_t hi;
    uint32_t lo;
} sxd_hmon_wqe_overflow_rdq_t;

/**
 * ku_hmon_reg structure is used to store the HMON register parameters
 */
struct ku_hmon_reg {
    uint8_t clr;
    uint8_t cprdq;
    uint8_t read_type;
    uint8_t crdq;
    uint8_t wqe_of_wrap;
    uint32_t wqe_overflow_high;
    uint32_t wqe_overflow_low;
    sxd_hmon_wqe_overflow_rdq_t wqe_overflow_rdq[SXD_HMON_WQE_OVERFLOW_RDQ_NUM];
};

/**
 * ku_access_hmon_reg structure is used to store the access register HMON command parameters
 */
struct ku_access_hmon_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_hmon_reg      hmon_reg; /**< hmon_reg - hmon register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

typedef struct sxd_mgpir_hw_info {
    uint8_t slot_index;
    uint8_t device_type;
    uint8_t devices_per_flash;
    uint8_t num_of_devices;
    uint8_t first_pluggable_interconnect_offset;
    uint8_t max_modules_per_slot;
    uint8_t num_of_slots;
    uint8_t num_of_modules;
} sxd_mgpir_hw_info_t;

/**
 * ku_mgpir_reg structure is used to store the MGPIR register parameters
 */
struct ku_mgpir_reg {
    sxd_mgpir_hw_info_t hw_info;
};

/**
 * ku_access_mgpir_reg structure is used to store the access register MGPIR command parameters
 */
struct ku_access_mgpir_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mgpir_reg     mgpir_reg; /**< mgpir_reg - mgpir register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_pmtm_module_type {
    SXD_PMTM_MODULE_TYPE_BACKPLANE_WITH_4_LANES_E = 0x0,
    SXD_PMTM_MODULE_TYPE_QSFP_E = 0x1,
    SXD_PMTM_MODULE_TYPE_SFP_E = 0x2,
    SXD_PMTM_MODULE_TYPE_BACKPLANE_WITH_SINGLE_LANE_E = 0x4,
    SXD_PMTM_MODULE_TYPE_BACKPLANE_WITH_TWO_LANES_E = 0x8,
    SXD_PMTM_MODULE_TYPE_CHIP2CHIP4X_E = 0xa,
    SXD_PMTM_MODULE_TYPE_CHIP2CHIP2X_E = 0xb,
    SXD_PMTM_MODULE_TYPE_CHIP2CHIP1X_E = 0xc,
    SXD_PMTM_MODULE_TYPE_QSFP_DD_E = 0xe,
    SXD_PMTM_MODULE_TYPE_OSFP_E = 0xf,
    SXD_PMTM_MODULE_TYPE_SFP_DD_E = 0x10,
    SXD_PMTM_MODULE_TYPE_DSFP_E = 0x11,
    SXD_PMTM_MODULE_TYPE_CHIP2CHIP8X_E = 0x12,
    SXD_PMTM_MODULE_TYPE_TWISTED_PAIR_E = 0x13,
    SXD_PMTM_MODULE_TYPE_MIN = SXD_PMTM_MODULE_TYPE_BACKPLANE_WITH_4_LANES_E,
    SXD_PMTM_MODULE_TYPE_MAX = SXD_PMTM_MODULE_TYPE_TWISTED_PAIR_E
} sxd_pmtm_module_type_t;

/**
 * ku_pmtm_reg structure is used to store the PMTM register parameters
 */
struct ku_pmtm_reg {
    uint8_t slot_index;
    uint8_t module;
    uint8_t module_width;
    sxd_pmtm_module_type_t module_type;
};

/**
 * ku_access_pmtm_reg structure is used to store the access register PMTM command parameters
 */
struct ku_access_pmtm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmtm_reg      pmtm_reg; /**< pmtm_reg - pmtm register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_tnqdr_reg structure is used to store the TNQDR register parameters
 */
struct ku_tnqdr_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t color;
    uint8_t switch_prio;
    uint8_t dscp;
};

/**
 * ku_access_tnqdr_reg structure is used to store the access register TNQDR command parameters
 */
struct ku_access_tnqdr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tnqdr_reg     tnqdr_reg; /**< tnqdr_reg - tnqdr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_sffp_type {
    SXD_SFFP_TYPE_BROADCAST_E = 0x0,
    SXD_SFFP_TYPE_UNKNOWN_UNICAST_E = 0x1,
    SXD_SFFP_TYPE_UNREGISTERED_MULTICAST_IPV4_E = 0x2,
    SXD_SFFP_TYPE_UNREGISTERED_MULTICAST_IPV6_E = 0x3,
    SXD_SFFP_TYPE_RESERVED_E = 0x4,
    SXD_SFFP_TYPE_UNREGISTERED_MULTICAST_NON_IP_E = 0x5,
    SXD_SFFP_TYPE_IPV4_LINK_LOCAL_E = 0x6,
    SXD_SFFP_TYPE_IPV6_ALL_HOSTS_E = 0x7,
    SXD_SFFP_TYPE_MIN = SXD_SFFP_TYPE_BROADCAST_E,
    SXD_SFFP_TYPE_MAX = SXD_SFFP_TYPE_IPV6_ALL_HOSTS_E
} sxd_sffp_type_t;

/**
 * ku_sffp_reg structure is used to store the SFFP register parameters
 */
struct ku_sffp_reg {
    uint8_t profile_id;
    sxd_sffp_type_t type;
    uint8_t flood_offset;
};

/**
 * ku_access_sffp_reg structure is used to store the access register SFFP command parameters
 */
struct ku_access_sffp_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sffp_reg      sffp_reg; /**< sffp_reg - sffp register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_mpcir_reg structure is used to store the MPCIR register parameters
 */
struct ku_mpcir_reg {
    uint8_t all;
    uint8_t gearbox;
    uint8_t leds;
    uint8_t voltage_current;
    uint8_t power;
    uint8_t fans;
    uint8_t thermal;
    uint8_t module_mng;
    uint8_t cpld;
    uint8_t ports;
    uint8_t gearbox_stat;
    uint8_t leds_stat;
    uint8_t voltage_current_stat;
    uint8_t power_stat;
    uint8_t fans_stat;
    uint8_t thermal_stat;
    uint8_t module_mng_stat;
    uint8_t cpld_stat;
    uint8_t ports_stat;
};

/**
 * ku_access_mpcir_reg structure is used to store the access register MPCIR command parameters
 */
struct ku_access_mpcir_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mpcir_reg     mpcir_reg; /**< mpcir_reg - mpcir register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_pmecr_e {
    SXD_PMECR_E_DO_NOT_GENERATE_EVENT_E = 0x0,
    SXD_PMECR_E_GENERATE_EVENT_E = 0x1,
    SXD_PMECR_E_GENERATE_SINGLE_EVENT_E = 0x2,
    SXD_PMECR_E_MIN = SXD_PMECR_E_DO_NOT_GENERATE_EVENT_E,
    SXD_PMECR_E_MAX = SXD_PMECR_E_GENERATE_SINGLE_EVENT_E
} sxd_pmecr_e_t;

/**
 * ku_pmecr_reg structure is used to store the PMECR register parameters
 */
struct ku_pmecr_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t ee;
    uint8_t eswi;
    uint8_t swi;
    sxd_pmecr_e_t e;
};

/**
 * ku_access_pmecr_reg structure is used to store the access register PMECR command parameters
 */
struct ku_access_pmecr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmecr_reg     pmecr_reg; /**< pmecr_reg - pmecr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_pter_error_page {
    SXD_PTER_ERROR_PAGE_INJECTION_OF_PHY_ERRORS_E = 0x0,
    SXD_PTER_ERROR_PAGE_INJECTION_OF_PORT_ERRORS_E = 0x1,
    SXD_PTER_ERROR_PAGE_MIN = SXD_PTER_ERROR_PAGE_INJECTION_OF_PHY_ERRORS_E,
    SXD_PTER_ERROR_PAGE_MAX = SXD_PTER_ERROR_PAGE_INJECTION_OF_PORT_ERRORS_E
} sxd_pter_error_page_t;

typedef struct sxd_pter_pter_phy_page_reg {
    uint8_t error_type_oper;
    uint8_t error_type_cap;
    uint8_t error_type_admin;
    uint16_t error_injection_time;
    uint8_t ber_mantissa;
    uint8_t ber_exp;
    uint16_t rs_symbol_errors;
    uint16_t rs_errors_interval;
} sxd_pter_pter_phy_page_reg_t;

typedef struct sxd_pter_pter_port_page_reg {
    uint8_t error_type_cap;
    uint8_t error_type_admin;
    uint8_t error_count;
} sxd_pter_pter_port_page_reg_t;

union pter_page_data {
    sxd_pter_pter_phy_page_reg_t pter_phy_page_reg;
    sxd_pter_pter_port_page_reg_t pter_port_page_reg;
};

/**
 * ku_pter_reg structure is used to store the PTER register parameters
 */
struct ku_pter_reg {
    sxd_pter_error_page_t error_page;
    uint8_t local_port;
    uint8_t pnat;
    uint8_t lp_msb;
    uint8_t port_type;
    uint8_t status;
    union pter_page_data page_data;
};

/**
 * ku_access_pter_reg structure is used to store the access register PTER command parameters
 */
struct ku_access_pter_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pter_reg      pter_reg; /**< pter_reg - pter register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_sllm_version {
    SXD_SLLM_VERSION_PROD_16NM_E = 0x3,
    SXD_SLLM_VERSION_PROD_7NM_E = 0x4,
    SXD_SLLM_VERSION_PROD_TBD_E = 0x7,
    SXD_SLLM_VERSION_MIN = SXD_SLLM_VERSION_PROD_16NM_E,
    SXD_SLLM_VERSION_MAX = SXD_SLLM_VERSION_PROD_TBD_E
} sxd_sllm_version_t;

typedef struct sxd_sllm_sllm_16nm {
    uint8_t lm_active;
    uint8_t lm_was_active;
    uint8_t pib_gw_lock;
    uint8_t lm_en;
    uint16_t lm_clk90_fl_err_max;
    uint32_t lm_clk90_fl_err_acc;
    uint16_t ib3_max_lm_90_tries;
    uint32_t lm_counter_up;
    uint16_t ib1_max_lm_90_tries;
    uint32_t lm_counter_mid;
    uint32_t lm_counter_dn;
} sxd_sllm_sllm_16nm_t;

typedef struct sxd_sllm_sllm_usr {
    uint8_t enable_lm;
    uint8_t enable_phase_maintenance;
    uint8_t enable_offset_maintenance;
    uint8_t lm_catastrophic_bit;
    uint8_t lm_activation_counter;
    uint8_t lm_fixes_counter;
    uint8_t lane_under_maintenance;
    uint8_t optimal_phase;
    uint8_t link_tuning_error;
    uint32_t lane_correctable_errors;
} sxd_sllm_sllm_usr_t;

typedef struct sxd_sllm_sllm_7nm {
    uint8_t ctle_peq_en;
    uint8_t peq_tsense_en;
    uint8_t peq_f1_adapt_skip;
    uint8_t vref_peq_en;
    uint8_t dffe_peq_scout_skip;
    uint8_t peq_train_mode;
    uint8_t peq_vref_iters;
    uint8_t peq_adc_vref_step;
    uint8_t dffe_peq_en;
    uint8_t peq_dffe_iters;
    uint8_t peq_dffe_delay;
    uint16_t ctle_peq_cnt;
    uint8_t ber_mon_mantissa;
    uint8_t ber_mon_exp;
} sxd_sllm_sllm_7nm_t;

union sllm_page_data {
    sxd_sllm_sllm_16nm_t sllm_16nm;
    sxd_sllm_sllm_usr_t sllm_usr;
    sxd_sllm_sllm_7nm_t sllm_7nm;
};

/**
 * ku_sllm_reg structure is used to store the SLLM register parameters
 */
struct ku_sllm_reg {
    uint8_t status;
    sxd_sllm_version_t version;
    uint8_t local_port;
    uint8_t pnat;
    uint8_t lp_msb;
    uint8_t lane;
    uint8_t port_type;
    uint8_t c_db;
    union sllm_page_data page_data;
};

/**
 * ku_access_sllm_reg structure is used to store the access register SLLM command parameters
 */
struct ku_access_sllm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sllm_reg      sllm_reg; /**< sllm_reg - sllm register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_SMPU_MID_NUM 256

typedef struct sxd_smpu_mid {
    uint16_t mid;
} sxd_smpu_mid_t;

/**
 * ku_smpu_reg structure is used to store the SMPU register parameters
 */
struct ku_smpu_reg {
    uint8_t swid;
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t op;
    uint16_t size;
    sxd_smpu_mid_t mid[SXD_SMPU_MID_NUM];
};

/**
 * ku_access_smpu_reg structure is used to store the access register SMPU command parameters
 */
struct ku_access_smpu_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_smpu_reg      smpu_reg; /**< smpu_reg - smpu register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_cegcr_reg structure is used to store the CEGCR register parameters
 */
struct ku_cegcr_reg {
    uint8_t f2e;
    uint8_t sticky;
    uint16_t max_floating_time;
    uint32_t reference_rate;
    uint32_t elephants_thr;
    uint32_t elephants_max_thr;
    uint32_t mice_thr;
};

/**
 * ku_access_cegcr_reg structure is used to store the access register CEGCR command parameters
 */
struct ku_access_cegcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_cegcr_reg     cegcr_reg; /**< cegcr_reg - cegcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_pmtu_reg structure is used to store the PMTU register parameters
 */
struct ku_pmtu_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t i_e;
    uint8_t itre;
    uint16_t max_mtu;
    uint16_t admin_mtu;
    uint16_t oper_mtu;
};

/**
 * ku_access_pmtu_reg structure is used to store the access register PMTU command parameters
 */
struct ku_access_pmtu_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmtu_reg      pmtu_reg; /**< pmtu_reg - pmtu register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_PMMP_QSFP_CABLE_PROTOCOL_TECHNOLOGY_NUM 3

#define SXD_PMMP_SFP_CABLE_PROTOCOL_TECHNOLOGY_NUM 3

/**
 * ku_pmmp_reg structure is used to store the PMMP register parameters
 */
struct ku_pmmp_reg {
    uint8_t slot_index;
    uint8_t module;
    uint8_t sticky;
    uint16_t eeprom_override_mask;
    uint16_t eeprom_override;
    uint32_t qsfp_cable_protocol_technology[SXD_PMMP_QSFP_CABLE_PROTOCOL_TECHNOLOGY_NUM];
    uint32_t sfp_cable_protocol_technology[SXD_PMMP_SFP_CABLE_PROTOCOL_TECHNOLOGY_NUM];
    uint8_t cable_length;
    uint8_t attenuation_25g;
    uint8_t attenuation_12g;
    uint8_t attenuation_7g;
    uint8_t attenuation_5g;
};

/**
 * ku_access_pmmp_reg structure is used to store the access register PMMP command parameters
 */
struct ku_access_pmmp_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmmp_reg      pmmp_reg; /**< pmmp_reg - pmmp register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_fmep_reg structure is used to store the FMEP register parameters
 */
struct ku_fmep_reg {
    uint8_t global;
    uint8_t local_port;
    uint8_t lp_msb;
    uint16_t ext_mod_parsing;
};

/**
 * ku_access_fmep_reg structure is used to store the access register FMEP command parameters
 */
struct ku_access_fmep_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_fmep_reg      fmep_reg; /**< fmep_reg - fmep register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_pecnrr_reg structure is used to store the PECNRR register parameters
 */
struct ku_pecnrr_reg {
    uint8_t clear;
    uint32_t tcam_trigger_high;
    uint32_t tcam_trigger_low;
    uint32_t tcam_full_lookup_high;
    uint32_t tcam_full_lookup_low;
};

/**
 * ku_access_pecnrr_reg structure is used to store the access register PECNRR command parameters
 */
struct ku_access_pecnrr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pecnrr_reg    pecnrr_reg; /**< pecnrr_reg - pecnrr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_RARLPGT_EGRESS_PORT_NUM 32

#define SXD_RARLPGT_EGRESS_PORT_OR_NUM 32

/**
 * ku_rarlpgt_reg structure is used to store the RARLPGT register parameters
 */
struct ku_rarlpgt_reg {
    uint16_t arlpgt_index;
    uint32_t egress_port[SXD_RARLPGT_EGRESS_PORT_NUM];
    uint32_t egress_port_or[SXD_RARLPGT_EGRESS_PORT_OR_NUM];
};

/**
 * ku_access_rarlpgt_reg structure is used to store the access register RARLPGT command parameters
 */
struct ku_access_rarlpgt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rarlpgt_reg   rarlpgt_reg; /**< rarlpgt_reg - rarlpgt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_fpftt_reg structure is used to store the FPFTT register parameters
 */
struct ku_fpftt_reg {
    uint8_t entry_index;
    uint8_t tran_en;
    uint8_t cur_ph;
    uint16_t next_protocol_value;
    uint8_t next_ph_inner;
    uint8_t next_ph;
};

/**
 * ku_access_fpftt_reg structure is used to store the access register FPFTT command parameters
 */
struct ku_access_fpftt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_fpftt_reg     fpftt_reg; /**< fpftt_reg - fpftt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MDDQ_DEVICE_TYPE_NAME_NUM 8

#define SXD_MDDQ_SLOT_ASCII_NAME_NUM 20


typedef enum sxd_mddq_query_type {
    SXD_MDDQ_QUERY_TYPE_RESERVED_E = 0x0,
    SXD_MDDQ_QUERY_TYPE_SLOT_INFO_E = 0x1,
    SXD_MDDQ_QUERY_TYPE_DEVICE_INFO_E = 0x2,
    SXD_MDDQ_QUERY_TYPE_SLOT_NAME_E = 0x3,
    SXD_MDDQ_QUERY_TYPE_MIN = SXD_MDDQ_QUERY_TYPE_RESERVED_E,
    SXD_MDDQ_QUERY_TYPE_MAX = SXD_MDDQ_QUERY_TYPE_SLOT_NAME_E
} sxd_mddq_query_type_t;

typedef struct sxd_mddq_slot_info {
    uint8_t provisioned;
    uint8_t sr_valid;
    uint8_t lc_ready;
    uint8_t active;
    uint16_t hw_revision;
    uint16_t ini_file_version;
    uint8_t card_type;
} sxd_mddq_slot_info_t;

typedef struct sxd_mddq_device_info {
    uint8_t uses_flash;
    uint8_t flash_owner;
    uint8_t thermal_sd;
    uint8_t lc_pwr_on;
    uint8_t flash_id;
    uint8_t device_index;
    uint16_t fw_major;
    uint16_t device_type;
    uint16_t fw_minor;
    uint16_t fw_sub_minor;
    uint8_t max_cmd_read_size_supp;
    uint8_t max_cmd_write_size_supp;
    uint8_t device_type_name[SXD_MDDQ_DEVICE_TYPE_NAME_NUM];
} sxd_mddq_device_info_t;

typedef struct sxd_mddq_slot_name {
    uint8_t slot_ascii_name[SXD_MDDQ_SLOT_ASCII_NAME_NUM];
} sxd_mddq_slot_name_t;

union mddq_data {
    sxd_mddq_slot_info_t slot_info;
    sxd_mddq_device_info_t device_info;
    sxd_mddq_slot_name_t slot_name;
};

/**
 * ku_mddq_reg structure is used to store the MDDQ register parameters
 */
struct ku_mddq_reg {
    uint8_t sie;
    sxd_mddq_query_type_t query_type;
    uint8_t slot_index;
    uint8_t response_message_sequence;
    uint8_t request_message_sequence;
    uint8_t data_valid;
    uint8_t query_index;
    union mddq_data data;
};

/**
 * ku_access_mddq_reg structure is used to store the access register MDDQ command parameters
 */
struct ku_access_mddq_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mddq_reg      mddq_reg; /**< mddq_reg - mddq register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_tnpc_tunnel_port {
    SXD_TNPC_TUNNEL_PORT_NVE_E = 0x0,
    SXD_TNPC_TUNNEL_PORT_VPLS_E = 0x1,
    SXD_TNPC_TUNNEL_PORT_FLEX_TUNNEL0_E = 0x2,
    SXD_TNPC_TUNNEL_PORT_FLEX_TUNNEL1_E = 0x3,
    SXD_TNPC_TUNNEL_PORT_MIN = SXD_TNPC_TUNNEL_PORT_NVE_E,
    SXD_TNPC_TUNNEL_PORT_MAX = SXD_TNPC_TUNNEL_PORT_FLEX_TUNNEL1_E
} sxd_tnpc_tunnel_port_t;

/**
 * ku_tnpc_reg structure is used to store the TNPC register parameters
 */
struct ku_tnpc_reg {
    sxd_tnpc_tunnel_port_t tunnel_port;
    uint8_t learn_enable_v4;
    uint32_t lb_tx_uc_tunnel_port;
    uint32_t lb_tx_mc_tunnel_port;
};

/**
 * ku_access_tnpc_reg structure is used to store the access register TNPC command parameters
 */
struct ku_access_tnpc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tnpc_reg      tnpc_reg; /**< tnpc_reg - tnpc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_pecnre_reg structure is used to store the PECNRE register parameters
 */
struct ku_pecnre_reg {
    uint16_t region_id;
    uint16_t region_id_mask;
};

/**
 * ku_access_pecnre_reg structure is used to store the access register PECNRE command parameters
 */
struct ku_access_pecnre_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pecnre_reg    pecnre_reg; /**< pecnre_reg - pecnre register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_mofs_reg structure is used to store the MOFS register parameters
 */
struct ku_mofs_reg {
    uint8_t type;
    uint16_t register_id;
    uint8_t section_id;
    uint8_t en;
    uint8_t action;
    uint8_t reg_status;
};

/**
 * ku_access_mofs_reg structure is used to store the access register MOFS command parameters
 */
struct ku_access_mofs_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mofs_reg      mofs_reg; /**< mofs_reg - mofs register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_sltp_ob_bad_stat {
    SXD_SLTP_OB_BAD_STAT_CONFIGURATION_WARNING_E = 0x0,
    SXD_SLTP_OB_BAD_STAT_ILLEGAL_OB_COMBINATION_E = 0xb,
    SXD_SLTP_OB_BAD_STAT_ILLEGAL_OB_M2LP_E = 0xc,
    SXD_SLTP_OB_BAD_STAT_ILLEGAL_OB_AMP_E = 0xd,
    SXD_SLTP_OB_BAD_STAT_ILLEGAL_OB_ALEV_OUT_E = 0xe,
    SXD_SLTP_OB_BAD_STAT_ILLEGAL_TAPS_E = 0xf,
    SXD_SLTP_OB_BAD_STAT_MIN = SXD_SLTP_OB_BAD_STAT_CONFIGURATION_WARNING_E,
    SXD_SLTP_OB_BAD_STAT_MAX = SXD_SLTP_OB_BAD_STAT_ILLEGAL_TAPS_E
} sxd_sltp_ob_bad_stat_t;


typedef enum sxd_sltp_version {
    SXD_SLTP_VERSION_PROD_40NM_E = 0x0,
    SXD_SLTP_VERSION_PROD_28NM_E = 0x1,
    SXD_SLTP_VERSION_PROD_16NM_E = 0x3,
    SXD_SLTP_VERSION_PROD_7NM_E = 0x4,
    SXD_SLTP_VERSION_PROD_LUT_7NM_E = 0x7,
    SXD_SLTP_VERSION_MIN = SXD_SLTP_VERSION_PROD_40NM_E,
    SXD_SLTP_VERSION_MAX = SXD_SLTP_VERSION_PROD_LUT_7NM_E
} sxd_sltp_version_t;

typedef struct sxd_sltp_sltp_28nm_40nm {
    uint8_t polarity;
    uint8_t ob_tap0;
    uint8_t ob_tap1;
    uint8_t ob_tap2;
    uint8_t ob_leva;
    uint8_t ob_preemp_mode;
    uint8_t ob_reg;
    uint8_t ob_bias;
    uint8_t ob_norm;
    uint8_t ob_bad_stat;
} sxd_sltp_sltp_28nm_40nm_t;

typedef struct sxd_sltp_sltp_16nm {
    uint8_t pre_2_tap;
    uint8_t pre_tap;
    uint8_t main_tap;
    uint8_t post_tap;
    uint8_t ob_m2lp;
    uint8_t ob_amp;
    uint8_t ob_alev_out;
    sxd_sltp_ob_bad_stat_t ob_bad_stat;
} sxd_sltp_sltp_16nm_t;

typedef struct sxd_sltp_sltp_7nm {
    uint8_t drv_amp;
    sxd_sltp_ob_bad_stat_t ob_bad_stat;
    uint8_t fir_pre3;
    uint8_t fir_pre2;
    uint8_t fir_pre1;
    uint8_t fir_main;
    uint8_t fir_post1;
} sxd_sltp_sltp_7nm_t;

typedef struct sxd_sltp_sltp_lut_7nm {
    uint8_t drv_amp;
    sxd_sltp_ob_bad_stat_t ob_bad_stat;
    uint8_t fir_pre3;
    uint8_t fir_pre2;
    uint8_t lut3;
    uint8_t lut2;
    uint8_t lut1;
    uint8_t lut0;
    uint8_t lut7;
    uint8_t lut6;
    uint8_t lut5;
    uint8_t lut4;
    uint8_t lut11;
    uint8_t lut10;
    uint8_t lut9;
    uint8_t lut8;
    uint8_t lut15;
    uint8_t lut14;
    uint8_t lut13;
    uint8_t lut12;
    uint8_t lut19;
    uint8_t lut18;
    uint8_t lut17;
    uint8_t lut16;
    uint8_t lut23;
    uint8_t lut22;
    uint8_t lut21;
    uint8_t lut20;
    uint8_t lut27;
    uint8_t lut26;
    uint8_t lut25;
    uint8_t lut24;
    uint8_t lut31;
    uint8_t lut30;
    uint8_t lut29;
    uint8_t lut28;
    uint8_t lut35;
    uint8_t lut34;
    uint8_t lut33;
    uint8_t lut32;
    uint8_t lut39;
    uint8_t lut38;
    uint8_t lut37;
    uint8_t lut36;
    uint8_t lut43;
    uint8_t lut42;
    uint8_t lut41;
    uint8_t lut40;
    uint8_t lut47;
    uint8_t lut46;
    uint8_t lut45;
    uint8_t lut44;
    uint8_t lut51;
    uint8_t lut50;
    uint8_t lut49;
    uint8_t lut48;
    uint8_t lut55;
    uint8_t lut54;
    uint8_t lut53;
    uint8_t lut52;
    uint8_t lut59;
    uint8_t lut58;
    uint8_t lut57;
    uint8_t lut56;
    uint8_t lut63;
    uint8_t lut62;
    uint8_t lut61;
    uint8_t lut60;
} sxd_sltp_sltp_lut_7nm_t;

union sltp_page_data {
    sxd_sltp_sltp_28nm_40nm_t sltp_28nm_40nm;
    sxd_sltp_sltp_16nm_t sltp_16nm;
    sxd_sltp_sltp_7nm_t sltp_7nm;
    sxd_sltp_sltp_lut_7nm_t sltp_lut_7nm;
};

/**
 * ku_sltp_reg structure is used to store the SLTP register parameters
 */
struct ku_sltp_reg {
    uint8_t status;
    sxd_sltp_version_t version;
    uint8_t local_port;
    uint8_t pnat;
    uint8_t tx_policy;
    uint8_t conf_mod;
    uint8_t lane;
    uint8_t lane_speed;
    uint8_t port_type;
    uint8_t c_db;
    union sltp_page_data page_data;
};

/**
 * ku_access_sltp_reg structure is used to store the access register SLTP command parameters
 */
struct ku_access_sltp_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sltp_reg      sltp_reg; /**< sltp_reg - sltp register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_ralcm_reg structure is used to store the RALCM register parameters
 */
struct ku_ralcm_reg {
    uint16_t virtual_router;
    uint8_t protocol;
};

/**
 * ku_access_ralcm_reg structure is used to store the access register RALCM command parameters
 */
struct ku_access_ralcm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ralcm_reg     ralcm_reg; /**< ralcm_reg - ralcm register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_PPHCR_BIN_RANGE_NUM 16


typedef enum sxd_pphcr_pnat {
    SXD_PPHCR_PNAT_LOCAL_PORT_NUMBER_E = 0x0,
    SXD_PPHCR_PNAT_IB_PORT_NUMBER_E = 0x1,
    SXD_PPHCR_PNAT_MIN = SXD_PPHCR_PNAT_LOCAL_PORT_NUMBER_E,
    SXD_PPHCR_PNAT_MAX = SXD_PPHCR_PNAT_IB_PORT_NUMBER_E
} sxd_pphcr_pnat_t;

typedef struct sxd_pphcr_bin_range {
    uint8_t high_val;
    uint8_t low_val;
} sxd_pphcr_bin_range_t;

/**
 * ku_pphcr_reg structure is used to store the PPHCR register parameters
 */
struct ku_pphcr_reg {
    uint8_t active_hist_type;
    uint8_t local_port;
    sxd_pphcr_pnat_t pnat;
    uint8_t lp_msb;
    uint8_t we;
    uint8_t num_of_bins;
    uint8_t hist_type;
    uint8_t hist_max_measurement;
    uint8_t hist_min_measurement;
    uint16_t bin_range_write_mask;
    sxd_pphcr_bin_range_t bin_range[SXD_PPHCR_BIN_RANGE_NUM];
};

/**
 * ku_access_pphcr_reg structure is used to store the access register PPHCR command parameters
 */
struct ku_access_pphcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pphcr_reg     pphcr_reg; /**< pphcr_reg - pphcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MTWE_SENSOR_WARNING_NUM 4

/**
 * ku_mtwe_reg structure is used to store the MTWE register parameters
 */
struct ku_mtwe_reg {
    uint32_t sensor_warning[SXD_MTWE_SENSOR_WARNING_NUM];
};

/**
 * ku_access_mtwe_reg structure is used to store the access register MTWE command parameters
 */
struct ku_access_mtwe_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mtwe_reg      mtwe_reg; /**< mtwe_reg - mtwe register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MGIR_MANUFACTURING_BASE_MAC_NUM 6

#define SXD_MGIR_PSID_NUM 16

#define SXD_MGIR_DEV_BRANCH_TAG_NUM 28

typedef struct sxd_mgir_hw_info {
    uint16_t device_hw_revision;
    uint16_t device_id;
    uint8_t num_ports;
    uint8_t technology;
    uint8_t pvs;
    uint16_t hw_dev_id;
    uint8_t manufacturing_base_mac[SXD_MGIR_MANUFACTURING_BASE_MAC_NUM];
    uint32_t uptime;
} sxd_mgir_hw_info_t;

typedef struct sxd_mgir_fw_info {
    uint8_t string_tlv;
    uint8_t dev;
    uint8_t debug;
    uint8_t signed_fw;
    uint8_t secured;
    uint8_t major;
    uint8_t minor;
    uint8_t sub_minor;
    uint32_t build_id;
    uint8_t month;
    uint8_t day;
    uint16_t year;
    uint16_t hour;
    uint8_t psid[SXD_MGIR_PSID_NUM];
    uint32_t ini_file_version;
    uint32_t extended_major;
    uint32_t extended_minor;
    uint32_t extended_sub_minor;
    uint16_t disabled_tiles_bitmap;
    uint16_t isfu_major;
    uint8_t encryption;
    uint8_t sec_boot;
    uint8_t life_cycle;
} sxd_mgir_fw_info_t;

typedef struct sxd_mgir_rom0_version {
    uint8_t major;
    uint8_t minor;
    uint16_t build;
} sxd_mgir_rom0_version_t;

typedef struct sxd_mgir_rom1_version {
    uint8_t major;
    uint8_t minor;
    uint16_t build;
} sxd_mgir_rom1_version_t;

typedef struct sxd_mgir_rom2_version {
    uint8_t major;
    uint8_t minor;
    uint16_t build;
} sxd_mgir_rom2_version_t;

typedef struct sxd_mgir_rom3_version {
    uint8_t major;
    uint8_t minor;
    uint16_t build;
} sxd_mgir_rom3_version_t;

typedef struct sxd_mgir_sw_info {
    uint8_t major;
    uint8_t minor;
    uint8_t sub_minor;
    uint8_t rom0_arch;
    uint8_t rom0_type;
    uint8_t rom1_arch;
    uint8_t rom1_type;
    uint8_t rom2_arch;
    uint8_t rom2_type;
    uint8_t rom3_arch;
    uint8_t rom3_type;
    sxd_mgir_rom0_version_t rom0_version;
    sxd_mgir_rom1_version_t rom1_version;
    sxd_mgir_rom2_version_t rom2_version;
    sxd_mgir_rom3_version_t rom3_version;
} sxd_mgir_sw_info_t;

typedef struct sxd_mgir_dev_info {
    uint8_t dev_branch_tag[SXD_MGIR_DEV_BRANCH_TAG_NUM];
} sxd_mgir_dev_info_t;

/**
 * ku_mgir_reg structure is used to store the MGIR register parameters
 */
struct ku_mgir_reg {
    sxd_mgir_hw_info_t hw_info;
    sxd_mgir_fw_info_t fw_info;
    sxd_mgir_sw_info_t sw_info;
    sxd_mgir_dev_info_t dev_info;
};

/**
 * ku_access_mgir_reg structure is used to store the access register MGIR command parameters
 */
struct ku_access_mgir_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mgir_reg      mgir_reg; /**< mgir_reg - mgir register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_modcr_reg structure is used to store the MODCR register parameters
 */
struct ku_modcr_reg {
    uint8_t clear;
    uint32_t fatal_asserts;
    uint32_t normal_asserts;
    uint32_t debug_asserts;
};

/**
 * ku_access_modcr_reg structure is used to store the access register MODCR command parameters
 */
struct ku_access_modcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_modcr_reg     modcr_reg; /**< modcr_reg - modcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_tidem_reg structure is used to store the TIDEM register parameters
 */
struct ku_tidem_reg {
    uint8_t underlay_ecn;
    uint8_t overlay_ecn;
    uint8_t eip_ecn;
    uint8_t trap_en;
    uint16_t trap_id;
};

/**
 * ku_access_tidem_reg structure is used to store the access register TIDEM command parameters
 */
struct ku_access_tidem_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tidem_reg     tidem_reg; /**< tidem_reg - tidem register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_tigcr_reg structure is used to store the TIGCR register parameters
 */
struct ku_tigcr_reg {
    uint8_t ipip_ttlc;
    uint8_t ipip_ttl_uc;
    uint8_t ipip_flc;
    uint8_t ipip_flh;
    uint16_t ipip_fl_prefix;
    uint8_t ipip_fl_suffix;
    uint32_t ipip_gre_key_for_hash;
};

/**
 * ku_access_tigcr_reg structure is used to store the access register TIGCR command parameters
 */
struct ku_access_tigcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tigcr_reg     tigcr_reg; /**< tigcr_reg - tigcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_mocmi_reg structure is used to store the MOCMI register parameters
 */
struct ku_mocmi_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint16_t cond_nelp;
    uint16_t cond_elp;
};

/**
 * ku_access_mocmi_reg structure is used to store the access register MOCMI command parameters
 */
struct ku_access_mocmi_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mocmi_reg     mocmi_reg; /**< mocmi_reg - mocmi register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_RLCMLD_DIP_NUM 4

#define SXD_RLCMLD_DIP_MASK_NUM 4

/**
 * ku_rlcmld_reg structure is used to store the RLCMLD register parameters
 */
struct ku_rlcmld_reg {
    uint8_t select;
    uint8_t filter_fields;
    uint8_t m_idx;
    uint8_t protocol;
    uint16_t virtual_router;
    uint32_t dip[SXD_RLCMLD_DIP_NUM];
    uint32_t dip_mask[SXD_RLCMLD_DIP_MASK_NUM];
};

/**
 * ku_access_rlcmld_reg structure is used to store the access register RLCMLD command parameters
 */
struct ku_access_rlcmld_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rlcmld_reg    rlcmld_reg; /**< rlcmld_reg - rlcmld register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_CEER_DMAC_NUM 6

#define SXD_CEER_SMAC_NUM 6

#define SXD_CEER_SIP_NUM 4

#define SXD_CEER_DIP_NUM 4

#define SXD_CEER_INNER_DMAC_NUM 6

#define SXD_CEER_INNER_SMAC_NUM 6

#define SXD_CEER_INNER_SIP_NUM 4

#define SXD_CEER_INNER_DIP_NUM 4


typedef enum sxd_ceer_inner_l3_type {
    SXD_CEER_INNER_L3_TYPE_IPV4_E = 0x0,
    SXD_CEER_INNER_L3_TYPE_OTHER_E = 0x1,
    SXD_CEER_INNER_L3_TYPE_MIN = SXD_CEER_INNER_L3_TYPE_IPV4_E,
    SXD_CEER_INNER_L3_TYPE_MAX = SXD_CEER_INNER_L3_TYPE_OTHER_E
} sxd_ceer_inner_l3_type_t;


typedef enum sxd_ceer_l2_type {
    SXD_CEER_L2_TYPE_NO_ETH_E = 0x0,
    SXD_CEER_L2_TYPE_ETH_E = 0x1,
    SXD_CEER_L2_TYPE_MIN = SXD_CEER_L2_TYPE_NO_ETH_E,
    SXD_CEER_L2_TYPE_MAX = SXD_CEER_L2_TYPE_ETH_E
} sxd_ceer_l2_type_t;


typedef enum sxd_ceer_extra_data_type {
    SXD_CEER_EXTRA_DATA_TYPE_NONE_E = 0x0,
    SXD_CEER_EXTRA_DATA_TYPE_TUNNEL_E = 0x1,
    SXD_CEER_EXTRA_DATA_TYPE_MPLS_E = 0x2,
    SXD_CEER_EXTRA_DATA_TYPE_MIN = SXD_CEER_EXTRA_DATA_TYPE_NONE_E,
    SXD_CEER_EXTRA_DATA_TYPE_MAX = SXD_CEER_EXTRA_DATA_TYPE_MPLS_E
} sxd_ceer_extra_data_type_t;


typedef enum sxd_ceer_tunnel_type {
    SXD_CEER_TUNNEL_TYPE_NO_TUNNEL_E = 0x0,
    SXD_CEER_TUNNEL_TYPE_VXLAN_E = 0x1,
    SXD_CEER_TUNNEL_TYPE_NVGRE_E = 0x2,
    SXD_CEER_TUNNEL_TYPE_IP_IN_IP_E = 0x3,
    SXD_CEER_TUNNEL_TYPE_IP_IN_GRE_IN_IP_E = 0x4,
    SXD_CEER_TUNNEL_TYPE_MPLS_E = 0x5,
    SXD_CEER_TUNNEL_TYPE_MIN = SXD_CEER_TUNNEL_TYPE_NO_TUNNEL_E,
    SXD_CEER_TUNNEL_TYPE_MAX = SXD_CEER_TUNNEL_TYPE_MPLS_E
} sxd_ceer_tunnel_type_t;


typedef enum sxd_ceer_l4_type {
    SXD_CEER_L4_TYPE_TCP_E = 0x0,
    SXD_CEER_L4_TYPE_UDP_E = 0x1,
    SXD_CEER_L4_TYPE_ICMP_E = 0x2,
    SXD_CEER_L4_TYPE_IGMP_E = 0x3,
    SXD_CEER_L4_TYPE_BTH_E = 0x4,
    SXD_CEER_L4_TYPE_BTH_OVER_UDP_E = 0x5,
    SXD_CEER_L4_TYPE_AH_E = 0x6,
    SXD_CEER_L4_TYPE_ESP_E = 0x7,
    SXD_CEER_L4_TYPE_UNKNOWN_E = 0xf,
    SXD_CEER_L4_TYPE_MIN = SXD_CEER_L4_TYPE_TCP_E,
    SXD_CEER_L4_TYPE_MAX = SXD_CEER_L4_TYPE_UNKNOWN_E
} sxd_ceer_l4_type_t;


typedef enum sxd_ceer_l3_type {
    SXD_CEER_L3_TYPE_IPV4_E = 0x0,
    SXD_CEER_L3_TYPE_IPV6_E = 0x1,
    SXD_CEER_L3_TYPE_GRH_E = 0x2,
    SXD_CEER_L3_TYPE_FIBERCHANNEL_E = 0x3,
    SXD_CEER_L3_TYPE_UNKNOWN_E = 0xf,
    SXD_CEER_L3_TYPE_MIN = SXD_CEER_L3_TYPE_IPV4_E,
    SXD_CEER_L3_TYPE_MAX = SXD_CEER_L3_TYPE_UNKNOWN_E
} sxd_ceer_l3_type_t;


typedef enum sxd_ceer_vlan_type {
    SXD_CEER_VLAN_TYPE_NO_TAG_E = 0x0,
    SXD_CEER_VLAN_TYPE_PRIO_TAG_E = 0x1,
    SXD_CEER_VLAN_TYPE_VLAN_TAG_E = 0x2,
    SXD_CEER_VLAN_TYPE_QINQ_E = 0x3,
    SXD_CEER_VLAN_TYPE_MIN = SXD_CEER_VLAN_TYPE_NO_TAG_E,
    SXD_CEER_VLAN_TYPE_MAX = SXD_CEER_VLAN_TYPE_QINQ_E
} sxd_ceer_vlan_type_t;

typedef struct sxd_ceer_ceer_extra_fields {
    uint32_t vni;
    uint8_t inner_dmac[SXD_CEER_INNER_DMAC_NUM];
    uint8_t inner_smac[SXD_CEER_INNER_SMAC_NUM];
    sxd_ceer_inner_l3_type_t inner_l3_type;
    uint8_t inner_dscp;
    uint8_t inner_ecn;
    uint8_t inner_ttl;
    uint8_t inner_dont_frag;
    uint32_t inner_sip[SXD_CEER_INNER_SIP_NUM];
    uint32_t inner_dip[SXD_CEER_INNER_DIP_NUM];
} sxd_ceer_ceer_extra_fields_t;

typedef struct sxd_ceer_ceer_extra_fields_MPLS {
    uint8_t mpls_bos;
    uint8_t mpls_exp;
    uint8_t mpls_lb0_v;
    uint32_t mpls_label0_label_id;
    uint8_t mpls_label0_ttl;
    uint8_t mpls_lb1_v;
    uint32_t mpls_label1_label_id;
    uint8_t mpls_label1_ttl;
    uint8_t mpls_lb2_v;
    uint32_t mpls_label2_label_id;
    uint8_t mpls_label2_ttl;
    uint8_t mpls_lb3_v;
    uint32_t mpls_label3_label_id;
    uint8_t mpls_label3_ttl;
    uint8_t mpls_lb4_v;
    uint32_t mpls_label4_label_id;
    uint8_t mpls_label4_ttl;
} sxd_ceer_ceer_extra_fields_MPLS_t;

typedef struct sxd_ceer_ceer_extra_fields_NONE {
    uint32_t reserved;
} sxd_ceer_ceer_extra_fields_NONE_t;

union ceer_extra_data {
    sxd_ceer_ceer_extra_fields_t ceer_extra_fields;
    sxd_ceer_ceer_extra_fields_MPLS_t ceer_extra_fields_MPLS;
    sxd_ceer_ceer_extra_fields_NONE_t ceer_extra_fields_NONE;
};

/**
 * ku_ceer_reg structure is used to store the CEER register parameters
 */
struct ku_ceer_reg {
    uint8_t clear;
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t detection_entry;
    uint8_t det;
    sxd_ceer_l2_type_t l2_type;
    sxd_ceer_extra_data_type_t extra_data_type;
    sxd_ceer_tunnel_type_t tunnel_type;
    sxd_ceer_l4_type_t l4_type;
    sxd_ceer_l3_type_t l3_type;
    sxd_ceer_vlan_type_t vlan_type;
    uint8_t hash_valid;
    uint16_t lag_hash;
    uint16_t router_hash;
    uint8_t dmac[SXD_CEER_DMAC_NUM];
    uint8_t smac[SXD_CEER_SMAC_NUM];
    uint8_t pcp;
    uint8_t dei;
    uint16_t vid;
    uint8_t inner_pcp;
    uint8_t inner_dei;
    uint16_t inner_vid;
    uint8_t dscp;
    uint8_t ecn;
    uint8_t ttl;
    uint8_t dont_frag;
    uint16_t sport;
    uint16_t dport;
    uint32_t sip[SXD_CEER_SIP_NUM];
    uint32_t dip[SXD_CEER_DIP_NUM];
    union ceer_extra_data extra_data;
};

/**
 * ku_access_ceer_reg structure is used to store the access register CEER command parameters
 */
struct ku_access_ceer_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ceer_reg      ceer_reg; /**< ceer_reg - ceer register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_pmtdb_reg structure is used to store the PMTDB register parameters
 */
struct ku_pmtdb_reg {
    uint8_t slot_index;
    uint8_t module;
    uint8_t ports_width;
    uint8_t num_ports;
    uint8_t status;
    uint16_t port_num1;
    uint16_t port_num2;
    uint16_t port_num3;
    uint16_t port_num4;
    uint16_t port_num5;
    uint16_t port_num6;
    uint16_t port_num7;
    uint16_t port_num8;
};

/**
 * ku_access_pmtdb_reg structure is used to store the access register PMTDB command parameters
 */
struct ku_access_pmtdb_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmtdb_reg     pmtdb_reg; /**< pmtdb_reg - pmtdb register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_ibfmrc_reg structure is used to store the IBFMRC register parameters
 */
struct ku_ibfmrc_reg {
    uint32_t attr_id_en;
};

/**
 * ku_access_ibfmrc_reg structure is used to store the access register IBFMRC command parameters
 */
struct ku_access_ibfmrc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ibfmrc_reg    ibfmrc_reg; /**< ibfmrc_reg - ibfmrc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_TNIFR_V2_PORT_FILTER_NUM 32

#define SXD_TNIFR_V2_PORT_FILTER_UPDATE_EN_NUM 32

/**
 * ku_tnifr_v2_reg structure is used to store the TNIFR_V2 register parameters
 */
struct ku_tnifr_v2_reg {
    uint8_t table_id;
    uint8_t tunnel_port;
    uint32_t port_filter[SXD_TNIFR_V2_PORT_FILTER_NUM];
    uint32_t port_filter_update_en[SXD_TNIFR_V2_PORT_FILTER_UPDATE_EN_NUM];
};

/**
 * ku_access_tnifr_v2_reg structure is used to store the access register TNIFR_V2 command parameters
 */
struct ku_access_tnifr_v2_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tnifr_v2_reg  tnifr_v2_reg; /**< tnifr_v2_reg - tnifr_v2 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_SMID_V2_PORT_NUM 32

#define SXD_SMID_V2_MASK_NUM 32


typedef enum sxd_smid_v2_op {
    SXD_SMID_V2_OP_UPDATE_E = 0x0,
    SXD_SMID_V2_OP_WRITE_E = 0x1,
    SXD_SMID_V2_OP_MIN = SXD_SMID_V2_OP_UPDATE_E,
    SXD_SMID_V2_OP_MAX = SXD_SMID_V2_OP_WRITE_E
} sxd_smid_v2_op_t;

/**
 * ku_smid_v2_reg structure is used to store the SMID_V2 register parameters
 */
struct ku_smid_v2_reg {
    uint8_t swid;
    uint16_t mid;
    sxd_smid_v2_op_t op;
    uint8_t smpe_valid;
    uint16_t smpe;
    uint32_t port[SXD_SMID_V2_PORT_NUM];
    uint32_t mask[SXD_SMID_V2_MASK_NUM];
};

/**
 * ku_access_smid_v2_reg structure is used to store the access register SMID_V2 command parameters
 */
struct ku_access_smid_v2_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_smid_v2_reg   smid_v2_reg; /**< smid_v2_reg - smid_v2 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_xralta_reg structure is used to store the XRALTA register parameters
 */
struct ku_xralta_reg {
    uint8_t op;
    uint8_t protocol;
    uint8_t tree_id;
};

/**
 * ku_access_xralta_reg structure is used to store the access register XRALTA command parameters
 */
struct ku_access_xralta_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_xralta_reg    xralta_reg; /**< xralta_reg - xralta register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_mpagr_mngr_type {
    SXD_MPAGR_MNGR_TYPE_HYPERVISOR_E = 0x0,
    SXD_MPAGR_MNGR_TYPE_LNM_E = 0x1,
    SXD_MPAGR_MNGR_TYPE_MIN = SXD_MPAGR_MNGR_TYPE_HYPERVISOR_E,
    SXD_MPAGR_MNGR_TYPE_MAX = SXD_MPAGR_MNGR_TYPE_LNM_E
} sxd_mpagr_mngr_type_t;

/**
 * ku_mpagr_reg structure is used to store the MPAGR register parameters
 */
struct ku_mpagr_reg {
    uint8_t swid;
    sxd_mpagr_mngr_type_t mngr_type;
    uint8_t trigger;
    uint8_t enable;
    uint8_t pa_id;
    uint32_t probability_rate;
};

/**
 * ku_access_mpagr_reg structure is used to store the access register MPAGR command parameters
 */
struct ku_access_mpagr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mpagr_reg     mpagr_reg; /**< mpagr_reg - mpagr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_xltq_reg structure is used to store the XLTQ register parameters
 */
struct ku_xltq_reg {
    uint16_t xm_device_id;
    uint32_t xlt_cap_mask0;
    uint32_t cap_xlt_entries;
    uint32_t cap_xlt_mtable;
    uint32_t cap_xlt_shspm_max_trees;
};

/**
 * ku_access_xltq_reg structure is used to store the access register XLTQ command parameters
 */
struct ku_access_xltq_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_xltq_reg      xltq_reg; /**< xltq_reg - xltq register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_PPCNT_HIST_NUM 16


typedef enum sxd_ppcnt_pnat {
    SXD_PPCNT_PNAT_LOCAL_PORT_NUMBER_E = 0x0,
    SXD_PPCNT_PNAT_IB_PORT_NUMBER_E = 0x1,
    SXD_PPCNT_PNAT_HOST_PORT_NUMBER_E = 0x2,
    SXD_PPCNT_PNAT_OOB_PORT_NUMBER_E = 0x3,
    SXD_PPCNT_PNAT_MIN = SXD_PPCNT_PNAT_LOCAL_PORT_NUMBER_E,
    SXD_PPCNT_PNAT_MAX = SXD_PPCNT_PNAT_OOB_PORT_NUMBER_E
} sxd_ppcnt_pnat_t;


typedef enum sxd_ppcnt_grp {
    SXD_PPCNT_GRP_IEEE_802_3_COUNTERS_E = 0x0,
    SXD_PPCNT_GRP_RFC_2863_COUNTERS_E = 0x1,
    SXD_PPCNT_GRP_RFC_2819_COUNTERS_E = 0x2,
    SXD_PPCNT_GRP_RFC_3635_COUNTERS_E = 0x3,
    SXD_PPCNT_GRP_ETHERNET_EXTENDED_COUNTERS_E = 0x5,
    SXD_PPCNT_GRP_ETHERNET_DISCARD_COUNTERS_E = 0x6,
    SXD_PPCNT_GRP_LINK_LEVEL_RETRANSMISSION_COUNTERS_E = 0x8,
    SXD_PPCNT_GRP_PER_PRIORITY_COUNTERS_E = 0x10,
    SXD_PPCNT_GRP_PER_TRAFFIC_CLASS_COUNTERS_E = 0x11,
    SXD_PPCNT_GRP_PHYSICAL_LAYER_COUNTERS_E = 0x12,
    SXD_PPCNT_GRP_PER_TRAFFIC_CLASS_CONGESTION_COUNTERS_E = 0x13,
    SXD_PPCNT_GRP_PER_RECEIVE_BUFFER_COUNTERS_E = 0x15,
    SXD_PPCNT_GRP_PHYSICAL_LAYER_STATISTICAL_COUNTERS_E = 0x16,
    SXD_PPCNT_GRP_OUT_OF_BAND_PORT_COUNTERS_E = 0x19,
    SXD_PPCNT_GRP_INFINIBAND_PORT_COUNTERS_E = 0x20,
    SXD_PPCNT_GRP_INFINIBAND_EXTENDED_PORT_COUNTERS_E = 0x21,
    SXD_PPCNT_GRP_PLR_COUNTERS_GROUP_E = 0x22,
    SXD_PPCNT_GRP_RS_FEC_HISTOGRAM_GROUP_E = 0x23,
    SXD_PPCNT_GRP_USR_XSR_PHYSICAL_LAYER_COUNTERS_GROUP_E = 0x24,
    SXD_PPCNT_GRP_MIN = SXD_PPCNT_GRP_IEEE_802_3_COUNTERS_E,
    SXD_PPCNT_GRP_MAX = SXD_PPCNT_GRP_USR_XSR_PHYSICAL_LAYER_COUNTERS_GROUP_E
} sxd_ppcnt_grp_t;

typedef struct sxd_ppcnt_eth_802_3_cntrs_grp_data_layout {
    uint32_t a_frames_transmitted_ok_high;
    uint32_t a_frames_transmitted_ok_low;
    uint32_t a_frames_received_ok_high;
    uint32_t a_frames_received_ok_low;
    uint32_t a_frame_check_sequence_errors_high;
    uint32_t a_frame_check_sequence_errors_low;
    uint32_t a_alignment_errors_high;
    uint32_t a_alignment_errors_low;
    uint32_t a_octets_transmitted_ok_high;
    uint32_t a_octets_transmitted_ok_low;
    uint32_t a_octets_received_ok_high;
    uint32_t a_octets_received_ok_low;
    uint32_t a_multicast_frames_xmitted_ok_high;
    uint32_t a_multicast_frames_xmitted_ok_low;
    uint32_t a_broadcast_frames_xmitted_ok_high;
    uint32_t a_broadcast_frames_xmitted_ok_low;
    uint32_t a_multicast_frames_received_ok_high;
    uint32_t a_multicast_frames_received_ok_low;
    uint32_t a_broadcast_frames_received_ok_high;
    uint32_t a_broadcast_frames_received_ok_low;
    uint32_t a_in_range_length_errors_high;
    uint32_t a_in_range_length_errors_low;
    uint32_t a_out_of_range_length_field_high;
    uint32_t a_out_of_range_length_field_low;
    uint32_t a_frame_too_long_errors_high;
    uint32_t a_frame_too_long_errors_low;
    uint32_t a_symbol_error_during_carrier_high;
    uint32_t a_symbol_error_during_carrier_low;
    uint32_t a_mac_control_frames_transmitted_high;
    uint32_t a_mac_control_frames_transmitted_low;
    uint32_t a_mac_control_frames_received_high;
    uint32_t a_mac_control_frames_received_low;
    uint32_t a_unsupported_opcodes_received_high;
    uint32_t a_unsupported_opcodes_received_low;
    uint32_t a_pause_mac_ctrl_frames_received_high;
    uint32_t a_pause_mac_ctrl_frames_received_low;
    uint32_t a_pause_mac_ctrl_frames_transmitted_high;
    uint32_t a_pause_mac_ctrl_frames_transmitted_low;
} sxd_ppcnt_eth_802_3_cntrs_grp_data_layout_t;

typedef struct sxd_ppcnt_eth_2863_cntrs_grp_data_layout {
    uint32_t if_in_octets_high;
    uint32_t if_in_octets_low;
    uint32_t if_in_ucast_pkts_high;
    uint32_t if_in_ucast_pkts_low;
    uint32_t if_in_discards_high;
    uint32_t if_in_discards_low;
    uint32_t if_in_errors_high;
    uint32_t if_in_errors_low;
    uint32_t if_in_unknown_protos_high;
    uint32_t if_in_unknown_protos_low;
    uint32_t if_out_octets_high;
    uint32_t if_out_octets_low;
    uint32_t if_out_ucast_pkts_high;
    uint32_t if_out_ucast_pkts_low;
    uint32_t if_out_discards_high;
    uint32_t if_out_discards_low;
    uint32_t if_out_errors_high;
    uint32_t if_out_errors_low;
    uint32_t if_in_multicast_pkts_high;
    uint32_t if_in_multicast_pkts_low;
    uint32_t if_in_broadcast_pkts_high;
    uint32_t if_in_broadcast_pkts_low;
    uint32_t if_out_multicast_pkts_high;
    uint32_t if_out_multicast_pkts_low;
    uint32_t if_out_broadcast_pkts_high;
    uint32_t if_out_broadcast_pkts_low;
} sxd_ppcnt_eth_2863_cntrs_grp_data_layout_t;

typedef struct sxd_ppcnt_eth_2819_cntrs_grp_data_layout {
    uint32_t ether_stats_drop_events_high;
    uint32_t ether_stats_drop_events_low;
    uint32_t ether_stats_octets_high;
    uint32_t ether_stats_octets_low;
    uint32_t ether_stats_pkts_high;
    uint32_t ether_stats_pkts_low;
    uint32_t ether_stats_broadcast_pkts_high;
    uint32_t ether_stats_broadcast_pkts_low;
    uint32_t ether_stats_multicast_pkts_high;
    uint32_t ether_stats_multicast_pkts_low;
    uint32_t ether_stats_crc_align_errors_high;
    uint32_t ether_stats_crc_align_errors_low;
    uint32_t ether_stats_undersize_pkts_high;
    uint32_t ether_stats_undersize_pkts_low;
    uint32_t ether_stats_oversize_pkts_high;
    uint32_t ether_stats_oversize_pkts_low;
    uint32_t ether_stats_fragments_high;
    uint32_t ether_stats_fragments_low;
    uint32_t ether_stats_jabbers_high;
    uint32_t ether_stats_jabbers_low;
    uint32_t ether_stats_collisions_high;
    uint32_t ether_stats_collisions_low;
    uint32_t ether_stats_pkts64octets_high;
    uint32_t ether_stats_pkts64octets_low;
    uint32_t ether_stats_pkts65to127octets_high;
    uint32_t ether_stats_pkts65to127octets_low;
    uint32_t ether_stats_pkts128to255octets_high;
    uint32_t ether_stats_pkts128to255octets_low;
    uint32_t ether_stats_pkts256to511octets_high;
    uint32_t ether_stats_pkts256to511octets_low;
    uint32_t ether_stats_pkts512to1023octets_high;
    uint32_t ether_stats_pkts512to1023octets_low;
    uint32_t ether_stats_pkts1024to1518octets_high;
    uint32_t ether_stats_pkts1024to1518octets_low;
    uint32_t ether_stats_pkts1519to2047octets_high;
    uint32_t ether_stats_pkts1519to2047octets_low;
    uint32_t ether_stats_pkts2048to4095octets_high;
    uint32_t ether_stats_pkts2048to4095octets_low;
    uint32_t ether_stats_pkts4096to8191octets_high;
    uint32_t ether_stats_pkts4096to8191octets_low;
    uint32_t ether_stats_pkts8192to10239octets_high;
    uint32_t ether_stats_pkts8192to10239octets_low;
} sxd_ppcnt_eth_2819_cntrs_grp_data_layout_t;

typedef struct sxd_ppcnt_eth_3635_cntrs_grp_data_layout {
    uint32_t dot3stats_alignment_errors_high;
    uint32_t dot3stats_alignment_errors_low;
    uint32_t dot3stats_fcs_errors_high;
    uint32_t dot3stats_fcs_errors_low;
    uint32_t dot3stats_single_collision_frames_high;
    uint32_t dot3stats_single_collision_frames_low;
    uint32_t dot3stats_multiple_collision_frames_high;
    uint32_t dot3stats_multiple_collision_frames_low;
    uint32_t dot3stats_sqe_test_errors_high;
    uint32_t dot3stats_sqe_test_errors_low;
    uint32_t dot3stats_deferred_transmissions_high;
    uint32_t dot3stats_deferred_transmissions_low;
    uint32_t dot3stats_late_collisions_high;
    uint32_t dot3stats_late_collisions_low;
    uint32_t dot3stats_excessive_collisions_high;
    uint32_t dot3stats_excessive_collisions_low;
    uint32_t dot3stats_internal_mac_transmit_errors_high;
    uint32_t dot3stats_internal_mac_transmit_errors_low;
    uint32_t dot3stats_carrier_sense_errors_high;
    uint32_t dot3stats_carrier_sense_errors_low;
    uint32_t dot3stats_frame_too_longs_high;
    uint32_t dot3stats_frame_too_longs_low;
    uint32_t dot3stats_internal_mac_receive_errors_high;
    uint32_t dot3stats_internal_mac_receive_errors_low;
    uint32_t dot3stats_symbol_errors_high;
    uint32_t dot3stats_symbol_errors_low;
    uint32_t dot3control_in_unknown_opcodes_high;
    uint32_t dot3control_in_unknown_opcodes_low;
    uint32_t dot3in_pause_frames_high;
    uint32_t dot3in_pause_frames_low;
    uint32_t dot3out_pause_frames_high;
    uint32_t dot3out_pause_frames_low;
} sxd_ppcnt_eth_3635_cntrs_grp_data_layout_t;

typedef struct sxd_ppcnt_eth_extended_cntrs_grp_data_layout {
    uint32_t port_transmit_wait_high;
    uint32_t port_transmit_wait_low;
    uint32_t ecn_marked_high;
    uint32_t ecn_marked_low;
    uint32_t no_buffer_discard_mc_high;
    uint32_t no_buffer_discard_mc_low;
    uint32_t rx_ebp_high;
    uint32_t rx_ebp_low;
    uint32_t tx_ebp_high;
    uint32_t tx_ebp_low;
    uint32_t rx_buffer_almost_full_high;
    uint32_t rx_buffer_almost_full_low;
    uint32_t rx_buffer_full_high;
    uint32_t rx_buffer_full_low;
    uint32_t rx_icrc_encapsulated_high;
    uint32_t rx_icrc_encapsulated_low;
    uint32_t tx_stats_pkts64octets_high;
    uint32_t tx_stats_pkts64octets_low;
    uint32_t tx_stats_pkts65to127octets_high;
    uint32_t tx_stats_pkts65to127octets_low;
    uint32_t tx_stats_pkts128to255octets_high;
    uint32_t tx_stats_pkts128to255octets_low;
    uint32_t tx_stats_pkts256to511octets_high;
    uint32_t tx_stats_pkts256to511octets_low;
    uint32_t tx_stats_pkts512to1023octets_high;
    uint32_t tx_stats_pkts512to1023octets_low;
    uint32_t tx_stats_pkts1024to1518octets_high;
    uint32_t tx_stats_pkts1024to1518octets_low;
    uint32_t tx_stats_pkts1519to2047octets_high;
    uint32_t tx_stats_pkts1519to2047octets_low;
    uint32_t tx_stats_pkts2048to4095octets_high;
    uint32_t tx_stats_pkts2048to4095octets_low;
    uint32_t tx_stats_pkts4096to8191octets_high;
    uint32_t tx_stats_pkts4096to8191octets_low;
    uint32_t tx_stats_pkts8192to10239octets_high;
    uint32_t tx_stats_pkts8192to10239octets_low;
    uint32_t ece_marked_high;
    uint32_t ece_marked_low;
} sxd_ppcnt_eth_extended_cntrs_grp_data_layout_t;

typedef struct sxd_ppcnt_eth_discard_cntrs_grp {
    uint32_t ingress_general_high;
    uint32_t ingress_general_low;
    uint32_t ingress_policy_engine_high;
    uint32_t ingress_policy_engine_low;
    uint32_t ingress_vlan_membership_high;
    uint32_t ingress_vlan_membership_low;
    uint32_t ingress_tag_frame_type_high;
    uint32_t ingress_tag_frame_type_low;
    uint32_t egress_vlan_membership_high;
    uint32_t egress_vlan_membership_low;
    uint32_t loopback_filter_high;
    uint32_t loopback_filter_low;
    uint32_t egress_general_high;
    uint32_t egress_general_low;
    uint32_t egress_hoq_high;
    uint32_t egress_hoq_low;
    uint32_t port_isolation_high;
    uint32_t port_isolation_low;
    uint32_t egress_policy_engine_high;
    uint32_t egress_policy_engine_low;
    uint32_t ingress_tx_link_down_high;
    uint32_t ingress_tx_link_down_low;
    uint32_t egress_stp_filter_high;
    uint32_t egress_stp_filter_low;
    uint32_t egress_hoq_stall_high;
    uint32_t egress_hoq_stall_low;
    uint32_t egress_sll_high;
    uint32_t egress_sll_low;
    uint32_t ingress_discard_all_high;
    uint32_t ingress_discard_all_low;
} sxd_ppcnt_eth_discard_cntrs_grp_t;

typedef struct sxd_ppcnt_link_level_retrans_cntr_grp_data {
    uint32_t llr_rx_cells_high;
    uint32_t llr_rx_cells_low;
    uint32_t llr_rx_error_high;
    uint32_t llr_rx_error_low;
    uint32_t llr_rx_crc_error_high;
    uint32_t llr_rx_crc_error_low;
    uint32_t llr_tx_cells_high;
    uint32_t llr_tx_cells_low;
    uint32_t llr_tx_ret_cells_high;
    uint32_t llr_tx_ret_cells_low;
    uint32_t llr_tx_ret_events_high;
    uint32_t llr_tx_ret_events_low;
} sxd_ppcnt_link_level_retrans_cntr_grp_data_t;

typedef struct sxd_ppcnt_eth_per_prio_grp_data_layout {
    uint32_t rx_octets_high;
    uint32_t rx_octets_low;
    uint32_t rx_uc_frames_high;
    uint32_t rx_uc_frames_low;
    uint32_t rx_mc_frames_high;
    uint32_t rx_mc_frames_low;
    uint32_t rx_bc_frames_high;
    uint32_t rx_bc_frames_low;
    uint32_t rx_frames_high;
    uint32_t rx_frames_low;
    uint32_t tx_octets_high;
    uint32_t tx_octets_low;
    uint32_t tx_uc_frames_high;
    uint32_t tx_uc_frames_low;
    uint32_t tx_mc_frames_high;
    uint32_t tx_mc_frames_low;
    uint32_t tx_bc_frames_high;
    uint32_t tx_bc_frames_low;
    uint32_t tx_frames_high;
    uint32_t tx_frames_low;
    uint32_t rx_pause_high;
    uint32_t rx_pause_low;
    uint32_t rx_pause_duration_high;
    uint32_t rx_pause_duration_low;
    uint32_t tx_pause_high;
    uint32_t tx_pause_low;
    uint32_t tx_pause_duration_high;
    uint32_t tx_pause_duration_low;
    uint32_t rx_pause_transition_high;
    uint32_t rx_pause_transition_low;
    uint32_t rx_discards_high;
    uint32_t rx_discards_low;
    uint32_t device_stall_minor_watermark_cnt_high;
    uint32_t device_stall_minor_watermark_cnt_low;
    uint32_t device_stall_critical_watermark_cnt_high;
    uint32_t device_stall_critical_watermark_cnt_low;
} sxd_ppcnt_eth_per_prio_grp_data_layout_t;

typedef struct sxd_ppcnt_eth_per_traffic_class_layout {
    uint32_t transmit_queue_high;
    uint32_t transmit_queue_low;
    uint32_t no_buffer_discard_uc_high;
    uint32_t no_buffer_discard_uc_low;
} sxd_ppcnt_eth_per_traffic_class_layout_t;

typedef struct sxd_ppcnt_phys_layer_cntrs {
    uint32_t time_since_last_clear_high;
    uint32_t time_since_last_clear_low;
    uint32_t symbol_errors_high;
    uint32_t symbol_errors_low;
    uint32_t sync_headers_errors_high;
    uint32_t sync_headers_errors_low;
    uint32_t edpl_bip_errors_lane0_high;
    uint32_t edpl_bip_errors_lane0_low;
    uint32_t edpl_bip_errors_lane1_high;
    uint32_t edpl_bip_errors_lane1_low;
    uint32_t edpl_bip_errors_lane2_high;
    uint32_t edpl_bip_errors_lane2_low;
    uint32_t edpl_bip_errors_lane3_high;
    uint32_t edpl_bip_errors_lane3_low;
    uint32_t fc_fec_corrected_blocks_lane0_high;
    uint32_t fc_fec_corrected_blocks_lane0_low;
    uint32_t fc_fec_corrected_blocks_lane1_high;
    uint32_t fc_fec_corrected_blocks_lane1_low;
    uint32_t fc_fec_corrected_blocks_lane2_high;
    uint32_t fc_fec_corrected_blocks_lane2_low;
    uint32_t fc_fec_corrected_blocks_lane3_high;
    uint32_t fc_fec_corrected_blocks_lane3_low;
    uint32_t fc_fec_uncorrectable_blocks_lane0_high;
    uint32_t fc_fec_uncorrectable_blocks_lane0_low;
    uint32_t fc_fec_uncorrectable_blocks_lane1_high;
    uint32_t fc_fec_uncorrectable_blocks_lane1_low;
    uint32_t fc_fec_uncorrectable_blocks_lane2_high;
    uint32_t fc_fec_uncorrectable_blocks_lane2_low;
    uint32_t fc_fec_uncorrectable_blocks_lane3_high;
    uint32_t fc_fec_uncorrectable_blocks_lane3_low;
    uint32_t rs_fec_corrected_blocks_high;
    uint32_t rs_fec_corrected_blocks_low;
    uint32_t rs_fec_uncorrectable_blocks_high;
    uint32_t rs_fec_uncorrectable_blocks_low;
    uint32_t rs_fec_no_errors_blocks_high;
    uint32_t rs_fec_no_errors_blocks_low;
    uint32_t rs_fec_single_error_blocks_high;
    uint32_t rs_fec_single_error_blocks_low;
    uint32_t rs_fec_corrected_symbols_total_high;
    uint32_t rs_fec_corrected_symbols_total_low;
    uint32_t rs_fec_corrected_symbols_lane0_high;
    uint32_t rs_fec_corrected_symbols_lane0_low;
    uint32_t rs_fec_corrected_symbols_lane1_high;
    uint32_t rs_fec_corrected_symbols_lane1_low;
    uint32_t rs_fec_corrected_symbols_lane2_high;
    uint32_t rs_fec_corrected_symbols_lane2_low;
    uint32_t rs_fec_corrected_symbols_lane3_high;
    uint32_t rs_fec_corrected_symbols_lane3_low;
    uint32_t link_down_events;
    uint32_t successful_recovery_events;
} sxd_ppcnt_phys_layer_cntrs_t;

typedef struct sxd_ppcnt_eth_per_traffic_class_cong_layout {
    uint32_t wred_discard_high;
    uint32_t wred_discard_low;
    uint32_t ecn_marked_tc_high;
    uint32_t ecn_marked_tc_low;
} sxd_ppcnt_eth_per_traffic_class_cong_layout_t;

typedef struct sxd_ppcnt_eth_per_receive_buffer_grp {
    uint32_t rx_no_buffer_discard_uc_high;
    uint32_t rx_no_buffer_discard_uc_low;
} sxd_ppcnt_eth_per_receive_buffer_grp_t;

typedef struct sxd_ppcnt_phys_layer_stat_cntrs {
    uint32_t time_since_last_clear_high;
    uint32_t time_since_last_clear_low;
    uint32_t phy_received_bits_high;
    uint32_t phy_received_bits_low;
    uint32_t phy_symbol_errors_high;
    uint32_t phy_symbol_errors_low;
    uint32_t phy_corrected_bits_high;
    uint32_t phy_corrected_bits_low;
    uint32_t phy_raw_errors_lane0_high;
    uint32_t phy_raw_errors_lane0_low;
    uint32_t phy_raw_errors_lane1_high;
    uint32_t phy_raw_errors_lane1_low;
    uint32_t phy_raw_errors_lane2_high;
    uint32_t phy_raw_errors_lane2_low;
    uint32_t phy_raw_errors_lane3_high;
    uint32_t phy_raw_errors_lane3_low;
    uint32_t phy_raw_errors_lane4_high;
    uint32_t phy_raw_errors_lane4_low;
    uint32_t phy_raw_errors_lane5_high;
    uint32_t phy_raw_errors_lane5_low;
    uint32_t phy_raw_errors_lane6_high;
    uint32_t phy_raw_errors_lane6_low;
    uint32_t phy_raw_errors_lane7_high;
    uint32_t phy_raw_errors_lane7_low;
    uint8_t raw_ber_magnitude;
    uint8_t raw_ber_coef;
    uint8_t effective_ber_magnitude;
    uint8_t effective_ber_coef;
    uint8_t symbol_ber_magnitude;
    uint8_t symbol_fec_ber_coef;
    uint8_t raw_ber_magnitude_lane0;
    uint8_t raw_ber_coef_lane0;
    uint8_t raw_ber_magnitude_lane1;
    uint8_t raw_ber_coef_lane1;
    uint8_t raw_ber_magnitude_lane2;
    uint8_t raw_ber_coef_lane2;
    uint8_t raw_ber_magnitude_lane3;
    uint8_t raw_ber_coef_lane3;
    uint8_t raw_ber_magnitude_lane4;
    uint8_t raw_ber_coef_lane4;
    uint8_t raw_ber_magnitude_lane5;
    uint8_t raw_ber_coef_lane5;
    uint8_t raw_ber_magnitude_lane6;
    uint8_t raw_ber_coef_lane6;
    uint8_t raw_ber_magnitude_lane7;
    uint8_t raw_ber_coef_lane7;
    uint32_t phy_effective_errors_high;
    uint32_t phy_effective_errors_low;
} sxd_ppcnt_phys_layer_stat_cntrs_t;

typedef struct sxd_ppcnt_eth_oob_port_cntrs {
    uint32_t if_in_ucast_pkts_high;
    uint32_t if_in_ucast_pkts_low;
    uint32_t if_in_octets_high;
    uint32_t if_in_octets_low;
    uint32_t if_in_discards_high;
    uint32_t if_in_discards_low;
    uint32_t if_in_errors_high;
    uint32_t if_in_errors_low;
    uint32_t ether_stats_crc_align_errors_high;
    uint32_t ether_stats_crc_align_errors_low;
    uint32_t ether_stats_undersize_pkts_high;
    uint32_t ether_stats_undersize_pkts_low;
    uint32_t ether_stats_oversize_pkts_high;
    uint32_t ether_stats_oversize_pkts_low;
    uint32_t dot3stats_symbol_errors_high;
    uint32_t dot3stats_symbol_errors_low;
    uint32_t dot3in_pause_frames_high;
    uint32_t dot3in_pause_frames_low;
    uint32_t dot3control_in_unknown_opcodes_high;
    uint32_t dot3control_in_unknown_opcodes_low;
    uint32_t if_out_ucast_pkts_high;
    uint32_t if_out_ucast_pkts_low;
    uint32_t if_out_octets_high;
    uint32_t if_out_octets_low;
    uint32_t dot3out_pause_frames_high;
    uint32_t dot3out_pause_frames_low;
    uint32_t if_out_errors_high;
    uint32_t if_out_errors_low;
    uint32_t phy_time_since_last_clear_high;
    uint32_t phy_time_since_last_clear_low;
    uint32_t phy_received_bits_high;
    uint32_t phy_received_bits_low;
    uint32_t phy_symbol_errors_high;
    uint32_t phy_symbol_errors_low;
} sxd_ppcnt_eth_oob_port_cntrs_t;

typedef struct sxd_ppcnt_IB_portcntrs_attribute_grp_data {
    uint16_t symbol_error_counter;
    uint8_t link_error_recovery_counter;
    uint8_t link_downed_counter;
    uint16_t port_rcv_errors;
    uint16_t port_rcv_remote_physical_errors;
    uint16_t port_rcv_switch_relay_errors;
    uint16_t port_xmit_discards;
    uint8_t port_xmit_constraint_errors;
    uint8_t port_rcv_constraint_errors;
    uint8_t local_link_integrity_errors;
    uint8_t excessive_buffer_overrun_errors;
    uint16_t vl_15_dropped;
    uint32_t port_xmit_data;
    uint32_t port_rcv_data;
    uint32_t port_xmit_pkts;
    uint32_t port_rcv_pkts;
    uint32_t port_xmit_wait;
} sxd_ppcnt_IB_portcntrs_attribute_grp_data_t;

typedef struct sxd_ppcnt_IB_long_portcntrs_attribute_grp_data {
    uint32_t symbol_error_counter_high;
    uint32_t symbol_error_counter_low;
    uint32_t link_error_recovery_counter_high;
    uint32_t link_error_recovery_counter_low;
    uint32_t link_downed_counter_high;
    uint32_t link_downed_counter_low;
    uint32_t port_rcv_errors_high;
    uint32_t port_rcv_errors_low;
    uint32_t port_rcv_remote_physical_errors_high;
    uint32_t port_rcv_remote_physical_errors_low;
    uint32_t port_rcv_switch_relay_errors_high;
    uint32_t port_rcv_switch_relay_errors_low;
    uint32_t port_xmit_discards_high;
    uint32_t port_xmit_discards_low;
    uint32_t port_xmit_constraint_errors_high;
    uint32_t port_xmit_constraint_errors_low;
    uint32_t port_rcv_constraint_errors_high;
    uint32_t port_rcv_constraint_errors_low;
    uint32_t local_link_integrity_errors_high;
    uint32_t local_link_integrity_errors_low;
    uint32_t excessive_buffer_overrun_errors_high;
    uint32_t excessive_buffer_overrun_errors_low;
    uint32_t vl_15_dropped_high;
    uint32_t vl_15_dropped_low;
    uint32_t port_xmit_data_high;
    uint32_t port_xmit_data_low;
    uint32_t port_rcv_data_high;
    uint32_t port_rcv_data_low;
    uint32_t port_xmit_pkts_high;
    uint32_t port_xmit_pkts_low;
    uint32_t port_rcv_pkts_high;
    uint32_t port_rcv_pkts_low;
    uint32_t port_xmit_wait_high;
    uint32_t port_xmit_wait_low;
    uint32_t port_effective_rcv_pkts_high;
    uint32_t port_effective_rcv_pkts_low;
    uint32_t port_effective_rcv_data_high;
    uint32_t port_effective_rcv_data_low;
} sxd_ppcnt_IB_long_portcntrs_attribute_grp_data_t;

typedef struct sxd_ppcnt_ppcnt_plr_counters {
    uint32_t plr_rcv_codes_high;
    uint32_t plr_rcv_codes_low;
    uint32_t plr_rcv_code_err_high;
    uint32_t plr_rcv_code_err_low;
    uint32_t plr_rcv_uncorrectable_code_high;
    uint32_t plr_rcv_uncorrectable_code_low;
    uint32_t plr_xmit_codes_high;
    uint32_t plr_xmit_codes_low;
    uint32_t plr_xmit_retry_codes_high;
    uint32_t plr_xmit_retry_codes_low;
    uint32_t plr_xmit_retry_events_high;
    uint32_t plr_xmit_retry_events_low;
    uint32_t plr_sync_events_high;
    uint32_t plr_sync_events_low;
    uint32_t hi_retransmission_rate_high;
    uint32_t hi_retransmission_rate_low;
    uint32_t plr_xmit_retry_codes_within_t_sec_max_high;
    uint32_t plr_xmit_retry_codes_within_t_sec_max_low;
    uint8_t pre_plr_ber_magnitude;
    uint8_t pre_plr_ber_coef;
} sxd_ppcnt_ppcnt_plr_counters_t;

typedef struct sxd_ppcnt_hist {
    uint32_t hi;
    uint32_t lo;
} sxd_ppcnt_hist_t;

typedef struct sxd_ppcnt_ppcnt_rs_fec_histograms_counters {
    sxd_ppcnt_hist_t hist[SXD_PPCNT_HIST_NUM];
} sxd_ppcnt_ppcnt_rs_fec_histograms_counters_t;

typedef struct sxd_ppcnt_usr_xsr_physical_layer {
    uint32_t time_since_last_clear_high;
    uint32_t time_since_last_clear_low;
    uint32_t fc_fec_corrected_blocks_lane0_high;
    uint32_t fc_fec_corrected_blocks_lane0_low;
    uint32_t fc_fec_corrected_blocks_lane1_high;
    uint32_t fc_fec_corrected_blocks_lane1_low;
    uint32_t fc_fec_corrected_blocks_lane2_high;
    uint32_t fc_fec_corrected_blocks_lane2_low;
    uint32_t fc_fec_corrected_blocks_lane3_high;
    uint32_t fc_fec_corrected_blocks_lane3_low;
    uint32_t fc_fec_corrected_blocks_lane4_high;
    uint32_t fc_fec_corrected_blocks_lane4_low;
    uint32_t fc_fec_corrected_blocks_lane5_high;
    uint32_t fc_fec_corrected_blocks_lane5_low;
    uint32_t fc_fec_corrected_blocks_lane6_high;
    uint32_t fc_fec_corrected_blocks_lane6_low;
    uint32_t fc_fec_corrected_blocks_lane7_high;
    uint32_t fc_fec_corrected_blocks_lane7_low;
    uint32_t fc_fec_uncorrectable_blocks_lane0_high;
    uint32_t fc_fec_uncorrectable_blocks_lane0_low;
    uint32_t fc_fec_uncorrectable_blocks_lane1_high;
    uint32_t fc_fec_uncorrectable_blocks_lane1_low;
    uint32_t fc_fec_uncorrectable_blocks_lane2_high;
    uint32_t fc_fec_uncorrectable_blocks_lane2_low;
    uint32_t fc_fec_uncorrectable_blocks_lane3_high;
    uint32_t fc_fec_uncorrectable_blocks_lane3_low;
    uint32_t fc_fec_uncorrectable_blocks_lane4_high;
    uint32_t fc_fec_uncorrectable_blocks_lane4_low;
    uint32_t fc_fec_uncorrectable_blocks_lane5_high;
    uint32_t fc_fec_uncorrectable_blocks_lane5_low;
    uint32_t fc_fec_uncorrectable_blocks_lane6_high;
    uint32_t fc_fec_uncorrectable_blocks_lane6_low;
    uint32_t fc_fec_uncorrectable_blocks_lane7_high;
    uint32_t fc_fec_uncorrectable_blocks_lane7_low;
    uint32_t link_down_events;
} sxd_ppcnt_usr_xsr_physical_layer_t;

union ppcnt_counter_set {
    sxd_ppcnt_eth_802_3_cntrs_grp_data_layout_t eth_802_3_cntrs_grp_data_layout;
    sxd_ppcnt_eth_2863_cntrs_grp_data_layout_t eth_2863_cntrs_grp_data_layout;
    sxd_ppcnt_eth_2819_cntrs_grp_data_layout_t eth_2819_cntrs_grp_data_layout;
    sxd_ppcnt_eth_3635_cntrs_grp_data_layout_t eth_3635_cntrs_grp_data_layout;
    sxd_ppcnt_eth_extended_cntrs_grp_data_layout_t eth_extended_cntrs_grp_data_layout;
    sxd_ppcnt_eth_discard_cntrs_grp_t eth_discard_cntrs_grp;
    sxd_ppcnt_link_level_retrans_cntr_grp_data_t link_level_retrans_cntr_grp_data;
    sxd_ppcnt_eth_per_prio_grp_data_layout_t eth_per_prio_grp_data_layout;
    sxd_ppcnt_eth_per_traffic_class_layout_t eth_per_traffic_class_layout;
    sxd_ppcnt_phys_layer_cntrs_t phys_layer_cntrs;
    sxd_ppcnt_eth_per_traffic_class_cong_layout_t eth_per_traffic_class_cong_layout;
    sxd_ppcnt_eth_per_receive_buffer_grp_t eth_per_receive_buffer_grp;
    sxd_ppcnt_phys_layer_stat_cntrs_t phys_layer_stat_cntrs;
    sxd_ppcnt_eth_oob_port_cntrs_t eth_oob_port_cntrs;
    sxd_ppcnt_IB_portcntrs_attribute_grp_data_t IB_portcntrs_attribute_grp_data;
    sxd_ppcnt_IB_long_portcntrs_attribute_grp_data_t IB_long_portcntrs_attribute_grp_data;
    sxd_ppcnt_ppcnt_plr_counters_t ppcnt_plr_counters;
    sxd_ppcnt_ppcnt_rs_fec_histograms_counters_t ppcnt_rs_fec_histograms_counters;
    sxd_ppcnt_usr_xsr_physical_layer_t usr_xsr_physical_layer;
};

/**
 * ku_ppcnt_reg structure is used to store the PPCNT register parameters
 */
struct ku_ppcnt_reg {
    uint8_t swid;
    uint8_t local_port;
    sxd_ppcnt_pnat_t pnat;
    uint8_t lp_msb;
    uint8_t port_type;
    sxd_ppcnt_grp_t grp;
    uint8_t clr;
    uint8_t lp_gl;
    uint8_t prio_tc;
    union ppcnt_counter_set counter_set;
};

/**
 * ku_access_ppcnt_reg structure is used to store the access register PPCNT command parameters
 */
struct ku_access_ppcnt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ppcnt_reg     ppcnt_reg; /**< ppcnt_reg - ppcnt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_PEFAAD_INDEX_DUMP_NUM 256

typedef struct sxd_pefaad_index_dump {
    uint32_t index_dump;
} sxd_pefaad_index_dump_t;

/**
 * ku_pefaad_reg structure is used to store the PEFAAD register parameters
 */
struct ku_pefaad_reg {
    uint8_t filter_fields;
    uint8_t op;
    uint16_t num_rec;
    uint8_t entry_a;
    uint16_t as_user_val;
    sxd_pefaad_index_dump_t index_dump[SXD_PEFAAD_INDEX_DUMP_NUM];
};

/**
 * ku_access_pefaad_reg structure is used to store the access register PEFAAD command parameters
 */
struct ku_access_pefaad_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pefaad_reg    pefaad_reg; /**< pefaad_reg - pefaad register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_pmlpe_width {
    SXD_PMLPE_WIDTH_UNMAP_LOCAL_PORT_E = 0x0,
    SXD_PMLPE_WIDTH_X1_E = 0x1,
    SXD_PMLPE_WIDTH_X2_E = 0x2,
    SXD_PMLPE_WIDTH_X4_E = 0x4,
    SXD_PMLPE_WIDTH_X8_E = 0x8,
    SXD_PMLPE_WIDTH_MIN = SXD_PMLPE_WIDTH_UNMAP_LOCAL_PORT_E,
    SXD_PMLPE_WIDTH_MAX = SXD_PMLPE_WIDTH_X8_E
} sxd_pmlpe_width_t;

/**
 * ku_pmlpe_reg structure is used to store the PMLPE register parameters
 */
struct ku_pmlpe_reg {
    uint8_t rxtx;
    uint8_t autosplit;
    uint8_t local_port;
    uint8_t lp_msb;
    sxd_pmlpe_width_t width;
    uint32_t lane0_module_mapping;
    uint32_t lane1_module_mapping;
    uint32_t lane2_module_mapping;
    uint32_t lane3_module_mapping;
    uint32_t lane4_module_mapping;
    uint32_t lane5_module_mapping;
    uint32_t lane6_module_mapping;
    uint32_t lane7_module_mapping;
};

/**
 * ku_access_pmlpe_reg structure is used to store the access register PMLPE command parameters
 */
struct ku_access_pmlpe_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmlpe_reg     pmlpe_reg; /**< pmlpe_reg - pmlpe register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_chlmm_reg structure is used to store the CHLMM register parameters
 */
struct ku_chlmm_reg {
    uint8_t switch_prio;
    uint8_t hlt_table_pointer;
};

/**
 * ku_access_chlmm_reg structure is used to store the access register CHLMM command parameters
 */
struct ku_access_chlmm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_chlmm_reg     chlmm_reg; /**< chlmm_reg - chlmm register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_tncr_reg structure is used to store the TNCR register parameters
 */
struct ku_tncr_reg {
    uint8_t clear_counters;
    uint32_t count_encap_high;
    uint32_t count_encap_low;
    uint32_t count_decap_high;
    uint32_t count_decap_low;
    uint32_t count_decap_errors_high;
    uint32_t count_decap_errors_low;
    uint32_t count_decap_discards_high;
    uint32_t count_decap_discards_low;
};

/**
 * ku_access_tncr_reg structure is used to store the access register TNCR command parameters
 */
struct ku_access_tncr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tncr_reg      tncr_reg; /**< tncr_reg - tncr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_rarlu_lut_en {
    SXD_RARLU_LUT_EN_DISABLE_E = 0x0,
    SXD_RARLU_LUT_EN_ENABLE_E = 0x1,
    SXD_RARLU_LUT_EN_MIN = SXD_RARLU_LUT_EN_DISABLE_E,
    SXD_RARLU_LUT_EN_MAX = SXD_RARLU_LUT_EN_ENABLE_E
} sxd_rarlu_lut_en_t;

/**
 * ku_rarlu_reg structure is used to store the RARLU register parameters
 */
struct ku_rarlu_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    sxd_rarlu_lut_en_t lut_en;
    uint32_t link_utiliztion_thr;
};

/**
 * ku_access_rarlu_reg structure is used to store the access register RARLU command parameters
 */
struct ku_access_rarlu_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rarlu_reg     rarlu_reg; /**< rarlu_reg - rarlu register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_sbsns_reg structure is used to store the SBSNS register parameters
 */
struct ku_sbsns_reg {
    uint8_t status;
    uint8_t trigger_id;
    uint32_t trigger_parameters;
    uint8_t time_high;
    uint32_t time_low;
};

/**
 * ku_access_sbsns_reg structure is used to store the access register SBSNS command parameters
 */
struct ku_access_sbsns_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbsns_reg     sbsns_reg; /**< sbsns_reg - sbsns register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_SPZR_NODE_DESCRIPTION_NUM 16

/**
 * ku_spzr_reg structure is used to store the SPZR register parameters
 */
struct ku_spzr_reg {
    uint8_t swid;
    uint8_t cm2;
    uint8_t ndm;
    uint8_t enh_sw_p0_mask;
    uint8_t cm;
    uint8_t vk;
    uint8_t mp;
    uint8_t sig;
    uint8_t ng;
    uint8_t enh_sw_p0;
    uint32_t capability_mask;
    uint32_t system_image_guid_h;
    uint32_t system_image_guid_l;
    uint32_t node_guid_h;
    uint32_t node_guid_l;
    uint32_t capability_mask2;
    uint16_t max_pkey;
    uint32_t node_description[SXD_SPZR_NODE_DESCRIPTION_NUM];
};

/**
 * ku_access_spzr_reg structure is used to store the access register SPZR command parameters
 */
struct ku_access_spzr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_spzr_reg      spzr_reg; /**< spzr_reg - spzr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_XMDR_TRANSACTION_NUM 32

/**
 * ku_xmdr_reg structure is used to store the XMDR register parameters
 */
struct ku_xmdr_reg {
    uint8_t num_rec;
    uint8_t reply_vect;
    uint32_t transaction[SXD_XMDR_TRANSACTION_NUM];
};

/**
 * ku_access_xmdr_reg structure is used to store the access register XMDR command parameters
 */
struct ku_access_xmdr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_xmdr_reg      xmdr_reg; /**< xmdr_reg - xmdr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

typedef struct sxd_mtcap_sensor_map {
    uint32_t hi;
    uint32_t lo;
} sxd_mtcap_sensor_map_t;

/**
 * ku_mtcap_reg structure is used to store the MTCAP register parameters
 */
struct ku_mtcap_reg {
    uint8_t slot_index;
    uint8_t sensor_count;
    uint8_t internal_sensor_count;
    sxd_mtcap_sensor_map_t sensor_map;
};

/**
 * ku_access_mtcap_reg structure is used to store the access register MTCAP command parameters
 */
struct ku_access_mtcap_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mtcap_reg     mtcap_reg; /**< mtcap_reg - mtcap register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_mdfcr_device_type {
    SXD_MDFCR_DEVICE_TYPE_VEGA_GEARBOX_E = 0x1,
    SXD_MDFCR_DEVICE_TYPE_TILE_E = 0x2,
    SXD_MDFCR_DEVICE_TYPE_MIN = SXD_MDFCR_DEVICE_TYPE_VEGA_GEARBOX_E,
    SXD_MDFCR_DEVICE_TYPE_MAX = SXD_MDFCR_DEVICE_TYPE_TILE_E
} sxd_mdfcr_device_type_t;


typedef enum sxd_mdfcr_error_id {
    SXD_MDFCR_ERROR_ID_NO_ERRORS_E = 0x1,
    SXD_MDFCR_ERROR_ID_ERROR_IN_TOTAL_SIZE_E = 0x2,
    SXD_MDFCR_ERROR_ID_ERROR_IN_IRAM_SIZE_READ_E = 0x3,
    SXD_MDFCR_ERROR_ID_ERROR_IN_DRAM_SIZE_READ_E = 0x4,
    SXD_MDFCR_ERROR_ID_SPI_READ_FROM_EEPROM_TIME_E = 0x5,
    SXD_MDFCR_ERROR_ID_CRC_ON_DOWNLOADED_EEPROM_CONTENT_E = 0x6,
    SXD_MDFCR_ERROR_ID_DOWNLOAD_PROCESS_IS_ON_E = 0x7,
    SXD_MDFCR_ERROR_ID_SPI_RESET_TIME_E = 0x8,
    SXD_MDFCR_ERROR_ID_MEMORY_PROTECTION_E = 0x9,
    SXD_MDFCR_ERROR_ID_UNKNOWN_PARAMETER_WAS_RECEIVED_BY_BOOTLOADER_E = 0xa,
    SXD_MDFCR_ERROR_ID_INVALID_MESSAGE_WAS_RECEIVED_BY_BOOTLOADER_E = 0xb,
    SXD_MDFCR_ERROR_ID_MESSAGE_WAS_ABORTED_BY_HOST_E = 0xc,
    SXD_MDFCR_ERROR_ID_MIN = SXD_MDFCR_ERROR_ID_NO_ERRORS_E,
    SXD_MDFCR_ERROR_ID_MAX = SXD_MDFCR_ERROR_ID_MESSAGE_WAS_ABORTED_BY_HOST_E
} sxd_mdfcr_error_id_t;

/**
 * ku_mdfcr_reg structure is used to store the MDFCR register parameters
 */
struct ku_mdfcr_reg {
    sxd_mdfcr_device_type_t device_type;
    uint8_t all;
    uint16_t device_index;
    uint8_t fw_status;
    uint16_t first_fw_status_device;
    uint32_t expected_fw_version;
    uint32_t fw_version;
    uint16_t build_id;
    uint8_t major;
    uint8_t minor;
    sxd_mdfcr_error_id_t error_id;
};

/**
 * ku_access_mdfcr_reg structure is used to store the access register MDFCR command parameters
 */
struct ku_access_mdfcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mdfcr_reg     mdfcr_reg; /**< mdfcr_reg - mdfcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_mddc_reg structure is used to store the MDDC register parameters
 */
struct ku_mddc_reg {
    uint8_t level;
    uint8_t index;
    uint8_t slot_index;
    uint8_t rst;
    uint8_t device_enable;
};

/**
 * ku_access_mddc_reg structure is used to store the access register MDDC command parameters
 */
struct ku_access_mddc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mddc_reg      mddc_reg; /**< mddc_reg - mddc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_paos_admin_status {
    SXD_PAOS_ADMIN_STATUS_UP_E = 0x1,
    SXD_PAOS_ADMIN_STATUS_DOWN_BY_CONFIGURATION_E = 0x2,
    SXD_PAOS_ADMIN_STATUS_UP_ONCE_E = 0x3,
    SXD_PAOS_ADMIN_STATUS_DISABLED_BY_SYSTEM_E = 0x4,
    SXD_PAOS_ADMIN_STATUS_MIN = SXD_PAOS_ADMIN_STATUS_UP_E,
    SXD_PAOS_ADMIN_STATUS_MAX = SXD_PAOS_ADMIN_STATUS_DISABLED_BY_SYSTEM_E
} sxd_paos_admin_status_t;


typedef enum sxd_paos_oper_status {
    SXD_PAOS_OPER_STATUS_UP_E = 0x1,
    SXD_PAOS_OPER_STATUS_DOWN_E = 0x2,
    SXD_PAOS_OPER_STATUS_DOWN_BY_PORT_FAILURE_E = 0x4,
    SXD_PAOS_OPER_STATUS_MIN = SXD_PAOS_OPER_STATUS_UP_E,
    SXD_PAOS_OPER_STATUS_MAX = SXD_PAOS_OPER_STATUS_DOWN_BY_PORT_FAILURE_E
} sxd_paos_oper_status_t;


typedef enum sxd_paos_e {
    SXD_PAOS_E_DO_NOT_GENERATE_EVENT_E = 0x0,
    SXD_PAOS_E_GENERATE_EVENT_E = 0x1,
    SXD_PAOS_E_GENERATE_SINGLE_EVENT_E = 0x2,
    SXD_PAOS_E_MIN = SXD_PAOS_E_DO_NOT_GENERATE_EVENT_E,
    SXD_PAOS_E_MAX = SXD_PAOS_E_GENERATE_SINGLE_EVENT_E
} sxd_paos_e_t;

/**
 * ku_paos_reg structure is used to store the PAOS register parameters
 */
struct ku_paos_reg {
    uint8_t swid;
    uint8_t local_port;
    uint8_t pnat;
    uint8_t lp_msb;
    sxd_paos_admin_status_t admin_status;
    sxd_paos_oper_status_t oper_status;
    uint8_t ase;
    uint8_t ee;
    uint8_t fd;
    sxd_paos_e_t e;
};

/**
 * ku_access_paos_reg structure is used to store the access register PAOS command parameters
 */
struct ku_access_paos_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_paos_reg      paos_reg; /**< paos_reg - paos register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_mtutc_operation {
    SXD_MTUTC_OPERATION_SET_TIME_AT_NEXT_SEC_E = 0x0,
    SXD_MTUTC_OPERATION_ADJUST_TIME_E = 0x2,
    SXD_MTUTC_OPERATION_ADJUST_FREQ_UTC_E = 0x3,
    SXD_MTUTC_OPERATION_ADJUST_FREQ_FRC_E = 0x4,
    SXD_MTUTC_OPERATION_ADJUST_FREQ_BOTH_E = 0x5,
    SXD_MTUTC_OPERATION_MIN = SXD_MTUTC_OPERATION_SET_TIME_AT_NEXT_SEC_E,
    SXD_MTUTC_OPERATION_MAX = SXD_MTUTC_OPERATION_ADJUST_FREQ_BOTH_E
} sxd_mtutc_operation_t;

/**
 * ku_mtutc_reg structure is used to store the MTUTC register parameters
 */
struct ku_mtutc_reg {
    sxd_mtutc_operation_t operation;
    uint32_t freq_adjustment;
    uint32_t utc_sec;
    uint32_t utc_nsec;
    uint32_t time_adjustment;
};

/**
 * ku_access_mtutc_reg structure is used to store the access register MTUTC command parameters
 */
struct ku_access_mtutc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mtutc_reg     mtutc_reg; /**< mtutc_reg - mtutc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_sfmr_flood_bridge_type {
    SXD_SFMR_FLOOD_BRIDGE_TYPE_TYPE_0_E = 0x0,
    SXD_SFMR_FLOOD_BRIDGE_TYPE_TYPE_1_E = 0x1,
    SXD_SFMR_FLOOD_BRIDGE_TYPE_MIN = SXD_SFMR_FLOOD_BRIDGE_TYPE_TYPE_0_E,
    SXD_SFMR_FLOOD_BRIDGE_TYPE_MAX = SXD_SFMR_FLOOD_BRIDGE_TYPE_TYPE_1_E
} sxd_sfmr_flood_bridge_type_t;

/**
 * ku_sfmr_reg structure is used to store the SFMR register parameters
 */
struct ku_sfmr_reg {
    uint8_t update;
    uint8_t op;
    uint16_t fid;
    uint16_t update_mask;
    uint8_t disable_tport_encap;
    uint8_t flood_rsp;
    sxd_sfmr_flood_bridge_type_t flood_bridge_type;
    uint16_t fid_offset;
    uint8_t vtfp;
    uint32_t nve_tunnel_flood_ptr;
    uint8_t vv;
    uint32_t vni;
    uint8_t irif_v;
    uint16_t irif;
    uint8_t decap_counter_set_type;
    uint32_t decap_counter_index;
    uint8_t tunnel_port_lbf_bitmap;
    uint8_t nve_flood_prf_id;
    uint8_t smpe_valid;
    uint16_t smpe;
};

/**
 * ku_access_sfmr_reg structure is used to store the access register SFMR command parameters
 */
struct ku_access_sfmr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sfmr_reg      sfmr_reg; /**< sfmr_reg - sfmr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_ptys_pnat {
    SXD_PTYS_PNAT_LOCAL_PORT_NUMBER_E = 0x0,
    SXD_PTYS_PNAT_LABEL_PORT_NUMBER_E = 0x1,
    SXD_PTYS_PNAT_OUT_OF_BAND_E = 0x3,
    SXD_PTYS_PNAT_MIN = SXD_PTYS_PNAT_LOCAL_PORT_NUMBER_E,
    SXD_PTYS_PNAT_MAX = SXD_PTYS_PNAT_OUT_OF_BAND_E
} sxd_ptys_pnat_t;


typedef enum sxd_ptys_port_type {
    SXD_PTYS_PORT_TYPE_NETWORK_PORT_E = 0x0,
    SXD_PTYS_PORT_TYPE_NEAR_E = 0x1,
    SXD_PTYS_PORT_TYPE_INTERNAL_IC_PORT_E = 0x2,
    SXD_PTYS_PORT_TYPE_FAR_E = 0x3,
    SXD_PTYS_PORT_TYPE_MIN = SXD_PTYS_PORT_TYPE_NETWORK_PORT_E,
    SXD_PTYS_PORT_TYPE_MAX = SXD_PTYS_PORT_TYPE_FAR_E
} sxd_ptys_port_type_t;


typedef enum sxd_ptys_proto_mask {
    SXD_PTYS_PROTO_MASK_INFINIBAND_E = 0x1,
    SXD_PTYS_PROTO_MASK_RESERVED_E = 0x2,
    SXD_PTYS_PROTO_MASK_ETHERNET_E = 0x4,
    SXD_PTYS_PROTO_MASK_MIN = SXD_PTYS_PROTO_MASK_INFINIBAND_E,
    SXD_PTYS_PROTO_MASK_MAX = SXD_PTYS_PROTO_MASK_ETHERNET_E
} sxd_ptys_proto_mask_t;


typedef enum sxd_ptys_an_status {
    SXD_PTYS_AN_STATUS_STATUS_IS_UNAVAILABLE_E = 0x0,
    SXD_PTYS_AN_STATUS_AN_COMPLETED_SUCCESSFULLY_E = 0x1,
    SXD_PTYS_AN_STATUS_AN_PERFORMED_BUT_FAILED_E = 0x2,
    SXD_PTYS_AN_STATUS_AN_WAS_NOT_PERFORMED_LINK_IS_UP_E = 0x3,
    SXD_PTYS_AN_STATUS_AN_WAS_NOT_PERFORMED_LINK_IS_DOWN_E = 0x4,
    SXD_PTYS_AN_STATUS_MIN = SXD_PTYS_AN_STATUS_STATUS_IS_UNAVAILABLE_E,
    SXD_PTYS_AN_STATUS_MAX = SXD_PTYS_AN_STATUS_AN_WAS_NOT_PERFORMED_LINK_IS_DOWN_E
} sxd_ptys_an_status_t;


typedef enum sxd_ptys_ib_proto_capability {
    SXD_PTYS_IB_PROTO_CAPABILITY_SDR_E = 0x1,
    SXD_PTYS_IB_PROTO_CAPABILITY_DDR_E = 0x2,
    SXD_PTYS_IB_PROTO_CAPABILITY_QDR_E = 0x4,
    SXD_PTYS_IB_PROTO_CAPABILITY_FDR10_E = 0x8,
    SXD_PTYS_IB_PROTO_CAPABILITY_FDR_E = 0x10,
    SXD_PTYS_IB_PROTO_CAPABILITY_EDR_E = 0x20,
    SXD_PTYS_IB_PROTO_CAPABILITY_HDR_E = 0x40,
    SXD_PTYS_IB_PROTO_CAPABILITY_NDR_E = 0x80,
    SXD_PTYS_IB_PROTO_CAPABILITY_MIN = SXD_PTYS_IB_PROTO_CAPABILITY_SDR_E,
    SXD_PTYS_IB_PROTO_CAPABILITY_MAX = SXD_PTYS_IB_PROTO_CAPABILITY_NDR_E
} sxd_ptys_ib_proto_capability_t;


typedef enum sxd_ptys_connector_type {
    SXD_PTYS_CONNECTOR_TYPE_NO_CONNECTOR_OR_UNKNOWN_E = 0x0,
    SXD_PTYS_CONNECTOR_TYPE_PORT_NONE_E = 0x1,
    SXD_PTYS_CONNECTOR_TYPE_PORT_TP_E = 0x2,
    SXD_PTYS_CONNECTOR_TYPE_PORT_AUI_E = 0x3,
    SXD_PTYS_CONNECTOR_TYPE_PORT_BNC_E = 0x4,
    SXD_PTYS_CONNECTOR_TYPE_PORT_MII_E = 0x5,
    SXD_PTYS_CONNECTOR_TYPE_PORT_FIBRE_E = 0x6,
    SXD_PTYS_CONNECTOR_TYPE_PORT_DA_E = 0x7,
    SXD_PTYS_CONNECTOR_TYPE_PORT_OTHER_E = 0x8,
    SXD_PTYS_CONNECTOR_TYPE_MIN = SXD_PTYS_CONNECTOR_TYPE_NO_CONNECTOR_OR_UNKNOWN_E,
    SXD_PTYS_CONNECTOR_TYPE_MAX = SXD_PTYS_CONNECTOR_TYPE_PORT_OTHER_E
} sxd_ptys_connector_type_t;

/**
 * ku_ptys_reg structure is used to store the PTYS register parameters
 */
struct ku_ptys_reg {
    uint8_t reserved_high;
    uint8_t an_disable_admin;
    uint8_t an_disable_cap;
    uint8_t force_tx_aba_param;
    uint8_t local_port;
    sxd_ptys_pnat_t pnat;
    uint8_t lp_msb;
    sxd_ptys_port_type_t port_type;
    sxd_ptys_proto_mask_t proto_mask;
    sxd_ptys_an_status_t an_status;
    uint16_t max_port_rate;
    uint16_t data_rate_oper;
    uint32_t ext_eth_proto_capability;
    uint32_t eth_proto_capability;
    uint16_t ib_link_width_capability;
    sxd_ptys_ib_proto_capability_t ib_proto_capability;
    uint32_t ext_eth_proto_admin;
    uint32_t eth_proto_admin;
    uint16_t ib_link_width_admin;
    uint16_t ib_proto_admin;
    uint32_t ext_eth_proto_oper;
    uint32_t eth_proto_oper;
    uint16_t ib_link_width_oper;
    uint16_t ib_proto_oper;
    uint8_t eth_proto_lp_valid;
    uint8_t force_kr_frames_cap;
    uint8_t force_kr_frames_admin;
    sxd_ptys_connector_type_t connector_type;
    uint32_t eth_proto_lp_advertise;
};

/**
 * ku_access_ptys_reg structure is used to store the access register PTYS command parameters
 */
struct ku_access_ptys_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ptys_reg      ptys_reg; /**< ptys_reg - ptys register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_hrdqt_reg structure is used to store the HRDQT register parameters
 */
struct ku_hrdqt_reg {
    uint8_t rdq;
    uint8_t tac_en;
    uint8_t mirror_action;
    uint8_t mirror_agent;
    uint8_t host_based_mirror_reason_id;
};

/**
 * ku_access_hrdqt_reg structure is used to store the access register HRDQT command parameters
 */
struct ku_access_hrdqt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_hrdqt_reg     hrdqt_reg; /**< hrdqt_reg - hrdqt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MTSDE_SENSOR_SHUT_DOWN_MAP_NUM 22

/**
 * ku_mtsde_reg structure is used to store the MTSDE register parameters
 */
struct ku_mtsde_reg {
    uint16_t last_sensor;
    uint8_t slot_index;
    uint16_t sensor_count;
    uint32_t sensor_shut_down_map[SXD_MTSDE_SENSOR_SHUT_DOWN_MAP_NUM];
};

/**
 * ku_access_mtsde_reg structure is used to store the access register MTSDE command parameters
 */
struct ku_access_mtsde_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mtsde_reg     mtsde_reg; /**< mtsde_reg - mtsde register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_smpe_reg structure is used to store the SMPE register parameters
 */
struct ku_smpe_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint16_t smpe_index;
    uint16_t evid;
};

/**
 * ku_access_smpe_reg structure is used to store the access register SMPE command parameters
 */
struct ku_access_smpe_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_smpe_reg      smpe_reg; /**< smpe_reg - smpe register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_hett_status {
    SXD_HETT_STATUS_IDLE_E = 0x0,
    SXD_HETT_STATUS_BUSY_E = 0x1,
    SXD_HETT_STATUS_MIN = SXD_HETT_STATUS_IDLE_E,
    SXD_HETT_STATUS_MAX = SXD_HETT_STATUS_BUSY_E
} sxd_hett_status_t;

typedef struct sxd_hett_trap_group_bitmap {
    uint32_t hi;
    uint32_t lo;
} sxd_hett_trap_group_bitmap_t;

/**
 * ku_hett_reg structure is used to store the HETT register parameters
 */
struct ku_hett_reg {
    uint8_t opcode;
    sxd_hett_status_t status;
    sxd_hett_trap_group_bitmap_t trap_group_bitmap;
    uint8_t trap_group;
};

/**
 * ku_access_hett_reg structure is used to store the access register HETT command parameters
 */
struct ku_access_hett_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_hett_reg      hett_reg; /**< hett_reg - hett register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_xgcr_reg structure is used to store the XGCR register parameters
 */
struct ku_xgcr_reg {
    uint8_t mtm;
};

/**
 * ku_access_xgcr_reg structure is used to store the access register XGCR command parameters
 */
struct ku_access_xgcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_xgcr_reg      xgcr_reg; /**< xgcr_reg - xgcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_tiqdr_reg structure is used to store the TIQDR register parameters
 */
struct ku_tiqdr_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t color;
    uint8_t switch_prio;
    uint8_t dscp;
};

/**
 * ku_access_tiqdr_reg structure is used to store the access register TIQDR command parameters
 */
struct ku_access_tiqdr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tiqdr_reg     tiqdr_reg; /**< tiqdr_reg - tiqdr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_xraltb_reg structure is used to store the XRALTB register parameters
 */
struct ku_xraltb_reg {
    uint16_t virtual_router;
    uint8_t protocol;
    uint8_t tree_id;
};

/**
 * ku_access_xraltb_reg structure is used to store the access register XRALTB command parameters
 */
struct ku_access_xraltb_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_xraltb_reg    xraltb_reg; /**< xraltb_reg - xraltb register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_tngee_tunnel_type {
    SXD_TNGEE_TUNNEL_TYPE_NVE_E = 0x0,
    SXD_TNGEE_TUNNEL_TYPE_FLEX_TUNNEL_E = 0x2,
    SXD_TNGEE_TUNNEL_TYPE_MIN = SXD_TNGEE_TUNNEL_TYPE_NVE_E,
    SXD_TNGEE_TUNNEL_TYPE_MAX = SXD_TNGEE_TUNNEL_TYPE_FLEX_TUNNEL_E
} sxd_tngee_tunnel_type_t;


typedef enum sxd_tngee_protocol {
    SXD_TNGEE_PROTOCOL_IPV4_E = 0x0,
    SXD_TNGEE_PROTOCOL_IPV6_E = 0x1,
    SXD_TNGEE_PROTOCOL_MIN = SXD_TNGEE_PROTOCOL_IPV4_E,
    SXD_TNGEE_PROTOCOL_MAX = SXD_TNGEE_PROTOCOL_IPV6_E
} sxd_tngee_protocol_t;

typedef struct sxd_tngee_tngee_nve {
    uint8_t vni_update;
    uint8_t tqos_prof_en;
    uint32_t vni;
    uint8_t tqos_profile;
} sxd_tngee_tngee_nve_t;

typedef struct sxd_tngee_tngee_flex_reg {
    uint8_t tqos_profile;
    uint8_t tunnel_port;
    uint8_t emt_pointer;
    uint8_t cbset_select;
    uint8_t cbset_x_set_en;
    uint8_t cbset_y_set_en;
    uint16_t cbset_x_val;
    uint16_t cbset_y_val;
} sxd_tngee_tngee_flex_reg_t;

union tngee_entry {
    sxd_tngee_tngee_nve_t tngee_nve;
    sxd_tngee_tngee_flex_reg_t tngee_flex_reg;
};

/**
 * ku_tngee_reg structure is used to store the TNGEE register parameters
 */
struct ku_tngee_reg {
    uint32_t l2_enc_index;
    sxd_tngee_tunnel_type_t tunnel_type;
    uint8_t vnext;
    uint32_t next_l2_enc_ptr;
    uint16_t ecmp_size;
    sxd_tngee_protocol_t protocol;
    uint16_t uirif;
    uint32_t udip;
    uint8_t counter_set_type;
    uint32_t counter_index;
    union tngee_entry entry;
};

/**
 * ku_access_tngee_reg structure is used to store the access register TNGEE command parameters
 */
struct ku_access_tngee_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tngee_reg     tngee_reg; /**< tngee_reg - tngee register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_spms_v2_state {
    SXD_SPMS_V2_STATE_STP_DISCARDING_E = 0x1,
    SXD_SPMS_V2_STATE_STP_LEARNING_E = 0x2,
    SXD_SPMS_V2_STATE_STP_FORWARDING_E = 0x3,
    SXD_SPMS_V2_STATE_MIN = SXD_SPMS_V2_STATE_STP_DISCARDING_E,
    SXD_SPMS_V2_STATE_MAX = SXD_SPMS_V2_STATE_STP_FORWARDING_E
} sxd_spms_v2_state_t;

#define SXD_SPMS_V2_VID_RECORD_NUM 255

typedef struct sxd_spms_v2_vid_record {
    sxd_spms_v2_state_t state;
    uint16_t vid;
} sxd_spms_v2_vid_record_t;

/**
 * ku_spms_v2_reg structure is used to store the SPMS_V2 register parameters
 */
struct ku_spms_v2_reg {
    uint8_t allv;
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t num_rec;
    sxd_spms_v2_vid_record_t vid_record[SXD_SPMS_V2_VID_RECORD_NUM];
};

/**
 * ku_access_spms_v2_reg structure is used to store the access register SPMS_V2 command parameters
 */
struct ku_access_spms_v2_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_spms_v2_reg   spms_v2_reg; /**< spms_v2_reg - spms_v2 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_SMPEB_ELPORT_RECORD_NUM 256

typedef struct sxd_smpeb_elport_record {
    uint8_t update;
    uint32_t value;
} sxd_smpeb_elport_record_t;

/**
 * ku_smpeb_reg structure is used to store the SMPEB register parameters
 */
struct ku_smpeb_reg {
    uint16_t smpe_index;
    uint8_t elport_page;
    sxd_smpeb_elport_record_t elport_record[SXD_SMPEB_ELPORT_RECORD_NUM];
};

/**
 * ku_access_smpeb_reg structure is used to store the access register SMPEB command parameters
 */
struct ku_access_smpeb_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_smpeb_reg     smpeb_reg; /**< smpeb_reg - smpeb register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_ibfmr_reg structure is used to store the IBFMR register parameters
 */
struct ku_ibfmr_reg {
    uint8_t atm_v;
    uint16_t attribute_id;
    uint32_t attribute_modifier;
};

/**
 * ku_access_ibfmr_reg structure is used to store the access register IBFMR command parameters
 */
struct ku_access_ibfmr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ibfmr_reg     ibfmr_reg; /**< ibfmr_reg - ibfmr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_sbsnte_reg structure is used to store the SBSNTE register parameters
 */
struct ku_sbsnte_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t type;
    uint32_t tclass_en_high;
    uint32_t tclass_en_low;
};

/**
 * ku_access_sbsnte_reg structure is used to store the access register SBSNTE command parameters
 */
struct ku_access_sbsnte_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbsnte_reg    sbsnte_reg; /**< sbsnte_reg - sbsnte register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_ppbs_action {
    SXD_PPBS_ACTION_NOP_E = 0x0,
    SXD_PPBS_ACTION_FORWARD_TO_IP_ROUTER_E = 0x3,
    SXD_PPBS_ACTION_FORWARD_TO_FCF_E = 0x4,
    SXD_PPBS_ACTION_DISCARD_E = 0x5,
    SXD_PPBS_ACTION_DISCARD_ERROR_E = 0xf,
    SXD_PPBS_ACTION_MIN = SXD_PPBS_ACTION_NOP_E,
    SXD_PPBS_ACTION_MAX = SXD_PPBS_ACTION_DISCARD_ERROR_E
} sxd_ppbs_action_t;


typedef enum sxd_ppbs_protocol {
    SXD_PPBS_PROTOCOL_IPV4_E = 0x0,
    SXD_PPBS_PROTOCOL_IPV6_E = 0x1,
    SXD_PPBS_PROTOCOL_MIN = SXD_PPBS_PROTOCOL_IPV4_E,
    SXD_PPBS_PROTOCOL_MAX = SXD_PPBS_PROTOCOL_IPV6_E
} sxd_ppbs_protocol_t;


typedef enum sxd_ppbs_type {
    SXD_PPBS_TYPE_UNICAST_RECORD_E = 0x0,
    SXD_PPBS_TYPE_UNICAST_LAG_RECORD_E = 0x1,
    SXD_PPBS_TYPE_MULTICAST_RECORD_E = 0x2,
    SXD_PPBS_TYPE_UNICAST_TUNNEL_RECORD_E = 0xc,
    SXD_PPBS_TYPE_MULTICAST_TUNNEL_RECORD_E = 0xf,
    SXD_PPBS_TYPE_MIN = SXD_PPBS_TYPE_UNICAST_RECORD_E,
    SXD_PPBS_TYPE_MAX = SXD_PPBS_TYPE_MULTICAST_TUNNEL_RECORD_E
} sxd_ppbs_type_t;

typedef struct sxd_ppbs_ppbs_unicast {
    uint8_t v_fid;
    uint8_t set_vid;
    uint16_t vid;
    uint16_t fid;
    sxd_ppbs_action_t action;
    uint16_t system_port;
} sxd_ppbs_ppbs_unicast_t;

typedef struct sxd_ppbs_unicast_lag {
    uint8_t uvid;
    uint16_t vid;
    uint16_t lag_id;
} sxd_ppbs_unicast_lag_t;

typedef struct sxd_ppbs_ppbs_multicast {
    uint8_t v_fid;
    uint16_t pgi;
    uint16_t fid;
    uint16_t mid;
} sxd_ppbs_ppbs_multicast_t;

typedef struct sxd_ppbs_unicast_tunnel {
    uint32_t udip;
    sxd_ppbs_protocol_t protocol;
    uint8_t gen_enc;
    uint16_t tunnel_port_lbf_bitmap;
    uint16_t ecmp_size;
} sxd_ppbs_unicast_tunnel_t;

typedef struct sxd_ppbs_multicast_tunnel {
    uint16_t underlay_mc_ptr_msb;
    uint16_t fid;
    uint8_t underlay_mc_ptr_lsb;
    uint8_t v_fid;
    uint16_t mid;
    uint16_t lbf_tunnel_port_bitmap;
    uint16_t ecmp_size;
} sxd_ppbs_multicast_tunnel_t;

union ppbs_pbs_record {
    sxd_ppbs_ppbs_unicast_t ppbs_unicast;
    sxd_ppbs_unicast_lag_t unicast_lag;
    sxd_ppbs_ppbs_multicast_t ppbs_multicast;
    sxd_ppbs_unicast_tunnel_t unicast_tunnel;
    sxd_ppbs_multicast_tunnel_t multicast_tunnel;
};

/**
 * ku_ppbs_reg structure is used to store the PPBS register parameters
 */
struct ku_ppbs_reg {
    uint8_t swid;
    sxd_ppbs_type_t type;
    uint32_t pbs_ptr;
    union ppbs_pbs_record pbs_record;
};

/**
 * ku_access_ppbs_reg structure is used to store the access register PPBS command parameters
 */
struct ku_access_ppbs_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ppbs_reg      ppbs_reg; /**< ppbs_reg - ppbs register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MDIR_DEVICE_ID_NUM 8

/**
 * ku_mdir_reg structure is used to store the MDIR register parameters
 */
struct ku_mdir_reg {
    uint32_t device_id[SXD_MDIR_DEVICE_ID_NUM];
};

/**
 * ku_access_mdir_reg structure is used to store the access register MDIR command parameters
 */
struct ku_access_mdir_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mdir_reg      mdir_reg; /**< mdir_reg - mdir register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

typedef struct sxd_fppc_protocol {
    uint8_t field_offset_dword_prot;
    uint8_t field_offset_bytes_prot;
    uint16_t field_mask_prot_non_tlv;
    uint32_t field_mask_prot_tlv;
} sxd_fppc_protocol_t;

typedef struct sxd_fppc_header_length {
    uint8_t field_offset_dword_length;
    uint8_t field_offset_bytes_length;
    uint8_t field_mask_length;
    uint8_t length_math_bitmap;
    uint8_t length_math_add_pos;
    uint8_t length_math_add;
    uint8_t length_math_shift_left;
    uint8_t length_math_shift;
} sxd_fppc_header_length_t;

typedef struct sxd_fppc_fexp_st {
    uint8_t fexp_st_en;
    uint8_t fexp_st_id;
    uint32_t fexp_st_tlv_type;
} sxd_fppc_fexp_st_t;

typedef struct sxd_fppc_fexp_of {
    uint8_t fexp_of_en;
    uint8_t fexp_of_id;
    uint32_t fexp_of_tlv_type;
    uint8_t field_offset_dword_fexp_of;
    uint8_t field_offset_bytes_fexp_of;
    uint8_t field_mask_fexp_of;
    uint8_t fexp_of_math_bitmap;
    uint8_t fexp_of_math_add_pos;
    uint8_t fexp_of_math_add;
    uint8_t fexp_of_math_shift_left;
    uint8_t fexp_of_math_shift;
} sxd_fppc_fexp_of_t;

typedef struct sxd_fppc_my_tlv {
    uint8_t my_ftlv_en;
    uint8_t my_ftlv_start;
    uint8_t my_ftlv_fpp;
} sxd_fppc_my_tlv_t;

/**
 * ku_fppc_reg structure is used to store the FPPC register parameters
 */
struct ku_fppc_reg {
    uint8_t as_ftlv;
    uint8_t fpp;
    uint8_t empty_fph;
    sxd_fppc_protocol_t protocol;
    sxd_fppc_header_length_t header_length;
    sxd_fppc_fexp_st_t fexp_st;
    sxd_fppc_fexp_of_t fexp_of;
    sxd_fppc_my_tlv_t my_tlv;
};

/**
 * ku_access_fppc_reg structure is used to store the access register FPPC command parameters
 */
struct ku_access_fppc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_fppc_reg      fppc_reg; /**< fppc_reg - fppc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MTEWE_SENSOR_WARNING_NUM 22

/**
 * ku_mtewe_reg structure is used to store the MTEWE register parameters
 */
struct ku_mtewe_reg {
    uint16_t last_sensor;
    uint8_t slot_index;
    uint16_t sensor_count;
    uint32_t sensor_warning[SXD_MTEWE_SENSOR_WARNING_NUM];
};

/**
 * ku_access_mtewe_reg structure is used to store the access register MTEWE command parameters
 */
struct ku_access_mtewe_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mtewe_reg     mtewe_reg; /**< mtewe_reg - mtewe register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_hgcr_reg structure is used to store the HGCR register parameters
 */
struct ku_hgcr_reg {
    uint16_t truncation_size;
    uint16_t truncation_size_prof1;
    uint16_t truncation_size_prof2;
    uint8_t tac_crawler_timer;
    uint8_t tac_crawler_action;
};

/**
 * ku_access_hgcr_reg structure is used to store the access register HGCR command parameters
 */
struct ku_access_hgcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_hgcr_reg      hgcr_reg; /**< hgcr_reg - hgcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_XLKBU_VALUE_NUM 16

#define SXD_XLKBU_MASK_NUM 16

#define SXD_XLKBU_NEW_VALUE_NUM 16

#define SXD_XLKBU_NEW_VALUE_MASK_NUM 16

/**
 * ku_xlkbu_reg structure is used to store the XLKBU register parameters
 */
struct ku_xlkbu_reg {
    uint8_t data_type;
    uint32_t value[SXD_XLKBU_VALUE_NUM];
    uint32_t mask[SXD_XLKBU_MASK_NUM];
    uint32_t new_value[SXD_XLKBU_NEW_VALUE_NUM];
    uint32_t new_value_mask[SXD_XLKBU_NEW_VALUE_MASK_NUM];
};

/**
 * ku_access_xlkbu_reg structure is used to store the access register XLKBU command parameters
 */
struct ku_access_xlkbu_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_xlkbu_reg     xlkbu_reg; /**< xlkbu_reg - xlkbu register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_xrmt_reg structure is used to store the XRMT register parameters
 */
struct ku_xrmt_reg {
    uint32_t index;
    uint8_t l0_val;
    uint8_t l0_vec;
    uint8_t l1_val;
    uint8_t l1_vec;
};

/**
 * ku_access_xrmt_reg structure is used to store the access register XRMT command parameters
 */
struct ku_access_xrmt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_xrmt_reg      xrmt_reg; /**< xrmt_reg - xrmt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_cepc_reg structure is used to store the CEPC register parameters
 */
struct ku_cepc_reg {
    uint16_t local_port;
    uint8_t pp;
    uint8_t lp_msb;
    uint8_t en_ed;
};

/**
 * ku_access_cepc_reg structure is used to store the access register CEPC command parameters
 */
struct ku_access_cepc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_cepc_reg      cepc_reg; /**< cepc_reg - cepc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_slsir_rx_ugl_state {
    SXD_SLSIR_RX_UGL_STATE_IDDQ_E = 0x0,
    SXD_SLSIR_RX_UGL_STATE_SLEEP_E = 0x1,
    SXD_SLSIR_RX_UGL_STATE_SPEED_CHANGE_E = 0x2,
    SXD_SLSIR_RX_UGL_STATE_POWERUP_E = 0x3,
    SXD_SLSIR_RX_UGL_STATE_CAL_E = 0x4,
    SXD_SLSIR_RX_UGL_STATE_WAIT_TERM_E = 0x5,
    SXD_SLSIR_RX_UGL_STATE_DATA_EN_RDY_E = 0x6,
    SXD_SLSIR_RX_UGL_STATE_DATA_EN_E = 0x7,
    SXD_SLSIR_RX_UGL_STATE_CDR_EN_E = 0x8,
    SXD_SLSIR_RX_UGL_STATE_ACTIVE_E = 0x9,
    SXD_SLSIR_RX_UGL_STATE_EQ_E = 0xa,
    SXD_SLSIR_RX_UGL_STATE_EOM_E = 0xb,
    SXD_SLSIR_RX_UGL_STATE_MIN = SXD_SLSIR_RX_UGL_STATE_IDDQ_E,
    SXD_SLSIR_RX_UGL_STATE_MAX = SXD_SLSIR_RX_UGL_STATE_EOM_E
} sxd_slsir_rx_ugl_state_t;


typedef enum sxd_slsir_rx_eom_ugl_state {
    SXD_SLSIR_RX_EOM_UGL_STATE_EOM_IDLE_E = 0x0,
    SXD_SLSIR_RX_EOM_UGL_STATE_EOM_DONE_WAIT1_E = 0x1,
    SXD_SLSIR_RX_EOM_UGL_STATE_EOM_DONE_WAIT0_E = 0x2,
    SXD_SLSIR_RX_EOM_UGL_STATE_EOM_DONE_E = 0x3,
    SXD_SLSIR_RX_EOM_UGL_STATE_MIN = SXD_SLSIR_RX_EOM_UGL_STATE_EOM_IDLE_E,
    SXD_SLSIR_RX_EOM_UGL_STATE_MAX = SXD_SLSIR_RX_EOM_UGL_STATE_EOM_DONE_E
} sxd_slsir_rx_eom_ugl_state_t;


typedef enum sxd_slsir_ae_state {
    SXD_SLSIR_AE_STATE_AE_STATE_RESET_E = 0x0,
    SXD_SLSIR_AE_STATE_AE_STATE_INIT_E = 0x1,
    SXD_SLSIR_AE_STATE_AE_STATE_IDLE_E = 0x2,
    SXD_SLSIR_AE_STATE_AE_STATE_HALT_E = 0x3,
    SXD_SLSIR_AE_STATE_AE_STATE_RXINIT_E = 0x4,
    SXD_SLSIR_AE_STATE_AE_STATE_RXINIT_DONE_E = 0x5,
    SXD_SLSIR_AE_STATE_AE_STATE_RXINIT_ABORT_E = 0x6,
    SXD_SLSIR_AE_STATE_AE_STATE_CDR_SEQ_E = 0x7,
    SXD_SLSIR_AE_STATE_AE_STATE_CDR_SEQ_DONE_E = 0x8,
    SXD_SLSIR_AE_STATE_AE_STATE_CDR_SEQ_ABORT_E = 0x9,
    SXD_SLSIR_AE_STATE_AE_STATE_CAL_E = 0xa,
    SXD_SLSIR_AE_STATE_AE_STATE_CAL_DONE_E = 0xb,
    SXD_SLSIR_AE_STATE_AE_STATE_CAL_ABORT_E = 0xc,
    SXD_SLSIR_AE_STATE_AE_STATE_FEQTRN_E = 0xd,
    SXD_SLSIR_AE_STATE_AE_STATE_PEQTRN_E = 0xe,
    SXD_SLSIR_AE_STATE_AE_STATE_EQTRN_DONE_E = 0xf,
    SXD_SLSIR_AE_STATE_AE_STATE_EQTRN_ABORT_E = 0x10,
    SXD_SLSIR_AE_STATE_AE_STATE_EOM_E = 0x11,
    SXD_SLSIR_AE_STATE_AE_STATE_EOM_DONE_E = 0x12,
    SXD_SLSIR_AE_STATE_AE_STATE_EOM_ABORT_E = 0x13,
    SXD_SLSIR_AE_STATE_AE_STATE_RAMP_E = 0x14,
    SXD_SLSIR_AE_STATE_AE_STATE_RAMP_ABORT_E = 0x15,
    SXD_SLSIR_AE_STATE_AE_STATE_MARGIN_E = 0x16,
    SXD_SLSIR_AE_STATE_AE_STATE_MARGIN_YIELD_E = 0x17,
    SXD_SLSIR_AE_STATE_AE_STATE_MARGIN_DONE_E = 0x18,
    SXD_SLSIR_AE_STATE_MIN = SXD_SLSIR_AE_STATE_AE_STATE_RESET_E,
    SXD_SLSIR_AE_STATE_MAX = SXD_SLSIR_AE_STATE_AE_STATE_MARGIN_DONE_E
} sxd_slsir_ae_state_t;

/**
 * ku_slsir_reg structure is used to store the SLSIR register parameters
 */
struct ku_slsir_reg {
    uint8_t status;
    uint8_t version;
    uint8_t local_port;
    uint8_t pnat;
    uint8_t lp_msb;
    uint8_t lane;
    uint8_t port_type;
    uint8_t nop_rsunf_error;
    uint8_t nop_rsovf_error;
    uint8_t nop_dsunf_error;
    uint8_t nop_dsovf_error;
    uint8_t peq_adc_overload;
    uint8_t feq_adc_overload;
    uint8_t cdr_error;
    uint8_t imem_chksm_error;
    sxd_slsir_rx_ugl_state_t rx_ugl_state;
    sxd_slsir_rx_eom_ugl_state_t rx_eom_ugl_state;
    uint8_t rx_cal_ugl_state;
    uint8_t rx_eq_ugl_state;
    uint8_t tx_ugl_state;
    uint8_t imem_loading_retries;
    uint8_t sd_hits_cnt;
    uint8_t sd_iter_cnt;
    uint8_t rd_iter_cnt;
    sxd_slsir_ae_state_t ae_state;
    uint8_t rx_init_abort_cnt;
    uint8_t rx_init_done_cnt;
    uint8_t cdr_abort_cnt;
    uint8_t cdr_done_cnt;
    uint8_t cal_abort_cnt;
    uint8_t cal_done_cnt;
    uint8_t eq_abort_cnt;
    uint8_t eq_done_cnt;
    uint8_t eom_abort_cnt;
    uint8_t eom_done_cnt;
};

/**
 * ku_access_slsir_reg structure is used to store the access register SLSIR command parameters
 */
struct ku_access_slsir_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_slsir_reg     slsir_reg; /**< slsir_reg - slsir register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_REIV_ELPORT_RECORD_NUM 256

typedef struct sxd_reiv_elport_record {
    uint8_t update;
    uint16_t evid;
} sxd_reiv_elport_record_t;

/**
 * ku_reiv_reg structure is used to store the REIV register parameters
 */
struct ku_reiv_reg {
    uint8_t port_page;
    uint16_t erif;
    sxd_reiv_elport_record_t elport_record[SXD_REIV_ELPORT_RECORD_NUM];
};

/**
 * ku_access_reiv_reg structure is used to store the access register REIV command parameters
 */
struct ku_access_reiv_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_reiv_reg      reiv_reg; /**< reiv_reg - reiv register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_PPAD_MAC_NUM 6


typedef enum sxd_ppad_pnat {
    SXD_PPAD_PNAT_LOCAL_PORT_NUMBER_E = 0x0,
    SXD_PPAD_PNAT_OUT_OF_BAND_E = 0x3,
    SXD_PPAD_PNAT_MIN = SXD_PPAD_PNAT_LOCAL_PORT_NUMBER_E,
    SXD_PPAD_PNAT_MAX = SXD_PPAD_PNAT_OUT_OF_BAND_E
} sxd_ppad_pnat_t;

/**
 * ku_ppad_reg structure is used to store the PPAD register parameters
 */
struct ku_ppad_reg {
    uint8_t single_base_mac;
    sxd_ppad_pnat_t pnat;
    uint8_t lp_msb;
    uint8_t local_port;
    uint8_t mac[SXD_PPAD_MAC_NUM];
};

/**
 * ku_access_ppad_reg structure is used to store the access register PPAD command parameters
 */
struct ku_access_ppad_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ppad_reg      ppad_reg; /**< ppad_reg - ppad register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

typedef struct sxd_prei_page_data {
    uint16_t mixer_offset0;
    uint16_t mixer_offset1;
} sxd_prei_page_data_t;

/**
 * ku_prei_reg structure is used to store the PREI register parameters
 */
struct ku_prei_reg {
    uint8_t version;
    uint8_t local_port;
    uint8_t pnat;
    uint8_t lp_msb;
    uint8_t ber_sel;
    uint8_t status;
    uint8_t en;
    uint8_t ber_mantissa;
    uint8_t ber_exp;
    uint16_t lane_rate_cap;
    sxd_prei_page_data_t page_data;
};

/**
 * ku_access_prei_reg structure is used to store the access register PREI command parameters
 */
struct ku_access_prei_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_prei_reg      prei_reg; /**< prei_reg - prei register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MOCS_PORT_MASK_NUM 16

#define SXD_MOCS_GRP_MASK_NUM 4


typedef enum sxd_mocs_type {
    SXD_MOCS_TYPE_PPCNT_SES1_E = 0x1,
    SXD_MOCS_TYPE_MGPCB_E = 0x2,
    SXD_MOCS_TYPE_PBSR_E = 0x3,
    SXD_MOCS_TYPE_SBSRD_E = 0x4,
    SXD_MOCS_TYPE_CEER_E = 0x5,
    SXD_MOCS_TYPE_MAFBI_E = 0x6,
    SXD_MOCS_TYPE_USACN_E = 0xa,
    SXD_MOCS_TYPE_UTCC_E = 0xb,
    SXD_MOCS_TYPE_UPCNT_E = 0xc,
    SXD_MOCS_TYPE_MIN = SXD_MOCS_TYPE_PPCNT_SES1_E,
    SXD_MOCS_TYPE_MAX = SXD_MOCS_TYPE_UPCNT_E
} sxd_mocs_type_t;


typedef enum sxd_mocs_status {
    SXD_MOCS_STATUS_IDLE_E = 0x0,
    SXD_MOCS_STATUS_BUSY_E = 0x1,
    SXD_MOCS_STATUS_CANCELED_E = 0x2,
    SXD_MOCS_STATUS_MIN = SXD_MOCS_STATUS_IDLE_E,
    SXD_MOCS_STATUS_MAX = SXD_MOCS_STATUS_CANCELED_E
} sxd_mocs_status_t;

typedef struct sxd_mocs_event_tid {
    uint32_t hi;
    uint32_t lo;
} sxd_mocs_event_tid_t;

typedef struct sxd_mocs_mocs_ppcnt {
    uint32_t port_mask[SXD_MOCS_PORT_MASK_NUM];
    uint32_t grp_mask[SXD_MOCS_GRP_MASK_NUM];
    uint32_t tc_mask;
    uint16_t prio_mask;
    uint16_t rx_buffer_mask;
} sxd_mocs_mocs_ppcnt_t;

typedef struct sxd_mocs_mocs_mgpcb {
    uint8_t flush;
    uint32_t num_rec;
    uint32_t counter_index_base;
} sxd_mocs_mocs_mgpcb_t;

typedef struct sxd_mocs_mocs_pbsr {
    uint32_t port_mask[SXD_MOCS_PORT_MASK_NUM];
} sxd_mocs_mocs_pbsr_t;

typedef struct sxd_mocs_mocs_sbsrd {
    uint8_t curr;
    uint8_t snap;
    uint8_t cells;
    uint8_t desc;
} sxd_mocs_mocs_sbsrd_t;

typedef struct sxd_mocs_mocs_ceer {
    uint32_t port_mask[SXD_MOCS_PORT_MASK_NUM];
} sxd_mocs_mocs_ceer_t;

typedef struct sxd_mocs_mocs_mafbi {
    uint8_t flush;
    uint8_t type;
    uint32_t num_rec;
    uint32_t counter_index_base;
} sxd_mocs_mocs_mafbi_t;

typedef struct sxd_mocs_mocs_usacn {
    uint32_t port_mask[SXD_MOCS_PORT_MASK_NUM];
    uint8_t side;
    uint16_t sadb_entry_index_base;
    uint16_t num_rec;
} sxd_mocs_mocs_usacn_t;

typedef struct sxd_mocs_mocs_utcc {
    uint32_t port_mask[SXD_MOCS_PORT_MASK_NUM];
    uint8_t side;
    uint8_t utcam_counter_idx_base;
    uint8_t num_rec;
} sxd_mocs_mocs_utcc_t;

typedef struct sxd_mocs_mocs_upcnt {
    uint32_t port_mask[SXD_MOCS_PORT_MASK_NUM];
} sxd_mocs_mocs_upcnt_t;

union mocs_entry {
    sxd_mocs_mocs_ppcnt_t mocs_ppcnt;
    sxd_mocs_mocs_mgpcb_t mocs_mgpcb;
    sxd_mocs_mocs_pbsr_t mocs_pbsr;
    sxd_mocs_mocs_sbsrd_t mocs_sbsrd;
    sxd_mocs_mocs_ceer_t mocs_ceer;
    sxd_mocs_mocs_mafbi_t mocs_mafbi;
    sxd_mocs_mocs_usacn_t mocs_usacn;
    sxd_mocs_mocs_utcc_t mocs_utcc;
    sxd_mocs_mocs_upcnt_t mocs_upcnt;
};

/**
 * ku_mocs_reg structure is used to store the MOCS register parameters
 */
struct ku_mocs_reg {
    sxd_mocs_type_t type;
    uint8_t clear;
    uint8_t opcode;
    sxd_mocs_status_t status;
    sxd_mocs_event_tid_t event_tid;
    union mocs_entry entry;
};

/**
 * ku_access_mocs_reg structure is used to store the access register MOCS command parameters
 */
struct ku_access_mocs_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mocs_reg      mocs_reg; /**< mocs_reg - mocs register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_IPAC_PORT_MASK_NUM 32


typedef enum sxd_ipac_status {
    SXD_IPAC_STATUS_IDLE_E = 0x0,
    SXD_IPAC_STATUS_BUSY_E = 0x1,
    SXD_IPAC_STATUS_CANCELED_E = 0x2,
    SXD_IPAC_STATUS_ERROR_E = 0x3,
    SXD_IPAC_STATUS_MIN = SXD_IPAC_STATUS_IDLE_E,
    SXD_IPAC_STATUS_MAX = SXD_IPAC_STATUS_ERROR_E
} sxd_ipac_status_t;

/**
 * ku_ipac_reg structure is used to store the IPAC register parameters
 */
struct ku_ipac_reg {
    uint8_t profile_index;
    uint8_t opcode;
    sxd_ipac_status_t status;
    uint32_t port_mask[SXD_IPAC_PORT_MASK_NUM];
    uint16_t log_op_time;
    uint32_t log_op_registers;
    uint8_t error_lp_msb;
    uint8_t error_local_port;
    uint16_t error_register_id;
    uint8_t error_status;
    uint16_t error_entry_index;
};

/**
 * ku_access_ipac_reg structure is used to store the access register IPAC command parameters
 */
struct ku_access_ipac_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ipac_reg      ipac_reg; /**< ipac_reg - ipac register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_pllp_reg structure is used to store the PLLP register parameters
 */
struct ku_pllp_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint16_t label_port;
    uint8_t split_stat;
    uint8_t split_num;
    uint8_t slot_num;
};

/**
 * ku_access_pllp_reg structure is used to store the access register PLLP command parameters
 */
struct ku_access_pllp_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pllp_reg      pllp_reg; /**< pllp_reg - pllp register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_SPAD_BASE_MAC_NUM 6

/**
 * ku_spad_reg structure is used to store the SPAD register parameters
 */
struct ku_spad_reg {
    uint8_t base_mac[SXD_SPAD_BASE_MAC_NUM];
};

/**
 * ku_access_spad_reg structure is used to store the access register SPAD command parameters
 */
struct ku_access_spad_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_spad_reg      spad_reg; /**< spad_reg - spad register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_qeec_element_hierarchy {
    SXD_QEEC_ELEMENT_HIERARCHY_PORT_E = 0x0,
    SXD_QEEC_ELEMENT_HIERARCHY_GROUP_E = 0x1,
    SXD_QEEC_ELEMENT_HIERARCHY_SUB_GROUP_E = 0x2,
    SXD_QEEC_ELEMENT_HIERARCHY_TRAFFIC_CLASS_E = 0x3,
    SXD_QEEC_ELEMENT_HIERARCHY_MIN = SXD_QEEC_ELEMENT_HIERARCHY_PORT_E,
    SXD_QEEC_ELEMENT_HIERARCHY_MAX = SXD_QEEC_ELEMENT_HIERARCHY_TRAFFIC_CLASS_E
} sxd_qeec_element_hierarchy_t;


typedef enum sxd_qeec_mise {
    SXD_QEEC_MISE_DISABLE_E = 0x0,
    SXD_QEEC_MISE_ENABLE_E = 0x1,
    SXD_QEEC_MISE_MIN = SXD_QEEC_MISE_DISABLE_E,
    SXD_QEEC_MISE_MAX = SXD_QEEC_MISE_ENABLE_E
} sxd_qeec_mise_t;


typedef enum sxd_qeec_mase {
    SXD_QEEC_MASE_DISABLE_E = 0x0,
    SXD_QEEC_MASE_ENABLE_E = 0x1,
    SXD_QEEC_MASE_MIN = SXD_QEEC_MASE_DISABLE_E,
    SXD_QEEC_MASE_MAX = SXD_QEEC_MASE_ENABLE_E
} sxd_qeec_mase_t;

/**
 * ku_qeec_reg structure is used to store the QEEC register parameters
 */
struct ku_qeec_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    sxd_qeec_element_hierarchy_t element_hierarchy;
    uint8_t element_index;
    uint8_t next_element_index;
    sxd_qeec_mise_t mise;
    uint8_t ptps;
    uint8_t pb;
    uint32_t min_shaper_rate;
    sxd_qeec_mase_t mase;
    uint32_t max_shaper_rate;
    uint8_t pqe;
    uint32_t phantom_queue_rate;
    uint8_t de;
    uint8_t dwrr;
    uint8_t dwrr_weight;
    uint8_t min_shaper_bs;
    uint8_t max_shaper_bs;
};

/**
 * ku_access_qeec_reg structure is used to store the access register QEEC command parameters
 */
struct ku_access_qeec_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qeec_reg      qeec_reg; /**< qeec_reg - qeec register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_RLCMLE_DIP_NUM 4


typedef enum sxd_rlcmle_action_type {
    SXD_RLCMLE_ACTION_TYPE_REMOTE_E = 0x0,
    SXD_RLCMLE_ACTION_TYPE_LOCAL_E = 0x1,
    SXD_RLCMLE_ACTION_TYPE_IP2ME_E = 0x2,
    SXD_RLCMLE_ACTION_TYPE_MIN = SXD_RLCMLE_ACTION_TYPE_REMOTE_E,
    SXD_RLCMLE_ACTION_TYPE_MAX = SXD_RLCMLE_ACTION_TYPE_IP2ME_E
} sxd_rlcmle_action_type_t;

typedef struct sxd_rlcmle_remote_action {
    uint8_t trap_action;
    uint16_t trap_id;
    uint32_t adjacency_index;
    uint16_t ecmp_size;
} sxd_rlcmle_remote_action_t;

typedef struct sxd_rlcmle_local_action {
    uint8_t trap_action;
    uint16_t trap_id;
    uint16_t local_erif;
} sxd_rlcmle_local_action_t;

typedef struct sxd_rlcmle_ip2me {
    uint8_t trap_action;
    uint8_t v;
    uint32_t tunnel_ptr;
} sxd_rlcmle_ip2me_t;

union rlcmle_action {
    sxd_rlcmle_remote_action_t remote_action;
    sxd_rlcmle_local_action_t local_action;
    sxd_rlcmle_ip2me_t ip2me;
};

/**
 * ku_rlcmle_reg structure is used to store the RLCMLE register parameters
 */
struct ku_rlcmle_reg {
    uint8_t protocol;
    uint8_t op;
    uint8_t m_idx;
    uint16_t virtual_router;
    uint8_t l_value;
    uint32_t dip[SXD_RLCMLE_DIP_NUM];
    sxd_rlcmle_action_type_t action_type;
    union rlcmle_action action;
    uint8_t counter_set_type;
    uint32_t counter_index;
};

/**
 * ku_access_rlcmle_reg structure is used to store the access register RLCMLE command parameters
 */
struct ku_access_rlcmle_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rlcmle_reg    rlcmle_reg; /**< rlcmle_reg - rlcmle register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_sbsnt_reg structure is used to store the SBSNT register parameters
 */
struct ku_sbsnt_reg {
    uint8_t take;
};

/**
 * ku_access_sbsnt_reg structure is used to store the access register SBSNT command parameters
 */
struct ku_access_sbsnt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbsnt_reg     sbsnt_reg; /**< sbsnt_reg - sbsnt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_rarft_reg structure is used to store the RARFT register parameters
 */
struct ku_rarft_reg {
    uint32_t arft_index;
    uint8_t arft_entry_in_row;
    uint8_t valid;
    uint8_t lp_msb;
    uint8_t local_port;
    uint8_t ar_prof_id;
};

/**
 * ku_access_rarft_reg structure is used to store the access register RARFT command parameters
 */
struct ku_access_rarft_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rarft_reg     rarft_reg; /**< rarft_reg - rarft register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MCQI_VERSION_STRING_NUM 92


typedef enum sxd_mcqi_info_type {
    SXD_MCQI_INFO_TYPE_CAPABILITIES_E = 0x0,
    SXD_MCQI_INFO_TYPE_VERSION_E = 0x1,
    SXD_MCQI_INFO_TYPE_ACTIVATION_METHOD_E = 0x5,
    SXD_MCQI_INFO_TYPE_LINKX_PROPERTIES_E = 0x6,
    SXD_MCQI_INFO_TYPE_MIN = SXD_MCQI_INFO_TYPE_CAPABILITIES_E,
    SXD_MCQI_INFO_TYPE_MAX = SXD_MCQI_INFO_TYPE_LINKX_PROPERTIES_E
} sxd_mcqi_info_type_t;

typedef struct sxd_mcqi_mcqi_cap {
    uint32_t supported_info_bitmask;
    uint32_t component_size;
    uint32_t max_component_size;
    uint8_t log_mcda_word_size;
    uint16_t mcda_max_write_size;
    uint8_t rd_en;
    uint8_t signed_updates_only;
    uint8_t match_chip_id;
    uint8_t match_psid;
    uint8_t check_user_timestamp;
    uint8_t match_base_guid_mac;
} sxd_mcqi_mcqi_cap_t;

typedef struct sxd_mcqi_build_time {
    uint32_t hi;
    uint32_t lo;
} sxd_mcqi_build_time_t;

typedef struct sxd_mcqi_user_defined_time {
    uint32_t hi;
    uint32_t lo;
} sxd_mcqi_user_defined_time_t;

typedef struct sxd_mcqi_mcqi_version {
    uint8_t build_time_valid;
    uint8_t user_defined_time_valid;
    uint8_t version_string_length;
    uint32_t version;
    sxd_mcqi_build_time_t build_time;
    sxd_mcqi_user_defined_time_t user_defined_time;
    uint32_t build_tool_version;
    uint8_t version_string[SXD_MCQI_VERSION_STRING_NUM];
} sxd_mcqi_mcqi_version_t;

typedef struct sxd_mcqi_mcqi_activation_method {
    uint8_t self_activation;
    uint8_t pending_server_ac_power_cycle;
    uint8_t pending_server_dc_power_cycle;
    uint8_t pending_server_reboot;
    uint8_t pending_fw_reset;
    uint8_t auto_activate;
    uint8_t all_hosts_sync;
} sxd_mcqi_mcqi_activation_method_t;

typedef struct sxd_mcqi_mcqi_linkx_properties {
    uint8_t fw_image_info_bitmap;
    uint8_t fw_image_status_bitmap;
    uint8_t image_a_major;
    uint8_t image_a_minor;
    uint16_t image_a_subminor;
    uint8_t image_b_major;
    uint8_t image_b_minor;
    uint16_t image_b_subminor;
    uint8_t factory_image_major;
    uint8_t factory_image_minor;
    uint16_t factory_image_subminor;
    uint8_t activation_type;
    uint8_t management_interface_protocol;
    uint16_t vendor_sn;
} sxd_mcqi_mcqi_linkx_properties_t;

union mcqi_data {
    sxd_mcqi_mcqi_cap_t mcqi_cap;
    sxd_mcqi_mcqi_version_t mcqi_version;
    sxd_mcqi_mcqi_activation_method_t mcqi_activation_method;
    sxd_mcqi_mcqi_linkx_properties_t mcqi_linkx_properties;
};

/**
 * ku_mcqi_reg structure is used to store the MCQI register parameters
 */
struct ku_mcqi_reg {
    uint8_t read_pending_component;
    uint16_t device_index;
    uint16_t component_index;
    uint8_t device_type;
    sxd_mcqi_info_type_t info_type;
    uint32_t info_size;
    uint32_t offset;
    uint16_t data_size;
    union mcqi_data data;
};

/**
 * ku_access_mcqi_reg structure is used to store the access register MCQI command parameters
 */
struct ku_access_mcqi_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mcqi_reg      mcqi_reg; /**< mcqi_reg - mcqi register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_chltr_reg structure is used to store the CHLTR register parameters
 */
struct ku_chltr_reg {
    uint8_t hlt_table_index;
    uint32_t high_latency_thr;
};

/**
 * ku_access_chltr_reg structure is used to store the access register CHLTR command parameters
 */
struct ku_access_chltr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_chltr_reg     chltr_reg; /**< chltr_reg - chltr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_rarsr_reg structure is used to store the RARSR register parameters
 */
struct ku_rarsr_reg {
    uint16_t ar_srf;
    uint16_t ar_srt;
};

/**
 * ku_access_rarsr_reg structure is used to store the access register RARSR command parameters
 */
struct ku_access_rarsr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rarsr_reg     rarsr_reg; /**< rarsr_reg - rarsr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_RATRB_DESTINATION_MAC_NUM 6


typedef enum sxd_ratrb_type {
    SXD_RATRB_TYPE_ETHERNET_E = 0x0,
    SXD_RATRB_TYPE_MPLS_E = 0x4,
    SXD_RATRB_TYPE_IPINIP_ENCAP_E = 0x5,
    SXD_RATRB_TYPE_L3_GENERIC_ENCAP_E = 0x6,
    SXD_RATRB_TYPE_RELOOKUPECMP_E = 0x8,
    SXD_RATRB_TYPE_RELOOKUPLPM_E = 0x9,
    SXD_RATRB_TYPE_MIN = SXD_RATRB_TYPE_ETHERNET_E,
    SXD_RATRB_TYPE_MAX = SXD_RATRB_TYPE_RELOOKUPLPM_E
} sxd_ratrb_type_t;

#define SXD_RATRB_RECORD_NUM 32


typedef enum sxd_ratrb_trap_action {
    SXD_RATRB_TRAP_ACTION_NOP_E = 0x0,
    SXD_RATRB_TRAP_ACTION_TRAP_E = 0x1,
    SXD_RATRB_TRAP_ACTION_MIRROR_TO_CPU_E = 0x2,
    SXD_RATRB_TRAP_ACTION_MIRROR_E = 0x3,
    SXD_RATRB_TRAP_ACTION_DISCARD_ERROR_E = 0x4,
    SXD_RATRB_TRAP_ACTION_MIN = SXD_RATRB_TRAP_ACTION_NOP_E,
    SXD_RATRB_TRAP_ACTION_MAX = SXD_RATRB_TRAP_ACTION_DISCARD_ERROR_E
} sxd_ratrb_trap_action_t;

typedef struct sxd_ratrb_eth_adjacency {
    uint8_t destination_mac[SXD_RATRB_DESTINATION_MAC_NUM];
} sxd_ratrb_eth_adjacency_t;

typedef struct sxd_ratrb_mpls_adjacency {
    uint32_t nhlfe_ptr;
    uint8_t tqos_profile;
    uint16_t ecmp_size;
    uint16_t underlay_router_interface;
} sxd_ratrb_mpls_adjacency_t;

typedef struct sxd_ratrb_ipinip_encap_adjacency {
    uint8_t ipip_type;
    uint8_t tqos_profile_en;
    uint8_t tqos_profile;
    uint8_t uirif_v;
    uint16_t uirif;
    uint32_t ipv4_udip;
    uint32_t ipv6_ptr;
} sxd_ratrb_ipinip_encap_adjacency_t;

typedef struct sxd_ratrb_l3_generic_encap_adjacency {
    uint8_t u_ip_ver;
    uint8_t emt_pointer;
    uint8_t tqos_profile;
    uint16_t uirif;
    uint32_t ipv4_udip;
    uint32_t ipv6_ptr;
    uint8_t cbset_x_select;
    uint8_t cbset_y_select;
    uint8_t cbset_x_set_en;
    uint8_t cbset_y_set_en;
    uint16_t cbset_x_val;
    uint16_t cbset_y_val;
} sxd_ratrb_l3_generic_encap_adjacency_t;

typedef struct sxd_ratrb_relookup_ecmp_adjacency {
    uint32_t next_adjacency_ptr;
    uint16_t next_ecmp_size;
    uint8_t rd;
    uint16_t rehash_seed;
} sxd_ratrb_relookup_ecmp_adjacency_t;

typedef struct sxd_ratrb_relookup_lpm_adjacency {
    uint16_t virtual_router;
    uint8_t rd;
    uint16_t rehash_seed;
} sxd_ratrb_relookup_lpm_adjacency_t;

union ratrb_adjacency_parameters {
    sxd_ratrb_eth_adjacency_t eth_adjacency;
    sxd_ratrb_mpls_adjacency_t mpls_adjacency;
    sxd_ratrb_ipinip_encap_adjacency_t ipinip_encap_adjacency;
    sxd_ratrb_l3_generic_encap_adjacency_t l3_generic_encap_adjacency;
    sxd_ratrb_relookup_ecmp_adjacency_t relookup_ecmp_adjacency;
    sxd_ratrb_relookup_lpm_adjacency_t relookup_lpm_adjacency;
};

typedef struct sxd_ratrb_record {
    sxd_ratrb_type_t type;
    uint16_t size;
    uint16_t egress_router_interface;
    uint8_t counter_set_type;
    uint32_t counter_index;
    union ratrb_adjacency_parameters adjacency_parameters;
} sxd_ratrb_record_t;

/**
 * ku_ratrb_reg structure is used to store the RATRB register parameters
 */
struct ku_ratrb_reg {
    uint8_t v;
    uint32_t adjacency_index;
    uint8_t num_rec;
    sxd_ratrb_trap_action_t trap_action;
    uint16_t trap_id;
    sxd_ratrb_record_t record[SXD_RATRB_RECORD_NUM];
};

/**
 * ku_access_ratrb_reg structure is used to store the access register RATRB command parameters
 */
struct ku_access_ratrb_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ratrb_reg     ratrb_reg; /**< ratrb_reg - ratrb register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_TNGCR_USIPV6_NUM 4

/**
 * ku_tngcr_reg structure is used to store the TNGCR register parameters
 */
struct ku_tngcr_reg {
    uint8_t type;
    uint8_t nve_valid;
    uint8_t nve_decap_ttl;
    uint8_t nve_ttlc;
    uint8_t nve_ttl_uc;
    uint8_t nve_ttl_mc;
    uint8_t nve_flc;
    uint8_t nve_flh;
    uint16_t nve_fl_prefix;
    uint8_t nve_fl_suffix;
    uint8_t nve_enc_orig;
    uint8_t nve_enc_orig_we;
    uint8_t nve_udp_sport_type;
    uint8_t et_vlan;
    uint8_t nve_udp_sport_prefix;
    uint8_t nve_udp_sport_suffix;
    uint8_t nve_group_size_mc;
    uint8_t nve_group_size_flood;
    uint8_t learn_enable;
    uint16_t underlay_virtual_router;
    uint16_t underlay_rif;
    uint32_t usipv4;
    uint32_t usipv6[SXD_TNGCR_USIPV6_NUM];
    uint32_t header0_bit_set;
};

/**
 * ku_access_tngcr_reg structure is used to store the access register TNGCR command parameters
 */
struct ku_access_tngcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tngcr_reg     tngcr_reg; /**< tngcr_reg - tngcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_molp_reg structure is used to store the MOLP register parameters
 */
struct ku_molp_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint16_t label_port;
};

/**
 * ku_access_molp_reg structure is used to store the access register MOLP command parameters
 */
struct ku_access_molp_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_molp_reg      molp_reg; /**< molp_reg - molp register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_qtttl_reg structure is used to store the QTTTL register parameters
 */
struct ku_qtttl_reg {
    uint8_t tqos_profile;
    uint8_t decap_ttl;
    uint8_t enc_ttlc;
    uint8_t enc_ttl_uc;
    uint8_t enc_ttl_mc;
};

/**
 * ku_access_qtttl_reg structure is used to store the access register QTTTL command parameters
 */
struct ku_access_qtttl_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qtttl_reg     qtttl_reg; /**< qtttl_reg - qtttl register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

typedef struct sxd_ptasv2_page_data {
    uint8_t tuning_type_support;
    uint8_t tuning_type_admin;
} sxd_ptasv2_page_data_t;

/**
 * ku_ptasv2_reg structure is used to store the PTASV2 register parameters
 */
struct ku_ptasv2_reg {
    uint8_t version;
    uint8_t local_port;
    uint8_t pnat;
    uint8_t lp_msb;
    uint8_t ig_dme_mod_cap;
    uint8_t ig_dme_mod_admin;
    uint8_t force_an_cap;
    uint8_t force_an_admin;
    sxd_ptasv2_page_data_t page_data;
};

/**
 * ku_access_ptasv2_reg structure is used to store the access register PTASV2 command parameters
 */
struct ku_access_ptasv2_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ptasv2_reg    ptasv2_reg; /**< ptasv2_reg - ptasv2 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MDDT_REGISTER_DATA_NUM 64

#define SXD_MDDT_DATA_NUM 65


typedef enum sxd_mddt_type {
    SXD_MDDT_TYPE_PRM_REGISTER_E = 0x0,
    SXD_MDDT_TYPE_COMMAND_E = 0x1,
    SXD_MDDT_TYPE_CRSPACE_ACCESS_E = 0x2,
    SXD_MDDT_TYPE_MIN = SXD_MDDT_TYPE_PRM_REGISTER_E,
    SXD_MDDT_TYPE_MAX = SXD_MDDT_TYPE_CRSPACE_ACCESS_E
} sxd_mddt_type_t;

typedef struct sxd_mddt_prm_register_payload {
    uint8_t status;
    uint8_t method;
    uint16_t register_id;
    uint32_t register_data[SXD_MDDT_REGISTER_DATA_NUM];
} sxd_mddt_prm_register_payload_t;

typedef struct sxd_mddt_command_payload {
    uint32_t data[SXD_MDDT_DATA_NUM];
} sxd_mddt_command_payload_t;

typedef struct sxd_mddt_crspace_access_payload {
    uint32_t address;
    uint32_t data[SXD_MDDT_DATA_NUM];
} sxd_mddt_crspace_access_payload_t;

union mddt_payload {
    sxd_mddt_prm_register_payload_t prm_register_payload;
    sxd_mddt_command_payload_t command_payload;
    sxd_mddt_crspace_access_payload_t crspace_access_payload;
};

/**
 * ku_mddt_reg structure is used to store the MDDT register parameters
 */
struct ku_mddt_reg {
    uint8_t slot_index;
    uint8_t device_index;
    uint8_t read_size;
    uint8_t write_size;
    sxd_mddt_type_t type;
    union mddt_payload payload;
};

/**
 * ku_access_mddt_reg structure is used to store the access register MDDT command parameters
 */
struct ku_access_mddt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mddt_reg      mddt_reg; /**< mddt_reg - mddt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_RIPS_IPV6_NUM 4

/**
 * ku_rips_reg structure is used to store the RIPS register parameters
 */
struct ku_rips_reg {
    uint32_t index;
    uint32_t ipv6[SXD_RIPS_IPV6_NUM];
};

/**
 * ku_access_rips_reg structure is used to store the access register RIPS command parameters
 */
struct ku_access_rips_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rips_reg      rips_reg; /**< rips_reg - rips register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_tndem_reg structure is used to store the TNDEM register parameters
 */
struct ku_tndem_reg {
    uint8_t underlay_ecn;
    uint8_t overlay_ecn;
    uint8_t eip_ecn;
    uint8_t trap_en;
    uint16_t trap_id;
};

/**
 * ku_access_tndem_reg structure is used to store the access register TNDEM command parameters
 */
struct ku_access_tndem_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tndem_reg     tndem_reg; /**< tndem_reg - tndem register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MAFBI_RECORD_NUM 64


typedef enum sxd_mafbi_type {
    SXD_MAFBI_TYPE_ENTRY_TYPE0_E = 0x0,
    SXD_MAFBI_TYPE_MIN = SXD_MAFBI_TYPE_ENTRY_TYPE0_E,
    SXD_MAFBI_TYPE_MAX = SXD_MAFBI_TYPE_ENTRY_TYPE0_E
} sxd_mafbi_type_t;

typedef struct sxd_mafbi_record {
    uint32_t counter_index;
    uint32_t bytes_inc;
    uint32_t packets_inc;
} sxd_mafbi_record_t;

typedef struct sxd_mafbi_mafbi_entry_type0 {
    sxd_mafbi_record_t record[SXD_MAFBI_RECORD_NUM];
} sxd_mafbi_mafbi_entry_type0_t;

union mafbi_entry {
    sxd_mafbi_mafbi_entry_type0_t mafbi_entry_type0;
};

/**
 * ku_mafbi_reg structure is used to store the MAFBI register parameters
 */
struct ku_mafbi_reg {
    sxd_mafbi_type_t type;
    uint8_t num_rec;
    union mafbi_entry entry;
};

/**
 * ku_access_mafbi_reg structure is used to store the access register MAFBI command parameters
 */
struct ku_access_mafbi_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mafbi_reg     mafbi_reg; /**< mafbi_reg - mafbi register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_PIFR_V2_PORT_FILTER_NUM 32

#define SXD_PIFR_V2_PORT_FILTER_UPDATE_EN_NUM 32

/**
 * ku_pifr_v2_reg structure is used to store the PIFR_V2 register parameters
 */
struct ku_pifr_v2_reg {
    uint8_t table_id;
    uint8_t local_port;
    uint8_t lp_msb;
    uint32_t port_filter[SXD_PIFR_V2_PORT_FILTER_NUM];
    uint32_t port_filter_update_en[SXD_PIFR_V2_PORT_FILTER_UPDATE_EN_NUM];
};

/**
 * ku_access_pifr_v2_reg structure is used to store the access register PIFR_V2 command parameters
 */
struct ku_access_pifr_v2_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pifr_v2_reg   pifr_v2_reg; /**< pifr_v2_reg - pifr_v2 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_RARPC_INGRESS_PORT_NUM 32

#define SXD_RARPC_L4PORT_CMP_NUM 4

typedef struct sxd_rarpc_l4port_cmp {
    uint16_t port_range_min;
    uint16_t port_range_max;
    uint8_t port_src;
    uint8_t comp_field;
} sxd_rarpc_l4port_cmp_t;

/**
 * ku_rarpc_reg structure is used to store the RARPC register parameters
 */
struct ku_rarpc_reg {
    uint8_t pc_default;
    uint8_t pc_entry;
    uint8_t l4_inner;
    uint8_t inner_must;
    uint8_t ar_packet_prof_id;
    uint16_t switch_prio;
    uint8_t l3_type;
    uint8_t inner_l3_type;
    uint8_t l4_type;
    uint8_t inner_l4_type;
    uint8_t bth_ar;
    uint8_t bth_opcode_msb;
    uint32_t bth_opcode_lsb;
    uint8_t inner_bth_ar;
    uint8_t inner_bth_opcode_msb;
    uint32_t inner_bth_opcode_lsb;
    uint32_t ingress_port[SXD_RARPC_INGRESS_PORT_NUM];
    sxd_rarpc_l4port_cmp_t l4port_cmp[SXD_RARPC_L4PORT_CMP_NUM];
};

/**
 * ku_access_rarpc_reg structure is used to store the access register RARPC command parameters
 */
struct ku_access_rarpc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rarpc_reg     rarpc_reg; /**< rarpc_reg - rarpc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_SFDB_V2_KEY_NUM 8

#define SXD_SFDB_V2_KEY_MASK_NUM 8

#define SXD_SFDB_V2_ACTION_NUM 8

#define SXD_SFDB_V2_ACTION_MASK_NUM 8

/**
 * ku_sfdb_v2_reg structure is used to store the SFDB_V2 register parameters
 */
struct ku_sfdb_v2_reg {
    uint32_t key[SXD_SFDB_V2_KEY_NUM];
    uint32_t key_mask[SXD_SFDB_V2_KEY_MASK_NUM];
    uint32_t action[SXD_SFDB_V2_ACTION_NUM];
    uint32_t action_mask[SXD_SFDB_V2_ACTION_MASK_NUM];
    uint32_t count_updates;
};

/**
 * ku_access_sfdb_v2_reg structure is used to store the access register SFDB_V2 command parameters
 */
struct ku_access_sfdb_v2_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sfdb_v2_reg   sfdb_v2_reg; /**< sfdb_v2_reg - sfdb_v2 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_TNUMT_UDIP_NUM 3

#define SXD_TNUMT_UDIP_PTR_NUM 5


typedef enum sxd_tnumt_record_type {
    SXD_TNUMT_RECORD_TYPE_IPV4_E = 0x0,
    SXD_TNUMT_RECORD_TYPE_IPV6_E = 0x1,
    SXD_TNUMT_RECORD_TYPE_MIN = SXD_TNUMT_RECORD_TYPE_IPV4_E,
    SXD_TNUMT_RECORD_TYPE_MAX = SXD_TNUMT_RECORD_TYPE_IPV6_E
} sxd_tnumt_record_type_t;

typedef struct sxd_tnumt_tunnel_mc_ipv4 {
    uint8_t size;
    uint32_t udip[SXD_TNUMT_UDIP_NUM];
} sxd_tnumt_tunnel_mc_ipv4_t;

typedef struct sxd_tnumt_udip_ptr {
    uint32_t udip_ptr;
} sxd_tnumt_udip_ptr_t;

typedef struct sxd_tnumt_tunnel_mc_ipv6 {
    uint8_t size;
    sxd_tnumt_udip_ptr_t udip_ptr[SXD_TNUMT_UDIP_PTR_NUM];
} sxd_tnumt_tunnel_mc_ipv6_t;

union tnumt_record {
    sxd_tnumt_tunnel_mc_ipv4_t tunnel_mc_ipv4;
    sxd_tnumt_tunnel_mc_ipv6_t tunnel_mc_ipv6;
};

/**
 * ku_tnumt_reg structure is used to store the TNUMT register parameters
 */
struct ku_tnumt_reg {
    sxd_tnumt_record_type_t record_type;
    uint32_t underlay_mc_ptr;
    uint8_t vnext;
    uint32_t next_underlay_mc_ptr;
    union tnumt_record record;
};

/**
 * ku_access_tnumt_reg structure is used to store the access register TNUMT command parameters
 */
struct ku_access_tnumt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tnumt_reg     tnumt_reg; /**< tnumt_reg - tnumt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_RLCME_DIP_NUM 4

#define SXD_RLCME_ACTION_NUM 5

/**
 * ku_rlcme_reg structure is used to store the RLCME register parameters
 */
struct ku_rlcme_reg {
    uint8_t protocol;
    uint8_t op;
    uint8_t m_idx;
    uint16_t virtual_router;
    uint32_t dip[SXD_RLCME_DIP_NUM];
    uint8_t action_type;
    uint32_t action[SXD_RLCME_ACTION_NUM];
    uint8_t counter_set_type;
    uint32_t counter_index;
    uint8_t action_valid;
    uint8_t l_vector;
    uint8_t l_value;
};

/**
 * ku_access_rlcme_reg structure is used to store the access register RLCME command parameters
 */
struct ku_access_rlcme_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rlcme_reg     rlcme_reg; /**< rlcme_reg - rlcme register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_fpts_reg structure is used to store the FPTS register parameters
 */
struct ku_fpts_reg {
    uint8_t global;
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t tran_type;
    uint8_t next_ph;
};

/**
 * ku_access_fpts_reg structure is used to store the access register FPTS command parameters
 */
struct ku_access_fpts_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_fpts_reg      fpts_reg; /**< fpts_reg - fpts register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_rarpr_reg structure is used to store the RARPR register parameters
 */
struct ku_rarpr_reg {
    uint8_t ar_prof_id;
    uint8_t prof_mode;
    uint8_t elph;
    uint8_t grade_thr_free;
    uint8_t grade_thr_busy;
    uint8_t srf;
    uint8_t srt;
    uint16_t time_bound_time;
};

/**
 * ku_access_rarpr_reg structure is used to store the access register RARPR command parameters
 */
struct ku_access_rarpr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rarpr_reg     rarpr_reg; /**< rarpr_reg - rarpr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

typedef struct sxd_htacg_fields {
    uint8_t mirror_reason;
    uint8_t rdq;
    uint16_t trap_id;
    uint8_t mirror_tclass;
    uint8_t mirror_tx_acl_system_port;
    uint16_t max_egress_buffer_fill_level;
    uint32_t last_ts;
    uint32_t pkt_count;
    uint8_t byte_count_high;
    uint32_t byte_count_low;
} sxd_htacg_fields_t;

typedef struct sxd_htacg_mask {
    uint8_t mirror_reason;
    uint8_t rdq;
    uint16_t trap_id;
    uint8_t mirror_tclass;
    uint8_t mirror_tx_acl_system_port;
    uint16_t max_egress_buffer_fill_level;
    uint32_t last_ts;
    uint32_t pkt_count;
    uint8_t byte_count_high;
    uint32_t byte_count_low;
} sxd_htacg_mask_t;

/**
 * ku_htacg_reg structure is used to store the HTACG register parameters
 */
struct ku_htacg_reg {
    uint8_t go;
    uint8_t grepper_index;
    uint8_t tac_flush;
    sxd_htacg_fields_t fields;
    sxd_htacg_mask_t mask;
};

/**
 * ku_access_htacg_reg structure is used to store the access register HTACG command parameters
 */
struct ku_access_htacg_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_htacg_reg     htacg_reg; /**< htacg_reg - htacg register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_pevpb_reg structure is used to store the PEVPB register parameters
 */
struct ku_pevpb_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t ev;
};

/**
 * ku_access_pevpb_reg structure is used to store the access register PEVPB command parameters
 */
struct ku_access_pevpb_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pevpb_reg     pevpb_reg; /**< pevpb_reg - pevpb register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_sfgc_type {
    SXD_SFGC_TYPE_BROADCAST_E = 0x0,
    SXD_SFGC_TYPE_UNKNOWN_UNICAST_E = 0x1,
    SXD_SFGC_TYPE_UNREGISTERED_MULTICAST_IPV4_E = 0x2,
    SXD_SFGC_TYPE_UNREGISTERED_MULTICAST_IPV6_E = 0x3,
    SXD_SFGC_TYPE_RESERVED_E = 0x4,
    SXD_SFGC_TYPE_UNREGISTERED_MULTICAST_NON_IP_E = 0x5,
    SXD_SFGC_TYPE_IPV4_LINK_LOCAL_E = 0x6,
    SXD_SFGC_TYPE_IPV6_ALL_HOSTS_E = 0x7,
    SXD_SFGC_TYPE_MIN = SXD_SFGC_TYPE_BROADCAST_E,
    SXD_SFGC_TYPE_MAX = SXD_SFGC_TYPE_IPV6_ALL_HOSTS_E
} sxd_sfgc_type_t;


typedef enum sxd_sfgc_bridge_type {
    SXD_SFGC_BRIDGE_TYPE_TYPE0_E = 0x0,
    SXD_SFGC_BRIDGE_TYPE_TYPE1_E = 0x1,
    SXD_SFGC_BRIDGE_TYPE_MIN = SXD_SFGC_BRIDGE_TYPE_TYPE0_E,
    SXD_SFGC_BRIDGE_TYPE_MAX = SXD_SFGC_BRIDGE_TYPE_TYPE1_E
} sxd_sfgc_bridge_type_t;


typedef enum sxd_sfgc_table_type {
    SXD_SFGC_TABLE_TYPE_ANY_TYPE_E = 0x0,
    SXD_SFGC_TABLE_TYPE_FID_E = 0x4,
    SXD_SFGC_TABLE_TYPE_MIN = SXD_SFGC_TABLE_TYPE_ANY_TYPE_E,
    SXD_SFGC_TABLE_TYPE_MAX = SXD_SFGC_TABLE_TYPE_FID_E
} sxd_sfgc_table_type_t;

/**
 * ku_sfgc_reg structure is used to store the SFGC register parameters
 */
struct ku_sfgc_reg {
    sxd_sfgc_type_t type;
    sxd_sfgc_bridge_type_t bridge_type;
    sxd_sfgc_table_type_t table_type;
    uint8_t flood_table;
    uint8_t counter_set_type;
    uint32_t counter_index;
    uint16_t mid_base;
};

/**
 * ku_access_sfgc_reg structure is used to store the access register SFGC command parameters
 */
struct ku_access_sfgc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sfgc_reg      sfgc_reg; /**< sfgc_reg - sfgc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_mcion_reg structure is used to store the MCION register parameters
 */
struct ku_mcion_reg {
    uint8_t module;
    uint8_t slot_index;
    uint16_t module_status_bits;
};

/**
 * ku_access_mcion_reg structure is used to store the access register MCION command parameters
 */
struct ku_access_mcion_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mcion_reg     mcion_reg; /**< mcion_reg - mcion register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_tiqcr_reg structure is used to store the TIQCR register parameters
 */
struct ku_tiqcr_reg {
    uint8_t enc_set_dscp;
    uint8_t enc_set_sp;
    uint8_t enc_dscp_rw;
    uint8_t enc_pcp_rw;
    uint8_t dec_set_dscp;
    uint8_t dec_set_sp;
    uint8_t dec_dscp_rw;
    uint8_t dec_pcp_rw;
};

/**
 * ku_access_tiqcr_reg structure is used to store the access register TIQCR command parameters
 */
struct ku_access_tiqcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tiqcr_reg     tiqcr_reg; /**< tiqcr_reg - tiqcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_tncr_v2_reg structure is used to store the TNCR_V2 register parameters
 */
struct ku_tncr_v2_reg {
    uint8_t clear_counters;
    uint8_t tunnel_port;
    uint32_t count_decap_discards_high;
    uint32_t count_decap_discards_low;
    uint32_t count_encap_discards_high;
    uint32_t count_encap_discards_low;
};

/**
 * ku_access_tncr_v2_reg structure is used to store the access register TNCR_V2 command parameters
 */
struct ku_access_tncr_v2_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tncr_v2_reg   tncr_v2_reg; /**< tncr_v2_reg - tncr_v2 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_PCSR_PORT_STATUS_MASK_NUM 4

/**
 * ku_pcsr_reg structure is used to store the PCSR register parameters
 */
struct ku_pcsr_reg {
    uint8_t gs;
    uint8_t offset;
    uint32_t port_status_mask[SXD_PCSR_PORT_STATUS_MASK_NUM];
};

/**
 * ku_access_pcsr_reg structure is used to store the access register PCSR command parameters
 */
struct ku_access_pcsr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pcsr_reg      pcsr_reg; /**< pcsr_reg - pcsr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_rarcc_reg structure is used to store the RARCC register parameters
 */
struct ku_rarcc_reg {
    uint8_t clr;
    uint32_t ar_changes_congestion_high;
    uint32_t ar_changes_congestion_low;
    uint32_t ar_changes_arn_high;
    uint32_t ar_changes_arn_low;
};

/**
 * ku_access_rarcc_reg structure is used to store the access register RARCC command parameters
 */
struct ku_access_rarcc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rarcc_reg     rarcc_reg; /**< rarcc_reg - rarcc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_CEDR_DETECTION_TABLE_NUM 4

/**
 * ku_cedr_reg structure is used to store the CEDR register parameters
 */
struct ku_cedr_reg {
    uint8_t clear;
    uint8_t local_port;
    uint8_t lp_msb;
    uint32_t detection_table[SXD_CEDR_DETECTION_TABLE_NUM];
};

/**
 * ku_access_cedr_reg structure is used to store the access register CEDR command parameters
 */
struct ku_access_cedr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_cedr_reg      cedr_reg; /**< cedr_reg - cedr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_RMID_V2_EGRESS_PORT_NUM 32

/**
 * ku_rmid_v2_reg structure is used to store the RMID_V2 register parameters
 */
struct ku_rmid_v2_reg {
    uint16_t rmid_index;
    uint16_t rmpe_index;
    uint32_t egress_port[SXD_RMID_V2_EGRESS_PORT_NUM];
};

/**
 * ku_access_rmid_v2_reg structure is used to store the access register RMID_V2 command parameters
 */
struct ku_access_rmid_v2_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rmid_v2_reg   rmid_v2_reg; /**< rmid_v2_reg - rmid_v2 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_rarcl_reg structure is used to store the RARCL register parameters
 */
struct ku_rarcl_reg {
    uint32_t eport_cong_level0;
    uint32_t eport_cong_level1;
    uint32_t eport_cong_level2;
};

/**
 * ku_access_rarcl_reg structure is used to store the access register RARCL command parameters
 */
struct ku_access_rarcl_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rarcl_reg     rarcl_reg; /**< rarcl_reg - rarcl register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_mafcr_reg structure is used to store the MAFCR register parameters
 */
struct ku_mafcr_reg {
    uint8_t clear;
    uint32_t counter_accu_overflow;
    uint16_t packets_inc_units;
    uint16_t bytes_inc_units;
};

/**
 * ku_access_mafcr_reg structure is used to store the access register MAFCR command parameters
 */
struct ku_access_mafcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mafcr_reg     mafcr_reg; /**< mafcr_reg - mafcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_XRALST_BIN_NUM 128

/**
 * ku_xralst_reg structure is used to store the XRALST register parameters
 */
struct ku_xralst_reg {
    uint8_t root_bin;
    uint8_t tree_id;
    uint16_t bin[SXD_XRALST_BIN_NUM];
};

/**
 * ku_access_xralst_reg structure is used to store the access register XRALST command parameters
 */
struct ku_access_xralst_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_xralst_reg    xralst_reg; /**< xralst_reg - xralst register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_SBSRD_SHARED_BUFFER_STATUS_NUM 128

typedef struct sxd_sbsrd_shared_buffer_status {
    uint32_t buff_occupancy;
    uint32_t max_buff_occupancy;
} sxd_sbsrd_shared_buffer_status_t;

/**
 * ku_sbsrd_reg structure is used to store the SBSRD register parameters
 */
struct ku_sbsrd_reg {
    uint8_t clr;
    uint8_t snap;
    uint8_t desc;
    uint8_t type;
    uint8_t num_rec;
    uint16_t fisrt_entry_index;
    uint8_t first_lp_msb;
    uint8_t first_local_port;
    sxd_sbsrd_shared_buffer_status_t shared_buffer_status[SXD_SBSRD_SHARED_BUFFER_STATUS_NUM];
};

/**
 * ku_access_sbsrd_reg structure is used to store the access register SBSRD command parameters
 */
struct ku_access_sbsrd_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbsrd_reg     sbsrd_reg; /**< sbsrd_reg - sbsrd register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_PLAR_LOCAL_PORT_ALLOCATED_NUM 16

/**
 * ku_plar_reg structure is used to store the PLAR register parameters
 */
struct ku_plar_reg {
    uint32_t local_port_allocated[SXD_PLAR_LOCAL_PORT_ALLOCATED_NUM];
};

/**
 * ku_access_plar_reg structure is used to store the access register PLAR command parameters
 */
struct ku_access_plar_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_plar_reg      plar_reg; /**< plar_reg - plar register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_iddd_reg structure is used to store the IDDD register parameters
 */
struct ku_iddd_reg {
    uint8_t entry_type;
    uint8_t duplication;
};

/**
 * ku_access_iddd_reg structure is used to store the access register IDDD command parameters
 */
struct ku_access_iddd_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_iddd_reg      iddd_reg; /**< iddd_reg - iddd register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_IEDR_RECORD_NUM 64

typedef struct sxd_iedr_record {
    uint8_t type;
    uint16_t size;
    uint32_t index_start;
} sxd_iedr_record_t;

/**
 * ku_iedr_reg structure is used to store the IEDR register parameters
 */
struct ku_iedr_reg {
    uint8_t bg;
    uint8_t num_rec;
    sxd_iedr_record_t record[SXD_IEDR_RECORD_NUM];
};

/**
 * ku_access_iedr_reg structure is used to store the access register IEDR command parameters
 */
struct ku_access_iedr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_iedr_reg      iedr_reg; /**< iedr_reg - iedr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_ieds_reg structure is used to store the IEDS register parameters
 */
struct ku_ieds_reg {
    uint8_t edpr;
    uint8_t ed_status;
};

/**
 * ku_access_ieds_reg structure is used to store the access register IEDS command parameters
 */
struct ku_access_ieds_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ieds_reg      ieds_reg; /**< ieds_reg - ieds register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_pmaos_admin_status {
    SXD_PMAOS_ADMIN_STATUS_ENABLED_E = 0x1,
    SXD_PMAOS_ADMIN_STATUS_DISABLED_BY_CONFIGURATION_E = 0x2,
    SXD_PMAOS_ADMIN_STATUS_ENABLED_ONCE_E = 0x3,
    SXD_PMAOS_ADMIN_STATUS_MIN = SXD_PMAOS_ADMIN_STATUS_ENABLED_E,
    SXD_PMAOS_ADMIN_STATUS_MAX = SXD_PMAOS_ADMIN_STATUS_ENABLED_ONCE_E
} sxd_pmaos_admin_status_t;


typedef enum sxd_pmaos_oper_status {
    SXD_PMAOS_OPER_STATUS_INITIALIZING_E = 0x0,
    SXD_PMAOS_OPER_STATUS_PLUGGED_ENABLED_E = 0x1,
    SXD_PMAOS_OPER_STATUS_UNPLUGGED_E = 0x2,
    SXD_PMAOS_OPER_STATUS_MODULE_PLUGGED_WITH_ERROR_E = 0x3,
    SXD_PMAOS_OPER_STATUS_PLUGGED_DISABLED_E = 0x4,
    SXD_PMAOS_OPER_STATUS_MIN = SXD_PMAOS_OPER_STATUS_INITIALIZING_E,
    SXD_PMAOS_OPER_STATUS_MAX = SXD_PMAOS_OPER_STATUS_PLUGGED_DISABLED_E
} sxd_pmaos_oper_status_t;


typedef enum sxd_pmaos_error_type {
    SXD_PMAOS_ERROR_TYPE_POWER_BUDGET_EXCEEDED_E = 0x0,
    SXD_PMAOS_ERROR_TYPE_LONG_RANGE_FOR_NON_MLNX_CABLE_OR_MODULE_E = 0x1,
    SXD_PMAOS_ERROR_TYPE_BUS_STUCK_E = 0x2,
    SXD_PMAOS_ERROR_TYPE_BAD_OR_UNSUPPORTED_EEPROM_E = 0x3,
    SXD_PMAOS_ERROR_TYPE_ENFORCE_PART_NUMBER_LIST_E = 0x4,
    SXD_PMAOS_ERROR_TYPE_UNSUPPORTED_CABLE_E = 0x5,
    SXD_PMAOS_ERROR_TYPE_HIGH_TEMPERATURE_E = 0x6,
    SXD_PMAOS_ERROR_TYPE_BAD_CABLE_E = 0x7,
    SXD_PMAOS_ERROR_TYPE_PMD_TYPE_IS_NOT_ENABLED_E = 0x8,
    SXD_PMAOS_ERROR_TYPE_PCIE_SYSTEM_POWER_SLOT_EXCEEDED_E = 0xc,
    SXD_PMAOS_ERROR_TYPE_MIN = SXD_PMAOS_ERROR_TYPE_POWER_BUDGET_EXCEEDED_E,
    SXD_PMAOS_ERROR_TYPE_MAX = SXD_PMAOS_ERROR_TYPE_PCIE_SYSTEM_POWER_SLOT_EXCEEDED_E
} sxd_pmaos_error_type_t;


typedef enum sxd_pmaos_e {
    SXD_PMAOS_E_DO_NOT_GENERATE_EVENT_E = 0x0,
    SXD_PMAOS_E_GENERATE_EVENT_E = 0x1,
    SXD_PMAOS_E_GENERATE_SINGLE_EVENT_E = 0x2,
    SXD_PMAOS_E_MIN = SXD_PMAOS_E_DO_NOT_GENERATE_EVENT_E,
    SXD_PMAOS_E_MAX = SXD_PMAOS_E_GENERATE_SINGLE_EVENT_E
} sxd_pmaos_e_t;

/**
 * ku_pmaos_reg structure is used to store the PMAOS register parameters
 */
struct ku_pmaos_reg {
    uint8_t rst;
    uint8_t slot_index;
    uint8_t module;
    sxd_pmaos_admin_status_t admin_status;
    sxd_pmaos_oper_status_t oper_status;
    uint8_t ase;
    uint8_t ee;
    uint8_t operational_notification;
    sxd_pmaos_error_type_t error_type;
    sxd_pmaos_e_t e;
};

/**
 * ku_access_pmaos_reg structure is used to store the access register PMAOS command parameters
 */
struct ku_access_pmaos_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmaos_reg     pmaos_reg; /**< pmaos_reg - pmaos register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_rxlte_reg structure is used to store the RXLTE register parameters
 */
struct ku_rxlte_reg {
    uint16_t virtual_router;
    uint8_t protocol;
    uint8_t lpm_xlt_en;
};

/**
 * ku_access_rxlte_reg structure is used to store the access register RXLTE command parameters
 */
struct ku_access_rxlte_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rxlte_reg     rxlte_reg; /**< rxlte_reg - rxlte register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_sbhbr_v2_reg structure is used to store the SBHBR_V2 register parameters
 */
struct ku_sbhbr_v2_reg {
    uint8_t local_port;
    uint8_t pg_buff;
    uint8_t lp_msb;
    uint8_t dir;
    uint8_t en;
    uint8_t mode;
    uint16_t hist_type;
    uint32_t hist_min_value;
    uint32_t hist_max_value;
    uint8_t sample_time;
};

/**
 * ku_access_sbhbr_v2_reg structure is used to store the access register SBHBR_V2 command parameters
 */
struct ku_access_sbhbr_v2_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbhbr_v2_reg  sbhbr_v2_reg; /**< sbhbr_v2_reg - sbhbr_v2 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_tnqcr_reg structure is used to store the TNQCR register parameters
 */
struct ku_tnqcr_reg {
    uint8_t enc_set_dscp;
    uint8_t enc_set_sp;
    uint8_t enc_dscp_rw;
    uint8_t enc_pcp_rw;
    uint8_t dec_set_dscp;
    uint8_t dec_set_sp;
    uint8_t dec_set_pcp;
    uint8_t dec_dscp_rw;
    uint8_t dec_pcp_rw;
};

/**
 * ku_access_tnqcr_reg structure is used to store the access register TNQCR command parameters
 */
struct ku_access_tnqcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tnqcr_reg     tnqcr_reg; /**< tnqcr_reg - tnqcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_SBHRR_V2_BIN_NUM 10

typedef struct sxd_sbhrr_v2_bin {
    uint32_t hi;
    uint32_t lo;
} sxd_sbhrr_v2_bin_t;

/**
 * ku_sbhrr_v2_reg structure is used to store the SBHRR_V2 register parameters
 */
struct ku_sbhrr_v2_reg {
    uint8_t clr;
    uint8_t local_port;
    uint8_t pg_buff;
    uint8_t lp_msb;
    uint8_t dir;
    uint16_t hist_type;
    uint32_t min_sampled_high;
    uint32_t min_sampled_low;
    uint32_t max_sampled_high;
    uint32_t max_sampled_low;
    sxd_sbhrr_v2_bin_t bin[SXD_SBHRR_V2_BIN_NUM];
};

/**
 * ku_access_sbhrr_v2_reg structure is used to store the access register SBHRR_V2 command parameters
 */
struct ku_access_sbhrr_v2_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbhrr_v2_reg  sbhrr_v2_reg; /**< sbhrr_v2_reg - sbhrr_v2 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_PBSR_STAT_BUFFER_NUM 10

typedef struct sxd_pbsr_stat_buffer {
    uint16_t watermark;
    uint16_t used_buffer;
} sxd_pbsr_stat_buffer_t;

typedef struct sxd_pbsr_stat_shared_headroom_pool {
    uint16_t watermark;
    uint16_t used_buffer;
} sxd_pbsr_stat_shared_headroom_pool_t;

/**
 * ku_pbsr_reg structure is used to store the PBSR register parameters
 */
struct ku_pbsr_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint8_t buffer_type;
    uint16_t clear_wm_buff_mask;
    uint8_t clear_wm;
    uint16_t used_shared_headroom_buffer;
    sxd_pbsr_stat_buffer_t stat_buffer[SXD_PBSR_STAT_BUFFER_NUM];
    sxd_pbsr_stat_shared_headroom_pool_t stat_shared_headroom_pool;
};

/**
 * ku_access_pbsr_reg structure is used to store the access register PBSR command parameters
 */
struct ku_access_pbsr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pbsr_reg      pbsr_reg; /**< pbsr_reg - pbsr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_rxltm_reg structure is used to store the RXLTM register parameters
 */
struct ku_rxltm_reg {
    uint8_t m_sel_update;
    uint8_t go_m_sel;
    uint8_t m_sel;
    uint8_t m1_val_v6;
    uint8_t m0_val_v6;
    uint8_t m1_val_v4;
    uint8_t m0_val_v4;
};

/**
 * ku_access_rxltm_reg structure is used to store the access register RXLTM command parameters
 */
struct ku_access_rxltm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rxltm_reg     rxltm_reg; /**< rxltm_reg - rxltm register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MSGI_SERIAL_NUMBER_NUM 6

#define SXD_MSGI_PART_NUMBER_NUM 5

#define SXD_MSGI_PRODUCT_NAME_NUM 16

/**
 * ku_msgi_reg structure is used to store the MSGI register parameters
 */
struct ku_msgi_reg {
    uint32_t serial_number[SXD_MSGI_SERIAL_NUMBER_NUM];
    uint32_t part_number[SXD_MSGI_PART_NUMBER_NUM];
    uint32_t revision;
    uint32_t product_name[SXD_MSGI_PRODUCT_NAME_NUM];
};

/**
 * ku_access_msgi_reg structure is used to store the access register MSGI command parameters
 */
struct ku_access_msgi_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_msgi_reg      msgi_reg; /**< msgi_reg - msgi register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_momte_mngr_type {
    SXD_MOMTE_MNGR_TYPE_HYPERVISOR_E = 0x0,
    SXD_MOMTE_MNGR_TYPE_LNM_E = 0x1,
    SXD_MOMTE_MNGR_TYPE_MIN = SXD_MOMTE_MNGR_TYPE_HYPERVISOR_E,
    SXD_MOMTE_MNGR_TYPE_MAX = SXD_MOMTE_MNGR_TYPE_LNM_E
} sxd_momte_mngr_type_t;

/**
 * ku_momte_reg structure is used to store the MOMTE register parameters
 */
struct ku_momte_reg {
    uint8_t swid;
    uint8_t local_port;
    uint8_t lp_msb;
    sxd_momte_mngr_type_t mngr_type;
    uint8_t type;
    uint32_t tclass_en_high;
    uint32_t tclass_en_low;
};

/**
 * ku_access_momte_reg structure is used to store the access register MOMTE command parameters
 */
struct ku_access_momte_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_momte_reg     momte_reg; /**< momte_reg - momte register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_rmpe_reg structure is used to store the RMPE register parameters
 */
struct ku_rmpe_reg {
    uint8_t local_port;
    uint8_t lp_msb;
    uint16_t rmpe_index;
    uint16_t erif;
};

/**
 * ku_access_rmpe_reg structure is used to store the access register RMPE command parameters
 */
struct ku_access_rmpe_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rmpe_reg      rmpe_reg; /**< rmpe_reg - rmpe register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_svfa_mapping_table {
    SXD_SVFA_MAPPING_TABLE_VLAN_MAPPING_TABLE_E = 0x0,
    SXD_SVFA_MAPPING_TABLE_PORT_VLAN_MAPPING_TABLE_E = 0x1,
    SXD_SVFA_MAPPING_TABLE_VNI_MAPPING_TABLE_E = 0x2,
    SXD_SVFA_MAPPING_TABLE_MIN = SXD_SVFA_MAPPING_TABLE_VLAN_MAPPING_TABLE_E,
    SXD_SVFA_MAPPING_TABLE_MAX = SXD_SVFA_MAPPING_TABLE_VNI_MAPPING_TABLE_E
} sxd_svfa_mapping_table_t;


typedef enum sxd_svfa_trap_action {
    SXD_SVFA_TRAP_ACTION_NOP_E = 0x0,
    SXD_SVFA_TRAP_ACTION_TRAP_E = 0x1,
    SXD_SVFA_TRAP_ACTION_MIRROR_TO_CPU_E = 0x2,
    SXD_SVFA_TRAP_ACTION_MIRROR_E = 0x3,
    SXD_SVFA_TRAP_ACTION_DISCARD_ERROR_E = 0x4,
    SXD_SVFA_TRAP_ACTION_MIN = SXD_SVFA_TRAP_ACTION_NOP_E,
    SXD_SVFA_TRAP_ACTION_MAX = SXD_SVFA_TRAP_ACTION_DISCARD_ERROR_E
} sxd_svfa_trap_action_t;

/**
 * ku_svfa_reg structure is used to store the SVFA register parameters
 */
struct ku_svfa_reg {
    uint8_t swid;
    uint8_t local_port;
    uint8_t lp_msb;
    sxd_svfa_mapping_table_t mapping_table;
    uint8_t tport;
    uint8_t v;
    uint16_t fid;
    uint16_t vid;
    uint8_t counter_set_type;
    uint32_t counter_index;
    sxd_svfa_trap_action_t trap_action;
    uint32_t vni;
    uint8_t irif_v;
    uint16_t irif;
};

/**
 * ku_access_svfa_reg structure is used to store the access register SVFA command parameters
 */
struct ku_access_svfa_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_svfa_reg      svfa_reg; /**< svfa_reg - svfa register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MAFRI_RECORD_NUM 128

typedef struct sxd_mafri_record {
    uint32_t bytes_inc;
    uint32_t packets_inc;
} sxd_mafri_record_t;

/**
 * ku_mafri_reg structure is used to store the MAFRI register parameters
 */
struct ku_mafri_reg {
    uint8_t fsf;
    uint8_t event;
    uint8_t num_rec;
    uint32_t counter_index_base;
    uint32_t user_val;
    sxd_mafri_record_t record[SXD_MAFRI_RECORD_NUM];
};

/**
 * ku_access_mafri_reg structure is used to store the access register MAFRI command parameters
 */
struct ku_access_mafri_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mafri_reg     mafri_reg; /**< mafri_reg - mafri register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_IHSR_OUTER_HEADER_FIELDS_ENABLE_NUM 5

typedef struct sxd_ihsr_inner_header_fields_enable {
    uint32_t hi;
    uint32_t lo;
} sxd_ihsr_inner_header_fields_enable_t;

/**
 * ku_ihsr_reg structure is used to store the IHSR register parameters
 */
struct ku_ihsr_reg {
    uint8_t sh;
    uint8_t type;
    uint32_t general_fields;
    uint16_t outer_header_enables;
    uint32_t outer_header_fields_enable[SXD_IHSR_OUTER_HEADER_FIELDS_ENABLE_NUM];
    uint16_t inner_header_enables;
    sxd_ihsr_inner_header_fields_enable_t inner_header_fields_enable;
};

/**
 * ku_access_ihsr_reg structure is used to store the access register IHSR command parameters
 */
struct ku_access_ihsr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ihsr_reg      ihsr_reg; /**< ihsr_reg - ihsr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_fphtt_reg structure is used to store the FPHTT register parameters
 */
struct ku_fphtt_reg {
    uint8_t entry_index;
    uint8_t tran_en;
};

/**
 * ku_access_fphtt_reg structure is used to store the access register FPHTT command parameters
 */
struct ku_access_fphtt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_fphtt_reg     fphtt_reg; /**< fphtt_reg - fphtt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_mcc_instruction {
    SXD_MCC_INSTRUCTION_LOCK_UPDATE_HANDLE_E = 0x1,
    SXD_MCC_INSTRUCTION_RELEASE_UPDATE_HANDLE_E = 0x2,
    SXD_MCC_INSTRUCTION_UPDATE_COMPONENT_E = 0x3,
    SXD_MCC_INSTRUCTION_VERIFY_COMPONENT_E = 0x4,
    SXD_MCC_INSTRUCTION_ACTIVATE_COMPONENET_E = 0x5,
    SXD_MCC_INSTRUCTION_ACTIVATE_E = 0x6,
    SXD_MCC_INSTRUCTION_READ_COMPONENT_E = 0x7,
    SXD_MCC_INSTRUCTION_CANCEL_E = 0x8,
    SXD_MCC_INSTRUCTION_CHECK_UPDATE_HANDLE_E = 0x9,
    SXD_MCC_INSTRUCTION_FORCE_HANDLE_RELEASE_E = 0xa,
    SXD_MCC_INSTRUCTION_READ_PENDING_COMPONENT_E = 0xb,
    SXD_MCC_INSTRUCTION_DOWNSRTEAM_DEVICE_TRANSFER_E = 0xc,
    SXD_MCC_INSTRUCTION_MIN = SXD_MCC_INSTRUCTION_LOCK_UPDATE_HANDLE_E,
    SXD_MCC_INSTRUCTION_MAX = SXD_MCC_INSTRUCTION_DOWNSRTEAM_DEVICE_TRANSFER_E
} sxd_mcc_instruction_t;


typedef enum sxd_mcc_control_state {
    SXD_MCC_CONTROL_STATE_IDLE_E = 0x0,
    SXD_MCC_CONTROL_STATE_LOCKED_E = 0x1,
    SXD_MCC_CONTROL_STATE_INITIALIZE_E = 0x2,
    SXD_MCC_CONTROL_STATE_DOWNLOAD_E = 0x3,
    SXD_MCC_CONTROL_STATE_VERIFY_E = 0x4,
    SXD_MCC_CONTROL_STATE_APPLY_E = 0x5,
    SXD_MCC_CONTROL_STATE_ACTIVATE_E = 0x6,
    SXD_MCC_CONTROL_STATE_UPLOAD_E = 0x7,
    SXD_MCC_CONTROL_STATE_UPLOAD_PENDING_E = 0x8,
    SXD_MCC_CONTROL_STATE_DOWNSRTEAM_DEVICE_TRANSFER_E = 0x9,
    SXD_MCC_CONTROL_STATE_MIN = SXD_MCC_CONTROL_STATE_IDLE_E,
    SXD_MCC_CONTROL_STATE_MAX = SXD_MCC_CONTROL_STATE_DOWNSRTEAM_DEVICE_TRANSFER_E
} sxd_mcc_control_state_t;


typedef enum sxd_mcc_device_type {
    SXD_MCC_DEVICE_TYPE_SWITCH_OR_NIC_E = 0x0,
    SXD_MCC_DEVICE_TYPE_GEARBOX_E = 0x1,
    SXD_MCC_DEVICE_TYPE_MIN = SXD_MCC_DEVICE_TYPE_SWITCH_OR_NIC_E,
    SXD_MCC_DEVICE_TYPE_MAX = SXD_MCC_DEVICE_TYPE_GEARBOX_E
} sxd_mcc_device_type_t;

/**
 * ku_mcc_reg structure is used to store the MCC register parameters
 */
struct ku_mcc_reg {
    uint16_t time_elapsed_since_last_cmd;
    uint8_t activation_delay_sec;
    sxd_mcc_instruction_t instruction;
    uint16_t component_index;
    uint8_t auto_update;
    uint32_t update_handle;
    uint8_t handle_owner_type;
    uint8_t handle_owner_host_id;
    uint8_t control_progress;
    uint8_t error_code;
    sxd_mcc_control_state_t control_state;
    uint32_t component_size;
    uint16_t device_index;
    sxd_mcc_device_type_t device_type;
    uint16_t rejected_device_index;
    uint16_t device_index_size;
};

/**
 * ku_access_mcc_reg structure is used to store the access register MCC command parameters
 */
struct ku_access_mcc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mcc_reg       mcc_reg; /**< mcc_reg - mcc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_sfdb_reg structure is used to store the SFDB register parameters
 */
struct ku_sfdb_reg {
    uint8_t policy;
    uint8_t update_type;
    uint8_t gfid;
    uint16_t entry_fid;
    uint32_t parameter;
    uint32_t parameter1;
    uint32_t new_parameter;
    uint32_t new_parameter1;
};

/**
 * ku_access_sfdb_reg structure is used to store the access register SFDB command parameters
 */
struct ku_access_sfdb_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sfdb_reg      sfdb_reg; /**< sfdb_reg - sfdb register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


typedef enum sxd_pmtps_ib_speed_module_c2m {
    SXD_PMTPS_IB_SPEED_MODULE_C2M_SDR_E = 0x1,
    SXD_PMTPS_IB_SPEED_MODULE_C2M_DDR_E = 0x2,
    SXD_PMTPS_IB_SPEED_MODULE_C2M_QDR_E = 0x4,
    SXD_PMTPS_IB_SPEED_MODULE_C2M_FDR10_E = 0x8,
    SXD_PMTPS_IB_SPEED_MODULE_C2M_FDR_E = 0x10,
    SXD_PMTPS_IB_SPEED_MODULE_C2M_EDR_E = 0x20,
    SXD_PMTPS_IB_SPEED_MODULE_C2M_HDR_E = 0x40,
    SXD_PMTPS_IB_SPEED_MODULE_C2M_NDR_E = 0x80,
    SXD_PMTPS_IB_SPEED_MODULE_C2M_MIN = SXD_PMTPS_IB_SPEED_MODULE_C2M_SDR_E,
    SXD_PMTPS_IB_SPEED_MODULE_C2M_MAX = SXD_PMTPS_IB_SPEED_MODULE_C2M_NDR_E
} sxd_pmtps_ib_speed_module_c2m_t;

/**
 * ku_pmtps_reg structure is used to store the PMTPS register parameters
 */
struct ku_pmtps_reg {
    uint8_t slot_index;
    uint8_t module;
    uint16_t module_type_admin;
    uint16_t module_type_connected;
    uint32_t eth_module_c2m;
    uint16_t ib_width_module_c2m;
    sxd_pmtps_ib_speed_module_c2m_t ib_speed_module_c2m;
};

/**
 * ku_access_pmtps_reg structure is used to store the access register PMTPS command parameters
 */
struct ku_access_pmtps_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmtps_reg     pmtps_reg; /**< pmtps_reg - pmtps register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MFDE_ASSERT_STRING_NUM 32


typedef enum sxd_mfde_severity {
    SXD_MFDE_SEVERITY_FATL_E = 0x2,
    SXD_MFDE_SEVERITY_NRML_E = 0x3,
    SXD_MFDE_SEVERITY_INTR_E = 0x5,
    SXD_MFDE_SEVERITY_MIN = SXD_MFDE_SEVERITY_FATL_E,
    SXD_MFDE_SEVERITY_MAX = SXD_MFDE_SEVERITY_INTR_E
} sxd_mfde_severity_t;


typedef enum sxd_mfde_event_id {
    SXD_MFDE_EVENT_ID_CRSPACE_TIMEOUT_E = 0x1,
    SXD_MFDE_EVENT_ID_KVD_IM_STOP_E = 0x2,
    SXD_MFDE_EVENT_ID_TEST_E = 0x3,
    SXD_MFDE_EVENT_ID_FW_ASSERT_E = 0x4,
    SXD_MFDE_EVENT_ID_FATAL_CAUSE_E = 0x5,
    SXD_MFDE_EVENT_ID_MIN = SXD_MFDE_EVENT_ID_CRSPACE_TIMEOUT_E,
    SXD_MFDE_EVENT_ID_MAX = SXD_MFDE_EVENT_ID_FATAL_CAUSE_E
} sxd_mfde_event_id_t;

typedef struct sxd_mfde_log_ip {
    uint32_t hi;
    uint32_t lo;
} sxd_mfde_log_ip_t;

typedef struct sxd_mfde_crspace_timeout {
    uint32_t log_address;
    uint8_t oe;
    uint8_t log_id;
    sxd_mfde_log_ip_t log_ip;
} sxd_mfde_crspace_timeout_t;

typedef struct sxd_mfde_kvd_im_stop {
    uint8_t oe;
    uint16_t pipes_mask;
} sxd_mfde_kvd_im_stop_t;

typedef struct sxd_mfde_test {
    uint32_t reserved;
} sxd_mfde_test_t;

typedef struct sxd_mfde_fw_assert {
    uint32_t assert_var0;
    uint32_t assert_var1;
    uint32_t assert_var2;
    uint32_t assert_var3;
    uint32_t assert_var4;
    uint32_t assert_existptr;
    uint32_t assert_callra;
    uint8_t test;
    uint8_t oe;
    uint8_t tile_v;
    uint8_t tile_index;
    uint16_t ext_synd;
    uint32_t assert_string[SXD_MFDE_ASSERT_STRING_NUM];
} sxd_mfde_fw_assert_t;

typedef struct sxd_mfde_fatal_cause {
    uint8_t test;
    uint32_t cause_id;
    uint8_t tile_v;
    uint8_t tile_index;
} sxd_mfde_fatal_cause_t;

union mfde_event_params {
    sxd_mfde_crspace_timeout_t crspace_timeout;
    sxd_mfde_kvd_im_stop_t kvd_im_stop;
    sxd_mfde_test_t test;
    sxd_mfde_fw_assert_t fw_assert;
    sxd_mfde_fatal_cause_t fatal_cause;
};

/**
 * ku_mfde_reg structure is used to store the MFDE register parameters
 */
struct ku_mfde_reg {
    uint8_t irisc_id;
    sxd_mfde_severity_t severity;
    sxd_mfde_event_id_t event_id;
    uint8_t method;
    uint8_t long_process;
    uint8_t command_type;
    uint8_t mgmt_class;
    uint16_t reg_attr_id;
    union mfde_event_params event_params;
};

/**
 * ku_access_mfde_reg structure is used to store the access register MFDE command parameters
 */
struct ku_access_mfde_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mfde_reg      mfde_reg; /**< mfde_reg - mfde register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_rxltcc_reg structure is used to store the RXLTCC register parameters
 */
struct ku_rxltcc_reg {
    uint8_t clear;
    uint32_t hit_ipv4_m_high;
    uint32_t hit_ipv4_m_low;
    uint32_t hit_ipv4_ml_high;
    uint32_t hit_ipv4_ml_low;
    uint32_t miss_ipv4_m_high;
    uint32_t miss_ipv4_m_low;
    uint32_t miss_ipv4_ml_high;
    uint32_t miss_ipv4_ml_low;
    uint32_t learned_ipv4_high;
    uint32_t learned_ipv4_low;
    uint32_t hit_ipv6_m_high;
    uint32_t hit_ipv6_m_low;
    uint32_t hit_ipv6_ml_high;
    uint32_t hit_ipv6_ml_low;
    uint32_t miss_ipv6_m_high;
    uint32_t miss_ipv6_m_low;
    uint32_t miss_ipv6_ml_high;
    uint32_t miss_ipv6_ml_low;
    uint32_t learned_ipv6_high;
    uint32_t learned_ipv6_low;
};

/**
 * ku_access_rxltcc_reg structure is used to store the access register RXLTCC command parameters
 */
struct ku_access_rxltcc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rxltcc_reg    rxltcc_reg; /**< rxltcc_reg - rxltcc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_sbhpc_reg structure is used to store the SBHPC register parameters
 */
struct ku_sbhpc_reg {
    uint32_t max_buff;
    uint32_t buff_occupancy;
};

/**
 * ku_access_sbhpc_reg structure is used to store the access register SBHPC command parameters
 */
struct ku_access_sbhpc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbhpc_reg     sbhpc_reg; /**< sbhpc_reg - sbhpc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MBCT_DATA_NUM 256


typedef enum sxd_mbct_ini_status {
    SXD_MBCT_INI_STATUS_EMPTY_NOT_VALID_E = 0x0,
    SXD_MBCT_INI_STATUS_VALID_E = 0x1,
    SXD_MBCT_INI_STATUS_READY_TO_USE_E = 0x2,
    SXD_MBCT_INI_STATUS_IN_USE_E = 0x3,
    SXD_MBCT_INI_STATUS_MIN = SXD_MBCT_INI_STATUS_EMPTY_NOT_VALID_E,
    SXD_MBCT_INI_STATUS_MAX = SXD_MBCT_INI_STATUS_IN_USE_E
} sxd_mbct_ini_status_t;


typedef enum sxd_mbct_op {
    SXD_MBCT_OP_RESERVED_E = 0x0,
    SXD_MBCT_OP_ERASE_INI_IMAGE_E = 0x1,
    SXD_MBCT_OP_DATA_TRANSFER_E = 0x2,
    SXD_MBCT_OP_ACTIVATE_E = 0x3,
    SXD_MBCT_OP_DEACTIVATE_E = 0x4,
    SXD_MBCT_OP_ABORT_E = 0x5,
    SXD_MBCT_OP_CLEAR_ERRORS_E = 0x6,
    SXD_MBCT_OP_QUERY_STATUS_E = 0x7,
    SXD_MBCT_OP_MIN = SXD_MBCT_OP_RESERVED_E,
    SXD_MBCT_OP_MAX = SXD_MBCT_OP_QUERY_STATUS_E
} sxd_mbct_op_t;


typedef enum sxd_mbct_status {
    SXD_MBCT_STATUS_NA_E = 0x0,
    SXD_MBCT_STATUS_BUSY_E = 0x1,
    SXD_MBCT_STATUS_PARTIAL_E = 0x2,
    SXD_MBCT_STATUS_LAST_DATA_E = 0x3,
    SXD_MBCT_STATUS_ERASE_IS_COMPLETE_E = 0x4,
    SXD_MBCT_STATUS_ERROR_ATTEMPTED_ERASE_INI_IN_USE_E = 0x5,
    SXD_MBCT_STATUS_TRANSFER_FAILURE_E = 0x6,
    SXD_MBCT_STATUS_ERASE_FAILURE_E = 0x7,
    SXD_MBCT_STATUS_INI_ERROR_E = 0x8,
    SXD_MBCT_STATUS_ACTIVATION_OF_INI_FAILED_E = 0x9,
    SXD_MBCT_STATUS_DEACTIVATION_OF_INI_FAILED_E = 0xa,
    SXD_MBCT_STATUS_ERROR_ILLEGAL_OPERATION_E = 0xb,
    SXD_MBCT_STATUS_MIN = SXD_MBCT_STATUS_NA_E,
    SXD_MBCT_STATUS_MAX = SXD_MBCT_STATUS_ERROR_ILLEGAL_OPERATION_E
} sxd_mbct_status_t;


typedef enum sxd_mbct_fsm_state {
    SXD_MBCT_FSM_STATE_IDLE_E = 0x0,
    SXD_MBCT_FSM_STATE_DATA_TRANSFER_E = 0x1,
    SXD_MBCT_FSM_STATE_MAGIC_PATTERN_VALID_E = 0x2,
    SXD_MBCT_FSM_STATE_READY_E = 0x3,
    SXD_MBCT_FSM_STATE_ERASE_E = 0x4,
    SXD_MBCT_FSM_STATE_INI_IN_USE_E = 0x5,
    SXD_MBCT_FSM_STATE_ERROR_E = 0x6,
    SXD_MBCT_FSM_STATE_MIN = SXD_MBCT_FSM_STATE_IDLE_E,
    SXD_MBCT_FSM_STATE_MAX = SXD_MBCT_FSM_STATE_ERROR_E
} sxd_mbct_fsm_state_t;

/**
 * ku_mbct_reg structure is used to store the MBCT register parameters
 */
struct ku_mbct_reg {
    uint8_t slot_index;
    sxd_mbct_ini_status_t ini_status;
    uint16_t data_size;
    sxd_mbct_op_t op;
    uint8_t last;
    uint8_t oee;
    sxd_mbct_status_t status;
    sxd_mbct_fsm_state_t fsm_state;
    uint32_t data[SXD_MBCT_DATA_NUM];
};

/**
 * ku_access_mbct_reg structure is used to store the access register MBCT command parameters
 */
struct ku_access_mbct_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mbct_reg      mbct_reg; /**< mbct_reg - mbct register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

#define SXD_MCDA_DATA_NUM 32

/**
 * ku_mcda_reg structure is used to store the MCDA register parameters
 */
struct ku_mcda_reg {
    uint32_t update_handle;
    uint32_t offset;
    uint16_t size;
    uint32_t data[SXD_MCDA_DATA_NUM];
};

/**
 * ku_access_mcda_reg structure is used to store the access register MCDA command parameters
 */
struct ku_access_mcda_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mcda_reg      mcda_reg; /**< mcda_reg - mcda register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};
