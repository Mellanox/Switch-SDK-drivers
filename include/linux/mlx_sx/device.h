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
struct sx_rx_timestamp {
    struct timespec timestamp; /* Linux time, HW time */
    u8              ts_type;   /* CQEv2 timestamp type */
};

#define SX_RX_TIMESTAMP_INIT(ptr, sec, nsec, type) \
    do {                                           \
        (ptr)->timestamp.tv_sec = (sec);           \
        (ptr)->timestamp.tv_nsec = (nsec);         \
        (ptr)->ts_type = (type);                   \
    } while (0)

#define SX_RX_TIMESTAMP_COPY(dst, src) \
    SX_RX_TIMESTAMP_INIT(dst, (src)->timestamp.tv_sec, (src)->timestamp.tv_nsec, (src)->ts_type)

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
    struct sx_rx_timestamp    rx_timestamp;
    u32                       user_def_val;
    u16                       dest_sysport;
    u8                        dest_is_lag;
    u8                        dest_lag_subport;
    u8                        mirror_reason;
    u8                        mirror_tclass;
    u16                       mirror_cong;
    u32                       mirror_lantency;
    u8                        device_id;
    pid_t                     target_pid;
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
    u64 rx_by_rdq[NUMBER_OF_SWIDS + 1][NUMBER_OF_RDQS];
    u64 rx_by_rdq_bytes[NUMBER_OF_SWIDS + 1][NUMBER_OF_RDQS];
    u64 tx_loopback_ok_by_synd[NUM_HW_SYNDROMES + 1];
    u64 tx_loopback_dropped_by_synd[NUM_HW_SYNDROMES + 1];
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
    unsigned long         dev_stuck_time;
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

    /* cr space address and size */
    void __iomem *cr_space_start;
    u32           cr_space_size;

    /* xm support */
    u8 xm_exists;
    u8 xm_num_local_ports;
    u8 xm_local_ports[SX_XM_MAX_LOCAL_PORTS_LEN];
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
    MTPPPC_REG_ID = 0x9090,
    MTPPTR_REG_ID = 0x9091,
    MTPTPT_REG_ID = 0x9092,
    MTPCPC_REG_ID = 0x9093,
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
struct sxd_emad_tlv_reg {
    __be16 type_len;
    __be16 reserved0;
};

#define EMAD_TLV_TYPE_SHIFT (11)
static inline u16 sxd_emad_tlv_type(const struct sxd_emad_tlv_reg *tlv)
{
    return be16_to_cpu(tlv->type_len) >> EMAD_TLV_TYPE_SHIFT;
}

static inline u16 sxd_emad_tlv_len(const struct sxd_emad_tlv_reg *tlv)
{
    return (be16_to_cpu(tlv->type_len) & ((1 << EMAD_TLV_TYPE_SHIFT) - 1)) * 4 /* sizeof DWORD */;
}

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
    u8                      dir_ing;
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
