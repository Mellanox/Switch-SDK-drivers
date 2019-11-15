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

#include <linux/time.h>
#include <linux/mlx_sx/kernel_user.h>
#include <uapi/linux/if_arp.h>

#include "sgmii_internal.h"
#include "cq.h"
#include "sx.h"

extern int sx_core_dev_init_switchx_cb(struct sx_dev *dev, enum sxd_chip_types chip_type, bool force);
extern int sx_core_init_one(struct sx_priv **sx_priv);
extern void sx_core_remove_one(struct sx_priv *priv);

static DEFINE_RWLOCK(__sgmii_netdev_lock);
static struct net_device *__sgmii_netdev = NULL;
static char               __sgmii_netdev_name[SX_IFNAMSIZ] = "";
static atomic_t           __sgmii_rx_budget;
static void __sgmii_rate_limiter_cb(unsigned long data);
static DEFINE_TIMER(__sgmii_rate_limiter_timer, __sgmii_rate_limiter_cb, 0, 0);

static struct sx_priv *__sgmii_priv = NULL;
static void            (*handle_rx_by_cqe_version_cb)(struct sgmii_dev *sgmii_dev,
                                                      struct sk_buff   *skb,
                                                      struct timespec  *timestamp);
static u16 __sgmii_cqe_size;
struct sgmii_encapsulation_header_rx { /* Linux strips VLAN tag from frame before getting to RX handler */
    struct ethhdr eth_hdr;
    u16           ver_reserved;
} __attribute__((packed));
struct sgmii_rx_skb_cb {
#define SGMII_RX_SKB_CB_MAGIC (0xfee1600d)
    int               magic;
    struct sgmii_dev *sgmii_dev;
};

#define SGMII_RX_SKB_CB(skb)          ((struct sgmii_rx_skb_cb*)(skb)->cb)
#define IS_SGMII_RX_SKB_CB_VALID(skb) (SGMII_RX_SKB_CB(skb)->magic == SGMII_RX_SKB_CB_MAGIC)


struct pkt_type_attr {
    /* fields in TX base header version 0 */
    u32 type;
    u32 emad;
    u32 mc;
    u32 proto;
    u32 ctl;

    /* fields in control segment */
    u32 ctrl_type;

    /* PCP */
    u8 pcp;
};
static const struct pkt_type_attr __pkt_type_to_attr[] = {
    [SX_PKT_TYPE_ETH_CTL_UC] =
    { .type = 6, .emad = 0, .mc = 0, .proto = 1, .ctl = 0, .ctrl_type = 2, .pcp = SGMII_PCP_MED },

    [SX_PKT_TYPE_ETH_CTL_MC] =
    { .type = 6, .emad = 0, .mc = 1, .proto = 1, .ctl = 0, .ctrl_type = 2, .pcp = SGMII_PCP_MED },

    [SX_PKT_TYPE_ETH_DATA] =
    { .type = 0, .emad = 0, .mc = 0, .proto = 1, .ctl = 1, .ctrl_type = 2, .pcp = SGMII_PCP_LOW },

    [SX_PKT_TYPE_DROUTE_EMAD_CTL] =
    { .type = 6, .emad = 1, .mc = 0, .proto = 1, .ctl = 2, .ctrl_type = 2, .pcp = SGMII_PCP_HIGH },

    [SX_PKT_TYPE_EMAD_CTL] =
    { .type = 6, .emad = 1, .mc = 0, .proto = 1, .ctl = 0, .ctrl_type = 2, .pcp = SGMII_PCP_HIGH },

    [SX_PKT_TYPE_FC_CTL_UC] =
    { .type = 6, .emad = 0, .mc = 0, .proto = 1, .ctl = 0, .ctrl_type = 5, .pcp = SGMII_PCP_MED },

    [SX_PKT_TYPE_FC_CTL_MC] =
    { .type = 6, .emad = 0, .mc = 1, .proto = 1, .ctl = 0, .ctrl_type = 5, .pcp = SGMII_PCP_MED },

    [SX_PKT_TYPE_FCOE_CTL_UC] =
    { .type = 6, .emad = 0, .mc = 0, .proto = 1, .ctl = 0, .ctrl_type = 5, .pcp = SGMII_PCP_MED },

    [SX_PKT_TYPE_FCOE_CTL_MC] =
    { .type = 6, .emad = 0, .mc = 1, .proto = 1, .ctl = 0, .ctrl_type = 5, .pcp = SGMII_PCP_MED },

    [SX_PKT_TYPE_IB_RAW_CTL] =
    { .type = 6, .emad = 0, .mc = 0, .proto = 0, .ctl = 3, .ctrl_type = 0, .pcp = SGMII_PCP_MED },

    [SX_PKT_TYPE_IB_TRANSPORT_CTL] =
    { .type = 6, .emad = 0, .mc = 0, .proto = 0, .ctl = 3, .ctrl_type = 1, .pcp = SGMII_PCP_MED },

    [SX_PKT_TYPE_IB_RAW_DATA] =
    { .type = 0, .emad = 0, .mc = 0, .proto = 0, .ctl = 1, .ctrl_type = 0, .pcp = SGMII_PCP_LOW },

    [SX_PKT_TYPE_IB_TRANSPORT_DATA] =
    { .type = 0, .emad = 0, .mc = 0, .proto = 0, .ctl = 1, .ctrl_type = 1, .pcp = SGMII_PCP_LOW },

    [SX_PKT_TYPE_EOIB_CTL] =
    { .type = 6, .emad = 0, .mc = 0, .proto = 0, .ctl = 3, .ctrl_type = 6, .pcp = SGMII_PCP_MED },

    [SX_PKT_TYPE_FCOIB_CTL] =
    { .type = 6, .emad = 0, .mc = 0, .proto = 0, .ctl = 3, .ctrl_type = 4, .pcp = SGMII_PCP_MED },

    [SX_PKT_TYPE_LOOPBACK_CTL] =
    { .type = 0, .emad = 0, .mc = 0, .proto = 0, .ctl = 0, .ctrl_type = 0, .pcp = SGMII_PCP_FROM_METADATA }
};
static struct net_device        * __sgmii_get_netdev(void)
{
    struct net_device *netdev = NULL;

    read_lock_bh(&__sgmii_netdev_lock);
    if (__sgmii_netdev) {
        netdev = __sgmii_netdev;
        dev_hold(netdev);
    }
    read_unlock_bh(&__sgmii_netdev_lock);

    return netdev;
}

static void __sgmii_rx_skb_cb_init(struct sk_buff *skb, struct sgmii_dev *sgmii_dev)
{
    SGMII_RX_SKB_CB(skb)->magic = SGMII_RX_SKB_CB_MAGIC;
    SGMII_RX_SKB_CB(skb)->sgmii_dev = sgmii_dev;
}


int sgmii_rx_skb_cb_dev_id_get(struct sk_buff *skb, struct sgmii_dev **sgmii_dev)
{
    if (!IS_SGMII_RX_SKB_CB_VALID(skb)) {
        return -EPERM;
    }

    if (sgmii_dev) {
        *sgmii_dev = SGMII_RX_SKB_CB(skb)->sgmii_dev;
    }

    return 0;
}


static u8 __sgmii_meta_to_pcp(const struct isx_meta *meta)
{
    /* lowest priority for invalid meta */
    if (!meta || (meta->type < SX_PKT_TYPE_MIN) || (meta->type > SX_PKT_TYPE_MAX)) {
        return SGMII_PCP_BEST_EFFORT;
    }

    return __pkt_type_to_attr[meta->type].pcp;
}


void sgmii_fill_common_control_segment(const struct isx_meta *meta, struct sgmii_control_segment *control_seg)
{
    const struct pkt_type_attr *pkt_type_attr = &__pkt_type_to_attr[meta->type];
    u32                         lp;

    if (meta->lp) {
        lp = 1; /* out-of-band local process */
    } else {
        lp = 2; /* out-of-band forward to switch */
    }

    control_seg->line_0 = 0;
    __sgmii_bit_field_set(&control_seg->line_0,  20, 22, 0);                            /* swid          */
    __sgmii_bit_field_set(&control_seg->line_0,  19, 19, 0);                            /* ipcs          */
    __sgmii_bit_field_set(&control_seg->line_0,  18, 18, 0);                            /* dmc           */
    __sgmii_bit_field_set(&control_seg->line_0,  17, 17, 1);                            /* isx           */
    __sgmii_bit_field_set(&control_seg->line_0,  10, 16, 0);                            /* dr_tq         */
    __sgmii_bit_field_set(&control_seg->line_0,   7,  9, pkt_type_attr->ctrl_type);     /* ctrl seg type */
    __sgmii_bit_field_set(&control_seg->line_0,   2,  6, 0);                            /* send_flow     */
    __sgmii_bit_field_set(&control_seg->line_0,   0,  1, lp);                           /* lp            */
    CONVERT_TO_NETWORK_ORDER(control_seg->line_0);

    control_seg->line_1 = 0;
    __sgmii_bit_field_set(&control_seg->line_1,   0,  1, 0);                            /* cr_ver    */
    CONVERT_TO_NETWORK_ORDER(control_seg->line_1);

    control_seg->line_2 = 0; /* reserved (so it should not be converted to network order) */
    control_seg->line_3 = 0; /* reserved (so it should not be converted to network order) */
}


void sgmii_fill_common_tx_base_header(const struct isx_meta                 *meta,
                                      struct sgmii_tx_base_header_version_0 *tx_base_header)
{
    const struct pkt_type_attr *pkt_type_attr = &__pkt_type_to_attr[meta->type];

    tx_base_header->line_0 = 0;
    __sgmii_bit_field_set(&tx_base_header->line_0, 28, 31, 0);                       /* version               */
    __sgmii_bit_field_set(&tx_base_header->line_0, 26, 27, pkt_type_attr->ctl);      /* ctl                   */
    __sgmii_bit_field_set(&tx_base_header->line_0, 25, 25, 0);                       /* u/l                   */
    __sgmii_bit_field_set(&tx_base_header->line_0, 24, 24, pkt_type_attr->mc);       /* mc                    */
    __sgmii_bit_field_set(&tx_base_header->line_0, 21, 23, pkt_type_attr->proto);    /* protocol              */
    __sgmii_bit_field_set(&tx_base_header->line_0, 18, 20, 0);                       /* etclass               */
    __sgmii_bit_field_set(&tx_base_header->line_0, 16, 17, 0);                       /* drop_precedence       */
    __sgmii_bit_field_set(&tx_base_header->line_0, 12, 14, meta->swid);              /* swid                  */
    CONVERT_TO_NETWORK_ORDER(tx_base_header->line_0);

    tx_base_header->line_1 = 0;
    __sgmii_bit_field_set(&tx_base_header->line_1, 16, 31, meta->system_port_mid);   /* system_port_mid       */
    __sgmii_bit_field_set(&tx_base_header->line_1, 15, 15, 0);                       /* ingress_trap          */
    __sgmii_bit_field_set(&tx_base_header->line_1, 14, 14, 0);                       /* ctclass3              */
    __sgmii_bit_field_set(&tx_base_header->line_1,  9, 13, meta->rdq);               /* rdq                   */
    __sgmii_bit_field_set(&tx_base_header->line_1,  0,  8, 0);                       /* cpu_signature         */
    CONVERT_TO_NETWORK_ORDER(tx_base_header->line_1);

    tx_base_header->line_2 = 0;
    __sgmii_bit_field_set(&tx_base_header->line_2, 16, 31, 0);                       /* lag_sub_port          */
    __sgmii_bit_field_set(&tx_base_header->line_2,  0, 15, 0);                       /* rp_system_port_lag_id */
    CONVERT_TO_NETWORK_ORDER(tx_base_header->line_2);

    tx_base_header->line_3 = 0;
    __sgmii_bit_field_set(&tx_base_header->line_3, 16, 31, 0xe0e0);                  /* signature             */
    __sgmii_bit_field_set(&tx_base_header->line_3, 13, 15, 0);                       /* stclass               */
    __sgmii_bit_field_set(&tx_base_header->line_3,  6, 12, 0);                       /* local_source_port     */
    __sgmii_bit_field_set(&tx_base_header->line_3,  5,  5, pkt_type_attr->emad);     /* emad                  */
    __sgmii_bit_field_set(&tx_base_header->line_3,  4,  4, 0);                       /* src_lag               */
    __sgmii_bit_field_set(&tx_base_header->line_3,  0,  3, pkt_type_attr->type);     /* type                  */
    CONVERT_TO_NETWORK_ORDER(tx_base_header->line_3);
}


int sgmii_send(struct sgmii_dev               *sgmii_dev,
               struct sk_buff                 *skb,
               const struct isx_meta          *meta,
               u8                              pcp,
               sgmii_fill_control_segment_cb_t fill_control_segment_cb,
               sgmii_fill_tx_base_header_cb_t  fill_tx_base_header_cb)
{
    struct sgmii_tx_base_header_version_0 *tx_base_header;
    struct sgmii_control_segment          *control_seg;
    struct sgmii_encapsulation_header_tx  *encap_header;
    const struct ku_dpt_sgmii_info        *sgmii_dev_dpt_info;
    struct sk_buff                        *skb_send;
    struct net_device                     *netdev;
    int                                    err;

    if (!skb || !fill_control_segment_cb) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, tx_invalid_argument);
        return -EINVAL;
    }

    if (meta && ((meta->type < SX_PKT_TYPE_MIN) || (meta->type > SX_PKT_TYPE_MAX))) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, tx_invalid_metadata);
        return -EINVAL;
    }

    netdev = __sgmii_get_netdev();
    if (!netdev) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, tx_sgmii_not_initialized);
        return -ENONET;
    }

    if (tx_debug) {
        printk(KERN_DEBUG PFX
               "%s: Sending pkt with meta: "
               "et: %d , swid: %d , sysport:0x%x, rdq: %d,"
               "to_cpu: %d, lp:%d, type: %d, dev_id: %d rx_is_router: %d "
               "fid_valid: %d fid :%d, skb_headlen(skb):%d, skb_shinfo(skb)->nr_frags:%d\n",
               __FUNCTION__, meta->etclass, meta->swid, meta->system_port_mid, meta->rdq, meta->to_cpu, meta->lp,
               meta->type, meta->dev_id, meta->rx_is_router, meta->fid_valid, meta->fid, skb_headlen(skb),
               skb_shinfo(skb)->nr_frags);
    }

    if (skb_is_nonlinear(skb)) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, tx_skb_fragmented);
        skb_send = skb_copy(skb, GFP_ATOMIC);
    } else {
        skb_send = skb_clone(skb, GFP_ATOMIC);
    }

    if (!skb_send) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, tx_skb_clone_failed);
        err = -ENOMEM;
        goto release_netdev;
    }

    err = skb_cow(skb_send,
                  sizeof(struct sgmii_encapsulation_header_tx) +
                  sizeof(struct sgmii_control_segment) +
                  (fill_tx_base_header_cb ? sizeof(struct sgmii_tx_base_header_version_0) : 0));
    if (err) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, tx_skb_cow_failed);
        goto out;
    }

    sgmii_dev_dpt_info = sgmii_dev_get_dpt_info(sgmii_dev);
    if (pcp == SGMII_PCP_FROM_METADATA) {
        pcp = __sgmii_meta_to_pcp(meta);
    }

    /* --------------------------------------------------- */
    /* build TX base header                                */
    /* --------------------------------------------------- */
    if (fill_tx_base_header_cb) {
        skb_push(skb_send, sizeof(struct sgmii_tx_base_header_version_0));
        tx_base_header = (struct sgmii_tx_base_header_version_0*)skb_send->data;
        fill_tx_base_header_cb(meta, tx_base_header);
    }

    /* --------------------------------------------------- */
    /* build control segment                               */
    /* --------------------------------------------------- */
    skb_push(skb_send, sizeof(struct sgmii_control_segment));
    control_seg = (struct sgmii_control_segment*)skb_send->data;
    fill_control_segment_cb(meta, control_seg);

    /* build encapsulation header */
    skb_push(skb_send, sizeof(struct sgmii_encapsulation_header_tx));
    encap_header = (struct sgmii_encapsulation_header_tx*)skb_send->data;
    memcpy(encap_header->eth_vlan_hdr.h_dest, sgmii_dev_dpt_info->dmac, 6);
    memcpy(encap_header->eth_vlan_hdr.h_source, netdev->dev_addr, 6);
    encap_header->eth_vlan_hdr.h_vlan_proto = htons(ETH_P_8021Q);
    encap_header->eth_vlan_hdr.h_vlan_TCI = htons(pcp << 13);
    encap_header->eth_vlan_hdr.h_vlan_TCI |= htons(sgmii_dev_dpt_info->vid);
    encap_header->eth_vlan_hdr.h_vlan_encapsulated_proto = htons(ETHTYPE_EMAD);
    encap_header->ver_reserved = 0;

    if (tx_dump) {
        printk(KERN_ERR "TX buffer [size=%d]\n", skb_send->len);
        print_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 16, 1, skb_send->data, skb_send->len, 0);
    }

    skb_send->dev = netdev;

    if (!netif_carrier_ok(netdev)) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, tx_netdev_carrier_down);
        err = -ENETDOWN;
        goto out;
    }

    if (skb_send->len > netdev->mtu) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, tx_exceeds_mtu);
        err = -EMSGSIZE;
        goto out;
    }

    err = dev_queue_xmit(skb_send);
    if (err) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, tx_dev_queue_xmit_failed);

        if (err == -ENETDOWN) { /* in this case, dev_queue_xmit() already called kfree_skb() */
            goto release_netdev;
        }

        goto out;
    }

    SGMII_DEV_INC_COUNTER(sgmii_dev, tx_ok);
    goto release_netdev;

out:
    kfree_skb(skb_send);

release_netdev:
    dev_put(netdev);
    return err;
}


int sgmii_send_misc(int dev_id, struct sk_buff *skb, const struct isx_meta *meta)
{
    struct sgmii_dev *sgmii_dev;
    int               ret;

    ret = sgmii_dev_get_by_id(dev_id, &sgmii_dev);
    if (ret) {
        COUNTER_INC(&__sgmii_global_counters.tx_not_sgmii_dev);
        goto out;
    }

    SGMII_DEV_INC_COUNTER(sgmii_dev, misc_tx);

    ret = sgmii_send(sgmii_dev,
                     skb,
                     meta,
                     SGMII_PCP_FROM_METADATA,
                     sgmii_fill_common_control_segment,
                     sgmii_fill_common_tx_base_header);

    if (ret) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, misc_send_failed);
    }

    sgmii_dev_dec_ref(sgmii_dev);

out:

    /* no matter what, we free original skb so it will activate its destructor (just like with PCI) */
    sx_skb_free(skb);
    return ret;
}


static void __handle_rx_by_cqe_version_v0(struct sgmii_dev *sgmii_dev, struct sk_buff *skb, struct timespec *timestamp)
{
    struct sx_cqe_v0 cqe_v0;
    union sx_cqe     cqe = {
        .v0 = &cqe_v0
    };
    int              err;

    memcpy(&cqe_v0, skb->data, sizeof(cqe_v0));
    skb_pull(skb, sizeof(cqe_v0));

    err = rx_skb(&__sgmii_priv->dev, skb, &cqe, timestamp, 0, NULL);
    if (err) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, rx_cqev0_handler_failed);
    } else {
        SGMII_DEV_INC_COUNTER(sgmii_dev, rx_cqev0_ok);
    }
}


static void __handle_rx_by_cqe_version_v2(struct sgmii_dev *sgmii_dev, struct sk_buff *skb, struct timespec *timestamp)
{
    struct sx_cqe_v2 cqe_v2;
    union sx_cqe     cqe = {
        .v2 = &cqe_v2
    };
    int              err;

    memcpy(&cqe_v2, skb->data, sizeof(cqe_v2));
    skb_pull(skb, sizeof(cqe_v2));

    err = rx_skb(&__sgmii_priv->dev, skb, &cqe, timestamp, 0, NULL);
    if (err) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, rx_cqev2_handler_failed);
    } else {
        SGMII_DEV_INC_COUNTER(sgmii_dev, rx_cqev2_ok);
    }
}


static rx_handler_result_t __sgmii_rx_handler(struct sk_buff **pskb)
{
    const struct sgmii_encapsulation_header_rx *encap_header;
    const struct ku_dpt_sgmii_info             *sgmii_dev_dpt_info;
    struct timespec                             timestamp;
    struct sk_buff                             *skb = *pskb;
    struct sgmii_dev                           *sgmii_dev;
    int                                         err;

    if (atomic_dec_return(&__sgmii_rx_budget) < 0) {
        /* just count, do not drop! */
        COUNTER_INC(&__sgmii_global_counters.rx_rate_limiter);
    }

    getnstimeofday(&timestamp);

    skb = skb_share_check(skb, GFP_ATOMIC);
    if (!skb) {
        COUNTER_INC(&__sgmii_global_counters.rx_skb_share_check_failed);
        return RX_HANDLER_CONSUMED;
    }

    if (skb_is_nonlinear(skb)) {
        COUNTER_INC(&__sgmii_global_counters.rx_skb_fragmented);
        if (rx_debug) {
            printk(KERN_INFO "skb is fragmented: nr_frags=%d, data_len=%u\n",
                   skb_shinfo(skb)->nr_frags, skb->data_len);
        }
    }

    if (!skb_mac_header_was_set(skb)) {
        COUNTER_INC(&__sgmii_global_counters.rx_no_encap_header);
        goto drop_skb;
    }

    /* place skb->data on the MAC header */
    skb_push(skb, skb->data - skb_mac_header(skb));

    err = skb_linearize(skb);
    if (err) {
        COUNTER_INC(&__sgmii_global_counters.rx_skb_linearize_failed);
        goto drop_skb;
    }

    if (rx_dump) {
        printk(KERN_ERR "RX buffer [data=%p, size=%d]\n", skb->data, skb->len);
        print_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 16, 1, skb->data, skb->len, 0);
    }

    if (!pskb_may_pull(skb, sizeof(struct sgmii_encapsulation_header_rx))) {
        COUNTER_INC(&__sgmii_global_counters.rx_no_encap_header);
        goto drop_skb;
    }

    encap_header = (struct sgmii_encapsulation_header_rx*)skb->data;
    if (ZERO_MAC(encap_header->eth_hdr.h_source)) {
        COUNTER_INC(&__sgmii_global_counters.rx_zero_src_mac);
        goto drop_skb;
    }

    err = sgmii_dev_get_by_mac(encap_header->eth_hdr.h_source, &sgmii_dev);
    if (err) {
        COUNTER_INC(&__sgmii_global_counters.rx_src_mac_not_found);
        goto drop_skb;
    }

    __sgmii_rx_skb_cb_init(skb, sgmii_dev);
    sgmii_dev_dpt_info = sgmii_dev_get_dpt_info(sgmii_dev);

#ifdef vlan_tx_tag_present
    if (!vlan_tx_tag_present(skb)) {
#else
    if (!skb_vlan_tag_present(skb)) {
#endif
        SGMII_DEV_INC_COUNTER(sgmii_dev, rx_untagged_frame);
        goto dec_dev_refcnt;
    }

#ifdef vlan_tx_tag_get
    if (sgmii_dev_dpt_info->vid != (vlan_tx_tag_get(skb) & VLAN_VID_MASK)) { /* not an error but let's count it */
#else
    if (sgmii_dev_dpt_info->vid != (skb_vlan_tag_get(skb) & VLAN_VID_MASK)) { /* not an error but let's count it */
#endif
        SGMII_DEV_INC_COUNTER(sgmii_dev, rx_warn_vlan_mismatch);
    }

    if (ntohs(encap_header->eth_hdr.h_proto) != ETHTYPE_EMAD) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, rx_invalid_ethertype);
        goto dec_dev_refcnt;
    }

    skb_pull(skb, sizeof(struct sgmii_encapsulation_header_rx));

    if (!pskb_may_pull(skb, __sgmii_cqe_size)) {
        SGMII_DEV_INC_COUNTER(sgmii_dev, rx_cqe_trimmed);
        goto dec_dev_refcnt;
    }

    if (sgmii_cr_space_check_for_response(sgmii_dev, skb)) { /* 0 = no CR response, 1 = CR response */
        goto dec_dev_refcnt;
    }

    handle_rx_by_cqe_version_cb(sgmii_dev, skb, &timestamp);
    skb = NULL; /* kfree_skb() (a few lines ahead) will do nothing then :) */

dec_dev_refcnt:
    sgmii_dev_dec_ref(sgmii_dev);

drop_skb:
    kfree_skb(skb);
    return RX_HANDLER_CONSUMED;
}


static void __sgmii_rate_limiter_cb(unsigned long data)
{
    atomic_set(&__sgmii_rx_budget, sgmii_get_rx_pps());
    mod_timer(&__sgmii_rate_limiter_timer, jiffies + HZ);
}


int sgmii_get_operational_rx_pps(void)
{
    int rx_pps = atomic_read(&__sgmii_rx_budget);

    if (rx_pps < 0) {
        rx_pps = 0;
    }

    return rx_pps;
}


const char * sgmii_get_netdev_name(void)
{
    return __sgmii_netdev_name;
}


int sgmii_get_netdev_mac(uint8_t *netdev_mac)
{
    struct net_device *netdev;
    int                err = -ENODEV;

    netdev = __sgmii_get_netdev();
    if (netdev) {
        memcpy(netdev_mac, netdev->dev_addr, 6);
        dev_put(netdev);
        err = 0;
    }

    return err;
}


static void __sgmii_dev_removed_cb(void *context)
{
    sgmii_transport_deinit();
}


static int __netdev_notify_cb(struct notifier_block *this, unsigned long event, void *context)
{
    const struct net_device *netdev_notif = (struct net_device*)context;
    struct net_device       *sgmii_netdev;

    sgmii_netdev = __sgmii_get_netdev();
    if (!sgmii_netdev) {
        goto out;
    }

    if ((event == NETDEV_UNREGISTER) && (netdev_notif == sgmii_netdev)) {
        printk(KERN_NOTICE "SGMII network link is being removed!\n");
        sgmii_queue_task(__sgmii_dev_removed_cb, NULL, 0, 0);
    }

    dev_put(sgmii_netdev);

out:
    return NOTIFY_DONE;
}


static struct notifier_block __netdev_notify = {
    __netdev_notify_cb,
    NULL,
    0
};


int sgmii_transport_init(const char       *netdev_name,
                         const uint8_t    *netdev_mac,
                         ku_chassis_type_t chassis_type,
                         uint8_t           cqe_ver)
{
    struct sockaddr     sa_hwaddr;
    enum sxd_chip_types chip_type;
    struct net_device  *netdev;
    int                 ret;

    netdev = __sgmii_get_netdev();
    if (netdev) {
        dev_put(netdev);
        return -EEXIST;
    }

    if (!netdev_name || (netdev_name[0] == '\0')) {
        printk(KERN_ERR "SGMII network's netdev name is empty\n");
        return -EINVAL;
    }

    switch (chassis_type) {
    case KU_CHASSIS_TYPE_BARRACUDA:
        chip_type = SXD_CHIP_TYPE_SWITCH_IB2;
        break;

    case KU_CHASSIS_TYPE_MANTARAY:
        chip_type = SXD_CHIP_TYPE_QUANTUM;
        break;

    default:
        printk(KERN_ERR "cannot initialize transport with invalid chassis type!\n");
        return -EINVAL;
    }

    if (cqe_ver == 0) {
        handle_rx_by_cqe_version_cb = __handle_rx_by_cqe_version_v0;
        __sgmii_cqe_size = sizeof(struct sx_cqe_v0);
    } else { /* cqe_ver == 2 */
        handle_rx_by_cqe_version_cb = __handle_rx_by_cqe_version_v2;
        __sgmii_cqe_size = sizeof(struct sx_cqe_v2);
    }

    __sgmii_priv = sx_priv(sx_glb.tmp_dev_ptr);
    ret = sx_core_dev_init_switchx_cb(&__sgmii_priv->dev, chip_type, 1);
    if (ret) {
        printk(KERN_ERR "failed to initialize per-chip-type callbacks (ret=%d)\n", ret);
        goto error;
    }

    netdev = dev_get_by_name(&init_net, netdev_name);
    if (!netdev) {
        printk(KERN_ERR "SGMII network's netdev '%s' was not found\n", netdev_name);
        ret = -ENODEV;
        goto error;
    }

    register_netdevice_notifier(&__netdev_notify);

    sa_hwaddr.sa_family = ARPHRD_ETHER;
    memcpy(sa_hwaddr.sa_data, netdev_mac, 6);

    rtnl_lock();

    ret = dev_set_mac_address(netdev, &sa_hwaddr);
    if (ret) {
        printk(KERN_ERR "Failed to set MAC address of SGMII netdev (err=%d)\n", ret);
    } else {
        ret = netdev_rx_handler_register(netdev, __sgmii_rx_handler, NULL);
        if (ret) {
            printk(KERN_ERR "Failed to enslave SGMII netdev to sx_core (err=%d)\n", ret);
        }
    }

    rtnl_unlock();

    if (ret) {
        goto error;
    }

    write_lock_bh(&__sgmii_netdev_lock);
    __sgmii_netdev = netdev;
    write_unlock_bh(&__sgmii_netdev_lock);

    __sgmii_rate_limiter_cb(0);
    strncpy(__sgmii_netdev_name, netdev_name, sizeof(__sgmii_netdev_name));
    return 0;

error:

    __sgmii_priv = NULL;
    return ret;
}


void sgmii_transport_deinit(void)
{
    struct net_device *netdev = NULL;

    write_lock_bh(&__sgmii_netdev_lock);
    if (__sgmii_netdev) { /* check if sgmii transport was initialized ... */
        netdev = __sgmii_netdev;
        __sgmii_netdev = NULL;
    }
    write_unlock_bh(&__sgmii_netdev_lock);

    if (!netdev) {
        return;
    }

    unregister_netdevice_notifier(&__netdev_notify);

    printk(KERN_NOTICE "Deinitializing SGMII transport!\n");

    rtnl_lock();
    netdev_rx_handler_unregister(netdev);
    rtnl_unlock();

    dev_put(netdev);

    del_timer_sync(&__sgmii_rate_limiter_timer);
    __sgmii_priv = NULL;
}
