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

/************************************************
 * Includes                                     *
 ***********************************************/

#include <linux/skbuff.h>
#include <linux/pci.h>
#include <linux/if_ether.h>
#include <linux/delay.h>
#include "dq.h"
#include "cq.h"
#include "alloc.h"
#include "sx.h"
#include <linux/mlx_sx/cmd.h>
#include <linux/mlx_sx/kernel_user.h>
#include <linux/mlx_sx/skb_hook.h>
#include "sx_dpt.h"
#include "sx_proc.h"
#include "sgmii.h"

#define SDQ_WATCHDOG_FULL_MSECS 300000

#define SX_MAX_SDQ_SW_QUEUE_LEN (10 * (1 << (SX_MAX_LOG_DQ_SIZE)))

/************************************************
 *  Globals
 ***********************************************/
static int (*tx_stub_func)(struct sk_buff *skb, u8 sdqn);
extern int tx_debug;
extern int tx_debug_pkt_type;
extern int tx_debug_emad_type;
extern int tx_dump;
extern int tx_dump_cnt;

/************************************************
 * Functions                            *
 ***********************************************/

void register_ver_tx_stub(int (*func)(struct sk_buff *skb, u8 sdqn))
{
    tx_stub_func = func;
}
EXPORT_SYMBOL(register_ver_tx_stub);

static int sx_nent_to_4k(int nent)
{
    return ALIGN(nent * SX_DESC_SIZE, 4096) / 4096;
}

static inline void * sx_buf_offset(struct sx_buf *buf, int offset)
{
    if (buf->nbufs == 1) {
        return buf->u.direct.buf + offset;
    } else {
        return buf->u.page_list[offset >> PAGE_SHIFT].buf +
               (offset & (PAGE_SIZE - 1));
    }
}

static void * sx_get_wqe(struct sx_dq *dq, int offset)
{
    return sx_buf_offset(&dq->buf, offset);
}

static void * sx_get_send_wqe(struct sx_dq *dq, int n)
{
    return sx_get_wqe(dq, n << SX_WQE_SHIFT);
}

static __be16 sx_set_wqe_flags(u8 set_lp, enum ku_pkt_type type)
{
    u16 flags = 0;

    flags |= (1 << 15); /* Generate CQE for this WQE */
    if (set_lp) {
        flags |= (1 << 14);
    }
    switch (type) {
    case SX_PKT_TYPE_ETH_CTL_UC:
    case SX_PKT_TYPE_ETH_CTL_MC:
    case SX_PKT_TYPE_ETH_DATA:
    case SX_PKT_TYPE_DROUTE_EMAD_CTL:
    case SX_PKT_TYPE_EMAD_CTL:
        flags |= (WQE_PKT_TYPE_ETH << 7);
        break;

    case SX_PKT_TYPE_FCOE_CTL_UC:
    case SX_PKT_TYPE_FCOE_CTL_MC:
        flags |= (WQE_PKT_TYPE_FCOE << 7);
        break;

    case SX_PKT_TYPE_IB_RAW_CTL:
    case SX_PKT_TYPE_IB_RAW_DATA:
        flags |= (WQE_PKT_TYPE_RAW_IB << 7);
        break;

    case SX_PKT_TYPE_IB_TRANSPORT_CTL:
    case SX_PKT_TYPE_IB_TRANSPORT_DATA:
    case SX_PKT_TYPE_IB_CTL_2:
        flags |= (WQE_PKT_TYPE_IB_TRANSPORT << 7);
        break;

    case SX_PKT_TYPE_FCOIB_CTL:
        flags |= (WQE_PKT_TYPE_FCOIB << 7);
        break;

    case SX_PKT_TYPE_IB_NVLINK:
        flags |= (WQE_PKT_TYPE_NVLoIB << 7);
        break;

    case SX_PKT_TYPE_FC_CTL_UC:
    case SX_PKT_TYPE_FC_CTL_MC:
    case SX_PKT_TYPE_EOIB_CTL:
    default:
        break; /* unsupported */
    }

    return cpu_to_be16(flags);
}

static int sx_build_send_packet(struct sx_dq *sdq, struct sk_buff *skb, struct sx_wqe *wqe, int idx)
{
    int             i, num_frags;
    struct sk_buff *orig_skb = NULL;

    num_frags = skb_shinfo(skb)->nr_frags;
    if (num_frags > 2) { /* no support for more than 2 fragments ... */
        orig_skb = skb;
        skb = skb_copy(skb, GFP_ATOMIC);

        if (!skb) {
            return -ENOMEM;
        }

        num_frags = 0;
    }

    sdq->sge[idx].skb = skb;
    sdq->sge[idx].hdr_pld_sg.vaddr = skb->data;
    sdq->sge[idx].hdr_pld_sg.len = skb_headlen(skb);
    sdq->sge[idx].hdr_pld_sg.dma_addr = dma_map_single(&sdq->dev->pdev->dev,
                                                       sdq->sge[idx].hdr_pld_sg.vaddr,
                                                       sdq->sge[idx].hdr_pld_sg.len, DMA_TO_DEVICE);
    if (dma_mapping_error(&sdq->dev->pdev->dev,
                          sdq->sge[idx].hdr_pld_sg.dma_addr)) {
        if (orig_skb) {
            sx_skb_free(skb); /* delete the copy. the original skb will be freed elsewhere */
        }

        return -ENOMEM;
    }

    if (orig_skb) {
        skb->destructor = orig_skb->destructor;
        orig_skb->destructor = NULL;
    }

    wqe->dma_addr[0] = cpu_to_be64(sdq->sge[idx].hdr_pld_sg.dma_addr);
    wqe->byte_count[0] = cpu_to_be16(sdq->sge[idx].hdr_pld_sg.len);

    dma_sync_single_for_device(&sdq->dev->pdev->dev,
                               sdq->sge[idx].hdr_pld_sg.dma_addr,
                               sdq->sge[idx].hdr_pld_sg.len, DMA_TO_DEVICE);

    for (i = 0; i < num_frags; i++) {
        skb_frag_t         *frag = &skb_shinfo(skb)->frags[i];
        struct sx_sge_data *sge_data;
        if (i == 0) {
            sge_data = &sdq->sge[idx].pld_sg_1;
        } else {
            sge_data = &sdq->sge[idx].pld_sg_2;
        }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
        sge_data->vaddr = skb_frag_address(frag);
        sge_data->len = skb_frag_size(frag);
#else
        sge_data->vaddr = lowmem_page_address(frag->page.p) +
                          frag->page_offset;
        sge_data->len = frag->size;
#endif

        sge_data->dma_addr = dma_map_single(&sdq->dev->pdev->dev,
                                            sge_data->vaddr, sge_data->len, DMA_TO_DEVICE);
        if (dma_mapping_error(&sdq->dev->pdev->dev, sge_data->dma_addr)) {
            return -ENOMEM;
        }

        wqe->dma_addr[i + 1] = cpu_to_be64(sge_data->dma_addr);
        wqe->byte_count[i + 1] = cpu_to_be16(sge_data->len);
        dma_sync_single_for_device(&sdq->dev->pdev->dev,
                                   sge_data->dma_addr, sge_data->len, DMA_TO_DEVICE);
    }

    for (; i < 2; i++) {
        wqe->byte_count[i + 1] = 0;
    }

    if (orig_skb) {
        sx_skb_consume(orig_skb); /* delete orig_skb instead of completion handler. the completion handler will
                                   *  delete the copy */
    }

    return 0;
}
/* DQ must be locked here!!! */
static int sx_dq_overflow(struct sx_dq *sdq)
{
    int q_size;

    if (sdq->head >= sdq->tail) {
        q_size = sdq->head - sdq->tail;
    } else {
        q_size = 0x10000 - (sdq->tail - sdq->head);
    }

    return (q_size + 1 >= sdq->wqe_cnt);
}


static int sx_is_overflow(unsigned head, unsigned tail, int n)
{
    if ((int)(head - tail) >= n) {
        return -1;
    } else {
        return 0;
    }
}

int sx_flush_dq(struct sx_dev *dev, struct sx_dq *dq, bool update_flushing_state)
{
    int             err;
    unsigned long   flags;
    unsigned long   end;
    struct sx_priv *priv = sx_priv(dev);

    if (priv->dev_stuck) {
        return -ETIMEDOUT;
    }

    if (update_flushing_state) {
        dq->is_flushing = 1;
    }
    err = sx_dq_modify_2err(dev, dq);
    if (err) {
        sx_warn(dev, "Failed to modify dq to error. "
                "May cause resource leak\n");
        goto out_mod;
    }

    end = jiffies + 5 * HZ;
    spin_lock_irqsave(&dq->lock, flags);
    while ((dq->head != dq->tail) || !sx_is_cq_idle(dev, dq->cq->cqn)) {
        spin_unlock_irqrestore(&dq->lock, flags);
        msleep(1000 / HZ);
        if (time_after(jiffies, end)) {
            spin_lock_irqsave(&dq->lock, flags);

            sx_err(dev, "sx_core: Error: DQ flush timeout [dqn=%d, head=%u, tail=%u, is_monitor=%s, idle=%s]\n",
                   dq->dqn,
                   dq->head,
                   dq->tail,
                   (dq->is_monitor ? "true" : "false"),
                   (sx_is_cq_idle(dev, dq->cq->cqn) ? "true" : "false"));
            break;
        }

        spin_lock_irqsave(&dq->lock, flags);
    }

    if (update_flushing_state) {
        dq->is_flushing = 0;
    }

    spin_unlock_irqrestore(&dq->lock, flags);

    /* take control from hw */
    err = sx_hw2sw_dq(dev, dq);
    if (err) {
        sx_warn(dev, "hw2sw_dq failed (%d) "
                "for DQN %06x\n", err, dq->dqn);
    }


out_mod:
    return err;
}

int sx_add_pkts_to_sdq(struct sx_dq *sdq)
{
    struct sx_wqe    *wqe;
    int               err = 0;
    int               wqe_idx;
    struct sx_pkt    *curr_pkt;
    struct list_head *pos, *q;
    u8                arm = 0;

    list_for_each_safe(pos, q, &sdq->pkts_list.list_send_to_sdq) {
        curr_pkt = list_entry(pos, struct sx_pkt, list_send_to_sdq);
        list_del(pos);
        wqe_idx = sdq->head & (sdq->wqe_cnt - 1);
        wqe = sx_get_send_wqe(sdq, wqe_idx);

        wqe->flags = sx_set_wqe_flags(curr_pkt->set_lp, curr_pkt->type);
        err = sx_build_send_packet(sdq, curr_pkt->skb, wqe, wqe_idx);
        if (err) {
            sx_skb_free(curr_pkt->skb); /* drop packet flow, use kfree_skb */
            break;
        }

        curr_pkt->idx = wqe_idx;
        curr_pkt->since = jiffies;
        list_add_tail(&curr_pkt->list_wait_for_completion, &sdq->pkts_comp_list.list_wait_for_completion);
        sdq->pkts_sent_to_sdq++;
        sdq->pkts_in_sw_queue--;

        ++sdq->head;

        arm = 1;
        if (sx_dq_overflow(sdq)) {
            break; /* go to arm the db */
        }
    }

    if (arm) {
        /*
         * Make sure that descriptors are written before
         * doorbell.
         */
        wmb();

        __raw_writel((__force u32)cpu_to_be32(sdq->head & 0xffff),
                     sdq->db);
        MMIOWB();
    }
    return err;
}

int __sx_core_post_send(struct sx_dev *dev, struct sk_buff *skb, struct isx_meta *meta, u8 sdq_id)
{
    struct sx_priv *priv = sx_priv(dev);
    unsigned long   flags = 0;
    int             err = 0;
    struct sx_pkt  *new_pkt;
    struct sx_dq   *sdq = NULL;
    u8              sdqn;
    u8              stclass;
    u8              max_cpu_etclass_for_unlimited_mtu;
    u16             cap_max_mtu = 0;

    if (!dev || !priv->profile.pci_profile_set) {
        printk(KERN_WARNING PFX "__sx_core_post_send() cannot "
               "execute because the profile is not "
               "set\n");
        sx_skb_free(skb); /* drop packet flow, use kfree_skb */
        return -EFAULT;
    }

    if (priv->global_flushing) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING "__sx_core_post_send: Cannot send packet "
                   "while in global_flushing mode\n");
        }
        sx_skb_free(skb); /* drop packet flow, use kfree_skb */
        return -EFAULT;
    }

    if (NUMBER_OF_SWIDS <= meta->swid) {
        printk(KERN_WARNING "__sx_core_post_send: Cannot send packet on swid %u\n",
               meta->swid);
        sx_skb_free(skb); /* drop packet flow, use kfree_skb */
        return -EFAULT;
    }

    err = sx_get_sdq(meta, dev, meta->type, meta->swid,
                     meta->etclass, &stclass, &sdqn, &max_cpu_etclass_for_unlimited_mtu,
                     &cap_max_mtu);

    if (err) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "sx_core_post_send: error in callback structure sx_get_sdq for "
                   "selecting SDQ \n");
        }
        sx_skb_free(skb); /* drop packet flow, use kfree_skb */
        return -EFAULT;
    }
    if (DONT_FORCE_SDQ_ID == sdq_id) {
        sdq = sx_priv(dev)->sdq_table.dq[sdqn];
    } else {
        /* used for Health event mechanism (SDQ monitor)*/
        sdq = sx_priv(dev)->sdq_table.dq[sdq_id];
    }

    if (!sdq) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "sx_core_post_send: ERR: " \
                   "SDQ was not allocated\n");
        }
        sx_skb_free(skb); /* drop packet flow, use kfree_skb */
        return -EFAULT;
    }

    if (sdq->is_flushing == 1) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING "__sx_core_post_send: Cannot send packet on dqn [%u] "
                   "while in flushing mode\n", sdqn);
        }
        sx_skb_free(skb); /* drop packet flow, use kfree_skb */
        return -EFAULT;
    }

    if (skb->len > cap_max_mtu) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "%s: cannot send packet of size %u, "
                   "larger than max MTU %u\n", __func__, skb->len, cap_max_mtu);
        }
        sx_skb_free(skb); /* drop packet flow, use kfree_skb */
        return -EFAULT;
    }

    err = sx_build_isx_header(meta, skb, stclass);
    if (err) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "sx_core_post_send: "
                   "error in build header/stub\n");
        }
        sx_skb_free(skb); /* drop packet flow, use kfree_skb */
        return -EFAULT;
    }

    if ((skb->len > 2048) && (priv->profile.pci_profile.cpu_egress_tclass[sdqn] > max_cpu_etclass_for_unlimited_mtu)) {
        printk(KERN_ERR PFX "sx_core_post_send: cannot send packet of size %u "
               "from SDQ %u since it's bounded to cpu_tclass %u\n",
               skb->len, sdqn, priv->profile.pci_profile.cpu_egress_tclass[sdqn]);
        sx_skb_free(skb); /* drop packet flow, use kfree_skb */
        return -EFAULT;
    }

    /* send the packet also to the verification stub.
     * Since the verification environment doesn't yet support ETH L3
     * packets we don't pass them such packets. */
    if (tx_stub_func &&
        ((meta->type != SX_PKT_TYPE_ETH_DATA) &&
         (meta->type != SX_PKT_TYPE_ETH_CTL_UC))) {
        tx_stub_func(skb, 0);
    }

    new_pkt = kmalloc(sizeof(*new_pkt), GFP_ATOMIC);
    if (!new_pkt) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "sx_core_post_send: "
                   "error - cannot allocate packets memory\n");
        }
        sx_skb_free(skb); /* drop packet flow, use kfree_skb */
        return -ENOMEM;
    }

    new_pkt->skb = skb;
    new_pkt->set_lp = meta->lp;
    new_pkt->type = meta->type;

    spin_lock_irqsave(&sdq->lock, flags);
    if (sdq->pkts_in_sw_queue < SX_MAX_SDQ_SW_QUEUE_LEN) {
        list_add_tail(&new_pkt->list_send_to_sdq, &sdq->pkts_list.list_send_to_sdq);
        sdq->pkts_in_sw_queue++;
    } else {
        sx_skb_free(skb);   /* drop packet flow, use kfree_skb */
        kfree(new_pkt);
        sdq->pkts_sw_queue_drops++;

        if (printk_ratelimit()) {
            printk(KERN_NOTICE "SW queue for SDQ %u is full. dropping the packet!\n", sdq->dqn);
        }
        err = -EFAULT;
        goto out;
    }

    if (sx_dq_overflow(sdq)) {
        if ((sdq->last_full_queue != sdq->last_completion) &&
            (time_after_eq(jiffies, (sdq->last_completion + msecs_to_jiffies(SDQ_WATCHDOG_FULL_MSECS))))) {
            sdq->last_full_queue = sdq->last_completion;
            printk(KERN_ERR PFX "%s: sdq[%d] buffer is full for at least %d seconds\n",
                   __func__,
                   sdq->dqn,
                   SDQ_WATCHDOG_FULL_MSECS / 1000);
        }
        goto out;
    }

    if (dev->pdev) {
        err = sx_add_pkts_to_sdq(sdq);
    }

out:
    spin_unlock_irqrestore(&sdq->lock, flags);
    return err;
}

int sx_core_post_send(struct sx_dev *dev, struct sk_buff *skb, struct isx_meta *meta)
{
    struct sx_priv *priv = (dev != NULL) ? sx_priv(dev) : NULL;
    int             err = 0;

    /* WA for pad TX packets with size less than ETH_ZLEN */
    if (((meta->type == SX_PKT_TYPE_ETH_DATA) ||
         (meta->type == SX_PKT_TYPE_ETH_CTL_UC)) &&
        (skb->len < ETH_ZLEN)) {
        err = skb_pad(skb, ETH_ZLEN - skb->len);
        if (err) {
            sx_skb_free(skb);   /* drop packet flow, use kfree_skb */
            return err;
        }
        skb->len = ETH_ZLEN;
        skb_set_tail_pointer(skb, ETH_ZLEN);
    }

    sx_core_skb_hook_tx_call(dev, skb);

    if (tx_debug &&
        ((tx_debug_pkt_type == SX_DBG_PACKET_TYPE_ANY) ||
         (tx_debug_pkt_type == meta->type)) &&
        ((tx_debug_emad_type == SX_DBG_EMAD_TYPE_ANY) ||
         (tx_debug_emad_type ==
          be16_to_cpu(((struct sx_emad *)skb->data)->emad_op.register_id)))) {
        pr_debug(PFX "sx_core_post_send: Sending "
                 "pkt with meta: "
                 "et: %d , swid: %d , sysport:0x%x, rdq: %d,"
                 "to_cpu: %d, lp:%d, type: %d, dev_id: %d rx_is_router: %d "
                 "fid_valid: %d fid :%d, skb_headlen(skb):%d, skb_shinfo(skb)->nr_frags:%d  \n",
                 meta->etclass, meta->swid,
                 meta->system_port_mid,
                 meta->rdq, meta->to_cpu, meta->lp, meta->type,
                 meta->dev_id, meta->rx_is_router, meta->fid_valid, meta->fid,
                 skb_headlen(skb), skb_shinfo(skb)->nr_frags);


        if (tx_dump) {
            int i;
            u8 *buf = (void*)skb->data;
            int cnt = skb_headlen(skb);

            for (i = 0; i < cnt; i++) {
                if ((i == 0) || (i % 4 == 0)) {
                    printk(KERN_INFO "\n0x%04x : ", i);
                }

                printk(KERN_INFO " 0x%02x", buf[i]);
            }

            if (skb_shinfo(skb)->nr_frags) {
                skb_frag_t *frag = &skb_shinfo(skb)->frags[0];
                int         prev_size = cnt;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                buf = skb_frag_address(frag);
                cnt = skb_frag_size(frag);
#else
                buf = (void*)(lowmem_page_address(frag->page.p) + frag->page_offset);
                cnt = frag->size;
#endif
                for (i = 0; i < cnt; i++) {
                    if ((i == 0) || (i % 4 == 0)) {
                        printk(KERN_INFO "\n0x%04x : ", i + prev_size);
                    }

                    printk(KERN_INFO " 0x%02x", buf[i]);
                }

                if (skb_shinfo(skb)->nr_frags > 1) {
                    skb_frag_t *frag = &skb_shinfo(skb)->frags[1];

                    prev_size += cnt;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
                    buf = skb_frag_address(frag);
                    cnt = skb_frag_size(frag);
#else
                    buf = (void*)(lowmem_page_address(frag->page.p) + frag->page_offset);
                    cnt = frag->size;
#endif
                    for (i = 0; i < cnt; i++) {
                        if ((i == 0) || (i % 4 == 0)) {
                            printk(KERN_INFO "\n0x%04x : ", i + prev_size);
                        }

                        printk(KERN_INFO " 0x%02x", buf[i]);
                    }
                }
            }

            printk(KERN_INFO "\n");
        }

        if ((tx_dump_cnt != 0xFFFF) && (tx_dump_cnt > 0)) {
            tx_dump_cnt--;
        }

        if (tx_dump_cnt == 0) {
            tx_dump = 0;
            tx_debug = 0;
            tx_debug_pkt_type = 0xFF;
        }
    }

    if ((dev != NULL) && (meta->swid < NUMBER_OF_SWIDS)) {
        priv->stats.tx_by_pkt_type[meta->swid][meta->type]++;
        priv->stats.tx_by_pkt_type_bytes[meta->swid][meta->type] += skb->len;
    } else if (dev != NULL) {
        priv->stats.tx_by_pkt_type[NUMBER_OF_SWIDS][meta->type]++;
        priv->stats.tx_by_pkt_type_bytes[NUMBER_OF_SWIDS][meta->type] += skb->len;
    }

    if ((meta->type == SX_PKT_TYPE_DROUTE_EMAD_CTL) || /* emad */
        (meta->type == SX_PKT_TYPE_EMAD_CTL)) { /* emad */
        err = sx_dpt_send_emad(meta->dev_id, skb, meta);
    } else if ((meta->type == SX_PKT_TYPE_IB_TRANSPORT_CTL) ||
               (meta->type == SX_PKT_TYPE_IB_TRANSPORT_DATA)) { /* mad */
        err = sx_dpt_send_mad(meta->dev_id, skb, meta);
    } else if (is_sgmii_device(meta->dev_id)) {
        err = sgmii_send_misc(meta->dev_id, skb, meta);
        if (err) {
            sx_skb_free(skb);   /* drop packet flow, use kfree_skb */
        }
    } else if (dev && dev->pdev) {
        err = __sx_core_post_send(dev, skb, meta, DONT_FORCE_SDQ_ID);
    } else if (sx_cr_mode()) {
        err = sx_cr_send_packet(dev, skb, meta);
    } else {
        return -EFAULT;
    }

    return err;
}
EXPORT_SYMBOL(sx_core_post_send);

/*
 * Posts a buffer to the HW RDQ
 * The skb contains the kernel buffer address and length of the buffer.
 * Post recv maps the buffer to DMA memory and adds it to RDQ.
 */
void sx_core_post_recv(struct sx_dq *rdq, struct sk_buff *skb)
{
    unsigned long   flags;
    int             idx;
    struct sx_wqe  *wqe;
    struct sx_priv *priv = sx_priv(rdq->dev);
    int             length = priv->profile.pci_profile.rdq_properties[rdq->dqn].entry_size;

#ifdef CONFIG_44x
    int i;
#endif

    if (!priv->profile.pci_profile_set) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "sx_core_post_recv() cannot execute because the profile is not set\n");
        }

        return;
    }
    spin_lock_irqsave(&rdq->lock, flags);
    /* Sanity check - overflow should never happen here */
    if (sx_is_overflow(rdq->head, rdq->tail, rdq->wqe_cnt)) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "ERR: overflow in rdq, " \
                   "rdq->tail = %u, "
                   "rdq->head = %u\n", rdq->tail, rdq->head);
        }
        goto out;
    }
    idx = rdq->head & (rdq->wqe_cnt - 1);
    wqe = sx_get_wqe(rdq, idx << SX_WQE_SHIFT);
    memset(wqe, 0, sizeof *wqe);

    /*
     * If skb != NULL :
     *       - new skb will be post_received
     *
     * else (also case of Monitor RDQ) :
     *      - the same buffer will be reposted
     *      - The start of the buffer will not be filled by 0x55555555
     *        because the same buffer is used
     */
    if (skb != NULL) {
        rdq->sge[idx].skb = skb;
        rdq->sge[idx].hdr_pld_sg.vaddr = skb->data;
        rdq->sge[idx].hdr_pld_sg.len = length;


#ifdef CONFIG_44x
        /*
         *   (L1_CACHE_BYTES = 32)
         *   L2 corruption PPC460 Errata workaround :
         *   1. Turn on bit 27 in L2_CFG reg (made in drv init)
         *   2. Write to first word of each cache line of the
         *   posted buffer. This will cause to invalidate
         *   of L2 buffer
         */
        for (i = 0; i < rdq->sge[idx].hdr_pld_sg.len; i += L1_CACHE_BYTES) {
            *(u32*)(rdq->sge[idx].hdr_pld_sg.vaddr + i) = 0x55555555;
        }
#else
        *(u32*)(rdq->sge[idx].hdr_pld_sg.vaddr) = 0x55555555; /* Mark 1st 4 bytes */
#endif

        /* DMA_TODEVICE in order the marking will be written */
        rdq->sge[idx].hdr_pld_sg.dma_addr = dma_map_single(&rdq->dev->pdev->dev,
                                                           rdq->sge[idx].hdr_pld_sg.vaddr,
                                                           length, DMA_TO_DEVICE);
        if (dma_mapping_error(&rdq->dev->pdev->dev,
                              rdq->sge[idx].hdr_pld_sg.dma_addr)) {
            if (printk_ratelimit()) {
                printk(KERN_WARNING PFX "%s:%d: Err: "
                       "got dma_mapping error\n", __func__, __LINE__);
            }
            goto out;
        }
        dma_unmap_single(&rdq->dev->pdev->dev,
                         rdq->sge[idx].hdr_pld_sg.dma_addr,
                         length, DMA_TO_DEVICE);
    }

    rdq->sge[idx].hdr_pld_sg.dma_addr = dma_map_single(&rdq->dev->pdev->dev,
                                                       rdq->sge[idx].hdr_pld_sg.vaddr,
                                                       length, DMA_FROM_DEVICE);
    if (dma_mapping_error(&rdq->dev->pdev->dev,
                          rdq->sge[idx].hdr_pld_sg.dma_addr)) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "sx_core_post_recv: Err: "
                   "got dma_mapping error\n");
        }
        goto out;
    }

    wqe->dma_addr[0] =
        cpu_to_be64(rdq->sge[idx].hdr_pld_sg.dma_addr);
    wqe->byte_count[0] = cpu_to_be16(rdq->sge[idx].hdr_pld_sg.len);

    dma_sync_single_for_device(&rdq->dev->pdev->dev,
                               rdq->sge[idx].hdr_pld_sg.dma_addr,
                               rdq->sge[idx].hdr_pld_sg.len, DMA_FROM_DEVICE);

    rdq->head++;

    if (rdq->is_monitor) {
        rdq->mon_rx_count++;

        /*
         *  the window [mon_rx_start, mon_rx_start+mon_rx_cnt] should
         *  contains maximum wqe_cnt packets
         */
        if (rdq->mon_rx_count - rdq->mon_rx_start > rdq->wqe_cnt) {
            rdq->mon_rx_start++;
        }
    }

    /*
     * Make sure that descriptors are written before
     * doorbell.
     */
    wmb();

    __raw_writel((__force u32)cpu_to_be32(rdq->head & 0xffff), rdq->db);
    MMIOWB();
out:
    spin_unlock_irqrestore(&rdq->lock, flags);
}

/*
 * This function is used because we can't call kfree_skb on IB packets
 * which hold info in the nonlinear part of the SKB which was not
 * allocated by us, but was given to us by the user */
void __sx_skb_free(struct sk_buff *skb, int is_drop_pkt_flow)
{
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 10, 0))
    int i;
#endif

    if (!skb) {
        return;
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
    skb_shinfo(skb)->nr_frags = 0;
    skb_shinfo(skb)->frag_list = NULL;
#else
    for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
        skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
        frag->page.p = NULL;
        frag->page_offset = 0;
        frag->size = 0;
    }

    if (i) {
        skb_shinfo(skb)->nr_frags = 0;
        skb_shinfo(skb)->frag_list = NULL;
    }
#endif

    /* sx_skb_free is called from drop packet flow */
    if (is_drop_pkt_flow) {
        kfree_skb(skb);
    } else {
        consume_skb(skb);
    }
}

/*
 * This function is used because we can't call kfree_skb on IB packets
 * which hold info in the nonlinear part of the SKB which was not
 * allocated by us, but was given to us by the user */
void sx_skb_free(struct sk_buff *skb)
{
    __sx_skb_free(skb, 1);
}
EXPORT_SYMBOL(sx_skb_free);

/*
 * This function is used because we can't call kfree_skb on IB packets
 * which hold info in the nonlinear part of the SKB which was not
 * allocated by us, but was given to us by the user */
void sx_skb_consume(struct sk_buff *skb)
{
    __sx_skb_free(skb, 0);
}
EXPORT_SYMBOL(sx_skb_consume);


/************************************************
 * Create Functions                             *
 ***********************************************/

int sx_init_dq_table(struct sx_dev *dev, unsigned int ndqs, int send)
{
    struct sx_priv     *priv = sx_priv(dev);
    struct sx_dq_table *dq_table = NULL;
    struct sx_dq      **dq_array = NULL;
    int                 err = 0;
    int                 i = 0;
    unsigned long       flags;

    dq_table = ((send == true) ? &(priv->sdq_table) : &(priv->rdq_table));
    spin_lock_init(&dq_table->lock);

    dq_array = kzalloc(ndqs * sizeof(*dq_array), GFP_KERNEL);
    if (!dq_array) {
        return -ENOMEM;
    }
    for (i = 0; i < ndqs; i++) {
        dq_array[i] = NULL;
    }

    spin_lock_irqsave(&dq_table->lock, flags);
    dq_table->dq = dq_array;
    spin_unlock_irqrestore(&dq_table->lock, flags);

    err = sx_bitmap_init(&dq_table->bitmap, ndqs);

    return err;
}

int sx_core_init_sdq_table(struct sx_dev *dev)
{
    return sx_init_dq_table(dev, sx_priv(dev)->dev_cap.max_num_sdqs, true);
}

int sx_core_init_rdq_table(struct sx_dev *dev)
{
    return sx_init_dq_table(dev, sx_priv(dev)->dev_cap.max_num_rdqs, false);
}

int sx_hw2sw_dq(struct sx_dev *dev, struct sx_dq *dq)
{
    int err;

    err = sx_cmd(dev, dev->device_id, 0, dq->dqn & 0xffffff, !dq->is_send,
                 SX_CMD_HW2SW_DQ, SX_CMD_TIME_CLASS_A,
                 sx_priv(dev)->fw.local_in_mb_size);
    if (!err) {
        dq->state = DQ_STATE_ERROR;
    }

    return err;
}

int sx_dq_modify_2err(struct sx_dev *dev, struct sx_dq *dq)
{
    int err;

    err = sx_cmd(dev, dev->device_id, 0, dq->dqn, !dq->is_send,
                 SX_CMD_2ERR_DQ, SX_CMD_TIME_CLASS_A,
                 sx_priv(dev)->fw.local_in_mb_size);
    if (!err) {
        dq->state = DQ_STATE_ERROR;
    }

    return err;
}

int sx_sw2hw_dq(struct sx_dev *dev, struct sx_dq *dq)
{
    struct sx_priv        *priv = sx_priv(dev);
    struct sx_cmd_mailbox *mailbox;
    struct sx_dq_context  *context;
    int                    err = 0;
    int                    i;
    struct sk_buff        *skb = NULL;

    mailbox = sx_alloc_cmd_mailbox(dev, dev->device_id);
    if (IS_ERR(mailbox)) {
        err = PTR_ERR(mailbox);
        mailbox = NULL;
        goto out;
    }

    memset(mailbox->buf, 0, SX_MAILBOX_SIZE);
    context = mailbox->buf;
    context->cq = dq->cq->cqn;
    context->log2_dq_sz = ilog2(sx_nent_to_4k(dq->wqe_cnt));
    if (dq->is_send) {
        context->sdq_tclass = priv->profile.pci_profile.cpu_egress_tclass[dq->dqn];
    }

    if (dev->pdev) {
        sx_fill_page_list(context->dma_addr, &dq->buf);
    }

    err = sx_cmd(dev, dev->device_id, mailbox, dq->dqn & 0xffffff,
                 !dq->is_send, SX_CMD_SW2HW_DQ, SX_CMD_TIME_CLASS_A,
                 sx_priv(dev)->fw.local_in_mb_size);
    if (!err) {
        if (dev->pdev && !dq->is_send) {
            u16      size = priv->profile.pci_profile.rdq_properties[dq->dqn].entry_size;
            uint16_t nent = priv->profile.pci_profile.rdq_properties[dq->dqn].number_of_entries;
            for (i = 0; i < nent; i++) {
                skb = alloc_skb(size, GFP_KERNEL);
                if (!skb) {
                    err = -ENOMEM;
                    goto out;
                }

                if (skb_put(skb, size) == NULL) {
                    err = -ENOMEM;
                    goto out;
                }

                sx_core_post_recv(dq, skb);
            }
        }

        dq->state = DQ_STATE_RTS;
    }

out:
    if (mailbox) {
        sx_free_cmd_mailbox(dev, mailbox);
    }

    return err;
}

static int sx_dq_alloc(struct sx_dev *dev, u8 send, struct sx_dq *dq, u8 dqn)
{
    int                 err;
    int                 dq_base;
    unsigned long       flags;
    struct sx_priv     *priv = sx_priv(dev);
    struct sx_dq_table *dq_table = send ?
                                   &priv->sdq_table : &priv->rdq_table;

    dq->is_send = send;
    dq->dqn = sx_bitmap_set(&dq_table->bitmap, dqn);
    if (dq->dqn == -1) {
        return -ENOMEM;
    }

    dq->sge = kzalloc(dq->wqe_cnt * sizeof *dq->sge, GFP_KERNEL);
    if (!dq->sge) {
        err = -ENOMEM;
        goto err_out;
    }

    spin_lock_irqsave(&dq_table->lock, flags);
    dq_table->dq[dq->dqn] = dq;
    spin_unlock_irqrestore(&dq_table->lock, flags);
    atomic_set(&dq->refcount, 1);
    init_completion(&dq->free);
    init_waitqueue_head(&dq->tx_full_wait);
    dq_base = send ? SX_SEND_DQ_DB_BASE : SX_RECV_DQ_DB_BASE;
    dq->db = priv->db_base + dq_base + dq->dqn * 4;
    spin_lock_init(&dq->lock);
    dq->state = DQ_STATE_RESET;
    dq->dev = dev;
    if (send) {
        INIT_LIST_HEAD(&dq->pkts_list.list_send_to_sdq);
        INIT_LIST_HEAD(&dq->pkts_comp_list.list_wait_for_completion);
        dq->pkts_sent_to_sdq = 0;
        dq->pkts_recv_completion = 0;
        dq->pkts_late_completion = 0;
        dq->pkts_in_sw_queue = 0;
        dq->pkts_sw_queue_drops = 0;
        dq->max_comp_time = 0;
    }

    return 0;

err_out:
    kfree(dq->sge);
    sx_bitmap_free(&dq_table->bitmap, dq->dqn);

    return err;
}

static int sx_create_dq(struct sx_dev *dev, int nent, u8 dqn, struct sx_dq **dq, u8 send)
{
    struct sx_priv *priv = sx_priv(dev);
    int             ret;
    struct sx_dq   *tdq;
    struct sx_cq   *cq;
    int             cqn = send ? dqn : dqn + NUMBER_OF_SDQS;

    tdq = kzalloc(sizeof *tdq, GFP_KERNEL);
    if (!tdq) {
        printk(KERN_ERR "failed to allocate DQ (dqn=%d, is_send=%u)\n", dqn, send);
        return -ENOMEM;
    }

    ret = sx_core_create_cq(dev, (1 << priv->dev_cap.log_max_cq_sz),
                            &cq, cqn);
    if (ret < 0) {
        printk(KERN_ERR "failed to allocate CQ for DQ (dqn=%d, is_send=%u, err=%d)\n", dqn, send, ret);
        goto free_dq;
    }

    tdq->cq = cq;
    ret = sx_buf_alloc(dev, nent * sizeof(struct sx_wqe),
                       PAGE_SIZE, &tdq->buf, 0);
    if (ret) {
        printk(KERN_ERR "failed to allocate buffers for DQ (dqn=%d, is_send=%u, err=%d)\n", dqn, send, ret);
        ret = -ENOMEM;
        goto free_cq;
    }

    tdq->wqe_cnt = nent;
    ret = sx_dq_alloc(dev, send, tdq, dqn);
    if (ret) {
        printk(KERN_ERR "failed to allocate DQ elements (dqn=%d, is_send=%u, err=%d)\n", dqn, send, ret);
        goto free_buf;
    }

    tdq->state = DQ_STATE_RESET;
    tdq->is_flushing = 0;
    ret = sx_sw2hw_dq(dev, tdq);
    if (ret) {
        printk(KERN_ERR "failed to create DQ in HW (err=%d)\n", ret);
        goto free_buf;
    }

    *dq = tdq;
    return 0;

free_buf:
    sx_buf_free(dev, nent * sizeof(struct sx_wqe), &tdq->buf);
free_cq:
    sx_core_destroy_cq(dev, cq, tdq);
free_dq:
    kfree(tdq);
    return ret;
}

int sx_core_create_sdq(struct sx_dev *dev, int nent, u8 dqn, struct sx_dq **sdq_p)
{
    return sx_create_dq(dev, nent, dqn, sdq_p, 1);
}

int sx_core_create_rdq(struct sx_dev *dev, int nent, u8 dqn, struct sx_dq **rdq_p)
{
    return sx_create_dq(dev, nent, dqn, rdq_p, 0);
}

int sx_core_add_rdq_to_monitor_rdq_list(struct sx_dq *dq)
{
    int            is_found = 0, i;
    struct sx_dev *dev = dq->dev;

    /* add monitor rdq to the list if it wasn't existed in the list before */
    is_found = 0;
    for (i = 0; i < sx_priv(dev)->monitor_rdqs_count; i++) {
        if (sx_priv(dev)->monitor_rdqs_arr[i] == dq->dqn) {
            is_found = 1;
        }
    }

    if (!is_found && (sx_priv(dev)->monitor_rdqs_count == MAX_MONITOR_RDQ_NUM)) {
        return -EINVAL;
    }

    if (!is_found) {
        sx_priv(dev)->monitor_rdqs_arr[sx_priv(dev)->monitor_rdqs_count] = dq->dqn;
        sx_priv(dev)->monitor_rdqs_count++;
        sx_bitmap_set(&sx_priv(dev)->monitor_cq_bitmap, dq->cq->cqn);
    }

    return 0;
}

void sx_core_del_rdq_from_monitor_rdq_list(struct sx_dq *dq)
{
    int            i;
    struct sx_dev *dev = dq->dev;
    u32            monitor_rdqs_count = sx_priv(dev)->monitor_rdqs_count;

    /* remove monitor rdq from the list */
    for (i = 0; i < monitor_rdqs_count; i++) {
        if (sx_priv(dev)->monitor_rdqs_arr[i] == dq->dqn) {
            sx_bitmap_free(&(sx_priv(dev)->monitor_cq_bitmap), dq->cq->cqn);
            sx_bitmap_free(&(sx_priv(dev)->active_monitor_cq_bitmap), dq->cq->cqn);
            sx_priv(dev)->monitor_rdqs_arr[i] = sx_priv(dev)->monitor_rdqs_arr[monitor_rdqs_count - 1];
            sx_priv(dev)->monitor_rdqs_count--;
            sx_priv(dev)->monitor_rdqs_arr[monitor_rdqs_count - 1] = RDQ_INVALID_ID;
        }
    }

    sx_cq_arm(dq->cq);
}


/************************************************
 * Destroy Functions                            *
 ***********************************************/
static void sx_free_dq_sges(struct sx_dev *dev, struct sx_dq *dq)
{
    int i;

    for (i = 0; i < dq->wqe_cnt; ++i) {
        if (dq->sge[i].hdr_pld_sg.vaddr) {
            wqe_sync_for_cpu(dq, i);
            /* The destructor assumes the context of the user
             *  who sent the packet still exists, and we might
             *  get a kernel oops if the user already closed the FD */
            dq->sge[i].skb->destructor = NULL;
            sx_skb_consume(dq->sge[i].skb); /* free unused skb, use consume_skb */
        }
    }
}

static void sx_dq_free(struct sx_dev *dev, struct sx_dq *dq)
{
    struct list_head *pos, *q;
    struct sx_pkt    *tmp_pkt;

    if (atomic_dec_and_test(&dq->refcount)) {
        complete(&dq->free);
    }

    wait_for_completion(&dq->free);

    if (dq->is_send && !list_empty(&dq->pkts_list.list_send_to_sdq)) {
        list_for_each_safe(pos, q, &dq->pkts_list.list_send_to_sdq) {
            tmp_pkt = list_entry(pos, struct sx_pkt, list_send_to_sdq);
            list_del(pos);
            sx_skb_consume(tmp_pkt->skb);   /* free unused skb, use consume_skb */
            kfree(tmp_pkt);
        }
    }

    if (dq->is_send && !list_empty(&dq->pkts_comp_list.list_wait_for_completion)) {
        list_for_each_safe(pos, q, &dq->pkts_comp_list.list_wait_for_completion) {
            tmp_pkt = list_entry(pos, struct sx_pkt, list_wait_for_completion);
            list_del(pos);
            kfree(tmp_pkt);
        }
    }

    sx_free_dq_sges(dev, dq);
    kfree(dq->sge);
}

static void sx_dq_remove(struct sx_dev *dev, struct sx_dq *dq)
{
    struct sx_dq_table *dq_table = dq->is_send ?
                                   &sx_priv(dev)->sdq_table : &sx_priv(dev)->rdq_table;
    unsigned long flags;

    sx_bitmap_free(&dq_table->bitmap, dq->dqn);
    spin_lock_irqsave(&dq_table->lock, flags);
    dq_table->dq[dq->dqn] = NULL;
    spin_unlock_irqrestore(&dq_table->lock, flags);
}

static void sx_destroy_dq(struct sx_dev *dev, struct sx_dq *dq)
{
    /* set dq flushing state true for the entire flow to stop packets sending */
    dq->is_flushing = 1;

    /* before flushing a RDQ, increment its CQ reference count.
     * The reference count will be decremented when the CQ is done handling all buffers that were
     * punted to CPU on sx_dq_modify_2err().
     *
     * The waiting on sx_flush_dq() is not enough because when dq->head == dq->tail, the CQ may still
     * be iterating in sx_cq_completion().
     */
    if (!dq->is_send) {
        atomic_inc(&dq->cq->refcount);
    }

    sx_flush_dq(dev, dq, false);
    sx_core_destroy_cq(dev, dq->cq, dq);
    sx_dq_remove(dev, dq);
    sx_dq_free(dev, dq);
    sx_buf_free(dev, dq->wqe_cnt * sizeof(struct sx_wqe), &dq->buf);
    kfree(dq);
}

void sx_core_destroy_sdq(struct sx_dev *dev, struct sx_dq *dq)
{
    sx_destroy_dq(dev, dq);
}

void sx_core_destroy_rdq(struct sx_dev *dev, struct sx_dq *dq)
{
    sx_destroy_dq(dev, dq);
}

void sx_core_destroy_sdq_table(struct sx_dev *dev, u8 free_table)
{
    struct sx_priv     *priv = sx_priv(dev);
    struct sx_dq_table *sdq_table = &priv->sdq_table;
    int                 i;

    for (i = 0; i < priv->dev_cap.max_num_sdqs; i++) {
        if (sdq_table->dq[i]) {
            if (atomic_read(&sdq_table->dq[i]->refcount) == 1) {
                sx_core_destroy_sdq(dev, sdq_table->dq[i]);
            } else {
                atomic_dec(&sdq_table->dq[i]->refcount);
            }
        }
    }

    if (free_table) {
        kfree(sdq_table->dq);
    }
}

void sx_core_destroy_rdq_table(struct sx_dev *dev, u8 free_table)
{
    struct sx_priv     *priv = sx_priv(dev);
    struct sx_dq_table *rdq_table = &priv->rdq_table;
    int                 i;

    for (i = 0; i < priv->dev_cap.max_num_rdqs; i++) {
        if (rdq_table->dq[i]) {
            if (atomic_read(&rdq_table->dq[i]->refcount) == 1) {
                disable_monitor_rdq(dev, rdq_table->dq[i]->dqn, 1);
                sx_core_destroy_rdq(dev, rdq_table->dq[i]);
            } else {
                atomic_dec(&rdq_table->dq[i]->refcount);
            }
        }
    }

    if (free_table) {
        kfree(rdq_table->dq);
    }
}

/************************************************
 *                  EOF                         *
 ***********************************************/
