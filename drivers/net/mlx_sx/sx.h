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
#include "counter.h"
#include <linux/interrupt.h>
#include <linux/version.h>
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0) && (defined(RHEL_MAJOR) && defined(RHEL_MINOR) && RHEL_MAJOR == 7 && \
    (RHEL_MINOR == 2 || RHEL_MINOR == 3)))
    #include <linux/timecounter.h>
#endif
#include <linux/clocksource.h>
#include <linux/net_tstamp.h>
#include <linux/ptp_clock_kernel.h>


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

#define TO_FIELD(mask, shift, value) \
    (value & mask) << shift;

#define SX_MAX_PTP_RECORDS 4

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
#define SXD_LAG_ID_MAX       0x3FF
#define LAG_ID_INVALID       (SXD_LAG_ID_MAX + 1)

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

/************************************************
 *  Enums
 ***********************************************/
enum {
    SX_FLAG_MSI_X = 1
};

enum TX_BASE_HEADER_DEFS {
    TX_HDR_VER_MASK_V1 = 0xF,
    TX_HDR_VER_SHIFT_V1 = 4,
    TX_HDR_CTL_MASK = 0x3,
    TX_HDR_CTL_SHIFT = 2,
    TX_HDR_MC_MASK = 0x1,
    TX_HDR_MC_SHIFT = 0,
    TX_HDR_PROTOCOL_MASK = 0x7,
    TX_HDR_PROTOCOL_SHIFT = 5,
    TX_HDR_ETCLASS_MASK = 0x7,
    TX_HDR_ETCLASS_SHIFT = 2,
    TX_HDR_SWID_MASK = 0x7,
    TX_HDR_SWID_SHIFT = 12,
    TX_HDR_SYSTEM_PORT_MID_MASK = 0xFFFF,
    TX_HDR_SYSTEM_PORT_MID_SHIFT = 0,
    TX_HDR_CTCLASS3_MASK = 0x1,
    TX_HDR_CTCLASS3_SHIFT = 14,
    TX_HDR_RDQ_MASK = 0x1F,
    TX_HDR_RDQ_SHIFT = 9,
    TX_HDR_CPU_SIGNATURE_MASK = 0x1FF,
    TX_HDR_CPU_SIGNATURE_SHIFT = 0,
    TX_HDR_SIGNATURE_MASK = 0xFFFF,
    TX_HDR_SIGNATURE_SHIFT = 0,
    TX_HDR_STCLASS_MASK = 0x7,
    TX_HDR_STCLASS_SHIFT = 13,
    TX_HDR_EMAD_MASK = 0x1,
    TX_HDR_EMAD_SHIFT = 5,
    TX_HDR_TYPE_MASK = 0xF,
    TX_HDR_TYPE_SHIFT = 0,
    TX_HDR_RX_IS_ROUTER_MASK_V1 = 0x1,
    TX_HDR_RX_IS_ROUTER_SHIFT_V1 = 3,
    TX_HDR_FID_VALID_MASK_V1 = 0x1,
    TX_HDR_FID_VALID_SHIFT_V1 = 0,
    TX_HDR_CONTROL_MASK_V1 = 0x1,
    TX_HDR_CONTROL_SHIFT_V1 = 6,
    TX_HDR_ETCLASS_MASK_V1 = 0xF,
    TX_HDR_ETCLASS_SHIFT_V1 = 0,
    TX_HDR_FID_MASK_V1 = 0xFFFF,
    TX_HDR_FID_SHIFT_V1 = 0
};

enum {
    PTP_PACKET_INGRESS = 0,
    PTP_PACKET_EGRESS = 1
};
/************************************************
 *  Structs
 ***********************************************/
struct event_data {
    struct list_head list;
    struct sk_buff  *skb;
    u16              system_port;
    u16              trap_id;
    u8               dev_id;
    u8               is_lag;
    u8               lag_sub_port;
    u8               swid;
    struct sx_dev   *dev;
    u32              original_packet_size;
    u8               has_timestamp;
    struct timespec  timestamp;
    u32              user_def_val;
    u16              dest_sysport;
    u8               dest_is_lag;
    u8               dest_lag_subport;
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
    u8  protocol_rx_is_router_fid_valid;
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
struct sx_cq {
    u32                   cons_index;
    u32                   cons_index_snapshot;
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
    void                  (*sx_fill_poll_one_params_from_cqe_cb)(union sx_cqe *u_cqe, u16 *trap_id, u8 *is_err,
                                                                 u8 *is_send, u8 *dqn, u16 *wqe_counter,
                                                                 u16 *byte_count);
    u8               (*sx_get_cqe_owner_cb)(struct sx_cq *cq, int n);
    void             (*sx_cqe_owner_init_cb)(struct sx_cq *cq);
    struct timespec* cqe_ts_arr;
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
    struct timer_list   sampling_timer;
};
struct sx_cq_table {
    struct sx_bitmap            bitmap;
    struct sx_bitmap            ts_bitmap;    /* time stamp enabled/disabled */
    struct timespec            *timestamps;
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
    struct list_head list;
    u8               set_lp;
    enum ku_pkt_type type;
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
    struct sx_pkt           pkts_list;
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
struct sx_catas_err {
    u32 __iomem      *map;
    struct timer_list timer;
    struct list_head  list;
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
    u16            core_clock;
    struct sx_icm *fw_icm;
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
    struct ku_access_qcap_reg  qcap_reg_data;
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

/* Timestamp to implement SW correction mechanism to the HW clock */
struct sx_tstamp {
    struct cyclecounter   cycles;   /* hardware abstraction for a free running counter */
    struct timecounter    clock;   /* layer above a %struct cyclecounter which counts nanoseconds */
    u32                   nominal_c_mult;   /* Hardware nominal mult */
    int                   freq_adj;   /* diff of frequency adjustment */
    bool                  time_adj;   /* is there any time adjustment recently? */
    struct sx_dev        *dev;
    struct ptp_clock     *ptp;
    struct ptp_clock_info ptp_info;
    u8                    is_ptp_enable;
    spinlock_t            lock;     /* R/W lock */
    struct delayed_work   overflow_work;
    unsigned long         overflow_period;
};
struct ber_work_data {
    struct sx_dev      *dev;
    u8                  local_port;
    struct delayed_work dwork;
};
struct sx_priv;
/* Note - all these callbacks are called when the db_lock spinlock is locked! */
struct dev_specific_cb {
    int (*get_hw_etclass_cb)(struct isx_meta *meta, u8* hw_etclass);
    int (*sx_build_isx_header_cb)(struct isx_meta *meta, struct sk_buff *skb, u8 stclass,  u8 hw_etclass);
    u8  (*max_cpu_etclass_for_unlimited_mtu)(void);
    int (*sx_get_sdq_cb)(struct sx_dev *dev, enum ku_pkt_type type,
                         u8 swid, u8 etclass, u8 *stclass, u8 *sdq);
    int  (*sx_get_sdq_num_cb)(struct sx_dev *dev, u8 swid, u8 etclass, u8 *sdq);
    int  (*get_send_to_port_as_data_supported_cb)(u8 *send_to_port_as_data_supported);
    int  (*get_rp_vid_cb)(struct sx_dev *dev, struct completion_info *comp_info, u16 *vid);
    int  (*get_swid_cb)(struct sx_dev *dev, struct completion_info *comp_info, u8 *swid);
    int  (*get_lag_mid_cb)(u16 lag_id, u16 *mid);
    int  (*get_ib_system_port_mid)(struct sx_dev *dev, u16 ib_port, u16* sys_port_mid);
    int  (*sx_ptp_init)(struct sx_priv *priv, ptp_mode_t ptp_mode);
    int  (*sx_ptp_cleanup)(struct sx_priv *priv);
    void (*sx_set_device_profile_update_cb)(struct ku_profile* profile, struct profile_driver_params *driver_params);
    void (*sx_init_cq_db_cb)(struct sx_cq *cq, u8 cqn, u8 *cqe_ver);
    void (*sx_printk_cqe_cb)(union sx_cqe *u_cqe);
    u8   (*is_sw_rate_limiter_supported)(void);
    void (*sx_fill_ci_from_cqe_cb)(struct completion_info *ci, union sx_cqe *u_cqe);
    void (*sx_fill_params_from_cqe_cb)(union sx_cqe *u_cqe, u16 *hw_synd_p, u8  *is_isx_p,
                                       u16 *byte_count_p, u8 *dqn_p, u8 *crc_present_p);
    void    (*sx_disconnect_all_trap_groups_cb)(struct sx_dev *dev);
    int     (*sx_get_phy_port_max_cb)(uint16_t *port);
    int     (*sx_get_lag_max_cb)(uint16_t *max_lag_p, uint16_t *max_port_lags_p);
    uint8_t (*sx_get_rdq_max_cb)(void);
    int     (*is_eqn_cmd_ifc_only_cb)(int eqn, u8 *is_cmd_ifc_only);
};
struct sx_priv {
    struct sx_dev              dev;
    struct list_head           dev_list;
    struct list_head           ctx_list;
    spinlock_t                 ctx_lock;  /* the ctx_list's lock */
    struct sx_cmd              cmd;
    struct sx_eq_table         eq_table;
    struct sx_cq_table         cq_table;
    struct sx_dq_table         sdq_table;
    struct sx_dq_table         rdq_table;
    struct sx_bitmap           swid_bitmap;
    struct sx_catas_err        catas_err;
    struct sx_fw               fw;
    int                        is_fw_initialized;
    int                        unregistered;
    void __iomem              *clr_base;
    union swid_data            swid_data[NUMBER_OF_SWIDS];
    struct ku_l2_tunnel_params l2_tunnel_params;

    /* PTP clock */
    struct sx_tstamp tstamp;
    void __iomem    *ptp_hw_frc_base;
    int              ptp_cqn;

    /* IB only */
    u8 ib_to_local_db[MAX_IBPORT_NUM + 1];
    /* ETH only */
    u8  system_to_local_db[MAX_SYSPORT_NUM];
    u16 local_to_system_db[MAX_PHYPORT_NUM + 1];
    u8  lag_member_to_local_db[MAX_LAG_NUM][MAX_LAG_MEMBERS_NUM];
    u8  local_is_rp[MAX_PHYPORT_NUM + 1];
    u16 local_rp_vid[MAX_PHYPORT_NUM + 1];
    u8  lag_is_rp[MAX_LAG_NUM];
    u16 lag_rp_vid[MAX_LAG_NUM];
    u16 fid_to_hwfid[MAX_FIDS_NUM];
    u16 rif_id_to_hwfid[MAX_RIFS_NUM];

    /* common */
    long             cq_last_time_armed[NUMBER_OF_SDQS + NUMBER_OF_RDQS];
    long             cq_last_time_event[NUMBER_OF_SDQS + NUMBER_OF_RDQS];
    struct sx_bitmap cq_high_priority;
    u8               local_to_swid_db[MAX_PHYPORT_NUM + 1];
    spinlock_t       db_lock;            /* Lock for all DBs */
    u16              pvid_sysport_db[MAX_SYSPORT_NUM];
    u16              pvid_lag_db[MAX_LAG_NUM];

#if defined(PD_BU)
    /* Part of the PUDE WA for MLNX OS (PUDE event are handled manually):
     * - should be removed before Phoenix bring up;
     * - field in kernel DB to store port admin status;
     */
    u8 admin_status_sysport_db[MAX_SYSPORT_NUM];
#endif

    u16 truncate_size_db[NUMBER_OF_RDQS];
    u16 sysport_filter_db[NUM_HW_SYNDROMES][MAX_SYSTEM_PORTS_IN_FILTER];
    u16 lag_filter_db[NUM_HW_SYNDROMES][MAX_LAG_PORTS_IN_FILTER];
    u8  lag_oper_state[MAX_LAG_NUM];
    u8  port_ber_monitor_bitmask[MAX_PHYPORT_NUM + 1];
    u8  port_ber_monitor_state[MAX_PHYPORT_NUM + 1];
    u8  tele_thrs_state[MAX_PHYPORT_NUM + 1];
    u64 tele_thrs_tc_vec[MAX_PHYPORT_NUM + 1];
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
    struct sx_bitmap      active_monitor_cq_bitmap;      /* WJH CQs that hold CQEs to handle */
};
struct listener_entry {
    u8                        swid;
    enum l2_type              listener_type;
    u8                        is_default;   /* is a default listener  */
    union ku_filter_critireas critireas;    /* more filter critireas  */
    cq_handler                handler;      /* The completion handler */
    void                     *context;      /* to pass to the handler */
    u64                       rx_pkts;
    struct list_head          list;
};
struct listener_port_vlan_entry {
    enum port_vlan_match match_crit;
    u16                  sysport;
    u16                  lag_id;
    u16                  vlan;

    struct {
        struct sx_core_counter_category category;

        struct {
            struct {
                struct sx_core_counter global;
                struct sx_core_counter sysport;
                struct sx_core_counter lag;
                struct sx_core_counter vlan;
            } accepted;

            struct {
                struct sx_core_counter sysport;
                struct sx_core_counter lag;
                struct sx_core_counter vlan;
            } mismtach;
        } listener_port_vlan;

        struct {
            struct {
                struct sx_core_counter def;
                struct sx_core_counter l2_dont_care;
                struct sx_core_counter l2_eth;
                struct sx_core_counter l2_ib;
            } accepted;

            struct {
                struct {
                    struct sx_core_counter swid;
                    struct sx_core_counter context;
                } common;

                struct {
                    struct sx_core_counter sysport;
                } l2_dont_care;

                struct {
                    struct sx_core_counter no_eth;
                    struct sx_core_counter ethtype;
                    struct sx_core_counter dmac;
                    struct sx_core_counter emad_tid;
                    struct sx_core_counter from_rp;
                    struct sx_core_counter from_bridge;
                } l2_eth;

                struct {
                    struct sx_core_counter no_ib;
                    struct sx_core_counter qpn;
                } l2_ib;
            } mismatch;
        } listener;
    } counters;

    struct listener_entry listener;
    struct list_head      list;
};
struct sx_globals {
    struct rw_semaphore             pci_restart_lock;
    spinlock_t                      pci_devs_lock; /* the devs list lock */
    struct list_head                pci_devs_list;
    int                             pci_devs_cnt;
    struct sx_dev                  *tmp_dev_ptr;
    struct sx_dev                  *oob_backbone_dev; /* SwitchX that interconnects all OOB devices */
    struct sx_dpt_s                 sx_dpt;
    struct sx_i2c_ifc               sx_i2c;
    struct sx_stats                 stats;
    struct ku_profile               profile;
    int                             index[SX_MAX_DEVICES];
    struct listener_port_vlan_entry listeners_db[NUM_HW_SYNDROMES + 1];
    spinlock_t                      listeners_lock; /* listeners' lock */
    struct cdev                     cdev;
    u8                              pci_drivers_in_use;
};
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
};

/************************************************
 * Inline Functions
 ***********************************************/
static inline struct sx_priv * sx_priv(struct sx_dev *p_dev)
{
    return container_of(p_dev, struct sx_priv, dev);
}

void * sx_get_dev_context(void);
void inc_unconsumed_packets_global_counter(u16 hw_synd, enum sx_packet_type pkt_type);
void inc_filtered_lag_packets_global_counter(void);
void inc_filtered_port_packets_global_counter(void);
void inc_unconsumed_packets_counter(struct sx_dev *dev, u16 hw_synd, enum sx_packet_type pkt_type);
void inc_filtered_lag_packets_counter(struct sx_dev *dev);
void inc_filtered_port_packets_counter(struct sx_dev *dev);
int get_system_status(struct sx_dev *dev, u16 *system_status);
int sx_reset(struct sx_dev *dev, u8 perform_chip_reset);
int sx_core_register_device(struct sx_dev *dev);
void sx_core_unregister_device(struct sx_dev *dev);
int sx_cmd_init(struct sx_dev *dev);
int sx_cmd_init_pci(struct sx_dev *dev);
int sx_cmd_pool_create(struct sx_dev *dev);
void sx_cmd_pool_destroy(struct sx_dev *dev);
void sx_cmd_unmap(struct sx_dev *dev);
void sx_core_start_catas_poll(struct sx_dev *dev);
void sx_core_stop_catas_poll(struct sx_dev *dev);
int sx_core_catas_init(struct sx_dev *dev);
void sx_core_catas_cleanup(struct sx_dev *dev);
int sx_restart_one_pci(struct pci_dev *pdev);
int sx_enable_swid(struct sx_dev *dev, int sx_dev_id, u8 swid, int synd, u64 mac);
void sx_disable_swid(struct sx_dev *dev, u8 swid);
int sx_change_configuration(struct sx_dev *dev);
int sx_handle_set_profile(struct sx_dev *dev);
int sx_build_isx_header(struct isx_meta *meta, struct sk_buff *skb, u8 stclass);
int sx_build_isx_header_v0(struct isx_meta *meta, struct sk_buff *skb, u8 stclass,  u8 hw_etclass);
int sx_build_isx_header_v1(struct isx_meta *meta, struct sk_buff *skb, u8 stclass,  u8 hw_etclass);
int sx_get_sdq(struct isx_meta *meta, struct sx_dev *dev, enum ku_pkt_type type, u8 swid,
               u8 etclass, u8 *stclass, u8 *sdq, u8 *max_cpu_etclass_for_unlimited_mtu);

/**
 * The following function is a wrapper for chip-specific
 * callbacks, which are used for getting relevant SDQ numbers
 * (IDs) which we want to create/delete.
 */
int sx_get_sqd_num(struct sx_dev *dev, u8 swid, u8 etclass, u8 *sdq);


int sx_get_sdq_from_profile(struct sx_dev *dev, enum ku_pkt_type type,
                            u8 swid, u8 etclass, u8 *stclass, u8 *sdq);
int sx_get_sdq_per_traffic_type(struct sx_dev *dev, enum ku_pkt_type type, u8 swid, u8 etclass,
                                u8 *stclass, u8 *sdq);
void sx_core_dispatch_event(struct sx_dev *dev, enum sx_dev_event type,
                            union sx_event_data *event_data);


/**
 * The following function is used as a callback for devices
 * where we are getting SDQ number for creation from device
 * PCI profile.
 * Please note that the further SDQ handling will be based on
 * traffic type and handled by 'sx_get_sdq_cb'
 */
int sx_get_sdq_num_from_profile(struct sx_dev *dev, u8 swid, u8 etclass, u8 *sdq);

/**
 * The following function is used as a callback for devices
 * where we are getting SDQ number for creation based on the
 * specified egress TC.
 * Please note that the further SDQ handling will be based on
 * traffic type and handled by 'sx_get_sdq_cb'
 */
int sx_get_sdq_num_per_etclasss(struct sx_dev *dev, u8 swid, u8 etclass, u8 *sdq);

#endif  /* SX_H */

/************************************************
 *                  EOF                         *
 ***********************************************/
