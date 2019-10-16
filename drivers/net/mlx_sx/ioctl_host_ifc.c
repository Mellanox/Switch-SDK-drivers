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

#include <linux/fs.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>

#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/kernel_user.h>
#include "sx.h"
#include "cq.h"
#include "dq.h"
#include "alloc.h"
#include "ioctl_internal.h"

#include "trace.h"

extern int enable_monitor_rdq_trace_points;

/*
 * This define is used to limit the maximum number of the entries in the SW
 * buffer (list) which is used to store the discarded packets which were matched
 * to specific drop reason which was registered for monitor trap group (WJH) and
 * considered by NOS (trap double registration).
 * Appropriate buffer should behave as head drop queue, so if number of elements
 * in the queue is more that 1024 head element will be dropped and new entry will
 * be pushed to the tail.
 */
#define SX_SW_EVENT_LIST_SIZE_MAX 1024


/**
 * This function is used to prepare required parameters for
 * managing (adding/removing) hardware syndrom. For example it
 * converts L2 listener type from value which was specified by
 * user to value which is suitable for driver.
 *
 * @param[in]  type            - value to convert
 * @param[out] listener_type_p - listener type value to use
 *
 * @return 0      - if operation completes successfully
 * @return EINVAL - if any input parameters is invalid
 */
static int sx_core_ioctl_synd_param_prepare(const enum ku_l2_type type, enum l2_type *listener_type_p)
{
    int err = 0;

    switch (type) {
    case SX_KU_L2_TYPE_DONT_CARE:
        *listener_type_p = L2_TYPE_DONT_CARE;
        break;

    case SX_KU_L2_TYPE_IB:
        *listener_type_p = L2_TYPE_IB;
        break;

    case SX_KU_L2_TYPE_ETH:
        *listener_type_p = L2_TYPE_ETH;
        break;

    case SX_KU_L2_TYPE_FC:
        *listener_type_p = L2_TYPE_FC;
        break;

    default:
        printk(KERN_ERR PFX "Err: invalid listener type : %d \n", type);
        err = -EINVAL;
        goto out;
    }

out:
    return err;
}


/**
 * This handler should be used only for Monitor RDQ in case of
 * HW syndrome was associated with two different trap groups
 * (RDQs), one - regular RDQ, and second - monitor RDQ.
 * This handler will store discarded packets to the SW buffer of
 * monitor RDQ and support trap double registration
 */
static void sx_cq_monitor_sw_queue_handler(struct completion_info *comp_info, void *context)
{
    unsigned long      flags;
    struct event_data *edata = NULL;
    struct sx_rsc     *file = ((struct file *)(context))->private_data;
    struct sx_dev     *sx_dev = comp_info->dev;
    struct sk_buff    *skb = comp_info->skb;
    struct event_data *head_edata_p = NULL;

    skb_get(skb);
    edata = kmalloc(sizeof(*edata), GFP_ATOMIC);
    if (edata == NULL) {
        if (sx_dev && !sx_dev->eventlist_drops_counter) {
            printk(KERN_WARNING PFX "Memory allocation "
                   "for event data failed, "
                   "dropping RX packet\n");
        }
        inc_eventlist_drops_counter(sx_dev, comp_info->hw_synd);
        goto out_free;
    }

    /* update edata params - prepare edata according to the retrieved Completion Info */
    sx_cq_handle_event_data_prepare(edata, skb, comp_info);

    spin_lock_irqsave(&file->lock, flags);

    /* monitor packet handling - case of trap double registration */
    if (file->bound_monitor_rdq->sw_dup_evlist_cnt == SX_SW_EVENT_LIST_SIZE_MAX) {
        /* if number of entries equals to the max - remove element from head */

        head_edata_p = list_first_entry(&file->bound_monitor_rdq->sw_dup_evlist_p->list, struct event_data, list);
        list_del(&head_edata_p->list);

        kfree_skb(head_edata_p->skb);
        kfree(head_edata_p);

        file->bound_monitor_rdq->sw_dup_evlist_cnt--;
    }

    /* Make sure that for WJH we will be able to see timestamp for this packet (if it was enabled there) */
    if (sx_bitmap_test(&sx_priv(sx_dev)->cq_table.ts_bitmap, file->bound_monitor_rdq->cq->cqn)) {
        edata->has_timestamp = true;
        getnstimeofday(&edata->timestamp);
    } else {
        edata->has_timestamp = false;
    }

    if (enable_monitor_rdq_trace_points) {
        if (edata->has_timestamp) {
            trace_monitor_rdq_rx(skb, comp_info->hw_synd, &edata->timestamp);
        } else {
            trace_monitor_rdq_rx(skb, comp_info->hw_synd, NULL);
        }
    }

    list_add_tail(&edata->list, &file->bound_monitor_rdq->sw_dup_evlist_p->list);
    file->bound_monitor_rdq->sw_dup_evlist_cnt++;
    file->bound_monitor_rdq->sw_dup_evlist_total_cnt++;

    wake_up_interruptible(&file->poll_wait);
    spin_unlock_irqrestore(&file->lock, flags);
    goto out_ok;

out_free:
    kfree_skb(skb);
    kfree(edata);
out_ok:
    return;
}


/**
 * This function is used to check the validity of the given ku
 *
 * param[in] ku_synd_ioctl - The given ku
 *
 * returns: 0 success
 *	   !0 error
 */
int check_valid_ku_synd(struct ku_synd_ioctl *ku)
{
    int err = 0;

    if ((ku->is_default != false) && (ku->is_default != true)) {
        err = -EINVAL;
#ifdef SX_DEBUG
        printk(KERN_DEBUG PFX "The given ku_synd_ioctl not valid: "
               " ku->is_default=[%d]\n", ku->is_default);
#endif
    }

    if ((ku->swid >= NUMBER_OF_SWIDS) && (ku->swid != SWID_NUM_DONT_CARE)) {
        err = -EINVAL;
#ifdef SX_DEBUG
        printk(KERN_DEBUG PFX "The given ku_synd_ioctl not valid: "
               " ku->swid=[%d]\n", ku->swid);
#endif
    }

    if (ku->syndrome_num > NUM_HW_SYNDROMES) {
        err = -EINVAL;
#ifdef SX_DEBUG
        printk(KERN_DEBUG PFX "The given ku_synd_ioctl not valid: "
               " ku->syndrome_num=[%d]\n", ku->syndrome_num);
#endif
    }

    return err;
}


static int sx_core_remove_synd_phy(u8                          swid,
                                   u16                         hw_synd,
                                   struct sx_dev              *dev,
                                   struct ku_port_vlan_params *port_vlan_params)
{
    union sx_event_data *event_data;

    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        return -ENOMEM;
    }

    event_data->eth_l3_synd.swid = swid;
    event_data->eth_l3_synd.hw_synd = hw_synd;
    switch (port_vlan_params->port_vlan_type) {
    case KU_PORT_VLAN_PARAMS_TYPE_GLOBAL:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_GLOBAL;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_PORT:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_PORT;
        event_data->eth_l3_synd.port = port_vlan_params->sysport;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_LAG:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_LAG;
        event_data->eth_l3_synd.port = port_vlan_params->lag_id;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_VLAN:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_VLAN;
        event_data->eth_l3_synd.vlan = port_vlan_params->vlan;
        break;
    }

    sx_core_dispatch_event(dev, SX_DEV_EVENT_REMOVE_SYND_PHY_NETDEV, event_data);
    kfree(event_data);

    return 0;
}


int sx_core_remove_synd_l2(u8 swid, u16 hw_synd, struct sx_dev *dev, struct ku_port_vlan_params *port_vlan_params)
{
    union sx_event_data *event_data;

    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        return -ENOMEM;
    }

    event_data->eth_l3_synd.swid = swid;
    event_data->eth_l3_synd.hw_synd = hw_synd;
    switch (port_vlan_params->port_vlan_type) {
    case KU_PORT_VLAN_PARAMS_TYPE_GLOBAL:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_GLOBAL;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_PORT:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_PORT;
        event_data->eth_l3_synd.port = port_vlan_params->sysport;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_LAG:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_LAG;
        event_data->eth_l3_synd.port = port_vlan_params->lag_id;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_VLAN:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_VLAN;
        event_data->eth_l3_synd.vlan = port_vlan_params->vlan;
        break;
    }

    sx_core_dispatch_event(dev, SX_DEV_EVENT_REMOVE_SYND_L2_NETDEV, event_data);
    kfree(event_data);

    return 0;
}


int sx_core_remove_synd_l3(u8 swid, u16 hw_synd, struct sx_dev *dev, struct ku_port_vlan_params *port_vlan_params)
{
    union sx_event_data *event_data;

    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        return -ENOMEM;
    }

    event_data->eth_l3_synd.swid = swid;
    event_data->eth_l3_synd.hw_synd = hw_synd;
    switch (port_vlan_params->port_vlan_type) {
    case KU_PORT_VLAN_PARAMS_TYPE_GLOBAL:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_GLOBAL;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_PORT:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_PORT;
        event_data->eth_l3_synd.port = port_vlan_params->sysport;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_LAG:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_LAG;
        event_data->eth_l3_synd.port = port_vlan_params->lag_id;
        break;

    case KU_PORT_VLAN_PARAMS_TYPE_VLAN:
        event_data->eth_l3_synd.type = L3_SYND_TYPE_VLAN;
        event_data->eth_l3_synd.vlan = port_vlan_params->vlan;
        break;
    }

    sx_core_dispatch_event(dev, SX_DEV_EVENT_REMOVE_SYND_NETDEV, event_data);
    kfree(event_data);

    return 0;
}


static int sx_core_add_synd_ipoib(u8 swid, u16 hw_synd, struct sx_dev *dev)
{
    union sx_event_data *event_data;

    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        return -ENOMEM;
    }

    event_data->ipoib_synd.swid = swid;
    event_data->ipoib_synd.hw_synd = hw_synd;
    sx_core_dispatch_event(dev, SX_DEV_EVENT_ADD_SYND_IPOIB, event_data);
    kfree(event_data);

    return 0;
}

static int sx_core_remove_synd_ipoib(u8 swid, u16 hw_synd, struct sx_dev *dev)
{
    union sx_event_data *event_data;

    event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!event_data) {
        return -ENOMEM;
    }

    event_data->ipoib_synd.swid = swid;
    event_data->ipoib_synd.hw_synd = hw_synd;
    sx_core_dispatch_event(dev, SX_DEV_EVENT_REMOVE_SYND_IPOIB, event_data);
    kfree(event_data);

    return 0;
}


static uint32_t sx_monitor_count_get(struct sx_dq *bound_monitor_rdq)
{
    uint32_t mon_rx_count;

    mon_rx_count = bound_monitor_rdq->mon_rx_count - bound_monitor_rdq->mon_rx_start;

    /* take also counter of discarded packets which we have in the SW buffer  */
    mon_rx_count += bound_monitor_rdq->sw_dup_evlist_cnt;

    return mon_rx_count;
}


static void sx_cq_handler(struct completion_info *comp_info, void *context)
{
    unsigned long      flags;
    struct event_data *edata = NULL;
    struct sx_rsc     *file = ((struct file *)(context))->private_data;
    struct sx_dev     *sx_dev = comp_info->dev;
    struct sk_buff    *skb = comp_info->skb;

    skb_get(skb);
    edata = kmalloc(sizeof(*edata), GFP_ATOMIC);
    if (edata == NULL) {
        if (sx_dev && !sx_dev->eventlist_drops_counter) {
            printk(KERN_WARNING PFX "Memory allocation "
                   "for event data failed, "
                   "dropping RX packet\n");
        }
        inc_eventlist_drops_counter(sx_dev, comp_info->hw_synd);
        goto out_free;
    }

    /* update edata params - prepare edata according to the retrieved Completion Info */
    sx_cq_handle_event_data_prepare(edata, skb, comp_info);

    spin_lock_irqsave(&file->lock, flags);

    if (file->evlist_size < SX_EVENT_LIST_SIZE) {
        list_add_tail(&edata->list, &file->evlist.list);
        file->evlist_size++;
        wake_up_interruptible(&file->poll_wait);
        spin_unlock_irqrestore(&file->lock, flags);
        goto out_ok;
    }

    spin_unlock_irqrestore(&file->lock, flags);

    if ((sx_dev != NULL) && (!sx_dev->eventlist_drops_counter)) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "Event list is full, dropping RX packet (trap_id=%u)\n", comp_info->hw_synd);
        }
    }
    inc_eventlist_drops_counter(sx_dev, comp_info->hw_synd);

out_free:
    kfree_skb(skb);
    kfree(edata);
out_ok:
    return;
}


static int sx_monitor_simulate_rx_skb(struct sx_dq          *bound_monitor_rdq,
                                      size_t                 buffers_count,
                                      size_t                *buf_len_list,
                                      size_t                *total_packet_cnt_p,
                                      struct listener_entry *force_listener)
{
    int              err = 0;
    struct sx_cq    *cq = bound_monitor_rdq->cq;
    struct sx_priv  *priv = sx_priv(cq->sx_dev);
    uint32_t         mon_rx_count = bound_monitor_rdq->mon_rx_count;
    uint32_t         mon_rx_start = bound_monitor_rdq->mon_rx_start;
    uint32_t         i, idx;
    struct sk_buff * skb;
    union sx_cqe     u_cqe;
    struct timespec* timestamp = NULL;
    u8               dqn = 0;
    u8               is_send = 0;
    u8               is_err = 0;
    u16              trap_id = 0;
    u16              byte_count = 0;
    u16              wqe_counter = 0;
    struct sx_dq    *dq;
    uint32_t         packets_sent_to_fd_count = 0;
    uint32_t         packets_sent_to_fd_total_size = 0;

    mon_rx_start = bound_monitor_rdq->mon_rx_start;
    mon_rx_count = bound_monitor_rdq->mon_rx_count - bound_monitor_rdq->mon_rx_start;

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX "Debug mon_rx_count:%d , mon_rx_start:%d, mon_rx_count_total:%d, buffers_count: %d \n",
           mon_rx_count, mon_rx_start, bound_monitor_rdq->mon_rx_count, (int)buffers_count);
#endif

    for (i = 0; i < mon_rx_count && i < buffers_count; /* i incremented inside loop */) {
        /* get the cqe from CQ by index */
        sx_get_cqe_all_versions(cq, (mon_rx_start + i), &u_cqe);

        if (u_cqe.v2 == NULL) {
#ifdef SX_DEBUG
            printk(
                KERN_DEBUG PFX "%s():%d u_cqe_v2 == NULL, rx_start:%d, i:%d, start+i:%d, rx_cnt:%d,r:tc:c:%d:%d:%d\n",
                __func__,
                __LINE__,
                mon_rx_start,
                i,
                (mon_rx_start + i),
                mon_rx_count,
                bound_monitor_rdq->mon_rx_start,
                bound_monitor_rdq->mon_rx_count,
                bound_monitor_rdq->mon_rx_count - bound_monitor_rdq->mon_rx_start);
#endif

            i++;
            continue;
        }

        /* extract cqe from cq */
        cq->sx_fill_poll_one_params_from_cqe_cb(&u_cqe, &trap_id, &is_err,
                                                &is_send, &dqn, &wqe_counter, &byte_count);

        if (is_send) {
            printk(KERN_ERR "%s(): Error SDQ %d was provided when only RDQ is supported.\n",
                   __func__, dqn);
            err = -EINVAL;
            goto out;
        }

        /* ETH packet always contains CRC. Driver doesn't copy the CRC to the user ,
         * so we need to remove it from byte_count */
        byte_count -= ETH_CRC_LENGTH;

        /*
         * Calculate if there enough space in the buffer for the packet
         * Need to verify that there is enough space for ku_read , packet , last ku_read
         */
        if (byte_count + sizeof(struct ku_read) > buf_len_list[i]) {
            /* There isn't enough space to this packet */
            printk(KERN_ERR "%s(): i=%d , not enough space %d for packet size %d \n",
                   __func__, i, (int)buf_len_list[i], (int)(byte_count + sizeof(struct ku_read)));
            goto out;
        }

#ifdef SX_DEBUG
        printk(KERN_DEBUG PFX "%s(): i=%d , packet size:%d , buffer_size:%d \n",
               __func__, i, (int)(byte_count + sizeof(struct ku_read)), (int)buf_len_list[i]);
#endif

        dq = priv->rdq_table.dq[dqn];
        if (!dq) {
            if (printk_ratelimit()) {
                sx_warn(cq->sx_dev, "could not find dq context for %s "
                        "dqn = %d\n",
                        is_send ? "send" : "recv", dqn);
            }
            goto out;
        }
        idx = (mon_rx_start + i) % dq->wqe_cnt;

        skb = dq->sge[idx].skb;
        if (sx_bitmap_test(&priv->cq_table.ts_bitmap, cq->cqn)) {
            timestamp = &cq->cqe_ts_arr[idx];
        }
        err = rx_skb(cq->sx_dev, skb, &u_cqe, timestamp, 1, force_listener);
        if (err) {
            printk(KERN_WARNING PFX "rx_skb error %d . Aborting\n", err);
            goto out;
        }

        /* after reading from the buffer we need to invalidate this buffer
         * so next read will bring to cache new data from memory */
        pci_dma_sync_single_for_device(dq->dev->pdev,
                                       dq->sge[idx].hdr_pld_sg.dma_addr,
                                       dq->sge[idx].hdr_pld_sg.len, DMA_FROM_DEVICE);


        packets_sent_to_fd_total_size += byte_count + sizeof(struct ku_read);
        packets_sent_to_fd_count++;
        i++;
    }

    /* update mon_start */
    bound_monitor_rdq->mon_rx_start += packets_sent_to_fd_count;
    *total_packet_cnt_p = packets_sent_to_fd_count;

out:
    return err;
}


static int sx_trap_group_path_set(struct sx_dq *bound_monitor_rdq, uint8_t cpu_path_type)
{
    int                       err;
    struct ku_access_htgt_reg reg_data;
    struct sx_dev            *dev = bound_monitor_rdq->dev;

    /* Read the current HTGT value (to get policer ID if any) */
    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.dev_id = 255;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, HTGT_REG_ID, 1); /* 1 - query */
    reg_data.htgt_reg.swid = 0;
    reg_data.htgt_reg.trap_group = bound_monitor_rdq->dqn;
    err = sx_ACCESS_REG_HTGT(dev, &reg_data);
    if (err) {
        printk(KERN_ERR PFX "failed to disconnect trap group %d \n", reg_data.htgt_reg.trap_group);
        goto out;
    }

    /* Stop the RDQ */
    sx_cmd_set_op_tlv(&reg_data.op_tlv, HTGT_REG_ID, 2); /* 2 - write */
    switch (cpu_path_type) {
    case HTGT_NULL_PATH:
        reg_data.htgt_reg.type = HTGT_NULL_PATH;
        reg_data.htgt_reg.trap_group = bound_monitor_rdq->dqn;
        break;

    case HTGT_LOCAL_PATH:
        reg_data.htgt_reg.type = HTGT_LOCAL_PATH;
        reg_data.htgt_reg.trap_group = bound_monitor_rdq->dqn; /* trap group num = dqn */
        reg_data.htgt_reg.path.local_path.rdq = bound_monitor_rdq->dqn;
        reg_data.htgt_reg.path.local_path.cpu_tclass = bound_monitor_rdq->cpu_tclass;
        break;

    default:
        printk(KERN_ERR PFX "invalid path type %d \n", cpu_path_type);
        err = -EINVAL;
        goto out;
    }
    err = sx_ACCESS_REG_HTGT(dev, &reg_data);
    if (err) {
        printk(KERN_ERR PFX "failed to disconnect trap group %d \n", reg_data.htgt_reg.trap_group);
        goto out;
    }

out:
    return err;
}


/**
 * Get edata which is the packet parameters and a copy it to local buffer.
 *
 * param[in] buf   - The place the meta-data + packet should be copied to
 * param[in] edata - The packet and meta-data parameters
 *
 * returns: positive number on success (the copied size of meta-data + packet)
 *	    !0 error
 */
static int copy_pkt(char *buf, struct event_data *edata)
{
    struct ku_read metadata;
    int            copied_size = 0;

    memset(&metadata, 0, sizeof(metadata));

    sx_copy_pkt_metadata_prepare(&metadata, edata);

    memcpy(buf, &metadata, sizeof(metadata));
    copied_size += sizeof(metadata);

    memcpy(buf + copied_size, edata->skb->data, edata->skb->len);
    copied_size += edata->skb->len;
#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX "copy_pkt() metadata.length=[%llu] " \
           "metadata.system_port=[%d] metadata.trap_id=[%d]\n",
           metadata.length, metadata.system_port,
           metadata.trap_id);
    SX_CORE_HEXDUMP16((void*)&metadata, sizeof(metadata));
    SX_CORE_HEXDUMP16(edata->skb->data, edata->skb->len);
#endif

    return copied_size;
}


/**
 *
 * Copy the edata that holds packet/s to the given buf
 * NOTE:
 *  1. The function assumes that there is enough free space in
 * the buffer (which was already checked before calling here)
 *  2. in this function used local buffer, not buffer which was
 *  specified by user
 *
 * param[in] edata - The packet and meta-data parameters
 * param[in] buf   - the data buffer, ku_read struct
 *
 * returns: The size of data which copied to the user buffer
 *	   !0 error
 */
static int copy_edata(struct event_data *edata, char *buf)
{
    struct event_data *tmp = NULL;
    int                so_far_copied = 0;
    int                copied_size = 0;
    int                err = 0;
    struct list_head  *pos, *q;
    struct sx_dev    * sx_dev = NULL;

    list_for_each_safe(pos, q, &edata->list) {
        tmp = list_entry(pos, struct event_data, list);

        copied_size = copy_pkt(buf + so_far_copied, tmp);
        if (copied_size == 0) {
            err = -EFAULT;
            goto out_free;
        }

        so_far_copied += copied_size;
        list_del(pos);
        kfree_skb(tmp->skb);
        kfree(tmp);
    }

    return so_far_copied;

out_free:
    list_for_each_safe(pos, q, &edata->list) {
        tmp = list_entry(pos, struct event_data, list);
        sx_dev = tmp->dev;
        if (sx_dev && !sx_dev->eventlist_drops_counter) {
            printk(KERN_WARNING PFX
                   "copy_pkt_to_user failed, " \
                   "dropping RX packet\n");
        }

        inc_eventlist_drops_counter(sx_dev, tmp->trap_id);
        list_del(pos);
        kfree_skb(tmp->skb);
        kfree(tmp);
    }

    return so_far_copied ? so_far_copied : err;
}


/**
 * This function read the data from the specified list_p and put
 * it according to the start and end indexes in correct position
 * of user_buffer_list which will be send to the user.
 * Note that this function is used for data lists which are used
 * for regular RDQ and for monitor SW queue
 */
static int __monitor_buff_data_handle(struct list_head *list_p,
                                      int              *list_size_p,
                                      uint8_t __user  **user_buffer_list_p,
                                      size_t           *user_buffer_size_list_p,
                                      size_t            start_idx,
                                      size_t            end_idx,
                                      size_t            user_requested_num)
{
    int               err = 0;
    int               copied_size = 0;
    struct event_data edata_list;
    size_t            i = 0;

    INIT_LIST_HEAD(&edata_list.list);

    for (i = start_idx; i < end_idx && i < user_requested_num; i++) {
        err = get_edata_from_elist(list_size_p, &edata_list,
                                   list_p, user_buffer_size_list_p[i], false);
        if (err) {
            printk(KERN_ERR "%s(): get_edata_from_elist buf_len:%d err: %d \n",
                   __func__, (int)user_buffer_size_list_p[i], err);
            goto out;
        }

        copied_size = copy_edata(&edata_list, user_buffer_list_p[i]);
        if (copied_size < 0) {
            err = copied_size;
            printk(KERN_ERR "%s(): copy_edata failed. err: %d \n",
                   __func__, err);
            goto out;
        }

        user_buffer_size_list_p[i] = copied_size;
    }

out:
    return err;
}


static ssize_t __monitor_file_read(struct file     *filp,
                                   enum SX_FILE_OP  file_op,
                                   int             *buffers_count_p,
                                   uint8_t __user **buffer_list_p,
                                   size_t          *buffer_size_list_p)
{
    unsigned long         flags;
    struct sx_rsc        *file = filp->private_data;
    int                   err = 0;
    size_t                total_packets_cnt = 0;
    size_t                sw_total_packets_cnt = 0;
    size_t                buffers_count = 0;
    struct listener_entry force_listener;
    uint8_t             **tmp_buff_pp = NULL;
    size_t                i = 0, j = 0;
    uint8_t               release_tmp_buff = false;

    if ((buffers_count_p == NULL) && (file_op != SX_FILE_OP_FLUSH)) {
        printk(KERN_ERR "%s(): buffers_count_p is  NULL \n", __func__);
        return -EINVAL;
    }
    buffers_count = *buffers_count_p;

    if (file_op == SX_FILE_OP_COUNT) {
        *buffers_count_p = sx_monitor_count_get(file->bound_monitor_rdq);
        goto out;
    }

    if (file_op == SX_FILE_OP_FLUSH) {
        sx_monitor_flush(file, file->bound_monitor_rdq);
        goto out;
    }

    force_listener.context = filp;
    force_listener.handler = sx_cq_handler;

    /* The next flow is for multi packet reading */
    if ((buffers_count == 0) || (buffer_list_p == NULL) || (buffer_size_list_p == NULL)) {
        return -EINVAL;
    }

    /* disconnect trap group from rdq */
    err = sx_trap_group_path_set(file->bound_monitor_rdq, HTGT_NULL_PATH);
    if (err) {
        printk(KERN_ERR "%s(): disconnect rdq %d from TG failed. err: %d \n",
               __func__, file->bound_monitor_rdq->dqn, err);
        goto out;
    }

    err = sx_monitor_simulate_rx_skb(file->bound_monitor_rdq,
                                     buffers_count,
                                     buffer_size_list_p,
                                     &total_packets_cnt, &force_listener);
    if (err) {
        printk(KERN_ERR "%s(): simulate_monitor_data_rx_skb for rdq %d failed. err: %d \n",
               __func__, file->bound_monitor_rdq->dqn, err);
        goto out;
    }

    /* store the number of packets in SW buffer */
    sw_total_packets_cnt = file->bound_monitor_rdq->sw_dup_evlist_cnt;

    tmp_buff_pp = (uint8_t**)kzalloc(buffers_count * sizeof(uint8_t *), GFP_KERNEL);
    if (tmp_buff_pp == NULL) {
        printk(KERN_ERR " Failed to allocate memory for local buffer tmp_buff_pp. \n");
        err = -ENOMEM;
        goto out;
    }

    for (i = 0; i < buffers_count; i++) {
        tmp_buff_pp[i] = (uint8_t*)kzalloc(buffer_size_list_p[i], GFP_KERNEL);
        if (tmp_buff_pp[i] == NULL) {
            printk(KERN_ERR " Failed to allocate memory for local buffer tmp_buff_pp, index=%zu. \n", i);

            /* release those indexes which were already allocated */
            for (j = i - 1; j >= 0; j--) {
                kfree(tmp_buff_pp[j]);
            }
            kfree(tmp_buff_pp);
            err = -ENOMEM;
            goto out;
        }
    }
    release_tmp_buff = true;

    spin_lock_irqsave(&file->lock, flags);

    /*
     * Read the data from the specified evlist which belongs to HW cyclic RDQ and
     * put this data to the buffer list according to the specified indexes
     */
    err = __monitor_buff_data_handle(&file->evlist.list,
                                     &file->evlist_size,
                                     tmp_buff_pp,
                                     buffer_size_list_p,
                                     0,
                                     total_packets_cnt,
                                     buffers_count);
    if (err) {
        printk(KERN_ERR "%s(): __monitor_buff_data_handle for regular monitor RDQ failed. err: %d \n",
               __func__, err);
        spin_unlock_irqrestore(&file->lock, flags);
        goto out;
    }

    /* Go over the SW buffer and read the data (discarded packets) from it as well.
     * Note that this buffer will contain data only if it was retrieved in case of trap
     * double registration (regular and monitor trap groups).
     */
    err = __monitor_buff_data_handle(&file->bound_monitor_rdq->sw_dup_evlist_p->list,
                                     &file->bound_monitor_rdq->sw_dup_evlist_cnt,
                                     tmp_buff_pp,
                                     buffer_size_list_p,
                                     total_packets_cnt,
                                     (total_packets_cnt + sw_total_packets_cnt),
                                     buffers_count);
    if (err) {
        printk(KERN_ERR "%s(): __monitor_buff_data_handle for monitor SW queue failed. err: %d \n",
               __func__, err);
        spin_unlock_irqrestore(&file->lock, flags);
        goto out;
    }

    spin_unlock_irqrestore(&file->lock, flags);

    if (buffers_count > total_packets_cnt + sw_total_packets_cnt) {
        /* User may requests more packets than we have in the buffers,
         * hence return to him the actual number of packets which we have. */
        *buffers_count_p = total_packets_cnt + sw_total_packets_cnt;
    }

    /* Copy retrieved data from local buffer to user */
    for (i = 0; i < (*buffers_count_p); i++) {
        if (copy_to_user(buffer_list_p[i], tmp_buff_pp[i], buffer_size_list_p[i])) {
            err = -EFAULT;
            goto out;
        }
    }

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX "To the user will be send %d entries in the buffer.\n", *buffers_count_p);
#endif

out:
    if (release_tmp_buff == true) {
        /* Release used memory which was requested by user */
        for (i = 0; i < buffers_count; i++) {
            kfree(tmp_buff_pp[i]);
        }
        kfree(tmp_buff_pp);
    }

    /* connect trap group to rdq */
    err = sx_trap_group_path_set(file->bound_monitor_rdq, HTGT_LOCAL_PATH);
    if (err) {
        printk(KERN_ERR "%s(): connect rdq %d to TG failed. err: %d \n",
               __func__, file->bound_monitor_rdq->dqn, err);
        goto out;
    }

    return err;
}


static void sx_l2_tunnel_handler(struct completion_info *comp_info, void *context)
{
    struct sx_dev  *dev = (struct sx_dev *)context;
    struct sk_buff *skb = comp_info->skb;

    /* sx_priv(dev) has the relevant info for building the headers and sending */
    dev = NULL;
    skb_get(skb);
    kfree_skb(skb);
}


static int __synd_cfg(struct file *filp, unsigned int cmd, unsigned long data)
{
    struct ku_synd_ioctl      ku;
    union ku_filter_critireas critireas;
    struct sx_dev            *dev;
    enum l2_type              listener_type = L2_TYPE_DONT_CARE;
    int                       err;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user((void*)&ku, (void*)data, sizeof(ku));
    if (err) {
        goto out;
    }

    err = check_valid_ku_synd(&ku);
    if (err) {
        goto out;
    }

    memcpy(&critireas, &ku.critireas, sizeof(critireas));

    err = sx_core_ioctl_synd_param_prepare(ku.type, &listener_type);
    if (err) {
        goto out;
    }

    switch (ku.channel_type) {
    case SX_KU_USER_CHANNEL_TYPE_PHY_NETDEV:
        if (dev->profile.swid_type[ku.swid] != SX_KU_L2_TYPE_ETH) {
            printk("%s: Adding phy netdev on non ethernet device is not implemented\n", __func__);
            err = -EFAULT;
            goto out;
        }

        if (cmd == CTRL_CMD_ADD_SYND) {
            printk("%s: Adding SX_KU_USER_CHANNEL_TYPE_PHY_NETDEV\n", __func__);
            err = sx_core_add_synd_phy(ku.swid, ku.syndrome_num, dev, &(ku.port_vlan_params));
        } else {
            printk("%s: Removing SX_KU_USER_CHANNEL_TYPE_PHY_NETDEV\n", __func__);
            err = sx_core_remove_synd_phy(ku.swid, ku.syndrome_num, dev, &(ku.port_vlan_params));
        }

        if (err) {
            goto out;
        }

        break;

    case SX_KU_USER_CHANNEL_TYPE_L2_NETDEV:
        if (dev->profile.swid_type[ku.swid] != SX_KU_L2_TYPE_ETH) {
            printk("%s: Adding L2 netdev on non ethernet device is not implemented\n", __func__);
            err = -EFAULT;
            goto out;
        }

        if (cmd == CTRL_CMD_ADD_SYND) {
            printk("%s: Adding SX_KU_USER_CHANNEL_TYPE_L2_NETDEV\n", __func__);
            err = sx_core_add_synd_l2(ku.swid, ku.syndrome_num, dev, &(ku.port_vlan_params));
        } else {
            printk("%s: Removing SX_KU_USER_CHANNEL_TYPE_L2_NETDEV\n", __func__);
            err = sx_core_remove_synd_l2(ku.swid, ku.syndrome_num, dev, &(ku.port_vlan_params));
        }

        if (err) {
            goto out;
        }

        break;

    case SX_KU_USER_CHANNEL_TYPE_L3_NETDEV:
        if (dev->profile.swid_type[ku.swid] == SX_KU_L2_TYPE_ETH) {
            /* L3 traps registration */
            if (cmd == CTRL_CMD_ADD_SYND) {
                err = sx_core_add_synd_l3(ku.swid, ku.syndrome_num, dev, &(ku.port_vlan_params));
            } else {
                err = sx_core_remove_synd_l3(ku.swid, ku.syndrome_num, dev, &(ku.port_vlan_params));
            }

            if (err) {
                goto out;
            }
        } else {
            /* IPoIB traps registration */
            if (cmd == CTRL_CMD_ADD_SYND) {
                err = sx_core_add_synd_ipoib(ku.swid, ku.syndrome_num, dev);
            } else {
                err = sx_core_remove_synd_ipoib(ku.swid, ku.syndrome_num, dev);
            }

            if (err) {
                goto out;
            }
        }

        break;

    case SX_KU_USER_CHANNEL_TYPE_FD:
        if ((ku.type == SX_KU_L2_TYPE_ETH) &&
            ((sx_glb.tmp_dev_ptr->profile.swid_type[ku.swid] == SX_KU_L2_TYPE_ETH) ||
             (sx_glb.tmp_dev_ptr->profile.swid_type[ku.swid] == SX_KU_L2_TYPE_ROUTER_PORT))) {
            ku.swid = SWID_NUM_DONT_CARE;
        } else if ((ku.type == SX_KU_L2_TYPE_DONT_CARE) &&
                   (ku.critireas.dont_care.sysport == SYSPORT_DONT_CARE_VALUE)) {
            if ((sx_glb.tmp_dev_ptr->profile.swid_type[ku.swid] == SX_KU_L2_TYPE_ETH) ||
                (sx_glb.tmp_dev_ptr->profile.swid_type[ku.swid] == SX_KU_L2_TYPE_ROUTER_PORT)) {
                ku.swid = SWID_NUM_DONT_CARE;
                ku.type = SX_KU_L2_TYPE_ETH;
            } else if (sx_glb.tmp_dev_ptr->profile.swid_type[ku.swid] == SX_KU_L2_TYPE_IB) {
                ku.type = SX_KU_L2_TYPE_IB;
            }
        }

        if (cmd == CTRL_CMD_ADD_SYND) {
            err = sx_core_add_synd(ku.swid, ku.syndrome_num,
                                   listener_type, ku.is_default,
                                   critireas, sx_cq_handler, filp,
                                   CHECK_DUP_ENABLED_E, dev, &ku.port_vlan_params);
        } else {
            err = sx_core_remove_synd(ku.swid, ku.syndrome_num,
                                      listener_type, ku.is_default,
                                      critireas, filp, dev, NULL, &ku.port_vlan_params);
        }

        if (err) {
            goto out;
        }

        break;

    case SX_KU_USER_CHANNEL_TYPE_L2_TUNNEL:
        if (cmd == CTRL_CMD_ADD_SYND) {
            sx_priv(dev)->l2_tunnel_params = ku.l2_tunnel_params;
            err = sx_core_add_synd(ku.swid, ku.syndrome_num,
                                   listener_type, ku.is_default,
                                   critireas, sx_l2_tunnel_handler, dev,
                                   CHECK_DUP_DISABLED_E, dev, &ku.port_vlan_params);
        } else {
            err = sx_core_remove_synd(ku.swid, ku.syndrome_num,
                                      listener_type, ku.is_default,
                                      critireas, dev, dev, NULL, &ku.port_vlan_params);
        }

        if (err) {
            goto out;
        }

        break;

    default:
        printk(KERN_ERR PFX "Err: invalid channel type : %d \n", ku.channel_type);
        err = -EINVAL;
        goto out;
    }

out:
    return err;
}


long ctrl_cmd_add_synd(struct file *file, unsigned int cmd, unsigned long data)
{
    return __synd_cfg(file, cmd, data);
}


long ctrl_cmd_remove_synd(struct file *file, unsigned int cmd, unsigned long data)
{
    return __synd_cfg(file, cmd, data);
}


/**
 * This function is used for managing (adding or removing)
 * hardware syndrom for monitor trap group.
 * Note that it will be invoked only in case of trap id double
 * registration what will allow to store the relevant discarded
 * packet to the SW buffer.
 *
 * @return err
 */

long ctrl_cmd_monitor_sw_queue_synd(struct file *file, unsigned int cmd, unsigned long data)
{
    int                          err = 0;
    struct ku_monitor_synd_ioctl ku;
    struct sx_dq                *monitor_dq;
    struct sx_dev               *dev;
    enum l2_type                 listener_type = L2_TYPE_DONT_CARE;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user((void*)&ku, (void*)data, sizeof(ku));
    if (err) {
        printk(KERN_ERR PFX "Failed to copy data provided by user, err = %d.\n", err);
        goto out;
    }

    if (ku.monitor_hw_trap_group >= dev->dev_cap.max_num_rdqs) {
        printk(KERN_ERR PFX "CTRL_CMD_MONITOR_SYND: RDQ %d is out of range\n",
               ku.monitor_hw_trap_group);
        return -EINVAL;
    }

    monitor_dq = sx_priv(dev)->rdq_table.dq[ku.monitor_hw_trap_group];
    if (!monitor_dq) {
        printk(KERN_ERR PFX "CTRL_CMD_MONITOR_SYND: RDQ %d is not valid\n",
               ku.monitor_hw_trap_group);
        return -EINVAL;
    }

    err = sx_core_ioctl_synd_param_prepare(ku.type, &listener_type);
    if (err) {
        printk(KERN_ERR PFX "Failed to prepare listener type attribute for type %u, err = %u.\n", ku.type, err);
        goto out;
    }

    if (ku.cmd == true) { /* Add listener which will store matched packet to SW buffer of monitor RDQ */
        err = sx_core_add_synd(ku.swid, ku.syndrome_num,
                               listener_type, false,
                               ku.critireas, sx_cq_monitor_sw_queue_handler,  monitor_dq->file_priv_p->owner, /* use required filp */
                               CHECK_DUP_ENABLED_E, dev, &ku.port_vlan_params);
    } else { /* remove listener */
        if (monitor_dq->file_priv_p) {
            err = sx_core_remove_synd(ku.swid, ku.syndrome_num,
                                      listener_type, false,
                                      ku.critireas,  monitor_dq->file_priv_p->owner, dev, NULL, &ku.port_vlan_params);
        }
    }

    if (err) {
        printk(KERN_ERR PFX "Failed to %s listener, err = %u.\n", ((ku.cmd == true) ? "add" : "remove"), err);
        goto out;
    }

out:
    return err;
}


long ctrl_cmd_multi_packet_enable(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_rsc *rsc = file->private_data;

    if ((data != false) && (data != true)) {
        printk(KERN_WARNING PFX "ioctl MULTI_PACKET_ENABLE: " \
               "error data = %lu > 1\n", data);
        return -EINVAL;
    }

    atomic_set(&rsc->multi_packet_read_enable, data);
    return 0;
}


long ctrl_cmd_blocking_enable(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_rsc *rsc = file->private_data;

    if ((data != false) && (data != true)) {
        return -EINVAL;
    }

    atomic_set(&rsc->read_blocking_state, data);
    return 0;
}


long ctrl_cmd_raise_event(struct file *file, unsigned int cmd, unsigned long data)
{
    int                    err = 0;
    struct sk_buff        *skb = NULL;
    struct sx_dev         *dev;
    struct ku_raise_trap   event_data;
    struct completion_info ci;
    void                  *buff;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user((void*)(&event_data), (void*)data, sizeof(event_data));
    if (err) {
        goto out_err;
    }

    if ((event_data.buffer_size == 0) ||
        (event_data.trap_id > NUM_HW_SYNDROMES)) {
        printk(KERN_WARNING "sx_raise_event: Bad parameters\n");
        err = -EINVAL;
        goto out_err;
    }

    skb = alloc_skb(event_data.buffer_size, GFP_KERNEL);
    if (!skb) {
        err = -ENOMEM;
        goto out_err;
    }

    buff = skb_put(skb, event_data.buffer_size);
    if (buff == NULL) {
        err = -ENOMEM;
        goto out;
    }
    err = copy_from_user(buff, event_data.buffer_p,
                         event_data.buffer_size);
    if (err) {
        goto out;
    }

#ifdef SX_DEBUG
    printk(KERN_DEBUG PFX "sx_raise_event: got from user:\n");
    printk(KERN_DEBUG PFX "sx_raise_event: trap_id = %u\n",
           event_data.trap_id);
    printk(KERN_DEBUG PFX "sx_raise_event: buffer_size = %u\n",
           event_data.buffer_size);
    SX_CORE_HEXDUMP16(event_data.buffer_p, event_data.buffer_size);
#endif

    memset(&ci, 0, sizeof(ci));
    ci.hw_synd = event_data.trap_id;
    ci.sysport = event_data.sysport;
    ci.is_lag = event_data.is_lag;
    ci.lag_subport = event_data.lag_subport;
    ci.swid = event_data.swid;
    ci.skb = skb;
    ci.pkt_type = PKT_TYPE_ETH;
    ci.info.eth.dmac = DMAC_DONT_CARE_VALUE;
    ci.info.eth.ethtype = ETHTYPE_DONT_CARE_VALUE;
    ci.info.eth.emad_tid = TID_DONT_CARE_VALUE;
    ci.context = file;
    dispatch_pkt(dev, &ci, event_data.trap_id, 0);
out:
    kfree_skb(skb);
out_err:
    return err;
}


long ctrl_cmd_get_syndrome_status(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_synd_query_ioctl *synd_query = NULL;
    struct ku_synd_query_ioctl  tmp_synd_query;
    unsigned long               flags;
    u8                          is_registered = 0;
    int                         err = 0;

    err = copy_from_user(&tmp_synd_query, (void*)data,
                         sizeof(tmp_synd_query));
    if (err) {
        goto out;
    }

    if (tmp_synd_query.syndrome_num > NUM_HW_SYNDROMES) {
        err = -EINVAL;
        goto out;
    }

    spin_lock_irqsave(&sx_glb.listeners_lock, flags);
    if (!list_empty(&sx_glb.listeners_db[tmp_synd_query.syndrome_num].list)) {
        is_registered = 1;
    }
    spin_unlock_irqrestore(&sx_glb.listeners_lock, flags);

    synd_query = (struct ku_synd_query_ioctl *)data;
    err = copy_to_user(&synd_query->is_registered, &is_registered,
                       sizeof(is_registered));

out:
    return err;
}


long ctrl_cmd_get_swid_2_rdq(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_swid_2_rdq_query swid_2_rdq;
    struct sx_dev             *dev;
    int                        err = 0;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    if (!dev->profile_set) {
        return -EFAULT;
    }

    err = copy_from_user(&swid_2_rdq, (void*)data,
                         sizeof(swid_2_rdq));
    if (err) {
        goto out;
    }

    if ((dev->profile.swid_type[swid_2_rdq.swid] ==
         SX_KU_L2_TYPE_DONT_CARE) ||
        !sx_bitmap_test(&sx_priv(dev)->swid_bitmap,
                        swid_2_rdq.swid)) {
        err = -EINVAL;
        goto out;
    }

    swid_2_rdq.rdq = dev->profile.rdq[swid_2_rdq.swid][0];
    err = copy_to_user((void*)data, &swid_2_rdq,
                       sizeof(swid_2_rdq));

out:
    return err;
}

long ctrl_cmd_set_rdq_rate_limiter(struct file *file, unsigned int cmd, unsigned long data)
{
    /* OBSOLETE FUNCTIONALITY! Leaving it here just not to break old users */
    return 0;
}


long ctrl_cmd_set_rdq_timestamp_state(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_rdq_timestamp_state rdq_ts_state;
    int                           cqn;
    struct sx_dev                *dev;
    int                           err = 0;
    int                           rc = 0;
    uint8_t                       rdq_num = 0;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    if (!dev->pdev) {
        printk(KERN_DEBUG PFX "will not set time stamp state since there's no PCI device\n");
        goto out;
    }

    err = copy_from_user(&rdq_ts_state, (void*)data, sizeof(rdq_ts_state));
    if (err) {
        goto out;
    }

    rc = sx_core_get_rdq_num_max(dev, &rdq_num);
    if (rc) {
        printk(KERN_ERR PFX "Error: failed to get max RDQ num\n");
        goto out;
    }

    if ((rdq_ts_state.rdq < 0) || (rdq_ts_state.rdq >= rdq_num)) {
        printk(KERN_WARNING PFX "Cannot set time stamp state, RDQ value (%d) is not valid\n",
               rdq_ts_state.rdq);
        err = -EINVAL;
        goto out;
    }

    cqn = rdq_ts_state.rdq + NUMBER_OF_SDQS;
    if (rdq_ts_state.enable) {
        sx_bitmap_set(&sx_priv(dev)->cq_table.ts_bitmap, cqn);
    } else {
        sx_bitmap_free(&sx_priv(dev)->cq_table.ts_bitmap, cqn);
    }

out:
    return err;
}


long ctrl_cmd_set_rdq_cpu_priority(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_rdq_cpu_priority rdq_cpu_prio;
    int                        cqn;
    struct sx_dev             *dev;
    int                        err = 0;
    int                        rc = 0;
    uint8_t                    rdq_num = 0;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    if (!dev->pdev) {
        printk(KERN_DEBUG PFX "will not set CPU priority since there's no PCI device\n");
        goto out;
    }

    err = copy_from_user(&rdq_cpu_prio, (void*)data, sizeof(rdq_cpu_prio));
    if (err) {
        goto out;
    }

    rc = sx_core_get_rdq_num_max(dev, &rdq_num);
    if (rc) {
        printk(KERN_ERR PFX "Error: failed to get max RDQ num\n");
        goto out;
    }

    if ((rdq_cpu_prio.rdq < 0) || (rdq_cpu_prio.rdq >= rdq_num)) {
        printk(KERN_WARNING PFX "Cannot set CPU priority, RDQ value (%d) is not valid\n",
               rdq_cpu_prio.rdq);
        err = -EINVAL;
        goto out;
    }

    cqn = rdq_cpu_prio.rdq + NUMBER_OF_SDQS;
    if (rdq_cpu_prio.high_prio || (rdq_cpu_prio.rdq == dev->profile.emad_rdq)) {
        sx_bitmap_set(&sx_priv(dev)->cq_table.cpu_traffic_prio.high_prio_cq_bitmap, cqn);
    } else {
        sx_bitmap_free(&sx_priv(dev)->cq_table.cpu_traffic_prio.high_prio_cq_bitmap, cqn);
    }

out:
    return err;
}

long ctrl_cmd_set_truncate_params(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_set_truncate_params truncate_params;
    unsigned long                 flags;
    struct sx_dev                *dev;
    int                           err = 0;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    if (!dev->pdev) {
        printk(KERN_DEBUG PFX "will not set truncate params since there's no "
               "PCI device\n");
        goto out;
    }

    err = copy_from_user(&truncate_params, (void*)data,
                         sizeof(truncate_params));
    if (err) {
        goto out;
    }

    if (truncate_params.rdq >= dev->dev_cap.max_num_rdqs) {
        printk(KERN_ERR PFX "CTRL_CMD_SET_TRUNCATE_PARAMS: RDQ %d is not valid\n",
               truncate_params.rdq);
        return -EINVAL;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (truncate_params.truncate_enable) {
        if (truncate_params.truncate_size < SX_TRUNCATE_SIZE_MIN) {
            printk(KERN_ERR PFX "CTRL_CMD_SET_TRUNCATE_PARAMS: Truncate size %u is not valid\n",
                   truncate_params.truncate_size);
            spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
            err = -EINVAL;
            goto out;
        }

        sx_priv(dev)->truncate_size_db[truncate_params.rdq] = truncate_params.truncate_size;
    } else {
        sx_priv(dev)->truncate_size_db[truncate_params.rdq] = 0;
    }

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

out:
    return err;
}


long ctrl_cmd_get_counters(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_get_counters *counters;
    const int               swid = 0; /* the only SWID on Spectrum */
    int                     trap_id;
    int                     err = 0;

    counters = (struct ku_get_counters*)kzalloc(sizeof(*counters), GFP_KERNEL);
    if (counters == NULL) {
        err = -ENOMEM;
        goto out;
    }

    /* the index NUMBER_OF_SWIDS holds the global counters of all swids */
    counters->fromcpu_data_packet = sx_glb.stats.tx_by_pkt_type[swid][SX_PKT_TYPE_ETH_DATA];
    counters->fromcpu_data_byte = sx_glb.stats.tx_by_pkt_type_bytes[swid][SX_PKT_TYPE_ETH_DATA];
    counters->fromcpu_control_packet = sx_glb.stats.tx_by_pkt_type[swid][SX_PKT_TYPE_ETH_CTL_UC] +
                                       sx_glb.stats.tx_by_pkt_type[swid][SX_PKT_TYPE_ETH_CTL_MC];
    counters->fromcpu_control_byte = sx_glb.stats.tx_by_pkt_type_bytes[swid][SX_PKT_TYPE_ETH_CTL_UC] +
                                     sx_glb.stats.tx_by_pkt_type_bytes[swid][SX_PKT_TYPE_ETH_CTL_MC];

    /* iterate HW trap_id (0-511) */
    for (trap_id = 0; trap_id < NUM_HW_SYNDROMES - NUM_SW_SYNDROMES; trap_id++) { /* trap_id 0-511 (512) */
        counters->trap_id_packet[trap_id] = sx_glb.stats.rx_by_synd[swid][trap_id];
        counters->trap_id_byte[trap_id] = sx_glb.stats.rx_by_synd_bytes[swid][trap_id];
    }

    /* iterate SW trap_id-events (512-575) */
    for (/* trap_id initialized */; trap_id < NUM_HW_SYNDROMES; trap_id++) {  /* trap_id 512-575 (64) */
        counters->trap_id_events[trap_id] = sx_glb.stats.rx_eventlist_by_synd[trap_id];
    }

    err = copy_to_user((void*)data, counters, sizeof(*counters));
    kfree(counters);

out:
    return err;
}


long ctrl_cmd_set_monitor_rdq(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_set_monitor_rdq_params monitor_rdq_params;
    struct sx_dq                    *dq;
    struct sx_dev                   *dev;
    struct sx_rsc                   *rsc = file->private_data;
    unsigned long                    flags;
    int                              err = 0;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    if (!dev->pdev) {
        printk(KERN_DEBUG PFX "will not set monitor rdq since there's no PCI device\n");
        goto out;
    }

    err = copy_from_user(&monitor_rdq_params, (void*)data, sizeof(monitor_rdq_params));
    if (err) {
        goto out;
    }

    if (monitor_rdq_params.rdq >= dev->dev_cap.max_num_rdqs) {
        printk(KERN_ERR PFX "CTRL_CMD_SET_MONITOR_RDQ: RDQ %d is out of range\n", monitor_rdq_params.rdq);
        return -EINVAL;
    }

    spin_lock_irqsave(&sx_priv(dev)->rdq_table.lock, flags);

    /* check the rdq is valid */
    dq = sx_priv(dev)->rdq_table.dq[monitor_rdq_params.rdq];
    if (!dq) {
        printk(KERN_ERR PFX "CTRL_CMD_SET_MONITOR_RDQ: RDQ %d is not valid\n", monitor_rdq_params.rdq);
        spin_unlock_irqrestore(&sx_priv(dev)->rdq_table.lock, flags);
        return -EINVAL;
    }

    if (monitor_rdq_params.is_monitor) {
        if (dq->is_monitor) {
            if (dq->file_priv_p->owner == rsc->owner) { /* same owner, do nothing */
                spin_unlock_irqrestore(&sx_priv(dev)->rdq_table.lock, flags);
                goto out;
            }

            unset_monitor_rdq(dq); /* remove old owner, here comes a new one */
        }

        dq->is_monitor = 1;
        dq->file_priv_p = rsc;
        dq->file_priv_p->bound_monitor_rdq = dq;
        dq->cpu_tclass = monitor_rdq_params.cpu_tclass;

        /* allocate memory for SW buffer which will be used for SW buffer
         * which is used to simulate RDQ and store discarded packets which
         * were consumed by NOS (in case of trap double registration). */
        dq->file_priv_p->bound_monitor_rdq->sw_dup_evlist_p =
            kzalloc(sizeof(*dq->file_priv_p->bound_monitor_rdq->sw_dup_evlist_p), GFP_KERNEL);

        if (dq->file_priv_p->bound_monitor_rdq->sw_dup_evlist_p == NULL) {
            printk(KERN_DEBUG PFX " Failed to allocate memory for SW duplication queue. \n");
            spin_unlock_irqrestore(&sx_priv(dev)->rdq_table.lock, flags);
            return -ENOMEM;
        }
        /* Initialize SW buffer counters */
        dq->file_priv_p->bound_monitor_rdq->sw_dup_evlist_cnt = 0;
        dq->file_priv_p->bound_monitor_rdq->sw_dup_evlist_total_cnt = 0;

        INIT_LIST_HEAD(&dq->file_priv_p->bound_monitor_rdq->sw_dup_evlist_p->list);
        dq->file_priv_p->bound_monitor_rdq->mon_rx_start = dq->file_priv_p->bound_monitor_rdq->cq->cons_index;
        dq->file_priv_p->bound_monitor_rdq->mon_rx_count = dq->file_priv_p->bound_monitor_rdq->mon_rx_start;
        dq->file_priv_p->bound_monitor_rdq->mon_rx_start_total = dq->file_priv_p->bound_monitor_rdq->mon_rx_count;

        err = sx_core_add_rdq_to_monitor_rdq_list(dq);
        if (err) {
            unset_monitor_rdq(dq);
            spin_unlock_irqrestore(&sx_priv(dev)->rdq_table.lock, flags);
            goto out;
        }
    } else {
        unset_monitor_rdq(dq);

        sx_core_del_rdq_from_monitor_rdq_list(dq);
    }

    spin_unlock_irqrestore(&sx_priv(dev)->rdq_table.lock, flags);

out:
    return err;
}


long ctrl_cmd_read_multi(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_read_multi_params *read_multi_params_p = NULL;
    struct sx_dev               *dev;
    struct sx_rsc               *rsc = file->private_data;
    int                          err = 0;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    if (!dev->pdev) {
        printk(KERN_DEBUG PFX "will not execute multi packets read since there's no PCI device\n");
        goto out;
    }

    read_multi_params_p = vmalloc(sizeof(*read_multi_params_p));
    if (!read_multi_params_p) {
        printk(KERN_DEBUG PFX "can't vmalloc read_multi_params_p\n");
        err = -ENOMEM;
        goto out;
    }


    err = copy_from_user(read_multi_params_p, (void*)data, sizeof(*read_multi_params_p));
    if (err) {
        vfree(read_multi_params_p);
        goto out;
    }

    if (rsc->bound_monitor_rdq) {
        err = __monitor_file_read(file, read_multi_params_p->file_op, &read_multi_params_p->buffer_count,
                                  read_multi_params_p->buffer_list, read_multi_params_p->buffer_size_list);
        if (err) {
            printk(KERN_ERR PFX "ioctl_read failed err:%d, buf_cnt:%d, buff_list:%p, buff_list_cnt:%p\n",
                   err,
                   read_multi_params_p->buffer_count,
                   read_multi_params_p->buffer_list,
                   read_multi_params_p->buffer_size_list);
            vfree(read_multi_params_p);
            goto out;
        }

        err = copy_to_user((void*)data, read_multi_params_p, sizeof(*read_multi_params_p));
    } else {
        printk(KERN_ERR PFX "multi_read from fd which is not monitor isn't supported .\n");
        err = -EINVAL;
    }

    vfree(read_multi_params_p);

out:
    return err;
}


/**
 * This function is used for reading Monitor RDQ statistics
 * (e.g. the total number of discarded packets). It count the
 * total number of discarded packets for real HW cyclic queue
 * and number of discarded packets for SW cyclic buffer.
 *
 * @param[in] dev  - sx_dev struct to use for handling the data
 * @param[in] data - retrieved data from user
 *
 * @return err
 */
long ctrl_cmd_get_rdq_stat(struct file *file, unsigned int cmd, unsigned long data)
{
    struct sx_dev                          *dev;
    int                                     err = 0;
    struct ku_monitor_trap_group_stat_ioctl ku;
    struct sx_dq                           *monitor_dq;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&ku, (void*)data, sizeof(ku));
    if (err) {
        printk(KERN_ERR PFX "Failed to copy provided by user data.\n");
        goto out;
    }

    if (ku.monitor_hw_trap_group >= dev->dev_cap.max_num_rdqs) {
        printk(KERN_ERR PFX "CTRL_CMD_GET_RDQ_STAT: RDQ %d is out of range\n",
               ku.monitor_hw_trap_group);
        err = -EINVAL;
        goto out;
    }

    monitor_dq = sx_priv(dev)->rdq_table.dq[ku.monitor_hw_trap_group];
    if (!monitor_dq) {
        printk(KERN_ERR PFX "CTRL_CMD_GET_RDQ_STAT: RDQ %d is not valid\n",
               ku.monitor_hw_trap_group);
        err = -EINVAL;
        goto out;
    }

    ku.discarded_pkts_total_num = monitor_dq->mon_rx_count - monitor_dq->mon_rx_start_total +
                                  monitor_dq->sw_dup_evlist_total_cnt;

    if (ku.clear_after_read == true) {
        monitor_dq->mon_rx_start_total = monitor_dq->mon_rx_count;
    }

    err = copy_to_user((void*)data, &ku, sizeof(ku));
    if (err) {
        printk(KERN_ERR PFX "Failed to copy data to user, err = %d.\n", err);
        goto out;
    }

out:
    return err;
}


long ctrl_cmd_set_skb_offload_fwd_mark_en(struct file *file, unsigned int cmd, unsigned long data)
{
#ifdef CONFIG_NET_SWITCHDEV
    struct sx_dev       *dev;
    int                  err = 0;
    union sx_event_data *offload_mark_event_data = NULL;
    u8                   offload_fwd_mark_en;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user((void*)&offload_fwd_mark_en,
                         (void*)data, sizeof(offload_fwd_mark_en));
    if (err) {
        err = -ENOMEM;
        goto out;
    }

    offload_mark_event_data = kzalloc(sizeof(union sx_event_data), GFP_KERNEL);
    if (!offload_mark_event_data) {
        err = -ENOMEM;
        goto out;
    }

    offload_mark_event_data->offload_mark_set.offload_mark_set_en = offload_fwd_mark_en;
    sx_core_dispatch_event(dev, SX_DEV_EVENT_OFFLOAD_MARK_SET, offload_mark_event_data);
    kfree(offload_mark_event_data);

out:
    return err;
#else
    printk(KERN_INFO PFX "ioctl ignored because offload_fwd_mark_en module param not avail in this kernel version\n");
    return 0;
#endif
}


long ctrl_cmd_flush_evlist(struct file *file, unsigned int cmd, unsigned long data)
{
    unsigned long      flags;
    struct list_head  *pos = NULL, *q = NULL;
    struct event_data *entry = NULL;
    struct sx_rsc     *rsc = file->private_data;

    spin_lock_irqsave(&rsc->lock, flags);

    list_for_each_safe(pos, q, &rsc->evlist.list) {
        entry = list_entry(pos, struct event_data, list);
        list_del(pos);
        kfree_skb(entry->skb);
        kfree(entry);
    }

    spin_unlock_irqrestore(&rsc->lock, flags);

    return 0;
}


long ctrl_cmd_trap_filter_add(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_trap_filter_data filter_data;
    struct sx_dev             *dev;
    unsigned long              flags;
    int                        i, idx = -1;
    uint16_t                   lag_max = 0, lag_member_max = 0;
    int                        err = 0;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&filter_data, (void*)data, sizeof(filter_data));
    if (err) {
        goto out;
    }

    if (filter_data.trap_id >= NUM_HW_SYNDROMES) {
        printk(KERN_ERR PFX "Received TRAP ID %d "
               "is invalid\n", filter_data.trap_id);
        err = -EINVAL;
        goto out;
    }

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        printk(KERN_ERR PFX "Failed to get max number of LAGs.\n");
        err = -EINVAL;
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (filter_data.is_lag) {
        if (filter_data.lag_id >= lag_max) {
            printk(KERN_ERR PFX "Received LAG ID 0x%x "
                   "is invalid\n",
                   filter_data.lag_id);
            spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
            err = -EINVAL;
            goto out;
        }

        for (i = 0; i < MAX_LAG_PORTS_IN_FILTER; i++) {
            if (sx_priv(dev)->lag_filter_db[filter_data.trap_id][i] ==
                filter_data.lag_id) {
                printk(KERN_ERR PFX "Received LAG ID %d "
                       "is already in the filter list "
                       "of trap ID 0x%x\n",
                       filter_data.lag_id,
                       filter_data.trap_id);
                spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
                err = -EEXIST;
                goto out;
            }

            if (sx_priv(dev)->lag_filter_db[filter_data.trap_id][i] ==
                LAG_ID_INVALID) {
                idx = i;
            }
        }

        if (idx == -1) {
            printk(KERN_ERR PFX "Cannot add LAG ID 0x%x to trap %d filter "
                   "because DB filter DB for this trap is full\n",
                   filter_data.lag_id, filter_data.trap_id);
            err = -EFAULT;
        } else {
            sx_priv(dev)->lag_filter_db[filter_data.trap_id][idx] =
                filter_data.lag_id;
            printk(KERN_INFO PFX "LAG ID %u was added to filter list "
                   "of trap ID 0x%x\n", filter_data.lag_id,
                   filter_data.trap_id);
        }
    } else {
        for (i = 0; i < MAX_SYSTEM_PORTS_IN_FILTER; i++) {
            if (sx_priv(dev)->sysport_filter_db[filter_data.trap_id][i] ==
                filter_data.sysport) {
                printk(KERN_ERR PFX "Received system port 0x%x "
                       "is already in the filter list "
                       "of trap ID 0x%x\n",
                       filter_data.sysport,
                       filter_data.trap_id);
                spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
                err = -EEXIST;
                goto out;
            }

            if (sx_priv(dev)->sysport_filter_db[filter_data.trap_id][i] == 0) {
                idx = i;
            }
        }

        if (idx == -1) {
            printk(KERN_ERR PFX "Cannot add system port 0x%x to trap %d filter "
                   "because DB filter DB for this trap is full\n",
                   filter_data.sysport, filter_data.trap_id);
            err = -EFAULT;
        } else {
            sx_priv(dev)->sysport_filter_db[filter_data.trap_id][idx] =
                filter_data.sysport;
            printk(KERN_INFO PFX "system port 0x%x was added to filter "
                   "list of trap ID 0x%x\n", filter_data.sysport,
                   filter_data.trap_id);
        }
    }

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

out:
    return err;
}


long ctrl_cmd_trap_filter_remove(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_trap_filter_data filter_data;
    uint16_t                   lag_max = 0, lag_member_max = 0;
    unsigned long              flags;
    struct sx_dev             *dev;
    int                        i, err = 0;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&filter_data, (void*)data, sizeof(filter_data));
    if (err) {
        goto out;
    }

    if (filter_data.trap_id >= NUM_HW_SYNDROMES) {
        printk(KERN_ERR PFX "Received TRAP ID %d "
               "is invalid\n", filter_data.trap_id);
        err = -EINVAL;
        goto out;
    }

    if (sx_core_get_lag_max(dev, &lag_max, &lag_member_max)) {
        printk(KERN_ERR PFX "Failed to get max number of LAGs.\n");
        err = -EINVAL;
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (filter_data.is_lag) {
        if (filter_data.lag_id >= lag_max) {
            printk(KERN_ERR PFX "Received LAG ID 0x%x "
                   "is invalid\n",
                   filter_data.lag_id);
            spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
            err = -EINVAL;
            goto out;
        }

        for (i = 0; i < MAX_LAG_PORTS_IN_FILTER; i++) {
            if (sx_priv(dev)->lag_filter_db[filter_data.trap_id][i] ==
                filter_data.lag_id) {
                sx_priv(dev)->lag_filter_db[filter_data.trap_id][i] =
                    LAG_ID_INVALID;
                printk(KERN_INFO PFX "LAG ID %u was removed from filter list "
                       "of trap ID 0x%x\n", filter_data.lag_id,
                       filter_data.trap_id);
                break;
            }
        }

        if (i == MAX_LAG_PORTS_IN_FILTER) {
            printk(KERN_ERR PFX "Cannot find LAG ID 0x%x in trap ID %d filter DB\n",
                   filter_data.lag_id, filter_data.trap_id);
            err = -EINVAL;
        }
    } else {
        for (i = 0; i < MAX_SYSTEM_PORTS_IN_FILTER; i++) {
            if (sx_priv(dev)->sysport_filter_db[filter_data.trap_id][i] ==
                filter_data.sysport) {
                sx_priv(dev)->sysport_filter_db[filter_data.trap_id][i] = 0;
                printk(KERN_INFO PFX "system port 0x%x was removed from filter "
                       "list of trap ID 0x%x\n", filter_data.sysport,
                       filter_data.trap_id);
                break;
            }
        }

        if (i == MAX_SYSTEM_PORTS_IN_FILTER) {
            printk(KERN_ERR PFX "Cannot find system port 0x%x in trap ID %d "
                   "filter DB\n", filter_data.sysport, filter_data.trap_id);
            err = -EINVAL;
        }
    }

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);

out:
    return err;
}


long ctrl_cmd_trap_filter_remove_all(struct file *file, unsigned int cmd, unsigned long data)
{
    struct ku_trap_filter_data filter_data;
    unsigned long              flags;
    struct sx_dev             *dev;
    int                        i, err = 0;

    SX_CORE_IOCTL_GET_GLOBAL_DEV(&dev);

    err = copy_from_user(&filter_data, (void*)data, sizeof(filter_data));
    if (err) {
        goto out;
    }

    if (filter_data.trap_id >= NUM_HW_SYNDROMES) {
        printk(KERN_ERR PFX "Received TRAP ID %d "
               "is invalid\n", filter_data.trap_id);
        err = -EINVAL;
        goto out;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    for (i = 0; i < MAX_LAG_PORTS_IN_FILTER; i++) {
        sx_priv(dev)->lag_filter_db[filter_data.trap_id][i] = LAG_ID_INVALID;
    }

    for (i = 0; i < MAX_SYSTEM_PORTS_IN_FILTER; i++) {
        sx_priv(dev)->sysport_filter_db[filter_data.trap_id][i] = 0;
    }

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
    printk(KERN_INFO PFX "Removed all ports and LAGs from the filter list "
           "of trap ID %d\n", filter_data.trap_id);

out:
    return err;
}
