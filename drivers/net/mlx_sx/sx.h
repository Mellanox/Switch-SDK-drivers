/*
 * Copyright (C) 2010-2022 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#ifndef SX_H
#define SX_H


/************************************************
 * Includes
 ***********************************************/
#include <asm/atomic.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/skbuff.h>
#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/sx_i2c_if.h>
#include <linux/timer.h>
#include "eq.h"
#include "fw.h"
#include "icm.h"
#include "sx_dpt.h"
#include "map.h"
#include "counter.h"
#include "internal_log.h"
#include <linux/interrupt.h>
#include <linux/version.h>
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0)) || defined(CONFIG_SX_RHEL_7_4) || defined(CONFIG_SX_RHEL_7_6)
#include <linux/timecounter.h>
#endif
#include <linux/clocksource.h>
#include <linux/net_tstamp.h>
#include <linux/ptp_clock_kernel.h>
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
#include <linux/bpf.h>
#endif

/************************************************
 *  Defines
 ***********************************************/
#ifdef PD_BU
#define INCREASED_TIMEOUT
#endif

#define DRV_NAME    "sx_core"
#define PFX         DRV_NAME ": "
#define DRV_RELDATE "May, 2011"

#define PCI_DRIVER_F_SX_DRIVER     (1 << 0) /* PCI driver initialized successfully */
#define PCI_DRIVER_F_SX_OOB_DRIVER (1 << 1) /* OOB PCI driver initialized successfully */

#define SX_MAX_DEVICES 2

/* SwitchX PCI device ID */
#define SWITCHX_PCI_DEV_ID 0xc738
/* SwitchX in flash recovery mode */
#define SWITCHX_FLASH_MODE_PCI_DEV_ID 0x0246

/* Spectrum PCI device ID */
#define SPECTRUM_PCI_DEV_ID 0xcb84
/* Spectrum in flash recovery mode */
#define SPECTRUM_FLASH_MODE_PCI_DEV_ID 0x0249

/* Spectrum2 PCI device ID */
#define SPECTRUM2_PCI_DEV_ID 0xcf6c
/* Spectrum2 in flash recovery mode */
#define SPECTRUM2_FLASH_MODE_PCI_DEV_ID 0x024f

/* Spectrum3 PCI device ID */
#define SPECTRUM3_PCI_DEV_ID 0xcf70
/* Spectrum3 in flash recovery mode */
#define SPECTRUM3_FLASH_MODE_PCI_DEV_ID 0x0250

/* Spectrum4 PCI device ID */
#define SPECTRUM4_PCI_DEV_ID 0xcf80
/* Spectrum4 in flash recovery mode */
#define SPECTRUM4_FLASH_MODE_PCI_DEV_ID 0x0254

/* SwitchIB PCI device ID */
#define SWITCH_IB_PCI_DEV_ID 0xcb20
/* SwitchIB in flash recovery mode */
#define SWITCH_IB_FLASH_MODE_PCI_DEV_ID 0x0247

/* SwitchIB2 PCI device ID */
#define SWITCH_IB2_PCI_DEV_ID 0xcf08

/* SwitchIB2 in flash recovery mode */
#define SWITCH_IB2_FLASH_MODE_PCI_DEV_ID 0x024B

/* Quantum PCI device ID */
#define QUANTUM_PCI_DEV_ID 0xd2f0

/* Quantum in flash recovery mode */
#define QUANTUM_FLASH_MODE_PCI_DEV_ID 0x024D

/* Quantum2 PCI device ID */
#define QUANTUM2_PCI_DEV_ID 0xd2f2

/* Quantum2 in flash recovery mode */
#define QUANTUM2_FLASH_MODE_PCI_DEV_ID 0x257

#define TO_FIELD(mask, shift, value) \
    (value & mask) << shift;

#undef CONFIG_SX_DEBUG
/*#define CONFIG_SX_DEBUG*/

#ifdef CONFIG_SX_DEBUG
extern int sx_debug_level;
#define sx_dbg(mdev, format, arg ...)                                                       \
    do {                                                                                    \
        if (sx_debug_level) {                                                               \
            dev_printk(KERN_DEBUG,                                                          \
                       &(mdev)->pdev->dev, "%s.%d: " format, __func__, __LINE__, ## arg); } \
    } while (0)

#else /* CONFIG_SX_DEBUG */

#define sx_dbg(mdev, format, arg ...) do { (void)mdev; } while (0)

#endif /* CONFIG_SX_DEBUG */

#define sx_err(mdev, format, arg ...)              \
    if (mdev->pdev) {                              \
        dev_err(&mdev->pdev->dev, format, ## arg); \
    } else {                                       \
        printk(KERN_ERR PFX format, ## arg);       \
    }
#define sx_warn(mdev, format, arg ...)              \
    if (mdev->pdev) {                               \
        dev_warn(&mdev->pdev->dev, format, ## arg); \
    } else {                                        \
        printk(KERN_WARNING PFX format, ## arg);    \
    }
#define sx_info(mdev, format, arg ...)              \
    if (mdev->pdev) {                               \
        dev_info(&mdev->pdev->dev, format, ## arg); \
    } else {                                        \
        printk(KERN_INFO PFX format, ## arg);       \
    }

#define SX_WRITE_LIMIT       2000
#define SX_TRUNCATE_SIZE_MIN 4
#define LAG_ID_INVALID       (MAX_LAG_NUM)

#define MAX_SLOT_NUM            16
#define MAX_MODULE_NUM          65
#define MAX_LANE_NUM_PER_MODULE 8

#ifdef SX_DEBUG

#define SX_CORE_HEXDUMP16(ptr, len)                   \
    do {                                              \
        unsigned char *data = (ptr);                  \
        int            i;                             \
        for (i = 0; i < len; i++) {                   \
            if ((i % 16) == 0) {                      \
                printk(KERN_DEBUG "\n0x%04x: ", i); } \
            if ((i % 8) == 0) {                       \
                printk(KERN_DEBUG " "); }             \
            printk(KERN_DEBUG "0x%02x ", data[i]);    \
        }                                             \
        printk(KERN_DEBUG "\n");                      \
    } while (0)

#endif

#define SX_CORE_UNUSED_PARAM(P)
#define MAX_SYSTEM_PORTS_IN_FILTER 256
#define MAX_LAG_PORTS_IN_FILTER    256
#define FROM_BITS_TO_U64(bits) \
    (((bits) %                 \
      64) ? ((bits) / 64) + 1 : ((bits) / 64))

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
#define SX_AGG_EBPF_PROG_NUM_PER_RDQ 7
#endif

/************************************************
 *  Enums
 ***********************************************/
enum {
    SX_FLAG_MSI_X = 1
};

enum TX_BASE_HEADER_DEFS {
    TX_HDR_VER_MASK_V1           = 0xF,
    TX_HDR_VER_SHIFT_V1          = 4,
    TX_HDR_CTL_MASK              = 0x3,
    TX_HDR_CTL_SHIFT             = 2,
    TX_HDR_MC_MASK               = 0x1,
    TX_HDR_MC_SHIFT              = 0,
    TX_HDR_PROTOCOL_MASK         = 0x7,
    TX_HDR_PROTOCOL_SHIFT        = 5,
    TX_HDR_ETCLASS_MASK          = 0x7,
    TX_HDR_ETCLASS_SHIFT         = 2,
    TX_HDR_SWID_MASK             = 0x7,
    TX_HDR_SWID_SHIFT            = 12,
    TX_HDR_SYSTEM_PORT_MID_MASK  = 0xFFFF,
    TX_HDR_SYSTEM_PORT_MID_SHIFT = 0,
    TX_HDR_CTCLASS3_MASK         = 0x1,
    TX_HDR_CTCLASS3_SHIFT        = 14,
    TX_HDR_RDQ_MASK              = 0x1F,
    TX_HDR_RDQ_SHIFT             = 9,
    TX_HDR_CPU_SIGNATURE_MASK    = 0x1FF,
    TX_HDR_CPU_SIGNATURE_SHIFT   = 0,
    TX_HDR_SIGNATURE_MASK        = 0xFFFF,
    TX_HDR_SIGNATURE_SHIFT       = 0,
    TX_HDR_STCLASS_MASK          = 0x7,
    TX_HDR_STCLASS_SHIFT         = 13,
    TX_HDR_EMAD_MASK             = 0x1,
    TX_HDR_EMAD_SHIFT            = 5,
    TX_HDR_TYPE_MASK             = 0xF,
    TX_HDR_TYPE_SHIFT            = 0,
    TX_HDR_RX_IS_ROUTER_MASK_V1  = 0x1,
    TX_HDR_RX_IS_ROUTER_SHIFT_V1 = 3,
    TX_HDR_RX_IS_TUNNEL_MASK_V1  = 0x1,
    TX_HDR_RX_IS_TUNNEL_SHIFT_V1 = 2,
    TX_HDR_FID_VALID_MASK_V1     = 0x1,
    TX_HDR_FID_VALID_SHIFT_V1    = 0,
    TX_HDR_CONTROL_MASK_V1       = 0x1,
    TX_HDR_CONTROL_SHIFT_V1      = 6,
    TX_HDR_ETCLASS_MASK_V1       = 0xF,
    TX_HDR_ETCLASS_SHIFT_V1      = 0,
    TX_HDR_FID_MASK_V1           = 0xFFFF,
    TX_HDR_FID_SHIFT_V1          = 0
};
enum tele_dir_ing {
    TELE_DIR_ING_EGRESS_E  = 0,
    TELE_DIR_ING_INGRESS_E = 1,
    TELE_DIR_ING_MAX_E     = 1,
    TELE_DIR_ING_NUM_E     = 2,
};
/************************************************
 *  Structs
 ***********************************************/
struct event_data {
    struct list_head       list;
    struct sk_buff        *skb;
    u16                    system_port;
    u16                    trap_id;
    u8                     dev_id;
    u8                     is_lag;
    u16                    lag_sub_port;
    u8                     swid;
    struct sx_dev         *dev;
    u32                    original_packet_size;
    struct sx_rx_timestamp rx_timestamp;
    u32                    user_def_val;
    u16                    dest_sysport;
    u8                     dest_is_lag;
    u16                    dest_lag_subport;
    u8                     mirror_reason;
    u8                     mirror_tclass;
    u16                    mirror_cong;
    u32                    mirror_lantency;
    u8                     mirror_elephant;
    u8                     channel_experienced_drop;
};
struct sx_rsc { /* sx  resource */
    struct event_data evlist;           /* event list           */
    int               evlist_size;      /* the current size     */
    spinlock_t        lock;         /* event list lock	*/
    wait_queue_head_t poll_wait;
    atomic_t          multi_packet_read_enable;
    atomic_t          read_blocking_state;
    struct semaphore  write_sem;
    struct sx_dq     *bound_monitor_rdq;
    struct file     * owner;
    int               queue_type;
    int               channel_experienced_drop;
    atomic_t          refcnt;
};
struct tx_base_header_v0 {
    u8  ctl_mc;
    u8  protocol_etclass;
    u16 swid;
    u16 system_port_mid;
    u16 ctclass3_rdq_cpu_signature;
    u32 reserved;
    u16 signature;
    u16 stclass_emad_type;
};
struct tx_base_header_v1 {
    u8  version_ctl;
    u8  protocol_rx_is_router_rx_is_tunnel_fid_valid;
    u16 swid_control_etclass;
    u16 system_port_mid;
    u16 reserved1;
    u16 fid;
    u16 reserved2;
    u8  reserved3[3];
    u8  type;
};
struct sx_bitmap {
    u32           max;
    spinlock_t    lock;   /* bitmap lock */
    unsigned long table[4];
};
struct sx_buf_list {
    void      *buf;
    dma_addr_t map;
};
struct sx_buf {
    struct {
        struct sx_buf_list  direct;
        struct sx_buf_list *page_list;
    } u;
    int nbufs;
    int npages;
    int page_shift;
};


/************************************************
 * EQ - Structs
 ***********************************************/
struct sx_eq {
    struct sx_dev      *dev;
    void __iomem       *ci_db;
    void __iomem       *arm_db;
    int                 eqn;
    u32                 cons_index;
    u16                 irq;
    u16                 have_irq;
    int                 nent;
    struct sx_buf_list *page_list;
};
struct sx_eq_table {
    struct sx_bitmap bitmap;
    void __iomem    *clr_int;
    u32              clr_mask;
    struct sx_eq     eq[SX_NUM_EQ];
    int              have_irq;
    u8               inta_pin;
};

/************************************************
 * CQ - Structs
 ***********************************************/
union sx_cqe;
struct sx_cq_bkp_poll {
    atomic_t curr_num_cq_polls;
    int      last_interval_num_cq_polls;
    int      last_interval_cons_index;
    atomic_t cq_bkp_poll_mode;
};
struct sx_cqe_params {
    u16                    trap_id;
    u8                     is_err;
    u8                     is_send;
    u8                     dqn;
    u16                    wqe_counter;
    u16                    byte_count;
    u32                    user_def_val_orig_pkt_len;
    u8                     is_lag;
    u16                    lag_subport;
    u16                    sysport_lag_id;
    u8                     mirror_reason;
    u16                    dest_sysport_lag_id;
    u8                     dest_is_lag;
    u16                    dest_lag_subport;
    u8                     mirror_tclass;
    u16                    mirror_cong;
    u32                    mirror_lantency;
    u8                     mirror_elephant;
    struct sx_rx_timestamp cqe_ts;
};
struct sx_cq {
    u32                   cons_index;
    u64                   cons_index_dbg;
    u64                   cons_index_dbg_snapshot;
    __be32               *set_ci_db;
    __be32               *arm_db;
    int                   cqn;
    atomic_t              refcount;
    struct completion     free;
    spinlock_t            lock; /* sx_cq lock */
    spinlock_t            rearm_lock; /* cq rearm lock */
    struct sx_buf         buf;
    int                   nent;
    struct sx_dev        *sx_dev;
    struct sx_cq_bkp_poll bkp_poll_data;
    u8                    cqe_version;
    size_t                cqe_sizeof;
    void                  (*sx_next_cqe_cb)(struct sx_cq *cq, union sx_cqe *cqe_p);
    void                  (*sx_fill_poll_one_params_from_cqe_cb)(union sx_cqe         *u_cqe,
                                                                 struct sx_cqe_params *cqe_params);
    u8                      (*sx_get_cqe_owner_cb)(struct sx_cq *cq, int n);
    void                    (*sx_cqe_owner_init_cb)(struct sx_cq *cq);
    struct sx_rx_timestamp* cqe_ts_arr;
    int                     dbg_cq_on_hold; /* if set, CQ handling will be stopped */
};
struct cpu_traffic_priority {
    struct sx_bitmap    high_prio_cq_bitmap;     /* CPU high priority CQs */
    struct sx_bitmap    active_high_prio_cq_bitmap; /* high priority CQs that hold CQEs to handle */
    struct sx_bitmap    active_low_prio_cq_bitmap; /* low priority CQs that hold CQEs to handle */
    atomic_t            high_prio_cq_in_load;    /* is high prio traffic in heave CPU load? */
    struct task_struct *low_prio_cq_thread;      /* low priority CQs handling thread */
    struct task_struct *monitor_cq_thread;      /* low priority CQs handling thread */
    struct semaphore    low_prio_cq_thread_sem;  /* semaphore to signal the low priority CQs handling thread */
    struct semaphore    monitor_cq_thread_sem;  /* semaphore to signal the low priority CQs handling thread */
    struct semaphore    low_prio_cq_thread_started_sem;  /* semaphore to signal that low priority CQs handling thread started */
    struct semaphore    monitor_cq_thread_started_sem;  /* semaphore to signal that monitor CQs handling thread started */
    u8                  low_prio_cq_thread_alive;
    u8                  monitor_cq_thread_alive;
    struct timer_list   sampling_timer;
};
struct sx_cq_table {
    struct sx_bitmap bitmap;
    struct sx_bitmap ts_bitmap;               /* time stamp enabled/disabled */
    struct sx_bitmap ts_hw_utc_bitmap;               /* hw utc time stamp enabled / disabled */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    struct timespec64 *timestamps;
#else
    struct timespec *timestamps;
#endif
    struct cpu_traffic_priority cpu_traffic_prio;
    spinlock_t                  lock;     /* cq_table lock */
    struct sx_cq              **cq;
};

/************************************************
 * DQ - Structs
 ***********************************************/
struct sx_sge_data {
    int        len;
    void      *vaddr;
    dma_addr_t dma_addr;
};
struct sx_sge_internal {
    struct sx_sge_data hdr_pld_sg;
    struct sx_sge_data pld_sg_1;
    struct sx_sge_data pld_sg_2;
    struct sk_buff    *skb;
};
struct sx_wqe {
    __be16 flags;
    __be16 byte_count[3];
    __be64 dma_addr[3];
};
struct sx_pkt {
    struct sk_buff  *skb;
    struct list_head list_send_to_sdq;
    u8               set_lp;
    enum ku_pkt_type type;
    struct list_head list_wait_for_completion;
    unsigned long    since;
    u16              idx;
    bool             completion_delay_reported;
};
enum dq_state {
    DQ_STATE_FREE,
    DQ_STATE_RESET,
    DQ_STATE_RTS,
    DQ_STATE_ERROR,
};
struct sx_dq {
    void                    (*event)(struct sx_dq *, enum sx_event);
    struct sx_dev          *dev;
    int                     dqn;
    int                     is_send;
    struct sx_buf           buf;
    spinlock_t              lock; /* sx_dq lock */
    u16                     head;
    u16                     tail; /* same type as wqe_counter in cqe */
    int                     wqe_cnt;
    int                     wqe_shift;
    struct sx_cq           *cq;  /* the matching cq */
    struct sx_sge_internal *sge;
    wait_queue_head_t       tx_full_wait; /* Not sure we need it */
    __be32                 *db;
    int                     is_flushing;
    struct sx_pkt           pkts_list; /* Send only */
    struct sx_pkt           pkts_comp_list; /* Send only */
    uint64_t                pkts_sent_to_sdq; /* Send only */
    uint64_t                pkts_recv_completion; /* Send only */
    uint64_t                pkts_no_recv_completion; /* Send only */
    uint64_t                pkts_late_completion; /* Send only */
    uint64_t                pkts_sw_queue_drops; /* Send only */
    uint32_t                pkts_in_sw_queue; /* Send only */
    uint64_t                max_comp_time; /* Send only */
    unsigned long           max_comp_ts; /* Send only */
    enum dq_state           state;
    atomic_t                refcount;
    struct completion       free;
    unsigned long           last_completion; /* time stamp that marks when last completion received */
    unsigned long           last_full_queue; /* time stamp that marks when was last time the queue was full */
    int                     is_monitor;      /* rdq is cyclic monitor rdq. non valid for sdq */
    int                     is_monitor_stopped;
    uint32_t                mon_rx_count;
    uint32_t                mon_rx_start;
    uint32_t                mon_rx_start_total; /* start point to calculate total number of discarded packets per RDQ */
    struct sx_rsc         * file_priv_p;
    uint8_t                 cpu_tclass;

    /* SW queue used for storing discarded packets which may be consumed by NOS,
     * since current HW doesn't allow to store such packet in multiple RDQs. */
    struct event_data *sw_dup_evlist_p;
    uint32_t           sw_dup_evlist_cnt;            /* number of discarded packets in the SW cyclic buffer */
    uint32_t           sw_dup_evlist_total_cnt;      /* total number of discarded packets per SW cyclic buffer (could be greater than size of the cyclic buffer) */
};
struct sx_dq_table {
    struct sx_bitmap bitmap;
    spinlock_t       lock;    /* dq_table lock */
    struct sx_dq   **dq;
};
struct sx_cmd {
    struct pci_pool       *pool;
    void __iomem          *hcr;
    struct mutex           hcr_mutex;  /* the HCR's mutex */
    struct semaphore       pci_poll_sem;
    struct semaphore       i2c_poll_sem;
    struct semaphore       event_sem;
    int                    max_cmds;
    spinlock_t             context_lock;  /* the context lock */
    int                    free_head;
    struct sx_cmd_context *context;
    u16                    token_mask;
    u8                     use_events;
    u8                     toggle;
};
struct sx_fw {
    u64            clr_int_base;
    u64            catas_offset;
    u32            catas_size;
    u8             clr_int_bar;
    u8             catas_bar;
    u8             debug_trace;
    u8             smkey;
    u64            fw_ver;
    u64            doorbell_page_offset;
    u8             doorbell_page_bar;
    u64            frc_offset;
    u8             frc_bar;
    u64            utc_sec_offset;
    u8             utc_sec_bar;
    u64            utc_nsec_offset;
    u8             utc_nsec_bar;
    u64            cr_dump_offset;
    u8             cr_dump_bar;
    u16            core_clock;
    struct sx_icm *fw_icm;
    struct sx_icm *pp_icm;
    u16            fw_pages;
    u8             fw_hour;
    u8             fw_minutes;
    u8             fw_seconds;
    u16            fw_year;
    u8             fw_month;
    u8             fw_day;
    u32            local_out_mb_offset;
    u32            local_out_mb_size;
    u32            local_in_mb_offset;
    u32            local_in_mb_size;
    u32            cap_dump_host_size_flat;
    u32            cap_dump_host_size_gw;
    u32            cap_dump_host_size_gdb;
};
union sx_cmd_ifc_registers {
    struct ku_access_pspa_reg  pspa_reg_data;
    struct ku_access_qsptc_reg qsptc_reg_data;
    struct ku_access_qstct_reg qstct_reg_data;
    struct ku_access_ptys_reg  ptys_reg_data;
    struct ku_access_pmlp_reg  pmlp_reg_data;
    struct ku_access_plib_reg  plib_reg_data;
    struct ku_access_spzr_reg  spzr_reg_data;
    struct ku_access_paos_reg  paos_reg_data;
    struct ku_access_pmpc_reg  pmpc_reg_data;
    struct ku_access_pmpr_reg  pmpr_reg_data;
    struct ku_access_pmtu_reg  pmtu_reg_data;
    struct ku_access_pelc_reg  pelc_reg_data;
    struct ku_access_htgt_reg  htgt_reg_data;
    struct ku_access_mfsc_reg  mfsc_reg_data;
    struct ku_access_mfsm_reg  mfsm_reg_data;
    struct ku_access_mfsl_reg  mfsl_reg_data;
    struct ku_access_pvlc_reg  pvlc_reg_data;
    struct ku_access_mcia_reg  mcia_reg_data;
    struct ku_access_hpkt_reg  hpkt_reg_data;
    struct ku_access_hcap_reg  hcap_reg_data;
    struct ku_access_hdrt_reg  hdrt_reg_data;
    struct ku_access_qprt_reg  qprt_reg_data;
    struct ku_access_mfcr_reg  mfcr_reg_data;
    struct ku_access_fore_reg  fore_reg_data;
    struct ku_access_mtcap_reg mtcap_reg_data;
    struct ku_access_mtbr_reg  mtbr_reg_data;
    struct ku_access_mtwe_reg  mtwe_reg_data;
    struct ku_access_mmdio_reg mmdio_reg_data;
    struct ku_access_mmia_reg  mmia_reg_data;
    struct ku_access_mfpa_reg  mfpa_reg_data;
    struct ku_access_mfbe_reg  mfbe_reg_data;
    struct ku_access_mfba_reg  mfba_reg_data;
    struct ku_access_mjtag_reg mjtag_reg_data;
    struct ku_access_pmaos_reg pmaos_reg_data;
    struct ku_access_mfm_reg   mfm_reg_data;
    struct ku_access_spad_reg  spad_reg_data;
    struct ku_access_sspr_reg  sspr_reg_data;
    struct ku_access_ppad_reg  ppad_reg_data;
    struct ku_access_spmcr_reg spmcr_reg_data;
    struct ku_access_pbmc_reg  pbmc_reg_data;
    struct ku_access_pptb_reg  pptb_reg_data;
    struct ku_access_smid_reg  smid_reg_data;
    struct ku_access_spvid_reg spvid_reg_data;
    struct ku_access_mgir_reg  mgir_reg_data;
    struct ku_access_plbf_reg  plbf_reg_data;
    struct ku_access_mhsr_reg  mhsr_reg_data;
    struct ku_access_mpsc_reg  mpsc_reg_data;
};
/************************************************
 * Private data struct
 ***********************************************/
union swid_data {
    struct {
        int synd;
        u64 mac;
    } eth_swid_data;
    struct {
    } ib_swid_data;
};

struct sx_priv;
struct sx_ptp_packet_metadata;
/* Note - all these callbacks are called when the db_lock spinlock is locked! */
struct dev_specific_cb {
    int (*get_hw_etclass_cb)(struct isx_meta *meta, u8* hw_etclass);
    int (*sx_build_isx_header_cb)(struct isx_meta *meta, struct sk_buff *skb, u8 stclass,  u8 hw_etclass);
    u8  (*max_cpu_etclass_for_unlimited_mtu)(void);
    int (*sx_get_sdq_cb)(struct sx_dev *dev, enum ku_pkt_type type,
                         u8 swid, u8 etclass, u8 *stclass, u8 *sdq);
    int (*sx_get_sdq_num_cb)(struct sx_dev *dev, u8 swid, u8 etclass, u8 *sdq);
    int (*get_send_to_port_as_data_supported_cb)(u8 *send_to_port_as_data_supported);
    int (*get_rp_vid_cb)(struct sx_dev *dev, struct completion_info *comp_info, u16 *vid);
    int (*get_swid_cb)(struct sx_dev *dev, struct completion_info *comp_info, u8 *swid);
    int (*get_lag_mid_cb)(struct sx_dev *dev, u16 lag_id, u16 *mid);
    int (*get_ib_system_port_mid)(struct sx_dev *dev, u16 ib_port, u16* sys_port_mid);
    int (*sx_ptp_dev_init)(struct sx_priv *priv, ptp_mode_t ptp_mode);
    int (*sx_ptp_dev_cleanup)(struct sx_priv *priv);
    int (*sx_ptp_dump)(struct sx_priv *priv, struct seq_file *m, void *v, void *context);
    int (*sx_ptp_rx_handler)(struct sx_priv                      *priv,
                             struct completion_info              *ci,
                             ptp_mode_t                           ptp_mode,
                             const struct sx_ptp_packet_metadata *pkt_meta);
    int (*sx_ptp_tx_handler)(struct sx_priv                      *priv,
                             struct sk_buff                      *skb,
                             const struct sx_ptp_packet_metadata *pkt_meta);
    int (*sx_ptp_tx_ts_handler)(struct sx_priv *priv,
                                struct sk_buff *skb,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                                const struct timespec64 *tx_ts);
#else
                                const struct timespec *tx_ts);
#endif
    int (*sx_ptp_get_supported_tx_types)(struct sx_priv *priv, u32 *tx_types);
    int (*sx_ptp_set_tx_type)(struct sx_priv *priv, int tx_type);
    int (*sx_ptp_tx_control_to_data)(struct sx_priv  *priv,
                                     struct sk_buff **orig_skb,
                                     struct isx_meta *meta,
                                     u16              port,
                                     u8               is_lag,
                                     u8              *is_tagged);
    void (*sx_set_device_profile_update_cb)(struct ku_profile* profile, struct profile_driver_params *driver_params);
    void (*sx_init_cq_db_cb)(struct sx_cq *cq, u8 cqn, u8 *cqe_ver);
    void (*sx_printk_cqe_cb)(union sx_cqe *u_cqe);
    u8   (*is_sw_rate_limiter_supported)(void);
    void (*sx_fill_ci_from_cqe_cb)(struct completion_info *ci, union sx_cqe *u_cqe);
    void (*sx_fill_params_from_cqe_cb)(union sx_cqe *u_cqe, u16 *hw_synd_p, u8  *is_isx_p,
                                       u16 *byte_count_p, u8 *dqn_p, u8 *crc_present_p);
    void (*sx_disconnect_all_trap_groups_cb)(struct sx_dev *dev);
    int  (*sx_get_phy_port_max_cb)(uint16_t *port);
    int  (*sx_get_lag_max_cb)(uint16_t *max_lag_p, uint16_t *max_port_lags_p);
    void (*sx_get_rdq_max_cb)(uint8_t *max_rdqs, uint16_t *max_entry_size);
    int  (*is_eqn_cmd_ifc_only_cb)(int eqn, u8 *is_cmd_ifc_only);
    int  (*sx_clock_dev_init)(struct sx_priv *priv);
    int  (*sx_clock_dev_cleanup)(struct sx_priv *priv);
    int  (*sx_clock_cqe_ts_to_utc)(struct sx_priv *priv,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                                   const struct timespec64 *cqe_ts,
                                   struct timespec64       *utc);
#else
                                   const struct timespec *cqe_ts,
                                   struct timespec       *utc);
#endif

    int  (*sx_clock_dump)(struct sx_priv *priv, struct seq_file *m, void *v, void *context);
    u16  (*cap_max_mtu_get_cb)(void);
    int  (*synce_init_cb)(void);
    void (*synce_deinit_cb)(void);
};

struct rif_info {
    u16 local_port;
    u16 vlan_id;
    u8  is_lag;
    u16 lag_id;
    u8  is_valid;
};

enum ptp_spc1_counters {
    PTP_COUNTER_SPC1_FIFO_TRAP,
    PTP_COUNTER_SPC1_GC_EVENTS,
    PTP_COUNTER_SPC1_GC_RECORDS,
    PTP_COUNTER_SPC1_FIFO_OVERFLOW,
    PTP_COUNTER_SPC1_OUT_OF_MEMORY,
    PTP_COUNTER_SPC1_PENDING_EVENTS,
    PTP_COUNTER_SPC1_PENDING_RECORDS,
    PTP_COUNTER_SPC1_EVENT_ARRIVED_FIRST,
    PTP_COUNTER_SPC1_RECORD_ARRIVED_FIRST,
    PTP_COUNTER_SPC1_EMPTY_TS,
    PTP_COUNTER_SPC1_REG_ACCESS_SUCCEEDED,
    PTP_COUNTER_SPC1_REG_ACCESS_FAILED,
    PTP_COUNTER_SPC1_LAST
};
struct ptp_record {
    struct list_head     list;
    unsigned long        since;
    struct mtpptr_record mtpptr;
};
struct sx_ptp_packet_fields {
    u16 seqid;
    u8  domain;
    u8  msg_type;
};
struct sx_ptp_packet_metadata {
    u16                         sysport_lag_id;
    u8                          timestamp_required;
    struct sx_ptp_packet_fields pkt_fields;
};
struct ptp_common_event_data {
    struct list_head            list;
    u8                          need_timestamp;
    unsigned long               since;
    struct sx_ptp_packet_fields pkt_fields;
};
struct ptp_rx_event_data {
    struct ptp_common_event_data common;
    struct completion_info      *ci;
};
struct ptp_tx_event_data {
    struct ptp_common_event_data common;
    struct sk_buff              *skb;
};

typedef void (*ptp_db_handle_cb_t)(struct sx_priv *priv, struct ptp_common_event_data *ced, u64 frc);
typedef void (*ptp_db_gc_cb_t)(struct ptp_common_event_data *ced);

#define PTP_MAX_PORTS   (MAX_PHYPORT_NUM + MAX_LAG_NUM)
#define PTP_MAX_RECORDS (4)

struct ptp_db {
    struct list_head   sysport_events_list[PTP_MAX_PORTS];
    struct list_head   sysport_records_list[PTP_MAX_PORTS];
    spinlock_t         sysport_lock[PTP_MAX_PORTS];
    u8                 direction;
    ptp_db_handle_cb_t handle_cb;
    ptp_db_gc_cb_t     gc_cb;
};

enum ptp_spc2_counters {
    PTP_COUNTER_SPC2_TIMESTAMP_ARRIVED,
    PTP_COUNTER_SPC2_ONE_STEP_TIMESTAMP_ARRIVED,
    PTP_COUNTER_SPC2_EMPTY_TIMESTAMP,
    PTP_COUNTER_SPC2_NO_TIMESTAMP,
    PTP_COUNTER_SPC2_TX_WA,
    PTP_COUNTER_SPC2_LAST
};

enum ptp_common_counters {
    PTP_COUNTER_COMMON_TOTAL,
    PTP_COUNTER_COMMON_NEED_TIMESTAMP,
    PTP_COUNTER_COMMON_RATE_LIMIT,
    PTP_COUNTER_COMMON_LAST
};
enum ptp_trap_counters {
    PTP_COUNTER_TRAP_PTP0,
    PTP_COUNTER_TRAP_PTP1,
    PTP_COUNTER_TRAP_OTHER,
    PTP_COUNTER_TRAP_PTP0_ERROR,
    PTP_COUNTER_TRAP_PTP1_ERROR,
    PTP_COUNTER_TRAP_LAST
};

#define PTP_PPS_MAX_PIN_NUM 8
typedef enum pps_pin_cap_mode {
    PPS_PIN_CAP_MODE_SUPPORT_PPS_IN_E      = 0x1,
    PPS_PIN_CAP_MODE_SUPPORT_PPS_OUT_E     = 0x2,
    PPS_PIN_CAP_MODE_SUPPORT_VIRTUAL_PIN_E = 0x4
} pps_pin_cap_mode_t;
struct ptp_pps {
    pps_pin_cap_mode_t pin_caps[PTP_PPS_MAX_PIN_NUM];
    bool               enabled;
};

struct ber_monitor_info {
    struct sx_dev *dev;
    u8             port_ber_monitor_bitmask[MAX_PHYPORT_NUM + 1];
    u8             port_ber_monitor_state[MAX_PHYPORT_NUM + 1];
};

struct sx_health_check_state {
    struct sx_bitmap sdq_bitmap;
    struct sx_bitmap rdq_bitmap;
    bool             cmd_ifc;
    bool             catas;
};

struct listener_register_filter_entry {
    int is_global_register;
    int is_global_filter;
    u64 ports_registers[FROM_BITS_TO_U64((MAX_PHYPORT_NUM + 1))];
    u64 vlans_registers[FROM_BITS_TO_U64((SXD_MAX_VLAN_NUM + 1))];
    u64 lags_registers[FROM_BITS_TO_U64((MAX_LAG_NUM + 1))];
    u64 ports_filters[FROM_BITS_TO_U64((MAX_PHYPORT_NUM + 1))];
    u64 vlans_filters[FROM_BITS_TO_U64((SXD_MAX_VLAN_NUM + 1))];
    u64 lags_filters[FROM_BITS_TO_U64((MAX_LAG_NUM + 1))];
};
struct listener_entry {
    u8                                    swid;
    enum l2_type                          listener_type;
    pid_t                                 pid;          /* process pid that registered the trap */
    char                                  pname[16];    /* process name that registered the trap */
    u8                                    is_default;   /* is a default listener  */
    union ku_filter_critireas             critireas;    /* more filter critireas  */
    cq_handler                            handler;      /* The completion handler */
    void                                 *context;      /* to pass to the handler */
    u64                                   rx_pkts;
    struct listener_register_filter_entry listener_register_filter;
    struct list_head                      list;
    struct list_head                      gc_list;
};

struct listeners_and_rf_info {
    struct list_head per_synd_list[NUM_HW_SYNDROMES + 1];
};

struct module_info {
    enum sx_module_power_mode_policy power_mode_policy;
    enum sx_module_power_mode        power_mode;
    uint16_t                         num_ports_up;
};

enum sx_kobject_type {
    SX_KOBJECT_ASIC      = 0,
    SX_KOBJECT_ASIC_TEMP = 1,
    SX_KOBJECT_MAX       = SX_KOBJECT_ASIC_TEMP,
};

struct sx_priv {
    struct sx_dev                dev;
    bool                         created_on_pci_probe;
    bool                         kobj_add_done;
    struct list_head             dev_list;
    struct list_head             ctx_list;
    spinlock_t                   ctx_lock; /* the ctx_list's lock */
    struct sx_cmd                cmd;
    struct sx_eq_table           eq_table;
    struct sx_cq_table           cq_table;
    struct sx_dq_table           sdq_table;
    struct sx_dq_table           rdq_table;
    struct sx_health_check_state debug_trigger_state;  /* debug triggers control this */
    struct sx_health_check_state operational_state;
    u64                          cmd_ifc_num_of_pck_received;
    struct sx_bitmap             swid_bitmap;
    struct sx_fw                 fw;
    int                          is_fw_initialized;
    int                          unregistered;
    void __iomem                *clr_base;
    union swid_data              swid_data[NUMBER_OF_SWIDS];
    struct ku_l2_tunnel_params   l2_tunnel_params;
    int                          pause_cqn;
    u8                           pause_cqn_completed;
    int                          force_iter_monitor_cq;
    int                          force_iter_low_prio_cq;
    int                          force_iter_high_prio_cq;
    struct completion            pause_cqn_completion;
    bool                         dev_specific_cb_init_done;
    bool                         dev_sw_rst_flow;
    unsigned long                flags;
    char                         board_id[SX_BOARD_ID_LEN];
    u16                          vsd_vendor_id;
    bool                         dev_stuck;
    unsigned long                dev_stuck_time;
    bool                         global_flushing;
    u64                          bar0_dbregs_offset;
    u8                           bar0_dbregs_bar;
    void __iomem                *db_base;

    struct {
        struct listeners_and_rf_info *info;
        spinlock_t                    lock;
    } listeners_and_rf_db;

    /* cr space address and size */
    void __iomem *cr_space_start;
    u32           cr_space_size;

    struct {
        spinlock_t            profile_lock;   /* the profile's lock */
        struct ku_profile     dev_profile;
        struct sx_pci_profile pci_profile;
        bool                  pci_profile_set;
        bool                  dev_profile_set;
        bool                  first_ib_swid;
    } profile;

    /* BER monitor */
    struct ber_monitor_info ber_monitor_info;

    /* HW clock and PTP */
    struct {
        struct ptp_clock      *clock;
        struct ptp_clock_info  clock_info;
        struct sx_core_map     clock_setters; /* database of processes that touched the clock */
        struct mutex           clock_setters_lock;
        u32                    clock_setters_num_entries;
        struct sx_internal_log log_settime;
        struct sx_internal_log log_adjtime;
        struct sx_internal_log log_adjfreq;
        struct sx_internal_log log_activity;
        union {
            struct {
                void __iomem       *frc_base;
                struct delayed_work overflow_dwork;
                unsigned long       overflow_period;
                struct cyclecounter cycles;     /* hardware abstraction for a clock */
                struct timecounter  clock;     /* layer above a %struct cyclecounter which counts nanoseconds */
                u32                 nominal_c_mult;     /* Hardware nominal mult */
                int                 freq_adj;     /* diff of frequency adjustment (relevant to SPC1 only) */
                bool                time_adj;     /* is there any time adjustment recently? (relevant to SPC1 only) */
                spinlock_t          clock_lock;       /* R/W lock */
                struct delayed_work set_hw_time_dwork;
            } spc1;
            struct {
                void __iomem  *utc_sec;
                void __iomem  *utc_nsec;
                struct ptp_pps pps_info;
            } spc2; /* and SPC3 */
        } hwd;
    } hw_clock;

    struct {
        ptp_mode_t             ptp_mode;
        struct delayed_work    per_sec_dwork;
        atomic64_t             rx_budget[PTP_MAX_PORTS];
        atomic64_t             tx_budget[PTP_MAX_PORTS];
        atomic64_t             common_counters[2][PTP_COUNTER_COMMON_LAST];
        atomic64_t             traps_counters[PTP_COUNTER_TRAP_LAST];
        int                    ptp_cqn;
        struct sx_internal_log log;  /* log of errors and major events */
        union {
            struct {
                atomic64_t          counters[2][PTP_COUNTER_SPC1_LAST];
                atomic64_t          records_dist[2][PTP_MAX_RECORDS + 1];
                u64                 max_diff[2];    /* max time diff between event and record */
                unsigned long       max_diff_ts[2];    /* max time difference timestamp */
                struct ptp_db       rx_db;
                struct ptp_db       tx_db;
                struct delayed_work gc_dwork;
            } spc1;
            struct {
                atomic64_t             counters[2][PTP_COUNTER_SPC2_LAST];
                struct sx_internal_log log_rx;
                struct sx_internal_log log_tx;
                struct sx_internal_log log_pps_events;
            } spc2; /* and SPC3 */
        } hwd;
    } ptp;

    /* XM support */
    struct {
        bool exists;
        u8   num_local_ports;
        u8   local_ports[SX_XM_MAX_LOCAL_PORTS_LEN];
    } xm;

    /* multi-dev support */
    struct {
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
        u64 eventlist_drops_counter;
        u64 unconsumed_packets_counter;
        u64 filtered_lag_packets_counter;
        u64 filtered_port_packets_counter;
        u64 loopback_packets_counter;
    } stats;

    struct sx_dev_cap dev_cap;

    /* IB only */
    u16 ib_to_local_db[MAX_IBPORT_NUM + 1];
    /* ETH only */
    u16                     system_to_local_db[MAX_SYSPORT_NUM];
    u16                     local_to_system_db[MAX_PHYPORT_NUM + 1];
    u16                     lag_member_to_local_db[MAX_LAG_NUM][MAX_LAG_MEMBERS_NUM];
    u8                      local_is_rp[MAX_PHYPORT_NUM + 1];
    u16                     local_rp_vid[MAX_PHYPORT_NUM + 1];
    u8                      lag_is_rp[MAX_LAG_NUM];
    u16                     lag_rp_vid[MAX_LAG_NUM];
    u16                     fid_to_hwfid[MAX_FIDS_NUM];
    u16                     rif_id_to_hwfid[MAX_RIFS_NUM];
    struct rif_info         rif_data[MAX_RIFS_NUM];
    u8                      local_to_slot_map[MAX_PHYPORT_NUM + 1];
    u8                      local_to_module_map[MAX_PHYPORT_NUM + 1];
    u16                     modules_to_port_map_count[MAX_SLOT_NUM][MAX_MODULE_NUM];
    u16                     module_to_ports_map[MAX_SLOT_NUM][MAX_MODULE_NUM][MAX_LANE_NUM_PER_MODULE];
    sxd_paos_admin_status_t local_port_state[MAX_PHYPORT_NUM + 1];
    struct module_info      module_data[MAX_SLOT_NUM][MAX_MODULE_NUM];
    struct mutex            module_access_mutex;
    struct kobject         *kobj[SX_KOBJECT_MAX + 1];

    /* common */
    long             cq_last_time_armed[NUMBER_OF_SDQS + NUMBER_OF_RDQS];
    long             cq_last_time_event[NUMBER_OF_SDQS + NUMBER_OF_RDQS];
    struct sx_bitmap cq_high_priority;
    u8               local_to_swid_db[MAX_PHYPORT_NUM + 1];
    spinlock_t       db_lock;            /* Lock for all DBs */
    u16              pvid_sysport_db[MAX_SYSPORT_NUM];
    u16              pvid_lag_db[MAX_LAG_NUM];
    u16              truncate_size_db[NUMBER_OF_RDQS];
    u16              sysport_filter_db[NUM_HW_SYNDROMES][MAX_SYSTEM_PORTS_IN_FILTER];
    u16              lag_filter_db[NUM_HW_SYNDROMES][MAX_LAG_PORTS_IN_FILTER];
    u8               lag_oper_state[MAX_LAG_NUM];
    u8               tele_thrs_state[MAX_PHYPORT_NUM + 1][TELE_DIR_ING_NUM_E];
    u64              tele_thrs_tc_vec[MAX_PHYPORT_NUM + 1][TELE_DIR_ING_NUM_E];
    /* RP helper dbs */
    u8                     port_prio2tc[MAX_PHYPORT_NUM + 1][MAX_PRIO_NUM + 1];
    u8                     lag_prio2tc[MAX_LAG_NUM + 1][MAX_PRIO_NUM + 1];
    u8                     port_vtag_mode[MAX_PHYPORT_NUM + 1][SXD_MAX_VLAN_NUM];
    u8                     lag_vtag_mode[MAX_LAG_NUM + 1][SXD_MAX_VLAN_NUM];
    u8                     port_rp_rif_valid[MAX_PHYPORT_NUM + 1][SXD_MAX_VLAN_NUM];
    u8                     lag_rp_rif_valid[MAX_LAG_NUM][SXD_MAX_VLAN_NUM];
    u16                    port_rp_rif[MAX_PHYPORT_NUM + 1][SXD_MAX_VLAN_NUM];
    u16                    lag_rp_rif[MAX_LAG_NUM][SXD_MAX_VLAN_NUM];
    u8                     port_prio_tagging_mode[MAX_PHYPORT_NUM + 1];
    u8                     lag_prio_tagging_mode[MAX_LAG_NUM + 1];
    u16                    port_vid_to_fid[MAX_PHYPORT_NUM + 1][SXD_MAX_VLAN_NUM];
    atomic_t               cq_backup_polling_refcnt;
    struct dev_specific_cb dev_specific_cb;
    atomic_t               dev_specific_cb_refcnt;
    wait_queue_head_t      dev_specific_cb_not_in_use;
    /* ECMP redirect IP override */
    u32                   icmp_vlan2ip_db[SXD_MAX_VLAN_NUM];
    struct tasklet_struct intr_tasklet;
    u32                   monitor_rdqs_arr[MAX_MONITOR_RDQ_NUM];
    u32                   monitor_rdqs_count;
    struct sx_bitmap      monitor_cq_bitmap;        /* WJH CQs */
    struct sx_bitmap      active_monitor_cq_bitmap; /* WJH CQs that hold CQEs to handle */
    u32                   warm_boot_mode;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 7, 0))
    struct bpf_prog* filter_ebpf_progs[NUMBER_OF_RDQS];
    struct bpf_prog* agg_ebpf_progs[NUMBER_OF_RDQS][SX_AGG_EBPF_PROG_NUM_PER_RDQ];
#endif
#ifdef SW_PUDE_EMULATION
    /* PUDE WA for NOS (PUDE events are handled by SDK). Needed for BU. */
    u8 admin_status_sysport_db[MAX_SYSPORT_NUM];
#endif /* SW_PUDE_EMULATION */
    void __iomem *cr_dump_base;
};

struct sx_globals {
    struct rw_semaphore      pci_restart_lock;
    u8                       pci_drivers_in_use; /* should be used under pci_restart_lock */
    struct sx_dev           *fake_dev;           /* running on OOB systems */
    struct sx_dev           *oob_backbone_dev;        /* SwitchX that interconnects all OOB devices */
    struct sx_dpt_s          sx_dpt;
    struct sx_i2c_ifc        sx_i2c;
    struct cdev              cdev;
    struct workqueue_struct *generic_wq;
};

extern struct sx_globals sx_glb;

struct isx_specific_data {
    u8  version;
    u8  ctl;
    u8  mc;
    u8  protocol;
    u8  ctclass;
    u16 cpu_signature;
    u16 signature;
    u8  emad;
    u8  type;
    u8  use_control_tclass;
    u8  rx_is_router;
    u8  fid_valid;
    u16 fid;
    u8  etclass;
    u8  rx_is_tunnel;
};

struct sx_timeval {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    struct timespec64 t;
#else
    struct timeval t;
#endif
    unsigned long j; /* jiffies */
};

struct sx_tm {
    struct tm tm;
    u32       msec;
};

/************************************************
 * Inline Functions
 ***********************************************/
static inline struct sx_priv * sx_priv(struct sx_dev *p_dev)
{
    return container_of(p_dev, struct sx_priv, dev);
}

void sx_core_file_add_ref(struct sx_rsc *file);
void sx_core_file_dec_ref(struct sx_rsc *file);

void inc_unconsumed_packets_global_counter(u16 hw_synd, enum sx_packet_type pkt_type);
void inc_filtered_lag_packets_global_counter(void);
void inc_filtered_port_packets_global_counter(void);
void inc_unconsumed_packets_counter(struct sx_priv *priv, u16 hw_synd, enum sx_packet_type pkt_type);
void inc_filtered_lag_packets_counter(struct sx_priv *priv);
void inc_filtered_port_packets_counter(struct sx_priv *priv);
int get_system_status(struct sx_dev *dev, u16 *system_status);
int sx_reset(struct sx_dev *dev, u8 perform_chip_reset);
int sx_core_register_device(struct sx_dev *dev);
void sx_core_unregister_device(struct sx_dev *dev);
int sx_cmd_init(struct sx_dev *dev);
int sx_cmd_init_pci(struct sx_dev *dev);
int sx_dbg_init(void);
void sx_dbg_deinit(void);
int sx_cmd_pool_create(struct sx_dev *dev);
void sx_cmd_pool_destroy(struct sx_dev *dev);
void sx_cmd_unmap(struct sx_dev *dev);
int sx_core_cr_dump_init(struct sx_priv *dev);
void sx_core_cr_dump_deinit(struct sx_priv *dev);
int sx_enable_swid(struct sx_dev *dev, int sx_dev_id, u8 swid, int synd, u64 mac);
void sx_disable_swid(struct sx_dev *dev, u8 swid);
int sx_change_configuration(struct sx_dev *dev);
int sx_handle_set_profile(struct sx_dev *dev);
int sx_build_isx_header(struct isx_meta *meta, struct sk_buff *skb, u8 stclass);
int sx_build_isx_header_v0(struct isx_meta *meta, struct sk_buff *skb, u8 stclass,  u8 hw_etclass);
int sx_build_isx_header_v1(struct isx_meta *meta, struct sk_buff *skb, u8 stclass,  u8 hw_etclass);
int sx_get_sdq(struct isx_meta *meta, struct sx_dev *dev, enum ku_pkt_type type, u8 swid,
               u8 etclass, u8 *stclass, u8 *sdq, u8 *max_cpu_etclass_for_unlimited_mtu, u16 *cap_max_mtu);
int sx_core_get_rdq_param_max(struct sx_dev *dev, uint8_t *rdq_num_max_p, uint16_t *rdq_max_entry_size_p);

/**
 * The following function is a wrapper for chip-specific
 * callbacks, which are used for getting relevant SDQ numbers
 * (IDs) which we want to create/delete.
 */
int sx_get_sqd_num(struct sx_dev *dev, u8 swid, u8 etclass, u8 *sdq);

int sx_get_sdq_per_traffic_type(struct sx_dev *dev, enum ku_pkt_type type, u8 swid, u8 etclass,
                                u8 *stclass, u8 *sdq);
int sx_core_dispatch_event(struct sx_dev *dev, enum sx_dev_event type,
                           union sx_event_data *event_data);

/**
 * The following function is used as a callback for devices
 * where we are getting SDQ number for creation based on the
 * specified egress TC.
 * Please note that the further SDQ handling will be based on
 * traffic type and handled by 'sx_get_sdq_cb'
 */
int sx_get_sdq_num_per_etclasss(struct sx_dev *dev, u8 swid, u8 etclass, u8 *sdq);

int disable_monitor_rdq(struct sx_dev *dev, int dqn);
void unset_monitor_rdq(struct sx_dq *dq);

/**
 * Used to send "SDK health" event (SXD_TRAP_ID_SDK_HEALTH_EVENT) to the registered users
 */
int sx_send_health_event(uint8_t dev_id, sxd_health_cause_t cause, sxd_health_severity_t severity);

bool sdk_health_get(uint8_t dev_id);
void sdk_health_set(uint8_t dev_id, bool is_enabled);
bool sdk_health_test_and_disable(uint8_t dev_id);

void sx_dbg_get_time(struct sx_timeval *sxtv);
void sx_dbg_jiffies_to_time(const struct sx_timeval *now,
                            unsigned long            jiffies_ts,
                            struct sx_tm            *sxtm);
void sx_dbg_jiffies_to_time_str(const struct sx_timeval *now,
                                unsigned long            jiffies_ts,
                                char                    *buff,
                                uint32_t                 bufflen);

#endif  /* SX_H */

/************************************************
 *                  EOF                         *
 ***********************************************/
