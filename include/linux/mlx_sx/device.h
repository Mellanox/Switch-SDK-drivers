/*
 * Copyright (C) 2010-2023 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of NVIDIA CORPORATION & AFFILIATES, Ltd.
 * (the "Company") and all right, title, and interest in and to the software product,
 * including all associated intellectual property rights, are and shall
 * remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 *
 */

#ifndef SX_DEVICE_H
#define SX_DEVICE_H

#include <linux/version.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/mlx_sx/kernel_user.h>

/* same type definition exists in sxd_libs. because of SWIG issues, need to separate them.
 * if you ever change this type definition, do so also in sxd_libs!
 */
typedef uint8_t sxd_dev_id_t;

/* According to CQe */
enum sx_packet_type {
    PKT_TYPE_IB_Raw      = 0,
    PKT_TYPE_IB_non_Raw  = 1,
    PKT_TYPE_ETH         = 2,
    PKT_TYPE_FC          = 3,
    PKT_TYPE_FCoIB       = 4,
    PKT_TYPE_FCoETH      = 5,
    PKT_TYPE_ETHoIB      = 6,
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

static const int sx_cqe_packet_type_str_len =
    sizeof(sx_cqe_packet_type_str) / sizeof(char *);
enum l2_type {
    L2_TYPE_DONT_CARE = -1,
    L2_TYPE_IB        = 0,
    L2_TYPE_ETH       = 1,
    L2_TYPE_FC        = 2
};
enum sx_event {
    SX_EVENT_TYPE_COMP           = 0x00,
    SX_EVENT_TYPE_CMD            = 0x0a,
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
    PORT_VLAN_MATCH_GLOBAL     = 0,
    PORT_VLAN_MATCH_PORT_VALID = 1,
    PORT_VLAN_MATCH_LAG_VALID  = 2,
    PORT_VLAN_MATCH_VLAN_VALID = 3
};
struct sx_rx_timestamp {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    struct timespec64 timestamp; /* Linux time, HW time */
#else
    struct timespec timestamp; /* Linux time, HW time */
#endif
    u8 ts_type;                /* CQEv2 timestamp type */
};

#define SX_RX_TIMESTAMP_INIT(ptr, sec, nsec, type) \
    do {                                           \
        (ptr)->timestamp.tv_sec = (sec);           \
        (ptr)->timestamp.tv_nsec = (nsec);         \
        (ptr)->ts_type = (type);                   \
    } while (0)

#define SX_RX_TIMESTAMP_COPY(dst, src) \
    SX_RX_TIMESTAMP_INIT(dst, (src)->timestamp.tv_sec, (src)->timestamp.tv_nsec, (src)->ts_type)

#define SX_CQE_MIRROR_LATENCY_INVALID 0xFFFFFF
#define SX_CQE_MIRROR_CONG_INVALID    0xFFF
#define SX_CQE_MIRROR_TCLASS_INVALID  0x1F
#define SX_CQE_MIRROR_LATENCY_SHIFT   6
#define SX_CQE_MIRROR_CONG_SHIFT      13

struct completion_info {
    u8                        swid;
    u16                       sysport;
    u16                       hw_synd;
    u8                        is_send;
    enum sx_packet_type       pkt_type;
    struct sk_buff           *skb;
    union ku_filter_critireas info;
    u8                        is_lag;
    u16                       lag_subport;
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
    u16                       dest_lag_subport;
    u8                        mirror_reason;
    u8                        mirror_tclass;
    u16                       mirror_cong;
    u32                       mirror_lantency;
    u8                        mirror_elephant;
    sxd_dev_id_t              device_id;
    pid_t                     target_pid;
};

typedef void (*cq_handler)(struct completion_info*, void *);

struct sx_dev {
    /* DON'T ADD HERE ANY NEW FIELD - DO THAT IN struct sx_priv */
    struct pci_dev *pdev;
    sxd_dev_id_t    device_id;
    u64             fw_ver;
};

enum {
    /* Register IDs for auto generated registers are defined in include/linux/mlx_sx/auto_registers/reg.h */
    PPBT_REG_ID     = 0x3003,
    PMLP_REG_ID     = 0x5002,
    PMTU_REG_ID     = 0x5003,
    PTYS_REG_ID     = 0x5004,
    PPAD_REG_ID     = 0x5005,
    PUDE_REG_ID     = 0x5009,
    PLIB_REG_ID     = 0x500a,
    PPTB_REG_ID     = 0x500B,
    PSPA_REG_ID     = 0x500d,
    PELC_REG_ID     = 0x500e,
    PVLC_REG_ID     = 0x500f,
    PMPR_REG_ID     = 0x5013,
    PDDR_REG_ID     = 0x5031,
    SPZR_REG_ID     = 0x6002,
    HCAP_REG_ID     = 0x7001,
    HTGT_REG_ID     = 0x7002,
    HPKT_REG_ID     = 0x7003,
    HDRT_REG_ID     = 0x7004,
    HOPF_REG_ID     = 0x7081,
    MFCR_REG_ID     = 0x9001,
    MFSC_REG_ID     = 0x9002,
    MFSM_REG_ID     = 0x9003,
    MFSL_REG_ID     = 0x9004,
    MTCAP_REG_ID    = 0x9009,
    MTBR_REG_ID     = 0x900f,
    MFPA_REG_ID     = 0x9010,
    MFBA_REG_ID     = 0x9011,
    MFBE_REG_ID     = 0x9012,
    MCIA_REG_ID     = 0x9014,
    MGIR_REG_ID     = 0x9020,
    MRSR_REG_ID     = 0x9023,
    PMAOS_REG_ID    = 0x5012,
    MFM_REG_ID      = 0x901d,
    MJTAG_REG_ID    = 0x901F,
    PMPC_REG_ID     = 0x501F,
    MPSC_REG_ID     = 0x9080,
    MTPPPC_REG_ID   = 0x9090,
    MTPPTR_REG_ID   = 0x9091,
    MTPTPT_REG_ID   = 0x9092,
    MTPPS_REG_ID    = 0x9053,
    MTUTC_REG_ID    = 0x9055,
    PPBMC_REG_ID    = 0x5052,
    PPMBE_REG_ID    = 0x5053,
    SBCTR_REG_ID    = 0xB00D,
    MTPSPU_REG_ID   = 0x9094,
    MTPPSE_REG_ID   = 0x9054,
    MOPIR_V2_REG_ID = 0x909b,
    MOPR_REG_ID     = 0x909c,
};

enum {
    TLV_TYPE_END_E,
    TLV_TYPE_OPERATION_E,
    TLV_TYPE_DR_E,
    TLV_TYPE_REG_E,
    TLV_TYPE_USER_DATA_E
};

typedef enum {
    /* PRM values */
    EMAD_METHOD_QUERY = 1,
    EMAD_METHOD_WRITE = 2,
    EMAD_METHOD_SEND  = 3,
    EMAD_METHOD_EVENT = 5,
} sx_emad_method_e;

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

struct workqueue_struct* sx_health_check_create_monitored_workqueue(const char* name);
void sx_health_check_destroy_monitored_workqueue(struct workqueue_struct * wq);

struct sxd_emad_pmpe_reg {
    struct sx_emad          emad_header;
    struct sxd_emad_tlv_reg tlv_header;
    u8                      slot_index;
    u8                      module;
    u8                      reserved1;
    u8                      module_status;
    u16                     reserved2;
    u8                      error_type;
    u8                      reserved3;
    __be32                  reserved4[2];
};


struct sxd_emad_mcion_reg {
    struct sx_emad          emad_header;
    struct sxd_emad_tlv_reg tlv_header;
    u8                      reserved1;
    u8                      module;
    u8                      slot_index;
    u16                     reserved2;
    u16                     module_status_bits;
    u32                     reserved3;
    u16                     module_status_bits_valid;
    u8                      reserved4;
    u8                      module_inputs;
    u16                     reserved5;
    u8                      reserved6;
    u8                      module_inputs_mask;
    __be32                  reserved7;
};

struct sxd_emad_pude_reg {
    struct sx_emad          emad_header;
    struct sxd_emad_tlv_reg tlv_header;
    u8                      swid;
    u8                      local_port;
    u8                      admin_status_lp_msb;
    u8                      oper_status;
    __be32                  reserved3[3];
};
struct sxd_emad_ppbme_reg {
    struct sx_emad          emad_header;
    struct sxd_emad_tlv_reg tlv_header;
    u8                      reserved1;
    u8                      local_port;
    u8                      pnat_msb_monitor_type;
    u8                      reserved2;
    u8                      reserved3[3];
    u8                      monitor_state;
    __be64                  reserved4;
};
struct sxd_emad_ppbmc_reg {
    struct sx_emad          emad_header;
    struct sxd_emad_tlv_reg tlv_header;
    u8                      reserved1;
    u8                      local_port;
    u8                      pnat_msb_monitor_type;
    u8                      reserved2;
    u8                      e_ievent_event_ctrl;
    u8                      monitor_ctrl;
    u8                      reserved3;
    u8                      monitor_state;
    __be64                  reserved4;
};
struct sxd_emad_sbctr_reg {
    struct sx_emad          emad_header;
    struct sxd_emad_tlv_reg tlv_header;
    u8                      ievent;
    u8                      local_port;
    u8                      lp_msb_and_dir_ing;
    u8                      fp_entity;
    u8                      reserved2[4];
    __be64                  tc_vec;
} __attribute__((packed));

#define SX_PORT_PHY_ID_OFFS (0)
#define SX_PORT_PHY_ID_MASK (0x000003FF)
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

#define SX_PORT_LAG_ID_OFFS (0)
#define SX_PORT_LAG_ID_MASK (0x000003FF)
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

/**
 * Get bit # BIT in a bit array called BITMAP which is composed
 * of LEN words, where each word is of WID bits.
 * Assuming: BIT < LEN x WID.
 */
#define SX_CORE_BITMAP_GET(BITMAP, LEN, WID, BIT) \
    ((BITMAP[((int)(BIT)) / ((int)(WID))]) & (1 << (((int)(BIT)) % ((int)(WID)))))

/**
 * Set bit # BIT in a bit array called BITMAP which is composed
 * of LEN words, where each word is of WID bits.
 * Assuming: BIT < LEN x WID.
 */
#define SX_CORE_BITMAP_SET(BITMAP, LEN, WID, BIT) \
    (BITMAP[((int)(BIT)) / ((int)(WID))] |= 1 << (((int)(BIT)) % ((int)(WID))))


#define NUM_OF_LAG_BITS 12

/* Bridge Netdev values */
/* MIN_BRIDGE_ID = 4k */
#define MIN_BRIDGE_ID 4096
/* MAX_BRIDGE_ID = (20k - 1) */
#define MAX_BRIDGE_ID 20479
/* MAX_BRIDGE_NUM */
#define MAX_BRIDGE_NUM (MAX_BRIDGE_ID - MIN_BRIDGE_ID + 1)

/** This enum defines bitmask values for combinations of port types */
enum sx_port_type {
    SX_PORT_TYPE_NETWORK = 0,
    SX_PORT_TYPE_LAG     = 1,
    SX_PORT_TYPE_VPORT   = 2,
    SX_PORT_TYPE_NVE     = 8,
    SX_PORT_TYPE_MIN     = SX_PORT_TYPE_NETWORK,
    SX_PORT_TYPE_MAX     = SX_PORT_TYPE_NVE,
};

/* Length of TLV in DWORDs*/
#define TLV_LEN 4

enum {
    TLV_REQUEST  = 0,
    TLV_RESPONSE = 1,
};

enum {
    EMAD_CLASS_RESERVED   = 0x00,
    EMAD_CLASS_REG_ACCESS = 0x01,
    EMAD_CLASS_IPC        = 0x02,
};

int send_trap(const void *buf,
              uint32_t    buf_size,
              uint16_t    trap_id,
              u8          is_from_user,
              u8          device_id,
              pid_t       target_pid,
              gfp_t       gfp_mask);

/* According to WQe */
enum sx_packet_type_wqe {
    WQE_PKT_TYPE_IBGen2_no_BTH = 0x4,
    WQE_PKT_TYPE_IBGen2        = 0x5,
    WQE_PKT_TYPE_NVLINK_LOCAL  = 0x6,
    WQE_PKT_TYPE_NVLoIB        = 0x7,
    WQE_PKT_TYPE_RAW_IB        = 0x8,
    WQE_PKT_TYPE_IB_TRANSPORT  = 0x9,
    WQE_PKT_TYPE_ETH           = 0xa,
    WQE_PKT_TYPE_FCOIB         = 0xc,
    WQE_PKT_TYPE_FCOE          = 0xd,
    WQE_PKT_TYPE_IPoIB         = 0xf
};

/* According to TX_Base header V0 */
enum tx_base_v0_header_protocol {
    PROTOCOL_INFINIBAND    = 0x0,
    PROTOCOL_ETHERNET      = 0x1,
    PROTOCOL_IBGen2        = 0x4,
    PROTOCOL_NVLINK_LOCAL  = 0x5,
    PROTOCOL_NVLINK_GLOBAL = 0x6,
    PROTOCOL_NVoIB         = 0x7
};

enum tx_base_v0_header_ctl {
    CTL_ETH_CONTROL  = 0x0,
    CTL_DATA         = 0x1,
    CTL_ETH_DR_EMADS = 0x2,
    CTL_IB_CONTROL   = 0x3
};

#endif /* SX_DEVICE_H */
