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

#include <linux/module.h>
#include <linux/delay.h>

#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/skb_hook.h>
#include <linux/mlx_sx/driver.h>
#include <linux/mlx_sx/auto_registers/cmd_auto.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include <linux/mlx_sx/cmd.h>

#include "sx.h"
#include "emad.h"
#include "dev_db.h"
#include "sx_dbg_dump_proc.h"

int emad_timeout_usec = 20000000;
module_param_named(emad_timeout_usec, emad_timeout_usec, int, 0644);
MODULE_PARM_DESC(emad_timeout_usec, "EMAD timeout in usec (only EMADs generated in driver)");

extern int rx_dump;
extern int tx_dump;

#define SX_EMAD_TLV_BUILD_TYPE_LEN(type, len_in_dwords) (cpu_to_be16(((type) << 11) | (len_in_dwords)))
#define SX_EMAD_TLV_GET_TYPE_LEN(tlv_hdr)               (cpu_to_be16(*(u16*)(tlv_hdr)))
#define SX_EMAD_TLV_TYPE(tlv_hdr)                       (SX_EMAD_TLV_GET_TYPE_LEN(tlv_hdr) >> 11)
#define SX_EMAD_TLV_LEN(tlv_hdr)                        (SX_EMAD_TLV_GET_TYPE_LEN(tlv_hdr) & 0x7ff)

#define SX_EMAD_TLV_LEN_IN_DWORDS            (1)
#define SX_EMAD_ETH_HDR_SIZE_IN_DWORDS       (4)
#define SX_EMAD_OPERATION_TLV_SIZE_IN_DWORDS (4)
#define SX_EMAD_END_TLV_SIZE_IN_DWORDS       (1)
#define SX_EMAD_STRING_TLV_SIZE_IN_DWORDS    (33)
#define SX_EMAD_LATENCY_TLV_SIZE_IN_DWORDS   (7)

#define SX_EMAD_TID_PREFIX   (0xc0ffee00)
#define SX_EMAD_TIMEOUT_MSEC (20000) /* 20 seconds */

#define SX_EMAD_FRAME_SIZE(string_tlv, latency_tlv, reg_size_in_dwords) \
    (4 * (SX_EMAD_ETH_HDR_SIZE_IN_DWORDS +                              \
          SX_EMAD_OPERATION_TLV_SIZE_IN_DWORDS +                        \
          ((string_tlv) ? SX_EMAD_STRING_TLV_SIZE_IN_DWORDS : 0) +      \
          ((latency_tlv) ? SX_EMAD_LATENCY_TLV_SIZE_IN_DWORDS : 0) +    \
          (reg_size_in_dwords + SX_EMAD_TLV_LEN_IN_DWORDS) +            \
          SX_EMAD_END_TLV_SIZE_IN_DWORDS))

#define SX_EMAD_TX_SKB_SIZE (1514)

#define SX_EMAD_F_SUPPORTED   (1 << 0)  /* does device support EMAD? */
#define SX_EMAD_F_STRING_TLV  (1 << 1)  /* include string TLV?       */
#define SX_EMAD_F_LATECNY_TLV (1 << 2)  /* include latency TLV?      */

static struct kmem_cache *__emad_transaction_cache = NULL;

typedef enum {
    SX_EMAD_TLV_TYPE_END_E,
    SX_EMAD_TLV_TYPE_OPERATION_E,
    SX_EMAD_TLV_TYPE_STRING_E,
    SX_EMAD_TLV_TYPE_REG_E,
    SX_EMAD_TLV_TYPE_LATENCY_E
} sx_emad_tlv_types_e;

typedef enum {
    /* Values are taken from PRM */
    SX_EMAD_STATUS_OK_E                     = 0x0,
    SX_EMAD_STATUS_BUSY_E                   = 0x1,
    SX_EMAD_STATUS_BAD_BASE_VER_E           = 0x2,
    SX_EMAD_STATUS_BAD_TLV_E                = 0x3,
    SX_EMAD_STATUS_NOT_SUPP_REG_E           = 0x4,
    SX_EMAD_STATUS_NOT_SUPP_CLASS_E         = 0x5,
    SX_EMAD_STATUS_NOT_SUPP_METHOD_E        = 0x6,
    SX_EMAD_STATUS_BAD_PARAM_E              = 0x7,
    SX_EMAD_STATUS_RESOURCE_NOT_AVAILABLE_E = 0x8,
    SX_EMAD_STATUS_LONG_PROCESS_E           = 0x9,
    SX_EMAD_STATUS_RETRY_E                  = 0xa,
    SX_EMAD_STATUS_PERIPHERAL_ERR_E         = 0xb,
    SX_EMAD_STATUS_PROFILE_NO_MEMORY_E      = 0xc,
    SX_EMAD_STATUS_ISSU_ONGOING_E           = 0xd,
    SX_EMAD_STATUS_BAD_CONFIG_E             = 0x20,
    SX_EMAD_STATUS_ERASE_EXCEEDED_E         = 0x21,
    SX_EMAD_STATUS_ERROR_E                  = 0x22,
    SX_EMAD_STATUS_REG_LENGTH_TOO_SMALL_E   = 0x24,
    SX_EMAD_STATUS_INTERNAL_ERR_E           = 0x70,
    SX_EMAD_STATUS_DROP_E                   = 0x7f
} sx_emad_status_e;

struct sx_emad_operation_tlv {
    u16 type_len;
    u8  dr_status;
    u8  reserved;
    u16 register_id;
    u8  r_method;
    u8  class;
    u64 tid;
} __attribute__ ((__packed__));

struct sx_emad_string_tlv {
    u16  type_len;
    u8   reserved[2];
    char string[128];
} __attribute__ ((__packed__));

struct sx_emad_latency_tlv {
    u16 type_len;
    u8  reserved1;
    u8  ccrt_v;
    u32 latency_time;
    u32 code_cache_read_time;
    u8  reserved2[3];
    u8  opaque0_type;
    u32 opaque0;
    u8  reserved3[3];
    u8  opaque1_type;
    u32 opaque1;
} __attribute__ ((__packed__));

struct sx_emad_reg_tlv {
    u16 type_len;
    u16 reserved1;
    u8  reg_data[0];
} __attribute__ ((__packed__));

struct sx_emad_end_tlv {
    u16 type_len;
    u16 reserved1;
} __attribute__ ((__packed__));

struct sx_emad_tlv_markers {
    struct sx_emad_operation_tlv *operation_tlv;
    struct sx_emad_string_tlv    *string_tlv;
    struct sx_emad_latency_tlv   *latency_tlv;
    struct sx_emad_reg_tlv       *reg_tlv;
    struct sx_emad_end_tlv       *end_tlv;
};

#define SX_EMAD_MAX_TLV_HEADERS (sizeof(struct sx_emad_tlv_markers) / sizeof(void*))

typedef u64 sx_emad_tid_t;

typedef enum {
    SX_EMAD_TR_STATE_ALLOCATED,
    SX_EMAD_TR_STATE_IN_TX_QUEUE,
    SX_EMAD_TR_STATE_RX_RECEIVED,
} sx_emad_transaction_state_e;

struct sx_emad_completion_status {
    bool timedout; /* has transaction timed out? */

    /* following data is valid only if transaction has not timed out */
    sx_emad_status_e fw_status;
    const char      *fw_error; /* valid only when fw_status is not OK and string_tlv is supported by the device */
    u32              fw_latency; /* valid only if latency_tlv is supported by the device */
};

typedef void (*sx_emad_reg_access_completion_t)(struct sx_dev                          *dev,
                                                const struct sx_emad_completion_status *emad_comp_status,
                                                void                                   *prm_reg,
                                                u32                                     prm_reg_len,
                                                void                                   *context);

struct sx_emad_transaction {
    struct sx_dev                   *dev;
    struct list_head                 list;    /* transaction list */
    sx_emad_method_e                 method;
    sx_emad_tid_t                    tid;
    u16                              reg_id;
    const struct sx_emad_in_params  *in_params;
    struct sx_emad_completion_status status;
    sx_emad_reg_access_completion_t  completion_cb;
    void                            *completion_cb_context;
    struct sk_buff                  *skb_tx;
    emad_prio_e                      priority;
    sx_emad_transaction_state_e      tr_state;
    unsigned long                    since;    /* jiffies */
};

struct sx_sync_emad_context {
    bool                       timedout;
    struct completion          comp;
    struct sx_emad_out_params *out_params;
};

struct sx_sync_emad_read_context {
    struct sx_sync_emad_context sync_ctx;
    access_reg_decode_cb_t      decode_cb;
    void                       *ku_reg;
};

static int __fw_status_to_err(u32 fw_status)
{
    switch (fw_status) {
    case SX_EMAD_STATUS_OK_E:
        return 0;

    case SX_EMAD_STATUS_BUSY_E:
        return -EBUSY;

    case SX_EMAD_STATUS_RESOURCE_NOT_AVAILABLE_E:
        return -ENOMEM;

    default:
        return -EIO;
    }

    return -EIO;
}

static struct sx_emad_transaction * __alloc_emad_transaction(void)
{
    return (struct sx_emad_transaction*)kmem_cache_zalloc(__emad_transaction_cache, GFP_KERNEL);
}

static void __dealloc_emad_transaction(struct sx_emad_transaction *emad_tr)
{
    kmem_cache_free(__emad_transaction_cache, emad_tr);
}

static void __complete_emad_transaction(struct sx_emad_transaction *emad_tr, void *prm_reg, u32 prm_reg_len)
{
    if (emad_tr->completion_cb) {
        emad_tr->completion_cb(emad_tr->dev,
                               &emad_tr->status,
                               prm_reg,
                               prm_reg_len,
                               emad_tr->completion_cb_context);
    }

    __dealloc_emad_transaction(emad_tr);
}

static int __get_tlv_headers(struct sk_buff *skb, struct sx_emad_tlv_markers *tlv_markers)
{
    u8 *buff;
    u32 buff_size;
    u32 tlv_len;
    int emad_tlv_type;
    int budget = SX_EMAD_MAX_TLV_HEADERS; /* we expect up to 'SXD_EMAD_MAX_HEADERS' TLV headers in the EMAD frame.
                                           *  'budget' is to make sure we're not in infinite loop here  */
    const char *reason = NULL;

    if (skb->len < SX_EMAD_ETH_HDR_SIZE_IN_DWORDS * 4) {
        reason = "Buffer does not even hold the EMAD header!";
        goto bad_emad_frame;
    }

    buff = skb->data + SX_EMAD_ETH_HDR_SIZE_IN_DWORDS * 4;
    buff_size = skb->len - SX_EMAD_ETH_HDR_SIZE_IN_DWORDS * 4;
    memset(tlv_markers, 0, sizeof(*tlv_markers));

    while (budget > 0 && !tlv_markers->end_tlv) {
        emad_tlv_type = SX_EMAD_TLV_TYPE(buff);

        switch (emad_tlv_type) {
        case SX_EMAD_TLV_TYPE_OPERATION_E:
            tlv_markers->operation_tlv = (struct sx_emad_operation_tlv*)buff;
            break;

        case SX_EMAD_TLV_TYPE_STRING_E:
            tlv_markers->string_tlv = (struct sx_emad_string_tlv*)buff;
            break;

        case SX_EMAD_TLV_TYPE_LATENCY_E:
            tlv_markers->latency_tlv = (struct sx_emad_latency_tlv*)buff;
            break;

        case SX_EMAD_TLV_TYPE_REG_E:
            tlv_markers->reg_tlv = (struct sx_emad_reg_tlv*)buff;
            break;

        case SX_EMAD_TLV_TYPE_END_E:
            tlv_markers->end_tlv = (struct sx_emad_end_tlv*)buff;
            break;

        default:
            reason = "Bad TLV type";
            goto bad_emad_frame;
            break;
        }

        tlv_len = SX_EMAD_TLV_LEN(buff) * 4;

        if (tlv_len > buff_size) {
            reason = "Buffer is too short";
            goto bad_emad_frame;
        }

        buff += tlv_len;
        buff_size -= tlv_len;
        budget--;
    }

    /* check that all mandatory TLVs are there */
    if (!tlv_markers->operation_tlv || !tlv_markers->reg_tlv || !tlv_markers->end_tlv) {
        reason = "Mandatory TLV header is missing";
        goto bad_emad_frame;
    }

    return 0;

bad_emad_frame:
    printk(KERN_ERR "EMAD bad RX frame [%s]!\n", reason);
    print_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 16, 1, skb->data, skb->len, 0);
    return -EINVAL;
}

static bool __emad_transaction_in_range(sx_emad_tid_t tid, sx_emad_tid_t head_tid, sx_emad_tid_t tail_tid)
{
    /*
     * this function tries to figure out if a certain transaction ID 'tid' exists in a list of
     * in-flight transaction IDs. the first tid in the list is 'head_tid'. the last tid in the list
     * is 'tail_tid'.
     *
     * the most common and simple case is [head_tid <= tid <= tail_tid].
     *
     * the corner case is when we have a wrap-around in the list:
     * [head_tid, ..., MAX_TID_VALUE, ZERO_TID_VALUE, ..., tail_tid]
     * the tid is in this list if [head_tid <= tid <= MAX_TID_VALUE] or [ZERO_TID_VALUE <= tid <= tail_tid]
     * where ZERO_TID_VALUE=(0x<__emad_tid_base> | 0x00000000), MAX_TID_VALUE=(0x<__emad_tid_base> | 0xffffffff)
     */

    if (head_tid <= tail_tid) {
        /* most of the time, head_tid <= tail_tid */
        return (tid >= head_tid && tid <= tail_tid);
    }

    /* if we're here (tid wrap-around), head_tid >= tail_tid */
    return (tid >= head_tid || tid <= tail_tid);
}

/* must be called when transaction list is locked! */
static struct sx_emad_transaction * __tid_lookup(struct sx_priv *priv, sx_emad_tid_t tid)
{
    struct sx_emad_transaction *head_tr, *tail_tr, *emad_tr, *tmp;

    if (list_empty(&priv->emad.transactions_list)) {
        printk(KERN_ERR "EMAD TID 0x%llx is unsolicited: there is no in-flight transaction (dev_id=%u)\n",
               tid, priv->dev.device_id);
        return NULL;
    }

    head_tr = list_first_entry(&priv->emad.transactions_list, struct sx_emad_transaction, list);
    tail_tr = list_last_entry(&priv->emad.transactions_list, struct sx_emad_transaction, list);

    if (!__emad_transaction_in_range(tid, head_tr->tid, tail_tr->tid)) {
        printk("EMAD TID 0x%llx is unsolicited: transaction is out of in-flight range "
               "(dev_id=%u, head_tid=0x%llx, tail_tid=0x%llx)\n",
               tid,
               priv->dev.device_id,
               head_tr->tid,
               tail_tr->tid);
        return NULL;
    }

    list_for_each_entry_safe(emad_tr, tmp, &priv->emad.transactions_list, list) {
        list_del(&emad_tr->list);

        emad_tr->tr_state = SX_EMAD_TR_STATE_RX_RECEIVED;

        /* we expect that requested tid will be at the beginning of the tid-list.
         * in this case, we just change the state of the transaction and go out.
         */
        if (emad_tr->tid == tid) {
            return emad_tr;
        }

        /* if we get here, it means that we have at least one unexpected transaction(s) in the
         * tid-list that comes before the expected one. it can be one of these cases:
         * 1) FW replies come in a different order than the requests we've sent (which is not good).
         * 2) user is working in transaction mode (no one waits for EMAD replies) and one or more
         *    of the requests did not get any reply for some reason.
         *
         * anyhow, we're going to ignore this reply and put an error for this.
         * */
        printk(KERN_ERR "EMAD transaction reply is out-of-order! "
               "(curr_tid=0x%llx, expected_tid (head_tid)=0x%llx, tail_tid=0x%llx "
               "reg_id=0x%x, dev_id=%u, method=%u)\n",
               tid,
               emad_tr->tid,
               tail_tr->tid,
               emad_tr->reg_id,
               priv->dev.device_id,
               emad_tr->method);

        /* if no one waits for the transaction (sync_event is NULL), let's deallocate the buffer.
         * if the main thread waited for this transaction and already timed out, the main thread
         * is responsible for deallocating the transaction.
         */
        emad_tr->status.timedout = true;
        __complete_emad_transaction(emad_tr, NULL, 0);
    }

    return NULL;
}

static void __emad_rx(struct completion_info *ci, void *context)
{
    struct sx_priv             *priv = sx_priv((struct sx_dev*)context);
    struct sk_buff             *skb = ci->skb;
    struct sx_emad_transaction *emad_tr;
    struct sx_emad_tlv_markers  tlv_markers;
    sx_emad_tid_t               tid;
    int                         err;

    if (rx_dump) {
        print_hex_dump(KERN_NOTICE, "", DUMP_PREFIX_OFFSET, 16, 1, skb->data, skb->len, 0);
    }

    err = __get_tlv_headers(skb, &tlv_markers);
    if (err) {
        return;
    }

    tid = be64_to_cpu(tlv_markers.operation_tlv->tid);

    spin_lock_bh(&priv->emad.transactions_lock);
    emad_tr = __tid_lookup(priv, tid);
    spin_unlock_bh(&priv->emad.transactions_lock);

    if (!emad_tr) { /* transaction was not found ... */
        return;
    }

    emad_tr->status.timedout = false;
    emad_tr->status.fw_status = tlv_markers.operation_tlv->dr_status & 0x7f;
    emad_tr->status.fw_error = tlv_markers.string_tlv ? tlv_markers.string_tlv->string : NULL;
    emad_tr->status.fw_latency = tlv_markers.latency_tlv ? be32_to_cpu(tlv_markers.latency_tlv->latency_time) : 0;

    if ((emad_tr->status.fw_status != SX_EMAD_STATUS_OK_E) && !emad_tr->in_params->silent) {
        printk(
            KERN_ERR "EMAD transaction FW error (tid=0x%llx, reg_id=0x%x, dev_id=%u, method=%u, priority=%u, fw_status=%u, fw_cause='%s')\n",
            emad_tr->tid,
            emad_tr->reg_id,
            emad_tr->dev->device_id,
            emad_tr->method,
            emad_tr->priority,
            emad_tr->status.fw_status,
            ((emad_tr->status.fw_error) ? emad_tr->status.fw_error : "N/A"));
        print_hex_dump(KERN_NOTICE, "", DUMP_PREFIX_OFFSET, 16, 1, skb, skb->len, 0);
    }

    __complete_emad_transaction(emad_tr,
                                tlv_markers.reg_tlv->reg_data,
                                4 * (SX_EMAD_TLV_LEN(tlv_markers.reg_tlv) - 1));
}

/* must be called within device's EMAD transactions lock */
static sx_emad_tid_t __create_transaction_id(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);
    sx_emad_tid_t   tid;

    /*
     * EMAD Transaction ID (64bit):
     *
     *       6         5         4         3         2         1
     *    3210987654321098765432109876543210987654321098765432109876543210
     *    |                               |       |
     *    |                               |       +--------- bits 00-23 (24bits) --> running counter
     *    |                               |                                          (no problem of wrap-around)
     *    |                               +----------------- bits 24-31 (8bits)  --> device-id
     *    +------------------------------------------------- bits 32-63 (32bits) --> SX_EMAD_TID_PREFIX
     */

    priv->emad.tid_lsb++;

    tid = ((u64)SX_EMAD_TID_PREFIX) << 32 |
          (((u32)dev->device_id) << 24) |
          (priv->emad.tid_lsb & 0xffffff);

    return tid;
}

static void __build_eth_header(u8 **buff)
{
    static const u8 eth_hdr[] = {
        0x01, 0x02, 0xc9, 0x00,
        0x00, 0x01, 0x00, 0x02,
        0xc9, 0x01, 0x02, 0x03,
        0x89, 0x32, 0x00, 0x00
    };

    memcpy(*buff, eth_hdr, sizeof(eth_hdr));
    *buff += sizeof(eth_hdr);
}

static void __build_operation_tlv(u8 **buff, u16 reg_id, sx_emad_method_e method)
{
    struct sx_emad_operation_tlv *op_tlv = (struct sx_emad_operation_tlv*)*buff;
    u32                           len = SX_EMAD_OPERATION_TLV_SIZE_IN_DWORDS * 4;

    memset(op_tlv, 0, len);
    op_tlv->type_len = SX_EMAD_TLV_BUILD_TYPE_LEN(SX_EMAD_TLV_TYPE_OPERATION_E, SX_EMAD_OPERATION_TLV_SIZE_IN_DWORDS);
    op_tlv->r_method = method;
    op_tlv->class = 0x1;
    op_tlv->register_id = cpu_to_be16(reg_id);
    op_tlv->tid = 0; /* will be filled later */

    *buff += len;
}

static void __build_string_tlv(u8 **buff)
{
    u32 len = SX_EMAD_STRING_TLV_SIZE_IN_DWORDS * 4;

    memset(*buff, 0, len);
    *((u16*)*buff) = SX_EMAD_TLV_BUILD_TYPE_LEN(SX_EMAD_TLV_TYPE_STRING_E, SX_EMAD_STRING_TLV_SIZE_IN_DWORDS);
    *buff += len;
}

static void __build_latency_tlv(u8 **buff)
{
    u32 len = SX_EMAD_LATENCY_TLV_SIZE_IN_DWORDS * 4;

    memset(*buff, 0, len);
    *((u16*)*buff) = SX_EMAD_TLV_BUILD_TYPE_LEN(SX_EMAD_TLV_TYPE_LATENCY_E, SX_EMAD_LATENCY_TLV_SIZE_IN_DWORDS);
    *buff += len;
}

static void __build_reg_tlv(u8 **buff, u32 prm_reg_len_in_dwords)
{
    u32 len = (prm_reg_len_in_dwords + SX_EMAD_TLV_LEN_IN_DWORDS) * 4;

    memset(*buff, 0, len);
    *((u16*)*buff) = SX_EMAD_TLV_BUILD_TYPE_LEN(SX_EMAD_TLV_TYPE_REG_E,
                                                prm_reg_len_in_dwords + SX_EMAD_TLV_LEN_IN_DWORDS);
    *buff += len;
}

static void __build_end_tlv(u8 **buff)
{
    u32 len = SX_EMAD_END_TLV_SIZE_IN_DWORDS * 4;

    memset(*buff, 0, len);
    *((u16*)*buff) = SX_EMAD_TLV_BUILD_TYPE_LEN(SX_EMAD_TLV_TYPE_END_E, SX_EMAD_END_TLV_SIZE_IN_DWORDS);
    *buff += len;
}

static struct sk_buff * __build_emad_skb(gfp_t                       gfp,
                                         sx_emad_method_e            method,
                                         u16                         reg_id,
                                         u32                         flags,
                                         u32                         prm_reg_len_in_dwords,
                                         struct sx_emad_tlv_markers *markers)
{
    struct sk_buff *skb;
    unsigned int    headroom;
    u8             *curr_hdr;

    skb = alloc_skb(SX_EMAD_TX_SKB_SIZE, gfp);
    if (!skb) {
        goto out;
    }

    headroom = skb_headroom(skb);
    if (headroom < ISX_HDR_SIZE) {
        skb_reserve(skb, ISX_HDR_SIZE - headroom);
    }

    skb_put(skb,
            SX_EMAD_FRAME_SIZE((flags & SX_EMAD_F_STRING_TLV),
                               (flags & SX_EMAD_F_LATECNY_TLV),
                               prm_reg_len_in_dwords));

    curr_hdr = skb->data;

    __build_eth_header(&curr_hdr);

    markers->operation_tlv = (struct sx_emad_operation_tlv*)curr_hdr;
    __build_operation_tlv(&curr_hdr, reg_id, method);

    if (flags & SX_EMAD_F_STRING_TLV) {
        markers->string_tlv = (struct sx_emad_string_tlv*)curr_hdr;
        __build_string_tlv(&curr_hdr);
    } else {
        markers->string_tlv = NULL;
    }

    if (flags & SX_EMAD_F_LATECNY_TLV) {
        markers->latency_tlv = (struct sx_emad_latency_tlv*)curr_hdr;
        __build_latency_tlv(&curr_hdr);
    } else {
        markers->latency_tlv = NULL;
    }

    markers->reg_tlv = (struct sx_emad_reg_tlv*)curr_hdr;
    __build_reg_tlv(&curr_hdr, prm_reg_len_in_dwords);

    markers->end_tlv = (struct sx_emad_end_tlv*)curr_hdr;
    __build_end_tlv(&curr_hdr);

out:
    return skb;
}

static void __init_meta(sxd_dev_id_t dev_id, struct isx_meta *meta)
{
    memset(meta, 0, sizeof(*meta));

    meta->dev_id = dev_id;
    meta->etclass = 6; /* EMAD ETCLASS */
    meta->rdq = 0x1f;
    meta->lp = 1;
    meta->type = SX_PKT_TYPE_EMAD_CTL;
}

int sx_emad_build(sxd_dev_id_t     dev_id,
                  const u8        *reg_buff,
                  u32              reg_buff_len,
                  struct sk_buff **skb,
                  struct isx_meta *meta,
                  u32              tid_high,
                  u32              tid_low,
                  gfp_t            gfp,
                  u16              reg_id,
                  sx_emad_method_e method)
{
    struct sx_emad_tlv_markers tlv_markers;
    struct sk_buff            *new_skb;

    new_skb = __build_emad_skb(gfp, method, reg_id, 0, reg_buff_len / 4, &tlv_markers);
    if (!new_skb) {
        return -ENOMEM;
    }

    __init_meta(dev_id, meta);
    tlv_markers.operation_tlv->tid = cpu_to_be64((((u64)tid_high) << 32) | tid_low);
    memcpy(tlv_markers.reg_tlv->reg_data, reg_buff, reg_buff_len);

    *skb = new_skb;
    return 0;
}

static struct sx_emad_transaction * __create_emad_transaction(struct sx_dev                  *dev,
                                                              emad_prio_e                     priority,
                                                              sx_emad_method_e                method,
                                                              u16                             reg_id,
                                                              const struct sx_emad_in_params *in_params,
                                                              sx_emad_reg_access_completion_t completion_cb,
                                                              void                           *completion_cb_context,
                                                              struct sk_buff                 *skb)
{
    struct sx_emad_transaction *emad_tr;

    emad_tr = __alloc_emad_transaction();
    if (!emad_tr) {
        goto out;
    }

    emad_tr->dev = dev;
    emad_tr->method = method;
    emad_tr->reg_id = reg_id;
    emad_tr->tid = 0; /* will be filled later */
    INIT_LIST_HEAD(&emad_tr->list);
    emad_tr->skb_tx = skb;
    emad_tr->in_params = in_params;
    emad_tr->completion_cb = completion_cb;
    emad_tr->completion_cb_context = completion_cb_context;
    emad_tr->priority = priority;
    emad_tr->tr_state = SX_EMAD_TR_STATE_ALLOCATED;
    emad_tr->since = jiffies;

out:
    return emad_tr;
}

static void __delete_emad_transaction(struct sx_emad_transaction *emad_tr)
{
    list_del(&emad_tr->list);
    __dealloc_emad_transaction(emad_tr);
}

static int __send_emad(struct sx_dev *dev, struct sx_emad_transaction *emad_tr, struct sx_emad_operation_tlv *op_tlv)
{
    struct sx_priv *priv = sx_priv(dev);
    struct isx_meta meta;
    struct sk_buff *skb = emad_tr->skb_tx;
    int             err;

    __init_meta(dev->device_id, &meta);

    spin_lock_bh(&priv->emad.transactions_lock);

    emad_tr->tid = __create_transaction_id(dev);
    op_tlv->tid = cpu_to_be64(emad_tr->tid);

    list_add_tail(&emad_tr->list, &priv->emad.transactions_list);

    if (tx_dump) {
        print_hex_dump(KERN_NOTICE, "", DUMP_PREFIX_OFFSET, 16, 1, skb->data, skb->len, 0);
    }

    err = sx_qos_emad_push_to_queue(dev, skb, &meta, emad_tr->priority);
    if (err) {
        kfree_skb(emad_tr->skb_tx);
        __delete_emad_transaction(emad_tr);
    } else {
        emad_tr->tr_state = SX_EMAD_TR_STATE_IN_TX_QUEUE;
    }

    spin_unlock_bh(&priv->emad.transactions_lock);

    return err;
}

struct sx_emad_transaction * __emad_reg_send(struct sx_dev                  *dev,
                                             emad_prio_e                     priority,
                                             sx_emad_method_e                method,
                                             u16                             reg_id,
                                             void                           *ku_reg,
                                             u32                             prm_reg_len_in_dwords,
                                             const struct sx_emad_in_params *in_params,
                                             access_reg_encode_cb_t          encode_cb,
                                             sx_emad_reg_access_completion_t completion_cb,
                                             void                           *completion_cb_context)
{
    struct sx_priv             *priv = sx_priv(dev);
    struct sx_emad_tlv_markers  tlv_markers;
    struct sx_emad_transaction *emad_tr = NULL;
    struct sk_buff             *skb;
    int                         err;

    skb = __build_emad_skb(GFP_KERNEL,
                           method,
                           reg_id,
                           priv->emad.flags,
                           prm_reg_len_in_dwords,
                           &tlv_markers);
    if (!skb) {
        goto out;
    }

    emad_tr = __create_emad_transaction(dev,
                                        priority,
                                        method,
                                        reg_id,
                                        in_params,
                                        completion_cb,
                                        completion_cb_context,
                                        skb);
    if (!emad_tr) {
        kfree_skb(skb);
        goto out;
    }

    encode_cb(tlv_markers.reg_tlv->reg_data, ku_reg, NULL);

    err = __send_emad(dev, emad_tr, tlv_markers.operation_tlv);
    if (err) { /* EMAD transaction and skb are already freed in this case */
        emad_tr = NULL;
        goto out;
    }

out:
    return emad_tr;
}

static int __sync_wait(struct sx_priv              *priv,
                       struct sx_emad_transaction  *emad_tr,
                       struct sx_sync_emad_context *ctx,
                       u32                          timeout_usec)
{
    bool should_wait;
    long wait_ret;
    int  err = 0;

    do {
        wait_ret = wait_for_completion_interruptible_timeout(&ctx->comp, msecs_to_jiffies(timeout_usec / 1000));
    } while (wait_ret == -ERESTARTSYS);

    if (wait_ret > 0) { /* RX flow signaled us */
        /* if context timed-out, it means that a reply for later transaction has arrived */
        err = (ctx->timedout) ? -ETIMEDOUT : __fw_status_to_err(ctx->out_params->fw_status);
        goto out;
    }

    /* if we got here, the transaction has timed out! */
    err = -ETIMEDOUT;

    spin_lock_bh(&priv->emad.transactions_lock);
    should_wait = (emad_tr->tr_state == SX_EMAD_TR_STATE_RX_RECEIVED);

    printk(KERN_ERR "EMAD TIMEOUT [tid:%llx, method=%u, reg_id=%04x]\n",
           emad_tr->tid,
           emad_tr->method,
           emad_tr->reg_id);

    if (!should_wait) {
        __delete_emad_transaction(emad_tr);
    }

    spin_unlock_bh(&priv->emad.transactions_lock);

    /* we might get into a situation where the timeout expired for an EMAD transaction but the
     * reply from FW received a very-short time after.
     * in this case, we MUST wait for it to complete because RX thread uses some data that
     * was allocated on our own thread's stack (the completion context).
     * we will wait on the very same completion object that was timed-out.
     */

    if (should_wait) {
        do {
            wait_ret = wait_for_completion_interruptible(&ctx->comp);
        } while (wait_ret == -ERESTARTSYS);
    }

out:
    return err;
}

static void __sync_complete(const struct sx_emad_completion_status *emad_comp_status, struct sx_sync_emad_context *ctx)
{
    ctx->timedout = emad_comp_status->timedout;
    if (!emad_comp_status->timedout) {
        ctx->out_params->fw_status = emad_comp_status->fw_status;
        ctx->out_params->fw_latency = emad_comp_status->fw_latency;
    }

    complete(&ctx->comp);
}

static void __sync_init(struct sx_emad_out_params *out_params, u16 reg_id, struct sx_sync_emad_context *ctx)
{
    memset(ctx, 0, sizeof(*ctx));

    init_completion(&ctx->comp);
    ctx->out_params = out_params;
    ctx->out_params->reg_id = reg_id;
}

static void __emad_write_completion(struct sx_dev                          *dev,
                                    const struct sx_emad_completion_status *emad_comp_status,
                                    void                                   *prm_reg,
                                    u32                                     prm_reg_len,
                                    void                                   *context)
{
    struct sx_sync_emad_context *ctx = (struct sx_sync_emad_context*)context;

    __sync_complete(emad_comp_status, ctx);
}

static int __sx_emad_reg_write_sync(struct sx_dev                  *dev,
                                    emad_prio_e                     priority,
                                    u16                             reg_id,
                                    void                           *ku_reg,
                                    u32                             prm_reg_len_in_dwords,
                                    const struct sx_emad_in_params *in_params,
                                    struct sx_emad_out_params      *out_params,
                                    access_reg_encode_cb_t          encode_cb,
                                    u32                             timeout_usec)
{
    struct sx_priv             *priv = sx_priv(dev);
    struct sx_emad_transaction *emad_tr;
    struct sx_sync_emad_context ctx;
    int                         err = 0;

    __sync_init(out_params, reg_id, &ctx);

    emad_tr = __emad_reg_send(dev,
                              priority,
                              EMAD_METHOD_WRITE,
                              reg_id,
                              ku_reg,
                              prm_reg_len_in_dwords,
                              in_params,
                              encode_cb,
                              __emad_write_completion,
                              &ctx);

    if (!emad_tr) {
        err = -ENOMEM;
        goto out;
    }

    err = __sync_wait(priv, emad_tr, &ctx, timeout_usec);

out:
    return err;
}

static void __emad_read_completion(struct sx_dev                          *dev,
                                   const struct sx_emad_completion_status *emad_comp_status,
                                   void                                   *prm_reg,
                                   u32                                     prm_reg_len,
                                   void                                   *context)
{
    struct sx_sync_emad_read_context *ctx = (struct sx_sync_emad_read_context*)context;

    if (!emad_comp_status->timedout && (emad_comp_status->fw_status == SX_EMAD_STATUS_OK_E)) {
        ctx->decode_cb((u8*)prm_reg, ctx->ku_reg, NULL);
    }

    __sync_complete(emad_comp_status, &ctx->sync_ctx);
}

static int __sx_emad_reg_read_sync(struct sx_dev                  *dev,
                                   emad_prio_e                     priority,
                                   u16                             reg_id,
                                   void                           *ku_reg,
                                   u32                             prm_reg_len_in_dwords,
                                   const struct sx_emad_in_params *in_params,
                                   struct sx_emad_out_params      *out_params,
                                   access_reg_encode_cb_t          encode_cb,
                                   access_reg_decode_cb_t          decode_cb,
                                   u32                             timeout_usec)
{
    struct sx_priv                  *priv = sx_priv(dev);
    struct sx_emad_transaction      *emad_tr;
    struct sx_sync_emad_read_context ctx;
    int                              err = 0;

    __sync_init(out_params, reg_id, &ctx.sync_ctx);
    ctx.decode_cb = decode_cb;
    ctx.ku_reg = ku_reg;

    emad_tr = __emad_reg_send(dev,
                              priority,
                              EMAD_METHOD_QUERY,
                              reg_id,
                              ku_reg,
                              prm_reg_len_in_dwords,
                              in_params,
                              encode_cb,
                              __emad_read_completion,
                              &ctx);

    if (!emad_tr) {
        err = -ENOMEM;
        goto out;
    }

    err = __sync_wait(priv, emad_tr, &ctx.sync_ctx, timeout_usec);

out:
    return err;
}

int sx_emad_access_reg_common(struct sx_dev                  *dev,
                              emad_prio_e                     priority,
                              sx_emad_method_e                method,
                              u16                             reg_id,
                              void                           *ku_reg,
                              u32                             prm_reg_len_in_dwords,
                              const struct sx_emad_in_params *in_params,
                              struct sx_emad_out_params      *out_params,
                              access_reg_encode_cb_t          encode_cb,
                              access_reg_decode_cb_t          decode_cb)
{
    struct sx_priv           *priv;
    int                       err = 0;
    struct sx_emad_in_params  backup_in_params;
    struct sx_emad_out_params backup_out_params;

    if (!dev || !reg_id || !ku_reg || !prm_reg_len_in_dwords || !encode_cb ||
        ((method != EMAD_METHOD_WRITE) && (method != EMAD_METHOD_QUERY)) ||
        ((method == EMAD_METHOD_QUERY) && !decode_cb)) {
        return -EINVAL;
    }

    priv = sx_priv(dev);
    if (!(priv->emad.flags & SX_EMAD_F_SUPPORTED)) {
        return -EOPNOTSUPP;
    }

    if (!in_params) {
        memset(&backup_in_params, 0, sizeof(backup_in_params));
        in_params = &backup_in_params;
    }

    if (!out_params) {
        memset(&backup_out_params, 0, sizeof(backup_out_params));
        out_params = &backup_out_params;
    }


    if (method == EMAD_METHOD_WRITE) {
        err = __sx_emad_reg_write_sync(dev,
                                       priority,
                                       reg_id,
                                       ku_reg,
                                       prm_reg_len_in_dwords,
                                       in_params,
                                       out_params,
                                       encode_cb,
                                       emad_timeout_usec);
    } else { /* method == EMAD_METHOD_QUERY */
        err = __sx_emad_reg_read_sync(dev,
                                      priority,
                                      reg_id,
                                      ku_reg,
                                      prm_reg_len_in_dwords,
                                      in_params,
                                      out_params,
                                      encode_cb,
                                      decode_cb,
                                      emad_timeout_usec);
    }

    return err;
}


int sx_emad_dev_init(struct sx_dev *dev)
{
    struct sx_priv           *priv = sx_priv(dev);
    struct ku_access_mgir_reg mgir;
    union ku_filter_critireas crit;
    int                       err = 0;

    INIT_LIST_HEAD(&priv->emad.transactions_list);
    spin_lock_init(&priv->emad.transactions_lock);
    priv->emad.flags = 0;
    priv->emad.tid_lsb = 0;

    memset(&mgir, 0, sizeof(mgir));
    mgir.dev_id = dev->device_id;
    mgir.op_tlv.type = 1;
    mgir.op_tlv.length = 4;
    mgir.op_tlv.register_id = MLXSW_MGIR_ID;
    mgir.op_tlv.method = EMAD_METHOD_QUERY;
    mgir.op_tlv.op_class = 1;

    err = sx_ACCESS_REG_MGIR(dev, &mgir);
    if (err) {
        printk(KERN_ERR "failed to initialize EMAD on device %u\n", dev->device_id);
        goto out;
    }

    switch (mgir.mgir_reg.hw_info.device_id) {
    case SXD_MGIR_HW_DEV_ID_SWITCH_IB:
    case SXD_MGIR_HW_DEV_ID_SWITCH_IB2:
        printk(KERN_NOTICE "device %d does not support EMAD\n", dev->device_id);
        goto out; /* without error (keep err = 0) */

    default:
        priv->emad.flags |= SX_EMAD_F_SUPPORTED;
        break;
    }

    priv->emad.flags |= (mgir.mgir_reg.fw_info.string_tlv) ? SX_EMAD_F_STRING_TLV : 0;
    priv->emad.flags |= (mgir.mgir_reg.fw_info.latency_tlv) ? SX_EMAD_F_LATECNY_TLV : 0;

    printk(KERN_INFO "EMAD is ready on device %u [string_tlv=%s, latency_tlv=%s]\n",
           dev->device_id,
           ((mgir.mgir_reg.fw_info.string_tlv) ? "true" : "false"),
           ((mgir.mgir_reg.fw_info.latency_tlv) ? "true" : "false"));

    memset(&crit, 0, sizeof(crit));
    crit.eth.emad_tid = SX_EMAD_TID_PREFIX;
    err = sx_core_add_synd(0, /* swid */
                           SXD_TRAP_ID_GENERAL_ETH_EMAD,
                           L2_TYPE_ETH,
                           0, /* pid */
                           "EMAD (driver)",
                           0, /* is default? */
                           &crit,
                           __emad_rx,
                           dev,
                           CHECK_DUP_ENABLED_E,
                           dev,
                           NULL,
                           1 /* is register? */);
    if (err) {
        printk(KERN_ERR "failed to register EMAD handler on device %u\n", dev->device_id);
        goto out;
    }

out:
    return err;
}

void sx_emad_dev_deinit(struct sx_dev *dev)
{
    struct sx_priv           *priv = sx_priv(dev);
    union ku_filter_critireas crit;
    bool                      busy;
    int                       err = 0;
    unsigned long             end_wait = jiffies + 5 * HZ; /* we'll wait up to 5 seconds */

    if (!(priv->emad.flags & SX_EMAD_F_SUPPORTED)) {
        return;
    }

    do {
        spin_lock_bh(&priv->emad.transactions_lock);
        busy = !list_empty(&priv->emad.transactions_list);
        spin_unlock_bh(&priv->emad.transactions_lock);

        if (!busy) {
            printk(KERN_WARNING "device %u does not have pending EMADs\n", dev->device_id);
            break;
        }

        printk(KERN_WARNING "device %u has pending EMADs, waiting ...\n", dev->device_id);
        msleep(100);
    } while (time_before(jiffies, end_wait));

    memset(&crit, 0, sizeof(crit));
    crit.eth.emad_tid = SX_EMAD_TID_PREFIX;
    err = sx_core_remove_synd(0, /* swid */
                              SXD_TRAP_ID_GENERAL_ETH_EMAD,
                              L2_TYPE_ETH,
                              0, /* is default? */
                              &crit,
                              dev,
                              dev,
                              __emad_rx,
                              NULL,
                              1, /* is register */
                              NULL);
    if (err) {
        printk(KERN_ERR "failed to unregister EMAD handler on device %u\n", dev->device_id);
    }
}

static const char * __state_to_str(sx_emad_transaction_state_e state)
{
    switch (state) {
    case SX_EMAD_TR_STATE_ALLOCATED:
        return "Allocated";

    case SX_EMAD_TR_STATE_IN_TX_QUEUE:
        return "TX-Queue";

    case SX_EMAD_TR_STATE_RX_RECEIVED:
        return "Received";

    default:
        break;
    }

    return "N/A";
}

static const char * __method_to_str(sx_emad_method_e method)
{
    switch (method) {
    case EMAD_METHOD_QUERY:
        return "Query";

    case EMAD_METHOD_WRITE:
        return "Write";

    case EMAD_METHOD_SEND:
        return "Send";

    case EMAD_METHOD_EVENT:
        return "Event";

    default:
        break;
    }

    return "N/A";
}

static const char * __prio_to_str(emad_prio_e prio)
{
    switch (prio) {
    case EMAD_PRIO_HIGH:
        return "High";

    case EMAD_PRIO_LOW:
        return "Low";

    default:
        break;
    }

    return "N/A";
}

static bool __per_dev_emad_from_driver_dump(struct sx_dev *dev, void *context)
{
    struct sx_dev_db_iterator_seq_file_context *ctx = (struct sx_dev_db_iterator_seq_file_context*)context;
    struct sx_priv                             *priv = sx_priv(dev);
    struct sx_emad_transaction                 *emad_tr;
    char                                        agent[30] = { 0 };

    /* EMAD-from-driver is not supported on non-PCI (OOB) systems */
    if (!dev->pdev) {
        return true;
    }

    seq_printf(ctx->m, "EMAD from driver - Device %u\n", dev->device_id);
    sx_dbg_dump_print_empty_line(ctx->m);
    seq_printf(ctx->m, "Supports String TLV: %s\n", ((priv->emad.flags & SX_EMAD_F_STRING_TLV) ? "True" : "False"));
    seq_printf(ctx->m, "Supports Latency TLV: %s\n", ((priv->emad.flags & SX_EMAD_F_LATECNY_TLV) ? "True" : "False"));
    sx_dbg_dump_print_empty_line(ctx->m);

    seq_printf(ctx->m, "%-20s    %-18s    %-6s    %-6s    %-9s    %-8s    %-15s\n",
               "Agent", "TID", "RegId", "Method", "State", "Priority", "Msecs-In-Flight");
    sx_dbg_dump_print_separate_line(ctx->m);

    spin_lock_bh(&priv->emad.transactions_lock);
    list_for_each_entry(emad_tr, &priv->emad.transactions_list, list) {
        snprintf(agent, sizeof(agent) - 1, "%s/%u", current->comm, current->pid);
        seq_printf(ctx->m, "%-20s    0x%016llx    0x%04x    %-6s    %-9s    %-8s    %-15lu\n",
                   agent,
                   emad_tr->tid,
                   emad_tr->reg_id,
                   __method_to_str(emad_tr->method),
                   __state_to_str(emad_tr->tr_state),
                   __prio_to_str(emad_tr->priority),
                   (unsigned long)jiffies_to_msecs(jiffies - emad_tr->since));
    }
    spin_unlock_bh(&priv->emad.transactions_lock);
    return true;
}

static int __emad_from_driver_dump(struct seq_file* seq_file, void *v, void* context)
{
    struct sx_dev_db_iterator_seq_file_context ctx = {
        .m = seq_file,
        .v = v,
        .context = context
    };

    sx_dev_db_iterate(__per_dev_emad_from_driver_dump, &ctx);
    return 0;
}

int sx_emad_init(void)
{
    int err;

    __emad_transaction_cache = kmem_cache_create("emad_transaction", sizeof(struct sx_emad_transaction), 0, 0, NULL);
    if (!__emad_transaction_cache) {
        printk(KERN_ERR "failed to create EMAD transaction cache\n");
        err = -ENOMEM;
        goto out;
    }

    err = sx_dbg_dump_read_handler_register("emad_from_driver", __emad_from_driver_dump, NULL, NULL);
    if (err) {
        printk(KERN_ERR "cannot register EMAD dump handler\n");
        kmem_cache_destroy(__emad_transaction_cache);
        __emad_transaction_cache = NULL;
        goto out;
    }

out:
    return err;
}

void sx_emad_deinit(void)
{
    sx_dbg_dump_read_handler_unregister("emad_from_driver");
    if (__emad_transaction_cache) {
        kmem_cache_destroy(__emad_transaction_cache);
        __emad_transaction_cache = NULL;
    }
}
