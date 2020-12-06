/*
* Copyright (c) 2008-2020,  Mellanox Technologies. All rights reserved.
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

 */

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


typedef enum sxd_spevet_et_vlan {
    SXD_SPEVET_ET_VLAN_ETHER_TYPE0_E = 0x0,
    SXD_SPEVET_ET_VLAN_ETHER_TYPE1_E = 0x1,
    SXD_SPEVET_ET_VLAN_ETHER_TYPE2_E = 0x2
} sxd_spevet_et_vlan_t;

/**
 * ku_spevet_reg structure is used to store the SPEVET register parameters
 */
struct ku_spevet_reg {
    uint8_t local_port;
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

/**
 * ku_mtmp_reg structure is used to store the MTMP register parameters
 */
struct ku_mtmp_reg {
    uint8_t slot_index;
    uint16_t sensor_index;
    uint16_t temperature;
    uint8_t mte;
    uint8_t mtr;
    uint16_t max_temperature;
    uint8_t tee;
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


typedef enum sxd_mogcr_toc_fmt {
    SXD_MOGCR_TOC_FMT_FREE_RUNNING_CLOCK_E = 0x0,
    SXD_MOGCR_TOC_FMT_UTC_E = 0x1
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


typedef enum sxd_rtdp_type {
    SXD_RTDP_TYPE_NVE_E = 0x0,
    SXD_RTDP_TYPE_IPINIP_E = 0x1
} sxd_rtdp_type_t;

typedef struct sxd_rtdp_rtdp_nve_decap {
    uint8_t decap_disable;
} sxd_rtdp_rtdp_nve_decap_t;

typedef struct sxd_rtdp_rtdp_ipinip {
    uint16_t irif;
    uint8_t sip_check;
    uint8_t type_check;
    uint8_t gre_key_check;
    uint32_t ipv4_usip;
    uint32_t ipv6_usip_ptr;
    uint32_t expected_gre_key;
} sxd_rtdp_rtdp_ipinip_t;

union rtdp_rtdp_entry {
    sxd_rtdp_rtdp_nve_decap_t rtdp_nve_decap;
    sxd_rtdp_rtdp_ipinip_t rtdp_ipinip;
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

#define SXD_TNIFR_PORT_FILTER_NUM 8

#define SXD_TNIFR_PORT_FILTER_UPDATE_EN_NUM 8

/**
 * ku_tnifr_reg structure is used to store the TNIFR register parameters
 */
struct ku_tnifr_reg {
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


typedef enum sxd_hcot_tunnel_port {
    SXD_HCOT_TUNNEL_PORT_NVE_E = 0x1,
    SXD_HCOT_TUNNEL_PORT_VPLS_E = 0x2,
    SXD_HCOT_TUNNEL_PORT_FLEX_TUNNEL0_E = 0x4,
    SXD_HCOT_TUNNEL_PORT_FLEX_TUNNEL1_E = 0x8
} sxd_hcot_tunnel_port_t;


typedef enum sxd_hcot_key_type {
    SXD_HCOT_KEY_TYPE_ETHERTYPE_E = 0x0,
    SXD_HCOT_KEY_TYPE_NEXT_PROTO_E = 0x1,
    SXD_HCOT_KEY_TYPE_LAYER4_PORT_E = 0x2,
    SXD_HCOT_KEY_TYPE_ICMP_IGMP_TYPE_E = 0x3
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

/**
 * ku_chltm_reg structure is used to store the CHLTM register parameters
 */
struct ku_chltm_reg {
    uint8_t local_port;
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

/**
 * ku_tnqdr_reg structure is used to store the TNQDR register parameters
 */
struct ku_tnqdr_reg {
    uint8_t local_port;
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
    SXD_SFFP_TYPE_IPV6_ALL_HOSTS_E = 0x7
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


typedef enum sxd_pter_error_page {
    SXD_PTER_ERROR_PAGE_INJECTION_OF_PHY_ERRORS_E = 0x0,
    SXD_PTER_ERROR_PAGE_INJECTION_OF_PORT_ERRORS_E = 0x1
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

#define SXD_PMMP_QSFP_CABLE_PROTOCOL_TECHNOLOGY_NUM 3

#define SXD_PMMP_SFP_CABLE_PROTOCOL_TECHNOLOGY_NUM 3

/**
 * ku_pmmp_reg structure is used to store the PMMP register parameters
 */
struct ku_pmmp_reg {
    uint8_t slot_index;
    uint8_t module;
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

/**
 * ku_tnpc_reg structure is used to store the TNPC register parameters
 */
struct ku_tnpc_reg {
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

#define SXD_MGIR_MANUFACTURING_BASE_MAC_NUM 6

#define SXD_MGIR_PSID_NUM 16

#define SXD_MGIR_DEV_BRANCH_TAG_NUM 28

typedef struct sxd_mgir_hw_info {
    uint16_t device_hw_revision;
    uint16_t device_id;
    uint8_t num_ports;
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
    uint16_t isfu_major;
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

#define SXD_IFBF_OUTER_HEADER_FIELDS_ENABLE_NUM 5

/**
 * ku_ifbf_reg structure is used to store the IFBF register parameters
 */
struct ku_ifbf_reg {
    uint8_t pp;
    uint8_t local_port;
    uint8_t type;
    uint32_t seed;
    uint16_t outer_header_enables;
    uint32_t outer_header_fields_enable[SXD_IFBF_OUTER_HEADER_FIELDS_ENABLE_NUM];
};

/**
 * ku_access_ifbf_reg structure is used to store the access register IFBF command parameters
 */
struct ku_access_ifbf_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ifbf_reg      ifbf_reg; /**< ifbf_reg - ifbf register tlv */
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
    SXD_MPAGR_MNGR_TYPE_LNM_E = 0x1
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
    SXD_PPCNT_PNAT_OOB_PORT_NUMBER_E = 0x3
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
    SXD_PPCNT_GRP_USR_XSR_PHYSICAL_LAYER_COUNTERS_GROUP_E = 0x24
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

typedef struct sxd_ppcnt_eth_per_traffic_class_cong_layout {
    uint32_t wred_discard_high;
    uint32_t wred_discard_low;
    uint32_t ecn_marked_tc_high;
    uint32_t ecn_marked_tc_low;
} sxd_ppcnt_eth_per_traffic_class_cong_layout_t;

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
    uint8_t post_fec_ber_magnitude;
    uint8_t post_fec_ber_coef;
} sxd_ppcnt_phys_layer_stat_cntrs_t;

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

union ppcnt_counter_set {
    sxd_ppcnt_eth_802_3_cntrs_grp_data_layout_t eth_802_3_cntrs_grp_data_layout;
    sxd_ppcnt_eth_2863_cntrs_grp_data_layout_t eth_2863_cntrs_grp_data_layout;
    sxd_ppcnt_eth_2819_cntrs_grp_data_layout_t eth_2819_cntrs_grp_data_layout;
    sxd_ppcnt_eth_3635_cntrs_grp_data_layout_t eth_3635_cntrs_grp_data_layout;
    sxd_ppcnt_eth_extended_cntrs_grp_data_layout_t eth_extended_cntrs_grp_data_layout;
    sxd_ppcnt_eth_discard_cntrs_grp_t eth_discard_cntrs_grp;
    sxd_ppcnt_eth_per_prio_grp_data_layout_t eth_per_prio_grp_data_layout;
    sxd_ppcnt_eth_per_traffic_class_layout_t eth_per_traffic_class_layout;
    sxd_ppcnt_eth_per_traffic_class_cong_layout_t eth_per_traffic_class_cong_layout;
    sxd_ppcnt_link_level_retrans_cntr_grp_data_t link_level_retrans_cntr_grp_data;
    sxd_ppcnt_IB_portcntrs_attribute_grp_data_t IB_portcntrs_attribute_grp_data;
    sxd_ppcnt_phys_layer_cntrs_t phys_layer_cntrs;
    sxd_ppcnt_usr_xsr_physical_layer_t usr_xsr_physical_layer;
    sxd_ppcnt_phys_layer_stat_cntrs_t phys_layer_stat_cntrs;
    sxd_ppcnt_ppcnt_plr_counters_t ppcnt_plr_counters;
    sxd_ppcnt_ppcnt_rs_fec_histograms_counters_t ppcnt_rs_fec_histograms_counters;
    sxd_ppcnt_eth_oob_port_cntrs_t eth_oob_port_cntrs;
};

/**
 * ku_ppcnt_reg structure is used to store the PPCNT register parameters
 */
struct ku_ppcnt_reg {
    uint8_t swid;
    uint8_t local_port;
    sxd_ppcnt_pnat_t pnat;
    uint8_t port_type;
    sxd_ppcnt_grp_t grp;
    uint8_t clr;
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

#define SXD_XMDR_TRANSACTION_NUM 32

/**
 * ku_xmdr_reg structure is used to store the XMDR register parameters
 */
struct ku_xmdr_reg {
    uint8_t bulk_entry;
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


typedef enum sxd_mdfcr_device_type {
    SXD_MDFCR_DEVICE_TYPE_VEGA_GEARBOX_E = 0x1,
    SXD_MDFCR_DEVICE_TYPE_TILE_E = 0x2
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
    SXD_MDFCR_ERROR_ID_MESSAGE_WAS_ABORTED_BY_HOST_E = 0xc
} sxd_mdfcr_error_id_t;

/**
 * ku_mdfcr_reg structure is used to store the MDFCR register parameters
 */
struct ku_mdfcr_reg {
    uint8_t slot_index;
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


typedef enum sxd_paos_admin_status {
    SXD_PAOS_ADMIN_STATUS_UP_E = 0x1,
    SXD_PAOS_ADMIN_STATUS_DOWN_BY_CONFIGURATION_E = 0x2,
    SXD_PAOS_ADMIN_STATUS_UP_ONCE_E = 0x3,
    SXD_PAOS_ADMIN_STATUS_DISABLED_BY_SYSTEM_E = 0x4
} sxd_paos_admin_status_t;


typedef enum sxd_paos_e {
    SXD_PAOS_E_DO_NOT_GENERATE_EVENT_E = 0x0,
    SXD_PAOS_E_GENERATE_EVENT_E = 0x1,
    SXD_PAOS_E_GENERATE_SINGLE_EVENT_E = 0x2
} sxd_paos_e_t;

/**
 * ku_paos_reg structure is used to store the PAOS register parameters
 */
struct ku_paos_reg {
    uint8_t swid;
    uint8_t local_port;
    uint8_t pnat;
    sxd_paos_admin_status_t admin_status;
    uint8_t oper_status;
    uint8_t ase;
    uint8_t ee;
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
    SXD_MTUTC_OPERATION_ADJUST_FREQ_BOTH_E = 0x5
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
    SXD_SFMR_FLOOD_BRIDGE_TYPE_TYPE_1_E = 0x1
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

/**
 * ku_smpe_reg structure is used to store the SMPE register parameters
 */
struct ku_smpe_reg {
    uint8_t local_port;
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

/**
 * ku_tiqdr_reg structure is used to store the TIQDR register parameters
 */
struct ku_tiqdr_reg {
    uint8_t local_port;
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

#define SXD_TNGEE_ENTRY_NUM 8


typedef enum sxd_tngee_protocol {
    SXD_TNGEE_PROTOCOL_IPV4_E = 0x0,
    SXD_TNGEE_PROTOCOL_IPV6_E = 0x1
} sxd_tngee_protocol_t;

/**
 * ku_tngee_reg structure is used to store the TNGEE register parameters
 */
struct ku_tngee_reg {
    uint32_t l2_enc_index;
    uint8_t tunnel_type;
    uint8_t vnext;
    uint32_t next_l2_enc_ptr;
    uint16_t ecmp_size;
    sxd_tngee_protocol_t protocol;
    uint16_t uirif;
    uint32_t udip;
    uint8_t counter_set_type;
    uint32_t counter_index;
    uint32_t entry[SXD_TNGEE_ENTRY_NUM];
};

/**
 * ku_access_tngee_reg structure is used to store the access register TNGEE command parameters
 */
struct ku_access_tngee_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_tngee_reg     tngee_reg; /**< tngee_reg - tngee register tlv */
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


typedef enum sxd_ppbs_action {
    SXD_PPBS_ACTION_NOP_E = 0x0,
    SXD_PPBS_ACTION_FORWARD_TO_IP_ROUTER_E = 0x3,
    SXD_PPBS_ACTION_FORWARD_TO_FCF_E = 0x4,
    SXD_PPBS_ACTION_DISCARD_E = 0x5,
    SXD_PPBS_ACTION_DISCARD_ERROR_E = 0xf
} sxd_ppbs_action_t;


typedef enum sxd_ppbs_protocol {
    SXD_PPBS_PROTOCOL_IPV4_E = 0x0,
    SXD_PPBS_PROTOCOL_IPV6_E = 0x1
} sxd_ppbs_protocol_t;


typedef enum sxd_ppbs_type {
    SXD_PPBS_TYPE_UNICAST_RECORD_E = 0x0,
    SXD_PPBS_TYPE_UNICAST_LAG_RECORD_E = 0x1,
    SXD_PPBS_TYPE_MULTICAST_RECORD_E = 0x2,
    SXD_PPBS_TYPE_UNICAST_TUNNEL_RECORD_E = 0xc,
    SXD_PPBS_TYPE_MULTICAST_TUNNEL_RECORD_E = 0xf
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
    uint16_t ecmp_size;
} sxd_ppbs_unicast_tunnel_t;

typedef struct sxd_ppbs_multicast_tunnel {
    uint16_t underlay_mc_ptr_msb;
    uint16_t fid;
    uint8_t underlay_mc_ptr_lsb;
    uint8_t v_fid;
    uint16_t mid;
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

#define SXD_REIV_ELPORT_RECORD_NUM 256

typedef struct sxd_reiv_elport_record {
    uint8_t update;
    uint16_t evid;
} sxd_reiv_elport_record_t;

/**
 * ku_reiv_reg structure is used to store the REIV register parameters
 */
struct ku_reiv_reg {
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
    SXD_PPAD_PNAT_LABEL_PORT_NUMBER_E = 0x1,
    SXD_PPAD_PNAT_OUT_OF_BAND_OR_PCI_E = 0x3
} sxd_ppad_pnat_t;

/**
 * ku_ppad_reg structure is used to store the PPAD register parameters
 */
struct ku_ppad_reg {
    uint8_t single_base_mac;
    sxd_ppad_pnat_t pnat;
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

#define SXD_MOCS_PORT_MASK_NUM 16

#define SXD_MOCS_GRP_MASK_NUM 4


typedef enum sxd_mocs_type {
    SXD_MOCS_TYPE_PPCNT_E = 0x1,
    SXD_MOCS_TYPE_MGPCB_E = 0x2,
    SXD_MOCS_TYPE_PBSR_E = 0x3,
    SXD_MOCS_TYPE_SBSRD_E = 0x4
} sxd_mocs_type_t;


typedef enum sxd_mocs_status {
    SXD_MOCS_STATUS_IDLE_E = 0x0,
    SXD_MOCS_STATUS_BUSY_E = 0x1
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

union mocs_entry {
    sxd_mocs_mocs_ppcnt_t mocs_ppcnt;
    sxd_mocs_mocs_mgpcb_t mocs_mgpcb;
    sxd_mocs_mocs_pbsr_t mocs_pbsr;
    sxd_mocs_mocs_sbsrd_t mocs_sbsrd;
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

#define SXD_RLCMLE_DIP_NUM 4


typedef enum sxd_rlcmle_action_type {
    SXD_RLCMLE_ACTION_TYPE_REMOTE_E = 0x0,
    SXD_RLCMLE_ACTION_TYPE_LOCAL_E = 0x1,
    SXD_RLCMLE_ACTION_TYPE_IP2ME_E = 0x2
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

#define SXD_MCQI_VERSION_STRING_NUM 92


typedef enum sxd_mcqi_info_type {
    SXD_MCQI_INFO_TYPE_CAPABILITIES_E = 0x0,
    SXD_MCQI_INFO_TYPE_VERSION_E = 0x1,
    SXD_MCQI_INFO_TYPE_ACTIVATION_METHOD_E = 0x5
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
    uint8_t pending_server_ac_power_cycle;
    uint8_t pending_server_dc_power_cycle;
    uint8_t pending_server_reboot;
    uint8_t pending_fw_reset;
    uint8_t auto_activate;
    uint8_t all_hosts_sync;
    uint8_t device_hw_reset;
} sxd_mcqi_mcqi_activation_method_t;

union mcqi_data {
    sxd_mcqi_mcqi_cap_t mcqi_cap;
    sxd_mcqi_mcqi_version_t mcqi_version;
    sxd_mcqi_mcqi_activation_method_t mcqi_activation_method;
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

#define SXD_TNUMT_UDIP_NUM 3

#define SXD_TNUMT_UDIP_PTR_NUM 5


typedef enum sxd_tnumt_record_type {
    SXD_TNUMT_RECORD_TYPE_IPV4_E = 0x0,
    SXD_TNUMT_RECORD_TYPE_IPV6_E = 0x1
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
 * ku_pevpb_reg structure is used to store the PEVPB register parameters
 */
struct ku_pevpb_reg {
    uint8_t local_port;
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
    SXD_SFGC_TYPE_IPV6_ALL_HOSTS_E = 0x7
} sxd_sfgc_type_t;


typedef enum sxd_sfgc_bridge_type {
    SXD_SFGC_BRIDGE_TYPE_TYPE0_E = 0x0,
    SXD_SFGC_BRIDGE_TYPE_TYPE1_E = 0x1
} sxd_sfgc_bridge_type_t;


typedef enum sxd_sfgc_table_type {
    SXD_SFGC_TABLE_TYPE_ANY_TYPE_E = 0x0,
    SXD_SFGC_TABLE_TYPE_FID_E = 0x4
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
    SXD_PMAOS_ADMIN_STATUS_ENABLED_ONCE_E = 0x3
} sxd_pmaos_admin_status_t;


typedef enum sxd_pmaos_oper_status {
    SXD_PMAOS_OPER_STATUS_INITIALIZING_E = 0x0,
    SXD_PMAOS_OPER_STATUS_PLUGGED_ENABLED_E = 0x1,
    SXD_PMAOS_OPER_STATUS_UNPLUGGED_E = 0x2,
    SXD_PMAOS_OPER_STATUS_MODULE_PLUGGED_WITH_ERROR_E = 0x3,
    SXD_PMAOS_OPER_STATUS_PLUGGED_DISABLED_E = 0x4
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
    SXD_PMAOS_ERROR_TYPE_PCIE_SYSTEM_POWER_SLOT_EXCEEDED_E = 0xc
} sxd_pmaos_error_type_t;


typedef enum sxd_pmaos_e {
    SXD_PMAOS_E_DO_NOT_GENERATE_EVENT_E = 0x0,
    SXD_PMAOS_E_GENERATE_EVENT_E = 0x1,
    SXD_PMAOS_E_GENERATE_SINGLE_EVENT_E = 0x2
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

/**
 * ku_rxltm_reg structure is used to store the RXLTM register parameters
 */
struct ku_rxltm_reg {
    uint8_t m_sel_update;
    uint8_t m_select;
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


typedef enum sxd_momte_mngr_type {
    SXD_MOMTE_MNGR_TYPE_HYPERVISOR_E = 0x0,
    SXD_MOMTE_MNGR_TYPE_LNM_E = 0x1
} sxd_momte_mngr_type_t;

/**
 * ku_momte_reg structure is used to store the MOMTE register parameters
 */
struct ku_momte_reg {
    uint8_t swid;
    uint8_t local_port;
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
    SXD_SVFA_MAPPING_TABLE_VNI_MAPPING_TABLE_E = 0x2
} sxd_svfa_mapping_table_t;


typedef enum sxd_svfa_trap_action {
    SXD_SVFA_TRAP_ACTION_NOP_E = 0x0,
    SXD_SVFA_TRAP_ACTION_TRAP_E = 0x1,
    SXD_SVFA_TRAP_ACTION_MIRROR_TO_CPU_E = 0x2,
    SXD_SVFA_TRAP_ACTION_MIRROR_E = 0x3,
    SXD_SVFA_TRAP_ACTION_DISCARD_ERROR_E = 0x4
} sxd_svfa_trap_action_t;

/**
 * ku_svfa_reg structure is used to store the SVFA register parameters
 */
struct ku_svfa_reg {
    uint8_t swid;
    uint8_t local_port;
    sxd_svfa_mapping_table_t mapping_table;
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
    SXD_MCC_INSTRUCTION_DOWNSRTEAM_DEVICE_TRANSFER_E = 0xc
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
    SXD_MCC_CONTROL_STATE_DOWNSRTEAM_DEVICE_TRANSFER_E = 0x9
} sxd_mcc_control_state_t;

/**
 * ku_mcc_reg structure is used to store the MCC register parameters
 */
struct ku_mcc_reg {
    uint16_t time_elapsed_since_last_cmd;
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
    uint8_t device_type;
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

/**
 * ku_pmtps_reg structure is used to store the PMTPS register parameters
 */
struct ku_pmtps_reg {
    uint8_t slot_index;
    uint8_t module;
    uint16_t module_type_admin;
    uint16_t module_type_connected;
    uint32_t eth_module_c2m;
};

/**
 * ku_access_pmtps_reg structure is used to store the access register PMTPS command parameters
 */
struct ku_access_pmtps_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmtps_reg     pmtps_reg; /**< pmtps_reg - pmtps register tlv */
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
