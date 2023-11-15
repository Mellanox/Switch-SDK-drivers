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

#include <linux/mlx_sx/cmd.h>

#include "sx.h"
#include "cq.h"
#include "sx_clock.h"
#include "ptp.h"
#include "dev_callbacks.h"
#include "dev_db.h"
#include "synce.h"

extern int tx_debug;

#define MAX_ROUTER_MID_TABLE_SIZE 0xffff
#define MAX_IB_PORT               65

#define SX_CORE_PHY_PORT_NUM_MAX           64
#define SX_CORE_PHY_PORT_NUM_QUANTUM_MAX   80
#define SX_CORE_PHY_PORT_NUM_QUANTUM2_MAX  128
#define SX_CORE_PHY_PORT_NUM_QUANTUM3_MAX  144
#define SX_CORE_PHY_PORT_NUM_SPECTRUM2_MAX 128
#define SX_CORE_PHY_PORT_NUM_SPECTRUM4_MAX 258

#define SX_CORE_LAG_NUM_MAX           64
#define SX_CORE_LAG_NUM_SPECTRUM2_MAX 128
#define SX_CORE_LAG_NUM_SPECTRUM4_MAX 256

#define SX_CORE_PORTS_PER_LAG_NUM_MAX           32
#define SX_CORE_PORTS_PER_LAG_NUM_SPECTRUM2_MAX 64
#define SX_CORE_PORTS_PER_LAG_NUM_SPECTRUM4_MAX 128

/* The following defines are used in the chip specific
 * callback functions to get the correct number of RDQ
 * (Receive descriptor queues) for the relevant chip
 * in respect with the PRM.
 * Please refer cap_max_num_rdq.
 */
#define RDQ_NUM_MAX      37
#define RDQ_NUM_MAX_SPC2 56

#define SX_CORE_DEV_CB_FINISH_WAIT_TIMEOUT (30 * HZ)

static int __sx_core_get_hw_etclass_impl(struct isx_meta *meta, u8* hw_etclass)
{
    /* According to the SX PRM
     * etclass should be set to the following value: (7 - Egress Tclass) */

    *hw_etclass = 7 - meta->etclass;

    return 0;
}

static void __get_specific_data(enum ku_pkt_type type, u8 to_cpu, u8 etclass, u8 lp, struct isx_specific_data *data)
{
    if ((type == SX_PKT_TYPE_ETH_DATA) || (type == SX_PKT_TYPE_IB_RAW_DATA)
        || (type == SX_PKT_TYPE_IB_TRANSPORT_DATA /*&& !lp*/) || (type == SX_PKT_TYPE_IB_NVLINK)) {
        data->type = 0;
    } else if (type == SX_PKT_TYPE_IB_CTL_2) {
        data->type = 5;
    } else {
        data->type = 6;
    }
    if ((type == SX_PKT_TYPE_DROUTE_EMAD_CTL) || (type == SX_PKT_TYPE_EMAD_CTL)) {
        data->emad = 1;
    } else {
        data->emad = 0;
    }
    if ((type == SX_PKT_TYPE_ETH_CTL_MC) || (type == SX_PKT_TYPE_FC_CTL_MC)
        || (type == SX_PKT_TYPE_FCOE_CTL_MC)) {
        data->mc = 1;
    } else {
        data->mc = 0;
    }
    if (type >= SX_PKT_TYPE_IB_RAW_CTL) {
        data->protocol = PROTOCOL_INFINIBAND;
    } else {
        data->protocol = PROTOCOL_ETHERNET;
    }

    switch (type) {
    case SX_PKT_TYPE_ETH_CTL_UC:
    case SX_PKT_TYPE_ETH_CTL_MC:
    case SX_PKT_TYPE_EMAD_CTL:
    case SX_PKT_TYPE_FC_CTL_UC:
    case SX_PKT_TYPE_FC_CTL_MC:
    case SX_PKT_TYPE_FCOE_CTL_UC:
    case SX_PKT_TYPE_FCOE_CTL_MC:
        data->ctl = CTL_ETH_CONTROL;
        break;

    case SX_PKT_TYPE_ETH_DATA:
    case SX_PKT_TYPE_IB_RAW_DATA:
    case SX_PKT_TYPE_IB_TRANSPORT_DATA:
        data->ctl = CTL_DATA;
        break;

    case SX_PKT_TYPE_DROUTE_EMAD_CTL:
        data->ctl = CTL_ETH_DR_EMADS;
        break;

    case SX_PKT_TYPE_IB_RAW_CTL:
    case SX_PKT_TYPE_IB_TRANSPORT_CTL:
    case SX_PKT_TYPE_EOIB_CTL:
    case SX_PKT_TYPE_FCOIB_CTL:
    case SX_PKT_TYPE_IB_CTL_2:
    case SX_PKT_TYPE_IB_NVLINK:
        data->ctl = CTL_IB_CONTROL;
        break;

    default:
        break;
    }

    if (to_cpu) {
        data->ctclass = (etclass & 0x8) >> 3;
    } else {
        data->ctclass = 0;
    }

    data->cpu_signature = 0;
    data->signature = 0xE0E0;
}

/**
 * Build isx_header from the given meta (meta-data) and push the isx_headr
 * to the beginning of the skb (before the pkt-buffer part) for Version 0
 */
static int __sx_build_isx_header_v0(struct isx_meta *meta, struct sk_buff *skb, u8 stclass, u8 hw_etclass)
{
    struct tx_base_header_v0 *p_hdr;
    struct isx_specific_data  specific_meta;

    p_hdr = (struct tx_base_header_v0 *)skb_push(skb, ISX_HDR_SIZE);
    if (p_hdr == NULL) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "sx_build_isx_header: "
                   "Error in skb_push\n");
        }
        return -ENOMEM;
    }

    memset(p_hdr, 0, sizeof(*p_hdr));
    memset(&specific_meta, 0, sizeof(specific_meta));
    __get_specific_data(meta->type, meta->to_cpu,
                        meta->etclass, meta->lp, &specific_meta);
    p_hdr->ctl_mc |=
        TO_FIELD(TX_HDR_CTL_MASK,
                 TX_HDR_CTL_SHIFT, specific_meta.ctl);
    p_hdr->ctl_mc |=
        TO_FIELD(TX_HDR_MC_MASK,
                 TX_HDR_MC_SHIFT, specific_meta.mc);
    p_hdr->protocol_etclass |=
        TO_FIELD(TX_HDR_PROTOCOL_MASK,
                 TX_HDR_PROTOCOL_SHIFT,
                 specific_meta.protocol);
    p_hdr->protocol_etclass |=
        TO_FIELD(TX_HDR_ETCLASS_MASK,
                 TX_HDR_ETCLASS_SHIFT, hw_etclass);
    p_hdr->swid |= (u16)TO_FIELD(TX_HDR_SWID_MASK,
                                 TX_HDR_SWID_SHIFT, meta->swid);
    p_hdr->swid = cpu_to_be16(p_hdr->swid);
    p_hdr->system_port_mid |=
        (u16)TO_FIELD(TX_HDR_SYSTEM_PORT_MID_MASK,
                      TX_HDR_SYSTEM_PORT_MID_SHIFT,
                      meta->system_port_mid);
    p_hdr->system_port_mid = cpu_to_be16(p_hdr->system_port_mid);
    p_hdr->ctclass3_rdq_cpu_signature |=
        (u16)TO_FIELD(TX_HDR_CTCLASS3_MASK,
                      TX_HDR_CTCLASS3_SHIFT,
                      specific_meta.ctclass);
    p_hdr->ctclass3_rdq_cpu_signature |=
        (u16)TO_FIELD(TX_HDR_RDQ_MASK,
                      TX_HDR_RDQ_SHIFT, meta->rdq);
    p_hdr->ctclass3_rdq_cpu_signature |=
        (u16)TO_FIELD(TX_HDR_CPU_SIGNATURE_MASK,
                      TX_HDR_CPU_SIGNATURE_SHIFT,
                      specific_meta.cpu_signature);
    p_hdr->ctclass3_rdq_cpu_signature =
        cpu_to_be16(p_hdr->ctclass3_rdq_cpu_signature);
    p_hdr->signature |=
        (u16)TO_FIELD(TX_HDR_SIGNATURE_MASK,
                      TX_HDR_SIGNATURE_SHIFT,
                      specific_meta.signature);
    p_hdr->signature = cpu_to_be16(p_hdr->signature);
    p_hdr->stclass_emad_type |=
        (u16)TO_FIELD(TX_HDR_STCLASS_MASK,
                      TX_HDR_STCLASS_SHIFT, stclass);
    p_hdr->stclass_emad_type |=
        (u16)TO_FIELD(TX_HDR_EMAD_MASK,
                      TX_HDR_EMAD_SHIFT, specific_meta.emad);
    p_hdr->stclass_emad_type |=
        (u16)TO_FIELD(TX_HDR_TYPE_MASK,
                      TX_HDR_TYPE_SHIFT, specific_meta.type);
    p_hdr->stclass_emad_type = cpu_to_be16(p_hdr->stclass_emad_type);
    if (tx_debug) {
        pr_debug(PFX "sx_core_post_send: Sending for version 0 "
                 "pkt with specific meta: "
                 "sysport:0x%x, specific_meta.ctl: %d,"
                 "specific_meta.protocol: %d\n",
                 meta->system_port_mid,
                 specific_meta.ctl, specific_meta.protocol);
    }
    return 0;
}

static void __get_specific_data_version_1(enum ku_pkt_type          type,
                                          u8                        to_cpu,
                                          u8                        etclass,
                                          u8                        lp,
                                          u8                        rx_is_router,
                                          u8                        fid_valid,
                                          u16                       fid,
                                          u8                        rx_is_tunnel,
                                          struct isx_specific_data *data)
{
    switch (type) {
    case SX_PKT_TYPE_ETH_CTL_UC:
    case SX_PKT_TYPE_ETH_CTL_MC:
        data->type = 6;
        data->protocol = 1;
        data->ctl = 0;
        data->use_control_tclass = 1;
        data->etclass = 0; /* When control_tclass = 1, this field is reserved */
        data->fid = 0;
        data->fid_valid = 0;
        data->rx_is_router = 0;
        break;

    case SX_PKT_TYPE_ETH_DATA:
        data->type = 0;
        data->protocol = 1;
        data->ctl = 1;
        data->use_control_tclass = 0;
        data->etclass = 0;
        data->rx_is_router = rx_is_router;
        data->fid_valid = fid_valid;
        data->fid = fid;
        data->rx_is_tunnel = rx_is_tunnel;
        break;

    case SX_PKT_TYPE_DROUTE_EMAD_CTL:
    case SX_PKT_TYPE_EMAD_CTL:
        data->type = 6;
        data->protocol = 1;
        data->ctl = 2;
        data->use_control_tclass = 0;
        data->etclass = 0;
        data->fid = 0;
        data->fid_valid = 0;
        data->rx_is_router = 0;
        break;

    default:
        break;
    }

    data->version = 1;
}

/**
 * Build isx_header from the given meta (meta-data) and push the isx_headr
 * to the beginning of the skb (before the pkt-buffer part) for condor (Version 1)
 */
static int __sx_build_isx_header_v1(struct isx_meta *meta, struct sk_buff *skb, u8 stclass,  u8 hw_etclass)
{
    struct sx_dev            *dev_p;
    struct tx_base_header_v1 *p_hdr;
    struct isx_specific_data  specific_meta;
    unsigned long             flags;

    dev_p = sx_dev_db_get_dev_by_id(meta->dev_id);
    if (!dev_p) {
        return -ENODEV;
    }

    p_hdr = (struct tx_base_header_v1 *)skb_push(skb, ISX_HDR_SIZE);
    if (p_hdr == NULL) {
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "sx_build_isx_header: "
                   "Error in skb_push\n");
        }
        return -ENOMEM;
    }

    if (meta->type == SX_PKT_TYPE_ETH_DATA) {
        if ((!(meta->rx_is_router)) && (meta->fid_valid)) {
            spin_lock_irqsave(&sx_priv(dev_p)->db_lock, flags);

            if (sx_priv(dev_p)->fid_to_hwfid[meta->fid] == INVALID_HW_FID_ID) {
                if (printk_ratelimit()) {
                    printk(KERN_WARNING PFX "Failed to update meta of outgoing packet:"
                           "no fid(%u) to hw_fid mapping \n", meta->fid);
                }
            } else {
                meta->fid = sx_priv(dev_p)->fid_to_hwfid[meta->fid];
            }

            spin_unlock_irqrestore(&sx_priv(dev_p)->db_lock, flags);
        }
    }

    memset(p_hdr, 0, sizeof(*p_hdr));
    memset(&specific_meta, 0, sizeof(specific_meta));
    __get_specific_data_version_1(meta->type, meta->to_cpu,
                                  meta->etclass, meta->lp, meta->rx_is_router,
                                  meta->fid_valid, meta->fid, meta->rx_is_tunnel, &specific_meta);

    p_hdr->version_ctl |=
        TO_FIELD(TX_HDR_VER_MASK_V1,
                 TX_HDR_VER_SHIFT_V1, specific_meta.version);

    p_hdr->version_ctl |=
        TO_FIELD(TX_HDR_CTL_MASK,
                 TX_HDR_CTL_SHIFT, specific_meta.ctl);

    p_hdr->protocol_rx_is_router_rx_is_tunnel_fid_valid |=
        TO_FIELD(TX_HDR_PROTOCOL_MASK,
                 TX_HDR_PROTOCOL_SHIFT,
                 specific_meta.protocol);

    p_hdr->protocol_rx_is_router_rx_is_tunnel_fid_valid |=
        TO_FIELD(TX_HDR_RX_IS_ROUTER_MASK_V1,
                 TX_HDR_RX_IS_ROUTER_SHIFT_V1,
                 specific_meta.rx_is_router);

    p_hdr->protocol_rx_is_router_rx_is_tunnel_fid_valid |=
        TO_FIELD(TX_HDR_RX_IS_TUNNEL_MASK_V1,
                 TX_HDR_RX_IS_TUNNEL_SHIFT_V1,
                 specific_meta.rx_is_tunnel);

    p_hdr->protocol_rx_is_router_rx_is_tunnel_fid_valid |=
        TO_FIELD(TX_HDR_FID_VALID_MASK_V1,
                 TX_HDR_FID_VALID_SHIFT_V1,
                 specific_meta.fid_valid);

    p_hdr->swid_control_etclass |= (u16)TO_FIELD(TX_HDR_SWID_MASK,
                                                 TX_HDR_SWID_SHIFT, meta->swid);

    p_hdr->swid_control_etclass |=
        (u16)TO_FIELD(TX_HDR_CONTROL_MASK_V1,
                      TX_HDR_CONTROL_SHIFT_V1,
                      specific_meta.use_control_tclass);
    p_hdr->swid_control_etclass |=
        (u16)TO_FIELD(TX_HDR_ETCLASS_MASK_V1,
                      TX_HDR_ETCLASS_SHIFT_V1, specific_meta.etclass);

    p_hdr->swid_control_etclass = cpu_to_be16(p_hdr->swid_control_etclass);

    p_hdr->system_port_mid |=
        (u16)TO_FIELD(TX_HDR_SYSTEM_PORT_MID_MASK,
                      TX_HDR_SYSTEM_PORT_MID_SHIFT,
                      meta->system_port_mid);

    p_hdr->system_port_mid = cpu_to_be16(p_hdr->system_port_mid);

    p_hdr->fid |=
        (u16)TO_FIELD(TX_HDR_FID_MASK_V1,
                      TX_HDR_FID_SHIFT_V1,
                      specific_meta.fid);
    p_hdr->fid = cpu_to_be16(p_hdr->fid);

    p_hdr->type |=
        TO_FIELD(TX_HDR_TYPE_MASK,
                 TX_HDR_TYPE_SHIFT, specific_meta.type);

    if (meta->span_oob_data_valid) {
        p_hdr->ext_fwd_mode = meta->span_oob_data.ext_fwd_mode;
        p_hdr->host_based_mirror_reason_mirror_agent = (meta->span_oob_data.span_session_id & 0x7);
        p_hdr->host_based_mirror_reason_mirror_agent |= ((meta->span_oob_data.mirror_reason_id & 0x3) << 3);
    }

    if (tx_debug) {
        pr_debug(PFX "sx_core_post_send: Sending "
                 "pkt with specific meta: "
                 "specific_meta.version: %d , swid: %d , sysport:0x%x, specific_meta.ctl: %d,"
                 "specific_meta.protocol: %d, specific_meta.rx_is_router:%d, type: %d, "
                 "specific_meta.fid_valid: %d,  specific_meta.use_control_tclass: %d, specific_meta.etclass :%d,"
                 "specific_meta.fid: %d, specific_meta.rx_is_tunnel: %d\n",
                 specific_meta.version, meta->swid,
                 meta->system_port_mid,
                 specific_meta.ctl, specific_meta.protocol, specific_meta.rx_is_router, specific_meta.type,
                 specific_meta.fid_valid, specific_meta.use_control_tclass, specific_meta.etclass, specific_meta.fid,
                 specific_meta.rx_is_tunnel);
    }

    return 0;
}

/*
 * Callback for systems with Spectrum 1,2,3
 */
static int __sx_build_isx_header_v1_spc(struct isx_meta *meta, struct sk_buff *skb, u8 stclass, u8 hw_etclass)
{
    if (meta->span_oob_data_valid) {
        printk(KERN_ERR "SPAN OOB message send supported on Spectrum4+ only.\n");
        return -EINVAL;
    }

    return __sx_build_isx_header_v1(meta, skb, stclass, hw_etclass);
}

/*
 * Callback for systems with Spectrum4+
 */
static int __sx_build_isx_header_v1_spc4(struct isx_meta *meta, struct sk_buff *skb, u8 stclass, u8 hw_etclass)
{
    return __sx_build_isx_header_v1(meta, skb, stclass, hw_etclass);
}

static u8 __max_cpu_etclass_for_unlimited_mtu_switchx(void)
{
    return 1; /* PRM 2.8.1 "Egress Traffic Class Allocation" */
}

static int __sx_get_sdq_per_traffic_type(struct sx_dev   *dev,
                                         enum ku_pkt_type type,
                                         u8               swid,
                                         u8               etclass,
                                         u8              *stclass,
                                         u8              *sdq)
{
    if ((type == SX_PKT_TYPE_DROUTE_EMAD_CTL) ||
        (type == SX_PKT_TYPE_EMAD_CTL)) {
        *sdq = 0;
    } else if ((type == SX_PKT_TYPE_ETH_CTL_UC) ||
               (type == SX_PKT_TYPE_ETH_CTL_MC)) {
        *sdq = 1;
    } else {
        *sdq = 2;
    }
    return 0;
}

static int __sx_get_sdq_num_per_etclass(struct sx_dev *dev, u8 swid, u8 etclass, u8 *sdq)
{
    if (sdq == NULL) {
        printk(KERN_ERR "Error: null ptr sdq\n");
        return -EINVAL;
    }

    if (etclass >= NUMBER_OF_ETCLASSES) {
        printk(KERN_ERR "Error: etclass %d is out of range [0..%d], force to 0\n",
               etclass, NUMBER_OF_ETCLASSES);
        return -EINVAL;
    }

    /* Let's use Spectrum1 like schema for SDQ creation.
     *
     * Please note that the further SDQ handling will be based on
     * traffic type and handled by 'sx_get_sdq_cb'
     *
     * Actually we should have 3 SDQ to be created.
     */
    if (etclass < 5) {
        *sdq = 2;
    } else if (etclass < 8) {
        *sdq = 1;
    } else {
        *sdq = 0;
    }

    return 0;
}

static int __sx_get_sdq_from_profile(struct sx_dev   *dev,
                                     enum ku_pkt_type type,
                                     u8               swid,
                                     u8               etclass,
                                     u8              *stclass,
                                     u8              *sdq)
{
    struct sx_priv *priv = sx_priv(dev);

    if ((type == SX_PKT_TYPE_DROUTE_EMAD_CTL) ||
        (type == SX_PKT_TYPE_EMAD_CTL)) {
        if (stclass) {
            *stclass = priv->profile.pci_profile.emad_tx_prof.stclass;
        }
        *sdq = priv->profile.pci_profile.emad_tx_prof.sdq;
        goto out;
    }

    if (swid >= NUMBER_OF_SWIDS) {
        printk(KERN_NOTICE "swid %d is out of range [0..%d], force to 0\n",
               swid, NUMBER_OF_SWIDS);
        swid = 0;
    }

    if (etclass >= NUMBER_OF_ETCLASSES) {
        printk(KERN_NOTICE "etclass %d is out of range [0..%d], force to 0\n",
               etclass, NUMBER_OF_ETCLASSES);
        etclass = 0;
    }

    if (stclass) {
        *stclass = priv->profile.pci_profile.tx_prof[swid][etclass].stclass;
    }
    *sdq = priv->profile.pci_profile.tx_prof[swid][etclass].sdq;

out:
    return 0;
}

static int __sx_get_sdq_num_from_profile(struct sx_dev *dev, u8 swid, u8 etclass, u8 *sdq)
{
    struct sx_priv *priv = sx_priv(dev);

    if (swid >= NUMBER_OF_SWIDS) {
        printk(KERN_ERR "swid %d is out of range [0..%d], force to 0\n",
               swid, NUMBER_OF_SWIDS);
        return -EINVAL;
    }

    if (etclass >= NUMBER_OF_ETCLASSES) {
        printk(KERN_ERR "etclass %d is out of range [0..%d], force to 0\n",
               etclass, NUMBER_OF_ETCLASSES);
        return -EINVAL;
    }

    if (dev == NULL) {
        printk(KERN_ERR "Error: null ptr dev\n");
        return -EINVAL;
    }

    if (sdq == NULL) {
        printk(KERN_ERR "Error: null ptr sdq\n");
        return -EINVAL;
    }

    *sdq = priv->profile.pci_profile.tx_prof[swid][etclass].sdq;

    return 0;
}

static int __sx_core_get_send_to_port_as_data_supported(u8* send_to_port_as_data_supported)
{
    *send_to_port_as_data_supported = false;
    return 0;
}

static int __sx_core_get_send_to_port_as_data_supported_spectrum(u8* send_to_port_as_data_supported)
{
    *send_to_port_as_data_supported = true;
    return 0;
}

static int __get_rp_vid_from_db(struct sx_dev *dev, struct completion_info *comp_info, u16 *vlan_id)
{
    struct sx_priv *dev_priv = sx_priv(dev);
    uint16_t        local = 0, phy_port_max = 0;
    uint16_t        port_lag_id = comp_info->sysport;
    uint8_t         is_lag = comp_info->is_lag;
    unsigned long   flags;

    *vlan_id = 0;

    if (comp_info->is_tagged == VLAN_TAGGED_E) {
        *vlan_id = comp_info->vid;
        return 0;
    }

    if (sx_core_get_phy_port_max(dev, &phy_port_max)) {
        printk(KERN_ERR PFX "Failed to get max number of phy ports.\n");
        return -EINVAL;
    }

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);
    if (is_lag) {
        *vlan_id = dev_priv->lag_rp_vid[port_lag_id];
    } else {
        local = dev_priv->system_to_local_db[port_lag_id];

        if (local > phy_port_max) {
            printk(KERN_ERR PFX "Local %d is invalid. (MAX %d).\n",
                   local, phy_port_max);
            spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
            return -EINVAL;
        }
        *vlan_id = dev_priv->local_rp_vid[local];
    }

    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
    return 0;
}

static int __get_swid_from_db(struct sx_dev *dev, struct completion_info *comp_info, u8 *swid)
{
    enum sx_packet_type pkt_type = comp_info->pkt_type;
    u8                  is_lag = comp_info->is_lag;
    u16                 sysport_lag_id = comp_info->sysport;
    u16                 lag_port_id = comp_info->lag_subport;
    u16                 system_port, local_port, ib_port;
    unsigned long       flags;

    spin_lock_irqsave(&sx_priv(dev)->db_lock, flags);

    switch (pkt_type) {
    case PKT_TYPE_ETH:
    case PKT_TYPE_FCoETH:
        if (is_lag) {
            local_port = sx_priv(dev)->lag_member_to_local_db[sysport_lag_id][lag_port_id];
        } else {
            system_port = sysport_lag_id;
            local_port = sx_priv(dev)->system_to_local_db[system_port];
        }

        break;

    case PKT_TYPE_IB_Raw:
    case PKT_TYPE_IB_non_Raw:
    case PKT_TYPE_FCoIB:
    case PKT_TYPE_ETHoIB:
        ib_port = (sysport_lag_id >> 4) & 0x7f;
        local_port = sx_priv(dev)->ib_to_local_db[ib_port];
        break;

    default:
        if (printk_ratelimit()) {
            printk(KERN_WARNING PFX "Received packet type is FC, "
                   "and therefore unsupported right now\n");
        }
        spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
        return 0;
    }

    *swid = sx_priv(dev)->local_to_swid_db[local_port];
    spin_unlock_irqrestore(&sx_priv(dev)->db_lock, flags);
    return 0;
}

static int __sx_get_lag_mid(struct sx_dev *dev, u16 lag_id, u16 *mid)
{
    if (mid) {
        *mid = lag_id + 0xC000 + sx_priv(dev)->profile.dev_profile.max_mid;
    }
    return 0;
}

static int __get_ib_system_port_mid_with_fix_up(struct sx_dev *dev, u16 ib_port, u16* system_port_mid)
{
    *system_port_mid =
        MAX_ROUTER_MID_TABLE_SIZE - MAX_IB_PORT + ib_port;

    return 0;
}

static void __sx_set_device_profile_update_cqe_v0(struct ku_profile           * profile,
                                                  struct profile_driver_params *driver_params)
{
    profile->set_mask_0_63 = profile->set_mask_0_63 | 0x100000000;
    driver_params->cqe_version = 0;
}

static u8 __sw_rate_limiter_supported(void)
{
    return 1;
}

static int __sx_get_phy_port_max(uint16_t *port)
{
    if (port) {
        *port = SX_CORE_PHY_PORT_NUM_MAX;  /* maximum number of physical ports per PRM */
    } else {
        printk(KERN_ERR PFX "port is NULL\n");
        return -EINVAL;
    }
    return 0;
}

static int __sx_get_lag_max(uint16_t *lags, uint16_t *ports_per_lag)
{
    if (lags) {
        *lags = SX_CORE_LAG_NUM_MAX;  /* maximum number of LAGs per PRM */
    } else {
        printk(KERN_ERR PFX "lags is NULL\n");
        return -EINVAL;
    }

    if (ports_per_lag) {
        *ports_per_lag = SX_CORE_PORTS_PER_LAG_NUM_MAX;  /* maximum number of ports per LAG per PRM */
    } else {
        printk(KERN_ERR PFX "ports_per_lag is NULL\n");
        return -EINVAL;
    }

    return 0;
}

static void __sx_get_rdq_max(uint8_t *max_rdqs, uint16_t *max_entry_size)
{
    if (max_rdqs) {
        *max_rdqs = RDQ_NUM_MAX;
    }

    if (max_entry_size) {
        *max_entry_size = SX_ETH_RDQ_MAX_MSG_SIZE_LEGACY;
    }
}

static u16 __cap_max_mtu_get_spectrum(void)
{
    return KU_CAP_MAX_MTU_SPECTRUM;
}

static int __get_rp_vid_from_ci(struct sx_dev *dev, struct completion_info *comp_info, u16 *vlan_id)
{
    *vlan_id = comp_info->vid;
    return 0;
}

static int __sx_core_get_hw_etclass_impl_spectrum(struct isx_meta *meta, u8* hw_etclass)
{
    /* According to the SX PRM
     * etclass should be set to the following value: (7 - Egress Tclass) */

    *hw_etclass = meta->etclass;

    return 0;
}

static u16 __cap_max_mtu_get_sib(void)
{
    return KU_CAP_MAX_MTU_SWITCH_IB;
}

static int __get_ib_system_port_mid(struct sx_dev *dev, u16 ib_port, u16* system_port_mid)
{
    *system_port_mid = ib_port;
    return 0;
}

static int __sx_get_phy_port_max_quantum(uint16_t *port)
{
    if (port) {
        *port = SX_CORE_PHY_PORT_NUM_QUANTUM_MAX;  /* maximum number of physical ports for Quantum per PRM */
    } else {
        printk(KERN_ERR PFX "port is NULL\n");
        return -EINVAL;
    }
    return 0;
}

static int __is_eqn_cmd_ifc_only(int eqn, u8 *is_cmd_ifc_only)
{
    if (!is_cmd_ifc_only) {
        printk(KERN_ERR PFX "is_cmd_ifc_only is NULL\n");
        return -EINVAL;
    }

    if (eqn == SX_EQ_ASYNC) {
        *is_cmd_ifc_only = 1; /* treat all events in SX_EQ_ASYNC queue as EVENT_TYPE_CMD_IFC */
    } else {
        *is_cmd_ifc_only = 0;
    }

    return 0;
}

static int __sx_get_phy_port_max_quantum2(uint16_t *port)
{
    if (port) {
        *port = SX_CORE_PHY_PORT_NUM_QUANTUM2_MAX;  /* maximum number of physical ports for Quantum2 per PRM */
    } else {
        printk(KERN_ERR PFX "port is NULL\n");
        return -EINVAL;
    }
    return 0;
}

static int __sx_get_phy_port_max_quantum3(uint16_t *port)
{
    if (port) {
        *port = SX_CORE_PHY_PORT_NUM_QUANTUM3_MAX;  /* maximum number of physical ports for Quantum3 per PRM */
    } else {
        printk(KERN_ERR PFX "port is NULL\n");
        return -EINVAL;
    }
    return 0;
}

static u8 __max_cpu_etclass_for_unlimited_mtu_spectrum(void)
{
    return 3; /* PRM 2.8.1 "Egress Traffic Class Allocation" */
}

static int __get_swid_from_ci(struct sx_dev *dev, struct completion_info *comp_info, u8 *swid)
{
    *swid = comp_info->swid;
    return 0;
}

static int __sdk_get_lag_mid(struct sx_dev *dev, u16 lag_id, u16 *mid)
{
    if (mid) {
        *mid = lag_id + 0x100;
    }
    return 0;
}

/* Used for Spectrum4 */
static int __sdk_get_lag_mid_spc4(struct sx_dev *dev, u16 lag_id, u16 *mid)
{
    if (mid) {
        *mid = lag_id + 0x400;
    }
    return 0;
}

static void __sx_set_device_profile_update_cqe_v2(struct ku_profile           * profile,
                                                  struct profile_driver_params *driver_params)
{
    profile->set_mask_0_63 = profile->set_mask_0_63 | 0x100000000;
    driver_params->cqe_version = 1;
}

static void __sx_disconnect_all_trap_groups_spectrum(struct sx_dev *dev)
{
    int                       i;
    struct ku_access_htgt_reg reg_data;
    int                       err;

    memset(&reg_data, 0, sizeof(reg_data));
    reg_data.dev_id = 255;
    sx_cmd_set_op_tlv(&reg_data.op_tlv, HTGT_REG_ID, 2); /* 2 - write */
    reg_data.htgt_reg.swid = 0;
    reg_data.htgt_reg.type = HTGT_NULL_PATH;

    for (i = 0; i < NUM_OF_TRAP_GROUPS; i++) {
        reg_data.htgt_reg.trap_group = i;
        err = sx_ACCESS_REG_HTGT(dev, &reg_data);
        if (err) {
            printk(KERN_ERR PFX "sx_disconnect_all_trap_groups: failed to disconnect trap group %d \n", i);
            return;
        }
    }
    pr_debug(PFX "sx_disconnect_all_trap_groups: succeeded \n");
}

static void __sx_set_device_profile_update_spc2(struct ku_profile            *profile,
                                                struct profile_driver_params *driver_params)
{
    profile->set_mask_0_63 = profile->set_mask_0_63 | 0x500000000;
    driver_params->cqe_version = 1;
    driver_params->cqe_time_stamp_type = 2; /* 2: UTC */
}

static int __sx_get_phy_port_max_spectrum2(uint16_t *port)
{
    if (port) {
        *port = SX_CORE_PHY_PORT_NUM_SPECTRUM2_MAX;  /* maximum number of physical ports for Spectrum2 per PRM */
    } else {
        printk(KERN_ERR PFX "port is NULL\n");
        return -EINVAL;
    }
    return 0;
}

static int __sx_get_lag_max_spectrum2(uint16_t *lags, uint16_t *ports_per_lag)
{
    if (lags) {
        *lags = SX_CORE_LAG_NUM_SPECTRUM2_MAX;  /* maximum number of LAGs per PRM */
    } else {
        printk(KERN_ERR PFX "lags is NULL\n");
        return -EINVAL;
    }

    if (ports_per_lag) {
        *ports_per_lag = SX_CORE_PORTS_PER_LAG_NUM_SPECTRUM2_MAX;  /* maximum number of ports per LAG per PRM */
    } else {
        printk(KERN_ERR PFX "ports_per_lag is NULL\n");
        return -EINVAL;
    }

    return 0;
}

static void __sx_get_rdq_max_spectrum2(uint8_t *max_rdqs, uint16_t *max_entry_size)
{
    if (max_rdqs) {
        *max_rdqs = RDQ_NUM_MAX_SPC2;
    }

    if (max_entry_size) {
        *max_entry_size = SX_ETH_RDQ_MAX_MSG_SIZE_SPC2;
    }
}

static int __sx_get_phy_port_max_spectrum4(uint16_t *port)
{
    if (port) {
        *port = SX_CORE_PHY_PORT_NUM_SPECTRUM4_MAX;  /* maximum number of physical ports for Spectrum4 per PRM */
    } else {
        printk(KERN_ERR PFX "port is NULL\n");
        return -EINVAL;
    }
    return 0;
}

static int __sx_get_lag_max_spectrum4(uint16_t *lags, uint16_t *ports_per_lag)
{
    if (lags) {
        *lags = SX_CORE_LAG_NUM_SPECTRUM4_MAX;  /* maximum number of LAGs per PRM */
    } else {
        printk(KERN_ERR PFX "lags is NULL\n");
        return -EINVAL;
    }

    if (ports_per_lag) {
        *ports_per_lag = SX_CORE_PORTS_PER_LAG_NUM_SPECTRUM4_MAX;  /* maximum number of ports per LAG per PRM */
    } else {
        printk(KERN_ERR PFX "ports_per_lag is NULL\n");
        return -EINVAL;
    }

    return 0;
}

static u8 __is_mirror_header_v2_ext(void)
{
    return 0;
}

static u8 __is_mirror_header_v2_ext_spc4(void)
{
    return 1;
}

/* ********************************************************************************
* SUPPORTED ASIC TYPES
* ********************************************************************************/

static struct dev_specific_cb __spec_cb_sx_a1 = {
    .get_hw_etclass_cb = __sx_core_get_hw_etclass_impl,
    .sx_build_isx_header_cb = __sx_build_isx_header_v0,
    .max_cpu_etclass_for_unlimited_mtu = __max_cpu_etclass_for_unlimited_mtu_switchx,
    .sx_get_sdq_cb = __sx_get_sdq_from_profile,
    .sx_get_sdq_num_cb = __sx_get_sdq_num_from_profile,
    .get_send_to_port_as_data_supported_cb = __sx_core_get_send_to_port_as_data_supported,
    .get_rp_vid_cb = __get_rp_vid_from_db,
    .get_swid_cb = __get_swid_from_db,
    .get_lag_mid_cb = __sx_get_lag_mid,
    .get_ib_system_port_mid = __get_ib_system_port_mid_with_fix_up,
    .sx_ptp_dev_init = NULL,
    .sx_ptp_dev_cleanup = NULL,
    .sx_ptp_dump = NULL,
    .sx_ptp_rx_handler = NULL,
    .sx_ptp_tx_handler = NULL,
    .sx_ptp_tx_ts_handler = NULL,
    .sx_ptp_get_supported_tx_types = NULL,
    .sx_ptp_set_tx_type = NULL,
    .sx_ptp_tx_control_to_data = NULL,
    .sx_set_device_profile_update_cb = __sx_set_device_profile_update_cqe_v0,
    .sx_init_cq_db_cb = sx_init_cq_db_v0,
    .sx_printk_cqe_cb = sx_printk_cqe_v0,
    .is_sw_rate_limiter_supported = __sw_rate_limiter_supported,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v0,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v0,
    .sx_disconnect_all_trap_groups_cb = NULL,
    .sx_get_phy_port_max_cb = __sx_get_phy_port_max,
    .sx_get_lag_max_cb = __sx_get_lag_max,
    .sx_get_rdq_max_cb = __sx_get_rdq_max,
    .is_eqn_cmd_ifc_only_cb = NULL,
    .sx_clock_dev_init = NULL,
    .sx_clock_dev_cleanup = NULL,
    .sx_clock_cqe_ts_to_utc = NULL,
    .sx_clock_dump = NULL,
    .cap_max_mtu_get_cb = __cap_max_mtu_get_spectrum,
    .synce_init_cb = NULL,
    .synce_deinit_cb = NULL,
    .get_chip_reset_type_cb = NULL,
    .is_mirror_header_v2_ext_cb = NULL,
};

static struct dev_specific_cb __spec_cb_sx_a2 = {
    .get_hw_etclass_cb = __sx_core_get_hw_etclass_impl,
    .sx_build_isx_header_cb = __sx_build_isx_header_v0,
    .max_cpu_etclass_for_unlimited_mtu = __max_cpu_etclass_for_unlimited_mtu_switchx,
    .sx_get_sdq_cb = __sx_get_sdq_from_profile,
    .sx_get_sdq_num_cb = __sx_get_sdq_num_from_profile,
    .get_send_to_port_as_data_supported_cb = __sx_core_get_send_to_port_as_data_supported,
    .get_rp_vid_cb = __get_rp_vid_from_ci,
    .get_swid_cb = __get_swid_from_db,
    .get_lag_mid_cb = __sx_get_lag_mid,
    .get_ib_system_port_mid = __get_ib_system_port_mid_with_fix_up,
    .sx_ptp_dev_init = NULL,
    .sx_ptp_dev_cleanup = NULL,
    .sx_ptp_dump = NULL,
    .sx_ptp_rx_handler = NULL,
    .sx_ptp_tx_handler = NULL,
    .sx_ptp_tx_ts_handler = NULL,
    .sx_ptp_get_supported_tx_types = NULL,
    .sx_ptp_set_tx_type = NULL,
    .sx_ptp_tx_control_to_data = NULL,
    .sx_set_device_profile_update_cb = __sx_set_device_profile_update_cqe_v0,
    .sx_init_cq_db_cb = sx_init_cq_db_v0,
    .sx_printk_cqe_cb = sx_printk_cqe_v0,
    .is_sw_rate_limiter_supported = __sw_rate_limiter_supported,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v0,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v0,
    .sx_disconnect_all_trap_groups_cb = NULL,
    .sx_get_phy_port_max_cb = __sx_get_phy_port_max,
    .sx_get_lag_max_cb = __sx_get_lag_max,
    .sx_get_rdq_max_cb = __sx_get_rdq_max,
    .is_eqn_cmd_ifc_only_cb = NULL,
    .sx_clock_dev_init = NULL,
    .sx_clock_dev_cleanup = NULL,
    .sx_clock_cqe_ts_to_utc = NULL,
    .sx_clock_dump = NULL,
    .cap_max_mtu_get_cb = __cap_max_mtu_get_spectrum,
    .synce_init_cb = NULL,
    .synce_deinit_cb = NULL,
    .get_chip_reset_type_cb = NULL,
    .is_mirror_header_v2_ext_cb = NULL,
};

static struct dev_specific_cb __spec_cb_sx_ib = {
    .get_hw_etclass_cb = __sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = __sx_build_isx_header_v0,
    .max_cpu_etclass_for_unlimited_mtu = NULL,
    .sx_get_sdq_cb = __sx_get_sdq_from_profile,
    .sx_get_sdq_num_cb = __sx_get_sdq_num_from_profile,
    .get_send_to_port_as_data_supported_cb = __sx_core_get_send_to_port_as_data_supported,
    .get_rp_vid_cb = __get_rp_vid_from_db,
    .get_swid_cb = __get_swid_from_db,
    .get_lag_mid_cb = NULL,
    .get_ib_system_port_mid = __get_ib_system_port_mid_with_fix_up,
    .sx_ptp_dev_init = NULL,
    .sx_ptp_dev_cleanup = NULL,
    .sx_ptp_dump = NULL,
    .sx_ptp_rx_handler = NULL,
    .sx_ptp_tx_handler = NULL,
    .sx_ptp_tx_ts_handler = NULL,
    .sx_ptp_get_supported_tx_types = NULL,
    .sx_ptp_set_tx_type = NULL,
    .sx_ptp_tx_control_to_data = NULL,
    .sx_set_device_profile_update_cb = __sx_set_device_profile_update_cqe_v0,
    .sx_init_cq_db_cb = sx_init_cq_db_v0,
    .sx_printk_cqe_cb = sx_printk_cqe_v0,
    .is_sw_rate_limiter_supported = __sw_rate_limiter_supported,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v0,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v0,
    .sx_disconnect_all_trap_groups_cb = NULL,
    .sx_get_phy_port_max_cb = __sx_get_phy_port_max,
    .sx_get_lag_max_cb = __sx_get_lag_max,
    .sx_get_rdq_max_cb = __sx_get_rdq_max,
    .is_eqn_cmd_ifc_only_cb = NULL,
    .sx_clock_dev_init = NULL,
    .sx_clock_dev_cleanup = NULL,
    .sx_clock_cqe_ts_to_utc = NULL,
    .sx_clock_dump = NULL,
    .cap_max_mtu_get_cb = __cap_max_mtu_get_sib,
    .synce_init_cb = NULL,
    .synce_deinit_cb = NULL,
    .get_chip_reset_type_cb = sdk_chip_reset_type_sw_reset,
    .is_mirror_header_v2_ext_cb = NULL,
};

static struct dev_specific_cb __spec_cb_quantum = {
    .get_hw_etclass_cb = __sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = __sx_build_isx_header_v0,
    .max_cpu_etclass_for_unlimited_mtu = NULL,
    .sx_get_sdq_cb = __sx_get_sdq_from_profile,
    .sx_get_sdq_num_cb = __sx_get_sdq_num_from_profile,
    .get_send_to_port_as_data_supported_cb = __sx_core_get_send_to_port_as_data_supported,
    .get_rp_vid_cb = __get_rp_vid_from_db,
    .get_swid_cb = __get_swid_from_db,
    .get_lag_mid_cb = NULL,
    .get_ib_system_port_mid = __get_ib_system_port_mid,
    .sx_ptp_dev_init = NULL,
    .sx_ptp_dev_cleanup = NULL,
    .sx_ptp_dump = NULL,
    .sx_ptp_rx_handler = NULL,
    .sx_ptp_tx_handler = NULL,
    .sx_ptp_tx_ts_handler = NULL,
    .sx_ptp_get_supported_tx_types = NULL,
    .sx_ptp_set_tx_type = NULL,
    .sx_ptp_tx_control_to_data = NULL,
    .sx_set_device_profile_update_cb = __sx_set_device_profile_update_cqe_v0,
    .sx_init_cq_db_cb = sx_init_cq_db_v0,
    .sx_printk_cqe_cb = sx_printk_cqe_v0,
    .is_sw_rate_limiter_supported = __sw_rate_limiter_supported,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v0,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v0,
    .sx_disconnect_all_trap_groups_cb = NULL,
    .sx_get_phy_port_max_cb = __sx_get_phy_port_max_quantum,
    .sx_get_lag_max_cb = __sx_get_lag_max,
    .sx_get_rdq_max_cb = __sx_get_rdq_max,
    .is_eqn_cmd_ifc_only_cb = __is_eqn_cmd_ifc_only,
    .sx_clock_dev_init = NULL,
    .sx_clock_dev_cleanup = NULL,
    .sx_clock_cqe_ts_to_utc = NULL,
    .sx_clock_dump = NULL,
    .cap_max_mtu_get_cb = __cap_max_mtu_get_sib,
    .synce_init_cb = NULL,
    .synce_deinit_cb = NULL,
    .get_chip_reset_type_cb = sdk_chip_reset_type_sw_reset,
    .is_mirror_header_v2_ext_cb = NULL,
};

static struct dev_specific_cb __spec_cb_quantum2 = {
    .get_hw_etclass_cb = __sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = __sx_build_isx_header_v0,
    .max_cpu_etclass_for_unlimited_mtu = NULL,
    .sx_get_sdq_cb = __sx_get_sdq_from_profile,
    .sx_get_sdq_num_cb = __sx_get_sdq_num_from_profile,
    .get_send_to_port_as_data_supported_cb = __sx_core_get_send_to_port_as_data_supported,
    .get_rp_vid_cb = __get_rp_vid_from_db,
    .get_swid_cb = __get_swid_from_db,
    .get_lag_mid_cb = NULL,
    .get_ib_system_port_mid = __get_ib_system_port_mid,
    .sx_ptp_dev_init = NULL,
    .sx_ptp_dev_cleanup = NULL,
    .sx_ptp_dump = NULL,
    .sx_ptp_rx_handler = NULL,
    .sx_ptp_tx_handler = NULL,
    .sx_ptp_tx_ts_handler = NULL,
    .sx_ptp_get_supported_tx_types = NULL,
    .sx_ptp_set_tx_type = NULL,
    .sx_ptp_tx_control_to_data = NULL,
    .sx_set_device_profile_update_cb = __sx_set_device_profile_update_cqe_v0,
    .sx_init_cq_db_cb = sx_init_cq_db_v0,
    .sx_printk_cqe_cb = sx_printk_cqe_v0,
    .is_sw_rate_limiter_supported = __sw_rate_limiter_supported,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v0,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v0,
    .sx_disconnect_all_trap_groups_cb = NULL,
    .sx_get_phy_port_max_cb = __sx_get_phy_port_max_quantum2,
    .sx_get_lag_max_cb = __sx_get_lag_max,
    .sx_get_rdq_max_cb = __sx_get_rdq_max,
    .is_eqn_cmd_ifc_only_cb = __is_eqn_cmd_ifc_only,
    .sx_clock_dev_init = NULL,
    .sx_clock_dev_cleanup = NULL,
    .sx_clock_cqe_ts_to_utc = NULL,
    .sx_clock_dump = NULL,
    .cap_max_mtu_get_cb = __cap_max_mtu_get_sib,
    .synce_init_cb = NULL,
    .synce_deinit_cb = NULL,
    .get_chip_reset_type_cb = sdk_chip_reset_type_sw_reset,
    .is_mirror_header_v2_ext_cb = NULL,
};

static struct dev_specific_cb __spec_cb_quantum3 = {
    .get_hw_etclass_cb = __sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = __sx_build_isx_header_v0,
    .max_cpu_etclass_for_unlimited_mtu = NULL,
    .sx_get_sdq_cb = __sx_get_sdq_from_profile,
    .sx_get_sdq_num_cb = __sx_get_sdq_num_from_profile,
    .get_send_to_port_as_data_supported_cb = __sx_core_get_send_to_port_as_data_supported,
    .get_rp_vid_cb = __get_rp_vid_from_db,
    .get_swid_cb = __get_swid_from_db,
    .get_lag_mid_cb = NULL,
    .get_ib_system_port_mid = __get_ib_system_port_mid,
    .sx_ptp_dev_init = NULL,
    .sx_ptp_dev_cleanup = NULL,
    .sx_ptp_dump = NULL,
    .sx_ptp_rx_handler = NULL,
    .sx_ptp_tx_handler = NULL,
    .sx_ptp_tx_ts_handler = NULL,
    .sx_ptp_get_supported_tx_types = NULL,
    .sx_ptp_set_tx_type = NULL,
    .sx_ptp_tx_control_to_data = NULL,
    .sx_set_device_profile_update_cb = __sx_set_device_profile_update_cqe_v0,
    .sx_init_cq_db_cb = sx_init_cq_db_v0,
    .sx_printk_cqe_cb = sx_printk_cqe_v0,
    .is_sw_rate_limiter_supported = __sw_rate_limiter_supported,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v0,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v0,
    .sx_disconnect_all_trap_groups_cb = NULL,
    .sx_get_phy_port_max_cb = __sx_get_phy_port_max_quantum3,
    .sx_get_lag_max_cb = __sx_get_lag_max,
    .sx_get_rdq_max_cb = __sx_get_rdq_max,
    .is_eqn_cmd_ifc_only_cb = __is_eqn_cmd_ifc_only,
    .sx_clock_dev_init = NULL,
    .sx_clock_dev_cleanup = NULL,
    .sx_clock_cqe_ts_to_utc = NULL,
    .sx_clock_dump = NULL,
    .cap_max_mtu_get_cb = __cap_max_mtu_get_sib,
    .synce_init_cb = NULL,
    .synce_deinit_cb = NULL,
    .get_chip_reset_type_cb = sdk_chip_reset_type_reset_by_pci_disable,
    .is_mirror_header_v2_ext_cb = NULL,
};

static struct dev_specific_cb __spec_cb_spectrum = {
    .get_hw_etclass_cb = __sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = __sx_build_isx_header_v1_spc,
    .max_cpu_etclass_for_unlimited_mtu = __max_cpu_etclass_for_unlimited_mtu_spectrum,
    .sx_get_sdq_cb = __sx_get_sdq_per_traffic_type,
    .sx_get_sdq_num_cb = __sx_get_sdq_num_from_profile,
    .get_send_to_port_as_data_supported_cb = __sx_core_get_send_to_port_as_data_supported_spectrum,
    .get_rp_vid_cb = __get_rp_vid_from_ci,
    .get_swid_cb = __get_swid_from_ci,
    .get_lag_mid_cb = __sdk_get_lag_mid,
    .get_ib_system_port_mid = NULL,
    .sx_ptp_dev_init = sx_ptp_dev_init_spc1,
    .sx_ptp_dev_cleanup = sx_ptp_dev_cleanup_spc1,
    .sx_ptp_dump = sx_ptp_dump_spc1,
    .sx_ptp_rx_handler = sx_ptp_rx_handler_spc1,
    .sx_ptp_tx_handler = sx_ptp_tx_handler_spc1,
    .sx_ptp_tx_ts_handler = NULL,
    .sx_ptp_get_supported_tx_types = sx_ptp_get_supported_tx_types_spc1,
    .sx_ptp_set_tx_type = sx_ptp_set_tx_type_spc1,
    .sx_ptp_tx_control_to_data = NULL,
    .sx_set_device_profile_update_cb = __sx_set_device_profile_update_cqe_v2,
    .sx_init_cq_db_cb = sx_init_cq_db_spc,
    .sx_printk_cqe_cb = sx_printk_cqe_v2,
    .is_sw_rate_limiter_supported = NULL,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v2,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v2,
    .sx_disconnect_all_trap_groups_cb = __sx_disconnect_all_trap_groups_spectrum,
    .sx_get_phy_port_max_cb = __sx_get_phy_port_max,
    .sx_get_lag_max_cb = __sx_get_lag_max,
    .sx_get_rdq_max_cb = __sx_get_rdq_max,
    .is_eqn_cmd_ifc_only_cb = NULL,
    .sx_clock_dev_init = sx_clock_dev_init_spc1,
    .sx_clock_dev_cleanup = sx_clock_dev_cleanup_spc1,
    .sx_clock_cqe_ts_to_utc = NULL,
    .sx_clock_dump = sx_clock_dump_spc1,
    .cap_max_mtu_get_cb = __cap_max_mtu_get_spectrum,
    .synce_init_cb = NULL,
    .synce_deinit_cb = sx_core_synce_deinit_spectrum,
    .get_chip_reset_type_cb = sdk_chip_reset_type_sw_reset,
    .is_mirror_header_v2_ext_cb = __is_mirror_header_v2_ext,
};

static struct dev_specific_cb __spec_cb_spectrum2 = {
    .get_hw_etclass_cb = __sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = __sx_build_isx_header_v1_spc,
    .max_cpu_etclass_for_unlimited_mtu = __max_cpu_etclass_for_unlimited_mtu_spectrum,
    .sx_get_sdq_cb = __sx_get_sdq_per_traffic_type,
    .sx_get_sdq_num_cb = __sx_get_sdq_num_per_etclass,
    .get_send_to_port_as_data_supported_cb = __sx_core_get_send_to_port_as_data_supported_spectrum,
    .get_rp_vid_cb = __get_rp_vid_from_ci,
    .get_swid_cb = __get_swid_from_ci,
    .get_lag_mid_cb = __sdk_get_lag_mid,
    .get_ib_system_port_mid = NULL,
    .sx_ptp_dev_init = sx_ptp_dev_init_spc2,
    .sx_ptp_dev_cleanup = sx_ptp_dev_cleanup_spc2,
    .sx_ptp_dump = sx_ptp_dump_spc2,
    .sx_ptp_rx_handler = sx_ptp_rx_handler_spc2,
    .sx_ptp_tx_handler = sx_ptp_tx_handler_spc2,
    .sx_ptp_tx_ts_handler = sx_ptp_tx_ts_handler_spc2,
    .sx_ptp_get_supported_tx_types = sx_ptp_get_supported_tx_types_spc2,
    .sx_ptp_set_tx_type = sx_ptp_set_tx_type_spc2,
    .sx_ptp_tx_control_to_data = sx_ptp_tx_control_to_data_spc2,
    .sx_set_device_profile_update_cb = __sx_set_device_profile_update_spc2,
    .sx_init_cq_db_cb = sx_init_cq_db_v2,
    .sx_printk_cqe_cb = sx_printk_cqe_v2,
    .is_sw_rate_limiter_supported = NULL,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v2,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v2,
    .sx_disconnect_all_trap_groups_cb = __sx_disconnect_all_trap_groups_spectrum,
    .sx_get_phy_port_max_cb = __sx_get_phy_port_max_spectrum2,
    .sx_get_lag_max_cb = __sx_get_lag_max_spectrum2,
    .sx_get_rdq_max_cb = __sx_get_rdq_max_spectrum2,
    .is_eqn_cmd_ifc_only_cb = __is_eqn_cmd_ifc_only,
    .sx_clock_dev_init = sx_clock_dev_init_spc2,
    .sx_clock_dev_cleanup = sx_clock_dev_cleanup_spc2,
    .sx_clock_cqe_ts_to_utc = sx_clock_cqe_ts_to_utc_spc2,
    .sx_clock_dump = sx_clock_dump_spc2,
    .cap_max_mtu_get_cb = __cap_max_mtu_get_spectrum,
    .synce_init_cb = sx_core_synce_init_spectrum,
    .synce_deinit_cb = sx_core_synce_deinit_spectrum,
    .get_chip_reset_type_cb = sdk_chip_reset_type_sw_reset,
    .is_mirror_header_v2_ext_cb = __is_mirror_header_v2_ext,
};

static struct dev_specific_cb __spec_cb_spectrum3 = {
    .get_hw_etclass_cb = __sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = __sx_build_isx_header_v1_spc,
    .max_cpu_etclass_for_unlimited_mtu = __max_cpu_etclass_for_unlimited_mtu_spectrum,
    .sx_get_sdq_cb = __sx_get_sdq_per_traffic_type,
    .sx_get_sdq_num_cb = __sx_get_sdq_num_per_etclass,
    .get_send_to_port_as_data_supported_cb = __sx_core_get_send_to_port_as_data_supported_spectrum,
    .get_rp_vid_cb = __get_rp_vid_from_ci,
    .get_swid_cb = __get_swid_from_ci,
    .get_lag_mid_cb = __sdk_get_lag_mid,
    .get_ib_system_port_mid = NULL,
    .sx_ptp_dev_init = sx_ptp_dev_init_spc2,
    .sx_ptp_dev_cleanup = sx_ptp_dev_cleanup_spc2,
    .sx_ptp_dump = sx_ptp_dump_spc2,
    .sx_ptp_rx_handler = sx_ptp_rx_handler_spc2,
    .sx_ptp_tx_handler = sx_ptp_tx_handler_spc2,
    .sx_ptp_tx_ts_handler = sx_ptp_tx_ts_handler_spc2,
    .sx_ptp_get_supported_tx_types = sx_ptp_get_supported_tx_types_spc2,
    .sx_ptp_set_tx_type = sx_ptp_set_tx_type_spc2,
    .sx_ptp_tx_control_to_data = sx_ptp_tx_control_to_data_spc2,
    .sx_set_device_profile_update_cb = __sx_set_device_profile_update_spc2,
    .sx_init_cq_db_cb = sx_init_cq_db_v2,
    .sx_printk_cqe_cb = sx_printk_cqe_v2,
    .is_sw_rate_limiter_supported = NULL,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v2,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v2,
    .sx_disconnect_all_trap_groups_cb = __sx_disconnect_all_trap_groups_spectrum,
    .sx_get_phy_port_max_cb = __sx_get_phy_port_max_spectrum2,
    .sx_get_lag_max_cb = __sx_get_lag_max_spectrum2,
    .sx_get_rdq_max_cb = __sx_get_rdq_max_spectrum2,
    .is_eqn_cmd_ifc_only_cb = NULL,
    .sx_clock_dev_init = sx_clock_dev_init_spc2,
    .sx_clock_dev_cleanup = sx_clock_dev_cleanup_spc2,
    .sx_clock_cqe_ts_to_utc = sx_clock_cqe_ts_to_utc_spc2,
    .sx_clock_dump = sx_clock_dump_spc2,
    .cap_max_mtu_get_cb = __cap_max_mtu_get_spectrum,
    .synce_init_cb = NULL,
    .synce_deinit_cb = sx_core_synce_deinit_spectrum,
    .get_chip_reset_type_cb = sdk_chip_reset_type_sw_reset,
    .is_mirror_header_v2_ext_cb = __is_mirror_header_v2_ext,
};

static struct dev_specific_cb __spec_cb_spectrum4 = {
    .get_hw_etclass_cb = __sx_core_get_hw_etclass_impl_spectrum,
    .sx_build_isx_header_cb = __sx_build_isx_header_v1_spc4,
    .max_cpu_etclass_for_unlimited_mtu = __max_cpu_etclass_for_unlimited_mtu_spectrum,
    .sx_get_sdq_cb = __sx_get_sdq_per_traffic_type,
    .sx_get_sdq_num_cb = __sx_get_sdq_num_per_etclass,
    .get_send_to_port_as_data_supported_cb = __sx_core_get_send_to_port_as_data_supported_spectrum,
    .get_rp_vid_cb = __get_rp_vid_from_ci,
    .get_swid_cb = __get_swid_from_ci,
    .get_lag_mid_cb = __sdk_get_lag_mid_spc4,
    .get_ib_system_port_mid = NULL,
    .sx_ptp_dev_init = sx_ptp_dev_init_spc2,
    .sx_ptp_dev_cleanup = sx_ptp_dev_cleanup_spc2,
    .sx_ptp_dump = sx_ptp_dump_spc2,
    .sx_ptp_rx_handler = sx_ptp_rx_handler_spc2,
    .sx_ptp_tx_handler = sx_ptp_tx_handler_spc2,
    .sx_ptp_tx_ts_handler = sx_ptp_tx_ts_handler_spc2,
    .sx_ptp_get_supported_tx_types = sx_ptp_get_supported_tx_types_spc2,
    .sx_ptp_set_tx_type = sx_ptp_set_tx_type_spc2,
    .sx_ptp_tx_control_to_data = sx_ptp_tx_control_to_data_spc2,
    .sx_set_device_profile_update_cb = __sx_set_device_profile_update_spc2,
    .sx_init_cq_db_cb = sx_init_cq_db_v2,
    .sx_printk_cqe_cb = sx_printk_cqe_v2,
    .is_sw_rate_limiter_supported = NULL,
    .sx_fill_ci_from_cqe_cb = sx_fill_ci_from_cqe_v2,
    .sx_fill_params_from_cqe_cb = sx_fill_params_from_cqe_v2,
    .sx_disconnect_all_trap_groups_cb = __sx_disconnect_all_trap_groups_spectrum,
    .sx_get_phy_port_max_cb = __sx_get_phy_port_max_spectrum4,
    .sx_get_lag_max_cb = __sx_get_lag_max_spectrum4,
    .sx_get_rdq_max_cb = __sx_get_rdq_max_spectrum2,
    .is_eqn_cmd_ifc_only_cb = NULL,
    .sx_clock_dev_init = sx_clock_dev_init_spc2,
    .sx_clock_dev_cleanup = sx_clock_dev_cleanup_spc2,
    .sx_clock_cqe_ts_to_utc = sx_clock_cqe_ts_to_utc_spc2,
    .sx_clock_dump = sx_clock_dump_spc2,
    .cap_max_mtu_get_cb = __cap_max_mtu_get_spectrum,
    .synce_init_cb = NULL,
    .synce_deinit_cb = sx_core_synce_deinit_spectrum,
    .get_chip_reset_type_cb = sdk_chip_reset_type_reset_by_pci_disable,
    .is_mirror_header_v2_ext_cb = __is_mirror_header_v2_ext_spc4,
};

/* ********************************************************************************
* ********************************************************************************/

int sx_core_dev_init_switchx_cb(struct sx_dev *dev, enum sxd_chip_types chip_type, bool force)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    unsigned long   flags;

    spin_lock_irqsave(&priv->db_lock, flags);

    if (!force && priv->dev_specific_cb_init_done) {
        printk(KERN_ERR PFX "init callbacks called but just was initialized, chip_type [%d].\n",
               chip_type);
        goto out;
    }

    memset(&(priv->dev_specific_cb), 0, sizeof(priv->dev_specific_cb));

    /* init specific and common callbacks per device revision */
    switch (chip_type) {
    case SXD_CHIP_TYPE_SWITCHX_A0:
        sx_err(dev, "Cannot add device , the SDK does not support "
               "SwitchX with revision A0\n");
        err = -EINVAL;
        break;

    case SXD_CHIP_TYPE_SWITCHX_A1:
        /* for A1 revision add specific cb */
        priv->dev_specific_cb = __spec_cb_sx_a1;
        break;

    case SXD_CHIP_TYPE_SWITCHX_A2:
        priv->dev_specific_cb = __spec_cb_sx_a2;
        break;

    case SXD_CHIP_TYPE_SWITCH_IB:
    case SXD_CHIP_TYPE_SWITCH_IB2:
        /* for pelican/eagle add specific cb */
        priv->dev_specific_cb = __spec_cb_sx_ib;
        break;

    case SXD_CHIP_TYPE_QUANTUM:
        /* for quantum add specific cb */
        priv->dev_specific_cb = __spec_cb_quantum;
        break;

    case SXD_CHIP_TYPE_QUANTUM2:
        /* for quantum2 add specific cb */
        priv->dev_specific_cb = __spec_cb_quantum2;
        break;

    case SXD_CHIP_TYPE_QUANTUM3:
        /* for quantum2 add specific cb */
        priv->dev_specific_cb = __spec_cb_quantum3;
        break;

    case SXD_CHIP_TYPE_SPECTRUM:
    case SXD_CHIP_TYPE_SPECTRUM_A1:
        /* for condor add specific cb */
        priv->dev_specific_cb = __spec_cb_spectrum;
        break;

    case SXD_CHIP_TYPE_SPECTRUM2:
        /* for spectrum2 add specific cb */
        priv->dev_specific_cb = __spec_cb_spectrum2;
        break;

    case SXD_CHIP_TYPE_SPECTRUM3:
        /* for spectrum3 add specific cb */
        priv->dev_specific_cb = __spec_cb_spectrum3;
        break;

    case SXD_CHIP_TYPE_SPECTRUM4:
        /* for spectrum4 add specific cb */
        priv->dev_specific_cb = __spec_cb_spectrum4;
        break;

    default:
        err = -EINVAL;
        sx_err(dev, "ERROR:hw_ver: 0x%x unsupported. \n",
               chip_type);
        goto out;
    }

    priv->dev_specific_cb_init_done = true;
    priv->dev_info.dev_info_ro.chip_type = chip_type;
    priv->dev_info.dev_info_ro.fw_boot_status = SXD_FW_BOOT_STATUS_OK_E;
    pr_debug(PFX "sx_core_dev_init_switchx_cb chip_type [%d]\n", chip_type);

out:
    spin_unlock_irqrestore(&priv->db_lock, flags);

    /*      we take the reference in init and release in deinit to get event
     * in case refcnt is 0
     */
    if (__sx_core_dev_specific_cb_get_reference(dev) != 0) {
        printk(KERN_ERR "could not get specific cb reference!\n");
        if (!err) { /* if no error till now, assign an error to return */
            err = -EFAULT;
        }
    }

    return err;
}

int sx_core_dev_deinit_switchx_cb(struct sx_dev *dev)
{
    struct sx_priv *priv = sx_priv(dev);
    int             err = 0;
    unsigned long   flags;

    spin_lock_irqsave(&priv->db_lock, flags);

    if (!priv->dev_specific_cb_init_done) {
        printk(KERN_ERR PFX "deinit callbacks called before was initialized. \n");
        spin_unlock_irqrestore(&priv->db_lock, flags);
        goto out;
    }

    priv->dev_specific_cb_init_done = false;

    spin_unlock_irqrestore(&priv->db_lock, flags);

    __sx_core_dev_specific_cb_release_reference(dev);

    /*
     * wait for refcnt == 0
     * In case of timeout , wait_event_timeout return with a value of 0
     * regardless of how condition evaluates.
     */
    if (!wait_event_timeout(priv->dev_specific_cb_not_in_use,
                            !atomic_read(&priv->dev_specific_cb_refcnt),
                            SX_CORE_DEV_CB_FINISH_WAIT_TIMEOUT)) {
        printk(KERN_ERR PFX "sx_core_dev_specific_cb_deinit_timeout.\n");
        err = -EBUSY;
        goto out;
    }

    memset(&(priv->dev_specific_cb), 0, sizeof(priv->dev_specific_cb));

    pr_debug(PFX "sx_core_dev_deinit_cb done successfully.\n");

out:

    return err;
}
