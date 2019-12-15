/*
 * Copyright (c) 2010-2019,  Mellanox Technologies. All rights reserved.
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

#ifndef SX_DEVICE_H
#define SX_DEVICE_H

#include <linux/types.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/mlx_sx/kernel_user.h>

#ifndef SYSTEM_PCI
#define NO_PCI
#endif

/* According to CQe */
enum sx_packet_type {
    PKT_TYPE_IB_Raw = 0,
    PKT_TYPE_IB_non_Raw = 1,
    PKT_TYPE_ETH = 2,
    PKT_TYPE_FC = 3,
    PKT_TYPE_FCoIB = 4,
    PKT_TYPE_FCoETH = 5,
    PKT_TYPE_ETHoIB = 6,
    PKT_TYPE_OOB_CR_RESP = 7,
    PKT_TYPE_NUM
};
static const char *sx_cqe_packet_type_str[] = {
    "PKT_TYPE_IB_Raw",
    "PKT_TYPE_IB_non_Raw",
    "PKT_TYPE_ETH",
    "PKT_TYPE_FC",
    "PKT_TYPE_FCoIB",
    "PKT_TYPE_FCoETH",
    "PKT_TYPE_ETHoIB",
    "PKT_TYPE_OOB_CR_RESP"
};
static const int   sx_cqe_packet_type_str_len =
    sizeof(sx_cqe_packet_type_str) / sizeof(char *);
enum l2_type {
    L2_TYPE_DONT_CARE = -1,
    L2_TYPE_IB = 0,
    L2_TYPE_ETH = 1,
    L2_TYPE_FC = 2
};
enum sx_event {
    SX_EVENT_TYPE_COMP = 0x00,
    SX_EVENT_TYPE_CMD = 0x0a,
    SX_EVENT_TYPE_INTERNAL_ERROR = 0x08
};

enum {
    SX_DBELL_REGION_SIZE = 0xc00
};

static const char *port_vlan_match_str[] = {
    "GLOBAL",
    "PORT_VALID",
    "LAG_VALID",
    "VLAN_VALID",
};
static const int   port_vlan_match_str_len =
    sizeof(port_vlan_match_str) / sizeof(char *);
enum port_vlan_match {
    PORT_VLAN_MATCH_GLOBAL = 0,
    PORT_VLAN_MATCH_PORT_VALID = 1,
    PORT_VLAN_MATCH_LAG_VALID = 2,
    PORT_VLAN_MATCH_VLAN_VALID = 3
};
struct completion_info {
    u8                        swid;
    u16                       sysport;
    u16                       hw_synd;
    u8                        is_send;
    enum sx_packet_type       pkt_type;
    struct sk_buff           *skb;
    union ku_filter_critireas info;
    u8                        is_lag;
    u8                        lag_subport;
    u8                        is_tagged;
    u16                       vid;
    void                     *context;
    struct sx_dev            *dev;
    u32                       original_packet_size;
    u16                       bridge_id;
    u8                        has_timestamp;
    struct timespec           timestamp;
    u32                       user_def_val;
    u16                       dest_sysport;
    u8                        dest_is_lag;
    u8                        dest_lag_subport;
};

typedef void (*cq_handler)(struct completion_info*, void *);

struct sx_stats {
    u64 rx_by_pkt_type[NUMBER_OF_SWIDS + 1][SX_PKT_TYPE_MAX];
    u64 tx_by_pkt_type[NUMBER_OF_SWIDS + 1][SX_PKT_TYPE_MAX];
    u64 tx_by_pkt_type_bytes[NUMBER_OF_SWIDS + 1][SX_PKT_TYPE_MAX];
    u64 rx_by_synd[NUMBER_OF_SWIDS + 1][NUM_HW_SYNDROMES + 1];
    u64 rx_by_synd_bytes[NUMBER_OF_SWIDS + 1][NUM_HW_SYNDROMES + 1];
    u64 rx_unconsumed_by_synd[NUM_HW_SYNDROMES + 1][PKT_TYPE_NUM];
    u64 rx_eventlist_by_synd[NUM_HW_SYNDROMES + 1];
    u64 rx_eventlist_drops_by_synd[NUM_HW_SYNDROMES + 1];
};
struct sx_dev {
    struct sx_dev_cap     dev_cap;
    spinlock_t            profile_lock;   /* the profile's lock */
    struct sx_pci_profile profile;
    u8                    profile_set;
    u8                    dev_profile_set;
    u8                    first_ib_swid;
    unsigned long         flags;
    struct pci_dev       *pdev;
    u64                   bar0_dbregs_offset;
    u8                    bar0_dbregs_bar;
    void __iomem         *db_base;
    char                  board_id[SX_BOARD_ID_LEN];
    u16                   vsd_vendor_id;
    struct device         dev;   /* TBD - do we need it? */
    u16                   device_id;
    struct list_head      list;
    u64                   fw_ver;
    u8                    dev_stuck;
    u8                    global_flushing;
    u8                    dev_sw_rst_flow;
    struct cdev           cdev;

    /* multi-dev support */
    struct sx_stats          stats;
    u64                      eventlist_drops_counter;
    u64                      unconsumed_packets_counter;
    u64                      filtered_lag_packets_counter;
    u64                      filtered_port_packets_counter;
    u64                      loopback_packets_counter;
    struct work_struct       catas_work;
    struct workqueue_struct *generic_wq;
    int                      catas_poll_running;
    u8                       dev_specific_cb_init_done;
};

enum {
    /* Register IDs for auto generated registers are defined in include/linux/mlx_sx/auto_registers/reg.h */
    PPBT_REG_ID = 0x3003,
    QSPTC_REG_ID = 0x4009,
    QSTCT_REG_ID = 0x400b,
    PMLP_REG_ID = 0x5002,
    PMTU_REG_ID = 0x5003,
    PTYS_REG_ID = 0x5004,
    PPAD_REG_ID = 0x5005,
    PUDE_REG_ID = 0x5009,
    PLIB_REG_ID = 0x500a,
    PPTB_REG_ID = 0x500B,
    PSPA_REG_ID = 0x500d,
    PELC_REG_ID = 0x500e,
    PVLC_REG_ID = 0x500f,
    PMPR_REG_ID = 0x5013,
    SPZR_REG_ID = 0x6002,
    HCAP_REG_ID = 0x7001,
    HTGT_REG_ID = 0x7002,
    HPKT_REG_ID = 0x7003,
    HDRT_REG_ID = 0x7004,
    HOPF_REG_ID = 0x7081,
    MFCR_REG_ID = 0x9001,
    MFSC_REG_ID = 0x9002,
    MFSM_REG_ID = 0x9003,
    MFSL_REG_ID = 0x9004,
    MTCAP_REG_ID = 0x9009,
    MTBR_REG_ID = 0x900f,
    MFPA_REG_ID = 0x9010,
    MFBA_REG_ID = 0x9011,
    MFBE_REG_ID = 0x9012,
    MCIA_REG_ID = 0x9014,
    MGIR_REG_ID = 0x9020,
    MRSR_REG_ID = 0x9023,
    PMAOS_REG_ID = 0x5012,
    MFM_REG_ID = 0x901d,
    MJTAG_REG_ID = 0x901F,
    PMPC_REG_ID = 0x501F,
    MPSC_REG_ID = 0x9080,
    MOGCR_REG_ID = 0x9086,
    MTPPPC_REG_ID = 0x9090,
    MTPPTR_REG_ID = 0x9091,
    MTPTPT_REG_ID = 0x9092,
    MTPPS_REG_ID = 0x9053,
    MTUTC_REG_ID = 0x9055,
    PPBMC_REG_ID = 0x5052,
    PPMBE_REG_ID = 0x5053,
    SBCTR_REG_ID = 0xB00D,
};

enum {
    TLV_TYPE_END_E,
    TLV_TYPE_OPERATION_E,
    TLV_TYPE_DR_E,
    TLV_TYPE_REG_E,
    TLV_TYPE_USER_DATA_E
};

enum {
    EMAD_METHOD_QUERY = 1,
    EMAD_METHOD_WRITE = 2,
    EMAD_METHOD_SEND = 3,
    EMAD_METHOD_EVENT = 5,
};

enum {
    PORT_OPER_STATUS_UP = 1,
    PORT_OPER_STATUS_DOWN = 2,
    PORT_OPER_STATUS_FAILURE = 4,
};

struct sx_eth_hdr {
    __be64 dmac_smac1;
    __be32 smac2;
    __be16 ethertype;
    u8     mlx_proto;
    u8     ver;
};
struct emad_operation {
    __be16 type_len;
    u8     status;
    u8     reserved1;
    __be16 register_id;
    u8     r_method;
    u8     class;
    __be64 tid;
};
struct sx_emad {
    struct sx_eth_hdr     eth_hdr;
    struct emad_operation emad_op;
};

#define EMAD_TLV_TYPE_SHIFT (11)
struct sxd_emad_tlv_reg {
    __be16 type_len;
    __be16 reserved0;
};
struct sxd_emad_pude_reg {
    struct sx_emad          emad_header;
    struct sxd_emad_tlv_reg tlv_header;
    u8                      swid;
    u8                      local_port;
    u8                      admin_status;
    u8                      oper_status;
    __be32                  reserved3[3];
};
struct sxd_emad_ppbme_reg {
    struct sx_emad          emad_header;
    struct sxd_emad_tlv_reg tlv_header;
    u8                      reserved1;
    u8                      local_port;
    u8                      pnat_monitor_type;
    u8                      reserved2;
    u8                      reserved3[3];
    u8                      monitor_state;
    __be64                  reserved4;
};
struct sxd_emad_sbctr_reg {
    struct sx_emad          emad_header;
    struct sxd_emad_tlv_reg tlv_header;
    u8                      ievent;
    u8                      local_port;
    u8                      reserved1;
    u8                      fp_entity;
    u8                      reserved2[4];
    __be64                  tc_vec;
} __attribute__((packed));

#define SX_PORT_PHY_ID_OFFS (8)
#define SX_PORT_PHY_ID_MASK (0x0000FF00)
#define SX_PORT_PHY_ID_ISO(id) ((id) & (SX_PORT_PHY_ID_MASK))
#define SX_PORT_PHY_ID_GET(id) (SX_PORT_PHY_ID_ISO(id) >> SX_PORT_PHY_ID_OFFS)

#define SX_PORT_DEV_ID_OFFS (16)
#define SX_PORT_DEV_ID_MASK (0x0FFF0000)
#define SX_PORT_DEV_ID_ISO(id) ((id) & (SX_PORT_DEV_ID_MASK))
#define SX_PORT_DEV_ID_GET(id) (SX_PORT_DEV_ID_ISO(id) >> SX_PORT_DEV_ID_OFFS)

#define SX_PORT_TYPE_ID_OFFS (28)
#define SX_PORT_TYPE_ID_MASK (0xF0000000)
#define SX_PORT_TYPE_ID_ISO(id) ((id) & (SX_PORT_TYPE_ID_MASK))
#define SX_PORT_TYPE_ID_GET(id) (SX_PORT_TYPE_ID_ISO(id) >> SX_PORT_TYPE_ID_OFFS)

#define SX_PORT_LAG_ID_OFFS (8)
#define SX_PORT_LAG_ID_MASK (0x000FFF00)
#define SX_PORT_LAG_ID_ISO(id) ((id) & (SX_PORT_LAG_ID_MASK))
#define SX_PORT_LAG_ID_GET(id) (SX_PORT_LAG_ID_ISO(id) >> SX_PORT_LAG_ID_OFFS)

#define CPU_PORT_PHY_ID              (0)
#define UCROUTE_CPU_PORT_DEV_MASK    (0x0FC0)
#define UCROUTE_CPU_DEV_BIT_OFFSET   (6)
#define UCROUTE_DEV_ID_BIT_OFFSET    (10)
#define UCROUTE_PHY_PORT_BITS_OFFSET (4)
#define UCROUTE_CPU_PORT_PREFIX      (0xB000)

#define SX_TELE_THRS_VALID_SET(id) ((id) |= 0x1)

#define SX_TELE_THRS_FIRST_EVENT_GET(id) (((id) >> 1) & 0x1)
#define SX_TELE_THRS_FIRST_EVENT_SET(id) ((id) |= 0x2)

#define SX_TELE_THRS_MAYBE_MASK (0x4)
#define SX_TELE_THRS_MAYBE_GET(id) (((id) >> 2) & 0x1)
#define SX_TELE_THRS_MAYBE_SET(id) ((id) |= 0x4)
#define SX_TELE_THRS_MAYBE_CLR(id) ((id) &= ~(SX_TELE_THRS_MAYBE_MASK))

u16 translate_user_port_to_sysport(struct sx_dev *dev, u32 log_port, int* is_lag);
u32 translate_sysport_to_user_port(struct sx_dev *dev, u16 port, u8 is_lag);
void * sx_get_dev_context(void);

typedef enum sxd_trap_id {
    /* GENERAL */
    SXD_TRAP_ID_GENERAL_FDB = 0x01,
    SXD_TRAP_ID_GENERAL_DR_IPC = 0x02,
    SXD_TRAP_ID_GENERAL_DR_RES = 0x04,
    SXD_TRAP_ID_GENERAL_ETH_EMAD = 0x05,
    SXD_TRAP_ID_FDB = 0x06,

    /* EVENTS */
    SXD_TRAP_ID_PUDE = 0x08,
    SXD_TRAP_ID_PMPE = 0x09,
    SXD_TRAP_ID_FLAE = 0x0A,
    SXD_TRAP_ID_FORE = 0x0B,
    SXD_TRAP_ID_TMPW = 0x0C,
    SXD_TRAP_ID_CPUWD = 0x0D,
    SXD_TRAP_ID_PPBME = 0x101,
    SXD_TRAP_ID_PACKET_RECEIVED = 0x103,

    /* ETHERNET L2 */
    SXD_TRAP_ID_ETH_L2_STP = 0x10,
    SXD_TRAP_ID_ETH_L2_LACP = 0x11,
    SXD_TRAP_ID_ETH_L2_EAPOL = 0x12,
    SXD_TRAP_ID_ETH_L2_LLDP = 0x13,
    SXD_TRAP_ID_ETH_L2_MMRP = 0x14,
    SXD_TRAP_ID_ETH_L2_MVRP = 0x15,
    SXD_TRAP_ID_ETH_L2_RPVST = 0x16,

    /* PTP */
    SXD_TRAP_ID_PTP_PTP0 = 0x28,
    SXD_TRAP_ID_PTP_PTP1 = 0x29,
    SXD_TRAP_ID_PTP_ING_EVENT = 0x2D,
    SXD_TRAP_ID_PTP_EGR_EVENT = 0x2E,

    SXD_TRAP_ID_ETH_L2_IGMP_TYPE_QUERY = 0x30,
    SXD_TRAP_ID_ETH_L2_IGMP_TYPE_V1_REPORT = 0x31,
    SXD_TRAP_ID_ETH_L2_IGMP_TYPE_V2_REPORT = 0x32,
    SXD_TRAP_ID_ETH_L2_IGMP_TYPE_V3_REPORT = 0x34,
    SXD_TRAP_ID_ETH_L2_IGMP_TYPE_V2_LEAVE = 0x33,
    SXD_TRAP_ID_ETH_L2_UDLD = 0x18,
    SXD_TRAP_ID_ETH_L2_DHCP = 0x19,
    SXD_TRAP_ID_ETH_CONF_TYPE0 = 0x35,
    SXD_TRAP_ID_ETH_CONF_TYPE1 = 0x36,
    SXD_TRAP_ID_ETH_L2_PKT_SAMPLE = 0x38,
    SXD_TRAP_ID_FDB_MISS = 0x3a,
    SXD_TRAP_ID_FDB_MISMATCH = 0x3b,
    SXD_TRAP_ID_ICMPV6_CONF_TYPE0 = 0x48,
    SXD_TRAP_ID_ICMPV6_CONF_TYPE1 = 0x49,
    SXD_TRAP_ID_OVERLAY_ICMPV6_CONF_TYPE = 0x4a,
    SXD_TRAP_ID_RARP_OPCODES = 0x4f,

    SXD_TRAP_ID_ETH_L2_PACKET_SAMPLING = 0x38,

    /* FCoE */
    SXD_TRAP_ID_FCOE_FIP = 0x20,

    /* Telemetry threshold crossing */
    SXD_TRAP_ID_SB_CONG_TX_PORT = 0x2F,

    /* ECN */
    SXD_TRAP_ID_DECAP_ECN0 = 0x40,
    SXD_TRAP_ID_DECAP_ECN1 = 0x41,

    /* Router */
    SXD_TRAP_ID_ARP_REQUEST = 0x50,
    SXD_TRAP_ID_ARP_RESPONSE = 0x51,
    SXD_TRAP_ID_ETH_L3_MTUERROR = 0x52,
    SXD_TRAP_ID_ETH_L3_TTLERROR = 0x53,
    SXD_TRAP_ID_ETH_L3_LBERROR = 0x54,
    SXD_TRAP_ID_OSPF = 0x55,
    SXD_TRAP_ID_RIP_V1 = 0x56,
    SXD_TRAP_ID_RIP_V2 = 0x57,
    SXD_TRAP_ID_PIM = 0x58,
    SXD_TRAP_ID_VRRP = 0x59,
    SXD_TRAP_ID_VRRP_IPV6 = 0x7a,
    SXD_TRAP_ID_RESERVED_MC = 0x5A,
    SXD_TRAP_ID_IPBC = 0x5B,
    SXD_TRAP_ID_ETH_L3_RPF = 0x5C,
    SXD_TRAP_ID_ETH_L3_ASSERT = 0x5D,
    SXD_TRAP_ID_IP2ME = 0x5F,
    SXD_TRAP_ID_IPTRAP_MIN = 0x1c0,
    SXD_TRAP_ID_IPTRAP_MAX = 0x1ff,
    SXD_TRAP_ID_RTR_INGRESS0 = 0x70,
    SXD_TRAP_ID_RTR_INGRESS1 = 0x71,
    SXD_TRAP_ID_RTR_INGRESS2 = 0x72,
    SXD_TRAP_ID_RTR_INGRESS3 = 0x73,
    SXD_TRAP_ID_RTR_EGRESS0 = 0x80,
    SXD_TRAP_ID_RTR_EGRESS1 = 0x81,
    SXD_TRAP_ID_RTR_EGRESS2 = 0x82,
    SXD_TRAP_ID_RTR_EGRESS3 = 0x83,
    SXD_TRAP_ID_HOST_MISS_IPV4 = 0x90,
    SXD_TRAP_ID_HOST_MISS_IPV6 = 0x92,
    SXD_TRAP_ID_BFD_IPV4 = 0xd0,
    SXD_TRAP_ID_BFD_IPV6 = 0xd1,
    SXD_TRAP_ID_SSH_IPV4 = 0xd2,
    SXD_TRAP_ID_SSH_IPV6 = 0xd3,
    SXD_TRAP_ID_PING_IPV4 = 0xd4,
    SXD_TRAP_ID_PING_IPV6 = 0xd5,
    SXD_TRAP_ID_ROUTER_ALERT_IPV4 = 0xd6,
    SXD_TRAP_ID_ROUTER_ALERT_IPV6 = 0xd7,
    SXD_TRAP_ID_IPV4_DHCP = 0x8f,
    SXD_TRAP_ID_IPV4_SNMP = 0xda,
    SXD_TRAP_ID_IPV6_SNMP = 0xdb,
    SXD_TRAP_ID_ROUTER_ARPBC = 0xe0,
    SXD_TRAP_ID_ROUTER_ARPUC = 0xe1,
    SXD_TRAP_ID_ROUTER_RARP_OPCODES = 0xe2,

    /*IPv6 L3*/
    SXD_TRAP_ID_IPV6_UNSPECIFIED_ADDRESS = 0x60,
    SXD_TRAP_ID_IPV6_LINK_LOCAL_DST = 0x61,
    SXD_TRAP_ID_IPV6_LINK_LOCAL_SRC = 0x62,
    SXD_TRAP_ID_IPV6_ALL_NODES_LINK = 0x63,
    SXD_TRAP_ID_IPV6_OSPF = 0x64,
    SXD_TRAP_ID_IPV6_DHCP = 0x69,

    /* IPv6 (SwitchX) */
    SXD_TRAP_ID_IPV6_ROUTER_SOLICITATION = 0x6a,
    SXD_TRAP_ID_IPV6_ROUTER_ADVERTISEMENT = 0x6b,
    SXD_TRAP_ID_IPV6_NEIGHBOR_SOLICITATION = 0x6c,
    SXD_TRAP_ID_IPV6_NEIGHBOR_ADVERTISEMENT = 0x6d,
    SXD_TRAP_ID_IPV6_REDIRECTION = 0x6e,

    /* IPv6 (Spectrum) */
    SXD_TRAP_ID_IPV6_ALL_ROUTERS_LINK = 0x6f,
    SXD_TRAP_ID_L3_IPV6_ROUTER_SOLICITATION = 0x8a,
    SXD_TRAP_ID_L3_IPV6_ROUTER_ADVERTISEMENT = 0x8b,
    SXD_TRAP_ID_L3_IPV6_NEIGHBOR_SOLICITATION = 0x8c,
    SXD_TRAP_ID_L3_IPV6_NEIGHBOR_ADVERTISEMENT = 0x8d,
    SXD_TRAP_ID_L3_IPV6_REDIRECTION = 0x8e,

    /*IPv6 L2*/
    SXD_TRAP_ID_IPV6_MLD_V1_V2 = 0x65,
    SXD_TRAP_ID_IPV6_MLD_V1_REPORT = 0x66,
    SXD_TRAP_ID_IPV6_MLD_V1_DONE = 0x67,
    SXD_TRAP_ID_IPV6_MLD_V2_REPORT = 0x68,

    /* InfiniBand */
    SXD_TRAP_ID_INFINIBAND_QP0 = 0xf0,
    SXD_TRAP_ID_INFINIBAND_QP1 = 0xf1,
    SXD_TRAP_ID_INFINIBAND_OTHER_QPS = 0xf2,
    SXD_TRAP_ID_INFINIBAND_EXTERNAL_SMA = 0x5e,
    SXD_TRAP_ID_INFINIBAND_IN_NV_ACCESS_REG = 0xf7,
    SXD_TRAP_ID_INFINIBAND_IB_FMAD_RCV = 0xf8,
    SXD_TRAP_ID_INFINIBAND_RESET_CMD = 0x102,

    /* ACL */
    SXD_TRAP_ID_ACL_MIN = 0x1c0,
    SXD_TRAP_ID_ACL_MAX = 0x1ef,

    /* MPLS */
    SXD_TRAP_ID_MPLS_ILM_MISS = 0x98,
    SXD_TRAP_ID_MPLS_LDP = 0x99,
    SXD_TRAP_ID_MPLS_LB_LSP_PING = 0x9a,
    SXD_TRAP_ID_MPLS_ILM0 = 0xa0,
    SXD_TRAP_ID_MPLS_ILM1 = 0xa1,
    SXD_TRAP_ID_MPLS_NHLFE0 = 0xa8,
    SXD_TRAP_ID_MPLS_NHLFE1 = 0xa9,

    /* BGP */
    SXD_TRAP_ID_IPV4_BGP = 0x88,
    SXD_TRAP_ID_IPV6_BGP = 0x89,

    /* SPAN */
    SXD_TRAP_ID_MIRROR = 0x3f,

    /* Tunneling */
    SXD_TRAP_ID_DECAP_ENCAP = 0xb0,
    SXD_TRAP_ID_IPIP_DECAP_ERROR = 0xb1,
    SXD_TRAP_ID_IPIP_ERROR = 0xb2,
    SXD_TRAP_ID_NVE_DECAP_IGMP = 0xb6,
    SXD_TRAP_ID_NVE_DECAP_ARP = 0xb8,
    SXD_TRAP_ID_NVE_DECAP_TAG_ERROR = 0xb9,
    SXD_TRAP_ID_NVE_IPV4_DHCP = 0xba,
    SXD_TRAP_ID_NVE_IPV6_DHCP = 0xbb,
    SXD_TRAP_ID_NVE_DECAP_FRAG_ERROR = 0xbc,
    SXD_TRAP_ID_NVE_ENCAP_ARP = 0xbd,
    SXD_TRAP_ID_NVE_DECAP_ETH = 0xbe,
    SXD_TRAP_ID_NVE_DECAP_MLD = 0xbf,

    /* Discards */
    SXD_TRAP_ID_DISCARD_ING_PACKET = 0x110,
    SXD_TRAP_ID_DISCARD_ING_SWITCH = 0x111,
    SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH = 0x112,
    SXD_TRAP_ID_DISCARD_ING_ROUTER = 0x113,
    SXD_TRAP_ID_DISCARD_ING_LSR = 0x114,
    SXD_TRAP_ID_DISCARD_ROUTER = 0x115,
    SXD_TRAP_ID_DISCARD_LSR = 0x116,
    SXD_TRAP_ID_DISCARD_DEC = 0x117,
    SXD_TRAP_ID_DISCARD_OVERLAY_SWITCH = 0x118,
    SXD_TRAP_ID_DISCARD_ISOLATION = 0x119,
    SXD_TRAP_ID_DISCARD_NON_ROUTED = 0x11a,
    SXD_TRAP_ID_DISCARD_EGR_LSR = 0x11b,
    SXD_TRAP_ID_DISCARD_MC_SCOPE = 0x11c,
    SXD_TRAP_ID_DISCARD_ROUTER2 = 0x130,
    SXD_TRAP_ID_DISCARD_ROUTER3 = 0x131,
    SXD_TRAP_ID_DISCARD_LSR2 = 0x132,
    SXD_TRAP_ID_DISCARD_LSR3 = 0x133,

    /* Extended Discards */
    SXD_TRAP_ID_DISCARD_ING_PACKET_SMAC_MC = 0x140,
    SXD_TRAP_ID_DISCARD_ING_PACKET_SMAC_DMAC = 0x141,
    SXD_TRAP_ID_DISCARD_ING_PACKET_RSV_MAC = 0x142,
    SXD_TRAP_ID_DISCARD_ING_SWITCH_VTAG_ALLOW = 0x148,
    SXD_TRAP_ID_DISCARD_ING_SWITCH_VLAN = 0x149,
    SXD_TRAP_ID_DISCARD_ING_SWITCH_STP = 0x14A,
    SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_UC = 0x150,
    SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_MC_NULL = 0x151,
    SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_LB = 0x152,
    SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_NO_PORTS = 0x153,

    SXD_TRAP_ID_DISCARD_ING_ROUTER_NO_HDR = 0x160,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_UC_DIP_MC_DMAC = 0x161,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_DIP_LB = 0x162,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_MC = 0x163,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_CLASS_E = 0x164,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_LB = 0x165,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_UNSP = 0x166,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_IP_HDR = 0x167,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_MC_DMAC = 0x168,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_DIP = 0x169,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_BC = 0x16A,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_DIP_LOCAL_NET = 0x16B,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_DIP_LINK_LOCAL = 0x16C,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_LINK_LOCAL = 0x16D,

    SXD_TRAP_ID_DISCARD_ING_LSR_NO_LABEL = 0x170,
    SXD_TRAP_ID_DISCARD_ING_LSR_UC_ET = 0x171,
    SXD_TRAP_ID_DISCARD_ING_LSR_MC_DMAC = 0x172,

    SXD_TRAP_ID_DISCARD_ROUTER_IRIF_EN = 0x178,
    SXD_TRAP_ID_DISCARD_ROUTER_ERIF_EN = 0x179,
    SXD_TRAP_ID_DISCARD_ROUTER_ERIF_FWD = 0x17A,
    SXD_TRAP_ID_DISCARD_ROUTER_LPM4 = 0x17B,
    SXD_TRAP_ID_DISCARD_ROUTER_LPM6 = 0x17C,

    SXD_TRAP_ID_DISCARD_LSR_MIN_LABEL = 0x180,
    SXD_TRAP_ID_DISCARD_LSR_MAX_LABEL = 0x181,
    SXD_TRAP_ID_DISCARD_LSR_LB = 0x182,

    SXD_TRAP_ID_DISCARD_DEC_PKT = 0x188,
    SXD_TRAP_ID_DISCARD_DEC_DIS = 0x189,
    SXD_TRAP_ID_DISCARD_OVERLAY_SWITCH_SMAC_MC = 0x190,
    SXD_TRAP_ID_DISCARD_OVERLAY_SWITCH_SMAC_DMAC = 0x191,

    SXD_TRAP_ID_DISCARD_EGR_LSR_NO_LABEL = 0x1A8,
    SXD_TRAP_ID_DISCARD_EGR_LSR_NO_IP = 0x1A9,
    SXD_TRAP_ID_DISCARD_EGR_LSR_PHP_NO_IP = 0x1AA,

    SXD_TRAP_ID_DISCARD_MC_SCOPE_IPV6_0 = 0x1B0,
    SXD_TRAP_ID_DISCARD_MC_SCOPE_IPV6_1 = 0x1B1,

    /* SW Generated Events */
    SXD_TRAP_ID_SIGNAL = 0x200,
    SXD_TRAP_ID_NEW_DEVICE_ADD = 0x201,                  /**< device add event */
    SXD_TRAP_ID_MAC_LEARNING_EVENT = 0x202,              /**< mac learning event */
    SXD_TRAP_ID_MAC_AGING_EVENT = 0x203,                 /**< mac aging event */
    SXD_TRAP_ID_NEED_TO_RESOLVE_ARP = 0x204,             /**< need to resolve ARP  */
    SXD_TRAP_ID_NO_NEED_TO_RESOLVE_ARP = 0x205,          /**< no need to resolve ARP  */
    SXD_TRAP_ID_FDB_EVENT = 0x206,                       /**< FDB event */
    SXD_TRAP_ID_RM_SDK_TABLE_THRESHOLD_EVENT = 0x207,
    SXD_TRAP_ID_RM_HW_TABLE_THRESHOLD_EVENT = 0x208,
    SXD_TRAP_ID_FDB_SRC_MISS = 0x209,                    /**< FDB SRC MISS trap */
    SXD_TRAP_ID_ROUTER_NEIGH_ACTIVITY = 0x20a,
    SXD_TRAP_ID_ASYNC_API_COMPLETE_EVENT = 0x20b,
    SXD_TRAP_ID_ROUTER_MC_ACTIVITY = 0x20c,              /**< router mc activity */
    SXD_TRAP_ID_FDB_IP_ADDR_ACTIVITY = 0x20d,
    SXD_TRAP_ID_TRANSACTION_ERROR = 0x20e,
    SXD_TRAP_ID_BFD_TIMEOUT_EVENT = 0x20f,
    SXD_TRAP_ID_BFD_PACKET_EVENT = 0x210,

    /*User defined trap ID*/
    SXD_TRAP_ID_IP2ME_CUSTOM0 = 0xc0,
    SXD_TRAP_ID_IP2ME_CUSTOM1 = 0xc1,

    SXD_TRAP_ID_MIN = SXD_TRAP_ID_GENERAL_FDB,
    SXD_TRAP_ID_MAX = SXD_TRAP_ID_BFD_PACKET_EVENT,
} sxd_trap_id_t;


#define NUM_OF_LAG_BITS 12

/* Bridge Netdev values */
/* MIN_BRIDGE_ID = 4k */
#define MIN_BRIDGE_ID 4096
/* MAX_BRIDGE_ID = (15k - 1) */
#define MAX_BRIDGE_ID 15359
/* MAX_BRIDGE_NUM */
#define MAX_BRIDGE_NUM (MAX_BRIDGE_ID - MIN_BRIDGE_ID + 1)

/** This enum defines bitmask values for combinations of port types */
enum sx_port_type {
    SX_PORT_TYPE_NETWORK = 0,
    SX_PORT_TYPE_LAG = 1,
    SX_PORT_TYPE_VPORT = 2,
    SX_PORT_TYPE_NVE = 8,
    SX_PORT_TYPE_MIN = SX_PORT_TYPE_NETWORK,
    SX_PORT_TYPE_MAX = SX_PORT_TYPE_NVE,
};

/* Length of TLV in DWORDs*/
#define TLV_LEN 4

enum {
    TLV_REQUEST = 0,
    TLV_RESPONSE = 1,
};

enum {
    EMAD_CLASS_RESERVED = 0x00,
    EMAD_CLASS_REG_ACCESS = 0x01,
    EMAD_CLASS_IPC = 0x02,
};

#endif /* SX_DEVICE_H */
