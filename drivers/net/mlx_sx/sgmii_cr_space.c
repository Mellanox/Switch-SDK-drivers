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

#include <linux/module.h>

#include "sgmii_internal.h"
#include "sx.h"
#include "counter.h"

int oob_cr_command_line_mode = 1; /* default to Quantum mode */
module_param_named(oob_cr_command_line_mode, oob_cr_command_line_mode, int, 0644);
MODULE_PARM_DESC(oob_cr_command_line_mode, "0:Switch-IB/2, 1:Quantum");

#define CR_SPACE_RESPONSE_TRAP_ID1 (0x0) /* on SwitchIB/2, cr-response trap is reserved */
#define CR_SPACE_RESPONSE_TRAP_ID2 (0xf)

#define SGMII_HEADROOM                              \
    (sizeof(struct sgmii_encapsulation_header_tx) + \
     sizeof(struct sgmii_control_segment))

#define CR_SPACE_MIN_FRAME_SIZE (64) /* according to PRM */

enum sgmii_cr_space_direction {
    CR_SPACE_DIRECTION_WRITE_E,
    CR_SPACE_DIRECTION_READ_E
};
enum sgmii_cr_space_size {
    CR_SPACE_SIZE_16_BYTES,
    CR_SPACE_SIZE_4_BYTES,
    CR_SPACE_SIZE_8_BYTES,
    CR_SPACE_SIZE_12_BYTES,
    CR_SPACE_SIZE_INVALID
};
struct sgmii_cr_space_sync_context {
    struct completion             completion;
    uint8_t                       token;
    enum sgmii_cr_space_direction direction;
    uint8_t                      *user_buff;
    int                           user_buff_size;
    int                           ret_val;
};
struct sgmii_cr_space_rx_context {
    struct sk_buff *skb;
};
struct sgmii_cr_response_cqe_v0 {
    u8     version;
    u8     mac_da[3]; /* DMAC MSB */
    u8     cr_resp_token;
    u8     reserved1;
    __be16 isx_dqn5_bytecount;
    u8     oob_checks;
    u8     reserved2;
    __be16 trap_id;
    __be16 reserved3;
    u8     type_swid_crc;
    u8     e_sr_dqn_owner;
};
struct sgmii_cr_command_line_v0 { /* the mode that switch-ib/2 works */
    __be32 line0; /* token, r/w, address, size */
} __attribute__((packed));
struct sgmii_cr_command_line_v1 { /* the mode that quantum works */
    __be32 line0; /* token, r/w, reserved, size */
    __be32 line1; /* address, reserved */
} __attribute__((packed));
static struct sgmii_transaction_db __cr_space_tr_db;
static struct mutex                __cr_space_mutex;
static uint8_t                     __cr_space_token = 0;
static atomic_t                    __sgmii_cr_space_transactions_in_progress = ATOMIC_INIT(0);
static void __sgmii_fill_cr_space_control_segment(const struct isx_meta        *meta,
                                                  struct sgmii_control_segment *control_seg)
{
    SX_CORE_UNUSED_PARAM(meta);

    control_seg->line_0 = 0;
    __sgmii_bit_field_set(&control_seg->line_0,  20, 22, 0); /* swid      */
    __sgmii_bit_field_set(&control_seg->line_0,  19, 19, 0); /* ipcs      */
    __sgmii_bit_field_set(&control_seg->line_0,  18, 18, 0); /* dmc       */
    __sgmii_bit_field_set(&control_seg->line_0,  17, 17, 0); /* isx       */
    __sgmii_bit_field_set(&control_seg->line_0,  10, 16, 0); /* dr_tq     */
    __sgmii_bit_field_set(&control_seg->line_0,   7,  9, 7); /* type      */
    __sgmii_bit_field_set(&control_seg->line_0,   2,  6, 0); /* send_flow */
    __sgmii_bit_field_set(&control_seg->line_0,   0,  1, 0); /* lp        */
    CONVERT_TO_NETWORK_ORDER(control_seg->line_0);

    control_seg->line_1 = 0; /* reserved (so it should not be converted to network order) */
    control_seg->line_2 = 0; /* reserved (so it should not be converted to network order) */
    control_seg->line_3 = 0; /* reserved (so it should not be converted to network order) */
}

/* Given the request size see how many bytes we can send */
/* will need adjustments for QTM2 */
int __sgmii_get_bytes_from_size(int size)
{
    if (16 <= size) {
        /* Due to HW bug (see PRM) only do 12B
         * return CR_SPACE_SIZE_16_BYTES;
         */
        return 12;
    } else if (12 <= size) {
        return 12;
    } else if (8 <= size) {
        return 8;
    } else {
        return 4;
    }
}


static enum sgmii_cr_space_size __sgmii_get_code_from_bytes(int bytes)
{
    switch (bytes) {
    case 4:
        return CR_SPACE_SIZE_4_BYTES;

    case 8:
        return CR_SPACE_SIZE_8_BYTES;

    case 12:
        return CR_SPACE_SIZE_12_BYTES;

/*        case 16: */
/*            return CR_SPACE_SIZE_16_BYTES; */
    default:
        return CR_SPACE_SIZE_INVALID;
    }
}


static void __cr_space_work_entry_status_cb(int err, struct sgmii_transaction_info *tr_info, void *context)
{
    if (err) {
        SGMII_DEV_INC_COUNTER(tr_info->orig_tx_dev, cr_space_send_failed);
    }

    if (tr_info->send_attempts_so_far > 1) {
        SGMII_DEV_INC_COUNTER(tr_info->orig_tx_dev, cr_space_retransmission);
    }
}

static void __header_to_network_order_token_set(struct sk_buff *skb, uint8_t hdr_size, uint8_t token)
{
    if (hdr_size == 4) { /* Switch-IB/2 mode */
        struct sgmii_cr_command_line_v0 *cr_space_header = (struct sgmii_cr_command_line_v0*)skb->data;
        __sgmii_bit_field_set(&cr_space_header->line0, 24, 31, token); /* __cr_space_token    */
        CONVERT_TO_NETWORK_ORDER(cr_space_header->line0);
    } else { /* Quantum mode */
        struct sgmii_cr_command_line_v1 *cr_space_header = (struct sgmii_cr_command_line_v1*)skb->data;
        __sgmii_bit_field_set(&cr_space_header->line0, 24, 31, token); /* __cr_space_token    */
        CONVERT_TO_NETWORK_ORDER(cr_space_header->line0);
        CONVERT_TO_NETWORK_ORDER(cr_space_header->line1);
    }
}

/* fill in the SKB CR header not that this is not converting it to network order
 * need to call __header_to_network_order_token_set in order to finalize the header */
static void __fill_cr_command_line_header(struct sk_buff               *skb,
                                          uint8_t                       hdr_size,
                                          uint8_t                       token,
                                          enum sgmii_cr_space_direction dir,
                                          uint32_t                      address,
                                          enum sgmii_cr_space_size      size_code)
{
    if (hdr_size == 4) { /* Switch-IB/2 mode */
        struct sgmii_cr_command_line_v0 *cr_space_header = (struct sgmii_cr_command_line_v0*)skb->data;

        memset(cr_space_header, 0, hdr_size);

        __sgmii_bit_field_set(&cr_space_header->line0, 24, 31, token); /* __cr_space_token    */
        __sgmii_bit_field_set(&cr_space_header->line0, 23, 23, dir);              /* r/w      */

        /* 'address' and 'size' share the 2 LSB bits! first comes the address (4bit aligned) and then the size */
        __sgmii_bit_field_set(&cr_space_header->line0, 0, 22, address);           /* address  */
        __sgmii_bit_field_set(&cr_space_header->line0, 0, 1, size_code);          /* size     */
    } else { /* Quantum mode */
        struct sgmii_cr_command_line_v1 *cr_space_header = (struct sgmii_cr_command_line_v1*)skb->data;

        memset(cr_space_header, 0, hdr_size);

        __sgmii_bit_field_set(&cr_space_header->line0, 24, 31, token); /* __cr_space_token */
        __sgmii_bit_field_set(&cr_space_header->line0, 23, 23, dir);              /* r/w   */
        __sgmii_bit_field_set(&cr_space_header->line0, 0, 1, size_code);          /* size  */

        /* 'address' is assumed to have 2 LSBs equal 0. The address should be put in offset 0
         * (so the 2 'reserved' bits remain 0). */
        __sgmii_bit_field_set(&cr_space_header->line1, 0, 31, address); /* address */
    }
}

int __fill_skb(struct sk_buff              **skb,
               enum sgmii_cr_space_direction dir,
               int                           hdr_size,
               uint32_t                      address,
               void                         *buf,
               int                           bytes_to_send)
{
    int                      frame_size = 0;
    int                      cr_space_payload = 0;
    int                      padding = 0;
    uint8_t                 *cr_data = NULL;
    enum sgmii_cr_space_size size_code = CR_SPACE_SIZE_INVALID;
    struct sk_buff          *my_skb = NULL;


    /* prepare the read */
    size_code = __sgmii_get_code_from_bytes(bytes_to_send);
    if (CR_SPACE_SIZE_INVALID == size_code) {
        return -EBADRQC;
    }

    cr_space_payload = hdr_size + bytes_to_send;
    frame_size = SGMII_HEADROOM + cr_space_payload;

    if (frame_size < CR_SPACE_MIN_FRAME_SIZE) {
        padding = CR_SPACE_MIN_FRAME_SIZE - frame_size;
        frame_size = CR_SPACE_MIN_FRAME_SIZE;
    }

    /* need to allocate every time because sending deletes the SKB (might want to not do this) */
    *skb = alloc_skb(frame_size, GFP_KERNEL);
    my_skb = *skb;
    if (!my_skb) {
        return -ENOMEM;
    }
    skb_reserve(my_skb, SGMII_HEADROOM); /* puts skb->data on CR-Space payload */

    skb_put(my_skb, cr_space_payload + padding);
    __fill_cr_command_line_header(my_skb, hdr_size, __cr_space_token, dir, address, size_code);
    /* point to the "SKB cr data", 0 it for read, give the user buffer for write */
    cr_data = my_skb->data + hdr_size;
    if (dir == CR_SPACE_DIRECTION_READ_E) {
        memset(cr_data, 0, bytes_to_send); /* data is reserved */
    } else {
        memcpy(cr_data, buf, bytes_to_send);
    }

    if (padding > 0) {
        memset(cr_data + bytes_to_send, 0, padding);
    }

    return 0;
}

static int __sgmii_send_cr_space_one(struct sgmii_dev                   *sgmii_dev,
                                     struct sk_buff                     *skb,
                                     uint8_t                             hdr_size,
                                     struct sgmii_cr_space_sync_context *context)
{
    int                           ret = 0;
    struct sgmii_transaction_meta tr_meta;

    ret = mutex_lock_interruptible(&__cr_space_mutex);
    if (ret) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_interrupted);

        kfree_skb(skb);
        /* process got interrupted, get out of here ... */
        return ret;
    }

    __header_to_network_order_token_set(skb, hdr_size, __cr_space_token);
    context->token = __cr_space_token;
    init_completion(&(context->completion));
    /* set the transaction meta data
     * only the token == id is required in the lock but no real performance issue with setting all */
    tr_meta.skb = skb;
    tr_meta.tr_db = &__cr_space_tr_db;
    tr_meta.tr_id = __cr_space_token;
    tr_meta.transport_type = SXD_COMMAND_TYPE_CR_ACCESS;

    /* sending CR access transaction. skb will be freed in this way or another by the transaction system */
    ret = sgmii_send_transaction(&tr_meta, sgmii_dev, NULL, context);
    if (ret) {
        /* skb is already deleted in this point */
        SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_transaction_init_failed);
        goto out;
    }

    atomic_inc(&__sgmii_cr_space_transactions_in_progress);

    do {
        ret = wait_for_completion_interruptible(&(context->completion));
    } while (ret == -ERESTARTSYS);

    ret = context->ret_val;
    __cr_space_token++;

out:
    mutex_unlock(&__cr_space_mutex);
    return ret;
}

static int __sgmii_send_cr_space(struct sgmii_dev             *sgmii_dev,
                                 uint32_t                      address,
                                 void                         *buf,
                                 int                           size,
                                 enum sgmii_cr_space_direction dir)
{
    struct sk_buff                    *skb;
    int                                ret = 0;
    int                                cr_cmd_line_hdr_size = 0;
    int                                bytes_to_send = 0;
    int                                tmp_size = size; /* define the size we will "eat out of" */
    void                              *tmp_buf = buf; /* we are going to "move" the pointer */
    uint32_t                           tmp_address = address;
    struct sgmii_cr_space_sync_context context = {
        .direction = dir,
        .user_buff = buf,
        .user_buff_size = size,
        .ret_val = -EIO
    };

    /* want to get the value of 'oob_cr_command_line_mode' only once per function call and use a local variable
     * to avoid situations where this parameter is changed in the middle of the function call ...
     */
    cr_cmd_line_hdr_size = (oob_cr_command_line_mode == 0) ? 4 /* Switch-IB/2 mode */ : 8 /* Quantum mode */;

    while (tmp_size > 0) {
        bytes_to_send = __sgmii_get_bytes_from_size(tmp_size);
        ret = __fill_skb(&skb, dir, cr_cmd_line_hdr_size,
                         tmp_address, tmp_buf, bytes_to_send);
        if (ret) {
            SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_skb_alloc_failed);
            printk(KERN_ERR "failed SKB creation to read CR address:[0x%x] error:[%d]\n",
                   tmp_address, ret);
            goto out;
        }
        context.direction = dir;
        context.user_buff = tmp_buf;
        context.user_buff_size = bytes_to_send;
        context.ret_val = -EIO;

        /* do one sync read */
        ret = __sgmii_send_cr_space_one(sgmii_dev, skb, cr_cmd_line_hdr_size, &context);
        if (ret) {
            printk(
                KERN_ERR "failed sending CR address:[0x%x] bytes:[%d] out of remaining request size:[%d] error:[%d]\n",
                tmp_address,
                bytes_to_send,
                tmp_size,
                ret);
            goto out;
        }
        /* move to the next bytes to read */
        tmp_size = tmp_size - bytes_to_send;
        tmp_buf = tmp_buf + bytes_to_send; /* read into the next available location */
        tmp_address = tmp_address + bytes_to_send; /* read from the next address */
    }

out:
    return ret;
}


int sgmii_send_cr_space_read(int dev_id, uint32_t address, void *buf, int size)
{
    struct sgmii_dev *sgmii_dev;
    int               ret;

    ret = sgmii_dev_get_by_id(dev_id, &sgmii_dev);
    if (ret) {
        return ret;
    }

    SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_read);

    ret = __sgmii_send_cr_space(sgmii_dev, address, buf, size, CR_SPACE_DIRECTION_READ_E);
    if (ret == -ETIMEDOUT) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_timeout);
    } else if (ret == -EINVAL) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_transaction_init_failed);
    }

    sgmii_dev_dec_ref(sgmii_dev);
    return ret;
}


int sgmii_send_cr_space_write(int dev_id, uint32_t address, void *buf, int size)
{
    struct sgmii_dev *sgmii_dev;
    int               ret;

    ret = sgmii_dev_get_by_id(dev_id, &sgmii_dev);
    if (ret) {
        return ret;
    }

    SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_write);

    ret = __sgmii_send_cr_space(sgmii_dev, address, buf, size, CR_SPACE_DIRECTION_WRITE_E);
    if (ret == -ETIMEDOUT) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_timeout);
    } else if (ret == -EINVAL) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_transaction_init_failed);
    }

    sgmii_dev_dec_ref(sgmii_dev);
    return ret;
}


/* returns 0 if packet is NOT CR response. returns 1 if packet is CR response */
uint8_t sgmii_cr_space_check_for_response(struct sgmii_dev *sgmii_dev, struct sk_buff *skb)
{
    const struct sgmii_cr_response_cqe_v0 *cr_resp_cqe_v0;
    uint16_t                               trap_id;

    if (!pskb_may_pull(skb, sizeof(struct sgmii_cr_response_cqe_v0))) {
        return 0;
    }

    cr_resp_cqe_v0 = (struct sgmii_cr_response_cqe_v0*)skb->data;
    if (((cr_resp_cqe_v0->type_swid_crc >> 5) & 0x7) != PKT_TYPE_OOB_CR_RESP) {
        return 0;
    }

    if (cr_resp_cqe_v0->oob_checks & 0xf) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_invalid_oob_checks);
        goto out;
    }

    trap_id = ntohs(cr_resp_cqe_v0->trap_id) & 0x1ff;

/* ******* UN-COMMENT THESE LINES WHEN HW IS READY WITH VALID TRAP IDs !!!
 *   if (trap_id != CR_SPACE_RESPONSE_TRAP_ID1 && trap_id != CR_SPACE_RESPONSE_TRAP_ID2) {
 *       SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_invalid_trap_id);
 *       goto out;
 *   }
 */

    if (((cr_resp_cqe_v0->type_swid_crc >> 1) & 0x7) != 0) { /* swid must be 0 */
        SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_misc_failed);
        goto out;
    }

    if (((cr_resp_cqe_v0->e_sr_dqn_owner >> 6) & 0x1) != 0) { /* sr must be 0 */
        SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_misc_failed);
        goto out;
    }

    skb_pull(skb, sizeof(struct sgmii_cr_response_cqe_v0));

    SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_rx);

    if (sgmii_transaction_check_completion(&__cr_space_tr_db,
                                           skb,
                                           cr_resp_cqe_v0->cr_resp_token,
                                           sgmii_dev) == 0) {
        /* incoming packet did not complete a CR-Space transaction ... */
        SGMII_DEV_INC_COUNTER(sgmii_dev, cr_space_unsolicited);
    }

out:
    return 1;
}


static void __sgmii_cr_space_transaction_completion(struct sk_buff                          *rx_skb,
                                                    enum sgmii_transaction_completion_status status,
                                                    struct sgmii_transaction_info           *tr_info,
                                                    void                                    *context)
{
    struct sgmii_cr_space_sync_context *tx_ctx = (struct sgmii_cr_space_sync_context*)context;

    switch (status) {
    case SGMII_TR_COMP_ST_COMPLETED:
        if (!pskb_may_pull(rx_skb, tx_ctx->user_buff_size)) {
            SGMII_DEV_INC_COUNTER(tr_info->orig_tx_dev, cr_space_snipped_data);
        } else {
            SGMII_DEV_INC_COUNTER(tr_info->orig_tx_dev, cr_space_transaction_completed);
        }

        if (tx_ctx->direction == CR_SPACE_DIRECTION_READ_E) {
            memcpy(tx_ctx->user_buff, rx_skb->data, tx_ctx->user_buff_size);
        }

        tx_ctx->ret_val = 0;
        break;

    case SGMII_TR_COMP_ST_RX_DEV_MISMATCH:
        tx_ctx->ret_val = -EPERM;
        break;

    case SGMII_TR_COMP_ST_TIMEDOUT:
        tx_ctx->ret_val = -ETIMEDOUT;
        break;
    }

    complete(&tx_ctx->completion);
    atomic_dec(&__sgmii_cr_space_transactions_in_progress);
}


int sgmii_cr_space_get_transactions_in_progress(void)
{
    return atomic_read(&__sgmii_cr_space_transactions_in_progress);
}


int sgmii_cr_space_init(void)
{
    int ret;

    ret = sgmii_transaction_db_init(&__cr_space_tr_db,
                                    __sgmii_fill_cr_space_control_segment,
                                    NULL,
                                    __cr_space_work_entry_status_cb,
                                    __sgmii_cr_space_transaction_completion);
    if (ret) {
        printk(KERN_ERR "failed to create cr-space transaction db (ret=%d)\n", ret);
        return ret;
    }

    mutex_init(&__cr_space_mutex);
    return 0;
}


void sgmii_cr_space_deinit(void)
{
}
