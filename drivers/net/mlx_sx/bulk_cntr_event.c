/*
 * Copyright (c) 2010-2020,  Mellanox Technologies. All rights reserved.
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

#include <linux/skbuff.h>

#include <linux/mlx_sx/device.h>
#include <linux/mlx_sx/auto_registers/reg.h>
#include "bulk_cntr_db.h"
#include "bulk_cntr_event.h"

#define EVENT_EMAD_HDR_TID(skb) (be64_to_cpu(((struct emad_operation*)((skb)->data + sizeof(struct sx_eth_hdr)))->tid))
#define EVENT_REG_OFFSET(skb)        \
    ((skb)->data +                   \
     sizeof(struct sx_eth_hdr) +     \
     sizeof(struct emad_operation) + \
     sizeof(struct sxd_emad_tlv_reg))

typedef void (*sx_bulk_cntr_reg_parser_t)(const void                                *reg,
                                          u32                                        reg_len,
                                          struct sxd_bulk_cntr_buffer_layout_common *layout_common,
                                          void                                      *context);

int send_trap(const void    *buf,
              const uint32_t buf_size,
              uint16_t       trap_id,
              u8             is_from_user,
              u8             device_id,
              pid_t          target_pid);

/* function to parse multi-reg EMAD frame */
static void __sx_bulk_cntr_multi_emad_parse(const void               *buff,
                                            u32                       buff_len,
                                            sx_bulk_cntr_reg_parser_t reg_parser_cb,
                                            void                     *context)
{
    const struct sx_eth_hdr                   *emad_eth_header = (struct sx_eth_hdr*)buff; /* ethernet header */
    const struct sxd_emad_tlv_reg             *tlv;
    struct sxd_bulk_cntr_buffer_layout_common *layout_common;
    sxd_bulk_cntr_event_id_t                   event_id;
    u32                                        buff_remain = buff_len;
    u16                                        type, len;
    int                                        err;

    /* check that buffer is long enough */
    if (buff_len < sizeof(*emad_eth_header) + sizeof(struct emad_operation)) {
        printk(KERN_ERR "SX_BULK_CNTR: buffer is too small [buff_len=%u]\n", buff_len);
        return;
    }

    /* skip the EMAD ethernet header */
    buff_remain -= sizeof(*emad_eth_header);

    /* check that the first TLV is OPERATION_TLV and then skip it */
    tlv = (struct sxd_emad_tlv_reg*)(((u8*)buff) + sizeof(*emad_eth_header));

    type = sxd_emad_tlv_type(tlv);
    len = sxd_emad_tlv_len(tlv);

    if (type != TLV_TYPE_OPERATION_E) {
        printk(KERN_ERR "SX_BULK_CNTR: operation TLV is missing in buffer\n");
        return;
    }

    if (len != sizeof(struct emad_operation)) {
        printk(KERN_ERR "SX_BULK_CNTR: operation TLV has bad length (len=%u)\n", len);
        return;
    }

    event_id.event_id_value = cpu_to_be64(((struct emad_operation*)tlv)->tid);
    err = bulk_cntr_db_event_id_to_buffer(&event_id, &layout_common);
    if (err) {
        printk(KERN_ERR "SX_BULK_CNTR: unable to find buffer for event_id %llu\n", event_id.event_id_value);
        return;
    }

    buff_remain -= sizeof(struct emad_operation);
    tlv = (struct sxd_emad_tlv_reg*)(((u8*)tlv) + sizeof(struct emad_operation));

    /* time to parse the registers until END_TLV */
    while (buff_remain >= sizeof(*tlv)) {
        type = sxd_emad_tlv_type(tlv);
        len = sxd_emad_tlv_len(tlv);

        if ((type != TLV_TYPE_REG_E) && (type != TLV_TYPE_END_E)) {
            printk(KERN_ERR "SX_BULK_CNTR: unexpected TLV in event (type=%u)\n", type);
            break;
        }

        /* in case of END_TLV, just stop parsing */
        if (type == TLV_TYPE_END_E) {
            break;
        }

        if (len == 0) {
            printk(KERN_ERR "SX_BULK_CNTR: REG-TLV length is 0\n");
            break;
        }

        if (len > buff_remain) {
            printk(KERN_ERR "SX_BULK_CNTR: REG-TLV unexpected length (len=%u, buff_len=%u)\n", len, buff_remain);
            break;
        }

        /* call the reg-parser callback */
        reg_parser_cb(((u8*)tlv) + sizeof(struct sxd_emad_tlv_reg),
                      len - sizeof(struct sxd_emad_tlv_reg),
                      layout_common,
                      context);

        /* go to the next register in the frame */
        tlv = (struct sxd_emad_tlv_reg*)(((u8*)tlv) + len);
        buff_remain -= len;
    }

    if (type != TLV_TYPE_END_E) {
        printk(KERN_ERR "SX_BULK_CNTR: unexpected end of frame (no END_TLV)\n");
    }
}


static int __send_notification_to_user(const sxd_bulk_cntr_event_id_t  *ev_id,
                                       unsigned long                    buffer_id,
                                       enum sxd_bulk_cntr_done_status_e status)
{
    sxd_bulk_counter_done_notification_t event = {
        .status = status,
        .buffer_id = buffer_id
    };
    int                                  err;

    /* the notification will be sent ONLY to the user process that
     * initiated the transaction */
    err = send_trap(&event,
                    sizeof(event),
                    SXD_TRAP_ID_BULK_COUNTER_DONE_EVENT,
                    0,
                    1,
                    ev_id->event_id_fields.client_id);
    if (err) {
        printk(KERN_ERR "failed to send notification for bulk-counter transaction completion\n");
    }

    return err;
}


/* this function is called in cases that the driver needs ack from SDK
 * to complete a bulk-counter transaction. For example, when flow-counter
 * bulk-read is done, SDK has to unlock the range of counters before the user
 * get notified that the transaction is done.
 */
int sx_bulk_cntr_handle_ack(const sxd_bulk_cntr_event_id_t *ev_id, unsigned long buffer_id)
{
    enum sxd_bulk_cntr_done_status_e status;

    /* complete the transaction: get status and delete from DB */
    int err = bulk_cntr_db_complete(ev_id, NULL, &status);

    if (err) {
        printk(KERN_ERR "Bulk-Cntr ACK: failed to complete the transaction\n");
        goto out;
    }

    /* send notification to user upon transaction completion */
    err = __send_notification_to_user(ev_id, buffer_id, status);
    if (err) {
        printk(KERN_ERR "Bulk-Cntr SDK ack: failed to send notification to user upon transaction completion\n");
    }

out:
    return err;
}

/***************************************************************************************
 * MOCS_DONE
 */

static void __mocs_done_parser(const void                                *mocs_reg,
                               u32                                        reg_len,
                               struct sxd_bulk_cntr_buffer_layout_common *layout_common,
                               void                                      *context)
{
    sxd_bulk_cntr_event_id_t         event_id;
    unsigned long                    buffer_id;
    enum sxd_bulk_cntr_done_status_e status;
    u64                              emad_tid = *((u64*)context);
    int                              err;

    event_id.event_id_value = (((uint64_t)mlxsw_reg_mocs_hi_get(mocs_reg)) << 32) | mlxsw_reg_mocs_lo_get(mocs_reg);

    if (emad_tid != event_id.event_id_value) {
        /* according to PRM they should be equal in MOCS_DONE event */
        printk("MOCS_DONE event is corrupted: emad_tid=%llu, event_tid=%llu\n", emad_tid, event_id.event_id_value);
        return;
    }

    if (event_id.event_id_fields.type == SXD_BULK_CNTR_KEY_TYPE_FLOW_E) {
        /* we don't send the notification to user now. First, SDK has to acknowledge that
         * it has unlocked the counters. we're waiting for the ack that will be handled
         * in sx_bulk_cntr_handle_ack() */
        return;
    }

    /* complete the transaction: get status and delete from DB */
    err = bulk_cntr_db_complete(&event_id, &buffer_id, &status);
    if (err) {
        printk(KERN_ERR "failed to get transaction status on bulk-counter completion\n");
        return;
    }

    /* send notification to user upon transaction completion */
    err = __send_notification_to_user(&event_id, buffer_id, status);
    if (err) {
        printk(KERN_ERR "Bulk-Cntr FW done - failed to send notification to user upon transaction completion\n");
    }
}


void sx_bulk_cntr_handle_mocs_done(struct completion_info *ci)
{
    u64 emad_tid;

    emad_tid = EVENT_EMAD_HDR_TID(ci->skb);
    __sx_bulk_cntr_multi_emad_parse(ci->skb->data,
                                    ci->skb->len,
                                    __mocs_done_parser,
                                    &emad_tid);
}

/***************************************************************************************
 * PPCNT
 */

void sx_bulk_cntr_handle_ppcnt(struct completion_info *ci)
{
    /* not implemented yet */
}


/***************************************************************************************
 * MGPCB
 *
 *       31                       24                       16                       8                        0
 *       +------------------------+------------------------+------------------------+------------------------+
 * 000h  |                        |                            counter_index_base                            |
 *       +------------------------+------------------------+------------------------+------------------------+
 * 004h  |                                                                          |         num_rec        |
 *       +------------------------+------------------------+------------------------+------------+-----------+
 * 008h  |                                                                                       |  opcode   |
 *       +------------------------+------------------------+------------------------+------------+-----------+
 * 00ch  |                                                                                                   |
 *       +---------------------------------------------------------------------------------------------------+
 * 010h  |                                        record[0].byte_counter                                     |
 * 014h  |                                                                                                   |
 *       +---------------------------------------------------------------------------------------------------+
 * 018h  |                                        record[0].packet_counter                                   |
 * 01ch  |                                                                                                   |
 *       +---------------------------------------------------------------------------------------------------+
 *       .
 *       .
 *       .
 *       +---------------------------------------------------------------------------------------------------+
 * 400h  |                                        record[63].byte_counter                                    |
 * 404h  |                                                                                                   |
 *       +---------------------------------------------------------------------------------------------------+
 * 408h  |                                        record[63].packet_counter                                  |
 * 40ch  |                                                                                                   |
 *       +---------------------------------------------------------------------------------------------------+
 *
 */

struct mgpcb_record {
    u64 byte_counter;
    u64 packet_counter;
};
struct mgpcb_reg {
    u32                 counter_index_base;
    u32                 num_rec;
    u32                 opcode;
    u32                 reserved;
    struct mgpcb_record records[0];
};
static void __mgpcb_parser(const void                                *mgpcb_reg,
                           u32                                        reg_len,
                           struct sxd_bulk_cntr_buffer_layout_common *layout_common,
                           void                                      *context)
{
    const struct mgpcb_reg                  *mgpcb = (struct mgpcb_reg*)mgpcb_reg;
    struct sxd_bulk_cntr_buffer_layout_flow *layout_flow = (struct sxd_bulk_cntr_buffer_layout_flow*)layout_common;
    u32                                      num_rec = be32_to_cpu(mgpcb->num_rec) & 0xff;
    u32                                      expected_reg_len = sizeof(struct mgpcb_reg) + num_rec *
                                                                sizeof(struct mgpcb_record);
    u32 counter_base_index;
    u32 i, index_to_buff;

    if (reg_len < expected_reg_len) {
        printk(KERN_ERR "MGPCB parse: reg_len is less than expected len (reg_len=%u, expected=%u)\n",
               reg_len, expected_reg_len);
        return;
    }

    counter_base_index = be32_to_cpu(mgpcb->counter_index_base) & 0xffffff;
    index_to_buff = (counter_base_index - layout_flow->base_counter_id) / 2; /* counter indexes increment by 2 */

    for (i = 0; i < num_rec; i++) {
        layout_flow->counters[index_to_buff + i].flow_counter_bytes = be64_to_cpu(mgpcb->records[i].byte_counter);
        layout_flow->counters[index_to_buff + i].flow_counter_packets = be64_to_cpu(mgpcb->records[i].packet_counter);
        if (layout_common->counters_received_so_far == layout_common->num_of_counters) {
            printk(KERN_ERR "MGPCB parse: got more counters than required\n");
            break;
        }

        layout_common->counters_received_so_far++;
    }
}

void sx_bulk_cntr_handle_mgpcb(struct completion_info *ci)
{
    __sx_bulk_cntr_multi_emad_parse(ci->skb->data, ci->skb->len, __mgpcb_parser, NULL);
}


/***************************************************************************************
 * PBSR
 */

void sx_bulk_cntr_handle_pbsr(struct completion_info *ci)
{
    /* not implemented yet */
}


/***************************************************************************************
 * SBSRD
 */

void sx_bulk_cntr_handle_sbsrd(struct completion_info *ci)
{
    /* not implemented yet */
}
